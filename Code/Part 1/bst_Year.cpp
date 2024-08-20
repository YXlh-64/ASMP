#include "bst_Year.h"
using namespace std;

bst_Year ::bst_Year() : root{nullptr}
{
    init("../Data/cities.csv");         // filling the cities, areas, wilayas vectors
    read_farmers("../Data/farmer.csv"); // filling the vector of farmers
}

// copy constructor
bst_Year ::bst_Year(const bst_Year &rhs) : root{nullptr}
{
    root = clone(rhs.root);
    wilayas = rhs.wilayas;
    cities = rhs.cities;
    farmers = rhs.farmers;
    areas = rhs.areas;
}

// Move constructor
bst_Year::bst_Year(bst_Year &&rhs) : root{rhs.root}
{
    rhs.root = nullptr;
    wilayas = move(rhs.wilayas);
    cities = move(rhs.cities);
    areas = move(rhs.areas);
    farmers = move(rhs.farmers);
}

// copy assignment
bst_Year &bst_Year ::operator=(const bst_Year &rhs)
{
    bst_Year copy = rhs;
    std::swap(*this, copy);
    return *this;
}

// Move assignment
bst_Year &bst_Year::operator=(bst_Year &&rhs)
{
    std::swap(root, rhs.root);
    bst_Year copy = std::move(rhs);
    wilayas = rhs.wilayas;
    areas = rhs.areas;
    cities = rhs.cities;
    farmers = rhs.farmers;
    return *this;
}

// insert a sales object to the bst_Year
void bst_Year::insert(const Sales &sl)
{
    BinaryNode *current = root;
    // we need first to check if the year exist or no
    while (current != nullptr)
    {
        if (sl.year < current->element.year)
            current = current->left;
        else if (sl.year > current->element.year)
            current = current->right;
        else
        {
            // the year exist then we just need to insert the sales to the its hashtable
            current->element.sales[sl.month - 1].insert(sl);
            return;
        }
    }
    // if the year doesn't exist then we need to create a yearSales object and then insert the sale then we need to insert
    // the yearSales object (hold) into our bst_Year
    yearSales hold(sl.year);
    hold.sales[sl.month - 1].insert(sl);
    insert(hold);
    return;
};

// Getting the sales of a specific farmer in a specific year
void bst_Year::reportSales(int year, long id) const
{
    if (year < 1990 || year > 2022)
        throw out_of_range("invalid year");
    BinaryNode *current = root;
    while (current != nullptr)
    {
        if (year < current->element.year)
            current = current->left;
        else if (year > current->element.year)
            current = current->right;

        else if (year == current->element.year)
        {
            cout << "---------------------------------------------------------------------------" << endl;
            for (int i = 0; i < 12; i++)
            {
                if (current->element.sales[i].contains(id))
                {
                    // we print the sales of the farmer then
                    Sales currentSale = current->element.sales[i].getSales(id);
                    cout << "The farmer  " << farmers[id - 1].farmer_fullName << " " << id << " has sold " << endl;
                    for (int j = 0; j < 5; j++)
                    {
                        cout << "  Category          :" << currentSale.set[j].category_name << "\n"
                             << "  the average price : " << setprecision(2) << fixed << currentSale.set[j].average_price << "\n"
                             << "  number of kg      : " << setprecision(2) << fixed << currentSale.set[j].nb_kg_sold << "\n";
                    }
                    cout << "in the month " << i + 1 << " and year " << year << endl;
                }
                else
                {
                    cout << "the farmer " << farmers[id - 1].farmer_fullName << " didn't work in the month : " << i + 1 << endl;
                }
            }
            cout << "---------------------------------------------------------------------------" << endl;
            return;
        }
    }
    cout <<"this year doesn't exist in our dataset" <<endl;
}

