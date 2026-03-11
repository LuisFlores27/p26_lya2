/*
	Montes Medina 		220111526
	Limon Aranzazu 		220111773
	Asael Lozano		220112555
	Sandoval Placencia	220111748
*/

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

#include "LosLimoneros_estados.h"

using namespace std;

int analiza(string str)
{
	int estado = 0;
	
	string reservadas[] = {
		"alignas","alignof","and","and_eq","asm","atomic_cancel","atomic_commit",
		"atomic_noexcept","auto","bitand","bitor","bool","break","case","catch",
		"char","char8_t","char16_t","char32_t","class","compl","concept","const",
		"consteval","constexpr","constinit","const_cast","continue","co_await",
		"co_return","co_yield","decltype","default","delete","do","double",
		"dynamic_cast","else","enum","explicit","export","extern","false","float",
		"for","friend","goto","if","inline","int","long","mutable","namespace",
		"new","noexcept","not","not_eq","nullptr","operator","or","or_eq",
		"private","protected","public","register","reinterpret_cast","requires",
		"return","short","signed","sizeof","static","static_assert","static_cast",
		"struct","switch","synchronized","template","this","thread_local","throw",
		"true","try","typedef","typeid","typename","union","unsigned","using",
		"virtual","void","volatile","wchar_t","while","xor","xor_eq"
	};
	
	string include = "";
	
	for (char c : str) {
		switch (c) {
			
			case '+': case '-':
				switch (estado){
					case E_INICIAL:
						estado = E_MAS_MENOS;
						break;
					case E_NOTA: 
						estado = E_NOTA2;
						break;
					default:
						estado = E_ERROR;
						break;
				}
				break;
			
			case '.':
				switch(estado){
					case E_ENTERO: case E_INICIAL:
						estado = E_PUNTO;
						break;
					default:
						estado = E_ERROR;
						break;
				}
				break;
				
			case 'e': case 'E':
				switch(estado){
					case E_ENTERO: case E_FLOTANTE:
						estado = E_NOTA;
						break;
						
					case E_ID:        // <- agregar esto
			            estado = E_ID;
			            break;
			            
					default:
						estado = E_ERROR;
						break;
				}		
				break;
				
			case '#':
			    switch(estado){
			        case E_INICIAL:
			            include = "#";  // se inicia la palabra
			            estado = E_GATO;
			            break;
			        default:
			            estado = E_ERROR;
			            break;
			    }
			    break;
			
			case '*': case '%': case '=': case ';': case ',': case '(': case ')':
			case '{': case '}': case '<': case '>': case '[': case ']':	
				switch (estado){
					case E_INICIAL:
						estado = E_OPERADOR;
						break;
					default:
						estado = E_ERROR;
						break;
				}
				break;
				
			case '"':
				switch(estado){
					case E_INICIAL:
						estado = E_COMILLA;
						break;
					case E_COMILLA:
						estado = E_COMILLA_F;
						break;
					default:
						estado = E_ERROR;
						break;
				}
				break;
				
			case '/':
				switch(estado){
					case E_INICIAL:
						estado = E_COMENT;
						break;
					case E_COMENT:
						estado = E_COMENT2;
						break;
					default:
						estado = E_ERROR;
						break;
				}
				break;
			case '\n':
				switch(estado){
					case E_COMENT2:
						estado = E_COMENT_F;
						break;
					default:
						estado = E_ERROR;
						break;	
				}
		}
		
		if (isdigit(c)){
			switch (estado){
				case E_INICIAL: case E_MAS_MENOS: case E_ENTERO:
					estado = E_ENTERO;
					break;
				case E_PUNTO: case E_FLOTANTE:
					estado = E_FLOTANTE;
					break;
				case E_NOTA: case E_NOTA2:
					estado = E_NOTA_CIEN;
					break;
			}
		}
		
		if (isalpha(c) || c == '_'){
			switch(estado){
				case E_INICIAL:
					estado = E_ID;
					break;
				case E_GATO:
					include += c;
					if (include == "#include") estado = E_INCLUDE;
					break;
			}
		}
		
		if (isalnum(c) || c == '_'){
			switch(estado){
				case E_ID:
					estado = E_ID;
					break;
			}
		}
		
		
		
	}
	return estado;
}

void imprimirResultado(string token, int estado_final)
{
	cout << "Token: " << token << endl;

	switch(estado_final) {
		case E_MAS_MENOS:
			cout << "Es un signo" << endl;
			break;
		case E_ENTERO:
			cout << "Es un entero" << endl;
			break;
		case E_FLOTANTE:
			cout << "Es un flotante" << endl;
			break;
		case E_NOTA_CIEN:
			cout << "Es Notacion Cientifica" << endl;
			break;
		case E_INCLUDE:
			cout << "Es #include" << endl;
			break;
		case E_ID:
			cout << "Es un identificador" << endl;
			break;
		case E_OPERADOR:
			cout << "Es un operador" << endl;
			break;
		case E_COMILLA_F:
			cout << "string" << endl;
			break;
		default:
			cout << "Error: no se identifico la entrada" << endl;
			break;
	}

	cout << endl;
}

int main (int argc, char *argv[])
{
	if (argc < 2){
		cout << "Uso: ./programa archivo.txt\n";
		return 1;
	}

	ifstream file(argv[1]);

	if (!file){
		cout << "No se pudo abrir el archivo\n";
		return 1;
	}

	string cadena;

	char c;
string token = "";

	while (file.get(c)) {
	
	    // separadores de tokens
	    if (isspace(c)) {
	        if (!token.empty()) {
	            int estado_final = analiza(token);
	            imprimirResultado(token, estado_final);
	            token = "";
	        }
	        continue;
	    }
	
	    // operadores individuales
	    if (ispunct(c) && c != '_') {

		    if (!token.empty()) {
		        int estado_final = analiza(token);
		        imprimirResultado(token, estado_final);
		        token = "";
		    }
		
		    string op(1, c);
		    int estado_final = analiza(op);
		    imprimirResultado(op, estado_final);
		
		    continue;
		}
	
	    // construir token
	    token += c;
	}

	file.close();
	return 0;
}

