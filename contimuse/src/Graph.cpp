#include "Graph.h"
#include "PointArray.h"
#include <GLFW/glfw3.h>
#include "globals.h"

GLfloat c[] =
{
	-1, -0.75,
	1, -0.75,
	-1, -0.5,
	1, -0.5,
	- 1, -0.25,
	1, -0.25,
	-1, 0,
	1, 0,
	-1, 0.25,
	1, 0.25,
	-1, 0.5,
	1, 0.5,
	-1, 0.75,
	1, 0.75,
};

Graph::Graph()
{

}

Graph::~Graph()
{

}

void Graph::repaint() const
{
	//set axis line color
    glColor3d(0.5, 0.5, 0.5);

	//draw c
	glVertexPointer(2, GL_FLOAT, 0, c);
	glDrawArrays(GL_LINES, 0, 14);

	//set user line color
	glColor3d(0.7, 0.7, 0.7);
	//draw lines creates by user
	glVertexPointer(2, GL_DOUBLE, 0, m_pointArray.points());
	glDrawArrays(GL_LINE_STRIP, 0, m_pointArray.numPoints());
}

void Graph::addPoint(GLdouble t, GLdouble n)
{
	m_pointArray.addPoint(t, n);
}