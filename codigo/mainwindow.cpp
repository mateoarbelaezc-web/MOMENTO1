#include "mainwindow.h"
#include <QInputDialog>
#include <QGraphicsPixmapItem>
#include <cstdlib>
#include <ctime>
#include <cmath>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    sonido = new SonidoManager();
    sonido->reproducirMusica("qrc:/assets/musica_menu.mp3");
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0,0,800,600);
    QPixmap fondoMenu(":/assets/fondo_menu.png");
    fondoMenu = fondoMenu.scaled(800,600);
    escena->setBackgroundBrush(fondoMenu);

    vista = new QGraphicsView(escena,this);
    vista->setFixedSize(806,606);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(vista);
    setWindowTitle("Star Wars Tennis");

    // Inicializar punteros
    dificultad = nullptr;
    pelota = nullptr;
    naveRebelde = nullptr;
    naveImperial = nullptr;
    obstaculo = nullptr;
    marcador = nullptr;
    fisicaMotor = nullptr;
    teclaArriba = teclaAbajo = false;
    juegoIniciado = false;
    menuTransition = false;
    volviendo = false;

    modoActual = MODO_MENU;
    teclaA = teclaD = teclaSpace = teclaJ = false;
    jedi = nullptr;
    atat = nullptr;
    vidas = 3;
    temporizadorJuego = nullptr;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizar);

    vista->installEventFilter(this);
    vista->setFocusPolicy(Qt::StrongFocus);
    vista->setFocus();

    menu = new MenuDificultad(escena);
    menu->mostrar();
    pantallaInstrucciones = new PantallaInstrucciones(escena);
    enInstrucciones = false;
    srand(time(nullptr));
}

MainWindow::~MainWindow() {}

