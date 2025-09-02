# Duff as a Queen

## 题目描述

Duff is the queen of her country, Andarz Gu. She's a competitive programming fan. That's why, when he saw her minister, Malek, free, she gave her a sequence consisting of $ n $ non-negative integers, $ a_{1},a_{2},...,a_{n} $ and asked him to perform $ q $ queries for her on this sequence.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587E/13c69dfd57d48044360a9b122095311a6f41fd5f.png)There are two types of queries:

1. given numbers $ l,r $ and $ k $ , Malek should perform ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587E/8a1be9e3c00e9730bbb643a5d7ee378a339f739b.png) for each $ l<=i<=r $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587E/5b5823515617df7c58796c723b273483849bc16e.png), bitwise exclusive OR of numbers $ a $ and $ b $ ).
2. given numbers $ l $ and $ r $ Malek should tell her the score of sequence $ a_{l},a_{l+1},...\ ,a_{r} $ .

Score of a sequence $ b_{1},...,b_{k} $ is the number of its different Kheshtaks. A non-negative integer $ w $ is a Kheshtak of this sequence if and only if there exists a subsequence of $ b $ , let's denote it as $ b_{i1},b_{i2},...\ ,b_{ix} $ (possibly empty) such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF587E/1e3a601936704cd1f565653c79e75d2cbcc0e258.png) ( $ 1<=i_{1}&lt;i_{2}&lt;...&lt;i_{x}<=k $ ). If this subsequence is empty, then $ w=0 $ .

Unlike Duff, Malek is not a programmer. That's why he asked for your help. Please help him perform these queries.

## 说明/提示

In the first query, we want all Kheshtaks of sequence $ 1,2,3,4,2 $ which are: $ 0,1,2,3,4,5,6,7 $ .

In the third query, we want all Khestaks of sequence $ 1,10,3,4,2 $ which are: $ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 $ .

In the fifth query, we want all Kheshtaks of sequence $ 0 $ which is $ 0 $ .

## 样例 #1

### 输入

```
5 5
1 2 3 4 2
2 1 5
1 2 2 8
2 1 5
1 1 3 10
2 2 2
```

### 输出

```
8
16
1
```

# 题解

## 作者：lory1608 (赞：2)

