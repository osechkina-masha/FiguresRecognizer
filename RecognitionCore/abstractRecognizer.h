#pragma once
#include <QString>
#include <QMap>
#include <QSharedPointer>
#include "GeometricForms.h"
#include "recognizerInterface.h"
#include <QDebug>

class GesturesManager
{
public:
    virtual void initIdealGestures(QMap<QString, PathVector> const & objects) = 0;
    virtual void setKey(const PathVector & path) = 0;
    virtual double getMaxDistance(QString const & object) = 0;
    virtual double getDistance(QString const & object) = 0;
    virtual bool isMultistroke() = 0;
    virtual ~GesturesManager() {}
};

template <typename TKey>
class GesturesRecognizer : public GesturesManager
{
public:
    double getDistance(QString const & item)
    {
        TKey key = mGestures[item];
        return getDistance(mKey, key);
    }

    void initIdealGestures(QMap<QString, PathVector> const & objects)
    {
        foreach (QString object, objects.keys()) {
            qDebug() << object;
            TKey key = getKey(objects[object]);
            mGestures.insert(object, key);
            qDebug() << object << "inserted";
        }
    }

    void setKey(PathVector const & path)
    {
        mKey = getKey(path);
    }

    virtual double getMaxDistance(QString const & object) = 0;
    virtual ~GesturesRecognizer()
    {
    }

protected:
    TKey mKey;
    virtual double getDistance(TKey const & key1, TKey const & key2) = 0;
    virtual TKey getKey(PathVector const & path) = 0;
    QMap<QString, TKey> mGestures;
};


class AbstractRecognizer : public RecognizerInterface
{
public:
    AbstractRecognizer(QSharedPointer<GesturesManager> const &recognizer, const QList<Entity> &objects) :
        mGesturesManager(recognizer)
    {
        setIdealGestures(objects);
    }

    AbstractRecognizer(QSharedPointer<GesturesManager> const & recognizer) :
        mGesturesManager(recognizer)
    {
    }

    AbstractRecognizer(QSharedPointer<GesturesManager> const &recognizer, const QMap<QString, UsersGestures> & objects) :
        mGesturesManager(recognizer)
      , mObjects(objects)
    {
        clearUsersGestures();
    }

    void setIdealGestures(const QList<Entity> & objects)
    {
        mObjects.clear();
        QMap<QString, PathVector> gestures;
        foreach (Entity entity, objects)
        {
            PathVector paths;
            paths = entity.second;
            QPair<PathVector, QStringList> pair(paths, QStringList());
            mObjects.insert(entity.first, pair);
            gestures.insert(entity.first, paths);
        }
        mGesturesManager->initIdealGestures(gestures);
    }

    QString recognizeObject()
    {
        QString recognizedObject;
        mGesturesManager->setKey(mGesture);
        //mLastGesture = pathToString(mGesture);
        mGesture.clear();
        if (mObjects.empty())
            return "";
        double minDist = mGesturesManager->getMaxDistance(mObjects.keys().at(0));
        foreach (QString object, mObjects.keys())
        {
            minDist = std::min(minDist, mGesturesManager->getMaxDistance(object));
            double dist = mGesturesManager->getDistance(object);
            if (dist < minDist)
            {
                minDist = dist;
                recognizedObject = object;
            }
        }
        return recognizedObject;
    }

    void mousePress(QPoint const & pnt)
    {
        QList<QPoint> path;
        path.push_back(pnt);
        mGesture.push_back(path);
    }

    void mouseMove(QPoint const & pnt)
    {
        PointVector path = mGesture.back();
        mGesture.pop_back();
        path.push_back(pnt);
        mGesture.push_back(path);
    }

    void mouseRelease(QPoint const & pnt)
    {
        mouseMove(pnt);
    }

    QList<QString> getObjects()
    {
        return mObjects.keys();
    }

    PathVector getGesture()
    {
        return mGesture;
    }

    QString recognizeObject(PathVector const & gesture)
    {
        mGesture = gesture;
        return recognizeObject();
    }
    void saveGesture(const QString & name)
    {
        mObjects[name].second.push_back(mLastGesture);
    }

    QMap<QString, QPair<PathVector, QStringList> > getAllGestures()
    {
        return mObjects;
    }
    void clearUsersGestures()
    {
        foreach (QString object, mObjects.keys())
            mObjects[object].second.clear();
    }
    virtual ~AbstractRecognizer() {}

private:
    QSharedPointer<GesturesManager> mGesturesManager;
    QMap<QString, QPair<PathVector, QStringList> > mObjects;
    QString mLastGesture;
    PathVector mGesture;
};
