# 题目信息

# Lazyland

## 题目描述

The kingdom of Lazyland is the home to $ n $ idlers. These idlers are incredibly lazy and create many problems to their ruler, the mighty King of Lazyland.

Today $ k $ important jobs for the kingdom ( $ k \le n $ ) should be performed. Every job should be done by one person and every person can do at most one job. The King allowed every idler to choose one job they wanted to do and the $ i $ -th idler has chosen the job $ a_i $ .

Unfortunately, some jobs may not be chosen by anyone, so the King has to persuade some idlers to choose another job. The King knows that it takes $ b_i $ minutes to persuade the $ i $ -th idler. He asked his minister of labour to calculate the minimum total time he needs to spend persuading the idlers to get all the jobs done. Can you help him?

## 说明/提示

In the first example the optimal plan is to persuade idlers 1, 6, and 8 to do jobs 2, 4, and 6.

In the second example each job was chosen by some idler, so there is no need to persuade anyone.

## 样例 #1

### 输入

```
8 7
1 1 3 1 5 3 7 1
5 7 4 8 1 3 5 2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 3
3 1 2
5 3 4
```

### 输出

```
0
```

# AI分析结果



### 题解思路、算法要点与解决难点

#### 核心贪心策略
- **核心思路**：优先选择说服时间最小的多余人员，确保每个工作至少有一人完成。
- **关键推导**：每个工作若被多选，只需保留一人，其余人转为填充未被覆盖的工作。最优解是说服每个工作中多余且说服时间最小的人员。
- **数据结构**：使用桶（数组）统计每个工作的选择次数，排序数组快速筛选最小成本。

#### 解决难点对比
1. **Molina/lbh666**：
   - **桶统计**：记录每个工作被选次数，初始遍历统计已覆盖工作数。
   - **排序策略**：按说服时间升序排列，贪心选择最小成本的冗余人员。
   - **动态调整**：遍历排序后数组，逐个选择可说服的人员，实时更新桶计数和剩余需填充工作数。
   - **优势**：代码直观，动态调整过程清晰。

2. **A524/ran_qwq**：
   - **保留最大值**：每个工作保留说服时间最大的成员，其余加入候选数组。
   - **静态筛选**：候选数组排序后取前 $k-s$ 个最小值（$s$ 为初始覆盖工作数）。
   - **优势**：避免重复遍历，代码更简洁，时间复杂度稳定。

### 题解评分（≥4星）

#### 4星题解
1. **Molina**（4星）
   - **亮点**：思路清晰，代码注释详细，动态调整桶计数逻辑易于理解。
   - **代码可读性**：结构体排序与桶统计结合，流程明确。
   - **优化点**：直接遍历排序数组，实时处理剩余工作数。

2. **ran_qwq**（4星）
   - **亮点**：代码简洁高效，预处理每个工作的最大值，避免动态调整。
   - **实现技巧**：利用 `vector` 分组排序，快速提取候选集。
   - **优势**：时间复杂度稳定，适合大规模数据。

3. **A524**（4星）
   - **亮点**：逆向思维保留最大值，预处理后直接排序候选集。
   - **代码简洁性**：变量命名稍简，但核心逻辑突出，适合快速实现。

### 最优思路与技巧提炼

#### 关键贪心技巧
1. **保留最大值策略**：每个工作保留说服时间最大的成员，确保剩余候选集说服时间总和最小。
2. **最小堆思想**：通过排序候选集，快速筛选前 $k-s$ 个最小说服时间。

#### 实现细节
- **桶统计**：统计每个工作被选次数，初始遍历确定未覆盖工作数。
- **排序方向**：按说服时间升序（Molina）或降序（A524）决定处理顺序。

### 同类型题与算法套路

#### 常见贪心应用
- **区间调度**：选择不重叠区间使数量最多（按结束时间排序）。
- **最小生成树**：Kruskal 算法选择最小边。
- **任务分配**：最小化等待时间或总成本。

### 推荐相似题目
1. **P1209** [修理牛棚](https://www.luogu.com.cn/problem/P1209)（区间覆盖与贪心）
2. **P1090** [合并果子](https://www.luogu.com.cn/problem/P1090)（最小堆贪心）
3. **P4995** [跳跳！](https://www.luogu.com.cn/problem/P4995)（排序与交替选择）

### 个人心得摘录
- **Molina**：强调初始桶统计与动态调整的平衡，避免复杂预处理。
- **A524**：通过逆向保留最大值简化问题，代码短小但高效。
- **ran_qwq**：分组排序提升效率，避免冗余遍历。

---

### 可视化与算法演示（核心贪心过程）

#### 动画方案
1. **桶填充与颜色标记**：
   - 初始显示所有工作桶，不同颜色区分覆盖状态。
   - 高亮当前处理的说服人员，显示其所属工作桶的剩余容量。

2. **贪心选择动态**：
   - 排序数组以流动条形图展示，当前选中项闪烁。
   - 说服操作后，对应工作桶计数减一，未覆盖工作数同步更新。

3. **复古像素风格**：
   - **Canvas 网格**：每个工作以像素块表示，颜色深浅反映被选次数。
   - **音效**：说服成功时播放8-bit音效，背景音乐循环。

#### 交互设计
- **步进控制**：支持暂停/继续，调整动画速度。
- **自动演示**：AI模式按最优策略自动执行，辅以音效提示。

---

### 题解代码精选（核心逻辑）

#### Molina 题解（关键代码）
```cpp
sort(a+1, a+n+1, cmp); // 按说服时间升序排序
for (int i=1; i<=n; i++) {
    if (ton[a[i].x] >= 2) { // 可说服
        ans += a[i].y;
        ton[a[i].x]--;
        k--;
    }
    if (k == 0) break;
}
```

#### ran_qwq 题解（关键代码）
```cpp
for (int i=1; i<=m; i++) {
    sort(v[i].begin(), v[i].end(), greater<int>()); // 降序排序
    for (int j=1; j<v[i].size(); j++)
        p[++len] = v[i][j]; // 保留最大值，其余加入候选
}
sort(p+1, p+1+len); // 升序取前k-s个
for (int i=1; i<=k; i++) ans += p[i];
```

---

### 可视化代码片段（复古风格）
```javascript
// Canvas 绘制工作桶
function drawBuckets() {
    ctx.fillStyle = "#8B0000"; // 暗红色背景
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    buckets.forEach((count, idx) => {
        ctx.fillStyle = count > 0 ? "#00FF00" : "#FF0000"; // 绿：已覆盖，红：未覆盖
        ctx.fillRect(idx * 20, 100 - count * 10, 18, count * 10);
    });
}
// 说服动画
function animatePersuade(person) {
    person.element.classList.add("highlight"); // 高亮当前人员
    playSound("select"); // 8-bit 音效
    setTimeout(() => {
        person.element.classList.remove("highlight");
        updateBucket(person.job); // 更新桶计数
    }, 500);
}
```

---
处理用时：143.62秒