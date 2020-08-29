#pragma once

namespace std{

template<typename T>
class range{
public:
    range(T _start, T _finish) : start(_start), finish(_finish) {
        if (finish < start){
            finish--;
        }
    };
    range(T _finish) : start(0), finish(_finish) {
        if (finish < start){
            start = 1;
        }
    };

    struct Iterator {
        T _p;
        bool forward = true;

        Iterator(T p) : _p(p) {};
        void setReverse() {forward = false;}
        T& operator*() {return _p;}
        bool operator != (const Iterator& rhs) {return _p != rhs._p;}
        void operator ++() {forward ? _p++ : _p--;}
    };

    Iterator begin() const {
        Iterator it(start);
        if(start > finish) {
            it.setReverse();
            it._p--;
        }
        return it;
    }

    Iterator end() const {
        Iterator it(finish);
        return it;
    }

private:
    T start;
    T finish;
};

};