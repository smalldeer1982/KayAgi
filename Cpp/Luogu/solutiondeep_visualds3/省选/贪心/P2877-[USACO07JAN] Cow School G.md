# 题目信息

# [USACO07JAN] Cow School G

## 题目描述

Bessy is going to school and doing well. She has taken N (1 ≤ N ≤ 5000 -- except one case where 1 ≤ N ≤ 50,000) tests and recorded the scores (Ti points out of Pi points for test i; 0 ≤ Ti ≤ Pi < 40,000; 0 < Pi) as this task's input.

Her teacher will drop the D tests with the lowest percentage (Ti⁄Pi) before calculating Bessie's final grade (which is the sum of the remaining test score points over the sum of the remaining total test points). Bessy is good at math and quickly realizes that this does not benefit her as much as it might.

To prove her point, Bessy wants to find all values of D for which she could have ended up with a higher grade by choosing to drop different tests than the teacher would have. Help her by finding and printing all values of D for which this is possible.

Bessy has noted that, amazingly, she has never scored the same percentage on two different tests.

一个人参加了 $N$ 场考试，第 $i$ 场满分为 $P_i$，其得分为 $T_i$。现在要删去其中 $D$ 次考试的成绩，用剩下的总得分除以剩下的满分之和，作为其最终成绩。问对于哪些 $D$ 而言，删除得分比（即 $\dfrac{T_i}{P_i}$）最小的 $D$ 场得到的最终成绩不是最优的（用其他方法可以得到更高的最终成绩）。

## 样例 #1

### 输入

```
5
1 2
5 9
3 8
4 10
1 3```

### 输出

```
2
1
2```

# AI分析结果


### 💡 Kay的C++算法解析：Cow School G 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：分数规划 + 斜率优化/决策单调性分治

🗣️ **初步分析**：
> 本题核心是分数规划问题，可类比为"寻找最优配方"——通过删除部分考试，使剩余成绩的"浓度"（总分/总满分）最大化。关键步骤：
> 1. 按得分比 $T_i/P_i$ 排序考试
> 2. 对每个删除数量 $D$，计算默认方案成绩 $S_d/T_d$
> 3. 通过变换 $f(D)=\min_{i≤D}(T_d·P_i - S_d·T_i)$ 和 $g(D)=\max_{j>D}(T_d·P_j - S_d·T_j)$ 判断是否存在更优方案
> 
> **可视化设计**：
> - 采用8位像素风格，如《吃豆人》的网格界面展示考试排序
> - 删除操作时触发"消除音效"，成功替换时播放NES风格的胜利音效
> - 动态高亮当前比较的考试对（$i$与$j$），用不同颜色区分 $f(D)$ 和 $g(D)$ 的计算过程
> - 控制面板提供单步执行/调速滑块，观察凸包维护过程

---

#### 2. 精选优质题解参考
**题解一（javalyc）**
* **点评**：
  思路清晰展现分数规划到斜率优化的转化过程，代码规范（变量名`st/sp`含义明确）。亮点在于用CDQ分治解决凸包维护问题：  
  - 左区间归并排序保证 $x$ 单调  
  - 右区间斜率查询时利用 $st[i]/sp[i]$ 单调性优化  
  边界处理严谨（初始值设为±1e18），博客链接提供额外学习资源。

**题解二（jyz666）**
* **点评**：
  简洁高效实现决策单调性分治，代码仅40行但功能完整。亮点：  
  - 分治时暴力计算中点决策，利用决策点单调性缩小搜索范围  
  - 避免复杂数学推导，适合竞赛快速编码  
  变量命名稍简略（如`dl/dr`），但核心逻辑（`getf/getg`函数）可读性强。

**题解三（一颗赛艇）**
* **点评**：
  提供最简$O(n)$解法，亮点在于直接利用斜率性质：  
  - 证明 $T_d/S_d$ 单调递减，可用单调栈维护凸包  
  - 双指针技巧避免分治开销  
  代码包含详细数学证明链接，实践价值极高但实现细节需仔细揣摩。

---

#### 3. 核心难点辨析与解题策略
1. **难点1：分数规划模型转化**
   * **分析**：需将原问题转化为 $\max\{ \frac{\sum T}{\sum P} \}$ 形式。优质题解通过代数变形得到关键不等式 $T_dP_j - S_dT_j > T_dP_i - S_dT_i$，将问题转化为比较极值。
   * 💡 **学习笔记**：分数规划核心是构造 $F(λ)= \max\{ \sum(T_i - λP_i) \} ≥ 0$

2. **难点2：动态维护凸包**
   * **分析**：计算 $f(D)/g(D)$ 需在动态变化的点集中查询极值。javalyc用CDQ分治解决坐标无序问题；一颗赛艇利用 $T_d/S_d$ 单调性简化。
   * 💡 **学习笔记**：当查询斜率单调时，可用单调队列维护凸包；否则需分治或平衡树。

3. **难点3：决策单调性证明**
   * **分析**：jyz666的分治依赖决策点单调性质。关键观察：$T_d/S_d$ 随 $D$ 增加而递减，导致最优决策点单向移动。
   * 💡 **学习笔记**：打表验证决策单调性是实用技巧。

### ✨ 解题技巧总结
- **技巧1：问题等价转化**（例：将分式比较转化为线性不等式）
- **技巧2：离线处理动态查询**（CDQ分治解决"插入-查询"序列）
- **技巧3：利用单调性降维**（证明斜率/决策点单调避免二分）

---

#### 4. C++核心代码实现赏析
**通用核心实现参考**
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e4+5;
const ll INF=1e18;

