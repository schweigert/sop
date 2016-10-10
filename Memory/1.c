#include <stdio.h>

unsigned int sum (unsigned int x, unsigned int y){
	unsigned int sum, carry;
    sum = x ^ y;
    carry = x & y;
    while (carry != 0) {
        carry = carry << 1;
        x = sum;
        y = carry;
        sum = x ^ y;
        carry = x & y;
    }
}

unsigned int pow2(unsigned int a){
	return 1<<a;
}

int main(int argc, char **argv)
{
	/* Argumentos:
	 * argv[0]: Tamando do endereço físico (em bits)
	 * argv[1]: Tamanho do endereço lógico (em bits)
	 * argv[2]: número de bits de deslocamento
	 */
	 
	 
	unsigned int enderecamentoFisico;
	unsigned int enderecamentoLogico;
	unsigned int tamanhoPagina;
	unsigned int numPaginasFisicas;
	unsigned int numEntradasDaTabelaPagina;
	unsigned int tamanhoTabelaPaginas;
	
	
	
	return 0;
}

