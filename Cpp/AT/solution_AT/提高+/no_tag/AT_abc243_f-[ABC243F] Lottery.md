# [ABC243F] Lottery

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc243/tasks/abc243_f

高橋君はくじを引こうとしています。

くじを $ 1 $ 回引くごとに、$ N $ 種類の賞品のいずれかが手に入ります。賞品 $ i $ が手に入る確率は $ \frac{W_i}{\sum_{j=1}^{N}W_j} $ であり、各くじの結果は独立です。

くじを $ K $ 回引いたとき、ちょうど $ M $ 種類の賞品が手に入る確率はいくらでしょうか？ $ \bmod\ 998244353 $ で求めてください。

## 说明/提示

### 注記

有理数を出力する際は、まずその有理数を分数 $ \frac{y}{x} $ として表してください。 ここで、$ x,y $ は整数であり、$ x $ は $ 998244353 $ で割り切れてはなりません（この問題の制約下で、そのような表現は必ず可能です）。 そして、$ xz\equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の唯一の整数 $ z $ を出力してください。

### 制約

- $ 1\ \leq\ K\ \leq\ 50 $
- $ 1\ \leq\ M\ \leq\ N\ \leq\ 50 $
- $ 0\ <\ W_i $
- $ 0\ <\ W_1\ +\ \ldots\ +\ W_N\ <\ 998244353 $
- 入力は全て整数である

### Sample Explanation 1

各くじの結果として、賞品 $ 1 $ が手に入る確率が $ \frac{2}{3} $、賞品 $ 2 $ が手に入る確率が $ \frac{1}{3} $ です。 $ 2 $ 回のくじの結果として、ともに賞品 $ 1 $ を手に入れる確率が $ \frac{4}{9} $、ともに賞品 $ 2 $ を手に入れる確率が $ \frac{1}{9} $ であるため、求める答えは $ \frac{5}{9} $ です。 これを注記にしたがって $ \bmod\ 998244353 $ で出力すると $ 221832079 $ になります。

### Sample Explanation 2

くじを $ 2 $ 回引いて $ 3 $ 種類の賞品を手に入れることはできません。したがって求める確率は $ 0 $ です。

## 样例 #1

### 输入

```
2 1 2
2
1```

### 输出

```
221832079```

## 样例 #2

### 输入

```
3 3 2
1
1
1```

### 输出

```
0```

## 样例 #3

### 输入

```
3 3 10
499122176
499122175
1```

### 输出

```
335346748```

## 样例 #4

### 输入

```
10 8 15
1
1
1
1
1
1
1
1
1
1```

### 输出

```
755239064```

# 题解

## 作者：mojoege (赞：3)

## 题意

~~原神~~的抽卡池里有 $n$ 种角色，每种角色的数量无限多，第 $i$ 个角色被抽出的概率是 $\frac{W_i}{\sum W}$，你的钱包只够你氪金抽 $k$ 次，问你最后恰好抽到 $m$ 种不同的角色的概率是多少，答案对 $998244353$ 取模。

## 分析

前置知识《伯努利试验》：设一个事件 $A$ 发生的概率 $P(A)$，则取 $p$ 次这个事件，恰好有 $k$ 次发生的概率是 $C_{p}^{k} \times {P(A)}^k \times {(1-P(A))}^{p-k}$。

依旧是 dp，设置状态 $dp_{i,j,k}$ 表示前 $i$ 种角色，抽了 $j$ 次，有 $k$ 种不同角色的概率。

而根据《伯努利试验》，设在前 $j$ 次抽卡中抽到了 $p$ 个角色 $i$，所以它的贡献就是 $C_{j}^{p} \times {(\frac{w_i}{\sum w})}^p \times dp_{i-1,j-p,k-1}$，这里乘上的 $dp_{i-1,j-p,k-1}$ 已经代表剩下的数全抽 $i$ 以前的角色的概率，不用再乘上 ${(1-P(A))}^{p-k}$。$dp_{i,j,k}$ 的答案就是这些贡献求和。这里转移前记得先将 $dp_{i,j,k}$ 赋值成 $dp_{i-1,j,k}$。	

basecase 就是 $dp_{0,0,0}=1$，ans 就是 $dp_{n,k,m}$。

