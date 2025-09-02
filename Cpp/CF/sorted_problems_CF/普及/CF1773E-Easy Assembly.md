---
title: "Easy Assembly"
layout: "post"
diff: 普及/提高-
pid: CF1773E
tag: []
---

# Easy Assembly

## 题目描述

Emma 喜欢玩积木，她有若干相同大小的、标有不同数字的积木，将它们竖直堆放。

现在，她可以进行以下操作：

- 分裂：从将一堆积木（数量大于 $1$）的顶端拿出若干块，按原来的顺序放在地上形成一堆新的积木。操作后积木堆数加一；

- 合并：将一堆积木全部按原来的顺序全部堆到另一堆积木的顶端。操作后积木堆数减一。

她想让所有木块形成一堆且积木上的数字由顶端到底端升序排列。请求出最小操作次数。

## 输入格式

第一行一个整数 $n$（$1\le n\le 10\,000$）表示初始积木堆数。

接下来 $n$ 行，第 $i$ 行开始一个整数 $k_i$（$k_i\ge 1$；$\sum\limits_{i=1}^n k_i\le 10\,000$）表示该堆木块数量。接下来 $k_i$ 个整数 $b_{i,j}$（$1\le b_{i,j}\le 10^9$），依次表示从顶端到底端的积木上的数字。

保证所有积木上的数字不同。

## 输出格式

一行两个整数 $s$ 和 $c$，表示在总操作数最小的情况下分裂和合并操作的次数。

### 样例解释

四张图依次是：初始状态、将最后一堆分裂、将第二堆合并入第一堆、将第一堆合并入第二堆。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/cb220fbe8fd5a228c5c21c989706c90547f1579c.png)$\qquad\qquad$![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/3de66ba621d6019801a98f584dbabf1895c3fe49.png)$\qquad\qquad$![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/97be0dbdbca0329fbb6578d639115dfa0e5cb4a8.png)$\qquad\qquad$![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1773E/254fe6b8fe2b5e78600f45ccede2be36ce9161ad.png)

## 样例 #1

### 输入

```
2
3 3 5 8
2 9 2
```

### 输出

```
1 2
```

