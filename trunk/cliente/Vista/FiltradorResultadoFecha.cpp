#include "FiltradorResultadoFecha.h"
#include "FiltradorInputFecha.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Consulta.h"

FiltradorResultadoFecha::FiltradorResultadoFecha(const Glib::ustring& fecha,
    const Glib::ustring& _valorCombo, const Glib::ustring& _valorEntrada)
    : FiltradorResultado(fecha),
    valorCombo(_valorCombo), valorEntrada(_valorEntrada)  {
    /** @deprecated todo esto */
    i = FiltradorInputFecha::perteneceAlCombobox(valorCombo);
    if (i == NO_PERTENECE) {
        std::string msj = "No pertenece al conjunto de valores posibles: ";
        msj += valorCombo.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    f = FiltradorInputFecha::validar(i, valorEntrada);
    if (f == STR_NULA) {
        std::string msj = "Valor de entrada inválido: ";
        msj += valorEntrada.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    Glib::ustring label = valorCombo;
    label += " ";
    label += valorEntrada;
    setResultado(label);
}

FiltradorResultadoFecha::~FiltradorResultadoFecha() {}

void FiltradorResultadoFecha::filtrar(Consulta& c) {
    c.agregarResultado(getResultado());
}
