#include "QuadProbTable1.h"
#include "QuadProbTable2.h"
#include "QuadProbTable3.h"
#include <iostream>
#include "fstream"
#include "string"
#include <locale.h>
using namespace std;


bool inputText(QuadraticProbingTable& Table, string filename) {
    ifstream fin(filename);
    if (!fin.is_open() || fin.eof()) return false;
    
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
    return true;
 }

bool inputText(QuadraticProbingTable2& Table, string filename) {
    ifstream fin(filename);
    if (!fin.is_open() || fin.eof()) return false;

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
    return true;
}

bool inputText(QuadraticProbingTable3& Table, string filename) {
    ifstream fin(filename);
    if (!fin.is_open() || fin.eof()) return false;

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
    return true;
}

void testCollisions(string filein, string fileout) {
    QuadraticProbingTable Table(64);
    QuadraticProbingTable2 Table2(64);
    QuadraticProbingTable3 Table3(64);
    ofstream fout(fileout);
    
    ifstream fin(filein);
    inputText(Table, filein);

   

    fin.seekg(0, fin.beg);
    inputText(Table2, filein);


    fin.seekg(0, fin.beg);
    inputText(Table3, filein);
    fin.close();

    fout << "Collions[hash1]=" << Table.CountColissions() << '\n';
    fout << "Collions[hash2]=" << Table2.CountColissions() << '\n';
    fout << "Collions[hash3]=" << Table3.CountColissions() << '\n';
}



void main() {
    setlocale(LC_ALL, "Russian");
    QuadraticProbingTable Table1(64);
    QuadraticProbingTable2 Table2(64);
    QuadraticProbingTable3 Table3(64);



    int ChosenHash = 1;
    string filename = "inputeng.txt";
    string fileout = "output.txt";




    cout << "1  -  Init Hash1" << '\n';
    cout << "2  -  Init Hash2" << '\n';
    cout << "3  -  Init Hash3\n" << '\n';

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
            Table1.clear();
            QuadraticProbingTable Table1(64);
            ChosenHash = 1;
        }
        break;
        case 2:
        {
            Table2.clear();
            QuadraticProbingTable2 Table2(64);
            ChosenHash = 2;
        }
        break;
        case 3:
        {
            Table3.clear();
            QuadraticProbingTable3 Table3(64);
            ChosenHash = 3;
        }
        break;
        case 4:
        {
            switch (ChosenHash) {
            case 1:
            {
                
                inputText(Table1, filename);
            }
            break;
            case 2:
            {

                inputText(Table2, filename);
            }
            break;
            case 3:
            {
     
                inputText(Table3, filename);
            }
            break;

            }
        }
        break;


        case 44:
        {
            string str;
            cin >> str;
            switch (ChosenHash) {
            case 1:
            {

                Table1.insert(str);
            }
            break;
            case 2:
            {

                Table2.insert(str);
            }
            break;
            case 3:
            {

                Table3.insert(str);
            }
            break;

            }
        }
            break;
        case 5:
        {
            string key;
            cin >> key;
            switch (ChosenHash) {
            case 1:
            {

                Table1.remove(key);
            }
            break;
            case 2:
            {

                Table2.remove(key);
            }
            break;
            case 3:
            {

                Table3.remove(key);
            }
            break;

            }
        }
        break;
        case 61:
        {
            string key;
            cin >> key;
            switch (ChosenHash) {
            case 1:
            {

               if ( Table1.find(key) == 1) cout << "Key found\n";
            }
            break;
            case 2:
            {

                if (Table2.find(key) == 1) cout << "Key found\n";;
            }
            break;
            case 3:
            {

                if (Table3.find(key) == 1) cout << "Key found\n";;
            }
            break;

            }
            
        }
        break;
        case 62:
        {
            string key;
            cin >> key;
            switch (ChosenHash) {
            case 1:
            {

                cout << Table1.get(key) << '\n';
            }
            break;
            case 2:
            {

                cout << Table2.get(key) << '\n';
            }
            break;
            case 3:
            {

                cout << Table3.get(key) << '\n';
            }
            break;

            }
        }
        break;

        case 7:
        {
            switch (ChosenHash) {
            case 1:
            {

                Table1.print();
            }
            break;
            case 2:
            {

                Table2.print();
            }
            break;
            case 3:
            {

                Table3.print();
            }
            break;

            }
        }
        break;

        case 8:
        {
            cout << "Collisions = ";
            switch (ChosenHash) {
            case 1:
            {
                cout << Table1.CountColissions() << '\n';
            }
            break;
            case 2:
            {

                cout << Table2.CountColissions() << '\n';
            }
            break;
            case 3:
            {

                cout << Table3.CountColissions() << '\n';
            }
            break;

            }
        }
        break;

        case 99:
        {
            switch (ChosenHash) {
            case 1:
            {

                Table1.clear();
            }
            break;
            case 2:
            {

                Table2.clear();
            }
            break;
            case 3:
            {

                Table3.clear();
            }
            break;

            }
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
    for (int i = 0; i < 64; i++) {
        Table1.insert("privet");
    }
    Table1.print();
}