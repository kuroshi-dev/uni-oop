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
    String(const char *str);
    String(const String &other);

    ~String();

    String &operator=(const String &other);

    String operator+(const String &other) const;
    bool operator==(const String &other) const;
    bool operator!=(const String &other) const;
    char &operator[](size_t index);

    friend std::ostream &operator<<(std::ostream &os, const String &str);

    size_t getLength();
    char *c_str();
    bool isEmpty();
};

#endif // STRING_H
