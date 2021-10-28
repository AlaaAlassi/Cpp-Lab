#include<iostream>
#include<thread>

using namespace std;

void threadFunction (){
    this_thread::sleep_for(chrono::milliseconds(1));
    cout << "finished work in thread" <<endl;
}



int main(){

    // create thread
    thread t(threadFunction);

    this_thread::sleep_for(chrono::milliseconds(50));

                unsigned int nCores = std::thread::hardware_concurrency();
    std::cout << "This machine supports concurrency with " << nCores << " cores available" << std::endl;

    cout << "finished work in main" << endl;

    t.join();

    return 0;
}