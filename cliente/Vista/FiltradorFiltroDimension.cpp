#include "FiltradorFiltroDimension.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Consulta.h"

FiltradorFiltroDimension::FiltradorFiltroDimension(const Glib::ustring& filtro,
    const Glib::ustring& _valor) : FiltradorFiltro(filtro, _valor) {}

FiltradorFiltroDimension::~FiltradorFiltroDimension() {}


void FiltradorFiltroDimension::filtrar(Consulta& c) {
    c.agregarFiltro(getFiltro(), getValor());
}
