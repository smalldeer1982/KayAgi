# 题目信息

# Bear and Paradox

## 题目描述

Limak is a big polar bear. He prepared $ n $ problems for an algorithmic contest. The $ i $ -th problem has initial score $ p_{i} $ . Also, testers said that it takes $ t_{i} $ minutes to solve the $ i $ -th problem. Problems aren't necessarily sorted by difficulty and maybe harder problems have smaller initial score but it's too late to change it — Limak has already announced initial scores for problems. Though it's still possible to adjust the speed of losing points, denoted by $ c $ in this statement.

Let $ T $ denote the total number of minutes needed to solve all problems (so, $ T=t_{1}+t_{2}+...+t_{n} $ ). The contest will last exactly $ T $ minutes. So it's just enough to solve all problems.

Points given for solving a problem decrease linearly. Solving the $ i $ -th problem after $ x $ minutes gives exactly ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/fc7b6e21f01df9be187009231b77169e209e48ba.png) points, where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/bafa872406a0b1a8fb62b20801e6fefc299422a3.png) is some real constant that Limak must choose.

Let's assume that $ c $ is fixed. During a contest a participant chooses some order in which he or she solves problems. There are $ n! $ possible orders and each of them gives some total number of points, not necessarily integer. We say that an order is optimal if it gives the maximum number of points. In other words, the total number of points given by this order is greater or equal than the number of points given by any other order. It's obvious that there is at least one optimal order. However, there may be more than one optimal order.

Limak assumes that every participant will properly estimate $ t_{i} $ at the very beginning and will choose some optimal order. He also assumes that testers correctly predicted time needed to solve each problem.

For two distinct problems $ i $ and $ j $ such that $ p_{i}&lt;p_{j} $ Limak wouldn't be happy to see a participant with strictly more points for problem $ i $ than for problem $ j $ . He calls such a situation a paradox.

It's not hard to prove that there will be no paradox for $ c=0 $ . The situation may be worse for bigger $ c $ . What is the maximum real value $ c $ (remember that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/bafa872406a0b1a8fb62b20801e6fefc299422a3.png)) for which there is no paradox possible, that is, there will be no paradox for any optimal order of solving problems?

It can be proved that the answer (the maximum $ c $ as described) always exists.

## 说明/提示

In the first sample, there are $ 3 $ problems. The first is $ (4,1) $ (initial score is $ 4 $ and required time is $ 1 $ minute), the second problem is $ (3,1) $ and the third one is $ (10,8) $ . The total time is $ T=1+1+8=10 $ .

Let's show that there is a paradox for $ c=0.7 $ . Solving problems in order $ 1 $ , $ 2 $ , $ 3 $ turns out to give the best total score, equal to the sum of:

1. solved $ 1 $ minute after the start: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/5d24fac1eb4d5cfcf64d9207f252db7e5c0491df.png)
2. solved $ 2 $ minutes after the start: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/f85b826c56f62f67a5d3d0474c30c9b216890f8c.png)
3. solved $ 10 $ minutes after the start: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF639E/c37a6ee62d21f25241df408bcd9cb5719cc26559.png)

So, this order gives $ 3.72+2.58+3=9.3 $ points in total and this is the only optimal order (you can calculate total scores for other $ 5 $ possible orders too see that they are lower). You should check points for problems $ 1 $ and $ 3 $ to see a paradox. There is $ 4&lt;10 $ but $ 3.72&gt;3 $ . It turns out that there is no paradox for $ c=0.625 $ but there is a paradox for any bigger $ c $ .

In the second sample, all $ 24 $ orders are optimal.

In the third sample, even for $ c=1 $ there is no paradox.

## 样例 #1

### 输入

```
3
4 3 10
1 1 8
```

### 输出

```
0.62500000000
```

## 样例 #2

### 输入

```
4
7 20 15 10
7 20 15 10
```

### 输出

```
0.31901840491
```

## 样例 #3

### 输入

```
2
10 20
10 1
```

### 输出

```
1.00000000000
```

# AI分析结果


### 💡 Kay的C++算法解析：Bear and Paradox 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：`贪心、二分答案`  
🗣️ **初步分析**：
> 解决本题需理解两个核心：  
> **贪心策略**：最优解题顺序按 $\frac{p_i}{t_i}$ 降序排列（想象按“性价比”排序商品）。  
> **二分答案**：答案 $c$ 具有单调性（$c$ 越大越可能出现悖论），可通过二分快速定位临界值。  
> - **核心难点**：处理 $\frac{p_i}{t_i}$ 相同的问题（可互换顺序），需计算每道题的最早/最晚完成时间。  
> - **可视化设计**：用像素时间轴展示问题解决顺序，高亮关键比较（$p_i < p_j$ 但得分反超）。  
> - **复古游戏化**：8位像素风格时间轴，问题化为方块移动；音效提示比较结果（胜利/失败音效）；控制面板支持单步执行和调速。

