#include "Stack.h"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

void producteur(pr::Stack<char> *stack)
{
    char c;
    while (std::cin.get(c))
    {
        stack->push(c);
    }
}

void consomateur(pr::Stack<char> *stack)
{
    for (;;)
    {
        const char c = stack->pop();
        std::cout << c << std::flush;
    }
}

void print_help(const char *const argv[]) { std::cerr << "Usage: " << argv[0] << " producer|consumer" << std::endl; }

int main(const int argc, char *argv[])
{
    if (argc != 2)
    {
        print_help(argv);
        return 1;
    }

    if (std::strcmp(argv[1], "producer") != 0 && std::strcmp(argv[1], "consumer") != 0)
    {
        print_help(argv);
        return 1;
    }

    const bool is_producer = (std::strcmp(argv[1], "producer") == 0);

    constexpr size_t size_of_stack = sizeof(pr::Stack<char>);
    const auto shm_name = "/stack_shm";

    const int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        return 1;
    }

    if (ftruncate(shm_fd, size_of_stack) == -1)
    {
        perror("ftruncate");
        return 1;
    }

    void *ptr = mmap(nullptr, size_of_stack, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }

    pr::Stack<char> *stack = nullptr;

    if (is_producer)
    {
        // Init the stack
        stack = new (ptr) pr::Stack<char>;
    }
    else // is consumer
    {
        // Get the stack
        stack = static_cast<pr::Stack<char> *>(ptr);
    }

    if (is_producer)
    {
        producteur(stack);
    }
    else
    {
        consomateur(stack);
    }

    // Only the producer clean
    if (is_producer)
    {
        stack->~Stack();
        munmap(ptr, size_of_stack);
        shm_unlink(shm_name);
    }
    else
    {
        munmap(ptr, size_of_stack);
    }

    return 0;
}
