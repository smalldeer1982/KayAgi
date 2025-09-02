# 题目信息

# Large Graph

## 题目描述

Given an array $ a $ of length $ n $ . Let's construct a square matrix $ b $ of size $ n \times n $ , in which the $ i $ -th row contains the array $ a $ cyclically shifted to the right by $ (i - 1) $ . For example, for the array $ a = [3, 4, 5] $ , the obtained matrix is

 $ $$$b = \begin{bmatrix} 3 & 4 & 5 \\ 5 & 3 & 4 \\ 4 & 5 & 3 \end{bmatrix} $ $ </p><p>Let's construct the following graph:</p><ul> <li> The graph contains  $ n^2 $  vertices, each of which corresponds to one of the elements of the matrix. Let's denote the vertex corresponding to the element  $ b\_{i, j} $  as  $ (i, j) $ .</li><li> We will draw an edge between vertices  $ (i\_1, j\_1) $  and  $ (i\_2, j\_2) $  if  $ |i\_1 - i\_2| + |j\_1 - j\_2| \\le k $  and  $ \\gcd(b\_{i\_1, j\_1}, b\_{i\_2, j\_2}) &gt; 1 $ , where  $ \\gcd(x, y) $  denotes the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor</a> of integers  $ x $  and  $ y $ . </li></ul><p>Your task is to calculate the number of connected components $ ^{\\dagger} $  in the obtained graph.</p><p> $ ^{\\dagger}$$$A connected component of a graph is a set of vertices in which any vertex is reachable from any other via edges, and adding any other vertex to the set violates this rule.

## 说明/提示

In the first test case, the matrix $ b $ is given in the statement. The first connected component contains the vertices $ (1, 1) $ , $ (2, 2) $ , and $ (3, 3) $ . The second connected component contains the vertices $ (1, 2) $ , $ (2, 3) $ , and $ (3, 1) $ . The third connected component contains the vertices $ (1, 3) $ , $ (2, 1) $ , and $ (3, 2) $ . Thus, the graph has $ 3 $ connected components.

In the second test case, the following matrix is obtained:

 $ $$$b = \begin{bmatrix} 3 & 4 & 9 \\ 9 & 3 & 4 \\ 4 & 9 & 3 \end{bmatrix} $ $ </p><p>The first connected component contains all vertices corresponding to elements with values  $ 3 $  and  $ 9 $ . The second connected component contains all vertices corresponding to elements with the value  $ 4$$$.

In the fourth test case, all vertices are in one connected component.

## 样例 #1

### 输入

```
6
3 3
3 4 5
3 3
3 4 9
3 2
3 4 9
2 2
2 8
5 3
8 27 5 4 3
4 10
2 2 2 2```

### 输出

```
3
2
3
1
4
1```

# AI分析结果



---

**唯一算法分类**：并查集（DSU）与质因子分解

---

### **题解思路与算法要点**

#### **核心思路**
1. **降维处理**：将二维矩阵的斜线转化为一维序列（长度为 $2n-1$），斜线相邻元素在序列中的距离为 1。
2. **质因子共享**：若两个元素共享一个质因子且下标差 $\le k$，则合并连通块。
3. **并查集优化**：通过预处理质因子，对每个质因子维护其出现的所有位置，合并相邻位置。
4. **特判 1**：值为 1 的元素无法形成边，直接累加其数量。

#### **解决难点**
- **二维转一维**：通过循环移位构造斜线序列，将曼哈顿距离转化为下标差。
- **质因子高效处理**：预处理每个数的最小质因子，分解时快速获取所有质因子。
- **合并逻辑**：对每个质因子的所有出现位置，检查相邻位置间距 $\le k$ 时合并。

---

### **最优思路与技巧提炼**
1. **质因子分组建边**：将元素按质因子分组，组内相邻元素间距 $\le k$ 时合并，时间复杂度从 $O(n^2)$ 降至 $O(n \log a_i)$。
2. **并查集的高效实现**：路径压缩与按秩合并保证接近线性的时间复杂度。
3. **特判 1 的优化**：直接计算 1 的贡献，避免参与并查集操作。

---

### **题解评分（≥4星）**
1. **CarroT1212（★★★★☆）**  
   - **亮点**：简洁的质因子预处理与并查集实现，代码逻辑清晰。  
   - **代码片段**：  
     ```cpp
     void mian() {
         for (ll i=2;i<N;i++) if (!vis[i]) {
             prm[i].pb(i);
             for (ll j=i+i;j<N;j+=i) vis[j]=i,prm[j].pb(i); 
         }
         // 处理质因子与并查集合并
     }
     ```
2. **Lu_xZ（★★★★☆）**  
   - **亮点**：使用最小质因子分解，代码规范且可读性强。  
   - **代码片段**：  
     ```cpp
     void Euler_Sieve() {
         low[1] = 1;
         for(int i = 2; i <= V; ++i) {
             if(!low[i]) p[++idx] = i;
             // 筛法预处理最小质因子
         }
     }
     ```
3. **int_R（★★★★☆）**  
   - **亮点**：代码短小精悍，质因子分解与合并逻辑高度优化。  
   - **代码片段**：  
     ```cpp
     inline void work() {
         for(int x:used) vis[x]=false,lst[x]=0;
         // 动态维护质因子出现位置
     }
     ```

---

### **可视化与算法演示**

#### **动画方案**
1. **像素化斜线展开**：  
   - **Canvas 绘制**：将矩阵斜线旋转 45 度，展开为横向序列，每个元素用像素块表示，颜色随值变化。  
   - **高亮当前质因子**：当处理质因子 $p$ 时，所有包含 $p$ 的像素块闪烁黄色。  
   - **合并动画**：相邻块间距 $\le k$ 时，绘制绿色连线，并查集合并后变为同色。

2. **并查集操作可视化**：  
   - **步进控制**：允许单步执行合并操作，显示父节点指针变化。  
   - **颜色标记连通块**：不同连通块用不同颜色区分，合并时颜色渐变。

3. **复古音效**：  
   - **合并音效**：8-bit 风格 "beep" 音效。  
   - **质因子高亮音效**：短促 "click" 音效。

---

### **同类型题目推荐**
1. **P3367（并查集模板）**  
2. **P1073（质因子与图连通性结合）**  
3. **P1522（矩阵转图连通块计数）**

---

### **个人心得摘录**
- **调试教训**：忽略 $a_i=1$ 的特判导致 WA，需明确 1 的贡献独立计算。  
- **优化顿悟**：将二维斜线映射到一维序列是关键降维技巧，极大简化问题。

---
处理用时：74.47秒