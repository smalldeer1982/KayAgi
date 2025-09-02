# [ABC212E] Safety Journey

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc212/tasks/abc212_e

AtCoder国には $ N $ 個の都市があり、都市 $ 1 $ , 都市 $ 2 $ , $ \ldots $ , 都市 $ N $ と番号付けられています。 最初、どの $ 2 $ つの相異なる都市の間も双方向に通れる道で結ばれていましたが、老朽化が進み、これらのうち $ M $ 本の道が使えなくなってしまいました。具体的には $ 1\leq\ i\ \leq\ M $ について都市 $ U_i $ と都市 $ V_i $ を結ぶ道が使えなくなってしまいました。

いま、高橋君は都市 $ 1 $ で始まり、都市 $ 1 $ で終わる $ K $ 日間の旅をしようと考えました。都市 $ 1 $ で始まり、都市 $ 1 $ で終わる $ K $ 日間の旅とは、 $ K+1 $ 個の都市の列 $ (A_0,\ A_1,\ \ldots,\ A_K) $ であって、$ A_0=A_K=1 $ をみたし、 $ 0\leq\ i\leq\ K-1 $ について $ A_i $ と $ A_{i+1} $ が相異なり、かつ都市 $ A_i $ と都市 $ A_{i+1} $ が現在も使用可能な道で結ばれているものを指します。

都市 $ 1 $ で始まり、都市 $ 1 $ で終わる $ K $ 日間の相異なる旅の数を $ 998244353 $ で割った余りを出力してください。ただし、 $ 2 $ つの $ K $ 日間の旅 $ (A_0,\ A_1,\ \ldots,\ A_K) $ と $ (B_0,\ B_1,\ \ldots,\ B_K) $ が相異なるとは、ある $ i $ が存在して $ A_i\neq\ B_i $ となることを言います。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5000 $
- $ 0\ \leq\ M\ \leq\ \min\left(\ \frac{N(N-1)}{2},5000\ \right) $
- $ 2\ \leq\ K\ \leq\ 5000 $
- $ 1\ \leq\ U_i\ <\ V_i\ \leq\ N $
- $ (U_i,\ V_i) $ は全て互いに相異なる。
- 入力は全て整数である。

### Sample Explanation 1

次のような $ 4 $ 種類の旅が存在します。 - ($ 1,2,1,2,1 $) - ($ 1,2,1,3,1 $) - ($ 1,3,1,2,1 $) - ($ 1,3,1,3,1 $) これ以外に条件をみたすようなものは無いため、 $ 4 $ を出力します。

### Sample Explanation 2

使える道が $ 1 $ 本も残っておらず、条件をみたすような旅は存在しません。

## 样例 #1

### 输入

```
3 1 4
2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3 3
1 2
1 3
2 3```

### 输出

```
0```

## 样例 #3

### 输入

```
5 3 100
1 2
4 5
2 3```

### 输出

```
428417047```

# 题解

## 作者：L_zaa_L (赞：6)

## 分析
首先就想到暴力 dp，用三个循环枚举：时间，目前在的城市，明天去的城市。
时间复杂度为 $O(n^2k)$，由于 $1 \le n,m,k \le 5000$，所以会超时。

### 暴力的代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()        {//快读
    int s=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch == '-') f=-1;ch=getchar();}
    while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();}
    return s*f;
}
void write(int x){//快写
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
    return;
}
int f[5005][5005],a[5005][5005],u,v;
signed main(){
	int n,m,k;
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		u=read(),v=read();
		a[u][v]=1;
		a[v][u]=1;//标记不能走
	}
	f[0][1]=1;
	for(int i=1;i<=k;i++)//枚举时间
		for(int j=1;j<=n;j++)//枚举目前所在的城市
			for(int t=1;t<=n;t++)//枚举将要去往的城市
				if(j!=t&&a[j][t]==0)//如果没有走到自己且有路
					f[i][j]=(f[i][j]+f[i-1][t])%998244353;//则加上这个点的方案数。
	cout<<f[k][1];
	return 0;
}

