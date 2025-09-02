# [ARC170C] Prefix Mex Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc170/tasks/arc170_c

有限個の非負整数からなる数列 $ X $ に対して，$ \mathrm{mex}(X) $ を $ X $ に含まれない最小の非負整数と定義します．例えば，$ \mathrm{mex}((0,0,\ 1,3))\ =\ 2,\ \mathrm{mex}((\ 1)\ )\ =\ 0,\ \mathrm{mex}(()\ )\ =\ 0 $ です．

各要素が $ 0 $ または $ 1 $ である長さ $ N $ の数列 $ S=(S_1,\ldots,S_N) $ が与えられます．

$ 0 $ 以上 $ M $ 以下の整数からなる長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ であって，以下の条件を満たすものの個数を $ 998244353 $ で割ったあまりを求めてください．

- 各 $ i(1\leq\ i\leq\ N) $ について，$ S_i=1 $ ならば $ A_i\ =\ \mathrm{mex}((A_1,A_2,\ldots,A_{i-1})) $，$ S_i=0 $ ならば $ A_i\ \neq\ \mathrm{mex}((A_1,A_2,\ldots,A_{i-1})) $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5000 $
- $ 0\leq\ M\leq\ 10^9 $
- $ S_i $ は $ 0 $ または $ 1 $
- 入力される数値は全て整数
 
### Sample Explanation 1

条件を満たす数列は以下の $ 4 $ 個です． - $ (0,0,0,1) $ - $ (0,0,2,1) $ - $ (0,2,0,1) $ - $ (0,2,2,1) $

### Sample Explanation 2

個数を $ 998244353 $ で割ったあまりを求めることに注意してください．

## 样例 #1

### 输入

```
4 2
1 0 0 1```

### 输出

```
4```

## 样例 #2

### 输入

```
10 1000000000
0 0 1 0 0 0 1 0 1 0```

### 输出

```
587954969```

# 题解

## 作者：Register_int (赞：9)

$\text{mex}$ 的定义比较烦人，我们尝试重新刻画一下。

首先当 $m\ge n$ 时，无论如何 $\text{mex}$ 都不会超过 $m$。所以当 $a_i=1$ 时只有一种方案，$a_i=0$ 时可以选 $m$ 种填法，直接计算即可。

对于 $m<n$，我们转化为在 $0,1,\cdots,m$ 这 $m+1$ 个格子中填数。于是有：

- $a_i=1$ 时相当于强制填掉最靠左的一个格子。
- $a_i=0$ 时相当于随便填除了 $\text{mex}$ 以外一个格子（不要求之前填没填过）。

于是设 $dp_{i,j}$ 表示前 $i$ 个填掉了 $j$ 个格子的方案数，有转移：

$$
dp_{i,j}=
\begin{cases}
dp_{i-1,j-1}&a_i=1\\
j\times dp_{i-1,j}+(m-j+1)\times dp_{i-1,j-1}&a_i=0
\end{cases}
$$

朴素转移，时间复杂度 $O(n^2)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e3 + 10;
const int mod = 998244353;

int n, m, a[MAXN]; ll ans, dp[MAXN][MAXN];

