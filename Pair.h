#pragma once
#include <iostream>
using namespace std;

template <class T>
class Pair {
    private:
        //pointers to the first & second objects
        T* first;
        T* second;

    public:
        
        /**
         * Constructor for the Pair class
         * @param obj1 -- first
         * @param obj2 -- second
         */
        Pair(T* obj1, T* obj2) : first(obj1), second(obj2) {}

        /**
         * Accessor method for the first object
         * @return pointer to the first
         */
        T* getFirst() const
        {
            return first;
        }

        /**
         * Accessor method for the second object
         * @return pointer to the second
         */
        T* getSecond() const
        {
            return second;
        }

        /**
         * Overloaded operator[]
         * @param index
         * @return object --- if index 1, return first, return second if index 2
         * if neither, return null
         */
        T* operator[](int index) const
        {  
            if(index == 1){
                return first;
            }
            else if(index == 2){
                return second;
            }
            //return null for any other index
            return nullptr;
        }

};