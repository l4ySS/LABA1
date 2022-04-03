#include "QuadProbTable.h"
#include <iostream>
#include "fstream"
#include "string"
#include <locale.h>

using namespace std;


int hash1(TValue value)
{

    int seed = 131;
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

    fin.close();
 }


void testCollisions(string filein, string fileout) {

    ofstream fout(fileout);

    QuadraticProbingTable Table1(64, &hash1);
    inputText(Table1, filein);

    QuadraticProbingTable Table2(64, &hash2);
    inputText(Table2, filein);

    QuadraticProbingTable Table3(64, &hash3);
    inputText(Table3, filein);

    fout << "Collions[hash1]=" << Table1.CountColissions() << '\n';
    fout << "Collions[hash2]=" << Table2.CountColissions() << '\n';
    fout << "Collions[hash3]=" << Table3.CountColissions() << '\n';
    fout.close();
}


void main() {
    setlocale(LC_ALL, "Russian");
    string filename = "inputeng.txt";
    string fileout = "output.txt";


    QuadraticProbingTable Table(64, &hash1);
  //QuadraticProbingTable Table(64, &hash3);
  //QuadraticProbingTable Table(64, &hash3);


    cout << "1  -  Input from file" << '\n';
    cout << "2  -  Input from console\n" << '\n';

    cout << "3  -  Remove key" << '\n';
    cout << "4  -  Find key" << '\n';
    cout << "5  -  Print key\n" << '\n';

    cout << "6  -  Print Table" << '\n';
    cout << "7  -  Print collisions count" << '\n';
    cout << "8  -  Clear Table" << '\n';
    cout << "9  -  Test\n" << '\n';

    cout << "0  -  Exit" << '\n';
   

    cout << "Enter command: ";
    int command;
    std::cin >> command;
    while (command != 0) {
        switch (command) {
        case 1:
        {
            inputText(Table, filename);
        }
        break;

        case 2:
        {
            string str;
            cin >> str;
            Table.insert(str);

        }
        break;

        case 3:
        {
            string key;
            cin >> key;
            Table.remove(key);
     
        }
        break;

        case 4:
        {
            string key;
            cin >> key;
            if ( Table.find(key) == 1) cout << "Key found\n";
        }
        break;

        case 5:
        {
            string key;
            cin >> key;
            cout << Table.get(key) << '\n';
        }
        break;

        case 6:
        {
            Table.print();
        }
        break;

        case 7:
        {
            cout << "Collisions = ";
            cout << Table.CountColissions() << '\n';

        }
        break;

        case 8:
        {
            Table.clear();
        }
        break;

        case 9:
        {
            testCollisions(filename, fileout);
        }
        break;

        default:
            std::cout << "Wrong number\n";
        break;

        }

        cout << "\nEnter command: ";
        std::cin >> command;
    }
}