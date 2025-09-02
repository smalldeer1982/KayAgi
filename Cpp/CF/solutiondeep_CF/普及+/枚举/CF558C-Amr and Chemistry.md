# 题目信息

# Amr and Chemistry

## 题目描述

Amr loves Chemistry, and specially doing experiments. He is preparing for a new interesting experiment.

Amr has $ n $ different types of chemicals. Each chemical $ i $ has an initial volume of $ a_{i} $ liters. For this experiment, Amr has to mix all the chemicals together, but all the chemicals volumes must be equal first. So his task is to make all the chemicals volumes equal.

To do this, Amr can do two different kind of operations.

- Choose some chemical $ i $ and double its current volume so the new volume will be $ 2a_{i} $
- Choose some chemical $ i $ and divide its volume by two (integer division) so the new volume will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF558C/2af906789c62f9845274f856d2f941f2357aa169.png)

Suppose that each chemical is contained in a vessel of infinite volume. Now Amr wonders what is the minimum number of operations required to make all the chemicals volumes equal?

## 说明/提示

In the first sample test, the optimal solution is to divide the second chemical volume by two, and multiply the third chemical volume by two to make all the volumes equal $ 4 $ .

In the second sample test, the optimal solution is to divide the first chemical volume by two, and divide the second and the third chemical volumes by two twice to make all the volumes equal $ 1 $ .

## 样例 #1

### 输入

```
3
4 8 2
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
3 5 6
```

### 输出

```
5```

# AI分析结果

### 题目内容
# Amr和化学

## 题目描述
Amr热爱化学，尤其喜欢做实验。他正在准备一个新的有趣实验。

Amr有$n$种不同类型的化学物质。每种化学物质$i$初始体积为$a_{i}$升。对于这个实验，Amr必须将所有化学物质混合在一起，但首先所有化学物质的体积必须相等。所以他的任务是使所有化学物质的体积相等。

为此，Amr可以进行两种不同类型的操作。
 - 选择某种化学物质$i$，将其当前体积翻倍，新体积将变为$2a_{i}$。
 - 选择某种化学物质$i$，将其体积除以2（整数除法），新体积将变为$\lfloor\frac{a_{i}}{2}\rfloor$。

假设每种化学物质都装在一个体积无限的容器中。现在Amr想知道使所有化学物质体积相等所需的最少操作次数是多少？

## 说明/提示
在第一个样例测试中，最优解决方案是将第二种化学物质的体积除以2，并将第三种化学物质的体积乘以2，使所有体积都等于4。

在第二个样例测试中，最优解决方案是将第一种化学物质的体积除以2，并将第二种和第三种化学物质的体积连续两次除以2，使所有体积都等于1。

## 样例 #1
### 输入
```
3
4 8 2
```
### 输出
```
2```

## 样例 #2
### 输入
```
3
3 5 6
```
### 输出
```
5```

### 综合分析与结论
这些题解主要围绕如何将给定的$n$个数通过乘2或除2（向下取整）操作，使它们达到相等状态并求出最少操作次数。
 - **思路方面**：多数题解将操作映射到二进制层面，乘2等价于二进制末尾补0，除2等价于二进制末尾删除一位。
 - **算法要点**：
    - **01 - Trie树**：利用01 - Trie树来表示数的二进制结构，通过树中节点关系和距离计算操作次数，如IkunTeddy的题解。
    - **换根dp**：在构建的树结构上进行换根dp，找到使所有点到某一点距离最短的点，如KokiNiwa、Marsrayd、Mr_Wu的题解。
    - **枚举状态**：枚举所有数最终可能达到的相等状态，通过桶记录每个状态被达到的次数及所需步数，如DennyQi、沉石鱼惊旋的题解。
    - **贪心**：通过贪心策略，如考虑二进制的公共前缀等方式来确定操作，如汪汪队队长1、KυρωVixen的题解。
 - **解决难点**：主要难点在于如何高效地找到所有数能通过最少操作达到的相等值。不同方法从不同角度解决，如利用树结构的性质、避免状态重复计算等。

### 所选的题解
#### IkunTeddy题解（5星）
 - **关键亮点**：将操作与二进制紧密联系，巧妙利用01 - Trie树结构，清晰地阐述了树中节点距离与操作次数的关系，并通过换根dp得出答案，思路新颖且清晰。
 - **重点代码核心实现思想**：通过`insert`函数将数插入01 - Trie树，记录节点信息。`dfs`函数进行换根dp，根据转移方程`dp[v]=dp[u]-cnt[v]+(n-cnt[v])`计算所有有数字的点走到各节点的总距离，从而找到最小距离即最少操作次数。
