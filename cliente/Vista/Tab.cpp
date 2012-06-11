#include "Tab.h"
#include <iostream>

Tab::Tab(int i, const Glib::ustring& _etiqueta): etiqueta(_etiqueta) {
    setSpinner(&s);
    etiquetaCompuesta.pack_end(etiqueta, false, false);
    etiquetaCompuesta.pack_end(s, false, false);
    etiqueta.show();
    s.hide();
}

Tab::Tab(const std::string& xml) {}

Tab::~Tab() {}

Gtk::HBox& Tab::getEtiqueta() {
    return etiquetaCompuesta;
}


void Tab::agregarConsultante(PadreDeConsultantes* c) {
    std::cout << "    Pt agregó un hijo (" << c << ")" << std::endl;
    PadreDeConsultantes::agregarConsultante(c);
}
