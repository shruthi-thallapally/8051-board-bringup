ORG 0000H
MOV B,#80H  	//2 Bytes,2 instruction cycles,storing divisor value in B
MOV A,#93H		//2 Bytes,2 instruction cycles,storing dividend value in A
MOV 20H,A 		//2 Bytes,2 instruction cycles,storing A value in internal memory
MOV 21H,A		//2 Bytes,2 instruction cycles,storing A value in internal memory
MOV 22H,B		//2 Bytes,2 instruction cycles,storing B value in internal memory
MOV A,B			//1 Byte,1 instruction cycles,storing B value in A
JZ ERROR_DIVISOR_ZERO		//2 Bytes,2 or 3 instruction cycles,checking if value in A is ZERO if it is, jumping to error_divisor_zero
RLC A			//1 Byte,1 instruction cycles,left shifting value in A(multiply by 2)
JC ERROR_8BIT_EXCEED
RLC A			//1 Byte,1 instruction cycles,left shifting value in A(multiply by 2)
JC ERROR_8BIT_EXCEED		//2 bytes,2 or 3 instruction cycles,checking if value is overflowing if it is, jumping to exceed_8bit_exceed
CLR C			//1 Byte,1 instruction cycles,clearing carry flag
MOV B,A			//1 Byte,1 instruction cycles,storing divisor value in B
MOV R0,#0H 		//2 bytes,2 instruction cycles,Intiating R0 register to zero to store quotient
MOV A,20H		//2 Bytes,2 instruction cycles,storing dividend value in A

DIVISIONLOOP:	//loop to divide
MOV R1,A		//1 Byte,1 instruction cycles,storing A value in R1 for future reference
SUBB A,B		//1 Byte,1 instruction cycles
JC DIVISIONEND	//2 Bytes,2 or 3 instruction cycles
INC R0			//1 Byte,1 instruction cycles,Incrementing R0 to store quotient
SJMP DIVISIONLOOP //2 bytes,3 instruction cycles

DIVISIONEND:	//Loop to end the division

MOV 24H,R0		//2 bytes,2 instruction cycles
MOV 25H,R1		//2 Bytes,2 instruction cycles
MOV 30H,#00H	//3 bytes,3 instruction cycles
SJMP ENDLOOP	//2 Bytes,3 instruction cycles


ERROR_DIVISOR_ZERO:		//error when divisor is zero
MOV 30H,#01H	//3 bytes,3 instruction cycles
SJMP ENDLOOP	//2 bytes,3 instruction cycles

ERROR_8BIT_EXCEED:		//error when bits overfloww
MOV 30H,#02H	//3 Bytes,3 instruction cycles
SJMP ENDLOOP	//2 bytes,3 instruction cycles

ENDLOOP:
SJMP ENDLOOP	//2 bytes,3 instruction cycles

END
