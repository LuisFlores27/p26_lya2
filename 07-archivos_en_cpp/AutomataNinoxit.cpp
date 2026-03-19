/*
    Equipo Ninoxit
    Soely Mayomi Camacho Camacho
    Daniela Ivette Nava Miranda
*/
#include "AutomataNinoxit.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

const std::string reservadas = "|auto|break|case|catch|char|class|const|const_cast|continue|"
                               "default|delete|do|double|dynamic_cast|else|enum|explicit|export|"
                               "extern|false|float|for|friend|goto|if|inline|int|long|mutable|"
                               "namespace|new|operator|private|protected|public|register|"
                               "reinterpret_cast|return|short|signed|sizeof|static|static_cast|"
                               "struct|switch|template|this|throw|true|try|typedef|typeid|"
                               "typename|union|unsigned|using|virtual|void|volatile|while|"
                               "string|list|vector|map|set|pair|stack|queue|cout|cin|cerr|endl|";

const std::string numeros     = "1234567890";
const std::string letras      = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
const std::string separadores = "+-*/%=<>!&|(){}[];,";

bool checker(const std::string& word, const std::string base) {
    if (word.empty()) return false;
    return (base.find("|" + word + "|") != std::string::npos);
}

int analizador(const std::string& cadena) {
    int estado = E_INICIAL;
    if (cadena.empty()) return E_ERROR;

    for (char ch : cadena) {
        const std::string _ch(1, ch);

        if (numeros.find(ch) != std::string::npos) {
            switch (estado) {
                case E_INICIAL:
                case E_SIGNO:
                case E_ENTERO:        estado = E_ENTERO;        break;
                case E_PUNTO:
                case E_FLOTANTE:      estado = E_FLOTANTE;      break;
                case E_NOTA_CIEN:     estado = E_NOTA_CIEN;     break;
                case E_IDENTIFICADOR: estado = E_IDENTIFICADOR; break;
                default:              estado = E_ERROR;
            }
        }
        else if (letras.find(ch) != std::string::npos) {
            switch (estado) {
                case E_INICIAL:
                case E_IDENTIFICADOR: estado = E_IDENTIFICADOR; break;
                default:              estado = E_ERROR;
            }
        }
        else if (ch == '.') {
            if (estado == E_ENTERO) estado = E_PUNTO;
            else                    estado = E_ERROR;
        }
        else if (ch == '+' || ch == '-') {
            if (estado == E_INICIAL) estado = E_SIGNO;
            else                     estado = E_ERROR;
        }
        else {
            estado = E_ERROR;
        }

        if (estado == E_ERROR) break;
    }

    if (estado == E_IDENTIFICADOR && checker(cadena, reservadas))
        estado = E_RESERVADA;

    return estado;
}

std::string nombreEstado(int estado) {
    switch (estado) {
        case E_ENTERO:          return "ENTERO";
        case E_FLOTANTE:        return "FLOTANTE";
        case E_IDENTIFICADOR:   return "IDENTIFICADOR";
        case E_RESERVADA:       return "RESERVADA";
        case E_SEPARADOR:       return "SEPARADOR";
        case E_COMENTARIO:      return "COMENTARIO";
        case E_PREPROCESADOR:   return "PREPROCESADOR";
        case E_FUNCION:         return "FUNCION";
        case E_CADENA:          return "CADENA";
        default:                return "ERROR";
    }
}

void tokenizar(const std::string& linea, int numLinea, std::stack<std::string>& pila) {
    int n = (int)linea.size();
    if (n == 0) return;

    // Preprocesadores
    if (linea[0] == '#') {
        pila.push("Linea " + std::to_string(numLinea) + " | PREPROCESADOR | " + linea);
        return;
    }

    // Comentarios
    if (n >= 2 && linea[0] == '/' && linea[1] == '/') {
        pila.push("Linea " + std::to_string(numLinea) + " | COMENTARIO | " + linea);
        return;
    }

    std::string token = "";
    int i = 0;

    auto flush = [&]() {
        if (!token.empty()) {
            int estado = analizador(token);

            
            if (estado == E_IDENTIFICADOR || estado == E_RESERVADA) {
                int j = i;
                while (j < n && (linea[j] == ' ' || linea[j] == '\t')) j++;
                if (j < n && linea[j] == '(') estado = E_FUNCION;
            }

            pila.push("Linea " + std::to_string(numLinea) + " | " + nombreEstado(estado) + " | " + token);
            token = "";
        }
    };

    while (i < n) {
        char ch = linea[i];

        if (ch == '/' && i + 1 < n && linea[i+1] == '/') {
            flush();
            pila.push("Linea " + std::to_string(numLinea) + " | COMENTARIO | " + linea.substr(i));
            break;
        }

        if (ch == '"') {
            flush();
            std::string lit(1, ch); i++;
            while (i < n && linea[i] != '"') {
                if (linea[i] == '\\' && i+1 < n) { lit += linea[i++]; }
                lit += linea[i++];
            }
            if (i < n) { lit += linea[i++]; }
            pila.push("Linea " + std::to_string(numLinea) + " | CADENA | " + lit);
            continue;
        }

        if (ch == '\'') {
            flush();
            std::string lit(1, ch); i++;
            while (i < n && linea[i] != '\'') {
                if (linea[i] == '\\' && i+1 < n) { lit += linea[i++]; }
                lit += linea[i++];
            }
            if (i < n) { lit += linea[i++]; }
            pila.push("Linea " + std::to_string(numLinea) + " | CADENA | " + lit);
            continue;
        }

        // Separadores
        if (separadores.find(ch) != std::string::npos) {
            flush();
            pila.push("Linea " + std::to_string(numLinea) + " | SEPARADOR | " + std::string(1, ch));
            i++;
            continue;
        }

        if (ch == ' ' || ch == '\t') { flush(); i++; continue; }

        token += ch;
        i++;
    }

    flush();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo.cpp>" << std::endl;
        return 1;
    }

    std::ifstream archivo(argv[1]);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir '" << argv[1] << "'" << std::endl;
        return 1;
    }

    std::stack<std::string> pila;
    std::string linea;
    int numLinea = 1;

    while (std::getline(archivo, linea)) {
        tokenizar(linea, numLinea, pila);
        numLinea++;
    }

    archivo.close();

    std::cout << "\n=== Tokens encontrados ===\n";
    while (!pila.empty()) {
        std::cout << pila.top() << "\n";
        pila.pop();
    }

    return 0;
}