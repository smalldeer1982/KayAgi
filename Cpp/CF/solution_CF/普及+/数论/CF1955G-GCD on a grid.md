# GCD on a grid

## 题目描述

Not long ago, Egor learned about the Euclidean algorithm for finding the greatest common divisor of two numbers. The greatest common divisor of two numbers $ a $ and $ b $ is the largest number that divides both $ a $ and $ b $ without leaving a remainder. With this knowledge, Egor can solve a problem that he once couldn't.

Vasily has a grid with $ n $ rows and $ m $ columns, and the integer $ {a_i}_j $ is located at the intersection of the $ i $ -th row and the $ j $ -th column. Egor wants to go from the top left corner (at the intersection of the first row and the first column) to the bottom right corner (at the intersection of the last row and the last column) and find the greatest common divisor of all the numbers along the path. He is only allowed to move down and to the right. Egor has written down several paths and obtained different GCD values. He became interested in finding the maximum possible GCD.

Unfortunately, Egor is tired of calculating GCDs, so he asks for your help in finding the maximum GCD of the integers along the path from the top left corner to the bottom right corner of the grid.

## 样例 #1

### 输入

```
3
2 3
30 20 30
15 25 40
3 3
12 4 9
3 12 2
8 3 12
2 4
2 4 6 8
1 3 6 9```

### 输出

```
10
3
1```

# 题解

## 作者：菲斯斯夫斯基 (赞：7)

## CF1955G GCD on a grid 题解

简单的暴力题。

### 思路

学会观察数据范围，有两个奇怪的地方：$n,m\le100$ 和 $a_i\le10^6$。

可以发现 $n,m\le 100$ 主要是因为数太多了 $\gcd$ 会变得很小。$n\times m\times\sqrt{a_i}$ 好像刚好能过。

所以不难想到枚举答案，然后 $\mathcal{O}(nm)$ 暴力检查。

检查怎么搞都行，比如 dp、并查集、bfs 等等.

这里用了 dp，转移和状态设计都很简单，设 $dp_{i,j}$ 为能否到达 $(i,j)$ 这个点。

$$dp_{i,j}=\begin{cases}0&k\nmid a_{i,j}\\dp_{i-1,j}|dp_{i,j-1}&k\mid a_{i,j}\end{cases}$$

上面的 $k$ 是枚举的答案。

时间复杂度是 $\mathcal{O}(nm\times d(V))$ 的。$V$ 是值域，这里最大是 $10^6$。$d(V)$ 指的是 $V$ 的因数个数，在 $10^6$ 范围里最大能取到 $240$。

注意 check 的时候不要用 `memset` 清空，运气不好会 TLE。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int t,n,m;
int a[N][N],dp[N][N];
vector<int>v;
bool cmp(int a,int b)
{
	return a>b;
}
bool check(int k)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			dp[i][j]=0;
	dp[1][1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if((i!=1||j!=1)&&a[i][j]%k==0)dp[i][j]=dp[i-1][j]|dp[i][j-1];
	return dp[n][m];
}
int main()
{
	cin>>t;
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",&a[i][j]);
		int ma=0,chk=0;
		for(int i=1;i*i<=a[1][1];i++)
		{
			if(a[1][1]%i)continue;
			v.push_back(a[1][1]/i);
			if(i*i!=a[1][1])v.push_back(i);
		}
		sort(v.begin(),v.end(),cmp);
		for(int i:v)
		{
			if(check(i))
			{
				printf("%d\n",i);
				break;
			}
		}
		v.clear();
	}
	return 0;
}
```

---

## 作者：Better_Fish (赞：2)

因为 $a_{1,1}$ 和 $a_{n,m}$ 分别是路径的起点和终点，所以答案会是 $\gcd(a_{1,1},a_{n,m})$ 的约数
。用根号时间复杂度枚举 $\gcd(a_{1,1},a_{n,m})$ 的约数 $x$，随后 dp 即可。

dp 时，先将 $a_{i,j}$ 是 $x$ 的倍数的格子标记为合法，随后检验有没有一条从 $a_{1,1}$ 到 $a_{n,m}$ 的合法路径。如果有，则统计最大值。

时间复杂度可行。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;

int t, n, m, a[MAXN][MAXN];

int gcd(int a, int b){
  return !b ? a : gcd(b, a % b);
}

bool dp[MAXN][MAXN];

bool B(int x){
  for(int i = 1; i <= n; i++){
    dp[i][1] = dp[i - 1][1] & !(a[i][1] % x);
  }
  for(int i = 1; i <= m; i++){
    dp[1][i] = dp[1][i - 1] & !(a[1][i] % x);
  }
  for(int i = 2; i <= n; i++){
    for(int j = 2; j <= m; j++){
      dp[i][j] = a[i][j] % x == 0 ? dp[i - 1][j] | dp[i][j - 1] : 0;
    }
  }
  return dp[n][m];
}

void A(){
  cin >> n >> m;
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= m; j++){
      cin >> a[i][j];
    }
  }
  int g = gcd(a[1][1], a[n][m]), ans = 0;
  for(int i = 1; i * i <= g; i++){
    if(g % i == 0){
      ans = max(ans, i * B(i));
      ans = max(ans, g / i * B(g / i));
    }
  }
  cout << ans << '\n';
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  dp[0][1] = dp[1][0] = 1;
  cin >> t;
  while(t--){
    A();
  }
  return 0;
}

```

