#include <iostream>
#include <cstring>
#include <stdexcept>
#include <istream>

template <typename charT>
class String {
  charT *mData = nullptr;
  void init(const charT *newData) {
    try {
      int new_len = newData ? static_cast<int>(std::char_traits<charT>::length(newData)) : 0;
      mData = new charT[new_len + 1]();
      std::memcpy(mData, newData, new_len * sizeof(charT));
      mData[new_len] = '\0';
    } catch (const std::bad_alloc &msg) {
      std::cerr << "Allocation failed: " << msg.what() << std::endl;
      throw;
    } catch (const std::exception &e) {
      std::cerr << "Exception: " << e.what() << std::endl;
      throw;
    }
  }

  void createOne(const String &s) {
    int new_len = s.mData ? static_cast<int>(std::char_traits<charT>::length(s.mData)) : 0;
    try {
      charT *newData = new charT[new_len + len() + 1]();
      std::memcpy(newData, mData, len() * sizeof(charT));
      std::memcpy(newData + len(), s.mData, new_len * sizeof(charT));
      delete[] mData;
      mData = newData;
    } catch (const std::bad_alloc &msg) {
      std::cerr << "Allocation failed: " << msg.what() << std::endl;
      throw;
    } catch (const std::exception &e) {
      std::cerr << "Exception: " << e.what() << std::endl;
      throw;
    }
  }

  void createTwo(charT c){
    try {
      charT *newData = new charT[len()+2]();
      std::memcpy(newData, mData, len()*sizeof(charT));
      newData[len()] = c;
      newData[len()+1] = '\0';
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
 public:
    String():mData(nullptr){}
    String(const charT *s){
        init(s);
    }
    String(const String &s){
        init(s.mData);
    }
    String& operator+=(const String &s){
        createOne(s);
        return *this;
    }
    String& operator+=(charT c){
        createTwo(c);
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
    friend String operator+(const charT* c, const String & s){
        String tmp;
        tmp.init(c);
        return tmp+=s;
    }
    bool operator > (const String &s) const{
        return (len() > static_cast<int>(std::char_traits<charT>::length(s.mData)));
    }
    bool operator <= (const String &s)const {
        return (len() <= static_cast<int>(std::char_traits<charT>::length(s.mData)));
    }
    bool operator!() const{
        return (mData != nullptr || len() != 0);
    }
    charT& operator[](int i){
        if(mData == nullptr) throw "mData nullptr!!";
        if(i<0 || i >= len()){
            throw "index out of bounds!!";
        } else {
            return mData[i];
        }
    }

  friend std::basic_ostream<charT>& operator<<(std::basic_ostream<charT>& os,
                                               const String& str) {
    try {
      os << str.mData;
      return os;
    } catch (const std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
      throw;
    }
  }
  friend std::basic_istream<charT>& operator>>(std::basic_istream<charT>& is,
                                               String& str) {
    try {
      charT buffer[1000];
      is >> buffer;
      str = buffer;
      return is;
    } catch (const std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
      throw;
    }
  }

    int len() const {
         return mData ? static_cast<int>(std::char_traits<charT>::length(mData)) : 0;
    }
    void print() const
    {
      if (mData == nullptr) {throw "mData nullptr";}
      std::wcout << mData << std::endl;
    }
    charT* convert() const {}
    ~String(){
        delete[] mData;
    }
    
};

template <typename charT>
void f(charT* str){}
int main(int argc, char **argv){
  String<wchar_t> s1, s2;
  s1 += s2;
  s1 += L'a'; 
  s1[0] = L'b'; 
  s1 += L"Hello"; 
  s2 = L"Hello" + s1; 
  s1.print();
  s2.print();
  f(s2.convert());
  if (s2 > s1) {
    std::wcout << s1 << std::endl; 
  } else if (s1 <= s2) {
    std::wcout << s2 << std::endl; 
  }

  if (!s1)
    std::wcin >> s1; 

}    