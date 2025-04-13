/* 
   The Builder Pattern allows for the construction of complex objects step by step. 
   It separates the construction of an object from its representation, allowing the same construction process to create different representations (types) of an object.
   This pattern is useful when an object needs to be created with many optional parts or configurations, especially when there is a complex set of construction steps involved.

   Real-World Example:
   Consider constructing a complex meal at a restaurant where the customer can select different components like the main dish, side dishes, drinks, and desserts. 
   The Builder Pattern allows the restaurant to build a complete meal through a series of steps, while the customer can customize the meal to their preferences.

   This pattern helps manage the complexity of constructing an object with many optional parts without having to pass all configurations as constructor arguments.
*/

#include <iostream>
#include <string>
#include <vector>

// Product Class
class Meal {
public:
    void addDish(const std::string& dish) {
        dishes.push_back(dish);
    }

    void showMeal() const {
        std::cout << "Meal includes: ";
        for (const auto& dish : dishes) {
            std::cout << dish << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::string> dishes;
};

// Abstract Builder Class
class MealBuilder {
public:
    virtual void buildMainDish() = 0;
    virtual void buildSideDish() = 0;
    virtual void buildDrink() = 0;
    virtual Meal* getMeal() = 0;
    virtual ~MealBuilder() {}
};

// Concrete Builder Class for Vegetarian Meal
class VegetarianMealBuilder : public MealBuilder {
public:
    VegetarianMealBuilder() { meal = new Meal(); }

    void buildMainDish() override {
        meal->addDish("Vegetarian Burger");
    }

    void buildSideDish() override {
        meal->addDish("Salad");
    }

    void buildDrink() override {
        meal->addDish("Lemonade");
    }

    Meal* getMeal() override {
        return meal;
    }

private:
    Meal* meal;
};

// Concrete Builder Class for Non-Vegetarian Meal
class NonVegetarianMealBuilder : public MealBuilder {
public:
    NonVegetarianMealBuilder() { meal = new Meal(); }

    void buildMainDish() override {
        meal->addDish("Chicken Burger");
    }

    void buildSideDish() override {
        meal->addDish("Fries");
    }

    void buildDrink() override {
        meal->addDish("Coke");
    }

    Meal* getMeal() override {
        return meal;
    }

private:
    Meal* meal;
};

// Director Class that constructs the meal
class MealDirector {
public:
    Meal* constructMeal(MealBuilder* builder) {
        builder->buildMainDish();
        builder->buildSideDish();
        builder->buildDrink();
        return builder->getMeal();
    }
};

// Client Code to use the Builder Pattern
int main() {
    // Create the Director
    MealDirector director;

    // Create a Vegetarian meal
    VegetarianMealBuilder vegetarianBuilder;
    Meal* vegetarianMeal = director.constructMeal(&vegetarianBuilder);
    std::cout << "Vegetarian Meal: ";
    vegetarianMeal->showMeal();
    delete vegetarianMeal;

    // Create a Non-Vegetarian meal
    NonVegetarianMealBuilder nonVegBuilder;
    Meal* nonVegetarianMeal = director.constructMeal(&nonVegBuilder);
    std::cout << "Non-Vegetarian Meal: ";
    nonVegetarianMeal->showMeal();
    delete nonVegetarianMeal;

    return 0;
}
