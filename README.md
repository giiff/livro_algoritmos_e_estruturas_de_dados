# Algoritmos e Estruturas de Dados
## Tecnólogo em Análise e Desenvolvimento de Sistemas
## Waldeyr Mendes Cordeiro da Silva 

Este é um livro em construção. 

Sua finalidade é prover material didático orientado para o perfil de tecnólogos nas áreas de T.I. que necessitam de aprender programação básica e estruturas de dados.

## Como obter os códigos deste repositório ?

Os códigos, em geral, estão em C (padrão C17), em `Code/C`. Há também implementações em Python 3, em `Code/Python`.

### Primeira vez que vai baixar o repositório ?

* No terminal de seu Linux, escolha e acesse a pasta de trabalho e digite/cole:
```console
git clone https://github.com/giiff/livro_algoritmos_e_estruturas_de_dados.git
```

### Já tem o repositório na máquina e quer baixar as últimas atualizações ?

* No terminal de seu Linux, acesse a pasta de trabalho e digite/cole:
```console
git pull
```

## Como instalar o compilador C/C++ em meu computador?

* No terminal de seu Linux Ubuntu, Mint ou outros derivados de Debian digite/cole:
```console
sudo apt install build-essential gcc
```

* No terminal de seu Linux Fedora ou outros derivados de Red Hat digite/cole:
```console
sudo dnf install gcc gcc-c++
```

* No Windows, siga os passos do tutorial abaixo:
[How to install C++ on Windows](https://preshing.com/20141108/how-to-install-the-latest-gcc-on-windows)


## Como compilar meu código fonte?
* No terminal de seu Linux digite/cole:
```console
gcc -Wall meu_programa.c -o meu_executavel
```
A opção `-Wall` mostra os avisos do compilador, que ajudam a encontrar erros.

## Como executar meu programa compilado ?
* No terminal de seu Linux digite/cole:
```console
./meu_executavel
```

## Como compilar o livro e testar os exemplos?

Na raiz do repositório:

```console
make livro          # gera o PDF (requer TeX Live, biber e latexmk)
make exemplos       # compila todos os exemplos em C em build/exemplos
make testes         # testa os exemplos em C e em Python
```

Para os testes em Python, instale as dependências com `pip install -r requirements.txt`.

O plano de atualização do livro está em [PLANO_DE_ATUALIZACAO.md](PLANO_DE_ATUALIZACAO.md).

# Usando o GIT: 

Como gerenciar o SEU PRÓPRIO repositório?

## Como criar um repositório novo?

Na página do GitHub, use o botão **New repository**, escolha um nome e confirme em **Create repository**.

## Primeira vez que vai baixar o repositório ?

* No terminal de seu Linux, escolha e acesse a pasta de trabalho e digite/cole:
```console
git clone https://github.com/waldeyr/meurepositorio.git
```

## Já tem o repositório na máquina e quer baixar as últimas atualizações ?

* No terminal de seu Linux, acesse a pasta de trabalho e digite/cole:
```console
git pull
```

## Como adicionar arquivos que eu alterei ou criei?

`git add <arquivo.c>`

## Como confirmar as alterações antes do upload?

`git commit -m "Uma mensagem de amor pela programação de computadores"`

## Como fazer o upload?

`git push origin master`
