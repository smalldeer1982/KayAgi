# Mr. Kitayuta, the Treasure Hunter

## 题目描述

The Shuseki Islands are an archipelago of $ 30001 $ small islands in the Yutampo Sea. The islands are evenly spaced along a line, numbered from $ 0 $ to $ 30000 $ from the west to the east. These islands are known to contain many treasures. There are $ n $ gems in the Shuseki Islands in total, and the $ i $ -th gem is located on island $ p_{i} $ .

Mr. Kitayuta has just arrived at island $ 0 $ . With his great jumping ability, he will repeatedly perform jumps between islands to the east according to the following process:

- First, he will jump from island $ 0 $ to island $ d $ .
- After that, he will continue jumping according to the following rule. Let $ l $ be the length of the previous jump, that is, if his previous jump was from island $ prev $ to island $ cur $ , let $ l=cur-prev $ . He will perform a jump of length $ l-1 $ , $ l $ or $ l+1 $ to the east. That is, he will jump to island $ (cur+l-1) $ , $ (cur+l) $ or $ (cur+l+1) $ (if they exist). The length of a jump must be positive, that is, he cannot perform a jump of length $ 0 $ when $ l=1 $ . If there is no valid destination, he will stop jumping.

Mr. Kitayuta will collect the gems on the islands visited during the process. Find the maximum number of gems that he can collect.

## 说明/提示

In the first sample, the optimal route is 0 $ → $ 10 (+1 gem) $ → $ 19 $ → $ 27 (+2 gems) $ →...&#x1; $

In the second sample, the optimal route is 0 $ → $ 8 $ → $ 15 $ → $ 21 $ → $ 28 (+1 gem) $ → $ 36 (+1 gem) $ → $ 45 (+1 gem) $ → $ 55 (+1 gem) $ → $ 66 (+1 gem) $ → $ 78 (+1 gem) $ →... $

In the third sample, the optimal route is 0 $ → $ 7 $ → $ 13 $ → $ 18 (+1 gem) $ → $ 24 (+2 gems) $ → $ 30 (+1 gem) $ →... $

## 样例 #1

### 输入

```
4 10
10
21
27
27
```

### 输出

```
3
```

## 样例 #2

### 输入

```
8 8
9
19
28
36
45
55
66
78
```

### 输出

```
6
```

## 样例 #3

### 输入

```
13 7
8
8
9
16
17
17
18
21
23
24
24
26
30
```

### 输出

```
4
```

# 题解

## 作者：zythonc (赞：9)

## 【分析过程】

~~很有意思，很有意思~~

首先简单的手玩一下发现贪心肯定是不行的，考虑动归

显然**第一维是我们现在处的位置**，看看第二维：

- 如果我们将上一次跳的步数 $c$ 作为一个状态维，那么这一维的大小就是$30000$

$30000*30000$的数组可以MLE上天...

考虑优化

我们发现跳完每一次之后下一次能跳的距离是能**确定**的，并且要么不变，要么+1，要么-1

所以这里容易想到把变化的次数作为一维，变化n次之后可以跳 $c+n-1$ ~ $c+n+1$ 距离远

举个例子，如果第一步可以跳 $300$ 距离，那么变化 $150$ 次下一次就是跳 $449$ ~ $451$ 距离远，变化 $-150$ 次下一次就是 $149$ ~ $151$ 距离远

手算一下可知最多变化 $300$ 多次，所以我们开 $650$ 是完全够用的

