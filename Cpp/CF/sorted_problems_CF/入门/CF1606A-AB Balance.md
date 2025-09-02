---
title: "AB Balance"
layout: "post"
diff: 入门
pid: CF1606A
tag: []
---

# AB Balance

## 题目描述

### 题意简述

给定一个字符串 $s$，定义 $\mathrm{AB}(s)$ 为 $s$ 中串 `ab` 出现的次数，$\mathrm{BA}(s)$，为 `ba` 出现的次数。

每次可以修改一个字符，要求通过尽量少的操作 ，使得 $\mathrm{AB}(s)=\mathrm{BA}(s)$。输出修改后的字符串。

## 输入格式

多组测试，先输入整数 $T\ (1\le T\le 1000)$。

接下来 $T$ 行，每行一个字符串 $s\ (1\le|s|\le 100)$。

## 输出格式

对于每组数据，输出一个字符串表示答案。

## 样例 #1

### 输入

```
4
b
aabbbabaa
abbb
abbaab
```

### 输出

```
b
aabbbabaa
bbbb
abbaaa
```

