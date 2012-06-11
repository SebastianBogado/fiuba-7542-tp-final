#include "PadreDeConsultantes.h"

PadreDeConsultantes::PadreDeConsultantes() {
    spinner = NULL;
    padre = NULL;
}

void PadreDeConsultantes::hacerConsulta() {
    std::list< PadreDeConsultantes* >::iterator it = hijos.begin();
    for ( ; it != hijos.end(); ++it) {
        (*it)->hacerConsulta();
        Lock l(m);
        ++hijosActualizando;
    }
    if (hijosActualizando > 0 && spinner) {
        spinner->show();
        spinner->start();
    }
}

void PadreDeConsultantes::agregarConsultante(PadreDeConsultantes* c) {
    hijos.push_back(c);
    c->setPadre(this);
}


void PadreDeConsultantes::informarConsultaTerminada() {
    Lock l(m);
    --hijosActualizando;

    if (hijosActualizando == 0) {
        if (spinner) {
            spinner->stop();
            spinner->hide();
        }
        if (padre)
            padre->informarConsultaTerminada();
    }
}

void PadreDeConsultantes::setPadre(PadreDeConsultantes* _padre) {
    padre = _padre;
}

void PadreDeConsultantes::setSpinner(Gtk::Spinner* s) {
    spinner = s;
}
