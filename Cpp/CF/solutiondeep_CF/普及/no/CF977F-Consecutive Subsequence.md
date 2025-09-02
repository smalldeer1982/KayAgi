# 题目信息

# Consecutive Subsequence

## 题目描述

You are given an integer array of length $ n $ .

You have to choose some subsequence of this array of maximum length such that this subsequence forms a increasing sequence of consecutive integers. In other words the required sequence should be equal to $ [x, x + 1, \dots, x + k - 1] $ for some value $ x $ and length $ k $ .

Subsequence of an array can be obtained by erasing some (possibly zero) elements from the array. You can erase any elements, not necessarily going successively. The remaining elements preserve their order. For example, for the array $ [5, 3, 1, 2, 4] $ the following arrays are subsequences: $ [3] $ , $ [5, 3, 1, 2, 4] $ , $ [5, 1, 4] $ , but the array $ [1, 3] $ is not.

## 说明/提示

All valid answers for the first example (as sequences of indices):

- $ [1, 3, 5, 6] $
- $ [2, 3, 5, 6] $

All valid answers for the second example:

- $ [1, 4] $
- $ [2, 5] $
- $ [3, 6] $

All valid answers for the third example:

- $ [1] $
- $ [2] $
- $ [3] $
- $ [4] $

All valid answers for the fourth example:

- $ [1, 2, 3, 7, 8, 9] $

## 样例 #1

### 输入

```
7
3 3 4 7 5 6 8
```

### 输出

```
4
2 3 5 6 
```

## 样例 #2

### 输入

```
6
1 3 5 2 4 6
```

### 输出

```
2
1 4 
```

## 样例 #3

### 输入

```
4
10 9 8 7
```

### 输出

```
1
1 
```

## 样例 #4

### 输入

```
9
6 7 8 3 4 5 9 10 11
```

### 输出

```
6
1 2 3 7 8 9 
```

# AI分析结果

### 题目内容重写
#### 连续子序列

**题目描述**

给定一个长度为 $n$ 的整数数组。

你需要选择一个子序列，使得这个子序列形成一个连续递增的整数序列，并且这个子序列的长度尽可能长。换句话说，要求的子序列应该是 $[x, x + 1, \dots, x + k - 1]$ 的形式，其中 $x$ 是某个整数，$k$ 是子序列的长度。

子序列可以通过从数组中删除一些（可能为零）元素得到。你可以删除任何元素，不一定是连续的。剩余的元素保持它们的原始顺序。例如，对于数组 $[5, 3, 1, 2, 4]$，以下数组是子序列：$[3]$，$[5, 3, 1, 2, 4]$，$[5, 1, 4]$，但数组 $[1, 3]$ 不是。

**说明/提示**

第一个样例的所有有效答案（作为索引序列）：

- $[1, 3, 5, 6]$
- $[2, 3, 5, 6]$

第二个样例的所有有效答案：

- $[1, 4]$
- $[2, 5]$
- $[3, 6]$

第三个样例的所有有效答案：

- $[1]$
- $[2]$
- $[3]$
- $[4]$

第四个样例的所有有效答案：

- $[1, 2, 3, 7, 8, 9]$

**样例 #1**

**输入**

```
7
3 3 4 7 5 6 8
```

**输出**

```
4
2 3 5 6 
```

**样例 #2**

**输入**

```
6
1 3 5 2 4 6
```

**输出**

```
2
1 4 
```

**样例 #3**

**输入**

```
4
10 9 8 7
```

**输出**

```
1
1 
```

**样例 #4**

**输入**

```
9
6 7 8 3 4 5 9 10 11
```

**输出**

```
6
1 2 3 7 8 9 
```

### 算法分类
动态规划

### 题解分析与结论
本题的核心是找到数组中长度最长的连续递增子序列。所有题解都采用了动态规划的思路，结合 `map` 数据结构来优化查找过程。不同题解在实现细节上有所差异，但整体思路相似。

### 所选高星题解

#### 题解1：爬行者小郑 (5星)
**关键亮点**：
- 使用 `map` 来存储每个数对应的索引，优化查找过程。
- 通过动态规划计算以每个数结尾的最长连续子序列长度。
- 详细解释了如何输出子序列的索引。

**核心代码**：
```cpp
map<int,int>m;
int ans[200005],a[200005];
int maxa, l, r;

for(int i=1;i<=n;i++) {
    cin>>a[i];
    int tmp=m[a[i]-1];
    if(tmp) ans[i]=ans[tmp]+1;
    else ans[i]=1;
    m[a[i]]=i;
}
for(int i=1;i<=n;i++) {
    if(ans[i]>maxa) maxa=ans[i], r=a[i];
}
cout<<maxa<<endl;
l=r-maxa+1;
int idx=l;
for(int i=1;i<=n;i++) {
    if(a[i]==idx) {
        cout<<i<<" ";
        idx++;
    }
}
```

#### 题解2：泠小毒 (4星)
**关键亮点**：
- 简洁的代码实现，直接使用 `map` 进行动态规划。
- 在动态规划过程中直接记录最大长度和结束值。

**核心代码**：
```cpp
map<int,int>a;
int ans=0, w=0, x[200010];

for(int i=1;i<=n;i++) {
    scanf("%d",&s);
    x[i]=s;
    a[s]=max(a[s],a[s-1]+1);
    if(a[s]>ans) ans=a[s], w=s;
}
printf("%d\n",ans);
for(int i=1;i<=n;i++) {
    if(x[i]==w-ans+1) print(i), ans--;
}
```

#### 题解3：FishingStar (4星)
**关键亮点**：
- 使用 `map` 存储每个数的最后一个出现位置。
- 通过 `last` 数组记录每个数的前一个数的索引，方便输出子序列。

**核心代码**：
```cpp
map<int, int> s;
int dp[200005], last[200005];

for(int i = 1; i < n; i++) {
    s[a[i]] = i;
    if(s.find(a[i] - 1) != s.end()) {
        dp[i] = dp[s[a[i] - 1]] + 1;
        last[i] = s[a[i] - 1];
    } else {
        dp[i] = 1;
        last[i] = i;
    }
    if(dp[i] > ans) {
        ans = dp[i];
        ans_i = i;
    }
}
```

### 最优关键思路
1. **动态规划**：通过 `map` 存储每个数的索引，动态规划计算以每个数结尾的最长连续子序列长度。
2. **输出子序列**：通过记录子序列的起始值和结束值，遍历数组输出对应的索引。

### 可拓展之处
类似的问题可以扩展到其他类型的子序列问题，如最长非递减子序列、最长等差子序列等。使用 `map` 或 `unordered_map` 可以优化查找过程，适用于大范围数据的处理。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
3. [P1439 最长公共子序列](https://www.luogu.com.cn/problem/P1439)

### 个人心得摘录
- **爬行者小郑**：在多个数的情况下，输出字典序最小的答案，无需复杂处理。
- **泠小毒**：题目难度被高估，实际是道水题，直接使用 `map` 即可解决。
- **FishingStar**：通过 `last` 数组记录前一个数的索引，方便输出子序列，类似于链表的遍历。

---
处理用时：39.94秒