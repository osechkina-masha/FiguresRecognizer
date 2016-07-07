#pragma once
#include "abstractRecognizer.h"
#include "GeometricForms.h"
#include "curveKeyBuilder.h"

class MixedGesturesManager : public GesturesRecognizer<QPair<QSharedPointer<double>, QSharedPointer<double>> >
{
public:
    MixedGesturesManager();
    double getMaxDistance(QString const &);
    bool isMultistroke();
    double getDistance(QPair<QSharedPointer<double>, QSharedPointer<double>> const & key1, QPair<QSharedPointer<double>, QSharedPointer<double>> const & key2);
    QPair<QSharedPointer<double>, QSharedPointer<double>> getKey(PathVector const & path);
};

class MixedClassifier
{
public:
    MixedClassifier(const PathVector &path)
    {
        MixedGesturesManager gManager;
        mKey = gManager.getKey(path);
    }

    MixedClassifier(){}

    double getDistance(const MixedClassifier &classifier)
    {
        QPair<QSharedPointer<double>, QSharedPointer<double>> key = classifier.key();
        MixedGesturesManager gManager;
        return gManager.getDistance(key, mKey);
    }
    MixedClassifier getPoint(MixedClassifier const & centre, double centreWeight)
    {
        QSharedPointer<double> key1 = centre.key().first;
        QSharedPointer<double> key2 = centre.key().second;
        double *finalKey1 = new double[gridSize * gridSize];
        double *finalKey2 = new double[gridSize * gridSize];
        for (int i = 0; i < gridSize * gridSize; i ++)
        {
            finalKey1[i] = (key1.data()[i] * centreWeight + mKey.first.data()[i]) / (centreWeight + 1);
            finalKey2[i] = (key2.data()[i] * centreWeight + mKey.second.data()[i]) / (centreWeight + 1);
        }
        return MixedClassifier(QPair<QSharedPointer<double>, QSharedPointer<double>>(
                                   QSharedPointer<double>(finalKey1, deleteArray), QSharedPointer<double>(finalKey2, deleteArray)));
    }

    QPair<QSharedPointer<double>, QSharedPointer<double>> key() const
    {
        return mKey;
    }

private:
    MixedClassifier(QPair<QSharedPointer<double>, QSharedPointer<double>> const & key) :
        mKey(key)
    {
    }
    QPair<QSharedPointer<double>, QSharedPointer<double>> mKey;
};
