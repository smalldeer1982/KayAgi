# 题目信息

# Tokitsukaze and Two Colorful Tapes

## 题目描述

Tokitsukaze has two colorful tapes. There are $ n $ distinct colors, numbered $ 1 $ through $ n $ , and each color appears exactly once on each of the two tapes. Denote the color of the $ i $ -th position of the first tape as $ ca_i $ , and the color of the $ i $ -th position of the second tape as $ cb_i $ .

Now Tokitsukaze wants to select each color an integer value from $ 1 $ to $ n $ , distinct for all the colors. After that she will put down the color values in each colored position on the tapes. Denote the number of the $ i $ -th position of the first tape as $ numa_i $ , and the number of the $ i $ -th position of the second tape as $ numb_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ba8639f69fd74760b5261096016619c105b9cbe6.png)For example, for the above picture, assuming that the color red has value $ x $ ( $ 1 \leq x \leq n $ ), it appears at the $ 1 $ -st position of the first tape and the $ 3 $ -rd position of the second tape, so $ numa_1=numb_3=x $ .

Note that each color $ i $ from $ 1 $ to $ n $ should have a distinct value, and the same color which appears in both tapes has the same value.

After labeling each color, the beauty of the two tapes is calculated as $ $$$\sum_{i=1}^{n}|numa_i-numb_i|. $ $$$

Please help Tokitsukaze to find the highest possible beauty.

## 说明/提示

An optimal solution for the first test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/eb5a2fd8a44a35877d106dc26e9dcf9fd0a2a486.png)The beauty is $ \left|4-3 \right|+\left|3-5 \right|+\left|2-4 \right|+\left|5-2 \right|+\left|1-6 \right|+\left|6-1 \right|=18 $ .

An optimal solution for the second test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ec6542f7ba45f38760ee0d113e52ba6999ceef87.png)The beauty is $ \left|2-2 \right|+\left|1-6 \right|+\left|3-3 \right|+\left|6-1 \right|+\left|4-4 \right|+\left|5-5 \right|=10 $ .

## 样例 #1

### 输入

```
3
6
1 5 4 3 2 6
5 3 1 4 6 2
6
3 5 4 6 2 1
3 6 4 5 2 1
1
1
1```

### 输出

```
18
10
0```

# AI分析结果



---

### **综合分析与结论**

**题目核心**：将两个排列转化为置换环结构，通过贪心策略在每个环中选择尽可能多的极大/极小值配对，最大化总绝对差和。  
**解决难点**：发现置换环结构与贪心配对方式，推导出答案公式 $2k(n−k)$（$k$ 为各环可贡献的最多配对数总和）。  
**算法要点**：  
1. **置换环分解**：将颜色映射关系转化为图中的环。  
2. **贪心策略**：每个环选择 $\lfloor \frac{L}{2} \rfloor$ 对，大数作为“山峰”，小数作为“山谷”。  
3. **数学优化**：总答案为 $2k(n−k)$，其中 $k$ 是所有环的半长总和。  

**可视化设计**：  
- **动画方案**：以像素风格绘制置换环，高亮当前遍历的节点，步进展示环的发现过程。  
- **游戏化交互**：每发现一个环时播放8bit音效，自动计算环的贡献对数，最终显示总答案推导过程。  
- **控制面板**：支持调节动画速度，单步执行环遍历，突出贪心策略的决策点。

---

### **题解清单 (≥4星)**

1. **I_am_Accepted (⭐⭐⭐⭐⭐)**  
   - **亮点**：代码简洁高效，置换环DFS遍历清晰，公式推导直观。  
   - **核心代码**：  
     ```cpp
     int dfs(int x) {
         vis[x] = 1;
         if (vis[b[x]]) return 1;
         else return 1 + dfs(b[x]);
     }
     // 统计总贡献对数 k=ans
     For(i,1,n) if(!vis[i]) ans += dfs(i)>>1;
     cout << 2*ans*(n-ans) << endl;
     ```

2. **Leasier (⭐⭐⭐⭐)**  
   - **亮点**：详细拆解绝对值贡献，数学证明严谨。  
   - **关键思路**：每个数贡献为 $\pm 2x$ 或 $0$，贪心最大化正项与负项的差。

3. **Renshey (⭐⭐⭐⭐)**  
   - **亮点**：代码变量命名清晰，逻辑简洁，直接映射题意。  
   - **心得摘录**：“拆绝对值，让较小数分配 $-1$，较大数分配 $+1$” —— 直观贪心选择。

---

### **最优思路与技巧提炼**

1. **置换环建模**：将颜色映射关系 $ca_i \leftrightarrow cb_i$ 视为边，构建环结构。  
2. **贪心配对**：每个环最多贡献 $\lfloor \frac{L}{2} \rfloor$ 对，每对由最大（山峰）和最小（山谷）值构成。  
3. **全局最优公式**：总贡献为 $2k(n−k)$，其中 $k$ 为所有环的半长总和。  
4. **实现技巧**：  
   - 通过数组映射快速定位颜色位置。  
   - DFS或并查集高效遍历环结构。

---

### **同类型题目推荐**

1. **P1963 变换序列**：置换环构造最小字典序解。  
2. **P5149 会议座位**：环分解与逆序对优化。  
3. **P3631 [APIO2011]方格染色**：图论建模与奇偶环分析。

---

### **代码片段（核心贪心逻辑）**

```cpp
// 映射构建与环遍历（I_am_Accepted版）
For(i,1,n) {
    cin >> x;
    a[x] = i; // 记录颜色在第一个数组中的位置
}
For(i,1,n) {
    cin >> x;
    b[i] = a[x]; // 构建映射关系 b[i]=j 表示第二个数组i位置对应第一个数组j位置的颜色
}
// DFS统计环长并计算k
int ans = 0;
For(i,1,n) if (!vis[i]) ans += dfs(i) >> 1;
cout << 2 * ans * (n - ans) << endl;
```

---

### **可视化与游戏化设计**

1. **像素动画**：  
   - 用Canvas绘制颜色节点，不同颜色区分环。  
   - 遍历环时高亮当前节点，步进显示DFS过程。  
2. **音效设计**：  
   - 发现新环时播放“升级”音效。  
   - 计算答案时播放胜利音乐。  
3. **自动演示模式**：AI自动遍历所有环，动态显示k值累加与公式计算。  
4. **积分系统**：每正确统计一个环得10分，错误操作扣分，增强互动。

---

**总结**：本题核心在于置换环分析与贪心极值配对，通过将问题转化为图论模型，快速推导出最优解公式。同类题目常涉及环结构分解与极值贪心策略。

---
处理用时：95.45秒