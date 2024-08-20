#File two(SALES)
#farmer_id, category, average_price, nb_kg_sold , penalty
#month, year, electricity consumption(DA), water consumption(DA)
import random
category = ["Cereals", "Dates", "Fruits", "Olives", "Vegetables"]
penalty = [0, 1, 2, 3]

#price of cereals variates between  70 and 90
#price of dates variates between 250 and 800
#price of fruits variates between 100 and 500
#price of olives variates between 200 and 300
#price of vegies variates between 20 and 150


#nb of kilograms of vegies between 2600 and 
#nb of 

non_cereals_producers=(9, 16, 35, 18, 34, 6)
non_vegetables_producers = (31, 41, 25, 4, 12, 6, 40, 34, 16, 9, 26, 38)
non_olives_producers = (1, 11, 24, 37, 33)
non_fruits_producers = (1, 7, 8, 17, 18, 19, 20, 28, 32, 34, 37, 38, 39, 40, 41, 44)
dates_producers=(39, 57, 55, 58, 1, 8, 49, 30, 11, 12, 33, 40, 32, 45, 5, 17, 3, 37)

def calculateAveragePrice(cats):
    counter = 0
    for cat in cats:
        counter += cats[cat][0] * cats[cat][1]
    return counter

def calculateElectricityCost(avg):
    return round(avg*0.25, 2)
def calculateWaterCost(avg):
    return avg*0.1
#file name: sales file
#generating a function that generates data into a csv file
def generateData(size):
    with open("sales.csv", "w") as file:
        file.write("Farmer Id,Cereals,Average Price,Number Of kgs Sold,Ceareals Penalty,Dates,Average Price,Number Of kgs Sold,Dates Penalty,Fruits,Average Price,Number Of kgs Sold,Fruits Penalty,Olives,Average Price,Number Of kgs Sold,Olives Penalty,Vegetables,Average Price,Number Of kgs Sold,Vegetables Penalty,month,year,electricity consumption(DA),water consumption(DA)\n")
        for i in range(size):
            category = {
                "Cereals":[0, 0, 0], 
                "Dates":[0, 0, 0], 
                "Fruits":[0, 0, 0], 
                "Olives":[0, 0, 0], 
                "Vegetables":[0, 0, 0]
            }
            #generate Cereals array
            to_be_filled = random.randint(0,1)
            if(to_be_filled):
                average_price = round(random.uniform(70, 90), 2)
                nb_kgs_sold = round(random.uniform(100, 3000)) 
                penalty = random.randint(0, 3)
                category["Cereals"] = [average_price, nb_kgs_sold, penalty]
            #generate Dates array
            to_be_filled = random.randint(0,1)
            if(to_be_filled):
                average_price = round(random.uniform(250, 800), 2)
                nb_kgs_sold = round(random.uniform(500, 9000))
                penalty = random.randint(0, 3)
                category["Dates"] = [average_price, nb_kgs_sold, penalty]
            #generate Fruits array
            to_be_filled = random.randint(0,1)
            if(to_be_filled):
                average_price = round(random.uniform(100, 500), 2)
                nb_kgs_sold = round(random.uniform(800, 10000))
                penalty = random.randint(0, 3)
                category["Fruits"] = [average_price, nb_kgs_sold, penalty]
            #generate Olives array
            to_be_filled = random.randint(0,1)
            if(to_be_filled):
                average_price = round(random.uniform(200, 300), 2)
                nb_kgs_sold = round(random.uniform(200, 4000))
                penalty = random.randint(0, 3)
                category["Olives"] = [average_price, nb_kgs_sold, penalty]
            #generate Vegies array
            to_be_filled = random.randint(0,1)
            if(to_be_filled):
                average_price = round(random.uniform(20, 150), 2)
                nb_kgs_sold = round(random.uniform(2000, 30000))
                penalty = random.randint(0, 3)
                category["Vegetables"] = [average_price, nb_kgs_sold, penalty]
            farmer_id = random.randint(1, 200000)
            month = random.randint(1, 12)
            year = random.randint(1990, 2022)
            average = calculateAveragePrice(category)
            electricity = calculateElectricityCost(average)
            water = calculateWaterCost(average)
            file.write(f"{farmer_id},")
            #writing the different categories with their corresponding values
            for cat in category:
                file.write(f"{cat},")
                for item in category[cat]:
                    file.write(f"{item},")
            #writing the remaining information related to this specific farmer
#Penalty,month,year,electricity consumption(DA),water consumption(DA)
            file.write(f"{penalty},{month},{year},{electricity},{water}\n")


generateData(1000000)