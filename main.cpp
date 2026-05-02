#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function prototypes
bool userLogin(string &username, string &password);
bool isValidName(string name);
bool isValidPhoneNumber(string phoneNumber);
void displayMenu(string items[], int prices[], int size);
void takeOrder(string items[], int prices[], int size, int inventory[], string &customerName, string &customerPhone);
int calculateTotal(int quantities[], int prices[], int size, float &tax);
void saveOrderFile(string items[], int quantities[], int prices[], int size, int total, float tax, float tip, string &customerName, string &customerPhone);
void saveCustomerFile(string &customerName, string &customerPhone);
void finalizeOrder(int quantities[], int size);
void applyDiscount(int &total, int &discount);
void manageInventory(string items[], int size, int inventory[]);
void saveInventoryFile(string items[], int inventory[], int size);
void loadInventoryFile(string items[], int inventory[], int size);
void manageTables(int tables[], int size);
void saveTableFile(int tables[], int size);
void loadTableFile(int tables[], int size);
void manageEmployees(string employeeNames[], int employeeHours[], int size);
void saveEmployeeFile(string names[], int hours[], int size);
void loadEmployeeFile(string names[], int hours[], int size);
void trackAttendance(string names[], int attendance[], int size);
void saveAttendanceFile(string names[], int attendance[], int size);
void loadAttendanceFile(string names[], int attendance[], int size);
void workWithUs();
void collectRating();
void manageSpicesInventory();
void manageDelivery();
void processPayment();
void addJobListing();
void showJobListings();
void calculateRevenue();

int main() {
    cout << "+=========================================+\n";
    cout << "|    WELCOME TO JAM DESI BITES RESTAURANT |\n";
    cout << "+=========================================+\n\n";

    int menuSize = 10;
    string foodItems[menuSize] = {
        "Chicken Tikka Karahi", "Chicken White Karahi", "Chicken Tikka", 
        "Kebab", "Dal Fry", "Dal Palak Mix", "Dal Chana", 
        "Aloo Keema", "Tandoori Naan", "Tandoori Roti"};
    int foodPrices[menuSize] = {180, 190, 200, 220, 100, 120, 100, 160, 25, 14};
    int inventory[menuSize] = {0};
    loadInventoryFile(foodItems, inventory, menuSize);

    int tables[10] = {0};
    loadTableFile(tables, 10);

    string employeeNames[10] = {""};
    int employeeHours[10] = {0};
    loadEmployeeFile(employeeNames, employeeHours, 10);

    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    if (userLogin(username, password)) {
        cout << "\nLogin successful!\n\n";
        
        string customerName, customerPhone;
        
        do {
            cout << "Enter Customer Name (Only alphabetic characters): ";
            cin >> customerName;
        } while (!isValidName(customerName));
        
        do {
            cout << "Enter Customer Phone Number (12 digits): ";
            cin >> customerPhone;
        } while (!isValidPhoneNumber(customerPhone));
        
        saveCustomerFile(customerName, customerPhone); 

        int choice;
        do {
            cout << "1. Take Order\n";
            cout << "2. Manage Inventory\n";
            cout << "3. Manage Tables\n";
            cout << "4. Track Employee Attendance\n";
            cout << "5. Manage Employees\n";
            cout << "6. Work With Us\n";
            cout << "7. Collect Rating\n";
            cout << "8. Manage Spices Inventory\n";
            cout << "9. Manage Delivery\n";
            cout << "10. Process Payment\n";
            cout << "11. Modify Careers\n";
            cout << "12. Calculate Revenue\n";
            cout << "13. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    takeOrder(foodItems, foodPrices, menuSize, inventory, customerName, customerPhone);
                    break;
                case 2:
                    manageInventory(foodItems, menuSize, inventory);
                    saveInventoryFile(foodItems, inventory, menuSize);
                    break;
                case 3:
                    manageTables(tables, 10);
                    saveTableFile(tables, 10);
                    break;
                case 4: {
                    int employeeAttendance[10] = {0};
                    trackAttendance(employeeNames, employeeAttendance, 10);
                    saveAttendanceFile(employeeNames, employeeAttendance, 10);
                    break;
                }
                case 5:
                    manageEmployees(employeeNames, employeeHours, 10);
                    saveEmployeeFile(employeeNames, employeeHours, 10);
                    break;
                case 6:
                    workWithUs();
                    break;
                case 7:
                    collectRating();
                    break;
                case 8:
                    manageSpicesInventory();
                    break;
                case 9:
                    manageDelivery();
                    break;
                case 10:
                    processPayment();
                    break;
                case 11:
                    addJobListing();
                    showJobListings();
                    break;
                case 12:
                    calculateRevenue();
                    break;
                case 13:
                    cout << "Exiting program. Goodbye!\n";
                    break;
                default:
                    cout << "Invalid Choice. Please try again.\n";
                    break;
            }
        } while (choice != 13);
    } else {
        cout << "Login failed. Exiting program.\n";
    }

    return 0;
}

