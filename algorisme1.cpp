#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

string toStr(int number){
  if (number > 9){
    string s = "permutation";
    int dec = number/10;
    s += char(number/10) + '0';
    s += char(number-(10 * dec)) + '0';
    return s;
  }else{
    string s= "permutation";
    s += char(number) + '0';
    return s+".txt";
  }
}

int main(){
    cout << "Nombre archivos a comparar: ";
    string file1, file2;
    cin >> file1 >> file2;
    cout << "Introducir k: ";
    int k;
    cin >> k;

    //string file1 = toStr(i);
    ifstream stream1(file1.c_str());
    set<string> set1;
    char c;
    if (stream1.is_open()){
        int numchars = 0;
        string kshingle = "";
        while (stream1.get(c)){
            if (numchars < k) {
                numchars++;
                kshingle += c;
            }
            else {
                set1.insert(kshingle);
                kshingle = kshingle.substr(1,k-1) + c;
            }
        }
    }
    else {
        cout << "unable to open file " + file1 << endl;
        exit(1);
    }

    //string file2 = tostr(j);
    ifstream stream2(file2.c_str());
    set<string> set2;
    if (stream2.is_open()){
        int numchars = 0;
        string kshingle = "";
        while (stream2.get(c)){
            if (numchars < k) {
                numchars++;
                kshingle += c;
            }
            else {
                set2.insert(kshingle);
                kshingle = kshingle.substr(1,k-1) + c;
            }
        }
    }
    else {
        cout << "unable to open file " + file2 << endl;
        exit(1);
    }
    set<string> setinter;
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(setinter, setinter.begin()));

    set<string> setunion;
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(setunion, setunion.begin()));

    double jaccard = (double)setinter.size()/(double)setunion.size();

    cout << jaccard << endl;
}
