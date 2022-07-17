#include "vector.hpp"
#include <vector>

int main(){
    ft::vector<int> v1(5, 3);

    ft::vector<int>::iterator it;
    ft::vector<int>::iterator ite;
    it = v1.begin() + 2;
    v1.insert(it, 300);
    it = v1.begin();
    ite = v1.end();
    while(it != ite)
    {
        std::cout << *it << std::endl;
        it++;
    }
    // ft::vector<int> v1(15);

    // for (int i = 0; i < 30; i++)
    // {
    //     v1.push_back(i);
    //     // std::cout << v1[i] << std::endl;

    // }

    // ft::vector<int>::iterator it;
    // ft::vector<int>::iterator ite;

    // it = v1.begin() + 3;
    // ite = v1.end();

    // // while (it != ite)
    // // {
    // //     std::cout << *it << std::endl;
    // //     it++;
    // // }

    // ft::vector<int> v3(it, ite);

    // ft::vector<int>::iterator it2;
    // ft::vector<int>::iterator ite2;

    // it2 = v3.begin();
    // ite2 = v3.end();

    // while (it2 != ite2)
    // {
    //     std::cout << *it2 << std::endl;
    //     it2++;
    // }
}