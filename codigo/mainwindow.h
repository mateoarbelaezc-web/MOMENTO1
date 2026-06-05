#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "pelota.h"
#include "jugador.h"
#include "enemigo.h"
#include "marcador.h"
#include "obstaculo.h"
#include "fisicamotor.h"
#include "dificultad.h"
#include "menudificultad.h"
#include "sonidomanager.h"
#include "pantallainstrucciones.h"

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
    // Modo tenis
    QGraphicsScene* escena;
    QGraphicsView* vista;
    QTimer* timer;
    Pelota* pelota;
    Jugador* jugador;
    Enemigo* enemigo;
    Marcador* marcador;
    bool teclaArriba, teclaAbajo;
    Obstaculo* obstaculo;
    FisicaMotor* fisicaMotor;
    Dificultad* dificultad;
    MenuDificultad* menu;
    bool juegoIniciado;
    void iniciarJuego();
    void volverAlMenu();
    SonidoManager* sonido;
    PantallaInstrucciones* pantallaInstrucciones;
    bool enInstrucciones;

    // Modo Jedi
    enum ModoJuego { MODO_MENU, MODO_TENIS, MODO_JEDI };
    ModoJuego modoActual;
    bool teclaA, teclaD, teclaSpace, teclaJ;
    Jugador* jedi;
    Enemigo* atat;
    QVector<Pelota*> bolasJedi;
    int vidas, tiempoRestante;
    QTimer* temporizadorJuego;
    QGraphicsTextItem* textoVidas;
    QGraphicsTextItem* textoTiempo;
    QGraphicsRectItem* barraVidaAtat;
    float multiplicadorDanio;
    bool congelacionActiva;
    bool hayBolaActiva;
    QTimer* disparoTimer;
    QTimer* spawnTimer;
    bool victoriaFlag;
    bool gameOverFlag;
    bool menuTransition;
    bool volviendo;
    QGraphicsTextItem* textoPowerUpActivo;   // <--- NUEVO: declaración

    void iniciarModoJedi(int nivelDificultad);
    void actualizarModoJedi();
    void generarPowerUp();
    void generarPenalidad();
    void aplicarPowerUp(QGraphicsPixmapItem* power);
    void aplicarPenalidad(QGraphicsPixmapItem* penalty);
    void gameOver();
    void victoria();
};

#endif
