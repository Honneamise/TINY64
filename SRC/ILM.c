//std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ilm
#include "ILM.h"
#include "ILM_utils.h"

//compiled kernel
const uint8_t KERNEL[KERNEL_SIZE] = {
	0x1D, 0x09, 0x1E, 0x1F, 0x00, 0x0A, 0x20, 0x05, 0x00, 0x02, 0x21, 0x01,
	0x00, 0x20, 0x03, 0x4C, 0x45, 0x54, 0x19, 0x00, 0xD7, 0x01, 0x00, 0xD7,
	0x01, 0x3D, 0x02, 0x00, 0xD8, 0x04, 0x18, 0x0A, 0x01, 0x00, 0x3E, 0x02,
	0x47, 0x4F, 0x01, 0x00, 0x31, 0x02, 0x54, 0x4F, 0x02, 0x00, 0xD8, 0x04,
	0x0B, 0x01, 0x00, 0xD7, 0x03, 0x53, 0x55, 0x42, 0x02, 0x00, 0xD8, 0x04,
	0x0C, 0x0B, 0x01, 0x00, 0x60, 0x05, 0x50, 0x52, 0x49, 0x4E, 0x54, 0x01,
	0x00, 0x59, 0x01, 0x22, 0x06, 0x01, 0x00, 0x56, 0x01, 0x2C, 0x08, 0x05,
	0x00, 0x47, 0x04, 0x09, 0x0A, 0x02, 0x00, 0xD8, 0x07, 0x05, 0x00, 0x4D,
	0x01, 0x00, 0x7B, 0x02, 0x49, 0x46, 0x02, 0x00, 0xD8, 0x02, 0x01, 0x38,
	0x02, 0x00, 0xD8, 0x01, 0x00, 0xD7, 0x04, 0x54, 0x48, 0x45, 0x4E, 0x0E,
	0x05, 0x00, 0x0B, 0x01, 0x00, 0x93, 0x05, 0x49, 0x4E, 0x50, 0x55, 0x54,
	0x19, 0x00, 0xD7, 0x10, 0x18, 0x01, 0x00, 0x91, 0x01, 0x2C, 0x05, 0x00,
	0x84, 0x04, 0x0A, 0x01, 0x00, 0xA0, 0x06, 0x52, 0x45, 0x54, 0x55, 0x52,
	0x4E, 0x04, 0x0D, 0x0A, 0x01, 0x00, 0xAA, 0x03, 0x45, 0x4E, 0x44, 0x22,
	0x00, 0x11, 0x01, 0x00, 0xB5, 0x04, 0x4C, 0x49, 0x53, 0x54, 0x04, 0x1C,
	0x0A, 0x01, 0x00, 0xC0, 0x03, 0x52, 0x55, 0x4E, 0x04, 0x22, 0x01, 0x0A,
	0x01, 0x00, 0xCD, 0x05, 0x43, 0x4C, 0x45, 0x41, 0x52, 0x04, 0x05, 0x00,
	0x00, 0x01, 0x00, 0xD7, 0x04, 0x45, 0x58, 0x49, 0x54, 0x22, 0x02, 0x12,
	0x01, 0x00, 0xE4, 0x01, 0x2D, 0x02, 0x01, 0x05, 0x15, 0x05, 0x00, 0xEC,
	0x01, 0x00, 0xE9, 0x01, 0x2B, 0x02, 0x01, 0x05, 0x01, 0x00, 0xF8, 0x01,
	0x2B, 0x02, 0x01, 0x05, 0x13, 0x05, 0x00, 0xEC, 0x01, 0x01, 0x04, 0x01,
	0x2D, 0x02, 0x01, 0x05, 0x14, 0x05, 0x00, 0xEC, 0x03, 0x02, 0x01, 0x20,
	0x01, 0x01, 0x14, 0x01, 0x2A, 0x02, 0x01, 0x20, 0x16, 0x05, 0x01, 0x08,
	0x01, 0x01, 0x04, 0x01, 0x2F, 0x02, 0x01, 0x20, 0x17, 0x05, 0x01, 0x08,
	0x19, 0x01, 0x25, 0x1B, 0x03, 0x1A, 0x01, 0x29, 0x03, 0x01, 0x01, 0x37,
	0x01, 0x28, 0x02, 0x00, 0xD8, 0x01, 0x01, 0x37, 0x01, 0x29, 0x03, 0x12,
	0x01, 0x01, 0x40, 0x01, 0x3D, 0x0F, 0x00, 0x03, 0x01, 0x01, 0x58, 0x01,
	0x3C, 0x01, 0x01, 0x4D, 0x01, 0x3D, 0x0F, 0x02, 0x03, 0x01, 0x01, 0x55,
	0x01, 0x3E, 0x0F, 0x03, 0x03, 0x0F, 0x01, 0x03, 0x01, 0x00, 0xD7, 0x01,
	0x3E, 0x01, 0x01, 0x65, 0x01, 0x3D, 0x0F, 0x05, 0x03, 0x01, 0x01, 0x6D,
	0x01, 0x3C, 0x0F, 0x03, 0x03, 0x0F, 0x04, 0x03
};

