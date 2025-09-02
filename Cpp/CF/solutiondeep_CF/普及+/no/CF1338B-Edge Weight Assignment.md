# 题目信息

# Edge Weight Assignment

## 题目描述

You have unweighted tree of $ n $ vertices. You have to assign a positive weight to each edge so that the following condition would hold:

- For every two different leaves $ v_{1} $ and $ v_{2} $ of this tree, [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of weights of all edges on the simple path between $ v_{1} $ and $ v_{2} $ has to be equal to $ 0 $ .

Note that you can put very large positive integers (like $ 10^{(10^{10})} $ ).

It's guaranteed that such assignment always exists under given constraints. Now let's define $ f $ as the number of distinct weights in assignment.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/eb47baeab358a9bf4d6536421055c2c258904b33.png) In this example, assignment is valid, because bitwise XOR of all edge weights between every pair of leaves is $ 0 $ . $ f $ value is $ 2 $ here, because there are $ 2 $ distinct edge weights( $ 4 $ and $ 5 $ ).![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/158a70d1382d5b7e8863700d0f77901af19c305f.png) In this example, assignment is invalid, because bitwise XOR of all edge weights between vertex $ 1 $ and vertex $ 6 $ ( $ 3, 4, 5, 4 $ ) is not $ 0 $ .

What are the minimum and the maximum possible values of $ f $ for the given tree? Find and print both.

## 说明/提示

In the first example, possible assignments for each minimum and maximum are described in picture below. Of course, there are multiple possible assignments for each minimum and maximum.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/c4eae7135fc2816569401e9d249b68afcb80223d.png)In the second example, possible assignments for each minimum and maximum are described in picture below. The $ f $ value of valid assignment of this tree is always $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/baad69bf823b2a9aa4bb5b201a45aae8769d51f6.png)In the third example, possible assignments for each minimum and maximum are described in picture below. Of course, there are multiple possible assignments for each minimum and maximum.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/4ce205cbdc1e4310ee123b92671ae7a1941bacd7.png)

## 样例 #1

### 输入

```
6
1 3
2 3
3 4
4 5
5 6```

### 输出

```
1 4```

## 样例 #2

### 输入

```
6
1 3
2 3
3 4
4 5
4 6```

### 输出

```
3 3```

## 样例 #3

### 输入

```
7
1 2
2 7
3 4
4 7
5 6
6 7```

### 输出

```
1 6```

# AI分析结果

### 题目翻译
## 边权赋值

### 题目描述
你有一棵包含 $n$ 个顶点的无权树。你需要为每条边分配一个正权重，使得以下条件成立：
- 对于这棵树的每两个不同的叶子节点 $v_1$ 和 $v_2$，$v_1$ 和 $v_2$ 之间简单路径上所有边的权重的[按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)值必须等于 $0$。

请注意，你可以使用非常大的正整数（例如 $10^{(10^{10})}$）。

在给定的约束条件下，保证这样的赋值总是存在。现在定义 $f$ 为赋值中不同权重的数量。

![示例1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/eb47baeab358a9bf4d6536421055c2c258904b33.png) 在这个例子中，赋值是有效的，因为每对叶子节点之间所有边权重的按位异或值都是 $0$。这里的 $f$ 值是 $2$，因为有 $2$ 个不同的边权重（$4$ 和 $5$）。
![示例2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/158a70d1382d5b7e8863700d0f77901af19c305f.png) 在这个例子中，赋值是无效的，因为顶点 $1$ 和顶点 $6$ 之间所有边权重（$3, 4, 5, 4$）的按位异或值不是 $0$。

对于给定的树，$f$ 的最小和最大可能值是多少？请找出并打印这两个值。

### 说明/提示
在第一个示例中，每个最小值和最大值的可能赋值如下图所示。当然，每个最小值和最大值都有多种可能的赋值。
![示例1](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/c4eae7135fc2816569401e9d249b68afcb80223d.png)
在第二个示例中，每个最小值和最大值的可能赋值如下图所示。这棵树的有效赋值的 $f$ 值始终为 $3$。
![示例2](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/baad69bf823b2a9aa4bb5b201a45aae8769d51f6.png)
在第三个示例中，每个最小值和最大值的可能赋值如下图所示。当然，每个最小值和最大值都有多种可能的赋值。
![示例3](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338B/4ce205cbdc1e4310ee123b92671ae7a1941bacd7.png)

