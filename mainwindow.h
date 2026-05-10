#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include "pelota.h"
#include "naverebelde.h"
#include "naveimperial.h"
#include "marcador.h"
#include "obstaculo.h"
#include "fisicamotor.h"
#include "dificultad.h"
#include "menudificultad.h"
#include <QMouseEvent>
#include "sonidomanager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject* obj, QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void actualizar();

private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    QTimer* timer;
    Pelota* pelota;
    NaveRebelde* naveRebelde;
    NaveImperial* naveImperial;
    Marcador* marcador;
    bool teclaArriba;
    bool teclaAbajo;
    Obstaculo* obstaculo;
    FisicaMotor* fisicaMotor;
    Dificultad* dificultad;
    MenuDificultad* menu;
    bool juegoIniciado;
    void iniciarJuego();
    void volverAlMenu();
    SonidoManager* sonido;
};

#endif
