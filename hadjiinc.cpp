#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;

#define INF 999
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
    int booking;
    string flight_path;
    string assigned_plane;
    Flights(int bookings, int source, int destination) : booking(bookings)
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
    int capacity;
    int maintenance;

    Aircraft(string id, int cap, int main) : aircraft_id(id), capacity(cap), maintenance(main){};

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
        while (input >> id >> cap >> main)
        {
            a.push_back(Aircraft(id, cap, main));
        }
    }

    static bool compare_sort(const Aircraft &a, const Aircraft &b)
    {
        return a.capacity > b.capacity;
    }

    private:
};

class Crew
{
};

class Schedule{
public:
    vector<Flights> flight;
    vector<Aircraft> aircraft;
    string departure_time;
    string arrival_time;


    Schedule(vector<Flights> flight, string departure, string arrival, vector<Aircraft> aircraft)
        : flight(flight), departure_time(departure), arrival_time(arrival), aircraft(aircraft) {}




};


int main()
{
    int source, booking;
    string choice;
    vector<Flights> depart;
    vector<Flights> arrive;
    vector<Schedule> sched;
    vector<Aircraft> a;
 
    Aircraft::initialize_aircraft("aircraft.txt", a);
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

    cout << "Enter Bookings for each flight: \n";
    for (int i = 0; i < initial_num_of_flights; i++)
    {
        if (source != i)
        {
            cout << cities[source] + " -> " + cities[i] << endl;
            cout << ">";
            cin >> booking;
            depart.push_back(Flights(booking, source, i));
            arrive.push_back(Flights(booking, i, source));
        }
    }
    sort(depart.begin(), depart.end(), Flights::compare_sort);
    sort(a.begin(), a.end(), Aircraft::compare_sort);
    for (int i = 0; i < depart.size(); i++)
    {
        sched.push_back(Schedule(depart, "00:00", to_string(depart[i].flight_cost) + ":00", a ));
    }
    cout<<"FLIGHT ID | FLIGHT PATH | DEPARTURE TIME | ARRIVAL TIME | ASSIGNED AIRCRAFT | CAPACITY\n";
    for (int i = 0; i < depart.size(); i++)
    {
        cout << sched[i].flight[i].flight_id<< "\t\t "<< sched[i].flight[i].flight_path<< "\t\t "<< sched[i].departure_time<< "\t\t "<< sched[i].arrival_time<< "\t\t "<< sched[i].flight[i].booking<< "\t\t "<<sched[i].aircraft[i].capacity<<" "<<endl;
    }


/*
    for (int i = 0; i < depart.size(); i++)
    {
        cout << depart[i].flight_id << " " << depart[i].flight_path << " " << depart[i].flight_cost << endl;
    }
    
    for (int i = 0; i < arrive.size(); i++)
    {
        cout << arrive[i].flight_id << " " << arrive[i].flight_path << " " << arrive[i].flight_cost << endl;
    }
  
    
        for (int i = 0; i < a.size(); i++)
    {
        cout << a[i].aircraft_id << " " << a[i].capacity << " " << a[i].maintenance << endl;
    }
      */
    
}
