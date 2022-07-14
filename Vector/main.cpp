#include "vector.hpp"
#include <vector>

int main(){
    ft::vector<int> v1(15);

    for (int i = 0; i < 30; i++)
    {
        v1.push_back(i);
        // std::cout << v1[i] << std::endl;

    }

    ft::vector<int>::iterator it;
    ft::vector<int>::iterator ite;

    it = v1.begin();
    ite = v1.end();

    // while (it != ite)
    // {
    //     std::cout << *it << std::endl;
    //     it++;
    // }

    ft::vector<int> v3(it, ite);

    ft::vector<int>::iterator it2;
    ft::vector<int>::iterator ite2;

    it2 = v3.begin();
    ite2 = v3.end();

    while (it2 != ite2)
    {
        std::cout << *it2 << std::endl;
        it2++;
    }

    // std::cout << v3[1] << std::endl;


    // // std::cout << v1.size() << std::endl;
    // // std::cout << v2.size() << std::endl;

    // // std::cout << " " << std::endl;
    // // std::cout << " " << std::endl;

    // // std::cout << "size " << v1.size() << std::endl;
    // // std::cout << "size " << v2.size() << std::endl;

    // // std::cout << v1[4] << std::endl;
    // // std::cout << v2[4] << std::endl;

    // v1.push_back(54);
    // v2.push_back(54);

    // // for (int i = 0; i < 6; i++){
    // //     std::cout << "V1 = " << v1[i] << "  " << "V2 = " << v2[i] << std::endl;
    // // }

    // // std::cout << " " << std::endl;
    // // std::cout << " " << std::endl;

    // v1.assign(2, 4);
    // v2.assign(2, 4);

    // // for (int i = 0; i < 6; i++){
    // //     std::cout << "V1 = " << v1[i] << "  " << "V2 = " << v2[i] << std::endl;
    // // }

    // std::cout << " " << std::endl;
    // std::cout << " " << std::endl;

    // for (int i = 0; i < 6; i++){
    //     std::cout << "V1 = " << v1[i] << "  " << "V2 = " << v2[i] << std::endl;
    // }
    // // for (int i = 0; i < 5; i++){
    // //     std::cout << "V2 = " << v2[i] << "  " << "V3 = " << v3[i] << std::endl;
    // // }

    // // std::cout << " " << std::endl;
    // // std::cout << " " << std::endl;

    // std::cout << "size " << v1.size() << std::endl;
    // std::cout << "size " << v2.size() << std::endl;

    // std::cout << v1.capacity() << std::endl;
    // std::cout << v2.capacity() << std::endl;
}