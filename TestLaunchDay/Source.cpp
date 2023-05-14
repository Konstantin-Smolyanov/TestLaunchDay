#include <iostream>
#include <string>
#include <vector>
#include <string>

#include "Header.h"

using namespace std;

int main() {
    string filepath, sender, password, receiver;

    //Get input from console
    cout << "Enter file path:  (ex. C:\\sample_file.csv)";
    cin >> filepath;
    cout << "Enter sender email address: ";
    cin >> sender;
    cout << "Enter sender email password: ";
    cin >> password;
    cout << "Enter receiver email address: ";
    cin >> receiver;



    vector<vector<string>> lines;
    vector<Day> days;
    string lineBuff, word;

    ifstream mFile;
    mFile.open(filepath, ios::in);

    // Open file and place data seperated by whitespaces into vect "words", then place words into vect "lines"
    if (mFile.is_open())
    {
        while (getline(mFile, lineBuff)) {
            days.clear();

            vector<string> line;
            stringstream ss(lineBuff);
            while (getline(ss, word, ',')) {
                line.push_back(word);
            }
            lines.push_back(line);
        }
        mFile.close();
    }

    // Error handlign for file not opened
    else {
        cout << "Couldn't open the file\n";
        return 1;
    }

    // vect to store values of weather parameters    (Temperature, Wind, Humidity, Precipitation, Lightning, Clouds)
    vector<string> weatherParameters;
    weatherParameters.reserve(7);

    for (int i = 1; i < lines[1].size() - 1; i++) {    // Itterates between columns (days)

        for (int j = 0; j < lines.size(); j++) {       // Itterates between rows (weather parameters)

            weatherParameters.push_back(lines[j][i]);  // Stores weather parameter values for a day
        }

        // Assigning weather values to Day object
        Day tempDay(weatherParameters[0], weatherParameters[1], weatherParameters[2], weatherParameters[3], weatherParameters[4], weatherParameters[5], weatherParameters[6]);

        days.push_back(tempDay);                       // Stores days in another vector
        weatherParameters.clear();                     // frees up space for next itteration

    }

    // Verify which days are eligible for a missile launch and put them into vect "validDays"
    vector<Day> validDays;
    for (int i = 0; i < days.size(); i++) {
        if (days[i].canLaunch()) {
            validDays.push_back(days[i]);

        }
    }

    // Error handling for an epmpty vector
    if (validDays.empty()) {
        cout << "There are no valid days for missile launch." << endl;
        return 0;
    }

    // Launch day calculations:
    Day bestDay = validDays[0];
    double windHumidity = 0;

    vector<double> windHumidities;
    windHumidities.reserve(validDays.size());

    // Calculate wind+humidity to make determin best day
    for (int i = 1; i < validDays.size() - 1; i++) {
        double windHumidity = validDays[i].getHumidity() + validDays[i].getWind() * 6;  // mulitplying wind so it's proportionate to humidity value

        windHumidities.push_back(windHumidity);
    }

    int bestWindHumidityIndex = 0;
    double bestWindHumidityRatio = windHumidities[0];
    for (int i = 1; i < windHumidities.size() - 1; i++) {
        if (windHumidities[i] < bestWindHumidityRatio) {
            bestWindHumidityRatio = windHumidities[i];
            bestWindHumidityIndex = i;
        }
    }

    Day avgDay = calculateAvg(days);
    Day maxDay = calculateMax(days);
    Day minDay = calculateMin(days);
    Day medDay = calculateMedian(days);
    bestDay = validDays[bestWindHumidityIndex];

    // Print (for TESTING)
    /*cout << "Average values: \n";
    avgDay.print();
    cout << "Maximum values: \n";
    maxDay.print();
    cout << "Minimum values: \n";
    minDay.print();
    cout << "Median values: \n";
    medDay.print();
    cout << "Most suitable launch day: \n";
    bestDay.print();*/

    // Place needed days into vector
    vector<Day> oDays;
    oDays.reserve(5);
    oDays.push_back(avgDay);
    oDays.push_back(maxDay);
    oDays.push_back(minDay);
    oDays.push_back(medDay);
    oDays.push_back(bestDay);

    // Place days from vect to CSV file
    ofstream oFile;
    oFile.open("WeatherReport.csv");
    oFile << "Day:";
    for (int i = 0; i < oDays.size(); i++)         oFile << oDays[i].getDay() << ", ";
    oFile << endl << "Temperature:";
    for (int i = 0; i < oDays.size(); i++)         oFile << oDays[i].getTemperature() << ", ";
    oFile << endl << "Wind:";
    for (int i = 0; i < oDays.size(); i++)         oFile << oDays[i].getWind() << ", ";
    oFile << endl << "Humidity:";
    for (int i = 0; i < oDays.size(); i++)         oFile << oDays[i].getHumidity() << ", ";
    oFile << endl << "Precipitation:";
    for (int i = 0; i < oDays.size(); i++)         oFile << oDays[i].getPrecipitation() << ", ";
    oFile << endl << "Lightning:";
    for (int i = 0; i < oDays.size(); i++)         oFile << oDays[i].getLightning() << ", ";
    oFile << endl << "Clouds:";
    for (int i = 0; i < oDays.size(); i++)         oFile << oDays[i].getClouds() << ", "; oFile << endl;

    cout << "WeatherReport.csv has been generated" << endl;


    // Send CSV file via e-mail:

    // UNCOMPLETE

    return 0;
}

