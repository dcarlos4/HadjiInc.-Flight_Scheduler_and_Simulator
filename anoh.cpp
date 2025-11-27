#include <iostream>
#include <vector>
#include <string>
#include <random>    // for random number generation

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
        std::random_device rd;
        std::mt19937 gen(rd());

        // Populate pilots and their availability
        populateWithRandomAvailability(gen, pilot, pilot_avail, {
            "Cheryl Gentry", "Louisa Holmes", "Layton Rubio", "Kristina Swanson", "Rafferty Frazier",
            "Lillie Stein", "Audrey Hart", "Isobel Bridges", "Gerald Frank", "Haseeb House",
            "Eshal Callahan", "Ivan Le", "Callum Myers", "Katrina Nichols", "Bryony Jarvis",
            "Brett Hendrix", "Oliver Alexander", "Shania Saunders", "Lilia Avila", "Muhammed Dixon"
        });

        // Populate copilots and their availability
        populateWithRandomAvailability(gen, copilot, copilot_avail, {
            "Rosie Chan", "Alyssia Aguirre", "Tom Bender", "Priya Irwin", "Nikodem Berry",
            "Frankie Donovan", "Penny Lamb", "Jason Macias", "Ronnie Scott", "Noel Cochran",
            "Siena Schultz", "Jessie Gardner", "Anais Everett", "Lulu Shepherd", "Monty Boyd",
            "Soraya O'Sullivan", "Beatrix Evans", "Angela Shepard", "Gabrielle Glover", "Aleena Huffman"
        });

        // Populate flight attendants and their availability
        populateWithRandomAvailability(gen, fa, fa_avail, {
            "Ezekiel Carney", "Abdulrahman Chan", "Victoria Newman", "Saffron Lowe", "Jacques Pineda",
            "Sachin Meyers", "Antonia Jimenez", "Cecil Wilkinson", "Andrew Oconnor", "Honey Randall",
            "Francesca Bowen", "Mitchell Larsen", "Carmen Walker", "Neve Lozano", "Yusra Ryan",
            "Ali Osborn", "Kobi Santiago", "Francesco Prince", "Ebony Everett", "Hope Morrison",
            "Chelsea Doyle", "Amirah Gaines", "Suzanne Bright", "Antony Hatfield", "Lois Frost",
            "Habiba Boyd", "Rhiannon Payne", "Felicity Blanchard", "Harmony Hutchinson", "Gethin Todd",
            "Ashleigh Pittman", "Sahil Rios", "Tegan Burgess", "Ilyas Horn", "Ronald Diaz", "Corey Lynn",
            "Bartosz Edwards", "Axel Potts", "Will Carroll", "Kamil Villegas"
        });

        // Sort availability arrays with true being the first
mergeSortAvailability(pilot, pilot_avail, 0, pilot.size() - 1);
mergeSortAvailability(copilot, copilot_avail, 0, copilot.size() - 1);
mergeSortAvailability(fa, fa_avail, 0, fa.size() - 1);

    }

private:
    // Helper function to populate crew members and availability
    void populateWithRandomAvailability(std::mt19937& gen,
                                        std::vector<std::string>& crew,
                                        std::vector<bool>& availability,
                                        const std::vector<std::string>& names) {
        // Populate crew members
        crew = names;

        // Determine the minimum number of 'true' values required
        size_t min_true_count = static_cast<size_t>(names.size() * 0.6);

        // Initialize counters
        size_t true_count = 0;

        // Populate availability with random true/false values
        for (size_t i = 0; i < names.size(); ++i) {
            if (true_count < min_true_count || gen() % 2 == 0) {
                availability.push_back(true);  // Assign 'true' with 50% probability or until the minimum count is reached
                true_count++;
            } else {
                availability.push_back(false);
            }
        }
    }

    // Helper function to merge sort availability with true being the first
   // Helper function to merge sort availability with true being the first
void mergeSortAvailability(std::vector<std::string>& crew, std::vector<bool>& availability, int left, int right) {
    if (right <= left) return;
    int mid = left + (right - left) / 2;

    mergeSortAvailability(crew, availability, left, mid);
    mergeSortAvailability(crew, availability, mid + 1, right);

    merge(crew, availability, left, mid, right);
}

void merge(std::vector<std::string>& crew, std::vector<bool>& availability, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    std::vector<std::string> temp_crew = crew;
    std::vector<bool> temp_availability = availability;

    while (i <= mid && j <= right) {
        if (temp_availability[i]) {
            availability[k] = temp_availability[i];
            crew[k] = temp_crew[i];
            i++;
        } else {
            availability[k] = temp_availability[j];
            crew[k] = temp_crew[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        availability[k] = temp_availability[i];
        crew[k] = temp_crew[i];
        i++;
        k++;
    }

    while (j <= right) {
        availability[k] = temp_availability[j];
        crew[k] = temp_crew[j];
        j++;
        k++;
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

