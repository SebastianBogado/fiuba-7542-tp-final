#include "FiltradorInputDimension.h"
#include "Respuesta.h"

FiltradorInputDimension::FiltradorInputDimension(const Glib::ustring& input,
    PadreDeConsultantes* padre) : FiltradorInput(input) {
    padre->agregarConsultante(this);
    setSpinner(&s);
    centradorDerecho.pack_start(s, false, false);
    s.hide();

    // para popular el combobox
    consulta.agregarResultado(getFiltro());
}

FiltradorInputDimension::~FiltradorInputDimension() {}

void FiltradorInputDimension::procesarRespuesta(const Respuesta& rta) {
    if (rta.cantidadColumnas != 1)
        return;

    for (unsigned i = 0; i < rta.cantidadFilas; ++i)
        valores.append_text(rta.dato(i, 0));
}
