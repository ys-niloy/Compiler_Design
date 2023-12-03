#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool checkExisting(char c, char op[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (op[i] == c)
        {
            return true;
        }
    }

    return false;
}

bool isSpace(char c)
{
    return (c == ' ');
}

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '=');
}

bool checkType(string line)
{
    int returnTypePos = line.find(" ");
    int i = 0;

    if (returnTypePos == -1)
    {
        return false;
    }

    if ((returnTypePos != 0) && (line.substr(0, 3) == "int" || line.substr(0, 4) == "void" || line.substr(0, 5) == "float" || line.substr(0, 5) == "double" || line.substr(0, 4) == "char" || line.substr(0, 5) == "string" || line.substr(0, 4) == "bool") &&
        (line.substr(4, 4) != "main"))
    {
        return true;
    }

    return false;
}

string getFunctionName(string &line)
{
    size_t returnTypePos = line.find(" ");
    if (returnTypePos != string::npos)
    {
        while (isSpace(line[returnTypePos]))
        {
            ++returnTypePos;
        }

        size_t start = returnTypePos;
        size_t end = line.find("(", start);
        if (end != string::npos)
        {
            return line.substr(start, end - start);
        }
    }

    return "";
}

void printOperator(string op, int opCount)
{
    string operatorNames[] = {"Addition", "Substraction", "Multiplication", "Division", "Assignment"};

    for (int i = 0; i < opCount; i++)
    {
        if (op[i] == '+')
        {
            cout << "Operator - " << i + 1 << ": " << " Addition" << endl;
        }
        else if (op[i] == '-')
        {
            cout << "Operator - " << i + 1 << ": " << " Substraction" << endl;
        }
        else if (op[i] == '*')
        {
            cout << "Operator - " << i + 1 << ": " << " Multiplication" << endl;
        }
        else if (op[i] == '/')
        {
            cout << "Operator - " << i + 1 << ": " << " Division" << endl;
        }
        else if (op[i] == '=')
        {
            cout << "Operator - " << i + 1 << ": " << " Assignment" << endl;
        }
    }

    cout << "Total number of operators: " << opCount << "\n\n";
}

void process(string fileName)
{

    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cerr << "Error opening file." << endl;
        return;
    }

    int funcCount = 0;
    int opCount = 0;

    int maxOpSize = 100;
    char op[maxOpSize];
    string functionName = " ";

    string line;

    // open file and fetch data
    while (getline(inputFile, line))
    {
        if (checkType(line))
        {
            functionName = getFunctionName(line);
            if (!functionName.empty())
            {
                cout << "Function - " << ++funcCount << ": " << functionName << endl;
            }
        }

        for (char c : line)
        {
            if (isOperator(c) && !checkExisting(c, op, opCount))
            {
                op[opCount++] = c;
            }
        }
    }

    inputFile.close();

    cout << "Total number of user-defined functions: " << funcCount << "\n\n";

    printOperator(op, opCount);
}

int main()
{

    string fileName = "program.cpp";
    process(fileName);

    return 0;
}