所以很容易写出转移方程：$f[i][o]=\max(f[i][o],\max(f[i-(m+o)][o],f[i-(m+o)][o-1],f[i-(m+o)][o+1])+v[i]);$

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 30010
using namespace std;
const int df=320;
int n,m,f[N][650],in,v[N],ans;
inline int tm(int a,int b,int c) {return a>b?(a>c?a:c):(b>c?b:c);}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>in;
		v[in]+=1;
	}
	memset(f,-0x3f,sizeof(f));
	ans=f[m][df]=v[0]+v[m];
	for(int i=m+1;i<=in;i++){
		for(int o=-320;o<=320;o++){
			if(m+o>0&&m+o<=i) f[i][df+o]=max(f[i][df+o],tm(f[i-(m+o)][df+o],f[i-(m+o)][df+o-1],f[i-(m+o)][df+o+1])+v[i]);
			ans=max(ans,f[i][df+o]);
		}
	}
	cout<<ans;
}
```

有人问不是最多变化 $300$ 多次吗，为什么如果将上一次跳的步数 $c$ 作为一个状态维，这一维的大小就是$30000$呢？

- 答：输入 $d$ 的时候可没写小于 $300$ 啊，所以我们考虑变化次数

---

## 作者：A_grasser (赞：3)

## 更新

1. 修复了代码错误。

## 题意简化

在 $n$ 个点有一些宝藏，初始时你在 $0$ 处。第一步你能跳到 $d$ 处，之后你可以选择跳 $c-1$，$c$，$c+1$ 步（$c$ 为上一跳的步数），问最多可获得多少宝藏。

## 需要注意的地方

1. 动态规划要进行优化。

## 解法分析

~~我是不会告诉你这道题在我任务计划里吃了半年灰的。~~

瞄一眼，感觉是动规，考虑状态。设 $f_{i,j}$ 是在 $i$ 处，上一步跳了 $j$ 步可获得的最多宝藏数。如果这么定义会产生一个问题，$i$ 和 $j$ 可以撑到 $30000 \times 30000$，铁定要 MLE。

哪里不行就优化哪里。可见，$j$ 一维有太多浪费的空间。改一下，$j$ 表示变化了 $j$ 次可获得的最多宝藏数，那么手推一下等差数列得到最大的 $j$ 只有 $ \frac{(2d+j)(j+1)}{2}$，大约 $300$ 左右。

接下来就好办了，推状态转移方程。最终 $f_{i,300+j}$ 只要在 ${f_{i,300+j}}$，$f_{i-(d+j),300+j}$，$f_{i-(d+j),300+j-1}$，$f_{i-(d+j),300+j+1}+w_i$ 中挑个最大的就行。

为什么是 $300+j$？因为他可以选择变换时少跳一步，这会使 $j$ 产生负数，调整一下即可。在实现时，这里的 $300$ 应调大一档，以免越界。

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int n,d,w[30007],f[30007][740],ans;
int main(){
	cin>>n>>d;
	int x;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		w[x]++;
	}
	//初始化 
	memset(f,-0x3f,sizeof(f));
	f[d][370]=w[0]+w[d];
	ans=f[d][370];
	for(int i=d+1;i<=x/*最后x一定最大，放心使用*/;i++){
		for(int j=-320;j<=320;j++){
			if(d+j>0 && d+j<=i)//符合条件 
				f[i][370+j]=max(f[i][370+j],max(f[i-(d+j)][370+j],max(f[i-(d+j)][370+j-1],f[i-(d+j)][370+j+1]))+w[i]);
			ans=max(ans,f[i][370+j]);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：__Hacheylight__ (赞：3)

CF505C Mr. Kitayuta, the Treasure Hunter 

题意：

在一个有n个点的岛屿上，有n个点有宝藏。

现在给你一个d。

开始你在0

第一步，你将跳到d处

之后你可以选择跳c-1,c,c+1步(c为你上一步跳的步数)

每跳到某处可获得该地宝藏

询问最大宝藏数

这个题当Div.1 A,现场跪了不少人，各种大佬，神犇

解析：

很明显是个DP

Dp[i][j]表示在i，上一步跳了c步的最大值

但i<=30000,j<=30000，时空一起炸，How to do it?

考虑优化：

因为每次挑一部c都只会改变1，所以j有很多空间浪费

dp[i][j]表示在i,与d变化了j的最大值

通过等差数列求和，可轻松得知j最多变化300次

则这个题就变成水题了。。。

递推版
```cpp
#include <bits/stdc++.h>
using namespace std ;
const int inf=0x3f3f3f3f ;
const int D=400 ; 
const int N=3e4 ;
int cnt[N+10];
int dp[N+10][2*D+10] ;
int n,d,x,ans ;
int main(){
	scanf("%d%d",&n,&d) ;
	for (int i=1;i<=n;i++){
		scanf("%d",&x);
		cnt[x]++ ;
	}
	for (int i=0;i<=N;i++){
		for (int j=-D;j<=D;j++)
		dp[i][j+D]=-inf ;
	}
	dp[d][D]=cnt[0]+cnt[d] ;
	for (int i=d;i<=N;i++){
		for (int j=-D;j<=D;j++){
			if (dp[i][j+D]==-inf){
				continue ;
			}
			for (int z=-1;z<=1;z++){
				int len=j+d+z ;
				if (j+z < -D || j+z >D || len<1 || i+len>N) continue ;
				dp[i+len][j+z+D]=max(dp[i+len][j+z+D],dp[i][j+D]+cnt[i+len]) ;
			}
		}
	}
	ans=0 ;
	for (int i=0;i<=N;i++){
		for (int j=-D;j<=D;j++){
			ans=max(ans,dp[i][j+D]) ;
		}
	}
	printf("%d\n",ans) ;
	return 0 ;
}
```

记忆化DP

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define N 30010
#define M 610
int s[N] ;
int dp[N][M] ;//滚动数组
//dp[i][j]表示跳到i,d的伏动范围为j-300的最大宝藏数 
//等差数列 告诉我们这大概最大有 sqrt(n)项≈300 
int n,d,x ;
bool ok(int x,int c){ //是否越界 
	int delta=d+c-300 ;
	if (delta<=0) return false ;
	if (delta+x>30000) return false ; 
	return true ;
}
int dfs(int x,int c){
	int &ret=dp[x][c] ;
	if (ret==-1){ //没算过 
		ret=0;
		if (ok(x,c)) ret=max(ret,dfs(x+d+c-300,c)) ;
		if (ok(x,c-1)) ret=max(ret,dfs(x+d+c-1-300,c-1)) ;
		if (ok(x,c+1)) ret=max(ret,dfs(x+d+c+1-300,c+1)) ;
		ret+=s[x] ;
	} 
	return ret ;
} 
int main(){
	scanf("%d%d",&n,&d);
	memset(dp,-1,sizeof(dp)) ;//清零 
	for (int i=1;i<=n;i++){
		scanf("%d",&x) ;
		s[x]++;//该点宝藏数 
	}
	printf("%d\n",dfs(d,300)) ;//滚动 
} 
```


