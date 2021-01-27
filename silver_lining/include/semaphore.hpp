
// Semaphore
// uncopyable

#ifndef ILRD_HRD14_SEMAPHORE_HPP
#define ILRD_HRD14_SEMAPHORE_HPP

#include <semaphore.h> // sem_t
#include <exception> //exception
#include  <stdexcept> // bad_alloc
#include <chrono>

namespace hrd14
{

class Semaphore
{
public:
    //sem_init
    explicit Semaphore(int pshared = 0, size_t value = 0);
    ~Semaphore();

    void Wait();
    void Post();
    void TryWait();
    void TimedWait(const std::chrono::seconds& timeout);

private:
    Semaphore(const Semaphore&);
    Semaphore& operator=(const Semaphore&);

    sem_t m_sem;
};

}//hrd14

#endif //ILRD_HRD14_SEMAPHORE_HPP