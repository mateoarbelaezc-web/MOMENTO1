#ifndef PANTALLAINSTRUCCIONES_H
#define PANTALLAINSTRUCCIONES_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QObject>

class PantallaInstrucciones : public QObject {
    Q_OBJECT
public:
    PantallaInstrucciones(QGraphicsScene* escena);
    void mostrar();
    void ocultar();
    bool clicEnVolver(QPointF pos);

private:
    QGraphicsScene* escena;
    QGraphicsTextItem* textoInstrucciones;
    QGraphicsRectItem* botonVolver;
    QGraphicsTextItem* textoVolver;
    QGraphicsRectItem* fondoPanel;
};

#endif
