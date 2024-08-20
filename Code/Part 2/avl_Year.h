#ifndef AVL_Year_H
#define AVL_Year_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "DSAexcpetions.h"
#include "SalesHashTable.h"
#include <algorithm>
using namespace std;

// the yearSales represent the the node in The avl_Year
struct yearSales
{
    int year;
    SaleHashTable sales[12]; // array of hashtables of sales // each hash table represents the sales for a specific month
    yearSales(int yr)
    {
        if (yr < 1990 || yr > 2022)
        {
            throw out_of_range("invalid year");
        }
        else
        {
            year = yr;
        }
    }

    yearSales(int &&yr)
    {
        if (yr < 1990 || yr > 2022)
        {
            throw out_of_range("invalid year");
        }
        else
        {
            year = move(yr);
        }
    }

    yearSales(int yr, SaleHashTable sl[])
    {
        if (yr < 1990 || yr > 2022)
        {
           throw out_of_range("invalid year");
        }
        else
        {
            year = yr;
        }
        for (int i = 0; i < 12; i++)
        {
            sales[i] = sl[i];
        }
    }; // we need first to create an array of sales that contain hash table of arrays
    yearSales(int &&yr, SaleHashTable sl[])
    {
        if (yr < 1990 || yr > 2022)
        {
           throw out_of_range("invalid year");
        }
        else
        {
            year = move(yr);
        }
        for (int i = 0; i < 12; i++)
        {
            sales[i] = sl[i];
        }
    }
    bool operator<(const yearSales &other) const
    {
        return year < other.year;
    }
};

class avl_Year
{
public:
    // farmer struct
    struct Farmer
    {
        // Farmer's ID, Farmer's area, Farmer's SSN,
        // Farmer's Full Name,Farmer's gender,
        // Farmer's age,Number Of People Who Help them
        long farmer_Id;
        int farmer_area;
        long farmer_SSN;
        string farmer_fullName;
        string farmer_gender; // Male or Female
        int farmer_age;
        int nb_helpers;

        // constructor function
        Farmer(long i = 0, int area = 0, long SSN = 0, string name = "", string gender = "",
               int age = 0, int helpers = 0)
            : farmer_Id{i}, farmer_area{area}, farmer_SSN{SSN}, farmer_fullName{name},
              farmer_gender{gender}, farmer_age{age}, nb_helpers{helpers} {
                if(farmer_Id < 0 || farmer_Id > 200000){
                   throw out_of_range("this is doesn't exist in our dataset ");
                  }
              };
    };

    // constructor
    avl_Year();

    /**
     * Copy constructor
     */
    avl_Year(const avl_Year &);

    /**
     * Move constructor
     */
    avl_Year(avl_Year &&);

    /**
     * Destructor for the tree
     */
    ~avl_Year()
    {
        makeEmpty();
    }

    /**
     * Copy assignment
     */
    avl_Year &operator=(const avl_Year &);

    /**
     * Move assignment
     */
    avl_Year &operator=(avl_Year &&);

    bool contains(const yearSales &x) const
    {
        return contains(x, root);
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const yearSales &x)
    {
        insert(x, root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(yearSales &&x)
    {
        insert(std::move(x), root);
    }
    void insert(const Sales &);

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const yearSales &x)
    {
        remove(x, root);
    }

    // Getting the sales of a specific farmer in a specific year and a specific month
    void reportSales(int, int, long) const;

    // Getting the sales of a specific farmer in a specific year
    void reportSales(int, long) const;

    // getting the penalties of a specific farmer in a specific year and month
    void reportPenalties(int, int, long) const;

    // getting the penalties of a specific farmer in a specific year
    void reportPenalties(int, long) const;

    // getting the sales of the farmers of a specific area in a specific year
    void reportArea(int, int) const;

    // getting the sales of the farmers of a specific city in a specific year

    void reportCity(int, int) const;

    // getting the sales of the farmers of a specific wilaya in a specific year
    void reportWilaya(int, int) const;

    // getting the sales of the all the farmers in a the whole contry .
    void reportCountry(int year) const;

    // getting the penalties of the all the farmers in a specific wilaya .
    void penalty_farmers_Wilaya(int year, int wilayaID);

    // getting the penalties of the all the farmers in a specific city .
    void penalty_farmers_city(int year, int cityId);

    void reportFarmer(int id) const;
    vector<float> findSales(long id, int month, int year, bool& worked);
private:
    struct BinaryNode
    {
        yearSales element;
        BinaryNode *left;
        BinaryNode *right;
        int height;
        BinaryNode(const yearSales &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} {}

        BinaryNode(yearSales &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{std::move(theElement)}, left{lt}, right{rt} {}
    };
    BinaryNode *root;
    static const int ALLOWED_IMBALANCE = 1;
    // wilayas stores a linked list of the cities corresponding to the current position in the vector
    // we will assume that the array starts at position 0 to keep consistent with the different wilayas and cities codes
    vector<list<int>> wilayas = vector<list<int>>(59);
    // cities stores a linkedist of areas codes corresponding to city position
    vector<list<int>> cities = vector<list<int>>(4829);
    // areas stores a linked list of Farmers ' Ids belonging to the area position
    vector<list<long>> areas = vector<list<long>>(1542);

    // definition of the Farmer struct as a an entry of the Farmers vector

    // Declare the farmers vector that contains a collection of farmers
    vector<Farmer> farmers;
    void fill_farmers(const Farmer &obj)
    {
        farmers.push_back(obj);
    }

    // Defining a function fill_areas to fill the areas vector with the appropriate farmers
    //  ' IDs
    void fill_areas(const avl_Year::Farmer &);

    void init(string);
    void read_farmers(string);

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const yearSales &, BinaryNode *&);

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(yearSales &&, BinaryNode *&);

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const yearSales &, BinaryNode *&);

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    bool contains(const yearSales &, BinaryNode *) const;

    void makeEmpty(BinaryNode *&);

    /**
     * Internal method to clone subtree.
     */
    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
    void balance(BinaryNode *&t);

    void rotateWithLeftChild(BinaryNode *&k2);
    void rotateWithRightChild(BinaryNode *&k1);
    void doubleWithLeftChild(BinaryNode *&k3);
    void doubleWithRightChild(BinaryNode *&k1);

    int height(BinaryNode *t){
        return t == nullptr ? -1 : t->height;
    }
    
    //utility function for the findSales used to display a bar chart for a farmer in a given month and year
    BinaryNode* searchNode(int year, BinaryNode* ptr){
        if(ptr == nullptr)
            return nullptr;
        if(year < ptr->element.year)
            searchNode(year, ptr->left);
        else if(year > ptr->element.year)
            searchNode(year, ptr->right);
        else
            return ptr;
    };
};

#endif
