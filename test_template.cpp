#include "test_template.h"
#include <iostream>

using namespace std;
using namespace test;


namespace test{

void swap(int&a , int& b) {
    int temp = a;
    a =  b;
    b = temp;
    cout << "swap int" << endl;
}

template<typename  T> void swap(T& t1, T& t2) {
    T tmpT;
    tmpT = t1;
    t1 = t2;
    t2 = tmpT;
    cout << "swap template" << endl;
}

template<class T> Stack<T>::Stack(){
    m_maxSize = 100;
    m_size = 0;
    m_pT = new T[m_maxSize];
}

template <class T>  Stack<T>::~Stack() {
   delete [] m_pT ;
}

template <class T> void Stack<T>::push(T t) {
    m_size++;
    m_pT[m_size - 1] = t;
}

template <class T> T Stack<T>::pop() {
    T t = m_pT[m_size - 1];
    m_size--;
    return t;
}

template <class T> bool Stack<T>::isEmpty() {
    return m_size == 0;
}

// T1 T2 表示两个模板参数，重载的是" " 空格运算符
template <class T> template <class T2>  Stack<T>::operator Stack<T2>() {
    Stack<T2> StackT2;
    for (int i = 0; i < m_size; i++) {
        StackT2.push((T2)m_pT[m_size - 1]);
    }
    return StackT2;
}

}



int main(){
    int a = 0;
    int b = 0;
    string s1 = "s1";
    string s2 = "s2";
    test::swap(s1, s2);
    Stack<Circle*> pcircleStack;
    Stack<Shape*> pshapeStack;
    pcircleStack.push(new Circle);
    pshapeStack = pcircleStack;
    cout << "end" << endl;
    return 0;
}