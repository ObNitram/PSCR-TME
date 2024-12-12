#include "Banque.h"

#include <functional>
#include <iostream>
#include <random>
#include <thread>

constexpr int NB_THREAD = 10;

void transactional_thread(pr::Banque &banque)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, banque.size() - 1);
    std::uniform_int_distribution<unsigned int> dist_val(1, 100);
    std::uniform_int_distribution<int64_t> dist_wait(1, 4);

    for (size_t i = 0; i < 1000; ++i)
    {
        const size_t deb = dist(gen);
        const size_t cred = dist(gen);
        const unsigned int val = dist_val(gen);
        banque.transfert(deb, cred, val);
        // std::this_thread::sleep_for(std::chrono::milliseconds(dist_wait(gen)));
    }
}

int main()
{
    std::vector<std::thread> threads;

    pr::Banque banque(10, 1000);

    std::atomic_bool running = true;
    auto comptable_thread = std::thread(
        [&banque, &running]()
        {
            while (running)
            {
                banque.comptabiliser(10000);
            }
        });

    for (int i = 0; i < NB_THREAD; ++i)
    {
        threads.emplace_back(transactional_thread, std::ref(banque));
    }

    for (auto &t : threads)
    {
        t.join();
    }

    running = false;

    comptable_thread.join();

    std::cout << "Fin des threads" << std::endl;
    banque.comptabiliser(10000);
    return 0;
}
