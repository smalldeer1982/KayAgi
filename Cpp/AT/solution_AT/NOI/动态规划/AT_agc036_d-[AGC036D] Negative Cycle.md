# [AGC036D] Negative Cycle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc036/tasks/agc036_d

$ N $ 頂点からなる重み付き有向グラフがあり、頂点には $ 0 $ から $ N-1 $ までの番号がついています。

最初、このグラフには $ N-1 $ 本の辺があります。 このうち $ i $ 番目 ($ 0\ \leq\ i\ \leq\ N-2 $) の辺は、 頂点 $ i $ から頂点 $ i+1 $ へ向かう重さ $ 0 $ の辺です。

すぬけさんはこれから、全ての $ i,j $ ($ 0\ \leq\ i,j\ \leq\ N-1,\ i\ \neq\ j $) について、新たに辺 $ (i\ →\ j) $ を追加する操作を行います。 辺の重さは、$ i\ <\ j $ なら $ -1 $、そうでないなら $ 1 $ とします。

りんごくんは、グラフに負閉路（閉路であって、そこに含まれる辺の重みの総和が $ 0 $ 未満のもの）があるととても悲しいです。 そこで、すぬけさんが追加した辺のうちいくつかを削除して、最終的なグラフに負閉路が含まれないようにすることにしました。 すぬけさんが追加した辺 $ (i\ →\ j) $ を削除するには $ A_{i,j} $ のコストがかかります。 なお、最初からあった $ N-1 $ 本の辺を削除することはできません。

りんごくんが目的を達成するために必要なコストの総和の最小値を求めてください。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ A_{i,j}\ \leq\ 10^9 $
- 入力される値はすべて整数である。

### Sample Explanation 1

すぬけさんが追加した辺 $ (0\ →\ 1) $ を削除すると、グラフに負閉路がないようになります。 この時必要なコストは $ 2 $ で、これが最小です。

### Sample Explanation 2

すぬけさんが追加した辺 $ (1\ →\ 2) $ と $ (3\ →\ 0) $ を削除すると、グラフに負閉路がないようになります。 この時必要なコストは $ 1+1=2 $ で、これが最小です。

## 样例 #1

### 输入

```
3
2 1
1 4
3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4
1 1 1
1 1 1
1 1 1
1 1 1```

### 输出

```
2```

## 样例 #3

### 输入

```
10
190587 2038070 142162180 88207341 215145790 38 2 5 20
32047998 21426 4177178 52 734621629 2596 102224223 5 1864
41 481241221 1518272 51 772 146 8805349 3243297 449
918151 126080576 5186563 46354 6646 491776 5750138 2897 161
3656 7551068 2919714 43035419 495 3408 26 3317 2698
455357 3 12 1857 5459 7870 4123856 2402 258
3 25700 16191 102120 971821039 52375 40449 20548149 16186673
2 16 130300357 18 6574485 29175 179 1693 2681
99 833 131 2 414045824 57357 56 302669472 95
8408 7 1266941 60620177 129747 41382505 38966 187 5151064```

### 输出

```
2280211```

# 题解

## 作者：小粉兔 (赞：67)

考虑差分约束模型，图中不存在负环等价于存在一组合法的差分约束的解。

考虑每个节点作为一个变量，第 $i$ 个节点对应的变量为 $x_i$。

因为初始的边不能删去，所以一定有 $x_i \ge x_{i + 1}$。

考虑令 $q_i = x_i - x_{i + 1}$，那么就会有 $q_i \ge 0$。

假设保留了一条边权为 $-1$ 的 $i \to j$ 的边，也就是说 $i < j$ 的话：  
就会有 $x_i - 1 \ge x_j$，即 $x_i - x_j \ge 1$，也就是说 $q_i + q_{i + 1} + \cdots + q_{j - 1} \ge 1$。

假设保留了一条边权为 $1$ 的 $i \to j$ 的边，也就是说 $i > j$ 的话：  
就会有 $x_i + 1 \ge x_j$，即 $x_j - x_i \le 1$，也就是说 $q_j + q_{j + 1} + \cdots + q_{i - 1} \le 1$。

反过来想，如果确定了所有的 $q_i$，那么每一条边就应该尽可能地保留下来，这样代价最小。

对于边权为 $-1$ 的边，是区间和 $\ge 1$ 才能保留，也就是说如果区间和 $= 0$ 就必须删除。

对于边权为 $1$ 的边，是区间和 $\le 1$ 才能保留，也就是说如果区间和 $\ge 2$ 就必须删除。

也就是说，对于一种 $q$ 的取值方案，$q_i = 0$ 的每个连续段，都对应着一系列的边权为 $-1$ 的边的删除。

而区间和 $\ge 2$ 的区间也对应着边权为 $1$ 的边的删除。

显然可以发现，如果出现了 $q_i \ge 2$，不如把它变成 $1$，这样一定会变得更优（边 $i \to (i + 1)$ 不用被删除了）。

所以只需要考虑 $q$ 的取值为 $\{0, 1\}$ 的情况。

然后可以发现，每个 $0$ 的连续段就对应着一部分区间的删除，所以考虑如下 DP：

记 $dp(i, j)$ 表示考虑到了 $q_i$，最后一个 $1$ 取在了 $q_i$，倒数第二个 $1$ 取在了 $q_j$ 处的情况下，可以确定的代价的最小值。

$dp(i, j)$ 可以从 $dp(j, k)$ 转移而来，利用二维前缀和可以快速求出转移系数。

