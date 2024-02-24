#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N_HIJOS = 5;
    int pids[N_HIJOS];

    for (int i = 0; i < N_HIJOS; i++){
        int pid = fork();
        if (pid == 0){
            // codigo del hijo generado 
            while(1) {
                sleep(1); // el hijo se queda en un loop infinito
            }
        } else {
            // este codigo solo lo ejecuta el padre
            pids[i] = pid;
        }
    }

    // enviar señal SIGKILL a todos los hijos
    for (int i = 0; i < N_HIJOS; i++){
        // acá es el padre quien imprime el PID de los hijos
        // ya que se ocuparían handlers de señales para que el hijo imprima su propio PID al
        // morir.
        printf("Matando al proceso %d \n", pids[i]);
        kill(pids[i], SIGKILL);
    }
}