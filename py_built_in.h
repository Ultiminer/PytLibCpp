#ifndef PY_INPUT_H_
#define PY_INPUT_H_
#include <iostream>
#include <string>
#include "quick_math.h"
#include <vector>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <functional>
#include <fstream>
#include "quicksort.h"
namespace py{



template <class OUT>
inline std::string input(OUT out)
{
    std::cout<< out; 
    std::string buffer; 
    std::getline(std::cin, buffer);
    return buffer; 
}
inline std::string input()
{
    std::string buffer; 
    std::getline(std::cin, buffer);
    return buffer; 
}

constexpr float abs(float x)
{
    return QM::abs(x);
}
template<typename T>
constexpr bool all(const std::vector<T>& iterable)
{
    for(auto& el: iterable)if(!el)return false;
    return true; 
}
template<typename T>
constexpr bool any(const std::vector<T>& iterable)
{
    for(auto& el: iterable)if(!el)return true;
    return false; 
}
struct binary_string
{
    char arr[35];
};
#define NCM_GetBit(x,bitPos) ((((*(unsigned int*)&(x))&(1<<(bitPos))))>>(bitPos))

constexpr binary_string bin(unsigned int x)
{
    binary_string retVal={};
    retVal.arr[34]='\0';
    retVal.arr[0]='0';
    retVal.arr[1]='b';
    for(size_t i=0; i<32;++i)
    retVal.arr[2+i]='0'+NCM_GetBit(x,i);
}
template <typename T>
constexpr bool bool_(T x)
{
    if(((T*)&x)==nullptr)return false; 
    return true; 
}

struct Complex
{
    float real; 
    float imag; 
    std::string label()const
    {
        return std::to_string(real)+" + i"+std::to_string(imag);
    }
    constexpr float squaredist()const
    {
        return real*real+imag*imag;
    }
    constexpr Complex conjugate()const
    {
        return {real,-imag}; 
    }
};
constexpr Complex complex(float Real,float Imag)
{
    return {Real,Imag};
}
constexpr Complex conjugate(float Real,float Imag)
{
    return {Real,-Imag};
}
constexpr Complex conjugate(const Complex& comp)
{
    return {comp.real,-comp.imag};
}
inline Complex complex(std::string comp)
{
        std::string realS; 
        std::string imS; 
        for(size_t i=0; i<comp.size();++i)
        {
            if(comp.at(i)=='+'&&comp.at(i+1)=='i')
            {
                realS=comp.substr(0,i);
                realS=comp.substr(i+1,comp.size()-i-1);
            }
        }
        for(size_t i=0; i<realS.size();++i)
        {
            if(realS.at(i)<44&&realS.at(i)>57){realS.erase(realS.begin()+i);i--;}
        }
        for(size_t i=0; i<realS.size();++i)
        {
            if(imS.at(i)<44&&imS.at(i)>57){imS.erase(realS.begin()+i);i--;}
        }
        return {(float)atof(realS.c_str()),(float)atof(imS.c_str())};
}

constexpr Complex operator+(const Complex& a, const Complex& b)
{
return {a.real+b.real, a.imag+b.imag};
}
constexpr Complex operator+(const Complex& a, float x)
{
return {a.real+x, a.imag};
}
constexpr Complex operator+(float x,const Complex& a)
{
return {a.real+x, a.imag};
}
constexpr Complex operator-(float x,const Complex& a)
{
return {x-a.real, a.imag};
}
constexpr Complex operator-(const Complex& a, float x)
{
return {a.real-x, a.imag};
}
constexpr Complex operator-(const Complex& a, const Complex& b)
{
return {a.real-b.real, a.imag-b.imag};
}
constexpr Complex operator*(const Complex& a, float x)
{
return {a.real*x, a.imag*x};
}
constexpr Complex operator*(float x, const Complex& a)
{
return {a.real*x, a.imag*x};
}
constexpr Complex operator/(const Complex& a, float x)
{
return {a.real/x, a.imag/x};
}
constexpr Complex operator/(float x, const Complex& a)
{
return {a.real*(x/(a.squaredist())), a.imag*(x/a.squaredist())};
}
constexpr Complex operator*(const Complex& a,const Complex& b)
{
return {a.real*b.real-a.imag*b.imag, a.real*b.imag+a.imag*b.real};
}
constexpr Complex operator/(const Complex& a,const Complex& b)
{
 return a*b.conjugate()/b.squaredist();
}

struct QuoRemPair{int quotient; float remainder;};

constexpr QuoRemPair divmod(float a, float b)
{
    const int q{a/b};
    return {q,a/b-q};
}
template<class F, typename T>
inline std::vector<size_t> filter_index(const F& fun,const std::vector<T>& iterable)
{
    std::vector<size_t> retVal;
    for(size_t i=0; i< iterable.size();++i)
    if(bool_(fun(iterable.at(i))))
    retVal.push_back(i);

    return retVal;
}
template<class F, typename T>
inline std::vector<T> filter(const F& fun,const std::vector<T>& iterable)
{
    std::vector<T> retVal;
    for(auto& el:iterable)
    if(bool_(fun(el)))
    retVal.push_back(el);

    return retVal;
}
#define getattr(obj,name) ((obj).(name))

template<class T>
constexpr uint64_t id(T& obj)
{
    return (&obj);
}

inline std::string hex( int i )
{
  std::stringstream stream;
  stream << "0x" 
         << std::setfill ('0') << std::setw(sizeof(int)*2) 
         << std::hex << i;
  return stream.str();
}
template<typename T>
constexpr size_t len(T& obj)
{
    return (sizeof(obj)/(sizeof(*obj)));
}

template<typename T, typename A,size_t S>
constexpr std::array<A,S> map(const std::function<A(T)>& fun, const std::array<T,S>& iterable)
{
    std::array<A,S> retVal;
    for(size_t i=0; i< iterable.size();++i)
    retVal.at(i)=fun(iterable.at(i));


    return retVal; 
}

template<typename T>
constexpr T max(const std::vector<T>& iterable)
{
    if(iterable.size()==0)return 0;
    T maxVal=iterable.front();
    for(auto& el: iterable)if(el>maxVal)maxVal=el;

    return maxVal;
}
template<typename T>
constexpr T max(const std::vector<T>& iterable , const std::function<bool(T,T)>comp)
{
    if(iterable.size()==0)return 0;
    T maxVal=iterable.front();
    for(auto& el: iterable)if(comp(el,maxVal))maxVal=el;

    return maxVal;
}
template<typename T>
constexpr T min(const std::vector<T>& iterable)
{
    if(iterable.size()==0)return 0;
    T minVal=iterable.front();
    for(auto& el: iterable)if(el<minVal)minVal=el;

    return minVal;
}
template<typename T>
constexpr T min(const std::vector<T>& iterable , const std::function<bool(T,T)>comp)
{
    if(iterable.size()==0)return 0;
    T minVal=iterable.front();
    for(auto& el: iterable)if(comp(el,minVal))minVal=el;

    return minVal;
}

template <typename T>
constexpr T max(const T& a, const T& b)
{
    if(a>b)return a; 
    return b;
}
template <typename T>
constexpr T min(const T& a, const T& b)
{
    if(a<b)return a; 
    return b;
}

constexpr int ord(char c)
{
    return c;
}

constexpr float pow(float base, float exp)
{
    return QM::pow(base, exp);
}

struct file_object
{
    std::fstream stream; 
    file_object(const char* path,std::_Iosb<int>::_Openmode mode )
    {
        stream.open(path,mode);
    }
    ~file_object()
    {
    stream.close();
    }
};
inline file_object open(const char* path, std::string mode)
{
    std::_Iosb<int>::_Openmode Omode; 
    for(auto& el: mode)
    {
        switch(el)
        {
            case 'r':
            Omode=(std::_Iosb<int>::_Openmode)(Omode|std::ios::in);
            break;
            case 'w':
            Omode=(std::_Iosb<int>::_Openmode)(Omode|std::ios::out|std::ios::trunc);
            break;
            case 'a':
            Omode=(std::_Iosb<int>::_Openmode)(Omode|std::ios::out|std::ios::app);
            break;
            case 'b':
            Omode=(std::_Iosb<int>::_Openmode)(Omode|std::ios::binary);
            break;
            case '+':
            Omode=(std::_Iosb<int>::_Openmode)(Omode|std::ios::out|std::ios::in);
            break;
        }
    }

    return {path,Omode}; 
}

constexpr float round(float num)
{
    return QM::round(num);

};
constexpr float sum(const std::vector<float>& iterable,size_t start)
{
    float retVal=0;
    for(size_t i=start;i<iterable.size();++i)retVal+=iterable.at(i);

    return retVal;
}
template<size_t S>
constexpr std::array<float ,S> sorted(const std::array<float ,S>& iterable)
{
    return QM_SORT(iterable);
}


}
#endif