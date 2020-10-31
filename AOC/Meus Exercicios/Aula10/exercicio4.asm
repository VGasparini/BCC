	.data
	mult_text:	.asciiz" x "
	espaco_text:	.asciiz" | "
	endl_text:	.asciiz"\n"
	igual_text:	.asciiz" = "
	.text
# Vinicius Gasparini
	.globl main main:

	li $s0, 2 # i = 2

mult_loop_i:
	slti $t0, $s0, 11 # if ( i < 11 )
	beq $t0, $zero, end
	li $s1, 1 # j=1

mult_loop_j:
	slti $t0, $s1, 11 # if ( j < 11 )
	beq $t0, $zero, quebra # pula pro fim de linha

	move $a0, $s0 # carrega valor de i
	li $v0, 1 # call code para print_int
	syscall

	la $a0, mult_text # carrega texto " x "
	li $v0, 4 # call code para print_str
	syscall

	move $a0, $s1 # carrega valor de j
	li $v0, 1 # call code para print_int
	syscall

	la $a0, igual_text # carrega texto " = "
	li $v0, 4 # call code para print_str
	syscall

	mul $a0, $s0, $s1 # i*j e carrega valor da multiplicação
	li $v0, 1 # call code para print_int
	syscall

	la $a0, espaco_text # carrega texto " | "
	li $v0, 4 # call code para print_str
	syscall

	addi $s1, $s1, 1 # j++
	j mult_loop_j

quebra:
	la $a0, endl_text # carrega texto de quebra de linha
	li $v0, 4 # call code para print_str
	syscall

	addi $s0, $s0, 1 # i++
	j mult_loop_i

end:

	li $v0, 10 # call code para exit
	syscall

