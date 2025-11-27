#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Define constants
#define INF INT_MAX
#define num_of_cities 5
#define initial_num_of_flights 5


// Function to clear the screen
void clearScreen() {
    // Use system-specific clear screen command
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Unix-like systems
#endif
}

// Define global variables
int cost[num_of_cities][num_of_cities] = { {0, 4, 3, 9, 8},
                                            {4, 0, 7, INF, 10},
                                            {3, 7, 0, INF, 9},
                                            {9, INF, INF, 0, 16},
                                            {8, INF, 9, INF, 0} };

string cities[num_of_cities] = { "MNL", "TYO", "BKK", "KWT", "SYD" };

// Function to generate random departure time in 12-hour format
void generateDepartureTime(int& departure_hour, int& departure_mins) {
    // Generate random hour between 1 and 12
    departure_hour = rand() % 12 + 1;
    // Generate random minutes between 0 and 59
    departure_mins = rand() % 60;
}

// Class for Flights
class Flights {
public:
    string flight_id;
    int flight_cost;
    string flight_path;
    bool high_demand;

    Flights(int source, int destination, bool demand) : high_demand(demand) {
        flight_id = flight_id_generator();
        flight_cost = dijkstra(source, destination);
        flight_path = pathing(source, destination);
    }

    static bool compare_sort(const Flights& a, const Flights& b) {
        return a.flight_cost < b.flight_cost;
    }

private:
    string flight_id_generator() {
        string id;
        random_device rand;
        mt19937 gen(rand());
        uniform_int_distribution<> alpha(65, 90);
        uniform_int_distribution<> numeric(0, 9);
        for (int i = 0; i < 2; i++) {
            id += static_cast<char>(alpha(gen));
        }
        for (int i = 0; i < 3; i++) {
            id += to_string(numeric(gen));
        }
        return id;
    }

    int dijkstra(int source, int destination) {
        vector<int> dist(num_of_cities, INF);
        vector<int> parent(num_of_cities, -1);
        vector<bool> visited(num_of_cities, false);

        dist[source] = 0;

        for (int i = 0; i < num_of_cities; i++) {
            int minDist = INF;
            int minIndex;

            for (int j = 0; j < num_of_cities; j++) {
                if (!visited[j] && dist[j] <= minDist) {
                    minDist = dist[j];
                    minIndex = j;
                }
            }

            visited[minIndex] = true;

            for (int j = 0; j < num_of_cities; j++) {
                if (!visited[j] && cost[minIndex][j] != INF && dist[minIndex] + cost[minIndex][j] < dist[j]) {
                    dist[j] = dist[minIndex] + cost[minIndex][j];
                    parent[j] = minIndex;
                }
            }
        }
        return dist[destination];
    }

    string pathing(int source, int destination) {
        string path;
        path = cities[source] + " -> " + cities[destination];
        return path;
    }
};

// Class for Aircraft
class Aircraft {
public:
    string aircraft_id;
    int maintenance;

    Aircraft(string id, int main) : aircraft_id(id), maintenance(main) {};

    static void initialize_aircraft(string filename, vector<Aircraft>& a) {
        string id;
        int main;
        ifstream input(filename);
        if (!input) {
            cerr << "Error Opening txt file!";
        }
        string line;
        getline(input, line);
        while (input >> id >> main) {
            a.push_back(Aircraft(id, main));
        }
    }
};

// Class for Crew
class Crew {
public:
    string crew_id;
    string crew_type;
    bool available;

    Crew(string type) : crew_type(type) {
        crew_id = generate_crew_id(type);
        available = rand() % 100 < 50 + 3; // Approximately 50% chances of being unavailable + 3 just to avoid that there will be no pilots at all and airline wont be functional

        // Check if the crew text file exists
        if (!fileExists("crew_members.txt")) {
            // If it doesn't exist, create it
            ofstream createFile("crew_members.txt");
            if (!createFile) {
                cerr << "Error creating crew_members.txt!" << endl;
                exit(EXIT_FAILURE);
            } else {
                createFile.close();
            }
        }

        // Write the generated crew member to the text file
        ofstream outputFile("crew_members.txt", ios::app);
        if (outputFile.is_open()) {
            outputFile << "Crew ID: " << crew_id << "\tCrew Type: " << crew_type << "\tAvailable: " << (available ? "Yes" : "No") << endl;
            outputFile.close();
        } else {
            cerr << "Unable to open file for writing!" << endl;
            exit(EXIT_FAILURE);
        }
    }

private:
    string generate_crew_id(string type) {
        string id;
        random_device rand;
        mt19937 gen(rand());
        uniform_int_distribution<> numeric(1000, 9999);
        if (type == "Pilot")
            id = "P";
        else if (type == "Co-Pilot")
            id = "CP";
        else if (type == "Flight Attendant")
            id = "FA";
        id += to_string(numeric(gen));
        return id;
    }

    bool fileExists(const std::string& filename) {
        ifstream file(filename.c_str());
        return file.good();
    }
};

