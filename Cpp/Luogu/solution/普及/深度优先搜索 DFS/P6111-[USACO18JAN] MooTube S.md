# [USACO18JAN] MooTube S

## 题目背景

*本题与 [金组同名题目](/problem/P4185) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

在业余时间，Farmer John 创建了一个新的视频共享服务，他将其命名为 MooTube。在 MooTube 上，Farmer John 的奶牛可以录制，分享和发现许多有趣的视频。他的奶牛已经发布了 $N$ 个视频（$1 \leq N \leq 5000$），为了方便将其编号为  $1 \ldots N$ 。然而，FJ 无法弄清楚如何帮助他的奶牛找到他们可能喜欢的新视频。

FJ 希望为每个 MooTube 视频创建一个“推荐视频”列表。这样，奶牛将被推荐与他们已经观看过的视频最相关的视频。

FJ 设计了一个“相关性”度量标准，顾名思义，它确定了两个视频相互之间的相关性。他选择 $N-1$ 对视频并手动计算其之间的相关性。然后，FJ 将他的视频建成一棵树，其中每个视频是节点，并且他手动将 $N-1$ 对视频连接。为了方便，FJ 选择了 $N-1$ 对，这样任意视频都可以通过一条连通路径到达任意其他视频。 FJ 决定将任意一对视频的相关性定义为沿此路径的任何连接的最小相关性。

Farmer John 想要选择一个 $K$ 值，以便在任何给定的 MooTube 视频旁边，推荐所有其他与该视频至少有 $K$ 相关的视频。然而，FJ 担心会向他的奶牛推荐太多的视频，这可能会分散他们对产奶的注意力！因此，他想设定适当的 $K$ 值。 Farmer John希望得到您的帮助，回答有关 $K$ 值的推荐视频的一些问题。

## 样例 #1

### 输入

```
4 3
1 2 3
2 3 2
2 4 4
1 2
4 1
3 1```

### 输出

```
3
0
2```

# 题解

## 作者：tribool4_in (赞：19)

似乎有很多题解用的是 离线+并查集，然而蒟蒻表示根本看不懂做法……

于是乎我打了个暴力 DFS，然后交了一通，结果就过了？？？

思路很简单，首先题目说，如果一个点 $u$ 的推荐视频中包含 $v$，必须要保证两点之间的路径的最小边长 $\ge k$。

显然，如果两点之间的路径的最小边长都 $\ge k$，则每条边长肯定都必须  $\ge k$。

因此，对于每个询问，从当前点出发进行深搜，如果当前边的长度 $< k$，则说明无法走通，否则情况数加一并继续深搜。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5;
int n, q, cnt = 0;
vector<int> G[N];
int g[N][N]; // 其实存图可以不用邻接矩阵，不过反正空间足够，存了也没事
void dfs(int u, int fa, int k) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i]; int w = g[u][v];
		if (v != fa && w >= k) {
			cnt++;
			dfs(v, u, k);
		}
	}
}
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i < n; i++) {
		int p, q, r;
		scanf("%d%d%d", &p, &q, &r);
		G[p].push_back(q), G[q].push_back(p), g[p][q] = g[q][p] = r;
	}
	for (int i = 1; i <= q; i++) {
		int k, v;
		scanf("%d%d", &k, &v);
		cnt = 0;
		dfs(v, -1, k);
		printf("%d\n", cnt);
	}
	return 0;
}

```

---

## 作者：HsKr (赞：6)

本题为并查集的较高难度题，可以考虑离线来做。

问题转化：给定一棵树，求每个点到其他点相关性大于$k$的数量，这里的相关性表示使两个点连接的边权中最小值。

例如：

```
1----->2----->3----->4----->5
  233    1      3       100
