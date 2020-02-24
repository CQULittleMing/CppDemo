#include <utility>

enum class shape_type {  
    circle,  
    triangle,  
    rectangle,
};

class shape
{
public:
    shape(){};
    ~shape(){};
};

class circle : public shape {
public:
    circle(){};
    ~circle(){};
};

class triangle : public shape {
public:
    triangle(){};
    ~triangle(){};
};

class rectangle : public shape {
public:
    rectangle(){};
    ~rectangle(){};
};

template <typename T>
class smart_ptr {
public:
  explicit smart_ptr(T* ptr = nullptr): ptr_(ptr) {}
  smart_ptr(smart_ptr& other){
    ptr_ = other.release();
  }
  smart_ptr& operator=(smart_ptr& rhs){
    smart_ptr(rhs).swap(*this);
    return *this;
  }
  ~smart_ptr()
  {
    delete ptr_;
  }
  T* get() const { return ptr_; }
  T& operator*() const { return *ptr_;} // 重载 *
  T* operator->() const { return ptr_;} // 重载->
  operator bool() const { return ptr_;}

private:
  T* ptr_;
  T* release() {
    T* ptr = ptr_;
    ptr_ = nullptr;
    return ptr;
  }
  void swap(smart_ptr& rhs) {
    using std::swap;    
    swap(ptr_, rhs.ptr_);
  }
};

shape* create_shape(shape_type type){
    switch (type) {
        case shape_type::circle:    
            return new circle();
        case shape_type::triangle:
            return new triangle();
        case shape_type::rectangle:
            return new rectangle();
    }
}

int main(int argc, char const *argv[]) {
    smart_ptr<shape> ptr1{create_shape(shape_type::circle)};
    smart_ptr<shape> ptr2{ptr1};
    return 0;
}