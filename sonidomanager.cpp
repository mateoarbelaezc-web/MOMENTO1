#include "sonidomanager.h"

SonidoManager::SonidoManager() {
    musicaPlayer = new QMediaPlayer();
    musicaOutput = new QAudioOutput();
    musicaPlayer->setAudioOutput(musicaOutput);
    musicaOutput->setVolume(0.5f);
    musicaPlayer->setLoops(QMediaPlayer::Infinite);

    efectoPlayer = new QMediaPlayer();
    efectoOutput = new QAudioOutput();
    efectoPlayer->setAudioOutput(efectoOutput);
    efectoOutput->setVolume(0.8f);
}

SonidoManager::~SonidoManager() {
    delete musicaPlayer;
    delete musicaOutput;
    delete efectoPlayer;
    delete efectoOutput;
}

void SonidoManager::reproducirMusica(QString archivo) {
    musicaPlayer->setSource(QUrl(archivo));
    musicaPlayer->play();
}

void SonidoManager::detenerMusica() {
    musicaPlayer->stop();
}

void SonidoManager::reproducirEfecto(QString archivo) {
    efectoPlayer->setSource(QUrl(archivo));
    efectoPlayer->play();
}

void SonidoManager::setVolumen(float volumen) {
    musicaOutput->setVolume(volumen);
}
