#include <assert.h>
#include <iostream>
#include <iterator>
#include <string>

class HashTable {
public:
    explicit HashTable(int initial_size);
    ~HashTable();
    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable& operator=(const HashTable&) = delete;
    HashTable& operator=(HashTable&&) = delete;

    bool Has(const std::string& key) const;
    bool Add(const std::string& key);
    bool Remove(const std::string& key);

private:
    std::string* table;
    int table_size = 0;
    int elements_ammount = 0;
    int deleted_ammount = 0;
    int hash_function(const std::string& key) const;
    void rehash();
};

void HashTable::rehash() {
    std::string* old_table = table;
    int old_table_size = table_size;

    if (deleted_ammount * 2 <= 1) table_size *= 2;


    table = new std::string[table_size];
    for (int i = 0; i < table_size; i++) {
        table[i] = "NONE";
    }

    elements_ammount = 0;
    deleted_ammount = 0;

    for (int i = 0; i < old_table_size; i++) {
        if (old_table[i] != "NONE" && old_table[i] != "DELETED") {
            Add(old_table[i]);
        }
    }

    delete[] old_table;
}

int HashTable::hash_function(const std::string& key) const {
    int hash = 0;
    int a = 47;
    for (int i = 0; key[i] != 0; ++i) {
        hash = (hash*a + key[i]) % table_size;
    }
    return hash;
}

HashTable::HashTable(int initial_size) {
    table_size = initial_size;
    table = new std::string[table_size];
    for (int i = 0; i < table_size; i++) {
        table[i] = "NONE";
    }
}

HashTable::~HashTable() {
    delete[] table;
}

bool HashTable::Has(const std::string& key) const {
    assert(!key.empty());

    int hash = (table_size + (hash_function(key) - 2)) % table_size;
    int i = 2;
    while (table[hash] != "NONE") {
        if (table[hash] == key) {
            return true;
        }
        hash = (hash + i++) % table_size;
    }
    return false;
}

bool HashTable::Add(const std::string& key) {
    assert(!key.empty());

    int hash = (table_size + (hash_function(key) - 2)) % table_size;

    int i = 2;

    int deleted_idx = -1;

    while (table[hash] != "NONE") {
        if (table[hash] == key) {
            return false;
        }

        if (table[hash] == "DELETED") deleted_idx = hash;

        hash = (hash + i++) % table_size;
    }

    if (deleted_idx != -1) {
        hash = deleted_idx;
        deleted_ammount -= 1;
    }
    if (table[hash] != "DELETED") elements_ammount += 1;

    table[hash] = key;

    if (elements_ammount >= (table_size * 3 / 4)) {
        rehash();
    }

    return true;
}

bool HashTable::Remove(const std::string& key) {
    assert(!key.empty());

    int hash = (table_size + (hash_function(key) - 2)) % table_size;

    int i = 2;
    while (table[hash] != "NONE") {
        if (table[hash] == key) {
            deleted_ammount += 1;
            table[hash] = "DELETED";
            return true;
        }
        hash = (hash + i++) % table_size;
    }
    return false;
}


int main() {
    HashTable table(8);

    char command = ' ';
    std::string value;
    while (std::cin >> command >> value) {
        switch (command) {
            case '?':
                std::cout << (table.Has(value) ? "OK" : "FAIL") << std::endl;
                break;
            case '+':
                std::cout << (table.Add(value) ? "OK" : "FAIL") << std::endl;
                break;
            case '-':
                std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
                break;
        }
    }
    return 0;
}
