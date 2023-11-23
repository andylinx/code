#include<cstdio>
#include<iostream>
#include<algorithm>
template <typename T>
class SharedPtr
{

private:
    T *_p;
    int *cnt;
    void del(){
        --(*cnt);
        if((*cnt)<=0)
        {
            // std::cout<<_p<<std::endl;
            if(_p) delete _p;
            delete cnt;
            _p=nullptr;
            cnt=nullptr;
            // std::cout<<"Del!"<<std::endl;
        }
    }
public:
    SharedPtr():_p(nullptr),cnt(new int(0)){}
    SharedPtr(T *_ptr):_p(_ptr),cnt(new int(1)){}
    ~SharedPtr(){
        // std::cerr<<(cnt)<<std::endl;
        del();
    }
    SharedPtr (const SharedPtr & oth){
        cnt=oth.cnt;
        _p=oth._p;
        (*cnt)++;
    }
    SharedPtr& operator = (const SharedPtr & oth){
        if(_p==oth._p) return *this;
        if((*cnt)>0) del();
        else delete cnt;
        _p=oth._p;
        cnt=oth.cnt;
        ++(*cnt);
        return *this;
    }
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
    void reset(){
        if(!(*cnt)) return;
        del();
        _p=nullptr; cnt=new int(0);
    }
    void reset(T *_ptr) {
        if(!(*cnt))
        {
            _p=_ptr;
            (*cnt)=1;
            return;
        }
        del();
        _p = _ptr; cnt=new int(1);
    }
    int use_count(){
        return *cnt;
    }
};
template <typename T,typename ...A>
T* make_shared(A && ... a){
    return (new T(std::forward<A>(a)...));
}
int main()
{ 
    SharedPtr <int> tmp;
    tmp.reset(new int(40));
    tmp.reset();
    SharedPtr <int> temp=make_shared <int>(200);
    temp.reset(new int(10));
    return 0;
}