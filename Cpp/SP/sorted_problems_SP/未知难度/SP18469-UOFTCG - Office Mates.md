---
title: "UOFTCG - Office Mates"
layout: "post"
diff: 难度0
pid: SP18469
tag: []
---

# UOFTCG - Office Mates

## 题目描述

Dr. Baws has an interesting problem. His $ N $ graduate students, while friendly with some select people, are generally not friendly with each other. No graduate student is willing to sit beside a person they aren't friends with.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP18469/b9e749d22fe4020301e2ab4c1e8fb50d23c75e41.png)

The desks are up against the wall, in a single line, so it's possible that Dr. Baws will have to leave some desks empty. He does know which students are friends, and fortunately the list is not so long: it turns out that for any subset of $ K $ graduate students, there are at most $ K-1 $ pairs of friends. Dr. Baws would like you to minimize the total number of desks required. What is this minimum number?

## 输入格式

The input begins with an integer $ T \le 50 $ , the number of test cases. Each test case begins with two integers on their own line: $ N \le 100000 $ , the number of graduate students (who are indexed by the integers $ 1 $ through $ N $ ), and $ M $ , the number of friendships among the students. Following this are $ M $ lines, each containing two integers $ i $ and $ j $ separated by a single space. Two integers $ i $ and $ j $ represent a mutual friendship between students $ i $ and $ j $ .

The total size of the input file does not exceed 2 MB.

## 输出格式

For each test case output a single number: the minimum number of desks Dr. Baws requires to seat the students.

## 样例 #1

### 输入

```
1\n6 5\n1 2\n1 3\n1 4\n4 5\n4 6
```

### 输出

```

```

