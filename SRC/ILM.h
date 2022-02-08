#ifndef ILM_H
#define ILM_H

//includes
#include <stdint.h>

//defines

#define KERNEL_SIZE 0x170

#define MEMORY_SIZE         KERNEL_SIZE
#define STACK_SIZE          0xFF
#define LINE_SIZE           0x40
#define MAX_LINES           0xFF
#define LINES_STACK_SIZE    0xFF
#define AESTK_SIZE          0xFF

#define ILM_COLLECTOR_POINT 0x02
#define ILM_EXECUTOR_POINT  0x0A

#define VARIABLES_SIZE      0x1A
#define VARIABLE_OFFSET     0x41

//defines
#define NOP     0x00
#define TST     0x01
#define CALL    0x02
#define RTN     0x03
#define DONE    0x04
#define JMP     0x05
#define PRS     0x06
#define PRN     0x07
#define SPC     0x08
#define NLINE   0x09
#define NXT     0x0A
#define XFER    0x0B
#define SAV     0x0C
#define RSTR    0x0D
#define CMPR    0x0E
#define LIT     0x0F
#define INNUM   0x10
#define FIN     0x11
#define ERR     0x12
#define ADD     0x13
#define SUB     0x14
#define NEG     0x15
#define MUL     0x16
#define DIV     0x17
#define STORE   0x18
#define TSTV    0x19
#define TSTN    0x1A
#define IND     0x1B
#define LST     0x1C
#define INIT    0x1D
#define GETLINE 0x1E
#define TSTL    0x1F
#define INSRT   0x20
#define XINIT   0x21
#define MODE    0x22 //MODE : 0 = direct, 1 = run, 2 = exit


typedef struct ILM
{
    uint8_t VMODE;

	uint16_t PC;
    
    uint8_t MEM[MEMORY_SIZE];
    
    uint8_t SP;
    
    uint16_t STACK[STACK_SIZE];
	
    uint8_t LBUF[LINE_SIZE];

    uint8_t CURSOR_LINE;

    uint8_t CURSOR; 

    uint8_t LINES[MAX_LINES][LINE_SIZE];

    uint8_t LINES_SP;

    uint8_t LINES_STACK[LINES_STACK_SIZE];

    uint8_t AESTK_SP;

    int AESTK[AESTK_SIZE];

    int VARIABLES[VARIABLES_SIZE];

}ILM;

/**********/
void ILM_error(ILM *IL, char *str);

void ILM_init(ILM *IL);

void ILM_reset(ILM *IL);

void ILM_execute(ILM *IL);

void ILM_execute_ins(ILM *IL);

void ILM_NOP(ILM *IL);
void ILM_TST(ILM *IL);
void ILM_CALL(ILM *IL);
void ILM_RTN(ILM *IL);
void ILM_DONE(ILM *IL);
void ILM_JMP(ILM *IL);
void ILM_PRS(ILM *IL);
void ILM_PRN(ILM *IL);
void ILM_SPC(ILM *IL);
void ILM_NLINE(ILM *IL);
void ILM_NXT(ILM *IL);
void ILM_XFER(ILM *IL);
void ILM_SAV(ILM *IL);
void ILM_RSTR(ILM *IL);
void ILM_CMPR(ILM *IL);
void ILM_LIT(ILM *IL);
void ILM_INNUM(ILM *IL);
void ILM_FIN(ILM *IL);
void ILM_ERR(ILM *IL);
void ILM_ADD(ILM *IL);
void ILM_SUB(ILM *IL);
void ILM_NEG(ILM *IL);
void ILM_MUL(ILM *IL);
void ILM_DIV(ILM *IL);
void ILM_STORE(ILM *IL);
void ILM_TSTV(ILM *IL);
void ILM_TSTN(ILM *IL);
void ILM_IND(ILM *IL);
void ILM_LST(ILM *IL);
void ILM_INIT(ILM *IL);
void ILM_GETLINE(ILM *IL);
void ILM_TSTL(ILM *IL);
void ILM_INSRT(ILM *IL);
void ILM_XINIT(ILM *IL);
void ILM_MODE(ILM *IL);

#endif