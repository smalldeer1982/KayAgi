# 题目信息

# Group Photo 2 (online mirror version)

## 题目描述

Many years have passed, and $ n $ friends met at a party again. Technologies have leaped forward since the last meeting, cameras with timer appeared and now it is not obligatory for one of the friends to stand with a camera, and, thus, being absent on the photo.

Simply speaking, the process of photographing can be described as follows. Each friend occupies a rectangle of pixels on the photo: the $ i $ -th of them in a standing state occupies a $ w_{i} $ pixels wide and a $ h_{i} $ pixels high rectangle. But also, each person can lie down for the photo, and then he will occupy a $ h_{i} $ pixels wide and a $ w_{i} $ pixels high rectangle.

The total photo will have size $ W×H $ , where $ W $ is the total width of all the people rectangles, and $ H $ is the maximum of the heights. The friends want to determine what minimum area the group photo can they obtain if no more than $ n/2 $ of them can lie on the ground (it would be strange if more than $ n/2 $ gentlemen lie on the ground together, isn't it?..)

Help them to achieve this goal.

## 样例 #1

### 输入

```
3
10 1
20 2
30 3
```

### 输出

```
180
```

## 样例 #2

### 输入

```
3
3 1
2 2
4 3
```

### 输出

```
21
```

## 样例 #3

### 输入

```
1
5 10
```

### 输出

```
50
```

# AI分析结果



### 综合分析与结论

**题目核心**：通过调整每个人的方向（站立/躺下），在最多允许半数人躺下的情况下，使总照片面积（总宽度 × 最大高度）最小。

**难点分析**：
1. **高度与宽度的动态影响**：总高度由最大值决定，而总宽度是累加值，两者相互制约。
2. **贪心策略设计**：需平衡高度限制与宽度总和，并控制躺下人数。
3. **枚举范围的正确性**：确保枚举的候选高度覆盖所有可能的最优解。

**算法要点**：
1. **枚举最大高度**（所有可能的候选值，如题目中提到的每个人原始高度和宽度的可能值）。
2. **分类处理每个人**：
   - 若躺下或站立后高度超过当前枚举值，直接跳过。
   - 强制必须躺下或站立的情况（如高度超限必须躺下）。
   - 可调整方向的人按收益（躺下后宽度减少量）排序，贪心选择。
3. **数据结构优化**：优先队列或排序用于快速选择最优调整对象。

**可视化设计**：
- **像素风格动画**：用 8-bit 风格展示每个人的状态（站立/躺下），高亮当前枚举的高度。
- **贪心过程分步演示**：动态显示每个候选高度下的选择过程，如必须躺下的人数、可调整的候选列表排序。
- **音效与交互**：触发音效提示可行解，自动播放模式模拟贪心决策流程。

---

### 题解清单（评分≥4星）

1. **题解一（communist）** ★★★★☆  
   - **亮点**：代码简洁，直接枚举高度，按差值排序贪心。
   - **关键思路**：强制处理必须躺下的人，剩余名额按 `w_i - h_i` 排序贪心。
   - **代码可读性**：结构清晰，无冗余逻辑。

2. **题解三（Happy_mouse）** ★★★★☆  
   - **亮点**：将人员状态分为五类，逻辑严密。
   - **关键思路**：按类型处理，优先调整收益最大的可选项。
   - **注释与结构**：详细注释，分类讨论增强可读性。

3. **题解四（tZEROちゃん）** ★★★★☆  
   - **亮点**：使用优先队列动态维护可调整项。
   - **关键思路**：优先队列处理可选调整项，优化贪心效率。
   - **代码简洁性**：无冗杂条件判断，逻辑流畅。

---

### 最优思路提炼

1. **枚举所有可能的最大高度**：覆盖每个人的原始高度和宽度值。
2. **强制与可选分类**：
   - 必须躺下：高度超过当前枚举值。
   - 必须站立：宽度超过当前枚举值。
   - 可选调整：按 `w_i - h_i` 排序，选择收益最大的前 `k` 项。
3. **贪心策略核心**：在剩余名额内，优先选择调整后宽度减少最多的人。

**代码片段**（题解一核心逻辑）：
```cpp
sort(v.begin(), v.end(), cmp);
for (int i = 0; i < v.size() && cnt + i < n/2; i++)
    rs += h[v[i]] - w[v[i]];
ans = min(ans, rs * maxh);
```

---

### 同类型题与算法套路

**常见贪心场景**：
- **区间调度**：选择不重叠区间，最大化数量。
- **最小化最大值**：如二分答案或枚举高度，结合条件验证。
- **动态调整选择**：利用排序/堆维护当前最优选项。

**推荐题目**：
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：优先队列贪心。
2. [P1842 奶牛玩杂技](https://www.luogu.com.cn/problem/P1842)：权重排序贪心。
3. [P1250 种树](https://www.luogu.com.cn/problem/P1250)：区间覆盖贪心。

---

### 个人心得摘录

- **调试教训**：需严格验证每个候选高度的合法性，避免遗漏边界条件。
- **贪心顿悟**：调整方向的最优性可通过差值排序直接体现，无需复杂计算。

---

### 可视化与算法演示

**动画方案**：
1. **像素网格展示**：每个候选高度对应一列，动态显示每个人的状态。
2. **颜色标记**：
   - 红色：必须躺下。
   - 绿色：必须站立。
   - 黄色：可调整。
3. **音效交互**：
   - 选中可行解：播放上扬音效。
   - 无效枚举：短促提示音。
4. **自动演示模式**：按候选高度顺序自动运行，观察面积变化。

**复古风格设计**：
- **Canvas 绘制**：8-bit 像素块表示人员状态。
- **积分系统**：每找到一个更优解增加积分，增强趣味性。

---

### 代码实现（题解一完整版）
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1010;
int n, w[maxn], h[maxn], hh, ans=1e9, sw;

bool cmp(int a, int b) {
    return w[a] - h[a] > w[b] - h[b];
}

int main() {
    scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        scanf("%d%d", &w[i], &h[i]);
        hh = max({hh, w[i], h[i]});
        sw += w[i];
    }
    for (int maxh=1; maxh<=hh; maxh++) {
        int cnt=0, rs=sw;
        vector<int> v;
        for (int i=1; i<=n; i++) {
            if (w[i]>maxh && h[i]>maxh) { cnt=1e9; break; }
            else if (h[i] > maxh) { cnt++; rs += h[i]-w[i]; }
            else if (w[i] > maxh) continue;
            else if (w[i] > h[i]) v.push_back(i);
        }
        if (cnt > n/2) continue;
        sort(v.begin(), v.end(), cmp);
        for (int i=0; i<v.size() && cnt+i <n/2; i++)
            rs += h[v[i]] - w[v[i]];
        ans = min(ans, rs * maxh);
    }
    printf("%d\n", ans);
    return 0;
}
```

---
处理用时：304.59秒