/**********/
void ILM_error(ILM *IL, char *str)
{
    int i = 0;

    if(IL->VMODE==0) 
    { 
        printf("[!] %s\n", (str!=NULL) ? str : "" );

        printf("%s",IL->LINES[IL->CURSOR_LINE]);
    }
    else 
    { 
        printf("[%d] %s\n",IL->CURSOR_LINE, (str!=NULL)? str : "" );

        printf("%s",IL->LINES[IL->CURSOR_LINE]);
    }

    for(i=0;i<IL->CURSOR;i++)
    {
        printf("-");
    };

    printf("^\n"); 

    IL->CURSOR = 0;

    IL->CURSOR_LINE = 0;

    IL->PC = ILM_COLLECTOR_POINT;

    IL->VMODE = 0;
}

/**********/
void ILM_init(ILM *IL)
{
    ILM_reset(IL);

    memcpy(IL->MEM, KERNEL, KERNEL_SIZE);

    printf("TINY64 OK !!!");
}

/**********/
void ILM_reset(ILM *IL)
{
    int i = 0;

    IL->PC = 0x00;
    
    IL->SP = 0x00;

    IL->LINES_SP = 0x00;

    IL->AESTK_SP = 0x00;

    IL->CURSOR = 0x00;

    IL->CURSOR_LINE = 0x00;

    IL->VMODE = 0x00;
    
    for(i=0;i<STACK_SIZE;i++)
    {
        IL->STACK[i] = 0x00;
    }
	
    ILM_line_clear(IL->LBUF);

    for(i=0;i<MAX_LINES;i++)
    {
        ILM_line_clear(IL->LINES[i]);
    }

    for(i=0;i<LINES_STACK_SIZE;i++)
    {
        IL->LINES_STACK[i] = 0x00;
    }

    for(i=0;i<AESTK_SIZE;i++)
    {
        IL->AESTK[i] = 0x00;
    }

    for(i=0;i<VARIABLES_SIZE;i++)
    {
        IL->VARIABLES[i] = 0x00;
    }

}

/**********/
void ILM_execute(ILM *IL)
{
    while(IL->VMODE!=2)
    {
        ILM_execute_ins(IL);
    }
}

