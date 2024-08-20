#include "APMS.h"
#include <chrono>
#include <iostream>









// Please Make sure to setup the python environment for Matplotlibcpp,
// then uncomment this
// namespace plt = matplotlibcpp;








APMS::APMS()
{
    winners = new winnertree();
    sales = new bst_Year();
    string Path = "../Data/sales.csv";
    ifstream file(Path);
    int aya = 10000;
    string line;
    int counter = 0;
    // reading from the file and store the line in a string
    getline(file, line);
    auto start = chrono::high_resolution_clock::now();
    while (getline(file, line))
    {

        stringstream ss(line);
        string token;
        string tokens[26];
        int count = 0;

        while (getline(ss, token, ','))
        {
            tokens[count] = token;
            count++;
        }

        // we create a categories array to store the categories information
        category categories[5];
        int count_0 = 0; // to check if the categories are all null
        int pos = 0;

        for (int i = 0; i < 5; i++)
        { // filling the categories
            categories[i].category_name = tokens[pos + 1];
            categories[i].average_price = stod(tokens[pos + 2]);
            categories[i].nb_kg_sold = stod(tokens[pos + 3]);
            categories[i].severity_penalty = stoi(tokens[pos + 4]);
            pos += 4;
            if (categories[i].average_price == 0 && categories[i].nb_kg_sold == 0 && categories[i].severity_penalty == 0)
            {
                count_0++;
            }
        }
        if (count_0 == 5)
        { // if a line doesn't contain any sale (all the sales for each category = 0 ) then skip
            counter++;
            if (counter == aya)
            {
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
                runningTime[(aya / 10000) - 1] = duration.count();
                aya += 10000;
            }
        }
        else
        {

            long id = stol(tokens[0]);
            int month = stoi(tokens[22]);
            int year = stoi(tokens[23]);
            double electricity = stod(tokens[24]);
            double water = stod(tokens[25]);
            Sales obj(id, categories, month, year, electricity, water);
            counter++;
            // cout << counter << endl;
            winners->update_winner(obj);
            sales->insert(obj);
            if (counter == aya)
            {
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
                runningTime[(aya / 10000) - 1] = duration.count();
                aya += 10000;
            }
        }
    }
    file.close();
}

APMS::~APMS()
{
    delete winners; // call the destructor of tree_winner
    delete sales;   // call the destructor of the year sales
}

void APMS::find_winner_by_year_month(int y, int m)
{
    winners->find_winner_by_year_month(y, m);
}

void APMS::find_winner_by_year(int y)
{
    winners->find_winner_by_year(y);
}

void APMS::find_winner_by_month(int m)
{
    winners->find_winner_by_month(m);
}

void APMS::reportSales(int year, int month, long id)
{
    sales->reportSales(year, month, id);
}
void APMS::reportSales(int year, long id)
{
    sales->reportSales(year, id);
}
void APMS::reportPenalties(int year, int month, long id)
{
    sales->reportPenalties(year, month, id);
}
void APMS::reportPenalties(int year, long id)
{
    sales->reportPenalties(year, id);
}
void APMS::reportArea(int year, int areaID)
{
    sales->reportArea(year, areaID);
}
void APMS::reportCity(int year, int cityID)
{
    sales->reportCity(year, cityID);
}
void APMS::reportWilaya(int year, int wilayaID)
{
    sales->reportWilaya(year, wilayaID);
}

void APMS::reportFarmer(int id) const
{
    sales->reportFarmer(id);
}

// void APMS::reportCountry(int year)
// {
//     sales->reportCountry(year);
// }
void APMS::insert_new_farmer(Sales ob)
{
    sales->insert(ob);
    winners->update_winner(ob);
}

// display all the penalties aply to all the farmers in a specific wilaya
void APMS::penalty_wilaya(int idWilaya, int year)
{
    sales->penalty_farmers_Wilaya(year, idWilaya);
}
void APMS::reportCountry(int year)
{
    sales->reportCountry(year);
}
// display all the penalties aply to all the farmers in a specific city
void APMS::penalty_city(int idcity, int year)
{
    sales->penalty_farmers_city(year, idcity);
}

void APMS::verify_id(int id)
{
    if (id < 0 || id > 200000)
    {
        cout << "this id doesn't exist in our dataset , the IDs range from 1 to 200 000" << endl;
        throw out_of_range("");
    }
}

void APMS::menu()
{
    cout << "*** choose one of the following : " << endl;
    cout << "  0 : to exit the code ... " << endl;
    cout << "  1 : Getting the sales of a specific farmer in a specific year and month " << endl;
    cout << "  2 : Getting the sales of a specific farmer in a specific year" << endl;
    cout << "  3 : getting the penalties of a specific farmer in a specific year and month" << endl;
    cout << "  4 : getting the penalties of a specific farmer in a specific year" << endl;
    cout << "  5 : display all the penalties applied to all the farmers in a specific wilaya " << endl;
    cout << "  6 : display all the penalties applied to all the farmers in a specific city" << endl;
    cout << "  7 : getting the sales of the farmers of a specific area in a specific year" << endl;
    cout << "  8 : getting the sales of the farmers of a specific city in a specific year" << endl;
    cout << "  9 : getting the sales of the farmers of a specific wilaya in a specific year" << endl;
    cout << " 10 : getting the sales of the farmers in the whole contry in a specific year" << endl;
    cout << " 11 : display  personal information of any farmer " << endl;
    cout << " 12 : finding the winner in a specific month and in a spesific year " << endl;
    cout << " 13 : finding the winner in a specific month in all the years  " << endl;
    cout << " 14 :finding the winner in a spesific year in all the monthes " << endl;
    cout << " 15 : add a new sale of a farmer to the dataset  " << endl;
    cout << " 16 : Generate a graph for the running time of inserting a sale based on the input size " << endl;
    cout << " 17 : Determining the running time for find winner in a randomly generated year(in microseconds) " << endl;
    cout << " 18 : Determining the running time for the report sale operation in a randomly generated year and month(in microseconds)" << endl;
    cout << " 19 : Determining the running time for the report penalties operation concerning a farmer with a randomly generated ID in a random month and year(in microseconds) " << endl;
    cout << " 20 : Determining the running time for the report areas operation in a random year and area(in microseconds) " << endl;
    cout << " 21 : Generating a bar chart representing the sales of a given farmer in all the five categories on a specific month and year " << endl;
}

