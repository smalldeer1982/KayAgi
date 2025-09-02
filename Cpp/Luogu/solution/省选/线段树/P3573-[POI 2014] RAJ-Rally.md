# [POI 2014] RAJ-Rally

## 题目描述

给定一个 $n$ 个点 $m$ 条边的有向无环图，每条边长度都是 $1$。

请找到一个点，使得删掉这个点后剩余的图中的最长路径最短。

## 样例 #1

### 输入

```
6 5
1 3
1 4
3 6
3 4
4 5
```

### 输出

```
1 2
```

# 题解

## 作者：xcxcli (赞：40)

本题的要点是**有向无环图**，所以我们可以先拓扑排序，并$O(n)$求出以$u$为起点的最长路$ds_u$和以$u$为终点的最长路$dt_u$。

于是我们可以得到经过边$(u\to v)$的最长路为$dt_u+1+ds_v$。

把拓扑序小于$i$的节点的集合记为$A$，把拓扑序大于$i$的集合记为$B$。在删去$i$之后，可能是最长路的路径有：

$A\to A,B\to B,A\to B$

所以我们要维护$dt_u(u\in A),ds_v(v\in B),dt_u+1+ds_v(u\to v)$的最大值。

那么我们怎么得到上面的路径？我们可以从删除$i+1$的状态转移过来。下面是转移的过程：

一开始数据结构中有：$dt_{1,2,3},ds_{4,5,6,7},dt_2+1+ds_4,dt_3+1+ds_5$

