#Parsers 

Este diretório contém três parsers desenvolvidos para três diferentes tracks: Óptima, Satisfy, e Agile. Cada parser é adaptado para resolver problemas específicos no domínio de planejamento automático usando o Fast Downward Planner.

## Tracks

### Óptima
A track Óptima foca em encontrar soluções ótimas para problemas de planejamento. Este parser é configurado para explorar exaustivamente o espaço de busca até encontrar a solução de menor custo possível. O objetivo principal é garantir que a solução encontrada seja a melhor dentre todas as possíveis.

### Satisfy
A track Satisfy é projetada para encontrar uma solução viável para o problema de planejamento, sem a necessidade de ser a solução de menor custo. Este parser prioriza a rapidez e eficiência na geração de soluções válidas, atendendo aos requisitos do problema sem necessariamente otimizar o custo.

### Agile
A track Agile se concentra em encontrar soluções rápidas e eficientes, balanceando entre a qualidade da solução e o tempo de processamento. Este parser é ideal para situações onde é necessário obter soluções boas o suficiente em um tempo curto, sendo uma abordagem intermediária entre as tracks Óptima e Satisfy.