时间复杂度为 $\mathcal O (N^3)$，[评测链接](https://atcoder.jp/contests/agc036/submissions/10351160)。

---

## 作者：cwfxlh (赞：13)

# [AT_agc036_d](https://www.luogu.com.cn/problem/AT_agc036_d)    
把这张图看做一个差分约束模型，对 $i$ 号点赋一个点权 $x_i$，问去掉若干条限制来使差分约束有解的最小代价。    

首先有固定限制 $a_i\le a_{i+1}$，于是对其差分，令 $c_i=a_{i+1}-a_i$，则首先有 $c_i$ 非负，另外，对于 $i<j$ 有 $\sum_{u=i}^{j-1}c_u\ge 1$，对于 $i>j$ 有 $\sum_{u=j}^{i-1}c_u\le 1$。   

可以发现，如果将所有非零的 $c$ 设为 $1$，答案不会变化，于是只需要考虑 $01$ 序列，另外，代价最多和两个 $1$ 相关，于是直接考虑 DP，记录强制设当前位置为 $1$ 和上一个 $1$ 的位置作为状态，转移即可。复杂度 $O(n^3)$。   

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[503][503],pre1[503][503],pre2[503][503],dp[503][503],ans;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			scanf("%lld",&a[i][j]);
			if(i<j)ans+=a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			pre1[i][j]=pre1[i-1][j]+pre1[i][j-1]-pre1[i-1][j-1];
			pre2[i][j]=pre2[i-1][j]+pre2[i][j-1]-pre2[i-1][j-1];
			if(i<j){
				pre1[i][j]+=a[j][i];
				pre2[i][j]+=a[i][j];
			}
		}
	}
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<i;j++){
			dp[i][j]=(pre1[j][i+1]-pre1[j][i])
			+(pre2[j][j])
			+(pre2[i-1][i]-pre2[j][i]-pre2[i-1][j+1]+pre2[j][j+1]);
			for(int k=1;k<j;k++){
				dp[i][j]=min(dp[i][j],dp[j][k]
				+(pre1[k][i]-pre1[k][j+1])
				+(pre1[j][i+1]-pre1[j][i])
				+(pre2[i-1][i]-pre2[j][i]-pre2[i-1][j+1]+pre2[j][j+1]));
			}
			ans=min(ans,dp[i][j]+(pre1[j][n]-pre1[j][i+1])+(pre2[n][n]-pre2[n][i+1]-pre2[i][n]+pre2[i][i+1]));
		}
	}
	for(int i=1;i<n;i++){
		ans=min(ans,pre2[i-1][i]-pre2[i-1][1]+pre2[n][n]-pre2[i][n]-pre2[n][i+1]+pre2[i][i+1]);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：天命之路 (赞：10)

跟现有题解的推法不太一样。这确实是道非常有 AtCoder 风格的题。

首先看到这种一眼没有多项式做法的题，考虑找性质简化问题。

我们注意到有 $n - 1$ 条 $i \to i + 1$ 的边是永远不会被删去的，考虑以此为突破口，观察与其方向相同的负边的性质。

**Key observation**：如果我们确定了一条从 $i$ 到 $j$ 的负边必须保留，那么对于 $i' \le i$，$j' \ge j$，负边 $i' \to j'$ 在最优解中也必须保留。

证明：考虑证明加入这条边后不影响合法性，如果保留边 $i' \to j'$ 之后出现了负环，那么把这个环中所有走过 $i'\to j'$ 的部分都替换为先用 $0$ 边从 $i'$ 走到 $i$，再走边 $i \to j$，然后从 $j$ 用 $0$ 边走到 $j'$，就会得到一个不经过边 $i' \to j'$ 的负环，说明加入这条边之前也有负环，矛盾了。

既然不影响合法性，所有边权值还都 $>0$，那加入这条边显然会得到一个更优的解。$\Box$

所以，最终答案的负边一定连成如下形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/oui9251a.png)

其中线段表示序列上的一个个区间，区间内部不连边，圆点表示一些孤立点。所有非孤立点向在它后面与其不同区间的非孤立点都有连边。

进一步观察可以发现，孤立点是不存在的，因为将孤立点并入其旁边的区间肯定不劣，这个操作不会影响正边怎么连。

于是在最优解中，原序列可以被划分为 $k$ 个区间 $[l_i,r_i]$，满足 $l_i = r_{i - 1} + 1,l_1 = 1,r_k = n$。所有起点终点在同一个区间内的负边都要删掉。而此时能保留的正边 $i \to j$ 必须满足 $i$ 与 $j$ 在同一个区间或者 $j$ 所在区间与 $i$ 所在区间中间没有夹着其它区间。其余的正边都要删掉。