void bst_Year ::reportCountry(int year)
{
    // looping through all the wilayas

    if (year < 1990 || year > 2022)
        throw out_of_range("invalid year");

    std::ofstream csvFile("reportCountry.csv");
    BinaryNode *current = root;
    // we need first to check if the year exist or no
    while (current != nullptr)
    {
        if (year < current->element.year)
            current = current->left;
        else if (year > current->element.year)
            current = current->right;
        else
        {
            for (int k = 1; k < 4; k++)
                for (const auto &cityId : wilayas[k])
                    for (const auto &areaID : cities[cityId])
                        for (const auto &idFarmer : areas[areaID])
                        {
                            for (int i = 0; i < 12; i++)
                            {
                                Sales currentSale = current->element.sales[i].getSales(idFarmer);
                                if (currentSale.set[0].average_price == 0 && currentSale.set[1].average_price == 0 && currentSale.set[2].average_price == 0 && currentSale.set[3].average_price == 0 && currentSale.set[4].average_price == 0 && currentSale.set[0].nb_kg_sold == 0 && currentSale.set[1].nb_kg_sold == 0 && currentSale.set[2].nb_kg_sold == 0 && currentSale.set[3].nb_kg_sold == 0 && currentSale.set[4].nb_kg_sold == 0 && currentSale.set[0].severity_penalty == 0 && currentSale.set[1].severity_penalty == 0 && currentSale.set[2].severity_penalty == 0 && currentSale.set[3].severity_penalty == 0 && currentSale.set[4].severity_penalty == 0)
                                {
                                    continue;
                                }
                                if (csvFile.is_open())
                                {
                                    // Write headers to the CSV file
                                    csvFile << idFarmer << ","
                                            << "Cerials"
                                            << "," << currentSale.set[0].average_price << "," << currentSale.set[0].nb_kg_sold << "," << currentSale.set[0].severity_penalty << ",   "
                                            << "Dates"
                                            << "," << currentSale.set[1].average_price << "," << currentSale.set[1].nb_kg_sold << "," << currentSale.set[1].severity_penalty << ","
                                            << "Fruits"
                                            << ",    " << currentSale.set[2].average_price << "," << currentSale.set[2].nb_kg_sold << "," << currentSale.set[2].severity_penalty << ","
                                            << "Olives"
                                            << "," << currentSale.set[3].average_price << "," << currentSale.set[3].nb_kg_sold << "," << currentSale.set[3].severity_penalty << ","
                                            << "Vegetables"
                                            << "," << currentSale.set[4].average_price << ",     " << currentSale.set[4].nb_kg_sold << "," << currentSale.set[4].severity_penalty << "," << i + 1 << "," << year << "," << currentSale.water << "," << currentSale.electricity << endl;
                                }
                            }
                        }
            csvFile.close();
            return;
        }
    }
}

//
void bst_Year::reportSales(int year, int month, long id) const
{
    if (year < 1990 || year > 2022)
        throw out_of_range("invalid year");

    if (month < 1 || month > 12)
        throw out_of_range("invalid month ");
    BinaryNode *current = root;
    while (current != nullptr) // we need first to find the node of the specified year
    {
        if (year < current->element.year)
        {

            current = current->left;
        }
        else if (year > current->element.year)
        {

            current = current->right;
        }
        else
        { // after finding the year now we check if the farmer exist in this hash table
            cout << "---------------------------------------------------------------------------" << endl;
            if (current->element.sales[month - 1].contains(id))
            {
                // we print the sales of the farmer then
                Sales currentSale = current->element.sales[month - 1].getSales(id);
                cout << "The farmer  " << farmers[id - 1].farmer_fullName << " " << id << " has sold " << endl;
                if (current->element.sales[month - 1].contains(id))
                {
                    // we print the sales of the farmer then
                    Sales currentSale = current->element.sales[month - 1].getSales(id);
                    cout << "The farmer  " << farmers[id - 1].farmer_fullName << " " << id << " has sold " << endl;
                    for (int j = 0; j < 5; j++)
                    {
                        cout << "  Category          :" << currentSale.set[j].category_name << "\n"
                             << "  the average price : " << setprecision(2) << fixed << currentSale.set[j].average_price << "\n"
                             << "  number of kg      : " << setprecision(2) << fixed << currentSale.set[j].nb_kg_sold << "\n";
                    }
                    cout << "in the month " << month << " and year " << year << endl;
                }
                current = nullptr;
                cout << "---------------------------------------------------------------------------" << endl;
            }
            else
            {
                cout << "---------------------------------------------------------------------------" << endl;
                cout << "the farmer " << farmers[id - 1].farmer_fullName << " didn't work in the month : " << month << endl;
                current = nullptr;
                cout << "---------------------------------------------------------------------------" << endl;
                return;
            }
        }
    }
    cout <<"this year doesn't exist in our dataset" <<endl;
}

