    .global DeleteContinue
    .type DeleteContinue, @function

DeleteContinue:
    li $v0, 0x10
    beq $v0,$s0, SkipSpawn
    li $v0, 0xD
    beq $v0, $s0, SkipSpawn
    nop
    j 0x80105770 /*GetMiscObject*/
SkipSpawn:
    li $v0, 0x0
    j $ra