/**********/
void ILM_execute_ins(ILM *IL)
{

    switch(IL->MEM[IL->PC])
    {
        case NOP: 
            ILM_NOP(IL);
            break;
        case TST: 
            ILM_TST(IL);
            break;     
        case CALL:
            ILM_CALL(IL); 
            break;
        case RTN: 
            ILM_RTN(IL);
            break;
        case DONE: 
            ILM_DONE(IL);
            break;
        case JMP: 
            ILM_JMP(IL);
            break;
        case PRS: 
            ILM_PRS(IL);
            break;
        case PRN: 
            ILM_PRN(IL);
            break;
        case SPC: 
            ILM_SPC(IL);
            break;
        case NLINE: 
            ILM_NLINE(IL);
            break;
        case NXT: 
            ILM_NXT(IL);
            break;
        case XFER:
            ILM_XFER(IL);
            break;
        case SAV: 
            ILM_SAV(IL);
            break;
        case RSTR: 
            ILM_RSTR(IL);
            break;
        case CMPR: 
            ILM_CMPR(IL);
            break;
        case LIT: 
            ILM_LIT(IL);
            break;
        case INNUM: 
            ILM_INNUM(IL);
            break;
        case FIN: 
            ILM_FIN(IL);
            break;
        case ERR: 
            ILM_ERR(IL);
            break;
        case ADD: 
            ILM_ADD(IL);
            break;
        case SUB: 
            ILM_SUB(IL);
            break;
        case NEG: 
            ILM_NEG(IL);
            break;
        case MUL: 
            ILM_MUL(IL);
            break;
        case DIV: 
            ILM_DIV(IL);
            break;
        case STORE: 
            ILM_STORE(IL);
            break;
        case TSTV: 
            ILM_TSTV(IL);
            break;
        case TSTN: 
            ILM_TSTN(IL);
            break;
        case IND: 
            ILM_IND(IL);
            break;
        case LST: 
            ILM_LST(IL);
            break;
        case INIT: 
            ILM_INIT(IL);
            break;
        case GETLINE: 
            ILM_GETLINE(IL);
            break;
        case TSTL: 
            ILM_TSTL(IL);
            break;
        case INSRT: 
            ILM_INSRT(IL);
            break;
        case XINIT: 
            ILM_XINIT(IL);
            break;
        case MODE: 
            ILM_MODE(IL);
            break;

        default:
            ILM_error(IL,"[!!!] Unknow instruction found");
            ILM_error(IL,"[!!!] PROGRAM HALTED");
            IL->VMODE = 2;
            break;
    }
}

/**********/
void ILM_NOP(ILM *IL)
{
    // no op 
    ILM_error(IL,"[!!!] NOP instruction found");
    ILM_error(IL,"[!!!] PROGRAM HALTED");
    IL->VMODE = 2;
}

/**********/
void ILM_TST(ILM *IL)
{
    //delete leading blanks
    //If string matches the BASIC line, advance cursor over the matched string and execute the next IL instruction.
    //If a match fails, execute the IL instruction at the labled lbl.

    int i = 0;
    int start = 0;
    int end = 0;
    uint8_t *token = NULL;

    //retrieve keyword from memory
    int tp = IL->PC + 3;

    int len = IL->MEM[tp];

    uint8_t *str = calloc(len+1,sizeof(uint8_t));

    tp++;

    for(i=0;i<len;i++)
    {
        str[i] = IL->MEM[tp+i];        
    }

    //token
    if(ILM_skip_spaces(IL)<0) { ILM_error(IL, "Error code 1"); return; }

    start = IL->CURSOR;

    end = start + len;

    token = calloc(end-start+1,sizeof(char));
    memcpy(token,IL->LINES[IL->CURSOR_LINE] + start, end-start);

    if(strcmp(token,str)==0)
    {
        IL->PC += 2 + 1 + len + 1;

        IL->CURSOR = end;
    }
    else//match fail, go to label
    {
        IL->PC = (IL->MEM[IL->PC+1] << 8 ) + IL->MEM[IL->PC+2];
    }

    free(token);
    free(str);
}

/**********/
void ILM_CALL(ILM *IL)
{
    //Execute the IL subroutine starting at lbl. 
    //Save the IL address following the CALL on the control stack.

    IL->STACK[IL->SP] = IL->PC + 3;

    IL->SP++;

    IL->PC = (IL->MEM[IL->PC+1] << 8 ) + IL->MEM[IL->PC+2];
}

/**********/
void ILM_RTN(ILM *IL)
{
    //Return to the IL location specified by the top of the control stack.

    IL->SP--;
    
    IL->PC = IL->STACK[IL->SP];  
}

/**********/
void ILM_DONE(ILM *IL)
{
    //Report a syntax error if after deletion leading blanks the cursor is not positioned to road a carriage return.

    ILM_skip_spaces(IL);

    if(IL->LINES[IL->CURSOR_LINE][IL->CURSOR]!='\n') { ILM_error(IL, "Error code 2"); return; }

    IL->PC++;
}

