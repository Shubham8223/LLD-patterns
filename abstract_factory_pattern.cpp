/* 
   The Abstract Factory Pattern provides an interface for creating families of related or dependent objects 
   without specifying their concrete classes. This pattern is particularly useful when a system should be independent 
   of how its products are created, composed, and represented.

   Real-World Example:
   Consider a furniture store where different types of furniture (like chairs and sofas) need to be created in different styles 
   (like Victorian and Modern). The Abstract Factory Pattern helps to create a family of related products (furniture styles) 
   while ensuring that the client does not need to know the exact classes of the products it uses. 
   This pattern makes it easy to extend the system by adding new families of furniture without changing existing code.
*/

#include <iostream>
#include <string>

// Abstract Product for Chair
class Chair {
public:
    virtual void sitOn() = 0;
    virtual ~Chair() {}
};

// Abstract Product for Sofa
class Sofa {
public:
    virtual void lieOn() = 0;
    virtual ~Sofa() {}
};

// Concrete Product for Victorian Chair
class VictorianChair : public Chair {
public:
    void sitOn() override {
        std::cout << "Sitting on a Victorian chair." << std::endl;
    }
};

// Concrete Product for Victorian Sofa
class VictorianSofa : public Sofa {
public:
    void lieOn() override {
        std::cout << "Lying on a Victorian sofa." << std::endl;
    }
};

// Concrete Product for Modern Chair
class ModernChair : public Chair {
public:
    void sitOn() override {
        std::cout << "Sitting on a Modern chair." << std::endl;
    }
};

// Concrete Product for Modern Sofa
class ModernSofa : public Sofa {
public:
    void lieOn() override {
        std::cout << "Lying on a Modern sofa." << std::endl;
    }
};

// Abstract Factory that creates abstract products (Chair and Sofa)
class FurnitureFactory {
public:
    virtual Chair* createChair() = 0;
    virtual Sofa* createSofa() = 0;
    virtual ~FurnitureFactory() {}
};

// Concrete Factory for creating Victorian Furniture
class VictorianFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() override {
        return new VictorianChair();  // Creates Victorian Chair
    }

    Sofa* createSofa() override {
        return new VictorianSofa();  // Creates Victorian Sofa
    }
};

// Concrete Factory for creating Modern Furniture
class ModernFurnitureFactory : public FurnitureFactory {
public:
    Chair* createChair() override {
        return new ModernChair();  // Creates Modern Chair
    }

    Sofa* createSofa() override {
        return new ModernSofa();  // Creates Modern Sofa
    }
};

// Client Code to use the Abstract Factory
int main() {
    int furnitureChoice;
    std::cout << "Enter furniture style (1 for Victorian, 2 for Modern): ";
    std::cin >> furnitureChoice;

    FurnitureFactory* factory = nullptr;

    // Select the appropriate factory based on user choice
    if (furnitureChoice == 1) {
        factory = new VictorianFurnitureFactory();  // Create Victorian style furniture
    } else {
        factory = new ModernFurnitureFactory();  // Create Modern style furniture
    }

    // Create the products (chair and sofa)
    Chair* chair = factory->createChair();
    Sofa* sofa = factory->createSofa();

    // Use the products
    chair->sitOn();
    sofa->lieOn();

    // Clean up
    delete chair;
    delete sofa;
    delete factory;

    return 0;
}
