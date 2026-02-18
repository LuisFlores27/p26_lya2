//Jose Ismael Gonzalez Cosme 220111522
//Aaron Alejandro Martinez Serrano 230120317
//Jesus Gerardo De la O Duran 230120115
//Karina Guadalupe Munoz Avila 230120315

#include <iostream>
#include <string>

#include "estados_Los_Venecos.h"

using namespace std;

int analiza(string str)
{
    int estado = E_INICIAL;

    for (char c : str) {

        switch (c) {

        case '+':
        case '-':
            if (estado == E_INICIAL) {
                estado = E_SIGNO;
            }
            else if (estado == E_EXP) {
                estado = E_EXP_SIGNO;
            }
            else {
                return E_ERROR;
            }
            break;

        case '.':
            if (estado == E_ENTERO) {
                estado = E_PUNTO;
            }
            else if(estado == E_INICIAL || estado == E_SIGNO){
                estado = E_PUNTO;
            }
            else {
                return E_ERROR;
            }
            break;

        case 'e':
        case 'E':
            if (estado == E_ENTERO || estado == E_FLOTANTE) {
                estado = E_EXP;
            }
            else {
                return E_ERROR;
            }
            break;

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':

            if (estado == E_INICIAL || estado == E_SIGNO) {
                estado = E_ENTERO;
            }
            else if (estado == E_ENTERO) {
                estado = E_ENTERO;
            }
            else if (estado == E_PUNTO) {
                estado = E_FLOTANTE;
            }
            else if (estado == E_FLOTANTE) {
                estado = E_FLOTANTE;
            }
            else if (estado == E_EXP || estado == E_EXP_SIGNO) {
                estado = E_NOTA_CIEN;
            }
            else if (estado == E_NOTA_CIEN) {
                estado = E_NOTA_CIEN;
            }
            else {
                return E_ERROR;
            }
            break;

        default:
            return E_ERROR;
        }
    }

    return estado;
}

int main()
{
    string cadena;
    cin >> cadena;

    int estado_final = analiza(cadena);

    switch (estado_final) {

    case E_ENTERO:
        cout << "Es un entero" << endl;
        break;

    case E_FLOTANTE:
        cout << "Es un flotante" << endl;
        break;

    case E_NOTA_CIEN:
        cout << "Es un numero en notacion cientifica" << endl;
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
