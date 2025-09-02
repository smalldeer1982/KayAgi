---
title: "Nearest Beautiful Number (easy version)"
layout: "post"
diff: 普及+/提高
pid: CF1560F1
tag: []
---

# Nearest Beautiful Number (easy version)

## 题目描述

It is a simplified version of problem F2. The difference between them is the constraints (F1: $ k \le 2 $ , F2: $ k \le 10 $ ).

You are given an integer $ n $ . Find the minimum integer $ x $ such that $ x \ge n $ and the number $ x $ is $ k $ -beautiful.

A number is called $ k $ -beautiful if its decimal representation having no leading zeroes contains no more than $ k $ different digits. E.g. if $ k = 2 $ , the numbers $ 3434443 $ , $ 55550 $ , $ 777 $ and $ 21 $ are $ k $ -beautiful whereas the numbers $ 120 $ , $ 445435 $ and $ 998244353 $ are not.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case consists of one line containing two integers $ n $ and $ k $ ( $ 1 \le n \le 10^9 $ , $ 1 \le k \le 2 $ ).

## 输出格式

For each test case output on a separate line $ x $ — the minimum $ k $ -beautiful integer such that $ x \ge n $ .

## 样例 #1

### 输入

```
4
1 1
221 2
177890 2
998244353 1
```

### 输出

```
1
221
181111
999999999
```

