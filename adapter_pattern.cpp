/* 
   The Adapter Pattern is a structural design pattern that allows incompatible interfaces to work together. 
   It acts as a bridge between two objects, allowing them to interact despite having different interfaces. 
   This pattern is used when you want to integrate a new system or library with an existing system, but their interfaces are incompatible.

   Real-World Example:
   Consider integrating a new payment gateway into an existing e-commerce system. 
   The new payment gateway has a different interface than the existing one, and the Adapter Pattern helps bridge that gap, 
   allowing the old system to communicate with the new gateway without modifying the existing code. 
   This makes it easy to add new functionality without affecting the core system.
*/

#include <iostream>
#include <string>

// Target interface (existing system interface)
class PaymentProcessor {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentProcessor() {}
};

// Adaptee class (new system with incompatible interface)
class NewPaymentGateway {
public:
    void makePayment(double amount) {
        std::cout << "Processing payment of $" << amount << " through NewPaymentGateway.\n";
    }
};

// Adapter class (adapts the new system to the target interface)
class PaymentAdapter : public PaymentProcessor {
public:
    PaymentAdapter(NewPaymentGateway* newGateway) : gateway(newGateway) {}
    
    void processPayment(double amount) override {
        gateway->makePayment(amount);  // Adapt the method to the new interface
    }

private:
    NewPaymentGateway* gateway;
};

// Client code that expects the target interface
void clientCode(PaymentProcessor* processor, double amount) {
    processor->processPayment(amount);
}

int main() {
    NewPaymentGateway* newGateway = new NewPaymentGateway();
    PaymentProcessor* adapter = new PaymentAdapter(newGateway);

    // Using the Adapter to work with the existing system
    clientCode(adapter, 150.75);  // Output: Processing payment of $150.75 through NewPaymentGateway.

    delete adapter;
    delete newGateway;

    return 0;
}
