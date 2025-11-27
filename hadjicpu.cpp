

void mergeSort(string arr[], int l, int r);

void assignCrew(const string& start, const string& end) {
    departure = stoi(start);
    destination = stoi(end);

    srand(time(NULL));
    for (int i = 0; i < 40; ++i)
        crews[i] = (i < 2) ? "P" + to_string(1000 + rand() % 9000) : "FA" + to_string(100 + rand() % 900);

    mergeSort(crews, 0, 39);

    if (highDemand) { // Check if flight is high demand
        for (int i = 0; i < 2; ++i)
            pilot[i] = crews[i];
        for (int i = 0; i < 8; ++i)
            flightAttendants[i] = crews[i + 2];
    } else {
        for (int i = 0; i < 2; ++i)
            pilot[i] = crews[i];
        for (int i = 0; i < 6; ++i)
            flightAttendants[i] = crews[i + 2];
    }

    cout << "Assigning Crew for Flight from " << departure << " to " << destination << endl;
    cout << "Pilots: ";
    for (int i = 0; i < 2; ++i)
        cout << pilot[i] << ", ";
    cout << endl;

    cout << "Flight Attendants: ";
    for (int i = 0; i < (highDemand ? 8 : 6); ++i)
        cout << flightAttendants[i] << ", ";
    cout << endl;
  }
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
