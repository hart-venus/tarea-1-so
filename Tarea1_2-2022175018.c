#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char to_char(int i) {
    return (char) (i + 65); // 65 es el valor ASCII de 'A'
}

int main() {
    int N_CHILDREN = 3; // A -> B -> C
    int i = 0;
    for (i = 0; i < N_CHILDREN; i++) {
        int pid = fork();
        if (pid != 0) {
            int tiempo_espera = (i+1)*5;
            sleep(tiempo_espera);
            printf("%c: Terminé de dormir %d segundos. \n", to_char(i), (i+1)*5);
            wait(NULL); // esperar a que el hijo termine
            if (i+1 < N_CHILDREN) printf("%c: Terminé de esperar a mi hijo %c. \n", to_char(i), to_char(i+1)); // asegura que no soy el ultimo de la cadena
            break; // los padres anteriores no deben crear más hijos
        }
    }
}