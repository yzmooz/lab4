#include "CustomHashTable.h"
#include <iostream>
#include <cassert>

void runTests() {
    CustomHashTable<std::string, double> hashTable;
    assert(hashTable.size() == 0);

    hashTable.add("Laptop", 1000);
    assert(hashTable.size() == 1);

    hashTable.add("Laptop", 1200);
    assert(hashTable.size() == 1);  // Размер остаётся прежним

    hashTable.add("Phone", 500);
    assert(hashTable.size() == 2);


    hashTable.remove("Phone");
    assert(hashTable.size() == 1);

    hashTable.clear();
    assert(hashTable.size() == 0);

    std::cout << "Все тесты прошли успешно" << std::endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    runTests();

    CustomHashTable<std::string, double> items;
    items.add("Laptop", 1500);
    items.add("Camera", 800);
    items.add("Phone", 600);
    items.add("Headphones", 200);

    std::cout << "Общий потенциальный доход: " << items.calculateTotalValue() << "\n";

    items.saveToFile("items.txt");
    CustomHashTable<std::string, double> loadedItems; 
    loadedItems.loadFromFile("items.txt"); 

    if (items == loadedItems) {
        std::cout << "Товары загружены и соответствуют оригинальной коллекции." << std::endl;
    }
    else {
        std::cout << "Загруженые товары загруженые не соответствуют оригинальной коллекции." << std::endl; 
    }

    return 0;
}
