---
title: "LuoTianyi and the Floating Islands (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF1824B1
tag: ['树论', '分类讨论']
---

# LuoTianyi and the Floating Islands (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ k\le\min(n,3) $ . You can make hacks only if both versions of the problem are solved.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B1/12896184a3f823fcd8518f46dc5b68823c932f0f.png) Chtholly and the floating islands.LuoTianyi now lives in a world with $ n $ floating islands. The floating islands are connected by $ n-1 $ undirected air routes, and any two of them can reach each other by passing the routes. That means, the $ n $ floating islands form a tree.

One day, LuoTianyi wants to meet her friends: Chtholly, Nephren, William, .... Totally, she wants to meet $ k $ people. She doesn't know the exact positions of them, but she knows that they are in pairwise distinct islands. She define an island is good if and only if the sum of the distances $ ^{\dagger} $ from it to the islands with $ k $ people is the minimal among all the $ n $ islands.

Now, LuoTianyi wants to know that, if the $ k $ people are randomly set in $ k $ distinct of the $ n $ islands, then what is the expect number of the good islands? You just need to tell her the expect number modulo $ 10^9+7 $ .

 $ ^{\dagger} $ The distance between two islands is the minimum number of air routes you need to take to get from one island to the other.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1\le k \le \min(n,3), 1\le n \le 2\cdot 10^5 $ ) — the number of the islands and people respectively.

Next $ n−1 $ lines describe the air routes. The $ i $ -th of them contains two integers $ u_i $ and $ v_i $ ( $ 1 \le u_i,v_i \le n, u_i \neq v_i $ ) — the islands connected by the $ i $ -th air route.

## 输出格式

Print a single integer — the expect number of the good islands modulo $ 10^9 + 7 $ .

Formally, let $ M = 10^9 + 7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 $ ( $ \operatorname{mod} M $ ). Output the integer equal to $ p \cdot q^{-1} $ $ \operatorname{mod} M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p $ ( $ \operatorname{mod} M $ ).

## 说明/提示

In the first example the air routes form the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B1/f98245759af7851bb13c350e387c9b296063f10a.png) If the people are in the islands $ 1 $ and $ 2 $ , then islands $ 1 $ and $ 2 $ will be good.

The sum of the distances from island $ 1 $ or $ 2 $ to all the people is $ 1+0=1 $ , which is the minimal. While the sum of the distances from island $ 3 $ to all the people is $ 2+1=3 $ , which is greater than $ 1 $ .

Like this, when the people are in island $ 1 $ and $ 3 $ , then islands $ 1,2 $ and $ 3 $ will be good.

When the people are in islands $ 1 $ and $ 4 $ , then islands $ 1,2,3 $ and $ 4 $ will be good.

When the people are in islands $ 2 $ and $ 3 $ , then islands $ 2 $ and $ 3 $ will be good.

When the people are in islands $ 2 $ and $ 4 $ , then islands $ 2,3 $ and $ 4 $ will be good.

When the people are in islands $ 3 $ and $ 4 $ , then islands $ 3 $ and $ 4 $ will be good.

So the expect of the number of the good islands is $ \frac{16}{6} $ , which equals to $ 666666674 $ modulo $ 10^9+7 $ .

In the second example the air routes form the following tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B1/2f411e079090512cd14c27f9186226921a07c282.png)There is always the only good island, so the expected number is $ 1 $ .

## 样例 #1

### 输入

```
4 2
1 2
2 3
3 4
```

### 输出

```
666666674
```

## 样例 #2

### 输入

```
5 1
1 2
2 3
3 4
3 5
```

### 输出

```
1
```



---

---
title: "One-Dimensional Puzzle"
layout: "post"
diff: 普及+/提高
pid: CF1931G
tag: ['组合数学', '分类讨论']
---

# One-Dimensional Puzzle

## 题目描述

You have a one-dimensional puzzle, all the elements of which need to be put in one row, connecting with each other. All the puzzle elements are completely white and distinguishable from each other only if they have different shapes.

