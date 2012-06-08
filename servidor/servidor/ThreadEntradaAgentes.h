#ifndef __THREADENTRADAAGENTES_H
#define __THREADENTRADAAGENTES_H

#include "Socket.h"
#include "ContenedorAgentes.h"
#include "ResolvedorEntradas.h"
#include "AgenteRemoto.h"
#include "Hilo.h"
#define PORT_AGENTE (Puerto) 12345

class ThreadEntradaAgentes: public Hilo {
private:
	Socket* entradaAgentes;
	ContenedorAgentes& ca;	
	ResolvedorEntradas& re;
public:

	// metodo que se queda pendiente de la conexion de nuevos agentes. 
	// Si llega un agente, crea un AgenteRemoto que procesa las consultas
	void correr();
	
	// Detiene la conexion de entrada de agentes. Desconecta, detiene y
	// sincroniza el hilo
	void detener_entrada();
	
	// constructor. Recibe un ContenedorAgentes valido y un ResolvedorEntradas.
	// El primero sera el que contenga todos los AgenteRemoto. El segundo
	// el que resuelva las entradas que reciba de cada AgenteRemoto
	ThreadEntradaAgentes(ContenedorAgentes& cag, ResolvedorEntradas& rent);
	
	// destructor. Detiene la entrada. Si sigue conectado, desconecta.
	~ThreadEntradaAgentes();
};

#endif