// getting the penalties of a specific farmer in a specific year and month
void bst_Year::reportPenalties(int year, int month, long id) const
{
     if (year < 1990 || year > 2022)
        throw out_of_range("invalid year");

    if (month < 1 || month > 12)
        throw out_of_range("invalid month ");

    BinaryNode *current = root;
    while (current != nullptr) // we need first to find the node of the specified year
    {
        if (year < current->element.year)
        {

            current = current->left;
        }
        else if (year > current->element.year)
        {

            current = current->right;
        }
        else
        { // after finding the year now we check if the farmer exist in this hash table
            cout << "---------------------------------------------------------------------------" << endl;
            if (current->element.sales[month - 1].contains(id))
            {
                // we print the sales of the farmer then
                Sales currentSale = current->element.sales[month - 1].getSales(id);
                cout << "The farmer  " << farmers[id - 1].farmer_fullName << " " << id << " has penalties in the categories:" << endl;
                for (int j = 0; j < 5; j++)
                {
                    cout << currentSale.set[j].category_name << ":" << currentSale.set[j].severity_penalty << endl;
                }
                cout << "in the month " << month << " in the year " << year << endl;

                current = nullptr;
                cout << "---------------------------------------------------------------------------" << endl;
            }
            else
            {
                cout << "the farmer " << farmers[id - 1].farmer_fullName << " didn't work in the month " << month << " and the year " << year << endl;
                current=nullptr;
                return;
            }
        }
    }
    cout <<"this year doesn't exist in our dataset" <<endl;
}

// getting the penalties of a specific farmer in a specific year
void bst_Year::reportPenalties(int year, long id) const
{
     if (year < 1990 || year > 2022)
        throw out_of_range("invalid year");

    BinaryNode *current = root;
    while (current != nullptr)
    {
        if (year < current->element.year)
            current = current->left;
        else if (year > current->element.year)
            current = current->right;

        else if (year == current->element.year)
        {
            cout << "---------------------------------------------------------------------------" << endl;
            for (int i = 0; i < 12; i++)
            {
                if (current->element.sales[i].contains(id))
                {
                    // we print the sales of the farmer then
                    Sales currentSale = current->element.sales[i].getSales(id);
                    cout << "The farmer  " << farmers[id - 1].farmer_fullName << " " << id << " has penalties in those categories: " << endl;
                    for (int j = 0; j < 5; j++)
                    {
                        cout << currentSale.set[j].category_name << ":" << currentSale.set[j].severity_penalty << endl;
                    }
                    cout << "in the month " << i + 1 << " in the year " << year << endl;
                }
                else
                {
                    cout << "the farmer " << farmers[id - 1].farmer_fullName << " didn't work in the month : " << i + 1 << endl;
                }
            }
            cout << "---------------------------------------------------------------------------" << endl;
            return;
        }
    }
    cout <<"this year doesn't exist in our dataset" <<endl;
}