---

#### 2. 精选优质题解参考
**题解一（作者：Kinandra）**  
* **点评**：  
  思路清晰，从贪心证明到二分实现逻辑严密。代码规范（如 `cmppdivt` 排序函数），变量名 `tmin`/`tmax` 含义明确。亮点在于高效处理相同 $\frac{p_i}{t_i}$ 的问题段，通过双排序（先按比值、再按 $p$）实现 $O(n \log n)$ 复杂度，边界处理严谨。

**题解二（作者：xht）**  
* **点评**：  
  代码简洁但完整覆盖核心逻辑。亮点在于直接用 `p[i].l`/`p[i].r` 存储时间范围，避免额外数组；使用 `eps` 处理浮点精度问题，提高鲁棒性。实践价值高，代码可直接用于竞赛。

**题解三（作者：installb）**  
* **点评**：  
  详细推导贪心策略（邻项交换法），教学性强。亮点在于显式处理“段”的概念（`lst` 指针分段），帮助理解相同比值问题的完成时间计算，代码中 `st`/`ed` 变量命名直观。

---

#### 3. 核心难点辨析与解题策略
1. **难点：贪心策略的证明与实现**  
   * **分析**：通过邻项交换法推导最优顺序（若 $\frac{p_i}{t_i} > \frac{p_j}{t_j}$，则 $i$ 在前更优）。关键变量是比值 $\frac{p_i}{t_i}$ 和前缀和 $sum$。  
   * 💡 **学习笔记**：贪心策略依赖严谨的数学证明，邻项交换是经典验证手段。

2. **难点：处理相同比值的问题段**  
   * **分析**：当 $\frac{p_i}{t_i}$ 相同时，问题可任意交换顺序。需计算该段中每个问题的最早完成时间（段起始时间 + $t_i$）和最晚完成时间（段结束时间）。  
   * 💡 **学习笔记**：段内问题共享时间区间，但得分计算需独立处理。

3. **难点：高效检查悖论条件**  
   * **分析**：按 $p$ 升序排序后，维护 $p_j < p_i$ 的最大得分 $mx$。若 $p_i$ 的最小得分 $<$ $mx$ 则悖论发生。关键是用二分加速检查。  
   * 💡 **学习笔记**：排序后通过单次遍历比较，复杂度从 $O(n^2)$ 降至 $O(n)$。

✨ **解题技巧总结**：
- **技巧1：问题分解** — 将复杂问题拆解为贪心排序、二分框架、悖论检查三个子问题。  
- **技巧2：边界处理** — 特别注意相同比值问题和浮点精度（如 `eps=1e-9`）。  
- **技巧3：维护极值** — 按 $p$ 排序时动态维护 $mx$，避免重复计算。

---

#### 4. C++核心代码实现赏析
**本题通用核心C++实现参考**  
* **说明**：综合优质题解，包含贪心排序、时间范围计算和二分检查。  
* **完整核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 150000;
const double eps = 1e-9;
struct Problem { 
    long long p, t, minT, maxT; 
    double ratio() const { return 1.0 * p / t; }
};
Problem prob[N];
long long T;
int n;

bool cmpRatio(Problem a, Problem b) { 
    return a.p * b.t > b.p * a.t; // 按 p/t 降序
}

bool cmpP(Problem a, Problem b) { 
    return a.p < b.p; // 按 p 升序
}

