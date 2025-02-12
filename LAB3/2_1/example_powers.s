# Programmer:  Mark Fienup
# Calculate Powers Example
# Algorithm:
# Main:
# maxNum = 3
# maxPower = 5
#
# CalculatePowers(maxNum, maxPower)
#
# end main
#
#
# CalculatePowers(integer numLimit, integer powerLimit)
# begin
#       integer i, j
#
#       for i := 1 to numLimit do
#            for j := 1 to powerLimit do
#                 result = Power(i, j)
#                 print i " raised to " j " power is " result
#            end for j
#       end for i
#
#
# integer Power(integer x, integer y)
# begin
#       integer result, counter
#
#       result = 1
#       for counter := 1 to y do
#            result := result * x
#       end for
#       return result
#######################################################################

		.text
		j	main			# Jump to main-routine

		.data
maxNum:		.word 3
maxPower:	.word 5

		.text
		.globl main
main:
		lw	$a0, maxNum
		lw	$a1, maxPower
		jal	CalculatePowers		# call CalculatePowers

		li      $v0, 10         	# exit system call 
		syscall
endMain:

		.data
str1:		.asciiz	" raised to "
str2:		.asciiz	" power is "
endLine:	.asciiz	"\n"

		.text
CalculatePowers:
#	Register Usage
#	$s0 contains i
#	$s1 contains j
#	$s2 contains numLimit
#	$s3 contains powerLimit
#	$t0 contains result

		addi	$sp, $sp, -20		# make room on stack for 5 registers
		sw	$s0, 0($sp)		# save $s0 on stack
		sw	$s1, 4($sp)		# save $s1 on stack
		sw	$s2, 8($sp)		# save $s2 on stack
		sw	$s3, 12($sp)		# save $s3 on stack
		sw	$ra, 16($sp)		# save $ra on stack

		move	$s2, $a0		# copy param. $a0 into $s2 (numLimit)
		move	$s3, $a1		# copy param. $a1 into $s3 (powerLimit)

for1:
		li	$s0, 1
forCompare1:
		ble	$s0, $s2, forBody1
		j	endFor1
forBody1:
        
for2:
		li	$s1, 1
forCompare2:
		ble	$s1, $s3, forBody2
		j	endFor2
forBody2:
        
		move	$a0, $s0		# call Power(i, j)
		move	$a1, $s1
		jal	Power			# returns result value in $v0
		move	$t0, $v0

		li	$v0, 1			# system call code for print_int
		move	$a0, $s0		# integer to print
		syscall

		li	$v0, 4			# system call code for print_str
		la	$a0, str1		# addr. of string to print
		syscall

		li	$v0, 1			# system call code for print_int
		move	$a0, $s1		# integer to print
		syscall

		li	$v0, 4			# system call code for print_str
		la	$a0, str2		# addr. of string to print
		syscall

		li	$v0, 1			# system call code for print_int
		move	$a0, $t0		# integer to print
		syscall

		li	$v0, 4			# system call code for print_str
		la	$a0, endLine		# addr. of string to print
		syscall

		addi	$s1, $s1, 1
		j	forCompare2
endFor2:

		addi	$s0, $s0, 1
		j	forCompare1
endFor1:

		lw	$s0, 0($sp)		# restore $s0 from stack
		lw	$s1, 4($sp)		# restore $s1 from stack
		lw	$s2, 8($sp)		# restore $s2 from stack
		lw	$s3, 12($sp)		# restore $s3 from stack
		lw	$ra, 16($sp)		# restore $ra from stack
		addi	$sp, $sp, 20		# remove call frame from stack 
		jr	$ra			# return to calling routine
endCalculatePowers:


Power:
#	Register Usage
#	$a0 contains x
#	$a1 contains y
#	$t0 contains counter
#	$v0 contains result

# Since no #s registers are used and no subprograms are called, we do not need
# to save any registers!!!

		li	$v0, 1
for3:
		li	$t0, 1
forCompare3:
		ble	$t0, $a1, forBody3
		j	endFor3
forBody3:
		mul	$v0, $v0, $a0

		addi	$t0, $t0, 1
		j	forCompare3
endFor3:

		jr	$ra
endPower:
