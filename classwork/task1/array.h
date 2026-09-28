#pragma once

#include <string>

class Array {
public:

    // конструктор
    Array();

    Array(const Array&);

    // деструктор
    ~Array();

    // получить текущий размер
    std::size_t size() const;

    // очистка, после неё текущий размер = 0
    void clear();

    // положить значение по данному индексу. Если индекс больше или равен текущему размеру, увеличить размер
    void put(std::size_t index, std::string value);

    // получить значение по индексу. Если индекс больше или равен текущему размеру, вернуть пустую строку
    std::string get(std::size_t index);

private:
    std::string* data_; // массив
    std::size_t size_;  // текущий размер массива (количество элементов)
};