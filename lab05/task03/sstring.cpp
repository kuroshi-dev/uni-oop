#include "sstring.h"

using namespace std;

String::String() : data(nullptr), length(0){
    data = new char[1];
    data[0] = '\0';
}

String::String(const char *str){
    if (str == nullptr){
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }
    else{
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }
}

String::String(const String &other){
    length = other.length;
    data = new char[length + 1];
    strcpy(data, other.data);
}

String::~String(){
    delete[] data;
}

// --------------------------------------------------

String &String::operator=(const String &other){
    if (this != &other){
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }
    return *this;
}

String String::operator+(const String &other) const{
    String result;
    result.length = this->length + other.length;
    delete[] result.data;
    result.data = new char[result.length + 1];

    strcpy(result.data, this->data);
    strcat(result.data, other.data);

    return result;
}

bool String::operator==(const String &other) const{
    return strcmp(this->data, other.data) == 0;
}

bool String::operator!=(const String &other) const{
    return !(*this == other);
}

char &String::operator[](size_t index){
    if (index >= length){
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

std::ostream &operator<<(std::ostream &os, const String &str){
    os << str.data;
    return os;
}

// ----------------------------------------

size_t String::getLength(){
    return length;
}

char *String::c_str(){
    return data;
}

bool String::isEmpty(){
    return length == 0;
}
