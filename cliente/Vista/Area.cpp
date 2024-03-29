#include "Area.h"
#include "Hecho.h"
#include "Utilitario.h"

#define DEFAULT_LINE_WIDTH  0.01
#define SELEC_LINE_WIDTH    1.5*DEFAULT_LINE_WIDTH

#define MAX_VALORES 15
double Area::colores[MAX_VALORES][4] = {
    {0.77, 0.2, 0.4, 1.0}, {0.4, 0.77, 0.2, 1.0}, {0.4, 0.3, 0.77, 1.0},
    {0.7, 0.3, 0.77, 1.0}, {0.1, 0.7, 0.77, 1.0}, {0.4, 0.9, 0.77, 1.0},
    {0.4, 0.67, 0.9, 1.0}, {0.9, 0.67, 0.4, 1.0}, {0.9, 0.4, 0.67, 1.0},
    {0.22, 0.2, 0.4, 1.0}, {0.4, 0.22, 0.2, 1.0}, {0.2, 0.4, 0.22, 1.0},
    {0.99, 0.3, 0.9, 1.0}, {0.1, 0.9, 0.99, 1.0}, {0.4, 0.9, 0.99, 1.0},
};

Area::Area(const Hecho& _dato, double maximo, unsigned i, double _offset)
: dato(_dato) {
    lineWidth = DEFAULT_LINE_WIDTH;
    offset = _offset;
    max = maximo;
    unsigned color_i = i % MAX_VALORES;
    for (unsigned j = 0; j < 4; ++j)
        color[j] = colores[color_i][j];
}

Area::~Area() {}

const Glib::ustring& Area::getEtiqueta() const {
    return dato.getEtiqueta();
}

const double* Area::getColor() const {
    return color;
}

void Area::setSeleccionada(bool selec) {
    if (selec)
        lineWidth = SELEC_LINE_WIDTH;
    else
        lineWidth = DEFAULT_LINE_WIDTH;
}

void Area::set_line_width(Cairo::RefPtr< Cairo::Context >& ctx) {
    ctx->set_line_width(lineWidth);
}
