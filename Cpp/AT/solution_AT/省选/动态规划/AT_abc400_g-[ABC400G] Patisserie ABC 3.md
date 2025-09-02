# [ABC400G] Patisserie ABC 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc400/tasks/abc400_g

在 ABC 西点店工作的糕点师高桥君决定为纪念 AtCoder Beginner Contest 400 推出特别蛋糕套装。

ABC 西点店销售 $N$ 种蛋糕，分别为蛋糕 $1$，蛋糕 $2$，……，蛋糕 $N$。  
每个蛋糕具有三个非负整数值属性：美观度、美味度和人气度。具体来说，蛋糕 $i$ 的美观度、美味度、人气度分别为 $X_i$，$Y_i$，$Z_i$。

高桥君计划将蛋糕无重复地组成 $K$ 对进行销售。  
形式化地说，需要选出 $2K$ 个**互不相同**的 $1$ 到 $N$ 之间的整数 $a_1, b_1, a_2, b_2, \ldots, a_K, b_K$，并将蛋糕 $a_i$ 与蛋糕 $b_i$ 组成一对。  
当蛋糕 $a_i$ 与蛋糕 $b_i$ 组成一对时，该对的价格定义为 $\max(X_{a_i} + X_{b_i},\ Y_{a_i} + Y_{b_i},\ Z_{a_i} + Z_{b_i})$。  
其中 $\max(P, Q, R)$ 表示 $P, Q, R$ 中的最大值。

请计算这 $K$ 对蛋糕价格总和的可能最大值。

给定 $T$ 个测试用例，请对每个用例输出答案。

## 说明/提示

### 约束条件

- $1 \leq T \leq 1000$
- $2 \leq N \leq 10^5$
- 对于每个输入文件，所有测试用例的 $N$ 总和不超过 $10^5$。
- $1 \leq K \leq \lfloor \frac{N}{2} \rfloor$（对于实数 $x$，$\lfloor x \rfloor$ 表示不超过 $x$ 的最大整数）。
- $0 \leq X_i, Y_i, Z_i \leq 10^9$
- 输入中的所有值均为整数

### 样例解释 1

从 $3$ 个蛋糕中选择 $1$ 对：  
- 蛋糕 $1$ 和 $2$ 组成的对价格为 $\max(6+3, 3+5, 8+0) = 9$  
- 蛋糕 $1$ 和 $3$ 组成的对价格为 $\max(6+2, 3+7, 8+3) = 11$  
- 蛋糕 $2$ 和 $3$ 组成的对价格为 $\max(3+2, 5+7, 0+3) = 12$  
因此选择蛋糕 $2$ 和 $3$ 组成的对，输出 $12$。

### 样例解释 2

