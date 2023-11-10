#ifndef GLOBALS
#define GLOBALS

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int MAX_NUM_POINTS = 32;
const int FLOOR_FREQUENCY = 20;
const int CEILING_FREQUENCY = 20000;
const int SAMPLE_RATE = 8000;
const GLdouble  PI = 3.14159265;

double convertMousePositionX(double x);
double convertMousePositionY(double y);
double positionToPitch(double position);

#endif