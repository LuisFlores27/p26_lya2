/*
Equipo Ninoxit
Soely Mayomi Camacho Camacho
Daniela Ivette Nava Miranda
*/
#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include <string>

#define E_ERROR         0xFFFF
#define E_INICIAL       0
#define E_SIGNO         1
#define E_ENTERO        2
#define E_FLOTANTE      4
#define E_NOTA_CIEN     7
#define E_IDENTIFICADOR 10
#define E_ARITMETICO    11
#define E_RESERVADA     12
#define E_PUNTO         13

bool checker(const std::string& word, const std::string base);
int analizador(const std::string& cadena);

#endif