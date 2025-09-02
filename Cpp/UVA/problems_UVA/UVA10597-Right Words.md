---
title: "Right Words"
layout: "post"
diff: 难度0
pid: UVA10597
tag: []
---

# Right Words

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1538

[PDF](https://uva.onlinejudge.org/external/105/p10597.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10597/6fb2860e45302802335c13c8433ffe968d74d946.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10597/a8d4ed5d3d2fd2bb3b66d204c6e26a8d84d04912.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10597/8c64737d3951e9b42a3ac27a5eb8628c285c9d27.png)

## 样例 #1

### 输入

```
S
SABC
ab
S -&gt; AB
S -&gt; BC
A -&gt; BA
A -&gt; a
B -&gt; CC
B -&gt; b
C -&gt; AB
C -&gt; a
# -&gt; #
baaba
ab
abaa
a
aaaaa
bbbbb
#
S
SAB
ab
S -&gt; AB
A -&gt; AA
A -&gt; a
B -&gt; b
# -&gt; #
ab
aaab
aba
baaaaaaaa
abbbbbb
aaaaaba
baaaaaaaab
aaaa
a
ab
#
```

### 输出

```
baaba is in L(G)
ab is in L(G)
abaa is in L(G)
a is not in L(G)
aaaaa is in L(G)
bbbbb is not in L(G)
ab is in L(G)
aaab is in L(G)
aba is not in L(G)
baaaaaaaa is not in L(G)
abbbbbb is not in L(G)
aaaaaba is not in L(G)
baaaaaaaab is not in L(G)
aaaa is not in L(G)
a is not in L(G)
ab is in L(G)
```

