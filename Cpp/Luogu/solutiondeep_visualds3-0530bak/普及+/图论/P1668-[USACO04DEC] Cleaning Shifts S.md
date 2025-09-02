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

## 算法分类
**贪心算法**

---

## 综合分析与结论

### 核心思路与难点对比
1. **贪心算法**（Greenzhe、HDZmessi等）
   - **核心步骤**：排序区间后，每次选择能覆盖当前起点且右端点最大的区间
   - **关键变量**：当前覆盖终点 `st`，双指针 `i/j` 遍历区间
   - **正确性证明**：每次选择右端点最大的区间能最大化覆盖范围，保证最优性
   - **时间复杂度**：O(n log n) 排序 + O(n) 扫描，适合 1e6 量级

2. **线段树优化DP**（MoonCake2011、Southern_Dynasty）
   - **状态设计**：`dp[i]` 表示覆盖 [1,i] 的最小奶牛数
   - **转移方程**：`dp[r] = min(dp[l-1..r-1]) + 1`
   - **优化手段**：线段树维护区间最小值，查询效率 O(log T)
   - **难点**：离散化处理、线段树实现细节

3. **最短路模型**（Southern_Dynasty、_k_e_v_i_n_）
   - **建图技巧**：时间点作为节点，区间 [s,e] 转化为 `s-1→e` 边权1
   - **辅助边**：`i→i-1` 边权0，允许向左回溯
   - **算法选择**：01-BFS 或 Dijkstra，时间复杂度 O(T+n)

### 可视化设计思路
**贪心算法动画方案**（8位像素风格）：
1. **时间轴展示**：横向像素条表示时间 [1,T]，绿色块表示已覆盖区域
2. **候选区间高亮**：红色框表示当前扫描区间，金色框表示候选最优区间
3. **音效触发**：
   - 选中区间时播放 "coin.wav"
   - 覆盖范围更新时播放 "powerup.wav"
   - 无解时播放 "game_over.wav"
4. **AI自动演示**：按贪心逻辑自动执行，速度可调节（1x/2x/4x）
5. **交互面板**：暂停/继续、单步执行、重置按钮

示例伪代码：
```javascript
// Canvas 绘制逻辑
function drawTimeline(st, ed, ranges) {
  ctx.fillStyle = "#8B8B83"; // 未覆盖区域
  ctx.fillRect(0, 0, T*10, 20);
  
  ctx.fillStyle = "#77DD77"; // 已覆盖区域
  ctx.fillRect(0, 0, st*10, 20);
  
  ranges.forEach(r => {
    ctx.strokeStyle = r.selected ? "#FFD700" : "#FF6961";
    ctx.strokeRect(r.s*10, 5, (r.e-r.s)*10, 10);
  });
}
```

---

## 高星题解清单（≥4★）

### 1. Greenzhe 的贪心解法（5★）
- **亮点**：双指针优化扫描过程，严格数学证明
- **代码片段**：
```cpp
sort(range+1, range+n+1);
int st=1, ans=0;
for(int i=1,j=1; i<=n; ){
    int r=0;
    while(j<=n && range[j].l<=st) 
        r = max(r, range[j++].r);
    if(r < st) break; // 无解判断
    ans++;
    st = r + 1;
    i = j;
}
```

### 2. Southern_Dynasty 的最短路模型（4★）
- **亮点**：离散化处理支持 T=1e9，01-BFS优化
- **关键代码**：
```cpp
for(int i=1; i<=n; ++i) 
    add_edge(u[i]-1, v[i], 1);
for(int i=1; i<=T; ++i) 
    add_edge(i, i-1, 0);
BFS_01(0); // 01-BFS
```

### 3. 船酱魔王 的线段树DP（4★）
- **亮点**：清晰的状态转移注释，完整线段树实现
- **核心逻辑**：
```cpp
build(1,1,t); // 初始化线段树
for(区间按r排序){
    int tmp = query(l-1, r-1) + 1;
    update(r, tmp);
}
```

---

## 最优技巧提炼
1. **贪心决策链**：排序后通过双指针快速定位候选区间集合
2. **离散化压缩**：将大范围时间点映射到有限节点（最短路模型）
3. **线段树优化**：将区间最小值查询从 O(n) 降至 O(log n)

---

## 相似题目推荐
1. [P4644 [USACO05DEC] Cleaning Shifts G](https://www.luogu.com.cn/problem/P4644)（带权区间覆盖）
2. [P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280)（逆向DP+区间处理）
3. [P2512 [HAOI2008] 糖果传递](https://www.luogu.com.cn/problem/P2512)（环形贪心）

---

## 个人心得摘录
> "在贪心实现中忘记更新双指针的起始位置，导致TLE。后来发现应将 `i=j` 来跳过已处理区间，这是双指针优化的关键。" —— Greenzhe

---

## 核心代码实现（贪心算法）
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Segment { int l, r; };
vector<Segment> ranges;

int main() {
    int n, T;
    cin >> n >> T;
    ranges.resize(n);
    for(auto &[l,r] : ranges) cin >> l >> r;
    
    sort(ranges.begin(), ranges.end(), [](auto &a, auto &b){
        return a.l < b.l; // 按左端点排序
    });
    
    int st = 1, ans = 0, i = 0;
    while(st <= T) {
        int max_r = -1;
        while(i < n && ranges[i].l <= st) {
            max_r = max(max_r, ranges[i].r);
            i++;
        }
        if(max_r < st) { cout << -1; return 0; }
        ans++;
        st = max_r + 1;
    }
    cout << ans;
}
```

---
处理用时：88.79秒