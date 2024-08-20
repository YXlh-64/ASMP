#include <iostream>
#include "SalesHashTable.h"
#include "DSAexcpetions.h"

using namespace std;

 

bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

int nextPrime(int n)
{
    if (n % 2 == 0)
        ++n;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}

category::category(string name , double average_pr , double nb_kg , int penalty) : category_name{name},
    average_price{average_pr}, nb_kg_sold{nb_kg}, severity_penalty{penalty} 
    {

       if (average_pr < 0 || nb_kg < 0)
            {
                throw out_of_range("the number of kgs and the average price , can NOT take negative values ");
            }

      if (penalty < 0 || penalty > 3)
{
            throw out_of_range("the penalty severity need to be between 1 and 3 ");
        }
    }

// overloading the operator << : 
ostream &operator<<(ostream &os, const category &sale)
{
    // Your implementation here
    os << "  Category          :" << sale.category_name << "\n"
       << "  the average price : " << setprecision(2) << fixed << sale.average_price << "\n"
       << "  number of kg      : " << setprecision(2) << fixed << sale.nb_kg_sold << "\n"
       << "  severity_penalty  : " << sale.severity_penalty << "\n";

    return os;
}

 bool category::operator==(const category &rhs) const
    {
        return (category_name == rhs.category_name &&
                average_price == rhs.average_price &&
                nb_kg_sold == rhs.nb_kg_sold &&
                severity_penalty == rhs.severity_penalty);
    }

     bool category::operator!=(const category &rhs) const
    {
        return !(*this == rhs);
    }

    category & category::operator=(const category &other)
    {
        if (this != &other)
        {
            category_name = other.category_name;
            average_price = other.average_price;
            nb_kg_sold = other.nb_kg_sold;
            severity_penalty = other.severity_penalty;
        }
        return *this; 
    }


    Sales::Sales(long id , category *name , int m , int y ,  double w , double el)
        : farmer_id{id}, month{m}, year{y}, water{w} , electricity{el}
     {

         if(farmer_id < 0 || farmer_id > 1000000){
            throw out_of_range("id doesn't exist , please try again ");
        }

        set = new category[5];

        if (name != nullptr)
        {
            for (int i = 0; i < 5; i++)
            {
                set[i] = name[i];
            }
        }
    }

    Sales:: ~Sales()
    {
        delete[] set;
    }

     Sales::Sales(const Sales &other)
        : farmer_id{other.farmer_id}, month{other.month}, year{other.year} , water{other.water} , electricity{other.electricity}
    {

        set = new category[5];
        for (int i = 0; i < 5; i++)
        {
            set[i] = other.set[i];
        }

    }

    Sales & Sales::operator=(const Sales &other)
    {
        if (this != &other)
        {
            delete[] set;
            farmer_id = other.farmer_id;
            month = other.month;
            year = other.year;
            water = other.water;
            electricity = other.electricity;
            set = new category[5];
            for (int i = 0; i < 5; i++)
            {
                set[i] = other.set[i];
            }
        }
        return *this;
    }

 

    bool Sales::operator==(const Sales &rhs) const
    {
        if (!((farmer_id == rhs.farmer_id) && (month == rhs.month) && (year == rhs.year) && (water == rhs.water) && (electricity == rhs.electricity)))
            return false;

        for (int i = 0; i < 5; i++)
        {
            if (set[i] != rhs.set[i])
                return false;
        }
        return true;
    }

     bool Sales::operator!=(const Sales &other)
    {
        return !(*this == other);
    }

     bool SaleHashTable::isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }
    size_t SaleHashTable::myhash(long key) const
    {
        static hash<long> hf;
        return hf(key) % array.size();
    }

    void SaleHashTable::rehash()
    {
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize(nextPrime(2 * oldArray.size()));
        for (auto &entry : array)
            entry.info = EMPTY;

        // Copy table over
        currentSize = 0;
        for (auto &entry : oldArray)
            if (entry.info == ACTIVE)
                insert(move(entry.element));
    }


   

SaleHashTable ::SaleHashTable(int size) : array(nextPrime(size))
{
    makeEmpty();
}

bool SaleHashTable ::contains(const Sales &x)
{
    return isActive(findPos(x.farmer_id));
}

bool SaleHashTable ::contains(const long x)
{
    return isActive(findPos(x));
}

void SaleHashTable ::makeEmpty()
{
    currentSize = 0;
    for (auto &entry : array)
        entry.info = EMPTY;
}

bool SaleHashTable ::insert(const Sales &x)
{
    // Insert x as active
    int currentPos = findPos(x.farmer_id);
    if (isActive(currentPos))
        return false;
    if (array[currentPos].info != DELETED)
        ++currentSize;

    array[currentPos].element = x;
    array[currentPos].info = ACTIVE;

    // Rehash; see Section 5.5
    if (currentSize > array.size() / 2)
        rehash();

    return true;
}

bool SaleHashTable ::remove(const Sales &x)
{
    int currentPos = findPos(x.farmer_id);
    if (!isActive(currentPos))
        return false;

    array[currentPos].info = DELETED;
    return true;
}

Sales SaleHashTable ::getSales(long key) // it returns the element inside the object in the array cell
{
    int currentPos = findPos(key);
    if (currentPos < array.size())
        return array[currentPos].element;
    return Sales{};
}

int SaleHashTable ::findPos(long key) // we made findPos a public function so we can use it later
{

    int offset = 1;

    int currentPos = myhash(key);

    while (array[currentPos].info != EMPTY && array[currentPos].element.farmer_id != key)
    {
        currentPos += offset; // Compute ith probe
        offset += 2;
        if (currentPos >= array.size())
            currentPos -= array.size();
    }
    return currentPos;
}

