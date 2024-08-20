#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iomanip>
#include "SalesHashTable.h"
using namespace std;

struct winnerCategory
{

    int id_of_veg_winner;
    double formula_veg_winner;
    int id_of_fruits_winner;
    double formula_fruits_winner;
    int id_of_cereals_winner;
    double formula_cereals_winner;
    int id_of_olives_winner;
    double formula_olives_winner;
    int id_of_dates_winner;
    double formula_dates_winner;

    // the default constructor initializes everything to 0
    winnerCategory();
    
    // overloaded operator<< for winnerCategory
    friend std::ostream &operator<<(std::ostream &os, const winnerCategory &winner);
    

    bool isvalid();
};

struct winner_node
{
    int year;
    int height; // adding the height to use it in the balance function
    std::vector<winnerCategory> month_winner = vector<winnerCategory>(12);
    winner_node *left;
    winner_node *right;

    // the default constructor initializes year to 0 and creates a vector with 12 elements (representing months)
    winner_node() ;

    // overloaded operator<< for winner_node
    friend std::ostream &operator<<(std::ostream &os, const winner_node &node);
    

    // Overloaded operator=
    winner_node &operator=(const winner_node &other);
    
};

class winnertree

{

public:
    // Constructor
    winnertree();

    // Copy constructor
    winnertree(const winnertree &other);

    // Move constructor
    winnertree(winnertree &&other) noexcept;

    // Copy assignment operator
    winnertree &operator=(const winnertree &other);

    // Move assignment operator
    winnertree &operator=(winnertree &&other) noexcept;

    // Destructor
    ~winnertree();

    void update_winner(const Sales &farmer); // the purpose of this function is to store and check the winner of each category in each month of a given year

    // fucntions to search for the winner depending on the year , month , or both :

    winnerCategory find_winner_by_year_month(int y, int m); // find the winner in a given year and in a given month

    vector<winnerCategory> find_winner_by_year(int y); // find the winner in a given year

    vector<winnerCategory> find_winner_by_month(int m); // find the winner in a given month

private:
    winner_node data;
    winner_node *root;

    static const int ALLOWED_IMBALANCE = 1;

    void update_winner(const Sales &farmer, winner_node *&temp); // helper function

    double calculateformula(Sales farmer, int category); // function to calculate the formula needed to compare the farmers

    bool isEmpty() const; // return true if the tree is empty

    void find_winner_by_month(int m, vector<winnerCategory> &result, winner_node *root); // find the winner in a given month and in a given year

    winner_node *copyTree(winner_node *node) const; // Function to copy a subtree

    void destroyTree(winner_node *node); // Function to destroy a subtree

    winner_node *insert(const winner_node &element, winner_node *&t); // insert a new node , wich is a helper function that we will call just inside the update_winner

    void insert(const winner_node &element); // insert a node

    void balance(winner_node *&t);

    void rotateWithLeftChild(winner_node *&k2);
    void rotateWithRightChild(winner_node *&k1);
    void doubleWithLeftChild(winner_node *&k3);
    void doubleWithRightChild(winner_node *&k1);

    int height(winner_node *N);
};
