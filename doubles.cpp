#include <cmath>
#include <ios>
#include <iostream>
#include <bitset>
#include <iomanip>
#include <limits>

using namespace std;

string getbits(double value) {
    char *pDouble = (char*)&value;
    string bits = "";

    for (int i = sizeof(value) - 1; i>=0; i--) {
        bitset<8> b = (pDouble[i]);
        bits += b.to_string();
    }

    return bits;
}

double todouble(string bits) {
    const int WIDTH = 15;
    bitset<1> sign(bits[0]);
    bitset<11> exp(bits.substr(1, 11));

    cout << "\n=== Sign (+/-) ===" << endl;
    cout << "Bit" << endl;
    cout << sign << endl;

    cout << left << endl;
    cout << "=== Exponent ===" << endl;
    cout << setw(WIDTH) << "Value" << setw(WIDTH) << "Bits" << endl;
    cout << setw(WIDTH) << exp.to_ulong() << setw(WIDTH) << exp << endl;

    double sum = 1;
    string fraction = bits.substr(12, 52);
    for (int i = 0; i<52; i++) {
        sum += (fraction[i] - '0') * pow(2, -(i + 1));
    }

    cout << left << endl;
    cout << "=== Fraction ===" << endl;
    cout << setw(WIDTH) << "Value" << setw(WIDTH) << "Bits" << endl;
    cout << setw(WIDTH) << sum << setw(WIDTH) << fraction << endl;

    double value = pow(-1, sign.to_ulong()) * pow(2, int(exp.to_ulong()) - 1023) * sum;
    return value;
}

void displayMenu() {
    cout << "\n1. Double -> Bits" << endl;
    cout << "2. Bits -> Double" << endl;
    cout << "3. Exit" << endl;
}

int main() {

    int choice = 0;

    do {
        displayMenu();

        do {
            cin >> choice;
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        } while (cin.fail());

        switch (choice) {
        case 1: {
                double value;
                cout << "Enter a floating point value: ";
                cin >> value;

                string bits = getbits(value);

                cout << "\n=== Bits of " << value << " ===" << endl;
                cout << bits << endl;
                break;
            }
            case 2: {
                string bits;
                cout << "Enter the bit values: ";
                cin >> bits;

                double value = todouble(bits);

                cout << "\n=== Value of bits -> double ===" << endl;
                cout << value << endl;
            }
        }
    } while (choice != 3);
}
