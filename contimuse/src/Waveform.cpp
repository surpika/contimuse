#include "Waveform.h"
#include "PointArray.h"
#include "globals.h"
#include "Graph.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <cassert>

class PointArray;

namespace little_endian_io
{
	template <typename Word>
	std::ostream& write_word(std::ostream& outs, Word value, unsigned size = sizeof(Word))
	{
		for (; size; --size, value >>= 8)
			outs.put(static_cast <char> (value & 0xFF));
		return outs;
	}
}
using namespace little_endian_io;

Waveform::Waveform() : m_arraySize(SAMPLE_RATE), m_numSamples(0)
{
	m_samples = new GLdouble[SAMPLE_RATE];
}

Waveform::~Waveform()
{
	delete[] m_samples;
}

void Waveform::computeWaveform(const PointArray& p)
{
	GLdouble dt = 1.0 / SAMPLE_RATE;
	GLdouble sum = 0;
	GLdouble t0;
	GLdouble t1;
	GLdouble f0;
	GLdouble f1;
	GLdouble timeSpan;
	double rectangle;
	double pitch;
	double sine;
	for (int i = 0; i < p.sizeUsed() - 2; i+=2)
	{
		t0 = p.points()[i];
		t1 = p.points()[i + 2];
		f0 = positionToPitch(p.points()[i + 1]);
		f1 = positionToPitch(p.points()[i + 3]);
		timeSpan = t1 - t0;
		for (long double t = 0; t < timeSpan; t += dt)
		{
			pitch = computeLinearPitch(t0, t1, f0, f1, t);
			rectangle = computeFrequency(pitch) * dt;
			sum += rectangle;
			sum = fmod(sum, 1);
			sine = sin(2 * PI * sum);
			addSample(sine);
		}
	}
}   

GLdouble Waveform::computeLinearPitch(GLdouble t0, GLdouble t1, GLdouble f0, GLdouble f1, GLdouble t)
{
	return (f1 - f0) / (t1 - t0) * t + f0;
}

GLdouble Waveform::computeFrequency(GLdouble pitch)
{
	return 440 * pow(2, (pitch - 49) / 12);
}

void Waveform::addSample(double y)
{
	if (m_numSamples == m_arraySize)
		increaseArraySize();
	m_samples[m_numSamples] = y;
	m_numSamples++;
}

void Waveform::increaseArraySize()
{
	GLdouble* temp = new GLdouble[(GLdouble)m_arraySize * 2.0];
	for (int i = 0; i < m_numSamples; i++)
	{
		temp[i] = m_samples[i];
	}
	delete[] m_samples;
	m_samples = temp;
	m_arraySize *= 2;
}

void Waveform::dump() const
{
	std::cout << "Samples dump:" << std::endl;
	for (int i = 0; i < m_numSamples; i ++)
	{
		std::cout << m_samples[i] << std::endl;
	}
	std::cout << std::endl;
}

void Waveform::writeToWav() const
{
    std::ofstream f("example.wav", std::ios::binary);

    // Write the file headers
    f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
    write_word(f, 16, 4);  // no extension data
    write_word(f, 1, 2);  // PCM - integer samples
    write_word(f, 1, 2);  // num channels
    write_word(f, SAMPLE_RATE, 4);  // samples per second (Hz)
    write_word(f, SAMPLE_RATE * 32 * 1 / 8, 4);  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word(f, 4, 2);  // data block size (sample size * num channels, in bytes)
    write_word(f, 32, 2);  // number of bits per sample (use a multiple of 8)

    // Write the data chunk header
    size_t data_chunk_pos = f.tellp();
    f << "data----";  // (chunk size to be filled in later)

    // Write the audio samples
    constexpr double two_pi = 6.283185307179586476925286766559;
    constexpr double max_amplitude = 10000; //32760 is the correct value  // "volume"

	std::cout << "m_numSamples: " << m_numSamples;

    for (int t = 0; t < m_numSamples; t++)
    {
		double value = m_samples[t];
		value *= max_amplitude;
		short intValue = (short)value;
        write_word(f, intValue, 2);
    }

    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = f.tellp();

    // Fix the data chunk header to contain the data size
    f.seekp(data_chunk_pos + 4);
    write_word(f, file_length - data_chunk_pos + 8);

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    f.seekp(0 + 4);
    write_word(f, file_length - 8, 4);
}
