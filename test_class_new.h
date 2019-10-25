#include <string>
using namespace std;  


class A {
public:
    A(int i);
    void print(string str);
};

class B
{
public:
    B();
    ~B();
    A mA;
};