//  See Random Number Generation in C++11 for more reference.
//  http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3551.pdf

#include <random>

using namespace std;

int main() {
    random_device rdev{};
    default_random_engine engine{rdev()};
    uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < 20; i++) {
        double val = distribution(engine);
        printf("%.3f\n", val);
    }

    return 0;
}

