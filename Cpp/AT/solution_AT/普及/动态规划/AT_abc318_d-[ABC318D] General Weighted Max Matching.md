# [ABC318D] General Weighted Max Matching

## 题目描述

**题意简述**

有一个无向图，$i$ 到 $j$ 的距离为 $D_{i,j}$。你可以选择一些边，使得这些边连接的所有顶点互不相同。求这些边总长度的最大值。

## 说明/提示

- $2 \le N \le 16$
- $1 \le D_{i,j} \le 10^9$

**样例一解释**

选择 $D_{1,3},D_{2,4}$，总和为$5+8=13$。

## 样例 #1

### 输入

```
4
1 5 4
7 8
6```

### 输出

```
13```

## 样例 #2

### 输入

```
3
1 2
3```

### 输出

```
3```

## 样例 #3

### 输入

```
16
5 6 5 2 1 7 9 7 2 5 5 2 4 7 6
8 7 7 9 8 1 9 6 10 8 8 6 10 3
10 5 8 1 10 7 8 4 8 6 5 1 10
7 4 1 4 5 4 5 10 1 5 1 2
2 9 9 7 6 2 2 8 3 5 2
9 10 3 1 1 2 10 7 7 5
10 6 1 8 9 3 2 4 2
10 10 8 9 2 10 7 9
5 8 8 7 5 8 2
4 2 2 6 8 3
2 7 3 10 3
5 7 10 3
8 5 7
9 1
4```

### 输出

```
75```

# 题解

## 作者：ScottSuperb (赞：10)

## 解法分析
我太蒻了想不出来 dp，只好暴搜了。枚举每个点与哪个点搭配，分配完了就更新答案。理论上至多有 $15 \times 13 \times 11 \times 9 \times 7 \times 5 \times 3 \times 1 = 2027025$ 种可能。
## 代码
读写函数定义已省略。
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
int n, a[20][20], v[20];
ll ans;

void dfs(int d, ll sum) {
  if (d > n) {
    ans = max(ans, sum);
    return;
  }
  if (!v[d]) {
    v[d] = 1;
    for (int i = d + 1; i <= n; ++i)
      if (!v[i]) {
        v[i] = 1;
        dfs(d + 1, sum + a[i][d]);
        v[i] = 0;
      }
    v[d] = 0;
  }
  dfs(d + 1, sum);
}

int main() {
  n = read();
  for (int i = 1; i < n; ++i)
    for (int j = i + 1; j <= n; ++j) a[i][j] = a[j][i] = read();
  dfs(1, 0);
  write(ans);
  fls();
  return 0;
}
```

---

## 作者：hjqhs (赞：6)

搜索题。函数 `dfs(u,sum)` 为当前在搜索第 $u$ 个点，已选的边权之和为 $sum$。  
如果这个点已经访问过了，直接搜索下一个点并返回。  
如果没有访问过，我们可以选择不搜这个点和搜这个点。如果选择不搜则直接跳过这个点。如果选择搜则在所有未访问过的点中选一点继续搜索。  
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=b;i>=a;--i)
#define pv(i,p) for(int i=0;i<p.size();++i)
#define ptc putchar
#define il inline
#define reg register
// #define push_back pb
#define mp make_pair
#define eb emplace_back
// #define ret; return 0;
using namespace std;
const int N=20;
const int MOD=998244353;
const int INF=0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
int Max(int a,int b){return a>b?a:b;}
int MAX(int a,int b,int c){return Max(a,Max(b,c));}
int Min(int a,int b){return a<b?a:b;}
int MIN(int a,int b,int c){return Min(a,Min(b,c));}
void Swap(int&a,int&b){int tmp=a;a=b;b=tmp;}
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int n,w[N][N],ans=-INF;
bool vis[N];
void dfs(int u,int sum){
	ans=max(ans,sum);
	if(u==n+1)return;
	if(vis[u]){
		dfs(u+1,sum);
		return;
	}
	vis[u]=1;
	for(int i=u+1;i<=n;++i){
		if(!vis[i]){
			vis[i]=1;
			dfs(u+1,sum+w[u][i]);
			vis[i]=0;
		}
	}
	vis[u]=0;
	dfs(u+1,sum);
}
void solve(){
	cin>>n;
	for(int i=1;i<n;++i){
		for(int j=i+1;j<=n;++j){
			int d;cin>>d;
			w[i][j]=w[j][i]=d;
		}
	}
	dfs(1,0);
	cout<<ans;
}
signed main(){
	// freopen(,,stdin);
	// freopen(,,stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
	return 0;
}
```

