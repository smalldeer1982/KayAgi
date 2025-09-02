---
title: "Conditional Mix"
layout: "post"
diff: 省选/NOI-
pid: CF1740F
tag: []
---

# Conditional Mix

## 题目描述

Pak Chanek is given an array $ a $ of $ n $ integers. For each $ i $ ( $ 1 \leq i \leq n $ ), Pak Chanek will write the one-element set $ \{a_i\} $ on a whiteboard.

After that, in one operation, Pak Chanek may do the following:

1. Choose two different sets $ S $ and $ T $ on the whiteboard such that $ S \cap T = \varnothing $ ( $ S $ and $ T $ do not have any common elements).
2. Erase $ S $ and $ T $ from the whiteboard and write $ S \cup T $ (the union of $ S $ and $ T $ ) onto the whiteboard.

After performing zero or more operations, Pak Chanek will construct a multiset $ M $ containing the sizes of all sets written on the whiteboard. In other words, each element in $ M $ corresponds to the size of a set after the operations.

How many distinct $ ^\dagger $ multisets $ M $ can be created by this process? Since the answer may be large, output it modulo $ 998\,244\,353 $ .

 $ ^\dagger $ Multisets $ B $ and $ C $ are different if and only if there exists a value $ k $ such that the number of elements with value $ k $ in $ B $ is different than the number of elements with value $ k $ in $ C $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2000 $ ).

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq n $ ).

## 输出格式

Output the number of distinct multisets $ M $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, the possible multisets $ M $ are $ \{1,1,1,1,1,1\} $ , $ \{1,1,1,1,2\} $ , $ \{1,1,1,3\} $ , $ \{1,1,2,2\} $ , $ \{1,1,4\} $ , $ \{1,2,3\} $ , and $ \{2,2,2\} $ .

As an example, let's consider a possible sequence of operations.

1. In the beginning, the sets are $ \{1\} $ , $ \{1\} $ , $ \{2\} $ , $ \{1\} $ , $ \{4\} $ , and $ \{3\} $ .
2. Do an operation on sets $ \{1\} $ and $ \{3\} $ . Now, the sets are $ \{1\} $ , $ \{1\} $ , $ \{2\} $ , $ \{4\} $ , and $ \{1,3\} $ .
3. Do an operation on sets $ \{2\} $ and $ \{4\} $ . Now, the sets are $ \{1\} $ , $ \{1\} $ , $ \{1,3\} $ , and $ \{2,4\} $ .
4. Do an operation on sets $ \{1,3\} $ and $ \{2,4\} $ . Now, the sets are $ \{1\} $ , $ \{1\} $ , and $ \{1,2,3,4\} $ .
5. The multiset $ M $ that is constructed is $ \{1,1,4\} $ .

## 样例 #1

### 输入

```
6
1 1 2 1 4 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
7
3 5 4 3 7 4 5
```

### 输出

```
11
```

