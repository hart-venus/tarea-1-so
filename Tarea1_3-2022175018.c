#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N_HIJOS = 5;
    int exit_codes[N_HIJOS];
    
    for (int i = 0; i < N_HIJOS; i++){
        int pid = fork();
        if (pid == 0){
            // codigo del hijo generado 
            srand(getpid()); // asegura un numero random diferente para cada hijo
            int n_random = rand() % 100; // numero random entre 0 y 99
            printf("Este es mi número random: %d \n", n_random);
            exit(n_random); // termina el proceso hijo con el numero random 
        } else {
            // este codigo solo lo ejecuta el padre
            int status;
            waitpid(pid, &status, 0); // espera a que el hijo termine
            if (WIFEXITED(status)){
                exit_codes[i] = WEXITSTATUS(status); // guarda el valor de salida del hijo
            }
        }
    }
    printf("Los números random generados son: ");
    for (int i = 0; i < N_HIJOS; i++){
        printf("%d ", exit_codes[i]);
    }
    printf("\n");
    exit(0);
}