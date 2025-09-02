# Little Elephant and Triangle

## 题目描述

### 题目翻译
#### 题目大意
小象正在玩直角坐标系。他最喜欢玩的是整数点。小象把整数点定义为一对整数 $(x,y)$，即 $0\le x\le w$ 和 $0\le y\le h$。因此，小象只知道 $(w + 1)(h + 1)$ 个不同的整数点。

小象想要画一个顶点位于整数点的三角形，且三角形的面积必须是正整数。为此，他需要找出由三个点组成的三角形的组数。这时，组中点的顺序就很重要了，也就是说： $(0,0),(0,2),(2,2)$ 这三点组成的组并不等于 $(0,2),(0,0),(2,2)$ 这三点组成的组。

现请你帮助小象找出由三个整数点组成的、面积为整数的三角形的组数。由于答案可能很大，请将答案模上 $1000000007 $($10^9+7$)。

## 样例 #1

### 输入

```
2 1
```

### 输出

```
36
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
240
```

# 题解

## 作者：Gauss0320 (赞：2)

枚举三角形的一个顶点$(x,y)$，并记另外两个顶点为$(x_1,y_1)$和$(x_2,y_2)$

根据叉积我们可以知道这个三角形面积的两倍为$|(x_1-x)(y_2-y)+(x_2-x)(y_1-y)|$.

所以这个三角形面积是否为整数仅取决于$x,y,x_1,y_1,x_2,y_2$的奇偶性（parity），只需枚举$2^6$种情况即可。

接下来考虑减去退化三角形的贡献，枚举一条线段的水平宽与铅垂高$i,j$（当$i=0$且$j=0$时线段退化成一个点）。满足条件的线段个数为$(n-i+1)(m-j+1)$，且每一条这样的线段上总共有$\gcd(i,j)+1$个整点。

那么无非是要求
$$\sum_{i=1}^n\sum_{j=1}^m\gcd(i,j)=\sum_{d=1}^{\min(n,m)}\varphi(d)\left\lfloor\frac{n}{d}\right\rfloor\left\lfloor
\frac{m}{d}\right\rfloor$$
$$\sum_{i=1}^n\sum_{j=1}^mi\gcd(i,j)=\sum_{d=1}^{\min(n,m)}d\varphi(d)S\left(\left\lfloor\frac{n}{d}\right\rfloor\right)\left\lfloor\frac{m}{d}\right\rfloor$$
$$\sum_{i=1}^n\sum_{j=1}^mij\gcd(i,j)=\sum_{d=1}^{\min(n,m)}d^2\varphi(d)S\left(\left\lfloor\frac{n}{d}\right\rfloor\right)S\left(\left\lfloor\frac{m}{d}\right\rfloor\right)$$
这几类式子的值。

本题数据比较小，$O(n)$和$O(n^2)$皆可过。

---

