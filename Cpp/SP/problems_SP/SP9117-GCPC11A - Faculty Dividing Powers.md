---
title: "GCPC11A - Faculty Dividing Powers"
layout: "post"
diff: 难度0
pid: SP9117
tag: []
---

# GCPC11A - Faculty Dividing Powers

## 题目描述

Fred Faculty 和 Paul Power 对大数字情有独钟。每天，Fred 都会随机挑选一个整数 $n$，然后计算它的阶乘 $n!$。与此同时，Paul 则通过计算一个随机整数 $k$ 的不同幂次（比如 $k^2$, $k^3$ 等）来玩乐。在一个炎热的夏天，Fred 和 Paul 实在无聊得无所事事，于是他们想给朋友 Dave Divider 开个玩笑。Fred 选择了一个整数 $n$，Paul 选择了一个整数 $k$，他们要求 Dave 找到最大的整数 $i$，使得 $k^i$ 可以整除 $n!$。如果 Dave 做不到，他们就把蛋糕扔在他的脸上。为了避免这样不幸的事情发生，Dave 希望你帮他找到那个最大整数 $i$。

## 输入格式

第一行输入一个整数 $t$，表示测试用例的数量 ($1 \le t \le 1000$)。接下来的每一行包含两个用空格分隔的整数 $n$ 和 $k$，满足 $2 \le n, k \le 1000$。

## 输出格式

对于每个测试用例，输出一行结果，表示最大的整数 $i$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
5 2
10 10
```

### 输出

```
3
2
```

