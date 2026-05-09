#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 800, 600);
    escena->setBackgroundBrush(Qt::black);

    vista = new QGraphicsView(escena, this);
    vista->setFixedSize(800, 600);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(vista);
    setWindowTitle("Tenis Star Wars");
}

MainWindow::~MainWindow() {}