bool APMS::stay()
{
    cout << "do you want to continue ?  , type 0 to exit , 1 to continue ... " << endl;
    int cont;
    cin >> cont;

    if (cont == 0)
    {
        cout << "thank you for trying our program :) " << endl;
        cout << "***************** go east go west , ensia is always the best *****************" << endl;
        return false;
    }
    return true;
}
// this array has all the existing areas in the country to perform validity checking on the id of the area entered by the user
// The total number of areas is 1542
vector<int> idAreas{1, 6, 13, 16, 17, 18, 27, 10, 28, 2, 4, 22, 26, 9, 20, 21, 39, 54, 55, 56, 57,
                    62, 32, 42, 44, 40, 61, 33, 37, 49, 38, 46, 53, 35, 50, 58, 31, 36, 63, 29, 59,
                    60, 43, 47, 34, 48, 51, 41, 52, 30, 45, 79, 68, 78, 70, 84, 75, 76, 65, 72, 77,
                    85, 86, 66, 67, 73, 69, 74, 87, 71, 64, 82, 83, 80, 81, 94, 112, 89, 96, 116, 93,
                    109, 110, 99, 114, 88, 90, 98, 101, 92, 103, 105, 104, 108, 97, 111, 115, 106, 95,
                    100, 107, 113, 91, 102, 123, 136, 154, 141, 145, 152, 155, 147, 167, 177, 151, 174,
                    119, 128, 132, 135, 162, 171, 127, 153, 165, 120, 173, 117, 134, 166, 175, 137, 142,
                    143, 129, 146, 126, 130, 122, 125, 149, 121, 133, 157, 138, 144, 168, 118, 124, 150,
                    158, 131, 156, 172, 159, 176, 139, 140, 160, 163, 164, 169, 148, 161, 170, 187, 210,
                    184, 188, 202, 214, 226, 209, 215, 219, 194, 217, 224, 179, 204, 180, 197, 221, 185,
                    228, 178, 189, 220, 181, 195, 205, 218, 183, 193, 208, 211, 190, 192, 222, 182, 196,
                    216, 223, 186, 206, 203, 199, 212, 213, 225, 227, 200, 201, 229, 198, 207, 191, 233,
                    243, 230, 238, 244, 260, 251, 241, 248, 253, 262, 231, 245, 246, 236, 239, 234, 235,
                    249, 261, 250, 252, 254, 256, 257, 242, 247, 264, 268, 275, 278, 272, 277, 280, 281,
                    263, 270, 276, 267, 288, 289, 292, 293, 286, 287, 304, 285, 295, 306, 297, 303, 284,
                    294, 302, 296, 301, 290, 298, 308, 300, 307, 291, 299, 305, 313, 315, 321, 332, 348,
                    316, 326, 337, 335, 350, 320, 322, 333, 338, 340, 353, 329, 343, 319, 334, 342, 351,
                    310, 317, 327, 328, 344, 311, 312, 314, 318, 330, 345, 309, 323, 336, 339, 347, 352,
                    324, 325, 331, 341, 346, 349, 355, 361, 354, 359, 362, 390, 369, 378, 372, 391, 370,
                    379, 381, 385, 368, 382, 383, 366, 371, 373, 367, 384, 365, 376, 377, 389, 364, 375,
                    386, 374, 380, 387, 388, 443, 396, 397, 398, 405, 416, 431, 433, 409, 432, 412, 419,
                    438, 442, 406, 428, 429, 401, 407, 415, 400, 439, 440, 392, 395, 418, 408, 435, 421,
                    430, 444, 420, 423, 414, 417, 434, 402, 437, 425, 426, 413, 427, 410, 436, 403, 422,
                    393, 399, 411, 394, 404, 424, 441, 483, 464, 466, 478, 446, 451, 468, 445, 452, 457,
                    470, 447, 461, 467, 472, 455, 475, 480, 485, 465, 473, 479, 448, 456, 482, 449, 453,
                    460, 463, 476, 459, 474, 486, 469, 477, 484, 454, 462, 481, 450, 458, 471, 549, 487,
                    490, 502, 503, 514, 532, 491, 496, 518, 520, 536, 548, 523, 526, 528, 506, 519, 524,
                    551, 553, 492, 529, 530, 500, 550, 497, 539, 545, 531, 542, 499, 508, 509, 510, 512,
                    516, 522, 527, 489, 493, 538, 547, 488, 498, 504, 507, 525, 535, 544, 505, 513, 515,
                    533, 517, 540, 543, 546, 494, 501, 537, 495, 534, 541, 511, 521, 552, 556, 582, 585,
                    605, 557, 567, 572, 596, 601, 564, 565, 576, 589, 604, 562, 563, 571, 580, 560, 570,
                    581, 597, 561, 592, 606, 583, 588, 591, 594, 555, 558, 568, 569, 574, 584, 595, 566,
                    598, 609, 587, 602, 603, 593, 600, 607, 608, 610, 559, 577, 578, 579, 590, 554, 573,
                    575, 586, 599, 624, 614, 633, 634, 645, 616, 629, 639, 617, 619, 611, 625, 627, 623,
                    631, 636, 640, 641, 628, 635, 643, 613, 620, 632, 622, 637, 642, 618, 621, 626, 612,
                    638, 644, 646, 615, 630, 662, 656, 668, 660, 674, 650, 651, 659, 665, 672, 647, 652,
                    657, 670, 658, 667, 666, 671, 661, 669, 649, 653, 655, 664, 648, 654, 663, 673, 729,
                    678, 703, 722, 683, 695, 718, 690, 698, 708, 730, 687, 728, 712, 723, 688, 706, 710,
                    692, 704, 681, 691, 693, 696, 675, 676, 707, 720, 686, 721, 734, 680, 709, 717, 724,
                    684, 685, 699, 701, 713, 732, 733, 702, 714, 725, 726, 727, 677, 679, 689, 697, 711,
                    716, 682, 694, 700, 705, 715, 719, 731, 745, 735, 742, 746, 738, 750, 740, 744, 747,
                    748, 736, 739, 741, 737, 743, 749, 772, 773, 785, 754, 762, 768, 752, 755, 765, 767,
                    771, 756, 757, 769, 760, 763, 764, 776, 777, 779, 774, 788, 766, 770, 780, 783, 787,
                    751, 759, 784, 758, 782, 761, 775, 786, 753, 778, 781, 824, 791, 820, 838, 796, 813,
                    839, 840, 803, 812, 835, 836, 790, 807, 823, 827, 799, 809, 826, 794, 829, 830, 831,
                    798, 805, 816, 837, 792, 804, 814, 811, 817, 833, 834, 815, 818, 819, 789, 808, 825,
                    828, 793, 800, 810, 821, 795, 797, 802, 806, 801, 822, 832, 842, 850, 843, 849, 852,
                    848, 851, 846, 841, 845, 847, 844, 859, 871, 856, 861, 882, 854, 855, 886, 857, 862,
                    876, 858, 860, 866, 868, 870, 875, 863, 872, 884, 867, 873, 880, 853, 865, 878, 881,
                    864, 869, 874, 877, 879, 883, 885, 891, 892, 894, 890, 898, 888, 893, 897, 887, 889,
                    895, 896, 919, 931, 959, 904, 922, 945, 960, 899, 925, 927, 942, 951, 903, 924, 940,
                    907, 921, 948, 900, 915, 916, 958, 911, 928, 952, 902, 917, 944, 918, 954, 955, 956,
                    929, 934, 947, 920, 930, 935, 909, 912, 914, 926, 936, 937, 910, 939, 950, 905, 913,
                    953, 906, 941, 946, 932, 949, 961, 962, 901, 923, 933, 957, 908, 938, 943, 979, 965,
                    970, 973, 972, 977, 992, 967, 981, 987, 991, 964, 975, 985, 983, 986, 993, 968, 971,
                    988, 963, 974, 980, 982, 969, 984, 989, 990, 966, 976, 978, 994, 1023, 1013, 1025,
                    1029, 1040, 1016, 1024, 1026, 1027, 1038, 1012, 1015, 1019, 1008, 1014, 1017, 1028,
                    998, 1000, 1004, 1009, 1018, 1002, 1007, 1033, 995, 1035, 1006, 1011, 1032, 1003,
                    1030, 1034, 1039, 1001, 1022, 1031, 1041, 996, 997, 999, 1005, 1036, 1020, 1021,
                    1010, 1037, 1069, 1050, 1055, 1065, 1057, 1061, 1086, 1079, 1083, 1085, 1056, 1073,
                    1088, 1044, 1075, 1080, 1063, 1067, 1068, 1070, 1082, 1052, 1059, 1066, 1043, 1045,
                    1064, 1076, 1047, 1048, 1062, 1042, 1058, 1049, 1051, 1084, 1046, 1074, 1077, 1053,
                    1087, 1054, 1060, 1071, 1072, 1078, 1081, 1101, 1102, 1100, 1096, 1089, 1095, 1103,
                    1093, 1131, 1114, 1124, 1127, 1116, 1125, 1126, 1122, 1123, 1134, 1113, 1133, 1110,
                    1115, 1128, 1112, 1118, 1120, 1129, 1117, 1121, 1132, 1135, 1111, 1119, 1130, 1144,
                    1152, 1142, 1150, 1141, 1151, 1149, 1145, 1136, 1137, 1146, 1139, 1147, 1157, 1143,
                    1148, 1140, 1138, 1153, 1154, 1155, 1156, 1162, 1159, 1160, 1163, 1166, 1165, 1187,
                    1191, 1171, 1188, 1195, 1168, 1179, 1181, 1185, 1189, 1164, 1197, 1167, 1170, 1176,
                    1180, 1194, 1174, 1177, 1184, 1190, 1175, 1182, 1186, 1196, 1172, 1173, 1178, 1193,
                    1169, 1183, 1192, 1206, 1209, 1227, 1204, 1205, 1207, 1212, 1220, 1203, 1211, 1217,
                    1229, 1200, 1223, 1225, 1218, 1219, 1208, 1214, 1222, 1228, 1199, 1202, 1224, 1226,
                    1198, 1201, 1210, 1213, 1215, 1216, 1221, 1230, 1236, 1246, 1253, 1231, 1237, 1247,
                    1249, 1233, 1234, 1243, 1244, 1245, 1250, 1251, 1238, 1240, 1248, 1239, 1241, 1242,
                    1232, 1235, 1252, 1254, 1255, 1269, 1276, 1257, 1258, 1259, 1273, 1271, 1275, 1261,
                    1263, 1266, 1264, 1268, 1272, 1274, 1260, 1277, 1262, 1265, 1256, 1267, 1270, 1285,
                    1290, 1283, 1294, 1299, 1278, 1286, 1297, 1304, 1287, 1298, 1280, 1288, 1289, 1307,
                    1279, 1282, 1305, 1291, 1301, 1292, 1295, 1320, 1319, 1325, 1327, 1310, 1315, 1318,
                    1326, 1308, 1323, 1311, 1313, 1322, 1328, 1312, 1314, 1317, 1321, 1309, 1316, 1324,
                    1349, 1329, 1336, 1347, 1334, 1337, 1330, 1341, 1332, 1350, 1353, 1333, 1335, 1342,
                    1339, 1344, 1348, 1331, 1346, 1354, 1338, 1345, 1352, 1340, 1343, 1351, 1382, 1369,
                    1375, 1374, 1377, 1381, 1355, 1368, 1376, 1364, 1370, 1378, 1380, 1359, 1365, 1373,
                    1366, 1367, 1357, 1360, 1361, 1371, 1356, 1362, 1379, 1358, 1363, 1372, 1386, 1398,
                    1405, 1395, 1413, 1385, 1390, 1400, 1394, 1402, 1409, 1388, 1403, 1407, 1383, 1401,
                    1414, 1389, 1392, 1404, 1412, 1396, 1397, 1391, 1406, 1399, 1408, 1387, 1410, 1411,
                    1384, 1393, 1417, 1425, 1442, 1428, 1439, 1440, 1446, 1415, 1420, 1437, 1429, 1430,
                    1431, 1421, 1434, 1441, 1435, 1449, 1416, 1433, 1447, 1422, 1432, 1443, 1418, 1419,
                    1444, 1436, 1445, 1450, 1426, 1427, 1448, 1423, 1424, 1438, 1460, 1451, 1455, 1458,
                    1452, 1462, 1461, 1454, 1459, 1453, 1456, 1457, 1466, 1485, 1472, 1477, 1478, 1480,
                    1464, 1481, 1486, 1489, 1471, 1474, 1483, 1490, 1470, 1473, 1475, 1479, 1482, 1463,
                    1465, 1467, 1468, 1469, 1476, 1488, 1484, 1487, 1496, 1493, 1491, 1501, 1502, 1497,
                    1503, 1492, 1494, 1500, 1508, 1533, 1521, 1525, 1526, 1529, 1514, 1527, 1510, 1523,
                    1536, 1506, 1513, 1515, 1530, 1509, 1511, 1541, 1512, 1519, 1531, 1507, 1517, 1534,
                    1537, 1505, 1518, 1516, 1522, 1504, 1520, 1538, 1540, 1532, 1539, 1524, 1528, 1535,
                    7, 14, 19, 15, 24, 11, 25, 3, 8, 12, 5, 23, 237, 240, 255, 232, 258, 259, 274, 279,
                    265, 282, 271, 269, 266, 273, 283, 360, 357, 358, 356, 363, 1099, 1106, 1108, 1109,
                    1092, 1094, 1090, 1098, 1105, 1091, 1107, 1097, 1104, 1158, 1161, 1284, 1296, 1302,
                    1303, 1281, 1293, 1300, 1306, 1495, 1499, 1498};

