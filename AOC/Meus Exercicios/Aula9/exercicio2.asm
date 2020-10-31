	.data 
	n_text:			.asciiz "Insira valor de n:  "
	ans_text: 		.asciiz "Fat(n): "
		
	.text
# Vinicius Gasparini
	
	.globl main
main:
	li $t1, 1 		# contador
	li $s1, 1 		# valor base
	
	li $v0, 4		# call code para print_str
	la $a0, n_text		# carregando str para arg da syscall
	syscall
	
	li $v0, 5		# call code para read_int
	syscall
	move $s0, $v0		# carregando valor de arg para n
	
fat:	
	mult $s1, $t1		# multiplicacao (n-1)*n
	mflo $s1		# move a parte low da mult para $s1
	addi $t1, $t1, 1	# incrementa contador
	slt $t0, $s0, $t1	# cont < n
	beq $t0, $zero, fat	# saindo do loop
	j print_end
	
print_end:
	li $v0, 4		# call code para print_str
	la $a0, ans_text	# carregando str para arg da syscall
	syscall
	li $v0, 1		# call code para print_int
	move $a0, $s1		# carregando valor de fat(n) para o arg da syscall
	syscall
