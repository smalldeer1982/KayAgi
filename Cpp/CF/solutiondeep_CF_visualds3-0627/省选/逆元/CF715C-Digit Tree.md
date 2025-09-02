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



**算法分类：树的分治算法（点分治/DSU on tree）**

---

### **题解思路与核心难点**

#### **核心思路**
1. **路径拆分与模运算**：将路径拆分为两段（自下而上与自上而下），利用模运算将问题转化为匹配问题。
2. **逆元处理**：由于M与10互质，使用扩展欧几里得算法预处理10的幂次逆元，避免除法。
3. **分治策略**：通过点分治或DSU on tree处理子树，统计经过分治重心或LCA的路径对。

#### **解决难点**
- **路径拼接**：将两段路径的值合并为一个整数，需处理模运算和逆元。
- **去重**：避免同一子树内的路径被重复统计（点分治用容斥，DSU处理轻子树）。
- **高效查询**：使用哈希表或`map`快速匹配满足条件的路径对。

---

### **题解评分（≥4星）**

1. **orangejuice（5星）**
   - **亮点**：完整推导DSU实现，预处理`disup/disdown`，利用重子树优化查询。
   - **代码**：结构清晰，注释详细，适合学习DSU on tree。

2. **MikukuOvO（4星）**
   - **亮点**：点分治思路简洁，式子变形明确，代码简洁。
   - **缺点**：代码链接失效，但思路值得参考。

3. **whiteqwq（4星）**
   - **亮点**：详细分析DSU实现，强调逆元处理，代码注释完整。
   - **心得**：强调调试中对模运算错误的检查。

---

### **最优思路提炼**

1. **预处理逆元**：提前计算10的幂次及其逆元，避免实时计算开销。
2. **路径表示**：维护`disup`（节点到根的逆序路径值）和`disdown`（根到节点的顺序路径值）。
3. **分治匹配**：
   - 点分治：统计经过重心的路径，用`map`存`d1`，查询`-d2 * 10^{-dep} mod M`。
   - DSU：合并子树时，先计算轻子树贡献，再合并到重子树。

---

### **同类型题与算法套路**

- **通用套路**：树上的路径统计问题，若需满足模/加减乘除条件，可拆分为两段，分治处理。
- **类似题目**：
  - [P2634 树上点对距离模3计数](https://www.luogu.com.cn/problem/P2634)
  - [P4178 Tree（统计路径长度≤K）](https://www.luogu.com.cn/problem/P4178)
  - [CF161D 路径长度等于K](https://www.luogu.com.cn/problem/CF161D)

---

### **推荐题目**

1. **P3806【模板】点分治**（基础分治练习）
2. **P4149 路径统计**（边权处理与计数）
3. **CF342E 动态最近点对**（分治维护动态树）

---

### **个人心得摘录**

- **逆元处理**：注意模运算中负数的处理，如`(x % mod + mod) % mod`。
- **路径拼接**：`10^k`的幂次与深度相关，预处理避免重复计算。
- **调试技巧**：分治时打印子树信息，验证逆元计算正确性。

---

### **可视化设计**

**动画方案（点分治流程）**：
1. **树结构展示**：8位像素风格，分治重心高亮为红色，子树用不同颜色。
2. **路径拆分**：点击路径时，拆分为两段（红蓝线段），显示模值和逆元计算。
3. **匹配演示**：当两段路径模值匹配成功时，播放上扬音效，路径闪烁。
4. **控制面板**：步进执行分治步骤，调节动画速度，查看当前`map`内容。

**核心代码（伪代码）**：
```python
def 点分治(节点):
    标记重心为已访问
    初始化map统计当前子树
    for 所有相邻子树:
        计算子树路径值
        在map中查询匹配项并累加答案
        将子树路径加入map
    递归处理未访问子树
```

---

**复古游戏化效果**：
- **像素风格**：树节点为8位方块，路径用像素线连接。
- **音效**：匹配成功时播放8位“胜利”音效，分治步骤切换时有“点击”声。
- **积分系统**：每正确统计一个子树得10分，连击奖励加速动画。

---
处理用时：88.60秒