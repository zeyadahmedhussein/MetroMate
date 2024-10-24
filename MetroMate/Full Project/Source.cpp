#include <iostream>
#include <string>
#include <ctime>
#include<cstdlib>
#include <cstdio>
#include<fstream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <iomanip>
#include <regex>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#define maxStations 100
#define MaxUser 10
#define MaxSub 100
using namespace std;
int constantPrice[4] = {6,8,12,15};
int indexOfUsers = 0;
int NumberOfStations;
int firstLineStations, secondLineStations, thirdLineStations;
int lineStations[3] = { firstLineStations, secondLineStations, thirdLineStations };
int transitionStations[10];




struct Ride {
    string rideID;
    string checkInStation;
    string checkOutStation;
    string rideDate;
    float cost;
};
struct Subscription {
    string subName;
    string startDate;
    string endDate;
    int ValidityDays;
    char index;
    int stage;
    int ridesCount;
    float price[4];
    int subscriptionCount;
    int fullRides;
}SubTypes[4];
struct Account {
    string username;
    string email;
    string password;
};
struct User {
    int id;
    Account UserAccount;
    float balance;
    Subscription Sub;
    Ride ridedetails[200];
    bool SubFound = false;
    bool signedUp = false;
    int ridesCount;
    float walletMoney;
    int tickets=0;
};