/**********/
void ILM_JMP(ILM *IL)
{
    //Continue execution of IL at the line specified.

    IL->PC = (IL->MEM[IL->PC+1] << 8 ) + IL->MEM[IL->PC+2];
}

/**********/
void ILM_PRS(ILM *IL)
{
    //Print characters from the BASIC text up to but not including the closing quote mark. 
    //If a cr is found in the program text, report an error. 
    //Move the cursor to the point following the closing quote.

    while(IL->LINES[IL->CURSOR_LINE][IL->CURSOR]!='"')
    {
        if(IL->LINES[IL->CURSOR_LINE][IL->CURSOR]=='\n')
        {
            ILM_error(IL,"Error code 3");
            return;
        }
        printf("%c",IL->LINES[IL->CURSOR_LINE][IL->CURSOR]);
        IL->CURSOR++;
    }

    IL->CURSOR++;

    IL->PC++;

}

/**********/
void ILM_PRN(ILM *IL)
{
    //Print number obtained by popping the top of the expression stack.

    int val = 0;

    IL->AESTK_SP--;
    
    val = IL->AESTK[IL->AESTK_SP];

    printf("%d",val);

    IL->PC++;
}

/**********/
void ILM_SPC(ILM *IL)
{
    //Insert spaces, to move the print head to next zone.

    printf(" ");

    IL->PC++;
}

/**********/
void ILM_NLINE(ILM *IL)
{
    //Output CRLF to Printer.

    printf("\n");

    IL->PC++;
}

/**********/
void ILM_NXT(ILM *IL)
{
    //If the present mode is direct (line number zero), then return to line collection. 
    //Otherwise, select the next line and begin interpretation.
    
    int i = 0;
    int next_line = 0;

    if(IL->VMODE==0){ IL->PC = ILM_COLLECTOR_POINT; IL->CURSOR=0; }
    else if(IL->VMODE==1)
    { 
        next_line = 0;

        for(i=IL->CURSOR_LINE+1;i<MAX_LINES;i++)
        {
            if( !ILM_line_isempty(IL->LINES[i])) { next_line = i; break; }
        }

        if(next_line==0)
        {
            IL->VMODE=0;
            IL->PC = ILM_COLLECTOR_POINT; 
            IL->CURSOR=0;
        }
        else
        {
            IL->CURSOR_LINE = next_line;
            IL->CURSOR = 0;
            IL->PC = ILM_EXECUTOR_POINT; 
        }
    }
}

/**********/
void ILM_XFER(ILM *IL)
{
    //Test valiue at the top of the AE stack to be within range. ( SHOULD I POP IT ??? )
    //If not, report an error. 
    //If so, attempt to position cursor at that line. 
    //If it exists, begin interpretation there; if not report an error.

    int val = 0;

    IL->AESTK_SP--;
    
    val = IL->AESTK[IL->AESTK_SP];

    if(val>0 && val<AESTK_SIZE)
    {
        if(!ILM_line_isempty(IL->LINES[val]))
        {
            IL->CURSOR = 0;
            IL->CURSOR_LINE = val;
            IL->PC = ILM_EXECUTOR_POINT;
        }
        else
        {
            ILM_error(IL,"Error code 4"); return;
        }
    }
    else
    {
        ILM_error(IL,"Error code 5"); return;
    }
}

/**********/
void ILM_SAV(ILM *IL)
{
    //Push present line number on SBRSTK. Report overflow as error.

    IL->LINES_STACK[IL->LINES_SP] = IL->CURSOR_LINE;

    IL->LINES_SP++;

    IL->PC++;
}

/**********/
void ILM_RSTR(ILM *IL)
{
    //Replace current line number with value on SBRSTK. 
    //If stack is empty, report error.

    IL->LINES_SP--;

    IL->CURSOR_LINE = IL->LINES_STACK[IL->LINES_SP];

    IL->PC++;
}

