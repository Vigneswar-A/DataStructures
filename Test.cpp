#include <iostream>

using namespace std;

class Test
{
};

int main()
{
    Test object;
    Test *p1, *p2;
    p1 = &object;
    p2 = &object;

    cout << (p1 == p2);
    return 0;
}