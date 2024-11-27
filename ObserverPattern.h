#pragma once
#include <vector>
#include <algorithm>
using namespace std;

enum Event {
    SQUARE_COLOR,
    ROBOT_MOVE,
    SCORE_UPDATE
};

template <class T>
class ObservableData {
    private:
        Event type;

    public:
        union Data{

            struct {
                int x;
                int y;
                SquareColor color;
            } SquareColorData;

            struct { 
                RobotMoveRequest mr;
            } robotMoveData;

            struct {
                int score;
            } scoreUpdateData;

        } data;

        //Virtual destructor (to be implemented)
        virtual ~ObservableData() = default;
        explicit ObservableData(Event t, const Data& d) : type(t), data(d) {}

        const Data& getData() const 
        { 
            return data; 
        }

        /**
         * Returns the given event type
         */
        Event getEvent() const 
        {
            return type;
        }

};

template <class T>
class Observer {
    public:
        //for updating the data (to be implemented)
        virtual void update(ObservableData<T> *data) = 0;
        //destructor (to be implemented)
        virtual ~Observer() = default;
};

template <class T>
class Observable {
    protected:
        vector<Observer<T>*> observers;

    public:
        //destructor (to be implemented)
        virtual ~Observable() = default;

        //for registering observers
        void registerObserver(Observer<T> *o)
        {
            observers.push_back(o);
        }
        
        //for removing observers
        void removeObserver(Observer<T> *o)
        {
            observers.erase(remove(observers.begin(), observers.end(), o), observers.end());
        }

        //for notifying observers (to be implemented)
        virtual void notifyObservers(ObservableData<T>*) = 0;

};