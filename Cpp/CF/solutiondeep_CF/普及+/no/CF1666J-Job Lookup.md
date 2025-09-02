# 题目信息

# Job Lookup

## 题目描述

Julia's $ n $ friends want to organize a startup in a new country they moved to. They assigned each other numbers from 1 to $ n $ according to the jobs they have, from the most front-end tasks to the most back-end ones. They also estimated a matrix $ c $ , where $ c_{ij} = c_{ji} $ is the average number of messages per month between people doing jobs $ i $ and $ j $ .

Now they want to make a hierarchy tree. It will be a binary tree with each node containing one member of the team. Some member will be selected as a leader of the team and will be contained in the root node. In order for the leader to be able to easily reach any subordinate, for each node $ v $ of the tree, the following should apply: all members in its left subtree must have smaller numbers than $ v $ , and all members in its right subtree must have larger numbers than $ v $ .

After the hierarchy tree is settled, people doing jobs $ i $ and $ j $ will be communicating via the shortest path in the tree between their nodes. Let's denote the length of this path as $ d_{ij} $ . Thus, the cost of their communication is $ c_{ij} \cdot d_{ij} $ .

Your task is to find a hierarchy tree that minimizes the total cost of communication over all pairs: $ \sum_{1 \le i < j \le n} c_{ij} \cdot d_{ij} $ .

## 说明/提示

The minimal possible total cost is $ 566 \cdot 1+239 \cdot 1+30 \cdot 1+1 \cdot 2+1 \cdot 2=839 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666J/7d043f0dc31fa1bc60f31358d0ccffe9104138cc.png)

## 样例 #1

### 输入

```
4
0 566 1 0
566 0 239 30
1 239 0 1
0 30 1 0```

### 输出

```
2 4 2 0```

# AI分析结果

【题目内容（中文重写）】
# 工作查找

## 题目描述
朱莉娅的 $n$ 个朋友想在他们搬去的一个新国家创办一家初创公司。他们根据各自的工作，从最前端的任务到最后端的任务，给彼此分配了从 1 到 $n$ 的编号。他们还估算了一个矩阵 $c$，其中 $c_{ij} = c_{ji}$ 是从事工作 $i$ 和工作 $j$ 的人每月的平均消息数量。

现在他们想构建一个层级树。这将是一棵二叉树，每个节点包含团队中的一名成员。会选出一名成员作为团队的领导者，该成员将位于根节点。为了让领导者能够轻松联系到任何下属，对于树中的每个节点 $v$，需满足以下条件：其左子树中的所有成员编号必须小于 $v$，右子树中的所有成员编号必须大于 $v$。

层级树确定后，从事工作 $i$ 和工作 $j$ 的人将通过树中他们节点之间的最短路径进行通信。我们用 $d_{ij}$ 表示这条路径的长度。因此，他们的通信成本为 $c_{ij} \cdot d_{ij}$。

你的任务是找到一棵层级树，使所有成对人员的总通信成本最小：$\sum_{1 \le i < j \le n} c_{ij} \cdot d_{ij}$。

## 说明/提示
最小可能的总通信成本是 $566 \cdot 1+239 \cdot 1+30 \cdot 1+1 \cdot 2+1 \cdot 2=839$：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1666J/7d043f0dc31fa1bc60f31358d0ccffe9104138cc.png)

## 样例 #1

### 输入
```
4
0 566 1 0
566 0 239 30
1 239 0 1
0 30 1 0
```

### 输出
```
2 4 2 0
```

【算法分类】
动态规划

【综合分析与结论】
- **思路对比**：各题解均采用区间动态规划的思路，设 $dp_{l,r}$ 表示区间 $[l,r]$ 中所有点贡献之和的最小值，通过枚举区间内的根节点 $k$，将区间划分为左右子树进行状态转移。
- **算法要点**：利用二维前缀和快速计算区间内节点之间的通信消息总数，以优化状态转移时的计算效率。同时，记录每个区间转移时的最优根节点，用于后续递归构造层级树。
- **解决难点**：关键在于如何将 $d_{i,j}$ 拆分到每条边上统计贡献，通过计算子树内节点到子树外节点的通话数来确定合并子树时产生的新贡献。

【所选题解】
- **DaiRuiChen007（5星）**：
    - **关键亮点**：思路清晰，代码注释详细，对状态转移方程和二维前缀和的使用解释明确，便于理解。
- **hyman00（4星）**：
    - **关键亮点**：代码简洁，逻辑清晰，通过 `pii` 类型记录最优状态和根节点，实现较为巧妙。
- **Redamancy_Lydic（4星）**：
    - **关键亮点**：详细阐述了区间动态规划的思路，代码结构清晰，包含输入优化函数。

【重点代码】
以下是 DaiRuiChen007 题解的核心代码：
```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
const int MAXN=201,INF=1e17;
int dp[MAXN][MAXN],rt[MAXN][MAXN],c[MAXN][MAXN],sum[MAXN][MAXN],fa[MAXN];
inline void dfs(int l,int r,int f) {
    if(l>r) return ;
    int k=rt[l][r];
    fa[k]=f;
    dfs(l,k-1,k),dfs(k+1,r,k);
}
inline int cnt(int r1,int r2,int c1,int c2) {
    if(r1>r2||c1>c2) return 0;
    return sum[r2][c2]-sum[r2][c1-1]-sum[r1-1][c2]+sum[r1-1][c1-1];
}
signed main() {
    int n;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) {
        for(int j=1;j<=n;++j) {
            scanf("%lld",&c[i][j]);
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+c[i][j];
        }
    }
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) dp[i][j]=INF;
    for(int i=1;i<=n;++i) dp[i][i]=0,rt[i][i]=i;
    for(int len=1;len<n;++len) {
        for(int l=1,r=l+len;r<=n;++l,++r) {
            for(int k=l;k<=r;++k) {
                int val=cnt(l,k-1,1,l-1)+cnt(l,k-1,k,n)+
                        cnt(k+1,r,1,k)+cnt(k+1,r,r+1,n)+
                        (k==l?0:dp[l][k-1])+(k==r?0:dp[k+1][r]);
                if(val<dp[l][r]) rt[l][r]=k,dp[l][r]=val;
            }
        }
    }
    dfs(1,n,0);
    for(int i=1;i<=n;++i) printf("%lld ",fa[i]);
    puts("");
    return 0;
}
```
**核心实现思想**：
1. 首先读取输入的矩阵 $c$，并计算二维前缀和矩阵 $sum$。
2. 初始化 $dp$ 数组和 $rt$ 数组，$dp_{i,i}=0$ 表示单个节点的贡献为 0，$rt_{i,i}=i$ 表示单个节点的根节点为自身。
3. 通过区间动态规划，枚举区间长度和区间左右端点，再枚举区间内的根节点 $k$，计算状态转移方程的值，更新 $dp$ 数组和 $rt$ 数组。
4. 最后通过递归函数 `dfs` 构造层级树，输出每个节点的父节点。

【扩展思路】
同类型题或类似算法套路：
- 区间动态规划在处理具有区间性质的最优子结构问题时非常有效，如石子合并问题、矩阵链乘法问题等。
- 对于涉及树结构的问题，可结合树的性质和动态规划的思想，通过枚举根节点将问题分解为子问题进行求解。

【推荐题目】
1. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P3146 [USACO16OPEN]248 G](https://www.luogu.com.cn/problem/P3146)
3. [P4170 [CQOI2007]涂色](https://www.luogu.com.cn/problem/P4170)

【个人心得】
题解中未包含个人心得。

---
处理用时：48.89秒