```

下方的数字表示边权：

```
1->2:233
1->3:1
1->4:1
1->5:1
2->3:1
2->4:1
2->5:1
3->4:3
3->5:3
4->5:100
```

此题代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN=100010;
int ans[MAXN+10];
int fa[MAXN+10];
int size[MAXN+10];//记录推荐数量 
int find(int x){//并查集的查询 
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void uni(int x,int y){//并查集的连接 
	int fx=find(x),fy=find(y);
	if(fx==fy) return;
    fa[fx]=fy;
    size[fy]+=size[fx];
}
struct Edge{//边（相关性） 
	int u,v,w;
}E[MAXN];
struct Ask{//询问 
	int k,v;
	int id;
}Q[MAXN];
bool cmpE(Edge a,Edge b){
	return a.w>b.w;
}
bool cmpQ(Ask a,Ask b){
	return a.k>b.k;
}
int main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){//初始化 
        fa[i]=i;
        size[i]=1;
    }
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
	}
	for(int i=1;i<=q;i++){
		scanf("%d%d",&Q[i].k,&Q[i].v);
		Q[i].id=i;
	}
	sort(E+1,E+n+1-1,cmpE);//对边的相关性进行排序 
	sort(Q+1,Q+q+1,cmpQ);//对询问的相关性进行排序 
	int j=1;//为什么不用内层从1枚举呢？排序后循环中k在降低，k大的时候能够满足那么k小的时候一定也能满足（k是要求满足的最小值） 
	for(int i=1;i<=q;i++){//枚举每一个询问
		while(j<n&&E[j].w>=Q[i].k){//只要不越界或没有达到相关性就循环操作 
			uni(E[j].u,E[j].v);//连接两边 
			j++;
		}
		ans[Q[i].id]=size[find(Q[i].v)]-1;//-1是因为自己不能推荐自己，然而size里面包含了自己 
	}
	for(int i=1;i<=q;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：miao5 (赞：3)

**题目大意：**

给一颗树，如果树上一点 $u$ 与另一点 $v$ 有联系，则他们间的距离必须大于 $k$ 。

求对于一个 $k_i$ ,找与给定的 $v_i$ 有联系的点个数。

**思路：**

如果 $v$ 与 $u$ 之间的最小边长大于等于 $k$ 那么他们之间的每一条边的长度肯定都大于等于 $k$ 。

之后我们可以进行DFS，如果当前边的长度小于 $k$ ，我们就返回，否则就答案加一并且继续DFS。

**code：**

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int N=1e5+5;
vector<int> g[N];
vector<int> a[N];
int n,q;
int cnt=0;
void dfs(int u,int fa,int k){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		int w=a[u][v];
		if(v==fa) continue;
		if(w>=k){
			cnt++;
			dfs(v,u,k);
		}
		
	}
}
int main(){
	cin>>n>>q;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		g[u].push_back(v);
		g[v].push_back(u);
		a[v][u]=a[u][v]=w;
	}
	for(int i=1;i<=q;i++){
		int k,v;
		cin>>k>>v;
		cnt=0;
		dfs(v,-1,k);
		cout<<cnt<<endl;
	}
}
```


---

## 作者：xh39 (赞：2)

前置算法:并查集。(为保证您的阅读质量,阅读此篇题解前请先学习并查集。)。

~~虽然我的算法重复了,可我觉得我可能讲得清楚一些。求过。~~
## 思路
我们把询问按k从大到小排序,把边按边权从大到排序。

我们就可以对于每个询问$i$,依次合并所有**不小于**$k[i]$的边连接的2个**节点**(注意宾语是**结点**)。

合并用并查集合并。

## 演示

下面来演示此算法。就拿样例来演示吧。
```cpp
4 3     排序后:
1 2 3   2 4 4
2 3 2   1 2 3
2 4 4   2 3 2
1 2     4 1
4 1     3 1
3 1     1 2
```
初始集合{1},{2},{3},{4}。

询问$k=4,v=1$:合并所有$>=4$。$2$合并到$4$,集合为{$1$},{$3$},{$2,4$};此时$v(1)$所在的集合元素个数为$1$。

询问$k=3,v=1$:合并所有$>=3$。$1$合并到$2$,集合为{$3$},{$1,2,4$};此时$v(1)$所在的集合元素个数为$3$。

询问$k=4,v=1$:合并所有$>=1$。$2$合并到$3$,集合为{$1,2,3,4$};此时$v(2)$所在的集合元素个数为$4$。