这里需要模，肯定是要使用逆元的，在此不多赘述。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 998244353;
int n, m, t, sum;
int w[55], fac[55], dp[55][55][55];

int ksm(int a, int b){//快速幂求逆元
    int res = 1;
    while (b){
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int C(int a, int b){//组合数
    return fac[a] * ksm(fac[b] * fac[a - b] % mod, mod - 2) % mod;
}

signed main(){
    cin >> n >> m >> t;
    fac[0] = 1;
    for (int i = 1; i <= t; i++) fac[i] = fac[i - 1] * i % mod;
    for (int i = 1; i <= n; i++) cin >> w[i], sum += w[i];
    dp[0][0][0] = 1;//basecase
    for (int i = 1; i <= n; i++){
        dp[i][0][0] = dp[i - 1][0][0];
        for (int j = 1; j <= t; j++){
            for (int k = 1; k <= i; k++){
                dp[i][j][k] = dp[i - 1][j][k];//初始化
                for (int p = 1; p <= j; p++) dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j - p][k - 1] * C(j, p) % mod * ksm(w[i], p) % mod * ksm(ksm(sum, p), mod - 2) % mod) % mod;//公式，记得用逆元
            }
        }
    }
    cout << dp[n][t][m];//ans
    return 0;
}
```

---

## 作者：cwxcplh (赞：2)

[洛谷题面。](https://www.luogu.com.cn/problem/AT_abc243_f)

[Atcoder 题面。](https://atcoder.jp/contests/abc243/tasks/abc243_f)

**题目大意：** 给定 $n$ 个物品，每一种物品被抽到的概率为 $\frac{W_i}{\sum_{j=1}^nW_j}$，一共可以抽 $k$ 次，求抽到 $m$ 种不同的物品的概率。

首先一看就知道这题肯定跟概率与数论会扯上关系，我们先考虑这样一种情况：假设抽到的 $k$ 个物品按照某种方式排列后的概率分别为 $a_1,a_2,a_3\dots,a_k$，那么我们肯定能很轻松的算出这种情况的概率就是 $\prod_{i=1}^ka_i$，问题就在于这个 $a_i$ 该怎么算。

我们再假设我们抽到的 $m$ 个不同的物品的概率分别是 $b_1,b_2,\dots,b_m$，每个物品的数量为 $c_1,c_2,\dots,c_m$，那么每个物品满足上述条件的概率 $a_i={b_i}^{c_i}$，总的合起来就是 $\prod_{i=1}^k{b_i}^{c_i}$，但又因为排列问题，我们还要再前面乘上一个数。

这个数的计算方法也很好算：因为一共有 $k$ 个物品，所以总的排列就是 $k!$，这一点可以很容易算出来，然而两个相同的物品互换了位置其实是不会变的，而每一个物品的排列方案数又是 $c_i!$，因为有 $m$ 个物品，所以总的方案数就是 $\prod_{i=1}^mc_i!$，那么我们用总的方案数去除以重复的方案数就是正确答案，即 $\cfrac{k!}{\prod_{i=1}^mc_i!}$，再乘以每一种方案下的概率就是答案，即 $\cfrac{k!}{\prod_{i=1}^mc_i!}\prod_{i=1}^m{b_i}^{c_i}$，把分母放进去，就成了 $k!\prod_{i=1}^m\cfrac{{b_i}^{c_i}}{c_i!}$。

其中 $k!$ 很好求，重点就在于后面的部分。

由于后半部分有很多种情况，所以我们考虑使用 DP。

定义 `dp[i][j][k]` 表示前 $i$ 种物品在抽了 $k$ 次抽出了 $j$ 个不同物品的概率，那么我们就可以得到如下状态转移方程：

1. **当抽了 $0$ 次第 $i$ 种时：** $dp_{i,j,k}=dp_{i,j,k}+dp_{i-1,j,k-l}$。（啥新的都没抽出来，就直接加上原本的概率就行了。）
2. **当抽了大于 $0$ 次第 $i$ 种时：** $dp_{i,j,k}=dp_{i,j,k}+dp_{i-1,j-1,k-l}\times\cfrac{{b_i}^l}{l!}$。（有新的，应该在原本概率的基础上乘上当前概率才是现在的总概率。）

其中，$l$ 表示抽第 $i$ 种物品抽的次数。（关于抽第 $i$ 种物品抽了 $l$ 次还没抽出来这件事……）

最后直接输出 `dp[n][m][k]` 就行了。

最后，我们来解决一个“小”问题：除法不支持取模运算，那应该怎么办呢？其实我们只需要把它转化成逆元就行了。

逆元，说白了就是把型如 $\cfrac{1}{b}$ 转化成 $b^{-1}$，然后我们就可以运用费马小定理。在这里因为 $998244353$ 是一个质数，所以由费马小定理：

$$a^{-1}\equiv a^{n-2}\ (\bmod\ n)$$

（当且仅当 $n$ 是一个质数且 $a$ 不是 $n$ 的倍数时使用。）

可知：

$$a^{-1}\equiv a^{998244351}\ (\bmod\ 998244353)$$

这个可以解决计算每种物品抽出的概率的计算。

对于 $\cfrac{1}{l!}$ 这里，我们可以使用阶乘逆元。我们说过，逆元就是把型如 $\cfrac{1}{b}$ 的类型变成 $b^{-1}$，那么阶乘的逆元就可以表示为 $(l!)^{-1}=\prod_{i=0}^li^{-1}$，我们设一个数组 `bfac[i]` 表示 $i$ 的阶乘逆元，那么 $bfac_i=0^{-1}\times1^{-1}\dots\times i^{-1}=0^{-1}\times1^{-1}\dots\times i^{-1}\times(i+1)^{-1}\times (i+1)=bfac_{i+1}\times(i+1)$，总结下来就是 $bfac_i=bfac_{i+1}\times(i+1)$，然后算一下 $bfac_n$ 再套用公式就行了。

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
#define code using
#define by namespace
#define plh std
code by plh;
const int mod=998244353;
const int N=56;
int n,m,k,fac[N],bfac[N],a[N],dp[N][N][N];
int qpow(int x,int y)//快速幂
{
    if(y==0)
    {
        return 1;
    }
    int t=qpow(x,y>>1)%mod;
    if(y&1)
    {
        return t*t%mod*x%mod;
    }
    else
    {
        return t*t%mod;
    }
}
signed main()
{
    fac[0]=bfac[0]=1;
    for(int i=1;i<N;i++)
    {
        fac[i]=fac[i-1]*i%mod;//阶乘
    }
    bfac[N-1]=qpow(fac[N-1],mod-2);//阶乘逆元
    for(int i=N-2;i>=0;i--)
    {
        bfac[i]=bfac[i+1]*(i+1)%mod;
    }
    int sum=0;
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];
    }
    sum=qpow(sum,mod-2);
    for(int i=1;i<=n;i++)
    {
        a[i]=a[i]*sum%mod;//题目中的公式
    }
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++)//跑 DP 啦
    {
        for(int j=0;j<=m;j++)
        {
            for(int l=0;l<=k;l++) 
            {
                for(int r=0;r<=l;r++)
                {
                    if(j==0&&r>0)
                    {
                        continue;
                    }
                    if(r>=1)
                    {
                        dp[i][j][l]+=dp[i-1][j-1][l-r]*qpow(a[i],r)%mod*bfac[r]%mod;
                    }
                    else
                    {
                        dp[i][j][l]+=dp[i-1][j][l]%mod;
                    }
                    dp[i][j][l]=(dp[i][j][l]%mod+mod)%mod;
                }
            }
        }
    }
    cout<<dp[n][m][k]*fac[k]%mod;//记住不要忘了乘 k 的阶乘
    return 0;
}
```

