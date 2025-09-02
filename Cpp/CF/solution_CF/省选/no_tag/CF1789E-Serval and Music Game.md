# Serval and Music Game

## 题目描述

给定整数 $n$ 和长度为 $n$ 的**递增**序列 $s$。  
定义 $f(x)$ 为满足下列要求的整数 $i(1\leq i\leq n)$ 的数量：

- 存在**非负整数** $p_i,q_i$ 使得 $s_i=p_i\bigg\lfloor\dfrac{s_n}{x}\bigg\rfloor+q_i\bigg\lceil\dfrac{s_n}{x}\bigg\rceil$。

你需要求出 $\sum_{x=1}^{s_n}x\times f(x)$ 对 $998244353$ 取模后的值。  
每个测试点包含 $t$ 组数据。

## 样例 #1

### 输入

```
4
3
1 2 4
4
1 2 7 9
4
344208 591000 4779956 5403429
5
1633 1661 1741 2134 2221```

### 输出

```
26
158
758737625
12334970```

# 题解

## 作者：thostever (赞：6)

非常有意思的题目。

我们考虑枚举每个 $x$ 算其贡献。

首先我们统计出 $s_i$ 的桶的前缀和，记为 $cnt_i$。方便计算。

### 情况 1：

若 $x$ 是 $s_n$ 的因数：

我们直接枚举 $\frac{s_n}{x}$ 的所有倍数，检查是否存在，算答案即可。复杂度是调和级数级别的。

### 情况 2：

若 $x$ 不是 $s_n$ 的因数：

我们令 $k=\left \lfloor \frac{s_n}{x} \right \rfloor $，则有$\left \lceil \frac{s_n}{x} \right \rceil =k+1$。

$p_i k+q_i (k+1)=s_i$

$(p_i+q_i)k+q_i=s_i$

由此可知，当 $s_i\mod k \leq \left \lfloor \frac{s_i}{k} \right \rfloor$ 时，存在 $p_i$ 和 $q_i$ 的解。

当 $\left \lfloor \frac{s_i}{k} \right \rfloor=j$ 时，$s_i\in [jk,jk+j]$。（只需要考虑 $j<k$ 的情况，因为 $s_i\geq k^2$ 时一定存在解）

这样我们就根据 $j\in [1,k-1]$ 把所有的 $s_i$ 划分成 $k-1$ 个区间，每个区间直接算贡献即可。同时也要加上 $s_i\geq k^2$ 的贡献。

对于所有 $k\leq \sqrt{s_n}$，每次计算 $k$ 个区间，一共计算 $k^2$ 次，总复杂度不超过 $O(s_n)$。

对于所有 $k>\sqrt{s_n}$，每次最多有 $\left \lfloor \frac{s_n}{k} \right \rfloor \leq \sqrt{s_n}$ 个区间（$k\times j\geq s_n$ 时无意义）。由于整除分块，最多有 $\sqrt{s_n}$ 个 $k$，总复杂度不超过 $O(s_n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
int n,m;
int s[1000010];
int cnt[10000010];
void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&s[i]);
	m=s[n];
	for(int i=1;i<=m;i++) cnt[i]=0;
	for(int i=1;i<=n;i++) cnt[s[i]]++;
	for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
	int ans=0;
	int lst=0;
	for(int i=1;i<=m;i++)
	{
		int sum=0;
		int k=m/i;
		if(m%i==0)
		{
			for(int j=k;j<=m;j+=k) sum+=cnt[j]-cnt[j-1];
		}
		else
		{
			if(m%(i-1)!=0&&int(m/(i-1))==k) sum=lst;
			else
			{
				for(int j=1;j<k&&j*k<=m;j++) sum+=cnt[min(j*k+j,m)]-cnt[j*k-1];
				if(1ll*k*k<=1ll*m) sum+=cnt[m]-cnt[k*k-1];
			}
		}
		ans=(1ll*i*sum+ans)%mod;
		lst=sum;
	}
	printf("%d\n",ans);
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
/*

*/

