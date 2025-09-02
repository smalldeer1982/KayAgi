---
title: "最小公倍数的最小和 Minimum Sum LCM"
layout: "post"
diff: 提高+/省选-
pid: UVA10791
tag: ['递归', '枚举', '素数判断,质数,筛法']
---

# 最小公倍数的最小和 Minimum Sum LCM

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=19&page=show_problem&problem=1732

[PDF](https://uva.onlinejudge.org/external/107/p10791.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/46b9c621d71e185653bf0a7197761eb0efdc4589.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/7a5e01d2fc4bd5a007ecd456a07165372a1da9fa.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10791/eb4e5ec11ec7e64f907d2a65a0fcc8faf715a7db.png)

## 样例 #1

### 输入

```
12
10
5
0
```

### 输出

```
Case 1: 7
Case 2: 7
Case 3: 6
```



---

---
title: "完美的服务 Perfect Service"
layout: "post"
diff: 提高+/省选-
pid: UVA1218
tag: ['动态规划 DP', '递归', '枚举']
---

# 完美的服务 Perfect Service

## 题目描述

一个网络中有 $N$ 个节点，由 $N-1$ 条边连通，每个节点是服务器或者客户端。如果节点 $u$ 是客户端，就意味着 $u$ 所连接的所有点中有且仅有一台服务器。求最少要多少台服务器才能满足要求。

## 输入格式

输入包含多组测试数据。对于每组数据，第一行是一个整数 $N(\le10000)$。

接下来 $N-1$ 行，每行两个整数 $a_i,b_i$，表示 $a_i,b_i$ 有一条双向连通的边。

除最后一组输入以外，每组数据以 $0$ 结尾，最后一组数据以 $-1$ 结尾。

## 输出格式

对于每组输入，仅输出一行，表示所需要的最小服务器台数。

翻译贡献者：An_Account.



---

