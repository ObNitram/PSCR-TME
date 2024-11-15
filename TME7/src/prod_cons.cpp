#include "Stack.h"
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;
using namespace pr;

void producteur(Stack<char> *stack)
{
    char c;
    while (cin.get(c))
    {
        stack->push(c);
    }
}

void consomateur(Stack<char> *stack)
{
    while (true)
    {
        char c = stack->pop();
        cout << c << flush;
    }
}

int main()
{
    auto s = new Stack<char>();

    pid_t pp = fork();
    if (pp == 0)
    {
        producteur(s);
        return 0;
    }

    pid_t pc = fork();
    if (pc == 0)
    {
        consomateur(s);
        return 0;
    }

    wait(nullptr);
    wait(nullptr);

    delete s;
    return 0;
}
