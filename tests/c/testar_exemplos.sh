#!/usr/bin/env bash
# Compila e executa todos os exemplos em C do livro.
# - compila com avisos tratados como erros e com AddressSanitizer/UBSan;
# - executa cada programa com a entrada de tests/c/entradas/<nome>.txt (se existir);
# - compara a saida com tests/c/esperado/<nome>.txt (se existir), ignorando
#   enderecos de memoria e a linha de tempo de execucao.
# Uso: tests/c/testar_exemplos.sh [--atualizar]
set -u
RAIZ="$(cd "$(dirname "$0")/../.." && pwd)"
TESTES="$RAIZ/tests/c"
CC="${CC:-gcc}"
CFLAGS="${CFLAGS:--std=c17 -Wall -Wextra -Wpedantic -Werror -g -fsanitize=address,undefined -fno-omit-frame-pointer}"
SAIDA="$(mktemp -d)"
trap 'rm -rf "$SAIDA"' EXIT
export ASAN_OPTIONS="detect_leaks=1:abort_on_error=1"
export UBSAN_OPTIONS="halt_on_error=1:print_stacktrace=1"

ATUALIZAR=0
[ "${1:-}" = "--atualizar" ] && ATUALIZAR=1

normalizar() {
    sed -E -e 's/0x[0-9a-fA-F]+/ENDERECO/g' -e 's/\(nil\)/ENDERECO_NULO/g' -e '/^Tempo: /d'
}

falhas=0
total=0
while IFS= read -r fonte; do
    nome="$(basename "$fonte" .c)"
    total=$((total + 1))
    exe="$SAIDA/$nome"
    if ! "$CC" $CFLAGS "$fonte" -o "$exe" 2> "$SAIDA/$nome.cc"; then
        echo "FALHA (compilacao) $fonte"; cat "$SAIDA/$nome.cc"; falhas=$((falhas + 1)); continue
    fi
    entrada="$TESTES/entradas/$nome.txt"
    [ -f "$entrada" ] || entrada=/dev/null
    if ! (cd "$SAIDA" && timeout 20 "$exe" < "$entrada" > "$SAIDA/$nome.out" 2> "$SAIDA/$nome.err"); then
        echo "FALHA (execucao) $fonte"; cat "$SAIDA/$nome.err"; falhas=$((falhas + 1)); continue
    fi
    esperado="$TESTES/esperado/$nome.txt"
    if [ "$ATUALIZAR" = 1 ]; then
        normalizar < "$SAIDA/$nome.out" > "$esperado"
    elif [ -f "$esperado" ]; then
        if ! diff -u "$esperado" <(normalizar < "$SAIDA/$nome.out") > "$SAIDA/$nome.diff"; then
            echo "FALHA (saida) $fonte"; cat "$SAIDA/$nome.diff"; falhas=$((falhas + 1)); continue
        fi
    fi
    echo "ok   $fonte"
done < <(find "$RAIZ/Code/C" -name '*.c' | sort)

# Testes unitarios dos algoritmos de ordenacao
total=$((total + 1))
if "$CC" $CFLAGS -I"$RAIZ/Code/C/Ordenacao" "$TESTES/teste_ordenacao.c" -o "$SAIDA/teste_ordenacao" \
    && "$SAIDA/teste_ordenacao"; then
    echo "ok   tests/c/teste_ordenacao.c"
else
    echo "FALHA tests/c/teste_ordenacao.c"; falhas=$((falhas + 1))
fi

echo "$((total - falhas))/$total testes passaram."
[ "$falhas" -eq 0 ]
