#import "template.typ": *

#show: project.with(
  university: "Universidade do Minho",
  department: "Departamento de Informática",
  title: "Computação Gráfica",
  subtitle: "Fase 1 - Grupo 59",
  authors: (
    (name: "Carlos Ferreira", number: "a89509"),
    (name: "Gerson Junior", number: "a88000"),
    (name: "Pedro Sousa", number: "a100823"),
    (name: "Pedro Viana", number: "a100701"),
  ),
  date: "March 8, 2024",
)

#pagebreak()

#outline(depth: 3, indent: true)

#pagebreak()

= Introdução

Serve o seguinte relatório para documentar o processo de desenvolvimento da primeira fase do trabalho prático da unidade curricular de Computação Gráfica, do ano letivo 2023/2024.

O objetivo desta fase é a implementação de duas aplicações, o Generator e o Engine. O Generator gera arquivos ".3d" com os dados dos modelos necessários ao Engine para os desenhar. O Engine, por sua vez, lê um arquivo de configuração XML que oferece as configurações da camera e uma listagem dos arquivos ".3d" dos modelos que, por fim, este desenha.

#pagebreak()

= Utils

Foram desenvolvidos alguns modulos com o objetivo de implementar conceitos abtratos como pontos, vectores e modelos.

== Point3

O tipo de dados `Point3` representa um ponto no espaço tridimensional e é implementado como 3 floats, x, y e z.

Objetos do tipo `Point3` são imutáveis, mas é possível obter um novo `Point3` transladado somando estes com um `Vector3` (vetores) ou triplos de `float`s.

== Vector3

O tipo de dados `Vector3` representa um vector no espaço tridimensional e é implementado como 3 `float`s, x, y e z.

Objetos do tipo `Vector3` são imutáveis, mas é possível obter um novo `Vector3` resultante da soma com outro `Vector3` ou da multiplicação por um escalar (`float`). 

== Model

O tipo de dados `Model` representa um modelo 3D composto por um conjunto de pontos. Cada três pontos representam um triângulo.

Este foi implementado como um `std::vector<Point3>`.

Objetos do tipo `Model` podem ser concatenados com outros `Model`, transladados dado um `Vector3`, rodados dados um `Vector3` e um ângulo (`float`), e escalados dado um triplo de `float`s.

É ainda possível desenhar o modelo, escrever para um ficheiro e ler de um ficheiro.

#pagebreak()

= Generator

== Modelos

Cada modelo é implementado como uma classe que extende a classe abstrata `Model` e, no seu construtor, calcula os seus vértices.

Nesta fase do projeto foram definidas 4 primitivas:
- Plano
- Caixa
- Esfera
- Cone

=== Plano

O plano é definido pelo comprimento do seu lado e o número de divisões. Cada divisão é composta por dois triângulos isósceles rectângulos.

Estratégia de cálculo dos vértices:

- Começamos por calcular o comprimento de cada divisão dividindo o comprimento do lado do plano pelo número de divisões.

- O plano é desenhado no plano xOz pelo que o y de todos os seus vértices é 0.

- Como é especificado apenas um comprimento do lado, o plano é quadrado e terá tantas divisões quanto o quadrado do número de divisões do seu lado. Assim, os triângulos destas são calculados em dois cilcos aninhados. Sendo n o número de divisões, o ciclo externo itera n vezes sobre o eixo dos z e o ciclo interno itera n vezes sobre o eixos dos x.

- A cada iteração calculámos as coordenadas dos vértices dos dois triângulos que compõe a divisão e adicionámos estes à lista de vértices do plano pela ordem ditada pela regra da mão direita de forma a que os triângulos estejam direcionados para cima.

=== Caixa

A caixa é definida pelo comprimento do seu lado e o número de divisões. Cada divisão é composta por dois triângulos isósceles rectângulos.

Estratégia de cálculo dos vértices:

- A caixa é definida como a concatenação de 6 planos rodados e transladados para o efeito.

=== Esfera

A esfera é definida por um raio, o número de _slices_ e o número de _stacks_.

Estratégia de cálculo dos vértices:

- Os vértices dos triângulos são calculados _stack_ a _stack_ e depois _slice_ a _slice_, ou seja, a cada iteração são calculados os dois triângulos que formam o quadrilátero correspondente à interseção da _stack_ e _slice_ atual.

- Foi decidido iterar _stack_ a _stack_ de forma a calcular a altura (o y) dos vértices de uma _stack_ apenas uma vez.

