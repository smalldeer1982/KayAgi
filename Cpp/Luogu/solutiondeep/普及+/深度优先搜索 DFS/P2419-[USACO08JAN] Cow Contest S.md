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
本题核心在于通过已知胜负关系推断所有可能的间接关系，从而确定每个节点的全局排名。各题解主要采用三种思路：**Floyd传递闭包**、**双向DFS遍历**、**拓扑排序衍生方法**，其中Floyd算法因其简洁性和高效性成为最优解。

---

### 精选题解与亮点

#### 1. xun薰（五星）
**关键亮点**：  
- 使用Floyd算法快速计算传递闭包，判断每头牛与其他牛的胜负关系。  
- 通过位运算优化判断逻辑（`f[i][j] = f[i][j] | (f[i][k] & f[k][j])`），提升代码效率。  
- 代码简洁清晰，逻辑紧凑，时间复杂度O(n³)完全符合题目约束。

**核心代码**：
```cpp
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j] = f[i][j] | (f[i][k] & f[k][j]);
```

#### 2. lixiao189（四星）
**关键亮点**：  
- 双向DFS分别统计每头牛能击败和被击败的数量，验证`sum_win + sum_lose == n-1`。  
- 建立正反图进行两次DFS遍历，直观体现间接关系。  
- 代码可读性强，适合理解DFS在图遍历中的应用。

**核心代码**：
```cpp
void dfs_win(int x) {
    for (auto it : win_graph[x]) {
        if (!vis_win[it]) {
            sum_win++;
            dfs_win(it);
        }
    }
}
// 反向DFS同理
```

#### 3. Starria的脑残粉（四星）
**关键亮点**：  
- 邻接矩阵实现双向DFS，简化代码结构。  
- 合并正反遍历结果，直接判断`dfs1(i)+dfs2(i)-1 == n`，逻辑简洁。  
- 适用于对空间复杂度敏感的场景。

**核心代码**：
```cpp
int dfs1(int d) { // 正向遍历
    for(int i=1; i<=n; i++)
        if(a[d][i] && !flag[i]) ans += dfs1(i);
    return ans;
}
```

---

### 关键思路与技巧
1. **Floyd传递闭包**：通过三重循环更新所有节点间的可达性，适合快速判断全局关系。
2. **双向遍历统计**：正反图遍历可分别计算每个节点的支配集与被支配集，总和决定排名。
3. **位运算优化**：使用按位与或运算简化布尔矩阵操作，提升代码效率。

---

### 拓展练习
1. [P1613 跑路](https://www.luogu.com.cn/problem/P1613)（Floyd+位运算优化）  
2. [P2881 [USACO07MAR]排名的牛](https://www.luogu.com.cn/problem/P2881)（传递闭包应用）  
3. [P2412 查单词](https://www.luogu.com.cn/problem/P2412)（拓扑排序与关系推导）

---
处理用时：46.82秒