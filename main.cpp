#include <iostream>

#define INF 999
#define num_of_flights 5

using namespace std;

int pathways[num_of_flights][num_of_flights] = {{0, 4, 3, 9, 8},
                      {4, 0, 7, INF, 10},
                      {3, 7, 0, INF, 9},
                      {9, INF, INF, 0, 16},
                      {8, INF, 9, INF, 0}};
int crews[40]; //crew
int planes = 5;
int cityNumber; //1-Manila 2-Kuwait 3-Tokyo 4-Sydney 5-Bangkok

class FlightList{ //for flight listing, delete a flight once set to a Flight
  private:
    int departure, destination;
    bool highDemand;

  public:
    FlightList(int departure, int destination, bool highDemand){
      departure = departure;
      destination = destination;
      highDemand = highDemand;
    }
};

class Flight{
  private:
    int flightNumber;
    int crewTime; //crewTime = airTime/2 if crewTime >= 8; rest
    int airTime; //if airTime >= 25; maintenance
    int layoverNumber;
    int departure, location, destination;
    
    bool highDemand;
    bool crewRest;
    bool underMaintenance;

    string layover;
    string pilot [2];  
    string flightAttendants [6];

    public: 
    //Constructor 
    Flight(){}
};

void merge(string arr[], int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;

        string L[n1], R[n2];
        for (int i = 0; i < n1; ++i)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (rand() % 2) {
                arr[k] = L[i];
                ++i;
            } else {
                arr[k] = R[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            arr[k] = L[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            arr[k] = R[j];
            ++j;
            ++k;
        }
    }
void mergeSort(string arr[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }
void randomizeArray(string arr[], int n){
   for (int i = n - 1; i > 0; i--){
     int j = rand() % (i + 1);
     swap(arr[i], arr[j]);
   }
}

void assignCrew(){
  
}
 
int main() {
  int option, flightAmt;

  cout<<"========================="<<endl;
  cout<<"      HADJI AIRLINES     "<<endl;
  cout<<"========================="<<endl;
  cout<<"[1] - Set Flights\n[0] - Exit\n:"<<endl;
  cin>>option;
  cout<<"Set Amount of Flights: ";
  cin>>flightAmt;
  FlightList flight[flightAmt];
  while(option != 0){
    switch(option){
      case 1:
        for(int x = 0; x < flightAmt; x++){
          int departure, destination;
          bool highDemand = 0;
          cout<<"Flight "<<x+1<<": "<<endl;
          cout<<"City of Departure: "<<endl;
          cout<<"[1] Manila\n[2] Kuwait\n[3] Tokyo\n[4] Sydney\n[5] Bangkok"<<endl;
          cin>>departure;
          cout<<"City of Destination: "<<endl;
          cout<<"[1] Manila\n[2] Kuwait\n[3] Tokyo\n[4] Sydney\n[5] Bangkok"<<endl;
          cin>>destination;
          cout<<"High Demand? (1 for yes, 0 for no)"<<endl;
          if(highDemand == 1){
            highDemand = true;
          }
          flight[x] = FlightList(departure, destination, highDemand);
        }
        break;
    }
  }
  
}

/* NOTE:

TASKS:

  Greedy Algorithm (Initial Scheduling)
  Coloma = Divide and Conquer (Crew Assignment)
  Buan = Transform and Conquer (Maintenance Scheduling)
  Decrease and Conquer (Optimization)

  
REQUIREMENTS:

  User Input = Flight and Demand
  High demand = more FA
  Matrix for pathways mostly
  Class and object for flight assembly containing the resources: Crew, fligh time, etc.

CONDITIONS:
  Planes will start at one country
  Flights will be scheduled based on the shortest path but with conditions:
    1. Find out different flights on the same country going on the same country(Layovers as         well) and if not high demand, then flight should merge and not make a new object                flight
    2. After arrival, it will also seek shortest path going to the next flight scheduled.
    3. For layovers, if plane need sudden maintenance or crew requires sudden rest, it will         stay and a new plane will be called for the passengers.
  Maintenance:
    1. Minor maintenance: 5 hrs Major maintenance: 1 day/24 hrs
    2. Plane will undergo maintenance if it reaches atleast 25hrs or greater flight time.
    3. During a layover and need maintenance, it should go do a minor maintenance unless there      is an available plane to fetch passengers it will go through full maintenance.
  Crew periods:
    1. Atleast 8hrs work on flights or greater, will take rest
    2. If under layover, will reduce the work time by 1hr
    3. Work hours on flight is divided by initial flight time by 2.
    4. If crew suddenly needs rest, the plane can go under minor maintenance which will reduce      flight time by 3hrs

  flight Table 5x5:
       PH    JP    SK   SG   AU
  PH |  0 |    4|    3|   3|   8|
  JP |    |     |     |    |    |
  SK |    |     |     |    |    |
  SG |    |     |     |    |    |
  AU |    |     |     |    |    |
*/