//Jose Ismael Gonzalez Cosme 220111522
//Jesus Gerardo De la O Duran 230120115
//Aaron Alejandro Martinez Serrano 230120317
//Karina Guadalupe Munoz Avila 230120315

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "estados_palabras_Los_Venecos.h"

using namespace std;

bool esSimbolo(char c) {
    string simbolos = "%*^~(){}[];,=\":!\'>"; 
    return simbolos.find(c) != string::npos;
}

bool esReservada(string str) {
    string Reservadas[] = {"if", "else", "while", "for", "int", "float", "char", "void", "#include", "return", "class", "public", "private", "protected", "static", "const", "break", "continue", "switch", "case", "default"};
    for (const string& res : Reservadas) {
        if (str == res)
         return true;
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
                else if (c == '+' || c == '-') estado = E_SIGNOP;
                else if  (c == '%' || c == '*' || c == '^' || c == '~') estado = E_SIGNO;
                else if (c == '/') estado = E_DIG;
                else if (c == '.') estado = E_PUNTO;
                else if (islower(c)) estado = E_MIN;
                else if (isupper(c)) estado = E_MAY;
                else if ( c == '<' || c == '"' ) estado = E_LIB;
                else if (esSimbolo(c)) estado = E_SIMB;
                else return E_ERROR;
                break;

            case E_LIB:
                 if (c == '<') estado = E_MEN;
                 else if (islower(c)) estado = E_SIM;
                 else return E_ERROR;
                 break;
            case E_DIG:
                    if (c == '/') estado = E_DIG;
                    else return E_ERROR;
                    break;
            case E_MEN:
                return E_ERROR;
                break;
            case E_SIMB:
                return E_ERROR;
                break;
            case E_SIM:
                if (c == '>' || c == '"') estado = E_SIM;
                else if (islower(c)) estado = E_SIM;
                else return E_ERROR;
                break;

            case E_SIGNOP:
                if (isdigit(c)) estado = E_ENTERO;
                else if (c == '.') estado = E_PUNTO;
                else if (c == E_SIGNOP) estado = E_SIGNOP; 
                else return E_ERROR;
                break;
            case E_SIGNO:
                if (estado == E_SIGNO) estado = E_SIGNO; 
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

    if (estado == 1 ||estado == 2 || estado == 4 || estado == 7 || estado == 8 || estado == 9 || estado == 10 || estado == 11 || estado == 12 || estado == 13 || estado == 14 || estado == 15 || estado == 16 || estado == 17) {
        return estado;
    }
    
    return E_ERROR;
}

void procesarPalabra(string palabra) {
    int res = analiza(palabra);

    
    cout << "[" << palabra << "] -> ";
    switch (res) {
        case E_ENTERO: 
            cout << "Numero Entero" << endl; 
            break;
        case E_FLOTANTE: 
            cout << "Numero Decimal" << endl; 
            break;
        case E_SIGNOP: 
        case E_SIGNO:
            cout << "Signo de Operacion" << endl; 
            break;
        case E_NOTA_CIEN: 
            cout << "Notacion Cientifica" << endl; 
            break;
        case E_SIM:
            cout << "Simbolo / Libreria" << endl; 
            break;
        case E_MIN:
        case E_MAY:
        case E_GUION: 
            cout << "Identificador Valido" << endl; 
            break;
        case E_RES: 
            cout << "Palabra Reservada" << endl; 
            break;
        case E_LIB:
            cout << "Simbolo / Libreria" << endl; 
            break;
        case E_DIG:
            cout << "Comentario de Linea" << endl; 
            break;
        case E_MEN:
            cout << "Comentario de Bloque" << endl; 
            break;
        case E_SIMB:   
            cout << "Simbolo Especial" << endl;
            break;
        default: 
            cout << "Error: Cadena no reconocida por el automata." << endl;
    }
} 

string separarSimbolos(string linea) {

    size_t pos = 0;
    while ((pos = linea.find("<<", pos)) != string::npos) {
        linea.replace(pos, 2, " << ");
        pos += 4; 
    }

    
    pos = 0;
    while ((pos = linea.find("//", pos)) != string::npos) {
        linea.replace(pos, 2, " // ");
        pos += 4;
    }

    string resultado = ""; 

    for (char c : linea) {
        if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' ||
            c == ';' || c == ',' || c == '*' || c == '"' || c == '='|| c == ':' || c == '!' || c == '.') {
            resultado += " "; 
            resultado += c;  
            resultado += " ";
        } 
    
        else {
            resultado += c; 
        }
    }

    return resultado;
}
int main (int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Error: no hay suficientes argumentos" << endl;
        return 1;
    }

    string nombreArchivo = argv[1];
    ifstream archivo(nombreArchivo);

    // Comprobamos si el archivo se abrio correctamente
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'" << endl;
        return 1;
    }

    string linea;

    while(getline(archivo, linea)) {

          //Separamos simbolos de palabras
          linea = separarSimbolos(linea);

        //Cortarmos por espacios
        istringstream flujo(linea);
        string palabra;

        //Extraemos palabra por palabra de esa línea
        while(flujo >> palabra) {
            procesarPalabra(palabra);
            
        }
    }
    
    archivo.close();
    return 0;
}