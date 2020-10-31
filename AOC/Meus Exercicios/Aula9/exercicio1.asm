	.data 
	ans_text: 		.asciiz "Fat(9): "
	
	.text
# Vinicius Gasparini
	
	.globl main
main:
	li $s1, 9 		# n=9
	li $t1, 1 		# contador
	li $s0, 1 		# valor base
fat:	
	mul $s0, $s0, $t1	# multiplicacao
	addi $t1, $t1, 1	# incrementa contador
	slt $t0, $s1, $t1	# cont < n
	beq $t0, $zero, fat	# saindo do loop
	j print_end
	
print_end:
	li $v0, 4		# call code para print_str
	la $a0, ans_text	# carregando str para arg da syscall
	syscall
	li $v0, 1		# call code para print_int
	move $a0, $s0		# carregando valor de fat(9) para o arg da syscall
	syscall
