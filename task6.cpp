#include <iostream>
#include <cstring>
#include <stdexcept>

template <class T> 
class String{
    T *mData = nullptr;
  void init(const T *newData){
    if(newData == nullptr) {return;}
    else{
    try{
      mData = new char[strlen(newData)+1] ();
      std::memcpy(mData, newData, strlen(newData)+1);
      mData[strlen(mData)] = '\0';
    } catch(const std::bad_alloc &msg){
      std::cerr << "Allocation failed: " << msg.what() << std::endl;
      throw;
    } catch (const std::exception &e){
      std::cerr << "Exception: " << e.what() << std::endl;
      throw;
    }
    }
    }

  void creatOne(String &s){
    int length = mData ? strlen(mData): 0;
    int new_length = s.mData ? strlen(s.mData): 0;
    try{
      T *newData = new char[new_length+ length +1];
      std::memcpy(newData, mData, length);
      std::memcpy(newData + length ,s.mData,new_length);
      newData[new_length+length] = '\0';
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
    int length = mData ? strlen(mData): 0;
    try {
      T *newData = new char[length+2]();
      std::memcpy(newData, mData, length);
      newData[length] = c;
      newData[length+1] = '\0';
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
    String (const T &s){
        init(s.mData);
    }
    String& operator+=(const String &s){
        creatOne(const_cast<String&>(s));
        return *this;
    }
    String& operator+=( T c){
        creatTwo(c);
        return *this;
    }
    String& operator = (const String& s){
        if(this != &s){
            if(s.mData == nullptr) {return *this;}
            else init(s.mData);
        }
    }
    friend String operator+(const String &s1, const String& s2){
        String tmp;
        return tmp += s2;
    }
    friend String operator+(const T* c, const String & s){
        String tmp;
        tmp.init(c);
        return tmp+=s;
    }
    bool operator > (const String &s) const{
        return (strlen(this->mData) > strlen(s.mData));
    }
    bool operator <= (const String &s)const {
        return (strlen(this->mData) <= strlen(s.mData));
    }
    bool operator!() const{
        return (mData != nullptr || strlen(mData) != 0);
    }
    T& operator[](int i){
        if(mData == nullptr) throw "mData nullptr!!";
        if(i<0 || i > strlen(mData)){
            throw "index out of bounds!!";
        } else {
            return mData[i];
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const String& str){
        try{
            os << str.mData;
            return os;
        } catch (const std::exception &e){
            std::cerr<< "Exception: " << e.what() << std::endl;
            throw;
        }
    }
    friend std::istream& operator >> (std::istream& is, const String& str){
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
    T* convert() const {}
    ~String(){
        delete[] mData;
    }
    
};

template <typename T>
void f(T* str){}
int main(int argc, char **argv){
    String<char> s1,s2;
    s1 += s2;
    s1 += 'a';
    s1[0] = 'b';
    s1 += "Hello";
    s2 = "Hello" + s1;
    f(s2.convert());
    if(s2 > s1){
    std::cout << s1 << std::endl;
    } else if(s1 <= s2) {
    std::cout << s2 << std::endl;
    }

    if(!s1 )  //if string not empty
    std::cin >> s1;
}    