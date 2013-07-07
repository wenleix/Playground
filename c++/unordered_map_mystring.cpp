//  Test unordered_map in C++11, with my structure.
//  For GCC, it requires to be compiled with flag -std=c++0x

#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

using namespace std;

struct MyString {
    char name[20];
    
    MyString(const char* qname) {
        if (strlen(qname) > 19) {
            throw std::runtime_error("MyString Too Long!!");
        }
        strcpy(name, qname);
    }

    bool operator==(const MyString& other) const {
        return strcmp(name, other.name) == 0;
    }
};

struct MyStringHash {
    size_t operator() (const MyString& c) const {
    // djb2
    // http://www.cse.yorku.ca/~oz/hash.html
        unsigned long hash = 5381;  
        for (const char* p = c.name; *p != 0; p++) {
            hash = ((hash << 5) + hash) + *p;    //  hash * 33 + *p
        }
        return hash;
    }
};

int main() {
    vector< pair<MyString, int> > t;
    t.push_back(make_pair(MyString("abc"), 2));
    t.push_back(make_pair(MyString("def"), 4));

    unordered_map<MyString, int, MyStringHash> q(t.begin(), t.end());
    for (auto& x: q)
        cout << x.first.name << ":" << x.second << endl;
    return 0;
}

