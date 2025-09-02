# 题目信息

# Closing ceremony

## 题目描述

The closing ceremony of Squanch Code Cup is held in the big hall with $ n×m $ seats, arranged in $ n $ rows, $ m $ seats in a row. Each seat has two coordinates $ (x,y) $ ( $ 1<=x<=n $ , $ 1<=y<=m $ ).

There are two queues of people waiting to enter the hall: $ k $ people are standing at $ (0,0) $ and $ n·m-k $ people are standing at $ (0,m+1) $ . Each person should have a ticket for a specific seat. If person $ p $ at $ (x,y) $ has ticket for seat $ (x_{p},y_{p}) $ then he should walk $ |x-x_{p}|+|y-y_{p}| $ to get to his seat.

Each person has a stamina — the maximum distance, that the person agrees to walk. You should find out if this is possible to distribute all $ n·m $ tickets in such a way that each person has enough stamina to get to their seat.

## 样例 #1

### 输入

```
2 2
3 3 3 2
1 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2 2
3 2 3 3
1 2
```

### 输出

```
NO
```

# AI分析结果



### 中文重写题目

#### 题目描述

闭幕式大厅有 $n×m$ 个座位，排成 $n$行，每行 $m$ 个。每个座位坐标 $(x,y)$（$1≤x≤n$, $1≤y≤m$）。两队人等待入场：$k$ 人位于 $(0,0)$，$n·m−k$ 人位于 $(0,m+1)$。每人需走到指定座位，行走距离为曼哈顿距离。判断是否存在一种票分配方案，使所有人的行走距离不超过其耐力值。

---

### 题解综合分析

#### 关键思路总结
1. **双队列贪心策略**：将两队分别排序，按耐力从小到大处理。
2. **交叉影响处理**：优先让左边队列占据对右边队列最不利的座位（即离右边门最远的座位）。
3. **数据结构优化**：用线段树/优先队列动态维护可选座位的最大距离，实现高效查询。

#### 优质题解推荐

**题解作者：iodwad（★★★★★）**  
**核心亮点**：  
- 将座位预处理为到右侧门的距离并排序，利用线段树维护最大值。  
- 左边队列按耐力升序处理，每次贪心取最大可用距离的座位。  
- 剩余座位再次排序后与右侧队列耐力值直接比较。  

**代码核心**：
```cpp
// 预处理所有座位到右侧门的距离并排序
for (int i = 1; i <= n; ++i) 
    for (int j = 1; j <= m; ++j)  
        p[++tot] = std::make_pair(i + j, m + 1 - j + i);
std::sort(p + 1, p + 1 + tot);
build(root, 1, tot); // 线段树建树

// 处理左侧队列
std::sort(a + 1, a + 1 + k);
for (int i = 1; i <= k; ++i) {
    int l = find(a[i]); // 二分找最大可用区间
    auto res = query(root, 1, tot, 1, l); // 查询区间最大
    modify(root, 1, tot, res.second, -1); // 标记已选
}

// 检查右侧队列
std::sort(b + 1, b + 1 + n * m - k);
for (int i = 1; i <= n * m - k; ++i) 
    if (a[i] > b[i]) return puts("NO");
```

---

### 拓展与总结

**同类问题套路**：  
- **双队列贪心**：当两组决策存在交叉影响时，优先处理对后续限制更严格的一方。  
- **距离最优化维护**：利用线段树/堆维护动态集合极值。  

**推荐练习题**：  
1. [P2893 道路修建](https://www.luogu.com.cn/problem/P2893)（坐标距离处理）  
2. [CF538B Quasi Binary](https://codeforces.com/problemset/problem/538/B)（双队列贪心）  
3. [P1849 障碍物赛跑](https://www.luogu.com.cn/problem/P1849)（动态极值维护）  

**调试心得摘录**：  
- 作者 **Seanq** 提到暴力枚举时需注意时间效率，实际比赛需优化。  
- 作者 **幻影星坚强** 强调预处理时坐标顺序易错，需仔细验证。  
- 作者 **iodwad** 使用线段树替代暴力查询，大幅降低复杂度。

---
处理用时：48.16秒