---

## 作者：I_LOVE_MATH (赞：2)

### 题目大意

有 $n$ 个元素，给出每个元素被抽到的概率 $w$，抽 $k$ 次，求恰好抽到 $m$ 种元素的概率。

### 解题思路

观察数据范围，暴力判断抽到哪些元素会超时，考虑**概率 dp**。

- 状态表示：$dp[i][j][k]$ 表示考虑到第 $i$ 个元素，抽了 $k$ 次，有 $j$ 种不同元素的概率。
- 初始化：显然不抽一定会有 $0$ 种不同，所以 $dp[i][0][0]=1$。
- 状态转移：类似于多重背包，我们分两种情况讨论。
  - **不抽第 $i$ 个元素**：那么就是前 $i-1$ 个元素，抽了 $k$ 次，有 $j$ 种不同元素的概率，有转移方程：
    $$dp[i][j][k]=dp[i-1][j][k]$$
  - **抽第 $i$ 个元素**：设抽了 $x$ 个，那么抽中其他元素的概率就是 $dp[i-1][j-1][k-x]$，抽中 $x$ 个 $i$ 元素的概率就是 $(\frac{w_i}{\sum w})^x$，另外我们不考虑抽中元素的顺序，因此需要再乘上 $C_k^x$，于是有转移方程：
    $$dp[i][j][k]=dp[i-1][j-1][k-x]\cdot(\frac{w_i}{\sum w})^x\cdot C_k^x$$
  综上，将以上情况求和可得：
  $$dp[i][j][k]=dp[i-1][j][k]+\sum_{x=1}^{k} dp[i-1][k-x][j-1]\cdot(\frac{w_i}{\sum w})^x\cdot C_k^x$$
