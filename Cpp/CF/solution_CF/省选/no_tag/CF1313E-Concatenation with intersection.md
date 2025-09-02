# Concatenation with intersection

## 题目描述

给定三个串 $a,b,s$，其中 $a,b$ 长度为 $n$，$s$ 长度为 $m$，求出四元组 $(l1,r1,l2,r2)$ 的个数，满足：

1. $[l1,r1]$ 和 $[l2,r2]$ 的交集非空。

2. $a$ 中位置 $l1$ 到 $r1$ 组成的子串与 $b$ 中位置 $l2$ 到 $r2$ 组成的子串拼起来恰好是 $s$。

$1 \leq n \leq 500000$，$2 \leq m \leq 2n$。

## 样例 #1

### 输入

```
6 5
aabbaa
baaaab
aaaaa```

### 输出

```
4```

## 样例 #2

### 输入

```
5 4
azaza
zazaz
azaz```

### 输出

```
11```

## 样例 #3

### 输入

```
9 12
abcabcabc
xyzxyzxyz
abcabcayzxyz```

### 输出

```
2```

# 题解

## 作者：tzc_wk (赞：12)

> 题意：给定三个串 $a,b,s$，其中 $a,b$ 长度为 $n$，$s$ 长度为 $m$，求出四元组 $(l1,r1,l2,r2)$ 的个数，满足：

> 1. $[l1,r1]$ 和 $[l2,r2]$ 的交集非空。

> 2. $a$ 中位置 $l1$ 到 $r1$ 组成的子串与 $b$ 中位置 $l2$ 到 $r2$ 组成的子串拼起来恰好是 $s$。

一道字符串+数据结构的神题。

首先，我们可以将两个串拼成 $s$ 转化为 $a$ 中匹配一个 $s$ 的非空前缀，$b$ 中匹配一个 $s$ 的非空后缀。

我们定义 $za_i$ 为 $s_1s_2 \dots s_{m-1}$ 与 $a_i,a_{i+1} \dots a_n$ 的最长公共前缀，$zb_i$ 为 $s_2s_3 \dots s_{m}$ 与 $b_1 b_2 \dots b_i$ 的最长公共后缀。这个可以用 Z 算法求出。详情见我的 blog ，这里就不赘述了。

不难发现，由于拼成的字符串恰好为 $s$，因此 

$$r1-l1+1+r2-l2+1=m$$

一定成立。移一下项，即

$$r2=l1-r1+l2-2+m$$

由于两区间有交点，所以 $l1 \leq r2$，$l2 \leq r1$ 成立，所以 $-r1+l2$ 一定小于等于 $0$，式子又可以变为

$$r2=l1-r1+l2-2+m \leq l1-2+m$$

所以我们可以得到 $r2 \leq l1+m-2$。

又根据 $l1 \leq r2$，所以两个区间满足条件一当且仅当 $l1 \leq r2 \leq l1+m-2$，$l2$ 和 $r1$ 就可以被我们忽略了。

我们发现，如果两个数 $l1,r2$ 满足上面的条件，那么满足条件的方案数为 $\max(za_{l1}+zb_{r2}-m+1,0)$。

这应该不是太难理解，举个栗子：

$m=5$，$s=\texttt{aabab}$，$za_{l1}=4$，$l1$ 开始的四个字符为 $\texttt{aaba}$，$zb_{l2}=3$，$l2$ 结尾的三个字符为 $\texttt{bab}$，那么有三种方法，分别是

- $\texttt{aa}+\texttt{bab}=\texttt{aabab}$

- $\texttt{aab}+\texttt{ab}=\texttt{aabab}$

- $\texttt{aaba}+\texttt{b}=\texttt{aabab}$

刚好就是 $4+3-5+1$。

这样我们就可以将原本 $n^5$ 的事情降到了 $n^2$，但是还是过不去啊。别急我们继续推式子。

根据上面的分析最终的答案就是：

$$\sum\limits_{l1=1}^n\ \sum\limits_{r2=l1}^{\min(l1+m-2,n)} \max(za_{l1}+zb_{r2}-m+1,0)$$

不难发现随着 $l1$ 的增长，$r2$ 也是单调递增的，所以我们可以用类似 two pointers 的方式维护，但是这个 $\max$ 有点讨厌，那么我们怎么想办法把这个 $\max$ 去掉呢？

我们发现，如果 $za_{l1}+zb_{r2}-m+1<0$，那么这个情况对答案没有贡献，因此我们只用考虑 $za_{l1}+zb_{r2}-m+1 \geq 0$，即 $m-1-zb_{r2} \leq za_{l1}$ 的情况，我们可以把这个条件加到我们的式子中，即

$$\sum\limits_{l1=1}^n\ \sum\limits_{r2=l1}^{\min(l1+m-2,n)} za_{l1}+zb_{r2}-m+1\ [m-1-zb_{r2} \leq za_{l1}]$$

假设在区间 $[l1,\min(l1+m-2,n)]$ 中满足 $m-1-zb_{r2} \leq za_{l1}$ 的 $r1$ 的个数为 $cnt$，又可以变为

$$\sum\limits_{l1=1}^n\ cnt \times (za_{l1}-m+1)+\sum\limits_{r2=l1}^{\min(l1+m-2,n)} zb_{r2}\ [m-1-zb_{r2} \leq za_{l1}]$$

