#include "FiltroConfigModelo.h"
#include "Organizacion.h"
#include "ExcepcionTabSoloAdmiteInputs.h"
#include "FiltradoresPanel.h"

FiltroConfigModelo::FiltroConfigModelo(unsigned _ID,
    const std::list< std::string >& _camposDisponibles)
: FiltradorConfigModelo(_ID, _camposDisponibles) {}

FiltroConfigModelo::~FiltroConfigModelo() {}

void FiltroConfigModelo::setFiltradorEn(FiltradoresTab* filtTab) {
    throw ExcepcionTabSoloAdmiteInputs("filtro");
}

void FiltroConfigModelo::setFiltradorEn(FiltradoresPanel* filtPanel) {
    if (Organizacion::esHecho(campoSelecc) ||
        Organizacion::esDimensionEspecial(campoSelecc))
        filtPanel->agregarFiltro(campoSelecc, _campoAux,
                                 entryPorCampo[campoSelecc]);
    else
        filtPanel->agregarFiltro(campoSelecc, entryPorCampo[campoSelecc]);
}

void FiltroConfigModelo::especializarVista() {
    entryExtra->show();
    entryExtra->signal_changed().connect(sigc::mem_fun(*this,
        &FiltroConfigModelo::on_entry_changed));
}

void FiltroConfigModelo::on_combo_dimension_changed() {
    campoSeleccNuevo = comboDimension->get_active_text();
    signal_campo_changed().emit(campoSelecc, campoSeleccNuevo);
    campoSelecc = campoSeleccNuevo;

    if (Organizacion::esDimensionEspecial(campoSelecc)) {
        comboFecha->show();
        comboHecho->hide();
        _campoAux = comboFecha->get_active_text();
    } else if (Organizacion::esHecho(campoSelecc)) {
        comboFecha->hide();
        comboHecho->show();
        _campoAux = comboHecho->get_active_text();
    } else {
        comboFecha->hide();
        comboHecho->hide();
    }
    entryExtra->set_text(_valorCampo);
}

void FiltroConfigModelo::on_entry_changed() {
	_valorCampo = entryExtra->get_text();
	entryPorCampo[campoSelecc] =_valorCampo;
}

void FiltroConfigModelo::completarAtributos() {
	entryPorCampo[campoSelecc] = _valorCampo;

	if (Organizacion::esDimensionEspecial(campoSeleccNuevo)) {
		comboFecha->set_active_text(_campoAux);
	}
	else if (Organizacion::esHecho(campoSeleccNuevo)) {
		comboHecho->set_active_text(_campoAux);
	}

	comboDimension->set_active_text(campoSeleccNuevo);
}
