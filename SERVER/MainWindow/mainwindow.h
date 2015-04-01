#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <capturesendframe.h>
#include <transfercmd.h>

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
    CaptureSendFrame *csf;
    CaptureThread *cap_thr;
    SendThread *send_thr;
    TransferCmd *tfc;
};

#endif // MAINWINDOW_H
