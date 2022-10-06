#pragma once

#include <Base/GLWindow.hpp>

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>

#include <QElapsedTimer>
#include <QTime>
#include <memory>

class FractalWindow final : public fgl::GLWindow
{

public:
	void init() override;
	void render() override;
	void setIterations(int iterations);
	void setRadius(float radius);
	float getFps();

protected:
	void mousePressEvent(QMouseEvent * e) override;
	void mouseReleaseEvent(QMouseEvent * e) override;
	void mouseMoveEvent(QMouseEvent * e) override;
	void wheelEvent(QWheelEvent * e) override;

private:
	GLint shiftUniform_ = -1;
	GLint zoomUniform_ = -1;
	GLint iterationsUniform_ = -1;
	GLint radiusUniform_ = -1;

	int iterations_ = 100;
	float radius_ = 2.0;
	float zoom_ = 0.4;
	QVector2D shift_{0., 0.};

	QOpenGLBuffer vbo_{QOpenGLBuffer::Type::VertexBuffer};
	QOpenGLBuffer ibo_{QOpenGLBuffer::Type::IndexBuffer};
	QOpenGLVertexArrayObject vao_;

	std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

	size_t frame_ = 0;
	QElapsedTimer m_time;
	float fps = 0;

	QVector2D mousePressPosition_{0., 0.};
	bool isPressed_ = false;
	QVector2D globalShift_{0., 0.};
};
