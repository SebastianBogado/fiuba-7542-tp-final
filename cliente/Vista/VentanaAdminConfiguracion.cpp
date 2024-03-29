#include "VentanaAdminConfiguracion.h"
#include <gtkmm/button.h>
#include <gtkmm/messagedialog.h>
#include "ExcepcionArchivoGladeCorrupto.h"
#include "TabAdminConfigConexion.h"
#include "TabAdminConfigConsultas.h"
#include "TabAdminConfigPassword.h"

#define VBOX_TAB_CONEXION "vboxTabAdminConfigConexion"
#define VBOX_TAB_CONSULTAS "vboxTabAdminConfigConsultas"
#define VBOX_TAB_PASSWORD "vboxTabAdminConfigPassword"
#define BOTON_APLICAR_CONFIG "BotonAplicarConfig"
#define BOTON_CANCELAR_CONFIG "BotonCancelarConfig"

VentanaAdminConfiguracion::VentanaAdminConfiguracion(BaseObjectType* cobject,
            const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::Window(cobject), Buildable(_builder),
  pVDinamica(NULL) {
    TabAdminConfigConexion* tabConexion;
    get_widget_derived(VBOX_TAB_CONEXION, tabConexion);
    tabs.push_back(tabConexion);

    get_widget_derived(VBOX_TAB_CONSULTAS, tabConsultas);
    tabs.push_back(tabConsultas);

    get_widget_derived(VBOX_TAB_PASSWORD, tabPassword);
    tabs.push_back(tabPassword);

    Gtk::Button* pBotonAux;

    get_widget(BOTON_APLICAR_CONFIG, pBotonAux);
    pBotonAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaAdminConfiguracion::on_aplicar_button_clicked));

    get_widget(BOTON_CANCELAR_CONFIG, pBotonAux);
    pBotonAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaAdminConfiguracion::on_cancelar_button_clicked));
}

VentanaAdminConfiguracion::~VentanaAdminConfiguracion() {}

void VentanaAdminConfiguracion::on_show() {
    Window::on_show();
    tabPassword->limpiar_pass_entries();
}

void VentanaAdminConfiguracion::setArchivoPersonalizador(const char* archivo) {
    tabConsultas->setArchivoPersonalizador(archivo);
    tabConsultas->actualizarVDinamica(pVDinamica);
}
void VentanaAdminConfiguracion::setVDinamica(
    VentanaClienteDinamica* _pVDinamica) {
    pVDinamica = _pVDinamica;
}

void VentanaAdminConfiguracion::on_aplicar_button_clicked() {
    std::list< TabAdminConfig* >::iterator it = tabs.begin();
    bool pudoGuardar = true;
    while (pudoGuardar && it != tabs.end())
        pudoGuardar = (*it++)->aplicarCambios();

    if (pudoGuardar)
        tabConsultas->actualizarVDinamica(pVDinamica);
    else
        --it;

    if (it == tabs.end())
        hide();
    else {
        Glib::ustring msj;
        if (*it == tabConsultas)
            msj = "Revise las configuraciones de las consultas.";
        else
            msj = "En el cambio de password, el actual es erróneo.";

        Gtk::MessageDialog dialog(*this,
                                  msj,
                                  false,
                                  Gtk::MESSAGE_ERROR,
                                  Gtk::BUTTONS_OK,
                                  true);
        dialog.set_title("Error en la configuración");
        dialog.run();
    }
}

void VentanaAdminConfiguracion::on_cancelar_button_clicked() {
    hide();
}
