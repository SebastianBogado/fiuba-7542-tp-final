#include "FiltradorConfigModelo.h"
#include "Organizacion.h"

FiltradorConfigModelo::FiltradorConfigModelo()
: comboDimension(NULL), comboFecha(NULL), comboHecho(NULL),
  entryExtra(NULL),
  botonEliminar(NULL) {

}

FiltradorConfigModelo::~FiltradorConfigModelo() {}

void FiltradorConfigModelo::setVista(Gtk::ComboBoxText* _comboDimension,
                                     Gtk::ComboBoxText* _comboFecha,
                                     Gtk::ComboBoxText* _comboHecho,
                                     Gtk::Entry* _entryExtra,
                                     Gtk::ToolButton* _botonEliminar) {
    setComboDimension(_comboDimension);
    setComboFecha(_comboFecha);
    setComboHecho(_comboHecho);
    setEntryExtra(_entryExtra);
    setBotonEliminar(_botonEliminar);
    especializarVista();
}


void FiltradorConfigModelo::setComboDimension(Gtk::ComboBoxText* comboDim) {
    comboDimension = comboDim;
    comboDimension->clear_items();
    for (unsigned i = 0; i < Organizacion::cantidadCampos(); ++i)
        comboDimension->append_text(Organizacion::nombreCampo(i));

    comboDimension->signal_changed().connect(sigc::mem_fun(*this,
        &FiltradorConfigModelo::on_combo_dimension_changed));

    comboDimension->set_active(0);
}

void FiltradorConfigModelo::setComboFecha(Gtk::ComboBoxText* _comboFecha) {
    comboFecha = _comboFecha;
    comboFecha->clear_items();
    comboFecha->append_text("Soy el combo de fecha");

    comboFecha->set_active(0);
}

void FiltradorConfigModelo::setComboHecho(Gtk::ComboBoxText* _comboHecho) {
    comboHecho = _comboHecho;
    comboHecho->clear_items();
    comboHecho->append_text("Soy el combo de hechos en general");

    comboHecho->set_active(0);
}

void FiltradorConfigModelo::setEntryExtra(Gtk::Entry* _entryExtra) {
    entryExtra = _entryExtra;
    entryExtra->set_text("");
}

void FiltradorConfigModelo::setBotonEliminar(Gtk::ToolButton* _botonEliminar) {
    botonEliminar = _botonEliminar;
    botonEliminar->signal_clicked().connect(sigc::mem_fun(*this,
        &FiltradorConfigModelo::on_boton_eliminar_clicked));
}

void FiltradorConfigModelo::on_boton_eliminar_clicked() {
    std::cout << "Eliminando filtrador @todo" << std::endl;
}