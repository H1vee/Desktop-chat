//
// Created by shingesa on 29/07/25.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent) {
    setupUi();
}

MainWindow::~MainWindow() = default;


void MainWindow::setupUi() {

    setWindowTitle("Custom Chat");
    resize(1000, 700);
}