---

## 作者：run_away (赞：2)

## 题意

在数轴上有 $n$ 块宝石，当你走到一个点时，可以获得点上所有的宝石。

若前一步走了 $c$ 个单位长度，那么下一步可以走 $c-1,c,c+1$ 个单位长度。

你最开始在原点，可以向右走 $d$ 个单位长度，求最多可获得多少宝石。

## 分析

设 $f_{i,j}$ 表示在第 $i$ 个点，上一步走 $j$ 个单位长度可获得的最大宝石数。

但是 $n,p_i$ 的范围是 $3\times 10^4$，二维数组会 MLE，考虑怎么优化。

因为最远的宝石在 $3\times 10^4$，设步数变化 $x$ 次，则最大的 $x$ 满足 $\frac{(2d+x)(x+1)}{2}\le 3\times 10^4$，解得 $x$ 不会超过 $300$。

更改一下状态，设 $f_{i,j}$ 表示在第 $i$ 个点，$d$ 变化了 $j$ 次所能得到的最大宝石数。

总时间复杂度大概计算 $300n$ 次，可过。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll maxn=30000,inf=400;
ll n,d,f[maxn+5][inf*2+5],cnt[maxn+5],ans;
signed main(){
    n=read(),d=read();
    for(ll i=1;i<=n;++i)++cnt[read()];
    for(ll i=0;i<=maxn;++i){
        for(ll j=-inf;j<=inf;++j){
            f[i][inf+j]=LLONG_MIN;
        }
    }
    f[d][inf]=cnt[0]+cnt[d];
    for(ll i=d;i<=maxn;++i){
        for(ll j=-inf;j<=inf;++j){
            if(f[i][inf+j]==LLONG_MIN)continue;
            for(ll k=-1;k<=1;++k){
                ll len=d+j+k;
                if(j+k<-inf||j+k>inf||len<1||i+len>maxn)continue;
                f[i+len][inf+j+k]=max(f[i+len][inf+j+k],f[i][inf+j]+cnt[i+len]);
            }
        }
    }
    for(ll i=0;i<=maxn;++i){
        for(ll j=-inf;j<=inf;++j){
            ans=max(ans,f[i][inf+j]);
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：wth2026 (赞：2)

# 题目大意
有 $n$ 个岛屿，$n$ 个宝藏，每一次可以跳上一次跳的步数加一，减一或者不变。求一共能吃到几个宝藏。
# 题目思路
看起来是一个很标准的动态规划，但是因为本人菜，不会写，所以只能写深搜。

每一次传跳到哪里了和跳的几步跳到这里的，枚举即可。
# AC Code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f

using namespace std;
int n, d, in, f[30005][605], mp[30005];

bool PD(int x, int y) {
    int k = d + y - 300;

    if (k <= 0) {
        return 0;
    }

    if (x + k > 30000) {
        return 0;
    }

    return 1;
}

int dfs(int x, int y) {
    if (f[x][y] != -1) {
        return f[x][y];
    }

    int cnt = 0;

    if (PD(x, y - 1)) {
        cnt = max(cnt, dfs(x + y - 1 + d - 300, y - 1));
    }

    if (PD(x, y)) {
        cnt = max(cnt, dfs(x + y + d - 300, y));
    }

    if (PD(x, y + 1)) {
        cnt = max(cnt, dfs(x + y + 1 + d - 300, y + 1));
    }

    f[x][y] = cnt + mp[x];
    return f[x][y];
}

void init() {
    memset(f, -1, sizeof(f));
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	
    cin >> n >> d;

    while (n --) {
        cin >> in;
		++ mp[in];
	}

    cout << dfs(d, 300) << endl;
    return 0;
}
```

---

## 作者：cheng_qi (赞：1)

### 题意

给定 $n$ 个有宝藏的点的坐标以及第一步的可以走的长度 $d$，求最多可以获得多少宝藏。（$n,d\le 3 \times 10^4$，坐标 $\le 3 \times 10^4$）

-----

首先给人的感觉是一道贪心题，但是并没有什么好的贪心思路。对于这种每一步决策都对后续决策有影响的题目考虑DP，首先设 $f_{i,j}$ 为走到坐标为 $i$，上一步走的长度为 $j$ 获得的宝藏数。不难给出方程式：
$$
f_{i + j,j} = \max(f_{i,j},f_{i,j - 1},f_{i,j+1}) + cnt_{i+j}
$$
其中 $cnt_i$ 表示 $i$ 坐标处有多少宝藏。

注意到数据范围，如果是 $O(n\cdot d)$ 的时间复杂度一定过不去，我们考虑裁剪无效状态。

我们考虑有哪些状态才能被转移，假设第一次移动的步数为 $d$，最终的移动步数为 $d + \lvert k\rvert $，根据等差数列 $\frac{(d + d + \lvert k\rvert) \times (\lvert k \rvert + 1)}{2} \le 3\times 10^4$，解得 $\lvert k \rvert$ 不超过 $400$。因此我们可以删去大部分无用状态。时间和空间也就都在可接受范围内了。这道题本身不难，主要是如何判断哪些状态无用。

### Code

在代码中贴了详细注释。

```cpp
constexpr int N = 30005, D = 400;
int n, d, cnt[N], f[N][(D << 1) + 10];
int main() {
    // read 是快读，这里不给出实现
    read(n), read(d);
    for (int i = 1; i <= n; ++i) {
        int pos;
        read(pos);
        ++cnt[pos];//统计每个位置的宝藏数量
    }
    memset(f, -0x3f, sizeof(f));
    f[d][D] = cnt[0] + cnt[d];//考虑第一步走 d 步，于是初始状态直接设置在 d 位置
    // 我们将 D 看作零点，防止出现负下标
    int ans = 0;
    for (int i = d + 1; i <= 30000; ++i) {
        for (int j = -D; j <= D; ++j) {
            for (int k = -1; k <= 1; ++k) {
                int step = j + d + k; // 这一步的步长
                if (step < 1 || i + step > 30000 || j + k < -D || j + k > D)
                    continue;
                f[i + step][j + k + D] = max(f[i + step][j + k + D], f[i][j + D] + cnt[i + step]);//这个dp式子与朴素的dp式子是相同的
            }
            ans = max(ans, f[i][j + D]);
        }
    }
    write(ans);
    return 0;
}
```





---

## 作者：_zqh_ (赞：0)

> 涉及芝士点：简单 DP

# 思路简述
设 $f_{i,j}$ 为当前蹦到第 $i$ 号点，上一次蹦了 $j$ 的最多宝藏数。

$30000 \times 30000$，连数组都开不下。

换种方式，设 $f_{i,j}$ 为当前蹦到第 $i$ 号点，上次蹦的长度偏移了 $j$ 的最多宝藏数。

因为等差数列，所以 $j$ 满足: 
$$
\frac{(j + 2 \times d)(j + 1)}{2} \le 30000 
$$

转化一下：

$$
\frac{1}{2}j^2+\frac{2d+1}{2}j+(d-30000)\le0
$$

解得约 $j\le300$；

因为 $j$ 有可能是负数，所以我们可以加上一个偏移量 $ex=300$。

---

接着就是转移；

$$
f_{i,j+300}=\max
\begin{cases}
f_{i-(d+j),j + 300}\\
f_{i-(d+j),j + 299}\\
f_{i-(d+j),j + 301}
\end{cases}
$$

思路完结。

# 代码

极其丑陋就别看了吧嘿嘿。

```cpp
#include <bits/stdc++.h>
// #pragma GCC optimize(2)
#define int long long
#define pii pair<int, int>
#define piiii pair<pii, pii>
#define il inline
#define p_q priority_queue
#define u_m unordered_map
#define bt bitset
#define rg register
#define rd Nothing::read
#define wt Nothing::write
#define endl '\n'

using namespace std;

namespace Nothing {
	il int read() {
		int f = 1, t = 0;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if ( ch == '-' ) {
				f = -1;
			}
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			t = t * 10 + ch - '0';
			ch = getchar();
		}
		return t * f;
	}

	il void write(int x, bool s) {
		if (x < 0) {
			putchar('-');
			write(-x, false);
			return ;
		}
		if (!s && x == 0)
			return ;
		if (s && x == 0) {
			putchar('0');
			return ;
		}
		write(x / 10, false);
		putchar(x % 10 + '0');
	}
}

const int N1 = 300005;
const int N2 = 1000006;
const int Mod = 998244353;

namespace COMB {
	int fac[N2] = {0};
	il void Cinit(int p) {
		fac[0] = 1;
		for (int i = 1; i < N2; i++) {
			fac[i] = fac[i - 1] * i % p;
		}
	}
	il int qpow(int a, int b, int p) {
		int ans = 1;
		while (b) {
			if (b & 1) {
				ans = ans * a % p;
			}
			a = a * a % p;
			b >>= 1;
		}
		return ans;
	}
	il int C(int n, int m, int p) {
		if (m > n || m < 0) {
			return 0;
		}
		return fac[n] * qpow(fac[m], p - 2, p) % p * qpow(fac[n - m], p - 2, p) % p;
	}
	il int Lucas(int n, int m, int p) {
		if (!m) return 1;
		return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
	}
	il int GCD(int n, int m, int p) {
		return __gcd(n, m) % p;
	}
	il int LCM(int n, int m, int p) {
		return n * m % p * qpow(GCD(n, m, p), p - 2, p) % p;
	}
}
using namespace COMB;
using namespace Nothing;

//#define debug 1
//#define multi_test 1
#define IOS 1

int T = 1;

int n, d;

int p[30005];

int Last;

int Dp[30005][645];

int dp(int i, int j, int k, int t) {
	if (j > t - d) return -0x3f3f3f3f3f3f3f3f;
	if (j <= -d) return -0x3f3f3f3f3f3f3f3f;
	return Dp[i][j + k];
}

void Init() {
	cin >> n >> d;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		p[x]++;
		Last = max(Last, x);
	}
	return ;
}

void Solve() {
	memset(Dp, -0x3f, sizeof(Dp));
	int ans = 0;
	ans = Dp[d][300] = p[0] + p[d];
	for (int i = d + 1; i <= Last; i++) {
		for (int j = -300; j <= 300; j++) {
			Dp[i][j + 300] = max(dp(i, j, 300, i), max(dp(i - (d + j), j, 300, i), max(dp(i - (d + j), j, 299, i), dp(i - (d + j), j, 301, i))) + p[i]);
			ans = max(ans, Dp[i][j + 300]);
		}
	}
	cout << ans;
	return ;
}

signed main() {
#ifdef debug
	freopen("zqh.in", "r", stdin);
	freopen("zqh.out", "w", stdout);
#endif
#ifdef multi_test
	cin >> T;
#endif
#ifdef IOS
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
#endif
	while (T--) {
		Init();
		Solve();
	}
	return 0;
}
/*

*/
```

---

