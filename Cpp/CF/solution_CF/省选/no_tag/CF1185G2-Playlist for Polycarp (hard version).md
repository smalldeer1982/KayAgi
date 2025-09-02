# Playlist for Polycarp (hard version)

## 题目描述

### 题意简述

你现在正在选择歌曲。现在共有 $n$ 首歌，每首歌有一个时长 $t_i$ 和一个编号 $g_i$ 。   
您需要求出有多少种选出若干首歌排成一排的方案，使得任意相邻两首歌的编号不同，且所有歌的时长和恰好为 $T$ 。

## 样例 #1

### 输入

```
3 3
1 1
1 2
1 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 3
1 1
1 1
1 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 10
5 3
2 1
3 2
5 1
```

### 输出

```
10
```

# 题解

## 作者：Alex_Wei (赞：16)

- Update on 2022.11.6：重写题解，原题解见 [剪贴板](https://www.luogu.com.cn/paste/dgsb19w2)。

[CF1185G2 Playlist for Polycarp (hard version)](https://www.luogu.com.cn/problem/CF1185G2)

考虑先求出 $f_{i, j, k}$ 表示选择 $i$ 个 $1$，$j$ 个 $2$，$k$ 个 $3$ 排成一行且相邻数不同的方案数。设 $g_{i, j, k, 1 / 2 / 3}$ 表示当前最后一个数，枚举下一个数转移求得 $g$，则 $f_{i, j, k} = \sum g_{i, j, k, 1 / 2 / 3}$。不要忘记给 $f_{i, j, k}$ 乘上 $i! j! k!$ 表示 $1, 2, 3$ 均可任意排列。时间复杂度 $n ^ 3$。

问题转化为求出选 $i$ 个 $1$，$j$ 个 $2$，$k$ 个 $3$ 且时长总和为 $T$ 的方案数。容易想到 $n ^ 4T$ 直接 DP，但不够优秀。我们发现直接 DP 可以求得每个 $T$ 的答案，遇到这种多花时间求出比答案更多的信息的情况，可以考虑如何改进算法使得我们恰好求得答案。

注意到 “总和为 $T$” 是一个背包的形式，我们不必要把整个背包均求出，只需求某个点值。如果我们能将大背包拆成两个小背包，完整求出这两个小背包，再枚举其中一个点值，根据 $T$ 算出另外一个背包的对应点值，即可解决问题。这启发我们将背包拆成 “选 $i$ 个 $1$ 且时长总和为 $u$” 和 “选 $j$ 个 $2$，$k$ 个 $3$ 且时长总和为 $v$” 两个小背包，分别 $n ^ 2T$ 和 $n ^ 3T$ 求出完整信息，然后枚举 $i, j, k, u$，则 $v = T - u$， $n ^ 3T$ 算出答案即可。

时间复杂度 $n ^ 3T$，有 $\dfrac 1 {27}$ 倍常数。[代码](https://codeforces.com/contest/1185/submission/179482517)。

---

## 作者：Purple_wzy (赞：6)

# CF1185G2 Playlist for Polycarp

[题面](https://www.luogu.com.cn/problem/CF1185G2)

[英文题面](https://codeforces.com/problemset/problem/1185/G2)

题意：有$n$首歌，每首歌有时间$t_i$，类型$g_i$。你需要选出若干首歌并将他们排成一排，满足相邻两首歌的类型不能相同，所有歌的时间总和为$T$。求方案数。

$n \leq 50,T \leq 2500,t_i \leq 50,1 \leq g_i \leq 3$。

题解：我们可以考虑先将两个限制分开考虑，然后再尝试合并。

先考虑第二个限制。设$a_{i,t}$表示第一种歌用了$i$个，总时长为$t$的方案数，$b_{i,j,t}$表示第二种、第三种歌分别选了$i$，$j$个，总时长为$t$的方案数。转移时就用01背包的转移方式即可。时间复杂度是$O(n^3 \times T)$的。

再考虑第一个限制。设$f_{i,j,k,l}$表示三种歌各选了$i,j,k$次，最后一个选的是$l$的方案数。转移就每次枚举往序列最后放哪个数即可。时间复杂度是$O(n^3)$的。

最后考虑将它们合并。我们枚举$i,j,k,t$，表示三种歌各选了$i,j,k$个，其中第一种歌的总时间是$t$。那么方案数为：

$$a_{i,t} \times b_{j,k,T-t} \times i! \times j! \times k! \times f_{i,j,k,0/1/2}$$

累加一下就是答案了。

时间复杂度：$O(n^3 \times T)$，常数非常小，可以通过本题。

代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline int
#define C(x,y) memset(x,y,sizeof(x))
#define STS system("pause")
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
const int Mod=1e9+7,N=55,M=2550;
int n,m,T,ans,fac[N],sum[3],cnt[3],t[N],s[N],a[N][M],b[N][N][M],f[N][N][N][4];
I add(int &x,int y){(x+=y)>=Mod?x-=Mod:0;}
IN Plus(int x,int y){(x+=y)>=Mod?x-=Mod:0;return x;}
int main(){
	read(n);read(T);
	F(i,1,n)read(t[i]),read(s[i]),s[i]--;
	fac[0]=1;F(i,1,n)fac[i]=(ll)fac[i-1]*i%Mod;
	a[0][0]=1;b[0][0][0]=1;
	F(j,1,n){
		cnt[s[j]]++;sum[s[j]]+=t[j];
		if(s[j]==1)FOR(i,cnt[1],1)FOR(k,cnt[2],0)FOR(l,sum[1]+sum[2],t[j])add(b[i][k][l],b[i-1][k][l-t[j]]);
		else if(s[j]==2)FOR(i,cnt[1],0)FOR(k,cnt[2],1)FOR(l,sum[1]+sum[2],t[j])add(b[i][k][l],b[i][k-1][l-t[j]]);
		else FOR(i,cnt[0],1)FOR(k,sum[0],t[j])add(a[i][k],a[i-1][k-t[j]]);
	}
	if(cnt[0])f[1][0][0][0]=1;if(cnt[1])f[0][1][0][1]=1;if(cnt[2])f[0][0][1][2]=1;
	F(s,2,n)F(i,0,min(cnt[0],s))F(j,0,min(cnt[1],s-i)){
		re k=s-i-j;if(k>cnt[2])continue;
		if(i)add(f[i][j][k][0],f[i-1][j][k][1]),add(f[i][j][k][0],f[i-1][j][k][2]);
		if(j)add(f[i][j][k][1],f[i][j-1][k][0]),add(f[i][j][k][1],f[i][j-1][k][2]);
		if(k)add(f[i][j][k][2],f[i][j][k-1][0]),add(f[i][j][k][2],f[i][j][k-1][1]);
	}
	F(i,0,cnt[0])F(j,0,cnt[1])F(k,0,cnt[2])f[i][j][k][3]=Plus(f[i][j][k][0],Plus(f[i][j][k][1],f[i][j][k][2]));
	ans=0;
	F(l,0,T)F(i,0,cnt[0]){
		if(!a[i][l])continue;
		F(j,0,cnt[1])F(k,0,cnt[2])if(b[j][k][T-l])add(ans,(ll)a[i][l]*b[j][k][T-l]%Mod*fac[i]%Mod*fac[j]%Mod*fac[k]%Mod*f[i][j][k][3]%Mod);
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：jianhe (赞：3)

### 前言：
一道 dp 好题。

### 思路：
由于有两个限制条件：不能相邻，总和为 $T$，答案并不好求。

那么我们考虑把两个条件分开再合并进行计算。

#### 不相邻：

设 $dp_{i,j,k,p}$ 表示第 $1$ 种歌选了 $i$ 个，第 $2$ 种歌选了 $j$ 个，第 $3$ 种歌选了 $k$ 个，前一个选了 $p$ 的方案数。则分类讨论 $p$ 得到转移方程如下：

```cpp
void no_next(){
	dp[1][0][0][1]=dp[0][1][0][2]=dp[0][0][1][3]=1;
	for(int i=0;i<=A;i++)
		for(int j=0;j<=B;j++)
			for(int k=0;k<=C;k++){
				dp[i+1][j][k][1]+=(dp[i][j][k][2]+dp[i][j][k][3])%mod,dp[i+1][j][k][1]%=mod;
				dp[i][j+1][k][2]+=(dp[i][j][k][1]+dp[i][j][k][3])%mod,dp[i][j+1][k][2]%=mod;
				dp[i][j][k+1][3]+=(dp[i][j][k][1]+dp[i][j][k][2])%mod,dp[i][j][k+1][3]%=mod;
			}
}
```
时间复杂度 $O(n^3)$。

#### 总和为 $T$：

朴素转移是 $O(n^4 T)$ 的，可能超时。

考虑优化。由于总和 $T$ 是一个定值，可以考虑把类型 $1$ 的歌曲单独拆出来计算。

设 $dp2_{i,t}$ 表示第 $1$ 种歌选了 $i$ 个，总时长为 $t$ 的方案数。跑 01 背包即可。

设 $dp3_{j,k,t}$ 表示第 $2$ 种歌选了 $j$ 个，第 $3$ 种歌选了 $k$ 个，总时长为 $t$ 的方案数。跑二维 01 背包即可。

则有：

```cpp
void tot_is_T(){
	dp2[0][0]=1;
	for(int i=1;i<=A;i++)
		for(int j=i-1;~j;j--)//01 背包
			for(int tt=T;tt>=song[1][i];tt--)
				dp2[j+1][tt]+=dp2[j][tt-song[1][i]],dp2[j+1][tt]%=mod;
	dp3[0][0][0]=1;
	for(int i=1;i<=n;i++)
		if(g[i]==2)
			for(int j=i-1;~j;j--)//二维 01 背包
				for(int k=i-1;~k;k--)
					for(int tt=T;tt>=t[i];tt--)
						dp3[j+1][k][tt]+=dp3[j][k][tt-t[i]],dp3[j+1][k][tt]%=mod;
		else if(g[i]==3)
			for(int j=i-1;~j;j--)
				for(int k=i-1;~k;k--)
					for(int tt=T;tt>=t[i];tt--)
						dp3[j][k+1][tt]+=dp3[j][k][tt-t[i]],dp3[j][k+1][tt]%=mod;
}
```

时间复杂度 $O(n^3 T)$。

#### 合并：
由于

>their order matters

即顺序要考虑，答案为两种情况相乘再分别乘上 $i,j,k$ 的阶乘。

则 $ans \leftarrow \sum_{i=0}^A \sum_{j=0}^B \sum_{k=0}^C i! j! k! \times (\sum_{p=1}^3 dp_{i,j,k,p}) \times \sum_{t=0}^T dp2_{i,t} \times dp3_{j,k,t}$。

```cpp
ll sum(ll i,ll j,ll k){
	ll ct=0;
	for(int t=0;t<=T;t++) ct+=dp2[i][t]*dp3[j][k][T-t]%mod,ct%=mod; 
	return ct*jc[i]%mod*jc[j]%mod*jc[k]%mod*(dp[i][j][k][1]+dp[i][j][k][2]+dp[i][j][k][3])%mod;
}
void get_sum(){
	for(int i=0;i<=A;i++)
		for(int j=0;j<=B;j++)
			for(int k=0;k<=C;k++)
				ans+=sum(i,j,k),ans%=mod;
}
```

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const ll N=55,MaxT=2510,mod=1e9+7;
ll n,T,ans,t[N],g[N],jc[N],A,B,C;
ll dp[N][N][N][4],dp2[N][MaxT],dp3[N][N][MaxT];
ll w[N][N][N];
vector<ll> song[4];
void init(){
	jc[0]=1;
	for(int i=1;i<=n;i++) jc[i]=jc[i-1]*i%mod;
}
void no_next(){
	dp[1][0][0][1]=dp[0][1][0][2]=dp[0][0][1][3]=1;
	for(int i=0;i<=A;i++)
		for(int j=0;j<=B;j++)
			for(int k=0;k<=C;k++){
				dp[i+1][j][k][1]+=(dp[i][j][k][2]+dp[i][j][k][3])%mod,dp[i+1][j][k][1]%=mod;
				dp[i][j+1][k][2]+=(dp[i][j][k][1]+dp[i][j][k][3])%mod,dp[i][j+1][k][2]%=mod;
				dp[i][j][k+1][3]+=(dp[i][j][k][1]+dp[i][j][k][2])%mod,dp[i][j][k+1][3]%=mod;
			}
}
void tot_is_T(){
	dp2[0][0]=1;
	for(int i=1;i<=A;i++)
		for(int j=i-1;~j;j--)
			for(int tt=T;tt>=song[1][i];tt--)
				dp2[j+1][tt]+=dp2[j][tt-song[1][i]],dp2[j+1][tt]%=mod;
	dp3[0][0][0]=1;
	for(int i=1;i<=n;i++)
		if(g[i]==2)
			for(int j=i-1;~j;j--)
				for(int k=i-1;~k;k--)
					for(int tt=T;tt>=t[i];tt--)
						dp3[j+1][k][tt]+=dp3[j][k][tt-t[i]],dp3[j+1][k][tt]%=mod;
		else if(g[i]==3)
			for(int j=i-1;~j;j--)
				for(int k=i-1;~k;k--)
					for(int tt=T;tt>=t[i];tt--)
						dp3[j][k+1][tt]+=dp3[j][k][tt-t[i]],dp3[j][k+1][tt]%=mod;
}
ll sum(ll i,ll j,ll k){
	ll ct=0;
	for(int t=0;t<=T;t++) ct+=dp2[i][t]*dp3[j][k][T-t]%mod,ct%=mod; 
	return ct*jc[i]%mod*jc[j]%mod*jc[k]%mod*(dp[i][j][k][1]+dp[i][j][k][2]+dp[i][j][k][3])%mod;
}
void get_sum(){
	for(int i=0;i<=A;i++)
		for(int j=0;j<=B;j++)
			for(int k=0;k<=C;k++)
				ans+=sum(i,j,k),ans%=mod;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>T;init();song[1].pb(0),song[2].pb(0),song[3].pb(0); 
	for(int i=1;i<=n;i++) cin>>t[i]>>g[i],song[g[i]].pb(t[i]);
	A=song[1].size()-1;
	B=song[2].size()-1;
	C=song[3].size()-1;
	no_next();
	tot_is_T();
	get_sum();
	cout<<ans;
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：2)

## 初步分析

原问题可以拆分成如下两个问题：

1. 不考虑总时长（以及歌曲的排列），计算从这 $n$ 首歌中选出 $i$ 个类型 $1$，$j$ 个类型 $2$，$k$ 个类型 $3$，且相邻歌曲类型不同的方案数。
2. 不考虑相邻歌曲类型不同（以及歌曲的排列），计算从这 $n$ 首歌中选出 $i$ 个类型 $1$，$j$ 个类型 $2$，$k$ 个类型 $3$，且总时长为 $t$ 的方案数。

两个方案数相乘，再乘上排列数 $i!j!k!$，就可以得到从这 $n$ 首歌中选出 $i$ 个类型 $1$，$j$ 个类型 $2$，$k$ 个类型 $3$，总时长为 $t$ 且相邻歌曲类型不同的方案数。

> 另一种理解方式：相当于有若干个格子和三种颜色，问题 1 负责涂色（保证相邻格子颜色不同），问题 2（乘上 $i!j!k!$）负责给每个格子放上具体的歌曲（颜色要匹配）。

枚举所有的 $i,j,k$，累加方案数，即为答案。

## 问题 1

不考虑总时长（以及歌曲的排列），计算从这 $n$ 首歌中选出 $i$ 个类型 $1$，$j$ 个类型 $2$，$k$ 个类型 $3$，且相邻歌曲类型不同的方案数。

用**状态机 DP** 解决。

定义 $c_{i,j,k,x}$ 表示从这 $n$ 首歌中选出 $i$ 个类型 $1$，$j$ 个类型 $2$，$k$ 个类型 $3$，最后一首歌的类型为 $x$ 且相邻歌曲类型不同的方案数。

枚举上一首歌的类型，那么有

$$
\begin{aligned}
c_{i+1,j,k,1} &= c_{i,j,k,2} + c_{i,j,k,3} \\
c_{i,j+1,k,2} &= c_{i,j,k,1} + c_{i,j,k,3} \\
c_{i,j,k+1,3} &= c_{i,j,k,1} + c_{i,j,k,2} \\
\end{aligned}
$$

这里用刷表法转移。

初始值 $c_{1,0,0,1} = c_{0,1,0,2} = c_{0,0,1,3} = 1$。

## 问题 2

不考虑相邻歌曲类型不同（以及歌曲的排列），计算从这 $n$ 首歌中选出 $i$ 个类型 $1$，$j$ 个类型 $2$，$k$ 个类型 $3$，且总时长为 $t$ 的方案数。

用多维 **0-1 背包**解决。

### 优化前

定义 $f_{p,i,j,k,t}$ 表示从前 $p$ 首歌中选出 $i$ 个类型 $1$，$j$ 个类型 $2$，$k$ 个类型 $3$，且总时长为 $t$ 的方案数。这需要 $\mathcal{O}(n^4T)$ 的时间和空间，太慢了。

### 优化

考虑继续拆分问题：

- 计算从这 $n$ 首歌中选出 $i$ 个类型 $1$，且总时长为 $t$ 的方案数。记作 $f_{i,t}$。
- 计算从这 $n$ 首歌中选出 $j$ 个类型 $2$，$k$ 个类型 $3$，且总时长为 $T-t$ 的方案数。记作 $g_{j,k,T-t}$。

两个方案数相乘，就是问题 2 的方案数。

这两个更小的问题，可以分别用 $\mathcal{O}(n^2T)$ 和 $\mathcal{O}(n^3T)$ 的多维 0-1 背包解决。

## 汇总

枚举 $i,j,k$。

从这 $n$ 首歌中选出 $i$ 个类型 $1$，$j$ 个类型 $2$，$k$ 个类型 $3$，总时长为 $t$ 且相邻歌曲类型不同的方案数为

$$
w_{i,j,k} = i!j!k! \cdot (c_{i,j,k,1} + c_{i,j,k,2} + c_{i,j,k,3}) \cdot \sum_{t=0}^T f_{i,t}g_{j,k,T-t}
$$

答案为

$$
\sum_{i=0}^{\textit{cnt}_1}\sum_{j=0}^{\textit{cnt}_2}\sum_{k=0}^{\textit{cnt}_3} w_{i,j,k}
$$

其中 $\textit{cnt}_x$ 为输入的 $n$ 首歌中的类型为 $x$ 的歌曲个数。

代码实现时，类型改成 $0,1,2$。

先计算问题 2，然后计算问题 1。计算问题 2 和计算答案可以在同一个枚举 $i,j,k$ 的三重循环中解决。

```go
package main
import ."fmt"

const mod = 1_000_000_007

func add(a *int, b int) {
	*a = (*a + b) % mod
}

func main() {
	var n, tot, w, tp int
	Scan(&n, &tot)

	f := make([][]int, n+2)
	for i := range f {
		f[i] = make([]int, tot+1)
	}
	f[0][0] = 1
	g := make([][][]int, n+2)
	for i := range g {
		g[i] = make([][]int, n+2)
		for j := range g[i] {
			g[i][j] = make([]int, tot+1)
		}
	}
	g[0][0][0] = 1

	cnt := [3]int{}
	for i := 0; i < n; i++ {
		Scan(&w, &tp)
		tp--
		if tp == 0 {
			for j := cnt[0]; j >= 0; j-- {
				for t := tot; t >= w; t-- {
					add(&f[j+1][t], f[j][t-w])
				}
			}
		} else {
			is := [3]int{}
			is[tp] = 1
			for j := cnt[1]; j >= 0; j-- {
				for k := cnt[2]; k >= 0; k-- {
					for t := tot; t >= w; t-- {
						add(&g[j+is[1]][k+is[2]][t], g[j][k][t-w])
					}
				}
			}
		}
		cnt[tp]++
	}

	fac := make([]int, n+1)
	fac[0] = 1
	for i := 1; i <= n; i++ {
		fac[i] = fac[i-1] * i % mod
	}

	ans := 0
	c := make([][][][3]int, cnt[0]+2)
	for i := range c {
		c[i] = make([][][3]int, cnt[1]+2)
		for j := range c[i] {
			c[i][j] = make([][3]int, cnt[2]+2)
		}
	}
	c[1][0][0][0] = 1
	c[0][1][0][1] = 1
	c[0][0][1][2] = 1
	for i, mat := range c[:cnt[0]+1] {
		for j, row := range mat[:cnt[1]+1] {
			for k, comb := range row[:cnt[2]+1] {
				sum := 0
				for t, fit := range f[i] {
					sum = (sum + fit*g[j][k][tot-t]) % mod
				}
				add(&ans, fac[i]*fac[j]%mod*fac[k]%mod*(comb[0]+comb[1]+comb[2])%mod*sum)

				add(&c[i+1][j][k][0], comb[1]+comb[2])
				add(&c[i][j+1][k][1], comb[0]+comb[2])
				add(&c[i][j][k+1][2], comb[0]+comb[1])
			}
		}
	}
	Print(ans)
}
```

**时间复杂度**：$\mathcal{O}(n^3T)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：Enoch006 (赞：0)

cf duel 到这个题，只能说，2600 虚高了。

考虑把原问题拆成两个问题：

1. 选出一个集合，使集合权值和为 $T$。
2. 对每一个集合计算其排列的方法。

注意到第二个问题只与每个编号的个数有关，因此，我们需要计算**定下每个编号的个数**，集合权值和为 $T$ 的方案数。

直接背包 DP 多记三维表每个编号选了几个即可，时间复杂度 $\mathcal{O}(n^5)$。由于是背包 DP，因此**考虑用 map 存下所有有值的地方**，这样常数很小，空间也不会爆。

第二个问题，已经知道了每个编号的个数，求相邻不能有相同的方案数。对于编号种类为 $1/2$，该问题十分容易，留给读者自己思考。

对于编号种类为 $3$ 种，考虑 DP，设 $g_{i,j,k,1/2/3}$ 表示选了 $i$ 个编号为 $1$，$j$ 个编号为 $2$，$k$ 个编号为 $3$ 的歌曲，最后一个选的是 $1/2/3$ 的方案数。转移也很好转移，**直接枚举上一个选的是什么，那么这一个就不能选他**，时间复杂度 $\mathcal{O(n^3)}$。

合并该问题，假设选了 $i$ 个编号为 $1$，$j$ 个编号为 $2$，$k$ 个编号为 $3$ 的歌曲，那么对于每个编号需要内部定序，因此答案为 $f_{T,i,j,k}\times g_{i,j,k,1/2/3}\times i!j!k!$。对于所有合法 $f_{T,i,j,k}$ 计算即可，时间复杂度 $\mathcal{O(n^3)}$。

代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 2555
#define maxn 55
#define inf 0x3f3f3f3f3f3f
#define mod 1000000007
#define msk cerr
using namespace std;
int T,n,m,ans;
int a[maxm],fac[maxm];
map<int,int>f[maxn][maxn][maxn];
int g[maxn][maxn][maxn][3];
int Ask(int x1,int x2,int x3){
    if(x1>x2)swap(x1,x2);if(x2>x3)swap(x2,x3);
    if(x1>x2)swap(x1,x2);if(x2>x3)swap(x2,x3);
    if(!x1&&!x2)return x3==1;
    if(!x1){
        int p=x3-x2;
        if(p==1)return 1*fac[x2]%mod*fac[x3]%mod;
        if(p==0)return 2*fac[x2]%mod*fac[x3]%mod;
        return 0;
    }
    int s=x1+x2+x3;
    return (g[x1][x2][x3][0]+g[x1][x2][x3][1]+g[x1][x2][x3][2])%mod*fac[x1]%mod*fac[x2]%mod*fac[x3]%mod;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    fac[0]=1;
    for(int i=1;i<=57;i++)fac[i]=fac[i-1]*i%mod;
    cin>>n>>m;f[0][0][0][0]=1;
    for(int i=1;i<=n;i++){
        int x,op;cin>>x>>op;
        // msk<<i<<"---------\n";
        for(int x1=i;x1>=0;x1--)
            for(int x2=i;x2>=0;x2--)
                for(int x3=i;x3>=0;x3--)
                    for(auto p:f[x1][x2][x3]){
                        // msk<<x1<<" "<<x2<<" "<<x3<<" "<<p.first<<" "<<p.second<<"\n";
                        int j=p.first;
                        if(j+x>m)break;
                        if(op==1)f[x1+1][x2][x3][j+x]=(f[x1+1][x2][x3][j+x]+f[x1][x2][x3][j]%mod)%mod;
                        if(op==2)f[x1][x2+1][x3][j+x]=(f[x1][x2+1][x3][j+x]+f[x1][x2][x3][j]%mod)%mod;
                        if(op==3)f[x1][x2][x3+1][j+x]=(f[x1][x2][x3+1][j+x]+f[x1][x2][x3][j]%mod)%mod;    
                    }
    } 
    g[1][0][0][0]=1;
    g[0][1][0][1]=1;
    g[0][0][1][2]=1;
    for(int i=2;i<=n;i++)
        for(int x=0;x<=i;x++)
            for(int y=0;y<=i;y++){
                int z=i-x-y;if(z<0)continue;
                if(x)g[x][y][z][0]=(g[x][y][z][0]+g[x-1][y][z][1]+g[x-1][y][z][2]%mod)%mod;
                if(y)g[x][y][z][1]=(g[x][y][z][1]+g[x][y-1][z][0]+g[x][y-1][z][2]%mod)%mod;
                if(z)g[x][y][z][2]=(g[x][y][z][2]+g[x][y][z-1][0]+g[x][y][z-1][1]%mod)%mod;
            }
    for(int x1=0;x1<=n;x1++)
        for(int x2=0;x2<=n;x2++)
            for(int x3=0;x3<=n;x3++)
                if(f[x1][x2][x3][m]){
                    // msk<<x1<<" "<<x2<<" "<<x3<<" "<<m<<"\n";
                    ans=(ans+f[x1][x2][x3][m]%mod*Ask(x1,x2,x3))%mod;
                }
    cout<<ans;
    return 0;
}
```

---

