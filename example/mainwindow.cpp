#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->fancyTabBar->addFancyTab(QIcon(":/img/information.svg"), "Information");
    ui->fancyTabBar->addFancyTab(QIcon(":/img/network.svg"), "Network");
    ui->fancyTabBar->addFancyTab(QIcon(":/img/settings.svg"), "Settings");
    ui->fancyTabBar->setActiveIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
