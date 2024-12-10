import random

def gerar_caso_teste(num_rochas, nome_arquivo):
    """Gera um caso de teste para o problema da mochila com múltiplas sondas."""

    with open(nome_arquivo, "w") as arquivo:
        arquivo.write(f"{num_rochas}")

        for _ in range(num_rochas):
            peso = random.randint(1, 40)  # Peso entre 1 e 40 (inclusive)
            valor = random.randint(1, 30) # Valor entre 1 e 150 (inclusive) - ajuste conforme necessário
            arquivo.write(f"\n{peso} {valor}")

    print(f"Caso de teste '{nome_arquivo}' gerado com sucesso.")


if __name__ == "__main__":
    gerar_caso_teste(20, "teste20.txt")
    gerar_caso_teste(25, "teste25.txt")