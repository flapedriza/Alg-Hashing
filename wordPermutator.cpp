#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <fstream>
using namespace std;

void printVect(vector<string> v)
{
    for (int j = 0; j < v.size(); ++j)
    {
        cout << v[j] << " ";
    }
    cout << endl
         << endl;
}

string toStr(int number)
{
    if (number > 9)
    {
        string s = "permutation";
        int dec = number / 10;
        s += char(number / 10) + '0';
        s += char(number - (10 * dec)) + '0';
        return s + ".txt";
    }
    else
    {
        string s = "permutation";
        s += char(number) + '0';
        return s + ".txt";
    }
}

void writeFile(vector<string> v, int number)
{
    ofstream file;
    file.open(toStr(number).c_str());
    for (int j = 0; j < v.size(); ++j)
    {
        file << v[j] << " ";
    }
    file.close();
}
int main()
{
    srand(time(NULL));
    vector<string> v;
    cout << "Introduce numero de palabras:";
    int np;
    cin >> np;
    for (int i = 0; i < np; ++i)
    {
        int longWord = (rand() % 8) + 2; //longitud minima palabra 2 caracteres
        string s;
        for (int j = 0; j < longWord; ++j)
        {
            s += char(rand() % 26) + 'A';
        }
        v.push_back(s);
    }
    cout << endl
         << "Generando permutaciones" << endl;
    cout << endl
         << "Introduce numero de permutaciones:";
    cin >> np;
    for (int i = 0; i < np; ++i)
    {
        vector<string> v_ = v;
        for (int j = 0; j < v.size(); ++j)
        {
            int s1 = rand() % v_.size();
            int s2 = rand() % v_.size();
            string s = v_[s1];
            v_[s1] = v_[s2];
            v_[s2] = s;
        }
        printVect(v_);
        writeFile(v_, i);
    }
}