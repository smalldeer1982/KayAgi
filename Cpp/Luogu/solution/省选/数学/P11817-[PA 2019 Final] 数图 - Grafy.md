# [PA 2019 Final] 数图 / Grafy

## 题目背景

译自 PA 2019 Final。$\texttt{5s,256M}$。


本题数据为自造。

std: joke3579，validator & generator: Starrykiller。

加强版：P11821。**请勿提交 OEIS 题解。**

## 题目描述

求出 $n$ 个节点的满足以下条件的**有标号有向简单图**的数量：

- $\forall 1\le i\le n$，$\operatorname{deg_{out}}(i)=\operatorname{deg_{in}}(i)=2$。

这里，$\operatorname{deg_{out}}(u)$ 指节点 $u$ 的出度，$\operatorname{deg_{in}}(u)$ 指节点 $u$ 的入度。

你只需要输出答案对给定大素数 $p$ 取模后的结果。


注意我们是对**有标号**的「有向简单图」计数。也就是说，这张图中无重边自环。注意 $u\to v$ 和 $v\to u$ 同时出现是允许的。




## 说明/提示

- $3\le n\le 500$；
- $10^8+7\le p\le 10^9+7$，$p$ 为素数。



## 样例 #1

### 输入

```
4 1000000007```

### 输出

```
9```

# 题解

## 作者：qweradf (赞：3)

考虑邻接矩阵，相当于一个 $n\times n$ 的 $01$ 矩阵，每行每列和为 $2$，对角线上全为 $0$，求方案数。

先容斥，钦定对角线的一个子集 $T$ 填 $1$。发现去掉这些 $1$ 后这些位置不能填数，不好处理。

好做的形式是对角线的子集 $\geq 1$，其他位置是 $0$ 或 $1$，这样把钦定的子集减一后对角线和其他格子就没有区别了。

具体地，把钦定的子集减一后，剩下的限制：$n\times n$ 的 $01$ 矩阵，每格填 $0$ 或 $1$，有 $|T|$ 行 $|T|$ 列和为 $1$，其余行列和为 $2$。

记 $f_{i,j,k,l}$ 表示有一个 $(i+j)\times(k+l)$ 的 $01$ 矩阵，要求前 $i$ 行、前 $k$ 列和为 $1$，后 $j$ 行、后 $l$ 列和为 $2$。

状态数是 $O(n^3)$（因为 $i+2j=k+2l$，$l$ 可以用 $i$，$j$，$k$ 表示），转移枚举第一行的 $1$ 填在哪，做到 $O(1)$，所以 $f$ 数组可以 $O(n^3)$ 求出。

容斥的时候钦定对角线的子集 $\geq 1$，其他位置是 $0$，$1$ 或 $2$，这个方案数可以用 $f$ 求出（枚举其他位置哪些填 $2$）。

因此总时空复杂度 $O(n^3)$，做到空间最劣解！！！11。。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb emplace_back
#define debug(x) (cerr<<#x": "<<(x)<<endl)
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;

