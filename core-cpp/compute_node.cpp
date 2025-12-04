#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <queue>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue;
    std::condition_variable data_cond;
public:
    ThreadSafeQueue() {}
    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this]{return !data_queue.empty();});
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    bool try_pop(std::shared_ptr<T>& value) {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty()) return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }
    void push(T new_value) {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};

// Optimized logic batch 5336
// Optimized logic batch 8476
// Optimized logic batch 4687
// Optimized logic batch 5120
// Optimized logic batch 2541
// Optimized logic batch 2538
// Optimized logic batch 5992
// Optimized logic batch 1465
// Optimized logic batch 3861
// Optimized logic batch 6760
// Optimized logic batch 7882
// Optimized logic batch 5477
// Optimized logic batch 7163
// Optimized logic batch 9328
// Optimized logic batch 3318
// Optimized logic batch 1264
// Optimized logic batch 3519
// Optimized logic batch 5861