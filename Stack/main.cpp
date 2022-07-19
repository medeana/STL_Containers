#include "stack.hpp"

int main() {
    ft::stack<int> s;
    std::cout << s.size() << std::endl;
    for (int i = 0; i < 15; i++)
        s.push(i);  
    std::cout << s.top() << std::endl;
    return 0;
}
