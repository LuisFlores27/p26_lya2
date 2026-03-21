/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * FilaDos
 * Carlos Emiliano Rodriguez Gonzalez	210111197
 * Fabian Ramzes Maciaz Rodriguez		230120563
 * Diego Javier De Avila Alvarez		230120116
 * Jonathan Joel Galaviz Arroyo			230120487
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

#include "estadosFilaDos.h"

using namespace std;

/*int analizaf(string str)
{
	int estado = 0;

	for (char c : str) {
		switch (c) {
			case '+':
			case '-':
				if (estado == E_INICIAL) {
					estado = E_SIGNO;
				}
				else {
					estado = E_ERROR;
				}
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				switch (estado) {
					case E_INICIAL:
					case E_SIGNO:
					case E_ENTERO:
						estado = E_ENTERO;
						break;
					case E_FLOTANTE:
						estado = E_FLOTANTE;
						break;
					case E_NOTA_CIEN:
						estado = E_NOTA_CIEN;
						break;
					default:
						estado = E_ERROR;
						break;
				}
				break;
			case '.':
				switch (estado) {
					case E_INICIAL:
					case E_SIGNO:
					case E_ENTERO:
						estado = E_FLOTANTE;
						break;
					default:
						estado = E_ERROR;
						break;
				}
				break;
			case 'e':
				switch (estado) {
					case E_ENTERO:
					case E_FLOTANTE:
						estado = E_NOTA_CIEN;
						break;
					default:
						estado = E_ERROR;
				}
				break;
			case '*':
			case '/':
				if (estado == E_INICIAL) {
					estado = E_ARITM;
				}
				else {
					estado = E_ERROR;
				}
				break;
			case '_':
				switch (estado) {
					case E_INICIAL:
					case E_MINUS:
					case E_MAYUS:
					case E_GUION:
						estado = E_GUION;
						break;
					default:
						estado = E_ERROR;
				}
				break;
		}
		if (c>='a' && c<='z'){
			switch (estado) {
				case E_INICIAL:
				case E_MINUS:
				case E_MAYUS:
				case E_GUION:
					estado = E_MINUS;
					break;
				default:
					estado = E_ERROR;
				}
		}
		if (c>='A' && c<='Z'){
			switch (estado) {
				case E_INICIAL:
				case E_MINUS:
				case E_MAYUS:
				case E_GUION:
					estado = E_MAYUS;
					break;
				default:
					estado = E_ERROR;
				}
		}
	}
	if (str=="int" || str=="char" ||str=="bool"){
		estado = E_RESERV;
	}
	return estado;
}*/

