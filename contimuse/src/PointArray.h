#ifndef POINT_ARRAY
#define POINT_ARRAY

#include <GLFW/glfw3.h>

class PointArray
{
public:
	PointArray();
	~PointArray();
	void addPoint(GLdouble t, GLdouble n);
	int arraySize() const { return m_arraySize; };
	int numPoints() const { return m_numPoints; };
	int sizeUsed() const { return m_numPoints * 2; };
	GLdouble* points() const { return m_points; };
	void dump() const;
private:
	void increaseArraySize();
	GLdouble* m_points;
	int m_numPoints;
	int m_arraySize;
};

#endif