---
title: "ADASEQEN - Ada and Subsequence"
layout: "post"
diff: 难度0
pid: SP32945
tag: []
---

# ADASEQEN - Ada and Subsequence

## 题目描述

给你两个由小写字母组成的字符串，告诉你 $26$ 个字母对应的价值，问你最大公共子序列（就是所有子序列中价值最大的）的价值。

字符串 $a,b$ 的长度 $n,m\le2\times10^3$。

## 输入格式

第一行两个整数 $n,m$ 表示两个字符串的长度。

第二行 $26$ 个整数表示每个字母对应的价值。

第三行输入一个长度为 $n$ 的字符串 $a$，第四行输入了一个长度为 $m$ 的字符串 $b$。

## 输出格式

输出一行一个正整数表示答案。

### 输入输出样例
Example Input
```
4 4
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
abcd
dbca
```
Example Output
```
2
```
Example Input
```
3 3
1 7 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
baa
aab
```
Example Output
```
7
```
Example Input
```
4 5
1 4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 6
zbbz
bbzbb
```
Example Output
```
14
```
Example Input
```
3 3
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
abc
def
```
Example Output
```
0
```

