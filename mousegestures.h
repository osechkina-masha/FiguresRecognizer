#pragma once
#include "GeometricForms.h"
#include "paintmanager.h"
#include "test/testwindow.h"
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QList>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <abstractRecognizer.h>

namespace Ui
{
class MouseGestures;
}

class MouseGestures : public QMainWindow
{
    Q_OBJECT

public:
    explicit MouseGestures(QWidget *parent = 0);
    ~MouseGestures();

protected:
    //void contextMenuEvent(QContextMenuEvent *event);
    void keyPressEvent(QKeyEvent *);

private:
    Ui::MouseGestures *ui;
    //MultistrokeGesturesManager * mKeyBulder;
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void showTable();
    void showObjectsMenu(QString const & object);
    void paintEvent(QPaintEvent *);
    //	void addEntities(EntityVector const & entities);
    QString mFileName;
    QSharedPointer<PaintManager> mPaintManager;
    void increasePath(double koef);
    QSharedPointer<GesturesManager> mGesturesManager;
    QSharedPointer<AbstractRecognizer> mRecognizer;
    TestWindow *mTestWindow;

private slots:
    void rotatePath();
    void increasePath();
    void decreasePath();
    void loadFile();
    void changePath();
    void drawGesture();
    void save();
    void chooseTestAlgorithm();
    void generateGestures();
    void saveTestGestures();
    void openTestGestures();
    void addTestGesture(QAction *);
};