最后提醒大家一句：**清空不规范，爆零两行泪！**

---

## 作者：__HHX__ (赞：2)

# 思路
因为到状态 $(x, y)$ 最优无法推出状态 $(n, m)$ 最优。

所以就别想在这做动规。

所以我们来探索性质。

答案 $ans$ 一定满足 $ans \mid a_{1,1}$。

所以我们发现可以用 $O(\sqrt n)$ 枚举 $ans$，满足 $ans \mid a_{1,1}$，然后看是否存在路径满足能被 $ans$ 整除。

大家可以使用 $O(NM)$ 动规来判断。

状态为是否可达，转移为若上面或左边可达且能被 $ans$ 整除，则可达。

时间复杂度为 $O(T \sqrt{V} + d(V) \cdot NM)$。

其中 $V = \max a_{i, j}$，$d(V)$ 小于等于 $V$ 的数的最大约数数量。

其中 $d(V) \leq 240$。

# 代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e2 + 3;

int a[N][N];

bool dp[N][N];

int n, m;

bool check(int x) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j] % x == 0) dp[i][j] = (dp[i][j - 1] | dp[i - 1][j]);
    }
  }
  return dp[n][m];
}

void Solve() {
  vector<int> q;
  int p;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  p = __gcd(a[1][1], a[n][m]);
  for (int i = 1; i * i <= p; i++) {
    if (p % i == 0) q.push_back(i), q.push_back(p / i);
  }
  sort(q.begin(), q.end(), greater<int>() );
  for (int u : q) {
    if (check(u)) {
      cout << u << '\n';
      return;
    }
  }
}

