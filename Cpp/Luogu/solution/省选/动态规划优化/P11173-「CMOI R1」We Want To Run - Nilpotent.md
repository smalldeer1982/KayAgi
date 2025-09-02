# 「CMOI R1」We Want To Run / Nilpotent

## 题目背景

![](bilibili:BV1qW4y1Q7Ce)

$\small\color{white}54^{\text{th}}\text{Problem by ArCu}.$

## 题目描述

对于 $n\times n$ 矩阵 $A$，定义 $f(A)$ 为最小的满足 $A^b=O$ 的正整数 $b$，若不存在这样的数则 $f(A)=0$。其中 $O$ 是零矩阵，即所有元素都是 $0$ 的矩阵。

给定 $n,a$，每个元素都是 $[0,a)$ 中整数的 $n\times n$ 矩阵有 $a^{n^2}$ 种。对所有 $a^{n^2}$ 种可能的矩阵 $A$ 求 $f(A)$ 之和。

答案对 $202407031$ 取模。

## 说明/提示

$\text{Sample 1 Explanation}:$

注意到对于任意正整数 $b$，$\begin{bmatrix}1&0\\1&1\end{bmatrix}^b\neq O$，所以 $f\left(\begin{bmatrix}1&0\\1&1\end{bmatrix}\right)=0$。而 $\begin{bmatrix}0&0\\1&0\end{bmatrix}^2=O$，所以 $f\left(\begin{bmatrix}0&0\\1&0\end{bmatrix}\right)=2$。

一共有 $2^4=16$ 种可能的矩阵。其中 $f(A)$ 不为 $0$ 的只有

$$f\left(\begin{bmatrix}0&0\\0&0\end{bmatrix}\right)=1,f\left(\begin{bmatrix}0&0\\1&0\end{bmatrix}\right)=f\left(\begin{bmatrix}0&1\\0&0\end{bmatrix}\right)=2$$

答案即为 $1+2+2=5$。

$\text{Details of Subtasks}:$

所有数据满足 $1\leq n\leq 600,0<a<2^{64}$。

| $\text{Subtask}$ | $\text{Special Constraints}$ | $\text{Score}$ |
| :----------: | :----------: | :----------: | 
| $1$ | $n\leq 5,a\leq 2$ | $3$ |
| $2$ | $n\leq 5$ | $7$ | 
| $3$ | $n\leq 10$ | $10$ | 
| $4$ | $n\leq 40$ | $20$ | 
| $5$ | $n\leq 200$ | $30$ |
| $6$ |  | $30$ |

$\text{Hint}:202407031=13009\times 15559.$

## 样例 #1

### 输入

```
2 2```

### 输出

```
5```

## 样例 #2

### 输入

```
3 4```

### 输出

```
793```

## 样例 #3

### 输入

```
5 10```

### 输出

```
59350891```

## 样例 #4

### 输入

```
18 15932416```

### 输出

```
52138206```

## 样例 #5

### 输入

```
1 1```

### 输出

```
1```

# 题解

## 作者：Petit_Souris (赞：7)

We Want To Run 是神曲，出题人有品啊！

真不是蓝题嘛（？）

$a$ 是多少不是很重要，我们只关心每个位置是否是 $0$。

首先很容易想到用一个经典的图论模型来刻画矩阵的幂：若 $A_{i,j}>0$，那么从 $i$ 向 $j$ 连一条边，此时 $(A^k)_{i,j}$ 就表示 $i\to j$ 是否存在长度为 $k$ 的路径。

那么题目中的 $f(A)$ 实际上就是最小的 $b$ 满足图上不存在长度为 $b$ 的路径。显然当图上有环的时候不存在合法的 $b$，而当图为 DAG 时 $b$ 就是图上最长路径的点数。

最长路径启发我们把图按照从该点出发的最长路分层，设分成了 $S_1,S_2,\dots S_{d}$ 这些点集，那么 $\forall i\ge 2,x\in S_i$，都需要满足 $x$ 向 $S_{i-1}$ 中至少一个点连边，且不存在 $x\in S_i,y\in S_j,i\le j$，$x$ 向 $y$ 连边。

根据这个性质，我们可以设计一个 dp，每次剥掉所有最下面一层的点（这其实很类似 DAG 计数对 $0$ 度点容斥的思想）。设 $dp_{i,j,k}$ 表示 $i$ 层点，用了 $j$ 个点，上一层有 $k$ 个点的方案数。

