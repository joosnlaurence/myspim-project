#include "spimcore.h"

/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
    //printf("op: %u\n", op);
    char isValid = 9; // If > 0, then opcode matches at least one instruction
    
    if(op == 0) {
        // Asserted for R-Type
        controls->RegDst = (char) 1;
        //printf("op is 000000\n");
    }
    // addi, slti, sltiu, lui, and lw
    else if(op == 0b001000 || op == 0b001010 || op == 0b001011 || 
            op == 0b001111 || op == 0b100011) {
        // De-Asserted for I-Type
        controls->RegDst = (char) 0;
    }
    else {
        // Don't care
        controls->RegDst = (char) 2;
        isValid--;
    }

    if(op == 0b000010) {
        // Asserted for jump
        controls->Jump = (char) 1;
    }
    else {
        // De-Asserted otherwise
        controls->Jump = (char) 0;
        isValid--;
    }

    if(op == 0b000100) {
        // Asserted for BEQ
        controls->Branch = (char) 1;
    }
    else {
        // De-Asserted otherwise
        controls->Branch = (char) 0;
        isValid--;
    }

    if(op == 0b100011) {
        // Asserted for LW
        controls->MemRead = (char) 1;
    }
    else {
        // De-Asserted otherwise
        controls->MemRead = (char) 0;
        isValid--;
    }

    if(op == 0b101011) {
        // Asserted for SW
        controls->MemWrite = (char) 1;
    }
    else {
        // De-Asserted Otherwise
        controls->MemWrite = (char) 0;
        isValid--;
    }

    if(op == 0b100011) {
        // Asserted for LW
        controls->MemtoReg = (char) 1;
    }
    else if(op == 0b000010){
        // Don't care for jump
        controls->MemtoReg = (char) 2;
    }
    else{
        // De-Asserted otherwise
        controls->MemtoReg = (char) 0;
        isValid--;
    }

    if(op == 0 || op == 0b000100) {
        // De-asserted for R-Types and BEQ
        controls->ALUSrc = (char) 0;
    }
    else {
        // Asserted otherwise
        controls->ALUSrc = (char) 1;
        isValid--;
    }
    
    if (op == 0b000000 || op == 0b001000 || op == 0b001010 || 
        op == 0b001011 || op == 0b001111 || op == 0b100011) {
        // Asserted for R-types, addi, slti, sltiu, lui, and lw
        controls->RegWrite = (char) 1;
    }
    else {
        // De-Asserted otherwise
        controls->RegWrite = (char) 0;
        isValid--;
    }

    // beq
    if(op == 0b000100){
        controls->ALUOp = (char) 1;
    }
    // slti
    else if(op == 0b001010) {
        controls->ALUOp = (char) 2;
    }
    // sltiu
    else if(op == 0b001011) {
        controls->ALUOp = (char) 3;
    }
    // lui
    else if(op == 0b001111){
        controls->ALUOp = (char) 6;
    }
    // R-type Instruction
    else if(op == 0) {
        controls->ALUOp = (char) 7;
    }
    // sw, lw, addi, or don't care
    else {
        isValid--;
        controls->ALUOp = 0;
    }
    if(!isValid)
        return 1;
    return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}
