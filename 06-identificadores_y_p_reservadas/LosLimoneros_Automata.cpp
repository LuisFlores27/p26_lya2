/*
	Montes Medina 		220111526
	Limon Aranzazu 		220111773
	Asael Lozano		220112555
	Sandoval Placencia	220111748
*/

#include <iostream>
#include <string>
#include <cctype>

#include "LosLimoneros_estados.h"

using namespace std;

int analiza(string str)
{
	int estado = 0;
	
	if (str == "for") return E_RESERVADA;
	if (str == "do") return E_RESERVADA;
	if (str == "while") return E_RESERVADA;
	if (str == "if") return E_RESERVADA;
	if (str == "int") return E_RESERVADA;
	if (str == "float") return E_RESERVADA;
	if (str == "case") return E_RESERVADA;
	if (str == "switch") return E_RESERVADA;
	if (str == "class") return E_RESERVADA;

	for (char c : str) {
		switch (c) {
			// signos aritmeticos
			case '+': case '-': case '*': case '/': case '%':
				switch (estado) {
					case E_INICIAL:
						estado = E_SIGNO;
						break;
					case E_NOTA:
						estado = E_NOTA2;
						break; 
					default:
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
						estado = E_ENTERO; // final
						break;
					case E_PUNTO:
					case E_FLOTANTE:
						estado = E_FLOTANTE; // final
						break;
					case E_NOTA:
					case E_NOTA2:	
					case E_NOTA_CIEN:
						estado = E_NOTA_CIEN; // final
						break;
					case E_ID:
						estado = E_ID;
						break;
					default:
						estado = E_ERROR;
				}
				break;
			case '.':
				switch (estado){
					case E_ENTERO:
						estado = E_PUNTO;
						break;
					case E_INICIAL:
					case E_SIGNO:
						estado = E_ERROR;
						break;
					default:
						estado = E_ERROR;
				}
				break;
			case 'E':
			case 'e':
				switch (estado) {
					case E_ENTERO:
						estado = E_NOTA;
						break;
					case E_FLOTANTE:
						estado = E_NOTA;
						break;
					case E_INICIAL:
						estado = E_ID;
					default:
						estado = E_ERROR;
				}
				break;
			default:
				if (isalpha(c) || c == '_') { // reconocer ID cualquier letra
				// cout << "isalpha " <<endl;
					switch (estado) {
						case E_INICIAL:
							estado = E_ID;
							break;
						case E_ID:
							estado = E_ID;
							break;
						default:
							estado = E_ERROR;
					}
					break;
				}
				else {
					estado = E_ERROR;
				}
				break;
		}
	}
	return estado;
}

int main (int argc, char *argv[])
{
	int estado_final = E_ERROR;
	string cadena;

	cin >> cadena;

	estado_final = analiza(cadena);
	// cout << "Estado alcanzado: " << estado_final << endl;

	switch(estado_final) {
		case E_SIGNO:
			cout << "Es un signo" << endl;
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
		case E_ID:
			cout << "Es un identificador " << endl;
			break;
		case E_RESERVADA:
			cout << "Es una palabra reservada " << endl;
			break;
		default:
			cout << "Error: no se identifico la entrada " << endl;
			break;
	}

	return 0;
}