自己不能推荐自己。所以把所有的答案-1,然后输出。
## ac.code
已经讲得很具体了,代码里的注释就不会很多了。
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct ${ //存询问。
	int k,v,id; //id表示询问编号。好将答案存起来。最后一起输出。
}_[1000005];
struct xyq{
	int u,v,w;
}e[1000005];
struct rule{ //存图。
	bool operator()(const xyq &s1,const xyq &s2){
		return s1.w>s2.w;
	}
};
struct rule${ //自定义排序。
	bool operator()(const $ &s1,const $ &s2){
		return s1.k>s2.k;
	}
};
int f[1000005],ans[1000005],size[1000005]; //f存并查集的父亲。ans存答案,size存大小。
int getfather(int iakioi){ //并查集找父亲。
	if(f[iakioi]==iakioi){
		return iakioi;
	}
	f[iakioi]=getfather(f[iakioi]); //路径压缩。
	return f[iakioi];
}
int main(){
	int n,m,i,a,b,c,tot=0,sum=0;
	cin>>n>>m;
	for(i=0;i<n-1;++i){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	for(i=0;i<m;++i){
		cin>>_[i].k>>_[i].v;
		_[i].id=i; //初始化编号别漏掉。
	}
	for(i=0;i<=n;++i){
		f[i]=i; //一开始自己的父亲都是自己。
		size[i]=1; //一开始元素的大小都是1。
	}
	sort(e,e+n,rule());
	sort(_,_+m,rule$());
	for(i=0;i<m;++i){
		while(_[i].k<=e[tot].w){
			size[getfather(e[tot].v)]+=size[getfather(e[tot].u)];
			f[getfather(e[tot].u)]=getfather(e[tot].v);
			++tot;
		}
		ans[_[i].id]=size[getfather(_[i].v)];
	}
	for(i=0;i<m;++i){
		cout<<ans[i]-1<<endl; //减1是因为自己不推荐自己。
	}
	return 0;
}
```

---

## 作者：wmy_goes_to_thu (赞：2)

一看到询问个数很多，肯定是并查集呀！

但是，如果直接并查集，会有删边的问题，那怎么办呢？我们可以按 $k$ 排个序，然后每次不用删边，只需要加边就可以了。

代码：
```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
int fa[100005];
int ans[100005];
int ha[100005];
int findfather(int x)
{
	if(x==fa[x])return x;
	return fa[x]=findfather(fa[x]);
}
vector<int>g[100005];
struct apple
{
	int u,v,w;
	bool operator<(const apple &other)const
	{
		return w>other.w;
	}
};
struct pear
{
	int kk,vv,qq;
	bool operator<(const pear &other)const
	{
		return kk>other.kk;
	}
};
apple st[100005];
pear pr[100005];
void insertedge(int x)
{
	int uu=st[x].u,vv=st[x].v;
	int fuu=findfather(uu),fvv=findfather(vv);
	fa[fuu]=fvv;
	ha[fvv]+=ha[fuu];
}
int main()
{
	for(int i=1;i<=100000;i++)fa[i]=i,ha[i]=1;
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<n;i++)
	{
		int ppp,pppp,ppppp;
		scanf("%d%d%d",&ppp,&pppp,&ppppp);
		st[i].u=ppp,st[i].v=pppp,st[i].w=ppppp;
	}
	sort(st+1,st+n);
	for(int i=1;i<=q;i++)
	{
		int kkksc03,vvvsc03;
		scanf("%d%d",&kkksc03,&vvvsc03);
		pr[i].kk=kkksc03,pr[i].vv=vvvsc03,pr[i].qq=i;
	}
	sort(pr+1,pr+q+1);
	int j=1;
	for(int i=1;i<=q;i++)
	{
		for(;j<n&&st[j].w>=pr[i].kk;j++)insertedge(j);
		int fvv=findfather(pr[i].vv);
		ans[pr[i].qq]=ha[fvv];
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]-1);
	return 0;
}
```


---

## 作者：Little09 (赞：2)

这题的加强版的我们 PJ 模拟赛的 T4，个人感觉还有点意思的。

先把题目转化一下，就是每个询问给你一个 $K$ 值和 $v$ 值，把所有小于 $K$ 的边都删掉，然后从 $v$ 能走到几个节点。

可以离线，所以选择离线。把问题按 $K$ 从大到小排序，把边按权值从大到小排序。然后依次考虑每个问题，进行加边操作。这里加边的时候要维护每个点所在的连通块的大小，所以可以用权值并查集维护。

为什么不从小到大排序然后维护删边？因为删边比加边难维护多了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct edge//每条边
{
	int x,y,z;
}t[100005];
struct ques//每个问题
{
	int k,x,id;
}q[100005];
bool cmp1(edge x,edge y)
{
	return x.z>y.z;
}
bool cmp2(ques x,ques y)
{
	return x.k>y.k;
}
int fa[100005],res[100005],ans[100005];//res表示i所在的连通块的大小
int find(int x)
{
	if (x==fa[x]) return x;
	int u=find(fa[x]);
	res[x]=res[u];
	fa[x]=u;
	return fa[x];
}
int main()
{
    cin >> n >> m;
    for (int i=1;i<n;i++)
    {
    	cin >> t[i].x >> t[i].y >> t[i].z;
	}
	for (int i=1;i<=n;i++) fa[i]=i,res[i]=1;
	sort(t+1,t+n,cmp1);
	for (int i=1;i<=m;i++)
	{
		cin >> q[i].k >> q[i].x;
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp2);
	int num=0;
	for (int i=1;i<=m;i++)
	{
		for (;num<n;num++)
		{
			if (t[num+1].z>=q[i].k) 
			{
				int x1=find(t[num+1].x),y1=find(t[num+1].y);
				fa[x1]=y1;
				res[x1]+=res[y1];
				res[y1]=res[x1];
			}
			else break;
		}
		int p=find(q[i].x);
		ans[q[i].id]=res[q[i].x]-1;
	}
	for (int i=1;i<=m;i++) cout << ans[i] << endl;
    return 0;
}
```


