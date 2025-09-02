---
title: "JGTLE - Jalil Got TLE"
layout: "post"
diff: 普及/提高-
pid: SP34011
tag: ['数学', '枚举']
---

# JGTLE - Jalil Got TLE

## 题目描述

Ananta Jalil 是一个多才多艺的人。他可以完成任何对别人来说不可能的任务。最近，他学会了编程基础。在一个问题中，他提交了以下解决方案：

```cpp
#include <stdio.h>

int main()
{
   int t;
   scanf("%d", &t);
   for(int tc = 1; tc <= t; ++tc) {
       int a, b, c;
       scanf("%d %d %d", &a, &b, &c);
       long long result = 0;
       for(int i = 1; i <= a; ++i) {
           for(int j = 1; j <= b; ++j) {
               for(int k = 1; k <= c; ++k) {
                   result += j * k;
               }
           }
       }
       printf("Case %d: %lld\n", tc, result);
   }
   return 0;
}
```

但由于他是编程新手，他得到了 TLE（Time Limit Exceeded，超出时间限制）。因此他的解决方案效率不高。所以，你需要为 Jalil 编写一个优化的解决方案，以获得相同的输出。

## 输入格式

输入的第一行将包含一个正整数 $T$，表示测试用例的数量。

在每个测试用例中，将有 $3$ 个正整数 $a$、$b$ 和 $c$。

## 输出格式

对于每个测试用例，打印与上述程序相同的输出。


---

Translated by User 735713.

## 样例 #1

### 输入

```
3
1 4 3
3 4 2
143 342 777
```

### 输出

```
Case 1: 60
Case 2: 90
Case 3: 2535110464887
```

