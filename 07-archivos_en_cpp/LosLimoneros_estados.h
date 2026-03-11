#ifndef _ESTADOS_H_
#define _ESTADOS_H_

#define E_ERROR   0xFFFF

#define E_INICIAL   	0
#define E_MAS_MENOS     1 // final
#define E_ENTERO    	2 // final
#define E_PUNTO     	3
#define E_FLOTANTE  	4 // final

#define E_NOTA      	5
#define E_NOTA2     	6 //SIGNO DE NOTACION CIENTIFICA
#define E_NOTA_CIEN 	7 // final (COMEPLETO)

#define E_ID        	8 // final

#define E_GATO			9 // (#)
#define E_INCLUDE		16 // final (#include)
#define E_OPERADOR 		10 // final

#define E_COMILLA     	11
#define E_COMILLA_F    	12 //final string

#define E_COMENT     	13
#define E_COMENT2     	14
#define E_COMENT_F     	15 // final comentario
#define E_RESERVADA		17 // final palabra resrvada

#endif