int main() {
	scanf("%d%d", &n, &m), **dp = 1;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	if (m >= n) {
		ans = 1;
		for (int i = 1; i <= n; i++) if (!a[i]) ans = ans * m % mod;
		return printf("%lld", ans), 0;
	}
	m++;
	for (int i = 1; i <= n; i++) {
		if (a[i]) for (int j = 1; j <= m; j++) dp[i][j] = dp[i - 1][j - 1];
		else for (int j = 1; j <= m; j++) dp[i][j] = (dp[i][j] + dp[i - 1][j] * j % mod + dp[i - 1][j - 1] * (m - j) % mod) % mod;
	}
	for (int i = 1; i <= m; i++) ans = (ans + dp[n][i]) % mod;
	printf("%lld", ans);
}
```

---

## 作者：EuphoricStar (赞：3)

我们实际上并不关心 $\text{mex}$ 的具体值，只关心它有没有成为 $\text{mex}$。

考虑有一个 $k = \min(m + 1, n)$ 个空位的长条。我们每次可以往长条最左边的空位放一个球（对应 $a_i$ 成为 $\text{mex}$），或者往长条不是最左边的空位或者非空位放一个球（对应 $a_i < k$ 且 $a_i$ 不是 $\text{mex}$），或者直接把这个球扔掉（对应 $a_i \ge k$）。

那么直接设 $f_{i, j}$ 表示考虑了前 $i$ 个数，长条占了的空位数为 $j$ 的方案数。转移考虑 $a_i$ 的取值个数即可。也就是：

- $s_i = 1$：往长条最左边的空位放一个球，有 $f_{i, j + 1} \gets f_{i - 1, j}$；
- $s_i = 0$：考虑放的球是否占用了空位，有 $f_{i, j} \gets (j + m - k + 1) f_{i - 1, j}, f_{i, j + 1} \gets (k - j - 1) f_{i - 1, j}$。

时间复杂度 $O(n \min(n, m))$。

[code](https://atcoder.jp/contests/arc170/submissions/49546324)

---

## 作者：Mikran (赞：2)

我们一个数有 $m+1$ 种选择嘛，因为可以等于 $0$，为了不混淆，设 $p=m+1$。

首先如果 $m\ge n$，那么无论如何去 mex 也不会超过 $m$。

所以 $s_i=1$ 时只能填当前的 mex 值，$s_i=0$ 时有 $p-1$ 种选法，只要不等于 mex 即可。

对于 $m<n$，题目变成在 $[0,m]$ $p$ 个数中选数字填。

- $s_i=1$，相当于把第一个没选过的数的填进 $A_i$。
- $s_i=0$，相当于随便选一个不是 mex 的数填进 $A_i$。

设 $dp[i][j]$ 为前 $i$ 个**选完**了前了 $j$ 个数填的方案数。注意：第 $j$ 个数**的值** $j-1$。

- $s_i=1$，$dp[i][j]=dp[i-1][j-1]$，只能填第 $j$ 个数，第 $j$ 个数就是 mex。
- $s_i=0$，$dp[i][j]+=j\times dp[i- 1][j]+ (p- j)\times dp[i- 1][j- 1]$，如果已经把前 $j$ 个数选完了，那么 mex 肯定不是 $j-1$ 和 $j-1$ 以前的（这里 $j-1$ 是值），所以你从 $0$ 选到 $j-1$ 都可以，一共 $j$ 个数，那么就是 $j\times dp[i- 1][j]$；如果把前 $j-1$ 个数选完，那么 mex 就是 $j-1$，所以只能从 $[j,m]$ 中选，就是 $(p-j)\times dp[i-1][j-1]$。

```cpp
#include <bits/stdc++.h>
#define int long long
const int N= 2e5+ 10, M= 2e5+ 10, inf= 1e9+ 10, mod= 998244353;
inline int read() {
    int x= 0, f= 1;
    char ch= getchar();
    for (; ! isdigit(ch); ch= getchar()) if (ch== '-') f= -1;
    for (; isdigit(ch); ch= getchar()) x= (x<< 3)+ (x<< 1)+ (ch^ 48);
    return x*= f;
}
using namespace std;
int n, m, a[N], dp[5010][5010], p;
signed main() {
	n= read(), m= read(), p= m+ 1; 
	for ( int i= 1; i<= n; i++) a[i]= read();
	if (m>= n) {
		int ans= 1;
		for ( int i= 1; i<= n; i++) if (! a[i]) ans= ans* (p- 1)% mod;
		cout<<ans;
		return 0;
	}
	dp[0][0]= 1;
	for ( int i= 1; i<= n; i++) {
		if (a[i]) for ( int j= 1; j<= p; j++) dp[i][j]= dp[i- 1][j- 1];
		else for ( int j= 1; j<= p; j++) dp[i][j]= (dp[i][j]+ j* dp[i- 1][j]% mod+ (p- j)* dp[i- 1][j- 1])% mod;
	}
	int ans= 0;
	for ( int i= 1; i<= p; i++) ans= (ans+ dp[n][i])% mod;
	cout<<ans;
}
```

---

## 作者：AC_love (赞：1)

显然，$N \le M + 1$ 时，可以随便填，不会对之后产生影响。

如果 $S_i = 1$，第 $i$ 位只有一种填法，如果 $S_i = 0$，第 $i$ 位能填所有 $M + 1$ 种填法中不构成 $\mathrm{mex}$ 的数，共 $M$ 种填法。

最后的答案就是 $M^k$，其中 $k$ 是满足 $S_i = 0$ 的 $i$ 的个数。

考虑 $N > M + 1$ 怎么处理。

$S_i = 0$ 时不能像刚才一样随便填了，因为当 $S_i = 1$ 时，必须保证有能填的数。

设 $f(i, j)$ 表示填了前 $i$ 个格子用了 $j$ 个数的方案数。

若 $S_i = 1$，则我们必须填一个新的数进来，$f(i, j) = f(i - 1, j - 1)$。

若 $S_i = 0$，我们可以填一个之前填过的数，也可以填一个新的数，但这个新的数不能是 $\mathrm{mex}$，那么转移为 $f(i, j) = f(i - 1, j) \times j + f(i - 1, j - 1) \times (M + 1 - j)$。

直接转移即可，复杂度 $O(NM)$，由于此时 $N > M$，所以复杂度最高为 $O(N^2)$，可以接受。

[code](https://atcoder.jp/contests/arc170/submissions/59505731)

---

## 作者：huangrenheluogu (赞：1)

因为从 $0$ 开始比较烦，不妨修改 $\operatorname{mex}$ 的定义为最小的没有出现的**正**整数。别忘记 $m\leftarrow m+1$。

一个比较有用个性质就是 $\operatorname{mex}$ 不会超过 $n$，说明记录在 $1\sim n$ 中不同的数字有多少个就好了。

想到这一个点，主要思路就是把 $n+1\sim m$ 压缩到 $n+1$ 这一个点。

记 $f_{i,j}$ 表示前 $i$ 个，在 $1\sim n$ 之间的有多少个数字。

转移显然的。

简单地说，如果 $s_i=1$，那么就必然在 $1\sim n$ 之间且不一样。

否则，分类讨论一下需不需要增加个数即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5005, mod = 998244353;
int f[N][N], n, sum, ans, m, up, a[N];
signed main(){
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	m++;
	up = min(n, m);
	f[0][0] = 1;
	for(int i = 1; i <= n; i++){
		if(a[i] == 1){
			for(int j = 1; j <= up; j++) f[i][j] = f[i - 1][j - 1];
			continue ;
		}
		for(int j = 0; j <= up; j++){
			if(j) f[i][j] += f[i - 1][j - 1] * (up - j) % mod;
			(f[i][j] += f[i - 1][j] * (m - up + j) % mod) %= mod;
		}
	}
	for(int j = 0; j <= up; j++) (ans += f[n][j]) %= mod;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Xiphi (赞：1)

有点东西。

首先观察样例，发现答案是 $m^k$，其中 $k$ 表示 $s$ 中 $0$ 的个数。但手玩之后发现这只在 $n-2\le m$ 且 $2 \le n$ 时满足。

那么就考虑 $dp$。发现过程中如果记录 $\rm mex$ 的话枚举复杂度就是 $O(m)$ 的，无法承受，但事实上有用的东西是“序列中不同的数的个数”而非 $\rm mex$。

设状态 $dp_{i,j}$ 表示填了前 $i$ 个数且不同个数为 $j$ 的方案数。

考虑以下两种情况：

- $s_i=1$，则 $dp_{i,j}=dp_{i-1,j-1}$。

- $s_i=0$，这样又要分两种情况：

 1. 不同值个数增加，且 $j\neq \min(m+1,n)$ 时（因为这样的话 $j$ 就不可能增加），$dp_{i,j}=dp_{i-1,j-1}\times(m-j+1)$。
 2. 不同值个数不增加，$dp_{i,j}=dp_{i-1,j}\times j$。
 
 然后最终答案就是 $\sum_{i=0}^{\min(n,m+1)} dp_{n,i} $。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5005,p=998244353;
int n,m,a[N],f[N][N];
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>m;
	f[0][0]=1;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i){
		for(int j=0;j<=min(m+1,n);++j){
			if(a[i]&&j)
				f[i][j]=f[i-1][j-1];
			else{
				if(1<=j&&j<=m)
					f[i][j]=(f[i][j]+f[i-1][j-1]*1ll*(m-j+1)%p)%p;
				f[i][j]=(f[i][j]+f[i-1][j]*1ll*j%p)%p;
			}
		}
	}
	int ans=0;
	for(int i=0;i<=min(m+1,n);++i)
		ans=(ans+f[n][i])%p;
	cout<<ans;
	return 0;
}
```

