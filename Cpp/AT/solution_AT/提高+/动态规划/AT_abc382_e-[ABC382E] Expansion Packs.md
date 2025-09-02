# [ABC382E] Expansion Packs

## 题目描述

给定无数包卡牌，每一包卡牌有 $N$ 张卡，对于每一张卡 $i$，有百分之 $P_i$ 的概率是稀有卡，否则是普通卡。现在，你要一直开包，直到你有 $X$ 张稀有卡，求你开包的期望次数。

## 说明/提示

- $1 \le N \le 5000$

- $1 \le X \le 5000$

- $1 \le P_i \le 100$


UID：928955

## 样例 #1

### 输入

```
2 2
50 100```

### 输出

```
1.5000000000000000```

## 样例 #2

### 输入

```
2 3
40 60```

### 输出

```
3.2475579530543811```

## 样例 #3

### 输入

```
6 3
10 33 33 10 100 10```

### 输出

```
1.8657859189536100```

# 题解

## 作者：mayike (赞：7)

不会期望，学了些许来做一下。

## 思路

设 $F(i)$ 表示有 $i$ 张稀有牌的期望打开包数，$P(i)$ 表示打开一包有 $i$ 张稀有牌的概率，$A_i$ 表示事件“从第一包到截至目前打开的上一包得到稀有牌个数为 $i$”。根据**全期望公式**，有
$$F(i)=F(F(i\mid A))=\sum_{j=0}^nF(i\mid A_{i-j})P(j)=\sum_{j=0}^n(1+F(i-j))P(j)$$

因为

$$\sum_{i=0}^{n}P(i)=1$$

所以

$$F(i)=\sum_{j=0}^n(1+F(i-j))P(j)=1+\sum_{j=0}^{n}F(i-j)P(j)$$

提 $j=0$ 出来，得

$$F(i)-F(i)P(0)=F(i)(1-P(0))=1+\sum_{j=1}^{n}F(i-j)P(j)$$

$$F(i)=\frac{1+\sum_{j=1}^{n}F(i-j)P(j)}{1-P(0)}$$

因为题目是至少获得 $X$ 张稀有牌，且随着 $i$ 增大 $F(i)$ 单调不减，则有

$$Ans=F(X)$$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,m;
long double a[N],p[N],f[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]/=1.0*100;
	}
	p[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=i;j>=0;j--)p[j]=p[j]*(1-a[i])+(j>0?p[j-1]:0)*a[i];
	for(int i=1;i<=m;i++){
		for(int j=1;j<=min(i,n);j++)f[i]+=f[i-j]*p[j];
		f[i]=(f[i]+1)/(1-p[0]);
	}
	cout<<fixed<<setprecision(6)<<f[m];
	return 0;
}
```

---

## 作者：刘梓轩2010 (赞：6)

## 题意

你有无数包卡牌，每包有 $n$ 张，同时有 $n$ 种稀有卡牌，每张稀有卡牌在每包中出现的概率为 $p_i$，问期望拆多少包卡牌可以获得 $m$ 张稀有卡牌。

$n \le 5000$，$m \le 5000$。

## 思路

很显然，我们可以用 dp 解决这个问题。

设 $f_i$ 为**至少**获得 $i$ 张稀有卡牌的期望拆的包数，$g_i$ 为每包**恰好**获得 $i$ 张卡牌的概率。

我们首先求解 $g$，我们可以考虑新加进来一种稀有卡牌，设新加进来第 $i$ 种稀有卡，考虑转移 $g_j$，那么有两种情况，一种是前 $i-1$ 种卡牌已经拆出 $j$ 张的概率，另一种是前 $i-1$ 种卡牌拆出 $j-1$ 张，同时拆出来了第 $i$ 种的概率，于是转移方程为 $g_j=g_j\times (1-p_i)+g_{j-1}\times p_i$。类似于背包，要倒序转移。

再来求解 $f$。转移时，我们可以枚举这一次拆出来的数量，借助 $g$ 转移。要让总卡牌数至少为 $i$，如果这一包拆出 $j$ 张，则原来至少有 $\max\{0,i-j\}$ 张。方程即为 $f_i=1+\sum_{j=0}^n f_{\max\{0,i-j\}}\times g_j$。

这样还有个问题，$f_i$ 会从自己转移过来，只需要把右边带 $f_i$ 的项移到右边即可。

最终的式子即为 $f_i=\tfrac{1}{1-g_0}\times(1+\sum_{j=1}^n f_{\max\{0,i-j\}}\times g_j)$。

不理解可以结合代码食用。

## Code
```c++
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define fi first
#define se second
using namespace std;
const int N=5000+10;
const int inf=0x3f3f3f3f3f3f3f3f;
double g[N];
double f[N];
int n,x;
double p[N],ans;
signed main()
{
	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
	    cin>>p[i];
	    p[i]/=100;
    }
    g[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=n;j>=1;j--)
        {
            g[j]=g[j]*(1-p[i])+g[j-1]*p[i];
        }
        g[0]*=(1-p[i]);
    }
    for(int i=1;i<=x;i++)
    {
        f[i]=1;
        for(int j=1;j<=n;j++)
        {
            f[i]+=f[max(0ll,i-j)]*g[j];
        }
        f[i]/=(1-g[0]);
    }
    printf("%.8lf",f[x]);
    return 0;
}
```

---

## 作者：sxwgysh (赞：3)

### 题解：AT_abc382_e [ABC382E] Expansion Packs
#### 题意：

有无限包卡，每一包卡里有 $N$ 张卡，其中第 $i$ 张卡为稀有卡的概率为 $P_i$，这里的 $P_i$ 是两两独立的。

求期望抽多少包卡，才能抽到至少 $X$ 张稀有卡。

$N,X\leq 5000$。

#### Solution：

首先，我们可以 DP（背包） 出 $f_i$ 表示一包卡中恰好包含 $i$ 张稀有卡的概率。

之后我们尝试得到一个数组 $g_i$ 表示期望抽到至少 $i$ 张卡的时间。虽然我们没法得到一个明确的 DP，但我们可以枚举最后一次抽到的卡数，并得到一个方程：

$$
g_i=\sum\limits_{j=0}^n g_{\max(0,i-j)}f_j + 1
$$

注意到这个方程中 $g_i$ 只和 $j\leq i$ 的 $j$ 有关，于是可以把与 $i$ 有关的项移到一边，便可得到 $g$ 的一个递推式。

容易做到 $O(n^2)$。

#### Code:

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 5e3 + 10;

int n, X, p[N];
double f[N], g[N], h[N][N], P[N];

signed main()
{
	cin >> n >> X;
	for(int i = 1; i <= n; ++ i)
		cin >> p[i], P[i] = 1.0 * p[i] / 100;
	h[0][0] = 1;
	for(int i = 0; i < n; ++ i)
		for(int j = 0; j <= n; ++ j)
		{
			h[i + 1][j] += h[i][j] * (1 - P[i + 1]);
			h[i + 1][j + 1] += h[i][j] * P[i + 1];
		}
	for(int i = 0; i <= n; ++ i)
		f[i] = h[n][i];
	for(int i = 1; i <= X; ++ i)
	{
		double sum = 0, alpha = 0;
		for(int j = 0; j <= n; ++ j)
		{
			if(j >= i) continue;
			if(j == 0) alpha = f[j];
			else sum += f[j] * g[i - j];
		}
		sum += 1;
		g[i] = sum / (1 - alpha);
	}
	printf("%.10lf", g[X]);
	return 0;
}
```

