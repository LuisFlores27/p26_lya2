/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

 //Jose Jaime Nuñez Vazquez NC: 230120398
 //Eliand Andres Murillo Ramos NC: 23012470
 //Luis Angel Flores Espinosa NC: 210110157
 //Juan Roberto Aguilar Molina NC: 210110268

#include <iostream>
#include <string>
#include <cctype>

#include "estados_Los_Chamos.h"

using namespace std;

bool esReservada(string str) {
    string reservadas[] = {
        "int", "float", "double", "char",
        "if", "else", "while", "for", "return"
    };

    for (string r : reservadas) {
        if (str == r)
            return true;
    }
    return false;
}

int analiza(string str)
{
    int estado = E_INICIAL;

    for (char c : str) {

        switch (c) {

        case '*':
        case '/':
        case '%':
            if (str.length() == 1)
                return E_OP_ARIT;
            else
                return E_ERROR;

        case '+':
        case '-':
            if (str.length() == 1)
                return E_OP_ARIT;
            else if (estado == E_INICIAL)
                estado = E_SIGNO;
            else if (estado == E_EXP)
                estado = E_EXP_SIGNO;
            else
                return E_ERROR;
            break;


        case '.':
            if (estado == E_ENTERO)
                estado = E_PUNTO;
            else
                return E_ERROR;
            break;

        case 'e':
        case 'E':
            if (estado == E_ENTERO || estado == E_FLOTANTE)
                estado = E_EXP;
            else if (estado == E_IDENT)
                estado = E_IDENT;
            else
                return E_ERROR;
            break;


        default:

            if (isdigit(c)) {
                if (estado == E_INICIAL || estado == E_SIGNO)
                    estado = E_ENTERO;
                else if (estado == E_ENTERO)
                    estado = E_ENTERO;
                else if (estado == E_PUNTO)
                    estado = E_FLOTANTE;
                else if (estado == E_FLOTANTE)
                    estado = E_FLOTANTE;
                else if (estado == E_EXP || estado == E_EXP_SIGNO)
                    estado = E_NOTA_CIEN;
                else if (estado == E_NOTA_CIEN)
                    estado = E_NOTA_CIEN;
                else if (estado == E_IDENT)
                    estado = E_IDENT;
                else
                    return E_ERROR;
            }       

            else if (isalpha(c) || c == '_') {
                if (estado == E_INICIAL)
                    estado = E_IDENT;
                else if (estado == E_IDENT)
                    estado = E_IDENT;
                else
                    return E_ERROR;
            }

            else {
                return E_ERROR;
            }

            break;
        }
    }

    return estado;
}

int main()
{
    string cadena;
    cin >> cadena;

    int estado_final = analiza(cadena);

    if (esReservada(cadena)) {
        cout << "Es una palabra reservada" << endl;
    }
    else {
        switch (estado_final) {

        case E_ENTERO:
            cout << "Es un entero" << endl;
            break;

        case E_FLOTANTE:
            cout << "Es un flotante" << endl;
            break;

        case E_NOTA_CIEN:
            cout << "Es un flotante en notacion cientifica" << endl;
            break;

        case E_IDENT:
            cout << "Es un identificador" << endl;
            break;

        case E_OP_ARIT:
            cout << "Es un operador aritmetico" << endl;
            break;

        default:
            cout << "Error: no se identifico la entrada" << endl;
        }
    }

    return 0;
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: t
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 noexpandtab:
 * :indentSize=8:tabSize=8:noTabs=false:
 */
