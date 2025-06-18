#include <iostream>
#include <iterator>
#include <map>
#include <math.h>
#include <numeric>
#include <vector>

using namespace std;

struct Node {
    string key;
    string value;
    Node* next;

    Node(string key, string value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

class HashTable {
private:
    Node** table;
    int tableSize;
    int itemCount;
public:
    // Constructor
    HashTable(int size) {
        this->tableSize = size;
        this->table = new Node*[this->tableSize];
        this->itemCount = 0;

        for (int i = 0; i < this->tableSize; i++) {
            this->table[i] = nullptr;
        }
    }

    int hashFunction(string key) {
        int hash = 0;
        for (char c : key) {
            hash += c;
        }

        return hash % this->tableSize;
    }

    void insert(string key, string value) {
        int index = hashFunction(key);

        // Check if key already exists (update value)
        Node* current = this->table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }

            current = current->next;
        }

        // If key doesn't exist, create new node or in the end if there is another key inside (tail)
        Node* newNode = new Node(key, value);
        if (this->table[index] == nullptr) { // Jika bucket kosong
            this->table[index] = newNode;
        } else { // Jika bucket tidak kosong, cari ekornya
            Node* temp = this->table[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        this->itemCount++;

        cout << "Inserted: " << key << " -> " << value << " at index " << index << endl;
    }

    void displayAllChains() {
        cout << "--- Displaying All Hash Table Chains ---" << endl;
        for (int i = 0; i < this->tableSize; ++i) {
            cout << "Index " << i << ": ";
            Node* current = this->table[i];

            if (current == nullptr) {
                cout << "Empty";
            } else {
                while (current != nullptr) {
                    cout << current->key << " (" << current->value << ")";
                    if (current->next != nullptr) {
                        cout << " -> ";
                    }
                    current = current->next;
                }
            }
            cout << endl; // Pindah ke baris baru untuk indeks berikutnya
        }
        cout << "--------------------------------------" << endl;
    }

    void update(string key, string value) {
        int index = hashFunction(key);

        // Check if key already exists (update value)
        Node* current = this->table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }

            current = current->next;
        }

        // If key not found.
        cout << "Key doesn't exist." << endl;
    }

    string search(string key) {
        int index = hashFunction(key);
        Node* current = this->table[index];

        // Traverse linked list at this index
        while (current != nullptr) {
            if (current->key == key) {
                return current->value; // Found
            }

            current = current->next;
        }

        return "Not found"; // Key not found
    }

    bool deleteKey(string key) {
        int index = hashFunction(key);
        Node* current = this->table[index];
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                // Delete head node
                if (previous == nullptr) {
                    this->table[index] = current->next;
                }
                // Delete middle/end node
                else {
                    previous->next = current->next;
                }

                delete current;
                this->itemCount--;
                return true; // Successfully deleted
            }

            previous = current;
            current = current->next;
        }

        return false; // Key not found
    }
};

void display_vector(const vector<int> &v)
{
    copy(v.begin(), v.end(),
        ostream_iterator<int>(cout, " "));
}

int convertString(string input) {
    int hash = 0;
    for (char c : input) {
        hash += c;
    }

    return hash;
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
    string names[62] = {
        "Alice Smith", "Bob Johnson", "Charlie Brown", "Diana Miller", "Ethan Davis",
        "Fiona Garcia", "George Rodriguez", "Hannah Martinez", "Ivan Hernandez", "Julia Lopez",
        "Kevin Gonzalez", "Laura Wilson", "Michael Anderson", "Nancy Thomas", "Olivia Jackson",
        "Paul White", "Quinn Harris", "Rachel Clark", "Steven Lewis", "Tina Young",
        "Ursula Hall", "Victor Allen", "Wendy Scott", "Xavier King", "Yara Green",
        "Zachary Adams", "Amy Baker", "Brian Nelson", "Catherine Hill", "Daniel Carter",
        "Emily Roberts", "Frank Campbell", "Grace Phillips", "Henry Evans", "Isabel Turner",
        "Jack Wright", "Karen Parker", "Liam Morris", "Mia Murphy", "Noah Rivera",
        "Olivia Cooper", "Peter Ward", "Quincy Bailey", "Rebecca Bell", "Samuel Cox",
        "Sophia Rogers", "Thomas Reed", "Uma Kelly", "Vincent Price", "Willow Peterson",
        "Xenia Foster", "Yusuf Sanders", "Zoe Ross", "Arthur Wood", "Brenda Cole",
        "Caleb Morgan", "Daisy Kim", "Edward James", "Felicity Gray", "Gavin Myers",
        "Holly Fisher", "Ian Henderson"
    };

    int tableSize[3] = {31, 101, 503};

    HashTable hashTable = HashTable(31);

    for (int i = 0; i < size(names); i++) {
        hashTable.insert(names[i], names[i]);
    }

    cout << hashTable.search("Daisy Kim") << endl;

    hashTable.update("Daisy Kim", "Kim Dokja");

    cout << hashTable.search("Daisy Kim") << endl;

    hashTable.deleteKey("Daisy Kim");

    cout << hashTable.search("Daisy Kim") << endl;

    hashTable.displayAllChains();

    return 0;
}