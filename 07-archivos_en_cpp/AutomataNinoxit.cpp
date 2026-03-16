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

const std::string reservadas  = "|const|int|double|float|if|else|switch|case|default|for|while|do|string|char|list|vector|return|void|bool|true|false|";
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
        default:                return "ERROR";
    }
}

void tokenizar(const std::string& linea, int numLinea, std::stack<std::string>& pila) {
    int n = (int)linea.size();
    if (n == 0) return;

    // Preprocesador
    if (linea[0] == '#') {
        pila.push("Linea " + std::to_string(numLinea) + " | PREPROCESADOR | " + linea);
        return;
    }

    // Comentario de línea completa
    if (n >= 2 && linea[0] == '/' && linea[1] == '/') {
        pila.push("Linea " + std::to_string(numLinea) + " | COMENTARIO | " + linea);
        return;
    }

    std::string token = "";
    int i = 0;

    auto flush = [&]() {
        if (!token.empty()) {
            int estado = analizador(token);
            pila.push("Linea " + std::to_string(numLinea) + " | " + nombreEstado(estado) + " | " + token);
            token = "";
        }
    };

    while (i < n) {
        char ch = linea[i];

        // Comentario inline
        if (ch == '/' && i + 1 < n && linea[i+1] == '/') {
            flush();
            pila.push("Linea " + std::to_string(numLinea) + " | COMENTARIO | " + linea.substr(i));
            break;
        }

        // Separador
        if (separadores.find(ch) != std::string::npos) {
            flush();
            pila.push("Linea " + std::to_string(numLinea) + " | SEPARADOR | " + std::string(1, ch));
            i++;
            continue;
        }

        // Espacios y tabs solo separan
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