void bst_Year ::reportArea(int year, int areaID) const
{
     if (year < 1990 || year > 2022)
        throw out_of_range("invalid year");

    std::ofstream csvFile("reportArea.csv");
    BinaryNode *current = root;
    // we need first to check if the year exist or no
    while (current != nullptr)
    {
        if (year < current->element.year)
            current = current->left;
        else if (year > current->element.year)
            current = current->right;
        else
        {
            for (const auto &idFarmer : areas[areaID])
            {
                for (int i = 0; i < 12; i++)
                {

                    Sales currentSale = current->element.sales[i].getSales(idFarmer);
                    if (currentSale.set[0].average_price == 0 && currentSale.set[1].average_price == 0 && currentSale.set[2].average_price == 0 && currentSale.set[3].average_price == 0 && currentSale.set[4].average_price == 0 && currentSale.set[0].nb_kg_sold == 0 && currentSale.set[1].nb_kg_sold == 0 && currentSale.set[2].nb_kg_sold == 0 && currentSale.set[3].nb_kg_sold == 0 && currentSale.set[4].nb_kg_sold == 0 && currentSale.set[0].severity_penalty == 0 && currentSale.set[1].severity_penalty == 0 && currentSale.set[2].severity_penalty == 0 && currentSale.set[3].severity_penalty == 0 && currentSale.set[4].severity_penalty == 0)
                    {
                        continue;
                    }
                    if (csvFile.is_open())
                    {
                        // Write headers to the CSV file
                        csvFile << idFarmer << ","
                                << "Cerials"
                                << "," << currentSale.set[0].average_price << "," << currentSale.set[0].nb_kg_sold << "," << currentSale.set[0].severity_penalty << ","
                                << "Dates"
                                << "," << currentSale.set[1].average_price << "," << currentSale.set[1].nb_kg_sold << "," << currentSale.set[1].severity_penalty << ","
                                << "Fruits"
                                << "," << currentSale.set[2].average_price << "," << currentSale.set[2].nb_kg_sold << "," << currentSale.set[2].severity_penalty << ","
                                << "Olives"
                                << "," << currentSale.set[3].average_price << "," << currentSale.set[3].nb_kg_sold << "," << currentSale.set[3].severity_penalty << ","
                                << "Vegetables"
                                << "," << currentSale.set[4].average_price << "," << currentSale.set[4].nb_kg_sold << "," << currentSale.set[4].severity_penalty << "," << i + 1 << "," << year << "," << currentSale.water << "," << currentSale.electricity << endl;
                    }
                }
            }
            csvFile.close();
            return;
        }
    }
}

