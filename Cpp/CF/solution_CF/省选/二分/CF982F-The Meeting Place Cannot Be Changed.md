# The Meeting Place Cannot Be Changed

## 题目描述

Petr is a detective in Braginsk. Somebody stole a huge amount of money from a bank and Petr is to catch him. Somebody told Petr that some luxurious car moves along the roads without stopping.

Petr knows that it is the robbers who drive the car. The roads in Braginsk are one-directional and each of them connects two intersections. Petr wants to select one intersection such that if the robbers continue to drive the roads indefinitely, they will sooner or later come to that intersection. The initial position of the robbers is unknown. Find such an intersection that fits the requirements.

## 说明/提示

In the first example the robbers can move, for example, along the following routes: $ (1-2-3-1) $ , $ (3-4-5-3) $ , $ (1-2-3-4-5-3-1) $ . We can show that if Petr chooses the $ 3 $ -rd intersection, he will eventually meet the robbers independently of their route.

## 样例 #1

### 输入

```
5 6
1 2
2 3
3 1
3 4
4 5
5 3
```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
1```

# 题解

## 作者：lfxxx (赞：4)

非常好的一道题。

首先不妨假设答案存在以化简情况。

先随便找出一个环，由于答案存在，所以其他环必定形如现在这个环上走一段再走一段非环边再走一段环边如此交替。

考虑找出所有非环边段，注意到这些非环边段无论处在哪个环中，其作用都是会使得其代替的环边集合上的点不可能成为答案，而无关环的具体形态，也就是说，只需要找到所有形如从环上一点出发走若干条非环边再回到环上一点的 非环边段即可，即对于一个环上点，我们要找出从其出发走非环边能抵达最远的环上点。

从每个环上点开始 dfs 一遍，存下每个点能抵达的最远环上点显然是正确的，不过这样做是 $O(n^2)$ 的，如何优化？

考虑下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4i4zs0sr.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

假若不存在红色边，我们可以发现如果从一个点开始 dfs 时遇到其他点 dfs 时经过的点，可以直接利用从其他点开始 dfs 求出的环上最远点，假若存在红色边，则一定无解，与最开始的假设矛盾。

因此每次 dfs 时如果一个点在之前的 dfs 时搜过了就不再搜，所以复杂度是 $O(n)$ 的，求出最远点后环覆盖可以断环为链差分做，注意最后还要把求出来的答案 check 一下是否合法，也就是其删去后图上是否还有环，因为最开始假设的是答案存在。

总的时间复杂度就是 $O(n)$ 的。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
vector<int> E[maxn];
int huan[maxn],tt;
int rk[maxn];
int stk[maxn],tp;
int n,m;
int vis[maxn],dfn[maxn];
void find(int u){
    vis[u]=1;
    dfn[u]=1;
    stk[++tp]=u;
    for(int v:E[u]){
        if(dfn[v]==0){
            find(v);
            if(tt!=0) return ;
        }else if(vis[v]!=0&&tt==0){
            while(stk[tp]!=v){
                huan[++tt]=stk[tp];
                rk[huan[tt]]=tt;
                tp--;
            }
            huan[++tt]=v;
            rk[huan[tt]]=tt;
            return ;
        }
    }
    vis[u]=0;
    tp--;
}
int far[maxn];
int dis(int idx,int idy){
    //idx->idy
    if(idx==0||idy==0) return -1e9;
    if(idx==idy) return tt;
    else if(idx>idy) return idx-idy;
    else return tt-(idy-idx);
}
int tag[maxn];
void dfs(int u,int id){
    tag[u]=1;
    for(int v:E[u]){
        if(rk[v]!=0){
            if(dis(id,rk[v])>dis(id,rk[far[u]])) far[u]=v;
        }else{
            if(tag[v]==0) dfs(v,id);
            if(dis(id,rk[far[v]])>dis(id,rk[far[u]])) far[u]=far[v];     
        }
    }
}
int use[maxn<<1];
void jump(int u,int v){
    if(rk[u]>rk[v]){
        use[rk[v]+1]++;
        use[rk[u]]--;
    }else{
        use[rk[v]+1]++;
        use[rk[u]+tt]--;
    }
}
int ans;
void check(int u){
    if(u==ans) return ;
    vis[u]=1;
    dfn[u]=1;
    stk[++tp]=u;
    for(int v:E[u]){
        if(v==ans) continue;
        if(dfn[v]==0){
            check(v);
            if(ans==-1) return ;
        }else if(vis[v]!=0){
            ans=-1;
            return ;
        }
    }
    vis[u]=0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(dfn[i]==0&&tt==0){
            find(i);
        }
    }
    for(int i=1;i<=tt;i++){
        dfs(huan[i],i);
        if(far[huan[i]]!=0) jump(huan[i],far[huan[i]]);
    }
    for(int i=1;i<=2*tt;i++) use[i]+=use[i-1];
    for(int i=1;i<=tt;i++){
        if(use[i]==0&&use[i+tt]==0){
            ans=huan[i];
            break;
        }
    }
    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    memset(stk,0,sizeof(stk));
    tp=0;
    for(int i=1;i<=n;i++){
        if(dfn[i]==0&&ans!=-1) check(i);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：GGapa (赞：1)

### CF982F The Meeting Place Cannot Be Changed

https://www.luogu.com.cn/problem/CF982F

trick：对于环求交问题，可以先找到一个主环，然后对于环上的每一个节点找到不经过环上的边能够走到最远的节点，将这两个节点之间的点标记为不合法，只需要遍历每个节点一次。

由于某人会任意选择起点然后走无穷多步，说明图上的每一个节点都能够走到一个环上，要求必经之路相当于就是求这个有向图所有环的交。

求有关于环的问题，第一时间可能会想到 DFS 生成树，但有向图的 DFS 生成树并没有什么很好的性质，我们不得不抛弃这一想法。

有一步非常套路的想法是现在图上随便找一个环（题目保证一定有环），接着进行某些处理得到答案，笔者正是卡在了这一步。思考如何找到交是非常不容易的，正难则反，考虑能否找到不是交的边。

对于主环上每一个节点，我们可以找到其不经过环上的边能够走到的最远的节点，然后将这两个节点之间的节点标记为不合法，正确性是显然的，直接暴力做的时间复杂度是 $O(n^2)$。实际上每个节点第一次被访问到才是有意义的。如果一个节点第二次被访问，那么第二次访问到达的最远的节点一定是第一次访问到达的，所以我们证明了一个节点至多只会被访问一次。

但请读者认真思考一下便会发现上述证明其实是有误的，因为对于两个不同的节点 $A$ 和 $B$ 他们对“远”的定义不同，对于一个在 $A$ 和 $B$ 之间的节点 $C$，在 $A$ 作为起点时 $dis(A, C)$ 是要小于 $dis(B, C)$ 的，但在第一次访问的时候 $C$ 并不是访问到最远的节点，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ka2j26fh.png)

为了解决这个问题，我们不妨钦定原图一定有交，若原图一定有交那么上述策略可以得证，如果最终找到的交删去之后依然有环存在，则说明问题无解，需要在结尾加一个 check。

[Code](https://codeforces.com/contest/982/submission/295705037)

---

