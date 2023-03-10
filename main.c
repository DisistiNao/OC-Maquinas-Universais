#include "cpu.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char**argv) {

    // double tempo_gasto = 0.0;
    // clock_t inicio = clock();

    srand(time(NULL));   // Inicializacao da semente para os numeros aleatorios.

    if (argc != 3) {
        printf("Numero de argumentos invalidos! Sao 3.\n");
        printf("Linha de execucao: ./exe TIPO_INSTRUCAO [TAMANHO_RAM|ARQUIVO_DE_INSTRUCOES]\n");
        printf("\tExemplo 1 de execucao: ./exe random 10\n");
        printf("\tExemplo 3 de execucao: ./exe file arquivo_de_instrucoes.txt\n");
        return 0;
    }

    int ramSize;
    Machine machine;
    Instruction *instructions;

    if (strcmp(argv[1], "random") == 0) {
        ramSize = atoi(argv[2]);
        instructions = generateRandomInstructions(ramSize);
    } else if (strcmp(argv[1], "multiply") == 0) {
        ramSize = atoi(argv[2]);
        instructions = generateMultiplicationInstructions(3, 4);
    } else if (strcmp(argv[1], "share") == 0) {
        ramSize = atoi(argv[2]);
        instructions = generateDivisionInstructions(27, 3);
    } else if (strcmp(argv[1], "rest") == 0) {
        ramSize = atoi(argv[2]);
        instructions = generateRestDivisionInstructions(28, 3);
    } else if (strcmp(argv[1], "fibo") == 0) {
        ramSize = atoi(argv[2]);
        instructions = generateFibonacciInstructions(ramSize);
    } else if (strcmp(argv[1], "file") == 0) {
        instructions = readInstructions(argv[2], &ramSize);
    } 
    else {
        printf("Opcao invalida.\n");
        return 0;
    }
    
    printf("Iniciando a maquina...\n");
    start(&machine, instructions, ramSize);
    printRAM(&machine);
    run(&machine);
    printRAM(&machine);
    stop(&machine);
    printf("Finalizando a maquina...\n");

    // clock_t fim = clock();
    // tempo_gasto += (double) (fim - inicio) / CLOCKS_PER_SEC;

    // printf("Tempo de execução: %f segundos\n", tempo_gasto);

    return 0;
}