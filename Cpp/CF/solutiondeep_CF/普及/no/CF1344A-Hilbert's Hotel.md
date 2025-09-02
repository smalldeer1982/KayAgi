# 题目信息

# Hilbert's Hotel

## 题目描述

Hilbert's Hotel is a very unusual hotel since the number of rooms is infinite! In fact, there is exactly one room for every integer, including zero and negative integers. Even stranger, the hotel is currently at full capacity, meaning there is exactly one guest in every room. The hotel's manager, David Hilbert himself, decides he wants to shuffle the guests around because he thinks this will create a vacancy (a room without a guest).

For any integer $ k $ and positive integer $ n $ , let $ k\bmod n $ denote the remainder when $ k $ is divided by $ n $ . More formally, $ r=k\bmod n $ is the smallest non-negative integer such that $ k-r $ is divisible by $ n $ . It always holds that $ 0\le k\bmod n\le n-1 $ . For example, $ 100\bmod 12=4 $ and $ (-1337)\bmod 3=1 $ .

Then the shuffling works as follows. There is an array of $ n $ integers $ a_0,a_1,\ldots,a_{n-1} $ . Then for each integer $ k $ , the guest in room $ k $ is moved to room number $ k+a_{k\bmod n} $ .

After this shuffling process, determine if there is still exactly one guest assigned to each room. That is, there are no vacancies or rooms with multiple guests.

## 说明/提示

In the first test case, every guest is shifted by $ 14 $ rooms, so the assignment is still unique.

In the second test case, even guests move to the right by $ 1 $ room, and odd guests move to the left by $ 1 $ room. We can show that the assignment is still unique.

In the third test case, every fourth guest moves to the right by $ 1 $ room, and the other guests move to the right by $ 5 $ rooms. We can show that the assignment is still unique.

In the fourth test case, guests $ 0 $ and $ 1 $ are both assigned to room $ 3 $ .

In the fifth test case, guests $ 1 $ and $ 2 $ are both assigned to room $ 2 $ .

## 样例 #1

### 输入

```
6
1
14
2
1 -1
4
5 5 5 1
3
3 2 1
2
0 1
5
-239 -2 -100 -3 -11```

### 输出

```
YES
YES
YES
NO
NO
YES```

# AI分析结果

### 题目内容重写
# 希尔伯特旅馆

## 题目描述

希尔伯特旅馆是一个非常不寻常的旅馆，因为它的房间数量是无限的！事实上，每个整数都有一个房间，包括零和负整数。更奇怪的是，旅馆目前已经满员，意味着每个房间都恰好有一位客人。旅馆的经理大卫·希尔伯特决定重新安排客人的位置，因为他认为这样会创造出一个空房间（没有客人的房间）。

对于任何整数 $k$ 和正整数 $n$，令 $k\bmod n$ 表示 $k$ 除以 $n$ 的余数。更正式地，$r=k\bmod n$ 是最小的非负整数，使得 $k-r$ 能被 $n$ 整除。它总是满足 $0\le k\bmod n\le n-1$。例如，$100\bmod 12=4$ 和 $(-1337)\bmod 3=1$。

然后，重新安排的过程如下。有一个包含 $n$ 个整数的数组 $a_0,a_1,\ldots,a_{n-1}$。对于每个整数 $k$，房间 $k$ 中的客人将被移动到房间号 $k+a_{k\bmod n}$。

在这个重新安排过程之后，确定是否每个房间仍然恰好有一位客人。也就是说，没有空房间或有多位客人的房间。

## 说明/提示

在第一个测试用例中，每个客人都被移动了 $14$ 个房间，因此分配仍然是唯一的。

在第二个测试用例中，偶数房间的客人向右移动 $1$ 个房间，奇数房间的客人向左移动 $1$ 个房间。我们可以证明分配仍然是唯一的。

在第三个测试用例中，每第四个客人向右移动 $1$ 个房间，其他客人向右移动 $5$ 个房间。我们可以证明分配仍然是唯一的。

在第四个测试用例中，客人 $0$ 和 $1$ 都被分配到房间 $3$。

在第五个测试用例中，客人 $1$ 和 $2$ 都被分配到房间 $2$。

## 样例 #1

### 输入

```
6
1
14
2
1 -1
4
5 5 5 1
3
3 2 1
2
0 1
5
-239 -2 -100 -3 -11```

### 输出

```
YES
YES
YES
NO
NO
YES```

### 算法分类
数学

### 题解分析与结论
本题的核心在于判断重新安排后是否每个房间仍然恰好有一位客人。通过分析，可以发现问题的关键在于判断是否存在两个不同的整数 $x$ 和 $y$，使得 $x + a_{x \bmod n} = y + a_{y \bmod n}$。如果存在这样的 $x$ 和 $y$，则输出 `NO`，否则输出 `YES`。

各题解的主要思路是通过数学推导，将问题转化为判断 $a_i + i$ 在模 $n$ 意义下是否有重复。如果存在重复，则输出 `NO`，否则输出 `YES`。大多数题解都使用了桶或 `map` 来记录 $a_i + i$ 的模 $n$ 值，从而判断是否有重复。

### 评分较高的题解
#### 作者：tommymio (5星)
**关键亮点**：通过数学推导，将问题转化为判断 $a_i + i$ 在模 $n$ 意义下是否有重复，并使用桶记录，代码简洁高效。
**代码核心实现**：
```cpp
for(register int i=0;i<n;++i) ++t[((read()+i)%n+n)%n];
for(register int i=0;i<2*n;++i) if(t[i]>1) {flag=0;break;}
```
**个人心得**：通过数学推导简化问题，使用桶记录模 $n$ 值，代码简洁高效。

#### 作者：killer_queen4804 (4星)
**关键亮点**：通过排序后判断 $a_i + i$ 的模 $n$ 值是否连续，思路清晰，代码简洁。
**代码核心实现**：
```cpp
for(int i=0;i<n;i++) a[i]=((a[i]+i)%n+n)%n;
sort(a,a+n);
for(int i=0;i<n;i++) if(a[i]!=i) {flag=0;break;}
```
**个人心得**：通过排序判断模 $n$ 值是否连续，思路清晰，代码简洁。

#### 作者：0x3F (4星)
**关键亮点**：使用桶记录 $a_i + i$ 的模 $n$ 值，代码简洁，处理负数取模的方式值得借鉴。
**代码核心实现**：
```cpp
for(int i = 0; i < n; i++) {
    a[i] = ((a[i] + i) % n + n) % n;
    if(vis[a[i]]) {cout << "NO" << endl; goto fail;}
    vis[a[i]] = 1;
}
```
**个人心得**：使用桶记录模 $n$ 值，处理负数取模的方式值得借鉴。

### 最优关键思路或技巧
1. **数学推导**：将问题转化为判断 $a_i + i$ 在模 $n$ 意义下是否有重复。
2. **桶记录**：使用桶或 `map` 记录 $a_i + i$ 的模 $n$ 值，判断是否有重复。
3. **负数取模**：处理负数取模时，使用 $(a \bmod n + n) \bmod n$ 的方式确保结果为非负数。

### 可拓展之处
1. **同类型题**：类似的问题可以出现在其他需要判断唯一性的场景中，如判断数组中是否有重复元素。
2. **类似算法套路**：使用桶或 `map` 记录模 $n$ 值的方法可以应用于其他需要判断唯一性的问题。

### 推荐题目
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1496 火烧赤壁](https://www.luogu.com.cn/problem/P1496)

---
处理用时：41.87秒