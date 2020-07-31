# Random-String

Dada uma string inicial, nosso objetivo é replicá-la através dos conceitos e teorias de algoritmos genéticos.
Inicialmente, criamos uma string aleatória de mesmo número de caracteres da string objetivo, e partimos dela para chegar ao resultado.

Os caracteres da string são considerados como genes, sendo contemplados A-Z, a-z, 0-9 e  alguns outros caracteres especiais, como "?,!" e etc.
Cada iteração, isto é, cada geração, possui indivíduos com o melhor fitness, que é medido pela diferença da quantidade de caracteres corretos, e na posição correta, entre a string objetivo e a string gerada aleatoriamente.

São utilizados os conceitos de crossover, mutation e survival of the fittest para a obtermos a solução.

Para executar o código, basta compilar o arquivo RandomString.cpp e executar o arquivo executável gerado.

Exemplo para Linux:
 g++ -o RandomString.cpp
 ./RandomString