- 答案：$dp[n][m][k]$。

代码实现上，可以预处理阶乘来 $O(1)$ 计算组合数，总时间复杂度 $O(n^4\log P)$，$O(\log P)$是逆元的复杂度。

### 代码
```cpp
#include<bits/stdc++.h>
#define endl "\n"
#define ll long long
using namespace std;

const ll N = 60, P = 998244353;

int n, m, t;
ll w[N], jc[N], sum;
ll dp[N][N][N];

inline ll qkpow(ll x, ll y)
{
	ll res = 1;
	while (y)
	{
		if (y & 1)
		{
			(res *= x) %= P;
		}
		(x *= x) %= P;
		y >>= 1;
	}
	return res;
}

inline ll c(ll x, ll y)
{
	return jc[y] * qkpow(jc[x] * jc[y - x] % P, P - 2) % P;
}

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++)
	{
		cin >> w[i];
		sum += w[i];
		dp[i][0][0] = 1;
	}
	jc[0] = 1;
	for (int i = 1; i <= t; i++)
	{
		jc[i] = (jc[i - 1] * i) % P;
	}
	dp[0][0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			for (int k = 1; k <= t; k++)
			{
				dp[i][j][k] = dp[i - 1][j][k];
				for (int x = 1; x <= k; x++)
				{
					(dp[i][j][k] += dp[i - 1][j - 1][k - x] * c(x, k) % P * qkpow(w[i], x) % P * qkpow(qkpow(sum, x), P - 2) % P) %= P;
				}
			}
		}
	}
	cout << dp[n][m][t];
	return 0;
}
```

---

## 作者：shinkuu (赞：1)

发现直接记录有哪些奖品被选是不可能的，所以考虑转换一下思路：设 $dp_{i,j,p}$ 为只考虑前 $i$ 个奖品，抽了 $j$ 次，有 $p$ 种不同奖品的的概率。

这个状态相当于是维护一个操作（抽奖）序列。考虑每次加入 $q$ 个第 $i$ 种奖品，就相当于是将原序列和一个由 $q$ 个 $i$ 组成的序列合并。这是经典问题，方案数即为 $\dbinom{j}{q}$。而该序列出现概率又为 $dp_{i-1,j-q,p-1}\times (\dfrac{w_i}{\sum w})^q$。还需要判断一下一些 $0/1$ 的情况。

code：

