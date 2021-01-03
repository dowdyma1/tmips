# Introduction
This project is a simulator for a smaller version of the MIPS instruction
set architecture. It takes in assembly as input and runs each instruction
through the simulated pipeline.

This project was completed in July of 2020 for my Computer Logic and Organization class.
It was a fun project to see how the MIPS datapath works on a basic level.

## How it works
There are 5 stages in this pipeline (from start to end):
* Instruction Fetch
* Instruction Decode/OP Fetch
* Execute
* Data memory
* Writeback

between each stage, there is a register which passes pertinent data from
one stage to the next.

![Datapath](/images/datapath.png)

## OP codes
```
1 -- LW
2 -- ADD
3 -- SW
4 -- SUB
5 -- SIO1 (input)
6 -- SIO2 (output)
7 -- SIO3 (eop)
8 -- JMP
9 -- BEQZ (branch on 0)
```

# How to run the program
```
make program
./prog <text file>
```

There are two premade assembly programs: add.txt and mult.txt.
They each do what you think they would, add.txt adds two numbers
and mult.txt multiplies two numbers.

## Instructions for mult.txt
```
1st input: first number to multiply
2nd input: second number to multiply
3rd input: just type the number 1

You will see 'OUTPUT:' <product of the first two inputs>
```

## Instructions for add.txt
```
1st input: first number to add
2nd input: second number to add

You will see 'OUTPUT:' <sum>
```