本题的做法和这道题很类似[P5607 Ynoi2013无力回天NOI2017](https://www.luogu.com.cn/problem/P5607),是一道很好的线性基练手的题目。

首先，对于线性基，他是**离线数据结构**，不能删除数。所以不能支持区间修改。

那么根据线性基的性质，只要是两个线性基的元素个数相同，且其中一个线性基的每一个元素都可以被另一个线性基的一个或多个元素表示，那么这两个线性基是等价的。

对于此题，维护$b$数组，其中初始时$b_i=a_i \ xor \ a_{i-1}$,特别的$b_1=a_1$。这样就可以维护**前缀异或**。

那么对于查询操作$l \quad r$，那么就选取$a_l$和$b_{l+1},b_{l+2},\cdots,b_r$所组成的线性基，假设正式询问的序列是$c_1,c_2,\cdots,c_n$,那么$c_l=a_l$,对于$i \in(l,r]$都有$c_i=b_i \ xor \ c_{i-1}$。

所以用$a_l$和$b_{l+1},\cdots,b_r$组成的线性基与$c_l,\cdots,c_r$组成的线性基等价。

所以只用通过两个线段树，分别维护$b$的线性基支持**单点修改，区间查询**数组$a$支持**区间修改，单点查询**即可。

对于线段树维护$b$的线性基，只需要在树上合并线性基即可，合并方式是，将其中一个线性基中的元素暴力插入到另外一个线性基中。

对于询问只用输出$2^{cnt}$其中$cnt$表示该线性基中元素个数。

注意线性基在线段树上合并时要将原有的线性基清空。

时间复杂度$\Theta(n\log n\log w)$,空间复杂度$\Theta(n\log w)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#define ll long long
#define ull unsigned long long
using namespace std;
const int maxn=2e5+5;
inline int getint()
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
struct xxj
{
	static const int maxm=31;
	int a[32];
	inline void clear()
	{
		memset(a,0,sizeof(a));
	}
	inline void insert(int x)
	{
		for(int i=maxm;i>=0;--i)
		{
			if(x&(1<<i))
			{
				if(a[i])x^=a[i];
				else
				{
					a[i]=x;
					return ;
				}
			}
		}
	}
	inline void merge(xxj b)
	{
		for(int i=maxm;i>=0;--i)
		{
			if(b.a[i])insert(b.a[i]);
		}
	}
	inline int query()
	{
		int cnt=0;
		for(int i=maxm;i>=0;--i)if(a[i])cnt++;
		return (1<<cnt);
	}
};
int a[maxn];
int b[maxn],n,m,opt,x,y;
namespace A
{
	struct segmentree
	{
		#define ls u<<1
		#define rs u<<1|1
		int sum[maxn<<2],tag[maxn<<2];
		inline void pushdown(int u)
		{
			if(tag[u]==0)return ;
			tag[ls]^=tag[u];
			tag[rs]^=tag[u];
			sum[ls]^=tag[u];
			sum[rs]^=tag[u];
			tag[u]=0;
		}
		inline void build(int u,int l,int r)
		{
			if(l==r)
			{
				sum[u]=a[l];
			}
			else
			{
				int mid=(l+r)>>1;
				build(ls,l,mid);
				build(rs,mid+1,r);
			}
		}
		inline void update(int u,int l,int r,int x,int y,int v)
		{
			if(x<=l&&y>=r)
			{
				tag[u]^=v;
				sum[u]^=v;
			}
			else
			{
				int mid=(l+r)>>1;
				pushdown(u);
				if(x<=mid)update(ls,l,mid,x,y,v);
				if(y>mid)update(rs,mid+1,r,x,y,v);
			}
		}
		inline int query(int u,int l,int r,int x)
		{
			if(l==r)return sum[u];
			else
			{
				pushdown(u);
				int mid=(l+r)>>1;
				if(x<=mid)return query(ls,l,mid,x);
				else return query(rs,mid+1,r,x);
			}
		}
	}tree;
}
struct segmentree
{
	#define ls u<<1
	#define rs u<<1|1
	xxj a[maxn<<2];
	inline void pushup(int u)
	{
		a[u].clear();
		a[u].merge(a[ls]);
		a[u].merge(a[rs]);
	}
	inline void build(int u,int l,int r)
	{
		if(l==r)
		{
			a[u].insert(b[l]);
		}
		else
		{
			int mid=(l+r)>>1;
			build(ls,l,mid);
			build(rs,mid+1,r);
			pushup(u);
		}
	}
	inline void update(int u,int l,int r,int x,int v)
	{
		if(l==r)
		{
			a[u].clear();
			a[u].insert(v);
		}
		else
		{
			int mid=(l+r)>>1;
			if(x<=mid)update(ls,l,mid,x,v);
			else update(rs,mid+1,r,x,v);
			pushup(u);
		}
	}
	inline xxj query(int u,int l,int r,int x,int y)
	{
		if(x<=l&&y>=r)
		{
			return a[u];
		}
		else
		{
			xxj val;
			val.clear();
			int mid=(l+r)>>1;
			if(x<=mid)val.merge(query(ls,l,mid,x,y));
			if(y>mid)val.merge(query(rs,mid+1,r,x,y));
			return val;
		}
	}
}tree;
int main()
{
	n=getint(),m=getint();
	for(int i=1;i<=n;++i)a[i]=getint(),b[i]=a[i]^a[i-1];
	A::tree.build(1,1,n);
	tree.build(1,1,n);
	for(int i=1;i<=m;++i)
	{
		opt=getint(),x=getint(),y=getint();
		if(opt==1)
		{
			int val=getint();
			A::tree.update(1,1,n,x,y,val);
			if(y!=n)tree.update(1,1,n,y+1,b[y+1]^=val);
			tree.update(1,1,n,x,b[x]^=val);
		}
		else
		{
			xxj now;
			now.clear();
			now.insert(A::tree.query(1,1,n,x));
			if(x!=y)now.merge(tree.query(1,1,n,x+1,y));
			printf("%d\n",now.query());
		}
	}
	return 0;
}
```

线性基合并是两个$\log$的。

---

## 作者：xlpg0713 (赞：1)

与 [P5607](https://www.luogu.com.cn/problem/P5607) 是双倍经验。

## 题意
转化后的题意都为在序列上的区间异或，查询区间线性基。

## 题解
先考虑弱化版，$l=r$，即单点修改。

考虑到一般的线性基支持 $O(\log v^2)$ 的合并，但是不支持删除，把区间拍到线段树上，单点修改是简单的，直接做就行，加上线段树的一只 $\log$ 是 $O((n+q)\times\log_n\times\log_v^2)$，一看数据范围可过。所以考虑怎么把原问题转化成单点修改。

想到了差分 $b_i=a_i\oplus a_{i-1},b_1=a_1$ 因为有 $x\oplus y\oplus y=x$ 易于证明 $a_l$ 到 $a_r$ 的线性基是 $a_l$ 与 $b_{l+1}-b_r$ 的线性基。

到现在就做完了，维护 $b$ 的线性基，然后就是正常的单点修改了。

代码很好写：

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
const int N = 2e5 + 10;
struct nd{ int a[35];
    void ins(int x){
        for(int i = 29; ~i; i--) if(x & (1 << i))
        if(a[i]) x ^= a[i]; else return void(a[i] = x);
    }
}t[N << 2];
nd mg(nd x, nd y){nd rs = x;
    for(int i = 29; ~i; i--)
        if(y.a[i]) rs.ins(y.a[i]);
    return rs;
}int n, m, a[N], b[N];
inline void is(int p, int x){while(p <= n) b[p] ^= x, p += p & -p;}
inline int qa(int p){int r = 0;while(p) r ^= b[p], p -= p& -p; return r;}
inline void ins(int p, int l, int r){
    if(l == r) return t[p].ins(a[l]);
    int mid = l + r >> 1;
    ins(p * 2, l, mid), ins(p * 2 + 1, mid + 1, r);
    t[p] = mg(t[p * 2], t[p * 2 + 1]);
}inline void upd(int p, int l, int r, int x, int k){
    if(l == r) return memset(t[p].a, 0, sizeof t[p].a), t[p].ins(a[l] ^= k);
    int mid = l + r >> 1; if(x <= mid) upd(p * 2, l, mid, x, k);
    else upd(p * 2 + 1, mid + 1, r, x, k); t[p] = mg(t[p * 2], t[p * 2 + 1]);
}inline nd qry(int p, int l, int r, int L, int R){
    if(l >= L && r <= R) return t[p];
    int mid = l + r >> 1;
    if(R <= mid) return qry(p * 2, l, mid, L, R);
    if(L > mid) return qry(p * 2 + 1, mid + 1, r, L, R);
    return mg(qry(p * 2, l, mid, L, R), qry(p * 2 + 1, mid + 1, r, L, R));
}int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);std::cout.tie(0);
    std::cin >> n >> m;
    for(int i = 1; i <= n; i++) std::cin >> a[i];
    for(int i = n; i > 1; i--) a[i] = a[i] ^ a[i - 1], is(i, a[i]); is(1, a[1]);
    ins(1, 1, n); while(m--){ int op, l, r, x; std::cin >> op >> l >> r;  
        if(op == 1) {std::cin >> x; is(l, x), upd(1, 1, n, l, x);
        if(r < n) is(r + 1, x), upd(1, 1, n, r + 1, x);}
        else{
            int k = qa(l); if(l == r){std::cout << (k ? 2 : 1) << '\n'; continue;}
            nd o = qry(1, 1, n, l + 1, r); o.ins(k); int ct = 0;
            for(int i = 29; ~i; i--) if(o.a[i]) ct++;
            std::cout << (1 << ct) << '\n';
        }
    }
}
```

---

## 作者：AAA404 (赞：0)

写给审核管理员：这篇题解动笔时洛谷 RMJ 不能正常提交，故在洛谷上没有 AC，CF 记录在[这里](https://codeforces.com/contest/587/submission/277853097)。

以下是正文。



---

异或数据结构首先应该想到：

- 01Tire

- 异或线性基

前者无法支持高效的修改，以及本题要求查询的内容无法维护，因此选用后者。

一般线性基是建立在全局上的，本题要求区间操作，可以考虑再套一层数据结构维护。

可以选用分块和线段树，其中分块复杂度较大，但是时限足够，可能可以通过，本题解将采用线段树解法，具体原因后续就知道了。

## Case 1

区间修改不好对线性基进行，所以考虑通过差分将区间操作变为单点操作。

具体的，设 $b_i=a_i \operatorname{xor} a_{i-1}$，由数学基础知识可得由 $a_x$ 和 $b_{x+1},b_{x+2},...,b_y$ 组成的线性基和原序列的线性基等价。

因此需要维护序列 $\{a\}$ 和 $\{b\}$，其中前者需要支持区间异或，单点查值，使用树状数组/线段树可以做到 $O(\log n)$；后者维护线性基，直接在线段树上合并线性基，单次合并暴力插入复杂度是 $O(\log V)$ 的，可以接受。

## Case 2

记区间线性基不为 $0$ 的位数为 $x$，那么答案就是 $2^x$。

证明显然，留作思考。



---



代码核心片段：


```cpp
void merge(cly b)//线性基合并，cly 是线性基封装
{
        for(int i=31;i>=0;i--)
        {
            if(b.d[i])insert(b.d[i]);
        }
}
```



---

为什么要采用线段树做法呢？因为有[双倍经验](https://www.luogu.com.cn/problem/P5607)，但是这题用分块会被卡常。

双倍经验题做法就是把统计答案改成贪心按位选择就行。

---

