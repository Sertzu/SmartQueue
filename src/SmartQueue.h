#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template<typename T>
class SmartQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable notEmpty;

public:
    SmartQueue() = default;
    ~SmartQueue() = default;

    SmartQueue(const SmartQueue&) = delete;
    SmartQueue& operator=(const SmartQueue&) = delete;

    // Add an item to the queue and notify one waiting thread
    void enqueue(T item) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            queue.push(std::move(item));
        }
        notEmpty.notify_one();
    }

    // Try to dequeue an item from the queue. Returns nullopt if the queue is empty
    std::optional<T> tryDequeue() {
        std::lock_guard<std::mutex> lock(mutex);
        if (queue.empty()) {
            return std::nullopt;
        }
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    // Dequeue an item from the queue. Blocks if the queue is empty until an item is enqueued
    T dequeue() {
        std::unique_lock<std::mutex> lock(mutex);
        notEmpty.wait(lock, [this]{ return !queue.empty(); });
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    // Check if the queue is empty. Note: This status could change immediately after this check.
    bool isEmpty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

    // Get the current size of the queue. Note: This status could change immediately after this check.
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.size();
    }
};
