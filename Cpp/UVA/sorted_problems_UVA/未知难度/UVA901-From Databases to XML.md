---
title: "From Databases to XML"
layout: "post"
diff: 难度0
pid: UVA901
tag: []
---

# From Databases to XML

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=11&page=show_problem&problem=842

[PDF](https://uva.onlinejudge.org/external/9/p901.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA901/dd96b1147a2e36aad5bec7754e9009f926436e6a.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA901/e73281ed452143ee631ea04c281c97bb7a339b58.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA901/dc52dcd96631a038c51b72f0bfb4d6f1b5596bb5.png)

## 样例 #1

### 输入

```
S(#C,A,D)
R(#A,B)
T(E,A)
data
T(e1,a2)
S(c3,a1,d1)
S(c1,a2,d2)
S(c2,a1,d3)
R(a1,b1)
R(a2,b2)
```

### 输出

```
&lt;DB&gt;
&lt;R #A="a1" B="b1"&gt;
&lt;S #C="c2" D="d3"&gt;
&lt;/S&gt;
&lt;S #C="c3" D="d1"&gt;
&lt;/S&gt;
&lt;/R&gt;
&lt;R #A="a2" B="b2"&gt;
&lt;S #C="c1" D="d2"&gt;
&lt;/S&gt;
&lt;T E="e1"&gt;
&lt;/T&gt;
&lt;/R&gt;
&lt;/DB&gt;
```

