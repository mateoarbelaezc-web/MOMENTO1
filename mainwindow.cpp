#include "mainwindow.h"
#include <QEvent>
#include <QDebug>
#include <QFont>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    sonido = new SonidoManager();
    sonido->reproducirMusica("qrc:/assets/musica_menu.mp3");
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 800, 600);
    QPixmap fondoMenu(":/assets/fondo_menu.png");
    fondoMenu = fondoMenu.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    escena->setBackgroundBrush(fondoMenu);


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

    pantallaInstrucciones = new PantallaInstrucciones(escena);
    enInstrucciones = false;
}

void MainWindow::iniciarJuego() {
    sonido->detenerMusica();
    if (dificultad->getNivel() == 1)
        sonido->reproducirMusica("qrc:/assets/musica_facil.mp3");
    else
        sonido->reproducirMusica("qrc:/assets/musica_dificil.mp3");
    QPixmap fondoJuego(":/assets/fondo.png");
    fondoJuego = fondoJuego.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    escena->setBackgroundBrush(fondoJuego);
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
        if (enInstrucciones) {
            if (pantallaInstrucciones->clicEnVolver(pos)) {
                pantallaInstrucciones->ocultar();
                enInstrucciones = false;
                menu->mostrar();
            }
            return;
        }
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
            } else if (menu->clicEnInstrucciones(pos)) {
                menu->ocultar();
                enInstrucciones = true;
                pantallaInstrucciones->mostrar();
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
        sonido->reproducirEfecto("qrc:/assets/golpe.wav");
        pelota->setVelX(qAbs(pelota->getVelX()));
        fisicaMotor->aplicarAnguloImpacto(pelota, naveRebelde->y(), naveRebelde->boundingRect().height(), dificultad->getVelBola());
        if (pelota->getVelY() > 3.0f) pelota->setVelY(-pelota->getVelY());
    }

    if (pelota->collidesWithItem(naveImperial)) {
        sonido->reproducirEfecto("qrc:/assets/golpe.wav");
        pelota->setVelX(-qAbs(pelota->getVelX()));
        fisicaMotor->aplicarAnguloImpacto(pelota, naveImperial->y(), naveImperial->boundingRect().height(), dificultad->getVelBola());
        if (pelota->getVelY() > 3.0f) pelota->setVelY(-pelota->getVelY());
    }

    if (pelota->collidesWithItem(obstaculo)) {
        sonido->reproducirEfecto("qrc:/assets/gravedad.wav");
        float rango = (dificultad->getNivel() == 1) ? 400.0f : 1200.0f;
        float desvio = ((rand() % (int)rango) - rango/2) / 100.0f;
        pelota->setVelY(pelota->getVelY() + desvio);
    }

    if (pelota->x() <= 0) {
        if (marcador->getEnTieBreak()) {
            marcador->anotarTieImperio();
            sonido->reproducirEfecto("qrc:/assets/punto.wav");
        } else {
            marcador->anotarImperio();
            sonido->reproducirEfecto("qrc:/assets/punto.wav");
        }
        if (marcador->hayGanador()) {
            timer->stop();
            escena->clear();
            QPixmap imgVictoria;
            if (marcador->getSetsJugador() >= 1)
                imgVictoria = QPixmap(":/assets/victoria_rebelde.png");
            else
                imgVictoria = QPixmap(":/assets/victoria_imperio.png");
            imgVictoria = imgVictoria.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            escena->setBackgroundBrush(imgVictoria);
            escena->update();
            return; // agregar esto en ambos bloques
        } else {
            pelota->setPos(400, 300);
            pelota->setVelX(dificultad->getVelBola());
            pelota->setVelY(dificultad->getVelBola());
        }
    }

    if (pelota->x() >= 790) {
        if (marcador->getEnTieBreak()) {
            marcador->anotarTieJugador();
            sonido->reproducirEfecto("qrc:/assets/punto.wav");
        } else {
            marcador->anotarJugador();
            sonido->reproducirEfecto("qrc:/assets/punto.wav");
        }
        if (marcador->hayGanador()) {
            timer->stop();
            escena->clear();
            QPixmap imgVictoria;
            if (marcador->getSetsJugador() >= 1)
                imgVictoria = QPixmap(":/assets/victoria_rebelde.png");
            else
                imgVictoria = QPixmap(":/assets/victoria_imperio.png");
            imgVictoria = imgVictoria.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            escena->setBackgroundBrush(imgVictoria);
            escena->update();
            return; // agregar esto en ambos bloques
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

    // Poner el fondo DESPUÉS de clear()
    sonido->detenerMusica();
    sonido->reproducirMusica("qrc:/assets/musica_menu.mp3");
    QPixmap fondoMenu(":/assets/fondo_menu.png");
    fondoMenu = fondoMenu.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    escena->setBackgroundBrush(fondoMenu);

    menu = new MenuDificultad(escena);
    menu->mostrar();
    pantallaInstrucciones = new PantallaInstrucciones(escena);
    enInstrucciones = false;
}
