---
title: "大理石在哪儿 Where is the Marble?"
layout: "post"
diff: 普及-
pid: UVA10474
tag: ['搜索', '二分', '递归', '枚举', '排序']
---

# 大理石在哪儿 Where is the Marble?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1415

[PDF](https://uva.onlinejudge.org/external/104/p10474.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/2bb1c26d80e7830dba0391c0afa3b04c198f8ee0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/6c2a03977a6e49d286d2fa5cc116d53d9da95e8b.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10474/03b79b1f48ddec6133706f0b92ca55a3ecd02a38.png)

## 样例 #1

### 输入

```
4 1
2
3
5
1
5
5 2
1
3
3
3
1
2
3
0 0
```

### 输出

```
CASE# 1:
5 found at 4
CASE# 2:
2 not found
3 found at 3
```



---

---
title: "The Wedding"
layout: "post"
diff: 普及-
pid: UVA10662
tag: ['枚举']
---

# The Wedding

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=18&page=show_problem&problem=1603

[PDF](https://uva.onlinejudge.org/external/106/p10662.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10662/ab41e0babb1499da2a267d5f5662f0b7680375d6.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10662/e776e9cac9929d4317c383d59ddc5df445b4a597.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10662/ecea46e33e04efcd8549429096690e8743c70af2.png)

## 样例 #1

### 输入

```
2 2 2
12 0 0
1 1 1
34 0 0
3 1 1
21 1 0
2 1 0
2 2 2
12 0 0
1 0 0
34 0 0
3 0 0
21 0 0
2 0 0
5 5 6
970 0 1 1 1 0
856 0 0 0 0 0
1290 1 0 0 1 0
1361 0 0 1 0 0
82 0 0 0 0 1
1182 0 0 0 1 1 0
450 0 1 1 0 0 1
895 0 0 1 0 1 1
1865 0 1 0 0 1 1
183 1 1 1 1 1 0
252 1 1 1 0 1
1813 1 0 0 1 1
1429 0 0 1 0 0
1522 1 1 1 0 0
1762 0 0 1 0 1
1946 0 1 0 0 0
```

### 输出

```
Don't get married!
1 1 1:6
4 1 3:2054
```



---

---
title: "最大乘积 Maximum Product"
layout: "post"
diff: 普及-
pid: UVA11059
tag: ['搜索', '枚举', '前缀和']
---

# 最大乘积 Maximum Product

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=2000

[PDF](https://uva.onlinejudge.org/external/110/p11059.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/65771c7c6d1492d75695a5505a88282671afede0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/057abe21049b4423b1de44dfdc2de12075eae6eb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11059/341e4b9b0d67601bc1876729c0e2aae16988584e.png)

## 样例 #1

### 输入

```
3
2 4 -3
5
2 5 -1 2 -1
```

### 输出

```
Case #1: The maximum product is 8.

Case #2: The maximum product is 20.
```



---

---
title: "GCD"
layout: "post"
diff: 普及-
pid: UVA11417
tag: ['枚举']
---

# GCD

## 题目描述

给定 $n$ ，求
$$\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n\gcd(i,j)$$
其中 $\gcd(i,j)$ 指的是 $i$ 和 $j$ 的最大公约数。

## 输入格式

**本题有多组数据。**

对于每组数据，输出一个整数 $n$ ，如果 $n=0$ 就终止程序。

## 输出格式

对于每组数据，输出计算结果。

## 说明/提示

对于 $100\%$ 的数据，$1 \le n \le 501$ 。

## 样例 #1

### 输入

```
10
100
500
0
```

### 输出

```
67
13015
442011
```



---

---
title: "Fill the Square"
layout: "post"
diff: 普及-
pid: UVA11520
tag: ['枚举']
---

# Fill the Square

## 题目描述

在一个$n*n$的网格中填了一些大写字母，你的任务是把剩下的格子中也填满大写字母，使得任意两个相邻的格子(即有公共边的格子)中的字母不同。如果有多种填法，则要求按照从上到下，从左到右的顺序把所以格子连接起来得到的字符串的字典序应该尽量小。

## 输入格式

输入的第一行为测试数据的组数$T$.每组数据的第一行为$n(1<=10)$,即网格的行数和列数；以下$n$行每行$n$个字符，表示整个网格。为了清楚起见，本题用小数点表示没有填字母的格子。

## 输出格式

对于每组数据，输出填满字母后的网格

感谢@洛谷万岁 提供的翻译

## 样例 #1

### 输入

```
2
3
...
...
...
3
...
A..
...
```

### 输出

```
Case 1:
ABA
BAB
ABA
Case 2:
BAB
ABA
BAB
```



---

---
title: "丑数 Ugly Numbers"
layout: "post"
diff: 普及-
pid: UVA136
tag: ['枚举', '优先队列', '队列']
---

# 丑数 Ugly Numbers

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=72

[PDF](https://uva.onlinejudge.org/external/1/p136.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/9235847457e3c8f707f609605cbc21fd7bb05029.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/ed5a845059370c8ba7ec4955b10f7eead4ab3787.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA136/c8116baef73c601c2156d6d31ee1e30b14b9b560.png)

## 样例 #1

### 输入

```

```

### 输出

```
The 1500'th ugly number is &lt;number&gt;.
```



---

---
title: "生成元 Digit Generator"
layout: "post"
diff: 普及-
pid: UVA1583
tag: ['枚举']
---

# 生成元 Digit Generator

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4458

[PDF](https://uva.onlinejudge.org/external/15/p1583.pdf)

## 样例 #1

### 输入

```
3
216
121
2005
```

### 输出

```
198
0
1979
```



---

---
title: "对称轴 Symmetry"
layout: "post"
diff: 普及-
pid: UVA1595
tag: ['枚举', '排序', '构造']
---

# 对称轴 Symmetry

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4470

[PDF](https://uva.onlinejudge.org/external/15/p1595.pdf)



---

---
title: "除法 Division"
layout: "post"
diff: 普及-
pid: UVA725
tag: ['枚举']
---

# 除法 Division

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=9&page=show_problem&problem=666

[PDF](https://uva.onlinejudge.org/external/7/p725.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA725/9177f6f6723402a8ca5cd51e53c7912c7289196b.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA725/eb406bd4ea0c6d996b8d045c8d41bdca36a0713e.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA725/03ea8e037e00b0eb98a658d2d9f018fa5375f0c6.png)

## 样例 #1

### 输入

```
61
62
0
```

### 输出

```
There are no solutions for 61.

79546 / 01283 = 62
94736 / 01528 = 62
```



---