int analiza(string str)
{
	int estado = 0;
	for (char c : str) {
		switch (c) {
			case ' ':
				estado = E_INICIAL;
				cout << endl;
				break;
			case '+':
			case '-':
				switch (estado) {
					case E_INICIAL:
						estado = E_SIGNO;
						cout <<c<<" es un signo indicativo o aritmetico"<<endl;
						break;
					case E_ENTERO:
					case E_FLOTANTE:
					case E_NOTA_CIEN:
						estado = E_ARITM;
						cout <<c<<" es un signo aritmetico"<<endl;
						break;
					default:
						estado = E_SIMBOL;
						cout <<c<<" es un simbolo"<<endl;
						break;
				}
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				switch (estado) {
					case E_INICIAL:
					case E_SIGNO:
					case E_ENTERO:
					case E_SIMBOL:
						estado = E_ENTERO;
						cout <<c<<" es un entero"<<endl;
						break;
					case E_FLOTANTE:
						estado = E_FLOTANTE;
						cout <<c<<" es un flotante"<<endl;
						break;
					case E_NOTA_CIEN:
						estado = E_NOTA_CIEN;
						cout <<c<<" es parte de notacion cientifica"<<endl;
						break;
					default:
						break;
				}
				break;
			case '.':
				switch (estado) {
					case E_INICIAL:
					case E_SIGNO:
					case E_ENTERO:
						estado = E_FLOTANTE;
						cout <<c<<" es un indicio de flotante"<<endl;
						break;
					default:
						estado = E_PUNTU;
						cout <<c<<" es un signo de puntuaciion"<<endl;
						break;
				}
				break;
			case 'e':
				switch (estado) {
					case E_ENTERO:
					case E_FLOTANTE:
						estado = E_NOTA_CIEN;
						cout <<c<<" es un indicio de notacion cientifica"<<endl;
						break;
					default:
						estado = E_MINUS;
						cout <<c<<" es una letra minuscula"<<endl;
						break;
				}
				break;
			case '*':
			case '/':
				switch (estado){
					case E_ENTERO:
					case E_FLOTANTE:
					case E_NOTA_CIEN:
						estado = E_ARITM;
						cout <<c<<" es un signo aritmetico"<<endl;
						break;
					default:
						estado = E_SIMBOL;
						cout <<c<<" es un simbolo"<<endl;
						break;
				}
				break;
			case '_':
				switch (estado) {
					case E_INICIAL:
					case E_MINUS:
					case E_MAYUS:
					case E_GUION:
						estado = E_GUION;
						cout <<c<<" es un guion bajo"<<endl;
						break;
					default:
						break;
				}
				break;
			case '#':
			case '<':
			case '>':
			case '(':
			case ')':
			case '{':
			case '}':
			case '[':
			case ']':
			case '!':
				estado = E_SIMBOL;
				cout <<c<<" es un simbolo"<<endl;
				break;
			case ';':
			case ':':
			case ',':
				estado = E_PUNTU;
				cout <<c<<" es un signo de puntuaciion"<<endl;
				break;
		}
		if (c>='a' && c<='z' && c!='e'){
			switch (estado) {
				default:
					estado = E_MINUS;
					cout <<c<<" es una letra minuscula"<<endl;
					break;
			}
		}
		if (c>='A' && c<='Z'){
			switch (estado) {
				default:
					estado = E_MAYUS;
					cout <<c<<" es una letra mayuscula"<<endl;
					break;
			}
		}
	}
	return estado;
}

bool esPalabraReservada(const string& palabra) {
	static const set<string> palabrasReservadas = {
		"break", "case", "char", "const", "do", "double", "else", "float", "for",
		"if", "int", "return", "ifstream", "#include", "switch", "while"
	};
	return palabrasReservadas.find(palabra) != palabrasReservadas.end();
}

//string res[] = {"#include", "iostream", "fstream", "string,", "using", ""};

int main (int argc, char *argv[])
{
	if (argc < 2) {
		cerr << "Error: no hay suficientes argumentos" << endl;
		return 1;
	}

	string nombreArchivo = argv[1];
	ifstream archivo(nombreArchivo); // Intentamos abrir el archivo

	// Comprobamos si el archivo se abrió correctamente
	if (!archivo.is_open()) {
		cerr << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'" << endl;
		return 1;
	}

	string linea;
	string palabra;

	while(getline(archivo,linea)) {
		stringstream ss(linea);
		analiza(linea);
		while (ss >> palabra) {
			if (esPalabraReservada(palabra)) {
				cout << palabra << " es reservada" << endl << endl;
			}
		}
		cout << linea << endl<< endl;
		
	}
	archivo.close();
	
	/*int estado_final = E_ERROR;
	string cadena;

	cin >> cadena;

	estado_final = analizaf(cadena);

	switch(estado_final) {
		case E_SIGNO:
			cout << "Es un signo y es aritmetico" << endl;
			break;
		case E_ENTERO:
			cout << "Es un entero" << endl;
			break;
		case E_FLOTANTE:
			cout << "Es un flotante" << endl;
			break;
		case E_NOTA_CIEN:
			cout << "Es un flotante en notación cientifica" << endl;
			break;
		case E_ARITM:
			cout << "Es un signo aritmetico" << endl;
			break;
		case E_GUION:
			cout << "Es un guion" << endl;
			break;
		case E_MINUS:
			cout << "Es una letra minuscula" << endl;
			break;
		case E_MAYUS:
			cout << "Es una letra mayuscula" << endl;
			break;
		case E_RESERV:
			cout << "Es una palabra reservada" << endl;
			break;
		default:
			cout << "Error: no se identifico la entrada" << endl;
	}*/

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

