///Os membros do grupo são:
///Luiza Culau - GRR20141014
///Adolfo Tognetti - GRR20152278

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>
//para poder usar marcadores de performance
#include <likwid.h>

///funcao dada pelo professor para capturar o tempo
double timestamp(void) {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

///funcao para imprimir a matriz no stdout
void imprimeMatriz(double *mat, unsigned int n, double tempo_LU, double tempo_iter, double tempo_residuo) {

	///imprimindo os tempos	e tamanho da matriz
	printf("# Tempo LU: %f\n# Tempo iter: %f\n# Tempo residuo: %f\n#\n%d\n", tempo_LU, tempo_iter, tempo_residuo, n);

	unsigned int iterador = 0;
	unsigned int fim =  n*n;
	while( iterador != fim ) {
		printf("%.17g ", mat[iterador]);
		iterador++;
		if((iterador%n) == 0){
			printf("\n");
		}
	}
}

///funcao para imprimir a matriz em um arquivo
void imprimeMatrizArquivo(double *mat, unsigned int n, double tempo_LU, double tempo_iter, double tempo_residuo, FILE *saida) {

	///imprimindo os tempos	e tamanho da matriz
	fprintf(saida, "# Tempo LU: %f\n# Tempo iter: %f\n# Tempo residuo: %f\n#\n%d\n", tempo_LU, tempo_iter, tempo_residuo, n);

	unsigned int iterador = 0;
	unsigned int fim =  n*n;
	while( iterador != fim ) {
		fprintf(saida, "%.17g ", mat[iterador]);
		iterador++;
		if((iterador%n) == 0){
			fprintf(saida, "\n");
		}
	}
}
///funcao dada pelo professor para gerar matriz eleatoria
double *generateSquareRandomMatrix( unsigned int n ) {
	double *mat = NULL;

	/* return NULL if memory allocation fails */
	if ( ! (mat = (double *) malloc(n*n*sizeof(double))) )
		return (NULL);

	/* generate a randomly initialized matrix in row-major order */
	double *ptr = mat;
	double *end = mat + n*n;

	double invRandMax = 1.0/(double)RAND_MAX;

	while( ptr != end ) {
		*ptr++ = (double)rand() * invRandMax;
	}

	return (mat);
}

///funcao para ler a matriz de um arquivo de entrada
double *leMatriz(FILE *entrada, unsigned int *tamanho) {
	double *mat = NULL;
	//recuperando o tamanho da matriz
	char buff[10];
	fscanf(entrada, "%s", buff);
	*tamanho = atoi(buff);

	///termina programa see alocacao falha
	if ( ! (mat = (double *) malloc(*tamanho**tamanho*sizeof(double))) ){
		printf("Erro: afalha na alocacao da matriz, terminando o programa.\n");
		exit(0);
	}

	unsigned int count = 0;
	fscanf(entrada, "%s", buff);
	while(count != (*tamanho**tamanho) && !feof(entrada)){
		double el = atof(buff);
		///salvando o elemento lido na matriz
		mat[count] = el;
		fscanf(entrada, "%s", buff);
		count ++;
	}
	return mat;
}

///funcao para ler matriz do stdin
double *leMatrizStdin(unsigned int *tamanho) {
	double *mat = NULL;

	scanf("%u", tamanho);

	///termina programa se alocacao falha
	if ( !(mat = (double *) malloc(*tamanho**tamanho*sizeof(double))) ){
		printf("Erro: afalha na alocacao da matriz, terminando o programa.\n");
		exit(0);
	}

	for(int i = 0; i < (*tamanho**tamanho); i++) {
		scanf("%lf", &mat[i]);
	}
	return mat;
}

///funcao para trocar linhas de uma matriz
void trocaLinhas(double *matriz, unsigned int tamanho, int linha1, int linha2) {
	double aux;
	linha1 = linha1*tamanho;
	linha2 = linha2*tamanho;
	for(int i = 0; i < tamanho; i++) {
		aux = matriz[(linha1*tamanho) + i];
		matriz[linha1 + i] = matriz[linha2 + i];
		matriz[linha2 + i] = aux;
	}
}

///funcao para fazer a fatoracao LU da matriz
double fatoracaoLU(double *L, int tamL, double *U, double *matriz, unsigned int tamanho, int *trocas) {
	///capturando o tempo inicial
	double tempo_inicial = timestamp();

	///inicializando a matriz U
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j ++){
			U[(i*tamanho) + j] = matriz[(i*tamanho) + j];
		}
	}

	///APLICANDO METODO DE GAUSS EM U
	int pivo_posicao;
	double pivo;
	int linha;
	int coluna;
	//bool teve_troca;

	///este for faz iterar para cada coluna
	for(int i = 1; i < tamanho; i++) {
		pivo_posicao = i-1;
		coluna = i-1;
		pivo = U[tamanho*pivo_posicao+pivo_posicao];
		/*teve_troca = false;

		///guarda em qual linha esta o maior pivo
		int maior = pivo_posicao;

		int aux;
		///procurando o maior elemento em modulo da coluna para ser pivo
		for (int p = pivo_posicao + 1; p < tamanho; p++) {
			if (fabs(U[tamanho*p+pivo_posicao]) > fabs(U[tamanho*maior+pivo_posicao])) {
				maior = p;
				teve_troca = true;
				printf("pos pivo= %d, maior pos=%d \n", pivo_posicao, maior);
				aux = trocas[pivo_posicao];
				trocas[pivo_posicao] = trocas[maior];
				trocas[maior] = aux;
			}
		}

		if (teve_troca) {
			trocaLinhas(U, tamanho, pivo_posicao, maior);
			trocaLinhas(identidade, tamanho, pivo_posicao, maior);
			trocaLinhas(matriz, tamanho, pivo_posicao, maior);
			pivo = U[tamanho*pivo_posicao+pivo_posicao];
		}
		*/
		///caso o pivo seja 0 a matriz nao tem inversa
		if (pivo == 0) {
			return -1;
		}

		///este for faz iterar para cada linha
		for(int k = i; k < tamanho; k++){
			linha = k*tamanho;

			///obtendo o fator para multiplicar a linha anterior e subtrair da linha atual
			double fator = U[linha+coluna]/pivo;
			L[((k*k-k)/2)+coluna] = fator;
			///este for faz a subtracao para cada el da linha
			for(int j = pivo_posicao; j < tamanho; j++){
				U[linha+j] = U[linha+j]-(U[tamanho*pivo_posicao+j]*fator);
			}
		}
	}

	if(U[(tamanho*tamanho)-1] == 0) {
		return -1;
	}
	//for(int i = 0; i < tamanho; i++){
	//	printf("%d ", trocas[i]);
	//}
	//printf("\n");

	///capturando variacao de tempo
	tempo_inicial = timestamp() - tempo_inicial;
	return tempo_inicial;
}

