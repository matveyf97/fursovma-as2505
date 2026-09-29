#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#include <fstream>
#include <iomanip>

using namespace std;

struct Pipe
{
    string name;
    double length = 0;
    double diameter = 0;
    bool inRepair = false;
};

struct Station
{
    string name;
    int totalWorkshops = 0;
    int workingWorkshops = 0;
    int stationClass = 0;
};

bool readPositiveNumber(const string &prompt, double &value)
{
    string line;

    while (true)
    {
        cout << prompt;

        if (!getline(cin, line))
        {
            return false;
        }

        istringstream input(line);
        double number;
        char extra;

        if ((input >> number) && !(input >> extra) && isfinite(number) && number > 0)
        {
            value = number;
            return true;
        }

        cout << "enter a positive number" << endl;
    }
}

bool readInteger(const string &prompt, int &value,
                 int minValue, int maxValue)
{
    string line;

    while (true)
    {
        cout << prompt;

        if (!getline(cin, line))
        {
            return false;
        }

        istringstream input(line);
        int number;
        char extra;

        if ((input >> number) && !(input >> extra) && number >= minValue && number <= maxValue)
        {
            value = number;
            return true;
        }

        cout << "enter a whole number from "
             << minValue << " to " << maxValue << endl;
    }
}

bool readPipe(Pipe &pipe)
{
    Pipe newPipe;

    while (true)
    {
        cout << "pipe name: ";

        if (!getline(cin, newPipe.name))
        {
            return false;
        }

        if (newPipe.name.find_first_not_of(" \t\r") != string::npos)
        {
            break;
        }

        cout << "name cannot be empty" << endl;
    }

    if (!readPositiveNumber("length in km: ", newPipe.length))
    {
        return false;
    }

    if (!readPositiveNumber("diameter in mm: ", newPipe.diameter))
    {
        return false;
    }

    string line;

    while (true)
    {
        cout << "in repair (0 - no, 1 - yes): ";

        if (!getline(cin, line))
        {
            return false;
        }

        istringstream input(line);
        int repair;
        char extra;

        if ((input >> repair) && !(input >> extra) && (repair == 0 || repair == 1))
        {
            newPipe.inRepair = (repair == 1);
            break;
        }

        cout << "enter 0 or 1" << endl;
    }

    pipe = newPipe;
    return true;
}

void showPipe(const Pipe &pipe)
{
    cout << "name: " << pipe.name << endl;
    cout << "length: " << pipe.length << " km" << endl;
    cout << "diameter: " << pipe.diameter << " mm" << endl;

    if (pipe.inRepair)
    {
        cout << "in repair: yes" << endl;
    }
    else
    {
        cout << "in repair: no" << endl;
    }
}

void editPipe(Pipe &pipe)
{
    pipe.inRepair = !pipe.inRepair;

    if (pipe.inRepair)
    {
        cout << "pipe is now in repair" << endl;
    }
    else
    {
        cout << "pipe is now working" << endl;
    }
}

bool readStation(Station &station)
{
    Station newStation;

    while (true)
    {
        cout << "station name: ";

        if (!getline(cin, newStation.name))
        {
            return false;
        }

        if (newStation.name.find_first_not_of(" \t\r") != string::npos)
        {
            break;
        }

        cout << "name cannot be empty" << endl;
    }

    if (!readInteger("total workshops: ",
                     newStation.totalWorkshops,
                     1, numeric_limits<int>::max()))
    {
        return false;
    }

    if (!readInteger("working workshops: ",
                     newStation.workingWorkshops,
                     0, newStation.totalWorkshops))
    {
        return false;
    }

    if (!readInteger("station class: ",
                     newStation.stationClass,
                     1, numeric_limits<int>::max()))
    {
        return false;
    }

    station = newStation;
    return true;
}

void showStation(const Station &station)
{
    cout << "station name: " << station.name << endl;
    cout << "total workshops: " << station.totalWorkshops << endl;
    cout << "working workshops: " << station.workingWorkshops << endl;
    cout << "station class: " << station.stationClass << endl;
}

bool editStation(Station &station)
{
    cout << "1. start workshop" << endl;
    cout << "2. stop workshop" << endl;
    cout << "0. back" << endl;

    int action;

    if (!readInteger("choose action: ", action, 0, 2))
    {
        return false;
    }

    if (action == 1)
    {
        if (station.workingWorkshops < station.totalWorkshops)
        {
            station.workingWorkshops++;
            cout << "workshop started" << endl;
        }
        else
        {
            cout << "all workshops are already working" << endl;
        }
    }
    else if (action == 2)
    {
        if (station.workingWorkshops > 0)
        {
            station.workingWorkshops--;
            cout << "workshop stopped" << endl;
        }
        else
        {
            cout << "all workshops are already stopped" << endl;
        }
    }

    return true;
}

void savePipe(ofstream &file, const Pipe &pipe)
{
    file << pipe.name << '\n';
    file << pipe.length << '\n';
    file << pipe.diameter << '\n';
    file << pipe.inRepair << '\n';
}

void saveStation(ofstream &file, const Station &station)
{
    file << station.name << '\n';
    file << station.totalWorkshops << '\n';
    file << station.workingWorkshops << '\n';
    file << station.stationClass << '\n';
}