Each element has straight borders at the top and bottom, and on the left and right it has connections, each of which can be a protrusion or a recess. You cannot rotate the elements.

You can see that there are exactly $ 4 $ types of elements. Two elements can be connected if the right connection of the left element is opposite to the left connection of the right element.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1931G/ab3dee044a8e18206fe7c695b7a089bda5931d43.png) All possible types of elements. The puzzle contains $ c_1, c_2, c_3, c_4 $ elements of each type. The puzzle is considered complete if you have managed to combine all elements into one long chain. You want to know how many ways this can be done.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 2 \cdot 10^5 $ ) — the number of input test cases. The descriptions of the test cases follow.

The description of each test case contains $ 4 $ integers $ c_i $ ( $ 0 \le c_i \le 10^6 $ ) — the number of elements of each type, respectively.

It is guaranteed that the sum of $ c_i $ for all test cases does not exceed $ 4 \cdot 10^6 $ .

## 输出格式

For each test case, print one integer — the number of possible ways to solve the puzzle.

Two methods are considered different if there is $ i $ , such that the types of elements at the $ i $ position in these methods differ.

Since the answer can be very large, output it modulo $ 998244353 $ .

If it is impossible to solve the puzzle, print $ 0 $ .

## 样例 #1

### 输入

```
11
1 1 1 1
1 2 5 10
4 6 100 200
900000 900000 900000 900000
0 0 0 0
0 0 566 239
1 0 0 0
100 0 100 0
0 0 0 4
5 5 0 2
5 4 0 5
```

### 输出

```
4
66
0
794100779
1
0
1
0
1
36
126
```



---

---
title: "Gerrymandering"
layout: "post"
diff: 普及+/提高
pid: CF2022C
tag: ['动态规划 DP', '分类讨论']
---

# Gerrymandering

## 题目描述

We all steal a little bit. But I have only one hand, while my adversaries have two.

Álvaro Obregón



Álvaro and José are the only candidates running for the presidency of Tepito, a rectangular grid of $ 2 $ rows and $ n $ columns, where each cell represents a house. It is guaranteed that $ n $ is a multiple of $ 3 $ .

Under the voting system of Tepito, the grid will be split into districts, which consist of any $ 3 $ houses that are connected $ ^{\text{∗}} $ . Each house will belong to exactly one district.

Each district will cast a single vote. The district will vote for Álvaro or José respectively if at least $ 2 $ houses in that district select them. Therefore, a total of $ \frac{2n}{3} $ votes will be cast.

As Álvaro is the current president, he knows exactly which candidate each house will select. If Álvaro divides the houses into districts optimally, determine the maximum number of votes he can get.

 $ ^{\text{∗}} $ A set of cells is connected if there is a path between any $ 2 $ cells that requires moving only up, down, left and right through cells in the set.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains one integer $ n $ ( $ 3 \le n \le 10^5 $ ; $ n $ is a multiple of $ 3 $ ) — the number of columns of Tepito.

The following two lines each contain a string of length $ n $ . The $ i $ -th line contains the string $ s_i $ , consisting of the characters $ \texttt{A} $ and $ \texttt{J} $ . If $ s_{i,j}=\texttt{A} $ , the house in the $ i $ -th row and $ j $ -th column will select Álvaro. Otherwise if $ s_{i,j}=\texttt{J} $ , the house will select José.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum number of districts Álvaro can win by optimally dividing the houses into districts.

## 说明/提示

The image below showcases the optimal arrangement of districts Álvaro can use for each test case in the example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2022C/df820ffc2e1ad6e016254b57c0ce9fb7f735735d.png)

## 样例 #1

### 输入

```
4
3
AAA
AJJ
6
JAJAJJ
JJAJAJ
6
AJJJAJ
AJJAAA
9
AJJJJAJAJ
JAAJJJJJA
```

### 输出

```
2
2
3
2
```



---

