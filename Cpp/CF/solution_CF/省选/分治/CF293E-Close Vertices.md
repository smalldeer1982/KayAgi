# Close Vertices

## 题目描述

You've got a weighted tree, consisting of $ n $ vertices. Each edge has a non-negative weight. The length of the path between any two vertices of the tree is the number of edges in the path. The weight of the path is the total weight of all edges it contains.

Two vertices are close if there exists a path of length at most $l$ between them and a path of weight at most $w$ between them. Count the number of pairs of vertices $v,u(v<u)$, such that vertices $v$ and $u$ are close.

## 样例 #1

### 输入

```
4 4 6
1 3
1 4
1 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 2 17
1 3
2 5
2 13
1 6
5 9
```

### 输出

```
9
```

# 题解

## 作者：da32s1da (赞：8)

考虑只有路径长度的限制怎么做。

~~P4178~~。

```
sort(sth+1,sth+Cnt+1);
while(l<r){
	if(sth[l]+sth[r]<=k){
    	ret+=r-l;
		l++;
	}else{
		r--;
	}
}
return ret;
```

加上路径边数的限制呢？

~~很自然地~~想到要在``ret+=r-l``这个地方**再筛选**出符合条件的路径。

于是用**树状数组**来做。

将dis排序，``if``里面是``dis``的限制，然后``ret``加上 ``≤ l-len[l]``的答案即可。

正确性显然。

这一段修改后的代码
```
//k是限制的长度，m是限制的边数
sort(sth+1,sth+Cnt+1,mmp);//按dis排序
for(int i=1;i<=Cnt;i++)s.insert(sth[i].dep+1);
//插入dep
int l=1,r=Cnt;LL res=0;
while(l<r){
	if(sth[l].dis+sth[r].dis<=k){//限制长度
		s.erase(sth[l].dep+1);//去掉自己
		res+=s.Ans(m-sth[l].dep+1);//累加答案
		l++;
	}else{
		s.erase(sth[r].dep+1);
		r--;
	}
}
s.erase(sth[l].dep+1);//注意最后去掉l=r的dep
return res;
```

那为什么需要+1呢？

~~因为树状数组操作起来方便，~~因为插入删除时可能遇到0的情况，会TLE。而查询的时候 两条路径边数之和等于m也是要算进答案的，若遇到0的情况，说明两条路径边数之和为m+1，此时不用统计答案。

完整代码：
```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+50;
typedef long long LL;
int to[N<<1],las[N<<1],fir[N],ds[N<<1],cnt;
inline void add_edge(int u,int v,int a){
	to[++cnt]=v;las[cnt]=fir[u];fir[u]=cnt;ds[cnt]=a;
	to[++cnt]=u;las[cnt]=fir[v];fir[v]=cnt;ds[cnt]=a;
}
inline int max(int u,int v){return u>v?u:v;}
inline int min(int u,int v){return u<v?u:v;}
int n,m,k,x,y;
int f[N],dis[N],dep[N],siz[N],vis[N];
int Cnt,rot,sum;
LL ans;
struct node{
	int dis,dep;
}sth[N];
struct Tree{
	int f[N];
	void insert(int u){
		if(u==0)return;
		for(int i=u;i<=n+1;i+=i&-i)f[i]++;
	}
	void erase(int u){
		if(u==0)return;
		for(int i=u;i<=n+1;i+=i&-i)f[i]--;
	}
	int Ans(int u){
		if(u<=0)return 0;
		int ret=0;
		for(int i=u;i;i&=i-1)ret+=f[i];
		return ret;
	}
}s;
bool mmp(const node &u,const node &v){
	return u.dis<v.dis;
}
void grot(int u,int v){
	siz[u]=1;f[u]=0;
	for(int i=fir[u];i;i=las[i])
	if(to[i]!=v&&!vis[to[i]]){
		grot(to[i],u);
		siz[u]+=siz[to[i]];
		f[u]=max(f[u],siz[to[i]]);
	}
	f[u]=max(f[u],sum-siz[u]);
	if(f[u]<f[rot])rot=u;
}
void gsth(int u,int v){
	sth[++Cnt]=(node){dis[u],dep[u]};
	for(int i=fir[u];i;i=las[i])
	if(to[i]!=v&&!vis[to[i]]){
		dis[to[i]]=dis[u]+ds[i];
		dep[to[i]]=dep[u]+1;
		gsth(to[i],u);
	}
}
LL calc(int u,int Dis,int Dep){
	Cnt=0;
	dis[u]=Dis;dep[u]=Dep;
	gsth(u,0);
	sort(sth+1,sth+Cnt+1,mmp);
	for(int i=1;i<=Cnt;i++)s.insert(sth[i].dep+1);
	int l=1,r=Cnt;LL res=0;
	while(l<r){
		if(sth[l].dis+sth[r].dis<=k){
			s.erase(sth[l].dep+1);
			res+=s.Ans(m-sth[l].dep+1);
			l++;
		}else{
			s.erase(sth[r].dep+1);
			r--;
		}
	}
	s.erase(sth[l].dep+1);
	return res;
}
void solve(int u){
	ans+=calc(u,0,0);vis[u]=1;
	for(int i=fir[u];i;i=las[i])
	if(!vis[to[i]]){
		ans-=calc(to[i],ds[i],1);
		rot=0;sum=siz[to[i]];
		grot(to[i],0);
		solve(rot);
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=2;i<=n;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,i,y);
	}
	f[0]=sum=n;
	grot(1,0);
	solve(rot);
	printf("%I64d\n",ans);
}
```

---

## 作者：KiDDOwithTopTree (赞：5)

题目在这：[传送门](https://www.luogu.com.cn/problem/CF293E)。

~~CF 题的题解真的那么少吗？~~

说实话这题可能只有紫题难度。

这一题和 [P4178](https://www.luogu.com.cn/problem/P4178) 很像。但是 P4178 的限制只是一维的，而这一题却有 $l$ 和 $w$ 两维的限制。

题解区各位大佬们的代码都是先排序再用树状数组来解决的。

但是我好菜啊 QAQ，愣是没有想通怎么样排序解决，就连 P4178 都是用 点分治+平衡树 的方法解决的。

肿么办呢？

解决二维偏序其实还有一个好东西：**树套树**。

~~就是会多一只 log 而已…~~

点分治可以套上各种数据结构，所以我们可以用 点分治+树套树 来写这一题。

我用的树套树是 **树状数组+FHQ_Treap**。树状数组 是存长度那一维，FHQ_Treap 是存边权那一维。码量很小，可以放心食用。

同样因为会遇到 0 的情况，长度要统一进行 +1。

初始时要在 $(1,0)$ 的位置上加入一个数，因为长度为 0，边权为 0 的点有一个（根）。

关于删除，我用了**惰性删除**，即为 $root$ 标为 0 视为删除。如果不想用惰性删除的可以用**垃圾回收**。这些方法都是为了节省空间的。

因为变量有许多重名。所以我用结构体封装了一下。

代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
const int N=1e5+10;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int n,l,w;
struct fhq_in_bit{
	struct fhq_treap{
		long long size;
		int lson,rson;
		int val,key;
	};
	fhq_treap fhq[40*N];
	int root[N];
	int cnt;
	inline void pushup(int pos){
		fhq[pos].size=fhq[fhq[pos].lson].size+fhq[fhq[pos].rson].size+1;
	}
	inline int newnode(int val){
		++cnt;
		fhq[cnt].lson=fhq[cnt].rson=0;//因为是惰性删除，所以原来的节点可能还有以前所存的lson和rson，要标为0
		fhq[cnt].key=rand();
		fhq[cnt].val=val;
		fhq[cnt].size=1;
		return cnt;
	}
	void split(int pos,int val,int &x,int &y){
		if(!pos){
			x=y=0;
			return ;
		}
		if(fhq[pos].val<=val){
			x=pos;
			split(fhq[x].rson,val,fhq[x].rson,y);
		}
		else{
			y=pos;
			split(fhq[y].lson,val,x,fhq[y].lson);
		}
		pushup(pos);
	}
	int merge(int x,int y){
		if(!x||!y)
			return x|y;
		if(fhq[x].key>fhq[y].key){
			fhq[x].rson=merge(fhq[x].rson,y);
			pushup(x);
			return x;
		}
		else{
			fhq[y].lson=merge(x,fhq[y].lson);
			pushup(y);
			return y;
		}
	}
	inline void fhq_ins(int &rt,int val){
		int x,y;
		split(rt,val,x,y);
		rt=merge(merge(x,newnode(val)),y);
	}
	inline long long fhq_query(int &rt,int val){
		int x,y;
		split(rt,val,x,y);
		long long ans=fhq[x].size;
		rt=merge(x,y);
		return ans;
	}
/*-----------以上为平衡树部分------------*/
	inline int lowbit(int x){
		return x&-x;
	}
	inline void bit_ins(int pos,int val){
		for(int i=pos;i<=n+1;i+=lowbit(i))
			fhq_ins(root[i],val);
	}
	inline long long bit_query(int r,int val){
		long long ans=0;
		for(int i=r;i;i-=lowbit(i))
			ans+=fhq_query(root[i],val);
		return ans;
	}
/*-----------以上为树状数组部分------------*/
	inline void clear(int pos){
		for(int i=pos;i<=n+1;i+=lowbit(i))
			root[i]=0;//惰性删除，root标为0即为删除
	}
};
struct edge{
	int from,to;
	int val;
	int nxt;
};
fhq_in_bit tr;
edge e[2*N];
int last[N],son[N],size[N],a[N],b[N],dis1[N],dis2[N],sta[N];
bool vis[N];
int tot,cnt,top,sum,root;
long long ans;
inline void add(int from,int to,int val){
	++tot;
	e[tot].from=from;
	e[tot].to=to;
	e[tot].val=val;
	e[tot].nxt=last[from];
	last[from]=tot;
}
void get_root(int u,int fa){
	son[u]=0;
	size[u]=1;
	for(int i=last[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]&&v!=fa){
			get_root(v,u);
			size[u]+=size[v];
			son[u]=max(size[v],son[u]);
		}
	}
	son[u]=max(sum-size[u],son[u]);
	if(son[u]<son[root])
		root=u;
}
void get_dis(int u,int fa){
	++cnt;
	a[cnt]=dis1[u];//dis1为长度
	b[cnt]=dis2[u];//dis2为边权
	for(int i=last[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]&&v!=fa){
			dis1[v]=dis1[u]+1;
			dis2[v]=dis2[u]+e[i].val;
			get_dis(v,u);
		}
	}
}
void calc(int u){
	tr.bit_ins(1,0);//插入(1,0)
	for(int i=last[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			cnt=0;
			dis1[v]=1;
			dis2[v]=e[i].val;
			get_dis(v,u);
			for(int j=1;j<=cnt;++j)
				if(a[j]<=l&&b[j]<=w)//防止越界
					ans+=tr.bit_query(l-a[j]+1,w-b[j]);
			for(int j=1;j<=cnt;++j)
				if(a[j]<=l&&b[j]<=w){
					sta[++top]=a[j];//这个数要在之后清空
					tr.bit_ins(a[j]+1,b[j]);
				}
		}
	}
	while(top){
		tr.clear(sta[top]+1);//清空
		top--;
	}
	tr.clear(1);//别忘了还有最开始的(1,0)
	tr.cnt=0;//cnt清空
}
void solve(int u){
	vis[u]=true;
	calc(u);
	for(int i=last[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			son[0]=sum=size[v];
			root=0;
			get_root(v,0);
			get_root(root,0);
			solve(root);
		}
	}
}
int main(){
	n=read();
	l=read();
	w=read();
	int x,y;
	for(int i=2;i<=n;++i){
		x=read();
		y=read();
		add(i,x,y);
		add(x,i,y);
	}
	son[0]=sum=n;
	root=0;
	get_root(1,0);
	get_root(root,0);
	solve(root);
	cout<<ans;
}
```

很简单对不对啊。

但是把这个代码一交…

Time limit exceeded on test 9...

毕竟这个算法是 $O(nlog^3n)$ 的啊。

看来只能用 排序+树状数组 了…

吗？

没事，我们可以**剪枝优化**。

第 9 个测试点长甚么样子呢？

```cpp
100000 600 81222411
1 8667
1 6347
2 49
2 3228
3 4875
3 1357
4 6006
4 9739
5 1526
5 6802
6 8956
6 6143
7 9356
7 1380
8 9923
8 3856
9 9794
9 3636
10 4148
10 7029
11 1780
11 9202
12 9838
12 3566
13 6108
13 3875
14 290
14 6097
15 4106
15 3903
16 9713
16 273
17 4341
17 2190
18 2938
18 6515
19 7831
19 4060
20 5958
20 3859
21 9452
21 1340
22 6722
22 6109
23 5574
23 8964
24 3026
24 2326
25 9617
25 5930
26 4374
26 7381
27 4889
27 3913
28 9482
28 4997
29 1236
...
```

一股完全二叉树的气息扑面而来。

~~其实我到现在还没想明白为什么卡链数据都过了，完全二叉树还没过…~~

我们可以手画一棵完全二叉树。

我通过**大眼观察法**，发现有许多关于长度的限制其实是没用的。那么是否可以直接进行剪枝呢？

**可以。**

我们记 $maxn$ 为之前遍历过的子树的最深的深度（初始为 1），那么如果 $l-a_j+1$ 要大于 $maxn$，我们是不是可以直接搜寻 $(maxn,w-b_j)$ 而不搜寻 $(l-a_j+1,w-b_j)$ 呢？

所以合并一下就是如下代码：

```cpp
if(a[j]<=l&&b[j]<=w)//边界条件还是要判断的
	ans+=tr.bit_query(min(maxn,l-a[j]+1),w-b[j]);
