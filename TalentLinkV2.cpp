#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
#include <queue>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
#include <set>
#include <unordered_set>
#include <functional>
#include <queue>
#include <stdexcept>
#include <ctime>
#include <stack>
#include <iterator>
#include "Staff.hpp"
#include "EventManager.hpp"
#include "User.hpp"

using namespace std;

    string getPassword() {
    string password;
    cout<<""<< endl;
    char ch = _getch();
    while (ch != '\r') {
    if (ch == '\b') {
    if (!password.empty()) {
    cout << "\b \b";
    password.pop_back();
    }
} else {
password += ch;
cout << '*';
}
ch = _getch();
}
cout << endl;
return password;
}

void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}
template <typename T>
bool Staff::binarySearch(T target, int (Staff::*getAttribute)() const, const std::string& attributeName) const {
    ifstream file("staff_data.txt");

    if (!file.is_open()) {
        cout << "Error opening file for searching." << endl;
        return false;
    }

    vector<Staff> staffList;

    Staff tempStaff;  // Temporary object to store data from the file
    while (file >> tempStaff.id >> tempStaff.name >> tempStaff.age >> tempStaff.gender >> tempStaff.height >> tempStaff.weight >> tempStaff.contact_number) {
        staffList.push_back(tempStaff);
    }

    file.close();

    // Sort the list before binary search
    sort(staffList.begin(), staffList.end(), [](const Staff& a, const Staff& b) {
        return a.getID() < b.getID();
    });

    // Perform binary search
    int low = 0;
    int high = staffList.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int currentAttributeValue = (staffList[mid].*getAttribute)();

        if (currentAttributeValue == target) {
            // Display the found staff details
            staffList[mid].displayStaffDetails();
            return true;
        }

        if (currentAttributeValue < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << "Staff with " << attributeName << " " << target << " not found." << endl;
    return false;
}
void Staff::displayStaffDetails() const {
    cout << left << setw(4) << id
         << setw(15) << name
         << setw(7) << age
         << setw(8) << gender
         << setw(12) << height
         << setw(12) << weight
         << setw(15) << contact_number << endl;

}
void Staff::displayAllStaffData() {
        ifstream file("staff_data.txt");

        if (!file.is_open()) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        vector<Staff> staffList;  // Vector to store staff data

    // Read staff data from the file and store it in the vector
    while (file >> id >> name >> age >> gender >> height >> weight >> contact_number) {
        Staff staff(id, name, age, gender, height, weight, contact_number);
        staffList.push_back(staff);
    }

    file.close();
    //sort algorithm
    sort(staffList.begin(), staffList.end(), [](const Staff& a, const Staff& b) {
        return a.getID() < b.getID();
    });

    cout << "\nAll Staff Data (Sorted by ID):\n";

    // Display column headers
    cout << left <<  setw(4) << "ID" << setw(15) << "Name" << setw(7) << "Age" << setw(8) << "Gender"
         << setw(12) << "Height(cm)" << setw(12) << "Weight(kg)" << setw(15) << "Contact Number(+60)\n";

    // Display sorted staff data
    int lastDisplayedID = -1;  // Initialize with an invalid ID

    for (const auto& staff : staffList) {
    // Check if the current staff ID is the same as the last displayed ID
    if (staff.getID() != lastDisplayedID) {
        cout << left << setw(4) << staff.getID() << setw(15) << staff.getName() << setw(7) << staff.getAge() << setw(8)
             << staff.getGender() << setw(12) << staff.getHeight() << setw(12) << staff.getWeight() << setw(15)
             << staff.getContactNumber() << "\n";

        lastDisplayedID = staff.getID();  // Update the last displayed ID
    }
}
    }
void Staff::enterNewDetails() {
    // Prompt user to enter new details
    cout << "\nEnter new details:" << endl;

    // Enter Name with error checking
    do {
        cout << "Enter Name(No space): ";
        cin >> name;

        if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
            cout << "Error: Name can only contain alphabetical characters. Try again." << endl;
        } else {
            break; // Exit the loop if the name is valid
        }
    } while (true);

    // Enter Age with error checking
    do {
        cout << "Enter Age: ";
        while (!(cin >> age) || age <= 0) {
            cout << "Invalid input. Age must be a positive integer. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (age < 18 || age > 100) {
            cout << "Error: Age must be legal between 18 and 100. Try again." << endl;
        } else {
            break; // Exit the loop if the age is valid
        }
    } while (true);

    // Enter Gender with error checking
    do {
        cout << "Enter Gender(Male / Female): ";
        cin >> gender;

        // Convert the gender to lowercase for case-insensitive comparison
        transform(gender.begin(), gender.end(), gender.begin(), ::tolower);

        if (gender != "male" && gender != "female") {
            cout << "Error: Invalid gender. Please enter 'Male' or 'Female'. Try again." << endl;
        } else {
            break; // Exit the loop if the gender is valid
        }
    } while (true);

    // Enter Height with error checking
    do {
        cout << "Enter Height(cm): ";
        while (!(cin >> height) || height <= 0) {
            cout << "Invalid input. Height must be a positive integer. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        break; // Exit the loop if the height is valid
    } while (true);

    // Enter Weight with error checking
    do {
        cout << "Enter Weight(kg): ";
        while (!(cin >> weight) || weight <= 0) {
            cout << "Invalid input. Weight must be a positive integer. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        break; // Exit the loop if the weight is valid
    } while (true);

    // Enter Contact Number with error checking
    do {
        cout << "Enter Contact Number (+60): ";
        while (!(cin >> contact_number) || contact_number <= 0) {
            cout << "Invalid input. Contact Number must be a positive integer. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (to_string(contact_number).length() <= 8 || to_string(contact_number).length() >= 11) {
            cout << "Error: Contact Number must be a 9 or 10-digit integer. Try again." << endl;
        } else {
            break; // Exit the loop if the contact number is valid
        }
    } while (true);
}

     int Staff::getID() const {
        return id;
    }

    const string& Staff::getName() const {
        return name;
    }

    int Staff::getAge() const {
        return age;
    }

    const string& Staff::getGender() const {
        return gender;
    }

    int Staff::getHeight() const {
        return height;
    }

    int Staff::getWeight() const {
        return weight;
    }

    int Staff::getContactNumber() const {
        return contact_number;
    }
    Staff::Staff() : id(0), age(0), height(0), weight(0), contact_number(0) {}

    // Constructor to initialize the object
    Staff::Staff(int _id, const string& _name, int _age, const string& _gender,
          int _height, int _weight, int _contact_number)
        : id(_id), name(_name), age(_age), gender(_gender),
          height(_height), weight(_weight), contact_number(_contact_number) {}

    // Function to add new staff details to the text file
void Staff::addNewStaff(const Staff& newStaff) {
    ofstream file("staff_data.txt", ios::app);

    if (!file.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    file << newStaff.id << " " << newStaff.name << " " << newStaff.age << " " << newStaff.gender << " "
         << newStaff.height << " " << newStaff.weight << " " << newStaff.contact_number << endl;

    file.close();
}

    void Staff::addStaff() {
        ifstream file("staff_data.txt");

    if (!file.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    // Read existing IDs to check for duplicates
    vector<int> existingIDs;
    while (file >> id >> name >> age >> gender >> height >> weight >> contact_number) {
        existingIDs.push_back(id);
    }
    file.close();
    do{
        cout << "Enter ID: ";
    while (!(cin >> id) || id <= 0) {
        cout << "Invalid input. ID must be a positive integer. Try again: ";
        cin.clear(); // Clear input buffer to restore cin to a usable state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }
    if (find(existingIDs.begin(), existingIDs.end(), id) != existingIDs.end()) {
            cout << "Error: ID already exists. Please enter a different ID." << endl;
        } else {
            break;
        }
    } while (true);

        cin.ignore(); // Clear any previous newline character

    do {
        cout << "Enter Name(No space): ";
        getline(cin, name);

        if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
            cout << "Error: Name can only contain alphabetical characters. Try again." << endl;
        } else {
            break; // Exit the loop if the name is valid
        }
    } while (true);

    do {
        cout << "Enter Age: ";
        while (!(cin >> age) || age <= 0) {
            cout << "Invalid input. Age must be a positive integer. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (age < 18 || age > 100) {
            cout << "Error: Age must be between 18 and 100. Try again." << endl;
        } else {
            break; // Exit the loop if the age is valid
        }
    } while (true);

    do {
        cout << "Enter Gender(Male / Female): ";
        cin >> gender;

    // Convert the gender to lowercase for case-insensitive comparison
        transform(gender.begin(), gender.end(), gender.begin(), ::tolower);

    if (gender != "male" && gender != "female") {
        cout << "Error: Invalid gender. Please enter 'Male' or 'Female'. Try again." << endl;
    } else {
        break; // Exit the loop if the gender is valid
    }
} while (true);

    cout << "Enter Height(cm): ";
    while (!(cin >> height) || height <= 0) {
        cout << "Invalid input. Height must be a positive integer. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter Weight(kg): ";
    while (!(cin >> weight) || weight <= 0) {
        cout << "Invalid input. Weight must be a positive integer. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    do {
        cout << "Enter Contact Number (+60): ";
        while (!(cin >> contact_number) || contact_number <= 0) {
            cout << "Invalid input. Contact Number must be a positive integer. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (to_string(contact_number).length() <= 8 || to_string(contact_number).length() >= 11 ) {
            cout << "Error: Contact Number must be at 9 or 10 digit integer. Try again." << endl;
        } else {
            break; // Exit the loop if the contact number is valid
        }
    } while (true);
    Staff newStaff = {id, name, age, gender, height, weight, contact_number};

    // Call the addNewStaff function to write to the file
    addNewStaff(newStaff);

    cout << "Staff added successfully." << endl;
}

    bool Staff::deleteStaff(int staffId) {
        ifstream inFile("staff_data.txt");
        ofstream outFile("temp.txt");

        if (!inFile.is_open() || !outFile.is_open()) {
            cout << "Error opening files for deletion." << endl;
            return false;
        }

        bool found = false;

        while (inFile >> id >> name >> age >> gender >> height >> weight >> contact_number) {
            if (id == staffId) {
                found = true;
                continue; // Skip writing this line to outFile
            }

            outFile << id << " " << name << " " << age << " " << gender << " "
                    << height << " " << weight << " " << contact_number << endl;
        }

        inFile.close();
        outFile.close();

        if (found) {
            remove("staff_data.txt");
            rename("temp.txt", "staff_data.txt");
            cout << "Staff with ID " << staffId << " deleted successfully." << endl;
        } else {
            cout << "Staff with ID " << staffId << " not found." << endl;
            remove("temp.txt"); // No need to keep temp file if no deletion occurred
        }

        return found;
    }

    bool Staff::editStaffDetails(int staffId) {
        ifstream inFile("staff_data.txt");
        ofstream outFile("temp.txt");

        if (!inFile.is_open() || !outFile.is_open()) {
            cout << "Error opening files for editing." << endl;
            return false;
        }

        bool found = false;

        while (inFile >> id >> name >> age >> gender >> height >> weight >> contact_number) {
            if (id == staffId) {
                found = true;

                // Display current details
                cout << "Current Details:" << endl;
                displayStaffDetails();

                // Enter new details
                enterNewDetails();

                // Write the updated details to the temp file
                outFile << id << " " << name << " " << age << " " << gender << " "
                        << height << " " << weight << " " << contact_number << endl;

                cout << "\nStaff details updated successfully." << endl;
            } else {
                // Write unchanged details to the temp file
                outFile << id << " " << name << " " << age << " " << gender << " "
                        << height << " " << weight << " " << contact_number << endl;
            }
        }

        inFile.close();
        outFile.close();

        if (found) {
            remove("staff_data.txt");
            rename("temp.txt", "staff_data.txt");
        } else {
            cout << "Staff with ID " << staffId << " not found." << endl;
            remove("temp.txt"); // No need to keep temp file if no editing occurred
        }

        return found;
    }

bool Staff::binarySearchByAge(int targetAge) const {
    ifstream file("staff_data.txt");

    if (!file.is_open()) {
        cout << "Error opening file for searching." << endl;
        return false;
    }

    vector<Staff> staffList;
    set<int> displayedIDs;  // Set to keep track of displayed staff IDs

    Staff tempStaff;  // Temporary object to store data from the file
    while (file >> tempStaff.id >> tempStaff.name >> tempStaff.age >> tempStaff.gender >> tempStaff.height >> tempStaff.weight >> tempStaff.contact_number) {
        staffList.push_back(tempStaff);
    }

    file.close();

    // Sort the list based on age before binary search
    sort(staffList.begin(), staffList.end(), [](const Staff& a, const Staff& b) {
        return a.getAge() < b.getAge();
    });

    // Perform binary search
    int low = 0;
    int high = staffList.size() - 1;
    bool found = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int currentAge = staffList[mid].getAge();

        if (currentAge == targetAge) {
            // Display the found staff details
            found = true;

            // Display all staff details with matching age
            while (mid >= 0 && staffList[mid].getAge() == targetAge) {
                int currentID = staffList[mid].getID();

                // Check if the ID has not been displayed yet to avoid duplicates
                if (displayedIDs.find(currentID) == displayedIDs.end()) {
                    staffList[mid].displayStaffDetails();
                    displayedIDs.insert(currentID);  // Add the ID to the set
                }

                mid--;
            }

            mid = low + 1; // Move to the next element in the range
            while (mid < staffList.size() && staffList[mid].getAge() == targetAge) {
                int currentID = staffList[mid].getID();

                // Check if the ID has not been displayed yet to avoid duplicates
                if (displayedIDs.find(currentID) == displayedIDs.end()) {
                    staffList[mid].displayStaffDetails();
                    displayedIDs.insert(currentID);  // Add the ID to the set
                }

                mid++;
            }

            return true;
        }

        if (currentAge < targetAge) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        cout << "Staff with Age " << targetAge << " not found." << endl;
    }

    return found;
}
bool Staff::binarySearchByHeight(int targetHeight) const {
    ifstream file("staff_data.txt");

    if (!file.is_open()) {
        cout << "Error opening file for searching." << endl;
        return false;
    }

    vector<Staff> staffList;
    set<int> displayedIDs;  // Set to keep track of displayed staff IDs

    Staff tempStaff;  // Temporary object to store data from the file
    while (file >> tempStaff.id >> tempStaff.name >> tempStaff.age >> tempStaff.gender >> tempStaff.height >> tempStaff.weight >> tempStaff.contact_number) {
        staffList.push_back(tempStaff);
    }

    file.close();

    // Sort the list based on height before binary search
    sort(staffList.begin(), staffList.end(), [](const Staff& a, const Staff& b) {
        return a.getHeight() < b.getHeight();
    });

    // Perform binary search
    int low = 0;
    int high = staffList.size() - 1;
    bool found = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int currentHeight = staffList[mid].getHeight();

        if (currentHeight == targetHeight) {
            found = true;

            // Display all staff details with matching height
            while (mid >= 0 && staffList[mid].getHeight() == targetHeight) {
                int currentID = staffList[mid].getID();

                // Check if the ID has not been displayed yet to avoid duplicates
                if (displayedIDs.find(currentID) == displayedIDs.end()) {
                    staffList[mid].displayStaffDetails();
                    displayedIDs.insert(currentID);  // Add the ID to the set
                }

                mid--;
            }

            mid = low + 1; // Move to the next element in the range
            while (mid < staffList.size() && staffList[mid].getHeight() == targetHeight) {
                int currentID = staffList[mid].getID();

                // Check if the ID has not been displayed yet to avoid duplicates
                if (displayedIDs.find(currentID) == displayedIDs.end()) {
                    staffList[mid].displayStaffDetails();
                    displayedIDs.insert(currentID);  // Add the ID to the set
                }

                mid++;
            }

            return true;
        }

        if (currentHeight < targetHeight) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        cout << "Staff with Height " << targetHeight << " not found." << endl;
    }

    return found;
}

// Function to perform binary search based on weight
bool Staff::binarySearchByWeight(int targetWeight) const {
    ifstream file("staff_data.txt");

    if (!file.is_open()) {
        cout << "Error opening file for searching." << endl;
        return false;
    }

    vector<Staff> staffList;
    set<int> displayedIDs;  // Set to keep track of displayed staff IDs

    Staff tempStaff;  // Temporary object to store data from the file
    while (file >> tempStaff.id >> tempStaff.name >> tempStaff.age >> tempStaff.gender >> tempStaff.height >> tempStaff.weight >> tempStaff.contact_number) {
        staffList.push_back(tempStaff);
    }

    file.close();

    // Sort the list based on weight before binary search
    sort(staffList.begin(), staffList.end(), [](const Staff& a, const Staff& b) {
        return a.getWeight() < b.getWeight();
    });

    // Perform binary search
    int low = 0;
    int high = staffList.size() - 1;
    bool found = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int currentWeight = staffList[mid].getWeight();

        if (currentWeight == targetWeight) {
            found = true;

            // Display all staff details with matching weight
            while (mid >= 0 && staffList[mid].getWeight() == targetWeight) {
                int currentID = staffList[mid].getID();

                // Check if the ID has not been displayed yet to avoid duplicates
                if (displayedIDs.find(currentID) == displayedIDs.end()) {
                    staffList[mid].displayStaffDetails();
                    displayedIDs.insert(currentID);  // Add the ID to the set
                }

                mid--;
            }

            mid = low + 1; // Move to the next element in the range
            while (mid < staffList.size() && staffList[mid].getWeight() == targetWeight) {
                int currentID = staffList[mid].getID();

                // Check if the ID has not been displayed yet to avoid duplicates
                if (displayedIDs.find(currentID) == displayedIDs.end()) {
                    staffList[mid].displayStaffDetails();
                    displayedIDs.insert(currentID);  // Add the ID to the set
                }

                mid++;
            }

            return true;
        }

        if (currentWeight < targetWeight) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        cout << "Staff with Weight " << targetWeight << " not found." << endl;
    }

    return found;
}
bool Staff::saveToFile(const string & filename) const {
    ofstream file(filename,ios::app);
    if (!file.is_open()) {
        cout << "Cannot open file." << endl;
        return false;
    }

    for (const auto &staff : staffList) {
        file << staff.getID() << " " << staff.getName() << " " << staff.getAge() << " "
             << staff.getGender() << " " << staff.getHeight() << " " << staff.getWeight()
             << " " << staff.getContactNumber() << endl;
    }

    file.close();
    cout << "Saved to file successfully." << endl;
    cout << "\nThanks for using Labour Management System." << endl;
    return true;
}


void EventManager::saveEventsToFile(const string& filename) const {
    ofstream file(filename); // Open the file in truncation mode

    if (!file.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    for (const auto& event : events) {
        file << event.id << ' ' << event.eventName << ' ' << event.eventDescription << ' '
             << event.year << ' ' << event.month << ' ' << event.day << ' '
             << event.startTime << ' ' << event.endTime << ' ' << event.salary << '\n';
    }

    file.close();
    cout << "Events saved to file successfully." << endl;
    cout << "Thanks for using the Event Management System." << endl;
}

void EventManager::addEvent() {
    Event newEvent;
    undoStack.push(events);

    do {
        newEvent.id = getValidID();

        auto it = find_if(events.begin(), events.end(), [&newEvent](const Event& e) {
            return e.id == newEvent.id;
        });

        if (it != events.end()) {
            cout << "Error: Event with ID " << newEvent.id << " already exists. Please enter a different ID.\n";
        } else {
            break;  // Break the loop if the ID is valid
        }
    } while (true);

    newEvent.eventName = getValidAlphabeticInput("Enter Event Name (No space): ");

     cout << "Enter Event Description: ";
     cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // Clear input buffer

    getline(cin, newEvent.eventDescription);

    // Tokenize the input to count words
    istringstream iss(newEvent.eventDescription);
    vector<string> words(istream_iterator<string>{iss},
                        istream_iterator<string>());

    // Limit the event description to 25 words
    ostringstream limitedDescription;
    for (size_t i = 0; i < min(words.size(), static_cast<size_t>(25)); ++i) {
        limitedDescription << words[i] << ' ';
    }

    // Update the event description
    newEvent.eventDescription = limitedDescription.str();

    newEvent.year = getValidIntInput("Enter Year: ", 2024, 2034);
    newEvent.month = getValidIntInput("Enter Month: ", 1, 12);
    newEvent.day = getValidIntInput("Enter Day: ", 1, 31);

    getValidTimeRange(newEvent.startTime, newEvent.endTime);

    newEvent.salary = getValidIntInput("Enter Salary: ", 1, numeric_limits<int>::max());

    events.push_back(newEvent);
    undoStack.push(events);

    cout << "\nEvent added successfully:\n";
    displayEvent(newEvent);
    saveEventsToFile("events.txt");
}

void EventManager::displayEvent(const Event& event) {
    cout << "ID" << '\t' << setw(15) << "Event Name" << '\t' << setw(25) << "Event Description" << '\t'
     << setw(8) << "Year" << '\t' << setw(8) << "Month" << '\t' << setw(8) << "Day" << '\t' << setw(10) << "Start Time"
     << '\t' << setw(10) << "End Time" << '\t' << setw(10) << "Salary\n";

    cout << event.id << '\t' << setw(15) << event.eventName << '\t' << setw(25) << event.eventDescription
         << '\t' << setw(8) << event.year << '\t' << setw(8) << event.month << '\t' << setw(8) << event.day << '\t'
         << setw(10) << event.startTime << '\t' << setw(10) << event.endTime << '\t' << setw(10) << event.salary << "\n";
}


void EventManager::displayAllEvents() {
    // Sort events by salary
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.salary < b.salary;
    });

    cout << "\nAll Event Data (Sorted by Salary):\n";

    // Display column headers
cout <<"ID" << '\t' << setw(20) << "Event Name" << '\t' << setw(25) << "Event Description" << '\t'
     << setw(10) << "Year" << '\t' << setw(10) << "Month" << '\t' << setw(10) << "Day" << '\t' << setw(10) << "Start Time"
     << '\t' << setw(10) << "End Time" << '\t' << setw(10) << "Salary\n";

for (const auto& event : events) {
    cout <<event.id << '\t' << setw(20) << event.eventName << '\t' << setw(25) << event.eventDescription
         << '\t' << setw(10) << event.year << '\t' << setw(10) << event.month << '\t' << setw(10) << event.day << '\t'
         << setw(10) << event.startTime << '\t' << setw(10) << event.endTime << '\t' << setw(10) << event.salary << "\n";
}
}

bool EventManager::isValidTime(int time) {
    return (time >= 0 && time <= 2359 && time % 100 < 60);
}

bool EventManager::isValidID(const string& input) {
    for (char ch : input) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

bool EventManager::isValidAlphabetic(const string& input) {
    for (char ch : input) {
        if (!isalpha(ch) && !isspace(ch)) {
            return false;
        }
    }
    return true;
}

bool EventManager::isValidInt(const string& input, int minValue, int maxValue) {
    stringstream ss(input);
    int value;
    return (ss >> value) && (ss.eof()) && (value >= minValue) && (value <= maxValue);
}

int EventManager::getValidID() {
    int id;
    string input;

    do {
        cout << "Enter Event ID: ";
        cin >> input;

        if (!isValidID(input)) {
            cout << "Invalid input. Please enter a numeric ID.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            stringstream ss(input);
            ss >> id;
        }
    } while (!isValidID(input));

    return id;
}

string EventManager::getValidAlphabeticInput(const string& prompt, bool requireDateFormatValidation) {
    string input;

    do {
        cout << prompt;
        cin >> ws; // Consume leading whitespaces
        getline(cin, input);

        if (!isValidAlphabetic(input)) {
            cout << "Invalid input. Please enter only alphabetic characters.\n";
        } else {
            break;
        }
    } while (true);

    return input;
}

int EventManager::getValidIntInput(const string& prompt, int minValue, int maxValue) {
    int value;
    string input;

    do {
        cout << prompt;
        cin >> input;

        if (!isValidInt(input, minValue, maxValue)) {
            cout << "Invalid input. Please enter a valid integer in the specified range.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            stringstream ss(input);
            ss >> value;
        }
    } while (!isValidInt(input, minValue, maxValue));

    return value;
}

void EventManager::getValidTimeRange(int& startTime, int& endTime) {
    do {
        startTime = getValidIntInput("Enter Start Time (1000-2359): ", 1000, 2359);
        endTime = getValidIntInput("Enter End Time (1000-2359): ", 1000, 2359);

        if (!isValidTime(startTime) || !isValidTime(endTime) || startTime >= endTime) {
            cout << "Invalid time range. Please check start time and end time.\n";
        }
    } while (!isValidTime(startTime) || !isValidTime(endTime) || startTime >= endTime);
}
void EventManager::loadEventsFromFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    events.clear();  // Clear existing events before loading from file

    Event newEvent;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        iss >> newEvent.id >> newEvent.eventName >> newEvent.eventDescription
            >> newEvent.year >> newEvent.month >> newEvent.day
            >> newEvent.startTime >> newEvent.endTime >> newEvent.salary;

        events.push_back(newEvent);
    }

    file.close();
}
void EventManager::removeEventByID(int id) {
    undoStack.push(events);
    auto it = find_if(events.begin(), events.end(), [id](const Event& e) {
        return e.id == id;
    });

    if (it != events.end()) {
        events.erase(it);
        cout << "Event with ID " << id << " removed successfully.\n";
    } else {
        cout << "Error: Event with ID " << id << " not found.\n";
    }
}

