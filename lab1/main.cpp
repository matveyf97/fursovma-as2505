#include <iostream>
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

        cin >> choice;

        if (choice == 0) {
            break;
        }

        cout << "you chose: " << choice << endl;
    }

    return 0;
}