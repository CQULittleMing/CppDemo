#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

static char a[50] = "bbbb";

class A{
public:
    static char* getA(){
        memcpy(a,"aaaaa",5);
        printf("%s\n", a);
        memcpy(a,"bbbb",5);
        return a;
    }
};

int main() {
    char* a  = A::getA();
    printf("%s\n", a);
}