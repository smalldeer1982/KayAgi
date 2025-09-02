# [ARC184D] Erase Balls 2D

## 题目描述

在二维平面上有 $N$ 个编号从 $1$ 到 $N$ 的球，第 $i$ 个位于 $(X_i, Y_i)$。其中，$X = (X_1, X_2, \cdots, X_n)$ 以及 $Y = (Y_1, Y_2, \cdots, Y_n)$ 分别是一个 $1, 2, \cdots, n$ 的排列（译注：即横纵坐标分别两两不同）。

你可以执行任意次以下操作：

- 从剩下的球中选择一个球，记为 $k$。对剩下的每个球 $i$，若满足「$X_i < X_k
$ 且 $Y_i < Y_k$」或「$X_i > X_k$ 且 $Y_i > Y_k$」（译注：即两球坐标间有二维偏序关系），将其移除。

求操作结束后，可能的剩下球的集合的数量，对 $998244353$ 取模。

- $1 \le N \le 300$

## 样例 #1

### 输入

```
3
1 3
2 1
3 2```

### 输出

```
3```

## 样例 #2

### 输入

```
4
4 2
2 1
3 3
1 4```

### 输出

```
3```

# 题解

## 作者：EuphoricStar (赞：10)

**转化计数对象。**

直接数最终剩下的球的集合似乎并不好做。考虑数**选择的球的集合**（显然选择的顺序不重要，只有选择了哪些球重要）。

先把所有球按 $x$ 坐标从小到大排序。设我们选择的球的下标为 $i_1 < i_2 < \cdots < i_k$。那么能选择这些球当且仅当 $y_{i_1} > y_{i_2} > \cdots > y_{i_k}$。因为若存在一对 $(p, q)$（$p < q$）使得 $y_{i_p} < y_{i_q}$，那么先选择任何一个都会导致另一个被删除。

但是很显然你直接这样数会算重，原因是一个最终剩下的球的集合可能对应多个选择的球的集合。**考虑增加限制**，数「选了集合外的任意一个球都会导致至少有一个球被删」的选择的球的集合。这样，选择的球的集合可以和最终剩下的球的集合一一映射。

判定一个选择的球的集合是否满足「选了集合外的任意一个球都会导致至少有一个球被删」，只需要判断对于所有相邻的球 $(i_p, i_{p + 1})$，把 $i_p < j < i_{p + 1}$ 且 $y_{i_p} > y_j > y_{i_{p + 1}}$ 的球 $j$ 拿出来，是否对于每个 $j$ 都满足「在这些球中 $j$ 前面有 $y$ 比它小的球」或「在这些球中 $j$ 后面有 $y$ 比它大的球」。

考虑直接 DP（为了方便可以添加两个坐标分别为 $(0, n + 1), (n + 1, 0)$ 的球）。设 $f_i$ 为考虑到前 $i$ 个球且选了第 $i$ 个球的方案数。转移枚举上一个在选择的球的集合内的球 $j$，$O(n)$ 判定 $j$ 能否转移到 $i$ 即可。

时间复杂度 $O(n^3)$。

[code](https://atcoder.jp/contests/arc184/submissions/58052510)

---

## 作者：Lgx_Q (赞：3)

首先 $n$ 个点，可以用排列 $P_{1...n}$ 表示，$P_i$ 为横坐标为 $i$ 的点的纵坐标。

考虑对点 $i$ 的一次操作的效果，会把点 $i$ 左下部分和右上部分删掉。如果进行多次操作，操作的点之间一定不会相互删除。

具体的，设 $S$ 为操作的点集，那么 $\forall i,j\in S  \land 1\le i < j\le n, \ P_i > P_j$。进一步的，我们可以发现会保留的点集如下所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/lk1lhiqn.png?x-oss-process=image/resize,m_lfit,h_250,w_600)

其中剩下的点为：红色矩形覆盖的点和图中标出的 $S$ 中的点。

对于一种剩余点集方案，为了防止算重，我们拎出所有满足如下条件的点 $x$：

+ 对于剩余的任意一点 $i$，若 $i<x$ 则 $P_i > P_x$，若 $i>x$ 则 $P_i < P_x$。

如果我们把 $S$ 强制定义为这些拎出来的点的集合，即可构成从 $S$ 到最终方案的双射。

设 $f[i]$ 表示考虑了点 $1...i$ 并且 $i \in S$ 的方案数。

