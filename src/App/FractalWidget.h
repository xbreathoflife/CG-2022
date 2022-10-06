#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QWidget>

class FractalWidget : public QWidget
{
public:
	FractalWidget(QWidget * parent = nullptr);
	FractalWidget(QWidget * parent = nullptr, float fps = 0);
	QLabel * fpsLabel_;
	QLabel * fpsLabelValue_;
	QLabel * radiusLabel_;
	QLabel * iterationsLabel_;
	QSlider * radiusEdit;
	QSlider * iterationsEdit;
};