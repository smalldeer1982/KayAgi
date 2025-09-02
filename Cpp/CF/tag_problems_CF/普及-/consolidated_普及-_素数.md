---
title: "Simple Repetition"
layout: "post"
diff: 普及-
pid: CF2093C
tag: ['素数判断,质数,筛法']
---

# Simple Repetition

## 题目描述

Pasha 喜欢质数 $ ^{\text{∗}} $ ！有一次他想找一个新的质数生成的方法，于是他在网上搜到了这样的数字生成方法：

- 选择一个没有前导零的正整数 $x$ 和一个正整数 $k$，把 $x$ 连写 $k$ 次得到新的正整数 $y$。

例如当 $x=52,\ k=3$ 时，$y=525252$，$x=6,\ k=7$ 时，$y=6666666$。

Pasha 想让得到的数是质数，但是他不知道怎么判断这种方法生成的是不是质数。请你写一个程序来判断 $y$ 是否是质数。

 $ ^{\text{∗}} $ 质数，也叫素数，指的是那些含有恰好 $2$ 个不同正约数的正整数。例如 $13$ 是一个质数，因为这个数只有 $2$ 个不同正约数 $1$ 和 $13$。$1$ 则不是质数，因为 $1$ 只有 $1$ 个不同正约数，那就是 $1$。

## 输入格式

**输入包含多组数据**。输入的开头是一个正整数 $t$（$1 \le t \le 100$），代表测试数据总数。以下有 $t$ 组测试数据，每组测试数据格式如下：

输入仅有一行，两个没有前导零的正整数 $x$ 和 $k$（$1 \le x \le {10}^9,\ 1 \le k \le 7$）。

## 输出格式

对于每组测试数据，如果把 $x$ 连写 $k$ 次得到的数是质数，输出一行一个字符串 `YES`，否则输出一行一个字符串 `NO`。

输出并不区分大小写，也就是说，`Yes`、`No`、`yEs` 和 `nO` 等输出都将被判为正确。

## 样例 #1

### 输入

```
4
52 3
6 7
7 1
1 7
```

### 输出

```
NO
NO
YES
NO
```



---

---
title: "Coins"
layout: "post"
diff: 普及-
pid: CF58B
tag: ['素数判断,质数,筛法']
---

# Coins

## 题目描述

In Berland a money reform is being prepared. New coins are being introduced. After long economic calculations was decided that the most expensive coin should possess the denomination of exactly $ n $ Berland dollars. Also the following restriction has been introduced for comfort: the denomination of each coin should be divisible by the denomination of any cheaper coin. It is known that among all the possible variants the variant with the largest number of new coins will be chosen. Find this variant. Print in the order of decreasing of the coins' denominations.

## 输入格式

The first and only line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ) which represents the denomination of the most expensive coin.

## 输出格式

Print the denominations of all the coins in the order of decreasing. The number of coins must be the largest possible (with the given denomination $ n $ of the most expensive coin). Also, the denomination of every coin must be divisible by the denomination of any cheaper coin. Naturally, the denominations of all the coins should be different. If there are several solutins to that problem, print any of them.

## 样例 #1

### 输入

```
10

```

### 输出

```
10 5 1

```

## 样例 #2

### 输入

```
4

```

### 输出

```
4 2 1

```

## 样例 #3

### 输入

```
3

```

### 输出

```
3 1

```



---

---
title: "Bear and Prime 100"
layout: "post"
diff: 普及-
pid: CF679A
tag: ['交互题', '素数判断,质数,筛法']
---

# Bear and Prime 100

## 题目描述

This is an interactive problem. In the output section below you will see the information about flushing the output.

Bear Limak thinks of some hidden number — an integer from interval $ [2,100] $ . Your task is to say if the hidden number is prime or composite.

Integer $ x>1 $ is called prime if it has exactly two distinct divisors, $ 1 $ and $ x $ . If integer $ x>1 $ is not prime, it's called composite.