void MainWindow::iniciarJuego() {
    sonido->detenerMusica();
    if (dificultad->getNivel()==1) sonido->reproducirMusica("qrc:/assets/musica_facil.mp3");
    else sonido->reproducirMusica("qrc:/assets/musica_dificil.mp3");

    QPixmap fondoJuego(":/assets/fondo.png");
    fondoJuego = fondoJuego.scaled(800,600);
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

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (modoActual != MODO_MENU) return;
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
            modoActual = MODO_TENIS;
            menu->ocultar();
            iniciarJuego();
        } else if (menu->clicEnDificil(pos)) {
            dificultad = new Dificultad(2);
            modoActual = MODO_TENIS;
            menu->ocultar();
            iniciarJuego();
        } else if (menu->clicEnInstrucciones(pos)) {
            menu->ocultar();
            enInstrucciones = true;
            pantallaInstrucciones->mostrar();
        } else if (menu->clicEnJediFacil(pos)) {
            menu->ocultar();
            modoActual = MODO_JEDI;
            iniciarModoJedi(1);
        } else if (menu->clicEnJediNormal(pos)) {
            menu->ocultar();
            modoActual = MODO_JEDI;
            iniciarModoJedi(2);
        } else if (menu->clicEnJediDificil(pos)) {
            menu->ocultar();
            modoActual = MODO_JEDI;
            iniciarModoJedi(3);
        }
    } catch (const std::invalid_argument& e) {
        qDebug() << "Error:" << e.what();
    }
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (obj == vista) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (modoActual == MODO_TENIS) {
                if (keyEvent->key() == Qt::Key_Up) teclaArriba = true;
                if (keyEvent->key() == Qt::Key_Down) teclaAbajo = true;
                if (keyEvent->key() == Qt::Key_Escape) volverAlMenu();
            } else if (modoActual == MODO_JEDI) {
                if (keyEvent->key() == Qt::Key_A) {
                    teclaA = true;

                }
                if (keyEvent->key() == Qt::Key_D) teclaD = true;
                if (keyEvent->key() == Qt::Key_Space) teclaSpace = true;
                if (keyEvent->key() == Qt::Key_J) teclaJ = true;
                if (keyEvent->key() == Qt::Key_Escape) volverAlMenu();
            }
            return true;
        }
        if (event->type() == QEvent::KeyRelease) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (modoActual == MODO_TENIS) {
                if (keyEvent->key() == Qt::Key_Up) teclaArriba = false;
                if (keyEvent->key() == Qt::Key_Down) teclaAbajo = false;
            } else if (modoActual == MODO_JEDI) {
                if (keyEvent->key() == Qt::Key_A) teclaA = false;
                if (keyEvent->key() == Qt::Key_D) teclaD = false;
                if (keyEvent->key() == Qt::Key_Space) teclaSpace = false;
                if (keyEvent->key() == Qt::Key_J) teclaJ = false;
            }
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::actualizar() {
    if (modoActual == MODO_TENIS) {
        // ===== MODO TENIS ORIGINAL =====
        escena->update();
        if (!pelota) return;
        pelota->mover();
        if (pelota->y() <= 8 || pelota->y() >= 580) pelota->setVelY(-pelota->getVelY());
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
        }if (pelota->x() <= 0) {
            if (marcador->getEnTieBreak()) marcador->anotarTieImperio();
            else marcador->anotarImperio();
            sonido->reproducirEfecto("qrc:/assets/punto.wav");
            pelota->setPos(400, 300);
            pelota->setVelX(dificultad->getVelBola());
            pelota->setVelY(dificultad->getVelBola());
            if (marcador->hayGanador()) {
                timer->stop();
                escena->clear();
                pelota = nullptr; naveRebelde = nullptr;
                naveImperial = nullptr; obstaculo = nullptr; marcador = nullptr;
                QPixmap imgVictoria = (marcador == nullptr) ? QPixmap(":/assets/victoria_imperio.png") : QPixmap(":/assets/victoria_rebelde.png");
                // Siempre imperio ganó si pelota salió por izquierda
                imgVictoria = QPixmap(":/assets/victoria_imperio.png");
                imgVictoria = imgVictoria.scaled(800, 600);
                escena->setBackgroundBrush(imgVictoria);
                QTimer::singleShot(3000, this, &MainWindow::volverAlMenu);
                return;
            }
        }
        if (pelota->x() >= 790) {
            if (marcador->getEnTieBreak()) marcador->anotarTieJugador();
            else marcador->anotarJugador();
            sonido->reproducirEfecto("qrc:/assets/punto.wav");
            pelota->setPos(400, 300);
            pelota->setVelX(-dificultad->getVelBola());
            pelota->setVelY(dificultad->getVelBola());
            if (marcador->hayGanador()) {
                timer->stop();
                escena->clear();
                pelota = nullptr; naveRebelde = nullptr;
                naveImperial = nullptr; obstaculo = nullptr; marcador = nullptr;
                QPixmap imgVictoria = QPixmap(":/assets/victoria_rebelde.png");
                imgVictoria = imgVictoria.scaled(800, 600);
                escena->setBackgroundBrush(imgVictoria);
                QTimer::singleShot(3000, this, &MainWindow::volverAlMenu);
                return;
            }

            else {
                pelota->setPos(400,300);
                pelota->setVelX(-dificultad->getVelBola());
                pelota->setVelY(dificultad->getVelBola());
            }
        }
        if (teclaArriba) naveRebelde->moverArriba();
        if (teclaAbajo) naveRebelde->moverAbajo();
        if (naveImperial) naveImperial->seguirPelota(pelota);
        if (obstaculo) obstaculo->moverVertical();

    } else if (modoActual == MODO_JEDI) {
        actualizarModoJedi();
    }
}

