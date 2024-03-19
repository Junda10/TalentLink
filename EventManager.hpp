#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class EventManager {
public:
    void displayEvent(const EventManager& event);
    void saveEventsToFile(const EventManager& newEvent);
    void addEvent();
    void displayAllEvents();
    void saveEventsToFile(const string& filename) const;
    void loadEventsFromFile(const string& filename);
    void removeEventByID(int id);
    void editEventByID(int id);
    void undoLastOperation();

private:
    struct Event {
        int id;
        string eventName;
        string eventDescription;
        int year;
        int month;
        int day;
        int startTime;
        int endTime;
        int salary;
    };
    int id;
        string eventName;
        string eventDescription;
        int year;
        int month;
        int day;
        int startTime;
        int endTime;
        int salary;

    vector<Event> events;
    stack<vector<Event>> undoStack;

    bool isValidTime(int time);
    bool isValidID(const string& input);
    bool isValidAlphabetic(const string& input);
    bool isValidInt(const string& input, int minValue, int maxValue);
    int getValidID();
    string getValidAlphabeticInput(const string& prompt, bool requireDateFormatValidation = false);
    int getValidIntInput(const string& prompt, int minValue, int maxValue);
    void getValidTimeRange(int& startTime, int& endTime);
    void displayEvent(const Event& event);
};

#endif // EVENT_MANAGER_HPP
