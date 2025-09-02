# Train Maintenance

## 题目描述

有 $n$ 种列车，第 $i$ 种列车每工作 $x_i$ 天就要维护 $y_i$ 天。

接下来的 $m$ 天中，每天有一个操作，分为加入一列车和删除一列车。在车刚加入的那一天，它刚维修完，即加进来的那天可以正常工作。

每一天的操作完成后，你都要回答，当前有多上车在维修？

## 说明/提示

$1\le n,m\le 2\times 10^5$。

$1\le x_i,y_i\le 10^9$。

$op=1$ 或 $op=2$。

$1\le k\le n$。

## 样例 #1

### 输入

```
3 4
10 15
12 10
1 1
1 3
1 1
2 1
2 3```

### 输出

```
0
1
0
0```

## 样例 #2

### 输入

```
5 4
1 1
10000000 100000000
998244353 1
2 1
1 2
1 5
2 5
1 5
1 1```

### 输出

```
0
0
0
1```

# 题解

## 作者：louhao088 (赞：12)

不知道大佬有没有 $\log$ 做法，蒟蒻只会根号做法。

具体的，我们用根号分治加差分思想。

先考虑加入，我们发现火车使用有 $x[i]+y[i]$ 这一循环，我们通过这个分类讨论。

我们可以很容易发现，对于 $x[i]+y[i]> \sqrt m$ 的情况，最多只会有 $\sqrt m$ 此贡献改变，贡献改变指从维修到使用，或从使用到维修。我们只要暴力修改，在差分数组上记录就可以了。时间复杂度 $O(m \sqrt m)$ 。

对于 $x[i]+y[i] \leq m$ 的情况，最多不会超过 $m$ 种 $x[i]+y[i]$，可以用一个数组记录以 $x[i]+y[i]$ 为循环，在这循环中每一天变化的贡献。对于每个加入可以 $O(1)$ 修改，统计答案枚举每个循环长度，加上此天贡献即可。时间复杂度 $O(m \sqrt m)$ 。

删除操作本质相同。

删除时要判断每个火车是否在修，若在修因对答案减 1。


------------
代码如下。


```cpp
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define re register
#define fi first
#define se second 
#define mp make_pair
const int maxn=2e5+5,M=455;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
void print(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
int n,m,a[maxn],b[maxn],c[M][M],op,t,ans=0,f[maxn],g[maxn],x;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read();t=sqrt(m);
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1;i<=m;i++)
	{
		op=read();x=read(); 
		if(op==1)
		{
			if(a[x]+b[x]>t)
			{
				f[x]=i;
				for(int j=i;j<=m;)//千万不要 j++，本人比赛时因此爆零
				{
					j+=a[x];
					if(j>m)break;g[j]++;
					j+=b[x];
					if(j>m)break;g[j]--;
				}
			}
			else
			{
				f[x]=i;
				int u=a[x]+b[x];
				c[u][i%u]--;c[u][(i+a[x])%u]++;ans++;
			} 
		}
		else
		{
			int u=a[x]+b[x];
			int h=i-f[x];
			if(h%u>a[x])ans--;
			if(h%u==0)ans--;
			if(a[x]+b[x]>t)
			{
				for(int j=f[x];j<=m;)
				{
					j+=a[x];
					if(j>m)break;g[j]--;
					j+=b[x];
					if(j>m)break;g[j]++;
				}	
			}
			else
			{
				c[u][f[x]%u]++,c[u][(f[x]+a[x])%u]--;
			}
		}
		ans+=g[i];
		for(int j=1;j<=t;j++)
		{
			ans+=c[j][i%j];
		}
		printf("%d\n",ans);
	} 
 	return 0;
}
```





---

## 作者：wmy_goes_to_thu (赞：8)

遇到这种周期性的东西，显然要想根号分治。

如果 $x+y$ 非常大，可以枚举第几个周期，数据结构维护区间加单点查询。

如果 $x+y$ 非常小，可以记录一个数组 $cnt_{i,j}$ 表示模 $i$ 余 $j$ 有多少价值。

然后，如果你发现用树状数组维护，出题人对着根号卡，所以改成前缀和既可。

