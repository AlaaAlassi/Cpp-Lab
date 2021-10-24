#include<iostream>
#include<thread>

using namespace std;

void threadFunction (){
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "finished work in thread" <<endl;
}



int main(){

    // create thread
    thread t(threadFunction);

    this_thread::sleep_for(chrono::milliseconds(50));

    cout << "finished work in main" << endl;

    t.join();

    return 0;
}