```

这是查询的优化，那么插入是否也可以优化呢？

**也可以。**

我们可以记一个数组 $son2$。$son2_u$ 表示以 $u$ 为根是最深的长度为多少。

$son2$ 可以在找重心时求出。但是这样就必须先以 $v$ 为根找一遍，再以 $root$ 为根找一遍。

那么我们每一次插入都只要找到 $son2_u+1$ 而非 $n+1$ 了。

~~这是什么？这是质的飞跃啊！~~

这样就终于可以快落的 AC 这一题了。

```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
const int N=1e5+10;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct fhq_in_bit{
	struct fhq_treap{
		long long size;
		int lson,rson;
		int val,key;
	};
	fhq_treap fhq[40*N];
	int root[N];
	int cnt;
	inline void pushup(int pos){
		fhq[pos].size=fhq[fhq[pos].lson].size+fhq[fhq[pos].rson].size+1;
	}
	inline int newnode(int val){
		++cnt;
		fhq[cnt].lson=fhq[cnt].rson=0;
		fhq[cnt].key=rand();
		fhq[cnt].val=val;
		fhq[cnt].size=1;
		return cnt;
	}
	void split(int pos,int val,int &x,int &y){
		if(!pos){
			x=y=0;
			return ;
		}
		if(fhq[pos].val<=val){
			x=pos;
			split(fhq[x].rson,val,fhq[x].rson,y);
		}
		else{
			y=pos;
			split(fhq[y].lson,val,x,fhq[y].lson);
		}
		pushup(pos);
	}
	int merge(int x,int y){
		if(!x||!y)
			return x|y;
		if(fhq[x].key>fhq[y].key){
			fhq[x].rson=merge(fhq[x].rson,y);
			pushup(x);
			return x;
		}
		else{
			fhq[y].lson=merge(x,fhq[y].lson);
			pushup(y);
			return y;
		}
	}
	inline void fhq_ins(int &rt,int val){
		int x,y;
		split(rt,val,x,y);
		rt=merge(merge(x,newnode(val)),y);
	}
	inline long long fhq_query(int &rt,int val){
		int x,y;
		split(rt,val,x,y);
		long long ans=fhq[x].size;
		rt=merge(x,y);
		return ans;
	}
	inline int lowbit(int x){
		return x&-x;
	}
	inline void bit_ins(int pos,int n,int val){
		for(int i=pos;i<=n+1;i+=lowbit(i))//因为到哪是由son2决定，所以n就变成传进来的参数
			fhq_ins(root[i],val);
	}
	inline long long bit_query(int r,int val){
		long long ans=0;
		for(int i=r;i;i-=lowbit(i))
			ans+=fhq_query(root[i],val);
		return ans;
	}
	inline void clear(int pos,int n){
		for(int i=pos;i<=n+1;i+=lowbit(i))//同理
			root[i]=0;
	}
};
struct edge{
	int from,to;
	int val;
	int nxt;
};
fhq_in_bit tr;
edge e[2*N];
int last[N],son1[N],son2[N],size[N],dep[N],a[N],b[N],dis1[N],dis2[N],sta[N];
bool vis[N];
int tot,cnt,top,sum,root;
long long ans;
int n,l,w;
inline void add(int from,int to,int val){
	++tot;
	e[tot].from=from;
	e[tot].to=to;
	e[tot].val=val;
	e[tot].nxt=last[from];
	last[from]=tot;
}
void get_root(int u,int fa){
	son1[u]=0;
	size[u]=1;
	son2[u]=dep[u]=dep[fa]+1;//son2初始值
	for(int i=last[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]&&v!=fa){
			get_root(v,u);
			size[u]+=size[v];
			son1[u]=max(size[v],son1[u]);
			son2[u]=max(son2[v],son2[u]);//更新son2值
		}
	}
	son1[u]=max(sum-size[u],son1[u]);
	if(son1[u]<son1[root])
		root=u;
}
void get_dis(int u,int fa){
	++cnt;
	a[cnt]=dis1[u];
	b[cnt]=dis2[u];
	for(int i=last[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]&&v!=fa){
			dis1[v]=dis1[u]+1;
			dis2[v]=dis2[u]+e[i].val;
			get_dis(v,u);
		}
	}
}
void calc(int u){
	tr.bit_ins(1,son2[u],0);
	int maxn=1;//赋值为1
	for(int i=last[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			cnt=0;
			dis1[v]=1;
			dis2[v]=e[i].val;
			get_dis(v,u);
			for(int j=1;j<=cnt;++j)
				if(a[j]<=l&&b[j]<=w)
					ans+=tr.bit_query(min(maxn,l-a[j]+1),w-b[j]);
			for(int j=1;j<=cnt;++j)
				if(a[j]<=l&&b[j]<=w){
					sta[++top]=a[j];
					tr.bit_ins(a[j]+1,son2[u],b[j]);
				}
			maxn=max(maxn,son2[v]);//不忘跟新maxn
		}
	}
	while(top){
		tr.clear(sta[top]+1,son2[u]);
		top--;
	}
	tr.clear(1,son2[u]);
	tr.cnt=0;
}
void solve(int u){
	vis[u]=true;
	calc(u);
	for(int i=last[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]){
			son1[0]=sum=size[v];
			root=0;
			get_root(v,0);
			get_root(root,0);
			solve(root);
		}
	}
}
int main(){
	n=read();
	l=read();
	w=read();
	int x,y;
	for(int i=2;i<=n;++i){
		x=read();
		y=read();
		add(i,x,y);
		add(x,i,y);
	}
	son1[0]=sum=n;
	root=0;
	get_root(1,0);
	get_root(root,0);
	solve(root);
	cout<<ans;
}
```

---

## 作者：UperFicial (赞：2)

考虑一个非常自然的想法：点分治。

对于分治点 $u$，对于在子树 $u$ 中的点 $i$，给它寄一个二元组 $(a_i,b_i)$，表示 $i$ 距离 $u$ 的边权与长度。

显然现在求的是二元组的二维偏序，不会树套树怎么办，直接 $\text{CDQ}$ 分治啊！

第一维的值域大，将它排序，第二维直接树状数组+双指针维护。

但这样会寄，因为会算重，$u$ 的子树内某两个点可能会同时选，那么直接跑一下每一个子树容斥一下即可。

算一下复杂度，点分治一个老哥，$\text{CDQ}$ 一个老哥，树状数组一个老哥，最后三个老哥，复杂度 $\Theta(n\log^3 n)$，非常的强大啊！可以通过本题。

代码：

```cpp
#define rep(i,a,b) for(register int i=a;i<=b;++i)
#define rev(i,a,b) for(register int i=a;i>=b;--i)
#define gra(i,u) for(register int i=head[u];i;i=edge[i].nxt)
using namespace std;
typedef long long ll;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}

const int MAXN(2e5+10);

int n,L,W;

struct E{int to,nxt,cost;};
E edge[MAXN<<1];

int head[MAXN],tot;

inline void add_edge(int u,int v,int w)
{
	edge[++tot].nxt=head[u];
	head[u]=tot;
	edge[tot].to=v;
	edge[tot].cost=w;
	return;
}

int root,siz[MAXN],dp[MAXN],S;
bool vis[MAXN];

inline void findroot(int u,int fa)
{
	siz[u]=1,dp[u]=0;
	gra(i,u)
	{
		int v=edge[i].to;
		if(v==fa||vis[v]) continue;
		findroot(v,u);
		siz[u]+=siz[v];
		dp[u]=Max(dp[u],siz[v]);
	}
	dp[u]=Max(dp[u],S-siz[u]);
	if(dp[u]<dp[root]||(!root)) root=u;
	return;  
}

struct BIT
{
	int tree[MAXN];
	
	inline int lowbit(int x){return x&(-x);}
	
	inline void update(int x,int k)
	{
		for(register int i=x;i<=n+1;i+=lowbit(i)) tree[i]+=k;
		return;
	}
	
	inline int query(int x)
	{
		int res(0);
		for(register int i=x;i;i-=lowbit(i)) res+=tree[i];
		return res;
	}
};

BIT bit;

int dep[MAXN],dis[MAXN],cnt;

typedef pair<int,int> P;

P a[MAXN];

inline void getdis(int u,int fa)
{
	a[++cnt]=make_pair(dis[u],dep[u]);
	gra(i,u)
	{
		E e=edge[i];
		if(vis[e.to]||e.to==fa) continue;
		dep[e.to]=dep[u]+1,dis[e.to]=dis[u]+e.cost;
		getdis(e.to,u);
	}
	return;
}

ll ans;

inline ll CDQ(int l,int r)
{
	if(l==r) return 0;
	int mid=(l+r)>>1;
	ll res=CDQ(l,mid)+CDQ(mid+1,r);
	int j(mid+1);
	rev(i,mid,l)
	{
		while(j<=r&&a[i].first+a[j].first<=W) bit.update(a[j++].second+1,1);
		if(L-a[i].second+1>0)res+=bit.query(L-a[i].second+1);
	}
	rep(i,mid+1,j-1) bit.update(a[i].second+1,-1);
	return res;
}

inline ll solve(int u,int DEP,int DIS)
{
	ll res(0);
	cnt=0;
	dep[u]=DEP,dis[u]=DIS;
	getdis(u,0);
	sort(a+1,a+1+cnt); 
	res=CDQ(1,cnt);
	return res;
}

inline void dfs(int u)
{
	ans+=solve(u,0,0);
	vis[u]=true;
	gra(i,u)
	{
		E e=edge[i];
		if(vis[e.to]) continue;
		S=siz[e.to],root=0;
		ans=ans-solve(e.to,dep[e.to],dis[e.to]);
		findroot(e.to,u);
		dfs(root);
	}
	return;
}

