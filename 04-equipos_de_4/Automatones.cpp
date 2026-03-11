/* SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <iostream>

#include "suma_Automatones.h"
#include "resta_Automatones.h"
#include "multipliacion_Automatones.h"
#include "division_Automatones.h"

using namespace std;

int main (int argc, char *argv[])
{
 cout << "3 + 5 = "<< suma(3,5) << endl;
 cout << "3 - 5 = "<< resta(3,5) << endl;
 cout << "3 * 5 = "<< multipliacion(3,5) << endl;
 cout << "3 / 5 = "<< division(3,5) << endl;

  return 0;
}

