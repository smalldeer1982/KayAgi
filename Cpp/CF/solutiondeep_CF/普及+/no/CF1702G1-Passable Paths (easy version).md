# 题目信息

# Passable Paths (easy version)

## 题目描述

给定一棵树，问是否能通过一条简单路径（即在树上找一条路径且不重复走一条边），使其经过给定点集中的所有点。

## 说明/提示

对于 $100\%$ 的数据：

+ $1 \le n \le 2 \cdot 10^5$，$ 1 \le u, v \le n$，$ u \ne v$；

+ $ 1 \le q \le 5$，$ 1 \le k \le n$，$ 1 \le p_i \le n$，所有 $k$ 的和不超过 $2\cdot10^5$。

## 样例 #1

### 输入

```
5
1 2
2 3
2 4
4 5
5
3
3 2 5
5
1 2 3 4 5
2
1 4
3
1 3 5
3
1 5 4```

### 输出

```
YES
NO
YES
NO
YES```

## 样例 #2

### 输入

```
5
1 2
3 2
2 4
5 2
4
2
3 1
3
3 4 5
3
2 3 5
1
1```

### 输出

```
YES
NO
YES
YES```

# AI分析结果

### 题目分类
图论

### 综合分析与结论
这些题解主要围绕判断树上是否存在一条简单路径经过给定节点集合中的所有点展开。不同题解的思路各有特色，但核心都是先确定路径的端点，再判断路径是否覆盖所有给定节点。
- **王熙文**：先确定最深点 `ax1` 和非 `ax1` 祖先中最深的点 `ax2` 作为可能的端点，再判断 `ax1` 到 `ax2` 的路径是否覆盖所有点。
- **qwq___qaq**：从深度最大的点开始进行 `dfs` 搜索，若能得到一条链则为 `YES`。
- **TernaryTree**：利用虚树，判断虚树中节点度数是否都不超过 2。
- **qnqfff**：找到深度最深的点和与其距离最远的点作为端点，判断其他点是否在两点的简单路径上。
- **ZLCT**：从深度最大的点出发进行 `dfs`，若能覆盖所有点则为 `YES`。
- **yingkeqian9217**：先找到深度最大的点 `x` 和非 `x` 祖先中深度最大的点 `y` 作为端点，再判断其他点是否在链上。

### 所选的题解
- **王熙文（4星）**：
  - 关键亮点：思路清晰，通过深度和祖先关系确定端点，再暴力判断路径是否覆盖所有点，代码实现简洁易懂。
- **qnqfff（4星）**：
  - 关键亮点：思路明确，先找到两个端点，再通过 `lca` 判断其他点是否在路径上，代码逻辑清晰。
- **yingkeqian9217（4星）**：
  - 关键亮点：利用树剖求 `lca`，时间复杂度为 $O(n\log n)$，思路独特，对问题的分析较为深入。

### 重点代码
#### 王熙文
```cpp
// 判断 u 是否是 v 的祖先
bool is_fa(int u,int v) 
{
    int cj=dep[v]-dep[u];
    for(int i=0; i<=19; ++i)
    {
        if(cj>>i&1) v=fa[v][i];
    }
    return u==v;
}

// 主逻辑
while(q--)
{
    cin>>k;
    for(int i=1; i<=k; ++i)
    {
        cin>>qs[i];
    }
    sort(qs+1,qs+k+1,cmp);
    int ax1=qs[1],ax2=0;
    for(int i=2; i<k; ++i)
    {
        if(!is_fa(qs[i],ax1))
        {
            ax2=qs[i];
            break;
        }
    }
    if(!ax2)
    {
        puts("Yes");
        continue;
    }
    memset(vis,0,sizeof(vis));
    int nowx=ax1,nowy=ax2;
    while(nowx!=nowy)
    {
        if(dep[nowx]<dep[nowy]) swap(nowx,nowy);
        vis[nowx]=1,nowx=fa[nowx][0];
    }
    vis[nowx]=1;
    bool flag=1;
    for(int i=1; i<=k; ++i)
    {
        if(!vis[qs[i]])
        {
            flag=0;
            break;
        }
    }
    puts(flag?"Yes":"No");
}
```
核心实现思想：先通过 `is_fa` 函数判断节点的祖先关系，然后确定端点 `ax1` 和 `ax2`，再标记 `ax1` 到 `ax2` 路径上的节点，最后判断给定节点是否都在该路径上。

