# [COTS 2020] 抗疫 Autoritet

## 题目背景

译自 [Izborne Pripreme 2020 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2020/) D2T1。$\texttt{2s,0.5G}$。


## 题目描述

有 $N$ 个国家，$M$ 条双向航线连接不同的国家。需要注意的是，两个国家之间可能有多条航线连接。

疫情当下，欲举全球之力共同抗疫，需要将世界联结。定义世界是**联结的**，当且仅当任意两个国家都通过航线直接或间接相连。



我们记 $V=\{1,2,\cdots,N\}$。在一次操作中：

- 任意选择 $u\in V$；
- 令集合 $S$ 为国家 $u$ 通过**恰好一条**航线能够到达的国家的集合；令集合 $T=V\backslash \{u\}\backslash S$。
- $\forall v\in S$，将连接 $u,v$ 的航线删除；$\forall w\in T$，添加连接 $u,w$ 的航线。

可以证明，添加足够多的航线后，一定能够使世界联结。

欲通过最少的操作次数使世界联结。

求出：
- 最少的操作次数 $k$；
- 在最小化操作次数的前提下，不同的操作序列数量。只需要求出对 $(10^9+7)$ 取模后的结果。

定义两个操作序列是不同的，当且仅当存在 $i\in [1,k]$，使得在这两个操作序列中第 $i$ 次选择的国家 $u$ 不同。

## 说明/提示


#### 样例解释

- 样例 $1$ 解释：存在不需要执行任何操作的情况。
- 样例 $2$ 解释：所有的操作序列有 $[1,4],[4,1],[2,3],[3,2]$。

#### 评分方式

如果回答对了第一问，可以获得 $15\%$ 的分数。

如果不打算回答第二问，也要任意输出一个 $\in [0,10^9+7)$ 的整数，否则不保证得分符合预期。


#### 数据范围


对于 $100\%$ 的数据，保证：

- $1\le N,M\le 5\times 10^5$；
- $a_i\neq b_i$。


| 子任务编号 | $N,M\le $  | 得分 |  
| :--: | :--: | :--: |  
| $ 1 $    | $18$ |  $ 5 $   |  
| $ 2 $    | $300$ |$ 9 $   |  
| $ 3 $    | $3\, 000$ |  $ 16 $   |  
| $ 4 $    | $5\times 10^5$ | $ 70 $   |  


## 样例 #1

### 输入

```
6 6
3 4
1 2
2 3
5 4
4 1
4 6```

### 输出

```
0
1```

## 样例 #2

### 输入

```
4 2
1 4
2 3```

### 输出

```
2
4```

## 样例 #3

### 输入

```
8 9
1 4
2 3
6 7
8 5
2 4
7 8
5 6
6 8
4 3```

### 输出

```
1
5```

# 题解

## 作者：H3PO4 (赞：1)

大分讨！

## 1. 图连通，最少的操作次数为 $0$

首先如果整个图连通，那么就不需要执行任何操作，直接输出 $0$ 和 $1$ 即可，时间复杂度 $O(n)$。

## 2. 图不连通，所有连通块都多于一个点

若图不连通，那么对某个点进行一次操作之后，它会与原来的其他所有连通块连通。此时若**它仍与本来所在的连通块连通（或者它原来所在的连通块只有它一个点）**，那么整个图就连通了。先不考虑只有一个点的连通块。

### 2.1 所有连通块都是完全图
发现所有点都不满足操作后仍与本来所在的连通块连通当且仅当原来的所有连通块都是完全图。

#### 2.1.1 只有两个连通块，最少的操作次数为较小的连通块的点数
此时对一个点操作相当于把它从一个连通块移动到了另一个连通块，且**操作后的连通块仍然是完全图**。所以最优策略就是把较小的连通块的点全部移动到较大的连通块，移动的顺序任意。

#### 2.1.2 有超过两个连通块，最少的操作次数为 $2$
设整个图的点集为 $V$，这些连通块的点集分别为 $V_1,V_2,V_3,\dots,V_n$。先对 $V_1$ 上的点 $v_1$ 操作，之后图就会变成两个连通块，点 $v_1$ 原来的连通块 $V_1$ 变成少一个点的完全图 $V_1^\prime$，另一个连通块则形如 $V_2,V_3,\dots,V_n$ 的每个点分别与点 $v_1$ 相连。此时，再对 $V_2$ 上的点 $v_2$ 操作，会断开它与点 $v_1$ 和 $V_2$ 中其他点的边，而与 $V_1^\prime,V_3,\dots,V_n$ 相连，于是**整个图连通只需要 $2$ 次操作**。注意到**若某个连通块只有两个点，那么也可以只操作这两个点，也只需要 $2$ 次操作**。所以最少的操作次数为 $2$，不同的操作序列数量为 $2\times N_2 + \sum_{i=1}^n |V_i|\times(|V|-|V_i|)$，其中 $N_2$ 为只有两个点的连通块的个数。

这一过程的时间复杂度为 $O(n)$。

### 2.2 某个连通块不是完全图，最少的操作次数为 $1$
设 $u$ 是这样的连通块上的一个点。操作后所有其他连通块都会与 $u$ 相连，所以只需考虑 $u$ 本来所在的连通块。若 $u$ 向此连通块中其他所有点都有连边，那么对它操作之后图还是不连通。否则，对 $u$ 操作之后 $u$ 一定会与此连通块中某个点连边。

#### 2.2.1 $u$ 不是割点
操作后此连通块仍然连通，于是**一次操作就让整个图连通了**。