---

## 作者：sycqwq (赞：1)

__题意__

给你一棵树

每次询问有多少个点，到点 $v_i$ 的简单路径中最小权值大于 $k_i$

__思路__

这个就是个暴力 $dfs$

可以考虑先把询问按 $k_i$ 值从大到小排序

因为最小值要大于 $k_i$ ，所以小于 $k_i$ 的边是不能走的

所以，可以根据询问，每次把大于 $k_i$ 的边加入

然后 $dfs$ 判断有多少可以到的点

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
struct node
{
	int x,y,k;
}a[5005];
vector<int> e[5005];
int cmp(node s1,node s2)
{
	return s1.k>s2.k;
}
struct nod
{
	int k,v,s,id;	
}b[5005];
int cmp1(nod s1,nod s2)
{
	return s1.k>s2.k;
}
int bk[5005],t;
void dfs(int x)//暴力判断
{
	if(bk[x]==1)
		return ;
	++t;
	bk[x]=1;
	for(int i=0;i<e[x].size();i++)
	{
		dfs(e[x][i]);
	}
}
int cmp2(nod s1,nod s2)
{
	return s1.id<s2.id;
}
int main(){
//	freopen("mootube.in","r",strin);
//	freopen("mootube.out","w",strout);
	cin>>n>>q;
	for(int i=1;i<n;i++)
		cin>>a[i].x>>a[i].y>>a[i].k;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=q;i++)
	{
		cin>>b[i].k>>b[i].v;
		b[i].id=i;
	}
	sort(b+1,b+q+1,cmp1);//按k值排序
	int l=1;
	for(int i=1;i<=q;i++)
	{
		for(int j=l;j<=n;j++)
		{ 
//		cout<<"****"<<a[j].k<<' '<<b[i].k<<endl;
			if(a[j].k<b[i].k)//加入小于k的边
				break;
			e[a[j].x].push_back(a[j].y);
			e[a[j].y].push_back(a[j].x);
			++l;
		}
		t=0;
		
		memset(bk,0,sizeof(bk));
		dfs(b[i].v);
//		cout<<"####"<<b[i].id<<' '<<l<<endl;
		b[i].s=--t;//因为dfs中，会加入自己，所以减一
	}
	sort(b+1,b+q+1,cmp2);//按问题编号排序，然后输出
	for(int i=1;i<=q;i++)
		cout<<b[i].s<<endl;
	return 0;
}
```

---

## 作者：银杉水杉秃杉 (赞：1)

[题目传送门 P6111 MooTube S](https://www.luogu.com.cn/problem/P6111)

本题做法与[金组同名题目](https://www.luogu.com.cn/problem/P4185)没有区别，也就数据范围不一样，时间复杂度都为$O(NlogN+QlogQ)$。

思路主要为并查集，具体做法如下：

先将所有边$e$和询问$k$降序排序，再对于每一个询问，扫完大于等于$k_i$的$e_j$，将$e_j$两端点连接至一个并查集，然后记录所查询的点$v_i$所在并查集点的数量$s_{v_i}-1$（因为要减去自身）为答案$ans_i$，最后按序输出$ans_i$即可。

话不多说，直接上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int f[5010],s[5010],ans[5010];//金组同名题目将数组范围改为100010即可
struct edge
{
	int u,v,w;
}e[5010];
struct ask
{
	int k,v,id;
}q[5010];
bool cmpe(edge a,edge b)//按边权排序
{
	return a.w>b.w;
}
bool cmpq(ask a,ask b)//按k排序
{
	return a.k>b.k;
}
int find(int x)//寻找父亲
{
	return f[x]==x?x:f[x]=find(f[x]);
}
void merge(int x,int y)//合并
{
	int fx=find(x),fy=find(y);
	if (fx==fy)
		return;
	f[fx]=fy;
	s[fy]+=s[fx];//合并时记得更新点的数量
}
int main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
	{
		f[i]=i;
		s[i]=1;
	}
	for (int i=1;i<n;i++)//有n-1条边
		cin>>e[i].u>>e[i].v>>e[i].w;
	for (int i=1;i<=m;i++)
	{
		cin>>q[i].k>>q[i].v;
		q[i].id=i;//记录询问序号
	}
	sort(e+1,e+n,cmpe);//边排序
	sort(q+1,q+m+1,cmpq);//询问排序
	int j=1;
	for (int i=1;i<=m;i++)
	{
		while (j<n&&e[j].w>=q[i].k)//扫边
		{
			merge(e[j].u,e[j].v);//合并
			j++;
		}
		ans[q[i].id]=s[find(q[i].v)]-1;//记录答案
	}
	for (int i=1;i<=m;i++)
		cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：neyczhy (赞：1)

不多说，本题为并查集的较高难度题，可以考虑离线来做。

问题转化：给定一棵树，求每个点到其他点相关性大于kk的数量，这里的相关性表示使两个点连接的边权中最小值。  
code：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct ${ //存询问。
    int k,v,id; //id表示询问编号。好将答案存起来。最后一起输出。
}_[1000005];
struct xyq{
    int u,v,w;
}e[1000005];
struct rule{ //存图。
    bool operator()(const xyq &s1,const xyq &s2){
        return s1.w>s2.w;
    }
};
struct rule${ //自定义排序。
    bool operator()(const $ &s1,const $ &s2){
        return s1.k>s2.k;
    }
};
int f[1000005],ans[1000005],size[1000005]; //f存并查集的父亲。ans存答案,size存大小。
int getfather(int iakioi){ //并查集找父亲。
    if(f[iakioi]==iakioi){
        return iakioi;
    }
    f[iakioi]=getfather(f[iakioi]); //路径压缩。
    return f[iakioi];
}
int main(){
    int n,m,i,a,b,c,tot=0,sum=0;
    cin>>n>>m;
    for(i=0;i<n-1;++i){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    for(i=0;i<m;++i){
        cin>>_[i].k>>_[i].v;
        _[i].id=i; //初始化编号别漏掉。
    }
    for(i=0;i<=n;++i){
        f[i]=i; //一开始自己的父亲都是自己。
        size[i]=1; //一开始元素的大小都是1。
    }
    sort(e,e+n,rule());
    sort(_,_+m,rule$());
    for(i=0;i<m;++i){
        while(_[i].k<=e[tot].w){
            size[getfather(e[tot].v)]+=size[getfather(e[tot].u)];
            f[getfather(e[tot].u)]=getfather(e[tot].v);
            ++tot;
        }
        ans[_[i].id]=size[getfather(_[i].v)];
    }
    for(i=0;i<m;++i){
        cout<<ans[i]-1<<endl; //减1是因为自己不推荐自己。
    }
    return 0;
}
```



