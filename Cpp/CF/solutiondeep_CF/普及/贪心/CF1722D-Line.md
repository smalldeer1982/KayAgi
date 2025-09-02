# 题目信息

# Line

## 题目描述

There are $ n $ people in a horizontal line, each looking either to the left or the right. Each person counts the number of people in the direction they are looking. The value of the line is the sum of each person's count.

For example, in the arrangement LRRLL, where L stands for a person looking left and R stands for a person looking right, the counts for each person are $ [0, 3, 2, 3, 4] $ , and the value is $ 0+3+2+3+4=12 $ .

You are given the initial arrangement of people in the line. For each $ k $ from $ 1 $ to $ n $ , determine the maximum value of the line if you can change the direction of at most $ k $ people.

## 说明/提示

In the first test case:

- $ k=1 $ : change the direction of $ 1 $ person to make the line RLR. The total value is $ 2+1+0=3 $ .
- $ k=2 $ : change the direction of $ 2 $ people to make the line RLL. The total value is $ 2+1+2=5 $ .
- $ k=3 $ : change the direction of $ 2 $ people to make the line RLL. The total value is $ 2+1+2=5 $ . Note that you have to change the direction of at most $ k $ people.

In the second test case, it is optimal to only change the direction of the first person for all $ k $ from $ 1 $ to $ 5 $ (that is, make the line RRRLL).

## 样例 #1

### 输入

```
6
3
LLR
5
LRRLL
1
L
12
LRRRLLLRLLRL
10
LLLLLRRRRR
9
LRLRLRLRL```

### 输出

```
3 5 5 
16 16 16 16 16 
0 
86 95 98 101 102 102 102 102 102 102 102 102 
29 38 45 52 57 62 65 68 69 70 
44 50 54 56 56 56 56 56 56```

# AI分析结果

### 题目内容重写

#### 题目描述

有 $n$ 个人排成一行，每个人要么向左看，要么向右看。每个人会数自己看的方向上的人数。这一行的价值是每个人数到的人数的总和。

例如，在排列 LRRLL 中，L 表示向左看，R 表示向右看，每个人的计数分别为 $[0, 3, 2, 3, 4]$，价值为 $0+3+2+3+4=12$。

给定初始排列，对于每个 $k$ 从 $1$ 到 $n$，求在最多改变 $k$ 个人的方向的情况下，这一行的最大价值。

#### 说明/提示

在第一个测试用例中：

- $k=1$：改变一个人的方向，使排列变为 RLR，总价值为 $2+1+0=3$。
- $k=2$：改变两个人的方向，使排列变为 RLL，总价值为 $2+1+2=5$。
- $k=3$：改变两个人的方向，使排列变为 RLL，总价值为 $2+1+2=5$。注意，你最多只能改变 $k$ 个人的方向。

在第二个测试用例中，对于所有 $k$ 从 $1$ 到 $5$，最优解是只改变第一个人的方向，使排列变为 RRRLL。

#### 样例 #1

##### 输入

```
6
3
LLR
5
LRRLL
1
L
12
LRRRLLLRLLRL
10
LLLLLRRRRR
9
LRLRLRLRL
```

##### 输出

```
3 5 5 
16 16 16 16 16 
0 
86 95 98 101 102 102 102 102 102 102 102 102 
29 38 45 52 57 62 65 68 69 70 
44 50 54 56 56 56 56 56 56
```

### 题解分析与结论

#### 综合分析与结论

本题的核心是通过贪心策略，优先改变那些改变方向后对总价值贡献最大的人的方向。具体来说，对于每个人，计算其改变方向后对总价值的贡献，然后按照贡献从大到小的顺序进行改变。这样可以保证每次改变都能最大化总价值的增加。

#### 所选高分题解

##### 题解1：ScottSuperb (5星)

**关键亮点：**
- 采用贪心策略，优先改变靠近队伍两端的人的方向，因为他们的改变对总价值的贡献最大。
- 通过枚举距离队伍两端的距离，逐步计算改变方向后的贡献，并保证改变次数不超过 $k$。
- 代码简洁高效，逻辑清晰。

**核心代码：**
```cpp
for (cnt = dis = 0, n2 = n >> 1; dis < n2; ++dis) {
    if (s[dis] == 'L')
        ans += n - dis - 1 - dis, ++cnt, write(ans);
    if (s[n - dis - 1] == 'R')
        ans += n - dis - 1 - dis, ++cnt, write(ans);
}
```

##### 题解2：lihanwen12 (4星)

**关键亮点：**
- 详细解释了每个人改变方向后对总价值的贡献计算方法。
- 通过排序优先选择贡献最大的人进行改变，确保每次改变都能最大化总价值。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
sort(a + 1, a + n + 1, cmp);
for (int i = 1; i <= n; i++) {
    cout << ans + a[i].up << " ", ans += a[i].up;
}
```

##### 题解3：Epi4any (4星)

**关键亮点：**
- 强调了贪心策略的重要性，并详细说明了如何计算每个人改变方向后的贡献。
- 通过排序和前缀和的方式，快速计算每次改变后的总价值。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
sort(p + 1, p + n + 1, cmp);
for (int i = 1; i <= n; i++) {
    cout << ans + p[i] << " ", ans += p[i];
}
```

### 最优关键思路与技巧

1. **贪心策略**：优先改变那些改变方向后对总价值贡献最大的人的方向，确保每次改变都能最大化总价值。
2. **贡献计算**：对于每个人，计算其改变方向后对总价值的贡献，并按照贡献从大到小的顺序进行改变。
3. **排序与前缀和**：通过排序和前缀和的方式，快速计算每次改变后的总价值。

### 可拓展之处

- **类似题目**：可以考虑其他需要贪心策略的题目，如背包问题、区间调度问题等。
- **优化技巧**：在类似问题中，可以考虑如何快速计算每次改变后的贡献，并通过排序和前缀和的方式优化计算过程。

### 推荐题目

1. **洛谷 P1090**：合并果子（贪心策略）
2. **洛谷 P1223**：排队接水（贪心策略）
3. **洛谷 P1803**：凌乱的yyy / 线段覆盖（贪心策略）

### 个人心得摘录

- **ScottSuperb**：通过枚举距离队伍两端的距离，逐步计算改变方向后的贡献，并保证改变次数不超过 $k$，这种方法简洁高效。
- **lihanwen12**：详细解释了每个人改变方向后对总价值的贡献计算方法，并通过排序优先选择贡献最大的人进行改变，确保每次改变都能最大化总价值。
- **Epi4any**：强调了贪心策略的重要性，并详细说明了如何计算每个人改变方向后的贡献，通过排序和前缀和的方式，快速计算每次改变后的总价值。

---
处理用时：43.79秒