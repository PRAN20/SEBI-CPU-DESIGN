# SEBI-CPU-DESIGN

## Challenge) Sebi and CPU Design Problem Code: SEBICPU
Add problem to Todo list
Read problem statements in Mandarin Chinese, Bengali, Russian, and Vietnamese as well.
The King of Chefland is a fan of triplets, especially Pythagorean triplets. His son, prince Sebi, designed the first CPU of Chefland.

Nobody wants to argue with the son of the king, so everybody agrees that he is a great hardware designer. However, he forgot a lot of important instructions, like assigning a constant to a register. Chefland is now looking for a programmer who can load some given triplets to registers quickly.

Architecture of Sebi's CPU:

There are four 64-bit registers based on the X64 architecture. These registers are named rax, rbx, rcx and rdx.
Parts of each 64-bit register can be used as smaller registers. For y equal to a, b, c or d, we have the following registers:
eyx: the lower (least significant) 32 bits of ryx
yx: the lower 16 bits of ryx
yl: the lower 8 bits of ryx
yh: the upper 8 bits of yx
The CPU cannot access any memory storage other than these registers.
The CPU supports several instructions based on assembly languages. Each instruction takes one or two registers as operands. Immediate values as operands are not supported. If an instruction takes two operands, they do not have to be distinct.
If an instruction takes two operands, they must have registers with the same width (number of bits). When the operands of an instruction are registers with width b
, the values stored in them are treated as unsigned b
-bit integers.
An instruction on registers with width b
 computes a result ― an unsigned b
-bit integer ― and stores it in the register given as the first operand. In case of overflow or underflow, the result is treated as computed modulo 2b
; all bits outside the first-operand register remain unchanged.
The available one-operand instructions and their results are:
dec reg: reg minus 1
inc reg: reg plus 1
not reg: bitwise NOT of reg
The available two-operand instructions and their results are:
and reg1 reg2: bitwise AND of reg1 and reg2
or reg1 reg2: bitwise OR of reg1 and reg2
xor reg1 reg2: bitwise XOR of reg1 and reg2
shl reg1 reg2: reg1 shifted left by reg2 bits (and inserts reg2 0
-s as the least significant bits)
shr reg1 reg2: reg1 shifted right by reg2 bits (and inserts reg2 0
-s as the most significant bits)
add reg1 reg2: reg1 plus reg2
sub reg1 reg2: reg1 minus reg2
mul reg1 reg2: reg1 multiplied by reg2
div reg1 reg2: reg1 divided by reg2 (integer division)
mod reg1 reg2: reg1 modulo reg2 (remainder of reg1 after division by reg2)
mov reg1 reg2: reg2 (the instruction copies the value of reg2 to reg1)
The only operations where the result could overflow are shl, add, sub, mul, inc and dec. In sub and dec, the result of i−j
 modulo 2b
 for j>i
 is 2b+i−j
. In all other instructions, modulo simply corresponds to discarding all except the least significant b
 bits.
It is not allowed to use the div or mod operation if reg2 contains 0
.
Initially, all four registers contain 0
-s. You are given N
 triplets of 64-bit integers (a1,b1,c1),(a2,b2,c2),…,(aN,bN,cN)
 and you should write a program (a sequence of instructions) such that each triplet appears in the registers at some point during the execution of this program. The order in which they appear does not matter. Formally, for each valid i
, there should be an instruction in your program such that immediately after this instruction is executed, one of the registers contains the value ai
, one contains bi
 and one contains ci
 (the fourth register may contain anything).

## Input
The first line of the input contains a single integer N
.
N
 lines follow. For each i
 (1≤i≤N
), the i
-th of these lines contains three space-separated integers ai
, bi
 and ci
.
## Output
First, print a line containing a single integer P
 ― the number of instructions in your program.
Then, print P
 lines. For each valid i
