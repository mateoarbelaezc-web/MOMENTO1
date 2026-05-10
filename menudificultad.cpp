#include "menudificultad.h"
#include <QFont>

MenuDificultad::MenuDificultad(QGraphicsScene* escena) {
    this->escena = escena;

    botonFacil = new QGraphicsRectItem(250, 250, 120, 50);
    botonFacil->setBrush(Qt::darkGreen);
    textoFacil = new QGraphicsTextItem("FACIL");
    textoFacil->setDefaultTextColor(Qt::white);
    textoFacil->setFont(QFont("Arial", 16, QFont::Bold));
    textoFacil->setPos(272, 258);

    botonDificil = new QGraphicsRectItem(430, 250, 120, 50);
    botonDificil->setBrush(Qt::darkRed);
    textoDificil = new QGraphicsTextItem("DIFICIL");
    textoDificil->setDefaultTextColor(Qt::white);
    textoDificil->setFont(QFont("Arial", 16, QFont::Bold));
    textoDificil->setPos(445, 258);

    escena->addItem(botonFacil);
    escena->addItem(textoFacil);
    escena->addItem(botonDificil);
    escena->addItem(textoDificil);
}

void MenuDificultad::mostrar() {
    botonFacil->setVisible(true);
    textoFacil->setVisible(true);
    botonDificil->setVisible(true);
    textoDificil->setVisible(true);
}

void MenuDificultad::ocultar() {
    botonFacil->setVisible(false);
    textoFacil->setVisible(false);
    botonDificil->setVisible(false);
    textoDificil->setVisible(false);
}

bool MenuDificultad::clicEnFacil(QPointF pos) {
    return botonFacil->rect().contains(pos);
}

bool MenuDificultad::clicEnDificil(QPointF pos) {
    return botonDificil->rect().contains(pos);
}
