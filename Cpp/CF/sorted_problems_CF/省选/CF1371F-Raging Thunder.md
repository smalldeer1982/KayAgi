---
title: "Raging Thunder"
layout: "post"
diff: 省选/NOI-
pid: CF1371F
tag: []
---

# Raging Thunder

## 题目描述

You are a warrior fighting against the machine god Thor.

Thor challenge you to solve the following problem:

There are $ n $ conveyors arranged in a line numbered with integers from $ 1 $ to $ n $ from left to right. Each conveyor has a symbol "&lt;" or "&gt;". The initial state of the conveyor $ i $ is equal to the $ i $ -th character of the string $ s $ . There are $ n+1 $ holes numbered with integers from $ 0 $ to $ n $ . The hole $ 0 $ is on the left side of the conveyor $ 1 $ , and for all $ i \geq 1 $ the hole $ i $ is on the right side of the conveyor $ i $ .

When a ball is on the conveyor $ i $ , the ball moves by the next rules:

If the symbol "&lt;" is on the conveyor $ i $ , then:

- If $ i=1 $ , the ball falls into the hole $ 0 $ .
- If the symbol "&lt;" is on the conveyor $ i-1 $ , the ball moves to the conveyor $ i-1 $ .
- If the symbol "&gt;" is on the conveyor $ i-1 $ , the ball falls into the hole $ i-1 $ .

If the symbol "&gt;" is on the conveyor $ i $ , then:

- If $ i=n $ , the ball falls into the hole $ n $ .
- If the symbol "&gt;" is on the conveyor $ i+1 $ , the ball moves to the conveyor $ i+1 $ .
- If the symbol "&lt;" is on the conveyor $ i+1 $ , the ball falls into the hole $ i $ .

You should answer next $ q $ queries, each query is defined by the pair of integers $ l, r $ ( $ 1 \leq l \leq r \leq n $ ):

- First, for all conveyors $ l,l+1,...,r $ , the symbol "&lt;" changes to "&gt;" and vice versa. These changes remain for the next queries.
- After that, put one ball on each conveyor $ l,l+1,...,r $ . Then, each ball falls into some hole. Find the maximum number of balls in one hole. After the query all balls disappear and don't considered in the next queries.

## 输入格式

The first line contains two integers $ n $ , $ q $ ( $ 1 \le n       \le 5 \times 10^5 , 1 \le q \le 10^5 $ ).

The second line contains a string $ s $ of length $ n $ . It consists of characters "&lt;" and "&gt;".

Next $ q $ lines contain the descriptions of the queries, $ i $ -th of them contains two integers $ l $ , $ r $ $ (1       \le l \le r \le n) $ , describing the $ i $ -th query.

## 输出格式

Print $ q $ lines, in the $ i $ -th of them print the answer to the $ i $ -th query.

## 说明/提示

- In the first query, the conveyors change to "&gt;&gt;&lt;&lt;&lt;". After that, put a ball on each conveyor $ \{2,3,4\} $ . All three balls fall into the hole $ 2 $ . So the answer is $ 3 $ .
- In the second query, the conveyors change to "&gt;&gt;&gt;&gt;&gt;". After that, put a ball on each conveyor $ \{3,4,5\} $ . All three balls fall into the hole $ 5 $ . So the answer is $ 3 $ .
- In the third query, the conveyors change to "&lt;&lt;&lt;&lt;&lt;". After that, put a ball on each conveyor $ \{1,2,3,4,5\} $ . All five balls fall into the hole $ 0 $ . So the answer is $ 5 $ .
- In the fourth query, the conveyors change to "&gt;&gt;&gt;&lt;&lt;". After that, put a ball on each conveyor $ \{1,2,3\} $ . All three balls fall into the hole $ 3 $ . So the answer is $ 3 $ .
- In the fifth query, the conveyors change to "&gt;&lt;&lt;&gt;&lt;". After that, put a ball on each conveyor $ \{2,3,4\} $ . Two balls fall into the hole $ 1 $ , and one ball falls into the hole $ 4 $ . So, the answer is $ 2 $ .
- In the sixth query, the conveyors change to "&lt;&gt;&gt;&lt;&gt;". After that, put a ball on each conveyor $ \{1,2,3,4,5\} $ . Three balls fall into the hole $ 3 $ , one ball falls into the hole $ 0 $ and one ball falls into the hole $ 5 $ . So, the answer is $ 3 $ .

## 样例 #1

### 输入

```
5 6
><>><
2 4
3 5
1 5
1 3
2 4
1 5
```

### 输出

```
3
3
5
3
2
3
```