bool userLogin(string &username, string &password) {
    ifstream userLoginFile("userlogin.txt");
    if (!userLoginFile.is_open()) {
        cout << "Unable to open userlogin file.\n";
        return false;
    }
    string usernameFile, passwordFile;
    while (userLoginFile >> usernameFile >> passwordFile) {
        if (usernameFile == username && passwordFile == password) {
            userLoginFile.close();
            return true;
        }
    }
    userLoginFile.close();
    return false;
}

bool isValidName(string name) {
    for (char c : name) {
        if (!isalpha(c)) {
            cout << "Invalid name. Only alphabetic characters are allowed.\n";
            return false;
        }
    }
    return true;
}

bool isValidPhoneNumber(string phoneNumber) {
    if (phoneNumber.length() != 12) {
        cout << "Invalid phone number. Please enter exactly 12 digits.\n";
        return false;
    }
    for (char c : phoneNumber) {
        if (!isdigit(c)) {
            cout << "Invalid phone number. Only digits are allowed.\n";
            return false;
        }
    }
    return true;
}

void displayMenu(string items[], int prices[], int size) {
    cout << "+=========================================+\n";
    cout << "|                   Menu                  |\n";
    cout << "+=========================================+\n";
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << items[i] << " - Rs." << prices[i] << endl;
    }
    cout << "+=========================================+\n\n";
}

void takeOrder(string items[], int prices[], int size, int inventory[], string &customerName, string &customerPhone) {
    int quantities[size] = {0};
    int choice;
    char moreItems;
    bool outOfStock = false;

    float tax = 0, tip = 0;

    do {
        displayMenu(items, prices, size);
        cout << "Select an item by number (1-" << size << "): ";
        cin >> choice;

        if (choice < 1 || choice > size) {
            cout << "Invalid selection. Please try again.\n";
            continue;
        }

        if (inventory[choice - 1] <= 0) {
            cout << "Sorry, " << items[choice - 1] << " is out of stock. Returning to menu.\n";
            outOfStock = true;
            break;
        }

        cout << "Enter quantity for " << items[choice - 1] << ": ";
        int quantity;
        cin >> quantity;

        if (quantity <= 0 || quantity > inventory[choice - 1]) {
            cout << "Invalid quantity. You cannot order more than the available stock.\n";
            continue;
        }

        quantities[choice - 1] += quantity;
        inventory[choice - 1] -= quantity;

        cout << "Would you like to order more items? (y/n): ";
        cin >> moreItems;

    } while (moreItems == 'y');

    if (outOfStock) {
        cout << "Order cannot be processed as some items are out of stock.\n";
        return;
    }

    finalizeOrder(quantities, size);
    int totalBill = calculateTotal(quantities, prices, size, tax);
    cout << "Enter tip amount (Rs.): ";
    cin >> tip;  
    int discount = 0;
    applyDiscount(totalBill, discount);
    cout << "Total Bill after discount: Rs. " << totalBill << endl;
    cout << "Tax: Rs." << tax << endl;
    cout << "Tip: Rs." << tip << endl;
    cout << "Total Bill after Tax and Tip: Rs." << (totalBill + tax + tip) << endl;
    saveOrderFile(items, quantities, prices, size, totalBill, tax, tip, customerName, customerPhone);
}

