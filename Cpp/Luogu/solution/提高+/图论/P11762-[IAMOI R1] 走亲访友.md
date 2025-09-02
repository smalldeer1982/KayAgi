# [IAMOI R1] 走亲访友

## 题目背景

小 C 拉小 L 去走亲戚。

## 题目描述

小 C 共有 $n$ 个亲戚，某些亲戚家之间有 $m$ 条双向的道路，保证亲戚家之间两两可达。

小 C 要亲自去走亲戚。具体的，小 C 一开始在第 $s$ 个亲戚家。每次她可以前往一个与她现在的位置有道路相连的亲戚家。然而小 C 太有魅力了。每当她走过一条道路时，追求她的人便会从四面八方涌来，导致这条路堵车。当然，她也可以躲在车里面，收起她的迷人魅力，这样这条路就不会堵车了。

因为小 L 是路痴，所以小 C 希望最后剩下尽量少的 $n-1$ 条没有堵车的道路，并使得只保留着 $n-1$ 条道路后，亲戚家之间仍两两可达。

因为小 C 不想四处奔波这么久，所以最多只会走过 $k$ 条道路。

请你为她输出一种走亲戚的方案。

### 形式化题意

给定一个 $n$ 个点 $m$ 条边的简单无向连通图，你需要构造一组满足下面要求的路径：

+ 起点为 $s$，终点不限。

+ 对于走过的每一组边 $(u_i,v_i)$，你需要额外决定 $p_i\in\{0,1\}$，满足：

1. $p_i=0$ 表示删除这条边，**且不能再使用，即之后不能再次经过这条边**；$p_i=1$ 表示不删除这条边。

2. 如果 $i>1$，那么 $u_i=v_{i-1}$。**即使 $p_i=0$，也需要满足这条限制。**

+ 路径的长度不能超过 $k$。

+ 最后未删除的边组成一棵 $n$ 个节点的树。

特别的，一组边在被删除前可以经过多次。

若有多组满足条件的路径，可以输出任意一组。

可以证明在本题的限制条件下，一定存在合法的方案。

## 说明/提示

