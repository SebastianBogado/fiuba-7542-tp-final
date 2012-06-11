#include "FiltradorInputFecha.h"

#define CANT_COMBO 8
Glib::ustring FiltradorInputFecha::valoresCombo[CANT_COMBO] = {
    "Año", "Mes", "Bimestre", "Trimestre", "Cuatrimestre", "Semestre",
    "Semana del año", "Dia" };

FiltradorInputFecha::FiltradorInputFecha(const Glib::ustring& input)
: FiltradorInput(input) {
    for (unsigned i = 0; i < CANT_COMBO; ++i)
        valores.append_text(valoresCombo[i]);

    centradorDerecho.pack_end(entrada, false, false);
}

FiltradorInputFecha::~FiltradorInputFecha() {}

bool FiltradorInputFecha::perteneceAlCombobox(const Glib::ustring& valor) {
    bool pertenece = false;
    unsigned i = 0;
    while (!pertenece && i < CANT_COMBO)
        pertenece = valor == valoresCombo[i++];

    return pertenece;
}

bool FiltradorInputFecha::esValido(const Glib::ustring& valor) {
    return true;
}