问题转化到这里就很好做了。设 $dp_{i,j}$ 表示考虑到第 $i$ 位，最后一个区间是 $[j,i]$ 的最小代价。 $dp_{i,j}$ 可以从 $dp_{j - 1,k}$ 转移过来，转移时加的代价可以通过二维前缀和快速预处理。总时间复杂度为 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 5;
typedef long long ll;
template<typename T> inline bool ckmin(T &x,const T &y) { return (x > y) && (x = y,true);}
int n;
int B[N][N],A[N][N]; // A+,B-
ll dp[N][N];
ll sa[N][N],sb[N][N];
inline ll Query(ll s[N][N],int l1,int r1,int l2,int r2) {
	if(l1 == 0 && l2 == 0) return s[r1][r2];
	if(l1 == 0) return s[r1][r2] - s[r1][l2 - 1];
	if(l2 == 0) return s[r1][r2] - s[l1 - 1][r2];
	return s[r1][r2] - s[l1 - 1][r2] - s[r1][l2 - 1] + s[l1 - 1][l2 - 1];
} 
int main() {
	cin >> n;
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j < i;j++) cin >> A[j][i];
		for(int j = i + 1;j <= n;j++) cin >> B[i][j];
	}
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			sa[i][j] = sa[i][j - 1] + sa[i - 1][j] - sa[i - 1][j - 1] + A[i][j],
			sb[i][j] = sb[i][j - 1] + sb[i - 1][j] - sb[i - 1][j - 1] + B[i][j];
	memset(dp,0x3f,sizeof dp);
	ll ans = 1e18;
	dp[0][0] = 0;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= i;j++)
			for(int k = 0;k < j;k++)
				ckmin(dp[j][i],dp[k][j - 1] + Query(sb,j,i,j,i) - Query(sa,j,i,j,i) - Query(sa,k,j - 1,j,i));
	for(int i = 1;i <= n;i++) ckmin(ans,dp[i][n]);
	ans += sa[n][n];
	cout << ans << endl;
	return 0;
}
```



---

## 作者：caidzh (赞：9)

不存在负环等价于存在最短路

不妨记 $0$ 到 $i$ 的最短路为 $d_i$

由于权值为 $0$ 边必然存在，所以 $d_i\ge d_{i+1}$

由于非 $0$ 的边权只有 $1,-1$，所以 $[d_{n-1},0]$ 中所有的值都至少在一个 $d_i$ 中出现，且所有相等的最短路值形成了一个连续的段

不妨考虑这样连续的三段 $i,j,k:$ 其中 $dis_i=dis_j+1=dis_k+2$

![](https://cdn.luogu.com.cn/upload/image_hosting/oz2xc2tj.png)

此时如果下面那条红边存在的话，$i$ 连续段会被松弛，此时产生了负环，若连向 $i$ 之前的连续段同理

如果一个连续段内存在一条 $-1$ 的边，则无法形成一个连续段

于是不妨考虑设 $f_{l,r}$ 为当前最后一个连续段为 $[l,r]$ 的最少花费，对删边费用做一个二维前缀和，就得到一个 $O(n^3)$ 的解法

---

## 作者：ZCETHAN (赞：8)

## 题意

一张有向图，初始有边 $\forall i\in[1,n-1],i\to i+1$，边权为 $0$。后来加入 $n\times (n-1)$ 条边，是对于每一对 $i,j(i\not ={j})$，连边 $i\to j$，若 $i<j$，边权为 $-1$，否则边权为 $1$。

删去后来加入的每条边都需要一定的代价，删去 $i\to j$ 需要花费 $A_{i,j}$，求使得图中不存在负环。

## Solution

若直接考虑去掉负环，发现负环的可能太多了，于是考虑转化题意。考虑什么地方会用到负环。**差分约束！** 于是我们把题目中每一条连边逆向翻译成差分约束的描述：

1. $x_i\ge x_{i+1}$
2. 若 $i<j$，则有：$x_i-1\ge x_j$
3. 若 $i>j$，则有：$x_i+1\ge x_j$

相当于说我们要在后面两条中删去一些条件使得不等式组有解。首先根据第一条，这是一个递减的序列。这样的话，一旦我们保留了边 $i\to j(i<j)$，那么边 $i\to k(k>j)$肯定是被保留的，因为 $x_i-1\ge x_j\ge x_k$，必然能够满足。同理，如果我们保留了边 $i\to j(i>j)$，那么边 $i\to k(j<k<i)$ 必然被保留。我们只需要考虑从哪里开始保留。

接下来考虑如何解决这个问题。实际上，我们就是需要构造一组解，使得不等式满足这个解的花费最小。由于我们需要构造一个非严格下降序列，容易想到用 $dp$ 来维护。根据上面的分析，我们知道，对于一个位置 $i$，它向后的连边，当且仅当 $x_i=x_j$ 需要删掉；向前的连边，当且仅当 $x_j\ge x_i+2$ 需要删掉。于是令 $dp_{i,j,k}$ 表示前 $i$ 个点，当前连续相等段的长度是 $j$，上一个连续相等段的长度是 $k$，所需要删去的最小花费。

这是可能有问题的，因为最终解不一定相邻两端中的数刚好是相差 $1$ 的。但你仔细一想，这样肯定不优，因为如果我把它调整到相差 $1$，凭空会有向前的边可以不删。

转移需要分讨，若当前 $j>1$，则：

$$
dp_{i,j,k}=dp_{i-1,j-1,k}+\sum_{p\le i-j-k}A_{i,p}+\sum_{p\in[i-j+1,i-1]}A_{p,i}
$$

我们对 $A$ 做前缀和优化上面的东西就可以做到 $O(1)$ 转移。

若当前 $j=1$，则：

$$
dp_{i,1,k}=\min_{l}\{dp_{i-1,k,l}+\sum_{p\le i-k-1}A_{i,p}\}
$$

虽然说可以对 $dp$ 前缀优化做到 $O(1)$ 转移，但是在 $dp$ 的每 $O(n)$ 个状态中才会有一个 $j=1$，所以暴力转移总复杂度还是 $O(n^3)$，没有优化的必要。

$dp$ 可以滚动一维优化空间。

然后直接在 $dp_{n,\sim,\sim}$ 中找到最小值就是答案。

**细节：** 注意当且仅当 $j=i$ 时 $k=0$ 是合法的，不然总是存在上一段。而 $j$ 是不能等于 $0$ 的。建议对 $i=1$ 特判。

## Code

```cpp
// Problem: 
//     [AGC036D] Negative Cycle
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc036_d
// Memory Limit: 1 MB
// Time Limit: 2000 ms

#include<bits/stdc++.h>
#define ll long long
#define inf (1<<30)
#define INF (1ll<<60)
#define pb emplace_back
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
#define all(a) a.begin(),a.end()
#define siz(a) (int)a.size()
#define clr(a) memset(a,0,sizeof(a))
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define pt(a) cerr<<#a<<'='<<a<<' '
#define pts(a) cerr<<#a<<'='<<a<<'\n'
#define int long long
using namespace std;
const int MAXN=510;
int A[MAXN][MAXN],dp[2][MAXN][MAXN];
int A1[MAXN][MAXN],A2[MAXN][MAXN];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n;cin>>n;
	rep(i,1,n) rep(j,1,n) if(i^j) cin>>A[i][j];
	rep(i,1,n) rep(j,1,n) A1[i][j]=A1[i-1][j]+A[i][j];
	rep(i,1,n) rep(j,1,n) A2[i][j]=A2[i][j-1]+A[i][j];
	memset(dp[1],0x3f,sizeof(dp[1]));
	dp[1][1][0]=0;
	rep(i,2,n){
		memset(dp[i&1],0x3f,sizeof(dp[i&1]));
		rep(k,1,i-1) rep(l,1-(k==i-1),i-k)
			dp[i&1][1][k]=min(dp[i&1][1][k],dp[(i-1)&1][k][l]+A2[i][i-k-1]);
		rep(j,2,i) rep(k,1-(j==i),i-j)
			dp[i&1][j][k]=dp[(i-1)&1][j-1][k]+A2[i][i-j-k]+A1[i-1][i]-A1[i-j][i];
	}
	int ans=INF;
	rep(j,1,n) rep(k,1-(j==n),n-j)
		ans=min(ans,dp[n&1][j][k]);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：11400F (赞：2)

## AGC036D Negative Cycle 题解

我们考虑这些负边的性质：

对于某一条负边 $i → j$，如果这条边是一定要保留的，那么把所有 $a\le i, b \ge j$ 的负边 $a → b$ 全部保留一定是最优的。

考虑怎么证明：如果一条负边 $i → j$ 他是有负环的，那么就一定有范围可以包裹住这条负边的正边。现在可以保留边 $i → j$，那么就说明没有可以包裹住这条负边的正边了。而且，$a → b$ 是建立在 $i → j$ 之上，并且范围还比他大，那么就更没有正边包裹住它了。所以这些边都是可保留的。

然后这就启发我们：最小的负边是最关键的。我们现在要判断这个图不合法的条件。如图：

