#pragma once

namespace std{
template<typename T>
class range{
public:
    range(int _start, int _finish) : start(_start), finish(_finish) {};
    range(int _finish) : start(0), finish(_finish) {};

    struct Iterator {
        T _p;
        bool forward = true;

        Iterator(T p) : _p(p) {};
        void setReverse() {forward = false;}
        T& operator*() { return _p; }
        bool operator != (const Iterator& rhs) {
            return _p != rhs._p;
        }
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
        start > finish ? finish-- : finish;
        Iterator it(finish);
        return it;
    }

private:
    mutable int start;
    mutable int finish;
};

};