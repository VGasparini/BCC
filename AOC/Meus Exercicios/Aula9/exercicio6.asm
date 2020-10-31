	.data 
	n_text:			.asciiz "Insira valor em reais:  "
		
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
# --- notas de 50
	li $t0, 50
	div $s0, $t0		# n / 50
	
	li $v0, 1		# call code para print_int
	mflo $a0		# carregando quantidade de notas de 50 para o arg da syscall
	syscall
	
	li $a0, 32 		#32 é o código do espaço
	li $v0, 11 		#11 em $v0 para S.O escrever $a0 na tela como char
	syscall 		#chama o S.O. para escrever
# --- notas de 20
	mfhi $s0		# carregando o resto da divisao para s0
	li $t0, 20
	div $s0, $t0		# n / 20
	
	li $v0, 1		# call code para print_int
	mflo $a0		# carregando quantidade de notas de 20 para o arg da syscall
	syscall
	
	li $a0, 32 		#32 é o código do espaço
	li $v0, 11 		#11 em $v0 para S.O escrever $a0 na tela como char
	syscall 		#chama o S.O. para escrever
# --- notas de 10	
	mfhi $s0		# carregando o resto da divisao para s0
	li $t0, 10
	div $s0, $t0		# n / 10
	
	li $v0, 1		# call code para print_int
	mflo $a0		# carregando quantidade de notas de 10 para o arg da syscall
	syscall
	
	li $a0, 32 		#32 é o código do espaço
	li $v0, 11 		#11 em $v0 para S.O escrever $a0 na tela como char
	syscall 		#chama o S.O. para escrever
# --- notas de 5
	mfhi $s0		# carregando o resto da divisao para s0
	li $t0, 5
	div $s0, $t0		# n / 5
	
	li $v0, 1		# call code para print_int
	mflo $a0		# carregando quantidade de notas de 5 para o arg da syscall
	syscall

	li $a0, 32 		#32 é o código do espaço
	li $v0, 11 		#11 em $v0 para S.O escrever $a0 na tela como char
	syscall 		#chama o S.O. para escrever
# --- moedas de 1
	li $v0, 1		# call code para print_int
	mfhi $a0		# carregando quantidade de moedas de 1  para o arg da syscall
	syscall