```
后来想到边表可以优化边，于是就用边表记录不能走的，$f_{i,j}$ 就是加上之前所有的方案数（$f_{i-1,j}$）再减去不能走的（包括自己）。虽然看上去没什么区别，但是因为只有 M 条边，所以只用算 2M 次（因为是双向的）。最终的时间复杂度为 $O(nm+nk)$。
### 最终的代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()        {
    int s=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch == '-') f=-1;ch=getchar();}
    while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();}
    return s*f;
}
void write(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
    return;
}
int u[100005],v[100005];
int tot,head[200005],to[200005],nxt[200005];//边表要开两倍，不然会寄，我多开了一点，其实10005也可以。
int f[5005][5005];
void add(int a,int b){to[++tot]=b;nxt[tot]=head[a];head[a]=tot;}//建立边表
signed main(){
	int n,m,k;
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read();	
		add(u[i],v[i]);
		add(v[i],u[i]); //加边
	}
	f[0][1]=1;
	for(int i=1;i<=k;i++){//第i天 
		int sum=0;
		for(int j=1;j<=n;j++){//求出如果没有不能走的时候的方案数 
			sum+=f[i-1][j];
		}
		for(int j=1;j<=n;j++){
			f[i][j]+=sum-f[i-1][j];
		}//不能走向自己，所以要减去
		for(int j=1;j<=n;j++){
			for(int k=head[j];k!=0;k=nxt[k])//减去不能走的边的方案数 
				f[i][j]-=f[i-1][to[k]];
			f[i][j]=(f[i][j]+998244353)%998244353;//取模
		}
	}
	cout<<f[k][1]%998244353;
	return 0;
}
```
感谢[@Li000000](https://www.luogu.com.cn/user/756229)大佬的帮助。

---

## 作者：_Ponder_ (赞：2)

[Safety Journey](https://www.luogu.com.cn/problem/AT_abc212_e)

### 题目大意

给定一张缺少了 $m$ 条边的 $n$ 个点的完全图和一个正整数 $k$，你需要求出满足以下条件的序列 $A$ 的数量：

- $A$ 的长度为 $k+1$。
- $A_0=A_k=1$。
- $\forall 0\le i\le k-1$，点 $A_i$ 和点 $A_{i+1}$ 之间存在边。

~~我的翻译这么好为什么没过~~

### 思路分析

图上计数，考虑 DP。

设 $f_{i,j}$ 表示考虑到路径上的第 $i$ 个点（从 $0$ 开始），当前位于点 $j$ 的方案数。

那么所求的就是 $f_{k,1}$。

考虑状态转移，因为给出的是原图的补图，所以可以列出方程：

$$f_{i,j}=\sum_{k=1}^nf_{i-1,k}-\sum_{v\in e_j}f_{i-1,v}-f_{i-1,j}$$

其中，$e_i$ 表示点 $i$ 在补图中的出点集合。

容易发现，前半部分可以通过记录前缀和的方式优化掉，所以就做完了，时间复杂度和空间复杂度均为 $O(n^2)$（视 $n,m$ 同阶），也可以通过滚动数组将空间优化到 $O(n)$，但无所谓了。

### 代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N=10100,M=5050,mod=998244353;
#define int long long

int to[N],nxt[N],head[N];
int idx=1,n,m,k,in1,in2,sum;
int f[M][M];

void add(int u,int v){
    idx++;to[idx]=v;nxt[idx]=head[u];head[u]=idx;
}

signed main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=m;i++){
        scanf("%lld%lld",&in1,&in2);
        add(in1,in2);add(in2,in1);
    }
    f[0][1]=1;//第 0 天在点 1 有一种方案
    for(int i=1;i<=k;i++){
        sum=0;
        for(int s=1;s<=n;s++) sum+=f[i-1][s];//记录和
        for(int s=1;s<=n;s++){
            f[i][s]=sum-f[i-1][s];
            for(int j=head[s];j;j=nxt[j]){
                int v=to[j];
                f[i][s]-=f[i-1][v];//依次减去
            }
            f[i][s]%=mod;
        }
    }
    cout<<f[k][1]<<'\n';
    return 0;
}
```

---

## 作者：_lfxxx_ (赞：2)

### 题目大意

$n$ 个点，每两个点有双向边，但有 $m$ 条边不能走，要走 $k$ 个点，起点和终点都是 $1$，有几种不同的方案，答案对 $998244353$ 取模。

$2 \le n \le 5000,0 \le m \le \min(\dfrac{n(n-1)}{2},5000),2 \le k \le 5000$。

### 思路

设 $f(u,n)$ 表示终点为 $u$ 点走了 $k$ 步的方案数，那么 $f(u,k)=\sum_{v \in e(u)}f(v,k-1)$，直接搞是 $O(n^2k)$，过不了。

我们发现被删的边数很少，于是我们在 $k-1 \to k$ 时先让 $k-1$ 层的点把 $k$ 层的点都更新一遍，$k-1$ 层的的和记录一下，这时一次需 $O(n)$。但多算了贡献，因此需要把那 $m$ 条边减掉，只有 $O(m)$ 条被删的边，因此一次就只要 $O(n+m)$ 而非 $O(n^2)$，总时间复杂度 $O((n+m)k)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#ifdef IAKIOI
	#define cin fin
	ifstream cin("in.txt");
#endif
constexpr int N=5005,mod=998244353;
int f[N][N],u[N],v[N];
inline void Mod(int&a,int b){a+=b;if(a<0)a+=mod;else if(a>=mod)a-=mod;}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,m,k,sum;
	cin>>n>>m>>k;
	for(int i=1;i<=m;++i)
		cin>>u[i]>>v[i];
	f[1][0]=1;
	for(int j=1;j<=k;++j){
		sum=0;
		for(int i=1;i<=n;++i)
			Mod(sum,f[i][j-1]);
		for(int i=1;i<=n;++i)
			Mod(f[i][j],sum-f[i][j-1]);
		for(int i=1;i<=m;++i)
			Mod(f[u[i]][j],-f[v[i]][j-1]),Mod(f[v[i]][j],-f[u[i]][j-1]);
	}
	cout<<f[1][k]<<endl;
    return 0;
}
```

