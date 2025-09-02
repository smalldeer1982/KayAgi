# 题目信息

# [USACO09DEC] Bobsledding S

## 题目描述

Bessie has entered a bobsled competition because she hopes her hefty weight will give her an advantage over the L meter course (2 <= L <= 1,000,000,000).

Bessie will push off the starting line at 1 meter per second, but her speed can change while she rides along the course. Near the middle of every meter Bessie travels, she can change her speed either by using gravity to accelerate by one meter per second or by braking to stay at the same speed or decrease her speed by one meter per second.

Naturally, Bessie must negotiate N (1 <= N <= 100,000) turns on the way down the hill. Turn i is located T\_i meters from the course start (1 <= T\_i <= L-1), and she must be enter the corner meter at a speed of at most S\_i meters per second (1 <= S\_i <= 1,000,000,000). Bessie can cross the finish line at any speed she likes.

Help Bessie learn the fastest speed she can attain without exceeding the speed limits on the turns.

Consider this course with the meter markers as integers and the turn speed limits in brackets (e.g., '[3]'):

```cpp

|   1   2   3   4   5   6   7[3]
|---+---+---+---+---+---+---+
|                            \
Start                         + 8    
                               \
                                + 9    
                                 \
                                  + 10       +++ 14 (finish)
                                   \         /
                              11[1] +---+---+
                                        12  13[8]
```
Below is a chart of Bessie's speeds at the beginning of each meter length of the course:

````
Max:                              3               1       8 
Mtrs: 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14 Spd:  1   2   3   4   5   5   4   3   4   3   2   1   2   3   4 
```
Her maximum speed was 5 near the beginning of meter 4. 

贝茜从山顶滑雪到山脚，山顶到山脚距离是L(2<L<10^9)米.贝茜在起点的速度是1米每 秒，但是他的速度是可以改变的，在每一米的速度可以是前一米的速度加1、减1，或者等于前一米 的速度.在滑行的过程中，贝茜会遇到N<=100000)个转弯处，第i个转弯处位于距离出发 Ti米处，为了安全，贝茜到达第i个转弯处的速度不能超过Si(1<Si<10^9)米 每秒.当然贝茜到达终点时的速度没有最大限制.请你计算贝茜在滑雪过程中最大的速度可以是多 少？


## 样例 #1

### 输入

```
14 3 
7 3 
11 1 
13 8 
```

### 输出

```
5 
```

# AI分析结果



### 算法分类
贪心

### 题目分析与结论
题目要求在满足转弯处速度限制的条件下，计算滑雪路径中的最大速度。各题解均采用以下核心思路：
1. **从后往前预处理速度限制**：调整每个转弯点的速度上限，确保后续转弯的限制能被满足。
2. **分段计算最大速度**：利用贪心策略，在相邻转弯点之间通过加速和减速计算可能的最大速度，公式为 `max_speed = (s + v0 + v1) // 2`，其中 `s` 为距离，`v0` 和 `v1` 分别为段起点和终点的速度。

### 高星题解推荐

#### 1. 作者：1124828077ccj（★★★★☆）
- **关键亮点**：代码简洁高效，预处理后分段处理并明确处理终点。核心逻辑清晰，通过两次遍历（反向预处理限制，正向计算最大速度）解决问题。
- **核心代码**：
```cpp
for (int i = n; i >= 2; i--)
    p[i-1].q = min(p[i-1].s, p[i].q + p[i].t - p[i-1].t); // 预处理限制
for (int i = 2; i <= n; i++) {
    // 计算段内最大速度
    if (m + p[i].t - p[i-1].t <= p[i].q) 
        ans = max(ans, m + p[i].t - p[i-1].t);
    else 
        ans = max(ans, (p[i].q + p[i].t - p[i-1].t + m) / 2);
    m = min(p[i].q, m + p[i].t - p[i-1].t);
}
```

#### 2. 作者：Lolierl（★★★★☆）
- **关键亮点**：详细数学推导，证明最大速度公式的正确性，代码中加入终点作为虚拟点处理。
- **核心公式**：`vmax = (s + v1 - v0) / 2 + v0`，等价于 `(s + v0 + v1) // 2`，覆盖加速与减速的所有情况。

#### 3. 作者：shenxinge（★★★★☆）
- **关键亮点**：代码简洁，包含调试注释，通过正反扫描处理限制，直观处理终点。
- **代码片段**：
```cpp
for(int i = n; i >= 1; i--) 
    a[i].s = min(a[i].s, a[i+1].s + a[i+1].t - a[i].t); // 反向预处理
for(int i = 1; i <= n; i++) {
    // 计算段内最大速度
    if(v0 + s <= v1) ans = max(ans, v0 + s);
    else ans = max(ans, (s + v0 + v1) / 2);
}
```

### 关键思路总结
1. **预处理限制**：从后向前调整转弯点速度，确保全局可行性。
2. **分段贪心**：利用加速-减速模型计算相邻点间的最大速度，公式为 `max_speed = (s + v0 + v1) // 2`。

### 拓展与举一反三
- **同类题目**：类似贪心预处理+分段极值的问题，如：
  - P1095 守望者的逃离（贪心+时间分配）
  - P3842 [TJOI2007]线段（动态规划+路径选择）
  - P5019 铺设道路（差分贪心）

### 个人心得摘录
- **调试经验**：作者QianhanOfficial提到通过绘制速度变化图，验证公式的正确性，强调预处理的重要性。
- **核心教训**：处理终点时需单独考虑加速可能性，避免遗漏边界情况。

---
处理用时：121.63秒