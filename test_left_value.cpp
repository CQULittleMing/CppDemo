#include<iostream>
#include<vector>
#include<cstring>

class MyString {
 private: 
  char* mData; 
  size_t mLen; 
  void _initmData(const char *s) {
    mData = new char[mLen+1]; 
    memcpy(mData, s, mLen); 
    mData[mLen] = '\0'; 
  } 
 public: 
  int mA = 0;
  MyString() {
    mData = NULL; 
    mLen = 0; 
  } 

  MyString(const char* p) {
    mLen = strlen (p); 
    _initmData(p); 
  } 

  MyString(const MyString& str) {
    mLen = str.mLen; 
    _initmData(str.mData); 
    std::cout << "Copy Constructor is called! source: " << str.mData << std::endl; 
  } 

  MyString& operator=(const MyString& str) {
    if (this != &str) { 
      mLen = str.mLen; 
      _initmData(str.mData); 
    } 
    std::cout << "Copy Assignment is called! source: " << str.mData << std::endl; 
    return *this; 
  }

  MyString(MyString&& str) {
    std::cout << "Move Constructor is called! source: " << str.mData << std::endl; 
    mLen = str.mLen; 
    mData = str.mData; 
    str.mLen = 0; 
    str.mData = NULL; 
  }

  MyString& operator=(MyString&& str) {
    // 此时，str是右值引用
    std::cout << "Move Assignment is called! source: " << str.mData << std::endl; 
    if (this != &str) { 
      mLen = str.mLen; 
      mData = str.mData; 
      str.mLen = 0; 
      str.mData = NULL; 
    } 
    return *this; 
 }

char* getData(){
  return mData;
 }


  virtual ~MyString() {
    if (mData) free(mData); 
  }
 }; 

void process_value(int& i) {
  // i是左值引用
  std::cout << "LValue processed: " << i << std::endl; 
} 

void process_value(int&& i) { 
  // i是右值引用
  std::cout << "RValue processed: "  << std::endl; 
}

 int main() { 
  //MyString a;
  //a = MyString("1");
  std::vector<MyString> vec(10);
  vec.emplace_back(MyString("2"));
  //vec.emplace_back(MyString("3"));
  //vec.emplace_back(MyString("3"));
  //vec.emplace_back(MyString("4"));
  // 0 是右值，a是左值
  // MyString a("2");
  std::cout << "aaaaaaaa" << std::endl;
  for (auto str: vec) {
      std::cout << "aaaaaaaa" << std::endl;
      std::cout << str.getData() << ".\n";  
  }
  /*int i = 0; 
  process_value(i);
  // 3 是右值，x是右值引用
  int&& x = 3;
  process_value(x); 

  std::string str = "Hello";
  std::vector<std::string> v;
  //调用常规的拷贝构造函数，新建字符数组，拷贝数据
  v.push_back(str);
  std::cout << "After copy, str is \"" << str << "\"\n";
  //调用移动构造函数，掏空str，掏空后，最好不要使用str
  v.push_back(std::move(str));
  std::cout << "After move, str is \"" << str << "\"\n";
  std::cout << "The contents of the vector are \"" << v[0] << "\", \"" << v[1] << "\"\n";*/
 }