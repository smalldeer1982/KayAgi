# [PA 2015] 健身房 / Siłownia

## 题目背景


译自 [PA 2015](https://sio2.mimuw.edu.pl/c/pa-2015-1/p/) R5.


## 题目描述

健身房里有 $k$ 个器材。

有 $n$ 个人预约了健身。第 $i$ 个人预约给定了 $l_i,r_i,p_i$，意思是要分配给他 $l_i,l_{i}+1,\cdots,r_i$ 中的一个（记为 $x$），他在第 $x$ 个小时中用器材 $p_i$ 健身。

同一时间不能有两个人用同一个健身器材。此外，老板还希望让健身房里没人的时刻尽量多，这样可以节约电费。

构造一组最优解。


## 说明/提示

- $1\le n\le 10^6$；
- $1\le k\le 10^9$；
- $1\le l_i\le r_i\le 10^9$；
- $1\le p_i\le k$。

## 样例 #1

### 输入

```
4 2
1 3 1
1 1 1
1 3 2
3 3 2```

### 输出

```
2
3
1
1
3```

## 样例 #2

### 输入

```
3 1
1 2 1
1 2 1
1 2 1```

### 输出

```
NIE```

# 题解

## 作者：Wuyanru (赞：13)

小清新贪心。

[题目链接](https://www.luogu.com.cn/problem/P11820)。

## 题意

现在有 $n$ 个人和 $k$ 个健身器材。

第 $i$ 个人需要在 $[l_i,r_i]$ 中的任意一个时刻去健身房 $p_i$，一个健身房同一时刻只能有最多一个人。

一个方案的代价是，有多少时刻，满足这个时刻中健身房里有人。

构造一个代价最小的方案。

$n\le 10^6$。

## 题解

首先来考虑，假如不存在两个人 $i,j$，使得 $r_i=r_j$ 且 $p_i=p_j$，答案怎么算。

可以发现这是一个贪心，因为每一个人进入健身房的时间应当是越晚越好，这样能让更多的人一起被安排。

具体过程是这样的，我们从小到大枚举时间 $t$。

首先若存在 $l_i=t$，这说明我们可以安排 $i$ 这个人了，将 $i$ 这个人加到 $p_i$ 这个 set 里面。

若存在一个人 $i$，满足 $r_i=t$，并且 $i$ 这个人还没有安排健身房。

那么我们知道，$t$ 这个时刻就一定得有人在健身房了，我们考虑安排哪些人去健身房。

显然，对于同一类人（如果 $p$ 相同我们就认为是一类人），应该选取一个 $r_i$ 最小的人去健身房，直接 set 里面找就好了。

显然，关键的 $t$ 只有 $O(n)$ 个（即每一个人的左右端点），那么这是一个 $O(n\log n)$ 的做法。

---

考虑为啥不能用这个做法做原题。

因为如果存在两个人 $i,j$，有 $r_i=r_j$，并且 $p_i=p_j$。

那么我们在扫到 $r_i-1$ 这个时刻的时候，就必须要安排一个人上去，否则 $r_i$ 再安排的时候安排不下就爆炸了。

这个时候有一个方法是拿线段树或者什么东西维护一下，可能能做，但我们有更牛的做法。

假设此时存在这样的一对 $i,j$，我们不妨假设 $l_i\le l_j$。

那么我们直接令 $r_i\gets r_i-1$ 就好了。

为什么呢，考虑我们的限制说明了有 $[l_j,r_j]\subseteq [l_i,r_i]$，也就是说 $j$ 能去健身房的时刻 $i$ 也能去。

那么如果 $i$ 在 $r_i$ 这个时刻去了健身房，我们直接让 $i,j$ 两个人去健身房的时刻交换一下，显然交换完的方案依然合法。

所以如果有解，我们就一定能够构造出，$i$ 不在 $r_i$ 时刻去健身房的方案。

那么我们一直做这个操作，做到不存在这样的 $i,j$ 为止。

假设此时存在一个 $k$ 满足 $l_k>r_k$，那么无解。

否则我们可以跑上面那个 set 维护的贪心。

那么如何快速做这个操作呢，把所有 $p_i$ 相同的人放在一起，然后按照 $l_i$ 从大到小进行排序，然后 set 维护连续段即可。

时间复杂度 $O(n\log n)$，并且我们只使用了 set，这实在是太牛了！

## 题解

```c++
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3fll
#define debug(x) cerr<<#x<<"="<<x<<endl
using namespace std;
using ll=long long;
using ld=long double;
using pli=pair<ll,int>;
using pi=pair<int,int>;
template<typename A>
using vc=vector<A>;
template<typename A,const int N>
using aya=array<A,N>;
inline int read()
{
	int s=0,w=1;char ch;
	while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline ll lread()
{
	ll s=0,w=1;char ch;
	while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
struct node
{
	int l,r,p,id;
}a[1000005];
struct nod
{
	int id,op,t;
	nod(int id=0,int op=0,int t=0):id(id),op(op),t(t){}
};
set<pi>rest[1000005];
set<int>S;
int qans[1000005];
map<int,int>to;
vc<nod>event;
int n,k,c;
set<pi>wtf;
inline void cover(int tim)
{
	vc<int>P;
	for(int i:S)
	{
		qans[a[(*rest[i].begin()).second].id]=tim;
		rest[i].erase(rest[i].begin());
		if(!rest[i].size()) P.push_back(i);
	}
	for(int i:P) S.erase(i);
}
inline int get(int v)
{
	int ans;
	auto it=wtf.upper_bound(pi(v+1,-1));
	if(it==wtf.begin()||(--it)->second<v) ans=v,wtf.insert(pi(v,v));
	else
	{
		int L=it->first,R=it->second;wtf.erase(it);
		while(true)
		{
			it=wtf.upper_bound(pi(v,-1));
			if(it==wtf.begin()||(--it)->second<L-1){ ans=L=L-1;break;}
			L=it->first;wtf.erase(it);
		}
		wtf.insert(pi(L,R));
	}
	return ans;
}
int main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++) a[i].l=read(),a[i].r=read(),a[i].p=read(),a[i].id=i;
	sort(a+1,a+n+1,[](node a,node b)
	{
		if(a.p!=b.p) return a.p<b.p;
		return a.l>b.l;
	});

	for(int i=1;i<=n;i++)
	{
		if(!to.count(a[i].p)) to[a[i].p]=++c;
		a[i].p=to[a[i].p];
	}

	for(int l=1,r;l<=n;l=r)
	{
		r=l+1;
		while(r<=n&&a[r].p==a[l].p) r++;
		// printf("%d ~ %d\n",l,r-1);
		for(int j=l;j<r;j++)
		{
			a[j].r=get(a[j].r);
			if(a[j].l>a[j].r)
			{
				printf("NIE\n");
				return 0;
			}
			event.push_back(nod(j,0,a[j].l));
			event.push_back(nod(j,1,a[j].r));
		}
		wtf.clear();
	}

	sort(event.begin(),event.end(),[](nod a,nod b)
	{
		if(a.t!=b.t) return a.t<b.t;
		return a.op<b.op;
	});

	// for(int i=1;i<=n;i++) printf("%d %d %d\n",a[i].l,a[i].r,a[i].p);

	int ans=0;
	for(auto p:event)
	{
		if(p.op==0)
		{
			int q=p.id;
			rest[a[q].p].insert(pi(a[q].r,q));
			S.insert(a[q].p);
		}
		else
		{
			int q=p.id,P=a[q].p;
			if(rest[P].find(pi(a[q].r,q))!=rest[P].end()) ans++,cover(a[q].r);
		}
	}

	printf("%d\n",ans);
	for(int i=1;i<=n;i++) printf("%d\n",qans[i]);
	return 0;
}
```

---

## 作者：Purslane (赞：4)

# Solution

这也太难了吧。参考了 Wuyanru 的题解（其实都是自己想的，但是最关键的一步“意识到它是贪心”是从题解中得到的。。。）。 /bx

首先要做一些基础的贪心。

比如我们不管他们要使用哪种器材，只是让每个人都能在健身房里呆着，最少用多少天。

做法实际上是简单的：扫描时间线，维护一个 `set` 表示当前需要健身的人，动态加人。如果有一个人到达时间上界了，就将 `set` 清空。正确性显然。

考虑加上不同的器材。还是考虑使用类似的方法，如果两个人使用的器材一样，但是时间上界不一样，显然贪心的时候取出时间上界最小的那个人即可。（证明也是显然的，因为上界越大越容易赶上后面的“便车”）。

但是，如何处理上界相同且器材相同的情况呢。这时候看起来没有优劣之分。

考虑强行修改使得上界互不相同。注意到 $l$ 越小，他就能有更多的机会，所以我们在 $r$ 相同时让对应 $l$ 更小的减一即可。

常数有点大，不过能过。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,k,ans,lsh[MAXN],tot,x[MAXN],tp[MAXN];
struct LIM {int l,r,id;}t[MAXN];
vector<LIM> lim[MAXN];
vector<LIM> fin;
map<int,vector<LIM>> add,del;
set<pair<int,int>> alive[MAXN];
set<int> cur;
void insert(int id,int u,int idx) {
	alive[id].insert({u,idx});
	if(alive[id].size()==1) cur.insert(id);
	return ;	
}
void ddel(int id,int u,int idx) {
	alive[id].erase({u,idx});
	if(alive[id].size()==0) cur.erase(id);
	return ;
}
void deal(int t) {
	set<int> occ,prev;
	sort(lim[t].begin(),lim[t].end(),[](LIM A,LIM B) {
		return A.l>B.l;	
	});
	for(auto pr:lim[t]) {
		int l=pr.l,r=pr.r,id=pr.id;
		if(occ.find(r)==occ.end()) {
			occ.insert(r),prev.insert(r-1);
			fin.push_back({l,r,id});
		}
		else {
			while(1) {
				auto it=--prev.lower_bound(r);
				if(occ.find(*it)!=occ.end()) {prev.erase(it);continue ;}
				if(l>*it) return cout<<"NIE",exit(0);
				r=*it,prev.insert(r-1);
				break ;
			}
			fin.push_back({l,r,id}),occ.insert(r);
		}
	}
	vector<LIM>().swap(lim[t]);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n) cin>>t[i].l>>t[i].r>>tp[i],t[i].id=i,lsh[++tot]=tp[i];
	sort(lsh+1,lsh+tot+1),tot=unique(lsh+1,lsh+tot+1)-lsh-1;
	ffor(i,1,n) tp[i]=lower_bound(lsh+1,lsh+tot+1,tp[i])-lsh,lim[tp[i]].push_back(t[i]);
	ffor(i,1,tot) deal(i);
	set<int> kt;
	for(auto pr:fin) add[pr.l].push_back(pr),del[pr.r].push_back(pr),kt.insert(pr.l),kt.insert(pr.r);
	for(auto id:kt) {
		int tt=id;
		if(add.count(id)) for(auto pr:add[id]) insert(tp[pr.id],pr.r,pr.id);
		int flg=0;
		if(del.count(id)) for(auto pr:del[id]) if(alive[tp[pr.id]].find({pr.r,pr.id})!=alive[tp[pr.id]].end()) flg=1;
		if(flg) {
			ans++;
			vector<pair<int,pair<int,int>>> del;
			for(auto id:cur) del.push_back({id,*alive[id].begin()});
			for(auto id:del) {
				x[id.second.second]=tt;
				ddel(id.first,id.second.first,id.second.second);
			}
		}
	}
	cout<<ans<<'\n';
	ffor(i,1,n) cout<<x[i]<<'\n';
	return 0;
}
```

---

## 作者：My__L (赞：2)

[题目链接](https://www.luogu.com.cn/problem/P11820)

题目大意：给定 $n$ 个带有颜色 $p$ 的区间 $[l,r]$，要求用最少的点覆盖所有区间（一个点不可以同时覆盖多个颜色相同的区间）$n\in[1,10^6],l,r,p\in[1,10^9]$

考虑没有颜色限制的做法。没有颜色限制时就维护一个集合，扫描线将所有区间按照左端点的顺序加入集合，若集合中存在一个区间的右端点恰好是当前的时间点 $t$，那么就用该点 $t$ 覆盖当前集合中的所有区间并清空集合。

考虑颜色的限制。对于在集合中的区间 $i,j$ 满足 $p_i=p_j,r_i<r_j$ 选择区间 $i$ 一定不比区间 $j$ 劣；若 $p_i=p_j,r_i=r_j,l_i<l_j$ ，则必有一个区间需在 $t-1$ 处被覆盖，直接将 $r_i$ 修改为 $r_i-1$ 即可。若是修改 $r_j$ ，可能会出现 $l_j>r_j$ 的情况导致区间不合法。
***
预处理颜色的限制时将所有区间按颜色为第一关键字、左端点为第二关键字降序排序，按颜色段考虑，若当前区间的右端点 $r$ 出现过则将其修改为 $r$ 左边最大的未出现过的数。可以用 set 维护出现过的 $r$ 形成的连续段，修改即改为 $r$ 所在的连续段的左端点-1

在扫描线的过程中，因为相同颜色的区间只会选择 $r$ 较小的那个区间，所以可以用 set 维护一个大集合与若干个颜色区间集合，大集合中只存颜色集合中 $r$ 最小的元素。我曾尝试只用一个队列维护整个集合，但这样元素的插入次数可以卡到 $n^2$ 

本人代码实现非常丑陋，就不放了

---