注意每个蛋糕最多只能出现在一个对中。此外，即使不同种类的蛋糕，其美观度、美味度、人气度也可能完全相同。  
对于第一个测试用例，选择蛋糕 $1$ 和 $2$（价格 $6$）以及蛋糕 $3$ 和 $5$（价格 $203$），总价格为 $209$。  
对于第二个测试用例，选择蛋糕 $2$ 和 $3$（价格 $176$）以及蛋糕 $4$ 和 $5$（价格 $157$），总价格为 $333$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
1
3 1
6 3 8
3 5 0
2 7 3```

### 输出

```
12```

## 样例 #2

### 输入

```
2
5 2
1 2 3
1 2 3
1 2 3
1 2 3
100 100 200
6 2
21 74 25
44 71 80
46 28 96
1 74 24
81 83 16
55 31 1```

### 输出

```
209
333```

# 题解

## 作者：Disjoint_cat (赞：15)

## Statement

给定正整数 $n,k$ 和 $n$ 个三元组 $(x_i,y_i,z_i)$。

现要选出 $k$ 个二元组 $(a_i,b_i)$，满足每个位置只能出现一次，并要求最大化：

$$\sum_{i=1}^k\max\{x_{a_i}+x_{b_i},y_{a_i}+y_{b_i},z_{a_i}+z_{b_i}\}$$

输出这个最大值。

Data range：$T$ 组多测，$\sum n\le 10^5$，$2k\le n$，$0\le x_i,y_i,z_i\le 10^9$。

## Solution

首先你考虑每个数对答案的贡献。你发现每种数（指 $x,y,z$）的贡献都是成对的，所以肯定要求数量都是偶数。

而你发现偶数是充要的（两两配对就行，如果实际上不是这种数产生贡献那也肯定不是最优解），那么问题转化成了：

> 对于每个 $i$ 可以选 $x_i$、选 $y_i$、选 $z_i$ 或什么都不选，要求一共选 $2k$ 个，且每种数都要选偶数个，求最大和。

这里就有了一个 $\mathcal O(nk)$ 的做法了，就是 dp 记一下前 $i$ 个里选了 $j$ 个，$x,y,z$ 分别有奇数/偶数个的最大和。

当然这是过不了的，考虑优化。

你发现偶数这个限制很松，即使不符合稍微调一下也能符合。

那你考虑按 $\max\{x_i,y_i,z_i\}$ 从大到小排序。

然后会有一个结论：最终方案中，前 $2k$ 个里面最多有两个不选（被调整成后面的至多两个，注意前面的选了并**不**一定是最大的那个）。

> 证明：
>
> 我们称一个前面没选的、$x_i$（在 $x_i,y_i,z_i$ 中）最大的位置为 $\texttt X$ 类，$\texttt Y,\texttt Z$ 类同理；后面的选了 $x_i$ 的位置为 $\texttt x$ 类，$\texttt y,\texttt z$ 类同理。
>
> 那么：
> 
> 1. 显然不可能同时出现 $\texttt X,\texttt x$ 类，因为可以直接替换掉，其他的同理。
> 2. 也不可能同时出现两个 $\texttt X$ 类和两个 $\texttt y$ 类：也可以直接替换。
>
> 假设前面的有三个没选，那么对应的后面会选了三个。
>
> 简单分讨一下这些位置分别是哪一类的，就可以发现这是不可能的，从而证明该命题。

那么接下来就简单了：对前 $2k$ 个和后面 $(n-2k)$ 个分别 dp，那么「选了几个」的维度就被压缩到了 $3$ 的长度（对于前面可以记不选了几个），那么 dp 的复杂度就降到了 $\mathcal O(n)$。

于是就在 $\mathcal O(n\log n)$ 的时间复杂度内解决了本题，瓶颈在于排序。

- 本题只有 $x,y,z$ 三维，但实际上可以扩展到 $m$ 维的情况。此时可以证明前面至多 $(m-1)$ 个被替换成后面的，所以可以在 $\mathcal O(n\log n+nm^22^m)$ 的时间复杂度内解决（注意转移带一个 $m$）。

## Code

32ms/14MB

截至现在它还是并列最优解。~~注意到有个 31ms 的代码与此代码编辑距离为 $0$。小朋友素质无敌了。~~

[Submission link](https://atcoder.jp/contests/abc400/submissions/64533700)

```cpp
// Author: YE Minghan
#include<bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include "templates/debug.h"
#else
#define dbg(...) (void)0
#define here (void)0
#endif
#define ll long long
#define endl '\n'
#define PB emplace_back
#define PPB pop_back
#define MP make_pair
#define ALL(Name) Name.begin(),Name.end()
#define PII pair<int,int>
#define VI vector<int>
#define GI greater<int>
#define fi first
#define se second

const int N=100005;
int n,k;
array<int,3>a[N];
ll dp[N][12];
void ck(ll &x,ll y){x=max(x,y);}