转移枚举上一个 $S$ 中的点 $j$ 且满足 $P_j > P_i$，可以转移的合法条件是 $j\sim i$ 这个矩形中拎不出满足条件的点 $x$，这个可以暴力判断。所以时间复杂度为 $O(n^3)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define mkp make_pair
#define pir pair <ll, ll>
#define pb emplace_back
#define i128 __int128
using namespace std;
const ll maxn = 310, mod = 998244353;
ll n, a[maxn], c[maxn], ok[maxn][maxn];
ll f[maxn];
int main() {
	scanf("%lld", &n);
	for(ll i = 1; i <= n; i++) {
		ll x, y; scanf("%lld%lld", &x, &y);
		a[x] = y;
	} a[0] = n + 1, f[0] = 1;
	for(ll i = 1; i <= n + 1; i++) {
		for(ll j = 0; j < i; j++)
			if(a[j] > a[i]) {
				memset(c, 0, sizeof c);
				ll val = 1e18;
				for(ll k = j + 1; k < i; k++) {
					if(a[k] > a[j] || a[k] < a[i]) continue;
					if(a[k] < val) val = a[k];
					else c[k] = 1;
				} val = -1e18; ll ok = 1;
				for(ll k = i - 1; k > j; k--) {
					if(a[k] > a[j] || a[k] < a[i]) continue;
					if(a[k] > val) val = a[k];
					else c[k] = 1; ok &= c[k];
				}
				if(ok) f[i] = (f[i] + f[j]) %mod;
			}
	} printf("%lld", f[n + 1]);
	return 0;
}
```

---

## 作者：cpchenpi (赞：3)

### 写在前面

这场比赛难度还是很高的，特别是后几题难度比较平滑。感觉赛时就应该 all in D 题的，看 B 题就输麻了。

### 题意简述

在二维平面上有 $N$ 个球（$1 \le N \le 300$），第 $i$ 个位于 $(X_i, Y_i)$。它们的横纵坐标分别两两不同。

你可以执行任意次以下操作：

- 从剩下的球中选择一个球，记为 $k$。对剩下的每个球 $i$，若坐标与 $k$ 有二维偏序关系，将其移除。

求操作结束后，可能的剩下球的集合的数量，对 $998244353$ 取模。

### 题解

首先，球的操作顺序无关，因为操作中的两个球之间一定不存在偏序关系。那么很容易使用 DP 求出操作集合的个数。

但我们发现要求的是剩下的球集合的数量，而不是操作球集合的数量；那么在计数时要求“应操作尽操作”即可。

具体地，若一个合法的剩下的球集合为 $S$ ，考虑记 $f(S)$ 为 $S$ 中满足以下条件的球的集合：

- 操作一次不会删除 $S$ 中其它球，即没有其它球与 $i$ 有偏序关系。

我们发现 $f(S)$ 与 $S$ 之间是一一对应的。

- 对 $f(S)$ 中的所有点做一次操作，即可从 $f(S)$ 构造唯一合法的 $S$。

接下来分析具体如何计数 $f(S)$。按横坐标从左到右编号。记 $f_i$ 为考虑到第 $i$ 个球，且 $f(S)$ 中最后一个球是 $i$ 的方案数。则 $i$ 可以从 $j < i$ 转移，当：

- 两球之间没有偏序关系，即 $y_j > y_i$。

- 两球之间没有可以操作并不影响 $S$ 的球 $k$。具体地，对矩形 $(j, i) \times (y_i, y_j)$ 内的球集合 $T$，不存在一个球与 $T$ 内其他球没有偏序关系。

  - 可以枚举 $k$，并使用二维前缀和检查这个条件。
 
时间复杂度 $O(n^3)$。

### 代码示例

``` cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;
constexpr int N = 300 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> y(n + 2), x(n + 2);
    x[0] = y[0] = n + 1; x[n + 1] = y[n + 1] = 0;
    for (int i = 1; i <= n; i++) {
        int u, v; 
        cin >> u >> v;
        y[u] = v, x[v] = u;
    }
    vector pres(n + 2, vector<int>(n + 2));
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n + 1; j++) {
            pres[i][j] = pres[i][j - 1] + pres[i - 1][j] - pres[i - 1][j - 1] + (y[i] == j);
        }
    }
    auto query = [&](int i, int j, int x, int y) {
        return pres[x - 1][y - 1] - pres[x - 1][j] - pres[i][y - 1] + pres[i][j];
    };
    vector<int> dp(n + 2);    
    dp[0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < i; j++) {
            if (y[j] < y[i]) continue;
            bool trans = true;
            for (int k = j + 1; k < i; k++) {
                if (y[j] > y[k] && y[k] > y[i]) {
                    if (query(j, y[i], k, y[k]) + query(k, y[k], i, y[j]) == 0) trans = false;
                }
            }
            if (trans) dp[i] += dp[j], dp[i] -= (dp[i] >= MOD) ? MOD : 0;
        }
    }
    cout << dp[n + 1] << "\n";
}
```

---

## 作者：Gordon_Song (赞：2)

### upd

2024/9/23：感谢评论区的提醒。修改了对于 dp 数组的定义，以及对转移条件的描述（原来的理解出现了一定的偏差，但居然也对了）

### sol

一个神奇的 dp。

首先对输入的数按 $x$ 进行排序，令 $a_i$ 表示排序后第 $i$ 个坐标的 $y$ 值。 

有一个结论：假设选出了集合 $S$ 表示要对这些位置进行操作，那么对于 $S$ 中任意两个数对 $(i,a_i)$，$(j,a_j)$，一定有要么 $i < j$ 且 $a_i > a_j$，要么 $i>j$ 且 $a_i < a_j$。证明是显然的，否则在操作 $(i,a_i)$ 是就已经把 $(j,a_j)$ 给删掉了。根据此结论也可以发现 $S$ 中的数也会留下来。

设 $dp_i$ 表示 $1$ 到 $i$ 留在集合中最后一个位置是 $i$ 的方案数，**且对 $i$ 点进行了操作**。

转移时枚举上一个选的位置 $j$ 满足 $a_j > a_i$，进行转移。

然而这样转移是错误的。具体而言，考虑下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/xt2wucza.png)

容易发现对于一些情况来说，操作 $(i,k,j)$ 和操作 $(i,j)$ 是一样的，所以要排掉这些情况。具体来说，如果有一个位置 $k$ 满足 $i < k < j$，$a_i > a_k > a_j$（这是三者能同时选择进行操作的基本条件），且图中所示 $A$，$B$ 区域都没有数时，选择执行 $(i,k,j)$ 和 $(i,j)$ 本质没有区别，此时不能从 $i$ 转移到 $k$

可以发现，这道题本质上是要在二维平面上选取若干个矩形，满足相邻的任意两个矩形都有一个公共点（可结合图以及想象力进行理解），那么这个 dp 相当于是在枚举那个矩形之间的公共点。

---

## 作者：zhm080507 (赞：1)

# [AT_arc184_d [ARC184D] Erase Balls 2D](https://atcoder.jp/contests/arc184/tasks/arc184_d)

### 题目大意

在给定给定的点集选择一些未删除的点，删去它们的左下和右上的所有点，求最后剩下的点集方案数。

### 算法分析

容易发现，剩余的点一定是在从左上到右下链接的几个矩形中的。

我们发现这样保留点的方案统计一定是基于要操作的点来统计的，且这些点一定位于各矩形相交的端点上。然后我们发现一个操作点的方案数是可以由它下方的操作点转移的。

考虑具体的从 $j$ 转移到 $i$ 方案（显然只有 $j$ 在 $i$ 的右下才合法）：

- 首先我们可以发现如果点 $i$ 与 $j$ 形成的矩形中没有点是一定可以转移的。
- 然后发现如果这个矩形中不存在一个点如果它操作了也不会删去这个矩形中其他任意点，那么我们认为转移是合法的。

解释一下第二条：因为如果存在这样的点 $k$，显然是可以由 $j$ 转移到 $k$ 再转移到 $i$ 的（这两种方案结果显然相同）。

最后就是一堆细节，具体可以参照代码。

### code

```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N=400,mod=998244353;
int n,t[N],f[N],x,y;
bool vis[N];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		t[y]=x;
	}//因为它保证不重，这样就少了一次排序 
	t[0]=n+1;t[n+1]=0;
	//方便统计答案，加入两个没有影响的边界点
	f[0]=1;
	for(int i=1;i<=n+1;i++){
		for(int j=0;j<i;j++){
			if(t[i]>t[j]) continue;
			int mx=400;
			for(int k=j+1;k<i;k++){
				vis[k]=0;
				if(t[k]<t[i]||t[k]>t[j]) continue;
				if(t[k]<mx) mx=t[k];
				else vis[k]=1;
			}
			mx=-1;
			for(int k=i-1;k>j;k--){
				if(t[k]<t[i]||t[k]>t[j]) continue;
				if(t[k]>mx) mx=t[k];
				else vis[k]=1;
			}//判断有没有左下右上都没有点的k 
			bool flag=1;
			for(int k=j+1;k<i;k++){
				if(t[k]<t[i]||t[k]>t[j]) continue;
				if(!vis[k]) flag=0;
			}
			if(flag) f[i]=(f[i]+f[j])%mod;
		}
	}
	
	cout<<f[n+1]<<"\n";
	return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