int main() {
  dp[0][1] = 1;
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    Solve();
  }
  return 0;
}
```

---

## 作者：Iniaugoty (赞：2)

必然存在一条路径，答案同时是上面每个数字的因数。

每条路径都经过 $a _ {1, 1}$ 和 $a _ {n, m}$，所以答案必然是 $a _ {1, 1}$ 和 $a _ {n, m}$ 的因数，即 $\gcd (a _ {1, 1}, a _ {n, m})$ 的因数。

一个经典且重要的结论是 $\operatorname d (n)$（因数个数）是远小于 $n$ 的。

题中 $a _ i \le 10 ^ 6$，这个范围下 $\max {\operatorname d (a _ i)}$ 大致是一个比较小的三位数。

考虑枚举 $\gcd (a _ {1, 1}, a _ {n, m})$ 的因数，判断是否存在一条路径上所有数都是它的倍数，用 bfs 找就行了。

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)
#define x first
#define y second

using namespace std;
typedef long long LL;
typedef pair<int, int> node;
const int N = 105;

int _, n, m, a[N][N];

int Gcd(int a, int b) { return !b ? a : Gcd(b, a % b); }

bool vis[N][N];
bool Check(int w) {
	F(i, 1, n) F(j, 1, m) vis[i][j] = 0;
	queue<node> q; q.push({1, 1}), vis[1][1] = 1;
	while (!q.empty()) { node u = q.front(); q.pop();
		if (u.x + 1 <= n && a[u.x + 1][u.y] % w == 0 && !vis[u.x + 1][u.y])
			vis[u.x + 1][u.y] = 1, q.push({u.x + 1, u.y});
		if (u.y + 1 <= m && a[u.x][u.y + 1] % w == 0 && !vis[u.x][u.y + 1])
			vis[u.x][u.y + 1] = 1, q.push({u.x, u.y + 1});
	} return vis[n][m];
}

int main() {
// 	freopen("wmyr.in", "r", stdin);
// 	freopen("wmyr.out", "w", stdout);
	ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
	cin >> _; while (_--) {
		cin >> n >> m; F(i, 1, n) F(j, 1, m) cin >> a[i][j];
		int g = Gcd(a[1][1], a[n][m]), ans = 1;
		for (int i = 1; i * i <= g; ++i)
			if (g % i == 0) {
				if (Check(i)) ans = max(ans, i);
				if (Check(g / i)) ans = max(ans, g / i);
			}
		cout << ans << "\n";
	} return 0;
}
```

---

## 作者：OIer_Hhy (赞：1)

这道题，很容易想到 dp。

令 $f_{i,j}$ 表示第 $i$ 行第 $j$ 列的最大 gcd，则状态转移方程为 $f_{i,j}=\max(\gcd(f_{i-1,j},a_{i,j}),\gcd(f_{i,j-1},a_{i,j}))$。

然而这明显不对。

样例 $2$ 中，若按这种方法去做，答案为 $2$，而实际上，是 $3$。

也就是一个状态最优解不一定为下一个状态的最优解！

可怜的蒟蒻我不知如何是好，只能硬着头皮优化。

把二维数组 $f$ 升级成三维。我们把每种情况的 gcd 都存进 $f_{i,j,k}$ 里，状态转移方程变为   $f_{i,j,k}=\gcd(f_{i,j-1,k},a_{i,j})$ 与 $f_{i,j,k}=\gcd(f_{i-1,j,k},a_{i,j})$。

酱紫应该能行了吧！我小心翼翼地交上去，结果……


果然不出我所料，MLE ON #12！

