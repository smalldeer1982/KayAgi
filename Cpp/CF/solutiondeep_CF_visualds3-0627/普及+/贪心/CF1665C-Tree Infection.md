# 题目信息

# Tree Infection

## 题目描述

### 题意描述
一个树是一个无环连通图。一个有根树有一个被称作“根结点”的结点。对于任意一个非根结点 $v$ ，其父结点是从根结点到结点 $v$ 最短路径上的前一个结点。结点 $v$ 的子结点包括所有以 $v$ 父结点为 $v$ 的结点。

给定一个有 $n$ 个结点的有根树。结点 $1$ 即为根结点。一开始，该树上所有结点均是“健康”的。

每一秒你会进行两次操作——先是传播操作，然后是注射操作，定义如下。

- 传播操作：对于每个结点 $v$ ，若该结点至少有一个子结点被“感染”，则你可以“感染”顶点 $v$ 任意一个其他的子结点。
- 注射：你可以选择任意一个“健康”的结点并使它变为“感染”状态。

这程每秒会重复一次知道整个树的结点都处于“感染”状态。你需要找到使整个树被“感染”的最短时间（秒数）。

## 说明/提示

- $ 1 \le t \le 10^4 $
- $ 2 \le n \le 2 \times 10^5 $
- $ 1 \le p_i \le n $
- $ \sum \limits_{i=1} ^t n_i \le 2 \times 10^5 $

## 样例 #1

### 输入

```
5
7
1 1 1 2 2 4
5
5 5 1 4
2
1
3
3 1
6
1 1 1 1 1```

### 输出

```
4
4
2
3
4```

# AI分析结果



### 综合分析与结论

**核心思路**：  
题目关键在于将每个节点的子节点视为独立集合，通过贪心策略优先处理较大的集合。初始注射确保每个父节点至少有一个子节点被感染，触发传播机制。剩余子节点数目用优先队列维护，每次选择最大的进行注射，直至所有剩余数目可被自动传播覆盖。

**贪心策略验证**：  
- **正确性**：每次处理当前最大剩余数目，确保该集合不会成为时间瓶颈。交换论证证明优先处理较大集合不会更差。
- **时间复杂度**：O(n log n)，适用于题目约束。

**可视化设计思路**：  
- **动画方案**：展示树结构，高亮当前处理节点的子节点集合。优先队列动态显示，每次弹出最大元素并更新。
- **颜色标记**：红色标记当前处理的节点，绿色表示已感染，黄色表示传播感染。
- **复古像素风格**：用8-bit方块表示子节点数目，音效提示注射与传播操作。

---

### 题解清单（≥4星）

1. **作者：tzyt（5星）**  
   - **亮点**：详细注释，清晰思路，优先队列动态处理剩余数目。正确计算初始处理时间，贪心策略高效。
   - **关键代码**：优先队列维护 `siz[i] - (i - fir_n_zero) - 1`，动态调整剩余数目。

2. **作者：听取MLE声一片（4星）**  
   - **亮点**：简洁实现，正确使用优先队列。通过计数器模拟传播时间，代码直观。
   - **个人心得**：处理最大剩余数目避免 `wa on 6` 的测试用例。

3. **作者：jiangtaizhe001（4星）**  
   - **亮点**：代码精简，变量命名合理。通过懒惰标记优化传播计算，逻辑清晰。
   - **核心片段**：`priority_queue` 处理 `son[i] - cnt`，动态更新。

---

### 最优思路与技巧

1. **贪心选择依据**：  
   - 初始注射每个父节点的一个子节点，确保传播可用。
   - 剩余数目排序后，优先队列维护当前最大值，每秒注射最大项。

2. **关键实现细节**：  
   ```cpp
   priority_queue<int> pq;
   for (int i = fir_n_zero; i <= n; i++) {
       pq.push(siz[i] - (i - fir_n_zero) - 1);
   }
   while (pq.top() > spreaded) {
       spreaded++;
       int tp = pq.top(); pq.pop();
       pq.push(tp - 1);
       tm_used++;
   }
   ```
   - **解释**：`siz[i] - (i - fir_n_zero) - 1` 表示初始注射后的剩余数目，动态调整。

---

### 同类型题目与算法套路

- **常见场景**：任务调度、资源分配、最大收益选择。
- **通用解法**：优先队列处理动态最大值，排序后贪心。
- **推荐题目**：  
  1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)（排序策略）  
  2. [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)（处理顺序）  
  3. [P2949 工作调度](https://www.luogu.com.cn/problem/P2949)（优先队列）

---

### 个人心得摘录

- **tzyt**：初始处理顺序影响总时间，先处理大集合避免后续瓶颈。
- **听取MLE声一片**：直接按大小排序会导致次大集合被忽略，需动态调整。

---

### 可视化与算法演示（伪代码）

```javascript
// 初始化Canvas
const canvas = document.getElementById('visualization');
const ctx = canvas.getContext('2d');
let nodes = [5, 3, 7, 2]; // 示例剩余数目

function drawNodes() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    nodes.forEach((size, index) => {
        ctx.fillStyle = size === Math.max(...nodes) ? '#ff0000' : '#00ff00';
        ctx.fillRect(index * 50, 50, 40, size * 10);
    });
}

function simulateStep() {
    if (nodes.length === 0) return;
    let maxIndex = nodes.indexOf(Math.max(...nodes));
    nodes[maxIndex] -= 1;
    drawNodes();
    playSound('click'); // 播放音效
}

// 自动演示
setInterval(simulateStep, 1000);
```

**复古风格设计**：  
- **8-bit方块**：红色表示当前处理节点，绿色为其余。
- **音效**：点击声提示注射，背景音乐循环播放芯片音乐。

---

### 代码实现（核心贪心逻辑）

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
int siz[MAXN], t;

int main() {
    scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        memset(siz, 0, sizeof(siz));
        for (int i = 1; i < n; i++) {
            int fa; scanf("%d", &fa);
            siz[fa]++;
        }
        siz[0] = 1;
        sort(siz, siz + n + 1);
        int fir = find_if(siz, siz+n+1, [](int x){return x!=0;}) - siz;

        priority_queue<int> pq;
        for (int i = fir; i <= n; i++) 
            pq.push(siz[i] - (i - fir) - 1);

        int ans = n - fir + 1, cnt = 0;
        while (pq.top() > cnt) {
            cnt++;
            int top = pq.top(); pq.pop();
            pq.push(top - 1);
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

**核心思想**：排序后优先队列动态处理最大剩余数目，时间复杂度 O(n log n)。

---
处理用时：133.17秒