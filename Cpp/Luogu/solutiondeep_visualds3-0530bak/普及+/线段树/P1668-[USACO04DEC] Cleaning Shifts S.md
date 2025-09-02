# 题目信息

# [USACO04DEC] Cleaning Shifts S

## 题目描述

一天有 $T(1\le T\le 10^6)$ 个时段。约翰正打算安排他的 $N(1\le N\le 2.5\times 10^4)$ 只奶牛来值班，打扫打扫牛棚卫生。每只奶牛都有自己的空闲时间段 $ [S_i,E_i](1\le S_i\le E_i\le T)$，只能把空闲的奶牛安排出来值班。而且，每个时间段必需有奶牛在值班。

那么，最少需要动用多少奶牛参与值班呢？如果没有办法安排出合理的方案，就输出 $-1$。

## 说明/提示

$1\le T\le 10^6$，$N\le 2.5\times 10^4$，$1\le S_i\le E_i\le T$。

$\text{Update On 2023/08/08}$：添加了一组hack数据，详情见[这里](https://www.luogu.com.cn/discuss/613052)。叉掉了时间复杂度为 $\mathcal O(nt)$ 的错解。

## 样例 #1

### 输入

```
3 10
1 7
3 6
6 10```

### 输出

```
2```

# AI分析结果



---

**唯一算法分类**：贪心算法

---

**综合分析与结论**

### 核心思路与难点
- **问题本质**：区间完全覆盖问题，要求用最少区间覆盖 [1, T]。
- **贪心核心**：按左端点排序，每次选覆盖当前起点且右端点最大的区间。正确性基于局部最优推导全局最优。
- **动态规划优化**：线段树维护区间最小值，优化状态转移（O(N log T)）。
- **最短路转化**：将区间视为边权为1的边，时间点间连0边，转化为最短路径问题。
- **难点**：处理大范围 T 的时间复杂度（离散化或数据结构优化），贪心正确性证明。

### 核心算法流程（贪心）
1. 排序区间按左端点升序。
2. 初始化当前覆盖终点 `st=1`。
3. 双指针遍历：找到所有左端点 ≤ st 的区间，记录最大右端点 `r`。
4. 若 `r < st` 则无解；否则 `st=r+1`，计数+1。
5. 重复直到覆盖整个区间或无法继续。

**可视化设计**：
- **动画效果**：时间轴横向展示，当前 `st` 高亮为红色。候选区间用绿色覆盖区域，选中区间变为蓝色并更新 `st`。步进按钮控制流程，音效提示选中/失败。
- **像素风格**：用8位像素块表示时间点，覆盖区域显示为不同颜色条带，贪心选择时播放「选择音效」，失败时「错误音效」。
- **交互面板**：支持速度调节、单步执行，显示当前覆盖区间和计数。

---

**题解清单 (≥4星)**

1. **Greenzhe (★★★★★)**  
   - **亮点**：清晰的贪心思路，双指针优化到 O(N log N)，代码简洁易懂。  
   - **关键代码**：
     ```cpp
     for(int i=1,j=1; i<=n; ){
         int r=0;
         while(j<=n && range[j].l<=st) r=max(r, range[j++].r);
         if(r<st) break;
         ans++;
         st = r+1;
         i=j;
     }
     ```

2. **Southern_Dynasty (★★★★☆)**  
   - **亮点**：最短路思路创新，01BFS 实现线性复杂度，离散化处理大 T。  
   - **关键代码**（01BFS）：
     ```cpp
     for(int i=1; i<=T; ++i) add_edge(i, i-1, 0);
     for(auto [l,r]: intervals) add_edge(l-1, r, 1);
     BFS_01(0); // 结果即 dis[T]
     ```

3. **MoonCake2011 (★★★★☆)**  
   - **亮点**：线段树优化 DP 的完整实现，状态转移方程清晰。  
   - **关键代码**（线段树查询）：
     ```cpp
     int tmp = query(a[i].l-1, a[i].r-1, 1, t, 1) + 1;
     update(a[i].r, tmp); // 维护 DP 最小值
     ```

---

**最优思路提炼**

1. **贪心选择**：排序后逐步扩展覆盖范围，每次选右端点最大的可行区间。
2. **线段树优化**：将 DP 的区间查询优化为 O(log T)，适用于动态规划场景。
3. **图论转化**：将区间覆盖转化为边权模型，利用最短路算法求解。

---

**同类型题与算法套路**
- **同类问题**：区间覆盖、跳跃游戏、任务调度。
- **通用套路**：
  - **贪心**：排序后选择局部最优。
  - **DP优化**：数据结构加速状态转移（线段树、单调队列）。
  - **图论建模**：将操作转化为边，用最短路/网络流求解。

---

**推荐题目**
1. [P4644 Cleaning Shifts](https://www.luogu.com.cn/problem/P4644)（带权区间覆盖）
2. [P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280)（逆向 DP）
3. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803)（经典贪心）

---

**个人心得摘录**
- **贪心边界**：需处理 `st` 更新为 `r+1` 而非 `r`，否则可能重复覆盖。
- **最短路细节**：离散化需包含 `l-1` 和 `r` 避免断点遗漏。
- **线段树初始化**：`f[0]=0` 是正确转移的起点，漏掉会导致错误。

---

**代码片段与可视化实现**

**贪心核心代码**：
```cpp
sort(range+1, range+n+1);
int st=1, ans=0;
for(int i=1, j=1; i<=n; ){
    int r=0;
    while(j<=n && range[j].l <= st) 
        r = max(r, range[j++].r);
    if(r < st) break; // 无解
    ans++;
    if(r >= T) { cout << ans; return 0; }
    st = r + 1; // 更新起点
    i = j;
}
```

**可视化 JS 伪代码**：
```javascript
// 初始化 Canvas
const canvas = initCanvas();
let st = 1, ans = 0;
const intervals = sortedIntervals;

function step() {
    let maxR = 0, ptr = currentIndex;
    while (ptr < n && intervals[ptr].l <= st) {
        maxR = Math.max(maxR, intervals[ptr].r);
        ptr++;
    }
    if (maxR < st) showFailure();
    else {
        ans++;
        st = maxR + 1;
        drawCovered(st, 'blue');
    }
    if (st > T) showSuccess(ans);
}
// 绑定步进按钮点击事件
document.getElementById('next-step').onclick = step;
```

---
处理用时：83.67秒