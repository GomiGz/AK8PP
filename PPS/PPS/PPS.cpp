// PPS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <omp.h>
#include "PPS.h"

using namespace std;

/*bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}*/


int main()
{
    bool stop = false;
    string test = "ad";
    while (!stop) {
        //system("cls");
        cout << "Algoritmy:" << endl;
        cout << "1) EREW PRAM" << endl;
        cout << "2) skalovatelny EREW PRAM" << endl;
        cout << "0) ukoncit" << endl;
        cout << "----------------------------------" << endl;
        cout << "Vyberte algortimus: ";
        //cin >> option;

        //if (!is_number(option))
          //  continue;

        switch (stoi(option))
        {
        case 0:
            stop = true;
            break;

        case 1:
            #pragma omp parallel
            {
                cout << ("Hello World... from thread = %d\n", omp_get_thread_num());
            }
            stop = true;
            break;
        default:
            break;
        }
    }
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