struct MetroStations {
    int id, line, zone, numberOfCheckIn, numberOfCheckOut;
    char symbol;
    string name;
};
MetroStations stations[3][maxStations];
struct destination {
    string station;
    int id, line;

};
struct departure {
    string station;
    int id, line;

};
void printErrorMessage(string message) {
    // ANSI escape code for red color
    string redColor = "\033[1;31m";
    // ANSI escape code to reset color to default
    string resetColor = "\033[0m";


    cout << redColor << message << resetColor << endl;
}
void printSuccessMessage(string message) {
    // ANSI escape code for red color
    string greenColor = "\033[1;32m";
    // ANSI escape code to reset color to default
    string resetColor = "\033[0m";


    cout << greenColor << message << resetColor << endl;
}
bool isBalancePositive(float balance) {
    return balance > 0;
}
Subscription UsersSubscriptionTypes[MaxSub];
User users[MaxUser];
bool login_status;
void DeletScreen() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("CLS");
}
void view_map()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Map");

    sf::Texture map;
    if (!map.loadFromFile("map.jpg"))
    {
        std::cout << "Can't find the map file.\n";
        system("pause");
    }

    sf::Sprite mapp(map);
    mapp.setPosition(0, 0);
    mapp.setScale(2.62, 1.5);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(mapp);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {

            window.close();
        }


        window.display();


    }


}
int readUserCount() {
    int count = 0;
    ifstream infile("user_count.txt");

    if (infile.is_open()) {
        infile >> count;
        infile.close();
    }
    else {
        cerr << "Warning: User count file not found. Assuming initial count as 0." << endl;
    }

    return count;
}
int realUsers = readUserCount();
departure userDeparture;
destination userDestination;
void ViewMetroStations(int lineNumber);
void UserIdGenerator() {

    users[realUsers].id = realUsers;
}
void IncrementUserNumber() {
    realUsers++;
}
void DecrementUserNumber() {
    realUsers--;
}
bool findEmail(string email) {
    for (int i = 0; i < realUsers; i++) {
        if (email == users[i].UserAccount.email)
            return true;
    }
    return false;
}
bool find(string email, string password) {
    for (int i = 0; i < realUsers; i++) {
        if (email == users[i].UserAccount.email && password == users[i].UserAccount.password) {
            indexOfUsers = users[i].id;
            return true;

        }
    }
    return false;
}
void StoreTheNumberOfRides() {
    ofstream outfile("numberRides.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            outfile << users[i].Sub.ridesCount << endl;

        }
        outfile.close();
    }
    else {
        cerr << "Error: Could not open user count file." << endl;
    }
}
void ReadTheNumberOfRides() {
    fstream infile("numberRides.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            infile >> users[i].Sub.ridesCount;


        }
        infile.close();
    }
    else {
        cerr << "Error: Could not open user count file." << endl;
    }
}
void StoreTheNumberOfUsers() {
    ofstream outfile("user_count.txt");

    if (outfile.is_open()) {
        outfile << realUsers << endl;
        outfile.close();
    }
    else {
        cerr << "Error: Could not open user count file." << endl;
    }
}
void StoreTheConstantPrice() {
    ofstream outfile("constantprices.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < 4; i++) {
            outfile << constantPrice[i] << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open users file." << endl;
    }
}
void ReadFromFileConstantPrice() {
    ifstream infile("constantprices.txt");

    if (infile.is_open()) {
        for (int i = 0; i < 4; i++) {
            infile >> constantPrice[i];
        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open users file." << endl;
    }
}
void StoreTheDataOfUsers() {
    ofstream outfile("users.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            outfile << users[i].UserAccount.email << " " << users[i].UserAccount.password << " "
                << users[i].id << " " << users[i].balance << " " << users[i].Sub.subName << " " << users[i].SubFound << " " << users[i].walletMoney << " " << users[i].tickets << " " << users[i].Sub.ridesCount <<" "<<users[i].Sub.fullRides << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open users file." << endl;
    }
}
void StoreTheDataOfRides() {
    ofstream outfile("rides.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            for (int j = 0; j < users[i].Sub.ridesCount; j++) {
                outfile << users[i].ridedetails[j].checkInStation << " " << users[i].ridedetails[j].checkOutStation<<" " << users[i].ridedetails[j].rideID
                    << " " << users[i].ridedetails[j].cost << " " << users[i].ridedetails[j].rideDate << endl;
            }
            cout << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open rides file." << endl;
    }
}
void ReadFromFileTheDataOfRides() {
    ifstream infile("rides.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            for (int j = 0; j < 200 && j < users[i].Sub.ridesCount; j++) {
                infile >> users[i].ridedetails[j].checkInStation >> users[i].ridedetails[j].checkOutStation>> users[i].ridedetails[j].rideID
                    >> users[i].ridedetails[j].cost >> users[i].ridedetails[j].rideDate;
            }
        }
        infile.close();
    }
    else {
        cerr << "Error: Could not open rides file." << endl;
    }
}
bool buyTicket;
void ReadFromFileTheDataOfUsers() {
    ifstream infile("users.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realUsers; i++) {
            infile >> users[i].UserAccount.email >> users[i].UserAccount.password
                >> users[i].id >> users[i].balance >> users[i].Sub.subName >> users[i].SubFound>>users[i].walletMoney>>users[i].tickets>>users[i].Sub.ridesCount>>users[i].Sub.fullRides;
        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open users file." << endl;
    }
}
bool SignUp() {
    User temp;

    cout << "Enter your name or press 0 to exit: \n";
    cin >> temp.UserAccount.username;
    if (temp.UserAccount.username == "0") {
        cout << "Exiting sign-up..." << endl;
        return false;
    }
    else {
        users[realUsers].UserAccount.username = temp.UserAccount.username;
    }

    string email;
    while (true) {
        cout << "Enter your email or press 0 to exit: \n";
        cin >> email;
        if (email == "0") {
            cout << "Exiting sign-up..." << endl;
            return false;
        }
        if (findEmail(email)) {
            cout << "This email already exists. Please enter another email." << endl;
        }
        else if (!regex_match(email, regex(".+@.+(\\.com)"))) {
            cout << "Invalid email format. " << endl;
        }
        else {
            temp.UserAccount.email = email;
            users[realUsers].UserAccount.email = email;
            break;
        }
    }

    string confirm_email;
    while (true) {
        cout << "Confirm your email or press 0 to exit: \n";
        cin >> confirm_email;
        if (confirm_email == "0") {
            cout << "Exiting sign-up..." << endl;
            return false;
        }
        if (temp.UserAccount.email != confirm_email) {
            cout << "Emails do not match. Please re-enter your email." << endl;
        }
        else {
            break; 
        }
    }

    cout << "Enter your password or press 0 to exit: \n";
    cin >> temp.UserAccount.password;
    if (temp.UserAccount.password == "0") {
        cout << "Exiting sign-up..." << endl;
        return false;
    }

    string confirm_password;
    while (true) {
        cout << "Confirm your password or press 0 to exit: "<<endl;
        cin >> confirm_password;
        if (confirm_password == "0") {
            cout << "Exiting sign-up..." << endl;
            return false;
        }
        if (temp.UserAccount.password != confirm_password) {
            cout << "Passwords do not match. Please re-enter your password." << endl;
        }
        else {
            break; // Break out of the loop if the passwords match
        }
    }

    cout << "Enter your balance or press 0 to exit: \n";
    cin >> temp.balance;
    if (temp.balance == 0) {
        cout << "Exiting sign-up..." << endl;
        return false;
    }

    while (temp.balance < 50 || temp.balance < 0) {
        if (temp.balance < 0) {
            cout << "Balance cannot be negative!" << endl;
        }
        else if (temp.balance < 50) {
            cout << "Minimum balance is 50. Please enter another balance: ";
        }
        cin >> temp.balance;
        if (temp.balance == 0) {
            cout << "Exiting sign-up..." << endl;
            return false;
        }
    }

    // If all data is entered correctly, proceed to store the user's information
    users[realUsers].UserAccount.password = temp.UserAccount.password;
    users[realUsers].balance = temp.balance;
    UserIdGenerator();
    indexOfUsers = users[realUsers].id;
    printSuccessMessage("Signed Up successfully!");
    IncrementUserNumber();
    DeletScreen();

    return true;
}
bool isAdmin;
void UpdatePersonalInformation();
bool Login() {
    char choice;
    User temp;
    cout << "Enter your Email or you can press 0 at any time to exit 0 to exit: "<<endl;
    cin >> temp.UserAccount.email;
    if (temp.UserAccount.email == "0") {
        cout << "Exiting login..." << endl;
        return false;
    }

    cout << "Enter your Password or press 0 to exit: ";
    cin >> temp.UserAccount.password;
    
    if (temp.UserAccount.password == "0") {
        printErrorMessage("Exiting login...");
        return false;
    }

    if (temp.UserAccount.email == "admin.com" && temp.UserAccount.password == "1") {
        isAdmin = true;
        printSuccessMessage("Logged in as admin!");
        DeletScreen();
        login_status = true;
        return true;
    }

    if (find(temp.UserAccount.email, temp.UserAccount.password)) {
        printSuccessMessage("Logged in successfully! ");
        DeletScreen();
        login_status = true;
        users[indexOfUsers].SubFound = true;
        return true;
    }
   
    else {
        printErrorMessage("This user doesn't exist!");
        DeletScreen();
        return false;
    }
}
int readrealSub() {
    int count = 0;
    ifstream infile("realsub.txt");

    if (infile.is_open()) {
        infile >> count;
        infile.close();
    }
    else {
        cerr << "Warning: User count file not found. Assuming initial count as 0." << endl;
    }

    return count;
}
int realSub = readrealSub();
void StoreTheDataOfSub() {
    ofstream outfile("datasub.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realSub; i++) {
            // Write the subscription data and prices separately
            outfile << SubTypes[i].subName << " " << SubTypes[i].index << " "
                << " " << SubTypes[i].ValidityDays << " " << SubTypes[i].ridesCount ;
            outfile << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open SubData file." << endl;
    }
}
void StoreThePrices() {
    ofstream outfile("price.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realSub; i++) {
            for (int j = 0; j < 4; j++) {
                outfile << SubTypes[i].price[j] << " "; // Access SubTypes[i].price[j]
            }
            outfile << endl; // Add a newline after each set of prices for clarity
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open prices file." << endl;
    }
}
void ReadFromFileThePrices() {
    ifstream infile("price.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realSub; i++) {
            for (int j = 0; j < 4; j++) {
                infile >> SubTypes[i].price[j];
            }

        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open prices file." << endl;
    }
}
void ReadFromFileTheDataOfSub() {
    ifstream infile("datasub.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realSub; i++) {
            // Read the subscription data and prices separately
            infile >> SubTypes[i].subName >> SubTypes[i].index
                >> SubTypes[i].ValidityDays >> SubTypes[i].ridesCount;
           
        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open SubData file." << endl;
    }
}
void StoreTheRealSub() {
    ofstream outfile("realsub.txt");

    if (outfile.is_open()) {
        outfile << realSub << endl;
        outfile.close();
    }
    else {
        cerr << "Error: Could not open user count file." << endl;
    }
}
void ModifySubscriptionAdmin() {
    int NewValidity = 0;
    int NewRides = 0;
    string NewName;
    char id;

    cout << "Enter the type of the Subscription (S for student / M for public monthly / A for public annual / W for wallet):" << endl;
    cin >> id;

    for (int i = 0; i < realSub; i++) {
        if (id == SubTypes[i].index) {
            // Display subscription details before editing
            cout << "Subscription details before editing:\n";
            cout << left << setw(20) << "Name: " << SubTypes[i].subName << "\n";
            cout << left << setw(20) << "Validity Days: " << SubTypes[i].ValidityDays << " days\n";
            cout << left << setw(20) << "Trips Count: " << SubTypes[i].ridesCount << " trips\n";
            cout << "-----------------------------------------------------------" << endl;

            int choice;
            do {
                cout << "1 ---> Edit name" << endl << "2 ---> Edit Validity Days" << endl << "3 ---> Edit Trips Count" << endl << "4 ---> Exit" << endl; 
                cin >> choice;

                switch (choice) {
                case 1:
                    cout << "Enter the new name for the subscription for users:" << endl;
                    cin >> NewName;
                    SubTypes[i].subName = NewName;
                    break;
                case 2:
                    cout << "Enter the new Validity days of subscription:" << endl;
                    cin >> NewValidity;
                    if (!isBalancePositive(NewValidity)) {
                        printErrorMessage("Validity days cannot be zero or negative. Do you want to enter a different value? (y/n)");
                        char response;
                        cin >> response;
                        if (response == 'n' || response == 'N') {
                            break;
                        }
                    }
                    SubTypes[i].ValidityDays = NewValidity;
                    break;
                case 3:
                    cout << "Enter the new Trips of subscription:" << endl;
                    cin >> NewRides;
                    if (!isBalancePositive(NewRides)) {
                        printErrorMessage("Trips count cannot be zero or negative. Do you want to enter a different value? (y/n)");
                        char response;
                        cin >> response;
                        if (response == 'n' || response == 'N') {
                            break;
                        }
                    }
                    SubTypes[i].ridesCount = NewRides;
                    break;
                case 4: // Added option 4: Exit
                printErrorMessage("Exiting...");
                    return; // Exit the function
                default:
                    printErrorMessage("Invalid option. Please enter a valid option.");
                    // Clear input buffer
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Updated here
                    break;
                }
            } while (choice != 4); // Repeat until the user chooses to exit

            // Display subscription details after editing if no negative number was entered
            if (choice != 4 && (isBalancePositive(NewValidity) && isBalancePositive(NewRides))) {
                cout << "Subscription details after editing:\n";
                cout << left << setw(20) << "Name: " << SubTypes[i].subName << "\n";
                cout << left << setw(20) << "Validity Days: " << SubTypes[i].ValidityDays << " days\n";
                cout << left << setw(20) << "Trips Count: " << SubTypes[i].ridesCount << " trips\n";
                cout << "-----------------------------------------------------------" << endl;

                printSuccessMessage("Subscription successfully edited!");
            }
            return;
        }
    }
    printErrorMessage("Subscription not found!");
}
void DeleteSubAdmin() {
    char id;
    bool validInput = false;

    do {
        cout << "Enter the type of the Subscription you want to delete (S for student / M for public monthly / A for public annual / W for wallet):" << endl;
        cin >> id;

        // Check if the entered option is valid
        if (id == 'S' || id == 'M' || id == 'A' || id == 'W') {
            validInput = true;
        }
        else {
            cout << "Invalid option! Please enter a valid option." << endl;
            // Clear input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!validInput);

    bool found = false; // Flag to check if the subscription was found and deleted

    for (int i = 0; i < realSub; i++) {
        if (id == SubTypes[i].index) {
            // Display subscription details before deletion
            cout << "Subscription details before deletion:\n";
            cout <<  "Name: " << SubTypes[i].subName << "\n";
            cout << "Validity Days: " << SubTypes[i].ValidityDays << " days\n";
            cout  << "Trips Count: " << SubTypes[i].ridesCount << " trips\n";
            cout << "-----------------------------------------------------------" << endl;

            // Shift the elements to fill the gap
            for (int j = i; j < realSub - 1; j++) {
                SubTypes[j] = SubTypes[j + 1];
            }
            realSub--; // Decrement the count of subscriptions
            found = true;
            cout << "Subscription successfully deleted!\n";
            return;
        }
    }

    if (!found) {
        cout << "Subscription not found!\n";
    }
}
void ViewSubAdmin() {
    string dashes(120, '-');  // Create a string of 120 dashes
    
    cout << "\nSubscriptions:\n";
    cout << left << setw(30) << "Name" << setw(15) << "Validity Days" << "      " << "Trips Count" << endl;
    cout << dashes << endl;
    for (int i = 0; i < realSub; i++) {
        cout << left << setw(30) << SubTypes[i].subName
            << SubTypes[i].ValidityDays << " days" << "           "
            << SubTypes[i].ridesCount << " trips" << endl;
        cout << dashes << endl;
    }
}
void AdminMenuSubscriptionManagement() {
    int choice;
    do {
        cout << "\nAdmin Menu:\n";
        cout << "1. Modify Subscription\n";
        cout << "2. Delete Subscription\n";
        cout << "3. View Subscriptions\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 4) {
            cout << "Invalid choice. Please enter a valid option.\n";

            continue;
        }

        switch (choice) {
        case 1:
            ModifySubscriptionAdmin();
            break;
        case 2:
            DeleteSubAdmin();
            break;
        case 3:
            ViewSubAdmin();
            break;
        case 4:
            cout << "Exiting Admin Menu...\n";
            break;
        }
    } while (choice != 4);
}
void ViewUsersAccountsAdmin() {
    cout << "Accounts:\n";
    for (int i = 0; i < realUsers; i++) {
        cout << left << setw(20) << "Email: " << users[i].UserAccount.email << "\n";
        cout << left << setw(20) << "Password: " << users[i].UserAccount.password << "\n";
        cout << left << setw(20) << "ID: " << users[i].id << "\n";
        cout << left << setw(20) << "Balance: " << users[i].balance << "\n";
        cout << left << setw(20) << "Subscription: " << users[i].Sub.subName << "\n";
        cout << left << setw(20) << "Stage: " << users[i].Sub.stage << "\n";
        cout << left << setw(20) << "Start Date: " << users[i].Sub.startDate << "\n";
        cout << left << setw(20) << "End Date: " << users[i].Sub.endDate << "\n";

        cout << "-----------------------------------------------------------" << endl;
    }
}
void EditUsersAccountsAdmin() {
    string NewEmail;
    string NewPassword;
    int id;
    ViewUsersAccountsAdmin();
    cout << "Enter the ID of the user:" << endl;
    cin >> id;
    for (int i = 0; i < realUsers; i++) {

        if (id == users[i].id) {
            int choice;
            cout << "1 ---> Edit email" << endl << "2 ---> Edit Password" << endl;
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter the new email for the user:" << endl;
                cin >> NewEmail;
                do {
                    cin.ignore();
                    cin >> NewEmail;
                    if (findEmail(NewEmail)) {
                        cout << "This email already exists. Please enter another email." << endl;
                    }
                    else if (!regex_match(NewEmail, regex(".+@.+(\\.com)"))) {
                        cout << "Invalid email format. Please enter a valid email: ";
                    }
                    else {
                        users[i].UserAccount.email = NewEmail;
                        break;
                    }
                } while (true);
                
                break;
            case 2:
                cout << "Enter the new password for the user:" << endl;
                cin >> NewPassword;
                users[i].UserAccount.password = NewPassword;
                break;
            default:
                cout << "Invalid option" << endl;
                break;
            }

        }
    }


}
void DeleteUsersAccountsAdmin() {
    for (int i = 0; i < realUsers; i++) {
        int id;
        cout << "Enter the id of the user you want to delete:" << endl;
        cin >> id;
        if (id == users[i].id) {

            users[i] = users[i + 1];
            DecrementUserNumber(); // Decrement the count of users
            printErrorMessage("User account deleted successfully!");
            return;


            cout << "User not found!\n";




        }
    }
}
void FareManagement() {
    char choice;
    do {
        char category;
        cout << "Enter 'E' to edit subscription prices or 'C' to edit constant prices: ";
        cin >> category;

        if (category == 'E') { // Editing subscription prices
            char stage, type;
            cout << "\nEnter the stage you want to change its prices (1-4): ";
            cin >> stage;
            cout << "Enter the subscription type (S for Student, W for Waller, M for PublicMonthly, A for PublicAnnual): ";
            cin >> type;
            float newPrice;

            int i = -1; 

            switch (stage) {
            case '1':
            case '2':
            case '3':
            case '4':
            {
                int stageIndex = stage - '1'; // to index (0)

                for (int j = 0; j < realSub; j++) {
                    if (type == SubTypes[j].index) {
                        i = j; // Update i if the subscription type is found
                        break;
                    }
                }

                if (i != -1) {
                    cout << "\nThe current price of stage " << stage << " for subscription type " << type << " is: "
                        << SubTypes[i].price[stageIndex] << endl;
                    cout << "Enter the new price for stage " << stage << " and subscription type " << type << ": ";
                    cin >> newPrice;
                    if (newPrice > 0) { // Validate that price is not negative
                        SubTypes[i].price[stageIndex] = newPrice;
                        printSuccessMessage("\nPrice updated successfully!");
                    }
                    else {
                        cout << "\nPrice cannot be negative or zero. Please enter a valid price." << endl;
                    }
                }
                else {
                    cout << "\nSubscription type does not exist!" << endl;
                }
                break;
            }
            default:
                cout << "\nInvalid stage! Please enter a stage between 1 and 4." << endl;
                break;
            }
        }
        else if (category == 'C') { // Editing constant prices
            int stageIndex;
            cout << "\nEnter the stage for which you want to change the constant price (1-4): ";
            cin >> stageIndex;
            if (stageIndex >= 1 && stageIndex <= 4) {
                float newPrice;
                cout << "Enter the new constant price for stage " << stageIndex << ": ";
                cin >> newPrice;
                if (newPrice > 0) { // Validate that price is not negative
                    constantPrice[stageIndex - 1] = newPrice;
                    cout << "\nConstant price for stage " << stageIndex << " updated successfully!" << endl;
                }
                else {
                    cout << "\nPrice cannot be negative. Please enter a valid price." << endl;
                }
            }
            else {
                cout << "\nInvalid stage! Please enter a stage between 1 and 4." << endl;
            }
        }
        else {
            cout << "\nInvalid category! Please enter 'S' for subscription types or 'C' for constant prices." << endl;
        }

        cout << "\nDo you want to edit another set of prices? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}
string CurrentDate() {
    // Get the current time
    time_t currentTime = time(nullptr);

    
    tm currentTimeStruct = *localtime(&currentTime);

    // Add the specified number of days


    // Normalize the date (adjust month and year if necessary)
    mktime(&currentTimeStruct);
    string DateString = to_string(currentTimeStruct.tm_mday) + "/" + to_string(currentTimeStruct.tm_mon + 1) + "/" + to_string(currentTimeStruct.tm_year + 1900);
    // Return the updated date structure
    return DateString;
}
string addDays() {
    // Get the current time
    time_t currentTime = time(nullptr);

    // Convert to a local time structure
    tm currentTimeStruct = *localtime(&currentTime);

    // Add the specified number of days
    currentTimeStruct.tm_mday += users[indexOfUsers].Sub.ValidityDays;

    // Normalize the date (adjust month and year if necessary)
    mktime(&currentTimeStruct);

    string DateString = to_string(currentTimeStruct.tm_mday) + "/" + to_string(currentTimeStruct.tm_mon + 1) + "/" + to_string(currentTimeStruct.tm_year + 1900);
    // Return the updated date structure
    return DateString;
}
void AddMetroStation() {
    int lineNumber, NumberOfStations;
    char option;
    do {
        bool stationAdded = false;
        cout << "Enter the line you want to add a station to: ";
        cin >> lineNumber;
        if (lineNumber >= 1 && lineNumber <= 3) {
            NumberOfStations = lineStations[lineNumber - 1];
            if (NumberOfStations < maxStations) {
                string NewStation;
                cout << "Enter the name of the new station: ";
                cin.ignore();
               cin>>NewStation;
                stations[lineNumber - 1][NumberOfStations].name = NewStation;
                stations[lineNumber - 1][NumberOfStations].id = NumberOfStations + 1;
                stations[lineNumber - 1][NumberOfStations].line = lineNumber;
                stations[lineNumber - 1][NumberOfStations].symbol = 'R';

                NumberOfStations++;
                lineStations[lineNumber - 1] = NumberOfStations; // Update the global variable
                stationAdded = true;
            }
            else {
                cout << "Cannot add more stations to this line. Maximum capacity reached.\n";
            }
        }
        else {
            cout << "Invalid line number!\n";
        }

        if (stationAdded) {
            cout << "Station added successfully!\n";
        }
        else {
            cout << "Error adding station!\n";
        }

        cout << "Do you want to add another station? (y/n): ";
        cin >> option;
    } while (option == 'y' || option == 'Y');
}
void ViewMetroStations(int lineNumber=0) {
    int  NumberOfStations;
    char option;
    do {

        if (lineNumber == 0) {
            cout << "Enter the line number you want to view: " << endl;
            cin >> lineNumber;

        }


        while (lineNumber < 1 || lineNumber>3)
        {
            printErrorMessage("Wrong line number, Enter again : ");
            cin >> lineNumber;

        }

        if (lineNumber >= 1 && lineNumber <= 3) {
            NumberOfStations = lineStations[lineNumber - 1];

            cout << "Stations:\n";
            for (int i = 0; i < NumberOfStations; i++) {
                if (lineNumber == 3) {
                    printSuccessMessage(to_string(i + 1) + "->" + stations[lineNumber - 1][i].name);
                }else
                cout << i + 1 << "->" << stations[lineNumber - 1][i].name << "\n";
            }
        }
        cout << "Do you want to view another line ? (y/n) \n";


        cin >> option;
        if (option == 'y' || option == 'Y')
            lineNumber = 0;

    } while (option == 'y' || option == 'Y');

}
void EditMetroStation() {

    int lineNumber, NumberOfStations, id;
    string NewStation;
    cout << "Enter the line you want to edit from: \n";
    cin >> lineNumber;
    cout << "Enter the number of the station you want to edit: ";
    cin >> id;

    if (lineNumber >= 1 && lineNumber <= 3) {
        NumberOfStations = lineStations[lineNumber - 1];
        bool stationFound = false;
        for (int i = 0; i < NumberOfStations; i++) {
            if (id == stations[lineNumber - 1][i].id) {
                cout << "Enter the new station for the metro:" << endl;
                cin.ignore();
                cin >> NewStation;
                stations[lineNumber - 1][i].name = NewStation;
                return;
            }
        }
        if (!stationFound)
            cout << "Station not found!\n";
    }
    else {
        cout << "Invalid line number!\n";
    }

}
void DeleteMetroStation() {
    int lineNumber, NumberOfStations, id;
    cout << "Enter the line you want to delete from: \n";
    cin >> lineNumber;
    cout << "Enter the number of the station you want to delete: ";
    cin >> id;
    if (lineNumber >= 1 && lineNumber <= 3) {
        NumberOfStations = lineStations[lineNumber - 1];
        bool stationFound = false;
        bool isTransational = false;
        for (int i = 0; i < NumberOfStations; i++) {
            if (id == stations[lineNumber - 1][i].id) {

                if (stations[lineNumber - 1][i].symbol != 'R') {
                    printErrorMessage("You can't delete a transitional station!");
                    stationFound = true;
                    break;

                }

                // Shift stations after the deleted station one index to the left
                for (int j = i; j < NumberOfStations - 1; j++) {
                    stations[lineNumber - 1][j] = stations[lineNumber - 1][j + 1];
                    // Update the ID of the shifted station
                    stations[lineNumber - 1][j].id = j + 1; // Assuming IDs start from 1
                }
                NumberOfStations--; // Decrement the count of stations
                printSuccessMessage("Metro station deleted successfully!");
                lineStations[lineNumber - 1] = NumberOfStations; // Update the global variable
                stationFound = true;
                break;
            }
        }
        if (stationFound) {
            // Update the global variable for the number of stations
            if (lineNumber == 1)
                lineStations[0] = NumberOfStations;
            else if (lineNumber == 2)
                lineStations[1] = NumberOfStations;
            else if (lineNumber == 3)
                lineStations[2] = NumberOfStations;
        }
        else {
            printErrorMessage("Station not found!");
        }
    }
    else {
        printErrorMessage("Invalid line number!");
    }
}
void StoreTheSubscriptionOfUsers() {
    ofstream outfile("subscription.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < realUsers; i++) {

            outfile << users[i].Sub.endDate << " " << users[i].Sub.index << " " << users[i].Sub.ridesCount << " " << users[i].Sub.stage << " " << users[i].Sub.startDate << " " << users[i].Sub.subName << " " << users[i].Sub.ValidityDays << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open prices file." << endl;
    }
}
void ReadTheSubscriptionOfUsers() {
    ifstream infile("subscription.txt");

    if (infile.is_open()) {
        for (int i = 0; i < realUsers; i++) {

            infile >> users[i].Sub.endDate >> users[i].Sub.index >> users[i].Sub.ridesCount >> users[i].Sub.stage >> users[i].Sub.startDate >> users[i].Sub.subName >> users[i].Sub.ValidityDays >> users[i].walletMoney;
        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open prices file." << endl;
    }
}
void ReadStationNumbersToFile() {
    ifstream infile("stationNumbers.txt");
    if (infile.is_open()) {
        infile >> lineStations[0] >> lineStations[1] >> lineStations[2];
        infile.close();
    }
    else {
        cerr << "Error: Could not open file for reading." << endl;
    }
}
void StoreStationNumbersToFile() {
    ofstream outfile("stationNumbers.txt");
    if (outfile.is_open()) {
        outfile << lineStations[0] << " " << lineStations[1] << " " << lineStations[2];
        outfile.close();
    }
    else {
        cerr << "Error: Could not open file for writing." << endl;
    }
}
void UserManagementAdmin() {
    char anotherFunction = 'y'; // Flag for continuing admin operations

    while (anotherFunction == 'y' || anotherFunction == 'Y') {
        // Check if there are any users before proceeding
        if (realUsers == 0) {
            cout << "There are no users to manage." << endl;
            break; // Exit the loop if no users
        }

        // Display user accounts
        ViewUsersAccountsAdmin();

        int choice;
        cout << "Choose what you want to do:" << endl;
        cout << "------------------------------------" << endl;
        cout << "1 = Edit Users Data" << endl;
        cout << "2 = Delete Users" << endl;
        cout << "3 = Exit" << endl; // Add exit option
        cin >> choice;

        switch (choice) {
        case 1:
            EditUsersAccountsAdmin();
            DeletScreen();
            break;
        case 2:
            DeleteUsersAccountsAdmin();
            DeletScreen();
            break;
        case 3:
            anotherFunction = 'n'; // Set flag to exit
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
        }

        // Prompt to continue with admin operations
        if (realUsers > 0 && anotherFunction != 'n') {
            cout << "Do you want to perform another operation (y/n)? ";
            cin >> anotherFunction;
        }
    }
}
void StoreTheDataOfStations() {
    ofstream outfile("stations.txt");

    if (outfile.is_open()) {
        for (int i = 0; i < lineStations[0]; i++) {
            outfile << stations[0][i].line << " " << stations[0][i].name << " " << stations[0][i].symbol << stations[0][i].zone<<" " << stations[0][i].numberOfCheckIn <<" " << stations[0][i].numberOfCheckOut << endl;
        }
        for (int i = 0; i < lineStations[1]; i++) {
            outfile << stations[1][i].line << " " << stations[1][i].name << " " << stations[1][i].symbol << " " << stations[1][i].zone << " " << stations[1][i].numberOfCheckIn << " " <<stations[1][i].numberOfCheckOut << endl;
        }

        for (int i = 0; i < lineStations[2]; i++) {
            outfile << stations[2][i].line << " " << stations[2][i].name << " " << stations[2][i].symbol << " " << stations[2][i].zone << " " << stations[2][i].numberOfCheckIn << " " << stations[2][i].numberOfCheckOut << endl;
        }

        outfile.close();
    }
    else {
        cerr << "Error: Could not open stations file." << endl;
    }
}
void ReadFromFileTheDataOfStations() {
    ifstream infile("stations.txt");

    if (infile.is_open()) {
        for (int i = 0; i < lineStations[0]; i++) {
            infile >> stations[0][i].line;
            stations[0][i].id = i + 1;
            infile >> stations[0][i].name;
            infile >> stations[0][i].symbol;
            infile >> stations[0][i].zone;
            infile >> stations[0][i].numberOfCheckIn;
            infile >> stations[0][i].numberOfCheckOut;
        }
        for (int i = 0; i < lineStations[1]; i++) {
            infile >> stations[1][i].line;
            if (stations[1][i].line == 3)
            {
                break;
            }
            stations[1][i].id = i + 1;
            infile >> stations[1][i].name;
            infile >> stations[1][i].symbol;
            infile >> stations[1][i].zone;
            infile >> stations[1][i].numberOfCheckIn;
            infile >> stations[1][i].numberOfCheckOut;

        }
        for (int i = 0; i < lineStations[2]; i++) {
            infile >> stations[2][i].line;
            stations[2][i].id = i + 1;
            infile >> stations[2][i].name;
            infile >> stations[2][i].symbol;
            infile >> stations[2][i].zone;
            infile >> stations[2][i].numberOfCheckIn;
            infile >> stations[2][i].numberOfCheckOut;
        }

        infile.close();
    }
    else {
        cerr << "Error: Could not open stations file." << endl;
    }
}
void StationsManagementAdmin() {
    int choice;
    char anotherFunction;


    do {

        ViewMetroStations();
        cout << "Choose what you want to do:" << endl;
        cout << "------------------------------------" << endl;
        cout << "1 = Add Stations" << endl;
        cout << "2 = Edit Stations" << endl;
        cout << "3 = Delete Stations" << endl;
        cout << "4 = Exit" << endl;

        cin >> choice;
        switch (choice) {
        case 1:
            AddMetroStation();
            DeletScreen();
            break;


        case 2:
            EditMetroStation();
            DeletScreen();
            break;
        case 3:
            DeleteMetroStation();
            DeletScreen();
            break;
        case 4:
            cout << "Exiting...";
            DeletScreen();
            break;
        }
       
    
        cout << "Do you want another function ?(y/n)";

        cin >> anotherFunction;
    } while (anotherFunction == 'y' || anotherFunction == 'Y');

   }
void viewUserRideHistory() {
    char choice;
    do {
        if (users[indexOfUsers].Sub.ridesCount > 0) {
            cout << users[indexOfUsers].UserAccount.username << " Rides:" << endl;
            for (int i = users[indexOfUsers].Sub.ridesCount - 1; i >= 0; i--) {
                cout << "Ride " << setw(10) << i + 1 << endl;
                cout << "------------------------------------------\n";
                cout << left << setw(15) << "Date:" << users[indexOfUsers].ridedetails[i].rideDate << endl;
                cout << left << setw(15) << "Ride ID:" << users[indexOfUsers].ridedetails[i].rideID << endl;
                cout << left << setw(15) << "From station:" << users[indexOfUsers].ridedetails[i].checkInStation << endl;
                cout << left << setw(15) << "To station:" << users[indexOfUsers].ridedetails[i].checkOutStation << endl;
               // if (buyTicket || users[indexOfUsers].Sub.index == 'W') {
                    cout << left << setw(15) << "Cost:" << users[indexOfUsers].ridedetails[i].cost << endl;
                //}
                cout << "------------------------------------------\n";
            }
        }
        else {
            cout << "No rides booked." << endl;
        }

        cout << "Do you want to return to the main menu? (y/n): ";
        cin >> choice;
    } while (choice != 'y' && choice != 'Y');
}
void viewAllRides() {
    char choice;
    do {
        for (int i = realUsers - 1; i >= 0; i--) {
            cout << users[i].UserAccount.email << " Rides:" << endl;
            cout << "-------------------------------------\n";
            for (int j = users[i].Sub.ridesCount - 1; j >= 0; j--) {
                cout << "Ride " << j + 1 << ":" << endl;
                cout << "Date: " << users[i].ridedetails[j].rideDate << endl;
                cout << "Ride ID: " << users[i].ridedetails[j].rideID << endl;
                cout << "From station: " << users[i].ridedetails[j].checkInStation << endl;
                cout << "To station: " << users[i].ridedetails[j].checkOutStation << endl;
                cout << "Cost: " << users[i].ridedetails[j].cost << endl;
                cout << "-------------------------------------\n";
            }
        }

        cout << "Do you want to return to the main menu? (y/n): ";
        cin >> choice;
    } while (choice != 'y' && choice != 'Y');
}
int count_of_type[4] = { 0 };
void subtype()
{
    int choice;


    for (int i = 0; i < realSub; i++) {
        cout << i + 1 << " " << SubTypes[i].subName << endl;
    }

    bool c;
    do
    {
        c = false;
        cin >> choice;
        for (int j = 1; j <= realSub; j++) {
            if (choice == j) {

                users[indexOfUsers].Sub.index = SubTypes[j - 1].index;
              
                users[indexOfUsers].Sub.subName = SubTypes[j - 1].subName;
                users[indexOfUsers].Sub.ValidityDays = SubTypes[j - 1].ValidityDays;
               
                c = true;
            }




        }
        if (!c) {
            cout << "invaled choice re enter your type of subscrbtion again\n";
        }


    } while (c == false);

}
void display_num_of_types()
{
    cout << "Number of student system subscribers: " << count_of_type[0] << endl;
    cout << "Number of wallet system subscribers: " << count_of_type[1] << endl;
    cout << "Number of annual public system subscribers: " << count_of_type[2] << endl;
    cout << "Number of monthly public system subscribers: " << count_of_type[3] << endl;
}
int buyCostStages(int& stage) {
    char ch;
    char subIndex = users[indexOfUsers].Sub.index;

    // Find the index of the subscription type
    int i;
    for (i = 0; i < realSub; i++) {
        if (SubTypes[i].index == subIndex) {
            break;
        }
    }



    cout << "You must pay " << SubTypes[i].price[stage - 1] << endl;
    cout << "Press 'y' to continue payment: " << endl;
    
    // While loop for user confirmation (y or Y)
    while (true) {
        cin >> ch;

        if (ch == 'y' || ch == 'Y') {
            DeletScreen();
            return SubTypes[i].price[stage - 1];
        }
        else {
            cout << "Invalid input. Please enter 'y' or 'Y' to confirm payment: ";
        }
    }
}
void purchasesubscribtion( float& cost) {
    subtype(); // Assuming this is a valid function call

    char subscriptionType = users[indexOfUsers].Sub.index;

    if (subscriptionType == 'S' || subscriptionType == 'M' || subscriptionType == 'A') {
        int i;
        for (i = 0; i < realSub; i++) {
            if (SubTypes[i].index == subscriptionType) {
                break;
            }
        }

        users[indexOfUsers].Sub.ValidityDays = SubTypes[i].ValidityDays;
        users[indexOfUsers].Sub.fullRides = SubTypes[i].ridesCount;
        cout << "Which stage do you want?" << endl;
        cout << "1: 2 to 9 stations, Price: " << SubTypes[i].price[0] << endl;
        cout << "2: 10 to 16 stations, Price: " << SubTypes[i].price[1] << endl;
        cout << "3: 17 to 23 stations, Price: " << SubTypes[i].price[2] << endl;
        cout << "4: More than 23 stations, Price: " << SubTypes[i].price[3] << endl;
        int stage;
        cin >> stage;

        cost = buyCostStages(stage);

        if (cost > users[indexOfUsers].balance) {
            cout << "Add balance because the balance is not enough." << endl;
            int add;
            cin >> add;

            while ((users[indexOfUsers].balance + add) < cost) {
                cout << "Added balance is still not enough. Please add more balance: ";
                int moreToAdd;
                cin >> moreToAdd;
                add += moreToAdd;
            }

            users[indexOfUsers].balance += add;
            SubTypes[i].subscriptionCount++;
            users[indexOfUsers].balance -= cost;
            users[indexOfUsers].Sub.ridesCount = 0;
            users[indexOfUsers].Sub.startDate = CurrentDate();
            users[indexOfUsers].Sub.endDate = addDays();
            users[indexOfUsers].Sub.stage = stage;

        }

       
        else {
            SubTypes[i].subscriptionCount++;
            users[indexOfUsers].balance -= cost;
            users[indexOfUsers].Sub.ridesCount = 0;
            users[indexOfUsers].Sub.startDate = CurrentDate();
            users[indexOfUsers].Sub.endDate = addDays();
            users[indexOfUsers].Sub.stage = stage;
            
        }

       
      
    }
    else {
        cout << "You must have in your Wallet Money multiple of 10 and less than 400." << endl;
        cout << "Select the money at wallet: ";
        int walletprice;
        do {
            
            cin >> walletprice;
            if (walletprice % 10 != 0 || walletprice > 400 || walletprice <= 0||walletprice>users[indexOfUsers].balance) {
                cout << "Invalid amount. Please enter a valid amount (multiple of 10, less than 400, and greater than 0): ";
            }
            else {
                break;
            }
        } while (true);

        users[indexOfUsers].walletMoney = walletprice;
        users[indexOfUsers].balance -= walletprice;
    }

    users[indexOfUsers].Sub.startDate = CurrentDate(); // Assuming CurrentDate() is a valid function returning a string
    users[indexOfUsers].Sub.endDate = addDays(); // Assuming addDays() is a valid function returning a string
    users[indexOfUsers].SubFound = true;
}
void inputDeparture()
{

    cout << "Enter the metro line number you are going from: \n" << "Enter 1 or 2 or 3 \n";
    cin >> userDeparture.line;
    while (userDeparture.line != 1 && userDeparture.line != 2 && userDeparture.line != 3)
    {
        cout << "you entered a wrong line number \n" << "Enter the metro line again: \n";
        cout << "Enter 1 or 2 or 3" << endl;
        cin >> userDeparture.line;
    }
    ViewMetroStations(userDeparture.line);

    cout << "Enter your departure station (ID):\n " << endl;

    bool canInput;

    do
    {
        canInput = true;

        cin >> userDeparture.id;



        if ((userDeparture.id > lineStations[0] || userDeparture.id == 0) && userDeparture.line == 1)
        {
            cout << "you entered a wrong station number \n" << "Enter the metro station again: \n";
            canInput = false;
        }
        if ((userDeparture.id > lineStations[1] || userDeparture.id == 0) && userDeparture.line == 2)
        {
            cout << "you entered a wrong station number \n" << "Enter the metro station again: \n";

            canInput = false;

        }

        if ((userDeparture.id > lineStations[2] || userDeparture.id == 0) && userDeparture.line == 3)
        {
            cout << "you entered a wrong station number \n" << "Enter the metro station again: \n";
            canInput = false;
        }

    } while (!canInput);


}
string GetDepartureName() {
    int NumberOfStations;
    
        if (userDeparture.line == 1)
            NumberOfStations = lineStations[0]; //35
        else if (userDeparture.line == 2)
            NumberOfStations = lineStations[1]; //20
        else if (userDeparture.line == 3)
            NumberOfStations = lineStations[2];//29
  

        for (int i = 0; i < NumberOfStations; i++) {
            if (userDeparture.id == stations[userDeparture.line - 1][i].id)
            {
               
                return stations[userDeparture.line - 1][i].name;
            }
        }
       
  

}
string GetDestinationName() {
    int NumberOfStations;

    if (userDestination.line == 1)
        NumberOfStations = lineStations[0]; //35
    else if (userDestination.line == 2)
        NumberOfStations = lineStations[1]; //20
    else if (userDestination.line == 3)
        NumberOfStations = lineStations[2];//29


    for (int i = 0; i < NumberOfStations; i++) {
        if (userDestination.id == stations[userDestination.line - 1][i].id)
        {

            return stations[userDestination.line - 1][i].name;
        }
    }



}
void inputDestination() {

    cout << "Enter the metro line number you are heading to: \n" << "Enter 1 or 2 or 3 \n";
    cin >> userDestination.line;
    while (userDestination.line != 1 && userDestination.line != 2 && userDestination.line != 3)
    {
        cout << "you entered a wrong line number \n" << "Enter the metro line again: \n";
        cout << "Enter 1 or 2 or 3" << endl;
        cin >> userDestination.line;
    }
    ViewMetroStations(userDestination.line);

    cout << "Enter your destination station (ID):\n " << endl;

    bool canInput;
    do
    {
        canInput = true;
        cin >> userDestination.id;


        if ((userDestination.id > lineStations[0] || userDestination.id == 0) && userDestination.line == 1)
        {
            cout << "you entered a wrong station number \n" << "Enter the metro station again: \n";
            canInput = false;
        }
        if ((userDestination.id > lineStations[1] || userDestination.id == 0) && userDestination.line == 2)
        {
            cout << "you entered a wrong station number \n" << "Enter the metro station again: \n";
            canInput = false;

        }

        if ((userDestination.id > lineStations[2] || userDestination.id == 0) && userDestination.line == 3)
        {
            cout << "you entered a wrong station number \n" << "Enter the metro station again: \n";
            canInput = false;
        }

    } while (!canInput);


}
void GetTransitionalStationsId() {

    // shohada = 0,1 attaba = 2,3 , nasser 4,5 

    for (int i = 0; i < lineStations[0]; i++) {
        if (stations[0][i].symbol == 'S')
        {
            transitionStations[0] = i + 1;
        }
        if (stations[0][i].symbol == 'N')
        {
            transitionStations[4] = i + 1;
        }
    }
    for (int i = 0; i < lineStations[1]; i++) {
        if (stations[1][i].symbol == 'S')
        {
            transitionStations[1] = i + 1;
        }
        if (stations[1][i].symbol == 'A')
        {
            transitionStations[2] = i + 1;
        }
    }

    for (int i = 0; i < lineStations[2]; i++) {
        if (stations[2][i].symbol == 'A')
        {
            transitionStations[3] = i + 1;
        }
        if (stations[2][i].symbol == 'N')
        {
            transitionStations[5] = i + 1;
        }
    }
}
void InitializeRide() {

    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].rideID = to_string(users[indexOfUsers].id) + to_string(users[indexOfUsers].Sub.ridesCount);
   users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].checkInStation = GetDepartureName();
    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].checkOutStation = GetDestinationName();
    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].rideDate = CurrentDate();
    stations[userDeparture.line - 1][userDeparture.id - 1].numberOfCheckIn++;
    stations[userDestination.line - 1][userDestination.id - 1].numberOfCheckOut++;
    users[indexOfUsers].Sub.ridesCount++;
   
}
bool purchaseTicket(int ticketPriceIndex) {
    if ((users[indexOfUsers].balance - constantPrice[ticketPriceIndex]) < 0) {
        cout << "You Don't have enough balance!" << endl;
        return false;
    }
    else {



        return true;
    }
}
int CalulateNumberOfStations();
bool canInitializeTheRide;
void walletDeduction(int NumberOfStations) {
    if (users[indexOfUsers].Sub.index == 'W') {
        int priceToDeduct = 0;

        if (1 < NumberOfStations && NumberOfStations < 10) {
            priceToDeduct = constantPrice[0];
        }
        else if (9 < NumberOfStations && NumberOfStations < 17) {
            priceToDeduct = constantPrice[1];
        }
        else if (16 < NumberOfStations && NumberOfStations < 24) {
            priceToDeduct = constantPrice[2];
        }
        else {
            priceToDeduct = constantPrice[3];
        }

        // Check if the price to deduct exceeds the wallet balance
        if (users[indexOfUsers].walletMoney < priceToDeduct) {
            cout << "Insufficient funds in the wallet please go and add money to the wallet in manage subscription!." << endl;
            canInitializeTheRide = false;
            return; // Exit the function if balance is insufficient
        }
        else {
            users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = priceToDeduct;
            users[indexOfUsers].walletMoney -= priceToDeduct;
            canInitializeTheRide = true;
            // Store the cost in the ridedetails structure
            // Assuming ridesCount is the index to store the next ride
            
            
           
            // Increment the ridesCount for the next ride

            cout << "The remaining money in the wallet: " << users[indexOfUsers].walletMoney << endl;
        }

        // Deduct the price from the wallet balance
       
    }
}
int CalulateNumberOfStations() {
    int NumberOfStations;

    // Your existing logic to calculate NumberOfStations...

    //cout << transitionStations[0] << ' ' << ' ' << transitionStations[1] << ' ' << transitionStations[2] << ' ' << transitionStations[3] << ' ' << transitionStations[4] << ' ' << transitionStations[5] << endl;
    if (userDeparture.line == userDestination.line)
        NumberOfStations = abs(userDestination.id - userDeparture.id) + 1;
    else if (userDeparture.line == 1 && userDestination.line == 2)
        NumberOfStations = abs(userDeparture.id - transitionStations[0]) + abs(userDestination.id - transitionStations[1]) + 1;
    // int a [10] { shohada line one , shohada line 2 , nasser line one , nasser line 3}
    else if (userDeparture.line == 1 && userDestination.line == 3) {
        if (userDeparture.id <= transitionStations[0] && userDestination.id >= transitionStations[3])
            NumberOfStations = abs(userDeparture.id - transitionStations[4]) + abs(userDestination.id - transitionStations[5]) - 1;
        else
            NumberOfStations = abs(userDeparture.id - transitionStations[4]) + abs(userDestination.id - transitionStations[5]) + 1;
    }
    else if (userDeparture.line == 2 && userDestination.line == 1)
        NumberOfStations = abs(userDeparture.id - transitionStations[1]) + abs(userDestination.id - transitionStations[0]) + 1;

    else if (userDeparture.line == 2 && userDestination.line == 3) {
        if (userDeparture.id >= transitionStations[3] && userDestination.id <= transitionStations[5])
            NumberOfStations = abs(userDeparture.id - transitionStations[2]) + abs(userDestination.id - transitionStations[3]) - 1;

        else
            NumberOfStations = abs(userDeparture.id - transitionStations[2]) + abs(userDestination.id - transitionStations[3]) + 1;
    }
    else if (userDeparture.line == 3 && userDestination.line == 1) {
        if (userDeparture.id >= transitionStations[3] && userDestination.id <= transitionStations[0])
            NumberOfStations = abs(userDeparture.id - transitionStations[5]) + abs(userDestination.id - transitionStations[4]) - 1;
        else
            NumberOfStations = abs(userDeparture.id - transitionStations[5]) + abs(userDestination.id - transitionStations[4]) + 1;
    }

    else if (userDeparture.line == 3 && userDestination.line == 2) {
        if (userDeparture.id <= transitionStations[5] && userDestination.id >= transitionStations[3])
            NumberOfStations = abs(userDeparture.id - transitionStations[3]) + abs(userDestination.id - transitionStations[2]) - 1;
        else
            NumberOfStations = abs(userDeparture.id - transitionStations[5]) + abs(userDestination.id - transitionStations[4]) + 1;
    }
    if (users[indexOfUsers].Sub.index == 'W') {
        walletDeduction(NumberOfStations);
    }
    char option;    // to choose either to choose again or to use balance
    switch (users[indexOfUsers].Sub.stage) {
    case 1:
        if (NumberOfStations > 9 && NumberOfStations <= 16) {
            cout << "Number of stations is more than the stage you have chosen (stage 1)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
               if (purchaseTicket(1)) {
                   users[indexOfUsers].balance -= constantPrice[1];
                   users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[1];
                   users[indexOfUsers].tickets++;
                   buyTicket = true;
                }
               
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture();
                inputDestination();
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations();
                return NumberOfStations;
            }
        }
        else if (NumberOfStations > 16 && NumberOfStations <= 23) {
            cout << "Number of stations is more than the stage you have chosen (stage 1)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
                if (purchaseTicket(2)) {
                    users[indexOfUsers].balance -= constantPrice[2];
                    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[2];
                    users[indexOfUsers].tickets++;
                    buyTicket = true;
                }
               
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture();
                inputDestination();
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations();
                return NumberOfStations;
            }
        }
        else if (NumberOfStations > 23) {
            cout << "Number of stations is more than the stage you have chosen (stage 1)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
                if (purchaseTicket(3)) {
                    users[indexOfUsers].balance -= constantPrice[3];
                    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[3];
                    users[indexOfUsers].tickets++;
                    buyTicket = true;
                }
              
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture();
                inputDestination();
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations();
                return NumberOfStations;
            }
        }
        break;
    case 2:
        if (NumberOfStations > 16 && NumberOfStations <= 23) {
            cout << "Number of stations is more than the stage you have chosen (stage 2)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
                if (purchaseTicket(2)) {
                    users[indexOfUsers].balance -= constantPrice[2];
                    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[2];
                    users[indexOfUsers].tickets++;
                    buyTicket = true;
                }
               
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture();
                inputDestination();
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations();
                return NumberOfStations;
            }
        }
        else if (NumberOfStations > 23) {
            cout << "Number of stations is more than the stage you have chosen (stage 2)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
                if (purchaseTicket(3)) {
                    users[indexOfUsers].balance -= constantPrice[3];
                    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[3];
                    users[indexOfUsers].tickets++;
                    buyTicket = true;
                }
                
                
                
                
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture();
                inputDestination();
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations();
                return NumberOfStations;
            }
        }
        break;
    case 3:
        if (NumberOfStations > 23) {
            cout << "Number of stations is more than the stage you have chosen (stage 3)." << endl;
            cout << "Do you want to purchase from your balance (y)? Or enter the destination again (n)?" << endl;
            cin >> option;
            if (option == 'Y' || option == 'y') {
                if (purchaseTicket(3)) {
                    
                    users[indexOfUsers].balance -= constantPrice[3];
                    users[indexOfUsers].ridedetails[users[indexOfUsers].Sub.ridesCount].cost = constantPrice[3];
                    users[indexOfUsers].tickets++;
                    buyTicket = true;
                }
            }
            else if (option == 'n' || option == 'N') {
                inputDeparture();
                inputDestination();
                NumberOfStations = 0;
                NumberOfStations = CalulateNumberOfStations();
                return NumberOfStations;
            }
        }
        break;
    }
   

 
   
    return NumberOfStations;
}
int timeEstimated(int NumberOfStations) {
    float timeForOneStations = 2.5;
    float timeEstimated = timeForOneStations * NumberOfStations;
    return timeEstimated;
}
int checkInAndCheckOut(departure& userDeparture, destination& userDestination) {
    
    if ((users[indexOfUsers].Sub.fullRides-users[indexOfUsers].Sub.ridesCount <= 0 || users[indexOfUsers].Sub.ValidityDays <= 0 ) && (users[indexOfUsers].Sub.index=='M'|| users[indexOfUsers].Sub.index == 'A'||users[indexOfUsers].Sub.index == 'S')) {
        cout << "Your subscription is invalid. Please renew your subscription." << endl;
        return 0; // Return 0 to indicate failure
    }
    
    GetTransitionalStationsId();
    ViewMetroStations();
    inputDeparture();
    inputDestination();
    int NumberOfStations = CalulateNumberOfStations();
    if (NumberOfStations != 0) {
        cout << NumberOfStations << " Stations";
       
    }
    else
        cout << "Not enough money! \n";
    if (users[indexOfUsers].Sub.index=='W' &&!canInitializeTheRide){

    }
    else {
        InitializeRide();
    }
    DeletScreen();
    float time = timeEstimated(NumberOfStations);
    cout << "The Estimated time to arrive is " << time <<" Minutes"<< endl;
    cout << "Happy Ride!" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return NumberOfStations;
}
void viewDetails( ) {
    cout << "The number of rides: " << users[indexOfUsers].Sub.ridesCount << endl;
    cout << "The type of Subscription: " << users[indexOfUsers].Sub.subName << endl;
    if (users[indexOfUsers].Sub.index == 'W') {
        cout << "The remaining money in the Wallet is " << users[indexOfUsers].walletMoney << endl;

    }
    else if (users[indexOfUsers].Sub.index == 'A' || users[indexOfUsers].Sub.index == 'M' || users[indexOfUsers].Sub.index == 'S'){
    cout << "The stage of Subscription: " << users[indexOfUsers].Sub.stage << endl;
    cout << "The start of Subscription: " << users[indexOfUsers].Sub.startDate << endl;
    cout << "The End of Subscription: " << users[indexOfUsers].Sub.endDate << endl;
    cout << "The days valid of Subscription: " << users[indexOfUsers].Sub.ValidityDays << endl;
    cout << "The remaining rides: " << users[indexOfUsers].Sub.fullRides - users[indexOfUsers].Sub.ridesCount+ users[indexOfUsers].tickets << endl;
}
}
bool checkTheSub()
{
    char subIndex = users[indexOfUsers].Sub.index;
    for (int i = 0; i < realSub; i++) {
        if (SubTypes[i].index == subIndex) {
            if (SubTypes[i].ridesCount - users[indexOfUsers].Sub.ridesCount == 0|| users[indexOfUsers].Sub.endDate == CurrentDate()) {
                cout << "Your subscription is not valid" << endl;
                return true;
            }
            break;
        }
    }

    if (subIndex == 'W') {
        if (users[indexOfUsers].walletMoney < 6) {
            cout << "Your subscription is not valid" << endl;
            return true;
        }
    }
   

    return false;
}
void generateReport() {

    int maxCheckIn = stations[0][0].numberOfCheckIn;
    int maxCheckOut = stations[0][0].numberOfCheckOut;
    int maxSubscriptionPlan = SubTypes[0].subscriptionCount;
    string stationWithMaxCheckIn = stations[0][0].name;
    string stationWithMaxCheckOut = stations[0][0].name;
    string subscriptionName = SubTypes[0].subName;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < maxStations; ++j) {
            if (stations[i][j].numberOfCheckIn > maxCheckIn) {
                maxCheckIn = stations[i][j].numberOfCheckIn;
                stationWithMaxCheckIn = stations[i][j].name;
            }
            if (stations[i][j].numberOfCheckOut > maxCheckOut) {
                maxCheckOut = stations[i][j].numberOfCheckOut;
                stationWithMaxCheckOut = stations[i][j].name;
            }
        }
    }

    for (int i = 0; i < realSub; i++) {
        if (SubTypes[i].subscriptionCount > maxSubscriptionPlan) {
            maxSubscriptionPlan = SubTypes[i].subscriptionCount;
            subscriptionName = SubTypes[i].subName;
        }
    }

    cout << stationWithMaxCheckIn << ": Highest number of check-ins: " << maxCheckIn << endl;
    cout << stationWithMaxCheckOut << ": Highest number of check-outs: " << maxCheckOut << endl;
    cout << subscriptionName << ": is the Highest number of subscription plans: " << maxSubscriptionPlan << endl;
    cout << endl;
    
    cout << "2:Exit " << endl;
    int userInput;
    cin >> userInput;
    if (userInput == 2) {
        return;
    }
    else {
        cout << "Exiting report generation..." << endl;
    }
}
void ManageSubscription( float& cost, int& stage) {
    int q;
    viewDetails();

    cout << "Do you want to upgrade or renew subscription?" << endl;
    cout << "1: Renew" << endl;
    cout << "2: Upgrade" << endl;
    cout << "3: Exit Manage Subscription" << endl;
    cout << "Choose: ";
    cin >> q;

    while (q != 1 && q != 2 && q != 3) {
        cout << "Invalid choice. Please choose again: ";
        cin >> q;
    }

    if (q == 1) {
        bool indexFound = false;
        for (int i = 0; i < realSub; i++) {
            if (users[indexOfUsers].Sub.index == SubTypes[i].index) {
                indexFound = true;
                break;
            }
        }
        bool balanceIsEnough = false;
        if (((users[indexOfUsers].Sub.index == 'S') || (users[indexOfUsers].Sub.index == 'M') || (users[indexOfUsers].Sub.index == 'A')) && indexFound) {
            do {
                if (cost <= users[indexOfUsers].balance) {
                    users[indexOfUsers].balance -= cost;
                    users[indexOfUsers].Sub.ridesCount = 0; // Reset rides count
                    users[indexOfUsers].Sub.startDate = CurrentDate();
                    users[indexOfUsers].Sub.endDate = addDays();
                    balanceIsEnough = true;
                    cout << users[indexOfUsers].Sub.ridesCount;
                }
                else {
                    cout << "Add balance because the balance is not enough" << endl;
                    int add;
                    cin >> add;

                    while ((users[indexOfUsers].balance + add) < cost) {
                        cout << "Added balance is still not enough. Please add more balance: ";
                        int moreToAdd;
                        cin >> moreToAdd;
                        add += moreToAdd;
                    }

                    users[indexOfUsers].balance += add;
                    if (users[indexOfUsers].balance>=cost) {
                        balanceIsEnough = true;
                        users[indexOfUsers].Sub.ridesCount = 0; // Reset rides count
                        users[indexOfUsers].Sub.startDate = CurrentDate();
                        users[indexOfUsers].Sub.endDate = addDays();
                        users[indexOfUsers].balance -= cost;
                  }
                   
                }
            } while (!balanceIsEnough);
        }
        else if (users[indexOfUsers].Sub.index == 'W' && indexFound) {
            // Handling wallet subscription
            users[indexOfUsers].Sub.ridesCount = 0; // Reset rides count
            cout << "You must have in your Wallet Money multiple of 10 and less than 400." << endl;

            int walletprice;
            do {
                cout << "Enter the money to add to the wallet: ";
                cin >> walletprice;

                if (walletprice <= 0) {
                    cout << "Invalid amount. Please enter a positive value." << endl;
                }
                else if (walletprice % 10 != 0 || walletprice > 400) {
                    cout << "Entered money must be a multiple of ten and less than 400." << endl;
                }
            } while (walletprice <= 0 || walletprice % 10 != 0 || walletprice > 400);

            while (users[indexOfUsers].balance < walletprice) {
                cout << "The entered wallet price exceeds your balance." << endl;
                cout << "Do you want to update your profile to add more balance? (y/n): ";
                char response;
                cin >> response;

                if (response == 'y' || response == 'Y') {
                    // Call updateProfile function here
                    UpdatePersonalInformation();
                    cout << "Profile updated successfully." << endl;
                    break;
                }
                else if (response == 'n' || response == 'N') {
                    // Return to the beginning of the loop to ask for wallet price again
                    cout << "Please enter another wallet price: ";
                    cin >> walletprice;
                }
                else {
                    // Invalid input, ask the user to enter again
                    cout << "Invalid choice. Please enter 'y' for yes or 'n' for no." << endl;
                }
            }

            users[indexOfUsers].walletMoney += walletprice;
            users[indexOfUsers].balance -= walletprice; // Deduct wallet price from balance
        }
        else {
            cout << "Your old Subscription is not found. You can go to upgrade!" << endl;
        }
    }
    else if (q == 2) {
        purchasesubscribtion(cost);
        users[indexOfUsers].Sub.ridesCount = 0;
    }
    else if (q == 3) {
        return;
    }
}
void LogOut();
void AdminMainMenu() {
    char choice;
    while (true) {
        int next;
        cout << "Choose what you want to do:" << endl;
        cout << "------------------------------------" << endl;
        cout << "1 = User Management" << endl;
        cout << "2 = Station Managemnt" << endl;
        cout << "3 = Fare Management" << endl;
        cout << "4 = View User Ride History" << endl;
        cout << "5 = Subscription Management" << endl; // New option
        cout << "6 = Show Brief History" << endl;       // New option
        cout << "7 = Log Out" << endl;

        cin >> next;
        if (next == 1) {
            DeletScreen();
            UserManagementAdmin();
            DeletScreen();
        }
        else if (next == 2) {
            DeletScreen();
            StationsManagementAdmin();
            DeletScreen();
        }
        else if (next == 3) {
            DeletScreen();
            FareManagement();
            DeletScreen();
        }
        else if (next == 4) {
            DeletScreen();
            viewAllRides();
            DeletScreen();
        }
        else if (next == 5) { // New option
            DeletScreen();
            AdminMenuSubscriptionManagement();
            DeletScreen();
        }
        else if (next == 6) { // New option
            DeletScreen();
            generateReport();
            DeletScreen();
        }
        else if (next == 7) {
            DeletScreen();
            LogOut();
            isAdmin = false;
            DeletScreen();
            break;
        }
        else {
            cout << "Invalid option" << endl;
        }
    }
}

