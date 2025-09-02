# 题目信息

# Digit Tree

## 题目描述

ZS the Coder has a large tree. It can be represented as an undirected connected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ n-1 $ edges between them. There is a single nonzero digit written on each edge.

One day, ZS the Coder was bored and decided to investigate some properties of the tree. He chose a positive integer $ M $ , which is coprime to $ 10 $ , i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/9b5bdec4cb6231baa1f3fcb57eb25703ae0eed8f.png).

ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting when if he would follow the shortest path from vertex $ u $ to vertex $ v $ and write down all the digits he encounters on his path in the same order, he will get a decimal representaion of an integer divisible by $ M $ .

Formally, ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting if the following states true:

- Let $ a_{1}=u,a_{2},...,a_{k}=v $ be the sequence of vertices on the shortest path from $ u $ to $ v $ in the order of encountering them;
- Let $ d_{i} $ ( $ 1<=i&lt;k $ ) be the digit written on the edge between vertices $ a_{i} $ and $ a_{i+1} $ ;
- The integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/72be647436ef167ccaba4334e08ad71c22afc6b4.png) is divisible by $ M $ .

Help ZS the Coder find the number of interesting pairs!

## 说明/提示

In the first sample case, the interesting pairs are $ (0,4),(1,2),(1,5),(3,2),(2,5),(5,2),(3,5) $ . The numbers that are formed by these pairs are $ 14,21,217,91,7,7,917 $ respectively, which are all multiples of $ 7 $ . Note that $ (2,5) $ and $ (5,2) $ are considered different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/08c05395fdf8f9a998abf43b020555e6b5471bd5.png)In the second sample case, the interesting pairs are $ (4,0),(0,4),(3,2),(2,3),(0,1),(1,0),(4,1),(1,4) $ , and $ 6 $ of these pairs give the number $ 33 $ while $ 2 $ of them give the number $ 3333 $ , which are all multiples of $ 11 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/8a71025758e81b9cf19889885872aec3ca3f5ffc.png)

## 样例 #1

### 输入

```
6 7
0 1 2
4 2 4
2 0 1
3 0 9
2 5 7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 11
1 2 3
2 0 3
3 0 3
4 3 3
```

### 输出

```
8
```

# AI分析结果


### 💡 Kay的C++算法解析：Digit Tree 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：树分治（点分治/DSU on tree） + 模运算技巧  
🗣️ **初步分析**：
> 解决"Digit Tree"的关键在于**树分治**与**模运算处理**。想象树是一张巨大的地图🌲，点分治就像在每个区域中心设置检查站🛂，统计经过检查站的路径；DSU on tree则像建立快速信息通道🚄，优先处理重子树避免重复计算。  
> - **核心思路**：通过树分治分解路径，利用模方程`dis1 × 10^len + dis2 ≡ 0 mod M`统计路径。难点在于数字拼接的方向处理（正向/反向）和模逆元计算（因M非质数需exgcd）。  
> - **可视化设计**：采用8位像素风🌌展示重心分解过程，用不同颜色标记当前操作节点（闪烁红🔴）和已访问路径（渐变蓝🔵）。当路径匹配成功时，播放"叮"🎵音效并展示像素爆炸动画💥，增强算法关键步骤感知。

---

#### 2. 精选优质题解参考
**题解一：orangejuice (DSU on tree)**  
* **点评**：思路清晰推导严谨，通过`disup/disdown`分离正反向路径值，创新性使用双map存储状态。代码规范（变量名`disup[u]`含义明确），算法高效（O(n log²n)）。亮点在**路径拼接的数学变形**："disup[begin] = ..."的推导极具启发性，帮助理解模方程本质。

**题解二：MikukuOvO (点分治)**  
* **点评**：代码简洁高效，利用`d1, d2`记录双向路径值，通过`map`快速匹配。亮点在**重心分解的直观实现**和**容斥处理重复路径**。实践价值高（直接可用于竞赛），边界处理严谨（特判单点路径）。

**题解三：Register_int (点分治)**  
* **点评**：结构清晰模块化强，详细注释exgcd求逆元过程。亮点在**轻量化代码设计**和**路径贡献分离技巧**（calc函数独立统计），调试友好性强。

---

#### 3. 核心难点辨析与解题策略
1. **难点1：路径数字拼接的方向性**  
   * **分析**：正向路径（u→v）与反向路径（v→u）数值不同。优质题解用`disup/disdown`分离存储，通过`10^dep`对齐数位（如`disdown[v] = 10*disdown[u] + w`）。
   * 💡 学习笔记：路径统计需双向计算，`dep`记录深度是数位对齐的关键。

2. **难点2：模方程变形与逆元**  
   * **分析**：方程`dis1 × 10^len + dis2 ≡ 0 mod M`需变形为`dis1 ≡ -dis2 × 10^{-len} mod M`。因M非质数，必须用exgcd求逆元（如`orangejuice`的`Inv()`函数）。
   * 💡 学习笔记：`gcd(10,M)=1`保证逆元存在，exgcd是通用解法。

