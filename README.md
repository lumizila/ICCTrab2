# ICCTrab2
### Segundo trabalho de ICC - Otimizar o codigo do primeiro trabalho.
### Usar o pdf do livro de referencia que se encontra neste diretorio
### Para usar o lidwid nos labs, executar os seguintes comandos primeiro: 

```
modprobe msr
cd /home/soft/likwid
export PATH=/home/soft/likwid/bin:/home/soft/likwid/sbin:$PATH
export LD_LIBRARY_PATH=/home/soft/likwid/lib:$LD_LIBRARY_PATH
cd ~/Documentos/ICCTrab2
```

*Entregar relatorio e codigo*

O relatorio eh SUPER importante, temos que explicar o que fizemos para que o professor saiba o que aprendemos. Incluir experimentos no relatorio nao eh super importante. Justificar as coisas que não deu pra melhorar. 

#### *Dicas de otimização/ dicas para o trabalho:*

- Lembrar de mudar a compilação para ser aquela que mais otimiza o codigo
- Cuidar com cashe trashing
- Performance depende do processador da maquina
- LIKWID -> software opensource que mede performance do sistema: https://github.com/RRZE-HPC/likwid/wiki
- Carregar modulo msr do kernel e exportar o likwid no PATH
- idealmente (Tem?) que compilar o LIKWID na maquina
- likwid-topology(mostra a topologia da maquina), likwid-bench(so faz sentido se compilar o likwid na maquina, serve para comparar seu codigo com outros mais rapidos que ja estao no likwid), likwid-perfctr(eh o cara que vamos usar no trabalho), likwid-perfscope(monitora a cada x unidades de tempo a aplicacao)
- Alguns processadores fazem coisas que outros nao fazem: ver com o professor caso isso aconteca
- Rodar o experimento no mesmo CORE
- Cuidar com outros processos na maquina que podem afetar a performance
- Com likwid-topology da pra ver: Niveis de cache/associatividade/quandidade de cores(e de nucleos)/memoria
- no trabalho vamos usar "likwid-perfctr -g" e depois temos que gerar os graficos

# O que estava na pag do moodle do daniel:

Trabalho Prático: Otimização do Desempenho na Inversão de Matrizes
O objetivo deste trabalho é melhorar e avaliar o desempenho do programa computacional desenvolvido no 1º Trabalho Prático.


Melhoria de Desempenho
Você deve alterar o código do primeiro trabalho (v1) de forma a obter uma melhora no desempenho (v2) em duas partes:

Na operação de resolução do sistema linear triangular (op1): LUx=b -> Ly=b -> Ux=y;
Na operação de cálculo do resíduo (op2): R = I - A * inv(A);
As alterações devem ser explicadas no relatório a ser entregue, justificando as razões pelas quais você efetuou cada alteração. MUITO IMPORTANTE: você deve ser explicar por que motivo suas modificações levaram a um aumento de desempenho.


Análise de Desempenho
Uma vez alterado o código, você deve comparar o desempenho das duas versões. Estas análises devem ser descritas, sob a forma de um trabalho acadêmico, e entregues em forma impressa e em formato PDF.

É imprescindível que sejam respeitadas as seguintes condições:

Ambos códigos devem ser compilados com GCC e as opções: -O3 -mavx -march=native;
Os códigos devem ser compilados na mesma máquina utilizada para os testes.
Os testes devem utilizar os mesmos parâmetros e em igualdade de condições;
Ambos códigos devem ser instrumentados com a biblioteca do LIKWID para que se possa separar o cálculo da MMV do cálculo da MVV, ou seja, você deve criar um marcador LIKWID para a parte da MMV e outro para a parte da MVV;
Você pode escolher um computador de sua preferência, desde que possua os contadores Likwid especificados. Não utilize as servidoras de processamento do DInf que tenham uso compartilhado. Elas podem ser máquinas virtuais e o compartilhamento impede medidas de desempenho. Em caso de dúvida, consulte o professor.
Você deve apresentar a arquitetura do processador utilizado nos testes no seu texto. Estas informações podem ser obtidas com o comando "LIKWID-topology -g -c".
 

