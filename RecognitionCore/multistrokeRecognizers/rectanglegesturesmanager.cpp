#include "rectanglegesturesmanager.h"
#include "curveKeyBuilder.h"
#include "sorts.h"
#include "QDebug"

RectangleGesturesManager::RectangleGesturesManager()
{
}

double RectangleGesturesManager::getMaxDistance(QString const &)
{
    return 1000;
}
bool RectangleGesturesManager::isMultistroke()
{
    return true;
}

double RectangleGesturesManager::getDistance(QSharedPointer<double> const & key1, QSharedPointer<double> const & key2)
{
    double norm = 0;
    double sum = 0;
    for (int i = 0; i < gridSize * gridSize; i ++)
    {
        sum += std::abs(key1.data()[i] - key2.data()[i]);
        norm = std::max(norm, std::abs(key1.data()[i] - key2.data()[i]));
    }
    return sum / (gridSize * gridSize);
}

QSharedPointer<double> RectangleGesturesManager::getKey(PathVector const & path)
{
    Key key = ::getKey(path, gridSize, gridSize);
    double *finalKey = new double[gridSize * gridSize];
    for (int i = 0; i < gridSize * gridSize; i ++)
    {
        finalKey[i] = key.size();
    }
    for (int k = 0; k < key.size(); k ++)
    {
        SquarePos pos = key.at(k);
        for (int i = 0; i < pos.first; i ++)
        {
            for (int j = 0; j < pos.second; j ++)
            {
                finalKey[i * gridSize + j] --;
            }
        }
    }
    return QSharedPointer<double>(finalKey, deleteArray);
}


