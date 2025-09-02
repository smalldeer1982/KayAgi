---
title: "DZY Loves FFT"
layout: "post"
diff: 提高+/省选-
pid: CF444B
tag: []
---

# DZY Loves FFT

## 题目描述

### 题目背景
*DZY 喜欢快速傅里叶变换，并乐于使用它。*

[快速傅里叶变换](https://oi-wiki.org/math/poly/fft/)是一种计算卷积的算法。如果 $a$，$b$，$c$ 均为下标从 $0$ 到 $n-1$ 的序列，并且 $c_i = \sum_{j=0}^i a_j \times b_{i-j}$，就可以用快速傅里叶变换来计算 $c$。

DZY 把上面这个式子变成了 $c_i = \max_{j=0}^i a_j \times b_{i-j}$。

其中，$a$ 是从 $1$ 到 $n$ 的**排列**，$b$ 是 $01$ 序列，下标从  $0$ 到 $n-1$。

DZY 需要你计算序列 $c$。

但 DZY 很调皮，他提供了一种方法来得到 $a$ 和 $b$。给定三个整数 $n$，$d$，$x$，使用下面的代码生成 $a$ 和 $b$。

```cpp
//x 为 long long 类型
long long getNextX(){
	x=(x*37+10007)%1000000007;
	return x;
}
void initAB(){
	for(int i=0;i<n;i++) a[i]=i+1;
	for(int i=0;i<n;i++) swap(a[i],a[getNextX()%(i+1)]);
	for(int i=0;i<n;i++)
		if(i<d) b[i]=1;
		else b[i]=0;
	for(int i=0;i<n;i++) swap(b[i],b[getNextX()%(i+1)]);
}
```

## 输入格式

输入一行，包含三个空格分隔的整数 $n$，$d$，$x$ ($1 \le d  \le  n \le  10^5，0 \le  x \le 10^9+6$)。且顽皮的 DZY 规定 $x$ 不等于 $27777500$。

## 输出格式

输出 $n$ 行，第 $i$ 行为 $c_{i-1}$。

翻译来自 [jianhe](https://www.luogu.com.cn/user/613794)。

## 样例 #1

### 输入

```
3 1 1

```

### 输出

```
1
3
2

```

## 样例 #2

### 输入

```
5 4 2

```

### 输出

```
2
2
4
5
5

```

## 样例 #3

### 输入

```
5 4 3

```

### 输出

```
5
5
5
5
4

```

