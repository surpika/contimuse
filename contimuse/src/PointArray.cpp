#include "PointArray.h"
#include "globals.h"
#include <GLFW/glfw3.h>
#include "iostream"

PointArray::PointArray() : m_arraySize(MAX_NUM_POINTS * 2), m_numPoints(0)
{
	m_points = new GLdouble[MAX_NUM_POINTS * 2];
}

PointArray::~PointArray()
{
	if (m_points)
	{
		delete[] m_points;
		m_points = nullptr;
	}
}

void PointArray::addPoint(GLdouble t, GLdouble n)
{
	int currSizeUsed = sizeUsed();
	if (m_numPoints * 2 == m_arraySize)
		increaseArraySize();
	//algorithm for storing points in order of increasing x-value
	int i = currSizeUsed - 2;
	//iterate through every even array element (x values of the points)
	for (;i >= 0 ; i-=2)
	{
		//check if element value is less than x value of point
		if (m_points[i] < t)
		{
			//shift elements
			for (int j = currSizeUsed-2; j >= i + 2; j-=2)
			{
				m_points[j + 2] = m_points[j];
				m_points[j + 3] = m_points[j + 1];
			}
			//add new point at correct location
			m_points[i + 2] = t;
			m_points[i + 3] = n;
			break;
		}
	}
	//put new point at beginning of array if all of the even array elements are greater than or equal to the new point
	if (i == -2)
	{
		//shift elements
		for (int j = currSizeUsed - 2; j >= 0; j -= 2)
		{
			m_points[j + 2] = m_points[j];
			m_points[j + 3] = m_points[j + 1];
		}
		//add new point at correct location
		m_points[0] = t;
		m_points[1] = n;
	}
	//increment the recorded number of points in the array
	m_numPoints++;
}

void PointArray::increaseArraySize()
{
	GLdouble* temp = new GLdouble[m_arraySize * 2];
	for (int i = 0; i < m_numPoints * 2; i++)
	{
		temp[i] = m_points[i];
	}
	delete[] m_points;
	m_points = temp;
	m_arraySize *= 2;
}

void PointArray::dump() const
{
	std::cout << "Point dump:" << std::endl;
	for (int i = 0; i < m_numPoints*2; i+=2)
	{
		std::cout << m_points[i] << ", " << m_points[i + 1] << std::endl;
	}
	std::cout << std::endl;
}