```cpp
void insert(int &v,int x,int p,int id,int d){
    if(!v)v=++cnt;
    dep[v]=d;
    tree[v].cnt++;
    if(!p){
        node[id]=v;
        return ;
    }
    int c=(x>>p-1)&1;
    insert(tree[v].son[c],x,p-1,id,d+1);
}
int dp[maxn];
int ans=0x3f3f3f3f;
void dfs(int u){
    ans=min(ans,dp[u]);
    for(int i=0;i<1;i++){
        int v=tree[u].son[i];
        if(!v)continue;
        dp[v]=dp[u]+n-2*tree[v].cnt;
        dfs(v);
    }
}
```
#### KokiNiwa题解（4星）
 - **关键亮点**：同样基于二进制和01 - Trie树的思路，清晰地阐述了问题转化过程，即把数转化为二进制串插入字典树，将操作对应为树中节点的移动，明确指出根节点是所有数的最近公共祖先，并且提到了不建树优化复杂度的思路。
 - **重点代码核心实现思想**：`dfs`函数先计算每个节点子树内有数字的点的个数`sze`。通过循环找到所有数的最近公共祖先`root`。利用`dis`数组记录节点到根的距离，通过循环计算所有点到`root`的距离总和`allDis[root]`，再通过换根操作更新其他节点的距离总和并找到最小值。
```cpp
void dfs(int now) {
    if (now > maxVal) return ;
    int lson = now << 1, rson = now << 1 | 1;
    dfs(lson), dfs(rson);
    sze[now] = mark[now];
    if (lson <= maxVal) sze[now] += sze[lson];
    if (rson <= maxVal) sze[now] += sze[rson];
    return ;
}
//...
for (reg int nodeI = 1; nodeI <= maxVal; ++nodeI)
    allDis[root] += (dis[nodeI] - dis[root]) * mark[nodeI];
for (reg int id = root << 1; id <= maxVal; id = id << 1)
    allDis[id] = allDis[id >> 1] + (totN - sze[id]) - sze[id];
int ans = 0x3f3f3f3f;
for (reg int id = root; id <= maxVal; id = id << 1)
    ans = min(ans, allDis[id]);
```
#### Marsrayd题解（4星）
 - **关键亮点**：通过构建经典二叉树来直观表示操作关系，清晰阐述操作在树中的体现，即点的向上或向左下移动，明确提出通过两次`dfs`进行换根dp的方法来解决问题，逻辑清晰。
 - **重点代码核心实现思想**：`dfs1`函数遍历树计算每个节点子树中加粗节点（给定数表示的节点）的个数`sz`。通过循环找到根节点`x`，并计算所有加粗节点到根节点的距离总和`ans`。`dfs2`函数从根节点开始向左儿子移动，根据公式`tmp=lst+sz[1]-2*sz[now]`更新距离总和并找到最小值。
```cpp
void dfs1(int now)
{
    if(now>mx) return;
    dfs1(now<<1),dfs1(now<<1|1);
    sz[now]+=sz[now<<1]+sz[now<<1|1];
}
void dfs2(int now,long long lst)
{
    if(now>mx) return;
    long long tmp=lst+sz[1]-2*sz[now];
    ans=std::min(ans,tmp);
    dfs2(now<<1,tmp);
}
```

### 最优关键思路或技巧
将数字操作转化为二进制层面的操作，利用树结构（如01 - Trie树或经典二叉树）来直观表示数之间的关系，通过在树结构上进行换根dp找到使所有数达到相等状态的最少操作次数。这种将问题转化为熟悉的数据结构和算法的思维方式是解决此类问题的关键。

### 可拓展之处
同类型题通常围绕数字的位操作、状态转移和最优解求解。类似算法套路包括利用二进制性质简化问题、使用数据结构（如Trie树）优化状态表示和查找、通过动态规划解决最优值问题。

### 推荐题目
 - [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)：涉及字符串与哈希，与本题利用数据结构优化问题求解思路类似。
 - [P2085 最小函数值](https://www.luogu.com.cn/problem/P2085)：通过枚举和动态规划求解最优值，与本题寻找最少操作次数的思路有相通之处。
 - [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：利用动态规划解决序列间的关系问题，与本题在树结构上进行动态规划求解有相似的思维方式。

### 个人心得摘录与总结
 - **KokiNiwa**：提到在使用$Trie$时要记住考虑一个字符串出现多次的情况，避免在此处栽跟头。总结为使用$Trie$树时需注意处理字符串重复出现的问题。 

---
处理用时：45.21秒