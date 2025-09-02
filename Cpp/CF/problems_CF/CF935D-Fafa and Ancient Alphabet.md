---
title: "Fafa and Ancient Alphabet"
layout: "post"
diff: 提高+/省选-
pid: CF935D
tag: []
---

# Fafa and Ancient Alphabet

## 题目描述

Ancient Egyptians are known to have used a large set of symbols ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/9d7de2306d9a860acda322166418d2eb2e3f0f44.png) to write on the walls of the temples. Fafa and Fifa went to one of the temples and found two non-empty words $ S_{1} $ and $ S_{2} $ of equal lengths on the wall of temple written one below the other. Since this temple is very ancient, some symbols from the words were erased. The symbols in the set ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/9d7de2306d9a860acda322166418d2eb2e3f0f44.png) have equal probability for being in the position of any erased symbol.

Fifa challenged Fafa to calculate the probability that $ S_{1} $ is lexicographically greater than $ S_{2} $ . Can you help Fafa with this task?

You know that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/ef268df96da9b2e5c8e0a535fddc8c6d2cd6ef3b.png), i. e. there were $ m $ distinct characters in Egyptians' alphabet, in this problem these characters are denoted by integers from $ 1 $ to $ m $ in alphabet order. A word $ x $ is lexicographically greater than a word $ y $ of the same length, if the words are same up to some position, and then the word $ x $ has a larger character, than the word $ y $ .

We can prove that the probability equals to some fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/f3d3518082efa9b78c1dfc7f1e277e49a9674698.png), where $ P $ and $ Q $ are coprime integers, and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/9d39e8956ca5ae36ed529a9998b81f8c971b6e39.png). Print as the answer the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/9db35f1977f217526a6ba86931500db815df9867.png), i. e. such a non-negative integer less than $ 10^{9}+7 $ , such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/377c132d9f19a05fde19ac3441d728f7ce7dc195.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/067e520c210c31f6438c25961d459da6fb1e4454.png) means that $ a $ and $ b $ give the same remainders when divided by $ m $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{5} $ ) — the length of each of the two words and the size of the alphabet ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/9d7de2306d9a860acda322166418d2eb2e3f0f44.png), respectively.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=m $ ) — the symbols of $ S_{1} $ . If $ a_{i}=0 $ , then the symbol at position $ i $ was erased.

The third line contains $ n $ integers representing $ S_{2} $ with the same format as $ S_{1} $ .

## 输出格式

Print the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/409150ea0aec421ee48df6cd56fed827ad4a4771.png), where $ P $ and $ Q $ are coprime and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/f3d3518082efa9b78c1dfc7f1e277e49a9674698.png) is the answer to the problem.

## 说明/提示

In the first sample, the first word can be converted into ( $ 1 $ ) or ( $ 2 $ ). The second option is the only one that will make it lexicographically larger than the second word. So, the answer to the problem will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/6816555efb79ba88b199193ab2e0de2995d92d86.png), that is $ 500000004 $ , because ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/6da52dcf52e727f86b710fd73b86d4595daebaef.png).

In the second example, there is no replacement for the zero in the second word that will make the first one lexicographically larger. So, the answer to the problem is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF935D/286eb02d12e6632b3327f1c14fd5fd72758c676f.png), that is $ 0 $ .

## 样例 #1

### 输入

```
1 2
0
1

```

### 输出

```
500000004

```

## 样例 #2

### 输入

```
1 2
1
0

```

### 输出

```
0

```

## 样例 #3

### 输入

```
7 26
0 15 12 9 13 0 14
11 1 0 13 15 12 0

```

### 输出

```
230769233

```

