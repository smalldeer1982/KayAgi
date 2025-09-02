# [NEERC 2015] Cactus Jubilee

## 题目描述

定义一种无向连通图叫`仙人掌图（Cactus图）`。仙人掌图中没有重边和自环，并且其中的每一条边至多位于一个简单环上。简单地说，`仙人掌图`是树的一种泛化形式，其中允许出现一些环。

现在有一个`仙人掌图`，你每次可以移动一条边（移除图的一条边，并将另一对顶点用一条边连接起来）。问如果要让后来得到的新图仍然是`仙人掌图`，有多少种移动边的办法？

## 说明/提示

$$1≤n≤50000,0≤m≤50000,2≤k_i≤1000,q_i∈[1,n]$$

## 样例 #1

### 输入

```
6 1
7 1 2 5 6 2 3 4
```

### 输出

```
42
```

## 样例 #2

### 输入

```
15 3
9 1 2 3 4 5 6 7 8 3
7 2 9 10 11 12 13 10
5 2 14 9 15 10
```

### 输出

```
216
```

# 题解

## 作者：Early (赞：2)

[原题链接](https://codeforces.com/gym/100851/problem/C)

## 题意

给定一个仙人掌图，问有多少种方法移动一条边使新图还是仙人掌图。

## 思路

分别考虑树上的边和环上的边：

- 对于树上的边，删除它后原图分为两部分，只需连接这两部分即可；
- 对于环上的边，删除它后，这个环连同原来连在环上的所有树组成了一棵新树，再从所有不在环上的点中任意连边即可。

## 实现

在一棵有 $x$ 个点的树上增加一条边的方案数为 $\frac{x\cdot(x-1)}2-(x-1)$。

## 代码

```cpp
#include<cstdio>
#include<cctype>
#include<vector>
using namespace std;
const int N=50000;
typedef pair<int,int> pii;
int n,m;
vector<int>e[N+1];
int cnt;
vector<pii>sc[N+1];
long long sum;
long long res;
int read()
{
    int ret=0;
    char c=getchar();
    while(!isdigit(c)) {
        c=getchar();
    }
    while(isdigit(c)) {
        ret=ret*10+c-'0';
        c=getchar();
    }
    return ret;
}
void tarjan(int u,int fa)
{
    static int tot,dfn[N+1],low[N+1],siz[N+1];
    static int top;
    static pii stk[N+1];
    dfn[u]=low[u]=++tot,siz[u]=1;
    for(int v:e[u]) {
        pii edg=pii{u,v};
        if(!dfn[v]) {
            stk[++top]=edg;
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            siz[u]+=siz[v];
            if(low[v]>dfn[u]) {
                res+=1ll*siz[v]*(n-siz[v])-1;
            }
            if(low[v]>=dfn[u]) {
                ++cnt;
                do {
                    sc[cnt].push_back(stk[top]);
                } while(stk[top--]!=edg);
            }
        } else {
            if((v!=fa)&&(dfn[v]<dfn[u])) {
                stk[++top]=edg;
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
    return;
}
namespace unionSet {
    int fa[N+1],siz[N+1];
    inline void init()
    {
        fill(siz+1,siz+n+1,1);
        return;
    }
    int find(int x)
    {
        return fa[x]?fa[x]=find(fa[x]):x;
    }
    void merge(int u,int v)
    {
        u=find(u),v=find(v);
        if(u!=v) {
            fa[v]=u,siz[u]+=siz[v];
        }
        return;
    }
}
inline long long calc(int x)
{
    return 1ll*x*(x-1)/2-(x-1);
}
int main()
{
    n=read(),m=read();
    while(m--) {
        int c=read(),u=read();
        while(--c) {
            int v=read();
            e[u].push_back(v),e[v].push_back(u);
            u=v;
        }
    }
    tarjan(1,0);
    unionSet::init();
    for(int i=1;i<=cnt;++i) {
        if(sc[i].size()==1) {
            unionSet::merge(sc[i].front().first,sc[i].front().second);
        }
    }
    for(int i=1;i<=n;++i) {
        if(!unionSet::fa[i]) {
            sum+=calc(unionSet::siz[i]);
        }
    }
    for(int i=1;i<=cnt;++i) {
        if(sc[i].size()==1) {
            continue;
        }
        int s=0;
        long long tem=sum;
        for(pii edg:sc[i]) {
            int u=unionSet::find(edg.first);
            s+=unionSet::siz[u];
            tem-=calc(unionSet::siz[u]);
        }
        res+=(tem+calc(s)-1)*sc[i].size();
    }
    printf("%lld\n",res);
    return 0;
}
```

---