struct Test { ll t, p; } a[N];
ll st[N], sp[N]; // 后缀和
double f[N], g[N]; // 极值存储
vector<int> ans;

int main() {
    int n; cin >> n;
    for(int i=1; i<=n; i++) 
        cin >> a[i].t >> a[i].p;
    
    // 按得分比排序
    sort(a+1, a+n+1, [](Test x, Test y){
        return x.t*y.p < y.t*x.p;
    });

    // 计算后缀和
    for(int i=n-1; i>=1; i--) {
        st[i] = st[i+1] + a[i+1].t;
        sp[i] = sp[i+1] + a[i+1].p;
    }

    // 计算极值（此处留空，可用CDQ/单调栈实现）
    // ...
    
    // 收集答案
    for(int i=1; i<n; i++)
        if(f[i] < g[i]) ans.push_back(i);
    
    cout << ans.size() << "\n";
    for(int d : ans) cout << d << "\n";
}
```

**题解一片段赏析（CDQ分治）**
```cpp
void CDQ_f(int l, int r) {
    if(l == r) return;
    int mid = (l+r)>>1, top=0;
    CDQ_f(l, mid); // 处理左半
    
    // 构建凸包（左区间）
    for(int i=l; i<=mid; i++) {
        while(top>1 && cross(q[top-1], q[top], i) <= 0) top--;
        q[++top] = i;
    }
    
    // 更新右区间f值
    for(int i=mid+1; i<=r; i++) {
        while(top>1 && calc(i, q[top-1]) >= calc(i, q[top])) top--;
        f[i] = max(f[i], calc(i, q[top]));
    }
    
    CDQ_f(mid+1, r); // 处理右半
    merge(l, r); // 归并排序
}
```
* **亮点**：分治处理凸包，避免 $x$ 无序问题
* **代码解读**：
  - `q[]` 维护上凸包（求最大值）
  - `cross` 计算叉积判断凸性
  - `calc(i,j)` 计算 $T_i·P_j - S_i·T_j$
* 💡 **学习笔记**：CDQ分治将动态问题转化为静态序列处理

**题解三片段赏析（单调栈）**
```cpp
// 计算g(D)（下凸包）
int top=0;
for(int i=n; i>=1; i--) {
    while(top>0 && a[i].p <= a[stk[top]].p) top--; // 横向过滤
    while(top>1 && cross(i, stk[top], stk[top-1])) top--; // 凸性维护
    stk[++top]=i;
    // 查询时用指针扫描凸包...
}
```
* **亮点**：$O(n)$ 复杂度完成极值查询
* 💡 **学习笔记**：斜率单调时，单调栈可替代分治

---

#### 5. 算法可视化：像素动画演示
<visualization_intro>
**像素探险家**在成绩迷宫中寻找最优路径！采用FC红白机风格，动态演示分数规划核心流程。
</visualization_intro>

* **主题**：8-bit成绩迷宫  
  - 考试化为彩色像素块（红：$T_i$，蓝：$P_i$，绿色深浅：得分比）
* **核心演示流程**：
  1. **初始化**：网格化排序结果，控制面板含调速滑块/单步执行
  2. **删除阶段**：
     - 点击"删除"D场：底部像素块爆炸特效 + "消除"音效
     - 显示当前成绩 $S_d/T_d$（顶部像素计数器）
  3. **极值查询**：
     - $f(D)$ 计算：左侧凸包绿色高亮，当前比较点闪烁黄光
     - $g(D)$ 计算：右侧凸包紫色高亮，触发"叮"声效
  4. **决策判定**：
     - 若 $f(D)<g(D)$：像素路径重组 + 胜利音效 + 金币掉落动画
     - 否则：灰色路径 + 低沉提示音
* **交互设计**：
  - **AI演示模式**：自动展示不同D值的决策过程
  - **比较视图**：分屏对比CDQ分治 vs 单调栈实现
  - **音效方案**：
    | 操作           | 音效            |
    |----------------|----------------|
    | 入栈/出栈      | 短促"滴"声     |
    | 极值更新       | 水晶音效       |
    | 成功替换       | 马里奥吃金币音 |

---

#### 6. 拓展练习与相似问题思考
* **技巧迁移**：
  1. 带权区间选择（如P5021赛道修建）
  2. 最优比率生成树（如P4951登山）
  3. 背包分数规划（如P4377 talent）

* **洛谷推荐**：
  1. **P4377** [Talent Show]  
     🗣️ 分数规划+背包，巩固代数转化技巧
  2. **P3199** [最优连通子集]  
     🗣️ 结合凸包维护，练习决策单调性证明
  3. **P4027** [货币兑换]  
     🗣️ 动态凸包经典题，强化CDQ分治应用

---

#### 7. 学习心得与经验分享
> **javalyc的调试经验**："凸包方向错误导致查询失效，通过绘制点集发现叉积计算反号"  
> **Kay点评**：验证凸包方向时，可用`右手定则`快速判断——若叉积>0应维护上凸包。建议用`matplotlib`可视化中间结果。

> **一颗赛艇的优化心得**："先写$O(n^2)$暴力，再逐步优化确保正确性"  
> **Kay点评**：分步优化是可靠策略，尤其适合斜率优化类问题。

---

通过本次分析，我们深入掌握了分数规划与凸包优化的核心技巧。记住：将分式比较转化为线性不等式是分数规划的钥匙，而凸包维护的本质是**利用单调性避免无效比较**。继续挑战新题目吧，少年！🚀

---
处理用时：131.93秒