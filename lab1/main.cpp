#include <iostream>
#include <string>
#include <sstream>


using namespace std;

int main() {
    int choice;

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
            cout << "add pipe" << endl;
            break;
        case 2:
            cout << "add station" << endl;
            break;
        case 3:
            cout << "show objects" << endl;
            break;
        case 4:
            cout << "edit pipe" << endl;
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