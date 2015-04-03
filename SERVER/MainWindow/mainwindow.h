#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <transfercmd.h>
#include <transferframe.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    TransferCmd::TransferCmd *transfer_cmd;
    TransferFrame::TransferFrame *transfer_frame;
};

#endif // MAINWINDOW_H