```cpp
int n,m,k,e[N],f[N],dp[N][N][N];
inline int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
inline int Cnm(int x,int y){
	if(x<0||y<0||x<y)
		return 0;
	return 1ll*f[x]*qpow(1ll*f[y]*f[x-y]%mod,mod-2)%mod;
}
void solve(){
	scanf("%d%d%d",&n,&m,&k);
	int sm=0;
	f[0]=1;
	for(int i=1;i<=k;i++)
		f[i]=1ll*f[i-1]*i%mod;
	for(int i=1;i<=n;i++){
		scanf("%d",&e[i]);
		sm+=e[i];
	}
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++){
		dp[i][0][0]=dp[i-1][0][0];
		for(int j=1;j<=k;j++){
			for(int p=1;p<=min(i,m);p++){
				dp[i][j][p]=dp[i-1][j][p];
				for(int q=1;q<=j;q++){
					dp[i][j][p]=(dp[i][j][p]+1ll*dp[i-1][j-q][p-1]*Cnm(j,q)%mod*qpow(e[i],q)%mod*qpow(qpow(sm,q),mod-2)%mod)%mod;
				}
			}
		}
	}
	printf("%d\n",dp[n][k][m]);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：daniEl_lElE (赞：1)

不错的容斥+dp+系数计算+概率论经典题。

## 思路

首先看到恰好直接上容斥，换成钦定在 $x$ 个彩票中选。

很容易计算出对于所有大小为 $0\sim m$ 的集合，其概率的 $k$ 次方大小之和。计之为 $f_i$。（#1）

然后进行容斥，容易发现容斥系数为 $(-1)^{m-i}\times \binom{n-i}{n-m}$。复杂度 $O(nmk^2)$。（#2）

~~这能过？这能过？这能过？~~

考虑 $dp_{i,j,k}$，表示看到 $i$ 号彩票，选出 $j$ 张，$k$ 次方和大小。转移的时候可以由 $dp_{i-1,j,k}$ 转移到 $dp_{i,j+1,l}$，其中 $l\geq k$。根据二项式定理，系数应该是 $\binom{l}{k}\times a_i^{l-k}$。（#1 解法及细节）

考虑计 $f_i$ 的系数为 $g_i$。容易发现 $f_i$ 被总计 $\binom{j}{i}$ 个 $f_j$ 各计算了 $g_j$ 次。通过归纳及推式子可以发现容斥系数如上。本人写代码时 $xs$ 数组表示的是这里的 $g$，也用的 $O(m^2)$ 计算系数，可以更优。整道题复杂度瓶颈在于前半段的 dp。（#2 解法及证明）

## 代码

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
using namespace std;
const int mod=998244353;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int dp[55][55][55];
int C[55][55]; 
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	for(int i=0;i<=50;i++) C[i][0]=1;
	for(int i=1;i<=50;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	int n,m,k,sum=0;
	cin>>n>>m>>k;
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++){
		int a; cin>>a;
		int pw[k+1]; pw[0]=1;
		for(int j=1;j<=k;j++) pw[j]=pw[j-1]*a%mod;
//		cout<<"OK";
		for(int j=0;j<=n;j++){
//			cout<<"OK"<<j; 
			for(int k1=0;k1<=k;k1++){
				(dp[i][j][k1]+=dp[i-1][j][k1])%=mod;
				for(int k2=k1;k2<=k;k2++){
					(dp[i][j+1][k2]+=dp[i-1][j][k1]*C[k2][k1]%mod*pw[k2-k1])%=mod;
				}
			}
		}
		sum+=a;
//		for(int j=0;j<=n;j++){
//			for(int k1=0;k1<=k;k1++){
//				cout<<dp[i][j][k1]<<" ";
//			}
//			cout<<endl;
//		}
//		cout<<endl;
	}
	int xs[m+1];
	int ans=dp[n][m][k]; xs[m]=1;
	for(int i=m-1;i>=1;i--){
		xs[i]=0;
		for(int j=i+1;j<=m;j++){
			(xs[i]+=mod-xs[j]*C[n-i][j-i]%mod)%=mod;
		}
//		cout<<xs[i]<<" ";
		(ans+=xs[i]*dp[n][i][k])%=mod;
	}
	cout<<ans*qp(sum,(mod-2)*k)%mod;
	return 0;
}
/*
5 3 5 4 3 4
things to check
1.  int overflow or long long memory need
2.  recursion/array/binary search/dp/loop bounds
3.  precision
4.  special cases(n=,bounds)
5.  delete debug statements
6.  initialize(especially multi-tests)
7.  = or == , n or m ,++ or -- , i or j , > or >= , < or <= , - or =
8.  keep it simple and stupid
9.  do not delete, use // instead
10. operator priority
11. is there anything extra to output?
12. if you don't know where the bug is , try to clear some parts of the code
 and check each part seperately.
*/


```

---

## 作者：zhaoyp (赞：1)