---

## 作者：qhy_ (赞：0)

首先，我们可以建一个邻接表来建图

然后我们可以直接 $DFS$ 暴搜（搜到边权比 $k$ 小的直接退出，因为后面的肯定不行）到一个点 $ans+1$。

```cpp
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int kMaxN = 5e3 + 1;

struct node {
  int get, moo[1000], f[1000];
} cow[kMaxN];
int n, q, k, ans;
bool f[kMaxN];

void dfs(int v) {  //DFS
  for (int i = 0; i < cow[v].get; i++) {
    if (cow[v].f[i] >= k && !f[cow[v].moo[i]]) {
      ans++, f[cow[v].moo[i]] = 1;
      dfs(cow[v].moo[i]);
    }
  }
}

int main() {
  cin >> n >> q;
  for (int i = 0; i < n - 1; i++) {
    int p, q, r;
    cin >> p >> q >> r;
    cow[p].moo[cow[p].get] = q, cow[q].moo[cow[q].get] = p;
    cow[p].f[cow[p].get++] = r, cow[q].f[cow[q].get++] = r; //建图
  }
  for (int i = 0; i < q; i++) {
    memset(f, 0, sizeof(f)), ans = 0;
    int v;
    cin >> k >> v;
    f[v] = 1, dfs(v);
    cout << ans << endl;
  }
  return 0;
}
```

