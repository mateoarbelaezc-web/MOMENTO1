#include "sonidomanager.h"

SonidoManager::SonidoManager() {
    musicaPlayer = new QMediaPlayer();
    musicaOutput = new QAudioOutput();
    musicaPlayer->setAudioOutput(musicaOutput);
    musicaOutput->setVolume(0.5f);
    musicaPlayer->setLoops(QMediaPlayer::Infinite);

    efectoGolpe = new QSoundEffect();
    efectoGolpe->setSource(QUrl("qrc:/assets/golpe.wav"));
    efectoGolpe->setVolume(0.8f);
    efectoPunto = new QSoundEffect();
    efectoPunto->setSource(QUrl("qrc:/assets/punto.wav"));
    efectoPunto->setVolume(0.8f);
    efectoGravedad = new QSoundEffect();
    efectoGravedad->setSource(QUrl("qrc:/assets/gravedad.wav"));
    efectoGravedad->setVolume(0.8f);
    efectoSable = new QSoundEffect();
    efectoSable->setSource(QUrl("qrc:/assets/sable.wav"));
    efectoSable->setVolume(0.9f);
    efectoPowerUp = new QSoundEffect();
    efectoPowerUp->setSource(QUrl("qrc:/assets/powerup.wav"));
    efectoPowerUp->setVolume(0.7f);
    efectoPenalidad = new QSoundEffect();
    efectoPenalidad->setSource(QUrl("qrc:/assets/penalty.wav"));
    efectoPenalidad->setVolume(0.7f);
    efectoVictoria = new QSoundEffect();
    efectoVictoria->setSource(QUrl("qrc:/assets/victoria.wav"));
    efectoVictoria->setVolume(0.8f);
    efectoDerrota = new QSoundEffect();
    efectoDerrota->setSource(QUrl("qrc:/assets/derrota.wav"));
    efectoDerrota->setVolume(0.8f);
}

SonidoManager::~SonidoManager() {
    delete musicaPlayer;
    delete musicaOutput;
    delete efectoGolpe;
    delete efectoPunto;
    delete efectoGravedad;
    delete efectoSable;
    delete efectoPowerUp;
    delete efectoPenalidad;
    delete efectoVictoria;
    delete efectoDerrota;
}

void SonidoManager::reproducirMusica(QString archivo) {
    musicaPlayer->setSource(QUrl(archivo));
    musicaPlayer->play();
}

void SonidoManager::detenerMusica() {
    musicaPlayer->stop();
}

void SonidoManager::reproducirEfecto(QString archivo) {
    if (archivo.contains("golpe")) efectoGolpe->play();
    else if (archivo.contains("punto")) efectoPunto->play();
    else if (archivo.contains("gravedad")) efectoGravedad->play();
    else if (archivo.contains("sable")) efectoSable->play();
    else if (archivo.contains("powerup")) efectoPowerUp->play();
    else if (archivo.contains("penalty")) efectoPenalidad->play();
    else if (archivo.contains("victoria")) efectoVictoria->play();
    else if (archivo.contains("derrota")) efectoDerrota->play();
}

void SonidoManager::setVolumen(float volumen) {
    musicaOutput->setVolume(volumen);
}
