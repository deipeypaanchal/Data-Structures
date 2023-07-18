#include <iostream>
#include <fstream>

using namespace std;

int main()
{

    string text;

    ifstream MyReadFile("rules.txt");

    while (getline (MyReadFile, text)) {
        cout << text << endl;
    }

    MyReadFile.close();

    return 0;
}