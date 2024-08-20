#include "winnertree_avl.h"

// the big five :

// default constructor
winnertree::winnertree() : data(), root(nullptr)
{
    root = nullptr;
}

// Copy constructor
winnertree::winnertree(const winnertree &other) : data(other.data), root(copyTree(other.root)) {}

// Move constructor
winnertree::winnertree(winnertree &&other) noexcept : data(std::move(other.data)), root(other.root)
{
    other.root = nullptr;
}

winnertree &winnertree::operator=(const winnertree &other) // Copy assignment operator
{
    if (this != &other)
    {
        data = other.data;
        root = copyTree(other.root);
    }
    return *this;
}

winnertree &winnertree::operator=(winnertree &&other) noexcept
{ // Move assignment operator
    // using the swap method that we learned in the TP sessions
    data = std::move(other.data);
    root = std::move(other.root);
    return *this;
}

// the destructor
winnertree::~winnertree()
{
    destroyTree(root);
   
}

// the purpose of this function is to store and check the winner of each category in each month of a given year
void winnertree::update_winner(const Sales &farmer)
{
    update_winner(farmer, root);
}
// the helper function of the update winner funcion :
void winnertree::update_winner(const Sales &farmer, winner_node *&temp)
{
    if (temp == nullptr)
    {
        /*
       Since we reached a point where the root becomes empty, so we didn't find any farmer
       corresponding to this year, then this farmer is the first and the only one (for this moment),
       so he is the winner of his the categories
       */

        winner_node *newnode = new winner_node();
        //   newnode.month_winner = vector<winnerCategory> (12);
        newnode->year = farmer.year;
        // This farmer is the winner in all the categories
        newnode->month_winner[farmer.month - 1].formula_veg_winner = calculateformula(farmer, 0);
        newnode->month_winner[farmer.month - 1].id_of_veg_winner = farmer.farmer_id;

        newnode->month_winner[farmer.month - 1].id_of_fruits_winner = farmer.farmer_id;
        newnode->month_winner[farmer.month - 1].formula_fruits_winner = calculateformula(farmer, 1);
        newnode->month_winner[farmer.month - 1].id_of_cereals_winner = farmer.farmer_id;
        newnode->month_winner[farmer.month - 1].formula_cereals_winner = calculateformula(farmer, 2);

        newnode->month_winner[farmer.month - 1].id_of_olives_winner = farmer.farmer_id;
        newnode->month_winner[farmer.month - 1].formula_olives_winner = calculateformula(farmer, 3);

        newnode->month_winner[farmer.month - 1].id_of_dates_winner = farmer.farmer_id;
        newnode->month_winner[farmer.month - 1].formula_dates_winner = calculateformula(farmer, 4);

        temp = newnode; // Insert this node with the new year

        return;

        // we traversed all the list and we didn't found the corresponding year so
    }
    int currentYear = farmer.year;

    if (currentYear > temp->year)
    {
        update_winner(farmer, temp->right);
    }
    else if (currentYear < temp->year)
    {
        update_winner(farmer, temp->left);
    }
    else
    {
        // year found
        int month = farmer.month - 1;

        double formula = calculateformula(farmer, 4);
        if (formula > data.month_winner[month].formula_veg_winner)
        {
            temp->month_winner[month].formula_veg_winner = formula;
            temp->month_winner[month].id_of_veg_winner = farmer.farmer_id;
        }

        formula = calculateformula(farmer, 2);
        if (formula > data.month_winner[month].formula_fruits_winner)
        {
            temp->month_winner[month].formula_fruits_winner = formula;
            temp->month_winner[month].id_of_fruits_winner = farmer.farmer_id;
        }

        formula = calculateformula(farmer, 0);
        if (formula > data.month_winner[month].formula_cereals_winner)
        {
            temp->month_winner[month].formula_cereals_winner = formula;
            temp->month_winner[month].id_of_cereals_winner = farmer.farmer_id;
        }

        formula = calculateformula(farmer, 1);
        if (formula > data.month_winner[month].formula_dates_winner)
        {
            temp->month_winner[month].formula_dates_winner = formula;
            temp->month_winner[month].id_of_dates_winner = farmer.farmer_id;
        }

        formula = calculateformula(farmer, 3);
        if (formula > data.month_winner[month].formula_olives_winner)
        {
            temp->month_winner[month].formula_olives_winner = formula;
            temp->month_winner[month].id_of_olives_winner = farmer.farmer_id;
        }

        return;
    }
}