---

## 作者：Po7ed (赞：3)

赛时没做出来，记录一下。记 $p_i=\dfrac{P_i}{100}$。

### 思路

设 $f(i,j)$ 表示拆一个包，对于包中前 $i$ 张牌，拆出 $j$ 张稀有牌的概率。枚举第 $i$ 张牌是否抽到，可以列出 dp 式：

$$
f(i,0)=(1-p_i)f(i-1,0)\\
f(i,j)=p_if(i-1,j-1)+(1-p_i)f(i-1,j)
$$

依然考虑使用 dp 递推求期望。设 $g(i)$ 表示得到大于等于 $i$ 张牌的期望拆包数，枚举最后一次拆包得到的稀有牌数，可以得到：

$$
g(0)=0\\
g(i)=1+\sum_{j=0}^{i-1}g(i-j)f(j)
$$

但上式无法直接转移，因为当 $j=0$ 时右边含有 $f(i)$。使用经典套路：移项。

$$
\begin{aligned}
g(i)&=1+\sum_{j=0}^{i-1}g(i-j)f(j)\\
g(i)&=1+g(i)f(0)+\sum_{j=1}^{i-1}g(i-j)f(j)\\
\big(1-f(0)\big)g(i)&=1+\sum_{j=1}^{i-1}g(i-j)f(j)\\
g(i)&=\dfrac{1}{1-f(0)}\left(1+\sum_{j=1}^{i-1}g(i-j)f(j)\right)\\
\end{aligned}
$$

这样就可以转移了。答案即为 $g(X)$。

### 代码

```cpp
#include <bits/stdc++.h>

using std::cin;
typedef long long ll;
constexpr int N=5114;
int n,m;
double p[N],f[N],g[N];

void Main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>p[i];
		p[i]/=(100.0);
	}
	f[0]=1.0;
	for(int i=1;i<=n;i++) // 这里压掉了第一维
	{
		for(int j=n;j;j--) // 所以要倒序转移
		{
			f[j]=(f[j-1]*p[i]+f[j]*(1.0-p[i]));
		}
		f[0]*=(1.0-p[i]); // 特殊处理一下，这样不会越界
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<i;j++)
		{
			g[i]+=g[i-j]*f[j];
		}
		g[i]++;
		g[i]/=(1-f[0]);
	}
	printf("%.12lf",g[m]);
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T=1;
	// cin>>T;
	while(T--)Main();
	return 0;
}
```

---

## 作者：Conan15 (赞：2)

