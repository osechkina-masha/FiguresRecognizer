#include "mixedgesturesmanager.h"
#include "rectanglegesturesmanager.h"
#include "nearestposgridgesturesmanager.h"
#include "curveKeyBuilder.h"

const double weight1 = 0.2; //0.3: 891 0.2: 899
const double weight2 = 1 - weight1;

MixedGesturesManager::MixedGesturesManager()
{
}

double MixedGesturesManager::getMaxDistance(QString const &)
{
    return 1000;
}
bool MixedGesturesManager::isMultistroke()
{
    return true;
}

double MixedGesturesManager::getDistance(QPair<QSharedPointer<double>,QSharedPointer<double>> const & key1,
                                         QPair<QSharedPointer<double>, QSharedPointer<double>> const & key2)
{
    double dist1 = RectangleGesturesManager().getDistance(key1.first, key2.first);
    double dist2 = NearestPosGridGesturesManager().getDistance(key1.second, key2.second);
    return dist1 * weight1 + dist2 * weight2;
}

QPair<QSharedPointer<double>, QSharedPointer<double>> MixedGesturesManager::getKey(PathVector const & path)
{
    QSharedPointer<double> key1 = RectangleGesturesManager().getKey(path);
    QSharedPointer<double> key2 = NearestPosGridGesturesManager().getKey(path);
    return QPair<QSharedPointer<double>, QSharedPointer<double>>(key1, key2);
}


