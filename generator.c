#include "generator.h"
#include <stdio.h>
#include <stdlib.h>

Instruction* generateRandomInstructions(int ramSize) {
    // 01|22|13|45 => isto é uma instrução
    // 02|33|12|01 => isto é outra instrução
            
    // 0 => salvar na memória
    // 1 => opcode => somar
    // 2 => opcode => subtrair
    //-1 => halt

    // 22 => significa um endereço da RAM (10 endereço) 
    // 13 => significa 2o endereço
    // 45 => significa 3o endereco
    //ramSize => ESTA FORA DO INTERVALO DE 0 A ramSize DA MEMÓRIA RAM

    Instruction* instructions = (Instruction*) malloc(10 * sizeof(Instruction)); // tornar esse 10 variado, passando como parametro

    for (int i=0; i<9; i++){
        instructions[i].opcode = rand() % 4; //0, 1, 2
        instructions[i].info1 = rand() % ramSize; //0 ... RAM_SIZE
        do {
            instructions[i].info2 = rand() % ramSize; //0 ... RAM_SIZE
        } while (instructions[i].info1 == instructions[i].info2);
        instructions[i].info3 = rand() % ramSize; //0 ... RAM_SIZE
    }
    
    //inserindo a ultima instrucao do programa que nao faz nada que presta
    instructions[9].opcode =-1;
    instructions[9].info1 = -1;
    instructions[9].info2 = -1;
    instructions[9].info3 = -1;
    
    return instructions;
}

Instruction* generateMultiplicationInstructions(int multiplier, int multiplicand) {
    Instruction* instructions = (Instruction*) malloc((3 + multiplier) * sizeof(Instruction));

    instructions[0].opcode = 0;
    instructions[0].info1 = multiplicand;
    instructions[0].info2 = 0;

    instructions[1].opcode = 0;
    instructions[1].info1 = 0;
    instructions[1].info2 = 1;

    for(int i = 0; i < multiplier; i++) {
        instructions[i + 2].opcode = 1;
        instructions[i + 2].info1 = 0;
        instructions[i + 2].info2 = 1;
        instructions[i + 2].info3 = 1;
    }

    instructions[multiplier + 2].opcode = -1;
    instructions[multiplier + 2].info1 = -1;
    instructions[multiplier + 2].info2 = -1;
    instructions[multiplier + 2].info3 = -1;

    return instructions;
}

Instruction* generateDivisionInstructions(int dividend, int divisor) {
    Instruction* instructions = (Instruction*) malloc((4 + dividend) * sizeof(Instruction));
    int i = 0;

    instructions[0].opcode = 0;
    instructions[0].info1 = dividend;
    instructions[0].info2 = 0;

    instructions[1].opcode = 0;
    instructions[1].info1 = divisor;
    instructions[1].info2 = 1;

    instructions[2].opcode = 0;
    instructions[2].info1 = 0;
    instructions[2].info2 = 2;

    for(i = 1; (i * divisor) <= dividend; i++) {
        instructions[i + 2].opcode = 2;
        instructions[i + 2].info1 = 0;
        instructions[i + 2].info2 = 1;
        instructions[i + 2].info3 = 0;
    }

    instructions[i + 2].opcode = 0;
    instructions[i + 2].info1 = i - 1;
    instructions[i + 2].info2 = 2;

    instructions[i + 3].opcode = -1;
    instructions[i + 3].info1 = -1;
    instructions[i + 3].info2 = -1;
    instructions[i + 3].info3 = -1;

    return instructions;
}

Instruction* generateRestDivisionInstructions(int dividend, int divisor) {
    Instruction* instructions = (Instruction*) malloc((3 + dividend) * sizeof(Instruction));
    int i = 0;

    instructions[0].opcode = 0;
    instructions[0].info1 = dividend;
    instructions[0].info2 = 1;

    instructions[1].opcode = 0;
    instructions[1].info1 = divisor;
    instructions[1].info2 = 0;

    for(i = 1; (i * divisor) <= dividend; i++) {
        instructions[i + 1].opcode = 2;
        instructions[i + 1].info1 = 1;
        instructions[i + 1].info2 = 0;
        instructions[i + 1].info3 = 1;
    }

    instructions[i + 1].opcode = -1;
    instructions[i + 1].info1 = -1;
    instructions[i + 1].info2 = -1;
    instructions[i + 1].info3 = -1;

    return instructions;
}

Instruction* generateFibonacciInstructions(int fibo) {
    Instruction* instructions = (Instruction*) malloc((fibo + 1) * sizeof(Instruction));

    instructions[0].opcode = 0;
    instructions[0].info1 = 0;
    instructions[0].info2 = 0;

    instructions[1].opcode = 0;
    instructions[1].info1 = 1;
    instructions[1].info2 = 1;

    for(int i = 2; i < fibo; i++) {
        instructions[i].opcode = 1;
        instructions[i].info1 = i-2;
        instructions[i].info2 = i-1;
        instructions[i].info3 = i;
    }

    instructions[fibo].opcode = -1;
    instructions[fibo].info1 = -1;
    instructions[fibo].info2 = -1;
    instructions[fibo].info3 = -1;

    return instructions;
}

Instruction* readInstructions(char* fileName, int* ramSize) {
    printf("FILE -> %s\n", fileName);
    FILE* file = fopen(fileName, "r"); // Abrindo arquivo no modo leitura
    
    if (file == NULL) {
        printf("Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    int n, i = 0;
    fscanf(file, "%d %d", ramSize, &n);
    Instruction* instructions = (Instruction*) malloc(n * sizeof(Instruction));
    while (i < n) {
        fscanf(file, "%d %d %d %d", &instructions[i].opcode, &instructions[i].info1, &instructions[i].info2, &instructions[i].info3);
        i++;
    }
    fclose(file); // Fechando o arquivo

    return instructions;
}
