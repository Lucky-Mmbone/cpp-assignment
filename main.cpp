#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Global variable for Task 3
string companyName = "AutoWorld Inc.";

// Task 1: Base Class Creation
class Vehicle {
protected:
    string brand;
    string model;
    static int count;  // Static variable to track number of vehicles

public:
    // Constructor
    Vehicle(string b, string m) : brand(b), model(m) {
        count++;
    }

    // Virtual destructor for proper cleanup
    virtual ~Vehicle() {}

    // Virtual display method for polymorphism
    virtual void displayInfo() const {
        cout << "Brand: " << brand << ", Model: " << model;
    }

    // Task 4: Update model method
    void updateModel(const string& newModel) {
        string tempModel = newModel;  // Local variable to temporarily store new model
        model = tempModel;  // Update instance variable
    }

    // Static method to get count
    static int getCount() {
        return count;
    }

    // Pure virtual function to make Vehicle abstract (optional but good practice)
    virtual void writeToFile(ofstream& file) const = 0;
    virtual void readFromFile(ifstream& file) = 0;
};

// Initialize static variable
int Vehicle::count = 0;

// Task 2: Derived Classes with Inheritance

class Car : public Vehicle {
private:
    int seats;

public:
    Car(string b, string m, int s) : Vehicle(b, m), seats(s) {
        // Task 6: Exception handling for invalid seats
        if (seats <= 0) {
            throw invalid_argument("Invalid number of seats: " + to_string(seats));
        }
    }

    // Override displayInfo method
    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << ", Type: Car, Seats: " << seats << ", Company: " << companyName << endl;
    }

    void writeToFile(ofstream& file) const override {
        file << "Car " << brand << " " << model << " " << seats << endl;
    }

    void readFromFile(ifstream& file) override {
        file >> brand >> model >> seats;
    }
};

class Motorbike : public Vehicle {
private:
    int engineCapacity;

public:
    Motorbike(string b, string m, int ec) : Vehicle(b, m), engineCapacity(ec) {
        // Task 6: Exception handling for invalid engine capacity
        if (engineCapacity <= 0) {
            throw invalid_argument("Invalid engine capacity: " + to_string(engineCapacity));
        }
    }

    // Override displayInfo method
    void displayInfo() const override {
        Vehicle::displayInfo();
        cout << ", Type: Motorbike, Engine Capacity: " << engineCapacity 
             << "cc, Company: " << companyName << endl;
    }

    void writeToFile(ofstream& file) const override {
        file << "Motorbike " << brand << " " << model << " " << engineCapacity << endl;
    }

    void readFromFile(ifstream& file) override {
        file >> brand >> model >> engineCapacity;
    }
};

// Function prototypes
void demonstrateExceptionHandling();
void demonstrateFileHandling(vector<Vehicle*>& vehicles);

int main() {
    cout << "=== VEHICLE MANAGEMENT SYSTEM ===" << endl;
    cout << "Company: " << companyName << endl << endl;

    vector<Vehicle*> vehicles;  // Using vector instead of array for flexibility

    try {
        // Task 3: Create objects and demonstrate polymorphism
        cout << "=== CREATING VEHICLES ===" << endl;
        
        // Create Car objects
        Car* car1 = new Car("Toyota", "Camry", 5);
        Car* car2 = new Car("Honda", "Civic", 4);
        
        // Create Motorbike objects
        Motorbike* bike1 = new Motorbike("Yamaha", "MT-07", 689);
        Motorbike* bike2 = new Motorbike("Kawasaki", "Ninja", 649);

        // Store in vector of Vehicle pointers
        vehicles.push_back(car1);
        vehicles.push_back(car2);
        vehicles.push_back(bike1);
        vehicles.push_back(bike2);

        // Display static count
        cout << "Total vehicles created: " << Vehicle::getCount() << endl << endl;

        // Task 3: Polymorphism - call displayInfo using base class pointers
        cout << "=== DISPLAYING VEHICLE INFORMATION (POLYMORPHISM) ===" << endl;
        for (size_t i = 0; i < vehicles.size(); i++) {
            vehicles[i]->displayInfo();
        }

        cout << endl;

        // Task 4: Demonstrate model update
        cout << "=== UPDATING VEHICLE MODELS ===" << endl;
        cout << "Before update: ";
        car1->displayInfo();
        car1->updateModel("Corolla");
        cout << "After update: ";
        car1->displayInfo();
        cout << endl;

        // Task 5: File handling
        demonstrateFileHandling(vehicles);

        // Task 6: Exception handling demonstration
        demonstrateExceptionHandling();

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // Cleanup
    for (Vehicle* vehicle : vehicles) {
        delete vehicle;
    }
    vehicles.clear();

    return 0;
}

void demonstrateExceptionHandling() {
    cout << "=== EXCEPTION HANDLING DEMONSTRATION ===" << endl;
    
    // Test invalid seats
    try {
        cout << "Testing invalid seats..." << endl;
        Car invalidCar("Test", "Model", -2);
    }
    catch (const invalid_argument& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    // Test invalid engine capacity
    try {
        cout << "Testing invalid engine capacity..." << endl;
        Motorbike invalidBike("Test", "Model", -100);
    }
    catch (const invalid_argument& e) {
        cout << "Caught exception: " << e.what() << endl;
    }
    cout << endl;
}

void demonstrateFileHandling(vector<Vehicle*>& vehicles) {
    cout << "=== FILE HANDLING DEMONSTRATION ===" << endl;
    
    string filename = "vehicles.txt";
    
    // Write to file
    cout << "Writing vehicle details to file..." << endl;
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Could not open file for writing!" << endl;
        return;
    }
    
    for (Vehicle* vehicle : vehicles) {
        vehicle->writeToFile(outFile);
    }
    outFile.close();
    cout << "Successfully wrote " << vehicles.size() << " vehicles to " << filename << endl;

    // Read from file and display
    cout << "\nReading vehicle details from file..." << endl;
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Could not open file for reading!" << endl;
        return;
    }

    string vehicleType;
    while (inFile >> vehicleType) {
        if (vehicleType == "Car") {
            string brand, model;
            int seats;
            inFile >> brand >> model >> seats;
            cout << "Car - Brand: " << brand << ", Model: " << model 
                 << ", Seats: " << seats << endl;
        }
        else if (vehicleType == "Motorbike") {
            string brand, model;
            int engineCapacity;
            inFile >> brand >> model >> engineCapacity;
            cout << "Motorbike - Brand: " << brand << ", Model: " << model 
                 << ", Engine Capacity: " << engineCapacity << "cc" << endl;
        }
    }
    inFile.close();
    cout << endl;
}
