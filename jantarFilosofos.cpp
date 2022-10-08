#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int main()
{
    struct Garfo{
    public:
        Garfo(){;};
        std::mutex mu;
    };

    const int qtd_fil = 5;

    auto eat = [](Garfo& garfo_esq, Garfo& garfo_dir, int num_filosofo)
    {
    std::unique_lock<std::mutex> lockEsq(garfo_esq.mu);
    std::unique_lock<std::mutex> lockDir(garfo_dir.mu);

    cout << "Filosofo " << num_filosofo << " esta comendo.\n";

    std::chrono::milliseconds timeout(1000); //definicao do tempo que demora pra comer
    std::this_thread::sleep_for(timeout);

    cout << "Filosofo " << num_filosofo << " comeu.\n";
    };

    Garfo garfo[qtd_fil];

    std::thread filosofos[qtd_fil]; //array com os filosofos como threads

    //Começam pensando
    cout << "Filosofo" << (0+1) << " esta pensando.\n";
    filosofos[0] = std::thread(eat, std::ref(garfo[0]), std::ref(garfo[qtd_fil-1]), (0+1));

    for(int i = 1; i<qtd_fil; ++i)
    {
        cout << "Filosofo" << (i+1) << " esta pensando.\n";
        filosofos[i] = std::thread(eat, std::ref(garfo[i]), std::ref(garfo[i-1]), (i+1));
    }

    for(auto &fil: filosofos) {
        fil.join();
    }

    return 0;

}