# Fools and Foolproof Roads

## 题目描述

You must have heard all about the Foolland on your Geography lessons. Specifically, you must know that federal structure of this country has been the same for many centuries. The country consists of $ n $ cities, some pairs of cities are connected by bidirectional roads, each road is described by its length $ l_{i} $ .

The fools lived in their land joyfully, but a recent revolution changed the king. Now the king is Vasily the Bear. Vasily divided the country cities into regions, so that any two cities of the same region have a path along the roads between them and any two cities of different regions don't have such path. Then Vasily decided to upgrade the road network and construct exactly $ p $ new roads in the country. Constructing a road goes like this:

1. We choose a pair of distinct cities $ u $ , $ v $ that will be connected by a new road (at that, it is possible that there already is a road between these cities).
2. We define the length of the new road: if cities $ u $ , $ v $ belong to distinct regions, then the length is calculated as $ min(10^{9},S+1) $ ( $ S $ — the total length of all roads that exist in the linked regions), otherwise we assume that the length equals $ 1000 $ .
3. We build a road of the specified length between the chosen cities. If the new road connects two distinct regions, after construction of the road these regions are combined into one new region.

Vasily wants the road constructing process to result in the country that consists exactly of $ q $ regions. Your task is to come up with such road constructing plan for Vasily that it meets the requirement and minimizes the total length of the built roads.

## 说明/提示

Consider the first sample. Before the reform the Foolland consists of four regions. The first region includes cities $ 1 $ , $ 2 $ , $ 3 $ , the second region has cities $ 4 $ and $ 6 $ , the third region has cities $ 5 $ , $ 7 $ , $ 8 $ , the fourth region has city $ 9 $ . The total length of the roads in these cities is $ 11 $ , $ 20 $ , $ 5 $ and $ 0 $ , correspondingly. According to the plan, we first build the road of length $ 6 $ between cities $ 5 $ and $ 9 $ , then the road of length $ 23 $ between cities $ 1 $ and $ 9 $ . Thus, the total length of the built roads equals $ 29 $ .

## 样例 #1

### 输入

```
9 6 2 2
1 2 2
3 2 1
4 6 20
1 3 8
7 8 3
5 7 2
```

### 输出

```
YES
9 5
1 9
```

## 样例 #2

### 输入

```
2 0 1 2
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
2 0 0 2
```

### 输出

```
YES
```

# 题解

## 作者：AladV (赞：2)

## 题意分析
首先我们想到，因为题目中允许有重边，所以说每次加边只会让整个图的连通分量的数量 $-1$ 或不变。所以我们得到了第一个结论：如果 cnt 也就是连通块的数量本来就小于 q,那么肯定做不到。同理，如果 $cnt-q>p$，也就是把所有边都用完了还是太多了，那也不行。最后一个 no 的情况就是如果本来没边，但是 $p\not=0$，然后 $q=n$，那么就是说我们只要加边就一定会让 $cnt-1$ 但是人家要求最后是 n 个，所以也不行。

## 做法分析
我们可以想到一个显而易见的贪心：每次拿两个边权最小的连通块出来，让他们两个连起来。这样一定是最优的，因为这个东西不存在之后的某种操作比现在好。

我们在每次加边的时候维护并查集，每次将边的两端加入到同一个并查集里边，同时用一个 siz 数组来维护每个并查集也就是每个连通块的边权和。

之后我们让每一个并查集出一个“代表”，在这里我选择了这个并查集的大祖先。然后把这个代表的编号和他所在的并查集的大小 siz 塞进一个优先队列。之后就 
`
while cnt>q
`
，每次从队头取出两个，这两个一定是最小的，然后让这两个的两个代表 merge 在一起，计算 siz，记得 $p-1$。

