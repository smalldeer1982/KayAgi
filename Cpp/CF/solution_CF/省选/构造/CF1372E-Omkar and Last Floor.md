# Omkar and Last Floor

## 题目描述

Omkar is building a house. He wants to decide how to make the floor plan for the last floor.

Omkar's floor starts out as $ n $ rows of $ m $ zeros ( $ 1       \le n,m \le 100 $ ). Every row is divided into intervals such that every $ 0 $ in the row is in exactly $ 1 $ interval. For every interval for every row, Omkar can change exactly one of the $ 0 $ s contained in that interval to a $ 1 $ . Omkar defines the quality of a floor as the sum of the squares of the sums of the values in each column, i. e. if the sum of the values in the $ i $ -th column is $ q_i $ , then the quality of the floor is $ \sum_{i = 1}^m q_i^2 $ .

Help Omkar find the maximum quality that the floor can have.

## 说明/提示

The given test case corresponds to the following diagram. Cells in the same row and have the same number are a part of the same interval.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1372E/e2f8400fab9b534d5d62160babde7e3b6dddc0b0.png)The most optimal assignment is:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1372E/2ddfdd398d9b8946cd6796d76ff01c94ae1b5237.png)The sum of the $ 1 $ st column is $ 4 $ , the sum of the $ 2 $ nd column is $ 2 $ , the sum of the $ 3 $ rd and $ 4 $ th columns are $ 0 $ , and the sum of the $ 5 $ th column is $ 4 $ .

The quality of this floor plan is $ 4^2 + 2^2 + 0^2 + 0^2 + 4^2       = 36 $ . You can show that there is no floor plan with a higher quality.

## 样例 #1

### 输入

```
4 5
2
1 2
3 5
2
1 3
4 5
3
1 1
2 4
5 5
3
1 1
2 2
3 5```

### 输出

```
36```

# 题解

## 作者：zac2010 (赞：10)

由于是取平方和，所以有明显的结论：一定存在一种最优方案，第 $1$ 列是全 $1$ 的。

这个结论看似没什么用，但却可以反应出如下性质：

> 定义“可取的位置”为：此时其所在区间还没有 $1$ 的位置。那么答案必定是按照
某个优先级从大到小，逐列把列上所有“可取的位置”都变为 $1$。

拿样例解释一下，它优先取第一列，发现当前所有包含了形如 $(i,1)$ 的区间都是全 $0$ 的，所以贡献为 $4^2$；其次是最后一列，发现贡献也是 $4^2$；接着是第二列，发现第 $3$ 行的第二个区间、第 $4$ 行的第二个区间是全 $0$ 的，贡献是 $2^2$；最后是剩下的 $3,4$ 两列，贡献都是 $0^2$。所以答案是 $4^2+4^2+2^2+0^2+0^2$。

会发现上述性质反证法可得。

考虑使用区间 $\text{DP}$。$f_{l,r}$：满足 $l \leq l' \leq r' \leq r$ 的所有区间 $[l',r']$ 能得到的最大贡献；再钦定 $c_{l,r,i}$ 为：满足 $l \leq l' \leq i \leq r' \leq r$ 的区间对 $[l', r']$ 的个数。

转移显然，枚举 $[l,r]$ 中优先级最高的点 $i$：
$$
f_{l,r} \gets f_{l,i-1}+f_{i+1,r}+c_{l,r,i}
$$

但是现在还存在一个问题：没有完全被 $[l,r]$ 覆盖的区间是否可能对 $i$ 产生贡献？

