---
title: "Final Countdown"
layout: "post"
diff: 普及/提高-
pid: CF1932E
tag: ['数学', '高精度']
---

# Final Countdown

## 题目描述

You are in a nuclear laboratory that is about to explode and destroy the Earth. You must save the Earth before the final countdown reaches zero.

The countdown consists of $ n $ ( $ 1 \le n \le 4 \cdot 10^5 $ ) mechanical indicators, each showing one decimal digit. You noticed that when the countdown changes its state from $ x $ to $ x-1 $ , it doesn't happen in one move. Instead, each change of a single digit takes one second.

So, for example, if the countdown shows 42, then it will change to 41 in one second, because only one digit is changed, but if the countdown shows 2300, then it will change to 2299 in three seconds, because the three last digits are changed.

Find out how much time is left before the countdown reaches zero.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then the descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 4\cdot 10^5 $ ).

The second line contains a string of $ n $ digits, the current state of the countdown. It is guaranteed that at least one digit is not zero.

The sum of $ n $ for all tests does not exceed $ 4\cdot 10^5 $ .

## 输出格式

For each test case, print a single integer without leading zeroes, the number of seconds left before the countdown reaches zero. Note that this number may be huge.

## 说明/提示

In the first example, there are four changes that take 2 seconds: 40 to 39, 30 to 29, 20 to 19, and 10 to 09, other changes take 1 second each. So the total time is $ 2\cdot 4 + 1\cdot(42-4) = 46 $ .

## 样例 #1

### 输入

```
5
2
42
5
12345
2
99
4
0005
27
456480697259671309012631002
```

### 输出

```
46
13715
108
5
507200774732968121125145546
```



---

---
title: "Petya and His Friends"
layout: "post"
diff: 普及/提高-
pid: CF66D
tag: ['高精度', '数论']
---

# Petya and His Friends

## 题目描述

Little Petya has a birthday soon. Due this wonderful event, Petya's friends decided to give him sweets. The total number of Petya's friends equals to $ n $ .

Let us remind you the definition of the greatest common divisor: $ GCD(a_{1},...,a_{k})=d $ , where $ d $ represents such a maximal positive number that each $ a_{i} $ ( $ 1<=i<=k $ ) is evenly divisible by $ d $ . At that, we assume that all $ a_{i} $ 's are greater than zero.

Knowing that Petya is keen on programming, his friends has agreed beforehand that the $ 1 $ -st friend gives $ a_{1} $ sweets, the $ 2 $ -nd one gives $ a_{2} $ sweets, ..., the $ n $ -th one gives $ a_{n} $ sweets. At the same time, for any $ i $ and $ j $ ( $ 1<=i,j<=n $ ) they want the $ GCD(a_{i},a_{j}) $ not to be equal to $ 1 $ . However, they also want the following condition to be satisfied: $ GCD(a_{1},a_{2},...,a_{n})=1 $ . One more: all the $ a_{i} $ should be distinct.

Help the friends to choose the suitable numbers $ a_{1},...,a_{n} $ .

## 输入格式

The first line contains an integer $ n $ ( $ 2<=n<=50 $ ).

## 输出格式

If there is no answer, print "-1" without quotes. Otherwise print a set of $ n $ distinct positive numbers $ a_{1},a_{2},...,a_{n} $ . Each line must contain one number. Each number must consist of not more than $ 100 $ digits, and must not contain any leading zeros. If there are several solutions to that problem, print any of them.

Do not forget, please, that all of the following conditions must be true:

- For every $ i $ and $ j $ ( $ 1<=i,j<=n $ ): $ GCD(a_{i},a_{j})≠1 $
- $ GCD(a_{1},a_{2},...,a_{n})=1 $
- For every $ i $ and $ j $ ( $ 1<=i,j<=n,i≠j $ ): $ a_{i}≠a_{j} $

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cout (also you may use %I64d).

## 样例 #1

### 输入

```
3

```

### 输出

```
99
55
11115

```

## 样例 #2

### 输入

```
4

```

### 输出

```
385
360
792
8360

```



---

---
title: "Position in Fraction"
layout: "post"
diff: 普及/提高-
pid: CF900B
tag: ['模拟', '字符串', '高精度']
---

# Position in Fraction

## 题目描述

给你三个整数 $a,b,c$，问 $\dfrac{a}{b}$ 的小数部分第几位是 $c$，如果无法找到，请输出 `-1`。

## 输入格式

共一行，三个整数 $a,b,c$。

## 输出格式

共一行，输出一个整数，表示 $c$ 的位置或 `-1`。

## 说明/提示

对于 $100\%$ 的数据：$1\le a<b\le 10^5,0\le c\le 9$。

## 样例 #1

### 输入

```
1 2 0

```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3 7

```

### 输出

```
-1
```



---

