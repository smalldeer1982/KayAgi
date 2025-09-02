---
title: "The Vigenère Cipher"
layout: "post"
diff: 难度0
pid: UVA856
tag: []
---

# The Vigenère Cipher

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=797

[PDF](https://uva.onlinejudge.org/external/8/p856.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA856/59861c0334365423b44cee3a51adf4001a5680fc.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA856/829a97b70eb0017f2650d514c0e02f413993ea8b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA856/941993b6e8dc07e7297725b8be9def6caf8c3852.png)

## 样例 #1

### 输入

```
PQRPQRPQR
PQRPQRPQR
```

### 输出

```
WHTWHTWHT -&gt; sixsixsix
WHTWHTVTC -&gt; sixsixtwo
WHTWHTACM -&gt; sixsixone
WHTVTCWHT -&gt; sixtwosix
WHTVTCVTC -&gt; sixtwotwo
WHTVTCACM -&gt; sixtwoone
WHTACMWHT -&gt; sixonesix
WHTACMVTC -&gt; sixonetwo
WHTACMACM -&gt; sixoneone
VTCWHTWHT -&gt; twosixsix
VTCWHTVTC -&gt; twosixtwo
VTCWHTACM -&gt; twosixone
VTCVTCWHT -&gt; twotwosix
VTCVTCVTC -&gt; twotwotwo
VTCVTCACM -&gt; twotwoone
VTCACMWHT -&gt; twoonesix
VTCACMVTC -&gt; twoonetwo
VTCACMACM -&gt; twooneone
ACMWHTWHT -&gt; onesixsix
ACMWHTVTC -&gt; onesixtwo
ACMWHTACM -&gt; onesixone
ACMVTCWHT -&gt; onetwosix
ACMVTCVTC -&gt; onetwotwo
ACMVTCACM -&gt; onetwoone
ACMACMWHT -&gt; oneonesix
ACMACMVTC -&gt; oneonetwo
ACMACMACM -&gt; oneoneone
WHTWHTWHT -&gt; sixsixsix
WHTWHTVTC -&gt; sixsixtwo
WHTWHTACM -&gt; sixsixone
WHTVTCWHT -&gt; sixtwosix
WHTVTCVTC -&gt; sixtwotwo
WHTVTCACM -&gt; sixtwoone
WHTACMWHT -&gt; sixonesix
WHTACMVTC -&gt; sixonetwo
WHTACMACM -&gt; sixoneone
VTCWHTWHT -&gt; twosixsix
VTCWHTVTC -&gt; twosixtwo
VTCWHTACM -&gt; twosixone
VTCVTCWHT -&gt; twotwosix
VTCVTCVTC -&gt; twotwotwo
VTCVTCACM -&gt; twotwoone
VTCACMWHT -&gt; twoonesix
VTCACMVTC -&gt; twoonetwo
VTCACMACM -&gt; twooneone
ACMWHTWHT -&gt; onesixsix
ACMWHTVTC -&gt; onesixtwo
ACMWHTACM -&gt; onesixone
ACMVTCWHT -&gt; onetwosix
ACMVTCVTC -&gt; onetwotwo
ACMVTCACM -&gt; onetwoone
ACMACMWHT -&gt; oneonesix
ACMACMVTC -&gt; oneonetwo
ACMACMACM -&gt; oneoneone
```

