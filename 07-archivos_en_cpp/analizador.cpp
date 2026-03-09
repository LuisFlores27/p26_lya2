#include <iostream>
#include <fstream>
#include <string>
#include "analizador.h"

using namespace std;

int main()
{

    ifstream archivo("codigo.cpp");

    if(!archivo.is_open())
    {
        cout<<"No se pudo abrir el archivo"<<endl;
        return 1;
    }

    string linea;

    while(getline(archivo,linea))
    {

        // detectar comentario
        size_t posComentario = linea.find("//");

        if(posComentario != string::npos)
        {
            string comentario = linea.substr(posComentario);
            linea = linea.substr(0,posComentario);

            cout<<comentario<<" -> Comentario"<<endl;
        }

        string token="";

        for(int i=0;i<=linea.length();i++)
        {

            if(i==linea.length() || isspace(linea[i]) || esDelimitador(linea[i]))
            {

                if(!token.empty())
                {

                    if(token=="#include")
                        cout<<token<<" -> Directiva"<<endl;

                    else if(reservadas.count(token))
                        cout<<token<<" -> Palabra reservada"<<endl;

                    else if(esOperador(token))
                        cout<<token<<" -> Operador"<<endl;

                    else if(esIdentificador(token))
                        cout<<token<<" -> Identificador"<<endl;

                    else
                    {

                        int tipo = analizaNumero(token);

                        if(tipo==1)
                            cout<<token<<" -> Entero"<<endl;

                        else if(tipo==2)
                            cout<<token<<" -> Flotante"<<endl;

                        else if(tipo==3)
                            cout<<token<<" -> Notacion cientifica"<<endl;

                        else
                            cout<<token<<" -> Error"<<endl;

                    }

                    token="";
                }

                if(i<linea.length() && esDelimitador(linea[i]))
                    cout<<linea[i]<<" -> Delimitador"<<endl;

            }
            else
            {
                token+=linea[i];
            }

        }

    }

    archivo.close();

    return 0;
}