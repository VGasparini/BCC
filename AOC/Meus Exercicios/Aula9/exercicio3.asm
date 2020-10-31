	.data 
	input_text:		.asciiz "\nInsira um valor de n (-1 para sair): "
	ans_text: 		.asciiz "\nMedia: "
	
	.text
# Vinicius Gasparini
	
	.globl main
main:
	li $t0, 0		# contador 
	li $s0,-1		# condicao de parada (n != -1)
	li $s1, 0		# soma parcial
loop:
	li $v0, 4		# call code para print_str
	la $a0, input_text	# carregando str para arg da syscall
	syscall
	
	li $v0, 5		# call code para read_int
	syscall
	move $t2, $v0		# carregando valor de arg para n
	
	beq $t2, $s0, print_end	#  verificando se n == -1; se sim sai do loop
	add $s1, $s1, $t2	# soma_parcial += n
	addi $t0, $t0, 1	# contador++
	
	j loop
	
print_end:
	li $v0, 4		# call code para print_str
	la $a0, ans_text	# carregando str para arg da syscall
	syscall
	
	li $v0, 1		# call code para print_int
	div $s1, $t0		# soma_parcial / contador
	mflo $a0		# move a parte low (cociente) da div para arg da syscall
	syscall
