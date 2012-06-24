/*
 * GenRegistros.h
 *
 *  Created on: 07/06/2012
 *      Author: migue
 */

#ifndef GENREGISTROS_H_
#define GENREGISTROS_H_
#include <stdlib.h>
#include <string>
#include "../servidor/MotorDeConsultas/BaseDeDatos.h"
#include "../comun/Organizacion.h"
#include "../comun/Utilitario.h"

int generarRandom (int cantMax);

void generarRegistros(BaseDeDatos& bdd, long cantReg);

#endif /* GENREGISTROS_H_ */