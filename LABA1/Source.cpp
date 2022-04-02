#include "QuadProbTable.h"
#include <iostream>
#include "fstream"
#include "string"
#include <locale.h>

using namespace std;


int hash1(TValue value)
{
    int seed = 7;
    unsigned long hash = 0;
    for (int i = 0; i < value.length(); i++)
    {
        hash = (hash * seed) + value[i];
    }
    return hash;
}

int hash2(TValue value)
{
    int prime = 31;
    int hashCode = 0;
    for (int i = 0; i < value.length(); i++) {
        hashCode += value[i] * pow(prime, i);
    }
    return hashCode;
}

int hash3(TValue value)
{
    int sum = 0;
    for (int i = 0; i < value.length(); i++)
        sum = sum + int(value[i]);

    return sum;
}

void inputText(QuadraticProbingTable& Table, string filename) {
    ifstream fin(filename);
    
    string temp, word;

    while (!fin.eof()) {

        getline(fin, temp);
        size_t index = 0;
        while (temp[index] != '\0')
        {

            if (!(ispunct((temp[index])) || isspace(temp[index])))
            {
                word += temp[index];

            }
            else
            {
                if (word.length() > 0)
                {
                   
                    Table.insert(word);

                }
                word.clear();
            }
            index++;
        }
        Table.insert(word);
    }

 }


void testCollisions(string filein, string fileout) {

    ofstream fout(fileout);
    ifstream fin(filein);

    QuadraticProbingTable Table1(64, &hash1);
    inputText(Table1, filein);

    fin.seekg(0, fin.beg);
    QuadraticProbingTable Table2(64, &hash2);
    inputText(Table2, filein);

    fin.seekg(0, fin.beg);
    QuadraticProbingTable Table3(64, &hash3);
    inputText(Table3, filein);

    fout << "Collions[hash1]=" << Table1.CountColissions() << '\n';
    fout << "Collions[hash2]=" << Table2.CountColissions() << '\n';
    fout << "Collions[hash3]=" << Table3.CountColissions() << '\n';
    fin.close();
    fout.close();
}


void main() {
    setlocale(LC_ALL, "Russian");
    QuadraticProbingTable Table(64, &hash2);
    string filename = "inputeng.txt";
    string fileout = "output.txt";


    cout << "1  -  Choose Hash1" << '\n';
    cout << "2  -  Choose Hash2" << '\n';
    cout << "3  -  Choose Hash3\n" << '\n';

    cout << "4  -  Input from file" << '\n';
    cout << "44 -  Input from console\n" << '\n';

    cout << "5  -  Remove key" << '\n';
    cout << "61 -  Find key" << '\n';
    cout << "62 -  Print key\n" << '\n';

    cout << "7  -  Print Table" << '\n';
    cout << "8  -  Print collisions count" << '\n';
    cout << "99 -  Clear Table" << '\n';
    cout << "11 -  Test\n" << '\n';

    cout << "0  -  Exit" << '\n';
   

    cout << "Enter command: ";
    int n;
    std::cin >> n;
    while (n != 0) {
        switch (n) {
        case 1:
        {
            Table.clear();
            QuadraticProbingTable Table(64, &hash1);
        }
        break;
        case 2:
        {
            Table.clear();
            QuadraticProbingTable Table(64, &hash2);
        }
        break;
        case 3:
        {
            Table.clear();
            QuadraticProbingTable Table(64, &hash3);
        }
        break;
        case 4:
        {
            inputText(Table, filename);
        }
        break;


        case 44:
        {
            string str;
            cin >> str;
            Table.insert(str);

        }
        break;
        case 5:
        {
            string key;
            cin >> key;
            Table.remove(key);
            
        }
        break;
        case 61:
        {
            string key;
            cin >> key;
            if ( Table.find(key) == 1) cout << "Key found\n";
        }
        break;
        case 62:
        {
            string key;
            cin >> key;
            cout << Table.get(key) << '\n';
        }
        break;

        case 7:
        {
            Table.print();
        }
        break;

        case 8:
        {
            cout << "Collisions = ";
            cout << Table.CountColissions() << '\n';

        }
        break;

        case 99:
        {
            Table.clear();
        }
        break;
        case 11:
        {
            testCollisions(filename, fileout);
        }
        break;
        default:
            std::cout << "Wrong number\n";
        break;
        }
        cout << "\nEnter command: ";
        std::cin >> n;
    }
}