// Class for Schedule
class Schedule {
public:
    vector<Flights> flight;
    vector<Aircraft> aircraft;

    Schedule(vector<Flights> flight, vector<Aircraft> aircraft)
        : flight(flight), aircraft(aircraft) {
    }
};

void printCrewMembers(const vector<Crew>& crewList, const string& crewType) {
    
    // Print crew members
    cout << setw(10) << "Crew ID" << "   ";
    cout << setw(12) << "Crew Type" << "   ";
    cout << setw(8) << "Available" << endl;

    for (const auto& crewMember : crewList) {
        if (crewMember.crew_type == crewType) {
            cout << setw(10) << crewMember.crew_id << "   ";
            cout << setw(12) << crewMember.crew_type << "   ";
            cout << setw(3) << (crewMember.available ? "Yes" : "No") << endl;

        }
    }
}


// Function to merge sort crew members by availability
vector<Crew> mergeSortCrewMembers(vector<Crew>& crewList) {
    // Base case: If the list has only one crew member, return the list
    if (crewList.size() <= 1) {
        return crewList;
    }

    // Divide the crew list into two halves
    int mid = crewList.size() / 2;
    vector<Crew> leftHalf(crewList.begin(), crewList.begin() + mid);
    vector<Crew> rightHalf(crewList.begin() + mid, crewList.end());

    // Recursively sort each half
    leftHalf = mergeSortCrewMembers(leftHalf);
    rightHalf = mergeSortCrewMembers(rightHalf);

    // Merge the sorted halves
    vector<Crew> sortedList;
    auto leftIter = leftHalf.begin();
    auto rightIter = rightHalf.begin();
    while (leftIter != leftHalf.end() && rightIter != rightHalf.end()) {
        if (leftIter->available < rightIter->available) {
            sortedList.push_back(*leftIter);
            ++leftIter;
        }
        else {
            sortedList.push_back(*rightIter);
            ++rightIter;
        }
    }
    sortedList.insert(sortedList.end(), leftIter, leftHalf.end());
    sortedList.insert(sortedList.end(), rightIter, rightHalf.end());

    return sortedList;
}

// Function to merge sort flights by departure time
vector<Flights> mergeSortFlights(vector<Flights>& flightList) {
    // Implement merge sort algorithm for flights
    // Sort flights by departure time
    sort(flightList.begin(), flightList.end(), [](const Flights& a, const Flights& b) {
        return a.flight_cost < b.flight_cost;
        });
    return flightList;
}

// Function to assign crew members to flights based on flight priorities
void assignCrewToFlights(vector<Crew>& crewList, vector<Flights>& flightList) {
    // Merge sort crew members by availability
    crewList = mergeSortCrewMembers(crewList);

    // Iterate through flights
    for (int i = 0; i < flightList.size(); ++i) {
        // Check if there are available crew members
        if (crewList.empty() || all_of(crewList.begin(), crewList.end(), [](const Crew& crew) {
            return !crew.available;
            })) {
            cout << "No available crew members for flight " << flightList[i].flight_id << endl;
            continue; // Skip to the next flight
        }

        // Find the first available crew member
        auto availableCrew = find_if(crewList.begin(), crewList.end(), [](const Crew& crew) {
            return crew.available;
            });

        if (availableCrew != crewList.end()) {
            // Assign the crew member to the flight
            cout << "Assigned crew member " << availableCrew->crew_id << " to flight " << flightList[i].flight_id << endl;
            // Mark the crew member as unavailable
            availableCrew->available = false;
        }
        else {
            // If no available crew members found, pull crew members from later flights
            cout << "No available crew members for flight " << flightList[i].flight_id << ". Pulling crew members from later flights." << endl;
            // Iterate through later flights
            for (int j = i + 1; j < flightList.size(); ++j) {
                auto availableCrewLaterFlight = find_if(crewList.begin(), crewList.end(), [](const Crew& crew) {
                    return crew.available;
                    });
                if (availableCrewLaterFlight != crewList.end()) {
                    // Assign the crew member to the current flight
                    cout << "Assigned crew member " << availableCrewLaterFlight->crew_id << " to flight " << flightList[i].flight_id << endl;
                    // Mark the crew member as unavailable
                    availableCrewLaterFlight->available = false;
                    break; // Move to the next flight
                }
            }
        }
    }
}