转移枚举这层放了 $p$ 个点，$dp_{i,j,k}\times \binom{j+p}{p}(a^k-1)^pa^{p(j-k)}\to dp_{i+1,j+p,p}$（其中第一个 $(a^k-1)^p$ 表示相邻层的连边方案，$a^{p(j-k)}$ 表示往 $i-1$ 层及以前的连边方案）。答案为 $\sum\limits_{i=1}^{n}i\sum\limits_{k=1}^{n}dp_{i,n,k}$。时间复杂度 $\mathcal O(n^4)$，期望得分 70。

考虑优化这个东西。观察到我们的转移系数和 $i$ 根本无关，这个 $i$ 只是用来最后统计答案的时候乘上一个 $i$ 的系数。于是想到用组合意义拆掉这个 $i$，转化成在 $i$ 层中选择一层作为关键层的方案数。这样我们的 dp 就不需要记录 $i$ 了，状态变为 $dp_{j,k,0/1}$ 表示 $j$ 个点，上一层有 $k$ 个点，是否已经选出了关键层的方案数。转移分类讨论一下这层是否选做关键层，时间复杂度 $\mathcal O(n^3)$，可以通过。

观察到过程中没有需要求逆元的地方，所以其实可以任意模数来着，不知道出题人给了个特别的模数是想 CRT 还是啥意思，不太懂。

实现的时候注意读入的 $a$ 的范围是 unsigned long long 的。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ull read(){
    ull x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
    return x;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=609,Mod=202407031;
ll n,A,pwA[N*N],pwq[N][N],C[N][N],dp[N][N][2],cur;
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%Mod;
        x=x*x%Mod,p>>=1;
    }
    return res;
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),A=read()%Mod;
    pwA[0]=1;
    rep(i,1,n*n)pwA[i]=pwA[i-1]*A%Mod;
    rep(i,1,n){
        pwq[i][0]=1;
        rep(j,1,n)pwq[i][j]=pwq[i][j-1]*(pwA[i]-1+Mod)%Mod;
    }
    rep(i,0,n){
        C[i][0]=1;
        rep(j,1,i)C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
    }
    ll ans=0;
    rep(i,1,n)dp[i][i][0]=dp[i][i][1]=1;
    rep(j,1,n){
        rep(k,1,n){
            rep(o,0,1){
                ll v=dp[j][k][o];
                if(!v)continue;
                rep(p,1,n-j){
                    dp[j+p][p][o]=(dp[j+p][p][o]+
                    v*pwq[k][p]%Mod*pwA[p*(j-k)]%Mod*C[j+p][p])%Mod;
                    if(!o)dp[j+p][p][1]=(dp[j+p][p][1]+
                    v*pwq[k][p]%Mod*pwA[p*(j-k)]%Mod*C[j+p][p])%Mod;
                }
            }
        }
    }
    rep(k,1,n)ans=(ans+dp[n][k][1])%Mod;
    write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：飞雨烟雁 (赞：7)

首先，注意到矩阵的所有元素非负，因此某个元素是 $1$ 还是 $2$ 对矩阵 $A$ 的 $f(A)$ 值并没有影响。故不妨将所有大于等于 $1$ 的元素视为 $1$。也即对于矩阵的每个元素，有 $1$ 种可能为 $0$，另外 $a-1$ 种可能为 $1$。

然后利用矩阵乘法和有向图的关系。0-1 矩阵 $A$ 幂零，等价于由它构建的有向图是个 DAG（构建规则为：若 $a_{ij}=1$，则连接 $i\rightarrow j$ 的有向边）。并且 $f(A)$ 就等于这个 DAG 的最长链上的点的数量。

综上，我们将问题转化为：对于有向无环图 $G$，记其边的数量为 $e(G)$，其最长链上点个数为 $l(G)$，试求：

$$\sum _G l(G)(a-1)^{e(G)}$$

（其中 $\sum_G$ 对所有 $n$ 个点的 DAG 求和）

---

对于有向无环图 $G$，我们考虑如何求其最长链。最简单的方法就是令出度为 $0$ 的节点深度为 $1$，然后对于每个点，令其深度为它所指的节点的深度的最大值 $+\,1$。那么，所有节点深度的最大值就是 $l(G)$。受此启发，我们设 $G$ 深度为 $i$ 的点有 $a_i$ 个，则有：

$$\sum_{k=1}^{l(G)}a_k=n$$

且 $\forall 1\le i\le l(G),a_i\neq 0$。

枚举 $l(G), a_1,\cdots,a_{l(G)}$，我们考虑这样的 $G$ 有几个。

