# Equilibrium

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556E/82dac8544603b5a29531fd9591e7750ab2f3a8ad.png)William has two arrays $ a $ and $ b $ , each consisting of $ n $ items.

For some segments $ l..r $ of these arrays William wants to know if it is possible to equalize the values of items in these segments using a balancing operation. Formally, the values are equalized if for each $ i $ from $ l $ to $ r $ holds $ a_i = b_i $ .

To perform a balancing operation an even number of indices must be selected, such that $ l \le pos_1 < pos_2 < \dots < pos_k \le r $ . Next the items of array a at positions $ pos_1, pos_3, pos_5, \dots $ get incremented by one and the items of array b at positions $ pos_2, pos_4, pos_6, \dots $ get incremented by one.

William wants to find out if it is possible to equalize the values of elements in two arrays for each segment using some number of balancing operations, and what is the minimal number of operations required for that. Note that for each segment the operations are performed independently.

## 说明/提示

For the first segment from $ 2 $ to $ 6 $ you can do one operation with $ pos = [2, 3, 5, 6] $ , after this operation the arrays will be: $ a = [0, 2, 2, 9, 4, 2, 7, 5] $ , $ b = [2, 2, 2, 9, 4, 2, 5, 8] $ . Arrays are equal on a segment from $ 2 $ to $ 6 $ after this operation.

For the second segment from $ 1 $ to $ 7 $ you can do three following operations:

1. $ pos = [1, 3, 5, 6] $
2. $ pos = [1, 7] $
3. $ pos = [2, 7] $

After these operations, the arrays will be: $ a = [2, 2, 2, 9, 4, 2, 7, 5] $ , $ b = [2, 2, 2, 9, 4, 2, 7, 8] $ . Arrays are equal on a segment from $ 1 $ to $ 7 $ after these operations.

For the third segment from $ 2 $ to $ 4 $ you can do one operation with $ pos = [2, 3] $ , after the operation arrays will be: $ a = [0, 2, 2, 9, 3, 2, 7, 5] $ , $ b = [2, 2, 2, 9, 4, 1, 5, 8] $ . Arrays are equal on a segment from $ 2 $ to $ 4 $ after this operation.

It is impossible to equalize the fourth and the fifth segment.

## 样例 #1

### 输入

```
8 5
0 1 2 9 3 2 7 5
2 2 1 9 4 1 5 8
2 6
1 7
2 4
7 8
5 8```

### 输出

```
1
3
1
-1
-1```

# 题解

## 作者：juju527 (赞：12)

### $\texttt{Solution}$

考虑记序列 $c$，满足 $c_i=b_i-a_i$。

原操作相当于在 $c$ 上对于一个长为偶数的子序列做 $-1,+1,\cdots,-1,+1$ 操作。

最终要求 $c$ 序列某段区间全为 0 的最小操作次数。

由于做一次操作后序列总和不会改变，观察到区间 $[l,r]$ 能由操作变为 0 至少满足 $\sum_{i}c_i=0$。

我们如果把正数 $x$ 看成 $x$ 个左括号，负数 $y$ 看成 $|y|$ 个右括号。

我们的操作等价于任选括号序列里的一个形如 $(\ )(\ )(\ )\cdots$ 的子序列删去。

由于只能删去一个合法括号序列，原序列也一定为合法括号序列才能有解。

结论是最小操作次数为括号序列前缀最大左括号剩余值。

考虑归纳证明：

我们首先将括号序列分为 $(\cdots)$ 和 $(\cdots)(\cdots)(\cdots)$ 型两种。

对于后者，其最小操作次数显然为每一段合法括号序列答案的最大值。

等价于前缀最大值，我们考虑第一种情况即可。

显然，大小为 2 的合法括号序列满足此结论。

若长度小于 $n$ 的合法括号序列均满足此结论。

对于一个长度为 $n$ 的形式1型合法括号序列。

我们先将其最外的一层括号拨开，里面一定是一个 $n-1$ 层的形式1型序列或者一个形式2形序列。

有归纳可知，这部分的答案为前缀最大值，记其为 $s$。

又因为最外层的一对括号没法和任意一对括号在同一次操作里被消除。

最终这个序列的答案应该为 $s+1$。

最外一层括号对前缀和的影响相当于整体加一并在最末尾补0，最大值将变为 $s+1$。

满足，故归纳成立。

得到结论后，我们仅需维护前缀最大/小值即可，可以线段树/st表解决。

时间复杂度 $O(n\log n)$。

