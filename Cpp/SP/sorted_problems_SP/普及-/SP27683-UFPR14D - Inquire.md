---
title: "UFPR14D - Inquire"
layout: "post"
diff: 普及-
pid: SP27683
tag: []
---

# UFPR14D - Inquire

## 题目描述

**(EN:)**

Every tourist visiting our city must visit the May 4 avenue. There are **N** houses, numbered from 1 to **N**. There are **P** $ _{i} $ people living at house _i_.

The statistic institute is procedding with the survey this year. They will make many queries about the avenue's population. For each query, two numbers **A** and **B**, with **A** <= **B**, are given. You must determine the total number of people living in all houses from house **A** to house **B**, inclusive.

## 输入格式

First line contains the number **N** (1 <= **N** <= 10 $ ^{5} $ ). Second line contains **N** integers **P** $ _{1} $ , **P** $ _{2} $ , ..., **P** $ _{N} $ , indicating how many people live at each house (for each 1 <= i <= **N**, 0 <= **P** $ _{i} $ <= 100). Next line contains the integer **Q** (1 <= **Q** <= 10 $ ^{4} $ ), the number of queries to be processed. Each of the next **Q** lines describes a query with two integers **A** and **B** (1 <= **A** <= **B** <= **N**).

## 输出格式

For each query, print a line with its result.

**(PT-BR:)**

Todo turista que visita a cidade deve conhecer a Avenida Quatro de Maio. Há **N** casas na avenida, numeradas sequencialmente de 1 a **N**. Há **P** $ _{i} $ pessoas morando na casa de número _i_ da avenida.  
  
O instituto de estatística está realizando o censo deste ano. Para tal, o instituto irá realizar diversas consultas sobre a população da avenida. Em cada consulta, são dados dois números **A** e **B**, com **A** <= **B**. Para cada consulta, é necessário determinar o número total de pessoas que moram entre as casas **A** e **B**, inclusive.  
  
Sua tarefa é, dada a população de cada casa e as consultas que o instituto irá fazer, determinar a resposta para cada consulta dada.

## 样例 #1

### 输入

```
4
10 2 8 72
3
4 4
1 3
2 4
```

### 输出

```
72
20
82
```

