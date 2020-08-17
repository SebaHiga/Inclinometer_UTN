#pragma once

#include <Arduino.h>

template<typename T, size_t N>
struct Array{
    T arr[N] = {0};

    Array() = default;
    Array(T *vec){
        for(size_t i = 0; i < N; i++) arr[i] = vec[i];
    }

    T sum(){
        T total = 0;
        for(auto n : arr){
            total += n;
        }
        return total;
    }

    void push_front (T data){
        for(size_t i = N-1; i > 0; i--){
            arr[i] = arr[i-1];
        }
        arr[0] = data;
    }

    size_t size(){return N;}

    void print(){
        for(auto n : arr){
            Serial.print(n);
            Serial.print(" ");
        }
        Serial.println("");
    }

    template<typename J>
    void operator=(J data){
        for(size_t i = 0; i < N and i < data.size(); i++){
            arr[i] = (T) data[i];
        }
    }

    template<typename J>
    Array operator*(J data){
        Array<T, N> tmp;
        for(size_t i = 0; i < N and i < data.size(); i++){
            tmp.arr[i] = (T) ((float)arr[i] * (float)data[i]);
        }

        return tmp;
    }

    T operator[] (size_t i){return arr[i];}

    T* begin(){return &arr[0];}

    T* end(){return &arr[N];}
};

template<typename T, size_t N>
class Filter{
public:
    using array_t = Array<T, N+1>;
    using array_short_t = Array<T, N>;
    
    using farray_t = Array<float, N+1>;
    using farray_short_t = Array<float, N>;

    void setCoefficients(farray_t _b, farray_short_t _a);
    T process(T data);
   
private:
    array_short_t y;
    array_short_t x;

    farray_t b;
    farray_short_t a;
};


template<typename T, size_t N>
void Filter<T, N>::setCoefficients(farray_t _b, farray_short_t _a){
    b = _b;
    a = _a;
}

template<typename T, size_t N>
T Filter<T, N>::process(T data){
    T filtered;
    array_t bx;
    array_short_t ay;

    bx = x;
    bx.push_front(data);
    bx = b * bx;

    bx = b * x;
    ay = a * y;

    filtered = bx.sum() - ay.sum();
    
    x.push_front(data);
    y.push_front(filtered);

    return filtered;
}