---

## 作者：DengDuck (赞：1)

明天是 THUWC，写个题解涨涨 RP。

显然我们只关心选中的是不是 $\operatorname{mex}$，所以我们考虑有哪些有关的内容。

首先，如果一个数字 $a_i\geq n$，那么这个数字就浪费了，因为这绝对不会影响到 $\operatorname{mex}$，你就算放 $[0,n-1]$ 这个区间 $\operatorname{mex}$ 也才是 $n$ 啊！

如果我们知道了 $[0,n-1]$ 有几个数字，我们发现就可以转移了。

所以我们状态只需要记录两个，一个是当前处理到第几个数字，一个是 $[0,n-1]$ 里选中的数量。

什么情况会增加选种的数量？

- 当强制选 $\operatorname{mex}$ 的时候。
- 随便选的时候没有选选过的位置。

然后直接转移就行，记得统计答案的时候变量 $i\leq m+1$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pb push_back
#define pLL pair<LL,LL>
#define fir first
#define sec second
using namespace std;
const LL N=5e3+5;
// const LL K;
// const LL M;
const LL mod=998244353;
LL n,m,s[N],f[N][N],ans;
void Add(LL &x,LL y)
{
    x=(x+y+mod)%mod;
}
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&s[i]);
    }
    m=m%mod;
    f[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(s[i]==1)
            {
                if(j)Add(f[i][j],f[i-1][j-1]);
            }
            else
            {
                Add(f[i][j],f[i-1][j]*j%mod);
                if(j)Add(f[i][j],(m-j+1+mod)%mod*f[i-1][j-1]);
            }
        }
    }
    for(int i=0;i<=n&&i<=m+1;i++)
    {
        Add(ans,f[n][i]);
    }
    printf("%lld",ans);
}
//RP++
```

---

## 作者：lfxxx (赞：0)

定睛一看，这个限制很松啊，是不是 $S_i = 1$ 只有一种填法，$S_i = 0$ 有 $m$ 种填法就做完了啊？

怎么可能，注意到你前面乱填的话后面填 $S_i = 1$ 就没法填了。

但是注意到 $m+1 \geq n$ 时，不会出现上面的情况，可以简单算，下面考虑 $m+1 < n$ 怎么做。

由于限制合法的是还有没有数填，所以不放 $dp_{i,j}$ 表示考虑前 $i$ 个限制，已经填了 $j$ 种数的方案，假若 $S_i = 0$ 时有 $dp_{i,j} = dp_{i-1,j-1} \times (m+1-(j-1)-1) + dp_{i-1,j} \times j$，当 $S_i = 1$ 时 $dp_{i,j} = dp_{i-1,j-1}$，直接转移的时间复杂度是 $O(n^2)$，可以通过。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 5e3+114;
int n,m;
int S[maxn];
int dp[maxn][maxn];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>S[i];
	if(m+1>=n){
		int res=1;
		for(int i=1;i<=n;i++){
			if(S[i]==0) res=res*m%mod;
		}
		cout<<res<<'\n';
	}else{
		dp[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m+1;j++){
				if(S[i]==0){
					dp[i][j]=(dp[i-1][j-1]*(m+1-(j-1)-1)%mod+dp[i-1][j]*j%mod)%mod;//前面填过 前面没填过 
				}else{
					dp[i][j]=dp[i-1][j-1];
				}
			}
		}
		int res=0;
		for(int j=1;j<=m+1;j++) res=(res+dp[n][j])%mod;
		cout<<res<<"\n";
	}
	return 0;
}
```

