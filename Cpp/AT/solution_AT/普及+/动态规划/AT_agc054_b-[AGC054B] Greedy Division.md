# [AGC054B] Greedy Division

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc054/tasks/agc054_b

みかんが $ N $ 個あり，$ 1 $ から $ N $ までの番号がついています． みかん $ i $ の重さは $ W_i $ です． 高橋くんと青木くんがこれらを以下のようにして分けます．

- $ (1,2,\cdots,N) $ の順列 $ (p_1,\ p_2,\ \cdots,\ p_N) $ を選ぶ．
- $ i\ =\ 1,\ 2,\ \cdots,\ N $ について，この順に以下のことを行う
  
  
  - 高橋くんがすでにとったみかんの重さの合計が，青木くんがすでにとったみかんの重さの合計以下なら，みかん $ p_i $ を高橋くんがとる． そうでないならみかん $ p_i $ を青木くんが取る．

最終的に二人が取るみかんの重さの合計が等しくなるような順列 $ p $ が何通りあるかを $ 998244353 $ で割った余りを求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ W_i\ \leq\ 100 $
- 入力される値はすべて整数

### Sample Explanation 1

条件を満たす $ p $ は，$ (1,3,2),(2,3,1),(3,1,2),(3,2,1) $ の $ 4 $ 通りです． 例えば，$ p=(3,2,1) $ の時は，以下のように進行します． - $ i=1 $: 高橋くんがすでにとったみかんの重さの合計は $ 0 $ で，青木くんがすでにとったみかんの重さの合計は $ 0 $ である． 高橋くんがみかん $ p_i=3 $ をとる． - $ i=2 $: 高橋くんがすでにとったみかんの重さの合計は $ 2 $ で，青木くんがすでにとったみかんの重さの合計は $ 0 $ である． 青木くんがみかん $ p_i=2 $ をとる． - $ i=3 $: 高橋くんがすでにとったみかんの重さの合計は $ 2 $ で，青木くんがすでにとったみかんの重さの合計は $ 1 $ である． 青木くんがみかん $ p_i=1 $ をとる． よって $ p=(3,2,1) $ は条件を満たす順列です．

## 样例 #1

### 输入

```
3
1 1 2```

### 输出

```
4```

## 样例 #2

### 输入

```
4
1 2 3 8```

### 输出

```
0```

## 样例 #3

### 输入

```
20
2 8 4 7 5 3 1 2 4 1 2 5 4 3 3 8 1 7 8 2```

### 输出

```
373835282```

# 题解

## 作者：gxp123 (赞：2)

# agc054 B - Greedy Division 题解

## 题意

有 $n(2\le n\le100)$ 个数，每个数有一个权值 $a_i(1\le a_i\le 100)$。现在对于一个排列 $p$，有两个人 $A$ 和 $B$ 会做如下操作：

- 对于 $1\sim n$ 从小到大的每个 $i$，如果 $A$ 手上数的权值和不大于 $B$ 的，那么 $A$ 拿走第 $p_i$ 个数，否则 $B$ 拿走。

问有多少个排列使得 $A$ 和 $B$ 最终手上的数的权值和一样。

答案对 $998244353$ 取模。

## 题解

这个题的破题点就是一个性质：

**假设你知道了 $A,B$ 的取数的顺序（合法的顺序），则总的数列的顺序是唯一的。**

> 证明：
>
> 设 $A$ 取数的顺序是 $p_1,p_2,...,p_s$，$B$ 取数的顺序是 $q_1,q_2,...,q_t$。
>
> 则显然，第一个数必然是 $p_1$（因为当前 $sumA = sumB = 0$）。
>
> 第二个数必然是 $q_1$（因为当前 $sumA = p_1 \ge 1>0=sumB$）。
>
> 而后面谁先谁后由 $sumA,sumB$ 的大小关系确定。
>
> 而 $A,B$ 取数的顺序又是一定。
>
> 所以假设知道了 $A,B$ 取数的顺序，则总的数列的顺序是唯一的。

直到了这个性质这个题就十分好做。

