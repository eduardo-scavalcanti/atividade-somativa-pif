#include <stdio.h>
#include <string.h>

#define ARQUIVO "contas.dat"

int existemClientesCadastrados(FILE *fp);

typedef struct {
    int numeroConta;
    char nome[50];
    double saldo;
} Cliente;

int main()
{
    FILE *fp = fopen(ARQUIVO, "r+b");
    if (fp == NULL)
    {
        fp = fopen(ARQUIVO, "w+b");
    }

    int opcao;
    do
    {
        printf("\n1. Cadastrar cliente\n");
        printf("2. Consultar cliente\n");
        printf("3. Atualizar saldo\n");
        printf("4. Encerrar conta\n");
        printf("5. Listar clientes\n");
        printf("6. Reiniciar leitura\n");
        printf("7. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            long pos;
            Cliente c;
            printf("Posicao: ");
            scanf("%ld", &pos);
            printf("Numero da conta: ");
            scanf("%d", &c.numeroConta);
            printf("Nome: ");
            scanf("%*c%49[^\n]", c.nome);
            printf("Saldo: ");
            scanf("%lf", &c.saldo);

            fseek(fp, pos * sizeof(Cliente), SEEK_SET);
            fwrite(&c, sizeof(Cliente), 1, fp);
            printf("Cliente cadastrado!\n");
        }

        else if (opcao == 2)
        {
            if (!existemClientesCadastrados(fp))
            {
                printf("Nao existem clientes cadastrados.\n");
            }
            else
            {
                int conta;
                printf("Numero da conta: ");
                scanf("%d", &conta);

                fseek(fp, 0, SEEK_END);
                long total = ftell(fp) / sizeof(Cliente);

                int encontrado = 0;
                for (long i = 0; i < total; i++)
                {
                    Cliente c;
                    fseek(fp, i * sizeof(Cliente), SEEK_SET);
                    fread(&c, sizeof(Cliente), 1, fp);
                    if (c.numeroConta == conta)
                    {
                        printf("Conta: %d\n", c.numeroConta);
                        printf("Nome: %s\n", c.nome);
                        printf("Saldo: %.2f\n", c.saldo);
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) 
                {
                    printf("Conta nao encontrada.\n");
                }
            }
        }

        else if (opcao == 3)
        {
            if (!existemClientesCadastrados(fp))
            {
                printf("Nao existem clientes cadastrados.\n");
            } 
            else
            {
                int conta;
                printf("Numero da conta: ");
                scanf("%d", &conta);

                fseek(fp, 0, SEEK_END);
                long total = ftell(fp) / sizeof(Cliente);

                int encontrado = 0;
                for (long i = 0; i < total; i++)
                {
                    Cliente c;
                    fseek(fp, i * sizeof(Cliente), SEEK_SET);
                    fread(&c, sizeof(Cliente), 1, fp);
                    if (c.numeroConta == conta)
                    {
                        printf("Novo saldo: ");
                        scanf("%lf", &c.saldo);
                        fseek(fp, i * sizeof(Cliente), SEEK_SET);
                        fwrite(&c, sizeof(Cliente), 1, fp);
                        printf("Saldo atualizado!\n");
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) 
                {
                    printf("Cliente nao encontrado.\n");
                }
            }
        }

        else if (opcao == 4) 
        {
            if (!existemClientesCadastrados(fp)) 
            {
                printf("Nao existem clientes cadastrados.\n");
            } 
            else 
            {
                int conta;
                printf("Numero da conta: ");
                scanf("%d", &conta);

                fseek(fp, 0, SEEK_END);
                long total = ftell(fp) / sizeof(Cliente);

                int encontrado = 0;
                for (long i = 0; i < total; i++) 
                {
                    Cliente c;
                    fseek(fp, i * sizeof(Cliente), SEEK_SET);
                    fread(&c, sizeof(Cliente), 1, fp);
                    if (c.numeroConta == conta) 
                    {
                        memset(&c, 0, sizeof(Cliente));
                        fseek(fp, i * sizeof(Cliente), SEEK_SET);
                        fwrite(&c, sizeof(Cliente), 1, fp);
                        printf("Conta encerrada!\n");
                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) 
                {
                    printf("Cliente nao encontrado.\n");
                }
            }
        }

        else if (opcao == 5) 
        {
            if (!existemClientesCadastrados(fp)) 
            {
                printf("Nao existem clientes cadastrados.\n");
            } 
            else 
            {
                fseek(fp, 0, SEEK_END);
                long total = ftell(fp) / sizeof(Cliente);

                rewind(fp);
                for (long i = 0; i < total; i++) 
                {
                    Cliente c;
                    fread(&c, sizeof(Cliente), 1, fp);
                    
                    if (c.numeroConta != 0) 
                    {
                        printf("Conta: %d | Nome: %s | Saldo: %.2f\n", c.numeroConta, c.nome, c.saldo);
                    }
                }
            }
        }

        else if (opcao == 6) 
        {
            rewind(fp);
            printf("Leitura reiniciada!\n");
            
            fseek(fp, 0, SEEK_END);
            long total = ftell(fp) / sizeof(Cliente);

            rewind(fp);
            for (long i = 0; i < total; i++) 
            {
                Cliente c;
                fread(&c, sizeof(Cliente), 1, fp);
                
                if (c.numeroConta != 0) 
                {
                    printf("Conta: %d | Nome: %s | Saldo: %.2f\n", c.numeroConta, c.nome, c.saldo);
                }
            }
            
        }

    } while (opcao != 7);

    fclose(fp);
    return 0;
}

int existemClientesCadastrados(FILE *fp) 
{
    fseek(fp, 0, SEEK_END);
    long total = ftell(fp) / sizeof(Cliente);

    for (long i = 0; i < total; i++) 
    {
        Cliente c;
        fseek(fp, i * sizeof(Cliente), SEEK_SET);
        fread(&c, sizeof(Cliente), 1, fp);
        
        if (c.numeroConta != 0) 
        {
            return 1;
        }
    }
    return 0;
}
