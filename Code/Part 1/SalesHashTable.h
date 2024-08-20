#ifndef SALESHASHTABLE_H
#define SALESHASHTABLE_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <functional>
#include "DSAexcpetions.h" // the file where we defined our own exception 

using namespace std;


int nextPrime(int n);

// this structure is for the 5 categries (vegetable , fruits , olives , cereals , dates) 
struct category
{
    string category_name;
    double average_price;
    double nb_kg_sold;
    int severity_penalty;
     // category constructor
    category(string name = " ", double average_pr = 0, double nb_kg = 0, int penalty = 0 ) ;
    friend ostream &operator<<(ostream &os, const category &sale);


    bool operator==(const category &rhs) const;
    

    bool operator!=(const category &rhs) const;
   

    category &operator=(const category &other);

};


// this structure represents an item of the hash tables that stores the sales, where the key is the ID of the farmer
struct Sales
{
    long farmer_id;
    category *set;
    int month;
    int year;
    double water ;
    double electricity ;

    // sales constructor
    Sales(long id = 0, category *name = nullptr, int m = 0, int y = 0 ,  double w = 0 , double el = 0);
     
    // sales destructor 
    ~Sales();
   

    // copy constructor
    Sales(const Sales &other);
    
  

    //copy assignment
    Sales &operator=(const Sales &other);
   

    friend ostream & operator<<(ostream &os, const Sales &sale)
    {
        os <<"Farmer ID  :" << sale.farmer_id <<"\n";
        os <<"Categories : " << "\n";

        for (int i = 0; i < 5; i++)
        {
            os << sale.set[i] << "\n";
        }
        os <<"month       : " << sale.month << "\n" ;
        os <<"year        : " << sale.year << "\n" ;
        os <<"water       : " << setprecision(2) << fixed << sale.water << "\n" ;
        os <<"electricity : " << setprecision(2) << fixed << sale.electricity<<"\n";
       
        return os;
    }
    

    bool operator==(const Sales &rhs) const;
    

    bool operator!=(const Sales &other);
   
};



class SaleHashTable
{
public:
    SaleHashTable(int size = 101) ; // constructor of SaleHashTable class . 
    
    bool contains(const Sales &x); // check if the sale is in the table or no using the Sale object. the running time is O(1).
    
    bool contains(const long x); //  takes the ID_farmer as parameter and checks if it exists in the hash table . the running time is O(1).

    void makeEmpty(); // make the table of the sales empty. the running time is O(n)

    bool insert(const Sales &x);  // insert the sales using the Id farmer. the running time is O(1).

    bool remove(const Sales &x);  // to remove the sale element. the running time is O(1).

    Sales getSales(long key) ;// it returns the element inside the object in the array cell. the running time is O(1).
   
    int findPos(long key) ; // we made findPos to find the position of the sale inside the table. the running time is O(1).


    enum EntryType
    {
        ACTIVE,
        EMPTY,
        DELETED
    };

private:
    struct HashEntry
    {
        Sales element;
        EntryType info;

        HashEntry(const Sales &e = Sales{}, EntryType i = EMPTY)
            : element{e}, info{i} {}

        HashEntry(Sales &&e, EntryType i = EMPTY)
            : element{std::move(e)}, info{i} {}
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive(int currentPos) const;


    size_t myhash(long key) const;


   

    void rehash();

};

#endif