int main()
{
	n=read(),L=read(),W=read();
	rep(i,1,n-1)
	{
		int p=read(),w=read();
		add_edge(i+1,p,w),add_edge(p,i+1,w);
	}
	S=n;
	findroot(1,0);
	dfs(root);
	printf("%lld\n",ans);
	return 0;
}
/*
Date : 2022/8/30 
Author : UperFicial 
Start coding at : 18:25
finish debugging at :
*/
```

---

## 作者：Conan15 (赞：1)

乍一看好像这个双重限制很难整，但是仔细想想好像就是加了一个类似二维数点的东西？\
首先，如果只有一个限制，那么这题和 [Tree](https://www.luogu.com.cn/problem/P4178) 是一样的。

所以先考虑 Tree 怎么做。显然一个树状数组就干完了，但是好像直接树状数组并不是很好拓展到本题。\
所以再考虑 Tree 的另一种解法：双指针。

点分治的一个经典 trick 是：把 $u$ 为根的所有点两两（选 $a,b$ 两点）计算贡献，然后再扣除 $a,b$ 在同一棵子树 $v$（$v$ 是 $u$ 的儿子）中的情况。\
那么可以把所有的 $dist$ 排序，双指针要求满足 $dis_{l}+dis_{r} \leq k$，那么贡献点对数量就是 $r-l$。

延伸到本题，对于第一维仍然可以这么做，那第二维用树状数组维护 $[l,r]$ 中的点就好了。\
由于路径长度是 $10^9$，路径边数 $\leq n$，所以第一维是路径长度，第二维是路径边数。

另外注意树状数组维护前缀点数的时候需要保证 $x \gt 0$，所以修改的时候需要下标集体 $+1$，询问的时候要特判 $\lt 0$。

```cpp
#include <bits/stdc++.h>
#define PII pair<long long, int>
using namespace std;
const int N = 1e5 + 15, M = N << 1;
int n, kl, kw;
int h[N], e[M], w[M], ne[M], idx = 0;
void adde(int a, int b, int c) { e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++; }
void addedge(int a, int b, int c) { adde(a, b, c), adde(b, a, c); }

bool st[N];
int sz[N], Max[N], rt;
void getsz(int u, int father, int sum) {
    sz[u] = 1, Max[u] = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == father || st[v]) continue;
        getsz(v, u, sum), sz[u] += sz[v], Max[u] = max(Max[u], sz[v]);
    }
    Max[u] = max(Max[u], sum - sz[u]);
    if (!rt || Max[rt] > Max[u]) rt = u;
}
PII p[N]; int tot = 0;  //first -> dis   second -> len
int dis[N], dep[N];
long long ans = 0;
void getdis(int u, int father) {
    p[++tot] = {dis[u], dep[u]};
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == father || st[v]) continue;
        dis[v] = dis[u] + w[i], dep[v] = dep[u] + 1, getdis(v, u);
    }
}

int tr[N];
void add(int x, int d) { x++; for ( ; x < N ; x += x & -x) tr[x] += d; }
int ask(int x) {
    if (x < 0) return 0;
    x++;
    int res = 0;
    for ( ; x ; x -= x & -x) res += tr[x];
    return res;
}

long long getval(int u, int w, int d) {
    dis[u] = w, dep[u] = d, tot = 0, getdis(u, 0);
    sort(p + 1, p + 1 + tot);
    for (int i = 1; i <= tot; i++) add(p[i].second, 1);
    int l = 1, r = tot;
    long long res = 0;
    while (l <= r) {
        if (p[l].first + p[r].first <= kw) add(p[l].second, -1), res += ask(kl - p[l].second), l++;
        else add(p[r].second, -1), r--;
    }
    return res;
}

void dfs(int u) {
    st[u] = 1;
    ans += getval(u, 0, 0);

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (st[v]) continue;
        ans -= getval(v, w[i], 1);
        rt = 0, getsz(v, u, sz[u]), getsz(rt, 0, sz[u]);
        dfs(rt);
    }
}

