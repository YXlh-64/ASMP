#include <iostream>
#include "APMS.h"
using namespace std;

//Note: Our program has been designed to be able to generate graphs and charts during the running time using the python's matplotlib library
//      , yet there is a set of instructions which you should follow in order to set up a python environment for our program, otherwise a set 
//      of fatal runtime errors would be generated.
//      Our program does not contain any dependencies to Python initially (We have commented the code sections that make use of Matplotlib initilally)
//      in case the user wants to test it regardless of these extra functionalities. So, if you want to make use of the funtions that generate graphs 
//      the runtime, all you need is to uncomment those peices of code and test them.
//      Make sure to take a look at our documentation located in the root folder entitled "Matplotlib setup: Installation and compilation" where we 
//      provided you with a full guidance of how you can setup this environment. In case it didn't work for you, we have included some screenshots
//      in the report that show how the graphs were generated


//Here is the command to run the program on ubuntu (using python 3.10) (notice that the command is machine-specific as described in the documentation)
//Make sure to visit our documentation "Matplotlib setup: Installation and compilation walkthrough in C++:" located in the root directory 
/*
    g++ -o main APMS.cpp bst_Year.cpp main.cpp SalesHashTable.cpp winnertree.cpp -std=c++11 -I/usr/include/python3.10 -lpython3.10 -w
*/
int main()
{
    cout << endl
              << endl
              << "Our dataset comprises two files: one with 1,000,000 instances and the other with 200,000 instances. \nAs the tree insertion operation is substantial, it may take a few seconds (approximately 57 seconds) to complete. Your patience is much appreciated... " << endl
              << endl;

    APMS test;
    test.run();
    return 0;
}