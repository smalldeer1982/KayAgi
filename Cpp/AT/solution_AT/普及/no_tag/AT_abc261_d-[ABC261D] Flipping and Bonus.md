# [ABC261D] Flipping and Bonus

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc261/tasks/abc261_d

高橋君が $ N $ 回コイントスを行います。 また、高橋君はカウンタを持っており、最初カウンタの数値は $ 0 $ です。

$ i $ 回目のコイントスで表裏のどちらが出たかによって、次のことが起こります。

- 表が出たとき：高橋君はカウンタの数値を $ 1 $ 増やし、$ X_i $ 円もらう。
- 裏が出たとき：高橋君はカウンタの数値を $ 0 $ に戻す。お金をもらうことは出来ない。

また、$ M $ 種類の連続ボーナスがあり、$ i $ 種類目の連続ボーナスではカウンタの数値が $ C_i $ になる**たびに** $ Y_i $ 円もらうことができます。

高橋君は最大で何円もらうことができるかを求めてください。

## 说明/提示

### 制約

- $ 1\leq\ M\leq\ N\leq\ 5000 $
- $ 1\leq\ X_i\leq\ 10^9 $
- $ 1\leq\ C_i\leq\ N $
- $ 1\leq\ Y_i\leq\ 10^9 $
- $ C_1,C_2,\ldots,C_M $ はすべて異なる。
- 入力はすべて整数

### Sample Explanation 1

順に 表, 表, 裏, 表, 表, 表 が出た時、もらえる金額は次のようになります。 - $ 1 $ 回目のコイントスで表が出る。カウンタの数値を $ 0 $ から $ 1 $ にして、$ 2 $ 円もらう。 - $ 2 $ 回目のコイントスで表が出る。カウンタの数値を $ 1 $ から $ 2 $ にして、$ 7 $ 円もらう。さらに、連続ボーナスとして $ 10 $ 円もらう。 - $ 3 $ 回目のコイントスで裏が出る。カウンタの数値を $ 2 $ から $ 0 $ にする。 - $ 4 $ 回目のコイントスで表が出る。カウンタの数値を $ 0 $ から $ 1 $ にして、$ 8 $ 円もらう。 - $ 5 $ 回目のコイントスで表が出る。カウンタの数値を $ 1 $ から $ 2 $ にして、$ 2 $ 円もらう。さらに、連続ボーナスとして $ 10 $ 円もらう。 - $ 6 $ 回目のコイントスで表が出る。カウンタの数値を $ 2 $ から $ 3 $ にして、$ 8 $ 円もらう。さらに、連続ボーナスとして $ 1 $ 円もらう。 このとき高橋君は合計で $ 2+(7+10)+0+8+(2+10)+(8+1)=48 $ 円もらうことができ、このときが最大です。 連続ボーナスはカウンタの数値が $ C_i $ になるたびに何度でももらえることに注意してください。 ちなみに、$ 6 $ 回のコイントスで全部表が出た時は $ 2+(7+10)+(1+1)+8+(2+5)+8=44 $ 円しかもらうことが出来ず、この時は最大ではありません。

### Sample Explanation 2

答えが $ 32 $ bit 整数型に収まらないこともあることに注意してください。

## 样例 #1

### 输入

```
6 3
2 7 1 8 2 8
2 10
3 1
5 5```

### 输出

```
48```

## 样例 #2

### 输入

```
3 2
1000000000 1000000000 1000000000
1 1000000000
3 1000000000```

### 输出

```
5000000000```

# 题解

## 作者：xiaomuyun (赞：3)

