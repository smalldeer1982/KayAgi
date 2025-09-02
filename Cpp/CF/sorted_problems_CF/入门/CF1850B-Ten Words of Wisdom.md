---
title: "Ten Words of Wisdom"
layout: "post"
diff: 入门
pid: CF1850B
tag: []
---

# Ten Words of Wisdom

## 题目描述

In the game show "Ten Words of Wisdom", there are $ n $ participants numbered from $ 1 $ to $ n $ , each of whom submits one response. The $ i $ -th response is $ a_i $ words long and has quality $ b_i $ . No two responses have the same quality, and at least one response has length at most $ 10 $ .

The winner of the show is the response which has the highest quality out of all responses that are not longer than $ 10 $ words. Which response is the winner?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 50 $ ) — the number of responses.

Then $ n $ lines follow, the $ i $ -th of which contains two integers $ a_i $ and $ b_i $ ( $ 1 \leq a_i, b_i \leq 50 $ ) — the number of words and the quality of the $ i $ -th response, respectively.

Additional constraints on the input: in each test case, at least one value of $ i $ satisfies $ a_i \leq 10 $ , and all values of $ b_i $ are distinct.

## 输出格式

For each test case, output a single line containing one integer $ x $ ( $ 1 \leq x \leq n $ ) — the winner of the show, according to the rules given in the statement.

It can be shown that, according to the constraints in the statement, exactly one winner exists for each test case.

## 说明/提示

In the first test case, the responses provided are as follows:

- Response 1: $ 7 $ words, quality $ 2 $
- Response 2: $ 12 $ words, quality $ 5 $
- Response 3: $ 9 $ words, quality $ 3 $
- Response 4: $ 9 $ words, quality $ 4 $
- Response 5: $ 10 $ words, quality $ 1 $

We can see that the responses with indices $ 1 $ , $ 3 $ , $ 4 $ , and $ 5 $ have lengths not exceeding $ 10 $ words. Out of these responses, the winner is the one with the highest quality.

Comparing the qualities, we find that:

- Response 1 has quality $ 2 $ .
- Response 3 has quality $ 3 $ .
- Response 4 has quality $ 4 $ .
- Response 5 has quality $ 1 $ .

Among these responses, Response 4 has the highest quality.

## 样例 #1

### 输入

```
3
5
7 2
12 5
9 3
9 4
10 1
3
1 2
3 4
5 6
1
1 43
```

### 输出

```
4
3
1
```

