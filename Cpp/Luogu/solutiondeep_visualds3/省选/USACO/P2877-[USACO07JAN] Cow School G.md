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
✨ **本题主要考察**：`分数规划`与`决策单调性优化`  
🗣️ **初步分析**：  
> 解决"牛校"题目的核心在于将成绩优化问题转化为**分数规划模型**，结合斜率优化实现高效求解。简单来说，就像在多个分数中找出最佳组合，使总成绩最高。  
> - 关键思路：将原问题转化为比较交换元素的收益（`T_i*T_d - S_d*P_i`），通过分治策略高效计算极值  
> - 难点：动态斜率变化导致直接计算复杂度高，需用决策单调性分治或CDQ分治优化  
> - 可视化设计：用像素网格展示考试分布（横轴P_i，纵轴T_i），动态绘制凸包构建过程。在分治阶段，左区间点变绿色，右区间点变蓝色，凸包连线用黄色闪烁动画，查询扫描线用红色表示，关键比较步骤触发8-bit音效  

---

#### 2. 精选优质题解参考
**题解一（javalyc - CDQ分治）**  
* **点评**：思路清晰度 ★★★★★  
  巧妙将分数规划转化为凸包查询问题，详细推导了斜率优化过程。代码规范性极强（变量名`st/sp`含义明确），采用CDQ分治处理非单调性问题，逻辑严谨。空间复杂度优化到O(n)，特别适合大型数据集实践  
  亮点：完整注释+数学推导，博客提供额外学习资源  

**题解二（jyz666 - 决策单调性分治）**  
* **点评**：算法有效性 ★★★★☆  
  用更简短的代码实现决策单调性分治，核心函数仅15行。虽解释较少但代码自文档化强（如`getf()`函数），实践价值高。时间复杂度O(n log n)与CDQ分治相当，但常数更小  
  亮点：代码极致简洁，适合竞赛快速实现  

**题解三（Henry__Chen - 斜率优化）**  
* **点评**：实践价值 ★★★★☆  
  结合单调队列维护凸包，通过预排序保证斜率单调性。代码包含完整归并排序实现，边界处理严谨。亮点是指标公式`T_i*T_d - S_d*P_i`的几何意义解释，帮助理解斜率优化本质  

---

#### 3. 核心难点辨析与解题策略
1. **分数规划转化**  
   * **分析**：需从成绩比较中抽象出`Ta_j - Sb_j > Ta_i - Sb_i`的不等式，优质题解通过交叉相乘消分母实现  
   * 💡 **学习笔记**：分数规划核心是构造线性函数比较  

2. **动态斜率处理**  
   * **分析**：斜率`k=T_d/S_d`随D递减，但横坐标不单调。CDQ分治先排序左区间建凸包，右区间二分查询；决策单调性分治则递归缩小决策范围  
   * 💡 **学习笔记**：横坐标无序时，分治替代单调队列  

3. **凸包维护方向**  
   * **分析**：求`f(d)`需下凸包（最小值），`g(d)`需上凸包（最大值）。Henry解法通过`slope()`比较确保正确方向  
   * 💡 **学习笔记**：凸包类型与问题最值方向严格对应  

### ✨ 解题技巧总结
- **问题转化**：将复杂优化转为分数规划模型  
- **几何思维**：将代数式视作平面点集，利用凸包性质优化  
- **分治应用**：对非单调数据采用CDQ/决策单调性分治  
- **边界防御**：初始化极值`INF/-INF`避免边界错误  

---

#### 4. C++核心代码实现赏析
**通用核心实现（决策单调性分治版）**  
```cpp
void getf(int l, int r, int dl, int dr) {
    int mid = (l + r) >> 1, dm = dl;
    f[mid] = INF;
    for (int i = dl; i <= min(mid, dr); i++) {
        ll val = sp[mid] * a[i].t - st[mid] * a[i].p;
        if (val < f[mid]) f[mid] = val, dm = i; // 更新决策点
    }
    if (l < mid) getf(l, mid - 1, dl, dm);    // 左子区间
    if (r > mid) getf(mid + 1, r, dm, dr);     // 右子区间
}
```
* **说明**：综合自jyz666题解，体现决策单调性分治精髓  
* **代码解读概要**：  
  1. 对每个查询区间`[l,r]`定位中点`mid`  
  2. 在决策区间`[dl,dr]`暴力搜索最优决策点  
  3. 根据决策点单调性递归子区间  

**题解一赏析（CDQ分治）**  
```cpp
// 凸包维护核心
while (R > 1 && Cross(T[i] - T[Q[R - 1]], T[Q[R]] - T[Q[R - 1]]) <= 0) 
    R--; // 弹出非凸点
Q[++R] = i; // 入栈新点
```
* **亮点**：用叉积避免浮点误差  
* **学习笔记**：向量叉积>0表示逆时针旋转，维护下凸包时需保证连续叉积≤0  

**题解二赏析（决策单调性）**  
```cpp
void solveMax(int l, int r, int dl, int dr) {
    int mid = (l + r) >> 1, u = dl;
    for (int i = dl; i <= dr; i++) {
        ll tmp = sp[mid] * a[i].t - st[mid] * a[i].p;
        if (tmp > g[mid]) g[mid] = tmp, u = i; // 更新最大值
    }
    if (l < mid) solveMax(l, mid - 1, dl, u); // 关键！决策区间收缩
}
```
* **亮点**：决策区间随分治层级收缩  
* **学习笔记**：`u`作为分界点保证决策单调性  

---

#### 5. 算法可视化：像素动画演示  
* **主题**：8-bit风格凸包建造者  
* **核心演示**：  
  ![](https://assets.leetcode.com/uploads/2019/10/20/sample_4_1728.png)  
  > 图：凸包构建过程示意图（实际动画为动态）

  **动画流程**：  
  1. **初始化**：像素网格中，考试化为彩色方块（红：被删考试，蓝：保留考试）  
  2. **分治阶段**：  
     - 左区间点变绿，按x排序过程展示为冒泡动画  
     - 凸包构建：连接点时触发"叮"音效，非凸点弹出时爆炸特效  
  3. **查询阶段**：  
     - 右区间点变紫，扫描红线（当前斜率）在凸包移动  
     - 命中最优解时，连线闪烁金色，播放胜利音效  
  4. **交互控制**：  
     - 步进按钮：空格键单步执行  
     - 速度滑块：0.5x~5x调速  
     - 3D视角：右键拖拽旋转凸包  

---

#### 6. 拓展练习与相似问题
* **思路迁移**：  
  1. 最优比率生成树（POJ 2728）  
  2. 背包分数规划（洛谷P4377）  
  3. 带权中位数优化（CF 1486E）  

* **洛谷推荐**：  
  1. **P4377** - 证明：练习01分数规划基础应用  
  2. **P3199** - 圈检测：学习负环判断结合分数规划  
  3. **P5785** - 任务安排：巩固斜率优化变形  

---

#### 7. 学习心得与经验分享
> **参考经验**（javalyc）：  
> "调试凸包时，叉积方向判断错误导致凸包反向了。建议用`(a.x*b.y - b.x*a.y)`标准叉积公式，并画图验证旋转方向"  
>   
> **点评**：凸包方向是常见错误点，初学者应用小数据集验证叉积符号与凸包类型关系  

--- 
> 掌握分数规划+分治优化的组合拳，你就能在成绩优化类问题中游刃有余！下次遇到类似问题，记得先问自己：斜率是否单调？横坐标是否有序？选择合适的分治策略是关键！ 🚀

---
处理用时：186.94秒