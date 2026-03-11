/*
    Equipo Ninoxit
    Soely Mayomi Camacho Camacho
    Daniela Ivette Nava Miranda
*/
#include "AutomataNinoxit.h"

const std::string reservadas = "const|int|double|float|if|else|switch|case|default|for|while|do|string|char|list|vector";
const std::string numeros = "1234567890";
const std::string letras = "abcdefghijklmnopqrstuvwxyz";

bool checker(const std::string& word, const std::string base) {
    if (word.empty()) return false;
    return (base.find(word) != std::string::npos);
}

int analizador(const std::string& cadena) {
    int estado = E_INICIAL;

    if (cadena.empty()) return E_ERROR;
    
    for (char ch : cadena) {
        const std::string _ch(1, ch);

        if (checker(_ch, numeros)) {
            switch (estado) {
                case E_INICIAL:
                case E_SIGNO:
                case E_ENTERO:
                    estado = E_ENTERO;
                    break;
                case E_PUNTO:
                case E_FLOTANTE:
                    estado = E_FLOTANTE;
                    break;
                case E_NOTA_CIEN:
                    estado = E_NOTA_CIEN;
                    break;
                case E_IDENTIFICADOR:
                    estado = E_IDENTIFICADOR;
                    break;
                default:
                    estado = E_ERROR;
            }
        }
        else if (checker(_ch, letras)) {
            switch (estado) {
                case E_INICIAL:
                case E_IDENTIFICADOR:
                    estado = E_IDENTIFICADOR;
                    break;
                default:
                    estado = E_ERROR;
            }
        }
        else if (ch == '.') {
            if (estado == E_ENTERO) {
                estado = E_PUNTO;
            } else {
                estado = E_ERROR;
            }
        }
        else if (ch == '+' || ch == '-') {
            if (estado == E_INICIAL) {
                estado = E_SIGNO;
            } else {
                estado = E_ERROR;
            }
        }
        else {
            estado = E_ERROR;
        }

        if (estado == E_ERROR) break;
    }
   
    if (estado == E_IDENTIFICADOR && checker(cadena, reservadas)) {
        estado = E_RESERVADA;
    }
    
    return estado;
}

int main() {
    // solo testeando con un flag debug
    // igual lo quitamos
    bool debug = 1;
    std::string cadenaInvalida = "";
    std::string cadenaValida = "+";
    
    std::cout << analizador((debug == true) ? cadenaInvalida : cadenaValida);
    return 0;
}