/**********/
void ILM_CMPR(ILM *IL)
{
    //Compare AESTK(SP), the top of the stack, with AESTK(SP-2) as per the relations indicated by AESTK(SP-1). 
    //Delete all from stack. 
    //If the condition specified did not match, then perform NXT action.

    //NUMBER      <-- TOP
    //RELATION    <-- TOP - 1
    //NUMBER      <-- TOP - 2

    // RELATION : 
    // 0 =
    // 4 >
    // 1 <
    // 5 >=
    // 2 <=
    // 3 <>

    int a = 0;
    int rel = 0;
    int b = 0;

    IL->AESTK_SP--;
    b = IL->AESTK[IL->AESTK_SP];

    IL->AESTK_SP--;
    rel = IL->AESTK[IL->AESTK_SP];

    IL->AESTK_SP--;
    a = IL->AESTK[IL->AESTK_SP];

    switch(rel)
    {
        case 0:
            if(a==b) { IL->PC++; }
            else { ILM_NXT(IL); }
            break;

        case 4:
            if(a>b) { IL->PC++; }
            else { ILM_NXT(IL); }
            break;

        case 1:
            if(a<b) { IL->PC++; }
            else { ILM_NXT(IL); }
            break;

        case 5:
            if(a>=b) { IL->PC++; }
            else { ILM_NXT(IL); }
            break;

        case 3:
            if(a!=b) { IL->PC++; }
            else { ILM_NXT(IL); }
            break;

        case 2:
            if(a<=b) { IL->PC++; }
            else { ILM_NXT(IL); }
            break;
        
        default :
            ILM_error(IL, "Error code 6");
            break;
    }

}

/**********/
void ILM_LIT(ILM *IL)
{
    //Push the number num onto the AESTK (Originally omitted)
    
    IL->AESTK[IL->AESTK_SP] = IL->MEM[IL->PC+1];
    
    IL->AESTK_SP++;

    IL->PC += 2;
}

/**********/
void ILM_INNUM(ILM *IL)
{
    //Read a number from the terminal and push its value onto the AESTK. 

    int val = 0;

    printf("<");

    scanf("%d",&val);

    IL->AESTK[IL->AESTK_SP] = val;

    IL->AESTK_SP++;

    IL->PC++;
}

/**********/
void ILM_FIN(ILM *IL)
{
    //Return to the line collect routine.
    IL->CURSOR = 0;

    IL->CURSOR_LINE = 0;

    IL->PC = ILM_COLLECTOR_POINT;

    IL->VMODE = 0;
}

/**********/
void ILM_ERR(ILM *IL)
{
    //Report syntax error am return to line collect routine.

    ILM_error(IL,"Syntax error");

    IL->PC = ILM_COLLECTOR_POINT;
}

/**********/
void ILM_ADD(ILM *IL)
{
    //Replace top two elements of AESTK by their sum.

    int a = 0;
    int b = 0;

    IL->AESTK_SP--;
    a = IL->AESTK[IL->AESTK_SP];

    IL->AESTK_SP--;
    b = IL->AESTK[IL->AESTK_SP];

    IL->AESTK[IL->AESTK_SP] = a + b;

    IL->AESTK_SP++;

    IL->PC++;

}

/**********/
void ILM_SUB(ILM *IL)
{
    //Replace top two elements of AESTK by their difference.

    int a = 0;
    int b = 0;

    IL->AESTK_SP--;
    a = IL->AESTK[IL->AESTK_SP];

    IL->AESTK_SP--;
    b = IL->AESTK[IL->AESTK_SP];

    IL->AESTK[IL->AESTK_SP] = b - a;

    IL->AESTK_SP++;

    IL->PC++;
}

/**********/
void ILM_NEG(ILM *IL)
{
    //Replace top of AESTK with its neqative.

    IL->AESTK[IL->AESTK_SP-1] *= -1;

    IL->PC++; 
}

