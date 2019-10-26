
namespace test{
void swap(int&a , int& b);
template<typename T> void swap(T& t1, T& t2);

template <class T> class Stack {
    public:
        Stack();
        ~Stack();
        void push(T t);
        T pop();
        bool isEmpty();
        template<class T2>  operator Stack<T2>();
    private:
        T *m_pT;        
        int m_maxSize;
        int m_size;
};

class Shape {

};
class Circle : public Shape {
};

}