// getting the sales of the farmers of a specific city in a specific year
void bst_Year::reportCity(int year, int cityId)
{
     if (year < 1990 || year > 2022)
        throw out_of_range("invalid year");


    std::ofstream csvFile("reportCity.csv");
    BinaryNode *current = root;
    // we need first to check if the year exist or no
    while (current != nullptr)
    {
        if (year < current->element.year)
            current = current->left;
        else if (year > current->element.year)
            current = current->right;
        else
        {
            for (const auto &areaID : cities[cityId])
                for (const auto &idFarmer : areas[areaID])
                {
                    cout << "hello" << endl;
                    for (int i = 0; i < 12; i++)
                    {

                        Sales currentSale = current->element.sales[i].getSales(idFarmer);
                        if (currentSale.set[0].average_price == 0 && currentSale.set[1].average_price == 0 && currentSale.set[2].average_price == 0 && currentSale.set[3].average_price == 0 && currentSale.set[4].average_price == 0 && currentSale.set[0].nb_kg_sold == 0 && currentSale.set[1].nb_kg_sold == 0 && currentSale.set[2].nb_kg_sold == 0 && currentSale.set[3].nb_kg_sold == 0 && currentSale.set[4].nb_kg_sold == 0 && currentSale.set[0].severity_penalty == 0 && currentSale.set[1].severity_penalty == 0 && currentSale.set[2].severity_penalty == 0 && currentSale.set[3].severity_penalty == 0 && currentSale.set[4].severity_penalty == 0)
                        {
                            continue;
                        }
                        if (csvFile.is_open())
                        {
                            // Write headers to the CSV file
                            csvFile << idFarmer << ","
                                    << "Cerials"
                                    << "," << currentSale.set[0].average_price << "," << currentSale.set[0].nb_kg_sold << "," << currentSale.set[0].severity_penalty << ","
                                    << "Dates"
                                    << "," << currentSale.set[1].average_price << "," << currentSale.set[1].nb_kg_sold << "," << currentSale.set[1].severity_penalty << ","
                                    << "Fruits"
                                    << "," << currentSale.set[2].average_price << "," << currentSale.set[2].nb_kg_sold << "," << currentSale.set[2].severity_penalty << ","
                                    << "Olives"
                                    << "," << currentSale.set[3].average_price << "," << currentSale.set[3].nb_kg_sold << "," << currentSale.set[3].severity_penalty << ","
                                    << "Vegetables"
                                    << "," << currentSale.set[4].average_price << "," << currentSale.set[4].nb_kg_sold << "," << currentSale.set[4].severity_penalty << "," << i + 1 << "," << year << "," << currentSale.water << "," << currentSale.electricity << endl;
                        }
                    }
                }
            csvFile.close();
            return;
        }
    }
}
// getting the penalties of the farmers of a specific wilaya in a specific year
void bst_Year::reportWilaya(int year, int wilayaID)
{
     if (year < 1990 || year > 2022)
        throw out_of_range("invalid year");


    std::ofstream csvFile("reportWilaya.csv");
    BinaryNode *current = root;
    // we need first to check if the year exist or no
    while (current != nullptr)
    {
        if (year < current->element.year)
            current = current->left;
        else if (year > current->element.year)
            current = current->right;
        else
        {
            for (const auto &cityId : wilayas[wilayaID])
                for (const auto &areaID : cities[cityId])
                    for (const auto &idFarmer : areas[areaID])
                    {
                        for (int i = 0; i < 12; i++)
                        {

                            Sales currentSale = current->element.sales[i].getSales(idFarmer);
                            if (currentSale.set[0].average_price == 0 && currentSale.set[1].average_price == 0 && currentSale.set[2].average_price == 0 && currentSale.set[3].average_price == 0 && currentSale.set[4].average_price == 0 && currentSale.set[0].nb_kg_sold == 0 && currentSale.set[1].nb_kg_sold == 0 && currentSale.set[2].nb_kg_sold == 0 && currentSale.set[3].nb_kg_sold == 0 && currentSale.set[4].nb_kg_sold == 0 && currentSale.set[0].severity_penalty == 0 && currentSale.set[1].severity_penalty == 0 && currentSale.set[2].severity_penalty == 0 && currentSale.set[3].severity_penalty == 0 && currentSale.set[4].severity_penalty == 0)
                            {
                                continue;
                            }
                            if (csvFile.is_open())
                            {
                                // Write headers to the CSV file
                                csvFile << idFarmer << ","
                                        << "Cerials"
                                        << "," << currentSale.set[0].average_price << "," << currentSale.set[0].nb_kg_sold << "," << currentSale.set[0].severity_penalty << ",   "
                                        << "Dates"
                                        << "," << currentSale.set[1].average_price << "," << currentSale.set[1].nb_kg_sold << "," << currentSale.set[1].severity_penalty << ","
                                        << "Fruits"
                                        << ",    " << currentSale.set[2].average_price << "," << currentSale.set[2].nb_kg_sold << "," << currentSale.set[2].severity_penalty << ","
                                        << "Olives"
                                        << "," << currentSale.set[3].average_price << "," << currentSale.set[3].nb_kg_sold << "," << currentSale.set[3].severity_penalty << ","
                                        << "Vegetables"
                                        << "," << currentSale.set[4].average_price << ",     " << currentSale.set[4].nb_kg_sold << "," << currentSale.set[4].severity_penalty << "," << i + 1 << "," << year << "," << currentSale.water << "," << currentSale.electricity << endl;
                            }
                        }
                    }
            csvFile.close();
            return;
        }
    }
}

