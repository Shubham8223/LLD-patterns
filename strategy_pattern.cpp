/* 
   The Strategy Pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable. 
   This allows the algorithm to vary independently from the clients that use it.

   Real-World Example:
   Consider a navigation system that offers multiple route strategies like driving, walking, or cycling. 
   Depending on user preferences or context, the app can switch strategies at runtime to find the best path.
   The Strategy Pattern enables this flexibility by allowing the route calculation algorithm to be selected and changed dynamically.
*/

#include <iostream>
#include <string>

// Strategy Interface
class RouteStrategy {
public:
    virtual void buildRoute(const std::string& start, const std::string& end) = 0;
    virtual ~RouteStrategy() {}
};

// Concrete Strategy - Driving
class DrivingStrategy : public RouteStrategy {
public:
    void buildRoute(const std::string& start, const std::string& end) override {
        std::cout << "Calculating driving route from " << start << " to " << end << std::endl;
    }
};

// Concrete Strategy - Walking
class WalkingStrategy : public RouteStrategy {
public:
    void buildRoute(const std::string& start, const std::string& end) override {
        std::cout << "Calculating walking route from " << start << " to " << end << std::endl;
    }
};

// Concrete Strategy - Cycling
class CyclingStrategy : public RouteStrategy {
public:
    void buildRoute(const std::string& start, const std::string& end) override {
        std::cout << "Calculating cycling route from " << start << " to " << end << std::endl;
    }
};

// Context Class
class Navigator {
private:
    RouteStrategy* strategy;

public:
    void setStrategy(RouteStrategy* newStrategy) {
        strategy = newStrategy;
    }

    void navigate(const std::string& start, const std::string& end) {
        if (strategy) {
            strategy->buildRoute(start, end);
        } else {
            std::cout << "No strategy set!" << std::endl;
        }
    }
};

// Client Code
int main() {
    Navigator navigator;

    DrivingStrategy drive;
    WalkingStrategy walk;
    CyclingStrategy cycle;

    std::string start = "Home";
    std::string end = "Office";

    navigator.setStrategy(&drive);
    navigator.navigate(start, end);  // Driving route

    navigator.setStrategy(&walk);
    navigator.navigate(start, end);  // Walking route

    navigator.setStrategy(&cycle);
    navigator.navigate(start, end);  // Cycling route

    return 0;
}
