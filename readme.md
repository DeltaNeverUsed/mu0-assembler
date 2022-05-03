
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

```
PS C:\Users\Sinus\Desktop\mu0 assembler> ./assembler.exe test.asm
Label: Start at: 0
Label: Mul at: 4
Label: one at: 12
Label: variable_a at: 27      
Label: variable_b at: 28      
Label: result at: 29
line: 0 inst: jmp, addr: 004 offset: 0
line: 1 inst: lda, addr: 01D offset: 0
line: 2 inst: sto, addr: 01C offset: 0
line: 3 inst: jmp, addr: 000 offset: 0
line: 4 inst: lda, addr: 01D offset: 0
line: 5 inst: add, addr: 01B offset: 0
line: 6 inst: sto, addr: 01D offset: 0
line: 7 inst: lda, addr: 01C offset: 0
line: 8 inst: sub, addr: 00C offset: 0
line: 9 inst: sto, addr: 01C offset: 0
line: 10 inst: jne, addr: 004 offset: 0
line: 11 inst: jmp, addr: 000 offset: 1
```
