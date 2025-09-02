---
title: "Square Equation Roots"
layout: "post"
diff: 提高+/省选-
pid: CF50E
tag: []
---

# Square Equation Roots

## 题目描述

A schoolboy Petya studies square equations. The equations that are included in the school curriculum, usually look simple:

 $ x^{2}+2bx+c=0 $  where $ b $ , $ c $ are natural numbers.Petya noticed that some equations have two real roots, some of them have only one root and some equations don't have real roots at all. Moreover it turned out that several different square equations can have a common root.

Petya is interested in how many different real roots have all the equations of the type described above for all the possible pairs of numbers $ b $ and $ c $ such that $ 1<=b<=n $ , $ 1<=c<=m $ . Help Petya find that number.

## 输入格式

The single line contains two integers $ n $ and $ m $ . ( $ 1<=n,m<=5000000 $ ).

## 输出格式

Print a single number which is the number of real roots of the described set of equations.

## 说明/提示

In the second test from the statement the following equations are analysed:

 $ b=1 $ , $ c=1 $ : $ x^{2}+2x+1=0 $ ; The root is $ x=-1 $

 $ b=1 $ , $ c=2 $ : $ x^{2}+2x+2=0 $ ; No roots

 Overall there's one root

In the second test the following equations are analysed:

 $ b=1 $ , $ c=1 $ : $ x^{2}+2x+1=0 $ ; The root is $ x=-1 $

 $ b=1 $ , $ c=2 $ : $ x^{2}+2x+2=0 $ ; No roots

 $ b=1 $ , $ c=3 $ : $ x^{2}+2x+3=0 $ ; No roots

 $ b=2 $ , $ c=1 $ : $ x^{2}+4x+1=0 $ ; The roots are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50E/3991ec922d7c769ae489eea64c57c2bbb41b0c54.png)

 $ b=2 $ , $ c=2 $ : $ x^{2}+4x+2=0 $ ; The roots are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50E/5d07b9483ebb741bb80c778aae623d469ac94a4a.png)

 $ b=2 $ , $ c=3 $ : $ x^{2}+4x+3=0 $ ; The roots are $ x_{1}=-3,x_{2}=-1 $

 $ b=3 $ , $ c=1 $ : $ x^{2}+6x+1=0 $ ; The roots are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50E/30c496d75cf97e85908b57bf3d939afa2185247b.png)

 $ b=3 $ , $ c=2 $ : $ x^{2}+6x+2=0 $ ; The roots are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50E/6c503238cbe1ecf3a5382e37b1c706ca9a71b27d.png)

 $ b=3 $ , $ c=3 $ : $ x^{2}+6x+3=0 $ ; The roots are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF50E/7103d2deaa4e6cd061273d09630c96da35ced6a7.png) Overall there are $ 13 $ roots and as the root $ -1 $ is repeated twice, that means there are $ 12 $ different roots.

## 样例 #1

### 输入

```
3 3

```

### 输出

```
12

```

## 样例 #2

### 输入

```
1 2

```

### 输出

```
1

```

