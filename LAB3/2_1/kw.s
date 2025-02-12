#
# Filename:	kw.s
# Author: 	Ben Juurlink
# Date:		March 3, 2000
# Description:	Fibonacci variant
#               a(n) = 3*a(n-1) + 2*a(n-1) + 3*a(n-3) + 3*a(n-4)
# 
	.text
	j	main			# Jump to main-routine

fibf:    
	addi	$sp, $sp, -12
	sw	$ra, 8($sp)		# push $ra
	sw	$a0, 4($sp)		# push n ($a0)
	sw	$s0, 0($sp)		# push $s0; it will contain the result
					# of the left subtree
	slti	$t0, $a0, 4		# $t0 = (n <= 3)
	beq	$t0, $zero, fib_else	# if (!$t0) goto fib_else
	addi	$v0, $zero, 1		# return 1 (in $v0)
	addi	$sp, $sp, 12		# no need to restore $ra, $a0, $s0
	jr	$ra			# return
fib_else:
	addi	$a0, $a0, -1		# n = n-1
	jal	fibf			# $v0 = fibf(n-1)
	mul	$v0, $v0, 3		# $v0 = 3*$v0
	move	$s0, $v0		# copy to saved register
	addi	$a0, $a0, -1		# n--. Note: $a0 is saved by callee
	jal	fibf			# $v0 = fibf(n-2)
	mul	$v0, $v0, 2		# $v0 = 2*$v0
	add	$s0, $s0, $v0		# $s0 += 2*fibf(n-2)
	addi	$a0, $a0, -1		# n--
	jal	fibf			# $v0 = fibf(n-3)
	mul	$v0, $v0, 3		# $v0 = 3*$v0
	add	$s0, $s0, $v0		# $s0 += 3*fibf(n-3)
	addi	$a0, $a0, -4		# n--
	jal	fibf			# $v0 = fibf(n-4)
	mul	$v0, $v0, 3		# $v0 = 3*$v0
	add	$v0, $v0, $s0		# $v0 += $s0
	lw	$s0, 0($sp)		# restore $s0
	lw	$a0, 4($sp)		# restore $a0
	lw	$ra, 8($sp)		# restore $ra
	addi	$sp, $sp, 12		# restore $sp
	jr	$ra			# return

#
# end fibf
#

	.data
invoer_str:	.asciiz	"Voer een getal in: "
het_str:	.asciiz	"Het "
uitvoer_str:	.asciiz	"-de Fibonacci getal is "
newline:	.asciiz	"\n"

	.text
	.globl	main
main:	
	addi	$sp, $sp, -4		# create a stack frame	
	sw	$ra, 0($sp)		# save the return address

	la	$a0, invoer_str		# printf("Voer een getal in: ")
	li	$v0, 	4		#
	syscall				#
	
	li		$v0, 5		# scanf("%d", &n)
	syscall				#
	move		$s0, $v0	# $s0=n
	
	move		$a0, $s0	# $a0=n
	jal		fibf		# call fibf
	
	move		$t0, $v0	# $t0=$v0
	
	la		$a0, het_str	# printf("Het ")
	li		$v0, 4		#
	syscall				#
	
	li		$v0, 1		# printf("%d", n)
	move		$a0, $s0	#
	syscall				#
	
	la		$a0, uitvoer_str# printf("-de Fibonacci getal is ")
	li		$v0, 4		#	
	syscall				#
	
	li		$v0, 1		# printf("%d", fibf(n))
	move		$a0, $t0	#
	syscall	#
	
	la		$a0, newline	# printf("\n")
	li		$v0, 4		#
	syscall				#
	
	lw		$ra, 0($sp)	# restore return address	
	addi		$sp, $sp, 4	# eliminate stack frame
	li		$v0, 10		# exit
	syscall

#
# end main
#	
