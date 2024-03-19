// staff.hpp

#ifndef STAFF_HPP
#define STAFF_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>

class Staff {
private:
    int id;
    std::string name;
    int age;
    std::string gender;
    int height;
    int weight;
    int contact_number;
    std::vector<Staff> staffList;

public:
    template <typename T>
    bool binarySearch(T target, int (Staff::*getAttribute)() const, const std::string& attributeName) const;

    void displayStaffDetails() const;

    void enterNewDetails();

    int getID() const;

    const std::string& getName() const;

    int getAge() const;

    const std::string& getGender() const;

    int getHeight() const;

    int getWeight() const;

    int getContactNumber() const;

    Staff();

    Staff(int _id, const std::string& _name, int _age, const std::string& _gender,
          int _height, int _weight, int _contact_number);

    void addNewStaff(const Staff& newStaff);

    void addStaff();

    bool deleteStaff(int staffId);

    void displayAllStaffData();

    bool editStaffDetails(int staffId);

    bool binarySearchByAge(int targetAge) const;

    bool binarySearchByHeight(int targetHeight) const;

    bool binarySearchByWeight(int targetWeight) const;

    bool saveToFile(const std::string & filename) const;
};

#endif // STAFF_HPP