发现 $m-1-zb_{r2}$ 不含 $l1$，那么我们可以建两个树状数组，从小到大枚举 $l1$，然后单调地增加 $r2$，每增加一个 $l2$，就在第一个树状数组 $m-1-zb_{r2}$ 增加 $zb_{r2}$，第二个树状数组 $m-1-zb_{r2}$ 增加 $1$，然后第一个树状数组 $\leq za_{l1}$ 位置上的和就是对应的 $\sum\limits_{r2=l1}^{\min(l1+m-2,n)} zb_{r2}$，第一个树状数组 $\leq za_{l1}$ 位置上的和就是对应的 $cnt$。然后加一下就可以了。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),m=read();
char a[500005],b[500005],s[1000005];
char buf[1500005];
int cnt=0,za[1500005],zb[1500005],z1[500005],z2[500005];
struct Fenwick_Tree{
	int bit[1500005];
	inline int lowbit(int x){
		return x&(-x);
	}
	inline void add(int x,int val){
		x=max(x,1ll);
		for(int i=x;i<=1000000;i+=lowbit(i))	bit[i]+=val;
	}
	inline int query(int x){
		int ans=0;
		for(int i=x;i;i-=lowbit(i))	ans+=bit[i];
		return ans;
	}
} t1,t2;
signed main(){
	scanf("%s%s%s",a+1,b+1,s+1);
	fz(i,1,m-1)	buf[cnt++]=s[i];
	buf[cnt++]='#';
	fz(i,1,n)	buf[cnt++]=a[i];
	int l=0,r=0;
	for(int i=1;i<cnt;i++){
		if(i<=r)	za[i]=min(za[i-l],r-i);
		while(i+za[i]<cnt&&buf[za[i]]==buf[i+za[i]])	za[i]++;
		if(i+za[i]>r){
			l=i;
			r=i+za[i];
		}
	}
	fill0(buf);cnt=0;
	fd(i,m,2)	buf[cnt++]=s[i];
	buf[cnt++]='#';
	fd(i,n,1)	buf[cnt++]=b[i];
	l=0,r=0;
	for(int i=1;i<cnt;i++){
		if(i<=r)	zb[i]=min(zb[i-l],r-i);
		while(i+zb[i]<cnt&&buf[zb[i]]==buf[i+zb[i]])	zb[i]++;
		if(i+zb[i]>r){
			l=i;
			r=i+zb[i];
		}
	}
	fz(i,1,n)	z1[i]=za[i+m-1];
	fz(i,1,n)	z2[i]=zb[i+m-1];
	reverse(z2+1,z2+n+1); 
	int r2=1,ans=0;
	fz(l1,1,n){
		while(r2<=min(l1+m-2,n)){
			t1.add(m-1-z2[r2],z2[r2]);
			t2.add(m-1-z2[r2],1);
			r2++;
		}
		ans+=(z1[l1]-m+1)*t2.query(z1[l1])+t1.query(z1[l1]);
		t1.add(m-1-z2[l1],-z2[l1]);
		t2.add(m-1-z2[l1],-1);
	}
	cout<<ans<<endl;
	return 0;
}
```

UPD：2020.2.26：公式中有个地方写错了，应该是 $za_{l1}+zb_{r2}-m+1$

---

## 作者：wucstdio (赞：5)

D 题 fst，自闭了。

## 题目大意

给你两个长度为 $n$ 的字符串 $a,b$ 和一个长度为 $m$ 的字符串 $s$，你需要从第一个字符串中选择一个 $a[l_1,r_1]$，在第二个字符串中选择一个 $b[l_2,r_2]$，使得 $a[l_1,r_1]+b[l_2,r_2]=s$，并且区间 $[l_1,r_1]$ 和 $[l_2,r_2]$ 有交，求方案数。

## 数据范围

$1\le n\le 500000,1\le m\le 2n$

## 解题过程

我们设 $s[i:]$ 表示 $s$ 这个字符串从 $s[i]$ 开始的后缀，$s[:i]$ 表示到 $s[i]$ 为止的前缀。 

首先考虑枚举 $l_1$ 和 $r_2$，则如果 $l_1+m-1<=r_2$ 就不可能（因为没法出现交点），否则考虑求出在这种情况下方案数是多少。

求出 $a[l_1:]$ 和 $s$ 的最长公共前缀的长度 $f(l_1)$ 以及 $b[:r_2]$ 和 $s$ 的最长公共后缀长度 $g(r_2)$，则方案数即为 $\max(0,f(l_1)+g(r_2)-m+1)$（可以枚举第一个区间的长度）。

综上所述，答案即为所有满足下列条件的 $f(i)+g(j)-m+1$ 之和：

- $i\le j$
- $i+m-1>j$
- $f(i)>0,g(j)>0$
- $f(i)+g(j)\ge m$

对第二个限制条件进行容斥，先加上所有满足一三四的，再减去满足一三四且 $j\ge i+m-1$ 的。

我们从后到前枚举 $i$，则无论是容斥的第一步还是第二步，$j$ 的取值范围都是一段连续的后缀，可以顺次加入。

接下来的问题就是维护一个 $j$ 的集合，支持动态插入 $j$ 以及对于一个 $i$，查询所有满足 $g(j)\ge \max(1,m-f(i))$ 的 $f(i)+g(j)-m+1$ 之和。

可以用树状数组实现。我们开两个树状数组，分别维护 $j$ 的数量 $A$ 以及满足条件的 $g(j)$ 之和 $B$，则答案即为 $(f(i)-m+1)*A-B$。

最后还有一个问题：如何快速求出所有的 $f(i)$ 和 $g(j)$。

一个思路是跑两遍 SA，时间复杂度 $O(n\log n)$，但是由于每一次字符串长度可以达到 $1.5\times 10^6$，有可能会 TLE。

更加优秀的解法是跑两遍扩展 KMP，时间复杂度 $O(n)$。

总时间复杂度是 $O(n\log n)$，由于 $\log$ 是树状数组所以常数够小，可以 AC。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
char a[500005],b[500005],s[1000005],ss[1500005];
int n,m,z[1500005],pre[500005],suf[500005],c2[1500005];
ll c[1500005],ans;//c记录的是g(j)之和，c2记录的是可行j的数量。
void add(int p,ll v)
{
	p++;
	while(p<=m+1)
	{
		c[p]+=v;
		c2[p]++;
		p+=p^(p&(p-1));
	}
}
pair<ll,int>sum(int p)//pair中的第一个是g(j)之和，第二个是j的数量
{
	p++;
	ll ans1=0;
	int ans2=0;
	while(p)
	{
		ans1+=c[p];
		ans2+=c2[p];
		p&=p-1;
	}
	return make_pair(ans1,ans2);
}
pair<ll,int>sum(int l,int r)
{
	l=max(1,l);
	r=min(m,r);
	if(l>r)return make_pair(0,0);
	pair<ll,int>s1=sum(r);
	pair<ll,int>s2=sum(l-1);
	return make_pair(s1.first-s2.first,s1.second-s2.second);
}
void Z(char*s,int n)//扩展KMP
{
	z[1]=n;
	int l=1,r=1;
	for(int i=2;i<=n;i++)
	{
		if(r<i)
		{
			l=r=i;
			while(r<=n&&s[r]==s[r-l+1])r++;
			z[i]=r-l;
			r--;
		}
		else
		{
			if(z[i-l+1]<r-i+1)z[i]=z[i-l+1];
			else
			{
				l=i;
				while(r<=n&&s[r]==s[r-l+1])r++;
				z[i]=r-l;
				r--;
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s%s%s",a+1,b+1,s+1);
	for(int i=1;i<=m;i++)ss[i]=s[i];
	for(int i=1;i<=n;i++)ss[i+m]=a[i];
	Z(ss,n+m);//第一次扩展KMP求出所有的f（也就是pre）
	for(int i=1;i<=n;i++)pre[i]=min(m-1,z[i+m]);
	for(int i=1;i<=m;i++)ss[i]=s[m-i+1];
	for(int i=1;i<=n;i++)ss[i+m]=b[n-i+1];
	Z(ss,n+m);//第二次扩展KMP求出所有的g（也就是suf）
	for(int i=1;i<=n;i++)suf[n-i+1]=min(m-1,z[i+m]);
	for(int i=n;i>=1;i--)//容斥第一步
	{
		add(suf[i],suf[i]);
		if(pre[i]==0)continue;
		pair<ll,int>res=sum(m-pre[i],m);
		ans+=res.first+(pre[i]-m+1ll)*res.second;
	}
	memset(c,0,sizeof(c));
	memset(c2,0,sizeof(c2));
	for(int i=n;i>=1;i--)//容斥第二步
	{
		if(i+m-2<=n)add(suf[i+m-1],suf[i+m-1]);
		if(pre[i]==0)continue;
		pair<ll,int>res=sum(m-pre[i],m);
		ans-=res.first+(pre[i]-m+1ll)*res.second;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：1saunoya (赞：4)

我们可以用 Z 算法求出来 A[]  和 S[] 的 LCP，B[] 和 S[] 的 LCS。复杂度  $O(N)$。

或者你喜欢 SA/SAM  也没关系，随便搞搞就好了，常数小点也能过（

然后我们发现，只要 $LCP + LCS \geq M$ 那么就是一组解，所以假设 $LCP + LCS \geq M$。

那么方案数是 $LCP  + LCS - M + 1$。

然后注意的一点是，两个有交，那么可以用树状数组扫描线维护一下。

但是有一点，两个交集不为空，那么两个字符串都不能为空，如果全覆盖，那么要预先减掉1。

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define int long long
const int maxn = 1e6 + 61;

struct BIT {
	std::vector <int> c, cnt;
	int n;
	BIT(int _n) { n = _n + 1; c.resize(n + 1), cnt.resize(n + 1); }
	
	int l(int x) { return x & -x; }
	void u(int x, int y) { for(; x <= n; x += l(x)) c[x] += y, cnt[x] += (y > 0) ? 1 : -1; }
	std::pair <int, int> q(int x) { std::pair <int, int> a = {0, 0}; for(; x; x ^= l(x)) a.first += c[x], a.second += cnt[x]; return a; }
};

signed main() {
	auto getZ = [&](char*s, int len) {
		std::vector <int> Z(len + 1, 0);
		Z[1] = len;
		for(int i = 2, l = 0, r = 0; i <= len; i++) {
			if(i < r)
				Z[i] = std::min(Z[i - l + 1], r - i + 1);
			while(i + Z[i] <= len && s[i+ Z[i]] == s[1 + Z[i]])
				++Z[i];
			if(i + Z[i] - 1 > r)
				l = i, r = i + Z[i] - 1;
		}
		return Z;
	};
	
	auto getP = [&](char*s, char*t, int n, int m) {
		std::vector <int> Z = getZ(t, m), P(n + 1, 0);
		for(int i = 1, l = 0, r = 0; i <= n; i++) {
			if(i < r)
				P[i] = std::min(Z[i - l + 1],  r - i + 1);
			while(i + P[i] <= n && s[i + P[i]] == t[1 + P[i]])
				++P[i];
			if(i + P[i] - 1 > r)
				l = i, r = i + P[i] - 1;
		}
		return P;
	};
	
	int n, m;
	static char a[maxn], b[maxn], s[maxn];
	scanf("%lld %lld", &n, &m);
	scanf("%s", a + 1), scanf("%s", b + 1), scanf("%s", s + 1);
	std::vector <int> P = getP(a, s, n, m);
	std::reverse(b + 1, b + n + 1);
	std::reverse(s + 1, s + m + 1);
	std::vector <int> Q = getP(b, s, n, m);
	reverse(Q.begin() + 1, Q.end());
	BIT bit(m + 1);
	for(int i = 1; i <= n; i++) {
		if(P[i] == m) --P[i];
		if(Q[i] == m) --Q[i];
	}
	long long ans = 0;
	for(int i = 1, j = 0; i <= n; i++)  {
		while(j < n && j + 1 < i + m - 1) { ++j; if(Q[j]) bit.u(Q[j], Q[j]); }
		std::pair <int, int> x = bit.q(m), y = bit.q(m - P[i] - 1);
		ans += x.first - y.first - 1ll * (x.second - y.second) * (m - P[i] - 1);
		if(Q[i]) bit.u(Q[i], -Q[i]);
	}
	printf("%lld\n", ans);
}
```

