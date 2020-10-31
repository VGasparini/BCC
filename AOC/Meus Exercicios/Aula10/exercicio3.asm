	.data 
	n_text:			.asciiz "Insira a idade em dias: "
	anos_text:		.asciiz " anos\n"
	mes_text:		.asciiz " meses\n"
	dias_text:		.asciiz " dias\n"
	
		
	.text
# Vinicius Gasparini
	
	.globl main
main:
	li $v0, 4		# call code para print_str
	la $a0, n_text		# carregando str para arg da syscall
	syscall
	
	li $v0, 5		# call code para read_int
	syscall
	move $s0, $v0		# carregando valor de arg para n

	li $t0, 365
	div $s0, $t0		# n / 365
	
	li $v0, 1		# call code para print_int
	mflo $a0		# carregando quantidade de anos para o arg da syscall
	syscall
	
	li $v0, 4 		# call code para print_str
	la $a0, anos_text	# carregando str para arg da syscall
	syscall 		

	mfhi $s0		# carregando o resto da divisao para s0
	li $t0, 30		# padronizando mes com 30 dias para fins de simplicidade
	div $s0, $t0		# n / 30
	
	li $v0, 1		# call code para print_int
	mflo $a0		# carregando quantidade de meses para o arg da syscall
	syscall
	
	li $v0, 4 		# call code para print_str
	la $a0, mes_text	# carregando str para arg da syscall
	syscall 		

	li $v0, 1		# call code para print_int
	mfhi $a0		# carregando quantidade de moedas de 1  para o arg da syscall
	syscall
	
	li $v0, 4 		# call code para print_str
	la $a0, dias_text	# carregando str para arg da syscall
	syscall 