---

## 作者：fire_hmz (赞：1)

考虑 DP。

定义状态 $dp_{i,j}$ 为在走了 $i$ 条边时，位于点 $j$。

然后时间复杂度 $O(N^2K)$ 。

然后就 T 了。

所以我们需要优化一个维度使得时间复杂度降到 $O(N^2)$ 级别。

正难则反，因为这个图一开始是一个完全图，我们可以考虑把删掉的边存储起来，就可以把原本 $O(N^2)$ 的枚举两点的时间优化成 $O(M)$。

然后可以用一个变量 $sum$ 存储上一层的情况总和，减掉当前点不能到达的所有点的上一步情况总和，就是当前点目前的情况总和。

Code:
```cpp
int n,m,k;
int dp[5003][5003];
int sum[5003];
vector<int> a[5003];
namespace third_coming {

	void init() {
		cin>>n>>m>>k;
		for(int i=1;i<=m;i++){
			int x,y;
			cin>>x>>y;
			a[x].push_back(y);
			a[y].push_back(x);
		}
		// for(int i=1;i<=n;i++){
			// a[i].push_back(i);
		// }
		sum[0]=1;
		dp[0][1]=1;
		for(int dep=1;dep<=k;dep++){
			for(int i=1;i<=n;i++){
				dp[dep][i]=(sum[dep-1]-dp[dep-1][i]+mod)%mod;
				for(int j=0;j<a[i].size();j++){
					int y=a[i][j];
					dp[dep][i]-=dp[dep-1][y];
					dp[dep][i]=(dp[dep][i]+mod)%mod;
				}
				sum[dep]=(sum[dep]+dp[dep][i]+mod)%mod;
				// cout<<i<<' '<<dep<<' '<<dp[dep][i]<<endl;
			}
		}
		cout<<dp[k][1];
		
	}

	void solve() {
		;
	}

	void main() {
		init();
		solve();
	}
}

	
```

---

## 作者：Swirl (赞：1)

定义 $dp(i, j)$ 为从 $1$ 开始走 $i$ 步走到 $j$ 的情况数。

如果暴力转移的话与弗洛伊德类似，是 $\mathcal O(n^3)$ 的，显然过不了。

如果把删完边的图建出来，再跑 dp 会很慢。

正难则反，可以把每一次从 $i - 1$ 转移到 $i$ 看成由 $n$ 个点减去部分点。

不妨对于 $i$ 把所有的 $dp(i, j)$ 的和预处理进一个数组 $b_i$，在转移 $i + 1$ 时可以使其复杂度降到 $\mathcal O(m)$。

$$
dp(i, j) = b_{i - 1} - dp(i - 1, j) - \sum_{u \in g_j}  dp(i - 1, u)
$$

其中 $g_j$ 代表与 $j$ 邻接的点构成的集合。

并且：

$$
b_i = \sum^{n} _ {j = 1} dp(i, j)
$$

最后输出 $dp(k, 1)$ 即可。

时间复杂度：$\mathcal O(nk + mk)$，可以过。