void MainWindow::iniciarModoJedi(int nivelDificultad) {

    sonido->detenerMusica();
    sonido->reproducirMusica("qrc:/assets/musica_jedi.mp3");
    escena->clear();

    QPixmap fondo(":/assets/fondo2.png");
    if (fondo.isNull()) fondo = QPixmap(":/assets/fondo2.png");
    fondo = fondo.scaled(800,600);
    escena->setBackgroundBrush(fondo);

    QGraphicsRectItem* barrera = new QGraphicsRectItem(400, 0, 6, 520);
    barrera->setBrush(QColor(0, 180, 255, 120));
    barrera->setPen(Qt::NoPen);
    escena->addItem(barrera);

    delete dificultad;
    dificultad = new Dificultad(nivelDificultad, true);
    float maxVel = dificultad->getVelBolaJedi();

    // Jedi
    jedi = new NaveRebelde();
    jedi->setLimites(10, 400, 481);
    jedi->setModoJedi(true);
    escena->addItem(jedi);
    victoriaFlag = false;
    gameOverFlag = false;

    // AT-AT
    atat = new NaveImperial(0, 0);
    atat->setModoJedi(true, dificultad->getFactorAprendizaje());
    atat->setPosicionDisparo(630, 300);
    escena->addItem(atat);

    vidas = 15;
    tiempoRestante = dificultad->getTiempoLimite();
    multiplicadorDanio = 1.0f;
    congelacionActiva = false;
    hayBolaActiva = false;
    disparoTimer = nullptr;
    spawnTimer = nullptr;

    textoVidas = new QGraphicsTextItem("Vidas: " + QString::number(vidas));
    textoVidas->setDefaultTextColor(Qt::white);
    textoVidas->setFont(QFont("Arial",14,QFont::Bold));
    textoVidas->setPos(10,10);
    escena->addItem(textoVidas);

    textoTiempo = new QGraphicsTextItem("Tiempo: " + QString::number(tiempoRestante));
    textoTiempo->setDefaultTextColor(Qt::white);
    textoTiempo->setFont(QFont("Arial",14,QFont::Bold));
    textoTiempo->setPos(10,40);
    escena->addItem(textoTiempo);

    barraVidaAtat = new QGraphicsRectItem(0,0,200,20);
    barraVidaAtat->setBrush(Qt::green);
    barraVidaAtat->setPos(580,10);
    escena->addItem(barraVidaAtat);

    // TEXTO PARA POWER-UPS
    textoPowerUpActivo = new QGraphicsTextItem("");
    textoPowerUpActivo->setDefaultTextColor(Qt::yellow);
    textoPowerUpActivo->setFont(QFont("Arial", 12, QFont::Bold));
    textoPowerUpActivo->setPos(10, 70);
    escena->addItem(textoPowerUpActivo);

    // Temporizador cuenta regresiva
    temporizadorJuego = new QTimer(this);
    connect(temporizadorJuego, &QTimer::timeout, [this]() {
        if (modoActual == MODO_JEDI && !congelacionActiva && !victoriaFlag && !gameOverFlag) {
            tiempoRestante--;
            textoTiempo->setPlainText("Tiempo: " + QString::number(tiempoRestante));
            if (tiempoRestante <= 0) gameOver();
        }
    });
    temporizadorJuego->start(1000);

    // Generación de power-ups y penalidades
    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, [this]() {
        if (modoActual != MODO_JEDI || victoriaFlag || gameOverFlag) return;
        if ((rand() % 100) < (int)(dificultad->getFrecuenciaPowerUps() * 100)) {
            qDebug() << "Generando powerup";
            generarPowerUp();
        }
        if ((rand() % 100) < 12) {
            qDebug() << "Generando penalidad";
            generarPenalidad();
        }
    });
    spawnTimer->start(1000);

    // Disparos AT-AT
    disparoTimer = new QTimer(this);
    connect(disparoTimer, &QTimer::timeout, [this, maxVel]() {
        if (modoActual == MODO_JEDI && !congelacionActiva && !hayBolaActiva &&
            atat && atat->getVida() > 0 && vidas > 0 && !victoriaFlag && !gameOverFlag) {
            atat->procesar();
            Pelota* nuevaBola = atat->ejecutar();
            hayBolaActiva = true;
            if (nuevaBola) {
                nuevaBola->setUsarGravedad(true);
                float vx = nuevaBola->getVelX();
                float vy = nuevaBola->getVelY();
                if (fabs(vx) > maxVel) vx = (vx>0?maxVel:-maxVel);
                if (fabs(vy) > maxVel) vy = (vy>0?maxVel:-maxVel);
                nuevaBola->setVelX(vx);
                nuevaBola->setVelY(vy);
                nuevaBola->setPos(680,320);
                bolasJedi.append(nuevaBola);
                escena->addItem(nuevaBola);
            }
        }
    });
    disparoTimer->start(1500);

    vista->setFocus();
    timer->start(16);

}

