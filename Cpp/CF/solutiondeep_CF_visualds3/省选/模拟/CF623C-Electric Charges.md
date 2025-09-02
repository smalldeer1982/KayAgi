# 题目信息

# Electric Charges

## 题目描述

Programmer Sasha is a student at MIPT (Moscow Institute of Physics and Technology) and he needs to make a laboratory work to pass his finals.

A laboratory unit is a plane with standard coordinate axes marked on it. Physicists from Moscow Institute of Physics and Technology charged the axes by large electric charges: axis $ X $ is positive and axis $ Y $ is negative.

Experienced laboratory worker marked $ n $ points with integer coordinates $ (x_{i},y_{i}) $ on the plane and stopped the time. Sasha should use "atomic tweezers" to place elementary particles in these points. He has an unlimited number of electrons (negatively charged elementary particles) and protons (positively charged elementary particles). He can put either an electron or a proton at each marked point. As soon as all marked points are filled with particles, laboratory worker will turn on the time again and the particles will come in motion and after some time they will stabilize in equilibrium. The objective of the laboratory work is to arrange the particles in such a way, that the diameter of the resulting state (the maximum distance between the pairs of points of the set) is as small as possible.

Since Sasha is a programmer, he naively thinks that all the particles will simply "fall" into their projections on the corresponding axes: electrons will fall on axis $ X $ , while protons will fall on axis $ Y $ . As we are programmers too, we will consider the same model as Sasha. That is, a particle gets from point $ (x,y) $ to point $ (x,0) $ if it is an electron and to point $ (0,y) $ if it is a proton.

As the laboratory has high background radiation and Sasha takes care of his laptop, he did not take it with him, and now he can't write a program that computes the minimum possible diameter of the resulting set. Therefore, you will have to do it for him.

Print a square of the minimum possible diameter of the set.

## 说明/提示

In the first sample Sasha puts electrons at all points, all particles eventually fall at a single point $ (1,0) $ .

In the second sample Sasha puts an electron at point $ (1,10) $ , and a proton at point $ (10,1) $ . The result is a set of two points $ (1,0) $ and $ (0,1) $ , which has a diameter of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF623C/2826342a15affce70e459206e8466cd2b66552a3.png).

## 样例 #1

### 输入

```
3
1 10
1 20
1 30
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2
1 10
10 1
```

### 输出

```
2
```

# AI分析结果

---
# 💡 Kay的C++算法解析：Electric Charges 深入学习指南 💡

<introduction>
今天我们来一起分析“Electric Charges”这道C++编程题。这道题的核心是通过合理选择每个点投影到x轴或y轴，使得最终所有投影点的最大距离平方最小。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`二分答案 + 双指针 + 预处理极值`  

🗣️ **初步分析**：  
解决这道题的关键在于“二分答案”——我们需要找到最小的直径平方（记为`mid`），并判断是否存在一种投影方式（部分点投影到x轴，其余到y轴）使得所有投影点的最大距离不超过`mid`。  

简单来说，“二分答案”就像用“猜数字”的方法找最小值：先假设一个`mid`，验证是否可行；若可行则尝试更小的`mid`，否则增大`mid`。这个过程通过二分法快速缩小范围。  

在本题中，判断“是否存在可行投影”是难点。优质题解通常通过以下步骤实现：  
1. **排序与预处理**：将点按x坐标排序，预处理前缀/后缀的y坐标极值（最小、最大值），便于快速计算Y集合（投影到y轴的点）的最大距离。  
2. **双指针确定X集合范围**：枚举X集合的左端点，用双指针找到最远的右端点，使得X集合内的x坐标差平方不超过`mid`。  
3. **验证Y集合条件**：剩余点（Y集合）的y坐标差平方需≤`mid`，且X集合的最大x平方 + Y集合的最大y平方需≤`mid`。  

可视化设计中，我们可以用像素网格展示所有点，用不同颜色区分X/Y集合（如X点为红色，Y点为蓝色）。双指针移动时，用像素箭头标注当前处理的左右端点；预处理的极值用动态文本框显示。关键条件验证时（如x差平方是否≤mid），触发“叮”的音效并高亮相关点。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性等维度的评估，以下题解因逻辑清晰、实现高效被选为优质参考：
</eval_intro>

**题解一：作者9AC8E2**  
* **点评**：此题解巧妙结合了二分答案与双指针法，通过预处理前缀/后缀的y极值（`l_min`/`l_max`/`r_min`/`r_max`）快速验证Y集合的条件。代码中`check`函数逻辑明确，枚举X集合的左右端点并动态调整范围，确保了时间复杂度的优化（O(n log max_ans)）。变量命名虽略简略（如`l_min`表示前缀y最小值），但结合注释易理解。实践价值高，可直接用于竞赛。

