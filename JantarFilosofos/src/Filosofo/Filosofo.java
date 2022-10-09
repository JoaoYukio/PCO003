package Filosofo;

public class Filosofo implements Runnable {
    private Object garfoEsquerda;
    private Object garfoDireita;

    public Filosofo(Object GarfoEsq, Object GarfoDir){
        this.garfoEsquerda = GarfoEsq;
        this.garfoDireita = GarfoDir;
    }

    public void FazerAcao(String acao) throws InterruptedException
    {
        //Aqui podemos comer ou pensar ou pegar um garfo
        System.out.println(
                Thread.currentThread().getName() + " " + acao
        );
        Thread.sleep(((int)(Math.random()*4000)));
    }

    @Override
    public void run() {
        try{
            while(true)
            {
                /*
                    Vida do filosofo:
                        Pensar,
                        // Depois de um tempo, quando ficar com fome
                        Comer -> pegar um garfo, e depois pegar outro
                        // Depois de satisfeito
                        Devolver os garfos e voltar a pensar
                 */
                FazerAcao("Pensando");
                // Usando MONITOR
                synchronized (garfoEsquerda){
                    FazerAcao("Peguei o garfo da esquerda");
                }
                //Caso tenha conseguido pegar
                synchronized (garfoDireita){
                    FazerAcao("Peguei o garfo da direita e agora vou comer");
                    FazerAcao("Devolvendo o garfo da direita");
                    //Quando sair desse bloco o monitor libera o garfo da direita
                }
                FazerAcao("Devolvendo o garfo da esquerda");
            }
        }catch (InterruptedException e){
            Thread.currentThread().interrupt();
            return;
        }
    }
}