太久没写题了，导致这题调半天。由于翻译插件坏了还读错题了一次。

容易想到先设 $dp_{i,j}$ 表示抽了前 $i$ 个，抽到 $j$ 张卡的概率，再设 $f_i=dp_{n,i}$ 表示一包卡中抽出 $i$ 张的概率。\
然后就可以背包了，设 $g_i$ 表示获得 $i$ 张卡的期望抽卡次数，则可以枚举 $j$ 表示这次抽了多少：

$$g_i = 1 + \sum\limits_{j=0}^{n} g_{\max(0,i-j)} \times f_j$$

看上去很对，但是注意到 $j=0$ 的时候等号后面会有 $g_i$ 这一项。\
所以考虑把 $j=0$ 单独提出来，转移方程变为：

$$g_i = 1 + \frac{1}{1 - f_0} ( \sum\limits_{j=1}^{n} g_{\max(0,i-j)} \times f_j )$$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5015;

int n, m, p[N];
long double dp[N][N], f[N], g[N], ans;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] += dp[i - 1][j] * 1.00 * (100 - p[i]) / 100.00;
            if (j) dp[i][j] += dp[i - 1][j - 1] * 1ll * p[i] / 100.00;
        }
    }
    for (int i = 0; i <= n; i++) f[i] = dp[n][i];
    // for (int i = 0; i <= n; i++) printf("%d %.5Lf\n", i, f[i]);
    g[0] = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) g[i] += g[max(0, i - j)] * f[j];
        g[i] = (g[i] + 1) * 1.00 / (1.00 - f[0]);
    }
    printf("%.15Lf\n", g[m]);
    return 0;
}
```

---

## 作者：wizard（偷开O2 (赞：2)

一道倍增 DP 的好题。

## 题意

有无限多的箱子随便给你开，每个箱子中有 $n$ 个物品，第 $i$ 个物品是稀有的概率是 $P_{i}\% $，求获得 $x$ 个稀有物品时打开箱子个数的期望值。

## 分析

因为我的 DP 很差。我尽量用清楚的话语表达我的思想。

我们现在不清楚开多少个箱子才可以达到目的，于是可以设 $dp_{i}$ 表示开当前箱子可以开出 $i$ 个稀有物品的概率。同时，我们还要找到稀有物品在开出物品中的存在性，于是设 $pf_{i,j}$ 表示开当前箱子前 $i$ 个物品中开出 $j$ 个稀有物品的概率。

首先我们考虑如何求出 $pf$。

如果把开箱子的过程看作从单个箱子中连续拿出物品的过程，如果下一个物品不是稀有物品，下一个状态由上一个状态转移而来，那么就有：

$$pf_{i+1,j}=pf_{i+1,j}+pf_{i,j}\times (1-P_{i+1})$$

如果下一个物品是稀有物品，那么就有：

$$pf_{i+1,j+1}=pf_{i+1,j+1}+pf_{i,j} \times P_{i+1}$$

预处理出 $pf$ 数组，我们再反过去处理 $dp$，回顾我给出的 $dp$ 定义。

$dp_{i}$ 表示开当前箱子可以开出 $i$ 个稀有物品的概率。

所以 $dp_{i}=pf_{n,i}$。

因为要求出获得 $x$ 个稀有物品时打开箱子个数的期望值，我们不妨直接枚举稀有物品数量，设 $g_{i}$ 表示开出至少 $i$ 个稀有物品的期望时间。

于是我们可以枚举最后一次抽出的卡数 $j$，最后累计出期望即可。

## 代码

```cpp
//ways:atcoder abc382 dp
//orz aqx wvr zak 
//noip 2024 rp++ 
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ls ((now<<1))
#define rs ((now<<1)|1)
#define mid ((l+r)>>1)
#define checkbug cout << "okok" << endl;
//#define len (r-l+1)
const int maxn=2e5+10;
const int inf=1e9;
const int maxa=5e3+10;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
	
}
int p0[maxn];
double p[maxn];
double pf[maxa][maxa];//前i
int n,x;
double dp[maxn];
double g[maxn];
signed main(){
	cin >> n >> x;
	for(int i=1;i<=n;i++){
		cin >> p0[i];
		p[i]=1.0*p0[i]/100;
	}
	pf[0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=n;j++){
			pf[i+1][j]+=pf[i][j]*(1-p[i+1]);
			pf[i+1][j+1]+=pf[i][j]*p[i+1];
		}
	}
	for(int i=0;i<=n;i++){
		dp[i]=pf[n][i];
	}
	for(int i=1;i<=x;i++){
		double sum,dex;
		sum=0;
		dex=dp[0];
		for(int j=0;j<i;j++){
			sum+=dp[j]*g[i-j];
		}
		sum+=1;
		g[i]=sum/(1-dex);
		
	}
	cout << fixed << setprecision(10) << g[x] << endl;
	return 0;
}
```

---

## 作者：N0_1 (赞：2)

定义概率 $P(i)$ 表示从一包卡片中抽取到 $i$ 张珍贵卡片的概率。

定义 $f(i, j)$ 为在抽取 $i$ 次后获得 $j$ 张珍贵卡片的概率，初始 $f(0, 0) = 1$。

根据定义，可以推导出递推公式：
$$ f(i, j) = \left(\frac{p_i}{100}\right) \times f(i-1, j-1) + \left(1 - \frac{p_i}{100}\right) \times f(i-1, j) $$
其中 $P(i)$ 表示为 $f(n, i)$，即在 $n$ 次抽取后获得 $i$ 张珍贵卡片的概率。

定义 $g(i)$ 为在 $i$ 次抽取中获得珍贵卡片的期望数量，则有：
$$ g(i) = 1 + \sum_{k=0}^{n} f(\max(0, i-k), k) \times P(k) $$

考虑到 $k = 0$ 时的情况，公式应变为：
$$ g(i) = \frac{1}{1 - P(0)} \left[1 + \sum_{k=1}^{n} f(\max(0, i-k), k) \times P(k)\right] $$

通过上述方法，可以利用动态规划算法求解 $g(i)$。

---

## 作者：lhz2022 (赞：1)

在下文中的 $a_i$ 即为题目中的 $\frac{p_i}{100}$。

设 $dp_i$ 为获得至少 $i$ 张稀有卡的概率。

再设 $g_i$ 为再单个卡包中获得恰好 $i$ 张卡的概率。

有 $dp_i=1+\sum_{j=0}^n {dp_{\max(i-j,0)}\times g_j}$ 显然成立。

但是当 $j=0$ 时等式右边有一项 $dp_i$，所以需要对式子其进行一些变形。

具体来说，移项，得 $dp_i-dp_i \times g_0=1+\sum_{j=1}^n {dp_{\max(i-j,0)}\times g_j}$。

即 $dp_i=\frac{1+\sum_{j=1}^n {dp_{\max(i-j,0)}\times g_j}}{1-g_0}$。

然后就是求出 $g_{i,j}$。

显然 $g$ 可以通过两个部分加起来转移得到。第一部分是前面已经获取 $j$ 个的概率（并且这个卡位没有获得稀有卡）再加上这个位置 $i$ 得到了一个稀有卡的概率之和。

所以 $g_{i,j}=g_{i-1,j}\times(1-a_i)+g_{i-1,j-1}\times a_i$。

注意到可以使用滚动数组优化一维空间。

于是化简为 $g_j=g_j\times(1-a_i)+g_{j-1}\times a_i$。

两次转移即可，时间复杂度 $O(N^2+N\times X)$。

[AC 记录](https://atcoder.jp/contests/abc382/submissions/61020995)

---

## 作者：Cosine_Func (赞：1)

很显然的期望 dp。

首先理解什么是期望。期望就是每一数值乘其出现概率的加权平均数，即 $E(X)=\prod_{i=1}^{N}V_i\times P_i$。记题中 $p_i=\frac{P_i}{100}$,设 $f_i$ 为一包卡中抽出 $i$ 张的概率，容易发现这是一个背包问题，易得状态转移方程：
$$
f_{j+1}=f_{j+1}+f_j\times p_i
$$
$$
f_j=f_j\times(1-p_i)
$$
接下来求期望。设 $g(i)$ 为至少再抽 $i$ 张后满足要求的期望，枚举每次抽的数量，可得状态转移方程：
$$
g(i)=\frac{1+\sum_{i-1}^n f_j\times g_{i+j}}{1-f_0}
$$

答案为 $g(0)$。

[参考代码](https://atcoder.jp/contests/abc382/submissions/60557404)

---

## 作者：roBotic (赞：1)

> 有无限个箱子，每个箱子里有 $n$ 个的物品，每个箱子重第 $i$ 个物品是稀有的概率是 $p_i\%$，每次可以打开整个箱子，获得其中所有物品，求获得 $X$ 个稀有物品时打开箱子个数的期望。

*以下文章中 $\textit{p}_i$ 均指原文中的概率百分比之后除以一百的小数值。*

期望背包 dp，先定义数组 $g_i$ 表示对于一个箱子，打开这个箱子正好获得 $i$ 个稀有物品的概率。这个可以 dp 得到，我们用一个辅助 dp 数组 $h_{i,j}$ 表示已经取走了前 $i$ 个物品，有 $j$ 个稀有的概率。初始化 $h_{0,0}=1$。那么我们有转移方程：

$$h_{i,j}=h_{i-1,j}\times (1-p_i)+h_{i-1,j-1}\times p_i.$$

所以我们得到了 $g$ 数组： $g_i=h_{n,i}$。

然后我们再次 dp，定义 $f_j$ 表示取得至少 $j$ 个稀有物品的期望打开箱子数。有以下 dp 方程：

$$f_i=\sum_{j=0}^i f_{\max(i-j,0)}\times g_j.$$

然后会发现这是一个一元一次的方程，他的形式可以变成：

$$\begin{aligned}
f_i&=g_0f_i+t,\\
t&=\sum_{j=1}^i f_{\max(i-j,0)}\times g_j.
\end{aligned}$$

我们可以 $O(n)$ 求出 $t$，然后移项除以系数算出 $f_i$。有：

$$f_i=\frac{t}{1-g_0}.$$

最终答案就是 $f_X$。

[My Submission.](https://atcoder.jp/contests/abc382/submissions/60326227)

---

## 作者：201012280925LSY (赞：1)

## 题目大意
有若干个盒子，每个盒子当中有 $N$ 张牌。第 $i$ 张牌出现的概率是 $\frac{P_i}{100}$。请输出拿到 $X$ 张牌期望打开的盒子数量。$P_i$ 是整数且 $1 \le P_i \le 100$。 

## 思路
很显然是一个概率 DP。

我们令 $f_i$ 表示获得 $i$ 张牌所期望的打开盒子的数量，令 $g_i$ 表示打开一个盒子能够获得 $i$ 张牌的期望概率。

推出来转移方程应该是 
$$
f_i=1+\sum_{j=0}^Nf_{i-j}\times g_j
$$

$1$ 是因为相对于 $f_{i-j}$ 我们肯定要多打开 $1$ 个盒子，然后在这个盒子里获得 $j$ 张牌，所以 $f_{i-j}$ 要乘上 $g_j$。

观察这个式子，发现当 $j=0$ 时，式子变为 $f_i \times g_0$，有一个 $f_i$ 所以是不可以的。

考虑把 $j=0$ 拆出来。
$$
f_i-(f_i \times g_0)=1+\sum_{j=1}^Nf_{i-j}\times g_j
$$
提取公因数，即为：
$$
f_i\times(1-g_0)=1+\sum_{j=1}^Nf_{i-j} \times g_j
$$
把 $(1-g_0) $ 除到右边去，得：
$$
f_i=\frac{1}{1-g_0} \times (1+\sum_{j=1}^N f_{i-j} \times g_j)
$$
这个可以用 $O(NX)$ 的时间复杂度把答案 $f_X$ 求出来。


接下来考虑把 $g_{0} \sim g_{N}$ 求出来。

令 $DP_{i,j}$ 表示盒子里的前 $i$ 张牌获得了 $j$ 张牌的期望概率。

所以 $DP_{i,0} = DP_{i-1,0} \times \frac{100-P_i}{100}$。

而当 $1 \le j \le i$ 时，转移方程为：
$$
DP_{i,j}=\frac{P_i}{100} \times DP_{i-1,j-1} + \frac{100-P_i}{100} \times DP_{i-1,j}
$$
其中 $\frac{P_i}{100} \times DP_{i-1,j-1}$ 表示新的一张牌获得了，$\frac{100-P_i}{100} \times DP_{i-1,j}$ 表示新的一张牌没有获得。

显然 $g_i=DP_{N,i}$。

所以求解 $g_i$ 的时间复杂度是 $O(N^2)$，总的时间复杂度是 $O(N^2+NX)$。

注意到 $f_i$ 的转移方程中有一个 $\frac{1}{1-g_0}$，但是因为 $g_0 = \prod_{i=1}^{N}\frac{100-P_i}{100}$，并且 $1 \le P_i \le 100$，所以说 $\frac{100-P_i}{100} < 1$，所以 $g_0=\prod_{i=1}^{N}\frac{100-P_i}{100} < 1$，则 $1-g_0 >0$。 

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,n; 
long long p[5010];
double DP[5010][5010],f[5010];
int main()
{
	scanf("%lld%lld",&n,&x);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&p[i]);
	}
	DP[0][0]=1;
	f[0]=0;
	for(int i=1;i<=n;i++)
	{
		DP[i][0]=DP[i-1][0]*((100-p[i])/100.0);
		for(int j=1;j<=i;j++)
		{
			DP[i][j]=(p[i]/100.0)*DP[i-1][j-1]+DP[i-1][j]*((100-p[i])/100.0);
		}
	}
	for(int i=1;i<=x;i++)
	{
		f[i]++;
		for(int j=1;j<=n;j++)
		{
			f[i]+=f[max(i-j,0)]*DP[n][j];
		}
		f[i]*=(1.0)/(1.0-DP[n][0]);
	}
	printf("%.20lf",f[x]);
	return 0;
}
```

