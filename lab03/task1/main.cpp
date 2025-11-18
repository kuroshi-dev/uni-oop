#include "base.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "\n--- Testing PublicDerived ---" << endl;
    PublicDerived pd;
    pd.tryAccess();

    cout << "\nAccess attempt from OUTSIDE PublicDerived:" << endl;
    try {
        pd.publicVar = 15;
        cout << "pd.publicVar accessible from outside: " << pd.publicVar << endl;
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
    }

    cout << "\n--- Testing ProtectedDerived ---" << endl;
    ProtectedDerived protd;
    protd.tryAccess();

    cout << "\n--- Testing PrivateDerived ---" << endl;
    PrivateDerived privd;
    privd.tryAccess();


    return 0;
}
