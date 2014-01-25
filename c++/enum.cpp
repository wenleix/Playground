#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

enum myType { my1 = 0, my2 = 1, my3 = 2 };

int main() {
    myType a = (myType)(1);
    if (a == my1) {
        cout << "my1" << endl;
    } else if (a == my2) {
        cout << "my2" << endl;
    } else if (a == my3) {
        cout << "my3" << endl;
    }


    myType b = my3;
    cout << (int)b << endl;
}

