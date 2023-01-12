#ifndef GENERATOR_H
#define GENERATOR_H

#include "cpu.h"

Instruction* generateRandomInstructions(int);
Instruction* generateMultiplicationInstructions(int, int);
Instruction* generateDivisionInstructions(int, int);
Instruction* generateRestDivisionInstructions(int, int);
Instruction* generateFibonacciInstructions(int);
Instruction* readInstructions(char*, int*);

#endif // !GENERATOR_H