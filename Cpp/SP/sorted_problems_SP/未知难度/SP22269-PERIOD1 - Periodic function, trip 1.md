---
title: "PERIOD1 - Periodic function, trip 1"
layout: "post"
diff: 难度0
pid: SP22269
tag: []
---

# PERIOD1 - Periodic function, trip 1

## 题目描述

![Fourier Cat](../../content/francky:FourierCat "http://xkcd.com/26/")[xkcd/26](http://xkcd.com/26/)

## 输入格式

第一行包含一个整数 $T$，即测试用例的数量。接下来的 $T$ 行中，每行给出一个整数 $N$。我们需要考虑周期为 $n$ 的函数族，其中 $n$ 在 $[1, N]$ 之间。这些函数之间存在一定的关联关系，比如说：\[2, 0\] 可以表示为 \[2, 0, 1, 0\] + \[0, 0, 1, 0\]，这里采用了一种简化的符号表示方法。

## 输出格式

输出这个函数族的秩，也就是这个函数族中能够找到的最大的线性无关集合大小。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2
3
4
```

### 输出

```
2
4
6
```

