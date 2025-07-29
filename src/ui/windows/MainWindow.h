//
// Created by shingesa on 29/07/25.
//
#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>


class MainWindow: public QMainWindow{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUi();
};



#endif //MAINWINDOW_H