// getting the penalties of the farmers of a specific city in a specific year
void bst_Year::penalty_farmers_city(int year, int cityId)
{
     if (year < 1990 || year > 2022)
        throw out_of_range("invalid year");


    std::ofstream csvFile("report_penalty_farmer_city.csv");
    BinaryNode *current = root;
    while (current != nullptr)
    {
        cout << "test" << endl;
        if (year < current->element.year)
            current = current->left;
        else if (year < current->element.year)
            current = current->right;
        else
        {
            for (const auto &areaID : cities[cityId])
            {
                for (const auto &idFarmer : areas[areaID])
                {
                    for (int i = 0; i < 12; i++)
                    {
                        Sales currentSale = current->element.sales[i].getSales(idFarmer);
                        if (currentSale.set[0].average_price == 0 && currentSale.set[1].average_price == 0 && currentSale.set[2].average_price == 0 && currentSale.set[3].average_price == 0 && currentSale.set[4].average_price == 0 && currentSale.set[0].nb_kg_sold == 0 && currentSale.set[1].nb_kg_sold == 0 && currentSale.set[2].nb_kg_sold == 0 && currentSale.set[3].nb_kg_sold == 0 && currentSale.set[4].nb_kg_sold == 0 && currentSale.set[0].severity_penalty == 0 && currentSale.set[1].severity_penalty == 0 && currentSale.set[2].severity_penalty == 0 && currentSale.set[3].severity_penalty == 0 && currentSale.set[4].severity_penalty == 0)
                        {
                            continue;
                        }
                        if (csvFile.is_open())
                        {
                            // Write headers to the CSV file
                            csvFile << idFarmer << ","
                                    << "Cerials"
                                    << "," << currentSale.set[0].severity_penalty << ","
                                    << "Dates"
                                    << "," << currentSale.set[1].severity_penalty << ","
                                    << "Fruits"
                                    << "," << currentSale.set[2].severity_penalty << ","
                                    << "Olives"
                                    << "," << currentSale.set[3].severity_penalty << ","
                                    << "Vegetables"
                                    << "," << currentSale.set[4].severity_penalty << endl;
                        }
                    }
                }
            }
            // Close the CSV file
            csvFile.close();
            return;
        }
    }
}

void bst_Year::penalty_farmers_Wilaya(int year, int wilayaID)
{
     if (year < 1990 || year > 2022)
        throw out_of_range("invalid year");


    std::ofstream csvFile("report_penalty_farmer_Wilaya.csv");
    BinaryNode *current = root;
    while (current != nullptr)
    {
        if (year < current->element.year)
            current = current->left;
        else if (year < current->element.year)
            current = current->right;
        else
        {
            for (const auto &cityID : wilayas[wilayaID])
                for (const auto &areaID : cities[cityID])
                {
                    for (const auto &idFarmer : areas[areaID])
                    {
                        for (int i = 0; i < 12; i++)
                        {
                            Sales currentSale = current->element.sales[i].getSales(idFarmer);
                            if (currentSale.set[0].average_price == 0 && currentSale.set[1].average_price == 0 && currentSale.set[2].average_price == 0 && currentSale.set[3].average_price == 0 && currentSale.set[4].average_price == 0 && currentSale.set[0].nb_kg_sold == 0 && currentSale.set[1].nb_kg_sold == 0 && currentSale.set[2].nb_kg_sold == 0 && currentSale.set[3].nb_kg_sold == 0 && currentSale.set[4].nb_kg_sold == 0 && currentSale.set[0].severity_penalty == 0 && currentSale.set[1].severity_penalty == 0 && currentSale.set[2].severity_penalty == 0 && currentSale.set[3].severity_penalty == 0 && currentSale.set[4].severity_penalty == 0)
                            {
                                continue;
                            }
                            if (csvFile.is_open())
                            {
                                // Write headers to the CSV file
                                csvFile << idFarmer << ","
                                        << "Cerials"
                                        << "," << currentSale.set[0].severity_penalty << ","
                                        << "Dates"
                                        << "," << currentSale.set[1].severity_penalty << ","
                                        << "Fruits"
                                        << "," << currentSale.set[2].severity_penalty << ","
                                        << "Olives"
                                        << "," << currentSale.set[3].severity_penalty << ","
                                        << "Vegetables"
                                        << "," << currentSale.set[4].severity_penalty << endl;
                            }
                        }
                    }
                }
            // Close the CSV file
            csvFile.close();
            return;
        }
    }
}

void bst_Year::reportFarmer(int farmerId) const
{
    cout << "The farmer name   :" << farmers[farmerId].farmer_fullName << endl;
    cout << "The farmer age    : " << farmers[farmerId].farmer_age << " years old " << endl;
    cout << "The farmer gender :" << farmers[farmerId].farmer_gender << endl;
    cout << "the farmer area   :" << farmers[farmerId].farmer_area << endl;
    cout << "The farmer SSN    :" << farmers[farmerId].farmer_SSN << endl;
    cout << "The number of helpers of the farmer :" << farmers[farmerId].nb_helpers << endl;
}
// Defining a function fill_areas to fill the areas vector with the appropriate farmers
//  ' IDs
void bst_Year::fill_areas(const bst_Year::Farmer &obj)
{
    int area = obj.farmer_area;
    areas[area].push_back(obj.farmer_Id);
}