之后还要注意一点，当 $cnt=q$ 的时候退出循环，此时 p 可能还有，也就是我们添加的边还不够，这个时候我们只需要找到任意一个点，让这个点和他的大祖先不停的连边，连到够为止，细节详见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int cnt,fa[N],n,m,p,q,siz[N];
struct ConnectBlock
{
    int Size,dpty;
    // int ;
    bool operator < (const ConnectBlock &b) const
	{
		return Size>b.Size;
	}
};
priority_queue<ConnectBlock> que;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while (c<'0'||c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
int getfa(int x)
{
    if(x==fa[x]) return x;
    return getfa(fa[x]);
}
void merge(int x,int y,int z)
{
    int fax=getfa(x),fay=getfa(y);
    if(fax==fay) siz[fax]+=z;
    else 
    {
        fa[fay]=fax;
        siz[fax]+=siz[fay]+z;
        cnt--;
    }
}
signed main()
{
    n=read(),m=read(),p=read(),q=read();
    cnt=n;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++) {int x=read(),y=read(),z=read();merge(x,y,z);}
    for(int i=1;i<=n;i++) if(i==fa[i]) que.push(ConnectBlock{siz[i],i});
    if(cnt<q || cnt-p>q || (!m && q==n && p)) puts("NO"),exit(0);
    puts("YES");
    while (cnt>q)
    {
        ConnectBlock x=que.top();que.pop();
        ConnectBlock y=que.top();que.pop();
        merge(x.dpty,y.dpty,min((int)1e9,x.Size+y.Size+1));
        cout<<x.dpty<<" "<<y.dpty<<endl;
        p--;
        que.push(ConnectBlock{siz[x.dpty],x.dpty});
    }
    for(int i=1;i<=n;i++)
    {
        if(i!=getfa(i)) 
        {
            while(p--) cout<<i<<" "<<getfa(i)<<endl;
            return 0;
        }
    }
    return 0;
}
```


---

## 作者：_edge_ (赞：1)

我们先来分析一下题目的条件，给你一堆连通块，然后在里面连边，连出 $q$ 个连通块，可以有重边并且不算做贡献。

如果我们去连了一条边，那么会消失一个连通块，如果不是重边的话。

因此我们可以得到连边至少要多少个，这个可以判掉无解的情况。

然后我们考虑如何去构造这个方案，我们发现，其实每次选两个边权和比较小的连通块不会使得答案变劣。

假如说不是选这两个连通块，另外两个连通块加上去的边权肯定是比这两个要大的，并且在之后不会产生其余贡献，所以这样贪心的决策还是挺对的。

当然，我们如何去维护这个东西也是很关键的问题。

考虑可以用堆来维护连通块，由于我不想用并查集，所以我选择直接将两个值给合并。

对于还有冗余的要添加的，随便找两个就可以了。

要开 long long，以及注意题目所给出的 $\min$ 条件。

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#define int long long 
using namespace std;
const int INF=1e6+5;
struct _node_edge{
	int to_,next_,disv_;
}edge[INF<<1];
int tot,head[INF],num[INF],l[INF][5],ans[INF][5],ans1;
void add_edge(int x,int y,int z) {
	edge[++tot]=(_node_edge){y,head[x],z};
	head[x]=tot;return ;
}
struct _node_data{
	int v,id;
	bool operator < (const _node_data &x) const {
		return x.v<v; 
	};
} aa[INF];
int DFS(int x) {
	if (num[x]) return 0;
	num[x]=tot;
	if (!l[tot][0]) l[tot][0]=x;
	else l[tot][1]=x;
	int sum=0;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		sum+=DFS(v)+edge[i].disv_;
	}
	return sum;
}
int n,m,p,qq;
priority_queue <_node_data> q;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>p>>qq;
	for (int i=1;i<=m;i++) {
		int x=0,y=0,z=0;
		cin>>x>>y>>z;
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	tot=0;
	for (int i=1;i<=n;i++) {
		if (num[i]) continue;
		tot++;aa[tot].v=DFS(i);
		aa[tot].id=tot;
		q.push(aa[tot]);
	}
//	if (n==1000 && m==100000)
//		cout<<tot<<" ??\n";
	if (tot-p>qq) {cout<<"NO\n";return 0;}
//	cout<<"YES\n";
	int pp=p;p=tot-qq;pp-=p;
	while (q.size()>1 && p) {
		_node_data x=q.top();q.pop();
		_node_data y=q.top();q.pop();
		ans[++ans1][0]=l[x.id][0];
		ans[ans1][1]=l[y.id][0];
//		cout<<x.v<<" "<<x.v<<" "
		x.v=(x.v+y.v)+min(x.v+y.v+1,(int)(1e9))+1;
		if (!l[x.id][1]) l[x.id][1]=l[y.id][0];
		q.push(x);
		p--;
	}
	
	while (pp && q.size()) {
		_node_data x=q.top();q.pop();
		if (!l[x.id][0] || !l[x.id][1]) continue;
//		cout<<x.v<<" fad?\n";
		ans[++ans1][0]=l[x.id][0];
		ans[ans1][1]=l[x.id][1];
		q.push(x);pp--;
	}
	
	if (!p && !pp) cout<<"YES\n";
	else {cout<<"NO\n";return 0;}
	for (int i=1;i<=ans1;i++)
		cout<<ans[i][0]<<" "<<ans[i][1]<<"\n";
	return 0;
}
```


