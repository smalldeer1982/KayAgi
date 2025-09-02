---
title: "MINCOUNT - Move To Invert"
layout: "post"
diff: 普及-
pid: SP1167
tag: []
---

# MINCOUNT - Move To Invert

## 题目描述

题目简述：

有一个高为h的硬币三角形，它的底部有h个硬币，倒数第2层有h-1个硬币，以此类推，最上层有1个硬币。问题是如何通过移动最少数量的硬币来翻转这个三角形。
![](https://cdn.luogu.org/upload/vjudge_pic/SP1167/9e6385b0d52afa178ab5facf98b60a551e521074.png)
在h=4的情况下，至少需要移动3个硬币才能翻转这个三角形。

## 输入格式

第一行为一个数N，表示有N个问题。下面有N行，为高度h，
0<=h<=10^10。

## 输出格式

N行，第i行对应第i个问题的答案。保证所有答案在long long范围内。

感谢@暴力通天下233 提供的翻译

## 样例 #1

### 输入

```
t:
1
3
```

### 输出

```
2
```

