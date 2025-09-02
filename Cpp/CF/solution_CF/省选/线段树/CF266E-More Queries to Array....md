# More Queries to Array...

## 题目描述

You've got an array, consisting of $ n $ integers: $ a_{1},a_{2},...,a_{n} $ . Your task is to quickly run the queries of two types:

1. Assign value $ x $ to all elements from $ l $ to $ r $ inclusive. After such query the values of the elements of array $ a_{l},a_{l+1},...,a_{r} $ become equal to $ x $ .
2. Calculate and print sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF266E/633cb60e7d18ebc2282c71be46423585a8ce8f27.png), where $ k $ doesn't exceed $ 5 $ . As the value of the sum can be rather large, you should print it modulo $ 1000000007 (10^{9}+7) $ .

## 样例 #1

### 输入

```
4 5
5 10 2 1
? 1 2 1
= 2 2 0
? 2 4 3
= 1 4 1
? 1 4 5
```

### 输出

```
25
43
1300
```

## 样例 #2

### 输入

```
3 1
1000000000 1000000000 1000000000
? 1 3 0
```

### 输出

```
999999986
```

# 题解

## 作者：zhangjiting (赞：5)

## 题意

区间覆盖，求 $ \displaystyle\ \sum_{i=l}^r a_i(i-l+1)^k$。

## 思路

二项式定理，把原式化为 $ \displaystyle\ \sum_{i=l}^r a_i \sum_{j=0}^k \binom{k}{j} i^j (1-l)^{k-j}$。

交换枚举顺序得 $ \displaystyle\ \sum_{j=0}^k \binom{k}{j} (1-l)^{k-j}\sum_{i=l}^r a_i \times i^j $。

