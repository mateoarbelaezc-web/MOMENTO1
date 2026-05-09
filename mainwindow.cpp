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

    // Inicializar punteros en null
    dificultad = nullptr;
    pelota = nullptr;
    naveRebelde = nullptr;
    naveImperial = nullptr;
    obstaculo = nullptr;
    marcador = nullptr;
    fisicaMotor = nullptr;

    teclaArriba = false;
    teclaAbajo = false;
    juegoIniciado = false;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizar);

    vista->installEventFilter(this);
    vista->setFocusPolicy(Qt::StrongFocus);
    vista->setFocus();

    menu = new MenuDificultad(escena);
    menu->mostrar();
}

void MainWindow::iniciarJuego() {
    pelota = new Pelota();
    pelota->setVelX(dificultad->getVelBola());
    pelota->setVelY(dificultad->getVelBola());
    escena->addItem(pelota);

    naveRebelde = new NaveRebelde();
    escena->addItem(naveRebelde);

    naveImperial = new NaveImperial(dificultad->getVelEnemigo(), dificultad->getMargenError());
    escena->addItem(naveImperial);

    obstaculo = new Obstaculo(dificultad->getVelObstaculo());
    escena->addItem(obstaculo);

    marcador = new Marcador(dificultad->getGamesParaGanar());
    escena->addItem(marcador);

    fisicaMotor = new FisicaMotor();

    timer->start(16);
}

MainWindow::~MainWindow() {}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (!juegoIniciado) {
        QPointF pos = vista->mapToScene(event->pos());
        try {
            if (menu->clicEnFacil(pos)) {
                dificultad = new Dificultad(1);
                menu->ocultar();
                juegoIniciado = true;
                iniciarJuego();
            } else if (menu->clicEnDificil(pos)) {
                dificultad = new Dificultad(2);
                menu->ocultar();
                juegoIniciado = true;
                iniciarJuego();
            }
        } catch (const std::invalid_argument& e) {
            qDebug() << "Error de dificultad:" << e.what();
        }
    }
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (obj == vista) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Up) teclaArriba = true;
            if (keyEvent->key() == Qt::Key_Down) teclaAbajo = true;
            if (keyEvent->key() == Qt::Key_Escape) volverAlMenu();
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

    if (pelota->y() <= 8 || pelota->y() >= 580)
        pelota->setVelY(-pelota->getVelY());

    if (pelota->collidesWithItem(naveRebelde)) {
        pelota->setVelX(qAbs(pelota->getVelX()));
        fisicaMotor->aplicarAnguloImpacto(pelota, naveRebelde->y(), 80.0f, dificultad->getVelBola());
    }

    if (pelota->collidesWithItem(naveImperial)) {
        pelota->setVelX(-qAbs(pelota->getVelX()));
        fisicaMotor->aplicarAnguloImpacto(pelota, naveImperial->y(), 80.0f, dificultad->getVelBola());
    }

    if (pelota->collidesWithItem(obstaculo)) {
        float rango = (dificultad->getNivel() == 1) ? 400.0f : 850.0f;
        float desvio = ((rand() % (int)rango) - rango/2) / 100.0f;
        pelota->setVelY(pelota->getVelY() + desvio);
    }

    if (pelota->x() <= 0) {
        if (marcador->getEnTieBreak())
            marcador->anotarTieImperio();
        else
            marcador->anotarImperio();
        if (marcador->hayGanador()) {
            timer->stop();
            QGraphicsTextItem* fin = new QGraphicsTextItem(marcador->ganador());
            fin->setDefaultTextColor(Qt::yellow);
            fin->setFont(QFont("Arial", 30, QFont::Bold));
            fin->setPos(150, 280);
            fin->setZValue(10);
            escena->addItem(fin);
            escena->update();
        } else {
            pelota->setPos(400, 300);
            pelota->setVelX(dificultad->getVelBola());
            pelota->setVelY(dificultad->getVelBola());
        }
    }

    if (pelota->x() >= 790) {
        if (marcador->getEnTieBreak())
            marcador->anotarTieJugador();
        else
            marcador->anotarJugador();
        if (marcador->hayGanador()) {
            timer->stop();
            QGraphicsTextItem* fin = new QGraphicsTextItem(marcador->ganador());
            fin->setDefaultTextColor(Qt::yellow);
            fin->setFont(QFont("Arial", 30, QFont::Bold));
            fin->setPos(150, 280);
            fin->setZValue(10);
            escena->addItem(fin);
            escena->update();
        } else {
            pelota->setPos(400, 300);
            pelota->setVelX(-dificultad->getVelBola());
            pelota->setVelY(dificultad->getVelBola());
        }
    }

    if (teclaArriba) naveRebelde->moverArriba();
    if (teclaAbajo) naveRebelde->moverAbajo();
    naveImperial->seguirPelota(pelota);
    obstaculo->moverVertical();
}

void MainWindow::volverAlMenu() {
    timer->stop();
    escena->clear();
    juegoIniciado = false;

    pelota = nullptr;
    naveRebelde = nullptr;
    naveImperial = nullptr;
    obstaculo = nullptr;
    marcador = nullptr;
    fisicaMotor = nullptr;
    dificultad = nullptr;

    menu = new MenuDificultad(escena);
    menu->mostrar();
}
