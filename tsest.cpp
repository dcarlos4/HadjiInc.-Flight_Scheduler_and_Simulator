#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;

#define INF INT_MAX
#define num_of_cities 5
#define initial_num_of_flights 5

int cost[num_of_cities][num_of_cities] = {{0, 4, 3, 9, 8},
                                          {4, 0, 7, INF, 10},
                                          {3, 7, 0, INF, 9},
                                          {9, INF, INF, 0, 16},
                                          {8, INF, 9, INF, 0}};

string cities[num_of_cities] = {"MNL", "TYO", "BKK", "KWT", "SYD"};

class Flights
{
public:
    string flight_id;
    int flight_cost;
    string flight_path;
    bool high_demand;

    Flights(int source, int destination, bool demand) : high_demand(demand)
    {
        flight_id = flight_id_generator();
        flight_cost = dijkstra(source, destination);
        flight_path = pathing(source, destination);
    }
    static bool compare_sort(const Flights &a, const Flights &b)
    {
        return a.flight_cost < b.flight_cost;
    }

private:
    string flight_id_generator()
    {
        string id;
        random_device rand;
        mt19937 gen(rand());
        uniform_int_distribution<> alpha(65, 90);
        uniform_int_distribution<> numeric(0, 9);
        for (int i = 0; i < 2; i++)
        {
            id += static_cast<char>(alpha(gen));
        }
        for (int i = 0; i < 3; i++)
        {
            id += std::to_string(numeric(gen));
        }
        return id;
    }

    int dijkstra(int source, int destination)
    {
        vector<int> dist(num_of_cities, INF);
        vector<int> parent(num_of_cities, -1);
        vector<bool> visited(num_of_cities, false);

        dist[source] = 0;

        for (int i = 0; i < num_of_cities; i++)
        {
            int minDist = INF;
            int minIndex;

            for (int j = 0; j < num_of_cities; j++)
            {
                if (!visited[j] && dist[j] <= minDist)
                {
                    minDist = dist[j];
                    minIndex = j;
                }
            }

            visited[minIndex] = true;

            for (int j = 0; j < num_of_cities; j++)
            {
                if (!visited[j] && cost[minIndex][j] != INF && dist[minIndex] + cost[minIndex][j] < dist[j])
                {
                    dist[j] = dist[minIndex] + cost[minIndex][j];
                    parent[j] = minIndex;
                }
            }
        }
        return dist[destination];
    }

    string pathing(int source, int destination)
    {
        string path;
        path = cities[source] + " -> " + cities[destination];
        return path;
    }
};

class Aircraft
{
public:
    string aircraft_id;
    int maintenance;
    int planeHours;

    Aircraft(string id, int main) : aircraft_id(id), maintenance(main), planeHours(0){};

    static void initialize_aircraft(string filename, vector<Aircraft> &a)
    {
        string id;
        int cap, main;
        ifstream input(filename);
        if (!input)
        {
            cerr << "Error Opening aircrafts.txt!";
        }
        string line;
        getline(input, line);
        while (input >> id >> main)
        {
            a.push_back(Aircraft(id, main));
        }
    }
    void setPlaneHours(int hours)
    { // setter ng planeHours for calculations
        this->planeHours = this->planeHours + hours;
    }
    int getPlaneHours()
    { // getter ng planeHours for calculations
        return this->planeHours;
    }
    void doneMaintenance()
    { // kada after maintenance
        this->planeHours = 0;
    }
};

struct CrewMember
{
    std::string name;
    bool available;

    CrewMember(const std::string &n, bool avail) : name(n), available(avail) {}
};
class Crew
{
public:
    std::vector<CrewMember> pilots;
    std::vector<CrewMember> copilots;
    std::vector<CrewMember> flight_attendants;