### 样例解释
![](https://cdn.luogu.com.cn/upload/image_hosting/qr0blgk5.png)

首先我们从第 $4$ 条道路后到达 $5$ 号亲戚家，再通过第 $2$ 条道路到达 $2$ 号亲戚，并让第 $2$ 条道路堵车。此时，只剩下 $n-1$ 条没有堵车的道路，并且亲戚家之间仍然两两可达。

对于以下输出：

```
2
4 1
5 0
```

或者以下输出：

```
3
4 1
2 1
3 0
```

也将视作正确。
### 数据范围

**本题采用捆绑测试**。

| Subtask | $n\le$ | $m$ | $k=$ | 分数 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $10$ | $\le 10$ | $100$ | $20$ |
| 2 | $100$ | $\le \frac{n(n-1)}{2}$ | $10^6$ | $10$ |
| 3 | $10^3$ | $=n$ | $n+m$ | $10$ |
| 4 | $10^3$ | $\le \frac{n(n-1)}{2}$ | $n^2$ | $20$ |
| 5 | $10^3$ | $\le \frac{n(n-1)}{2}$ | $n+m$ | $40$ |


对于 $100\%$ 的数据，$n-1\le m\le\dfrac{n(n-1)}{2}$，$1\le u,v \le n$，且图中无自环、重边。

后话：这并非此题的原版，而是改版。然而[原版](https://www.luogu.com.cn/problem/T565042)我们目前并没有想到做法，有思路可以联系 [Down_syndrome](https://www.luogu.com.cn/user/984018)。

## 样例 #1

### 输入

```
5 5 10 4
1 3
2 5
2 3
4 5
1 5```

### 输出

```
2
4 1
2 0```

# 题解

## 作者：Esucu (赞：5)

## Subtask1

考虑随便搜出一棵生成树，然后删掉剩余 $m-n+1$ 条边，从起点开始，每次从当前点暴力跑 dfs 走到下一条要删的边的端点（这样可以保证走的点之前没有被删过），然后删掉这条边就行。

总共经过 $m-n+1$ 轮，每轮最多走 $m$ 条边，因此边数最多为 $m(m-n+1)$，复杂度是 $O(m^2)$。

## Subtask2

把暴力跑 dfs 换成暴力跑树边就能把复杂度降至 $O(nm)$。

## Subtask3

依然沿用 Subtask1 的做法，边数是 $n$ 条，复杂度是 $O(n+m)$。

## Subtask4

考虑贴近正解。

如果没有“删除一条边后就不能再走”的限制这题是简单的，直接把每条边都遍历一遍就行了。

添加这个要求后，我们就要考虑如何不重复地经过每条边。

考虑到“不重复”，可以想到欧拉回路（欧拉路径也是一样）。对于原图是欧拉图的情况，总步数可以不超过 $m$。因为我们可以跑一遍欧拉回路，每遍历到一条边，若它是树边则不删去，否则删去。欧拉回路是为了保证每条边可以不重不漏地走一次。

否则的话原图存在奇度点，考虑把这些奇度点“去掉”。事实上，我们跑出来的路径不一定要是严格的欧拉回路。因为一条边实际上可以经过多次，我们只需要再最后删除就行了。我们可以给每条路径新增一个“通过次数”。我们可以给奇度点两两分组，给每组组内两个点间的任意简单路径上的每条边的“通过次数”都加一，可以看做将该路径复制一遍（以下简称加边），使得原图转化为欧拉图。

这样最多有 $\frac{n}{2}$ 组，每组最多加 $n-1$ 条边，总边数控制在 $m+\frac{n(n-1)}{2}$ 内。

然而如果暴力跑 dfs 时间复杂度是 $O(nm)$ 的，依然可以通过把暴力跑 dfs 换成暴力跑树边，复杂度做到 $O(n^2+m)$。

## Subtask5

你已经非常接近正解了！

考虑优化一下分组，使得新加入的边尽量少。

可以这样加边：搜一遍生成树，在****回溯****时若该点为奇度点，则****将该点与其父亲节点加边****。

可以证明这样加完边后原图一定是欧拉图。

简单证明：用这样的操作，因为回溯时才加边保证了非根节点一定可以变成偶度点，而每一次加边，节点度数和的奇偶性不变，一开始是偶数个，加完边后也是偶数个，又因为没有其他偶度点了，所以根节点也是偶度点。

这样，就在每条树边最多复制一次的情况下让每个点的度数均变成了偶数。

理一遍思路：直接跑生成树，给树边打标记，奇度点加边，跑欧拉回路输出路径。

总边数 $m+n-1$ 条，复杂度 $O(n+m)$。

std：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
const int M=5e5+5;
int n,m,s,u,v,cnt=1,cntans,to[N+M<<1],id[N+M<<1],nxt[N+M<<1],h[N],d[N],ans[N+M];
bool tag[M],vis[N+M<<1];
void save(int u,int v,int w){
	to[++cnt]=v;
	id[cnt]=w;
	nxt[cnt]=h[u];
	h[u]=cnt;
	d[u]++;
}
void dfs(int u){
	vis[u]=1;
	for(int i=h[u];i;i=nxt[i]){
		if(vis[to[i]]||i>(m<<1|1)) continue;
		tag[id[i]]=1;
		dfs(to[i]);
		if(d[to[i]]&1){
			save(u,to[i],id[i]);
			save(to[i],u,id[i]);
		}
	}
}
void dfs2(int u){
	for(int &i=h[u];i;i=nxt[i]){
		if(vis[i]) continue;
		vis[i]=vis[i^1]=1;
		int k=id[i];
		dfs2(to[i]);
		ans[++cntans]=k;
	}
}
int main(){
	scanf("%d%d%*d%d",&n,&m,&s);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		save(u,v,i);
		save(v,u,i);
	}
	dfs(s);
	memset(vis,0,sizeof(vis));
	dfs2(s);
	printf("%d\n",cntans);
	for(int i=cntans;i>=1;i--) printf("%d %d\n",ans[i],(int)tag[ans[i]]);
	return 0;
}
```

---

## 作者：Jorisy (赞：3)

晚上跟同学打完球回机房的时候 zhk 已经在开 t4 了，他说 t3 比较有意思，让我们想想。

好题要点赞。

首先可以容易得到一个上限为 $2m$ 的做法：直接暴力 dfs，搜到一个非树边就返回并清除该边。

这个看起来没什么前途，因为我们的瓶颈在于每条边都要来回走，中间浪费了很多。

但是给了我们启示，发现它是一个欧拉回路。

于是就考虑能否将我们走的路径构成欧拉回路。

但是显然，图中的奇度点较多，如何处理？

考虑一个经典 trick，即 [Some Simple Tricks](https://www.luogu.com.cn/article/cqhi72t6) 中的 $\bm{Trick\ 5}$ ，将在图上的决策转化为生成树上。这样我们可以从叶子开始从下往上给树边加重边。由于一条边会对两个节点的度数贡献，所以最后到根节点的时候根的度数一定是偶数。

然后我们跑欧拉回路即可。

由于每条树边最多被加一次重边，所以最坏路径长度为 $2(n-1)+m-(n-1)=m+n-1$，恰好在限制范围内。

```cpp
#include<bits/stdc++.h>
#define N 1003
#define M 2000005
#define ll long long
#define mod 
using namespace std;

struct node{
    int to,nxt,id;
}e[M];
int n,m,k,st,hd[N],deg[N],col[M],vis[M],tot=1;

void add(int u,int v,int id)
{
    e[++tot]={v,hd[u],id};
    hd[u]=tot;
}

void dfs(int x,int lst=0,int id=0)
{
    vis[x]=1;
    for(int i=hd[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(vis[y]||i>m*2+1) continue;
        col[e[i].id]=1;
        dfs(y,x,e[i].id);
    }
    if(deg[x]&1^1) return;
    add(x,lst,id);
    add(lst,x,id);
    deg[x]++;
    deg[lst]++;
}

vector<pair<int,int>>ans;

void hier(int x,int id)
{
    // cerr<<x<<','<<id<<'\n';
    for(int &i=hd[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(vis[i]) continue;
        vis[i]=vis[i^1]=1;
        hier(y,e[i].id);
    }
    ans.push_back({id,col[id]});
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>k>>st;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        add(u,v,i);
        add(v,u,i);
        deg[u]++;
        deg[v]++;
    }
    dfs(st);
    memset(vis,0,sizeof(vis));
    hier(st,0);
    ans.pop_back();
    reverse(ans.begin(),ans.end());
    cout<<ans.size()<<'\n';
    for(auto i:ans) cout<<i.first<<' '<<i.second<<'\n';
    return 0;
}
```

---

## 作者：dyc2022 (赞：2)

[更好的阅读体验](https://www.cnblogs.com/dyc2022/p/18730851)
***
如果原图是欧拉图，我们显然是会做的。我们可以先钦定哪些边是树边，然后在跑欧拉回路的过程中，直接删除非树边。这样我们就可以做到路径长度 $\le m$，非常优秀。

那我们不妨将其推广，由于一条边可以通过多次，因此我们可以进行转换，将经过多次的边转换成重边，然后让每条边通过一次。

那么问题就转化成给定一个图，通过添加 $\le n$ 条重边使其成为欧拉图。

那么我们考虑先将一棵生成树拎出来，然后从下往上递推，如果当前节点度数为奇数，就添加一条连往其父亲的边。因为这个时候父亲是还没有处理的，而父亲注定可以通过同样的调整满足欧拉图的条件。

那么这道题就做完了，时间复杂度显然是 $O(n+m)$，而每个点最多只会多连一条边（$s$ 不会向上连边），因此最后欧拉图的边数 $\le n+m-1$，可以通过。

```cpp
#include<bits/stdc++.h>
//#define int long long
#define endl '\n'
#define N 1006
using namespace std;
int n,m,tot,te[N*N],deg[N],vis[N],flag[N*N],K,s;
struct Tuple{int x,y,z;};
vector<Tuple> G[N];
//vector<tuple<int,int,int> > G[N];
vector<pair<int,int> > ans;
void dfs1(int u)
{
    vis[u]=1;vector<Tuple> tmp;
    for(auto [v,id,opt]:G[u])if(!vis[v]&&opt<=m)
    {
        dfs1(v),te[id]=1;
        if(deg[v]&1)
        {
            tmp.push_back({v,id,++tot});
            G[v].push_back({u,id,tot});
            deg[u]++,deg[v]++;
        }
    }
    for(auto t:tmp)G[u].push_back(t);
    tmp.clear();
}
void dfs2(int u)
{
    for(auto [v,id,opt]:G[u])if(!flag[opt])
    {
        flag[opt]=1;
        dfs2(v);
        ans.push_back({id,1});
    }
}
main()
{
    scanf("%d%d%d%d",&n,&m,&K,&s),tot=m;
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v),deg[u]++,deg[v]++;
        G[u].push_back({v,i,i}),G[v].push_back({u,i,i});
    }
    dfs1(s),dfs2(s);
    reverse(ans.begin(),ans.end());
    for(int i=ans.size()-1;~i;i--)
    {
        if(te[ans[i].first])continue;
        if(flag[ans[i].first]==2)continue;
        ans[i].second=0,flag[ans[i].first]=2;
    }
    printf("%d\n",(int)ans.size());
    for(auto [id,opt]:ans)printf("%d %d\n",id,opt);
    return 0;
}
```

---

