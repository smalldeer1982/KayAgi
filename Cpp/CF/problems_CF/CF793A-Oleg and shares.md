---
title: "Oleg and shares"
layout: "post"
diff: 普及-
pid: CF793A
tag: []
---

# Oleg and shares

## 题目描述

Oleg the bank client checks share prices every day. There are $ n $ share prices he is interested in. Today he observed that each second exactly one of these prices decreases by $ k $ rubles (note that each second exactly one price changes, but at different seconds different prices can change). Prices can become negative. Oleg found this process interesting, and he asked Igor the financial analyst, what is the minimum time needed for all $ n $ prices to become equal, or it is impossible at all? Igor is busy right now, so he asked you to help Oleg. Can you answer this question?

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=10^{5},1<=k<=10^{9} $ ) — the number of share prices, and the amount of rubles some price decreases each second.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the initial prices.

## 输出格式

Print the only line containing the minimum number of seconds needed for prices to become equal, of «-1» if it is impossible.

## 说明/提示

Consider the first example.

Suppose the third price decreases in the first second and become equal $ 12 $ rubles, then the first price decreases and becomes equal $ 9 $ rubles, and in the third second the third price decreases again and becomes equal $ 9 $ rubles. In this case all prices become equal $ 9 $ rubles in $ 3 $ seconds.

There could be other possibilities, but this minimizes the time needed for all prices to become equal. Thus the answer is $ 3 $ .

In the second example we can notice that parity of first and second price is different and never changes within described process. Thus prices never can become equal.

In the third example following scenario can take place: firstly, the second price drops, then the third price, and then fourth price. It happens $ 999999999 $ times, and, since in one second only one price can drop, the whole process takes $ 999999999*3=2999999997 $ seconds. We can note that this is the minimum possible time.

## 样例 #1

### 输入

```
3 3
12 9 15

```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 2
10 9

```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 1
1 1000000000 1000000000 1000000000

```

### 输出

```
2999999997
```

