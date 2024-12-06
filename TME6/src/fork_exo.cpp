#include <iostream>
#include <unistd.h>

int main () {
    const int N = 3;
    std::cout << "main pid=" << getpid() << std::endl;

    for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
        std::cout << " i:j " << i << ":" << j << std::endl;
        for (int k=1; k<=i && j==N ; k++) {
            if ( fork() == 0) {
                j=0;
                std::cout << " k:j " << k << ":" << j << std::endl;
            }
        }
    }
    return 0;
}