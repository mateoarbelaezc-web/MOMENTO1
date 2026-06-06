#include "enemigo.h"
#include <QPainter>
#include <cstdlib>
#include <cmath>

Enemigo::Enemigo(float velocidadIA, float margenError) {
    ancho=100; alto=125;
    this->velocidadIA=velocidadIA; this->margenError=margenError;
    sprite=QPixmap(":/assets/tiefighter.png").scaled(100,125,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setPos(650,260);
    modoJedi=false;
    srand(time(nullptr));
}

QRectF Enemigo::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void Enemigo::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if(!sprite.isNull()) painter->drawPixmap(0,0,sprite);
    else { painter->setBrush(Qt::red); painter->drawRect(boundingRect()); }
}

QPainterPath Enemigo::shape() const {
    QPainterPath path;
    path.addRect(0, 0, ancho, alto);
    return path;
}

void Enemigo::seguirPelota(Pelota* pelota) {
    if(modoJedi) return;
    float error=(rand()%100)/100.0f*margenError;
    float objetivo=pelota->y()+error;
    if(y()+alto/2<objetivo && y()+alto<600) setPos(x(),y()+velocidadIA);
    else if(y()+alto/2>objetivo && y()>0) setPos(x(),y()-velocidadIA);
}

void Enemigo::setModoJedi(bool activar, float factorAprendizaje) {
    modoJedi = activar;
    if (modoJedi) {
        sprite = QPixmap(":/assets/at-at.png").scaled(150,180,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ancho = sprite.width();
        alto = sprite.height();
        setPos(630,210);
        vida = 100;
        multiplicadorDanio = 1;
        dificultadIA = factorAprendizaje;
        memoria.clear();
        memoria.push_back({0, -30, -15, 1, 0});
        memoria.push_back({1, -20, -40, 1, 0});
        memoria.push_back({2, -45, -10, 1, 0});
        memoria.push_back({3, -35, -8,  1, 0});
        posDisparoX = 680;
        posDisparoY = 320;
        bolaEntrante = false;
        tipoAnterior = -1;
        contadorRepeticion = 0;
    }
}

void Enemigo::leerPelota(const Pelota* pelota, bool fueGolpeadaPorJugador) {
    if(!modoJedi) return;
    if(pelota){
        percepX=pelota->x(); percepY=pelota->y();
        percepVx=pelota->getVelX(); percepVy=pelota->getVelY();
        bolaEntrante=true;
        if(fueGolpeadaPorJugador){
            if(pelota->y()<200) ultimaZonaImpacto=1;
            else if(pelota->y()>350) ultimaZonaImpacto=2;
            else ultimaZonaImpacto=0;
        }
    } else bolaEntrante=false;
}

void Enemigo::procesar() {
    if (!modoJedi) return;
    if (!bolaEntrante) {
        float pesoTotal = 0;
        for (auto& rec : memoria) {
            float distancia = qAbs(posXJugadorActual - rec.posXJugador);
            float bonusPosicion = (distancia < 80.0f) ? 2.0f : 1.0f;
            pesoTotal += (rec.usos + rec.exitos * dificultadIA) * bonusPosicion;
        }
        float r = (rand() % 10000) / 10000.0f * pesoTotal;
        float acum = 0;
        for (auto& rec : memoria) {
            float distancia = qAbs(posXJugadorActual - rec.posXJugador);
            float bonusPosicion = (distancia < 80.0f) ? 2.0f : 1.0f;
            acum += (rec.usos + rec.exitos * dificultadIA) * bonusPosicion;
            if (r <= acum) { tipoSeleccionado = rec.tipo; break; }
        }
    } else {
        switch (ultimaZonaImpacto) {
        case 1: tipoSeleccionado = 1; break;
        case 2: tipoSeleccionado = 0; break;
        default: tipoSeleccionado = 2; break;
        }
    }
}

Pelota* Enemigo::ejecutar() {
    if(!modoJedi) return nullptr;
    ShotRecord& rec=memoria[tipoSeleccionado];
    rec.usos++;
    float vx=rec.vx, vy=rec.vy;
    if(dificultadIA>1.0f){ vx*=(0.9f+(rand()%20)/100.0f); vy*=(0.9f+(rand()%20)/100.0f); }

    // Limitar ángulo: velY nunca supera 0.6 * |velX| para evitar disparos
    // hacia la esquina superior izquierda que el jugador no puede alcanzar
    float limiteVelY = 0.6f * qAbs(vx);
    if (vy < -limiteVelY) vy = -limiteVelY;
    if (vy >  limiteVelY) vy =  limiteVelY;

    Pelota* nueva=new Pelota();
    nueva->setUsarGravedad(true);
    nueva->setVelX(vx); nueva->setVelY(vy);
    nueva->setPos(posDisparoX,posDisparoY);
    return nueva;
}

void Enemigo::aprender(bool jugadorPerdioVida, int tipoDisparoUsado) {
    if(!modoJedi) return;
    if (jugadorPerdioVida) {
        for (auto& rec : memoria)
            if (rec.tipo == tipoDisparoUsado) {
                rec.exitos++;
                rec.posXJugador = posXJugadorActual; // guardar posición del éxito
                break;
            }
        contadorRepeticion = 0;
        tipoAnterior = tipoDisparoUsado;
    } else {
        // Cambio 2: el disparo NO fue exitoso
        if(tipoDisparoUsado == tipoAnterior) {
            contadorRepeticion++;
            // Si repite 3 veces seguidas sin éxito, penalizar ese tipo
            if(contadorRepeticion >= 3) {
                for(auto& rec:memoria) {
                    if(rec.tipo==tipoDisparoUsado && rec.usos > 1) {
                        rec.usos /= 2; // reducir peso para que lo elija menos
                        break;
                    }
                }
                contadorRepeticion = 0; // reiniciar para que pueda volver a penalizar
            }
        } else {
            contadorRepeticion = 1;
        }
        tipoAnterior = tipoDisparoUsado;
    }
}

void Enemigo::recibirDanio(int puntos) {
    if(modoJedi) vida -= puntos * multiplicadorDanio;
    if(vida < 0) vida = 0;
}

int Enemigo::getVida() const { return vida; }
void Enemigo::setMultiplicadorDanio(float mult) { multiplicadorDanio=mult; }
void Enemigo::setPosicionDisparo(float x, float y) { posDisparoX=x; posDisparoY=y; }
int Enemigo::getTipoSeleccionado() const { return tipoSeleccionado; }

void Enemigo::setPosXJugador(float x) {
    posXJugadorActual = x;
}
