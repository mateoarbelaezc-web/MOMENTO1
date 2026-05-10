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

private:
    QGraphicsScene* escena;
    QGraphicsRectItem* botonFacil;
    QGraphicsRectItem* botonDificil;
    QGraphicsRectItem* botonInstrucciones;
    QGraphicsTextItem* textoFacil;
    QGraphicsTextItem* textoDificil;
    QGraphicsTextItem* textoInstrucciones;
};

#endif