首先，深度为 $i+1$ 的点必须有一条边连向某个深度为 $i$ 的点。然后，深度为 $i+1$ 的点可以往深度低于 $i$ 的点任意地连边。于是满足条件的 DAG 有这么多个：

$$\binom{n}{a_1,\cdots,a_{l(G)}}\prod_{i}\left(2^{a_{i}}-1\right)^{a_{i+1}}2^{a_{i+1}(a_1+\cdots+a_{i-1})}$$

但是这样就没有 $e(G)$ 什么事了！因此，我们用 $x$ 的次数来记录有向边条数，则上式应改写为：

$$\binom{n}{a_1,\cdots,a_{l(G)}}\prod_{i}\left[(1+x)^{a_{i}}-1\right]^{a_{i+1}}(1+x)^{a_{i+1}(a_1+\cdots+a_{i-1})}$$

故而我们有：

$$\sum _ G l(G)x^{e(G)}=\sum_{a_1+\cdots+a_k=n, a_k\neq 0}k\binom{n}{a_1,\cdots,a_k}\prod_{i}\left[(1+x)^{a_{i}}-1\right]^{a_{i+1}}(1+x)^{a_{i+1}(a_1+\cdots+a_{i-1})}$$

令 $x=a-1$ 得答案为：

$$n!\sum_{a_1+\cdots+a_k=n, a_k\neq 0}k\prod_{i}\dfrac{\left(a^{a_{i}}-1\right)^{a_{i+1}}}{a_i!}a^{a_{i+1}(a_1+\cdots+a_{i-1})}$$

直接计算可以通过前三个 Subtask。

---

下面考虑用 DP 优化计算。设 $f_{k,s,l}$ 为：

$$\begin{aligned}f_{k,s,l}&=\sum_{a_1+\cdots+a_k=s,a_k=l}\prod_{i}\dfrac{\left(a^{a_{i}}-1\right)^{a_{i+1}}}{a_i!}a^{a_{i+1}(a_1+\cdots+a_{i-1})}\end{aligned}$$

则答案为 $n!\sum _ {k,l}k f_ {k,n,l}$。

枚举 $r=a_{k-1}$，可知递推式如下：

$$f_{k,s,l}=\sum_{r} f_{k-1,s-l,r}\dfrac{\left(a^{r}-1\right)^{l}}{l!}a^{l(s-l-r)}$$

且边界为 $f_{1,s,l}=[s=l]\frac{1}{s!}$。

这样就是一个 $\Theta(n^4)$ 或 $\Theta(n^4\log n)$ 的 DP，能过前四个 Subtask。

---

我们继续考虑优化，注意到递推式中，$s,l$ 都和求和指标 $r$ 有关，唯独 $k$ 和 $r$ 没什么关系，这引导我们设：

$$g_{s,l}=\sum_k f_{k,s,l}$$

但是这样的话答案就算不了了，所以我们再设：

$$h_{s,l}=\sum_k kf_{k,s,l}$$

这样答案就是 $n!\sum _ l h_{n,l}$。接着我们考虑写出 $g,h$ 的状态转移方程。

$$\begin{aligned}g_{s,l}&=\sum_{k,r} f_{k-1,s-l,r}\dfrac{\left(a^{r}-1\right)^{l}}{l!}a^{l(s-l-r)}\\&=\sum_{r}g_{s-l,r}\dfrac{\left(a^{r}-1\right)^{l}}{l!}a^{l(s-l-r)}\end{aligned}$$

而 $h$ 的方程是类似的：

$$\begin{aligned}h_{s,l}&=\sum_{k,r} kf_{k-1,s-l,r}\dfrac{\left(a^{r}-1\right)^{l}}{l!}a^{l(s-l-r)}\\&=\sum_{k,r} (k-1)f_{k-1,s-l,r}\dfrac{\left(a^{r}-1\right)^{l}}{l!}a^{l(s-l-r)}+g_{s,l}\\&=\sum_{r}h_{s-l,r}\dfrac{\left(a^{r}-1\right)^{l}}{l!}a^{l(s-l-r)}+g_{s,l}\end{aligned}$$

边界条件是 $g_{k,k}=h_{k,k}=\frac 1{k!}$。

预处理 $a$ 相关的快速幂，可得一个 $\Theta(n^3)$ 的做法，足以通过此题。

核心代码如下：