// a vector for all the possible cities ids
// The total number of cities is 340
vector<int> idCities{
    101, 103, 104, 108, 109, 111, 112, 115, 116, 123, 125, 201, 202, 204, 206, 207, 210, 212, 220, 222, 223, 229, 230, 232, 301, 302, 304, 306, 307, 310, 313, 314, 319, 321, 401, 402, 403, 406, 408, 411, 412, 416, 417, 422, 424, 425, 501, 504, 505, 506, 507, 508, 509, 516, 519, 529, 530, 535, 536, 542, 543, 544, 545, 547, 550, 551, 553, 601, 602, 607, 608, 611, 617, 620, 622, 624, 625, 626, 627, 629, 634, 636, 639, 640, 644, 650, 701, 705, 708, 711, 712, 715, 717, 719, 720, 721, 724, 726, 801, 803, 806, 807, 810, 811, 812, 813, 814, 817, 818, 821, 901, 903, 904, 905, 907, 912, 914, 916, 917, 922, 1001, 1004, 1005, 1012, 1013, 1015, 1018, 1033, 1035, 1036, 1037, 1038, 1101, 1102, 1103, 1104, 1106, 1107, 1201, 1202, 1203, 1205, 1209, 1210, 1211, 1212, 1213, 1219, 1220, 1301, 1303, 1304, 1306, 1307, 1313, 1317, 1318, 1320, 1324, 1326, 1327, 1335, 1338, 1339, 1340, 1341, 1344, 1350, 1351, 1401, 1402, 1406, 1413, 1414, 1415, 1416, 1421, 1427, 1428, 1429, 1433, 1434, 1435, 1501, 1502, 1509, 1510, 1511, 1517, 1518, 1521, 1522, 1524, 1529, 1532, 1534, 1536, 1537, 1538, 1540, 1547, 1548, 1550, 1552, 1602, 1605, 1609, 1611, 1613, 1614, 1617, 1620, 1636, 1638, 1644, 1649, 1652, 1701, 1704, 1707, 1708, 1714, 1717, 1719, 1720, 1725, 1726, 1730, 1801, 1803, 1804, 1805, 1807, 1809, 1810, 1811, 1812, 1817, 1824, 1901, 1902, 1903, 1908, 1916, 1917, 1920, 1921, 1922, 1926, 1927, 1928, 1930, 1932, 1939, 1940, 1941, 1943, 1950, 1955, 2001, 2003, 2006, 2009, 2010, 2014, 2101, 2103, 2104, 2108, 2110, 2113, 2115, 2116, 2119, 2123, 2126, 2127, 2201, 2202, 2204, 2205, 2208, 2210, 2214, 2217, 2218, 2222, 2223, 2228, 2229, 2245, 2246, 2301, 2302, 2303, 2305, 2309, 2310, 2401, 2404, 2413, 2415, 2418, 2419, 2422, 2425, 2426, 2427, 2501, 2502, 2504, 2506, 2507, 2512, 2601, 2602, 2604, 2607, 2609, 2618, 2626, 2632, 2633, 2635, 2636, 2638, 2643, 2644, 2646, 2647, 2648, 2652, 2658, 2701, 2705, 2706, 2707, 2711, 2712, 2716, 2717, 2719, 2722, 2801, 2803, 2804, 2807, 2809, 2811, 2816, 2817, 2820, 2821, 2822, 2824, 2841, 2842, 2847, 2901, 2902, 2903, 2906, 2907, 2910, 2912, 2917, 2918, 2922, 2923, 2924, 2926, 2927, 2930, 2931, 2931, 3001, 3003, 3004, 3011, 3013, 3014, 3015, 3016, 3019, 3021, 3101, 3102, 3103, 3105, 3106, 3107, 3109, 3111, 3124, 3201, 3202, 3203, 3204, 3205, 3206, 3207, 3208, 3301, 3302, 3306, 3401, 3402, 3403, 3404, 3408, 3409, 3411, 3413, 3415, 3431, 3501, 3502, 3504, 3505, 3507, 3509, 3514, 3523, 3531, 3601, 3602, 3603, 3605, 3608, 3613, 3616, 3701, 3801, 3802, 3803, 3804, 3806, 3809, 3811, 3813, 3901, 3902, 3904, 3906, 3908, 3911, 3913, 3914, 3918, 3926, 3927, 3928, 4001, 4003, 4005, 4006, 4008, 4011, 4013, 4016, 4101, 4102, 4104, 4105, 4108, 4110, 4112, 4114, 4115, 4116, 4201, 4208, 4209, 4210, 4214, 4215, 4217, 4218, 4219, 4224, 4301, 4302, 4303, 4306, 4308, 4310, 4314, 4315, 4317, 4318, 4319, 4323, 4330, 4401, 4402, 4403, 4404, 4405, 4407, 4408, 4410, 4411, 4412, 4414, 4416, 4422, 4431, 4501, 4502, 4503, 4505, 4506, 4507, 4510, 4601, 4604, 4609, 4614, 4619, 4622, 4623, 4625, 4701, 4702, 4703, 4704, 4705, 4706, 4708, 4710, 4713, 4801, 4802, 4807, 4808, 4811, 4812, 4814, 4817, 4819, 4822, 4825, 4827, 4828, 5001, 5002, 5003, 5004, 5005, 5006, 5007, 5010, 5010, 5010, 5010, 5013, 5013, 5013, 5013, 5015, 5015, 5015, 5015, 5022, 5022, 5022, 5022, 5025, 5025, 5025, 5025, 5028, 5028, 5028, 5028, 5032, 5032, 5032, 5032, 5033, 5033, 5033, 5033, 5036, 5036, 5036, 5036, 5037, 5037, 5037, 5037, 5040, 5040, 5040, 5040, 5043, 5043, 5043, 5043, 5044, 5044, 5044, 5044, 5047, 5047, 5047, 5047, 5049, 5049, 5049, 5049, 5050, 5050, 5050, 5050, 5052, 5052, 5052, 5052, 5053, 5053, 5053, 5053, 5054, 5054, 5054, 5054, 5057, 5057, 5057, 5057, 5061, 5061, 5061, 5061, 5063, 5063, 5063, 5063, 5064, 5064, 5064, 5064, 5065, 5065, 5065, 5065, 5066, 5066, 5066, 5066, 5067, 5067, 5067, 5067, 5069, 5069, 5069, 5069, 5071, 5071, 5071, 5071, 5072, 5072, 5072, 5072, 5073, 5073, 5073, 5073, 5074, 5074, 5074, 5074, 5075, 5075, 5075, 5075, 5076, 5076, 5076, 5076, 5077, 5077, 5077, 5077, 5078, 5078, 5078, 5078, 5080, 5080, 5080, 5080, 5082, 5082, 5082, 5082, 5084, 5084, 5084, 5084, 5085, 5085, 5085, 5085, 5087, 5087, 5087, 5087, 5089, 5089, 5089, 5089, 5090, 5090, 5090, 5090, 5092, 5092, 5092, 5092, 5094, 5094, 5094, 5094, 5096, 5096, 5096, 5096, 5098, 5098, 5098, 5098, 5099, 5099, 5099, 5099, 5101, 5101, 5101, 5101, 5103, 5103, 5103, 5103, 5105, 5105, 5105, 5105, 5106, 5106, 5106, 5106, 5107, 5107, 5107, 5107, 5109, 5109, 5109, 5109, 5110, 5110, 5110, 5110, 5112, 5112, 5112, 5112, 5114, 5114, 5114, 5114, 5115, 5115, 5115, 5115, 5116, 5116, 5116, 5116, 5117, 5117, 5117, 5117, 5119, 5119, 5119, 5119, 5120, 5120, 5120, 5120};
