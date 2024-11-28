#include <stdio.h>
#include <stddef.h> 

#define TAMANHO_MEMORIA 1024  

unsigned char memoria[TAMANHO_MEMORIA];

typedef struct {
    void* ptr;      // Ponteiro para o início do bloco alocado
    size_t tamanho; // Tamanho do bloco alocado
} BlocoMemoria;

BlocoMemoria alocacoes[100];
int num_alocacoes = 0;        

// Função malloc
void* aloca(size_t tamanho) {
    for (int i = 0; i < TAMANHO_MEMORIA - tamanho; i++) {
        int livre = 1;
        // Valida se espaço de memória está livre
        for (int j = 0; j < num_alocacoes; j++) {
            if (alocacoes[j].ptr >= (void*)&memoria[i] &&
                alocacoes[j].ptr < (void*)&memoria[i + tamanho]) {
                livre = 0;  // O espaço já foi alocado
                break;
            }
        }

        // Se o espaço está livre, aloca o bloco
        if (livre) {
            void* ptr = &memoria[i];
            alocacoes[num_alocacoes].ptr = ptr;
            alocacoes[num_alocacoes].tamanho = tamanho;
            num_alocacoes++;
            return ptr;
        }
    }
    
    return NULL;
}

// Função free
void desaloca(void* ptr) {
    // Procurar o bloco de memória a ser desalocado
    for (int i = 0; i < num_alocacoes; i++) {
        if (alocacoes[i].ptr == ptr) {
            // Libera a alocação com vazio
            for (int j = i; j < num_alocacoes - 1; j++) {
                alocacoes[j] = alocacoes[j + 1]; // Move os blocos para baixo
            }
            num_alocacoes--;
            return;
        }
    }
    
    printf("Erro: Tentativa de desalocar memória não alocada.\n");
}

int main() {
    void* ptr1 = aloca(100);  // Aloca 100 bytes
    void* ptr2 = aloca(200);  // Aloca 200 bytes
    void* ptr3 = aloca(50);   // Aloca 50 bytes

    if (ptr1 != NULL) {
        printf("Bloco 1 alocado com sucesso.\n");
    } else {
        printf("Falha na alocação do bloco 1.\n");
    }

    if (ptr2 != NULL) {
        printf("Bloco 2 alocado com sucesso.\n");
    } else {
        printf("Falha na alocação do bloco 2.\n");
    }

    if (ptr3 != NULL) {
        printf("Bloco 3 alocado com sucesso.\n");
    } else {
        printf("Falha na alocação do bloco 3.\n");
    }

    // Desalocando um bloco
    desaloca(ptr2);
    printf("Bloco 2 desalocado.\n");

    // Tentando alocar novamente após desalocar
    void* ptr4 = aloca(100); 
    if (ptr4 != NULL) {
        printf("Bloco 4 alocado com sucesso após desalocação.\n");
    } else {
        printf("Falha na alocação do bloco 4.\n");
    }

    return 0;
}