---

```cpp
namespace zqh {
	const int N = 5005;
	
	int n, m, k, f[N][N], sum[N];
	vector<int> g[N];
	
	void init() {
		cin >> n >> m >> k;
		rep (i, 1, m) {
			int a, b;
			cin >> a >> b;
			g[a].push_back(b);
			g[b].push_back(a);
		}
	}
	
	void solve() {
		f[0][1] = 1;
		sum[0] = 1;
		rep (i, 1, k) {
			rep (j, 1, n) {
				f[i][j] = (sum[i - 1] - f[i - 1][j] + mod) % mod;
				for (int x : g[j]) {
					f[i][j] = (f[i][j] - f[i - 1][x] + mod) % mod;
				}
				sum[i] = (sum[i] + f[i][j]) % mod;
			}
		}
		cout << f[k][1] % mod;
	}
	
	void main() {
		init();
		solve();
	}
}  // namespace zqh
```

---

## 作者：wth2026 (赞：1)

# 题目思路

首先考虑此题的 $O(n^{3})$ 写法。

定义 $f_{i,j}$ 表示第 $j$ 步走到 $i$ 的方案数，对于每一层 $j$ 的每一个 $i$，枚举每一个与它相连的点，本次的答案是它们上一层答案之和。由于状态数是 $n^2$，转移时 $n$，所以时间复杂度是 $O(n^3)$。

考虑优化。

看数据范围：
> - $ 0\ \leq\ M\ \leq\ \min\left(\ \frac{N(N-1)}{2},5000\ \right) $

这种写法非常容易让人产生疑惑，我们可以从这里下手。

因为每一次，我们的答案都是大量的相关数值加起来，所以，我们可以考虑使用一个变量记录每一层的答案和，然后对于每一个点，减去与它不连边的点与自身的上一层的答案。

由于一共只有 $M$ 个边被断掉，每一条边连接两个点，所以时间复杂度为：$O(K\times \max(N,M\times 2))$。

# [AC Code](https://atcoder.jp/contests/abc212/submissions/57417761)
```cpp
// LUOGU_RID: 175806102
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 998244353
#define lnf 0x3f3f3f3f3f3f3f3f

#pragma GCC optimize (1)
#pragma GCC optimize (2)
#pragma GCC optimize (3)
#pragma GCC optimize (4)
#pragma GCC optimize (5)
#pragma GCC optimize ("Os")
#pragma GCC optimize ("Ofast")

using namespace std;

namespace WTH {
	const int N = 5005;
	
	int n, m, k;
	int u, v;
	bool _Mp[N][N];
	int f[N][N], _Sm[N][N], sum[N];//f[i][j]表示在第 j 步走到 i 的方案数，_Sm[i][j] 表示点集与 i 有边在第 j 步的方案和 
	vector <int> _Dnt[N];
	
	void init () {
		for (register int i = 0; i < N; ++ i) {
			for (register int j = 0; j < N; ++ j) {
				_Mp[i][j] = 1;
			}
			
			_Mp[i][i] = 0;
			_Dnt[i].clear ();
			_Dnt[i].push_back (i);
		}
		
		memset (f, 0, sizeof (f));
		memset (_Sm, 0, sizeof (_Sm));
		memset (sum, 0, sizeof (sum));
		
		f[1][0] = 1;
		sum[0] = 1;
	}

	void main () {
		cin >> n >> m >> k;
		
//		for (register int i = 1; i <= k; ++ i) {
//			for (register int j = 1; j <= n; ++ j) {
//				
//		
		for (register int i = 1; i <= m; ++ i) {
			cin >> u >> v;
			_Mp[u][v] = 0;
			_Mp[v][u] = 0;
			_Dnt[u].push_back (v);
			_Dnt[v].push_back (u);
		}
		
		for (register int i = 1; i <= k; ++ i) {
			for (register int j = 1; j <= n; ++ j) {
//				for (register int k = 1; k <= n; ++ k) {
//					if (k == j) {
//						continue ;
//					}
//					
//					if (_Mp[k][j]) {
//						f[j][i] += f[k][i - 1];
//						f[j][i] %= inf;
//					}
//				}
//				
				f[j][i] = sum[i - 1];
				
				for (register int k = 0; k < _Dnt[j].size (); ++ k) {
					f[j][i] = (f[j][i] - f[_Dnt[j][k]][i - 1] + inf) % inf;
				}
				
				sum[i] += f[j][i];
			}
		}
		
		cout << f[1][k] << endl;
	}
}

signed main () {
	ios :: sync_with_stdio (false);
	cin.tie (0);
	cout.tie (0);

	int T = 1;
	//cin >> T;

	while (T --) {
		WTH :: init ();
		WTH :: main ();
	}

	return 0;
}

```

