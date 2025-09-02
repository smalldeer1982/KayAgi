# [THUPC 2025 初赛] waht 先生的法阵

## 题目背景

由于洛谷评测机太慢，$4s\to 5s$。

## 题目描述

waht 先生是一名法力强大的魔法师。

waht 先生为了增强自己的法力，设置了一个法阵。这个法阵中共有 $n$ 块魔法石，它们从左到右依次排成一列；并且从左数第 $i$ 块魔法石的编号为 $i$，其法力值初始为 $a_i$。

waht 先生可以获取一些魔法石的法力。然而由于这个法阵的特殊性质，在获取法力时，waht 先生必须先选择一块魔法石；并且一旦第 $x$ 块魔法石被选，接下来必须再选第 $x+\gcd(x,a_x)$ 块魔法石（这里 $\gcd(x,y)$ 表示 $x,y$ 的最大公约数），直到 $x+\gcd (x,a_x)>n$ 时 waht 先生会立即停止本次法力获取的过程。waht 先生获取的法力将会是过程中所选的所有魔法石的法力值之和。

waht 先生会对这个法阵进行 $q$ 次操作。具体的，有以下两类操作：

- waht 先生选择两个数 $l,r\;(1\leq l\leq r\leq n)$，对区间 $[l,r]$ 中的所有魔法石施加法术，使得它们的法力值全部乘以 $c$。具体的，对于所有满足 $l\leq i\leq r$ 的 $i$，将 $a_i$ 的值修改为 $c\cdot a_i$。
- waht 先生选择第 $x$ 块魔法石，并按照上述的规则获取法力。

每当 waht 先生选择某一块魔法石来获取法力时，你都需要帮他计算出他到底获得了多少法力。由于答案可能很大，你只需要求出答案对 $998244353$ 取模的结果。


## 说明/提示

第一次操作，将区间 $[2,6]$ 中的魔法石的法力值乘以 $2$，法力值序列变为 $1,2,2,2,2,2,1$；

第二次操作，waht 先生选择第 $1$ 块魔法石，则编号为 $1,2,4,6$ 的魔法石会依次被选中，这些魔法石的法力值之和为 $7$；

第三次操作，将区间 $[3,5]$ 中的魔法石的法力值乘以 $5$，法力值序列变为 $1,2,10,10,10,2,1$；

第四次操作，waht 先生选择第 $3$ 块魔法石，则编号为 $3,4,6$ 的魔法石会依次被选中，这些魔法石的法力值之和为 $22$；

第五次操作，将区间 $[2,7]$ 中的魔法石的法力值乘以 $3$，法力值序列变为 $1,6,30,30,30,6,3$；

第六次操作，waht 先生选择第 $3$ 块魔法石，则编号为 $3,6$ 的魔法石会依次被选中，这些魔法石的法力值之和为 $36$；

第七次操作，waht 先生选择第 $2$ 块魔法石，则编号为 $2,4,6$ 的魔法石会依次被选中，这些魔法石的法力值之和为 $42$。

#### 题目来源

来自 2025 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2025）初赛。

题解等资源可在 <https://gitlink.org.cn/thusaa/thupc2025pre/tree/master> 查看。

## 样例 #1

### 输入

```
7 7
1 1 1 1 1 1 1
1 2 6 2
2 1
1 3 5 5
2 3
1 2 7 3
2 3
2 2```

### 输出

```
7
22
36
42```

# 题解

## 作者：Pengzt (赞：8)

# waht 先生的法阵

