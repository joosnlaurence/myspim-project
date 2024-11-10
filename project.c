#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    //add
	if (ALUControl == 0) // 000
		*ALUresult = A + B;

	//subtract
	else if (ALUControl == 1) // 001
		*ALUresult = A - B;

	//SLT (set if less than) for signed integers
	else if (ALUControl == 2) // 010
		*ALUresult = ((int)A < (int)B) ? 1 : 0;
	
	//SLT for unsigned integers
	else if (ALUControl == 3) // 011
		*ALUresult = (A < B) ? 1 : 0;

	//AND
	else if (ALUControl == 4) // 100
		*ALUresult = A & B;

	//OR
	else if (ALUControl == 5) // 101
		*ALUresult = A | B;

	//Shift Left by 16 
	else if (ALUControl == 6) // 110
		*ALUresult = B << 16;

	//NOT of A
	else // 111
		*ALUresult = ~A;

	//Assign Zero to 1 if the result is zero; otherwise, assign 0.
	*Zero = (*ALUresult == 0) ? 1 : 0;
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    // Check if PC is word-aligned
	if(PC % 4 != 0) 
		return 1;

	// Fetch instruction from memory
	*instruction = Mem[(PC >> 2)];

	if (*instruction == 0x00000000)
		return 1;

	return 0;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    unsigned op_mask = 0xFC000000; // instruction [31-26]
    unsigned r1_mask = 0x03E00000; // instruction [25-21]  
    unsigned r2_mask = r1_mask >> 5; // instruction [20-16]
    unsigned r3_mask = r2_mask >> 5; // instruction [15-11]
    unsigned funct_mask = 0x0000003F; // instruction [5-0]
    unsigned offset_mask = 0x0000FFFF; // instruction [15-0]
    unsigned jsec_mask = ~op_mask;  // instruction [25-0]      

    *op = (instruction & op_mask) >> 26;              
    *r1 = (instruction & r1_mask) >> 21;    
    *r2 = (instruction & r2_mask) >> 16;    
    *r3 = (instruction & r3_mask) >> 11;    
    *funct = instruction & funct_mask;
    *offset = instruction & offset_mask; 
    *jsec = instruction & jsec_mask;   
}


/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    if((offset >> 15) == 1)
        offset = offset | 0xFFFF0000;
    
    *extended_value = offset;
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}
