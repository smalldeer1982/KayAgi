# 题目信息

# AND-MEX Walk

## 题目描述

There is an undirected, connected graph with $ n $ vertices and $ m $ weighted edges. A walk from vertex $ u $ to vertex $ v $ is defined as a sequence of vertices $ p_1,p_2,\ldots,p_k $ (which are not necessarily distinct) starting with $ u $ and ending with $ v $ , such that $ p_i $ and $ p_{i+1} $ are connected by an edge for $ 1 \leq i < k $ .

We define the length of a walk as follows: take the ordered sequence of edges and write down the weights on each of them in an array. Now, write down the bitwise AND of every nonempty prefix of this array. The length of the walk is the MEX of all these values.

More formally, let us have $ [w_1,w_2,\ldots,w_{k-1}] $ where $ w_i $ is the weight of the edge between $ p_i $ and $ p_{i+1} $ . Then the length of the walk is given by $ \mathrm{MEX}(\{w_1,\,w_1\& w_2,\,\ldots,\,w_1\& w_2\& \ldots\& w_{k-1}\}) $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Now you must process $ q $ queries of the form u v. For each query, find the minimum possible length of a walk from $ u $ to $ v $ .

The MEX (minimum excluded) of a set is the smallest non-negative integer that does not belong to the set. For instance:

- The MEX of $ \{2,1\} $ is $ 0 $ , because $ 0 $ does not belong to the set.
- The MEX of $ \{3,1,0\} $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the set, but $ 2 $ does not.
- The MEX of $ \{0,3,1,2\} $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the set, but $ 4 $ does not.

## 说明/提示

The following is an explanation of the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1659E/e80c1510937e2e4c165cad1b2b45b357811161d4.png)The graph in the first example.Here is one possible walk for the first query:

 $ $$$1 \overset{5}{\rightarrow} 3 \overset{3}{\rightarrow} 2 \overset{1}{\rightarrow} 1 \overset{5}{\rightarrow} 3 \overset{1}{\rightarrow} 4 \overset{2}{\rightarrow} 5. $ $ </p><p>The array of weights is  $ w=\[5,3,1,5,1,2\] $ . Now if we take the bitwise AND of every prefix of this array, we get the set  $ \\{5,1,0\\} $ . The MEX of this set is  $ 2$$$. We cannot get a walk with a smaller length (as defined in the statement).

## 样例 #1

### 输入

```
6 7
1 2 1
2 3 3
3 1 5
4 5 2
5 6 4
6 4 6
3 4 1
3
1 5
1 2
5 3```

### 输出

```
2
0
1```

## 样例 #2

### 输入

```
9 8
1 2 5
2 3 11
3 4 10
3 5 10
5 6 2
5 7 1
7 8 5
7 9 5
10
5 7
2 5
7 1
6 4
5 2
7 6
4 1
6 2
4 7
2 8```

### 输出

```
0
0
2
0
0
2
1
0
1
1```

# AI分析结果



## 算法分类
图论、位运算、并查集

## 题解思路与核心逻辑

### 核心观察
1. **答案必为0/1/2**  
   由于按位与运算的单调递减性，路径的AND序列必然呈现非递增特性。当序列中出现2（二进制10）后无法再得到1（二进制01），因此答案不可能超过2。

2. **分层并查集策略**
   - **0的判断**：对每个二进制位建立并查集，若存在某位所有边权在该位均为1，则u→v存在全1路径
   - **1的判断**：引入虚节点0，将偶数边权相邻点与虚节点合并，判断是否存在"全非末位1路径 + 至少一条偶数边"
   - **2的默认**：不满足前两种条件时自动成立

### 解决难点
1. **高效处理30个二进制位**
   使用30个并查集分别维护每个二进制位对应的连通性，时间复杂度O(30mα(n))，空间复杂度O(30n)

2. **偶数边的特殊处理**
   通过虚节点0建立"可到达偶数边"的标记，实现O(1)时间判断是否存在有效偶数边接入点

## 四星题解推荐

### Binary_Lee（★★★★☆）
- **亮点**：完整证明答案范围，清晰拆解判断逻辑，可读性强的分层并查集实现
- **核心代码**：
```cpp
struct DSU{ // 位分片并查集模板
    int fa[100005];
    DSU(){for(int i=0;i<=100000;i++)fa[i]=i;}
    int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
    void merge(int x,int y){fa[find(x)]=find(y);}
    bool query(int x,int y){return find(x)==find(y);}
}x[35],y[35];
```

### Vocaloid世末歌者（★★★★☆）
- **亮点**：引入虚节点简化偶数边判断，代码高度简洁（仅30行核心逻辑）
- **关键步骤**：
```cpp
if(!(w&1)) rep(j,1,29) s1[j].merge(u,0),s1[j].merge(v,0); // 连接虚节点
```

### Mine_King（★★★★☆）
- **亮点**：结构体封装并查集实现复用，完整注释辅助理解
- **特色实现**：
```cpp
for(int i=1;i<30;i++) y[i]=x[i]; // 复制并查集结构
for(int j=1;j<=n;j++) if(f[j]) y[i].merge(j,0); // 动态连接虚节点
```

## 最优思路提炼

### 关键技巧
1. **位分片并查集**  
   每个二进制位独立维护连通性，实现O(1)时间判断某位全1路径

2. **虚节点标记法**  
   将偶数边相邻点与特殊节点0合并，快速判断是否存在偶数边接入点

3. **预处理优化**  
   预先建立所有可能需要的并查集结构，查询时直接使用预计算结果

## 相似题目推荐
1. **P2306 被窃的项链**（位运算+连通性判断）
2. **P1967 货车运输**（最大生成树+路径极值）
3. **CF888G Xor-MST**（位分治+最小生成树）

## 可视化设计

### 算法演示方案
1. **分层染色显示**  
   - 30个并查集对应30个颜色层
   - 滑动条选择二进制位时，显示对应层的连通情况

2. **虚节点特效**  
   用闪烁的黄色节点表示虚节点0，连接偶数边时触发粒子特效

3. **路径追踪动画**  
   - 红色高亮显示当前判断的二进制位路径
   - 绿色标记成功匹配的连通分量

### 复古像素风格
1. **8位调色板**  
   - 背景：#2d1b3c（深紫）
   - 节点：#e5c3b6（米白）
   - 连通线：按位分层彩虹色

2. **音效设计**  
   - 合并节点：8-bit "blip" 音效
   - 成功判定：FC风格胜利音效
   - 错误提示：短促蜂鸣声

3. **自动演示模式**  
   - 按F1启动AI自动遍历所有位判断
   - 方向键控制演示速度（←减速，→加速）

## 核心代码实现
```cpp
// 并查集预处理（以Binary_Lee实现为例）
for(int j=0;j<30;j++)
    if((w>>j)&1) x[j].merge(u,v); // 位分片处理
if(!(w&1)) // 处理虚节点连接
    for(int j=1;j<30;j++)
        y[j].merge(u,0), y[j].merge(v,0);

// 查询处理
int query(int u, int v) {
    for(int j=0;j<30;j++)
        if(x[j].find(u) == x[j].find(v)) return 0;
    for(int j=1;j<30;j++)
        if(y[j].find(u) == y[j].find(0)) return 1;
    return 2;
}
```

---
处理用时：69.73秒