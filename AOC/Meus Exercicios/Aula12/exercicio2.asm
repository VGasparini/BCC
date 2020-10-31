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
	
	li $v0, 5		# call code para read_int
	syscall
	move $a0, $v0		# carregando valor de arg para n

	jal fib 		
	move $s0, $v0		# salvando retorno fib(n)
	
	ori $v0, $zero, 4	# call code para print_str
	la $a0, ans_text	# carregando str para arg da syscall
	syscall
	
	move $a0, $s0		# carregando fib(n)
	ori $v0, $zero, 1	# call code para print_int
	syscall
	
	li $v0,10
	syscall

fib:
	addi $sp,$sp,-12	# ajusta a pilha para 3 items
	sw $ra,0($sp)		# retorno de fib(n) no topo da pilha
	sw $s0,4($sp)		# retorno de fib(n-1)
	sw $s1,8($sp)		# retorn de fib(n-2

	add $s0,$a0,$zero	

	addi $t1,$zero,1	# condicao de parada da recursividade
	beq $s0,$zero,return0
	beq $s0,$t1,return1

	addi $a0,$s0,-1		# chama fib(n-1)
	jal fib

	add $s1,$zero,$v0     	# s1 = fib(n-1)
	addi $a0,$s0,-2		# chama fib(n-2)
	jal fib               	#v0=fib(n-2)

	add $v0,$v0,$s1       	# v0 => fib(n) = fib(n-2)+fib(n-1)

end:
	lw $ra,0($sp)		# recupera valores dos registradores na stack
	lw $s0,4($sp)
	lw $s1,8($sp)
	addi $sp,$sp,12       	# ajustando o topo da pilha para excluir itens
	jr $ra			# salta de volta a main

return1:
 	ori $v0,$zero,1		# salva retorno 1
 	j end
return0 :
	ori $v0,$zero,0		# salva retorn 0
 	j end
