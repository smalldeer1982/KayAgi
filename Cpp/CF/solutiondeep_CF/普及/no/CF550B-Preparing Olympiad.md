# 题目信息

# Preparing Olympiad

## 题目描述

You have $ n $ problems. You have estimated the difficulty of the $ i $ -th one as integer $ c_{i} $ . Now you want to prepare a problemset for a contest, using some of the problems you've made.

A problemset for the contest must consist of at least two problems. You think that the total difficulty of the problems of the contest must be at least $ l $ and at most $ r $ . Also, you think that the difference between difficulties of the easiest and the hardest of the chosen problems must be at least $ x $ .

Find the number of ways to choose a problemset for the contest.

## 说明/提示

In the first example two sets are suitable, one consisting of the second and third problem, another one consisting of all three problems.

In the second example, two sets of problems are suitable — the set of problems with difficulties 10 and 30 as well as the set of problems with difficulties 20 and 30.

In the third example any set consisting of one problem of difficulty 10 and one problem of difficulty 20 is suitable.

## 样例 #1

### 输入

```
3 5 6 1
1 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 40 50 10
10 20 30 25
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 25 35 10
10 10 20 10 20
```

### 输出

```
6
```

# AI分析结果



### 中文题目
#### 准备竞赛

**题目描述**

你有 $n$ 个题目，第 $i$ 个题目的难度为整数 $c_i$。现在需要从中选若干题目组成一个比赛题集。要求如下：
1. 题集至少包含 **2** 个题目；
2. 题集总难度在 $[l, r]$ 范围内；
3. 题集中最难题与最简单题的难度差至少为 $x$。

求满足条件的选题方式数目。

**样例输入输出**  
（参见原题内容）

---

### 算法分类
**枚举**

---

### 题解分析与结论

所有题解均基于 **枚举子集** 的思路，利用 $n \leq 15$ 的小数据范围，直接遍历所有可能的子集组合并检查条件。实现方式主要分为两类：
1. **二进制枚举**：将子集表示为二进制数，逐位检查是否选中，并维护总和、最大值、最小值。
2. **DFS回溯**：递归选择或不选每个题目，传递当前总和、最大值、最小值，减少重复计算。

**关键优化点**：
- **提前排序**：部分题解先对难度排序，简化最大值和最小值的计算。
- **状态维护**：在DFS过程中动态维护当前总和、最大值、最小值，避免子集生成后重新遍历计算。

---

### 高星题解推荐

#### 1. 作者：ChrisWangZi（DFS回溯）  
**⭐️⭐️⭐️⭐️⭐️**  
**亮点**：  
- 代码简洁，递归时动态维护 `sum`、`maxn`、`minn`，避免后续重复计算。  
- 初始 `minn` 设为极大值，`maxn` 设为极小值，处理边界清晰。  
**核心代码**：  
```cpp
void dfs(int k, int sum, int minn, int maxn, int cnt) {
    if (k == n) {
        if (cnt >= 2 && sum >= l && sum <= r && maxn - minn >= x) ans++;
        return;
    }
    // 选第 k+1 题
    dfs(k + 1, sum + c[k+1], min(minn, c[k+1]), max(maxn, c[k+1]), cnt + 1);
    // 不选
    dfs(k + 1, sum, minn, maxn, cnt);
}
```

#### 2. 作者：LYR_（DFS回溯）  
**⭐️⭐️⭐️⭐️**  
**亮点**：  
- 初始 `minn` 设为 `INT_MAX`，确保首次选中元素后正确更新最小值。  
- 递归终止条件统一判断，逻辑集中。  
**核心代码**：  
```cpp
void dfs(int p, int sum, int maxn, int minn) {
    if (p == n + 1) {
        if (sum >= l && sum <= r && maxn - minn >= x) ans++;
        return;
    }
    dfs(p + 1, sum + a[p], max(maxn, a[p]), min(minn, a[p]));
    dfs(p + 1, sum, maxn, minn);
}
```

#### 3. 作者：Z_M__（二进制枚举）  
**⭐️⭐️⭐️⭐️**  
**亮点**：  
- 显式遍历所有二进制状态，适合理解枚举本质。  
- 通过排序预处理，简化最大值和最小值计算。  
**核心代码**：  
```cpp
sort(a, a + n); // 预处理排序
for (int i = 0; i < (1 << n); i++) {
    int sum = 0, min_val = INF, max_val = -INF, cnt = 0;
    for (int j = 0; j < n; j++) {
        if (i & (1 << j)) {
            sum += a[j];
            min_val = min(min_val, a[j]);
            max_val = max(max_val, a[j]);
            cnt++;
        }
    }
    if (cnt >= 2 && sum >= l && sum <= r && max_val - min_val >= x) ans++;
}
```

---

### 关键思路总结
1. **枚举所有子集**：利用 $n$ 较小的特点，直接遍历 $2^n$ 种可能。
2. **动态维护状态**：在DFS或二进制枚举过程中，实时更新总和、最大值、最小值，避免生成子集后重新计算。
3. **排序预处理**：对难度排序可简化最大值和最小值的获取，尤其是对二进制枚举更高效。

---

### 类似题目推荐
1. [P2036 PERKET](https://www.luogu.com.cn/problem/P2036)（枚举子集，计算酸度和苦度差）  
2. [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)（子集生成与输出）  
3. [P1036 选数](https://www.luogu.com.cn/problem/P1036)（子集和与质数判断）

---
处理用时：85.67秒