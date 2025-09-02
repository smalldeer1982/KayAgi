---
title: "Division?"
layout: "post"
diff: 入门
pid: CF1669A
tag: []
---

# Division?

## 题目描述

Codeforces separates its users into $ 4 $ divisions by their rating:

- For Division 1: $ 1900 \leq \mathrm{rating} $
- For Division 2: $ 1600 \leq \mathrm{rating} \leq 1899 $
- For Division 3: $ 1400 \leq \mathrm{rating} \leq 1599 $
- For Division 4: $ \mathrm{rating} \leq 1399 $

Given a $ \mathrm{rating} $ , print in which division the $ \mathrm{rating} $ belongs.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of testcases.

The description of each test consists of one line containing one integer $ \mathrm{rating} $ ( $ -5000 \leq \mathrm{rating} \leq 5000 $ ).

## 输出格式

For each test case, output a single line containing the correct division in the format "Division X", where $ X $ is an integer between $ 1 $ and $ 4 $ representing the division for the corresponding rating.

## 说明/提示

For test cases $ 1-4 $ , the corresponding ratings are $ -789 $ , $ 1299 $ , $ 1300 $ , $ 1399 $ , so all of them are in division $ 4 $ .

For the fifth test case, the corresponding rating is $ 1400 $ , so it is in division $ 3 $ .

For the sixth test case, the corresponding rating is $ 1679 $ , so it is in division $ 2 $ .

For the seventh test case, the corresponding rating is $ 2300 $ , so it is in division $ 1 $ .

## 样例 #1

### 输入

```
7
-789
1299
1300
1399
1400
1679
2300
```

### 输出

```
Division 4
Division 4
Division 4
Division 4
Division 3
Division 2
Division 1
```

