#include "waveform_generator.h"
#include <cmath>
#define PI 3.14159265358979323846

// For inherited classes
using namespace WafeformGenerator;

WaveformGenerator::WaveformGenerator() :
    time_stamp(0.0f), dt(0.001f) { };

WaveformGenerator::WaveformGenerator(double stamp, double step) :
    time_stamp(stamp), dt(step) { };

double WaveformGenerator::getTimeStamp() {
    return time_stamp;
}
void WaveformGenerator::setStepSize(double step_size) {
    dt = step_size;
}
void WaveformGenerator::forward() {
    time_stamp += dt;
}

// Define the wave by using frequency
SineWaveF::SineWaveF(double a, double f, double s) :
    amplitude(a), frequency(f), shift(s) { };

// y(t) = A*sin(2*PI*f*t+fii+shift)
double SineWaveF::generate() {
    double y = amplitude * sin(2 * PI * frequency * time_stamp + shift);
    forward();
    return y;
}

// Define the wave by using period. Utilize the previoud definition.
SineWave::SineWave(double a, double p, double s) : SineWaveF(a, 0.0f, s) {
    SineWaveF::frequency = 1 / p; // just convert period to freq.
};

// Positive square wave, box shape
SquareWave::SquareWave(double a) :
    amplitude(a), period(a) { };

// Positive square wave, arbitrary period
SquareWave::SquareWave(double a, double p) :
    amplitude(a), period(p) { };

double SquareWave::generate() {
    double mod = std::fmod(time_stamp, period);
    double y = mod < amplitude ? amplitude : 0;
    forward();
    return y;
}


// Positive triangle wave, symmetric
TriangleWave::TriangleWave(double a) :
    amplitude(a), period(a) { };

// Positive triangle wave, arbitrary period
TriangleWave::TriangleWave(double a, double p) :
    amplitude(a), period(p) { };

double TriangleWave::generate() {
    double y = abs(std::fmod(time_stamp, 2 * period) - amplitude);
    forward();
    return y;
}


// Sawtooth, theeths facing forward
SawtoothWaveForward::SawtoothWaveForward(double a) :
    amplitude(a), period(a) { };

SawtoothWaveForward::SawtoothWaveForward(double a, double p) :
    amplitude(a), period(p) { };

double SawtoothWaveForward::generate() {
    //double y = abs(amplitude - std::fmod(time_stamp, period));
    double y = abs(std::fmod(time_stamp, 2 * period) - amplitude + period);
    forward();
    return y;
}

// Sawtooth, teeths facing backwards
SawtoothWaveBackward::SawtoothWaveBackward(double a) :
    amplitude(a), period(a) { };

SawtoothWaveBackward::SawtoothWaveBackward(double a, double p) :
    amplitude(a), period(p) { };

double SawtoothWaveBackward::generate() {
    //double y = abs(amplitude - std::fmod(time_stamp, period));
    double y = abs(std::fmod(time_stamp, 2 * period) - amplitude + period);
    forward();
    return y;
}


PetalWave::PetalWave(double a, double c) :
    TriangleWave(a), quadratic_coefficient(c) { };

double PetalWave::generate() {
    double y = TriangleWave::generate();
    y = pow(y, quadratic_coefficient);
    // Note: do not forward again, already forwarded.
    return y;
}
