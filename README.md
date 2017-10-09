# ICCTrab2
### Segundo trabalho de ICC - Otimizar o codigo do primeiro trabalho.

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
- 
