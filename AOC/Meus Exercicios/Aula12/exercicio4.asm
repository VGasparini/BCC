	.data 
	n_input:			.asciiz "Insira valor de n: "
	
	.text
# Vinicius Gasparini
	.globl main
main:
	li $v0, 4		# call code para print_str
	la $a0, n_input		# carregando str para arg da syscall
	syscall

	ori $v0, $zero, 5	# call code para read_int
	syscall
	ori $a0, $v0, 0		# a0 = n
	
	jal soma
	
	ori $a0, $v0, 0		# carregando retorno para arg da syscall
	ori $v0, $zero, 1	# call code para print_int
	syscall

end:
	li $v0, 10
	syscall

soma:
	slti $t0, $a0, 10 	# if (a0<10)
	bne $t0, $zero, return 	# if (a0<10)
	
	ori $s0, $zero, 10 	# s0 = 10
	div $a0, $s0 		# n/10
	mflo $t1 		# n//10
	mfhi $t2 		# n%10
	
	addi $sp, $sp, -8 	# liberando espaço na stack
	sw $ra, 0($sp) 		# salvando endereço de retorno na stack
	sw $t2, 4($sp) 		# salvando n%10 na stack

	ori $a0, $t1, 0
	jal soma
	
	lw $ra, 0($sp) 		# recuperando da stack o retorno
	lw $t2, 4($sp) 		# n%10
	addi $sp, $sp, 8 	# liberando a stack
	
	add $v0, $v0, $t2
	jr $ra

return:
	ori $v0, $a0, 0
	jr $ra