bool check(double c) {
    double maxScore = 0;
    for (int i = 1; i <= n; ) {
        int j = i;
        while (j <= n && prob[j].p == prob[i].p) {
            double score = prob[j].p * (1 - c * prob[j].maxT / T);
            if (score < maxScore) return false; // 悖论检查
            j++;
        }
        // 更新 p_j < p_i 的最大得分
        for (int k = i; k < j; k++) 
            maxScore = max(maxScore, prob[k].p * (1 - c * prob[k].minT / T));
        i = j;
    }
    return true;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> prob[i].p;
    for (int i = 0; i < n; i++) cin >> prob[i].t, T += prob[i].t;
    
    sort(prob, prob + n, cmpRatio); // 按 p/t 排序
    long long sum = 0;
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && abs(prob[j].ratio() - prob[i].ratio()) < eps) j++;
        // 计算段内问题的 minT/maxT
        for (int k = i; k < j; k++) 
            prob[k].minT = sum + prob[k].t; // 最早完成时间
        for (int k = i; k < j; k++) 
            sum += prob[k].t;
        for (int k = i; k < j; k++) 
            prob[k].maxT = sum; // 最晚完成时间
        i = j;
    }
    
    sort(prob, prob + n, cmpP); // 按 p 排序
    double low = 0, high = 1;
    while (high - low > eps) {
        double mid = (low + high) / 2;
        check(mid) ? low = mid : high = mid;
    }
    printf("%.10f\n", low);
}
```
* **代码解读概要**：
  > 1. 按 $\frac{p_i}{t_i}$ 降序排序，计算相同比值问题的完成时间范围（`minT`/`maxT`）。  
  > 2. 按 $p$ 升序排序，二分 $c$ 检查悖论（$p_i$ 的最小得分 $\ge$ 所有 $p_j < p_i$ 的最大得分）。  
  > 3. 关键变量：`sum`（前缀和）、`minT`/`maxT`（时间范围）、`maxScore`（维护最大得分）。

**题解片段赏析**  
**题解一（Kinandra）片段**：
```cpp
for (int i = 1, j; i <= n; i = j + 1) {
    j = i;
    while (j < n && p[j + 1].p * p[i].t == p[i].p * p[j + 1].t) ++j;
    for (int k = i; k <= j; ++k) // 计算段内时间范围
        p[k].tmin = p[i - 1].sum + p[k].t;
    for (int k = i; k <= j; ++k) 
        p[k].tmax = p[j].sum;
}
```
* **亮点**：显式处理相同比值段，逻辑清晰。  
* **学习笔记**：相同比值问题共享时间区间，需批量计算。

**题解二（xht）片段**：
```cpp
sort(p + 1, p + n + 1, [&](P x, P y) { return x.p < y.p; });
ld ans = 1;
for (int i = 1; i < n; i++)
    if (p[i].p < p[i+1].p) {
        ld l = 1e8L, r = 0.0L;
        // 更新 p_i 的最小得分和 p_j 的最大得分
        if (l + eps < r) ans = min(ans, (p[i].p - p[i+1].p) / (l - r));
    }
```
* **亮点**：直接按 $p$ 排序后比较相邻问题，避免额外维护。  
* **学习笔记**：利用排序后的局部性，高效检查悖论。

---

### 5. 算法可视化：像素动画演示
<visualization_intro>  
**主题**：8位像素风格时间轴，问题化为彩色方块移动，模拟解题顺序与得分变化。  
**核心演示**：展示贪心排序、时间范围计算和悖论检查过程，融入音效与关卡机制。  
**设计思路**：复古风格降低理解门槛，游戏化元素（如得分/音效）增强学习动力。
</visualization_intro>

* **动画帧步骤**：
  1. **初始化**：  
     - 像素网格展示问题（颜色区分 $p_i$），底部控制面板（开始/单步/调速）。  
     - 8位背景音乐启动，时间轴从0延伸至 $T$。
  2. **贪心排序**：  
     - 方块按 $\frac{p_i}{t_i}$ 降序排列（高亮当前比较的方块，播放“叮”音效）。  
     - 相同比值方块同色，显示可互换提示。
  3. **时间范围计算**：  
     - 动态绘制前缀和进度条，相同比值段内方块共享时间区间（段边框闪烁）。  
     - 每段起始/结束播放“入队/出队”音效。
  4. **悖论检查**：  
     - 按 $p$ 排序后，从左到右扫描方块（扫描线高亮）。  
     - 当 $p_i < p_j$ 但 $i$ 的最小得分 $>$ $j$ 的最大得分时，触发红色警报和失败音效。  
     - 成功通过检查则播放胜利音效，方块变为金色。
  5. **交互控制**：  
     - **单步执行**：逐步展示排序、时间计算、比较过程。  
     - **自动演示**：AI自动运行（可调速），类似贪吃蛇自动解题。  
     - **关卡机制**：将排序、时间计算、二分检查设为三关，通关解锁下一阶段。

---

### 6. 拓展练习与相似问题思考
<similar_problems_intro>  
掌握贪心排序和二分框架后，可解决更多最优顺序和单调性问题。
</similar_problems_intro>

* **洛谷题目推荐**：
  1. **P1233 木棍加工**  
     🗣️ 推荐理由：贪心排序（双关键字）的直接应用，巩固邻项交换技巧。  
  2. **P1080 国王游戏**  
     🗣️ 推荐理由：复杂邻项交换证明，需推导最优排列策略。  
  3. **P2123 皇后游戏**  
     🗣️ 推荐理由：贪心结合数学归纳法，提升边界条件处理能力。

---

### 7. 学习心得与经验分享
<insights_intro>  
题解中的调试经验对解决浮点误差和边界问题极具参考价值。
</insights_intro>

> **参考经验（作者：樱雪喵）**：  
> “注意判断 $\frac{p_i}{t_i}$ 时使用足够小的 $\text{eps}$，否则会炸精度。”  
> **点评**：浮点数比较必须用 $\epsilon$ 容错（如 `1e-9`），这是数值算法的通用技巧。

---

<conclusion>  
通过本题，我们深入理解了贪心策略的证明方法、二分答案的框架设计，以及如何避免浮点精度陷阱。下次遇到最优顺序问题时，不妨尝试邻项交换法！🚀  
</conclusion>

---
处理用时：132.48秒