/* 
   The Composite Pattern allows you to compose objects into tree structures 
   and treat individual objects and compositions of objects uniformly.

   Real-World Example:
   Consider a company with multiple departments like HR, IT, and Finance. Some departments are simple (like HR), 
   while others (like IT) may contain sub-departments (like Software and Infrastructure). 
   The Composite Pattern enables the client to treat all departments the same way, 
   regardless of whether they are composite or leaf nodes.
*/

#include <iostream>
#include <vector>
#include <string>

// Component interface
class Department {
public:
    virtual void showDetails() const = 0;
    virtual ~Department() {}
};

// Leaf - HR Department
class HRDepartment : public Department {
public:
    void showDetails() const override {
        std::cout << "HR Department" << std::endl;
    }
};

// Leaf - Finance Department
class FinanceDepartment : public Department {
public:
    void showDetails() const override {
        std::cout << "Finance Department" << std::endl;
    }
};

// Composite - Can hold sub-departments
class HeadDepartment : public Department {
private:
    std::vector<Department*> departments;

public:
    void add(Department* dept) {
        departments.push_back(dept);
    }

    void remove(Department* dept) {
        departments.erase(std::remove(departments.begin(), departments.end(), dept), departments.end());
    }

    void showDetails() const override {
        for (const auto& dept : departments) {
            dept->showDetails();
        }
    }

    ~HeadDepartment() {
        for (auto dept : departments) {
            delete dept;
        }
    }
};

// Client Code
int main() {
    // Create leaf departments
    Department* hr = new HRDepartment();
    Department* finance = new FinanceDepartment();

    // Create composite department and add sub-departments
    HeadDepartment* headOffice = new HeadDepartment();
    headOffice->add(hr);
    headOffice->add(finance);

    std::cout << "Company Departments:\n";
    headOffice->showDetails();

    // Clean up
    delete headOffice;

    return 0;
}