[MLE CODE](https://www.luogu.com.cn/paste/rpmm4dcb)

我只好用 set 代替 vector。

硬着头皮再交一发！

TLE ON #31。

[TLE CODE](https://www.luogu.com.cn/paste/vejduz76)

我只得继续优化。

考虑以下性质：$\gcd(n,k) \ge \gcd(m,k) (n=mq)(q∈{N_+})$。

于是，我们可以删掉每个  $f_{i,j,k}$ 的真因子，只留下它自己。

先初始化出每一个 $k$ 的真因子 $(1 \le k \le 10^6)$，在每次计算完 $f_{i,j,k}$ 后删掉真因子。

预处理时间复杂度为 $O(m \times \sqrt m)$ 为 $10^9$，求值与优化时间复杂度为 $O(n^2 \times k)$，3 秒时限绰绰有余。

Accepted！

[AC CODE](https://www.luogu.com.cn/paste/ufprd7m4)

---

## 作者：Weekoder (赞：1)

### 思路

由于要从 $(1,1)$ 走到 $(n,m)$，答案一定是 $\gcd(a_{1,1},a_{n,m})$ 的因数（$1\sim \gcd(a_{1,1},a_{n,m})$），可以 $\sqrt{\gcd(a_{1,1},a_{n,m})}$ 枚举，判断是否存在路径即可。

如何判断路径？考虑 $dp$，设 $dp_{i,j}$ 为是否能到达 $(i,j)$。假设当前枚举到的因子为 $x$，显然有初始状态 $dp_{1,1}=[x|a_{i,j}]$。而状态转移方程也很简单：要保证当前的 $a_{i,j}$ 是 $x$ 的倍数，而且左边和上面至少有一个地方能转移过来，即：

$$
dp_{i,j}=(dp_{i-1,j}\text{ or }dp_{i,j-1}) \text{ and }x|a_{i,j}
$$

最后判断 $dp_{n,m}$ 是否为真，取最大值即可。注意，答案至少应该为 $1$。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 105;

int T, n, m, a[N][N], ans;

bool dp[N][N];

void solve(int x) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1) {
                dp[i][j] = (a[i][j] % x == 0);
                continue;
            }    
            dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]) && (a[i][j] % x == 0);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while (T --) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> a[i][j];
        int x = __gcd(a[1][1], a[n][m]), ans = 1;
        for (int i = 1; i * i <= x; i++) {
            if (x % i)
                continue;
            memset(dp, 0, sizeof dp);
            solve(i);
            if (dp[n][m])
                ans = max(ans, i);
            memset(dp, 0, sizeof dp);
            solve(x / i);
            if (dp[n][m])
                ans = max(ans, x / i);
        }
        cout << ans << "\n";
    }
    return 0;
} 
```

---

## 作者：yshpdyt (赞：1)

## 闲话
全场被 hack 似光了，甚至 std。
## 题意
$n\times m$  网格，最大化从 $(1,1)$ 到 $(n,m)$ 路径上的值的最大公约数。
## Sol
记 $w=\gcd(a_{1,1},a_{n,m})$，那么答案肯定是 $w$ 的因数，求出其所有因数然后 bfs，记 $w \equiv 0\pmod p$，答案合法当且仅当路径上所有点 $a_{i,j}\equiv 0\pmod p$ 。

得卡卡常，不然被 hack 得很惨。

顺带一提 hack 数据都是往网格中填因数很多的数字，在最后放几个因数很少的。
## Code
```cpp// LUOGU_RID: 155155393
#include<bits/stdc++.h>
#define ll long long
#define N 205
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,m;
ll a[N][N];
bool vis[N*N];
ll w;
queue<pair<ll,ll> >q;
bool bfs(ll x,ll y,ll p){
    while(!q.empty())q.pop();
    q.push({x,y});
    vis[(x-1)*m+y]=1;
    while(!q.empty()){
        auto t=q.front();
        q.pop();
        vis[(t.fi-1)*m+t.se]=0;
        if(t.fi==n&&t.se==m)return 1;
        for(int i=1;i<=2;i++){
            ll nx=t.fi+(i==1);
            ll ny=t.se+(i==2);
            if(nx>n)continue;
            if(ny>m)continue;
            if(vis[(nx-1)*m+ny]||a[nx][ny]%p)continue;
            q.push({nx,ny});
            vis[(nx-1)*m+ny]=1;
        }
    }
    return 0;
}
vector<ll>v; 
bool cmp(ll x,ll y){
    return x>y;
}
void sol(){
    v.clear();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    w=__gcd(a[1][1],a[n][m]);
    int i=1;
    for(i=1;i*i<w;i++){
        if(w%i==0){
            v.push_back(w/i);
            v.push_back(i);
        }
    }
    if(i*i==w)v.push_back(i);
    sort(v.begin(),v.end(),cmp);
    for(auto i:v){
        if(bfs(1,1,i)){
            cout<<i<<endl;
            return ;
        }
    }

}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：_xguagua_Firefly_ (赞：0)

### 分析

首先我们看到数据范围，$\sum nm \le 2 \times 10 ^ 5$，所以我们的复杂度一定是 $\Omicron(nm)$ 再带一个可以比较大的常数。

发现直接做比较难做，考虑用判断代替求解。我们枚举 $x$ 表示路径上的数的公因数，然后 DP 判断答案是否合法，设 $dp _ {i,j}$ 表示 从 $(1,1)$ 到 $(i,j)$ 是否有公因数为 $x$ 的路径，转移方程比较显然，$dp _ {i,j} = (dp _ {i - 1,j} \wedge [a _ {i,j} \bmod x = 0]) \vee (dp _ {i,j - 1} \wedge [a _ {i,j} \bmod x = 0])$。直接转移，$dp _ {n,m}$ 就表示 $x$ 是否合法。

