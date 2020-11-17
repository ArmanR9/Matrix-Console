//#include "Arduino.h"
/*
#include "arrayList.h"
#include <iostream>

template <class T>
class ArrayList{
private:

    T* m_arr = nullptr;
    size_t m_size {0};
    size_t m_capacity {0};

public:

    void realloacte(T newValue){
        T* tempArr {new T[m_capacity]};
        
        for(int i{0}; i < m_size-1; ++i){
            tempArr[i] = m_arr[i];
        }

        tempArr[m_size-1] = newValue;
        delete m_arr;

        m_arr = tempArr;
    }

    void push_back(T newData){
        ++m_size;

        if(m_size >= m_capacity){
            m_capacity *= 2;
            reallocate();
        }
    }

    T operator[](size_z index){
        
    }

    ArrayList(size_t arraySize)
    : m_size(arraySize), m_capacity(arraySize)
    {
        m_arr = new T[arraySize]{0};
    }


};

*/