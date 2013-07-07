//  Test unordered_map in C++11
//  For GCC, it requires to be compiled with flag -std=c++0x

#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector< pair<int, int> > t;
    t.push_back(make_pair(1, 2));
    t.push_back(make_pair(15, 4));

    unordered_map<int, int> q(t.begin(), t.end());
    for (auto& x: q)
        cout << x.first << ":" << x.second << endl;
    return 0;
}