    // Constructor to populate the crew members and availability
    Crew()
    {
        // Initialize random number generator
        srand(time(nullptr));

        // Populate pilots and their availability
        populateWithRandomAvailability(pilots, {"Cheryl Gentry", "Louisa Holmes", "Layton Rubio", "Kristina Swanson", "Rafferty Frazier",
                                                "Lillie Stein", "Audrey Hart", "Isobel Bridges", "Gerald Frank", "Haseeb House",
                                                "Eshal Callahan", "Ivan Le", "Callum Myers", "Katrina Nichols", "Bryony Jarvis",
                                                "Brett Hendrix", "Oliver Alexander", "Shania Saunders", "Lilia Avila", "Muhammed Dixon"});

        // Populate copilots and their availability
        populateWithRandomAvailability(copilots, {"Rosie Chan", "Alyssia Aguirre", "Tom Bender", "Priya Irwin", "Nikodem Berry",
                                                  "Frankie Donovan", "Penny Lamb", "Jason Macias", "Ronnie Scott", "Noel Cochran",
                                                  "Siena Schultz", "Jessie Gardner", "Anais Everett", "Lulu Shepherd", "Monty Boyd",
                                                  "Soraya O'Sullivan", "Beatrix Evans", "Angela Shepard", "Gabrielle Glover", "Aleena Huffman"});

        // Populate flight attendants and their availability
        populateWithRandomAvailability(flight_attendants, {"Ezekiel Carney", "Abdulrahman Chan", "Victoria Newman", "Saffron Lowe", "Jacques Pineda",
                                                           "Sachin Meyers", "Antonia Jimenez", "Cecil Wilkinson", "Andrew Oconnor", "Honey Randall",
                                                           "Francesca Bowen", "Mitchell Larsen", "Carmen Walker", "Neve Lozano", "Yusra Ryan",
                                                           "Ali Osborn", "Kobi Santiago", "Francesco Prince", "Ebony Everett", "Hope Morrison",
                                                           "Chelsea Doyle", "Amirah Gaines", "Suzanne Bright", "Antony Hatfield", "Lois Frost",
                                                           "Habiba Boyd", "Rhiannon Payne", "Felicity Blanchard", "Harmony Hutchinson", "Gethin Todd",
                                                           "Ashleigh Pittman", "Sahil Rios", "Tegan Burgess", "Ilyas Horn", "Ronald Diaz", "Corey Lynn",
                                                           "Bartosz Edwards", "Axel Potts", "Will Carroll", "Kamil Villegas"});

        // Sort availability arrays with true being the first
        mergeSortAvailability(pilots);
        mergeSortAvailability(copilots);
        mergeSortAvailability(flight_attendants);
    }

private:
    // Helper function to populate crew members and availability
    void populateWithRandomAvailability(std::vector<CrewMember> &crew,
                                        const std::vector<std::string> &names)
    {
        // Populate crew members
        for (const auto &name : names)
        {
            // Determine availability randomly
            bool avail = (rand() % 2 == 0); // 50% chance of being available
            crew.emplace_back(name, avail);
        }
    }

    // Helper function to merge sort availability with true being the first
    void mergeSortAvailability(std::vector<CrewMember> &crew)
    {
        // Implement merge sort
        if (crew.size() <= 1)
            return;

        std::vector<CrewMember> left_crew, right_crew;

        size_t mid = crew.size() / 2;

        for (size_t j = 0; j < mid; ++j)
        {
            left_crew.push_back(crew[j]);
        }

        for (size_t j = mid; j < crew.size(); ++j)
        {
            right_crew.push_back(crew[j]);
        }

        mergeSortAvailability(left_crew);
        mergeSortAvailability(right_crew);

        crew.clear();

        size_t left_index = 0, right_index = 0;

        while (left_index < left_crew.size() && right_index < right_crew.size())
        {
            if (left_crew[left_index].available)
            {
                crew.push_back(left_crew[left_index]);
                left_index++;
            }
            else
            {
                crew.push_back(right_crew[right_index]);
                right_index++;
            }
        }

        while (left_index < left_crew.size())
        {
            crew.push_back(left_crew[left_index]);
            left_index++;
        }

        while (right_index < right_crew.size())
        {
            crew.push_back(right_crew[right_index]);
            right_index++;
        }
    }
};

