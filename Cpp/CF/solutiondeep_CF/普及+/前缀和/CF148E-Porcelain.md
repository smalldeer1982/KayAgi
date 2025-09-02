# 题目信息

# Porcelain

## 题目描述

During her tantrums the princess usually smashes some collectable porcelain. Every furious shriek is accompanied with one item smashed.

The collection of porcelain is arranged neatly on $ n $ shelves. Within each shelf the items are placed in one row, so that one can access only the outermost items — the leftmost or the rightmost item, not the ones in the middle of the shelf. Once an item is taken, the next item on that side of the shelf can be accessed (see example). Once an item is taken, it can't be returned to the shelves.

You are given the values of all items. Your task is to find the maximal damage the princess' tantrum of $ m $ shrieks can inflict on the collection of porcelain.

## 说明/提示

In the first case there are two shelves, each with three items. To maximize the total value of the items chosen, one can take two items from the left side of the first shelf and one item from the right side of the second shelf.

In the second case there is only one shelf, so all three items are taken from it — two from the left side and one from the right side.

## 样例 #1

### 输入

```
2 3
3 3 7 2
3 4 1 5
```

### 输出

```
15
```

## 样例 #2

### 输入

```
1 3
4 4 3 1 2
```

### 输出

```
9
```

# AI分析结果



# Porcelain

## 题目描述

公主发脾气时会摔碎收藏的瓷器。每次尖叫会伴随摔碎一个物品。瓷器被整齐摆放在 $n$ 个架子上，每个架子的物品排成一行，每次只能取最左侧或最右侧的物品（取走后该侧的下一个物品变为可访问）。给定所有物品的价值，求 $m$ 次摔砸能造成的最大总价值。

## 输入样例 #1

```
2 3
3 3 7 2
3 4 1 5
```

## 输出样例 #1

```
15
```

## 输入样例 #2

```
1 3
4 4 3 1 2
```

## 输出样例 #2

```
9
```

---

### 综合分析与结论
各题解均采用**分组背包**框架，核心思路分两步：
1. **预处理单层最优**：计算每层取 $k$ 个物品的最大价值
2. **组合多层结果**：将每层视为物品组，用背包问题合并结果

#### 关键优化技巧
- **前缀和加速计算**：快速获取左取 $l$ 个、右取 $r$ 个的价值和
- **空间优化**：通过滚动数组或倒序枚举降低空间复杂度
- **边界处理**：处理右端索引时的数组越界问题

---

### 高分题解推荐

#### 1. 作者：wanggiaoxing（⭐⭐⭐⭐⭐）
**核心亮点**  
- 代码简洁，直接使用二维数组存储单层预处理结果
- 分组背包转移逻辑清晰，循环边界处理明确
- 包含边界条件注释，可读性强

**关键代码**  
```cpp
// 预处理单层最优
for(int j=1;j<=k;j++)
    for(int l=0;l<=j;l++) {
        int r = k - (j-l);
        dp1[i][j] = max(dp1[i][j], sum[i][l] + sum[i][k] - sum[i][r]);
    }

// 分组背包转移
for(int i=1;i<=n;i++)
    for(int k=0;k<=m;k++)
        for(int j=0;j<=q[i];j++)
            if(k>=j) dp[i][k] = max(dp[i][k], dp[i-1][k-j]+dp1[i][j]);
```

#### 2. 作者：jdsb（⭐⭐⭐⭐）
**核心亮点**  
- 使用滚动数组优化空间至一维
- 函数化计算单层价值，提升代码复用性
- 倒序枚举容量避免覆盖旧状态

**关键代码**  
```cpp
// 滚动数组优化
for(int i=1;i<=n;i++)
    for(int j=m;j>=1;j--)
        for(int k=0;k<=min(num[i],j);k++)
            dp[j] = max(dp[j], dp[j-k]+f[i][k]);
```

#### 3. 作者：_lxy_（⭐⭐⭐⭐）
**核心亮点**  
- 独立计算前后缀数组，逻辑更直观
- 使用三层循环枚举左右取物组合
- 代码结构模块化，方便调试

**关键代码**  
```cpp
// 预处理前后缀
for(int l=0;l<=k[i];l++)
    for(int r=0;l+r<=k[i];r++)
        f[i][l+r] = max(f[i][l+r], pre[i][l]+suf[i][k[i]-r+1]);
```

---

### 举一反三
1. **预处理子问题思想**：适用于需要分层处理的最优化问题（如[P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)）
2. **分组背包变种**：物品分组且每组只能选一种类型时使用（如[P2014 选课](https://www.luogu.com.cn/problem/P2014)）
3. **双端取物模型**：可拓展到环形取物（如[P1880 石子合并](https://www.luogu.com.cn/problem/P1880)）

---

### 调试经验摘录
- **转移顺序陷阱**：倒序枚举容量时若忘记从大到小循环，会导致同一层多次使用（@_Album_）
- **索引计算错误**：计算右端点时未考虑数组偏移量导致越界（@E1_de5truct0r）
- **初始化遗漏**：未清空滚动数组导致上一组数据残留（@jdsb）

---
处理用时：52.23秒