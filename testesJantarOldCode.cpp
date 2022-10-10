#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

class Filosofo{
    private:
        int id;
        long numPensa = 0;
        long numCome = 0;
    public:
        std::mutex* m1;
        std::mutex* m2;
        Filosofo(int id, std::mutex* m1, std::mutex* m2){
            this->id = id;
            this->m1 = m1;
            this->m2 = m2;
        }
        void comer(){
            /*
                    Vida do filosofo:
                        Pensar,
                        // Depois de um tempo, quando ficar com fome
                        Comer -> pegar um garfo, e depois pegar outro
                        // Depois de satisfeito
                        Devolver os garfos e voltar a pensar
            */
            //Variaveis para controlar o tempo de simulacao 
            std::chrono::time_point<std::chrono::system_clock> start, agora;
            std::chrono::duration<double> elapsed_seconds;
            start = std::chrono::system_clock::now();
            //no loop while controlamos por quanto tempo vamos simumlar
            while(elapsed_seconds.count() <= 300){
                //Pensar
                pensar();
                //Tentar pegar os garfos
                //Primeiro o m1, ou seja, o da esquerda, depois o da direita
                m1->lock();
                m2->lock();
                cout << "Filosofo " << id << " comendo\n";
                numCome++;
                //Tempo que leva para comer
                this_thread::sleep_for(chrono::milliseconds(rand()%2000));
                //Solta os garfos
                m1->unlock();
                m2->unlock();
                
                agora = std::chrono::system_clock::now();
                elapsed_seconds = agora - start;
                //Volta a pensar

            }
        }
        void pensar(){
            cout << "Filosofo " << id << " pensando\n";
            numPensa++;
            this_thread::sleep_for(chrono::milliseconds(rand()%2000));
        }
        long getNumPensa(){
            return numPensa;
        }
        long getNumCome(){
            return numCome;
        }
};

int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, agora;
    std::chrono::duration<double> elapsed_seconds;
    start = std::chrono::system_clock::now();

    // Cria um array contendo os mutex que representam os garfos
    mutex garfos[5];

    // Cria um id pros filosofos e fala qual garfo esta a sua esquerda e qual esta a sua direita
    Filosofo f1(0, &garfos[4], &garfos[1]);
    Filosofo f2(1, &garfos[0], &garfos[2]);
    Filosofo f3(2, &garfos[1], &garfos[3]);
    Filosofo f4(3, &garfos[2], &garfos[4]);
    Filosofo f5(4, &garfos[0], &garfos[3]);

    //Cria um array contendo os filosofos criados anteriormente
    Filosofo filosofos[5] = {
        f1,f2,f3,f4,f5
    };

    // Cria um array com a thread de cada Filosofo, ou seja, contendo a vida do Filosofo
    std::thread threadsFilosofos[5] = {
        std::thread(&Filosofo::comer, &filosofos[0]),
        std::thread(&Filosofo::comer, &filosofos[1]),
        std::thread(&Filosofo::comer, &filosofos[2]),
        std::thread(&Filosofo::comer, &filosofos[3]),
        std::thread(&Filosofo::comer, &filosofos[4])
    };
    
    // Faz com que as threads esperem as outras liberarem os garfos caso nao consiga pegar
    for(int i = 0; i < 5; i++){
        threadsFilosofos[i].join();
    }

    // Mostra quantas vezes cada filosofo pensou e comeu
    for(int i = 0; i < 5; i++){
        cout << "Filosofo " << i << " pensou " << filosofos[i].getNumPensa() << " vezes e comeu " << filosofos[i].getNumCome() << " vezes\n";
    }

    agora = std::chrono::system_clock::now();
    elapsed_seconds = agora - start;

    cout << "Tempo total: " << elapsed_seconds.count() << "s\n";

    return 0;
}
