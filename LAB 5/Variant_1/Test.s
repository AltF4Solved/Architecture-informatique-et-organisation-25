    j main
ShiftFunction:

    addi $sp, $sp, -4     # allocate space on the stack
    sw   $ra, 0($sp)      # save the return address on the stack
    sra  $t2, $t2, 4      # arithmetic shift right $t2 by x bits and store in $t2
    lw   $ra, 0($sp)      # restore the return address from the stack
    addi $sp, $sp, 4      # deallocate space on the stack
    jr   $ra              # jump to the return address
	
main:

    addi $s0,$0, -12
    addi $s1,$0, -4
    add  $t0,$s0, 0
    add  $t1,$s1, 0
    add $s2,$s1, $s0
    add  $t2,$s2, 0
    jal ShiftFunction
    addi $s0, $t0, 0
    addi $s1, $t1, 0
    addi $s2, $t2, 0

    