#### qnqfff
```cpp
// 倍增求 lca
int lca(int x,int y)
{
    if(dep[x]<dep[y])
        swap(x,y);
    for(int i=20;i>=0;i--)
        if(dep[f[x][i]]>=dep[y])
            x=f[x][i];
    if(x==y)
        return x;
    for(int i=20;i>=0;i--)
        if(f[x][i]!=f[y][i])
            x=f[x][i],y=f[y][i];
    return f[x][0]; 
}

// 主逻辑
while(q--)
{
    memset(a,0,sizeof(a));
    int m=read();
    for(int i=1;i<=m;i++)
        a[i]=read();
    int x=0,maxnx=-1e9,y=0,maxny=-1e9;
    for(int i=1;i<=m;i++)
        if(dep[a[i]]>maxnx) maxnx=dep[a[i]],x=a[i];//取深度最深的点
    for(int i=1;i<=m;i++)
        if(dep[x]+dep[a[i]]-2*dep[lca(x,a[i])]+1>maxny&&a[i]!=x) maxny=dep[x]+dep[a[i]]-2*dep[lca(x,a[i])]+1,y=a[i];//取离深度最深的点最远的点
    bool flag=0;
    for(int i=1;i<=m;i++)
    {
        if(a[i]==x||a[i]==y||lca(x,y)==a[i]||(lca(lca(x,y),a[i])==lca(x,y)&&lca(a[i],x)==a[i])||(lca(lca(x,y),a[i])==lca(x,y)&&lca(a[i],y)==a[i]))//在两点路径上
            continue;
        flag=1;//不在
        break;
    }
    cout<<(flag?"NO":"YES")<<endl;
}
```
核心实现思想：先通过倍增法求 `lca`，然后找到深度最深的点和与其距离最远的点作为端点，最后通过 `lca` 判断其他点是否在两点的简单路径上。

#### yingkeqian9217
```cpp
// 树剖求 lca
int lca(int x,int y)
{
    if(!x||!y) return -1;//不知道有没有用的特判
    while(top[x]!=top[y])
    {
        if(dep[top[x]]>dep[top[y]]) x=f[top[x]];
        else y=f[top[y]];
    }
    return (dep[x]>dep[y]?y:x);
}

// 主逻辑
void solve()
{
    int x=1,y=0;
    scanf("%d",&m);
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    if(m==2) return void(puts("YES"));//特判两点，必然成立
    sort(a+1,a+m+1,cmp);//排序
    for(int i=2;i<=m;i++)
        if(lca(a[x],a[i])!=a[i])
        {
            y=i;//记录另一个端点
            break;
        }
    if(!y) return void(puts("YES"));//特判
    if(dep[a[m]]<dep[lca(a[x],a[y])]) return void(puts("NO"));//特判最高点
    for(int i=1;i<=m;i++)
        if(lca(a[i],a[x])!=a[i]&&lca(a[i],a[y])!=a[i])//是否为祖先
            return void(puts("NO"));
    puts("YES");
}
```
核心实现思想：利用树剖求 `lca`，先确定深度最大的点 `x` 和非 `x` 祖先中深度最大的点 `y` 作为端点，再通过 `lca` 判断其他点是否在链上。

### 关键思路或技巧
- 利用深度信息确定路径的端点，通常深度最大的点是路径的一个端点。
- 通过判断节点的祖先关系（如使用 `lca`）来确定节点是否在路径上。
- 可以使用倍增、树剖等方法求 `lca`。

### 拓展思路
同类型题或类似算法套路：
- 树上路径问题，如判断树上两点间路径是否经过某些特定节点。
- 虚树的应用，在处理树上多个节点的问题时，虚树可以有效降低复杂度。

### 推荐题目
- [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
- [P2912 [USACO08OCT]Building Roads S](https://www.luogu.com.cn/problem/P2912)
- [P1364 医院设置](https://www.luogu.com.cn/problem/P1364)

### 个人心得
- **yingkeqian9217**：“如何评价我做 G1 结果做出来的解法 G2 也能过。。。” 总结：该作者在解决本题时，意外发现自己的解法可以同时适用于更难的版本，说明在解题过程中可能发现了问题的本质，找到了通用的解法。 

---
处理用时：57.69秒