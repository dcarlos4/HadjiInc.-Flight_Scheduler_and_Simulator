#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // for time()

class Crew {
public:
    std::vector<std::string> pilot;
    std::vector<bool> pilot_avail;

    std::vector<std::string> copilot;
    std::vector<bool> copilot_avail;

    std::vector<std::string> fa;
    std::vector<bool> fa_avail;

    // Constructor to populate the crew members and availability
    Crew() {
        // Initialize random number generator
        srand(time(nullptr));

        // Populate pilots and their availability
        populateWithRandomAvailability(pilot, pilot_avail, {
            "Cheryl Gentry", "Louisa Holmes", "Layton Rubio", "Kristina Swanson", "Rafferty Frazier",
            "Lillie Stein", "Audrey Hart", "Isobel Bridges", "Gerald Frank", "Haseeb House",
            "Eshal Callahan", "Ivan Le", "Callum Myers", "Katrina Nichols", "Bryony Jarvis",
            "Brett Hendrix", "Oliver Alexander", "Shania Saunders", "Lilia Avila", "Muhammed Dixon"
        });

        // Populate copilots and their availability
        populateWithRandomAvailability(copilot, copilot_avail, {
            "Rosie Chan", "Alyssia Aguirre", "Tom Bender", "Priya Irwin", "Nikodem Berry",
            "Frankie Donovan", "Penny Lamb", "Jason Macias", "Ronnie Scott", "Noel Cochran",
            "Siena Schultz", "Jessie Gardner", "Anais Everett", "Lulu Shepherd", "Monty Boyd",
            "Soraya O'Sullivan", "Beatrix Evans", "Angela Shepard", "Gabrielle Glover", "Aleena Huffman"
        });

        // Populate flight attendants and their availability
        populateWithRandomAvailability(fa, fa_avail, {
            "Ezekiel Carney", "Abdulrahman Chan", "Victoria Newman", "Saffron Lowe", "Jacques Pineda",
            "Sachin Meyers", "Antonia Jimenez", "Cecil Wilkinson", "Andrew Oconnor", "Honey Randall",
            "Francesca Bowen", "Mitchell Larsen", "Carmen Walker", "Neve Lozano", "Yusra Ryan",
            "Ali Osborn", "Kobi Santiago", "Francesco Prince", "Ebony Everett", "Hope Morrison",
            "Chelsea Doyle", "Amirah Gaines", "Suzanne Bright", "Antony Hatfield", "Lois Frost",
            "Habiba Boyd", "Rhiannon Payne", "Felicity Blanchard", "Harmony Hutchinson", "Gethin Todd",
            "Ashleigh Pittman", "Sahil Rios", "Tegan Burgess", "Ilyas Horn", "Ronald Diaz", "Corey Lynn",
            "Bartosz Edwards", "Axel Potts", "Will Carroll", "Kamil Villegas"
        });
    }

private:
    // Helper function to populate crew members and availability
    void populateWithRandomAvailability(std::vector<std::string>& crew,
                                        std::vector<bool>& availability,
                                        const std::vector<std::string>& names) {
        // Populate crew members
        crew = names;

        // Populate availability with random true/false values
        for (size_t i = 0; i < names.size(); ++i) {
            availability.push_back(rand() % 2 == 0); // Randomly assigns true or false
        }
    }
};

int main() {
    // Create an instance of the Crew class
    Crew crew;

    // Print out the crew members and their availability
    std::cout << "Pilots:" << std::endl;
    for (size_t i = 0; i < crew.pilot.size(); ++i) {
        std::cout << crew.pilot[i] << " - Available: " << (crew.pilot_avail[i] ? "Yes" : "No") << std::endl;
    }

    std::cout << "\nCo-pilots:" << std::endl;
    for (size_t i = 0; i < crew.copilot.size(); ++i) {
        std::cout << crew.copilot[i] << " - Available: " << (crew.copilot_avail[i] ? "Yes" : "No") << std::endl;
    }

    std::cout << "\nFlight Attendants:" << std::endl;
    for (size_t i = 0; i < crew.fa.size(); ++i) {
        std::cout << crew.fa[i] << " - Available: " << (crew.fa_avail[i] ? "Yes" : "No") << std::endl;
    }

    return 0;
}
