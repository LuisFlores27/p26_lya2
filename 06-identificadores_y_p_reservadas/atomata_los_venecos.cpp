#include <iostream>
#include <string>
#include <vector>
#include "estados_palabras_Los_Venecos.h"

using namespace std;

bool esReservada(string str) {
    string Reservadas[] = {"if", "else", "while", "for", "int", "float", "char", "void"};
    for (const string& res : Reservadas) {
        if (str == res) return true;
    }
    return false;
}

int analiza(string str) {
    // si es reservada, va al estado 11
    if (esReservada(str)) return E_RES;

    int estado = E_INICIAL;

    for (char c : str) {
        switch (estado) {
            case E_INICIAL:
                if (isdigit(c)) estado = E_ENTERO;
                else if (c == '+' || c == '-') estado = E_SIGNO;
                else if (c == '.') estado = E_PUNTO;
                else if (islower(c)) estado = E_MIN;
                else if (isupper(c)) estado = E_MAY;
                else return E_ERROR;
                break;

            case E_SIGNO:
                if (isdigit(c)) estado = E_ENTERO;
                else if (c == '.') estado = E_PUNTO;
                else return E_ERROR;
                break;

            case E_ENTERO:
                if (isdigit(c)) estado = E_ENTERO;
                else if (c == '.') estado = E_PUNTO;
                else if (c == 'e' || c == 'E') estado = E_EXP;
                else return E_ERROR;
                break;

            case E_PUNTO:
                if (isdigit(c)) estado = E_FLOTANTE;
                else return E_ERROR;
                break;

            case E_FLOTANTE:
                if (isdigit(c)) estado = E_FLOTANTE;
                else if (c == 'e' || c == 'E') estado = E_EXP;
                else return E_ERROR;
                break;

            case E_EXP:
                if (c == '+' || c == '-') estado = E_EXP_SIGNO;
                else if (isdigit(c)) estado = E_NOTA_CIEN;
                else return E_ERROR;
                break;

            case E_EXP_SIGNO:
                if (isdigit(c)) estado = E_NOTA_CIEN;
                else return E_ERROR;
                break;

            case E_NOTA_CIEN:
                if (isdigit(c)) estado = E_NOTA_CIEN;
                else return E_ERROR;
                break;

            case E_MIN:
                if (islower(c)) estado = E_MIN;
                else if (isupper(c)) estado = E_MAY;
                else if (c == '_') estado = E_GUION;
                else return E_ERROR;
                break;

            case E_MAY:
                if (isupper(c)) estado = E_MAY;
                else if (islower(c)) estado = E_MIN;
                else if (c == '_') estado = E_GUION;
                else return E_ERROR;
                break;

            case E_GUION:
                if (islower(c)) estado = E_MIN;
                else if (isupper(c)) estado = E_MAY;
                else return E_ERROR;
                break;

            default:
                return E_ERROR;
        }
    }

    if (estado == 2 || estado == 4 || estado == 7 || estado == 8 || estado == 9 || estado == 10 || estado == 11) {
        return estado;
    }
    
    return E_ERROR;
}

int main() {
    string cadena;
    cout << "Ingrese la cadena a analizar: ";
    cin >> cadena;

    int res = analiza(cadena);

    switch (res) {
        case E_ENTERO: cout << "Resultado: Numero Entero (Estado 2)" << endl; break;
        case E_FLOTANTE: cout << "Resultado: Numero Decimal (Estado 4)" << endl; break;
        case E_NOTA_CIEN: cout << "Resultado: Notacion Cientifica (Estado 7)" << endl; break;
        case E_MIN:
        case E_MAY:
        case E_GUION: cout << "Resultado: Identificador Valido (Estados 8-10)" << endl; break;
        case E_RES: cout << "Resultado: Palabra Reservada (Estado 11)" << endl; break;
        default: cout << "Error: Cadena no reconocida por el automata." << endl;
    }

    return 0;
}