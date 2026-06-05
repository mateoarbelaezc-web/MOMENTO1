#include "menudificultad.h"
#include <QFont>

MenuDificultad::MenuDificultad(QGraphicsScene* escena) {
    this->escena = escena;

    // Botones tenis
    botonFacil = new QGraphicsRectItem(250,250,120,50);
    botonFacil->setBrush(Qt::darkGreen);
    textoFacil = new QGraphicsTextItem("TENIS FACIL");
    textoFacil->setDefaultTextColor(Qt::white);
    textoFacil->setFont(QFont("Arial",12,QFont::Bold));
    textoFacil->setPos(260,258);
    escena->addItem(botonFacil); escena->addItem(textoFacil);

    botonDificil = new QGraphicsRectItem(430,250,120,50);
    botonDificil->setBrush(Qt::darkRed);
    textoDificil = new QGraphicsTextItem("TENIS DIFICIL");
    textoDificil->setDefaultTextColor(Qt::white);
    textoDificil->setFont(QFont("Arial",12,QFont::Bold));
    textoDificil->setPos(435,258);
    escena->addItem(botonDificil); escena->addItem(textoDificil);

    botonInstrucciones = new QGraphicsRectItem(300,320,200,50);
    botonInstrucciones->setBrush(Qt::darkBlue);
    textoInstrucciones = new QGraphicsTextItem("INSTRUCCIONES");
    textoInstrucciones->setDefaultTextColor(Qt::white);
    textoInstrucciones->setFont(QFont("Arial",14,QFont::Bold));
    textoInstrucciones->setPos(315,328);
    escena->addItem(botonInstrucciones); escena->addItem(textoInstrucciones);

    // Botones Jedi
    botonJediFacil = new QGraphicsRectItem(200,400,100,40);
    botonJediFacil->setBrush(Qt::green);
    textoJediFacil = new QGraphicsTextItem("JEDI FÁCIL");
    textoJediFacil->setDefaultTextColor(Qt::white);
    textoJediFacil->setFont(QFont("Arial",10,QFont::Bold));
    textoJediFacil->setPos(210,408);
    escena->addItem(botonJediFacil); escena->addItem(textoJediFacil);

    botonJediNormal = new QGraphicsRectItem(350,400,100,40);
    botonJediNormal->setBrush(Qt::yellow);
    textoJediNormal = new QGraphicsTextItem("JEDI NORMAL");
    textoJediNormal->setDefaultTextColor(Qt::black);
    textoJediNormal->setFont(QFont("Arial",10,QFont::Bold));
    textoJediNormal->setPos(355,408);
    escena->addItem(botonJediNormal); escena->addItem(textoJediNormal);

    botonJediDificil = new QGraphicsRectItem(500,400,100,40);
    botonJediDificil->setBrush(Qt::red);
    textoJediDificil = new QGraphicsTextItem("JEDI DIFÍCIL");
    textoJediDificil->setDefaultTextColor(Qt::white);
    textoJediDificil->setFont(QFont("Arial",10,QFont::Bold));
    textoJediDificil->setPos(505,408);
    escena->addItem(botonJediDificil); escena->addItem(textoJediDificil);
}

void MenuDificultad::mostrar() {
    botonFacil->setVisible(true); textoFacil->setVisible(true);
    botonDificil->setVisible(true); textoDificil->setVisible(true);
    botonInstrucciones->setVisible(true); textoInstrucciones->setVisible(true);
    botonJediFacil->setVisible(true); textoJediFacil->setVisible(true);
    botonJediNormal->setVisible(true); textoJediNormal->setVisible(true);
    botonJediDificil->setVisible(true); textoJediDificil->setVisible(true);
}

void MenuDificultad::ocultar() {
    QList<QGraphicsItem*> items = escena->items();
    for (QGraphicsItem* it : items) it->setVisible(false);
}

bool MenuDificultad::clicEnFacil(QPointF pos) { return botonFacil->rect().contains(pos); }
bool MenuDificultad::clicEnDificil(QPointF pos) { return botonDificil->rect().contains(pos); }
bool MenuDificultad::clicEnInstrucciones(QPointF pos) { return botonInstrucciones->rect().contains(pos); }
bool MenuDificultad::clicEnJediFacil(QPointF pos) { return botonJediFacil->rect().contains(pos); }
bool MenuDificultad::clicEnJediNormal(QPointF pos) { return botonJediNormal->rect().contains(pos); }
bool MenuDificultad::clicEnJediDificil(QPointF pos) { return botonJediDificil->rect().contains(pos); }