/**********/
void ILM_MUL(ILM *IL)
{
    //Replace top two elements of AESTK by their product.

    int a = 0;
    int b = 0;

    IL->AESTK_SP--;
    a = IL->AESTK[IL->AESTK_SP];

    IL->AESTK_SP--;
    b = IL->AESTK[IL->AESTK_SP];

    IL->AESTK[IL->AESTK_SP] = a * b;

    IL->AESTK_SP++;

    IL->PC++;
}

/**********/
void ILM_DIV(ILM *IL)
{
    //Replace top two elements of AESTK by their quotient.

    int a = 0;
    int b = 0;

    IL->AESTK_SP--;
    a = IL->AESTK[IL->AESTK_SP];

    IL->AESTK_SP--;
    b = IL->AESTK[IL->AESTK_SP];

    IL->AESTK[IL->AESTK_SP] = b / a;

    IL->AESTK_SP++;

    IL->PC++;
}

/**********/
void ILM_STORE(ILM *IL)
{
    //Place the value at the top of the AESTK into the variable designated by the index specified by the value immediately below it. 
    //Delete both from the stack.

    int val = 0;
    int var_index = 0;

    IL->AESTK_SP--;
    val = IL->AESTK[IL->AESTK_SP];

    IL->AESTK_SP--;
    var_index = IL->AESTK[IL->AESTK_SP];

    IL->VARIABLES[var_index] = val ;

    IL->PC++;
}

/**********/
void ILM_TSTV(ILM *IL)
{
    //Test for variable (i.e letter) if present.
    //Place its index value onto the AESTK and continue execution at next suggested location. 
    //Otherwise continue at lbl.

    if(ILM_skip_spaces(IL)<0) { ILM_error(IL, "Error code 7"); return; }

    if( (int)IL->LINES[IL->CURSOR_LINE][IL->CURSOR]>=65 &&  (int)IL->LINES[IL->CURSOR_LINE][IL->CURSOR]<=90 )
    {     
        IL->AESTK[IL->AESTK_SP] = (int)IL->LINES[IL->CURSOR_LINE][IL->CURSOR]-VARIABLE_OFFSET;

        IL->CURSOR++;

        IL->AESTK_SP++;

        IL->PC += 3;
    }
    else
    {
        IL->PC = (IL->MEM[IL->PC+1] << 8 ) + IL->MEM[IL->PC+2];
    }
}

/**********/
void ILM_TSTN(ILM *IL)
{
    //Test for number. 
    //If present, place its value onto the AESTK and continue execution at next suggested location. 
    //Otherwise continue at lbl.

    int start = 0;
    int end = 0;
    uint8_t *token = 0;

    if(ILM_skip_spaces(IL)<0) { ILM_error(IL, "Error code 8"); return; }
    start = IL->CURSOR;

    if(ILM_read_until_is_digit(IL)<0) { ILM_error(IL, "Error code 9"); return; }
    end = IL->CURSOR;

    token = calloc(end-start+1,sizeof(uint8_t));
    memcpy(token,IL->LINES[IL->CURSOR_LINE] + start, end-start);

    if(ILM_line_isnumber(token))
    {
        IL->AESTK[IL->AESTK_SP] = atoi(token);

        IL->AESTK_SP++;

        IL->PC += 3;
    }
    else
    {
        IL->CURSOR = start;

        IL->PC = (IL->MEM[IL->PC+1] << 8 ) + IL->MEM[IL->PC+2];
    }

    free(token);
    
}

/**********/
void ILM_IND(ILM *IL)
{
    //Replace top of AEstack by variable value it indexes.

    IL->AESTK[IL->AESTK_SP-1] = IL->VARIABLES[IL->AESTK[IL->AESTK_SP-1]];

    IL->PC++;
}

/**********/
void ILM_LST(ILM *IL)
{
    //List the contents of the program area.

    int i = 0;

    for(i=1;i<MAX_LINES;i++)
    {
        if(!ILM_line_isempty(IL->LINES[i])) { printf("%02d %s", i, IL->LINES[i]); }
    }

    IL->PC++;
}

/**********/
void ILM_INIT(ILM *IL)
{
    //Perform global initilization
    //Clears program area, empties GOSUB stack, etc.

    ILM_reset(IL);

    IL->PC++;
}