---

## 作者：信守天下 (赞：0)

## [洛谷传送门](https://www.luogu.com.cn/problem/P6111)
## 思路
$N$ 和 $Q$ 都不⼤，所以直接暴力。

对于每个询问都进⾏⼀次树的遍历即可。

### 时间复杂度
询问数量 $O(Q)$ ，遍历 $O(N)$ ，总共 $O(NQ)$ 。
## $code$
~~~cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 5e3 + 1;

struct E {
  int p, r;  // 指向节点、关联性
};
vector<E> e[kMaxN];
int n, q, x, y, r;

int S(int f, int x) {                        // 父亲f，当前点x，搜索关联点数
  int c = 1;                                 // 初始化点数
  for (int i = 0; i < e[x].size(); i++) {    // 枚举邻边
    if (e[x][i].p != f && e[x][i].r >= r) {  // 非父亲且关联
      c += S(x, e[x][i].p);                  // 搜索邻点并累加
    }
  }
  return c;
}

int main() {
  cin >> n >> q;
  for (int i = 1; i < n; i++) {
    cin >> x >> y >> r;
    e[x].push_back({y, r});
    e[y].push_back({x, r});
  }
  while (q--) {
    cin >> r >> x;
    cout << S(0, x) - 1 << endl;  // 减去自身
  }
  return 0;
}

~~~

---

## 作者：Singercoder (赞：0)

kruskal重构树模板题；

对边按照边权从大到小排序，然后建立kruskal重构树，每次询问向上倍增跳父亲即可，输出答案为当前子树下叶子节点个数减一。

比起并查集的优点大概就是支持询问在线，复杂度均为$O(nlogn)$。

```cpp
#include<bits/stdc++.h>

#define ri register int 

#define inf 0x3f3f3f3f

using namespace std;

inline int read()
{
	ri a=0,f=1,c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(isdigit(c))
	{
		a=a*10+c-'0';
		c=getchar();
	}
	return a*f;
}

const int N=2e5+10;

int n,q;

struct edge
{
	int u,v,w;
}e[N];
bool operator > (const edge &X,const edge &Y) {return X.w>Y.w;}

int nn,lg[N],Fa[N];
int get_Fa(int u){return u==Fa[u]?u:Fa[u]=get_Fa(Fa[u]);}
int ch[N][2],fa[N][20],d[N],sz[N],c[N];
bool vis[N];
void dfs(int u)
{
	vis[u]=1;
	for(ri i=1;i<=lg[d[u]];++i)fa[u][i]=fa[fa[u][i-1]][i-1];
	if(!ch[u][0])sz[u]=1;
	else 
	{
		fa[ch[u][0]][0]=u;
		fa[ch[u][1]][0]=u;
		d[ch[u][0]]=d[u]+1;
		d[ch[u][1]]=d[u]+1;
		dfs(ch[u][0]);
		dfs(ch[u][1]);
		sz[u]+=sz[ch[u][0]]+sz[ch[u][1]];
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	
	n=nn=read();q=read();
	for(ri i=1;i<=n-1;++i){e[i].u=read();e[i].v=read();e[i].w=read();}
	
	//kurskal
	sort(e+1,e+n,greater<edge>());
	for(ri i=1;i<=nn;++i){Fa[i]=i;c[i]=inf;}
	for(ri i=1;i<=n-1;++i)
	{
		ri u=get_Fa(e[i].u),v=get_Fa(e[i].v),w=e[i].w;
		if(u!=v)
		{
			++nn;
			Fa[u]=Fa[v]=Fa[nn]=nn;
			ch[nn][0]=u;
			ch[nn][1]=v;
			c[nn]=w;
		}
	}
	for(ri i=2;i<=nn;++i)lg[i]=lg[i>>1]+1;
	for(ri i=1;i<=n;++i)if(!vis[i])dfs(get_Fa(i));
	
	//cal
	for(ri i=1;i<=q;++i)
	{
		ri k=read(),u=read();
		for(ri j=lg[d[u]];j>=0;--j)if(fa[u][j] && c[fa[u][j]]>=k)u=fa[u][j];
		printf("%d\n",sz[u]-1);
	}
	
	return 0;
}
```



