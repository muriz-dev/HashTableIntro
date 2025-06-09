#include <iostream>
#include <iterator>
#include <map>
#include <math.h>
#include <numeric>
#include <vector>

using namespace std;

// Mengubah string menjadi sebuah nilai yang dapat dihitung
int hashFunction(string key, int size) {
    int hash = 0;
    for (char c : key) {
        hash += c;
    }

    return hash % size;
}

void display_vector(const vector<int> &v)
{
    std::copy(v.begin(), v.end(),
        std::ostream_iterator<int>(std::cout, " "));
}

// Division Method
int division(int key, int size) {
    return key % size;
}

// Multiplication Method
int multiplication(int key, int size) {
    const double ratio = 0.618;

    double temp = fmod(key * ratio, 1);

    if (temp < 0) {
        temp += 1.0;
    }

    return floor(size * temp);
}

// Fungsi untuk mendapatkan 3 atau 2 digit tengah dari sebuah string
string getMiddleCharacters(string value) {
    int length = value.length();

    if (length == 0) {
        return "";
    }

    if (length % 2 == 0) {
        if (length < 2) {
            return "";
        }

        return value.substr((length / 2) - 1, 2);
    } else {
        if (length < 3) {
            return "";
        }

        return value.substr((length / 2) - 1, 3);
    }
}

// Mid-Square Method
int midSquare(int key, int size) {
    long long temp = static_cast<long long>(key) * key;

    string middle = getMiddleCharacters(to_string(temp));

    if (!middle.empty()) {
        return stoi(middle) % size;
    } else {
        return 0 % size;
    }
}

// Fungsi untuk membagi sebuah string menjadi 3 digit di setiap segmen
vector<long long> splitToSegment(string characters, int length) {
    vector<long long> segments;

    for (int i = 0; i < characters.length(); i += length) {
        string segment = characters.substr(i, length);
        segments.push_back(stoll(segment));
    }

    return segments;
}


// Fungsi untuk menjumlahkan seluruh segmen
long long sumSegments(vector<long long> data) {
    return accumulate(data.begin(), data.end(), 0LL);
}

// Folding Method
int shiftFolding(long long key, int size) {
    vector<long long> segments = splitToSegment(to_string(key), 3);

    return sumSegments(segments) % size;
}

// Fungsi untuk menghitung jumlah key yang muncul lebih dari 1, dimana yang artinya adalah sebuah collision
int countNumbersAppearingMoreThanOnce(vector<int>& data) {
    map<int, int> counts;

    for (int num : data) {
        counts[num]++;
    }

    int numbersWithDuplicates = 0;
    for (const auto& pair : counts) {
        if (pair.second > 1) {
            numbersWithDuplicates++;
        }
    }

    return numbersWithDuplicates;
}

// Fungsi untuk menghitung jumlah key unik yang muncul
int countSameNumberInVector(vector<int>& data) {
    map<int, int> counts;

    for (int num : data) {
        counts[num]++;
    }

    return counts.size();
}

// Fungsi untuk menghitung collision rate
void collisionRate(vector<int>& data, int datasetSize) {
    double result = static_cast<double>(countNumbersAppearingMoreThanOnce(data)) / datasetSize;

    cout << "collision: " << countNumbersAppearingMoreThanOnce(data) << endl;
    cout << "Dataset Size: " << datasetSize << endl;
    cout << "collision Rate: " << result << " atau " << result * 100 << "%" << endl;
}

// Fungsi untuk menghitung load factor
void loadFactor(vector<int>& data, int tableSize) {
    double result = static_cast<double>(countSameNumberInVector(data)) / tableSize;

    cout << "Load factor: " << result << endl;
}

int getMaxChainLength(vector<int>& data) {
    map<int, int> counts;

    for (int num : data) {
        counts[num]++;
    }

    int maxChainLength = 0;
    int keyWithHighChainLength = 0;

    for (const auto& pair : counts) {
        if (pair.second > maxChainLength) {
            maxChainLength = pair.second;
            keyWithHighChainLength = pair.first;
        }
    }

    return maxChainLength;
}

void maxChainLength(vector<int>& data) {
    int result = getMaxChainLength(data);

    if (result > 1) {
        cout << "Max Chain Length: " << result << endl;
    } else {
        cout << "Max Chain Length: Tidak ada key dengan chain"<< endl;
    }
}

