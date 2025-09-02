---
title: "Interesting Array"
layout: "post"
diff: 提高+/省选-
pid: CF482B
tag: ['线段树', '进制', '构造']
---

# Interesting Array

## 题目描述

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 输入格式

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 输出格式

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 样例 #1

### 输入

```
3 1
1 3 3

```

### 输出

```
YES
3 3 3

```

## 样例 #2

### 输入

```
3 2
1 3 3
1 3 2

```

### 输出

```
NO

```