---

## 作者：gejunyi1Longer2csbs (赞：1)

### AT_abc382_e Expansion Packs 题解

---

[题目传送门](https://www.luogu.com.cn/problem/AT_abc382_e)

**题意**

有无数包牌，每包有 $ n $ 张牌。在每包牌中，$ i $ 这张牌是稀有的牌的概率为 $ p_i \% $。每张牌是否稀有与其他牌是否稀有无关。求一直开包直到总共获得至少 $ x $ 张稀有卡牌时，开包的预期次数。

**思路**

考虑 $ dp $,设 $ f_{i,j} $ 是在前 $ i $ 张牌中得到 $ i $ 张稀有卡牌预计需要拆开的卡包数，初始化 $ f_{0,0}=1 $，可得状态转移方程：

$$
f_{i,j}=f_{i-1,j} \times (1-p_i\%) + f_{i-1,j-1} \times p_i\%\\
$$

求值为 $ f_{n,x} $ 。

设 $ g_i $ 是一个卡包里正好包含 $ i $ 张稀有卡牌的期望拆开卡包数，初始化 $ g_0=0 $，可得状态转移方程：

$$
g_i=\sum_{j=1}^{i-1} g_{i-j} \times f_{n,j}
$$

求值为 $ g_x $。

时间复杂度：$ O(n^2+nx) $

[AC Link](https://www.luogu.com.cn/record/192834404) / [Code](https://www.luogu.com.cn/paste/2armr7ir)

---

## 作者：Little_Fox_Fairy (赞：0)

### 闲话

今天刚刚学了概率 DP，回来补一下这道题。

### Description

你现在需要开卡包，每个卡包里面有 $ n $ 张卡片。在这 $ n $ 张卡片中，第 $ i $ 张卡片为稀有卡片的概率为 $ p_i\% $。现在询问至少获得 $ x $ 张稀有卡片时，打开卡包的数量的期望值。

### Solution

观察题面我们发现，题面让求的期望值，由于每一张稀有卡片的贡献均为 $ 1 $，所以题目实际上就是求至少获得 $ x $ 张稀有卡片时，打开卡包的数量的概率之和。

首先，我们设 $ f_{i,j} $ 表示一个卡包中前 $ i $ 张卡片，其中有 $ j $ 张是稀有卡片的概率。然后这个所有的 $ f_{i,j} $ 就可以在 $ O(n^2) $ 的时间内求出。

此时的转移式为：

$$
f_{i,j} = \sum_{j=0}^{n} f_{i-1,j} \times (1 - p_i) + f_{i-1,j-1} \times p_i
$$

（这里的 $ p_i $ 为题面上的 $ p_i $ 除以 $ 100 $，即百分数的小数形式）

求出 $ f_(i,j) $ 之后，我们再设 $ dp_i $ 表示获得 $ i $ 张稀有卡片所需要开的卡包个数的期望值。那么 $ dp $ 数组的转移式就为：

$$
dp_i = \sum_{j=0}^{i-1} {1 + dp_{i-j} \times f_{n,j} } 
$$

但是我们又发现，当 $ j=0 $ 时，我们会用 $ dp_i $ 更新 $ dp_i $，这是不行的，所以我们要对原转移式做一些调整。

$$
dp_i = 1 + f_{n,0} \times dp_i +  \sum_{j=1}^{i-1} { dp_{i-j} \times f_{n,j} } \\

dp_i - f_{n,0} \times dp_i = 1 + \sum_{j=1}^{i-1} { dp_{i-j} \times f_{n,j} }  \\

dp_i \times (1 - f_{n,0})= 1 + \sum_{j=1}^{i-1} { dp_{i-j} \times f_{n,j} }  \\

dp_i = \dfrac{1 + \sum_{j=1}^{i-1} { dp_{i-j} \times f_{n,j} }}{1 - f_{n,0}}

$$

然后就求完 $ dp $ 数组了，此时答案为 $ dp_x $。

### Code
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++) 
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=5e3+10;

int n,m;
double p[N],f[N][N],dp[N];
signed main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	rep(i,1,n) cin>>p[i],p[i]=p[i]/100;
	f[0][0]=1;
	rep(i,1,n) {
		rep(j,0,i){
			f[i][j]+=f[i-1][j]*(1-p[i])+f[i-1][j-1]*p[i];
		}
	}
	rep(i,1,m) {
		dp[i]=1;
		rep(j,1,i-1) {
			dp[i]+=dp[i-j]*f[n][j];
		}
		dp[i]/=(1-f[n][0]);
	}
	cout<<fixed<<setprecision(10)<<dp[m]<<endl;
	return (0-0);
}
```

---

## 作者：liugh_ (赞：0)

### [[ABC382E] Expansion Packs](https://www.luogu.com.cn/problem/AT_abc382_e)

> 给定长度为 $n$ 的序列 $g$，其中 $p_i$ 为第 $i$ 个物品在一次操作中被选中的概率，求期望操作次数使得选了**至少** $m$ 个物品。$n,m\le 5000$。

设 $f(i)$ 为选了 $i$ 个物品的期望操作次数，操作可能是无限的，不能直接递推怎么办？先列转移方程！
$$
f(i)=1+\sum_{k=0}^{i} f(i-k)g_k
$$
其中 $g_k$ 为一次操作中选中 $k$ 个物品的概率。注意到不能直接递推的原因在于当 $k=0$ 时有 $f(i)g_0$ 的贡献，于是考虑移项，有
$$
f(i)=\frac{1+\sum_{k=1}^{i} f(i-k)g_k}{1-g_0}
$$
注意题目要求**至少** $m$ 个物品，故我们需要对转移方程稍作修改，使得超出 $m$ 的贡献落到 $f(m)$ 上，即
$$
f(i)=\frac{1+\sum_{k=1}^{m} f(\max\{i-k,0\})g_k}{1-g_0}
$$
时间复杂度 $\Theta(nm)$。

```cpp
for(int i=1;i<=n;i++){int x;cin>>x;p[i]=x/100.0;}
g[0]=1;
for(int i=1;i<=n;i++){
    for(int j=n;j>=1;j--)g[j]=p[i]*g[j-1]+(1-p[i])*g[j];
    g[0]*=1-p[i];
}
for(int i=1;i<=m;i++){
    f[i]=1;
    for(int j=1;j<=n;j++)f[i]+=f[max(i-j,0ll)]*g[j];
    f[i]/=1-g[0];
}
```

---

## 作者：_smart_stupid_ (赞：0)

赛时没推出来，但是觉得较有质量，所以写一篇题解。

首先，让我们用 $dp_i$ 表示开 $i$ 张稀有卡期望要开的包数，让 $dp1_i$ 表示开一包开到 $i$ 张稀有卡的概率。

我觉得你应该可以推出 DP 式子来了。
## 计算 $dp_i$
可以得到这个式子：

$$
dp_i = 1 + \sum\limits_{k=0}^n dp_{\max(i - k, 0)} \cdot dp1_k
$$

很好理解，讨论一包可以开出来的卡牌数，并进行转移。

但是在编码时，发现 $dp_i$ 需要用 $dp_i$ 进行转移，所以考虑移项：

$$
dp_i = 1 + dp_i\cdot dp1_0 +  \sum\limits_{k=1}^n dp_{\max(i - k, 0)} \cdot dp1_k
$$

$$
dp_i \cdot (1 - dp1_0) = 1 + \sum\limits_{k=1}^n dp_{\max(i - k, 0)} \cdot dp1_k
$$

$$
dp_i = \frac{1 + \sum\limits_{k=1}^n dp_{\max(i - k, 0)} \cdot dp1_k}{1 - dp1_0}
$$

由于每一张卡都有概率被开出来，所以 $dp1_0$ 不可能为 $1$，也就不会发生除 $0$ 错误。

## 计算 dp1_i

~~如果暴力枚举……~~

枚举这种若只做法就不说了，对于每一张牌更新 $dp1_i$，让 $dp2_i$ 表示我们更新后得到的数组。首先，能开出来的情况：

$$
dp2_i = dp1_{i-1}\cdot \frac{p_i}{100}
$$

不能开出来的情况：

$$
dp2_i = dp1_i\cdot (1 - \frac{p_i}{100})
$$

合起来：

$$
dp2_i = dp1_{i-1}\cdot \frac{p_i}{100} + dp1_i\cdot (1 - \frac{p_i}{100})
$$

题外话，诸位有没有觉得这个公式和一个组合公式很像？

$$
C_m^n = C_{m-1}^{n-1}+C_{m-1}^n
$$

最后，由于 $dp_i$ 中 $i$ 不超过 $x$，所以转移时只需要 $NX$ 的复杂度，$dp1_i$ 一共用 $N$ 张牌分别更新 $N$ 中情况，所以复杂度是 $\Theta(N\max(N,X))$ 的。

## Let's AC！

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, x, a[5010];
double dp[5010], p[5010], dp1[5010], dp2[5010];
void dfs(int x) {
	if (dp[x] || x <= 0) return;
	for (int i = 1; i <= min(n, x); i++) dfs(x - i);
	for (int i = 1; i <= n; i++) {
		dp[x] += (dp[max(x - i, 0)]) * dp1[i];
	}
	dp[x]++;
	dp[x] /= (1 - dp1[0]);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> x;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		p[i] = (double)a[i] / 100.0;
	}
	dp1[0] = 1;  //一开始一张牌都不选，一定是0。
	for (int i = 1; i <= n; i++) {
		dp2[0] = dp1[0] * (1 - p[i]);
		for (int j = 1; j <= n; j++) {
			dp2[j] = dp1[j - 1] * p[i] + dp1[j] * (1 - p[i]);
		}
		for (int j = 0; j <= n; j++) {
			dp1[j] = dp2[j], dp2[j] = 0;  // 使用滚动数组节省空间
		}
	}
	dfs(x);
	cout << fixed << setprecision(20) << dp[x] << '\n'; //注意精度
	return 0;
}
```

