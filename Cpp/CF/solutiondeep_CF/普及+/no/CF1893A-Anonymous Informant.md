# 题目信息

# Anonymous Informant

## 题目描述

You are given an array $ b_1, b_2, \ldots, b_n $ .

An anonymous informant has told you that the array $ b $ was obtained as follows: initially, there existed an array $ a_1, a_2, \ldots, a_n $ , after which the following two-component operation was performed $ k $ times:

1. A fixed point $ ^{\dagger} $ $ x $ of the array $ a $ was chosen.
2. Then, the array $ a $ was cyclically shifted to the left $ ^{\ddagger} $ exactly $ x $ times.

As a result of $ k $ such operations, the array $ b_1, b_2, \ldots, b_n $ was obtained. You want to check if the words of the anonymous informant can be true or if they are guaranteed to be false.

 $ ^{\dagger} $ A number $ x $ is called a fixed point of the array $ a_1, a_2, \ldots, a_n $ if $ 1 \leq x \leq n $ and $ a_x = x $ .

 $ ^{\ddagger} $ A cyclic left shift of the array $ a_1, a_2, \ldots, a_n $ is the array $ a_2, \ldots, a_n, a_1 $ .

## 说明/提示

In the first test case, the array $ a $ could be equal to $ [3, 2, 3, 4, 3] $ . In the first operation, a fixed point $ x = 2 $ was chosen, and after $ 2 $ left shifts, the array became $ [3, 4, 3, 3, 2] $ . In the second operation, a fixed point $ x = 3 $ was chosen, and after $ 3 $ left shifts, the array became $ [3, 2, 3, 4, 3] $ . In the third operation, a fixed point $ x = 3 $ was chosen again, and after $ 3 $ left shifts, the array became $ [4, 3, 3, 2, 3] $ , which is equal to the array $ b $ .

In the second test case, the array $ a $ could be equal to $ [7, 2, 1] $ . After the operation with a fixed point $ x = 2 $ , the array became $ [1, 7, 2] $ . Then, after the operation with a fixed point $ x = 1 $ , the array returned to its initial state $ [7, 2, 1] $ . These same $ 2 $ operations (with $ x = 2 $ , and $ x = 1 $ ) were repeated $ 49 $ times. So, after $ 100 $ operations, the array returned to $ [7, 2, 1] $ .

In the third test case, it can be shown that there is no solution.

## 样例 #1

### 输入

```
6
5 3
4 3 3 2 3
3 100
7 2 1
5 5
6 1 1 1 1
1 1000000000
1
8 48
9 10 11 12 13 14 15 8
2 1
1 42```

### 输出

```
Yes
Yes
No
Yes
Yes
No```

# AI分析结果

### 题目内容重写

#### 匿名线人

##### 题目描述

给定一个数组 $ b_1, b_2, \ldots, b_n $。

一个匿名线人告诉你，数组 $ b $ 是通过以下方式得到的：最初存在一个数组 $ a_1, a_2, \ldots, a_n $，然后进行了 $ k $ 次由两部分组成的操作：

1. 选择一个数组 $ a $ 的不动点 $ x $（即 $ 1 \leq x \leq n $ 且 $ a_x = x $）。
2. 将数组 $ a $ 循环左移 $ x $ 次。

经过 $ k $ 次这样的操作后，得到了数组 $ b_1, b_2, \ldots, b_n $。你需要检查匿名线人的话是否可能为真，或者是否肯定为假。

##### 说明/提示

在第一个测试用例中，数组 $ a $ 可能等于 $ [3, 2, 3, 4, 3] $。在第一次操作中，选择了不动点 $ x = 2 $，经过 $ 2 $ 次左移后，数组变为 $ [3, 4, 3, 3, 2] $。在第二次操作中，选择了不动点 $ x = 3 $，经过 $ 3 $ 次左移后，数组变为 $ [3, 2, 3, 4, 3] $。在第三次操作中，再次选择了不动点 $ x = 3 $，经过 $ 3 $ 次左移后，数组变为 $ [4, 3, 3, 2, 3] $，这与数组 $ b $ 相等。

