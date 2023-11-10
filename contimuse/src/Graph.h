#ifndef GRAPH
#define GRAPH

#include <vector>
#include <GLFW/glfw3.h>
#include "PointArray.h"

class Graph
{
public:
	Graph();
	~Graph();
	void repaint() const;
	void addPoint(GLdouble t, GLdouble n);
	void dump() const { m_pointArray.dump(); };
	PointArray& pointArray() { return m_pointArray; };
private:
	PointArray m_pointArray;
};

#endif