// initializing the areas and cities and wilayas
void bst_Year::init(string file_path)
{
    ifstream file;
    file.open(file_path);
    if (!file)
    {
        cerr << "Error opening the file." << endl;
        return;
    }
    // creating a string which holds a single row in the file
    string line;

    //eliminating the header line
    getline(file, line);
    
    // before reaching the eof indicator
    while (getline(file, line))
    {
        // creating a string stream to simplify strings operations
        stringstream S(line);
        string wilaya;
        string city;
        string area;
        // Assume each line has two columns separated by a comma
        // retrieve the wilaya
        getline(S, wilaya, ',');
        // retrieve the city
        getline(S, city, ',');
        wilayas[stoi(wilaya)].push_back(stoi(city));
        // retrieve the area
        getline(S, area, ',');
        cities[stoi(city)].push_back(stoi(area));
    }
    file.close();
}

void bst_Year::read_farmers(string path)
{
    ifstream file;
    file.open(path);
    if (!file)
        cerr << "File located in " << path << "couldn't be opened!" << endl;
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream S(line);
        string id_farmer;   // to be converted
        string area_farmer; // to be converted
        string SSN_farmer;  // to be converted
        string fullName_farmer;
        string gender_farmer;
        string age_farmer;        // to be converted
        string nb_helpers_farmer; // to be converted
        getline(S, id_farmer, ',');
        getline(S, area_farmer, ',');
        getline(S, SSN_farmer, ',');
        getline(S, fullName_farmer, ',');
        getline(S, gender_farmer, ',');
        getline(S, age_farmer, ',');
        getline(S, nb_helpers_farmer, ',');
        // build an instance of Farmer
        Farmer current(stoll(id_farmer), stoi(area_farmer), stoll(SSN_farmer),
                       fullName_farmer, gender_farmer, stoi(age_farmer), stoi(nb_helpers_farmer));
        // push the instance of Farmer created to the vector containing all the farmers
        fill_farmers(current);
        // pass the instance of Farmer created to the function that matches each farmer
        // with their corresponding area
        fill_areas(current);
    }
}
/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void bst_Year::insert(const yearSales &x, BinaryNode *&t)
{
    if (t == nullptr)
    {
        t = new BinaryNode{x, nullptr, nullptr};
    }
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ; // Duplicate; do nothing
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void bst_Year::insert(yearSales &&x, BinaryNode *&t)
{
    if (t == nullptr)
        t = new BinaryNode{std::move(x), nullptr, nullptr};
    else if (x < t->element)
        insert(std::move(x), t->left);
    else if (t->element < x)
        insert(std::move(x), t->right);
    else
        ; // Duplicate; do nothing
}
/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void bst_Year::remove(const yearSales &x, BinaryNode *&t)
{
    if (t == nullptr)
        return; // Item not found; do nothing
    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr) // Two children
    {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else
    {
        BinaryNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}
/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */

bool bst_Year::contains(const yearSales &x, BinaryNode *t) const
{
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->left);
    else if (t->element < x)
        return contains(x, t->right);
    else
        return true; // Match
}
void bst_Year::makeEmpty(BinaryNode *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

vector<float> bst_Year::findSales(long id, int month, int year, bool& worked){
    vector<float> farmerSales = vector<float>(5);
    BinaryNode* temp = searchNode(year, root);
    if(temp && temp->element.sales[month-1].contains(id))
    {
        float avg_price;
        float nb_kgs;
        for(int i=0; i<5; ++i){
            avg_price = temp->element.sales[month-1].getSales(id).set[i].average_price;
            nb_kgs = temp->element.sales[month-1].getSales(id).set[i].nb_kg_sold;
            farmerSales[i] = nb_kgs * avg_price;
        }
        return farmerSales;
    }    
    //in case the year does not exist or the farmer didn't work in that month
    if(!temp->element.sales[month-1].contains(id))
        worked = false;
    farmerSales.clear();
    return farmerSales;
};
