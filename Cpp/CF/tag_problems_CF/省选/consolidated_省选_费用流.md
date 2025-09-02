---
title: "For the Emperor!"
layout: "post"
diff: 省选/NOI-
pid: CF2046D
tag: ['强连通分量', '费用流']
---

# For the Emperor!

## 题目描述

在古罗马，为了击败野蛮人，制定了一项计划，但要实施该计划，每个城市都必须得到通知。

罗马帝国的北部由 $n$ 个城市组成，这些城市通过 $m$ 条单向道路相连。起初，第 $i$ 个城市有 $a_i$ 名信使，每名信使可以沿着现有的道路自由地在城市间移动。一名信使可以携带一份计划副本，并在他访问的城市中传达信息，并且可以在他当前所在的城市为其他信使制作无限多的副本。

开始时，你需要制作一定数量的计划，并将它们交给选定的信使。你的目标是确保每座城市都被携带计划的信使访问过。找出最初需要制作的计划的最小数量，以确保信使能够将计划送到每一个城市，或者确定根本无法做到这一点。

## 输入格式

每个测试数据包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 100$），表示测试用例的数量。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$2 \le n \le 200$，$1 \le m \le 800$）—— 分别表示城市的数量和道路的数量。

第二行包含 $n$ 个非负整数 $a_1, a_2, \ldots, a_n$（$0 \le a_{i} \le n$）—— 分别表示每个城市初始拥有的信使数量。

接下来的 $m$ 行每行包含两个整数 $u$ 和 $v$（$1 \le u,v \le n, u \ne v$），表示从城市 $u$ 到城市 $v$ 有一条单向道路。道路可能会重复出现。

保证所有测试用例中 $n$ 的总和不超过 $200$。保证所有测试用例中 $m$ 的总和不超过 $800$。

## 输出格式

对于每个测试用例，输出一行包含一个整数 —— 表示最初需要给信使的计划副本的最小数量，如果不可能通知到所有城市，则输出 $-1$。

## 样例 #1

### 输入

```
2
7 6
2 1 0 1 2 3 4
1 2
1 3
2 4
2 5
3 6
3 7
4 4
1 1 1 1
1 2
1 3
2 4
3 4
```

### 输出

```
2
2
```



---

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



---