bool ST;
const int N=510;
int f[N][N][N];
int n;ll P;
ll CC[N][N];ll C(ll x,ll y){return (x>=y&&y>=0)?CC[x][y]:0;}
bool ED;
int32_t main(){
	debug(fabs(&ST-&ED)/(1<<20));
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>P;
	rep(i,0,n) CC[i][0]=1;
	rep(i,1,n) rep(j,1,i) CC[i][j]=(CC[i-1][j-1]+CC[i-1][j])%P;
	int k;
	f[0][0][0]=1;
	rep(i,0,n) for(int j=0;i+j<=n;j++) rep(l,0,n){
		k=i+2*j-2*l;if(k<0) continue;
		if(i==0){
			if(j==0&&k==0) continue;
			if(k>=2) f[i][j][l]=(f[i][j][l]+(ll)f[i][j-1][l]*(k*(k-1)/2))%P;
			if(k>=1&&l>=1) f[i][j][l]=(f[i][j][l]+(ll)f[i][j-1][l-1]*k*l)%P;
			if(l>=2) f[i][j][l]=(f[i][j][l]+(ll)f[i][j-1][l-2]*(l*(l-1)/2))%P;
		}
		else{
			f[i][j][l]=(f[i][j][l]+(ll)f[i-1][j][l]*k)%P;
			f[i][j][l]=(f[i][j][l]+(ll)f[i-1][j][l-1]*l)%P;
		}
	}
	ll ans=0;
	rep(i,0,n){
		ll ret=0;
		rep(j,0,n-i) (ret+=C(n-i,j)*f[i][n-i-j][n-i-j])%=P;
		ret=ret*C(n,i)%P;
		if(i&1) (ans+=P-ret)%=P;
		else (ans+=ret)%=P;
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Purslane (赞：3)

# Solution

问题转化为：有多少个长度为 $2n$ 的序列，满足 $a_{2i-1} \neq a_{2i}$ 且，$i \neq a_{2i-1}$、$i \neq a_{2i}$。

考虑容斥。假设钦定了 $a$ 个 $i$ 满足 $a_{2i-1}=a_{2i}$，$b$ 个 $i$ 满足 $a_{2i} = i$ 或 $a_{2i+1} = i$，有 $c$ 个同时满足。假设一共有 $d$ 个不合法的 $i$，则一个图合法显然是 $[d=0]$，将其用容斥拆开，所以我们钦定了 $(a,b,c)$ 就要乘上 $(-1)^{a+b-c}$ 的系数。


这样剩下有 $a-c$ 个 $i$ 满足 $a_{2i-1} = a_{2i}$，以及 $b-c$ 个 $i$ 满足恰好有一个 $x \in \{2i-1,2i\}$ 满足 $a_x = i$。

所以你需要预处理：$dp_{n,m}$ 为，长度为 $n$ 的排列，对于前 $m$ 个数限制 $p_i \neq i$ 的方案数。以及 $f_{n,m}$ 表示，从 $n$ 个数里面选 $m$ 个使得 $p_i \neq i$ 的方案数。这两者都可以使用类似错排的手段处理——以 $f_{n,m}$ 为例，假设 $m>1$，则

$$
f_{n,m} = (n-m)f_{n-1,m-1} + (m-1)(f_{n-2,m-2} + f_{n-1,m-1})
$$

后者含义为，假设第一个数拿了 $i$（$2 \le i \le m$），如果第 $i$ 个数拿了 $1$ 就转化为 $f_{n-2,m-2}$；否则，第 $i$ 个数不能拿 $1$ 就相当于第 $i$ 个数原来不能拿 $i$，转化到 $f_{n-1,m-1}$。

$dp_{n,m}$ 也是类似的——当 $m=0$ 时答案是 $n!$；否则，考察 $p_1$ 的值，如果大于 $m$ 就是 $(n-m)dp_{n-1,m-1}$，否则假设是 $j$，考虑 $1$ 的去向——如果是 $j$ 则为 $dp_{n-2,m-2}$，否则为 $dp_{n-1,m-1}$。

你钦定了 $c$ 个位置全是 $i$，那没有别的方法；$a-c$ 个位置相等且不是自己，就是 $f_{n-b,a-c}$（原因是，显然有 $b$ 种数不能放）；$b-c$ 个数恰好有一个 $i$，你先钦定 $2^{b-c}$ 种方向，转化为 $dp_{2(n-a-b+c)+b-c,b-c}$（注意到剩下的 $n-a-b+c$ 种数全都是成对出现的，所以最后还要除序）。

你算出答案之后，除以 $2^n$ 即可。复杂度 $O(n^3)$。

这个做法太鬼扯晦气了吧，有没有更优美的做法。 /kel

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10;
int n,MOD,frac[MAXN],dp[MAXN][MAXN],f[MAXN][MAXN],C[MAXN][MAXN],p2[MAXN],i2[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>MOD;
	p2[0]=1; ffor(i,1,n) p2[i]=p2[i-1]*2%MOD;
	i2[0]=1; ffor(i,1,n) i2[i]=i2[i-1]*(MOD+1)/2%MOD;
	frac[0]=1; ffor(i,1,n+n) frac[i]=frac[i-1]*i%MOD;
	ffor(i,0,n) {
		C[i][0]=1;
		ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;	
	}
	ffor(i,0,n) ffor(j,0,i) {
		if(j==0) {f[i][j]=1; continue ;}
		f[i][j]=(i-j)*f[i-1][j-1]%MOD;
		if(j-1) f[i][j]=(f[i][j]+(j-1)*(f[i-2][j-2]+f[i-1][j-1]))%MOD;
	}
	ffor(i,0,n+n) ffor(j,0,i) {
		if(j==0) {dp[i][j]=frac[i];continue ;}
		dp[i][j]=(i-j)*dp[i-1][j-1]%MOD;
		if(j-1) dp[i][j]=(dp[i][j]+(j-1)*(dp[i-2][j-2]+dp[i-1][j-1]))%MOD;
	}
	int ans=0;
	ffor(c,0,n) ffor(a,c,n) ffor(b,c,n+c-a) {
		int mul=C[n][c]*C[n-c][a-c]%MOD*C[n-a][b-c]%MOD;
		if((a+b-c)&1) mul=-mul;
		ans=(ans+mul*p2[b-c]%MOD*f[n-b][a-c]%MOD*dp[2*(n-a-b+c)+b-c][b-c]%MOD*i2[n-a-b+c])%MOD;
	}
	ans=ans*i2[n]%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