int main() {
    scanf("%d%d%d", &n, &kl, &kw);
    for (int i = 1; i <= n; i++) h[i] = -1;
    for (int i = 2, fa, c; i <= n; i++) scanf("%d%d", &fa, &c), addedge(i, fa, c);
    
    rt = 0, getsz(1, 0, n), getsz(rt, 0, n);
    dfs(rt);
    
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：NightDiver (赞：1)

对于这种树上路径统计问题，一个经典解法就是点分治。

如果没有两个限制，还是很简单的，对于单个限制，使用树状数组来解决就行了。

但是这道题目要求两个限制，有点像二维偏序，但不完全是。可以说是分成了几个段，每个段之间求二维偏序，而要求段内不能产生贡献。如果这么表述这个问题的话，那就很好解决了：把段内的贡献先求出来，再求出总的贡献，减去即可。

但是如果在表述问题时用：子树内与已经记录的桶内的贡献，那么就死路一条了。

这给了两个启示：1.点分治不要拘泥于每个子树与已经记录的桶之间的关系。2.尝试转化问题，把问题用比较形式化的语言表述出来（比如“子树”这个说法，其实它是不是个树无所谓）。

注意有个易错点：不要搞混了限制中的 $l,w$ 与双指针中的 $l$，边权的 $w$。

[代码在这里](https://www.cnblogs.com/TongKa/p/18370368)

---

## 作者：lzyqwq (赞：1)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/articles/17531588.html)**

**[CF](https://codeforces.com/problemset/problem/293/E "CF")**

**[洛谷](https://www.luogu.com.cn/problem/CF293E "洛谷")**

码农但是好懂的方法。

> - 给出 $n$ 个点的树。边有长度为 $1$，以及权值为 $w$。求有多少对无序点对 $(i,j)(i\ne j)$ 满足 $i,j$ 路径上边长度和不超过 $L$，以及权值和不超过 $W$。
>
> - $n\le 10^5$，$W\le 10^9$。

看到树上路径问题，貌似没法 dp，于是考虑点分治。如果去掉 $L$ 的限制，就是 [P4178](https://www.luogu.com.cn/problem/P4178 "P4178")。于是考虑把 P4178 的树状数组换成树套树。然后你会发现这题卡了 $\mathcal{O}(n\log^3 n)$，喜提 TLE。

怎么办呢？设当前根为 $rt$，点 $u$ 到 $rt$ 的边长和为 $len_u$，边权和为 $val_u$。

先计算子树内的点之间的贡献，考虑怎样的点 $v$ 能够给点 $u$ 贡献，显然 $len_v\le L-len_u$ 且 $val_v\le W-val_u$。典型二维偏序。观察到 $W$ 值域较大，于是将所有点按照 $val$ 从小到大排序，并按照这个顺序建立主席树。主席树的节点内 $[l,r]$ 维护当前版本 $len_v$ 在这个区间内的数的个数。查询的时候，先二分出 $val_v\le W-val_u$ 的最后一个版本，然后查询区间 $[1,L-len_u]$ 即可。注意到自己可能会统计到自己，如果 $2\times len_u\le W$ 且 $2\times val_u\le W$，则将答案减去 $1$。

由于一条路径会在 $u,v$ 两点处计算到（移项一下 $u$  也满足 $v$ 的条件），将答案再除以二。

但是仍然会统计到同一子树之间的贡献，于是在 dfs 子树的时候，将子树内的节点存起来，然后它们进行上述的计算。再将这些结果减去。

再考虑子树到根的贡献，对于一个点，只要满足 $len_u\le L$ 且 $val_u\le W$。主席树上类似查询即可。

时间复杂度为 $\mathcal{O}(n\log^2n)$，空间复杂度为 $\mathcal{O}(n\log n)$。

**[记录](https://www.luogu.com.cn/problem/CF293E "记录")**


```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define lb(x) ((x)&(-x))
#define ll long long
using namespace std;
const int N=1e5+5;
int n,L,W,rt,sz[N],mx[N],tot,len[N],val[N],cnt,ls[N*30],rs[N*30],ver[N],node,a[N],num;
vector<pair<int,ll>>g[N];
pair<int,int>p[N],q[N];
ll ans,sum[N*30];
bool vis[N];
void insert(int&x,int y,int l,int r,int k){
    x=++node;
    sum[x]=sum[y]+1;
    if(l^r){
        int m=(l+r)>>1;
        if(k<=m){
            rs[x]=rs[y];
            insert(ls[x],ls[y],l,m,k);
        }else{
            ls[x]=ls[y];
            insert(rs[x],rs[y],m+1,r,k);
        }
    }
}
ll query(int x,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        return sum[x];
    }
    int m=(l+r)>>1;
    ll ret=0;
    if(ql<=m&&ls[x]){
        ret+=query(ls[x],l,m,ql,qr);
    }
    if(qr>m&&rs[x]){
        ret+=query(rs[x],m+1,r,ql,qr);
    }
    return ret;
}
void gravity(int u,int fa){
    sz[u]=1;
    mx[u]=0;
    for(auto[v,w]:g[u]){
        if((v^fa)&&!vis[v]){
            gravity(v,u);
            sz[u]+=sz[v];
            mx[u]=max(mx[u],sz[v]);
        }
    }
    mx[u]=max(tot-sz[u],mx[u]);
    if(mx[u]<mx[rt]){
        rt=u;
    }
}
void get(int u,int fa){
    q[++num]=p[++cnt]={val[u],len[u]};
    for(auto[v,w]:g[u]){
        if((v^fa)&&!vis[v]){
            len[v]=len[u]+1;
            val[v]=val[u]+w;
            get(v,u);
        }
    }
}
ll cal(pair<int,int>*p,int cnt){
    stable_sort(p+1,p+1+cnt);
    for(int i=1;i<=cnt;++i){
        insert(ver[i],ver[i-1],1,n,p[i].second);
    }
    ll s=0;
    int k=cnt;
    for(int i=1;i<=cnt;++i){
        if(p[i].first>W){
            k=i-1;
            break;
        }
        if(p[i].second>=L){
            continue;
        }
        int l=1,r=cnt,f=0;
        while(l<=r){
            int m=(l+r)>>1;
            if(p[m].first<=W-p[i].first){
                f=m;
                l=m+1;
            }else{
                r=m-1;
            }
        }
        s+=query(ver[f],1,n,1,L-p[i].second);
        if((p[i].first<<1)<=W&&(p[i].second<<1)<=L){
            --s;
        }
    }
    return s>>1;
}
void clear(int&tmp){
    for(int i=1;i<=node;++i){
        sum[i]=ls[i]=rs[i]=0;
    }
    for(int i=1;i<=tmp;++i){
        ver[i]=0;
    }
    tmp=node=0;
}
void divide(int u){
    vis[u]=1;
    for(auto[v,w]:g[u]){
        if(!vis[v]){
            len[v]=1;
            val[v]=w;
            get(v,u);
            ans-=cal(q,num);
            clear(num);
        }
    }
    if(!cnt){
        return;
    }
    ans+=cal(p,cnt);
    int l=1,r=cnt,f=0;
    while(l<=r){
        int m=(l+r)>>1;
        if(p[m].first<=W){
            f=m;
            l=m+1;
        }else{
            r=m-1;
        }
    }
    ans+=query(ver[f],1,n,1,L);
    clear(cnt);
    for(auto[v,w]:g[u]){
        if(!vis[v]){
            tot=sz[v];
            mx[rt=0]=1e9;
            gravity(v,u);
            gravity(rt,0);
            divide(rt);
        }
    }
}
int main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n>>L>>W;
    for(int i=1,p,w;i^n;++i){
        cin>>p>>w;
        g[i+1].emplace_back(p,w);
        g[p].emplace_back(i+1,w);
    }
    tot=n;
    mx[0]=1e9;
    gravity(1,0);
    gravity(rt,0);
    divide(rt);
    cout<<ans;
}
```

---

## 作者：Diaоsi (赞：1)

[Close Vertices](https://www.luogu.com.cn/problem/CF293E)

点分治。

首先考虑如果只有 $w$ 一维的限制该怎么做，就是点分治的板子，对于每个分治重心，处理出当前分治区域内的点到分治重心的 $w$ 值和 $l$ 值的和，排序之后用双指针扫描一遍就行。

将 $w$ 从小到大排序之后用一个左指针单调向右扫描，右指针指向当前序列中的最大的能与 $w_l$ 相加之后小于等于限制的值的位置，形象地说就是：

$$ w_l + w_r \leq w_{\lim}\ ,\ w_l + w_{r+1} > w_{\lim} $$

由于 $w$ 是单调递增的，所以右指针单调向右移，当没有 $l_{\lim}$ 的限制时，区间 $w_{l+1 \sim r}$ 中的点都能与 $w_l$ 匹配形成一条经过分治重心且 $\sum w \leq w_{\lim}$ 的路径。

接下来在 $w_{\lim}$ 的限制下考虑 $l_{\lim}$ 的限制，也就是说我们要知道在 $w_{l+1 \sim r}$ 这些值对应的点中有哪些点能与左指针的点匹配形成一条 $\sum l \leq l_{\lim}$  的路径。

由于 $l$ 值的上限是 $10^5$ ，所以可以将 $l$ 映射到树状数组上，可以将 $l$ 值作为树状数组下标，一开始将序列上的点的 $l$ 值都加入到树状数组中，当左右指针向中移动时就一个一个地将点对应的信息从树状数组上删去。

匹配时树状数组维护的信息就是左右指针对应地区间中的点的信息，于是直接查询有多少点能与左指针指向的点匹配即可。

具体实现有一些小细节，可以参考代码，时间复杂度为 $\mathcal{O(n\log^2 n)}$ 。

既然你能找到这题，我相信你能瞬间做出来的。

```Code:```

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
typedef long long LL;
typedef long double LD;
using namespace std;
const LL N=100010,M=1000010,INF=0x3f3f3f3f;
inline LL max(LL x,LL y){return x>y?x:y;}
inline LL min(LL x,LL y){return x<y?x:y;}
inline void swap(LL &x,LL &y){x^=y^=x^=y;}
LL head[N],ver[M],edge[M],Next[M],tot;
LL n,L,W,rt,ans,c[N],d[N],vis[N],size[N];
vector<pair<LL, LL> > v;// fi -> W se -> L
void add(LL x,LL y){
	for(++x;x<N;x+=x&-x)c[x]+=y;
}
LL ask(LL x){
	LL res=0;x=max(x,0)+1;
	for(;x;x-=x&-x)res+=c[x];
	return res;
}
void add(LL x,LL y,LL z){
	ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}
void get_size(LL x,LL fa){
	size[x]=1;
	for(LL i=head[x];i;i=Next[i]){
		LL y=ver[i];
		if(y==fa||vis[y])continue;
		get_size(y,x);
		size[x]+=size[y];
	}
}
void get_rt(LL x,LL fa,LL sum){
	size[x]=1;
	LL flag=1;
	for(LL i=head[x];i;i=Next[i]){
		LL y=ver[i];
		if(y==fa||vis[y])continue;
		get_rt(y,x,sum);
		size[x]+=size[y];
		if(size[y]>sum/2)flag=0;
	}
	if(flag&&sum-size[x]<=sum/2)rt=x;
}
void get_dis(LL x,LL fa,LL val,LL dis){
	v.push_back(make_pair(val,dis));
	if(val>=W||dis>=L)return;
	for(LL i=head[x];i;i=Next[i]){
		LL y=ver[i],z=edge[i];
		if(y==fa||vis[y])continue;
		get_dis(y,x,val+z,dis+1);
	}
}
void calc(LL x){
	for(LL i=head[x];i;i=Next[i]){
		LL y=ver[i],z=edge[i];
		if(vis[y])continue;
		v.clear();
		get_dis(y,x,z,1);
		sort(v.begin(),v.end());
		for(pair<LL, LL> z:v)add(z.se,1);
		for(LL l=0,r=v.size()-1;l<(LL)v.size();l++){
			add(v[l].se,-1);
			while(l<r&&v[l].fi+v[r].fi>W)add(v[r--].se,-1);
			if(l>=r)break;
			ans-=ask(L-v[l].se);
		}
	}
	v.clear();
	get_dis(x,0,0,0);
	sort(v.begin(),v.end());
	for(pair<LL, LL> z:v)add(z.se,1);
	for(LL l=0,r=v.size()-1;l<(LL)v.size();l++){
		add(v[l].se,-1);
		while(l<r&&v[l].fi+v[r].fi>W)add(v[r--].se,-1);
		if(l>=r)break;
		ans+=ask(L-v[l].se);
	}
}
void solve(LL x){
	vis[x]=1;
	calc(x);
	for(LL i=head[x];i;i=Next[i]){
		LL y=ver[i];
		if(vis[y])continue;
		get_size(y,x);
		get_rt(y,x,size[y]);
		solve(rt);
	}
}
int main(){
	scanf("%lld%lld%lld",&n,&L,&W);
	for(LL i=1;i<n;i++){
		LL p,w;
		scanf("%lld%lld",&p,&w);
		add(i+1,p,w),add(p,i+1,w);
	}
	get_size(1,0);
	get_rt(1,0,n);
	solve(rt);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：liangzihao (赞：1)

题目大意：
给你一棵有$n(n<=10^5)$个点的树，每条边有边权$w_i(0<=w_i<=10^4)$，定义两个点$(x,y)$的距离为简单路径上的边数，权重为简单路径上的权值和。求有多少对$(x,y)$，其中$x≠y$，距离小于等于$l(l<=n)$，权重小于等于$w(0<=w<=10^9)$。

分析：
两点之间的距离和权重显然可以想到点分治了。考虑一棵子树对于前面的子树的贡献。先只考虑一维距离，我们可以把当前子树节点的到当前根的距离从大到小排序，把前面的子树的节点从小到大排序，这时候只需要分别使用一个指针就可以了。当一个指针右移使距离变小时，另一个指针右移增大，然后统计答案即可。复杂度是与节点数线性相关的。

对于两维的话，第一维还是按照上述方法，而第二个指针右移时，把这些节点的第二维丢到一个树状数组里，然后就可以统计答案了。由于距离最大只有$n-1$，而权值能达到$10^9$，所以第一维应该设为权值，第二维应该设为距离。

代码：
```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#define LL long long

const int maxn=1e5+7;

using namespace std;

int n,l,d,x,w,cnt,root,sum,head,tail;
int t[maxn];
LL ans;
int size[maxn],vis[maxn],dis[maxn],len[maxn],f[maxn];
int ls[maxn];

struct edge{
    int y,w,next;
}g[maxn*2];

struct rec{
    int l,d;
}h[maxn];

queue <int> q;

void add(int x,int y,int w)
{
    g[++cnt]=(edge){y,w,ls[x]};
    ls[x]=cnt;
}

bool cmp1(rec x,rec y)
{
    return x.d<y.d;
}

bool cmp2(rec x,rec y)
{
    return x.d>y.d;
}

void findroot(int x,int fa)
{
    size[x]=1;
    f[x]=0;
    for (int i=ls[x];i>0;i=g[i].next)
    {
        int y=g[i].y;
        if ((y==fa) || (vis[y])) continue;
        findroot(y,x);
        size[x]+=size[y];
        f[x]=max(f[x],size[y]);
    }
    f[x]=max(f[x],sum-size[x]);
    if ((f[x]<f[root]) || (!root)) root=x;
}

int lowbit(int x)
{
    return x&(-x);
}

void updata(int x,int k)
{
    while (x<=n)
    {
        t[x]+=k;
        x+=lowbit(x);
    }
}

int getsum(int x)
{
    int sum=0;
    while (x>0)
    {
        sum+=t[x];
        x-=lowbit(x);
    }
    return sum;
}

void dfs(int x,int fa)
{
    size[x]=1;
    for (int i=ls[x];i>0;i=g[i].next)
    {
        int y=g[i].y;
        if ((y==fa) || (vis[y])) continue;
        len[y]=len[x]+1;
        dis[y]=dis[x]+g[i].w;
        h[++tail]=(rec){len[y],dis[y]};
        dfs(y,x);
        size[x]+=size[y];
        if (x==root)
        {
            sort(h+1,h+head+1,cmp1);
            sort(h+head+1,h+tail+1,cmp2);
            int k=1;
            for (int j=head+1;j<=tail;j++)
            {
                while ((h[k].d+h[j].d<=d) && (k<=head))
                {
                    updata(h[k].l+1,1);
                    k++;
                }
                ans+=(LL)getsum(l-h[j].l+1);
            }
            for (int g=1;g<k;g++) updata(h[g].l+1,-1);
            head=tail;
            q.push(y);
        }
    }
}

int main()
{
    scanf("%d%d%d",&n,&l,&d);	
    for (int i=2;i<=n;i++)
    {
        scanf("%d%d",&x,&w);
        add(i,x,w);
        add(x,i,w);
    }	
    q.push(1);
    size[1]=n;	
    while (!q.empty())
    {
        int x=q.front();
        q.pop();
        sum=size[x];
        root=0;
        findroot(x,0);
        len[root]=dis[root]=0;
        head=1; tail=1;
        h[1]=(rec){0,0};
        dfs(root,0);
        vis[root]=1;
    }
    printf("%lld",ans);
}
```

---

## 作者：Union_Find (赞：0)

容易注意到路径问题可以点分治。

设 $dep_u,dis_u$ 分别表示点 $u$ 到 $rt$ 的边数和距离。那么就是求 $dep_u+dep_v \le l$  且 $dis_u + dis_v \le w$ 的 $(u,v)$ 个数。容易发现，当 $u$ 固定时，满足条件的 $v$ 的 $dep$ 和 $dis$ 是一段区间，我们考虑处理这个。

首先是 $dis$，可以直接排序，然后双指针固定位置。然后考虑 $dep$，使用树状数组查询区间。树状数组是在双指针移动时一起维护。然后在左指针移动时记录答案。但是直接这样做会重复，我们要把在同一子树内的点对减去即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define il inline
#define N 100005
#define getv(t, ii) (ii < t.size() ? t[ii].v : 0)
#define getw(t, ii) (ii < t.size() ? t[ii].w : 0)
#define rep(u, v, w) for (int ii = 0, v = getv(e[u], 0), w = getw(e[u], 0); ii < e[u].size(); ii++, v = getv(e[u], ii), w = getw(e[u], ii))
#define repq(i) for (int i = q.hd; i <= q.tl; i++)
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}

int n, lp, lw, u, v, w, ans;
int sz[N], mxs[N], rt, dep[N], dis[N], tr[N];
il bool cmp(int a, int b){return dis[a] != dis[b] ? dis[a] < dis[b] : dep[a] < dep[b];}
struct Queue{
	int hd = 1, tl, q[N];
	il bool empty(){return hd > tl;}
	il void pop(){hd++;}
	il void push(int x){q[++tl] = x;}
	il int front(){return q[hd];}
	il void clr(){hd = 1, tl = 0;}
	il void sorts(){sort (q + hd, q + tl + 1, cmp);}
	int& operator [](const int &x){return q[x];}
}q;
il void add(int x, int k){if (!x) return ;for (int i = x; i <= n + 1; i += (i & (-i))) tr[i] += k;}
il int ask(int x){int ans = 0;for (int i = x; i >= 1; i -= (i & (-i))) ans += tr[i];return ans;}
struct E{
	int v, w;
};
vector <E> e[N];
bool del[N];
void get_size(int u, int fa, int S){
	sz[u] = 1, mxs[u] = 0;
	rep(u, v, w) if (!del[v] && v != fa) get_size(v, u, S), sz[u] += sz[v], mxs[u] = max(mxs[u], sz[v]);
	mxs[u] = max(mxs[u], S - sz[u]), rt = mxs[u] < mxs[rt] ? u : rt;
}
void get_dep(int u, int fa){
	q.push(u);rep(u, v, w) if (!del[v] && v != fa) dep[v] = dep[u] + 1, dis[v] = dis[u] + w, get_dep(v, u);
}
il int calc(int u, int D1, int D2){
	int res = 0;
	q.clr();
	dep[u] = D1, dis[u] = D2, get_dep(u, 0);
	q.sorts();
	repq(i) add(dep[q[i]] + 1, 1);
	int l = q.hd, r = q.tl;
	for (; l < r;){
		if (dis[q[l]] + dis[q[r]] <= lw) add(dep[q[l]] + 1, -1), res += ask(lp - dep[q[l]] + 1), l++;
		else add(dep[q[r]] + 1, -1), r--;
	}add(dep[q[l]] + 1, -1);
	return res;
}
void solve(int u, int S){
	rt = 0, get_size(u, 0, S), u = rt, get_size(u, 0, S), del[u] = 1, ans += calc(u, 0, 0);
	rep(u, v, w) if (!del[v]) ans -= calc(v, 1, w);
	rep(u, v, w) if (!del[v]) solve(v, sz[v]);
}
signed main(){
	n = rd(), lp = rd(), lw = rd();
	for (int i = 1; i < n; i++){
		u = rd(), w = rd();
		e[u].push_back(E{i + 1, w}), e[i + 1].push_back({u, w});
	}mxs[0] = 1e9, solve(1, n), printf ("%lld", ans);
	return 0;
}

```

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

如果只有一维，那就是 P4178，可以直接树状数组维护。

但是它是二维的，所以我们可以把 DS 也开成二维的。第一维只有 $10 ^ {5}$，树状数组开的下。第二维的大小达到了 $10 ^ {9}$，不能用树状数组。

我们需要维护的是一个数的排名，可以用权值线段树或者平衡树。树状数组套权值线段树的空间复杂度是 $\Omicron(n \log ^ 2 n)$ 的，会爆，所以我选的是树状数组套 FHQ Treap（如果你懒得写你也可以直接用 pbds 的红黑树）。时间复杂度是 $\Omicron(n \log ^ 3 n)$

但是，这个东西常数太大了，被卡掉了，考虑卡常。

我们发现，这个 $l$ 最大只会更新到 $dep _ {max}$，$dep$ 指子树内结点的深度，所以，我们可以预处理一个 $mxdep$，每次只更新到 $mxdep$。同理，因为更新最多到 $mxdep$，所以我们查询也只用查询到 $mxdep _ {max}$。

$mxdep$ 可以在求重心的时候顺便求出来，只不过要跑两遍。

你也可以用其他方法跑二维偏序，比如 CDQ 分治，~~但我就喜欢用纯 DS 的方法过~~。

### Code

手写的 FHQ Treap，pbds 因为常数会跑的比较慢。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,ll>
using namespace std;

constexpr int MAXN = 1e5 + 24;
int n,L,W,v;
ll ans,w;
vector<pii> g[MAXN];
random_device seed;
mt19937 rnd(seed());
namespace FHQBIT
{
    namespace FHQTreap
    {
        struct Firefly
        {
            ll rank,size;
            int ls,rs,val;
        }tree[MAXN * 40];
        #define lson(rt) tree[rt].ls
        #define rson(rt) tree[rt].rs
        int cnt;
        inline int newNode(int val)
        {
            ++cnt;
            lson(cnt) = rson(cnt) = 0;
            tree[cnt].val = val,tree[cnt].rank = rnd(),tree[cnt].size = 1;
            return cnt;
        }
        inline void pushup(int rt)
        {tree[rt].size = tree[lson(rt)].size + tree[rson(rt)].size + 1;}
        inline void splitVal(int rt,int val,int &L,int &R)
        {
            if(!rt)
            {
                L = R = 0;
                return ;
            }
            if(tree[rt].val <= val)
            {
                L = rt;
                splitVal(rson(rt),val,rson(rt),R);
            }
            else
            {
                R = rt;
                splitVal(lson(rt),val,L,lson(rt));
            }
            pushup(rt);
        }
        inline int merge(int L,int R)
        {
            if(!L || !R)
                return L | R;
            if(tree[L].rank < tree[R].rank)
            {
                rson(L) = merge(rson(L),R);
                pushup(L);
                return L;
            }
            else
            {
                lson(R) = merge(L,lson(R));
                pushup(R);
                return R;
            }
        }
        inline void insert(int &rt,int val)
        {
            int x,y;
            splitVal(rt,val,x,y);
            rt = merge(merge(x,newNode(val)),y);
        }
        inline int query(int &rt,int val)
        {
            int x,y;
            splitVal(rt,val,x,y);
            int res = tree[x].size;
            rt = merge(x,y);
            return res;
        }
    }
    int root[MAXN];
    inline int lowbit(int x)
    {return (x & (-x));}
    inline void modify(int p,int n,int val)
    {
        for(int i = p;i <= n + 1;i += lowbit(i))
            FHQTreap::insert(root[i],val);
    }
    inline int query(int p,int val)
    {
        int res = 0;
        for(int i = p;i;i -= lowbit(i))
            res += FHQTreap::query(root[i],val);
        return res;
    }
    inline void remove(int p,int n)
    {
        for(int i = p;i <= n + 1;i += lowbit(i))
            root[i] = 0;
    }
}
namespace PDC
{
    int mx[MAXN],sz[MAXN],mxdep[MAXN],dep[MAXN],GC[MAXN],root,sum,cnt;
    ll dis[MAXN];
    pii rec[MAXN];
    bool vis[MAXN];
    inline void getRoot(int u,int fa)
    {
        mx[u] = 0,sz[u] = 1,mxdep[u] = dep[u] = dep[fa] + 1;
        for(auto x : g[u])
        {
            int v = x.first;
            if(v == fa || vis[v])
                continue;
            getRoot(v,u);
            sz[u] += sz[v];
            mx[u] = max(mx[u],sz[v]);
            mxdep[u] = max(mxdep[u],mxdep[v]);
        }
        mx[u] = max(mx[u],sum - sz[u]);
        if(mx[u] < mx[root])
            root = u;
    }
    inline void getDis(int u,int fa)
    {
        rec[++cnt] = {dep[u],dis[u]};
        for(auto x : g[u])
        {
            int v = x.first;
            if(v == fa || vis[v])
                continue;
            dep[v] = dep[u] + 1,dis[v] = dis[u] + x.second;
            getDis(v,u);
        }
    }
    inline void solve(int u)
    {
        FHQBIT::modify(1,mxdep[u],0);
        int lmt = 1,top = 0;
        for(auto x : g[u])
        {
            int v = x.first;
            if(vis[v])
                continue;
            cnt = 0,dep[v] = 1,dis[v] = x.second;
            getDis(v,u);
            for(int i = 1;i <= cnt;i++)
            {
                if(rec[i].first <= L && rec[i].second <= W)
                    ans += FHQBIT::query(min(lmt,L - rec[i].first + 1),W - rec[i].second);
            }
            for(int i = 1;i <= cnt;i++)
            {
                if(rec[i].first <= L && rec[i].second <= W)
                {
                    GC[++top] = rec[i].first + 1;
                    FHQBIT::modify(GC[top],mxdep[u],rec[i].second);
                }
            }
            lmt = max(lmt,mxdep[v]);
        }
        for(int i = 1;i <= top;i++)
            FHQBIT::remove(GC[i],mxdep[u]);
        FHQBIT::remove(1,mxdep[u]);
        FHQBIT::FHQTreap::cnt = 0;
    }
    inline void DFZ(int u)
    {
        vis[u] = 1;
        solve(u);
        for(auto x : g[u])
        {
            int v = x.first;
            if(vis[v])
                continue;
            mx[root = 0] = sum = sz[v];
            getRoot(v,0),getRoot(root,0);
            DFZ(root);
        }
    }
}
using namespace PDC;
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> n >> L >> W;
    for(int u = 2;u <= n;u++)
    {
        cin >> v >> w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    mx[root = 0] = sum = n;
    getRoot(1,0),getRoot(root,0);
    DFZ(root);
    cout << ans;
}
```

---

## 作者：Nephren_Sakura (赞：0)

点分治板子。

题目要求长度在 $l$ 内，且权值总和在 $w$ 内的路径条数。考虑如何维护这个信息。

对于每个节点 $cur$，遍历 $cur$ 的每一棵子树 $nxt$。然后计算当前子树 $nxt$ 与之前的子树的贡献。

也就是说现在有一些路径，要找到 $nxt$ 之前的路径数量满足两条路径的长度之和不超过 $l$，权值之和不超过 $w$。容易想到用二维数点去做，时间复杂度 $O(n^2 \times \log n)$。

现在我们考虑如何加速计算。序列上的分治是利用的中点的性质，每一次最长序列长度除以 $2$，至多 $\log n$ 次后便会结束分治。

考虑树上有哪些有类似性质的点，发现重心的所有子树大小也会除以 $2$，如果用类似于广搜的方法去理解，每一层至多有 $n$ 个点，至多出现 $\log n$ 层，时间复杂度 $O(n \times \log n)$。

再加上二维数点的时间复杂度是 $O(n \times \log^2 n)$。

贴一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,L,W,nwsiz,siz[1000005],ans;
bool del[1000005];
vector<pair<int,int> > v[1000005];
int find(int cur,int fa){
	int mx=0;
	for(auto i:v[cur]){
		int nxt=i.first;
		if(nxt!=fa&&!del[nxt]){
			int val=find(nxt,cur);
			if(val) return val;
			mx=max(mx,siz[nxt]);
		}
	}
	if(max(mx,nwsiz-siz[cur])*2<=nwsiz) return cur;
	return 0;
}
void pre(int cur,int fa){
	siz[cur]=1;
	for(auto i:v[cur]){
		int nxt=i.first;
		if(nxt!=fa&&!del[nxt]) pre(nxt,cur),siz[cur]+=siz[nxt];
	}
	return;
}
struct BIT{
	int tree[1000005];
	void update(int cur,int val){cur++;for(int i=cur; i<=n; i+=(i&-i)) tree[i]+=val;return;}
	int query(int cur){int res=0;cur++;for(int i=cur; i; i-=(i&-i)) res+=tree[i];return res;}
}T;
vector<pair<int,int> > V;
struct node{
	int w,l,id;
};
vector<node> v2;
bool cmp(node x,node y){if(x.w!=y.w) return x.w>y.w;return x.id>y.id;}
void queryans(int cur,int fa,int l,int w){
	V.push_back({w,l});
	if(w<=W&&l<=L) ans++;
	else return;
	for(auto i:v[cur]){
		int nxt=i.first;
		if(nxt!=fa&&!del[nxt]) queryans(nxt,cur,l+1,w+i.second);
	}
	return;
}
void dfs(int cur){
	for(auto i:v[cur]){
		int nxt=i.first;
		if(!del[nxt]){
			int lst=V.size();
			queryans(nxt,cur,1,i.second);
			v2.clear();
			for(int i=0; i<lst; i++) v2.push_back({V[i].first,V[i].second,1}),T.update(V[i].second,1);
			for(int i=lst; i<V.size(); i++) v2.push_back({W-V[i].first,L-V[i].second,2});
			sort(v2.begin(),v2.end(),cmp);
			for(auto x:v2){
				if(x.id==2&&x.l>=0) ans+=T.query(x.l);
				else if(x.id==1&&x.l>=0) T.update(x.l,-1);
			}
		}
	}
	V.clear();
	del[cur]=true;
	pre(cur,0);
	for(auto i:v[cur]){
		int nxt=i.first;
		if(!del[nxt]) nwsiz=siz[nxt],dfs(find(nxt,0));
	}
	return;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>L>>W;
	for(int i=2,x,w; i<=n; i++) cin>>x>>w,v[x].push_back({i,w}),v[i].push_back({x,w});
	nwsiz=n,pre(1,0),dfs(find(1,0));
	cout<<ans;
	return 0;
}
```

---

## 作者：liujiaxi123456 (赞：0)

## 关键词：点分治，双指针，树状数组
### 思路：
**全局点对信息**，考虑点分治。

考虑跨越信息如何求解，最直观的做法是树套树直接维护二维限制。

但二维偏序限制显然可以先排序降调一维，但如果直接二叉合并的话，需要把 $1$ 到 $i-1$ 的所有儿子和第 $i$ 个儿子合并，时间会爆炸。

于是我们考虑把所有儿子的信息一起统一双指针。具体的，先按 $dis$ 排序，令 $l=1,r=top$，一直向左移动右指针直到 $dis_l+dis_r\le limit_{dis}$，此时 $l$ 指针提供的答案就是 $\left [ l,r \right ]$ 中 $dep \le limit_{dep}-dep_l$ 的点的数量，树状数组即可解决。

但是注意到上面的答案中可能包含路径的两个端点都在同一个子树的情况，这条路径是不经过当前的分支中心的，但是却被统计进了当前分支中心的答案，明显重复了，需要去重。

也很简单，只需要统计一下两个端点都在一个子树里的情况即可，统计方法同上，对每个子树双指针一遍即可。
### Code：
```cpp 
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 1e5+5;
int N, A, B;

namespace EDGE {
	int sz, head[Maxn];
	struct Edge { int next, to, val; } edge[Maxn*2];
	inline void Add_edge(int u, int v, int w) {
		edge[++sz] = {head[u], v, w};
		head[u] = sz;
	}
} using namespace EDGE;

class BinaryIndexedTree {
private:
	int tree[Maxn];	
	inline int lowbit(int t) { return t&(-t); } 
public:
	inline void Add(int t, int delta) {
		for(t++; t<=N; t+=lowbit(t))	tree[t] += delta;
	}
	inline int Ask(int t) {
		int res = 0;
		for(t=min(t+1, N); t; t-=lowbit(t))	res += tree[t];
		return res;
	}
} bit;

namespace Josh_zmf {
	
	int rt, sum, size[Maxn], top, dis[Maxn];
	ll ans; bool vis[Maxn];
	struct node { int dis, dep; } stk[Maxn];

	inline void getrt(int u, int faa) {
		static int maxx[Maxn]; maxx[u] = sum - size[u];
		for(int i=head[u], v; i; i=edge[i].next) {
			if((v=edge[i].to)==faa || vis[v])	continue;
			getrt(v, u), maxx[u] = max(maxx[u], size[v]);
		}
		if(!rt || maxx[u] < maxx[rt])	rt = u;
	}

	inline int getsz(int u, int faa) {
		size[u] = 1;
		for(int i=head[u], v; i; i=edge[i].next) {
			if((v=edge[i].to)==faa || vis[v])	continue;
			size[u] += getsz(v, u);
		}
		return size[u];
	}

	inline void getdis(int u, int faa, int diss, int depp) {
		if(diss>A || depp>B)	return ;
		stk[++top] = {diss, depp};
		for(int i=head[u], v; i; i=edge[i].next) {
			if((v=edge[i].to) == faa || vis[v])	continue;
			getdis(v, u, diss+edge[i].val, depp+1);
		}
	}
	
	inline void dfs(int u) {
		sum = getsz(u, 0), rt = 0, getrt(u, 0), vis[u=rt] = 1;
		// printf("dfs(%d)\n", u);
		stk[top=1] = {0, 0};
		for(int i=head[u], v, start; i; i=edge[i].next) {
			if(vis[v=edge[i].to])	continue;
			start = top+1, getdis(v, u, edge[i].val, 1);
			sort(stk+start, stk+1+top, [&](const node &x, const node &y) { return x.dis < y.dis; } );
			for(int j=start; j<=top; j++)	bit.Add(stk[j].dep, 1);
			for(int x=start, y=top; x<=y; x++) {
				for(; x<y && stk[x].dis+stk[y].dis>A; y--)	bit.Add(stk[y].dep, -1);
				bit.Add(stk[x].dep, -1), ans -= bit.Ask(B-stk[x].dep);
			}
		}
		sort(stk+1, stk+1+top, [&](const node &x, const node &y) { return x.dis < y.dis; } );
		for(int i=1; i<=top; i++)	bit.Add(stk[i].dep, 1);
		for(int l=1, r=top; l<=r; l++) {
			for(; l<r && stk[l].dis+stk[r].dis>A; r--)	bit.Add(stk[r].dep, -1);
			bit.Add(stk[l].dep, -1), ans += bit.Ask(B-stk[l].dep);
		}
		for(int i=head[u], v; i; i=edge[i].next) {
			if(!vis[v=edge[i].to])	dfs(v);
		}
	}
	

	inline int main() {
		cin>> N>> B>> A;
		for(int i=2, v, w; i<=N; i++)	cin>> v>> w, Add_edge(i, v, w), Add_edge(v, i, w);
		dfs(1), cout<< ans;
		return 0;
	}

}

signed main() {
	Josh_zmf::main();
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：0)

### [CF293E Close Vertices](https://www.luogu.com.cn/problem/CF293E)
相比于模板，这道题只多了一个路径长度不超过 $l$ 的限制，自然可以想到二维数点。\
点分治一般有两种写法，一种运用容斥，一种不运用，因为树状数组二维数点只能离线，所以只能运用容斥，否则不能将询问离线下来，或者可以采用树套树来维护，这样可以不用容斥。\
具体来说，每次分治时，将路径权值固定，从小到大排序，然后将路径长度作为树状数组的下标，直接修改查询，然后容斥减去子树内的贡献即可。每次分治结束时将树状数组清空。\
由于长度和权值会有 $0$，可以将树状数组这样写：
- `p|=p+1` 查找父亲。
- `p=(p&p+1)-1` 查找上一个范围的父亲。

或者直接全部加一后存也行。
```cpp
#include<bits/stdc++.h>
typedef long long ll;
#define int long long
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=1e5+10;
int n,l,k,size[N],head[N],dis[N],top,tot,dep[N],rt,t[N],ans;
std::vector<std::pair<int,int>> d;
bool vis[N];
struct EDGE{int v,next,w;}e[N<<1];
inline void add(int u,int v,int w){e[++tot]={v,head[u],w};head[u]=tot;}
inline void insert(int p,int x){for(;p<=n;p|=p+1)t[p]+=x;}
inline int query(int p){int res=0;for(;p>=0;p=(p&p+1)-1)res+=t[p];return res;}
inline void findrt(int x,int fa,int cnt){
	size[x]=1;int mx=0;
	for(int i=head[x],y;i;i=e[i].next){
		if(vis[y=e[i].v]||y==fa)continue;
		findrt(y,x,cnt);
		size[x]+=size[y];
		mx=std::max(size[y],mx);
	}
	mx=std::max(mx,cnt-size[x]);
	if(mx<=cnt/2)rt=x;
}
inline void dfs(int x,int fa,int di,int de){
	d.push_back({di,de});
	for(int i=head[x],y;i;i=e[i].next){
        if(vis[y=e[i].v]||y==fa)continue;
        dfs(y,x,di+e[i].w,de+1);
    }
}
inline int calc(int x,int fa,int di,int de){
	dfs(x,fa,di,de);int res=0;
	std::vector<std::pair<int,int>>q;
	std::sort(d.begin(),d.end());
	for(int i=d.size()-1;i>=0;i--){q.push_back({k-d[i].first,l-d[i].second});}
	int l=0;
	for(auto it:q){
		while(l<d.size()&&d[l].first<=it.first)insert(d[l].second,1),l++;
		res+=query(it.second);
	}
	for(int i=0;i<l;++i)insert(d[i].second,-1);
	d.clear();
	return res;
}
inline void solve(int x){
	vis[x]=1;ans+=calc(x,0,0,0);
	for(int i=head[x],y;i;i=e[i].next){
		if(vis[y=e[i].v])continue;
		ans-=calc(y,0,e[i].w,1);
	}
	for(int i=head[x],y;i;i=e[i].next){
        if(vis[y=e[i].v])continue;
		findrt(y,0,size[y]);findrt(rt,0,size[y]);
		solve(rt);
    }
}
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	n=read(),l=read(),k=read();
	for(int i=1;i<n;++i){
		int x=read(),w=read();
		add(x,i+1,w),add(i+1,x,w);
	}
	findrt(1,0,n);findrt(rt,0,n);
	solve(rt);
	std::cout<<(ans-n)/2<<'\n';
}
```

---

## 作者：_zuoqingyuan (赞：0)

继续点分治。

# 思路分析

这题和 [Tree](https://www.luogu.com.cn/problem/P4178) 这题类似，不一样的是本题对合法路径有两个限制（分别是长度限制和边权和限制）。

我们确定一个根 $R$，通过 dfs 找出每个节点 $x$ 距离 $R$ 的长度 $len_x$，以及 $x\to R$ 路径上的边权和 $dis_x$。仿照老方法，我们先求出 $dis_x+dis_y\le w,len_x+len_y\le l$ 的 $(x,y)$ 的对数（不考虑位于不同子节点子树内的限制），再依据容斥原理一一减去不合法的路径。

对于统计 $dis_x+dis_y\le w,len_x+len_y\le l$，我们先将所有节点按照 $dis_x$ 来排序，然后用双指针来限制第一维，第二维可以用树状数组解决。总时间复杂度 $O(n\log^2 n)$

注意树状数组无法在第 $0$ 位加减，所以树状数组在执行加减及求和操作时，应当把修改的位置向后移 $1$。同时注意树状数组的上界应当是 $n+1$。

# $\text{Code}$：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1e5+10;
int n,L,K,idx,ver[N],nxt[2*N],to[2*N],val[2*N],maxn[N],siz[N],root,vis[N],cnt,c[N];
long long ans;
struct node{
    int d,l;
}a[N];
bool cmp(node a,node b){
    return a.d<b.d;
}
void link(int x,int y,int z){
    to[++idx]=y,nxt[idx]=ver[x],ver[x]=idx,val[idx]=z;
}
void add(int x,int t){
    while(x<=n+1){
        c[x]+=t;
        x+=(x&-x);
    }
    return;
}
int ask(int x){
    int cnt=0;
    while(x>0){
        cnt+=c[x];
        x-=(x&-x);
    }
    return cnt;
}
int dfs_root(int x,int fa,int sum){
    siz[x]=1,maxn[x]=0;
    for(int i=ver[x];i;i=nxt[i]){
        if(vis[to[i]]||to[i]==fa)continue;
        siz[x]+=(siz[to[i]]=dfs_root(to[i],x,sum));
        maxn[x]=max(maxn[x],siz[to[i]]);
    }
    maxn[x]=max(maxn[x],sum-siz[x]);
    if(maxn[x]<maxn[root])root=x;
    return siz[x];
}
void dfs_dis(int x,int fa,int len,int dist){
    a[++cnt]=node{dist,len};
    add(len+1,1);
    for(int i=ver[x];i;i=nxt[i]){
        if(vis[to[i]]||to[i]==fa)continue;
        dfs_dis(to[i],x,len+1,dist+val[i]);
    }
    return;
}
long long calc(int u,int len,int dist){
    a[cnt=1]=node{dist,len};add(len+1,1);
    for(int i=ver[u];i;i=nxt[i]){
        if(vis[to[i]])continue;
        dfs_dis(to[i],u,len+1,dist+val[i]);
    }
    sort(a+1,a+1+cnt,cmp);
    int l=1,r=cnt;
    long long sum=0;
    while(l<r){
        while(a[l].d+a[r].d>K&&l<r)add(a[r].l+1,-1),r--;
        if(l!=r)add(a[l].l+1,-1),sum+=ask(L-a[l].l+1),l++;
    }
    add(a[l].l+1,-1);
    return sum;
}
void solve(int u){
    vis[u]=1;
    ans+=calc(u,0,0);
    for(int i=ver[u];i;i=nxt[i]){
        if(vis[to[i]])continue;
        ans-=calc(to[i],1,val[i]);
        root=0,dfs_root(to[i],u,siz[to[i]]);
        solve(root);
    }
    return;
}
int main(){
    scanf("%d %d %d",&n,&L,&K);
    for(int i=1,u,v;i<n;i++){
        scanf("%d %d",&u,&v);
        link(i+1,u,v),link(u,i+1,v);
    }
    maxn[0]=N;
    dfs_root(1,-1,n);
    solve(root);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Reunite (赞：0)

为什么要树套树？为什么要树状数组？

---
## 一
---

点对计数，首先考虑树分治，这里我选用点分治。套路地，考虑以一点为点分中心，计算其子树内所有点对的贡献。

一遍 dfs 获得所有子树内的信息，记三元组 $(l,w,top)$ 表示一点距离点分中心 $l$ 条边，边权和为 $w$，位于**点分中心的儿子 $top$ 的子树内**。则原问题可以转化为三维数点问题，即对于每一个点，有：$cnt((l'\le L-l,w' \le W-w,top' < top))$ 的贡献，$cnt(x,y,z)$ 表示符合条件的三元组个数，$top$ 的小于号限制是防止算重和同一子树内的错误合并。

直接暴力上 CDQ $+$ BIT 是朴素的，复杂度高达 $O(n\log_2^3n)$，在远古场是过不了的，也是很不优的。

发现 $top$ 的限制其实很松，如果我们先不考虑算重，那么 $top$ 实际上只有一个不相同的限制，而这个是可以直接一个桶 $O(1)$ 解决的。考虑我们这样做算重了那些信息，发现任意一点对含点分中心的只被算了一次，不含的被统计了两次，所以只需在预处理 CDQ 的时候统计一下能与点分中心合并的数量（$tot$），最终算得的结果改为：$ans \leftarrow \frac{(ans-tot)}{2}+tot$ 即可。

---
## 二
---

点分治是一个 $\log$，CDQ 因为我们没有使用任何数据结构，也是一个 $\log$，总时间复杂度 $O(n\log_2^2n)$，空间线性。时空吊打任何树形数据结构。


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

int n,L,W,root,tot;
int sz[100005];
int msz[100005];
bool mp[100005];
vector <pair <int,int>> g[100005];
ll ans,cnt;

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline void getroot(int u,int fa){
	sz[u]=1,msz[u]=0;
	for(auto tmp:g[u]){
		int v=tmp.first;
		if(mp[v]||v==fa) continue;
		getroot(v,u);
		sz[u]+=sz[v];
		msz[u]=max(msz[u],sz[v]);
	}
	msz[u]=max(msz[u],tot-sz[u]);
	if(msz[u]<msz[root]) root=u;
	return ;
}

int tt=0;
int h[100005];
struct node{int l,w,tp,op;};
node a[200005];
node b[200005];

inline void CDQ(int l,int r){
	if(l>=r) return ;
	int mid=(l+r)>>1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	int pos=l,s=0;
	for(int i=mid+1;i<=r;i++){
		while(pos<=mid&&a[pos].w<=a[i].w){
			s+=a[pos].op;
			h[a[pos].tp]+=a[pos].op;
			pos++;
		}
		if(!a[i].op) ans+=(s-h[a[i].tp]);
	}
	for(int i=l;i<pos;i++) h[a[i].tp]=0;
	int lf=l,rt=mid+1,tt=0;
	while(lf<=mid&&rt<=r){
		if(a[lf].w<a[rt].w||(a[lf].w==a[rt].w&&a[lf].op)) b[++tt]=a[lf++];
		else b[++tt]=a[rt++];
	}
	while(lf<=mid) b[++tt]=a[lf++];
	while(rt<=r) b[++tt]=a[rt++];
	for(int i=1;i<=tt;i++) a[l+i-1]=b[i];
	return ;
}

inline void getinformation(int u,int fa,int tp,int l,int w){
	if(l<=L&&w<=W) a[++tt]={L-l,W-w,tp,0},a[++tt]={l,w,tp,1},cnt++;
	for(auto tmp:g[u]){
		int v=tmp.first;
		if(v==fa||mp[v]) continue;
		getinformation(v,u,tp,l+1,w+tmp.second);
	}
	return ;
}

inline void work(int u){
	tt=0;
	for(auto tmp:g[u]){
		int v=tmp.first;
		if(mp[v]) continue;
		getinformation(v,u,v,1,tmp.second);
	}
	a[++tt]={0,0,u,1};
	sort(a+1,a+1+tt,[](node p,node q){return p.l==q.l?p.op>q.op:p.l<q.l;});
	CDQ(1,tt);
	return ;
}

inline void solve(int u){
	mp[u]=1;
	work(u);
	for(auto tmp:g[u]){
		int v=tmp.first;
		if(mp[v]) continue;
		tot=sz[v];
		root=0;
		getroot(v,u);
		solve(root);
	}
	return ;
}

int main(){
	in(n),in(L),in(W);
	for(int i=1;i<n;i++){
		int v,w;
		in(v),in(w);
		g[v].push_back({i+1,w});
		g[i+1].push_back({v,w});
	}
	sz[0]=msz[0]=(tot=n)+1;
	getroot(1,0);
	solve(root);
	printf("%lld\n",(ans-cnt)/2+cnt);

	return 0;
}
```

---

## 作者：happybob (赞：0)

看着就像点分治，但会发现和模板有些不同，多了一维。

我们还是照着模板的做法，分治求出重心，然后深搜找出每个点到重心的距离。不过我们这里要求两个，分别是长度 $d_u$ 和边权和 $p_u$。

考虑枚举一个点 $u$。如果这个点和另外一个点 $v$ 是满足条件的，那么必有 $d_u + d_v \leq l$ 且 $p_u + p_v \leq w$，最重要的，$u$ 和 $v$ 在以重心为根的两个子树中。

在两个子树中其实很好处理，我们先抛开这个条件，算出所有的 $u,v$，再减去每个子树中的数量即可。

那么如何求这个东西呢？枚举 $u$，我们知 $d_v \leq l - d_u$，$p_v \leq w - p_u$。容易发现这是个二位偏序，离线树状数组等一些数据结构均可维护。复杂度 $O(n \log^2 n)$。

不过具体还是有些细节的，例如树状数组可能统计到一对 $u=v$，又或者统计到两对 $u,v$ 和 $v,u$。注意细节即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
#define ll long long

const int N = 1e5 + 5;

vector<pair<int, ll> > G[N];

int n, l;
ll w;

bool del[N];
int sz[N], dis1[N], wc, tot;
ll dis2[N];
vector<pair<int, ll> > v;

void dfs_sz(int u, int fa)
{
	sz[u] = 0;
	if (del[u]) return;
	sz[u] = 1;
	for (auto j : G[u])
	{
		if (j.first != fa)
		{
			dfs_sz(j.first, u);
			sz[u] += sz[j.first];
		}
	}
}

void dfs_wc(int u, int fa)
{
	if (del[u]) return;
	int maxn = 0, sum = 1;
	for (auto& j : G[u])
	{
		if (j.first == fa) continue;
		dfs_wc(j.first, u);
		maxn = max(maxn, sz[j.first]);
		sum += sz[j.first];
	}
	maxn = max(maxn, tot - sum);
	if (maxn <= tot / 2)
	{
		wc = u;
	}
}

void dfs_dist(int u, int fa, int d1, ll d2, ll len)
{
	dis1[u] = dis2[u] = 0;
	if (del[u]) return;
	dis1[u] = d1 + 1;
	dis2[u] = d2 + len;
	v.emplace_back(make_pair(dis1[u], dis2[u]));
	for (auto& j : G[u])
	{
		if (j.first != fa)
		{
			dfs_dist(j.first, u, dis1[u], dis2[u], j.second);
		}
	}
}

int cc = 0;

class Bit
{
public:
	int tr[N];
	int lowbit(int x)
	{
		return x & -x;
	}
	void update(int x, int v)
	{
		while (x < N)
		{
			tr[x] += v;
			x += lowbit(x);
		}
	}
	int query(int x)
	{
		int res = 0;
		while (x)
		{
			res += tr[x];
			x -= lowbit(x);
		}
		return res;
	}
}bt;

inline bool cmp(const pair<int, ll>& x, const pair<int, ll>& y)
{
	return x.second < y.second;
}

vector<pair<int, ll> > QRY;

map<ll, vector<int> > mp;

inline ll calc(int u) 
{
	if (del[u])
	{
		return 0;
	}
	ll res = 0;
	dfs_sz(u, 0);
	tot = sz[u];
	wc = 0;
	dfs_wc(u, 0);
	u = wc;
	if (del[u]) return 0;
	del[u] = 1;
	if (!u) return 0LL;
	vector<pair<int, ll> > total;
	ll css = 0;
	for (auto& j : G[u])
	{
		if (del[j.first]) continue;
		mp.clear();
		QRY.clear();
		v.clear();
		dfs_dist(j.first, u, 0, j.second, 0);
		for (int i = 0; i < v.size(); i++)
		{
			total.emplace_back(v[i]);
			auto k = v[i];
			if (k.first <= l && k.second <= w)
			{
				res++;
			}
			if (l - k.first >= 0 && w - k.second >= 0)
			{
				QRY.emplace_back(make_pair(l - k.first, w - k.second));
				if (l - k.first >= k.first && w - k.second >= k.second)
				{
					css++;
				}
			}
		}
		sort(v.begin(), v.end(), cmp);
		for (auto i : QRY)
		{
			auto it = upper_bound(v.begin(), v.end(), i, cmp);
			if (it == v.begin())
			{
				continue;
			}
			else mp[(*(--it)).second].emplace_back(i.first);
		}
		for (int p = 0; p < v.size(); p++)
		{
			bt.update(v[p].first, 1);
			if (p == v.size() - 1 || v[p + 1].second != v[p].second)
			{
				for (auto pp : mp[v[p].second])
				{
					css -= bt.query(pp);
				}
			}	
			
		}
		for (auto& p : v)
		{
			bt.update(p.first, -1);
		}
	}
	QRY.clear();
	for (int i = 0; i < total.size(); i++)
	{
		auto k = total[i];
		if (l - k.first >= 0 && w - k.second >= 0)
		{
			QRY.emplace_back(make_pair(l - k.first, w - k.second));
			if (l - k.first >= k.first && w - k.second >= k.second) css--;
		}
	}
	mp.clear();
	sort(total.begin(), total.end(), cmp);
	for (auto i : QRY)
	{
		auto it = upper_bound(total.begin(), total.end(), i, cmp);
		if (it == total.begin())
		{
			continue;
		}
		else mp[(*(--it)).second].emplace_back(i.first);
	}
	for (int p = 0; p < total.size(); p++)
	{
		bt.update(total[p].first, 1);
		if (p == total.size() - 1 || total[p + 1].second != total[p].second)
		{
			for (auto pp : mp[total[p].second])
			{
				css += bt.query(pp);
			}
		}
		
	}
	for (auto& p : total)
	{
		bt.update(p.first, -1);
	}
	for (auto& j : G[u])
	{
		res += calc(j.first);
	}
	//cout << "!: " << u << " " << css << "\n";
	res += css / 2;
	return res;
}

signed main()
{
	//freopen("D:\\1233.txt", "r", stdin);
	//freopen("D:\\1233.ans", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> l >> w;
	for (int i = 1; i < n; i++)
	{
		int v;
		ll w;
		cin >> v >> w;
		G[i + 1].emplace_back(make_pair(v, w));
		G[v].emplace_back(make_pair(i + 1, w));
	}
	cout << calc(1) << "\n";
	return 0;
}
```


---

## 作者：Gaode_Sean (赞：0)

发现题解区的写法跟我的都不太一样呢..

如果只考虑 $i$ 到 $j$ 的边权不超过 $w$，那就是一个点分治模板（P4178）。

那么加上长度不超过 $l$ 的限制以后，该怎么解决？

考虑在计算每个重心（即子问题的根节点）对答案的贡献时，用一个树状数组来来维护每个点到根节点的长度，再来进行统计。

不过 模板 $+$ 树状数组 的做法有一个问题，那就是会算重，具体指的是同子树内的两个节点对答案的贡献可能会被多算。解决方法也不难想，枚举重心的每个儿子就行了。这样一来复杂度仍是正确的。

时间复杂度 $\mathcal{O(n \log^2 n)}$，空间复杂度 $\mathcal{O}(n)$。

[AC Code](https://codeforces.com/contest/293/submission/188824912)

---

## 作者：ExplodingKonjac (赞：0)

### [【原题链接】](https://www.luogu.com.cn/problem/CF293E)

看了题解区的 dalao 们很多用了树状数组统计答案，但我并不是很懂，所以写一了个（貌似）易懂一些的题解。

## 题目分析

看到路径统计，基本上就是点分治的题了。而这题确实就是点分治。

我们对于某个重心对应的子树，暴力求出其中每个点到根的 $dis_1$（经过边的长度）和 $dis_2$（经过边的权值）

然后，我们对于每一组 $dis_{1,u},\ dis_{2,u}$ 求出有多少个点能够与其匹配且满足题目条件。也就是说，我们要找到满足 $\displaystyle{\begin{cases}dis_{1,u}+dis_{1,v}\le l\\dis_{2,u}+dis_{2,v}\le w\end{cases}}$ 的 $v$ 的数量。

转换一下，就是 $\displaystyle{\begin{cases}dis_{1,v}\le l-dis_{1,u}\\dis_{2,v}\le w-dis_{2,u}\end{cases}}$，这是一个典型的二维偏序。

但是本蒟蒻并没有搞懂树状数组是怎么做的，所以还是选择将所有点按照 $dis_2$ 排序，然后用一个主席树来维护偏序。其中，主席树的下标代表 $dis_1$，而根的编号代表 $dis_2$。

然后我们对于每个 $u$ 查出来符合条件的 $v$ 的数量，记作 $cnt_u$，答案貌似就是 $\displaystyle\frac{\sum cnt_u}{2}$，不是吗？

但是这里有一个小细节：如果 $2dis_{1,u}\le l$ 且 $2dis_{2,u}\le w$，那么 $u$ 是可以自己和自己配对的。但是观察一下求 $cnt_u$ 的过程会发现这里 $(u,u)$ 只会被算一次。因此我们需要在满足上述条件时将 $cnt_u$ 再 $+1$ 就行了

总时间复杂度为 $O(n\log^2n)$，常数稍大。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/*
省略快读快写模板，即下面的 qin、qout。
*/

typedef long long LL;
const int INF=0x7fffffff;
int n,k1,k2;
LL ans;
struct Edge{ int to,w,nxt; }e[200005];
int cnt,head[100005];
inline void addEdge(int u,int v,int w)
	{ e[++cnt]=(Edge){v,w,head[u]},head[u]=cnt; }
int siz[100005],mxs[100005];
bool vis[100005];
void getRoot(int u,int &rt,int whole,int fa=0)
{
	siz[u]=1,mxs[u]=0;
	for(int i=head[u],v;v=e[i].to;i=e[i].nxt)
		if(v!=fa && !vis[v])
		{
			getRoot(v,rt,whole,u),siz[u]+=siz[v];
			mxs[u]=max(mxs[u],siz[v]);
		}
	mxs[u]=max(mxs[u],whole-siz[u]);
	if(mxs[u]<mxs[rt])	rt=u;
}
struct Dist
{
	LL d1,d2;
	Dist(LL _d1=0,LL _d2=0): d1(_d1),d2(_d2){}
	inline bool operator <(const Dist &b)const
		{ return d2<b.d2; }
}dis[100005];
int tot;
void dfs2(int u,LL d1,LL d2,int fa=0)
{
	if(d1>k1 || d2>k2)	return;
	dis[++tot]=Dist(d1,d2);
	for(int i=head[u],v;v=e[i].to;i=e[i].nxt)
		if(v!=fa && !vis[v])
			dfs2(v,d1+1,d2+e[i].w,u);
}
struct TreeNode{ int sum,lc,rc; }t[2000005];
int rt[100005];
#define LC t[i].lc
#define RC t[i].rc
void modify(int p,int &i,int l=0,int r=n)
{
	t[++cnt]=t[i],t[i=cnt].sum++;
	if(l!=r)
	{
		int mid=(l+r)>>1;
		if(mid>=p)	modify(p,LC,l,mid);
		else	modify(p,RC,mid+1,r);
	}
}
int query(int lq,int rq,int i,int l=0,int r=n)
{
	if(!i)	return 0;
	if(l>=lq && r<=rq)	return t[i].sum;
	int mid=(l+r)>>1,res=0;
	if(mid>=lq)	res+=query(lq,rq,LC,l,mid);
	if(mid<rq)	res+=query(lq,rq,RC,mid+1,r);
	return res;
}
LL calc(int u,LL d1,LL d2)
{
	tot=cnt=0,dfs2(u,d1,d2),sort(dis+1,dis+tot+1);
	LL res=0;
	for(int i=1;i<=tot;i++)	modify(dis[i].d1,rt[i]=rt[i-1]);
	for(int i=1;i<=tot;i++)
	{
		int v=upper_bound(dis+1,dis+tot+1,Dist(0,k2-dis[i].d2))-dis-1;
		res+=query(0,k1-dis[i].d1,rt[v]);
		if(2*dis[i].d1<=k1 && 2*dis[i].d2<=k2)	res++;
	}
	return res/2;
}
void dfs1(int u)
{
	ans+=calc(u,0,0),vis[u]=true;
	int rt;
	for(int i=head[u],v;v=e[i].to;i=e[i].nxt)
		if(!vis[v])
		{
			ans-=calc(v,1,e[i].w);
			rt=0,getRoot(v,rt,siz[v]);
			dfs1(rt);
		}
}
int main()
{
	qin>>n>>k1>>k2;
	for(int i=2;i<=n;i++)
	{
		int v,w;qin>>v>>w;
		addEdge(i,v,w),addEdge(v,i,w);
	}
	int rt=0;
	mxs[0]=INF,getRoot(1,rt,n),dfs1(rt);
	qout<<ans-n;
//	return qout.flush(),0;
}
```


---

## 作者：Y_B_X (赞：0)

题意：求树上满足 $i$ 到 $j$ 的**路径长度**不超过 $kk$ ，且**点权和**不超过 $k$ 的点对 $(i,j)$ 的个数   
###$Solution$  
首先，这道题明显是点分治，且与[这题](https://www.luogu.com.cn/problem/P4178)十分相像，只不过多了**路径长度**这一维的限制  
像那题一样，在点分治每层处理当前 $root$ 时，考虑枚举每条从 $root$ 出发的**各个子树**相互间产生的贡献，可避免容斥   
若某子树中的点自身以满足长度 $\leq kk$ ，且点权和 $\leq k$ ，直接计入答案  
然后对每个子树再将子树中的点到根的**点权和**排序，再统计与在它之前被遍历过的子树间的答案，便可写出一个朴素算法：
```cpp
//以下中d为点到根的点权和，dd为点到根的路径长，q为目前统计到的d与dd
void work(int x){
	cnt=0;
	for(int i=h[x];i;i=nextn[i]){
		int y=to[i];
		if(b[y])continue;
		tot=0,dfs(y,x,w[i],1);//处理出子树中的tmp[].d、tmp[].dd
		sort(tmp+1,tmp+tot+1);//对.d排序
		for(int j=1;j<=tot;j++){
			for(int i=1;i<=cnt&&q[i].d<=k-tmp[j].d;i++)if(q[i].dd<=kk-tmp[j].dd)ans++;//暴力
			if(tmp[j].d<=k&&tmp[j].dd<=kk)ans++;
		}
		merge(tmp+1,tmp+tot+1,q+1,q+cnt+1,q0+1);//合并两段有序数组，不用sort
		cnt+=tot;
		for(int i=1;i<=cnt;i++)q[i]=q0[i];//保证q中.d有序
	}
}
```
时间复杂度明显不对，考虑优化代码中暴力的那一段。  
然而我们观察到由于 $q$ 中 $d$ 的递增， $k-tmp[j].d$ 是可以用  $\operatorname{lowerbound}$ 求出在 $q$ 中的位置，记为 $pos$ 。  
那么，剩下的便是统计 $q[1···pos]$ 中 $q[l].dd\leq kk-tmp[j].dd$ 的 $l$ 的个数。  
而后，我们又能发现基于 $tmp[j].d$ 的递增， $pos$ 应该是递减的。  
于是，我们将 $tmp$ 反过来求， $pos$ 便可递增，于是在查询 $\leq kk-tmp[j].dd$ 的个数时就可以用**树状数组**，**一边插入，一边查询**。  
时间复杂度： $O(n\log^2 n)$  
总代码：( 当前在洛谷 $rank2$ )
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int n,m,nn,cnt,tot,kk,x,y,rt;
ll k,ww,ans;
int to[N],nextn[N],h[N];
int mxsize[N],size[N];
ll w[N];
struct dis{
	ll d;
	int dd;
	bool operator <(const dis &x)const{return x.d>d;}
}tmp[N],q[N],q0[N];
int t[N];
bool b[N];
int lowbit(int x){return x&(-x);}
void update(int x,int v){
	for(int i=x;i<=n;i+=lowbit(i))t[i]+=v;
}
ll inquiry(int x){
	ll res=0;
	for(int i=x;i;i-=lowbit(i))res+=t[i];
	return res;
}
void add(int x,int y,ll ww){
	cnt++;
	to[cnt]=y;
	nextn[cnt]=h[x];
	h[x]=cnt;
	w[cnt]=ww;
}
void findrt(int x,int anc){
	mxsize[x]=0;
	size[x]=1;
	for(int i=h[x];i;i=nextn[i]){
		int y=to[i];
		if(y==anc||b[y])continue;
		findrt(y,x);
		size[x]+=size[y];
		mxsize[x]=max(mxsize[x],size[y]);
	}
	mxsize[x]=max(mxsize[x],nn-size[x]);
	if(mxsize[x]<mxsize[rt])rt=x;
}
void dfs(int x,int anc,ll dis1,int dis_){
	tmp[++tot]=(dis){dis1,dis_};
	if(dis1<=k&&dis_<=kk)ans++;//直接计入答案
	for(int i=h[x];i;i=nextn[i]){
		int y=to[i];
		if(y==anc||b[y])continue;
		dfs(y,x,dis1+w[i],dis_+1);
	}
}
void work(int x){
	cnt=0;
	for(int i=h[x];i;i=nextn[i]){
		int y=to[i];
		if(b[y])continue;
		tot=0;
		dfs(y,x,w[i],1);
		sort(tmp+1,tmp+tot+1);
		int last=0;
		for(int j=tot;j>=1;j--)if(tmp[j].d<k&&tmp[j].dd<kk){//剪枝
			int pos=lower_bound(q+1,q+cnt+1,dis{k-tmp[j].d+1,0})-q;//应是小于等于k-tmp[j].d的最大位置
			while(q[pos].d>k-tmp[j].d)pos--;
			for(int l=last+1;l<=pos&&l<=cnt;l++)update(q[l].dd,1);
			ans+=inquiry(kk-tmp[j].dd);
			last=pos;
		}
		for(int l=1;l<=last&&l<=cnt;l++)update(q[l].dd,-1);
		merge(tmp+1,tmp+tot+1,q+1,q+cnt+1,q0+1);
		cnt+=tot;
		for(int i=1;i<=cnt;i++)q[i]=q0[i];
	}
}
void solve(int x){
	b[x]=1;
	work(x);
	for(int i=h[x];i;i=nextn[i]){
		int y=to[i];
		if(b[y])continue;
		rt=0,mxsize[0]=n;
		nn=size[y];
		findrt(y,x);
		solve(rt);
	}
}
main(){
	scanf("%d%d%lld",&n,&kk,&k);
	for(int i=1;i<n;i++){
		scanf("%d%lld",&y,&ww);
		add(i+1,y,ww),add(y,i+1,ww);
	}
	rt=0,nn=n;
	mxsize[0]=n;
	findrt(1,0);
	solve(rt);
	printf("%lld",ans);
}
```

---

