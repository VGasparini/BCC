	.data 
	n_text:			.asciiz "\nInsira valor de n: "
	ans_text: 		.asciiz "Fib(n): "
		
	.text
# Vinicius Gasparini
	
	.globl main
main:
	ori $v0, $zero, 4	# call code para print_str
	la $a0, n_text		# carregando str para arg da syscall
	syscall
	
	ori $v0, $zero, 5	# call code para read_int
	syscall
	move $a0, $v0		# carregando valor da syscall para arg 
	
	slt $t0, $a0, $zero	# if n < 0
	bnez $t0, end
	
	jal fib
    move $s0, $v0
	
	ori $v0, $zero, 4	# call code para print_str
	la $a0, ans_text	# carregando str para arg da syscall
	syscall
	ori $v0, $zero, 1	# call code para print_int
	move $a0, $s0		# carregando valor de fib(n) para o arg da syscall
	syscall
	j main

end:
	ori $v0, $zero, 10	# call code para exit
	syscall

fib:	
	ori $v0, $zero, 0 	# valor base
	beqz $a0, fib_zero
	ori $t2, $zero, 0	# contador
	ori $t1, $zero, 1 	# valor base
	ori $t3, $a0, 0		# valor n
fib_loop:
	move $t0, $v0		
	add $v0, $t1, $v0	# fib(n) = fib(n-1) + fib(n-2)
	move $t1, $t0		
	addi $t2, $t2, 1	# contador++
	slt $t0, $t2, $t3	# cont < n
	bne $t0, $zero, fib_loop# saindo do loop
	
	jr $ra
fib_zero:
	jr $ra