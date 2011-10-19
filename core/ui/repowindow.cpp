#include "repowindow.h"
#include "ui_repowindow.h"

RepoWindow::RepoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RepoWindow)
{
    ui->setupUi(this);
}

RepoWindow::~RepoWindow()
{
    delete ui;
}
