# 一个简单的线程池

通过条件变量控制的线程池

线程池模板类名称ThreadPool

有两个模板参数size_t threadnum 和 class T
第一个表示线程池创建的线程数，默认为5
第二个表示线程池使用的任务类，默认为Task
第三个参数表示线程池是否在执行完任务后delete掉Tssk

Task类要以指针方式push入线程池任务队列，并在内部实现无参空返回值的Start函数作为实际的任务，所需变量应在构造时初始化为成员变量



