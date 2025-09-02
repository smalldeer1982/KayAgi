# Virus

## 题目描述

In Bubbleland a group of special programming forces gets a top secret job to calculate the number of potentially infected people by a new unknown virus. The state has a population of $ n $ people and every day there is new information about new contacts between people. The job of special programming forces is to calculate how many contacts in the last $ k $ days a given person had.

The new virus has an incubation period of $ k $ days, and after that time people consider as non-infectious. Because the new virus is an extremely dangerous, government mark as suspicious everybody who had direct or indirect contact in the last $ k $ days, independently of the order of contacts.

This virus is very strange, and people can't get durable immunity.

You need to help special programming forces to calculate the number of suspicious people for a given person (number of people who had contact with a given person).

There are 3 given inputs on beginning $ n $ where $ n $ is population, $ q $ number of queries, $ k $ virus incubation time in days. Each query is one of three types:

1. ( $ x $ , $ y $ ) person $ x $ and person $ y $ met that day ( $ x \neq y $ ).
2. ( $ z $ ) return the number of people in contact with $ z $ , counting himself.
3. The end of the current day moves on to the next day.

## 说明/提示

Pay attention if persons $ 1 $ and $ 2 $ had contact first day and next day persons $ 1 $ and $ 3 $ had contact, for $ k $ &gt; $ 1 $ number of contacts of person $ 3 $ is $ 3 $ (persons:1,2,3).

## 样例 #1

### 输入

```
5 12 1
1 1 2
1 1 3
1 3 4
2 4
2 5
3
2 1
1 1 2
1 3 2
2 1
3
2 1```

### 输出

```
4
1
1
3
1```

## 样例 #2

### 输入

```
5 12 2
1 1 2
1 1 3
1 3 4
2 4
2 5
3
2 1
1 1 2
1 3 2
2 1
3
2 1```

### 输出

```
4
1
4
4
3```

## 样例 #3

### 输入

```
10 25 2
1 9 3
2 5
1 1 3
1 3 1
2 2
1 8 3
1 5 6
3
1 9 2
1 8 3
2 9
1 3 1
2 5
1 6 4
3
3
2 4
3
1 10 9
1 1 7
3
2 2
3
1 5 6
1 1 4```

### 输出

```
1
1
5
2
1
1```

# 题解

## 作者：lory1608 (赞：5)

### 题意简述

给定一个 $n$ 个点的图，有 $q$ 次询问，**每一条边在其连边的第 $k$ 天开始时**被删去。

有三次询问

- $\texttt{1 x y}$ 将 $x$ 与 $y$ 连边。

- $\texttt{2 z}$ 询问 $z$ 所在的连通块大小。

- $\texttt{3}$ 进入下一天。

**注意：对于一条在第 $x$ 天连接的边，在第 $x+k$ 天开始时删除。（具体解释见样例）**


### 题解

如果没有 $k$ 的限制，就是一道并查集可以水过的题。

但是有了 $k$ 时，原题就相当于有加边，有删边，有查询连通块大小的操作，很容易想出可以用 $\texttt{lct}$ 维护，显然可以维护一颗最晚时间生成树，过了 $k$ 天之后，将那一天的没被删除的边删掉，就行了。

