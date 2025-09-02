# 题目信息

# [USACO08NOV] Time Management S

## 题目描述

Ever the maturing businessman, Farmer John realizes that he must manage his time effectively. He has N jobs conveniently numbered 1..N (1 <= N <= 1,000) to accomplish (like milking the cows, cleaning the barn, mending the fences, and so on).

To manage his time effectively, he has created a list of the jobs that must be finished. Job i requires a certain amount of time T\_i (1 <= T\_i <= 1,000) to complete and furthermore must be finished by time S\_i (1 <= S\_i <= 1,000,000). Farmer John starts his day at time t=0 and can only work on one job at a time until it is finished.

Even a maturing businessman likes to sleep late; help Farmer John determine the latest he can start working and still finish all the jobs on time.

作为一名忙碌的商人，约翰知道必须高效地安排他的时间。他有 $N(1\le N\le 1000)$ 个工作要做，比如给奶牛挤奶，清洗牛棚，修理栅栏之类的。

为了高效，约翰列出了所有工作的清单。第 $i(1\le i\le N)$ 个工作需要 $T_i(1\le T_i\le 1000)$ 单位的时间来完成，而且必须在 $1\le S_i\le 10^6$ 或之前完成。现在是 $0$ 时刻。约翰做一份工作必须直到做完才能停止。

所有的商人都喜欢睡懒觉。请帮约翰计算他最迟什么时候开始工作，可以让所有工作按时完成。（如果始终无法完成全部任务，输出 $-1$）


## 说明/提示

Farmer John has 4 jobs to do, which take 3, 8, 5, and 1 units of time, respectively, and must be completed by time 5, 14, 20, and 16, respectively.


Farmer John must start the first job at time 2. Then he can do the second, fourth, and third jobs in that order to finish on time.


## 样例 #1

### 输入

```
4 
3 5 
8 14 
5 20 
1 16 
```

### 输出

```
2 
```

# AI分析结果



---

## 算法分类  
**贪心算法**

## 题解思路与解决难点  

### 核心思路对比  
1. **二分答案法**  
   - **排序依据**：按截止时间升序排列  
   - **验证逻辑**：假设开始时间为 `mid`，依次处理每个工作，若累计时间超过截止时间则判定失败  
   - **时间复杂度**：O(n log M)（M 为最大截止时间）  

2. **贪心逆序处理法**  
   - **排序依据**：按截止时间降序排列  
   - **核心操作**：从最晚截止的工作开始，维护当前时间 `now`，逐次取 `min(now, S_i) - T_i`  
   - **时间复杂度**：O(n log n)（仅排序开销）  

### 解决难点  
- **贪心策略的正确性证明**：通过逆序处理，确保每个工作的最晚开始时间受后续工作限制的最小值，从而保证全局最优。  
- **排序方向的选择**：必须按截止时间降序排序，才能正确维护前置约束。  

---

## 题解评分 (≥4星)  

### 1. Dr_殇 (★★★★☆)  
- **亮点**：贪心逆序处理，代码简洁高效  
- **代码片段**：  
  ```cpp
  sort(work + 1, work + 1 + n, cmp);
  ans = work[1].f;
  for (int i = 1; i <= n; i++) {
      if (ans <= work[i].f) ans -= work[i].v;
      else ans = work[i].f - work[i].v;
  }
  ```

### 2. Benson2005 (★★★★☆)  
- **亮点**：代码极简，核心逻辑仅两行  
- **代码片段**：  
  ```cpp
  sort(a + 1, a + n + 1, cmp);
  for (int i = 1; i <= n; i++) lst = min(lst, a[i].l) - a[i].t;
  ```

### 3. Diamiko (★★★★★)  
- **亮点**：详细解释二分思路，代码注释清晰  
- **代码片段**：  
  ```cpp
  while (l <= r) {
      mid = (l + r) >> 1;
      if (check(mid)) ans = mid, l = mid + 1;
      else r = mid - 1;
  }
  ```

---

## 最优思路提炼  
**贪心逆序处理法**：  
1. 按截止时间降序排序  
2. 初始化 `now = 最晚截止时间`  
3. 对每个工作：`now = min(now, S_i) - T_i`  
4. 若最终 `now ≥ 0`，则输出 `now`，否则输出 `-1`  

**正确性证明**：  
- 逆序处理确保每次调整的时间约束包含后续工作的限制  
- `min(now, S_i)` 保证当前工作不会因后续约束而超时  

---

## 类似题目推荐  
1. **P1230 智力大冲浪**（贪心调度任务）  
2. **P5019 铺设道路**（贪心分段处理）  
3. **P1090 合并果子**（优先队列贪心）  

---

## 可视化与算法演示  

### 动画设计  
1. **排序展示**：降序排列的工作列表，以不同颜色标记截止时间  
2. **逐步处理**：高亮当前工作，显示 `now` 变化过程  
3. **关键操作**：  
   - 红色标记 `min(now, S_i)` 的决策点  
   - 绿色箭头表示 `now` 更新为 `now - T_i`  

### 复古像素风格  
- **颜色方案**：8-bit 调色板（红：决策点，绿：时间更新）  
- **音效设计**：  
  - 成功完成：8-bit 上升音阶  
  - 调整时间：短促“滴”声  

---

## 核心代码实现  

### 贪心逆序处理  
```cpp
#include <algorithm>
using namespace std;

struct Task { int t, s; };
bool cmp(Task a, Task b) { return a.s > b.s; }

int main() {
    int n, now = 0;
    Task tasks[1005];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &tasks[i].t, &tasks[i].s);
    
    sort(tasks, tasks + n, cmp);
    now = tasks[0].s;
    for (int i = 0; i < n; i++) {
        now = min(now, tasks[i].s) - tasks[i].t;
        if (now < 0) break;
    }
    printf("%d", now >= 0 ? now : -1);
    return 0;
}
```

---

## 个人心得摘录  
- **调试教训**：初始未处理 `now < 0` 导致错误输出（如第八组数据）  
- **顿悟点**：逆序处理时，`min(now, S_i)` 的约束传递是关键  

---

**可视化演示链接**：[Time Management S - 贪心动画演示](https://example.com/demo)  
（注：示例链接需替换为实际实现）

---
处理用时：175.06秒