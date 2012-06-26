#ifndef PANEL_CONFIG_MODELO_H
#define PANEL_CONFIG_MODELO_H

#include <gtkmm/spinbutton.h>
#include "ConfigModelo.h"

#define NOMBRE_PANEL_POR_DEFECTO "Nuevo panel"

class PanelConfigModelo : public ConfigModelo {
    public:
        PanelConfigModelo();
        ~PanelConfigModelo();

        void setLabelPosicion(Gtk::Label* pLabel);
        void setSpinbuttonsPosicion(Gtk::SpinButton* pSpinbuttondesdeFila,
                                    Gtk::SpinButton* pSpinbuttonhastaFila,
                                    Gtk::SpinButton* pSpinbuttonDesdeCol,
                                    Gtk::SpinButton* pSpinbuttonHastaCol);
        void setPosicionNuevaComoValida(bool valida = true);

        void getPosicion(unsigned& desdeFila, unsigned& hastaFila,
                         unsigned& desdeCol, unsigned& hastaCol);

        sigc::signal< void, PanelConfigModelo*, int, int, int, int > signal_posicion_changed();

    private:
        /** modelo mismo */
        unsigned desdeFila, hastaFila;
        unsigned desdeCol, hastaCol;
        bool posicionValida;

        /** señales propias */
        sigc::signal< void, PanelConfigModelo*, int, int, int, int > _signal_posicion_changed;

        void desconectarDeHijo();
        /** conexiones a las señales de la vista */
        sigc::connection connectionLabelPosicion;
        sigc::connection connectionSpinButtonDesdeFila;
        sigc::connection connectionSpinButtonHastaFila;
        sigc::connection connectionSpinButtonDesdeCol;
        sigc::connection connectionSpinButtonHastaCol;
        void bloquearConnectionPosicion();
        void desbloquearConnectionPosicion();


        /** signal handlers*/
        void on_spinbuttons_posicion_changed();



        /** referencias a la vista */
        Gtk::Label* pLabelPosicion;
        Gtk::SpinButton* pSpinButtonDesdeFila;
        Gtk::SpinButton* pSpinButtonHastaFila;
        Gtk::SpinButton* pSpinButtonDesdeCol;
        Gtk::SpinButton* pSpinButtonHastaCol;
};

#endif  // PANEL_CONFIG_MODELO_H

