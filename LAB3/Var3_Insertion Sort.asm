# Data segment for strings and array storage
.data
    promptSize:      .asciiz "Insert the array size\n"
    promptElements:  .asciiz "Insert the array elements, one per line\n"
    outputMsg:       .asciiz "The sorted array is:\n"
    newline:         .asciiz "\n"

.text
.globl main

###############################################################################
# Function: insert
# Arguments:
#   $a0 - array base address
#   $a1 - length
#   $a2 - elem to insert
#   $a3 - position i to insert at
# Returns: void
###############################################################################
insert:
    # Save registers
    addi $sp, $sp, -16
    sw   $ra, 12($sp)
    sw   $s0, 8($sp)
    sw   $s1, 4($sp)
    sw   $s2, 0($sp)
    
    # Initialize
    move $s0, $a1         # j = length - 1
    addi $s0, $s0, -1
    move $s1, $a0         # save array base
    move $s2, $a3         # save position i
    
shift_loop:
    blt  $s0, $s2, insert_elem  # if j < i, exit loop
    
    # a[j+1] = a[j]
    sll  $t0, $s0, 2      # j * 4
    add  $t0, $s1, $t0    # address of a[j]
    lw   $t1, 0($t0)      # load a[j]
    sw   $t1, 4($t0)      # store at a[j+1]
    
    addi $s0, $s0, -1     # j--
    j    shift_loop
    
insert_elem:
    # a[i] = elem
    sll  $t0, $s2, 2      # i * 4
    add  $t0, $s1, $t0    # address of a[i]
    sw   $a2, 0($t0)      # store elem
    
    # Restore registers
    lw   $ra, 12($sp)
    lw   $s0, 8($sp)
    lw   $s1, 4($sp)
    lw   $s2, 0($sp)
    addi $sp, $sp, 16
    
    jr   $ra

###############################################################################
# Function: binarySearch
# Arguments:
#   $a0 - array base address
#   $a1 - length
#   $a2 - elem to search for
# Returns:
#   $v0 - position where elem should be inserted
###############################################################################
binarySearch:
    # Save registers
    addi $sp, $sp, -20
    sw   $ra, 16($sp)
    sw   $s0, 12($sp)
    sw   $s1, 8($sp)
    sw   $s2, 4($sp)
    sw   $s3, 0($sp)
    
    # Initialize
    li   $s0, -1          # low = -1
    move $s1, $a1         # high = length
    move $s2, $a0         # save array base
    move $s3, $a2         # save elem
    
search_loop:
    sub  $t0, $s1, $s0    # high - low
    addi $t1, $t0, -1     # (high - low) - 1
    blez $t1, end_search  # if low >= high-1, exit
    
    # mid = (low + high) / 2
    add  $t0, $s0, $s1
    sra  $t0, $t0, 1      # divide by 2
    
    # Load a[mid]
    sll  $t1, $t0, 2
    add  $t1, $s2, $t1
    lw   $t2, 0($t1)      # t2 = a[mid]
    
    # Compare a[mid] with elem
    blt  $t2, $s3, mid_less
    move $s1, $t0         # high = mid
    j    search_loop
    
mid_less:
    move $s0, $t0         # low = mid
    j    search_loop
    
end_search:
    # Return high
    move $v0, $s1
    
    # Restore registers
    lw   $ra, 16($sp)
    lw   $s0, 12($sp)
    lw   $s1, 8($sp)
    lw   $s2, 4($sp)
    lw   $s3, 0($sp)
    addi $sp, $sp, 20
    
    jr   $ra

###############################################################################
# Function: insertionSort
# Arguments:
#   $a0 - array base address
#   $a1 - length
# Returns: void
###############################################################################
insertionSort:
    # Save registers
    addi $sp, $sp, -28
    sw   $ra, 24($sp)
    sw   $s0, 20($sp)
    sw   $s1, 16($sp)
    sw   $s2, 12($sp)
    sw   $s3, 8($sp)
    sw   $s4, 4($sp)
    sw   $s5, 0($sp)
    
    # Initialize
    move $s0, $a0         # save array address
    move $s1, $a1         # save length
    
    # Allocate array b
    sll  $a0, $a1, 2      # length * 4
    li   $v0, 9           # sbrk syscall
    syscall
    move $s2, $v0         # s2 = b array address
    
    # Main sorting loop
    move $s3, $zero       # i = 0
sort_loop:
    beq  $s3, $s1, copy_back  # if i == length, exit loop
    
    # Load a[i]
    sll  $t0, $s3, 2
    add  $t0, $s0, $t0
    lw   $s4, 0($t0)      # s4 = a[i]
    
    # Call binarySearch
    move $a0, $s2         # b array
    move $a1, $s3         # current length (i)
    move $a2, $s4         # element to insert
    jal  binarySearch
    move $s5, $v0         # s5 = position
    
    # Call insert
    move $a0, $s2         # b array
    move $a1, $s3         # current length (i)
    move $a2, $s4         # element to insert
    move $a3, $s5         # position
    jal  insert
    
    addi $s3, $s3, 1      # i++
    j    sort_loop
    
copy_back:
    # Copy array b back to a
    move $s3, $zero       # i = 0
copy_loop:
    beq  $s3, $s1, end_sort  # if i == length, exit
    
    sll  $t0, $s3, 2
    add  $t1, $s2, $t0    # address in b
    add  $t2, $s0, $t0    # address in a
    lw   $t3, 0($t1)      # load from b
    sw   $t3, 0($t2)      # store in a
    
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

    # Call insertionSort
    move $a0, $s1             # array address
    move $a1, $s0             # length
    jal  insertionSort
    
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
