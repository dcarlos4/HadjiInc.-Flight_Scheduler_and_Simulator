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