#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsItem>
#include <QPixmap>

class Personaje : public QGraphicsItem {
public:
    Personaje();
    virtual ~Personaje() = default;
    float getAncho() const;
    float getAlto() const;

protected:
    float ancho, alto;
    QPixmap sprite;
};

#endif