void MainWindow::actualizarModoJedi() {
    // Forzar actualización para eliminar estela
    escena->update();

    if (!jedi || !atat) return;
    if (victoriaFlag || gameOverFlag) return;

    jedi->moverIzquierda(teclaA);
    jedi->moverDerecha(teclaD);
    if (teclaSpace) jedi->saltar();
    if (teclaJ) jedi->activarSwing();
    jedi->actualizarFisica();

    for (int i = 0; i < bolasJedi.size(); ++i) {
        Pelota* bola = bolasJedi[i];
        if (!bola) continue;

        bola->setFrozen(congelacionActiva);
        bola->actualizarConGravedad(0.4f, 520.0f);

        // Colisión con power-ups / penalidades (la bola los activa)
        QList<QGraphicsItem*> colisiones = bola->collidingItems();
        for (QGraphicsItem* item : colisiones) {
            if (item->data(0).toString() == "powerup") {
                aplicarPowerUp(qgraphicsitem_cast<QGraphicsPixmapItem*>(item));
                break;
            } else if (item->data(0).toString() == "penalty") {
                aplicarPenalidad(qgraphicsitem_cast<QGraphicsPixmapItem*>(item));
                break;
            }
        }

        // Golpe con sable
        if (jedi->isSwinging() && bola->collidesWithItem(jedi)) {
            sonido->reproducirEfecto("sable");
            float maxVel = dificultad->getVelBolaJedi();
            float nuevaVelX = maxVel;
            float nuevaVelY = -maxVel * 0.8f;
            float puntoImpacto = (bola->y() - jedi->y()) / jedi->boundingRect().height();
            puntoImpacto = qBound(-0.5f, puntoImpacto, 0.5f);
            nuevaVelY = -maxVel * (0.7f + puntoImpacto * 0.2f);
            bola->setVelX(nuevaVelX);
            bola->setVelY(nuevaVelY);
            bola->setDesviada(true);  // Cambio 4: marcar que el jugador la golpeó
            if (bola->x() <= jedi->x() + jedi->boundingRect().width())
                bola->setX(jedi->x() + jedi->boundingRect().width() + 5);
        }

        // Cambio borde: bola llegó al borde izquierdo sin ser desviada → desaparece sin consecuencias
        if (bola->salio()) {
            // El AT-AT NO aprende éxito: el disparo fue desperdiciado
            hayBolaActiva = false;
            escena->removeItem(bola);
            delete bola;
            bolasJedi.erase(bolasJedi.begin() + i);
            i--;
            continue;
        }

        // Daño al AT-AT: solo si la bola fue desviada por el jugador (Cambio 4)
        if (bola->collidesWithItem(atat) && bola->getVelX() > 0 && bola->isDesviada()) {
            sonido->reproducirEfecto("golpe");
            int danio = 10 * multiplicadorDanio;
            atat->recibirDanio(danio);
            float porcentaje = atat->getVida() / 200.0f;
            barraVidaAtat->setRect(0, 0, 200 * porcentaje, 20);
            if (porcentaje < 0.3) barraVidaAtat->setBrush(Qt::red);
            else if (porcentaje < 0.6) barraVidaAtat->setBrush(Qt::yellow);
            else barraVidaAtat->setBrush(Qt::green);
            hayBolaActiva = false;
            escena->removeItem(bola);
            delete bola;
            bolasJedi.erase(bolasJedi.begin() + i);
            i--;
            if (atat->getVida() <= 0) {
                qDebug() << "AT-AT destruido, llamando victoria()";
                victoria();
                return;
            }
            continue;
        }

        // Muerte por rebote
        if (bola->isDead()) {
            if (vidas > 0) {
                vidas--;
                textoVidas->setPlainText("Vidas: " + QString::number(vidas));
                if (atat) atat->aprender(true, atat->getTipoSeleccionado());
            }
            hayBolaActiva = false;
            escena->removeItem(bola);
            delete bola;
            bolasJedi.erase(bolasJedi.begin() + i);
            i--;
            if (vidas <= 0) {
                qDebug() << "Vidas 0, llamando gameOver()";
                gameOver();
                return;
            }
            continue;
        }

        // Limpieza fuera de pantalla
        if (bola->x() < -100 || bola->x() > 900 || bola->y() < -100 || bola->y() > 700) {
            // Cambio 2: disparo fallido, el agente debe aprenderlo
            if (atat) atat->aprender(false, atat->getTipoSeleccionado());
            hayBolaActiva = false;
            escena->removeItem(bola);
            delete bola;
            bolasJedi.erase(bolasJedi.begin() + i);
            i--;
        }
    }
}


