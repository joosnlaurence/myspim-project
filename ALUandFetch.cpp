#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A, unsigned B, char ALUControl, unsigned* ALUresult, char* Zero)
{
	//add
	if (ALUControl == '000')
		*ALUresult = A + B;

	//subtract
	else if (ALUControl == '001')
		*ALUresult = A - B;

	//SLT (set if less than) for signed integers
	else if (ALUControl == '010')
		*ALUresult = ((int)A < (int)B) ? 1 : 0;
	
	//SLT for unsigned integers
	else if (ALUControl == '011') 		
		*ALUresult = (A < B) ? 1 : 0;

	//AND
	else if (ALUControl == '100')
		*ALUresult = A & B;

	//OR
	else if (ALUControl == '101')
		*ALUresult = A | B;

	//Shift Left by 16
	else if (ALUControl == '110')
		*ALUresult = B << 16;

	//NOT of A
	else (ALUControl == '111')
		*ALUresult = ~A;

	//Assign Zero to 1 if the result is zero; otherwise, assign 0.
	*Zero = (*ALUresult == 0) ? 1 : 0;
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC, unsigned* Mem, unsigned* instruction)
{

	// Fetch instruction from memory
	*instruction = Mem[(PC >> 2)];

	if (*instruction == 0x00000000)
		return 1;

	return 0;
}