void saveData(const Pipe &pipe, bool hasPipe,
              const Station &station, bool hasStation)
{
    ofstream file("data.txt");

    if (!file.is_open())
    {
        cout << "cannot open file" << endl;
        return;
    }

    file << setprecision(numeric_limits<double>::max_digits10);

    file << hasPipe << '\n';

    if (hasPipe)
    {
        savePipe(file, pipe);
    }

    file << hasStation << '\n';

    if (hasStation)
    {
        saveStation(file, station);
    }

    file.close();

    if (!file)
    {
        cout << "cannot save data" << endl;
        return;
    }

    cout << "data saved" << endl;
}
bool readFileInteger(ifstream &file, int &value)
{
    string line;

    if (!getline(file, line))
    {
        return false;
    }

    istringstream input(line);
    char extra;

    if (!(input >> value) || (input >> extra))
    {
        return false;
    }

    return true;
}

bool readFileDouble(ifstream &file, double &value)
{
    string line;

    if (!getline(file, line))
    {
        return false;
    }

    istringstream input(line);
    char extra;

    if (!(input >> value) || (input >> extra))
    {
        return false;
    }

    return isfinite(value);
}

bool loadPipe(ifstream &file, Pipe &pipe)
{
    if (!getline(file, pipe.name))
    {
        return false;
    }

    if (pipe.name.find_first_not_of(" \t\r") == string::npos)
    {
        return false;
    }

    if (!readFileDouble(file, pipe.length) || pipe.length <= 0)
    {
        return false;
    }

    if (!readFileDouble(file, pipe.diameter) || pipe.diameter <= 0)
    {
        return false;
    }

    int repair;

    if (!readFileInteger(file, repair) || (repair != 0 && repair != 1))
    {
        return false;
    }

    pipe.inRepair = (repair == 1);
    return true;
}

bool loadStation(ifstream &file, Station &station)
{
    if (!getline(file, station.name))
    {
        return false;
    }

    if (station.name.find_first_not_of(" \t\r") == string::npos)
    {
        return false;
    }

    if (!readFileInteger(file, station.totalWorkshops) || station.totalWorkshops < 1)
    {
        return false;
    }

    if (!readFileInteger(file, station.workingWorkshops) || station.workingWorkshops < 0 || station.workingWorkshops > station.totalWorkshops)
    {
        return false;
    }

    if (!readFileInteger(file, station.stationClass) || station.stationClass < 1)
    {
        return false;
    }

    return true;
}

void loadData(Pipe &pipe, bool &hasPipe,
              Station &station, bool &hasStation)
{
    ifstream file("data.txt");

    if (!file.is_open())
    {
        cout << "cannot open file" << endl;
        return;
    }

    Pipe newPipe;
    Station newStation;
    int pipeExists;
    int stationExists;

    if (!readFileInteger(file, pipeExists) || (pipeExists != 0 && pipeExists != 1))
    {
        cout << "invalid pipe flag" << endl;
        return;
    }

    if (pipeExists == 1 && !loadPipe(file, newPipe))
    {
        cout << "invalid pipe data" << endl;
        return;
    }

    if (!readFileInteger(file, stationExists) || (stationExists != 0 && stationExists != 1))
    {
        cout << "invalid station flag" << endl;
        return;
    }

    if (stationExists == 1 && !loadStation(file, newStation))
    {
        cout << "invalid station data" << endl;
        return;
    }

    string remaining;

    while (getline(file, remaining))
    {
        if (remaining.find_first_not_of(" \t\r") != string::npos)
        {
            cout << "unexpected data at end of file" << endl;
            return;
        }
    }

    if (file.bad() || !file.eof())
    {
        cout << "cannot read file" << endl;
        return;
    }

    pipe = newPipe;
    station = newStation;
    hasPipe = (pipeExists == 1);
    hasStation = (stationExists == 1);

    cout << "data loaded" << endl;
}

int main()
{
    int choice;

    Pipe pipe;
    bool hasPipe = false;

    Station station;
    bool hasStation = false;

    while (true)
    {
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

        if (!getline(cin, line))
        {
            break;
        }

        istringstream input(line);
        char extra;

        if (!(input >> choice) || (input >> extra))
        {
            cout << "enter one whole number" << endl;
            continue;
        }

        if (choice < 0 || choice > 7)
        {
            cout << "choose from 0 to 7" << endl;
            continue;
        }

        if (choice == 0)
        {
            break;
        }

        switch (choice)
        {
        case 1:
            if (hasPipe)
            {
                cout << "pipe already added" << endl;
                break;
            }

            if (!readPipe(pipe))
            {
                return 0;
            }

            hasPipe = true;
            cout << "pipe added" << endl;
            break;
        case 2:
            if (hasStation)
            {
                cout << "station already added" << endl;
                break;
            }

            if (!readStation(station))
            {
                return 0;
            }

            hasStation = true;
            cout << "station added" << endl;
            break;
        case 3:
            if (hasPipe)
            {
                showPipe(pipe);
            }
            else
            {
                cout << "no pipe added" << endl;
            }

            if (hasStation)
            {
                showStation(station);
            }
            else
            {
                cout << "no station added" << endl;
            }
            break;

        case 4:
            if (hasPipe)
            {
                editPipe(pipe);
            }
            else
            {
                cout << "no pipe added" << endl;
            }
            break;
        case 5:
            if (!hasStation)
            {
                cout << "no station added" << endl;
                break;
            }

            if (!editStation(station))
            {
                return 0;
            }
            break;
        case 6:
            saveData(pipe, hasPipe, station, hasStation);
            break;
        case 7:
            loadData(pipe, hasPipe, station, hasStation);
            break;
        }
    }
    return 0;
}