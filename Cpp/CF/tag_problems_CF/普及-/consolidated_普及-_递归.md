---
title: "New Year Transportation"
layout: "post"
diff: 普及-
pid: CF500A
tag: ['递推', '递归']
---

# New Year Transportation

## 题目描述

New Year is coming in Line World! In this world, there are $ n $ cells numbered by integers from $ 1 $ to $ n $ , as a $ 1×n $ board. People live in cells. However, it was hard to move between distinct cells, because of the difficulty of escaping the cell. People wanted to meet people who live in other cells.

So, user tncks0121 has made a transportation system to move between these cells, to celebrate the New Year. First, he thought of $ n-1 $ positive integers $ a_{1},a_{2},...,a_{n-1} $ . For every integer $ i $ where $ 1<=i<=n-1 $ the condition $ 1<=a_{i}<=n-i $ holds. Next, he made $ n-1 $ portals, numbered by integers from 1 to $ n-1 $ . The $ i $ -th ( $ 1<=i<=n-1 $ ) portal connects cell $ i $ and cell $ (i+a_{i}) $ , and one can travel from cell $ i $ to cell $ (i+a_{i}) $ using the $ i $ -th portal. Unfortunately, one cannot use the portal backwards, which means one cannot move from cell $ (i+a_{i}) $ to cell $ i $ using the $ i $ -th portal. It is easy to see that because of condition $ 1<=a_{i}<=n-i $ one can't leave the Line World using portals.

Currently, I am standing at cell $ 1 $ , and I want to go to cell $ t $ . However, I don't know whether it is possible to go there. Please determine whether I can go to cell $ t $ by only using the construted transportation system.

## 输入格式

The first line contains two space-separated integers $ n $ ( $ 3<=n<=3×10^{4} $ ) and $ t $ ( $ 2<=t<=n $ ) — the number of cells, and the index of the cell which I want to go to.

The second line contains $ n-1 $ space-separated integers $ a_{1},a_{2},...,a_{n-1} $ ( $ 1<=a_{i}<=n-i $ ). It is guaranteed, that using the given transportation system, one cannot leave the Line World.

## 输出格式

If I can go to cell $ t $ using the transportation system, print "YES". Otherwise, print "NO".

## 说明/提示

In the first sample, the visited cells are: $ 1,2,4 $ ; so we can successfully visit the cell $ 4 $ .

In the second sample, the possible cells to visit are: $ 1,2,4,6,7,8 $ ; so we can't visit the cell $ 5 $ , which we want to visit.

## 样例 #1

### 输入

```
8 4
1 2 1 2 1 2 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
8 5
1 2 1 2 1 1 1

```

### 输出

```
NO

```



---

---
title: "Splits"
layout: "post"
diff: 普及-
pid: CF964A
tag: ['数学', '贪心', '递归']
---

# Splits

## 题目描述

我们定义正整数$n$的分裂为一个由正整数组成的不上升序列，且序列数字和为$n$

举个栗子：下列这些序列都是$8$的分裂：$[4,4],[3,3,2],[2,2,1,1,1],[5,2,1]$

下列这些序列不是$8$的分裂：$[1,7],[5,4],[11,-3],[1,1,4,1,1]$

一个分裂的权是序列第一个数出现的次数，举个例子：$[1,1,1,1,1]$的权是$5$，$[5,5,3,3,3]$的权是$2$，$[9]$的权是$1$

现在给出$n$，求$n$的分裂有多少个不同的权

## 输入格式

第一行为$n(1\leq n \leq 10^9)$

## 输出格式

答案

## 样例 #1

### 输入

```
7

```

### 输出

```
4

```

## 样例 #2

### 输入

```
8

```

### 输出

```
5

```

## 样例 #3

### 输入

```
9

```

### 输出

```
5

```



---

---
title: "Hexadecimal's Numbers"
layout: "post"
diff: 普及-
pid: CF9C
tag: ['递归', '枚举', '进制', '队列']
---

# Hexadecimal's Numbers

## 题目描述

One beautiful July morning a terrible thing happened in Mainframe: a mean virus Megabyte somehow got access to the memory of his not less mean sister Hexadecimal. He loaded there a huge amount of $ n $ different natural numbers from 1 to $ n $ to obtain total control over her energy.

But his plan failed. The reason for this was very simple: Hexadecimal didn't perceive any information, apart from numbers written in binary format. This means that if a number in a decimal representation contained characters apart from 0 and 1, it was not stored in the memory. Now Megabyte wants to know, how many numbers were loaded successfully.

## 输入格式

Input data contains the only number $ n $ ( $ 1<=n<=10^{9} $ ).

## 输出格式

Output the only number — answer to the problem.

## 说明/提示

For $ n $ = 10 the answer includes numbers 1 and 10.

## 样例 #1

### 输入

```
10

```

### 输出

```
2
```



---

