#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

// ----------------- User Model -----------------
class User {
public:
    int id;
    string name;
    string email;

    User(int id, string name, string email) : id(id), name(name), email(email) {}
};

// ----------------- Group Model -----------------
class Group {
public:
    int id;
    string name;
    vector<shared_ptr<User>> members;

    Group(int id, string name) : id(id), name(name) {}

    void addMember(shared_ptr<User> user) {
        members.push_back(user);
    }

    void showMembers() {
        cout << "Group: " << name << " [ID: " << id << "] Members:\n";
        for (auto& user : members) {
            cout << "- " << user->name << " (" << user->email << ")\n";
        }
    }
};

// ----------------- Strategy Base -----------------
class SplitStrategy {
public:
    virtual vector<float> calculateExpensePerUser(float amount, vector<shared_ptr<User>> users, vector<float> values = {}) = 0;
};

// ----------------- Equal Split Strategy -----------------
class EqualSplitStrategy : public SplitStrategy {
public:
    vector<float> calculateExpensePerUser(float amount, vector<shared_ptr<User>> users, vector<float> values = {}) override {
        int n = users.size();
        float share = amount / n;
        return vector<float>(n, share);
    }
};

// ----------------- Expense Model -----------------
class Expense {
public:
    int id;
    float amount;
    shared_ptr<User> paidBy;
    vector<shared_ptr<User>> participants;
    shared_ptr<SplitStrategy> strategy;

    Expense(int id, float amount, shared_ptr<User> paidBy,
            vector<shared_ptr<User>> participants,
            shared_ptr<SplitStrategy> strategy)
        : id(id), amount(amount), paidBy(paidBy), participants(participants), strategy(strategy) {}

    unordered_map<int, float> splitAmount() {
        unordered_map<int, float> splits;
        vector<float> shares = strategy->calculateExpensePerUser(amount, participants);
        for (size_t i = 0; i < participants.size(); ++i) {
            splits[participants[i]->id] = shares[i];
        }
        return splits;
    }
};

// ----------------- User Service -----------------
class UserService {
    unordered_map<int, shared_ptr<User>> users;

public:
    void addUser(int id, const string& name, const string& email) {
        users[id] = make_shared<User>(id, name, email);
    }

    shared_ptr<User> getUser(int id) {
        return users.count(id) ? users[id] : nullptr;
    }
};

// ----------------- Group Service -----------------
class GroupService {
    unordered_map<int, shared_ptr<Group>> groups;

public:
    void createGroup(int id, string name) {
        groups[id] = make_shared<Group>(id, name);
    }

    void addUserToGroup(int groupId, shared_ptr<User> user) {
        if (groups.count(groupId)) {
            groups[groupId]->addMember(user);
        }
    }

    shared_ptr<Group> getGroup(int id) {
        return groups.count(id) ? groups[id] : nullptr;
    }

    void showGroup(int id) {
        if (groups.count(id)) {
            groups[id]->showMembers();
        } else {
            cout << "Group not found.\n";
        }
    }
};

// ----------------- Expense Service -----------------
class ExpenseService {
    vector<shared_ptr<Expense>> expenses;

public:
    void addExpense(shared_ptr<Expense> expense) {
        expenses.push_back(expense);
        auto splits = expense->splitAmount();

        cout << "\nExpense ID: " << expense->id << " of amount " << expense->amount << " paid by " << expense->paidBy->name << "\n";
        for (auto& pair : splits) {
            cout << "User ID: " << pair.first << " owes: " << pair.second << endl;
        }
    }
};

// ----------------- Main -----------------
int main() {
    UserService userService;
    GroupService groupService;
    ExpenseService expenseService;

    // Create users
    userService.addUser(1, "Alice", "alice@example.com");
    userService.addUser(2, "Bob", "bob@example.com");
    userService.addUser(3, "Charlie", "charlie@example.com");

    auto alice = userService.getUser(1);
    auto bob = userService.getUser(2);
    auto charlie = userService.getUser(3);

    // Create group
    groupService.createGroup(101, "Trip to Goa");
    groupService.addUserToGroup(101, alice);
    groupService.addUserToGroup(101, bob);
    groupService.addUserToGroup(101, charlie);

    groupService.showGroup(101);

    // Create expense using Equal Split
    shared_ptr<SplitStrategy> strategy = make_shared<EqualSplitStrategy>();
    vector<shared_ptr<User>> participants = {alice, bob, charlie};
    shared_ptr<Expense> expense = make_shared<Expense>(1001, 300.0f, alice, participants, strategy);

    expenseService.addExpense(expense);

    return 0;
}
