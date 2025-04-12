/* The Factory Method Pattern provides an interface for creating objects, but allows subclasses to alter the type of objects that will be created. 
   This pattern is used when you need to create objects of different types but want to let subclasses decide which class to instantiate. 
   It's commonly used when a class can’t anticipate the class of objects it must create.

   Real-World Example:
   Consider an e-commerce system where different types of shipping methods need to be instantiated based on user input or preferences.
   The Factory Method Pattern helps decouple the creation of shipping methods from the logic that uses them, allowing new types of shipping methods to be added without changing the existing code.
*/

#include <iostream>
#include <string>

// Base class for all Shipping Methods
class ShippingMethod {
public:
    virtual void bookShipment() = 0;
    virtual double calculateShippingCost(double weight, double distance) = 0;
    virtual ~ShippingMethod() {}
};

// Concrete class for AirShipping
class AirShipping : public ShippingMethod {
public:
    void bookShipment() override {
        std::cout << "Air shipping booked." << std::endl;
    }

    double calculateShippingCost(double weight, double distance) override {
        return weight * distance * 0.5;  // Example cost calculation for air shipping
    }
};

// Concrete class for SeaShipping
class SeaShipping : public ShippingMethod {
public:
    void bookShipment() override {
        std::cout << "Sea shipping booked." << std::endl;
    }

    double calculateShippingCost(double weight, double distance) override {
        return weight * distance * 0.3;  // Example cost calculation for sea shipping
    }
};

// Concrete class for GroundShipping
class GroundShipping : public ShippingMethod {
public:
    void bookShipment() override {
        std::cout << "Ground shipping booked." << std::endl;
    }

    double calculateShippingCost(double weight, double distance) override {
        return weight * distance * 0.1;  // Example cost calculation for ground shipping
    }
};

// Creator class (Factory) which will be responsible for creating shipping methods
class ShippingFactory {
public:
    virtual ShippingMethod* createShippingMethod() = 0;  // Factory method
    virtual ~ShippingFactory() {}
};

// Concrete Creator classes
class AirShippingFactory : public ShippingFactory {
public:
    ShippingMethod* createShippingMethod() override {
        return new AirShipping();  // Creates an instance of AirShipping
    }
};

class SeaShippingFactory : public ShippingFactory {
public:
    ShippingMethod* createShippingMethod() override {
        return new SeaShipping();  // Creates an instance of SeaShipping
    }
};

class GroundShippingFactory : public ShippingFactory {
public:
    ShippingMethod* createShippingMethod() override {
        return new GroundShipping();  // Creates an instance of GroundShipping
    }
};

// Client Code to use the Factory Method
int main() {
    int shippingChoice;
    std::cout << "Enter shipping method (1 for Air, 2 for Sea, 3 for Ground): ";
    std::cin >> shippingChoice;

    ShippingFactory* factory = nullptr;

    // Select the appropriate factory based on user choice
    if (shippingChoice == 1) {
        factory = new AirShippingFactory();
    } else if (shippingChoice == 2) {
        factory = new SeaShippingFactory();
    } else {
        factory = new GroundShippingFactory();
    }

    ShippingMethod* shippingMethod = factory->createShippingMethod();

    // Book the shipment and calculate cost for a weight of 10 kg and distance of 500 km
    shippingMethod->bookShipment();
    double cost = shippingMethod->calculateShippingCost(10, 500);
    std::cout << "Shipping cost: $" << cost << std::endl;

    // Clean up
    delete shippingMethod;
    delete factory;

    return 0;
}
