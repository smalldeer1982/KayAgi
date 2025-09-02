# Subsequences

## 题目描述

For the given sequence with $ n $ different elements find the number of increasing subsequences with $ k+1 $ elements. It is guaranteed that the answer is not greater than $ 8·10^{18} $ .

## 样例 #1

### 输入

```
5 2
1
2
3
5
4
```

### 输出

```
7
```

# 题解

## 作者：Emp7iness (赞：9)

树状数组优化 dp。（不用线段树的原因是因为码量大，常数也大）

定义 $dp[i][j]$ 表示以第 $i$ 个结尾，长度为 $j$ 的严格上升子序列的个数。

得到这么一个式子：

$$dp[i][j]=\sum_{a[k]<a[i]} dp[k][j-1]$$

当然如果这么做时间复杂度是 $O(n^2m)$，显然会 TLE，考虑优化。

我们可以建 $m$ 个树状数组，分别维护长度从 $1$ 到 $m$ 的最长子序列个数，这样可以优化到 $O(nm\log n)$，可以通过此题。

另外，因为 $dp[i][j]$ 的值只从 $dp[i][j-1]$ 转移得来，所以可以压掉一维，空间复杂度降低到 $O(n)$。

代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define int long long
const int N=1e5+5;
int n,k,ans,a[N],t[N],f[N];
int lowbit(int k)
{
	return k&-k;
}
void add(int x,int k)
{
	while(x<=n)
	{
		t[x]+=k;
		x+=lowbit(x);
	}
}
int sum(int x)
{
	int s=0;
	while(x!=0)
	{
		s+=t[x];
		x-=lowbit(x);
	}
	return s;
}
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		f[i]=1;
	}
	for(int i=1;i<=k;i++)
	{
		memset(t,0,sizeof(t));
		for(int j=1;j<=n;j++)
		{
			add(a[j],f[j]);
			f[j]=sum(a[j]-1);
		}
	}
	for(int i=1;i<=n;i++)	ans+=f[i];
	cout<<ans;
	return 0;
}
```


---

## 作者：king_xbz (赞：4)

比较经典的子序列$DP$问题，但是求的不是最长上升子序列，而是长为$k+1$的上升子序列个数

很容易求得一个算法，$O(n^2)$枚举起点终点，然后求出期间长为$k+1$的上升子序列。

$f_{i,j}=\sum_{l=1}^{{i-1}}f_{l,j-1}$,其中$[a_l<a_i]$。

代码：

```cpp
for(fint i=1;i<=n;i++)
f[i][1]=1;
for(int i=2;i<=n;i++)
for(fint j=2;j<=min(i,k+1);j++)
{
	for(fint l=1;l<i;l++)
	if(a[l]<a[i])
	f[i][j]+=f[l][j-1];
}
```

但是，$1e5$的数据范围显然需要一个$O(n\ log\ n)$的算法。

所以我们需要考虑数据结构优化。

就用树状数组吧。

怎么优化呢？

我们观察到第三重循环，有几个$l$，满足$a[l]<a[i]$就转移几次。所以，我们可以开$11$个树状数组，维护序列长为$1-k+1$时的值，查询前面有几个比自己小即可。

对于转移，我们可以直接把dp数组$f[i][j]$给放到第$j$个树状数组中去。此时一次查询就可以完成转移。

代码：

```cpp
#include<bits/stdc++.h>
#define fint register int
#define H 5001
#define N 105904
#define int long long
using namespace std;
int n,k;
int a[N],f[N][15],t[N][15];
inline int lowbit(int x);
inline int query(int x,int j);
inline void adds(int x,int y,int j);
signed main()
{
	cin>>n>>k;
	for(fint i=1;i<=n;i++)
	cin>>a[i];
	for(fint i=1;i<=n;i++)
	{
		adds(a[i],1,1);
		for(fint j=2;j<=k+1;j++)
		f[i][j]=query(a[i]-1,j-1),adds(a[i],f[i][j],j);
	} 
	int ans=0;
	for(fint i=1;i<=n;i++)
	ans+=f[i][k+1];
	if(k==0)
	ans++;
	cout<<ans;
	return 0;
}