int calculateTotal(int quantities[], int prices[], int size, float &tax) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += quantities[i] * prices[i];
    }
    tax = total * 0.1;
    return total;
}

void saveOrderFile(string items[], int quantities[], int prices[], int size, int total, float tax, float tip, string &customerName, string &customerPhone) {
    ofstream totalBillFile("orderfile.txt", ios::app); 
    if (totalBillFile.is_open()) {
        totalBillFile << "Customer: " << customerName << ", Phone: " << customerPhone << endl;
        totalBillFile << "Order Summary:\n";
        for (int i = 0; i < size; i++) {
            if (quantities[i] > 0) {
                totalBillFile << items[i] << " x " << quantities[i] << " - Rs." << (quantities[i] * prices[i]) << endl;
            }
        }
        totalBillFile << "Total Bill: Rs." << total << endl;
        totalBillFile << "Tax: Rs." << tax << endl;
        totalBillFile << "Tip: Rs." << tip << endl;
        totalBillFile << "Total Bill after Tax and Tip: Rs." << (total + tax + tip) << endl;
        totalBillFile << "----------------------------------------\n";
        totalBillFile.close();
        cout << "Your order has been saved to orderfile.txt\n";
    } else {
        cout << "Unable to open file for writing.\n";
    }
}

void saveCustomerFile(string &customerName, string &customerPhone) {
    ofstream customerFile("customers.txt", ios::app); 
    if (customerFile.is_open()) {
        customerFile << customerName << "\n" << customerPhone << endl;
        customerFile.close();
        cout << "Customer information has been saved.\n";
    } else {
        cout << "Unable to save customer information.\n";
    }
}

void finalizeOrder(int quantities[], int size) {
    char confirm;
    cout << "Do you want to finalize your order? (y/n): ";
    cin >> confirm;
    if (confirm == 'y') {
        cout << "Your order has been finalized. No further modification allowed.\n";
    }
}

void applyDiscount(int &total, int &discount) {
    if (total > 500) {
        discount = total * 0.1;
        total -= discount;
        cout << "Discount applied: Rs." << discount << endl;
    }
}

void manageInventory(string items[], int size, int inventory[]) {
    int choice;
    do {
        cout << "+=========================================+\n";
        cout << "|       Inventory Management              |\n";
        cout << "+=========================================+\n\n";
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ". " << items[i] << " - Available: " << inventory[i] << endl;
        }
        cout << "Enter the item to update inventory (0 to exit): ";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > size) {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        cout << "Do you want to (1) Add to existing quantity or (2) Set new quantity? ";
        int updateOption;
        cin >> updateOption;

        if (updateOption == 1) {
            cout << "Enter quantity to add to " << items[choice - 1] << ": ";
            int addQuantity;
            cin >> addQuantity;

            if (addQuantity < 0) {
                cout << "Invalid quantity. Please enter a non-negative value.\n";
                continue;
            }

            inventory[choice - 1] += addQuantity;
            cout << "Inventory for " << items[choice - 1] << " updated successfully!\n";

        } else if (updateOption == 2) {
            cout << "Enter new inventory quantity for " << items[choice - 1] << ": ";
            int newQuantity;
            cin >> newQuantity;

            if (newQuantity < 0) {
                cout << "Invalid quantity. Please enter a non-negative value.\n";
                continue;
            }

            inventory[choice - 1] = newQuantity;
            cout << "Inventory for " << items[choice - 1] << " updated successfully!\n";

        } else {
            cout << "Invalid option. Please select 1 or 2.\n";
        }

    } while (true);
}

