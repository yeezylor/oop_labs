#include "array.h"

Array::Array() {
    data_ = nullptr;
    size_ = 0;
}

Array::Array(const Array& arr) : data_(new std::string[arr.size_]) {
    for (size_t i = 0; i < arr.size_; i++) {
        data_[i] = arr.data_[i];
    }
    size_ = arr.size_;
}

Array::~Array() {
    delete[] data_;  
}

std::size_t Array::size() const {
    return size_;
}

void Array::clear() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
}

void Array::put(std::size_t index, std::string value) {
    if (index >= size_) {
        std::size_t new_size = index + 1;
        std::string* new_data = new std::string[new_size];

        for (std::size_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
        size_ = new_size;
    }
    data_[index] = value;
}

std::string Array::get(std::size_t index) {
    if (index >= size_) {
        return "";
    }
    return data_[index];
}