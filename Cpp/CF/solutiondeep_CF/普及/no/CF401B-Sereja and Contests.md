# 题目信息

# Sereja and Contests

## 题目描述

Sereja is a coder and he likes to take part in Codesorfes rounds. However, Uzhland doesn't have good internet connection, so Sereja sometimes skips rounds.

Codesorfes has rounds of two types: $ Div1 $ (for advanced coders) and $ Div2 $ (for beginner coders). Two rounds, $ Div1 $ and $ Div2 $ , can go simultaneously, ( $ Div1 $ round cannot be held without $ Div2 $ ) in all other cases the rounds don't overlap in time. Each round has a unique identifier — a positive integer. The rounds are sequentially (without gaps) numbered with identifiers by the starting time of the round. The identifiers of rounds that are run simultaneously are different by one, also the identifier of the $ Div1 $ round is always greater.

Sereja is a beginner coder, so he can take part only in rounds of $ Div2 $ type. At the moment he is taking part in a $ Div2 $ round, its identifier equals to $ x $ . Sereja remembers very well that he has taken part in exactly $ k $ rounds before this round. Also, he remembers all identifiers of the rounds he has taken part in and all identifiers of the rounds that went simultaneously with them. Sereja doesn't remember anything about the rounds he missed.

Sereja is wondering: what minimum and what maximum number of $ Div2 $ rounds could he have missed? Help him find these two numbers.

## 说明/提示

In the second sample we have unused identifiers of rounds 1, 6, 7. The minimum number of rounds Sereja could have missed equals to 2. In this case, the round with the identifier 1 will be a usual $ Div2 $ round and the round with identifier $ 6 $ will be synchronous with the $ Div1 $ round.

The maximum number of rounds equals $ 3 $ . In this case all unused identifiers belong to usual $ Div2 $ rounds.

## 样例 #1

### 输入

```
3 2
2 1
2 2
```

### 输出

```
0 0```

## 样例 #2

### 输入

```
9 3
1 2 3
2 8
1 4 5
```

### 输出

```
2 3```

## 样例 #3

### 输入

```
10 0
```

### 输出

```
5 9```

# AI分析结果



# Sereja and Contests

## 题目翻译

### 题目描述

Sereja 是一名程序员，喜欢参加 Codesorfes 比赛。Uzhland 的网络连接较差，因此他有时会错过比赛。

Codesorfes 有两种比赛类型：Div1（高级选手）和 Div2（初级选手）。Div1 和 Div2 可以同时进行（此时 Div1 必须与 Div2 同时进行），其他情况下比赛时间不重叠。每场比赛有唯一的递增编号，同时进行的两个比赛编号相差 1，且 Div1 的编号更大。

Sereja 只能参加 Div2 比赛。当前他正在参加编号为 x 的 Div2 比赛，且记得之前参加过 k 场比赛的所有编号（包括同步进行的其他比赛）。求他可能错过的 Div2 比赛的最小和最大数量。

### 输入输出样例

#### 样例 #1
**输入**
```
3 2
2 1
2 2
```
**输出**
```
0 0
```

#### 样例 #2
**输入**
```
9 3
1 2 3
2 8
1 4 5
```
**输出**
```
2 3
```

#### 样例 #3
**输入**
```
10 0
```
**输出**
```
5 9
```

---

## 算法分类
模拟

---

## 题解分析与关键思路

### 核心思路
1. **最大值计算**：所有未被标记的编号（1 至 x-1）的总数量。
2. **最小值计算**：将连续未被标记的编号视为 Div1+Div2 组合，每对减少一次计数。公式为 `总数量 - 连续对数`。

### 最优题解（评分：4★）

#### 题解作者：N_z_
**关键亮点**  
- 直接遍历未被标记的区间，动态统计连续对。
- 代码简洁高效，时间复杂度 O(n)。

**核心代码**  
```cpp
int ans1 = 0;
for (int x = 1; x < n; x++)
    if (!b[x]) ans1++; // 最大值统计

int ans2 = ans1;
for (int x = 1; x < n; x++)
    if (!b[x] && !b[x+1] && x+1 < n)
        ans2--, x++; // 最小值统计
```

---

#### 题解作者：Camellia_Spoil
**关键亮点**  
- 通过维护连续段长度，分块计算最少次数。
- 逻辑清晰，适合理解分段处理。

**核心代码**  
```cpp
int len = 0, mi = 0;
for (int i = 1; i < x; i++) {
    if (!vis[i]) len++;
    else {
        mi += len / 2 + (len % 2);
        len = 0;
    }
}
mi += len / 2 + (len % 2); // 处理最后一段
```

---

#### 题解作者：KevinHu0402
**关键亮点**  
- 显式存储未标记的编号数组，直观处理相邻关系。
- 双指针遍历减少空间复杂度。

**核心代码**  
```cpp
vector<int> ans;
for (int i = 1; i < n; i++)
    if (!a[i]) ans.push_back(i);

int anss = 0;
for (int i = 0; i < ans.size(); i++) {
    if (i+1 < ans.size() && ans[i+1] - ans[i] == 1) i++;
    anss++;
}
```

---

## 相似题目推荐
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047) - 区间标记与统计
2. [P2669 金币](https://www.luogu.com.cn/problem/P2669) - 分段累加计算
3. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147) - 连续区间处理

---
处理用时：220.93秒