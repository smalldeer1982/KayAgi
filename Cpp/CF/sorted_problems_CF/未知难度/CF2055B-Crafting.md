---
title: "Crafting"
layout: "post"
diff: 难度0
pid: CF2055B
tag: []
---

# Crafting

## 题目描述

As you'd expect, Florida is home to many bizarre magical forces, and Florida Man seeks to tame them.There are $ n $ different types of magical materials, numbered from $ 1 $ to $ n $ . Initially, you have $ a_i $ units of material $ i $ for each $ i $ from $ 1 $ to $ n $ . You are allowed to perform the following operation:

- Select a material $ i $ (where $ 1\le i\le n $ ). Then, spend $ 1 $ unit of every other material $ j $ (in other words, $ j\neq i $ ) to gain $ 1 $ unit of material $ i $ . More formally, after selecting material $ i $ , update array $ a $ as follows: $ a_i := a_i + 1 $ , and $ a_j := a_j - 1 $ for all $ j $ where $ j\neq i $ and $ 1\le j\le n $ . Note that all $ a_j $ must remain non-negative, i.e. you cannot spend resources you do not have.

You are trying to craft an artifact using these materials. To successfully craft the artifact, you must have at least $ b_i $ units of material $ i $ for each $ i $ from $ 1 $ to $ n $ . Determine if it is possible to craft the artifact by performing the operation any number of times (including zero).

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2\le n\le 2\cdot 10^5 $ ) — the number of types of materials.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i\le 10^9 $ ) — the amount of each material $ i $ that you currently hold.

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 0 \le b_i\le 10^9 $ ) — the amount of each material $ i $ needed to produce the artifact.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single line containing either "YES" or "NO", representing whether or not the artifact can be crafted.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first test case, perform an operation on material $ 1 $ . After doing so, we will have exactly the required resources: $ 1 $ unit of material $ 1 $ , and $ 4 $ units each of materials $ 2 $ and $ 3 $ .

In the second test case, it can be shown that no matter how the operations are performed, it is impossible to craft the artifact.

In the third test case, we can perform the operation on material $ 1 $ twice. After these operations, we will have $ 3 $ units of material $ 1 $ and $ 8 $ units of material $ 2 $ , which is more than enough to craft the artifact.

## 样例 #1

### 输入

```
3
4
0 5 5 1
1 4 4 0
3
1 1 3
2 2 1
2
1 10
3 3
```

### 输出

```
YES
NO
YES
```

