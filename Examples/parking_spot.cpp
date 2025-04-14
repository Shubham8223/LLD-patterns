#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

enum class VehicleType { CAR, BIKE, TRUCK };
enum class SpotType { CAR, BIKE, TRUCK };

// ---------- Vehicle Base + Factory ----------
class Vehicle {
public:
    string number;
    VehicleType type;
    Vehicle(string num, VehicleType t) : number(num), type(t) {}
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
public:
    Car(string num) : Vehicle(num, VehicleType::CAR) {}
};

class Bike : public Vehicle {
public:
    Bike(string num) : Vehicle(num, VehicleType::BIKE) {}
};

class Truck : public Vehicle {
public:
    Truck(string num) : Vehicle(num, VehicleType::TRUCK) {}
};

class VehicleFactory {
public:
    static shared_ptr<Vehicle> createVehicle(VehicleType type, const string& num) {
        if (type == VehicleType::CAR) return make_shared<Car>(num);
        if (type == VehicleType::BIKE) return make_shared<Bike>(num);
        if (type == VehicleType::TRUCK) return make_shared<Truck>(num);
        return nullptr;
    }
};

// ---------- Parking Spot ----------
class ParkingSpot {
public:
    int number;
    SpotType type;
    bool isAvailable = true;
    shared_ptr<Vehicle> currentVehicle = nullptr;

    ParkingSpot(int num, SpotType type) : number(num), type(type) {}

    virtual bool assignVehicle(shared_ptr<Vehicle> v) {
        if (!isAvailable) return false;
        currentVehicle = v;
        isAvailable = false;
        return true;
    }

    virtual void removeVehicle() {
        currentVehicle = nullptr;
        isAvailable = true;
    }
};

class CarSpot : public ParkingSpot {
public:
    CarSpot(int num) : ParkingSpot(num, SpotType::CAR) {}
};
class BikeSpot : public ParkingSpot {
public:
    BikeSpot(int num) : ParkingSpot(num, SpotType::BIKE) {}
};
class TruckSpot : public ParkingSpot {
public:
    TruckSpot(int num) : ParkingSpot(num, SpotType::TRUCK) {}
};

class SpotFactory {
public:
    static shared_ptr<ParkingSpot> createSpot(SpotType type, int number) {
        if (type == SpotType::CAR) return make_shared<CarSpot>(number);
        if (type == SpotType::BIKE) return make_shared<BikeSpot>(number);
        if (type == SpotType::TRUCK) return make_shared<TruckSpot>(number);
        return nullptr;
    }
};

// ---------- Ticket ----------
class Ticket {
public:
    static int globalId;
    int id;
    time_t entryTime;
    shared_ptr<Vehicle> vehicle;
    shared_ptr<ParkingSpot> spot;

    Ticket(shared_ptr<Vehicle> v, shared_ptr<ParkingSpot> s)
        : vehicle(v), spot(s) {
        id = ++globalId;
        entryTime = time(nullptr);
    }
};
int Ticket::globalId = 0;

// ---------- Strategy Pattern for Spot Assignment ----------
class SpotAssignmentStrategy {
public:
    virtual shared_ptr<ParkingSpot> findSpot(vector<shared_ptr<ParkingSpot>>& spots) = 0;
};

class FirstAvailableStrategy : public SpotAssignmentStrategy {
public:
    shared_ptr<ParkingSpot> findSpot(vector<shared_ptr<ParkingSpot>>& spots) override {
        for (auto& spot : spots) {
            if (spot->isAvailable) return spot;
        }
        return nullptr;
    }
};

// ---------- Floor ----------
class ParkingFloor {
public:
    vector<shared_ptr<ParkingSpot>> spots;
    void addSpot(shared_ptr<ParkingSpot> spot) {
        spots.push_back(spot);
    }

    shared_ptr<ParkingSpot> getAvailableSpot(VehicleType vtype) {
        SpotType required;
        if (vtype == VehicleType::CAR) required = SpotType::CAR;
        else if (vtype == VehicleType::BIKE) required = SpotType::BIKE;
        else required = SpotType::TRUCK;

        for (auto& spot : spots) {
            if (spot->type == required && spot->isAvailable)
                return spot;
        }
        return nullptr;
    }
};

// ---------- Singleton ParkingLot ----------
class ParkingLot {
private:
    static shared_ptr<ParkingLot> instance;
    ParkingLot() {}

public:
    string name;
    vector<shared_ptr<ParkingFloor>> floors;

    static shared_ptr<ParkingLot> getInstance() {
        if (!instance)
            instance = make_shared<ParkingLot>();
        return instance;
    }

    void addFloor(shared_ptr<ParkingFloor> floor) {
        floors.push_back(floor);
    }

    shared_ptr<Ticket> parkVehicle(shared_ptr<Vehicle> vehicle) {
        for (auto& floor : floors) {
            auto spot = floor->getAvailableSpot(vehicle->type);
            if (spot && spot->assignVehicle(vehicle)) {
                return make_shared<Ticket>(vehicle, spot);
            }
        }
        cout << "No spot available for vehicle: " << vehicle->number << endl;
        return nullptr;
    }

    void unparkVehicle(shared_ptr<Ticket> ticket) {
        ticket->spot->removeVehicle();
        auto duration = difftime(time(nullptr), ticket->entryTime) / 60;
        float rate = 2.0;
        cout << "Vehicle " << ticket->vehicle->number << " left. Pay: ₹" << duration * rate << endl;
    }
};

shared_ptr<ParkingLot> ParkingLot::instance = nullptr;

// ---------- Main ----------
int main() {
    auto lot = ParkingLot::getInstance();
    lot->name = "CyberPark";

    auto floor1 = make_shared<ParkingFloor>();
    floor1->addSpot(SpotFactory::createSpot(SpotType::CAR, 101));
    floor1->addSpot(SpotFactory::createSpot(SpotType::BIKE, 102));
    floor1->addSpot(SpotFactory::createSpot(SpotType::TRUCK, 103));
    lot->addFloor(floor1);

    auto vehicle1 = VehicleFactory::createVehicle(VehicleType::CAR, "DL-001");
    auto ticket1 = lot->parkVehicle(vehicle1);

    this_thread::sleep_for(chrono::seconds(2)); // Simulate parking time
    lot->unparkVehicle(ticket1);

    return 0;
}
