#include "base.h"

using namespace std;

Base::Base() : publicVar(1), protectedVar(2), privateVar(3) {}

void Base::showBase() {
    cout << "Base::publicVar = " << publicVar << endl;
    cout << "Base::protectedVar = " << protectedVar << endl;
    cout << "Base::privateVar = " << privateVar << endl;
}

void PublicDerived::tryAccess() {
    cout << "\nPublicDerived" << endl;

    try {
        publicVar = 10; // public -> public
        cout << "publicVar accessible: " << publicVar << endl;
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
    }

    try {
        protectedVar = 20; // protected -> protected
        cout << "protectedVar accessible: " << protectedVar << endl;
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
    }

    try {
        // privateVar = 30;
        throw runtime_error("privateVar NOT ACCESSIBLE");
    } catch (const exception& e) {
        cerr << "ACCESS ERROR: " << e.what() << endl;
    }
}

void ProtectedDerived::tryAccess() {
    cout << "\nProtectedDerived" << endl;

    try {
        publicVar = 100; // public -> protected
        cout << "publicVar accessible inside: " << publicVar << endl;
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
    }

    try {
        protectedVar = 200; // protected -> protected
        cout << "protectedVar accessible inside: " << protectedVar << endl;
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
    }

    try {
        // privateVar = 300;
        throw runtime_error("privateVar NOT ACCESSIBLE");
    } catch (const exception& e) {
        cerr << "ACCESS ERROR: " << e.what() << endl;
    }
}

void PrivateDerived::tryAccess() {
    cout << "\nPrivateDerived" << endl;

    try {
        publicVar = 1000; // public -> private
        cout << "publicVar accessible inside: " << publicVar << endl;
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
    }

    try {
        protectedVar = 2000; // protected -> private
        cout << "protectedVar accessible inside: " << protectedVar << endl;
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
    }

    try {
        // privateVar = 3000;
        throw runtime_error("privateVar NOT ACCESSIBLE");
    } catch (const exception& e) {
        cerr << "ACCESS ERROR: " << e.what() << endl;
    }
}
