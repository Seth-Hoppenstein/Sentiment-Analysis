#include "DSString.h"
#include <cstring>

DSString::DSString() : data(nullptr), length(0) {}

DSString::DSString(const char* str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy(data, str);
}

DSString::DSString(const DSString& other) {
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
}

DSString::~DSString() {
    delete[] data;
}

DSString& DSString::operator=(const DSString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }
    return *this;
}

size_t DSString::getLength() const {
    return length;
}

const char* DSString::c_str() const {
    return data;
}

void DSString::append(const char* str) {
    size_t newLength = length + strlen(str);
    char* newData = new char[newLength + 1];
    strcpy(newData, data);
    strcat(newData, str);
    delete[] data;
    data = newData;
    length = newLength;
}

void DSString::clear() {
    delete[] data;
    data = nullptr;
    length = 0;
}
