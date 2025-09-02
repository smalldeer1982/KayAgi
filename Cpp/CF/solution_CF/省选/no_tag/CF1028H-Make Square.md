# Make Square

## 题目描述

我们称一个数组 $b_1, b_2, \ldots, b_m$ 是好的，如果存在两个下标 $i < j$，使得 $b_i \cdot b_j$ 是一个[完全平方数](https://en.wikipedia.org/wiki/Square_number)。

给定一个数组 $b_1, b_2, \ldots, b_m$，你每次操作可以执行以下两种之一：

- 将任意一个元素 $b_i$ 乘以任意一个质数 $p$；
- 如果 $b_i$ 能被质数 $p$ 整除，则将 $b_i$ 除以 $p$。

记 $f(b_1, b_2, \ldots, b_m)$ 为将数组 $b$ 变为好的所需的最少操作次数。

现在给定一个长度为 $n$ 的整数数组 $a_1, a_2, \ldots, a_n$，以及 $q$ 个询问，每个询问为 $l_i, r_i$。对于每个询问，输出 $f(a_{l_i}, a_{l_i + 1}, \ldots, a_{r_i})$。

## 说明/提示

在第一个样例的第一个询问中，你可以将第二个数乘以 $7$ 得到 $259$，再将第三个数乘以 $37$ 得到 $1036$。此时 $a_2 \cdot a_3 = 268\,324 = 518^2$。

在第二个询问中，子数组已经是好的，因为 $a_4 \cdot a_6 = 24^2$。

在第三个询问中，你可以将 $50$ 除以 $2$ 得到 $25$。此时 $a_6 \cdot a_8 = 30^2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
10 10
34 37 28 16 44 36 43 50 22 13
1 3
4 8
6 10
9 10
3 10
8 9
5 6
1 4
1 7
2 6
```

### 输出

```
2
0
1
3
0
1
1
1
0
0
```

# 题解

## 作者：luogubot (赞：1)

定义一个序列 $b$ 是优秀的，当且仅当存在 $i<j,b_i\times b_j$ 是完全平方数。定义序列 $b$ 上的一次操作为任意选择一个 $b$ 中的元素，将其乘/除以一个质数 $p$（除法要求整除）。

给定序列 $a_{1\cdots n}$，$q$ 次询问区间 $[l,r]$ 组成的序列至少进行多少次操作才能变成优秀的。

$n\leq 2\times 10^5$，$q\leq 10^6$，$1\leq a_i\leq 5\times 10^6$，$l<r$，7s，1G。

预处理去掉每个数的平方因子，则此时每个数的 $\omega \leq7$。记 $t_i$ 表示 $i$ 的质因子个数，则两个数 $x,y$ 要操作 $t_x+t_y-2t_{\gcd(x,y)}$ 次才能满足 $x\times y$ 是完全平方数。

考虑若 $a|b$，则 $t_a\leq t_b$，要最小化 $t_x+t_y-2t_{\gcd}$，则如果只处理一次询问，可以枚举 $d|x,d|y$ 统计 $t_x+t_y-2t_d$ 的最小值。

枚举 $d$ 拉出序列中 $d$ 的倍数，注意到处理后的 $a_i$ 不含平方因子，则其因子个数为 $2^\omega\leq 128$ 个，则总共只有 $128n$ 次被拉出来统计。对于确定的 $d$，希望最小化 $t_x+t_y$，也就是需要找到最小和次小的 $t$。

对于一次询问，暴力地统计其中的最小值和次小值。对于多次询问，考虑真正有贡献的（最小值，次小值）点对实际只有 $O(len)$ 对。具体地，枚举次小值所在的位置，找到其左，右第一个比自己小的作为最小值，则每个区间的情况都被包含了。正确性考虑截取其中的一个区间 $[l,r]$，找到区间最小值，则区间里的次小值会找到它作为某一边第一个比自己小的数计入答案。则问题转为区间包含的线段的最小权值，容易离线扫描线。

线段有 $2^8n\leq 5\times 10^7$ 个，而询问只有 $10^6$ 个，扫描线时需要支持的操作是单点修改，后缀求 $\min$。注意到答案首先不超过 $14$，那么可以改为前缀取 $\min$ 和单点查值，前缀取 $\min$ 则值单调不降，暴力地往前更新 $f$ 值直到不能更新，则更新次数容易均摊到 $2\omega n\leq 14n$，这样统计答案的部分就快了不少。

单调栈部分复杂度是 $O(2^\omega n)$，统计答案部分复杂度是 $O(2^\omega n+q+\omega n)$，则总复杂度是 $O(\omega2^\omega n+q+V\times \omega)$。

不卡常，实现比较简陋。[Submission](https://codeforces.com/contest/1028/submission/178756057)。

---

## 作者：FxorG (赞：0)

考虑把每个数质因数分解，每个质数指数模 $2$，对于 $x,y$ 的答案是什么？是不是假如 $2$ 边的质数指数只有 $1$ 个为 $1$ 的质数个数。

具体的，记 $f_x$ 为 $x$ 分解后指数模 $2$ 为 $1$ 的个数，那么 $f_x+f_y$ 是不是 $2$ 边同时为 $1$ 就不需要减去？如何保留 $2$ 边共同的 $1$？显然 $\gcd(x,y)$，所以 $ans=f_x+f_y-2f_{\gcd(x,y)}$。

考虑 $5\times 10^6$ 内质数个数最多 $7$ 个，因为从 $2$ 开始连续 $8$ 个质数积大于 $5\times 10^6$。

那么 $\max\{d(a_i)\}=2^7,i\in n$。

接下来自然想到枚举 $\gcd$，因为每个数的约数不多，显然需要上一个数 $y,d\mid a_y$ 的位置，又因为答案跟 $f$ 有关，$f$ 最大为 $7$，考虑扫描线，到 $i$ 时枚举约数，再定义 $f_{i,j}$ 为当前扫描下， $\gcd$ 为 $j$ 时，满足 $j\mid a_x$ 的最大 $x$。那么只要枚举一下就好了，接下来变成一个更新操作有 $n\times7\times128$ 次，查询操作有 $m$ 次的单点更新，区间最小值，发现是不平衡的。我们直接使用 $O(1)$ 修改，$O(\sqrt{n})$ 查询分块即可。

这里补一个东西：

假如 $\gcd(x,y)=d$，但是枚举到 $k,k\mid d$ 时，因为 $f_k<f_d$ 所以显然不会对最小值有影响。

不过确实跑的挺慢的（发现忘了关同步流，关了之后还是能在时限一半内通过的）。

```cpp
#include <bits/stdc++.h>
//#define int long long
#define pb push_back
using namespace std;
const int N=(int)(1e6+5),M=5040000;
bool vis[M];
int pri[M>>1],cnt;
int n,m,a[N],f[M];

namespace MI {
	int mi[1000],val[N],id[N],bl,L[1000],R[1000];
	void init() {
		bl=sqrt(n);
		for(int i=1;i<=n;i++) id[i]=(i-1)/bl+1;
		for(int i=1;i<=id[n];i++) mi[i]=0x3f3f3f3f,L[i]=(i-1)*bl+1,R[i]=i*bl; R[id[n]]=n;
		for(int i=1;i<=n;i++) val[i]=0x3f3f3f3f;
	}
	void upt(int x,int v) {
		val[x]=min(val[x],v);
		mi[id[x]]=min(mi[id[x]],v);
	}
	int qry(int l,int r) {
		if(id[l]==id[r]) {
			int res=0x3f3f3f3f;
			for(int i=l;i<=r;i++) res=min(res,val[i]);
			return res;
		} else {
			int res=0x3f3f3f3f;
			for(int i=l;i<=R[id[l]];i++) res=min(res,val[i]);
			for(int i=id[l]+1;i<id[r];i++) res=min(res,mi[i]);
			for(int i=L[id[r]];i<=r;i++) res=min(res,val[i]);
			return res;
		}
	}
}

void init() {
	for(int i=2;i<=M-5;i++) {
		if(!vis[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<=M-5;j++) {
			vis[i*pri[j]]=1;
			if(i%pri[j]==0) break ; 
		}
	}
}

int gcd(int x,int y) {
	return !y?x:gcd(y,x%y);
}
vector<pair<int,int> >vec[N];
int tmp[10],ans[N*5],sum[N],st[20][N];
vector<int>vecd[N]; 

inline int qry(int l,int r) {
	int qwq=log2(r-l+1);
	return min(st[qwq][l],st[qwq][r-(1<<qwq)+1]);
}

int mp[8][M];
signed main() {
	cin.tie(0); ios::sync_with_stdio(false);
	cin>>n>>m; init();
	for(int i=1;i<=n;i++) {
		int x,sz=0; cin>>x; int res=1;
		for(int j=1;j<=cnt&&pri[j]*pri[j]<=x;j++) {
			if(x%pri[j]) continue ;
			int qwq=0;
			while(x%pri[j]==0) x/=pri[j],++qwq;
			if(qwq&1) tmp[++sz]=pri[j],res*=pri[j];
		}
		if(x!=1) res*=x,tmp[++sz]=x;
		for(int S=1;S<=(1<<sz)-1;S++) {
			int qwq=1;
			for(int j=0;j<sz;j++) {
				if((S>>j)&1) {
					qwq*=tmp[j+1];
				}
			}
//			++mp[qwq]; if(mp[qwq]==2) vecd.pb(qwq);
			vecd[i].pb(qwq);
		}
		vecd[i].pb(1);
		if(res!=1) a[i]=res;
	}
	for(int i=1;i<=M-5;i++) {
		int x=i,num=0;
		for(int j=1;j<=cnt&&pri[j]*pri[j]<=x;j++) {
			if(x%pri[j]) continue ;
			int qwq=0;
			while(x%pri[j]==0) x/=pri[j],++qwq;
			if(qwq&1) ++num;
		}
		if(x!=1) ++num;
		f[i]=num;
	}
	memset(ans,0x3f,sizeof(ans));
	memset(st,0x3f,sizeof(st));
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(a[i]==0);
	for(int i=1;i<=n;i++) {
		if(!a[i]) st[0][i]=0x3f3f3f3f;
		else st[0][i]=f[a[i]];
	}
	for(int i=1;(1<<i)<=n;i++) {
		for(int j=1;j+(1<<i)-1<=n;j++) {
			st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
		}
	}
	for(int i=1;i<=m;i++) {
		int x,y; cin>>x>>y; 
		if(sum[y]-sum[x-1]>=2) ans[i]=0;
		else if(sum[y]-sum[x-1]==1) {
			ans[i]=qry(x,y);
		}
		vec[y].pb(make_pair(x,i));
	}
	MI::init();
	for(int i=1;i<=n;i++) {
		for(int d:vecd[i]) {
			for(int j=0;j<=7;j++) {
				int p=mp[j][d];
				if(p) MI::upt(mp[j][d],f[a[i]]+f[a[p]]-2*f[d]);
			}
		}
		for(int d:vecd[i]) {
			mp[f[a[i]]][d]=i;
		}
		for(auto x:vec[i]) ans[x.second]=min(ans[x.second],MI::qry(x.first,i));
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
	return 0;
}

```

---

## 作者：_szh_ (赞：0)

我们称一个数列$b$是“优秀的”，当且仅当**存在**$\ b_i*b_j(i<j) $是一个完全平方数。

给定一个数列$a$，每次询问使$a_l,a_{l+1},\cdots ,a_{r-1},a_r$这个数列成为一个“优秀的”数列至少要进行几次操作，共$q$次询问。

每一次操作，你可以将数列中的任意一个数乘以/除以一个质数$p$（除法需要保证被除数能被整除）。

$n\le2e5,q\le1e6,a_i\le5e6$

-----
将每个数的平方因子去掉，此时一个数个数不超过 $7$， 约数个数 $2^7$

记$f_x=x $的质因数个数。 

钦定两个数 $x,y$ 满足条件的操作个数即为 $f_{x}+f_{y}-2f_{gcd(x,y)}$

我们发现答案 $\le14$，而且可以枚举约数（包含了 $gcd$ ）

那么做到第 $r$ 位时

设 $pos[i][j]$ 表示 $i|a_x ,f_{a_x}=j$ 的最右的 $x$
 
$ans[i]$ 表示 $f_{a_x}+f_{a_y}-2f_{gcd(a_x,a_y)}=i(x<y\le r)$ 的最右的 $x$

转移暴力转移，询问离线枚举答案查询

```cpp
for(int i=1;i<=Q;i++)
{
	int l=read(),r=read();
	q[r].push_back(make_pair(l,i));
}
for(int i=1;i<=n;i++)
{
	for(auto v:d[i])//枚举约数
	{
		int sum=f[a[i]]-2*f[v];
		for(int j=0;j<=7;j++)ans[j+sum]=max(ans[j+sum],pos[v][j]);
		pos[v][f[a[i]]]=i;
	}	
	for(auto v:q[i])
	   	for(int j=14;j>=0;j--)
			if(ans[j]>=v.fir)lst[v.sec]=j;//询问
}
```
复杂度 $O(n*f_x*2^{f_x}+q*ans)$

实际 $ans$ 不到 $14$，仅有 $11$



---

