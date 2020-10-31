	.data 
	n_input:			.asciiz "Insira valor de n: "
	k_input: 		.asciiz "\nInsira o valor de k: "
	
	.text
# Vinicius Gasparini
	.globl main
main:
	li $v0, 4		# call code para print_str
	la $a0, n_input		# carregando str para arg da syscall
	syscall

	ori $v0, $zero, 5	# call code para read_int
	syscall
	ori $t0, $v0, 0		# t0 = n
	
	li $v0, 4		# call code para print_str
	la $a0, k_input		# carregando str para arg da syscall
	syscall

	ori $v0, $zero, 5
	syscall
	
	ori $a0, $t0, 0 	# a0 = n
	ori $a1, $v0, 0 	# a1 = n
	ori $v0, $zero, 0

	jal conta
	
	ori $a0, $v0, 0		# carregando retorno para arg da syscall
	ori $v0, $zero, 1	# call code para print_int
	syscall

end:
	li $v0, 10
	syscall

conta:
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
	jal conta
	
	lw $ra, 0($sp) 		# recuperando da stack o retorno
	lw $t2, 4($sp) 		# n%10
	addi $sp, $sp, 8 	# liberando a stack

	beq $t2, $a1, return_1
	jr $ra
return_1:
	addi $v0, $v0, 1
	jr $ra
	
return:
	beq $a0, $a1, return_1
	jr $ra




