#include "automata_diosarrolladores.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
using namespace std;

bool esReservada(const string &str) {
  static const set<string> palabras = {
      "int", "float",  "double", "char",  "if",       "else",     "while",
      "for", "return", "class",  "using", "#include", "namespace"};
  return palabras.count(str) > 0;
}

int analiza(ifstream &archivo, string &lexema, int &linea) {
  char c;
  lexema = "";
  int estado = E_INICIAL;

  while (archivo.get(c)) {
    if (c == '\n') {
      linea++;
      if (estado != E_INICIAL) {
        if (estado == E_IDENTIFICADOR) {
          if (esReservada(lexema))
            return E_RESERVADA;
          return E_IDENTIFICADOR;
        }
        if (estado == E_ENTERO)
          return E_ENTERO;
        if (estado == E_FLOTANTE)
          return E_FLOTANTE;
        if (estado == E_NOTA_CIEN)
          return E_NOTA_CIEN;
      }
      continue;
    }

    if (estado == E_INICIAL && isspace(c))
      continue;

    if (estado != E_INICIAL && estado != E_CADENA_ACUM &&
        estado != E_COMENTARIO_ACUM && isspace(c)) {
      if (estado == E_IDENTIFICADOR) {
        if (esReservada(lexema))
          return E_RESERVADA;
        return E_IDENTIFICADOR;
      }
      if (estado == E_ENTERO)
        return E_ENTERO;
      if (estado == E_FLOTANTE)
        return E_FLOTANTE;
      if (estado == E_NOTA_CIEN)
        return E_NOTA_CIEN;
      return E_ERROR;
    }

    switch (estado) {
    case E_INICIAL:
      if (isalpha(c) || c == '_') {
        lexema = c;
        estado = E_IDENTIFICADOR;
      } else if (isdigit(c)) {
        lexema = c;
        estado = E_ENTERO;
      } else if (c == '"') {
        lexema = c;
        estado = E_CADENA_ACUM;
      } else if (c == '#') {
        lexema = c;
        while (archivo.get(c) && c != '\n')
          lexema += c;
        linea++;
        return E_DIRECTIVA;
      } else if (c == '/') {
        lexema = c;
        estado = E_COMENTARIO_ACUM;
      } else if (c == '+' || c == '-' || c == '*' || c == '%' || c == '=' ||
                 c == '<' || c == '>') {
        lexema = c;
        return E_ARITMETICO;
      }
      break;

    case E_IDENTIFICADOR:
      if (isalnum(c) || c == '_')
        lexema += c;
      else {
        archivo.unget();
        if (esReservada(lexema))
          return E_RESERVADA;
        return E_IDENTIFICADOR;
      }
      break;

    case E_ENTERO:
      if (isdigit(c)) {
        lexema += c;
      } else if (c == '.') {
        lexema += c;
        estado = E_FLOTANTE;
      } else if (c == 'e' || c == 'E') {
        lexema += c;
        estado = E_EXP_ESPERA;
      } else {
        archivo.unget();
        return E_ENTERO;
      }
      break;

    case E_FLOTANTE:
      if (isdigit(c)) {
        lexema += c;
      } else if (c == 'e' || c == 'E') {
        lexema += c;
        estado = E_EXP_ESPERA;
      } else {
        archivo.unget();
        return E_FLOTANTE;
      }
      break;

    case E_EXP_ESPERA:
      if (isdigit(c) || c == '+' || c == '-') {
        lexema += c;
        estado = E_NOTA_CIEN;
      } else {
        archivo.unget();
        return E_ERROR;
      }
      break;

    case E_NOTA_CIEN:
      if (isdigit(c))
        lexema += c;
      else {
        archivo.unget();
        return E_NOTA_CIEN;
      }
      break;

    case E_CADENA_ACUM:
      lexema += c;
      if (c == '"')
        return E_CADENA;
      break;

    case E_COMENTARIO_ACUM:
      if (c == '/') {
        lexema += c;
        while (archivo.get(c) && c != '\n')
          lexema += c;
        linea++;
        return E_COMENTARIO;
      } else if (c == '*') {
        lexema += c;
        char prev = 0;
        while (archivo.get(c)) {
          if (c == '\n')
            linea++;
          lexema += c;
          if (prev == '*' && c == '/')
            break;
          prev = c;
        }
        return E_COMENTARIO;
      } else {
        archivo.unget();
        lexema = "/";
        return E_ARITMETICO;
      }
      break;
    }
  }

  if (!lexema.empty()) {
    if (estado == E_IDENTIFICADOR) {
      if (esReservada(lexema))
        return E_RESERVADA;
      return E_IDENTIFICADOR;
    }
    if (estado == E_ENTERO)
      return E_ENTERO;
    if (estado == E_FLOTANTE)
      return E_FLOTANTE;
    if (estado == E_NOTA_CIEN)
      return E_NOTA_CIEN;
  }

  return E_EOF;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "No se proporciono archivo" << endl;
    return 1;
  }
  ifstream archivo(argv[1]);
  if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo" << endl;
    return 1;
  }

  string lexema;
  int linea = 1;
  int resultado;

  while ((resultado = analiza(archivo, lexema, linea)) != E_EOF) {
    cout << "linea " << linea << ": " << lexema << " -> ";
    switch (resultado) {
    case E_ENTERO:
      cout << "Numero entero" << endl;
      break;
    case E_FLOTANTE:
      cout << "Numero flotante" << endl;
      break;
    case E_NOTA_CIEN:
      cout << "Notacion cientifica" << endl;
      break;
    case E_IDENTIFICADOR:
      cout << "Identificador" << endl;
      break;
    case E_RESERVADA:
      cout << "Palabra reservada" << endl;
      break;
    case E_ARITMETICO:
      cout << "Operador" << endl;
      break;
    case E_DIRECTIVA:
      cout << "Directiva de preprocesador" << endl;
      break;
    case E_CADENA:
      cout << "Cadena" << endl;
      break;
    case E_COMENTARIO:
      cout << "Comentario" << endl;
      break;
    default:
      cout << "Error de lexico" << endl;
      break;
    }
  }

  archivo.close();
  return 0;
}

