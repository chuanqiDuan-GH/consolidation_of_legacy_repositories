#ifndef	__OP_H__
#define	__OP_H__
typedef void (*cbFunc)(int, int);

void call(cbFunc pcbFunc, int num1, int num2);
void op_plus(int num1, int num2);
void op_sub(int num1, int num2);
void op_mul(int num1, int num2);
void op_div(int num1, int num2);


#endif	//__OP_H__
