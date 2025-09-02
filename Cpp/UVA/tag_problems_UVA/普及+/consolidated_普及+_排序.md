---
title: "传说中的车 Fabled Rooks"
layout: "post"
diff: 普及+/提高
pid: UVA11134
tag: ['贪心', '排序', '二分图']
---

# 传说中的车 Fabled Rooks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2075

[PDF](https://uva.onlinejudge.org/external/111/p11134.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/bd6c0f2fb7433acc9184472bbe18e9f1a53f823f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/4e1549d0f9cab4c45c78627adabecc71e886e762.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/81fe8f66faa05106571245120e3fbecf732028ae.png)

## 样例 #1

### 输入

```
8
1 1 2 2
5 7 8 8
2 2 5 5
2 2 5 5
6 3 8 6
6 3 8 5
6 3 8 8
3 6 7 8
8
1 1 2 2
5 7 8 8
2 2 5 5
2 2 5 5
6 3 8 6
6 3 8 5
6 3 8 8
3 6 7 8
0
```

### 输出

```
1 1
5 8
2 4
4 2
7 3
8 5
6 6
3 7
1 1
5 8
2 4
4 2
7 3
8 5
6 6
3 7
```



---

---
title: "和为 0 的 4 个值 4 Values whose Sum is 0"
layout: "post"
diff: 普及+/提高
pid: UVA1152
tag: ['二分', '枚举', '排序']
---

# 和为 0 的 4 个值 4 Values whose Sum is 0

## 题目描述

给出四个数组  $A,B,C,D$ ，每个数组中有  $n$  个整数。求有多少组  $i,j,k,l$  满足  $A_i+B_j+C_k+D_l=0$ 。

## 输入格式

**本题有多组测试数据。**

第一行一个正整数  $T$ ，表示数据组数。

对于每组数据:

第一行一个整数  $n$ 。

接下来  $n$  行，一行四个整数，分别表示  $A_i,B_i,C_i,D_i$ 。

## 输出格式

共  $2\times T$  行。

对于每组数据：

第一行一个整数，表示该组测试数据的答案。

接下来输出一个空行。

## 说明/提示

$1\le n\le4000$ 。数组中所有数的绝对值不大于  $2^{28}$ 。



---

---
title: "单向TSP Unidirectional TSP"
layout: "post"
diff: 普及+/提高
pid: UVA116
tag: ['动态规划 DP', '排序', '最短路']
---

# 单向TSP Unidirectional TSP

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=52

[PDF](https://uva.onlinejudge.org/external/1/p116.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/8f55250e58c560c3ec06a86150f26e2b1e1f75c6.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/801aba8894b1c630f564c73247a3de8b316ca7cf.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA116/f42899d4753927986e0c7f639bd537f5a3da0a4c.png)

## 样例 #1

### 输入

```
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 8 6 4
5 6
3 4 1 2 8 6
6 1 8 2 7 4
5 9 3 9 9 5
8 4 1 3 2 6
3 7 2 1 2 3
2 2
9 10 9 10
```

### 输出

```
1 2 3 4 4 5
16
1 2 1 5 4 5
11
1 1
19
```



---

---
title: "Supermarket"
layout: "post"
diff: 普及+/提高
pid: UVA1316
tag: ['贪心', '并查集', '排序']
---

# Supermarket

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4062

[PDF](https://uva.onlinejudge.org/external/13/p1316.pdf)

## 样例 #1

### 输入

```
4 50 2 10 1 20 2 30 1
7 20 1 2 1 10 3 100 2 8 2 5 20 50 10
```

### 输出

```
80 
185
```



---

---
title: "Hypertransmission"
layout: "post"
diff: 普及+/提高
pid: UVA1325
tag: ['枚举', '排序']
---

# Hypertransmission

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4071

[PDF](https://uva.onlinejudge.org/external/13/p1325.pdf)



---

---
title: "Anagram"
layout: "post"
diff: 普及+/提高
pid: UVA195
tag: ['排序']
---

# Anagram

## 输出格式

感谢@dogfar 提供的翻译

## 样例 #1

### 输入

```
3
aAb
abc
acba
```

### 输出

```
Aab
Aba
aAb
abA
bAa
baA
abc
acb
bac
bca
cab
cba
aabc
aacb
abac
abca
acab
acba
baac
baca
bcaa
caab
caba
cbaa
```



---

