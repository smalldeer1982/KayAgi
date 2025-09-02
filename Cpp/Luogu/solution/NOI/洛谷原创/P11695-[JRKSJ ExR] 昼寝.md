# [JRKSJ ExR] 昼寝

## 题目背景

![安静的午后](https://cdn.luogu.com.cn/upload/image_hosting/7i2traxd.png)

## 题目描述

给定 $n,m$，你需要维护一个 $[1,n)$ 的数轴上区间的初始为空的**可重集合**，支持三种操作共 $m$ 次：

1. 插入一个区间 $[l,r)$。
2. 删除第 $t$ 次操作插入的区间。
3. 给出一个区间 $[l,r)$，判断当前可重集合中是否存在一个子集，使得子集中所有区间的并恰好是 $[l,r)$。

## 说明/提示

### 样例解释

对于样例 $1$，第一次询问时的可重集合为 $\{[1,3),[2,4)\}$，$[1,3)\cup [2,4)=[1,4)$。

第二次询问时的可重集合为 $\{[2,4)\}$，显然不存在满足条件的子集。

### 数据规模与约定

**本题采用捆绑测试。**

| $\mathrm{Subtask}$ | $n\le$ | $m\le$ | 特殊性质 |分数 | 
| :-----: | :-----: | :-----: | :-----: | :-----: | 
| $1$ | $10^3$ | $10^3$ | |$10$ | 
| $2$ | $10^6$ | $5\times 10^5$ |$\text A$ |$15$ | 
| $3$ | $10^6$ | $5\times 10^5$ | $\text B$|$30$ | 
| $4$ | $2\times 10^5$ | $2\times 10^5$ | |$10$ | 
| $5$ | $10^6$ | $5\times 10^5$ | |$35$ |

特殊性质 $\text A$：保证不存在 $2$ 操作，且所有 $1$ 操作在所有 $3$ 操作之前。

特殊性质 $\text B$：保证不存在 $2$ 操作。

对于所有数据，保证 $2\le n\le 10^6$，$1\le m\le 5\times 10^5$，$1\le l<r\le n$。

保证所有操作 $2$ 对应的 $t$ 都是此前的操作 $1$ 且所有 $t$ 互不相同。

## 样例 #1

### 输入

```
5 5
1 1 3
1 2 4
3 1 4
2 1
3 1 4```

### 输出

```
Y
N```

## 样例 #2

### 输入

```
9 17
1 6 9
1 1 8
1 5 7
1 6 8
1 8 9
3 4 5
3 1 7
3 8 9
1 4 9
3 1 8
3 1 7
1 6 9
3 2 6
2 2
1 1 3
3 1 2
1 4 6```

### 输出

```
N
N
Y
Y
N
N
N```

# 题解

## 作者：Rainbow_qwq (赞：14)

下面把 $r\to r-1$。则问题转化为：选择所有被 $[ql,qr]$ 包含的区间，判断是否能覆盖 $[ql,qr]$ 内的所有整点。

下称一个操作的范围为 $[ql,qr,tl,tr]$（区间，时间区间），一个询问为 $[ql,qr,t]$。

先对序列分治，计算所有跨过 $mid$ 的询问。

考虑先算跨过 $mid$ 的区间的贡献。对于询问 $[ql,qr,t]$，能覆盖到的最小位置 $x$ 就是存在一个操作 $[x,r,tl,tr]$ 使得 $x\in [ql,mid],r\le qr,t\in [tl,tr]$。对时间维度扫描线，线段树二分即可。

然后考虑所有在两边的区间，能不能把剩下的空隙填上。假设考虑左边，我们对时间轴开一个线段树，扫描序列维度（$i=l\to mid$）。

每次扫到一个询问就放在线段树上，维护当前这个询问的右端点到了哪里。扫到一个操作就是区间取 max。做完 $[i,r]$ 的所有操作后，不断取线段树上最小值，如果 $<i$ 了就弹掉。

时间复杂度 $O(q\log^2 q)$。

```cpp
struct Max{
	int x;
	Max (int xx=-inf){
		x=xx;
	}
};
Max operator +(Max a,Max b){
	return Max(max(a.x,b.x));
}

struct Min{
	int x;
	Min (int xx=inf){
		x=xx;
	}
};
Min operator +(Min a,Min b){
	return Min(min(a.x,b.x));
}

struct opMin{
	int x;
	opMin (int xx=inf){
		x=xx;
	}
};

struct opMax{
	int x;
	opMax (int xx=-inf){
		x=xx;
	}
};

void operator +=(opMax &a,opMax b){
	a.x=max(a.x,b.x);
}
void operator +=(opMin &a,opMin b){
	a.x=min(a.x,b.x);
}

void operator +=(Min &a,opMax b){
	a.x=max(a.x,b.x);
}
void operator +=(Max &a,opMin b){
	a.x=min(a.x,b.x);
}

int n,q,m,m2;
int qwq[maxn];
int ql[maxn],qr[maxn],dl[maxn],tl[maxn],tr[maxn],tim[maxn];

struct node{
	int ql,qr,tl,tr;
};

int fid[maxn];

int c[maxn];
bool ask(int l,int r){
	For(i,l-1,r+1) c[i]=0;
	For(i,1,m) if(!dl[i]) {
		if(ql[i]>=l && qr[i]<=r) ++c[ql[i]],--c[qr[i]+1];
	}
	For(i,l,r) {
		c[i]+=c[i-1];
		if(!c[i]) return 0;
	}
	return 1;
}

bool res[maxn];

int dest(vector<node>&ts,vector<node>&qs){
	vi tmp;
	for(auto [ql,qr,tl,tr]:ts) tmp.pb(tl),tmp.pb(tr);
	for(auto [ql,qr,tl,tr]:qs) tmp.pb(tl);
	sort(ALL(tmp));
	tmp.erase(unique(ALL(tmp)),tmp.end());
	auto V=[&](int x){
		x=lower_bound(ALL(tmp),x)-tmp.begin();
		return x+1;
	};
	for(auto &[ql,qr,tl,tr]:ts) tl=V(tl),tr=V(tr);
	for(auto &[ql,qr,tl,tr]:qs) tl=V(tl);
	return tmp.size();
}

multiset<int>s[maxn];

vi in[maxn],ot[maxn],qq[maxn];

int tol[maxn],tor[maxn];
int qid[maxn];

int t3[maxn],t4[maxn];

void solve(int l,int r,vector<node>ts,vector<node>qs)
{
	if(!SZ(qs)) return;
	
//	cout<<"solve "<<l<<" "<<r<<endl;
	
	int m=dest(ts,qs);
	int mid=l+r>>1;
	
//	cout<<"m: "<<m<<endl;
	
	segt1<Min>T1;
	segt1<Max>T2;
	
	vector<node>QL,QR,TL,TR;
	
	For(i,1,m) s[i].clear(),in[i].clear(),ot[i].clear(),qq[i].clear();
	
	For(i,0,SZ(ts)-1){
		auto [ql,qr,tl,tr]=ts[i];
		if(ql<=mid && qr>mid) in[tl].pb(i),ot[tr].pb(i);
		else if(qr<=mid) TL.pb(ts[i]);
		else TR.pb(ts[i]);
	}
	bool hav=0;
	For(i,0,SZ(qs)-1){
		auto [ql,qr,tl,tr]=qs[i];
		if(ql<=mid && qr>mid) qq[tl].pb(i),tol[tr]=mid+1,tor[tr]=mid;
		else if(qr<=mid) QL.pb(qs[i]);
		else QR.pb(qs[i]);
	}
	
	T1.init(mid-l+1);
	T2.init(r-mid);
	
	auto gval=[&](int x){
		if(x<=mid){
			return s[x].empty()? inf:*s[x].begin();
		}else{
			return s[x].empty()?-inf:*s[x].rbegin();
		}
	};
	
	auto upd1=[&](int x){
		if(x<=mid){
			T1.upd(x-l+1,{gval(x)});
		}else{
			T2.upd(x-mid,{gval(x)});
		}
	};
	
	For(i,1,m){
		for(auto id:in[i]){
			auto [ql,qr,tl,tr]=ts[id];
			s[ql].insert(qr);
			s[qr].insert(ql);
			upd1(ql);
			upd1(qr);
		}
		for(auto id:qq[i]){
			auto [ql,qr,tl,ii]=qs[id];
		//	cout<<"ID "<<id<<endl;
			tol[ii]=T1.findL(ql-l+1,mid-l+1,[&](Min t){
				return t.x<=qr;
			});
			tor[ii]=T2.findR(1,qr-mid,[&](Max t){
				return t.x>=ql;
			});
			tol[ii]+=l-1;
			tor[ii]+=mid;
			if(!(tol[ii]>=l && tol[ii]<=mid)) tol[ii]=mid+1;
			if(!(tor[ii]>=mid+1 && tor[ii]<=r)) tor[ii]=mid;
		}
		for(auto id:ot[i]){
			auto [ql,qr,tl,tr]=ts[id];
		//	cout<<"del: "<<ql<<" "<<qr<<endl;
			s[ql].erase(s[ql].find(qr));
			s[qr].erase(s[qr].find(ql));
		//	cout<<"done.\n";
			upd1(ql);
			upd1(qr);
		}
	}
	
	For(i,0,m) in[i].clear(),ot[i].clear(),qq[i].clear();
	
//	cout<<"QWQ\n";
	
	segt<Min,opMax>T3;
	segt<Max,opMin>T4;
	
	T3.init(m);
	T4.init(m);
	For(i,l,r) in[i].clear(),qq[i].clear();
    
	For(i,0,SZ(TL)-1){
		auto [ql,qr,tl,tr]=TL[i];
		in[ql].pb(i);
	}
	For(i,0,SZ(qs)-1){
		auto [ql,qr,tl,tr]=qs[i];
		if(ql<=mid && qr>mid) qq[ql].pb(i),qq[qr].pb(i);
	}
	For(i,l,mid){
		for(auto id:qq[i]){
			auto [ql,qr,tl,ii]=qs[id];
			qid[tl]=ii;
			T3.upd(tl,{i-1});
		}
		for(auto id:in[i]){
			auto [ql,qr,tl,tr]=TL[id];
			T3.mdf(tl,tr,{qr});
		}
		while(1){
			int p=T3.findL(1,m,[&](Min t){
				return t.x<i;
			});
			if(!(p>=1&&p<=m)) break;
			int ii=qid[p];
			if(i<tol[ii]) res[ii]=0;
			T3.upd(p,{inf});
		}
	}
	For(i,l,mid) in[i].clear(),qq[i].clear();
	
	For(i,0,SZ(TR)-1){
		auto [ql,qr,tl,tr]=TR[i];
		in[qr].pb(i);
	}
	Rep(i,r,mid+1){
		for(auto id:qq[i]){
			auto [ql,qr,tl,ii]=qs[id];
			qid[tl]=ii;
			T4.upd(tl,{i+1});
		}
		for(auto id:in[i]){
			auto [ql,qr,tl,tr]=TR[id];
			T4.mdf(tl,tr,{ql});
		}
		while(1){
			int p=T4.findR(1,m,[&](Max t){
				return t.x>i;
			});
			if(!(p>=1&&p<=m)) break;
			int ii=qid[p];
			if(tor[ii]<i) res[ii]=0;
			T4.upd(p,{-inf});
		}
	}
	
	
	
	For(i,mid+1,r) in[i].clear(),qq[i].clear();
	
	solve(l,mid,TL,QL);
	solve(mid+1,r,TR,QR);
}

void work()
{
	n=read(),q=read();
	
	vector<node> Qs,Ts;
	For(i,1,q){
		int op=read();
		if(op==1){
			++m,ql[m]=read(),qr[m]=read()-1;
			dl[m]=0;
			fid[i]=m;
			tl[m]=m2+1;
			if(ql[m]==qr[m]) ++qwq[ql[m]];
			tr[m]=-1;
		}
		if(op==2){
			int x=read();
			x=fid[x];	
			assert(!dl[x]);
			if(ql[x]==qr[x]) --qwq[ql[x]];
			dl[x]=1;
			tr[x]=m2;
		}
		if(op==3){
			int l=read(),r=read()-1;
			++m2;
			if(l==r) res[m2]=(qwq[l]);
			else Qs.pb({l,r,m2,m2}),res[m2]=1;
			tim[m2]=i;
		}
	}
	
	For(i,1,m){
		if(tr[i]==-1)tr[i]=m2;
		if(tl[i]<=tr[i]) Ts.pb({ql[i],qr[i],tl[i],tr[i]});
	}
	
	solve(1,n-1,Ts,Qs);
	For(i,1,m2) {
		if(res[i])puts("Y");
		else puts("N");
	}
}

signed main()
{
//	freopen("my.out","w",stdout);
	int T=1;
	while(T--)work();
	return 0;
}
```

---

## 作者：critnos (赞：10)

下面我们令 $r\gets r-1$。

考虑区间分治的结构。对于一组 $L\le l\le mid <r\le R$，以 $[mid+1,r]$ 为例，如果我们求出了所有 $[mid+1,r]$ 中的区间未能覆盖的下标最大的位置，接下来就只用判断跨过 $mid$ 的 $[l,r]$ 中的区间是否覆盖这个位置，直接线段树维护即可。

每个区间会贡献到 $O(\log n)$ 个包含其的分治结点和一个包含且跨过中点的分治结点。考虑如何求出某个前缀中未能覆盖的下标最大的位置。做法很多，下面是三个比较好的做法。

### 算法 1

倒着扫序列，把覆盖当前结点的询问和修改的 $r$ 挂在时间轴上（修改的 $r$ 会覆盖一段时间轴）。我们知道如果（时间轴上）覆盖某个询问的修改的 $r$ 都大于这个询问对应的前缀，那就可以把这个询问 pop 了。注意到每次加入的修改的 $r$ 总是最小的，所以线段树维护区间中可能合法的前缀最短的询问，线段树每个结点上用个 stack 维护即可。

### 算法 2

考虑维护每个点的最小的前缀使得这个点被覆盖，那么修改就是区间取 $\min$，查询是区间 $\max$ 的线段树二分。但这里有撤销操作，直接做会变成 $\log^3 n$。

可以发现这里在 $\log n$ 个分治结点上做了完全一样的操作，而线段树的每个结点在其祖先对应的分治结点中出现。所以其实只需要在修改的最深的区间的线段树结点上修改堆信息，然后取个后缀 $\min$ 即可。

但这种做法的常数看起来很大，应该比较难通过。

### 算法 3

还是和算法 $1$ 一样扫描线。将询问按时间顺序排列，在扫到一个询问的时候将其激活，维护其当前被覆盖到的位置。每次加入一个修改就将一个时间区间对这个区间的左端点取 $\min$。取出没被覆盖的区间就直接维护区间最大值即可。

我实现的是算法 1（原初之做法），但算法 3 的常数更小且空间是线性，推荐大家写这个。

时间复杂度 $O(q\log^2 n)$。大伙可以研究一下能不能单 $\log $！！

---

## 作者：cyffff (赞：4)

[$\text{Link}$](https://www.luogu.com.cn/problem/P11695)
## 题意

给定 $n,m$，你需要维护一个 $[1,n)$ 的数轴上区间的初始为空的可重集合，支持三种操作共 $m$ 次：

1. 插入一个区间 $[l,r)$。
2. 删除第 $t$ 次操作插入的区间。
3. 给出一个区间 $[l,r)$，判断当前可重集合中是否存在一个子集，使得子集中所有区间的并恰好是 $[l,r)$。

$n\le 10^6$，$m\le 5\times 10^5$。

## 题解
本题解中默认将题目中给出的区间的右端点减一变为闭区间。

静态情况下的问题考虑扫描线。扫描右端点，维护一个数组 $c_{1\sim r}$，其中 $c_i$ 表示包含 $i$ 的区间的左端点的最大值，那么一个区间 $[l,r]$ 能被表示出当且仅当 $\min_{i=l}^rc_i=l$。
****
一个询问区间 $[ql,qr]$ 能被表示出当且仅当所有是 $[ql,qr]$ 的子区间的操作区间 $[l,r]$ 的并恰等于 $[ql,qr]$。

对于动态的情况，每个操作区间 $[l,r]$ 有其存在的时间区间 $[tl,tr]$，每个询问区间 $[ql,qr]$ 也有其时间 $qt$。

考虑序列分治，设现在正在处理区间 $[cl,cr]$，我们尝试解决所有跨过区间中点 $mid$ 的询问 $[ql,qr]$。

操作区间有被左半边包含、被右半边包含和跨过区间中点三类。
****
对于跨过区间中点的一类，我们按顺序扫描时间轴。

这一类区间对每个询问的贡献为左区间的一个后缀和右区间的一个前缀。

对每个询问 $[ql,qr]$，这部分贡献的右区间前缀即为这个时间点存在的所有满足 $r\le qr,l\ge ql$ 的操作区间 $[l,r]$ 中最大的 $r$。

建一颗线段树，其位置 $p$ 存储右端点为 $r$ 的区间中左端点的最大值，进行一次线段树二分即可找到位置 $p$。左半区间的部分同理。
****
接下来是被半边包含的情况，不妨考虑右半区间的一类。对于一个询问区间 $[ql,qr]$，我们要求出最大的位置 $mid<p\le qr$ 使得位置 $p$ 不能被这一类区间覆盖。

接下来的思路是，对于单次询问，可以从右往左依次枚举直到找到一个位置 $p$ 使得其未被覆盖。于是考虑将所有询问一起做这个过程，扫到一个位置 $p$ 时取出所有在这个位置未被覆盖的询问。

按照 $i=r,r-1,\dots$ 的顺序进行扫描线，在时间轴上维护一个数组 $f_{1\sim t}$，扫到一个询问区间的右端点时我们将这个询问放至其对应时间点的位置进行维护，即令 $f_{qt}\gets i$，扫到一个操作区间 $[l,i]$ 的右端点时将其对应时间区间的 $f$ 值对 $l-1$ 取 $\min$。扫到 $i$ 时，取出所有 $f_{qt}=i$ 的询问即可。

这可以使用线段树轻松实现。
****

根据三部分求出的信息，我们便可判断每个询问区间是否可被表示出了。

每个操作区间会在 $O(\log n)$ 个分治区间中作出贡献，故时间复杂度 $O(n\log n+m\log^2n)$，可以通过。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
    //read()
}
#define pii pair<int,int>
#define mpr make_pair
#define fir first
#define sec second
#define vci vector<int>
const int N=1e6+10,M=5e5+10,INF=1e9+10;
int n,m;
int tl[M],tr[M],tpl[M],tpr[M],L[M],R[M];
int rl1[M],rr1[M],rl2[M],rr2[M],ans[M];
vci vl[N],vt[N],vi[M],vd[M],vq[M];
template<class ND>
struct Set{
	priority_queue<ND>p,q;
	inline void upd(){ while(!q.empty()&&p.top()==q.top()) p.pop(),q.pop(); }
	public:
	inline int size(){ return p.size()-q.size(); }
	inline bool empty(){ return p.size()==q.size(); }
	inline void ins(ND v){ p.push(v); }
	inline void del(ND v){ q.push(v); }
	inline ND top(){ upd();return p.top(); }
	inline void pop(){ upd();p.pop(); }
};
Set<int>sl[N],sr[N];
#define ls (rt<<1)
#define rs (rt<<1|1)
struct Segment_Tree1{
	int mn[N<<1];
	inline void pushup(int rt){
		mn[rt]=min(mn[ls],mn[rs]);
	}
	inline void build(int rt,int l,int r){
		mn[rt]=INF;
		if(l==r) return ;
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(rt);
	}
	inline void update(int rt,int l,int r,int p){
		if(l==r){
			mn[rt]=sl[l].size()?-sl[l].top():INF;
			return ;
		}
		int mid=l+r>>1;
		if(p<=mid) update(ls,l,mid,p);
		else update(rs,mid+1,r,p);
		pushup(rt);
	}
	inline int find(int rt,int l,int r,int L,int R,int v){
		if(r<L||l>R||mn[rt]>v) return -1;
		if(l==r) return l;
		int mid=l+r>>1,tp=find(ls,l,mid,L,R,v);
		if(tp==-1) tp=find(rs,mid+1,r,L,R,v);
		return tp;
	}
}Tl; 
struct Segment_Tree2{
	int mx[N<<1];
	inline void pushup(int rt){
		mx[rt]=max(mx[ls],mx[rs]);
	}
	inline void build(int rt,int l,int r){
		mx[rt]=0;
		if(l==r) return ;
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(rt);
	}
	inline void update(int rt,int l,int r,int p){
		if(l==r){
			mx[rt]=sr[l].size()?sr[l].top():0;
			return ;
		}
		int mid=l+r>>1;
		if(p<=mid) update(ls,l,mid,p);
		else update(rs,mid+1,r,p);
		pushup(rt);
	}
	inline int find(int rt,int l,int r,int L,int R,int v){
		if(r<L||l>R||mx[rt]<v) return -1;
		if(l==r) return l;
		int mid=l+r>>1,tp=find(rs,mid+1,r,L,R,v);
		if(tp==-1) tp=find(ls,l,mid,L,R,v);
		return tp;
	}
}Tr; 
struct Segment_Tree3{
	pii mn[M<<2];
	int tag[N<<2];
	inline void pushup(int rt){
		mn[rt]=min(mn[ls],mn[rs]);
	}
	inline void pushtag(int rt,int v){
		mn[rt].fir=max(mn[rt].fir,v);
		tag[rt]=max(tag[rt],v); 
	}
	inline void pushdown(int rt){
		if(!tag[rt]) return ;
		pushtag(ls,tag[rt]);
		pushtag(rs,tag[rt]);
		tag[rt]=0;
	}
	inline void build(int rt,int l,int r){
		tag[rt]=0,mn[rt]=mpr(INF,0);
		if(l==r) return ;
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	inline void ins(int rt,int l,int r,int p,pii v){
		if(l==r){
			mn[rt]=v;
			return ;
		}
		pushdown(rt);
		int mid=l+r>>1;
		if(p<=mid) ins(ls,l,mid,p,v);
		else ins(rs,mid+1,r,p,v);
		pushup(rt);
	}
	inline void upd(int rt,int l,int r,int L,int R,int v){
		if(L<=l&&r<=R) return pushtag(rt,v);
		pushdown(rt);
		int mid=l+r>>1;
		if(L<=mid) upd(ls,l,mid,L,R,v);
		if(R>mid) upd(rs,mid+1,r,L,R,v);
		pushup(rt);
	}
	inline pii query(){
		return mn[1];
	}
}T1;
struct Segment_Tree4{
	pii mx[M<<2];
	int tag[N<<2];
	inline void pushup(int rt){
		mx[rt]=max(mx[ls],mx[rs]);
	}
	inline void pushtag(int rt,int v){
		mx[rt].fir=min(mx[rt].fir,v);
		tag[rt]=min(tag[rt],v); 
	}
	inline void pushdown(int rt){
		if(tag[rt]==INF) return ;
		pushtag(ls,tag[rt]);
		pushtag(rs,tag[rt]);
		tag[rt]=INF;
	}
	inline void build(int rt,int l,int r){
		tag[rt]=INF,mx[rt]=mpr(-INF,0);
		if(l==r) return ;
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
	}
	inline void ins(int rt,int l,int r,int p,pii v){
		if(l==r){
			mx[rt]=v;
			return ;
		}
		pushdown(rt);
		int mid=l+r>>1;
		if(p<=mid) ins(ls,l,mid,p,v);
		else ins(rs,mid+1,r,p,v);
		pushup(rt);
	}
	inline void upd(int rt,int l,int r,int L,int R,int v){
		if(L<=l&&r<=R) return pushtag(rt,v);
		pushdown(rt);
		int mid=l+r>>1;
		if(L<=mid) upd(ls,l,mid,L,R,v);
		if(R>mid) upd(rs,mid+1,r,L,R,v);
		pushup(rt);
	}
	inline pii query(){
		return mx[1];
	}
}T2;
inline void solve(int l,int r,vci op,vci qr){
	if(l>r||!qr.size()||!op.size()) return ;
	if(l==r) return ;
	int mid=l+r>>1;
//	printf("---solve(%d,%d,%d)---\n",l,r,mid);
	vci opl,opm,opr,qrl,qrm,qrr;
	for(auto tp:op){
		if(R[tp]<=mid) opl.push_back(tp);
		else if(L[tp]>mid) opr.push_back(tp);
		else opm.push_back(tp);
	}
	for(auto tp:qr){
		if(R[tp]<=mid) qrl.push_back(tp);
		else if(L[tp]>mid) qrr.push_back(tp);
		else qrm.push_back(tp);
	}
	//对时间维离散化
	vci lsh;
	for(auto i:op) lsh.push_back(tpl[i]=tl[i]),lsh.push_back(tpr[i]=tr[i]);
	for(auto i:qrm) lsh.push_back(tl[i]);
	sort(lsh.begin(),lsh.end());
	lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
	int k=lsh.size();
	for(auto i:op) tl[i]=lower_bound(lsh.begin(),lsh.end(),tl[i])-lsh.begin()+1;
	for(auto i:op) tr[i]=lower_bound(lsh.begin(),lsh.end(),tr[i])-lsh.begin()+1;
	for(auto i:qrm) tl[i]=lower_bound(lsh.begin(),lsh.end(),tl[i])-lsh.begin()+1;
	//计算跨 mid 区间对跨 mid 询问 
	for(int p:opm) 
		vi[tl[p]].push_back(p),
		vd[tr[p]].push_back(p);
	for(int p:qrm)
		vq[tl[p]].push_back(p);
	Tl.build(1,l,mid),Tr.build(1,mid+1,r);
	for(int i=1;i<=k;i++){
		for(auto p:vi[i])
			sl[L[p]].ins(-R[p]),
			sr[R[p]].ins(L[p]),
			Tl.update(1,l,mid,L[p]),
			Tr.update(1,mid+1,r,R[p]);
		for(auto p:vq[i]){
			int tp=Tl.find(1,l,mid,L[p],mid,R[p]);
			rl1[p]=tp==-1?mid+1:tp;
			tp=Tr.find(1,mid+1,r,mid+1,R[p],L[p]);
			rr1[p]=tp==-1?mid:tp;
		}
		for(auto p:vd[i])
			sl[L[p]].del(-R[p]),
			sr[R[p]].del(L[p]),
			Tl.update(1,l,mid,L[p]),
			Tr.update(1,mid+1,r,R[p]);
	}
	for(auto p:qrm)
		rl2[p]=mid+1,rr2[p]=mid;
	//计算左区间对跨 mid 询问
	T1.build(1,1,k);
	for(int p:qrm)
		vt[L[p]].push_back(p);
	for(int p:opl)
		vl[L[p]].push_back(p);
	for(int i=l;i<=mid;i++){
		for(auto p:vt[i])
			T1.ins(1,1,k,tl[p],mpr(i,p));
		for(auto p:vl[i])
			T1.upd(1,1,k,tl[p],tr[p],R[p]+1);
		while(1){
			pii tp=T1.query();
			if(tp.fir>i) break;
			int p=tp.sec;
			rl2[p]=i;
			T1.ins(1,1,k,tl[p],mpr(INF,0));
		}
	}
	//计算右区间对跨 mid 询问
	T2.build(1,1,k);
	for(int p:qrm)
		vt[R[p]].push_back(p);
	for(int p:opr)
		vl[R[p]].push_back(p);
	for(int i=r;i>mid;i--){
		for(auto p:vt[i])
			T2.ins(1,1,k,tl[p],mpr(i,p));
		for(auto p:vl[i])
			T2.upd(1,1,k,tl[p],tr[p],L[p]-1);
		while(1){
			pii tp=T2.query();
			if(tp.fir<i) break;
			int p=tp.sec;
			rr2[p]=i;
			T2.ins(1,1,k,tl[p],mpr(-INF,0));
		}
	}
	for(auto p:qrm)
		ans[p]=(rl2[p]>=rl1[p])&&(rr2[p]<=rr1[p]);
	//清空+递归 
	for(int i=1;i<=k;i++)
		vi[i].clear(),vd[i].clear(),vq[i].clear();
	for(int i=l;i<=r;i++)
		vt[i].clear(),vl[i].clear();
	for(auto p:opl) tl[p]=tpl[p],tr[p]=tpr[p];
	for(auto p:opr) tl[p]=tpl[p],tr[p]=tpr[p];
	solve(l,mid,opl,qrl),solve(mid+1,r,opr,qrr);
}
int ct[N];
int main(){
//	freopen("1.in","r",stdin);
//	freopen("1.ans","w",stdout);
	n=read(),m=read();
	vci Op,Qr;
	R[0]=INF;
	for(int i=1;i<=m;i++){
		int op=read();
		if(op==2){
			int t=read();
			tr[t]=i-1;
			if(L[t]==R[t]) ct[L[t]]--;
		}else{
			int l=read(),r=read()-1;
			L[i]=l,R[i]=r,tl[i]=i,tr[i]=m;
			if(l==r){
				if(op==1) ct[l]++;
				else ans[i]=!!ct[l];
			}
			if(op==1) Op.push_back(i);
			else Qr.push_back(i);
		}
	}
	solve(1,n-1,Op,Qr);
	for(int i:Qr)
		putc(ans[i]?'Y':'N'),putc('\n');
	flush();
}
```

---

## 作者：lzyqwq (赞：2)

---
给定 $n,m$，你需要维护一个 $[1,n)$ 的数轴上区间的初始为空的**可重集合**，支持三种操作共 $m$ 次：

1. 插入一个区间 $[l,r)$。
2. 删除第 $t$ 次操作插入的区间。
3. 给出一个区间 $[l,r)$，判断当前可重集合中是否存在一个子集，使得子集中所有区间的并恰好是 $[l,r)$。

---

将区间看成四元组 $(l_i,r_i,b_i,e_i)$，将询问看成三元组 $(x_j,y_j,t_j)$。

首先区间都是左闭右开的实数区间。考虑记第 $i$ 个段为 $[i,i+1)$，则区间 $[l,r)$ 表示了第 $l,\dots ,r-1$ 个段。所以令 $r\leftarrow r-1$ 后，仅需要考虑整数的情况。下面令 $[l,r]$ 表示该区间内整数构成的集合。

判断一个询问时，贪心地把所有子集选上再判断是否有解。这样一定不劣。

分治。记当前分治区间为 $[L,R]$，中点 $M=\left\lfloor\dfrac{L+R}{2}\right\rfloor$。考虑解决所有 $x_j\le M<y_j$ 的询问。

先考虑选上所有跨过 $l_i\le M<r_i$ 且 $[l_i,r_i]\sube [x_j,y_j]$ 的区间。选上这些子区间后并集形如一个跨过 $M$ 的区间 $[\text{lp}_j,\text{rp}_j]$，其中 $\text{lp}_j,\text{rp}_j$ 表示左半区间中被覆盖的最小位置、有半区间中被覆盖的最大位置。考虑求出她们。

以 $\text{lp}_j$ 为例。记 $k_w=\min\limits_{l_i=w,r_i>M}r_i$。按照时间维扫描线，则相当于在 $b_i$ 时刻插入一个区间、在 $e_i+1$ 时刻删除一个区间；查询 $t_j$ 时刻 $[x_j,M]$ 内最小的 $p$ 使得 $k_p\le y_j$。记 **可重集** $K_w=\{r_i\,|\,l_i=w,r_i>M\}$，则 $k_w$ 就是 $K_w$ 中的最小值。问题变成维护 $n$ 个可重集，支持单个可重集插入、删除元素，求一个区间内最小值不超过某个定值的编号最小的可重集。用线段树维护，叶子节点维护 `multiset`，非叶子节点维护区间内 $k_w$ 的最小值。查询使用线段树二分。单次时间复杂度 $\mathcal{O}(\log n)$。

接下来考虑不跨过 $M$ 的子集。对于每个询问求出 $\text{Lp}_j,\text{Rp}_j$，表示左 / 右半区间的子集最小 / 最大不能覆盖的位置。

同样以 $\text{Lp}_j$ 为例，考虑从左往右扫描答案 $p$。则对于一个询问，若插入所有 $x_j\le l_i\le p,r_i\le M$ 的区间后，$p$ 位置仍未被覆盖，则她不会被后面的区间覆盖了。因此扫到的第一个符合上述条件的 $p$ 即为答案。每次暴力找出 $p$ 能更新的询问，然后将这些询问扔掉。则一个询问只会被计算一次。将询问的时刻离散化，对时间轴用线段树维护 $f_t$ 表示 $t$ 时刻的询问扫到当前 $p$ 时的 $\text{Lp}_j$，由于在之前已经把 $\text{Lp}_j<p$ 的询问取出了，剩下的询问保证 $f_t\ge p$，维护最小值，判断当前 $f_t$ 最小值是否为 $p$，暴力取出最小值再删除即可。先不考虑 $x_j\le l_i$。此时仅要求 $L\le l_i$。那么扫描的时候插入所有 $l_i=p$ 的区间，其影响为对 $[b_i,e_i]$ 时刻内的区间的 $f_t$ 对 $r_i+1$ 取 $\max$。在线段树上打标记即可。接下来考虑 $x_j\le l_i$ 的限制，则扫到 $p$ 时对于 $x_j=p$ 的询问，之前的修改不能生效，且这个区间不能在这之前被取出。后者考虑初值赋为极大值即可，前者考虑在扫到 $p$ 时单点重新覆盖成 $p$ 即可消除先前的标记。容易线段树维护。

最后判断有无解就是是否 $\text{Lp}_j\ge \text{lp}_j$ 且 $\text{Rp}_j\le \text{rp}_j$。就是考虑两边能否和中间连上。

一个询问在第一个跨过中点的区间被计算，一个区间在包含她的 $\mathcal{O}(\log n)$ 个分治区间中被操作。因此时间复杂度 $\mathcal{O}\left(m\log^2n+n\log n\right)$，空间复杂度视实现精细程度为 $\mathcal{O}(n)$ 或 $\mathcal{O}(m\log n)$。


```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)
using namespace std; const int N = 1000005; vector<int> l_[N], r_[N];
struct QR { int l, r, t; }; vector<QR> qr, Qr, Rg, gl[N], gr[N];
struct RG { int l, r, tl, tr; }; vector<RG> rg; bool ans[N], ok[N];
int n, q, l[N], r[N], lp[N], rp[N], Lp[N], Rp[N], lh[N], c, op[N];
struct SGT1 {
	multiset<int> s[N]; int t[N << 1]; SGT1 () { fill(t, t + (N << 1), N); }
	void U(int x, int l, int r, int k, int v, bool o) {
		if (l == r) {
			if (o) s[l].emplace(v); else s[l].erase(s[l].find(v));
			return void(t[x] = s[l].size() ? *s[l].begin() : N);
		}
		int m = l + r >> 1;
		if (k <= m) U(ls(m), l, m, k, v, o); else U(rs(m), m + 1, r, k, v, o);
		t[x] = min(t[ls(m)], t[rs(m)]);
	}
	int Q(int x, int l, int r, int ql, int qr, int v) {
		if (t[x] > v) return 0; if (l == r) return l; int m = l + r >> 1, k = 0;
		if (ql <= m) k = Q(ls(m), l, m, ql, qr, v); if (k) return k;
		return Q(rs(m), m + 1, r, ql, qr, v);
	}
} t1;
struct SGT2 {
	multiset<int> s[N]; int t[N << 1];
	void U(int x, int l, int r, int k, int v, bool o) {
		if (l == r) {
			if (o) s[l].emplace(v); else s[l].erase(s[l].find(v));
			return void(t[x] = s[l].size() ? *s[l].rbegin() : 0);
		}
		int m = l + r >> 1;
		if (k <= m) U(ls(m), l, m, k, v, o); else U(rs(m), m + 1, r, k, v, o);
		t[x] = max(t[ls(m)], t[rs(m)]);
	}
	int Q(int x, int l, int r, int ql, int qr, int v) {
		if (t[x] < v) return 0; if (l == r) return l; int m = l + r >> 1, k = 0;
		if (qr > m) k = Q(rs(m), m + 1, r, ql, qr, v); if (k) return k;
		return Q(ls(m), l, m, ql, qr, v);
	}
} t2;
struct SGT3 {
	int s[N << 1], t[N << 1];
	void B(int x, int l, int r) {
		s[x] = N; t[x] = 0; if (l == r) return;
		int m = l + r >> 1; B(ls(m), l, m); B(rs(m), m + 1, r);
	}
	void U(int x, int v) { s[x] = max(s[x], v); t[x] = max(t[x], v); }
	void U(int x, int l, int r, int ql, int qr, int v) {
		if (ql <= l && r <= qr) return U(x, v); int m = l + r >> 1; 
		if (ql <= m) U(ls(m), l, m, ql, qr, v);
		if (qr > m) U(rs(m), m + 1, r, ql, qr, v);
		s[x] = max(min(s[ls(m)], s[rs(m)]), t[x]);
	}
	void C(int x, int l, int r, int k, int v) {
		if (l == r) return void(s[x] = v); int m = l + r >> 1;
		U(ls(m), t[x]); U(rs(m), t[x]); t[x] = 0;
		if (k <= m) C(ls(m), l, m, k, v); else C(rs(m), m + 1, r, k, v);
		s[x] = min(s[ls(m)], s[rs(m)]);
	}
	int Q(int x, int l, int r) {
		if (l == r) return l; int m = l + r >> 1;
		return s[ls(m)] < s[rs(m)] ? Q(ls(m), l, m) : Q(rs(m), m + 1, r);
	}
} t3;
struct SGT4 {
	int s[N << 1], t[N << 1];
	void B(int x, int l, int r) {
		s[x] = 0; t[x] = N; if (l == r) return;
		int m = l + r >> 1; B(ls(m), l, m); B(rs(m), m + 1, r);
	}
	void U(int x, int v) { s[x] = min(s[x], v); t[x] = min(t[x], v); }
	void U(int x, int l, int r, int ql, int qr, int v) {
		if (ql <= l && r <= qr) return U(x, v); int m = l + r >> 1; 
		if (ql <= m) U(ls(m), l, m, ql, qr, v);
		if (qr > m) U(rs(m), m + 1, r, ql, qr, v);
		s[x] = min(max(s[ls(m)], s[rs(m)]), t[x]);
	}
	void C(int x, int l, int r, int k, int v) {
		if (l == r) return void(s[x] = v); int m = l + r >> 1;
		U(ls(m), t[x]); U(rs(m), t[x]); t[x] = N;
		if (k <= m) C(ls(m), l, m, k, v); else C(rs(m), m + 1, r, k, v);
		s[x] = max(s[ls(m)], s[rs(m)]);
	}
	int Q(int x, int l, int r) {
		if (l == r) return l; int m = l + r >> 1;
		return s[ls(m)] > s[rs(m)] ? Q(ls(m), l, m) : Q(rs(m), m + 1, r);
	}
} t4;
void lzyqwq(int l, int r, vector<QR> &qr, vector<RG> &rg) {
	if (!qr.size() || !rg.size()) return;
	if (l == r) { for (QR i : qr) ans[i.t] = 1; return; } int m = l + r >> 1; c = 0;
	for (QR i : qr)
		if (i.l <= m && i.r > m) {
			Qr.eb(i); Lp[i.t] = m + 1; Rp[i.t] = m; lh[++c] = i.t;
		}
	if (c) {
		for (RG i : rg)
			if (i.l <= m && i.r > m)
				Rg.eb(QR{i.l, i.r, i.tl}), Rg.eb(QR{-i.l, i.r, i.tr + 1});
		stable_sort(Qr.begin(), Qr.end(), [&](QR u, QR v) { return u.t < v.t; });
		stable_sort(Rg.begin(), Rg.end(), [&](QR u, QR v) { return u.t < v.t; });
		for (int i = 0, j = 0; i < c; ++i) {
			for (; j < Rg.size() && Rg[j].t <= Qr[i].t; ++j)
				t1.U(1, 1, n, abs(Rg[j].l), Rg[j].r, abs(Rg[j].l) == Rg[j].l);
			lp[Qr[i].t] = t1.Q(1, 1, n, Qr[i].l, n, Qr[i].r);
			if (!lp[Qr[i].t]) lp[Qr[i].t] = m + 1;
			if (i == c - 1)
				for (--j; j >= 0; --j)
					t1.U(1, 1, n, abs(Rg[j].l), Rg[j].r, abs(Rg[j].l) != Rg[j].l);
		}
		for (int i = 0, j = 0; i < c; ++i) {
			for (; j < Rg.size() && Rg[j].t <= Qr[i].t; ++j)
				t2.U(1, 1, n, Rg[j].r, abs(Rg[j].l), abs(Rg[j].l) == Rg[j].l);
			rp[Qr[i].t] = t2.Q(1, 1, n, 1, Qr[i].r, Qr[i].l);
			if (!rp[Qr[i].t]) rp[Qr[i].t] = m;
			if (i == c - 1)
				for (--j; j >= 0; --j)
					t2.U(1, 1, n, Rg[j].r, abs(Rg[j].l), abs(Rg[j].l) != Rg[j].l);
		}
		for (int i = 0; i < c; ++i)
			l_[Qr[i].l].eb(i + 1), r_[Qr[i].r].eb(i + 1), lh[i + 1] = Qr[i].t;
		Qr.clear(); Rg.clear(); t3.B(1, 1, c); t4.B(1, 1, c);
		for (auto [l, r, tl, tr] : rg) {
			if (l <= m && r > m) continue;
			int sl = lower_bound(lh + 1, lh + c + 1, tl) - lh,
			    sr = upper_bound(lh + 1, lh + c + 1, tr) - lh - 1;
			if (sl > sr) continue;
			if (r <= m) gl[l].eb(QR{sl, sr, r + 1});
			else gr[r].eb(QR{sl, sr, l - 1});
		}
		for (int i = l, p; i <= m; ++i) {
			for (int j : l_[i]) t3.C(1, 1, c, j, i); l_[i].clear();
			for (auto [l, r, v] : gl[i]) t3.U(1, 1, c, l, r, v); gl[i].clear();
			while (t3.s[1] == i) Lp[lh[p = t3.Q(1, 1, c)]] = i, t3.C(1, 1, c, p, N);
		}
		for (int i = r, p; i > m; --i) {
			for (int j : r_[i]) t4.C(1, 1, c, j, i); r_[i].clear();
			for (auto [l, r, v] : gr[i]) t4.U(1, 1, c, l, r, v); gr[i].clear();
			while (t4.s[1] == i) Rp[lh[p = t4.Q(1, 1, c)]] = i, t4.C(1, 1, c, p, 0);
		}
		for (QR i : qr)
			if (i.l <= m && i.r > m)
				ans[i.t] = (lp[i.t] <= Lp[i.t] && rp[i.t] >= Rp[i.t]);
	}
	vector<QR> l_, r_; vector<RG> L_, R_;
	for (QR i : qr) if (i.r <= m) l_.eb(i); else if (i.l > m) r_.eb(i);
	for (RG i : rg) if (i.r <= m) L_.eb(i); else if (i.l > m) R_.eb(i);
	qr.clear(); rg.clear(); lzyqwq(l, m, l_, L_); lzyqwq(m + 1, r, r_, R_);
	l_.clear(); r_.clear(); L_.clear(); R_.clear();
}
int main() {
	scanf("%d%d", &n, &q); --n;
	for (int i = 1; i <= q; ++i) {
		scanf("%d%d", &op[i], &l[i]);
		if (op[i] == 1) scanf("%d", &r[i]);
		else if (op[i] ^ 3)
			rg.eb(RG{l[l[i]], r[l[i]] - 1, l[i], i - 1}), ok[l[i]] = 1;
		else scanf("%d", &r[i]), qr.eb(QR{l[i], r[i] - 1, i});
	}
	for (int i = 1; i <= q; ++i)
		if (op[i] == 1 && !ok[i]) rg.eb(RG{l[i], r[i] - 1, i, q});
	lzyqwq(1, n, qr, rg);
	for (int i = 1; i <= q; ++i) if (op[i] == 3) puts(ans[i] ? "Y" : "N"); return 0;
}
```

---

## 作者：M1saka16I72 (赞：2)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-p11695)

忙里偷闲做 ds！

## 思路

参考了 [@Rainbow_qwq 的题解](https://www.luogu.com.cn/article/gfcgtqd7)，orz。

题意简述：支持加 / 删区间和查询当前所有被 $[l,r]$ 包含的区间的并是否等于 $[l,r]$。

数据范围不小，很难在线维护，考虑离线分治。

  设当前分治区间为 $[sl,sr]$，中点为 $mid$，在这一层分治内部处理所有被 $[sl,sr]$ 完全包含并跨过 $mid$ 的询问，其余询问递归处理。考虑两类区间对询问的贡献：跨过 $mid$ 或被 $[l,mid]$ 和 $(mid,r]$ 完全包含。

### 跨过 $mid$ 的操作区间

对于这类区间，当前的目标是对每个询问 $[ql,qr]$ 找到所有被 $[ql,qr]$ 包含的区间中，极左的能贡献的位置 $tl$ 与极右的能贡献的位置 $tr$。下面以求解 $tl$ 为例，$tr$ 与 $tl$ 本质相同：

首先对时间轴扫描线，在区间被删除的时候撤销其贡献。需要用线段树和可删堆 / set 对每个 $l$ 维护当前还存在的以 $l$ 为左端点的区间 $[l,r]$ 中 $r$ 的最小值。假设现在扫描到时间轴的位置为 $i$，需要进行以下操作：

- 若第 $i$ 个操作加入了当前需要处理的区间 $[l,r]$，在第 $l$ 个可删堆中插入 $r$，将线段树下标为 $l$ 的位置修改为这个堆里的 $\min$。

- 若第 $i$ 个操作是当前需要处理的询问 $[l,r]$，则在线段树上二分 $[l,mid]$ 内第一个值 $\leq r$ 的下标，赋值为这个询问的 $tl$。

- 若第 $i$ 个操作删除了当前需要处理的区间 $[l,r]$，则在第 $l$ 个可删堆中删除 $r$，将线段树下标为 $l$ 的位置更新成这个堆里的 $\min$（如果堆是空的则更新为极大值）。

可见线段树需要支持的功能为单点修改 / 区间 $\min$ / 区间二分第一个 $\leq k$ 的数（求解 $tr$ 时正好相反，维护的是区间 $\max$ 以及区间二分最后一个 $\geq k$ 的数，同时可删堆维护的也变成了最大值）。

### 不跨过 $mid$，被 $[l,mid]$ 或 $(mid,r]$ 完全包含的操作区间

这次我们更换扫描线的维度，对序列下标扫描线，线段树维护的下标则是时间轴。还是以处理完全在左边的操作区间为例，完全在右边的情况本质相同。

首先将要处理的询问和区间全部按左端点升序排序，从左到右扫描线。考虑使用这些区间依次往右覆盖询问，遇到询问时判断这个询问被覆盖的值是否小于它的 $tl-1$，若是则不合法。假设当前扫描到序列下标为 $i$，需要进行的操作为：

- 遍历所有左端点为 $i$ 的询问。设询问编号为 $t$，在线段树上将下标为 $t$ 的位置修改为极小值，这样就可以撤销所有左端点 $<i$ 的区间对这个询问的贡献。

- 遍历所有左端点为 $i$ 的区间 $[i,r]$。设其在时间轴上出现的时间区间为 $[lt,rt]$。在线段树上将 $[lt,rt]$ 对 $r$ 取 $\max$。

- 不断取出当前线段树上的最小值，设最小值为 $x$，取到最小值的位置为 $id$，循环终止条件为 $x\geq i$（若 $x<i$，代表 $i$ 这个下标未被覆盖，则左端点 $\geq i+1$ 的区间就无法对其造成贡献了）。若 $tl_{id}>i$，这个询问就是不合法的。特别地，若没有任何区间覆盖过这个询问，取出的 $x$ 会是极小值。特判一下，这种情况合法的条件为 $tl_{id}=l_{id}$。

这一步需要一个支持区间取 $\max$，单点修改和全局最小值的线段树（同样的，求解右区间时也正好相反）。

至此，所有情况的贡献都被我们统计完成。这题里扫描线的各种用法感觉很有启发性。

## 代码

[link](https://www.luogu.com.cn/paste/pvk84g3z)，11 kb，太恐怖。

---

## 作者：XZhuRen (赞：2)

好题。

---

前置知识：

猫树分治，线段树，以及 [P11536](https://www.luogu.com.cn/problem/P11536),[P7497](https://www.luogu.com.cn/problem/P7497)。

---

首先问题明显是要求判定这样一个问题：一个询问 $(\left [l,r\right ),t)$ 是否能被所有的子区间在包含 $t$ 的时间内完整覆盖。

找出这个区间完整包含是不太明智的，发现我们很难用分治结构刻画。

我们发现扫描线必然是扫描位置的，但是与此同时我们也需要时间扫描线。

接下来整区间，线段都表示为 $[l,r)$，情况都以**中点以左的区间**为例：

猫树，当一个询问 $[l,r)$ 插在中点上时，它可能被这样的区间覆盖：

刻画的时候发现与区间有交必然不行，我们只考虑接下来两种线段：

1. 同样插在中点上 $[lt,rt)$：
>
>$lt\ge l,rt\le r$，我们取最靠近右边的，这个直接线段树二分（底层 set 或对顶堆）即可维护，按照时间操作。
>
>记下这一部分最远覆盖到 $ext$。
>
>时间复杂度 $\mathcal{O}(m\log m)$。

2. 在两边。

>这一部分即让我们要求总覆盖区间 $[L,R)$ 满足 $L=l$，$ext\le R\le mid$ ，$mid$ 的限制不存在，即右端点在一段到 $R$ 的前（后）缀上。
>
>这里加在序列上的限制较多，考虑 [curtains 的解法](https://www.luogu.com.cn/article/5rqqcqna)：对序列扫描线，并记录左端点能到达的右端点在哪里。
>
>考虑限制，限制少了一个右端点包含，多了一个时间轴。
>
>怎么刻画固定左端点的限制？首先我们扫描到询问的时候，必然插入这个询问到它对应的时间上。
>
>发现并不能用右端点扫描，这样就无法用原题的标记合并方法了。其实也没有必要扫描右端点，因为不存在右端点包含的限制。
>
>考虑左端点从左到右扫描：
>
>我们每次询问的时候点亮一个点，每次操作到新左端 $l$ 手动删去所有不满足 $rt\ge l$ 的已点亮时间点，这一部分复杂度为 $\mathcal{O}(m\log m)$，每个点只会被删去一次。
>
>加入一段区间则也在左端点加入，对还点亮的点区间 $chkmx()$ 即可，这一部分复杂度 $\mathcal{O}(m\log m \log n)$，每个操作被拆成最多 $\log n$ 个区间在线段树上。
>
>在询问右端点 $mid-ext$ 时收获即可，即查看当前的时间点是否仍然点亮。

做完了，代码并不好写。

核心部分代码：

``` cpp
#define ls (o<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
namespace dac{
	vector<Line>asmd[M];
	vector<Line>qs[M];
	void insa(int o,int l,int r,int lt,int rt,Line le){//插入修改（只插中点）
	}
	void insq(int o,int l,int r,int lt,int rt,Line le){//插入询问
	}
}
struct node{//对顶堆
};
struct sgt{//维护前缀最小值
	int mn[M];int L[M],R[M];node uds[N];
	void build(int o,int l,int r){//维护单点值的
	}
	void pushup(int o){}
	void update(int o,int pos){
	}
	void insert(int pos,int dt){
	}
	void del(int pos,int dt){
	}
	int getmns(int o,int x){
	}
	int Get_mns(int o,int x,int rt){
	}
	void init(int r){
	}
}T1,T2;
namespace beats{
	/*
	位置反扫描线
	固定单端点 l
	令端点 r 在一段后缀内
	仅此而已！                                                                                     
	*/
	//若参考 curtains，维护二元组标记，则对所有 r>=l 的取新的 r
	//但是若新旧标记不交，则我们在本题中无法确认保留哪个标记！
	//因为 r 并不是递增的（要保证 l 包含性，扫描 l）！
	//我们无法对 l,r 做出规约
	//所以：手动记录线段树上 mn[x]< i 的点，然后把它删掉！
	//这里参考 P7497 四方喝彩！
	int L[M],R[M];
	int mx[M];//规约使得 mx>=ext
	int mn[M];//记录 mn，扫描后删除所有 mn<l 的点！
	int tag[M];
	void build(int o,int l,int r){
	}
	void update(int o,int tg){
		if(mn[o]==inf)return;//无元素
		mn[o]=max(mn[o],tg);//最小值被更新
		mx[o]=max(mx[o],tg);//全部更新，必合法！
		tag[o]=max(tag[o],tg);
	}
	void pushdown(int o){
	}
	void acti(int o,int pos,int stt){//激活单点
	}
	void chkmx(int o,int lt,int rt,int x){
	}
	void check(int o,int x){//单点只会激活/熄灭一次，所以均摊线性*log，这里遍历法熄灭不合法单点
	}
	int query(int o,int pos){
	}
}
struct line1{
	int l,r;int t,op;int ext;
	bool operator <(const line1 &o)const{return t==o.t?op<o.op:t<o.t;}
}tl[N],qsl[N],qsr[N];
int totl;int tql,tqr;int ttmp[M],ttt=0;
void solveside(){
	if(!totl)return;
	ttt=0;//离散化
	for(int i=1;i<=totl;i++)
		if(tl[i].op==-1)ttmp[++ttt]=tl[i].l;
	if(!ttt)return;
	sort(ttmp+1,ttmp+1+ttt);ttt=unique(ttmp+1,ttmp+1+ttt)-ttmp-1;
	for(int i=1;i<=totl;i++){
		if(tl[i].op!=1)tl[i].r=tl[i].l;
		tl[i].l=lower_bound(ttmp+1,ttmp+1+ttt,tl[i].l)-ttmp;
		if(tl[i].op==1)tl[i].r=upper_bound(ttmp+1,ttmp+1+ttt,tl[i].r)-ttmp-1;
	}
	sort(tl+1,tl+1+totl);beats::build(1,1,ttt);
	int lst=-1;
	for(int i=1;i<=totl;i++){
		int l=tl[i].t;
		if(l!=lst)beats::check(1,l);
		if(tl[i].op==-1)beats::acti(1,tl[i].l,tl[i].t);
		else if(tl[i].op==1){
			if(tl[i].l<=tl[i].r)
			beats::chkmx(1,tl[i].l,tl[i].r,tl[i].ext);//修改
		}else Ans[tl[i].r]&=bool(beats::query(1,tl[i].l)>=l);
		lst=l;
	}
}
void solve(int o,int l,int r,vector<Line>ass){
	using namespace dac;
	totl=tql=tqr=0;
	{//第一部分：跨过中点部分，1log
		for(auto cq:qs[o])tl[++totl]=(line1){cq.l,cq.r,cq.st,2,0};
		for(auto cq:asmd[o]){
			tl[++totl]=(line1){cq.l,cq.r,cq.st,1,0};
			tl[++totl]=(line1){cq.l,cq.r,cq.ed,-1,0};
		}
		sort(tl+1,tl+1+totl);T1.init(mid-l),T2.init(r-mid);
		for(int i=1;i<=totl;i++){
			if(tl[i].op==2){
				qsl[++tql]=qsr[++tqr]=tl[i];
				qsl[tql].ext=T1.Get_mns(1,tl[i].r-mid,mid-tl[i].l);//<=r
				qsr[tqr].ext=T2.Get_mns(1,mid-tl[i].l,tl[i].r-mid);//>=l
				if(qsl[tql].ext==mid-qsl[tql].l)tql--;
				if(qsr[tqr].ext==qsr[tqr].r-mid)tqr--;
			}else{
				if(tl[i].op==1)T1.insert(mid-tl[i].l,tl[i].r-mid),T2.insert(tl[i].r-mid,mid-tl[i].l);
				else T1.del(mid-tl[i].l,tl[i].r-mid),T2.del(tl[i].r-mid,mid-tl[i].l);
			}
		}
	}
	{//第二部分：不过中点部分，2log
		totl=0;
		for(auto cq:ass){
			if(cq.l<=mid&&cq.r>=mid)continue;
			if(cq.r<mid)//左边的，左端点修改
			tl[++totl]=(line1){cq.st,cq.ed-1,cq.l-l,1,cq.r-l};//修改
		}
		while(tql){
			tl[++totl]=(line1){qsl[tql].t,qsl[tql].t,qsl[tql].l-l,-1,0};//插入询问
			tl[++totl]=(line1){qsl[tql].t,qsl[tql].t,mid-qsl[tql].ext-l,2,0};//ext 就可以收获了！
			tql--;
		}
		solveside();
		totl=0;
		for(auto cq:ass){
			if(cq.l<=mid&&r>=mid)continue;
			if(cq.l>mid)//右边的，旋转后左端点修改
			tl[++totl]=(line1){cq.st,cq.ed-1,r-cq.r,1,r-cq.l};//修改
		}
		while(tqr){
			tl[++totl]=(line1){qsr[tqr].t,qsl[tql].t,r-qsr[tqr].r,-1,0};//询问
			tl[++totl]=(line1){qsr[tqr].t,qsl[tql].t,r-mid-qsr[tqr].ext,2,0};//ext 收获！
			tqr--;
		}
		solveside();
	}
	vector<Line>las,ras;
	for(auto cq:ass){
		if(cq.r<=mid)las.emplace_back(cq);
		if(cq.l>=mid)ras.emplace_back(cq);
	}
	ass.clear();
	if(l+1!=r)solve(ls,l,mid,las),solve(rs,mid,r,ras);
}
#undef ls
#undef rs
#undef mid
```

本题略微卡常，线段树 $chkmx()$ 的时候加优化，以及把底层的 `multiset` 换成对顶堆就好了。

加强版这个卡不过，修改线段树即可。

---