因为路径一定经过 $(1,1)$ 和 $(n,m)$，则我们可以直接枚举 $\gcd (a _ {1,1},a _ {n,m})$ 的因数，然后进行判断，因此可以直接给 $dp _{1,1}$ 赋值为 $1$。

时间复杂度 $\Omicron(nm\delta)$，其中 $\delta$ 表示 $\gcd(a _ {1,1},a _ {n,m})$ 的因数个数，打表发现 $10 ^ {6}$ 范围内 $\delta$ 的最大值为 $240$，能过。

### Code

```cpp
#include <bits/extc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 114;
int T;
int n,m,a[MAXN][MAXN];
bool dp[MAXN][MAXN];
inline bool check(int x)
{
    memset(dp,0,sizeof(dp));
    dp[1][1] = 1;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
        {
            if(i == 1 && j == 1)
                continue;
            dp[i][j] = (dp[i - 1][j] && (a[i][j] % x == 0)) || (dp[i][j - 1] && (a[i][j] % x == 0));
        }
    }
    return dp[n][m];
}
inline void Solve()
{
    cin >> n >> m;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= m;j++)
            cin >> a[i][j];
    }
    int num = __gcd(a[1][1],a[n][m]);
    set<int> ans;
    for(int i = 1;i * i <= num;i++)
    {
        if(num % i == 0)
        {
            if(check(num / i))
            {
                cout << (num / i) << "\n";
                return ;
            }
            if(check(i))
                ans.emplace(i);
        }
    }
    cout << (*ans.rbegin()) << "\n";
}
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> T;
    while(T--)
        Solve();
}
```

---

## 作者：coding_goat (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1955G)