Para comparar o desempenho dos códigos, você deve efetuar uma série de testes.

Cada teste deve ser reportado sob a forma de um gráfico de linhas, com linhas em cores distintas para os resultados de cada versão (v1 e v2);
No eixo das abcissas os gráficos representam o tamanho da matriz (N). Cada teste deve ser executado para os seguintes tamanhos de matriz:  N={32, 33, 64, 65, 128, 129, 256, 257, 512, 1000, 2000};
O número de iterações em todos os testes, para todos tamanhos de matrizes, deve ser -i 10;
As matrizes devem ser geradas aleatoreamente com a função definida no primeiro trabalho;
Cada teste deve apresentar em linhas distintas os valores para o cálculo de cada operações (op1 e op2). Assim, os gráficos terão sempre 4 linhas, duas para a v1 e duas para a v2;
Cada gráfico deve ser explicado e você deve demonstrar que consegue entender o que está reportado nele;
Os gráficos devem ser apresentados com o eixo das ordenadas em escala logarítmica.
 

Os seguintes testes devem ser executados (um gráfico para cada teste):

Teste de tempo: mostra o tempo médio do cálculo da op1 e o tempo médio do cálculo da op2 (utilize a função "timestamp()" para medir o tempo);
Banda de Memória: utilizar o grupo MEM do LIKWID, e apresentar o resultado de "Memory bandwidth [MBytes/s]"; Caso não tenha o grupo MEM, utilize o grupo L3.
Cache miss L1: utilizar o grupo CACHE do LIKWID, e apresentar o resultado de "data cache miss ratio". Caso não tenha o cache miss da L1, utilize o cache miss da L2.
Operações aritméticas: utilizar o grupo FLOPS_DP ou FLOPS_AVX do LIKWID, e apresentar o resultado de "MFLOP/s"
Produto a ser Entregue
O trabalho deve ser desenvolvido pelo MESMO GRUPO ds primeira parte.

Cada grupo deve entregar um pacote de software completo contendo os fontes em linguagem C/C++ do trabalho 1, com as modificações introduzidas para o trabalho 2 e um relatório em formato PDF.

O pacote deve ser arquivado e compactado com tar(1) e gzip(1) em um arquivo chamado login1.tar.gz (se grupo com 1 membro) ou login1-login2.tar.gz (se grupo com 2 membros), onde login1 e login2 são os logins dos alunos que compõem o grupo. O pacote deve ter a mesma estrutura de diretório e arquivos do Trabalho 1.

O arquivo contendo o relatório deve ser nomeado RELATORIO-login1-login2.pdf e também deve ser entregue impresso no dia seguinte à data limite de entrega do trabalho.

RELATORIO-login1-login2.pdf

O relatório deve ter o formato de um trabalho acadêmico e conter todas as informações e análises solicitadas. Além disso, a conclusão deve apresentar os aspectos que sua equipe considerou mais relevante/importante no desenvolvimento do trabalho.

Entrega
O prazo final para a entrega deste trabalho é dia  19 de novembro de 2017, 23:55:00h, IMPRETERIVELMENTE.

O trabalho deve ser entregue via moodle
No texto de entrega DEVE CONSTAR OBRIGATORIAMENTE o Nome e Números de Registro Acadêmico (RA) dos membros do grupo;
 
Critérios de Avaliação
APENAS OS TRABALHOS QUE FUNCIONAREM SERÃO CORRIGIDOS. Se o trabalho não compilar ou acusar falha de segmentação (Segmentation fault) prematura durante os testes realizados pelo professor (sem que qualquer operação se efetue a contento) ou não produzir uma matriz inversa, trará para o grupo NOTA 0 (ZERO). Também receberão NOTA 0 (ZERO) trabalhos plagiados de qualquer fonte, e/ou com códigos idênticos ou similares. Além disso, apenas trabalhos entregues no prazo marcado receberão nota.