---

## 作者：Engulf (赞：1)

先考虑朴素的 dp，设 $f_{i, j}$ 表示 $j$ 时刻走到 $i$ 点的方案数，转移很简单：

$$f_{i, j} = \sum\limits_{k \in \{k | i \text{可到达} k \}} f_{k,j - 1}$$

时间复杂度 $\mathcal{O}(n^2k)$，超时。

注意到 $m$ 最大也才 $5000$，能否从这里入手？题目给出的是 $m$ 条 **不能** 走的边，考虑一下容斥，转移改成：

$$f_{i, j} = \sum\limits_{k = 1}^{n} f_{k, j - 1} - f_{i, j - 1} - \sum\limits_{k\text{到不了}i}f_{k, j - 1}$$

第一项是所有上一步的状态，因为这是完全图，可以从任意一点转移过来。

第二项是减去自己走向自己的方案数。

第三项是减去题目限制的不能行走的边的方案数。

这样看似复杂度很高，其实不然。一共只可能有 $m$ 条边，所以复杂度其实是 $\mathcal{O}(k(n + m))$ 的。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 5005, mod = 998244353;

int n, m, t;

int a[N][N];

int f[N][N];

vector<int> g[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> t;
    for (int i = 1, u, v; i <= m; i++) cin >> u >> v, g[u].emplace_back(v), g[v].emplace_back(u);
    f[1][0] = 1;
    for (int k = 1; k <= t; k++) {
        int sum = 0;
        for (int i = 1; i <= n; i++) sum = (sum + f[i][k - 1]) % mod;
        for (int i = 1; i <= n; i++) f[i][k] = (sum - f[i][k - 1] + mod) % mod;
        for (int i = 1; i <= n; i++)
            for (auto j: g[i])
                f[i][k] = (f[i][k] - f[j][k - 1] + mod) % mod;
    }
    cout << f[1][t] << "\n";
    return 0;
}
```

这道题提示我们，想到做法时要认真分析时间复杂度，不要仅仅看循环个数判断，别被表象所欺骗。

---

## 作者：ZLCT (赞：0)

# ABC212E Safety Journey
## 题目描述
在一个 $n$ 个点的完全图中去除 $m$ 条边。求有多少条路线，满足从 $1$ 号点出发，走了 $k$ 步路之后回到 $1$ 号点。
## 题目思路
- 暴力考虑将每一条路径 dfs 遍历，计数满足条件的答案数量，复杂度 $O(n^k)$。
- 由于不需要关注路径的走法，只需要考虑某一条路径的结束点与步数，于是考虑将两者作为 dp 状态设计 dp 转移。
- 令 $f_{i,j}$ 表示走了 $i$ 步，结束点为 $j$ 的路径数。
- 考虑状态转移：$f_{i,j}$ 一定可以由某个 $f_{i-1,k}$ 走一步到达，而可以到达的条件显然为 $j,k$ 间存在边。
- 于是转移方程就为 $f_{i,j}=\sum_{k \in G_j} f_{i-1,k}$
- 但是枚举外层 $i$ 复杂度为 $O(k)$，内层枚举 $j,k$ 的复杂度为图中的总边数即 $O(n^2 - 2 \times m)$，总复杂度为 $O(n^2k-2km)$，显然不行。
- 观察题目可以发现 $m\le 5000$，而对于第 $i$ 层的每一个 $j$，都可以看成在所有 $k\in n$ 中减掉 $k \notin G_j$ 所做的贡献。
- 于是转移方程就变成了 $f_{i,j}=\sum_{k \in n} f_{i-1,k} - \sum_{k \notin G_j} f_{i-1,k}$ 。而 $\sum_{k \in n} f_{i-1,k}$ 可以通过预处理实现，于是复杂度变为了 $O(nk+mk)$，可以接受。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n,m,k,f[5005][5005],sum;
vector<int>G[5005];
signed main(){
    cin>>n>>m>>k;
    while(m--){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    f[0][1]=1;
    for(int i=1;i<=k;++i){
        sum=0;
        for(int j=1;j<=n;++j){
            sum+=f[i-1][j];
            sum%=mod;
        }
        for(int j=1;j<=n;++j){
            f[i][j]=(sum-f[i-1][j]+mod)%mod;
            for(int v:G[j]){
                f[i][j]-=f[i-1][v];
                f[i][j]=(f[i][j]+mod)%mod;
            }
        }
    }
    cout<<f[k][1]<<'\n';
    return 0;
}

```

