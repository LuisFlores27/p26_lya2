/* SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <iostream>

#include "suma_LosLimoneros.h"
#include "resta_LosLimoneros.h"
#include "multiplicacion_LosLimoneros.h"
#include "division_LosLimoneros.h"

using namespace std;

int main (int argc, char *argv[])
{
  cout << "3 + 5 = "<< suma(3,5) << endl;
  cout << "3 - 5 = "<< resta(3,5) << endl;
  cout << "3 * 5 = "<< multiplicacion(3,5) << endl;
  cout << "3 / 5 = "<< division(3,5) << endl;

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

