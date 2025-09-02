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



---

## **综合分析与结论**

### **题目核心**
在排序后的数据中，对于每个D，判断是否存在更优的删除方案。核心在于比较分数规划后的极值，通过斜率优化与分治维护凸包实现高效求解。

### **核心贪心策略**
1. **排序策略**：按$T_i/P_i$升序排列，确保删除D场时默认方案为删除前D小的元素。
2. **分数规划转换**：将分式比较转化为线性比较，即$T_jS - S_jT > T_iS - S_iT$。
3. **极值维护**：用分治+凸包维护前D项最小值（下凸包）和后N-D项最大值（上凸包）。

### **解决难点**
- **非单调斜率处理**：通过CDQ分治归并保证x有序，从而能用单调队列维护凸包。
- **时间复杂度优化**：将暴力$O(n^2)$优化至$O(n\log n)$。

---

## **题解评分与亮点**

### **≥4星题解清单**

1. **javalyc（5星）**
   - **亮点**：完整实现CDQ分治+凸包维护，注释清晰，数学推导详细。
   - **代码可读性**：结构清晰，变量命名规范，关键步骤有注释。
   ```cpp
   // CDQ分治维护凸包
   void CDQ_f(int l,int r) {
       if(l==r) return;
       int mid=(l+r)>>1;
       CDQ_f(l,mid);
       // 维护凸包并更新右区间极值
       CDQ_f(mid+1,r);
   }
   ```

2. **jyz666（4星）**
   - **亮点**：决策单调性分治实现简洁，代码量极小（仅60行）。
   - **优化技巧**：利用分治的天然单调性避免复杂凸包维护。
   ```cpp
   void getf(int l,int r,int dl,int dr) {
       int mid=(l+r)>>1,dm;
       for(int i=dl; i<=dr; i++) 
           f[mid]=min(f[mid], calc(...));
       // 分治左右区间
   }
   ```

3. **Henry__Chen（4星）**
   - **亮点**：数学推导完整，给出斜率优化几何解释，代码模块化。
   - **可视化友好**：凸包维护逻辑适合动画展示。

---

## **最优思路提炼**

### **关键步骤**
1. **排序预处理**：按$T_i/P_i$升序排列。
2. **分数规划转换**：比较式$\frac{\sum T}{\sum P} > k$转为线性式$T_j - kP_j > T_i - kP_i$。
3. **极值计算**：
   - **前D项最小值**：维护下凸包，斜率递增。
   - **后N-D项最大值**：维护上凸包，斜率递减。

### **数学推导**
设$k = \frac{\sum T}{\sum P}$，最优解满足：
$$ \max_{j>D}(T_j - kP_j) > \min_{i≤D}(T_i - kP_i) $$
通过维护凸包快速计算极值。

---

## **同类型题目推荐**
1. **P3199 [HNOI2009] 最小圈**（分数规划+SPFA判负环）
2. **P3515 [POI2011] Lightning Conductor**（决策单调性分治）
3. **P4027 [NOI2007] 货币兑换**（动态凸包维护）

---

## **可视化设计**

### **复古像素风格演示**
1. **Canvas绘制**：
   - 红色像素块表示前D项，蓝色表示后N-D项。
   - 绿色高亮当前比较的$(T_i,P_i)$对。
   ```javascript
   ctx.fillStyle = "#FF0000"; // 前D项红色
   ctx.fillRect(x, y, 8, 8); 
   ```

2. **凸包动画**：
   - 黄色线段动态绘制凸包边界。
   - 紫色标记当前极值点。
   ```javascript
   function drawConvexHull(points) {
       // 绘制凸包边
   }
   ```

3. **音效设计**：
   - 正确选择：8-bit上升音效（Web Audio API）。
   - 错误选择：低沉脉冲音。

---

## **核心代码片段**

### **斜率优化关键比较**
```cpp
bool operator < (const nod &x) const {
    return t*x.p < x.t*p; // 避免浮点误差
}
```

### **决策单调性分治**
```cpp
void solve(int l,int r,int optL,int optR) {
    int mid=(l+r)/2, opt=optL;
    for(int i=optL; i<=optR; i++) {
        if(calc(i,mid) < f[mid]) 
            opt=i, f[mid]=calc(i,mid);
    }
    solve(l,mid-1,optL,opt);
    solve(mid+1,r,opt,optR);
}
```

---

## **总结**
本题通过分数规划将分式比较转化为线性极值问题，结合排序与分治维护凸包实现高效求解。不同题解在实现细节（CDQ分治 vs 决策单调性）上各有千秋，核心思路高度一致。可视化设计可重点展示凸包构建过程与极值比较，复古像素风格能增强学习趣味性。

---
处理用时：71.82秒