inline void adds(int x,int y,int j)
{
	for(fint i=x;i<=n;i+=lowbit(i))
	t[i][j]+=y;
	return ;
}

inline int query(int x,int j)
{
	int tot=0;
	for(fint i=x;i;i-=lowbit(i))
	tot+=t[i][j];
	return tot;
}

inline int lowbit(int x)
{
	return x&(-x);
}
```
这样，我们就完成了此题。


---

## 作者：2016gdgzoi581 (赞：3)

题意：给出大小为$n$的数组$a$，求长度为$k+1$的上升子序列的个数，其中$a_i$两两不等。

题解：考虑到$k \le 10$,故设$f_{i,j}$表示以$a_i$结尾的长度为$j$的上升子序列的个数，易得$$f_{i,j}=\sum_{k=1}^{{i-1}}f_{k,j-1}[a_k<a_i]$$

因此我们将$a$中的数按顺序加入，枚举序列长度$j$，用树状数组维护转移
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
int n,k,c[160010][12];
int lb(int x){
	return x&-x;
} 
void inc(int pos,int val,int k){
	for(int i=pos;i<=n;i+=lb(i)){
		c[i][k]+=val;
	}
}
int sum(int pos,int k){
	int res=0;
	for(int i=pos;i;i-=lb(i)){
		res+=c[i][k];
	}
	return res;
}
int ans=0;
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;++i){
		int x;
		scanf("%lld",&x);
		inc(x,1,1);
		for(int j=2;j<=k+1;++j){
			int s=sum(x-1,j-1);
			inc(x,s,j);
			if(j==k+1)ans+=s;
		}
	}
	cout<<ans;
}
```

---

## 作者：registerGen (赞：2)

# Solution

DS 优化 dp。

设 $f_{i,j}$ 表示 $a_1\sim a_i$ 中长度为 $j$ 的 LIS。

则

$$f_{i,j}=\begin{cases}1&j=1\\\displaystyle\sum_{k=1}^{i-1}[a_k<a_i]f_{k,j-1}&j\ge 2\end{cases}$$

开 $10$ 个 BIT 优化即可。

# Code