///Funcao que calcula os valores da matriz Inversa atraves da retrosubstituicao
double retrosubstituicao(double *L, double *U, double *Inversa, unsigned int tamanho) {
	LIKWID_MARKER_START("Retrosubstituição(op1)");
	///capturando o tempo inicial
	double tempo_inicial = timestamp();
	///agora que temos a matriz identidade, a L e a U
	///de forma que matriz*inversa = identidade, eh possivel
	///calcular a inversa coluna por coluna na forma:
	///matriz*inversa[coluna x] = identidade[coluna x]
	///assim temos que Ax=b e A=LU, portanto L(Ux) = b, Ly = b e Ux = y

	///criando o vetor x e matriz y para salvar as informacoes
	double y[tamanho];
	double multi;
	double l;
	int linha;
	int identidade;

	for(int m = 0; m < tamanho*tamanho; m++){
		Inversa[m] = 0;
	}

	///inicializando a matriz y
	//if (!(y = (double *) malloc(tamanho*tamanho*sizeof(double))) ) {
	//	printf("Erro: afalha na alocacao da matriz R, terminando o programa.\n");
	//	exit(0);
	//}
	
	for(int i = 0; i < tamanho; i++){
		for(int m = 0; m < tamanho; m++){
			y[m] = 0;
		}

		///este for eh para cada coluna de Identidade
	
		///Ly = b
		///este for eh para cada linha de y
		///faz-se a substituicao
		for(int j = 0; j < tamanho; j++){
				///este for opera a multiplicacao entre a matriz L e o vetor y
				multi = 0;
				///para cada linha de y
				linha = tamanho*j;
				for(int k = 0; k < j; k++){
					l = 1;
					if(k != j){
						int aux = ((j*j)-j)/2;
						l = L[aux+k];
					}
					multi = multi + l * y[k];
				}

				//y[2] = (identidade[tamanho*j+i]-(L[tamanho*j]*y[0]+L[tamanho*j+1]*y[1]))/ L[tamanho*j+2]
 				//...
				identidade = 0;
				if(j == i){
					identidade = 1;
				}
				y[j] = (identidade - multi);
		}
	
			///Ux = y
			///agora que tenho o valor de y referente a coluna i da identidade,
			///eh possivel calcular o vetor x referente a coluna i da identidade
			///com retrosubstituicao

			///para cada coluna de Inversa
		for(int j = (tamanho-1); j >= 0; j--) {
			///este for opera a multiplicacao entre U e x
			multi = 0;
			linha = tamanho*j;
			///para cada linha de Inversa
			for(int k = (tamanho-1); k >= j; k--) {
				multi = multi + U[linha+k]*Inversa[tamanho*k+i];
			}
			double total =  (y[j] - multi) / U[linha+j];
			Inversa[linha+i] = total;
		}
	}
	//free(y);
	LIKWID_MARKER_STOP("Retrosubstituição(op1)");
	///capturando variacao de tempo
	tempo_inicial = timestamp() - tempo_inicial;
	return tempo_inicial;
}

