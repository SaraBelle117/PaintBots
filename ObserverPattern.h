#pragma once
#include <vector>
#include <algorithm>
#include "BoardSquare.h"
using namespace std;

//class BoardSquare
class GameBoard;

enum Event {
    SQUARE_COLOR,
    ROBOT_MOVE,
    SQUARE_TYPE
};

template <class T>
class ObservableData {
    private:
        Event type;

    public:
        union Data{

            struct {
                Location position;
                SquareColor color;
            } square_color;

            struct { 
                Location position;
                RobotColor color;
            } robot_move;

            struct{
                Location position;
                SquareType sq;
            } square_type;

        } data;

        //Virtual destructor (to be implemented)
        virtual ~ObservableData() = default;

        //constructor
        ObservableData(Event t, const Data& d) : type(t), data(d) {}

        //copy constructor
        ObservableData(const ObservableData& rhs) : type(rhs.type), data(rhs.data){}


        /**
         * Gets the given data
         * @return Data reference 
         */
        const Data& getData() const 
        { 
            return data; 
        }

        /**
         * Returns the given event type
         * @return Event type 
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