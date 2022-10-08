#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

class Garfo{
    public:
    mutex mutexGarfo;
};

class Filosofo{
    int num;
    public:
    Filosofo(int num)
    {
        this->num = num;
    }
    void estiloDeVida(Garfo& gl, Garfo& gr)
    {
        while(1)
        {
            //Pensar
            int tempoPensando = rand()%(1001); // Leva ate 1 segundo pensando
            cout << "Filosofo " << num << " pensando.\n";
            this_thread::sleep_for(chrono::milliseconds(tempoPensando));
            // Comer
            comer(gl, gr);
        }
    }
};

void comer(Garfo& gl, Garfo& gr, int numFil)
{
    int tempoComendo = rand()%(1001);
    std::unique_lock<std::mutex> lockEsq(gl.mutexGarfo);
    std::unique_lock<std::mutex> lockDir(gr.mutexGarfo);
    cout << "Filosofo " << num << " esta comendo.\n";
    this_thread::sleep_for(chrono::milliseconds(tempoComendo));
    cout << "Filosofo " << num << " comeu.\n";
    lockEsq.release();
    lockDir.release();
}

int main()
{
    Garfo garfo1 = Garfo();
    Garfo garfo2 = Garfo();
    Garfo garfo3 = Garfo();
    Garfo garfo4 = Garfo();
    Garfo garfo5 = Garfo();

    Filosofo fil1 = Filosofo(1);
    Filosofo fil2 = Filosofo(2);
    Filosofo fil3 = Filosofo(3);
    Filosofo fil4 = Filosofo(4);
    Filosofo fil5 = Filosofo(5);

    thread T1(fil1.estiloDeVida(garfo5, garfo2));
    thread T2(fil2.estiloDeVida(garfo1, garfo3));
    thread T3(fil3.estiloDeVida(garfo2, garfo4));
    thread T4(fil4.estiloDeVida(garfo3, garfo5));
    thread T5(fil5.estiloDeVida(garfo4, garfo1));

    T1.join();
    T2.join();
    T3.join();
    T4.join();
    T5.join();

    return 0;

}