# Data segment for strings and array storage
.data
    promptSize:      .asciiz "Insert the array size\n"
    promptElements:  .asciiz "Insert the array elements, one per line\n"
    outputMsg:       .asciiz "The sorted array is:\n"
    newline:         .asciiz "\n"

.text
.globl main

###############################################################################
# Function: swap
# Arguments: 
#   $a0 - array base address
#   $a1 - index i
#   $a2 - index j
# Returns: void
###############################################################################
swap:
    # Save registers according to convention
    addi $sp, $sp, -12
    sw   $s0, 8($sp)
    sw   $s1, 4($sp)
    sw   $s2, 0($sp)
    
    # Calculate addresses and load values
    sll  $s0, $a1, 2      # i * 4
    sll  $s1, $a2, 2      # j * 4
    add  $s0, $a0, $s0    # address of v[i]
    add  $s1, $a0, $s1    # address of v[j]
    
    # Perform swap
    lw   $s2, 0($s0)      # tmp = v[i]
    lw   $t0, 0($s1)      # t0 = v[j]
    sw   $t0, 0($s0)      # v[i] = v[j]
    sw   $s2, 0($s1)      # v[j] = tmp
    
    # Restore registers
    lw   $s0, 8($sp)
    lw   $s1, 4($sp)
    lw   $s2, 0($sp)
    addi $sp, $sp, 12
    
    jr   $ra

###############################################################################
# Function: indexMinimum
# Arguments:
#   $a0 - array base address
#   $a1 - first index
#   $a2 - last index
# Returns:
#   $v0 - index of minimum element
###############################################################################
indexMinimum:
    # Save registers
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $s0, 12($sp)
    sw   $s1, 8($sp)
    sw   $s2, 4($sp)
    sw   $s3, 0($sp)
    
    # Initialize variables
    move $s0, $a1         # mini = first
    sll  $t0, $a1, 2
    add  $t0, $a0, $t0
    lw   $s1, 0($t0)      # min = v[first]
    addi $s2, $a1, 1      # i = first + 1
    move $s3, $a0         # save array base address
    
loop_min:
    bgt  $s2, $a2, end_min    # if i > last, exit loop
    
    # Load v[i]
    sll  $t0, $s2, 2
    add  $t0, $s3, $t0
    lw   $t1, 0($t0)         # t1 = v[i]
    
    # if v[i] >= min, skip
    bge  $t1, $s1, next_min
    
    # Update minimum
    move $s0, $s2            # mini = i
    move $s1, $t1            # min = v[i]
    
next_min:
    addi $s2, $s2, 1         # i++
    j    loop_min
    
end_min:
    # Return mini in $v0
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
# Function: selectionSort
# Arguments:
#   $a0 - array base address
#   $a1 - length of array
# Returns: void
###############################################################################
selectionSort:
    # Save registers
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $s0, 12($sp)
    sw   $s1, 8($sp)
    sw   $s2, 4($sp)
    sw   $s3, 0($sp)
    
    # Initialize
    move $s0, $zero        # i = 0
    addi $s1, $a1, -1      # length - 1
    move $s2, $a0          # save array base address
    move $s3, $a1          # save length
    
sort_loop:
    bge  $s0, $s1, end_sort    # if i >= length-1, exit
    
    # Call indexMinimum(a, i, length-1)
    move $a0, $s2              # array address
    move $a1, $s0              # i
    addi $a2, $s3, -1          # length-1
    jal  indexMinimum
    
    # Call swap(a, i, mini)
    move $a0, $s2              # array address
    move $a1, $s0              # i
    move $a2, $v0              # mini (returned by indexMinimum)
    jal  swap
    
    addi $s0, $s0, 1           # i++
    j    sort_loop
    
end_sort:
    # Restore registers
    lw   $ra, 16($sp)
    lw   $s0, 12($sp)
    lw   $s1, 8($sp)
    lw   $s2, 4($sp)
    lw   $s3, 0($sp)
    addi $sp, $sp, 20
    
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
    
    # Allocate array memory (length * 4 bytes)
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

    # Call selectionSort
    move $a0, $s1             # array address
    move $a1, $s0             # length
    jal  selectionSort
    
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
