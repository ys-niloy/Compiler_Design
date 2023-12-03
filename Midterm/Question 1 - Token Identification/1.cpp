#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



string printValue;
vector<string> invalidVariables;

bool isKeyword(string token)
{
    // taking input from the file
    string filename = "keywords.txt";
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cout << "Error: Unable to open the file." << endl;
        return 1;
    }
    // end of input

    // storing the keywords
    string input;
    vector<string> keys;
    while (inputFile >> input)
    {
        keys.push_back(input);
    }

    string temp; // string to store characters

    for (char c : token)
    {
        if (!isalnum(c))
        {
            break; // stop when an opening bracket is found
        }
        temp += c; // append the character to the temp string
    }

    bool flag = false;

    // check if temp is one of the predefined keywords
    for (const string &key : keys)
    {
        if (temp == key)
        {
            flag = true;
            printValue = temp;
            break;
        }
    }

    // flag will be true if temp is one of the keywords
    return flag;
}

// function to store invalid identifiers
void storeInvalid(const string &invalid)
{
    invalidVariables.push_back(invalid);
}

bool isVariable(string token)
{
    int length = token.size() - 1;

    // Check if the token is a valid variable name
    if (!token.empty() && (isalpha(token[0]) || token[0] == '_'))
    {
        // Check if the rest of the token contains valid characters
        for (int i = 1; i < token.size(); i++)
        {
            if (token[i] == ';' && i == length )
            {
                token.erase(i, 1);
                i--;
            }

            if (!isalnum(token[i]) && token[i] != '_' )
            {
                storeInvalid(token);
                return false;
            }
        }
        printValue = token;
        return true;
    }

    return false;
}



bool isFunction(string token)
{
    int length = token.size() - 1;
    bool flag = false;
    // Check if the token is a valid C++ variable name
    if (!token.empty() && (isalpha(token[0]) || token[0] == '_' ))
    {

        for (int i = 1; i < token.size(); i++)
        {
            if(token[i] == '(')
            {
                flag = true;
                break;
            }
        }

        // Check if the rest of the token contains valid characters
        for (int i = 1; i < token.size(); i++)
        {

            if (token[i] == ';' && i == length )
            {
                token.erase(i, 1);
                i--;
            }

            if (!isalnum(token[i]) && token[i] != '_' && token[i] != '(' && token[i] != ')')
            {
                storeInvalid(token);
                return false;
            }
        }
        if(flag == true)
        {
            printValue = token;
            return true;
        }
    }

    return false;
}


bool isOperator(const string &token)
{
    for (int i = 0; i < token.size(); i++)
    {
        if(token[i] == '+' || token[i] == '-' || token[i] == '/' || token[i] == '*' || token[i] == '%' )
        {
            printValue = token[i];
            return true;
        }
    }

    return false;
}


bool isPunctuations(string &token)
{
    for (int i = 0; i < token.size(); i++)
    {
        if(token[i] == ';' || token[i] == ',' || token[i] == '"' || token[i] == '"' || (token[i] == '<' && token[i+1] == '<' )||
                (token[i] == '>' && token[i+1] == '>' ))
        {
            printValue = token[i];
            return true;
        }
    }

    return false;
}


void print(vector<string> v, string c)
{
    cout << "___________________________________________________________" << endl << endl;
    cout << "The " << c << " in the text file are: " << endl;

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

int main()
{
    // opening the file
    ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        cout << "Error: Unable to open the file." << endl;
        return 1;
    }
    


    // vectors to store the keywords
    vector<string> keywords;
    vector<string> variables;
    vector<string> functions;
    vector<string> operators;
    vector<string> punc;
    
    string prev;  // string to store the previous value

    // storing the lines
    vector<string> tokens;
    string token;
    while (inputFile >> token)
    {
        tokens.push_back(token);
    }
    // end of taking input


    // identifying the entities
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        prev = tokens[i-1];
        if (isKeyword(tokens[i]))
        {
            keywords.push_back(printValue);
        }
        else if ((prev == "int" || prev == "float" || prev == "double" || prev == "char" || prev == "string") && isVariable(tokens[i]))
        {
            variables.push_back(printValue);
        }
        else if (isFunction(tokens[i]))
        {
            functions.push_back(printValue);
        }
        else if (isOperator(tokens[i]))
        {
            operators.push_back(printValue);
        }
        else if (isPunctuations(tokens[i]))
        {
            punc.push_back(printValue);
        }
        else
        {
            printValue.clear();
        }
    }
    inputFile.close();


    print(keywords, "Keywords");
    print(variables, "Variables");
    print(functions, "Functions");
    print(operators, "Operators");
    print(punc, "Punctuations");
    print(invalidVariables, "Invalid Identifiers");

    

    return 0;
}
