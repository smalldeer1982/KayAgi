---
title: "Gosha is hunting"
layout: "post"
diff: 省选/NOI-
pid: CF739E
tag: ['二分', '费用流', '期望']
---

# Gosha is hunting

## 题目描述

Gosha is hunting. His goal is to catch as many Pokemons as possible. Gosha has $ a $ Poke Balls and $ b $ Ultra Balls. There are $ n $ Pokemons. They are numbered $ 1 $ through $ n $ . Gosha knows that if he throws a Poke Ball at the $ i $ -th Pokemon he catches it with probability $ p_{i} $ . If he throws an Ultra Ball at the $ i $ -th Pokemon he catches it with probability $ u_{i} $ . He can throw at most one Ball of each type at any Pokemon.

The hunting proceeds as follows: at first, Gosha chooses no more than $ a $ Pokemons at which he will throw Poke Balls and no more than $ b $ Pokemons at which he will throw Ultra Balls. After that, he throws the chosen Balls at the chosen Pokemons. If he throws both Ultra Ball and Poke Ball at some Pokemon, he is caught if and only if he is caught by any of these Balls. The outcome of a throw doesn't depend on the other throws.

Gosha would like to know what is the expected number of the Pokemons he catches if he acts in an optimal way. In other words, he would like to know the maximum possible expected number of Pokemons can catch.

## 输入格式

The first line contains three integers $ n $ , $ a $ and $ b $ ( $ 2<=n<=2000 $ , $ 0<=a,b<=n $ ) — the number of Pokemons, the number of Poke Balls and the number of Ultra Balls.

The second line contains $ n $ real values $ p_{1},p_{2},...,p_{n} $ ( $ 0<=p_{i}<=1 $ ), where $ p_{i} $ is the probability of catching the $ i $ -th Pokemon if Gosha throws a Poke Ball to it.

The third line contains $ n $ real values $ u_{1},u_{2},...,u_{n} $ ( $ 0<=u_{i}<=1 $ ), where $ u_{i} $ is the probability of catching the $ i $ -th Pokemon if Gosha throws an Ultra Ball to it.

All the probabilities are given with exactly three digits after the decimal separator.

## 输出格式

Print the maximum possible expected number of Pokemons Gosha can catch. The answer is considered correct if it's absolute or relative error doesn't exceed $ 10^{-4} $ .

## 样例 #1

### 输入

```
3 2 2
1.000 0.000 0.500
0.000 1.000 0.500

```

### 输出

```
2.75

```

## 样例 #2

### 输入

```
4 1 3
0.100 0.500 0.500 0.600
0.100 0.500 0.900 0.400

```

### 输出

```
2.16

```

## 样例 #3

### 输入

```
3 2 0
0.412 0.198 0.599
0.612 0.987 0.443

```

### 输出

```
1.011
```