### 样例 #1
#### 输入
```
6
1 3
2 3
3 4
4 5
5 6
```
#### 输出
```
1 4
```

### 样例 #2
#### 输入
```
6
1 3
2 3
3 4
4 5
4 6
```
#### 输出
```
3 3
```

### 样例 #3
#### 输入
```
7
1 2
2 7
3 4
4 7
5 6
6 7
```
#### 输出
```
1 6
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是先确定一个非叶子节点作为根节点，然后分别求解边权种类的最小值和最大值。
- **最小值**：若所有叶子节点到根节点的路径长度奇偶性相同，答案为 $1$；否则为 $3$。因为偶数个相同数异或为 $0$，而存在奇数长度路径时，需用 $1,2,3$ 三种权值构造。
- **最大值**：初始将最大值设为边数，若一个节点有 $k$ 个儿子为叶子节点，它们到父亲的权值必须相同，最大值减去 $k - 1$。

各题解主要使用深度优先搜索（DFS）遍历树，判断叶子节点深度的奇偶性，计算最大值时统计叶子节点的分布情况。

### 所选题解
- **Marser（5星）**
    - **关键亮点**：思路清晰，对最小值和最大值的分析详细，通过构造具体的赋值方案解释最小值的两种情况，代码实现规范，有详细注释。
    - **个人心得**：无
- **too_later（4星）**
    - **关键亮点**：思路简洁明了，代码风格简洁，时间复杂度分析准确，通过记录叶子节点深度和判断深度奇偶性求解最小值，通过统计叶子节点个数更新最大值。
    - **个人心得**：第一次考场上做出的 $Div$ $2$ $D$ 题，有成就感。
- **奇米（4星）**
    - **关键亮点**：结论总结清晰，通过画图辅助理解最大值的计算方法，代码实现简单易懂，时间复杂度为 $O(n)$。
    - **个人心得**：无

### 重点代码
#### Marser 的代码
```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
typedef long long ll;
const int MN=1e5+5;
int to[MN<<1],nxt[MN<<1],h[MN],cnt;
inline void ins(int s,int t){
    to[++cnt]=t;nxt[cnt]=h[s];h[s]=cnt;
    to[++cnt]=s;nxt[cnt]=h[t];h[t]=cnt;
}
int n,Ans=1,deg[MN];
bool f[MN][2];
void dfs1(int st,int fa=0){
    if(!nxt[h[st]])f[st][0]=true;
    for(reg int i=h[st];i;i=nxt[i])
        if(to[i]!=fa){
            dfs1(to[i],st);
            if(f[to[i]][0]&&f[st][0])Ans=3;
            if(f[to[i]][1]&&f[st][1])Ans=3;
            f[st][0]|=f[to[i]][1];
            f[st][1]|=f[to[i]][0];
        }
}
void dfs2(int st,int fa=0){
    if(!nxt[h[st]]){
        if(st==1)deg[to[h[st]]]++;
        else{deg[fa]++;return;}
    }
    for(reg int i=h[st];i;i=nxt[i])
        if(to[i]!=fa)dfs2(to[i],st);
}
int main(){
    scanf("%d",&n);
    for(reg int i=1,s,t;i<n;i++)
        scanf("%d%d",&s,&t),ins(s,t);
    dfs1(1);printf("%d ",Ans);
    Ans=n-1;dfs2(1);
    for(reg int i=1;i<=n;i++)
        if(deg[i])Ans-=deg[i]-1;
    printf("%d\n",Ans);
    return 0;
}
```
**核心实现思想**：`dfs1` 函数用于判断是否存在奇数长度的叶子节点路径，若存在则将最小值设为 $3$；`dfs2` 函数用于统计每个非叶子节点的叶子儿子个数，最后更新最大值。

#### too_later 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

vector<int> tr[maxn];
int n, x, y, ans, vis[maxn], dep[maxn];
bool is[2];

int dfs(int u, int fa){
    dep[u] = dep[fa] + 1; 
    if(tr[u].size() == 1){
        vis[dep[u]] = 1; //记录叶子结点深度 
        return 1; // 这是叶子结点 
    }
    
    int sum = 0;
    for(int v, i = 0; i < tr[u].size(); i++)
        if((v = tr[u][i]) != fa){
            sum += dfs(v, u); // 记录叶子结点个数 
        }
    
    ans -= max(0, sum - 1); // 步骤3 
    return 0; // 这不是叶子结点 
}

int main(){
    scanf("%d", &n); ans = n - 1;// 初始化最大值 
    
    for(int i = 1; i < n; i++)
        scanf("%d%d", &x, &y), tr[x].push_back(y), tr[y].push_back(x);
    
    for(int i = 1; i <= n; i++)
        if(tr[i].size() != 1)
            { dfs(i, 0); break; } //找到根节点 
    
    for(int i = 1; i <= n; i++)
        if(vis[i])
            is[i & 1] = 1; //查看叶子结点深度奇偶性 
    
    if(is[0] && is[1]) printf("3 "); //深度和为奇数 
    else printf("1 "); // 深度和为偶数 
    printf("%d\n", ans);
    
    return 0;
}
```
**核心实现思想**：`dfs` 函数用于记录叶子节点深度，统计叶子节点个数并更新最大值，通过 `is` 数组判断叶子节点深度的奇偶性来确定最小值。