///funcao utilizada para resolver o sistema necessario no processo de refinamento
void retrosubstituicao_refinamento(double *L, double *U, double *DiferencaInversa, double *R, unsigned int tamanho) {

	///criando o vetor y para salvar as informacoes
	double y[tamanho];
	double x[tamanho];

	double multi;
	double l;
	///este for eh para cada coluna da matriz R
	for(int i = 0; i < tamanho; i++) {
		///inicializando o vetor y e o vetor x
		for(int m = 0; m < tamanho; m++){
			y[m] = 0;
			x[m] = 0;
		}

		///Ly = b
		///este for eh para cada linha de y
		for(int j = 0; j < tamanho; j++){
				///este for opera a multiplicacao entre a matriz L e o vetor y
				multi = 0;
				for(int k = 0; k < j; k++){
					l = 1;
					if(k != j){
						int aux = ((j*j)-j)/2;
						l = L[aux+k];
					}
					multi = multi + l*y[k];
				}
				y[j] = (R[tamanho*j+i] - multi);
		}

		///Ux = y
		///para cada linha de x, comecando de baixo pra cima
		for(int j = (tamanho-1); j >= 0; j--) {
			///este for opera a multiplicacao entre U e x
			multi = 0;
			for(int k = (tamanho-1); k >= j; k--) {
				multi = multi + U[tamanho*j+k]*x[k];
			}
			x[j] = (y[j] - multi) / U[tamanho*j+j];

			///colocando os resultados de x na matriz DiferencaInversa
			DiferencaInversa[tamanho*j+i] = x[j];
		}
	}
}

