#pragma once
#include <mutex>
#include <thread>
#include <queue>
#include <ctime>
#include <condition_variable>

#include "Task.h"

template <size_t threadnum = 5, class T = Task, bool isdel = true>
class ThreadPool
{
public:
    // 线程池开始运行
    void Run()
    {
        std::thread* t;
        for (int i = 0; i < threadnum; i++)
        {
            //t = new std::thread(Start,this);
            t = new std::thread(Start, &_qe,&_mtx,&_cv);
            if (t == nullptr) {
                exit(-1);
            }
            _v.push_back(t);
            t = nullptr;
        }
       
    }

    // 将任务添加到任务队列
    void push(T*& tk)
    {
        //条件变量版本
        
        std::unique_lock<std::mutex> lck(_mtx);
        _qe.push(tk);
        //std::cout << "任务加入任务队列" << std::endl;
        _cv.notify_one();

        // //互斥锁版本
        // _mtx.lock();
        // _qe.push(tk);
        // _mtx.unlock();
    }

    ~ThreadPool()
    {
        std::cout << "线程销毁" << std::endl;
        if (!_qe.empty())
        {
            for (auto& e : _v) {
                e->join();
                delete e;
                e = nullptr;
            }
        }
    }

private:
    // 线程开始从任务队列拿取任务并执行
    //static void Start(ThreadPool<threadnum>* tp)
    static void Start(std::queue<T*>* qe, std::mutex* mtx, std::condition_variable* cv)
    {
        std::unique_lock<std::mutex> lck(*mtx, std::defer_lock);

        Task* tk = nullptr;
        while (true)
        {
            //条件变量版本
            lck.lock();
            cv->wait(lck, [&qe] {return !qe->empty(); });
            tk = qe->front();
            qe->pop();
            lck.unlock();
            //std::cout << std::this_thread::get_id() << "获取到任务" << std::endl;
            tk->Start();
            if(isdel == true){
                delete tk;
            }
            tk = nullptr;

            ////互斥锁版本
            //if (!qe->empty()) {
            //    mtx->lock();
            //    if (!qe->empty()) {
            //        tk = qe->front();
            //        qe->pop();
            //        mtx->unlock();
            //        tk->Start();
            //        delete tk;
            //        tk = nullptr;
            //    }
            //    else {
            //        mtx->unlock();
            //    }
            //}
            
        }
    }

    std::mutex _mtx;
    std::queue<T*> _qe;
    std::vector<std::thread*> _v;
    std::condition_variable _cv;
};
