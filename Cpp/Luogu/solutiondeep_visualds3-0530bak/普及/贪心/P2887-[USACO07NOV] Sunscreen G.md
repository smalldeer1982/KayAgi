# 题目信息

# [USACO07NOV] Sunscreen G

## 题目描述

To avoid unsightly burns while tanning, each of the C (1 ≤ C ≤ 2500) cows must cover her hide with sunscreen when they're at the beach. Cow i has a minimum and maximum SPF rating (1 ≤ minSPFi ≤ 1,000; minSPFi ≤ maxSPFi ≤ 1,000) that will work. If the SPF rating is too low, the cow suffers sunburn; if the SPF rating is too high, the cow doesn't tan at all........

The cows have a picnic basket with L (1 ≤ L ≤ 2500) bottles of sunscreen lotion, each bottle i with an SPF rating SPFi (1 ≤ SPFi ≤ 1,000). Lotion bottle i can cover coveri cows with lotion. A cow may lotion from only one bottle.

What is the maximum number of cows that can protect themselves while tanning given the available lotions?

有C个奶牛去晒太阳 (1 <=C <= 2500)，每个奶牛各自能够忍受的阳光强度有一个最小值和一个最大值，太大就晒伤了，太小奶牛没感觉。

而刚开始的阳光的强度非常大，奶牛都承受不住，然后奶牛就得涂抹防晒霜，防晒霜的作用是让阳光照在身上的阳光强度固定为某个值。

那么为了不让奶牛烫伤，又不会没有效果。

给出了L种防晒霜。每种的数量和固定的阳光强度也给出来了

每个奶牛只能抹一瓶防晒霜，最后问能够享受晒太阳的奶牛有几个。


## 样例 #1

### 输入

```
3 2
3 10
2 5
1 5
6 2
4 1```

### 输出

```
2```

# AI分析结果



### 综合分析与结论
#### 核心贪心策略分析
1. **右端点优先策略**  
   - 将牛的区间按右端点升序排序，防晒霜按SPF升序排序  
   - 每次选择满足当前牛区间的最小可用SPF值  
   - **正确性证明**：优先处理右端点小的区间，避免大区间占用小SPF值  
   - 时间复杂度：O(C*L)，适合题目给定的数据规模  

2. **左端点优先策略**  
   - 将牛的区间按左端点降序排序，防晒霜按SPF降序排序  
   - 每次选择满足当前牛区间的最大可用SPF值  
   - **正确性证明**：优先处理左端点大的区间，最大化SPF利用率  
   - 时间复杂度：O(C*L)，实现更简洁  

#### 算法难点对比
| 策略           | 排序依据               | 贪心选择逻辑           | 实现复杂度 | 正确性验证难度 |
|----------------|------------------------|------------------------|------------|----------------|
| 右端点优先     | 牛右端点升序 + SPF升序 | 取第一个覆盖区间的SPF | 中         | 较高           |
| 左端点优先     | 牛左端点降序 + SPF降序 | 取最后一个覆盖区间的SPF| 低         | 中等           |

### 题解清单（≥4星）
#### 1. 翼德天尊（⭐⭐⭐⭐⭐）
- **核心思路**：右端点排序 + 双循环贪心  
- **亮点**：用反例验证排序策略正确性，代码简洁高效  
- **代码片段**：
```cpp
sort(cow+1,cow+c+1,cmp); // 按右端点排序
sort(fss+1,fss+l+1,cmp1); // 按SPF升序
for (每头牛) {
    for (每种防晒霜) {
        if (在区间内) { 使用并break; }
    }
}
```

#### 2. 陷语（⭐⭐⭐⭐）
- **核心思路**：左端点降序排序 + 最大可用SPF优先  
- **亮点**：给出严格数学证明，通过SPF利用率最大化保证正确性  
- **代码片段**：
```cpp
sort(a, a+c, [](Cow a, Cow b){return a.minSPF > b.minSPF;});
sort(lotion, lotion+l, [](SunScreen a, SunScreen b){return a.SPF > b.SPF;});
for (每种防晒霜) {
    for (每头牛) {
        if (在区间内) { 使用并break; }
    }
}
```

