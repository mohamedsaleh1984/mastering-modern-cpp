#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>
using namespace std;
using namespace std::chrono;

// threads, mutexes and locks, and std::async/std::future
void print_message()
{
    std::cout << "Hello from thread!" << std::endl;
    // simualte some work
    std::this_thread::sleep_for(chrono::seconds(5));
    std::cout << "5 seconds has gone..." << std::endl;
}

void print_sum(int a, int b)
{
    std::cout << "Sum: " << a + b << std::endl;
}

void using_threads()
{
    std::thread t(print_message); // create a new thread and execute
    t.join();                     // wait for the thread to finish execution
}

void using_threads_with_parameters()
{
    std::thread t(print_sum, 5, 3); // create a new thread and execute
    t.join();                       // wait for the thread to finish execution
}
/*
    Detach: The thread runs independently from the calling thread. The detach() method
    allows the new thread to continue executing in the background, and the calling thread will
    not wait for it.
*/
void using_detach()
{
    // this is basically will not show anything because the main thread will NOT wait for it.
    std::thread t(print_message);
    t.detach(); // Detach the thread; it runs in the background
}

/*
    if we call detach twice or join twice it will lead to crash/unexpected behavious
    therefore, we need to check joinable?? before calling detach
*/
void using_safe_detach()
{
    std::thread t1(print_message);
    t1.detach();
    if (t1.joinable())
        t1.detach();
}

/*
    A mutex (short for mutual exclusion) is a synchronization primitive that provides
    exclusive access to shared resources. By locking a mutex, one thread ensures that no other
    thread can access the protected resource at the same time.

    It doesn't garantee which thread will get hold of the lock first
    so order is not garanteed
*/

std::mutex mtx;
// Mutex to protect shared data
void print_hello(string s)
{
    // Automatically locks and unlocks the mutex
    std::lock_guard<std::mutex> lock(mtx);
    // The mutex is unlocked when the lock goes out of scope
    std::cout << "Hello from thread " << s << std::endl;
    std::this_thread::sleep_for(chrono::seconds(2));
}

void using_mutex()
{
    std::thread t1(print_hello, "t1");
    std::thread t2(print_hello, "t2");
    t1.join();
    t2.join();
}

/*
    A deadlock occurs when two or more threads are blocked, each waiting for the other to release a resource.
*/
std::mutex mtx1, mtx2;
void avoid_deadlocks(string s)
{

    std::lock(mtx1, mtx2);
    // Locks both mutexes at once
    std::lock_guard<std::mutex> lg1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lg2(mtx2, std::adopt_lock);
    std::cout << "Hello from thread " << s << std::endl;
}
void using_lock_to_avoid_deadlocks()
{
    std::thread t1(avoid_deadlocks, "t1");
    std::thread t2(avoid_deadlocks, "t2");
    t1.join();
    t2.join();
}

/*
    std::async allows you to launch a task asynchronously, meaning the task will run in the
    background, allowing the main thread to continue doing other work. It returns a std::future
    object, which represents a value that will be available at some point in the future.

    Like Promise in JS
 */

int add(int a, int b)
{
    cout << "doing heavy calculations..." << endl;
    std::this_thread::sleep_for(chrono::seconds(5));
    return a + b;
}

// amazing feature.
void using_async_futures()
{
    std::future<int> result = std::async(std::launch::async, add, 5, 3);
    std::cout << "Doing other work..." << std::endl;
    // when you done show the result.
    std::cout << "Result of add: " << result.get() << std::endl;
}
int divide(int a, int b)
{
    if (b == 0)
        throw std::invalid_argument("Division by zero");
    return a / b;
}

void using_async_futures_exception_handling()
{
    std::future<int> result = std::async(std::launch::async, divide, 10, 0);
    try
    {
        std::cout << "Result: " << result.get() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

int main()
{
    // using_threads();
    // using_threads_with_parameters();
    // using_detach();
    // using_safe_detach();
    // using_mutex();
    // using_lock_to_avoid_deadlocks();
    // using_async_futures();
    using_async_futures_exception_handling();
    return 0;
}