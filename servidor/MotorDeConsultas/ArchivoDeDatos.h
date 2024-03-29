/*
 * ArchivoDeDatos.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef ARCHIVODEDATOS_H_
#define ARCHIVODEDATOS_H_

#include <string>
#include <fstream>
#include "Mutex.h"

typedef unsigned int Id_Registro;

/**
 * @class ArchivoDeDatos
 * Esta clase es la encargada de almacenar todo tipo de registros guardándolos
 * en disco, permitiendo acceder a estos a partir de su id de registro.
 */

class ArchivoDeDatos {
public:

	/**
	 * @brief Constructor que recibe la ruta del archivo de datos.
	 */
	ArchivoDeDatos(const std::string& ruta);
	virtual ~ArchivoDeDatos();

	/**
	 * @brief Obtiene el registro con numero "id" del archivo
	 * @param id identificador del registro a recuperar
	 * @return string que contiene el registro completo recuperado
	 */
	std::string obtenerRegistro(Id_Registro id);

	/**
	 * @brief Guarda el registro en el archivo
	 * @param registro que se almacenara en el archivo
	 * @return identificador del registro guardado
	 */
	Id_Registro guardarRegistro(const std::string& registro);

	/**
	 * @brief Retorna la cantidad de registros que estan guardados en el archivo.
	 * @return cantidad de registros actual.
	 */
	size_t cantidadRegistros() const;

	/**
	 * @brief Borra todo el contenido de los datos
	 */
	void borrarDatos();

private:
	/**
	 * @brief Lee un registro desde el argumento posicion y lo almacena en
	 * el otro argumento string reg.
	 * @param posicion "offset" donde comienza el registro en el archivoPrincipa
	 * @param reg string a donde se guardara el registro leido.
	 */
	void leerRegistro(const size_t& posicion, std::string& reg);

	/**
	 * @brief Inicializa los archivos utilizados de la Clase}}}}
	 */
	void inicilizarArchivos();

	/**
	 * @brief comprueba si la posicion es valida, si no arroja una excepcion.
	 * @throw ErrorArchivoCorrompido
	 */
	void posicionValida(size_t posicion);


	std::fstream _archivoPrincipal;
	std::fstream _posRelativas;
	Id_Registro _ultimoID;

	std::string _rutaArchivoPrin;
	std::string _rutaArchivoSec;

	Mutex _mutex;
};

#endif /* ARCHIVODEDATOS_H_ */