void APMS::run()
{

    while (true)
    {

        menu();
        int choice;
        cin >> choice;

        while (choice > 21 || choice < 0)
        {
            cout << " bad choice , please try again , here is the menu " << endl;
            if (!stay())
            {
                choice == 0;
            }
            else
            {
                menu();
                cin >> choice;
            }
        }

        try
        {
            if (choice == 0)
            {
                cout << "thank you for trying our program :) " << endl;
                cout << "***************** go east go west , ensia is always the best *****************" << endl;
                break;
            }
            if (choice == 1)
            {
                int id, year, month;
                cout << "please enter the id of the farmer " << endl;
                cin >> id;
                verify_id(id);
                cout << "please enter the year : " << endl;
                cin >> year;
                cout << "please enter the month : " << endl;
                cin >> month;

                this->reportSales(year, month, id);
                if (!stay())
                    break;
            }
            if (choice == 2)
            {
                int id, year;
                cout << "please enter the id of the farmer " << endl;
                cin >> id;
                verify_id(id);
                cout << "please enter the year : " << endl;
                cin >> year;

                this->reportSales(year, id);
                if (!stay())
                    break;
            }
            if (choice == 3)
            {
                int id, month, year;
                cout << "please enter the id of the farmer " << endl;
                cin >> id;
                verify_id(id);
                cout << "please enter the year : " << endl;
                cin >> year;
                cout << "please enter the month : " << endl;
                cin >> month;
                this->reportPenalties(year, month, id);
                if (!stay())
                    break;
            }
            if (choice == 4)
            {
                int id, year;
                cout << "please enter the id of the farmer " << endl;
                cin >> id;
                verify_id(id);
                cout << "please enter the year : " << endl;
                cin >> year;
                this->reportPenalties(year, id);
                if (!stay())
                    break;
            }
            if (choice == 5)
            {
                int year, idwilaya;
                cout << "enter the year : ";
                cin >> year;
                while (true)
                {
                    cout << "Please enter a valid id of the wilaya " << endl;
                    cin >> idwilaya;
                    if (idwilaya < 59 && idwilaya > 0)
                        break;
                }

                this->penalty_wilaya(idwilaya, year);
                cout << "\nThe result is going to be stored in a file named report_penalty_farmer_Wilaya.csv located in the current directory, if the function has already been called the content will be overwritten " << endl;
                if (!stay())
                    break;
            }
            if (choice == 6)
            {
                int year, idcity;
                cout << "enter the year : ";
                cin >> year;
                while (true)
                {
                    cout << "Please enter A valid id of the city " << endl;
                    cin >> idcity;
                    bool isValid;
                    for (int item : idCities)
                    {
                        if (idcity == item)
                        {
                            isValid = true;
                            break;
                        }
                    }
                    if (isValid)
                        break;
                    else
                    {
                        cout << "invalid city id try again , the cities' id in algeria start from 101 " << endl;
                    }
                }

                this->penalty_city(idcity, year);
                cout << "\nThe result is going to be stored in a file named report_penalty_farmer_city.csv located in the current directory, if the function has already been called the content will be overwritten " << endl;
                if (!stay())
                    break;
            }

            if (choice == 7)
            {
                int idArea, year;
                cout << "please enter the year : " << endl;
                cin >> year;
                while (true)
                {
                    cout << "Please enter A valid id of the area " << endl;
                    cin >> idArea;
                    bool isValid = false;
                    for (int item : idAreas)
                    {

                        if (idArea == item)
                        {
                            isValid = true;
                            break;
                        }
                    }
                    if (isValid)
                        break;
                }
                this->reportArea(year, idArea);
                cout << "\nThe result is going to be stored in a file named reportArea.csv located in the current directory, if the function has already been called the content will be overwritten " << endl;
                if (!stay())
                    break;
            }
            if (choice == 8)
            {
                int idCity, year;
                cout << "please enter the year : " << endl;
                cin >> year;
                while (true)
                {
                    cout << "Please enter A valid id of the city " << endl;
                    cin >> idCity;
                    bool isValid;
                    for (int item : idCities)
                    {
                        if (idCity == item)
                        {
                            isValid = true;
                            break;
                        }
                    }
                    if (isValid)
                        break;
                }
                this->reportCity(year, idCity);
                cout << "\nThe result is going to be stored in a file named reportCity.csv located in the current directory, if the function has already been called the content will be overwritten " << endl;
                if (!stay())
                    break;
            }
            if (choice == 9)
            {
                int idwilaya, year;
                cout << "please enter the year : " << endl;
                cin >> year;

                while (true)
                {
                    cout << "Please enter A valid id of the wilaya " << endl;
                    cin >> idwilaya;
                    if (idwilaya < 59 && idwilaya > 0)
                        break;
                }
                this->reportWilaya(year, idwilaya);
                cout << "\nThe result is going to be stored in a file named reportWilaya.csv located in the current directory, if the function has already been called the content will be overwritten " << endl;
                if (!stay())
                    break;
            }

            if (choice == 10)
            {
                int year;
                cout << "Enter the year : " << endl;
                cin >> year;
                this->reportCountry(year);
                cout << "\nThe result is going to be stored in a file named reportCountry.csv located in the current directory, if the function has already been called the content will be overwritten " << endl;
                if (!stay())
                    break;
            }
            if (choice == 11)
            {
                int id;
                cout << "Enter the id of the farmer : " << endl;
                cin >> id;
                verify_id(id);
                this->reportFarmer(id);
                if (!stay())
                    break;
            }
            if (choice == 12)
            {
                int month, year;

                cout << "Enter the month : " << endl;
                cin >> month;
                while (month < 1 || month > 12)
                {
                    cout << "invalid month , try again " << endl;
                    cin >> month;
                }

                cout << "Enter the year : " << endl;
                cin >> year;
                while (year > 2022 || year < 1990)
                {
                    cout << "invalid year , try again " << endl;
                    cin >> year;
                }

                this->find_winner_by_year_month(year, month);

                if (!stay())
                    break;
            }
            if (choice == 13)
            {
                int month;
                while (true)
                {
                    cout << "Enter the month : " << endl;
                    cin >> month;
                    if (month <= 12 && month >= 1)
                        break;
                }

                this->find_winner_by_month(month);

                if (!stay())
                    break;
            }
            if (choice == 14)
            {
                int year;
                while (true)
                {
                    cout << "Enter the year : " << endl;
                    cin >> year;
                    if (year >= 1962 && year <= 2022)
                        break;
                }

                this->find_winner_by_year(year);

                if (!stay())
                    break;
            }
            if (choice == 15)
            {
                cout << "Here you will enter the information of the sale of the farmer :  " << endl;
                Sales ob;
                cout << " THE INFORMATIONS OF THE SALE OF THAT FARMER IN THAT YEAR IN THAT MONTH, WILL BE OVERWRITTEN IF THEIR EXIST IN THE DATASET !!!!!" << endl;

                cout << "the id of the farmer : " << endl;
                cin >> ob.farmer_id;
                while (ob.farmer_id < 0 || ob.farmer_id > 200000)
                {
                    cout << "invalid values , enter new value  : ";
                    cin >> ob.farmer_id;
                }
                cout << "the month of the sale : " << endl;
                cin >> ob.month;
                while (ob.month > 12 || ob.month < 1)
                {
                    cout << "invalid month , enter new values " << endl;
                    cin >> ob.month;
                }
                cout << "the year of the sale : " << endl;
                cin >> ob.year;
                while (ob.year > 2022 || ob.year < 1990)
                {
                    cout << "invalid year , enter new values " << endl;
                    cin >> ob.year;
                }
                cout << "the water consumption of the farmer : " << endl;
                cin >> ob.water;
                while (ob.water < 0)
                {
                    cout << "invalid values , enter new value  : ";
                    cin >> ob.water;
                }

                cout << "the electricity consumption of the farmer : " << endl;
                cin >> ob.electricity;
                while (ob.electricity < 0)
                {
                    cout << "invalid values , enter new value  : ";
                    cin >> ob.electricity;
                }
                category *set = new category[5];

                cout << endl;
                cout << "------ now you will enter the informations of the sales of this farmer in the 5 categories , if the farmer hasn't sale anything in a category enter 0 " << endl
                     << "*********************************" << endl;
                cout << "the informations about the sales of the cereals category : " << endl;
                set[0].category_name = "cereals";
                cout << "enter the average price in this category in this month  : " << endl;
                cin >> set[0].average_price;
                while (set[0].average_price < 0)
                {
                    cout << "invalid price , try again " << endl;
                    cin >> set[0].average_price;
                }
                cout << "enter the number of kg sold in this category in this month , in this year " << endl;
                cin >> set[0].nb_kg_sold;
                while (set[0].nb_kg_sold < 0)
                {
                    cout << "invalid nb of kg, try again " << endl;
                    cin >> set[0].nb_kg_sold;
                }

                cout << "enter the penalty severity in this category for this farmer (from 1 to 3 ) : " << endl;
                cin >> set[0].severity_penalty;
                while (set[0].severity_penalty > 3 || set[0].severity_penalty < 1)
                {
                    cout << "the severity of the penalty must be between 1 and 3 , try again " << endl;
                    cin >> set[0].severity_penalty;
                }

                cout << endl
                     << "*********************************" << endl;
                cout << "the informations about the sales of the dates category : " << endl;
                set[1].category_name = "dates";
                cout << "enter the average price in this category in this month  : " << endl;
                cin >> set[1].average_price;
                while (set[1].average_price < 0)
                {
                    cout << "invalid price , try again " << endl;
                    cin >> set[1].average_price;
                }
                cout << "enter the number of kg sold in this category in this month , in this year " << endl;
                cin >> set[1].nb_kg_sold;
                while (set[1].nb_kg_sold < 0)
                {
                    cout << "invalid nb of kg, try again " << endl;
                    cin >> set[1].nb_kg_sold;
                }
                cout << "enter the penalty severity in this category for this farmer (from 1 to 3 ) : " << endl;
                cin >> set[1].severity_penalty;
                while (set[1].severity_penalty > 3 || set[1].severity_penalty < 1)
                {
                    cout << "the severity of the penalty must be between 1 and 3 , try again " << endl;
                    cin >> set[1].severity_penalty;
                }
                cout << endl
                     << "*********************************" << endl;
                cout << "the informations about the sales of the fruits category : " << endl;
                set[2].category_name = "fruits";
                cout << "enter the average price in this category in this month  : " << endl;
                cin >> set[2].average_price;
                while (set[2].average_price < 0)
                {
                    cout << "invalid price , try again " << endl;
                    cin >> set[2].average_price;
                }
                cout << "enter the number of kg sold in this category in this month , in this year " << endl;
                cin >> set[2].nb_kg_sold;
                while (set[2].nb_kg_sold < 0)
                {
                    cout << "invalid nb of kg, try again " << endl;
                    cin >> set[2].nb_kg_sold;
                }
                cout << "enter the penalty severity in this category for this farmer (from 1 to 3 ) : " << endl;
                cin >> set[2].severity_penalty;
                while (set[2].severity_penalty > 3 || set[2].severity_penalty < 1)
                {
                    cout << "the severity of the penalty must be between 1 and 3 , try again " << endl;
                    cin >> set[2].severity_penalty;
                }

                cout << endl
                     << "*********************************" << endl;
                cout << "the informations about the sales of the vegetables category : " << endl;
                set[3].category_name = "olives";
                cout << "enter the average price in this category in this month  : " << endl;
                cin >> set[3].average_price;
                while (set[3].average_price < 0)
                {
                    cout << "invalid price , try again " << endl;
                    cin >> set[3].average_price;
                }
                cout << "enter the number of kg sold in this category in this month , in this year " << endl;
                cin >> set[3].nb_kg_sold;
                while (set[3].nb_kg_sold < 0)
                {
                    cout << "invalid nb of kg, try again " << endl;
                    cin >> set[3].nb_kg_sold;
                }
                cout << "enter the penalty severity in this category for this farmer (from 1 to 3 ) : " << endl;
                cin >> set[3].severity_penalty;
                while (set[3].severity_penalty > 3 || set[3].severity_penalty < 1)
                {
                    cout << "the severity of the penalty must be between 1 and 3 , try again " << endl;
                    cin >> set[3].severity_penalty;
                }

                cout << endl
                     << "*********************************" << endl;
                cout << "the informations about the sales of the olives category : " << endl;
                set[4].category_name = "vegetables";
                cout << "enter the average price in this category in this month  : " << endl;
                cin >> set[4].average_price;
                while (set[4].average_price < 0)
                {
                    cout << "invalid price , try again " << endl;
                    cin >> set[4].average_price;
                }
                cout << "enter the number of kg sold in this category in this month , in this year " << endl;
                cin >> set[4].nb_kg_sold;
                while (set[4].nb_kg_sold < 0)
                {
                    cout << "invalid nb of kg, try again " << endl;
                    cin >> set[4].nb_kg_sold;
                }
                cout << "enter the penalty severity in this category for this farmer (from 1 to 3 ) : " << endl;
                cin >> set[4].severity_penalty;
                while (set[4].severity_penalty > 3 || set[4].severity_penalty < 1)
                {
                    cout << "the severity of the penalty must be between 1 and 3 , try again " << endl;
                    cin >> set[4].severity_penalty;
                }

                this->insert_new_farmer(ob);

                cout << "farmer inserted " << endl;
                if (!stay())
                    break;
            }

            if (choice == 16)
            {
                cout << "Please Make sure to setup the python environment for Matplotlibcpp, then uncomment the function generateRunningTimeGraph() definition and call and uncomment the include path as well as the namespace definition" << endl;
                // generateRunningTimeGraph();
                if (!stay())
                    break;
            }

            if (choice == 17)
            {
                runningTimeFindWinner();
                if (!stay())
                    break;
            }
            if (choice == 18)
            {
                runningTimeReportSale();
                if (!stay())
                    break;
            }
            if (choice == 19)
            {
                runningTimeReportPenalities();
                if (!stay())
                    break;
            }

            if (choice == 20)
            {
                runningTimeReportAreas();
                if (!stay())
                    break;
            }

            if (choice == 21)
            {
                cout << "Please Make sure to setup the python environment for Matplotlibcpp, then uncomment the function generateSalesBarChart() definition and call and uncomment the include path as well as the namespace definition" << endl;
                // generateSalesBarChart();
                if (!stay())
                    break;
            }
        }
        catch (const out_of_range &e)
        {
            // Catch-all block for any other type of exception
            cerr << e.what() << endl;
            std::cerr << "a problem occure please , check your inputs again , thank you for trying our program !" << std::endl;
            if (!stay())
                break;
        }
        catch (...)
        {
            // Catch-all block for any other type of exception
            std::cerr << "a problem occure please , check your inputs again , thank you for trying our program !" << std::endl;
            if (!stay())
                break;
        }
    }
}

