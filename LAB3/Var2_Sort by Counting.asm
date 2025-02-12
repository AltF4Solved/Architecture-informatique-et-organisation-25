# Data segment for strings and array storage
.data
    promptSize:      .asciiz "Insert the array size\n"
    promptElements:  .asciiz "Insert the array elements, one per line\n"
    outputMsg:       .asciiz "The sorted array is:\n"
    newline:         .asciiz "\n"

.text
.globl main

###############################################################################
# Function: countLessThan
# Arguments:
#   $a0 - array base address
#   $a1 - length
#   $a2 - index i
# Returns:
#   $v0 - count of elements less than a[i]
###############################################################################
countLessThan:
    # Save registers
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $s0, 12($sp)
    sw   $s1, 8($sp)
    sw   $s2, 4($sp)
    sw   $s3, 0($sp)
    
    # Initialize variables
    move $s0, $zero        # count = 0
    move $s1, $zero        # j = 0
    move $s2, $a0          # save array address
    move $s3, $a2          # save i
    
    # Load a[i] into $t2
    sll  $t0, $a2, 2
    add  $t0, $s2, $t0
    lw   $t2, 0($t0)      # t2 = a[i]
    
count_loop:
    beq  $s1, $a1, end_count    # if j == length, exit loop
    
    # Load a[j]
    sll  $t0, $s1, 2
    add  $t0, $s2, $t0
    lw   $t1, 0($t0)          # t1 = a[j]
    
    # Check if a[j] < a[i]
    bge  $t1, $t2, check_equal
    addi $s0, $s0, 1          # count++
    j    next_count
    
check_equal:
    bne  $t1, $t2, next_count  # if a[j] != a[i], skip
    bge  $s3, $s1, next_count  # if i >= j, skip
    addi $s0, $s0, 1           # count++
    
next_count:
    addi $s1, $s1, 1           # j++
    j    count_loop
    
end_count:
    # Return count in $v0
    move $v0, $s0
    
    # Restore registers
    lw   $ra, 16($sp)
    lw   $s0, 12($sp)
    lw   $s1, 8($sp)
    lw   $s2, 4($sp)
    lw   $s3, 0($sp)
    addi $sp, $sp, 20
    
    jr   $ra

###############################################################################
# Function: sortByCounting
# Arguments:
#   $a0 - array base address
#   $a1 - length
# Returns: void
###############################################################################
sortByCounting:
    # Save registers
    addi $sp, $sp, -28
    sw   $ra, 24($sp)
    sw   $s0, 20($sp)
    sw   $s1, 16($sp)
    sw   $s2, 12($sp)
    sw   $s3, 8($sp)
    sw   $s4, 4($sp)
    sw   $s5, 0($sp)
    
    # Initialize variables
    move $s0, $a0          # save array address
    move $s1, $a1          # save length
    
    # Allocate memory for array b
    sll  $a0, $a1, 2      # length * 4
    li   $v0, 9           # sbrk syscall
    syscall
    move $s2, $v0         # s2 = b array address
    
    # First loop: fill array b
    move $s3, $zero       # i = 0
fill_loop:
    beq  $s3, $s1, copy_loop_init   # if i == length, exit loop
    
    # Call countLessThan
    move $a0, $s0         # array address
    move $a1, $s1         # length
    move $a2, $s3         # i
    jal  countLessThan
    move $s4, $v0         # s4 = lessThan
    
    # b[lessThan] = a[i]
    sll  $t0, $s3, 2
    add  $t0, $s0, $t0
    lw   $t1, 0($t0)      # t1 = a[i]
    
    sll  $t0, $s4, 2
    add  $t0, $s2, $t0
    sw   $t1, 0($t0)      # b[lessThan] = a[i]
    
    addi $s3, $s3, 1      # i++
    j    fill_loop
    
    # Second loop: copy back to array a
copy_loop_init:
    move $s3, $zero       # i = 0
copy_loop:
    beq  $s3, $s1, end_sort   # if i == length, exit loop
    
    # a[i] = b[i]
    sll  $t0, $s3, 2
    add  $t1, $s2, $t0
    add  $t2, $s0, $t0
    lw   $t3, 0($t1)
    sw   $t3, 0($t2)
    
    addi $s3, $s3, 1      # i++
    j    copy_loop
    
end_sort:
    # Restore registers
    lw   $ra, 24($sp)
    lw   $s0, 20($sp)
    lw   $s1, 16($sp)
    lw   $s2, 12($sp)
    lw   $s3, 8($sp)
    lw   $s4, 4($sp)
    lw   $s5, 0($sp)
    addi $sp, $sp, 28
    
    jr   $ra

###############################################################################
# Main function
###############################################################################
main:
    # Save $ra
    addi $sp, $sp, -4
    sw   $ra, 0($sp)
    
    # Print prompt for array size
    li   $v0, 4
    la   $a0, promptSize
    syscall
    
    # Read array size
    li   $v0, 5
    syscall
    move $s0, $v0              # s0 = length
    
    # Allocate array memory
    sll  $a0, $s0, 2          # length * 4
    li   $v0, 9               # sbrk syscall
    syscall
    move $s1, $v0             # s1 = array base address
    
    # Print prompt for elements
    li   $v0, 4
    la   $a0, promptElements
    syscall
    
    # Read array elements
    move $s2, $zero           # i = 0
read_loop:
    beq  $s2, $s0, end_read   # if i == length, exit loop
    
    # Read integer
    li   $v0, 5
    syscall
    
    # Store in array
    sll  $t0, $s2, 2
    add  $t0, $s1, $t0
    sw   $v0, 0($t0)
    
    addi $s2, $s2, 1          # i++
    j    read_loop
end_read:

    # Call sortByCounting
    move $a0, $s1             # array address
    move $a1, $s0             # length
    jal  sortByCounting
    
    # Print sorted array message
    li   $v0, 4
    la   $a0, outputMsg
    syscall
    
    # Print sorted array
    move $s2, $zero           # i = 0
print_loop:
    beq  $s2, $s0, end_print  # if i == length, exit loop
    
    # Load and print integer
    sll  $t0, $s2, 2
    add  $t0, $s1, $t0
    lw   $a0, 0($t0)
    li   $v0, 1
    syscall
    
    # Print newline
    li   $v0, 4
    la   $a0, newline
    syscall
    
    addi $s2, $s2, 1          # i++
    j    print_loop
end_print:

    # Restore $ra and return
    lw   $ra, 0($sp)
    addi $sp, $sp, 4
    
    li   $v0, 10              # exit
    syscall
