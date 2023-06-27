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
O termo [esteganografia](https://www.gta.ufrj.br/grad/09 1/versao-final/stegano/introducao.html) deriva da junção das palavras gregas estegano que significa “esconder ou mascarar”, e grafia, que significa “escrita”. Portanto, esteganografia pode ser compreendida como a arte de esconder informações, tornando-as ocultas, assim como a criptografia. O
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
1. Um arquivo est´a escondido na imagem .PPM. O arquivo escondido est´a codificado nos
pixels da imagem da seguinte forma:
 o bin´ario dos c´odigos ASCII do nome original do arquivo (finalizado pelo caracter
zero)
 o bin´ario do tamanho do arquivo (em quatro bytes)
 e os bytes do arquivo.
