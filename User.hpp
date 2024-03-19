// User.hpp
#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>
#include <queue>

using namespace std;

class User {
private:
    int id;
    string eventName;
    string eventDescription;
    int year;
    int month;
    int day;
    string startTime;
    string endTime;
    double salary;
    int userid;
    int userID;

public:
    static void someStaticFunction();
    void someNonStaticFunction();
    User(int id, const string& eventName,
                 const string& eventDescription,
                 int year, int month, int day,
                 const string& startTime, const string& endTime,
                 double salary, int userid)
        : id(id), eventName(eventName), eventDescription(eventDescription),
          year(year), month(month), day(day), startTime(startTime), endTime(endTime),
          salary(salary), userid(userid) {}

    User(int id, const string& eventName,
                 const string& eventDescription,
                 int year, int month, int day,
                 const string& startTime, const string& endTime)
        : id(id), eventName(eventName), eventDescription(eventDescription),
          year(year), month(month), day(day), startTime(startTime), endTime(endTime), salary(0.0) {}


    void bookEvent(queue<User>& bookedEvents, queue<User>& workQueue, int enteredId);
    void accountSummary(queue<User>& bookedEvents) const;
    void showAvailableEvents(const queue<User>& workQueue) const;
    void showBookedEvents(const queue<User>& bookedEvents) const;
    void storeBookingDetails(queue<User>& bookedEvents, const User& bookedEvent);

    string serializeAvailableEvent() const;
    string serializeBookedEvent() const;
    static User deserializeAvailableEvent(const string& data);
    static User deserializeBookedEvent(const string& data);

    static queue<User> loadFromFile(const string& filename);
    void setUserID(int id);
    int getUserID() const;
};

#endif // USER_HPP