---

## 作者：Albert_van (赞：0)

[题](https://www.luogu.com.cn/problem/AT_abc382_e) [题](https://atcoder.jp/contests/abc382/tasks/abc382_e)。一个抽象思路。以下 $m$ 为题述 $X$。这种“多次操作直到满足条件”的惯用思路是，记 $q(t)$ 表示 $t$ 次操作后**仍不满足条件**的**概率**，答案即为 $\sum q(t)$（由期望的线性性，每次操作对答案的贡献为 $1$，将其乘上概率加和即为期望）。这题令 $q(t)$ 表示开了 $t$ 个包后抽到的总卡数 $<m$ 的概率，答案为 $\sum_{t=0}^{+\infty} q(t)$。

先不管那个 $+\infty$，考虑给出 $t$ 如何计算 $q(t)$。记 $g(t,i)$ 表示开了 $t$ 个包后抽到总卡数恰为 $i$ 的概率，$f(x)$ 表示开一个包拿到恰好 $x$ 张卡的概率，显然有：
$$
g(t,i)=\sum_x g(t-1,i-x)f(x)
$$
求 $f(x)$ 也是简单背包，考虑加入一张概率为 $p$ 的卡对 $f$ 的贡献：
$$
\forall x,f(x)\gets p\times f(x-1)+(1-p)\times f(x)
$$
现在问题在于如何处理 $+\infty$。第一思路是，因为这题小数形式输出，所以当 $q(t_0)=\sum_{i<m} g(t_0,i)<\epsilon$ 时就不用去算 $t>t_0$ 的 $q(t)$ 了。这题取 $\epsilon=10^{-7}$，对于 $t\le t_0$ 的部分直接暴力递推。这个算法可以通过 Atcoder 上 $35$ 个测试点中的 $34$ 个。稍加思考发现，虽然 $t_0$ 的上界可以保证（极端情况 $n=1,p_1=1\%$，此时条件近似为 $(99\%)^{t_0}<\epsilon$，与 $m$ 弱相关，$t_0$ 是 $10^3$ 级别的），但是 $g$ 的递推过程中对精度的要求同样指数增长，$g(t,i)(i\ge m)$ 的数量级远超 `long double` 所能处理的范围，实测极端情况下用 `long double` 递推时 $q(10^6)$ 仍然 $>1-\epsilon$，这说明 $\ge m$ 的那部分概率被浮点误差给完全吃掉。

成也小数，败也小数。重新去看 $g$ 的递推式，发现形如卷积，写成生成函数形式即为 $g(t)(x)=f^t(x)$，所求即为
$$
\sum_{t=0}^{+\infty}f^t(x)=\frac 1{1-f(x)} \pmod{x^m}
$$
直接多项式求逆，把板子贺过来换上 FFT 发现炸精（误差高达 $10^{-4}$），那么暴力多项式乘法即可，总复杂度 $\mathcal O(n^2+m^2)$。另外，这题如果在整数域上取模做可以做到 $\mathcal O(n\log^2 n+m\log m)$（求 $f$ 可以直接分治 NTT）。

```cpp
#include <cstdio>
#define ld long double

const int N=5141;ld a[N],b[N],c[N],d[N];

void Inv(int n){
	if(n==1) return b[0]=1/a[0],void();
	Inv(n+1>>1);
	for(int i=0;i<n;++i) c[i]=d[i]=0;
	for(int i=0;i<n;++i) for(int j=0;i+j<n;++j) c[i+j]+=a[i]*b[j];
	for(int i=0;i<n;++i) for(int j=0;i+j<n;++j) d[i+j]+=c[i]*b[j];
	for(int i=0;i<n;++i) b[i]=2*b[i]-d[i];
}

int main()
{
	int n,m;scanf("%d%d",&n,&m);
	a[0]=1;for(int i=1;i<=n;++i){
		ld p;scanf("%Lf",&p);p/=100;
		for(int k=i;~k;--k) a[k]=(k?a[k-1]:0)*p+a[k]*(1-p);
	}
	for(int i=0;i<=n;++i) a[i]=-a[i];
	a[0]+=1;Inv(m);ld ans=0;
	for(int i=0;i<m;++i) ans+=b[i];
	printf("%.7Lf",ans);
}
```

---

## 作者：CuteForces (赞：0)

首先，我们令 $P(i)$ 为一包卡开出 $i$ 张稀有卡的概率。

我们可以用动态规划，令 $f_{i,j}$ 为 $i$ 张卡出 $j$ 张稀有卡的概率，$f_{0,0}=1$。

我们可以得出 $f_{i,j}=\frac{p_i}{100}f_{i-1,j-1}+(1-\frac{p_i}{100})f_{i-1,j},P(i)=f_{n,i}$。

---

接下来，我们令 $f_i$ 为 $i$ 张稀有卡的期望次数。就可以枚举 $j$，从 $f_{i-j}$ 来推出 $f_i$。就是：

$$f_i=1+\sum\limits_{j=0}^nf_{\max\{0,i-j\}}P(j)$$

但是，当 $j=0$ 时，会发现 $f_i$ 在右边的系数为 $P(0)$，需要移项。转移过去后，就变成：

$$f_i=\frac{1}{1-P(0)}[1+\sum\limits_{j=1}^nf_{\max\{0,i-j\}}P(j)]$$

这样就可以动态规划了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5010;
int n,m;
double a[N],p[N][N],f[N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]/=100;
	}
	p[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			p[i][j]=p[i-1][j]*(1-a[i]);
			if(j) p[i][j]+=p[i-1][j-1]*a[i];
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++) f[i]+=f[max(i-j,0)]*p[n][j];
		f[i]=(f[i]+1)/(1-p[n][0]);
	}
	printf("%.9lf",f[m]);
	return 0;
}
```

---

