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

## 综合分析与结论

### 核心思路与难点
**问题本质**：区间完全覆盖问题，要求用最少的区间覆盖 [1, T] 的所有整数点  
**核心难点**：如何在 O(n) 或 O(n log n) 复杂度下找到最优解  
**贪心策略**：  
1. 按左端点排序区间，每次选择能覆盖当前起点且右端点最大的区间  
2. 更新起点为选中区间的右端点+1，重复直到覆盖终点  
**正确性证明**：每次选择覆盖更多未来时段的区间，保证后续需要更少的选择次数

### 题解对比与可视化设计
#### 贪心解法（Greenzhe / ICU152_lowa_IS8）
- **核心差异**：循环终止条件与区间选择细节  
- **可视化要点**：
  - 红框高亮当前候选区间范围（左端点 ≤ 当前起点）
  - 黄框标记当前选中区间（最大右端点）
  - 绿色进度条显示已覆盖时段
  - 音效设计：选择区间时播放"金币收集"音效，失败时播放"错误"音效

#### 最短路解法（Southern_Dynasty）
- **核心思想**：将区间转换为边权为1的边，时间点间添加边权为0的逆向边
- **可视化要点**：
  - 动态绘制图结构，红色箭头表示区间边，灰色箭头表示逆向边
  - 显示最短路径的扩散过程（类似Dijkstra动画）

---

## 题解清单（≥4星）

### 1. Greenzhe 的贪心解法（★★★★★）
- **亮点**：双指针优化 + 严格数学证明  
- **关键代码**：
```cpp
sort(range+1, range+n+1);
int st=1, ans=0;
for(int i=1,j=1; i<=n; ) {
    int r=0;
    while(j<=n && range[j].l<=st) 
        r = max(r, range[j++].r);
    if(r < st) break;
    ans++;
    if(r >= ed) { cout << ans; return 0; }
    st = r+1;
    i = j;
}
```

### 2. Southern_Dynasty 的最短路解法（★★★★☆）
- **亮点**：离散化处理 + 01BFS优化  
- **创新点**：将区间覆盖问题转化为图论问题  
- **数据兼容**：支持 T 达到 1e9 的离散化版本

### 3. bloodstalk 的线段树DP（★★★★☆）
- **亮点**：线段树优化区间最小值查询  
- **通用性**：可扩展为带权区间覆盖问题  
- **代码片段**：
```cpp
build(1,0,R); // 建立覆盖[0,T]的线段树
Modify(0,0,R,1,0); // 初始化dp[0]=0
for(auto &cow : sorted_cows) {
    int min_val = Query(cow.l-1, cow.r-1);
    dp[cow.r] = min(dp[cow.r], min_val+1);
    Modify(cow.r, dp[cow.r]);
}
```

---

## 最优思路提炼

### 贪心算法关键步骤
1. **排序预处理**：按左端点升序、右端点降序排列
2. **双指针扫描**：用 j 指针快速跳过无法覆盖当前起点的区间
3. **候选区间筛选**：在左端点 ≤ 当前起点的区间中选右端点最大者
4. **跳跃更新**：直接将起点更新为选中区间的右端点+1

### 正确性验证
- **数学归纳法**：假设前k步选择最优，第k+步选择最大右端点必然最优  
- **反证法**：若存在更优解，其选择的区间右端点必定不大于贪心选择

---

## 同类题目推荐
1. **P1280 尼克的任务**（区间覆盖+逆向DP）  
2. **P1514 引水入城**（区间完全覆盖变形）  
3. **P5020 货币系统**（贪心+完全覆盖思想）

---

## 可视化方案设计（贪心算法）

### 像素风格演示
```html
<canvas id="timeline" width="800" height="100"></canvas>
<script>
// 初始化时间轴（8-bit风格）
const ctx = document.getElementById('timeline').getContext('2d');
let st = 1, ed = 10, currentMax = 0;
const ranges = [[1,7], [3,6], [6,10]];

function draw() {
    ctx.fillStyle = '#2C3E50'; // 背景色
    ctx.fillRect(0, 0, 800, 100);
    
    // 绘制时间轴
    ranges.forEach(([l,r], i) => {
        ctx.fillStyle = i === currentIdx ? '#F1C40F' : '#3498DB';
        ctx.fillRect(l*80-80, 40, (r-l+1)*80, 20);
    });
    
    // 绘制当前选择线
    ctx.strokeStyle = '#E74C3C';
    ctx.beginPath();
    ctx.moveTo(st*80-80, 70);
    ctx.lineTo(st*80-80, 90);
    ctx.stroke();
}
```

### 交互功能
1. **步进控制**：空格键单步执行算法  
2. **自动播放**：按A键启动自动演示（可调速）  
3. **音效反馈**：
   - 正确选择：8-bit风格上升音阶（Web Audio API）  
   - 错误情况：短促的"哔"声

### 动画逻辑
```javascript
function greedyStep() {
    let maxR = 0, selectedIdx = -1;
    for(let i=0; i<ranges.length; i++) {
        if(ranges[i][0] > st) break;
        if(ranges[i][1] > maxR) {
            maxR = ranges[i][1];
            selectedIdx = i;
        }
    }
    
    if(selectedIdx === -1) {
        playErrorSound();
        return false;
    }
    
    st = maxR + 1;
    currentIdx = selectedIdx;
    playSuccessSound();
    return true;
}
```

---

## 关键代码实现

### 贪心算法完整版
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Segment { int l, r; };
const int MAXN = 25005;

int main() {
    int n, T;
    Segment seg[MAXN];
    cin >> n >> T;
    
    for(int i=0; i<n; ++i) 
        cin >> seg[i].l >> seg[i].r;
    
    sort(seg, seg+n, [](auto& a, auto& b) {
        return a.l != b.l ? a.l < b.l : a.r > b.r;
    });
    
    int ans = 0, cur_end = 0, ptr = 0;
    while(cur_end < T) {
        int max_next = cur_end;
        while(ptr < n && seg[ptr].l <= cur_end + 1) {
            max_next = max(max_next, seg[ptr].r);
            ptr++;
        }
        
        if(max_next == cur_end) {
            cout << -1;
            return 0;
        }
        
        cur_end = max_next;
        ans++;
    }
    
    cout << ans;
    return 0;
}
```

---

## 总结与提升
本题的贪心解法体现了**局部最优导致全局最优**的经典思想，关键点在于：
1. 合理的排序策略（左端点优先，右端点次之）  
2. 高效的扫描方式（双指针避免重复遍历）  
3. 严谨的终止条件判断（及时检测无法覆盖的情况）

建议在类似区间问题中，优先考虑贪心策略，再结合具体条件设计排序与选择规则。对于更复杂的带权问题，可参考线段树优化DP的思路。

---
处理用时：81.45秒