#### 2.2.2 $u$ 是割点
包含 $u$ 的点双连通分量中，**包含其他割点的点双连通分量在操作后仍然连通**，而只包含一个割点 $u$ 的点双连通分量，只有当它存在不与 $u$ 直接连边的点，即这个点双连通分量与 $u$ 之间的边数小于它的点数时，才能在操作后依然与 $u$ 连通。也就是说，**所有只包含一个割点 $u$ 的点双连通分量都满足与 $u$ 之间的边数小于它的点数时，对 $u$ 操作才能立刻使整个图连通**。

显然，上述论证表明**合法的点（一次操作后整个图连通）一定存在**。这一判断过程的时间复杂度为 Tarjan 算法的复杂度加上割点的度数和，即 $O(n+m)$。

## 3. 某个连通块只有一个点
设 $N_1$ 为只有一个点的连通块的个数。这时只需对这一个点操作即可使整个图连通。若所有连通块都是完全图，那么不同的操作序列数量就是 $N_1$。若某个连通块不是完全图，那么不同的操作序列数量就是按照上述方法判断的合法的点的数量再加上 $N_1$。

---

因为有重边，所以需要去重。我用的是 `std::sort` 然后 `std::unique`，时间复杂度 $O(m \log n)$，当然用哈希表可以做到 $O(m)$。

总时间复杂度 $O(n + m \log n)$

代码大量滥用了 lambda，写的很丑，仅供参考。

```cpp
#include<bits/stdc++.h>
using I=int;
template<class T>using V=std::vector<T>;
template<class T,I N>using A=std::array<T,N>;
#define bg(x) (x).begin()
#define ed(x) (x).end()
#define all(x) bg(x),ed(x)
const I MOD=1e9+7;
int main(){
  std::cin.tie(0)->sync_with_stdio(0);
  
  I n,m;std::cin>>n>>m;
  V<V<I>>g(n);
  for(I i=0;i<m;i++){
    I u,v;std::cin>>u>>v;u--;v--;
    g[u].push_back(v);g[v].push_back(u);
  }
  for(auto&e:g){
    std::sort(all(e));
    e.erase(std::unique(all(e)),ed(e));
  }

  V<I>fac(n+1);
  fac[0]=1;for(I i=1;i<=n;i++)fac[i]=1ll*i*fac[i-1]%MOD;

  V<I>vis(n,-1);V<V<I>>pts;
  auto dfs=[&](auto&&dfs,I u,I c)->void{
    vis[u]=c;pts[c].push_back(u);
    for(I v:g[u])if(vis[v]==-1)dfs(dfs,v,c);
  };

  I col=0;
  for(I i=0;i<n;i++)if(vis[i]==-1)pts.push_back({}),dfs(dfs,i,col++);
  if(col==1){std::cout<<"0\n1\n";return 0;}
  
  I minz=1e9,nmz=0,w=0,w2=0,allcc=1;
  for(I i=0;i<col;i++){
    if([&]{for(I u:pts[i])if(g[u].size()!=pts[i].size()-1)return 0;return 1;}()){
      if(pts[i].size()==1)w2++;
      if(I z=pts[i].size();z<minz)minz=z,nmz=1;
      else if(z==minz)nmz++;
    }else{
      allcc=0;
      I root=pts[i][0];
      V<I>dfn(n,-1),low(n,-1),cut(n),bl(n,-1),sta;
      V<V<I>>dcc;
      I bc=0;
      auto tarjan=[&](auto&&tarjan,I u)->void{
        dfn[u]=low[u]=bc++;sta.push_back(u);
        int f=0;
        for(I v:g[u]){
          if(dfn[v]!=-1)low[u]=std::min(low[u],dfn[v]);
          else{
            tarjan(tarjan,v);
            low[u]=std::min(low[u],low[v]);
            if(low[v]>=dfn[u]){
              if(++f>1||u!=root)cut[u]=1;
              dcc.push_back({});
              while(1){
                I t=sta.back();sta.pop_back();
                dcc.back().push_back(t);
                bl[t]=dcc.size()-1;
                if(t==v)break;
              }
              dcc.back().push_back(u);
              bl[u]=dcc.size()-1;
            }
          }
        }
      };
      tarjan(tarjan,root);
      V<V<I>>nr(n);
      for(I z=0;auto&cc:dcc){
        I t=0,w;
        for(I u:cc)if(cut[u])t++,w=u;
        if(t==1)nr[w].push_back(z);
        z++;
      }
      for(I u:pts[i])if(g[u].size()!=pts[i].size()-1){
        I ow=w;
        if(cut[u]){
          if(nr[u].empty())w++;
          else
            w+=[&](){
              for(I i:nr[u]){
                I t=0;
                for(I v:g[u])if(bl[v]==i)t++;
                if(t==dcc[i].size()-1)return 0;
              }
              return 1;
            }();
        }else w++;
      }
    }
  }
  if(allcc){
    if(col==2||minz==1)std::cout<<minz<<'\n'<<1ll*nmz*fac[minz]%MOD<<'\n';
    else{
      I w=0;
      for(I i=0;i<col;i++)w=(w+1ll*pts[i].size()*(n-pts[i].size())%MOD)%MOD;
      if(minz==2)w+=2*nmz;
      std::cout<<"2\n"<<w%MOD<<'\n';
    }
    return 0;
  }

  std::cout<<"1\n"<<w+w2<<"\n";
}

```

---

