#include "pelota.h"
#include <QPainter>

Pelota::Pelota() {
    velX=5; velY=5; radio=20;
    sprite=QPixmap(":/assets/pelota.png").scaled(40,40,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setPos(400,300);
    usarGravedad=false; bounceCount=0; dead=false; frozen=false; restitution=0.6f;
}
QRectF Pelota::boundingRect() const { return QRectF(-radio,-radio,radio*2,radio*2); }
void Pelota::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if(!sprite.isNull()) painter->drawPixmap(-radio,-radio,sprite);
    else { painter->setBrush(Qt::yellow); painter->drawEllipse(boundingRect()); }
}
void Pelota::mover() {
    if(usarGravedad) return;
    if(velY>5) velY=5; if(velY<-5) velY=-5;
    setPos(x()+velX, y()+velY);
}
void Pelota::rebotar(){ velY=-velY; }
QPainterPath Pelota::shape() const { QPainterPath path; path.addEllipse(-radio,-radio,radio*2,radio*2); return path; }
float Pelota::getVelX() const { return velX; }
float Pelota::getVelY() const { return velY; }
void Pelota::setVelX(float vx){ velX=vx; }
void Pelota::setVelY(float vy){ velY=vy; }
void Pelota::setUsarGravedad(bool usar){ usarGravedad=usar; }
void Pelota::actualizarConGravedad(float gravedad, float sueloY) {
    if (!usarGravedad || frozen || dead) return;

    velY += gravedad;
    setPos(x() + velX, y() + velY);

    const float MAX_SPEED = 200.0f;
    if (velX >  MAX_SPEED) velX =  MAX_SPEED;
    if (velX < -MAX_SPEED) velX = -MAX_SPEED;
    if (velY >  MAX_SPEED) velY =  MAX_SPEED;
    if (velY < -MAX_SPEED) velY = -MAX_SPEED;

    // Rebote en el piso
    if (y() + radio*2 >= sueloY) {
        setY(sueloY - radio*2);
        velY = -velY * restitution;
        bounceCount++;
        if (bounceCount >= 2) dead = true;
    }

    // Rebote en paredes laterales
    if (x() <= 0)              { setX(0);              velX = qAbs(velX); }
    if (x() + radio*2 >= 800)  { setX(800 - radio*2);  velX = -qAbs(velX); }
    // Rebote en techo
    if (y() <= 0) { setY(0); velY = qAbs(velY) * 0.8f; }
}
int Pelota::getBounceCount() const { return bounceCount; }
bool Pelota::isDead() const { return dead; }
void Pelota::setFrozen(bool congelada) {
    frozen = congelada;
}
