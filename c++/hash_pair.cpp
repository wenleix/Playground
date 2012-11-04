#include <ext/hash_set>
#include <ext/hash_map>
#include <utility>

using namespace std;

struct pair_hash {
    size_t operator()(const pair<int, int>& key) const {
        return (key.first << 9) ^ key.second;
    }
};

struct pair_equal {
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) const {
        return lhs == rhs;
    }
};

__gnu_cxx::hash_map< pair<int, int>, int, pair_hash, pair_equal> a;
__gnu_cxx::hash_set< pair<int, int>, pair_hash, pair_equal> b;

int main() {
    return 0;
}


