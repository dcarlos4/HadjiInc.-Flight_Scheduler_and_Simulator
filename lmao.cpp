#include <iostream>
#include <vector>
#include <string>

class Flight {
public:
    std::string flight_id;
    int flight_hours;

    // Constructor
    Flight(const std::string& id, int hours) : flight_id(id), flight_hours(hours) {}
};

class Aircraft {
public:
    std::string aircraft_id;
    int capacity;

    // Constructor
    Aircraft(const std::string& id, int cap) : aircraft_id(id), capacity(cap) {}
};

class Schedule {
public:
    Flight flight;
    Aircraft aircraft;

    // Constructor
    Schedule(const Flight& f, const Aircraft& a) : flight(f), aircraft(a) {}
};

int main() {
    std::vector<Flight> flights;
    std::vector<Aircraft> aircrafts;
    std::vector<Schedule> schedules;

    // Add a flight and an aircraft to the vectors
    flights.push_back(Flight("AB123", 5));
    aircrafts.push_back(Aircraft("AC456", 200));

    // Create a schedule and add it to the vector
    schedules.push_back(Schedule(flights[0], aircrafts[0]));

    // Access flight, aircraft, and schedule data
    for (const Schedule& schedule : schedules) {
        std::cout << "Flight ID: " << schedule.flight.flight_id 
                  << ", Flight Hours: " << schedule.flight.flight_hours 
                  << ", Aircraft ID: " << schedule.aircraft.aircraft_id 
                  << ", Capacity: " << schedule.aircraft.capacity << std::endl;
    }

    return 0;
}
