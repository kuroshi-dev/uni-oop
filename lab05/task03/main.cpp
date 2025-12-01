#include "sstring.h"

using namespace std;

int main()
{
    cout << "=== Testing String class ===" << endl;

    cout << "\n1. Creating String objects:" << endl;
    String str1("Hello");
    String str2("World");
    String str3;       // empty string
    String str4(str1); // copy constructor

    cout << "str1: " << str1 << endl
         << "str2: " << str2 << endl
         << "str3: " << str3 << endl
         << "str4 (copy of str1): " << str4 << endl;

    cout << "\n2. Testing concatenation operator (+):" << endl;
    String str5 = str1 + String(" ") + str2 + String("!");
    cout << "str1 + \" \" + str2 + \"!\": " << str5 << endl;

    cout << "\n3. Testing comparison operators:" << endl
         << "str1 == str2: " << (str1 == str2 ? "true" : "false") << endl
         << "str1 == str4: " << (str1 == str4 ? "true" : "false") << endl
         << "str1 != str2: " << (str1 != str2 ? "true" : "false") << endl
         << "str1 != str4: " << (str1 != str4 ? "true" : "false") << endl;

    cout << "\n4. Testing character access operator ([]):" << endl
         << "Characters in str1 \"" << str1 << "\":" << endl;
    for (size_t i = 0; i < str1.getLength(); ++i)
    {
        cout << "str1[" << i << "] = '" << str1[i] << "'" << endl;
    }

    cout << "\nChanging first character of str1 to 'X':" << endl;
    str1[0] = 'X';
    cout << "str1 after change: " << str1 << endl;

    cout << "\n5. Testing output operator (<<):" << endl
         << "Output of all strings:" << endl
         << "str1: " << str1 << endl
         << "str2: " << str2 << endl
         << "str3: " << str3 << endl
         << "str4: " << str4 << endl
         << "str5: " << str5 << endl;

    cout << "\n6. Additional tests:" << endl
         << "Length of str1: " << str1.getLength() << endl
         << "Length of str2: " << str2.getLength() << endl
         << "Length of str3: " << str3.getLength() << endl
         << "str3 is empty: " << (str3.isEmpty() ? "true" : "false") << endl;

    cout << "\n7. Testing operation chaining:" << endl;
    String result = String("Hello") + String(" ") + String("World") + String("!");
    cout << "Result of concatenation chain: " << result << endl;

    cout << "\n8. Testing assignment operator:" << endl;

    String str6;
    str6 = str2;

    cout << "str6 = str2: " << str6 << endl
         << "str6 == str2: " << (str6 == str2 ? "true" : "false") << endl;

    cout << "\n9. Testing exception handling:" << endl;
    try
    {
        cout << "Trying to access character at index " << str1.getLength() + 5 << endl;
        char c = str1[str1.getLength() + 5];
        cout << "Character: " << c << endl;
    }
    catch (const out_of_range &e)
    {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "\n--- Testing completed ---" << endl;

    return 0;
}
