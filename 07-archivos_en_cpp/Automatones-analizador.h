#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include <iostream>
#include <string>
#include <cctype>
#include <set>

using namespace std;

set<string> reservadas = {
"int","float","double","char","if","else","while","for",
"return","void","switch","case","break","continue","do"
};

bool esIdentificador(string s)
{
    if(!(isalpha(s[0]) || s[0]=='_'))
        return false;

    for(char c : s)
        if(!(isalnum(c) || c=='_'))
            return false;

    return true;
}

bool esOperador(string s)
{
    return s=="+" || s=="-" || s=="*" || s=="/" || s=="%" ||
           s=="=" || s=="++" || s=="--" || s=="==";
}

bool esDelimitador(char c)
{
    return c==';'||c==','||c=='('||c==')'||
           c=='{'||c=='}'||c=='['||c==']';
}

int analizaNumero(string s)
{
    int estado = 0;

    for(char c : s)
    {

        switch(estado)
        {

        case 0:
            if(isdigit(c)) estado=1;
            else if(c=='.') estado=3;
            else return -1;
        break;

        case 1:
            if(isdigit(c)) estado=1;
            else if(c=='.') estado=2;
            else if(c=='e'||c=='E') estado=5;
            else return -1;
        break;

        case 2:
            if(isdigit(c)) estado=4;
            else return -1;
        break;

        case 3:
            if(isdigit(c)) estado=4;
            else return -1;
        break;

        case 4:
            if(isdigit(c)) estado=4;
            else if(c=='e'||c=='E') estado=5;
            else return -1;
        break;

        case 5:
            if(c=='+'||c=='-') estado=6;
            else if(isdigit(c)) estado=7;
            else return -1;
        break;

        case 6:
            if(isdigit(c)) estado=7;
            else return -1;
        break;

        case 7:
            if(isdigit(c)) estado=7;
            else return -1;
        break;

        }

    }

    if(estado==1) return 1;
    if(estado==4) return 2;
    if(estado==7) return 3;

    return -1;
}

#endif