如果 $\sum\limits_{i = 1}^{n} a_i$ 是奇数，则一定无解（因为你没办法均分）。

假设我们已经直到了 $A$ 的选择数的集合，且 $A$ 当前选了 $k$ 个数。

则 $B$ 选的数字就是已知的了，且 $B$ 选了 $n - k$ 个数。

所以当前情况方案的贡献就是 $k!(n - k)!$，$x!$ 表示 $x$ 的阶乘。

于是我们就只关心 $A$ 的选择数的集合和选择的数的个数。

我们设 $f_{i,j,k}$ 表示前 $i$ 个，选了 $j$ 个数，总和为 $k$ 的方案数。

转移就是：

$$
f_{i,j,k} = f_{i - 1,j,k} + (f_{i - 1,j - 1,k - A_i})
$$

后面的一项需要满足：$j > 0 $ 并且 $ k \ge a_i$。

记 $sumh = \sum\limits_{i = 1}^{n} a_i$；

则答案就是：
$$
\sum\limits_{k = 1}^{n} f_{n,k,\frac{sumh}{2}}\times k!\times(n - k) !
$$
因为 $i$ 的这一维只和 $i - 1$ 有关，则我们可以滚动数组优化掉一维空间。

时间复杂度：$O(n^4)$。

## code

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxN = 100 + 10;
const int mod = 998244353;
int f[2][maxN][maxN * maxN];
int n,a[maxN],jc[maxN];

