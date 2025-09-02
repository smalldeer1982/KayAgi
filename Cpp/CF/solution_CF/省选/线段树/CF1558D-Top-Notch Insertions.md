# Top-Notch Insertions

## 题目描述

Consider the insertion sort algorithm used to sort an integer sequence $ [a_1, a_2, \ldots, a_n] $ of length $ n $ in non-decreasing order.

For each $ i $ in order from $ 2 $ to $ n $ , do the following. If $ a_i \ge a_{i-1} $ , do nothing and move on to the next value of $ i $ . Otherwise, find the smallest $ j $ such that $ a_i < a_j $ , shift the elements on positions from $ j $ to $ i-1 $ by one position to the right, and write down the initial value of $ a_i $ to position $ j $ . In this case we'll say that we performed an insertion of an element from position $ i $ to position $ j $ .

It can be noticed that after processing any $ i $ , the prefix of the sequence $ [a_1, a_2, \ldots, a_i] $ is sorted in non-decreasing order, therefore, the algorithm indeed sorts any sequence.

For example, sorting $ [4, 5, 3, 1, 3] $ proceeds as follows:

- $ i = 2 $ : $ a_2 \ge a_1 $ , do nothing;
- $ i = 3 $ : $ j = 1 $ , insert from position $ 3 $ to position $ 1 $ : $ [3, 4, 5, 1, 3] $ ;
- $ i = 4 $ : $ j = 1 $ , insert from position $ 4 $ to position $ 1 $ : $ [1, 3, 4, 5, 3] $ ;
- $ i = 5 $ : $ j = 3 $ , insert from position $ 5 $ to position $ 3 $ : $ [1, 3, 3, 4, 5] $ .

You are given an integer $ n $ and a list of $ m $ integer pairs $ (x_i, y_i) $ . We are interested in sequences such that if you sort them using the above algorithm, exactly $ m $ insertions will be performed: first from position $ x_1 $ to position $ y_1 $ , then from position $ x_2 $ to position $ y_2 $ , ..., finally, from position $ x_m $ to position $ y_m $ .

How many sequences of length $ n $ consisting of (not necessarily distinct) integers between $ 1 $ and $ n $ , inclusive, satisfy the above condition? Print this number modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the algorithm performs no insertions — therefore, the initial sequence is already sorted in non-decreasing order. There are $ 10 $ such sequences: $ [1, 1, 1], [1, 1, 2], [1, 1, 3], [1, 2, 2], [1, 2, 3], [1, 3, 3], [2, 2, 2], [2, 2, 3], [2, 3, 3], [3, 3, 3] $ .

In the second test case, the only sequence satisfying the conditions is $ [3, 2, 1] $ .

In the third test case, $ [4, 5, 3, 1, 3] $ is one of the sought sequences.

## 样例 #1

### 输入

```
3
3 0
3 2
2 1
3 1
5 3
3 1
4 1
5 3```

### 输出

```
10
1
21```

# 题解

## 作者：syksykCCC (赞：13)

当 $m$ 次插入确定了以后，本质上是一个从原序列到新序列的置换，例如 $n = 3$，只进行了 $(2, 1)$ 这次插入，那么相当于是从原先的 $[a_1, a_2, a_3]$ 变成了 $[a_2, a_1, a_3]$。

那么，根据**最终序列是不下降**的，可以得到一个 $a_2 \le a_1 \le a_3$ 的不等式。

这个条件显然不是充要的，原因在于，当发生插入 $(x, y)$ 时，确定了一组明确的**严格小于**的关系（被插入的数 $<$ 原来该位置上的数，注意**不是** $a_x < a_y$），而非简单的不下降。

在上面的例子中，发生 $(2, 1)$ 这次插入表示 $a_2 < a_1$。所以真正严格的限制应当是 $a_2 < a_1 \le a_3$。

先不妨不关心最终的限制是什么，假设我们知道了最终限制中有 $c$ 个「小于号」和 $n - 1 - c$ 个「小于等于号」，根据隔板法，可以知道方案数应当是 $\binom{2n - 1 - c}{n}$。

问题转化为了求出 $c$ 的值，即小于号的个数。

根据上面的过程，可以发现，一个数前面**是小于号**而不是小于等于号的要求是 **「有另一个数直接插入到了它的前面」**。

考虑逆序这些插入，维护一个集合 $S$。初始时 $S$ 包含了 $1,2, \cdots, n$ 的所有的数。