**题解二：作者紊莫**  
* **点评**：此题解思路更“自然”，双指针维护X集合的极长段（`l`到`r`），并通过交换x/y轴两次二分（取最小值）确保全面性。代码变量名（如`pmn`前缀y最小、`smx`后缀y最大）直观易懂，`ck`函数封装了关键验证逻辑，结构清晰。特别地，作者提到的“hack样例”提示了边界条件的重要性，对学习者有启发。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决本题时，以下三个关键点最易卡壳，结合优质题解的共性，我们逐一分析：
</difficulty_intro>

1.  **关键点1**：如何高效判断“是否存在可行投影方式”？  
    * **分析**：直接枚举所有可能的投影方式（2ⁿ种）不可行，因此需用“二分答案”+“双指针”缩小范围。双指针通过维护X集合的左右端点（`l`到`r`），确保X集合内的x差平方≤`mid`，剩余点自动归为Y集合。预处理Y的极值（前缀/后缀的y最小、最大）可快速计算Y集合的最大距离。  
    * 💡 **学习笔记**：双指针+预处理极值是解决“区间极值验证”问题的常用组合。

2.  **关键点2**：如何处理X与Y集合的交互条件？  
    * **分析**：除了X集合内的x差平方≤`mid`、Y集合内的y差平方≤`mid`，还需满足X的最大x平方 + Y的最大y平方≤`mid`（因两点分别在x轴和y轴时，距离平方为x²+y²）。预处理Y的极值后，可快速计算此条件。  
    * 💡 **学习笔记**：多条件验证时，需明确各条件的数学表达式，并通过预处理简化计算。

3.  **关键点3**：如何避免遗漏边界情况？  
    * **分析**：例如，所有点投影到x轴（Y集合为空）或所有点投影到y轴的情况。优质题解通过初始化`ans`为全x或全y的最大距离平方，确保这些情况被覆盖。  
    * 💡 **学习笔记**：初始化时考虑极端情况（如全选X或全选Y）是避免漏解的关键。

### ✨ 解题技巧总结  
- **二分答案的下界与上界**：下界为0（所有点投影到同一点），上界为全x或全y的最大距离平方（初始`ans`）。  
- **预处理极值数组**：前缀/后缀的极值数组（如`pmn`/`pmx`）可O(1)查询任意区间的极值，大幅提升效率。  
- **双指针维护极长区间**：固定左端点`l`，右端点`r`尽可能右移（满足x差平方≤`mid`），确保覆盖所有可能的X集合。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合两个优质题解的思路，提炼出一个逻辑清晰、实现高效的通用核心代码。
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：本代码综合了9AC8E2和紊莫的题解思路，采用二分答案+双指针+预处理极值的方法，覆盖全x/全y的边界情况，并通过交换x/y轴两次二分确保最优解。  
* **完整核心代码**：  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
const ll INF = 1e18;

struct Point { ll x, y; } p[N];
int n;
ll pmn[N], pmx[N], smn[N], smx[N]; // 前缀/后缀y的最小、最大值

ll sqr(ll x) { return x * x; }