```


---

## 作者：Hisaishi_Kanade (赞：2)

首先当然要考虑对于其中一个 $x$ 怎么算。

便于我撰写设 $s_i=w,s_n=m$，$p,q$ 代表原题中的 $p_i,q_i$。

+ 若有 $\lfloor \dfrac m x\rfloor=\lceil\dfrac m x\rceil$，即 $m \bmod x=0$。这时候对于满足条件的的 $s_i$ 都得是 $\dfrac m x$ 的倍数，容易解决。
+ 如果不是以上的情况，则必然 $\lfloor \dfrac m x\rfloor+1=\lceil\dfrac m x\rceil$，设 $\lfloor \dfrac m x\rfloor=\lceil\dfrac m x\rceil -1=d$。
+ 即对于 $w$，$w=p\lfloor\dfrac{s_n}{x}\rfloor+q\lceil\dfrac{s_n}{x}\rceil=pd+q(d+1)=d(p+q)+q$。
+ 既然 $w=d(p+q)+q$，则 $w\bmod d=q$。
+ 注意到，$qd<w$，即 $q<\dfrac w d$，即 $w\bmod d\le\lfloor\dfrac w d\rfloor$。
+ 显然的，$w\bmod d\ge 0$，可以列出不等式即 $0\le w\bmod d\le\lfloor\dfrac w d\rfloor$。
+ 运用典中典结论 $a\bmod b=a-b\lfloor \dfrac a b \rfloor$，可以将原式化为 $d\lfloor\dfrac {s_n} d\rfloor\le s_i\le(d+1)\lfloor\dfrac {s_n} d\rfloor$。

我们把原题中的 $s_i$ 放入桶中然后前缀和，这样可以快速求出大小在某个范围内的数的个数。$s_n$ 不是很大我们直接枚举每一个 $x$。

然后枚举 $\dfrac m d$ 的值，对每个值算上面区间内数的个数。

累计一下就做完了。

```cpp
#include <iostream>
using ll=long long;
using namespace std;
#define rep(i,l,r) for(i=l;i<=r;++i)
int s[10000005];
int a[1000005];
int t,i,j,n,m,x;
ll d,ret,ans;
const int p=998244353;
inline ll min(ll x,ll y){return x<y?x:y;}
int main()
{
	cin>>t;
	while(t--)
	{
		ret=ans=0;
		cin>>n;
		rep(i,1,n)
			cin>>a[i];
		m=a[n];
		rep(i,1,m)s[i]=0;
		rep(i,1,n)++s[a[i]];
		rep(i,1,m)s[i]+=s[i-1];
		rep(x,1,m)
		{
			ret=0;
			d=m/x;
			if(m%x==0)
				for(j=d;j<=m;j+=d)
					ret+=(s[j]-s[j-1]);
			else
			{
				for(j=1;j<d && j*d<=m;++j)
					ret+=(s[min(j*d+j,m)]-s[j*d-1]);
				if(d*d<=m)
					ret+=s[m]-s[d*d-1];
			}
//			cout<<ret<<' '<<x<<endl;
			(ans+=x*ret)%=p;
		}
		cout<<ans<<"\n";
	}
}
```

---

## 作者：2018ljw (赞：1)

关注到 $\lfloor\frac {s_n}x\rfloor$ 和 $\lceil\frac{s_n}{x}\rceil$ 取值都很有限，考虑枚举前者的值 $val$，可以得到 $x$ 的一段对应区间。此时，若 $x\mid s_n$，后者值为 $val$，否则为 $val+1$，分别考虑。

若 $x\mid s_n$，则相当于问有多少数是 $val$ 的倍数，直接枚举倍数即可。

这一部分复杂度大致为 $s_n$ 约数和。

否则相当于问是否存在 $p,q$，$s_i=val\times (p+q)+q$。同时模 $val$ 得到最小的 $q=s_i\bmod val$，然后单独验证 $q\times val+q\le s_i$ 是否成立即可。

关注到我们的问题是，给定 $k$，问有多少 $s_i$ 满足 $(s_i\bmod k)\times(k+1)\le s_i$。设 $s_i=kx+b$，则有 $bk+b\le kx+b$，即 $b\le x$。

因此实际上就是在判定有多少 $\lfloor\frac{s_i}k\rfloor\ge s_i\bmod k$。

枚举 $\lfloor\frac{s_i}k\rfloor$ 一项，发现满足条件的 $s$ 在值域上应当是一个区间。因此对 $s$ 的桶做一个前缀和即可。

$k^2\le s$ 时必定合法，因此 $k\le\sqrt s_n$ 的有效枚举量不超过 $\sum k\le s_n$，$k\ge \sqrt s_n$ 时，由于 $k$ 的数量为根号级别，总枚举量不超过 $\sum \frac{s_n}{k}\le s_n$。

这一部分复杂度为 $O(s_n)$。[record](https://codeforces.com/contest/1789/submission/211291994)。

---

## 作者：紊莫 (赞：0)

暴力过了.jpg

---

我们尝试对于一个 $x$，计算答案。

显然 $\left \lfloor \dfrac{s_n}{x}  \right \rfloor $ 和 $\left \lceil \dfrac{s_n}{x}  \right \rceil$ 只有两种可能，相等或差为 $1$。相等时直接暴力算。

考虑不相等的情况，也就是说 $\left \lfloor \dfrac{s_n}{x}  \right \rfloor+1=\left \lceil \dfrac{s_n}{x}  \right \rceil$。这个时候怎样的 $s_i$ 才满足条件呢？化一下式子，设 $a=\left \lfloor \dfrac{s_n}{x}  \right \rfloor,b=\left \lceil \dfrac{s_n}{x}  \right \rceil$。

$$\begin{aligned}
s_i &= ap+bq\\
&= ap+(a+1)q\\
&=a(p+q)+q
\end{aligned}$$

发现其一定可以表示为 $s_i \bmod a=q$ 的形式，而根据 $aq<s_i$ 得到 $s_i \bmod a<\dfrac{s_i}{a}$，进一步得到 $s_i$ 的取值范围，然后发现这个范围很小，直接前缀和统计一下，我觉得很卡，但是意外地跑得很快。

[参考代码。](https://codeforces.com/contest/1789/submission/243389920)

---

## 作者：daniEl_lElE (赞：0)

$\text{Difficulty: }\color{red}\text{2500}$。

考虑先整除分块，按 $\lfloor\frac{s_n}{x}\rfloor,\lceil\frac{s_n}{x}\rceil$ 整除分块。

然后考虑 $\lfloor\frac{s_n}{x}\rfloor\not=\lceil\frac{s_n}{x}\rceil$ 的情况，显然此时不可以被构造出来的是 $\lfloor\frac{s_n}{x}\rfloor-1$ 段长度为 $\lfloor\frac{s_n}{x}\rfloor-1,\lfloor\frac{s_n}{x}\rfloor-2,\dots,0$ 的区间（手模可以得知，具体见代码），即 $0<k<\lfloor\frac{s_n}{x}\rfloor,[(k-1)\lfloor\frac{s_n}{x}\rfloor+1,k\lfloor\frac{s_n}{x}\rfloor-k]$。同时当区间左端点大于 $n$ 即可跳出循环。不难发现对于 $x\leq\sqrt{s_n}$ 和 $s>\sqrt{s_n}$ 复杂度均为 $O(s_n)$，即可通过。

[提交记录](https://codeforces.com/contest/1789/submission/200983519)。

---

