#ifndef ESTADOS_PALABRAS_H
#define ESTADOS_PALABRAS_H
#define E_INICIAL    0   // Estado de inicio
#define E_SIGNO      1   // Después de +/-
#define E_ENTERO     2   // [Aceptación] Número entero
#define E_PUNTO      3   // Después del punto decimal '.'
#define E_FLOTANTE   4   // [Aceptación] Número decimal
#define E_EXP        5   // Después de 'e' o 'E'
#define E_EXP_SIGNO  6   // Después de +/- en el exponente
#define E_NOTA_CIEN  7   // [Aceptación] Notación científica completa
#define E_MIN        8   // [Aceptación] Identificador (inicia minúscula)
#define E_MAY        9   // [Aceptación] Identificador (inicia mayúscula)
#define E_GUION      10  // [Aceptación] Identificador con guion bajo '_'
#define E_RES        11  // [Aceptación] Palabra Reservada

// Estado de error
#define E_ERROR      -1

#endif