3. **难点3：避免重复统计**  
   * **分析**：点分治需容斥处理子树内路径（`ans -= calc(v)`），DSU需在重子树基础上合并轻子树（`if(son[u])...`）。
   * 💡 学习笔记：树分治的本质是"总贡献-子贡献"，容斥是防重核心。

### ✨ 解题技巧总结
- **技巧1：数学建模优先**：将路径拼接转化为模方程，避免高精度。
- **技巧2：双向分离存储**：用`disup/disdown`分别处理正反向路径值。
- **技巧3：模块化设计**：拆分`exgcd, getRoot, calc`函数提升可读性。

---

#### 4. C++核心代码实现赏析
**通用核心实现（点分治框架）**  
```cpp
void solve(int u) {
    vis[u] = 1;
    ans += calc(u, 0); // 统计u为根的贡献
    for (auto [v, w] : G[u]) {
        if (vis[v]) continue;
        ans -= calc(v, w); // 容斥扣除同子树路径
        getRoot(v);       // 获取新重心
        solve(root);      // 递归分治
    }
}
```
* **说明**：综合点分治最优实践，体现"统计-容斥-递归"核心逻辑。
* **代码解读概要**：  
  1. `vis[]`标记已访问重心  
  2. `calc()`计算当前重心路径贡献  
  3. 容斥后递归处理子树  

---

**题解一：orangejuice (DSU核心片段)**  
```cpp
void dfs_getans(int u, int f, int h) {
    for (int e : light_son[u]) dfs_getans(e, u, 0); // 递归轻儿子
    if (heavy_son[u]) dfs_getans(heavy_son[u], u, 1); // 保留重儿子
    for (int e : light_son[u]) {
        Upd(e, u, u, 1); // 统计轻儿子贡献
        Upd(e, u, u, 0); // 合并轻儿子信息
    }
    Calc(u, u); // 计算u为LCA的路径
    Add(u);     // 添加u的信息
}
```
* **亮点**：重儿子信息保留避免重复计算，轻儿子暴力合并。
* **学习笔记**：DSU的`保留重子树+轻子树合并`是O(n log n)复杂度的关键。

---

#### 5. 算法可视化：像素动画演示
**🎮 主题**：`像素探险家寻宝`（FC红白机风格）  
**🎨 设计思路**：  
- **场景**：树转化为网格地图，重心为城堡🏰，路径为像素小路（棕色⬜）。  
- **动画流程**：  
  1. **初始化**：8-bit音乐🎶中显示树结构，控制面板（开始/步进/速度条）。  
  2. **重心选择**：当前重心闪烁💡，播放"选择"音效（8-bit哔声）。  
  3. **路径统计**：  
     - 红箭头→移动表示当前路径计算（正向`disup`：黄🔶，反向`disdown`：蓝🔵）  
     - 路径匹配成功时，目标节点💎发光，播放"叮！"音效 + 像素烟花💥  
  4. **数据结构可视化**：  
     - `map`存储状态：右侧像素表格显示键值对（如`disup: 3 → 计数:2`）  
     - 队列/栈用像素方块堆叠动态展示  
  5. **交互控制**：  
     - 步进模式：按右键逐步执行，当前代码行高亮  
     - 自动演示：AI贪吃蛇模式自动遍历路径，速度滑块调速  

**⚙️ 技术实现**：  
```javascript
// 伪代码：路径匹配动画
function drawMatch(u, v) {
    highlightNode(u, COLOR_YELLOW); // 高亮起点
    highlightNode(v, COLOR_BLUE);    // 高亮终点
    drawPath(u, v);                 // 绘制路径
    playSound("match");             // 播放匹配音效
    if (calcMod() == 0) {           // 模为0时
        explodePixels(u, v);        // 像素爆炸特效
        addScore(10);               // 游戏化积分
    }
}
```

---

#### 6. 拓展练习与相似问题
1. **洛谷 P3806** - 点分治模板  
   * 🗣️ 推荐理由：基础点分治应用，巩固"统计路径数"的思想。  
2. **洛谷 P2634** - 树分治求路径和  
   * 🗣️ 推荐理由：将数字统计转化为路径和，训练模型抽象能力。  
3. **洛谷 P2664** - 树上颜色统计  
   * 🗣️ 推荐理由：DSU on tree经典应用，强化重子树优化技巧。  

---

#### 7. 学习心得分享
> **经验摘录（orangejuice）**：  
> "调试时重点验证`disup/disdown`的递推式，用小数据模拟路径拼接过程。"  
> **Kay总结**：  
> 调试树分治问题时，**打印中间变量**（如路径值）和**可视化小树**是定位错误的核心手段。记住：数学推导的严谨性决定代码正确性！  

---  
💪 编程能力的提升在于持续学习和勇于实践！下次挑战见！

---
处理用时：104.72秒