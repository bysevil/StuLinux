#include "ThreadPool.h"
#include<cstdlib>

int main() {
    srand((unsigned int)time(NULL));

    ThreadPool<> tp;
    tp.Run();

    for (int i = 0; i < 1000; i++) {

        Task* tk = new Task(i,rand() % 10 + 1, rand() % 10 + 1);
        tp.push(tk);
    }
    return 0;
}