---

## 作者：Expert_Dream (赞：0)

这一道题我们用的是**容斥原理**。

考虑最暴力的 Dp，$dp_{i,j}$ 为从 $j$ 的时间走到 $i$ 点的方案数，$dp_{i,j} = \sum_{k} dp_{k,j-1} [k\ \texttt{可到达}\ i] + dp_{i,j-1}$。

考虑容斥，变成 $dp_{i,j} = \sum_{k=1}^n dp_{k,j-1} - dp_{i,j-1} - \sum_{k} dp_{k,j-1} [k\ \texttt{不可到达}\ i]$。

我们发现 $\sum_{k=1}^n dp_{k,j-1}$ 对于同一个 $j$ 来说都是一样的，我们可以对每一个 $j$ 一开始将他先算出来，记录成 $sum$，于是，转移方程变成了：$dp_{i,j} = sum - dp_{i,j-1} - \sum_{k} dp_{k,j-1} [k\ \texttt{不可到达}\ i]$。

又因为 $\sum_{k} dp_{k,j-1} [k\ \texttt{不可到达}\ i]$ 是非常少的，因为总共也就是有  $M$ 条边。

因此我们使用 $sum = \sum_{k=1}^n dp_{k,j-1}$，$dp_{i,j} = sum - dp_{i,j-1} - \sum_{k} dp_{k,j-1} [k\ \texttt{不可到达}\ i]$ 的转移方程时间复杂度正确，即可通过本题。

