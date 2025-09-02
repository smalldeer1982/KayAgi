# 题目信息

# [USACO08JAN] Cow Contest S

## 题目描述

$ N (1 ≤ N ≤ 100) $ cows, conveniently numbered $ 1 ~ N $ , are participating in a programming contest. As we all know, some cows code better than others. Each cow has a certain constant skill rating that is unique among the competitors.

The contest is conducted in several head-to-head rounds, each between two cows. If cow $ A $ has a greater skill level than cow $ B (1 ≤ A ≤ N; 1 ≤ B ≤ N; A ≠ B) $, then cow $ A $ will always beat cow $ B $ .

Farmer John is trying to rank the cows by skill level. Given a list the results of $ M (1 ≤ M ≤ 4,500) $ two-cow rounds, determine the number of cows whose ranks can be precisely determined from the results. It is guaranteed that the results of the rounds will not be contradictory.

FJ的 $N$（$1 \leq N \leq 100$）头奶牛们最近参加了场程序设计竞赛。在赛场上，奶牛们按 $1, 2, \cdots, N$ 依次编号。每头奶牛的编程能力不尽相同，并且没有哪两头奶牛的水平不相上下，也就是说，奶牛们的编程能力有明确的排名。 整个比赛被分成了若干轮，每一轮是两头指定编号的奶牛的对决。如果编号为 $A$ 的奶牛的编程能力强于编号为 $B$ 的奶牛 （$1 \leq A, B \leq N$，$A \neq B$)，那么她们的对决中，编号为 $A$ 的奶牛总是能胜出。 FJ 想知道奶牛们编程能力的具体排名，于是他找来了奶牛们所有 $M$（$1 \leq M \leq 4,500$）轮比赛的结果，希望你能根据这些信息，推断出尽可能多的奶牛的编程能力排名。比赛结果保证不会自相矛盾。

## 说明/提示

样例解释：

编号为 $2$ 的奶牛输给了编号为 $1, 3, 4$ 的奶牛，也就是说她的水平比这 $3$ 头奶牛都差。而编号为 $5$ 的奶牛又输在了她的手下，也就是说，她的水平比编号为 $5$ 的奶牛强一些。于是，编号为 $2$ 的奶牛的排名必然为第 $4$，编号为 $5$ 的奶牛的水平必然最差。其他 $3$ 头奶牛的排名仍无法确定。

## 样例 #1

### 输入

```
5 5
4 3
4 2
3 2
1 2
2 5```

### 输出

```
2
```

# AI分析结果



### 综合分析与结论
本题需通过给定的胜负关系确定能准确排名的奶牛数量。核心思路是**利用图的传递闭包确定各节点的连通性**。题解主要分为两类：  
1. **Floyd传递闭包**：通过Floyd算法推导所有节点间的可达性，统计每个节点与其他节点是否均有确定关系。  
2. **DFS/BFS遍历**：正向反向遍历图，统计每个节点的间接胜负关系总数。

### 精选题解与评分
#### 1. xun薰的题解（★★★★★）  
**关键亮点**：  
- 使用Floyd的位运算优化传递闭包，代码简洁高效。  
- 逻辑清晰，直接判断每个节点是否与所有其他节点连通。  
**核心代码**：  
```cpp
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j] |= f[i][k] & f[k][j];
```
**个人心得**：  
- 位运算优化 (`|`和`&`) 代替布尔运算，提升性能。

#### 2. Believe_R_的题解（★★★★☆）  
**关键亮点**：  
- 详细解释Floyd的变形应用，强调连通性判断。  
- 提供运算符优先级提示，降低理解门槛。  
**核心代码**：  
```cpp
f[i][j] = f[i][j] || (f[i][k] && f[k][j]);
```

#### 3. lixiao189的题解（★★★★☆）  
**关键亮点**：  
- 双向DFS遍历统计胜负总数，直观展示间接关系。  
- 通过`sum_win + sum_lose == n-1`判断排名确定性。  
**核心代码**：  
```cpp
void dfs_win(int x) {
    for (邻接节点遍历)
        if (未访问) 递归统计胜场;
}
void dfs_lose(int x) {
    for (邻接节点遍历)
        if (未访问) 递归统计负场;
}
```

### 关键思路与技巧
- **传递闭包思想**：通过Floyd算法推导所有间接关系，适用于稠密图。  
- **入度+出度判定**：若节点i的胜负关系总数等于n-1，则排名确定。  
- **双向遍历优化**：正反向DFS/BFS减少重复计算。

### 拓展与举一反三
- **同类题目推荐**：  
  - [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)（Floyd动态更新）  
  - [P1347 排序](https://www.luogu.com.cn/problem/P1347)（拓扑排序确定顺序）  
  - [P1613 跑路](https://www.luogu.com.cn/problem/P1613)（位运算优化最短路）  
- **思维迁移**：传递闭包可用于社交网络连通性分析、状态可达性判断等问题。

### 个人心得摘录
- **位运算优化**（xun薰）：利用`f[i][j] |= f[i][k] & f[k][j]`简化代码，提升运算效率。  
- **双向DFS的直观性**（lixiao189）：正向反向遍历分别统计胜负，降低逻辑复杂度。  
- **拓扑排序的局限性**（karma）：多次拓扑排序比较位置，虽思路独特但时间复杂度较高。

---
处理用时：63.39秒