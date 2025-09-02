# 题目信息

# Bear and Three Musketeers

## 题目描述

Do you know a story about the three musketeers? Anyway, you will learn about its origins now.

Richelimakieu is a cardinal in the city of Bearis. He is tired of dealing with crime by himself. He needs three brave warriors to help him to fight against bad guys.

There are $ n $ warriors. Richelimakieu wants to choose three of them to become musketeers but it's not that easy. The most important condition is that musketeers must know each other to cooperate efficiently. And they shouldn't be too well known because they could be betrayed by old friends. For each musketeer his recognition is the number of warriors he knows, excluding other two musketeers.

Help Richelimakieu! Find if it is possible to choose three musketeers knowing each other, and what is minimum possible sum of their recognitions.

## 说明/提示

In the first sample Richelimakieu should choose a triple $ 1 $ , $ 2 $ , $ 3 $ . The first musketeer doesn't know anyone except other two musketeers so his recognition is $ 0 $ . The second musketeer has recognition $ 1 $ because he knows warrior number $ 4 $ . The third musketeer also has recognition $ 1 $ because he knows warrior $ 4 $ . Sum of recognitions is $ 0+1+1=2 $ .

The other possible triple is $ 2,3,4 $ but it has greater sum of recognitions, equal to $ 1+1+1=3 $ .

In the second sample there is no triple of warriors knowing each other.

## 样例 #1

### 输入

```
5 6
1 2
1 3
2 3
2 4
3 4
4 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7 4
2 1
3 6
5 1
1 7
```

### 输出

```
-1
```

# AI分析结果



# Bear and Three Musketeers

## 题目描述

你听说过三个火枪手的故事吗？现在你将了解这个故事的起源。

Richelimakieu 是 Bearis 城的主教。他厌倦了独自应对犯罪，需要三名勇敢的战士来帮助他与坏人战斗。

有 $n$ 名战士。Richelimakieu 想从中选出三人成为火枪手，但这并不容易。最重要的条件是火枪手必须彼此认识才能高效合作。同时他们不应该被太多人认识，以免被旧友背叛。每个火枪手的认可度是他认识的战士数量（不包括另外两个火枪手）。

帮助 Richelimakieu！判断是否可以选出三个互相认识的战士，并求他们认可度之和的最小可能值。

## 说明/提示

第一个样例中应选择三元组 1,2,3。第一个火枪手的认可度是 0（除同伴外不认识其他人），第二个和第三个各认识 4 号战士，总和为 0+1+1=2。

第二个样例不存在满足条件的三元组。

## 样例 #1

### 输入
```
5 6
1 2
1 3
2 3
2 4
3 4
4 5
```

### 输出
```
2
```

## 样例 #2

### 输入
```
7 4
2 1
3 6
5 1
1 7
```

### 输出
```
-1
```

**算法分类**：图论

---

### 题解综合分析

#### 核心思路
寻找图中所有三元环（三个互相连接的节点），计算每个三元环的度数之和减6（每个节点减去另外两个同伴），取最小值。

#### 解决难点
1. **暴力枚举优化**：直接三重循环 O(n³) 无法通过大数据（n≤4000）
2. **高效遍历方式**：通过枚举边或邻接关系减少无效遍历
3. **快速判边技巧**：使用邻接矩阵存储实现 O(1) 时间的边存在性判断

---

### 精选题解

#### 1. yangjinqian（⭐⭐⭐⭐⭐）
**关键思路**：枚举所有边，对每条边的两个端点u和v，遍历u的其他邻居w，若w也与v相连则构成三元环。  
**优化点**：时间复杂度 O(mn)，m为边数，充分利用邻接矩阵判边。  
**核心代码**：
```cpp
for (int i = 1; i <= m; i++)
    for (int j = 1; j <= n; j++)
        if (a[x[i]][j] && a[j][y[i]])
            minn = min(minn, num[x[i]] + num[y[i]] + num[j]);
```

#### 2. _saltFish_（⭐⭐⭐⭐）
**关键技巧**：使用链式前向星存储邻接关系，双重遍历邻接节点  
**亮点**：通过邻接表遍历减少冗余判断，配合邻接矩阵判边  
**核心片段**：
```cpp
for(int i=1;i<=n;i++)
    for(int j=h[i];j;j=nxt[j])
        for(int k=h[to[j]];k;k=nxt[k])
            if(can[to[k]][i])
                ans=min(ans,du[i]+du[to[j]]+du[to[k]]-6);
```

#### 3. Noby_Glds（⭐⭐⭐）
**实现思路**：两重邻接表遍历，时间复杂度 O(d²)（d为节点度数）  
**优势**：在稀疏图中表现优异  
**代码亮点**：
```cpp
for(int i=1;i<=n;i++){
    for(int j=head[i];j;j=dl[j].next){
        int v=dl[j].v;
        for(int k=head[v];k;k=dl[k].next)
            if(vis[dl[k].v][i])
                ans=min(ans,in[i]+in[v]+in[dl[k].v]-6);
```

---

### 关键优化技巧
1. **边枚举优先**：相比节点枚举，边枚举能有效利用已有连接信息
2. **度数预处理**：提前存储每个节点的度数，避免实时计算
3. **邻接矩阵判边**：使用二维数组实现 O(1) 时间的边存在性判断

---

### 拓展建议
同类问题可考虑：
1. 三元环计数问题（如 HDU 6184）
2. 寻找最小度数和子图
3. 社交网络中的紧密群体发现

---

### 推荐习题
1. [P1989 三元环计数](https://www.luogu.com.cn/problem/P1989)  
2. [CF985F Isomorphic Strings](https://www.luogu.com.cn/problem/CF985F)  
3. [P3402 可持久化并查集](https://www.luogu.com.cn/problem/P3402)

---

### 心得分镜
_saltFish_ 在题解中提及：
> "枚举边的方式让很多测试点只有 0 毫秒，成功轰下最优解。这让我意识到：在稠密图中，边数远大于节点数时，通过边遍历能极大优化时间复杂度"

这启示我们：在处理图论问题时，应根据图的特点（稀疏/稠密）选择遍历方式，充分利用已知连接信息来减少无效计算。

---
处理用时：63.45秒