---

## 作者：std_qwq (赞：0)

### 思路

题目询问方案数。事实上，**我们并不在乎具体填了什么数字**，我们只需在乎我们在填入第 $i$ 个数字的时候**有多少个选项可选**。

$\operatorname{mex}$ 操作的特点在于**选择当前选择的集合的补集中的最小值**（有点绕口，请读者自行断句理解）。对 $a_{i}=1$，如果补集不为空，则只有一种选择。反之，假设补集中有 $s$ 个元素，当前选择的集合有 $c$ 个元素，就有 $s-1+c$ 种选择。 这启发我们按照**目前选择了多少个元素**进行状态设计进行 dp。值得注意的是，因为数据范围是  $1 \le N \le 5000,0 \le M \le 10^{9}$，我们不考虑“还剩多少元素”这种状态设计。

### 状态设计
设 $f_{i,j}$ 为：考虑前 $i$ 个数字，占用 $[0,m]$ 中 $j$ 个整数的方案数（$j\le i$ 且 $j\le m+1$）。则答案是：
$${\textstyle \sum_{i=1}^{\min(m+1,n)}f_{n,i}} $$ 

### 初始化与状态转移
$$ f_{0,0}=1 $$

$$f_{i,j}=\left\{\begin{matrix}f_{i-1,j-1},\space a_{i}=1, \\j\times f_{i-1,j}+(m+1-j)\times f_{i-1,j-1},\space a_{i}=0.\end{matrix}\right.$$

### 参考代码
事实上可以压缩掉 $i$ 这一维，但是以下代码并没有这样做。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5010,M=998244353;
//突发奇想：实际上不在乎具体方案，在于可选选项的个数
//f[i][j]:1~i中[0,m]的占用个数j>0
//a[i]=1 -> f[i][j]=f[i-1][j-1]
//a[i]=0 -> f[i][j]= j*f[i-1][j]+(m+1-j)f[i-1][j-1]*[j>0] if j<m+1
//                   (m+1)*f[i-1][m+1] if j=m+1
typedef long long ll;
ll f[N][N];
int a[N],n,m;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    f[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=min(m+1,i);j>0;j--)
            if(a[i])f[i][j]=f[i-1][j-1];
            else f[i][j]=(j*f[i-1][j]%M+(m+1-j)*f[i-1][j-1]%M)%M;
    ll ans=0;
    for(int i=1;i<=min(m+1,n);i++)(ans+=f[n][i])%=M;
    cout<<ans;
}
```
若能帮到各位，在下荣幸之至qwq。

---

## 作者：int_R (赞：0)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/17980822/AT_arc170_c)

[原题链接](https://www.luogu.com.cn/problem/AT_arc170_c)

发现所有的限制都只跟已经使用的数字个数有关，故记 $f_{i,j}$ 为前 $i$ 个数，使用了 $j$ 个数的方案数。

当 $s_i=0$，可以填已经出现过的数，也可以填没有出现过但并非当前 $\operatorname{mex}$ 的数，即 $f_{i,j}=f_{i-1,j}\times j +f_{i-1,j-1}\times (m-(j-1))$。

当 $s_i=1$，只能填 $\operatorname{mex}$ 所以 $f_{i,j}=f_{i-1,j-1}$。

最后答案是 $\sum\limits_{i=0}^{\min(n,m+1)} f_{n,i}$

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int MAXN=5e3+10,MOD=998244353;
int n,m,s[MAXN],f[MAXN][MAXN],now,ans;
signed main()
{
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n>>m;f[0][0]=1;
    for(int i=1;i<=n;++i)
    {
        cin>>s[i];
        if(!s[i])
        {
            for(int j=0;j<=n;++j)
            {
                f[i][j]=(f[i][j]+f[i-1][j]*j%MOD)%MOD;
                if(m-j>=0)
                    f[i][j+1]=f[i-1][j]*(m-j)%MOD;
            }
        }
        if(s[i])
        {
            for(int j=0;j<=n;++j)
                f[i][j+1]=f[i-1][j];
            ++now;
        }
    }
    for(int j=0;j<=min(n,m+1);++j)
        ans=(ans+f[n][j])%MOD;
    cout<<ans<<'\n';return 0;
}
```

