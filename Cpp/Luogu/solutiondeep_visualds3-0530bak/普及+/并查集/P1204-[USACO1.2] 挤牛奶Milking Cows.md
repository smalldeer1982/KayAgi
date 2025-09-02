# 题目信息

# [USACO1.2] 挤牛奶Milking Cows

## 题目描述

三个农民每天清晨 $5$ 点起床，然后去牛棚给三头牛挤奶。

第一个农民在 $300$ 秒 (从 $5$ 点开始计时) 给他的牛挤奶，一直到 $1000$ 秒。第二个农民在 $700$ 秒开始，在 $1200$ 秒结束。第三个农民在 $1500$ 秒开始，$2100$ 秒结束。  

期间最长的至少有一个农民在挤奶的连续时间为 $900$ 秒 (从 $300$ 秒到 $1200$ 秒)，而最长的无人挤奶的连续时间(从挤奶开始一直到挤奶结束)为 $300$ 秒 (从 $1200$ 秒到 $1500$ 秒)。
****

你的任务是编一个程序，读入一个有 $n$ 个农民挤 $n$ 头牛的工作时间列表，计算以下两点(均以秒为单位):

最长至少有一人在挤奶的时间段。

最长的无人挤奶的时间段。（从有人挤奶开始算起）


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 5000$，$0 \le l \le r \le 10^6$。

题目翻译来自NOCOW。

USACO Training Section 1.2


## 样例 #1

### 输入

```
3
300 1000
700 1200
1500 2100
```

### 输出

```
900 300
```

# AI分析结果



## 【算法分类】
区间合并

---

## 【综合分析与结论】

### 核心思路
题目要求找出最长连续挤奶时间和最长无挤奶时间。核心难点在于处理时间区间重叠与间隙，常见解决方案包括布尔标记、区间合并、差分数组等。最优解法是区间合并法，通过排序后合并重叠区间，再计算最大连续段和间隔。

### 算法流程
1. **区间排序**：按开始时间升序排序所有时间段
2. **区间合并**：维护当前合并后的时间段 [cur_start, cur_end]
   - 若新区间与当前重叠（新.start ≤ cur_end），扩展 cur_end
   - 若新区间不重叠，保存当前段并重置为新区间
3. **统计结果**：在合并过程中记录最长连续段和间隔

### 可视化设计
1. **动画方案**：在 Canvas 上展示区间合并过程
   - 初始区间随机颜色显示，合并后统一颜色
   - 高亮当前合并区间，显示合并前后的变化
2. **步进控制**：允许单步执行合并步骤，观察区间扩展逻辑
3. **像素风格**：采用 8-bit 风格界面，合并时播放 "滴" 音效，完成时播放通关音效
4. **状态面板**：实时显示最长连续时间和最大间隔

---

## 【题解清单 (≥4星)】

### 1. 结构体排序法（学而思李老师，4.5星）
- **亮点**：代码简洁，标准区间合并模板
- **核心**：按开始时间排序，动态维护合并区间
- **代码片段**：
```cpp
sort(m + 1, m + 1 + N, cmp);
int begin = m[1].begin, end = m[1].end;
for(int i=2; i<=N; ++i) {
    if(m[i].begin <= end) 
        end = max(end, m[i].end);
    else {
        ans1 = max(end - begin);
        ans2 = max(m[i].begin - end);
        begin = m[i].begin; end = m[i].end;
    }
}
```

### 2. 差分数组法（KesdiaelKen，4.5星）
- **亮点**：O(n) 时间复杂度，高效处理大规模数据
- **核心**：差分标记变化点，前缀和统计覆盖状态
- **代码片段**：
```cpp
for(int i=0;i<n;i++) {
    c[a]++; c[b]--; // 差分标记
}
for(int i=start; i<=end; i++) {
    c[i] += c[i-1]; // 前缀和还原
    if(c[i]>0) tmpa++; else tmpb++; // 统计连续段
}
```

### 3. 事件点扫描法（Mys_C_K，4星）
- **亮点**：将时间点视为事件，扫描计算覆盖状态
- **核心**：处理开始/结束事件，维护当前覆盖人数
- **代码片段**：
```cpp
sort(event+1, event+2*n+1);
int scount=0, last=event[1].seconds;
for(int i=2; i<=2*n; i++) {
    if(event[i].is_start) {
        if(scount==0) ans2 = max(event[i].seconds - last);
        scount++;
    } else {
        scount--;
        if(scount==0) ans1 = max(event[i].seconds - last);
    }
}
```

---

## 【最优思路提炼】
1. **区间合并法**：排序后线性扫描合并，时间复杂度 O(n log n)
2. **差分标记法**：通过变化点统计覆盖状态，时间复杂度 O(max_time)
3. **事件点扫描**：将时间点抽象为事件，动态维护覆盖状态

---

## 【同类型题推荐】
1. P1886 滑动窗口（区间极值）
2. P1496 火烧赤壁（区间合并）
3. P2285 打鼹鼠（时间区间覆盖）

---

## 【核心代码实现（区间合并法）】
```cpp
#include <algorithm>
#include <iostream>
using namespace std;

struct Interval { int start, end; };
Interval intervals[5005];

int main() {
    int n; cin >> n;
    for(int i=0; i<n; i++) 
        cin >> intervals[i].start >> intervals[i].end;
    
    sort(intervals, intervals+n, [](auto& a, auto& b) { 
        return a.start < b.start; 
    });

    int max_cover = 0, max_gap = 0;
    int cur_start = intervals[0].start;
    int cur_end = intervals[0].end;
    
    for(int i=1; i<n; i++) {
        if(intervals[i].start <= cur_end) {
            cur_end = max(cur_end, intervals[i].end);
        } else {
            max_gap = max(max_gap, intervals[i].start - cur_end);
            max_cover = max(max_cover, cur_end - cur_start);
            cur_start = intervals[i].start;
            cur_end = intervals[i].end;
        }
    }
    max_cover = max(max_cover, cur_end - cur_start);
    
    cout << max_cover << " " << max_gap << endl;
    return 0;
}
```

---

## 【可视化设计要点】
1. **Canvas 绘制**：横向时间轴，不同区间用颜色块表示
2. **合并动画**：相邻区间合并时显示扩展效果，伴随音效
3. **状态跟踪**：侧边栏实时显示当前最长覆盖和间隔
4. **复古风格**：8-bit 像素字体，合并时播放 FC 风格音效

通过交互式演示，学习者可直观理解区间合并的动态过程，快速掌握算法核心思想。

---
处理用时：67.75秒