#### 3. 追梦_Chen（⭐⭐⭐⭐）
- **核心思路**：左端点降序排序 + 优先队列优化  
- **亮点**：用优先队列动态维护可用区间，时间复杂度优化至O(C log C)  
- **关键代码**：
```cpp
priority_queue<int> q;
for (防晒霜按SPF降序) {
    while (牛的左端点 >= SPF) { q.push(牛右端点); }
    while (!q.empty() && q.top() < SPF) { q.pop(); }
    while (剩余数量--) { q.pop(); ans++; }
}
```

### 最优思路与技巧提炼
1. **排序策略选择**  
   - **右端点排序**：保证小范围优先使用小SPF值  
   - **左端点降序**：确保大SPF值优先用于高需求区间  

2. **贪心验证方法**  
   - **交换论证法**：若存在更优解，必能通过交换步骤转化为当前策略的解  
   - **极值法**：总存在一个最优解包含当前策略的第一个选择  

3. **实现优化技巧**  
   - 双排序后双循环匹配（O(C*L)）  
   - 优先队列维护可用区间（O(C log C)）  

### 同类型题目推荐
1. **P1230 智力大冲浪** - 贪心选择截止时间最近的区间  
2. **P1209 [USACO1.3]修理牛棚 Barn Repair** - 区间覆盖与间隔选择  
3. **P2882 [USACO07MAR]Face The Right Way G** - 贪心反转策略  

### 可视化设计（复古像素风格）
#### 动画要素
1. **元素展示**  
   - 牛区间：用不同颜色线段表示[minSPF, maxSPF]  
   - 防晒霜：像素方块表示SPF值，数量用堆叠高度表示  

2. **贪心过程**  
   - **高亮当前牛**：闪烁黄色边框  
   - **匹配过程**：从防晒霜列表扫描，匹配成功时播放"滴"声  
   - **淘汰不可用**：灰色半透明处理  

3. **控制面板**  
   - 速度调节滑块（1x-5x）  
   - 暂停/继续/单步执行按钮  
   - 当前匹配计数显示  

#### 音效设计
- **正确匹配**：8-bit上升音阶（C4→E4→G4）  
- **错误尝试**：低音蜂鸣（100Hz方波）  
- **关卡完成**：马里奥过关音效  

### 核心代码实现（贪心+双排序）
```cpp
// 翼德天尊策略实现
#include <bits/stdc++.h>
using namespace std;

struct Cow { int l, r; };
struct Sunscreen { int spf, cnt; };

int main() {
    int C, L;
    cin >> C >> L;
    vector<Cow> cows(C);
    vector<Sunscreen> suns(L);
    for (auto &c : cows) cin >> c.l >> c.r;
    for (auto &s : suns) cin >> s.spf >> s.cnt;
    
    sort(cows.begin(), cows.end(), [](auto a, auto b) { 
        return a.r < b.r; // 按右端点升序
    });
    sort(suns.begin(), suns.end(), [](auto a, auto b) {
        return a.spf < b.spf; // 按SPF升序
    });
    
    int ans = 0;
    for (auto &c : cows) {
        for (auto &s : suns) {
            if (s.cnt > 0 && s.spf >= c.l && s.spf <= c.r) {
                s.cnt--;
                ans++;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```

### 总结与心得
- **贪心选择的关键**在于排序策略的合理性，需结合区间覆盖特性  
- **调试技巧**：构造极端测试数据（如全区间相同、SPF值边界情况）  
- **性能优化**：当C/L较大时，优先队列策略更优，但需注意实现复杂度  
- **可视化价值**：动态展示排序和匹配过程能极大提升算法理解效率

---
处理用时：73.96秒