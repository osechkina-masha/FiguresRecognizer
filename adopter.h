#pragma once
#include <QList>
#include <QPoint>
#include <QString>
#include <QSharedPointer>

QString pathToString(QList<QList<QPoint> > const &path);
QList<QList<QPoint>> stringToPath(QString const &str);
