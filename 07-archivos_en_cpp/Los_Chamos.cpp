/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

// Jose Jaime Nuñez Vazquez NC: 230120398
// Eliand Andres Murillo Ramos NC: 23012470
// Luis Angel Flores Espinosa NC: 210110157
// Juan Roberto Aguilar Molina NC: 210110268

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "estados_Los_Chamos.h"

using namespace std;

bool esReservada(string str)
{
    string reservadas[] = {
        "int","float","double","char","bool",
        "if","else","while","for","return",
        "using","namespace","include",
        "true","false"
    };

    for(string r : reservadas)
        if(str == r)
            return true;

    return false;
}

int analiza(string str)
{
    int estado = E_INICIAL;

    for(char c : str)
    {

        switch(c)
        {

        case '+':
        case '-':
            if(str.length() == 1)
                return E_OP_ARIT;

            if(estado == E_INICIAL)
                estado = E_SIGNO;

            else if(estado == E_EXP)
                estado = E_EXP_SIGNO;

            else
                return E_ERROR;

            break;


        case '*':
        case '/':
        case '%':
            if(str.length() == 1)
                return E_OP_ARIT;
            else
                return E_ERROR;


        case '.':
            if(estado == E_ENTERO)
                estado = E_PUNTO;
            else
                return E_ERROR;
            break;


        case 'e':
        case 'E':

            if(estado == E_ENTERO || estado == E_FLOTANTE)
            estado = E_EXP;

            else if(estado == E_IDENT)
                estado = E_IDENT;

            else if(estado == E_INICIAL)
                estado = E_IDENT;

            else
        return E_ERROR;

            break;

        default:

            if(isdigit(c))
            {

                if(estado == E_INICIAL || estado == E_SIGNO)
                    estado = E_ENTERO;

                else if(estado == E_ENTERO)
                    estado = E_ENTERO;

                else if(estado == E_PUNTO)
                    estado = E_FLOTANTE;

                else if(estado == E_FLOTANTE)
                    estado = E_FLOTANTE;

                else if(estado == E_EXP || estado == E_EXP_SIGNO)
                    estado = E_NOTA_CIEN;

                else if(estado == E_NOTA_CIEN)
                    estado = E_NOTA_CIEN;

                else if(estado == E_IDENT)
                    estado = E_IDENT;

                else
                    return E_ERROR;
            }

            else if(isalpha(c) || c == '_')
            {

                if(estado == E_INICIAL)
                    estado = E_IDENT;

                else if(estado == E_IDENT)
                    estado = E_IDENT;

                else
                    return E_ERROR;
            }

            else
                return E_ERROR;

            break;
        }
    }

    return estado;
}

//CLASIFICAR TOKEN

void clasificarToken(string token)
{

    if(token.empty())
        return;

    if(token == "#include")
    {
        cout << token << " -> directiva preprocesador\n";
        return;
    }

    if(esReservada(token))
    {
        cout << token << " -> palabra reservada\n";
        return;
    }

    int estado = analiza(token);

    switch(estado)
    {

    case E_ENTERO:
        cout << token << " -> entero\n";
        break;

    case E_FLOTANTE:
        cout << token << " -> flotante\n";
        break;

    case E_NOTA_CIEN:
        cout << token << " -> notacion cientifica\n";
        break;

    case E_IDENT:
        cout << token << " -> identificador\n";
        break;

    case E_OP_ARIT:
        cout << token << " -> operador aritmetico\n";
        break;

    default:
        cout << token << " -> token no reconocido\n";
    }
}

//ANALIZAR LINEA

void analizarLinea(string linea)
{
    string token="";

    for(size_t i=0;i<linea.size();i++)
    {
        char c = linea[i];

        /* espacios */

        if(isspace(c))
        {
            clasificarToken(token);
            token="";
            continue;
        }

        /* comentarios */

        if(c=='/' && i+1 < linea.size() && linea[i+1]=='/')
        {
            clasificarToken(token);
            token="";

            string comentario = linea.substr(i);

            cout << comentario << " -> comentario\n";

            break;
        }

        /* delimitadores */

        if(c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']'||c==';'||c==',')
        {
            clasificarToken(token);
            token="";

            cout << c << " -> delimitador\n";
            continue;
        }

        /* operadores */

        if(c=='+'||c=='-'||c=='*'||c=='/'||c=='='||
           c=='<'||c=='>'||c=='%'||c=='.'||c=='!')
        {
            clasificarToken(token);
            token="";

            string op(1,c);

            if(i+1 < linea.size())
            {
                char sig = linea[i+1];

                if((c=='<' && sig=='<') ||
                   (c=='>' && sig=='>') ||
                   (c=='=' && sig=='=') ||
                   (c=='!' && sig=='='))
                {
                    op+=sig;
                    i++;
                }
            }

            cout << op << " -> operador\n";
            continue;
        }

        /* strings */

        if(c=='"')
        {
            clasificarToken(token);
            token="";

            string cadena="\"";
            i++;

            while(i<linea.size() && linea[i]!='"')
            {
                cadena+=linea[i];
                i++;
            }

            cadena+="\"";

            cout << cadena << " -> cadena\n";
            continue;
        }

        /* directivas */

        if(c=='#')
        {
            clasificarToken(token);
            token="";

            string dir="#";
            i++;

            while(i<linea.size() && !isspace(linea[i]))
            {
                dir+=linea[i];
                i++;
            }

            cout << dir << " -> directiva\n";
            continue;
        }

        token+=c;
    }

    clasificarToken(token);
}


int main(int argc, char *argv[])
{

    if(argc < 2)
    {
        cerr << "Error: no hay suficientes argumentos\n";
        return 1;
    }

    string nombreArchivo = argv[1];

    ifstream archivo(nombreArchivo);

    if(!archivo.is_open())
    {
        cerr << "Error: no se pudo abrir el archivo\n";
        return 1;
    }

    string linea;

    while(getline(archivo,linea))
    {
        analizarLinea(linea);
    }

    archivo.close();

    return 0;
}