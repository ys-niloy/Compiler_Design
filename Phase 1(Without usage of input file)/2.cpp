#include <iostream>
#include <string>

using namespace std;

bool isOperator(char c) 
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=');
}

int main() {
    string userInput;
    cout << "Enter a string: ";
    getline(cin, userInput);

    cout << "Operators: ";
    for (char c : userInput) 
   {
        if (isOperator(c)) {
            cout << c << " ";
        }
    }

    return 0;
}
