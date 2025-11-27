#include <iostream>
#include <random>
#include <ctime>

using namespace std;

struct Pilot {
    string pilot_name[20] = {
        "Cheryl Gentry", "Louisa Holmes", "Layton Rubio", "Kristina Swanson", "Rafferty Frazier",
        "Lillie Stein", "Audrey Hart", "Isobel Bridges", "Gerald Frank", "Haseeb House",
        "Eshal Callahan", "Ivan Le", "Callum Myers", "Katrina Nichols", "Bryony Jarvis",
        "Brett Hendrix", "Oliver Alexander", "Shania Saunders", "Lilia Avila", "Muhammed Dixon"
    };
    bool pilot_avail[20] = {false};
};

struct Copilot {
    string copilot_name[20] = {
        "Rosie Chan", "Alyssia Aguirre", "Tom Bender", "Priya Irwin", "Nikodem Berry",
        "Frankie Donovan", "Penny Lamb", "Jason Macias", "Ronnie Scott", "Noel Cochran",
        "Siena Schultz", "Jessie Gardner", "Anais Everett", "Lulu Shepherd", "Monty Boyd",
        "Soraya O'Sullivan", "Beatrix Evans", "Angela Shepard", "Gabrielle Glover", "Aleena Huffman"
    };
    bool copilot_avail[20] = {false};
};

struct Flight_attendant {
    string fa_name[40] = {
        "Ezekiel Carney", "Abdulrahman Chan", "Victoria Newman", "Saffron Lowe", "Jacques Pineda",
        "Sachin Meyers", "Antonia Jimenez", "Cecil Wilkinson", "Andrew Oconnor", "Honey Randall",
        "Francesca Bowen", "Mitchell Larsen", "Carmen Walker", "Neve Lozano", "Yusra Ryan",
        "Ali Osborn", "Kobi Santiago", "Francesco Prince", "Ebony Everett", "Hope Morrison",
        "Chelsea Doyle", "Amirah Gaines", "Suzanne Bright", "Antony Hatfield", "Lois Frost",
        "Habiba Boyd", "Rhiannon Payne", "Felicity Blanchard", "Harmony Hutchinson", "Gethin Todd",
        "Ashleigh Pittman", "Sahil Rios", "Tegan Burgess", "Ilyas Horn", "Ronald Diaz", "Corey Lynn",
        "Bartosz Edwards", "Axel Potts", "Will Carroll", "Kamil Villegas"
    };
    bool fa_avail[40] = {false};
};

// Function to populate the boolean arrays with random true or false values
void populateAvailability(bool* availArray, int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < size; ++i) {
        availArray[i] = dis(gen); // Randomly assign true or false
    }
}

int main() {
    srand(time(nullptr)); // Seed the random number generator

    Pilot pilot;
    Copilot copilot;
    Flight_attendant fa;

    populateAvailability(pilot.pilot_avail, 20);
    populateAvailability(copilot.copilot_avail, 20);
    populateAvailability(fa.fa_avail, 40);

    // Printing some of the availabilities for demonstration
    cout << "Pilot availability:" << endl;
    for (int i = 0; i < 20; ++i) {
        cout << pilot.pilot_name[i] << ": " << (pilot.pilot_avail[i] ? "Available" : "Not Available") << endl;
    }

    cout << "\nCopilot availability:" << endl;
    for (int i = 0; i < 20; ++i) {
        cout << copilot.copilot_name[i] << ": " << (copilot.copilot_avail[i] ? "Available" : "Not Available") << endl;
    }

    cout << "\nFlight attendant availability:" << endl;
    for (int i = 0; i < 40; ++i) {
        cout << fa.fa_name[i] << ": " << (fa.fa_avail[i] ? "Available" : "Not Available") << endl;
    }

    return 0;
}
