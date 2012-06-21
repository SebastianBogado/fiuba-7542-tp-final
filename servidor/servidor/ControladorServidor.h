#ifndef __CONTROLADOR_H
#define __CONTROLADOR_H

//#include "BLQueue.h"
//#include "BLMap.h"
#include <utility>
#include <list>
#include "ClienteRemoto.h"
#include "AgenteRemoto.h"
#include "ContenedorAgentes.h"
#include "ContenedorClientes.h"
#include "ResolvedorConsultas.h"
#include "ResolvedorEntradas.h"
#include "Consulta.h"
#include "ThreadEntradaAgentes.h"
#include "ThreadEntradaClientes.h"
#include "Mutex.h"
#include <iostream>
#include "Definiciones.h"
#include "PoolClientes.h"
#include "PoolAgentes.h"
using namespace std;

class ControladorServidor:  public ResolvedorConsultas, 
							public ResolvedorEntradas,
							public ContenedorClientes,
							public ContenedorAgentes {
private:
	// atributos
	ConsultasAgentesServidor centradas;
	ConsultasClientesServidor cconsultas;
	typedef std::list<ClienteRemoto*> lclientes;
	typedef std::list<AgenteRemoto*> lagentes;
	unsigned int ncons;
	unsigned int nact;
	lclientes clientes;
	Puerto puerto_clientes;
	Puerto puerto_agentes;
	lagentes agentes;
	ResolvedorConsultas& rcons;
	ResolvedorEntradas& rentr;
	ThreadEntradaAgentes* tagentes;
	ThreadEntradaClientes* tclientes;
	PoolClientes poolclientes;
	PoolAgentes poolagentes;
	Mutex m;
public:
	Respuesta resolverEntrada(Consulta& entrada);
	Respuesta resolver(Consulta& consulta);
	ControladorServidor(ResolvedorConsultas& cons, ResolvedorEntradas& rent,
								Puerto pclientes, Puerto pagentes);
	~ControladorServidor();
	void agregarCliente(ClienteRemoto* rem);
	void agregarAgente(AgenteRemoto* agt);
	void comenzar();
	void detener();
};

#endif
