---
title: "TediousLee"
layout: "post"
diff: 普及+/提高
pid: CF1369D
tag: []
---

# TediousLee

## 题目描述

首先，我们定义 `RDB` 为一棵具有特殊性质的树，它有一个级别 $level$。  
一个级别为 $1$ 的 `RDB` 是一个单独的节点。
接着，对于所有 $i>1$，级别为 $i$ 的 `RDB` 的构成方法如下。  
先求出级别为 $i-1$ 的 `RDB`，然后对于该 `RDB` 中的每个节点 $x$。  

- 如果 $x$ 没有孩子，那么给他加上一个孩子。  
- 如果 $x$ 只有一个孩子，那么给他加上两个孩子。  
- 如果 $x$ 已经有了超过一个孩子，那么我们跳过节点 $x$。  

以下是 $1\le n \le 3$ 的所有 `RDB`

![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGMTM2OUQvNjRjNjY3Zjg4YjBiYTNiNThhNDU4MWU4ZjcyNmQ0ODQ3ZDk3N2E2Yy5wbmc?x-oss-process=image/format,png)

接下来，我们定义一个 `claw`  （见下图），它也是一棵具有特殊性质的树，并且将节点 $1$ 称为这个 `claw` 的中心，其他的称为底部节点。

![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9jZG4ubHVvZ3UuY29tLmNuL3VwbG9hZC92anVkZ2VfcGljL0NGMTM2OUQvNDE0MmRhNTE0NDVmNGNmY2UxNmVhNjhkOTY4MzJjYWFiZjE3YWNjZS5wbmc?x-oss-process=image/format,png)

现在，给出一个级别为 $n$ 的 `RDB`，初始时他上面的所有节点都为绿色，你可以进行一些操作。  
对于每次操作，你需要在给出的 `RDB` 中找到一个 `claw`，满足所有底部节点在 `RDB` 中都是中心节点的儿子，且这四个节点在 `RDB` 中都是绿色。然后将这四个节点染为黄色。  
问最多可以将多少个节点染成黄色。

## 输入格式

第一行一个整数 $T$，表示数据的组数。  
接下来 $T$ 行，每行一个正整数 $n$，表示有一棵级别为 $n$ 的 `RDB`。

## 输出格式

输出有 $n$ 行，每行一个整数，对应每组数据的答案。  
这个答案可能很大，所以输出它对 $10^9+7$ 取模后的结果。

## 说明/提示

$1\le T\le 10^4$  
$1\le n \le 2\cdot 10^6$

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
7
1
2
3
4
5
100
2000000
```

### 输出

```
0
0
4
4
12
990998587
804665184
```

