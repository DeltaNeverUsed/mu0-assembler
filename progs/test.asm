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
