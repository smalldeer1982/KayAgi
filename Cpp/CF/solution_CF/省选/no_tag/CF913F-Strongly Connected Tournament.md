# Strongly Connected Tournament

## 题目描述

这是一个在All-Right城的国际象棋比赛。n个运动员被邀请参加比赛，比赛依照以下规则举办：

1. 	期初，每个运动员与其他每一个运动员比赛，他们之间没有任何关系。
2.	在比赛之后，组织者造了一副有向的完全图，这张图把每名运动员看做点，对于每对运动员他们之间有一条边：他们之间比赛的胜利者是这条边的起点，输了的人是终点。
3.	然后对原图进行缩点，之后这张图变成了由原图的强连通分量组成的一条链A1→ A2→A3→……→Ak
4. 之后对将强联通分量A1里的点放到|A1|里面，将强联通分量A2中的所有点放入|A2|里面，以此类推
5. 为了确定每个运动员在各自强联通分量中的排名，需要再在每个强联通分量中将不断地进行1-5这五个步骤，也就是说，Ai中的k个人都需要和其他的k-1个人再比赛一次。
6. 如果一个强联通分量里只有一个人，那么他已经没有对手了，那么他的水平就已经确定了，就可以不用继续进行了。


运动员们被标号为1到n，标号被用在最初的图上。我们知道运动员i能赢运动员j的概率为p（i<j）。


你需要去帮助组织比赛，求出比赛总场数的期望值。


答案显然可以表示成P/Q,答P，Q为互质的整数。且Q不等于0。
输出P乘上Q相对于998244353的逆元。


简而言之答案对998244353取模。

## 样例 #1

### 输入

```
3
1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
4 6
```

### 输出

```
142606340
```

## 样例 #3

### 输入

```
4
1 2
```

### 输出

```
598946623
```

# 题解

## 作者：cyffff (赞：17)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF913F)

$\text{update 2022.2.21}$：修正一处笔误。
## 题意
给你 $n$ 个点，其中对于所有的 $i,j(i<j)$连有一条的有向边，其中有 $p=\dfrac a b$ 的概率为 $i$ 连向 $j$。

对这张完全图缩点，并对于每个强连通分量重复执行以上操作直至只剩一个点。

求期望的连边数，对 $998244353$ 取模。

$n\le 2000$。
## 思路
nb dp 题。

我们设 $dp_i$ 表示 $i$ 个点时的期望答案。

考虑枚举最弱的强联通分量的大小，则对于这个强联通分量里的点已经构成了一张完全图，并且其它的点都打赢过这个强联通分量里的点。换句话说，如果这个强联通分量大小为 $j$，则已经连了 $j(i-j)+\dfrac{j(j-1)}2$ 条边了。

考虑需要算出 $i$ 个点组成强联通图的概率与 $i$ 个点都打赢了其中 $j$ 个点的概率，不妨分别设其为 $c_i,d_{i,j}$。

考虑一次转移，还需要在强联通分量内部和外部递归处理，列出转移方程：

$$dp_i=\sum_{j=1}^ic_jd_{i,j}\left(j(i-j)+\dfrac {j(j-1)}2+dp_j+dp_{i-j}\right)$$

但是我们发现当 $i=j$ 即这个图自己构成一个强联通分量时，$dp_i$ 会转移到自己，考虑变个形：

$$dp_i=\dfrac{\sum_{j=1}^{i-1}\left[c_jd_{i,j}\left(j(i-j)+\dfrac {j(j-1)}2+dp_j+dp_{i-j}\right)\right]+c_id_{i,i}\dfrac {i(i-1)}2}{1-c_id_{i,i}}$$

现在需要算出 $c$ 和 $d$。

考虑只要图中没有点被其它点都吊打的情况它就是强联通图，$c$ 的转移十分简单：

$$c_i=1-\sum_{j=1}^{i-1}c_jd_{i,j}$$

对于 $d$，考虑新加入一个点，如果它是输的那 $j$ 个中的一个，则它要输给 $i-j$ 个点，否则它要赢 $j$ 个点。转移也比较简单（注意边的方向与编号大小的关系）：

$$d_{i,j}=(1-p)^jd_{i-1,j}+p^{i-j}d_{i-1,j-1}$$

