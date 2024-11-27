#pragma once
#include <vector>
#include <algorithm>
using namespace std;

template <class T, class Data = ObservableData<T>>
class Observer {
    public:
        virtual void update(Data *data) = 0;
        virtual ~Observer() = default;
};

template <class T>
class Observable {
    protected:
        vector<Observer<T>*> observers;

    public:
        //destructor
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

template <class T>
class ObservableData {
    public:
        virtual T getData() = 0;

};