int main(){
    scanf("%d",&n);
    int sumh = 0;
    jc[0] = 1;
    for(int i = 1 ; i <= n ; ++i){
        scanf("%d",a + i);
        sumh += a[i];
        jc[i] = 1ll * jc[i - 1] * i % mod;
    }
    if(sumh & 1){
        puts("0");
        return 0;
    }
    sumh = sumh >> 1;
    f[0][0][0] = 1;
    for(int i = 1,op,opt ; i <= n ; ++i){
        op = i & 1;
        opt = op ^ 1;
        for(int j = 0 ; j <= i ; ++j){
            for(int k = 0 ; k <= sumh ; ++k){
                f[op][j][k] = f[opt][j][k];
                if(j > 0 && k >= a[i])
                    f[op][j][k] = (f[op][j][k] + f[opt][j - 1][k - a[i]]) % mod;
            }
        }
    }
    long long ans = 0;
    int op = n & 1;
    for(int i = 1 ; i <= n ; ++i){
        ans = (1ll * jc[i] * jc[n - i] % mod * f[op][i][sumh] % mod + ans) % mod;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：WaterSun (赞：2)

# 思路

首先不难发现一个规律，当 $sum$ 为奇数时不可能有解。

定义 $dp_{i,j,k,0/1}$ 表示 A 在前 $i$ 个数中选出和为 $j$ 的 $k$ 个数，且第 $i$ 个 不选/选 的方案数。

那么，我们只需要对于第 $i$ 个数的状态分类讨论就能得到状态转移方程：

1. 不选 $i$，$dp_{i,j,k,0} = dp_{i - 1,j,k,0/1}$。

2. 选 $i$，$dp_{i,j,k,1} = dp_{i - 1,j - a_i,k - 1,0/1}$。

综上，得到状态转移方程：

$$
\left\{\begin{matrix}
dp_{i,j,k,0} = dp_{i - 1,j,k,0/1}\\
dp_{i,j,k,1} = dp_{i - 1,j - a_i,k - 1,0/1}
\end{matrix}\right.
$$

然后，我们就得到了序列 $a$ 固定时的答案。那么，我们还要考虑一下 $a$ 不固定的情况。

假设 A 最后取出了 $x$ 个数，那么，我们就可以就可以对 A 和 B 两人选取数的序列进行全排列，即 $(x!)((n - i)!)$。

现在还有一个问题，为什么不能直接对 $a$ 进行全排列，也就是直接乘 $n!$。那是因为如果 A 和 B 两人选取的序列是固定的，由于题目中的条件当前权值小的人才能取数，所以说当两人选取数字的序列固定了，那么，拼起来的序列 $a$ 也是固定的。

综上，答案为 $\sum_{i = 1}^{n - 1}(dp_{n,\frac{sum}{2},i,0/1} \times (i!) \times ((n - i)!))$。

这样就可以得到 [MLE 1 个点](https://www.luogu.com.cn/paste/qw8gkrc0) 的代码。

然后，我们发现 $dp_i$ 时的所有状态都是由 $dp_{i - 1}$ 转移来的，所以说直接滚动一下即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 110,M = 1e4 + 10,mod = 998244353;
int n,r,sum,ans;
int arr[N],mul[N];
int dp[2][M][N][2];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void init(){
	mul[0] = 1;
	for (re int i = 1;i <= n;i++) mul[i] = mul[i - 1] * i % mod;
}

signed main(){
	n = read();
	init();
	for (re int i = 1;i <= n;i++){
		arr[i] = read();
		sum += arr[i];
	}
	if (sum & 1){
		puts("0");
		return 0;
	}
	dp[0][0][0][0] = dp[0][arr[1]][1][1] = 1;
	for (re int i = 2;i <= n;i++){
		r ^= 1;
		for (re int j = 0;j <= sum;j++){
			for (re int k = 0;k <= i;k++) dp[r][j][k][0] = dp[r][j][k][1] = 0;
		}
		for (re int j = 0;j <= sum;j++){
			for (re int k = 0;k <= i;k++){
				dp[r][j][k][0] = (dp[r ^ 1][j][k][0] + dp[r ^ 1][j][k][1]) % mod;
				if (j >= arr[i]) dp[r][j][k][1] = (dp[r ^ 1][j - arr[i]][k - 1][0] + dp[r ^ 1][j - arr[i]][k - 1][1]) % mod;
			}
		}
	}
	for (re int i = 1;i < n;i++) ans = (ans + (dp[r][sum / 2][i][0] + dp[r][sum / 2][i][1]) % mod * mul[i] % mod * mul[n - i] % mod) % mod;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：small_turtle (赞：1)

直接对排列计数非常困难。我们希望能够找到一个桥梁，能够将排列个数和一个更好算的东西连接起来。假设 $A$ 依次选择的卡牌是 $t_1,t_2\dots,t_k$，$B$ 依次选择的是 $g_1,g_2\dots,g_{n-k}$。第一步肯定是选择 $t_1$。第二步必然选择 $g_1$。接着看 $A$ 的权值和大，还是 $B$ 的权值和大，从而决定是选择 $t$ 还是选择 $g$。会发现这样选取的方案数是唯一的。可以发现，固定了卡排堆 $g$ 和 $t$，则选取方案唯一。因此我们称：排列 $P$ 和分发卡牌的情况总数构成双射关系。问题可以转化为从一堆数中选一些数使得和为 $\frac{S}{2}$。考虑使用动态规划解决该问题。设当前选到了第 $i$ 个正整数，总共选了 $j$ 个正整数，当前所有选的数的和为 $k$ 的方案数。使用背包+滚动数组即可。最后每一种方案，假设选了 $a$ 个正整数，则还需要额外乘上 $a!(n-a)!$。因为在动态规划过程中未考虑到选数的顺序。然后当心溢出即可。

```cpp
//Time:2023.3.13
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define unordered_map map
const ll inf=0x3f3f3f3f,mod=998244353;
const double eps=1e-6;
using namespace std;

ll n,s,ans,a[105],f[105][10005];
ll fac[105];

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	scanf("%lld", &n);
	fac[0]=1;
	for(int i=1;i<=n;++i)
	{
		scanf("%lld", &a[i]);
		s+=a[i];
		fac[i]=(fac[i-1]*i)%mod;//
	}
	if(s&1)//奇数不可能平分
	{
		puts("0");
		return 0;
	}

	s/=2;
	f[0][0]=1;
	for(int i=1;i<=n;++i)
	{
		for(int j=n;j;--j)
		{
			for(int k=s;k>=a[i];--k)
			{
				f[j][k]=(f[j-1][k-a[i]]+f[j][k])%mod;
			}
		}
	}
	
	for(int i=1;i<=n;++i)
	{
		ans+=(fac[i]*fac[n-i]*f[i][s])%mod;
		ans%=mod;
	}
	printf("%lld", ans%mod);
	return 0;
}

```
最后是一道与此题有点相似的题[P1466[USACO2.2]集合 Subset Sums](https://www.luogu.com.cn/problem/P1466)。

---

## 作者：highkj (赞：1)

# 前言
这是某个同学让我给他讲的题目，结果他过来竟是为了看旁边一位同学玩游戏，然后我们过了这道题之后发现那位玩游戏的同学早就通过一些特殊方法过了这道题。

话说那个水太阳的题解是不是写复杂了一点。
# 思路
一眼 Dp，我们定义 $f_{i,j,k}$ 前 $i$ 个数选出 $j$ 个和为 $k$ 的方案数，这里因为我们前 $i$ 个数一定要选所以知道了 B 选出的和。

那么我们的状态转移方程就位 $f_{i,j,k}=f_{i-1,j,k}+f_{i-1,j-1,k-a_i}$ 这里就是分要它和不要它的这里我们分成两循环处理。

最后的答案就位 $f_{n,i,sum\div2}$ 因为可以排列组合所以还要乘上 $i$ 和 $n-i$ 的阶乘。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void read(int &x) {
	x=false;
	ri f=1;
	char c=getchar();
	while(c>'9'||c<'0') {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c-'0'<=9&&c>='0') {
		x=x*10+c-'0';
		c=getchar();
	}
	x*=f;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
const int N=110,mod=998244353;
int f[N][N][N*N];
int n,a[N],s;
int sbzhuang[N];
void init() {
	sbzhuang[0]=1;
	rep(i,1,n) sbzhuang[i]=sbzhuang[i-1]*i%mod;
}
fire main() {
	cin>>n;
	init();
	rep(i,1,n) cin>>a[i],s+=a[i];
	if(s&1) {
		return cout<<0<<endl,0;
	}
	f[0][0][0]=1;
	rep(i,1,n) {
		rep(j,0,i) {
			rep(k,a[i],s) {
				if(j>=1) (f[i][j][k]+=f[i-1][j-1][k-a[i]])%=mod;
			}
			rep(k,0,s) f[i][j][k]=(f[i][j][k]+f[i-1][j][k])%mod;
		}
	}
	int res=0;
	rep(i,1,n) (res+=(f[n][i][s/2])*sbzhuang[i]%mod*sbzhuang[n-i]%mod)%=mod;
	cout<<res;
	return false;
}

```

---

## 作者：卷王 (赞：1)

## 题目大意

略。

## 大体思路

这题的一个重要结论就是：每一个排列 $p$ 和操作都是一一对应的，这就是所谓的 **双射关系**。

发现了这个结论这题就解决了一大半了。

剩下的就是典型的背包+滚动数组了，dp 的具体过程可以看代码里的注释。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pr;
const int mod = 998244353;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int _,n,a[107],sum,ans;
int dp[107][5007];
int fac[107];
//dp[i][j][k] 表示到了第 i 个数，选了 j 个数，和为 k 的方案数
//发现 dp[i][j][k] 只和 dp[i-1][j][k] 有关系，于是滚动第一维
//dp[j][k] 表示选了 j 个数，和为 k 的方案数
//我们需要求的是，和为 sum/2 的方案数
//答案就是 dp[j][sum/2]*(j!)*((n-j)!)(1<=j<=n) 的和
//乘上 (j!)*((n-j)!) 是因为我们的 dp 数组是不记录选取数字的顺序的
//我们需要把这种选取方案的所有情况全都加上
//这个可以预处理

inline void init(){
	fac[0]=1;
	for(int i=1;i<=100;i++)
		fac[i]=fac[i-1]*i%mod;
}

signed main(){
	init();
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),sum+=a[i];
	if(sum&1){ printf("0\n"); return 0; }
	//和是奇数，说明无法平均分成 2 份
	dp[0][0]=1;
	for(int i=1;i<=n;i++) //枚举到了第 i 个数
		for(int j=n;j>=1;j--) //选了 j 个数 由于滚动数组，j 要倒序枚举
			for(int k=sum/2;k>=a[i];k--) //和为 k
				dp[j][k]=(dp[j][k]+dp[j-1][k-a[i]])%mod; //方案数要累加
	
	for(int i=1;i<=n;i++)
		ans=(ans+fac[i]*fac[n-i]%mod*dp[i][sum/2]%mod)%mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：MurataHimeko (赞：0)

一个排列肯定只对应一个拿数的情况。

对排列计数是困难的，不妨对拿数的情况计数。

如果我们已经确定了 $A,B$ 拿到的数以及拿数顺序，那么可以唯一确定一个排列。

发现需要“拿到的数的个数”这个信息。

设 $f_{i,j,k}$ 表示，到了第 $i$ 个数，$A$ 拿到的数的和为 $j$，$A$ 已经拿了 $k$ 个数的方案数。

最后答案为 $\sum_{i} f_{n,\frac{sum}{2}, i} \times i!\times (n-i)!$。

代码：

```cpp
const int mod = 998244353;
int n, a[105];
int f[105][10005], g[105][10005];
int fac[105];

int main () {
    io >> n;
    re(i, n) io >> a[i];
    int sum = 0;
    g[0][0] = 1;
    re(i, n) {
        sum += a[i];
        rep(j, 0, i) {
            rep(k, 0, sum) {
                f[j][k] = g[j][k];
                if(k >= a[i] && j) f[j][k] = (f[j][k] + g[j-1][k - a[i]]) % mod;
            }
        }
        rep(j, 0, i) rep(k, 0, sum) g[j][k] = f[j][k], f[j][k] = 0;
    }
    fac[0] = 1;
    re(i, n) fac[i] = 1ll * fac[i-1] * i % mod;
    ll ans = 0;
    if(sum & 1) {
        io << "0";
        return 0;
    }
    re(i, n) {
        ans = (ans + 1ll * g[i][sum / 2] * fac[i] % mod * fac[n-i] % mod) % mod;
    }
    io << ans;
}
```


---

## 作者：Jsxts_ (赞：0)

对于一个情况，其中 $A$ 按顺序选了 $a_1\sim a_{k1}$，$B$ 按顺序选了 $b_1\sim b_{k2}$，那么对应这种情况的排列有且只有一个。因为如果交换一个排列中的任意两个数，所得的 $a$ 与 $b$ 序列都会不同。

所以，这道题就变成了一道很简单的题：从一堆数中选一些数使得和为 $\dfrac S2$。

背包即可。但是因为实际上是不考虑选数的顺序的，所以对于一个方案，假设选了 $x$ 个数，对答案的贡献要乘上 $x!(n-x)!$，所以在背包的基础上再加一维代表选了几个数。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 2e9;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n,m,a[110],f[110][10010],jc[110];
//f[i][j]:选了i个数，总和为j的方案数 
const int mod = 998244353;
int main() {
	n = read();
	for (int i = 1;i <= n;i ++ ) a[i] = read(), m += a[i];
	if (m % 2) puts("0"), exit(0);
	f[0][0] = 1;
	m /= 2;
	for (int i = 1;i <= n;i ++ )
		for (int k = n;k;k -- )
			for (int j = m;j >= a[i];j -- )
				f[k][j] = (f[k][j] + f[k - 1][j - a[i]]) % mod;
	int ans = 0;jc[0] = 1;
	for (int i = 1;i <= n;i ++ ) jc[i] = 1ll * jc[i - 1] * i % mod;
	for (int i = 1;i <= n;i ++ ) {
//		cout << i << ' ' << f[i][m] << endl;
		ans = (ans + 1ll * jc[i] * jc[n - i] % mod * f[i][m] % mod) % mod;
	}
	cout << ans;
	return 0;
}
```


---

