#include "testwindow.h"
#include "ui_testwindow.h"
#include "multistrokeRecognizers/multistrokeGesturesManagers.h"
#include "multistrokeRecognizers/rectanglegesturesmanager.h"
#include "multistrokeRecognizers/sumMultistrokeGesturesManager.h"
#include "multistrokeRecognizers/nearestposgridgesturesmanager.h"
#include "multistrokeRecognizers/rectangleClassifier.h"
#include "multistrokeRecognizers/mixedgesturesmanager.h"
#include "recognizerInterface.h"
#include "multistrokeRecognizers/adaBoostManager.h"
#include "adopter.h"
#include "testThread.h"

//const QString pathToTestFile = "usersGestures.xml";
const QString pathToTrainingFile = "NeuralNetwork/learnGestures/learn_gestures1.xml";
const QString levXYSortAlgorithm = "levenshtein distance square and sorting by XY coordinates";
const QString levDistHullAlgorithm = "levenshtein distance and hull sorting";
const QString sortXYAlgorithm = "one size keys and sorting by XY";
const QString hullSortAlgorithm = "one size keys and hull sorting";
const QString squaresCurvesAlgorithm = "distance between nearest squares";
const QString trainingGesturesManagerAlgorithm = "training algorithm";
const QString sumGesturesRecognizeAlgorithm = "sum positions algorithm";
const QString rectangleGesturesAlgorithm = "rectangle gestures algorithm";
const QString nearestPosGridAlgorithm = "distance grid algorithm";
const QString sumGesturesTrainingAlgorithm = "sum positions training algorithm";
const QString rectangleGesturesTrainingAlgorithm = "rectangle gestures training algorithm";
const QString nearestPosGridTrainingAlgorithm = "distance grid training algorithm";
const QString mixedGridAlgorithm = "combination of rectangle and nesrest squares algorithm";
const QString mixedTrainingAlgorithm = "mixed training algorithm";
const QString adaBoostAlgorithm = "adaboost";

TestWindow::TestWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::TestWindow)
{
	ui->setupUi(this);
	ui->cbAlgorithm->addItem(squaresCurvesAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(trainingGesturesManagerAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(levXYSortAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(levDistHullAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(sortXYAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(hullSortAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(sumGesturesRecognizeAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(rectangleGesturesAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(nearestPosGridAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(sumGesturesTrainingAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(rectangleGesturesTrainingAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(nearestPosGridTrainingAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(mixedGridAlgorithm, QVariant());
	ui->cbAlgorithm->addItem(mixedTrainingAlgorithm,  QVariant());
	ui->cbAlgorithm->addItem("adaboost", QVariant()); //TODO: add constant
	connect(ui->bTest, SIGNAL(clicked()), this, SLOT(test()));
	ui->pbTested->setValue(0);
}

void TestWindow::test()
{
	ui->pbTested->setValue(1);
    QSharedPointer<RecognizerInterface> gesturesManager = getGesturesManager();
    TestThread *thread = new TestThread(gesturesManager, this); // will be deleted as a child of QObject
	connect(thread, SIGNAL(tested(int, int, int)), this, SLOT(printData(int,int,int)));
	ui->pbTested->setValue(5);
	thread->run();
}

void TestWindow::printData(int percent, int all, int recognized)
{
	ui->pbTested->setValue(percent);
	ui->teAll->setText(QString::number(all));
	ui->teRecognized->setText(QString::number(recognized));
	ui->teNotRecognized->setText(QString::number(all - recognized));
}

QSharedPointer<RecognizerInterface> TestWindow::getGesturesManager()
{
	QString name = ui->cbAlgorithm->currentText();
//	if (name == adaBoostAlgorithm) {
//        QSharedPointer<AdaBoostManager> adaBoostManager(new AdaBoostManager());
//        train(*adaBoostManager);
//		return adaBoostManager;
//	}
    QSharedPointer<GesturesManager> gestureManager;
	if (name ==  levXYSortAlgorithm) {
        gestureManager.reset(new LevenshteinXYSortGesturesManager());
	}
	else if (name == levDistHullAlgorithm) {
        gestureManager.reset(new LevenshteinHullGesturesManager());
	}
	else if (name == sortXYAlgorithm) {
        gestureManager.reset(new OneSizeXYSortGesturesManager());
	}
	else if (name == squaresCurvesAlgorithm) {
        gestureManager.reset(new SquaresCurveGesturesManager());
	}
	else if (name == trainingGesturesManagerAlgorithm)
	{
        QSharedPointer<TrainingGesturesManager<GridClassifier>> trainingGesturesManager(
                    new TrainingGesturesManager<GridClassifier>());
        trainGesturesManager<GridClassifier>(trainingGesturesManager);
        gestureManager = trainingGesturesManager;
	}
	else if (name == sumGesturesRecognizeAlgorithm)
	{
		qDebug() << "try to initialize";
        gestureManager.reset(new SumGesturesManager());
	}
	else if (name == rectangleGesturesAlgorithm) {
        gestureManager.reset(new RectangleGesturesManager());
	}
	else if (name == nearestPosGridAlgorithm) {
        gestureManager.reset(new NearestPosGridGesturesManager());
	}
	else if (name == mixedGridAlgorithm) {
        gestureManager.reset(new MixedGesturesManager());
	}
	else if (name == sumGesturesTrainingAlgorithm)
	{
        QSharedPointer<TrainingGesturesManager<RectangleClassifier<SumGesturesManager>>> trainingGM(
                new TrainingGesturesManager<RectangleClassifier<SumGesturesManager>>());
        trainGesturesManager(trainingGM);
        gestureManager = trainingGM;
	}
	else if (name == rectangleGesturesTrainingAlgorithm)
	{
        QSharedPointer<TrainingGesturesManager<RectangleClassifier<RectangleGesturesManager>>> trainingGM(
                new TrainingGesturesManager<RectangleClassifier<RectangleGesturesManager>>());
        trainGesturesManager(trainingGM);
        gestureManager = trainingGM;
	}
	else if (name == nearestPosGridTrainingAlgorithm)
	{
        QSharedPointer<TrainingGesturesManager<RectangleClassifier<NearestPosGridGesturesManager>>> trainingGM(
                new TrainingGesturesManager<RectangleClassifier<NearestPosGridGesturesManager> >());
        trainGesturesManager(trainingGM);
        gestureManager = trainingGM;
	}
	else if (name == mixedTrainingAlgorithm)
	{
        QSharedPointer<TrainingGesturesManager<MixedClassifier>> trainingGM(
                new TrainingGesturesManager<MixedClassifier>());
        trainGesturesManager(trainingGM);
        gestureManager = trainingGM;
	}
	else {
        gestureManager.reset(new OneSizeHullGesturesManager());
	}
    return QSharedPointer<RecognizerInterface>(new AbstractRecognizer(gestureManager));
}

TestWindow::~TestWindow()
{
	delete ui;
}
