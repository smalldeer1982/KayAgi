---
title: "Epic Game"
layout: "post"
diff: 入门
pid: CF119A
tag: ['模拟', '最大公约数 gcd']
---

# Epic Game

## 题目描述

Simon和Antisimon在玩石子游戏。

共有n颗石子，Simon先拿。

Simon能拿当前n和a的最大公约数，Antisimon能拿当前n和b的最大公约数。

当有一个人不能拿时（n=0）那个人就输了。

求谁赢了。

## 输入格式

一行，a，b，n（1<=a,b,n<=100）

## 输出格式

一行，如果Simon赢了，输出0；Antisimon赢了，输出1.

## 说明/提示

gcd(0,x)=gcd(x,0)=x;

对于样例1：

Simon拿gcd(3,9)=3颗

Antisimon拿gcd(5,6)=1颗

Simon拿gcd(3,5)=1颗

Antisimon拿gcd(5,4)=1颗

Simon拿gcd(3,3)=3颗

Antisimon输了

感谢@引领天下 提供的翻译

## 样例 #1

### 输入

```
3 5 9

```

### 输出

```
0
```

## 样例 #2

### 输入

```
1 1 100

```

### 输出

```
1
```



---

---
title: "GCD Arrays"
layout: "post"
diff: 入门
pid: CF1629B
tag: ['贪心', '最大公约数 gcd']
---

# GCD Arrays

## 题目描述

考虑一下数组 $a$，范围是 $[l,r]$。例如，$[3,7]$，数组 $a$ 就是 $[3,4,5,6,7]$。   
给出 $l,r,k$，询问 $gcd(a)$ 是否能在最多 $k$ 次如下 操作以后比 1 大？
* 在 $a$ 数组中选择两个数。
* 删除这两个数。
* 将这两个数的乘积放回数组 $a$。    

其中，$gcd(b)$ 意思就是 $b$ 数组中数字的[最大公因数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fromtitle=%E6%9C%80%E5%A4%A7%E5%85%AC%E5%9B%A0%E6%95%B0&fromid=869104&fr=aladdin)

## 输入格式

第一行包含一个整数 $t (1 \le t \le 10^5)$，表示数据组数。    

接下来 $t$ 行，每行三个正整数 $l,r,k (1 \le l,r \le 10^9;0 \le k \le r - l)$，含义如题。

## 输出格式

对于每组数据，如果能在 1 到 $k$ 步求出日题意的最大公因数，那么输出
`YES`，否则输出
`NO`。

## 说明/提示

对于样例输入的第 1 组测试数据，$a = [1]$，所以输出
`NO`，因为 1 是数组 $a$ 的唯一元素。   
对于样例输入的第 2 组数据，数组 $a = [3,4,5]$，现在我们有 1 次操作机会。不难发现，无论如何操作，结果只会有 3 个：$[3,20],[4,15],[5,12]$，他们的最大公因数都是 1，没有其他的数，所以输出
`NO`。    

对于样例输入的第 3 组测试数据，$a = [13]$，所以输出
`YES`，因为唯一的元素就是 13，一个质数。

对于样例输入的第 4 组数据，$a = [4]$，输出
`YES`，因为 4 是唯一的元素。

## 样例 #1

### 输入

```
9
1 1 0
3 5 1
13 13 0
4 4 0
3 7 4
4 10 3
2 4 0
1 7 3
1 5 3
```

### 输出

```
NO
NO
YES
YES
YES
YES
NO
NO
YES
```



---

---
title: "Ksusha and Array"
layout: "post"
diff: 入门
pid: CF299A
tag: ['最大公约数 gcd']
---

# Ksusha and Array

## 题目描述

输入 $N$ 个数字，你的任务是**在这些数字中**找到一个能够整除所有这些数字的数。

## 输入格式

第一行输入 $N$（$1 \le N \le {10}^5$），第二行输入 $N$ 个数字 $a_i$（$1 \le a_i \le {10}^9$）。

## 输出格式

输出那个数字，若没有则输出 $-1$，若有多个，可任意输出其中一个。

## 样例 #1

### 输入

```
3
2 2 4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
2 1 3 1 6

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3
2 3 5

```

### 输出

```
-1

```



---

---
title: "I'm bored with life"
layout: "post"
diff: 入门
pid: CF822A
tag: ['数学', '最大公约数 gcd']
---

# I'm bored with life

## 题目描述

Holidays have finished. Thanks to the help of the hacker Leha, Noora managed to enter the university of her dreams which is located in a town Pavlopolis. It's well known that universities provide students with dormitory for the period of university studies. Consequently Noora had to leave Vičkopolis and move to Pavlopolis. Thus Leha was left completely alone in a quiet town Vičkopolis. He almost even fell into a depression from boredom!

Leha came up with a task for himself to relax a little. He chooses two integers $ A $ and $ B $ and then calculates the greatest common divisor of integers " $ A $ factorial" and " $ B $ factorial". Formally the hacker wants to find out GCD $ (A!,B!) $ . It's well known that the factorial of an integer $ x $ is a product of all positive integers less than or equal to $ x $ . Thus $ x!=1·2·3·...·(x-1)·x $ . For example $ 4!=1·2·3·4=24 $ . Recall that GCD $ (x,y) $ is the largest positive integer $ q $ that divides (without a remainder) both $ x $ and $ y $ .

Leha has learned how to solve this task very effective. You are able to cope with it not worse, aren't you?

## 输入格式

The first and single line contains two integers $ A $ and $ B $ $ (1<=A,B<=10^{9},min(A,B)<=12) $ .

## 输出格式

Print a single integer denoting the greatest common divisor of integers $ A! $ and $ B! $ .

## 说明/提示

Consider the sample.

 $ 4!=1·2·3·4=24 $ . $ 3!=1·2·3=6 $ . The greatest common divisor of integers $ 24 $ and $ 6 $ is exactly $ 6 $ .

## 样例 #1

### 输入

```
4 3

```

### 输出

```
6

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

