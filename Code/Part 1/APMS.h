#include <iostream>
#include "SalesHashTable.h"
#include "winnertree.h"
#include "bst_Year.h"








//Please Make sure to setup the python environment for Matplotlibcpp,
//then uncomment this
//#include "matplotlibcpp.h"













using namespace std;

class APMS
{
public:
    APMS();
    ~APMS();

    void run();

private:
    winnertree *winners;
    bst_Year *sales;
    vector<double> runningTime = vector<double>(100);
    // helper functions :
    void menu();
    bool stay();
    void insert_new_farmer(Sales ob);
    void find_winner_by_year_month(int y, int m);
    void find_winner_by_year(int y);
    void find_winner_by_month(int m);

    void verify_id(int id);
    void reportFarmer(int id) const;
    void reportSales(int year, int month, long id);
    void reportSales(int year, long id);
    void reportPenalties(int year, int month, long id);
    void reportPenalties(int year, long id);
    void penalty_wilaya(int idWilaya, int year);
    void penalty_city(int idcity, int year);
    void reportArea(int year, int areaID);
    void reportCity(int year, int cityId);
    void reportWilaya(int year, int wilayaId);
    void reportCountry(int);
    void generateRunningTimeGraph();
    void runningTimeFindWinner();
    void runningTimeReportSale();
    void runningTimeReportPenalities();
    void runningTimeReportAreas();
    void generateSalesBarChart();
};