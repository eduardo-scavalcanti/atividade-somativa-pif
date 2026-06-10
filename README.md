# Sistema de Manutenção de Contas Bancárias em C

Trabalho da disciplina de Linguagem de Programação — 2° período ADS.

## O que o programa faz

Sistema de cadastro de clientes bancários usando arquivo binário. O usuário interage por um menu com 7 opções:

1. Cadastrar um novo cliente em uma posição específica
2. Consultar um cliente pelo número da conta
3. Atualizar o saldo de um cliente
4. Encerrar conta
5. Listar todos os clientes
6. Reiniciar a leitura do arquivo com `rewind()`
7. Sair

## Como compilar e executar

```bash
gcc -o contas contas.c
./contas
```

## Estrutura do registro

Cada cliente é armazenado em uma struct de tamanho fixo:

```c
typedef struct {
    int numeroConta;
    char nome[50];
    double saldo;
} Cliente;
```

Por ter tamanho fixo, é possível ir direto a qualquer posição do arquivo usando `fseek()`.

## Funções usadas

- `fseek()` — para acessar uma posição específica no arquivo
- `fread()` — para ler um registro do arquivo
- `fwrite()` — para gravar um registro no arquivo
- `rewind()` — para voltar o ponteiro ao início do arquivo
- `existemClientesCadastrados()` — função auxiliar para verificar se há clientes no arquivo

## Remoção de conta

Quando uma conta é encerrada, o registro não é apagado fisicamente. O programa usa `memset` para zerar todos os bytes daquele registro, fazendo `numeroConta` virar `0`. Na listagem, registros com `numeroConta == 0` são ignorados.

## Organização do código

O código segue a estrutura padrão C:
- Includes e defines no topo
- Protótipo da função auxiliar
- Definição da struct
- Função main
- Implementação das funções auxiliares no final

## Função auxiliar

### `existemClientesCadastrados(FILE *fp)`

Função criada para verificar se há clientes cadastrados no arquivo, evitando duplicação de código. 

- **Parâmetro**: Ponteiro para o arquivo binário
- **Retorno**: 1 se existirem clientes ativos, 0 se não existirem
- **Uso**: Chamada nas opções 2, 3, 4, 5 e 6 antes de executar operações

## Tratamento de erros

O programa inclui verificações para:

- **Operações com arquivo vazio**: Nas opções 2, 3, 4, 5 e 6, o programa verifica se existem clientes cadastrados antes de executar a operação. Se não houver, exibe "Não existem clientes cadastrados."
- **Conta inexistente**: Nas opções 2, 3 e 4, se o número da conta digitado não for encontrado, exibe "Cliente não encontrado."

## Arquivo gerado

O programa cria automaticamente o arquivo `contas.dat` na primeira execução. Os dados ficam salvos entre execuções.
