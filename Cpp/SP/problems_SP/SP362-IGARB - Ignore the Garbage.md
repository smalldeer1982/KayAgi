---
title: "IGARB - Ignore the Garbage"
layout: "post"
diff: 难度0
pid: SP362
tag: []
---

# IGARB - Ignore the Garbage

## 题目描述

_Tip: 翻译相对于原题做了部分改变，但不影响理解_


有一家IT公司，由于每天有太多客户，所以公司使用了一种排队策略以缓解服务压力。

这个策略是：给每个客户一张带有号码的票，票上全是数字号码，公司装了一个液晶显示屏，用来叫号。在显示屏上，每个数字分别显示为：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP362/ef6f759f72ca9483ff40a7a67d74c5db395bfaa4.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP362/87ba89c0ef882d77e13d4a650b71459c68c9d9c2.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP362/7356fc92d8d27ebd082a8d1d174d724ac42b63e6.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP362/b159054a3254b337991fc58fe2df41f27c22e8c3.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP362/46b71f1b43797d8847b1d7d6a9873f0a6c327956.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP362/cf3e529da34842dd3d50f7e9cad24f9e476f42f7.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP362/8e14c9632522f55453a957a9c47b319c5856eef7.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP362/eff0533fed98ba724ce628518a952b428df0e754.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP362/39b9c68a3c172560d6fe262f4df2b850f7bc4629.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP362/7c851d5a5e1726787d53d827fe2eb1288d01e56b.png)

但是安装这台显示屏的工作人员却不小心把显示屏装倒了，不过，就算是倒着的显示屏也会时不时地显示几个有效号码（注意：有效号码并不是指和原号码相同的号码，而是仍可以读出来的号码，例如倒过来的6是有效的，因为显示屏上会显示9）。

没有倒过来的显示器最初显示的是1，每一秒数字加一，工作人员想知道第$k$个有效号码是多少（注意：200倒过来在显示屏上显示的号码002，也算有效号码）。

## 输入格式

第一行为一个整数$T$，代表测试数据的组数；其后共$T$行，每行一个整数$k_i$。

## 输出格式

共$T$行，每行为一个整数$s_i$，代表第$k_i$个有效号码。

### 输入输出样例

#### 输入#1

```
8
1
2
3
4
5
6
8
98
```

#### 输出#1

```
1
2
5
9
8
6
11
002
```

### 样例说明&数据范围

## 说明/提示

对于$100\%$的数据：$T \leq 2200,k_i \leq 10^{200}$
  
$\quad$

**Translated by** [**@wanguan**](https://www.luogu.com.cn/user/719577)

## 样例 #1

### 输入

```
8
1
2
3
4
5
6
8
98
```

### 输出

```
1
2
5
9
8
6
11
002
```