int main() {

    srand(time(nullptr)); // Seed the random number generator

    int o;
    int source, booking, yn;

    vector<vector<string>> crew;

    string choice;
    vector<Flights> depart;
    vector<Flights> arrive;
    vector<Schedule> sched;
    vector<Schedule> sched2;
    vector<Aircraft> a;
    vector<Crew> crewList; // Add vector to store crew members

    // Populate crewList vector with crew members
    for (int i = 0; i < 5; ++i) {
        crewList.push_back(Crew("Pilot"));
    }
    for (int i = 0; i < 5; ++i) {
        crewList.push_back(Crew("Co-Pilot"));
    }
    for (int i = 0; i < 40; ++i) {
        crewList.push_back(Crew("Flight Attendant"));
    }

    Aircraft::initialize_aircraft("aircrafts.txt", a);
    cout << "Hadji Inc. Flight Scheduler\n\n";

    // Start the main loop using a do-while loop
    do {
        // Prompt user to choose an option
        cout << "Choose an option:\n"
            << "[1]. Airport\n"
            << "[2]. Crew\n"
            << "[3]. Crew Assignment\n"
            << "[4]. Exit\n";
        cin >> o;

        //clearScreen();

        switch (o) {
        case 1:
            // Airport option implementation
            cout << "Choose an Airport: \n";
            cout << "[1] MNL (Manila)\n"
                << "[2] TYO (Tokyo)\n"
                << "[3] BKK (Bangkok)\n"
                << "[4] KWT (Kuwait)\n"
                << "[5] SYD (Sydney)\n";
            cin >> choice;

            if (choice == "1")
                source = 0;
            else if (choice == "2")
                source = 1;
            else if (choice == "3")
                source = 2;
            else if (choice == "4")
                source = 3;
            else if (choice == "5")
                source = 4;

            cout << "Enter Demand for each flight: \n";
            cout << "[0] NO DEMAND\n";
            cout << "[1] HIGH DEMAND\n";

            for (int i = 0; i < initial_num_of_flights; i++) {
                if (source != i) {
                    cout << cities[source] + " -> " + cities[i] << endl;
                    do {
                        cout << ">";
                        cin >> yn;
                        if (yn != 0 && yn != 1) {
                            cout << "Invalid choice! Please choose between 0 (NO DEMAND) or 1 (HIGH DEMAND)." << endl;
                        }
                    } while (yn != 0 && yn != 1);

                    if (yn == 1) {
                        depart.push_back(Flights(source, i, true));
                        arrive.push_back(Flights(i, source, true));
                    }
                    else {
                        depart.push_back(Flights(source, i, false));
                        arrive.push_back(Flights(i, source, false));
                    }
                }
            }

            sort(depart.begin(), depart.end(), Flights::compare_sort);
            sort(arrive.begin(), arrive.end(), Flights::compare_sort);

            // Random departure time generation
            int departure_hour, departure_mins;
            generateDepartureTime(departure_hour, departure_mins);

            // Create Schedule objects
            for (int i = 0; i < depart.size(); i++) {
                sched.push_back(Schedule(depart, a));
            }

            for (int i = 0; i < arrive.size(); i++) {
                sched2.push_back(Schedule(arrive, a));
            }

            cout << "FLIGHT ORDER \t| FLIGHT ID \t| FLIGHT PATH \t| DEPARTURE TIME \t| ARRIVAL TIME  | ASSIGNED AIRCRAFT \n";
            cout << setfill('-') << setw(17) << "|" << setfill('-') << setw(72) << "|" << setfill('-') << setw(20) << " " << endl;
            for (int i = 0; i < depart.size(); i++) {
                // Calculate arrival hour based on departure hour and flight cost
                int flight_cost = sched[i].flight[i].flight_cost;
                int arrival_hour = (departure_hour + flight_cost) % 24;
                int arrival_mins = departure_mins;

                // Adjust arrival time if it goes to the next day
                if (arrival_hour < departure_hour) {
                    arrival_hour += 24;
                }

                cout << i << "\t\t"
                    << "| " << sched[i].flight[i].flight_id << "\t\t|" << sched[i].flight[i].flight_path << "\t|" << setfill('0') << setw(2) << departure_hour << ":" << setfill('0') << setw(2) << departure_mins << "\t\t\t| " << setfill('0') << setw(2) << arrival_hour << ":" << setfill('0') << setw(2) << arrival_mins << " \t|" << sched[i].aircraft[i].aircraft_id << endl;

                // Increment departure hour for the next flight
                departure_hour = (departure_hour + 1) % 24;
            }

            // Clear vectors for next iteration
            depart.clear();
            arrive.clear();
            sched.clear();
            sched2.clear();
      
            break;
        case 2:
            // Crew option implementation
            cout << "==CREW MEMBERS==" << endl;
            cout << "[PILOTS]" << endl;
            printCrewMembers(crewList, "Pilot");
            cout << endl;

            cout << "[CO-PILOTS]" << endl;
            printCrewMembers(crewList, "Co-Pilot");
            cout << endl;

            cout << "[FLIGHT ATTENDANTS]" << endl;
            printCrewMembers(crewList, "Flight Attendant");
            cout << endl;
            break;
        case 3:
            // Crew Assignment option implementation
            cout << "Crew Assignment:" << endl;
            // Merge sort crew members by availability
            crewList = mergeSortCrewMembers(crewList);
            // Merge sort flights by departure time
            depart = mergeSortFlights(depart);
            // Assign crew members to flights
            assignCrewToFlights(crewList, depart);
            break;
        case 4:
            cout << "\nThank You";
            break; // Exit the loop
        default:
            cout << "Invalid option. Please choose again.\n";
            break;
        }
    } while (o != 4);

    return 0;
}