![](https://cdn.luogu.com.cn/upload/image_hosting/977j9qwm.png)

删除$ds_4,dt_2+1+ds_4$，这时数据结构中数字的最大值就是图的最长路。

![](https://cdn.luogu.com.cn/upload/image_hosting/kd031fkn.png)

将$dt_4,dt_4+1+ds_6,dt_4+1+ds_5$加入数据结构，成功转移到下一个状态。

![](https://cdn.luogu.com.cn/upload/image_hosting/vt31kw3f.png)

所以我们可以将初始状态设为所有节点都在$B$，然后按拓扑序一个个加入到$A$中。

我们的数据结构要支持插入、删除、求最大值。所以我们可以用multiset，权值线段树。但我们还可以写**堆**。

我们可以用$a,b$两个堆，分别表示插入和删除的操作。当我们要取出堆顶元素时，可以比较两者的堆顶。若两者相同，则弹出两者。否则$a$的堆顶元素就是真正的堆顶元素。

```cpp
struct Queue{
	priority_queue<int>a,b;int sz;
	void push(int x){a.push(x),++sz;}
	void pop(int x){b.push(x),--sz;}
	int top(){
		while(!b.empty()&&a.top()==b.top())a.pop(),b.pop();
		return sz>0?a.top():-INF;
	}
}Q;//可删堆
```

下面我们来分析一下复杂度：初始化+拓扑排序$O(n+m)$，每个点和边都加入和删除过一次，总复杂度$O((n+m)\log(n+m))$。

~~比用multiset和权值线段树都跑得慢，果然是人弱自带大常数。~~

代码如下：

```cpp
#include<stdio.h>
#include<queue>
using namespace std;
int rd(){
	int k=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return f?k:-k;
}
const int N=500001;
int Max(int x,int y){return x>y?x:y;}
int Min(int x,int y){return x<y?x:y;}
struct E{int v,nxt;}e[N<<1]; 
struct Queue{
	priority_queue<int>a,b;
	void push(int x){a.push(x);}
	void pop(int x){b.push(x);}
	int top(){while(!b.empty()&&a.top()==b.top())a.pop(),b.pop();return a.top();}
}Q;//可删堆
int n,m,h[N],H[N],cnt,u,v,ds[N],dt[N],I[N],a[N],T,w,ans;queue<int>q;
void add(int u,int v,int*head){e[++cnt].v=v,e[cnt].nxt=head[u],head[u]=cnt;}
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	n=rd(),m=rd();
	for(int i=1;i<=m;++i)u=rd(),v=rd(),add(u,v,h),add(v,u,H),++I[v];
	for(int i=1;i<=n;++i)if(!I[i])q.push(i);
	while(!q.empty()){
		u=q.front(),q.pop(),a[++T]=u;
		for(int i=h[u];i;i=e[i].nxt)if(--I[v=e[i].v]==0)q.push(v); 
	}//拓扑排序
	for(int i=1;i<=n;++i){
		u=a[i];
		for(int i=h[u];i;i=e[i].nxt)v=e[i].v,dt[v]=Max(dt[v],dt[u]+1);
	}
	for(int i=n;i;--i){
		u=a[i];
		for(int i=H[u];i;i=e[i].nxt)v=e[i].v,ds[v]=Max(ds[v],ds[u]+1);
	}//求dt,ds
	for(int i=1;i<=n;++i)Q.push(ds[i]);
	ans=Q.top();
	for(int j=1;j<=n;++j){
		u=a[j],Q.pop(ds[u]);
		for(int i=H[u];i;i=e[i].nxt)Q.pop(dt[e[i].v]+ds[u]+1);//删除点和边
		T=Q.top();
		if(T<=ans)ans=T,w=u;//更新答案
		for(int i=h[u];i;i=e[i].nxt)Q.push(dt[u]+ds[e[i].v]+1);
		Q.push(dt[u]);//插入点和边
	}
	printf("%d %d\n",w,ans);
	return 0;
}
```

---

## 作者：ButterflyDew (赞：17)

来[Dew](https://www.cnblogs.com/ppprseter/p/9602576.html)的博客观看？

好神仙的一道题目！

一般来说一些删边删点的东西在统计统计信息什么的在图上都比较麻烦，我们应该找一找这个题的特殊性

很容易发现，重点在这个图是DAG。

有了DAG，我们可以$O(n)$求出单源点最长路什么的

然而这个图的最长路咋求呢？其实这个不难，统计通过每条边的最长路，取最大值就行了

设$diss_i$表示以$i$为开头的最长路，$dist_i$表示以$i$为结尾的最长路，为起点的反向跑一遍就可以得到

通过某条边$E=(u,v)$的最长路等价于$dist_u+diss_v+1$

topo图还有一个性质，按照topo序取出一部分连续的点作为$S$集，剩下的作为$T$集，则两个集合的相互连边只有一些$S$到$T$的

![](http://m.qpic.cn/psb?/V14VFGnz4fbJRr/byyAHvWRFVeoUGIBkDHICtEmxF.vDwp4w7XfQbe.wc4!/b/dFMBAAAAAAAA&bo=fwKBAX8CgQEDCSw!&rf=viewer_4)

为了方便，节点编号就是topo序，红边为$S$连向$T$的边

这启发我们按照拓扑序进行删点，我们先假设所有的点在$T$集，这样最长路就是$max diss_i$

我们按topo序拿走点，删掉有关贡献的边，统计答案，加入有关贡献的边，然后加入$S$集

这样说起来一点也不清楚，我们结合图形说明

![](http://m.qpic.cn/psb?/V14VFGnz4fbJRr/D0PFA37UFuITQxVwf1QiD4vlDG0LFmVPmYTc*6eQ5oI!/b/dEYBAAAAAAAA&bo=ZgJ9AWYCfQEDGTw!&rf=viewer_4)

现在正在删点4，看看有那些边可以作为答案。

首先$S$集合里面的边的最长长度，但不可以跨越两个集合即 $max_{i \in S} dist_i$，当然4的不算

然后跨越$S,T$集合的边即 $max_{E(u,v),u \in S,v \in T} dist_u+diss_v+1$

最后是集合$T$的，其实也差不多，不赘述了

我们首先在$T$集合的只有最后一种的答案，发现第一种的答案可以在把点扔进$S$的时候更新，而多余的$T$的答案可以在每次删点时删掉

第二种边其实也好统计，在点进去的时候出边都放进答案，当这个出边对的点进入$S$的时候把边的答案去掉

这么说可能还是有点抽象，还是拿4举个例子

第一步，删去$diss_4$

第二步，删去$diss_4+dist_{1/2/3}+1$这三个

第三步，统计最大值

第四步，加入$dist_4+diss_{6/7}+1$这两个

第五步，加入$dist_4$

关于这些操作，因为边权很小，所以我们可以拿权值线段树维护，也可以拿堆维护

其实思想上我说得也不算清楚，只是大概把过程讲清楚了

-------------
**Code:**
```cpp
#include <cstdio>
#include <vector>
const int N=1e6+10;
int head[N],to[N<<1],Next[N<<1],cnt;
void add(int u,int v)
{
    to[++cnt]=v,Next[cnt]=head[u],head[u]=cnt;
}
std::vector <int > To[N];
int q[N],n,m,in[N],topo[N],tot;
void toposort()
{
    int l=1,r=0;
    for(int i=1;i<=n;i++)
        if(!in[i]) topo[++tot]=i,q[++r]=i;
    while(l<=r)
    {
        int u=q[l++];
        for(int i=head[u];i;i=Next[i])
        {
            int v=to[i];
            --in[v];
            if(!in[v]) q[++r]=v,topo[++tot]=v;
        }
    }
}
int diss[N],dist[N];
#define ls ch[now][0]
#define rs ch[now][1]
int max(int x,int y){return x>y?x:y;}
void DP()
{
    for(int k=1;k<=n;k++)
    {
        int u=topo[k];
        for(int i=head[u];i;i=Next[i])
        {
            int v=to[i];
            dist[v]=max(dist[v],dist[u]+1);
        }
    }
    for(int k=n;k;k--)
    {
        int u=topo[k];
        for(int i=0;i<To[u].size();i++)
        {
            int v=To[u][i];
            diss[v]=max(diss[v],diss[u]+1);
        }
    }
}
void init()
{
    scanf("%d%d",&n,&m);
    for(int u,v,i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add(u,v),++in[v],To[v].push_back(u);
    }
    toposort();
    DP();
}
int ch[N<<2][2],sum[N<<2],root;
void change(int &now,int l,int r,int pos,int delta)
{
    if(!now) now=++tot;
    if(l==r) {sum[now]+=delta;return;}
    int mid=l+r>>1;
    if(pos<=mid) change(ls,l,mid,pos,delta);
    else change(rs,mid+1,r,pos,delta);
    sum[now]=sum[ls]+sum[rs];
}
int query(int now,int l,int r)
{
    if(l==r) return l;
    int mid=l+r>>1;
    if(sum[rs]) return query(rs,mid+1,r);
    else return query(ls,l,mid);
}
void work()
{
    tot=0;int mx,id,ans=0x7fffffff;
    for(int i=1;i<=n;i++)
        change(root,0,n,diss[i],1);
    for(int i=1;i<=n;i++)
    {
        int now=topo[i];
        change(root,0,n,diss[now],-1);
        for(int j=0;j<To[now].size();j++)
        {
            int v=To[now][j];
            change(root,0,n,diss[now]+dist[v]+1,-1);
        }
        if((mx=query(root,0,n))<ans) ans=mx,id=now;
        for(int j=head[now];j;j=Next[j])
        {
            int v=to[j];
            change(root,0,n,dist[now]+diss[v]+1,1);
        }
        change(root,0,n,dist[now],1);
    }
    printf("%d %d\n",id,ans);
}
int main()
{
    init(),work();
    return 0;
}

```

---

## 作者：LlLlCc (赞：11)

和其他题解有点不一样（~~更繁琐了~~）

------------
先用$topo$将每个点的拓扑序求出来，再建一个超级源点$S$，超级汇点$T$，正反建图跑两遍$topo$，求出$S_x,S_y$，分别表示源点到点$x$的最长路和点$x$到汇点的最长路

这样对于一条边$(x\rightarrow y)$，如果这条边是在最长链上，那么最长链的长度为$S_x+T_y+1$

同时，因为图是$DAG$，所以只会从拓扑序低的点走向拓扑序高的点，也就是说如果我们走了边$(x\rightarrow y)$，那么拓扑序在点$x$的拓扑序和点$y$的拓扑序之间的点，我们是不可能走的，就等于删除。所以我们可以用线段树来给这个区间标记打上$S_x+T_y+1$

但还有两种情况，删除点$x$后，最长链是在拓扑序小于或大于点$x$的一些点中，所以我们还要求出$1$到$x-1$中的最大$S_i$和$x+1$到$n$中的最大$T_i$

## code
```
#include<bits/stdc++.h>
#define maxn 2000005
using namespace std;
const int INF=1<<30;
int m,n,x,T_in[maxn],Q[maxn],L,R,Ans=INF,ans,id[maxn],Cnt,dis[2][maxn],S,T,q[maxn],Tt,nxt[maxn],son[maxn],lnk[maxn],tot,f[maxn],F[maxn];
bool vis[maxn];
struct lc{
	int L,R,x,k;
}tree[maxn];
struct Lc{
	int x,y;
}e[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;T_in[y]++;}
inline void Topo(){
	int hed=0,til=0;
	for (int i=1;i<=m;i++) add(e[i].x,e[i].y);
	for (int i=2;i<n;i++) add(1,i);
	Cnt=id[1]=vis[1]=Q[++til]=1;dis[0][1]=-1;
	while (hed<til){
		hed++;
		for (int i=lnk[Q[hed]];i;i=nxt[i])
		  if (!vis[son[i]]){
		  	T_in[son[i]]--;dis[0][son[i]]=max(dis[0][son[i]],dis[0][Q[hed]]+1);
		  	if (!T_in[son[i]]) Q[++til]=son[i],vis[son[i]]=1,id[son[i]]=++Cnt,q[++Tt]=son[i];
		  }
	}
	memset(lnk,0,sizeof lnk);memset(vis,0,sizeof vis);memset(T_in,0,sizeof T_in);
	hed=til=tot=0;
	for (int i=1;i<=m;i++) add(e[i].y,e[i].x);
	for (int i=2;i<n;i++) add(n,i);
	vis[n]=Q[++til]=n;dis[1][n]=-1;
	while (hed<til){
		hed++;
		for (int i=lnk[Q[hed]];i;i=nxt[i])
		  if (!vis[son[i]]){
		  	T_in[son[i]]--;dis[1][son[i]]=max(dis[1][son[i]],dis[1][Q[hed]]+1);
		  	if (!T_in[son[i]]) Q[++til]=son[i],vis[son[i]]=1;
		  }
	}
}
inline void down(int k){
	tree[k<<1].k=max(tree[k<<1].k,tree[k].k);
	tree[k<<1|1].k=max(tree[k<<1|1].k,tree[k].k);
	tree[k<<1].x=max(tree[k<<1].x,tree[k].k);
	tree[k<<1|1].x=max(tree[k<<1|1].x,tree[k].k);
	tree[k].k=0;
}
inline void Build(int k,int L,int R){
	tree[k].L=L,tree[k].R=R;
	if (L==R) return;
	int mid=L+R>>1;
	Build(k<<1,L,mid);Build(k<<1|1,mid+1,R);
}
inline void Change(int k){
	if (tree[k].L>=L&&tree[k].R<=R){
		tree[k].x=max(tree[k].x,x);
		tree[k].k=max(tree[k].k,x);
		return;
	}
	if (tree[k].k) down(k);
	int mid=tree[k].L+tree[k].R>>1;
	if (L<=mid) Change(k<<1);
	if (R>mid) Change(k<<1|1);
	tree[k].x=max(tree[k<<1].x,tree[k<<1|1].x);
}
inline int Get(int k,int x){
	if (tree[k].L==tree[k].R) return tree[k].x;
	if (tree[k].k) down(k);
	int mid=tree[k].L+tree[k].R>>1;
	if (x<=mid) return Get(k<<1,x);
	else return Get(k<<1|1,x);
}
int main(){
	n=read()+2,m=read();S=1,T=n;
	for (int i=1;i<=m;i++) e[i]=(Lc){read()+1,read()+1};
	Topo();Build(1,1,n);
	for (int i=2;i<=Tt;i++) f[i]=max(f[i-1],dis[0][q[i-1]]);
	for (int i=Tt-1;i;i--) F[i]=max(F[i+1],dis[1][q[i+1]]);
	for (int i=1;i<=m;i++){
		x=dis[0][e[i].x]+dis[1][e[i].y]+1;
		L=id[e[i].x]+1,R=id[e[i].y]-1;
		if (L<=R) Change(1);
	}
	for (int i=2;i<n;i++){
     	int Now=Get(1,id[i]);if (Now==INF) Now=0;
		if (max(f[id[i]-1],max(F[id[i]-1],Now))<Ans) Ans=max(f[id[i]-1],max(F[id[i]-1],Now)),ans=i;
    }
	printf("%d %d",ans-1,Ans);
	return 0;
}
```


---

## 作者：MloVtry (赞：4)

思路上和下面的dalao相同，但是仔细分析一下发现我只需要滋滋这样几个操作就可以了：

- 插入一个数
- 删除一个数
- 查询一个最大值

边长都是1，这代表着我们插入删除的值有一定的限度。

这就可以用权值线段树维护了。

代码
```
#include<bits/stdc++.h>
#define M 2000005
#define N 500005
using namespace std;
int f[N],g[N],d[N],n,m,id,ans;
int head[N],to[M],Next[M],e;
vector<int> h[N];
void buid(int u,int v)
{
	h[v].push_back(u);
	Next[++e]=head[u];head[u]=e;to[e]=v;d[v]++;
}
queue<int> q;
int top[N];
void Top_sort()
{
	for(int i=1;i<=n;++i) if(!d[i]) q.push(i);
	for(int i=1;i<=n;++i)
	{
		top[i]=q.front();q.pop();
		for(int k=head[top[i]];k;k=Next[k])
		{
			int j=to[k];
			d[j]--;
			if(!d[j]) q.push(j);
		}
	}
}
void Get_dis()
{
/*	for(int i=1;i<=n;++i) cout<<top[i]<<" ";
	cout<<endl;
	*/
	for(int i=n;i;--i)
	{
		int now=top[i];
		for(int i=head[now];i;i=Next[i])
		{
			int j=to[i];
			f[now]=max(f[now],f[j]+1);
		}
	}
	for(int i=1;i<=n;++i)
	{
		int now=top[i];
		for(int i=head[now];i;i=Next[i])
		{
			int j=to[i];
			g[j]=max(g[j],g[now]+1);
		}
	}
/*	for(int i=1;i<=n;++i) cout<<f[i]<<" ";
	cout<<endl;
	for(int i=1;i<=n;++i) cout<<g[i]<<" ";
	cout<<endl;*/
}
struct node
{
	int num,big;
}tre[N*4];
void update(int now,int lson,int rson)
{
	tre[now].big=max(tre[lson].big,tre[rson].big);
	tre[now].num=0;
	if(tre[lson].big==tre[now].big)  tre[now].num+=tre[lson].num;
	if(tre[rson].big==tre[now].big)  tre[now].num+=tre[rson].num;
}
void pop(int to,int l,int r,int now)
{
	if(l==r)
	{
		tre[now].num--;if(!tre[now].num) tre[now].big=0;
		return;
	}
	int mid=(l+r)>>1,lson=now<<1,rson=lson|1;
	if(to<=mid) pop(to,l,mid,lson);
	else pop(to,mid+1,r,rson);
	update(now,lson,rson);
}
void add(int to,int l,int r,int now)
{
	if(l==r)
	{
		tre[now].num++;tre[now].big=to;return;
	}
	int mid=(l+r)>>1,lson=now<<1,rson=lson|1;
	if(to<=mid) add(to,l,mid,lson);
	else add(to,mid+1,r,rson);
	update(now,lson,rson);
}
void Doit()
{
	ans=(1<<30);
	int s=n+1,t=n+2;
	for(int i=1;i<=n;++i)
	buid(s,i),buid(i,t),add(f[i],1,n+2,1);
	g[s]=f[t]=-1;
	
	for(int i=1;i<=n;++i)
    {
    	int now=top[i];
    	for(int j=0,zz=h[now].size();j<zz;++j)
    	{
    		int k=h[now][j];
    		pop(f[now]+g[k]+1,1,n+2,1);
		}
		int it=tre[1].big;
//		cout<<now<<" -- "<<it<<endl;
		if(it<ans) ans=it,id=now;
		for(int j=head[now];j;j=Next[j])
		{
			int k=to[j];
			add(f[k]+g[now]+1,1,n+2,1);
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v;scanf("%d%d",&u,&v);buid(u,v);
	}
	Top_sort();Get_dis();Doit();
	printf("%d %d\n",id,ans);
	return 0;
}
```

---

## 作者：skylee (赞：3)

建立超级源汇$S$和$T$，DP求出分别以$S$和$T$为源点的最长路$diss$和$dist$。

对于每条边$i$，设定一个权值$w_i=diss_{i.from}+dist_{i.to}-1$。

表示原图中包含这条边的从$S$到$T$的最长路。

然后按照拓扑序删点$x$，用堆维护不包含$x$的最长路长度。

然而一次性不能把所有边放进去，不然会MLE一个点（因为这个调了一个晚上）。

应该在换$x$的时候，把老$x$的出边重新加入，并将新$x$的入边删去。

注意开的数组不能太多，能合并的信息尽量合并，（比如所有边正反边用一个数组存，取值的时候用异或），不然把堆修改以后还是会MLE。

```cpp
#include<queue>
#include<cstdio>
#include<cctype>
#include<vector>
#include<ext/pb_ds/priority_queue.hpp>
inline int getint() {
    register char ch;
    while(!isdigit(ch=getchar()));
    register int x=ch^'0';
    while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
    return x;
}
const int inf=0x7fffffff;
const int V=500002,E=2000000;
struct Edge {
    int from,to;
};
Edge e[E];
int w[E];
int s,t;
int n,m;
std::vector<int> eids[V],eidt[V];
int inds[V]={0},indt[V]={0};
inline void add_edge(const int u,const int v,int *ind,std::vector<int> *eid,const int i) {
    eid[u].push_back(i);
    ind[v]++;
}
int diss[V]={0},dist[V]={0};
std::queue<int> top;
inline void Kahn(const int s,std::vector<int> *eid,int *dis,int *ind,const int op=0) {
    std::queue<int> q;
    q.push(s);
    while(!q.empty()) {
        int x=q.front();
        q.pop();
        if(op) top.push(x);
        for(register unsigned i=0;i<eid[x].size();i++) {
            int y=e[eid[x][i]].from^e[eid[x][i]].to^x;
            dis[y]=std::max(dis[y],dis[x]+1);
            if(!--ind[y]) q.push(y);
        }
    }
}
__gnu_pbds::priority_queue<int> q;
__gnu_pbds::priority_queue<int>::point_iterator p[E];
int v,ans=inf;
int cnt=0;
inline void solve() {
    while(!top.empty()) {
        int x=top.front();
        top.pop();
        for(register unsigned i=0;i<eidt[x].size();i++) {
            q.erase(p[eidt[x][i]]);
        }
        if(!q.empty()) {
            if((x!=s)&&(x!=t)&&(q.top()<ans)) {
                ans=q.top();
                v=x;
            }
        }
        for(register unsigned i=0;i<eids[x].size();i++) {
            p[eids[x][i]]=q.push(w[eids[x][i]]);
        }
    }
}
int main() {
    n=getint(),m=getint();
    s=0,t=n+1;
    for(register int i=1;i<=n;i++) {
        e[cnt].from=s,e[cnt].to=i;
        add_edge(s,i,inds,eids,cnt);
        add_edge(i,s,indt,eidt,cnt);
        cnt++;
    }
    for(register int i=0;i<m;i++) {
        int &u=e[cnt].from=getint(),&v=e[cnt].to=getint();
        add_edge(u,v,inds,eids,cnt);
        add_edge(v,u,indt,eidt,cnt);
        cnt++;
    }
    for(register int i=1;i<=n;i++) {
        e[cnt].from=i,e[cnt].to=t;
        add_edge(i,t,inds,eids,cnt);
        add_edge(t,i,indt,eidt,cnt);
        cnt++;
    }
    Kahn(s,eids,diss,inds,1);
    Kahn(t,eidt,dist,indt);
    for(register int i=0;i<cnt;i++) {
        w[i]=diss[e[i].from]+dist[e[i].to]-1;
    }
    solve();
    printf("%d %d\n",v,ans);
    return 0;
}
```

---

## 作者：AquaRio (赞：3)

突然发现所有的题解都没有用multiset。

其它题解都是用权值线段树，或者是堆解决的问题。

但是权值线段树码量太大，堆跑得很慢。

为什么不了解一下~~又好写又跑得快~~的multiset呢？

```cpp
// P3573.CPP

#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
const int M = 1e6 + 5;

int n, m;
multiset<int> S;

struct edge {
    int v, nxt;
} e[M << 1];

int head[2][N], cnt, in[N], q[N], l, r;
int dis[2][N];

inline void add(int u, int v, int t) {
    e[++cnt].v = v;
    e[cnt].nxt = head[t][u];
    head[t][u] = cnt;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        in[v]++;
        add(u, v, 0);
        add(v, u, 1);
    }
    int pos = 0, dismin = n, tmp;
    for (int i = 1; i <= n; i++)
        if (in[i] == 0)
            q[r++] = i;
    while (l < r) {
        int fr = q[l];
        l++;
        for (int i = head[0][fr]; i; i = e[i].nxt) {
            int to = e[i].v;
            in[to]--;
            if (!in[to])
                q[r++] = e[i].v;
        }
    }
    for (int k = 0; k <= n - 1; k++)
        for (int i = head[0][q[k]]; i; i = e[i].nxt)
            dis[0][e[i].v] = max(dis[0][e[i].v], dis[0][q[k]] + 1);
    for (int k = n - 1; k >= 0; k--)
        for (int i = head[1][q[k]]; i; i = e[i].nxt)
            dis[1][e[i].v] = max(dis[1][e[i].v], dis[1][q[k]] + 1);

    for (int i = 1; i <= n; i++)
        S.insert(dis[1][i]);
    for (int k = 0; k <= n - 1; k++) {
        S.erase(S.find(dis[1][q[k]]));
        for (int i = head[1][q[k]]; i; i = e[i].nxt)
            S.erase(S.find(dis[0][e[i].v] + dis[1][q[k]] + 1));
        tmp = *S.rbegin();
        if (tmp < dismin)
            dismin = tmp, pos = q[k];
        for (int i = head[0][q[k]]; i; i = e[i].nxt)
            S.insert(dis[0][q[k]] + dis[1][e[i].v] + 1);
        S.insert(dis[0][q[k]]);
    }
    cout << pos << " " << dismin << endl;
}

```

---

## 作者：Elma_ (赞：2)

> 给定一个 $n$ 个点 $m$ 条边的 DAG，每条边长度均为 $1$，找到一个点使得删掉这个点后图中的最长路径最短。

好题，好题。看到 DAG，首先想到拓扑排序。先对 DAG 拓扑排序一遍，然后求出分别以 $i$ 号点为开头与结尾的最长路径 $S_i$ 和 $T_i$。那么对于原图中的一条边 $u \to v$，经过这条边的最长路径的长度为 $S_u + T_v + 1$。

然后考虑如下性质：对于一个点 $i$，设拓扑序在其之前的点点集为 $S$，拓扑序在其之后的点点集为 $T$。显然对于任意 $u \in S$，以 $u$ 为结尾过点 $i$；同理，对于任意 $v \in T$，以 $v$ 为开头的最长路径也一定不经过 $i$。

于是我们按照拓扑序枚举 $i$，考虑如何维护删掉点 $i$ 后的最长路。初始时所有点均视为在 $T$ 中，对于 $S$ 和 $T$ 中的最长路，因为有刚才的那条性质，所以在 $i$ 移出 $T$ 的时候删除 $T_i$，加入 $S$ 的时候插入 $S_i$ 即可。然后考虑如何维护 $S \to T$ 的最长路，仿照上面的做法，当 $i$ 移出 $T$ 时删除指向 $i$ 的所有边，当 $i$ 进入 $S$ 的时候插入 $i$ 的所有出边即可。

因此我们需要一个数据结构，支持插入一个数，删除一个数，查询最大值。可以使用线段树，multiset 或是懒惰删除的堆。代码中写的是懒惰删除的堆，时间复杂度为 $O((n+m)\log(n+m))$。

```cpp
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
#define pii pair<int, int>
#define mp make_pair
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 5e5 + 5;
const int maxm = 255;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f3f3f3f;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

struct node {
	int nxt, to;
} edge[maxn << 1], edge1[maxn << 1];
int n, m, tot, tot1, cnt, tmp, head[maxn], head1[maxn];
int ans, len, deg[maxn], a[maxn], ds[maxn], dt[maxn];

struct Queue {
	priority_queue <int> a, b;
	inline void push(int x) {
		a.push(x);
	}
	inline void pop(int x) {
		b.push(x);
	}
	inline int top() {
		while (!b.empty() && a.top() == b.top()) a.pop(), b.pop();
		return a.top();
	}
} Q;
queue <int> q;

inline void addedge(int u, int v) {
	edge[++tot] = (node){ head[u], v }, head[u] = tot;
}
inline void addedge1(int u, int v) {
	edge1[++tot1] = (node){ head1[u], v }, head1[u] = tot1;
}

signed main(void) {
	n = read(), m = read();
	for (int i = 1, u, v;i <= m;i++) {
		u = read(), v = read();
		addedge(u, v), addedge1(v, u), deg[v]++;
	} 
	for (int i = 1;i <= n;i++) if (!deg[i]) a[++cnt] = i;
	for (int i = 1, u;i <= cnt;i++) {
		u = a[i];
		for (int p = head[u];p;p = edge[p].nxt) {
			int v = edge[p].to;
			if (!(--deg[v])) a[++cnt] = v;
		}
	}
	for (int i = 1, u;i <= n;i++) {
		u = a[i];
		for (int p = head[u];p;p = edge[p].nxt) {
			int v = edge[p].to;
			ds[v] = max(ds[v], ds[u] + 1);
		}
	}
	for (int i = n, u;i >= 1;i--) {
		u = a[i];
		for (int p = head1[u];p;p = edge1[p].nxt) {
			int v = edge1[p].to;
			dt[v] = max(dt[v], dt[u] + 1);
		}
	}
	for (int i = 1;i <= n;i++) Q.push(dt[i]);
	len = Q.top();
	for (int i = 1, u;i <= n;i++) {
		u = a[i], Q.pop(dt[u]);
		for (int p = head1[u];p;p = edge1[p].nxt) {
			int v = edge1[p].to;
			Q.pop(ds[v] + dt[u] + 1);
		}
		tmp = Q.top();
		if (tmp <= len) len = tmp, ans = u;
		for (int p = head[u];p;p = edge[p].nxt) {
			int v = edge[p].to;
			Q.push(ds[u] + dt[v] + 1);
		}
		Q.push(ds[u]);
	}
	printf("%lld %lld\n", ans, len);
	return 0;   
}
```


---

## 作者：RemiliaScar1et (赞：2)

## P3573 [POI2014]RAJ-Rally

首先我们考虑求出以某个点为 起点/终点 的最长路径长度。

由于这是一个 DAG 且边权固定为 1 ，我们可以拓补排序之后 DP。

设 $diss(i)$ 为以 $i$ 为起点的最长路径长度，考虑状态来源。这个状态会被所有有 $(u,i)$ 存在的点更新到，即 $diss(i)=\max\limits_{(u,i)\in E}\{diss(u)+1\}$ 。我们在反图上跑刷表法。用当前的 $x$ 更新 $y$。

设 $dist(i)$ 为以 $i$ 为终点的最长路径长度，和上面几乎一样，在正图上面跑刷表法即可。

现在我们要考虑删点的问题。显然我们无法立即知道哪个点最优。所以我们试图遍历每个点，把每个点都删除一遍。此时我们需要快速得出删点之后的最长路。

首先我们要知道一个拓补图的性质，在拓补序列的两个不相交区间 $A=[l_1,r_1],B=[l_2,r_2](r_1<l_2)$ 之间，只会存在边 $(u,v),(u\in A,v\in B)$。这是拓补排序的过程所决定的。

而我们若是删除一个点 $x$ ，相当于将拓补序列分成了两部分 $A,B$，那么最长路径有三种情况：在 $A$ 内部，在 $B$ 内部，从 $A$ 到 $B$。我们需要维护 $A,B$ 两个集合以及三种情况的最大值。

具体的说：
- 在 $A$ 内部的最长路我们维护它的终点在 $A$ 内部，也就是 $dist(i),i\in A$；
- 跨越 $A,B$ 之间的最长路我们维护在跨越 $A,B$ 集合之间的边 $(u,v),u\in A,v\in B$ 上的最长路，即 $dist(u)+1+diss(v)$ 。
- 在 $B$ 内的最长路我们维护 $diss(i),i\in B$ 即可。

附示意图：

[![](https://pic.imgdb.cn/item/61246cbd44eaada739a7e1d8.png)](https://pic.imgdb.cn/item/61246cbd44eaada739a7e1d8.png)

现在我们来正式删除点 $x$。这个点上次删除时应在 $B$ 集合中。

首先我们要把经过 $A$ 中的点连向它的边上的最长路全部删去，同时要将以它为起点的最长路删去。

然后直接查询全图的最长路。打擂台记录最小值。

现在我们要把这个点放回去，我们应该把它放到 $A$ 集合。先将以它为终点的最长路放进去，然后再把所有经过它出边的最长路也放进去。

综上，我们需要一个能够支持插入、删除、查询全局最大的数据结构。multiset线段树懒惰删除堆都是可以的，这里使用的懒惰删除堆

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=5e5+10,M=4e6+10,INF=1e8;
int n,m;
int head[N],head1[N],ver[M],nxt[M],edg[M],tot=0;
void add(int x,int y,int w)
{
	ver[++tot]=y; edg[tot]=w; nxt[tot]=head[x]; head[x]=tot;
}
void add1(int x,int y,int w)
{
	ver[++tot]=y; edg[tot]=w; nxt[tot]=head1[x]; head1[x]=tot;
}
int ind[N];
int diss[N],dist[N];
queue<int> q;
int seq[N],id[N];

struct Heap
{
	priority_queue<int> a,b;
	int size_=0;
	void push(int x){a.push(x);++size_;}
	void pop(int x){b.push(x);--size_;}
	int top()
	{
		while(b.size()&&a.top()==b.top()) a.pop(),b.pop();
		return size_<=0?-INF:a.top();
	}
} H;//懒惰删除堆

void topo()
{
	int cnt=0;
	while(q.size())
	{
		int x=q.front();
		q.pop();
		seq[++cnt]=x;id[x]=cnt;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=ver[i];
			ind[y]--;
			if(!ind[y]) q.push(y);
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y,1);add1(y,x,1);
		ind[y]++;
	}
	for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
	topo();
	for(int i=1;i<=n;i++)
	{
		int x=seq[i];
		for(int j=head[x];j;j=nxt[j])
		{
			int y=ver[j];
			dist[y]=max(dist[y],dist[x]+1);
		}
	}
	for(int i=n;i>=1;i--)
	{
		int x=seq[i];
		for(int j=head1[x];j;j=nxt[j])
		{
			int y=ver[j];
			diss[y]=max(diss[y],diss[x]+1);
		}
	}
	for(int i=1;i<=n;i++) H.push(diss[i]);
	int ans=H.top(),anx;
	for(int i=1;i<=n;i++)
	{
		int x=seq[i]; H.pop(diss[x]);
		for(int j=head1[x];j;j=nxt[j])
			H.pop(dist[ver[j]]+diss[x]+1);
		int tmp=H.top();
		if(tmp<ans) ans=tmp,anx=x;
		for(int j=head[x];j;j=nxt[j])
			H.push(dist[x]+diss[ver[j]]+1);
		H.push(dist[x]);
	}
	printf("%d %d",anx,ans);
	return 0;
}
```

---

## 作者：tommymio (赞：1)

性质题。$\text{DAG 0/1}$ 最值路径这种类型，一般想到拓扑序。

根据拓扑排序的过程，我们可以推出这样一条性质：在拓扑序列中取出两个不相交的区间 $[L_1,R_1],[L_2,R_2]$，其中 $R_1 < L_2$，$\forall i\in[L_1,R_1],j\in[L_2,R_2]$，只会有边 $i\to j$。这条性质有什么用呢？

想一想，枚举被删去的节点 $z$，设任意点 $i$ 的拓扑序为 $seq_i$，拓扑序 $i$ 对应的点为 $rev_i$。将其删去后，原拓扑序列被划分为两部分：$[1,seq_z),(seq_z,n]$。而我们需要快速计算从原图 $G$ 中删去点 $z$ 的最长路。

这里需要一个上述性质的推论，删去点 $z$ 后，最长路一定经过 $rev_x\to rev_y(x\in[1,seq_z),y\in(seq_z,n])$ 这条边。对于这个推论可以根据上述性质使用反证法证明，这里留给读者自行证明。值得注意的是，此推论正确性仅建立在原图 $G$ 边权相同的情况下。

预处理出从某个点到点 $x$ 的最长路 $f_x$，从点 $x$ 到某个点的最长路 $g_x$ 后，可以使用上述推论得到删去点 $z$ 后的最长路为 $\max\limits_{x\in[1,seq_z),y\in(seq_z,n],(rev_x,rev_y)\in E} f_{rev_x}+g_{rev_y}+1$。考虑快速计算这个式子，由于 $x$ 的右边界单调增大，我们可以按拓扑序枚举点 $z$，在 $x$ 的右边界增大时加入新的 $(rev_x,rev_y)$ 的值。查询时只查询 $seq_z<y\leq n$ 的 $y$ 值相关的最大值。

在求不定源最短路的时候，可以设立超级源点和超级汇点。上述操作使用线段树或者懒惰删除的堆均可实现。其中前者时间复杂度为 $O((n+m) \log n)$，后者时间复杂度为 $O((n+m) \log (n+m))$。

```cpp
#include<cstdio>
#include<queue>
#define ls p<<1
#define rs p<<1|1
int num=0,cnt[2];
int mx[2000005];
int h[2][500005],to[2][1000005],ver[2][1000005],w[2][1000005],du[2][500005];
int dis[2][500005],seq[500005],rev[500005],f[500005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline void add(int id,int x,int y,int z=1) {
	++du[id][y];
	to[id][++cnt[id]]=y;
	ver[id][cnt[id]]=h[id][x];
	w[id][cnt[id]]=z;
	h[id][x]=cnt[id];
}
inline void topo(int u,int id) {
	std::queue<int> Q; num=0;
	Q.push(u); dis[id][u]=0;
	while(Q.size()) {
		int x=Q.front(); Q.pop();
		seq[++num]=x; rev[x]=num;
		for(register int i=h[id][x];i;i=ver[id][i]) {
			int y=to[id][i];
			dis[id][y]=max(dis[id][y],dis[id][x]+w[id][i]);
			if(!(--du[id][y])) Q.push(y);
		} 
	}
}
inline void change(int p,int l,int r,int x,int val) {
	if(l==r) {mx[p]=max(mx[p],val); return;}
	int mid=l+r>>1;
	if(x<=mid) change(ls,l,mid,x,val);
	else change(rs,mid+1,r,x,val);
	mx[p]=max(mx[ls],mx[rs]);
}
inline int ask(int p,int l,int r,int L,int R) {
	if(L<=l&&r<=R) return mx[p];
	int mid=l+r>>1,res=0;
	if(L<=mid) res=max(res,ask(ls,l,mid,L,R));
	if(R>mid) res=max(res,ask(rs,mid+1,r,L,R));
	return res;
}
int main() {
	int n=read(),m=read(),S=n+1,T=n+2,res=0;
	for(register int i=1;i<=n;++i) {
		add(0,S,i,0); add(0,i,T,0);
		add(1,i,S,0); add(1,T,i,0);
	}
	for(register int i=1;i<=m;++i) {int x=read(),y=read();add(0,x,y);add(1,y,x);}
	topo(T,1); topo(S,0);
	f[0]=n+m;
	for(register int i=1;i<=num-2;++i) {
		int x=seq[i];
		for(register int k=h[0][x];k;k=ver[0][k]) {
			int y=to[0][k];
			change(1,1,num,rev[y],dis[0][x]+dis[1][y]+w[0][k]);
		}
		f[i+1]=ask(1,1,num,i+2,num);
		if(f[res]>f[i+1]) {res=i+1;}
	}
	printf("%d %d\n",seq[res],f[res]);
	return 0;
}
```

---

## 作者：No_wonder (赞：1)

这道题的确是神仙题，我被正图反图绕晕了好久。这篇题解中对于正图反图的说明可能会存在一些错误，希望读者指出。

题意简述：给你一个DAG，删除一个节点后使最长路径最短，求这个节点与路径长度。

因为DAG优秀的性质，我们可以用拓扑排序快速求出最长路，同时我们建立反图，一并求出以一个节点为起点和终点的最长路。

有了上面所有的预处理，我们已经能求出没删点时的最长路，现在我们来考虑删点。

我们是要求最大值，所以我们的数据结构要求支持删除，支持修改，支持求最值，可删堆是一个好的选择。当然，你也可以用权值线段树与multiset。

那么操作就很简单了，只需要枚举每一个节点并删除，弹出和这个节点有关的路径，记录这时的最大值。然后再把这个节点放回去就可以。

我们来想想弹出一个节点时，影响到的路径究竟是什么。

我们想象出超级原点与超级汇点，那么$dis1,dis2$分别就是到一个点u到超级原点与超级汇点的距离

删除这个点，影响的就是该节点上一个节点经过该节点走到这个节点下一个节点的这条路径。

该节点的上一个节点就是反图中的$e[u].to$，所以更改的就是$dis2[u]+dis1[e[u].to]+1$

在添加节点时，我们就要添加的是前面的点到达该节点后经过边走到该节点相邻节点的路径。

就是正图中的$dis1[u]+dis2[e[u].to]+1$

那么删除与添加操作也明确了，就是
```cpp
for(ri i=1;i<=n;i++)	p.push(dis2[i]);	
	ans=p.top();
	for(ri i=1;i<=n;i++)															
	{
		int u=tp[i];																//删除节点 
		p.pop(dis2[u]);
		for(ri j=head[u]; j; j=e[j].next)	if(e[j].dist==-1)	p.pop(dis2[u]+dis1[e[j].to]+1);
		int tmp=p.top();
		if(tmp<ans)	ans=tmp,key=u;
		for(ri j=head[u]; j; j=e[j].next)	if(e[j].dist==1)	p.push(dis1[u]+dis2[e[j].to]+1);
		p.push(dis1[u]);
	}
```


如果还是不懂，我这里添加了一幅图片进行说明

![](https://cdn.luogu.com.cn/upload/image_hosting/o6sifbgn.png)

图中并没有给出超级原点与超级汇点，不过不妨碍理解。

我们删除4，实际上删除的是1->4->5与3->4->5，1->3->4->5这三条路径。1,3都是反图中4直接链接的节点，他们为终点到超级原点的距离+4为起点到超级汇点的距离构成一条路径。

添加进4的时候，添加回来的就是正图中超级原点到4的距离+正图中与4直接相连的5到超级汇点的距离。

如果有了上面的说明还存在疑惑，欢迎私信询问我。

这道来自POI的题目就可以解决啦~~

完整代码
```cpp
#include<bits/stdc++.h>
#include<queue>
#define ri register int
using namespace std;
struct Edge{
	int next;
	int to;
	int dist;
}e[2000200];


struct de_heap{					//可删堆 
	priority_queue<int> a,b;
	void push(int x){a.push(x);}
	void pop(int x){b.push(x);}
	int top()
	{
		while(!b.empty() && a.top()==b.top())	
		a.pop(),b.pop();
		return a.top();
	}
}p;


int n,m,ans,key;


int head[500050],cnt;
void add_edge(int from,int to,int dist)
{
	e[++cnt].to=to;
	e[cnt].next=head[from];
	e[cnt].dist=dist;
	head[from]=cnt;
}


int in[500050],tp[500050],sum;						//拓扑排序求最长路 
queue<int> q;
void tpsort()
{
	for(ri i=1;i<=n;i++)
	if(!in[i])	q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		tp[++sum]=u;
		q.pop();
		for(ri i=head[u]; i; i=e[i].next)
		if(e[i].dist==1)
		{
			in[e[i].to]--;
			if(in[e[i].to]==0)	q.push(e[i].to);
		}
	}
} 

//这里这么bfs的缘故是因为拓扑排序求最长路，一定是从拓扑序低的地方向高的地方转移，所以每次只需要扩展一次。 
int dis1[500050],dis2[500050];					 
void bfs1(int now)			
{
	for(ri i=head[now]; i; i=e[i].next)
		if(e[i].dist==1)	dis1[e[i].to]=max(dis1[e[i].to],dis1[now]+1);
}
void bfs2(int now)
{
	for(ri i=head[now]; i; i=e[i].next)
		if(e[i].dist==-1)	dis2[e[i].to]=max(dis2[e[i].to],dis2[now]+1);
}


int main()
{
	scanf("%d%d",&n,&m);
	for(ri i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v,1);				//1代表正图，-1代表反图
		add_edge(v,u,-1);
		in[v]++;
	}
	tpsort();
	//for(ri i=1;i<=n;i++)
	//printf("%d ",tp[i]);
	for(ri i=1;i<=sum;i++)
	bfs1(tp[i]);
	for(ri i=sum;i>=1;i--)
	bfs2(tp[i]); 
	//for(ri i=1;i<=sum;i++)
	//printf("%d %d\n",dis1[i],dis2[i]);
	for(ri i=1;i<=n;i++)	p.push(dis2[i]);	
	ans=p.top();
	for(ri i=1;i<=n;i++)															
	{
		int u=tp[i];																//删除节点 
		p.pop(dis2[u]);
		for(ri j=head[u]; j; j=e[j].next)	if(e[j].dist==-1)	p.pop(dis2[u]+dis1[e[j].to]+1);	
		int tmp=p.top();
		if(tmp<ans)	ans=tmp,key=u;
		for(ri j=head[u]; j; j=e[j].next)	if(e[j].dist==1)	p.push(dis1[u]+dis2[e[j].to]+1);
		p.push(dis1[u]);
	}
	printf("%d %d",key,ans);
} 
```


---

## 作者：shiroi (赞：1)

### Description

给定一个 $N$ 个点 $M$ 条边的有向无环图，每条边长度都是1。

请找到一个点，使得删掉这个点后剩余的图中的最长路径最短。

### Solution

一道思路好题。

题目中给出的图是一个DAG图，所以一般的做法考虑拓扑排序之后dp求出最长路径。

对于本题，可以建立超级源点和超级汇点，最长路径即为S到T的最长路。

考虑进行转移。对于图上的任意一条边  $(u,v)$ ，经过这条边的最长路即为源点S到u的最长加上该条边的边权和v到T的最长距离。

由此图的最长路径就被转化为图上所有边边权的最大值，现在可以利用数据结构维护。需要支持插入、删除和最大值查询。可以手写一个支持删除的堆或者直接写线段树。

定义 $f[i][0]$ 为源点到i的最长距离，$f[i][1]$ 为i到汇点的距离，边  $(u,v)$  的贡献即为 $f[u][0]+f[v][1]$ 。具体实现见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0,f=1,c=getchar();
	while(c<48) c=='-'&&(f=-1),c=getchar();
	while(c>47) x=x*10+c-'0',c=getchar();
	return x*f;
}

const int MAXN = 500005;
const int INF = 0x7fffffff;
struct Seg {int l,r,mx,num;} t[MAXN<<2];
std::vector<int> G[MAXN],adj[MAXN];
int topo[MAXN],ind[MAXN],visit[MAXN],f[MAXN][2];
int n,m,tp,ans,mxl=INF;

inline void addedge(int u,int v)
{G[u].push_back(v);}

inline void insert(int u,int v)
{adj[u].push_back(v);}

inline void topost()
{
	int head=1,rear=n; stack<int>st;
	for(int i=head; i<=rear; i++)
		if(!ind[i]) st.push(i),topo[++tp]=i;
	while(!st.empty())
	{
		int x=st.top(); st.pop(); visit[x]=0;
		for(int &y : G[x])
			if(!(--ind[y])) st.push(y),topo[++tp]=y;
	}
}

void dfs()
{
	for(int i=1; i<=n; i++)
	{
		int x=topo[i]; f[x][0]=max(f[x][0],1);
		for(int &y : G[x])
			f[y][0]=max(f[y][0],f[x][0]+1);
	}
	for(int i=n; i>=1; i--)
	{
		int x=topo[i]; f[x][1]=max(f[x][1],1);
		for(int &y : G[x])
			f[x][1]=max(f[y][1]+1,f[x][1]);
	}
}

inline void pushup(int x)
{t[x].mx=max(t[x<<1].mx,t[x<<1|1].mx);}

void build(int x,int l,int r)
{
	t[x].l=l,t[x].r=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}

inline void puttag(int x,int l,int r,int k)
{
	t[x].num+=k; t[x].mx=t[x].num>0? l : -1;
	t[x].num=max(t[x].num,0);
}

void update(int x,int pos,int k)
{
	int l=t[x].l,r=t[x].r;
	if(l==r) {puttag(x,l,r,k); return;}
	int mid=(l+r)>>1;
	if(pos<=mid) update(x<<1,pos,k);
	if(pos>mid)  update(x<<1|1,pos,k);
	pushup(x);
}

int query(int x,int ql,int qr)
{
	int l=t[x].l,r=t[x].r;
	if(ql<=l && qr>=r) return t[x].mx;
	int mid=(l+r)>>1,res=-INF;
	if(ql<=mid) res=max(res,query(x<<1,ql,qr));
	if(qr>mid)  res=max(res,query(x<<1|1,ql,qr));
	return res;
}

int main(int argc, char const *argv[])
{
	n=read(); m=read();
	int x,y,k;
	for(int i=1; i<=m; ++i)
	{
		x=read(); y=read(); ind[y]++;
		addedge(x,y); insert(y,x);
	}
	topost(); dfs(); build(1,0,n);
	for(int i=1; i<=n; i++)
		update(1,f[i][1],1);
	for(int i=1; i<=n; i++)
	{
		int x=topo[i]; update(1,f[x][1],-1);
		for(int &y : adj[x])
			update(1,f[y][0]+f[x][1],-1);
		if(query(1,0,n)<mxl)
			mxl=query(1,0,n),ans=x;
		update(1,f[x][0],1);
		for(int &y : G[x])
			update(1,f[x][0]+f[y][1],1);
	}
	printf("%d %d\n",ans,mxl-1);
	return 0;
}
```





---

