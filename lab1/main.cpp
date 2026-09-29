#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;


struct Pipe {
    string name; 
    double length = 0;
    double diameter = 0;
    bool inRepair = false;
};

struct Station {
    string name;
    int totalWorkshops = 0;
    int workingWorkshops = 0;
    int stationClass = 0;
};

bool readPositiveNumber(const string& prompt, double& value) {
    string line;

    while (true) {
        cout << prompt;

        if (!getline(cin, line)) {
            return false;
        }

        istringstream input(line);
        double number;
        char extra;

        if ((input >> number) && !(input >> extra)
            && isfinite(number) && number > 0) {
            value = number;
            return true;
        }

        cout << "enter a positive number" << endl;
    }
}

bool readInteger(const string& prompt, int& value,
                 int minValue, int maxValue) {
    string line;

    while (true) {
        cout << prompt;

        if (!getline(cin, line)) {
            return false;
        }

        istringstream input(line);
        int number;
        char extra;

        if ((input >> number) && !(input >> extra)
            && number >= minValue && number <= maxValue) {
            value = number;
            return true;
        }

        cout << "enter a whole number from "
             << minValue << " to " << maxValue << endl;
    }
}

bool readPipe(Pipe& pipe) {
    Pipe newPipe;

    while (true) {
        cout << "pipe name: ";

        if (!getline(cin, newPipe.name)) {
            return false;
        }

        if (newPipe.name.find_first_not_of(" \t\r") != string::npos) {
            break;
        }

        cout << "name cannot be empty" << endl;
    }

    if (!readPositiveNumber("length in km: ", newPipe.length)) {
        return false;
    }

    if (!readPositiveNumber("diameter in mm: ", newPipe.diameter)) {
        return false;
    }

    string line;

    while (true) {
        cout << "in repair (0 - no, 1 - yes): ";

        if (!getline(cin, line)) {
            return false;
        }

        istringstream input(line);
        int repair;
        char extra;

        if ((input >> repair) && !(input >> extra)
            && (repair == 0 || repair == 1)) {
            newPipe.inRepair = (repair == 1);
            break;
        }

        cout << "enter 0 or 1" << endl;
    }

    pipe = newPipe;
    return true;
}

void showPipe(const Pipe& pipe) {
    cout << "name: " << pipe.name << endl;
    cout << "length: " << pipe.length << " km" << endl;
    cout << "diameter: " << pipe.diameter << " mm" << endl;

    if (pipe.inRepair) {
        cout << "in repair: yes" << endl;
    } else {
        cout << "in repair: no" << endl;
    }
}

void editPipe(Pipe& pipe) {
    pipe.inRepair = !pipe.inRepair;

    if (pipe.inRepair) {
        cout << "pipe is now in repair" << endl;
    } else {
        cout << "pipe is now working" << endl;
    }
}

bool readStation(Station& station) {
    Station newStation;

    while (true) {
        cout << "station name: ";

        if (!getline(cin, newStation.name)) {
            return false;
        }

        if (newStation.name.find_first_not_of(" \t\r") != string::npos) {
            break;
        }

        cout << "name cannot be empty" << endl;
    }

    if (!readInteger("total workshops: ",
                     newStation.totalWorkshops,
                     1, numeric_limits<int>::max())) {
        return false;
    }

    if (!readInteger("working workshops: ",
                     newStation.workingWorkshops,
                     0, newStation.totalWorkshops)) {
        return false;
    }

    if (!readInteger("station class: ",
                     newStation.stationClass,
                     1, numeric_limits<int>::max())) {
        return false;
    }

    station = newStation;
    return true;
}

void showStation(const Station& station) {
    cout << "station name: " << station.name << endl;
    cout << "total workshops: " << station.totalWorkshops << endl;
    cout << "working workshops: " << station.workingWorkshops << endl;
    cout << "station class: " << station.stationClass << endl;
}

int main() {
    int choice;

    Pipe pipe;
    bool hasPipe = false;

    Station station;
    bool hasStation = false;

    while (true) {
                cout << "\n1. add pipe" << endl;
        cout << "2. add station" << endl;
        cout << "3. show objects" << endl;
        cout << "4. edit pipe" << endl;
        cout << "5. edit station" << endl;
        cout << "6. save" << endl;
        cout << "7. load" << endl;
        cout << "0. exit" << endl;
        cout << "choose action: ";

        string line;

        if (!getline(cin, line)) {
            break;
        }

        istringstream input(line);
        char extra;

        if (!(input >> choice) || (input >> extra)) {
            cout << "enter one whole number" << endl;
            continue;
        }

        if (choice < 0 || choice > 7) {
            cout << "choose from 0 to 7" << endl;
            continue;
        }

        if (choice == 0) {
            break;
        }

    switch (choice) {
        case 1:
            if (hasPipe) {
                cout << "pipe already added" << endl;
                break;
            }

            if (!readPipe(pipe)) {
                return 0;
            }

            hasPipe = true;
            cout << "pipe added" << endl;
            break;
        case 2:
            if (hasStation) {
                cout << "station already added" << endl;
                break;
            }

            if (!readStation(station)) {
                return 0;
            }

            hasStation = true;
            cout << "station added" << endl;
            break;
        case 3:
            if (hasPipe) {
                showPipe(pipe);
            } else {
                cout << "no pipe added" << endl;
            }

            if (hasStation) {
                showStation(station);
            } else {
                cout << "no station added" << endl;
                
            }
            break;

        case 4:
            if (hasPipe) {
                editPipe(pipe);
            } else {
                cout << "no pipe added" << endl;
            }
            break;
        case 5:
            cout << "edit station" << endl;
            break;
        case 6:
            cout << "save" << endl;
            break;
        case 7:
            cout << "load" << endl;
            break;
        }
    }    
    return 0;
}