void MainWindow::generarPowerUp() {
    QGraphicsPixmapItem* power = new QGraphicsPixmapItem(QPixmap(":/assets/pelota2.png").scaled(30,30));
    power->setPos(rand() % 600 + 100, rand() % 250 + 150);
    power->setData(0, "powerup");
    escena->addItem(power);
    QTimer::singleShot(8000, this, [this]() {
        if (modoActual != MODO_JEDI) return;
        for (QGraphicsItem* item : escena->items()) {
            if (item->data(0).toString() == "powerup") {
                escena->removeItem(item);
                delete item;
                break;
            }
        }
    });
}

void MainWindow::generarPenalidad() {
    QGraphicsPixmapItem* penalty = new QGraphicsPixmapItem(QPixmap(":/assets/pelota2.png").scaled(30,30));
    penalty->setPos(rand() % 600 + 100, rand() % 250 + 150);
    penalty->setData(0, "penalty");
    escena->addItem(penalty);
    QTimer::singleShot(8000, this, [this]() {
        if (modoActual != MODO_JEDI) return;
        for (QGraphicsItem* item : escena->items()) {
            if (item->data(0).toString() == "penalty") {
                escena->removeItem(item);
                delete item;
                break;
            }
        }
    });
}

void MainWindow::aplicarPowerUp(QGraphicsPixmapItem* power) {
    if (power && power->scene() == escena) {
        escena->removeItem(power);
        delete power;
    }
    if (modoActual != MODO_JEDI || victoriaFlag || gameOverFlag) return;
    if (!atat || !jedi) return;

    if (rand() % 2 == 0) {
        multiplicadorDanio = 2.0f;
        atat->setMultiplicadorDanio(multiplicadorDanio);
        if (textoPowerUpActivo) textoPowerUpActivo->setPlainText("¡POWER-UP! Daño x2 (10s)");
        QTimer::singleShot(10000, this, [this]() {
            if (modoActual != MODO_JEDI || victoriaFlag || gameOverFlag) return;
            multiplicadorDanio = 1.0f;
            if (atat) atat->setMultiplicadorDanio(1.0f);
            if (textoPowerUpActivo) textoPowerUpActivo->setPlainText("");
        });
    } else {
        congelacionActiva = true;
        if (textoPowerUpActivo) textoPowerUpActivo->setPlainText("¡POWER-UP! Congelación (5s)");
        for (Pelota* bola : bolasJedi) if (bola) bola->setFrozen(true);
        QTimer::singleShot(5000, this, [this]() {
            if (modoActual != MODO_JEDI || victoriaFlag || gameOverFlag) return;
            congelacionActiva = false;
            for (Pelota* bola : bolasJedi) if (bola) bola->setFrozen(false);
            if (textoPowerUpActivo) textoPowerUpActivo->setPlainText("");
        });
    }
}

