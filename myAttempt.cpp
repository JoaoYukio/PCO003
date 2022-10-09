#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

class Filosofo{
    public:
        int id;
        std::mutex* m1;
        std::mutex* m2;
        Filosofo(int id, std::mutex *m1, std::mutex *m2){
            this->id = id;
            this->m1 = m1;
            this->m2 = m2;
        }
        void comer(){
            while(true){
                pensar();
                m1->lock();
                m2->lock();
                cout << "Filosofo " << id << " comendo" << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
                m1->unlock();
                m2->unlock();
            }
        }
        void pensar(){
            cout << "Filosofo " << id << " pensando" << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    
    
};

int main()
{
    mutex garfos[5];

    Filosofo f1(0, &garfos[4], &garfos[1]);
    Filosofo f2(1, &garfos[0], &garfos[2]);
    Filosofo f3(2, &garfos[1], &garfos[3]);
    Filosofo f4(3, &garfos[2], &garfos[4]);
    Filosofo f5(4, &garfos[0], &garfos[3]);

    
    Filosofo filosofos[5] = {
        f1,f2,f3,f4,f5
    };

    std::thread threadsFilosofos[5] = {
        std::thread(&Filosofo::comer, &filosofos[0]),
        std::thread(&Filosofo::comer, &filosofos[1]),
        std::thread(&Filosofo::comer, &filosofos[2]),
        std::thread(&Filosofo::comer, &filosofos[3]),
        std::thread(&Filosofo::comer, &filosofos[4])
    };

    /*threads[0] = thread(&Filosofo::comer, &filosofos[0]);
    threads[1] = thread(&Filosofo::comer, &filosofos[1]);
    threads[2] = thread(&Filosofo::comer, &filosofos[2]);
    threads[3] = thread(&Filosofo::comer, &filosofos[3]);
    threads[4] = thread(&Filosofo::comer, &filosofos[4]);
    */
    
    for(int i = 0; i < 5; i++){
        threadsFilosofos[i].join();
    }

    return 0;
}