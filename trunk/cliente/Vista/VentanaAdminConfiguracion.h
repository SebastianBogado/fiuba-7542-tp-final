#ifndef VENTANA_ADMIN_CONFIGURACION_H
#define VENTANA_ADMIN_CONFIGURACION_H

#include <list>
#include <gtkmm/window.h>
#include "Buildable.h"

class TabAdminConfig;
class TabAdminConfigConsultas;

class VentanaAdminConfiguracion : public Gtk::Window, public Buildable  {
    public:
        VentanaAdminConfiguracion(BaseObjectType* cobject,
                                  const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaAdminConfiguracion();

        void setArchivoPersonalizador(const char* archivo);
    private:
        TabAdminConfigConsultas* tabConsultas;
        std::list< TabAdminConfig* > tabs;

        void on_aplicar_button_clicked();
        void on_cancelar_button_clicked();
};

#endif  // VENTANA_ADMIN_CONFIGURACION_H
