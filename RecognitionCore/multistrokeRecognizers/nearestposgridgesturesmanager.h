#pragma once
#include "abstractRecognizer.h"
#include "GeometricForms.h"

class NearestPosGridGesturesManager : public GesturesRecognizer<QSharedPointer<double>>
{
public:
    NearestPosGridGesturesManager();
    double getMaxDistance(QString const &);
    bool isMultistroke();
    double getDistance(QSharedPointer<double> const &key1, QSharedPointer<double> const &key2);
    QSharedPointer<double> getKey(PathVector const & path);
};
