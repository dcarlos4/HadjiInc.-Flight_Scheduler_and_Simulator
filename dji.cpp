#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <iomanip>

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

    Aircraft(string id, int main) : aircraft_id(id), maintenance(main){};

    static void initialize_aircraft(string filename, vector<Aircraft> &a)
    {
        string id;
        int cap, main;
        ifstream input(filename);
        if (!input)
        {
            cerr << "Error Opening input.txt!";
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

class Crew
{
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

        arrival_hour[i] = (departure_hour[i] + sched[i].flight[i].flight_cost) % 24;
        int planehour = 2 * sched[i].flight[i].flight_cost;
        a[i].setPlaneHours(planehour);
        if (i > 0)
            departure_hour[i] = (departure_hour[i - 1] + 1) % 24;

            cout << i + 1 << "\t\t"
                 << "| " << sched[i].flight[i].flight_id << "\t\t|" << sched[i].flight[i].flight_path << "\t|" << setfill('0') << setw(2) << departure_hour[i] << ":" << setfill('0') << setw(2) << departure_mins[i] << "\t\t\t| " << setfill('0') << setw(2) << arrival_hour[i] << ":" << setfill('0') << setw(2) << arrival_mins[i] << "\t\t|" << sched[i].aircraft[i].aircraft_id<< endl;
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
    cout<<endl;
    for (int i = 0; i < a.size(); i++)
    {
        a[i].planeHours = a[i].getPlaneHours();
        if (a[i].planeHours > 16)
        {
            cout << "Aircraft " << a[i].aircraft_id << " has undergone maintenance at time " << arrival_hour[i] << ":00" << endl;
            a[i].doneMaintenance();
        }
    }

    sched.clear();
    depart.clear();
    arrive.clear();

    return;
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
             << "[3]. Exit\n";
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