![](https://s21.ax1x.com/2024/12/10/pAH6iYq.png)

一个正边包裹住了两个不交的负边，那么这样就是不合法的。因为你可以从第一个负边走到正边的开头，然后值为 $-2$，再经过正边走回负边开头，最后值为 $-1$。于是这样就不合法了。我们考虑应该如何规避这种情况。

出现这种情况的原因是因为正边太大、负边太小，导致一条正边可以包裹住很多条负边。我们可以让负边的范围变大，正边的范围变小。让你走了两条负边都没有一条正边包裹住。

于是我们可以使用隔板法，让每一条负边都跨过至少一个隔板，让每一条正边都跨过不多于一个隔板。于是这样你最多也就只有个 $0$ 环，不会出现负环。

相应地，为了满足这些限制，我们可以枚举这些隔板出现的位置。一个隔板肯定是安放在两个点之间的，我们就设两个隔板的中间为块，然后枚举块。

![](https://s21.ax1x.com/2024/12/10/pAH6D9P.png)

最终构成的边一定是这样子的。

我们设当前答案 $dp_{j,i}$ 为枚举到 $i$ 时，最后一个块为 $[j,i]$ 的最小代价。于是图上的这些边都可以被保留。我们再枚举一个块 $[k,j-1]$，表示从上一个块转移过来的。

对于新的块 $j\sim i$，我们要把这个块里所有的起点、终点都在这个块里的负边都给删掉。也就是加上所有起点、终点都在范围 $[j,i]$ 里的负边的代价和。而对于正边，它不能跨越多于 $1$ 个隔板，于是就要把起点在 $[j,i]$ 范围，终点在 $[1,k-1]$ 范围里的正边全部删掉。也就是加上这些正边的代价和。假设对于每一个 $k$，这次删除的负边代价和为 $neg_k$，这次删除的正边代价和为 $pos_k$，最后当前 $dp_{j,i}$ 就是 $\displaystyle\min_{0\le k < j}(dp_{k,j-1} + pos_k + neg_k)$。

我们可以用二维前缀和来维护起点、终点在某一区间范围的正边或负边的代价和。就可以用 $O(1)$ 求出 $pos$ 和 $neg$。最后最终答案就是 $\displaystyle\min_{1\le i\le n} dp_{i,n}$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 504;
typedef long long ll;
ll sumneg[N][N], sumpos[N][N];
//负边、正边的前缀和。
ll neg[N][N], pos[N][N];
int n;
void init(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            sumneg[i][j] = sumneg[i-1][j] + sumneg[i][j-1] - sumneg[i-1][j-1] + neg[i][j];
            sumpos[i][j] = sumpos[i-1][j] + sumpos[i][j-1] - sumpos[i-1][j-1] + pos[i][j];
        }
    }
}

ll posque(int l1, int r1, int l2, int r2){
    if(l2>r2) return 0;
    return sumpos[r1][r2] - sumpos[l1-1][r2] - sumpos[r1][l2-1] + sumpos[l1-1][l2-1]; 
}

ll negque(int l1, int r1, int l2, int r2){
    return sumneg[r1][r2] - sumneg[l1-1][r2] - sumneg[r1][l2-1] + sumneg[l1-1][l2-1]; 
}

