#include <stdio.h>
#include <string.h>

#pragma pack(1)

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char**argv)
{
	FILE *x;
	Endereco e;
	int y, qt;
	int primeiro, meio, ultimo, atual;

	x = fopen("cep_ordenado.dat","r"); // O arquivo esta sendo procurado
	if(!x)
	{
		printf("O arquivo nao pode ser aberto\n"); // O arquivo nao foi encontrado
		return 1;
	}
	else{
        printf("O arquivo foi aberto com sucesso\n"); // O arquivo foi aberto
	}

    fseek(x,0,SEEK_END); // Direcionando a leitura para o ultimo byte
    atual = ftell(x); // Para descobrir o numero de bytes
    rewind(x); // Retornando para o primeiro byte
    primeiro = 0;
    ultimo = (atual/sizeof(Endereco))-1;
    meio = (primeiro+ultimo)/2;

    fseek(x,meio*sizeof(Endereco),SEEK_SET);
    qt = fread(&e, sizeof(Endereco),1,x);
    y = 0;

        while(strncmp(argv[1],e.cep,8)!=0)
        {
            if(strncmp(argv[1],e.cep,8)<0)
            {
                ultimo = meio-1;
                meio = (primeiro + ultimo)/2;
                fseek(x,meio * sizeof(Endereco),SEEK_SET);
            }
            else
            {
                primeiro = meio+1;
                meio = (primeiro + ultimo)/2;
                fseek(x,meio * sizeof(Endereco),SEEK_SET);
            }
            qt = fread(&e, sizeof(Endereco),1,x);
        }
        printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);

    fclose(x);
	return 0;
}
