/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

/*
	Montes Medina 		220111526
	Limon Aranzazu 		220111773
	Asael Lozano		220112555
	Sandoval Placencia	220111748
*/

#include <iostream>
#include <string>

#include "LosLimoneros_estados.h"

using namespace std;

int analiza(string str)
{
	int estado = 0;

	for (char c : str) {
		switch (c) {
			case '+':
			case '-':
				switch (estado) {
					case E_INICIAL:
						estado = E_SIGNO;
						break;
					case E_NOTA_CIEN:
						estado = E_NOTA_CIEN;
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
					case E_NOTA_CIEN:
						estado = E_NOTA_CIEN; // final
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
					case E_FLOTANTE:
						estado = E_NOTA_CIEN;
						break;
					default:
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
		default:
			cout << "Error: no se identifico la entrada" << endl;
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