ll dp[N][N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++) cin>>pos[i][j];
        for(int j=i+1;j<=n;j++) cin>>neg[i][j];
    }
    init();
    ll ans = 0x3f3f3f3f3f3f3f3f;
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            for(int k=0;k<j;k++){
                dp[j][i] = min(dp[j][i],
                dp[k][j-1] + posque(j,i,1,k-1) + negque(j,i,j,i));
            }
        }
    }
    for(int i=1;i<=n;i++){
        ans = min(ans, dp[i][n]);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：xht (赞：2)

## [Negative Cycle](https://atcoder.jp/contests/agc036/tasks/agc036_d)

### 题意

- 有一张 $n$ 个点的有向图，点的编号为 $0 \sim n - 1$。
- 一开始有 $n-1$ 条边，对于 $i\in [0,n-2]$，有边 $(i,i+1,0)$。
- 另外若 $i<j$，加边 $(i,j,-1)$；若 $i>j$，加边 $(i,j,1)$。这些边都可以删除，边 $(i,j)$ 删除的代价为 $a_{i,j}$。
- 你希望用最小的代价删除某些边，使得图中不存在负环。
- $n \le 500$，$a_{i,j} \le 10^9$。

### 题解

考虑差分约束模型，图中不存在负环等价于存在一组合法的差分约束的解。

将每个节点作为一个变量，第 $i$ 个节点对应的变量为 $x_i$。因为初始的边不能删去，所以一定有 $x_i \ge x_{i + 1}$。

令 $q_i = x_i - x_{i + 1}$，有 $q_i \ge 0$。

假设保留了一条边权为 $-1$ 的 $i \to j(i < j)$ 的边，有 $x_i - 1 \ge x_j$，即 $x_i - x_j \ge 1$，即 $q_i + q_{i + 1} + \cdots + q_{j - 1} \ge 1$；假设保留了一条边权为 $1$ 的 $i \to j(i>j)$ 的边，有 $x_i + 1 \ge x_j$，即 $x_j - x_i \le 1$，即 $q_j + q_{j + 1} + \cdots + q_{i - 1} \le 1$。

反过来想，如果确定了所有的 $q_i$，那么每一条边就应该尽可能地保留下来，这样代价最小。

对于边权为 $-1$ 的边，是区间和 $\ge 1$ 才能保留，也就是说如果区间和 $= 0$ 就必须删除；对于边权为 $1$ 的边，是区间和 $\le 1$ 才能保留，也就是说如果区间和 $\ge 2$ 就必须删除。

也就是说，对于一种 $q$ 的取值方案，$q_i = 0$ 的每个连续段，都对应着一系列的边权为 $-1$ 的边的删除，而区间和 $\ge 2$ 的区间也对应着边权为 $1$ 的边的删除。

可以发现如果出现了 $q_i \ge 2$，不如把它变成 $1$，这样一定更优，所以只需要考虑 $q$ 的取值为 $0/1$ 的情况。

考虑 DP，设 $f_{i,j}$ 表示最后一个 $1$ 取在 $q_i$ 处，倒数第二个 $1$ 取在 $q_j$ 处的情况下，前缀 $i$ 的代价的最小值。

转移枚举下一个 $1$ 的位置即可，二维前缀和预处理转移系数后，时间复杂度 $\mathcal O(n^3)$。

### 代码

```cpp
const int N = 507;
const ll inf = 1e18;
int n;
ll a[N][N], b[N][N], f[N][N], ans = inf;

inline ll calc(int k, int j, int i) {
	return b[j+1][i] + a[n][j] - a[n][k] - a[i][j] + a[i][k];
}

int main() {
	rd(n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j) rd(a[i][j]);
	for (int j = 1; j <= n; j++)
		for (int i = j; i; i--)
			b[i][j] = b[i+1][j] + b[i][j-1] - b[i+1][j-1] + a[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
	for (int i = 1; i < n; i++) {
		f[i][0] = calc(0, 0, i);
		ans = min(ans, f[i][0] + calc(0, i, n));
		for (int j = 1; j < i; j++) {
			f[i][j] = inf;
			for (int k = 0; k < j; k++)
				f[i][j] = min(f[i][j], f[j][k] + calc(k, j, i));
			ans = min(ans, f[i][j] + calc(j, i, n));
		}
	}
	print(ans);
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：2)

**sol of AGC036D**

没想到差分约束啊。其实后面的 dp 难度还好。

我们考虑不存在负环其实有个很好的限制：存在至少一组差分约束。

从 $1$ 开始标号。我们令 $p_i$ 表示一个点到虚拟源点 $0$ 的距离，显然 $p_i \geq p_{i + 1}$，我们靠考虑差分一下令 $o_i = p_i - p_{i + 1}$，则 $o_i \geq 0$。

考虑对于 $i < j$ 的边本质就是限制了 $x_i - 1 \geq x_j$ 即 $x_i - x_j \geq 1$，写成差分的形式即 $\sum_{k = i} ^ {j - 1} o_k \geq 1$。记这种边为一类边。

对于 $i > j$ 的边推一下，发现是 $\sum_{k = j} ^ {i - 1} o_k \leq 1$。记这种边为二类边。

我们发现若出现 $o_i \geq 2$ 显然不优于令 $o_i = 1$，因为两者都可以满足 $o_i \geq 0$ 且不会使得一个本身留下来的一类边被剔除（因为相当于不会影响区间和 $\geq 1$），但是却更有可能使得区间和 $\leq 1$，从而保留二类边。

有了这么个强大的性质，就直接对 $o$ 数组硬上 dp 就好了：设 $dp_{j,i}$ 表示倒数第二个 $1$ 在 $j$ 位置，最后一个 $1$ 在 $i$ 位置，我们枚举一个之前的状态 $dp_{k,j}$ 转移：

- 对于一类边要求区间和 $\geq 1$，则可新产生的左端点在 $[1 , j]$，右端点在 $[j + 1 , i]$ 内；

- 对于二类边，要求区间和 $\leq 1$，则可新产生的左端点在 $[k + 1,i]$，右端点在 $[j + 1 , i]$。

发现两类贡献都可以由若干个矩形拼成，预处理二维前缀和转移即可。

时间复杂度 $O(n ^ 3)$。



---

## 作者：xxr___ (赞：1)

### 闲话：
蒟蒻做过的为数不多的黑，记录一下了。
### 思路： 
我们令边权是 `1` 的边称为正边，边权 `0` 的边叫做零边，边权是 `-1` 的边称作负边。

性质：

- 最后肯定不会删去零边，因为删不删对答案无影响。
- 假设最后存在边 $i→j$ 那么肯定存在 $i'→j'$ 其中 $i',j'$ 满足 $i'\leq i∧j\leq j'$，其实很显然。
  - 证明：因为存在 $i→j$ 且不存在负环，也就是说 $i→j$ 后一直沿着零边走，然后又走到负边，走到一个位置走正边往回走，且满足正边的数量大于等于负边的数量，要不然就有负环了。图示如下：![](https://cdn.luogu.com.cn/upload/image_hosting/72zmc0jp.png)这个时候假设没有绿色的边，图是合法的，加入了绿色以后，由于他起点更前，终点更靠后，由于零边不能返回，所以经过的正边的数量是递增的，而且负边的数量递减的，你可以感性理解成，这个绿边能经过的负边红的都能经过，但是红的经过的正边绿色一定也能经过。然后就证得不会因为加入 $i'→j'$ 而凭空产生负环。

然后你就发现实际上就是把序列分段，然后每段算贡献，这个时候如果一个段内负边起始点和终点都包含就肯定不合法，如果正边跨了两段及以上就不合法。

设 $f_{l,r}$ 表示最后一段选区间 $[l,r]$ 然后转移枚举一个 $k$ 表示上一个区间是 $[k,l-1]$ 然后对于同段的负边已经那些不合法的负边二维前缀和就可以解决。

也就是那些左端点是 $[1,k-1]$ 的连向 $[l,r]$ 的正边和 $[l,r]$ 中的 $i$ 连向 $[l,r]$ 中的 $j$ 满足 $i<j$ 的负边都是不合法的。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define pre(i,l,r) for(int i=(l);i>=(r);--i)
const int N=505;
int f[N][N];
int n,a[N][N],b[N][N];
int sum1(int l,int r,int ll,int rr){
	return a[ll][rr]-a[ll][r-1]-a[l-1][rr]+a[l-1][r-1];
}
int sum2(int l,int r,int ll,int rr){
	return b[ll][rr]-b[ll][r-1]-b[l-1][rr]+b[l-1][r-1];
}
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	rep(i,1,n){
		rep(j,1,i-1) cin>>a[i][j];
		rep(j,i+1,n) cin>>b[i][j];
	}
	memset(f,0x3f,sizeof f);
	rep(i,1,n)
		rep(j,1,n){
			a[i][j]+=a[i][j-1]+a[i-1][j]-a[i-1][j-1];
			b[i][j]+=b[i][j-1]+b[i-1][j]-b[i-1][j-1];
		}
	f[0][0]=0;
	rep(i,1,n){
		rep(j,1,i){
			rep(k,0,j-1){
				f[j][i]=min(f[j][i],f[k][j-1]+sum1(j,1,i,k-1)+sum2(j,j,i,i));
			}
		}
	}
	int ans=1e18;
//	rep(i,1,n){
//		rep(j,i,n){
//			cout<<"f["<<i<<"]["<<j<<"]="<<f[i][j]<<'\n';
//		}
//	}
	rep(i,1,n) ans=min(ans,f[i][n]);
	cout<<ans;
	return 0;
}
//tomxi
```

---

## 作者：OrangeEye (赞：1)

本文中将所有下标倒置，即原题中 $i\rightarrow j$ 全部改为 $n-1-i\rightarrow n-i-j$。

首先考虑差分约束模型：即给每个点赋权值 $x_i$ 之后满足对于每条边 $i\rightarrow j$ （边权为 $w$）满足 $x_j\leq x_i+w$，有负环等价于无解。

由于固定有 $i\rightarrow i-1$，边权为 $0$ 的边，所以 $x_i\leq x_{i+1}$。对于两个点 $i<j$，如果 $x_j-x_i=0$，那么需要割掉 $j\rightarrow i$，权值为 $-1$ 的边，否则需要割掉 $i\rightarrow j$，权值为 $1$ 的边。

于是可以 DP：$f_{i,j,k}$ 表示考虑到第 $i$ 个点，编号最小的和 $i$ 权值相等的点是 $j$，最小的和 $i$ 权值相差不超过 $1$ 的点是 $k$，枚举每个点是前一个点加 $0$ 还是加 $1$ 转移即可。因为加更多肯定不优。注意到每个点向前割掉的边都是连续的两段，前缀和优化即可做到 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define endl '\n'
mt19937 rnd(537462565);
const int inf=0x3f3f3f3f3f3f3f3f;
void cmn(int &x,int y){if(x>y)x=y;}
int n,a[505][505],pre1[505][505],pre2[505][505],dp[505][505][505],ans=inf;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=n;i;i--)for(int j=n;j;j--)if(i!=j)cin>>a[i][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)pre1[i][j]=pre1[i][j-1]+a[i][j],pre2[i][j]=pre2[i-1][j]+a[i][j];
	memset(dp,0x3f,sizeof(dp));
	dp[1][1][1]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			for(int k=1;k<=j;k++)if(dp[i][j][k]<inf){
				cmn(dp[i+1][j][k],dp[i][j][k]+pre1[i+1][i]-pre1[i+1][j-1]+pre2[k-1][i+1]);
				cmn(dp[i+1][i+1][j],dp[i][j][k]+pre2[j-1][i+1]);
			}
	for(int i=1;i<=n;i++)for(int j=1;j<=i;j++)cmn(ans,dp[n][i][j]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：LgDan321 (赞：1)

## AT_agc036_d

存在一个 $N$ 个点的有向图，标号从 $0$ 开始。

这张图有两类边：

1. 对于 $i=1...N-1$，存在 $i-1\to i$，边权为 $0$，无法删除。
2. 对于所有 $0\le i,j\le N-1\ \{i\ne j\}$，存在 $i\to j$。边权当 $i<j$ 时为 $-1$，否则为 $1$，删除代价为 $A_{i,j}$。

求最小删除代价，使得图中不存在负环。$1\le N\le 500$，$1\le A_{i,j}\le 10^9$。

---

这个题有两种出发点不同的思考角度，但是但是结果是差不多的，本文将分别介绍。笔者按照个人习惯，改为从 $1$ 开始的标号，并将 $N,A$ 改为小写。

### 差分约束

对于不存在负环的限制，试图找到较好的刻画方式。在众多方法中，只有 SPFA 和差分约束是针对负环的。SPFA 显然在这里没用，所以考虑负环如何对题目产生限制。

首先定义差分约束变量 $x_1,\dots,x_n$。根据差分约束公式，对于任意边 $i\to j$，均需满足 $x_i+w_{i,j}\ge x_j$。

- 对于 $i\to i+1$，有 $x_i\ge x_{i+1}$，于是定义 $b_i=x_i-x_{i+1}\ge 0$。
- 对于 $i\to j\ \{i<j\}$，有 $x_i-1\ge x_{j}$，于是 $x_i-x_j=\sum_{k=i}^{j-1}b_k\ge 1$。
- 对于 $i\to j\ \{i>j\}$，有 $x_i+1\ge x_{j}$，于是 $x_j-x_i=\sum_{k=i}^{j-1}b_k\le 1$。

此时 $b_{1},b_2,...,b_{n-1}$ 正好刻画了变量间的关系。分析得到 $b_i\in \{0,1\}$，因为 $b_i\ge 2$ 显然比 $b_i=1$ 更容易破环 $\sum b_k\le 1$的限制。到此为止可以看出题目会和 dp 有关。于是尝试 $dp_{i,j,k}$ 表示考虑到前 $i$ 个 $b$ 数组的值，上一个 $1$ 位于 $j$，上上个位于 $k$。转移时试图枚举下一个值是否为 $1$，提前计算矩阵的二维前缀和方便计算贡献。复杂度就能做到 $\mathrm O(n^3)$。

### 调整分析

首先明确一个基本的观点：题目中的负环里一定有至少两条负权边。所以直接分析保留的负权边会有什么性质。对于 $i\to j\ \{i\le j\}$ 被保留，所有 $(x,y)\ \{x\le i\wedge y\ge j\}$ 均会被保留。因为删除了这些边，同样可以通过 $x\to_0 i\to j\to_0 y$ 的方法到达。但是有了这个并不能直接得出很好的结论，比如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ewkbq2ih.png)