每次遇到一个 $(x_i, y_i)$ 时，查询 $S$ 中第 $y_i$ 小的数 $p$ 和第 $y_i + 1$ 小的数 $q$，即将 $p$ 插入到了 $q$ 之前。那么从 $S$ 中删除 $p$，令 $tag_q \gets 1$，表示有个数插入到了 $q$ 之前。

最终 $c$ 就等于 $tag= 1 $ 的位置的个数。

注意实现应当是 $O(m \log n)$，不要搞成了 $O(n \log n)$。

代码用线段树二分实现的。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
const int N = 2e5 + 5, MOD = 998244353;
int n, m, x[N], y[N], roll[N], val[N << 2], fac[N << 1], ifac[N << 1];
std::set<int> pos;
int qpow(int a, int p) {
	int res = 1;
	while(p) {
		if(p & 1) res = (ll)res * a % MOD;
		a = (ll)a * a % MOD; p >>= 1;
	}
	return res;
}
void init(int l, int r, int rt) {
	val[rt] = r - l + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	init(l, mid, rt << 1); init(mid + 1, r, rt << 1 | 1);
}
int query(int l, int r, int rt, int k) {
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(val[rt << 1] >= k) return query(l, mid, rt << 1, k);
	else return query(mid + 1, r, rt << 1 | 1, k - val[rt << 1]);
}
void modify(int l, int r, int rt, int p, int v) {
	val[rt] += v;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) modify(l, mid, rt << 1, p, v);
	else modify(mid + 1, r, rt << 1 | 1, p, v);
}
int C(int a, int b) {
	if(a < 0 || b < 0 || a < b) return 0;
	return (ll)fac[a] * ifac[b] % MOD * ifac[a - b] % MOD;
}
int main() {
	fac[0] = 1;
	for(int i = 1; i < N * 2; i++) fac[i] = (ll)fac[i - 1] * i % MOD;
	ifac[N * 2 - 1] = qpow(fac[N * 2 - 1], MOD - 2);
	for(int i = N * 2 - 1; i; i--) ifac[i - 1] = (ll)ifac[i] * i % MOD; 
	int test; scanf("%d", &test); init(1, N - 1, 1);
	while(test--) {
		scanf("%d %d", &n, &m); pos.clear();
		for(int i = 1; i <= m; i++) scanf("%d %d", &x[i], &y[i]);
		for(int i = m; i; i--) {
			int p = query(1, N - 1, 1, y[i]), q = query(1, N - 1, 1, y[i] + 1);
			modify(1, N - 1, 1, p, -1); 
			roll[i] = p; pos.insert(q); 
		}
		for(int i = 1; i <= m; i++) modify(1, N - 1, 1, roll[i], 1);
		int c = (int)pos.size();
		printf("%d\n", C(n * 2 - 1 - c, n));
	}
	return 0;
}
```



---

## 作者：Diana773 (赞：4)

由[官方题解](https://codeforces.com/blog/entry/94216)改编
# 题意简述
- 有一个正整数数列 $[a_1,a_2,\dots,a_n]$ ，数列中每一个数不大于 $n$，数列中数字有重复。

- 对数列按照以下规则进行排序，使之变成一个从小到大的数列。

- 令 $i$ 按顺序 $2$ 到 $n$：
     
     1. 若 $a_i>=a_{i-1}$ ，则不对数列进行操作。（非插入操作）
     2. 若 $a_i<a_{i-1}$ ，寻找数列中最小的 $j$ 满足 $a_i<a_j$，把 $a_i$ 取出，再插入数列当前的第 $j$ 个与 $j-1$ 位置中间。（插入操作）
    
- 按顺序给定插入操作中每一对 $i$、$j$，求有多少种数列满足排序操作的插入操作与给定的一致。

# 题目分析
- 给定所有的插入操作的参数，相当于给定了排序时的所有操作。排序后得到得数列与原数列是一一对应的。例如：给定 $(3,1)$、$(4,2)$、$(5,4)$ 原数列 $[a_1,a_2,a_3,a_4,a_5]$ 排序后必定是 $[a_3,a_4,a_1,a_5,a_2]$。同理用排序后的序列也可以反推出唯一确定的原序列。为了考虑问题简单，可以只统计经过排序后的数列有几种。

- 记排序后的数列为 $[b_1,b_2,b_3,b_4,b_5]$ 可以发现对全部的 $i$ 要满足 $ b_i\le b_{i+1}$，经过插入操作后部分 $i$ 要满足 $b_i< b_{i+1}$。

- 现在记数列 $b$ 中有 $c$ 个 $i$ 要满足 $b_i< b_{i+1}$。我们让所有 $b$ 中要满足 $ b_i\le b_{i+1}$ 的位置 $i$ 之后的 $[b_{i+1},b_{i+2},\dots,b_n]$ 都加上 $1$，即可保证 $b$ 中的数字各不相同，$b_n$ 上限是 $2n-1-c$。此时相当于从  $1$ 到 $2n-1-c$ 中的数字挑选 $n$ 个填入数列 $b$ ，可以看出此时 $b$ 有 $\dbinom{2n-1-c}{n}$ 种。

- 最后我们求出 $c$ 的大小即可。可以发现在插入操作时有一些数会严格小于同一个数（如样例 $3$ 和上面的例子），这样对 $c$ 的贡献只能算一次。我们要模拟整个排序过程对 $m$ 次的插入操作去重。我们考虑倒序操作，每次在序列中删除一个数，对于插入操作用权值线段树实现对第 $i$ 大的数的查找删除，再查找第 $i$ 大的数统计贡献（因为删除过了，两个第 $i$ 大不一样）。

- 题目对 $\sum n$ 无限制，直接模拟排序会超时。发现非插入操作最后对数字大小查找没有影响，可以直接忽略。线段树最开始建树时直接建为 $2\times 10^5$ 大小的，进行下一组数据运算时进行之前用插入操作（之前所有删除的逆操作）代替初始化。

# 参考代码
```
#include<iostream>
#include<cstdio> 
#include<set>

