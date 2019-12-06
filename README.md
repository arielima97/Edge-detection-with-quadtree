# Edge-detection-with-quadtree
Projeto final de Estrutura de dados e Algoritmos - Detectando bordas de imagem usando quadtrees.

Autor: Ariel Lima Andrade

Utilizando a estrutura de dados de árvores quarternárias com os dados dos pontos do quadrante da imagem, utilizei o algoritmo de DFS para buscar as bordas. Para idenficar uma borda eu determinava o tamanho da área de detecção e caso a média de cor dessa área fosse diferente de preto ou branco isso significa que esta área possui uma borda (mudança de cor). Com isso utilizei as informações dos pontos dessas pequenas áreas para desenhar, resultando no contorno da imagem.

Ao executar o programa:

- Pressione 1 para visualizar a estrutura quadtree na imagem.
- Pressione 2 para visualizar as bordas com o fundo preto.
- Pressione 3 para visualizar as bordas com o fundo branco.
- Pressione Q para visualizar as bordas com o fundo branco.
- Pressione + para aumentar tamanho da borda.
- Pressione - para aumentar tamanho da borda.

Github do projeto: https://github.com/arielima97/Edge-detection-with-quadtree

