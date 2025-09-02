---
title: "Maximum in Table"
layout: "post"
diff: 入门
pid: CF509A
tag: ['动态规划 DP', '递推', '递归']
---

# Maximum in Table

## 题目描述

给定一个 $N$ * $N$ 的矩阵，令 $a_{i,j}$ 为矩阵中第i行第j列的元素，则有：
1. $a_{k,1}=a_{1,k}=1(1≤k≤N)$ 
2. $a_{i,j}=a_{i-1,j}+a_{i,j-1}(2≤i,j≤N)$ 
现请求出该矩阵中最大元素的值。

## 输入格式

一行一个正整数 $N(N ≤ 10)$ 。

## 输出格式

一行一个正整数表示上述答案。

## 样例 #1

### 输入

```
1

```

### 输出

```
1
```

## 样例 #2

### 输入

```
5

```

### 输出

```
70
```



---

---
title: "Joysticks"
layout: "post"
diff: 入门
pid: CF651A
tag: ['模拟', '贪心', '递归']
---

# Joysticks

## 题目描述

朋友们正要去玩游戏机。他们有两个游戏机，却只有一个充电器。最开始第一个游戏机有a1%的电，第二个游戏机有a2%的电。你只能在每分钟的最开始将一个游戏机接上充电器。每一分钟每个游戏机会消耗2%的电（如果没有接上充电器）或者充上1%的电（如果接上了充电器）。

当两个游戏机都有电时游戏才能继续。因此，如果在某一分钟的开始某个游戏机只有1%的电，它必须接上充电器，否则游戏会停止。如果某个游戏机完全没电（它的电量变为0），游戏也会停下。

试确定该游戏能够持续的最长时间。禁止暂停游戏，即在每一分钟两个游戏机都应该在使用。允许将游戏机充电到超过100%的电量。

## 输入格式

输入的第一行包括两个正整数a1、a2（1 <= a1、a2 <= 100），分别表示第一个游戏机和第二个游戏机的初始电量。

## 输出格式

输出一个整数，游戏能够持续的最长时间。在某一个游戏机没电之前游戏继续。

感谢@蒟蒻的PSJ 提供的翻译

## 样例 #1

### 输入

```
3 5

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 4

```

### 输出

```
5

```



---

---
title: "QAQ"
layout: "post"
diff: 入门
pid: CF894A
tag: ['字符串', '递归', '枚举']
---

# QAQ

## 题目描述

"QAQ" is a word to denote an expression of crying. Imagine "Q" as eyes with tears and "A" as a mouth.

Now Diamond has given Bort a string consisting of only uppercase English letters of length $ n $ . There is a great number of "QAQ" in the string (Diamond is so cute!).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF894A/333c4dadce3b03c143ff500b3cc7457c4f2b76a3.png)illustration by 猫屋 https://twitter.com/nekoyaliuBort wants to know how many subsequences "QAQ" are in the string Diamond has given. Note that the letters "QAQ" don't have to be consecutive, but the order of letters should be exact.

## 输入格式

The only line contains a string of length $ n $ ( $ 1<=n<=100 $ ). It's guaranteed that the string only contains uppercase English letters.

## 输出格式

Print a single integer — the number of subsequences "QAQ" in the string.

## 说明/提示

In the first example there are $ 4 $ subsequences "QAQ": "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN".

## 样例 #1

### 输入

```
QAQAQYSYIOIWIN

```

### 输出

```
4

```

## 样例 #2

### 输入

```
QAQQQZZYNOIWIN

```

### 输出

```
3

```



---

---
title: "Die Roll"
layout: "post"
diff: 入门
pid: CF9A
tag: ['数学', '递归', '最大公约数 gcd']
---

# Die Roll

## 题目描述

Yakko, Wakko and Dot, world-famous animaniacs, decided to rest from acting in cartoons, and take a leave to travel a bit. Yakko dreamt to go to Pennsylvania, his Motherland and the Motherland of his ancestors. Wakko thought about Tasmania, its beaches, sun and sea. Dot chose Transylvania as the most mysterious and unpredictable place.

But to their great regret, the leave turned to be very short, so it will be enough to visit one of the three above named places. That's why Yakko, as the cleverest, came up with a truly genius idea: let each of the three roll an ordinary six-sided die, and the one with the highest amount of points will be the winner, and will take the other two to the place of his/her dreams.

Yakko thrown a die and got Y points, Wakko — W points. It was Dot's turn. But she didn't hurry. Dot wanted to know for sure what were her chances to visit Transylvania.

It is known that Yakko and Wakko are true gentlemen, that's why if they have the same amount of points with Dot, they will let Dot win.

## 输入格式

The only line of the input file contains two natural numbers Y and W — the results of Yakko's and Wakko's die rolls.

## 输出格式

Output the required probability in the form of irreducible fraction in format «A/B», where A — the numerator, and B — the denominator. If the required probability equals to zero, output «0/1». If the required probability equals to 1, output «1/1».

## 说明/提示

Dot will go to Transylvania, if she is lucky to roll 4, 5 or 6 points.

## 样例 #1

### 输入

```
4 2

```

### 输出

```
1/2

```



---