class Schedule
{
public:
    vector<Flights> flight;
    vector<Aircraft> aircraft;

    Schedule(vector<Flights> flight, vector<Aircraft> aircraft)
        : flight(flight), aircraft(aircraft)
    {
    }
};

void simulation(vector<Schedule> &s1, vector<Schedule> &s2, vector<Aircraft> &ac, vector<Flights> &depart, vector<Flights> &arrive)
{

    for (int hour = 0; hour < 24; hour++)
    {
        system("cls");
        cout << setfill('0') << setw(2) << hour << ":"
             << "00\n\n";
        int departure_hour[depart.size()] = {0};
        int departure_mins[depart.size()] = {0};
        int arrival_hour[depart.size()] = {0};
        int arrival_mins[depart.size()] = {0};
        cout << "DEPARTURES\n\n";
        cout << "FLIGHT ORDER \t| FLIGHT ID \t| FLIGHT PATH \t| DEPARTURE TIME \t| ARRIVAL TIME \t| ASSIGNED AIRCRAFT \t| STATUS \n";
        cout << setfill('-') << setw(17) << "|" << setfill('-') << setw(72) << "|" << setfill('-') << setw(23) << " "
             << "|" << setfill('-') << setw(15) << " " << endl;

        for (int i = 0; i < depart.size(); i++)
        {
            arrival_hour[i] = (departure_hour[i] + s1[i].flight[i].flight_cost) % 24;
            int planehour = 2 * s1[i].flight[i].flight_cost;
            ac[i].setPlaneHours(planehour);
            if (i > 0)
                departure_hour[i] = (departure_hour[i - 1] + 1) % 24;

            cout << i + 1 << "\t\t"
                 << "| " << s1[i].flight[i].flight_id << "\t\t|" << s1[i].flight[i].flight_path << "\t|" << setfill('0') << setw(2) << departure_hour[i] << ":" << setfill('0') << setw(2) << departure_mins[i] << "\t\t\t| " << setfill('0') << setw(2) << arrival_hour[i] << ":" << setfill('0') << setw(2) << arrival_mins[i] << "\t\t|" << s1[i].aircraft[i].aircraft_id;
            if (hour == departure_hour[i])
                cout << "\t\t\t    Departed";
            else if (hour == arrival_hour[i])
                cout << "\t\t\t    Arrived";
            else
                cout << "\t\t\t      -  ";

            cout << endl;
        }

        for (int i = 0; i < depart.size(); i++)
        {
            departure_hour[i] = arrival_hour[i];
            departure_mins[i] = arrival_mins[i];
        }

        arrival_hour[depart.size()] = 0;
        arrival_mins[depart.size()] = 0;
        cout << endl
             << endl;

        cout << "ARRIVALS\n";
        cout << "FLIGHT ORDER \t| FLIGHT ID \t| FLIGHT PATH \t| DEPARTURE TIME \t| ARRIVAL TIME \t| ASSIGNED AIRCRAFT \t| STATUS \n";
        cout << setfill('-') << setw(17) << "|" << setfill('-') << setw(72) << "|" << setfill('-') << setw(23) << " "
             << "|" << setfill('-') << setw(15) << " " << endl;
        for (int i = 0; i < arrive.size(); i++)
        {
            arrival_hour[i] = (departure_hour[i] + s2[i].flight[i].flight_cost + 1) % 24;

            if (hour == 1 + departure_hour[i])
            {
                cout << i + 1 << "\t\t"
                     << "| " << s1[i].flight[i].flight_id << "\t\t|" << s1[i].flight[i].flight_path << "\t|" << setfill('0') << setw(2) << departure_hour[i] + 1 << ":" << setfill('0') << setw(2) << departure_mins[i] << "\t\t\t| " << setfill('0') << setw(2) << arrival_hour[i] << ":" << setfill('0') << setw(2) << arrival_mins[i] << "\t\t|" << s1[i].aircraft[i].aircraft_id << "\t\t\t    Departed";
            }

            else if (hour == 1 + arrival_hour[i] && departure_hour[i] < arrival_hour[i])
            {
                cout << i + 1 << "\t\t"
                     << "| " << s1[i].flight[i].flight_id << "\t\t|" << s1[i].flight[i].flight_path << "\t|" << setfill('0') << setw(2) << departure_hour[i] + 1 << ":" << setfill('0') << setw(2) << departure_mins[i] << "\t\t\t| " << setfill('0') << setw(2) << arrival_hour[i] << ":" << setfill('0') << setw(2) << arrival_mins[i] << "\t\t|" << s1[i].aircraft[i].aircraft_id << "\t\t\t    Arrived";
            }

            else
            {
                cout << i + 1 << "\t\t"
                     << "| " << s1[i].flight[i].flight_id << "\t\t|" << s1[i].flight[i].flight_path << "\t|" << setfill('0') << setw(2) << departure_hour[i] + 1 << ":" << setfill('0') << setw(2) << departure_mins[i] << "\t\t\t| " << setfill('0') << setw(2) << arrival_hour[i] << ":" << setfill('0') << setw(2) << arrival_mins[i] << "\t\t|" << s1[i].aircraft[i].aircraft_id << "\t\t\t      -  ";
            }

            cout << endl;
        }
        cout << endl;

        for (int i = 0; i < ac.size(); i++)
        {
            ac[i].planeHours = ac[i].getPlaneHours();
            if (ac[i].planeHours > ac[i].maintenance && hour == ac[i].planeHours)
            {
                cout << "Aircraft " << ac[i].aircraft_id << " has undergone maintenance at time " << arrival_hour[i] << ":00" << endl;
                ac[i].doneMaintenance();
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void processAirport(int source, vector<Flights> &depart, vector<Flights> &arrive, vector<Aircraft> &a)
{
    int booking, yn;
    vector<Schedule> sched;
    vector<Schedule> sched2;
    cout << "Enter Demand for each flight: \n";
    for (int i = 0; i < initial_num_of_flights; i++)
    {
        if (source != i)
        {
            cout << cities[source] + " -> " + cities[i] << endl;
            cout << ">";
            cin >> yn;
            if (yn == 1)
            {
                depart.push_back(Flights(source, i, true));
                arrive.push_back(Flights(i, source, true));
            }
            else
            {
                depart.push_back(Flights(source, i, false));
                arrive.push_back(Flights(i, source, false));
            }
        }
    }

    sort(depart.begin(), depart.end(), Flights::compare_sort);
    sort(arrive.begin(), arrive.end(), Flights::compare_sort);

    vector<Flights> high_demand_flights;
    vector<Flights> high_demand_flights2;

    // Move high-demand flights to the front of the depart vector, prioritizing by flight cost
    for (int i = depart.size() - 1; i >= 0; i--)
    {
        if (depart[i].high_demand)
        {
            high_demand_flights.push_back(depart[i]); // Store high-demand flight
            depart.erase(depart.begin() + i);         // Remove high-demand flight from its original position
        }
    }
    // Sort high-demand flights by flight cost
    sort(high_demand_flights.begin(), high_demand_flights.end(), Flights::compare_sort);
    // Place sorted high-demand flights at the beginning of the depart vector
    for (int i = high_demand_flights.size() - 1; i >= 0; i--)
    {
        depart.insert(depart.begin(), high_demand_flights[i]);
    }
    ////////////////////////
    for (int i = arrive.size() - 1; i >= 0; i--)
    {
        if (arrive[i].high_demand)
        {
            high_demand_flights2.push_back(arrive[i]); // Store high-demand flight
            arrive.erase(arrive.begin() + i);          // Remove high-demand flight from its original position
        }
    }
    // Sort high-demand flights by flight cost
    sort(high_demand_flights2.begin(), high_demand_flights2.end(), Flights::compare_sort);
    // Place sorted high-demand flights at the beginning of the depart vector
    for (int i = high_demand_flights2.size() - 1; i >= 0; i--)
    {
        arrive.insert(arrive.begin(), high_demand_flights2[i]);
    }

    /////////////////////////////
    for (int i = 0; i < depart.size(); i++)
        sched.push_back(Schedule(depart, a));

    for (int i = 0; i < arrive.size(); i++)
        sched2.push_back(Schedule(arrive, a));

    int departure_hour[depart.size()] = {0};
    int departure_mins[depart.size()] = {0};
    int arrival_hour[depart.size()] = {0};
    int arrival_mins[depart.size()] = {0};
    cout << "DEPARTURES\n\n";
    cout << "FLIGHT ORDER \t| FLIGHT ID \t| FLIGHT PATH \t| DEPARTURE TIME \t| ARRIVAL TIME \t| ASSIGNED AIRCRAFT \n";
    cout << setfill('-') << setw(17) << "|" << setfill('-') << setw(72) << "|" << setfill('-') << setw(20) << " " << endl;

    for (int i = 0; i < depart.size(); i++)
    {
        int planehour = 2 * sched[i].flight[i].flight_cost;
        a[i].setPlaneHours(planehour);
        arrival_hour[i] = (departure_hour[i] + sched[i].flight[i].flight_cost) % 24;
        if (i > 0)
            departure_hour[i] = (departure_hour[i - 1] + 1) % 24;

        cout << i + 1 << "\t\t"
             << "| " << sched[i].flight[i].flight_id << "\t\t|" << sched[i].flight[i].flight_path << "\t|" << setfill('0') << setw(2) << departure_hour[i] << ":" << setfill('0') << setw(2) << departure_mins[i] << "\t\t\t| " << setfill('0') << setw(2) << arrival_hour[i] << ":" << setfill('0') << setw(2) << arrival_mins[i] << "\t\t|" << sched[i].aircraft[i].aircraft_id << endl;
    }

    for (int i = 0; i < depart.size(); i++)
    {
        departure_hour[i] = arrival_hour[i];
        departure_mins[i] = arrival_mins[i];
    }

    arrival_hour[depart.size()] = 0;
    arrival_mins[depart.size()] = 0;
    cout << endl
         << endl;

    cout << "ARRIVALS\n";
    cout << "FLIGHT ORDER \t| FLIGHT ID \t| FLIGHT PATH \t| DEPARTURE TIME \t| ARRIVAL TIME \t| ASSIGNED AIRCRAFT \n";
    cout << setfill('-') << setw(17) << "|" << setfill('-') << setw(72) << "|" << setfill('-') << setw(20) << " " << endl;
    for (int i = 0; i < arrive.size(); i++)
    {
        arrival_hour[i] = (departure_hour[i] + sched2[i].flight[i].flight_cost + 1) % 24;

        cout << i + 1 << "\t\t"
             << "| " << sched2[i].flight[i].flight_id << "\t\t|" << sched2[i].flight[i].flight_path << "\t|" << setfill('0') << setw(2) << departure_hour[i] + 1 << ":" << setfill('0') << setw(2) << departure_mins[i] << "\t\t\t| " << setfill('0') << setw(2) << arrival_hour[i] << ":" << setfill('0') << setw(2) << arrival_mins[i] << "\t\t|" << sched2[i].aircraft[i].aircraft_id << endl;
    }
    cout << endl;
    for (int i = 0; i < a.size(); i++)
    {

        a[i].planeHours = a[i].getPlaneHours();

        if (a[i].planeHours >= a[i].maintenance)
        {
            cout << "Aircraft " << a[i].aircraft_id << " has undergone maintenance at time " << arrival_hour[i] << ":00" << endl;
            a[i].doneMaintenance();
        }
    }

    int c;
    while (true)
    {

        cout << "\n< Back - 1                              Simulation - 2\n";
        cout << ">";
        cin >> c;
        if (c == 1)
        {
            sched.clear();
            depart.clear();
            arrive.clear();
            for (int i = 0; i < a.size(); i++)
            {

                a[i].setPlaneHours(0);
            }
            return;
        }
        else if (c == 2)
        {
            simulation(sched, sched2, a, depart, arrive);
        }
        else
        {
            cout << "\nInvalid Input!\n";
        }
    }
}

void crew_menu(vector<Aircraft> &a)
{
    Crew crew;
    vector<vector<string>> fleet747(a.size(), vector<string>(8));
    vector<vector<string>> fleet330(a.size(), vector<string>(7)); // Initialize fleet747 with 8 columns

    // Populate pilots for fleet747 747 aircraft
    int fa_count = 2;
    for (int i = 0; i < a.size(); i++)
    {

        int len = a[i].aircraft_id.length();
        string type = a[i].aircraft_id.substr(len - 3, 3);
        if (type == "747")
        {
            // Assign crew members to the fleet747 vector
            fleet747[i][0] = crew.pilots[i].name;
            fleet747[i][1] = crew.copilots[i].name;
            for (int j = 2; j < 8; j++)
            {
                fleet747[i][j] = crew.flight_attendants[fa_count].name;
                fa_count++;
            }
        }
        else if (type == "330")
        {
            fleet330[i][0] = crew.pilots[i].name;
            fleet330[i][1] = crew.copilots[i].name;
            for (int j = 2; j < 7; j++)
            {
                fleet330[i][j] = crew.flight_attendants[fa_count].name;
                fa_count++;
            }
        }
    }

    for (int i = 0; i < a.size(); i++)
    {
        int len = a[i].aircraft_id.length();
        string type = a[i].aircraft_id.substr(len - 3, 3);
        cout << a[i].aircraft_id << " \n";
        if (type == "747")
        {

            cout << "Pilot: " << fleet747[i][0] << endl;
            cout << "Co-pilot: " << fleet747[i][1] << endl;
            cout << "Flight Attendants: ";
            for (int j = 2; j < 8; j++)
            {
                cout << fleet747[i][j] << ", ";
            }
        }
        else if (type == "330")
        {
            cout << "Pilot: " << fleet330[i][0] << endl;
            cout << "Co-pilot: " << fleet330[i][1] << endl;
            cout << "Flight Attendants: ";
            for (int j = 2; j < 7; j++)
            {
                cout << fleet330[i][j] << ", ";
            }
        }
        cout << endl
             << endl;
    }
}

int main()
{
    int o;
    int source;

    vector<vector<string>> crew;

    string choice;
    vector<Flights> depart;
    vector<Flights> arrive;
    vector<Aircraft> a;

    Aircraft::initialize_aircraft("aircrafts.txt", a);
    while (true)
    {
        cout << "Hadji Inc. Flight Scheduler\n\n";
        cout << "[1]. Airport\n"
             << "[2]. Crew\n"
             << "[3]. Crew Availability\n"
             << "[4]. Exit\n";
        cin >> o;

        if (o == 1)
        {
            cout << "Choose an Airport: \n";
            cout << "MNL - TYO - BKK - KWT - SYD\n";
            cin >> choice;

            if (choice == "MNL")
                source = 0;
            else if (choice == "TYO")
                source = 1;
            else if (choice == "BKK")
                source = 2;
            else if (choice == "KWT")
                source = 3;
            else if (choice == "SYD")
                source = 4;

            processAirport(source, depart, arrive, a);
        }
        else if (o == 2)
        {
            crew_menu(a);
        }
        else if (o == 3)
        {
            cout << "\nThank You";
            return 0;
        }
        else
        {
            cout << "\nInvalid Input!\n";
        }
    }
}