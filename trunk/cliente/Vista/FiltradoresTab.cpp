#include "FiltradoresTab.h"
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/spinner.h>
#include <gtkmm/separator.h>
#include "Organizacion.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Filtrador.h"
#include "FiltradorInputDimension.h"
#include "FiltradorInputFecha.h"
#include "FiltradorInputHecho.h"

#define EXCEP_MSJ_INPUT_MAL     "El campo solicitado para el input no es dimensión ni hecho"

FiltradoresTab::FiltradoresTab() {}

FiltradoresTab::~FiltradoresTab() {
    std::list< Filtrador* >::iterator it = filtradores.begin();
    for ( ; it != filtradores.end(); ++it)
        delete *it;
}

void FiltradoresTab::agregarEntrada(const std::string& entrada) {
    FiltradorInput* f;
    try {
        if (Organizacion::esDimension(entrada)) {
            if (Organizacion::esDimensionEspecial(entrada))
                f = new FiltradorInputFecha(entrada);
            else{
                f = new FiltradorInputDimension(entrada);
                filtrosConsultantes.push((FiltradorInputDimension* ) f);
            }
        } else {
            if (Organizacion::esHecho(entrada))
                f = new FiltradorInputHecho(entrada);
            else
                throw ExcepcionFiltradorMalConstruido(EXCEP_MSJ_INPUT_MAL);
        }
        add(*f);
        filtradores.push_back(f);
        filtrosNavegables.push(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresTab::filtrar(Consulta& c) {
    std::list< Filtrador* >::iterator it = filtradores.begin();
    for ( ; it != filtradores.end(); ++it)
        (*it)->filtrar(c);
}

bool FiltradoresTab::tieneFiltrosNavegables() {
    return !filtrosNavegables.empty();
}

bool FiltradoresTab::tieneFiltrosConsultantes() {
    return !filtrosConsultantes.empty();
}

FiltradorInput* FiltradoresTab::getFiltroNavegable() {
    FiltradorInput* f = filtrosNavegables.front();
    filtrosNavegables.pop();
    return f;
}

FiltradorInputDimension* FiltradoresTab::getFiltroConsultante() {
    FiltradorInputDimension* f = filtrosConsultantes.front();
    filtrosConsultantes.pop();
    return f;
}