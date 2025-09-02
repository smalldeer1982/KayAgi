---
title: "Ant Man"
layout: "post"
diff: 省选/NOI-
pid: CF704B
tag: []
---

# Ant Man

## 题目描述

Scott Lang is at war with Darren Cross. There are $ n $ chairs in a hall where they are, numbered with $ 1,2,...,n $ from left to right. The $ i $ -th chair is located at coordinate $ x_{i} $ . Scott is on chair number $ s $ and Cross is on chair number $ e $ . Scott can jump to all other chairs (not only neighboring chairs). He wants to start at his position (chair number $ s $ ), visit each chair exactly once and end up on chair number $ e $ with Cross.

As we all know, Scott can shrink or grow big (grow big only to his normal size), so at any moment of time he can be either small or large (normal). The thing is, he can only shrink or grow big while being on a chair (not in the air while jumping to another chair). Jumping takes time, but shrinking and growing big takes no time. Jumping from chair number $ i $ to chair number $ j $ takes $ |x_{i}-x_{j}| $ seconds. Also, jumping off a chair and landing on a chair takes extra amount of time.

If Scott wants to jump to a chair on his left, he can only be small, and if he wants to jump to a chair on his right he should be large.

Jumping off the $ i $ -th chair takes:

- $ c_{i} $ extra seconds if he's small.
- $ d_{i} $ extra seconds otherwise (he's large).

Also, landing on $ i $ -th chair takes:

- $ b_{i} $ extra seconds if he's small.
- $ a_{i} $ extra seconds otherwise (he's large).

In simpler words, jumping from $ i $ -th chair to $ j $ -th chair takes exactly:

- $ |x_{i}-x_{j}|+c_{i}+b_{j} $ seconds if $ j&lt;i $ .
- $ |x_{i}-x_{j}|+d_{i}+a_{j} $ seconds otherwise ( $ j&gt;i $ ).

Given values of $ x $ , $ a $ , $ b $ , $ c $ , $ d $ find the minimum time Scott can get to Cross, assuming he wants to visit each chair exactly once.

## 输入格式

The first line of the input contains three integers $ n,s $ and $ e $ ( $ 2 \le  n \le  5000,1 \le  s,e \le  n,s≠e $ ) — the total number of chairs, starting and ending positions of Scott.

The second line contains $ n $ integers $ x_{1},x_{2},...,x_{n} $ ( $ 1 \le  x_{1} < x_{2} < ... < x_{n} \le  10^{9} $ ).

The third line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1 \le  a_{1},a_{2},...,a_{n} \le  10^{9} $ ).

The fourth line contains $ n $ integers $ b_{1},b_{2},...,b_{n} $ ( $ 1 \le  b_{1},b_{2},...,b_{n} \le  10^{9} $ ).

The fifth line contains $ n $ integers $ c_{1},c_{2},...,c_{n} $ ( $ 1 \le  c_{1},c_{2},...,c_{n} \le  10^{9} $ ).

The sixth line contains $ n $ integers $ d_{1},d_{2},...,d_{n} $ ( $ 1 \le  d_{1},d_{2},...,d_{n} \le  10^{9} $ ).

## 输出格式

Print the minimum amount of time Scott needs to get to the Cross while visiting each chair exactly once.

## 说明/提示

In the sample testcase, an optimal solution would be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF704B/4c6f96e15c54bfd937ff89197525b5068744a884.png). Spent time would be $ 17+24+23+20+33+22=139 $ .

## 样例 #1

### 输入

```
7 4 3
8 11 12 16 17 18 20
17 16 20 2 20 5 13
17 8 8 16 12 15 13
12 4 16 4 15 7 6
8 14 2 11 17 12 8

```

### 输出

```
139

```