```cpp
int Solve(){
	Frac[0] = PA[0] = 1;
	for(int i = 1; i < Mx; ++i) Frac[i] = 1ll * i * Frac[i - 1] % Mod;
	Infs[Mx - 1] = FastPow(Frac[Mx - 1], Nod - 1);
	for(int i = Mx - 1; i; --i) Infs[i - 1] = 1ll * i * Infs[i] % Mod;
	for(int i = 0; i < Mx; ++i) for(int j = 0; j < Mx; ++j) U[i][j] = FastPow(FastPow(a, i) - 1, j);
	for(int i = 1; i < Nx; ++i) PA[i] = 1ll * PA[i - 1] * a % Mod;
	
	for(int s = 0; s <= n; ++s){
		G[s][s] = H[s][s] = Infs[s];
		for(int l = 1; l < s; ++l){
			ll Q = 0, Q2 = 0;
			for(int r = 1; r <= s - l; ++r){
				Q += 1ll * G[s - l][r] * PA[(s - l - r) * l] % Mod * U[r][l] % Mod;
				Q2 += 1ll * H[s - l][r] * PA[(s - l - r) * l] % Mod * U[r][l] % Mod;
			}
			G[s][l] = Q % Mod * Infs[l] % Mod;
			H[s][l] = (Q2 % Mod * Infs[l] + G[s][l]) % Mod;
		}
	}
	
	ll Ans = 0;
	for(int s = 1; s <= n; ++s) Ans += H[n][s];
	Ans = Ans % Mod * Frac[n] % Mod;
	
	return Ans < 0 ? Ans + Mod : Ans;
}
```

---

**闲话**：

比赛开始时我先看了 G 题，虽然一眼数树，但是根本不会组合推导，所以果断写 F 题。因为模数非质数，我就想着对两个质数分别求答案，再暴力枚举答案（不想写 CRT）。因此我代码里的模数不是 `const` 类型，导致我就算写了 $\Theta(n^3)$ 的正解仍旧 TLE。最后把代码复制成两份，一份用 Mod0，一份用 Mod1，然后就过了。有点可惜，是二杀，鉴定为不会数学导致的。

---

## 作者：251Sec (赞：5)

瞪眼之后发现所求就是所有 $n$ 个点 DAG 的最长路，乘上 $(a-1)$ 的边数次方，求和。

把 DAG 的点按照以它结尾的最长路长度分层，那么对于第 $i$ 层的点一定有至少一个第 $(i-1)$ 层的点向它连边，且有任意多个 $<i-1$ 层的点向它连边。

直接对着这个东西 DP，$f(i,j,k)$ 代表 $i$ 层，$j$ 个点，最后一层有 $k$ 个点的方案数。这是 $O(n^4)$ 的。

层数在 DP 过程中没有什么用，只有在最后统计答案的时候需要乘上层数的贡献，考虑这个贡献的组合意义，实际上相当于在这个 DAG 中选出一层，于是设 $f(i,j,0/1)$ 代表 $i$ 个点，最后一层有 $j$ 个点，是否选出了一层的方案数。这样就是 $O(n^3)$ 的。

