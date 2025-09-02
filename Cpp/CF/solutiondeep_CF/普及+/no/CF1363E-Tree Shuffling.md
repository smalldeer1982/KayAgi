# 题目信息

# Tree Shuffling

## 题目描述

Ashish has a tree consisting of $ n $ nodes numbered $ 1 $ to $ n $ rooted at node $ 1 $ . The $ i $ -th node in the tree has a cost $ a_i $ , and binary digit $ b_i $ is written in it. He wants to have binary digit $ c_i $ written in the $ i $ -th node in the end.

To achieve this, he can perform the following operation any number of times:

- Select any $ k $ nodes from the subtree of any node $ u $ , and shuffle the digits in these nodes as he wishes, incurring a cost of $ k \cdot a_u $ . Here, he can choose $ k $ ranging from $ 1 $ to the size of the subtree of $ u $ .

He wants to perform the operations in such a way that every node finally has the digit corresponding to its target.

Help him find the minimum total cost he needs to spend so that after all the operations, every node $ u $ has digit $ c_u $ written in it, or determine that it is impossible.

## 说明/提示

The tree corresponding to samples $ 1 $ and $ 2 $ are:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1363E/7a89fb5868f7e2cc9a5cf05da12869789d228775.png)In sample $ 1 $ , we can choose node $ 1 $ and $ k = 4 $ for a cost of $ 4 \cdot 1 $ = $ 4 $ and select nodes $ {1, 2, 3, 5} $ , shuffle their digits and get the desired digits in every node.

In sample $ 2 $ , we can choose node $ 1 $ and $ k = 2 $ for a cost of $ 10000 \cdot 2 $ , select nodes $ {1, 5} $ and exchange their digits, and similarly, choose node $ 2 $ and $ k = 2 $ for a cost of $ 2000 \cdot 2 $ , select nodes $ {2, 3} $ and exchange their digits to get the desired digits in every node.

In sample $ 3 $ , it is impossible to get the desired digits, because there is no node with digit $ 1 $ initially.

## 样例 #1

### 输入

```
5
1 0 1
20 1 0
300 0 1
4000 0 0
50000 1 0
1 2
2 3
2 4
1 5```

### 输出

```
4```

## 样例 #2

### 输入

```
5
10000 0 1
2000 1 0
300 0 1
40 0 0
1 1 0
1 2
2 3
2 4
1 5```

### 输出

```
24000```

## 样例 #3

### 输入

```
2
109 0 1
205 0 1
1 2```

### 输出

```
-1```

# AI分析结果

### 题目翻译
#### 树的洗牌

### 题目描述
阿希什有一棵由 $n$ 个节点组成的树，节点编号从 $1$ 到 $n$，根节点为 $1$。树中的第 $i$ 个节点有一个代价 $a_i$，并且其中写有一个二进制数字 $b_i$。他希望最终第 $i$ 个节点中写有二进制数字 $c_i$。

为了实现这一目标，他可以进行以下操作任意次数：
- 从任意节点 $u$ 的子树中选择任意 $k$ 个节点，并按照他的意愿对这些节点中的数字进行洗牌，产生的代价为 $k \cdot a_u$。这里，他可以选择的 $k$ 范围是从 $1$ 到节点 $u$ 子树的大小。

他希望以这样的方式执行操作，使得每个节点最终都具有与其目标对应的数字。

帮助他找到在所有操作之后，每个节点 $u$ 都写有数字 $c_u$ 所需花费的最小总代价，或者确定这是不可能的。

### 说明/提示
对应样本 $1$ 和 $2$ 的树如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1363E/7a89fb5868f7e2cc9a5cf05da12869789d228775.png)
在样本 $1$ 中，我们可以选择节点 $1$ 并取 $k = 4$，代价为 $4 \cdot 1 = 4$，选择节点 $\{1, 2, 3, 5\}$，对它们的数字进行洗牌，从而在每个节点中得到所需的数字。

在样本 $2$ 中，我们可以选择节点 $1$ 并取 $k = 2$，代价为 $10000 \cdot 2$，选择节点 $\{1, 5\}$ 并交换它们的数字，同样地，选择节点 $2$ 并取 $k = 2$，代价为 $2000 \cdot 2$，选择节点 $\{2, 3\}$ 并交换它们的数字，从而在每个节点中得到所需的数字。

在样本 $3$ 中，不可能得到所需的数字，因为最初没有数字为 $1$ 的节点。

### 样例 #1
#### 输入
```
5
1 0 1
20 1 0
300 0 1
4000 0 0
50000 1 0
1 2
2 3
2 4
1 5
```
#### 输出
```
4
```

### 样例 #2
#### 输入
```
5
10000 0 1
2000 1 0
300 0 1
40 0 0
1 1 0
1 2
2 3
2 4
1 5
```
#### 输出
```
24000
```

