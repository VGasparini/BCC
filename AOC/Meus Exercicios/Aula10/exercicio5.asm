	.data
	ponto_x_text:	.asciiz "Insira as coordenadas do ponto em X  "
	ponto_y_text:	.asciiz "Insira as coordenadas do ponto em Y  "
	quad_text:	.asciiz " quadrante"
	eixo_x_text:	.asciiz "Eixo x"
	eixo_y_text:	.asciiz "Eixo y"
	origem_text:	.asciiz "Origem"
	.text
# Vinicius Gasparini
	.globl main
main:

	li $v0, 4		# call code para print_str
	la $a0, ponto_x_text	# carregando str para arg da syscall
	syscall
	
	li $v0, 5		# call code para read_int
	syscall
	move $s0, $v0		# carregando valor de arg para n
	
	slt $t0, $s0, $zero	# verificando se x < 0
	
	li $v0, 4		# call code para print_str
	la $a0, ponto_y_text	# carregando str para arg da syscall
	syscall
	
	li $v0, 5		# call code para read_int
	syscall
	move $s1, $v0		# carregando valor de arg para n
	
	slt $t1, $s1, $zero	# verificando se y < 0
	
	beq $s0, $s1, igual
	beqz $s0, eixo_y
	beqz $s1, eixo_x
quadrantes:
	beqz $t0, direita
	j esquerda
igual:
	beqz $s0, origem
	j quadrantes
direita:
	beqz $t1, quad_1
	j quad_4
esquerda:
	beqz $t1, quad_2
	j quad_3
origem:
	li $v0, 4		# call code para print_str
	la $a0, origem_text	# carregando str para arg da syscall
	syscall
	j end
eixo_x:
	li $v0, 4		# call code para print_str
	la $a0, eixo_x_text	# carregando str para arg da syscall
	syscall
	j end
eixo_y:
	li $v0, 4		# call code para print_str
	la $a0, eixo_y_text	# carregando str para arg da syscall
	syscall
	j end
quad_1:
	li $a0, 1
	j print
quad_2:
	li $a0, 2
	j print
quad_3:
	li $a0, 3
	j print
quad_4:
	li $a0, 4
	j print
print:    
	li   $v0, 1      	# call code para print_int
	syscall
	la   $a0, quad_text    	# carrega texto
	li   $v0, 4		# call code para print_str
	syscall      
end:
	li $v0, 10		# call code para exit
	syscall

