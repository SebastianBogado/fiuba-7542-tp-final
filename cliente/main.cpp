#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/builder.h>
#include "Cliente.h"
#include "ExcepcionArchivoGladeCorrupto.h"

#define SIN_ERRORES "____no_hubo_errores____"

int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);
    Glib::ustring msj = SIN_ERRORES;
    try {
        Cliente c(argc, argv);
        c.run();
    }
    catch(const Glib::FileError& e) {
        msj = "FileError: " + e.what();
    }
    catch(const Gtk::BuilderError& e) {
        msj = "BuilderError: " + e.what();
    }
    catch(const Glib::MarkupError& e) {
        msj = "MarkupError: " + e.what();
    }
    catch (const ExcepcionArchivoGladeCorrupto& e) {
         msj = e.what();
    }
    catch (char const* _msj) {
        msj = _msj;
    }
    catch (...) {
    	msj = "Consulta Mal Formada";
    }

    if (msj != SIN_ERRORES) {
        msj += "\n\nContáctese con el administrador.";
        Gtk::MessageDialog dialog(msj,
                                  false,
                                  Gtk::MESSAGE_ERROR,
                                  Gtk::BUTTONS_OK,
                                  true);
        dialog.set_title("Error");
        dialog.run();
    }
    return 0;
}