---

## 作者：xht (赞：3)

exkmp 求出 $a$ 的每个后缀和 $s$ 的 LCP，以及 $b$ 的每个后缀和 $s^r$ 的 LCP。

统计每个 $a_i$ 开头的方案数，two pointers 在 $b$ 上扫到对应的区间，树状数组维护即可。

设 $n,m$ 同阶，总时间复杂度 $\mathcal O(n \log n)$，$\log$ 在树状数组上而不在求 LCP 上，常数较小。

```cpp
const int N = 1e6 + 7;
int n, m, p[N], q[N], d[N], z[N];
ll c[N], ans;
char a[N], b[N], s[N];

inline void Z(char *s, int n) {
	for (int i = 1; i <= n; i++) z[i] = 0;
	z[1] = n;
	for (int i = 2, l = 0, r = 0; i <= n; i++) {
		if (i <= r) z[i] = min(z[i-l+1], r - i + 1);
		while (i + z[i] <= n && s[i+z[i]] == s[z[i]+1]) ++z[i];
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}

inline void exkmp(char *s, int n, char *t, int m, int *p) {
	Z(t, m);
	for (int i = 1; i <= n; i++) p[i] = 0;
	for (int i = 1, l = 0, r = 0; i <= n; i++) {
		if (i <= r) p[i] = min(z[i-l+1], r - i + 1);
		while (i + p[i] <= n && s[i+p[i]] == t[p[i]+1]) ++p[i];
		if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
	}
}

inline void add(int x, int k) {
	if (!x) return;
	while (x <= m) c[x] += k, d[x] += k > 0 ? 1 : -1, x += x & -x;
}

inline pair<ll, int> ask(int x) {
	ll k = 0;
	int p = 0;
	while (x) k += c[x], p += d[x], x -= x & -x;
	return mp(k, p);
}

int main() {
	rd(n), rd(m);
	rds(a, n), rds(b, n), rds(s, m);
	exkmp(a, n, s, m, p);
	reverse(b + 1, b + n + 1);
	reverse(s + 1, s + m + 1);
	exkmp(b, n, s, m, q);
	reverse(q + 1, q + n + 1);
	for (int i = 1, j = 0; i <= n; i++) {
		while (j + 1 <= n && j + 1 < i + m - 1) {
			if (q[++j] == m) --q[j];
			add(q[j], q[j]);
		}
		if (p[i] == m) --p[i];
		pair<ll, int> x = ask(m), y = ask(m - p[i] - 1);
		ans += x.fi - y.fi - 1ll * (x.se - y.se) * (m - p[i] - 1);
		add(q[i], -q[i]);
	}
	print(ans);
	return 0;
}
```

---

## 作者：chenxia25 (赞：2)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF1313E) & [CodeForces题目页面传送门](https://codeforces.com/contest/1313/problem/E)

>给定$3$个字符串$a,b,c,|a|=|b|=n,|c|=m$，求满足以下全部条件的有序区间对$([l1,r1],[l2,r2])$的个数：

>1. $[l1,r1]\cap[l2,r2]\neq\varnothing$；
>1. $a_{l1\sim r1}+b_{l2\sim r2}=c$。

>$n\in\left[1,5\times10^5\right],m\in[2,2n]$。

$c$由$a,b$各一个子串拼接而成，不难想到两面夹击——从$a_{l1}$往后与$c$的前缀匹配、从$b_{r2}$往前与$c$的后缀匹配。于是我们可以预处理出$2$个数组$lcP:lcP_i=\max\limits_{a_{i\sim i+j-1}=c_{1\sim j}}\{j\},Lcs:Lcs_i=\max\limits_{b_{i-j+1\sim i}=c_{m-j+1\sim m}}\{j\}$，对$c+\texttt!+a,c^\mathrm r+\texttt!+b^\mathrm r$这$2$个字符串各跑一遍Z算法即可。

假设我们已经固定住了$l1,r2$。设从$l1$往后延伸了$x$位，从$r2$往前自然就延伸了$m-x$位，于是$r1=l1+x-1,l2=r2-m+x+1$。

