.Start_r_pos
    lda Pos ; reset Pos if more than 15
    sub Const_15
    jne Start
    jmp Reset_Pos
.Start
    lda Const_lda_Display ; load lda inst for loading board1 into acc
    add Pos ; add the current position to offset the board position
    sto lda_display+2

    add Const_1 ; load the next line
    sto lda_display

.lda_display
    0x0 ; Gets replaced with the lda for the board position
    sto Compare_1
    0x0

    ; check if next number is higher
    sto Compare_0
    sub Compare_1
    ldr 0x0 ; check if carry is high
    jne Swap
    jmp Incr_pos

.Swap ; Swaps display Compare_0 and Compare_1
    lda Const_sto_Display ; load lda inst for loading board1 into acc
    add Pos ; add the current position to offset the board position
    sto Swap_1+1 ; load the current pos

    add Const_1 ; load the next line
    sto Swap_1+3
.Swap_1
    lda Compare_1
    0x0 ; stores Compare_1 to display+pos
    lda Compare_0
    0x0 ; stores Compare_0 to display+pos+1

.Incr_pos
    lda Pos
    add Const_1
    sto Pos
    jmp Start_r_pos

.Reset_Pos
    lda Const_0
    sto Pos
    jmp Start_r_pos

.Const_0
    0
.Const_1
    1
.Const_15
    15

.Compare_temp
    0x0
.Compare_0
    0x0
.Compare_1
    0x0

.Pos
    0

.Const_lda_Display
    lda Display
.Const_sto_Display
    sto Display

.Padding
    0 0 0 0 0 0 0 0 0

.Display 
    0x9bb8 0xd250 0x7642 0x5d0f
    0x9d46 0x730e 0x40d7 0x0afc
    0xbf18 0x38c6 0x6e0c 0xdc84
    0x1726 0x863d 0x6aa9 0x3a35