[可能更好的阅读体验](https://www.cnblogs.com/CodingGoat/p/18467568)

我们暴力枚举可能的答案 $k$，然后每一次检查时跑一遍 dp。

设 $f_{i,j}$ 表示在格子 $(i,j)$ 是否可以满足有一条路径可以到达该格子且该格子是否为 $k$ 的倍数，递推式即为 $f_{i,j}=[k\mid a_{i,j} ]\operatorname{and} [f_{i-1,j} \operatorname{or} f_{i,j-1}]$ 最后的答案即是 $f_{n,m}$。

时间复杂度 $O(nm\sqrt{V})$，其中 $V$ 是值域。

代码：

```cpp
bool check(int k) {
	m0(f);
	f[1][1]=1;
	For(i,1,n) For(j,1,m) {
		if(a[i][j]%k==0) {
			f[i][j]|=f[i-1][j]|f[i][j-1];
		}
	}
	return f[1][1]&f[n][m];
}
void work() {
	in2(n,m);
	For(i,1,n) inn(a[i],m);
	int g=__gcd(a[1][1],a[n][m]);
	int ans=0;
	
	for(int i=1;i*i<=g;i++){
		if(g%i==0) {
			if(check(i))
				ans=max(ans,i);
			if(check(g/i))
				ans=max(ans,g/i);
		}
	}
	cout<<ans<<'\n';
}
```

---

## 作者：210101zhaosicheng (赞：0)

# 题解：CF1955G GCD on a grid

## 题意分析

给你一个 $n\times m$ 的矩阵，求出 $a[1][1]$ 到 $a[n][m]$ 的路径上所有的数字的 gcd 的最大值。

说的再明确一下，就是让你找一条从 $(1,1)$ 到 $(n,m)$ 的路径，使得上面的每一个数的 gcd 最终值最大。

结合样例说一下：
```
2 3
30 20 30
15 25 40
```

显然，这是一个 $2$ 行 $3$ 列的矩阵，从左上角到右下角的每一条路径上的 $\gcd$ 最大值，选择的路径为 $30\to 20\to 30\to 40$ 此时有最大值为 $10$。

**注意**

题目说明了只能向右走或者向下走。

有多组解取最小的。

## 思路分析

因为 只能**向右**走或者**向下**走。

所以可以很轻松的想到 DP（动态规划）。

但是，当你打完 DP（动态规划）以后，你会发现：似乎 **没有办法**从局部最优解扩散到全局最优解，因此只能放弃。

转念一想，如果把起点和终点的最大公约数算出来然后用质数筛把因子筛出来行不行？

但是因为筛质数传递的时候太慢了，容易 TLE 所以也被否了。

最后时刻灵光乍现：

如果把起点和终点的最大公约数算出来然后在枚举它的每一个因子看看能否传递呢？

如果可以，那么肯定是一组解，否则，就继续寻找另一组解。

思路通过，开码！

UPD：害怕有同学看不懂 cnt，所以我解释一下，cnt 用来 DP，可以不用每次都清空 $dp$ 数组，更加省时间。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[114][114],a[514][514],n,m,T,cnt=1;//cnt一定要定义在全局，我也不知道为什么，但是当时定义了局部变量以后就一直不对，如果有知道的可以私信我
int gcd(int a,int b)//欧几里得求最大公约数
{
	if(a==0)
	{
		return b;
	}
	if(b==0)
	{
		return a;
	}
	int c=a%b;
	while(c!=0)
	{
		a=b;
		b=c;
		c=a%b;
	}
	return b;
}
bool check(int x,const int num)//x是传递的数字，num是vis数组的标记
{
	dp[1][1]=num;//第一个肯定能整除，因为x是起点和终点的最大公约数
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(i==j&&j==1)//如果是1,1直接跳过
			{
				continue;
			}
			if(i==1)//如果在第一行
			{
				if(a[i][j]%x==0&&dp[i][j-1]==num)//如果当前数可以整除x并且左侧也可以整除x（即有路径到达当前点）。
				{
					dp[i][j]=num;
				}
				continue;
			}
			if(j==1)//在第一列
			{
				if(a[i][j]%x==0&&dp[i-1][j]==num)//上方有路径可以到达并且当前点是x的倍数（即可以整除x）
				{
					dp[i][j]=num;
				}
				continue;
			}
			if(i==1||j==1)//当时d代码心态炸了防止C++脑瘫的（不用管）
			{
				continue;
			}
			if((dp[i-1][j]==num||dp[i][j-1]==num)&&a[i][j]%x==0)//如果有路径到达并且当前点可以整除x那么就可以到达
			{
				dp[i][j]=num;
			}
			
		}
	}
	if(dp[n][m]==num)//判断是否可行
	{
		return 1;
	}
	return 0;
}
void solve()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	int t=gcd(a[1][1],a[n][m]);//起点和终点的最大公约数
	for(int i=1;i*i<=t;i++)//从1~平方根找因子
	{
		if(t%i==0)//是因子
		{
			cnt++;//标记加上1
			if(check(t/i,cnt))//判断大的因子
			{
				cout<<t/i<<'\n';
				goto fuck;//找到就跳出
			}
			if(i*i==t)//似乎没啥卵用
			{
				break;
			}
		}
	}
	for(int i=sqrt(t);i>=1;i--)//从平方根向下找
	{
		if(t%i==0)//可以被整除
		{
			cnt++;
			if(check(i,cnt))
			{
				cout<<i<<'\n';//输出
				goto fuck;//跳出
			}
			if(i*i==t)
			{
				continue;
			}
		}
	}
	fuck:;
//	cout<<n<<' '<<m<<'\n';
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=m;j++)
//		{
//			cout<<a[i][j]<<' ';
//		}
//		putchar(10);
//	}
//	putchar(10);
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=m;j++)
//		{
//			cout<<dp[i][j]<<' ';
//		}
//		putchar(10);
//	}
}
int main()
{
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	cin>>T;//没啥好解释的
	while(T--)
	{
		solve();
	}
	return 0;
}
/*
3
2 3
30 20 30
15 25 40
3 3
12 4 9
3 12 2
8 3 12
2 4
2 4 6 8
1 3 6 9
*/
```

---

