#ifndef VENTANA_CLIENTE_DINAMICA_H
#define VENTANA_CLIENTE_DINAMICA_H

#include <map>
#include <gtkmm/notebook.h>
#include "Personalizador.h"
#include "Buildable.h"

class Tab;
class ServidorRemoto;
class Consultante;

typedef std::map < unsigned, Consultante* > MapaConsultantesTab;
typedef std::pair < unsigned, Consultante* > parMapaConsultas;

class VentanaClienteDinamica : public Gtk::Notebook, public Buildable  {
    public:
        VentanaClienteDinamica(BaseObjectType* cobject,
                               const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaClienteDinamica();

        void personalizar(const char* archivo);

        void hacerConsulta(ServidorRemoto& server);
        void hacerConsultaInicial(ServidorRemoto& server);
        void cancelarConsulta(ServidorRemoto& server);
        // actualiza una consulta en particular, a pedido
        void actualizarConsulta(Consultante* c);

        void removerConsultante(unsigned ID);
        void agregarConsultantesTab(const MapaConsultantesTab& consultantes);

        void retirarRespuestas(ServidorRemoto& server);

        bool disponibleParaActualizacion(guint pag);

        // fuerza un refresh
        void refresh();

        sigc::signal< void, Consultante* > signal_actualizacion();

    private:
        Personalizador dynBuilder;
        MapaConsultantesTab consultas;
        std::vector< Tab* > tabs;

        void agregarData(Tab& t);

        /** señal para evitar setearle el padre (es una prueba) */
        sigc::signal< void, Consultante* > solicitudDeActualizacion;
};

#endif  // VENTANA_CLIENTE_DINAMICA_H