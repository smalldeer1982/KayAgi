# [PA 2024] Kolorowy las

## 题目背景

PA 2024 4A

## 题目描述

**题目译自 [PA 2024](https://sio2.mimuw.edu.pl/c/pa-2024-1/dashboard/) Runda 4 [Kolorowy las](https://sio2.mimuw.edu.pl/c/pa-2024-1/p/kol/)，感谢 Macaronlin 提供翻译**

给定 $n$ 个点的森林（无向无环图），点从 $1$ 到 $n$ 编号，有正整数边权，每个点有颜色，初始所有点颜色为 $0$。

有 $4$ 种共 $q$ 个操作：

- $1\ a_i\ b_i\ d_i$：在 $a_i$ 和 $b_i$ 之间添加一条边权为 $d_i$ 的边（保证添加之后图中仍无环）；
- $2\ a_i\ b_i$：删除 $a_i$ 和 $b_i$ 之间的边；
- $3\ v_i\ z_i\ k_i$：把所有可以到达 $v_i$ 且到 $v_i$ 的距离小于等于 $z_i$ 的顶点染色为 $k_i$；
- $4\ u_i$：查询点 $u_i$ 的颜色。

## 说明/提示

- 在某些子任务中，不存在操作 $1$ 和 $2$，且 $m=n-1$；
- 在某些子任务中，操作 $3$ 中均有 $z_i=10^{15}$。

对于上述每种附加限制，都至少有一个子任务能满足。满足两种附加限制的子任务集合可能相交，也可能不相交。

## 样例 #1

### 输入

```
4 2 9
1 2 2
3 2 5
4 2
3 2 2 5
4 1
3 2 4 3
4 1
4 3
2 2 1
1 1 4 1
4 4
```

### 输出

```
0
5
3
0
0
```

# 题解

## 作者：WrongAnswer_90 (赞：4)

## [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18290068)

### [P10359 [PA2024] Kolorowy las](https://www.luogu.com.cn/problem/P10359)

/tuu。写了三天。

首先考虑树的形态不变怎么做，直接的想法是树分治这种东西可以做到一只或者两只 $\log$。

但是点分这种东西不太好扩展到动态树的问题。但是因为这是单点查询，所以可以不用真正的树上染色，只需要回答每个询问即可。考虑对于每个询问，考虑找到在它之前第一次给这个点染色的操作，这样这次操作就是答案。

这样就比较简单了。可以从后向前做，遇到一个查询就把它挂在点上，对于染色操作就把邻域的所有询问回答。需要维护加删标记点，查询最近的标记点，可以用 LCT 套一个 `multiset` 维护（`multiset` 用来维护轻子树的答案），总复杂度是 $\mathcal O(n\log^2n)$。

因为要 `link,cut` 就要换根就要 `reverse`，所以需要维护到链头链尾分别的最短关键点，实现有一些细节。

```cpp
int n,m,q;
namespace LCT
{
	namespace Splay
	{
		int cnt;
		struct PII
		{
			int fi,se;
			PII(int X=0,int Y=0){fi=X,se=Y;}
			bool operator <(const PII x)const{return fi<x.fi||(fi==x.fi&&se<x.se);}
		};
		struct{int ch[2],fa,tg,v,siz;PII l,r;multiset<PII> st;}t[2000010];
		vector<int> ve[200010];
		#define ls(x) t[x].ch[0]
		#define rs(x) t[x].ch[1]
		#define fa(x) t[x].fa
		#define ident(x) (x==t[fa(x)].ch[1])
		#define connect(x,f,s) (t[fa(x)=f].ch[s]=x)
		#define ntroot(x) (x==ls(fa(x))||x==rs(fa(x)))
		inline PII operator +(const PII a,const int b){return PII(a.fi+b,a.se);}
		inline PII get(PII a,PII b){return a<b?a:b;}
		template<typename ...Args> inline PII get(PII a,Args...args){return get(get(args...),a);}
		inline void down(int x){t[x].tg^=1,swap(t[x].l,t[x].r),swap(ls(x),rs(x));}
		inline void spread(int x){if(t[x].tg)down(ls(x)),down(rs(x)),t[x].tg=0;}
		inline void update(int x)
		{
			spread(x);
			t[x].siz=t[ls(x)].siz+t[rs(x)].siz+t[x].v;
			PII nw;
			if(t[x].st.size())nw=*t[x].st.begin();else nw=PII(INF,0);
			t[x].l=get(t[ls(x)].l,t[rs(x)].l+t[ls(x)].siz+t[x].v,nw+t[ls(x)].siz);
			t[x].r=get(t[rs(x)].r,t[ls(x)].r+t[rs(x)].siz+t[x].v,nw+t[rs(x)].siz);
		}
		inline void rotate(int x)
		{
			int f=fa(x),ff=fa(f),k=ident(x);
			connect(t[x].ch[k^1],f,k);
			if(ntroot(f))t[ff].ch[ident(f)]=x;fa(x)=ff;
			connect(f,x,k^1),update(f),update(x);
		}
		void pushall(int x){if(ntroot(x))pushall(fa(x));spread(x);}
		void splaying(int x)
		{
			pushall(x);
			while(ntroot(x))
			{
				int f=fa(x);
				if(ntroot(f))ident(x)^ident(f)?rotate(x):rotate(f);
				rotate(x);
			}
		}
	}
	using namespace Splay;
	unordered_map<int,int> hash;
	inline void access(int x)
	{
		for(int y=0;x;y=x,x=fa(x))
		{
			splaying(x);
			if(rs(x))t[x].st.insert(t[rs(x)].l+t[x].v);
			rs(x)=y;
			if(rs(x))t[x].st.erase(t[x].st.find(t[rs(x)].l+t[x].v));
			update(x);
		}
	}
	inline void mkroot(int x){access(x),splaying(x),down(x),update(x);}
	inline int findroot(int x)
	{
		access(x);
		splaying(x),spread(x);
		while(ls(x))spread(x=ls(x));
		return x;
	}
	inline void link(int x,int y){mkroot(x),fa(x)=y,t[y].st.insert(t[x].l+t[y].v),update(y);}
	inline void cut(int x,int y){mkroot(x),access(y),splaying(y),fa(x)=ls(y)=0,update(y);}
	inline int newnode(int x){t[++cnt].v=x;return update(cnt),cnt;}
	inline void LINK(int x,int y,int z){z=newnode(z),hash[x*n+y]=hash[y*n+x]=z,link(x,z),link(y,z);}
	inline void CUT(int x,int y){int t=hash[x*n+y];cut(x,t),cut(y,t);}
}
using namespace LCT;
struct{int opt,x,y,z;}a[200010];
int ans[200010];
inline void mian()
{
	read(n,m,q),cnt=n,t[0].l=t[0].r=PII(INF,0);int x,y,z;
	for(int i=1;i<=m;++i)read(x,y,z),LINK(x,y,z);
	for(int i=1;i<=q;++i)
	{
		read(a[i].opt);
		if(a[i].opt==1)read(a[i].x,a[i].y,a[i].z),LINK(a[i].x,a[i].y,a[i].z);
		else if(a[i].opt==2)read(a[i].x,a[i].y),a[i].z=t[hash[a[i].x*n+a[i].y]].v,CUT(a[i].x,a[i].y);
		else if(a[i].opt==3)read(a[i].x,a[i].y,a[i].z);
		else read(a[i].x);
	}
	for(int i=q;i>=1;--i)
	{
		if(a[i].opt==1)CUT(a[i].x,a[i].y);
		else if(a[i].opt==2)LINK(a[i].x,a[i].y,a[i].z);
		else if(a[i].opt==3)
		{
			while(mkroot(a[i].x),t[a[i].x].l.fi<=a[i].y)
			{
				int p=t[a[i].x].l.se;
				mkroot(p);
				for(auto v:ve[p])
				{
					ans[v]=a[i].z;
					t[p].st.erase(t[p].st.find(PII(0,p)));
				}
				ve[p].clear(),update(p);
			}
		}
		else ve[a[i].x].eb(i),mkroot(a[i].x),t[a[i].x].st.insert(PII(0,a[i].x)),update(a[i].x);
	}
	for(int i=1;i<=q;++i)if(a[i].opt==4)write(ans[i],'\n');
}
```

---