void UpdatePersonalInformation() {
    int choose;
    char complete;

    do {
        cout << "What do you want to change?" << endl;
        cout << "1: Name " << endl;
        cout << "2: Password " << endl;
        cout << "3: Email " << endl;
        cout << "4: Balance" << endl;
        cout << "5: Exit" << endl;
        cout << "Choose: ";
        cin >> choose;

        while (choose > 5 || choose < 1) {
            cout << "Sorry, please repeat your choice: ";
            cin >> choose;
        }

        if (choose == 1) {
            cout << "Change your name" << endl;
            cin.ignore();
           cin>>users[indexOfUsers].UserAccount.username;
        }
        else if (choose == 2) {
            cout << "Change your password" << endl;
            cin.ignore();
           cin>>users[indexOfUsers].UserAccount.password;
        }
        else if (choose == 3) {
            cout << "Change your email" << endl;
            string newEmail;
            do {
                cin.ignore();
                cin >> newEmail;
                if (findEmail(newEmail)) {
                    cout << "This email already exists. Please enter another email." << endl;
                }
                else if (!regex_match(newEmail, regex(".+@.+(\\.com)"))) {
                    cout << "Invalid email format. Please enter a valid email: ";
                }
                else {
                    users[indexOfUsers].UserAccount.email = newEmail;
                    break;
                }
            } while (true);
        }
        else if (choose == 4) {
            cout << "Change your balance" << endl;
            int balance;
            do {
           
                cin >> balance;
                if (!isBalancePositive(balance)) {
                    cout << "Balance cannot be zero or negative. Please enter a valid balance:" << endl;
                }
            } while (!isBalancePositive(balance));
            users[indexOfUsers].balance += balance;
        }
        else if (choose == 5) {
            cout << "Exiting..." << endl;
            break;
        }

        cout << "Do you want to change anything else? (y/n)" << endl;
        cin >> complete;
    } while (complete == 'y' || complete == 'Y');
}
void somePlacesNextTheStations()
{
    // Ghazy
    cout << "Some places are near the stations:" << endl;
    cout << "------------------------------------" << endl;
    cout << "1- Om El Misreyeen station" << endl;
    cout << "   Salah Salem Street and Square" << endl;
    cout << "------------------------------------" << endl;
    cout << "2- Giza station" << endl;
    cout << "   Giza Railway Station" << endl;
    cout << "   Giza Court" << endl;
    cout << "   Pyramids Street" << endl;
    cout << "   Faisal Court" << endl;
    cout << "------------------------------------" << endl;
    cout << "3- Cairo University station" << endl;
    cout << "   Cairo University" << endl;
    cout << "   Safat El Laban Area" << endl;
    cout << "   Sudan Street" << endl;
    cout << "   Between the Palaces Area" << endl;
    cout << "   Cairo University City" << endl;
    cout << "   Giza Zoo" << endl;
    cout << "------------------------------------" << endl;
    cout << "4- Opera station" << endl;
    cout << "   Egyptian Opera House" << endl;
    cout << "   Al Ahly Club" << endl;
    cout << "   Qasr El Nil Bridge" << endl;
    cout << "   Cairo Tower" << endl;
    cout << "   Andalusian Garden" << endl;
    cout << "------------------------------------" << endl;
    cout << "5- Mohamed Naguib station" << endl;
    cout << "   Aabdeen District and Palace" << endl;
    cout << "   Mostafa Kamel Square" << endl;
    cout << "   Talaat Harb Square" << endl;
    cout << "------------------------------------" << endl;
    cout << "6- El Ataba station" << endl;
    cout << "   El Ataba Square" << endl;
    cout << "   Azbakeya Book Market" << endl;
    cout << "   Al Muski" << endl;
    cout << "   Al Azhar Street" << endl;
    cout << "   Al Hussein Area and Mosque" << endl;
    cout << "   Al Azhar Park" << endl;
    cout << "------------------------------------" << endl;
    cout << "7- Rod El Farag station" << endl;
    cout << "   Faculty of Engineering, Shubra, Benha University" << endl;
    cout << "   Shubra Street" << endl;
    cout << "------------------------------------" << endl;
    cout << "8- Faculty of Agriculture station" << endl;
    cout << "   Faculty of Agriculture, Ain Shams University" << endl;
    cout << "------------------------------------" << endl;
    cout << "9- El Quba Bridge station" << endl;
    cout << "   Qasr El Quba" << endl;
    cout << "   Al Hadayek Area" << endl;
    cout << "------------------------------------" << endl;
    cout << "10- Mar Girgis station" << endl;
    cout << "   Complex of Religions Area" << endl;
    cout << "   Nile Corniche" << endl;
    cout << "   Mar Girgis Church" << endl;
    cout << "   Hanging Church" << endl;
    cout << "   Amr Ibn Al Aas Mosque" << endl;
    cout << "------------------------------------" << endl;
    cout << "11- Helwan University station" << endl;
    cout << "   Student Residential City" << endl;
    cout << "   Helwan University" << endl;
    cout << "------------------------------------" << endl;
    cout << "12- Sayeda Zeinab station" << endl;
    cout << "   Aboul Rish Hospital" << endl;
    cout << "   Ibn Tulun Mosque" << endl;
    cout << "   Sayeda Zeinab Mosque and Area" << endl;
    cout << "   Kasr El Aini Faculty of Medicine" << endl;
    cout << "   Cairo University Faculty of Pharmacy" << endl;
    cout << "   Cairo University Faculty of Dentistry" << endl;
    cout << "   Salah El Din Citadel" << endl;
    cout << "   Sayeda Aisha Mosque" << endl;
    cout << "------------------------------------" << endl;
    cout << "13- Anwar El Sadat station" << endl;
    cout << "   Egyptian Museum" << endl;
    cout << "   American University" << endl;
    cout << "   Garden City Area" << endl;
    cout << "   Nile Corniche" << endl;
    cout << "------------------------------------" << endl;
    cout << "14- Manshiyat Al Sadr station" << endl;
    cout << "   Al Quba Gardens" << endl;
    cout << "   Ain Shams University" << endl;
    cout << "   University City" << endl;
    cout << "------------------------------------" << endl;
    cout << "15- El Demerdash station" << endl;
    cout << "   El Demerdash Hospital" << endl;
    cout << "   Ain Shams Faculty of Medicine" << endl;
    cout << "------------------------------------" << endl;
    cout << "16- El Shohadaa station" << endl;
    cout << "   Ramses Area" << endl;
    cout << "   Egypt Railway Station" << endl;
    cout << "   Al Fath Mosque" << endl;
    cout << "   El Fagalla" << endl;
    cout << "   Azbakeya Police Station" << endl;
    cout << "------------------------------------" << endl;
    cout << "17- Shubra station" << endl;
    cout << "   Shubra Railway Station" << endl;
    cout << "------------------------------------" << endl;
    cout << "18- Adly Mansour station" << endl;
    cout << "   New Administrative Capital" << endl;
    cout << "------------------------------------" << endl;
    cout << "19- El Abbasia station" << endl;
    cout << "   Nour Mosque and Ain Shams University" << endl;
    cout << "------------------------------------" << endl;
    cout << "20- Safaa Hegazi station" << endl;
    cout << "   Zamalek area" << endl;
    cout << "------------------------------------" << endl;
    cout << "21- Abdo Pasha station" << endl;
    cout << "   Faculty of Engineering, Ain Shams University" << endl;
    cout << "------------------------------------" << endl;
    cout << "22- Bab El Shaaria station" << endl;
    cout << "   El Moez Street" << endl;
    cout << "------------------------------------" << endl;
    cout << "23- Al Ahram station" << endl;
    cout << "   Al Korba Area" << endl;
    cout << "------------------------------------" << endl;
    int choice;
    
    
  cout << "Want to exit press 1" << endl;
  cin >> choice;
  if (choice==1) {
        return;
    }
}
struct MetroStage {
    int number;
    string description;
    int price;
};
MetroStage metroStages[4] = {
    {1, "6 LE from 1 station to 9 stations", 6},
    {2, "8 LE from 10 stations to 16 stations", 8},
    {3, "12 LE from 17 stations to 23 stations", 12},
    {4, "15 LE greater than 23 stations", 15}
};
struct SubscriptionType
{
    string name;
    string description;
    int price[4];
};