void MainWindow::aplicarPenalidad(QGraphicsPixmapItem* penalty) {
    if (penalty && penalty->scene() == escena) {
        escena->removeItem(penalty);
        delete penalty;
    }
    if (modoActual != MODO_JEDI || victoriaFlag || gameOverFlag) return;
    if (!jedi) return;

    if (rand() % 2 == 0) {
        jedi->setMultiplicadorVelocidad(0.5f);
        if (textoPowerUpActivo) textoPowerUpActivo->setPlainText("¡PENALIDAD! Lentitud (5s)");
        QTimer::singleShot(5000, this, [this]() {
            if (modoActual != MODO_JEDI || victoriaFlag || gameOverFlag) return;
            if (jedi) jedi->setMultiplicadorVelocidad(1.0f);
            if (textoPowerUpActivo) textoPowerUpActivo->setPlainText("");
        });
    } else {
        for (Pelota* bola : bolasJedi) if (bola) {
                bola->setVelX(bola->getVelX() * 1.5f);
                bola->setVelY(bola->getVelY() * 1.5f);
            }
        if (textoPowerUpActivo) textoPowerUpActivo->setPlainText("¡PENALIDAD! Velocidad extrema");
        QTimer::singleShot(5000, this, [this]() {
            if (modoActual != MODO_JEDI || victoriaFlag || gameOverFlag) return;
            if (textoPowerUpActivo) textoPowerUpActivo->setPlainText("");
        });
    }
}
void MainWindow::victoria() {
    qDebug() << "victoria() - INICIO, victoriaFlag=" << victoriaFlag;
    if (victoriaFlag) return;
    victoriaFlag = true;

    qDebug() << "victoria() - deteniendo disparoTimer";
    if (disparoTimer) { disparoTimer->stop(); delete disparoTimer; disparoTimer = nullptr; }
    qDebug() << "victoria() - deteniendo spawnTimer";
    if (spawnTimer) { spawnTimer->stop(); delete spawnTimer; spawnTimer = nullptr; }
    qDebug() << "victoria() - deteniendo temporizadorJuego";
    if (temporizadorJuego) { temporizadorJuego->stop(); delete temporizadorJuego; temporizadorJuego = nullptr; }
    qDebug() << "victoria() - deteniendo timer principal";
    timer->stop();

    qDebug() << "victoria() - limpiando bolasJedi, cantidad=" << bolasJedi.size();
    for (Pelota* b : bolasJedi) { if (b) { escena->removeItem(b); delete b; } }
    bolasJedi.clear();

    qDebug() << "victoria() - limpiando escena";
    escena->clear();
    jedi = nullptr; atat = nullptr;
    textoVidas = nullptr; textoTiempo = nullptr;
    barraVidaAtat = nullptr; textoPowerUpActivo = nullptr;

    qDebug() << "victoria() - cargando imagen";
    QPixmap imgVictoria(":/assets/victoria_rebelde.png");
    if (imgVictoria.isNull()) {
        qDebug() << "ERROR: victoria_rebelde.png no encontrada";
        imgVictoria = QPixmap(800,600);
        imgVictoria.fill(Qt::green);
    }
    imgVictoria = imgVictoria.scaled(800,600);
    escena->setBackgroundBrush(imgVictoria);

    qDebug() << "victoria() - programando volverAlMenu en 3s";
    QTimer::singleShot(3000, this, &MainWindow::volverAlMenu);
    qDebug() << "victoria() - FIN";
}

void MainWindow::gameOver() {
    qDebug() << "gameOver() - INICIO";
    if (gameOverFlag) return;
    gameOverFlag = true;

    // Detener y eliminar todos los timers
    if (disparoTimer) {
        disparoTimer->stop();
        delete disparoTimer;
        disparoTimer = nullptr;
    }
    if (spawnTimer) {
        spawnTimer->stop();
        delete spawnTimer;
        spawnTimer = nullptr;
    }
    if (temporizadorJuego) {
        temporizadorJuego->stop();
        delete temporizadorJuego;
        temporizadorJuego = nullptr;
    }
    timer->stop();

    escena->clear();

    QPixmap imgDerrota(":/assets/victoria_imperio.png");
    if (imgDerrota.isNull()) {
        qDebug() << "ERROR: victoria_imperio.png no encontrada";
        imgDerrota = QPixmap(800,600);
        imgDerrota.fill(Qt::red);
    }
    imgDerrota = imgDerrota.scaled(800,600);
    escena->setBackgroundBrush(imgDerrota);

    QTimer::singleShot(3000, this, &MainWindow::volverAlMenu);
}

void MainWindow::volverAlMenu() {
    if (volviendo) return;
    volviendo = true;

    timer->stop();

    textoPowerUpActivo = nullptr;
    textoVidas = nullptr;
    textoTiempo = nullptr;
    barraVidaAtat = nullptr;
    pelota = nullptr;
    naveRebelde = nullptr;
    naveImperial = nullptr;
    obstaculo = nullptr;
    marcador = nullptr;
    fisicaMotor = nullptr;
    jedi = nullptr;
    atat = nullptr;
    bolasJedi.clear();

    escena->clear();

    delete dificultad;
    dificultad = nullptr;

    juegoIniciado = false;
    modoActual = MODO_MENU;
    victoriaFlag = false;
    gameOverFlag = false;

    sonido->detenerMusica();
    sonido->reproducirMusica("qrc:/assets/musica_menu.mp3");

    QPixmap fondoMenu(":/assets/fondo_menu.png");
    if (fondoMenu.isNull()) {
        fondoMenu = QPixmap(800,600);
        fondoMenu.fill(Qt::black);
    }
    escena->setBackgroundBrush(fondoMenu.scaled(800,600));

    menu = new MenuDificultad(escena);
    menu->mostrar();
    pantallaInstrucciones = new PantallaInstrucciones(escena);
    enInstrucciones = false;

    vista->setFocus();
    volviendo = false;
}
