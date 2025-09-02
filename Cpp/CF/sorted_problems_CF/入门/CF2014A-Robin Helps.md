---
title: "Robin Helps"
layout: "post"
diff: 入门
pid: CF2014A
tag: ['模拟']
---

# Robin Helps

## 题目描述

There is a little bit of the outlaw in everyone, and a little bit of the hero too.



The heroic outlaw Robin Hood is famous for taking from the rich and giving to the poor.

Robin encounters $ n $ people starting from the $ 1 $ -st and ending with the $ n $ -th. The $ i $ -th person has $ a_i $ gold. If $ a_i \ge k $ , Robin will take all $ a_i $ gold, and if $ a_i=0 $ , Robin will give $ 1 $ gold if he has any. Robin starts with $ 0 $ gold.

Find out how many people Robin gives gold to.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1\leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ , $ k $ ( $ 1 \le n \le 50, 1 \le k \le 100 $ ) — the number of people and the threshold at which Robin Hood takes the gold.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 100 $ ) — the gold of each person.

## 输出格式

For each test case, output a single integer, the number of people that will get gold from Robin Hood.

## 说明/提示

In the first test case, Robin takes $ 2 $ gold from the first person and gives a gold to the second person.

In the second test case, Robin takes $ 3 $ gold and gives $ 1 $ gold to each of the next $ 2 $ people.

In the third test case, Robin takes $ 3 $ gold and so only gives gold to $ 3 $ other people.

## 样例 #1

### 输入

```
4
2 2
2 0
3 2
3 0 0
6 2
0 3 0 0 0 0
2 5
5 4
```

### 输出

```
1
2
3
0
```