SubscriptionType studentCard =
{
    "Student Card",
    "Fixed amount every 3 months for 180 trips",
    {33, 41, 50, 65}
};

SubscriptionType publicCardMonthly = {
    "Public Card (1 Month)",
    "Fixed amount every 1 month for 60 trips",
    {230, 290, 340, 450}
};

SubscriptionType publicCardYearly = {
    "Public Card (1 Year)",
    "Fixed amount every 1 year for 730 trips",
    {1500, 2500, 3500, 4500}
};

// Cash Wallet Card
struct CashWalletCard {
    int limit;
    string description;
};

CashWalletCard cashWalletCard = {
    400,
    "Pay any amount of money (multiples of 10) at any time. Charges individual tickets according to metro stages."
};
void displayMetroStages()
{
    cout << "Metro Stages:" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << "- #" << metroStages[i].number << " => " << metroStages[i].description << " - Price: " << metroStages[i].price << " LE" << endl;
    }
}
void displaySubscriptionTypes() {
    cout << "Subscription Types:" << endl;
    cout << "1. " << studentCard.name << ":" << endl;
    cout << "   - " << studentCard.description << endl;
    cout << "   - Example prices: ";
    for (int i = 0; i < 4; ++i) {
        cout << studentCard.price[i] << " LE for stage #" << i + 1 << ", ";
    }
    cout << endl;

    cout << "2. " << publicCardMonthly.name << ":" << endl;
    cout << "   - " << publicCardMonthly.description << endl;
    cout << "   - Example prices: ";
    for (int i = 0; i < 4; ++i) {
        cout << publicCardMonthly.price[i] << " LE for stage #" << i + 1 << ", ";
    }
    cout << endl;

    cout << "3. " << publicCardYearly.name << ":" << endl;
    cout << "   - " << publicCardYearly.description << endl;
    cout << "   - Example prices: ";
    for (int i = 0; i < 4; ++i) {
        cout << publicCardYearly.price[i] << " LE for stage #" << i + 1 << ", ";
    }
    cout << endl;
}
void displayCashWalletCard() {
    cout << "Cash Wallet Card:" << endl;
    cout << "- Card limit: " << cashWalletCard.limit << " LE" << endl;
    cout << "- Description: " << cashWalletCard.description << endl;
}
void subDetails()
{
    displayMetroStages();
    cout << endl;
    displaySubscriptionTypes();
    cout << endl;
    displayCashWalletCard();
}
void userDetails()
{
    cout << "User ID: " << users[indexOfUsers].id << endl;
    cout << "Username: " << users[indexOfUsers].UserAccount.username << endl;
    cout << "Email: " << users[indexOfUsers].UserAccount.email << endl;
    cout << "Password: " << users[indexOfUsers].UserAccount.password << endl;
    cout << "Balance: " << users[indexOfUsers].balance << endl;
    cout << "Subscription Name: " << users[indexOfUsers].Sub.subName << endl;
    cout << "Start Date: " << users[indexOfUsers].Sub.startDate << endl;
    cout << "End Date: " << users[indexOfUsers].Sub.endDate << endl;
    cout << "Validity Days: " << users[indexOfUsers].Sub.ValidityDays << endl;
    cout << "Index: " << users[indexOfUsers].Sub.index << endl;
    cout << "Stage: " << users[indexOfUsers].Sub.stage << endl;
    cout << "Rides Count: " << users[indexOfUsers].Sub.ridesCount << endl;
}
void chat_bot()
{

    cout << "hello, " << users[indexOfUsers].UserAccount.username << endl;
    cout << "How can help you today? " << endl;
    string put;
    cin.ignore();
    getline(cin, put);
    while (true)
    {
        cout << " What is your problem? " << "Choose \n " << endl;
        cout << "-----------------------------------------------------\n";
        cout << "1: Do you want to edit any thing? \n2: Do you want to know or view any thing? \n3: Do you want to add ride? \n4: Exit" << endl;
        int choose;
        cin >> choose;
        while (choose > 5 || choose < 1)
        {
            cout << "Invalid choice. Please choose again." << endl;
            cin >> choose;
        }
        switch (choose)
        {
        case 1:
            DeletScreen();
            cout << " If you want update your information go to the menu and choose 4 \n or upgrade your subscription go to the menu and choose 2 " << endl;
            break;
        case 2:
            DeletScreen();
            cout << " 1: View your data \n 2: View your subscription details  \n 3: know the types of subscribtions details \n 4: view all rides \n 5: Know the placse next the stations \n 6: View the metro map " << endl;
            cout << " choose: \n -----------------------------------------------\n";
            int c2;
            cin >> c2;
            switch (c2)
            {
            case 1:
                userDetails();
                break;
            case 2:
                cout << "Go to the menu and choose 2 \n";
            case 3:
                subDetails();
                break;
            case 4:
                cout << "Go to the menu and choose 3 \n ";
                break;
            case 5:
                cout << "Go to the menu and choose 5  \n";
                break;
            case 6:
                view_map();
                break;
            default:
                cout << " this is choice not exist " << endl;
                break;
            }
            break;
        case 3:
            cout << "Go to the menu and choose 1 \n";
            break;
        case 4:
            cout << "Exiting..." << endl;
            return;
        default:
            cout << " this choice no exist " << endl;
            continue;

        }


        char complete;
        cout << "Do you want to make more changes? (y/n): " << endl;
        cin >> complete;
        if (complete == 'y' || complete == 'Y')
        {
            continue;
        }
        else
        {
            return;
        }
    }
}
void drawHeader() {
    cout << setw(70) << "----------------------" << endl;
    cout << setw(70) << "|     MetroMate      |" << endl;
    cout << setw(70) << "----------------------" << endl;
    cout << string(120, '-') << endl << endl;

}
void userMenu()

