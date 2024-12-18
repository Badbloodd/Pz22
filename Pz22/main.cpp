#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

#include "car.h"

using namespace std;

class Snack {
private:
    string name;
    int calories;
    double price;

public:
    Snack(string name, int calories = 250, double price = 1.5)
        : name(name), calories(calories), price(price) {
    }

    string getName() const { return name; }
    double getPrice() const { return price; }
    string getCalories() const { return to_string(calories) + " calories"; }

    void setPrice(double newPrice) { price = newPrice; }
    void setCalories(int newCalories) { calories = newCalories; }

    friend ostream& operator<<(ostream& os, const Snack& snack) {
        os << snack.name << " (Calories: " << snack.calories << ", Price: $" << snack.price << ")";
        return os;
    }
};

class SnackSlot {
private:
    vector<Snack*> snacks;
    int capacity;

public:
    SnackSlot(int capacity) : capacity(capacity) {}

    bool addSnack(Snack* snack) {
        if (snacks.size() < capacity) {
            snacks.push_back(snack);
            return true;
        }
        return false;
    }

    void deleteSnack(string name) {
        for (auto it = snacks.begin(); it != snacks.end(); ++it) {
            if ((*it)->getName() == name) {
                snacks.erase(it);
            }
        }
    }

    vector<Snack*> getSnacks() const { return snacks; }

    int getSnackCount() const { return snacks.size(); }
    int getRemainingCapacity() const { return capacity - snacks.size(); }
};

class VendingMachine {
private:
    vector<SnackSlot*> slots;

public:
    void addSlot(SnackSlot* slot) {
        slots.push_back(slot);
    }

    int getEmptySlotsCount() const {
        int count = 0;
        for (const auto& slot : slots) {
            count += slot->getRemainingCapacity();
        }
        return count;
    }

    void displaySnacks() const {
        cout << "Available Snacks:" << endl;
        for (const auto& slot : slots) {
            for (const auto& snack : slot->getSnacks()) {
                cout << *snack << endl;
            }
        }
    }

    ~VendingMachine() {
        for (auto slot : slots) {
            delete slot;
        }
    }
};

int runMachine() {
    Snack* bounty = new Snack("Bounty");
    Snack* snickers = new Snack("Snickers");
    Snack* mars = new Snack("Mars");
    SnackSlot* slot = new SnackSlot(10);

    slot->addSnack(bounty);
    slot->addSnack(snickers);
    slot->addSnack(mars);

    VendingMachine* machine = new VendingMachine();
    machine->addSlot(slot);

    cout << machine->getEmptySlotsCount() << endl;
    machine->displaySnacks();

    slot->deleteSnack("Snickers");
    cout << machine->getEmptySlotsCount() << endl;
    machine->displaySnacks();

    delete machine;
    delete slot;
    delete snickers;
    delete bounty;

    return 0;
}

int testCar() {
    vector<Car> cars;
    char addMore = 'y';

    while (addMore == 'y') {
        int year;
        string brand, color, type;
        double capacity, mileage;

        cout << "Enter car year: ";
        cin >> year;

        while (cin.fail()) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> year;
        }

        cout << "Enter car brand: ";
        cin.ignore();
        getline(cin, brand);

        cout << "Enter car color: ";
        getline(cin, color);

        cout << "Enter car type: ";
        getline(cin, type);

        cout << "Enter car fuel capacity (liters): ";
        cin >> capacity;
        while (cin.fail() || capacity <= 0) {
            cout << "Invalid input. Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> capacity;
        }

        cout << "Enter car mileage (km): ";
        cin >> mileage;
        while (cin.fail() || mileage < 0) {
            cout << "Invalid input. Please enter a non-negative number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> mileage;
        }


        cars.push_back(Car(year, brand, color, type, capacity, mileage));

        cout << "Add another car? (y/n): ";
        cin >> addMore;
    }

    for (size_t i = 0; i < cars.size(); ++i) {
        cout << "\nCar " << i + 1 << ":" << endl;
        cout << cars[i] << endl;
        int distance;
        cout << "Enter distance traveled (km): ";
        cin >> distance;

        double fuel_consumed;
        cout << "Enter fuel consumed (liters): ";
        cin >> fuel_consumed;

        while (cin.fail() || distance <= 0) {
            cout << "Invalid input. Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> distance;
        }

        cout << "Average fuel consumption: " << cars[i].calcAvgConsumption(distance, fuel_consumed) << " liters/100km" << endl;

    }

    ofstream outputFile("car_data.txt");
    if (outputFile.is_open()) {
        for (const auto& car : cars) {
            outputFile << car.getYear() << ","
                << car.getBrand() << ","
                << car.getColor() << ","
                << car.getType() << ","
                << car.getCapacity() << ","
                << car.getMileage() << endl;
        }
        outputFile.close();
        cout << "\nCar data saved to car_data.txt" << endl;
    }
    else {
        cerr << "Unable to open file for writing." << endl;
    }

    return 0;
}


int main() {
    testCar();
}
