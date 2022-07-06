#include "vector.hpp"
#include <vector>

int main(){
    std::vector<int> v1(10);
    ft::vector<int> v2(10);

    std::cout << v1.at(10) << std::endl;
    // std::cout << v2.get_allocator() << std::endl;
}