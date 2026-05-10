#ifndef SONIDOMANAGER_H
#define SONIDOMANAGER_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QString>

class SonidoManager {
public:
    SonidoManager();
    ~SonidoManager();
    void reproducirMusica(QString archivo);
    void detenerMusica();
    void reproducirEfecto(QString archivo);
    void setVolumen(float volumen);

private:
    QMediaPlayer* musicaPlayer;
    QAudioOutput* musicaOutput;
    QMediaPlayer* efectoPlayer;
    QAudioOutput* efectoOutput;
};

#endif
