# 题目信息

# Dima and Bacteria

## 题目描述

Dima took up the biology of bacteria, as a result of his experiments, he invented $ k $ types of bacteria. Overall, there are $ n $ bacteria at his laboratory right now, and the number of bacteria of type $ i $ equals $ c_{i} $ . For convenience, we will assume that all the bacteria are numbered from $ 1 $ to $ n $ . The bacteria of type $ c_{i} $ are numbered from ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400D/982a571b1865821e9e229719b32d90deaece954a.png) to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400D/cadef4f1e0deb44673d0bf224d83a90828e59d96.png).

With the help of special equipment Dima can move energy from some bacteria into some other one. Of course, the use of such equipment is not free. Dima knows $ m $ ways to move energy from some bacteria to another one. The way with number $ i $ can be described with integers $ u_{i} $ , $ v_{i} $ and $ x_{i} $ mean that this way allows moving energy from bacteria with number $ u_{i} $ to bacteria with number $ v_{i} $ or vice versa for $ x_{i} $ dollars.

Dima's Chef (Inna) calls the type-distribution correct if there is a way (may be non-direct) to move energy from any bacteria of the particular type to any other bacteria of the same type (between any two bacteria of the same type) for zero cost.

As for correct type-distribution the cost of moving the energy depends only on the types of bacteria help Inna to determine is the type-distribution correct? If it is, print the matrix $ d $ with size $ k×k $ . Cell $ d[i][j] $ of this matrix must be equal to the minimal possible cost of energy-moving from bacteria with type $ i $ to bacteria with type $ j $ .

## 样例 #1

### 输入

```
4 4 2
1 3
2 3 0
3 4 0
2 4 1
2 1 2
```

### 输出

```
Yes
0 2
2 0
```

## 样例 #2

### 输入

```
3 1 2
2 1
1 2 0
```

### 输出

```
Yes
0 -1
-1 0
```

## 样例 #3

### 输入

```
3 2 2
2 1
1 2 0
2 3 1
```

### 输出

```
Yes
0 1
1 0
```

## 样例 #4

### 输入

```
3 0 2
1 2
```

### 输出

```
No
```

# AI分析结果

### 题目重写
# Dima和细菌

## 题目描述
Dima从事细菌生物学研究，通过实验，他培育出了$k$种细菌。目前实验室里共有$n$个细菌，其中第$i$种细菌的数量为$c_{i}$。为方便起见，我们将所有细菌从$1$到$n$编号，第$i$种细菌的编号范围是从$\sum_{j = 1}^{i - 1}c_{j} + 1$到$\sum_{j = 1}^{i}c_{j}$。

借助特殊设备，Dima能够将能量从某些细菌转移到其他细菌，但使用该设备并非免费。Dima知晓$m$种能量转移方式，第$i$种方式可用整数$u_{i}$、$v_{i}$和$x_{i}$描述，表示可以花费$x_{i}$美元，将能量从编号为$u_{i}$的细菌转移到编号为$v_{i}$的细菌，反之亦然。

Dima的导师（Inna）认为，如果对于任何特定种类的细菌，都存在一种方式（可以是非直接的），使得该种类的任意细菌都能以零成本将能量转移到同种类的其他任意细菌，那么这种细菌的类型分布就是正确的。

对于正确的类型分布，能量转移的成本仅取决于细菌的类型。请帮助Inna确定当前的类型分布是否正确。如果正确，请输出一个大小为$k×k$的矩阵$d$，矩阵中元素$d[i][j]$应等于从第$i$种细菌转移能量到第$j$种细菌的最小成本。

## 样例 #1
### 输入
```
4 4 2
1 3
2 3 0
3 4 0
2 4 1
2 1 2
```
### 输出
```
Yes
0 2
2 0
```

## 样例 #2
### 输入
```
3 1 2
2 1
1 2 0
```
### 输出
```
Yes
0 -1
-1 0
```