- A primeira e última _stack_ da esfera são cálculadas separadamente do resto do modelo pois cada _slice_ destas contém apenas um triângulo evitando incluir triângulos duplicados. Estas são calculadas no mesmo ciclo de forma a reaproveitar o cálculo dos ângulos.

- O cálculo de cada coordenada é feito convertendo coordenadas esféricas, (\u{03B1}, \u{03B2}, _r_) em coordenadas cartesianas do seguinte modo:

$ x = r dot cos(beta) dot sin(alpha) \
  y = r dot sin(beta) \
  z = r dot cos(beta) dot cos(alpha) $

=== Cone

O cone é definido pelo raio da base, a sua altura e o número de _slices_ e _stacks_ do próprio cone.

Estratégia de cálculo dos vértices:

- Similarmente à esfera, os vértices são calculados _stack_ a _stack_ e a ponta (última _stack_) é calculada separadamente de forma a evitar incluir triângulos duplicados.

== Sintaxe ficheiros .3d

Os ficheiros ".3d" são ficheiros binários de forma a minimizar o tamanaho e o tempo de leitura e escrita destes.

Estes contém apenas as coordenadas de cada vértice do modelo. Cada 3 vértices representam um triângulo.

As coordenadas são representadas por floats pelo que cada uma ocupa 4 bytes. Assim, um plano com uma divisão ocupa 72 bytes ($2 "triângulos" * 3 "vértices" * 3 "coordenadas" * 4 "bytes"$).

#pagebreak()

= Engine

Nesta fase foi desenvolvido um motor 3D capaz de posicionar e orientar a camera e desenhar múltiplos modelos compostos por triângulos.

Este motor começa por ler um ficheiro XML cujo nome é passado como primeiro argumento do programa. Este ficheiro contém os dados da camera a definir e uma lista de modelos a desenhar.

São ainda desenhados os eixos x, y e z com cores vermelho, verde e azul, respetivamente, de forma a mais facilmente identificar a posição dos modelos desenhados.

Foram também definidos alguns controlos para controlar a camera.

== Parsing de XML

Para o parsing do ficheiro _XML_ foi usada a biblioteca #link("https://github.com/leethomason/tinyxml2")[TinyXML2]

Nesta fase a implementação do parsing foi feita de forma mais simples possível deixando todo o código na função do _engine_ e iniciando múltiplas variáveis globais, em particular, os modelos são carregados para um `vector<Model>`. Posteriormente, o parsing será encapsulado na seu próprio módulo.

== Desenho dos Modelos

Para desenhar os modelos itera-se sobre o vetor de `Model` e chama-se o método `draw()` a cada modelo. Este método desenha um triângulo com cada 3 vértices no modelo.

== Câmara

As propriedades da camera são definidas pelos dados contidos no ficheiro XML, porém também foi incluída a possibilidade de mover a camera no estilo "terceira pessoa" após esta ser definida com os seguintes controlos:

- W - subir
- S - descer
- A - esquerda
- D - direita
- J - zoom in
- K - zoom out

O shift é usado como modificador para executar as mesmas ações 10 vezes mais depressa.

Para a execução destas funcionalidades, o programa recorre a dois ângulos (`yaw` e `pitch`).

Estes são calculados logo após ao parse do ficheiro xml, utilizando os valores da posição da câmara e da posição para onde está a 'olhar'.
O yaw é o ângulo em torno do eixo y, e o `pitch` é o ângulo em torno do eixo do z.

O movimento baseia-se na incrementação ou decrementação do valor destes ângulos, dependendo da tecla pressionada

#pagebreak()

= Conclusão

Nesta fase do projeto foi possível identificar e desenvolver estratégias de cálculo e representação de simples modelos 3D compostos por triângulos.

Considera-se que nesta fase foi possível consolidar os básicos do desenvolvimento de software com Glut/OpenGL assim como o uso de trignometria e C++ para codificar o cálculo de pontos no espaço e a regra da mão direita para construir triângulos direcionados para o lado pretendido.

Assim, o grupo considera ser agora capaz de implementar outras primitivas como o torus.

Contudo, o trabalho feito nesta fase pode ainda ser desenvolvido, por exemplo, implementando uma abstração de coordenadas polares simplificando assim o cálculo de coordenadas na construção do cone e da esfera.

É ainda possível melhorar a performance do projeto, porém considerou-se que nesta fase era mais valioso apontar para um bom balanço entre simplicidade e performance, mas, em fases seguintes, performance será uma maior preocupação do grupo.