对于 $j \in \{ x \in \mathbb{Z}| 0 \le x \le 5\}$ 维护 $ \displaystyle\ \sum_{i=l}^r a_i \times i^j$，很基础的线段树。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug(x) cout<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e5+5,mod=1e9+7;
int n,m;
int a[N];
int C[6][6];
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) (res*=a)%=mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}
#define ls p<<1
#define rs p<<1|1
struct node{
	int l,r;
	int sum[6],hlp[6];
	int tag;
}tree[N<<2];
void push_up(int p){
	for(int i=0;i<=5;i++){
		tree[p].hlp[i]=(tree[ls].hlp[i]+tree[rs].hlp[i])%mod;
		tree[p].sum[i]=(tree[ls].sum[i]+tree[rs].sum[i])%mod;
	}
}
void insert(int p,int k){
	for(int i=0;i<=5;i++) tree[p].sum[i]=(tree[p].hlp[i]*k)%mod;
	tree[p].tag=k;
}
void push_down(int p){
	if(tree[p].tag==-1) return;
	insert(ls,tree[p].tag);
	insert(rs,tree[p].tag);
	tree[p].tag=-1;
}
void build(int p,int l,int r){
	tree[p].l=l,tree[p].r=r,tree[p].tag=-1;
	if(l==r){
		for(int i=0;i<=5;i++){
			tree[p].hlp[i]=qpow(l,i);
			tree[p].sum[i]=(tree[p].hlp[i]*a[l])%mod;
		}
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(p);
}
void cover(int p,int l,int r,int k){
	if(l<=tree[p].l&&tree[p].r<=r){
		insert(p,k);
		return;
	}
	push_down(p);
	int mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid) cover(ls,l,r,k);
	if(r>mid) cover(rs,l,r,k);
	push_up(p);
}
int q[6];
void ask(int p,int l,int r,int k){
	if(l<=tree[p].l&&tree[p].r<=r){
		for(int i=0;i<=k;i++) (q[i]+=tree[p].sum[i])%=mod;
		return;
	}
	push_down(p);
	int mid=(tree[p].l+tree[p].r)>>1;
	if(l<=mid) ask(ls,l,r,k);
	if(r>mid) ask(rs,l,r,k);
}
signed main(){
	C[0][0]=1;
	for(int i=1;i<=5;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	build(1,1,n);
	char op;
	for(int _=1,l,r,k;_<=m;_++){
		cin>>op>>l>>r>>k;
		if(op=='=') cover(1,l,r,k);
		else{
			int ans=0;
			memset(q,0,sizeof(q));
			ask(1,l,r,k);
			for(int i=0;i<=k;i++){
				ans=(ans+C[k][i]%mod*qpow(1-l,k-i)%mod*q[i]%mod+mod)%mod;
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：1saunoya (赞：4)

$(i - l + 1) = (i + (1 - l))$

$(i + (1 - l))^k = \sum_{j = 0}^{k} \binom{j}{k} i^j (1-l)^{k-j}$

二项式定理展开成这样，然后在线段树上维护 $a_i \times i^{j}$ 就好了。

注意到这个 $k$ 只有 $5$ 所以直接搞就好了.jpg。


---

## 作者：wsyhb (赞：3)

## 题解

题目求的东西：

$$\sum_{i=l}^{r}a_i \cdot (i-l+1)^k$$

使用**二项式定理**，把与 $i$ 有关的部分和与 $l$ 有关的部分分离，并交换 $\sum$ 顺序：

$$
\begin{aligned}
&\sum_{i=l}^{r}a_i[\sum_{j=0}^{k}\binom{k}{j}(i+1)^j(-l)^{k-l}]\\
=&\sum_{j=0}^k\binom{k}{j}(-l)^{k-j}[\sum_{i=l}^{r}a_i \cdot (i+1)^j]
\end{aligned}
$$

由于 $k \le 5$，可以使用**线段树**对 $0 \le j \le 5$ 每个 $j$ 直接维护 $\sum_{i=l}^{r}a_i \cdot (i+1)^j$。

只需支持**区间赋值**和**区间查询**即可，时间复杂度 $O(mk\log{n})$。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int max_n=1e5+5;
int a[max_n],Pow[max_n][6],C[6][6];
const int mod=1e9+7;
inline int get_sum(int a,int b)
{
	return a+b-(a+b>=mod?mod:0);
}
namespace SegmentTree
{
	struct Node
	{
		int sum[6],val[6],lazy;
	}node[max_n<<2];
	#define sum(p,x) node[p].sum[x]
	#define val(p,x) node[p].val[x]
	#define lazy(p) node[p].lazy
	#define ls(p) ((p)<<1)
	#define rs(p) ((p)<<1|1)
	void build(int p,int l,int r)
	{
		lazy(p)=-1;
		if(l==r)
		{
			for(int i=0;i<=5;++i)
			{
				sum(p,i)=Pow[l+1][i];
				val(p,i)=1ll*sum(p,i)*a[l]%mod;
			}
			return;
		}
		int mid=(l+r)>>1;
		build(ls(p),l,mid);
		build(rs(p),mid+1,r);
		for(int i=0;i<=5;++i)
		{
			sum(p,i)=get_sum(sum(ls(p),i),sum(rs(p),i));
			val(p,i)=get_sum(val(ls(p),i),val(rs(p),i));
		}
	}
	inline void assign(int p,int v)
	{
		for(int i=0;i<=5;++i)
			val(p,i)=1ll*sum(p,i)*v%mod;
		lazy(p)=v;
	}
	inline void push_down(int p)
	{
		assign(ls(p),lazy(p));
		assign(rs(p),lazy(p));
		lazy(p)=-1;
	}
	void assign(int p,int l,int r,int a,int b,int v)
	{
		if(a<=l&&r<=b)
		{
			assign(p,v);
			return;
		}
		if(~lazy(p))
			push_down(p);
		int mid=(l+r)>>1;
		if(a<=mid)
			assign(ls(p),l,mid,a,b,v);
		if(b>mid)
			assign(rs(p),mid+1,r,a,b,v);
		for(int i=0;i<=5;++i)
			val(p,i)=get_sum(val(ls(p),i),val(rs(p),i));
	}
	int res[6];
	void query(int p,int l,int r,int a,int b,int k)
	{
		if(a<=l&&r<=b)
		{
			for(int i=0;i<=k;++i)
				res[i]=get_sum(res[i],val(p,i));
			return;
		}
		int mid=(l+r)>>1;
		if(~lazy(p))
			push_down(p);
		if(a<=mid)
			query(ls(p),l,mid,a,b,k);
		if(b>mid)
			query(rs(p),mid+1,r,a,b,k);
	}
	inline void query(int l,int r,int k)
	{
		for(int i=0;i<=k;++i)
			res[i]=0;
		query(1,1,n,l,r,k);
		int p=1,ans=0;
		for(int i=k;i>=0;--i)
		{
			ans=(ans+1ll*C[k][i]*p%mod*res[i])%mod;
			p=1ll*p*(mod-l)%mod;
		}
		printf("%d\n",ans);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	for(int i=2;i<=n+1;++i)
	{
		Pow[i][0]=1;
		for(int j=1;j<=5;++j)
			Pow[i][j]=1ll*Pow[i][j-1]*i%mod;
	}
	for(int i=0;i<=5;++i)	
		for(int j=0;j<=i;++j)
			C[i][j]=j==0||j==i?1:C[i-1][j-1]+C[i-1][j];
	SegmentTree::build(1,1,n);
	while(m--)
	{
		char opt[4];
		int l,r,x;
		scanf("%s%d%d%d",opt,&l,&r,&x);
		if(opt[0]=='=')
			SegmentTree::assign(1,1,n,l,r,x);
		else
		{
			assert(opt[0]=='?');
			SegmentTree::query(l,r,x);
		}
	}
	return 0;
}
```

---

## 作者：MortisM (赞：2)

# Preface

[题目链接](http://codeforces.com/problemset/problem/266/E)

很典型的一道线段树题，拿来当模板练练。

# Statement

给你一个长度为 $n$ 的序列 $[a_1,a_2,\cdots,a_n]$，有两种操作:
+ `= l r x` 表示将 $a_l,a_{l+1},\cdots,a_r$ 全部赋成 $x$
+ `? l r k` 表示询问 $\sum_{i=l}^ra_i\cdot(i-l+1)^k$ 模 $10^9+7$ 的值。

# Solution

看这个式子满脸的不可做，所以要用二项式定理把它拆开。

> **二项式定理**：
$$
\begin{aligned}
(x+y)^n&=x^n+\binom{n}{1}x^{n-1}y+\binom{n}{2}x^{n-2}y^2+\cdots+\binom{n}{n-1}xy^{n-1}+y^n\\
\\&=\sum_{k=0}^n\binom{n}{k}x^{n-k}y^k
\end{aligned}
$$

拆开过程如下：

$$
\begin{aligned}
\sum_{i=l}^ra_i\cdot(i-l+1)^k&=\sum_{i=l}^ra_i\cdot(i+(1-l))^k\\&=\sum_{i=l}^ra_i\cdot\sum_{j=0}^k\binom{k}{j}(1-l)^{k-j}\cdot i^j\\&=\sum_{j=0}^k\binom{k}{j}(1-l)^{k-j}\cdot\sum_{i=l}^ra_i\cdot i^j
\end{aligned}
$$

只要维护 $\sum_{i=l}^ra_i\cdot i^j$ 即可，这个直接搞 6 棵线段树带懒标记就行，时间复杂度 $O(n\log n)$，但是自带巨大多常数。

# Summary

无脑拆式子题……

# Code

```cpp
//AC!
#include<bits/stdc++.h>
#define int long long
#define repe(i,l,r) for(int (i)=l;(i)<=r;(i)++)
#define rep(i,n) for(int (i)=1;(i)<=n;(i)++)
#define FOR(i,r,l) for(int (i)=r;(i)>=l;(i)--)
#define INF 0x3f3f3f
#define pii pair<int,int>
#define ll long long
#define mpr make_pair
#define pb push_back
#define F first
#define S second
#define sz(v) (int)((v).size())
#define ALL(v) (v).begin(),(v).end()
#define rALL(v) (v).rbegin(),(v).rend()
#define srt(v) sort(ALL(v))
#define rsrt(v) sort(rALL(v))
#define rev(v) reverse(ALL(v))
#define lb(v,x) (int)(lower_bound(ALL(v),x)-v.begin())
#define ub(v,x) (int)(upper_bound(ALL(v),x)-v.begin())
#define uni(v) v.resize(unique(ALL(v))-v.begin())
using namespace std;
int read(){int sum=0,f=1;char c;c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){sum=(sum<<1)+(sum<<3)+(c-'0');c=getchar();}return sum*f;}
void out(int x){if(x<0){x=-x;putchar('-');}if(x>=10)out(x/10);putchar(x%10+'0');}
void die(string s){puts(s.c_str());exit(0);}
int fast(int a,int b,int P){int res=1;if(P<=0){while(b){if(b&1)res=res*a;a=a*a;b>>=1;}}else{while(b){if(b&1)res=res*a%P;a=a*a%P;b>>=1;}}return res;}
const int N=1e5+10,P=1e9+7;
int n,m,a[N],sum[6][N];
struct node{
	int l,r;
	int val,tag;
};
struct segTree{
	node tree[6][N<<2];
	void pushup(int k,int x){
		tree[k][x].val=(tree[k][x<<1].val+tree[k][x<<1|1].val)%P;
	}
	void pushdown(int k,int x){
		if(tree[k][x].tag==-1)return;
		tree[k][x<<1].val=1LL*tree[k][x].tag*((sum[k][tree[k][x<<1].r]-sum[k][tree[k][x<<1].l-1]+P)%P)%P;
		tree[k][x<<1|1].val=1LL*tree[k][x].tag*((sum[k][tree[k][x<<1|1].r]-sum[k][tree[k][x<<1|1].l-1]+P)%P)%P;
		tree[k][x<<1].tag=tree[k][x<<1|1].tag=tree[k][x].tag;
		tree[k][x].tag=-1;
	}
	void build(int k,int x,int l,int r){
		tree[k][x].l=l,tree[k][x].r=r;
		tree[k][x].tag=-1;
		if(l==r){
			tree[k][x].val=1LL*a[l]*fast(l,k,P)%P;
			return;
		}
		int mid=(l+r)>>1;
		build(k,x<<1,l,mid);
		build(k,x<<1|1,mid+1,r);
		pushup(k,x);
	}
	void update(int k,int x,int l,int r,int v){
		if(tree[k][x].l>=l&&tree[k][x].r<=r){
			tree[k][x].val=1LL*v*((sum[k][tree[k][x].r]-sum[k][tree[k][x].l-1]+P)%P)%P;
			tree[k][x].tag=v;
			return;
		}
		pushdown(k,x);
		int mid=(tree[k][x].l+tree[k][x].r)>>1;
		if(l<=mid)update(k,x<<1,l,r,v);
		if(r>mid)update(k,x<<1|1,l,r,v);
		pushup(k,x);
	}
	int query(int k,int x,int l,int r){
		if(tree[k][x].l>=l&&tree[k][x].r<=r){
			return tree[k][x].val;
		}
		pushdown(k,x);
		int mid=(tree[k][x].l+tree[k][x].r)>>1,ans=0;
		if(l<=mid)ans=query(k,x<<1,l,r);
		if(r>mid)ans=(ans+query(k,x<<1|1,l,r))%P;
		return ans;
	}
}T;
int binom(int x,int y){
	int ans=1;
	for(int i=x;i>x-y;i--)ans*=i;
	for(int i=y;i>1;i--)ans/=i;
	return ans;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<=5;i++){
		for(int j=1;j<=n;j++){
			sum[i][j]=(sum[i][j-1]+fast(j,i,P))%P;
		}
	}
	for(int i=0;i<=5;i++)T.build(i,1,1,n);
	char ch,tmp;
	int l,r,x;
	for(int i=1;i<=m;i++){
		ch=getchar(),tmp=getchar();
		l=read(),r=read(),x=read();
		if(ch=='='){
			for(int j=0;j<=5;j++){
				T.update(j,1,l,r,x);
			}
		}
		else{
			int ans=0;
			for(int j=0;j<=x;j++){
				int mul;
				if((x-j)&1)mul=(P-fast(l-1,x-j,P))%P;
				else mul=fast(l-1,x-j,P);
				ans=(ans+1LL*binom(x,j)*mul%P*T.query(j,1,l,r)%P)%P;
			}
			out(ans),putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：wmy_goes_to_thu (赞：2)

$k$ 只有 $5$，直接二项式展开。

那么就相当于维护 $\sum\limits_{i=1}^{m}a_i\times i^k$ 的值，还有区间赋值，那么预处理 $\sum\limits_{i=1}^{m}i^k$ 的值，分别开 $5+1$ 棵线段树+懒标记维护即可。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
char cc[105];
int a[100005],d[10][100005],c[105][105];
long long sm[6][400005],lz[6][400005];
int powdv(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)ans=1ll*ans*x%mod;
		y>>=1;
		x=1ll*x*x%mod;
	}
	return ans;
}
void build(int K,int l,int r,int o)
{
	if(l==r)
	{
		sm[K][o]=1ll*a[l]*powdv(l,K)%mod;
		return;
	}
	int mid=l+r>>1;
	build(K,l,mid,o<<1);
	build(K,mid+1,r,o<<1|1);
	sm[K][o]=(sm[K][o<<1]+sm[K][o<<1|1])%mod;
}
void pushdown(int K,int l,int r,int o)
{
	if(lz[K][o]==-1)return;
	int mid=l+r>>1;
	sm[K][o<<1]=1ll*lz[K][o]*(d[K][mid]-d[K][l-1])%mod;
	sm[K][o<<1|1]=1ll*lz[K][o]*(d[K][r]-d[K][mid])%mod;
	lz[K][o<<1]=lz[K][o<<1|1]=lz[K][o],lz[K][o]=-1;
}
void add(int K,int l,int r,int o,int ll,int rr,int v)
{
	if(l>=ll&&r<=rr)
	{
		lz[K][o]=v;
		sm[K][o]=1ll*lz[K][o]*(d[K][r]-d[K][l-1])%mod;
		return;
	}
	pushdown(K,l,r,o);
	int mid=l+r>>1;
	if(mid>=ll)add(K,l,mid,o<<1,ll,rr,v);
	if(mid<rr)add(K,mid+1,r,o<<1|1,ll,rr,v);
	sm[K][o]=(sm[K][o<<1]+sm[K][o<<1|1])%mod;
}
int query(int K,int l,int r,int o,int ll,int rr)
{
	if(l>=ll&&r<=rr)return sm[K][o];
	pushdown(K,l,r,o);
	int mid=l+r>>1,ans=0;
	if(mid>=ll)ans+=query(K,l,mid,o<<1,ll,rr);
	if(mid<rr)ans+=query(K,mid+1,r,o<<1|1,ll,rr);
	return ans%mod;
}
int main()
{
	for(int i=0;i<=100;i++)c[i][0]=1;
	for(int i=1;i<=100;i++)for(int j=1;j<=i;j++)
		c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	memset(lz,-1,sizeof(lz));
	for(int K=0;K<=5;K++)
	{
		for(int i=1;i<=n;i++)d[K][i]=(d[K][i-1]+powdv(i,K))%mod;
		build(K,1,n,1);
	}
	while(m--)
	{
		scanf("%s",cc+1);
		if(cc[1]=='=')
		{
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			for(int K=0;K<=5;K++)add(K,1,n,1,l,r,x);
		}else
		{
			int l,r,k,dd=0;
			scanf("%d%d%d",&l,&r,&k);
			for(int K=0;K<=k;K++)
			{
				int cs=1ll*powdv(1-l,k-K)*c[k][K]%mod;
				dd=(dd+1ll*cs*query(K,1,n,1,l,r))%mod;
			}
			printf("%d\n",(dd+mod)%mod);
		}
	}
	return 0;
}
```

---

## 作者：lemondinosaur (赞：2)

[洛谷传送门](https://www.luogu.com.cn/problem/CF266E)

[CF266E传送门](http://codeforces.com/problemset/problem/266/E)

---
# 分析
首先区间修改区间查询首选线段树

要找突破口，$(i-l+1)^k$中$i$不是定值，

显然得拆开，而且$k$很小，根据二项式定理，
$$\sum_{i=l}^ra_i(i-l+1)^k=\sum_{i=l}^ra_i\sum_{j=0}^kC(k,j)\times i^j\times (l-1)^{k-j}\times (-1)^{k-j}$$

$$=\sum_{j=0}^kC(k,j)\times (\sum_{i=l}^ra_i\times i^j)\times (l-1)^{k-j}\times (-1)^{k-j}$$

那么线段树叶子节点维护$a_i\times i^j$，

对于区间修改在预处理时做前缀和，直接赋值

显然正整数幂和组合数都能预处理，

所以时间复杂度$O((n+m)klogn)$

卡常：
1. 不用快速幂，预处理的时候通过$i^{j-1}$推出$i^j$
2. 注意0^0=1，虽然在初中无意义
3. 线段树每次只递归1次，$j=0\sim 5$同时修改查询，查询最后用一个结构体记录答案，懒标记只需要1个
4. 组合数可以不用阶乘，实测快30ms

---
# 代码
```cpp
#include <cstdio>
#include <cctype>
#define rr register
using namespace std;
const int N=100011,mod=1000000007;
int si[6][N],a[N],n,m,c[6][6];
inline signed iut(){
	rr int ans=0; rr char c=getchar();
	while (!isdigit(c)) c=getchar();
	while (isdigit(c)) ans=(ans<<3)+(ans<<1)+(c^48),c=getchar();
	return ans;
}
inline void print(int ans){
	if (ans>9) print(ans/10);
	putchar(ans%10+48);
}
inline signed mo(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline void Pro(int n){
	c[0][0]=1;
	for (rr int i=1;i<6;++i){
		c[i][0]=c[i][i]=1;
		for (rr int j=1;j<i;++j)
		    c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	for (rr int i=0;i<=n;++i) si[0][i]=1;
	for (rr int j=1;j<6;++j)
	for (rr int i=1;i<=n;++i) si[j][i]=1ll*si[j-1][i]*i%mod;
	for (rr int j=0;j<6;++j)
	for (rr int i=1;i<=n;++i) si[j][i]=mo(si[j][i],si[j][i-1]);
}
inline signed Get(int k,int l,int r){return mo(si[k][r],mod-si[k][l-1]);}
struct Array_Six{int Q[6];};
struct Segment_Tree{
	int w[N<<2][6],lazy[N<<2];
	inline void pup(int k){
		for (rr int j=0;j<6;++j)
		    w[k][j]=mo(w[k<<1][j],w[k<<1|1][j]);
	}
	inline void build(int k,int l,int r){
		lazy[k]=-1;
		if (l==r){
			for (rr int j=0;j<6;++j)
			    w[k][j]=1ll*a[l]*Get(j,l,l)%mod;
		    return;
		}
		rr int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		pup(k);
	}
	inline void pdown(int k,int l,int mid,int r){
		if (~lazy[k]){
			lazy[k<<1]=lazy[k<<1|1]=lazy[k];
			for (rr int j=0;j<6;++j)
			    w[k<<1][j]=1ll*lazy[k]*Get(j,l,mid)%mod,
			    w[k<<1|1][j]=1ll*lazy[k]*Get(j,mid+1,r)%mod;
			lazy[k]=-1;
		}
	}
	inline void update(int k,int l,int r,int x,int y,int z){
		if (l==x&&r==y){
			lazy[k]=z;
			for (rr int j=0;j<6;++j)
			    w[k][j]=1ll*z*Get(j,l,r)%mod;
			return;
		}
		rr int mid=(l+r)>>1; pdown(k,l,mid,r);
		if (y<=mid) update(k<<1,l,mid,x,y,z);
		else if (x>mid) update(k<<1|1,mid+1,r,x,y,z);
		else update(k<<1,l,mid,x,mid,z),update(k<<1|1,mid+1,r,mid+1,y,z);
		pup(k);
	}
	inline Array_Six query(int k,int l,int r,int x,int y){
		rr Array_Six t1,t2;
		if (l==x&&r==y){
			for (rr int j=0;j<6;++j)
			    t1.Q[j]=w[k][j];
			return t1;
		}
		rr int mid=(l+r)>>1; pdown(k,l,mid,r);
		for (rr int j=0;j<6;++j) t1.Q[j]=t2.Q[j]=0;
		if (y<=mid) t1=query(k<<1,l,mid,x,y);
		else if (x>mid) t2=query(k<<1|1,mid+1,r,x,y);
		else t1=query(k<<1,l,mid,x,mid),
		    t2=query(k<<1|1,mid+1,r,mid+1,y);
		for (rr int j=0;j<6;++j) t1.Q[j]=mo(t1.Q[j],t2.Q[j]);
		return t1;
	}
}Tre;
signed main(){
	n=iut(); m=iut(); Pro(N-11);
	for (rr int i=1;i<=n;++i) a[i]=iut();
	Tre.build(1,1,n);
	for (;m;--m){
		rr char C=getchar();
		while (C!='?'&&C!='=') C=getchar();
		if (C=='='){
			rr int l=iut(),r=iut(),x=iut();
			Tre.update(1,1,n,l,r,x);
		}else{
			rr int l=iut(),r=iut(),k=iut(),ans=0;
			rr Array_Six t=Tre.query(1,1,n,l,r);
			for (rr int j=0,W;j<=k;++j){
				if (l>1) W=Get(k-j,l-1,l-1);
				    else W=si[k-j][l-1];
				if (((k^j)&1)&&W) W=mod-W;
				ans=mo(ans,1ll*W*c[k][j]%mod*t.Q[j]%mod);
			}
			print(ans),putchar(10);
		}
	}
	return 0;
}
```

---

## 作者：Setsugesuka (赞：1)

看到区间赋值，不难想到 $ODT$ 。

然后 $T$ 光了。

观察式子，不难发现一段连续的 $ai$ 的 $ai*(i-l+1)^k$ 是不同的。

于是我们考虑不用 $ODT$ 去解决这个问题。

注意到 $K$ 很小，把式子变换一下。显然有 $(i-l+1)^k=(i+(1-l))^k$ 。 $ai*i$ 可以预处理，$1-l$ 的次幂也可以预处理，对于每次询问，我们用二项式定理去展开它，用我们维护好的信息去算就可以了（markdown打不来sigma..）。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

template <class T>
inline bool read(T &ret)
{
    char c;
    int sgn;
    if (c = getchar(), c == EOF)
    {
        return 0;
    }
    while (c != '-' && (c < '0' || c > '9'))
    {
        c = getchar();
    }
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0');
    }
    ret *= sgn;
    return 1;
}

template <class T>
inline void write(T x)
{
    if (x > 9)
    {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}

const int MAXN=1e6+10;
const long long MOD=1e9+7;
long long cc[MAXN][6],sum[MAXN][6],lazy[MAXN],ans[6];
int n,m;

inline long long calc(int l,int r,int k)
{
    return ((cc[r][k]-cc[l-1][k])%MOD+MOD)%MOD;
}

inline void pushup(int x)
{
    for(int i=0;i<=5;i++)
    {
        sum[x][i]=(sum[x<<1][i]+sum[x<<1|1][i])%MOD;
    }
}

inline void pushdown(int l,int r,int x)
{
    if(lazy[x]!=-1)
    {
        int mid=(l+r)>>1;
        lazy[x<<1]=lazy[x];
        lazy[x<<1|1]=lazy[x];
        for(int i=0;i<=5;i++)
        {
            sum[x<<1][i]=(lazy[x]*calc(l,mid,i))%MOD;
            sum[x<<1|1][i]=(lazy[x]*calc(mid+1,r,i))%MOD;
        }
        lazy[x]=-1;
    }
}

void build(int l,int r,int x)
{
    lazy[x]=-1;
    if(l==r)
    {
        int sr;
        read(sr);
        for(int i=0;i<=5;i++)
        {
            sum[x][i]=sr*calc(l,l,i)%MOD;
        }
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,x<<1);
    build(mid+1,r,x<<1|1);
    pushup(x);
}

void change(int L,int R,int C,int l,int r,int x)
{
    if(L<=l&&r<=R)
    {
        lazy[x]=C;
        for(int i=0;i<=5;i++)
        {
            sum[x][i]=C*calc(l,r,i)%MOD;
        }
        return;
    }
    pushdown(l,r,x);
    int mid=(l+r)>>1;
    if(L<=mid)
        change(L,R,C,l,mid,x<<1);
    if(R>mid)
        change(L,R,C,mid+1,r,x<<1|1);
    pushup(x);
}

void query(int L,int R,int l,int r,int x)
{
    if(L<=l&&r<=R)
    {
        for(int i=0;i<=5;i++)
        {
            ans[i]=(ans[i]+sum[x][i])%MOD;
        }
        return;
    }
    pushdown(l,r,x);
    int mid=(l+r)>>1;
    if(L<=mid)
        query(L,R,l,mid,x<<1);
    if(R>mid)
        query(L,R,mid+1,r,x<<1|1);
}

signed main()
{
    read(n),read(m);
    for(int i=1;i<=n;i++)
    {
        cc[i][0]=1;
        for(int j=1;j<=5;j++)
        {
            cc[i][j]=(cc[i][j-1]*i)%MOD;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=5;j++)
        {
            cc[i][j]=(cc[i][j]+cc[i-1][j])%MOD;
        }
    }
    build(1,n,1);
    while(m--)
    {
        char op;
        cin>>op;
        int l,r,k;
        read(l),read(r),read(k);
        if(op=='=')
        {
            change(l,r,k,1,n,1);
        }
        else
        {
            memset(ans,0,sizeof(ans));
            query(l,r,1,n,1);
            long long ret=0;
            if(k==0)
            {
                ret+=ans[0];
                ret%=MOD;
            }
            else if(k==1)
            {
                ret+=ans[1];
                ret%=MOD;
                ret-=((l-1)*ans[0])%MOD;
                ret+=MOD;
                ret%=MOD;
            }
            else if(k==2)
            {
                ret+=ans[2];
                ret%=MOD;
                ret-=(2*(l-1)*ans[1])%MOD;
                ret+=MOD;
                ret%=MOD;
                ret+=((l-1)*(l-1)%MOD*ans[0])%MOD;
                ret%=MOD;
            }
            else if(k==3)
            {
                ret+=ans[3];
                ret%=MOD;
                ret-=(3*(l-1)*ans[2])%MOD;
                ret+=MOD;
                ret%=MOD;
                ret+=(3*(l-1)*(l-1)%MOD*ans[1])%MOD;
                ret%=MOD;
                ret-=((((l-1)*(l-1))%MOD*(l-1))%MOD*ans[0])%MOD;
                ret+=MOD;
                ret%=MOD;
            }
            else if(k==4)
            {
                ret+=ans[4];
                ret%=MOD;
                ret-=(4*(l-1)*ans[3])%MOD;
                ret+=MOD;
                ret%=MOD;
                ret+=(6*(l-1)*(l-1)%MOD*ans[2])%MOD;
                ret%=MOD;
                ret-=(((4*(l-1)*(l-1))%MOD*(l-1))%MOD*ans[1])%MOD;
                ret+=MOD;
                ret%=MOD;
                ret+=(((((l-1)*(l-1)%MOD)*(l-1))%MOD*(l-1))%MOD*ans[0])%MOD;
                ret%=MOD;
            }
            else if(k==5)
            {
                ret+=ans[5];
                ret%=MOD;
                ret-=(5*(l-1)*ans[4])%MOD;
                ret+=MOD;
                ret%=MOD;
                ret+=(10*(l-1)*(l-1)%MOD*ans[3])%MOD;
                ret%=MOD;
                ret-=(((10*(l-1)*(l-1))%MOD*(l-1))%MOD*ans[2])%MOD;
                ret+=MOD;
                ret%=MOD;
                ret+=((((5*(l-1)*(l-1)%MOD)*(l-1))%MOD*(l-1))%MOD*ans[1])%MOD;
                ret%=MOD;
                ret-=(((((l-1)*(l-1)%MOD*(l-1))%MOD*(l-1))%MOD*(l-1))%MOD*ans[0])%MOD;
                ret+=MOD;
                ret%=MOD;
            }
            ret=(ret%MOD+MOD)%MOD;
            write(ret);
            putchar('\n');
        }
    }
    return 0;
}
```


---

## 作者：Populus_euphratica (赞：0)

首先，考虑如何将贡献拆开。

仔细看看，可以考虑使用二项式定理：

$$
\sum_{i = l} ^ r a_i(i - l + 1) ^ k\\
=\sum_{i = l} ^ r a_i \sum_{j = 0} ^ k \binom{k}{j} (i + 1) ^ j (-l) ^ {k - j}\\
$$

转换求和顺序可以得到：

$$
\sum_{j = 0} ^ k \binom{k}{j}(-l) ^ {k - j} \sum_{i = l} ^ r a_i(i + 1) ^ j
$$

后面的部分可以使用线段树进行维护。

由于 $k$ 的取值不大，可以对每一个 $k$ 维护一个答案。

并且是区间赋值，同时也需要把 $(i + 1) ^ j$ 一起维护方便修改。

区间赋值，区间查询，时间复杂度为 $O(m \log n)$，因为要处理所有的 $k$，所以要带一个六倍的常数。

```cpp
#include<bits/stdc++.h>
#define lson (x << 1)
#define rson ((x << 1) | 1)
#define mid ((l + r) >> 1)
#define int long long
using namespace std;
const int Maxn = 100010, mod = 1e9 + 7;
int n, Q;
int a[Maxn], Pow[Maxn][10];
struct node{
	int Pow[10], sum[10];
}Tree[Maxn << 2];
int tag[Maxn << 2];
int C[10][10];
int ppow(int x, int y){
	int s = 1;
	while(y--) s = s * x % mod;
	return s;
}
void update(int x){
	for(int i = 0 ; i <= 5 ; i++){
		Tree[x].sum[i] = (Tree[lson].sum[i] + Tree[rson].sum[i]) % mod; 
		Tree[x].Pow[i] = (Tree[lson].Pow[i] + Tree[rson].Pow[i]) % mod;
	}
}
void build(int x, int l, int r){
	tag[x] = -1;
	if(l == r){
		for(int i = 0 ; i <= 5 ; i++) Tree[x].Pow[i] = Pow[l][i];
		for(int i = 0 ; i <= 5 ; i++) Tree[x].sum[i] = Tree[x].Pow[i] * a[l] % mod;
		return ;
	}
	build(lson, l, mid);
	build(rson, mid + 1, r);
	update(x);
}
void pushup(int x, int v){
	for(int i = 0 ; i <= 5 ; i++){
		Tree[x].sum[i] = Tree[x].Pow[i] * v % mod;
	}
	tag[x] = v;
}
void pushdown(int x){
	if(tag[x] == -1) return ;
	pushup(lson, tag[x]);
	pushup(rson, tag[x]);
	tag[x] = -1;
}
void modify(int x, int l, int r, int L, int R, int v){
	if(L <= l && r <= R){
		pushup(x, v);
		return ;
	}
	if(tag[x] != -1) pushdown(x);
	if(L <= mid) modify(lson, l, mid, L, R, v);
	if(mid < R) modify(rson, mid + 1, r, L, R, v);
	update(x);
}
node query(int x, int l, int r, int L, int R){
	if(L <= l && r <= R) return Tree[x];
	node s1, s2;
	memset(s1.sum, 0, sizeof(s1.sum));
	memset(s2.sum, 0, sizeof(s2.sum));
	if(tag[x] != -1) pushdown(x);
	if(L <= mid) s1 = query(lson, l, mid, L, R);
	if(mid < R) s2 = query(rson, mid + 1, r, L, R);
	node s;
	for(int i = 0 ; i <= 5 ; i++) s.sum[i] = (s1.sum[i] + s2.sum[i]) % mod;
	return s;
}
signed main(){
	ios::sync_with_stdio(false);
	cin >> n >> Q;
	for(int i = 1 ; i <= n ; i++) cin >> a[i];
	for(int i = 1 ; i <= n ; i++){
		Pow[i][0] = 1;
		for(int j = 1 ; j <= 5 ; j++)
			Pow[i][j] = Pow[i][j - 1] * (i + 1) % mod;
	}
	for(int i = 0 ; i <= 5 ; i++){
		for(int j = 0 ; j <= i ; j++){
			if(i == 0 || j == 0) C[i][j] = 1;
			else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
	build(1, 1, n);
	while(Q--){
		char op;
		int l, r, x;
		cin >> op >> l >> r >> x;
		if(op == '='){
			modify(1, 1, n, l, r, x);
			continue;
		}
		node s = query(1, 1, n, l, r);
		int ans = 0;
		for(int i = 0 ; i <= x ; i++)
			ans = (ans + C[x][i] * ppow(mod - l, x - i) % mod * s.sum[i]) % mod;
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：BFSDFS123 (赞：0)

看到 $k\le 5$，直接合理推测拆开式子，建 $k$ 棵线段树。

$(i-l+1)^k$ 是一个奇怪的式子，我们不妨考虑将其利用二项式定理拆开。

有：

$$(i-l+1)^k= [(i+1)-l]^k= \sum_{j=0}^k{\binom{k}{j}\times (i+1)^j\times (-l)^{k-j}}$$

将 $a_i$ 带入，有：

$$\sum_{i=1}^na_i \sum_{j=0}^k{\binom{k}{j}\times (i+1)^j\times (-l)^{k-j}}$$

看到这个式子，我们先考虑将 $a_i$ 和后面的一堆东西扔在一起，用线段树维护。

结果就变成了：

$$\sum_{j=0}^k{{\binom{k}{j}\times (-l)^{k-j}}\times [\sum_{i=1}^n a_i(i+1)^j]}$$

后面的中括号里的那一撮东西用可以用线段树维护

---

## 作者：FutaRimeWoawaSete (赞：0)

考虑维护的东西可以用二项式定理拆开那就先拆开：              

$a_i(i - l + 1) ^ k$         

$= a_i(i - (l - 1)) ^ k$

$= \sum_{s = 0} ^ k (a_i \times i ^ s) \times (l - 1) ^ {k - s} \times (-1) ^ {k - s}$            

考虑中间的东西之和 $i$ 有关所以必定可以维护，而后面的东西在 $s$ 和 $k$ 固定的情况下每次查询固定。观察到 $k$ 很小我们考虑对于每个 $s$ 进行计算。            

$\sum_{i = l} ^ r a_i(i - l + 1)$        

$= \sum_{s = 0} ^ k (l - 1) ^ {k - s} \times (-1) ^ {k - s} \times (\sum_{i = l} ^ r a_i \times i ^ s)$          

前面的东西可以在每次枚举 $k$ 时计算，后面的东西线段树维护即可。       
时间复杂度 $O(6 n\log n)$。

当然也可以通过分块维护，这个就更简单了，维护一下所有的块内 $0 ^ k + 1 ^ k + 2 ^ k + 3 ^ k ....$ 之和以及块内的 $a_{L_i} \times 0 ^ k + a_{L_i + 1} \times 1 ^ k ....$ 之和即可，时间复杂度 $O(6 n \sqrt n)$，但是不知道为什么这个脑瘫题不放过。               

```cpp
#include "bits/stdc++.h"
using namespace std;
#define int long long
const int Len = 1e5 + 5 , mod = 1e9 + 7;
int n,m,tag[Len << 2],C[7][7],a[Len];
long long sumB[Len << 2][7],sum[Len << 2][7],qpow[Len][7];
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
void push_up(int x){for(int i = 0 ; i <= 5 ; i ++) sumB[x][i] = sumB[ls(x)][i] + sumB[rs(x)][i] , sumB[x][i] %= mod;}
void push_down(int p,int l,int r)
{
	if(~tag[p])
	{
		tag[ls(p)] = tag[rs(p)] = tag[p];
		for(int i = 0 ; i <= 5 ; i ++)
		{
			sumB[ls(p)][i] = sum[ls(p)][i] * tag[ls(p)] % mod;
			sumB[rs(p)][i] = sum[rs(p)][i] * tag[rs(p)] % mod;
		}
	}
	tag[p] = -1;
}
void build(int p,int l,int r)
{
	tag[p] = -1;
	if(l == r)
	{
		for(int i = 0 ; i <= 5 ; i ++) 
		{
			sum[p][i] = qpow[l][i];
			sumB[p][i] = sum[p][i] * a[l] % mod;
		}
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
	for(int i = 0 ; i <= 5 ; i ++) sum[p][i] = sum[ls(p)][i] + sum[rs(p)][i] , sum[p][i] %= mod;
}
void update(int p,int l,int r,int nl,int nr,int k)
{
	if(nl <= l && nr >= r)
	{
		tag[p] = k;
		for(int i = 0 ; i <= 5 ; i ++) sumB[p][i] = sum[p][i] * tag[p] % mod;
		return;
	}
	push_down(p , l , r);
	int mid = (l + r) >> 1;
	if(nl <= mid) update(ls(p) , l , mid , nl , nr , k);
	if(nr > mid) update(rs(p) , mid + 1 , r , nl , nr , k);
	push_up(p);
}
long long query(int p,int l,int r,int nl,int nr,int k)
{
	if(nl <= l && nr >= r) return sumB[p][k];
	push_down(p , l , r);
	int mid = (l + r) >> 1;long long res = 0;
	if(nl <= mid) res += query(ls(p) , l , mid , nl , nr , k);
	if(nr > mid) res += query(rs(p) , mid + 1 , r , nl , nr , k);
	res %= mod;
	return res; 
}
char s[3];
long long Qpow(int x)
{
	if(x % 2 == 1) return -1;
	return 1;
}
signed main()
{
	C[0][0] = C[1][0] = C[1][1] = 1;
	for(int i = 2 ; i <= 5 ; i ++)
		for(int j = 0 ; j <= i ; j ++)
		{
			if(j == 0 || j == i) C[i][j] = 1;
			else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	scanf("%lld %lld",&n,&m);
	for(int i = 0 ; i <= n ; i ++) 
	{
		qpow[i][0] = 1;
		for(int j = 1 ; j <= 5 ; j ++) qpow[i][j] = qpow[i][j - 1] * i % mod;
	}
	for(int i = 1 ; i <= n ; i ++) scanf("%lld",&a[i]);
	build(1 , 1 , n);
	for(int i = 1 ; i <= m ; i ++)
	{
		scanf("%s",s);int l,r,k;scanf("%lld %lld %lld",&l,&r,&k);
		if(s[0] == '?') 
		{
			long long YYSWYS = 0;
			for(int s = 0 ; s <= k ; s ++)
			{
				YYSWYS += C[k][s] * query(1 , 1 , n , l , r , s)  
				% mod * qpow[l - 1][k - s] * Qpow(k - s) % mod;
				YYSWYS = (YYSWYS + mod) % mod;
			} 
			printf("%lld\n",YYSWYS);
		}
		else update(1 , 1 , n , l , r,  k);
		
	} 
	return 0;
}
```

---