- [洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc261_d)
- [AtCoder 题目传送门](https://atcoder.jp/contests/abc261/tasks/abc261_d)

## 思路分析

考虑 $dp$。

设 $dp_{i,j}$ 为掷第 $i$ 次硬币，计数器示数为 $j$ 时的最大可能收益。我们可以很容易想到两种情况。

### 1. $j=0$

$j=0$ 说明上一次掷硬币掷到了反面，所以上一次计数器的示数从 $0$ 到 $i$ 都有可能，因此当 $j=0$ 时：

$$dp_{i,j}=\max\limits_{k=0}^i dp_{i-1,k}$$

### 2. $j>0$

$j>0$ 说明上一次掷硬币掷到了正面，所以上一次计数器的示数只可能是 $j-1$。这时会获取钱。首先是第 $i$ 次掷硬币掷到正面获取的 $x_i$，然后是计数器的额外连胜奖励。为了方便查找，我们在输入连胜奖励的时候用一个数组 $y$ 来存，$y_i$ 表示计数器示数为 $i$ 时的奖励，默认为 $0$，即没有奖励。所以当 $j>0$ 时：

$$dp_{i,j}=dp_{i-1,j-1}+x_i+y_j$$

### 答案统计

因为最后一次掷硬币示数为任意 $\le n$ 的数都可以，所以答案为 $\max\limits_{i=0}^n dp_{n,i}$。

## 代码实现

注意获得的奖励之和有可能大于 `int` 的范围，所以需要 `long long`。

```cpp
#include<algorithm>
#include<cstdio>
#define int long long
using namespace std;
const int maxn=5e3+1;
int n,m,x[maxn],y[maxn],f[maxn][maxn],res=0;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lld",&x[i]);
	for(int i=1,c,v;i<=m;++i){
		scanf("%lld%lld",&c,&v);
		y[c]=v;//用数组储存额外连胜奖励
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<i;++j) f[i][0]=max(f[i-1][j],f[i][0]);//对应j=0
		for(int j=1;j<=i;++j) f[i][j]=f[i-1][j-1]+x[i]+y[j];//对应j>0
		if(i==n){//统计答案
			for(int j=0;j<=n;++j) res=max(f[n][j],res);
		}
	}
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：luwanning (赞：1)

### Solution

一道典型 DP。

令 $f[i][j]$ 表示第 $i$ 次掷硬币，计数器示数为 $j$ 时的最大收益。


---


转移分两种情况。

当 $j=0$ 时，上一次掷硬币一定为反面，所以计数器示数 $0$ 到 $i-1$ 都有可能。

转移方程：$f_{i,j}=\max_{0\le{j}<i}(f_{i-1,j})$。

当 $j>0$ 时，上一次掷硬币一定为正面，所以计数器示数为第 $i-1$ 轮掷硬币的示数加 $1$，收益为原有的收益加上 $x_i$，而且如果计数器示数为 $j$ 时有连胜奖励也要加上 $y[j]$。
转移方程：$f_{i,j}=f_{i-1,j-1}+x_i+y_j$。

代码 1.0：
```
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 5011;
int n, m, x[N], y[N];
long long f[N][N], ans;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &x[i]);
	for (int i = 1; i <= m; i++) {
		int c, d;
		scanf("%d%d", &c, &d);
		y[c] = d;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++)
			f[i][0] = max(f[i][0], f[i - 1][j]);
		for (int j = 1; j <= i; j++)
			f[i][j] = 0LL + f[i - 1][j - 1] + x[i] + y[j];
	}
	for (int i = 0; i <= n; i++)
		ans = max(ans, f[n][i]);
	printf("%lld\n", ans);
	return 0;
}
//时间复杂度为O(nm)
//空间复杂度为O(n*n)
```


---


但是空间复杂度还能优化！
每轮循环只需要用到 $f_i$ 和 $f_{i-1}$，滚动数组！这个我就不写了。

还可以继续优化成一个一维数组。计算 $f_{i,j}$ 时可以倒着枚举 $j$，这样每次用到 $f_{i-1,j-1}$ 都是前面已经计算好的。但注意！计算 $f_{i,1}$ 的时候会用到 $f_{i,0}$，在这一轮中被计算过，所以用变量 $pr$ 记录每个 $f_{i-1,0}$。

好啦！现在就可以吧空间复杂度优化到 $\operatorname{O}(n)$ 啦！

代码 2.0：

```
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 5011;
int n, m, x[N], y[N];
long long f[N], ans, pr;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &x[i]);
	for (int i = 1; i <= m; i++) {
		int c, d;
		scanf("%d%d", &c, &d);
		y[c] = d;
	}
	for (int i = 1; i <= n; i++) {
		pr = f[0];
		for (int j = 1; j < i; j++)
			f[0] = max(f[0], f[j]);
		for (int j = i; j >= 2; j--)
			f[j] = 0LL + f[j - 1] + x[i] + y[j];
		f[1] = pr + x[i] + y[1];
	}
	for (int i = 0; i <= n; i++)
		ans = max(ans, f[i]);
	printf("%lld\n", ans);
	return 0;
}
```
此题解决！

---

## 作者：Mingrui_Yang (赞：1)

[luogu 传送门](https://www.luogu.com.cn/problem/AT_abc261_d)

## 题意

高桥要掷 $N$ 次硬币。   
如果为正面，则获得 $X_i$ 元的奖励。如果连续 $C_i$ 次为正面（即计数器示数为 $C_i$），则获得 $Y_i$ 元的奖励。  
求高桥的最大收益。

## Solution

考虑 DP。

令 $f_{i, j}$ 为掷了 $i$ 次硬币，计数器示数为 $j$（连续 $j$ 次为正面）的最大收益。

如果 $j = 0$，则说明上一次掷到的是反面，所以上一次计数器的示数可以是 $0$ 到 $i$ 之间的任意整数。因为上一次为反面，所以没有奖励。  
所以此时 $f_{i, j}$ 就等于 $f_{i - 1, k} (0 \le k < i)$ 的最大值。

如果 $j \ge 1$，则说明上一次掷到的是正面，所以上一次计数器的示数一定是 $j - 1$。因为上一次是正面，所以会有奖励，最基本的奖励 $X_i$ 和连胜奖励。我们可以开一个 $mp$ 数组，在输入时初始化，$mp_i$ 计数器示数为 $i$ 时的连胜奖励。  
所以此时 $f_{i, j}$ 就等于 $f_{i - 1, j - 1} + X_i + mp_i$（通过枚举 $j(1 \le j \le i)$ 的值来更新所有的 $f_{i, j}$）。

答案为 $f_{n, k}(0 \le k \le n)$ 的总和。

## CODE

注意开 `long long`。

```cpp
#include <bits/stdc++.h>