You can ask up to $ 20 $ queries about divisors of the hidden number. In each query you should print an integer from interval $ [2,100] $ . The system will answer "yes" if your integer is a divisor of the hidden number. Otherwise, the answer will be "no".

For example, if the hidden number is $ 14 $ then the system will answer "yes" only if you print $ 2 $ , $ 7 $ or $ 14 $ .

When you are done asking queries, print "prime" or "composite" and terminate your program.

You will get the Wrong Answer verdict if you ask more than $ 20 $ queries, or if you print an integer not from the range $ [2,100] $ . Also, you will get the Wrong Answer verdict if the printed answer isn't correct.

You will get the Idleness Limit Exceeded verdict if you don't print anything (but you should) or if you forget about flushing the output (more info below).

## 输入格式

After each query you should read one string from the input. It will be "yes" if the printed integer is a divisor of the hidden number, and "no" otherwise.

## 输出格式

Up to $ 20 $ times you can ask a query — print an integer from interval $ [2,100] $ in one line. You have to both print the end-of-line character and flush the output. After flushing you should read a response from the input.

In any moment you can print the answer "prime" or "composite" (without the quotes). After that, flush the output and terminate your program.

To flush you can use (just after printing an integer and end-of-line):

- fflush(stdout) in C++;
- System.out.flush() in Java;
- stdout.flush() in Python;
- flush(output) in Pascal;
- See the documentation for other languages.

Hacking. To hack someone, as the input you should print the hidden number — one integer from the interval $ [2,100] $ . Of course, his/her solution won't be able to read the hidden number from the input.

## 说明/提示

The hidden number in the first query is $ 30 $ . In a table below you can see a better form of the provided example of the communication process.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/b5d048578748c4adde3d49c36a749660a61701b4.png)

The hidden number is divisible by both $ 2 $ and $ 5 $ . Thus, it must be composite. Note that it isn't necessary to know the exact value of the hidden number. In this test, the hidden number is $ 30 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/f54f8d5adb5e9403a147185e0d841ee7fbfd7d7b.png)

 $ 59 $ is a divisor of the hidden number. In the interval $ [2,100] $ there is only one number with this divisor. The hidden number must be $ 59 $ , which is prime. Note that the answer is known even after the second query and you could print it then and terminate. Though, it isn't forbidden to ask unnecessary queries (unless you exceed the limit of $ 20 $ queries).

## 样例 #1

### 输入

```
yes
no
yes

```

### 输出

```
2
80
5
composite

```

## 样例 #2

### 输入

```
no
yes
no
no
no

```

### 输出

```
58
59
78
78
2
prime

```



---

---
title: "Fake NP"
layout: "post"
diff: 普及-
pid: CF805A
tag: ['素数判断,质数,筛法']
---

# Fake NP

## 题目描述

Tavak and Seyyed are good friends. Seyyed is very funny and he told Tavak to solve the following problem instead of longest-path.

You are given $ l $ and $ r $ . For all integers from $ l $ to $ r $ , inclusive, we wrote down all of their integer divisors except $ 1 $ . Find the integer that we wrote down the maximum number of times.

Solve the problem to show that it's not a NP problem.

## 输入格式

The first line contains two integers $ l $ and $ r $ ( $ 2<=l<=r<=10^{9} $ ).

## 输出格式

Print single integer, the integer that appears maximum number of times in the divisors.

If there are multiple answers, print any of them.

## 说明/提示

Definition of a divisor: <https://www.mathsisfun.com/definitions/divisor-of-an-integer-.html>

The first example: from $ 19 $ to $ 29 $ these numbers are divisible by $ 2 $ : $ {20,22,24,26,28} $ .

The second example: from $ 3 $ to $ 6 $ these numbers are divisible by $ 3 $ : $ {3,6} $ .

## 样例 #1

### 输入

```
19 29

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 6

```

### 输出

```
3

```



---

