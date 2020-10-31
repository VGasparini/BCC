	.data 
	poli_text:		.asciiz "Dado o polinomio y = ax^3+bx^2+cx+d\nInsira os valores de a,b,c e d\n"
	x_text: 			.asciiz "Insira o valor de x: "
	ans_text:		.asciiz "Y no ponto informado: "
		
	.text
# Vinicius Gasparini
	
	.globl main
main:
	ori $v0, $zero, 4	# call code para print_str
	la $a0, poli_text	# carregando str para arg da syscall
	syscall
	
	addi $sp, $sp, -16	# avancando stack pointer
	li $v0, 5		# call code para read_int
	syscall
	sw $v0, 0($sp)		# carregando valor de a para stack
	
	li $v0, 5		# call code para read_int
	syscall
	sw $v0, 4($sp)		# carregando valor de b para stack
	
	li $v0, 5		# call code para read_int
	syscall
	sw $v0, 8($sp)		# carregando valor de c para stack
	
	li $v0, 5		# call code para read_int
	syscall
	sw $v0, 12($sp)		# carregando valor de d para stack
	
	ori $v0, $zero, 4	# call code para print_str
	la $a0, x_text		# carregando str para arg da syscall
	syscall
	
	li $v0, 5		# call code para read_int
	syscall
	move $a1, $v0		# carregando valor de x para arg
	
	jal polinomio
	move $s0, $v0
	
	ori $v0, $zero, 4	# call code para print_str
	la $a0, ans_text	# carregando str para arg da syscall
	syscall
	
	move $a0, $s0		# carregando resultado para o arg da funcao
	ori $v0, $zero, 1	# call code para print_int
	syscall
	
end:
	ori $v0, $zero, 10	# call code para exit
	syscall

polinomio:	
	lw $s0, 0($sp) 		# $s0 = a
	addi $sp, $sp, 4	# recuando stack pointer
	lw $s1, 0($sp) 		# $s1 = b
	addi $sp, $sp, 4	# recuando stack pointer
	lw $s2, 0($sp) 		# $s2 = c
	addi $sp, $sp, 4	# recuando stack pointer
	lw $s3, 0($sp) 		# $s3 = d
	
	or $s4, $a1, $zero	# $s4 = x 
	
	mul $t0, $s4, $s4	# x^2
	mul $t1, $t0, $s4	# x^3
	
	mul $s0, $t1, $s0	# a* x^3
	mul $s1, $t0, $s1	# b* x^2
	mul $s2, $s4, $s2	# c*x
	
	add $v0, $s3, $s2	# d + c*x
	add $v0, $v0, $s1	# d + c*x +  b* x^2
	add $v0, $v0, $s0	# d + c*x +  b* x^2 + a* x^3
	
	jr $ra
