#include "Graph.h"
#include "globals.h"

double convertMousePositionX(double x)
{
	return (x - WINDOW_WIDTH / 2)/(WINDOW_WIDTH/2);
}

double convertMousePositionY(double y)
{
	return -(y - WINDOW_HEIGHT / 2)/(WINDOW_HEIGHT/2);
}

double positionToPitch(double position)
{
	return 40 + position * 48;
}