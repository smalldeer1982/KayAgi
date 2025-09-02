# [集训队互测 2022] Range Minimum Element

## 题目描述

有一个长度为 $n$，值域为 $[1,c]$ 的正整数序列 $a$。给定 $m$ 个区间 $[l_i,r_i]$，设长度为 $m$ 的序列 $b$ 满足 $\forall i\in [1,m],b_i=\min\limits_{j=l_i}^{r_i}\{a_j\}$。求出 $a$ 在范围内任意取的情况下共能得到多少种不同的 $b$。答案对 $998244353$ 取模。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 100,1\le m\le\dfrac{n(n+1)}{2},1\le c<998244353,\forall i\in [1,m],1\le l_i\le r_i\le n$。保证给定的 $m$ 个区间两两不同。

$\operatorname{Subtask}1(5\%):n,c\le 5$。

$\operatorname{Subtask}2(10\%):c\le 100$，且对于任意两个有交点的区间一定存在其中一个包含另一个。

$\operatorname{Subtask}3(15\%):m\le 18,c=2$。

$\operatorname{Subtask}4(20\%):c=2$。

$\operatorname{Subtask}5(15\%):n,c\le 40$。

$\operatorname{Subtask}6(15\%):c\le 100$。

$\operatorname{Subtask}7(20\%):$ 无特殊限制。

#### 样例说明 1

当 $a=(1,1,1)$ 时，$b=(1,1)$。

当 $a=(1,1,2)$ 时，$b=(1,1)$。

当 $a=(1,2,1)$ 时，$b=(1,1)$。

当 $a=(1,2,2)$ 时，$b=(1,2)$。

当 $a=(2,1,1)$ 时，$b=(1,1)$。

当 $a=(2,1,2)$ 时，$b=(1,1)$。

当 $a=(2,2,1)$ 时，$b=(2,1)$。

当 $a=(2,2,2)$ 时，$b=(2,2)$。

因此共能得到 $[1,1],[1,2],[2,1],[2,2]$ 这 $4$ 种不同的 $b$。

## 样例 #1

### 输入

```
3 2 2
1 2
2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
10 11 2
1 10
2 2
3 3
5 5
6 10
6 7
6 6
7 7
8 10
8 9
10 10```

### 输出

```
129```

## 样例 #3

### 输入

```
40 40 40
31 34
9 34
4 25
36 38
8 29
8 30
6 26
17 19
6 23
36 39
11 39
2 10
32 37
32 33
33 35
17 21
8 35
31 40
11 25
11 20
8 37
26 36
22 34
17 39
28 38
26 28
11 12
12 15
12 37
1 9
11 23
5 26
8 11
1 23
12 32
7 19
22 28
20 27
8 40
19 40```

### 输出

```
567581188```

# 题解

## 作者：ningago (赞：12)

为方便表述，记 $R(f)$ 为 $f$ 的值域。

建立 $a$ 与 $b$ 的双射关系。题目中自然地有 $f:\{a\}\to\{ b\}$ 的映射，如果能为 $b$ 构造一个反映射 $g:R(f)\to\{a\}$（类似反三角），那么就可以从『计数本质不同的 $b$』转化为『求 $|R(g)|$』（由于 $g$ 是 $f$ 的反映射，故 $g$ 显然是单射）。

不妨使用贪心构造 $g$。对于某一个确定的 $b$，执行下列操作即可得到 $g(b)$：

- 初始时将 $a$ 中元素全部设置为 $+\infty$。
- 按权值从大到小遍历 $b$。
- 遍历到 $b_{[l,r]}=x$ 时，将对应的 $a$ 区间内的所有 $+\infty$ 设置为 $x$。
  - 若 $a$ 的对应区间内并不存在 $+\infty$（或已经设置过的 $x$），则代表这个 $b$ 并不存在于 $R(f)$ 中。
- 最后设置剩余的 $+\infty$ 为 $1$。

根据这个过程，可以尝试去判断某一个确定的 $a$ 是否存在于 $R(g)$ 中：

- 考虑 $a_x=1$ 的最小的 $x$。
  - 若不存在这样的 $x$，则说明所有的 $b$ 都有 $b_i>1$，且没有上述过程中『剩余的 $+\infty$』，也就是说条件为：**所有 $b_i$ 的并集为 $[1,n]$**。递归到『找最小 $a_x=2$ 』的子问题。
  - 否则，对于完全被 $[1,i-1]$ 包含的区间都有 $b_i>1$，而包含了 $i$ 的区间都有 $b_i\leq 1$。并且有条件：完全被 $[1,i-1]$ 包含的区间**的并集恰好为 $[1,i-1]$**（否则 $i$ 就不是最小的了）。递归到『找 $[1,i-1]$ 中最小 $a_x=2$』和 『找 $[1,n]$ 中次小 $a_x=1$（找 $[i+1,n]$ 中最小 $a_x=1$）』两个子问题。
  
普遍地，令 $dp_{l,r,p}$ 表示考虑区间 $[l,r]$，完全被 $[l,r]$ 包含的区间都有 $b_i\geq p$。令 $I_{l,r}$ 表示**是否**完全被 $[l,r]$ 包含的区间的并集恰好为 $[l,r]$。

则转移为：

- $dp_{l,r,p}\leftarrow I_{l,r}\times dp_{l,r,p+1}$
- $dp_{l,r,p}\leftarrow I_{l,i-1}\times dp_{l,i-1,p+1}\times dp_{i+1,r,p}$

此时复杂度为 $O(n^3c)$。

由于 DP 的转移过程是简单加乘，故**不难发现**，$dp_{l,r}$ 是一个次数为 $O(r-l)$ 的多项式 $F_{l,r}$，$dp_{l,r,p}$ 的取值为 $F_{l,r}(c-p+1)$（其中 $c-p+1$ 为 $dp_{l,r,p}$ 的迭代层数）。

在对 $c-p+1\geq O(n)$ 做区间 DP 后，用拉格朗日插值即可求出最终答案。

复杂度 $O(n^4)$。