Os itens de avaliação do trabalho e respectivas pontuações são:

Qualidade da documentação: arquivo RELATORIO-login1-login2.pdf (20 pontos)
Testes: corretude das respostas nos testes executados bem como na sua análise (40 pontos)
Otimização: Qualidade/dificuldade das otimizações efetuadas (40 pontos)
BONUS: se você comprovar que está usando os registradores AVX de maneira eficiente no seu código, ganha um bônus de 10 pontos no trabalho.
 

Defesa: A defesa será agendada pelo professor caso julgue necessário. Especialmente casos em que houver discrepância entre a nota do trabalho e da segunda prova ensejarão defesa para comprovação de autoria.

# O resultado do comando "likwid-topology -c -g" na maquina H40 do LAB12 foi:

```
lmwc14@h40:/home/soft/likwid$ likwid-topology -c -g
--------------------------------------------------------------------------------
CPU name:	AMD FX(tm)-6300 Six-Core Processor
CPU type:	AMD Interlagos processor
CPU stepping:	0
********************************************************************************
Hardware Thread Topology
********************************************************************************
Sockets:		1
Cores per socket:	3
Threads per core:	2
--------------------------------------------------------------------------------
HWThread	Thread		Core		Socket		Available
0		0		0		0		*
1		0		0		0		*
2		0		1		0		*
3		0		1		0		*
4		0		2		0		*
5		0		2		0		*
--------------------------------------------------------------------------------
Socket 0:		( 0 1 2 3 4 5 )
--------------------------------------------------------------------------------
********************************************************************************
Cache Topology
********************************************************************************
Level:			1
Size:			16 kB
Type:			Data cache
Associativity:		4
Number of sets:		64
Cache line size:	64
Cache type:		Non Inclusive
Shared by threads:	1
Cache groups:		( 0 ) ( 1 ) ( 2 ) ( 3 ) ( 4 ) ( 5 )
--------------------------------------------------------------------------------
Level:			2
Size:			2 MB
Type:			Unified cache
Associativity:		16
Number of sets:		2048
Cache line size:	64
Cache type:		Non Inclusive
Shared by threads:	2
Cache groups:		( 0 1 ) ( 2 3 ) ( 4 5 )
--------------------------------------------------------------------------------
Level:			3
Size:			8 MB
Type:			Unified cache
Associativity:		64
Number of sets:		2048
Cache line size:	64
Cache type:		Non Inclusive
Shared by threads:	2
Cache groups:		( 0 1 ) ( 2 3 ) ( 4 5 )
--------------------------------------------------------------------------------
********************************************************************************
NUMA Topology
********************************************************************************
NUMA domains:		1
--------------------------------------------------------------------------------
Domain:			0
Processors:		( 0 1 2 3 4 5 )
Distances:		10
Free memory:		1587.15 MB
Total memory:		3680.29 MB
--------------------------------------------------------------------------------


********************************************************************************
Graphical Topology
********************************************************************************
Socket 0:
+-------------------------------------------------------------+
| +-------+ +-------+ +-------+ |
| |  0 1  | |  2 3  | |  4 5  | |
| +-------+ +-------+ +-------+ |
| +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ |
| | 16 kB | | 16 kB | | 16 kB | | 16 kB | | 16 kB | | 16 kB | |
| +-------+ +-------+ +-------+ +-------+ +-------+ +-------+ |
| +-------+ +-------+ +-------+ |
| |  2 MB | |  2 MB | |  2 MB | |
| +-------+ +-------+ +-------+ |
| +-------+ +-------+ +-------+ |
| |  8 MB | |  8 MB | |  8 MB | |
| +-------+ +-------+ +-------+ |
+-------------------------------------------------------------+
```
