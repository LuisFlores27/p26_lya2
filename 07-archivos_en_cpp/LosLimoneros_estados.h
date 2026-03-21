#ifndef _ESTADOS_H_
#define _ESTADOS_H_
//corregido
#define E_ERROR         0xFFFF

#define E_INICIAL       0
#define E_MAS_MENOS     1  // final (Signos + o -)
#define E_ENTERO        2  // final (Números enteros)
#define E_PUNTO         3  // final (Punto decimal o selector '.')
#define E_FLOTANTE      4  // final (Números con decimales)


#define E_NOTA          5  // Aparece la 'e' o 'E'
#define E_NOTA2         6  // Aparece el signo en el exponente
#define E_NOTA_CIEN     7  // final (Número científico completo)


#define E_ID            8  // final (Variables y nombres)
#define E_RESERVADA     15 // final (int, while, if, return, etc.)


#define E_GATO          9  // Símbolo '#' inicial
#define E_INCLUDE       16 // final (Palabra completa #include)
#define E_OPERADOR      10 // final (Símbolos como *, +, =, ;, etc.)


#define E_COMILLA       11 // Inicio de comillas
#define E_COMILLA_F     12 // final (String cerrado con comillas)

#define E_COMENT        13 // Primera diagonal '/'
#define E_COMENT2       14 // final (Comentario de línea //)
#define E_COMENT_F      17 // final (Estado de cierre de comentario)

#endif // Fin de _ESTADOS_H_