#define int long long 

using namespace std;

const int N = 5010;

int n, m;
int x[N], c[N], y[N];
int mp[N];
int f[N][N];

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ ) cin >> x[i];
	for (int i = 1; i <= m; i ++ ) cin >> c[i] >> y[i], mp[c[i]] = y[i];		// mp 存连胜奖励 
	
	for (int i = 1; i <= n; i ++ ) {
		for (int j = 0; j < i; j ++ ) f[i][0] = max(f[i][0], f[i - 1][j]);		// j == 0
		for (int j = 1; j <= i; j ++ ) f[i][j] = f[i - 1][j - 1] + x[i] + mp[j];// j >= 1
	}
	
	int ans = 0; // 答案 
	for (int i = 0; i <= n; i ++ ) ans = max(f[n][i], ans);
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：Tsawke (赞：1)

# [[ABC261D] Flipping and Bonus](https://www.luogu.com.cn/problem/AT_abc261_d) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC261D)

## 题面

掷 $ n $ 次硬币，同时存在计数器，初始为 $ 0 $。第 $ i $ 次投掷若为正面则计数器 $ +1 $ 并获得 $ X_i $ 元。若为背面则清空计数器并不获得钱。额外地，有 $ m $ 种连胜奖励，即示数为 $ C_i $ 时额外奖励 $ Y_i $ 元。求可能的最大收益。

## Solution

