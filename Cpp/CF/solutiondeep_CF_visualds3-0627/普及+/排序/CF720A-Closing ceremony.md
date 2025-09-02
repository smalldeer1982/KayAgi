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



## 算法分类
**贪心算法**

---

## 题解思路与解决难点

### 核心思路
- **问题拆解**：将座位分为两个视角——左边队列（入口 (0,0)）和右边队列（入口 (0,m+1)）。左边队列的人需满足座位到 (0,0) 的曼哈顿距离 ≤ 其耐力，右边同理。
- **贪心策略**：
  1. **左边队列处理**：按耐力升序排序，每次选择当前能到达的座位中到右边入口最远（即对右边队列影响最大的座位）。
  2. **右边队列处理**：剩余座位按到右边入口的距离排序，按耐力升序匹配是否满足条件。

### 关键难点
1. **高效选择最优座位**：左边队列需快速找到耐力范围内且对右边队列最不利的座位，需动态维护区间最大值。
2. **数据结构优化**：使用线段树或优先队列维护可选的座位集合，避免暴力遍历。

### 解决方案
- **线段树维护区间最大值**：预处理所有座位按左边入口距离排序，线段树维护每个区间的最大右边入口距离，快速查询和更新。
- **双指针匹配剩余座位**：处理完左边后，剩余座位按右边距离排序，与右边队列的耐力升序逐一匹配。

---

## 题解评分（≥4星）

### 1. 作者：iodwad（★★★★★）
- **亮点**：线段树高效维护区间最大值，时间复杂度 O(nm log nm)，逻辑清晰。
- **核心代码**：
  ```cpp
  // 预处理座位并按左边距离排序
  for (int i = 1; i <= n; ++i) 
      for (int j = 1; j <= m; ++j) 
          p[++tot] = {i + j, i + (m + 1 - j)};
  sort(p + 1, p + 1 + tot);
  
  // 线段树查询并更新最大值
  int l = find(a[i]); // 找到耐力允许的最大左边距离
  auto res = query(root, 1, tot, 1, l);
  modify(root, 1, tot, res.second, -1); // 标记已选
  ```

### 2. 作者：hjqhs（★★★★）
- **亮点**：利用 `lower_bound` 快速匹配，代码简洁。
- **核心代码**：
  ```cpp
  per(i, n, 1) rep(j, 1, m) {
      auto p = lower_bound(all(a), i + j);
      auto q = lower_bound(all(b), i + (m + 1 - j));
      if (p != a.end()) a.erase(p);
      else if (q != b.end()) b.erase(q);
      else return NO;
  }
  ```

### 3. 作者：RainFestival（★★★★）
- **亮点**：优先队列动态维护可用座位，逻辑直观。
- **核心代码**：
  ```cpp
  // 预处理每个距离的座位集合
  for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j) {
          s1[dist(i, j, 0, 0)].push_back({i, j});
          s2[dist(i, j, 0, m + 1)].push_back({i, j});
      }
  
  // 优先队列维护最大右边距离
  priority_queue<pair<int, pair<int, int>>> pq;
  for (auto seat : s1[d]) 
      pq.push({seat到右边的距离, seat});
  ```

---

## 最优思路提炼
1. **贪心方向**：左边队列优先占据对右边队列最不利的座位（即右边距离最大）。
2. **数据结构**：线段树或优先队列动态维护最大值，避免重复遍历。
3. **排序策略**：两个队列均按耐力升序处理，确保小耐力优先匹配。

---

## 类似题目推荐
1. **P1896 [SCOI2005] 互不侵犯**（状态压缩+贪心布局）
2. **P2870 [USACO07DEC] Best Cow Line G**（双端队列贪心）
3. **P1094 [NOIP2007 普及组] 纪念品分组**（双指针贪心匹配）

---

## 可视化设计
### 核心流程动画
1. **网格绘制**：Canvas 绘制 n×m 网格，每个格子显示到两入口的距离。
2. **颜色标记**：
   - 红色：当前处理的左边队列座位。
   - 蓝色：右边队列待选座位。
   - 绿色：已分配座位。
3. **步进控制**：单步显示线段树查询最大值过程，高亮当前操作的区间和座位。

### 复古像素风格
- **调色板**：16色，红（#FF0000）、蓝（#0000FF）、绿（#00FF00）等。
- **音效**：
  - 分配座位时播放 8-bit “哔”声。
  - 失败时播放低沉音效，成功时播放胜利旋律。

---

## 核心代码片段（iodwad）
```cpp
// 预处理座位并排序
int tot = 0;
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {  
        p[++tot] = {i + j, i + (m + 1 - j)};
    }
}
sort(p + 1, p + 1 + tot);

// 线段树查询最大值
for (int i = 1; i <= k; ++i) {
    int l = find(a[i]); // 二分找到耐力允许的最大左边距离
    auto res = query(root, 1, tot, 1, l);
    if (res.first == -1) return NO;
    modify(root, 1, tot, res.second, -1); // 标记为已选
}
```

---
处理用时：93.95秒