在第二个测试用例中，数组 $ a $ 可能等于 $ [7, 2, 1] $。在选择了不动点 $ x = 2 $ 的操作后，数组变为 $ [1, 7, 2] $。然后，在选择了不动点 $ x = 1 $ 的操作后，数组回到了初始状态 $ [7, 2, 1] $。这两个操作（$ x = 2 $ 和 $ x = 1 $）重复了 $ 49 $ 次。因此，经过 $ 100 $ 次操作后，数组回到了 $ [7, 2, 1] $。

在第三个测试用例中，可以证明没有解。

##### 样例 #1

###### 输入

```
6
5 3
4 3 3 2 3
3 100
7 2 1
5 5
6 1 1 1 1
1 1000000000
1
8 48
9 10 11 12 13 14 15 8
2 1
1 42```

###### 输出

```
Yes
Yes
No
Yes
Yes
No```

### 算法分类
模拟

### 题解分析与结论

#### 题解1：EternityLove (5星)
- **关键亮点**：通过逆向思维，将问题转化为判断 $b$ 序列能否进行 $k$ 次逆操作。通过模拟指针移动，避免了数组的实际移动，优化了时间复杂度。
- **代码实现**：使用一个指针 `now` 来记录当前操作的位置，通过循环左移 `a[now]` 位来模拟逆操作。如果 `a[now] > n`，则直接输出 "No"。通过 `flag` 数组记录访问过的位置，避免重复操作。
- **优化**：由于 $k$ 可能很大，通过记录访问过的位置，最多只需要模拟 $n$ 次操作即可得到答案。

#### 题解2：fish_shit (4星)
- **关键亮点**：同样采用逆向思维，通过模拟每次操作后最后一个数的位置来判断是否可以进行逆操作。通过 `vis` 数组记录访问过的位置，避免重复操作。
- **代码实现**：使用 `pos` 变量记录当前操作的位置，通过 `b[pos]` 来确定下一次操作的位置。如果 `b[pos] > n`，则直接输出 "No"。通过 `vis` 数组记录访问过的位置，避免重复操作。
- **优化**：最多只需要模拟 $n$ 次操作即可得到答案。

#### 题解3：wangyibo201026 (3星)
- **关键亮点**：通过图论的思想，将问题转化为图的遍历问题。通过建图并暴力跑最长路来判断是否存在解。
- **代码实现**：通过 `add` 函数建图，`dfs` 函数遍历图。如果遍历到环或者遍历次数达到 $k$，则输出 "Yes"。
- **优化**：通过图的遍历，每个点每条边最多遍历一次，复杂度为 $O(n)$。

### 最优关键思路或技巧
- **逆向思维**：通过逆向操作来简化问题，避免了直接模拟 $k$ 次操作的复杂性。
- **指针模拟**：通过指针记录当前操作的位置，避免了数组的实际移动，优化了时间复杂度。
- **访问记录**：通过记录访问过的位置，避免重复操作，最多只需要模拟 $n$ 次操作即可得到答案。

### 可拓展之处
- **类似问题**：类似的问题可以通过逆向思维和指针模拟来优化时间复杂度。例如，某些需要多次操作的问题，可以通过逆向操作来简化问题。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)

### 个人心得摘录
- **EternityLove**：通过逆向思维，将问题转化为判断 $b$ 序列能否进行 $k$ 次逆操作，避免了直接模拟 $k$ 次操作的复杂性。
- **fish_shit**：通过模拟每次操作后最后一个数的位置来判断是否可以进行逆操作，避免了数组的实际移动，优化了时间复杂度。
- **wangyibo201026**：通过图论的思想，将问题转化为图的遍历问题，通过建图并暴力跑最长路来判断是否存在解。

---
处理用时：48.26秒