void APMS::runningTimeReportAreas()
{
    // int year, int areaID
    srand(time(0));
    int year = rand() % 32 + 1991;
    long areaID = rand() % 1498 + 1;
    cout << "Calling the report areas in " << year
         << " for the area with ID " << areaID << " ..." << endl;
    auto start = std::chrono::high_resolution_clock::now();
    reportArea(year, areaID);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "\n\nThe operation took " << duration.count() << "µs" << endl;
}
void APMS::runningTimeReportPenalities()
{
    // int year, int month, long id
    srand(time(0));
    int year = rand() % 32 + 1991;
    int month = rand() % 12 + 1;
    long id = rand() % 200000 + 1;
    cout << "Calling the report penalties on " << year << " at the month " << month
         << " for the farmer with id " << id << " ..." << endl;
    auto start = std::chrono::high_resolution_clock::now();
    reportPenalties(year, month, id);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "\n\nThe operation took " << duration.count() << "µs" << endl;
};

void APMS::runningTimeReportSale()
{
    // int year, int month, long id
    srand(time(0));
    int year = rand() % 32 + 1991;
    int month = rand() % 12 + 1;
    long id = rand() % 200000 + 1;
    cout << "Calling the report sales on " << year << " at the month " << month
         << " for the farmer with id " << id << " ..." << endl;
    auto start = std::chrono::high_resolution_clock::now();
    reportSales(year, month, id);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "\n\nThe operation took " << duration.count() << "µs" << endl;
}

