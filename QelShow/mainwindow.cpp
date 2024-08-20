#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    p_stacked_widget_(new QStackedWidget(this)),
    p_button_page_(new ButtonPage(this))
{
    this->setFixedSize(800, 600);
    this->setCentralWidget(p_stacked_widget_);
    p_stacked_widget_->addWidget(p_button_page_);
    p_stacked_widget_->setCurrentWidget(p_button_page_);
}

MainWindow::~MainWindow()
{
    delete ui;
}