```cpp
#pragma GCC optimize(2) 
#include<bits/stdc++.h>
using namespace std;
int x[200005],y[200005];
int tim[200005],cnt[3005][3005];
int n,m,c[200005];
void add(int x,int s)
{
	if(x>m)return;
	c[x]+=s;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
		x[i]=min(x[i],m),y[i]=min(y[i],m);
	}
	int S=min(m+0.0,sqrt(m+0.5)),lst=0;
	for(int l=1;l<=m;l++)
	{
		int op,k;
		scanf("%d%d",&op,&k);
		int aa=3-2*op;
		if(op==1)tim[k]=l;
		if(x[k]+y[k]>S)
		{
			for(int i=tim[k]+x[k];i<=m;i+=x[k]+y[k])
				add(max(i,l),aa),add(max(l,i+y[k]),-aa);
		}else
		{
			for(int i=tim[k]+x[k];i<tim[k]+x[k]+y[k];i++)
				cnt[x[k]+y[k]][i%(x[k]+y[k])]+=aa;
		}
		int ans=lst+c[l];
		lst=ans;
		for(int i=1;i<=S;i++)ans+=cnt[i][l%i];
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：SunnyYuan (赞：5)

我们以 $\sqrt m$ 为分界点来进行平衡。

设当前在进行第 $k$ 次操作，询问 $i$。

对于 $x_i + y_i \leq \sqrt m$，可以在 $last_{x_i + y_i,day \bmod (x_i + y_i)}$ 上 $+1$，其中 $day$ 表示维修的时间，$k + x_i \leq day \leq k + x_i + y_i - 1$，输出时暴力统计即可。

对于 $x_i + y_i > \sqrt m$ 的，可以在利用差分数组在 $f_{day_1}$ 上 $+ 1$，在 $f_{day_2}$ 上 $-1$，其中 $day_1$ 表示所有的维修时间的开始时间，$day_2$ 表示所有维修时间的结束时间的后面一天。

时间复杂度：$O(m\sqrt m)$。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 200010, V = 450;

int n, m, s;
int st[N];
int f[N];
int last[V][V];
int x[N], y[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n >> m;
	s = sqrt(m);
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	int opt, a;
	int sum = 0;
	for (int i = 1; i <= m; i++) {
		cin >> opt >> a;
		if (opt == 1) {
			if (x[a] + y[a] > s) {
				for (int j = i + x[a]; j <= m; j += x[a] + y[a]) {
					f[j] += 1;
					if (j + y[a] <= m) f[j + y[a]] -= 1;
				}
			}
			else {
				int b = i + x[a], e = i + x[a] + y[a] - 1;
				for (int j = b; j <= e; j++) {
					last[x[a] + y[a]][j % (x[a] + y[a])]++;
				}
			}
			st[a] = i;
		}
		else {
			if (x[a] + y[a] > s) {
				for (int j = st[a] + x[a]; j <= m; j += x[a] + y[a]) {
					f[j] -= 1;
					if (j < i) sum--;
					if (j + y[a] <= m) {
					    f[j + y[a]] += 1;
					    if (j + y[a] < i) sum++;
					}
				}
			}
			else {
				for (int j = st[a] + x[a]; j < st[a] + x[a] + y[a]; j++) {
					last[x[a] + y[a]][j % (x[a] + y[a])]--;
				}
			}
		}
		sum += f[i];
		int res = sum;
		for (int j = 1; j <= s; j++) res += last[j][i % j];
		cout << res << '\n';
	}
	return 0;
}
```


---

## 作者：pengyule (赞：4)

前置知识：根号平衡思想。

算法概述：对于一些特殊的操作 $f(a)$（$a$ 代表操作参数），分 $a$ 与 $\sqrt n$ 的大小关系，一半采用暴力，一半采用特殊手段，从而使两种复杂度都为 $O(n\sqrt n)$，总复杂度 $O(n\sqrt n)$。分块思想即从此衍生而来。

