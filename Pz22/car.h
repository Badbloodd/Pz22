#pragma once
#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    int year;
    string brand;
    string color;
    string type;
    double capacity;
    double mileage;

public:
    Car(int year, string brand, string color, string type, double capacity, double mileage) : year(year), brand(brand), color(color), type(type), capacity(capacity), mileage(mileage) {}

    int getYear() const { return year; }
    string getBrand() const { return brand; }
    string getColor() const { return color; }
    string getType() const { return type; }
    double getCapacity() const { return capacity; }
    double getMileage() const { return mileage; }

    void setYear(int newYear) { year = newYear; }
    void setBrand(string newBrand) { brand = newBrand; }
    void setColor(string newColor) { color = newColor; }
    void setType(string newType) { type = newType; }
    void setCapacity(double newCapacity) { capacity = newCapacity; }
    void setMileage(double newMileage) { mileage = newMileage; }

    double calcAvgConsumption(int distance, double fuel_consumed) const {
        if (distance <= 0 || fuel_consumed <= 0) {
            cerr << "Error: Distance must be positive, and fuel consumed must be greater than zero." << endl;
            return 0;
        }
        return (fuel_consumed / distance) * 100;
    }

    friend ostream& operator<<(ostream& os, const Car& car) {
        os << "Year: " << car.getYear() << endl;
        os << "Brand: " << car.getBrand() << endl;
        os << "Color: " << car.getColor() << endl;
        os << "Type: " << car.getType() << endl;
        os << "Capacity: " << car.getCapacity() << endl;
        os << "Mileage: " << car.getMileage() << endl;
        return os;
    }

};