```
#define N 110
int n, m, K;
int l_[N * N], r_[N * N];
bool ok[N][N]; int d[N];
int dp[N][N][N << 1];
int val[N << 1];

void solve()
{
	n = read(), m = read(), K = read();
	for(int i = 1; i <= m; i++) l_[i] = read(), r_[i] = read();
	for(int l = 1; l <= n; l++)
	{
		for(int r = l; r <= n; r++)
		{
			ok[l][r] = 1;
			for(int i = l - 1; i <= r + 1; i++) d[i] = 0;
			for(int i = 1; i <= m; i++) if(l <= l_[i] && r_[i] <= r) d[l_[i]]++, d[r_[i] + 1]--;
			for(int i = l; i <= r; i++) d[i] += d[i - 1], !d[i] && (ok[l][r] = 0);
		}
	}
	int tp = n + 5;
	for(int x = 1; x <= tp; x++)
	{
		for(int len = 1; len <= n; len++)
		{
			for(int l = 1, r = len; r <= n; l++, r++)
			{
				if(ok[l][r]) dp[l][r][x] = dp[l][r][x - 1];
				if(l == r) plus_(dp[l][r][x], 1);
				else plus_(dp[l][r][x], dp[l + 1][r][x]);
				if(l != r && ok[l][r - 1]) plus_(dp[l][r][x], dp[l][r - 1][x - 1]);
				for(int i = l + 1; i < r; i++)
					if(ok[l][i - 1])
						plus_(dp[l][r][x], 1ll * dp[l][i - 1][x - 1] * dp[i + 1][r][x] % mod);
			}
		}
		val[x] = dp[1][n][x];
	}
	if(K <= tp) { printf("%d\n", val[K]); return; }
	int ans = 0;
	for(int i = 1; i <= tp; i++)
	{
		int now = val[i];
		for(int j = 1; j <= tp; j++)
			if(i != j)
				mul_(now, sm(K + mod - j)), mul_(now, ksm(sm(i + mod - j), mod - 2));
		plus_(ans, now);
	}
	print(ans, '\n');
}
```

---

## 作者：_Cheems (赞：8)

题意：给定 $n$ 和 $m$ 个区间 $[l_i,r_i]$，对每个值域在 $[1,c]$ 的序列 $a$ 都生成序列 $b$，其中 $b_i=\min\limits_{j\in[l_i,r_i]}a_j$，求有多少种不同的 $b$。$n\le 100,m\le \frac {n(n+1)}2,c<998244353$。

发现这题和某道 AT 题很像，考虑固定单射，对一个 $b$ 构造一个特定的 $a$：一开始 $a$ 全是空位，从大到小考虑 $b$，对于每个区间将剩余空位填当前值（无空位无解），最后所有空位填 $1$。

然后考虑判定 $a$ 是否能由上述方式构造：从小到大考虑 $a$，先从值为 $1$ 开始，找到第一个 $a_x=1$，那么跨过该区间的 $b$ 都是 $1$ 不用管了；对于 $[1,x)$ 化归到值为 $2$ 的情况，但是有前提 $[1,x)$ 的所有区间的并必须是 $[1,x)$ 否则矛盾；对于 $(x,n]$ 化归到值为 $1$ 的情况。当然有可能不存在 $x$，那么条件还是区间并为 $[1,n]$。

容易 dp，记 $f_{i,l,r}$ 为考虑值为 $i$ 区间为 $[l,r]$ 的方案，转移如下：

* $f_{i,l,r}\gets I_{l,r}f_{i+1,l,r}$。
* $f_{i,l,r}\gets \sum\limits_{k\in [l,r]} I_{l,k-1}f_{i+1,l,k-1}f_{i,k+1,r}$。

容易拉插优化，$O(n^4)$。

---

## 作者：MaxBlazeResFire (赞：8)

update：先前的版本因疏忽把一段话重复写了两遍。

记 $f(a)$ 表示由序列 $a$ 生成的序列 $b$。

入手相当困难，考虑 $c=2$ 的 $\rm subtask$。一个 $b$ 序列合法当且仅当存在一个 $a$ 使得 $f(a)=b$，那么考虑 $2^m$ 枚举 $b$ 序列每一位的取值 $\{1,2\}$，然后将为 $2$ 的区间都赋值为 $2$，对于剩下的位置都赋值为 $1$，这样必然不劣。记这种方法构造出的序列为 $g(b)$，此时我们发现一种 $b$ 合法的判据就是 $g(b)$ 不存在一个最小值为 $1$ 的区间存在 $2$。

我们发现，当两个合法序列 $b_1\neq b_2$，那么 $g(b_1)\neq g(b_2)$，因为若 $g(b_1)=g(b_2)$，那么有 $b_1=f(g(b_1))=f(g(b_2))=b_2$，矛盾。于是我们的目标转变为计数有多少合法的 $b$ 生成的本质不同的 $g(b)$。

也就是有多少 $1,2$ 序列，满足所有极长的 $2$ 连续段都恰好可以写成若干给定线段的并。记 $v_{l,r}$ 表示区间 $[l,r]$ 是否可以写作若干给定线段的并。$dp_{i,1/2}$ 表示考虑前 $i$ 个数，第 $i$ 个数填 $1/2$ 的方案数，转移为 $\displaystyle dp_{0,1}=1,dp_{i,1}=dp_{i-1,1}+dp_{i-1,2},dp_{i,2}=\sum_{j<i}dp_{j,1}v_{j+1,i}$。

考虑 $c>2$。类比刚才 $1,2$ 的填法，我们发现对于一种 $b$ 序列，若考虑从 $1$ 到 $c$ 逐步填入，设当前要填的是 $x$，那么必然填满当前所有不在 $b_i>x$ 的区间内的没有填的所有位置，这必然不劣，重新定义 $g(b)$ 为这个过程带来的序列 $a$，我们发现仍然只需统计本质不同的 $g(b)$ 的个数。

进行区间 $\rm DP$，倒着考虑值域，记 $dp_{l,r,x}$ 表示将 $[x,c]$ 填满区间 $[l,r]$ 的答案。初始化 $f_{l,r,c}=1$。

从 $c-1$ 开始倒序枚举 $x$，每一层初始化 $dp_{i,i,x}=1+v_{i,i}dp_{i,i,x+1}$，$1$ 是因为在 $x$ 这一层 $x$ 这个数可以随意决策；而当 $[i,i]$ 合法时可以继承上一层的贡献；

枚举 $[l,r]$，先做转移 $dp_{l,r,x}\leftarrow v_{l,r}dp_{l,r,x+1}$ 继承上一层贡献，然后 $x$ 需要在 $[l,r]$ 内至少出现一次，枚举其起始位置 $s$：当 $s=l$ 时，$dp_{l,r,x}\leftarrow dp_{l+1,r,x}$；当 $s=r$ 时 $dp_{l,r,x}\leftarrow v_{l,r-1}dp_{l,r-1,x+1}$；然后枚举 $s\in[l+1,r-1]$，转移 $dp_{l,r,x}\leftarrow v_{l,s-1}dp_{l,s-1,x+1}\times dp_{s,r,x}$。

答案为 $dp_{1,n,1}$，复杂度 $O(n^3c)$。

当 $c$ 更大时怎么办？注意到本题的方案数实际上只与 $a$ 数列本质能取的数的数量有关。也就是说，存在一个数列 $p_i$ 表示 $a$ 数列总计有 $i$ 种本质不同取值时的答案，使得总答案为一个有关 $p_i$ 的常系数组合。于是答案必然是一个关于 $c$ 的多项式，它的次数最多为 $n$。

