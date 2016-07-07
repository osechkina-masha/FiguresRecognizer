#pragma once
#include "abstractRecognizer.h"
#include "GeometricForms.h"

class SumGesturesManager : public GesturesRecognizer<QSharedPointer<double>>
{
public:
    SumGesturesManager() {
    qDebug() << "SumGesturesManager initialized";}
    double getMaxDistance(QString const &);
    bool isMultistroke();
    double getDistance(QSharedPointer<double> const & key1, QSharedPointer<double> const & key2);
    QSharedPointer<double> getKey(PathVector const & path);
};
