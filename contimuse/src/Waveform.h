#ifndef WAVEFORM
#define WAVEFORM

#include "PointArray.h"
#include "Graph.h"

class PointArray;

class Waveform
{
public:
	Waveform();
	~Waveform();
	//add a linear pitch waveform segment to the waveform
	void computeWaveform(const PointArray& p);
	GLdouble computeLinearPitch(GLdouble t0, GLdouble t1, GLdouble f0, GLdouble f1, GLdouble t);
	GLdouble computeFrequency(GLdouble pitch);
	void dump() const;
	void writeToWav() const;
	void addSample(double y);
private:
	void increaseArraySize();
	int m_arraySize;
	int m_numSamples;
	GLdouble* m_samples;
};

#endif