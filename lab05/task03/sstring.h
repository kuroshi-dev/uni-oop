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
    String();                    // Конструктор по умолчанию
    String(const char *str);     // Конструктор от C-строки
    String(const String &other); // Конструктор копирования

    ~String();

    String &operator=(const String &other);

    // Перегруженные операторы
    String operator+(const String &other) const; // Конкатенация
    bool operator==(const String &other) const;  // Сравнение на равенство
    bool operator!=(const String &other) const;  // Сравнение на неравенство
    char &operator[](size_t index);              // Доступ к символу
    const char &operator[](size_t index) const;  // Константный доступ к символу

    // Дружественная функция для вывода
    friend std::ostream &operator<<(std::ostream &os, const String &str);

    // Дополнительные методы
    size_t getLength() const;
    const char *c_str() const;
    bool isEmpty() const;
};

#endif // STRING_H