时间复杂度 $\Theta(n^2)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=2000+10,mod=998244353;
inline int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return res;
} 
int n,p,c[N],d[N][N],dp[N];
int main(){
	n=read();
	int a=read(),b=read();
	p=1ll*a*qpow(b,mod-2)%mod;
	d[1][0]=d[1][1]=1;
	for(int i=2;i<=n;i++){
		d[i][0]=1;
		for(int j=1;j<=i;j++)
			d[i][j]=(1ll*d[i-1][j]*qpow(mod+1-p,j)+1ll*d[i-1][j-1]*qpow(p,i-j))%mod;
	}
	for(int i=1;i<=n;i++){
		int res=0;
		for(int j=1;j<i;j++)
			res=(res+1ll*c[j]*d[i][j])%mod;
		c[i]=((1-res)%mod+mod)%mod;
	}
	for(int i=1;i<=n;i++){
		int res=0;
		for(int j=1;j<i;j++){
			int tmp=(dp[j]+dp[i-j])%mod;
			tmp=(tmp+1ll*j*(i-j))%mod;
			tmp=(tmp+1ll*j*(j-1)/2)%mod;
			res=(res+1ll*c[j]*d[i][j]%mod*tmp)%mod;
		}
		res=(res+1ll*c[i]*d[i][i]%mod*(i*(i-1)/2))%mod;
		dp[i]=1ll*res*qpow(mod+1-1ll*c[i]*d[i][i]%mod,mod-2)%mod;
	}
	write(dp[n]);
	flush();
}
```
再见 qwq~

---

## 作者：ywy_c_asm (赞：14)

血的教训：期望是可以统计贡献，**但是请务必搞清楚这部分的贡献的概率要乘啥**。~~然后就费了我大半天时间……~~

首先我们不难想到对一个竞赛图当它本身不是$SCC$的时候一定存在一个缩完点之后拓扑序最大的$SCC$，不妨称它为$lst$，显然$lst$以外的点都必须向$lst$的每个点连边，我们考虑从一个竞赛图的$lst$入手把它dp出来。

首先我们先处理出$f[i]$为i个点的竞赛图定向之后是$SCC$的概率，显然要枚举$lst$容斥，那么我们就要算$lst$与外面连的边的概率乘积。我们发现这个概率是和这条边两边的大小关系决定的，那么我们不妨**从小到大加点**，设$dp[i][j]$从小到大考虑了前i个点，我们钦定的$lst$集合里（我们并不考虑$lst$内部的连边情况，只把它当做集合）有j个点，此时$lst$与$lst$外的点连的所有边的概率乘积和。考虑第i个点是不是加入$lst$集合，那么有$dp[i][j]=dp[i-1][j-1](1-p)^{i-j}+dp[i-1][j]p^j$。那么可以发现$dp[i][j]f[j]$即为i个点的竞赛图的$lst$大小为j的概率，那么$f[i]=1-\sum_{j=1}^{i-1}dp[i][j]f[j]$。

然后我们考虑求$g[i]$为i个点的**未定向**竞赛图的期望次数，答案即$g[n]$，首先我们应该发现可能定向之后自身就是$SCC$，需要重新给自身定向，即$f[i]g[i]$，否则的话我们接着枚举$lst$，但是我们发现一个问题，$lst$以外的点该如何处理？为了解决它我们还需要搞出一个与$g$类似的$h[i]$为i个点的竞赛图，但是**它已经定过向了**（也就是不用再在这一轮比赛了）的期望次数。那么就显然有$g[i]=\frac 1{1-f[i]}(C_i^2+\sum_{j=1}^{i-1}dp[i][j]f[j](g[j]+h[i-j]))$，$h[i]=f[i]g[i]+\sum_{j=1}^{i-1}dp[i][j]f[j](g[j]+h[i-j]))$，$O(n^2)$。

上代码~

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
#define p 998244353
using namespace std;
namespace ywy {
	inline ll mi(int a, int b) {
	    ll ans = 1, tmp = a;
	    while (b) {
	        if (b & 1)
	            ans = (ans * tmp) % p;
	        tmp = (tmp * tmp) % p;
	        b >>= 1;
	    }
	    return (ans);
	}
	ll dk[4000001], dk1[4000001], dp[2001][2001], f[2001], g[2001], h[2001];
	void ywymain() {
	    int n, a, b;
	    cin >> n >> a >> b;
	    ll P = (a * mi(b, p - 2)) % p;
	    dk[0] = dk1[0] = 1;
	    if (n == 1) {
	        cout << 0 << endl;
	        return;
	    }
	    if (n == 2) {
	        cout << 1 << endl;
	        return;
	    }
	    for (register int i = 1; i <= n * n; i++) {
	        dk[i] = (dk[i - 1] * P) % p;
	        dk1[i] = (dk1[i - 1] * (p + 1 - P)) % p;
	    }
	    dp[0][0] = 1;
	    for (register int i = 1; i <= n; i++) {
	        dp[i][0] = 1;
	        for (register int j = 1; j <= i; j++) {
	            dp[i][j] = (dp[i - 1][j] * dk1[j] + dp[i - 1][j - 1] * dk[i - j]) % p;
	        }
	    }
	    for (register int i = 1; i <= n; i++) {
	        f[i] = 1;
	        for (register int j = 1; j < i; j++) f[i] = (f[i] - f[j] * dp[i][j]) % p, f[i] += p, f[i] %= p;
	    }
	    for (register int i = 3; i <= n; i++) {
	        ll cjr = (i * (i - 1)) / 2;
	        for (register int j = 1; j < i; j++) {
	            ll ywy = g[j] + h[i - j];
	            ywy *= f[j];
	            ywy %= p;
	            ywy *= dp[i][j];
	            cjr = (cjr + ywy) % p;
	        }
	        g[i] = (cjr * mi(1 + p - f[i], p - 2)) % p;
	        cjr = (f[i] * g[i]) % p;
	        for (register int j = 1; j < i; j++) {
	            ll ywy = g[j] + h[i - j];
	            ywy *= f[j];
	            ywy %= p;
	            ywy *= dp[i][j];
	            cjr = (cjr + ywy) % p;
	        }
	        h[i] = cjr;
	    }
	    cout << g[n] << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# CF913F 题解



[Problem Link](https://www.luogu.com.cn/problem/CF913F)



## 题目大意

> 给定 $n$ 个人，标号 $1\sim n$，两两比赛构造一张竞赛图，其中标号小的赢标号大的的概率是 $p$。
>
> 得到竞赛图后进行缩点，对每个大小大于 $1$ 的强连通分量重复此操作。
>
> 求最终比赛次数的期望。
>
> 数据范围：$n\le 2000$。

## 思路分析

首先想如何求某个集合在竞赛图上构成强联通分量的概率，可以看 [CF1556F](https://www.luogu.com.cn/problem/CF1556F) 这道题，在那道题中我们枚举的缩点后有向链链顶对应的 SCC，得到了如下的式子：
$$
f_{S}=1-\sum_{T\subsetneq S} f_T\times P([T\text{ win }S-T])
$$
在这道题中考虑边权的独特特性，我们设 $f_i$ 表示构成一个大小为 $i$ 的强联通分量的概率，设 $c_{i,j}$ 表示 $1\sim i$ 中挑选 $j$ 个点赢剩下的 $i-j$ 个点的概率之和得到：
$$
\begin{aligned}
f_i&=1-\sum_{j<i} f_j\times c_{i,j}\\
c_{i,j}&= (1-p)^{i-j}\times c_{i-1,j-1}+p^{j}\times c_{i-1,j}
\end{aligned}
$$
接下来考虑原问题，设 $dp_i$ 表示解决一个大小为 $i$ 的强连通分量的期望步数，枚举竞赛图缩点后链顶的 SCC 得到：
$$
dp_{i}=\sum_{j\le i} f_j\times c_{i,j}\times \left(\binom i2-\binom {i-j}2+dp_{j}+dp_{i-j}\right)
$$
注意到转移可能成环，提取出 $j=i$ 一项的贡献，根据 $dp_0=0,c_{i,i}=1$ 进一步简化式子得到：
$$
dp_i=\dfrac{1}{1-f_i}\left(f_i\times \binom i2+\sum_{j<i} f_{i}\times c_{i,j}\times \left(\binom i2-\binom{i-j}2+dp_j+dp_{i-j}\right)\right)
$$
注意到 $i>1$ 时 $f_i<1$，$i\le 1$ 时 $dp_{i}=0$，因此不用担心 $1-f_i$ 没有逆元的情况。

根据如上转移式逐步计算即可。

时间复杂度 $\mathcal O(n^2)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2005,MOD=998244353;
inline int ksm(int a,int b=MOD-2,int p=MOD) {
	int ret=1;
	while(b) ret=(b&1?ret*a%p:ret),a=a*a%p,b=b>>1;
	return ret;
}
int f[MAXN],c[MAXN][MAXN],dp[MAXN];
signed main() {
	int n,a,b,p,q;
	scanf("%lld%lld%lld",&n,&a,&b),p=a*ksm(b)%MOD,q=(MOD+1-p)%MOD;
	for(int i=0;i<=n;++i) {
		c[i][0]=1;
		for(int j=1;j<=i;++j) c[i][j]=(c[i-1][j-1]*ksm(q,i-j)+c[i-1][j]*ksm(p,j))%MOD;
	}
	for(int i=0;i<=n;++i) {
		f[i]=1;
		for(int j=1;j<i;++j) f[i]=(f[i]+MOD-f[j]*c[i][j]%MOD)%MOD;
	}
	dp[0]=dp[1]=0;
	auto e=[&](int x) { return x*(x-1)>>1; };
	for(int i=0;i<=n;++i) {
		dp[i]=e(i)*f[i]%MOD;
		for(int j=1;j<i;++j) {
			dp[i]=(dp[i]+(e(i)-e(i-j)+dp[j]+dp[i-j])%MOD*f[j]%MOD*c[i][j]%MOD)%MOD;
		}
		dp[i]=dp[i]*ksm((1+MOD-f[i])%MOD)%MOD;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

好题。

首先一个重要的观察是对于一个子图而言，将这个子图确定顺序的代价只与子图大小有关。

考虑如何来算答案，对于一个大小为 $i$ 局面，你会先花费 $i \choose 2$ 的代价然后缩点，如果缩点完只有一个点就必须重新再对这个局面做一遍，否则你就拆解到了一个子问题。

考虑到把大小为 $i$ 局面拆解为 $c_1,c_2,\dots,c_k$ 有 $\sum c_j = i$，限制等价于这 $k$ 个点之间的所有边都是前面的点指向后面的点，你发现这不太好刻画，但是如果你只把局面划分为两部分，满足两个部分之间的边全部同向，那么满足这个限制的概率是好计算的。

具体来说，我们设 $w_{i,j}$ 表示把大小为 $i$ 的子图划分为两个部分，大小分别为 $i-j,j$，满足所有边都是由 $i-j$ 的部分连向 $j$ 的部分，所有划分方案的一个划分方案中的边满足限制的概率之和。转移考虑从小往大枚举最大点加入了哪个部分，令 $P = \frac{a}{b}$，转移是 $w_{i,j} = w_{i-1,j-1} \times P^{i-j} + w_{i-1,j} \times (1-P)^j$。

然后考虑划分为两部分后如何计算对答案的贡献，我们将局面划分为两个部分，为了避免计重，我们可以认为大小为 $j$ 的部分是图上最后一个强连通分量，这样就不会计重，贡献的话考虑大小为 $j$ 的部分在之后的代价就是一个大小为 $j$ 的局面也就是 $dp_j$，大小为 $i-j$ 的部分的代价实际上是大小为 $i-j$ 且已经知道了缩点后结果的局面，代价就是 $dp_{i-j} - {i-j \choose 2}$，另外还要考虑缩点后只有一个点的可能，不妨设 $p_i$ 表示大小为 $i$ 的局面缩点后只有一个点的概率，转移与 $dp_i$ 类似，我们还是去剥去最后一个强连通分量，也就是 $p_i = 1 - \sum_{j=1}^{i-1} p_j \times w_{i,j}$，而 $dp_i$ 的转移就是 $dp_i = {i \choose 2} + \sum_{j=1}^{i-1} w_{i,j} \times p_j \times (dp_j + dp_{i-j} - {i-j \choose 2}) + p_i \times dp_i$，虽然自己转移自己了，但是没关系，移项后得到 $dp_i = \frac{{i \choose 2} + \sum_{j=1}^{i-1} w_{i,j} \times p_j \times (dp_j + dp_{i-j} - {i-j \choose 2})}{1-p_i}$。

直接做是 $O(n^2 \log n)$ 的，可以通过，但是也可以通过预处理 $P,1-P$ 的 $1 \sim n$ 次方做到 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
#define int long long
const int mod = 998244353;
using namespace std;
const int maxn = 2e3+114;
int p[maxn],dp[maxn],w[maxn][maxn];
int n,P,a,b;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>a>>b;
    P=a*qpow(b,mod-2)%mod;
    p[1]=1;
    dp[1]=0;
    for(int i=2;i<=n;i++){
        for(int j=0;j<i;j++){
            w[i][1]=(w[i][1]+qpow(P,j)*qpow(mod+1-P,i-1-j)%mod)%mod;
        }
        w[i][i-1]=w[i][1];
        for(int j=2;j<i-1;j++){
            w[i][j]=(w[i-1][j-1]*qpow(P,i-j)%mod+w[i-1][j]*qpow(mod+1-P,j)%mod)%mod;
        }
    }
    for(int i=2;i<=n;i++){
        p[i]=1;
        for(int j=1;j<i;j++) p[i]=(p[i]+mod-p[j]*w[i][j]%mod)%mod;
        dp[i]=i*(i-1)/2%mod;
        for(int j=1;j<i;j++){
            dp[i]=(dp[i]+(dp[j]+dp[i-j]+mod-(i-j)*(i-j-1)/2%mod)%mod*w[i][j]%mod*p[j]%mod)%mod;
        }
        dp[i]=dp[i]*qpow(mod+1-p[i],mod-2)%mod;
    }
    cout<<dp[n]<<'\n';
    return 0;
}
```

---

