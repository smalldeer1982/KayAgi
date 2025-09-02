# 题目信息

# Moon Craters

## 题目描述

There are lots of theories concerning the origin of moon craters. Most scientists stick to the meteorite theory, which says that the craters were formed as a result of celestial bodies colliding with the Moon. The other version is that the craters were parts of volcanoes.

An extraterrestrial intelligence research specialist professor Okulov (the namesake of the Okulov, the author of famous textbooks on programming) put forward an alternate hypothesis. Guess what kind of a hypothesis it was –– sure, the one including extraterrestrial mind involvement. Now the professor is looking for proofs of his hypothesis.

Professor has data from the moon robot that moves linearly in one direction along the Moon surface. The moon craters are circular in form with integer-valued radii. The moon robot records only the craters whose centers lay on his path and sends to the Earth the information on the distance from the centers of the craters to the initial point of its path and on the radii of the craters.

According to the theory of professor Okulov two craters made by an extraterrestrial intelligence for the aims yet unknown either are fully enclosed one in the other or do not intersect at all. Internal or external tangency is acceptable. However the experimental data from the moon robot do not confirm this theory! Nevertheless, professor Okulov is hopeful. He perfectly understands that to create any logical theory one has to ignore some data that are wrong due to faulty measuring (or skillful disguise by the extraterrestrial intelligence that will be sooner or later found by professor Okulov!) That’s why Okulov wants to choose among the available crater descriptions the largest set that would satisfy his theory.

## 样例 #1

### 输入

```
4
1 1
2 2
4 1
5 1
```

### 输出

```
3
1 2 4
```

# AI分析结果



**唯一算法分类**  
组合数学

---

### **题解思路、算法要点与解决难点**

**核心问题**：在直线上选择最多的圆（转化为区间），满足两两之间完全包含或不相交。  
**数学核心**：区间调度中的动态规划，关键在于处理包含关系并优化状态转移。

**关键公式与推导**：  
1. **区间排序**：按左端点升序，右端点降序排序，确保处理顺序正确。  
2. **状态定义**：  
   - `f(i, j)` 表示从第 `i` 个圆开始，右端点不超过 `j` 的最大可选数。  
   - 转移方程：  
     ```  
     f(i,j) = max(f(i+1,j), f(i+1,m_i) + f(R_i+1,j) + 1)  
     ```  
     其中 `m_i` 为当前圆的右端点，`R_i` 是预处理的最远右端点。  
3. **离散化优化**：将端点映射为离散值，减少状态空间。  

**难点对比**：  
- **封禁用户**：预处理 `R` 和 `nxt` 数组优化状态转移，复杂度 `O(n²)`。  
- **Duramente**：按右端点排序，计算每个圆内部最大可选数，需维护 `dp` 数组。  
- **信息向阳花木**：区间 `DP` 结合离散化，递归构造答案，但状态转移复杂度较高。  

---

### **题解评分 (≥4星)**

1. **封禁用户 (4.5星)**  
   - **亮点**：预处理优化清晰，代码逻辑简洁，输出答案递归高效。  
   - **代码可读性**：结构清晰，变量命名合理，注释较少但逻辑自洽。  

2. **信息向阳花木 (4星)**  
   - **亮点**：离散化处理详细，递归输出答案直观。  
   - **优化点**：状态转移稍显冗余，但思路易懂。  

3. **荣一鸣 (4星)**  
   - **亮点**：离散化与区间 `DP` 结合紧密，递归构造答案逻辑清晰。  
   - **不足**：代码注释较少，需深入理解离散化步骤。  

---

### **最优思路提炼**

**关键步骤**：  
1. **排序预处理**：按左端点升序、右端点降序排列区间。  
2. **离散化端点**：减少状态空间，便于动态规划处理。  
3. **动态规划转移**：  
   - 状态表示区间范围，转移时选择或不选当前区间。  
   - 预处理相邻区间关系（如 `nxt[i]`）优化复杂度。  

**代码实现核心**：  
```cpp
// 预处理 nxt 数组
for (int i=0; i<n; ++i) {
    nxt[i] = n; // 初始化为末尾
    for (int j=0; j<n; ++j)
        if (node[i].r <= node[j].l) {
            nxt[i] = j; break;
        }
}

// DP 转移
for (int i=n-1; ~i; --i)
    for (int j=0; j<n; ++j) {
        dp[i][j] = dp[i+1][j]; // 不选当前圆
        if (node[i].r <= R[j]) // 选当前圆
            getMax(dp[i][j], dp[i+1][Rid[i]] + dp[nxt[i]][j] + 1);
    }
```

---

### **同类型题与算法套路**

**常见套路**：  
- **区间调度**：贪心或动态规划处理区间选择问题。  
- **包含关系处理**：按端点排序，利用单调性优化状态转移。  

**推荐题目**：  
1. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233)  
2. [P2307 迷宫](https://www.luogu.com.cn/problem/P2307)  
3. [P2434 区间](https://www.luogu.com.cn/problem/P2434)  

---

### **可视化与算法演示**

**动画设计**：  
1. **像素风格演示**：  
   - **Canvas 绘制**：直线上离散化端点，圆表示为彩色线段。  
   - **颜色标记**：当前处理区间高亮为红色，已选区间为绿色。  
   - **步进控制**：单步展示 `DP` 状态转移，显示 `f(i,j)` 值更新。  

2. **音效与交互**：  
   - **音效触发**：选中区间时播放清脆音效，错误选择时低沉音效。  
   - **自动演示**：模拟贪心选择或 `DP` 转移流程，速度可调。  

**示例步骤**：  
1. 初始化所有区间，按左端点排序。  
2. 动态规划逐步选择区间，高亮当前处理区间。  
3. 递归构造答案时，显示路径回溯过程。  

---

### **个人心得摘录**

- **封禁用户**：  
  > “区间 DP 需要发现相互独立的子问题，预处理是关键。”  
- **荣一鸣**：  
  > “离散化后区间端点变为连续下标，极大简化了状态表示。”  

---

### **复古游戏化动画（示例）**

```javascript
// 伪代码：Canvas 绘制区间选择过程
function drawStep(ctx, intervals, selected) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    intervals.forEach((interval, idx) => {
        const x1 = interval.l * SCALE, x2 = interval.r * SCALE;
        ctx.fillStyle = selected.has(idx) ? '#00FF00' : '#FF0000';
        ctx.fillRect(x1, 50, x2 - x1, 20); // 绘制区间
    });
    // 播放音效
    if (selected.size > prevSize) playSound('select.wav');
}
```

---

**总结**：本题核心在于区间动态规划与预处理优化，结合离散化降低复杂度。推荐封禁用户的解法作为最优实现，兼顾效率与可读性。

---
处理用时：66.09秒