#### 奇米的代码
```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
    int sum=0,ff=1; char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-') ff=-1;
        ch=getchar();
    }
    while(isdigit(ch))
        sum=sum*10+(ch^48),ch=getchar();
    return sum*ff;
}

const int N=1e5+5;

int n,m,zz,in[N],vis[N];
vector<int> G[N];

inline void dfs(int u,int fa,int dep)
{
    if(G[u].size()==1&&dep%2==1) zz=1;
    for ( int i=0;i<G[u].size();i++ )
    {
        int v=G[u][i];
        if(v==fa) continue;
        dfs(v,u,dep+1);
    }
}

int main()
{
    n=read();
    for ( int i=1;i<n;i++ )
    {
        int x,y;
        x=read(),y=read();
        G[x].pb(y);
        G[y].pb(x);
        in[y]++;
    }
    int rt=0;
    for ( int i=1;i<=n;i++ ) if(G[i].size()==1) 
    {
        rt=i;
        break;
    }
    dfs(rt,0,0);
    (zz)?printf("3 "):printf("1 ");
    int mx=n-1;
    for ( int i=1;i<=n;i++ ) 
    {
        int gs=0;
        for ( int j=0;j<G[i].size();j++ )
        {
            int v=G[i][j];
            if(G[v].size()==1) gs++;
        }
        mx-=gs;
        if(gs) mx+=1;
    }
    printf("%d\n",mx);
}
```
**核心实现思想**：`dfs` 函数用于判断是否存在奇数深度的叶子节点，若存在则将最小值设为 $3$，通过统计每个节点的叶子儿子个数更新最大值。

### 关键思路或技巧
- 选择一个非叶子节点作为根节点，通过深度优先搜索遍历树，判断叶子节点深度的奇偶性，确定最小值。
- 统计每个非叶子节点的叶子儿子个数，更新最大值，利用异或的性质和题目条件进行推理。

### 拓展思路
同类型题目可能会改变树的结构或条件，例如给定有向树、带权树等，解题思路仍然是分析叶子节点的路径特征，结合异或的性质进行构造和计算。类似算法套路包括树的遍历、图的搜索、异或运算的应用等。

### 推荐题目
- [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：涉及动态规划和图的遍历，与本题的树的遍历和状态判断有相似之处。
- [P1113 杂务](https://www.luogu.com.cn/problem/P1113)：需要对图进行拓扑排序和动态规划，与本题的树的结构分析和状态转移有一定关联。
- [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)：涉及图的最短路和动态规划，与本题的树的路径分析和状态更新有相似的思维方式。

### 个人心得总结
too_later 提到第一次在考场上做出 $Div$ $2$ $D$ 题，有成就感，这表明通过不断练习和思考，能够在竞赛中取得进步。在解题过程中，要善于总结规律，利用题目条件进行推理，通过画图等方式辅助理解。

---
处理用时：96.23秒