---

## 作者：jichi (赞：0)

关于这道题的数据加强版，就是题面里的$Ag$的题目啦

这篇题解主要是对于其他题解没有提及为什么按$k$从大到小排序就是正解的补充

我的思路如下：
（先贴代码,$siz[x]$表示$x$所在连通块大小）

```cpp
while(cur<=n&&e[cur].w>=a[i].k){
    merge(find(e[cur].u),find(e[cur].v));cur++;
}
ans[a[i].id]=siz[find(a[i].v)]-1;
```
我们将$k$和边权从大到小进行排序之后，如果扫到一个边权比$k$更大的边，就将这条边加入连通块，然后我们所求的这个点的相关就是它所在联通块的大小（因为目前被加入的边都是大于$k$的）。

$AC$  $Code$

```cpp
#include<bits/stdc++.h> 

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	int xx=x%10;
	putchar(xx+'0');
}

int n,q;
int fa[100010],siz[100010],ans[100010];
struct node{
	int u,v,w;
}e[100010];
struct edge{
	int k,v,id;
}a[100010];
inline bool cmp1(const node&a,const node&b){
	return a.w>b.w;
}

inline bool cmp2(const edge&a,const edge&b){
	return a.k>b.k;
}

inline void merge(int x,int y){
	if(x==y) return;
	fa[y]=x;siz[x]+=siz[y];
}

inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

signed main(){
    int n=read(),q=read();
    for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
    for(int i=1;i<n;i++) e[i].u=read(),e[i].v=read(),e[i].w=read();
    for(int i=1;i<=q;i++) a[i].k=read(),a[i].v=read(),a[i].id=i;
    sort(e+1,e+n,cmp1);sort(a+1,a+q+1,cmp2);
    int cur=1;
    for(int i=1;i<=q;i++){
    	while(cur<=n&&e[cur].w>=a[i].k){
    		merge(find(e[cur].u),find(e[cur].v));cur++;
		}
		ans[a[i].id]=siz[find(a[i].v)]-1;
	}
	for(int i=1;i<=q;i++) write(ans[i]),puts("");
	return 0;
}
```


---

## 作者：Na2PtCl6 (赞：0)

此题可以不用并查集来做哦（废话）

## 分析题目
不难发现，题目中的推荐视频数就是某个节点在满足边权 $\ge k$ 的情况下能到达的所有节点数

图解样例

