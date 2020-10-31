	.data 
	n_text:			.asciiz "Insira valor de n:  "
	par: 			.asciiz "Eh par\n"
	impar: 			.asciiz "Eh impar\n"		
	.text
# Vinicius Gasparini
	
	.globl main
main:
	li $t0, 2
	
paridade:
	li $v0, 4		# call code para print_str
	la $a0, n_text		# carregando str para arg da syscall
	syscall
	
	li $v0, 5		# call code para read_int
	syscall
	move $s0, $v0		# carregando valor de arg para n
	
	beq $s0, $zero, end
	div $s0, $t0		# n / 2
	mfhi $t1
	beq $t1, $zero, n_par	# caso resto = 0, par
	j n_impar		# caso resto = 1, impar
	
n_par:
	li $v0, 4		# call code para print_str
	la $a0, par		# carregando str para arg da syscall
	syscall
	j paridade
n_impar:
	li $v0, 4		# call code para print_str
	la $a0, impar		# carregando str para arg da syscall
	syscall
	j paridade
	
end:
	li $v0, 10		# call code para exit
	syscall
