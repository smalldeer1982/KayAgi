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



# 算法分类
排序合并区间

---

# 题解思路与难点对比

## 核心思路
1. **排序区间**：将所有挤奶时间段按开始时间排序
2. **合并重叠区间**：遍历排序后的区间，动态维护当前合并后的最大区间
3. **计算最长覆盖与间隔**：在合并过程中记录最大连续覆盖时间与区间之间的最大间隔

## 解决难点
1. **区间重叠判断**：需判断当前区间是否与合并后的最大区间有重叠
2. **时间计算细节**：挤奶结束时刻不计入工作时间（左闭右开区间）
3. **边界处理**：需处理第一个区间的初始化及最终合并结果的统计

---

# 最优题解（评分≥4★）

1. **KesdiaelKen（差分法）** ★★★★☆
- 亮点：利用差分数组+前缀和高效统计覆盖情况
- 核心代码：
```cpp
for(int i=start;i<=end;i++){
    c[i] = c[i-1] + c[i];
    if(c[i]>0) update_cover_time();
    else update_idle_time();
}
```

2. **Mys_C_K（事件排序法）** ★★★★☆
- 亮点：将开始/结束作为事件点排序处理
- 关键步骤：
```cpp
sort(event+1, event+2*n+1);
for(事件i in 排序后事件){
    if(开始事件) 覆盖计数++;
    else 覆盖计数--;
    计算连续覆盖/空闲时间...
}
```

3. **hanxin（区间合并法）** ★★★★
- 核心逻辑：
```cpp
sort(区间数组);
维护当前合并区间[start,end];
for(区间 in 排序后数组){
    if(可合并) 扩展end;
    else 计算间隔并更新结果...
}
```

---

# 最优思路提炼

**关键技巧**：
1. **排序预处理**：按开始时间排序后，只需顺序处理即可保证区间有序
2. **贪心合并**：每次只需比较当前区间的开始与合并区间的结束时间
3. **即时统计**：在合并过程中动态维护最大值，避免二次遍历

**实现要点**：
```python
sorted_intervals = sorted(intervals, key=lambda x:x[0])
current_start, current_end = sorted_intervals[0]
max_cover = current_end - current_start
max_gap = 0

for s, e in sorted_intervals[1:]:
    if s <= current_end:
        current_end = max(current_end, e)
        max_cover = max(max_cover, current_end - current_start)
    else:
        max_gap = max(max_gap, s - current_end)
        current_start, current_end = s, e
```

---

# 同类题目推荐
1. P1883 线段覆盖（区间最大覆盖次数）
2. P1496 火烧赤壁（区间合并长度计算）
3. P2434 区间覆盖问题（最少覆盖区间数）

---

# 可视化设计

**动画效果**：
1. **区间排序阶段**：以时间轴为背景，未排序的区间随机分布，排序后从左到右依次对齐
2. **合并过程**：
   - 当前合并区间用绿色高亮
   - 新处理区间用黄色闪烁
   - 合并时显示扩展动画（绿色向右延伸）
3. **间隔统计**：红色高亮显示区间之间的空白段

**交互功能**：
- 速度调节滑块控制动画速度
- 单步执行按钮观察每一步合并细节
- 悬浮显示当前合并区间的[start,end]值

**复古像素风格**：
- 时间轴以8-bit风格砖块表示
- 合并动画伴随经典FC音效（扩展时"嘟"声，间隔出现时"咔"声）
- 得分板采用像素字体显示当前max_cover/max_gap值

---

# 核心代码实现
```python
# 区间合并核心逻辑
def milk_cows(intervals):
    intervals.sort()
    res = [intervals[0]]
    max_cover = intervals[0][1] - intervals[0][0]
    max_gap = 0
    
    for s, e in intervals[1:]:
        last_e = res[-1][1]
        if s <= last_e:
            res[-1][1] = max(last_e, e)
            max_cover = max(max_cover, res[-1][1]-res[-1][0])
        else:
            max_gap = max(max_gap, s - last_e)
            res.append([s, e])
    
    return max_cover, max_gap
```

---
处理用时：63.24秒