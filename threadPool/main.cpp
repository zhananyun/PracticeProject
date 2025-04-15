#include "thread_pool.h"

int main(){
    ThreadPool pool;
    pool.init(4);
    pool.start();
    return 0;
}