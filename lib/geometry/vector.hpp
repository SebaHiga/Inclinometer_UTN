#pragma once

template<typename T>
struct vect_t{
    union{
        struct{
            T xyz[3];
        };
        struct{
            T x, y, z;
        };
    };

    template<typename P>
    void operator= (const P vec){
        int i = 0;
        for(auto &val : xyz){
            val = (T) vec[i];
            i++;
        }
    }

    T operator[] (size_t index) const {
        return xyz[index];
    }

    template<typename P>
    void operator/= (const P num){
        int i = 0;
        for(auto &val : xyz){
            val = (T) (val / num);
            i++;
        }
    }

    template<typename P>
    void operator*= (const P num){
        int i = 0;
        for(auto &val : xyz){
            val = (T) (val * num);
            i++;
        }
    }

    float getModule (){
        return sqrt(x*x + y*y + z*z);
    }

    void print(){
        for(auto val : xyz){
            Serial.print(val);
            Serial.print(" ");
        }
        Serial.println();
    }

};