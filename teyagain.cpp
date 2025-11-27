#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct CrewMember
{
    string name;
    string role;
};
struct fleet747
{
    string fleet_747_id;
    string pilot_747;
    string copilot_747;
    string fa_747[5];
    string role_747;
};

struct fleet330
{
    string fleet_330_id;
    string pilot_330;
    string copilot_330;
    string fa_330[4];
    string role_330;
};
// Merge function for merging two sorted halves of the vector
// Merge function for merge sort
void merge(std::vector<CrewMember> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<CrewMember> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        // Ensure pilots appear first, then copilots, then flight attendants
        if (L[i].role == "Pilot" || (L[i].role == "Co-Pilot" && R[j].role == "Flight Attendant"))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Main merge sort function
void mergeSort(std::vector<CrewMember> &crew, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(crew, left, mid);
        mergeSort(crew, mid + 1, right);

        // Merge the sorted halves
        merge(crew, left, mid, right);
    }
}

int main()
{
    vector<CrewMember> crewVector;
    vector<fleet747> f747(28);
    vector<fleet330> f330(24);
    // Names provided in the list (unchanged from your code)
    std::vector<std::string> names = {
        "Tiago O'Moore", "Billy Sanchez", "Nicolas Mccarty", "Ebony Gill", "Anish Cantrell",
        "Olivia Daniel", "Hazel Hubbard", "Rosalind Shepherd", "Hollie Mcconnell", "Jacqueline Rosales",
        "Alexandre Jensen", "Sallie Mcdaniel", "Oscar Gibson", "Clara Stone", "Liliana Carr",
        "Daniela Graham", "Enzo Luna", "Szymon Fletcher", "Jed Cross", "Tiana Mullins",
        "Celeste Roth", "Livia Ayers", "Kelsey Bolton", "Gregory Kaufman", "Alysha Haley",
        "Mariyah Schroeder", "Asa Guzman", "Mikayla Delacruz", "Brendon Oliver", "Josephine Ruiz",
        "Steffan Wilkerson", "Helena Mack", "Abbie Gamble", "Thomas Washington", "Jessica Bernard",
        "Remi Sims", "Zahra Mccormick", "Hope Sampson", "Lyra Barnes", "Julie Smith",
        "Cohen Henderson", "Darius Pugh", "Prince Griffin", "Eliana May", "Arjun Hickman",
        "Frances Erickson", "Lana Davidson", "Flynn Dyer", "Barnaby Miranda", "Albie Sharp",
        "Andrew Baird", "Aliza Hebert"};

    for (int i = 16; i < 52; ++i)
    {
        CrewMember flightAttendant;
        flightAttendant.name = names[i];
        flightAttendant.role = "Flight Attendant";
        crewVector.push_back(flightAttendant);
    }

    for (int i = 0; i < 8; ++i)
    {
        CrewMember pilot;
        pilot.name = names[i];
        pilot.role = "Pilot";
        crewVector.push_back(pilot);
    }

    for (int i = 8; i < 16; ++i)
    {
        CrewMember copilot;
        copilot.name = names[i];
        copilot.role = "Co-Pilot";
        crewVector.push_back(copilot);
    }

    // Sorting the crew members
    mergeSort(crewVector, 0, crewVector.size() - 1);

    for (int i = 0; i < 4; i++)
    {
        f747[i].fleet_747_id = "Crew 747 " + i;
        f747[i].pilot_747 = crewVector[i].name;
        f747[i].role_747 = crewVector[i].role;
    }

    for (int i = 4; i < 8; i++)
    {
        f330[i].fleet_330_id = "Crew 330 " + i;
        f330[i].pilot_330 = crewVector[i].name;
        f330[i].role_330 = crewVector[i].role;
    }

    for (int i = 8; i < 12; i++)
    {
        f747[i].copilot_747 = crewVector[i].name;
        f747[i].role_747 = crewVector[i].role;
    }
    for (int i = 12; i < 16; i++)
    {
        f330[i].copilot_330 = crewVector[i].name;
        f330[i].role_330 = crewVector[i].role;
    }
    
  for (int i = 0; i < 5; i++) {
    for (int j = 16; j < 36; j++) {
        f747[i].fa_747[i] = crewVector[j].name;
    }
}




    for (int i = 0; i<4; i++){
        cout<<f747[i].pilot_747;
        for (int j=0; j<5; j++){
            cout<<f747[j].fa_747;
        }
    }
    return 0;
}