void saveInventoryFile(string items[], int inventory[], int size) {
    ofstream inventoryFile("inventory.txt");
    if (inventoryFile.is_open()) {
        for (int i = 0; i < size; i++) {
            inventoryFile << inventory[i] << endl;
        }
        inventoryFile.close();
        cout << "Inventory saved to file.\n";
    } else {
        cout << "Unable to save inventory to file.\n";
    }
}

void loadInventoryFile(string items[], int inventory[], int size) {
    ifstream inventoryFile("inventory.txt");
    if (inventoryFile.is_open()) {
        for (int i = 0; i < size; i++) {
            inventoryFile >> inventory[i];
        }
        inventoryFile.close();
    } else {
        cout << "No inventory file found. Default values will be used.\n";
    }
}

void manageTables(int tables[], int size) {
    int choice;
    do {
        cout << "+=========================================+\n";
        cout << "|            Table Management             |\n";
        cout << "+=========================================+\n";
        for (int i = 0; i < size; i++) {
            cout << "Table " << i + 1 << ": " << (tables[i] ? "Occupied" : "Available") << endl;
        }
        cout << "\nEnter table number to toggle status (0 to exit): ";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > size) {
            cout << "Invalid table number. Please try again.\n";
            continue;
        }

        tables[choice - 1] = !tables[choice - 1];
        cout << "Table " << choice << " is now " << (tables[choice - 1] ? "Occupied" : "Available") << ".\n";
    } while (true);
}

void saveTableFile(int tables[], int size) {
    ofstream tableFile("tables.txt");
    if (tableFile.is_open()) {
        for (int i = 0; i < size; i++) {
            tableFile << tables[i] << endl;
        }
        tableFile.close();
        cout << "Table data saved to file.\n";
    } else {
        cout << "Unable to save table data to file.\n";
    }
}

void loadTableFile(int tables[], int size) {
    ifstream tableFile("tables.txt");
    if (tableFile.is_open()) {
        for (int i = 0; i < size; i++) {
            tableFile >> tables[i];
        }
        tableFile.close();
    } else {
        cout << "No table file found. Default values will be used.\n";
    }
}

void manageEmployees(string employeeNames[], int employeeHours[], int size) {
    int choice;
    do {
        cout << "+=========================================+\n";
        cout << "|         Employee Management             |\n";
        cout << "+=========================================+\n";
        for (int i = 0; i < size; i++) {
            if (!employeeNames[i].empty()) {
                cout << i + 1 << ". " << employeeNames[i] << " - Hours: " << employeeHours[i] << endl;
            } else {
                cout << i + 1 << ". (No employee)\n";
            }
        }

        cout << "Enter employee number to modify hours (0 to exit): ";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > size) {
            cout << "Invalid choice. Please try again.\n";
            continue;
        }

        cout << "Enter new name for employee (Leave blank to keep previous): ";
        cin.ignore();
        string name;
        getline(cin, name);
        if (!name.empty()) {
            employeeNames[choice - 1] = name;
        }

        cout << "Enter new working hours for " << employeeNames[choice - 1] << ": ";
        int hours;
        cin >> hours;
        employeeHours[choice - 1] = hours;

    } while (true);
}

void saveEmployeeFile(string names[], int hours[], int size) {
    ofstream employeeFile("employees.txt");
    if (employeeFile.is_open()) {
        for (int i = 0; i < size; i++) {
            employeeFile << names[i] << "\n" << hours[i] << endl;
        }
        employeeFile.close();
        cout << "Employee data saved to file.\n";
    } else {
        cout << "Unable to save employee data to file.\n";
    }
}

