/*
   The Prototype Pattern allows creating new objects by copying an existing object, known as the prototype. 
   It is useful when the cost of creating an object is expensive or complicated, and copying an existing one is easier.
   This pattern enables the client to create new instances without knowing their specific class.

   Real-World Example:
   Consider a game where different types of characters (e.g., Warrior, Mage, Archer) need to be created. 
   The Prototype Pattern can help by cloning an existing character prototype and making necessary adjustments, rather than creating a new one from scratch.
*/

#include <iostream>
#include <string>
#include <unordered_map>

// Prototype Interface
class Character {
public:
    virtual Character* clone() const = 0;
    virtual void showDetails() const = 0;
    virtual ~Character() {}
};

// Concrete Prototype: Warrior
class Warrior : public Character {
public:
    Warrior(const std::string& name) : name(name) {}

    Character* clone() const override {
        return new Warrior(*this);  // Clone the Warrior
    }

    void showDetails() const override {
        std::cout << "Warrior: " << name << std::endl;
    }

private:
    std::string name;
};

// Concrete Prototype: Mage
class Mage : public Character {
public:
    Mage(const std::string& name) : name(name) {}

    Character* clone() const override {
        return new Mage(*this);  // Clone the Mage
    }

    void showDetails() const override {
        std::cout << "Mage: " << name << std::endl;
    }

private:
    std::string name;
};

// Concrete Prototype: Archer
class Archer : public Character {
public:
    Archer(const std::string& name) : name(name) {}

    Character* clone() const override {
        return new Archer(*this);  // Clone the Archer
    }

    void showDetails() const override {
        std::cout << "Archer: " << name << std::endl;
    }

private:
    std::string name;
};

// Prototype Registry
class CharacterRegistry {
public:
    void addPrototype(const std::string& type, Character* prototype) {
        prototypes[type] = prototype;
    }

    Character* getPrototype(const std::string& type) const {
        return prototypes.at(type)->clone();  // Return a clone of the prototype
    }

    ~CharacterRegistry() {
        for (auto& pair : prototypes) {
            delete pair.second;
        }
    }

private:
    std::unordered_map<std::string, Character*> prototypes;
};

// Client Code
int main() {
    CharacterRegistry registry;

    // Adding prototypes to the registry
    registry.addPrototype("warrior", new Warrior("Conan"));
    registry.addPrototype("mage", new Mage("Gandalf"));
    registry.addPrototype("archer", new Archer("Legolas"));

    // Creating new characters by cloning prototypes
    Character* warrior1 = registry.getPrototype("warrior");
    warrior1->showDetails();  // Warrior: Conan

    Character* mage1 = registry.getPrototype("mage");
    mage1->showDetails();  // Mage: Gandalf

    Character* archer1 = registry.getPrototype("archer");
    archer1->showDetails();  // Archer: Legolas

    // Cloning and modifying the prototypes
    Character* warrior2 = registry.getPrototype("warrior");
    warrior2->showDetails();  // Warrior: Conan

    Character* mage2 = registry.getPrototype("mage");
    mage2->showDetails();  // Mage: Gandalf

    delete warrior1;
    delete mage1;
    delete archer1;
    delete warrior2;
    delete mage2;

    return 0;
}