绿色边是不包含其他任何负权边的极短的负权边，红色边是唯一一个删掉的正权边，这个图看起来 3 个不同的极短边没有任何关系，但是实际上：

![](https://cdn.luogu.com.cn/upload/image_hosting/6hmzi80z.png)

黄色边指出了一个非常不显然地不合法的情况。所以这时候加入紫色边其实不影响连通性。于是看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/q7tvcnrz.png)

我们按照 3 种红边，分别讨论紫色边是不影响的：

- 如果存在 1 类红边，直接改为研究第一个绿边和这条红边，这样第二条边的起始点会向后移动，可以在有限步内调整到不存在 1 类红边。
- 如果存在 2 类红边，按照刚刚的构造，加上紫色边不影响环的存在性。
- 如果存在 3 类红边，比第 2 类更加明显，紫色边不影响环的存在性。
- 如果不存在这 3 类红边的任意一种，如果把图反过来，入边形如这样的情况是一样分析的。如果入边也不存在，说明绿色边左右没有影响它们的边，所以直接加上紫色边，图依旧合法。

通过上述论证，我们证明了所有极小的负权边不会有交。于是对着没有交的极小负权 dp 就好了。定义 $dp_{i,j,k}$ 表示考虑到第 $i$ 个点，上一个负权边是 $j\to k$ 的最小代价。此时可以得出另外的转移。