, the i
-th of these lines should contain the i
-th instruction from your program in the format described above.
## Constraints
N=64
0≤ai,bi,ci<264
 for each valid i
ai≠bi
, bi≠ci
, ai≠ci
 for each valid i
Scoring
If your program attempts to divide anything by zero or compute anything modulo zero, your submission will receive the Wrong Answer verdict.

If P
 exceeds N⋅500
, your submission will also receive the Wrong Answer verdict. Otherwise, the score of your program is equal to P
. Your goal is to minimise this number.

There are ten test files. During the contest, the displayed score will account for exactly three test files. However, if your program gets a non-AC verdict on any test file, your submission's verdict will be non-AC. In other words, an AC verdict denotes that your program runs successfully on all the test files. After the end of the contest, your score will be changed to include the sum of your program's scores over the other 7 test files.

Generation
There are five types of test files and two files of each type.

Type 1: Each triplet is chosen uniformly randomly among all valid triplets.
Type 2: For each valid i
:
ai
 is chosen uniformly randomly among all 64-bit integers which contain at least 25 0-bits and at least 25 1-bits.
bi
 and ci
 are chosen uniformly randomly among all pairs of distinct 64-bit integers which only differs from ai
 in one or two bits.
Type 3: For each valid i
:
If i=1+8k
 for some integer k
, an unsigned integer d
 (1≤d<263
) is chosen uniformly randomly. This integer is used for this triplet and the next seven triplets.
First, ai
 is chosen uniformly randomly; bi=ai+d
 and ci=ai+2d
. If ci≥264
, ai
 is chosen uniformly randomly again and bi
 and ci
 are updated.
This process is repeated until ci<264
.
Type 4:
First, three 64-bit unsigned integers are chosen uniformly randomly and assigned to three registers. The fourth register is unused; we may assume that it does not exist. Consider the following program which generates a list L
:
If L
 contains 9N
 integers, terminate.
Randomly choose two registers in some order. Randomly choose to use the whole registers or their lower 32 bits.
Randomly choose one of the instructions xor, and, or, add or sub and execute it with the chosen registers as operands.
Add the values in the three registers (in a fixed order) to the list L
.
Consider every third element of the list L
. The first three of these integers form the first triplet, the next three form the second triplet and so on.
While any triplet contains two equal elements, this process is repeated and the triplets regenerated.
Type 5:
A 64-bit unsigned integer K
 is chosen uniformly randomly.
Each triplet is chosen uniformly randomly among all valid triplets with sum of all three elements equal to K
.
## Example Input 1
3
255 2 4
1 0 3
2 6 3
## Example Output 1
10
dec al
inc rcx
inc ecx
mov rdx rcx
add rcx rdx
add rcx rdx
mov rbx rcx
div rbx rdx
div rdx rdx
div rcx rax
## Example Input 2
1
18446743995541146810 18446743995541146811 18446743995541146809
## Example Output 2
13
dec ebx
add bx bx
mul rbx rbx
not ebx
sub eax ebx
div ebx eax
mul ebx ebx
sub ebx eax
mul rax rbx
mov rdx rax
dec rax
mov rbx rax
dec rbx
## Explanation
Note that N≠64
 to keep the input short. This constraint holds for all input files.

Example case 1: The 64-bit values stored in the registers (rax, rbx, rcx, rdx) after each instruction is executed are as follows:

dec al                 (255, 0, 0, 0)
inc rcx                (255, 0, 1, 0)
inc ecx                (255, 0, 2, 0)
mov rdx rcx            (255, 0, 2, 2)
add rcx rdx            (255, 0, 4, 2) ― the first triplet appears
add rcx rdx            (255, 0, 6, 2)
mov rbx rcx            (255, 6, 6, 2)
div rbx rdx            (255, 3, 6, 2) ― the third triplet appears
div rdx rdx            (255, 3, 6, 1)
div rcx rax            (255, 3, 0, 1) ― the second triplet 
