---
title: "SUBS - String it out"
layout: "post"
diff: 难度0
pid: SP665
tag: []
---

# SUBS - String it out

## 题目描述

Let **A** and **B** be two strings made up of alphabets such that **A = A $ _{[1-n]} $ , B = B $ _{[1-m]} $** . We say **B** is a subsequence of **A** if there exists a sequence of indices **i $ _{1} $ < i $ _{2} $ <.. _of **A** such that **A\[i $ _{k} $ \] = B\[k\]**._**

 Given **B\[1-m\]**, a string of characters from some alphabets, **B^i** is defined as string with the characters of **B** each repeating **i** times. For example, **(abbacc)^3 = aaabbbbbbaaacccccc**. Also, **B^0** is the empty string.

 Given strings **X**, **Y** made up of characters from **'a' - 'z'** find the maximum value of **M** such that **X^M** is a subsequence of **Y**.

## 输入格式

- The first line of the input contains a positive integer **t <= 20**, denoting the no. of test cases.
- The following **2t** lines contain the value of **X** and **Y** for the cases.
- The description of the test cases follow one after the other. 
  - Line **2k** contains the value of **X** for case **k**; **(1 <= k <= t)**
  - Line **2k+1** contains the value of **Y** for case **k**; **(1 <= k <= t)**.
  - The no. of characters in **X** , **Y** will be **<= 500010**.

## 输出格式

 The output must contain **t** lines, each line corresponding to a test case. The value on the **k $ ^{th} $**  line should be the value of **M** for the **k $ ^{th} $**  pair of **X** and **Y**.

## 样例 #1

### 输入

```
\n3
\nabc
\naabbcc
\nabc
\nbbccc
\nabcdef
\nabc
```

### 输出

```
\n2
\n0
\n0
```