void loadEmployeeFile(string names[], int hours[], int size) {
    ifstream employeeFile("employees.txt");
    if (employeeFile.is_open()) {
        for (int i = 0; i < size; i++) {
            getline(employeeFile, names[i]);
            employeeFile >> hours[i];
            employeeFile.ignore();  // Ignore the newline
        }
        employeeFile.close();
    } else {
        cout << "No employee file found. Default values will be used.\n";
    }
}

void trackAttendance(string names[], int attendance[], int size) {
    int choice;
    do {
        cout << "+=========================================+\n";
        cout << "|         Attendance Tracking             |\n";
        cout << "+=========================================+\n";
        for (int i = 0; i < size; i++) {
            if (!names[i].empty()) {
                cout << i + 1 << ". " << names[i] << " - Attendance: " << attendance[i] << endl;
            } else {
                cout << i + 1 << ". (No employee)\n";
            }
        }

        cout << "Enter employee number to toggle attendance (0 to exit): ";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > size) {
            cout << "Invalid employee number. Please try again.\n";
            continue;
        }

        attendance[choice - 1] = !attendance[choice - 1];
        cout << names[choice - 1] << "'s attendance is now marked as " 
             << (attendance[choice - 1] ? "Present" : "Absent") << ".\n";
    } while (true);
}

void saveAttendanceFile(string names[], int attendance[], int size) {
    ofstream attendanceFile("attendance.txt");
    if (attendanceFile.is_open()) {
        for (int i = 0; i < size; i++) {
            attendanceFile << names[i] << "\n" << attendance[i] << endl;
        }
        attendanceFile.close();
        cout << "Attendance data saved to file.\n";
    } else {
        cout << "Unable to save attendance data to file.\n";
    }
}

void loadAttendanceFile(string names[], int attendance[], int size) {
    ifstream attendanceFile("attendance.txt");
    if (attendanceFile.is_open()) {
        for (int i = 0; i < size; i++) {
            getline(attendanceFile, names[i]);
            attendanceFile >> attendance[i];
        }
        attendanceFile.close();
    } else {
        cout << "No attendance file found. Default values will be used.\n";
    }
}

void workWithUs() {
    string position, name, phone, experience;
    int choice;

    cout << "+=========================================+\n";
    cout << "|           Work With Us                  |\n";
    cout << "+=========================================+\n";
    cout << "Available Positions:\n";
    cout << "1. Waiter\n";
    cout << "2. Chef\n";
    cout << "3. Manager\n";
    cout << "Enter the position you are applying for (1-3): ";
    cin >> choice;

    switch (choice) {
        case 1:
            position = "Waiter";
            break;
        case 2:
            position = "Chef";
            break;
        case 3:
            position = "Manager";
            break;
        default:
            cout << "Invalid choice. Returning to main menu.\n";
            return;
    }

    cout << "Enter your Name: ";
    cin >> name;
    cout << "Enter your Phone Number: ";
    cin >> phone;
    cout << "Enter your Experience (in years): ";
    cin >> experience;

    ofstream jobApplicationFile("applications.txt", ios::app);
    if (jobApplicationFile.is_open()) {
        jobApplicationFile << "Position: " << position << "\n";
        jobApplicationFile << "Name: " << name << "\n";
        jobApplicationFile << "Phone: " << phone << "\n";
        jobApplicationFile << "Experience: " << experience << " years\n";
        jobApplicationFile << "----------------------------------------\n";
        jobApplicationFile.close();
        cout << "Your application has been submitted successfully!\n";
    } else {
        cout << "Error saving application. Please try again later.\n";
    }
}

void collectRating() {
    int food, service, experience;
    cout << "+=========================================+\n";
    cout << "|           Collect Rating                |\n";
    cout << "+=========================================+\n";
    cout << "Rate food (1 to 5): ";
    cin >> food;
    cout << "Rate service (1 to 5): ";
    cin >> service;
    cout << "Rate overall experience (1 to 5): ";
    cin >> experience;
    
    ofstream outFile("ratings.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "Food: " << food << ", Service: " << service << ", Experience: " << experience << endl;
        outFile.close();
        cout << "Thank you for your feedback!" << endl;
    } else {
        cout << "Error opening file!" << endl;
    }
}

