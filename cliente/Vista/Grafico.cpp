#include "Grafico.h"
#include <exception>
#include <gtkmm/messagedialog.h>
#include "Area.h"
#include "FiltradoresPanel.h"
#include "Respuesta.h"
#include "Tab.h"

#define MIN_LADO 200
#define COL_RESULTADO 0  // constante que hace que siempre se tome la columna 0 de la respuesta para dar nombre a las áreas del gráfico
#define SIN_DATOS "No hay datos para mostrar"

Grafico::Grafico(FiltradoresPanel* _f) : Consultante(_f) {
    _f->signal_navegabilidad().connect(sigc::mem_fun(*this,
        &Consultante::on_navegabilidad_seleccionada));

    add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK);
    set_size_request(MIN_LADO, MIN_LADO);
    s.set_no_show_all();
    setSpinner(&s);
    furthest_x = 1.0;
    furthest_y = 1.0;
    min_lado = 0;
    areaSeleccionada = areas.end();
    should_request_size = true;
}

Grafico::~Grafico() {
    deleteAreas();
}

void Grafico::deleteAreas() {
    std::list< Area* >::iterator it;
    for (it = areas.begin(); it != areas.end(); ++it)
        delete *it;
}

void Grafico::regenerarReferencias() {
    std::list< Area* >::const_iterator itAreas = areas.begin();
    referencias.clear();
    for ( ; itAreas != areas.end(); ++itAreas) {
        Referencia refNueva(**itAreas);
        referencias.push_back(refNueva);
    }
    areaSeleccionada = areas.end();
}

bool Grafico::on_expose_event(GdkEventExpose* ev) {
    Glib::RefPtr<Gdk::Window> window = get_window();
    if (window) {
        Gtk::Allocation allocation = get_allocation();
        ancho_ventana = allocation.get_width();
        alto_ventana = allocation.get_height();
        if (!min_lado)
            min_lado = ancho_ventana < alto_ventana? ancho_ventana : alto_ventana;

        Cairo::RefPtr<Cairo::Context> ctx = window->create_cairo_context();
        ctx->set_source_rgba(1.0, 1.0, 1.0, 1.0);
        ctx->rectangle(0, 0, ancho_ventana, alto_ventana);
        ctx->fill_preserve();
        ctx->clip();
        ctx->scale(min_lado, min_lado);
        dibujarAreas(ctx);
        dibujarReferencias(ctx);
        dibujarEspecializacion(ev, ctx);
    }

    return true;
}

bool Grafico::on_motion_notify_event(GdkEventMotion* ev) {
    if (areas.empty())
        return true;
    // comprobar que el área seleccionada siga siendo la seleccionada, para
    // evitar iterar sobre todas y redibujar cuando no hubo cambios
    if (areaSeleccionada != areas.end() &&
        (*areaSeleccionada)->fueClickeada(ev->x/min_lado, ev->y/min_lado))
        return true;

    std::list< Area* >::iterator it = areas.begin();
    bool encontrada = false;
    unsigned i = 0;
    while ( !encontrada && it != areas.end()) {
        encontrada = (*it)->fueClickeada(ev->x/min_lado, ev->y/min_lado);
        (*(it++))->setSeleccionada(false);
        ++i;
    }

    if (encontrada) {
        areaSeleccionada = --it;
        (*areaSeleccionada)->setSeleccionada(true);
        set_tooltip_text((*areaSeleccionada)->getInfo());;
        ++it;
        for ( ; it != areas.end(); ++it)
            (*it)->setSeleccionada(false);
        --i;
    } else {
        // si ya se daba que ninguna estuviera seleccionada, cortar acá
        if (areaSeleccionada == areas.end())
            return true;

        set_tooltip_text("");
        areaSeleccionada = areas.end();
    }

    std::list< Referencia >::iterator itRefs = referencias.begin();
    unsigned j = 0;
    for ( ; j < i; ++j, ++itRefs)
        itRefs->setNegrita(false);
    if (itRefs != referencias.end()) {
        itRefs++->setNegrita(true);
        ++j;

        for ( ; j < referencias.size(); ++j, ++itRefs)
            itRefs->setNegrita(false);
    }

    queue_draw_area(0,0, ancho_ventana, alto_ventana);
    return true;
}

bool Grafico::on_button_press_event(GdkEventButton* ev) {
    if (ev->button != 1)
        return true;
    if (areaSeleccionada == areas.end())
        return true;

    Glib::ustring valor = (*areaSeleccionada)->getEtiqueta();
    Glib::ustring input = consulta.resultado(COL_RESULTADO);

    padre->difundirNavegacionSeleccionada(input, valor);
    return true;
}

void Grafico::dibujarAreas(Cairo::RefPtr< Cairo::Context >& ctx) {
    if (areas.empty()) {
        ctx->save();
            ctx->move_to(0.03, 0.1);
            ctx->set_font_size(0.06);
            ctx->set_source_rgb(0.5, 0.5, 0.5);
            ctx->show_text(SIN_DATOS);
        ctx->restore();
    } else {
        std::list< Area* >::iterator it = areas.begin();
        for ( ; it != areas.end(); ++it)
            (*it)->dibujar(ctx);
    }
}

void Grafico::dibujarReferencias(Cairo::RefPtr< Cairo::Context >& ctx) {
    if (referencias.empty())
        return;

    double offset = 0.0;
    double x, y;
    std::list< Referencia >::iterator it = referencias.begin();
    for ( ; it != referencias.end(); ++it) {
        dibujarEspecializacionReferencias(ctx);
        offset = it->dibujar(ctx, offset);
        ctx->get_current_point(x, y);
        actualizarTamanioMinimo(x, y);
    }
    resize();
}

void Grafico::procesarRespuesta(const Respuesta& rta) {
    if (rta.cantidadColumnas() != 2) {
        Gtk::MessageDialog dialog("Los gráficos sólo admiten un par de resultados",
                                  false,
                                  Gtk::MESSAGE_ERROR,
                                  Gtk::BUTTONS_OK,
                                  true);
        dialog.set_title("Error en una consulta");
        dialog.run();
        return;
    }

    double valor;
    std::stringstream ss;
    std::list< Hecho > datos;
    for (unsigned i = 0; i < rta.cantidadFilas(); ++i) {
        ss << rta.dato(i, 1);
        ss >> valor;
        datos.push_back(Hecho(rta.dato(i, COL_RESULTADO) , valor));
        ss.clear();
    }

    actualizarDatos(datos);
    queue_draw_area( 0, 0, ancho_ventana, alto_ventana);
}

void Grafico::actualizarTamanioMinimo(double x, double y) {
    furthest_x = x > furthest_x? x : furthest_x;
    furthest_y = y > furthest_y? y : furthest_y;
}

void Grafico::resize() {
    if (should_request_size &&
        (furthest_x > 1 || furthest_x > 1)) {
        // para que no termine la ventana pegada al último punto
        furthest_x += 0.1;
        furthest_y += 0.1;
        set_size_request(min_lado * furthest_x, min_lado * furthest_y);
        should_request_size = false;
    }
}