维护子树大小可以参见[大融合](https://www.luogu.com.cn/problem/P4219)。

然后这就是一道板题了。

```cpp
#pragma GCC optimize(2) 
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(u) for(int i=p[u];i!=-1;i=e[i].nxt)
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
#define rd (rand()<<16^rand())
using namespace std;
inline int gi()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return (f==1)?x:-x;
}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int maxn=6e5+5;
int n,q,k;
int val[maxn],fa[maxn],son[maxn][2],minv[maxn],root[maxn],tot,siz[maxn],t,si[maxn],temp[maxn];
bool rev[maxn];
inline bool nroot(int u)
{
	return son[fa[u]][0]==u||son[fa[u]][1]==u;
}
inline void pushup(int u)
{
	if(val[minv[son[u][0]]]<val[minv[son[u][1]]]&&val[minv[son[u][0]]]<val[u])minv[u]=minv[son[u][0]];
	else if(val[minv[son[u][1]]]<val[u])minv[u]=minv[son[u][1]];
	else minv[u]=u;
	siz[u]=siz[son[u][0]]+siz[son[u][1]]+si[u]+temp[u];
}
inline void pushdown(int u)
{
	if(rev[u])
	{
		swap(son[u][0],son[u][1]);
		rev[son[u][0]]^=1,rev[son[u][1]]^=1;
		rev[u]=0;
	}
}
inline void pushall(int u)
{
	if(nroot(u))pushall(fa[u]);
	pushdown(u);
}
inline void rotate(int x)
{
	int y=fa[x],z=fa[y],k=son[y][1]==x;
	if(nroot(y))son[z][son[z][1]==y]=x;
	fa[x]=z;
	son[y][k]=son[x][k^1];
	fa[son[x][k^1]]=y;
	son[x][k^1]=y;
	fa[y]=x;
	pushup(y);
	pushup(x);
}
inline void splay(int x)
{
	pushall(x);
	while(nroot(x))
	{
		int y=fa[x],z=fa[y];
		if(nroot(y))
		{
			if((son[z][1]==y)^(son[y][1]==x))rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
inline void access(int x)
{
	for(int y=0;x;y=x,x=fa[x])
	{
		splay(x);
		si[x]=si[x]+siz[son[x][1]]-siz[y];
		son[x][1]=y;
		pushup(x);
	}
}
inline int findroot(int x)
{
	access(x);
	splay(x);
	pushdown(x);
	while(son[x][0])x=son[x][0],pushdown(x);
	splay(x);
	return x;
}
inline void makeroot(int x)
{
	access(x);
	splay(x);
	rev[x]^=1;
}
inline void link(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
	fa[x]=y;
	si[y]+=siz[x];
	pushup(y);
}
inline void cut(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
	if(findroot(y)==x&&fa[y]==x&&!son[y][0])
	{
		fa[y]=son[x][1]=0;
		pushup(x);
	}
}
inline bool query(int x,int y)
{
	makeroot(x);
	return findroot(y)==x;
}
inline void split(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
}
set<PII>s[maxn];
vector<PII>v;
int tim[maxn],curr;
int main()
{
	memset(val,0x3f,sizeof(val));
	n=gi(),q=gi(),k=gi();
	int now=1,curr=0;
	v.push_back(PII(0,0));
	FOR(i,1,n)temp[i]=1;
	FOR(i,1,q)
	{
		int typ=gi();
		if(typ==1)
		{
			int x=gi(),y=gi();
			if(x<y)swap(x,y);
			s[now].insert(PII(x,y));
			++tot;
			tim[tot]=now;
			v.push_back(PII(x,y)); 
			if(query(x,y))
			{
				split(x,y);
				int now1=minv[y]-n;
				s[minv[y]].erase(PII(v[now1].first,v[now1].second));
				cut(v[now1].first,now1+n);
				cut(v[now1].second,now1+n);
				link(x,tot+n);
				link(y,tot+n);
				val[tot+n]=now;
			}
			else 
			{
				link(x,tot+n);
				link(tot+n,y);
				val[tot+n]=now;
			}
		}
		else if(typ==2)
		{
			int x=gi();
			makeroot(x);
			printf("%d\n",siz[x]);
		}
		else 
		{
			now++;
			if(now-k>=1)
			{
				int now1=now-k;
				while(tim[curr+1]==now1)
				{
					curr++;
					if(s[now1].count(v[curr]))s[now1].erase(v[curr]);
					cut(v[curr].first,curr+n);
					cut(v[curr].second,curr+n);
				}
			}
		}
	}
	return 0;
}
```

再补一个方法：线段树分治。

考虑每条边只会在一段时间出现，那么我们在对应线段树节点上打上标记，然后在最后dfs一次，用**可撤销的按秩合并的并查集即可**。

复杂度$\Theta(nlog^2n)$。

比lct快了5倍啊。

```cpp
//#pragma GCC optimize(4)
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(u) for(int i=p[u];i!=-1;i=e[i].nxt)
#define PII pair<int,int>
#define ll long long
#define pb push_back
#define rd (rand()<<16^rand())
#define gc getchar()//(_p1==_p2&&(_p2=(_p1=_buf)+fread(_buf,1,100000,stdin),_p1==_p2)?EOF:*_p1++)
using namespace std;
char _buf[100000],*_p1=_buf,*_p2=_buf;
inline int gi()
{
	int x=0,f=1;
	char ch=gc;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=gc;
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=gc;
	}
	return (f==1)?x:-x;
}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int maxn=5e5+5,maxt=5e5;
int n,k,q,x,y,typ[maxn];
struct state
{
	int x,y,sizx;
	state(int xx=0,int yy=0,int ss=0){x=xx,y=yy,sizx=ss;}
};
int fa[maxn],siz[maxn];
stack<state>stk;
vector<PII>que[maxn];
int ans[maxn];
inline int get(int x){if(x==fa[x])return x;else return get(fa[x]);}
inline void merge(int x,int y)
{
	x=get(x),y=get(y);
	if(x==y)return ;
	if(siz[x]>siz[y])swap(x,y);
	fa[x]=y;
	siz[y]+=siz[x];
	stk.push(state(x,y,siz[x]));
}
inline void del()
{
	int x=stk.top().x,y=stk.top().y,sizx=stk.top().sizx;
	siz[y]-=sizx;fa[x]=x;
}
struct segmentree
{
	static const int maxn=2e6+5;
	#define ls u<<1
	#define rs u<<1|1
	vector<PII>vec[maxn];
	inline void update(int u,int l,int r,int x,int y,int xx,int yy)
	{
		if(x<=l&&y>=r)return vec[u].pb(PII(xx,yy)),void();
		int mid=(l+r)>>1;
		if(x<=mid)update(ls,l,mid,x,y,xx,yy);
		if(y>mid)update(rs,mid+1,r,x,y,xx,yy);
	}
	inline void dfs(int u,int l,int r)
	{
		int cnt=stk.size();
		for(auto x:vec[u])merge(x.first,x.second);
		if(l==r)
		{
			for(auto x:que[l])
			ans[x.first]=siz[get(x.second)];
		}
		else
		{
			int mid=(l+r)>>1;
			dfs(ls,l,mid);
			dfs(rs,mid+1,r);
		}
		while(stk.size()>cnt)del(),stk.pop();
	}
}tree;
int a[maxn],b[maxn],cur[maxn];
int temp[maxn];
inline void init()
{

}
inline void input()
{
	n=gi(),q=gi(),k=gi();
	int now=1;
	int counter=0;
	FOR(i,1,n)fa[i]=i,siz[i]=1;
	FOR(i,1,q)
	{
		typ[i]=gi();
		if(typ[i]==1)
		{
			a[i]=gi(),b[i]=gi();
			cur[i]=now;
			//tree.update(1,1,q,i,min(maxt,now+k-1),x,y);
		}
		else if(typ[i]==2)
		{
			int x=gi();
			que[i].pb(PII(++counter,x));
		}
		else now++,temp[now]=i;
	}
	FOR(i,1,q)
	{
		if(cur[i]+k>now)tree.update(1,1,q,i,q,a[i],b[i]);
		else tree.update(1,1,q,i,temp[cur[i]+k],a[i],b[i]);
	}
	tree.dfs(1,1,q);
	FOR(i,1,counter)printf("%d\n",ans[i]);
}
inline void solve()
{

}
int main()
{
	init();
	input();
	solve();
	return 0;
}
```

虽然有很简单的办法，但是无脑的方法好想啊！

---

## 作者：Walrus (赞：2)

又一次复习了线段树分治。

首先这个线段树分治应该很一眼，因为操作一对于边的出现时间做出了限制。

**首先考虑将 $[1,q]$ 作为操作的时间轴，这里要注意区分，题目给出的「连边的第 $k$ 天」并不是时间戳，一定要区分清楚。**

其实上述题目描述给出的时间将我们应该维护的时间轴划分成了若干个段，所以连上的边的出现与消失时间应该对应段的左右端点而不是题目中所谓的「出现时间」。

接下来就是板子了，对于某一个点所在的集合大小这个查询肯定可以用并查集维护，至于在线段树分治上由于普通并查集不支持撤销所以要用可撤销并查集，可撤销的并查集又不能路径压缩，所以直接按秩合并。

然后对于 $ask$ 这块，大概就是这么写的，记录下时间戳和要查的东西就可以了。大概是这样：
```cpp
void ask(int p, int l, int r) {
	int S = DSU.st.size();
	for(auto ed : e[p]) {
		int x = ed.fi, y = ed.se;
		DSU.merge(x, y);
	}
	if(l == r) {
		for(auto ed : g[l]) ans[ed.fi] = DSU.siz[DSU.get(ed.se)];//<----
	}
	else ask(ls, l, mid), ask(rs, mid + 1, r);
	DSU.undo(S);
}
```

然后就是注意一下题目中**最后一天**时的区间右端点是 $q$ 就可以了。

[code](https://www.luogu.com.cn/paste/plsgmobm)

---

## 作者：E1_de5truct0r (赞：1)

首先看到了插入和删除，考虑线段树分治。
    
然后无非就是动态的维护一个图每个点所在的连通块大小，可撤销并查集即可了，为了方便可以直接按大小而不是深度合并。
   
特别注意一下：每一天的操作也有先后顺序，因此不能按天数弄线段树分治，要按操作编号。
    
复杂度 $O(n \log^2 n)$。

[Code](https://codeforces.com/contest/1423/submission/202473245)

---

## 作者：Leap_Frog (赞：1)

### P.S.
最优解喜提 +1

### Description.
略

### Solution.
考虑题目没有强在，直接离线。  
看到加边删边操作，直接线段树分治。  
~~比起 LCT 来说，常数也小，跑的也快，也更好写~~。  

然后就做完了。  
如果不会线段树分治可以参考 [这个](https://www.luogu.com.cn/problem/solution/P5787)  

实现的时候还有一个细节，就是你按照天来建时间线段树和按每个询问来建线段树应该都可以。  
如果按天的话复杂度一样，但是常数应该会更优一点。  
下面代码是按照询问来建立线段树的。  

复杂度 $O(q\cdot\log q)$，复杂度有点高，但是为什么跑过了楼上的 $O(q\log n)$ 了呢（bushi
### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),bz=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) bz=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	bz?x=-x:x;
}/*}}}*/
int n,Q,K,p3[1000005],p3t,sz[100005],fa[100005];
struct node{int fg,x,y;}q[500005];vector<pair<int,int> >T[2000005];
struct dsub{int x,y,sz;}ds[100005];int dt=0;
inline int getf(int x) {return fa[x]==x?x:getf(fa[x]);}
inline void mrg(int x,int y)
{
	x=getf(x),y=getf(y);if(x==y) return;else if(sz[x]>sz[y]) swap(x,y);
	ds[++dt]=(dsub){x,y,sz[y]},sz[y]+=sz[x],fa[x]=y;
}
inline void pop(int q) {while(dt>q) fa[ds[dt].x]=ds[dt].x,sz[ds[dt].y]-=sz[ds[dt].x],dt--;}
inline void modif(int x,int l,int r,int dl,int dr,pair<int,int>dc)
{
	if(l>dr||dl>r) return;else if(dl<=l&&r<=dr) return T[x].push_back(dc);
	modif(x<<1,l,(l+r)>>1,dl,dr,dc),modif(x<<1|1,((l+r)>>1)+1,r,dl,dr,dc);
}
inline void solve(int x,int l,int r)
{
	int ww=dt;for(auto z:T[x]) mrg(z.first,z.second);
	if(l==r) return (q[l].fg==2?printf("%d\n",sz[getf(q[l].x)]):0),pop(ww);
	solve(x<<1,l,(l+r)>>1),solve(x<<1|1,((l+r)>>1)+1,r),pop(ww);
}
int main()
{
	read(n),read(Q),read(K);for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
	for(int i=1;i<=Q;i++) read(q[i].fg),(q[i].fg<3?read(q[i].x),0:0),(q[i].fg<2?read(q[i].y),0:0);
	p3[++p3t]=1;for(int i=1;i<=Q;i++) if(q[i].fg==3) p3[++p3t]=i;
	for(int i=p3t+1;i<=p3t+K;i++) p3[i]=Q+1;
	for(int i=1;i<=Q;i++) if(q[i].fg==1)
	{
		int x=i,y=p3[upper_bound(p3+1,p3+p3t+1,i)-p3-1+K];
		modif(1,1,Q,x,y-1,make_pair(q[i].x,q[i].y));
		//printf("%d <-> %d : %d ~ %d\n",q[i].x,q[i].y,x,y-1);
	}
	return solve(1,1,Q),0;
}
```

---