// 检查当X集合为[l..r]时，是否满足条件，mid为当前尝试的直径平方
bool check(ll mid, int axis) {
    if (axis == 0) sort(p + 1, p + n + 1, [](Point a, Point b) { return a.x < b.x; });
    else sort(p + 1, p + n + 1, [](Point a, Point b) { return a.y < b.y; });

    // 预处理前缀、后缀y极值（若axis=1，实际处理的是x的极值）
    pmn[0] = INF, pmx[0] = -INF;
    for (int i = 1; i <= n; ++i) {
        pmn[i] = min(pmn[i - 1], (axis == 0 ? p[i].y : p[i].x));
        pmx[i] = max(pmx[i - 1], (axis == 0 ? p[i].y : p[i].x));
    }
    smn[n + 1] = INF, smx[n + 1] = -INF;
    for (int i = n; i >= 1; --i) {
        smn[i] = min(smn[i + 1], (axis == 0 ? p[i].y : p[i].x));
        smx[i] = max(smx[i + 1], (axis == 0 ? p[i].y : p[i].x));
    }

    // 双指针维护X集合的l..r
    for (int l = 1, r = 1; l <= n; ++l) {
        while (r < n) {
            ll dx = (axis == 0 ? p[r + 1].x - p[l].x : p[r + 1].y - p[l].y);
            if (sqr(dx) > mid) break;
            r++;
        }
        // 计算Y集合的极值（前缀l-1和后缀r+1的极值）
        ll y_min = min(pmn[l - 1], smn[r + 1]);
        ll y_max = max(pmx[l - 1], smx[r + 1]);
        if (y_min == INF) y_min = y_max; // Y集合为空

        // 验证Y集合的y差平方≤mid
        if (sqr(y_max - y_min) > mid) continue;

        // 计算X集合的最大x平方（或y平方，若axis=1）
        ll x_max_sq = (axis == 0 ? sqr(p[r].x) : sqr(p[r].y));
        // 验证x_max_sq + y_max_sq ≤ mid（两点分别在x轴和y轴时的距离平方）
        if (x_max_sq + sqr(y_max) <= mid) return true;
        if (x_max_sq + sqr(y_min) <= mid) return true;
    }
    return false;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;

    // 初始答案为全x或全y的最大距离平方
    ll ans = INF;
    ll max_x = -INF, min_x = INF, max_y = -INF, min_y = INF;
    for (int i = 1; i <= n; ++i) {
        max_x = max(max_x, p[i].x); min_x = min(min_x, p[i].x);
        max_y = max(max_y, p[i].y); min_y = min(min_y, p[i].y);
    }
    ans = min(ans, sqr(max_x - min_x));
    ans = min(ans, sqr(max_y - min_y));

    // 二分答案（先处理x轴为X集合，再处理y轴为X集合）
    ll l = 0, r = 4e18;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid, 0)) r = mid - 1, ans = min(ans, mid);
        else l = mid + 1;
    }
    l = 0, r = 4e18;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid, 1)) r = mid - 1, ans = min(ans, mid);
        else l = mid + 1;
    }

    cout << ans << endl;
    return 0;
}
```
* **代码解读概要**：  
  代码首先预处理全x或全y的最大距离平方作为初始答案。通过`check`函数（支持切换x/y轴）判断当前`mid`是否可行：排序后预处理极值数组，双指针维护X集合的`l..r`，验证Y集合的条件。最后两次二分（x轴和y轴分别作为X集合）取最小值，确保覆盖所有可能情况。

---
<code_intro_selected>
接下来，我们剖析两个优质题解的核心代码片段，学习其亮点：
</code_intro_selected>

**题解一：作者9AC8E2**  
* **亮点**：预处理前缀/后缀的y极值（`l_min`/`l_max`/`r_min`/`r_max`），快速计算Y集合的极值，双指针动态调整X集合的右端点。  
* **核心代码片段**：  
```cpp
bool check(long long mid) {
    int r = 1;
    for (int l = 1; l <= n; l++) { // 枚举X集合的左端点
        if (v[l].x > 0) break; // 按x排序后，左端点应为负或小值
        while (abs(v[r + 1].x) <= abs(v[l].x) && sqr(v[r + 1].x - v[l].x) <= mid && r + 1 <= n) r++;
        // 验证X集合和Y集合的条件...
    }
}
```
* **代码解读**：  
  `l`是X集合的左端点，`r`是动态调整的右端点，确保X集合内的x差平方≤`mid`。`abs(v[r + 1].x) <= abs(v[l].x)`确保X集合的x绝对值不超过左端点（避免大值干扰）。通过预处理的极值数组，快速计算Y集合的极值并验证条件。  
* 💡 **学习笔记**：双指针的移动条件需同时满足x差平方和绝对值约束，确保X集合的有效性。

**题解二：作者紊莫**  
* **亮点**：交换x/y轴两次二分，确保覆盖所有投影情况；`ck`函数封装验证逻辑，结构清晰。  
* **核心代码片段**：  
```cpp
int ck(int l, int r, int mid) {
    int mn = min(pmn[l - 1], smn[r + 1]); // Y集合的y最小值
    int mx = max(pmx[l - 1], smx[r + 1]); // Y集合的y最大值
    if (pf(mx - mn) <= mid) { // Y集合的y差平方≤mid
        // 计算X集合（l..r）与Y集合点的最大距离平方
        int d = max({dis({p[l].x, 0}, {0, mx}), dis({p[l].x, 0}, {0, mn}),
                     dis({p[r].x, 0}, {0, mn}), dis({p[r].x, 0}, {0, mx})});
        return d <= mid;
    }
    return 0;
}
```
* **代码解读**：  
  `ck`函数验证X集合（`l..r`）和Y集合的条件：Y的y差平方≤`mid`，且X的端点（`p[l].x`和`p[r].x`）与Y的极值点（`mx`和`mn`）的距离平方≤`mid`。通过`max`函数覆盖所有可能的点对，确保验证全面。  
* 💡 **学习笔记**：封装关键验证逻辑（如`ck`函数）可提升代码可读性，避免重复代码。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解“二分答案+双指针”的过程，我们设计一个“像素实验室”动画，用8位复古风格展示点的投影选择和条件验证。
</visualization_intro>

  * **动画演示主题**：`像素粒子投影实验`  
  * **核心演示内容**：展示二分答案的搜索过程，双指针调整X集合范围，Y集合极值的动态计算，以及各条件（x差平方、y差平方、x²+y²）的验证。  

  * **设计思路简述**：  
    采用FC红白机风格的像素网格（16色，如红色X点、蓝色Y点），通过颜色高亮当前处理的X集合（`l..r`）。双指针移动时，用黄色箭头标注`l`和`r`的位置；极值计算时，用动态文本框显示`pmn`/`pmx`等值。关键条件验证（如x差平方≤mid）触发“叮”的音效，增强操作记忆。

  * **动画帧步骤与交互关键点**：  

    1.  **初始化场景**：  
        - 像素网格中显示所有点（绿色方块），顶部显示“当前mid值”和“是否可行”状态。  
        - 控制面板包含：单步/自动播放按钮、速度滑块、重置按钮。  

    2.  **二分搜索过程**：  
        - 初始`l=0`，`r=4e18`，mid值动态更新（如从大到小收缩）。  
        - 每次计算mid后，触发`check`函数的动画。  

    3.  **check函数演示**：  
        - 点按x排序（像素点从左到右排列），X集合的`l`（红色箭头）从左到右移动，`r`（蓝色箭头）尽可能右移（满足x差平方≤mid）。  
        - Y集合的点（蓝色方块）显示为`l-1`和`r+1`区间外的点，动态计算其y极值（文本框显示`mn`和`mx`）。  
        - 验证条件时，相关点闪烁（如x差超过mid时，`l`和`r`点红色闪烁；y差超过mid时，Y集合点蓝色闪烁）。  

    4.  **目标达成**：  
        - 找到最小mid时，所有点变为金色，播放“胜利”音效（如8位音乐的上升调），显示“最小直径平方：mid”。  

  * **旁白提示**：  
    - “当前尝试mid=100，检查是否存在投影方式…”  
    - “X集合的l=1，r=3，x差平方=25≤100，符合条件！”  
    - “Y集合的y极值为5和15，y差平方=100≤100，继续验证x²+y²…”  

<visualization_conclusion>
通过这样的动画，我们能直观看到二分法如何缩小范围，双指针如何调整X集合，以及各条件如何验证，从而更深刻理解算法逻辑。
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心思路（二分答案+双指针+预处理极值）适用于多种“最小化最大值”问题。以下是相关拓展练习：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - 最小化最大距离（如仓库选址问题）。  
    - 最小化最大等待时间（如任务分配问题）。  
    - 最小化最大资源消耗（如网络带宽分配问题）。  

  * **练习推荐 (洛谷)**：  
    1.  **洛谷 P1824 进击的奶牛**  
        * 🗣️ **推荐理由**：经典“最小化最大距离”问题，需用二分答案+排序+贪心，与本题思路类似。  
    2.  **洛谷 P3853 [TJOI2007]路标设置**  
        * 🗣️ **推荐理由**：通过二分答案判断“添加路标后最大间距是否≤mid”，双指针验证，锻炼条件判断能力。  
    3.  **洛谷 P4392 [BOI2007]Mokia 摩基亚**  
        * 🗣️ **推荐理由**：二维前缀和+二分答案，拓展二维场景下的极值处理技巧。  

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本题解中，作者紊莫提到：“不理解的可以看这一组hack样例，答案是20。” 这提示我们：
</insights_intro>

> **参考经验**：“在验证算法时，构造边界样例（如多个点的x/y分布复杂的情况）能有效暴露逻辑漏洞。例如，当X集合的范围选择不当时，可能遗漏更优解。”  
> **点评**：这位作者的经验很实用！在编程中，主动构造hack样例（如全正/全负点、x/y交叉分布）是验证代码鲁棒性的关键。遇到卡壳时，手动模拟小数据（如样例输入）能快速定位问题。

-----

<conclusion>
本次关于“Electric Charges”的C++解题分析就到这里。希望这份指南能帮助大家掌握二分答案、双指针和预处理极值的核心技巧。记住，多动手编写代码、构造测试样例，是提升算法能力的关键！下次我们再一起探索新的编程挑战！💪
</conclusion>

---
处理用时：156.82秒