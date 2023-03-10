#include <iostream>
#include <cstring>
#include <stdexcept>
#include <string>

template <typename T>
class String{
    T *mData = nullptr;
  void init(const T *newData){
    try{
      int new_len = newData ? std::char_traits<T>::length(newData) : 0 ;
      mData = new T[new_len+1]();
      std::memcpy(mData, newData, new_len);
      mData[std::char_traits<T>::length(mData)] = '\0';
    } catch(const std::bad_alloc &msg){
      std::cerr << "Allocation failed: " << msg.what() << std::endl;
      throw;
    } catch (const std::exception &e){
      std::cerr << "Exception: " << e.what() << std::endl;
      throw;
    }
    }

  void creatOne(const String &s){
    // int length = mData ? length: 0;
    int len = mData ? std::char_traits<T>::length(mData) : 0 ;
    int new_len = s.mData ? std::char_traits<T>::length(s.mData) : 0;
    try{
      T *newData = new T[new_len + len +1]();
      std::memcpy(newData, mData, len);
      std::memcpy(newData + len ,s.mData,new_len);
      //newData[new_length+length+1] = '\0';
      delete[] mData;
      mData = newData;
    } catch(const std::bad_alloc &msg){
      std::cerr << "Allocation failed: " << msg.what() << std::endl;
      throw;
    } catch (const std::exception &e){
      std::cerr << "Exception: " << e.what() << std::endl;
      throw;
    }
    }

  void creatTwo(T c){
    // int length = mData ? length: 0;
    int len= mData ? std::char_traits<T>::length(mData) : 0 ;
    try {
      T *newData = new T[len+2]();
      std::memcpy(newData, mData, len);
      newData[len] = c;
      newData[len+1] = '\0';
      delete[] mData;
      mData = newData;
      //return *this;
    } catch(const std::bad_alloc &msg){
      std::cerr << "Allocation failed: " << msg.what() << std::endl;
      throw;
    } catch (const std::exception &e){
      std::cerr << "Exception: " << e.what() << std::endl;
      throw;
    } 
    }

 public:
    String():mData(nullptr){}
    String(const T *s){
        init(s);
    }
    // String (const T &s){
    //     init(s);
    // }
    String(const String &s){
        init(s.mData);
    }
    String& operator+=(const String &s){
        creatOne(s);
        return *this;
    }
    String& operator+=(T c){
        creatTwo(c);
        return *this;
    }
    String& operator = (const String& s){
        if(this != &s){
            if(s.mData == nullptr) {return *this;}
            else {
               init(s.mData);
               return *this;
            }
        }
    }
    friend String operator+(const String &s1, const String& s2){
        String tmp(s1);
        return tmp += s2;
    }
    friend String operator+(const T* c, const String & s){
        String tmp;
        tmp.init(c);
        return tmp+=s;
    }
    bool operator > (const String &s) const{
      int len = mData ? std::char_traits<T>::length(mData) : 0 ;
        return (len > std::char_traits<T>::length(s.mData));
    }
    bool operator <= (const String &s)const {
      int len = mData ? std::char_traits<T>::length(mData) : 0 ;
        return (len <= std::char_traits<T>::length(s.mData));
    }
    bool operator!() const{
      int len = mData ? std::char_traits<T>::length(mData) : 0 ;
        return (mData != nullptr || len != 0);
    }
    T& operator[](int i){
      int len = mData ? std::char_traits<T>::length(mData) : 0 ;
        if(mData == nullptr) throw "mData nullptr!!";
        if(i<0 || i >= len){
            throw "index out of bounds!!";
        } else {
            return mData[i];
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const String& str){
        // if(mData == nullptr) throw "mData nullptr";
        try{
            os << str.mData;
            return os;
        } catch (const std::exception &e){
            std::cerr<< "Exception: " << e.what() << std::endl;
            throw;
        }
    }
    friend std::istream& operator>>(std::istream& is, String& str){
        try{
            T buffer[1000];
            is >> buffer;
            str = buffer;
            return is;
        } catch (const std::exception &e){
            std::cerr << "Exception: " << e.what() << std::endl;
            throw;
        }
    }
    void print() const
    {
      if (mData == nullptr) {throw "mData nullptr";}
      std::cout << mData << std::endl;
    }
    T* convert() const {}
    ~String(){
        delete[] mData;
    }
    
};

template <typename T>
void f(T* str){}
int main(int argc, char **argv){
// String<wchar_t> s1, s2;
// s1 += s2;
// s1 += L'a'; 
// s1[0] = L'b'; 
// s1 += L"Hello"; 
// s2 = L"Hello" + s1; 
String<char> s1,s2;
s1 += s2;
s1 += 'a';
s1[0] = 'b';
s1 += "Hello";
s2 = "Hello" + s1    ;    
s2.print();
f(s2.convert());
if (s2 > s1) {
    std::cout << s1 << std::endl; 
} else if (s1 <= s2) {
    std::cout << s2 << std::endl; 
}

if (!s1)
    std::cin >> s1; 

}    