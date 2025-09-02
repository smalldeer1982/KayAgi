# Circular

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2018/tasks/tenka1_2018_f

整数 $ N $ 個からなる列 $ A_1,A_2,...,A_N $ が与えられます。

$ 1,2,...,N $ の並び替え $ p_1,p_2,...,p_N $ であって、 次の操作を何度か行うことでこの列を $ A_1,A_2,...,A_N $ に変換できるようなものの個数を $ 998244353 $ で割ったあまりを求めてください。

- 各 $ 1\leq\ i\leq\ N $ に対し、$ q_i=min(p_{i-1},p_{i}) $ とする。ただし、$ p_0=p_N $ とする。列 $ p $ を列 $ q $ で置き換える。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3\ ×\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ N $
- 入力はすべて整数である

### Sample Explanation 1

$ (2,3,1),(3,2,1) $ が条件を満たします。

## 样例 #1

### 输入

```
3
1
2
1```

### 输出

```
2```

## 样例 #2

### 输入

```
5
3
1
4
1
5```

### 输出

```
0```

## 样例 #3

### 输入

```
8
4
4
4
1
1
1
2
2```

### 输出

```
24```

## 样例 #4

### 输入

```
6
1
1
6
2
2
2```

### 输出

```
0```

# 题解

## 作者：stntn (赞：3)

## 题意

给定一个长为 $n$ 的序列 $A$，求排列 $P$ 的个数，可以通过若干次以下操作使其与 $A$ 相同。

- $\forall i \in [2,n],\min(a_i,a_{i-1}) \to a_i$，特别的，$a_1 =\min(a_1,a_n)$。

## 分析

首先易知，在 $A$ 中不可能存在有同一种数字出现在不同段中的情况，否则无解。

此时 $1$ 所在连续段的长度即为总操作次数，记为 $m$。

那么对于任意 $i$，$p_i \ge \max\{p_i,p_{i+1},\cdots , p_{i+m-1}\}$（断环为链）。这是显然的。对于任意数字 $x$，他在 $P$ 中的位置仅可能是满足以上条件的位置。

此外，如果数字 $x$ 在 $A$ 中出现且连续段为 $[l,r]$，那么额外要求这个数字的位置在 $[r-m+1,l]$  内。

令 $cnt_x= \sum_{1 \le i \le n} [\max\{p_i,p_{i+1},\cdots , p_{i+m-1}\}\le x]$，对于一个无额外要求的数字 $x$，对答案乘以 $cnt_x-(x-1)$，即 $cnt_x$ 位置中已选 $x-1$ 个位置剩余可选位置数，否则乘以符合要求的位置数。

至于实现上随便写写就行了，对于有要求的数字用 BIT 区间内小于自己的数字就行了。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 600010
#define M 100010
#define int long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define mod 998244353
#define INF 0x3f3f3f3f
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int n,p,ans,qcc,a[N],l[N],r[N],len[N],cnt[N],can[N],mx[N];
struct QUEUE
{
	pir q[N];int head,tail;
	inline void init(){head=1;tail=0;}
	inline void push(pir x){for(;head<=tail&&q[tail]<=x;tail--);q[++tail]=x;}
	inline int front(){return head>tail?-1:q[head].fi;}
	inline void pop(int t){for(;head<=tail&&q[head].se>t;head++);}
}q;
struct BIT
{
	int sum[N];
	inline void update(int x,int v){for(;x<=n;x+=x&-x) sum[x]+=v;}
	inline int query(int x){int r=0;for(;x;x-=x&-x) r+=sum[x];return r;}
}t;
struct QUERY
{
	int p,id,w;
	bool operator < (const QUERY &b) const {return p<b.p;}
}Q[N<<1];
signed main()
{
	read(n);ans=1;
	rep(i,1,n) read(a[i]),a[n+i]=a[i];
	p=1;for(;a[p]==a[n]&&p<=n;p++);
	if(p==n+1) if(a[1]==1)
	{
		rep(i,1,n) (ans*=i)%=mod;
		return printf("%lld\n",ans),0;
	}
	else return printf("0\n"),0;
	rep(i,1,n) a[i]=a[i+p-1];
	rep(i,1,n) a[i+n]=a[i];
	rep(i,1,n)
	{
		if(l[a[i]]) return printf("0\n"),0;
		l[a[i]]=i;
		for(;a[i]==a[i+1]&&i<n;i++);
		r[a[i]]=i;len[a[i]]=r[a[i]]-l[a[i]]+1;
	}
	rep(i,2,n) if(len[i]>len[1]) return printf("0\n"),0;
	q.init();
	per(i,n+len[1]-1,n+1) q.push(mp(a[i],i));
	per(i,n,1)
	{
		q.push(mp(a[i],i));q.pop(i+len[1]-1);
		cnt[mx[i]=q.front()]++;
	}
	rep(i,1,n) mx[i+n]=mx[i];
	rep(i,2,n) cnt[i]+=cnt[i-1];
	rep(i,1,n) if(l[i])
	{
		Q[++qcc]={r[i]-len[1]<0?r[i]-len[1]+n:r[i]-len[1],i,-1};
		Q[++qcc]={r[i]-len[1]<0?l[i]+n:l[i],i,1};
	}
	sort(Q+1,Q+1+qcc);
	for(int i=1,j=1;i<=n<<1;i++)
	{
		t.update(mx[i],1);
		for(;Q[j].p<i&&j<=qcc;j++);
		for(;Q[j].p==i&&j<=qcc;j++) can[Q[j].id]+=Q[j].w*t.query(Q[j].id);
	}
	rep(i,1,n)
	{
		if(l[i]) (ans*=can[i])%=mod;
		else (ans*=(cnt[i]-(i-1)))%=mod;
	}
	printf("%lld\n",ans);
	return 0;
}

```

---

