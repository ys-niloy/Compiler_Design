#include <iostream>
#include <string>

using namespace std;

bool isNumeric(string &userInput) {
    for (char c : userInput) {
        if (!((c >= '0' && c <= '9') || c == '.')) {
            return false;
        }
    }
    return true;
}

int main() {
    string userInput;
    cout << "Enter a string: ";
    getline(cin, userInput);

    if (isNumeric(userInput)) {
        cout << "Numeric";
    } else {
        cout << "Not Numeric";
    }

    return 0;
}