---

## 作者：快乐的大童 (赞：0)

### 题意简述
有长度为 $n$ 的 $s_i=0/1$，求满足下列条件的长度为 $n$ 的序列 $a$ 的个数，对 $998244353$ 取模：

- $\forall i,0\le a_i\le m$
- 当 $s_i=0$ 时，$a_i\not=\operatorname{mex}(a_1,a_2,\cdots,a_{i-1})$
- 当 $s_i=1$ 时，$a_i=\operatorname{mex}(a_1,a_2,\cdots,a_{i-1})$


数据范围：$n\le 5000,m\le 10^9$。




### 分析

首先简单分析下发现 $ans=m^k$，$k$ 为 $s_i=0$ 的 $i$ 的个数（当 $s_i=1$ 时只有一种填法，当 $s_i=0$ 时只有一种填法不能选）。

然后我们发现在 $m$ 较大时该结论正确（实际上是 $m\ge n-1,n\ge 2$ 时正确，代码中为 $m\ge n$，实际上去掉这个特判也不影响正确性）。

~~以上跟正题没有什么关系，下面进入正题。~~

当 $s_i=1$ 时，能填进去的数唯一。问题主要在于如何合理的设计 dp 状态处理掉 $s_i=0$ 的情况。

发现一个 $s_i=0$ 的连续段中不能填的数一定。因为在填前面的数时，由于不能填 mex，故 mex 一直没有发生改变。

而且我们发现值和值之间没有太大的本质区别，我们也不需要知道 mex 具体是几，仅仅知道那个数不能填。由此设 $f_{i,j}$ 表示前 $i$ 个数中出现了 $j$ 种不同的数字的方案数。

转移：

- $s_i=0:f_{i,j}\leftarrow f_{i-1,j-1}$，因为此时只能强制填 mex，而 mex 在之前必定没出现过。
- $s_i=1:f_{i,j}\leftarrow f_{i-1,j}\times j+f_{i-1,j-1}\times(m-j)$，因为此时可以填 $j$ 种出现过的数字，也可以填 $m-j+1$ 种没有出现过的数字，但不能填 mex，而 mex 在之前必定没出现过，所以可以填 $m-j$ 种数字。

由于 $n$ 个值里面至多有 $n$ 个不同值，故时间复杂度 $O(n^2)$。

[code](https://atcoder.jp/contests/arc170/submissions/49554905)

---