---

## 作者：guanyf (赞：6)

### 题意：
- 给定 $N$ 个点的无向完全图，$D_{i,j}$ 表示有一天边权为 $D_{i,j}$ 的边连接点 $i$ 和 $j(i < j)$。请你选出满足以下条件的一些边，并求出这些边权之和的最大值：选出的边连接的两个点必须是两两不同的。

- $2 \le N \le 16$

### 分析、思路
先看数据范围：$N$ 这么小，要么是搜索，要么是状压 DP。状压比较好写，因此选择状压。

设当前状态为 $i$，表示当前状态下选择了一些点后最优的边权。因为边和点是一一对应的，且同一个状态可能有多种连边的方式，因此可以状态和平，取最优值。

对于当前状态，我们可以枚举未选择的两个点，在它们之间连一条边，继续递推。因此状态转移方程为：

$$i : 1 \rightarrow N , j : 1 \rightarrow N $$
$$dp_{i + 2 ^ j + 2 ^ k} = \max(dp_{i + 2 ^ j + 2 ^ k} , dp_i + D_{j,k})$$

时间复杂度：$\operatorname{O}(2 ^ N \cdot N^2)$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 17;  // 65536
int n, e[MAXN][MAXN], dp[1 << MAXN], a[MAXN], tot, ans;
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) cin >> e[i][j], e[j][i] = e[i][j];
  }
  for (int i = 0; i < (1 << n); i++) {
    tot = 0;
    for (int j = 0; j < n; j++) {
      int v = i & (1 << j);
      if (!v) a[++tot] = j;
    }
    for (int j = 1; j <= tot; j++) {
      for (int k = j + 1; k <= tot; k++) {
        int w = e[a[j] + 1][a[k] + 1];
        dp[i + (1 << a[j]) + (1 << a[k])] = max(dp[i + (1 << a[j]) + (1 << a[k])], dp[i] + w);
      }
    }
    ans = max(ans, dp[i]);
  }
  cout << ans;
  return 0;
}
```

### 拓展
在上述转移方程中，有一个比较冗余的地方：每次都要找 $2$ 个点，才能连成一条边。其实，有这样一条最优策略：对于还没有用过的点，用了肯定是比没有用划算的。因此我们可以从右往左找到第一个没有选过的点 $a$，再去考虑其他没有选过的点和它的连边。

仔细想想，这样答案并不会变得更劣。假设当前点有一个更优的点，但是它连了点 $a$，虽然在这种情况下变得更劣，但是，在其他情况下其他的点连了点 $a$，这个点依然可以连上最优的点，因此是最优的。

时间复杂度：$\operatorname{O}(2 ^ N \cdot N)$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define v (i & (1 << j))
using namespace std;
const int MAXN = 17;  // 65536
int n, e[MAXN][MAXN], dp[1 << MAXN], p, ans;
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) cin >> e[i][j], e[j][i] = e[i][j];
  }
  for (int i = 0; i < (1 << n); i++) {
    p = -1;
    for (int j = 0; j < n; j++) {
      if (!v && p == -1) p = j;
    }
    for (int j = 0; j < n; j++) {
      if (!v) dp[i | (1 << p) | (1 << j)] = max(dp[i | (1 << p) | (1 << j)], dp[i] + e[j + 1][p + 1]);
    }
    ans = max(ans, dp[i]);
  }
  cout << ans;
  return 0;
}
```


---

## 作者：DerrickLo (赞：2)

显然可以状压。

