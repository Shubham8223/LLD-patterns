/* The Factory Method Pattern provides an interface for creating objects, but allows subclasses to alter the type of objects that will be created. 
   This pattern is used when you need to create objects of different types but want to let subclasses decide which class to instantiate. 
   It is particularly useful when a class cannot anticipate the class of objects it must create, or when object creation logic needs to be delegated to subclasses.

   Real-World Example:
   Consider an e-commerce system where different types of shipping methods need to be instantiated based on user input or preferences.
   The Factory Method Pattern helps decouple the creation of shipping methods from the logic that uses them, allowing new types of shipping methods to be added without changing the existing code.
   This makes it easy to extend the system with new shipping methods without modifying existing functionality, promoting open/closed principle.
*/#include <iostream>
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

// Creator class (Factory) responsible for creating shipping methods
class ShippingFactory {
public:
    static ShippingMethod* createShippingMethod(int shippingChoice) {
        // Select the appropriate shipping method based on user choice
        if (shippingChoice == 1) {
            return new AirShipping();  // Create AirShipping
        } else if (shippingChoice == 2) {
            return new SeaShipping();  // Create SeaShipping
        } else {
            return new GroundShipping();  // Create GroundShipping
        }
    }
};

// Client Code to use the Factory Method
int main() {
    int shippingChoice;
    std::cout << "Enter shipping method (1 for Air, 2 for Sea, 3 for Ground): ";
    std::cin >> shippingChoice;

    // Use the factory to create the appropriate shipping method based on user choice
    ShippingMethod* shippingMethod = ShippingFactory::createShippingMethod(shippingChoice);

    // Book the shipment and calculate cost for a weight of 10 kg and distance of 500 km
    shippingMethod->bookShipment();
    double cost = shippingMethod->calculateShippingCost(10, 500);
    std::cout << "Shipping cost: $" << cost << std::endl;

    // Clean up
    delete shippingMethod;

    return 0;
}