# Example Output
```
./prog mult.txt
```
```
Assembling program...
sio1 1 0 5
sio1 0 0 5
sio1 2 0 5
sub  0 0 2
add  3 1 3
beqz 0 0 0
jmp  0 0 12
sw   3 0 0
lw   0 0 0
sio2 0 0 9
halt 0 0 0
Program Assembled.
PC = 0 | RF = [0 0 0 0 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [0 0 0 0] |
IDEX = [0 0 0 0] | EXDM = [0 0 0 0] | DMWB = [0 0 0 0]

sio1 1 0 5
5
PC = 4 | RF = [0 5 0 0 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [5 1 0 5] |
IDEX = [5 1 0 5] | EXDM = [5 1 0 5] | DMWB = [5 1 0 5]

sio1 0 0 5
8
PC = 8 | RF = [8 5 0 0 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [5 0 0 5] |
IDEX = [5 0 0 5] | EXDM = [5 0 0 8] | DMWB = [5 0 0 8]

sio1 2 0 5
1
PC = 12 | RF = [8 5 1 0 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [5 2 0 5] |
IDEX = [5 2 0 5] | EXDM = [5 2 0 1] | DMWB = [5 2 0 1]

sub  0 0 2
PC = 16 | RF = [7 5 1 0 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [4 0 0 2] |
IDEX = [4 0 8 1] | EXDM = [4 0 0 7] | DMWB = [4 0 0 7]

add  3 1 3
PC = 20 | RF = [7 5 1 5 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [2 3 1 3] |
IDEX = [2 3 5 0] | EXDM = [2 3 0 5] | DMWB = [2 3 0 5]

beqz 0 0 0
PC = 24 | RF = [7 5 1 5 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [9 0 0 0] |
IDEX = [9 0 0 0] | EXDM = [9 0 0 0] | DMWB = [9 0 0 0]

jmp  0 0 12
PC = 12 | RF = [7 5 1 5 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [8 0 0 12] |
IDEX = [8 0 0 12] | EXDM = [8 0 0 12] | DMWB = [8 0 0 12]

sub  0 0 2
PC = 16 | RF = [6 5 1 5 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [4 0 0 2] |
IDEX = [4 0 7 1] | EXDM = [4 0 0 6] | DMWB = [4 0 0 6]

add  3 1 3
PC = 20 | RF = [6 5 1 10 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [2 3 1 3] |
IDEX = [2 3 5 5] | EXDM = [2 3 0 10] | DMWB = [2 3 0 10]

beqz 0 0 0
PC = 24 | RF = [6 5 1 10 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [9 0 0 0] |
IDEX = [9 0 0 0] | EXDM = [9 0 0 0] | DMWB = [9 0 0 0]

jmp  0 0 12
PC = 12 | RF = [6 5 1 10 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [8 0 0 12] |
IDEX = [8 0 0 12] | EXDM = [8 0 0 12] | DMWB = [8 0 0 12]

sub  0 0 2
PC = 16 | RF = [5 5 1 10 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [4 0 0 2] |
IDEX = [4 0 6 1] | EXDM = [4 0 0 5] | DMWB = [4 0 0 5]

add  3 1 3                                                                                                                                             [93/558]
PC = 20 | RF = [5 5 1 15 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [2 3 1 3] |
IDEX = [2 3 5 10] | EXDM = [2 3 0 15] | DMWB = [2 3 0 15]

beqz 0 0 0
PC = 24 | RF = [5 5 1 15 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [9 0 0 0] |
IDEX = [9 0 0 0] | EXDM = [9 0 0 0] | DMWB = [9 0 0 0]

jmp  0 0 12
PC = 12 | RF = [5 5 1 15 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [8 0 0 12] |
IDEX = [8 0 0 12] | EXDM = [8 0 0 12] | DMWB = [8 0 0 12]

sub  0 0 2
PC = 16 | RF = [4 5 1 15 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [4 0 0 2] |
IDEX = [4 0 5 1] | EXDM = [4 0 0 4] | DMWB = [4 0 0 4]

add  3 1 3
PC = 20 | RF = [4 5 1 20 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [2 3 1 3] |
IDEX = [2 3 5 15] | EXDM = [2 3 0 20] | DMWB = [2 3 0 20]

beqz 0 0 0
PC = 24 | RF = [4 5 1 20 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [9 0 0 0] |
IDEX = [9 0 0 0] | EXDM = [9 0 0 0] | DMWB = [9 0 0 0]

jmp  0 0 12
PC = 12 | RF = [4 5 1 20 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [8 0 0 12] |
IDEX = [8 0 0 12] | EXDM = [8 0 0 12] | DMWB = [8 0 0 12]

sub  0 0 2
PC = 16 | RF = [3 5 1 20 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [4 0 0 2] |
IDEX = [4 0 4 1] | EXDM = [4 0 0 3] | DMWB = [4 0 0 3]

add  3 1 3
PC = 20 | RF = [3 5 1 25 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [2 3 1 3] |
IDEX = [2 3 5 20] | EXDM = [2 3 0 25] | DMWB = [2 3 0 25]

beqz 0 0 0                                                                                                                                             [48/558]
PC = 24 | RF = [3 5 1 25 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [9 0 0 0] |
IDEX = [9 0 0 0] | EXDM = [9 0 0 0] | DMWB = [9 0 0 0]

jmp  0 0 12
PC = 12 | RF = [3 5 1 25 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [8 0 0 12] |
IDEX = [8 0 0 12] | EXDM = [8 0 0 12] | DMWB = [8 0 0 12]

sub  0 0 2
PC = 16 | RF = [2 5 1 25 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [4 0 0 2] |
IDEX = [4 0 3 1] | EXDM = [4 0 0 2] | DMWB = [4 0 0 2]

add  3 1 3
PC = 20 | RF = [2 5 1 30 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [2 3 1 3] |
IDEX = [2 3 5 25] | EXDM = [2 3 0 30] | DMWB = [2 3 0 30]

beqz 0 0 0
PC = 24 | RF = [2 5 1 30 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [9 0 0 0] |
IDEX = [9 0 0 0] | EXDM = [9 0 0 0] | DMWB = [9 0 0 0]

jmp  0 0 12
PC = 12 | RF = [2 5 1 30 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [8 0 0 12] |
IDEX = [8 0 0 12] | EXDM = [8 0 0 12] | DMWB = [8 0 0 12]

sub  0 0 2
PC = 16 | RF = [1 5 1 30 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [4 0 0 2] |
IDEX = [4 0 2 1] | EXDM = [4 0 0 1] | DMWB = [4 0 0 1]

add  3 1 3
PC = 20 | RF = [1 5 1 35 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [2 3 1 3] |
IDEX = [2 3 5 30] | EXDM = [2 3 0 35] | DMWB = [2 3 0 35]

beqz 0 0 0
PC = 24 | RF = [1 5 1 35 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [9 0 0 0] |
IDEX = [9 0 0 0] | EXDM = [9 0 0 0] | DMWB = [9 0 0 0]

jmp  0 0 12                                                                                                                                             [3/558]
PC = 12 | RF = [1 5 1 35 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [8 0 0 12] |
IDEX = [8 0 0 12] | EXDM = [8 0 0 12] | DMWB = [8 0 0 12]

sub  0 0 2
PC = 16 | RF = [0 5 1 35 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [4 0 0 2] |
IDEX = [4 0 1 1] | EXDM = [4 0 0 0] | DMWB = [4 0 0 0]

add  3 1 3
PC = 20 | RF = [0 5 1 40 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [2 3 1 3] |
IDEX = [2 3 5 35] | EXDM = [2 3 0 40] | DMWB = [2 3 0 40]

beqz 0 0 0
PC = 28 | RF = [0 5 1 40 0 0 0 0] |
DM = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [9 0 0 0] |
IDEX = [9 0 0 0] | EXDM = [9 0 0 0] | DMWB = [9 0 0 0]

sw   3 0 0
PC = 32 | RF = [0 5 1 40 0 0 0 0] |
DM = [40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [3 3 0 0] |
IDEX = [3 40 0 0] | EXDM = [3 40 0 0] | DMWB = [3 40 0 0]

lw   0 0 0
PC = 36 | RF = [40 5 1 40 0 0 0 0] |
DM = [40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [1 0 0 0] |
IDEX = [1 0 0 0] | EXDM = [1 0 0 0] | DMWB = [1 0 0 40]

sio2 0 0 9

OUTPUT: 40

PC = 40 | RF = [40 5 1 40 0 0 0 0] |
DM = [40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [6 0 0 9] |
IDEX = [6 40 0 0] | EXDM = [6 40 0 0] | DMWB = [6 40 0 0]

halt 0 0 0
end of program
PC = 44 | RF = [40 5 1 40 0 0 0 0] |
DM = [40 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] IFID = [7 0 0 0] |
IDEX = [7 0 0 0] | EXDM = [7 0 0 0] | DMWB = [7 0 0 0]

```
