#include "test_class_new.h"
#include<iostream>
using namespace std;  
A::A(int i){
    cout << i << endl;
}

void A::print(string s){
    cout << s << endl;
}

B::B(){

}

B::~B(){
    
}

int main(int argc, char const *argv[]){
    B* b = new B();
    b->mA.print("dddd");
    return 0;
}