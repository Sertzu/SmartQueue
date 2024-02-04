#include <gtest/gtest.h>
#include <thread>
#include <vector>

#include "SmartQueue.h" // Make sure to include your SmartQueue class definition

// Test 1: Enqueue and Dequeue Operations
TEST(SmartQueueTest, EnqueueDequeue) {
    SmartQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);

    auto first = queue.dequeue();
    auto second = queue.dequeue();

    EXPECT_EQ(first, 1);
    EXPECT_EQ(second, 2);
}

// Test 2: TryDequeue on Empty Queue
TEST(SmartQueueTest, TryDequeueEmpty) {
    SmartQueue<int> queue;
    auto result = queue.tryDequeue();

    EXPECT_EQ(result, std::nullopt);
}

// Test 3: Thread Safety
TEST(SmartQueueTest, ThreadSafety) {
    SmartQueue<int> queue;
    const int numThreads = 10;
    const int numIterations = 1000;

    // Start producer threads
    std::vector<std::thread> producers;
    for (int i = 0; i < numThreads; ++i) {
        producers.emplace_back([&]() {
            for (int j = 0; j < numIterations; ++j) {
                queue.enqueue(j);
            }
        });
    }

    // Start consumer threads
    std::vector<std::thread> consumers;
    for (int i = 0; i < numThreads; ++i) {
        consumers.emplace_back([&]() {
            for (int j = 0; j < numIterations; ++j) {
                auto value = queue.dequeue(); // Not using the value here
            }
        });
    }

    // Join all threads
    for (auto& t : producers) t.join();
    for (auto& t : consumers) t.join();

    // At the end, the queue should be empty
    EXPECT_TRUE(queue.isEmpty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