[ABC243F](https://atcoder.jp/contests/abc243/tasks/abc243_f)
$\text{Difficulty : 2125}$ ：每次抽奖有 $p_i$ 的概率获得物品 $i$，求抽 $k$ 次恰好获得 $m$ 个不同的物品的概率。对大质数取模。

首先如果 $k$ 次中每个数抽到 $c_i$ 次的概率为 $\dfrac{k!}{\prod\limits_{i=1}^nc_i!}\prod\limits_{i=1}^np_i^{c_i}$。

考虑这些数组成不同的排列共有 $\dfrac{k!}{\prod\limits_{i=1}^nc_i!}$ 种即可。

记 $f_{i,j,k}$ 表示前 $i$ 个物品，选了 $k$ 次，选出 $j$ 个的概率，也就是上式去掉 $k!$ 的部分。则有：

- 不选 $i$，$f_{i,j,k} = f_{i-1,j,k}$。
- 选 $i$，参见上式可以得到， $f_{i,j,k}=\sum\limits_{x=1}^k \dfrac{p_i^t}{x!} f_{i-1,j-1,k-x}$。

$$ans = f_{n,m,k} \times k!$$

大力 dp 即可，时间复杂度 $O(n^4)$。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 55;
const int mod = 998244353;
long long n,m,K,f[maxn][maxn][maxn],w[maxn],fac[maxn],inv[maxn],b[maxn][maxn],p[maxn];
inline int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while(ch < '0'||ch > '9'){if(ch == '-'){f = -1;}ch = getchar();}
	while(ch <= '9'&&ch >= '0'){x = (x << 1) + (x << 3) + ch - '0',ch = getchar();}
	return f * x;
}
long long qpow(long long a,long long b)
{
	long long res = 1;
	while(b)
	{
		if(b & 1)
			res = res * a % mod;
		a = a * a % mod;
		b >>= 1; 
	}
	return res % mod;
}
void prefix()
{
	long long sum = 0;
	for(int i = 1;i <= n;i++)
		sum += w[i];
	sum = qpow(sum,mod - 2);
	for(int i = 1;i <= n;i++)
		p[i] = w[i] * sum % mod;
	for(int i = 1;i <= n;i++)
		for(int j = 0;j <= K;j++)
			b[i][j] = qpow(p[i],j);
	fac[0] = 1;
	for(int i = 1;i <= K;i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[K] = qpow(fac[K],mod - 2);
	for(int i = K - 1;i >= 0;i--)
		inv[i] = inv[i + 1] * (i + 1) % mod;
}

int main()
{
	n = read(),m = read(),K = read();
	for(int i = 1;i <= n;i++)
		w[i] = read();
	prefix();
	for(int i = 0;i <= n;i++)
		f[i][0][0] = 1;
	for(int i = 1;i <= n;i++)
		for(int k = 1;k <= K;k++)
			for(int j = 1;j <= k;j++)
			{
				f[i][j][k] = f[i - 1][j][k];
				for(int t = 1;k - t >= j - 1;t++)
					f[i][j][k] = (f[i][j][k] + f[i - 1][j - 1][k - t] * b[i][t] % mod * inv[t]) % mod;
			}
	printf("%lld",f[n][m][K] * fac[K] % mod);
	return 0 ;
}
```

---

## 作者：封禁用户 (赞：1)

# 「ABC243F」Lottery 题解

本蒟蒻的第一篇题解！

## 思路

设 $p_i$ 为抽出第 $i$ 个角色的概率，可以直接算出来。

然后直接动态规划，设 $dp_{i,j,k}$ 为**前 $i$ 个角色，抽了 $j$ 次奖，有 $k$ 种不同角色的概率**。

接下来我们考虑对于第 $i$ 个角色，抽了 $t$ 次都抽出来的概率。

发现抽这个角色 $t$ 次的概率就是 $p_i^t$。

这 $t$ 次可以是任意 $t$ 次，所以需要再乘上一个 $C_j^t$。

可以通过 $dp_{i-1,j-t,k-1}$ 转移过来。

然后就很容易得出状态转移式：

$$dp_{i,j,k}= dp_{i-1,j-t,k-1}\times C_j^t\times p_i^t$$

最后答案为 $dp_{n,K,m}$。

注意组合数预处理到**最大值 $50$ 而不是 $n$**。

具体细节看代码注释。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
#include<string>
#include<iostream>
#include<unordered_map>
#define int long long
#define inf 0x3f3f3f3f
#define il inline
#define db double
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define f(i,a,b) for(int i=(a);i>=(b);--i)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
const int N=110;
const int mod=998244353;
int w[N];
int n,m,K,sum;
int dp[N][N][N];
int c[N][N];
void init()
{
	F(i,0,50) F(j,0,i)//处理到50
	{
		if(!j) c[i][j]=1;
		else c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
}
inline int qpow(int a,int b)//快速幂
{
    int res=1;
    while(b)
	{
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
inline int inv(int a){return qpow(a,mod-2)%mod;}//使用费马小定理求出逆元 
signed main()
{
	n=read(),m=read(),K=read();
	F(i,1,n) w[i]=read(),sum+=w[i];
	init();//预处理组合数 
	dp[0][0][0]=1;
	F(i,1,n)
	{
		dp[i][0][0]=1;//初始化
		F(j,1,K)
		{
			F(k,1,m)
			{
				dp[i][j][k]=dp[i-1][j][k];
				F(t,1,j) dp[i][j][k]=(dp[i][j][k]+c[j][t]*dp[i-1][j-t][k-1]%mod*qpow(w[i]*inv(sum)%mod,t)%mod)%mod;
				/*w[i]*inv(sum)即为p[i]*/
			}
		}
	}
	std::cout<<dp[n][K][m];
	return 0;
}
```






---

## 作者：IGpig (赞：0)

## abc243f

### Solution

考虑动态规划，$dp_{i,j,k}$ 表示在前 $i$ 个物品中，抽 $j$ 次，有 $k$ 个不同奖品的概率。

预处理一下：

- 组合数 $comb_{i,j}$ 表示在从 $i$ 个不同元素中取出 $j$ 个元素的所有组合的个数。
- 乘法逆元，这里采用快速幂法（关于为什么不用拓展欧几里得，因为别的地方要有快速幂）。

初始化：$dp_{0,0,0}=1$（显然）。

##### 动态规划过程

```cpp
for(int i=1;i<=n;i++){//枚举前i个。
    for(int j=0;j<=k;j++){//抽了j次。
        for(int p=0;p<=m;p++){//如果不抽第i个，有p个不同奖品的个数。
            dp[i][j][p]=dp[i-1][j][p];//不抽i，和上一个一样。
        }
     }
     for(int j=1;j<=k;j++){//抽了j次。
        for(int p=1;p<=m;p++){//有p个不同奖品的个数。
           for(int q=1;q<=j;q++){//在j次中，有q次抽到了i,至少一次。
               LL qt=qpow(a[i]*mmi(sum)%mod,q);//q次抽到i,就是抽到一次的概率的q次方。
               LL way=comb[j][q];//在这j次中，q次抽到i的组合。
               dp[i][j][p]=(dp[i][j][p]+dp[i-1][j-q][p-1]*way%mod*qt%mod)%mod;//不抽i的方案加上抽i的方案，注意取模。
            }
         }
     }
}
```

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
const LL mod=998244353;
LL n,m,k,dp[55][55][55]={1},comb[55][55],a[55],sum;// dp[i][j][k]：考虑前 i 个奖品，抽了 j 次，有 p 个不同奖品的概率
void combination(){
    for(int i=0;i<=50;i++){
        comb[i][0]=1;
        for(int j=1;j<=i;j++){
            comb[i][j]=(comb[i-1][j]+comb[i-1][j-1])%mod;
        }
    }
}
inline LL qpow(LL x,LL y){
    LL res=1;
    while(y){
        if(y&1) res*=x;
        x*=x;y/=2;
        x%=mod,res%=mod;
    }
    return res;
}
inline LL mmi(LL x){
    return qpow(x,mod-2);
}
void DP(){
    //enum i
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            for(int p=0;p<=m;p++){
                dp[i][j][p]=dp[i-1][j][p];
            }
        }
        for(int j=1;j<=k;j++){
            for(int p=1;p<=m;p++){
                for(int q=1;q<=j;q++){
                    LL qt=qpow(a[i]*mmi(sum)%mod,q);
                    LL way=comb[j][q];
                    dp[i][j][p]=(dp[i][j][p]+dp[i-1][j-q][p-1]*way%mod*qt%mod)%mod;
                }
            }
        }
    }
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];sum+=a[i];
    }
    combination();
    DP();
    cout<<dp[n][k][m];
    return  0;
}
```

---

## 作者：lihongqian__int128 (赞：0)

考虑概率 DP。

定义 $dp_{i,j,e}$ 为到第 $i$ 个角色，抽了 $j$ 次，出了 $e$ 种角色的概率。

转移：$dp_{i,j,e}\gets\sum\limits_{l=0}^{j}\left(dp_{i-1,j-l,e-[l=0]}\times\left(\begin{array}{cc}j\\l\end{array}\right)\times\left(\dfrac{W_i}{\sum\limits_{p=1}^nW_p}\right)^l\right)$。

解释一下：

$dp_{i-1,j-l,e-[l=0]}$ 表示之前的答案（如果 $l=0$，说明没有出第 $i$ 种角色，种类数不变，否则种类数减 $1$）。

$\left(\begin{array}{cc}j\\l\end{array}\right)$ 表示在抽的 $j$ 次中选 $l$ 次抽角色 $i$。

$\left(\dfrac{W_i}{\sum\limits_{p=1}^nW_p}\right)^l$ 表示这 $l$ 次都出角色 $i$ 的概率。

初始：$dp_{0,0,0}\gets0$。

答案：$dp_{n,m,k}$。

用费马小定理求逆元，再次不再赘述。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=998244353;
int qp(int a,int b){a%=M;int s=1;while(b){if(b&1)s=s*a%M;a=a*a%M,b>>=1;}return s;}
int jc[55],jcn[55];
int C(int n,int m){return jc[n]*jcn[m]%M*jcn[n-m]%M;}
int n,m,k,w[55],dp[55][55][55];
signed main(){
	cin>>n>>m>>k;
	int tot=0;
	for(int i=1;i<=n;i++)cin>>w[i],tot+=w[i];
	int inv=qp(tot,M-2);
	jc[0]=jcn[0]=1;
	for(int i=1;i<=k;i++)jc[i]=jc[i-1]*i%M,jcn[i]=qp(jc[i],M-2);
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=k;j++)
			for(int e=0;e<=m;e++){
				for(int l=0;l<=j;l++){
					if(!e&&l>0)continue;
					dp[i][j][e]=(dp[i][j][e]+dp[i-1][j-l][e-(l>0)]*C(j,l)%M*qp(w[i]*inv,l))%M;
				}
			}
	cout<<dp[n][k][m];
	return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

## solution
本题为**概率动态规划**和**组合数学**。

假设 $k$ 次选到的奖一次是 $a_{1},a_{2},\dots,a_{k}$，那么它的概率是 $\prod_{i=1}^{k}a_{i}$。

假设选的 $m$ 种概率分别是 $b_{1},b_{2},\dots,b_{m}$，选的个数为 $c_{1},c_{2},\dots,c_{m}$。
那么它的概率为 $\frac{k!}{\prod_{i=1}^{m}C_{i}!}\prod_{i=1}^{m}b_{i}^{c_{i}}$，也就是 $k!\prod_{i=1}^{m}\frac{b_{i}^{c_{i}}}{c_{i}!}$。

定义 $dp_{i,j,l}$ 为前 $i$ 个，有 $j$ 个不相同的物品，选了 $l$ 次的概率。

转移方程：

$dp_{i,j,l}=dp_{i,j,l}+dp_{i-1,j-1,l-r}\times\frac{a_{i}^{r}}{r!}+dp_{i-1,j,l}$

两个转移分别代表了取了第 $i$ 种和不取第 $i$ 种的情况。

最终答案为 $dp_{n,m,k}$。

---

## 作者：majoego (赞：0)

这是一个概率 Dp。

我们可以先预处理一下抽到每一个 $i$ 的概率是多少，即：$\frac{W_i}{\sum_{j=1}^{n}W_j}$。

$dp_{i,j,k}$ 表示前 $i$ 个角色，抽了 $j$ 个，$k$ 种不同的角色。

每一次转移的时候都是对第 $i$ 个进行转移，对于这个 $i$，它的概率是 $p_i^x$。$x$ 为抽的个数。

由于 $x$ 可以遍布于之前 $j$ 个中，于是还需要乘上一个组合数：$C_j^x$。

于是我们可以得到 Dp 状态转移方程。

$dp_{i,j,k} = \sum_{x=1}^j dp_{i-1,j-x,k-1} \times p_i^x \times C_j^x$。

最后的答案就是 $dp_{n,K,m}$。

我们可以先预处理一下组合数，就是杨辉三角。

注意，由于有除法，所以需要使用逆元，记得勤取模。

[link](https://atcoder.jp/contests/abc243/submissions/51183236)。

---