int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	int _;cin>>_;while(_--)
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=0;j<3;j++)cin>>a[i][j];
	sort(a+1,a+n+1,[](auto x,auto y){return max({x[0],x[1],x[2]})>max({y[0],y[1],y[2]});});
	memset(dp,0xc0,8*12*(n+3));
	dp[0][0]=dp[n+1][0]=0;
	for(int i=1;i<=k<<1;i++)
		for(int j=0;j<12;j++)
		{
			ck(dp[i][j],dp[i-1][j]+a[i][0]);
			ck(dp[i][j^1],dp[i-1][j]+a[i][1]);
			ck(dp[i][j^2],dp[i-1][j]+a[i][2]);
			if(j<8)ck(dp[i][j+4],dp[i-1][j]);
		}
	for(int i=n;i>k<<1;i--)
		for(int j=0;j<12;j++)
		{
			if(j<8)ck(dp[i][j+4],dp[i+1][j]+a[i][0]);
			if(j<8)ck(dp[i][(j+4)^1],dp[i+1][j]+a[i][1]);
			if(j<8)ck(dp[i][(j+4)^2],dp[i+1][j]+a[i][2]);
			ck(dp[i][j],dp[i+1][j]);
		}
	ll ans=0;
	for(int i=0;i<12;i++)ck(ans,dp[k<<1][i]+dp[(k<<1)+1][i]);
	cout<<ans<<endl;

}

	return 0;
}
```

---

## 作者：wmrqwq (赞：3)

这是一篇视频题解。

![](bilibili:BV1pydkYuEoc?t=20)

[参考代码](https://atcoder.jp/contests/abc400/submissions/64829121)

---

## 作者：luanyanjia (赞：2)

调的有点久。

如果不考虑 $k$ 的限制，那么有一个显然的 DP：先把 $x,y,z$ 的贡献拆掉，转化成选一些数两两配对，计算他们 $x_i$ 的贡献；再选另外一些数配对，计算他们 $y_i$ 的贡献；对 $z_i$ 同理。

又由于他们可以任意配对，所以限制就可以直接写成：

> 从序列中选出三组数，其中每一组的数量都是偶数。答案是第一组的 $x_i$ 之和加上第二组的 $y_i$ 之和加上第三组的 $z_i$ 之和。

这样是对的，因为错解一定是不优的。

DP 的时候直接多记一维状态 $0 \le S < 2^3$ 表示三组数个数的奇偶性即可。单次时间复杂度 $O(n)$。

现在加上 $k$ 的限制。我们发现选 $k$ 组的答案关于 $k$ 是凸的（理解一下就是一定会先选出贡献大的数对，斜率是不增的）。直接上 wqs 二分就行。

写的时候注意一下二分的是 $x$ 到 $x+2$ 之间的斜率，要进行一些乘除 $2$ 的处理，具体看代码吧。

```cpp
#include<bits/stdc++.h>
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
    int ch=getchar();
    T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x*=f;rd(args...);
}
const int N=1e5+5;
typedef long long ll;
const ll INF=1e18;
int T,n,k,v[N][3];
std::pair<ll,int> dp[N][8];
inline std::pair<ll,int> Solve(int x){
	for(int i=0;i<8;i++)dp[0][i]={-INF,0};
	dp[0][0]={0,0};
	for(int i=1;i<=n;i++){
		for(int j=0;j<8;j++){
			dp[i][j]=dp[i-1][j];
			for(int k=0;k<3;k++){
				auto tmp=std::make_pair(dp[i-1][j^(1<<k)].first+2*v[i][k]-x,dp[i-1][j^(1<<k)].second+1);
				dp[i][j]=std::max(dp[i][j],tmp);
			}
		}
	}return dp[n][0];
}
inline void Solve(){
	rd(n,k);
	for(int i=1;i<=n;i++)rd(v[i][0],v[i][1],v[i][2]);
	int L=0,R=2e9;
	while(L<=R){
		int mid=(0ll+L+R)>>1;
		Solve(mid);
		if(dp[n][0].second>=2*k)L=mid+1;
		else R=mid-1;
	}
	Solve(R);
	printf("%lld\n",dp[n][0].first/2+1ll*k*R);
}
signed main(){
	rd(T);
	while(T--)Solve();
    return 0;
}
```

---

## 作者：_Kamisato_Ayaka_ (赞：2)

[ABC400G](https://www.luogu.com.cn/problem/AT_abc400_g)

## Statement

给你 $n$ 个元素，每个元素有三个参数 $X_i,Y_i,Z_i$，你要不重复的选出 $K$ 对元素，也是就说你会取 $2K$ 个元素，对于每对元素其价值为 $max\{X_i + X_j, Y_i + Y_j, Z_i + Z_j\}$，求你最后能获得的最大价值和，多测。

## Solution

记 $a_{i,k}(k\in [1,3])$ 表示 $x_i,y_i,z_i$。

考虑给题目一个转化：
> $\forall i \in [1,n]$，你在 $x_i,y_i,z_i$ 中选择一个或者不选，每一种选了偶数个的最大价值和。

其实在没有偶数个的限制是很好做的，按照 $\max\{x_i,y_i,z_i\}$ 从大到小排序，选择前 $2K$ 个就行。

但是加上了限制呢？

如果说把前 $2K$ 个选了，可能会存在不满足偶数个的一种类型，也就是说要进行调整，前 $2K$ 个中选了之后调整一定更优。

这样来看就是前 $2K$  个中可能会有 $t$ 个不会被选到，这个 $t$ 的数量其实不会很多。

也就是说有 $t$ 个不会被选的名额分到了 $3$ 种参数上，但是你不想让 $t$ 太大，结论告诉我们 $t = 3$。

考虑抽屉原理，假设 $t = 4$，那么选择的 $x_i,y_i,z_i$ 一定会有那个是不被选了两个的，那么不在前 $2K$ 个当中的 $x_i,y_i,z_i$ 也是有 $4$ 个被选，且有两个重复的。

如果说你把后面选的两个重复替换到前面，奇偶性不会改变（如果是奇数依旧不满足要求），但是会更优（前面选出来不一定是每组最大的），因为你可以选择其它的来改变奇偶性或者增加答案，综上 $t = 3$ 最优。

开始 dp，记 $f_{i,j,S}$ 表示前 $i$ 个不被选的有 $j$ 个，集合 $S$ 表示每种数（$x_i,y_i,z_i$）被选的个数的奇偶性（$0$ 偶 $1$ 奇），$g_{i,j,S}$ 表示考虑后面 $[i,n]$ 中选了 $j$ 个，集合 $S$ 同理，$f,g$ 一开始都是极小值，$f_{0,0,0} = g_{n+1,0,0} = 0$。

考虑 $f$ 的转移，假设当前 $i$ 要选：
$$
f_{i,j,S} \leftarrow \max{f_{i-1,j,S\oplus 2^k} + a_{i,k}}
$$
否则：
$$
f_{i,j,S} \leftarrow \max{f_{i-1,j,S}}
$$

$g$ 其实就同理了，只不过倒序转移：

$$
g_{i,j,S} \leftarrow \max{g_{i+1,j-1,S\oplus 2^k}}
$$

以及：

$$
g_{i,j,S} \leftarrow \max{g_{i+1,j,S}}
$$

最后答案：

$$
\max\limits_{j=0}^{3}{\max\limits_{S=0}^{7}\{f_{2k,j,S} + g_{2k + 1,j,S}\}}
$$

完结撒花。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline void chkmin (int &x, int y) { if (x > y) x = y; }
inline void chkmax (int &x, int y) { if (x < y) x = y; }
inline int _max (int x, int y, int z) { return max (x, max (y, z)); }

constexpr int MAXN = 1e5 + 10, INF = 0x7f7f7f7f7f7f;
int Test = 0, n = 0, K = 0, f[MAXN][4][8], g[MAXN][4][8];
struct Cake {
	int val[3];
	bool operator < (const Cake &s) const { return _max (val[0], val[1], val[2]) > _max (s.val[0], s.val[1], s.val[2]); }
} infor[MAXN];

inline void Solve() {
	scanf ("%lld %lld", &n, &K);
	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j < 3; j ++)
			scanf ("%lld", &infor[i].val[j]);
	}
	sort (infor + 1, infor + n + 1);
	for (int i = 0; i <= n + 1; i ++) {
		for (int j = 0; j < 4; j ++) {
			for (int S = 0; S < 8; S ++)
				f[i][j][S] = g[i][j][S] = -INF;
		}
	}
	f[0][0][0] = g[n + 1][0][0] = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j < 4; j ++) {
			for (int S = 0; S < 8; S ++) {
				for (int k = 0; k < 3; k ++) 
					chkmax (f[i][j][S], f[i - 1][j][S ^ (1LL << k)] + infor[i].val[k]);
				if (j) chkmax (f[i][j][S], f[i - 1][j - 1][S]);
			}
		}
	}
	for (int i = n; i; i --) {
		for (int j = 0; j < 4; j ++) {
			for (int S = 0; S < 8; S ++) {
				for (int k = 0; k < 3; k ++) if (j)
					chkmax (g[i][j][S], g[i + 1][j - 1][S ^ (1LL << k)] + infor[i].val[k]);
				chkmax (g[i][j][S], g[i + 1][j][S]);
			}
		}
	}
	int Answer = 0;
	for (int j = 0; j < 4; j ++) {
		for (int S = 0; S < 8; S ++)
			chkmax (Answer, f[K << 1][j][S] + g[K << 1 | 1][j][S]);
	}
	return printf ("%lld\n", Answer), void();
}

signed main() {
	scanf ("%lld", &Test);
	while (Test --) Solve();
	return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：1)

实际上这个题可以用 wqs 二分做的。

首先，我们需要拆分一下原问题贡献。发现答案形式 $\max(x_i+x_j,y_i+y_j,z_i+z_j)$。说明了以 $x,y,z$ 为贡献的情况都是一对一对的，也就是说满足选择的个数是偶数。

然后我们就有一个这样的做法：设 $f_{i,j,0/1,0/1,0/1}$ 表示前 $i$ 个数选 $j$ 个然后 $x,y,z$ 个数的奇偶性。做到 $O(nk)$。

设选 $k$ 对的答案为 $g(k)$。你会发现 $g(k)$ 单调并且增长速度递减。很好理解，对于正整数 $i$ 如果存在 $g(i)-g(i-1) < g(i+1)-g(i)$ 就说明解并不优秀。具体而言可以把第 $i+1$ 组与 $i$ 组调换，得到更优秀的答案。

所以我们可以 wqs 二分一下，设每选一组需要花费的代价为 $lim$，此时最优解中选取的组数 $x$ 随 $lim$ 的增大减小。状态简化为 $f_{i,0/1,0/1,0/1}$，去掉了第二维 $j$。

然后需要注意一下记录常见的细节问题，比如选取组数取值范围，时间复杂度 $O(n \log V)$，其中 $V$ 是值域。

---

## 作者：ax_by_c (赞：0)

太牛。不会。最好能在这道题上学到点东西。

首先注意到 $x,y,z$ 这三类中每一类都产生了偶数次贡献，且每一个 $(x,y,z)$ 最多产生一次贡献。

实际上这样选就够了，我们给选到同一类的两两配对，那么实际价值不会比这样算出来的价值小，而且是能取到的。

于是有了一个 DP，设 $f_{i,j,S}$ 表示前 $i$ 个 $(x,y,z)$ 选了 $j$ 个，三类取的个数奇偶性为 $S$ 时的最大价值。

转移显然，答案即为 $f_{n,2k,0}$。

时间复杂度 $O(nk)$，无法通过。

注意到奇偶性的限制比较松，稍微调一下就能合法。

不考虑奇偶性的限制时直接按 $\max(x,y,z)$ 排序后取前 $2k$ 大即可。

那么考虑使用类似做法。先排个序，然后分成前面 $2k$ 个和后面。

假设前面有至少 $3$ 个没选，那么后面会选至少 $3$ 个。

1. 不可能同一类在前面没选后面选了，否则可以直接换掉。

2. 不可能前面同一类有两个没选后面同一类有两个选了，否则可以直接换掉。

3. 不可能前面和后面都是三类，否则可以直接换掉。

于是可以得出结论：前面至多两个不选，后面至多选两个。

于是 DP 中 $j$ 那一维就可以优化掉了，时间复杂度 $O(n\log n)$，瓶颈在于排序。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll llinf=3e18;
const int N=1e5+5;
void chk(ll &x,ll y){
	x=(x>y)?(x):(y);
}
struct node{
	ll w[3];
}a[N];
bool cmp(node a,node b){
	return max({a.w[0],a.w[1],a.w[2]})>max({b.w[0],b.w[1],b.w[2]});
}
int n,m;
ll f1[N][3][8],f2[N][3][8];
void slv(){
	scanf("%d %d",&n,&m);
	rep(i,1,n)rep(j,0,2)scanf("%lld",&a[i].w[j]);
	sort(a+1,a+1+n,cmp);
	rep(i,0,n+1)rep(j,0,2)rep(k,0,7)f1[i][j][k]=f2[i][j][k]=-llinf;
	chk(f1[0][0][0],0);
	rep(i,0,m*2-1)rep(j,0,2)rep(k,0,7){
		rep(p,0,2)chk(f1[i+1][j][k^(1<<p)],f1[i][j][k]+a[i+1].w[p]);
		if(j<2)chk(f1[i+1][j+1][k],f1[i][j][k]);
	}
	chk(f2[n+1][0][0],0);
	per(i,n+1,m*2+2)rep(j,0,2)rep(k,0,7){
		chk(f2[i-1][j][k],f2[i][j][k]);
		if(j<2)rep(p,0,2)chk(f2[i-1][j+1][k^(1<<p)],f2[i][j][k]+a[i-1].w[p]);
	}
	ll ans=0;
	rep(x,0,2)rep(s,0,7)chk(ans,f1[m*2][x][s]+f2[m*2+1][x][s]);
	printf("%lld\n",ans);
}
void main(){
	int T=1;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
} 
```

---

