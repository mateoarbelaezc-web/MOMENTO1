#include "naverebelde.h"
#include <QPainter>
#include <cmath>

NaveRebelde::NaveRebelde() {
    ancho = 100; alto = 125;
    sprite = QPixmap(":/assets/xwing.png").scaled(100,125,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setPos(30,260);
    modoJedi = false;

    spriteIdle  = QPixmap(":/assets/jedi_idle.png");
    spriteWalk1 = QPixmap(":/assets/jedi_walk1.png");
    spriteWalk2 = QPixmap(":/assets/jedi_walk2.png");
    spriteJump  = QPixmap(":/assets/jedi_jump.png");
    spriteSwing = QPixmap(":/assets/jedi_swing.png");

    if (spriteIdle.isNull())  { spriteIdle  = QPixmap(60,100); spriteIdle.fill(Qt::blue); }
    if (spriteWalk1.isNull()) spriteWalk1 = spriteIdle;
    if (spriteWalk2.isNull()) spriteWalk2 = spriteIdle;
    if (spriteJump.isNull())  spriteJump  = spriteIdle;
    if (spriteSwing.isNull()) spriteSwing = spriteIdle;

    vx = vy = 0;
    enSuelo = true;
    gravedad = 0.6f;
    potenciaSalto = -17.0f;
    velocidadMovimiento = 5.0f;
    multiplicadorVel = 1.0f;
    limiteIzquierdo = 10;
    limiteDerecho = 700;
    sueloY = 481;           // bajado para que esté cerca del suelo visual
    izquierdaPresionada = derechaPresionada = false;
    swingActivo = false;
    swingFrames = 0;
    swingSpriteCounter = 0;
    walkFrameCounter = 0;
    walkToggle = false;
}

QRectF NaveRebelde::boundingRect() const {
    if (modoJedi) return QRectF(0, 0, ancho, alto);
    else return QRectF(20, 10, ancho-40, alto-20);
}

void NaveRebelde::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (modoJedi) {
        QPixmap* current = &spriteIdle;

        if (swingSpriteCounter > 0) {
            current = &spriteSwing;
        } else if (!enSuelo) {
            current = &spriteJump;
        } else if (izquierdaPresionada || derechaPresionada) {
            current = walkToggle ? &spriteWalk1 : &spriteWalk2;
        }

        bool mirarIzquierda = (izquierdaPresionada && !derechaPresionada) || (vx < 0);
        painter->save();
        if (mirarIzquierda) {
            painter->translate(ancho, 0);
            painter->scale(-1, 1);
        }
        painter->drawPixmap(0, 0, ancho, alto, *current);
        painter->restore();
    } else {
        painter->drawPixmap(0, 0, sprite);
    }
}

QPainterPath NaveRebelde::shape() const {
    QPainterPath path;
    if (modoJedi) path.addRect(boundingRect());
    else {
        path.addRect(ancho*0.35,0,ancho*0.30,alto);
        path.addRect(0,alto*0.35,ancho,alto*0.30);
    }
    return path;
}

void NaveRebelde::moverArriba() { if (!modoJedi && y()>0) setPos(x(), y()-6); }
void NaveRebelde::moverAbajo()  { if (!modoJedi && y()+alto<595) setPos(x(), y()+6); }

void NaveRebelde::setModoJedi(bool activar) {
    modoJedi = activar;
    if (modoJedi) {
        ancho = spriteIdle.isNull() ? 60 : spriteIdle.width();
        alto  = spriteIdle.isNull() ? 100 : spriteIdle.height();
        setPos(100, sueloY - alto);
        vx = vy = 0;
        enSuelo = true;
        swingSpriteCounter = 0;
        swingActivo = false;
        walkFrameCounter = 0;
        walkToggle = false;
    }
}

void NaveRebelde::actualizarFisica() {
    if (!modoJedi) return;
    if (izquierdaPresionada) vx = -velocidadMovimiento * multiplicadorVel;
    else if (derechaPresionada) vx = velocidadMovimiento * multiplicadorVel;
    else vx = 0;
    setX(x() + vx);
    if (x() < limiteIzquierdo) setX(limiteIzquierdo);
    if (x() + ancho > limiteDerecho) setX(limiteDerecho - ancho);

    vy += gravedad;
    setY(y() + vy);
    if (y() + alto >= sueloY) {
        setY(sueloY - alto);
        vy = 0;
        enSuelo = true;
    } else {
        enSuelo = false;
    }

    // Animación caminata: alterna cada 8 frames
    if ((izquierdaPresionada || derechaPresionada) && enSuelo) {
        walkFrameCounter++;
        if (walkFrameCounter >= 8) {
            walkFrameCounter = 0;
            walkToggle = !walkToggle;
        }
    } else {
        walkFrameCounter = 0;
    }

    if (swingSpriteCounter > 0) {
        swingSpriteCounter--;
        if (swingSpriteCounter == 0) swingActivo = false;
    }
    if (swingFrames > 0) {
        swingFrames--;
        if (swingFrames == 0) swingActivo = false;
    }
}

void NaveRebelde::saltar() {
    if (modoJedi && enSuelo) {
        vy = potenciaSalto;
        enSuelo = false;
    }
}

void NaveRebelde::activarSwing() {
    if (!modoJedi) return;
    swingActivo = true;
    swingFrames = 12;
    swingSpriteCounter = 12;
}

bool NaveRebelde::isSwinging() const { return swingActivo; }
void NaveRebelde::setMultiplicadorVelocidad(float mult) { multiplicadorVel = mult; }
void NaveRebelde::moverIzquierda(bool activo) { izquierdaPresionada = activo; }
void NaveRebelde::moverDerecha(bool activo) { derechaPresionada = activo; }
void NaveRebelde::setLimites(float izquierda, float derecha, float suelo) {
    limiteIzquierdo = izquierda;
    limiteDerecho = derecha;
    sueloY = suelo;
}
