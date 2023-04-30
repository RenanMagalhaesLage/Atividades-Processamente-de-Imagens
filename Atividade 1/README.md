#### Universidade Federal de Alfenas - UNIFAL-MG
Bacharelado em Ciência da Computação

Prof. [Luiz Eduardo da Silva](https://github.com/luizedsilva)

<hr>
<div align="center">
<h1>Trabalho de Processamento de Imagem</h1>
    <p>Atividade 1 - Arte ASCII</p>
</div>

## Objetivo
O objetivo desse atividade é explorar os conceitos iniciais da disciplina de processamento de imagens como: vizinhança dos pixels, amostragem e quantização.

## Problema
As imagens feitas com caracteres ASCII, também conhecidas como arte ASCII ou arte de
texto, têm uma história longa e rica que remonta ao início da computação pessoal. A técnica de usar caracteres ASCII para criar imagens foi desenvolvida no início dos anos
60, logo após a introdução dos primeiros terminais de computador. Esses terminais eram basicamente máquinas de escrever eletrônicas que podiam ser usadas para interagir com os
mainframes da época. Como os monitores eram em preto e branco e de baixa resolução, os usuários come¸caram a experimentar com o uso de caracteres ASCII para criar desenhos e
imagens na tela.
Nos anos 70, quando a computação pessoal come¸cou a se popularizar, a arte ASCII se tornou uma forma popular de expressão artística. Programadores e entusiastas come¸caram a
criar imagens de personagens de jogos de vídeo game, paisagens, retratos e outros temas usando
caracteres ASCII. As imagens geralmente eram criadas manualmente, digitando-se linhas e linhas de caracteres em um editor de texto.
Nos anos 80, a arte ASCII tornou-se ainda mais popular com o surgimento dos BBSs (Bulletin Board Systems), que eram sistemas de mensagem que permitiam que os usuários se conectassem a partir de seus próprios computadores e compartilhassem mensagens, jogos e outros
conteúdos. Os BBSs eram frequentemente decorados com arte ASCII feita por usuários, dandolhes uma aparência única e pessoal.
Nos anos 90, a popularidade da arte ASCII diminuiu um pouco, à medida que a tecnologia
gráfica melhorou e os usuários passaram a preferir imagens coloridas e de alta resolução. No
entanto, a arte ASCII permaneceu uma forma de expressão artística popular entre alguns artistas e comunidades online.
Hoje em dia, a arte ASCII continua sendo uma forma de expressão artística única e distinta,
e é frequentemente usada em fóruns de discussão online, mensagens de texto e outras formas de
comunicação digital. Embora possa parecer limitada pela sua simplicidade, a arte ASCII pode ser surpreendentemente complexa e bonita, e continua a encantar e inspirar pessoas de todo o mundo.

## Descrição
1. Nessa atividade você deverá construir uma ferramenta que a partir de uma imagem em tons de cinza (PGM), produza a imagem usando caracteres ASCII como tons de cinza.
2. O usuário desse programa deverá informar a imagem, o número de colunas e linhas da imagem ASCII que será gerada (amostragem) e o string de caracteres para codificar os
tons de cinza (quantização).
3. O programa deverá gerar um arquivo de nome "result.txt" com a imagem ASCII, codificando os pixels da imagem dada com os caracteres informados no string.
4.  O programa deverá ser chamado em linha de comando da seguinte forma:

```bash
./ a s c i i <nome_arquivo_imagem> <ncolunas> <nlinhas> <string>[.pgm ]
```
Por exemplo :
```bash
./ascii cao.pgm 100 30 ”@$#*%o!=+;:˜= ,. ”
```

## Entrada
![Captura de Tela (10)](https://user-images.githubusercontent.com/89847080/235377167-7f62db0e-b3e1-4c7b-8f48-0d719e658cdb.png)


## Saída
![Captura de Tela (12)](https://user-images.githubusercontent.com/89847080/235377201-14799914-86ec-49df-9333-b1b575461f75.png)

