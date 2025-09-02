# Cube Snake

## 题目描述

You've got an $ n×n×n $ cube, split into unit cubes. Your task is to number all unit cubes in this cube with positive integers from $ 1 $ to $ n^{3} $ so that:

- each number was used as a cube's number exactly once;
- for each $ 1<=i&lt;n^{3} $ , unit cubes with numbers $ i $ and $ i+1 $ were neighbouring (that is, shared a side);
- for each $ 1<=i&lt;n $ there were at least two different subcubes with sizes $ i×i×i $ , made from unit cubes, which are numbered with consecutive numbers. That is, there are such two numbers $ x $ and $ y $ , that the unit cubes of the first subcube are numbered by numbers $ x $ , $ x+1 $ , $ ... $ , $ x+i^{3}-1 $ , and the unit cubes of the second subcube are numbered by numbers $ y $ , $ y+1 $ , $ ... $ , $ y+i^{3}-1 $ .

Find and print the required numeration of unit cubes of the cube.

## 说明/提示

In the sample the cubes with sizes $ 2×2×2 $ are numbered with integers $ 1,...,8 $ and $ 5,...,12 $ .

## 样例 #1

### 输入

```
3
```

### 输出

```
1 4 17 
2 3 18 
27 26 19 

8 5 16 
7 6 15 
24 25 20 

9 12 13 
10 11 14 
23 22 21 

```

# 题解

## 作者：Sampson_YW (赞：0)

人麻了，怎么会遇到这种题。

*2700 可能单纯是因为难以找到好的方式来把自己想的做法用代码表现出来。

考虑递归构造一个 $n\times n\times (n+1)$ 的符合要求的长方体。使得从 $(0,0,0)$ 开始，到 $(0,n-1,n)$ 结束。

首先设立原点 $(0,0,0)$，将底面铺上 $[1,n^2]$，使得 $n^2$ 被铺在了 $(0,n-1,0)$。这相当于在 $n\times n$ 的正方形上铺数，使得从 $(0,0)$ 开始，$(0,n-1)$  结束。对 $n$ 奇偶讨论后容易构造（具体可以看代码）。

然后从 $(0,n-1,0)$ 走到 $(0,n-1,n-1)$，再塞一个 $(n-1)\times (n-1)\times n$ 的长方体：从 $(1,n-1,n-1)$ 开始，到 $(1,0,1)$ 结束。这个长方体的左下角为 $(1,0,1)$，右上角为 $(n-1,n-1,n-1)$。变换坐标系即可递归构造。

接着从 $(1,0,1)$ 走到 $(0,0,1)$，再在侧面铺一个 $(n-1)\times(n-1)$ 的正方形：从 $(0,0,1)$ 开始，到 $(0,0,n-1)$ 结束。正方形的构造同上。

最后从 $(0,0,n-1)$ 走到 $(0,0,n)$，再在顶面铺一个 $n\times n$ 的正方形：从 $(0,0,n)$ 开始，到 $(0,n-1,n)$ 结束。

这样就完成了构造。容易发现这个长方体包含两个 $n\times n\times n$ 的值域连续的立方体：分别是丢掉顶面和丢掉底面的立方体。最后输出答案直接选丢掉顶面的立方体。

[code](https://www.luogu.com.cn/paste/juo1y5hr)

---

