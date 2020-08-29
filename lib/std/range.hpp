#pragma once

namespace std{

class range{
public:
    range(int _bot, int _top) : bot(_bot), top(_top) {};
    range(int _top) : bot(0), top(_top) {};

    template<typename T>
    struct Iterator {
        T p;
        T& operator*() { return p; }
        bool operator != (const Iterator& rhs) {
            return p != rhs.p;
        }
        void operator ++() { ++p; }
    };

    Iterator<int> begin() const {
        return Iterator<int>{bot};
    }
    Iterator<int> end() const {
        return Iterator<int>{top};
    }

private:
    int bot;
    int top;
};

};