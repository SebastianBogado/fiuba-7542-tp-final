#ifndef FILTRADOR_FILTRO_FECHA_H
#define FILTRADOR_FILTRO_FECHA_H

#include "FiltradorFiltro.h"

/** @class FiltradorFiltroFecha
 * Filtro de tipo fecha.
 */
class FiltradorFiltroFecha : public FiltradorFiltro {
    public:
        FiltradorFiltroFecha(const Glib::ustring& fecha,
                             const Glib::ustring& valorCombo,
                             const std::string& valorEntrada);
        ~FiltradorFiltroFecha();

        void filtrar(Consulta& c);

    private:
        Glib::ustring valorCombo;
        Glib::ustring valorEntrada;
        int i;  // iésimo valor del combobox posible
        Fecha f;
};

#endif  // FILTRADOR_FILTRO_FECHA_H