/**********/
void ILM_GETLINE(ILM *IL)
{
    //Input a line to LBUF.

    ILM_line_clear(IL->LBUF);

    fgets(IL->LBUF, LINE_SIZE, stdin); 

    if( ILM_line_isempty(IL->LBUF) ) { return; } //trick to avoid empty lines

    IL->CURSOR_LINE = 0;

    IL->CURSOR = 0;

    IL->PC++;
}

/**********/
void ILM_TSTL(ILM *IL)
{
    //After editing leading blanks, look for a line number. 
    //Report error if invalid; transfer to lbl if not present.

    int val = 0;
    uint8_t *start = NULL;
    uint8_t *end = NULL;
    uint8_t *token = NULL;

    start = ILM_line_skipspaces(IL->LBUF);
    if(start==NULL){ ILM_error(IL,"Error code 10"); return; }

    end = ILM_line_tokenend(start);
    if(end==NULL){ ILM_error(IL,"Error code 11"); return;}

    token = calloc(end-start+1,sizeof(uint8_t));
    memcpy(token,start,end-start);
    
    if(ILM_line_isnumber(token))
    {
        val = atoi(token);

        if(val>0 && val<MAX_LINES)//is line number valid ?
        {
            IL->PC += 3;
        }
        else
        {
            free(token);
            ILM_error(IL,"Error code 12"); 
            return;
        }
    }
    else //no line number, PUT LBUF IT IN LINE[0],SET CURSOR LINE 0 and go to label
    {
        memcpy(IL->LINES[0], IL->LBUF, LINE_SIZE);

        IL->CURSOR_LINE = 0;

        IL->CURSOR = 0;        

        IL->PC = (IL->MEM[IL->PC+1] << 8 ) + IL->MEM[IL->PC+2];
    }

    free(token);
}

/**********/
void ILM_INSRT(ILM *IL)
{
    //Insert line after deleting any line with same line number.

    int val = 0;
    uint8_t *start = NULL;
    uint8_t *end = NULL;
    uint8_t *token = NULL;

    start = ILM_line_skipspaces(IL->LBUF);
    if(start==NULL){ ILM_error(IL,"Error code 13"); return; }

    end = ILM_line_tokenend(start);
    if(end==NULL){ ILM_error(IL,"Error code 14"); return; }

    token = calloc(end-start+1,sizeof(uint8_t));
    memcpy(token,start,end-start);
    
    if(strlen(token)==0){ free(token); ILM_error(IL,"Error code 15"); return; }

    if(ILM_line_isnumber(token))
    {
        val = atoi(token);

        if(val>=1 && val < MAX_LINES)//is line number valid ?
        {
            ILM_line_clear(IL->LINES[val]);

            start = ILM_line_skipblanks(end);

            if(start!=NULL)
            {
                memcpy(IL->LINES[val], start,strlen((char *)start));
            }

            IL->PC++;
        }
        else
        {
            free(token);
            ILM_error(IL,"Error code 16");
            return;
        }
    }
    else //no line number
    {
        free(token);
        ILM_error(IL,"Error code 17");
        return;
    }

    free(token);
}

/**********/
void ILM_XINIT(ILM *IL)
{
    //Perform initialization for each stated execution. Empties AEXP stack.

    int i = 0;

    IL->AESTK_SP = 0x00;
    
    for(i=0;i<AESTK_SIZE;i++)
    {
        IL->AESTK[i] = 0x00;
    } 

    IL->PC++;
}

/**********/
void ILM_MODE(ILM *IL)
{
    //ADDED BY ME :
    //read the next byte and set it to the VMODE (virtual machine mode)
    //MODE : 0 = direct, 1 = run, 2 = exit

    int i = 0;

    if(IL->VMODE==0 && IL->MEM[IL->PC+1]==1)
    {
        for(i=0;i<VARIABLES_SIZE;i++)
        {
            IL->VARIABLES[i] = 0x00;
        } 
    }

    IL->VMODE = IL->MEM[IL->PC+1];    

    IL->PC += 2;
}
