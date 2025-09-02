---
title: "Birthday"
layout: "post"
diff: 省选/NOI-
pid: CF494D
tag: []
---

# Birthday

## 题目描述

Ali is Hamed's little brother and tomorrow is his birthday. Hamed wants his brother to earn his gift so he gave him a hard programming problem and told him if he can successfully solve it, he'll get him a brand new laptop. Ali is not yet a very talented programmer like Hamed and although he usually doesn't cheat but this time is an exception. It's about a brand new laptop. So he decided to secretly seek help from you. Please solve this problem for Ali.

An $ n $ -vertex weighted rooted tree is given. Vertex number $ 1 $ is a root of the tree. We define $ d(u,v) $ as the sum of edges weights on the shortest path between vertices $ u $ and $ v $ . Specifically we define $ d(u,u)=0 $ . Also let's define $ S(v) $ for each vertex $ v $ as a set containing all vertices $ u $ such that $ d(1,u)=d(1,v)+d(v,u) $ . Function $ f(u,v) $ is then defined using the following formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF494D/a49e19fad915afd07784c02308a91dfcb85750c8.png)The goal is to calculate $ f(u,v) $ for each of the $ q $ given pair of vertices. As the answer can be rather large it's enough to print it modulo $ 10^{9}+7 $ .

## 输入格式

Ali is Hamed's little brother and tomorrow is his birthday. Hamed wants his brother to earn his gift so he gave him a hard programming problem and told him if he can successfully solve it, he'll get him a brand new laptop. Ali is not yet a very talented programmer like Hamed and although he usually doesn't cheat but this time is an exception. It's about a brand new laptop. So he decided to secretly seek help from you. Please solve this problem for Ali.

An $ n $ -vertex weighted rooted tree is given. Vertex number $ 1 $ is a root of the tree. We define $ d(u,v) $ as the sum of edges weights on the shortest path between vertices $ u $ and $ v $ . Specifically we define $ d(u,u)=0 $ . Also let's define $ S(v) $ for each vertex $ v $ as a set containing all vertices $ u $ such that $ d(1,u)=d(1,v)+d(v,u) $ . Function $ f(u,v) $ is then defined using the following formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF494D/a49e19fad915afd07784c02308a91dfcb85750c8.png)The goal is to calculate $ f(u,v) $ for each of the $ q $ given pair of vertices. As the answer can be rather large it's enough to print it modulo $ 10^{9}+7 $ .

## 输出格式

Ali is Hamed's little brother and tomorrow is his birthday. Hamed wants his brother to earn his gift so he gave him a hard programming problem and told him if he can successfully solve it, he'll get him a brand new laptop. Ali is not yet a very talented programmer like Hamed and although he usually doesn't cheat but this time is an exception. It's about a brand new laptop. So he decided to secretly seek help from you. Please solve this problem for Ali.

An $ n $ -vertex weighted rooted tree is given. Vertex number $ 1 $ is a root of the tree. We define $ d(u,v) $ as the sum of edges weights on the shortest path between vertices $ u $ and $ v $ . Specifically we define $ d(u,u)=0 $ . Also let's define $ S(v) $ for each vertex $ v $ as a set containing all vertices $ u $ such that $ d(1,u)=d(1,v)+d(v,u) $ . Function $ f(u,v) $ is then defined using the following formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF494D/a49e19fad915afd07784c02308a91dfcb85750c8.png)The goal is to calculate $ f(u,v) $ for each of the $ q $ given pair of vertices. As the answer can be rather large it's enough to print it modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
5
1 2 1
4 3 1
3 5 1
1 3 1
5
1 1
1 5
2 4
2 1
3 5

```

### 输出

```
10
1000000005
1000000002
23
1000000002

```

## 样例 #2

### 输入

```
8
1 2 100
1 3 20
2 4 2
2 5 1
3 6 1
3 7 2
6 8 5
6
1 8
2 3
5 8
2 6
4 7
6 1

```

### 输出

```
999968753
49796
999961271
999991235
999958569
45130

```