const int MAX_SPICES = 100;
string spiceNames[MAX_SPICES];
int spiceQuantities[MAX_SPICES];
string spiceExpiryDates[MAX_SPICES];
int spiceCount = 0;

void saveInventoryToFile() {
    ofstream outFile("spices_inventory.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < spiceCount; i++) {
            outFile << spiceNames[i] << "," << spiceQuantities[i] << "," << spiceExpiryDates[i] << endl;
        }
        outFile.close();
        cout << "Spices inventory saved to file.\n";
    } else {
        cout << "Unable to save spices inventory to file.\n";
    }
}

void loadInventoryFromFile() {
    ifstream inFile("spices_inventory.txt");
    if (inFile.is_open()) {
        spiceCount = 0;
        string line;
        while (getline(inFile, line)) {
            size_t comma1 = line.find(',');
            size_t comma2 = line.find(',', comma1 + 1);

            if (comma1 != string::npos && comma2 != string::npos) {
                spiceNames[spiceCount] = line.substr(0, comma1);
                spiceQuantities[spiceCount] = stoi(line.substr(comma1 + 1, comma2 - comma1 - 1));
                spiceExpiryDates[spiceCount] = line.substr(comma2 + 1);
                spiceCount++;
            }
        }
        inFile.close();
        cout << "Spices inventory loaded from file.\n";
    } else {
        cout << "No previous inventory found. Starting fresh.\n";
    }
}

void manageSpicesInventory() {
    loadInventoryFromFile();

    int choice;
    do {
        cout << "+=========================================+\n";
        cout << "|       Spices Inventory Management       |\n";
        cout << "+=========================================+\n\n";
        for (int i = 0; i < spiceCount; i++) {
            cout << i + 1 << ". " << spiceNames[i] << " - Quantity: " << spiceQuantities[i] 
                 << ", Expiry Date: " << spiceExpiryDates[i] << endl;
        }
        cout << "\n1. Add New Spice\n";
        cout << "2. Update Spice Quantity\n";
        cout << "3. Delete Spice\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                if (spiceCount >= MAX_SPICES) {
                    cout << "Spices inventory is full. Cannot add more spices.\n";
                    break;
                }
                string name, expiryDate;
                int quantity;
                cout << "Enter spice name: ";
                cin.ignore(); // To ignore the newline character left in the buffer
                getline(cin, name);
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter expiry date (dd-mm-yyyy): ";
                cin.ignore(); // To ignore the newline character left in the buffer
                getline(cin, expiryDate);

                spiceNames[spiceCount] = name;
                spiceQuantities[spiceCount] = quantity;
                spiceExpiryDates[spiceCount] = expiryDate;
                spiceCount++;

                cout << "Spice added successfully!\n";
                break;
            }
            case 2: {
                if (spiceCount == 0) {
                    cout << "No spices available to update.\n";
                    break;
                }
                int index;
                cout << "Enter the number of the spice to update: ";
                cin >> index;
                if (index < 1 || index > spiceCount) {
                    cout << "Invalid selection. Please try again.\n";
                    break;
                }
                cout << "Enter new quantity: ";
                cin >> spiceQuantities[index - 1];
                cout << "Enter new expiry date (dd-mm-yyyy): ";
                cin.ignore(); 
                getline(cin, spiceExpiryDates[index - 1]);
                cout << "Spice updated successfully!\n";
                break;
            }
            case 3: {
                if (spiceCount == 0) {
                    cout << "No spices available to delete.\n";
                    break;
                }
                int index;
                cout << "Enter the number of the spice to delete: ";
                cin >> index;
                if (index < 1 || index > spiceCount) {
                    cout << "Invalid selection. Please try again.\n";
                    break;
                }
                for (int i = index - 1; i < spiceCount - 1; i++) {
                    spiceNames[i] = spiceNames[i + 1];
                    spiceQuantities[i] = spiceQuantities[i + 1];
                    spiceExpiryDates[i] = spiceExpiryDates[i + 1];
                }
                spiceCount--;
                cout << "Spice deleted successfully!\n";
                break;
            }
            case 4:
                cout << "Exiting spices inventory management.\n";
                saveInventoryToFile();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);
}

