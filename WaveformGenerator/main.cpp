#include <fstream>
#include <string>
#include "waveform_generator.h"

// This demonstrates the use of the WaveformGenerator. In this example,
// a CSV-file is created and different signal values are stored to the
// file. Signals can be plotted by using some external software (e.g. Excel).

int main()
{
    char csv_separator = ';';
    std::ofstream data_file("wave_data.csv");
    WafeformGenerator::SineWave sine(5.0f, 3.0f);
    WafeformGenerator::SquareWave square(3.0f, 4.0f);
    WafeformGenerator::TriangleWave triangle(4.0f);
    WafeformGenerator::SawtoothWaveForward sawtooth(3.0f);
    WafeformGenerator::PetalWave petal_1(2.0f, 2.0f);
    WafeformGenerator::PetalWave petal_2(3.0f, 0.5f);
    double y1, y2, y3, y4, y5, y6, t = 0.0f;

    // Add titles for columns
    data_file << "Time" << csv_separator << "Sine" << csv_separator << "Square" << csv_separator 
        << "Triangle" << csv_separator << "Sawtooth" << csv_separator << "Petal_1" << csv_separator 
        << "Petal_2" << std::endl;

    // Start generating data
    for (int time = 0; time < 15000; time++) {
        t = sine.getTimeStamp(); // time is same for all the waves
        y1 = sine.generate();
        y2 = square.generate();
        y3 = triangle.generate();
        y4 = sawtooth.generate();
        y5 = petal_1.generate();
        y6 = petal_2.generate();

        // Store generated values to the CSV-file
        data_file << std::to_string(t)  << csv_separator
                  << std::to_string(y1) << csv_separator
                  << std::to_string(y2) << csv_separator
                  << std::to_string(y3) << csv_separator
                  << std::to_string(y4) << csv_separator
                  << std::to_string(y5) << csv_separator
                  << std::to_string(y6) << std::endl;
    }
}
