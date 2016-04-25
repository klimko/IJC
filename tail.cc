// tail.c
// Riesenie IJC-DU2, príklad 1b), 25.4.2016
// Autor:     Daniel Klimaj, FIT
// Prelozene: gcc 4.8.4
// Program na citanie poslednych n riadkov suboru

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

void read_lines(istream &stream, int count)
{
    string line;
    vector<string> v;

    while(getline(stream, line))
    {
        v.push_back(line);
    }

    int lines = v.size();
    if(count > lines)
    {
        count = lines;
    }

    for(int i=(lines-count); i<lines; i++)
    {
        cout << v[i];
        if(i+1 != lines)
            cout << endl;
    }
    v.clear();
}

int read_stream(string file_name, int count)
{
    if(file_name == "")
    {
        read_lines(cin, count);
    }
    else
    {
        ifstream f;

        f.open(file_name);
        if(f.is_open() && f.good())
        {
            read_lines(f, count);
            f.close();
        }
        else
        {
            cerr << "Failed to open file '" << file_name << "'" << endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    string file_name;
    int n;

    if(argc == 1)
    {
        n = 10;
    }
    else if(argc == 2)
    {
        file_name = string(argv[1]);
        n = 10;
    }
    else if(argc == 3 || argc == 4)
    {
        if(string(argv[1]) == "-n")
        {
            try
            {
               n = stoi(string(argv[2]));
            }
            catch(const invalid_argument& ia)
            {
                cerr << "Invalid format of number of lines" << endl;
                return EXIT_FAILURE;
            }
        }
        else
        {
            cerr << "Invalid argument " << string(argv[1]) << endl;;
            return EXIT_FAILURE;
        }

        if(argc == 4)
            file_name = string(argv[3]);
    }
    else
    {
        cerr << "Invalid number arguments" << endl;
        return EXIT_FAILURE;
    }

    int rslt = read_stream(file_name, n);

    return rslt;
}