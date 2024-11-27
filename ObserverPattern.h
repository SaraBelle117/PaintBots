#pragma once
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class Observer {
    public:
        virtual void update(T *data) = 0;
        virtual ~Observer() = default;
};

template <typename T>
class Observable {
    protected:
        vector<Observer<T>*> observers;

    public:
        virtual ~Observable() = default;
        
        void registerObserver(Observer<T> *o)
        {
            observers.push_back(o);
        }

        void removeObserver(Observer<T> *o)
        {
            observers.erase(remove(observers.begin(), observers.end(), o), observers.end());
        }

        virtual void notifyObservers(ObservableData<T>*) = 0;

};