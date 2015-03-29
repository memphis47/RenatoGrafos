Trabalho para a disciplina CI065 / CI755 - Algoritmos e Teoria dos Grafos
Professor Renato Carmo

Aluno: Rafael Rocha de Carvalho 
GRR: 20104490
Identificador: rafaelc

Introdução:
	Esse Trabalho tem como objetivo implementar uma struct para guardar um grafo lido pela biblioteca cgraph.

Modo de execução:
	Para executar o programa passando dois arquivos como parametro, sendo o primeiro um .dot e o segundo um arquivo para saida use:

	> ./nome_do_executavel nome_do_arquivo.dot nome_do_arquivo_de_saida

	Caso queira usar a saidas padrao stdin e stdout use:

	> ./nome_do_executavel < nome_do_arquivo.dot

Bugs:

	Bug 1: 
		Bug: Erro ao dar free no grafo g;
		Gravidade: Médio;
		Função Responsável: destroi_grafo(); 
		Descrição:  
			Nos arquivos .dot que foram disponibilizados pelo professor não acontece nenhum erro, 
			porêm com arquivos .dot que eu criei e com o arquivo petersen.dot o arquivo apresenta o seguinte erro:

				*** Error in `./nome_do_executavel': free(): invalid next size (fast): 0x0000000001448180 ***
				Abortado

			Esse erro não afeta o armazenamento do grafo na struct, só interrompendo o programa durante a execução da função detroi_grafo.