int main() {
    /*
      ========================= EVALUASI METODE HASHING =========================

      Berdasarkan hasil pengujian terhadap 4 dataset menggunakan 4 metode hashing
      yang berbeda (Division, Multiplication, Mid-Square, dan Folding), diperoleh
      hasil dan kesimpulan sebagai berikut:

      >> Dataset 1:
         - Metode Terbaik: Division Method (Ukuran Tabel: 503)
         - Alasan: Tidak terjadi collision (0%), panjang rantai = 0, dan load factor ideal.

      >> Dataset 2:
         - Metode Terbaik: Division Method (Ukuran Tabel: 503)
         - Alasan: Collision rate terendah (10%) dan panjang rantai pendek (maksimal 3).

      >> Dataset 3:
         - Metode Terbaik: Multiplication Method (Ukuran Tabel: 503)
         - Alasan: Collision rate paling rendah (9.17%) dan panjang rantai hanya 2.

      >> Dataset 4:
         - Metode Terbaik: Division Method (Ukuran Tabel: 503)
         - Alasan: Performa paling stabil dengan collision rate 16.18% dan panjang rantai maksimal 4.

      ---------------------------------------------------------------------------

      >> Observasi Umum:
         - Metode Division secara konsisten memberikan performa terbaik, terutama
           saat digunakan dengan ukuran tabel yang besar (bilangan prima seperti 503).
         - Metode Multiplication juga memberikan hasil baik, terutama pada dataset 3.
         - Metode Mid-Square dan Folding cenderung menghasilkan collision lebih tinggi
           dan rantai yang lebih panjang, sehingga kurang optimal.
         - Peningkatan ukuran tabel secara signifikan dapat menurunkan collision rate
           dan memperbaiki distribusi data.

      ===========================================================================
    */

    int dataset1[100] = {
        1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009,
        1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019,
        1020, 1021, 1022, 1023, 1024, 1025, 1026, 1027, 1028, 1029,
        1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039,
        1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049,
        1050, 1051, 1052, 1053, 1054, 1055, 1056, 1057, 1058, 1059,
        1060, 1061, 1062, 1063, 1064, 1065, 1066, 1067, 1068, 1069,
        1070, 1071, 1072, 1073, 1074, 1075, 1076, 1077, 1078, 1079,
        1080, 1081, 1082, 1083, 1084, 1085, 1086, 1087, 1088, 1089,
        1090, 1091, 1092, 1093, 1094, 1095, 1096, 1097, 1098, 1099
    };

    int dataset2[150] = {
        15847, 73291, 28756, 91234, 45678, 82139, 67890, 34512, 78945, 23167,
        89012, 56734, 12389, 90456, 67123, 45890, 78234, 34567, 91890, 25634,
        58947, 83712, 47265, 94851, 36729, 82543, 69174, 51386, 74925, 18637,
        95284, 42761, 87359, 63148, 29576, 85392, 71648, 54917, 38254, 92681,
        46173, 79528, 13865, 97241, 58374, 84629, 27156, 93482, 65917, 41285,
        78643, 52198, 86754, 39427, 94183, 67529, 23846, 89571, 45297, 81652,
        57984, 34719, 98325, 62458, 26791, 83146, 49673, 95128, 71395, 47862,
        84257, 18594, 92731, 56268, 39485, 75912, 43679, 87234, 61597, 24853,
        98176, 52419, 86742, 31865, 77298, 43521, 89654, 65187, 27943, 94576,
        58139, 82467, 46792, 73258, 19485, 95671, 62134, 38597, 84923, 51286,
        77649, 24172, 98435, 53768, 87291, 41654, 76987, 32519, 95842, 68175,
        44238, 89561, 25794, 93167, 56423, 82756, 48189, 74512, 19845, 96278,
        63741, 37164, 84597, 51923, 78256, 24689, 97152, 53485, 86918, 42351,
        79784, 35217, 91543, 67876, 44239, 88562, 25895, 94128, 57461, 83794,
        49127, 75563, 31896, 98229, 64572, 37945, 84278, 51631, 78964, 25397
    };

    int dataset3[120] = {
        2021001, 2021002, 2021003, 2021004, 2021005, 2021006, 2021007, 2021008, 2021009, 2021010,
        2021045, 2021046, 2021047, 2021048, 2021049, 2021050, 2021089, 2021090, 2021091, 2021092,
        2021123, 2021124, 2021125, 2021126, 2021167, 2021168, 2021169, 2021170, 2021171, 2021172,
        2022011, 2022012, 2022013, 2022014, 2022015, 2022034, 2022035, 2022036, 2022037, 2022038,
        2022078, 2022079, 2022080, 2022081, 2022082, 2022112, 2022113, 2022114, 2022115, 2022116,
        2022156, 2022157, 2022158, 2022159, 2022160, 2022190, 2022191, 2022192, 2022193, 2022194,
        2023023, 2023024, 2023025, 2023026, 2023027, 2023067, 2023068, 2023069, 2023070, 2023071,
        2023101, 2023102, 2023103, 2023104, 2023105, 2023145, 2023146, 2023147, 2023148, 2023149,
        2023189, 2023190, 2023191, 2023192, 2023193, 2024012, 2024013, 2024014, 2024015, 2024016,
        2024056, 2024057, 2024058, 2024059, 2024060, 2024090, 2024091, 2024092, 2024093, 2024094,
        2024134, 2024135, 2024136, 2024137, 2024138, 2024178, 2024179, 2024180, 2024181, 2024182,
        2025201, 2025202, 2025203, 2025204, 2025205, 2025245, 2025246, 2025247, 2025248, 2025249
    };

    string dataset4[68] = {
        "978-0-123456-78-9", "978-1-234567-89-0", "978-0-345678-90-1", "978-1-456789-01-2",
        "979-0-567890-12-3", "978-2-678901-23-4", "979-1-789012-34-5", "978-3-890123-45-6",
        "978-0-901234-56-7", "979-2-012345-67-8", "978-1-123456-78-9", "978-4-234567-89-0",
        "979-0-345678-90-1", "978-2-456789-01-2", "978-5-567890-12-3", "979-1-678901-23-4",
        "978-3-789012-34-5", "978-6-890123-45-6", "979-2-901234-56-7", "978-4-012345-67-8",
        "ABC-DEF-123456-XY", "XYZ-ABC-789012-PQ", "MNO-PQR-345678-ST", "RST-UVW-901234-KL",
        "JKL-MNO-567890-CD", "EFG-HIJ-234567-WX", "UVW-XYZ-890123-EF", "GHI-JKL-456789-AB",
        "BCD-EFG-012345-YZ", "STU-VWX-678901-MN", "HIJ-KLM-123456-OP", "NOP-QRS-789012-GH",
        "CDE-FGH-345678-TU", "TUV-WXY-901234-IJ", "DEF-GHI-567890-VW", "OPQ-RST-234567-CD",
        "FGH-IJK-890123-XY", "VWX-YZA-456789-KL", "GHI-JKL-012345-AB", "WXY-ZAB-678901-PQ",
        "A1B2C3D4E5F6G7H8", "X9Y8Z7A6B5C4D3E2", "M1N2O3P4Q5R6S7T8", "U9V8W7X6Y5Z4A3B2",
        "K1L2M3N4O5P6Q7R8", "S9T8U7V6W5X4Y3Z2", "I1J2K3L4M5N6O7P8", "Q9R8S7T6U5V4W3X2",
        "G1H2I3J4K5L6M7N8", "O9P8Q7R6S5T4U3V2", "E1F2G3H4I5J6K7L8", "M9N8O7P6Q5R4S3T2",
        "C1D2E3F4G5H6I7J8", "K9L8M7N6O5P4Q3R2", "A1B2C3D4E5F6G7H8", "I9J8K7L6M5N4O3P2",
        "LONG-STRING-PATTERN-001", "EXTENDED-FORMAT-DATA-025", "COMPLEX-IDENTIFIER-999",
        "UNIQUE-ALPHANUMERIC-ABC", "VARIABLE-LENGTH-XYZ-789", "MIXED-CHARS-PATTERN-456",
        "SPECIAL-FORMAT-ID-2024", "ULTRA-LONG-IDENTIFIER-X1", "CUSTOM-PATTERN-ABCD-789",
        "MULTI-SEGMENT-ID-999999", "HYPHENATED-LONG-STRING-A", "EXTENDED-ID-FORMAT-2025"
    };

    string methodList[4] = {
        "Division Method", "Multiplication Method",
        "Mid-Square Method", "Folding Method"
    };

    int datasetList[4] = {1, 2, 3, 4};

    int tableSize[3] = {31, 101, 503};

    // Perulangan untuk methodList
    for (int i = 0; i < size(methodList); i++) {
       cout << endl;
       cout << methodList[i] << endl;

       if (methodList[i] == "Division Method") {
           // Perulangan untuk datasetList
           for (int j = 0; j < size(datasetList); j++) {
               vector<int> temp;
               switch (datasetList[j]) {
                   case 1:
                       cout << "Dataset 1" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset1); l++) {
                               // cout << division(dataset1[l], tableSize[k]) << ", ";
                               temp.push_back(division(dataset1[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset1));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 2:
                       cout << "Dataset 2" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset2); l++) {
                               // cout << division(dataset2[l], tableSize[k]) << ", ";
                               temp.push_back(division(dataset2[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset2));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 3:
                       cout << "Dataset 3" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset3); l++) {
                               // cout << division(dataset3[l], tableSize[k]) << ", ";
                               temp.push_back(division(dataset3[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset3));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 4:
                       cout << "Dataset 4" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset4); l++) {
                               // cout << division(hashFunction(dataset4[l], tableSize[k]), tableSize[k]) << ", ";
                               temp.push_back(hashFunction(dataset4[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset4));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   default:
                       cout << "Dataset not found" << endl;
                   break;
               }
           }
       } else if (methodList[i] == "Multiplication Method") {
           // Perulangan untuk datasetList
           for (int j = 0; j < size(datasetList); j++) {
               vector<int> temp;
               switch (datasetList[j]) {
                   case 1:
                       cout << "Dataset 1" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset1); l++) {
                               // cout << multiplication(dataset1[l], tableSize[k]) << ", ";
                               temp.push_back(multiplication(dataset1[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset1));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 2:
                       cout << "Dataset 2" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset2); l++) {
                               // cout << multiplication(dataset2[l], tableSize[k]) << ", ";
                               temp.push_back(multiplication(dataset2[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset2));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 3:
                       cout << "Dataset 3" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset3); l++) {
                               // cout << multiplication(dataset3[l], tableSize[k]) << ", ";
                               temp.push_back(multiplication(dataset3[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset3));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 4:
                       cout << "Dataset 4" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset4); l++) {
                               // cout << multiplication(hashFunction(dataset4[l], tableSize[k]), tableSize[k]) << ", ";
                               temp.push_back(multiplication(hashFunction(dataset4[l], tableSize[k]), tableSize[k]));
                           }

                           collisionRate(temp, size(dataset4));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   default:
                       cout << "Dataset not found" << endl;
                   break;
               }
           }
       } else if (methodList[i] == "Mid-Square Method") {
           // Perulangan untuk datasetList
           for (int j = 0; j < size(datasetList); j++) {
               vector<int> temp;
               switch (datasetList[j]) {
                   case 1:
                       cout << "Dataset 1" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset1); l++) {
                               // cout << midSquare(dataset1[l], tableSize[k]) << ", ";
                               temp.push_back(midSquare(dataset1[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset1));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 2:
                       cout << "Dataset 2" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset2); l++) {
                               // cout << midSquare(dataset2[l], tableSize[k]) << ", ";
                               temp.push_back(midSquare(dataset2[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset2));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 3:
                       cout << "Dataset 3" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset3); l++) {
                               // cout << midSquare(dataset3[l], tableSize[k]) << ", ";
                               temp.push_back(midSquare(dataset3[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset3));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 4:
                       cout << "Dataset 4" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset4); l++) {
                               // cout << midSquare(hashFunction(dataset4[l], tableSize[k]), tableSize[k]) << ", ";
                               temp.push_back(midSquare(hashFunction(dataset4[l], tableSize[k]), tableSize[k]));
                           }

                           collisionRate(temp, size(dataset4));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   default:
                       cout << "Dataset not found" << endl;
                   break;
               }
           }
       } else if (methodList[i] == "Folding Method") {
           // Perulangan untuk datasetList
           for (int j = 0; j < size(datasetList); j++) {
               vector<int> temp;
               switch (datasetList[j]) {
                   case 1:
                       cout << "Dataset 1" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset1); l++) {
                               // cout << shiftFolding(dataset1[l], tableSize[k]) << ", ";
                               temp.push_back(shiftFolding(dataset1[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset1));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 2:
                       cout << "Dataset 2" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset2); l++) {
                               // cout << shiftFolding(dataset2[l], tableSize[k]) << ", ";
                               temp.push_back(shiftFolding(dataset2[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset2));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 3:
                       cout << "Dataset 3" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset3); l++) {
                               // cout << shiftFolding(dataset3[l], tableSize[k]) << ", ";
                               temp.push_back(shiftFolding(dataset3[l], tableSize[k]));
                           }

                           collisionRate(temp, size(dataset3));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   case 4:
                       cout << "Dataset 4" << endl;
                       for (int k = 0; k < size(tableSize); k++) {
                           cout << "Table Size: " << tableSize[k] << endl;
                           for (int l = 0; l < size(dataset4); l++) {
                               // cout << shiftFolding(hashFunction(dataset4[l], tableSize[k]), tableSize[k]) << ", ";
                               temp.push_back(shiftFolding(hashFunction(dataset4[l], tableSize[k]), tableSize[k]));
                           }

                           collisionRate(temp, size(dataset4));
                           loadFactor(temp, tableSize[k]);
                           maxChainLength(temp);
                           temp.clear();

                           cout << endl;
                       }
                   break;
                   default:
                       cout << "Dataset not found" << endl;
                   break;
               }
           }
       } else {
           cout << "No method selected" << endl;
       }
    }

    return 0;
}