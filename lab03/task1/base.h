#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <windows.h>

class Base {
public:
    Base();
    void showBase();

    int publicVar;

protected:
    int protectedVar;

private:
    int privateVar;
};

class PublicDerived : public Base {
public:
    void tryAccess();
};

class ProtectedDerived : protected Base {
public:
    void tryAccess();
};

class PrivateDerived : private Base {
public:
    void tryAccess();
};

#endif // BASE_H
