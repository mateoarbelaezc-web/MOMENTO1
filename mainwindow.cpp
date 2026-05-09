#include "mainwindow.h"
#include <QEvent>
#include <QDebug>
#include <QFont>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 800, 600);
    escena->setBackgroundBrush(Qt::black);

    vista = new QGraphicsView(escena, this);
    vista->setFixedSize(806, 606);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(vista);
    setWindowTitle("Tenis Star Wars");

    pelota = new Pelota();
    escena->addItem(pelota);

    naveRebelde = new NaveRebelde();
    escena->addItem(naveRebelde);

    naveImperial = new NaveImperial(4.0f, 80.0f);
    escena->addItem(naveImperial);

    obstaculo = new Obstaculo();
    escena->addItem(obstaculo);

    marcador = new Marcador();
    escena->addItem(marcador);

    teclaArriba = false;
    teclaAbajo = false;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizar);
    timer->start(16);

    vista->installEventFilter(this);
    vista->setFocusPolicy(Qt::StrongFocus);
    vista->setFocus();
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (obj == vista) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Up) teclaArriba = true;
            if (keyEvent->key() == Qt::Key_Down) teclaAbajo = true;
            return true;
        }
        if (event->type() == QEvent::KeyRelease) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Up) teclaArriba = false;
            if (keyEvent->key() == Qt::Key_Down) teclaAbajo = false;
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::actualizar() {
    escena->update();
    pelota->mover();

    // Rebotar en bordes superior e inferior
    if (pelota->y() <= 0 || pelota->y() >= 590)
        pelota->setVelY(-pelota->getVelY());

    // Colision con NaveRebelde
    if (pelota->collidesWithItem(naveRebelde)) {
        pelota->setVelX(qAbs(pelota->getVelX()));
    }

    // Colision con NaveImperial
    if (pelota->collidesWithItem(naveImperial)) {
        pelota->setVelX(-qAbs(pelota->getVelX()));
    }

    // Colision con obstaculo
    if (pelota->collidesWithItem(obstaculo)) {
        float desvio = ((rand() % 400) - 200) / 100.0f;
        pelota->setVelY(pelota->getVelY() + desvio);
    }

    // Pelota sale por la izquierda (punto Imperio)
    if (pelota->x() <= 0) {
        if (marcador->getEnTieBreak())
            marcador->anotarTieImperio();
        else
            marcador->anotarImperio();
        if (marcador->hayGanador()) {
            timer->stop();
            qDebug() << "Ganador:" << marcador->ganador();
            qDebug() << "Sets jugador:" << marcador->getSetsJugador();
            qDebug() << "Sets Imperio:" << marcador->getSetsImperio();
            QGraphicsTextItem* fin = new QGraphicsTextItem(marcador->ganador());
            fin->setDefaultTextColor(Qt::yellow);
            fin->setFont(QFont("Arial", 30, QFont::Bold));
            fin->setPos(150, 280);
            fin->setZValue(10);
            escena->addItem(fin);
            escena->update();
        } else {
            pelota->setPos(400, 300);
            pelota->setVelX(5.0f);
            pelota->setVelY(5.0f);
        }
    }

    if (pelota->x() >= 790) {
        if (marcador->getEnTieBreak())
            marcador->anotarTieJugador();
        else
            marcador->anotarJugador();
        if (marcador->hayGanador()) {
            timer->stop();
            qDebug() << "Ganador:" << marcador->ganador();
            qDebug() << "Sets jugador:" << marcador->getSetsJugador();
            qDebug() << "Sets Imperio:" << marcador->getSetsImperio();
            QGraphicsTextItem* fin = new QGraphicsTextItem(marcador->ganador());
            fin->setDefaultTextColor(Qt::yellow);
            fin->setFont(QFont("Arial", 30, QFont::Bold));
            fin->setPos(150, 280);
            fin->setZValue(10);
            escena->addItem(fin);
            escena->update();
        } else {
            pelota->setPos(400, 300);
            pelota->setVelX(-5.0f);
            pelota->setVelY(5.0f);
        }
    }

    if (teclaArriba) naveRebelde->moverArriba();
    if (teclaAbajo) naveRebelde->moverAbajo();
    naveImperial->seguirPelota(pelota);
    obstaculo->moverVertical();
}


MainWindow::~MainWindow() {}
