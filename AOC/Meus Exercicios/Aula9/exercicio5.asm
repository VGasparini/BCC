	.data 
	n_text:			.asciiz "Insira valor de n:  "
	ans_text: 		.asciiz "Fib(n): "
		
	.text
# Vinicius Gasparini
	
	.globl main
main:
	li $t1, 0		# contador
	li $s0, 0 		# valor base
	li $s1, 1 		# valor base
	
	li $v0, 4		# call code para print_str
	la $a0, n_text		# carregando str para arg da syscall
	syscall
	
	li $v0, 5		# call code para read_int
	syscall
	move $s2, $v0		# carregando valor de arg para n
	
fib:	
	beq $s2, $zero, fib_zero
	move $t3, $s0		
	add $s0, $s1, $s0	# fib(n) = fib(n-1) + fib(n-2)
	move $s1, $t3		
	addi $t1, $t1, 1	# contador++
	slt $t0, $t1, $s2	# cont < n
	bne $t0, $zero, fib	# saindo do loop
	
	j print_end
	
fib_zero:
	li $s0, 0	
	
print_end:
	li $v0, 4		# call code para print_str
	la $a0, ans_text	# carregando str para arg da syscall
	syscall
	
	li $v0, 1		# call code para print_int
	move $a0, $s0		# carregando valor de fib(n) para o arg da syscall
	syscall
