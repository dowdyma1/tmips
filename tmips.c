/*
 * Matthew Dowdy
 * CDA3103C
 * 07/16/20
 * Project
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LW 1
#define ADD 2
#define SW 3
#define SUB 4
#define SIO1 5
#define SIO2 6
#define SIO3 7
#define JMP 8
#define BEQZ 9

#define MAXPROGSIZE 500
#define MAXDATASIZE 16
#define MAXREGISTERS 8

typedef struct {
    int opcode, rx, ry, rz;
} instruction;


// helper fn to get string representation of opcodes
char* opcode_to_str(int opcode) {
    if(opcode == 1){return "lw  ";}
    if(opcode == 2){return "add ";}
    if(opcode == 3){return "sw  ";}
    if(opcode == 4){return "sub ";}
    if(opcode == 5){return "sio1";}
    if(opcode == 6){return "sio2";}
    if(opcode == 7){return "halt";}
    if(opcode == 8){return "jmp ";}
    if(opcode == 9){return "beqz";}
}

// helper fn to print array given the array and size
void print_arr(int *arr, int size){
    printf("[");
    for(int i = 0; i < size; i++){
        printf("%d", arr[i]);
        if(i != size-1){printf(" ");}
    }
    printf("]");

    return;
}

void print_assembly(instruction inst){
    printf("%s %d %d %d\n", opcode_to_str(inst.opcode),
            inst.rx, inst.ry, inst.rz);

    return;
}

// prototype functions for each pipeline
int *instruct_fetch(instruction* im, int *pc);
int* inst_decode_op_fetch(int ifid[4], int *rf, int *pc);
int* execute(int idex[4]);
int* data_mem(int exdm[4], int *dm);
void write_back(int dmwb[4], int* rf);


int main(int argc, char *argv[]){
    // instruction memory array
    instruction im[MAXPROGSIZE];

    // program counter
    int *pc = (int*)malloc(sizeof(int));
    *pc = 0;

    // data memory array
    int *dm = (int*)malloc(MAXDATASIZE * sizeof(int));
    // register file array
    int *reg_file = (int*)malloc(MAXREGISTERS * sizeof(int));

    // zero out buffer arrays & initialize
    int temp_ifid[] = {0,0,0,0};
    int t_idex[] = {0,0,0,0};
    int t_exdm[] = {0,0,0,0};
    int t_dmwb[] = {0,0,0,0};
    int* ifid;
    int* idex;
    int* exdm;
    int* dmwb;
    ifid = temp_ifid;
    idex = t_idex; 
    exdm = t_exdm;
    dmwb = t_dmwb;

    // file pointer
    FILE * ifp;
    ifp = fopen(argv[1], "r");

    int i = 0;
    // while we haven't finished reading the file...
    while(feof(ifp) != 1){
        // read the numbers 4 at a time & set to im position
        fscanf(ifp, "%d %d %d %d ", 
                &im[i].opcode, &im[i].rx, &im[i].ry, &im[i].rz);
        i++;
        }

        printf("Assembling program...\n");
        for(int j = 0; j < i; j++){
            print_assembly(im[j]);
        }
        printf("Program Assembled.\n");
    fclose(ifp);

    // initial print sequence, at PC=0
    printf("PC = %d | RF = ", *pc*4);
    print_arr(reg_file, MAXREGISTERS);
    printf(" | \nDM = ");
    print_arr(dm, MAXDATASIZE);
    printf(" IFID = ");
    print_arr(ifid, 4);
    printf(" | \nIDEX = ");
    print_arr(idex, 4);
    printf(" | EXDM = ");
    print_arr(exdm, 4);
    printf(" | DMWB = ");
    print_arr(dmwb, 4);
    printf("\n\n");

    // while the last buffer opcode isn't halt
    while(dmwb[0] != SIO3){
        print_assembly(im[*pc]);
        
        // whole pipeline
        ifid = instruct_fetch(im, pc);
        idex = inst_decode_op_fetch(ifid, reg_file, pc);
        exdm = execute(idex);
        dmwb = data_mem(exdm, dm);
        write_back(dmwb, reg_file);

        
        // print readout
        printf("PC = %d | RF = ", *pc*4);
        print_arr(reg_file, MAXREGISTERS);
        printf(" | \nDM = ");
        print_arr(dm, MAXDATASIZE);
        printf(" IFID = ");
        print_arr(ifid, 4);
        printf(" | \nIDEX = ");
        print_arr(idex, 4);
        printf(" | EXDM = ");
        print_arr(exdm, 4);
        printf(" | DMWB = ");
        print_arr(dmwb, 4);
        printf("\n\n");
    }

    
    // free dynamic memory
    free(pc);
    free(reg_file);
    free(dm);

    return 0;
}


// input: IM | output: IFID
int *instruct_fetch(instruction* im, int *pc){
    int mar1 = *pc;
    *pc = *pc + 1;
    
    instruction ir;
    ir.opcode = im[mar1].opcode;
    ir.rx = im[mar1].rx;
    ir.ry = im[mar1].ry;
    ir.rz = im[mar1].rz;

    static int ifid[4];
    ifid[0] = ir.opcode;
    ifid[1] = ir.rx;
    ifid[2] = ir.ry;
    ifid[3] = ir.rz;

    if(ir.opcode == JMP){
        // internal pc has 1 for every 4 printed ticks
        // because of the use of struct for IM
        *pc = (int)(ir.rz/4);
    }

    return ifid;
}


// input: IFID | output: IDEX
int* inst_decode_op_fetch(int ifid[4], int *rf, int *pc){
    int idcu, idx, idy, idz, v1, v2;
    static int idex[4];

    idcu = ifid[0];
    idx = ifid[1];
    idy = ifid[2];
    idz = ifid[3];

    idex[0] = idcu;

    // passthrough
    if(idcu == LW || idcu == SIO1 || idcu == SIO3 || idcu == JMP){
        idex[1] = idx;
        idex[2] = idy;
        idex[3] = idz;
    }
    else if(idcu == ADD || idcu == SUB){
        v1 = rf[idy];
        v2 = rf[idz];
        idex[1] = idx;
        idex[2] = v1;
        idex[3] = v2;
    }
    else if(idcu == SW || idcu == SIO2){
        v1 = rf[idx];
        idex[1] = v1;
        idex[2] = idy;
        if(idcu == SIO2){idex[3]=0;}
        else{idex[3]=idz;}
    }
    else if(idcu == BEQZ && idx == 0){
        v1 = rf[idx];
        if(v1 == 0){ // if the value of R0 is 0
            *pc = *pc + 1;
        }
        idex[1] = idx;
        idex[2] = idy;
        idex[3] = idz;
    }

    return idex;
}

// input: IDEX | output: EXDM
int* execute(int idex[4]){
    int excu, exx, exy, exz, value3, input;
    static int exdm[4];

    excu = idex[0];
    exx = idex[1];
    exy = idex[2];
    exz = idex[3];

    exdm[0] = excu;
    exdm[1] = exx;

    // passthrough
    if(excu == LW || excu == SW || excu == JMP || excu == BEQZ){
        exdm[2] = exy;
        exdm[3] = exz;
    }
    else if(excu == ADD){
        value3 = exy + exz;

        exdm[2] = 0;
        exdm[3] = value3;
    }
    else if(excu == SUB){
        value3 = exy - exz;

        exdm[2] = 0;
        exdm[3] = value3;
    }
    else if(excu == SIO1){
        scanf("%d", &input);

        exdm[2] = exy;
        exdm[3] = input;
    }
    else if(excu == SIO2){
        printf("\nOUTPUT: %d\n\n",exdm[1]);

        exdm[2] = exy;
        exdm[3] = exz;
    }
    else if(excu == SIO3){
        printf("end of program\n"); // actual halting taken care of in main
    }

    return exdm;
}

// input: EXDM | output: DMWB
int* data_mem(int exdm[4], int* dm){
    int dmcu, dmx, dmy, dmz, v1;
    static int dmwb[4];

    dmcu = exdm[0];
    dmx = exdm[1];
    dmy = exdm[2];
    dmz = exdm[3];

    dmwb[0] = dmcu;
    dmwb[1] = dmx;
    dmwb[2] = dmy;

    // passthrough
    if(dmcu == ADD || dmcu == SUB || dmcu == SIO1 || dmcu == SIO2 ||
            dmcu == SIO3 || dmcu == JMP || dmcu == BEQZ){
        dmwb[3] = dmz;
    }
    else if(dmcu == LW){
        int mar2;
        mar2 = dmz;
        v1 = dm[mar2];
        dmwb[3] = v1;
    }
    else if(dmcu == SW){
        int mar2;
        mar2 = dmz;
        dm[mar2] = dmx;
        dmwb[3] = mar2;
    }

    return dmwb;
}

// input: DMWB | output: void
void write_back(int dmwb[4], int* rf){
    int wbcu, wbx, wby, wbz;

    wbcu = dmwb[0];
    wbx = dmwb[1];
    wby = dmwb[2];
    wbz = dmwb[3];

    if(wbcu == ADD || wbcu == SUB || wbcu == LW || wbcu == SIO1){
        rf[wbx] = wbz;
    }

    return;
}
