#include "mainwindow.h"
#include "ui_mainwindow.h"

// QT includes
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QFileDialog>

// STL includes
#include <vector>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&this->kbtracker,SIGNAL(errorMessage(QString)), ui->error_label, SLOT(setText(QString)));

    connect(&kbtracker, SIGNAL(setStitchedImage(QPixmap)),ui->result_final,SLOT(setPixmap(QPixmap)));

    connect(ui->load_calib, SIGNAL(clicked(bool)), &this->kbtracker, SLOT(loadCalibration()));

    connect(ui->run, SIGNAL(clicked(bool)), &this->kbtracker, SLOT(startLoop()));

    connect(ui->find_kb, SIGNAL(clicked(bool)), &this->kbtracker, SLOT(findKilobots()));

    connect(ui->lineEdit, SIGNAL(editingFinished()), &this->kbtracker, SLOT(setCamOrder()));

    connect(ui->cam_radio, SIGNAL(toggled(bool)), &this->kbtracker, SLOT(setSourceType(bool)));

    connect(ui->sel_video, SIGNAL(clicked(bool)), this, SLOT(setVideoSource()));

    connect(ui->houghAcc_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setHoughAcc(int)));
    connect(ui->cannyThresh_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setCannyThresh(int)));
    connect(ui->kbMax_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setKbMax(int)));
    connect(ui->kbMin_slider, SIGNAL(valueChanged(int)), &this->kbtracker, SLOT(setKbMin(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setVideoSource()
{

    QSettings settings;
    QString lastDir = settings.value("videoLastDir", QDir::homePath()).toString();
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Set the video source"), lastDir);

    if (dirName.isEmpty()) {
        ui->error_label->setText("No path selected");
    }

    // set dir
    this->kbtracker.setVideoDir(dirName);
    ui->vid_path->setText(dirName);
    ui->vid_path->setToolTip(dirName);
    settings.setValue ("videoLastDir", dirName);
}

