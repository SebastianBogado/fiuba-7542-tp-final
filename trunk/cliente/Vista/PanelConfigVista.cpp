#include "PanelConfigVista.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "PanelConfigModelo.h"

#define ENTRY_PANEL_LABEL "entryPanelLabel"
#define SPINBUTTON_DESDE_FILA "spinbuttonPanelDesdeFila"
#define SPINBUTTON_HASTA_FILA "spinbuttonPanelHastaFila"
#define SPINBUTTON_DESDE_COL "spinbuttonPanelDesdeCol"
#define SPINBUTTON_HASTA_COL "spinbuttonPanelHastaCol"

#include <iostream>
PanelConfigVista::PanelConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::VBox(cobject), Buildable(_builder), pModelo(NULL) {
    // label
    get_widget(ENTRY_PANEL_LABEL, pEntryPanelLabel);

    // spinners fila
    get_widget(SPINBUTTON_DESDE_FILA, pSpinbuttonDesdeFila);
    get_widget(SPINBUTTON_HASTA_FILA, pSpinbuttonHastaFila);

    // spinners col
    get_widget(SPINBUTTON_DESDE_COL, pSpinbuttonDesdeCol);
    get_widget(SPINBUTTON_HASTA_COL, pSpinbuttonHastaCol);
}

PanelConfigVista::~PanelConfigVista() {}

#include <iostream>
void PanelConfigVista::setModelo(PanelConfigModelo* pModeloNuevo) {
    if (pModelo == pModeloNuevo)
        return;

    std::cout << "PanelConfigVista ( " << this << " ) seteando modelo nuevo de panel: " <<pModeloNuevo << std::endl;
    if (pModelo)
        pModelo->desconectar();

    pModelo = pModeloNuevo;
    pModelo->setEntryLabel(pEntryPanelLabel);
//    pModelo->setSpinButtonsGrilla(pSpinButtonFilas, pSpinButtonCols);
}