其实不然。当我们转移到一个区间时，端点处要不是边界，就是优先级比它高的点。所以不存在这种情况。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 110;
int n, m, f[N][N], c[N][N][N];
int main(){
	scanf("%d%d", &n, &m);
	FL(i, 1, n){
		int len, l, r; scanf("%d", &len);
		FL(j, 1, len){
			scanf("%d%d", &l, &r);
			FL(k, l, r) c[l][r][k]++;
		}
	}
	FL(len, 1, m) FL(l, 1, m - len + 1){
		int r = l + len - 1;
		FL(i, l, r){
			c[l][r][i] += c[l + 1][r][i] + c[l][r - 1][i] - c[l + 1][r - 1][i];
			f[l][r] = max(f[l][r], f[l][i - 1] + f[i + 1][r] + c[l][r][i] * c[l][r][i]);
		}
	}
	printf("%d\n", f[1][m]);
	return 0;
}
```


---

## 作者：do_while_true (赞：9)

orz qyc

看很多写法都是 $\mathcal{O}(n^4)$ 的，其实稍微预处理下就能做到 $\mathcal{O}(n^3)$ 的了。

~~并不那么~~显然地看出是个区间 dp，后面就很好做了。

发现平方聚在一起是更优的，则区间 dp 应该是枚举一列让它尽可能的多选。

基于这个贪心的思路，设 $f_{l,r}$ 为仅考虑左右端点均在 $[l,r]$ 内的段的答案，转移就枚举哪一行是尽可能填的。设 $s_{k,l,r}$ 为代表左右端点都在 $[l,r]$ 内且经过 $k$ 列的区间个数。

枚举尽可能多选的那一列是第 $k$ 列，则有：

$$
f_{l,r}=\max\{f_{l,k-1}+{s_{k,l,r}}^2+f_{k+1,r}\}
$$

然后考虑怎样算 $s$。

对于给出的一个段 $x,y$，实际上是对所有的 $l\leq x,r\geq y,x\leq k\leq y$，$s_{k,l,r}$ 都加上 $1$。

也许读者注意到一个细节，$s$ 的状态设计中，我将 $k$ 放在第一维，实际上是方便对 $\mathcal{O}(n^3)$ 预处理 $s$ 作铺垫。考虑对每个 $k$ 建立一个平面直角坐标系，横坐标为 $l$，纵坐标为 $r$，$(l,r)$ 上的值为 $s_{k,l,r}$。

那么所有满足 $l\leq x,r\geq y$ 的 $(l,r)$，构成了一个左上角上的矩形，矩形加最后单点查，可以二维差分解决。

但实际上都是左上角的矩形，在 $(l,r)$ 打个 tag 然后做二维前缀和就完全足够。

时间复杂度 $\mathcal{O(n^3)}$．

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long ll;
const ll mod = 1000000007;
template <typename T> T Add(T x, T y) { return (x + y >= mod) ? (x + y - mod) : (x + y); }
template <typename T> T cAdd(T x, T y) { return x = (x + y >= mod) ? (x + y - mod) : (x + y); }
template <typename T> T Mul(T x, T y) { return x * y % mod; }
template <typename T> T Mod(T x) { return x < 0 ? (x + mod) : x; }
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T> T Abs(T x) { return x < 0 ? -x : x; }
template <typename T> T chkmax(T &x, T y) { return x = x > y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r <<1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
ll qpow(ll x, ll y) {
	ll sumq = 1;
	while(y) {
		if(y & 1) sumq = sumq * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return sumq;
}
const int N = 110;
int n, m;
int len[N], f[N][N], s[N][N][N];
signed main() { //freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
	read(n); read(m);
	for(int i = 1; i <= n; ++i) {
		read(len[i]);
		for(int j = 1; j <= len[i]; ++j) {
			int x, y; read(x); read(y);
			for(int k = x; k <= y; ++k)
				++s[k][x][y];
		}
	}
	for(int k = 1; k <= m; ++k) {
		for(int l = m; l; --l)
			for(int r = 1; r <= m; ++r)
				s[k][l][r] += s[k][l][r-1];
		for(int l = m; l; --l)
			for(int r = 1; r <= m; ++r)
				s[k][l][r] += s[k][l+1][r];
	}
	for(int k = 1; k <= m; ++k) f[k][k] = s[k][k][k] * s[k][k][k];
	for(int len = 1; len < m; ++len)
		for(int i = 1; i + len <= m; ++i) {
			int j = i + len;
			for(int k = i; k <= j; ++k) f[i][j] = Max(f[i][j], f[i][k-1] + s[k][i][j] * s[k][i][j] + f[k+1][j]);
		}
	printf("%d\n", f[1][m]);
	return 0;
}
```

---

## 作者：Masterwei (赞：6)

挺妙的，主要是根据性质联想到区间 dp。

首先发现 $1$ 的个数之和是不变的。然后手玩一下发现组成的最大值越大越好。

考虑区间 dp，设 $f_{l,r}$ 表示用被 $[l,r]$ 包含的段中的 $1$，构成的最大权值是多少。

考虑转移：$f_{l,r}=\max(f_{l,k-1}+f_{k+1,r}+cost(l,r,k))$ 或者 $f_{l,r}=\max(f_{l,k-1}+f_{k,r})$。

