#### Universidade Federal de Alfenas - UNIFAL-MG
Bacharelado em Ciência da Computação

Prof. [Luiz Eduardo da Silva](https://github.com/luizedsilva)

<hr>
<div align="center">
<h1>Trabalho de Processamento de Imagem</h1>
    <p>Atividade 1 - Arte ASCII</p>
</div>

## Objetivo
O objetivo desse atividade é explorar os conceitos de cores e de codificação e decodificação utilizados nos formatos de imagens.

## Problema
O termo [esteganografia](https://www.gta.ufrj.br/grad/09\-1/versao-final/stegano/introducao.html) deriva da junção das palavras gregas estegano que significa “esconder ou mascarar”, e grafia, que significa “escrita”. Portanto, esteganografia pode ser compreendida como a arte de esconder informações, tornando-as ocultas, assim como a criptografia. O
objetivo desta técnica é que esses dados não sejam percebidos por terceiros; ou seja, a presen¸ca
de mensagens escondidas dentro de arquivos é simplesmente desconhecida. Somente o receptor
da mensagem tem conhecimento de sua existência, assim como da maneira como extraí-la.
Apesar de parecer, a esteganografia e a criptografia são duas áreas com objetivos bastante
diferentes. Enquanto o segundo tem o propósito de impedir que as pessoas saibam o conteúdo
de uma mensagem, o primeiro se baseia em evitar que as pessoas saibam que a mensagem
escondida existe. Ou seja, na criptografia, os receptores sabem da existência das mensagens,
porém não conseguem, a princípio, lê-las; a esteganografia tenta fazer com que os receptores
não percebam que há uma mensagem naquele meio (imagem, texto, etc.). Existem várias formas de esconder mensagens ou arquivos em imagens. Uma das técnicas
possíveis é modificar alguns bits (menos relevantes) dos pixels da imagem, com as informações
que se quer esconder. Por exemplo, a modificação do bit menos significativo de uma banda (red) de um pixel de uma imagem colorida não é perceptível ao olho humano. A esteganoanálise
dessa modificação, no entanto, não é difícil de se realizar a partir da comparação do arquivo
original e do arquivo modificado. O ruído, calculado como a diferençaa desses dois arquivos é a mensagem codificada.
O objetivo desse trabalho é completar o código disponível nesta atividade para realizar a decodificação de um arquivo que foi esteganografado na imagem.

## Descrição

- [x] Um arquivo está escondido na imagem <b>.PPM</b>. O arquivo escondido está codificado nos pixels da imagem da seguinte forma:
    - o binário dos códigos ASCII do nome original do arquivo (finalizado pelo caracter zero)
    - o binário do tamanho do arquivo (em quatro bytes)
    - e os bytes do arquivo.

- [x] Os bits (zero ou um) das representações binárias estão armazenados, modificando as bandas R,G e B dos pixels em sequência. Por exemplo, considerando a imagem colorida:
      
![tabela](https://github.com/RenannLage/Atividades-Processamente-de-Imagens/assets/89847080/bc9912fa-6bc9-43e2-860b-bacd188c1b1d)

Seja 'A', a primeira letra do nome do arquivo (cujo código ASCII binário é 01000001). Na codificação do arquivo, a letra 'A' modifica as seguintes bandas dos pixels iniciais (identificados em letras maiúsculas e com cores).

![tabela2](https://github.com/RenannLage/Atividades-Processamente-de-Imagens/assets/89847080/7431e2c7-7ce1-44c1-8856-7711e5f511e9)

Onde:
    R1 = r1 & 0xF E, codifica o bit zero (0)
    
    G2 = g2 | 0x01, codifica o bit um (1)
    
    B3 = b3 & 0xF E, codifica o bit zero (0)
    
    R4 = r4 & 0xF E, codifica o bit zero (0)
    
    G5 = g5 & 0xF E, codifica o bit zero (0)
    
    B6 = b6 & 0xF E, codifica o bit zero (0)
    
    R7 = r7 & 0xF E, codifica o bit zero (0)
    
    G8 = g8 | 0x01, codifica o bita um (1)

- [x] A operação R1 = r1 & 0xF E, que executa um e-bit-a-bit com a máscara 0xF E, tem o efeito de transformar o último bit da banda R para zero.
- [x] De forma simétrica, a operação G2 = g2 | 0x01 , que executa um ou-bit-a-bit com a máscara 0x01, tem o efeito de transformar o último bit da banda G para um e assim sucessivamente.
- [x] Depois da codificação do nome do arquivo, os quatro bytes seguintes definem a quantidade de bytes do arquivo, e dessa forma, a quantidade de pixels que estão modificados no restante da imagem.

![imgexemplo](https://github.com/RenannLage/Atividades-Processamente-de-Imagens/assets/89847080/4387ad81-3854-455d-88c6-b79497604d30)

Para incluir o arquivo de nome 'A.txt', com os seguintes 2 bytes:

42

Cuja codificação (nome, tamanho e os bytes) em binário é:

![sdasdad](https://github.com/RenannLage/Atividades-Processamente-de-Imagens/assets/89847080/b72621de-45d3-4354-93d6-098a279c60ac)

- [x] Pode-se observar ainda que, considerando esse esquema de codificação, para que um arquivo possa ser escondido numa imagem, o número de pixels da imagem deve ser suficiente
para a codificação do arquivo. Sejam:
    - TN (Tamanho do Nome) = o número de letras do nome do arquivo somado de um (caracter zero no fim do nome);
    - TA (Tamanho do arquivo) = quatro bytes usados para codificar o tamanho do arquivo;
    - NB (Número de bytes) = número de bytes do arquivo a ser ocultado;
    - nlinhas = número de linhas da imagem;
    - ncolunas = número de colunas da imagem.

Assim, o arquivo só pode ser esteganografado na imagem se:

![numero](https://github.com/RenannLage/Atividades-Processamente-de-Imagens/assets/89847080/be557a13-7e69-4b61-b3c6-5081b72b99b6)

- [x] No exemplo anterior, TN = 6, TA = 4, NB = 2, o que soma 12 * 8 pixels que foram afetados, ou seja, 96 pixels da imagem com 100 pixels (10 linhas e 10 colunas) foram modificados para codificar o arquivo.
- [x] Considerando esse esquema de codificação do arquivo na imagem, a sua tarefa é desenvolver o decodificador. O código a ser completado está disponível junto com a atividade.
Este programa deve receber o nome do arquivo da imagem, extrair e gerar (em disco) o arquivo que está escondido.






