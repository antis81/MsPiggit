#ifndef REPOWINDOW_H
#define REPOWINDOW_H

#include <QMainWindow>

namespace Ui {
    class RepoWindow;
}

class RepoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RepoWindow(QWidget *parent = 0);
    ~RepoWindow();

private:
    Ui::RepoWindow *ui;
};

#endif // REPOWINDOW_H
