# Maximum Reduction

## 题目描述

给定一个长为 $n$ 的数组 $a$ 和一个数 $k$（$2\le k\le n$），数组从 $1$ 开始编号。

请阅读下列程序伪代码，并输出 $z(a,k)$ 对 $10^9+7$ 取模后的值。

**z 函数的大意：**

- 在数组 $a$ 中，记录下从左到右每一段长度为 $k$ 的区间内的最大值。

- 返回的是这些最大值之和，加上这些最大值从左到右排列形成的新的数组 $b$ 的 $z(b,k)$ 的值，即这是个递归函数。

- 如果数组长度比 $k$ 小，返回 $0$。

## 样例 #1

### 输入

```
3 2
9 1 10
```

### 输出

```
29
```

## 样例 #2

### 输入

```
5 3
5 8 7 1 9
```

### 输出

```
34
```

# 题解

## 作者：Winniechen (赞：7)

这大概是一种非常套路的题，比如说Coci2015 Norma

这个题比那道题简单多了，我们考虑使用分治算法解决这个问题。

每次，将区间分成两部分，$l\sim m$以及$m+1\sim r$并递归下去。

那么，我们只需要考虑跨过$m$的贡献。

接下来，我们用左区间的后缀最大值，以及前缀最大答案即可。

剩下的东西就可以直接枚举右区间，然后左区间用一个指针扫一遍即可。

每次的贡献是：$ maxx\times t\%mod+s[max(i-(u*(k-1)),l-1)] $

其中，$s$表示前缀答案和，$maxx$表示$m+1\sim i$的最大值

附上代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;
#define N 1000005
#define ll long long
#define mod 1000000007
int n,k,lg[N];ll ans,a[N],mx[N],s[N];
void solve(int l,int r)
{
    if(r-l+1<k)return ;int m=(l+r)>>1;mx[m]=a[m];s[m]=0;s[l-1]=0;
    for(int i=m-1;i>=l;i--)mx[i]=max(mx[i+1],a[i]),s[i]=0;
    for(int i=l;i<=m;i++)
    {
        int x=i-k+1;if(x>=l)s[i]=s[x];
        s[i]+=mx[i];s[i]%=mod;
    }ll maxx=a[m+1];
    for(int i=m+1,j=m;i<=r;i++,maxx=max(maxx,a[i]))
    {
        if(i-l+1<k)continue;
        while(j>=l&&mx[j]<maxx)j--;
        int x=i-j,t=(x-1)/(k-1),u=t+1;t-=(i-m-1)/(k-1);
        ans+=maxx*t%mod+s[max(i-(u*(k-1)),l-1)];ans%=mod;
    }solve(l,m);solve(m+1,r);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    solve(1,n);
    printf("%lld\n",ans);
}
```

---

## 作者：hwk0518 (赞：5)

这道题是可以做到$O(N)$的。

首先我们发现，题目让我们求的就是：

$max(1 \to k)+max(2 \to k+1)+...+max(n-k+1 \to n)+$

$max(1 \to 2k-1)+...+max(n-2k+2 \to n)+$

$max(1 \to 3k-2)+...+max(n-3k+3 \to n)+...$

然后我们考虑每一个数对几个区间有贡献。

先求出$a_i$左边所有比它大的数中最右的一个，记位置为$j$，再求出$a_i$右边所有比它大的数中最左的一个，记位置为$k$。如果没有，左边位置就记为$0$，右边位置就记为$n+1$。这可以利用单调栈在$O(n)$的时间内求出。

所有最大值取$a_i$的区间要满足两个条件：

$(1)$ 不能跨过$j$和$k$，即被区间$[j+1,k-1]$包含；

$(2)$ 必须跨过$i$，即不被区间$[j+1,i-1]$和$[i+1,k-1]$包含。

现在我们来求有多少个区间被$[l,r]$包含。容易发现，所有长度为$r-l+1$的区间答案都相等。设区间大小为$t$。

长度为$k$的区间有$t-k+1$个；

长度为$2k$的区间右$t-2k+2$个；

...

记$p=\frac{t}{k-1}$，则答案为：

$t*p-(1+...+p)*k+(1+...+p)$

$=t*p-\frac{p(p+1)}{2}*k+\frac{p(p+1)}{2}$

$=t*p-\frac{p(p+1)}{2}*(k-1)$

细节上，如果两数相等，我们强制右边的数更大。

总时间复杂度$O(n)$。

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int N=1e6+5;
const int mod=1e9+7;
int n,k,a[N],l[N],r[N];
int que[N],top;

void init()
{
	scanf("%d%d",&n,&k);int i;
	for(i=1;i<=n;++i) scanf("%d",&a[i]);
}

void prework()
{
	int i;a[0]=a[n+1]=1e9+7;
	
	top=1,que[top]=0;
	for(i=1;i<=n;++i)
	{
		while(a[que[top]]<=a[i]) --top;
		l[i]=que[top]+1;
		que[++top]=i;
	}
	
	top=1,que[top]=n+1;
	for(i=n;i;--i)
	{
		while(a[que[top]]<a[i]) --top;
		r[i]=que[top]-1;
		que[++top]=i;
	}
}

int calc(int t)
{
	int p=t/(k-1);
	int ret=1LL*t*p%mod;
	ret-=(1LL*p*(p+1)>>1)%mod*(k-1)%mod;
	if(ret<0) ret+=mod;
	return ret;
}

void work()
{
	int i,ans=0;
	for(i=1;i<=n;++i)
	{
		int sz=r[i]-l[i]+1,lsz=i-l[i],rsz=r[i]-i;
		int nw=calc(sz);
		nw-=calc(lsz);if(nw<0) nw+=mod;
		nw-=calc(rsz);if(nw<0) nw+=mod;
		ans+=1LL*nw*a[i]%mod;if(ans>=mod) ans-=mod;
	}
	printf("%d\n",ans);
}

int main()
{
	init();prework();work();
	return 0;
}

```

