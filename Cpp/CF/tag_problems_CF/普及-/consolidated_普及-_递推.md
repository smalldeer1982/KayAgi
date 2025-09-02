---
title: "Thorns and Coins"
layout: "post"
diff: 普及-
pid: CF1932A
tag: ['递推']
---

# Thorns and Coins

## 题目描述

你发现了一个世界。这是一个有 $n$ 个连续单元格的路径，每个单元格可以是空的、含有荆棘或者硬币。在一次移动中，你可以沿着路径向右移动一格或两格，前提是目标单元格不含有荆棘（并且属于路径）。如果你移动到的单元格正好含有硬币的单元格，你就会捡起它。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/bbfdc346db7373b864d2642fd35cef4a577781a2.png)
 
上图中，绿色箭头表示合法移动，红色箭头表示非法移动。你想要在这个发现的世界中收集尽可能多的硬币。你从路径的最左边单元格开始，找出你可以在这个世界中收集的最大硬币数量。


第二个示例的图片如下：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/e0c47ff41c71ce332d7b876f950ed50eee6c4f4d.png)

第三个示例的图片如下：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/880dc20f87f4adb0891a434fca6a4717f38a2a7e.png)

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t\le 1000$），表示测试用例的数量。然后是 $t$ 组测试数据的描述。

每组测试数据的第一行包含一个整数 $n$（$1\le n\le50$），表示路径的长度。

每组测试数据的第二行包含一个长度为 $n$ 的字符串，描述路径。字符 `.` 表示空单元格，`@` 表示含有硬币的单元格，`*` 表示含有荆棘的单元格。保证第一个单元格是空的。

## 输出格式

对于每个测试数据，输出一个整数，表示你可以收集的最大硬币数量。

### 样例解释

## 样例 #1

### 输入

```
3
10
.@@*@.**@@
5
.@@@@
15
.@@..@***..@@@*
```

### 输出

```
3
4
3
```



---

---
title: "Basil's Garden"
layout: "post"
diff: 普及-
pid: CF1987C
tag: ['递推']
---

# Basil's Garden

## 题目描述

There are $ n $ flowers in a row, the $ i $ -th of them initially has a positive height of $ h_i $ meters.

Every second, the wind will blow from the left, causing the height of some flowers to decrease.

Specifically, every second, for each $ i $ from $ 1 $ to $ n $ , in this order, the following happens:

- If $ i = n $ or $ h_i > h_{i + 1} $ , the value of $ h_i $ changes to $ \max(0, h_i - 1) $ .

How many seconds will pass before $ h_i=0 $ for all $ 1 \le i \le n $ for the first time?

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of flowers.

The second line of each test case contains $ n $ integers $ h_1, h_2, \ldots, h_n $ ( $ 1 \le h_i \le 10 ^ 9 $ ) — the heights of the flowers.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of seconds that will pass before $ h_i=0 $ for all $ 1 \le i \le n $ .

## 说明/提示

In the first test case, the flower heights change as follows: $ [1, 1, 2] \rightarrow [1, 1, 1] \rightarrow [1, 1, 0] \rightarrow [1, 0, 0] \rightarrow [0, 0, 0] $ .

In the second test case, the flower heights change as follows: $ [3, 1] \rightarrow [2, 0] \rightarrow [1, 0] \rightarrow [0, 0] $ .

## 样例 #1

### 输入

```
4
3
1 1 2
2
3 1
1
9
5
7 4 4 3 2
```

### 输出

```
4
3
9
7
```



---

---
title: "Calculating Function"
layout: "post"
diff: 普及-
pid: CF486A
tag: ['递推']
---

# Calculating Function

## 题目描述

For a positive integer $ n $ let's define a function $ f $ :

 $ f(n)=-1+2-3+..+(-1)^{n}n $

Your task is to calculate $ f(n) $ for a given integer $ n $ .

## 输入格式

The single line contains the positive integer $ n $ ( $ 1<=n<=10^{15} $ ).

## 输出格式

Print $ f(n) $ in a single line.

## 说明/提示

 $ f(4)=-1+2-3+4=2 $

 $ f(5)=-1+2-3+4-5=-3 $

## 样例 #1

### 输入

```
4

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5

```

### 输出

```
-3

```



---

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

