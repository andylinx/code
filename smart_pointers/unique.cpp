#include<algorithm>
#include<cstdio>
#include<iostream>
#include<string>
template <typename T>
class UniquePtr
{
public:
    UniquePtr():_p(nullptr){}
    explicit UniquePtr(T *_ptr):_p(_ptr){}
    UniquePtr(UniquePtr<T> && oth){
        _p = oth._p;
        oth._p = nullptr;
    };
    ~UniquePtr(){
        delete _p;
    }
    UniquePtr(const UniquePtr & oth) = delete;
    UniquePtr & operator = (UniquePtr & oth) = delete;
    UniquePtr & operator = (UniquePtr<T> && oth){
        std::swap(_p,oth._p);
        return *this;
    };
    T& operator * (){
        return *_p;
    }
    T* operator -> (){
        return _p;
    }
    T* get() const{
        return _p;
    }
    operator bool() const{
        return _p != nullptr;
    }
    T* release(){
        T *tmp = _p;
        _p = nullptr;
        return tmp;
    }
    void reset(){
        delete _p;
        _p=nullptr;
    }
    void swap(UniquePtr &_ptr) {
        std::swap(_p, _ptr._p);
    }
    void reset(T *_ptr) {
        UniquePtr<T>().swap(*this);
        _p = _ptr;
    }

private:
    T *_p;
};

template <typename T,typename ...A>
UniquePtr <T> make_unique(A && ... a){
    return UniquePtr<T>(new T(std::forward<A>(a)...));
}
int main()
{   
    UniquePtr<std::string> ptr2 = make_unique<std::string>("hello world!");
    std::cout<<*ptr2;
    return 0;
}