{
    drawHeader();
    float cost=0;
    int valid = 0;
    int stage; // sub stage
    // when the user to do any thing else  
    int next = 0;
    int walletprice; // when the sub is wallet 
    if (users[indexOfUsers].SubFound == false)
    {
        purchasesubscribtion( cost);
    }
    while (true) {
        cout << "Hello " << users[indexOfUsers].UserAccount.email << endl;
        cout << "Your Balance:" << users[indexOfUsers].balance << endl;
        if (users[indexOfUsers].Sub.index=='W') {
            cout << "Wallet Money " << users[indexOfUsers].walletMoney << endl;
       }
        cout << "Choose: " << endl;
        cout << "-------------------------------" << endl;
        cout << "1: Add Ride " << endl;
        cout << "2: Manage Subscription" << endl;
        cout << "3: View Ride History" << endl;
        cout << "4: Update Personal Information" << endl;
        cout << "5: Chatbot" << endl;
        cout << "6: Some places near the stations" << endl;
        cout << "7: Log Out" << endl;
        cin >> next;

        if (next == 1) {
            DeletScreen();
            NumberOfStations = checkInAndCheckOut(userDeparture, userDestination);
            DeletScreen();
        }
        else if (next == 2) {
            DeletScreen();
            ManageSubscription( cost, stage);
            DeletScreen();
        }
        else if (next == 3) {
            DeletScreen();

            viewUserRideHistory();
            DeletScreen();
        }
        else if (next == 4) {
            DeletScreen();
            UpdatePersonalInformation();
            DeletScreen();
        }
        else if (next == 5) {
            DeletScreen();
            chat_bot();
            DeletScreen();
            // Break out of the loop when user chooses to log out
        }
        else if (next==6) {
            DeletScreen();
            somePlacesNextTheStations();
            DeletScreen();
        }
        else if (next == 7) {
            DeletScreen();
            LogOut();
            DeletScreen();
            break; // Break out of the loop when user chooses to log out
        }
        else {
            cout << "Invalid choice. Please choose again." << endl;
        }
    }
}
int close;
void Store();
void MainMenu() {
    int accountExist;

    do {
        cout << "1. Log In\n";
        cout << "2. Sign Up\n";
        cout << "3. Close the program\n";
        cout << "Enter your choice: ";
        cin >> accountExist;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters in the input buffer
            continue; // Skip to the next iteration
        }
        switch (accountExist) {
        case 1:
            if (Login()) {
                if (isAdmin)
                    AdminMainMenu();
                else
                    userMenu();
            }
            break; // Added break statement
            
        case 2:
            if (SignUp()) {


                userMenu();
            }
            break; // Added break statement

        case 3:
            cout << "See you later!" << endl;
            DeletScreen();
            Store();
            exit(0);
            break; // Added break statement

        default:
            cout << "Invalid choice\n";
            break;
        }


    } while (accountExist != 1 || accountExist != 2 || accountExist != 3);
}
void Read() {
    readrealSub();
    ReadFromFileTheDataOfSub();
    ReadFromFileThePrices();
    readUserCount();
    ReadFromFileTheDataOfUsers();
    ReadTheNumberOfRides();
    ReadFromFileTheDataOfRides();
    ReadStationNumbersToFile();
    ReadFromFileTheDataOfStations();
    ReadTheSubscriptionOfUsers();
    ReadFromFileConstantPrice();
    


}
int main()
{

    Read();
    MainMenu();
    Store();


}
void Store() {
   
    StoreTheDataOfUsers();
    StoreTheNumberOfUsers();
    StoreTheNumberOfRides();
    StoreStationNumbersToFile();
    StoreTheDataOfStations();
    StoreTheDataOfRides();
    StoreThePrices();
    StoreTheSubscriptionOfUsers();
    StoreTheRealSub();
    StoreTheConstantPrice();
    StoreTheDataOfSub();


}
void LogOut() {
    if (login_status) {
        cout << "Are you sure you want to logout?(y/n)";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "Logged out successfully." << endl;
            isAdmin = false;
            DeletScreen();
            MainMenu();
        }

    }

}