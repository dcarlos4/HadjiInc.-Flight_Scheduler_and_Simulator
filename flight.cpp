#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

#define INF 999
#define num_of_flights 5

using namespace std;

int cost[num_of_flights][num_of_flights] = {{0, 4, 3, 9, 8},
                                            {4, 0, 7, INF, 10},
                                            {3, 7, 0, INF, 9},
                                            {9, INF, INF, 0, 16},
                                            {8, INF, 9, INF, 0}};

class HadjiInc
{
public:
    string cities[num_of_flights] = {"MNL", "TYO", "BKK", "KWT", "SYD"};
    struct schedule
    {
        string fid;
        string fpath;
        int ftime;
        string assigned_plane;
    };

    struct flights
    {
        string flight_path;
        int flight_cost;
        int booking;
    };

    struct aircraft
    {
        string aircraft_id;
        int capacity;
        int total_hours_before_maintenance;
    };
};

// functions
HadjiInc::flights *dijkstra(int starting);
HadjiInc::aircraft *initialize_aircrafts();
HadjiInc::aircraft *sort_aircrafts(HadjiInc::aircraft *a, int num_of_aircrafts);
HadjiInc::schedule *plane_assignment(HadjiInc::flights *f, HadjiInc::aircraft *a);
int get_nearest(int dist[], bool visited[]);

// main function
int main()
{
    string input;
    int starting;
    int hour, minute;
    cout << "Choose an Airport: ";
    cout << "MNL - TYO - BKK - KWT - SYD\n";

    cin >> input;
    if (input == "MNL")
    {
        starting = 0;
    }
    else if (input == "TYO")
    {
        starting = 1;
    }
    else if (input == "BKK")
    {
        starting = 2;
    }
    else if (input == "KWT")
    {
        starting = 3;
    }
    else if (input == "SYD")
    {
        starting = 4;
    }
    HadjiInc::flights *f = dijkstra(starting);
    HadjiInc::aircraft *a = initialize_aircrafts();
    

    cout << "Enter bookings for each flight:";
    for (int i = 0; i < num_of_flights; i++)
    {
        if (starting != i)
        {
            cout << f[i].flight_path << " ";
           
            cin >> f[i].booking;
        }
    }
    for (int i=0; i<num_of_flights; i++){
       // cout<<a[i].aircraft_id;
    }
HadjiInc::schedule *s = plane_assignment(f, a);
    for (int i = 0; i < num_of_flights; i++)
    {
        if (starting != i)
        {

            //cout << s[i].fpath << " ";
            //cout << s[i].assigned_plane << " ";
        }
    }
}

HadjiInc::schedule *plane_assignment(HadjiInc::flights *f, HadjiInc::aircraft *a)
{
    HadjiInc::schedule *s = new HadjiInc::schedule[num_of_flights];
        for (int i = 0; i < num_of_flights; i++)
    {
        //cout<<f[i].booking;
        //cout<<a[i].capacity;
    }



    return s;
}

HadjiInc::aircraft *initialize_aircrafts()
{
    int num_of_aircrafts = 0;
    string aID;
    int cap, main;
    ifstream input("aircraft.txt");
    if (!input)
    {
        cerr << "Error Opening input.txt!";
        return 0;
    }

    input.ignore(numeric_limits<streamsize>::max(), '=');
    input >> num_of_aircrafts;
    string line;
    getline(input, line);
    getline(input, line);
    HadjiInc::aircraft *a = new HadjiInc::aircraft[num_of_aircrafts];

    for (int i = 0; i < num_of_aircrafts; i++)
    {
        input >> aID >> cap >> main;
        a[i].aircraft_id = aID;
        a[i].capacity = cap;
        a[i].total_hours_before_maintenance = main;
    }
    input.close();
    a = sort_aircrafts(a, num_of_aircrafts);
    return a;
}

HadjiInc::aircraft *sort_aircrafts(HadjiInc::aircraft *a, int num_of_aircrafts)
{
    int min = 0;
    int temp1, temp3;
    string temp2;
    for (int i = 0; i < num_of_aircrafts - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < num_of_aircrafts; j++)
        {
            if (a[j].capacity > a[min].capacity)
            {
                min = j;
            }
        }

        temp1 = a[i].capacity;
        temp2 = a[i].aircraft_id;
        temp3 = a[i].total_hours_before_maintenance;

        a[i].capacity = a[min].capacity;
        a[i].aircraft_id = a[min].aircraft_id;
        a[i].total_hours_before_maintenance = a[min].total_hours_before_maintenance;

        a[min].capacity = temp1;
        a[min].aircraft_id = temp2;
        a[min].total_hours_before_maintenance = temp3;
    }

    return a;
}

HadjiInc::flights *dijkstra(int start)
{
    HadjiInc::flights *f = new HadjiInc::flights[num_of_flights];
    HadjiInc hdji;

    int path[100], dist[100];
    bool visited[100] = {0};
    fill(dist, dist + 100, INF);
    dist[start] = 0;

    for (int i = 0; i < num_of_flights; i++)
    {
        int current_node = get_nearest(dist, visited);
        visited[current_node] = true;
        for (int j = 0; j < num_of_flights; j++)
        {
            if (!visited[j] && (dist[current_node] + cost[current_node][j]) < dist[j] && cost[current_node][j] != INF)
            {
                dist[j] = dist[current_node] + cost[current_node][j];
            }
        }
    }

    for (int i = 0; i < num_of_flights; i++)
    {
        f[i].flight_path = hdji.cities[start] + " -> " + hdji.cities[i];
        f[i].flight_cost = dist[i];
    }

    return f;
}

int get_nearest(int dist[], bool visited[])
{
    int min = INF;
    int node = 0;
    for (int i = 0; i < num_of_flights; i++)
    {
        if (!visited[i] && dist[i] < min)
        {
            min = dist[i];
            node = i;
        }
    }
    return node;
}