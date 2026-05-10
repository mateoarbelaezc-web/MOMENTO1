#include "pantallainstrucciones.h"
#include <QFont>

PantallaInstrucciones::PantallaInstrucciones(QGraphicsScene* escena) {
    this->escena = escena;

    // Panel de fondo
    fondoPanel = new QGraphicsRectItem(80, 30, 640, 560);
    fondoPanel->setBrush(QColor(0, 0, 0, 200));
    fondoPanel->setZValue(5);

    // Texto de instrucciones
    QString instrucciones =
        "INSTRUCCIONES\n\n"
        "CONTROLES:\n"
        "  Flecha arriba / abajo: mover nave\n"
        "  ESC: volver al menu\n\n"
        "OBJETIVO:\n"
        "  Golpea el torpedo proton con tu nave\n"
        "  y evita que el Imperio anote puntos.\n\n"
        "PUNTUACION:\n"
        "  Sistema de puntuacion real de tenis\n"
        "  (15, 30, 40, Deuce, Ad, Tie-break)\n\n"
        "CAMPO GRAVITACIONAL:\n"
        "  Al cruzar el campo gravitacional,\n"
        "  la trayectoria del torpedo puede\n"
        "  desviarse de forma impredecible.\n\n"
        "DIFICULTAD:\n"
        "  Facil:  2 games, enemigo lento,\n"
        "          campo lento\n"
        "  Dificil: 3 games, enemigo rapido,\n"
        "          campo mas impredecible\n\n"
        "CONTEXTO:\n"
        "  La Alianza Rebelde enfrenta al Imperio\n"
        "  Galactico en una batalla espacial\n"
        "  de tenis cerca de la Estrella de la Muerte.";

    textoInstrucciones = new QGraphicsTextItem(instrucciones);
    textoInstrucciones->setDefaultTextColor(Qt::white);
    textoInstrucciones->setFont(QFont("Arial", 11));
    textoInstrucciones->setPos(100, 40);
    textoInstrucciones->setZValue(6);

    // Boton volver
    botonVolver = new QGraphicsRectItem(330, 565, 140, 40);
    botonVolver->setBrush(Qt::darkRed);
    botonVolver->setZValue(6);
    textoVolver = new QGraphicsTextItem("VOLVER");
    textoVolver->setDefaultTextColor(Qt::white);
    textoVolver->setFont(QFont("Arial", 14, QFont::Bold));
    textoVolver->setPos(355, 570);
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
