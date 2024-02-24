#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
    int i;
    int N_HIJOS= 5;
    int N_GENERACIONES = 3;
    int gen = 1; 

    for (int j = 0; j < N_GENERACIONES; j++) {
        for (i = 0; i < N_HIJOS; i++) {
            int pid = fork();
            if (pid != 0) {
                wait(NULL); // esperar a que el hijo termine
            } else {
                gen++;
                break; // soy el hijo, ocupo continuar con el ciclo exterior 
            }
        }
        if (i == N_HIJOS) {
            break; // soy el padre, ocupo salir del ciclo exterior
            // esto funciona ya que el padre nunca hace break, y el hijo siempre lo hace
        }
    }    

    printf("Gen: %d \t Padre: %ld \t Yo: %ld \n", gen, (long)getppid(), (long)getpid());
    // Se comprobó el funcionamiento con grep, ex.
    // ./Tarea1_1-2022175018 | grep -c "Gen: 4" -> 125
    // ./Tarea1_1-2022175018 | grep -c "Gen: 3" -> 25
    // ./Tarea1_1-2022175018 | grep -c "Gen: 2" -> 5
    // ./Tarea1_1-2022175018 | grep -c "Gen: 1" -> 1
    exit(0);
}