$cost(l,r,k)$ 表示的是在 $k$ 点，用被 $[l,r]$ 包含的段，能获得的最大 $1$ 的个数的平方。暴力算时间复杂度是 $O(n)$ 的。

总时间复杂度为 $O(m^3 n)$，可以优化，但没有必要。

---

## 作者：ty_mxzhn (赞：3)

好题啊。

根据贪心，**一定可以找到一个位置，使得跨过这个位置的段全都会选这里**。证明考虑假设不选这个位置，一定可以调整。

设计 $f_{i,j}$ 表示只考虑在 $[i,j]$ 这个区间内的段的权值最大值。转移时枚举一个位置 $k$，让跨过 $k$ 的段全部选 $k$。

具体的转移式子是 $\displaystyle f_{i,j}=\max_{k=i}^j f_{i,k-1}+S_{i,j,k}+f_{k+1,j}$。

其中 $S_{i,j,k}$ 表示在 $[i,j]$ 这个区间内的段有多少个经过 $k$。$S_{i,j,k}$ 显然可以用前缀和 $O(m^3)$ 预处理。

于是直接写出转移，时间复杂度 $O(m^3+nm)$。

代码不放了。

---

## 作者：daniEl_lElE (赞：3)

首先观察得出，和一定时，想要 $q_i^2$ 尽可能大，一定会按顺序去最大化若干个 $q_i$。

注意到当最大化某个位置后，这个位置两边将互不影响。

考虑区间 dp，设 $dp_{l,r}$ 表示 $[l,r]$ 区间内放置 $q_i$，$\sum_{i=l}^rq_i^2$ 的最大值。注意到我们是按所说的钦定顺序反向 dp，故所有不完全被 $[l,r]$ 包含的区间一定不会放置 $1$ 在 $[l,r]$ 区间中。

考虑转移，$dp_{l,r}\leftarrow dp_{l,k-1}+dp_{k+1,r}+(\sum_{i=1}^n[l\leq posl_{i,k}\leq posr_{i,k}\leq r])^2$，其中 $posl_{i,k},posr_{i,k}$ 表示 $i$ 行第 $k$ 个所在的区间的左端点和右端点。

总复杂度 $O(m^3n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int tol[105][105],tor[105][105];
int dp[105][105];
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++){
		int k; cin>>k;
		for(int j=1;j<=k;j++){
			int l,r; cin>>l>>r;
			for(int p=l;p<=r;p++) tol[i][p]=l,tor[i][p]=r;
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++) dp[i][i]+=(tol[j][i]==i)&(tor[j][i]==i);
		dp[i][i]*=dp[i][i];
	}
	for(int len=2;len<=m;len++){
		for(int l=1,r=len;r<=m;l++,r++){
			for(int k=l;k<=r;k++){
				int cnt=0;
				for(int p=1;p<=n;p++) cnt+=(l<=tol[p][k])&(tor[p][k]<=r);
				dp[l][r]=max(dp[l][r],dp[l][k-1]+dp[k+1][r]+cnt*cnt);
			}
		}
	}
	cout<<dp[1][m];
	return 0;
}
```

---

## 作者：crashed (赞：3)

**去往[原博客](https://www.cnblogs.com/crashed/p/13766487.html)食用更佳。**

# 题目

[点这里](https://www.luogu.com.cn/problem/CF1372E)看题目。

# 分析

~~好妙的题！~~

初看起来无从下手（我最初一直想着要分行依次叠加贡献），这样的话，我们不妨来看一下，第一步应该怎么计算贡献。

面对区间 $[1,m]$，一种方法是**首先选出一列 $k$**，然后**最大化这一列上的和**——显然就是 $n$。接着，所有经过了 $k$ 的区间都不能再用了。那么问题自然地被划分成了 $[1,k-1]$ 和 $[k+1,m]$ 两个**独立的**子问题。

这提醒了我们，可以使用区间 DP。可以考虑定义状态为：

$f(i,j)$：左右端点都在 $[i,j]$ 内的区间的最大贡献和。

转移比较显然。记 $S(i,j,k)$ 为所有的左右端点都在 $[i,j]$ 中，且经过了 $k$ 这个位置的区间数量。那么就有转移：

$$
f(i,j)=\max\{f(i,k-1)+f(k+1,j)+(S(i,j,k))^2|i\le k\le j\}
$$

这里的 $S$ 理论上来说，可以直接 $O(n^3)$ 地预处理出来（高位前缀和）。~~实际上直接 $O(n^4)$ 也无伤大雅。~~

总时间复杂度就是 $O(n^3)\sim O(n^4)$。

# 代码

```cpp
#include <cstdio>

