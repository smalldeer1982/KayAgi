---
title: "Add on a Tree"
layout: "post"
diff: 普及/提高-
pid: CF1188A1
tag: []
---

# Add on a Tree

## 题目描述

Note that this is the first problem of the two similar problems. You can hack this problem only if you solve both problems.

You are given a tree with $ n $ nodes. In the beginning, $ 0 $ is written on all edges. In one operation, you can choose any $ 2 $ distinct leaves $ u $ , $ v $ and any real number $ x $ and add $ x $ to values written on all edges on the simple path between $ u $ and $ v $ .

For example, on the picture below you can see the result of applying two operations to the graph: adding $ 2 $ on the path from $ 7 $ to $ 6 $ , and then adding $ -0.5 $ on the path from $ 4 $ to $ 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/4514fbf35a3201a7ca3b335f667bd3e11a688c5b.png)Is it true that for any configuration of real numbers written on edges, we can achieve it with a finite number of operations?

Leaf is a node of a tree of degree $ 1 $ . Simple path is a path that doesn't contain any node twice.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the number of nodes.

Each of the next $ n-1 $ lines contains two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ , $ u \neq v $ ), meaning that there is an edge between nodes $ u $ and $ v $ . It is guaranteed that these edges form a tree.

## 输出格式

If there is a configuration of real numbers written on edges of the tree that we can't achieve by performing the operations, output "NO".

Otherwise, output "YES".

You can print each letter in any case (upper or lower).

## 说明/提示

In the first example, we can add any real $ x $ to the value written on the only edge $ (1, 2) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/25d412324353a5cacb63d72803d1f9b15e742633.png)In the second example, one of configurations that we can't reach is $ 0 $ written on $ (1, 2) $ and $ 1 $ written on $ (2, 3) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/e16117f5a283e54a35e77dfddddf18a8df81966b.png)Below you can see graphs from examples $ 3 $ , $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/1d0c41f73ee7e0beb3f827a01577bfa07941d15e.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1188A1/91469666c4af6f377da3f6104280ec7d6081a3a0.png)

## 样例 #1

### 输入

```
2
1 2

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
1 2
2 3

```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
1 2
1 3
1 4
2 5

```

### 输出

```
NO
```

## 样例 #4

### 输入

```
6
1 2
1 3
1 4
2 5
2 6

```

### 输出

```
YES
```