> 一共 $n$ 辆火车，每辆有两个参数 $x_i,y_i$
>
> 一共有 $m$ 天，每天会有一个事件：一辆火车 $k_i$ 开始使用，或一辆火车 $k_i$ 停止使用。
>
> 一辆火车 $k$ 在使用过程中会先工作 $x_k$ 天，再维修 $y_k$ 天，再工作 $x_k$ 天，如此往复，直至它被停止使用。停止使用的那一天被视作没有被使用。
>
> 对于 $1..m$ 中每一天，求这一天有多少火车在维修。

观察到火车的使用具有周期性和区间性，分类讨论：

- $x+y>\sqrt m$
  - 不会超过 $\sqrt m$ 个“工作、维修”周期，可以直接在差分序列上对维修区间的始末打标记
- $x+y\le \sqrt m$
  - 对于火车 $k$，什么样的天 $t$ 是维修日呢？$(t-s_k)\bmod (x_k+y_k)\ge x_k$ 时（$s_k$ 表示火车 $k$ 的开始使用日期）
  - 实时维护一个大小为 $\sqrt m$ 的数组 $f$，$f_{p,q}$ 表示第 $t≡q(\bmod p)$ 天有多少辆 $x+y=p$ 的火车在维修。
  - 研究第一排的式子，设 $v=(t-s_k)\bmod (x_k+y_k)\ge x_k$，则 $v≡t-s_k$，则 $t≡v+s_k$。
  - 于是对于每一次加入的火车，将 $f_{(v+s_k)\bmod p}++,v\in[x_k,x_k+y_k) $；在每一次结束时$--$；在每一天 $1\le t\le m$ 统计 $\sum _{i\le \sqrt m}f_{i,t\bmod i}$ 为这一天的答案。

