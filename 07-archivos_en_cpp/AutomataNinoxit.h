/*
    Equipo Ninoxit
    Soely Mayomi Camacho Camacho
    Daniela Ivette Nava Miranda
*/
#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include <string>
#include <stack>

#define E_ERROR             0xFFFF
#define E_INICIAL           0
#define E_SIGNO             1
#define E_ENTERO            2
#define E_FLOTANTE          4
#define E_NOTA_CIEN         7
#define E_IDENTIFICADOR     10
#define E_ARITMETICO        11
#define E_RESERVADA         12
#define E_PUNTO             13
#define E_SEPARADOR         20
#define E_COMENTARIO        21
#define E_PREPROCESADOR     22
#define E_FUNCION           23
#define E_CADENA            24


bool        checker(const std::string& word, const std::string base);
int         analizador(const std::string& cadena);
std::string nombreEstado(int estado);
void        tokenizar(const std::string& linea, int numLinea, std::stack<std::string>& pila);

#endif