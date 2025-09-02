# 题目信息

# New Year and Rating

## 题目描述

Every Codeforces user has rating, described with one integer, possibly negative or zero. Users are divided into two divisions. The first division is for users with rating $ 1900 $ or higher. Those with rating $ 1899 $ or lower belong to the second division. In every contest, according to one's performance, his or her rating changes by some value, possibly negative or zero.

Limak competed in $ n $ contests in the year 2016. He remembers that in the $ i $ -th contest he competed in the division $ d_{i} $ (i.e. he belonged to this division just before the start of this contest) and his rating changed by $ c_{i} $ just after the contest. Note that negative $ c_{i} $ denotes the loss of rating.

What is the maximum possible rating Limak can have right now, after all $ n $ contests? If his rating may be arbitrarily big, print "Infinity". If there is no scenario matching the given information, print "Impossible".

## 说明/提示

In the first sample, the following scenario matches all information Limak remembers and has maximum possible final rating:

- Limak has rating $ 1901 $ and belongs to the division $ 1 $ in the first contest. His rating decreases by $ 7 $ .
- With rating $ 1894 $ Limak is in the division $ 2 $ . His rating increases by $ 5 $ .
- Limak has rating $ 1899 $ and is still in the division $ 2 $ . In the last contest of the year he gets $ +8 $ and ends the year with rating $ 1907 $ .

In the second sample, it's impossible that Limak is in the division $ 1 $ , his rating increases by $ 57 $ and after that Limak is in the division $ 2 $ in the second contest.

## 样例 #1

### 输入

```
3
-7 1
5 2
8 2
```

### 输出

```
1907
```

## 样例 #2

### 输入

```
2
57 1
22 2
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
1
-5 1
```

### 输出

```
Infinity
```

## 样例 #4

### 输入

```
4
27 2
13 1
-50 1
8 2
```

### 输出

```
1897
```

# AI分析结果



# New Year and Rating

## 题目描述

每个 Codeforces 用户都有一个评分，可以是负数、零或正数。用户分为两个组别：第一组评分不低于 1900，第二组评分不高于 1899。Limak 参加了 n 场比赛，每场赛前他所在的组别为 d_i，赛后评分变化为 c_i。求他最终可能的最高评分，若无法确定则输出 "Impossible"，若可无限大则输出 "Infinity"。

---

## 题解分析与结论

### 关键思路：动态维护区间约束
通过维护初始评分可能的上下界，逐步根据每场比赛的组别要求调整区间。初始时上下界为 [-∞, +∞]，每场比赛根据组别 d_i 调整约束条件：

1. **组别 1**（d_i=1）：当前评分 ≥1900 → 初始评分 ≥1900 - 前缀和
2. **组别 2**（d_i=2）：当前评分 ≤1899 → 初始评分 ≤1899 - 前缀和

最终根据最终约束区间判断结果：
- 若区间为空 → Impossible
- 若上界仍为 +∞ → Infinity
- 否则最大初始评分加总变化即为答案

---

## 精选题解

### 题解1：frankchenfu（5星）
**亮点**：代码简洁，区间维护逻辑清晰，完美处理所有边界条件。
```cpp
const int INF=0x7fffffff;
int lans=-INF, rans=INF, sum=0;

for(int i=1; i<=n; i++) {
    // 处理当前比赛的约束
    if(d[i]==1) lans = max(lans, 1900 - sum);
    else rans = min(rans, 1899 - sum);
    sum += c[i];
}

if(lans > rans) cout<<"Impossible";
else if(rans==INF) cout<<"Infinity";
else cout<<rans + sum;
```
**核心思想**：动态维护初始评分的可行区间，通过前缀和快速计算约束条件。

---

### 题解2：封禁用户（4星）
**亮点**：初始值设为最大整型，直观处理无穷大场景。
```cpp
int maxn=0x7fffffff, minn=0;

for(int i=1; i<=n; i++) {
    // 矛盾检测
    if((d==1 && maxn<1900) || (d==2 && minn>1899)) {
        cout<<"Impossible"; return;
    }
    // 更新区间
    if(d==1) minn = max(minn, 1900);
    else maxn = min(maxn, 1899);
    // 累加变化
    minn += c; maxn += c;
}
```
**注意点**：需确保初始化足够大，代码中直接使用 0x7fffffff 处理无穷大。

---

## 相似题目推荐
1. [CF1025B Weakened Common Divisor](https://www.luogu.com.cn/problem/CF1025B)  
   **相似点**：通过动态维护约束条件求解可行解。

2. [CF813A The Contest](https://www.luogu.com.cn/problem/CF813A)  
   **相似点**：区间约束判断可行性，处理时间窗口的交集。

3. [CF1016C Vasya And The Mushrooms](https://www.luogu.com.cn/problem/CF1016C)  
   **相似点**：动态维护路径选择的最优区间，需处理变化累积效应。

---
处理用时：202.59秒