调整分析的方法有点抽象，感觉还是差分约束做法更直接更好。于是有一个差分约束的 code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;
constexpr int N=502;
bool a1;
int n;
ll a[N][N],dp[N][N];
ll matrix(int l1,int l2,int r1,int r2){
    return a[l2][r2]-a[l2][r1-1]-a[l1-1][r2]+a[l1-1][r1-1];
}
bool a2;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cerr<<"static memory::"<<&a1-&a2<<'\n';
    cin>>n;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(i==j)continue;
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            a[i][j]=a[i][j]+a[i][j-1]+a[i-1][j]-a[i-1][j-1];
        }
    }
    memset(dp,0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<n;++i){
        for(int j=i-1;j>=0;--j){
            for(int k=j;k>=0;--k){
                dp[i][j]=min(dp[i][j],dp[j][k]);
            }
        }
        for(int j=i;j>=0;--j){
            for(int k=j;k>=0;--k){
                if(dp[j][k]!=dp[n][n]){
                    dp[j][k]+=matrix(j+1,i+1,i+1,i+1);
                    if(k)dp[j][k]+=matrix(i+1,i+1,1,k);
                }
            }
        }
    }
    ll ans=dp[n][n];
    for(int i=0;i<=n;++i){
        for(int j=0;j<=n;++j)ans=min(ans,dp[i][j]);
    }
    cout<<ans<<'\n';
    cerr<<"time::"<<clock()<<'\n';
    return 0;
}
```

---

## 作者：tribool4_in (赞：1)

不会差分约束。

将初始 $i\to i+1$ 的边称为链边，权值为 $1$ 称为正边，$-1$ 称为负边。

首先由于初始的链边不能被删除，很多种负环的方案都能通过将一段权值和为 $0$ 的 $i\to j\ (i<j)$ 的复杂路径换成直接走链边来化简。经过手玩可以发现，只需要考虑所有“平面负环”，因为其他负环一定可以化简得到“平面负环”，在“平面负环”被断掉后一定也会被断掉（感性理解）。

这里“平面负环”指的是先只通过负边和链边向前走，再只通过正边走回起点的环。

此时极妙地考虑根据最终方案的负边将序列分段，使得每一段不存在内部连负边（即负边的端点必须在两个段内）。此时可以发现，合法的方案中的每条正边都不应跨过大于等于一段（即正边需要两端在同一段内或在相邻段中）。必要性显然（因为如果存在则直接构成了负环），充分性考虑在此条件下一条正边构成的链，其跨过的段数不少于其边数，而段数不少于跨过这些段需要的负边个数，因此如果成环，其权值和一定不为负。

因此设 $dp_{i,j}$ 表示考虑前 $i$ 个点且当前段为 $[j,i]$ 合法的最小代价。转移考虑从 $dp_{j-1,k}$ 转移过来。发现需要满足 $[j,i]$ 内部没有负边连接，且 $[j,i]$ 没有连接到 $[1,k-1]$ 的正边，二维前缀和即可。时间复杂度 $O(n^3)$。

代码与差分约束做法殊途同归。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e2 + 10, INF = 2e18;
int n, a[N][N], b[N][N], sa[N][N], sb[N][N], dp[N][N];
int getsum(auto v, int i1, int i2, int j1, int j2) { return v[i2][j2] - v[i1 - 1][j2] - v[i2][j1 - 1] + v[i1 - 1][j1 - 1]; }
void chkmin(int &x, int v) { x = min(x, v); }
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i) cin >> a[i][j];
            if (j > i) cin >> b[i][j];
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sa[i][j] = a[i][j] + sa[i][j - 1] + sa[i - 1][j] - sa[i - 1][j - 1];
            sb[i][j] = b[i][j] + sb[i][j - 1] + sb[i - 1][j] - sb[i - 1][j - 1];
        }
        for (int j = 1; j <= i; j++)
            for (int k = 0; k < j; k++) chkmin(dp[i][j], dp[j - 1][k] + getsum(sb, j, i, j, i) + getsum(sa, j, i, 1, k - 1));
    }
    int ans = INF;
    for (int i = 1; i <= n; i++) ans = min(ans, dp[n][i]);
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：_fairytale_ (赞：1)

**前言：本题的点从 $0$ 标号到 $n-1$，这是坏文明，因此本文把标号都 $+1$，相当于点从 $1$ 到 $n$ 编号。同时本文的 $A_{i,j}$ 为删掉边 $(i,j)$ 的代价，与题面略有区别。**

神！不存在负环相当于差分约束有解。所以不妨把 $n$ 个点看作 $n$ 个变量 $x_1\dots x_n$，在保证差分约束有解的前提下使删掉的边代价总和最小。

设 $d_i=x_i-x_{i+1}$（注意这里是前减后），则 $x_i-x_j=d_i+\dots+d_{j-1}$。

- $i\to i+1$ 的边等价于 $x_i\ge x_{i+1}$，即 $d_i\ge 0$。称这种边为**原边**。
- $i\to j(i<j)$ 的边等价于 $x_i-1\ge x_j$，即 $d_i+\dots+d_{j-1}\ge 1$。称这种边为**正向边**。
- $i\to j(i>j)$ 的边等价于 $x_i+1\ge x_j$，即 $d_j+\dots+d_{i-1}\le 1$。称这种边为**反向边**。

注意到对于一段 $d=0$ 的区间，我们要删除其中所有正向边；对于一段 $\sum d>1$ 的区间，我们要删除其中所有反向边。

显然 $d_i\in\{0,1\}$。因为假如存在一个 $d_i>1$，将它变为 $1$ 必然不劣。

不难想到 DP。设 $f[j][i]$ 表示的是考虑前 $i$ 个位置，第 $i$ 个位置填了 $1$，上一个填 $1$ 的位置是 $j$ 的最小代价。

有转移方程：
$$
f[j][i]=\min_{k<j}\{f[k][j]+\sum_{a=i+1}^{n}\sum_{b=k+1}^{j}A_{a,b}\}+\sum_{a=j+1}^{i-1}\sum_{b=a+1}^{i}A_{a,b}
$$

初值的话，$f[0][i]=\sum_{a=1}^{i-1}\sum_{b=a+1}^{i}A_{a,b}$。

然后两个 $\sum$ 可以通过预处理解决。

时间复杂度 $\mathcal O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define re register
#define il inline
#define ll long long
#define rep(x,qwq,qaq) for(re int (x)=(qwq);(x)<=(qaq);++(x))
using namespace std;
#define inf 0x3f3f3f3f3f3f3f3f
#define maxn 550
int n,m;
ll ans=inf;
ll A[maxn][maxn],pre[maxn][maxn];
ll query(int lx,int ly,int rx,int ry){//左上角和右下角 
	return pre[rx][ry]-pre[lx-1][ry]-pre[rx][ly-1]+pre[lx-1][ly-1];
} 
ll f[maxn][maxn];
ll sum_0[maxn][maxn];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n;
    rep(i,1,n){
    	rep(j,1,n){
    		if(i==j)continue;
    		cin>>A[i][j];
    		pre[i][j]=pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+A[i][j];
		}
	}
	rep(i,1,n){
		rep(j,0,i-1){
			rep(a,j+1,i-1){
				sum_0[j][i]+=query(a,a+1,a,i);
			}
		}
	}
	memset(f,0x3f,sizeof f);
	rep(i,1,n)f[0][i]=sum_0[0][i];
	rep(i,1,n-1){
		rep(j,0,i-1){
			rep(k,0,j-1){
				f[j][i]=min(f[j][i],f[k][j]+query(i+1,k+1,n,j)+sum_0[j][i]);
			}
			ans=min(ans,f[j][i]+sum_0[i][n]);
		}
	}
	cout<<ans;
	return 0;
}
/*
input:
3
3 2 
2 1 
3 1 
output:
1
*/
```