void EventManager::editEventByID(int id) {
    undoStack.push(events);

    auto it = find_if(events.begin(), events.end(), [id](Event& e) {
        return e.id == id;
    });

    if (it != events.end()) {
            undoStack.push(events);
        // Prompt user for new details
        it->eventName = getValidAlphabeticInput("Enter Event Name (No space and enter twice after input): ");
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Enter Event Description: ";
        getline(cin, it->eventDescription);

        it->year = getValidIntInput("Enter Year: ", 1900, 9999);
        it->month = getValidIntInput("Enter Month: ", 1, 12);
        it->day = getValidIntInput("Enter Day: ", 1, 31);
        getValidTimeRange(it->startTime, it->endTime);
        it->salary = getValidIntInput("Enter Salary: ", 1, numeric_limits<int>::max());

        cout << "Event with ID " << id << " edited successfully.\n";
    } else {
        cout << "Error: Event with ID " << id << " not found.\n";
    }
}
    void EventManager::undoLastOperation() {
    if (!undoStack.empty()) {
        events = undoStack.top();
        undoStack.pop();
        cout << "Undo successful.\n";
        saveEventsToFile("events.txt");
    } else {
        cout << "Error: No operation to undo.\n";
    }
}

bool isStaffIdValid(int enteredId) {
    ifstream staffFile("staff_data.txt");
    int id;

    while (staffFile >> id) {
        if (id == enteredId) {
            staffFile.close();
            return true;
        }
        // Assuming the next line contains additional staff information
        staffFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    staffFile.close();
    return false;
}
// Forward declaration for the saveToFile function
void saveToFile(const string& filename, queue<User> events);



void User::bookEvent(queue<User>& bookedEvents, queue<User>& workQueue) {
    int eventIdToBook;
    cout << "\n\tEnter the event ID to book: ";

    while (!(cin >> eventIdToBook) || cin.peek() != '\n') {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Invalid input. Please enter a valid event ID: ";
    }

    bool eventFound = false;
    queue<User> tempQueue;

     while (!workQueue.empty()) {
        auto currentEvent = workQueue.front();
        workQueue.pop();

        if (currentEvent.id == eventIdToBook) {
            eventFound = true;
            auto selectedEvent = currentEvent;

            cout << "\n\tEnter your User ID: ";
            cin >> selectedEvent.userid;

            auto existingBooking = bookedEvents;
            bool alreadyBooked = false;

            while (!existingBooking.empty()) {
                if (existingBooking.front().id == selectedEvent.id) {
                    alreadyBooked = true;
                    break;
                }
                existingBooking.pop();
            }

            if (!alreadyBooked) {
                bookedEvents.push(selectedEvent);
                showBookedEvents(bookedEvents);
                saveToFile("bookedevents.txt", bookedEvents);
                saveToFile("events.txt", workQueue);
            } else {
                cout << "Event is already booked. You cannot book the same event multiple times.\n";
            }
        } else {
            tempQueue.push(currentEvent);
        }
    }

    workQueue = tempQueue;

    if (!eventFound) {
        cout << "Event ID not found. Please check the available events again.\n";
    }
}

void User::accountSummary(queue<User>& bookedEvents) const {
    cout << "\nBooking Details:\n";
    queue<User> tempQueue = bookedEvents;

    while (!tempQueue.empty()) {
        auto event = tempQueue.front();
        tempQueue.pop();

        cout << "\nUser ID: " << event.userid
             << ", Event ID: " << event.id << ", Event Name: " << event.eventName
             << ", Event Description: " << event.eventDescription
             << ", Date: " << event.year << "-" << event.month << "-" << event.day
             << ", Start Time: " << event.startTime << ", End Time: " << event.endTime
             << ", Salary: " << event.salary <<"\n";
    }
}

void User::showAvailableEvents(const queue<User>& workQueue) const {
    if (!workQueue.empty()) {
cout << setw(5) << left << "ID" << '\t' << setw(20) << "Event Name" << '\t' << setw(20) << "Event Description"
     << '\t' << setw(6) << "Year" << '\t' << setw(6) << "Month" << '\t' << setw(6) << "Day" << '\t' << setw(12) << "Start Time"
     << '\t' << setw(12) << "End Time" << '\t' << setw(8) << "Salary\n";

// Display sorted event data from tempQueue
queue<User> tempQueue = workQueue;
while (!tempQueue.empty()) {
    auto event = tempQueue.front();
    tempQueue.pop();

    cout << setw(4) << left << event.id << '\t' << setw(20) << event.eventName << '\t' << setw(20) << event.eventDescription
         << '\t' << setw(6) << event.year << '\t' << setw(6) << event.month << '\t' << setw(6) << event.day << '\t'
         << setw(12) << event.startTime << '\t' << setw(12) << event.endTime << '\t' << setw(8) << event.salary << "\n";
}
    } else {
        cout << "No events available yet.\n";
    }
}

void User::showBookedEvents(const queue<User>& bookedEvents) const {
    if (!bookedEvents.empty()) {
        cout << "Event booked successfully:\n";
        auto lastBookedEvent = bookedEvents.back();

        cout << "Event ID: " << lastBookedEvent.id << ", Name: " << lastBookedEvent.eventName
             << ", Description: " << lastBookedEvent.eventDescription
             << ", Date: " << lastBookedEvent.year << "-" << lastBookedEvent.month << "-"
             << lastBookedEvent.day << ", Start Time: " << lastBookedEvent.startTime
             << ", End Time: " << lastBookedEvent.endTime
             << ", Salary: " << lastBookedEvent.salary << ", User ID: " << lastBookedEvent.userid << "\n";
    } else {
        cout << "No events booked yet.\n";
    }
}

void User::storeBookingDetails(queue<User>& bookedEvents, const User& bookedEvent) {
    bookedEvents.push(bookedEvent);
    cout << "Booking details stored successfully.\n";
}

string User::serializeAvailableEvent() const {
    stringstream ss;
    ss << id << " " << eventName << " " << eventDescription
       << " " << year << " " << month << " " << day << " " << startTime << " " << endTime << " " << salary;
    return ss.str();
}

string User::serializeBookedEvent() const {
    stringstream ss;
    ss <<  id << " " << eventName << " " << eventDescription
       << " " << year << " " << month << " " << day << " " << startTime << " " << endTime
       << " " << salary << " " << userid;
    return ss.str();
}

User User::deserializeAvailableEvent(const string& data) {
    if (data.empty()) {
        throw runtime_error("Empty line in file");
    }

    int id;
    string eventName;
    string eventDescription;
    int year, month, day;
    string startTime;
    string endTime;
    double salary;
    istringstream ss(data);

    if (ss >> id >> eventName >> eventDescription >> year >> month >> day >> startTime >> endTime >> salary) {
        return User(id, eventName, eventDescription, year, month, day, startTime, endTime, salary, 0);
    } else {
        throw runtime_error("Invalid data format for available event");
    }
}

User User::deserializeBookedEvent(const string& data) {
    if (data.empty()) {
        throw runtime_error("Empty line in file");
    }

    int id;
    string eventName;
    string eventDescription;
    int year, month, day;
    string startTime;
    string endTime;
    double salary;
    int userid;
    istringstream ss(data);

    if (ss >> id >> eventName >> eventDescription >> year >> month >> day >> startTime >> endTime >> salary >> userid) {
        return User(id, eventName, eventDescription, year, month, day, startTime, endTime, salary, userid );
    } else {
        throw runtime_error("Invalid data format for booked event");
    }
}

queue<User> User::loadFromFile(const string& filename) {
    queue<User> events;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        int lineNumber = 0;
        while (getline(file, line)) {
            lineNumber++;
            try {
                if (filename == "events.txt") {
                    events.push(deserializeAvailableEvent(line));
                } else if (filename == "bookedevents.txt") {
                    events.push(deserializeBookedEvent(line));
                }
            } catch (const runtime_error& e) {
                           }
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
    return events;
}

void saveToFile(const string& filename, queue<User> events) {
    ofstream file(filename);
    if (file.is_open()) {
        while (!events.empty()) {
            if (filename == "events.txt") {
                file << events.front().serializeAvailableEvent() << "\n";
            } else if (filename == "bookedevents.txt") {
                file << events.front().serializeBookedEvent() << "\n";
            }
            events.pop();
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}


int main() {
    int choice;
    Staff s;
    EventManager eventManager;
    eventManager.loadEventsFromFile("events.txt");
    bool requirePassword = false;
    bool exitProgram = false;

    queue<User> bookedEvents = User::loadFromFile("bookedevents.txt");
    queue<User> workQueue = User::loadFromFile("events.txt");

    system("Color 0E");//oranges

    do {
                string lines[] = {
            "",
        "                _________    __      _       ______  ___      _  _________  _       _______  ___      _  _    _ ",
        "               (___   ___)  /  \\    | |     |  ____||   \\    | |(___   ___)| |     |__   __||   \\    | || |  / /",
        "                   | |     / /\\ \\   | |     | |     | |\\ \\   | |    | |    | |        | |   | |\\ \\   | || | / /",
        "                   | |    / /  \\ \\  | |     | |__   | | \\ \\  | |    | |    | |        | |   | | \\ \\  | || |/ / ",
        "                   | |   | |----| | | |     |  __|  | |  \\ \\ | |    | |    | |        | |   | |  \\ \\ | ||   \\ ",
        "                   | |   | |----| | | |     | |     | |   \\ \\| |    | |    | |        | |   | |   \\ \\| || |\\ \\ ",
        "                   | |   | |    | | | |____ | |____ | |    \\ - |    | |    | |____  __| |__ | |    \\ - || | \\ \\ ",
        "                   |_|   |_|    |_| |______||______||_|     \\__|    |_|    |______||_______||_|     \\__||_|  \\_\\ "
    };
    for (const auto& line : lines) {
        cout << line << endl;
        delay(200); // Adjust the delay time (in milliseconds) as needed
    }

    cout << " " << endl;
    cout << " " << endl;
    cout << "========================================================================================================================" << std::endl;
    cout << " " << endl;
    cout << "                               WELCOME TO Labour Management SYSTEM !!!                                        " << std::endl;
    cout << " " << endl<<endl;
    cout << "========================================================================================================================" << std::endl;

        cout << "Select an option:\n";
        cout << "1. Admin Page\n";
        cout << "2. User Page\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
                requirePassword = true;
            do {
                if (requirePassword) {
                    string password = "";
                    cout << "\n\n\n\t\t\t\t\t Please enter the password : \n" << endl;
                    password = getPassword();
                    while (password != "123") {
                      system("Color 0C");//red
                        cout << "\n\t\t\t\t\t\tInvalid password";
                        cout << "\n\n\n\t\t\t\t\t Please enter the password : \n" << endl;
                        password = getPassword();
                    }
                    system("cls");
                }
                system("Color 0E");//oranges
                cout <<"Redirecting to Admin Page...\n";
                do {
        cout<<"========================================================================================================================"<<endl;
        cout<<" "<<endl;
        cout << "                               WELCOME TO Labour Management SYSTEM !!!                                        " << std::endl;
        cout<<" "<<endl;
        cout<<"========================================================================================================================"<<endl;
        cout << "\n\t\t1. Add New Staff" << endl;
        cout << "\n\t\t2. Remove Staff" << endl;
        cout << "\n\t\t3. Update Staff Details" << endl;
        cout << "\n\t\t4. Display All Staff" <<endl;
        cout << "\n\t\t5. Search Staff Details"<<endl;
        cout << "\n\t\t6. Add new event"<<endl;
        cout << "\n\t\t7. Remove event"<<endl;
        cout << "\n\t\t8. Update event details"<<endl;
        cout << "\n\t\t9. Display all event"<<endl;
        cout << "\n\t\t10. Undo last event operation" << endl;
        cout << "\n\t\t11. Save and exit"<<endl;
        cout << "\nEnter your choice[1/2/3/4/5/6/7/8/9/10/11]: ";
        cin >> choice;
        switch (choice) {
        case 1:
            s.addStaff();
            s.saveToFile("staff_data.txt");
            cout << ""<<endl;
            system("pause");
            system("cls");
            break;
        case 2: {
            int idToDelete;
            s.displayAllStaffData();
            cout << "\nEnter the ID of the staff to remove: ";
            cin >> idToDelete;
            s.deleteStaff(idToDelete);
            cout << "" << endl;
            system("pause");
            system("cls");
            break;
            }
        case 3: {
        int idToEdit;
        s.displayAllStaffData();
        cout << "\nEnter the ID of the staff to edit: ";
        cin >> idToEdit;
        s.editStaffDetails(idToEdit);
        cout << "" << endl;
        system("pause");
        system("cls");
        break;
}
        case 4:
            s.displayAllStaffData();
            cin.ignore(); // Wait for user to press Enter
            system("pause");
            system("cls");
            break;
        case 5:
            {
                int searchChoice;
                cout << "\n\t\t1. Search by Age" << endl;
                cout << "\t\t2. Search by Height" << endl;
                cout << "\t\t3. Search by Weight" << endl;
                cout << "\nEnter your choice [1/2/3]: ";
                cin >> searchChoice;

                int targetValue;
                switch (searchChoice) {
                    case 1:

                        cout << "Enter the value to search: ";
                        cin >> targetValue;
                        cout << left <<  setw(4) << "ID" << setw(15) << "Name" << setw(7) << "Age" << setw(8) << "Gender"
                        << setw(12) << "Height(cm)" << setw(12) << "Weight(kg)"
                        << setw(15) << "Contact Number(+60)\n";
                        s.binarySearchByAge(targetValue);
                    break;
                    case 2:
                        cout << left <<  setw(4) << "ID" << setw(15) << "Name" << setw(7) << "Age" << setw(8) << "Gender"
                        << setw(12) << "Height(cm)" << setw(12) << "Weight(kg)"
                        << setw(15) << "Contact Number(+60)\n";
                        cout << "Enter the value to search: ";
                        cin >> targetValue;
                        s.binarySearchByHeight(targetValue);
                        break;
                    case 3:
                        cout << left <<  setw(4) << "ID" << setw(15) << "Name" << setw(7) << "Age" << setw(8) << "Gender"
                        << setw(12) << "Height(cm)" << setw(12) << "Weight(kg)"
                        << setw(15) << "Contact Number(+60)\n";
                        cout << "Enter the value to search: ";
                        cin >> targetValue;
                        s.binarySearchByWeight(targetValue);
                        break;
                    default:
                        cout << "Invalid choice for search type." << endl;
                        cout << "Redirecting to Admin Page...\n" << endl;
                            break;
                        }
                    cout << "" << endl;
                    system("pause");
                    system("cls");
                    break;
            }
        case 6:
                eventManager.addEvent();
                cin.ignore(); // Wait for user to press Enter
            system("pause");
            system("cls");
                break;

            case 7:{
                eventManager.displayAllEvents();
                int id;
                cout << "Enter the ID of the event to remove: ";
                cin >> id;
                eventManager.removeEventByID(id);
                cin.ignore(); // Wait for user to press Enter
            system("pause");
            system("cls");
                break;
            }
            case 8: {
                eventManager.displayAllEvents();
                int id;
                cout << "Enter the ID of the event to edit: ";
                cin >> id;
                eventManager.editEventByID(id);
                cin.ignore(); // Wait for user to press Enter
            system("pause");
            system("cls");
                break;
            }
            case 9:{
                eventManager.displayAllEvents();
                bookedEvents.back().accountSummary(bookedEvents);
                cin.ignore(); // Wait for user to press Enter
            system("pause");
            system("cls");
                break;
            }

            case 10:
                eventManager.undoLastOperation();
                cin.ignore(); // Wait for user to press Enter
            system("pause");
            system("cls");
                break;

            case 11:
                s.saveToFile("staff_data.txt");
                eventManager.saveEventsToFile("events.txt");
                cout << "Exiting program.\n";
                cin.ignore(); // Wait for user to press Enter
            system("pause");
            system("cls");
            exitProgram = true;
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        break;
                       }
            }while (choice != 11);
            } while (!exitProgram);
        } else if (choice == 2){

        int enteredId;
        bool validId = false;

        do {
            cout << "Enter your ID: ";
            cin >> enteredId;

            if (isStaffIdValid(enteredId)) {
                validId = true;
            } else {
                cout << "Invalid ID. Try again.\n";
            }
        } while (!validId);
        system("cls");

        queue<User> bookedEvents = User::loadFromFile("bookedevents.txt");
        queue<User> workQueue = User::loadFromFile("events.txt");

        int userChoice;
        do {
        cout<<"========================================================================================================================"<<endl;
        cout<<" "<<endl;
        cout << "                               WELCOME TO Labour Management SYSTEM !!!                                        " << std::endl;
        cout<<" "<<endl;
        cout<<"========================================================================================================================"<<endl;
            cout << "\n\t 1. Book Event"<< endl;
            cout << "\n\t 2. Account Summary\t"<< endl;
            cout << "\n\t 3. Show Available Events\t"<< endl;
            cout << "\n\t 4. Show Previous Booked Event\t"<< endl;
            cout << "\n\t 5. Exit\t"<< endl;
            cout << "\n\tEnter your choice: \t"<< endl;
            cin >> userChoice;

            switch (userChoice) {
                case 1: {
                    bookedEvents.front().showAvailableEvents(workQueue);
                    do {
                        User User(0, "", "", 0, 0, 0, "", "", 0.0, 0);
                        User.bookEvent(bookedEvents, workQueue);

                        char anotherBooking;
                        cout << "Do you want to book another event? (y/n): ";
                        cin >> anotherBooking;

                        if (anotherBooking != 'y' && anotherBooking != 'Y') {
                            break;
                        }
                    } while (true);
                    system("pause");
                    system("cls");
                    break;
                }
                case 2:
                    if (bookedEvents.empty()) {
                        cout << "No events booked yet.\n";
                    } else {
                        bookedEvents.front().accountSummary(bookedEvents);
                    }
                    system("pause");
                    system("cls");
                    break;
                case 3:
                    bookedEvents.front().showAvailableEvents(workQueue);
                    system("pause");
                    system("cls");
                    break;
                case 4:
                    if (!bookedEvents.empty()) {
                        bookedEvents.front().showBookedEvents(bookedEvents);
                    } else {
                        cout << "No events booked yet.\n";
                    }
                    system("pause");
                    system("cls");
                    break;
                case 5:
                    cout << "Exiting user page.\n";
                    system("pause");
                    system("cls");
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (userChoice !=5);
    }else if (choice == 3){
    cout << "Exiting program. Thanks for using TalentLink-Labour Management System\n";
    } else {
    cout << "Invalid choice. Please enter a valid option.\n";
    system("pause");
    system("cls");}
    } while (choice != 3);

    return 0;
}
