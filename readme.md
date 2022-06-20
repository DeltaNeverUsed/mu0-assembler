
# mu0 Assembler
This is an mu0 Assembler i created for my [VRC mu0 Avatar](https://github.com/DeltaNeverUsed/VRC-mu0-Avatar)

## Usage

if the output file is not specified it'll output to "o.lst"

Basic Usage 
``assembler.exe [input file] [output file]``
```asm
.Start
    jmp Mul
    lda result
    sto variable_b
    jmp Start

.Mul
    lda result ; This is a comment
    add variable_a
    sto result

    lda variable_b
    sub one
    sto variable_b
    jne Mul
    jmp Start+1

.one
    1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ; most of this is padding but can be accessed by doing one+1, one+2, one+3, etc
.variable_a 
    0x2
.variable_b
    0x1
.result
    0x0
```

Here's an example of what the output would look like using "test.asm" 

```asm
PS C:\Users\Sinus\Desktop\mu0 assembler> ./assembler.exe test.asm
4 004
0 01D
1 01B
4 000
0 01D
2 01B
1 01D
0 01B
3 00C
1 01B
6 004
4 001
0001
0000
0000
0000
0000
0000
0000
0000
0000
0000
0000
0000
0000
0000
0000
0002
0001
0000
```
