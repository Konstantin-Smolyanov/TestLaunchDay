#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;


class Day {
private:
    int day;
    double temperature;
    double wind;
    double humidity;
    double precipitation;
    string lightning;
    string clouds;

public:

    // Constructor for input
    Day(string Day, string Temperature, string Wind, string Humidity, string Precipitation, string Lightning, string Clouds) {
        this->day = stoi(Day);
        this->temperature = stod(Temperature);
        this->wind = stod(Wind);
        this->humidity = stod(Humidity);
        this->precipitation = stod(Precipitation);
        this->lightning = Lightning;
        this->clouds = Clouds;
    };

    // Constructor for further calculations
    Day(int Day, double Temperature, double Wind, double Humidity, double Precipitation, string Lightning, string Clouds) {
        this->day = Day;
        this->temperature = Temperature;
        this->wind = Wind;
        this->humidity = Humidity;
        this->precipitation = Precipitation;
        this->lightning = Lightning;
        this->clouds = Clouds;
    };

    // Test if day is eligible for launch
    bool canLaunch() {
        if (temperature < 2 && temperature > 31) { return false; }
        if (wind > 10) { return false; }
        if (humidity >= 60) { return false; }
        if (precipitation > 0) { return false; }
        if (lightning == "Yes") { return false; }
        if (clouds == "Cumulus" || clouds == "Nimbus") { return false; }

        return true;
    };

    //Getters:
    int getDay() {
        return day;
    }
    double getTemperature() {
        return temperature;
    }
    double getWind() {
        return wind;
    }
    double getHumidity() {
        return humidity;
    }
    double getPrecipitation() {
        return precipitation;
    }
    string getLightning() {
        return lightning;
    }
    string getClouds() {
        return clouds;
    }

    //Setters:
    void setDay(int Day) {
        this->day = Day;
    }
    void setTemperature(double Temperature) {
        this->temperature = Temperature;
    }
    void setWind(double Wind) {
        this->wind = Wind;
    }
    void setHumidity(double Humidity) {
        this->humidity = Humidity;
    }
    void setPrecipitation(double Precipitation) {
        this->precipitation = Precipitation;
    }
    void setLightning(string Lightning) {
        this->lightning = Lightning;
    }
    void setClouds(string Clouds) {
        this->clouds = Clouds;
    }

    // Print day to console (for TESTING)
    void print() {
        cout << "Day: " << day <<
            "\n" << "Temperature: " << temperature <<
            "\n" << "Wind: " << wind <<
            "\n" << "Humidity: " << humidity <<
            "\n" << "Precipitation: " << precipitation <<
            "\n" << "Lightning: " << lightning <<
            "\n" << "Clouds: " << clouds << "\n \n";
    }

    // Print only numerical values of day to console (for TESTING)
    void printData() {
        cout << "Temperature: " << temperature <<
            "\n" << "Wind: " << wind <<
            "\n" << "Humidity: " << humidity <<
            "\n" << "Precipitation: " << precipitation << "\n \n";
    }
};

// Finds highest value for seperate weather parameters
Day calculateMax(vector<Day>& days) {

    double maxTemperature = 0;
    double maxWind = 0;
    double maxHumidity = 0;
    double maxPrecipitation = 0;

    int totalLightning = 0;
    string lightning;

    map<string, int> cloudTypes;
    cloudTypes["Nimbus"] = 0;
    cloudTypes["Cumulus"] = 0;
    cloudTypes["Stratus"] = 0;
    cloudTypes["Cirrus"] = 0;


    // Calculate max temperature, wind, humidity and precipitation
    for (int i = 0; i < days.size(); i++) {
        if (days[i].getTemperature() > maxTemperature) {
            maxTemperature = days[i].getTemperature();
        }
        if (days[i].getWind() > maxWind) {
            maxWind = days[i].getWind();
        }
        if (days[i].getHumidity() > maxHumidity) {
            maxHumidity = days[i].getHumidity();
        }
        if (days[i].getPrecipitation() > maxPrecipitation) {
            maxPrecipitation = days[i].getPrecipitation();
        }
        if (days[i].getLightning() == "Yes") { totalLightning++; }
        else { totalLightning--; }
    }


    // Lightning
    if (totalLightning <= 0) { lightning = "No"; }
    else { lightning = "Yes"; }

    // Cloud
    auto NimbusIterator = cloudTypes.begin();
    pair <string, int> maxCloudType;

    maxCloudType.first = NimbusIterator->first;
    maxCloudType.second = NimbusIterator->second;

    for (auto i : cloudTypes) {
        if (NimbusIterator->second > i.second) {
            maxCloudType.first = i.first;
            maxCloudType.second = i.second;
        }
    }

    Day MaxDay(0, maxTemperature, maxWind, maxHumidity, maxPrecipitation, lightning, maxCloudType.first);

    return MaxDay;
}

