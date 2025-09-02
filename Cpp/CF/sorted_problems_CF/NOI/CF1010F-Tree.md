---
title: "Tree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1010F
tag: []
---

# Tree

## 题目描述

The Main Martian Tree grows on Mars. It is a binary tree (a rooted tree, with no more than two sons at each vertex) with $ n $ vertices, where the root vertex has the number $ 1 $ . Its fruits are the Main Martian Fruits. It's summer now, so this tree does not have any fruit yet.

Autumn is coming soon, and leaves and branches will begin to fall off the tree. It is clear, that if a vertex falls off the tree, then its entire subtree will fall off too. In addition, the root will remain on the tree. Formally: the tree will have some connected subset of vertices containing the root.

After that, the fruits will grow on the tree (only at those vertices which remain). Exactly $ x $ fruits will grow in the root. The number of fruits in each remaining vertex will be not less than the sum of the numbers of fruits in the remaining sons of this vertex. It is allowed, that some vertices will not have any fruits.

Natasha wondered how many tree configurations can be after the described changes. Since this number can be very large, output it modulo $ 998244353 $ .

Two configurations of the resulting tree are considered different if one of these two conditions is true:

- they have different subsets of remaining vertices;
- they have the same subset of remaining vertices, but there is a vertex in this subset where they have a different amount of fruits.

## 输入格式

The first line contains two integers: $ n $ and $ x $ ( $ 1 \le n \le 10^5 $ , $ 0 \le x \le 10^{18} $ ) — the size of the tree and the number of fruits in the root.

The $ i $ -th of the following $ (n-1) $ lines contains two integers $ a_i $ and $ b_i $ ( $ 1 \le a_i, b_i \le n $ ) — vertices connected by the $ i $ -th edge of the tree.

It is guaranteed that the input data describes a correct binary tree with the root at the vertex $ 1 $ .

## 输出格式

Print one number — the number of configurations of the resulting tree modulo $ 998244353 $ .

## 说明/提示

Consider the first example. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/e006e9aa9bfd626cb58918fdedfcf46e7b8caaaa.png)

There are $ 2 $ fruits at the vertex $ 1 $ . The following $ 13 $ options are possible:

- there is no vertex $ 2 $ , there is no vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/ac5eccec509eafa9e9632100afa8feac81206c7a.png)
- there is no vertex $ 2 $ , there are no fruits at the vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/1b9eb2f94222ad9b4a95d9a4c12ace03e39a5c65.png)
- there is no vertex $ 2 $ , there is $ 1 $ fruit at the vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/c6d930189e2e38c0a7f9fc5b5ae41e259ac43c60.png)
- there is no vertex $ 2 $ , there are $ 2 $ fruits at the vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/31d6520771c57a7c2c5ee10f3a0d5f97d22d929e.png)
- there are no fruits at the vertex $ 2 $ , there is no vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/2fafe60e9207dc43580f5178c5219fe1c2ce4280.png)
- there are no fruits at the vertex $ 2 $ , there are no fruits at the vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/db28e3762e440236cc9bdf232e1332d72cf930a8.png)
- there are no fruits at the vertex $ 2 $ , there is $ 1 $ fruit at the vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/83b7d7babf60a8e333b889d46432e709e9c55964.png)
- there are no fruits at the vertex $ 2 $ , there are $ 2 $ fruits at the vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/bf4591c237d146328e362b2775a374e47c6a8e1f.png)
- there is $ 1 $ fruit at the vertex $ 2 $ , there is no vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/129ebc1752c50c2b8f78552f55438f7233215e10.png)
- there is $ 1 $ fruit at the vertex $ 2 $ , there are no fruits at the vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/c862117377ccf3074edd9d39ef792eb2f7efd07c.png)
- there is $ 1 $ fruit at the vertex $ 2 $ , there is $ 1 $ fruit at the vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/c71af07e5a385d01a401070b48e50293c8e2bad4.png)
- there are $ 2 $ fruits at the vertex $ 2 $ , there is no vertex $ 3 $ ; ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/d0d91e75c72ccb399333407b57951d47ae7d4eeb.png)
- there are $ 2 $ fruits at the vertex $ 2 $ , there are no fruits at the vertex $ 3 $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1010F/f9a32865116becf27f40b4c7f576f48ff8827e4c.png)

Consider the second example. There are $ 5 $ fruits at the vertex $ 1 $ . The following $ 7 $ options are possible:

- there is no vertex $ 2 $ ;
- there are no fruits at the vertex $ 2 $ ;
- there is $ 1 $ fruit at the vertex $ 2 $ ;
- there are $ 2 $ fruits at the vertex $ 2 $ ;
- there are $ 3 $ fruits at the vertex $ 2 $ ;
- there are $ 4 $ fruits at the vertex $ 2 $ ;
- there are $ 5 $ fruits at the vertex $ 2 $ .

## 样例 #1

### 输入

```
3 2
1 2
1 3

```

### 输出

```
13

```

## 样例 #2

### 输入

```
2 5
1 2

```

### 输出

```
7

```

## 样例 #3

### 输入

```
4 10
1 2
1 3
3 4

```

### 输出

```
441

```

