#include "vector.hpp"
#include <vector>

int main(){
    std::vector<int> v1(5, 6);
    ft::vector<int> v2(5, 6);

    std::cout << v1.size() << std::endl;
    std::cout << v2.size() << std::endl;

    std::cout << " " << std::endl;

    v1.resize(8);
    v2.resize(8);

    // v1.reserve(8);
    // v2.reserve(8);

    std::cout << " " << std::endl;

    std::cout << v1.size() << std::endl;
    std::cout << v2.size() << std::endl;

    std::cout << v1[7] << std::endl;
    std::cout << v2[7] << std::endl;

    // std::cout << v1.capacity() << std::endl;
    // std::cout << v2.capacity() << std::endl;
}