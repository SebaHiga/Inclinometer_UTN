#pragma once

#include <math.h>

template<typename T>
struct vect_t{
    enum Module {
        xy = 0,
        xz,
        yz
    };

    union{
        struct{
            T xyz[3];
        };
        struct{
            T x, y, z;
        };
    };

    float theta, phi;
    T r;

    inline void calcPolar(){
        r = getModule();
        theta = acos(z / r);
        phi = acos(x / (r * sin(theta)));
    }

    template<typename P>
    void operator= (const P vec){
        int i = 0;
        for(auto &val : xyz){
            val = (T) vec[i];
            i++;
        }
        calcPolar();
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
        calcPolar();
    }

    template<typename P>
    void operator*= (const P num){
        int i = 0;
        for(auto &val : xyz){
            val = (T) (val * num);
            i++;
        }
        calcPolar();
    }

    float getModule (){
        return sqrt(x*x + y*y + z*z);
    }

    float getModule(Module m){
        switch (m){
        case Module::xy:
            return sqrt(x*x + y*y);
        case Module::xz:
            return sqrt(x*x + z*z);
        case Module::yz:
            return sqrt(y*y + z*z);
        }
        return 0;
    }

    void print(){
        for(auto val : xyz){
            Serial.print(val);
            Serial.print(" ");
        }
        Serial.println();
    }

};