---

## 作者：w4p3r (赞：5)

### 一丶思路

我们先考虑一个只有$0,1$的序列如何求解答案，如果能求解这个问题显然可以拓展到其他情况上。

设一个长度为$n$全为$1$的序列的答案为$s_n$，则显然有$DP$式：

1.$s_i=0(i \le k)$

2.$s_i=s_{i-k+1}+(i-k+1) \   (i \ge k)$

设这个序列所有**连续的**全等于$0$的字串的长度分别是$l_1,l_2...,l_m$，那么显然$ans=s_n-\sum_{i=1}^{m}s_{l_{i}}$。

（因为是求max，只要包含$1$就对答案有贡献，只需要减去完全为$0$的区间即可）

然后把这个问题扩展到所有情况上。设置一个当前阈值$v$，若$a_i \ge v$则假设$a_i=1$，否则假设$a_i=0$。

考虑$v$变成$v+1$时，我们只需把所有$a_i=v$的点变成$0$，同时维护$\sum_{i=1}^{m}s_{l_{i}}$，并让总答案加上当前序列答案即可。

在总值域较大时离散化即可，不再赘述，时间复杂度$O(nlogn)$

### 二丶代码

```cpp
//W4P3R
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register int
#define fr first
#define sd second
#define pa pair<int,int>
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define N 1000010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline int read()
{
	char ch=getchar();
	int s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
const int mod=1e9+7;
inline int Z(int x){return x>=mod?x-mod:x;}
inline int lowbit(int x){return x&(-x);}
int n,a[N],w[N],k,s[N];
int p[N],len;vector<int>v[N];
int fa[N],L[N],R[N],sz[N];
int nowans,ans;
/*
nowans:sn-sigma(sli)的值
ans:总答案
*/
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
int main()
{
	//ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),k=read();
	FOR(i,1,n)a[i]=p[i]=read(),w[i]=1;//一开始假设所有点都是1
	sort(p+1,p+n+1);len=unique(p+1,p+n+1)-p-1;//离散化
	FOR(i,1,n)
	{
		a[i]=lower_bound(p+1,p+len+1,a[i])-p;
		v[a[i]].pb(i);
	}
	FOR(i,k,n)s[i]=Z(s[i-k+1]+(i-k+1));
	nowans=s[n];
	FOR(i,1,n)fa[i]=L[i]=R[i]=i,sz[i]=1;//用并查集维护
	w[0]=w[n+1]=1;
	FOR(i,1,len)
	{
		ans=Z(ans+1LL*(p[i]-p[i-1])*nowans%mod);
		for(int x:v[i])
		{
			int l=x,r=x;
			if(!w[x-1]){nowans=Z(nowans+s[sz[find(x-1)]]);l=L[find(x-1)];fa[find(x-1)]=x;}
			if(!w[x+1]){nowans=Z(nowans+s[sz[find(x+1)]]);r=R[find(x+1)];fa[find(x+1)]=x;}
			L[x]=l,R[x]=r,sz[x]=r-l+1;nowans=Z(nowans+mod-s[sz[x]]);w[x]=0;//维护nowans
		}
	}
	printf("%d\n",ans);
	return 0;
}
//gl


```

