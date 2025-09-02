---
title: "Making Anti-Palindromes"
layout: "post"
diff: 普及+/提高
pid: CF1822E
tag: []
---

# Making Anti-Palindromes

## 题目描述

给您一个由小写字母组成的字符串 $s$，在每次操作中，您可以交换 $s$ 中的任意两个字母，请问把 $s$ 变为“反回文串”的最小操作次数是多少？


“反回文串”定义为：对于一个长度为 $n$ 的字符串 $s$，如果对于任意 $1\leqslant i\leqslant n$ 均有 $s_i\not=s_{n-i+1}$，那么字符串 $s$ 就叫做“反回文串”。

## 输入格式

第一行包含一个正整数 $ t $ ( $ 1 \le t \le 10^4 $ ) ，表示询问次数。

每次询问包含两行， 第一行包含一个整数 $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) ，表示字符串 $ s $ 的长度；第二行为一个由 $ n $ 个小写英文字母组成的字符串 $ s $。

所有询问的 $ n $ 之和不会超过 $ 2 \cdot 10^5 $ 。

## 输出格式

对于每次询问，输出一个整数，表示把 $ s $ 变为“反回文串”的最小操作次数, 如果无法把 $s$ 变为“反回文串”，输出 `-1`。

## 样例 #1

### 输入

```
10
10
codeforces
3
abc
10
taarrrataa
10
dcbdbdcccc
4
wwww
12
cabbaccabaac
10
aadaaaaddc
14
aacdaaaacadcdc
6
abccba
12
dcbcaebacccd
```

### 输出

```
0
-1
1
1
-1
3
-1
2
2
2
```

