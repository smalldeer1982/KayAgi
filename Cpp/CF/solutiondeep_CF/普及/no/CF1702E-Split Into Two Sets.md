# 题目信息

# Split Into Two Sets

## 题目描述

Polycarp was recently given a set of $ n $ (number $ n $ — even) dominoes. Each domino contains two integers from $ 1 $ to $ n $ .

Can he divide all the dominoes into two sets so that all the numbers on the dominoes of each set are different? Each domino must go into exactly one of the two sets.

For example, if he has $ 4 $ dominoes: $ \{1, 4\} $ , $ \{1, 3\} $ , $ \{3, 2\} $ and $ \{4, 2\} $ , then Polycarp will be able to divide them into two sets in the required way. The first set can include the first and third dominoes ( $ \{1, 4\} $ and $ \{3, 2\} $ ), and the second set — the second and fourth ones ( $ \{1, 3\} $ and $ \{4, 2\} $ ).

## 说明/提示

In the first test case, the dominoes can be divided as follows:

- First set of dominoes: $ [\{1, 2\}, \{4, 3\}] $
- Second set of dominoes: $ [\{2, 1\}, \{3, 4\}] $

 In other words, in the first set we take dominoes with numbers $ 1 $ and $ 2 $ , and in the second set we take dominoes with numbers $ 3 $ and $ 4 $ .In the second test case, there's no way to divide dominoes into $ 2 $ sets, at least one of them will contain repeated number.

## 样例 #1

### 输入

```
6
4
1 2
4 3
2 1
3 4
6
1 2
4 5
1 3
4 6
2 3
5 6
2
1 1
2 2
2
1 2
2 1
8
2 1
1 2
4 3
4 3
5 6
5 7
8 6
7 8
8
1 2
2 1
4 3
5 3
5 4
6 7
8 6
7 8```

### 输出

```
YES
NO
NO
YES
YES
NO```

# AI分析结果

### 题目内容重写
**题目描述**

Polycarp 最近得到了一组 $n$（$n$ 为偶数）个多米诺骨牌。每个多米诺骨牌上包含两个整数，范围从 $1$ 到 $n$。

他能否将所有的多米诺骨牌分成两个集合，使得每个集合中的多米诺骨牌上的数字都不重复？每个多米诺骨牌必须恰好放入其中一个集合。

例如，如果他有 $4$ 个多米诺骨牌：$\{1, 4\}$、$\{1, 3\}$、$\{3, 2\}$ 和 $\{4, 2\}$，那么 Polycarp 可以将它们按照要求分成两个集合。第一个集合可以包含第一个和第三个多米诺骨牌（$\{1, 4\}$ 和 $\{3, 2\}$），第二个集合包含第二个和第四个多米诺骨牌（$\{1, 3\}$ 和 $\{4, 2\}$）。

**说明/提示**

在第一个测试用例中，多米诺骨牌可以如下划分：

- 第一个集合：$[\{1, 2\}, \{4, 3\}]$
- 第二个集合：$[\{2, 1\}, \{3, 4\}]$

换句话说，第一个集合中包含数字 $1$ 和 $2$，第二个集合中包含数字 $3$ 和 $4$。在第二个测试用例中，无法将多米诺骨牌分成两个集合，至少有一个集合中会包含重复的数字。

**样例 #1**

### 输入
```
6
4
1 2
4 3
2 1
3 4
6
1 2
4 5
1 3
4 6
2 3
5 6
2
1 1
2 2
2
1 2
2 1
8
2 1
1 2
4 3
4 3
5 6
5 7
8 6
7 8
8
1 2
2 1
4 3
5 3
5 4
6 7
8 6
7 8
```

### 输出
```
YES
NO
NO
YES
YES
NO
```

### 算法分类
图论、并查集

### 题解分析与结论
该题的核心问题是将多米诺骨牌分成两个集合，使得每个集合中的数字不重复。这个问题可以转化为图论中的二分图判定问题。具体来说，可以将每个多米诺骨牌看作图中的一个节点，如果两个多米诺骨牌上有相同的数字，则在这两个节点之间连一条边。最终需要判断这个图是否是二分图。

### 所选题解
#### 题解1：tzyt (赞：19)
**星级：5星**
**关键亮点：**
- 通过图论的角度分析问题，将问题转化为二分图判定。
- 使用DFS进行二分图染色，判断图是否为二分图。
- 代码简洁且高效，时间复杂度为$O(n)$。

**个人心得：**
- 作者提到贪心算法的错误性，并给出了反例，强调了图论方法的重要性。

**核心代码：**
```cpp
bool iseven_cycle(int cur, int fa, bool cur_color) {
    if (e[cur].size() < 2) return true;
    for (E &nex : e[cur]) {
        if (nex.to == fa) continue;
        if (nex.color == -1)
            nex.color = !cur_color;
        else if (nex.color == cur_color)
            return false;
        else if (nex.color == !cur_color)
            return true;
        if (!iseven_cycle(nex.to, cur, !cur_color)) return false;
    }
    return true;
}
```

#### 题解2：8atemak1r (赞：11)
**星级：4星**
**关键亮点：**
- 使用并查集来维护二分图的判定，避免了DFS的递归深度问题。
- 通过并查集的路径压缩和按秩合并优化了性能。

**核心代码：**
```cpp
int find(int k) {
    if(fa[k] == k) return k;
    return fa[k] = find(fa[k]);
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if(fx == fy) return;
    if(siz[fx] > siz[fy]) f[fy] = fx, siz[fx] += siz[fy];
    else f[fx] = fy, siz[fy] += siz[fx];
}
```

#### 题解3：Wonder_Fish (赞：4)
**星级：4星**
**关键亮点：**
- 使用二分图染色法，通过BFS实现二分图判定。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
bool check() {
    queue<int> q;
    memset(c, 0, sizeof(c));
    for(int i = 1; i <= n; i++) {
        if(!c[i]) {
            q.push(i); c[i] = 1;
            while(!q.empty()) {
                int x = q.front(); q.pop();
                for(int j = 0; j < g[x].size(); ++j) {
                    int y = g[x][j];
                    if(!c[y]) {
                        q.push(y);
                        if(c[x] == 1) c[y] = 2;
                        else c[y] = 1;
                    }
                    else if(c[y] == c[x]) return false;
                }
            }
        }
    }
    return true;
}
```

### 最优关键思路或技巧
1. **图论转化**：将多米诺骨牌上的数字关系转化为图中的边，通过二分图判定来解决问题。
2. **并查集优化**：使用并查集来维护二分图的判定，避免了DFS的递归深度问题，适合大规模数据。
3. **二分图染色**：通过DFS或BFS进行二分图染色，判断图是否为二分图。

### 可拓展之处
该题的图论方法可以拓展到其他类似的二分图判定问题，如判断图中的节点是否可以分成两个集合，使得集合内的节点没有边相连。

### 推荐题目
1. [P1892 [BOI2003]团伙](https://www.luogu.com.cn/problem/P1892)
2. [P1525 [NOIP2010 提高组] 关押罪犯](https://www.luogu.com.cn/problem/P1525)
3. [P5937 [CEOI1999]Parity Game](https://www.luogu.com.cn/problem/P5937)

---
处理用时：45.77秒