const int INF = 0x3f3f3f3f;
const int MAXN = 105;

template<typename _T>
void read( _T &x )
{
    x = 0; char s = getchar(); int f = 1;
    while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
    while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ); s = getchar(); }
    x *= f;
}

template<typename _T>
void write( _T x )
{
    if( x < 0 ) putchar( '-' ), x = -x;
    if( 9 < x ) write( x / 10 );
    putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
    return a > b ? a : b;
}

int f[MAXN][MAXN];
int su[MAXN][MAXN][MAXN];

int N, M;

int main()
{
    read( N ), read( M );
    for( int i = 1 ; i <= N ; i ++ )
    {
        int K, l, r;
        read( K );
        while( K -- )
        {
            read( l ), read( r );
            for( int a = 1 ; a <= l ; a ++ )
                for( int b = r ; b <= M ; b ++ )
                    su[a][b][l] ++, su[a][b][r + 1] --;
        }
    }
    for( int i = 1 ; i <= M ; i ++ )
        for( int j = i + 1 ; j <= M ; j ++ )
            for( int k = i ; k <= j ; k ++ )
                su[i][j][k] += su[i][j][k - 1];
    for( int i = M ; i ; i -- )
    {
        f[i][i + 1] = -INF;
        for( int j = i ; j <= M ; j ++ )
            for( int k = i ; k <= j ; k ++ )
                f[i][j] = MAX( f[i][j], f[i][k - 1] + f[k + 1][j] + su[i][j][k] * su[i][j][k] );
    }
    write( f[1][M] ), putchar( '\n' );
    return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：1)

给出一种最为好写好想、实现细节最少的写法。

**题意**

给你一个 $N \times M$ 的矩阵，其中每行被分隔成若干个区间。你需要在矩阵中填 $1$ 或 $0$，一个区间只能有 $1$ 个 $1$。现在你需要让每一列的 $1$ 的数量的平方和最大。求出这个值。

**分析**

$N,M \le 100$ 非常像是区间 dp 这种较高维 dp 的复杂度对应的数据范围。

一个应该想到的性质：我们应该尽可能让 $1$ 在一列摞起来。这样，平方和更大。事实上，样例就是一个很好的例子。那我们的状态可以定义为：

$dp_{i,j}$ 代表在横坐标 $[i,j]$，纵坐标 $[1,N]$ 的子矩阵内，最大列平方和。

枚举 $k \in [i,j]$。因为我们要让 $1$ 集中来加大平方和，因此我们要求 **所有左右端点均在 $[l,r]$ 内且经过 $k$ 的区间，都把 $1$ 放在 $k$ 上。** 之后，答案就是


$$dp_{i,j}= dp_{i,k-1}+cov_{i,j,k}+dp_{k+1,j}$$



答案即可求出。容易发现，这里的时间复杂度是 $O(N^3)$ （我们认为 $N,M$ 相同）。

如何求出 $cov_{i,j,k}$？目前题解区有 $2$ 种解法：二维差分与前缀和、开 $l,r$ 数组存端点等方法。它们的时间复杂度分别是 $O(N^3)-O(N^3)$、$O(N^3)-O(N^4)$（破折号前是预处理复杂度，后面是 dp 复杂度）。

但是其实可以直接在输入时直接预处理。对于输入的区间 $[la,ra]$，枚举所有 $lb \in [1,la],rb \in [ra,M],k \in [la,ra]$。之后把 $cov_{lb,rb,k}$ 更新即可。对于单个区间，它实现了最劣 $O(N^3)$ 的预处理。一共有 $N^2$ 量级的区间，但因为所有 $k$ 之和一定 $=N^2$，所以复杂度是 $O(N^4)$ 而不是 $O(N^5)$。

