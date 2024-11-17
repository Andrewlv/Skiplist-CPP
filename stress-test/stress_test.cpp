#include <iostream>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "../skiplist.h"

#define NUM_THREADS 1
#define TEST_COUNT 100000

// 初始化跳表，最大层数设置为18
SkipList<int, std::string> skipList(18);

// 插入元素的函数
void insertElement(int thread_id) {
    std::cout << "Insert Thread ID: " << thread_id << std::endl;

    int taskPerThread = TEST_COUNT / NUM_THREADS;
    for (int i = 0; i < taskPerThread; i++) {
        skipList.insert_element(rand() % TEST_COUNT, "a");
    }
}

// 查找元素的函数
void getElement(int thread_id) {
    std::cout << "Search Thread ID: " << thread_id << std::endl;

    int taskPerThread = TEST_COUNT / NUM_THREADS;
    for (int i = 0; i < taskPerThread; i++) {
        skipList.search_element(rand() % TEST_COUNT);
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // 插入操作计时
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;

    // 创建插入线程
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.emplace_back(insertElement, i);
    }

    // 等待所有插入线程完成
    for (auto& thread: threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    threads.clear();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Insert elapsed time: " << elapsed.count() << " seconds" << std::endl;

    // 查找操作计时
    start = std::chrono::high_resolution_clock::now();
    // 创建查找线程
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.emplace_back(getElement, i);
    }

    // 等待所有查找线程完成
    for (auto& thread: threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Search elapsed time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
