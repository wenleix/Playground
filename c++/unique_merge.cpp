//  A STL Like-Function for unique and merge
//  Based on the SGI's STL implementation of unique(): http://www.sgi.com/tech/stl/stl_algo.h

template <class ForwardIterOfPair>
ForwardIterOfPair unique_merge(ForwardIterOfPair first, ForwardIterOfPair last) {
    if (first == last)
        return last;

    //  Skip unique items at the beginning
    //  adjacent_find()
    ForwardIterOfPair next = first;
    while (++next != last) {
        if (first->first == next->first)
            break;
        first = next;
    }

    //  Notice * first * cannot be * last * here.

    //  unique_copy()
    ForwardIterOfPair input = first, output = first;
    while (++input != last) {
        if (output->first != input->first)
            *++output = *input;
        else 
            output->second += input->second;
    }

    return ++output;
}

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std; 

void PrintVector(const vector< pair<int, int> >& vec) {
    for (vector< pair<int, int> >::const_iterator it = vec.begin(); it != vec.end(); it++) {
        printf("(%d, %d) ", it->first, it->second);
    }
    printf("\n"); 
}

int main() {
    //  Some simple test cases
    //  Result should be: 
    //  (blank line)
    //  (1, 3) 
    //  (1, 1) (2, 2) (3, 28) (4, 224) (5, 256) (6, 512) 
    //  (1, 3) (2, 4) (3, 56) (4, 960) 
    //  (1, 1) (2, 2) (3, 4) (4, 8) (5, 16) (6, 32) (7, 64) (8, 128) (9, 256) (10, 512) 
    vector< pair<int, int> > t0, t1, t2, t3, t4;
    t1.push_back(make_pair(1, 1)); 
    t1.push_back(make_pair(1, 2)); 

    t2.push_back(make_pair(1, 1));
    t2.push_back(make_pair(2, 2));
    t2.push_back(make_pair(3, 4));
    t2.push_back(make_pair(3, 8));
    t2.push_back(make_pair(3, 16));
    t2.push_back(make_pair(4, 32));
    t2.push_back(make_pair(4, 64));
    t2.push_back(make_pair(4, 128));
    t2.push_back(make_pair(5, 256));
    t2.push_back(make_pair(6, 512));

    t3.push_back(make_pair(1, 1));
    t3.push_back(make_pair(1, 2));
    t3.push_back(make_pair(2, 4));
    t3.push_back(make_pair(3, 8));
    t3.push_back(make_pair(3, 16));
    t3.push_back(make_pair(3, 32));
    t3.push_back(make_pair(4, 64));
    t3.push_back(make_pair(4, 128));
    t3.push_back(make_pair(4, 256));
    t3.push_back(make_pair(4, 512));
    
    t4.push_back(make_pair(1, 1));
    t4.push_back(make_pair(2, 2));
    t4.push_back(make_pair(3, 4));
    t4.push_back(make_pair(4, 8));
    t4.push_back(make_pair(5, 16));
    t4.push_back(make_pair(6, 32));
    t4.push_back(make_pair(7, 64));
    t4.push_back(make_pair(8, 128));
    t4.push_back(make_pair(9, 256));
    t4.push_back(make_pair(10, 512));
    
    t0.resize(unique_merge(t0.begin(), t0.end()) - t0.begin());
    t1.resize(unique_merge(t1.begin(), t1.end()) - t1.begin());
    t2.resize(unique_merge(t2.begin(), t2.end()) - t2.begin());
    t3.resize(unique_merge(t3.begin(), t3.end()) - t3.begin());
    t4.resize(unique_merge(t4.begin(), t4.end()) - t4.begin());

    PrintVector(t0);
    PrintVector(t1);
    PrintVector(t2);
    PrintVector(t3);
    PrintVector(t4);

    return 0;
}

