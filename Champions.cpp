// Name: Deepey Panchal
// U80305771
// Champions Program

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// Function to split a string into tokens using a delimiter
vector<string> split(string str, char delimiter)
{
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    // Open input file
    ifstream input_file("world_cup_champions.txt");
    if (!input_file)
    {
        cerr << "Error: failed to open input file." << endl;
        return 1;
    }

    // Map to store the number of wins for each country
    map<string, int> country_wins;

    // Read input file line by line
    string line;
    while (getline(input_file, line))
    {
        // Split line into tokens using tab as delimiter
        vector<string> tokens = split(line, '\t');
        if (tokens.size() < 2)
        {
            cerr << "Error: invalid input line: " << line << endl;
            continue;
        }
        // Extract country name from tokens
        string country = tokens[1];
        // If country not in map, add it with 0 wins
        if (country_wins.find(country) == country_wins.end())
        {
            country_wins[country] = 0;
        }
        // Increment number of wins for the country
        country_wins[country]++;
    }

    // Output header
    cout << "FIFA World Cup Winners" << endl;
    cout << endl;
    cout << "Country         Wins  Years" << endl;
    cout << "=======         ====  =====" << endl;

    // Iterate over the map to output results for each country
    for (map<string, int>::iterator it = country_wins.begin(); it != country_wins.end(); ++it)
    {
        // Extract country name and number of wins from iterator
        const string &country = it->first;
        const int &wins = it->second;
        // Output country name and number of wins
        cout << left << setw(15) << country << " ";
        cout << right << setw(4) << wins << "  ";
        // Reset input file to beginning
        input_file.clear();
        input_file.seekg(0);
        // Read input file line by line to find years the country won
        string years;
        while (getline(input_file, line))
        {
            if (line.find(country) != string::npos)
            {
                vector<string> tokens = split(line, '\t');
                years += tokens[0] + ", ";
            }
        }
        // Remove trailing comma and space from years string
        years.erase(years.size() - 2);
        // Output years the country won
        cout << years << endl;
    }

    // Close input file and exit
    input_file.close();
    return 0;
}