```cpp
// f[i][j] = [a_k < a_i] * f[k][j-1] k = 1 to i - 1

#include<cstdio>
#include<algorithm>

typedef long long ll;

const int N=1e5;

int n,k,a[N+10];
ll ans,f[N+10][15];

struct BIT // 树状数组
{
	ll c[N+10];

#define lowbit(x) (x&(-x))

	inline void modify(int i,ll x)
	{
		for(;i<=n;i+=lowbit(i))c[i]+=x;
	}

	inline ll query(int i)
	{
		ll res=0;
		for(;i;i-=lowbit(i))res+=c[i];
		return res;
	}

#undef lowbit
}t[15];

int main()
{
	scanf("%d%d",&n,&k);k++;
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	if(k==1)return printf("%d\n",n),0; // 特判
	for(int i=1;i<=n;i++)
	{
		t[1].modify(a[i],1); // f[i][1] = 1
		for(int j=2;j<=k;j++)
		{
			// 经典的写法
			f[i][j]=t[j-1].query(a[i]-1);
			t[j].modify(a[i],f[i][j]);
		}
		ans+=f[i][k]; // 统计答案
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：AFewSuns (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF597C)

### 题目大意

给你一个 $1 \sim n$ 的排列 $a$，求长度为 $k+1$ 的 LIS 个数。

$1 \leq n \leq 10^5,0 \leq k \leq 10$

### 题目分析

先不管数据范围，思考如何暴力 dp。

一个非常非常非常暴力的做法就是设 $f[i][j][s]$ 为前 $i$ 个数中，LIS 长度为 $j$ 且末尾为 $s$ 的子序列个数。

如何转移？分两种情况：

1. $s \neq a_i$：$f[i][j][s]=f[i-1][j][s]$

1. $s=a_i$：$f[i][j][s]=f[i-1][j][s]+\displaystyle\sum_{ss=1}^{s}{f[i-1][j-1][ss]}$

这样无论是空间还是时间都会炸，于是考虑如何优化。

盯着这个转移方程看，有区间的求和，而且不复杂，考虑用线段树优化。

发现 $k+1$ 很小，直接暴力开 $k+1$ 颗线段树，然后以 LIS 末尾数字 $s$ 为下标建线段树。

枚举 $i$，对于第一种情况，不用管；第二种情况，相当于是在原来的基础上加上 $\displaystyle\sum_{ss=1}^{s}{f[i-1][j-1][ss]}$

这个东西直接在 $j-1$ 这颗线段树里面查 $[1,s]$ 的和即可。

一点细节：倒序枚举 $j$，原因如 01 背包，不要影响后面的答案。

注意特判一下 $j=1$，这个时候序列个数无论如何都是 $1$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define LC lc[x]
#define RC rc[x]
using namespace std;
ll n,k,a[100010],tmp;
ll rt[15],tree[5000050],lc[5000050],rc[5000050],tot=0;
void pushup(ll x){
	tree[x]=tree[LC]+tree[RC];
}
void build(ll &x,ll l,ll r){
	x=++tot;
	if(l==r) return;
	ll mid=(l+r)>>1;
	build(LC,l,mid);
	build(RC,mid+1,r);
}
void mdf(ll x,ll l,ll r,ll pos,ll v){
	if(l==r){
		tree[x]+=v;
		return;
	}
	ll mid=(l+r)>>1;
	if(pos<=mid) mdf(LC,l,mid,pos,v);
	else mdf(RC,mid+1,r,pos,v);
	pushup(x);
}
ll query(ll x,ll l,ll r,ll ql,ll qr){
	if(ql<=l&&r<=qr) return tree[x];
	ll mid=(l+r)>>1,res=0;
	if(ql<=mid) res+=query(LC,l,mid,ql,qr);
	if(mid<qr) res+=query(RC,mid+1,r,ql,qr);
	return res;
}
int main(){
	scanf("%lld %lld",&n,&k);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(ll i=1;i<=k+1;i++) build(rt[i],1,n);
	for(ll i=1;i<=n;i++){
		for(ll j=k+1;j>=1;j--){
			if(j==1) tmp=1;
			else tmp=query(rt[j-1],1,n,1,a[i]);
			mdf(rt[j],1,n,a[i],tmp);
		}
	}
	printf("%lld",tree[rt[k+1]]); 
}
```

---

## 作者：StayAlone (赞：0)

从 UVA 那个极度卡常题来的。

一道简单题，思维黄，非常板，加个树状数组算个绿吧。

### 思路

显然 dp。设 $f_{i, j}$ 表示以 $a_i$ 结尾，长度为 $j$ 的严格上升子序列数量。

容易得到 $\mathcal O(n^2m)$ 的 dp：

$$
f_{i,j} = \sum_{k < i \land a_k < a_i} f_{k, j - 1}
$$

含义是第 $i$ 个必须选，那么转移来的 $a_k < a_i$ 就需要累加。

考虑在循环的过程中，将 $i-1$ 内，结尾为 $v$，长度为 $j$ 的 $f$ 数组累加进 $S_{j,v}$ 中，再进行前缀和。形式化的，$S_{j, v} = \sum\limits_{k \leq i-1\land a_k= v} f_{k, j}$。

那么转移方程可以改写为：

$$
f_{i,j} = \sum_{v=1}^{a_i - 1}S_{j - 1, v}
$$

每求出一个 $f_{i, j}$，在树状数组上修改 $S_{j, a_i}$。转移时直接查询即可。

$ans = \sum\limits_{i=1}^n f_{i, k + 1}$。

时间复杂度 $\mathcal O(nm\log n)$。

