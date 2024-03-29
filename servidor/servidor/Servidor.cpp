#include "Servidor.h"
#include <iostream>
#include <fstream>
#include "Organizacion.h"
#define RSERVIDOR "servidor.config"
using namespace std;

Respuesta Servidor::resolverEntrada(Consulta& entrada) {
	if (vde.verificarEntrada(entrada)) {
		Respuesta r = bdd->agregarEntrada(entrada);
		r.definirID(entrada.devolverID());
		return r;
	}
	// TODO: al integrar, habria que reformular esto
	return Respuesta(Respuesta::mensajeError);
}

Respuesta Servidor::resolver(Consulta& consulta) {
	if (vdc.verificarConsulta(consulta)) {
	   	Respuesta r = bdd->resolverConsulta(consulta);
		r.definirID(consulta.devolverID());
		return r;
	}
	// TODO: al integrar, habria que reformular esto
	return Respuesta(Respuesta::mensajeError);
}

bool Servidor::funcional() {
	return cds.activo();
}

Servidor::Servidor(Puerto cliente, Puerto agente): cds(*this, *this,
													cliente, agente) {
	Organizacion::cargarDefiniciones(RUTA_ARCH_MODELO);
	//generarRegistros(bdd, 1000);

	bdd = new BaseDeDatos("BDD.dat");

	cds.comenzar();
}

Servidor::~Servidor() {
	cds.detener();

	delete bdd;
}
