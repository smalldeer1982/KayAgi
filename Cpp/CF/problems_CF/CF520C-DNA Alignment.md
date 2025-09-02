---
title: "DNA Alignment"
layout: "post"
diff: 普及/提高-
pid: CF520C
tag: []
---

# DNA Alignment

## 题目描述

Vasya became interested in bioinformatics. He's going to write an article about similar cyclic DNA sequences, so he invented a new method for determining the similarity of cyclic sequences.

Let's assume that strings $ s $ and $ t $ have the same length $ n $ , then the function $ h(s,t) $ is defined as the number of positions in which the respective symbols of $ s $ and $ t $ are the same. Function $ h(s,t) $ can be used to define the function of Vasya distance $ ρ(s,t) $ :

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF520C/0b4348c88074431fd692746719c4a6f852a88ac1.png) where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF520C/e04d6b40ed912903e989b816c65cd323f288312f.png) is obtained from string $ s $ , by applying left circular shift $ i $ times. For example,  $ ρ(&quot;AGC&quot;,&quot;CGT&quot;)= $   $ h(&quot;AGC&quot;,&quot;CGT&quot;)+h(&quot;AGC&quot;,&quot;GTC&quot;)+h(&quot;AGC&quot;,&quot;TCG&quot;)+ $   $ h(&quot;GCA&quot;,&quot;CGT&quot;)+h(&quot;GCA&quot;,&quot;GTC&quot;)+h(&quot;GCA&quot;,&quot;TCG&quot;)+ $   $ h(&quot;CAG&quot;,&quot;CGT&quot;)+h(&quot;CAG&quot;,&quot;GTC&quot;)+h(&quot;CAG&quot;,&quot;TCG&quot;)= $   $ 1+1+0+0+1+1+1+0+1=6 $ Vasya found a string $ s $ of length $ n $ on the Internet. Now he wants to count how many strings $ t $ there are such that the Vasya distance from the string $ s $ attains maximum possible value. Formally speaking, $ t $ must satisfy the equation: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF520C/106c86f5cd7beb20b5aaf5b6e98985a65f7d4450.png).

Vasya could not try all possible strings to find an answer, so he needs your help. As the answer may be very large, count the number of such strings modulo $ 10^{9}+7 $ .

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ).

The second line of the input contains a single string of length $ n $ , consisting of characters "ACGT".

## 输出格式

Print a single number — the answer modulo $ 10^{9}+7 $ .

## 说明/提示

Please note that if for two distinct strings $ t_{1} $ and $ t_{2} $ values $ ρ(s,t_{1}) $ и $ ρ(s,t_{2}) $ are maximum among all possible $ t $ , then both strings must be taken into account in the answer even if one of them can be obtained by a circular shift of another one.

In the first sample, there is $ ρ(&quot;C&quot;,&quot;C&quot;)=1 $ , for the remaining strings $ t $ of length 1 the value of $ ρ(s,t) $ is 0.

In the second sample, $ ρ(&quot;AG&quot;,&quot;AG&quot;)=ρ(&quot;AG&quot;,&quot;GA&quot;)=ρ(&quot;AG&quot;,&quot;AA&quot;)=ρ(&quot;AG&quot;,&quot;GG&quot;)=4 $ .

In the third sample, $ ρ(&quot;TTT&quot;,&quot;TTT&quot;)=27 $

## 样例 #1

### 输入

```
1
C

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
AG

```

### 输出

```
4

```

## 样例 #3

### 输入

```
3
TTT

```

### 输出

```
1

```