官方题解中对 $f(i,j,0/1)$ 除掉了 $i!$，所以需要求阶乘逆元，不过我们其实可以不除，在转移的时候乘组合数即可。所以这题其实可以做任意模数。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P = 202407031;
int n;
unsigned long long a;
ll pw[100005];
ll QPow(ll a, ll b) {
	ll res = 1;
	for (; b; b >>= 1, a = a * a % P) if (b & 1) res = res * a % P;
	return res;
}
ll f[605][605][2], c[605][605];
int main() {
	scanf("%d%llu", &n, &a), a %= P;
	for (int i = 0; i <= n; i++) {
		for (int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % P;
		c[i][0] = 1;
	}
	pw[0] = 1;
	for (int i = 1; i <= 100000; i++) pw[i] = pw[i - 1] * a % P;
	for (int i = 1; i <= n; i++) f[i][i][0] = f[i][i][1] = 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			ll s = (pw[j] + P - 1) % P, t = 1;
			for (int x = 1; i + x <= n; x++) {
				t = t * s % P;
				for (int k = 0; k < 2; k++) {
					for (int y = k; y < 2; y++) {
						(f[i + x][x][y] += f[i][j][k] * c[i + x][x] % P * pw[x * (i - j)] % P * t % P) %= P;
					}
				}
			}
		}
	}
	ll ans = 0;
	for (int j = 1; j <= n; j++) ans += f[n][j][1];
	printf("%lld\n", ans % P);
	return 0;
}
```

---

## 作者：dAniel_lele (赞：5)

没看懂出题人想表达什么，但是按照我的做法这没黑吧/jk

显然，问题等价于求所有 $n$ 个点的 DAG 最长链乘上 $x^c$ 的和，其中 $c$ 为边数。

先弱化，算方案数。

考虑分层，设 $dp_{i,j}$ 表示目前考虑了 $i$ 个点，最前面一层有 $j$ 个点的方案数。

转移考虑枚举新的一层的点数 $k$，$dp_{i,j}\times(x^i-x^{i-j})^k\to dp_{i+k,k}$。也就是说，新的一层的每个点必须被一个前一层的点连向，其余随意。

考虑上最长链长度。

设 $dp_{i,j,0/1}$ 表示目前考虑了 $i$ 个点，最前面一层有 $j$ 个点的方案数和所有方案数目前链长之和。有转移：

* $dp_{i,j,0}\times(x^i-x^{i-j})^k\times\binom{i+k}{k}\to dp_{i+k,k,0}$；
* $dp_{i,j,0}\times(x^i-x^{i-j})^k\times\binom{i+k}{k}\to dp_{i+k,k,1}$；
* $dp_{i,j,1}\times(x^i-x^{i-j})^k\times\binom{i+k}{k}\to dp_{i+k,k,1}$。

最后答案就是 $\sum_{j=1}^ndp_{n,j,1}$。总复杂度 $O(n^3)$。

为什么 $n^3$ 开 $600$？因为 $1000$ 太大了。

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
#define double long double
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
const int mod=202407031;
int dp[605][605][2],C[605][605],pw[605];
int f[605][2],g[605][2];
signed main(){
	for(int i=0;i<=600;i++) C[i][0]=1;
	for(int i=1;i<=600;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	int n,a; cin>>n>>a; a%=mod;
	pw[0]=1; for(int i=1;i<=600;i++) pw[i]=pw[i-1]*a%mod;
	for(int i=1;i<=n;i++) dp[i][i][0]=dp[i][i][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			int mul=(pw[i]+mod-pw[i-j])%mod,tr=1;
			for(int k=1;i+k<=n;k++){
				(tr*=mul)%=mod;
				int tmptr=tr*C[i+k][k]%mod;
				(dp[i+k][k][0]+=dp[i][j][0]*tmptr)%=mod;
				(dp[i+k][k][1]+=(dp[i][j][0]+dp[i][j][1])*tmptr)%=mod;
			}
		}
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=i;j++) (g[i][0]+=dp[i][j][0])%=mod,(g[i][1]+=dp[i][j][1])%=mod;
	cout<<g[n][1];
	return 0;
}
```

---

## 作者：Argon_Cube (赞：5)

Official Solution By Argon_Cube.