这样实现了 $O(N^4)-O(N^3)$ 的解法，可以通过本题。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=505,MOD=998244353;
int N,M;
LL cov[105][105][105];
LL dp[105][105];
int main()
{
    scanf("%d %d",&N,&M);
    for(int i=1;i<=N;i++)
    {
		int t;
		scanf("%d",&t);
		for(int j=1;j<=t;j++)
		{
			int la,ra;
			scanf("%d %d",&la,&ra);
			for(int lb=la;lb;lb--)
				for(int rb=ra;rb<=M;rb++)
					for(int k=la;k<=ra;k++)
						cov[lb][rb][k]++;
		}
	}
	for(int i=1;i<=M;i++) dp[i][i]=cov[i][i][i]*cov[i][i][i];
	for(int i=1;i<=M;i++) dp[i][i-1]=0;
	for(int len=2;len<=M;len++)
	{
		for(int l=1;l+len-1<=M;l++)
		{
			int r=l+len-1;
			for(int i=l;i<=r;i++)
			{
				dp[l][r]=max(dp[l][r],cov[l][r][i]*cov[l][r][i]+dp[l][i-1]+dp[i+1][r]);
			}
		}
	}
	printf("%lld\n",dp[1][M]);
    return 0;
}
```


---

## 作者：45dino (赞：1)

题目大意：一个 $n\times m$ 的矩阵，初始值全为 $0$ ，每一行都被分成若干部分，每一部分只能出现一个 $1$ ，设 $q_i$ 为第 $i$ 列 $1$ 的个数，求 $\sum_{i=1}^mq_i^2$ 的最大值。

一个比较裸的区间DP。设 $dp_{l,r}$ 表示 $\sum_{i=l}^rq_i^2$ 的最大值，对于 $dp_{l,r}$ ，枚举 $k$ ，如果第 $k$ 列最多能有 $a$ 个 $1$ ，则
$$dp_{l,r}=max(dp_{l,r},dp_{l,k-1}+a^2+dp_{k+1,r})$$
然后代码就显而易见了。

喜闻乐见的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,dp[101][101],lef[101][101],rig[101][101];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		while(k--)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			for(int j=l;j<=r;j++)
			{
				lef[i][j]=l;
				rig[i][j]=r;
			}	
		}	
	}	
	for(int i=m;i>=1;i--)
		for(int l=i;l<=m;l++)
			for(int k=i;k<=l;k++)
			{
				int a=0;
				for(int j=1;j<=n;j++)
					if(lef[j][k]>=i&&rig[j][k]<=l)
						a++;
				dp[i][l]=max(dp[i][l],dp[i][k-1]+a*a+dp[k+1][l]);
			}
	cout<<dp[1][m];
	return 0;
} 
```


---

## 作者：Purslane (赞：0)

# Solution

群里看到的题，感觉困难。

考虑所有**完全包含在 $[i,j]$ 中的行散块**，一定存在一个位置 $p$ 使得**所有包含 $p$ 的行散块的 $1$ 都集中在其中**。

> 这一部分考虑直接调整，找到所有列中包含 $1$ 个数最多的列，其他都得向他调整。

