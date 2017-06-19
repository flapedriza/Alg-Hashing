#include <iostream>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <random>
#include <string>

using namespace std;

unsigned long hashFunction(unsigned long h, const char *str){
    int c;
    while (c = *str++) h = ((h << 5) + h) + c;
    return h;
}

int main(){
    cout << "Nombre archivos a comparar: ";
    string file1, file2;
    cin >> file1 >> file2;
    int k, nHash, nShingles;
    cout << "Introduce valor de k: ";
    cin >> k;
    cout << "Introduce numero de shingles a computar: ";
    cin >> nShingles;
    cout << "Introduce numero de funciones de hash: ";
    cin >> nHash;

    //Usaremos esto para obtener nHash funciones de hash distintas
    vector< vector<int> > hashValues(nHash,vector<int>(2,0));
    random_device rd;
    for (int i = 0; i < nHash; ++i){
        hashValues[i][0] = rd()%100;
        hashValues[i][1] = rd()%1000;
    }

    ifstream stream1(file1.c_str());
    unordered_set<string> set1;
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

    ifstream stream2(file2.c_str());
    unordered_set<string> set2;
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

    unordered_set<string> s1, s2;

    unordered_set<string>::iterator it;
    it = set1.begin();
    while (s1.size() < nShingles){
        int randomN = rd()%3;
        for (int i = 0; i < randomN; ++i){
            ++it;
            if (it == set1.end()) it = set1.begin();
        }
	s1.insert(*it);
    }
    it = set2.begin();
    while (s2.size() < nShingles){
        int randomN = rd()%3;
    	for (int i = 0; i < randomN; ++i){
	    ++it;
    	    if (it == set2.end()) it = set2.begin();
        }
        s2.insert(*it);
    }
    //Generar signature
    unordered_set<int> randomHashCodes;
    vector<unsigned long> sig1(nHash,0);
    vector<unsigned long> sig2(nHash,0); //signatures
    unsigned long min1 = 0, min2 = 0;
    for (int i = 0; i < nHash; ++i){
            bool ready = false;
            while (not ready){
                    int randomN = rd()%(nHash*100);
                    if (randomHashCodes.find(randomN) == randomHashCodes.end()){
                            randomHashCodes.insert(randomN);
                            ready = true;
                    }
            }
    }

    unordered_set<string>::iterator it2;
    unordered_set<int>::iterator it3 = randomHashCodes.begin();
    for (int i = 0; i < nHash; ++i){
        it = s1.begin();
        it2 = s2.begin();
        int h = *it3;
        ++it3;
        for (int j = 0; j < nShingles; ++j){
                    string str1 = *it;
                    if (it == s1.begin()) min1 = (hashValues[i][0]*hashFunction(h, str1.c_str())+hashValues[i][1])%nShingles;
                    else{
                            unsigned long x = (hashValues[i][0]*hashFunction(h, str1.c_str())+hashValues[i][1])%nShingles;
                            if (x < min1) min1 = x;
                    }
                    cout << "1-> " << str1 << ": " << (hashValues[i][0]*hashFunction(h, str1.c_str())+hashValues[i][1])%nShingles << endl;

                    string str2 = *it2;
                    if (it2 == s2.begin()) min2 = (hashValues[i][0]*hashFunction(h, str2.c_str())+hashValues[i][1])%nShingles;
                    else{
                            unsigned long x = (hashValues[i][0]*hashFunction(h, str2.c_str())+hashValues[i][1])%nShingles;
                            if (x < min2) min2 = x;
                    }
                    cout << "2-> " << str2 << ": " << (hashValues[i][0]*hashFunction(h, str2.c_str())+hashValues[i][1])%nShingles << endl;
                    ++it;
                    ++it2;
        }
        sig1[i] = min1;
        sig2[i] = min2;

    }
    for (int i = 0; i < nHash; ++i) cout << sig1[i] << " ";
    cout << endl;
    for (int i = 0; i < nHash; ++i) cout << sig2[i] << " ";
    cout << endl;

    int sum = 0;
    for (int i = 0; i < nHash; ++i){
        if (sig1[i] == sig2[i]) ++sum;
    }
    double coeficient = (double)sum/(double)nHash;
    cout << "El coeficient de similaritat entre els dos textos es: " << coeficient << endl;

}