首先有一个很经典的结论（[AT_dp_r](https://www.luogu.com.cn/problem/AT_dp_r)），就是若 $A$ 为某个有向图的邻接矩阵，则 $A^k$ 的 $(i,j)$ 元素就是从 $i$ 到 $j$ 经过 $k$ 条边的路径权值和（定义一条路径的权值为所有边权的乘积）。

那么我们逆用这个结论，考虑将 $A$ 视为邻接矩阵则 $A$ 与边权为 $[1,a)$ 的简单有向图一一对应。$A^k=O$ 代表该图不存在长度为 $k$ 的路径，所以 $f(A)$ 就等于图上最长路径经过的点数。特别的，如果 $A$ 有环那么可以一直在环上绕，此时 $f(A)=0$。

这样我们就将问题转化为了所有边权为 $[1,a)$ 的 DAG 上最长路径经过的点数和。显然从 DP 的角度考虑是没有前途的，考虑另一种方法：拓扑排序，每轮把入度为 $0$ 的点一起删掉，则进行的轮数就是最长路长度。

那么就可以考虑枚举进行的轮数和每轮删去的点数了，设第 $i$ 轮删了 $b_i$ 个点，显然每一层的点至少需要一条来自上一层的出边，边两端在同一层的不能连，不在相邻两层的随便连：

$$\sum_{m=1}^nm\sum_{|b|=m,\sum b=n}\binom n{b_1,\cdots,b_m}\left(\prod_{i+1<j}a^{b_ib_j}\right)\left(\prod_{i}(a^{b_i}-1)^{b_{i+1}}\right)$$

把组合数的 $n!$ 提到外面最后再乘，这样每个 $b$ 的权值就和 $n$ 无关了。然后直接暴力 DP，设 $f_{i,j,k}$ 是所有长为 $i$，和为 $j$，最后一个数是 $k$ 的 $b$ 的权值和，枚举倒数第二个数转移：

$$f_{i,j,k}=\frac{1}{k!}\sum_{l}f_{i-1,j-k,l}a^{k(j-k-l)}(a^l-1)^k$$

简单预处理即可 $\Omicron(n^4)$。

可以发现长度这一维很烦，考虑一个长度为 $i$ 的数组权值会乘上 $i$ 也就是贡献 $i$ 次。那么考虑这个 $i$ 的组合意义，在这个数组中选出一个非空后缀的方案数就是 $i$。那么直接把长度那一维去掉，然后设 $f_{i,j,\{0,1\}}$，状态的意义是记录当前的和与最后一个数，以及最后这个数在不在选出的后缀中。转移基本不变。

这样时间复杂度就变成了 $\Omicron(n^3)$。

注意到模数是合数，不能也不需要对 $a$ 求逆，但是模数两个质因子都远大于 $n$，要求逆的只有阶乘，所以直接用 $a^{-1}\equiv a^{\varphi(m)-1}\pmod m$ 求逆就好了。

---

## 作者：orange_new (赞：2)

节选自：[DP做题记录（三）（2025.4.5 - 2025.4.19）](https://www.luogu.com.cn/article/tobtmxka)

[安利一下我的博客](https://www.cnblogs.com/JPGOJCZX/p/18830560)

套用非常经典的线性代数结论，一张图的邻接矩阵的 $k$ 次方后每个位置 $A_{u, v}$ 就表示 $u$ 到 $v$ 的所有路径中长度为 $k$ 的路径条数。

注意到这张图中左右边权非负，那么在矩乘时，如果两个位置都不为 $0$，那么乘积也不为 $0$，必须至少有一个是 $0$ 才可以，于是，每个位置 $A_{i, j}$ 我们不用考虑它的具体取值，只用考虑它是否为 $0$。

那么现在，$A^b = O$ 的含义就变成了对一个边权只有 $0$ 和 $1$ 的图，找到最小的 $b$ 使得图中没有长度为 $b$ 的链。显然，如果这张图存在环，那么图中就不存在最长链（可以一直在环上绕），因此这张图一定是一个 DAG。

由于我们要统计方案数，因此我们考虑枚举贡献。如果这张图中最长链上的**点数**为 $b$，那么说明最长链的**长度**为 $b - 1$，于是对答案的贡献就是 $b$。由于是 DAG 我们可以按拓扑序一层一层枚举。

我们设 $dp_{i, j, k}$ 表示前 $i$ 个点分了 $j$ 层，上一层有 $k$ 个点的方案数。我们先枚举这一层的点数 $p$，那么这 $p$ 个点就可以从这 $i + p$ 个点中选出，因此转移时首先要乘以 $\displaystyle\binom{i + p}{p}$。

其次，这一层的点必须至少与上一层的 $1$ 个点连边，边权任意，于是转移时又要乘以 $(a^k - 1)^p$（减 $1$ 是因为不能一个点都不连）。

最后，这一层的点可以与之前层的点随便连边，之前的点一共有 $i - k$ 个，于是答案又要乘以 $a^{p(i - k)}$，因此我们就得到了转移方程 $dp_{i, j, k} \times \displaystyle\binom{i + p}{p} (a^k - 1)^p a^{p(i - k)} = dp_{i + p, j + 1, p}$。那么答案就是 $\displaystyle\sum_{j = 1}^n j \sum_{k = 1}^{n - j + 1} dp_{n, j, k}$。

我们其实可以发现，$j$ 其实顶没用的（~~和我一样~~），只是在最后求答案时要乘以 $j$。我们考虑 $j$ 的组合意义，就是在这 $j$ 层中选一层作为关键层。这是因为 $\displaystyle\binom j1 = j$。

现在我们可以改变 DP 的函数了，设 $dp_{i, j, 0 / 1}$ 表示给前 $i$ 个数分层，上一层有 $j$ 个数，且是否选择过关键层的答案，$dp_{i, j, 0}$ 到 $dp_{i + p, p, 0}$，$dp_{i, j, 1}$ 到 $dp_{i + p, p, 1}$ 直接用之前的转移方程。对于每一层，都可以选择这一层成为关键层，于是把 $dp_{i, j, 0}$ 按照转移方程加到 $dp_{i + p, p, 1}$ 就可以了，复杂度降低到 $O(n^3)$，足以通过此题。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
const int N = 6e2 + 9, MOD = 202407031;
int dp[N][N][2], binom[N][N], pwr[N * N], po[N][N], n, a, ans;
int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') 
			f = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = ((x << 1) + (x << 3) + (ch ^ 48));
		ch = getchar();
	}
	return x * f;
}
void write(int x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	n = read();
	a = read();
	a %= MOD;
	pwr[0] = 1;
	for(int i = 1; i <= n * n; i++)
		pwr[i] = pwr[i - 1] * a % MOD;
	for(int i = 1; i <= n; i++){
		po[i][0] = 1;
		for(int j = 1; j <= n; j++)
			po[i][j] = po[i][j - 1] * (pwr[i] - 1 + MOD) % MOD;
	}
	binom[0][0] = 1;
	for(int i = 1; i <= n; i++){
		binom[i][0] = 1;
		for(int j = 1; j <= i; j++)
			binom[i][j] = (binom[i - 1][j] + binom[i - 1][j - 1]) % MOD;
	}
	for(int i = 1; i <= n; i++)
		dp[i][i][1] = dp[i][i][0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(dp[i][j][0] != 0){
				for(int p = 1; p <= n - i; p++){
					dp[i + p][p][0] = (dp[i + p][p][0] + dp[i][j][0] * binom[i + p][p] % MOD * po[j][p] % MOD * pwr[p * (i - j)] % MOD) % MOD;
					dp[i + p][p][1] = (dp[i + p][p][1] + dp[i][j][0] * binom[i + p][p] % MOD * po[j][p] % MOD * pwr[p * (i - j)] % MOD) % MOD;
				}
			}
			if(dp[i][j][1] != 0){
				for(int p = 1; p <= n - i; p++)
					dp[i + p][p][1] = (dp[i + p][p][1] + dp[i][j][1] * binom[i + p][p] % MOD * po[j][p] % MOD * pwr[p * (i - j)] % MOD) % MOD;
			}	
		}
	}
	for(int i = 1; i <= n; i++)
		ans = (ans + dp[n][i][1]) % MOD;
	write(ans);
	return 0;
}
```

---

## 作者：Re_Star (赞：2)

[题面](https://www.luogu.com.cn/problem/P11173)

[更好的阅读体验](https://www.cnblogs.com/Re-Star/p/18831213)

首先我们把矩阵 $A$ 看成一个图的邻接矩阵，那么 $A^b_{u,v}$ 表示 $u\rightarrow v$ 所有路径的边权乘积之和。因为边权都大于 $0$，所以不会出现多条路径边权乘积加起来等于 $0$，那么 $A^b=O$ 当且仅当图中不存在经过 $b$ 条边的路径。

如果图中有环，那么图中一定存在经过任意点数的路径，则 $f(A)$ 等于 $0$。所以我们只需要考虑 DAG。如果一个图最长链经过 $s$ 个点，那么它对答案的贡献

考虑 DP，我们把图分层，设 $f_{i,j,k}$ 表示前 $i$ 个点分成 $j$ 层，最后一层有 $k$ 个点的方案数，这里我们钦定每个点都至少和上一层的一个点有边。这个转移是容易的，我们枚举下一层选 $p$ 个点，这一层中每个点和上一层需要有连边，所以方案数为 $(a^k-1)^p$，和前面其它点的连边没有限制，方案数为 $(a^{i-k})^p$，那么有如下转移：
$$
f_{i,j,k}\times(a^k-1)^p\times(a^{i-k})^p\times{i+p\choose p}\rightarrow f_{i+p,j+1,p}
$$
但是这个转移总复杂度是 $O(N^4)$，过不了。这里我们考虑第二维 $j$ 的意义是什么，因为最终对答案的贡献是 $j\times f_{i,j,k}$，所以我们才需要记录点的分层数。但是这里我们考虑乘的这个 $j$ 的组合意义就是，将一层选作关键层的方案数，那么我们就不需要记录层数而只需要记录一维 $0/1$ 表示是否选过关键层。新的状态为 $f_{i,j,0/1}$ 表示前 $i$ 个点分层，最后一层有 $j$ 个点，是否选过关键层的方案数。这个转移和上面是类似的。
$$
\begin{aligned} 
\begin{equation}
    \begin{cases}
    f_{i,j,op}\times(a^j-1)^p\times(a^{i-j})^p\times{i+p\choose p}\rightarrow f_{i+p,p,op}\\
    f_{i,j,0}\times(a^j-1)^p\times(a^{i-j})^p\times{i+p\choose p}\rightarrow f_{i+p,p,1}\\
    \end{cases}
\end{equation}
\end{aligned}
$$
现在总复杂度是 $O(N^3)$，可以过了。

code：

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const ll N=605,mod=202407031; 
ll n,a,ans,c[N][N],dp[N][N][2],s1[N*N],s2[N][N];
inline ll rd()
{
    char c;int f=1;
    while(!isdigit(c=getchar()))if(c=='-')f=-1;
    ll x=c-'0';
    while(isdigit(c=getchar()))x=(x*10+(c^48))%mod;
    return x*f;
}
inline ll qp(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1) (res*=x)%=mod;
		(x*=x)%=mod,y>>=1;
	}
	return res;
}
int main()
{
	for(int i=0;i<N;i++)
	{
		c[i][0]=c[i][i]=1;
		for(int j=1;j<i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	n=rd(),a=rd();
	for(int i=0;i<=n*n;i++) s1[i]=qp(a,i);
	for(int i=0;i<N;i++) 
		for(int j=0;j<N;j++) s2[i][j]=qp(qp(a,i)-1+mod,j);
	for(int i=1;i<=n;i++) dp[i][i][0]=dp[i][i][1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			for(int k=0;k<2;k++) if(dp[i][j][k])
			{
				ll x=dp[i][j][k];
				for(int p=1;p+i<=n;p++)
				{
					(dp[i+p][p][k]+=x*s2[j][p]%mod*s1[p*(i-j)]%mod*c[i+p][i]%mod)%=mod;
					if(!k) (dp[i+p][p][1]+=x*s2[j][p]%mod*s1[p*(i-j)]%mod*c[i+p][i]%mod)%=mod;
				}
			}
	for(int i=1;i<=n;i++) (ans+=dp[n][i][1])%=mod;
	cout<<ans;
	return 0;
}

```

