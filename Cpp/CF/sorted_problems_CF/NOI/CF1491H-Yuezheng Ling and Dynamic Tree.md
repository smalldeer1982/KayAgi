---
title: "Yuezheng Ling and Dynamic Tree"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1491H
tag: []
---

# Yuezheng Ling and Dynamic Tree

## 题目描述

Yuezheng Ling gives Luo Tianyi a tree which has $ n $ nodes, rooted at $ 1 $ .

Luo Tianyi will tell you that the parent of the $ i $ -th node is $ a_i $ ( $ 1 \leq a_i<i $ for $ 2 \le i \le n $ ), and she will ask you to perform $ q $ queries of $ 2 $ types:

1. She'll give you three integers $ l $ , $ r $ and $ x $ ( $ 2 \le l \le r \le n $ , $ 1 \le x \le 10^5 $ ). You need to replace $ a_i $ with $ \max(a_i-x,1) $ for all $ i $ with $ l \leq i \leq r $ .
2. She'll give you two integers $ u $ , $ v $ ( $ 1 \le u, v \le n $ ). You need to find the [LCA](https://en.wikipedia.org/wiki/Lowest_common_ancestor) of nodes $ u $ and $ v $ (their lowest common ancestor).

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2\leq n,q \leq 10^5 $ ) — the number of nodes and the number of queries, respectively.

The second line contains $ n-1 $ integers $ a_2, a_3,\dots, a_n $ ( $ 1 \le a_i < i $ ), where $ a_i $ is the parent of the node $ i $ .

Next $ q $ lines contain queries. For each query, the first integer of each line is $ t $ ( $ t = 1 $ or $ 2 $ ) — the type of the query.

 If $ t = 1 $ , this represents the query of the first type. Then, three integers will follow: $ l $ , $ r $ , $ x $ ( $ 2 \le l \le r \le n $ , $ 1 \le x \le 10^5 $ ), meaning that you have to replace $ a_i $ with $ \max(a_i-x,1) $ for all $ i $ with $ l \leq i \leq r $ .

 If $ t = 2 $ , this represents the query of the second type. Then, two integers will follow: $ u $ and $ v $ ( $ 1 \le u, v \le n $ ), and you have to find the LCA of $ u $ and $ v $ .

 It's guaranteed that there is at least one query of the second type.

## 输出格式

For each query of the second type output answer on a new line.

## 说明/提示

The tree in example is shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1491H/818163092787871fe6b5fd7889d250d0fa5e8087.png)After the query of the first type, the tree changes and is looking as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1491H/c2a6cdaaa81fc0062a546706c09a18121fedd155.png)

## 样例 #1

### 输入

```
6 4
1 2 3 3 4
2 3 4
1 2 3 1
2 5 6
2 2 3
```

### 输出

```
3
3
1
```

