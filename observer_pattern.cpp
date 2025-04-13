/* 
   The Observer Pattern defines a one-to-many dependency between objects so that when one object (the Subject)
   changes state, all its dependents (Observers) are notified and updated automatically.

   Real-World Example:
   Consider a weather station that provides temperature updates. Multiple displays (e.g., Phone App, Web Dashboard, Digital Board)
   may want to get updates whenever the temperature changes. Using the Observer Pattern, we can ensure that all registered observers 
   are notified whenever the subject (WeatherStation) updates its state.

   This pattern promotes loose coupling between the subject and its observers, allowing them to change independently.
*/

#include <iostream>
#include <vector>
#include <algorithm>

// Observer interface
class Observer {
public:
    virtual void update(float temperature) = 0;
    virtual ~Observer() {}
};

// Subject interface
class Subject {
public:
    virtual void addObserver(Observer* obs) = 0;
    virtual void removeObserver(Observer* obs) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() {}
};

// Concrete Subject (Weather Station)
class WeatherStation : public Subject {
private:
    std::vector<Observer*> observers;
    float temperature;

public:
    void addObserver(Observer* obs) override {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) override {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notifyObservers() override {
        for (auto obs : observers) {
            obs->update(temperature);
        }
    }

    void setTemperature(float temp) {
        temperature = temp;
        notifyObservers();
    }
};

// Concrete Observer - Phone Display
class PhoneDisplay : public Observer {
public:
    void update(float temperature) override {
        std::cout << "Phone Display: Current temperature is " << temperature << "°C" << std::endl;
    }
};

// Concrete Observer - Web Dashboard
class WebDashboard : public Observer {
public:
    void update(float temperature) override {
        std::cout << "Web Dashboard: Current temperature is " << temperature << "°C" << std::endl;
    }
};

// Client Code
int main() {
    WeatherStation* station = new WeatherStation();

    Observer* phone = new PhoneDisplay();
    Observer* web = new WebDashboard();

    // Register observers
    station->addObserver(phone);
    station->addObserver(web);

    // Temperature update
    station->setTemperature(25.5f);
    station->setTemperature(30.0f);

    // Remove one observer and update again
    station->removeObserver(web);
    station->setTemperature(28.2f);

    // Clean up
    delete phone;
    delete web;
    delete station;

    return 0;
}
