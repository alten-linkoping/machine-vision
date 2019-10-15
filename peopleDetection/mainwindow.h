#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_playButton_clicked();
    void updatePlayerUI(QImage img);

    void on_radioButton_motion_clicked();
    void on_radioButton_hog_clicked();

    void on_radioButton_cascade_clicked();

private:
    Ui::MainWindow *ui;
    Player *player;

    QString filename;
    QString detectorName;
};
#endif // MAINWINDOW_H
