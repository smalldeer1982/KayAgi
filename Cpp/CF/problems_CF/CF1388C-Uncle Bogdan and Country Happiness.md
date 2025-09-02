---
title: "Uncle Bogdan and Country Happiness"
layout: "post"
diff: 普及+/提高
pid: CF1388C
tag: ['图论']
---

# Uncle Bogdan and Country Happiness

## 题目描述

Uncle Bogdan is in captain Flint's crew for a long time and sometimes gets nostalgic for his homeland. Today he told you how his country introduced a happiness index.

There are $ n $ cities and $ n−1 $ undirected roads connecting pairs of cities. Citizens of any city can reach any other city traveling by these roads. Cities are numbered from $ 1 $ to $ n $ and the city $ 1 $ is a capital. In other words, the country has a tree structure.

There are $ m $ citizens living in the country. A $ p_i $ people live in the $ i $ -th city but all of them are working in the capital. At evening all citizens return to their home cities using the shortest paths.

Every person has its own mood: somebody leaves his workplace in good mood but somebody are already in bad mood. Moreover any person can ruin his mood on the way to the hometown. If person is in bad mood he won't improve it.

Happiness detectors are installed in each city to monitor the happiness of each person who visits the city. The detector in the $ i $ -th city calculates a happiness index $ h_i $ as the number of people in good mood minus the number of people in bad mood. Let's say for the simplicity that mood of a person doesn't change inside the city.

Happiness detector is still in development, so there is a probability of a mistake in judging a person's happiness. One late evening, when all citizens successfully returned home, the government asked uncle Bogdan (the best programmer of the country) to check the correctness of the collected happiness indexes.

Uncle Bogdan successfully solved the problem. Can you do the same?

More formally, You need to check: "Is it possible that, after all people return home, for each city $ i $ the happiness index will be equal exactly to $ h_i $ ".

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le       10000 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le 10^5 $ ; $ 0 \le m \le 10^9 $ ) — the number of cities and citizens.

The second line of each test case contains $ n $ integers $ p_1, p_2, \ldots, p_{n} $ ( $ 0 \le p_i \le m $ ; $ p_1 + p_2       + \ldots + p_{n} = m $ ), where $ p_i $ is the number of people living in the $ i $ -th city.

The third line contains $ n $ integers $ h_1, h_2, \ldots,       h_{n} $ ( $ -10^9 \le h_i \le 10^9 $ ), where $ h_i $ is the calculated happiness index of the $ i $ -th city.

Next $ n − 1 $ lines contain description of the roads, one per line. Each line contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ ; $ x_i \neq y_i $ ), where $ x_i $ and $ y_i $ are cities connected by the $ i $ -th road.

It's guaranteed that the sum of $ n $ from all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print YES, if the collected data is correct, or NO — otherwise. You can print characters in YES or NO in any case.

## 说明/提示

Let's look at the first test case of the first sample:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/001794ade043a3f0f7ed603305eb551246689207.png)At first, all citizens are in the capital. Let's describe one of possible scenarios:

- a person from city $ 1 $ : he lives in the capital and is in good mood;
- a person from city $ 4 $ : he visited cities $ 1 $ and $ 4 $ , his mood was ruined between cities $ 1 $ and $ 4 $ ;
- a person from city $ 3 $ : he visited cities $ 1 $ and $ 3 $ in good mood;
- a person from city $ 6 $ : he visited cities $ 1 $ , $ 3 $ and $ 6 $ , his mood was ruined between cities $ 1 $ and $ 3 $ ;

 In total, - $ h_1 = 4 - 0 =         4 $ ,
- $ h_2 = 0 $ ,
- $ h_3 = 1 - 1 = 0 $ ,
- $ h_4 = 0 - 1 = -1 $ ,
- $ h_5 = 0 $ ,
- $ h_6 = 0 - 1 = -1 $ ,
- $ h_7 = 0 $ .

The second case of the first test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/a9264c4828a85c9989a95ed8604e23cfb9f3dcda.png)All people have already started in bad mood in the capital — this is the only possible scenario.

The first case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/b8bbd8cbfa8f12355a17c596fd18bc65433a619c.png)The second case of the second test:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1388C/5c48a1551b8fe0dc0edc02bc5782fb0068b84587.png)It can be proven that there is no way to achieve given happiness indexes in both cases of the second test.

## 样例 #1

### 输入

```
2
7 4
1 0 1 1 0 1 0
4 0 0 -1 0 -1 0
1 2
1 3
1 4
3 5
3 6
3 7
5 11
1 2 5 2 1
-11 -2 -6 -2 -1
1 2
1 3
1 4
3 5
```

### 输出

```
YES
YES
```

## 样例 #2

### 输入

```
2
4 4
1 1 1 1
4 1 -3 -1
1 2
1 3
1 4
3 13
3 3 7
13 1 4
1 2
1 3
```

### 输出

```
NO
NO
```