///retorna o menor valor
int min(int a, int b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

///Funcao que melhora os resultados obtidos anteriormente para a matriz Inversa, atraves do metodo de refinamento
double refinamento(double *matriz, double *L, double *U, double *Inversa, unsigned int tamanho_matriz, int iteracoes, FILE *saida, bool tem_saida, double *tempo_iter) {
	LIKWID_MARKER_START("Refinamento(op2)");
	double tempo_total = 0;
	double soma_tempo = 0;
	int linha;
	double tempoTotalRefinamento = timestamp();

	///R = I - I_aprox
	double *R = NULL;

	///I_aprox = matriz * Inversa
	double *I_aprox = NULL;

	if (!(R = (double *) malloc(tamanho_matriz*tamanho_matriz*sizeof(double))) ) {
		printf("Erro: afalha na alocacao da matriz R, terminando o programa.\n");
		exit(0);
	}

	if (!(I_aprox = (double *) malloc(tamanho_matriz*tamanho_matriz*sizeof(double))) ) {
		printf("Erro: afalha na alocacao da matriz I_aprox, terminando o programa.\n");
		exit(0);
	}

	double *DiferencaInversa = NULL;
	if ( ! (DiferencaInversa = (double *) malloc(tamanho_matriz*tamanho_matriz*sizeof(double))) ){
		printf("Erro: afalha na alocacao da matriz DiferencaInversa, terminando o programa.\n");
		exit(0);
	}

	///repete o processo o numero de vezes foi passado por parametro
	for (int it = 1; it <= iteracoes; it++) {

		//zera a matrix
		for(int a = 0; a < tamanho_matriz*tamanho_matriz; a++) {
			I_aprox[a] = 0;
		}

		///I_aprox calculado com Blocking
		double soma;
		int blockSize = 16;
		for(int i = 0; i < tamanho_matriz; i += blockSize) {
			for(int j = 0; j < tamanho_matriz; j += blockSize) {
		    for(int k = 0; k < tamanho_matriz; k += blockSize) {
					for(int ii = 0; ii < min(blockSize, tamanho_matriz-i); ii++) {
						for(int jj = 0; jj < min(blockSize, tamanho_matriz-j); jj++) {
							soma = 0;
							for(int kk = 0; kk < min(blockSize, tamanho_matriz-k); kk++) {
								soma = soma + (matriz[((i+ii)*tamanho_matriz) + (k+kk)] * Inversa[((k+kk)*tamanho_matriz) + (j+jj)]);
							}
							I_aprox[((i+ii)*tamanho_matriz) + (j+jj)] = I_aprox[((i+ii)*tamanho_matriz) + (j+jj)] + soma;
						}
					}
		    }
			}
		}

		///I_aprox calculado normalmente
		/*double soma;
		for(int i = 0; i < tamanho_matriz; i++) {
			linha = i * tamanho_matriz;
			for(int j = 0; j < tamanho_matriz; j++) {
			    soma = 0;
			    for(int k = 0; k < tamanho_matriz; k++) {
						soma = soma + matriz[linha + k] * Inversa[(k*tamanho_matriz) + j];
			    }
				I_aprox[(i*tamanho_matriz) + j] = soma;
			}
		}*/

		///calculando R
		for(int i = 0; i < tamanho_matriz; i++) {
			linha = i * tamanho_matriz;
			for(int j = 0; j < tamanho_matriz; j++) {
				//R[(i*tamanho_matriz) + j] = identidade[(i*tamanho_matriz) + j] - I_aprox[(i*tamanho_matriz) + j];
				if (i == j) {
					R[linha + j] = 1 - I_aprox[linha + j];
				} else {
					R[linha + j] = 0 - I_aprox[linha + j];
				}
			}
		}


		///calculando norma de R
		tempo_total = timestamp();
		double sum = 0;
		double norma = 0;
		for(int i = 0; i < tamanho_matriz*tamanho_matriz; i++) {
			sum = sum + (R[i] * R[i]);
		}
		tempo_total = timestamp() - tempo_total;
		soma_tempo = soma_tempo + tempo_total;

		norma = sqrt(sum);

		if (tem_saida) {
			fprintf(saida, "# iter %d: %.17g\n", it, norma);
		} else {
			printf("# iter %d: %.17g\n", it, norma);
		}

		//devemos resolver o sistema A*DiferencaInversa = R para encontrar DiferencaInversa
		retrosubstituicao_refinamento(L, U, DiferencaInversa, R, tamanho_matriz);


		double tempo_inicial = timestamp();
		///entao refinamos o resultado somando a Inversa + DiferencaInversa
		for(int i = 0; i < tamanho_matriz; i++){
			for(int j = 0; j < tamanho_matriz; j++){
				Inversa[(i*tamanho_matriz) + j] = Inversa[(i*tamanho_matriz) + j] + DiferencaInversa[(i*tamanho_matriz) + j];
			}
		}
		tempo_inicial = timestamp() - tempo_inicial;
		*tempo_iter = *tempo_iter + tempo_inicial;

	}
	free(R);
	free(I_aprox);
	free(DiferencaInversa);
	tempoTotalRefinamento = timestamp() - tempoTotalRefinamento;
	printf("# Tempo op2: %f", tempoTotalRefinamento);
	printf("\n");
	LIKWID_MARKER_STOP("Refinamento(op2)");
	return soma_tempo/iteracoes;
}

///INICIO DO PROGRAMA PRINCIPAL
int main(int argc, char *argv[]){
	//inicializando os marcadores
	LIKWID_MARKER_INIT;
	LIKWID_MARKER_THREADINIT;

	///inicializando a seed de randomizacao
	srand( 20172 );

	///apontadores para arquivos de entrada/saida
	FILE *entrada;
	FILE *saida;

	bool tem_entrada = false;
	bool tem_saida = false;
	bool tem_iteracoes = false;
	bool eh_randomica = false;
	int iteracoes = 0;
	unsigned int tamanho_matriz = 0;
	double tempo_residuo = 0;

	///a matriz na realidade sera um vetor onde o primeiro elemento
	///fica na posicao 0 e o primeiro elemento da segunda linha
	///fica na posicao n
	double *matriz = NULL;

	///esse for localiza os parametros passados para o argv
	///e faz as operacoes devidas de acordo com o parametro;
	for(int i =0; i < argc; i++){
		if(strcmp(argv[i], "-e") == 0){
			///ler arquivo de entrada
			tem_entrada = true;
			entrada = fopen(argv[i+1], "r");
			if (entrada == NULL) {
				perror("Erro ao abrir o arquivo de entrada");
	     		}
		}
		else if(strcmp(argv[i], "-o") == 0){
			///escrever no arquivo de saida
			tem_saida = true;
			saida = fopen(argv[i+1], "w");
			if (saida == NULL) {
				perror("Erro ao abrir o arquivo de saida");
			}
		}
		else if(strcmp(argv[i],"-r") == 0){
			///gerar matriz eleatoriamente
			eh_randomica = true;
			tamanho_matriz = atoi(argv[i+1]);
			matriz = generateSquareRandomMatrix(tamanho_matriz);
			//descomentar a linha de baixo para ver a matriz eleatoria criada
			//imprimeMatriz(matriz, tamanho_matriz,0,0,0);
		}
		else if(strcmp(argv[i], "-i") == 0){
			///numero de iteracoes do refinamento
			tem_iteracoes = true;
			iteracoes = atoi(argv[i+1]);
		}
	}

	///checando o parametro obrigatorio
	if(!tem_iteracoes){
		printf("Erro: O parametro -i k eh obrigatorio\n");
		printf("O formato da chamada eh:\ninvmat [-e arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
		exit(0);
	}

	///lendo a matriz do arquivo de entrada ou do stdin
	if(tem_entrada && (!eh_randomica)){
		matriz = leMatriz(entrada, &tamanho_matriz);
	} else if ((!tem_entrada) && (!eh_randomica)) {
		matriz = leMatrizStdin(&tamanho_matriz);
	}

	///fazendo a fatoracao L U
	double *L = NULL;
	double *U = NULL;
	double *Inversa = NULL;
	int tam_quadrado = tamanho_matriz*tamanho_matriz;
	//ALOCACAO ANTIGA
	/*if ( ! (L = (double *) malloc(tamanho_matriz*tamanho_matriz*sizeof(double))) ){
		printf("Erro: afalha na alocacao da matriz L, terminando o programa.\n");
		exit(0);
	}*/
	if ( ! (U = (double *) malloc(tam_quadrado*sizeof(double))) ){
		printf("Erro: afalha na alocacao da matriz U, terminando o programa.\n");
		exit(0);
	}
	if ( ! (Inversa = (double *) malloc(tam_quadrado*sizeof(double))) ){
		printf("Erro: afalha na alocacao da matriz I, terminando o programa.\n");
		exit(0);
	}

	//ALOCACAO NOVA, MAIS EFICIENTE, MENOS MEMORIA
	int tamL = tam_quadrado - (((tam_quadrado-tamanho_matriz)/2) + tamanho_matriz);
	if ( ! (L = (double *) malloc(tamL * sizeof(double))) ){
		printf("Erro: afalha na alocacao da matriz L, terminando o programa.\n");
		exit(0);
	}

	int trocas[tamanho_matriz];
	for(int i = 0; i < tamanho_matriz; i++){
		trocas[i] = i;
	}
	double tempo_LU = fatoracaoLU(L, tamL, U, matriz, tamanho_matriz, trocas);
	///testa se inversivel
	if(tempo_LU == -1) {
		printf("Erro: a matriz nao eh inversivel\n");
		exit(1);
	}

	///faz a retrosubstituicao
	double tempo_iter = retrosubstituicao(L, U, Inversa, tamanho_matriz);

	if (tem_saida) {
		fprintf(saida, "#\n");
	} else {
		printf("#\n");
	}

	///chamando a funcao de refinamento
	if (iteracoes > 0) {
		tempo_residuo = refinamento(matriz, L, U, Inversa, tamanho_matriz, iteracoes, saida, tem_saida, &tempo_iter);
	}

	if(tem_saida){
		imprimeMatrizArquivo(Inversa, tamanho_matriz, tempo_LU, tempo_iter, tempo_residuo, saida);
	}
	else{
		imprimeMatriz(Inversa, tamanho_matriz, tempo_LU, tempo_iter, tempo_residuo);
	}

	///fechando os arquivos
	if(tem_entrada == true){
		fclose(entrada);
	}
	if(tem_saida == true){
		fclose(saida);
	}

	free(matriz);
	free(L);
	free(U);
	free(Inversa);
	LIKWID_MARKER_CLOSE;
}
