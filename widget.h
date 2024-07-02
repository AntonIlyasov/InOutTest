#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QDateTime>
#include "qcustomplot.h"
#include "blocks/gain/gain.h"
#include "blocks/integrator/integrator.h"
#include "blocks/plant/plant.h"
#include "blocks/plantDiscrete/plantdiscrete.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void update();

private:
    Ui::Widget* ui;
    QGridLayout* mainlayout;

    QCustomPlot* generatorContinuousPlot;
    QCustomPlot* generatorDiscretePlot;

    QCustomPlot* plantContinuousPlot;
    QCustomPlot* plantDiscretePlot;

    QPushButton* startButton;
    QPushButton* saveButton;

    qint64 startTime = 0;
    qint64 relativeTime = 0;
    qint64 lastTime = 0;
    qint64 dt;

    QTimer* timer;

    // --------------------------
    // Add pointer to the object here
    // --------------------------
    gain* object;   // <=
//    Integrator* integrator;
    Plant* plant;
    PlantDiscrete* plantDiscrete;
    // --------------------------
    // Add pointer to the object here
    // --------------------------
};

#endif // WIDGET_H
