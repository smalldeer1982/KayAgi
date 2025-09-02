---
title: "Optimize!"
layout: "post"
diff: 省选/NOI-
pid: CF338E
tag: ['线段树']
---

# Optimize!

## 题目描述

Manao is solving a problem with the following statement:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF338E/5342825b0bbcbbc06536e5a019fb46969a4849f8.png)He came up with a solution that produces the correct answers but is too slow. You are given the pseudocode of his solution, where the function getAnswer calculates the answer to the problem:

```
getAnswer(a[1..n], b[1..len], h)
  answer = 0
  for i = 1 to n-len+1
    answer = answer + f(a[i..i+len-1], b, h, 1)
  return answer

f(s[1..len], b[1..len], h, index)
  if index = len+1 then
    return 1
  for i = 1 to len
    if s[index] + b[i] >= h
      mem = b[i]
      b[i] = 0
      res = f(s, b, h, index + 1)
      b[i] = mem
      if res > 0
        return 1
  return 0
```

Your task is to help Manao optimize his algorithm.

## 输入格式

The first line contains space-separated integers $ n $ , $ len $ and $ h $ ( $ 1<=len<=n<=150000; 1<=h<=10^{9} $ ). The second line contains $ len $ space-separated integers $ b_{1},b_{2},...,b_{len} $ ( $ 1<=b_{i}<=10^{9} $ ). The third line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print a single number — the answer to Manao's problem.

## 样例 #1

### 输入

```
5 2 10
5 3
1 8 5 5 7

```

### 输出

```
2

```

