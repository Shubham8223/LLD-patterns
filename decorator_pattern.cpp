/* 
   The Decorator Pattern is a structural design pattern that allows adding new functionality to an object 
   dynamically, without altering its structure. It provides a flexible alternative to subclassing for extending functionality.
   This pattern is useful when you need to add responsibilities to individual objects without affecting others of the same class.

   Real-World Example:
   Consider a coffee shop system where you want to allow customers to customize their coffee with different add-ons like milk, sugar, or whipped cream. 
   Instead of creating separate subclasses for each combination of ingredients, the Decorator Pattern allows you to dynamically add ingredients to a basic coffee object.
   This makes it easy to extend the system by adding new ingredients without modifying existing code.
*/

#include <iostream>
#include <string>

// Base Coffee class
class Coffee {
public:
    virtual double cost() const = 0;
    virtual std::string description() const = 0;
    virtual ~Coffee() {}
};

// Concrete class for a simple coffee
class SimpleCoffee : public Coffee {
public:
    double cost() const override {
        return 5.0;  // Base cost of simple coffee
    }

    std::string description() const override {
        return "Simple Coffee";
    }
};

// Abstract Decorator class for Coffee
class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee;

public:
    CoffeeDecorator(Coffee* c) : coffee(c) {}

    virtual double cost() const override = 0;
    virtual std::string description() const override = 0;
};

// Concrete Decorator for Milk
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(Coffee* c) : CoffeeDecorator(c) {}

    double cost() const override {
        return coffee->cost() + 1.5;  // Add cost for milk
    }

    std::string description() const override {
        return coffee->description() + ", Milk";
    }
};

// Concrete Decorator for Sugar
class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(Coffee* c) : CoffeeDecorator(c) {}

    double cost() const override {
        return coffee->cost() + 0.5;  // Add cost for sugar
    }

    std::string description() const override {
        return coffee->description() + ", Sugar";
    }
};

// Concrete Decorator for Whipped Cream
class WhippedCreamDecorator : public CoffeeDecorator {
public:
    WhippedCreamDecorator(Coffee* c) : CoffeeDecorator(c) {}

    double cost() const override {
        return coffee->cost() + 2.0;  // Add cost for whipped cream
    }

    std::string description() const override {
        return coffee->description() + ", Whipped Cream";
    }
};

// Client Code
int main() {
    Coffee* myCoffee = new SimpleCoffee();  // Start with a basic coffee
    std::cout << myCoffee->description() << " costs $" << myCoffee->cost() << std::endl;

    // Add Milk to the coffee
    myCoffee = new MilkDecorator(myCoffee);
    std::cout << myCoffee->description() << " costs $" << myCoffee->cost() << std::endl;

    // Add Sugar to the coffee
    myCoffee = new SugarDecorator(myCoffee);
    std::cout << myCoffee->description() << " costs $" << myCoffee->cost() << std::endl;

    // Add Whipped Cream to the coffee
    myCoffee = new WhippedCreamDecorator(myCoffee);
    std::cout << myCoffee->description() << " costs $" << myCoffee->cost() << std::endl;

    // Clean up
    delete myCoffee;

    return 0;
}
