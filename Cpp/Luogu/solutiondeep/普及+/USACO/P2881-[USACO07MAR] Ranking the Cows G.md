# 题目信息

# [USACO07MAR] Ranking the Cows G

## 题目描述

Each of Farmer John's N cows (1 ≤ N ≤ 1,000) produces milk at a different positive rate, and FJ would like to order his cows according to these rates from the fastest milk producer to the slowest.

FJ has already compared the milk output rate for M (1 ≤ M ≤ 10,000) pairs of cows. He wants to make a list of C additional pairs of cows such that, if he now compares those C pairs, he will definitely be able to deduce the correct ordering of all N cows. Please help him determine the minimum value of C for which such a list is possible.

FJ想按照奶牛产奶的能力给她们排序。现在已知有N头奶牛（1 ≤ N ≤ 1,000）。FJ通过比较，已经知道了M（1 ≤ M ≤ 10,000）对相对关系。每一对关系表示为“X Y”，意指X的产奶能力强于Y。现在FJ想要知道，他至少还要调查多少对关系才能完成整个排序。


## 说明/提示

From the information in the 5 test results, Farmer John knows that since cow 2 > cow 1 > cow 5 and cow 2 > cow 3 > cow 4, cow 2 has the highest rank. However, he needs to know whether cow 1 > cow 3 to determine the cow with the second highest rank. Also, he will need one more question to determine the ordering between cow 4 and cow 5. After that, he will need to know if cow 5 > cow 3 if cow 1 has higher rank than cow 3. He will have to ask three questions in order to be sure he has the rankings: "Is cow 1 > cow 3?  Is cow 4 > cow 5? Is cow 5 > cow 3?"


## 样例 #1

### 输入

```
5 5
2 1
1 5
2 3
1 4
3 4```

### 输出

```
3```

# AI分析结果

### 综合分析与结论
本题核心是求在已知部分奶牛产奶能力大小关系的情况下，还需确定多少对关系才能完成所有奶牛的排序，可转化为求传递闭包问题。各题解主要围绕Floyd算法、拓扑排序和DFS等方法展开，且部分使用bitset优化复杂度。

### 所选题解
- **作者：panyf（5星）**
    - **关键亮点**：详细介绍传递闭包的四种求法，对每种方法的复杂度和适用场景分析清晰，代码实现完整且有对应提交记录。
    - **核心代码及思想**：
```cpp
// 做法1：Floyd + bitset优化
for(i=1;i<=n;++i)for(j=1;j<=n;++j)if(b[j][i])b[j]|=b[i];
```
思想：枚举中转点`i`，若`b[j][i]`为真，说明`j`能到`i`，则将`j`能到达的点集更新为`j`原来能到达的点集和`i`能到达的点集的并集。

```cpp
// 做法2：以每个点为起点深搜
void dfs(int x){for(int i:g[x])if(!b[i])b[i]=1,--s,dfs(i);}
```
思想：从每个点出发进行深度优先搜索，标记能到达的点，同时更新未确定关系的对数。

```cpp
// 做法3：缩点后dfs
void dfs(int x){
    b[x][x]=1;
    for(int i:g[x]){
        if(!b[i][i])dfs(i);
        b[x]|=b[i];
    }
}
```
思想：先对图进行缩点（本题为DAG可省略），然后从每个点出发dfs，若当前点未被访问过则递归访问，最后更新当前点能到达的点集。

```cpp
// 做法4：缩点后按拓扑序分块求解
for(i=1;i<=n;++i)if(b[i][i]=1,!(i&7)){
    for(j=1;j<256;++j)l=j&-j,o[j]=o[j^l]|b[i-7+__lg(l)];
    for(j=i+1;j<=n;b[j++]|=o[l])for(r=l=0;r<8;++r)if(e[j][i-7+r])l|=1<<r;
}else for(j=min(n,i/8*8+8);j>i;--j)if(e[j][i])b[j]|=b[i];
```
思想：先缩点求拓扑序，按拓扑序每8个点分一块，倒序求解，通过子集的可达集合更新每个点的可达集合。

- **作者：zhzh2001（4星）**
    - **关键亮点**：介绍改进Floyd和拓扑排序两种方法，给出理论分析和代码实现，对复杂度有明确说明，总结了不同图的适用方法。
    - **核心代码及思想**：
```cpp
// 改进Floyd
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        if(mat[i][k])
            mat[i]|=mat[k];
```
思想：枚举中转点`k`，若`mat[i][k]`为真，说明`i`能到`k`，则将`i`能到达的点集更新为`i`原来能到达的点集和`k`能到达的点集的并集。

```cpp
// 拓扑排序
void dfs(int k)
{
    mat[k][k]=vis[k]=true;
    for(int i=head[k];i;i=nxt[i])
    {
        if(!vis[v[i]])
            dfs(v[i]);
        mat[k]|=mat[v[i]];
    }
}
```
思想：从每个未访问的点出发进行dfs，标记当前点已访问，递归访问其邻接点，最后更新当前点能到达的点集。

- **作者：Mine_King（4星）**
    - **关键亮点**：详细讲解Floyd和拓扑排序两种做法，对复杂度进行分析，并介绍bitset优化方法，代码示例清晰。
    - **核心代码及思想**：
```cpp
// Floyd做法
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=f[i][j]|(f[i][k]&f[k][j]);
```
思想：经典Floyd算法，枚举中转点`k`，若`i`能到`k`且`k`能到`j`，则`i`能到`j`。

```cpp
// 拓扑排序做法
while(!q.empty())
{
    int x=q.front();
    for(int i=1;i<=n;i++)
        if(g[x][i])
        {
            for(int j=1;j<=n;j++)
                if(f[x][j]) f[i][j]=true;
            if(!--in[i]) q.push(i);
        }
}
```
思想：按拓扑序遍历点，若`x`到`i`有边，则将`x`能到达的点集更新到`i`能到达的点集中。

```cpp
// bitset对Floyd的优化
for(int k=1;k<=n;k++)
    for(int j=1;j<=n;j++)
        if(g[k][j])
            f[j]|=f[k];
```
思想：枚举中转点`k`和终点`j`，若`k`到`j`有边，则将`j`能到达的点集更新为`j`原来能到达的点集和`k`能到达的点集的并集。

### 最优关键思路或技巧
- **使用bitset优化**：将布尔数组用bitset替代，利用位运算一次处理多个位，可将时间复杂度从$O(n^3)$优化到$O(\frac{n^3}{w})$，其中$w$为计算机的位数。
- **拓扑排序**：对于DAG图，按拓扑序更新点的可达集合，避免重复计算，复杂度可优化到$O(\frac{nm}{w})$。

### 可拓展之处
同类型题如求图中任意两点的连通性、传递关系的推导等。类似算法套路包括Tarjan缩点处理有环图、分块优化等。

### 推荐题目
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：Floyd算法的动态应用。
- [P2419 [USACO08JAN]Cow Contest S](https://www.luogu.com.cn/problem/P2419)：求传递闭包确定排名的问题。
- [P3905 道路重建](https://www.luogu.com.cn/problem/P3905)：涉及图的连通性和传递关系。

### 个人心得
- **xkcdjerry**：发现Floyd算法中若`f[i][k]`为`false`，则可直接跳过内层循环，避免不必要的计算，从而优化算法。 

---
处理用时：41.58秒