---

## 作者：BreakPlus (赞：1)

考虑矩阵乘法的定义：在 $A \times B = C$ 中，$A_{i,j} \times B_{j,k}$ 将会贡献到 $C_{i,k}$。这和图上的路径相关。

在矩阵 $A$ 中，若 $A_{i,j}>0$，连一条 $i \to j$ 的有向边。

若令 $T = A^k$，则存在 $i,j$ 使得 $T_{i,j}>0$ 的充要条件是图中存在一个长度为 $k$ 的路径。

若图中存在环（包括自环）显然 $f(A)=0$。因此只需要考虑所有拓扑图。

对于一张基于 $A$ 建成的拓扑图 $G$，每次找到所有 $0$ 度点，并将它们及其连出去的边删去，不再考虑（即分层），直到图被删空。根据拓扑图分层的性质，层数（操作的次数）即为 $f(A)$。

----

经典的容斥 DAG 计数做法不能支持维护层数（至少容斥系数不会是简单的 $(-1)^{k-1}$）。

考虑一个很暴力的 DP，记 $f_{i,j}$ 表示目前图中有 $i+j$ 个点，共有 $j$ 个 $0$ 度点。

枚举 $k$，表示新图有 $k$ 个 $0$ 度点，$i+j+k$ 个点。那么原来的 $j$ 个 $0$ 度点必须至少向新的 $k$ 个点连一条边，而剩余的 $i$ 个点无所谓。