题意较为明显，再看数据范围，显然 DP。不难想到设状态 $ dp(i, j) $ 表示投掷完第 $ i $ 次并且此时示数为 $ j $，我们特别地令 $ Y_i $ 表示示数为 $ i $ 时的奖励，无奖励时认为为 $ 0 $，显然可以通过 `map` 维护。显然边界均为 $ 0 $ 即可，则转移显然为：
$$
dp(i, j) =
\left\{
\begin{array}{ll}
dp(i - 1, j - 1) + X_i + Y_j & \quad j \neq 0 \\
\max_{k = 0}^{i - 1}\{dp(i - 1, k)\} & \quad j = 0
\end{array}
\right.
$$
也就是如果继续连胜则由上次转移，否则可以由任意示数转移到示数为 $ 0 $，后者式子可以优化到 $ O(1) $ 但没必要，最终为 $ \texttt{2D0D} $ 的 DP，复杂度 $ O(n^2) $，可以通过。

最终答案即为 $ \max_{i = 0}^n dp(n, i) $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N, M;
ll X[5100];
unordered_map < ll, ll > mp;
ll dp[5100][5100];
ll ans(0);
ll Y(int idx){
    if(mp.find(idx) == mp.end())return 0;
    return mp[idx];
}

int main(){
    N = read(), M = read();
    for(int i = 1; i <= N; ++i)X[i] = read();
    for(int i = 1; i <= M; ++i){
        int C = read(), Y = read();
        mp.insert({C, Y});
    }
    for(int i = 1; i <= N; ++i){
        for(int k = 0; k <= i - 1; ++k)dp[i][0] = max(dp[i][0], dp[i - 1][k]);
        for(int j = 1; j <= i; ++j)dp[i][j] = dp[i - 1][j - 1] + X[i] + Y(j);
    }
    for(int i = 0; i <= N; ++i)ans = max(ans, dp[N][i]);
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_24 初稿

---

## 作者：highkj (赞：0)

# 思路
一眼 Dp 题，我们来想如何定义状态，我们可以定义 $f_{i,j,0/1}$ 为现在是第 $i$ 次计数器为 $j$ 这次是正面还是反面的最大价值。

然后就可以开始想如何转移了，首先肯定要枚举一个 $i$ 和 $j$ 然后我们把 $k=0$ 或 $k=1$ 的情况分开处理。
- $f_{i,0,0}=\max(f_{i-1,0,0},f_{i-1,j,1})$ 这里的 $j$ 其实枚举的是上一次的状态。
- $f_{i,j+1,1}=\max(f_{i-1,j,0}+x_i+mp_{j+1})$ 这里还需要将 $f_{i,1,1}$ 给先处理出来，其中 $mp_i$ 代表当计数器为 $i$ 时的奖励。

最后答案就位所有的 $f_{n,i,1}$ 和 $f_{n,0,0}$ 的最大值了。
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
const int N=5e3+10;
int f[N][N][3];
int mp[N];
int x[N],n,m;
fire main() {
	cin>>n>>m;
	rep(i,1,n) cin>>x[i];
	rep(i,1,m) {
		int c,y;
		cin>>c>>y;
		mp[c]+=y;
	}
	rep(i,1,n) {
		f[i][1][1]=f[i-1][0][0]+x[i]+mp[1]; //提前处理不然会错
		f[i][0][0]=f[i-1][0][0]+mp[0];
		rep(j,1,i-1) {
			f[i][0][0]=max(f[i][0][0],f[i-1][j][1]+mp[0]);//转移
			f[i][j+1][1]=max(f[i][j+1][1],f[i-1][j][1]+x[i]+mp[j+1]);
		}
	}
	int ans=0;
	rep(i,1,n) ans=max(ans,f[n][i][1]);
	cout<<max(ans,f[n][0][0])<<endl; //输出
	return false;
}

```

---

## 作者：SnapYust (赞：0)

## 题目传送门

[Flipping and Bonus](https://www.luogu.com.cn/problem/AT_abc261_d)

## 思路

看到这种和硬币有关的，求利益最大化的，一般都是用贪心和动规。

但对于贪心来说，这道题贪心很难打，并且就算打出来那大概率也是假的。

于是我们就需要进行**动态规划**！

这是一个很简单的 dp 题，可以当动规初学的练手题。

这篇题解已经假设您已经理解了简单的动规，并且接触过二维动规。

我们先假设 $dp_i$ 表示前 $i$ 个硬币的最大利益。

但这样根据题意，我们还需要维护当前的计数器，因为还有 $M$ 种**额外连胜奖励**需要用到计数器。

所以，我们再假设 $dp_{i,j,k}(k\in[0,1])$ 来表示前 $i$ 个硬币，当前计数器为 $j$，选（或不选）第 $i$ 个（$k=1$ 或 $k=0$）的最大利益。

可以得出：

$$dp_{i,0,0}=\max dp_{i-1,j(0\to i),k(1\text{ or }0)}$$

$$dp_{i,j(j>0),1}=\max(dp_{i-1,j-1,1},dp_{i-1,j-1,0})+X_i$$

$$dp_{i,j(j>0),0}=\max(dp_{i-1,j-1,1},dp_{i-1,j-1,0})$$

并且，对于 $\forall j>0$ 且 $k=1$：

$$if(C_{l(1\to m)}=j)\text{ }dp_{i,j,k}\leftarrow dp_{i,j,k}+Y_l$$

对于以上思路，时间复杂度是 $O(n^2m)$，显然不能AC。

考虑**优化**：

我们可以设定一个数组 $g$，在输入程序的时候 $g_{C_l}=Y_l$，这样就能 $O(1)$ 的复杂度来查询当前的 $j$ 是否能加钱，省去一个 $m$。

同时在最外层的 $for(i\to n)$ 内定义一个变量 $last=-1$，然后在内层的 $for((j=1)\to i)$ 中每求出一个 $dp_{i,j,k}$ 就和 $last$ 取一个 $\max$。然后下一个 $dp_{i,0,0}=last$ 就好了，又优化了一点。

现在的复杂度为小于 $O(n^2)$，可以切爆本题。

但大家都发现了，这是个三维动规，那我们可以优化成二维吗？

**当然可以**！

我们发现当 $j=0$ 时，$k$ 也等 $0$，反之毅然，且可以证明 $dp_{i,j(j>0),1}>dp_{i,j(j>0),0}$，多了一个转移方程，我们完全可以把 $k$ 优化掉。

于是：

$$dp_{i,0}=last$$

$$dp_{i,j}=dp_{i-1,j-1}+X_i+g_j$$

$$ans=\max\text{ }dp_{n,p(0\to n)}$$

然后这道题就做完了，代码也比较好写，一共二三十行，我就不放代码了。

---

## 作者：hjqhs (赞：0)

考虑 dp。   
先设计状态。容易想到设 $dp_{i,j}$ 为投第 $i$ 枚硬币，计数器为 $j$ 时的最大收益。  
当 $j=0$ 时，说明上一次硬币是反面，上一次计时器的范围显然 $0$ 到 $i$ 都有可能，所以 $dp_{i,j}=\max{dp_{i-1,k}}(0 \le k \le i)$。  
当 $j \ge 0$ 时，说明上一次硬币是正面，那么上一次计数器只能是 $j-1$。此时获得的钱是 $x_i+y_j$ 元，转移方程是 $dp_{i,j}=dp_{i-1,j-1}+x_i+y_j$。  
而答案为 $\max_{i=0}^{n}{dp_{n,i}}$。  
代码时间复杂度 $O(n^2)$，注意要开 `long long`。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF=0x3f3f3f3f;
const int MAXN=5005;
const int MAXM=5005;
int n,m,x[MAXN],y[MAXM],dp[MAXN][MAXN],ans=-INF;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>x[i];
	for(int i=1;i<=m;++i){
		int c,v;
		cin>>c>>v;
		y[c]=v;
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<=i;++j){
			if(j==0){
				for(int k=0;k<=i;++k){
					dp[i][j]=max(dp[i][j],dp[i-1][k]);
				}
			}else if(j>0){
				dp[i][j]=dp[i-1][j-1]+x[i]+y[j];
			}
		}
	}
	for(int i=0;i<=n;++i)ans=max(ans,dp[n][i]);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc261_d)

# 思路

这题有正反两种情况，我们可以考虑 dp，定义 $ dp_{i,j} $ 表示第 $ i $ 次抛硬币计数器示数为 $ j $。

第一种情况 $ j = 0 $，抛的硬币是反面。

$$ dp_{i,0} = \max^{i}_{j=0}dp_{i-1,j} $$

第二种情况 $ j > 0 $，抛的硬币是正面。

$$ dp_{i,j} = dp_{i-1,j-1} + x_i + y_j $$

最大收益。

$$ ans = \max^{n}_{i=1}dp_{n,i} $$

# code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[5002][5002],m,n,x[5002],a,b,ans=-1e18;
map<int,int>mp;//map存储连胜奖励
signed main(){//记得开long long
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>x[i];
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		mp[a]=b;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) 
			f[i][0]=max(f[i][0],f[i-1][j]);//j=0的情况
		for(int j=1;j<=i;j++)
			f[i][j]=f[i-1][j-1]+x[i]+mp[j];//j>0的情况
	}
	for(int i=1;i<=n;i++) 
		ans=max(ans,f[n][i]);//统计答案
	cout<<ans<<endl;
	return 0;//完结撒花
}
```


---

## 作者：Glacial_Shine (赞：0)

# 题目大意

丢 $n$ 次硬币，如果这次是反面，就将计数器清空，如果这次是正面，就将计数器加一，并且得到 $x_i$ 元。

有 $m$ 种额外的奖励，当你的计数器为 $c_i$ 时，你将得到 $d_i$ 的钱。

求你最多能得到多少钱？

# 思路

考虑 DP。

我们设 $f_{i, j}$ 表示当你**丢完**第 $i$ 次硬币时，你的计数器的值为 $j$ 时最多能得到的钱。

如果 $j\not=0$，说明这一次丢到的是正面，则 $f_{i, j} = f_{i - 1, j - 1} + x_i + d_j$。

如果 $j = 0$，说明这一次丢到的是反面，则 $f_{i, 0} = max( \left\{  f_{i - 1, j} | 0 \leq j < i \right\} )$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, m;
LL f[5005][5005], a[5005], b[5005], ans, maxn;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    LL u, v;
    for (int i = 1; i <= m; i++)
        scanf("%lld%lld", &u, &v), b[u] += v;
    f[1][1] = a[1] + b[1];
    for (int i = 2; i <= n; i++) {
        maxn = 0;
        for (int j = 1; j <= i; j++)
            f[i][j] = f[i - 1][j - 1] + a[i] + b[j], maxn = max(f[i - 1][j], maxn);
        f[i][0] = maxn;
    }
    for (int j = 0; j <= n; j++)
        ans = max(ans, f[n][j]);
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：Butterfly_qwq (赞：0)

这题大体思路如下：

首先，DP，不难看出来吧。

定义数组 $f_i$ 表示计数器显示 $i$ 时获得的额外奖金。

$dp_{i,j}$ 表示投掷 $i$ 次硬币计数器显示 $j$ 的时候所获得的最大收益。

接下来分两种情况，$j=0$ 和 $j\not=0$。

当 $j=0$，上一次就投掷到了反面，那么上一次的 $j$ 可以是任意数（除了 $0$）

那么 $dp_{i,0}=\max\limits_{j=1}^{i-1}dp_{i-1,j}$

如果 $j\not=0$，那么上一次投掷到了正面，那么 $dp_{i,j}=dp_{i-1,j-1}+x_i+f_j$

注：此处 $x_i$ 为第 $i$ 次投掷获得的基础钱财

那么整体公式就是：

$$dp_{i,j}= \left\{
\begin{aligned}
&\max\limits_{j=1}^{i-1}dp_{i-1,j}\ \ \ \ \ j=0\\
&dp_{i-1,j-1}+x_i+f_j \ \ \ \ \ j\not=0 
\end{aligned}
\right.$$

给个代码：

```
#include<bits/stdc++.h>
using namespace std;
long long x[5001],f[5001],dp[5001][5001];
int main()
{
	int n,m;
	long long c,y,ans=-1;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>x[i];
	for(int i=0;i<m;i++)
	{
		cin>>c>>y;
		f[c]=y;
	}
	for(int i=1;i<=n;i++)
	{
		dp[i][0]=-1;
		for(int j=1;j<=i;j++)dp[i][j]=dp[i-1][j-1]+x[i]+f[j];
		for(int j=0;j<i;j++)dp[i][0]=max(dp[i][0],dp[i-1][j]);
	}
	for(int i=0;i<=n;i++)ans=max(ans,dp[n][i]);
	cout<<ans;
	return 0;
}
```

谢谢大家，祝洛谷越办越好！！！

---

