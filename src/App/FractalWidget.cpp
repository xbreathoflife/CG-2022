#include "FractalWidget.h"
#include <QHBoxLayout>
#include <QSlider>

FractalWidget::FractalWidget(QWidget * parent, float fps)
	: QWidget(parent)
{
	QGridLayout * grid = new QGridLayout();

	iterationsLabel_ = new QLabel("Iterations: ", this);
	iterationsEdit = new QSlider(this);
	iterationsEdit->setOrientation(Qt::Horizontal);
	iterationsEdit->setMinimum(0);
	iterationsEdit->setMaximum(200);
	iterationsEdit->setValue(100);

	radiusLabel_ = new QLabel("Radius: ", this);
	radiusEdit = new QSlider(this);
	radiusEdit->setOrientation(Qt::Horizontal);
	radiusEdit->setMinimum(0);
	radiusEdit->setMaximum(30);
	radiusEdit->setValue(2);

	fpsLabel_ = new QLabel("FPS: ", this);
	fpsLabelValue_ = new QLabel(QString::number(fps), this);

	grid->addWidget(iterationsLabel_, 0, 0);
	grid->addWidget(iterationsEdit, 0, 1);
	grid->addWidget(radiusLabel_, 1, 0);
	grid->addWidget(radiusEdit, 1, 1);
	grid->addWidget(fpsLabel_, 2, 0);
	grid->addWidget(fpsLabelValue_, 2, 1);
	setLayout(grid);
}