# 题目信息

# Permutation Restoration

## 题目描述

Monocarp 有一个长度为 $n$ ，由 $1$ ~ $n$ 构成的数组  $a$ ，其中每个元素在 $a$ 中出现且仅出现 $1$ 次。

现在 Monocarp 计算一个数组 $b$ ，使得 $b_i=\lfloor\frac{i}{a_i}\rfloor$ 。

现在给出 $b$ 数组，要求求出任意一组 $a$ 。

注意：保证对于所给出的 $b$ 至少有一组 $a$ 与之对应。

## 样例 #1

### 输入

```
4
4
0 2 0 1
2
1 1
5
0 0 1 4 1
3
0 1 3```

### 输出

```
2 1 4 3 
1 2 
3 4 2 1 5 
3 2 1```

# AI分析结果



### 题解思路与算法要点

**核心贪心策略**  
题目要求根据给定的数组 $b$ 重构排列 $a$。通过分析 $b_i = \lfloor \frac{i}{a_i} \rfloor$，可推导出每个 $a_i$ 的取值区间：  
$$ \frac{i}{b_i+1} < a_i \le \frac{i}{b_i} \quad \text{（若 } b_i=0 \text{，则 } a_i \in (i, n] \text{）} $$  
贪心思路：将每个区间按左端点排序，每次选择右端点最小的区间，以最大化后续选择空间。使用优先队列维护当前可选的区间。

**算法实现步骤**  
1. **预处理区间**：对每个 $i$，计算 $a_i$ 的左右端点 $l_i$ 和 $r_i$。  
2. **排序与堆管理**：将所有区间按左端点排序，遍历时动态将左端点等于当前值的区间加入优先队列（按右端点排序）。  
3. **贪心选择**：每次从队列中取出右端点最小的区间，分配当前值 $i$ 作为对应的 $a_i$。

**解决难点**  
- **区间推导**：需准确处理 $b_i=0$ 的特殊情况，避免计算错误。  
- **高效选择**：通过堆维护候选区间，保证每次选择最优解的复杂度为 $O(n \log n)$。

---

### 题解评分（≥4星）

1. **Morax_（5星）**  
   - **亮点**：代码结构清晰，预处理与堆操作分离，多组数据清空处理完善。  
   - **代码可读性**：结构体排序和优先队列的结合直观易懂。  
   - **核心代码**：  
     ```cpp
     for (int i = 1; i <= n; ++i) {
         while (cnt <= n && k[cnt].l == i) {
             Q.push({b[id] == 0 ? n : id / b[id], id});
             cnt++;
         }
         a[Q.top().second] = i;
         Q.pop();
     }
     ```

2. **intel_core（4星）**  
   - **亮点**：使用 `vector` 动态存储区间，逻辑简洁。  
   - **代码优化**：直接按左端点分组，避免重复排序。  
   - **核心代码**：  
     ```cpp
     for (int i = 1; i <= n; i++) {
         for (int x : v[i]) q.push({r[x], x});
         a[q.top().second] = i;
         q.pop();
     }
     ```

3. **roumeideclown（4星）**  
   - **亮点**：代码简洁，使用 `set` 替代堆，支持动态插入和删除。  
   - **代码片段**：  
     ```cpp
     set<pii> t;
     for (int i = 1; i <= n; i++) {
         for (auto j : tt[i]) t.emplace(r[j], j);
         ans[t.begin()->second] = i;
         t.erase(t.begin());
     }
     ```

---

### 最优思路提炼

**关键贪心策略**  
- **区间排序**：按左端点排序，保证按顺序处理区间。  
- **右端点优先队列**：动态维护当前可选的区间，每次选择右端点最小的，确保后续有更多选择空间。  

**实现技巧**  
1. **特殊值处理**：当 $b_i=0$ 时，$a_i$ 的右端点固定为 $n$。  
2. **多组数据清空**：优先队列和存储结构需在每组数据前清空。  

---

### 同类型题目与算法套路

**通用贪心思路**  
- **区间调度问题**：如选择不重叠区间使数量最多（按右端点排序）。  
- **任务分配**：如将任务分配到时间槽，优先处理结束时间早的任务。  

**推荐题目**  
1. **洛谷 P1803**：线段覆盖，选择最多不重叠区间。  
2. **CF 1029C**：区间交集最大化，需处理区间端点。  
3. **LeetCode 435**：无重叠区间，贪心删除最少区间。  

---

### 可视化与算法演示

**动画设计**  
1. **像素风格界面**：用色块表示区间，当前处理的位置高亮为红色。  
2. **堆操作可视化**：候选区间显示为绿色，选中区间变为黄色并分配值。  
3. **音效反馈**：  
   - **加入堆**：短促“滴”声。  
   - **选中分配**：上扬音调。  

**交互功能**  
- **步进控制**：支持暂停/继续，调整动画速度。  
- **自动演示**：AI 模式自动执行，展示贪心策略全过程。  

**Canvas 示例**  
```javascript
// 伪代码：绘制区间和当前选择
function drawStep(i) {
    ctx.clearRect(0, 0, width, height);
    // 绘制所有区间
    intervals.forEach(interval => {
        drawRect(interval.l, interval.r, 'green');
    });
    // 高亮当前处理的i
    drawRect(i, i, 'red');
    // 绘制堆中的候选区间
    heap.forEach(interval => {
        drawRect(interval.l, interval.r, 'blue');
    });
}
```

---

### 代码实现（Morax_ 题解核心）

```cpp
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

struct Node { int l, i; } k[500005];
int b[500005], a[500005];

bool cmp(Node x, Node y) { return x.l < y.l; }

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &b[i]);
            k[i] = {i / (b[i] + 1) + 1, i};
        }
        sort(k + 1, k + n + 1, cmp);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
        int cnt = 1;
        for (int i = 1; i <= n; ++i) {
            while (cnt <= n && k[cnt].l == i) {
                int id = k[cnt].i;
                Q.push({b[id] ? id / b[id] : n, id});
                cnt++;
            }
            a[Q.top().second] = i;
            Q.pop();
        }
        for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
        printf("\n");
    }
}
```

---

**总结**：通过贪心策略和优先队列高效实现区间选择，确保每次决策的局部最优性，最终得到全局合法解。

---
处理用时：108.30秒