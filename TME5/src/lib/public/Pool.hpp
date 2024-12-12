#pragma once

#include "Job.hpp"
#include "Queue.hpp"

#include <cassert>
#include <thread>
#include <vector>

namespace pr
{

class Pool
{
    Queue<Job> queue;
    std::vector<std::thread> threads;

  public:
    explicit Pool(const int qsize) : queue(qsize) {}
    ~Pool() = default;

    Pool(const Pool &other) = delete;
    Pool &operator=(const Pool &other) = delete;

    Pool(Pool &&other) = delete;
    Pool &operator=(Pool &&other) = delete;

    void start(int nbthread)
    {
        threads.reserve(nbthread);
        for (int i = 0; i < nbthread; ++i)
        {
            threads.emplace_back(lunch_thread, std::ref(queue));
        }
    }

    void submit(Job *job)
    {
        assert(job != nullptr);
        queue.push(job);
    }

    void stop()
    {
        queue.setBehavior(false);

        for (auto &thread : threads)
        {
            thread.join();
        }
    }

  private:
    static void lunch_thread(Queue<Job> &jobs)
    {
        while (true)
        {
            const auto job = jobs.pop();
            if (job == nullptr) return;
            job->run();
        }
    }
};

} // namespace pr
