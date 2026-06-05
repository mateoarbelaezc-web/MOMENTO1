#ifndef MENUDIFICULTAD_H
#define MENUDIFICULTAD_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QObject>

class MenuDificultad : public QObject {
    Q_OBJECT
public:
    MenuDificultad(QGraphicsScene* escena);
    void mostrar();
    void ocultar();
    bool clicEnFacil(QPointF pos);
    bool clicEnDificil(QPointF pos);
    bool clicEnInstrucciones(QPointF pos);
    bool clicEnJediFacil(QPointF pos);
    bool clicEnJediNormal(QPointF pos);
    bool clicEnJediDificil(QPointF pos);

private:
    QGraphicsScene* escena;
    QGraphicsRectItem *botonFacil, *botonDificil, *botonInstrucciones;
    QGraphicsTextItem *textoFacil, *textoDificil, *textoInstrucciones;
    QGraphicsRectItem *botonJediFacil, *botonJediNormal, *botonJediDificil;
    QGraphicsTextItem *textoJediFacil, *textoJediNormal, *textoJediDificil;
};

#endif
