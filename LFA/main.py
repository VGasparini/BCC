from class_factory import Factory
from class_assembly_line import Assembly_Line
from class_maestro import Maestro
from class_DFA import DFA
from class_moore import Moore
from class_regex import Regex
from utils import *

#Leitura do automato de validação de entrada
validacao_entrada = DFA(*read_quintuple_from_data("valida_demanda.txt"))


#Definindo quantidade máxima de erros por linha/fabrica
max_erros = 7

#Instanciando as fábricas
fabrica1 = Factory("b.txt", max_erros)
fabrica2 = Factory("g.txt", max_erros)
fabrica3 = Factory("j.txt", max_erros)
fabrica4 = Factory("m.txt", max_erros)
fabrica5 = Factory("n.txt", max_erros)
fabrica6 = Factory("u.txt", max_erros)
fabrica7 = Factory("w.txt", max_erros)
fabrica8 = Factory("z.txt", max_erros)

#Instanciando a expressão regular que gera a instrução de fabricação
producao_regex = Regex("regex_producao.txt")

#Recebendo a demanda
header("Validação da demanda")
demanda = generate_demand()

#Validando a entrada
if validacao_entrada.run_with_word(demanda) == True:
    print(
        "Demanda validada!\nTamanho da demanda:",
        len(validacao_entrada.get_output()),
        "carros",
    )

    header("Iniciando a fábrica")
    #Preparando os carros reconhecidos para enviar a fabricação
    instrucoes_producao = []
    for carro in validacao_entrada.get_output():
        instrucoes_producao.append(producao_regex.run_regex(carro))

    #Instanciando o Maestro
    maestro = Maestro([fabrica1, fabrica2, fabrica3,fabrica4,fabrica5,fabrica6,fabrica7,fabrica8])
    
    #Gerando as instruções de produção utilizando a regex
    maestro.set_words(instrucoes_producao)

    #Iniciando a produção. O parâmetro enviado define o tempo de espera entre uma transição e outra
    maestro.pooling(0)

    #Mostrando estatisticas de produção
    maestro.statistics()

    #Salvando dados da execução
    clean()

else:
    print("Demanda inválida!\n Fechando!")

header("Desenvolvido por\nKelver Bruggmann, Rafael Granza e Vinicius Gasparini")