[AC code record](https://www.luogu.com.cn/record/101003075)

```cpp
int n, m, a[MAXN]; ll f[MAXN][15];

struct setr {
	ll sum[MAXN];
	
	il void add(int x, ll k) {
		while (x <= n) sum[x] += k, x += lowbit(x);
	}
	
	il ll query(int x) {
		ll ans = 0;
		while (x) ans += sum[x], x -= lowbit(x);
		return ans;
	}
	
	il void clear() {
		rep1(i, 0, n) sum[i] = 0;
	}
} T[15];

int main() {
	read(n, m); rer(i, 1, n, a); ++m;
	rep1(i, 0, n) rep1(j, 0, m) f[i][j] = 0;
	rep1(i, 1, n) rep1(j, 1, min(m, i)) {
			if (j == 1) f[i][j] = 1;
			else f[i][j] = T[j - 1].query(a[i] - 1);
			T[j].add(a[i], f[i][j]);
	} ll ans = 0;
	rep1(i, 1, n) ans += f[i][m];
	printf("%lld\n", ans);
	rout;
}
```

---

## 作者：Arghariza (赞：0)

有个显然的 $dp$：令 $f_{i,j}$ 为前 $i$ 个数中取出末尾为 $i$ 的并且长度为 $j$ 的上升子序列的个数。

那么有 $f_{i,j}=\sum\limits_{k=1}^{i-1}[a_k<a_i]f_{k,j-1}$，暴力转移 $O(n^2)$，考虑数据结构优化。

你想到了优化最长上升子序列的做法，于是你考虑维护 $k+1$ 个权值树状数组，第 $i$ 个表示 $f$ 第二维 为 $i$ 时，以每个权值结尾并且长度为 $i$ 的上升子序列总数。

于是查询的时候对于 $f_{i,j}$ 只需要在第 $j-1$ 个树状数组中查询 $1$ 到 $a_i-1$ 的上升子序列总数即可。时间复杂度 $O(kn\log n)$。

最后的答案即 $ans=\sum\limits_{i=1}^{n}f_{i,k+1}$。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 1e5 + 100;
int n, k, a[maxn], tr[15][maxn], dp[maxn][15];

int lowbit(int x) { return x & (-x); }
void modify(int x, int y, int id) { for (int i = x; i <= n; i += lowbit(i)) tr[id][i] += y; }
int query(int x, int id) { int res = 0; for (int i = x; i; i -= lowbit(i)) res += tr[id][i]; return res; }

signed main() {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) {
		modify(a[i], 1, 1), dp[i][1] = 1;
		for (int j = 2; j <= k + 1; j++) {
			dp[i][j] = query(a[i] - 1, j - 1);
			modify(a[i], dp[i][j], j);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans += dp[i][k + 1];
	write(ans);
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

容易想到 dp：定义 $dp_{i,j}$ 表示前 $i$ 个中长度为 $j$ 的严格最长公共子序列的数量，易得：$dp_{i,j}=\sum\limits_{k=1}^idp_{k,j-1}(a_k<a_i)$，时间复杂度 $O(n^2k)$，TLE。

我们可以考虑值域树状数组优化：用值域维护 $a_k<a_i$ 的信息，那么我们可以用一次 $O(\log n)$ 的树状数组代替 $O(n)$ 的枚举。

时间复杂度 $O(nk\log n)$。
```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&-x
using namespace std;
const int maxn=1e5+5;
inline int read(){
    int res=0,f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        res=(res<<1)+(res<<3)+(ch^'0');
        ch=getchar();
    }
    return f?-res:res;
}
int T,n,m,tot=1,sum,a[maxn],b[maxn],dp[maxn][15],c[15][maxn];
inline int ask(int k,int x){
	int s=0;
	for(;x;x-=lowbit(x))
		s+=c[k][x];
	return s;
}
inline void add(int k,int x,int y){
	for(;x<=n;x+=lowbit(x))
		c[k][x]+=y;		
}
unordered_map<int,int> mp;
signed main(){
	n=read(),m=read()+1;
	for(int i=1;i<=n;++i)
		b[i]=a[i]=read();
	sort(b+1,b+n+1);
	mp[b[1]]=1;
	for(int i=2;i<=n;++i)
		if(b[i]!=b[i-1])
			mp[b[i]]=++tot;
	for(int i=1;i<=n;++i){
		a[i]=mp[a[i]]; 
		dp[i][1]=1;
	} 
	for(int j=2;j<=m;++j)
		for(int i=1;i<=n;++i){
			dp[i][j]=ask(j-1,a[i]-1);
			add(j-1,a[i],dp[i][j-1]);
		}
	for(int i=m;i<=n;++i)
		sum+=dp[i][m];
	printf("%lld\n",sum);
	return 0;
}
```

---

## 作者：_lxy_ (赞：0)

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF597C-Solution.html)
### 题意

略。

### 分析

一眼望去发现是 dp。容易想到状态 $dp_{i,j}$ 表示以第 $i$ 位为结尾长度为 $j$ 的严格上升子序列个数，转移方程为：
$$
dp_{i,j}=\sum\limits_{a_k<a_i \vee k<i} dp_{k,j-1}
$$
但是这样做的时间复杂度为 $\mathcal{O}(n^2m)$，显然会 TLE，因此考虑优化：

可以想到把 dp 值放到树状数组中，这样转移时就不用再枚举一重 $k$ 了，可以开 $n$ 个树状数组，$tr_i$ 存严格上升子序列长度为 $i$ 的 dp 值。这样转移时就可以把时间复杂度降为 $\mathcal{O}(\log_2n)$，总时间复杂度 $\mathcal{O}(nm\log_2n)$。

### 代码

```cpp
#define int long long
const int MAXN=1e5+7;
int T,n,m,a[MAXN],b[MAXN],t,tr[17][MAXN];
inline int lowbit(int x){return x&(-x);}
void update(int x,int k,int p){for(;x<=n;x+=lowbit(x)) tr[p][x]=(tr[p][x]+k);}
int query(int x,int p)
{
	int res=0;
	for(;x;x-=lowbit(x)) res+=tr[p][x];
	return res;
}
signed main()
{
    int i,j;
    qread(n,m);m++;
    for(i=1;i<=n;i++) qread(a[i]);update(1,1,0);
    for(i=1;i<=n;i++)
    {
        if(a[i]==1) 
        {
            update(1,1,1);
            continue;
        }
        for(j=1;j<=m;j++)
        {
            int tmp=query(a[i]-1,j-1);
            update(a[i],tmp,j);
        }
    }
    printf("%lld\n",query(n,m));
    return 0;
}
```



---

## 作者：Plozia (赞：0)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/116571049)

这道题属于数据结构优化 DP 题，一般的题目大体上分 4 步：

1. 写出转移方程。
2. 观察整理式子。
3. 数据结构优化。
4. 一些细节处理。

------

1. 写出转移方程

设 $f_{i,j}$ 表示以 $i$ 为末尾，长度为 $j$ 的最长上升子序列的方案数，那么有转移方程：

$$f_{i,j}=\sum_{k=1}^{i-1}f_{k,j-1}(a_k<a_i)$$

复杂度 $O(n^2k)$，初值为 $f_{i,1}=1|i \in [1,n]$。

2. 观察整理式子

没法整理qwq

3. 数据结构优化

观察 $\sum\limits_{k=1}^{i-1}f_{k,j-1}(a_k<a_i)$，我们发现：我们需要在 $[1,i-1]$ 中查询所有 $a_k<a_i$ 的 $k$ 的 $f_{k,j-1}$ 的和~~好绕口~~。

那么这个仍然可以使用线段树优化。

我们建立 $k$ 棵线段树（这里的 $k$ 是题中的 $k$ 加 1），第 $i$ 棵线段树专门用来维护 $f_{j,i}|j \in [1,n]$。

**注意线段树是值域线段树**。

然后对于第 $i$ 个位置的数，转移完之后在 $a_i$ 上单点加上 $f_{i,j}$ 即可，而转移可以采用线段树的区间查询。

4. 一些细节处理

没啥细节qwq

代码：

```cpp
/*
========= Plozia =========
    Author:Plozia
    Problem:CF597C Subsequences
    Date:2021/5/9
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 10;
int n, k, a[MAXN];
LL f[MAXN][15];
struct node
{
    int l, r;
    LL val;
}tree[15][MAXN << 2];

int read()
{
    int sum = 0, fh = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
    return sum * fh;
}

void build(int p, int Tag, int l, int r)
{
    tree[Tag][p].l = l, tree[Tag][p].r = r;
    if (l == r) { tree[Tag][p].val = 0; return ; }
    int mid = (l + r) >> 1;
    build(p << 1, Tag, l, mid); build(p << 1 | 1, Tag, mid + 1, r);
    tree[Tag][p].val = tree[Tag][p << 1].val + tree[Tag][p << 1 | 1].val;
}

void add(int p, int Tag, int x, LL d)
{
    if (tree[Tag][p].l == tree[Tag][p].r && tree[Tag][p].l == x) { tree[Tag][p].val += d; return ; }
    int mid = (tree[Tag][p].l + tree[Tag][p].r) >> 1;
    if (x <= mid) add(p << 1, Tag, x, d);
    else add(p << 1 | 1, Tag, x, d);
    tree[Tag][p].val = tree[Tag][p << 1].val + tree[Tag][p << 1 | 1].val;
}

LL ask(int p, int Tag, int l, int r)
{
    if (tree[Tag][p].l >= l && tree[Tag][p].r <= r) return tree[Tag][p].val;
    int mid = (tree[Tag][p].l + tree[Tag][p].r) >> 1; LL val = 0;
    if (l <= mid) val += ask(p << 1, Tag, l, r);
    if (r > mid) val += ask(p << 1 | 1, Tag, l, r);
    return val;
}

int main()
{
    n = read(), k = read() + 1;
    for (int i = 1; i <= n; ++i) a[i] = read();
    for (int i = 1; i <= n; ++i) f[i][1] = 1;
    for (int i = 1; i <= k; ++i) build(1, i, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        add(1, 1, a[i], 1);
        for (int j = 2; j <= k; ++j) { f[i][j] = ask(1, j - 1, 1, a[i] - 1); add(1, j, a[i], f[i][j]); }
    }
    LL ans = 0;
    for (int i = 1; i <= n; ++i) ans += f[i][k];
    printf("%lld\n", ans); return 0;
}
```

---

## 作者：shao0320 (赞：0)

#### CF597C Subsequences

水紫。

由于$k$规模巨小，因此考虑算一下以每个点为终点的长度为$i$的子序列方案数。

那就是在前边找一个点使得其权值小于该点，然后查询其长度为$i-1$的子序列的方案数。

开$k+1$个树状数组，树状数组的下标记录值域，即$T[i][j]$表示到目前为止长度为$i$的子序列，最后一个位置的权值为$j$的方案数，维护前缀和即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 200005
#define lowbit(x) x&-x
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,K,ans[N],anss,a[N];
struct BIT
{
	int c[N];
	void modify(int x,int k){for(;x<=n;x+=lowbit(x))c[x]+=k;}
	int query(int x){int res=0;for(;x;x-=lowbit(x))res+=c[x];return res;}
}t[15];
signed main()
{
	n=read();K=read()+1;
	for(int i=1;i<=n;i++)a[i]=read();
	if(K==1)return printf("%d\n",n),0;
	for(int i=1;i<=n;i++)
	{
		for(int j=K;j>=2;j--)
		{
			int now=t[j-1].query(a[i]);
			if(j==K)ans[i]=now;
			t[j].modify(a[i],now);
		}
		t[1].modify(a[i],1);
	}
	for(int i=1;i<=n;i++)anss+=ans[i];
	//for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	//puts("");
	printf("%lld\n",anss);
}
```





---

## 作者：MuYC (赞：0)

### 前言
这是一道数据结构优化 $dp$ 的入门题，但是也很有意思。

前置知识：线段树维护前缀和（区间加法，单点求值）/树状数组也可

（没人写线段树题解？线段树党来了）

### 题解正文

题目大意：

给定一个长度为 $n$ 的序列 $A$ 以及一个数 $k$ ，求其长度为 $k + 1$ 的上升子序列的数量。

$n <= 10^5,1 <= A_i <= n,0 <= k <= 10$

思路:

首先我们看到本题，不难想到经典问题：最长上升子序列。（但是其实关系不大）

在解**最长上升子序列**的时候我们一般用的是 $nlogn$ 的算法，但是实际上还存在一种被不屑的 $n^2$ 求最长上升子序列的方法。

对于 $n^2$ 的方法稍加魔改变形就可以得到本题的 $n^2$ 做法。

$n ^ 2$ $dp$ :

设置状态: 

$dp[i][j]$ 表示前 $i$ 个数中，以 $i$ 结尾的长度为 $j$ 的上升子序列的数量。

转移方程:

$dp[i][j] = \sum_{l = 1}^{l = min(i,k+1)}{dp[l][j - 1](if:A[i] > A[l])}$

边界设置:

$dp[i][1] = 1$ 

最终答案即: $\sum_{i = 1}^{i = n}{dp[i][k + 1]}$

上面这个方法我们需要枚举 $i$ ，以及子序列长度 $j$ ，还有枚举 $i$ 前面的所有 $dp[l][j - 1]$，总复杂度是 O$(n^2k)$ 的，这是显然过不了本题的。

思考如何优化。

不难发现 $dp[i][j]$ 只与 $dp[l < i][j - 1]$ 有关，可以类似于前缀和处理，但是前缀和每次修改需要 O$(n)$ 的复杂度，行不通。

于是考虑用 **线段树/树状数组** 优化这个过程。

将 $A[i]$ 看作是前缀和的下标，然后前缀和对应的值就是 $dp[i][j]$，然后线段树维护前缀和即可。

因为是按照 $1$ ~ $n$ 的顺序进行 $dp$ 的，我们很容易边 $dp$ 转移状态边修改，从而满足 $l < i$，于是就可以大胆的采用 $11$ 棵线段树维护整个 $dp$ 过程，从而使得整个过程都满足 $A[l] < A[i]$。

此题完结。

细节可见代码：

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
char buf[1 << 22] , *p1 = buf , * p2 = buf;(kaui)
#define int long long
#define mid ((L[x] + R[x]) >> 1)
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1 << 21 , stdin) , p1 == p2) ? EOF : *p1++)
const int MAXN = 1e5 + 50;
int n,k,A[MAXN];
long long dp[MAXN][15],Ans;

inline int read() {
	int x = 0 , flag = 1;
	char ch = getchar();
	for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
	for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}

struct SegmentTree {//11棵线段树都写一遍不现实，用结构体就可以封装了
	int L[MAXN * 4],R[MAXN * 4],sum[MAXN * 4],laz[MAXN * 4];
	
	void build(int x,int l,int r) {//建树
		L[x] = l , R[x] = r; 
		laz[x] = sum[x] = 0;
		if(l == r) return ;
		build(x << 1 , l , mid);
		build(x << 1 | 1  , mid + 1 , r);
	}
	
	void ad(int x,int k) {//修改 
		laz[x] += k , sum[x] += k; 
		return ;
	}
	
	void pushdown(int x) {//下传标记
		if(laz[x] == 0) return ;
		ad(x << 1 , laz[x]);
		ad(x << 1 | 1 , laz[x]);
		laz[x] = 0;
		return ;
	}
	
	int Get(int x,int pos) {//单点求值
		if(L[x] == pos && R[x] == pos) return sum[x];
		pushdown(x);
		if(pos <= mid) return Get(x << 1 , pos);
		else return Get(x << 1 | 1, pos);
	}
	
	void change(int x,int l,int r,int k) {//区间修改
		if(L[x] >= l && R[x] <= r) {ad(x,k) ; return ;}
		if(l <= mid) change(x << 1 , l , r , k);
		if(r  > mid) change(x << 1 | 1 , l , r , k);
		return ;
	}
} T[12];

signed main() {
	n = read() , k = read();
	for(int i = 1 ; i <= n ; i ++) A[i] = read(),dp[i][1] = 1;
	if(k == 0) { cout << n ; return 0;}
	for(int i = 1 ; i <= k + 1 ; i ++) T[i].build(1, 1, n);
	for(int i = 1 ; i <= n ; i ++) {
		for(int j = 2 ; j <= min(i, k + 1) ; j ++)
		dp[i][j] += T[j - 1].Get(1,A[i]) ;//获得答案
		for(int j = 1 ; j <= min(i, k + 1) ; j ++)
		T[j].change(1,A[i] + 1 , n , dp[i][j]);//每次都修改
		Ans += dp[i][k + 1];//统计答案
	}
	cout << Ans;
	return 0;
}
```

---