## 样例 #3
### 输入
```
3 2 2
2 1
1 2 0
2 3 1
```
### 输出
```
Yes
0 1
1 0
```

## 样例 #4
### 输入
```
3 0 2
1 2
```
### 输出
```
No
```

### 算法分类
图论（并查集 + Floyd最短路）

### 题解综合分析与结论
所有题解思路基本一致，均采用并查集判断同类型细菌是否能以0代价互相连通，再用Floyd算法计算不同类型细菌间转移能量的最小成本。具体步骤为：先初始化并查集，将边权为0的边的端点合并；接着检查每种类型的细菌是否都在同一集合中，判断类型分布是否正确；若正确，将每种类型看作一个点，取不同类型中两点的最小边权连边，最后通过Floyd算法得到任意两种类型细菌间的最小代价。各题解主要差异在于代码实现细节和风格，如输入输出方式、变量命名、函数封装等。

### 所选的题解
- **作者：foryou_（5星）**
    - **关键亮点**：思路阐述简洁清晰，直接点明每一步骤使用的算法及时间复杂度，未给出代码但对整体思路把握精准。
- **作者：wangboyue（5星）**
    - **关键亮点**：代码结构清晰，各功能模块封装成函数，逻辑连贯，变量命名有意义，便于理解。
    - **重点代码**：
```cpp
int find(int x){
    if(fa[x]==x){
        return x;
    }
    return fa[x]=find(fa[x]);
}// 并查集查找函数，路径压缩优化
void add(int x,int y){
    x=find(x);
    y=find(y);
    if(x!=y){
        fa[x]=y;
    }
    return;
}// 并查集合并函数
void floyd(){
    for(int l=1;l<=k;l++){
        for(int i=1;i<=k;i++){
            for(int j=1;j<=k;j++){
                dp[i][j]=min(dp[i][j],dp[i][l]+dp[l][j]);
            }
        }
    }
    return;
}// Floyd算法核心，更新最短路径
```
- **作者：Weekoder（4星）**
    - **关键亮点**：对思路分析详细，将每个步骤的代码片段单独列出并加以解释，整体代码规范，注释清晰。
    - **重点代码**：
```cpp
void floydinit() {
    memset(dp, 0x3f, sizeof dp);
    for (int i = 1; i <= k; i++) dp[i][i] = 0;
}// Floyd算法初始化，将dp数组设为极大值，对角线设为0
void floyd() {
    for (int l = 1; l <= k; l++)
        for (int i = 1; i <= k; i++)
            for (int j = 1; j <= k; j++)
                if (dp[i][l]!= INF && dp[l][j]!= INF)
                    dp[i][j] = min(dp[i][j], dp[i][l] + dp[l][j]);
}// Floyd算法更新最短路径，避免INT_MAX溢出
```

### 最优关键思路或技巧
- **数据结构选择**：利用并查集高效处理连通性问题，通过路径压缩优化查找操作，降低时间复杂度。
- **算法结合**：将并查集判断连通性与Floyd算法计算多源最短路径相结合，解决类型分布正确性判断及不同类型间最小代价计算问题。
- **问题转化**：把每种细菌类型看作一个点，将原问题转化为图论中关于点与点之间连通性和最短路径的问题，便于使用成熟算法解决。

### 拓展
此类题目属于图论中结合连通性判断与最短路径求解的问题。类似套路包括先通过某种方式（如并查集）处理图的连通分量，再利用图的遍历（如BFS、DFS）或最短路径算法（如Dijkstra、Floyd）解决与节点间关系相关的问题。常见同类型题有判断网络连通性并计算节点间最小传输代价等。

### 推荐题目
- [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：经典并查集应用题目，通过并查集判断亲戚关系。
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：结合图论和时间轴的题目，需要在不同时间点下计算最短路径，可使用Floyd算法结合条件判断。
- [P3369 【模板】普通并查集](https://www.luogu.com.cn/problem/P3369)：并查集模板题，用于巩固并查集的基本操作和应用。 

---
处理用时：68.40秒