设 $dp[S]$ 表示选的集合是 $S$，答案的最大值。

可以得到 $dp[S]=\displaystyle{\max_{i<j,i\in{S},j\in{S}}(dp[S\backslash\{i\}\backslash\{j\}]+d[i][j])}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,d[25][25],dp[(1<<17)],ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n-i;j++)cin>>d[i][i+j];
	for(int S=0;S<(1<<n);S++){
		for(int j=1;j<=n;j++)for(int k=j+1;k<=n;k++){
			if(!(S&(1<<(j-1)))&&!(S&(1<<(k-1)))){
				dp[S+(1<<(j-1))+(1<<(k-1))]=max(dp[S+(1<<(j-1))+(1<<(k-1))],dp[S]+d[j][k]);
			}
		}
	}
	for(int i=0;i<(1<<n);i++)ans=max(ans,dp[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Red_Star_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc318_d)

#### 思路

看到 $n \le 16$，想到暴力，如果要最优，肯定每个点都会和其它一个点匹配，由于 $n$ 可能为奇数或者某些点与当前这个点一起更优，于是枚举一遍分别以 $i$ 开始最优解是多少，亲测可以 AC。

#### code

```c
#include<bits/stdc++.h>
using namespace std;
long long n,a[100][100],bj[100],ma,l[10010],bb[20],o = 1;
void dfs(long long z,int y,int x) {
	if(y <= n) ma = max(ma,z);
	if(y >= n) return;
	while(bj[x]) {
		x++;
	}
	if(x > n) x = 1;//越界了就重头开始
	while(bj[x]) {
		x++;
	}
	bj[x] = 1;
	for(int j = 1; j <= n; j++) {
		if(!bj[j]) {
			bj[j] = 1;
			dfs(z + a[x][j],y + 2,x + 1);
			bj[j] = 0;
		}
	}
	bj[x] = 0;
}
int main() {
	cin >> n;
	for(int i = 1; i < n; i++,o++)
		for(int j = i + 1; j <= n; j++)
			cin >> a[i][j],a[j][i] = a[i][j];
	for(int i = 1; i <= n; i++) dfs(0,0,i),memset(bj,0,sizeof(bj));
	printf("%lld",ma);
	return 0;
}

```


---

## 作者：Loser_Syx (赞：1)

数据范围 $n \leq 16$，考虑状压。

将 $n$ 个 $01$ 组成的字符串，其中，若第 $j$ 位为 $1$，说明此时选取 $j$ 这个点，然后将这个字符串从二进制压成一个十进制数 $i$，定义 $f_i$ 为十进制数 $i$ 能得到的最大价值。

然后对于 $i$ 枚举其中的 $2$ 个点为新连接的两个点，则其没连这两个点之前的状态为 $f_{i - 2^j-2^k}$，则转移方程为 $f_i = f_{i - 2^j-2^k}+a_{i,j}$。

答案是 $\max f_i$。

[代码](https://atcoder.jp/contests/abc318/submissions/45207846)

---

## 作者：Hyc_ (赞：1)

题目大意：

给出有 $N$ 个顶点的带边权完全图，选任意条顶点不重合的线段，求最大边权和。

由于 $2 \le N \le 16$，可以考虑状压 dp 求解。

枚举状态，每次检查其中二进制位中 $1$ 的个数，如果为奇数或者比 $N-2$ 大就跳过。

对于每个状态 $i$ 枚举加入两个点 $u,v(u<v)$，如果可以加入就取最大值更新答案。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
template<typename T>inline void Max(T &X,T Y){X<Y?X=Y:0;}
ll n,d[18][18],ans,dp[1<<17];
inline int check(int x){
	int cnt=0;
	for(;x;x-=x&-x)++cnt;
	return cnt;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j)
			cin>>d[i][j];
	for(int x,i=0;i<(1<<n);++i){
		x=check(i);
		if(x&1||x+1>=n)continue;
		for(int u=0;u<n;++u){
			if((1<<u)&i)continue;
			for(int v=u+1;v<n;++v){
				if((1<<v)&i)continue;
				int j=i|(1<<u)|(1<<v);
				Max(dp[j],dp[i]+d[u][v]);
				Max(ans,dp[j]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：shinzanmono (赞：1)

看到 $n\leq16$，就想到了状压 dp。

设 $f_S$ 表示 $S$ 为当前已选边的两端点的集合所获得的最大权值。可以知道，$S$ 中的元素个数一定是偶数。

转移：

枚举每一对 $(j,k)$ 满足 $j,k\in S$ 且 $j<k$，可以得到：

$$
f_S=\max_{j,k\in S\text{且}j
<k}\left\{f_{S-\{j,k\}}+w_{j\rightarrow k}\right\}
$$

我们考虑时间复杂度：

枚举状态需要 $O(2^n)$，枚举 $j,k$ 需要 $O(n^2)$，所以总的时间复杂度是 $O(2^nn^2)$，在 $n\leq16$ 时可以通过此题。

---

## 作者：ldj2006 (赞：0)

# [ABC318D] General Weighted Max Matching 题解

## 题意

&emsp;&emsp;给定无向有权完全图，求最大权匹配。

## 思路分析

&emsp;&emsp;注意到 $n \le 16$，我考虑状压 DP。

&emsp;&emsp;设当前点集 $S$ 中最大权匹配的答案是 $f_S$，我们考虑 $S$ 中“最后”一个点 $p$（这里的“最后”一个点是指，在状压表示状态的时候，最后一个 1 所代表的那个点，只需从这个点考虑就行，不需要考虑其他前面的点，因为会被更小状态考虑过）。

&emsp;&emsp;我们可以从前面其他点中，选择一个点 $q$ 和这个点匹配，也可以不匹配这个点。于是有转移方程：

$$
f_S = \max(f_{S-p},f_{S-p-q}),p \in S,q \in S, p \ne q
$$

&emsp;&emsp;其中 $w_{p,q}$ 代表点 $p$ 与点 $q$ 之间的边权。

&emsp;&emsp;初始化：当 $S$ 中没有点或只有一个点的时候 $f_S = 0$；当 $S$ 中有两个点 $u,v$ 时，$F_S = w_{u,v}$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 18;
const int S = (1<<(N+1));

LL a[N][N];
LL dp[S];
LL cnt[S];
LL n;

int count(int s)
{
	if(cnt[s] != -1)
		return cnt[s];
	int ans = 0;
	while(s>0)
	{
		ans += (s&1);
		s >>= 1;
	}
	return cnt[s] = ans;
}

LL dfs(int s)
{
	if(dp[s] != -1) return dp[s];
	if(count(s) <= 1)
	{
		dp[s] = 0;
		return 0;
	}
	if(count(s) == 2)
	{
		int idx1 = -1,idx2 = -1;
		int tmp = s,tmpidx = 0;
		while(tmp>0)
		{
			if(tmp&1)
			{
				if(idx1 == -1)
				{
					idx1 = tmpidx;
				}
				else
				{
					idx2 = idx1;
					idx1 = tmpidx;
				}
			}
			tmpidx++;
			tmp >>= 1;
		}
		dp[s] = a[idx1][idx2];
		return dp[s];
	}
	LL idxf = -1;
	LL ans = 0;
	for(int i = n-1;i >= 0;i--)
	{
		if((s&(1<<i)) > 0)
		{
			if(idxf == -1)
			{
				idxf = i;
			}
			else
			{
				ans = max(ans,a[idxf][i]+dfs(s-(1<<i)-(1<<idxf)));
			}
		}
	}
	ans = max(ans,dfs(s-(1<<idxf)));
	return dp[s] = ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
	memset(dp,-1,sizeof(dp));
	memset(cnt,-1,sizeof(cnt));
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		for(int j = i+1;j <= n;j++)
		{
			cin >> a[i-1][j-1];
			a[j-1][i-1] = a[i-1][j-1];
		}
	}
	dfs((1<<n)-1);
	cout << dp[(1<<n)-1] << "\n";
	return 0;
}
```


---

