# Count Leaves

## 题目描述

有正整数 $n$ 和 $d$。我们按如下规则建一棵 $T_{n,d}$ 的约数树：

- 树的根节点上的数为 $n$。这是树的第 $0$ 层。
- 对于第 $i$ 层（$i=0,1,...,d-1$）的每个结点，执行如下操作：若当前节点上的数为 $x$，则 $x$ 的所有可能的不同约数为其儿子节点上的数。这些儿子节点位于第 $i+1$ 层。
- 第 $d$ 层上的点为叶子节点。

例如，$T_{6,2}$（$n=6,d=2$ 的约数树）如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2020F/fe3509981f0e7cfbf5fabd59d7e6e5b6182b6f65.png)

定义 $f(n,d)$ 为 $T(n,d)$ 的叶子节点数。

给定 $n,k,d$ ，计算 $\sum\limits_{i=1}^nf(i^k,d)$ 模 $10^9+7$ 后的答案。

注：在这个问题中，我们说 $y$ 为 $x$ 的约数当且仅当 $y\geq1$ 且存在整数 $z$ 使得 $x=y\cdot z$。

## 样例 #1

### 输入

```
3
6 1 1
1 3 3
10 1 2```

### 输出

```
14
1
53```

# 题解

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2020F)

**题目大意**

> 给定 $n,d$，构造一棵深度为 $d$ 的有根树，根节点的标号为 $n$，标号为 $x$ 的节点有 $\sigma_0(x)$ 个儿子，标号为分别为 $x$ 的每个因数。
>
> 设 $f(n,d)$ 为这棵树的叶子个数，求 $\sum_{i=1}^n f(i^k,d)$。
>
> 数据范围：$n\le 10^9,k,d\le 10^5$。

**思路分析**

先刻画 $f(n,d)$，观察 $n$ 的某个约数 $w$ 出现次数，相当于 $n$ 的每个质因子的质数逐层递减，计数路径条数，

容易发现 $f(n,d)$ 是积性函数，因此只要考虑 $f(p^c,d)$，其中 $p$ 是质数，很显然 $f(p^c,d)$ 就是 $\binom{c+d}{d}$。

因此 $w(i)=f(i^k,d)=\prod_{p^c}\binom{ck+d}d$，要算的就是这个积性函数的答案。

从小大大爆搜每个质因数，枚举 $i$ 除以最大质因子的结果，如果最大质因子出现次数 $=1$，贡献确定，只要数质数个数，相当于数 $1\sim \left\lfloor\dfrac nt\right\rfloor$ 的质数个数，Min25 筛预处理。

而最大质因子出现次数 $\ge 2$，此时这个质因子 $\le \sqrt n$，在爆搜的时候特判即可。

时间复杂度 $\mathcal O\left(\dfrac{n^{3/4}}{\log n}\right)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5,MOD=1e9+7,MAXV=3.2e6+5;
ll fac[MAXV],ifac[MAXV];
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
ll C(int x,int y) {
	if(x<0||y<0||y>x) return 0;
	return fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}
int n,K,D,B,val[MAXN];
bool isc[MAXN];
int p[MAXN],tot,m,idx1[MAXN],idx2[MAXN],g[MAXN];
inline int idx(int v) {
	return (v<=B)?idx1[v]:idx2[n/v];
}
ll f[32],ans;
void dfs(int i,int N,ll dp) {
	if(g[idx(N)]>i) ans=(ans+dp*f[1]%MOD*(g[idx(N)]-i))%MOD;
	for(int j=i+1;j<=tot&&p[j]<=N/p[j];++j) {
		for(int c=1,M=N/p[j];M>=p[j];++c,M/=p[j]) {
			ans=(ans+dp*f[c+1])%MOD;
			dfs(j,M,dp*f[c]%MOD);
		}
	}
}
void solve() {
	scanf("%d%d%d",&n,&K,&D),B=sqrt(n),tot=m=0;
	for(int i=2;i<=B;++i) {
		if(!isc[i]) p[++tot]=i;
		for(int j=1;j<=tot&&i*p[j]<=B;++j) {
			isc[i*p[j]]=true;
			if(i%p[j]==0) break;
		}
	}
	for(ll l=1,r;l<=n;l=r+1) {
		r=n/(n/l),val[++m]=n/l;
		if(val[m]<=B) idx1[val[m]]=m;
		else idx2[n/val[m]]=m;
		g[m]=val[m]-1;
	}
	for(int k=1;k<=tot;++k) {
		for(int i=1;i<=m&&1ll*p[k]*p[k]<=val[i];++i) {
			g[i]-=g[idx(val[i]/p[k])]-(k-1);
		}
	}
	for(int i=1;i<=30;++i) f[i]=C(K*i+D,D);
	ans=1,dfs(0,n,1);
	printf("%lld\n",ans);
	for(int i=1;i<=m;++i) val[i]=g[i]=0;
	for(int i=1;i<=B;++i) idx1[i]=idx2[i]=0,isc[i]=false;
}
signed main() {
	for(int i=fac[0]=1;i<MAXV;++i) fac[i]=fac[i-1]*i%MOD;
	ifac[MAXV-1]=ksm(fac[MAXV-1]);
	for(int i=MAXV-1;i;--i) ifac[i-1]=ifac[i]*i%MOD;
	int _; scanf("%d",&_);
	while(_--) solve();
	return 0;
}
```

---

