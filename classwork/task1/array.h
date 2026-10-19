#pragma once

#include <string>

class Container {
public:
    size_t size() const;
protected:
    void set_size(size_t size);
private:
    size_t size_;
};

class Array : public Container{
public:

    // конструктор
    Array();

    Array(const Array&);

    // деструктор
    ~Array();

    Array& operator=(const Array& arr);

    std::string& operator[](int ind) const;

    bool operator==(const Array& other);

    // очистка, после неё текущий размер = 0
    void clear();

    // положить значение по данному индексу. Если индекс больше или равен текущему размеру, увеличить размер
    void put(std::size_t index, std::string value);

    // получить значение по индексу. Если индекс больше или равен текущему размеру, вернуть пустую строку
    std::string get(std::size_t index);

private:
    std::string* data_; // массив
};