// find the winner in a given year and in a given month

winnerCategory winnertree::find_winner_by_year_month(int y, int m)
{
   if (y < 1990 || y > 2022)
    {
       throw out_of_range("invalid year");
    }
    if (m > 12 || m < 1)
    {
        throw out_of_range("invalid_month");
    }

    winner_node *temp = root;

    while (temp != nullptr)
    {
        if (y > temp->year)
            temp = temp->right;
        else if (y < temp->year)
            temp = temp->left;
        else
        {
            if ((temp->month_winner[m - 1]).isvalid())
            {

                cout << "---------------------------------------------------------------------------" << endl;
                cout << "The winners of " << m << " / " << y << " are:" << endl;
                cout << "---------------------------------------------------------------------------" << endl;
                cout << temp->month_winner[m - 1];
                cout << "---------------------------------------------------------------------------" << endl;
                return temp->month_winner[m - 1];
            }
            else
            {
                cout << "---------------------------------------------------------------------------" << endl;
                cout << "There are no winners in " << m << " / " << y << " yet." << endl;
                cout << "---------------------------------------------------------------------------" << endl;
            }
        }
    }

    // Output to console for immediate visibility
    cout << "---------------------------------------------------------------------------" << endl;
    cout << "Year not found" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    return winnerCategory();
}

// find the winner in a given year
vector<winnerCategory> winnertree::find_winner_by_year(int y)
{
    // if (y < 1962 || y > 2024)
    //     throw underflow_error("");
    vector<winnerCategory> result(12);
    cout << "***************************************************************************" << endl;
    cout << "The winners in all the months in the year " << y << " are:" << endl;
    cout << "***************************************************************************" << endl;
    for (int i = 1; i <= 12; i++)
    {
        result.push_back(find_winner_by_year_month(y, i));
    }
    return result;
}


// function to calculate the formula needed to compare the farmers
double winnertree::calculateformula(Sales farmer, int category)
{
    return farmer.set[category].nb_kg_sold * farmer.set[category].average_price * (1 - farmer.set[category].severity_penalty / 100) - (farmer.electricity + farmer.water) / 5;
}

// return true if the tree is empty
bool winnertree::isEmpty() const
{
    return root == nullptr;
}

// find the winner in a given month
vector<winnerCategory> winnertree::find_winner_by_month(int m)
{
    winner_node *temp = root;
    vector<winnerCategory> result(10);

   
    if (m < 1 || m > 12)
    {
        throw out_of_range("invalid month");
    }
    
    // Output to console for immediate visibility
    cout << "*****************************************************************************************************************************************************************************************************************" << endl;
    cout << "The winners in all the years corresponding to the month " << m << " are:" << endl;
    cout << "*****************************************************************************************************************************************************************************************************************" << endl;
    find_winner_by_month(m, result, temp);
    return result;
}

// find the winner in a given month and in a given year  (helper function )
void winnertree::find_winner_by_month(int m, vector<winnerCategory> &result, winner_node *root)
{

    if (root == nullptr)
        return;
    // inorder traversal of the tree :
    find_winner_by_month(m, result, root->left);

    // process the root :
    cout << root->month_winner[m];
    result.push_back(root->month_winner[m]);

    find_winner_by_month(m, result, root->right);
}

winner_node *winnertree::copyTree(winner_node *node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    winner_node *newNode = new winner_node(*node);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

void winnertree::destroyTree(winner_node *node)
{
    if (node == nullptr)
    {
        return;
    }
    destroyTree(node->left);
    destroyTree(node->right);
    node->height = -1;
    delete node;
}

winner_node *winnertree::insert(const winner_node &element, winner_node *&t)
{

    if (t == nullptr)
    {
        t = new winner_node();
        t->year = element.year;

        t->month_winner = element.month_winner;
        t->left = nullptr;
        t->right = nullptr;
    }
    else if (element.year < t->year)
    {
        insert(element, t->left);
    }
    else if (element.year > t->year)
    {
        insert(element, t->right);
    }
    balance(t);
    return t;
}

void winnertree::insert(const winner_node &element)
{
    insert(element, root);
}

void winnertree::balance(winner_node *&t)
{
    if (t == nullptr)
        return;

    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        // Left left imbalance
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        // Left right imbalance
        else
            doubleWithLeftChild(t);
    else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
        // Right right imbalance
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);
        // Right left imbalance
        else
            doubleWithRightChild(t);

    // Update the height
    t->height = max(height(t->left), height(t->right)) + 1;
}

