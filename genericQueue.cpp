#include<deque>
#include<thread>
#include <mutex>
#include <condition_variable>
#include <iostream>


template <class T>
class MessageQueue
{
public:
    void send(T && msg);
    T receive();

private:
std::mutex _mux;
std::condition_variable _cond;
std::deque<T> _message;

};

void planningFunciton(std::shared_ptr<MessageQueue<int>> avialableRobots,std::shared_ptr<MessageQueue<int>> busyRobots){
        while (true)
    {
    int message = avialableRobots->receive();
     std::cout << "[Planning] recived "<< message << std::endl;
    busyRobots->send(std::move(message));
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait()
    // to wait for and receive new messages and pull them from the queue using move semantics.
    // The received object should then be returned by the receive function.
    std::unique_lock<std::mutex> uLock(_mux);
    _cond.wait(uLock, [this]
               { return !_message.empty(); });
    T msg = std::move(_message.front());
    _message.pop_front();
    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex>
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> lGuard(_mux);
    _message.push_back(std::move(msg));
    _cond.notify_one();
}

int main(){
    std::shared_ptr<MessageQueue<int>> avialableRobots = std::make_shared<MessageQueue<int>>();
    std::shared_ptr<MessageQueue<int>> busyRobots = std::make_shared<MessageQueue<int>>();
    int message =0;
    for(int i=0;i<10;i++){
        avialableRobots->send(std::move(i));
    }
    std::thread simulationThread(&planningFunciton, avialableRobots,busyRobots);


    while(true){

    int message = busyRobots->receive();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "[Execution] Sent "<< message << std::endl;
    avialableRobots->send(std::move(message));
    }

    simulationThread.join();


}
