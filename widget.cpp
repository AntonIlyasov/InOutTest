#include "widget.h"
#include "ui_widget.h"
#include <iostream>
#include <math.h>

// --------------------------
// Set stop time here
// --------------------------
#define ENDOFTIME 100
#define SAMPLINGTIMEMSEC 10
// --------------------------
// Set stop time here
// --------------------------

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Create dir for logs
    if (!QDir("logs").exists()) {
        QDir().mkdir("logs");
    }

    // Set window size
    this->setMinimumSize(640, 480);

    // Add main layout with two plots
    mainlayout = new QGridLayout(this);
    generatorContinuousPlot = new QCustomPlot(this);
    generatorDiscretePlot = new QCustomPlot(this);
    plantContinuousPlot = new QCustomPlot(this);
    plantDiscretePlot = new QCustomPlot(this);

    mainlayout->addWidget(generatorContinuousPlot, 0, 0);
    mainlayout->addWidget(generatorDiscretePlot, 1, 0);
    mainlayout->addWidget(plantContinuousPlot, 0, 1);
    mainlayout->addWidget(plantDiscretePlot, 1, 1);

    generatorContinuousPlot->addGraph();
    generatorDiscretePlot->addGraph();

    plantContinuousPlot->addGraph();
    plantDiscretePlot->addGraph();

    startButton = new QPushButton("Start");
    connect(startButton, &QPushButton::clicked, this, [=](){
        startTime = 0;
        relativeTime = 0;
        lastTime = 0;
        generatorContinuousPlot->graph(0)->data()->clear();
        generatorDiscretePlot->graph(0)->data()->clear();

        plantContinuousPlot->graph(0)->data()->clear();
        plantDiscretePlot->graph(0)->data()->clear();
        timer->start();
    });
    mainlayout->addWidget(startButton, 2, 0);

    saveButton = new QPushButton("Save");
    connect(saveButton, &QPushButton::clicked, this, [=](){
        QString timestamp = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
        generatorContinuousPlot->savePng(QString("./logs/%1_continuousGenerator.png").arg(timestamp));
        generatorDiscretePlot->savePng(QString("./logs/%1_discreteGenerator.png").arg(timestamp));

        plantContinuousPlot->savePng(QString("./logs/%1_continuousPlot.png").arg(timestamp));
        plantDiscretePlot->savePng(QString("./logs/%1_discretePlot.png").arg(timestamp));
    });
    mainlayout->addWidget(saveButton, 2, 1);

    // Give the axes some labels:
    generatorContinuousPlot->xAxis->setLabel("t");
    generatorContinuousPlot->yAxis->setLabel("Continuous generator");
    plantContinuousPlot->xAxis->setLabel("t");
    plantContinuousPlot->yAxis->setLabel("Continuous plant");

    generatorDiscretePlot->xAxis->setLabel("t");
    generatorDiscretePlot->yAxis->setLabel("Discrete generator");
    plantDiscretePlot->xAxis->setLabel("t");
    plantDiscretePlot->yAxis->setLabel("Discrete plant");

    // --------------------------
    // Change ranges if you need
    // --------------------------
    // Set axes ranges so see all data:
    generatorContinuousPlot->xAxis->setRange(0, ENDOFTIME);
    generatorContinuousPlot->yAxis->setRange(-3, 3);
    plantContinuousPlot->xAxis->setRange(0, ENDOFTIME);
    plantContinuousPlot->yAxis->setRange(-180, 180);


    generatorDiscretePlot->xAxis->setRange(0, ENDOFTIME);
    generatorDiscretePlot->yAxis->setRange(-3, 3);
    plantDiscretePlot->xAxis->setRange(0, ENDOFTIME);
    plantDiscretePlot->yAxis->setRange(-3, 3);

    // --------------------------
    // Create the object here
    // --------------------------
    object = new gain(2.0);
//    integrator = new Integrator(-1.0);
    plant = new Plant();
    plantDiscrete = new PlantDiscrete();
    // --------------------------
    // Create the object here
    // --------------------------

    timer = new QTimer(this);
    timer->setTimerType(Qt::TimerType::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // --------------------------
    // Set sampling time here
    // --------------------------
    timer->setInterval(SAMPLINGTIMEMSEC);
    // --------------------------
    // Set sampling time here
    // --------------------------
}

Widget::~Widget()
{
    delete ui;
    delete generatorContinuousPlot;
    delete generatorDiscretePlot;
    delete plantContinuousPlot;
    delete plantDiscretePlot;
    delete timer;
    delete mainlayout;

    // --------------------------
    // Delete the object here
    // --------------------------
    delete object;
//    delete integrator;
    delete plant;
    delete plantDiscrete;
    // --------------------------
    // Delete the object here
    // --------------------------
}

void Widget::update() {

    // --------------------------
    // Replace input signal with ours
    // --------------------------
    double signal = std::sin(relativeTime / 1000.0);
    // --------------------------
    // Replace input signal with ours
    // --------------------------

    // --------------------------
    // Plot current continuous values here
    // --------------------------

    generatorContinuousPlot->graph(0)->addData(relativeTime / 1000.0, signal);
//    plantContinuousPlot->graph(0)->addData(relativeTime / 1000.0, integrator->update(signal, 0.01));
//    plantContinuousPlot->graph(0)->addData(relativeTime / 1000.0, plant->update(signal, 0.01));

    //discrete
    plantContinuousPlot->graph(0)->addData(relativeTime / 1000.0, plantDiscrete->update(signal));
    //discrete


    generatorContinuousPlot->replot();
    plantContinuousPlot->replot();

    // --------------------------
    // Plot current discrete values here
    // --------------------------

    //generatorContinuousPlot->graph(0)->addData(relativeTime / 1000.0, signal);
    //plantContinuousPlot->graph(0)->addData(relativeTime / 1000.0, 1);

//    generatorContinuousPlot->replot();
//    plantContinuousPlot->replot();


    if (startTime == 0) {
        // First step only plot initial values
        startTime = QDateTime::currentMSecsSinceEpoch();
        return;
    } else {
        lastTime = relativeTime;
        relativeTime = QDateTime::currentMSecsSinceEpoch() - startTime;
        dt = relativeTime - lastTime;
    }


    // --------------------------
    // Update the object here
    // --------------------------
//    object->update(signal);                                   // comment
    //integrator->update(signal, 0.01);
    // --------------------------
    // Update the object here
    // --------------------------

    if (relativeTime / 1000.0 > ENDOFTIME) {
        timer->blockSignals(true);
        timer->stop();
        timer->blockSignals(false);
    }
}