void manageDelivery() {
    string deliveryPerson;
    string orderDetails;
    
    cout << "Enter delivery person name: ";
    cin.ignore(); 
    getline(cin, deliveryPerson);
    cout << "Enter order details: ";
    getline(cin, orderDetails);

    ofstream outFile("delivery.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "Delivery Person: " << deliveryPerson << ", Order: " << orderDetails << endl;
        outFile.close();
        cout << "Delivery managed successfully!" << endl;
    } else {
        cout << "Error opening file!" << endl;
    }
}

void processPayment() {
    int paymentChoice;
    float amount;

    cout << "+=========================================+\n";
    cout << "|           Payment Options               |\n";
    cout << "+=========================================+\n";
    cout << "1. Credit/Debit Card\n";
    cout << "2. Jazz Cash/Easypaisa\n";
    cout << "3. Cash\n";
    cout << "Enter your payment method (1-3): ";
    cin >> paymentChoice;

    if (paymentChoice < 1 || paymentChoice > 3) {
        cout << "Invalid choice. Payment processing canceled.\n";
        return;
    }

    cout << "Enter amount: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. Payment processing canceled.\n";
        return;
    }

    string paymentMethod;
    switch (paymentChoice) {
        case 1:
            paymentMethod = "Credit/Debit Card";
            break;
        case 2:
            paymentMethod = "JazzCash/Easypaisa";
            break;
        case 3:
            paymentMethod = "Cash";
            break;
    }

    ofstream outFile("payments.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "Payment Method: " << paymentMethod << ", Amount: " << amount << endl;
        outFile.close();
        cout << "Payment processed successfully using " << paymentMethod << "!\n";
    } else {
        cout << "Error opening file! Payment details could not be saved.\n";
    }
}

void addJobListing() {
    string jobTitle;
    string jobDescription;
    
    cout << "+=========================================+\n";
    cout << "|           Modified Career               |\n";
    cout << "+=========================================+\n";
    
    cout << "Enter job title: ";
    cin.ignore(); 
    getline(cin, jobTitle);
    cout << "Enter job description: ";
    getline(cin, jobDescription);

    ofstream outFile("careers.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "Job Title: " << jobTitle << ", Description: " << jobDescription << endl;
        outFile.close();
        cout << "Job listing added!" << endl;
    } else {
        cout << "Error opening file!" << endl;
    }
}

void showJobListings() {
    ifstream inFile("careers.txt");
    string line;
    if (inFile.is_open()) {
        cout << "Job Listings: \n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Error opening file!" << endl;
    }
}

void calculateRevenue() {
    ifstream orderFile("orderfile.txt");
    if (!orderFile.is_open()) {
        cout << "No order records found. Revenue is Rs. 0.\n";
        return;
    }

    float totalRevenue = 0;
    string line;
    while (getline(orderFile, line)) {
        // Look for the line that contains "Total Bill after Tax and Tip: Rs."
        if (line.find("Total Bill after Tax and Tip: Rs.") != string::npos) {
            // Extract the amount from the line
            size_t pos = line.find("Rs.") + 3; // Position after "Rs."
            string amountStr = line.substr(pos); // Extract the amount
            float amount = stof(amountStr); // Convert string to float
            totalRevenue += amount;
        }
    }

    orderFile.close();
    cout << "+=========================================+\n";
    cout << "|           Total Revenue                 |\n";
    cout << "+=========================================+\n";
    cout << "Total Revenue: Rs. " << totalRevenue << endl;
}