---

## 作者：UKE_Automation (赞：0)

### AGC036D Negative Cycle

[$\text{Link}$](https://atcoder.jp/contests/agc036/tasks/agc036_d)

首先我们把整张图当成一个差分约束模型，这样没有负环就代表不等式组有解。

由于原图中 $i\to i+1$ 的边不能删去，所以我们可以得到 $x_i\ge x_{i+1}$。移项后 $x_i-x_{i+1}\ge 0$，令 $c_i=x_i-x_{i+1}$，则有 $c_i\ge 0$。

然后考虑新加的边，对于一条 $i\to j(i<j)$ 的边，其对应限制条件为 $x_i-1\ge x_{j}$，也就是 $x_i-x_{j}\ge 1$。改写一下可以知道 $c_i+c_{i+1}+\cdots+c_{j-1}\ge 1$。同理如果有一条 $j\to i(i<j)$ 的边，那么条件就是 $c_{i}+c_{i+1}+\cdots+c_{j-1}\le 1$。

然后将这个过程反过来，假如我们知道了 $c_i$ 的取值，那么为了满足这个结果，有一些限制条件就要被删掉。根据上面的分析不难发现，如果有一段区间和等于 $0$ 说明要删一条 $-1$ 边，如果有一段区间和 $\ge 2$ 说明要删一条 $1$ 边。进一步分析发现，如果 $c_i\ge 2$，那么把它改成 $1$ 一定更优，因为这样不会增加区间和为 $0$ 的区间且会至少减少一个区间和 $\ge 2$ 的边。于是 $c_i\in \{0,1\}$。

那么这样的话我们就可以直接 dp 了，令 $dp(i,j)$ 表示当前令 $c_i=1$，上一个 $c$ 为 $1$ 的位置是 $c_j$，删去的边的权值和的最小值。枚举上一个状态 $dp(j,k)$，转移的时候用二维前缀和计算一下删去的边的权值总和即可。复杂度是 $O(n^3)$ 的。

```cpp
#include <bits/stdc++.h>
#define int long long 

using namespace std;

const int Maxn = 5e2 + 5;
const int Inf = 1e18;

int n;
int s1[Maxn][Maxn], s2[Maxn][Maxn];

int q1(int l1, int r1, int l2, int r2) {
	return s1[r1][r2] - s1[r1][l2 - 1] - s1[l1 - 1][r2] + s1[l1 - 1][l2 - 1];
} 

int q2(int l1, int r1, int l2, int r2) {
	return s2[r1][r2] - s2[r1][l2 - 1] - s2[l1 - 1][r2] + s2[l1 - 1][l2 - 1];
}

int dp[Maxn][Maxn];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= i - 1; j++) cin >> s1[i][j];
		for(int j = i + 1; j <= n; j++) cin >> s2[i][j];
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			dp[i][j] = Inf;
			s1[i][j] += s1[i - 1][j] + s1[i][j - 1] - s1[i - 1][j - 1];
			s2[i][j] += s2[i - 1][j] + s2[i][j - 1] - s2[i - 1][j - 1];
		}
	}
	for(int i = 1; i <= n; i++) dp[i][0] = q2(1, i, 1, i);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j < i; j++) {
			for(int k = 0; k < j; k++) {
				dp[i][j] = min(dp[i][j], dp[j][k] + q2(j + 1, i, j + 1, i) + q1(j + 1, i, 1, k));
			}
		}
	}
	int ans = Inf;
	for(int i = 0; i < n; i++) {
		ans = min(ans, dp[n][i]);
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

难点在于联想到**差分约束**。

将所有边边权翻转，变为不能有正环。而对最长路的差分约束恰好满足这一要求。

具体的，设 $x_i$ 为 $1$ 到 $i$ 的最长路。边 $(u,v,w)$ 的含义是 $x_u + w \le x_v$。

所以：

- $x_i \le x_{i+1}$；
- $\forall i < j$，如果 $x_i + 1 > x_j$ 则要支付 $A_{i,j}$ 的代价；
- $\forall i < j$，如果 $x_i + 1 < x_j$ 则要支付 $A_{j,i}$ 的代价。

所以问题就变味，对于所有的 $x$ 最优化。注意到可以将 $x$ 变为差分。则限制 $2$ 相当于：如果一段区间里差分全是 $0$ 则要支付 $A_{i,j}$ 的代价。限制 $3$ 相当于：如果一段区间里差分和大于等于 $2$ 则要支付 $A_{j,i}$ 的代价。

首先重要观察：差分数组所有元素都 $\in \{0,1\}$。因为注意到如果有 $\ge 2$ 的元素，将其改为 $1$ 不会影响限制 $2$，而且在限制 $3$ 中支付更少的费用。

这样可以直接暴力了：设 $dp_{i,j}$ 为，差分数组第 $i$ 个位置是 $1$，上一个是 $1$ 的位置是 $j$，则长度为 $i$ 的前缀所需要的最小代价是多少。

转移暴力枚举，用二位前缀和预处理一些东西即可。复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=500+10;
int n,a[MAXN][MAXN],lim1[MAXN][MAXN],lim2[MAXN][MAXN],dp[MAXN][MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) ffor(j,1,n) if(j!=i) cin>>a[i][j];
	ffor(i,1,n) ffor(j,i+1,n) lim1[i][j-1]=a[i][j],lim2[i][j-1]=a[j][i];
	ffor(i,0,n) ffor(j,1,n) lim1[i][j]+=lim1[i][j-1];
	roff(i,n,0) ffor(j,0,n) lim1[i][j]+=lim1[i+1][j];
	ffor(i,1,n) ffor(j,0,n) lim2[i][j]+=lim2[i-1][j];
	ffor(i,0,n) roff(j,n,0) lim2[i][j]+=lim2[i][j+1];
	memset(dp,0x3f,sizeof(dp));
	int ans=LONG_LONG_MAX;
	ffor(i,1,n) {
		dp[i][0]=lim1[1][i-1]+lim2[0][i];
		ffor(j,1,i-1) ffor(k,0,j-1) dp[i][j]=min(dp[i][j],dp[j][k]+lim1[j+1][i-1]+lim2[j][i]-lim2[k][i]);
	}
	ffor(i,0,n-1) ans=min(ans,dp[n][i]);
	cout<<ans;
	return 0;
}
```

---

