---
title: "STC02 - Antisymmetry"
layout: "post"
diff: 提高+/省选-
pid: SP15569
tag: ['二分', '枚举', '哈希 hashing', 'Manacher 算法']
---

# STC02 - Antisymmetry

## 题目描述

对于一个 01 字符串，如果将这个字符串 0 和 1 取反后，再将整个串反过来和原串一样，就称作「反对称」字符串。比如 00001111 和 010101 就是反对称的，而 1001 就不是。 现在给出一个长度为 n 的 01 字符串，求它有多少个子串是反对称的，注意这里相同的子串出现在不同的位置会被重复计算。

## 输出格式

Translated by @xzjds



---

---
title: "NETADMIN - Smart Network Administrator"
layout: "post"
diff: 提高+/省选-
pid: SP287
tag: ['二分', '网络流']
---

# NETADMIN - Smart Network Administrator

## 题目描述

 The citizens of a small village are tired of being the only inhabitants around without a connection to the Internet. After nominating the future network administrator, his house was connected to the global network. All users that want to have access to the Internet must be connected directly to the admin's house by a single cable (every cable may run underground along streets only, from the admin's house to the user's house). Since the newly appointed administrator wants to have everything under control, he demands that cables of different colors should be used. Moreover, to make troubleshooting easier, he requires that no two cables of the same color go along one stretch of street.

 Your goal is to find the minimum number of cable colors that must be used in order to connect every willing person to the Internet.

## 输入格式

 _t_ \[the number of test cases, t<=500\]  
_n m k_ \[_n_ <=500 the number of houses (the index of the admin's house is 1)\]  
 \[_m_ the number of streets, _k_ the number of houses to connect\]  
_h_ $ _{1} $ _h_ $ _{2} $ ... _h $ _{k} $_  \[a list of _k_ houses wanting to be conected to the network, 2<=_h $ _{i} $_ <=_n_\]  
 \[The next _m_ lines contain pairs of house numbers describing street ends\]  
_e_ $ _{11} $ _e_ $ _{12} $   
_e_ $ _{21} $ _e_ $ _{22} $   
 ...  
_e_ $ _{m1} $ _e_ $ _{m2} $   
 \[next cases\]

## 输出格式

 For each test case print the minimal number of cable colors necessary to make all the required connections.

## 样例 #1

### 输入

```
2

5 5 4

2 3 4 5

1 2

1 3

2 3

2 4

3 5

8 8 3

4 5 7

1 2

1 8

8 7

1 3

3 6

3 2

2 4

2 5
```

### 输出

```
2

1
```



---

