#include <QAbstractSlider>
#include <QApplication>
#include <QSurfaceFormat>
#include <QVBoxLayout>

#include "FractalWidget.h"
#include "FractalWindow.h"

namespace
{
constexpr auto g_sampels = 16;
constexpr auto g_gl_major_version = 3;
constexpr auto g_gl_minor_version = 3;
}// namespace

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	QSurfaceFormat format;
	format.setSamples(g_sampels);
	format.setVersion(g_gl_major_version, g_gl_minor_version);
	format.setProfile(QSurfaceFormat::CoreProfile);

	FractalWindow window;
	window.setFormat(format);

	QWidget * container = QWidget::createWindowContainer(&window);
	container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QVBoxLayout * layout = new QVBoxLayout(nullptr);
	FractalWidget * widget = new FractalWidget(nullptr, window.getFps());
	layout->addWidget(container);
	layout->addWidget(widget, 0, Qt::Alignment(Qt::AlignBottom));
	QObject::connect(widget->iterationsEdit, &QSlider::valueChanged, &window,
					 &FractalWindow::setIterations);
	QObject::connect(widget->radiusEdit, &QSlider::valueChanged, &window,
					 &FractalWindow::setRadius);

	auto window1 = new QWidget;
	window1->resize(640, 480);
	window1->setLayout(layout);
	window1->show();


	window.setAnimated(true);

	return app.exec();
}