![](https://cdn.luogu.com.cn/upload/image_hosting/2xwapppy.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于第一个询问，从节点 2 出发，我们可以通过边权 \>1 的边 2-1 走到节点 1，通过边权 \>1 的边 2-4 走到节点 4，通过边权 \>1 的边 2-3 走到节点 3。共走到 3 个点。

对于第二个询问，从节点 1 出发，没有边权 \>=4 的边。共走到 0 个点。 

对于第三个询问，从节点 1 出发，可以通过 1-2 到达 2，从节点 2 可以通过 2-4，到达节点 4。共到达 2 个点。

## 代码实现
考虑到数据较小，我们用 bfs 实现每次的遍历。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5004;
char vis[maxn];
int n,q,p,id,r,k,v;
struct edge{ int to,val;};
vector < edge > vec[maxn];

int bfs(int k,int from){
	int cnt=0;
	queue < int > q;
	q.push(from);
	memset(vis,0,sizeof(vis));
	vis[from]=1;
	while(!q.empty()){
		int fr=q.front();
		q.pop();
		vector < edge > v=vec[fr];
		for(int i=0;i<v.size();i++){
			if(!vis[v[i].to]&&v[i].val>=k){
				++cnt;  //发现可以到达的点,结果+1 
				q.push(v[i].to);
				vis[v[i].to]=1;
			}
		}
	}
	return cnt;
}

int main(){
	scanf("%d %d",&n,&q);
	while(--n){
		scanf("%d %d %d",&p,&id,&r);
		//无向图要双向加边 
		vec[p].push_back((edge){id,r});
		vec[id].push_back((edge){p,r});
	}
	while(q--){
		scanf("%d %d",&k,&v);
		printf("%d\n",bfs(k,v));
	}
	return 0;
}
```

---

## 作者：Phykyer (赞：0)

[到blog食用效果更佳](https://www.luogu.com.cn/blog/phykyerblog/solution-p6111)

第一眼看见了“与更高难的题目”仅有数据范围不同，再瞟一眼数据范围才 $5000$ ，那不就暴力就完事了（~~话说现在的题解居然没有暴力的实在太强了~~）

关于暴力：对于每个询问从询问点开始跑一遍 $dfs$ 即可，代码如下：

```cpp
#include <cstdio>
using namespace std;

const int N = 5010;

int n, q, ans;
int head[N], ver[N << 1], edge[N << 1], Next[N << 1], cnt;

inline void add(int x, int y, int z) {
	ver[++cnt] = y; edge[cnt] = z; Next[cnt] = head[x]; head[x] = cnt;
}

inline void dfs(int x, int fa, int val) {
	for (int i = head[x]; i; i = Next[i]) {
		int y = ver[i], z = edge[i];
		if (y == fa) continue;
		if (val > z) continue; // 不满足相关值 >=k
		dfs(y, x, val);
		ans += 1;
	}
}

inline int read() {
	int x = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}

int main() {
	n = read(); q = read();
	int x, y, z;
	for (int i = 1; i < n; i++) {
		x = read(); y = read(); z = read();
		add(x, y, z); add(y, x, z);
	}
	while (q--) {
		y = read(); x = read();
		ans = 0;
		dfs(x, 0, y);
		printf("%d\n", ans);
	}
	return 0;
}
```

而对于数据范围达到了 $10^{5}$ 的情况来说，在线处理就显得不可行了。于是考虑离线算法。

可以比较容易想到：将读入的边按边权从大到小排序，对于读入的询问也按 $k$ 值从大到小排序。

具体来说就是按 $k$ 值从大到小处理问题，当前的 $k$ 值会不断缩小，每个询问前判断是否有边的权值满足 $>=k$ 的条件，如果有只要进行合并操作即可（因为这条边的边权一定大于等于之后所有询问的 $k$），这样处理询问过程的复杂度就可以被压缩到 $O(n)$，程序整体复杂度为 $O(nlogn)$。

以下为代码（注意点代码内有注释）

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 100010;

int n, q, ans[N];//ans储存答案 
int fa[N], size[N];//size为并查集大小，也就是每次询问的答案 

struct edge {
	int x, y, z;
}t[N];

struct questions {
	int u, k, id;//id记录问题编号 
}a[N];

inline bool comp(edge a, edge b) {return a.z > b.z;}
inline bool cmp(questions x, questions y) {return x.k > y.k;}

inline int get(int x) {
	return x == fa[x] ? x : fa[x] = get(fa[x]);
}

inline int read() {
	int x = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}

int main() {
	n = read(); q = read();
	for (int i = 1; i <= n; i++) fa[i] = i, size[i] = 1;
	int x, y, z;
	for (int i = 1; i < n; i++) {
		t[i].x = read(); t[i].y = read(); t[i].z = read();
	}
	for (int i = 1; i <= q; i++) {
		a[i].k = read(); a[i].u = read(); a[i].id = i;
	}
	sort(a + 1, a + q + 1, cmp);
	sort(t + 1, t + n + 1, comp);
	int now = 0;
	for (int i = 1; i <= q; i++) {
		while (t[now + 1].z >= a[i].k) {//满足边权>=k 
			now += 1;
			x = get(t[now].x); y = get(t[now].y);
			if (x == y) continue;
			fa[x] = y;
			size[y] += size[x];//合并记得合并size 
		}
		ans[a[i].id] = size[get(a[i].u)] - 1;//答案记得-1因为推荐不包含自己本身 
	}
	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
	return 0;
}
```


---

