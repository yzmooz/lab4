#ifndef CUSTOMHASHTABLE_H
#define CUSTOMHASHTABLE_H

#include <vector>
#include <list>
#include <string>
#include <functional>
#include <fstream>
#include <iostream>

const size_t TABLE_SIZE = 101;  // Размер хэш-таблицы

// Шаблонный класс для хэш-таблицы
template <typename KeyType, typename ValueType>
class CustomHashTable {  
private: 
    std::vector<std::list<std::pair<KeyType, ValueType>>> table; 

    size_t hashFunction(const KeyType& key) const {
        return std::hash<KeyType>{}(key) % TABLE_SIZE;
    }

public:
    // Конструктор по умолчанию
    CustomHashTable() : table(TABLE_SIZE) {}

    // Конструктор копирования
    CustomHashTable(const CustomHashTable& other) : table(other.table) {}

    // Деструктор
    ~CustomHashTable() {}

    // Добавление или обновление значения
    void add(const KeyType& key, const ValueType& value) {
        size_t index = hashFunction(key); 
        for (auto& pair : table[index]) { 
            if (pair.first == key) { 
                pair.second = std::max(pair.second, value); 
                return;
            } 
        }
        table[index].emplace_back(key, value);
    }

    // Удаление элемента 
    void remove(const KeyType& key) {
        size_t index = hashFunction(key);
        table[index].remove_if([&key](const std::pair<KeyType, ValueType>& pair) { 
            return pair.first == key;
            });
    }

    // Очистка коллекции
    void clear() {
        for (auto& bucket : table) { 
            bucket.clear(); 
        } 
    } 
     
    // Получение количества элементов  
    size_t size() const { 
        size_t count = 0; 
        for (const auto& bucket : table) { 
            count += bucket.size(); 
        } 
        return count; 
    }

    // Сохранение коллекции в файл
    void saveToFile(const std::string& "lb.txt") const {
        std::ofstream file("lb.txt");
        if (!file.is_open()) {
            std::cerr << "no file for writing" << std::endl;
            return;
        }
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                file << pair.first << " " << pair.second << "\n";
            }
        }
        file.close();
    }

    // Загрузка коллекции из файла
    void loadFromFile(const std::string& "lb.txt") {
        clear();
        std::ifstream file("lb.txt");
        if (!file.is_open()) {
            std::cerr << "no file for reading" << std::endl;
            return;
        }
        KeyType key;
        ValueType value;
        while (file >> key >> value) {
            add(key, value);
        }
        file.close();
    }

    // Расчёт общей суммы значений
    ValueType calculateTotalValue() const {
        ValueType total = 0;
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                total += pair.second;
            }
        }
        return total;
    }



    // Оператор сравнения ==
    bool operator==(const CustomHashTable& other) const {
        return table == other.table;
    }
};

#endif
