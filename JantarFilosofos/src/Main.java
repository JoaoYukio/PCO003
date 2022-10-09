import Filosofo.Filosofo;

public class Main {
    public static void main(String[] args) throws Exception {
        // Criar os filosofos da mesa
        Filosofo filosofos[] = new Filosofo[5];
        // Criar os garfos
        Object garfo[] = new Object[5];
        for(int i = 0; i<5; i++)
        {
            // Criando os objetos um por um
            garfo[i] = new Object();
        }
        // Falar qual garfo e de qual filosofo
        filosofos[0] = new Filosofo(garfo[4], garfo[1]);
        filosofos[1] = new Filosofo(garfo[0], garfo[2]);
        filosofos[2] = new Filosofo(garfo[1], garfo[3]);
        filosofos[3] = new Filosofo(garfo[2], garfo[4]);
        //Aqui eu vou mudar uma coisa, o ultimo filosofo vai pegar primeiro o garfo da direita em vez o da esquerda
        //Assim eu evito o deadlock
        filosofos[4] = new Filosofo(garfo[0], garfo[3]);

        // Criar as threads que representam cada filosofo
        Thread t1 = new Thread(filosofos[0], "Filosofo 1");
        Thread t2 = new Thread(filosofos[1], "Filosofo 2");
        Thread t3 = new Thread(filosofos[2], "Filosofo 3");
        Thread t4 = new Thread(filosofos[3], "Filosofo 4");
        Thread t5 = new Thread(filosofos[4], "Filosofo 5");

        // Iniciar as threads
        t1.start();
        t2.start();
        t3.start();
        t4.start();
        t5.start();
    }
}