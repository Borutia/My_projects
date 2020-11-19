#include <iostream>
#include <string>

using namespace std;
int main()
{
    string source;
    getline(cin,source);
    string lexeme;
    getline(cin,lexeme);

    string result = "";

    for (size_t pos = 0; pos <= source.size(); pos += 1)
    {
        pos = source.find(lexeme, pos);
        if (pos != string::npos)
        {
            result += to_string(pos) + " ";
        }
        else
        {
            break;
        }
    }
    cout << result;
    return 0;
}