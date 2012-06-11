#include "FiltradorFiltroFecha.h"
#include "FiltradorInputFecha.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Consulta.h"

FiltradorFiltroFecha::FiltradorFiltroFecha(const Glib::ustring& fecha,
    const Glib::ustring& _valorCombo, const std::string& _valorEntrada)
    : FiltradorFiltro(fecha, ""),
    valorCombo(_valorCombo), valorEntrada(_valorEntrada) {
    i = FiltradorInputFecha::perteneceAlCombobox(valorCombo);
    if (i == NO_PERTENECE) {
        std::string msj = "No pertenece al conjunto de valores posibles: ";
        msj += valorCombo.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    if (!FiltradorInputFecha::esValido(valorEntrada)) {
        std::string msj = "Valor de entrada inválido: ";
        msj += valorEntrada.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    Glib::ustring label = valorCombo;
    label += " ";
    label += valorEntrada;
    setValor(label);
}

FiltradorFiltroFecha::~FiltradorFiltroFecha() {}

Consulta& FiltradorFiltroFecha::filtrar(Consulta& c) {
    std::cout << "@todo Consulta& FiltradorFiltroFecha::filtrar(Consulta& c)" << std::endl;
    return c;
}
