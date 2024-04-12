#include "../tests/tests.hpp"

int main() {
    Test test;
    test.test1();  // github test
    std::cout << "---------" << std::endl;
    test.test2();  // compare two string
    std::cout << "---------" << std::endl;
    test.test3();  // overtaking operator
    std::cout << "---------" << std::endl;
    test.test4();  // Pair <string, string> + uncorrect key
    std::cout << "---------" << std::endl;

    return 0;
}