考察最终做了操作的球的集合可能长成什么样：

![](https://cdn.luogu.com.cn/upload/image_hosting/iaxzym1c.png)

也就是找到一个子序列，$x$ 递增 $y$ 递减，相邻的点围成的矩形内部点都会被保留下来。

于是想到 dp：设 $dp_{i}$ 表示目前选到 $x=i$ 的点的方案数，转移枚举下一个点 $j$ 选什么。但是这样有个问题是可能会算重。比如 $x_i=i,y_i=n-i+1$ 的情况，有 $2^n$ 种操作方法，但是剩下的球都是相同的。

考虑如何避免这件事情：我们只去统计不能进行更多操作的集合。对于上面这个例子，只要没有把每个球选一遍就是不合法的，因为可以再加一次操作，所以统计到的就是我们想要的答案 $1$。

如何刻画这个条件？实际上这就等价于，对于选择的相邻两个点 $i,j$，不存在 $x_i<x_k<x_j,y_i>y_k>y_j$，满足 $(i,k)$ 围成的矩形和 $(k,j)$ 围成的矩形包含的点和 $(i,j)$ 围成的矩形相同。因此直接枚举 $i,k,j$，用前缀和判断转移是否合法即可，时间复杂度 $\mathcal O(n^3)$。

[submission](https://atcoder.jp/contests/arc184/submissions/59296069)

---

## 作者：piggy123 (赞：1)

考虑最终删除的形式，我们发现最终保留下来的必定形如下面图中所示的阴影部分，即从左上到右下若干个顶点相接的矩形，其中矩形必然为关键点：

![](https://cdn.luogu.com.cn/upload/image_hosting/ayo9c4iq.png)

如果我们直接统计相接顶点的位置会算重，但是我们可以令 $j\to i$ 可以转移当且仅当不存在 $j\lt k\lt i$ 满足点 $k$ 在 $i,j$ 形成的矩形中且 $i,j$ 形成的矩形中所有点都被 $i,k$ 形成的矩形和 $k,j$ 形成的矩形所包含。这样相当于我们为每个方案选取了一个代表元，直接暴力判断就是 $O(n^3)$ 的，利用数据结构（如树套树等）维护转移应该可以至少做到 $O(n\log n)$。 

[Submission Link](https://atcoder.jp/contests/arc184/submissions/58034131)。

---

## 作者：_Cheems (赞：0)

先排序，被操作的点一定是下降子序列，直接算肯定会算重，考虑增强限制去重。

删去的点构成上下两个阶梯，不好处理，故考虑保留的点，是若干首尾相接的矩形。

注意到一个矩形若能被划为两个更小的矩形且点集不变，则会算重，所以要求不能发生这种情况。

现在不会算重了吗？对于最终统计的方案，考虑未被操作的点，若选其一必然多删去点；而操作点若取消操作，要么点集变了，反之不可能被统计（因为操作它点集不变）。

直接计数即可。$O(n^3)$。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e2 + 5, mod = 998244353;
int n, s[N][N], f[N];
struct node{int x, y;} a[N];

inline bool chk(int x, int y){
	for(int i = x + 1; i < y; ++i)
		if(a[x].y > a[i].y && a[i].y > a[y].y && s[x][i] + s[i][y] - 1 == s[x][y]) return false;
	return true;
}
signed main(){
	cin >> n;
	for(int i = 1; i <= n; ++i) scanf("%lld%lld", &a[i].x, &a[i].y);
	a[n + 1] = {0, n + 1};
	a[n + 2] = {n + 1, 0};
	n += 2; 
	sort(a + 1, a + 1 + n, [](node A, node B){return A.x < B.x;}); 
	
	for(int i = 1; i <= n; ++i)
		for(int j = i + 1; j <= n; ++j)
			for(int k = i; k <= j; ++k)
				if(a[i].y >= a[k].y && a[k].y >= a[j].y) ++s[i][j]; 
	
	f[1] = 1;
	for(int i = 2; i <= n; ++i)
		for(int j = 1; j < i; ++j) 
			if(a[i].y < a[j].y && chk(j, i)) f[i] = (f[i] + f[j]) % mod;
	cout << f[n];
	return 0;
}

```

---

## 作者：WrongAnswer_90 (赞：0)

# [My Blogs](https://wronganswer90.github.io/2024/10/07/ARC184D-Erase-Balls-2D)

### [[ARC184D] Erase Balls 2D](https://www.luogu.com.cn/problem/AT_arc184_d)

剩下的点的不同方案不好计数，对操作方案计数会算重。

考虑在剩余点的方案和操作之间构建一个双射：对于一个剩下的方案，不断操作不会新删去当前剩下的点的点直到没有点可以操作，这样操作方案就和剩下的球的方案一一对应了。

所以需要计数的序列是，操作任意一个没有被删去且没有被操作的点都会导致其他没有被删去的点删掉的操作方案。设 $f_i$ 表示最后一次操作是 $i$，枚举下一次操作位置 $j>i$，检查 $i$ 是否能转移到 $j$ 就是直接枚举 $i<k<j$ 且 $a_j<a_k<a_i$，检查操作 $k$ 是否会删去其他值即可判断能否转移。时间复杂度 $\mathcal O(n^3)$。

具体实现可以新建两个点 $(0,n+1)$ 和 $(n+1,0)$ 避免讨论。

```cpp
int n,a[310],f[310],t[310][310];
inline int ask(int x1,int y1,int x2,int y2)
{
	return t[x2][y2]-t[x2][y1-1]-t[x1-1][y2]+t[x1-1][y1-1];
}
inline void mian()
{
	read(n);int x,y;
	for(int i=1;i<=n;++i)read(x,y),a[x]=y,++t[x][y];
	a[0]=n+1;
	for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)t[i][j]+=t[i][j-1];
	for(int i=1;i<=n;++i)for(int j=1;j<=n;++j)t[i][j]+=t[i-1][j];
	f[0]=1;
	for(int i=0;i<=n;++i)
	{
		for(int j=i+1;j<=n+1;++j)if(a[j]<a[i])
		{
			int fl=1;
			for(int k=i+1;k<j;++k)if(a[j]<a[k]&&a[k]<a[i])
			{
				int ffl=1;
				if(ask(i+1,a[j]+1,k-1,a[k]-1)>0)ffl=0;
				if(ask(k+1,a[k]+1,j-1,a[i]-1)>0)ffl=0;
				if(ffl)fl=0;
			}
			if(fl)Madd(f[j],f[i]);
		}
	}
	write(f[n+1]);
}
```

---

## 作者：LCat90 (赞：0)

为什么场上会一直想区间 dp 呢。

这题的难点在于如何避免算重，我们需要**加强对状态的限制**。

考虑 dp 操作序列（显然顺序不影响，所以按 $x$ 升序进行 dp），令 $dp_i$ 表示对 $i$ 进行操作，并枚举上一个操作的位置 $j(j<i)$ 转移过来。

如何避免不会算重？这里我们再限制：对于当前的操作序列，如果再操作任意一个球都会改变剩下的球。~~非常妙，使我想不到。~~

这样设计过后，所有剩下球的状态都会对应唯一的 dp 状态中的操作序列（尽管 dp 中某次操作**没有改变剩下的球**），两者形成双射。

然后就是转移条件了：（$j<i$，把下标当成 $x$ 轴）

+ 保证每个球都可以被操作，不存在操作一次球之后把其他待操作的球弄没了的情况：$a_j>a_i$。这里的结论是操作序列按下标排序后 $y$ 值是单减的。

+ 由于 $(j,i)$ 内的球都没有操作，所以根据定义的限制，要判断是否所有的 $k(j<k<i)$，它操作过后都会改变剩下的球。当然为了保证 $k$ 可以操作，还要 $k$ 满足 $a_j>a_k>a_i$。

状态线性，枚举转移点线性，判断是否可以转移线性，时间复杂度为 $O(n^3)$。当然这东西显然可以大大优化，不讨论。

代码：https://atcoder.jp/contests/arc184/submissions/58079618

---