注意到对于刚才的转移方程，$dp_{1,n,x}$ 本质上就是取值有 $c-x+1$ 个时的答案，于是我们将求解完之后的所有 $dp_{1,n,i},i
\in[1,n+1]$ 当作点值，插值即可。

复杂度 $O(n^4)$。
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 105
#define mod 998244353

inline void chkadd( int &x , int k ){ x += k; if( x >= mod ) x -= mod; }
inline void chkequ( int &x , int k ){ x = k; if( x >= mod ) x -= mod; }
inline int fp( int x , int p ){ int res = 1; while( p ){ if( p & 1 ) res = 1ll * res * x % mod; x = 1ll * x * x % mod; p >>= 1; } return res; }
inline int reduce( int x ){ return x + ( x >> 31 & mod ); }

int n,m,c,l[MAXN * MAXN],r[MAXN * MAXN],dif[MAXN];
int f[MAXN][MAXN],dp[MAXN][MAXN][MAXN],val[MAXN];

signed main(){
	scanf("%d%d%d",&n,&m,&c);
	for( int i = 1 ; i <= m ; i ++ ) scanf("%d%d",&l[i],&r[i]);
	for( int L = 1 ; L <= n ; L ++ ){
		for( int R = L ; R <= n ; R ++ ){
			int cnt = 0;
			for( int j = 1 ; j <= n + 1 ; j ++ ) dif[j] = 0;
			for( int j = 1 ; j <= m ; j ++ ) if( l[j] >= L && r[j] <= R ) cnt ++,dif[l[j]] ++,dif[r[j] + 1] --;
			for( int j = 1 ; j <= n ; j ++ ) dif[j] += dif[j - 1];
			bool flag = 0;
			for( int p = L ; p <= R ; p ++ ) if( !dif[p] ){ flag = 1; break; }
			f[L][R] = !flag;
		}
	}
	for( int l = 1 ; l <= n ; l ++ ) for( int r = l ; r <= n ; r ++ ) dp[l][r][n + 1] = 1;
	for( int x = n ; x >= 1 ; x -- ){
		for( int i = 1 ; i <= n ; i ++ ) dp[i][i][x] = 1 + f[i][i] * dp[i][i][x + 1];
		for( int len = 2 ; len <= n ; len ++ ){
			for( int l = 1 ; l + len - 1 <= n ; l ++ ){
				int r = l + len - 1;
				chkequ( dp[l][r][x] , dp[l + 1][r][x] + f[l][r] * dp[l][r][x + 1] );
				if( f[l][r - 1] ) chkadd( dp[l][r][x] , dp[l][r - 1][x + 1] );
				for( int k = l + 1 ; k <= r - 1 ; k ++ )
					if( f[l][k - 1] ) chkadd( dp[l][r][x] , 1ll * dp[l][k - 1][x + 1] * dp[k + 1][r][x] % mod );
			}
		}
	}
	for( int i = 1 ; i <= n + 1 ; i ++ ) val[n - i + 2] = dp[1][n][i];
	int Ans = 0;
	for( int i = 1 ; i <= n + 1 ; i ++ ){
		int fra = 1;
		for( int j = 1 ; j <= n + 1 ; j ++ ){
			if( i == j ) continue;
			fra = 1ll * fra * reduce( c - j ) % mod * fp( reduce( i - j ) , mod - 2 ) % mod;
		}
		chkadd( Ans , 1ll * val[i] * fra % mod );
	}
	printf("%d\n",Ans);
	return 0;
}
```

---

## 作者：cwfxlh (赞：5)

# [P10008](https://www.luogu.com.cn/problem/P10008)     

没用插值的做法（其实差不多）。         

考虑从小往大填每个元素的值，填完一个元素后，包含这个元素的区间的 $\min$ 就固定了。于是初步考虑区间 $dp$。对于 $[l,r]$，只考虑被 $[l,r]$ 包含的区间。令 $dp_{l,r,x}$ 表示只考虑区间 $[l,r]$，当前能填的最小值是 $x$，转移的时候要么转移到 $dp_{l,r,x+1}$，要么枚举第一个填 $x$ 的位置，就可以转移了。         

然而实际上，这样转移有很大的问题。首先，必须强制钦定第一个填 $x$ 的位置有区间覆盖它，否则这样填不会对 $b$ 序列造成影响，会算重。       

另外，令覆盖了位置 $A$ 的区间集合为 $S_A$，则如果存在 $B\in[l,A)$，且 $S_B\in S_A,S_B\not=\empty$，那么不能选 $A$。原因在于，选 $A$ 作为第一个填 $x$ 位置所生成的 $b$ 序列，与 $B$ 和 $A$ 都填 $x$，且 $B$ 是第一个填 $x$ 的位置所生成的 $b$ 序列是没有区别的，这样会算重。              

怎么判断 $S_B\in S_A$ 呢，对于每个点算出覆盖它的区间的最小右端点，判断是否包含 $A$ 即可。最小右端点可以使用 $O(1)$ 区间取 $\max$，$O(n\log n)$ 下放的方式求出（即 ST 表）。           

最后得到 $dp_{1,n,i}$，表示使用 $i$ 种颜色去填的方案数，容斥一下得到 $b$ 序列中有 $i$ 种颜色的方案数，然后乘上 $\binom{i}{c}$ 就可以了。


最终复杂度 $O(n^4+n^2m)$。                  

代码：            


```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
int n,m,c,l[500003],r[500003],dp[103][103][103],f[103],C[103][103],v[103][103],ans,ny[103],k1,k2,k3,k4,k5,mnv[103];
int ST[103][23],lg[103];
int fstp(int X,int Y){
    int ret=1,bse=X;
    while(Y){
        if(Y%2)ret=ret*bse%MOD;
        bse=bse*bse%MOD;
        Y/=2;
    }
    return ret;
}
int getC(int X,int Y){
    if(X<Y||X<0||Y<0)return 0;
    int ret=1;
    for(int i=X;i>=X-Y+1;i--)ret=ret*i%MOD;
    for(int i=1;i<=Y;i++)ret=ret*ny[i]%MOD;
    return ret;
}
signed main(){
    ios::sync_with_stdio(false);
    for(int i=1;i<=100;i++)ny[i]=fstp(i,MOD-2);
    for(int i=0;i<=100;i++)C[i][0]=1;
    for(int i=2;i<=100;i++)lg[i]=lg[i>>1]+1;
    for(int i=1;i<=100;i++){
        for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
    }
    cin>>n>>m>>c;
    for(int i=1;i<=m;i++)cin>>l[i]>>r[i];
    for(int i=1;i<=m;i++)v[l[i]][r[i]]=1;
    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            k1=k2=0;
            for(int u=i;u<=j;u++)if(v[i][u])k1=u;
            for(int u=j;u>=i;u--)if(v[u][j])k2=u;
            if(k1>=k2-1)v[i][j]=1;
        }
    }
    for(int i=0;i<=n+2;i++){
        for(int j=1;j<=n+1;j++)dp[j][j-1][i]=1;
    }
    for(int i=1;i<=n+1;i++)v[i][i-1]=1;
    for(int len=1;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            for(int u=i;u<=j;u++){
                for(int o=0;o<=20;o++)ST[u][o]=n+1;
            }
            for(int u=1;u<=m;u++){
                if(l[u]>=i&&r[u]<=j){
                    ST[l[u]][lg[r[u]-l[u]+1]]=min(ST[l[u]][lg[r[u]-l[u]+1]],r[u]);
                    ST[r[u]-(1<<lg[r[u]-l[u]+1])+1][lg[r[u]-l[u]+1]]=min(ST[r[u]-(1<<lg[r[u]-l[u]+1])+1][lg[r[u]-l[u]+1]],r[u]);
                }
            }
            for(int u=20;u;u--){
                for(int o=i;o+(1<<u)-1<=j;o++){
                    ST[o][u-1]=min(ST[o][u-1],ST[o][u]);
                    ST[o+(1<<(u-1))][u-1]=min(ST[o+(1<<(u-1))][u-1],ST[o][u]);
                }
            }
            for(int u=i;u<=j;u++)mnv[u]=ST[u][0];
            dp[i][j][1]=1;
            for(int u=i;u<=j;u++){
                if(mnv[u]==n+1)continue;
                k2=0;
                for(int o=i;o<u;o++){
                    if(mnv[o]>=u&&mnv[o]!=n+1)k2=1;
                }
                if(k2)continue;
                for(int o=2;o<=n;o++)dp[i][j][o]=(dp[i][j][o]+dp[i][u-1][o-1]*dp[u+1][j][o])%MOD;
            }
            for(int o=2;o<=n;o++)dp[i][j][o]=(dp[i][j][o]+dp[i][j][o-1])%MOD;
        }
    }
    for(int i=1;i<=n;i++)f[i]=dp[1][n][i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++)f[i]=(f[i]-f[j]*C[i][j])%MOD;
    }
    for(int i=1;i<=n;i++)ans=(ans+f[i]*getC(c,i))%MOD;
    ans%=MOD;
    ans+=MOD;
    ans%=MOD;
    cout<<ans;
    return 0;
}
```

---

## 作者：caibet (赞：2)

非常值得推敲的题目。这里给出一个比较完整且略微不同的思路。

首先如果从小到大填数，则填完一个数后这个数左边和右边就是独立的。我们定义 $f_{l,r,k}$ 表示当前考虑区间 $[l,r]$，有 $k$ 个可用的数（当前填最小的那个）时，最终生成的 $\{b\}$ 有多少种可能。

初步考虑可能会想到枚举哪个位置 $p$ 第一个放最小的数，然后用 $f_{l,p-1,k-1}\times f_{p+1,r,k}$ 进行类似转移，可惜没有考虑已经填过的区间的影响会导致此方法算重，例如有区间 $[1,2]$ 时下标 $1,2$ 分别放 $1,1$ 和 $1,2$ 和 $2,1$ 等等会被视为不同方案，但区间最小值都为 $1$。我们考虑构造一种填数方法，使得每一种填数恰好和一种 $\{b\}$ 一一对应。

考虑到这个 dp 的本质是选择区间中的一个子序列填上当前需要填的数，再分为若干个子区间作为子问题，这个过程会确定若干个 $b_i$。然而已知确定了哪些 $b_i$ 时，可能会有多个子序列满足，我们不妨只计数**字典序最小**的那个子序列。为了简化填法不妨钦定子序列必须以 $r+1$ 作为结束标志，这样字典序最小的子序列一定是把不被 未确定的 $b_i$ 对应区间 覆盖的位置全部填上当前的数，自然语言就是“能填就填”。举个例子：

- dp 到 $[1,6]$ 时，确定了 $[1,2],[4,5]$，未确定 $[3,4]$。
- 则字典序最小的填法就是 $\texttt{xx..xx}$，也就是子序列 $\{1,2,5,6,7\}$。

那我们考虑如何计数这个字典序最小的子序列。dp 过程中，对于 $[l,r]$，我们钦定的是最小值第一个放的位置 $p$，此时如果 $[l,p)$ 内有未被覆盖的空位，我们第一个最小值放在这个空位上显然字典序更小且不影响 $b$ 的确定，那么这个 $p$ 也就并不合法。

也就是说：对于一个固定的 $l$，$p$ 合法当且仅当 $[l,p)$ 内所有 *确定 $b$ 的区间* 的并恰为 $[l,p)$。个人感觉这个东西非常巧妙，以样例为例，区间为 $[1,2]$ 和 $[2,3]$ 时：

- $l=1$ 时 $p$ 可为 $1,3,4$；
- $l=2$ 时 $p$ 可为 $2,4$；
- $l=3$ 时 $p$ 可为 $3$。

这样可以生成的子序列有：

- $\{1,2,3,4\}$，对应确定区间 $[1,2]$ 和 $[2,3]$；
- $\{1,4\}$，对应确定区间 $[1,2]$；
- $\{3,4\}$，对应确定区间 $[2,3]$；
- $\{4\}$，对应不确定任一区间。

得到这一点后就豁然开朗了，我们对于每个 $l$ 预处理出合法的 $p$，只用这些 $p$ 做最开始的区间 dp 即可。

最后可以得到使用不同数字数量 $\le$ 某个 $k$ 时的方案数，由于超过 $n$ 个是无效的，可以直接二项式反演后运用组合数求解。

时间复杂度 $O(n^4+nm)$。

```cpp
namespace{
//
const int N=103,mod=998244353;
template<class T>inline void add(T&x,T y){
	x+=y;x=x<mod?x:x-mod;
}
int n,m,c;
ll f[N][N][N],res[N],inv[N];
vector<int> b[N],nxt[N];
ll C(ll b,ll a){
	if(a>b) return 0;
	ll res=1;
	for(int i=1;i<=a;++i){
		res=res*inv[i]%mod*(b-i+1)%mod;
	}
	return res;
}
void work(){
	n=read();m=read();c=read();
	for(int i=1;i<=m;++i){
		int x=read(),y=read();
		b[y].pb(x);
	}
	for(int i=1;i<=n;++i){
		// 直接记录最远的空位
		int pos=0;
		for(int r=i;r<=n+1;++r){
			if(!pos){
				nxt[i].pb(r);
				pos=r;
			}
			for(int l:b[r]){
				if(l<i) continue;
				if(l<=pos) pos=0;
			}
		}
	}
	for(int i=1;i<=n+1;++i) for(int k=0;k<=n;++k) f[i][i-1][k]=1; 
	for(int l=1;l<=n;++l){
		for(int i=1;i+l-1<=n;++i){
			int j=i+l-1;
			for(int k=1;k<=n;++k){
				for(int p:nxt[i]){
					add(f[i][j][k],f[i][p-1][k-1]*(p>j?1:f[p+1][j][k])%mod);
					if(p>j) break;
				}
			}
		}
	}
	inv[1]=1;
	for(int i=2;i<=n;++i) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	ll ans=0;
	for(int i=1;i<=n;++i){
		res[i]=f[1][n][i];
		for(int j=1;j<i;++j){
			add(res[i],mod-res[j]*C(i,j)%mod);
		}
		add(ans,res[i]*C(c,i)%mod);
	}
	cout<<ans;
}
}
```

---

## 作者：drmr (赞：1)

做完 $c = 2$ 就做完了。

考虑如何判定一个 $b$ 是否合法。对于每一个条件 $\min_{i = l}^{r} a_i = x$ 等价于 $\forall i \in [l, r], a_i > x$。先维护出每个位置可能取到的最小值 $c_i$，此时一组合法的解为 $a_i = c_i$。证明显然。

在 $x$ 轴长 $n$，$y$ 轴长 $c$ 的平面直角坐标系中，区间 $[l, r]$ 的最小值为 $x$ 则作出矩形，左上角 $(l, x)$，右下角 $(r, 1)$。则一个位置 $p$ 的最小值为直线 $x = p$ 中最下方没有被覆盖的点。此时一组合法的 $b$ 与所有矩形的交两两对应。

对矩形的上边缘动态规划。对于 $c = 2$ 的情况，当一段连续的位置 $[l, r]$ 中的值都是 $2$，则绝对存在一些区间的并为 $[l, r]$，并且它们都取 $2$。因此对于一个区间 $[l, r]$ 预处理出 $o_{l, r}$ 表示是否可以选择一些区间的并集为 $[l, r]$。这显然可以通过离线以及线段树做到 $O(n^2 \log n)$（这是由于前一天的模拟赛刚好考到了这个题，也可以用 $O(n^4)$ 做。）

对于 $c \in (2, n]$ 可以通过 $c - 1$ 次动态规划进行。具体来讲，每一次考虑值域在 $[k, c]$ 中的值，对于 $k$ 当做 $1$，$(k, c]$ 当做 $2$。从一段连续段中乘以上一次 $dp$ 的值。

对于 $c > n$ 只需乘以组合数即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 205;
const int Mod = 998244353;
int n, m, c, q, f[N][N][N], ok[N][N], val[100000], tag[100000];
int g[N], ans;

struct node{int l, r, op;}s[20000];
bool cmp(node a, node b){
	if(a.r != b.r) return a.r < b.r;
	if(a.op != b.op) return a.op < b.op;
	return a.l < a.r;
}
void pushDown(int u){
	val[u << 1] = max(val[u << 1], tag[u]);
	tag[u << 1] = max(tag[u << 1], tag[u]);
	val[u << 1 | 1] = max(val[u << 1 | 1], tag[u]);
	tag[u << 1 | 1] = max(tag[u << 1 | 1], tag[u]);
	tag[u] = 0;
	return ;
}
void pushUp(int u){
	val[u] = min(val[u << 1], val[u << 1 | 1]);
	return ;
}
void Modify(int u, int l, int r, int ql, int qr, int v){
	if(ql <= l && r <= qr){
		tag[u] = max(tag[u], v);
		val[u] = max(val[u], v);
		return ;
	}
	pushDown(u);
	int mid = (l + r) >> 1;
	if(ql <= mid) Modify(u << 1, l, mid, ql, qr, v);
	if(mid < qr) Modify(u << 1 | 1, mid + 1, r, ql, qr, v);
	pushUp(u);
	return ;
}
int Query(int u, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr)
		return val[u];
	pushDown(u);
	int mid = (l + r) >> 1, res = 1e9;
	if(ql <= mid) res = min(res, Query(u << 1, l, mid, ql, qr));
	if(mid < qr) res = min(res, Query(u << 1 | 1, mid + 1, r, ql, qr));
	return res;
}

int qpow(int x, int y){
	int res = 1;
	while(y){
		if(y & 1) res = res * x % Mod;
		x = x * x % Mod;
		y >>= 1;
	}
	return res;
}
int C(int n, int m){
	int p = 1, q = 1;
	for(int i = 1; i <= m; i++){
		q = q * i % Mod;
		p = p * (n - i + 1) % Mod;
	}
	return p * qpow(q, Mod - 2) % Mod;
}

void solve(){
	for(int i = 1; i <= n + 1; i++)
		for(int j = i; j <= n + 1; j++)
			f[0][i][j] = 1;
	for(int i = c - 1; i >= c - n + 1; i--){
		for(int j = 1; j <= n; j++){
			f[c - i][j][j - 1] = 1;
			for(int k = j; k <= n + 1; k++){
				f[c - i][j][k] = f[c - i][j][k - 1];
				for(int l = j; l <= k - 1; l++){
					if(ok[l][k - 1]) f[c - i][j][k] = (f[c - i][j][k] + f[c - i][j][l - 1] * f[c - i - 1][l][k] % Mod) % Mod;
				}
			}
		}
	}

	for(int i = 1; i <= n; i++){
		g[i] = f[i - 1][1][n + 1];
		for(int k = 1; k <= i - 1; k++)
			g[i] = (g[i] - g[k] * C(i, k) % Mod + Mod) % Mod;
		ans = (ans + g[i] * C(c, i) % Mod) % Mod;
	}
	cout << ans << "\n";
	return ;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> c;
	for(int i = 1; i <= m; i++){
		cin >> s[i].l >> s[i].r, s[i].op = 0;
	}
	for(int i = 1; i <= n; i++){
		for(int j = i; j <= n; j++){
			s[++q + m].l = i, s[q + m].r = j;
			s[q + m].op = 1;
		}
	}
	sort(s + 1, s + 1 + m + q, cmp);
	for(int i = 1; i <= m + q; i++){
		if(!s[i].op) Modify(1, 1, n, s[i].l, s[i].r, s[i].l);
		else ok[s[i].l][s[i].r] = (Query(1, 1, n, s[i].l, s[i].r) >= s[i].l);
	}

	if(c >= n + 2){
		solve();
		return 0;
	}

	for(int i = 1; i <= n + 1; i++)
		for(int j = i; j <= n + 1; j++)
			f[c][i][j] = 1;
	for(int i = c - 1; i >= 1; i--){
		for(int j = 1; j <= n; j++){
			f[i][j][j - 1] = 1;
			for(int k = j; k <= n + 1; k++){
				f[i][j][k] = f[i][j][k - 1];
				for(int l = j; l <= k - 1; l++){
					if(ok[l][k - 1]) f[i][j][k] = (f[i][j][k] + f[i][j][l - 1] * f[i + 1][l][k] % Mod) % Mod;
				}
			}
		}
	}
	cout << f[1][1][n + 1] << "\n";
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P10008)

**题目大意**

> 给定长度为 $n$，值域 $[1,c]$ 的序列 $a$，给定 $m$ 个区间 $[l_i,r_i]$，定义 $b_i=\max_{l_i\le j\le r_i} a_j$，求所有 $a$ 共能得到多少个本质不同的 $b$。
>
> 数据范围：$n\le 100,m\le\dfrac{n(n+1)}2,c\le 10^9$。

**思路分析**

若 $a$ 能生成 $b$，我们记 $b=f(a)$。

考虑将每个 $b$ 唯一对应到 $a$ 上，从小到大依次枚举 $i=1\sim c$，把不被任何一个 $b_j>i$ 的区间 $[l_j,r_j]$ 包含，且 $a_x$ 未被确定的 $a_x$ 赋值成 $i$，记此时的 $a$ 为 $g(b)$。

容易证明一组 $b$ 合法当且仅当 $g(b)$ 生成的序列能生成 $b$，即 $f(g(b))=b$。

容易发现两个不同的合法 $b$ 序列对应的 $g(b)$ 也一定不同。

进一步，每个不合法的 $b$ 序列唯一对应一个合法的 $b$ 序列使得他们的 $g(b)$ 相同。

因此我们只要计数多少个 $a$ 可能被某个 $b$ 作为 $g(b)$ 生成（$b$ 不一定要合法）。

那么考虑区间 dp：$dp_{l,r,i}$ 表示仅考虑区间 $[l,r]$，值域 $[1,i]$ 的方案数。

枚举第一个填 $1$ 的位置 $p$，可以拆成区间 $[l,p)$ 的值域 $[2,i]$，区间 $(p,r]$ 值域 $[1,i]$ 的两个子问题，从 $dp_{l,p-1,i-1}\times dp_{p+1,r,i}$ 转移。

但我们钦定了 $p$ 是区间内第一个 $1$，那么 $[l,p-1]$ 都要至少被一个 $>1$ 的区间覆盖，很显然把 $[l,p-1]$ 中的所有区间 $b$ 都设为 $>1$ 的数即可。

因此一个 $p$ 合法当且仅当 $[l,p-1]$ 内部所有区间的并恰好为 $[l,p-1]$。

预处理合法区间然后 dp，答案为 $dp_{1,n,c}$，时间复杂度 $\mathcal O(n^3c)$。

注意到 $dp_{l,r,i}$ 可以看成一个和 $i$ 有关的 $\mathcal O(r-l)$ 次多项式，可以归纳证明。

那么求出 $dp_{1,n,0\sim n}$ 然后拉格朗日插值求出 $dp_{1,n,c}$ 即可。

时间复杂度 $\mathcal O(n^2m+n^4)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=105,MAXM=5105,MOD=998244353;
ll ksm(ll a,ll b=MOD-2) {
	ll ret=1;
	for(;b;a=a*a%MOD,b>>=1) if(b&1) ret=ret*a%MOD;
	return ret;
}
int L[MAXM],R[MAXM],cov[MAXN];
ll dp[MAXN][MAXN][MAXN];
bool ok[MAXN][MAXN];
signed main() {
	int n,m,c;
	scanf("%d%d%d",&n,&m,&c);
	for(int i=1;i<=m;++i) scanf("%d%d",&L[i],&R[i]);
	for(int l=1;l<=n;++l) for(int r=l;r<=n;++r) {
		ok[l][r]=true,memset(cov,0,sizeof(cov));
		for(int i=1;i<=m;++i) if(l<=L[i]&&R[i]<=r) ++cov[L[i]],--cov[R[i]+1];
		for(int i=l;i<=r;++i) cov[i]+=cov[i-1],ok[l][r]&=(cov[i]!=0);
	}
	for(int l=0;l<=n+1;++l) for(int r=0;r<=n+1;++r) dp[1][l][r]=1;
	int mx=n+3;
	for(int o=2;o<=mx;++o) {
		auto f=dp[o],g=dp[o-1];
		for(int l=0;l<=n;++l) f[l+1][l]=1;
		for(int len=1;len<=n;++len) for(int l=1,r=len;r<=n;++l,++r) {
			if(ok[l][r]) f[l][r]=g[l][r];
			for(int p=l;p<=r;++p) if(p==l||ok[l][p-1]) {
				f[l][r]=(f[l][r]+g[l][p-1]*f[p+1][r])%MOD;
			}
		}
	}
	if(c<=mx) return printf("%lld\n",dp[c][1][n]),0;
	ll ans=0;
	for(int i=1;i<=mx;++i) {
		ll val=dp[i][1][n];
		for(int j=1;j<=mx;++j) if(i^j) {
			val=val*(c-j)%MOD*ksm((i+MOD-j)%MOD)%MOD;
		}
		ans=(ans+val)%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：WrongAnswer_90 (赞：0)

# [My Blogs](https://www.cnblogs.com/WrongAnswer90/p/18350906)

### [P10008 [集训队互测 2022] Range Minimum Element](https://www.luogu.com.cn/problem/P10008)

难点在于双射构造。

首先考虑给定了 $b$ 如何进行判定。从小到大填数 $x$，每次把能填的地方（$b_i>x$ 的区间之外）全部填上 $x$，这样填一定是最优的。合法当且仅当这样生成的序列 $a$ 对应的 $b$ 就是 $b$ 本身。

发现通过这样的生成方式，合法的 $a$ 和 $b$ 是一一对应的，所以对 $b$ 计数可以转为对能被这样生成的 $a$ 计数。

如果给定了 $a$，如何判 $a$ 是否合法？找到第一个最小值的位置 $p$，把 $A[1,n]$ 变成 $A[1,p-1]$ 和 $A[p+1,n]$。因为 $[1,p-1]$ 中并没有被填上最小值，所以被 $[1,p-1]$ 包含的区间一定选择的都是大于最小值的数，并且他们的的并集一定是 $[1,p-1]$。然后递归判断 $A[1,p-1]$ 和 $A[p+1,n]$ 是否合法。

上述过程是值域从小到大，分裂序列。计数就考虑值域从大到小，合并序列。$f_{l,r,x}$ 表示区间 $[l,r]$ 填入了 $[x,c]$ 中的数的方案数。转移就是枚举最小值的位置 $p$：

$$
\begin{aligned}
f_{l,r,x}&\leftarrow [[l,r]\text{合法}]\times f_{l,r,x+1}\\
f_{l,r,x}&\leftarrow [[l,p-1]\text{合法}]\times f_{l,p-1,x+1}\times f_{p+1,r,x}
\end{aligned}
$$

第一种转移表示区间内没有 $=x$ 的数。预处理合法区间，暴力做复杂度是 $\mathcal O(n^3c)$。套路性的，不难归纳证明 $f_{l,r,x}$ 是一个关于 $x$ 的 $\mathcal O(r-l)$ 次多项式。

令 $x\leftarrow c-x+1$，这样可以暴力求得 $f_{1,n,1\sim n+1}$，然后可以拉插出 $x=c$ 的点值，复杂度是 $\mathcal O(m+n^4)$。

```cpp
int n,m,K,f[110][110][110];
bool v[110][110];
inline void mian()
{
	read(n,m,K);int x,y,ans=0;
	while(m--)read(x,y),v[x][y]=1;
	for(int i=n;i>=1;--i)
	{
		for(int j=i;j<=n;++j)
		{
			int x=-1,y=-1;
			for(int k=j;k>=i;--k)if(v[i][k]){x=k;break;}
			for(int k=i;k<=j;++k)if(v[k][j]){y=k;break;}
			if(x==-1||y==-1)continue;
			v[i][j]|=x>=y-1;
		}
	}
	for(int i=1;i<=n;++i)v[i][i-1]=1;
	for(int i=1;i<=n;++i)for(int j=i;j<=n;++j)f[1][i][j]=1;
	for(int i=1;i<=n+1;++i)for(int j=1;j<=n+1;++j)f[i][j][j-1]=1;
	for(int x=2;x<=n+1;++x)
	{
		for(int i=n;i>=1;--i)
		{
			for(int j=i;j<=n;++j)
			{
				if(v[i][j])f[x][i][j]=f[x-1][i][j];
				for(int k=i;k<=j;++k)if(v[i][k-1])
				Madd(f[x][i][j],Cmul(f[x-1][i][k-1],f[x][k+1][j]));
			}
		}
	}
	for(int i=1;i<=n+1;++i)
	{
		int v=1,x=1;
		for(int j=1;j<=n+1;++j)if(i!=j)Mmul(v,Cdel(i,j)),Mmul(x,Cdel(K,j));
		Madd(ans,Cmul(x,power(v,MOD-2),f[i][1][n]));
	}
	write(ans);
}
```

---

## 作者：xcyyyyyy (赞：0)

### [集训队互测 2022] Range Minimum Element

感觉这里把 $a$ 的合法条件说清楚了。

考虑 $c=2$，此时合法的 $b$ 一定满足 $b_i=2$ 的区间并不完全包含任何一个 $b_i=1$ 的区间。

这样的 $b$ 一定可以映射到一个 $a$ 上，满足所有为 $2$ 的极长段必须是某些段的并，我们直接处理出哪些区间是可以为某些段的并，直接设 $f_{i,1/2}$ 转移即可。

考虑扩展到 $c$ 为任意值的时候，此时我们考虑合法的 $b$ 一定满足任意一个区间 $i$，对于所有 $b_j \gt b_i$ 的区间并一定不会全部被包含，然后将他区间内没有被 $b_j \gt b_i$ 覆盖的点直接染成 $b_i$。

这样染色所对应的 $a$ 一定满足：$\forall x \in(1,c]$，颜色 $\geq x$ 的极长段一定是某些区间的并。

考虑用区间 dp 刻画这个过程，设 $f_{i,l,r}$ 表示在 $[l,r]$ 区间内填上 $[i,c]$ 颜色的方案数，设 $w_{l,r}$ 表示其能否拆成一个区间。继承 $f_{i+1}$ 的答案后，直接枚举该区间内第一个为 $i$ 颜色的点即可。

观察数据范围不难想到可以用拉格朗日插值。

---

## 作者：Graphcity (赞：0)

比较笨的方法。

我们首先考虑判断一组 $b_{1\cdots m}$ 是否合法。我们按照值域从大到小扫描每个数。扫描到 $i$ 时，将所有最小值 $>i$ 的区间都打上标记。如果所有最小值 $=i$ 的区间都至少有一个位置没有被打上标记，那就是合法的。不难发现这是充要条件。

考虑使用区间 DP 刻画这个判定的过程。设 $f_{l,r,i}$ 表示仅考虑被 $[l,r]$ 包含的所有区间，共有 $i$ 种不同的最小值的方案数。为了方便，我们要求所有被 $[l,r]$ 包含的区间的并恰好为 $[l,r]$。

假设这些区间组成的集合为 $S$，我们考虑选择其中一个子集 $T$ 表示 **非 $S$ 中最小值** 组成的集合。考虑判断所选择的 $T$ 是否满足要求：首先，$T\not= S$，否则就不存在最小值了；其次，不存在 $S\oplus T$ 中的某个区间 $[l_1,r_1]$ 被 $T$ 中区间的并包含，否则这个区间所有数字都被打上标记了。注意到这个就是充要条件。

考虑刻画这个 $T$。注意到 $T$ 的并可以被刻画成若干个不相邻的子区间 $[l_1,r_1],[l_2,r_2],\cdots,[l_k,r_k]\ (r_i+1<l_{i+1})$。对于 $[l_i,r_i]$，它需要满足所有被 $[l_i,r_i]$ 包含的区间的并恰好为 $[l_i,r_i]$。注意到这个跟 $f_{l,r}$ 是否合法的判定条件相同，满足子结构性质。对于 $T\not=S$ 的限制，只需要保证  $[l_1,r_1]\not=[l,r]$ 即可，这个是简单的。

转移 $f_{l,r,*}$ 时，可能需要一个辅助数组 $g_{i,k}$，表示 $T$ 中最后一个子区间的结尾为 $i$，且数字种类为 $k$ 时的方案数。$g$ 的转移是简单的。统计答案时，只需要对于所有区间并所划分出来的每一个极长的子区间，找出它们的 $f$ 值。注意到每个子区间是独立的，乘起来就可以了。

总时间复杂度 $O(n^4)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=100,Mod=998244353;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,m,c,R[Maxn+5],C[Maxn+5][Maxn+5];
vector<int> v[Maxn+5];
int f[Maxn+5][Maxn+5][Maxn+5];
int h[Maxn+5][Maxn+5][Maxn+5];
int chk[Maxn+5][Maxn+5];

inline int Get(int x,int y)
{
    if(x<y || y<0) return 0; int res=1;
    For(i,1,y) res=1ll*res*(x-i+1)%Mod*Pow(i,Mod-2)%Mod;
    return res;
}

int main()
{
    cin>>n>>m>>c; C[0][0]=1;
    For(i,1,n) {C[i][0]=1; For(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;}
    For(i,1,m) {int l,r; cin>>l>>r; v[l].push_back(r);}
    For(l,1,n) For(r,l,n)
    {
        int mxr=l-1; For(p,l,r)
        {
            for(auto q:v[p]) if(q<=r) mxr=max(mxr,q);
            if(mxr<p) break;
        } if(mxr==r) chk[l][r]=1;
    }
    Rof(l,n,1)
    {
        static int g[Maxn+5][Maxn+5];
        For(i,l-1,n) For(j,1,n) g[i][j]=0;
        For(i,1,n) g[l-1][i]=1;
        For(r,l,n)
        {
            static int val[Maxn+5];
            memset(val,0,sizeof(val));
            Rof(j,max(r-2,l-1),l-1)
            {
                if(j+2<=r && chk[j+2][r]) For(k,1,n) val[k]=(val[k]+h[j+2][r][k])%Mod;
                For(k,1,n) g[r][k]=(g[r][k]+1ll*val[k]*g[j][k])%Mod;
            }
            if(!chk[l][r]) continue;
            f[l][r][1]=1; memset(val,0,sizeof(val));
            For(i,1,n)
            {
                For(j,l,r) val[i]=(val[i]+g[j][i])%Mod;
                For(j,1,i-1) val[i]=(val[i]-1ll*val[j]*C[i][j]%Mod+Mod)%Mod;
                f[l][r][i+1]=val[i];
            }
            For(i,1,n) if(f[l][r][i]) For(j,i,n) h[l][r][j]=(h[l][r][j]+1ll*f[l][r][i]*C[j][i])%Mod;
            For(k,1,n) g[r][k]=(g[r][k]+h[l][r][k])%Mod;
        }
    }
    int ans=1;
    for(int l=1,r;l<=n;)
    {
        for(r=n;r>=l;--r) if(chk[l][r]) break;
        if(r<l) {l++; continue;} int res=0;
        For(i,1,min(n,c)) if(f[l][r][i])
            res=(res+1ll*f[l][r][i]*Get(c,i))%Mod;
        ans=1ll*ans*res%Mod; l=r+1;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Phartial (赞：0)

有点厉害的题。

记 $f(a)$ 为序列 $a$ 以题面中的方式生成的序列 $b$。我们称序列 $b$ 合法，当且仅当存在 $a$ 使得 $f(a)=b$。

考虑刻画序列 $b$ 在合法时需要满足的约束，不难发现以下方式：生成序列 $a$，其中 $a_i=\max\limits_{i\in[l_j,r_j]} b_j$（特别的，如果不存在 $i\in[l_j,r_j]$，令 $a_i=1$），不妨将其记作 $g(b)$。

容易发现若 $f(g(b))\ne b$，则必然不存在 $f(a)=b$（即，$b$ 必然不合法），于是我们只需校验 $f(g(b))$ 是否等于 $b$。进一步的，注意到所有合法的 $b$ 与 $g(b)$ 构成了双射关系（如果存在两个合法序列 $b_1,b_2$ 满足 $g(b_1)=g(b_2)$，则必然有 $b_1=f(g(b_1))=f(g(b_2))=b_2$，注意这要求 $b_1,b_2$ 合法），于是我们只需计数所有由合法的 $b$ 生成的 $g(b)$。

考虑 $g(b)$ 的另外一种构造方法：从小到大遍历每个数 $i$，对所有 $b_j>i$ 的 $[l_j,r_j]$ 取并，将不在并中且未被确定的位置填上 $i$，这启示我们使用区间 dp 对其进行计数。

设 $f_{l,r,i}$ 表示区间 $[l,r]$ 里的数都 $\ge i$ 的方案数，枚举其中首个填 $i$ 的位置 $j$，有转移 $f_{l,r,i}\gets f_{l,j-1,i+1}\times f_{j+1,r,i}$（没有 $i$ 的情况可以看作是 $j=r+1$），但你显然不能瞎选 $j$，考虑何时可以进行这样的转移：其相当于所有 $b_j>i$ 的 $[l_j,r_j]$ 的并包含 $[l,j-1]$ 但不包含 $l-1$ 和 $j$，贪心的选出所有不包含 $l-1,j$ 的区间并校验其并是否包含 $[l,j-1]$ 即可，可以简单预处理。

于是我们就做到了 $\mathcal{O}(n^3c)$，由于 $c\le 10^9$，显然过不去，考虑优化。

注意到 $f_{l,r,i}$ 可以看成是关于 $i$ 的 $\mathcal{O}(r-l)$ 次多项式，于是只需要计算出 $f_{1,n,c+1},f_{1,n,c},\cdots,f_{1,n,c-n}$ 即可通过拉格朗日插值得到 $f_{1,n,1}$，时间复杂度 $\mathcal{O}(n^4)$。

```cpp
#include <iostream>