using namespace std;

const int mod=998244353;
const int N=2e5+1000;
const int NN=2e5+10;

int mul(int a,int b)
{
	return (long long)a*b%mod;
}

int qpow(int a,int b)
{
	int ans=1;
	for (; b>0; b=b>>1)
	{
		if ((b&1)==1)
		  ans=mul(ans,a);
		a=mul(a,a);
	} 
	return ans;
}

int fac[N<<1];
int nfac[N<<1];

void init() //预处理阶乘和阶乘的逆 
{
	fac[0]=1;
	for (int i=1; i<=400000; i++)
      fac[i]=mul(fac[i-1],i);	
    nfac[400000]=qpow(fac[400000],mod-2);
    for (int i=399999; i>=0; i--)
      nfac[i]=mul(nfac[i+1],i+1);
}

int cc(int a,int b) //从b中选a个的组合数 
{
	return mul(fac[b],mul(nfac[a],nfac[b-a]));
}

namespace seg
{
	#define ls pl<<1
	#define rs (pl<<1)|1
	int tree[N<<2];
	
	void build(int pl,int l,int r)
	{
		if (l==r)
		{
			tree[pl]=1;
			return;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		tree[pl]=tree[ls]+tree[rs];
	}
	
	void add(int pl,int l,int r,int g,int zz) //将位置为g的叶子节点权值改为zz 
	{
		if (l==r&&l==g)
		{
			tree[pl]=zz;
			return;
		}
		int mid=(l+r)>>1;
		if (g>mid) 
		  add(rs,mid+1,r,g,zz);
		else
		  add(ls,l,mid,g,zz);
		tree[pl]=tree[ls]+tree[rs];
	}
	
	int find(int pl,int l,int r,int g) //查找排名为g的位置 
	{
		if (l==r)
		  return l;
		int mid=(l+r)>>1;
		if (tree[ls]>=g)
		  return find(ls,l,mid,g);
		else
		  return find(rs,mid+1,r,g-tree[ls]);		
	}		
}

int t,n,m,c,pl,ff;
int x[N];
int y[N];

int main()
{
    std::ios::sync_with_stdio(false);
    init();
    cin>>t;    	
	seg::build(1,1,NN);
    for (int qqw=1; qqw<=t; qqw++)
    {
    	cin>>n>>m;
    	set<int> ans;
    	set<int> zzf;
    	for (int i=1; i<=m; i++)
    	  cin>>x[i]>>y[i];
    	c=0;
    	for (int i=m; i>=1; i--)   
    	{
    		pl=seg::find(1,1,NN,y[i]); 
    		seg::add(1,1,NN,pl,0);   
			zzf.insert(pl); 		
    		pl=seg::find(1,1,NN,y[i]); //统计c 用set去重		
			ans.insert(pl);      
		}
		
		for (int i:zzf)  //用删除的逆操作代替初始化操作 
		  seg::add(1,1,NN,i,1);
		c=ans.size();
    	//cout<<c<<endl;   	
    	cout<<cc(n,2*n-1-c)<<'\n';
	}	
	return 0;
}
```



---

## 作者：Demoe (赞：4)

[$\large\text{题目传送门}$](https://www.luogu.com.cn/problem/CF1558D)

## $\text{Description}$

- 给定一个操作序列，求满足该操作序列且值域为 $[1,n]$ 长度为 $n$ 的序列数。
- 操作为对于一个 $i\ge 2$，若 $\forall j\le i, a_j\le a_i$ 则不操作，否则找到 $pos=\min\{x|a_{x}>a_i\}$，将 $a_i$ 插入到 $a_{pos}$ 前。
- 操作满足 $i$ 递增，对 $998244353$ 取模。

## $\text{Solution}$

考虑原问题可以抽象成什么。

由于序列最终是单调不降的，且 $i$ 单调递增，那么每次操作到 $i$ 时，有前 $i-1$ 项为单调不降序列。

那么我们直接给相邻两项加上 $\le$ 标志。

考虑一次操作 $(i,j)$。

对于当前序列 $\{a_n\}$，其所代表的的就是把 $a_i$ 提到 $a_j$ 前，然后把 $a_j$ 前的符号改为 $<$。

然后考虑计算长度为 $n$ 的值域为 $[1,m]$ 的不降序列的个数，其中有 $c$ 个 $i$ 要求 $a_i<a_{i+1}$，另外 $n-1-c$ 个满足 $a_i\le a_{i+1}$。

考虑将 $a_i\le a_{i+1}$ 转化为 $a_i< a_{i+1}+1$，然后我们将值域转化为 $[1,m+n-1-c]$。

显然有 $\dbinom{m+n-1-c}{n}$ 个序列，考虑就是 $[1,m+n-1-c]$ 里面选 $n$ 个数，由于严格单调递增，所以不能选相同的，而且其还限定了每个组合对答案都只贡献 $1$。

~~注意这里 $m$ 代表的是值域，并不是题目中的操作次数。~~

那么我们想要知道的就是 $<$ 或者 $\le$ 的个数。

显然每次操作最多增加一个 $<$，而题目限定了操作次数，而没有限定序列总长，那么我们考虑记录 $<$ 的个数。

考虑对于一次操作 $(i,j)$ 要支持什么操作。

考虑用一个 DS 维护 $<$ 的下标。

若 $a_j$ 前为 $\le$，我们将它修改为 $<$，在 DS 中插入 $j$。

否则啥都不干。

然后由于插入了 $a_i$，我们将 DS 中所有不小于 $j$ 的数都加 $1$。

因此这个 DS 需要支持插入值查询值和基于值域的区间加。

可以用 FHQ Treap 解决。

时间复杂度 $O(m\log m)$。

~~我吹爆 FHQ Treap！！1~~

## $\text{Code}$

```cpp
const int N=5e5+5,mod=998244353;
int n,cnt,m,T,rt,fac[N],inv[N];
struct node{int l,r,rd,v,sz,tag;}t[N];

inline int pw(int x,int y){
	int sum=1;
	while(y){
		if(y&1) sum=1ll*sum*x%mod;
		x=1ll*x*x%mod;y>>=1;
	}
	return sum;
}

inline void init(int n){
	fac[0]=1;
	for(re i=1;i<=n;++i) fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=pw(fac[n],mod-2);
	for(re i=n-1;i>=0;--i) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}

inline int C(int x,int y){
	if(x<y||y<0)return 0;
	return 1ll*fac[x]*inv[x-y]%mod*inv[y]%mod;
}

inline int newnode(int val){
	++cnt;t[cnt].l=t[cnt].r=t[cnt].tag=0;t[cnt].v=val;t[cnt].sz=1;t[cnt].rd=rand();
	return cnt;
}

inline void pushup(int p){
	if(!p) return;
	t[p].sz=t[t[p].l].sz+t[t[p].r].sz+1;
}

inline void pushdown(int p){
	if(!p) return;
	if(t[p].tag){
		if(t[p].l) t[t[p].l].v+=t[p].tag,t[t[p].l].tag+=t[p].tag;
		if(t[p].r) t[t[p].r].v+=t[p].tag,t[t[p].r].tag+=t[p].tag;
		t[p].tag=0;
	}
}

inline void split(int p,int k,int &x,int &y){
	if(!p){x=y=0;return;}
	pushdown(p);
	if(k>=t[p].v) x=p,split(t[p].r,k,t[p].r,y);
	else y=p,split(t[p].l,k,x,t[p].l);
	pushup(p);
}

inline int merge(int x,int y){
	if(!x||!y) return x|y;
	if(t[x].rd<t[y].rd){
		pushdown(x);t[x].r=merge(t[x].r,y);pushup(x);
		return x;
	}
	else{
		pushdown(y);t[y].l=merge(x,t[y].l);pushup(y);
		return y;
	}
}

inline bool find(int x,int p){
	if(!p) return 0;
	if(t[p].v==x) return 1;
	pushdown(p);
	if(x<t[p].v) return find(x,t[p].l);
	else return find(x,t[p].r);
}

inline void solve(){
	rd(n);rd(m);rt=cnt=0;
	for(re i=1;i<=m;++i){
		int a,b,x,y;rd(a);rd(b);
		bool f=find(b,rt);
		split(rt,b-1,x,y);
		if(y) ++t[y].v,++t[y].tag;
		rt=merge(x,f?y:merge(newnode(b+1),y));
	}
	wr(C(n+n-cnt-1,n));puts("");
}

// ----------	---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	init(400000);srand(time(nullptr));
	rd(T);while(T--)solve();
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：gyh20 (赞：2)

根据条件，我们可以建出一个形如 $a_{p_1}< a_{p_2}\leq a_{p_3}\dots\leq a_{p_n}$，其中中间的符号既可能是 $<$ 也可能是 $\leq $。具体的构建可以看作插入 $i$ 时，$i$ 之前的数构成了如上的不等式，$i$ 加入时，插入到其对应的位置，将前一个符号改成 $\leq $，后一个符号改为 $<$，可以发现仍然是一个符合条件的不等式。

假设我们得到了一个不等式，考虑如何求解，按照从小到大的顺序放，设 $f_{i,x}$ 表示前 $i$ 个位置，最后一个位置放 $x$ 的方案数，可以 DP。

发现我们的操作只有前缀和和平移一位，平移次数可以单独拿出来算，于是只有前缀和操作，容易发现就是一列组合数的前缀。

组合数列求和 $\displaystyle\sum\limits_{i=n}^m\dbinom i n=\dbinom {m+1}{n+1}$。

于是关键在于求 $<$ 的个数。

根据定义我们可以模拟，每一次会删掉一个原来的符号，加入一个 $\leq $ 和 $<$，可以直接维护出符号，由于有很多类似排名的操作，可以用平衡树维护（听说也可以倒过来用树状数组）。

时间复杂度 $O(m\log m)$。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=998244353;
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
inline void Add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
int n,m,fac[400003],inv[400003],siz[400003],val[400003],tg[400003],tr[400003][2],num[400003],root,fa[400003],w,cnt,TG[400003];
inline int C(re int x,re int y){return 1ll*fac[x]*inv[y]%M*inv[x-y]%M;}
inline void pu(re int p){
	siz[p]=siz[tr[p][0]]+siz[tr[p][1]]+num[p];
}
inline void pd(re int x){
	if(!x)return;
	val[x]+=tg[x];
	if(tr[x][0])tg[tr[x][0]]+=tg[x];
	if(tr[x][1])tg[tr[x][1]]+=tg[x];
	tg[x]=0;
}
inline void Pd(re int p){
	if(p^root)Pd(fa[p]);
	pd(p);
}
inline void add(re int p,re int v){
	pd(p);
	if(val[p]==v)++num[p],++siz[w=p];
	else if(val[p]>v&&tr[p][0])add(tr[p][0],v);
	else if(val[p]<v&&tr[p][1])add(tr[p][1],v);
	else{
		if(val[p]>v)tr[p][0]=++cnt;
		if(val[p]<v)tr[p][1]=++cnt;
		siz[cnt]=1,val[cnt]=v,num[cnt]=1,fa[w=cnt]=p;
	}
	pu(p);
}
inline void rotate(re int p,re int &f){
	int x=fa[p],y=fa[x];
	int s=(p!=tr[x][0]),t=(s^1);
	if(x^f)tr[y][(tr[y][0]!=x)]=p;
	else f=p;
	fa[fa[x]=p]=y;
	fa[tr[x][s]=tr[p][t]]=x;
	pu(tr[p][t]=x),pu(p);
}
inline void splay(re int p,re int &rt){
	Pd(p);
	while(p^rt){
		int x=fa[p],y=fa[x];
		if(x^rt)if((tr[x][0]==p)^(tr[y][0]==x))rotate(p,rt);
		else rotate(x,rt);
		rotate(p,rt);
	}
}
inline int find(re int p,re int x){
	if(!p)return 0;
	pd(p);
	if(val[p]<x)return find(tr[p][1],x);
	else{
		re int s=find(tr[p][0],x);
		if(!s)return p;
		else return s;
	}
}
int main(){
	n=400001;
	for(re int i=fac[0]=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%M;
	inv[n]=ksm(fac[n],M-2);
	for(re int i=n-1;~i;--i)inv[i]=1ll*inv[i+1]*(i+1)%M;
	int t=read();
	while(t--){
		n=read()-1,m=read();
		for(re int i=1;i<=cnt;++i)val[i]=tg[i]=tr[i][0]=tr[i][1]=num[i]=fa[i]=siz[i]=TG[i]=0;
		val[1]=1e9,val[tr[1][0]=2]=-1e9;
		siz[2]=fa[siz[1]=cnt=2]=root=num[1]=num[2]=1;
		re int k=m;
		for(re int i=1;i<=k;++i){
			re int x=read(),y=read();
			re int z=find(root,y);splay(z,root);
			re int tttt=find(root,y-1);
			if(val[tttt]==y-1&&TG[tttt]==0)--m,TG[tttt]=1;
			assert(z==root);
			val[z]+=1,tg[tr[z][1]]+=1;
			add(root,y),splay(w,root);
		}
		re int ans=C(2*n-m+1,n+1);
		printf("%d\n",ans);
	}
}
```


---

## 作者：C20203030 (赞：2)

__题目描述__


[点此看题](https://codeforces.com/contest/1558/problem/D)

考虑对一个长度为 $n$ 的数组 $a$ 进行插入排序，对于每个位置 $i$，如果 $a_{i-1}\leq a_i$ 那么不需要进行插入排序；否则找到第一个位置 $j$ 满足 $a_i<a_j$ 把 $a_i$ 插入到 $a_j$ 的前面，此时我们记录下插入信息 $(i,j)$

现给出 $m$ 个插入信息 $(x_i,y_i)$，问有多少个初始序列 $a$ 的插入排序恰好能对应给定的插入信息。

$n\leq 2\cdot 10^5,m\leq 2\cdot 10^5$，多组数据**只保证** $\sum m\leq 2\cdot 10^5$

__解法__

这道题是真的难，但是我一个学弟随便切掉了。

考虑初始序列 $a$ 是 $[a_1,a_2,a_3,a_4,a_5]$，如果给出的插入信息是 $(3,1),(4,1),(5,3)$，那么可以唯一确定排序后的结果是 $[a_4,a_3,a_5,a_1,a_2]$，所以初始序列唯一对应一个排序序列，并且由于插入过程确定，所以排序序列也唯一对应一个初始序列，**那么初始序列和排序序列构成一个双射**，问题可以转化成对排序序列的计数。

还是用上面的例子，由排序序列可以得到限制 $a_4\leq a_3\leq a_5\leq a_1\leq a_2$，我们考虑插入过程中还带来了什么限制：

- 如果 $a_{i-1}\leq a_i$，那么 $a_i$ 一定在 $a_{i-1}$ 后面，限制已经被排序序列考虑。
- 如果需要插入，那么 $a_i<a_j$ 会产生一个额外的限制，并且类似地其他的 $\leq$ 都已经被考虑过了。

设排序序列 $b$ 有 $c$ 个位置满足 $b_i<b_{i+1}$（注意并不完全是上面所谓的”限制“个数和，因为如果 $a_{i1},a_{i2}$ 同时插入到 $a_j$ 的后面那么最终只会产生一个小于号），显然这是一个组合数问题，先把 $b$ 差分，然后可以转化成有 $n+1$ 个未知数，其中有 $c+1$ 个未知数要求为正，要求和为 $n$，利用隔板法可知解的个数是 ${2n-1-c\choose n}$

现在的问题就是求 $c$ 嘛，考虑关键的地方是要看 $a_j$ 是否之前就被插入了，如果没有才让 $c\leftarrow c+1$，可以用平衡树维护，按题目给的插入信息来模拟，如果 $a_j$ 不在平衡树就相当于没有被插入过，然后打标记来维护插入后的整体平移即可，时间复杂度 $O(m\log n)$

__总结__

一开始我想根据题目的限制建拓扑图，但是这样会多出来很多无用的限制反而不好考虑，所以一定要去除**无效限制**，本题就是用考虑排序序列的方法去除了很多无效限制。

计数问题要找映射关系，如果有双射关系很可能有大用处。


```c++
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
const int M = 400005;
const int MOD = 998244353;
#define int long long
int read()
{
    int x=0,f=1;char c;
    while((c=getchar())<'0' || c>'9') {if(c=='-') f=-1;}
    while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
int T,n,m,fac[M],inv[M];
void init(int n)
{
	fac[0]=inv[0]=inv[1]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%MOD;
	for(int i=2;i<=n;i++) inv[i]=inv[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=2;i<=n;i++) inv[i]=inv[i-1]*inv[i]%MOD;
}
int C(int n,int m)
{
	if(n<m || m<0) return 0;
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
namespace treap
{
	int rt,cnt,ch[M][2],val[M],hp[M],tg[M];
	void clear()
	{
		for(int i=1;i<=cnt;i++)
			ch[i][0]=ch[i][1]=val[i]=tg[i]=0;
		rt=cnt=0;
	}
	struct node
	{
		int p[2];
		node() {p[0]=p[1]=0;}
	}emp;
	void add(int x,int v)
	{
		if(!x) return ;
		val[x]+=v;tg[x]+=v; 
	}
	void down(int x)
	{
		if(!tg[x]) return ;
		add(ch[x][0],tg[x]);
		add(ch[x][1],tg[x]);
		tg[x]=0;
	}
	node split(int x,int v)
	{
		if(!x) return emp;
		int d=val[x]<=v;down(x);
		node y=split(ch[x][d],v);
		ch[x][d]=y.p[d^1];
		y.p[d^1]=x;
		return y;
	}
	int merge(int x,int y)
	{
		if(!x || !y) return x+y;
		if(hp[x]<hp[y])
		{
			down(x);
			ch[x][1]=merge(ch[x][1],y);
			return x;
		}
		down(y);
		ch[y][0]=merge(x,ch[y][0]);
		return y;
	}
	int get(int x)//creat an element x
	{
		cnt++;val[cnt]=x;
		hp[cnt]=rand();
		return cnt;
	}
	int find(int x)//exist x? 
	{
		node t=split(rt,x-1),w=split(t.p[1],x);
		if(w.p[0]>0)//exist
		{
			add(w.p[0],1);add(w.p[1],1);
			rt=merge(t.p[0],merge(w.p[0],w.p[1]));
			return 0;
		}
		//if not,we need to insert
		w.p[0]=merge(get(x),w.p[1]);
		add(w.p[0],1);
		rt=merge(t.p[0],w.p[0]);
		return 1;
	}
}
signed main()
{
	T=read();init(4e5);
	while(T--)
	{
		n=read();m=read();
		treap::clear();int ans=0;
		for(int i=1;i<=m;i++)
		{
			int a=read(),b=read();
			if(treap::find(b)) ans++;
		}
		printf("%lld\n",C(2*n-ans-1,n));
	}
}
```



---

## 作者：yangchenxiao (赞：1)

首先可以先模拟一番来理解题意：   
比如 $a_1,a_2$，此时只有限制 $a_1\le a_2$。   
加入 $a_3$ 时加入有操作 $(3,1)$，那么放在第一位，并且此时要求 $a_3$ 是严格小于 $a_1$ 的，变成 $a_3<a_1\le a_2$。   
再来一个 $(4,2)$，变成了 $a_3\le a_4<a_1\le a_2$，可以发现此时 $<$ 的数量没有变，因为插入时 $3,4$ 的大小关系其实并不知道，而 $1$ 前面本来就是小于。   
因此，可以得出结论：小于号个数等于被在前面插入过数的位置的个数。    

接下来考虑对于 $n$ 个数，有 $m$ 个小于号连接时的方案数。   
可以理解为把前一个和后一个的差看成 $n-1$ 个非负未知数，和 $\le n-1$ 的方案数，其中有 $m$ 个还要求是正数。那么不妨把 $m$ 个 $1$ 预先先减去，总和 $\le n-m-1$，转化为 $n-1$ 个非负整数。由于总和是 $\le$ 也比较难受，那么不妨将第一个数和 $1$ 的差，最后一个数和 $n$ 的差也看作未知数，此时转化为恰好的情形。    
综上，$n+1$ 个非负整数和为 $n-m-1$ 的方案数，是经典的多重集组合数问题，答案为 $\binom{2n-m-1}{n}$。

在实现时，由于下标是动态变化的，需要知道当前情况第 $i$ 个位置上的数是什么，那么不妨倒序来做，每次删掉一个数即可。   
可以发现需要做的操作仅仅是朴素的第 $k$ 大，那么远没有必要手写平衡树，直接用 $pb\_ds$ 即可。    
~~（短到甚至可以一屏放下）~~


```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
#define pb push_back
using namespace std;using namespace __gnu_pbds;
const int maxn=4e5+5;const int stan=4e5;const int mod=998244353;
int t,frac[maxn],inv[maxn],inv1[maxn],ans,n,m,x[maxn],y[maxn];
vector<int>stax,stay;bool vis[maxn];
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>s;
int C(int n,int m){if(n<m)return 0;return frac[n]*inv[m]%mod*inv[n-m]%mod;}
void pre(int n){
	frac[0]=frac[1]=inv1[1]=inv[1]=inv[0]=1;
	for(int i=2;i<=n;i++)frac[i]=frac[i-1]*i%mod,inv1[i]=(mod-mod/i)*inv1[mod%i]%mod,inv[i]=inv[i-1]*inv1[i]%mod;
}
signed main(){
	pre(stan);cin>>t;for(int i=1;i<=stan;i++)s.insert(i);
	while(t--){
		cin>>n>>m;for(int i=1;i<=m;i++)cin>>x[i]>>y[i];
		for(int i=m;i>=1;i--){
			auto posx=s.find_by_order(y[i]-1),posy=s.find_by_order(y[i]);
			ans+=!vis[*posy],vis[*posy]=true,stay.pb(*posy);stax.pb(*posx),s.erase(posx);
		}
		printf("%d\n",C(n*2-ans-1,n));
		for(int i:stax)s.erase(i);for(int i:stay)vis[i]=false;
		stax.clear(),stay.clear(),ans=0;
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

容易发现，每次插入我们可以得到的信息为 $a_q\leq a_i<a_p$，其中 $a$ 为初始序列。

不难发现总方案数与最终的信息中 $<$ 个数有关。

每插入一个 $a_{x_i}$，$y_i$ 位置前面就会变成 $<$。

显然可以使用平衡树维护。当然也可以不使用平衡树。考虑从后往前插入每个数，$a_{x_i}$ 所对应的就是第 $y_i$ 个目前已经在序列里的数。用线段树找到位置，将这个数移出序列。再找到此时的第 $y_i$，将该位置前面改为 $<$，可以使用线段树上二分维护。

总复杂度 $O(m\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
int qp(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1; 
	}
	return ans;
}
int fac[1000005],inv[1000005];
void init(){
	fac[0]=1; for(int i=1;i<=1000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[1000000]=qp(fac[1000000]); for(int i=999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
struct sgt{
	int f[1000005],g[1000005];
	void changef(int i,int l,int r,int pos,int cg){
		if(l==r){
			f[i]=cg;
			return ;
		}
		if(pos<=mid) changef(i*2,l,mid,pos,cg);
		if(pos>mid) changef(i*2+1,mid+1,r,pos,cg);
		f[i]=f[i*2]+f[i*2+1];
	}
	void changeg(int i,int l,int r,int pos,int cg){
		if(l==r){
			g[i]=cg;
			return ;
		}
		if(pos<=mid) changeg(i*2,l,mid,pos,cg);
		if(pos>mid) changeg(i*2+1,mid+1,r,pos,cg);
		g[i]=g[i*2]+g[i*2+1];
	}
	int qkth(int i,int l,int r,int k){
		if(l==r) return l;
		if(f[i*2]>=k) return qkth(i*2,l,mid,k);
		return qkth(i*2+1,mid+1,r,k-f[i*2]);
	}
}tree;
signed main(){
	for(int i=1;i<=200000;i++) tree.changef(1,1,200000,i,1);
	init();
	int t; cin>>t;
	while(t--){
		int n,m; cin>>n>>m;
		int pos[m+1],x[m+1];
		for(int i=1;i<=m;i++) cin>>pos[i]>>x[i];
		vector<int> vcf,vcg;
		for(int i=m;i>=1;i--){
			int pos1=tree.qkth(1,1,200000,x[i]); vcf.push_back(pos1); tree.changef(1,1,200000,pos1,0);
			int pos2=tree.qkth(1,1,200000,x[i]); vcg.push_back(pos2); tree.changeg(1,1,200000,pos2,1);
		}
		int num=tree.g[1];
		cout<<C(n-1-num+n,n)<<"\n";
		for(auto v:vcf) tree.changef(1,1,200000,v,1);
		for(auto v:vcg) tree.changeg(1,1,200000,v,0);
	}
	return 0;
}
```

---

