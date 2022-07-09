#include "vector.hpp"
#include <vector>

int main(){
    std::vector<int> v1(5, 1);
    ft::vector<int> v2(5, 6);
    ft::vector<int> v3(5, 4);

    // std::cout << v1.size() << std::endl;
    // std::cout << v2.size() << std::endl;

    // std::cout << " " << std::endl;
    // std::cout << " " << std::endl;

    // std::cout << "size " << v1.size() << std::endl;
    // std::cout << "size " << v2.size() << std::endl;

    // std::cout << v1[4] << std::endl;
    // std::cout << v2[4] << std::endl;

    v1.push_back(54);
    v2.push_back(54);

    // for (int i = 0; i < 6; i++){
    //     std::cout << "V1 = " << v1[i] << "  " << "V2 = " << v2[i] << std::endl;
    // }

    // std::cout << " " << std::endl;
    // std::cout << " " << std::endl;

    // v1.pop_back();
    // v2.pop_back();

    // for (int i = 0; i < 6; i++){
    //     std::cout << "V1 = " << v1[i] << "  " << "V2 = " << v2[i] << std::endl;
    // }
    v2.swap(v3);

    std::cout << " " << std::endl;
    std::cout << " " << std::endl;

    for (int i = 0; i < 6; i++){
        std::cout << "V1 = " << v1[i] << "  " << "V2 = " << v2[i] << std::endl;
    }
    // for (int i = 0; i < 5; i++){
    //     std::cout << "V2 = " << v2[i] << "  " << "V3 = " << v3[i] << std::endl;
    // }

    // std::cout << " " << std::endl;
    // std::cout << " " << std::endl;

    // std::cout << "size " << v1.size() << std::endl;
    // std::cout << "size " << v2.size() << std::endl;

    // std::cout << v1.capacity() << std::endl;
    // std::cout << v2.capacity() << std::endl;
}