void winnertree::rotateWithLeftChild(winner_node *&k2)
{
    winner_node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

// right right imbalance
void winnertree::rotateWithRightChild(winner_node *&k1)
{
    winner_node *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

// Left right imbalance
void winnertree::doubleWithLeftChild(winner_node *&k3)
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

// right left imbalance
void winnertree::doubleWithRightChild(winner_node *&k1)
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

int winnertree::height(winner_node *N)
{
    if (N == NULL)
        return -1;
    return N->height;
}


// in the winner category struct we have : 
winnerCategory::winnerCategory()
    : id_of_veg_winner(0),
      formula_veg_winner(0),
      id_of_fruits_winner(0),
      formula_fruits_winner(0),
      id_of_cereals_winner(0),
      formula_cereals_winner(0),
      id_of_olives_winner(0),
      formula_olives_winner(0),
      id_of_dates_winner(0),
      formula_dates_winner(0) {}




// oveloading the operator << for the struct winnerCategory 
ostream &operator<<(std::ostream &os, const winnerCategory &winner)
{
    os << "+------------------------+" << endl;
    os << "|      Winners Table     |" << endl;
    os << "+------------------------+" << endl <<endl;

    if (winner.formula_veg_winner > 0)
    {
        os << "|  Vegetables Category   |" << endl;
        os << "+------------------------+" << endl;
        os << "| ID of Veg Winner:     " << winner.id_of_veg_winner <<" | "<< endl;
        os << "| Formula Veg Winner:   " << setprecision(2) << fixed << winner.formula_veg_winner << "| "<< endl;
        os << "+------------------------+" << endl << endl;
    }

    if (winner.formula_fruits_winner > 0)
    {
        os << "|    Fruits Category     |" << endl;
        os << "+------------------------+" << endl;
        os << "| ID of Fruits Winner:   " << winner.id_of_fruits_winner<<" | " << endl;
        os << "| Formula Fruits Winner: " << setprecision(2) << fixed << winner.formula_fruits_winner<<" | " << endl;
        os << "+------------------------+" << endl << endl;
    }

    if (winner.formula_cereals_winner > 0)
    {
        os << "|    Cereals Category    |" << endl;
        os << "+------------------------+" << endl;
        os << "| ID of Cereals Winner:  " << winner.id_of_cereals_winner<<" | " << endl;
        os << "| Formula Cereals Winner " << setprecision(2) << fixed << winner.formula_cereals_winner<<" | " << endl;
        os << "+------------------------+" << endl << endl;
    }

    if (winner.formula_olives_winner > 0)
    {
        os << "|    Olives Category     |" << endl;
        os << "+------------------------+" << endl;
        os << "| ID of Olives Winner:   " << winner.id_of_olives_winner<<" | " << endl;
        os << "| Formula Olives Winner: " << setprecision(2) << fixed << winner.formula_olives_winner<<" | " << endl;
        os << "+------------------------+" << endl << endl;
    }

    if (winner.formula_dates_winner > 0)
    {
        os << "|    Dates Category      |" << endl;
        os << "+------------------------+" << endl;
        os << "| ID of Dates Winner:    " << winner.id_of_dates_winner <<" | "<< endl;
        os << "| Formula Dates Winner:  " << setprecision(2) << fixed << winner.formula_dates_winner <<" | "<< endl;
        os << "+------------------------+" << endl << endl;
    }

    return os;
}



// in the winner node struct we have  :

winner_node::winner_node() : year(0)
{
    left = nullptr;
    right = nullptr;
}
ostream &operator<<(std::ostream &os, const winner_node &node)
{
    os << "Year: " << node.year << endl;

    for (int i = 0; i < node.month_winner.size(); i++)
    {
        os << "the winner in the month : " << i + 1 << "are :" << endl;
        os << node.month_winner[i];
    }

    return os;
}




bool winnerCategory::isvalid()
{
    if (id_of_cereals_winner == 0 && id_of_dates_winner == 0 && id_of_fruits_winner == 0 && id_of_olives_winner == 0 && id_of_veg_winner == 0)
        return false;

    return true;
}


winner_node &winner_node::operator=(const winner_node &other)
{
    if (this != &other) // self-assignment check
    {
        year = other.year;
        month_winner = other.month_winner;
        left = other.left;
        right = other.right;
        height = other.height;
    }
    return *this;
}