[link](https://atcoder.jp/contests/abc212/submissions/52248062)。

---

## 作者：2020luke (赞：0)

# [[ABC212E] Safety Journey](https://www.luogu.com.cn/problem/AT_abc212_e) 题解

## 思路解析

首先根据题目的条件我们可以想到 dp，用 $f_{i,j}$ 表示走了 $i$ 步，现在在 $j$ 的方案数，可见转移即是 $f_{i,u} \gets \sum{f_{i-1,v}}$，这里的 $v$ 表示每个与 $u$ 相连的点。可见如此做时间复杂度为 $O(kn(\frac{n(n-1)}{2}-m))=O(k(\frac{n^3-n^2}{2}-nm)) \approx O(kn^3-knm)$，考虑优化。

可以发现如果我们像上文一样建边总边数可以达到 $\frac{n(n-1)}{2}-m \approx n^2-m$，这个大小是很难被接受的，于是我们想到可以建反边，也就是只建被删除的那 $m$ 条边，这样总边数就只有 $m$ 条，可以接受，然后对于统计答案就只需要将转移式改成 $f_{i,u} \gets \sum^{n}_{j=1}{f_{i-1,j}}-\sum{f_{i-1,v}}$ 即可，其中 $\sum^{n}_{j=1}{f_{i-1,j}}$ 对于每个 $u$ 都不会变，可以提前处理好。

注意计算 $f_{i,u}$ 时要先减去 $f_{i-1,u}$，同时勤取模。

时间复杂度：虽有三层循环，但第二层内遍历的是每一条边，而总共只有 $m$ 条边，因此为 $O(km)$，可以通过。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5010, q = 998244353;
int n, m, k, f[N][N];
vector<int> g[N];
void mod(int &x) {
	x = (x % q + q) % q;
}
signed main() {
	cin >> n >> m >> k;
	for(int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back(v); g[v].push_back(u);
	}
	f[0][1] = 1;
	for(int i = 1; i <= k; i++) {
		int sum = 0;
		for(int j = 1; j <= n; j++) sum += f[i - 1][j], mod(sum);
		for(int j = 1; j <= n; j++) {
			f[i][j] = sum - f[i - 1][j]; mod(f[i][j]);
			for(auto it : g[j]) {
				f[i][j] -= f[i - 1][it]; mod(f[i][j]);
			}
		}
	}
	cout << f[k][1];
	return 0;
}
```

---

## 作者：gxp123 (赞：0)

# abc212 E - Safety Journey

## 题意

给定一个完全图，并在其中去除 $m$ 条边。求有多少条路线，满足从 $1$ 号点出发，走了 $k$ 步路之后回到 $1$ 号点。

## 题解

我们记 $f_{i,j}$ 表示当前走了 $k$ 步路，在第 $j$ 个节点。

假设没有边被删除，则 $f_{i,j} = \sum\limits_{k = 1}^n f_{i - 1,k} - f_{i-1,j}$。

如果有边被删除了。

我们记 $S_x$ 表示 $x$ 不能到达的节点集合。

则 $f_{i,j} = \sum\limits_{k=1}^nf_{i-1,k}-\sum\limits_{k\in S_j} f_{i-1,k} - f_{i-1,j}$。

而 $\sum\limits_{k=1}^nf_{i-1,k}$ 是好维护的，$\sum |S_j| \le 10000$。

所以这样枚举的时间复杂度是：$O(NM)$。  

我们可以用滚动数组优化一下空间。

## code

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;
const int maxN = 5000 + 10;
const int mod = 998244353;
struct edge{
    int v,nxt;
};
edge e[maxN << 1];
int head[maxN],tot;
bool a[maxN][maxN];
ll f[2][maxN];
int n,m,k;
void add(int u,int v){
    e[++tot] = (edge){
        v,head[u]
    };
    head[u] = tot;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i = 1,u,v ; i <= m ; ++i){
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    f[0][1] = 1;
    int tag = 0;
    for(int i = 1,op,opt ; i <= k ; ++i){
        op = i & 1;
        opt = op ^ 1;
        tag = 0;
        for(int x = 1 ; x <= n ; ++x){
            for(int ii = head[x],y ; ii ; ii = e[ii].nxt){
                y = e[ii].v;
                f[op][y] = (f[op][y] - f[opt][x] + mod) % mod;
            }
            f[op][x] = (f[op][x] - f[opt][x] + mod) % mod;
            tag = (f[opt][x] + mod + tag) % mod;
        }
        for(int x = 1 ; x <= n ; ++x){
            f[op][x] = (tag + f[op][x]) % mod;
            f[opt][x] = 0;
        }
    }
    cout << (f[k & 1][1] + mod) % mod << endl;
    return 0;
}
```

---

## 作者：CQ_Bab (赞：0)

# 思路
我们首先可以想到 Dp 那么我们先定义一个状态为 $f_{i,j}$ 为已经走了 $i$ 个点，第 $i$ 个为 $j$ 的方案数。然后我们分析一下时间复杂度发现会超时，那么我们想一下如何优化，因为我们发现要排除的边很少，所以我们可以用总的减去不能走的即可。
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
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n,m,k;
int mp[5010][5010];
vector<int>v[5010];
int f[5010][5010];
const int mod=998244353;
fire main() {
	cin>>n>>m>>k;
	rep(i,1,m) {
		int a,b;
		cin>>a>>b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	f[1][1]=1;
	int sum=0,sum1=f[1][1];
	rep(i,2,k+1) {
		sum=sum1,sum1=false;
		rep(j,1,n) {
			f[i][j]=(sum-f[i-1][j]+mod)%mod; //减去上一个就是这个点
			for(auto x:v[j]) {
				f[i][j]=(f[i][j]-f[i-1][x]+mod)%mod;//将不能走的边的贡献减去
			}
			sum1=(sum1+f[i][j])%mod;
		}
	}
	cout<<f[k+1][1]<<endl;
	return false;
}

```

---

## 作者：_zzzzzzy_ (赞：0)

## 思路
树上 dp，首先考虑一下暴力暴力时间所在的城市和下一步要走的城市，但这样时间复杂度是 $O(n^2k)$，考虑到是一个完全图，我们可以先找出所有的要走到的城市的和，然后再减去坏掉的路就行了。

是运用了补图的思想。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5005,mod=998244353;
vector<int>e[maxn];
int n,m,k,dp[maxn][maxn];
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dp[0][1]=1;
	for(int i=0;i<k;i++){
		int sum=0;
		for(int v=1;v<=n;v++){
			sum=(sum+dp[i][v])%mod;
		}
		for(int u=1;u<=n;u++){
			dp[i+1][u]=(sum-dp[i][u]+mod)%mod;
			for(int v:e[u]){
				dp[i+1][u]=(dp[i+1][u]-dp[i][v]+mod)%mod;
			}
		}
	}
	cout<<dp[k][1];
	return 0;
}
```

---

