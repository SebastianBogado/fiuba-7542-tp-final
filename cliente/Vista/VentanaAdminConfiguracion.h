#ifndef VENTANA_ADMIN_CONFIGURACION_H
#define VENTANA_ADMIN_CONFIGURACION_H

#include <gtkmm/window.h>
#include <gtkmm/builder.h>

class VentanaAdminConfiguracion : public Gtk::Window {
    public:
        VentanaAdminConfiguracion(BaseObjectType* cobject,
                                  const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaAdminConfiguracion();
    private:
        Glib::RefPtr< Gtk::Builder > builder;

        void on_aplicar_button_clicked();
        void on_cancelar_button_clicked();
};

#endif  // VENTANA_ADMIN_CONFIGURACION_H
