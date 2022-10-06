#include "FractalWindow.h"

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QScreen>

#include <array>

namespace
{

constexpr std::array<GLfloat, 8u> vertices = {
	-1.0f,
	-1.0f,
	-1.0f,
	1.0f,
	1.0f,
	-1.0f,
	1.0f,
	1.0f,
};
constexpr std::array<GLuint, 6u> indices = {0, 1, 2, 1, 2, 3};

}// namespace

void FractalWindow::init()
{
	// Configure shaders
	program_ = std::make_unique<QOpenGLShaderProgram>(this);
	program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/diffuse.vs");
	program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/diffuse.fs");
	program_->link();

	// Create VAO object
	vao_.create();
	vao_.bind();

	// Create VBO
	vbo_.create();
	vbo_.bind();
	vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vbo_.allocate(vertices.data(), static_cast<int>(vertices.size() * sizeof(GLfloat)));

	// Create IBO
	ibo_.create();
	ibo_.bind();
	ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
	ibo_.allocate(indices.data(), static_cast<int>(indices.size() * sizeof(GLuint)));

	// Bind attributes
	program_->bind();

	program_->enableAttributeArray(0);
	program_->setAttributeBuffer(0, GL_FLOAT, 0, 2, static_cast<int>(2 * sizeof(GLfloat)));

	iterationsUniform_ = program_->uniformLocation("iterations");
	radiusUniform_ = program_->uniformLocation("radius");
	zoomUniform_ = program_->uniformLocation("zoom");
	shiftUniform_ = program_->uniformLocation("shift");

	// Release all
	program_->release();

	vao_.release();

	ibo_.release();
	vbo_.release();

	// Uncomment to enable depth test and face culling
	// glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);

	// Clear all FBO buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FractalWindow::render()
{
	// Configure viewport
	const auto retinaScale = devicePixelRatio();
	glViewport(0, 0, static_cast<GLint>(width() * retinaScale),
			   static_cast<GLint>(height() * retinaScale));

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind VAO and shader program
	program_->bind();
	vao_.bind();

	// Update uniform value
	program_->setUniformValue(iterationsUniform_, iterations_);
	program_->setUniformValue(radiusUniform_, radius_);
	program_->setUniformValue(zoomUniform_, zoom_);
	program_->setUniformValue(shiftUniform_, globalShift_ + shift_);

	// Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// Release VAO and shader program
	vao_.release();
	program_->release();
	// Increment frame counter
	if (frame_ == 0)
	{
		m_time.start();
	}
	else
	{
		fps = m_time.elapsed() / float(frame_);
	}
	++frame_;
}


void FractalWindow::mousePressEvent(QMouseEvent * e)
{
	isPressed_ = true;
	mousePressPosition_ = QVector2D(e->localPos());
}

void FractalWindow::mouseReleaseEvent(QMouseEvent * e)
{
	isPressed_ = false;
	int xAtRelease = e->x();
	int yAtRelease = e->y();
	float dx = xAtRelease - mousePressPosition_.x();
	float dy = yAtRelease - mousePressPosition_.y();
	globalShift_ += QVector2D(-2 * dx / (float)width(), 2 * dy / (float)height());
	shift_ = QVector2D(0, 0);
}


void FractalWindow::mouseMoveEvent(QMouseEvent * e)
{
	if (isPressed_)
	{
		int xAtMove = e->x();
		int yAtMove = e->y();
		float dx = xAtMove - mousePressPosition_.x();
		float dy = yAtMove - mousePressPosition_.y();
		shift_ = QVector2D(-2 * dx / (float)width(), 2 * dy / (float)height());
	}
}

void FractalWindow::wheelEvent(QWheelEvent * e)
{
	float prev = zoom_;
	float x = float(e->position().x() / width());
	float y = 1.0f - float(e->position().y() / height());
	zoom_ = std::max(0.1f, zoom_ + float(e->pixelDelta().y() / 100.) * zoom_);

	globalShift_ = zoom_ / prev * (QVector2D(-1, -1) + globalShift_ + 2 * QVector2D(x, y))
		- QVector2D(-1, -1) - 2 * QVector2D(x, y);
}

void FractalWindow::setIterations(int iterations)
{
	iterations_ = iterations;
}


void FractalWindow::setRadius(float radius)
{
	radius_ = radius;
}

float FractalWindow::getFps()
{
	return fps;
}