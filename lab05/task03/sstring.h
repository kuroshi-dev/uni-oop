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
    const char &operator[](size_t index) const;

    friend std::ostream &operator<<(std::ostream &os, const String &str);

    size_t getLength() const;
    const char *c_str() const;
    bool isEmpty() const;
};

#endif // STRING_H
