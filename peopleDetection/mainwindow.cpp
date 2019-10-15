#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    player = new Player();
    QObject::connect(player, SIGNAL(processedImage(QImage)),
                     this, SLOT(updatePlayerUI(QImage)));

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}


void MainWindow::on_loadButton_clicked()
{
    this->filename = QFileDialog::getOpenFileName(this,
                                              tr("Open Video"), ".",
                                              tr("Video Files (*.avi *.mpg *.mp4)"));

    if (!this->filename.isEmpty()){
            if (!player->loadVideo(this->filename.toLatin1().data()))
            {
                QMessageBox msgBox;
                msgBox.setText("The selected video could not be opened!");
                msgBox.exec();
            }
        }
}

void MainWindow::on_playButton_clicked()
{
    if (!this->detectorName.isEmpty())
        if (!this->filename.isEmpty())
        {
            if (player->isStopped())
            {
                player->Play();
                ui->playButton->setText(tr("Stop"));
            }else
            {
                    player->Stop();
                    ui->playButton->setText(tr("Play"));
            }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Select video first!");
            msgBox.exec();
        }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Select detection method first!");
        msgBox.exec();
    }
}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->videoWindow->setAlignment(Qt::AlignCenter);
        ui->videoWindow->setPixmap(QPixmap::fromImage(img).scaled(ui->videoWindow->size(),
                                                                  Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::on_radioButton_motion_clicked()
{
    this->detectorName = "Motion";
    player->setDetector(this->detectorName);
}

void MainWindow::on_radioButton_hog_clicked()
{
    this->detectorName = "HOG";
    player->setDetector(this->detectorName);
}

void MainWindow::on_radioButton_cascade_clicked()
{
    this->detectorName = "Cascade";
    player->setDetector(this->detectorName);
}