void APMS::runningTimeFindWinner()
{
    srand(time(0));
    int year = rand() % 32 + 1991;
    cout << "Finding the winner at the year " << year << "..." << endl;
    auto start = std::chrono::high_resolution_clock::now();
    find_winner_by_year(year);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "\n\nThe operation took " << duration.count() << "µs" << endl;
}

//**********************************************************************************************

// Please uncomment these after setting up the environment for running the functions that depend on matplotlibcpp

/* void APMS::generateRunningTimeGraph(){
    //fill the vector that will be passed to the plot function
    vector<double> size = vector<double>(100);
    int step = 10000;
    for(int i = 0; i < 100; ++i)
    {
        size[i] = (i+1)*step;
    }
    cout << "\n\nGenerating a graph for the running time of the insertion of sales based on different input sizes..." <<endl;
    cout << "****************************************************************************" << endl;
    cout << "The generated graph will be stored in an image named bstInsertion.png\n" << endl;
    //Set the size of output image = 1200x780 pixels
    plt::figure_size(1200, 780);
    //Plot line from given x and y data. Color is selected automatically.
    plt::plot(size, runningTime);
    //Plot a line whose name will show up as "log(x)" in the legend.
    plt::named_plot("Insert sales",size, runningTime);
    plt::xlabel("Input size");
    plt::ylabel("Running Time (microseconds)");
    //Add graph title
    plt::title("The running time for inserting sales in a BST tree");
    //save figure
    const char* filename = "./bstInsertion.png";
    std::cout << "Saving result to " << filename << std::endl;;
    plt::save(filename);
}

void APMS::generateSalesBarChart(){
    long id;
    int month;
    int year;
    cout << "Enter the farmer's ID:  " << endl;
    cin >> id;
    cout << "Enter the month:  " << endl;
    cin >> month;
    cout << "Enter the year:  "<< endl;
    cin >> year;
    bool worked = true;
    std::vector<float> categories;
    categories = {1, 2, 3, 4, 5};
    //filling the sales vector for the farmer with the given id in the given year and month
    std::vector<float> farmerSales = sales->findSales(id, month, year, worked);
    if(worked == false)
    {
        cout << "The farmer with id " << id << " didn't work on the month "<< month << " in the year "<< year << endl;
        return;
    }
    if(farmerSales.empty())
    {
        cout << "No year corresponding to your input " << endl;
        return;
    }
    //now, we make sure that the year exists and the farmer with the specified id has worked in that given month
    //plotting the sales for the different sales
    plt::bar(categories, farmerSales);
    plt::xlabel("Categories");
    plt::ylabel("Sales");
    //plt::show();
    string filename = to_string(id) + ".png";
    cout << "\nSaving the bar chart to the picture entitled " << id << ".png ..." << endl;
    plt::save(filename);
}; */