[code](https://codeforces.com/contest/1556/submission/127426300)

---

## 作者：Cry_For_theMoon (赞：7)

[传送门](https://codeforces.com/contest/1556/problem/E)

这场的题非常棒！但是我打拉胯了...

#### 前言：

hack了一车人（包括自己）的数据（自己躺床上摸鱼的时候随便造的）：

```
2 1
3 0
0 3 
1 2
```

应该输出无解。

#### 分析：

这个题，看上去是完全没有头绪的，但是 CF 上这样的类似题还是很多的，无非就是猜个结论然后用 DS 去搞搞。所以我们不要怕，直接研究整个序列的操作方案。

首先你发现一个事情是 $a,b$ 的具体值是不重要的，对于同一个位置的 $a,b$ 我们只关心他们的差。所以我们记 $c_i=b_{i}-a_i$，这个时候，你发现原来的操作变成了这样：

选择 $k$ 个下标 $pos_1\lt pos_2 \lt ... \lt pos_k$，然后把 $c_{pos_1},c_{pos_3},...,c_{pos_{k-1}}$ 全部减一，其它的减加一。

我们的目标是让每个数变成 $0$，然后很快你就会发现这意味着 $\sum c=0$。否则一定无解。

那么我们不妨来把这个操作再放在 $c$ 的前缀和 $d_i=\sum_{j=1}^{i}c_j$ 上去看。你会发现，让 $c_{pos_1}$ 减一实际上意味着把 $d_{pos_1}$ 一直到 $d_n$ 都减去一；让 $c_{pos_2}$ 加一实际上意味着把 $d_{pos_2}$ 一直到 $d_n$ 都加上一，也就是说此时只有 $[pos_1,pos_2-1]$ 这段的 $d$ 被减一。更一般地，由于是一减一加地操作，所以操作等价于在 $d$ 上选若干个不相邻区间然后把这些区间的 $d$ 全部减一。

不过这里还有一点小问题，就是你的区间不能对最后一个数减一，因为不能在后面在找到一个位置 $+1$ 了。但是因为我们要求 $d_n=0$ 所以对它的减法是没有必要存在的。那么一切都很对了！

我们的目标是让每个 $d$ 都变成 $0$。也就是说如果一开始就有一个 $d$ 小于 $0$ 那么一样无解。否则答案显然是 $ans=\max\{d\}$，只需要考虑每一轮让所有最大的数减去 $1$ 就可以了。

所以我们需要维护的是 $d$ 的最大值和最小值，然后就可以 $O(1)$ 去回答。考虑区间查询这个东西，你发现其实就是全局的 $d$ 每个都减去 $d_{l-1}$，由于减的是同一个数，所以最大值和最小值的出现位置是不变的，只需要询问 $\max\{d\}$ 然后减去 $d_{l-1}$ 就可以了，$\min$ 查询同理。

时间复杂度：$O(n\log n+q)$。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e5+10;
int n,q,l,r;
ll a[MAXN],b[MAXN],c[MAXN],d[MAXN];
ll power[20],logn[MAXN];
struct ST{
	ll minn[MAXN][20],maxn[MAXN][20];
	void build(){
		rep(i,1,n)minn[i][0]=maxn[i][0]=d[i];
		rep(j,1,19){
			rep(i,1,n){
				if(i+power[j]-1>n)break;
				minn[i][j]=min(minn[i][j-1],minn[i+power[j-1]][j-1]);
				maxn[i][j]=max(maxn[i][j-1],maxn[i+power[j-1]][j-1]);
			}
		}
	}
	ll querymin(int l,int r){
		int len=logn[r-l+1];
		return min(minn[l][len],minn[r-power[len]+1][len]);
	}
	ll querymax(int l,int r){
		int len=logn[r-l+1];
		return max(maxn[l][len],maxn[r-power[len]+1][len]);
	}
}st;
int main(){
	power[0]=1;rep(i,1,19)power[i]=power[i-1]*2;
	logn[0]=-1;rep(i,1,1e5)logn[i]=logn[i>>1]+1;
	scanf("%d%d",&n,&q);
	rep(i,1,n){
		scanf("%lld",&a[i]);
	}
	rep(i,1,n){
		scanf("%lld",&b[i]);
	}
	rep(i,1,n){
		c[i]=b[i]-a[i];
		d[i]=d[i-1]+c[i];
	}
	st.build();
	rep(i,1,q){
		scanf("%d%d",&l,&r);
		if(d[r]-d[l-1]!=0){
			printf("-1\n");
			continue;
		}
		ll minn=st.querymin(l,r),maxn=st.querymax(l,r);
		minn-=d[l-1];maxn-=d[l-1];
		if(minn<0){
			printf("-1\n");
			continue;
		}
		printf("%lld\n",maxn);
	}

	return 0;
}
```

---

## 作者：myee (赞：6)

### 前言

五发罚时害死人！

莫队平衡复杂度差不多得了！

---

### 题意

给你两个长度为 $n$ 的自然数序列，$a$ 和 $b$。

规定在 $[l,r]$ 范围内的**平衡操作**，是指自由选出一段长度为偶数 $k$ 的整数序列 $pos$，使得 $l\le pos_1<pos_2<\dots<pos_k\le r$，然后令 $pos_1,pos_3,pos_5,pos_7,\dots,pos_{k-1}$ 位置的 $a$ 加一，令 $pos_2,pos_4,pos_6,pos_8,\dots,pos_k$ 位置的 $b$ 加一。

$q$ 次询问，每次询问给你一段区间 $[l,r]$，问你至少做几次该区间内的平衡操作，可以使 $[l,r]$ 间所有位置满足 $a=b$，无解输出 $-1$。询问独立。

数据范围：$2\le n\le10^5$，$1\le q\le10^5$，$0\le a_i,b_i\le10^9$，$1\le l<r\le n$。

---

### 思路

#### 转化题意

记 $A=a-b$，则题意转化为：

给你一个长度为 $n$ 的整数序列 $A$。

规定在 $[l,r]$ 范围内的平衡操作，是指自由选出一段长度为偶数 $k$ 的整数序列 $pos$，使得 $l\le pos_1<pos_2<\dots<pos_k\le r$，然后令 $pos_1,pos_3,pos_5,pos_7,\dots,pos_{k-1}$ 位置的 $A$ 加一，令 $pos_2,pos_4,pos_6,pos_8,\dots,pos_k$ 位置的 $A$ 减一。

$q$ 次询问，每次询问给你一段区间 $[l,r]$，问你至少做几次该区间内的平衡操作，可以使 $[l,r]$ 间所有位置满足 $A=0$，无解输出 $-1$。询问独立。

数据范围：$2\le n\le10^5$，$1\le q\le10^5$，$-10^9\le A_i\le10^9$，$1\le l<r\le n$。

---

#### 分析

有了 $A$ 数组还不够，我们依旧需要一个条件来判断是否有解。

I.显然若区间内 $A$ 数组的和不是 $0$，则必然无解。

II.同时，若区间内存在前缀和为正数 $m$ ，则亦无解。

> 证明：
>
> 由每次操作对前缀和的影响一定不减且最多加一可得。
>
> 因为序列 $D:\big<0,\dots,0,1,0,\dots,0,-1,0,\dots,0,1,0,\dots,0,-1,0,\dots\big>$ 序列的前缀和序列 $\sum D$ 中每一项不是 $0$ 就是 $1$，由前缀和的线性性即 $\sum(A+D)=\sum A+\sum D$ ，这个 $m$ 必然不减而无法变为 $0$。

除去这两种情况，剩下的情况都容易构造方案，即利用上述论述中操作对前缀和的影响（$\sum D:\big<0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1,0,0,\dots\big>$）来构造，构造方案略。

III.不难发现答案即区间内最大的**前缀和的相反数**，或者说区间内**最小前缀和**的相反数，即 $-\min\{\sum A\}$，证明由构造方案与证明下界两部分组成，此处略去。

---

考虑怎么快速判断。

对情况 I，直接维护全局前缀和数组即可。

对情况 II，等价于区间内最大前缀和为正，这个可以转化成序列上两个前缀和的差，于是就要维护全局前缀和数组，要求查询区间 $\max$，用 ST 表即可。

对情况 III，等价于求区间内最小前缀和，这个也可以转化成序列上两个前缀和的差，于是就要维护全局前缀和数组，要求查询区间 $\min$，用 ST 表即可。

复杂度 $O(n\log n) - O(1)$。

---

由于赛前在练习莫队，于是赛场上没有想到 ST 表，胡了一个奇妙的平衡复杂度莫队做法，大致方法类似，就是将全局前缀和数组先离散化再插入一个值域分块里面，反正是个非常谔谔的做法。

复杂度 $O(n\sqrt n)$。

结果拿了 $5$ 发罚时，写了亿年才过（

---

### Code

给出平衡复杂度莫队版的代码。

```cpp
// Problem: E. Equilibrium
// Contest: Codeforces - Deltix Round, Summer 2021 (open for everyone, rated, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1556/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms

#include <algorithm>
#include <math.h>
#include <set>
#include <map>
#include <stdio.h>
typedef long long llt;
typedef unsigned uint;typedef unsigned long long ullt;
typedef bool bol;typedef char chr;typedef void voi;
typedef double dbl;
template<typename T>bol _max(T&a,T b){return(a<b)?a=b,true:false;}
template<typename T>bol _min(T&a,T b){return(b<a)?a=b,true:false;}
template<typename T>T power(T base,T index,T mod){return((index<=1)?(index?base:1):(power(base*base%mod,index>>1,mod)*power(base,index&1,mod)))%mod;}
template<typename T>T lowbit(T n){return n&-n;}
template<typename T>T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T>T lcm(T a,T b){return(a!=0||b!=0)?a/gcd(a,b)*b:(T)0;}
template<typename T>T exgcd(T a,T b,T&x,T&y){if(!b)return y=0,x=1,a;T ans=exgcd(b,a%b,y,x);y-=a/b*x;return ans;}
template<const uint Sqrt=1500>
struct Block
{
	uint A[Sqrt*Sqrt],B[Sqrt];
	Block()
	{
		for(uint i=0;i<Sqrt*Sqrt;i++)A[i]=0;
		for(uint i=0;i<Sqrt;i++)B[i]=0;
	}
	voi insert(uint v){A[v]++,B[v/Sqrt]++;}
	voi erase(uint v){A[v]--,B[v/Sqrt]--;}
	uint findmin()
	{
		for(uint i=0;i<Sqrt;i++)if(B[i])
			for(uint j=0;j<Sqrt;j++)if(A[i*Sqrt+j])return i*Sqrt+j;
		return-1;
	}
	uint findmax()
	{
		for(uint i=Sqrt-1;~i;i--)if(B[i])
			for(uint j=Sqrt-1;~j;j--)if(A[i*Sqrt+j])return i*Sqrt+j;
		return-1;
	}
};
Block<>B;
uint Siz;
struct ques{uint l,r,t;llt ans;};
bol cmp1(const ques&a,const ques&b){return(a.l/Siz==b.l/Siz)?(((a.l/Siz)&1)?b.r<a.r:(a.r<b.r)):(a.l<b.l);}
bol cmp2(const ques&a,const ques&b){return a.t<b.t;}
llt A[100005],_S[100005],User[100005];
uint S[100005];
ques Q[100005];
uint l,r;
std::set<llt>Set;
std::map<llt,uint>Map;
llt sgn(llt v){return(v>0)?1:(v?-1:0);}
voi insert(uint m){B.insert(S[m+1]);}
voi erase(uint m){B.erase(S[m+1]);}
int main()
{
	uint n,m;llt v;
	scanf("%u%u",&n,&m),Siz=sqrt(n);
	for(uint i=0;i<n;i++)scanf("%lld",A+i);
	for(uint i=0;i<n;i++)scanf("%lld",&v),Set.insert(_S[i+1]=_S[i]+(A[i]-=v));
	Set.insert(0);
	while(!Set.empty())User[Map[*Set.rbegin()]=Set.size()]=*Set.rbegin(),Set.erase(*Set.rbegin());
	for(uint i=0;i<=n;i++)S[i]=Map[_S[i]];
	for(uint i=0;i<m;i++)scanf("%u%u",&Q[i].l,&Q[i].r),Q[i].l--,Q[i].t=i;
	std::sort(Q,Q+m,cmp1),l=r=0;
	for(uint i=0;i<m;i++)
	{
		ques&qs=Q[i];
		while(l>qs.l)insert(l-1),l--;
		while(r<qs.r)insert(r),r++;
		while(l<qs.l)erase(l),l++;
		while(r>qs.r)erase(r-1),r--;
		qs.ans=(B.findmax()==S[l]&&S[r]==S[l])?User[S[l]]-User[B.findmin()]:-1;
	}
	std::sort(Q,Q+m,cmp2);
	for(uint i=0;i<m;i++)printf("%lld\n",Q[i].ans);
	return 0;
}
```


---

## 作者：Otomachi_Una_ (赞：3)

## 题目简述

- 给两个长度为 $n$ 的数列 $a_i,b_i$。
- 给出 $q$ 次询问，每次询问 $l,r$。问要进行多少次操作才可以让 $\forall i\in[l,r],a_i=b_i$。
- 一次操作指选出 $l\leq p_1<p_2\dots <p_{2k}$，$a_{p_{2i}}$ 加一，$b_{p_{2i+1}}$ 加一。
- $n,q\leq 10^5$，$a_i\leq10^9$。

## 解题思路

这个操作好像只和 $a_i-b_i$ 有关。我们假设 $c_i=a_i-b_i$。那么每一次操作就是 选出 $l\leq p_1<p_2\dots <p_{2k}$，$c_{p_{2i}}$ 加一，$c_{p_{2i+1}}$ 减一。我们最终的目标是让 $c_l=c_{l+1}\dots =c_r$。

那么这样的 $\sum_{i=l}^r c_i$ 是不变的。也就是如果 $\sum c_i\not = 0$ 那么直接输出 `-1` 即可。

对于每一个 $i\in [l,r]$，我们会发现无论怎么操作，$\sum_{j=l}^i c_j$ 的值是不减的。也就是说如果有一个 $i$ 使得 $\sum_{j=l}^i c_j>0$ 就只能无解了。

剩余的情况考虑 $\sum_{j=l}^i c_j$ 的最小值，因为每一次操作最多让此值加一。所以答案就是 $|\sum_{j=l}^i c_j|$

## 参考代码

通过 ST 表和前缀和解决。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define ll long long
const int MAXN=1e5+5;
int n,q;
int a[MAXN];
ll s[MAXN];
ll mx[20][MAXN],mn[20][MAXN];
inline int read(){
	int re=0;char ch=getchar();
	while(ch>'9'||ch<'0') ch=getchar();
	while(ch>='0'&&ch<='9') re=10*re+ch-'0',ch=getchar();
	return re;
}
void init(){
	for(int i=1;i<=n;i++)
		mx[0][i]=mn[0][i]=s[i];
	for(int i=1;i<=19;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<i-1)]),
			mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<i-1)]);
	return;
}
ll Mx(int l,int r){
	int len=log2(r-l+1);
	return max(mx[len][l],mx[len][r-(1<<len)+1]);
}
ll Mn(int l,int r){
	int len=log2(r-l+1);
	return min(mn[len][l],mn[len][r-(1<<len)+1]);
}
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) a[i]-=read();
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];//前缀和 
	init();
	while(q--){
		int l=read(),r=read();
		if(s[r]-s[l-1]!=0||Mx(l,r)>s[l-1]) cout<<"-1"<<endl;
		else cout<<-Mn(l,r)+s[l-1]<<endl;
	}
	return 0;
} 
```


---

## 作者：白鲟 (赞：3)

### 前言
我恨 inf。

### 分析
很自然地把操作全部转化到 $a$ 上，奇数位置加，偶数位置减，使得 $a_i=b_i$。容易想到令 $a_i'=a_i-b_i$，即每个 $a_i$ 所需的改变量。

先判断可行性。把一次操作拆成若干对一加一减的操作，发现这个操作可看作括号匹配，于是 $a_i'$ 在 $[l,r]$ 上的前缀和非负且总和为 $0$。后一个条件容易判断。前一个条件写出式子为 $\forall i,sum_i-sum_{l-1}\ge 0$，于是 $\min\{sum_i\}\ge sum_{l-1}$。线段树维护区间最小值即可。（当然也可以使用我赛时那样离线树状数组查询区间小于某个数的个数的巨大复杂做法……）

得到可行性后构造最优答案，即将加减法两两配对后把多个对使用一组操作完成。根据前缀和非负的性质，减法操作附属于加法操作，于是只需考虑加法操作每次添加的组数。对于每一个 $a_i>0$，能够加入之前组的数量是之前存在的组数中以 $-1$ 结尾的个数，同时这些组的结尾添加一个 $1$，可用组数不足 $a_i$ 则补足；而每遇到 $a_i<0$，则可以将 $-a_i$ 个结尾为 $1$ 组的结尾添加一个 $-1$。发现这一系列操作得到的组数事实上是 $sum_i-sum_{l-1}$ 的最大值，线段树维护即可。

注意线段树查询最大值区间不相交时返回的极小值不能为 $0$……

### 代码
```cpp
#include<bits/stdc++.h>
#define loop(i,from,to) for(ll i=(from);i<=(to);++i)
using namespace std;
typedef long long ll;
const ll maxn=2e5+5,inf=0x3f3f3f3f3f3f3f3fll;
ll n,q,x,y,a[maxn+1],sum[maxn+1],maxof[maxn<<2|1],minof[maxn<<2|1];
void build(int now,int l,int r){
	if(l==r){
		maxof[now]=minof[now]=sum[l];
		return;
	}
	int mid=(l+r)/2;
	build(now<<1,l,mid),build(now<<1|1,mid+1,r),maxof[now]=max(maxof[now<<1],maxof[now<<1|1]),minof[now]=min(minof[now<<1],minof[now<<1|1]);
	return;
}
ll SGT_max(int now,int l,int r,int target_l,int target_r){
	if(target_l>r||target_r<l)return -inf;
	if(target_l<=l&&r<=target_r)return maxof[now];
	int mid=(l+r)/2;
	return max(SGT_max(now<<1,l,mid,target_l,target_r),SGT_max(now<<1|1,mid+1,r,target_l,target_r));
}
ll SGT_min(int now,int l,int r,int target_l,int target_r){
	if(target_l>r||target_r<l)return inf;
	if(target_l<=l&&r<=target_r)return minof[now];
	int mid=(l+r)/2;
	return min(SGT_min(now<<1,l,mid,target_l,target_r),SGT_min(now<<1|1,mid+1,r,target_l,target_r));
}
int main(){
	scanf("%lld%lld",&n,&q);
	loop(i,1,n)scanf("%lld",&a[i]);
	loop(i,1,n)scanf("%lld",&x),sum[i]=sum[i-1]+(a[i]=x-a[i]);
	build(1,1,n);
	loop(i,1,q){
		scanf("%lld%lld",&x,&y);
		if(SGT_min(1,1,n,x,y)<sum[x-1]||sum[y]-sum[x-1])puts("-1");
		else printf("%lld\n",SGT_max(1,1,n,x,y)-sum[x-1]);
	}
	return 0;
}
```

---

## 作者：KellyFrog (赞：2)

我们将题目进行一步转化，第 $i$ 个位置上有数 $v_i=a_i-b_i$，每次可以选偶数个位置，将奇数位增大 1，将偶数位减小 1，显然一个位置不可能先增大再减小

我们考虑每次选两个数出来会怎么样，不难发现可以把连续一段正的和连续一段负的合成一段，之后一定是相邻两个后面移到前面，如果一堆剩下 0 了，就再把前后两堆合并

这样我们就可以判掉无解——区间里的后缀和必须 $\ge 0$，且区间和 $=0$

我们再做一次转化，不难发现答案等于 $\max\{\text{每堆被消掉的时间}\}$，对一个 $v_i$ 算这个玩意有显然的下界 $v_i$

接下来不妨考虑连续的三堆 $v_{i},v_{i+1},v_{i+2}(v_{i+1}>0)$，一次之后会消成 $v_i+v_{i+1},0,v_{i+2}+v_{i+1}$，合并起来是 $v_{i}+v_{i+2}+2\cdot v_{i+1}$，加上原来花费的时间，刚好是 $v_{i}+v_{i+1}+v_{i+2}$

观察这一过程，每次合并两堆，最后一个点所在的一定是一段区间，而没有取到的区间一定是正的被消没了，选上也不会更优，所以答案就是这个区间的最大子段和（显然最大子段和自动帮我们做好了把连着一段拼在一起的工作）

上线段树维护，复杂度 $O(n+q\log n)$


```cpp
// Problem: Equilibrium
// Contest: Codeforces
// URL: http://m2.codeforces.com/contest/1556/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

/* template ends here */

const int N = 1e5 + 5;

int a[N], b[N], c[N];
int n, q;
ll suf[N];

struct Node {
	ll premx, sufmx, mxval, sum;
	ll misuf;
};

Node tree[N << 2];
Node res; bool isfirst;

Node merge(const Node& x, const Node& y) {
	Node ret;
	ret.sum = x.sum + y.sum;
	ret.premx = max(x.premx, y.premx + x.sum);
	ret.sufmx = max(y.sufmx, x.sufmx + y.sum);
	ret.mxval = max(max(x.mxval, y.mxval), x.sufmx + y.premx);
	ret.misuf = min(x.misuf, y.misuf);
	return ret;
}

void build(int cur, int l, int r) {
	if(l == r) {
		tree[cur].premx = tree[cur].sufmx = tree[cur].mxval = max(0, a[l] - b[l]);
		tree[cur].sum = a[l] - b[l];
		tree[cur].misuf = suf[l];
		return;
	}
	int mid = l + r >> 1;
	build(cur << 1, l, mid);
	build(cur << 1 | 1, mid + 1, r);
	tree[cur] = merge(tree[cur << 1], tree[cur << 1 | 1]);
}

void query(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		if(isfirst) res = tree[cur], isfirst = 0;
		else res = merge(res, tree[cur]);
		return;
	}
	int mid = l + r >> 1;
	if(ql <= mid) query(cur << 1, ql, qr, l, mid);
	if(mid < qr) query(cur << 1 | 1, ql, qr, mid + 1, r);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cout << fixed << setprecision(15); cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	per(i, 1, n) suf[i] = suf[i+1] + a[i] - b[i];
	
	build(1, 1, n);
	
	while(q--) {
		int l, r;
		cin >> l >> r;
		isfirst = 1;
		query(1, l, r, 1, n);
		if(res.misuf - suf[r+1] < 0) {
			cout << -1 << "\n";
			continue;
		}
		if(suf[l] - suf[r+1] != 0) {
			cout << -1 << "\n";
			continue;
		}
		cout << res.mxval << "\n";
	}
	
	return 0;
}
```

---

## 作者：FreedomKing (赞：1)

### 思路

两个序列显然是不好操作的，记 $c_i=b_i-a_i$，然后考虑观察题目性质，发现在记作 $c$ 之后序列操作变成了选择若干个元素进行奇数位 $-1$、偶数位 $+1$，题目要求的 $a_i=b_i$ 也转化为了使 $c_i=0$。由于选择的元素个数必须为偶数，显然 $c$ 的元素和是不变的，故对于询问 $l,r$，若 $\sum_{i=l}^rc_i\neq 0$ 则无论如何也无法使 $c_i=0$，输出 $-1$。

然后考虑维护一个 $c$ 的前缀和，发现每次序列操作可以使 $c_i$ 区间减一，故答案输出 $\max_{i=l}^r\{\sum_{j=l}^ic_j\}$。但是可以发现无解情况依然存在漏判，考虑当存在 $\min_{i=l}^r\{\sum_{j=l}^ic_j\}<0$ 时，无法将其归零，故无解输出 $-1$。

### AC Code

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=1e5+5,mod=1e9+7;
namespace FreedomKing_qwq{
#define lowbit(_) (_&-_) 
	struct Tree{
		int tree[N];
		inline void add(int x,int k){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=k;
			return;
		}
		inline int query(int x){
			int ans=0;
			for(int i=x;i>1;i-=lowbit(i)) ans+=tree[i];
			return ans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[y]=x;
			return;
		}
	};
	//#define lc (p<<1)
	//#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
	//	inline int max(int x,int y){return (x>y?x:y);}
	//	inline int min(int x,int y){return (x<y?x:y);}
	inline int abss(int x){return (x>=0?x:-x);}
}
int a[N],b[N],maxn[N][22],minn[N][22];
signed main(){
	int n=qr,T=qr;
	for(int i=1;i<=n;i++) maxn[i][0]=qr;
	for(int i=1;i<=n;i++){
		maxn[i][0]=qr-maxn[i][0]+maxn[i-1][0];
		minn[i][0]=maxn[i][0];
	}
	for(int j=1;j<=21;j++)
		for(int i=1;i+(1<<j)-1<=n;i++) maxn[i][j]=max(maxn[i][j-1],maxn[i+(1<<(j-1))][j-1]);
	for(int j=1;j<=21;j++)
		for(int i=1;i+(1<<j)-1<=n;i++) minn[i][j]=min(minn[i][j-1],minn[i+(1<<(j-1))][j-1]);
	while(T--){
		int l=qr,r=qr,k=log2(r-l+1);
		if(maxn[r][0]-maxn[l-1][0]){
			qwe(-1);
			continue;
		}
		int maxans=max(maxn[l][k],maxn[r-(1<<k)+1][k])-maxn[l-1][0];
		int minans=min(minn[l][k],minn[r-(1<<k)+1][k])-minn[l-1][0];
		if(minans<0){
			qwe(-1);
			continue;
		}
		qwe(maxans);
	}
	return 0;
}
```

---

## 作者：ziyistudy (赞：1)

## 前言

>梦熊神机居然放 $n^2=10^{10}$ 的做法过了？！ 
>
>~~绝对不是脚造数据。~~

## 正言

这是一篇线段树做法。

容易发现，我们并不关心 $a,b$ 中的数值具体是多少，而关心的是它们的差值。所以在 $a_i,b_j$ 上加 $1$ 等同于在 $a_i$ 上加 $1$，$a_j$ 上减 $1$。

我们记 $c_i=a_i-b_i$，发现目标转换为通过一系列交替的 $+1$ 和 $-1$ 操作将 $c_i$ 变成全 $0$。

下记区间操作为 $L,R$，$L\leq l\leq r\leq R$。

显然看的出来和不变，所以若有 ${\textstyle \sum \limits_{i=L}^{R} c_i} \ne 0$，必然是不行的。 

其次，因为我们先进行了 $+1$ 操作，所以对任意 ${\textstyle \sum \limits_{i=L}^{r}c_i}$ 经过操作之后一定是不会减少的。原因：若想让这个东西减少，则必须在 $r$ 左有一个 $-1$ 操作，但这个 $-1$ 操作的左边又必定还有一个 $+1$ 操作，便抵消掉了。所以，如果有 ${\textstyle \sum \limits_{i=L}^{r}c_i} > 0$，则必定无解，因为我们永远无法将这个东西变为 $0$。

接下来考虑操作总次数。注意到，我们每次是先进行的 $+1$ 操作，所以对于区间 ${\textstyle \sum \limits_{i=L}^{r} c_i}<0$，我们最多一次将这个区间总和加 $1$。所以，操作次数为前缀区间的最小值的绝对值。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
//#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll MOD=998244353;
// head
int ls(int x) {return x<<1;}
int rs(int x) {return x<<1|1;}
const int N=1e5+5,INF=1e18;
int a[N],b[N];
int all[N];
struct node{int mxpre,mnpre;};
struct Seg
{
    node ans[N<<2];
    void push_up(int dir)
    {
        ans[dir].mxpre=max(ans[ls(dir)].mxpre,ans[rs(dir)].mxpre);
        ans[dir].mnpre=min(ans[ls(dir)].mnpre,ans[rs(dir)].mnpre);
    }
    void build_tree(int dir,int l,int r)
    {
        if(l==r) {ans[dir].mxpre=ans[dir].mnpre=all[l];return ;}
        int mid=(l+r)>>1;
        build_tree(ls(dir),l,mid);
        build_tree(rs(dir),mid+1,r);
        push_up(dir);
    }
    node query(int qx,int qy,int x,int y,int dir)
    {
        node l={-INF,INF};
        if(qx<=x&&y<=qy) return ans[dir];
        int mid=(x+y)>>1;
        if(qx<=mid) l=query(qx,qy,x,mid,ls(dir));
        if(qy>mid) {
            node r=query(qx,qy,mid+1,y,rs(dir));
            l.mxpre=max(l.mxpre,r.mxpre);
            l.mnpre=min(l.mnpre,r.mnpre);
        }
        return l;
    }
}tree;
signed main() 
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n,q;cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=n;i++) all[i]=all[i-1]+a[i]-b[i];
    tree.build_tree(1,1,n);
    while(q--)
    {
        int l,r;cin>>l>>r;
        if(all[r]-all[l-1]!=0) {cout<<-1<<endl;continue;}
        node tmp=tree.query(l,r,1,n,1);
        if(tmp.mxpre>all[l-1]) {cout<<-1<<endl;continue;}
        cout<<abs(tmp.mnpre-all[l-1])<<endl;
    }
}
```

## 后言

这道题还可以使用 ST 表求解，但我~~不会写~~懒得写。

---

## 作者：Drest (赞：1)

# [CF1556E] Equilibrium 题解

## 传送门
[luogu](https://www.luogu.com.cn/problem/CF1556E)
|
[codeforces](http://codeforces.com/problemset/problem/1556/E)

## 解题思路

首先我们可以发现，答案仅与两个序列的差值有关，也就是与 $c_i = a_i - b_i$ 有关。

那么题目就可以转换为：

- 选择一个长度为 $k$（$k$ 是偶数）的正整数序列 $pos$，满足 $l \le p_1 < p_2 < \dots < p_{k-1} < p_k \le r$，将 $c_{pos_1}, c_{pos_3},\dots,c_{pos_k-1}$ 加一，将 $c_{pos_2}, c_{pos_4},\dots,c_{pos_k}$ 减一。

- 给定 $l,r$，问最小进行多少次操作，能使得 $c_l = c_{l+1} = c_{l+2} = \dots = c_r  = 0$ 或报告无解。

对每次操作进行分析，我们会发现，操作完后，序列 $c$ 的和永远不发生改变，即 $\sum c_i$ 是定值。也就是说，如果给定的 $l, r$ 不能满足 $\sum_{i=l}^r c_i = 0$，就应该直接报告无解。

继续对操作分析，我们发现每次操作后， $j\in{[l,r]},\sum_{i=l}^j c_i$ 是不降的，因为**加操作的下标永远在减操作的下表前面**，且**加减操作轮流出现**。那么，如果有任意 $j\in{[l,r]},\sum_{i=l}^j c_i > 0$，也是无解的。

对于有解情况，考虑 $j\in{[l,r]},\sum_{i=l}^j c_i$ 的最小值 $m$，如果想让 $c$ 序列的 $[l,r]$ 区间全部变为 $0$，那么就要至少操作 $m$ 次，因为**每次操作只能最多将 $m$ 增加 $1$**。

所以有解时的答案就是 $m$，用 st 表预处理即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int N = 1e5 + 10;
namespace st {
    struct s_table {
        int st[N][22], lg[N];

        std::function<int(int, int)> func;

        s_table(int (*func)(int, int)) {
            this->func = func;
        }

        void init(const int a[], int n) {
            lg[0] = -1;
            for (int i = 1; i < N; i++)
                lg[i] = lg[i >> 1] + 1;

            for (int i = 1; i <= n; i++)
                st[i][0] = a[i];

            int p = (int) log2(n);
            for (int i = 1; i <= p; i++)
                for (int j = 1; j + (1 << i) <= n + 1; j++)
                    st[j][i] = func(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
        }

        int query(int l, int r) {
            int k = (int) (lg[r - l + 1]);
            return func(st[l][k], st[r - (1 << k) + 1][k]);
        }
    };
}
using namespace std;
int n, q, a[N], b[N], c[N];
int qz[N];
int mx(int x, int y) {
    return x > y ? x : y;
}
int mn(int x, int y) {
    return x < y ? x : y;
}
st::s_table mxt = st::s_table(mx);
st::s_table mnt = st::s_table(mn);
signed main() {

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        c[i] = a[i] - b[i];
        qz[i] = qz[i - 1] + c[i];
    }

    mxt.init(qz, n);
    mnt.init(qz, n);

    while (q--) {
        int l, r;
        cin >> l >> r;
        if (qz[r] - qz[l - 1] != 0 || mxt.query(l, r) > qz[l - 1]) {
            cout << -1 << endl;
            continue;
        }
        cout << qz[l - 1] - mnt.query(l, r) << endl;

    }
    return 0;
}
```

---

## 作者：Targanzqq (赞：1)

### 一道神奇的题目
我们转化一下题目的要求：我们的目的是逐步减小 $a_i$ 和 $b_i$ 的差以至于它们相等，因此我们让 $a$ 增加，也就相当于让 $b$ 减少。因此原来的题目操作可以转化为选一些位置，让 $b$ 中已选的编号为奇数的位置 $-1$，偶数的位置 $+1$。因此我们可以知道，**$b$ 的总和是不变的**。这是第一个性质。

我们再考虑一点。假设 $c_i=a_i-b_i$，由于 $b_i$ 的总和不变，因此 $c_i$ 的总和也不变。因此如果 $c$ 的**区间和不为 $0$**，且这段区间内**有从左端点开始的连续段的和大于 $0$**（或者说这一段出现 $b$ 的和比 $a$ 小），那我们无法让 $c$ 成为 $0$。这两种情况下无解。这是第二个性质。

还有一点，就是说如果我们每次选一些位于某一段中的位置，那么有可能这一段的某个前缀中有奇数个或偶数个，对于前者，这一段的和会加上 $1$，后者则不变。因此我们得到 **$c$ 的可选区间前缀的和不减**。

这样我们把满足条件的部分都筛下来了。设 $c$ 的前缀和为 $s$，所以现在就变成了如何让最大的那个 $|s|$，也就是最小的 $s$（因为 $s$ 一定小于等于 $0$）变成 $0$。因为总和为 $0$，我们可以找到方案，使得一个小于 $0$ 的前缀和 $+1$，且一次操作最多只能加 $1$。（这也是总和不为 $0$ 就没有方案的原因）。

因此我们只要找到那个最小的可选区间的 $s$ 即可。我们可以维护所有前缀和区间最小值的 $st$ 表，算完答案之后再减去 $s_{l-1}$。我们维护是否无解需要再使用一个前缀和区间最大值的 $st$ 表。时间复杂度 $O(n\log n)$。

源代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,q,a[200005],b[200005],c[200005],f1[200005][20],f2[200005][20];

int query1(int l,int r){
	int k=log2(r-l+1);
	return max(f1[l][k],f1[r-(1<<k)+1][k]);
}

int query2(int l,int r){
	int k=log2(r-l+1);
	return min(f2[l][k],f2[r-(1<<k)+1][k]);
}

signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)c[i]=a[i]-b[i];
	for(int i=1;i<=n;i++){
		c[i]+=c[i-1];
		f1[i][0]=c[i];
		f2[i][0]=c[i];
	}
	for(int i=1;i<=20;i++){
		for(int j=1;j<=n;j++){
			if(j+(1<<i)-1<=n){
				f1[j][i]=max(f1[j][i-1],f1[j+(1<<(i-1))][i-1]);
				f2[j][i]=min(f2[j][i-1],f2[j+(1<<(i-1))][i-1]);
			}
		}
	}
	for(int i=1;i<=q;i++){
	    int l,r;cin>>l>>r;
	    if(query1(l,r)>c[l-1]||c[r]!=c[l-1]){
	    	cout<<-1<<"\n";continue; 
		}
		cout<<abs(query2(l,r)-c[l-1])<<"\n";
	}
}

```

---

## 作者：kradcigam (赞：1)

题目意思：

> 有 $n$ 组数 $a_1,a_2,\cdots,a_n$ 和 $b_1,b_2,\cdots,b_n$，$q$ 次独立的询问，每次询问区间 $l\sim r$，求多少次“平衡操作”使得每个满足 $l\le i\le r$ 的 $i$ 都有 $a_i=b_i$，无法完成输出 `-1`。
>
> 平衡操作指的是给出一个长度为**偶数**位置序列 $l\le pos_1<pos_2<\cdots<pos_k\le r$，进行操作：$a_{pos_1},a_{pos_3},a_{pos_5},\cdots$ 加上 1，$b_{pos_2}$ 加上 1。

我们发现如果 $a_i$ 减去 1，那么就相当于是 $a_i-b_i$ 减去 $1$。我们发现如果 $b_i$ 减去 1，那么就相当于是 $a_i-b_i$ 加上 $1$，最终要让每个满足 $l\le i\le r$ 的 $i$ 都有 $a_i-b_i=0$。

我们去观察它的操作序列，实际上这些元素是分成了若干个组，比如 $po s_1$ 和 $pos_2$。

我们把 $a_i-b_i$ 这个东西前缀和一下，$s_i$ 表示 $(a_1-b_1)+(a_2-b_2)+\cdots+(a_i-b_i)$，就会发现每组操作 $pos_1,pos_2$，相当于是在前缀和上区间加 $s_{pos_1}\sim s_{pos_2-1}$ 区间加 1。

判 `-1` 就是 2 种情况：

1. $s_r\ne s_{l-1}$ 
2. $\max\limits_{i=l}^{r}\{s_i\}>s_{l-1}$ （因为是区间加 1）

答案是 $s_{l-1}-\min\limits_{i=l}^{r}\{s_i\}$，都不是很困难。

区间查询 $\max$ 和 $\min$，用 ST 表实现即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define log(a) cerr<<"[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<endl
using namespace std;
typedef long long LL;
template<typename T>void chkmax(T&x,T y){x=max(x,y);}
template<typename T>void chkmin(T&x,T y){x=min(x,y);}
template<typename T>inline void read(T &FF){
    T RR=1;FF=0;char CH=getchar();
    for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
    for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
    FF*=RR;
}
const int N=1e5+10,M=25;
int a[N],f[N],lg[N],mxn[M][N],mnn[M][N];
pair<int,int>query(int l,int r){
	int len=lg[r-l+1];
	return make_pair(max(mxn[len][l],mxn[len][r-(1<<len)+1]),min(mnn[len][l],mnn[len][r-(1<<len)+1]));
}
signed main(){
	int n,q;
	read(n);read(q);
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1,x;i<=n;i++){
		read(x);
		a[i]-=x;
		f[i]=f[i-1]+a[i];
	}
	// cout<<"->f";for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<endl;
	for(int i=0;i<=20;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			if(i==0)mxn[i][j]=mnn[i][j]=f[j];
			else{
				mxn[i][j]=max(mxn[i-1][j],mxn[i-1][j+(1<<(i-1))]);
				mnn[i][j]=min(mnn[i-1][j],mnn[i-1][j+(1<<(i-1))]);
			}
	// log(mnn[2][2]);
	while(q--){
		int l,r;
		read(l);read(r);
		pair<int,int>a=query(l,r);
		// log(a.first);log(a.second);
		if(f[r]!=f[l-1]||a.first>f[l-1])puts("-1");
		else cout<<f[l-1]-a.second<<endl;
	}
	return 0;
}
```



---

## 作者：Dtw_ (赞：0)

# 0.前言
在题单里的一众 DP 中，一道不像 DP 的题脱颖而出。

# 1.思路

分几个模块拆分此题，应该会更清晰。

## 模块 1
看到希望序列里的数都相等，容易想到将两个序列作差，然后修改这个差序列。
## 模块 2
在差序列上操作时，发现一定是 $+1,-1,+1,-1$ 这样的操作。所以记 $c_i = b_i-a_i$，如果 $\sum c_i=0$ 那就是有解，否则无解。而 $+1,-1$ 这个东西就很括号序列，把 $+1$ 看做左括号，$-1$ 看做右括号。
## 模块 3
考虑对于一个这样的括号序列 `((())())`，他需要修改几次呢？

要修改 $3$ 次，为什么呢？因为每次我们只能 $-1$，所以我们将括号分层，每次同层 $-1$，所以如果记层数为 $t_i$ 那么要减 $\max(t_i)$ 次，所以对于区间 $[l,r]$ 来说，答案就是最多的左括号重叠数。

## 模块 4

然后对于前面的情况怎么维护呢？发现是区间信息，直接线段树。

注意静态区间，所以用 ST 表就行。

但是还要注意无解情况，就是区间最小值要大于 $-1$，那对于前缀和上就是 $c_{l-1}< min(c_i)$。然后就行了。
# Code

```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

const int N = 1e5 + 10;

int n, q, a[N], b[N], c[N], f[N][21], g[N][21];

int query(int l, int r)
{
	int k = log2(r - l + 1);
	return max(f[l][k], f[r - (1 << k) + 1][k]);
}

int query2(int l, int r)
{
	int k = log2(r - l + 1);
	return min(g[l][k], g[r - (1 << k) + 1][k]);
}

signed main()
{
    cin >> n >> q;
    for(int i=1; i<=n; i++) cin >> a[i];
    for(int i=1; i<=n; i++) cin >> b[i];
    for(int i=1; i<=n; i++) c[i] = b[i] - a[i];
    for(int i=1; i<=n; i++)
    {
    	c[i] += c[i - 1];
    	f[i][0] = c[i];
    	g[i][0] = c[i];
	}
	for(int j=1; j<=20; j++)
	{
		for(int i=1; i<=n; i++)
		{
			if(i + (1 << j) - 1 <= n)
			{
				f[i][j] = max(f[i][j-1], f[i + (1 << (j - 1))][j-1]);
				g[i][j] = min(g[i][j-1], g[i + (1 << (j - 1))][j-1]);
			}
		}
	}
	while(q--)
	{
		int l, r;
		cin >> l >> r;
		if(query2(l, r) < c[l - 1] || c[r] != c[l - 1]) cout << "-1\n";
		else cout << abs(query(l, r) - c[l - 1]) << endl;
	}
	return 0;
}




```

---

## 作者：hellolin (赞：0)

$b$ 序列加一可以看作 $a$ 序列减一，即令 $\Delta_i = b_i-a_i$，我们需要做到 $\forall i\in [l, r],\ \Delta_i=0$。

注意到 $\sum \Delta_i$ 不变，即若 $\sum \Delta_i \neq 0$ 必定无解。

注意到减一操作前必须有一个加一操作，如果我们将 $\Delta$ 中同号的子段合并（忽略 $0$），发现某个负数大于其前的前缀和（也即，某些位置的前缀和为负），那么必定无解。

E.g. $\Delta=\{2,-5,4,-1\}$，此时 $-5$ 无法变成 $0$。

不难证明以上两个条件的充分性、必要性。

有解情况下的答案即为最大的前缀和。

实现方面，我们先算出 $\Delta$，对其做前缀和，线段树维护前缀和的 $\min$ 与 $\max$，再按照以上方法判定即可。

``` cpp
static constexpr int N = 1e5 + 5;
int n, q;
i64 a[N], b[N], d[N];

// 省略线段树 QAQ

void main() {
  io.read(n, q);
  for (int i = 1; i <= n; ++i)
    io.read(a[i]);
  for (int i = 1; i <= n; ++i)
    io.read(b[i]), d[i] = b[i] - a[i] + d[i - 1];
  build();
  for (int i = 1, l, r; i <= q; ++i) {
    io.read(l, r);
    const auto [Min, Max] = query(l, r);
    if (d[r] - d[l - 1] || Min - d[l - 1] < 0)
      io.writeln(-1);
    else
      io.writeln(Max - d[l - 1]);
  }
}
```

---

## 作者：Eric_jx (赞：0)

## 解题思路

考虑将在两个序列上的操作变为在一个序列上的操作，即将 $b$ 变为 $a$，位置 $pos_1$，$pos_3$，$pos_5$⋯ 处的数组 $a$ 的项增加 $1$，就是数组 $b$ 相应项 减 $1$。

为了方便，我们可以让 $c_i=b_i-a_i$，数组 $c$ 记录 $a$ 与 $b$ 的差值，每次操作，我们都是在弥补这个差值。

对于一个区间 $[l,r]$，如果这个区间的 $c$ 数组的和（即差值和）不等于 $0$，说明无法通过操作实现，就输出 $-1$ 报告无解。

我们的每次操作都可以看作是将数组 $c$ 的值进行转移，比如 $a_i+1$，$b_j+1$，就可以看成 $c_i-1$，$c_j+1$，假设现在我们已经求出了 $c_i$ 的前缀和 $sum$，对于区间 $[l,r]$，$sum_i$ 的值都不能小于 $sum_{l-1}$，因为每次操作都相当于是对 $c_i$ 的转移，如果存在 $sum_i<sum_{l-1}$，说明区间 $[l,i]$ 这段和为负值，而我们的操作是先减后加，不可能出现负值。

那么如何计算操作次数？ 因为我们每次操作，都是减加减加，所有总共操作次数就是最长的加序列，也就是 $sum$ 的最大值。可以把正数看成左括号，负数看成是右括号，$[l,r]$ 是合法的括号序列，则可以操作，最少次数是最大的括号嵌套数。

我们取 $[l,r]$ 中 $sum_i$ 的最大值，$\max(sum_i)-sum_{l-1}$ 就是操作次数，利用 $ST$ 表求解。

## AC代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
long long a[100005],logg[100005];
long long s[100005],fm[35][100005],fmi[35][100005];
long long suan_max(long long l,long long r){
	long long len=logg[r-l+1];
	return max(fm[len][l],fm[len][r-(1<<len)+1]);
}
long long suan_min(long long l,long long r){
	long long len=logg[r-l+1];
	return min(fmi[len][l],fmi[len][r-(1<<len)+1]);
}
int main(){
	long long n,q;
	scanf("%lld%lld",&n,&q); 
	for(long long i=2;i<=n;i++){
		logg[i]=logg[i>>1]+1;
	}
	for(long long i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(long long i=1;i<=n;i++){
		long long x;
		scanf("%lld",&x);
		a[i]=x-a[i];
		s[i]=s[i-1]+a[i];
	}
	for(long long i=0;i<=20;i++){
		for(long long j=1;j+(1<<i)-1<=n;j++){
			if(i==0){
				fm[i][j]=fmi[i][j]=s[j];
			}
			else{
				fm[i][j]=max(fm[i-1][j],fm[i-1][j+(1<<(i-1))]);
				fmi[i][j]=min(fmi[i-1][j],fmi[i-1][j+(1<<(i-1))]);
			}
		}
	}
	while(q--){
		long long l,r;
		scanf("%lld%lld",&l,&r);
		if(s[r]!=s[l-1]||suan_min(l,r)<s[l-1]){
			cout<<"-1\n";
			continue;
		} 
		cout<<suan_max(l,r)-s[l-1]<<"\n";
	}
	return 0;
}

```

---

