#include "pantallainstrucciones.h"
#include <QFont>

PantallaInstrucciones::PantallaInstrucciones(QGraphicsScene* escena) {
    this->escena = escena;

    fondoPanel = new QGraphicsRectItem(50, 20, 700, 570);
    fondoPanel->setBrush(QColor(0, 0, 0, 210));
    fondoPanel->setZValue(5);

    QString instrucciones =
        "══════════  INSTRUCCIONES  ══════════\n\n"
        "MODO TENIS\n"
        "  ↑ / ↓        Mover nave\n"
        "  ESC          Volver al menú\n\n"
        "  Objetivo: devuelve la pelota y anota puntos.\n"
        "  Sistema de puntuación real de tenis (games y sets).\n"
        "  El campo gravitacional desvía la trayectoria.\n\n"
        "  Fácil:   2 games para ganar, velocidad lenta\n"
        "  Difícil: 3 games para ganar, velocidad rápida\n\n"
        "────────────────────────────────────────\n\n"
        "MODO JEDI\n"
        "  A / D        Moverse izquierda / derecha\n"
        "  ESPACIO      Saltar\n"
        "  J            Golpear con sable láser\n"
        "  ESC          Volver al menú\n\n"
        "  Objetivo: deflecta los disparos del AT-AT\n"
        "  de vuelta hacia él para destruirlo.\n\n"
        "  Power-ups:  daño x2 o congela los disparos\n"
        "  Penalidades: lentitud o disparos más rápidos\n\n"
        "  Fácil:   más tiempo, disparos lentos\n"
        "  Normal:  velocidad media\n"
        "  Difícil: poco tiempo, disparos rápidos";

    textoInstrucciones = new QGraphicsTextItem(instrucciones);
    textoInstrucciones->setDefaultTextColor(Qt::white);
    textoInstrucciones->setFont(QFont("Arial", 10));
    textoInstrucciones->setPos(65, 28);
    textoInstrucciones->setZValue(6);

    botonVolver = new QGraphicsRectItem(330, 565, 140, 35);
    botonVolver->setBrush(Qt::darkRed);
    botonVolver->setZValue(6);

    textoVolver = new QGraphicsTextItem("VOLVER");
    textoVolver->setDefaultTextColor(Qt::white);
    textoVolver->setFont(QFont("Arial", 13, QFont::Bold));
    textoVolver->setPos(358, 569);
    textoVolver->setZValue(7);

    escena->addItem(fondoPanel);
    escena->addItem(textoInstrucciones);
    escena->addItem(botonVolver);
    escena->addItem(textoVolver);
    ocultar();
}

void PantallaInstrucciones::mostrar() {
    fondoPanel->setVisible(true);
    textoInstrucciones->setVisible(true);
    botonVolver->setVisible(true);
    textoVolver->setVisible(true);
}

void PantallaInstrucciones::ocultar() {
    fondoPanel->setVisible(false);
    textoInstrucciones->setVisible(false);
    botonVolver->setVisible(false);
    textoVolver->setVisible(false);
}

bool PantallaInstrucciones::clicEnVolver(QPointF pos) {
    return botonVolver->rect().contains(pos);
}
