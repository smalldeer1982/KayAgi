---
title: "Carrying Conundrum"
layout: "post"
diff: 普及/提高-
pid: CF1567C
tag: []
---

# Carrying Conundrum

## 题目描述

Alice has just learned addition. However, she hasn't learned the concept of "carrying" fully — instead of carrying to the next column, she carries to the column two columns to the left.

For example, the regular way to evaluate the sum $ 2039 + 2976 $ would be as shown:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/7f811803128f9de09a9d354d6ba38f6c979516bb.png)However, Alice evaluates it as shown:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/83982f3a368c4bf27357d999f4274a4bb752e11c.png)In particular, this is what she does:

- add $ 9 $ and $ 6 $ to make $ 15 $ , and carry the $ 1 $ to the column two columns to the left, i. e. to the column " $ 0 $ $ 9 $ ";
- add $ 3 $ and $ 7 $ to make $ 10 $ and carry the $ 1 $ to the column two columns to the left, i. e. to the column " $ 2 $ $ 2 $ ";
- add $ 1 $ , $ 0 $ , and $ 9 $ to make $ 10 $ and carry the $ 1 $ to the column two columns to the left, i. e. to the column above the plus sign;
- add $ 1 $ , $ 2 $ and $ 2 $ to make $ 5 $ ;
- add $ 1 $ to make $ 1 $ .

 Thus, she ends up with the incorrect result of $ 15005 $ .Alice comes up to Bob and says that she has added two numbers to get a result of $ n $ . However, Bob knows that Alice adds in her own way. Help Bob find the number of ordered pairs of positive integers such that when Alice adds them, she will get a result of $ n $ . Note that pairs $ (a, b) $ and $ (b, a) $ are considered different if $ a \ne b $ .

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. The description of the test cases follows.

The only line of each test case contains an integer $ n $ ( $ 2 \leq n \leq 10^9 $ ) — the number Alice shows Bob.

## 输出格式

For each test case, output one integer — the number of ordered pairs of positive integers such that when Alice adds them, she will get a result of $ n $ .

## 说明/提示

In the first test case, when Alice evaluates any of the sums $ 1 + 9 $ , $ 2 + 8 $ , $ 3 + 7 $ , $ 4 + 6 $ , $ 5 + 5 $ , $ 6 + 4 $ , $ 7 + 3 $ , $ 8 + 2 $ , or $ 9 + 1 $ , she will get a result of $ 100 $ . The picture below shows how Alice evaluates $ 6 + 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1567C/b16910e4b25eab78326b49caad3574b10b90fef3.png)

## 样例 #1

### 输入

```
5
100
12
8
2021
10000
```

### 输出

```
9
4
7
44
99
```