直接模拟即可，复杂度 $O(n^4)$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10;
int n,m,ll[MAXN][MAXN],rr[MAXN][MAXN],dp[MAXN][MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) {
		int cnt;
		cin>>cnt;
		ffor(j,1,cnt) {
			int L,R;
			cin>>L>>R;
			ffor(t,L,R) ll[i][t]=L,rr[i][t]=R;
		}
	}
	ffor(len,1,m) for(int l=1,r=len;r<=m;l++,r++) {
		ffor(p,l,r) {
			int cnt=0;
			ffor(j,1,n) if(l<=ll[j][p]&&rr[j][p]<=r) cnt++;
			dp[l][r]=max(dp[l][r],cnt*cnt+dp[l][p-1]+dp[p+1][r]);
		}
	}
	cout<<dp[1][m];
	return 0;
}
```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1372E)

&nbsp;

### 题目大意：

给定一个 $n \times m$ 的矩阵，将其每行划分为多个部分，每一部分中需要填上 $1$ 个 $1$，设第 $i$ 列有 $a_i$ 个 $1$，求 $\sum\limits_{i=1}^m{a_i^2}$ 的最大值。 

&nbsp;

### 解题思路：

不难发现的是，肯定会有一列被放置了 $n$ 个 $1$，可以简单的证明一下。假设我们现在有两列 $1$，一列有 $x$ 个，另一列则有 $x-2$ 个，比较 $x^2+(x-2)^2$ 与 $(x-1)^2\times 2$ 的大小，$x^2=(x-1)^2+x-1+x$，$(x-1)^2=(x-2)^2+x-2+x-1$，两个式子做差可以得到 $2$，显然 $x^2+(x-2)^2$ 更大。

我们设放置了 $n$ 个 $1$ 的为第 $k$ 列，则问题之和显然为  $n^2$ $+$ 区间 $[1,k-1]$ 和 $[k+1,m]$ 中的最大答案。而对于每个区间，显然也可以重复刚才的步骤，找到一列把空余的位置放满，然后再次分为左右两个区间求解。

那么根据刚才的描述不难发现，对于一个区间 $[l,r]$，假设我们优先放置第 $x$ 列，且区间 $[l_i,r_i]$ 未被放置且能放置在第 $x$ 列，则其一定满足 $l\leq l_i\leq x\leq r_i\leq r$。

于是可以设一个 `dp` 状态为 $dp[i][j]$，代表左右端点都在 $[i,j]$ 之间的区间能做出的最大贡献，同时记一个数组 $c[i][j][k]$ 代表左右端点在 $[i,j]$ 之间，且经过 $k$ 的区间个数，转移方程如下：

$$dp[i][j]=\max(dp[i][j],dp[i][k-1]+dp[k+1][j]+c[i][j][k]^2)$$

代码如下：
```cpp
int main(){
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++){
		int p;
		scanf("%d",&p);
		
		for(int j=1;j<=p;j++){
			int l,r;
			scanf("%d%d",&l,&r);
			for(int k=l;k<=r;k++){
				cnt[l][r][k]++;
			}
		}
	}
	
	for(int l=1;l<=m;l++){
		for(int i=1;i+l-1<=m;i++){
			int j=i+l-1;
			for(int k=i;k<=j;k++){
				cnt[i][j][k]+=cnt[i+1][j][k]+cnt[i][j-1][k]-cnt[i+1][j-1][k];
				dp[i][j]=max(dp[i][j],dp[i][k-1]+dp[k+1][j]+cnt[i][j][k]*cnt[i][j][k]);
			}
		}
	}
	
	printf("%lld",dp[1][m]);
	return 0;
}

```
完结撒花 OvO！！！

---

## 作者：7KByte (赞：0)

非常巧妙的区间DP思维题。

按照套路定义状态$f[l][r]$。表示$[l,r]$区间的最大贡献。

但是很快可以发现根本写不出转移方程。

观察下每块地板$[l,r]$，一定在$[l,r]$中有一个$1$，假设$1$的位置在$k$。

那么对于区间$[l,r]$中左右端点都在$[l,r]$中的地板，枚举一个$k$，地板分为两类。

一类是经过第$k$列，另一类是不经过第$k$列。

这样我们可以设计状态$f[l][r]$表示$[l,r]$中左右端点都在$[l,r]$之间的地板的最大贡献。

显然答案为$f[1][m]$。

如果能想到这一步，答案就出来了，转移方程$:$

$$f[l][r]=\max\limits_{l\le k\le r}\{f[l][k-1]+f[k+1][r]+S_{k,l,r}^2\}$$


其中$S_{k,l,r}$指经过第$k$列，左右端点在$[l,r]$之间的地板个数。


```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 105
using namespace std;
int f[N][N],L[N][N],R[N][N],n,m;
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n){
		int x;scanf("%d",&x);
		rep(op,1,x){
			int l,r;scanf("%d%d",&l,&r);
			rep(j,l,r)L[j][i]=l,R[j][i]=r;
		}
	}
	//rep(i,1,n){rep(j,1,m)printf("%d ",L[j][i]);putchar('\n');}
	//rep(i,1,n){rep(j,1,m)printf("%d ",R[j][i]);putchar('\n');}
	rep(len,1,m){
		rep(l,1,m-len+1){
			int r=l+len-1;
			//cout<<l<<" "<<r<<endl;
			rep(k,l,r){
				int sum=0;
				rep(w,1,n)sum+=(L[k][w]>=l&&R[k][w]<=r);
				f[l][r]=max(f[l][r],f[l][k-1]+f[k+1][r]+sum*sum);
			}
		}
	}
	printf("%d\n",f[1][m]);
	return 0;
}
```

小结：

这道题需要一定的技巧，其中最关键的一部是状态的设计。本题只要正确设计出状态，就能够解决了。

---

