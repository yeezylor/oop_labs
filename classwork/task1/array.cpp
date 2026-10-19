#include "array.h"

Container::Container() {
    size_ = 0;
}

Container::~Container() {}

void Container::set_size(size_t size) {
    size_ = size;
}

std::size_t Container::size() const {
    return size_;
}

Array::Array() {
    data_ = nullptr;
}   

Array::Array(const Array& arr) : data_(new std::string[size()]) {
    for (size_t i = 0; i < size(); i++) {
        data_[i] = arr.data_[i];
    }
    set_size(arr.size());
}

Array::~Array() {
    delete[] data_;  
}

Array& Array::operator=(const Array& arr) {
    if (this == &arr) {
        return *this;
    }

    std::string* new_data = new std::string[arr.size()];
    for (size_t i = 0; i < arr.size(); i++) {
        new_data[i] = arr.data_[i];
    }
    delete[] data_;
    data_ = new_data;
    set_size(arr.size());

    return *this;
}

std::string& Array::operator[](int ind) const{
    return data_[ind];
}

bool Array::operator==(const Array& other) {
    if (size() != other.size()) {
        return false;
    }
    for (size_t i = 0; i < size(); i++) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

void Array::clear() {
    delete[] data_;
    data_ = nullptr;
    set_size(0);
}

void Array::put(std::size_t index, std::string value) {
    if (index >= size()) {
        std::size_t new_size = index + 1;
        std::string* new_data = new std::string[new_size];

        for (std::size_t i = 0; i < size(); i++) {
            new_data[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
        set_size(new_size);
    }
    data_[index] = value;
}

std::string Array::get(std::size_t index) {
    if (index >= size()) {
        return "";
    }
    return data_[index];
}