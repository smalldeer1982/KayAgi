# Ski Base

## 题目描述

A ski base is planned to be built in Walrusland. Recently, however, the project is still in the constructing phase. A large land lot was chosen for the construction. It contains $ n $ ski junctions, numbered from $ 1 $ to $ n $ . Initially the junctions aren't connected in any way.

In the constructing process $ m $ bidirectional ski roads will be built. The roads are built one after another: first the road number $ 1 $ will be built, then the road number $ 2 $ , and so on. The $ i $ -th road connects the junctions with numbers $ a_{i} $ and $ b_{i} $ .

Track is the route with the following properties:

- The route is closed, that is, it begins and ends in one and the same junction.
- The route contains at least one road.
- The route doesn't go on one road more than once, however it can visit any junction any number of times.

Let's consider the ski base as a non-empty set of roads that can be divided into one or more tracks so that exactly one track went along each road of the chosen set. Besides, each track can consist only of roads from the chosen set. Ski base doesn't have to be connected.

Two ski bases are considered different if they consist of different road sets.

After building each new road the Walrusland government wants to know the number of variants of choosing a ski base based on some subset of the already built roads. The government asks you to help them solve the given problem.

## 说明/提示

Let us have 3 junctions and 4 roads between the junctions have already been built (as after building all the roads in the sample): 1 and 3, 2 and 3, 2 roads between junctions 1 and 2. The land lot for the construction will look like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF91C/28b4727aa73cce1da2aeb595e550d496be82b411.png)The land lot for the construction will look in the following way:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF91C/28b4727aa73cce1da2aeb595e550d496be82b411.png)We can choose a subset of roads in three ways:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF91C/f9fe4e0ad2052df89d1d0881cb2113925e271782.png)In the first and the second ways you can choose one path, for example, 1 - 2 - 3 - 1. In the first case you can choose one path 1 - 2 - 1.

## 样例 #1

### 输入

```
3 4
1 3
2 3
1 2
1 2
```

### 输出

```
0
0
1
3
```

# 题解

## 作者：隔壁泞2的如心 (赞：1)

题意可以转化为：给定一些整数，求它有多少个子集的异或和为 $0$。

——等等？？你转化了个啥？？

——这题让你求出来的不是有多少个边集满足保留它之后，每个点的度数都是偶数嘛，那么把每一条边视作一个 $n$ 位二进制数，它连接的两个点对应的二进制位为 $1$，那么“每个点的度数均为偶数”就成了“异或和为 $0$”了（

对于异或和为某值的集合计数——其实你可以直接拎出来一个大小为 $n$ 的线性基这样线性基外的数不管咋选线性基内都能正好找到一个和线性基外的数异或和相同的选取方案这样集合数量显然就是 $2^{m-n}$——不对啊，好像这个**线性基并不存在**……

于是上述做法就寄了，但我还是不想动脑子怎么办呢？那就直接上 FWT，考虑 FWT 数组里的每一项，在加入一条边后，要么会 $\times 2$，要么会 $\times 0$。然后设新加入的边对应的整数为 $a$、正在考虑 $\text{FWT}_b$，那么 $\times 0$ 的情况全都是满足 $\text{popcount}(a\operatorname{and}b)=1$ 的，也就是 $b$ 对应的点集恰好包含了 $a$ 对应的边的一个端点。

当所有边都加入完毕后，只有满足“对于任意一条边，它两边的点要么同时在 $x$ 对应的子集内，要么同时不在”的 $x$ 才会使得 $\text{FWT}_x$ 不为 $0$ 而为 $2^m$，而这样的 $x$ 显然只有 $2^{\text{连通块数}}$ 个。由于 FWT 数组的每一项在 IFWT 中对 $0$ 的贡献都是 $2^{-n}$，因此答案就是 $2^{m+\text{连通块数}-n}$。

所以你加边时维护一下图内连通块个数就可以了，记得减去空集。代码就不放了，~~反正也交不了（~~

---