考虑满足题目中的条件$1$的充要条件。满足条件$1$当且仅当$[l1,r1]\cap[l2,r2]=[l1,l1+x-1]\cap[r2-m+x+1,r2]=[\max(l1,r2-m+x+1),\min(l1+x-1,r2)]\neq\varnothing$，即$\max(l1,r2-m+x+1)\leq\min(l1+x-1,r2)$，即$\begin{cases}l1\leq l1+x-1\\l1\leq r2\\r2-m+x+1\leq l1+x-1\\r2-m+x+1\leq r2\end{cases}$，即$\begin{cases}x\in[1,m-1]\\r2\in[l1,l1+m-2]\end{cases}$。

再考虑满足条件$2$的充要条件。满足条件$2$当且仅当$\begin{cases}x\leq lcP_{l1}\\m-x\leq Lcs_{r2}\end{cases}$，即$x\in[m-Lcs_{r2},lcP_{l1}]$。

综上，若已知$l1,r2,x$，那么满足题目中的所有条件当且仅当$\begin{cases}r2\in[l1,l1+m-2]\\x\in[\max(1,m-Lcs_{r2}),\min(m-1,lcP_{l1})]\end{cases}$。显然$\forall l1\in[1,n],\forall r2\in[l1,\min(n,l1+m-2)]$，$r2$对答案贡献为$\max(1,\min(m-1,lcP_{l1})-\max(1,m-Lcs_{r2})+1)$。这里面有个$\max$，比较讨厌，我们把它分成$\min(m-1,lcP_{l1})-\max(1,m-Lcs_{r2})+1\geq1$和$\min(m-1,lcP_{l1})-\max(1,m-Lcs_{r2})+1<1$这$2$种情况。对于后者，显然贡献为$0$，无需考虑；对于前者，即$\max(1,m-Lcs_{r2})\leq \min(m-1,lcP_{l1})$，贡献为$\min(m-1,lcP_{l1})-\max(1,m-Lcs_{r2})+1$。

所以答案显然为$\sum\limits_{l1=1}^n\sum\limits_{r2\in[l1,\min(n,l1+m-2)],\max(1,m-Lcs_{r2})\leq\min(m-1,lcP_{l1})}(\min(m-1,lcP_{l1})-\max(1,m-Lcs_{r2})+1)$。由于当$l1$单调递增时，$r2$所在区间的左端点和右端点也同时单调递增，我们可以用two-pointers维护。不妨在值域上建一个BIT，然后从左往右枚举$l1$，每次添加、删除各$0\sim1$个$\max(1,m-Lcs_{r2})$。答案中的求和式可以分成分别关于$l1,r2$的$2$部分$\min(m-1,lcP_{l1})+1,-\max(1,m-Lcs_{r2})$，对$2$部分分别求和，显然BIT不仅要实现值域上的区间求和，还要实现值域上的区间计数。枚举到每个$l1$，设添加、删除完$\max(1,m-Lcs_{r2})$后，值域上的区间$[1,\min(m-1,lcP_{l1})]$内求和的结果为$sum$，计数的结果为$cnt$，则对答案的贡献是$cnt\cdot(\min(m-1,lcP_{l1})+1)+sum$。哦对了，别忘了在$l1=1$的时候把$\forall r2\in[1,\min(n,m-1)],\max(1,m-Lcs_{r2})$全部添加到BIT里哦！

$\forall r2\in[1,n]$，$\max(1,m-Lcs_{r2})$最多会被添加、删除各$1$次，每次$\mathrm O(\log_2m)$，所以复杂度$\mathrm O(n\log_2m)$。再加上之前$\mathrm O(n+m)$的Z算法，总复杂度$\mathrm O(m+n\log_2m)$。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//答案会爆int 
int lowbit(int x){return x&-x;} 
const int N=500000,M=1000000;
int n/*|a|=|b|*/,m/*|c|*/; 
char a[N+5],b[N+5],c[M+5];//3个字符串 
int lcP[N+1],Lcs[N+1];//lcP[i],Lcs[i]各表示从a,b的第i位开始向后、向前最多能与c的前缀、后缀匹配的位数 
int s;/*|d|*/ 
char d[N+M+5];//临时字符串 
void con(char x[],char y[]){//令d=x+'!'+y 
	s=0;
	for(int i=1;i<=m;i++)d[++s]=x[i];
	d[++s]='!';
	for(int i=1;i<=n;i++)d[++s]=y[i];
}
int z[N+M+1];//z数组 
void z_init(){//Z算法 
	z[1]=s;
	int zl=0,zr=0;
	for(int i=2;i<=s;i++)
		if(zr<i){
			z[i]=0;
			while(i+z[i]<=s&&d[i+z[i]]==d[1+z[i]])z[i]++;
			if(z[i])zl=i,zr=i+z[i]-1;
		}
		else if(i+z[i-zl+1]<=zr)z[i]=z[i-zl+1];
		else{
			z[i]=zr-i+1;
			while(i+z[i]<=s&&d[i+z[i]]==d[1+z[i]])z[i]++;
			zl=i;zr=i+z[i]-1;
		}
}
struct bitree{//BIT 
	int sum[M+1]/*和*/,cnt[M+1]/*计数*/;
	void init(){
		memset(sum,0,sizeof(sum));
		memset(cnt,0,sizeof(cnt));
	}
	void add(int v){//添加 
		int x=v;
	    while(x<=n)sum[x]-=v,cnt[x]++,x+=lowbit(x);
	}
	void del(int v){//删除 
		int x=v;
		while(x<=n)sum[x]+=v,cnt[x]--,x+=lowbit(x);
	}
	int Sum(int x){//求前缀和 
		int res=0;
		while(x)res+=sum[x],x-=lowbit(x);
		return res;
	}
	int Cnt(int x){//求前缀计数 
		int res=0;
		while(x)res+=cnt[x],x-=lowbit(x);
		return res;
	}
}bit;
signed main(){
	scanf("%lld%lld%s%s%s",&n,&m,a+1,b+1,c+1);
	con(c,a);
	z_init();
	for(int i=1;i<=n;i++)lcP[i]=z[m+1+i];//求lcP 
	reverse(b+1,b+n+1);reverse(c+1,c+m+1);con(c,b);
	z_init();
	for(int i=1;i<=n;i++)Lcs[i]=z[m+1+(n-i+1)];//求Lcs 
//	for(int i=1;i<=n;i++)printf("%lld %lld\n",lcP[i],Lcs[i]);
	int ans=0;
	bit.init();
	for(int i=1;i<=min(n,m-1);i++)bit.add(max(1ll,m-Lcs[i]));//在l1=1时预先添加r2 in [1,min(n,m-1)]
	for(int i=1;i<=n;i++){
		if(i>1)bit.del(max(1ll,m-Lcs[i-1]))/*删除r2=i-1*/,i+m-2<=n&&(bit.add(max(1ll,m-Lcs[i+m-2])),0)/*添加r2=i+m-2*/;
		ans+=(min(m-1,lcP[i])+1)*bit.Cnt(min(m-1,lcP[i]))+bit.Sum(min(m-1,lcP[i]));//贡献答案 
//		cout<<ans<<"\n";
	}
	cout<<ans;
	return 0;
}
```

最后说句闲话，你们知道为什么这题难度这么高吗？

~~因为这场比赛的D非常难~~

---

## 作者：xfrvq (赞：1)

设 $a_i=\mathrm{lcp}(A_{i\cdots n},S),b_i=\mathrm{lcs}(B_{1\cdots i},S)$，字符串哈希求。对于 $i=l_1,j=r_2$，考虑 $(r_1,l_2)$ 应满足的条件。

+ $[l_1,r_1],[l_2,r_2]$ 交集非空：$j\in[i,i+m-1)$。
+ 此时可能的 $(r_1,l_2)$ 是一段区间，有 $\max(a_i+b_j-m+1,0)$ 个。

对于 $i$，要对所有 $j\in[i,i+m-1),b_j\ge m-a_i-1$ 的 $j$ 求出个数，$b_j$ 的和。直接二维数点即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e6 + 5;
const ll mod = 1e9 + 7;

int n,m,a[N],b[N];
ll P[N],Q[N],S[N],T[N];
__int128 ans;
vector<pair<int,int>> V[N];

void print(auto x){
	if(x / 10) print(x / 10);
	putchar(x % 10 + 48);
}

struct solve{
	string s;
	vector<ll> f;
	
	void init(){
		f.resize(s.size() + 1);
		for(int i = 1;i <= s.size();++i)
			f[i] = (f[i - 1] + (s[i - 1] - 'a' + 1) * P[i]) % mod;
	}
	
	ll qry(int l,int r){
		l = max(l,1),r = min(r,(int)s.size());
		return (f[r] - f[l - 1] + mod) % mod * Q[l - 1] % mod;
	}
} A,B,C;

void upd(int p,ll x){
	for(;p;p &= p - 1) S[p] += x,++T[p];
}

auto qry(int p,ll s = 0,ll t = 0){
	for(;p < N;p += p & -p) s += S[p],t += T[p];
	return make_pair(s,t);
}

int main(){
	for(int i = P[0] = Q[0] = 1;i < N;++i)
		P[i] = P[i - 1] * 31 % mod,Q[i] = Q[i - 1] * 129032259 % mod;
	cin >> n >> m >> A.s >> B.s >> C.s;
	A.init(),B.init(),C.init();
	for(int i = 1;i <= n;++i){
		for(int j = 19;~j;--j){
			if(A.qry(i,i + a[i] + (1 << j) - 1) == C.qry(1,a[i] + (1 << j))) a[i] += 1 << j;
			if(B.qry(i - b[i] - (1 << j) + 1,i) == C.qry(m - b[i] - (1 << j) + 1,m)) b[i] += 1 << j;
		}
		a[i] = min({a[i],n - i + 1,m}),b[i] = min({b[i],i,m});
		if(a[i] == m) (ans += -m + 1);
		if(b[i] == m) (ans += -m + 1);
		if(i <= min(i + m - 2,n)) V[i - 1].emplace_back(i,-1),V[min(i + m - 2,n)].emplace_back(i,1);
	}
	for(int i = 1;i <= n;++i){
		ll x,y;
		upd(b[i] + 1,b[i]);
		for(auto[j,k] : V[i])
			tie(x,y) = qry(m - a[j] + 1),
			ans += (x + (a[j] - m + 1) * y) * k;
	}
	print(ans);
	return 0;
}
```

