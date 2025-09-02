# 题目信息

# Strongly Connected City

## 题目描述

Imagine a city with $ n $ horizontal streets crossing $ m $ vertical streets, forming an $ (n-1)×(m-1) $ grid. In order to increase the traffic flow, mayor of the city has decided to make each street one way. This means in each horizontal street, the traffic moves only from west to east or only from east to west. Also, traffic moves only from north to south or only from south to north in each vertical street. It is possible to enter a horizontal street from a vertical street, or vice versa, at their intersection.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF475B/7015745b6e36cd9d1741bb00e67e81a4ab310705.png)The mayor has received some street direction patterns. Your task is to check whether it is possible to reach any junction from any other junction in the proposed street direction pattern.

## 说明/提示

The figure above shows street directions in the second sample test case.

## 样例 #1

### 输入

```
3 3
><>
v^v```

### 输出

```
NO
```

## 样例 #2

### 输入

```
4 6
<><>
v^v^v^```

### 输出

```
YES
```

# AI分析结果



# 强连通城市

## 题目描述

想象一个由 $n$ 条水平街道与 $m$ 条垂直街道交叉形成的 $(n-1)×(m-1)$ 网格城市。市长决定将每条街道设为单行道：水平街道只能东西单向行驶，垂直街道只能南北单向行驶。交叉口处允许不同方向转换。请验证该城市是否任意交叉口可互达。

## 输入输出样例

样例1输入：
```
3 3
><>
v^v
```
样例1输出：
```
NO

样例2输入：
4 6
<><>
v^v^v^
```
样例2输出：
```
YES
```

**算法分类**：图论/构造

---

## 题解综合分析

### 核心思路对比
1. **四角连通定理**（Hanzire76、JRzyh等）：  
   若四个边角（左上、右上、左下、右下）构成的环路能形成闭环（顺时针或逆时针），则全图强连通。这是最优解，时间复杂度 O(1)。

2. **暴力搜索法**（Fan_Tuan）：  
   对每个节点进行DFS/BFS，验证可达性。时间复杂度 O(n²m²)，但数据规模小（20x20）仍可通过。

3. **强连通分量算法**（yuy_）：  
   使用Tarjan算法求强连通分量，复杂度 O(nm)，代码量较大但理论完备。

4. **传递闭包**（Sangber）：  
   Floyd算法预处理可达性矩阵，复杂度 O((nm)³)，理论可行但实际效率较低。

### 最优思路提炼
**四角连通定理**是本题的最优解法，其核心在于：
1. 四角构成的外环若形成闭环，则边缘所有点可达
2. 内部点可通过边缘点间接连通
3. 只需验证四条边的首尾方向是否构成顺时针/逆时针环流

---

## 精选题解（评分≥4星）

### 1. Hanzire76 题解（⭐⭐⭐⭐⭐）
**亮点**：  
- 发现四角连通定理，将问题转化为四个方向的逻辑判断  
- 代码简洁高效（O(1) 时间复杂度）  
- 正确性证明清晰  

**核心代码**：
```cpp
if (s1[0]=='<'&&s1[n-1]=='>'&&s2[0]=='v'&&s2[m-1]=='^') cout<<"YES";
else if (s1[0]=='>'&&s1[n-1]=='<'&&s2[0]=='^'&&s2[m-1]=='v') cout<<"YES";
else cout<<"NO";
```

### 2. JRzyh 题解（⭐⭐⭐⭐）
**亮点**：  
- 图形化解释四角连通原理  
- 明确顺时针/逆时针两种合法情形  
- 代码极简（仅需4个条件判断）

**代码片段**：
```cpp
if(s1[0]=='>'&&s1[n-1]=='<'&&s2[0]=='^'&&s2[m-1]=='v')cout<<"YES";
```

### 3. Fan_Tuan 题解（⭐⭐⭐⭐） 
**亮点**：  
- 暴力DFS验证每个点的可达性  
- 代码易理解，适合小数据范围  
- 包含完整的访问统计逻辑  

**核心实现**：
```cpp
void dfs(int i, int j) {
    if (越界或已访问) return;
    vis[i][j] = 1;
    // 根据方向递归相邻点
    if (水平方向右) dfs(i,j+1);
    if (垂直方向下) dfs(i+1,j);
}
```

---

## 关键技巧与拓展
1. **图论问题降维**：将二维网格连通性问题转化为边界特征分析  
2. **拓扑特征观察**：识别环状结构在连通性中的决定性作用  
3. **暴力法优化**：当 n,m ≤20 时，O(n²m²) 的暴力解法仍可行  

**同类题目推荐**：  
1. [P2743 - 方形牧场](https://www.luogu.com.cn/problem/P2743)（网格结构分析）  
2. [P1363 幻象迷宫](https://www.luogu.com.cn/problem/P1363)（无限网格连通性判断）  
3. [P1038 神经网络](https://www.luogu.com.cn/problem/P1038)（有向图连通性应用）  

---

## 调试心得摘录
"第一次看以为是DFS题，仔细分析后发现是结论题。关键突破点在于意识到外环的连通性决定整体结构" —— smydahaoren  
"调试时发现边界处理容易出错，特别是数组索引从1开始还是0开始要统一" —— Fan_Tuan  
"验证四角定理时，通过绘制多组样例确认顺时针和逆时针两种合法情形" —— JRzyh

---
处理用时：63.18秒