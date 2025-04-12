/*    The Singleton pattern is commonly used in database connections to ensure that there is only one connection to the database at any time, 
      which helps in maintaining resource efficiency and avoids creating multiple unnecessary connections. 
      This is crucial for scenarios where creating a new connection on every database request can lead to performance issues,
      resource consumption, and potential connection limits in the database server.

      Why Use Singleton for Database Connections?
      Single Connection: You want to maintain a single connection to the database throughout the lifecycle of the application.
      
      Efficiency: Opening and closing database connections repeatedly can be inefficient, and a Singleton ensures that the connection is reused.
      
      Resource Management: Opening too many connections to the database can lead to hitting connection limits or resource exhaustion. Singleton ensures that only one connection is used.
      
      Global Access: The Singleton provides global access to the same database connection object, which simplifies database operations across different parts of your application.
*/
#include <iostream>
#include <string>

class DatabaseConnection {
private:
    static DatabaseConnection* instance;
    std::string connectionString;

    // Private constructor to prevent instantiation
    DatabaseConnection(const std::string& connectionStr) : connectionString(connectionStr) {
        std::cout << "Database connection established: " << connectionString << std::endl;
    }

public:
    // Static method to get the instance of DatabaseConnection
    static DatabaseConnection* getInstance(const std::string& connectionStr) {
        if (instance == nullptr) {
            instance = new DatabaseConnection(connectionStr);  // Create the connection only once
        }
        return instance;
    }

    void executeQuery(const std::string& query) {
        std::cout << "Executing query: " << query << std::endl;
    }

    void closeConnection() {
        std::cout << "Closing database connection." << std::endl;
        // Connection close logic goes here.
    }
};

// Initialize static member to nullptr
DatabaseConnection* DatabaseConnection::instance = nullptr;

int main() {
    // Get the Singleton instance with a connection string
    DatabaseConnection* db1 = DatabaseConnection::getInstance("Server=myServerAddress;Database=myDataBase;");
    db1->executeQuery("SELECT * FROM users");

    // Try to get another instance, which should be the same as db1
    DatabaseConnection* db2 = DatabaseConnection::getInstance("Different Connection String");
    db2->executeQuery("SELECT * FROM orders");

    // Both db1 and db2 are referring to the same instance (same connection)
    db1->closeConnection();

    return 0;
}