[题目链接](https://www.luogu.com.cn/problem/P11527)。[cnblogs](https://www.cnblogs.com/Pengzt/p/18660161)。

### Problem

给定数列 $a$。需要支持 $Q$ 次操作，分为以下两种。

1. 区间乘 $c$（$2 \le c \le 2.5\times 10^5$）。
2. 给出 $x$，按以下方法得到答案：记答案为 $ans$，初始时为 $0$。从 $x$ 开始，每次 $ans \gets ans+a_x$ 后 $x \gets x+\gcd(x, a_x)$。当 $x$ 大于 $n$ 时结束。求出  $ans$ 对 $998244353$ 取模的值。

数据范围：$1 \le n, Q \le 2.5\times 10^5, a_i \in [1, 998244353) \cap \mathbb{Z}$。

### Sol

这个东西和 [CF1491H Yuezheng Ling and Dynamic Tree](https://www.luogu.com.cn/problem/CF1491H) 这道题很像啊。不难发现，对于 $i$，$\gcd(i, a_i)$ 的变化次数是非常有限的，可以直接均摊出来。直接考虑分块。

不妨记 $to_i$ 和 $sum_i$ 分别表示 $i$ 跳出当前块的右端点时的位置和经过的权值和。对于散块可以暴力更新。对于整块：

+ 如果块内所有 $\gcd(i, a_i) = 1$。跳过该块。
+ 否则找到所有会被更改的点，暴力更新。

如果块长取 $B$，则一个点更改一次的时间复杂度是 $\mathcal{O}(B)$ 的。判断整块是否需要更新可以枚举 $c$ 的所有质因数，然后看这块中有没有数乘上这个质因数后 $\gcd$ 会变化（这个可以对每个数记录还有那些质因数以及次数，然后就是查询区间是否有值）。

对于枚举质数的部分，时间复杂度为：$\mathcal{O}(m \omega(c)\log n)$。

查询的复杂度：$\mathcal{O}(\frac nB)$。

现在考虑一个数会修改多少次，显然当 $a_i$ 都是 $1$ 的时候变化次数最多。考虑质数 $p$ 会产生多少的贡献，这个显然为 $\sum\limits_{i=1}^{+\infty} \lfloor \frac{n}{p^i} \rfloor \le \sum\limits_{i=1}^{+\infty} \frac{n}{p^i} = \frac{n}{p - 1}$，即所有数分解质因数后 $p$ 的出现次数和。所以最后所有数的变化次数为 $\sum_{p \in \text{prime}} \frac{n}{p-1}$。~~clx 表示这是欧依的~~。根据埃氏筛的时间复杂度分析，这个是 $\mathcal{O}(\ln \ln n)$ 的。

所以修改的时间是 $\mathcal{O}(B n \ln \ln n)$。

当 $m\frac nB = Bn \ln \ln n$ 时，即 $B = \sqrt{\frac{m}{\ln \ln n}}$ 时有最小值。时间复杂度为：$\mathcal{O}(n\sqrt{m \ln \ln n})$。题解有不对的地方欢迎大家指正！

### Code

代码没有卡过常，跑得很慢。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second
mt19937_64 eng(time(0) ^ clock());
template<typename T>
T rnd(T l, T r) { return eng() % (r - l + 1) + l; }
int pC, pri[250005];
bool vis[250005];
vector<int> d[250005];
void Init(int n) {
    for (int i = 2; i <= n; i++) {
        if (!vis[i])
            pri[++pC] = i;
        for (int j = 1; j <= pC && i * pri[j] <= n; ++j) {
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
	for (int i = 1; i <= pC && pri[i] <= n; i++)
		for (int j = pri[i]; j <= n; j += pri[i])
			d[j].emplace_back(i);
    memset(vis, 0, sizeof(vis));
}
const int B = 200, P = 998244353;
int n, m;
int bel[250005], L[250005], R[250005], g[250005], re[250005], to[250005];
ll a[250005], sum[250005], laz[250005];
set<int> s[250005];
int tpt, stkt[250005];
int tp, stk[250005];
void Calc(int i) {
	int x = i;
	sum[i] = 0;
	while (x <= R[bel[i]]) {
		(sum[i] += a[x]) %= P;
		x += g[x];
	}
	to[i] = x;
}
bool arv[250005];
void Update(int x) {
	for (int i = R[x]; i >= L[x]; i--) {
		sum[i] = a[i] % P;
		if (i + g[i] <= R[x]) {
			(sum[i] += sum[i + g[i]]) %= P, to[i] = to[i + g[i]];
		} else {
			to[i] = i + g[i];
		}
	}
}
void Modify(int l, int r, ll c) {
	int x = bel[l], y = bel[r];
	int now = c;
	for (int i : d[c]) {
		if ((int) s[i].size() == 0)
			continue;
		int cnt = 0;
		while (now % pri[i] == 0)
			now /= pri[i], cnt++;
		auto pl = s[i].lower_bound(l);
		auto pr = s[i].lower_bound(r + 1);
		for (auto it = pl; it != pr; it++) {
			int p = *it, tmp = cnt;
			while (re[p] % pri[i] == 0 && tmp > 0)
				re[p] /= pri[i], g[p] *= pri[i], tmp--;
			if (re[p] % pri[i])
				stkt[++tpt] = p;
			if (!vis[p])
				stk[++tp] = p, vis[p] = 1;
		}
		while (tpt)
			s[i].erase(stkt[tpt--]);
	}
	for (int i = 1; i <= tp; i++) {
		Calc(stk[i]);
		Update(bel[stk[i]]);
	}
	for (int i = 1; i <= tp; i++)
		vis[stk[i]] = 0;
	tp = 0;
	if (x == y) {
		for (int i = l; i <= r; i++)
			a[i] = a[i] * c % P;
		Update(x);
	} else {
		for (int i = l; i <= R[x]; i++)
			a[i] = a[i] * c % P;
		for (int i = L[y]; i <= r; i++)
			a[i] = a[i] * c % P;
		Update(x), Update(y);
		for (int i = x + 1; i < y; i++)
			laz[i] = laz[i] * c % P;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	Init(250000);
	for (int i = 1; i <= n; i++)
		scanf("%lld", a + i);
	for (int i = 1; i <= n; i++)
		bel[i] = (i - 1) / B + 1;
	for (int i = 1; i <= bel[n]; i++)
		L[i] = (i - 1) * B + 1, R[i] = min(n, i * B);
	for (int i = 1; i <= bel[n]; i++)
		laz[i] = 1;
	for (int i = 1; i <= n; i++) {
		g[i] = __gcd((ll) i, a[i]);
		re[i] = i / g[i];
		for (int j : d[re[i]])
			s[j].emplace(i);
	}
	for (int i = 1; i <= n; i++)
		Calc(i);
	for (int _ = 1, op, x, y, z; _ <= m; _++) {
		scanf("%d%d", &op, &x);
		if (op == 1) {
			scanf("%d%d", &y, &z);
			Modify(x, y, z);
		} else {
			ll ans = 0;
			for (int i = x; i <= n; i = to[i])
				(ans += sum[i] * laz[bel[i]] % P) %= P;
			printf("%lld\n", ans);
		}
	}
	return 0;
}
```

[原始代码 & gen & 暴力](https://www.luogu.com.cn/paste/rartmnwn)

---

## 作者：donghanwen1225 (赞：5)

出题人来写个题解。

做法的核心是分块。将序列分为长度为 $B$ 的一些块，并维护块内每个位置不断向后跳时第一次跳出块时对应的位置和这个过程中 $a_x$ 的总和，则可以 $O\left(\dfrac{n}{B}\right)$ 的处理一次查询。修改虽然是区间修改，但维护新的跳到的位置时，$\gcd(x,a_x)$ 的改变次数最多是 $x$ 质因子分解后对应幂次的总和，可以说明总的改变次数是 $O(n\log\log n)$ 的，因此可以用 set 对每个质数维护还可能被修改的位置，每次修改时暴力重构整个块；而对于维护一路上的权值和，可以对整块的修改打标记、散块的修改直接暴力，复杂度为 $O\left(B+\dfrac{n}{B}\right)$。因此总的复杂度大致为 $O\left(q\left(B+\dfrac{n}{B}\right)+n\log\log n\cdot (B+\log n)\right)$，综合分析常数和理论结果，大致取 $B=200\sim250$ 时最优。

原题时限 $4s$，std 即使开 $B=500$ 也能 $2s$ 跑完，所以应该完全不卡常。事实上赛时一些 $O(q\sqrt n\log n)$ 复杂度的都可以卡过去。

代码：


```cpp
#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
const int B=250,mod=998244353;
int n,q,op,l,r,c,x,ks,a[250005],rs[250005],cd[250005],cv[250005],tag[1005];
int cnt,p[250005];bool v[250005];set<int> s[250005];
template<typename T> void Read(T &x)
{
	x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
}
void init(int n)
{
	for(int i=2;i<=n;i++)
		if(!v[i])
		{
			p[++cnt]=i;
			for(int j=i*2;j<=n;j+=i) v[j]=1;
		}
}
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
void upd(int l,int r,int cs,int cp)
{
	auto be=s[cp].lower_bound(l);
	while(be!=s[cp].end()&&*be<=r)
	{
		int now=*be;int nr=now/rs[now],cc=0;
		while(nr%cp==0&&cc<cs) nr/=cp,rs[now]*=cp,cc++;
		int bl=(now-1)/B+1,L=(bl-1)*B+1,R=min(n,bl*B);int nto=now+rs[now];
		if(nto>n) cd[now]=n+1,cv[now]=a[now];
		else if(nto>R) cd[now]=nto,cv[now]=a[now];
		else cd[now]=cd[nto],cv[now]=(a[now]+cv[nto])%mod;
		for(int i=now-1;i>=L;i--)
		{
			int to=i+rs[i];
			if(to>n) cd[i]=n+1,cv[i]=a[i];
			else if(to>R) cd[i]=to,cv[i]=a[i];
			else cd[i]=cd[to],cv[i]=(a[i]+cv[to])%mod;
		}
		if(nr%cp) be=s[cp].erase(be);
		else be++;
	}
}
void rb(int x,int l,int r,int c)
{
	int L=(x-1)*B+1,R=min(n,x*B);
	for(int i=L;i<=R;i++)
	{
		a[i]=1ll*a[i]*tag[x]%mod;
		if(l<=i&&i<=r) a[i]=1ll*a[i]*c%mod;
	}
	for(int i=R;i>=L;i--)
	{
		int to=i+rs[i];
		if(to>n) cd[i]=n+1,cv[i]=a[i];
		else if(to>R) cd[i]=to,cv[i]=a[i];
		else cd[i]=cd[to],cv[i]=(a[i]+cv[to])%mod;
	}
	tag[x]=1;
}
int main()
{
	Read(n);Read(q);
	for(int i=1;i<=n;i++) Read(a[i]),rs[i]=gcd(i,a[i]);
	init(n);
	for(int i=1;i<=n;i++)
	{
		int tmp=i/rs[i];
		for(int j=1;p[j]*p[j]<=tmp;j++)
			if(tmp%p[j]==0)
			{
				s[p[j]].insert(i);
				while(tmp%p[j]==0) tmp/=p[j];
			}
		if(tmp>1) s[tmp].insert(i);
	}
	ks=(n-1)/B+1;
	for(int i=ks;i>=1;i--)
	{
		int L=(i-1)*B+1,R=min(n,i*B);
		for(int j=R;j>=L;j--)
		{
			int to=j+rs[j];
			if(to>n) cd[j]=n+1,cv[j]=a[j];
			else if(to>R) cd[j]=to,cv[j]=a[j];
			else cd[j]=cd[to],cv[j]=(a[j]+cv[to])%mod;
		}
		tag[i]=1;
	}
	while(q--)
	{
		Read(op);
		if(op==1)
		{
			Read(l);Read(r);Read(c);
			int tc=c;
			for(int j=1;p[j]*p[j]<=tc;j++)
				if(tc%p[j]==0) 
				{
					int cs=0;while(tc%p[j]==0) tc/=p[j],cs++;
					upd(l,r,cs,p[j]);
				}
			if(tc>1) upd(l,r,1,tc);
			int bl=(l-1)/B+1,br=(r-1)/B+1;
			for(int i=bl+1;i<=br-1;i++) tag[i]=1ll*tag[i]*c%mod;
			if(bl==br) rb(bl,l,r,c);
			else rb(bl,l,bl*B,c),rb(br,(br-1)*B+1,r,c);
		}
		if(op==2)
		{
			Read(x);
			int ans=0,dq=x;
			while(dq<=n)
			{
				int bl=(dq-1)/B+1;
				ans=(ans+1ll*tag[bl]*cv[dq])%mod;
				dq=cd[dq];
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：XZhuRen (赞：3)

# 前置知识

看到跳跃次数，想到倍增，发现要求动态，明显不可以。

然后发现可以用 [P3203 [HNOI2010] 弹飞绵羊](https://www.luogu.com.cn/problem/P3203)的方法维护。

做前最好知道势能 `set` 的用法，[P4145 上帝造题的七分钟 2 / 花神游历各国](https://www.luogu.com.cn/problem/P4145)。 

# 题解

观察数据范围，发现 $1≤a_{i}<998244353$，但是 $2≤c≤2.5×10^{5}$，$c$ 与 $n$ 是同级的，这提示我们每次筛出 $2.5×10^{5}$ 范围内的所有质数，对于一个 $\gcd(a_{i},i)$，只要维护 $i$ 的质因数就可以了。

容易发现质因数个数是 $\ln$ 级别的，实际代码中也不会超过 $7$。

一次跳跃的步数是 $\gcd(a_{i},i)$，容易发现 $i$ 的因子是不变的，也就是最大公因数取到 $i$ 就不会变化了。

所以套路地，用 `set` 维护对于每个因数，还有哪些元素乘上之后有变化。

用分块分别维护块内的数到块外的步数，价值和即可，注意另用开数列分块维护乘法标记，整块修改直接乘法标记，散块修改完 `rebuild()`。

将修改 $\gcd$ 视为散块修改，每次修改需要 $\mathcal{O}(\sqrt{n})$ 的时间，最多修改 $n \ln n$ 次。本题常数要求不高，时间复杂度取大为 $\mathcal{O}(n \sqrt{n}\ln n)$，块长为 $\sqrt{n}$ 即可通过。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename T>
void in(T &n){
    n=0;char c=getchar();bool flag=0;
    for(;c<'0'||c>'9';c=getchar()) if (c=='-') flag=1;
    for(;c>='0'&&c<='9';c=getchar()) (n*=10)+=(c^48);
    if (flag) n=-n;
}
int wlsk[45];int wltp;
template<typename T>
void out(T n,char c=0){
    if (n==0){putchar('0');if (c)putchar(c);return ;}
    if (n<0) putchar('-'),n=-n;
    while(n) wlsk[++wltp]=(n%10),n/=10;
    while(wltp) putchar(wlsk[wltp--]^48);
    if (c) putchar(c);
}
const int N=3e5+5;
const int M=2.5e5;
const int MAXS=505;
typedef long long ll1;
ll1 A[N];
const ll1 mod=998244353;
int n,q;
struct blocks{
	int l,r;
}b[MAXS];
ll1 tag[N];//乘法标记，表示整个区间乘法标记
int nxt[N];
ll1 step[N];
int tb=0;
int bel[N];
int S;
bool isp[N];
int p[N],sp=0;
int id[N];//每个质因子的编号
void euler(){//筛出
	isp[1]=0;
	for(int i=2;i<=M;i++){
		isp[i]=(isp[i]^1);
		if(isp[i])p[++sp]=i,id[i]=sp;
		for(int j=1,k=2;j<=sp&&i*k<=M;k=p[++j]){
			isp[i*k]=true;
			if(i%k==0)break;
		}
	}
}
//对每个i进行质因数分解(1<=i<=n)
//得到的必然是不超过log2(i)个数个质因子
int Primex(int x,int *C){
	int cnt=0;
	for(int i=2;i*i<=x;i++){
		if(x%i)continue;
		C[++cnt]=i;
		while(x%i==0)x/=i;
	}
	if(x>1){C[++cnt]=x;}
	return cnt;
}
int c[N][7];//每个数的分解质因数
int cntc[N][7];//每个数的质因数计数
int ac[N][7];//每个元素a[i]相对于当前的i取的一个最大公因数，以c[i]为基准
set<int>e[22050];//每个质因数有贡献的单位
int gcd[N];//nxt[i]i+gcd[i]

void init(){
	euler();
	for(int i=1;i<=M;i++){
		c[i][0]=Primex(i,c[i]);
		int tmpi;
		for(int j=1;j<=c[i][0];j++)c[i][j]=id[c[i][j]];
		for(int j=1;j<=c[i][0];j++){
			tmpi=i;
			while(tmpi%(p[c[i][j]])==0){
				tmpi/=p[c[i][j]],
				cntc[i][j]++;
			}
		}
	}//给每个数除除倍
	in(n),in(q);
	int ta;
	for(int i=1;i<=n;i++){
		in(A[i]);ta=A[i];
		for(int j=1;j<=c[i][0];j++){
			while(ta%(p[c[i][j]])==0){
				ta/=p[c[i][j]],
				ac[i][j]++;
			}
			ac[i][j]=min(ac[i][j],cntc[i][j]);
		}
	}
}
int GCD(int x){
	int res=1,tmp;
	for(int i=1;i<=c[x][0];i++){
		tmp=min(ac[x][i],cntc[x][i]);
		while(tmp--)res*=p[c[x][i]];
	}
	return res;
}
void rebuild(int o){
	int l=b[o].l,r=b[o].r;
	for(int i=r;i>=l;i--)A[i]=(A[i]*tag[o])%mod;
	tag[o]=1;
	for(int i=r;i>=l;i--){
		if(i+gcd[i]>r)step[i]=A[i],nxt[i]=i+gcd[i];//,cs[i]=1;
		else step[i]=(A[i]+step[i+gcd[i]])%mod,nxt[i]=nxt[i+gcd[i]];//cs[i]=cs[i+gcd[i]]+1;
	}
}
int count(int x){
	int ans=0;
	while(x<=n){
		(ans+=(step[x]*tag[bel[x]])%mod)%=mod;
		x=nxt[x];
	}
	return ans;
}
void init2(){
	S=sqrt(n);
	b[tb=0].l=-S-S;
	for(int i=1;i<=n;i++){
		if((b[tb].l+S-1)<i)b[++tb].l=i;
		b[tb].r=i;bel[i]=tb;
	}
	for(int i=1;i<=n;i++){
		gcd[i]=GCD(i);
		for(int j=1;j<=c[i][0];j++)
			if(ac[i][j]<cntc[i][j])e[c[i][j]].insert(i);
	}
	for(int i=1;i<=tb;i++){
		tag[i]=1;rebuild(i);
	}
}
set<int>::iterator pos,pos1,pos2;
int stk[N],top=0;
void modify(int P,int lt,int rt){
	pos1=e[P].lower_bound(lt);
	pos2=e[P].upper_bound(rt);
	if(pos1==pos2)return;
	top=0;int x;
	for(pos=pos1;pos!=pos2;pos++){
		x=*pos;
		int i=1;
		for(;i<=c[x][0];i++)if(c[x][i]==P)break;
		ac[x][i]++;
		gcd[x]=GCD(x);
		rebuild(bel[x]);
		if(ac[x][i]<cntc[x][i])stk[++top]=x;
	}
	e[P].erase(pos1,pos2);
	while(top)e[P].insert(stk[top--]);
}
void change(int lt,int rt,int x){
	int st=bel[lt],ed=bel[rt];
	for(int o=st;o<=ed;o++){
		int l=b[o].l,r=b[o].r;
		if(l>=lt&&r<=rt){//整块乘法
			tag[o]=(tag[o]*x)%mod;
		}else{
			for(int i=max(lt,l);i<=min(r,rt);i++){
				A[i]=(A[i]*x)%mod;
			}
			rebuild(o);
		}
	}
}
void work(){
	int op;
	int l,r;
	int x;
	int ans=0;
	while(q--){
		in(op);
		if(op==1){
			in(l),in(r),in(x);
			for(int i=1;i<=c[x][0];i++){
				for(int j=1;j<=cntc[x][i];j++)
				modify(c[x][i],l,r);
			}
			change(l,r,x);
		}else{
			in(x);ans=count(x);
			out(ans,'\n');
		}
	}
}
signed main(){
//	freopen("H.in","r",stdin);
	init();
	init2();
	work();
	return 0;
}
```

---

## 作者：xxxxxzy (赞：2)

场上过了，写篇题解吧，感觉八辈子没写过题解了。

看起来不太会 $\log$，直接考虑根号，分块维护每个点跳出块需要几次，以及跳到哪个点，这个是简单的。

$\gcd$ 最多变化 $w$ 次，直接的思路是直接找到区间 $\gcd(a_i,x) \ne 1$ 的块暴力修改，但是发现这样是 $O(nw \sqrt{n \log n})$，$w$ 是质因数个数。反正赛时第一遍写了这么个唐氏做法，没卡过去。

有点唐氏的是，第一遍没看到修改的值域 $c_i \le 2.5 \times 10^5$，贴了个 $\text{rho}$ 上去。

考虑优化，优化是简单的，参考 [P5610 [Ynoi2013] 大学](https://www.luogu.com.cn/problem/P5610)，每个质因数开一个并查集维护，每次修改直接暴力修改。

默认 $n,q$ 同阶，总复杂度 $O(wnB + \dfrac{n^2}{B} + n \log^2 V)$，视 $w = \log V$，理论 $O(n\sqrt{n\log V} + n \log^2 V)$，$B$ 取 $80$ 左右跑得飞快，直接拿下最优解。

要代码私信，不放了。

---

## 作者：yzq_yzq (赞：2)

## 前置芝士

Ynoi 大学，以及弹飞绵羊。

---

记 $V$ 为值域。

题目其实就是要快速找到一个区间与 $x$ 的 $gcd(x,a_i) > 1$ 的位置的数并将它们除以 $\gcd$，然后做弹飞绵羊即可。

假如做过 Ynoi 大学的话就可以知道我们只需要给每个质因子维护一个链表（并查集实现）就行了，然后修改的时候把 $c$ 的质因子枚举去暴力删除就行，这个部分是 $n\log^2 V$ 的。

然后变成 $n \ln V$ 次修改的带权弹飞绵羊，套用弹飞绵羊的分块加个维护和就行，整体上是小常数根号 $\log$ 轻松过了。

不难发现 $O(n \ln V)$ 级别的修改，$O(m)$ 级别的查询可以平衡一下，$n,m$ 同阶，于是取块长 $B = \sqrt{\frac n {\ln V}}$ 就能做到 $n \sqrt {n\ln V}$ 的复杂度了。

常数相对较小，砍下了最优解。

贴个代码：

```cpp
#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = x; i <= y; ++i)
#define drep(i, x, y) for (int i = x; i >= y; --i)
#define ll long long
#define pb push_back
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int N = 250005, mod = 998244353;
int n, q; ll a[N], mul[N];
int L[N], R[N], pos[N], sq;
vector<int> fa[N], p[N];
ll w[N]; int g[N], v[N], f[N];
inline void rebuild(int b) {
	drep(i, R[b], L[b]) {
		a[i] = a[i] * mul[b] % mod;
		if(f[i] > R[b]) g[i] = f[i], w[i] = a[i];
		else {
			g[i] = g[f[i]];
			w[i] = w[f[i]] + a[i];
			if(w[i] >= mod) w[i] -= mod;
		}
	}
	mul[b] = 1;
}
inline ll qs(int x) {
	ll res = 0;
	while(x <= n) res += w[x] * mul[pos[x]] % mod, x = g[x];
	return res % mod;
}
vector<int> num;
bool vi[N];
inline void upd(int x, int y) {
	if(vi[x]) return;
	int z = __gcd(v[x], y);
	if(z > 1) {
		v[x] /= z, f[x] = x + x / v[x];
		vi[x] = 1; num.pb(x);
//		cout << "update : " << x << " " << f[x] << " to " << x + x / z << '\n';
		rebuild(pos[x]);
	}
}
int pr[N], cnt, mi[N], sz[N]; bool vis[N];
inline int find(int x, int y) {
	if(y >= sz[x] || fa[x][y] == y) return y;
	return fa[x][y] = find(x, fa[x][y]);
}
inline void prime(int n = N - 1) {
	vis[1] = 1;
	rep(i, 2, n) {
		if(!vis[i]) pr[++cnt] = i, mi[i] = i;
		rep(j, 1, cnt) {
			if(pr[j] * i > n) break;
			vis[pr[j] * i] = 1;
			mi[pr[j] * i] = pr[j];
			if(i % pr[j] == 0) break;
		}
	}
}
inline void update(int l, int r, int c) {
	int lst = c;
	num.clear();
	while(c > 1) {
		int x = mi[c];
		auto y = lower_bound(p[x].begin(), p[x].end(), l);
		while(c % x == 0) c /= x;
		if(y == p[x].end()) continue;
		int u = y - p[x].begin();
		for(int i = find(x, u); i < sz[x] && p[x][i] <= r; i = find(x, i + 1)) {
			int v = p[x][i];
			upd(v, lst);
			if(::v[v] % x) fa[x][i] = i + 1;
		}
	}
	for(int x : num) vi[x] = 0;
	c = lst;
	rep(i, pos[l] + 1, pos[r] - 1) mul[i] = mul[i] * c % mod;
	if(pos[l] == pos[r]) { rep(i, l, r) a[i] = a[i] * c % mod; rebuild(pos[l]); }
	else {
		rep(i, l, R[pos[l]]) a[i] = a[i] * c % mod; rebuild(pos[l]);
		rep(i, L[pos[r]], r) a[i] = a[i] * c % mod; rebuild(pos[r]);
	}
}
int main() {
	IOS;
	prime();
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i], v[i] = i / __gcd(1ll * i, a[i]);
	sq = sqrt(n) / 8.5;
	sq = max(sq, 1);
	rep(i, 1, n) pos[i] = (i - 1) / sq + 1;
	rep(i, 1, pos[n]) L[i] = (i - 1) * sq + 1, R[i] = min(n, i * sq), mul[i] = 1;
	rep(i, 1, n) {
		int x = v[i];
		f[i] = i / v[i] + i;
		while(x > 1) {
			int p = mi[x];
			fa[p].pb(fa[p].size());
			::p[p].pb(i);
			while(x % p == 0) x /= p;
		}
	}
	rep(i, 1, pos[n]) rebuild(i);
	rep(i, 2, N - 1) {
		if(p[i].size()) {
			sz[i] = p[i].size();
			rep(j, 0, sz[i] - 1) fa[i][j] = j;
		}
	}
	while(q--) {
		int op, x, y, z;
		cin >> op >> x;
		if(op == 1) {
			cin >> y >> z;
			update(x, y, z);
		} else cout << qs(x) << '\n';
	}
	return 0;
}
``

---

## 作者：Aegleseeker_ (赞：1)

不难，但是写起来比较恶心的题。

首先我们观察到这个 $i+\gcd(i,a_i)$ 很难直接维护，考虑分块。类比弹飞绵羊一题的思路，我们令 $pos_i$ 代表从 $i$ 开始跳，跳出 $i$ 所在块外的第一个点；令 $sum_i$ 代表此时的代价。有一个显然的转移：

$$pos_i=\begin{cases}i+\gcd(i,a_i)&i+\gcd(i,a_i)>R_i\\pos_{i+\gcd(i,a_i)}&i+\gcd(i,a_i)\le R_i\end{cases}$$

$$sum_i=\begin{cases}a_i&i+\gcd(i,a_i)>R_i\\sum_{i+\gcd(i,a_i)}+a_i&i+\gcd(i,a_i)\le R_i\end{cases}$$

其中 $R_i$ 代表 $i$ 所在块的右端点。

因此，我们可以在 $O(B)$ 的复杂度内重构一个块，求出该块中所有元素的 $pos_i,sum_i$。但是由于每次修改需要对 $O(\frac{n}{B})$ 个块进行重构，所以复杂度不对。

考虑什么时候需要重构一个块，我们这里将 $a_i$ 和 $g_i=\gcd(i,a_i)$ 当成两个东西看待，即当不影响 $\gcd$ 的值时，我们只需要对 $a_i$ 区间乘就行，这个可以通过整块打 tag 解决。

也就说，我们需要重构一个块，当且仅当存在块内的某个数的 $g_i$ 会发生变化。利用势能线段树的思想，我们可以同样想到利用势能分块来解决此题。这类势能的题目的本质是，在修改、重构的复杂度不可避免时，考虑一个位置被 **有效修改次数的上界**，从而找到一些规避无效浪费复杂度的做法。

对于一个位置 $i$，不难发现由于区间乘会使 $a_i$ 不降，因此当某个时刻 $g_i=i$ 时，此时 $\gcd(i,a_i)=i$，后续时刻这个 $g$ 就不会在变化了，就可以根据上文提到的方法打 tag 了。问题转换成，位置 $i$ 会被有效操作多少次才能使得 $g_i=i$？

考虑「有效操作」的定义，即乘完之后 $\gcd$ 改变，不难发现次数乘上去的这个 $c$ 一定是 $i$ 的因数，且 $i$ 与 $a_i$ 中这个因数的次数不同，不然乘完之后不会有变化。$\gcd$ 又启发我们，**将因数刻画为质因数**，「有效操作」可以被质因数分解刻画成：存在某个质数 $p$ 使得 $P(i)$ 中 $p$ 出现次数大于 $P(a_i)$ 中 $p$ 出现次数，且 $P(c)$ 中 $p$ 的出现次数 $\ge 1$。其中 $P(x)$ 是 $x$ 质因数分解后构成的可重集。

因此，我们发现**一个数至多被「有效操作」$|P(i)|$ 次**。则这 $n$ 个数总共会被操作 $\sum\limits_{i=1}^n|P(i)|$ 次。根据埃式筛的复杂度分析，可以证明这个式子是 $O(n\ln \ln n)$ 量级的。至此势能分析部分全部完毕，接下来考虑维护「有效操作」的方式以及块长的取值。

对于每个质数，我们开一个二元组 `set`，存储所有对于该位置、乘上这个质数是「有效操作」的位置以及还可以乘这个质数作为「有效操作」的次数。形式化的，令 $s_i$ 代表质数 $i$ 的集合，则其中存的是：

$$\Bigg\{ (x,y)\Big | \Big(\sum\limits_{u\in P(x)}[u=i]\Big)-\Big(\sum\limits_{u\in P(a_x)}[u=i]\Big)=y,y>0\Bigg\}$$

对于一次询问，我们先做一个正常的分块，即对散块的处理、整块的打 tag，把 $a_i$ 处理好。然后考虑更新所有需要更新的 $g_i$。将 $c$ 质因数分解，对于一个质因数 $p$，我们考虑直接暴力枚举 $s_p$ 中二元组第一维在 $[l,r]$ 之间的所有位置，对 $g$ 进行更新，并存下这些位置所对应的所有块。最后我们对这些所有块都进行 $O(B)$ 的重构即可。

查询时，由于我们的 $sum_i$ 维护的是整块的值，因此可以直接把 tag 乘上去，即 $sum_i\times tag_i$。注意处理散块时不管是不是有效操作都要对块进行重构，因为你没有打 tag，但是改变了这个块 $pos_i,sum_i$ 的值。

最后来分析复杂度。两部分复杂度分别为 $O(Bn\ln \ln n)$ 以及 $O(q\times \frac{n}{B})$，不难注意到最小值取在 $B=\sqrt \frac{q}{\ln \ln n}$，有最终复杂度 $O(n\sqrt {q\ln \ln n})$。实现时可以把块长定到 $250$ 左右。`set` 部分常数很小且实现优秀可以忽略到其本身的复杂度，因此这里不考虑其复杂度的代价。

submission：https://www.luogu.com.cn/record/225679451

---

## 作者：littlebug (赞：1)

当**有效**操作的数量非常有限时，分块是一个很好的选择。

不过细节还是太多了。

## Solution

注意到当 $a_i$ 的质因数足够丰富的时候，$\gcd(i,a_i) = i$，所以考虑记录每个 $i$ 剩余的（即 $a_i$ 没有的）因数，过程中顺便可以维护 gcd。

因为 $c_i$ 与 $n$ 同阶，于是先预处理出值域内所有数的质因数。然后维护一个 tag，$f_{i,j}$ 表示块 $i$ 内的第 $j$ 个质因数是否还有剩余。这样就可以避免很多的无效操作了。

每次修改散块暴力，整块看看 $k$ 的质因数在块 $i$ 有没有剩余，如果有就直接重构，没有就打上乘法 tag。

关于查询，可以维护 $nxt_i$ 表示 $i$ 往后延伸到的第一个块外的位置，$s_i$ 表示 $i$ 在块内延伸到的所有数之和，这两个东西显然后缀扫一遍就可以算出来。

复杂分析度（均从整体考虑）：

- 修改：
  - 散块显然是 $O(q \times B)$。
  - 整块可以从每个质因数产生了多少贡献这个角度来考虑，直观感觉就是 ln ln 的，具体分析见[这篇题解](https://www.luogu.com.cn/article/y288ujii)。复杂度 $O(B \times n \ln \ln n)$。
- 查询显然是 $O(q \times \frac n B)$。

所以 $B = \sqrt {n \ln \ln n}$ 最优，不过这题很良心，一点也不卡常，$\sqrt n$ 也能过。

## Code

注意散块操作的时候，$f_{i,j}$ 应该在整个块判断，而不是只看被操作的部分，也不知道谁因为这个调了 3days。

```cpp
bitset <N+100> isp;
vector <int> ps,fac[N+100];
il void get_primes(int n)
{
	isp=0,clr(ps);
	rep(i,2,n)
	{
		isp[i] || (ps.pb(i),fac[i].pb(i),1);
		for(int j=0;j<ps.size() && i*ps[j]<=n;++j)
		{
			isp[i*ps[j]]=1,(fac[i*ps[j]]=fac[i]).pb(ps[j]);
			if(!(i%ps[j])) break;
		}
	}
}
inline int gcd(int a,int b){if(!(a|b)) return a?a:b; while(b^=a^=b^=a%=b); return a;}

const int B=250;
int n,q,a[N],bl[N],L[N/B+5],R[N/B+5],s[N],nxt[N],tag[N/B+5],g[N],pid[N+100];
bitset <22100> f[N/B+5];
map <int,int> c[N],cbl[N/B+5];

il void reset(int l,int r,int k,bool op)
{
	int id=bl[l];
	
	if(k>0)
	{
		if(l==L[id] && r==R[id]) tag[id]=mod_(tag[id]*k);
		else 
		{
			rep(i,l,r) a[i]=mod_(a[i]*k);
			op=1;
		}
		
		for(auto p:fac[k]) if(f[id][pid[p]])
		{
			op=1;
			rep(i,l,r) if(c[i].count(p))
			{
				--c[i][p],--cbl[id][p],g[i]*=p;
				c[i][p] || c[i].erase(p);
			}
			f[id][pid[p]]=cbl[id][p];
			cbl[id][p] || (cbl[id].erase(p));
		}
	}
	
	if(op) rpe(i,R[id],L[id])
	{
		nxt[i]=(i+g[i]>R[id] ? i+g[i] : nxt[i+g[i]]);
		s[i]=(i+g[i]>R[id] ? a[i] : mod_(a[i]+s[i+g[i]]));
	}
}

il void upd(int l,int r,int k)
{
	if(bl[l]==bl[r]) return reset(l,r,k,0);
	
	reset(l,R[bl[l]],k,0),reset(L[bl[r]],r,k,0);
	rep(i,bl[l]+1,bl[r]-1) reset(L[i],R[i],k,0);
}

il int query(int x)
{
	int ans=0;
	while(x<=n) add(ans,mod_(s[x]*tag[bl[x]])),x=nxt[x];
	return ans;
}

il void solve()
{
	read(n,q),_::r(a,n);
	
	rep(i,1,n) bl[i]=(i+B-1)/B;
	rep(i,1,bl[n]) L[i]=(i-1)*B+1,R[i]=i==bl[n]?n:i*B,tag[i]=1;
	
	get_primes(N+50);
	rep(i,0,(int)ps.size()-1) pid[ps[i]]=i+1;
	rep(i,1,n)
	{
		g[i]=gcd(i,a[i]);
		for(auto p:fac[i/g[i]]) ++c[i][p],++cbl[bl[i]][p],f[bl[i]][pid[p]]=1;
	}
	rep(i,1,bl[n]) reset(L[i],-1,-1,1);
	
	int op,l,r,k;
	while(q--)
	{
		read(op);
		if(op==1) read(l,r,k),upd(l,r,k);
		else read(k),write(query(k),'\n');
	}
}
```

---

华风夏韵，洛水天依！

---

## 作者：wwwwwza (赞：0)

思路比较显然，分块。

对于每个 $\gcd(x,a_x)$ 最多变化 $x$ 分解质因数的每个质数的指数和，比 $O(\log n)$ 小一点，我们就当它是 $O(\log n)$ 算。

每一次修改 $\gcd(x,a_x)$，就对 $x$ 所在的块暴力重构，每一个数最多被改 $O(\log n)$ 次，每次重构是 $O(\sqrt{n})$ 的，所以时间复杂度可以做到 $O(n\sqrt{n}\log n)$，改一下块长可以做到 $O(n\sqrt{n\log n})$。

对于每一个 $x$，存下 $\frac{x}{\gcd(x,a_x)}$ 含哪些质因数，每次修改的之后直接改即可，用 set 的时间复杂度是 $O(\log n)$，不过每次修改只用查乘上的数的质因数个数次，差不多是 $O(n\log^2 n)$。

~~不是最劣解。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2.5e5+5;
const int inf=2.5e5;
const int M=300;
const int mod=998244353;
int n,m,a[N],opt,l,r,c;
int id[N],nxt[N],jmp[N],del[N],flag[N];
int V,pos[N],L[N],R[N],sum[N],tag[N];
int prime[N],bac[N],tot=0,vis[N];
set<int>s[22100];
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
void init(){
	V=(n-1)/M+1;
	for(int i=1;i<=V;i++)L[i]=R[i-1]+1,R[i]=i*M;
	R[V]=n;
	for(int i=1;i<=V;i++){
		tag[i]=1;
		for(int j=L[i];j<=R[i];j++)pos[j]=i;
	}
	for(int i=2;i<=inf;i++){
		if(!vis[i])prime[++tot]=i,bac[i]=tot;
		for(int j=1;j<=tot&&i*prime[j]<=inf;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
void build(int i){
	for(int j=R[i];j>=L[i];j--){
		sum[j]=a[j];
		jmp[j]=nxt[j]+j;
		if(jmp[j]<=R[i])sum[j]+=sum[jmp[j]],jmp[j]=jmp[jmp[j]];
		sum[j]%=mod;
	}
}
void upd(int l,int r,int c){
	for(int i=l;i<=r;i++){
		a[i]=1ll*a[i]*c%mod;
		nxt[i]*=gcd(id[i],c);
		id[i]/=gcd(id[i],c);
	}
}
void calc(int l,int r,int now,int p){
	if(s[bac[p]].empty())return;
	set<int>::iterator it=s[bac[p]].lower_bound(l);
	if(it==s[bac[p]].end())return;
	int top=0;
	while(it!=s[bac[p]].end()&&*it<=r){
		int t=*it;
		nxt[t]*=gcd(id[t],now);
		id[t]/=gcd(id[t],now);
		if(id[t]%p!=0)del[++top]=t;
		flag[pos[t]]=1;
		it++;
	}
	for(int i=1;i<=top;i++)s[bac[p]].erase(del[i]);
	for(int i=pos[l];i<=pos[r];i++){
		if(flag[i])build(i);
		flag[i]=0;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >>n>>m;
	init();
	for(int i=1;i<=n;i++){
		cin >>a[i];
		nxt[i]=gcd(i,a[i]);
		c=id[i]=i/nxt[i];
		for(int j=1;prime[j]*prime[j]<=c;j++){
			if(c%prime[j]==0)s[j].insert(i);
			while(c%prime[j]==0)c/=prime[j];
		}
		if(c!=1)s[bac[c]].insert(i);
	}
	for(int i=1;i<=V;i++){
		build(i);
	}
	while(m--){
		cin >>opt;
		if(opt==1){
			cin >>l>>r>>c;
			if(pos[l]==pos[r])upd(l,r,c),build(pos[l]);
			else{
				upd(l,R[pos[l]],c),upd(L[pos[r]],r,c);
				build(pos[l]),build(pos[r]);
				if(pos[l]+1==pos[r])continue;
				for(int i=pos[l]+1;i<=pos[r]-1;i++)tag[i]=1ll*tag[i]*c%mod;
				for(int i=1;prime[i]*prime[i]<=c;i++){
					int now=1;
					while(c%prime[i]==0)now*=prime[i],c/=prime[i];
					if(now!=1)calc(R[pos[l]]+1,L[pos[r]]-1,now,prime[i]);
				}
				if(c!=1)calc(R[pos[l]]+1,L[pos[r]]-1,c,c);
			}
		}else{
			cin >>c;
			int ans=0;
			while(c<=n){
				ans=(ans+1ll*sum[c]*tag[pos[c]]%mod)%mod;
				c=jmp[c];
			}
			cout <<ans<<"\n";
		}
	}
	return 0;
}

```

---

## 作者：CarroT1212 (赞：0)

场上三个人会这题不会 G，三辈子都有了。

首先，由于 $\gcd(i,a_i)$ 只增不减，而 $i$ 的质因子个数有限，对每个 $i$ 的 $\gcd(i,a_i)$ 的有效更新次数不会超过 $\log i$ 次。所以每次区间乘的时候只要精准跳过不会更新的 $i$，就可以将对于 $\gcd(i,a_i)$ 的更新看成最多 $n\log$ 次单点修改。这个维护各种东西的质因子精细实现即可做到。

而这个从 $i$ 到 $i+\gcd(i,a_i)$ 问路径信息的东西看起来有种[弹飞绵羊](https://www.luogu.com.cn/problem/P3203)的内味。考虑分块，将序列分为 $\sqrt{n}$ 块，每块分别 DP 预处理从块上的每个位置开始跳对答案的贡献以及会跳到哪。单点修改的时候对于单个块暴力重新 DP 一次，查询的时候暴力跳大块。貌似做完了？

哦不，这题问的是路径上的 $a_i$ 和，那就不完全能等效为单点修改了，还有一个对 $a_i$ 的区间乘修改。那会影响到原本的分块信息，这……问题不大，考虑一起分块，每次区间乘对于两边的散块暴力更新 $a_i$，并把这俩散块在修改的时候一起 DP 重构了，而大块直接打个 tag，暴力跳查询的时候记得把遇到的大块答案乘个 tag。

$O((n\log n+q)\sqrt{n})$，其实貌似是 $\log\log$，反正常数很小。块长 $300$ 1.4s 通过。

```cpp
const ll J=1e18,N=2.5e5+7,B=300,P=998244353;
ll qp(ll x,ll y=P-2) { return y?(y&1?x:1)*qp(x*x%P,y>>1)%P:1; }
ll n,q,a[N],b[N],c[N];
ll vis[N]; vector<pll> v[N];
set<ll> s[N];
struct sgt {
	ll c[N],sum[N];
	void ini(ll n,ll *a) { for (ll i=1;i<=n;i++) c[i]=a[i],sum[i]=1; }
	void mul(ll l,ll r,ll x) {
		ll sl=(l-1)/B+1,sr=(r-1)/B+1;
		if (sl==sr) for (ll i=l;i<=r;i++) (c[i]*=x)%=P;
		else {
			for (ll i=l;i<=sl*B;i++) (c[i]*=x)%=P;
			for (ll i=r;i>(sr-1)*B;i--) (c[i]*=x)%=P;
			for (ll i=sl+1;i<sr;i++) (sum[i]*=x)%=P;
		}
	}
	ll que(ll x) { return c[x]*sum[(x-1)/B+1]%P; }
} T;
struct nod { ll fi,se,th; } dp[N];
void upd(ll o) {
	ll l=(o-1)*B+1,r=min(o*B,n);
	for (ll i=r;i>=l;i--) {
		ll x=T.c[i],y=i+b[i];
		dp[i]=y>r?(nod){i,x,1}:(nod){dp[y].fi,(dp[y].se+x)%P,dp[y].th+1};
	}
}
void mian() {
	for (ll i=2;i<N;i++) if (!vis[i]) {
		v[i].pb({i,1});
		for (ll j=i+i;j<N;j+=i) {
			vis[j]=1,v[j].pb({i,0});
			for (ll x=j;x%i==0;x/=i) v[j].back().se++;
		}
	}
	scanf("%lld%lld",&n,&q);
	for (ll i=1;i<=n;i++) {
		scanf("%lld",&a[i]),b[i]=__gcd(i,a[i]),c[i]=i/b[i];
		for (pll j:v[c[i]]) s[j.fi].insert(i);
	}
	T.ini(n,a);
	for (ll i=1;(i-1)*B+1<=n;i++) upd(i);
	for (ll opt,l,r,x;q--;) {
		scanf("%lld",&opt);
		if (opt==1) {
			scanf("%lld%lld%lld",&l,&r,&x);
			T.mul(l,r,x);
			set<ll> has;
			for (pll i:v[x]) {
				vector<ll> vv;
				for (auto it=s[i.fi].lower_bound(l);it!=s[i.fi].end()&&*it<=r;it++) {
					ll x=*it;
					for (ll j=1;j<=i.se&&c[x]%i.fi==0;j++) c[x]/=i.fi,b[x]*=i.fi;
					if (c[x]%i.fi!=0) vv.pb(x);
					has.insert((x-1)/B+1);
				}
				for (ll j:vv) s[i.fi].erase(j);
			}
			has.insert((l-1)/B+1),has.insert((r-1)/B+1);
			for (ll i:has) upd(i);
		}
		else {
			scanf("%lld",&x);
			ll ans=0;
			while (x<=n)
				(ans+=dp[x].se*T.sum[(x-1)/B+1])%=P,x=dp[x].fi,x+=b[x];
			cout<<ans<<"\n";
		}
	}
}
```

---