【参考代码】[CF Submission](https://codeforces.com/problemset/submission/1580/130778035)


---

## 作者：5ab_juruo (赞：3)

有 $n$ 台设备，将第 $i$ 台投入使用有 $x_i$ 的运行时间和 $y_i$ 的维护时间，两种状态交替。现在有 $m$ 的时间，每单位时间会发生两种事件之一：

- 将某台设备投入使用；
- 将某台设备报废，注意之后可以重新加入。

求每单位时间在维护的设备数。

---

简单的根号分治题，即将两个暴力综合获得复杂度优秀的做法。

当 $x_i+y_i$ 较小时，我们可以开桶，并在 $[x_i+1,x_i+y_i]$ 的区间加一，查询只需要取模即可，单步复杂度 $\mathcal{O}(x_i+y_i)$。

当 $x_i+y_i$ 较大时，注意到区间加的操作较少，我们维护差分数组，暴力修改即可，复杂度 $\mathcal{O}\left({n\over x_i+y_i}\right)$。

显然，当 $x_i+y_i\le \sqrt{m}$ 时使用方法一，否则使用方法二，这样的总复杂度是 $\mathcal{O}(m\sqrt{m})$ 的，统计时只需把两部分答案求和即可。

```cpp
const int max_n = 200000, bs = 450;

int a[max_n], b[max_n], x[max_n], y[max_n], bk[bs][bs], dif[max_n+1], ps[max_n], m;

inline void tr(int p, int v) { if (p <= m) dif[p] += v; }

signed main()
{
	int n = read(), ansd = 0;
	
	m = read();
	for (int i = 0; i < n; i++)
		x[i] = read(), y[i] = read();
	for (int i = 0, opt, tx, ansb; i < m; i++)
	{
		opt = read(), tx = read() - 1;
		if (opt == 1)
		{
			if (x[tx] + y[tx] < bs)
				for (int j = 0, tj = i + x[tx]; j < y[tx]; j++)
					bk[x[tx]+y[tx]][(j+tj) % (x[tx]+y[tx])]++;
			else
			{
				for (int j = i; j < m; j += x[tx] + y[tx])
					tr(j+x[tx], 1), tr(j, -1);
				tr(i, 1);
			}
			ps[tx] = i;
		}
		else
		{
			if (x[tx] + y[tx] < bs)
				for (int j = 0, tj = ps[tx] + x[tx]; j < y[tx]; j++)
					bk[x[tx]+y[tx]][(j+tj) % (x[tx]+y[tx])]--;
			else
			{
				for (int j = ps[tx]; j < m; j += x[tx] + y[tx])
					tr(j+x[tx], -1), tr(j, 1);
				tr(ps[tx], -1);
				if ((i - ps[tx]) % (x[tx] + y[tx]) > x[tx] || !((i - ps[tx]) % (x[tx] + y[tx])))
					ansd--;
			}
		}
		
		ansb = 0;
		for (int j = 1; j < bs; j++)
			ansb += bk[j][i%j];
		ansd += dif[i];
		printf("%d\n", ansb + ansd);
	}
	
	return 0;
}
```

---

## 作者：Stinger (赞：2)

翻译一下官方题解。

考虑对于 $x_i+y_i$ 进行根号分治。

设立一个阈值 $S$。

若 $x_i+y_i>S$，则这个列车被维修的时间段不会超过 $n/S$ 段，所以我们可以对每一段暴力地使用差分数组维护。时间复杂度 $O(\frac{m}{S})$。

若 $x_i+y_i\le S$，假设这列车 $st$ 时刻被加进来，当前时间为 $now$，当且仅当 $(t-st)\text{ mod }(x_i+y_i)\ge x_i$ 时，这列车在维修。相应的，我们可以算出 $now\text{ mod }(x_i+y_i)$ 等于多少时，这列车在维修。对于每个 $x_i+y_i$ 开一个数组，记录一下 $now\text{ mod } (x_i+y_i)$ 的每种取值对应的维修中列车数量。时间复杂度 $O(S)$。

查询的时候，答案分为两部分组成：差分数组前缀和以及数组中记录的车辆列数。时间复杂度 $O(S)$。

总时间复杂度 $O(m(S+\frac{m}{S}))$，空间复杂度 $O(n+m)$。所以，$m=\sqrt{m}$ 时时间复杂度最优，为 $O(m\sqrt{m})$。

CF 上这道题被认为卡常，个人觉得写法正常都能过吧（？），毕竟 CF 上只跑了500ms。

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>

int x[200005], y[200005], s[200005], lst[200005], *a[500], n, m, S, now;

int main() {
	scanf("%d%d", &n, &m);
	S = 0;
	for (int i = 2; i <= S; ++ i) a[i] = new int[i], memset(a[i], 0, i << 2);
	for (int i = 1; i <= n; ++ i) scanf("%d%d", x + i, y + i);
	for (int now = 1, j = 0; now <= m; j += s[++ now]) {
		int d, p, ans = 0;
		scanf("%d%d", &d, &p);
		if (d == 2) d = -1;
		if (x[p] + y[p] > S) {
			if (d == 1) {
				for (int i = now + x[p]; i <= m; i += x[p] + y[p]) {
					++ s[i];
					if (i + y[p] <= m) -- s[i + y[p]];
				}
				lst[p] = now;
			} else {
				for (int i = lst[p] + x[p]; i <= m; i += x[p] + y[p]) {
					if (i <= now) -- j;
					if (i + y[p] <= now) ++ j;
					-- s[i];
					if (i + y[p] <= m) ++ s[i + y[p]];
				}
			}
		} else {
			if (d == 1) lst[p] = now;
			for (int i = x[p]; i <= x[p] + y[p] - 1; ++ i)
				a[x[p] + y[p]][(i + lst[p]) % (x[p] + y[p])] += d;
		}
		for (int i = 2; i <= S; ++ i) ans += a[i][now % i];
		printf("%d\n", ans + j);
	}
	return 0;
}
```

---

## 作者：arrow_king (赞：1)

# 思路

看到此类的循环类操作容易想到根号分治，考虑按照 $x_i+y_i$ 与 $\sqrt m$ 的大小关系分治。

首先 $x_i+y_i$ 大于 $\sqrt m$ 的情况是简单的，考虑一段一段暴力去加，但是最多要加 $O(\sqrt m)$ 次，因此我们要把区间加的复杂度限制在 $O(1)$ 一次。联想到查询是单点查询，因此用分块维护差分数组。这部分的复杂度是 $O(\sqrt m)$。

接下来考虑 $x_i+y_i$ 小于 $\sqrt m$ 的情况。如果我们只看 $x_i+y_i=t\in[1,\sqrt m]$ 的操作，容易发现此时的数组是以 $t$ 为周期长度循环的，因此我们维护辅助数组 $s_{t,i}$ 表示在只看 $x_j+y_j=t$ 的情况下数组下标与 $i$ 模 $t$ 同余的位置被增加的值。修改的时候由于 $t\le\sqrt m$，因此暴力修改的复杂度也是 $\sqrt m$。

因为查询位置单调递增，因此不用管前面的部分，直接全局加即可。查询的时候先在大于 $\sqrt m$ 的分块查询，再到小于 $\sqrt m$ 的部分里面查表即可，查询复杂度也是 $O(\sqrt m)$。

因此总时间复杂度为 $O(m\sqrt m)$。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
#include<random>
#include<ctime>
using namespace std;
#define ll long long
#define il inline
#define sqr 452
#define N 200005
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
mt19937 Rand(time(0));
int n,m,sq;
int x[N],y[N],lst[N];
int belong[N],st[sqr],ed[sqr],sum[sqr],val[N];
int small[sqr][sqr];
il void add(int p,int x) {
	if(p>m) return;
	val[p]+=x,sum[belong[p]]+=x;
}
il int getsum(int l,int r) {
	int ans=0,bl=belong[l],br=belong[r];
	if(bl==br) {
		for(int i=l;i<=r;++i) ans+=val[i];
		return ans;
	}
	for(int i=bl;i<br;++i) ans+=sum[i];
	for(int i=st[br];i<=r;++i) ans+=val[i];
	return ans;
}
il void write(int x,bool type=1) {
	if(x==0&&type) {putchar('0');return;}
	if(x>=10) write(x/10,0);
	putchar((x%10)^48);
}
signed main() {
//	freopen("housekeep4.in","r",stdin);
//	freopen("housekeep.out","w",stdout);
	n=read(),m=read(),sq=300+Rand()%3-1;
	for(int i=1;i<=n;++i) x[i]=read(),y[i]=read();
	for(int i=1;i<=sq;++i) st[i]=ed[i-1]+1,ed[i]=(m/sq)*i;
	ed[sq]=m;
	for(int i=1;i<=sq;++i) {
		for(int j=st[i];j<=ed[i];++j) belong[j]=i;
	}
	for(int i=1,opt,k;i<=m;++i) {
		opt=read(),k=read();
		if(opt==2) opt=-1;
		if(!lst[k]) lst[k]=i;
		if(x[k]+y[k]>=sq) {
			for(int j=lst[k]-1;j<m;j+=x[k]+y[k]) {
				add(min(j+x[k]+1,m+1),opt),add(min(j+x[k]+y[k]+1,m+1),-opt);
			}
		}
		else {
			int s=x[k]+y[k],fst=lst[k]%s;//First not failed system tests
			for(int j=fst+x[k];j<fst+x[k]+y[k];++j) small[s][j%s]+=opt;
		}
		if(lst[k]!=i) lst[k]=0;
		int cnt=0;
		for(int j=1;j<sq;++j) cnt+=small[j][i%j];
		cnt+=getsum(1,i);
		write(cnt);putchar('\n');
	}
	return 0;
}
```

---

## 作者：ax_by_c (赞：1)

首先我们可以把每辆列车生效的时间记下来。

然后发现这种操作一般数据结构完全做不了，考虑根号分治。

设有一辆生效时间为 $[L,R]$ 的列车，记 $len=R-L+1$。

1.$len\ge \sqrt m$

则 $\frac {m}{len}\le \sqrt m$，利用前缀和差分，暴力即可，时间复杂度 $O(m\sqrt m)$。

2.$len\operatorname{<}\sqrt m$

仔细观察发现操作其实就是对下标模 $len$ 后在范围内且在生效区间内的位置产生 $1$ 的贡献。

那么设 $g_{i,j}$ 表示当前模 $i$ 为 $j$ 的位置能得到多少贡献。

将操作拆到 $L,R+1$ 上即可。

时间复杂度 $O(m\sqrt m)$。

综上，时间复杂度为 $O(m\sqrt m)$。

---

## 作者：Dtw_ (赞：0)

# Solution 
我的第一想法是把询问离线，这样就知道了每个火车的起始时间和终止时间，然后暴力的跳，每次跳 $x+y$，然后用差分维护一下就行。但这只有 $x + y$ 很大的时候才能做，然后就自然的想到了根号分治。

考虑 $x + y \leq B$ 的时候怎么做。

由于 $x + y$ 很小，所以可以记 $f_{i, j}$ 表示模数为 $i$ 时模 $i$ 为 $j$ 时的答案。

然后每次就可以 $O(B)$ 的转移。

具体有 $f_{x+y,j}+1$ 其中 $0\leq j \leq x+y$ 然后就做完了。

# 细节
  但是被卡了，所以考虑到 $x + y \leq B$ 的跑的很满，但是 $x + y > B$ 的跑不满，所以可以适当降低 $B$，这里我的 $B = \sqrt \frac{m}{2}$。但是，我还是被卡了，然后我把读入搞成超级快读就过了。
# Code
只放调整阈值之后还是 T 的代码，把读入换一下就行，因为超级快读太长了，就不放了。

放一个大佬的超级快读 [this](https://www.luogu.com/paste/bmanisb6)。
```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define fi first
#define se second

#define int long long

#define pii pair<int, int>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n, m, id[N], f[500][500];

int x[N], y[N], s[N];

signed main()
{
	fst
	cin >> n >> m;
	int B = sqrt(m / 2);
	for (int i=1; i<=n; i++) cin >> x[i] >> y[i];
	for (int i=1; i<=m; i++)
	{
		int op, k;
		cin >> op >> k;
		int p = (x[k] + y[k]);
		if (p <= B)
		{
			if (op == 1)
			{
				id[k] = i;
				for (int j=0; j<p; j++)
				{
					if (((j - id[k]) % p + p) % p >= x[k]) f[p][j]++;
				}
			}
			else
			{
				for (int j=0; j<p; j++)
				{
					if (((j - id[k]) % p + p) % p >= x[k]) f[p][j]--;
				}
			}
		}
		else
		{
			if (op == 1)
			{
				id[k] = i;
				for (int j=i; j+x[k]<=m; j+=p)
				{
					s[j + x[k]]++;
					if (j + p <= m) s[j + p]--;
				}
			}
			else
			{
				int l = (i - id[k]) / p;
				l = l * p + id[k];
				for (int j=l; j+x[k]<=m; j+=p)
				{
					if (j + x[k] >= i) s[j + x[k]]--;
					else s[i]--;
					if (j + p <= m)
					{
						if (j + p >= i) s[j + p]++;
						else s[i]++;
					}
				}
			}
		}
		int res = 0;
		for (int j=2; j<=B; j++) res += f[j][i % j];
		s[i] += s[i-1];
		cout << res + s[i] << endl;
	}
	return 0;
}



```

---

## 作者：small_john (赞：0)

## 思路

神仙题。

考虑根号分值。

假设当前加入第 $i$ 种火车，分两种情况讨论：

- 当 $x_i+y_i>\sqrt m$ 时，最多只有 $\sqrt m$ 个周期，所以直接暴力枚举时间即可。为了实现区间加，采用差分。这部分的时间复杂度为 $O(m\sqrt m)$。

- 当 $x_i+y_i<\sqrt m$ 时，周期中最多有 $\sqrt m$ 天，所以直接用数组 $s_{i,j}$ 表示周期为 $i$ 天，现在是周期中的第 $j$ 天的方案数。统计的话直接枚举周期天数即可，时间复杂度 $O(m\sqrt m)$。

删掉一个火车也是一样的，时间复杂度 $O(m\sqrt m)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n,m,a[N],b[N],las[N];
int c[N<<2],s[3005][3005];
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i<=n;i++)
		cin>>a[i]>>b[i],a[i] = min(a[i],m),b[i] = min(b[i],m);
	int B = sqrt(m),sum = 0;
	for(int _ = 1,op,k;_<=m;_++)
	{
		cin>>op>>k;
		op = 3-2*op;
		if(op==1) las[k] = _;
		if(a[k]+b[k]>B)
			for(int i = las[k];i<=m;i+=a[k]+b[k])
				c[max(i+a[k],_)]+=op,c[max(i+a[k]+b[k],_)]-=op;
		else for(int i = las[k]+a[k];i<las[k]+a[k]+b[k];i++)
			s[a[k]+b[k]][i%(a[k]+b[k])]+=op;
		sum+=c[_];
		int ans = 0;
		for(int i = 1;i<=B;i++) ans+=s[i][_%i];
		cout<<sum+ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16438002.html)


# 题目大意

有 $n$ 种列车，第 $i$ 种列车每工作 $x_i$ 天就要维护 $y_i$ 天。

接下来的 $m$ 天中，每天有一个操作，分为加入一列车和删除一列车。在车刚加入的那一天，它刚维修完，即加进来的那天可以正常工作。

每一天的操作完成后，你都要回答，当前有多上车在维修？

# 题目分析

根号分治。

设定一个阈 $(yù)$ 值 $S$ 来分界。

当 $x_k+y_k\ge S$ 时，可以直接采用差分数组的方法暴力修改，可以保证修改区间不超过 $\dfrac{m}{S}$。

当 $x_k+y_k\lt S$ 时，直接朴素差分不再可行，我们不妨找找规律：

设列车 $k$ 开始工作的时间为 $st$，则维护的区间有 $[st+x_k,st+x_k+y_k-1],[st+x_k+y_k+x_k,st+x_k+y_k+x_k+y_k-1],\cdots$，归纳一下就是 $[(st+x_k)\bmod (x_k+y_k),(st-1)\bmod(x_k+y_k)]$。

所以，当前的天数 $now$ 经过处理之后就可以直接发现今天列车是否在维修即可。

# 代码

```cpp
// Problem: CF1580C Train Maintenance
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1580C
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Date:2022-07-02 06:45
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	#ifndef ONLINE_JUDGE
	#define getc getchar
	#endif
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getc();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getc();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getc();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 2e5 + 5,M = 448;
int x[N],y[N],sub[N],pos[N],cnt[M][M];
int n,m,ans,sq;
inline void update(int st,int k,int v) {
	int l = (st + x[k]) % (x[k] + y[k]),r = (st - 1) % (x[k] + y[k]);
	if (l <= r) {
		for (register int i = l;i <= r; ++ i) cnt[x[k] + y[k]][i] += v;
	} else {
		for (register int i = 0;i <= r; ++ i) cnt[x[k] + y[k]][i] += v;
		for (register int i = l;i < x[k] + y[k]; ++ i) cnt[x[k] + y[k]][i] += v;
	}
}
inline int query(int x) {
	int res = 0;
	for (register int i = 1;i <= sq; ++ i) res += cnt[i][x % i];
	return res;
}
int main(void) {
	n = read(),m = read();
	sq = sqrt(m);
	for (register int i = 1;i <= n; ++ i) {
		x[i] = read(),y[i] = read();
	}
	for (register int i = 1;i <= m; ++ i) {
		int opt = read(),k = read();
		if (opt == 1) {
			if (x[k] + y[k] >= sq) {
				for (register int j = i + x[k];j <= m;j += x[k] + y[k]) {
					sub[j] ++;
					if (j + y[k] <= m) sub[j + y[k]] --;
				}
			} else {
				update(i,k,1);
			}
			pos[k] = i;
		} else {
			if (x[k] + y[k] >= sq) {
				for (register int j = pos[k] + x[k];j <= m;j += x[k] + y[k]) {
					sub[j] --;
					if (j + 1 <= i) ans --;
					if (j + y[k] + 1 <= i) ans ++;
					if (j + y[k] <= m) sub[j + y[k]] ++;
				}
			} else {
				update(pos[k],k,-1);
			}
		}
		ans += sub[i];
		printf("%d\n",ans + query(i));
	}
	
	return 0;
}
```

---

