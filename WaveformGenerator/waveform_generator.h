#pragma once
// Comments:
// Functions only output the calculated signal value,
// it is user's responsibility to request the next value.
// There is no data buffering or such. Only single value is outputted.
// With overloads, if user does not specify period, then it is
// assumed to be same as amplitude and hence the waves are symmetric.

class WaveformGenerator {
public:
    WaveformGenerator();
    WaveformGenerator(double stamp, double dt);
    void setStepSize(double step_size);
    double getTimeStamp();
    virtual double generate() = 0;
protected:
    void forward();
    double time_stamp; // current time
    double dt;         // step size
};

// --- Basic waveforms ---------------------------------------

class SineWaveF : public WaveformGenerator {
public:
    SineWaveF(double a, double f, double s=0.0f);
    double generate();
protected:
    double amplitude;
    double frequency;
    double shift; // Optional, defaults to 0.0
};

// Frequency is here more convenient, but the lib defaults to period.
// Let the user see period definition, but actually use this behind the scenes.
class SineWave : public SineWaveF {
public: 
    SineWave(double a, double f, double s = 0.0f);
};

class SquareWave : public WaveformGenerator {
public:
    SquareWave(double a);
    SquareWave(double a, double p);
    double generate();
private:
    double amplitude;
    double period;
};

class TriangleWave : public WaveformGenerator {
public:
    TriangleWave(double a);
    TriangleWave(double a, double p);
    double generate();
protected:
    double amplitude;
    double period;
};

class SawtoothWave : public WaveformGenerator {
public:
    SawtoothWave(double a);
    SawtoothWave(double a, double p);
    double generate();
protected:
    double amplitude;
    double period;
};

// --- Special waveforms -------------------------------------
// Some predefined waveforms that are derived from the previous definitions

class PetalWave : public TriangleWave {
public:
    PetalWave(double a, double c);
    double generate();
private:
    double quadratic_coefficient;
};