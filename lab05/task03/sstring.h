#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <string.h>
#include <cstring>
#include <stdexcept>

class String
{
private:
    char *data;
    size_t length;

public:
    String();
    String(char *str);
    String(String &other);

    ~String();

    String &operator=(String &other);

    String operator+(String &other);
    bool operator==(String &other);
    bool operator!=(String &other);
    char &operator[](size_t index);

    friend std::ostream &operator<<(std::ostream &os, String &str);

    size_t getLength();
    char *c_str();
    bool isEmpty();
};

#endif // STRING_H