---

## 作者：紊莫 (赞：1)

容易想到去求出 $pre_i$ 表示 $a$ 中 $[i, n]$ 这个后缀和 $s$ 的 LCP，以及 $suf_i$ 表示 $b$ 中 $[1, i]$ 这个前缀和 $s$ 的 LCS（最长公共后缀）。

可以通过 Z-function 在 $O(n)$ 时间内求出。

然后考虑枚举题目中的 $l_1, r_2$ 以及在 $a$ 中的长度 $l$，有如下限制：

1. 不能超过和 $s$ 最长的匹配长度。
2. 不能超出边界。
3. $r_2 - l_1 + 1 < m$，保证题目中的有交。

最后得到的式子非常简单，使用你喜欢的数据结构来拆开计算即可。


```cpp
// To scale the heights, one must embrace the fall.
#include <bits/stdc++.h>
#define int long long

#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define dF(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int N = 2000005, M = (N << 1), inf = 1e16, mod = 1e9 + 7;
int n, m, ans, pre[N], suf[N];
auto getz(string s) {
    int l = s.size(); s = " " + s;
    vector<int> z(l + 1, 0);
    for (int i = 2, x = 0, r = 0; i <= l; i++) {
        if (r > i) z[i] = min(z[i - x + 1], r - i);
        while (s[z[i] + 1] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) r = i + z[i] - 1, x = i;
    }
    return z;
}
string rev(string s) { reverse(s.begin(), s.end()); return s; }
struct BIT {
    int t[N];
    void add(int x, int v) {
        for (; x <= 2000000; x += x & -x) t[x] += v;
    }
    int query(int x) {
        int r = 0;
        for (; x; x -= x & -x) r += t[x];
        return r;
    }
    int query(int x, int y) {
        return query(y) - query(x - 1);
    }
} t1, t2;
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    string a, b, s;
    cin >> n >> m >> a >> b >> s;
    auto z1 = getz(s + a), z2 = getz(rev(s) + rev(b));
    F(i, 1, n) {
        pre[i] = min(m - 1, z1[i + m]);
        suf[i] = min(m - 1, z2[n - i + 1 + m]);
        pre[i] = min(pre[i], n - i + 1);
        suf[i] = max(m - suf[i], m - i);
    }
    int p = 1;
    F(i, 1, n) {
        while (p <= n && p <= i + m - 2) {
            t1.add(suf[p], 1);
            t2.add(suf[p], suf[p]);
            p++;
        }
        int ct = t1.query(pre[i] + 1);
        int sm = t2.query(pre[i] + 1);
        ans += (pre[i] + 1) * ct - sm;
        t1.add(suf[i], -1);
        t2.add(suf[i], -suf[i]);
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：BreakPlus (赞：1)

+ 本篇题解 1-index。

+ 考虑将 $s$ 分成两段，$s = p + q$，然后在 $a$ 里面匹配 $p$，$b$ 里面匹配 $q$。

+ 发现 $p$ 是 $s$ 的前缀，$q$ 是 $s$ 的后缀。

+ 为了利用这个性质，我们可以记录 $u_i = \operatorname{LCP}(a[i:n],s)$ 以及 $v_i = \operatorname{LCS}(a[1:i],s)$。其中 LCP 是最长公共前缀，LCS 是最长公共后缀。这样，跑两边 Z 函数，我们就可以获得所有的匹配信息。

+ 也就是说，我们接下来将会盯着 $l_1, r_2$ 看。

+ 同时加入**交集非空**的限制，若钦定 $|p|=x, |q|=m-x$，令两个位置为 $l_1=s,r_2=t$，它们能匹配当且仅当 $u_s \ge x,v_t\ge m-x，s \le t \le s+m-2$。

+ 发现 $s \le t \le s+m-2$ 这个条件挺优美的。这是因为 $|p| + |q|$ 恒为 $m$，第一个小于号防止了 $r_2 > l_1$，第二个小于号防止了 $r_1 < l_2$。

+ 众多题解都把接下来一步做得有些繁琐，其实可以枚举 $|p|$，用树状数组维护每个时刻 $u_s \ge x$ 的 $s$，$v_t \ge m-x$，以及当前匹配的 $(s,t)$ 的数量，然后累加得到答案。这是很好写的。

```cpp
const ll N = 1000000;
ll n,m; char a[N+5],b[N+5],s[N+5];
ll z[N+5],p[N+5],q[N+5];
void Z(){
    memset(z, 0, sizeof(z));
    z[1] = m;
    ll zl=0, zr=0;
    for(ll i=2;i<=m;i++){
        if(i <= zr) z[i] = minn(z[i-zl+1], zr-i+1);
        while(i+z[i] <= m && s[1+z[i]] == s[i+z[i]]) z[i]++;
        if(i+z[i]-1 > zr) zl = i, zr = i+z[i]-1;
    }
}
vector<ll>vp[N+5],vq[N+5];
ll now = 0;
// b1 b2 是两个树状数组
void addleft(ll i){
    now += b2.query(min(i+m-2, n)) - b2.query(i-1);
    b1.update(i, 1);
}
void delright(ll i){
    now -= b1.query(i) - b1.query(max(i-m+2, 1ll)-1);
    b2.update(i, -1);
}
void solve(){
    n=read(), m=read();
    scanf("%s%s%s", a+1, b+1, s+1);
    Z();
    ll zl=0, zr=0;
    for(ll i=1;i<=n;i++){
        if(i <= zr) p[i] = minn(z[i-zl+1], zr-i+1);
        while(p[i]+i <= n && 1+p[i] <= m && s[1+p[i]] == a[i+p[i]]) p[i]++;
        if(i+p[i]-1 > zr) zl = i, zr = i+p[i]-1;
    }

    reverse(s+1, s+m+1); reverse(b+1, b+n+1);
    Z();
    zl=0, zr=0;
    for(ll i=1;i<=n;i++){
        if(i <= zr) q[i] = minn(z[i-zl+1], zr-i+1);
        while(q[i]+i <= n && 1+q[i] <= m && s[1+q[i]] == b[i+q[i]]) q[i]++;
        if(i+q[i]-1 > zr) zl = i, zr = i+q[i]-1;
    }

    reverse(q+1, q+n+1);

    for(ll i=1;i<=n;i++) vp[p[i]].pb(i);
    for(ll i=1;i<=n;i++) vq[q[i]].pb(i), b2.update(i, 1);

    for(auto v: vp[m]) addleft(v);
    ll ans = 0;
    for(ll i=m-1;i>=1;i--){
        for(auto v: vp[i]) addleft(v);
        for(auto v: vq[m-i-1]) delright(v);
        ans += now;
    }
    printf("%lld\n", ans);
}
```

---

## 作者：do_while_true (赞：1)

考虑这个 $l_1$ 一定是 $s$ 的开头，$r_2$ 一定是 $t$ 的结尾，那么就考虑假如固定了 $l_1,r_2$ 之后怎么计算对答案的贡献。

一个河狸的想法是，固定 $l_1$ 之后可以通过 exkmp 求出 $\operatorname{LCP}(a[l_1:],s)$，就知道 $r_1$ 能落在 $l_1$ 的 Z-box 里。同理也知道 $l_2$ 能落在 $r_2$ 的 Z-box 里。

假设 $\operatorname{LCP}(a[l_1:],s)=p,\operatorname{LCS}(b[:r_2],s)=q$，$a$ 选了 $x$ 个，那么 $b$ 选 $m-x$ 个，则 $[l_1,r_1]=[l_1,l_1+x-1],[l_2,r_2]=[r_2-(m-x)+1,r_2]$．

它俩有交当且仅当 $r_1\geq l_2$ 且 $r_2\geq l_1$，化简后可得 $l_1\leq r_2\leq l_1+m-2$，这是第一维限制。

然后再考虑满足条件的 $x$ 数量，$1\leq x\leq p,1\leq m-x\leq q$，也就是 $\max(1,m-q)\leq x\leq \min(p,m-1)$．

然后所有的 $p,q$ 都和 $m-1$ 取个 $\min$，这样符合条件的 $x$ 的数量就是 $p-(m-q)+1$，而且要满足 $p\geq m-q$，这是第二维限制。

于是变成一个二维数点问题。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=998244353;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
inline int lowbit(int x){
	return x&(-x);
}
const int N=1000100;
int n,m,z[N],p[N],q[N];
char a[N],b[N],s[N];
ll ans;
struct Tree{
	ll tree[N];
	void modify(int x,ll v){++x;for(;x<=n+1;x+=lowbit(x))tree[x]+=v;}
	ll query(int x){++x;ll s=0;for(;x;x-=lowbit(x))s+=tree[x];return s;}
	ll query(int l,int r){return query(r)-query(l-1);}
}tr1,tr2;
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n,m);
	scanf("%s%s%s",a+1,b+1,s+1);
	for(int i=2,l=0,r=0;i<=m;i++){
		if(i<=r)z[i]=min(z[i-l+1],r-i+1);
		else z[i]=0;
		while(i+z[i]<=m && s[z[i]+1]==s[i+z[i]])++z[i];
		if(i+z[i]-1>r)r=i+z[i]-1,l=i;
	}
	for(int i=1,l=0,r=0;i<=n;i++){
		if(i<=r)p[i]=min(z[i-l+1],r-i+1);
		else p[i]=0;
		while(p[i]<m && i+p[i]<=n && s[p[i]+1]==a[i+p[i]])++p[i];
		if(i+p[i]-1>r)r=i+p[i]-1,l=i;
	}
	reverse(b+1,b+n+1);
	reverse(s+1,s+m+1);
	for(int i=2,l=0,r=0;i<=m;i++){
		if(i<=r)z[i]=min(z[i-l+1],r-i+1);
		else z[i]=0;
		while(i+z[i]<=m && s[z[i]+1]==s[i+z[i]])++z[i];
		if(i+z[i]-1>r)r=i+z[i]-1,l=i;
	}
	for(int i=1,l=0,r=0;i<=n;i++){
		if(i<=r)q[i]=min(z[i-l+1],r-i+1);
		else q[i]=0;
		while(q[i]<m && i+q[i]<=n && s[q[i]+1]==b[i+q[i]])++q[i];
		if(i+q[i]-1>r)r=i+q[i]-1,l=i;
	}	
	reverse(q+1,q+n+1);
	for(int i=1;i<=n;i++)cmin(p[i],m-1),cmin(q[i],m-1);
	for(int i=n;i;i--){
		tr1.modify(m-q[i],1);
		tr2.modify(m-q[i],-m+q[i]+1);
		ans+=tr1.query(p[i])*p[i];
		ans+=tr2.query(p[i]);
		if(i-m+1>=1){
			int l=i-m+1;
			ans-=tr1.query(p[l])*p[l];
			ans-=tr2.query(p[l]);
		}
	}
	cout << ans << '\n';
    #ifdef do_while_true
		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

仅考虑第二个条件是容易计算的。具体地，对于 $a$ 的每一位找到他与 $s$ 匹配的最长前缀，$b$ 的每一位找到他与 $s$ 匹配的最长后缀，使用前缀和即可算出。对于第一个条件，考虑容斥，用总数减去 $[l_1,r_1]$ 与 $[l_2,r_2]$ 不交的方案数。

当 $r_1<l_2$ 时，$l_1\leq r_2-s$，于是可以扫一遍 $b$ 数组，每次将 $a$ 的 $i-s$ 位置与 $s$ 匹配的最长前缀扔到线段树中区间加，对于 $b$ 的 $i$ 位置与 $s$ 匹配的最长后缀在线段树中区间求和。

$r_2<l_1$ 时，只需要扫一遍 $a$ 数组，将 $b$ 数组的情况扔进线段树即可。与前一种情况类似。

总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353,mul=131;
struct sgt{
	int f[4000005],lzt[4000005];
	void init(){
		memset(f,0,sizeof(f));
		memset(lzt,0,sizeof(lzt));
	}
	void pushdown(int i,int l,int r){
		f[i*2]+=lzt[i]*(mid-l+1);
		f[i*2+1]+=lzt[i]*(r-mid);
		lzt[i*2]+=lzt[i];
		lzt[i*2+1]+=lzt[i];
		lzt[i]=0; 
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql>qr) return ;
		if(ql<=l&&r<=qr){
			lzt[i]+=cg;
			f[i]+=(r-l+1)*cg;
			return ;
		}
		pushdown(i,l,r);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		f[i]=f[i*2]+f[i*2+1];
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql>qr) return 0;
		if(ql<=l&&r<=qr) return f[i];
		pushdown(i,l,r);
		if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		return qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr);
	}
}tree;
int hsh1[1000005],hsh2[1000005],pw[1000005];
int lcp[1000005],lcs[1000005];
signed main(){
	pw[0]=1; for(int i=1;i<=1000000;i++) pw[i]=pw[i-1]*mul%mod;
	int n,m; cin>>n>>m;
	string a,b,s,t; cin>>a>>b>>s; t=s; reverse(t.begin(),t.end());
	a=" "+a,b=" "+b,s=" "+s,t=" "+t;
	{
		memset(hsh1,0,sizeof(hsh1));
		memset(hsh2,0,sizeof(hsh2));
		for(int i=1;i<=m;i++) hsh1[i]=(hsh1[i-1]+pw[i]*(s[i]-'a'+1))%mod;
		for(int i=1;i<=n;i++) hsh2[i]=(hsh2[i-1]+pw[i]*(a[i]-'a'+1))%mod;
		for(int i=1;i<=n;i++){
			if(s[1]-'a'!=a[i]-'a') continue;
			int l=1,r=min(m,n-i+1);
			while(l<r){
				int M=(l+r+1)>>1;
				if((hsh1[M]*pw[i-1]%mod)==((hsh2[i+M-1]+mod-hsh2[i-1])%mod)) l=M;
				else r=M-1;
			}
			lcp[i]=l;
		}
	}
	{
		memset(hsh1,0,sizeof(hsh1));
		memset(hsh2,0,sizeof(hsh2));
		for(int i=1;i<=m;i++) hsh1[i]=(hsh1[i-1]+pw[i]*(t[i]-'a'+1))%mod;
		for(int i=n;i>=1;i--) hsh2[i]=(hsh2[i+1]+pw[n-i+1]*(b[i]-'a'+1))%mod;
		for(int i=1;i<=n;i++){
			if(t[1]-'a'!=b[i]-'a') continue;
			int l=1,r=min(m,i);
			while(l<r){
				int M=(l+r+1)>>1;
				if((hsh1[M]*pw[n-i]%mod)==((hsh2[i-M+1]+mod-hsh2[i+1])%mod)) l=M;
				else r=M-1;
			}
			lcs[i]=l;
		}
	}
	int ans=0;
	tree.init();
	for(int i=1;i<=n;i++) tree.change(1,1,m,1,lcp[i],1);
	for(int i=1;i<=n;i++) ans+=tree.qry(1,1,m,m-lcs[i],m-1);
	tree.init();
	for(int i=1;i<=n;i++){
		if(i>=m) tree.change(1,1,m,1,lcp[i-m+1],1);
		ans-=tree.qry(1,1,m,m-lcs[i],m-1);
	}
	tree.init();
	for(int i=n;i>=1;i--){
		ans-=tree.qry(1,1,m,m-lcs[i],m-1);
		tree.change(1,1,m,1,lcp[i],1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lzqy_ (赞：0)

一骑绝尘的最劣解做法，是最劣解 $rk2$ 时间的三倍，空间的十倍。

一个最基础的暴力是从小到大枚举  $s$ 的断点 $i$（$[1,i]$ 从 $a$ 中取，$(i,m]$ 从 $b$ 中取），接着求出 $s[1,i]$ 在 $a$ 中出现的位置 $[l_1,r_1],\dots,[l_m,r_m]$ 以及 $s[i+1,m]$ 在 $b$ 中出现的位置 $[L_1,R_1],\dots,[L_m,R_m]$，然后两两配对统计答案。这样就得到了一种 $O(n^3)$ 方的做法。

考虑基于这个暴力进行优化。

考虑对 $a$ 的反串以及 $b$ 分别建立 SAM，那么 $l_i,R_i$ 分别是两个 SAM 的 $\text{endpos}$。依次枚举端点时，显然 $a^r,b$ 对应的 $\text{endpos}$ 集是单调的。发现断点从 $1\sim m$ 时，$\text{endpos}$ 集在 Parent Tree 上对应的是一条深度单调的链。考虑将链上的节点标记，对于未标记的节点做启发式合并，那么在每个标记的节点上挂的集合，就是走到该节点时需要添加或删除的 $\text{endpos}$ 集。至此，便做到了均摊 $O(n)$ 的实时维护两个 $\text{endpos}$ 集。每加入一个新区间，更新答案是显然的，用两个 BIT 标记 $\text{endpos}$ 即可。

 另一个问题是，$a$ 区间集合的 $l_i$ 不变，$r_i$ 依次减一，$b$ 的区间集合 $R_i$ 不变，$L_i$ 依次加一。但这个改变对于答案是没有影响的，考虑相交的条件是 $R_j-l_i+1 \in [0,len_a+len_b]$，值域并未发生变化。所以在枚举断点的同时实时维护相交的区间数即可。

时间复杂度 $O(n\log n)$，时空常数极大。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=500010;
const int MAXN=maxn*2;
struct edge{
    int v,to;
}e1[MAXN],e2[MAXN];
int head1[MAXN],ecnt1;
int head2[MAXN],ecnt2;
void addedge1(int u,int v){
    e1[++ecnt1].v=v,e1[ecnt1].to=head1[u],head1[u]=ecnt1;
}
void addedge2(int u,int v){
    e2[++ecnt2].v=v,e2[ecnt2].to=head2[u],head2[u]=ecnt2;
}
struct sam{
    int ch[26],fa,len;
}a1[MAXN],a2[MAXN];
int cnt1=1,Ed1=1;
int cnt2=1,Ed2=1;
ll ans;
int n,m;
vector<int>v1[MAXN],v2[MAXN];
int Tree1[maxn],Tree2[maxn];
void A1(int k,int x){for(;k<=n;k+=k&-k)Tree1[k]+=x;}
void A2(int k,int x){for(;k<=n;k+=k&-k)Tree2[k]+=x;}
int Q1(int k,int sum=0){for(;k;k-=k&-k)sum+=Tree1[k];return sum;}
int Q2(int k,int sum=0){for(;k;k-=k&-k)sum+=Tree2[k];return sum;}
void Insert1(int c){   
    int t=Ed1,x=Ed1=++cnt1,nt=0,nx; a1[x].len=a1[t].len+1;
    v1[x].push_back(a1[x].len);////////
    for(;!nt&&t;t=a1[t].fa,nt=a1[t].ch[c]) a1[t].ch[c]=x;
    if(!t){a1[x].fa=1;return ;}
    if(a1[nt].len==a1[t].len+1){a1[x].fa=nt;return ;}
    nx=++cnt1,a1[nx].len=a1[t].len+1;
    a1[nx].fa=a1[nt].fa,a1[nt].fa=a1[x].fa=nx;
    for(int i=0;i<26;i++) a1[nx].ch[i]=a1[nt].ch[i];
    for(;a1[t].ch[c]==nt;t=a1[t].fa) a1[t].ch[c]=nx;
}
void Insert2(int c){   
    int t=Ed2,x=Ed2=++cnt2,nt=0,nx; a2[x].len=a2[t].len+1;
    v2[x].push_back(a2[x].len);////////
    for(;!nt&&t;t=a2[t].fa,nt=a2[t].ch[c]) a2[t].ch[c]=x;
    if(!t){a2[x].fa=1;return ;}
    if(a2[nt].len==a2[t].len+1){a2[x].fa=nt;return ;}
    nx=++cnt2,a2[nx].len=a2[t].len+1;
    a2[nx].fa=a2[nt].fa,a2[nt].fa=a2[x].fa=nx;
    for(int i=0;i<26;i++) a2[nx].ch[i]=a2[nt].ch[i];
    for(;a2[t].ch[c]==nt;t=a2[t].fa) a2[t].ch[c]=nx;
}
int loc1[MAXN],loc2[MAXN];
char a[maxn],b[maxn],c[maxn<<1];
int id1[MAXN],id2[MAXN];
bool vis1[MAXN],vis2[MAXN];

bool chk1(int r){
    for(int x=1,i=r;i;x=a1[x].ch[c[i]-'a'],i--)
        if(!a1[x].ch[c[i]-'a']) return 0;
    return 1;
}
bool chk2(int l){
    for(int x=1,i=l;i<=m;x=a2[x].ch[c[i]-'a'],i++)
        if(!a2[x].ch[c[i]-'a']) return 0;
    return 1;
}
void merge1(int x,int y){
    if(v1[id1[x]].size()<v1[id1[y]].size()){
        int tmp=id1[x];
        id1[x]=id1[y];
        x=tmp,y=id1[y];
        swap(x,y);
    }else x=id1[x],y=id1[y];
    for(int i=0;i<v1[y].size();i++)
        v1[x].push_back(v1[y][i]);
    v1[y].clear(),v1[y].shrink_to_fit();
}
void merge2(int x,int y){
    if(v2[id2[x]].size()<v2[id2[y]].size()){
        int tmp=id2[x];
        id2[x]=id2[y];
        x=tmp,y=id2[y];
        swap(x,y);
    }else x=id2[x],y=id2[y];
    for(int i=0;i<v2[y].size();i++)
        v2[x].push_back(v2[y][i]);
    v2[y].clear(),v2[y].shrink_to_fit();
}
void dfs1(int x){
    for(int i=head1[x];i;i=e1[i].to){
        dfs1(e1[i].v);
        if(!vis1[e1[i].v])
            merge1(x,e1[i].v);
    }
}
void dfs2(int x){
    for(int i=head2[x];i;i=e2[i].to){
        dfs2(e2[i].v);
        if(!vis2[e2[i].v])
            merge2(x,e2[i].v);
    }
}
void Add1(int x,int len,ll &sum){
    int len2=m-len;
    for(int i=0;i<v1[x].size();i++){
        int l=n-v1[x][i]+1,r=l+len-1;
        sum+=Q2(min(r+len2-1,n))-Q2(l-1),A1(l,1);
    }
}
void Del1(int x,int len,ll &sum){
    int len2=m-len;
    for(int i=0;i<v1[x].size();i++){
        int l=n-v1[x][i]+1,r=l+len-1;
        sum-=Q2(min(r+len2-1,n))-Q2(l-1),A1(l,-1);
    }
}
void Add2(int x,int len,ll &sum){
    int len1=m-len;
    for(int i=0;i<v2[x].size();i++){
        int r=v2[x][i],l=r-len+1;
        sum+=Q1(r)-Q1(max(l-len1,0)),A2(r,1);
    }
}
void Del2(int x,int len,ll &sum){
    int len1=m-len;
    for(int i=0;i<v2[x].size();i++){
        int r=v2[x][i],l=v2[x][i]-len+1;
        sum-=Q1(r)-Q1(max(l-len1,0)),A2(r,-1);
    }
}
int main(){
    //printf("%.3lf\n",(sizeof(a1)+sizeof(a2)+sizeof(e1)+sizeof(e2)+sizeof(head1)+sizeof(head2))/1024.0/1024.0);
    scanf("%d%d",&n,&m);
    scanf("%s",a+1);
    scanf("%s",b+1);
    scanf("%s",c+1);
    for(int i=1;i<=n;i++)
        if(i<n-i+1) swap(a[i],a[n-i+1]);
    for(int i=1;i<=n;i++) Insert1(a[i]-'a');
    for(int i=1;i<=n;i++) Insert2(b[i]-'a');
    //for(int i=1;i<=cnt1;i++,printf("\n"))
    //    for(int j=0;j<26;j++)
    //        printf("%d ",a1[i].ch[j]);
    for(int i=1;i<=cnt1;i++) id1[i]=i;
    for(int i=1;i<=cnt2;i++) id2[i]=i;
    for(int i=2;i<=cnt1;i++) addedge1(a1[i].fa,i);
    for(int i=2;i<=cnt2;i++) addedge2(a2[i].fa,i);
    //////////////////////////////
    int l=1,r=min(n,m-1),mid,x=1;
    while(r>l){
        mid=l+r+1>>1;
        if(chk1(mid)) l=mid;
        else r=mid-1;
    }
    for(int i=l;i;i--)
        x=a1[x].ch[c[i]-'a'];
    for(int i=l;i;i--){
        loc1[i]=x,vis1[x]=1;
        if(a1[a1[x].fa].len==i-1)
            x=a1[x].fa;
    }
    //////////////////////////////
    //////////////////////////////
    l=m-min(n,m-1)+1,r=m,x=1;
    while(r>l){
        mid=l+r>>1;
        if(chk2(mid)) r=mid;
        else l=mid+1;
    }
    for(int i=l;i<=m;i++)
        x=a2[x].ch[c[i]-'a'];
    for(int i=(m-l+1);i;i--){
        loc2[i]=x,vis2[x]=1;
        if(a2[a2[x].fa].len==i-1)
            x=a2[x].fa;
    }
    //////////////////////////////
    dfs1(loc1[1]),dfs2(loc2[1]);
    ll sum=0;
    for(int i=1;i<=n;i++)
        if(loc1[i]!=loc1[i-1]) Add1(id1[loc1[i]],i,sum);
    for(int i=1,l1,l2;i<=min(n,m-1);i++){
        l1=i,l2=m-i;
        if(loc1[l1]!=loc1[l1-1]) Del1(id1[loc1[l1-1]],l1,sum);
        if(loc2[l2]!=loc2[l2+1]) Add2(id2[loc2[l2]],l2,sum);
        ans+=sum;
    }printf("%lld\n",ans);
    return 0;
}
```





---

