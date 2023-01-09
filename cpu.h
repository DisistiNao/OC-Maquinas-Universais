#ifndef CPU_H
#define CPU_H

typedef struct {
    int opcode; // instructions
    int info1; // val 01
    int info2; // val 02
    int info3; // val slavar
} Instruction;

typedef struct {
    float *items;
    int size;
} Memory;

typedef struct {
    Instruction* instructions;
    Memory RAM;
} Machine;

void start(Machine*, Instruction*, int);
void stop(Machine*);
void run(Machine*);
void printRAM(Machine*);

#endif // !CPU_H