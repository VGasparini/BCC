	.text
	
	.globl main
main:
	li $s0, 9 # n
	li $t1, 1 # contador
	li $s1, 1 # valor base
fat:	
	mul $s1, $s1, $t1	# multiplicacao
	addi $t1, $t1, 1	# incremento contador
	slt $t0, $s0, $t1	# cont < n
	beq $t0, $zero, fat	# saindo do loop
	j end
	
end:
	li $v0, 1		# call code para print int
	add $a0, $zero, $s1	# carregando valor de fat(n) para o arg da syscall
	syscall