转移方程非常容易，略去。

```cpp
int n; ull a;
int dp[605][605], ans[605][605], C[605][605], pr[605][605], ps[605][605];
void init(){
	C[0][0]=1;
	for(int i=1;i<=600;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
}
void procedure(){
	scanf("%d%llu", &n, &a);
	a%=mod;
	dp[0][0] = 1;
	for(int i=0;i<=n;i++){
		for(int j=1;i+j<=n;j++){
			pr[i][j] = qpow((qpow(a, j)+mod-1)%mod, i)%mod;
			ps[i][j] = qpow(a, i*j);
		}
	}
	for(int i=0;i<n;i++)
		for(int j=0;i+j<n;j++){
			if(!dp[i][j]) continue;
			for(int k=1;i+j+k<=n;k++){
				ull coef=1ull*C[i+j+k][k]*pr[j][k]%mod*ps[i][k]%mod;
				dp[i+j][k]=(dp[i+j][k]+coef*dp[i][j])%mod;
				ans[i+j][k]=(ans[i+j][k]+1ull*coef*(ans[i][j]+dp[i][j]))%mod;
			}
		}
	int w=0;
	for(int i=1;i<=n;i++){
		w=(w+ans[n-i][i])%mod;
	}
	printf("%d\n", w);
}
```

---

