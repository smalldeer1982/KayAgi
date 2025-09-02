---
title: "Optimal Number Permutation"
layout: "post"
diff: 提高+/省选-
pid: CF622D
tag: []
---

# Optimal Number Permutation

## 题目描述

You have array $ a $ that contains all integers from $ 1 $ to $ n $ twice. You can arbitrary permute any numbers in $ a $ .

Let number $ i $ be in positions $ x_{i},y_{i} $ ( $ x_{i}&lt;y_{i} $ ) in the permuted array $ a $ . Let's define the value $ d_{i}=y_{i}-x_{i} $ — the distance between the positions of the number $ i $ . Permute the numbers in array $ a $ to minimize the value of the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF622D/22b9f04219f1da8748ed3cb58a6363dd566698ed.png).

## 输入格式

The only line contains integer $ n $ ( $ 1<=n<=5·10^{5} $ ).

## 输出格式

Print $ 2n $ integers — the permuted array $ a $ that minimizes the value of the sum $ s $ .

## 样例 #1

### 输入

```
2

```

### 输出

```
1 1 2 2

```

## 样例 #2

### 输入

```
1

```

### 输出

```
1 1

```

