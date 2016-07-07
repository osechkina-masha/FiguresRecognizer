#pragma once

#include <QMainWindow>
#include <QFileDialog>
#include <QApplication>
#include "xmlparser.h"
#include "abstractRecognizer.h"
#include "NeuralNetwork/neuralnetwork.h"
#include "multistrokeRecognizers/adaBoostManager.h"

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = 0);
    ~TestWindow();

private:
    Ui::TestWindow *ui;
    QSharedPointer<RecognizerInterface> getGesturesManager();
    template <typename T>
    void trainGesturesManager(const QSharedPointer<TrainingGesturesManager<T>> &trainingGesturesManager)
    {
        QString trainingFile = QFileDialog::getOpenFileName(this, tr("Open Xml"), "",
                                                            tr("Xml files (*.xml)"));
        QMap<QString, UsersGestures> gestures = XmlParser::parseXml(trainingFile);
        foreach (QString object, gestures.keys())
        {
            UsersGestures paths = gestures[object];
            trainingGesturesManager->learn(object, paths.first);
            foreach (QString path, paths.second)
            {
                QApplication::processEvents();
                qDebug() << "new gesture";
                PathVector gesture = stringToPath(path);
                //if (!trainingGesturesManager->belong(object, gesture))
                trainingGesturesManager->learn(object, gesture);
            }
        }
        qDebug() << "learnt";
    }

private slots:
    void test();
    void printData(int, int, int);
};