### 样例 #3
#### 输入
```
2
109 0 1
205 0 1
1 2
```
#### 输出
```
-1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，利用树的性质进行操作。首先发现一个节点的操作可由其祖先完成，所以将每个节点的花费更新为其到根路径上点的费用的最小值，这样可以在子树中贪心交换。在交换过程中，记录子树内位置不对的 $0$ 和 $1$ 的个数，每次操作选择 $0$、$1$ 中错误个数较小的进行重新排列。对于无法完成目标状态（即初始 $1$ 的总数和目标 $1$ 的总数不相等）的情况，直接输出 $-1$。

### 所选题解
- **作者：fighter (赞：10)，4星**
    - **关键亮点**：思路清晰，代码简洁易懂，直接实现了贪心算法的核心逻辑。
- **作者：lcc17 (赞：0)，4星**
    - **关键亮点**：使用树形 dp 的思想，对每个节点的子树状态进行记录和更新，逻辑清晰。
- **作者：Fairicle (赞：0)，4星**
    - **关键亮点**：同样基于贪心思想，在 dfs 过程中更新最小值，代码简洁。

### 重点代码
#### fighter 的题解核心代码
```cpp
void dfs(int x, int fa){
    if(x != 1) a[x] = min(a[x], a[fa]);
    s[x][b[x]] += (b[x]!=c[x]);
    for(int i = head[x]; i; i = Next[i]){
        int v = vet[i];
        if(v == fa) continue;
        dfs(v, x);
        s[x][0] += s[v][0], s[x][1] += s[v][1];
    }
    int t = min(s[x][0], s[x][1]);
    ans += a[x]*t*2;
    s[x][0] -= t, s[x][1] -= t;
}
```
**核心实现思想**：在 dfs 过程中，更新节点的花费为其和父节点花费的最小值，统计子树内位置不对的 $0$ 和 $1$ 的个数，每次选择较小的个数进行交换并更新答案。

#### lcc17 的题解核心代码
```cpp
void dfs(int u, int fa){
    if(u!=1) a[u]=min(a[u],a[fa]);
    dp[u][b[u]]+=(b[u]!=c[u]);
    for(int i=head[u];i;i=e[i].ne){
        int v=e[i].to;
        if(v==fa) continue;
        dfs(v,u);
        dp[u][0]+=dp[v][0];dp[u][1]+=dp[v][1];
    }
    int minn=min(dp[u][0],dp[u][1]);
    ans=ans+2*minn*a[u];
    dp[u][0]-=minn,dp[u][1]-=minn;
}
```
**核心实现思想**：通过树形 dp 记录子树内状态，更新节点花费，计算可交换的最小个数并更新答案。

#### Fairicle 的题解核心代码
```cpp
void dfs(int now, int fa){
    if(now!=1)
        a[now]=min(a[now],a[fa]);
    s[now][b[now]]=(b[now]!=c[now]);
    for(ri i=head[now];i;i=star[i].nxt){
        int u=star[i].to;
        if(u==fa) continue;
        dfs(u,now);
        s[now][0]+=s[u][0],s[now][1]+=s[u][1];
    }
    ll x=min(s[now][0],s[now][1]);
    ans+=2ll*x*a[now];
    s[now][0]-=x,s[now][1]-=x;
}
```
**核心实现思想**：在 dfs 中更新节点花费，统计子树内状态，选择最小个数交换并更新答案。

### 关键思路或技巧
- **贪心策略**：优先在花费小的节点进行操作，每次选择子树内位置不对的 $0$ 和 $1$ 中个数较小的进行交换。
- **更新节点花费**：将每个节点的花费更新为其到根路径上点的费用的最小值，简化操作。
- **树形 dfs**：利用深度优先搜索遍历树，统计子树内状态。

### 拓展思路
同类型题可以是树上的其他操作优化问题，例如树上的染色问题、树上的路径选择问题等。类似算法套路可以是先分析树的性质，然后利用贪心或动态规划的思想，结合深度优先搜索进行状态的统计和更新。

### 推荐题目
- [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)：树形 dp 经典题目，通过深度优先搜索遍历树，更新节点状态。
- [P2014 选课](https://www.luogu.com.cn/problem/P2014)：树上的分组背包问题，利用树形 dp 解决。
- [P1272 重建道路](https://www.luogu.com.cn/problem/P1272)：树上的删边问题，通过树形 dp 计算最小删边数。

### 个人心得
- **ShineEternal**：提到 u 和 i 在键盘上离得太近，导致在 i 的循环内错打为 u，这提醒我们在编码时要注意变量名的区分，避免因输入错误导致的 bug。

---
处理用时：61.63秒