# 题目信息

# Set To Max (Hard Version)

## 题目描述

This is the hard version of the problem. The only differences between the two versions of this problem are the constraints on $ n $ and the time limit. You can make hacks only if all versions of the problem are solved.

You are given two arrays $ a $ and $ b $ of length $ n $ .

You can perform the following operation some (possibly zero) times:

1. choose $ l $ and $ r $ such that $ 1 \leq l \leq r \leq n $ .
2. let $ x=\max(a_l,a_{l+1},\ldots,a_r) $ .
3. for all $ l \leq i \leq r $ , set $ a_i := x $ .

Determine if you can make array $ a $ equal to array $ b $ .

## 说明/提示

In the first test case, we can achieve array $ b $ by applying a single operation: $ (l,r)=(2,3) $ .

In the second test case, it can be shown we cannot achieve array $ b $ in any amount of operations.

In the third test case, we can achieve array $ b $ by applying two operations: $ (l,r)=(2,5) $ . followed by $ (l,r)=(1,3) $ .

In the fourth and fifth test cases, it can be shown we cannot achieve array $ b $ in any amount of operations.

## 样例 #1

### 输入

```
5
5
1 2 3 2 4
1 3 3 2 4
5
3 4 2 2 4
3 4 3 4 4
5
3 2 1 1 1
3 3 3 2 2
2
1 1
1 2
3
1 1 2
2 1 2```

### 输出

```
YES
NO
YES
NO
NO```

# AI分析结果



### 唯一算法分类
贪心 + 数据结构优化

---

### 题解思路与解决难点

#### 核心思路
所有题解的核心逻辑是：
1. **初步判断**：若存在 `a[i] > b[i]` 则无解。
2. **寻找覆盖源**：对于每个 `b[i]`，找到左右最近的 `a[j] = b[i]`（称为左源和右源）。
3. **区间合法性验证**：
   - **最大值约束**：在候选区间内，`a` 的最大值必须等于 `b[i]`（否则无法通过操作生成该值）。
   - **最小值约束**：在候选区间内，`b` 的最小值必须不小于 `b[i]`（否则后续无法还原更小的 `b[k]`）。

#### 数据结构对比
| 题解作者       | 数据结构           | 时间复杂度   | 实现难点                     |
|----------------|--------------------|-------------|------------------------------|
| huangrenheluogu | 线段树             | O(n log n)  | 维护区间最大/最小值          |
| wangshi         | ST表              | O(n log n)  | 预处理区间最值               |
| Diaоsi          | 树状数组 + ODT    | O(n log n)  | 区间推平操作的模拟           |
| Natori          | 单调栈 + 动态维护 | O(n)        | 贪心策略的单调性维护         |

---

### 题解评分（≥4星）

1. **huangrenheluogu（5星）**
   - **思路清晰**：通过左右双向扫描 + 线段树验证，逻辑严密。
   - **代码可读性**：线段树模板化实现，结构清晰。
   - **优化程度**：严格满足时间复杂度要求。

2. **wangshi（4星）**
   - **思路亮点**：使用 ST表预处理，减少代码量。
   - **实现简洁性**：通过预处理 `pre` 和 `nxt` 数组快速定位候选区间。
   - **局限性**：需要额外处理 `pre` 和 `nxt` 的初始化逻辑。

3. **MaxBlazeResFire（4星）**
   - **技巧创新**：结合 `set` 和 ST表，实现高效区间查询。
   - **代码简洁性**：利用 `upper_bound` 和 `lower_bound` 快速定位候选位置。
   - **实践性**：适合竞赛场景的快速实现。

---

### 最优思路与技巧

1. **双向扫描 + 区间约束验证**
   - **左源右源定位**：通过预处理或动态维护，快速找到每个 `b[i]` 的左右最近源。
   - **区间合法性检查**：
     ```cpp
     // 左源区间检查
     if (query_max(left_source, i) == b[i] && 
         query_min_b(left_source, i) >= b[i]) 
         valid = true;
     // 右源区间检查同理
     ```

2. **数据结构选择**
   - **线段树**：灵活支持动态区间查询（适用于需要动态更新的场景）。
   - **ST表**：静态区间最值查询的极优选择，预处理后查询 O(1)。

---

### 类似题目推荐

1. **CF1321C (Remove Adjacent)**
   - 贪心删除字符，需动态维护相邻关系。

2. **CF1547E (Air Conditioners)**
   - 左右双向扫描确定最近温度源。

3. **Luogu P1972 (HH的项链)**
   - 区间查询与离线处理，结合树状数组优化。

---

### 可视化与算法演示

#### 动画设计
1. **像素风格界面**：
   - **数组展示**：每个元素用 16x16 像素块表示，颜色编码值大小。
   - **当前操作高亮**：处理 `i` 时，用闪烁边框标记 `i`，左/右源用红/蓝框标记。

2. **关键步骤演示**：
   - **步骤1**：检查 `a[i] > b[i]`，若存在则播放爆炸音效并终止。
   - **步骤2**：左右滑动扫描，动态绘制候选区间。
   - **步骤3**：区间合法性检查时，用绿色覆盖合法区间，红色标记非法区域。

3. **交互控制**：
   ```javascript
   // 伪代码示例
   function animateStep(i) {
       highlight(i);
       let left = findLeftSource(i);
       let right = findRightSource(i);
       drawInterval(left, i, 'red');
       drawInterval(i, right, 'blue');
       if (validate(left, i)) flashGreen();
       else if (validate(i, right)) flashGreen();
       else playFailureSound();
   }
   ```

#### 复古音效
- **音效类型**：8-bit 风格音效库。
- **触发逻辑**：
  - **成功**：高音“叮”。
  - **失败**：低音“哔”。
  - **背景音乐**：循环播放 FC 风格背景音乐。

---

### 题解代码片段（huangrenheluogu）

**核心逻辑：线段树验证**
```cpp
// 线段树查询区间最大值和最小值
int querymax(int l, int r) { /* ... */ }
int querymin(int l, int r) { /* ... */ }

void solve() {
    for (int i = 1; i <= n; i++) {
        // 左源检查
        if (las[b[i]] && 
            querymin(las[b[i]], i) >= b[i] && 
            querymax(las[b[i]], i) <= b[i]) 
            ans[i] = 1;
        // 右源检查同理
    }
}
```

---

### 个人心得摘录

- **huangrenheluogu**：  
  *“线段树的区间查询必须严格覆盖目标区间，否则会漏判边界情况。”*

- **Diaоsi**：  
  *“ODT 的区间推平操作虽然暴力，但在有序覆盖场景下复杂度有保障。”*

---
处理用时：82.30秒