// Finds lowest value for seperate weather parameters
Day calculateMin(vector<Day>& days) {
    double minTemperature = 0;
    double minWind = 0;
    double minHumidity = 0;
    double minPrecipitation = 0;

    for (int i = 0; i < days.size(); i++) {
        if (days[i].getTemperature() < minTemperature) {
            minTemperature = days[i].getTemperature();
        }
        if (days[i].getWind() < minWind) {
            minWind = days[i].getWind();
        }
        if (days[i].getHumidity() < minHumidity) {
            minHumidity = days[i].getHumidity();
        }
        if (days[i].getPrecipitation() < minPrecipitation) {
            minPrecipitation = days[i].getPrecipitation();
        }
    }

    Day MinDay(0, minTemperature, minWind, minHumidity, minPrecipitation, "", "");

    return MinDay;
}

// Finds average value for seperate weather parameters
Day calculateAvg(vector<Day>& days) {

    double totalTemperature = 0;
    double totalWind = 0;
    double totalHumidity = 0;
    double totalPrecipitation = 0;

    for (int i = 0; i < days.size(); i++) {
        totalTemperature += days[i].getTemperature();
        totalWind += days[i].getWind();
        totalHumidity += days[i].getHumidity();
        totalPrecipitation += days[i].getPrecipitation();
    }

    double avgTemperature = totalTemperature / days.size();
    double avgWind = totalWind / days.size();
    double avgHumidity = totalHumidity / days.size();
    double avgPrecipitation = totalPrecipitation / days.size();

    Day avgDay(0, avgTemperature, avgWind, avgHumidity, avgPrecipitation, "", "");

    return avgDay;
}

// Finds median value for seperate weather parameters
Day calculateMedian(vector<Day>& days) {

    double medianTemperature = 0;
    double medianWind = 0;
    double medianHumidity = 0;
    double medianPrecipitation = 0;

    // Vectors containing all comparable values
    vector<double> temperatures;
    temperatures.reserve(days.size());
    vector<double> winds;
    winds.reserve(days.size());
    vector<double> humidities;
    humidities.reserve(days.size());
    vector<double> precipitations;
    precipitations.reserve(days.size());

    // Filling up vectors with data
    for (int i = 0; i < days.size(); i++) {
        temperatures.push_back(days[i].getTemperature());
        winds.push_back(days[i].getWind());
        humidities.push_back(days[i].getHumidity());
        precipitations.push_back(days[i].getPrecipitation());
    }

    // Sorting said vectors
    sort(temperatures.begin(), temperatures.end());
    sort(winds.begin(), winds.end());
    sort(humidities.begin(), humidities.end());
    sort(precipitations.begin(), precipitations.end());

    // Calculating median values
    if (temperatures.size() % 2 == 0) {
        medianTemperature = (temperatures[(temperatures.size() / 2)] + temperatures[((temperatures.size() / 2) + 1)]) / 2;
        medianWind = (winds[(temperatures.size() / 2)] + winds[((temperatures.size() / 2) + 1)]) / 2;
        medianHumidity = (humidities[(temperatures.size() / 2)] + humidities[((temperatures.size() / 2) + 1)]) / 2;
        medianPrecipitation = (precipitations[(temperatures.size() / 2)] + precipitations[((temperatures.size() / 2) + 1)]) / 2;
    }
    else {
        medianTemperature = temperatures[((temperatures.size() / 2) + 1)];
        medianWind = winds[((temperatures.size() / 2) + 1)];
        medianHumidity = humidities[((temperatures.size() / 2) + 1)];
        medianPrecipitation = precipitations[((temperatures.size() / 2) + 1)];
    }

    Day medianDay(0, medianTemperature, medianWind, medianHumidity, medianPrecipitation, "", "");

    return medianDay;
}
