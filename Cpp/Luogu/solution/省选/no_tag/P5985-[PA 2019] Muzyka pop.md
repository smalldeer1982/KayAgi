# [PA 2019] Muzyka pop

## 题目描述

给定 $ n$ 个整数 $a_{1..n}$，请找到 $n$ 个非负整数 $b_{1..n}$，使得 $a_1\times \operatorname{f(b_1)}+a_2\times \operatorname{f(b_2)}+...+a_n\times \operatorname{f(b_n)}$ 的值最大，其中 $\operatorname{f(x)} $ 为 $x$ 在二进制下的 $1$ 的个数。

你找到的这 $n$ 个非负整数 $b_{1..n}$ 需要满足 $0\le b_1<b_2<...<b_n\le m$。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 200$，$n-1\le m\le 10^{18}$，$|a_i|\le 10^{14}$。

----

### 解释：

$b_1=3,b_2=4,b_3=5$，则答案为 $2\times 2+(-1)\times 1+3\times 2=9$。

## 样例 #1

### 输入

```
3 5
2 -1 3```

### 输出

```
9```

# 题解

## 作者：mRXxy0o0 (赞：5)

不妨在 Trie 树上考虑这个问题。

首先建一颗树：

![HLB的倾情赠予](https://cdn.acwing.com/media/article/image/2023/09/27/155587_96a47f5d5d-4.PNG)

这样一来，对于 $m$ 的限制就自然转化成了只取字典树的前半部分。

先考虑 DP，设 $f_{u,l,r}$ 表示 $u$ 号点的子树内取出 $b$ 数组中下标 $[l,r]$ 的部分。

我们考虑一个节点 $u$ 向其儿子转移的过程。很自然地，可以得到 $f_{u,l,r}=\max\limits_{k=l-1}^{r}(f_{ls,l,k}+f_{rs,k+1,r}+a_{k+1}+\dots+a_r)$ 的转移方程。

明显，这里无法枚举所有 Trie 树上的点。但是又发现，同一层上的点除了高位限制以外，本质上是一样的。

所以我们改进一下 DP 数组的定义。$f_{i,l,r,0/1}$ 表示第 $i$ 层之下取出 $b$ 数组中下标 $[l,r]$ 的部分，最后一维表示有无高位限制。按原式计算即可。

据说还可以四边形不等式优化，就看别的奆佬的题解吧（笑。

再仔细一想，发现它竟然和数位 DP 一模一样，其实这本质上是一致的。可是第一眼确实想不太到数位 DP。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=210,M=61;
int n,s[N][N];
ll f[M][N][N][2],a[N],m;
inline ll max(ll x,ll y){
	return x>y?x:y;
}
int main(){
	memset(f,-0x3f,sizeof f);
	scanf("%d%lld",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		a[i]+=a[i-1];
		f[0][i][i][0]=f[0][i][i][1]=0;
	}
	for(int i=0;i<M;++i) for(int j=1;j<=n+1;++j) f[i][j][j-1][0]=f[i][j][j-1][1]=0;
	for(int i=1;i<M;++i)
		for(int l=1;l<=n;++l)
			for(int r=l;r<=n;++r){
				if(m&(1ll<<i-1)) for(int k=l-1;k<=r;++k) f[i][l][r][1]=max(f[i][l][r][1],f[i-1][l][k][0]+f[i-1][k+1][r][1]+a[r]-a[k]);
				else f[i][l][r][1]=f[i-1][l][r][1];
				for(int k=l-1;k<=r;++k) f[i][l][r][0]=max(f[i][l][r][0],f[i-1][l][k][0]+f[i-1][k+1][r][0]+a[r]-a[k]);
			}
	printf("%lld",f[M-1][1][n][1]);
	return 0;
}
```


---

## 作者：Betrayer_of_love (赞：3)

[题目传送器](https://www.luogu.com.cn/problem/P5985)

### 题解：

---

考虑有一棵包含了 $[0,m]$ 所有数 01Trie，有一种暴力 DP：设 $f(x,l,r)$ 表示将 $al,al+1\dots a_r$ 分配给 Trie 树上 $x$ 子树内的最大值。发现若 $x$ 子树满二叉树，则同一深度这样的 $x$ 都是等价的，只有 $m$ 所在的那一条链不是这样。因此状态可以优化为 $f(i,l,r,0/1)$，表示当前深度为 $i$，考虑 $[l,r]$ 的 $a$，当前是否在 $m$ 所在的那一条链上的最大值。分类讨论转移即可。

### CODE:

---


```cpp

#include<bits/stdc++.h>
#define maxn 210
#define maxm 62
#define inf 1000000000000000000
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x){
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
ll n,m,lim=1;
ll s[maxn],f[maxm][maxn][maxn][2];
int main(){
    read(n),read(m);
    while(((ll)1<<lim)<=m) lim++;
    for(int i=1;i<=n;++i) read(s[i]),s[i]+=s[i-1];
    for(int i=0;i<=lim;++i)
        for(int l=1;l<=n;++l)
            for(int r=l;r<=n;++r)
                for(int k=0;k<=1;++k)
                    f[i][l][r][k]=-inf;
    for(int i=1;i<=n;++i) f[0][i][i][0]=f[0][i][i][1]=0;
    for(int i=1;i<=lim;++i){
        for(int l=1;l<=n;++l){
            for(int r=l;r<=n;++r){
                f[i][l][r][0]=f[i-1][l][r][0]+max(s[r]-s[l-1],(ll)0);
                for(int k=l;k<r;++k)
                    f[i][l][r][0]=max(f[i][l][r][0],f[i-1][l][k][0]+f[i-1][k+1][r][0]+s[r]-s[k]);
                if(m&((ll)1<<(i-1))){
                    f[i][l][r][1]=max(f[i-1][l][r][0],f[i-1][l][r][1]+s[r]-s[l-1]);
                    for(int k=l;k<r;++k)
                        f[i][l][r][1]=max(f[i][l][r][1],f[i-1][l][k][0]+f[i-1][k+1][r][1]+s[r]-s[k]);
                }
                else f[i][l][r][1]=f[i-1][l][r][1];
            }
        }
    }
    printf("%lld",f[lim][1][n][1]);
    return 0;
}
```


**完结撒花，谢谢！！！**

---

## 作者：teylnol_evteyl (赞：3)

先不考虑 $m$ 的限制。

设 $f_{k,l,r}$ 表示区间 $[l,r]$ 的数 $b_i<2^k$ 的最大价值，枚举最高为取值为 $0,1$ 的分界线，则状态转移为：
$$f_{k,l,r}=\max_{i=l}^r\{f_{k-1,l,i}+f_{k-1,i+1,r}+s_r-s_i\}$$

其中 $s_i$ 表示 $a_i$ 的前缀和。

边界为 $f_{k,i,i}=k\max\{0,a_i\}$。

这个 DP 的时间复杂度是 $O(n^3\log m)$。

实际上，这个 DP 满足四边形不等式，可以进行四边形不等式优化，时间复杂度 $O(n^2\log m)$。

现在加上 $m$ 的限制。设 $g_{k,i}$ 表示前 $i$ 个数，最后一个数的 $b$ 最高的与 $m$ 不同数位在第 $k$ 位的最大价值。转移为：

$$g_{k,i}=\max\{g_{k+1,i},g_{k+1,j}+f_{k,j+1,i}+\operatorname{F}(m,k)(s_i-s_j)\}$$

其中第 $2$ 部分 $m$ 的第 $k$ 位为 $1$，$\operatorname{F}(m,k)$ 表示 $m$ 高于 $k$ 位的部分 $1$ 的个数。

时间复杂度 $O(n^2\log m)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 205, K = 63;

int n;
LL m, a[N], f[K][N][N], g[K][N], ans;
int s[K][N][N];
int p[K + 5], t;

int main()
{
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; i ++ ) scanf("%lld", &a[i]), a[i] += a[i - 1];
	if(m == 1)
	{
		printf("!%d\n", a[1]);
		return 0;
	}
	
	for(int i = 1; i <= n; i ++ )
		for(int j = i + 1; j <= n; j ++ )
			f[0][i][j] = -2e18;
	int kk = log2(m) + 1;
	LL w;
	for(int k = 1; k < kk; k ++ )
		for(int i = n; i >= 1; i -- )
		{
			f[k][i][i] = f[k - 1][i][i] + max(0LL, a[i] - a[i - 1]), s[k][i][i] = i;
			for(int j = i + 1; j <= n; j ++ )
			{
				f[k][i][j] = -2e18;
				for(int l = s[k][i][j - 1]; l <= s[k][i + 1][j]; l ++ )
				{
					w = f[k - 1][i][l] + f[k - 1][l + 1][j] + a[j] - a[l];
					if(w > f[k][i][j]) f[k][i][j] = w, s[k][i][j] = l;
				}
			}
		}
	
	ans = -1e18;
	memset(g, 0xe3, sizeof g);
	for(int i = K - 1; i >= 0; i -- )
		if(m >> i & 1)
			p[ ++ t] = i;
	for(int i = 1; i <= n; i ++ ) g[1][i] = f[p[1]][1][i];
	for(int k = 1; k <= t; k ++ )
		for(int i = 1; i <= n; i ++ )
			for(int j = i; j <= n; j ++ )
					g[k + 1][j] = max(g[k + 1][j], g[k][i] + f[p[k + 1]][i + 1][j] + (a[j] - a[i]) * k);
	for(int i = 1; i <= t + 1; i ++ ) ans = max(ans, g[i][n]);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Acoipp (赞：3)

首先看到 $b$ 的限制，$b$ 数列的每个数在二进制拆分下来说，最高位的值一定是递增的，如果最高位相同，再比较次高位，以此类推。

我们就可以设 $dp_{l,r,p,limit}$ 表示 $b_l \sim b_r$ 这一个范围内，只决策了小于等于 $2^p$ 的位，能够获得的最大值是多少。

$limit$ 就像数位 dp 一样规定这个位是否是顶着 $m$ 取的，然后按照数位 dp 的方式转移就可以了，把当前位可以取的上界 $up$ 弄出来就可以了。

如果 $up=0$，那么这一位只能全部填 $0$，直接 $dp_{l,r,p,limit} \gets dp_{l,r,p-1,limit}$ 就可以了。

否则这一位可以全部填 $0$ 或者全部填 $1$ 或者一半 $0$ 一半 $1$，那么就相当于：

$$
dp_{l,r,p,limit} = \max(dp_{l,r,p-1,0},dp_{l,r,p-1,1}+\sum_{i=l}^r a_i,\max_{l \le k<r} (dp_{l,k,p-1,0}+dp_{k+1,r,p-1,1}+\sum_{i=k+1}^r a_i))
$$

加的 $\sum$ 表示我们对于这些数字当前位填 $1$ 就有一个 $a_i$ 的贡献，这一部分用前缀和计算即可。

边界情况：$p=0$ 的时候，我们只有当 $l=r$ 时才有解，否则需要满足 $b_i<b_{i+1}$，无解，返回一个较小的值就可以了。

初始化一定要赋值 $-10^{18}$，我因为这一个原因 WA 了几次。

最后我们可以采用递归或者循环实现，循环实现会比较快，可能 2s 左右，递归就很慢了，不建议使用，代码使用的是循环版本：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 205
using namespace std;
ll n,m,i,j,k,l,r,p,o,up,a[N],s[N],maps[N][N],dp[N][N][N][2],len,pos[N],tot;
inline void cmax(ll &a,ll b){if(a<b) a=b;}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	if(m==0){
		cout<<0<<endl;
		return 0;
	}
	while(m) pos[++tot] = m%2,m /= 2;
	for(i=1;i<=n;i++) cin>>a[i],s[i]=s[i-1]+a[i];
	for(i=1;i<=n;i++){
		for(j=i;j<=n;j++){
			if(i==j) dp[0][i][j][0]=dp[0][i][j][1]=0;
			else dp[0][i][j][0]=dp[0][i][j][1]=-1e18;
			maps[i][j] = s[j]-s[i-1];
		}
	}
	for(i=1;i<=tot;i++){
		for(l=1;l<=n;l++){
			for(r=l;r<=n;r++){
				dp[i][l][r][0] = -1e18;
				up = 1;
				dp[i][l][r][0] = max(dp[i-1][l][r][0],dp[i-1][l][r][0]+maps[l][r]);
				for(o=l;o<r;o++) cmax(dp[i][l][r][0],dp[i-1][l][o][0]+dp[i-1][o+1][r][0]+s[r]-s[o]);
				
				dp[i][l][r][1] = -1e18;
				up = pos[i];
				if(!up) dp[i][l][r][1] = dp[i-1][l][r][1];
				else dp[i][l][r][1] = max(dp[i-1][l][r][0],dp[i-1][l][r][1]+maps[l][r]);
				if(up) for(o=l;o<r;o++) cmax(dp[i][l][r][1],dp[i-1][l][o][0]+dp[i-1][o+1][r][1]+s[r]-s[o]);
			}
		}
	}
	cout<<dp[tot][1][n][1]<<endl;
	return 0;
}
```

另：这题好像有四边形不等式优化的做法（基于上述普通 dp），跑得飞快，是 [liyixi_i](https://www.luogu.com.cn/user/636142) 提出的，但是我不会证。。。

---

## 作者：chaynflow (赞：3)

## Description

给定 $n,m$ 与 $n$ 个整数 $a$，构造序列 $b$，满足 $0 \le b_1 < b_2 < \cdots < b_n \le m$，求最大的 $\sum_{i=1}^n a_i \times\operatorname{popcount}(b_i)$。

## Solution

对于 $\operatorname{popcount}$ 这一类的二进制东西，考虑类数位 dp 做法，设计状态 $f_{l,r,p,0/1}$ 表示计算 $l \sim r$ 这一段数，已经计算到二进制第 $p$ 位（最低位为第 $0$ 位），是否无上界（或者说上界为 $2^{p+1} -1$）限制的最大答案。

递推不好写，就记搜吧，以下的 $num$ 表示记搜过程中的上界（$m$ 的后 $0 \sim p$ 位或者 $2^{p+1}-1$）。

分两种情况转移。

+ 如果 $num \operatorname{and} 2^p = 0$，就说明这一位没 $1$ 可选，直接转移到 $f_{l,r,p,0} = f_{l,r,p-1,[num=2^p-1]}$。

+ 否则，说明可以选 $1$，枚举前后两部分的断点 $i$，将 $l \sim i$ 第 $p$ 位选 $0$，$i+1 \sim r$ 选 $1$，转移到 $f_{l,r,p,0} = \max\{\max\{l-1,r-num+2^p-1\} \le i \le \min\{r,l+2^p-1\}\mid sum_r - sum_i + f_{l,i,p-1,1} + f_{i+1,r,p-1,[num-2^p+1=2^p-1]}\}$。

（其中 $sum$ 数组是 $a_i$ 的前缀和）

一些细节：

实际上并不用那么麻烦，因为我们传的是 $num$，每次开头判一下是 $f_{l,r,p,0}$ 还是 $f_{l,r,p,1}$ 就可以了。

稍微要处理一些边界。

式子对着代码更好理解。

时间复杂度应该是 $O (n^3 \log m)$，要吸氧。

很短啊。不到四十行。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 205;
int n;
ll m, a[N], f[N][N][65][2], sum[N];
ll dp(int l, int r, int p, ll num)
{
    int c = (num == (1ll << p + 1) - 1); // 0/1
    if (f[l][r][p][c] > -3e18) return f[l][r][p][c]; //记忆化
    if (l > r) return 0; // 边界1
    if (num == 0) return 0; // 边界2
    if (p == 0) // 边界3
    {
        if (l == r) return max(a[r], 0ll); // 选0/1
        else return a[r]; // 必须l选0,r选1
    }
    ll g = (1ll << p); // 实际意义: 2^p
    if (!(num & g)) return f[l][r][p][c] = dp(l, r, p - 1, num); // 第一种情况
    ll t = num - g + 1; // 实际意义: num 去掉第 p 位后 + 1 
    for (int i = max((ll)l - 1, r - t); i <= min((ll)r, l + g - 1); i++) // i 要满足的范围
        f[l][r][p][c] = max(f[l][r][p][c], sum[r] - sum[i] + dp(l, i, p - 1, g - 1)  + dp(i + 1, r, p - 1, t - 1)); // 第二种情况
    //                                                               ^^^                                   ^^^
    //                                                    2^p-1的上界 ^^^                  num后面几位的上界 ^^^
    return f[l][r][p][c];
}
int main()
{
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), sum[i] = sum[i - 1] + a[i]; // a 前缀和
    memset(f, 0xc0, sizeof(f)); // 极小值
    printf("%lld\n", dp(1, n, 62, m));
	return 0;
} 
```

---

## 作者：蒟蒻tyy (赞：1)

#### $\mathcal Description:$

$\quad\bullet$ 给定 $n,m$ 和 $n$ 个正整数 $a$。

$\quad\bullet$ 要求找到 $n$ 个正整数 $b$，使得 $\sum\limits_{i=1}^npopcount(b_i)a_i$ 最大化。

$\quad\bullet$ 其中 $0 \leq b_1 <b_2 < \cdot\cdot\cdot <b_m \leq m$。

#### $\mathcal Solution:$

$\quad\bullet$ 刚开始想了个贪心，结果显然假了。

$\quad\bullet$ 考虑动态规划，设 $f_{i,l,r}$ 代表处理区间 $[l,r]$ ，所有 $[l,r]$ 的 $b$ 数字在 $[0,2^i)$ 时的最大值。设  $s_i$ 代表前 $i$ 个 $a$ 数字的前缀和。可以得到转移：

$$
f_{i,l,r} = \max\{f_{i-1,l,k}+f_{i-1,k+1,r}+s_r-s_k\}
$$

$\quad\bullet$ 这个部分的时间复杂度为 $\mathcal O(n^3)$。

$\quad\bullet$ 考虑求解问题，设 $g_{dep,l,r}$ 代表区间 $[l,r]$ 的答案，其中 $[l,r]$ 位置的数字 $b$ 的二进制位的 $dep+1$ 即以上位已经计算完毕，并且卡着 $m$ 这个上界。还是可以得到转移。

$$
g_{dep,l,r} = \begin{cases}g_{dep-1,l,r}\quad if \quad (*)\quad  \\ \max\{f_{dep-1,l,k}+g_{dep-1,k+1,r}+s_r-s_{k}\}\end{cases}
$$

$\quad\bullet$ 其中 $(*)$ 代表 $m$ 的第 $dep$ 位二进制不为 $1$。

$\quad\bullet$ 按照这个方法计算即可。

---

## 作者：Feryquitous (赞：1)

不难看出是数位 dp。

多个小于关系，思考一下发现自低位向高位考虑更容易。

可以发现最高位会分为一段前缀为 $0$，剩余后缀为 $1$ 的形态。两段又分别是个子问题。

那么显然需要枚举这个分界点，然后从左右两个区间转移。是不是有点像区间 dp？

定义状态 $f_{i,l,r,0/1}$ 表示考虑到前 $i$ 位，区间为 $[l,r]$，当前位是否和 $m$ 这位相等的答案。

如果当前位与 $m$ 相等且 $m$ 这一位为 $0$，就无法累加贡献，那么：

$f_{i,l,r,1}=f_{i-1,l,r,1}$。

否则有状态转移方程：

$f_{i,l,r,0/1}=\max\limits_{k=l}^{r-1}(f_{i-1,l,k,0}+f_{i-1,k+1,r,0/1}+s_r-s_k)$，其中 $s$ 为 $a$ 数组的前缀和。

发现上面考虑不到只填一个数的情况，一种技巧是把 dp 数组里区间 $[l,l-1]$ 初值赋为 0，然后增加 $k$ 的枚举范围。

复杂度 $O(n^3\log m)$，吸氧可过。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=205;
int n,m,a[N],f[64][N][N][2];

main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];
    memset(f,-0x3f,sizeof(f));
    for(int i=1;i<=n;i++) f[0][i][i][0]=f[0][i][i][1]=0;
    for(int i=0;i<64;i++) for(int j=1;j<=n+1;j++) for(int k=0;k<2;k++) f[i][j][j-1][k]=0;
    for(int i=1;i<64;i++)
        for(int l=1;l<=n;l++)
            for(int r=l;r<=n;r++)
                for(int j=0;j<2;j++)
                    if(!(m&(1ll<<i-1))&&j) f[i][l][r][j]=f[i-1][l][r][j];
                    else for(int k=l-1;k<=r;k++) f[i][l][r][j]=max(f[i][l][r][j],f[i-1][l][k][0]+f[i-1][k+1][r][j]+a[r]-a[k]);
    cout<<f[63][1][n][1];
}
```

---