---

## 作者：sdxjzsq (赞：0)

### 题目链接
https://www.luogu.com.cn/problem/CF362D  
http://codeforces.com/contest/362/problem/D  
### 题目大意  
已知一个 $n$ 个点 $m$ 条边的无向图，求能否通过添加 $p$ 条边使图中连通块数恰好为 $q$ 。若不能，则输出`NO`，否则输出`YES`，并求出加边后边权和最小的方案。  
其中，可以在任意两点（即使已经相连）加边，若两点不在一个连通块中，则加的边长度为 $min(10^9,S+1)$ ，否则为 $1000$ 。其中 $S$ 要连接的两个连通块的边权和。  
### 思路  
算法：并查集+优先队列。  
本题整个过程中只需要知道两点是否在一个连通块中，因此可以用并查集来写。  
首先是判断无解的情况，分为以下三种：  
1. 加边（也就是连接连通块）后联通块数量依旧大于 $q$。(`tot-p>q`)  
2. 加边前连通块数量已经小于 $q$。(`tot<q`)
3. 点的数量等于 $q$ ，且没有边，但 $p>0$ ，显然任意两点间均不能加边。(`!m&&!(q-n)&&p`)  

因为判断需要知道连通块数量 `tot`，因此需要先建好并查集。  
之后求最优方案。因为需要边权值最小，因此可以用优先队列维护当前最小的两个连通块，每次取出进行合并并输出合并的父亲节点的编号，直到连通块数量等于 $q$。  
最后如果加完边后依然 $q>0$，那么随便找在相同连通块中的两个点，剩下的边都加给他们即可。  
### code  
~~你看代码这么短，才29行(压了好久)~~
``` cpp
#include<bits/stdc++.h>
using namespace std;
const long long maxn = 1e5+7,inf = 1e9;
long long n,m,p,q,sz[maxn],fa[maxn],tot;
struct node
{
	long long x,sz;
	bool operator < (const node& rhs) const {return sz>rhs.sz;}
}t1,t2;
priority_queue<node> Q;
long long find(long long x){return x==fa[x]?x:fa[x]=find(fa[x]);}
long long merge(long long x,long long y,long long l)
{
	x=find(x),y=find(y);
	if(x==y)sz[x]+=l;else fa[x]=y,sz[y]+=l+sz[x],tot--;
}
int main()
{
	scanf("%lld%lld%lld%lld",&n,&m,&p,&q),tot=n;//tot为连通块数 
	for(long long i=1;i<=n;++i)fa[i]=i;//初始化并查集 
	for(long long i=1,x,y,l;i<=m;++i)scanf("%lld%lld%lld",&x,&y,&l),merge(x,y,l);//构建并查集 
	if(tot-p>q||tot<q||(!m&&!(q-n)&&p))return 0*puts("NO");else puts("YES");//判断无解 
	for(int i=1;i<=n;++i)if(find(i)==i)Q.push((node){i,sz[fa[i]]});// 
	while(tot>q)t1=Q.top(),Q.pop(),t2=Q.top(),Q.pop(),p--,tot--,printf("%lld %lld\n",t1.x,t2.x)
	,fa[t2.x]=t1.x,sz[t1.x]+=min(inf,t1.sz+t2.sz+1)+t2.sz,Q.push((node){t1.x,sz[t1.x]});//取出最小的两个连通块合并后再压入优先队列 
	for(tot=1;tot<=n;++tot)if(find(tot)!=tot)break;//随便找在相同连通块中的两个点
	while(p--)printf("%lld %lld\n",tot,fa[tot]);
	return 0;
}
```

---

