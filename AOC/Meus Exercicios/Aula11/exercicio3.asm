	.data 
	n_text:			.asciiz "Insira valor de n: "
	ans1_text: 		.asciiz " possui "
	ans2_text: 		.asciiz " digitos"
		
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
	
	li $v0, 5		# call code para read_int
	syscall
	move $a1, $v0		# carregando valor de arg para n
	
	jal conta_digitos
	
	move $a0, $v0		# carregando qtd de digitos para o arg da funcao
	ori $v0, $zero, 1	# call code para print_int
	syscall

	ori $v0, $zero, 10	# call code para exit
	syscall

conta_digitos:
	ori $t1, $zero, 10
	addi $sp, $sp, -4 	#ajusta a pilha
	sw $ra, 0($sp) 		#guarda o endereço de retorno
	div $a0, $t1		# n / 10
	mfhi $s0
	mflo $a0
	beq $s0, $a1, return1
	
	jal conta_digitos
	
	lw $ra, 0($sp) 		#carrega o endereço de retorno da pilha
	addi $sp, $sp, 4 	#apaga os valores da pilha
	jr $ra

end:
	add $ra, $ra, $v0
	jr $ra			# salta de volta a main

return1:
 	ori $v0,$zero,1		# salva retorno 1
 	j end
return0 :
	ori $v0,$zero,0		# salva retorn 0
 	j end