using namespace std;

const int kN = 102, kM = 998244353;

struct I {
  int l, r;
} a[kN * kN];
int n, m, v, f[kN][kN][kN], c[kN], iv[kN];
bool p[kN][kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> v;
  for (int i = 1; i <= m; ++i) {
    cin >> a[i].l >> a[i].r;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      fill_n(c + 1, n, 0);
      for (int k = 1; k <= m; ++k) {
        if (i <= a[k].l && a[k].r <= j) {
          ++c[a[k].l], --c[a[k].r + 1];
        }
      }
      for (int k = i; k < j; ++k) {
        c[k + 1] += c[k];
      }
      p[i][j] = 1;
      for (int k = i; k <= j; ++k) {
        p[i][j] &= !!c[k];
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      f[n + 1][i][j] = 1;
    }
  }
  for (int v = n; v >= 1; --v) {
    for (int i = 0; i <= n; ++i) {
      f[v][i + 1][i] = f[v][i + 2][i] = 1;
    }
    for (int l = 1; l <= n; ++l) {
      for (int i = 1, j = l; j <= n; ++i, ++j) {
        for (int k = i; k <= j + 1; ++k) {
          f[v][i][j] = (f[v][i][j] + 1LL * p[i][k - 1] * f[v + 1][i][k - 1] * f[v][k + 1][j] % kM) % kM;
        }
      }
    }
  }
  iv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    iv[i] = 1LL * iv[kM % i] * (kM - kM / i) % kM;
  }
  int ans = 0;
  for (int i = 1; i <= n + 1; ++i) {
    int s = f[n - i + 2][1][n];
    for (int j = 1; j <= n + 1; ++j) {
      if (j != i) {
        s = 1LL * s * (kM + v - j) % kM * (j < i ? iv[i - j] : kM - iv[j - i]) % kM;
      }
    }
    ans = (ans + s) % kM;
  }
  cout << ans;
  return 0;
}
```


---

