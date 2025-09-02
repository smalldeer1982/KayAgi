# 题目信息

# [USACO09DEC] Selfish Grazing S

## 题目描述

Each of Farmer John's N (1 <= N <= 50,000) cows likes to graze in a certain part of the pasture, which can be thought of as a large one-dimeensional number line. Cow i's favorite grazing range starts at location S\_i and ends at location E\_i (1 <= S\_i < E\_i; S\_i < E\_i <= 100,000,000).

Most folks know the cows are quite selfish; no cow wants to share any of its grazing area with another. Thus, two cows i and j can only graze at the same time if either S\_i >= E\_j or E\_i <= S\_j. FJ would like to know the maximum number of cows that can graze at the same time for a given set of cows and their preferences.

Consider a set of 5 cows with ranges shown below:

```cpp
  ... 1    2    3    4    5    6    7    8    9   10   11   12   13 ...
  ... |----|----|----|----|----|----|----|----|----|----|----|----|----
Cow 1:      <===:===>          :              :              :
Cow 2: <========:==============:==============:=============>:
Cow 3:          :     <====>   :              :              :
Cow 4:          :              :     <========:===>          :
Cow 5:          :              :     <==>     :              :
```
These ranges represent (2, 4), (1, 12), (4, 5), (7, 10), and (7, 8), respectively.

For a solution, the first, third, and fourth (or fifth) cows can all graze at the same time. If the second cow grazed, no other cows could graze. Also, the fourth and fifth cows cannot graze together, so it is impossible for four or more cows to graze.

约翰有N(1≤N≤50000)头牛，约翰的草地可以认为是一条直线．每只牛只喜欢在某个特定的范围内吃草．第i头牛喜欢在区间(Si，Ei)吃草，1≤Si<Ei≤1,000,000,00.

奶牛们都很自私，他们不喜欢和其他奶牛共享自己喜欢吃草的领域，因此约翰要保证任意

两头牛都不会共享他们喜欢吃草昀领域．如果奶牛i和奶牛J想要同时吃草，那么要满足：Si>=Ej或者Ei≤Sj．约翰想知道在同一时刻，最多可以有多少头奶牛同时吃草？


## 样例 #1

### 输入

```
5 
2 4 
1 12 
4 5 
7 10 
7 8 
```

### 输出

```
3 
```

# AI分析结果



### 综合分析与结论

**题目核心**：在数轴区间调度问题中，通过贪心策略选择最多不重叠的区间。  
**算法要点**：将区间按右端点升序排列，依次选取不重叠的区间。  
**解决难点**：正确选择排序依据（右端点）并证明贪心策略的全局最优性。  
**可视化思路**：通过排序后的逐步选择动画，高亮当前选中区间和可用区间，展示贪心决策的影响。

---

### 题解评分（≥4星）

1. **微香玉烛暗（4.5星）**  
   - **亮点**：详细样例分析 + 代码逐行注释，解释排序策略和遍历逻辑。  
   - **心得引用**：*"每次用开始时间比较，并更新$ans$"* 强调贪心选择的核心。

2. **wubaiting2020（4星）**  
   - **亮点**：代码简洁清晰，结构体排序与遍历逻辑直观，适合快速理解。  
   - **关键代码**：`if(a[i].x>=t)` 直接体现贪心条件判断。

3. **CloudStroll（4星）**  
   - **亮点**：对比贪心与DP的适用场景，拓展思维。  
   - **引用**：*"如果要求算奶牛的草场总长则应该用dp"* 深化问题理解。

---

### 最优思路与技巧提炼

**核心贪心策略**：  
1. **排序依据**：按区间右端点升序排列，确保每次选择结束最早的区间。  
2. **遍历逻辑**：初始化结束点为第一个区间的右端点，后续选择左端点≥当前结束点的区间，并更新结束点。  
3. **正确性证明**：选择结束最早的区间能为后续留下更多可用空间，局部最优推导全局最优。

**代码实现关键**：  
```cpp
// 结构体定义与排序
struct node { int x, y; };
bool cmp(node a, node b) { return a.y < b.y; }
sort(a+1, a+n+1, cmp);

// 贪心遍历
int ans = 1, end = a[1].y;
for (int i=2; i<=n; i++) {
    if (a[i].x >= end) {
        ans++;
        end = a[i].y;
    }
}
```

---

### 同类型题与算法套路

**常见贪心应用场景**：  
- 区间调度（最大不重叠区间数）  
- 最小点覆盖（用最少的点覆盖所有区间）  
- 区间合并（重叠区间的合并策略）  

**推荐题目**：  
1. 洛谷 P1803 【线段覆盖】  
2. 洛谷 P1937 【仓配间的连线】  
3. 洛谷 P1255 【数轴上的跳跃】  

---

### 可视化与算法演示方案

**核心动画设计**：  
1. **排序展示**：数轴上动态绘制初始区间，按右端点排序后重新排列。  
2. **贪心选择**：  
   - **高亮当前区间**：绿色标记当前选中区间（右端点最小）。  
   - **可用区间标记**：蓝色显示左端点≥当前结束点的候选区间。  
3. **状态更新**：红色更新当前结束点，计数器递增。  

**复古游戏化设计**：  
- **像素风格**：Canvas绘制数轴和区间方块，8-bit音效（选择时“叮”，错误“哔”）。  
- **自动演示**：AI模式逐步选择，显示已选数量，积分+10/步。  
- **交互功能**：暂停/继续、速度调节、手动点击选择验证。  

**关键交互代码（伪代码）**：  
```javascript
// 排序后遍历
let end = sortedIntervals[0].y;
let selected = [sortedIntervals[0]];
for (let i=1; i<sortedIntervals.length; i++) {
    if (sortedIntervals[i].x >= end) {
        selected.push(sortedIntervals[i]);
        end = sortedIntervals[i].y;
        playSound('select'); // 播放选择音效
    }
}
```

---

### 个人心得摘录

- **调试教训**：初始未将`ans`设为1导致少计数（如：user48442的代码）。  
- **顿悟时刻**：*"按右端点排序后，第一个必选，全局最优由此展开"*（微香玉烛暗）。  
- **优化技巧**：稳定排序（`stable_sort`）在某些实现中更高效（hylong的题解）。  

---

### 总结

本题通过经典的贪心策略解决区间调度问题，核心在于排序依据的选择与遍历逻辑的实现。可视化设计通过动态排序和选择过程，直观展示贪心策略的优越性，复古游戏化元素增强学习趣味性。

---
处理用时：75.40秒