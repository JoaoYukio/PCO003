#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

class Filosofo{
    private:
        int id;
        long vezesComeu;
        long vezesPensou;
    public:
        std::mutex* m1; // Garfo da direita   
        std::mutex* m2;// Garfo da esquerda
        //Construtor do filosofo
        Filosofo(int id, std::mutex* garfoDir, std::mutex* garfoEsq)
        {
            this->id = id;
            this->m1 = garfoDir;
            this->m2 = garfoEsq;
            vezesComeu = 0;
            vezesPensou = 0;
        }
        void vidaFilosofo()
        {
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
            while(elapsed_seconds.count() <= 300)
            {
                pensa();
                pegarGarfos();
                come();
                soltarGarfos();
                agora = std::chrono::system_clock::now();
                elapsed_seconds = agora - start;
            }
        }
        void pensa()
        {
            cout << "Filosofo " << id << " pensando\n";
            vezesPensou++;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        void come()
        {
            cout << "Filosofo " << id << " comendo\n";
            vezesComeu++;
            //Tempo que leva para comer
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        void pegarGarfos()
        {
            //Tenta pegar o garfo da direita
            this->m1->lock();
            //Tenta pegar o garfo da esquerda
            this->m2->lock();
        }
        void soltarGarfos()
        {
            //Solta os garfos
            this->m1->unlock();
            this->m2->unlock();
        }
        long getNumPensa(){
            return vezesPensou;
        }
        long getNumCome(){
            return vezesComeu;
        }
};

int main()
{

    std::chrono::time_point<std::chrono::system_clock> start, agora;
    std::chrono::duration<double> elapsed_seconds;
    start = std::chrono::system_clock::now();

    std::mutex garfo1;
    std::mutex garfo2;
    std::mutex garfo3;
    std::mutex garfo4;
    std::mutex garfo5;

    Filosofo f1 = Filosofo(1, &garfo5, &garfo1);
    Filosofo f2 = Filosofo(2, &garfo1, &garfo2);
    Filosofo f3 = Filosofo(3, &garfo2, &garfo3);
    Filosofo f4 = Filosofo(4, &garfo3, &garfo4);
    Filosofo f5 = Filosofo(5, &garfo5, &garfo4);
    
    std::thread threadsFilosofos[5] = {
        std::thread(&Filosofo::vidaFilosofo, &f1),
        std::thread(&Filosofo::vidaFilosofo, &f2),
        std::thread(&Filosofo::vidaFilosofo, &f3),
        std::thread(&Filosofo::vidaFilosofo, &f4),
        std::thread(&Filosofo::vidaFilosofo, &f5)
    };

    for(int i = 0; i<5; i++)
    {
        threadsFilosofos[i].join();
    }

    Filosofo filosofos[5] = {f1,f2,f3,f4,f5};

    for(int i = 0; i < 5; i++){
        cout << "Filosofo " << i << " pensou " << filosofos[i].getNumPensa() << " vezes e comeu " << filosofos[i].getNumCome() << " vezes\n";
    }

    agora = std::chrono::system_clock::now();
    elapsed_seconds = agora - start;

    cout << "Tempo total: " << elapsed_seconds.count() << "s\n";

    return 0;
}