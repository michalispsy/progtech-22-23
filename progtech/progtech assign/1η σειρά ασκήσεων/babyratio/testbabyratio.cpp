#include <iostream>
#include "babyratio.hpp"

using namespace std;

int main() {
    rational a(3, 8); /// 3 8 -2 11
    rational b(-2, 11);
    rational c(5, 6);
    a.div(b).print();
    cout << endl;
}