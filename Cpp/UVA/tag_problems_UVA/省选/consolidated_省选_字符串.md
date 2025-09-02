---
title: "Always an integer"
layout: "post"
diff: 省选/NOI-
pid: UVA1069
tag: ['字符串']
---

# Always an integer

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=245&page=show_problem&problem=3510

[PDF](https://uva.onlinejudge.org/external/10/p1069.pdf)



---

---
title: "Jewel Magic"
layout: "post"
diff: 省选/NOI-
pid: UVA11996
tag: ['字符串', '哈希 hashing', '概率论']
---

# Jewel Magic

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3147

[PDF](https://uva.onlinejudge.org/external/119/p11996.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/2bab589816720983ab635f9484728b78d4993b0f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/f01f1337a503a06d908bccf8ce9f1b2f678759c7.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/07591e46a067540334a0ba60ca15ea251c41da0e.png)

## 样例 #1

### 输入

```
12 9
000100001100
1 0 1
4 2 6
3 7 10
4 1 7
2 9
4 3 11
4 1 9
4 1 7
4 2 3
```

### 输出

```
3
6
2
0
3
2
```



---

---
title: "串折叠 Folding"
layout: "post"
diff: 省选/NOI-
pid: UVA1630
tag: ['字符串', '动态规划 DP']
---

# 串折叠 Folding

## 题目描述

折叠由大写字母组成的长度为 $n$（$1\leqslant n\leqslant100$）的一个字符串，使得其成为一个尽量短的字符串，例如 `AAAAAA` 变成 `6(A)`。

这个折叠是可以嵌套的，例如 `NEEEEERYESYESYESNEEEEERYESYESYES` 会变成 `2(N5(E)R3(YES))`。

多解时可以输出任意解。

Translated by @_UKE自动机_

## 输入格式

**输入有多组数据**。

输入若干行，第 $i$ 行有一个仅由大写字母组成的，长度小于等于 $100$ 的字符串。

## 输出格式

对于每组输入，输出折叠后的字符串。

多解时可以输出任意解。

## 样例 #1

### 输入

```
AAAAAAAAAABABABCCD
NEERCYESYESYESNEERCYESYESYES
```

### 输出

```
9(A)3(AB)CCD
2(NEERC3(YES))
```



---