**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**



---

## 作者：Fido_Puppy (赞：2)

$$\texttt{Preface}$$

![](https://z3.ax1x.com/2021/05/30/2VNbwQ.png) orz [Tx_Lcy](https://www.luogu.com.cn/user/253608) 认为显然的 $\Theta(n)$ 做法，只会 $\Theta(n \log n)$ 的小蒟蒻瑟瑟发抖。

$$\texttt{Description}$$

[Maximum Reduction](https://www.luogu.com.cn/problem/CF1037F)

$$\texttt{Solution}$$

我们设 $ans_i$ 表示序列 $a$ 中所有连续 $i$ 个数的最大值之和。

题目让我们求的就是 $ans_k + ans_{2k - 1} + ans_{3k - 2} + \cdots$。

所以我们只需要把 $\forall i \in [1, n], ans_i$ 求出来即可。

我们考虑用单调栈对于每个 $i$ 求出 $L_i$ 和 $R_i$，分别表示左边第一个 $> a_i$ 的数的位置和右边第一个 $\ge a_i$ 的数的位置。

至于一个是 $>$，一个是 $\ge$，是因为有如下情况：

`1 1 4 5 1 4 1 9 1 9 8 1 0`

这段区间中最大值 $9$ 出现了两次，若是两个都是 $\ge$，则这段区间会被重复计算两次。

然后显然有：

$$\forall l \in (L_i, i], r \in [i, R_i), \max_{k = l}^r \{a_k\} = a_i$$

然后我们考虑枚举左端点**或者**右端点，这里以枚举左端点为例，那么右端点的取值为 $i \sim R_i - 1$，所以左端点为 $j$ 时，区间的长度范围为 $i - j + 1 \sim R_i - j$，我们就可以利用差分在 $\Theta(1)$ 的时间复杂度内对 $ans$ 数组中区间 $[i - j + 1, R_i - j]$ 加上 $a_i$；右端点同理。

所以我们可以启发式分裂，每次贪心选择左右两端中比较小的一段去枚举，时间复杂度 $\Theta(n \log n)$。

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int mod = 1e9 + 7;
int n, k, a[1000005], L[1000005], R[1000005], ans[1000005];
stack <int> sta;
template <typename T> void Myclear(T & q) { T e; q.swap(e); }
int main() {
	ios :: sync_with_stdio(0), cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	Myclear(sta), sta.push(0);
	for (int i = 1; i <= n; ++i) {
		while (sta.top() && a[ sta.top() ] < a[i]) sta.pop();
		L[i] = sta.top(), sta.push(i);
	}
	Myclear(sta), sta.push(n + 1);
	for (int i = n; i; --i) {
		while (sta.top() <= n && a[ sta.top() ] <= a[i]) sta.pop();
		R[i] = sta.top(), sta.push(i);
	}
	auto add = [&] (int &x, int v) -> void {
		x += v; if (x >= mod) x -= mod;
	};
	for (int i = 1; i <= n; ++i) {
		auto update = [&] (int l, int r, int c) -> void {
			if (r == n) add(ans[l], c);
			else add(ans[l], c), add(ans[ r + 1 ], mod - c);
		};
		if (i - L[i] < R[i] - i) {
			for (int j = L[i] + 1; j <= i; ++j) {
				update(i - j + 1, R[i] - j, a[i]);
			}
		}
		else {
			for (int j = i; j < R[i]; ++j) {
				update(j - i + 1, j - L[i], a[i]);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		add(ans[i], ans[ i - 1 ]);
	}
	int sum = 0;
	for (int i = k; i <= n; i += k - 1) {
		add(sum, ans[i]);
	}
	cout << sum << '\n';
	return 0;
}
```

$$\texttt{Thanks for watching!}$$

---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1037F)

## 思路

较为傻逼的 $\verb!*2500!$。

怎么会有人去写分治啊，$\mathcal O(n)$ 做法不是很显然吗？

先找找规律，题目就是要让我们求所有区间 $[x,x+k)$ 以及 $[x,x+k+(k-1)+(k-1)+...)$ 的和。

由于是个 $\sum$，可以分离贡献，考虑每个数对答案的贡献。

先两个单调栈求出 $\rm pre_i,nxt_i$，然后先计算 $[x,x+k)$ 的贡献，可以直接来，非常简单。

接下来计算 $[x,x+k+(k-1)+...)$ 的贡献，相当于一段连续的区间除以某个数的和，我们要 $\mathcal O(1)$ 算出。

考虑这个 $k$ 是每个都要加的，故没有影响，答案变为一段连续的区间除以 $k-1$ 的和，发现范围很小，可以前缀和直接来，那么就结束了。

单调栈出现相同的数以及前缀和的边界要稍微判一下，不过都是小问题。

话说这是怎么评上这个难度的，感觉思路很显然啊。

## 码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e6+10;
int const mod=1e9+7;
int a[N],nxt[N],pre[N],s[N],sum[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,k;cin>>n>>k;
    int ans=0,top=0;
    for (int i=1;i<=n;++i) cin>>a[i];
    for (int i=1;i<=n;++i){
        while (top && a[i]>a[s[top]]) nxt[s[top]]=i-1,--top;
        s[++top]=i;nxt[i]=n;
    }
    top=0;
    for (int i=n;i>=1;--i){
        while (top && a[i]>=a[s[top]]) pre[s[top]]=i+1,--top;
        s[++top]=i;pre[i]=1;
    }
    for (int i=1;i<=n;++i){
        if (nxt[i]-k+1<pre[i]) continue;
        ans+=(min(nxt[i]-k+1,i)-max(i-k+1,pre[i])+1)*a[i]%mod;
        ans%=mod;
    }
    for (int i=1;i<=2*n;++i) sum[i]=sum[i-1]+(i/(k-1));
    for (int i=1;i<=n;++i){
        int res=sum[max(0ll,nxt[i]+1-k-pre[i])]-sum[max(0ll,nxt[i]+1-k-min(i,nxt[i]+1-k)-1)];
        res-=sum[max(0ll,i-k-pre[i])]-sum[max(0ll,i-k-min(i,i-k)-1)];res%=mod;res+=mod;res%=mod;
        ans+=res*a[i]%mod;ans%=mod;
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：bsdsdb (赞：1)

题意：现有函数：

```text
function z(a : array, k : int) -> int:
	if (|a| < k):
		return 0
	b : empty array
	for i in [1, |a| - k + 1]:
		append \max_{j=i}^{i+k-1}a_i to the end of b
	return \sum b + z(b, k)
```

给定 $\{a_i\}_{i=1}^n$ 和 $k$，求 $z(a,k)$。

考虑一个最大数对答案的贡献：

![](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/xcki7y4b)

设最大数位置为 $X$，令 $a=:b+a_X+c$，$X$ 在所有迭代的 $a$ 中出现了 $d$ 次，那么 $z(a,k)=z(b,k)+z(c,k)+(d-1)X$。$b$ 和 $c$ 不用复制一遍，指针 + 长度即可。递归要搞 $\Omicron(n)$ 次，接下来 $\Omicron(1)$ 计算 $d$：

$$
d=\sum_{i=1}^{\frac n{k-1}}(\min(\blue b,\green g)-\max(\red r,\orange o)+1)
$$

（为了方便，所有除法默认下取整）

考虑将四条线的解析式写出来：

$$
\blue b=n-(i-1)(k-1)\\
\green g=X\\
\red r=X-(i-1)(k-1)\\
\orange o=1
$$

令 $i\gets i-1,k\gets k-1$：

$$
\begin{aligned}
d=&\sum_{i=0}^{\frac n{k-1}-1}(\min(\blue b,\green g)-\max(\red r,\orange o)+1)\\
=&\sum_{i=0}^{\frac n{k-1}-1}(\min(\blue{n-ik},\green X)-\max(\red {X-ik},\orange 1)+1)\\
=&\blue\sum_{i\le\frac n{k-1}-1,\blue{n-ik}<\green X}(n-ik)+\green\sum_{i\le\frac n{k-1}-1,\blue{n-ik}\ge\green X}X\\
&-\red\sum_{i\le\frac n{k-1}-1,\red{X-ik}\ge\orange1}(X-ik)-\orange\sum_{i\le\frac n{k-1}-1,\red{X-ik}<\orange{1}}1\\
=&\blue\sum_{i=\frac{n-X}k+1}^{\frac n{k-1}-1}(n-ik)+\green\sum_{i=0}^{\frac{n-X}k}X-\red\sum_{i=0}^{\frac{X-1}k}(X-ik)-\orange\sum_{i=\frac{X-1}k+1}^{\frac n{k-1}-1}1
\end{aligned}
$$

高斯求和即可。复杂度 $\Omicron(n\log n)$，瓶颈在于 st 表或者线段树求出一个区间内最值的索引。

---

## 作者：Nightingale_OI (赞：1)

## CF1037F

### 大意

给定数组 $a_n$，求 $a$ 的所有长度为 $t(k-1)+1\ (t\in \rm{N^+})$ 的区间的最大值之和。

这或许是一级结论。

### 思路

由于 $a_i$ 可能重复，于是钦定相等时左边的数更大。

先两次单调栈求出对于每个 $i$，求出一个极大的区间 $[L_i,R_i]$ 使得 $i\in[L_i,R_i]$ 且该区间最大值为 $a_i$。

那么 $a_i$ 的贡献次数就是 $[L_i,R_i]$ 内长度合法且包含 $i$ 的区间数量。

这是不好算的，考虑容斥，按 $a_i$ 从小到大枚举 $i$。

可以先算出 $b_i$ 表示 $[L_i,R_i]$ 内长度合法的区间数量（代码 `clac` 函数，不多赘述）。

有一个很好的性质，$\forall_{j\in[L_i,R_i]}a_j\leq a_i,[L_j,R_j]\subset[L_i,R_i]$，树状数组维护：

$$b_i'=b_i-\sum_{j=L_i}^{R_i}b_j'$$

让答案累加上 $a_i\times b_i'$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
const int N=1010101,mo=1e9+7,m2=5e8+4;
struct Kazemaru{
	int c[N];
	inline void add(int x,int y){for(int i=x;i<=n;i+=-i&i)c[i]=(c[i]+y)%mo;}
	inline int sum(int x,int y=0){for(int i=x;i;i-=-i&i)y=(y+c[i])%mo;return y;}
	inline int ask(int l,int r){return (sum(r)-sum(l-1)+mo)%mo;}
}T;
int a[N],b[N],L[N],R[N],p[N];
inline int clac(int x,int k){return (x-k+x-(x/k)*k)%mo*(x/k)%mo*m2%mo;}
inline int cmp(int x,int y){return a[x]==a[y]?x>y:a[x]<a[y];}
signed main(){
	cin>>n>>m;
	f(i,1,n)scanf("%lld",&a[i]);
	a[0]=a[n+1]=1e15;
	b[s=1]=0;
	f(i,1,n){
		while(a[b[s]]<a[i])--s;
		L[i]=b[s]+1;b[++s]=i;
	}
	b[s=1]=n+1;
	g(i,n,1){
		while(a[b[s]]<=a[i])--s;
		R[i]=b[s]-1;b[++s]=i;
	}
	s=0;
	f(i,1,n)b[p[i]=i]=clac(R[i]-L[i]+1,m-1);
	sort(p+1,p+n+1,cmp);
	f(i,1,n){
		l=p[i];
		T.add(l,b[l]=(b[l]+mo-T.ask(L[l],R[l]))%mo);
		s=(s+a[l]*b[l])%mo;
	}
	printf("%lld\n",s);
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
不难的数数。

摘自[数数数](https://www.luogu.com.cn/training/627660)。
## 思路分析
首先考虑对整个序列整体考虑。

然后发现因为我们不知道每次去掉的是哪几个，也就没法高效维护操作一次之后对整个序列的影响。

这就很难办。

所以这个想法大概是错完了。

不妨把每个数拆开考虑，考虑一个数 $a_i$ 在整个操作过程中总共出现了多少次。

因为我们的操作是 $k$ 个取 $\max$，所以一个数消失必然是被一个比他大的数顶掉了。

那么考虑一下数 $i$ 会被哪个数顶掉呢？

肯定是他左边/右边第一个比他大的数。

左右两边不断扩散过来，最后就会把 $i$ 顶掉。

手玩一下这个过程，比如我们用 $x$ 表示 $a_i$，$y$ 表示比 $a_i$ 大的数，$z$ 表示比 $x$ 小的数，且令 $k=3$，大致过程就像这样：

$\color{red}y\color{black},z,z,z,z,x,z,z,z,\color{red}y$

$\color{red}y\color{black},z,z,x,x,x,z,\color{red}y$

$\color{red}y\color{black},x,x,x,x,\color{red}y$

$\color{red}y\color{black},x,x,\color{red}y$

$\color{red}y,y$

我们观察到最前面的 $y$ 相当于是没动的，只是 $x$ 在不断的吃掉 $z$ 往前跑。

观察 $z$ 的变化，我们就会发现两边的 $z$ 都是以倒三角型收缩下来的。

而对于整个由 $y$ 围成的图形，也是一个大的倒三角。

这个倒三角他的最上面一行长度我们是知道的，而且公差为 $k-1$ 我们也是知道的。

直接等差数列求和就可以容斥出 $x$ 的数量了。

具体的来说，$z$ 大概长成：

$y,\color{red}{z,z,z}\color{black}{,x}$

$y,\color{red}{z}\color{black}{,x,x,x}$

类似于这样的一个公差为 $k-1$ 的等差数列，右边同理。

而整个大三角形就是上文中的例子中的红框部分。

所以简单容斥就可以得到 $x$ 的数量了。

具体的假设第一行为 $x$ 个，且设 $t=\lfloor\frac{x}{k-1}\rfloor$，那么我们就有操作中出现的总数量为：

$$x\cdot t-\frac{t\cdot(t+1)\cdot(k-1)}{2}$$

按照式子和题意模拟一下就好了。

~~笑话之不会写单调栈挂了两发。~~
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=2e6+10,M=6e5+10,V=1e9+10,lim=1e6,LIM=1e12,LLIM=1e18,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,k,ans,a[N],l[N],r[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(long long x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='#'||c=='.'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline void calc(int len,int w,int op)
{
	int t=len/(k-1);
	ans=(ans+(op*(t*len-((t+1)*t>>1)*(k-1))%mod+mod)%mod*w%mod)%mod;
}
inline void solve()
{
	n=read(),k=read();for(int i=1;i<=n;i++) a[i]=read();
	stack<int>s;s.emplace(0);a[0]=a[n+1]=INF;
	for(int i=1;i<=n;i++)
	{
		while(!s.empty()&&a[s.top()]<=a[i]) s.pop();
		l[i]=s.top();s.emplace(i);
	}while(!s.empty()) s.pop();s.emplace(n+1);
	for(int i=n;i>=1;i--)
	{
		while(!s.empty()&&a[s.top()]<a[i]) s.pop();
		r[i]=s.top();s.emplace(i);
	}while(!s.empty()) s.pop();
	for(int i=1;i<=n;i++)
	{
		calc(i-l[i]-1,a[i],-1);calc(r[i]-i-1,a[i],-1);
		calc(r[i]-l[i]-1,a[i],1);
	}print(ans);
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：_l_l_ (赞：0)

讲一个不用脑子的做法

首先，我们称原数组记作 $f_0$，每计算一次区间 max，就记作 $f_i$。

样例二的 $f$：
```
5 8 7 1 9
8 8 9
9
```
然后明显的可以看出，对于每一个 $f_{i,j}$，它可以对 $f_{i+1,j'}(j-k<j'\leq j)$ 做出贡献，每一个数的值即为上方数的贡献 max。

我们把目光放在最大的一个数上，可以发现因为这个数是最大的，因此它将对下面所有可以做出贡献的数全部直接赋值了，而直观体验来看这就是一个区域赋值：如果位置 $p$ 有一个最大值，则对于所有 $f_{x,y}(y\leq p\land \frac{p-y}{k-1}\leq x)$，它的值一定是 $f_{0,p}$。

```
(k=3)
-------*-
-----***-
---*****-
-*******-
********-
```

再来看其他的区域，这些区域会受到左右的包夹，直到右边的数包夹到左边的数，中间这块区域才完全消失，无法继续做出贡献。

实现中，我们可以记录 中间碰到左边的迭代数，右边碰到中间的迭代数，右边碰到左边的迭代数，然后就可以使用等差数列求和解决问题。

求一个数的左右第一大于它的数可以随便拿单调栈上二分或其他做法，反正不会超时。

时间复杂度 $O(n\log_2 n)$（有可能 $O(n)$？）

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
long long calc(int l, int x, int r, int k) {
	// 一个数在位置 x，被 l 和 r 两面包夹的贡献
	l++; r--;
	long long ans = 0;
	int r2x = (r - x) / (k - 1) + 1; ans += 1ll * r2x * x;
	int r2l = (r - l) / (k - 1) + 1, x2l = (x - l) / (k - 1) + 1;
	ans += 1ll * (r - r2x * (k - 1) + r - (r2l - 1) * (k - 1)) * (r2l - r2x) / 2;
	ans -= 1ll * (x + x - (x2l - 1) * (k - 1)) * x2l / 2;
	ans -= 1ll * (r2l - x2l) * l;
	ans += r2l;
	return ans;
}
int stk[1000005], stka[1000005], top;
int a[1000005], lmax[1000005], rmax[1000005];
int main() {
	int n, k; scanf("%d %d", &n, &k);
	long long sm = 0;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), sm += a[i];
	stk[top = 0] = 0; stka[0] = 0x7fffffff;
	for (int i = 1; i <= n; i++) {
		lmax[i] = stk[upper_bound(stka, stka + top + 1, a[i], [](int a, int b) {return a > b;}) - stka - 1];
		while (top && a[i] >= a[stk[top]]) top--;
		stk[++top] = i; stka[top] = a[i];
	}
	stk[top = 0] = n + 1; stka[0] = 0x7fffffff;
	for (int i = n; i; i--) {
		rmax[i] = stk[lower_bound(stka, stka + top + 1, a[i], [](int a, int b) {return a > b;}) - stka - 1];
		while (top && a[i] >= a[stk[top]]) top--;
		stk[++top] = i; stka[top] = a[i];
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += calc(lmax[i], i, rmax[i], k) % 1000000007 * a[i];
		ans %= 1000000007;
	}
	printf("%lld\n", (ans + 1000000007 - sm % 1000000007) % 1000000007); return 0;
}
```

---

## 作者：赵悦岑 (赞：0)

## 题意

这道题定义了 $z(a,k)$，$b$ 为 $a$ 从左到右每一个长度为 $k$ 的区间的最大值，$z(a,k)=\sum b_i + z(b,k)$。显然，从 $k$ 个恰好覆盖 $[1,2k-1]$ 的区间中取最大值等价于 $[1,2k-1]$ 中的最大值，所以问题就转化为了求长度为 $t(k-1)+1,t \in \mathbb{N_{+}}$ 的所有区间的最大值的和。

## 分析

由于区间长度个数可以达到 $n$，所以不能枚举长度。这种很多区间的贡献和一般能想到分治，如果按最大值分很好分，但是会被卡，所以我们只能将区间分为两半。

每次将区间折半，层数是 $\log n$ 的，所以我们只需要线性地求出一段中跨过一个点的区间的最大值总和即可。考虑分为最大值在左边 $[l,mid]$ 和最大值在右边 $[mid+1,r]$ 的情况，假设最大值在左边，只要右边最大值不超过左边最大值即可。

而左边的区间扩大，最大值一定不比原来小，所以右边的上限也不比原来小，所以右区间大小关于左区间大小单调不降，即左端点左移时，右端点一定右移或不动。所以找到每个左端点对应的最大右端点是均摊 $O(1)$ 的。要找到一个点到中点之间的区间最大值，只需要预处理前缀后缀最大值即可。

当我们找到了 $[l,r]$ 区间中的最大值为左边的 $q$，那么左端点为 $l$，右端点在 $[mid+1,r]$ 的区间对总和的贡献都是 $q$，个数也很好算，计算右端点在 $[l,r]$ 中的个数减去右端点在 $[l,mid]$ 的个数即可，即

$$\frac{(r-mid)}{(k-1)}-\frac{(l-mid)}{(k-1)}$$

注意这里除法是下取整。然后乘上 $q$ 就是贡献了。

分治的边界条件是 $l=r$，由于长度为 $1$ 的区间不合法，所以不计算贡献。

## code

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2000001;
const ll P=1e9+7;
int n,m;
ll s,a[N],b1[N],b2[N];
ll sum1(ll q,ll l,ll r)
{
    return ((r-q)/(m-1)-(l-q-1)/(m-1))%P;
}
ll sum2(ll q,ll l,ll r)
{
    return ((q-l)/(m-1)-(q-r-1)/(m-1))%P;
}
void solve(int l,int r)
{
    if(l>r) return;
    if(l==r) return;
    int q=l+r>>1;
    b1[q]=a[q];
    b2[q+1]=a[q+1];
    for(int i=q-1;i>=l;--i) b1[i]=max(b1[i+1],a[i]);
    for(int i=q+2;i<=r;++i) b2[i]=max(b2[i-1],a[i]);
    int x=q;
    for(int i=q;i>=l;--i)
    {
        while(x+1<=r&&b2[x+1]<=b1[i]) ++x;
        s=(s+b1[i]*sum1(i,q+1,x)%P)%P;
    }
    x=q+1;
    for(int i=q+1;i<=r;++i)
    {
        while(x-1>=l&&b1[x-1]<b2[i]) --x;
        s=(s+b2[i]*sum2(i,x,q)%P)%P;
    }
    solve(l,q);
    solve(q+1,r);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    solve(1,n);
    printf("%lld",(s%P+P)%P);
    return 0;
}
```

---

## 作者：nynkqh_yzp (赞：0)

$\mathcal O(n)$ 的做法，但常数有一些大，要用类似于零点分段的方法。

首先容易发现答案就是每个长度为 $x\times (k-1)+1$ 的区间的最大值之和，即：
$$
\sum_{l=1}^{n}\sum_{x=1}^{\lfloor\frac{n-l}{k-1}\rfloor}\max_{i=l}^{l+x\times(k-1)}a_i
$$
这个时候区间的左右端点是在模 $k-1$ 意义下同余的。

然后就可以用处理这类题的常规方法：算每个数的贡献。

令 $f_{i,j}$ 表示 $[0,i]$ 中模 $k-1$ 等于 $j$ 的个数。

令 $l_i$ 表示 $a_{l_i-1}$ 是从 $i$ 往前第一个大于等于 $a_i$ 的数，没有就是 $1$。

令 $r_i$ 表示 $a_{l_r+1}$ 是从 $i$ 往后第一个大于 $a_i$ 的数，没有就是 $n$。

那么答案就是：
$$
\sum_{i=1}^{n}a_i\times((\sum_{j=0}^{k-2}(f_{i,j}-f_{l_i-1,j})\times(f_{r_i,j}-f_{i-1,j}))-1)
$$
为了减少讨论情况，做一步转换：
$$
\sum_{i=1}^{n}a_i\times((\sum_{j=0}^{k-2}(f_{i-1,j}-f_{l_i-1,j})\times(f_{r_i,j}-f_{i-1,j}))+f_{r_i,i\bmod (k-1)}-f_{i,i\bmod (k-1)})
$$
接下来要寻找 $f_{i,j}$ 的规律，发现：
$$
f_{i,0}=f_{i,1}=…=f_{i,i\bmod (k-1)}=f_{i,i\bmod (k-1)+1}+1=f_{i,i\bmod (k-1)+2}+1=…=f_{i,k-2}+1
$$
所以可以找五个断点 $-1$、$(l_i-1)\bmod(k-1)$、$(i-1)\bmod(k-1)$、$(r_i)\bmod(k-1)$、$k-2$。

然后前一个断点加 $1$ 到后一个断点之间的所有余数算出来的结果相等，可以合并。

代码有些丑。
```cpp
#include<bits/stdc++.h> 
using namespace std;
long long n,k,a[1000001],l[1000001],r[1000001],b[7],mo=1e9+7,s[1000001],ans;
long long f(long long x,long long y){//f函数 
	return x/k+(s[x]>=y);
}
int main(){
	scanf("%lld%lld",&n,&k);
	k--;
	for(long long i=1;i<=n;i++)
		scanf("%lld",&a[i]),s[i]=i%k;
	for(long long i=1;i<=n;i++){//处理数组l和数组r 
		l[i]=i-1;
		while(l[i]!=0&&a[l[i]]<a[i])
			l[i]=l[l[i]];
	}
	for(long long i=n;i>0;i--){
		r[i]=i+1;
		while(r[i]!=n+1&&a[r[i]]<=a[i])
			r[i]=r[r[i]];
	}
	for(long long i=1;i<=n;i++)
		l[i]++,r[i]--;
	for(long long i=1;i<=n;i++){
		ans+=a[i]*(f(r[i],s[i])-f(i,s[i])); 
		b[1]=-1,b[5]=k-1;//断点 
		b[2]=s[l[i]-1];
		b[3]=s[i-1];
		b[4]=s[r[i]];
		sort(b+1,b+6);
		for(long long j=2;j<=5;j++)
			ans+=a[i]*(b[j]-b[j-1])%mo*(f(i-1,b[j])-f(l[i]-1,b[j]))%mo*(f(r[i],b[j])-f(i-1,b[j]));//算每两个断点之间的值 
		ans%=mo;
	}
	printf("%lld",ans);
	return 0;
}
```


---

