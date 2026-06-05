#include "naveimperial.h"
#include <QPainter>
#include <cstdlib>
#include <cmath>

NaveImperial::NaveImperial(float velocidadIA, float margenError) {
    ancho=100; alto=125;
    this->velocidadIA=velocidadIA; this->margenError=margenError;
    sprite=QPixmap(":/assets/tiefighter.png").scaled(100,125,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    setPos(650,260);
    modoJedi=false;
    srand(time(nullptr));
}

QRectF NaveImperial::boundingRect() const {
    return QRectF(0, 0, ancho, alto);
}

void NaveImperial::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if(!sprite.isNull()) painter->drawPixmap(0,0,sprite);
    else { painter->setBrush(Qt::red); painter->drawRect(boundingRect()); }
}

QPainterPath NaveImperial::shape() const {
    QPainterPath path;
    path.addRect(0, 0, ancho, alto);
    return path;
}

void NaveImperial::seguirPelota(Pelota* pelota) {
    if(modoJedi) return;
    float error=(rand()%100)/100.0f*margenError;
    float objetivo=pelota->y()+error;
    if(y()+alto/2<objetivo && y()+alto<600) setPos(x(),y()+velocidadIA);
    else if(y()+alto/2>objetivo && y()>0) setPos(x(),y()-velocidadIA);
}

void NaveImperial::setModoJedi(bool activar, float factorAprendizaje) {
    modoJedi = activar;
    if (modoJedi) {
        sprite = QPixmap(":/assets/tiefighter.png").scaled(100,120,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ancho = sprite.width();
        alto = sprite.height();
        setPos(680,290);
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
    }
}

void NaveImperial::leerPelota(const Pelota* pelota, bool fueGolpeadaPorJugador) {
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

void NaveImperial::procesar() {
    if(!modoJedi) return;
    if(!bolaEntrante){
        float pesoTotal=0;
        for(auto& rec:memoria) pesoTotal+=rec.usos+rec.exitos*dificultadIA;
        float r=(rand()%10000)/10000.0f*pesoTotal;
        float acum=0;
        for(auto& rec:memoria){
            acum+=rec.usos+rec.exitos*dificultadIA;
            if(r<=acum){ tipoSeleccionado=rec.tipo; break; }
        }
    } else {
        switch(ultimaZonaImpacto){
        case 1: tipoSeleccionado=1; break;
        case 2: tipoSeleccionado=0; break;
        default: tipoSeleccionado=2; break;
        }
    }
}

Pelota* NaveImperial::ejecutar() {
    if(!modoJedi) return nullptr;
    ShotRecord& rec=memoria[tipoSeleccionado];
    rec.usos++;
    float vx=rec.vx, vy=rec.vy;
    if(dificultadIA>1.0f){ vx*=(0.9f+(rand()%20)/100.0f); vy*=(0.9f+(rand()%20)/100.0f); }
    Pelota* nueva=new Pelota();
    nueva->setUsarGravedad(true);
    nueva->setVelX(vx); nueva->setVelY(vy);
    nueva->setPos(posDisparoX,posDisparoY);
    return nueva;
}

void NaveImperial::aprender(bool jugadorPerdioVida, int tipoDisparoUsado) {
    if(!modoJedi) return;
    if(jugadorPerdioVida){
        for(auto& rec:memoria)
            if(rec.tipo==tipoDisparoUsado){ rec.exitos++; break; }
    }
}

void NaveImperial::recibirDanio(int puntos) {
    if(modoJedi) vida -= puntos * multiplicadorDanio;
    if(vida < 0) vida = 0;
}

int NaveImperial::getVida() const { return vida; }
void NaveImperial::setMultiplicadorDanio(float mult) { multiplicadorDanio=mult; }
void NaveImperial::setPosicionDisparo(float x, float y) { posDisparoX=x; posDisparoY=y; }
int NaveImperial::getTipoSeleccionado() const { return tipoSeleccionado; }
