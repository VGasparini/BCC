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
	ori $a1, $zero, 1	# bit aceso de base
	
	jal dec_to_bin
	
	ori $a0, $v0, 0		# carregando retorno binario para arg da syscall
	ori $v0, $zero, 1	# call code para print_int	
	syscall

end:
	li $v0, 10
	syscall

dec_to_bin:
	
	slti $t0, $a0, 2 	# if (a0<2)
	bne $t0, $zero, return 	# if (a0<2)
	
	ori $s0, $zero, 2 	# s0 = 2
	div $a0, $s0 		# n/2
	mfhi $t1 		# n%2
	mflo $a0		# n//2
	mul $t1, $t1, $a1 	# t1 = (n%2) * b
	
	addi $sp, $sp, -8 	# liberando espaço na stack
	sw $ra, 0($sp) 		# salvando endereço de retorno na stack
	sw $t1, 4($sp) 		# salvando bit na stack

	ori $t2, $zero, 10	# t2 = 10
	mul $a1, $a1, $t2	# 
	
	jal dec_to_bin 		# dec_to_bin(n/2, b*10)
	
	lw $ra, 0($sp) 		# recuperando da stack o retorno
	lw $t1, 4($sp) 		# n%10
	addi $sp, $sp, 8 	# liberando a stack
	
	add $v0, $v0, $t1
	jr $ra

return:
	mult $a0, $a1
	mflo $v0
	jr $ra

	
