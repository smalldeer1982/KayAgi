# Tourism

## 题目描述

Masha lives in a country with $ n $ cities numbered from $ 1 $ to $ n $ . She lives in the city number $ 1 $ .

There is a direct train route between each pair of distinct cities $ i $ and $ j $ , where $ i \neq j $ . In total there are $ n(n-1) $ distinct routes. Every route has a cost, cost for route from $ i $ to $ j $ may be different from the cost of route from $ j $ to $ i $ .

Masha wants to start her journey in city $ 1 $ , take exactly $ k $ routes from one city to another and as a result return to the city $ 1 $ . Masha is really careful with money, so she wants the journey to be as cheap as possible. To do so Masha doesn't mind visiting a city multiple times or even taking the same route multiple times.

Masha doesn't want her journey to have odd cycles. Formally, if you can select visited by Masha city $ v $ , take odd number of routes used by Masha in her journey and return to the city $ v $ , such journey is considered unsuccessful.

Help Masha to find the cheapest (with minimal total cost of all taken routes) successful journey.

## 样例 #1

### 输入

```
5 8
0 1 2 2 0
0 0 1 1 2
0 1 0 0 0
2 1 1 0 0
2 0 1 2 0```

### 输出

```
2```

## 样例 #2

### 输入

```
3 2
0 1 1
2 0 1
2 2 0```

### 输出

```
3```

# 题解

## 作者：Dilute (赞：11)

[$$\color{darkblue}\Huge\texttt{My blog}$$](https://dilute.xyz/2020/02/24/Solutions/Solution-CF1314D/)

> 开场 10 分钟就有人过的 1D ，你值得拥有！
>
> $\texttt{swap(B, D)}$ 警告。

精读题面，发现 $k \le 10$ ，考虑从这个性质中寻找解法。

$k \le 10$ 意味着最后真正对结果产生贡献的节点只会有 $10$ 个以下。

结合题面中给出的「没有奇环」条件，容易想到二分图黑白染色。

考虑对每个点随机染 黑 / 白色，再强制走两端颜色 **不相同** 的边。

这个过程可以用简单 dp ，$f_{i, j}$ 表示走了 $i$ 条边，当前在节点 $j$ 的最小花费，$\Theta(n^2k)$ 直接转移即可。

重复这个过程若干遍即可。

我们继续考虑为什么这个解法是大概率正确的。

考虑如果我们已经知道了最终的一条最优路径，这上面最多有 $k$ 个点。

那么这 $k$ 个点在一种染色方案中黑白相间的概率是 $\frac{1}{2^{k - 1}}$ ，在 $k = 10$ 的情况下就是 $\frac{1}{512}$。

随机 $5000$ 次的情况下，随不出正确答案的概率是 $(\frac{511}{512})^{5000} \approx 0.000056845461206$ ，非常小，可以忽略不计。

这解法就 ** 离谱。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

ll f[20][100], dis[100][100];
int c[100];

int main(){
    srand((unsigned)time(NULL));
    int n = inp();
    int k = inp();
    int T = 5000;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            dis[i][j] = inp();
    ll ans = 1e18;
    while(T--){
        for(int i = 1; i <= n; i++){
            c[i] = rand() & 1;
            f[0][i] = 1e18;
        }
        f[0][1] = 0;
        for(int i = 0; i < k; i++){
            for(int j = 1; j <= n; j++)
                f[i + 1][j] = 1e18;
            for(int j = 1; j <= n; j++)
                for(int u = 1; u <= n; u++)
                    if(c[j] != c[u])
                        f[i + 1][u] = std::min(f[i + 1][u], f[i][j] + dis[j][u]);
        }
        ans = std::min(ans, f[k][1]);
    }
    printf("%lld\n", ans);
}
```

---

## 作者：Petit_Souris (赞：9)

来看看确定性做法，全对！！1

假设路径经过的 $k+1$ 个点依次为 $p_1,p_2\dots p_{k+1}$，其中 $p_1=p_{k+1}=1$，那么没有奇环其实就是限制了 $p$ 的奇数位和 $p$ 的偶数位没有相同元素。

我们可以先固定奇数位的剩余 $\frac{k}{2}-1$ 个点，对于相邻两个奇数位的点 $(u,v)$，找一个偶数位的点 $w$ 使得 $u\to w\to v$ 最短。（因为奇偶位置独立，偶数位内部是可以重复经过点的，所以每个奇数点的相邻 pair 是独立的）

每次搜完奇数位的点之后对于每个 $(u,v)$ 枚举 $w$ 的时间复杂度为 $\mathcal O(n^{\frac{k}{2}})$，过不了。考虑预处理，对于每个 $(u,v)$，预处理前 $\frac{k}{2}+1$ 优的 $w$，搜索的时候枚举前 $\frac{k}{2}+1$ 优解中第一个没有出现在奇数点集里的点即可。预处理复杂度 $\mathcal O(n^3k)$，搜索复杂度 $\mathcal O(kn^{\frac{k}{2}-1})$，可以通过。

反观随机化，理论上应当随机 $2^k$ 次染色，期望复杂度 $\mathcal O(2^kkn^2)$，还有约 $10^{-6}$ 的概率不能得到正确答案，错完了！！1

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const ll N=85,INF=1e15;
ll n,k,a[N][N],d[N][N][7],r[N],ans=INF,v[N];
ll calc(ll i,ll j,ll k){
	if(!k)return INF;
	return a[i][k]+a[k][j];
}
void dfs(ll x){
	if(x>k/2){
		ll res=0;
		rep(i,1,k/2-1){
			rep(p,0,5){
				if(!v[d[r[i]][r[i+1]][p]]){
					res+=calc(r[i],r[i+1],d[r[i]][r[i+1]][p]);
					break;
				}
			}
		}
		rep(p,0,5){
			if(!v[d[r[k/2]][r[1]][p]]){
				res+=calc(r[k/2],r[1],d[r[k/2]][r[1]][p]);
				break;
			}
		}
		ans=min(ans,res);
		return ;
	}
	rep(i,1,n){
		r[x]=i;
		v[i]++;
		dfs(x+1);
		r[x]=0;
		v[i]--;
	}
}
int main(){
	n=read(),k=read();
	rep(i,1,n){
		rep(j,1,n)a[i][j]=read();
	}
	rep(i,1,n){
		rep(j,1,n){
			rep(k,1,n){
				if(k==i||k==j)continue;
				d[i][j][6]=k;
				per(p,5,0){
					if(calc(i,j,d[i][j][p+1])<calc(i,j,d[i][j][p]))swap(d[i][j][p+1],d[i][j][p]);
					else break;
				}
			}
		}
	}
	r[1]=1,v[1]=1;
	dfs(2);
	write(ans);
	return 0;
}
```

---

## 作者：aison (赞：4)

我来写一个不是随机的做法。设答案路径为$a_1,a_2,...,a_k,a_{k+1}$,其中$a_1=a_{k+1}=1$。不存在奇环即对于任意奇偶性不同的$i,j$，满足$a_i\not=a_j$

首先没有奇环让人想到二分图。借用二分图的思想，我们可以枚举路径中的$a_3,a_5,...,a_{k-1}$，现在我们需要确定下标为偶数的点。因为不能有奇环条件的存在，偶数下标的点不能与奇数下标的点相同，但是奇数下标的不同的点最多只有5个，因此我们可以预处理出对于每个有序点对（u,v），从u沿相邻边直接走到某个不为1的点，然后直接到达v的前4短的路径，以及其对应的中间点的序号，这一步操作只需要枚举中间点，对于每个点对是$O(n)$的。然后对于每一对相邻的奇数下标的点$a_{2t-1},a_{2t+1}$，确定一个最优的夹在它们中间的$a_{2t}$，使得$a_{2t}$与所有的奇数下标的点都不同，且路径长度最短，直接在前面处理出的四个候选解当中查找即可。

预处理复杂度$O(n^3)$，枚举复杂度$O((\frac{k}{2}-1)n^{\frac{k}{2}-1})$，可以通过。

---

## 作者：DegChuZm (赞：3)

### sol
因为有这个奇环的限制，直接去做是不好做的。

但是因为这是奇环，于是把图黑白染色再去做。

黑白染色后就是一个普通的 dp 板子了。

但是，怎么才能确定正确的染色序列呢？

不好弄，枚举是 $2^n$ 级的，骨灰都给你 T 没咯。

~~不会优化~~，于是考虑随机化这个东西（随机染色），这里我随机的是 $4000$ 次，然后过了。

那么为什么随机化是这么大概率是对的呢？

从 $1$ 到回到自己要走 $k$ 步，那么最多会经过 $k-1$ 个点，显然只有这 $k-1$ 个点的颜色会对答案产生影响。

那么一次的错误率最大就为 $\frac{511}{512}$， 重复 $4000$ 次还错的概率大概是 $0.0004$ 左右，比出金概率还低，没过只能说明脸背。

于是愉悦的给出代码。

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[81][81],opt,x,y,cnt,col[81],dis[81][81],ans=INT_MAX;
string s;
struct dcz{
	int u,st,d;
	bool operator<(const dcz &x)const{
		return x.d<d;
	}
};
priority_queue<dcz> q; 
void running(){
	for(int st=0;st<m;st++){
		for(int u=1;u<=n;u++){
			for(int i=1;i<=n;i++){
				if(col[i]!=col[u]){
					if(dis[i][st+1]>dis[u][st]+a[u][i]){
						dis[i][st+1]=dis[u][st]+a[u][i];
					}
				}
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	srand(time(0));
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=4000;i++){
		for(int j=1;j<=n;j++) col[j]=rand()&1;
		memset(dis,0x3f,sizeof dis);
		dis[1][0]=0;
		running();
		ans=min(ans,dis[1][m]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：SunsetGlow95 (赞：2)

# 题解 - CF1310D Tourism

如果像我一样没有注意到二分图，也完全不会随机化，那该怎么办？

## 简述题意

给一图，求经过点 $1$、点数为 $k$、不含奇环、可以重复经过点和边的边权和最小环路。$n\le 80$，$k\le 10$ 且 $k$ 为偶数。

## 分析

我们首先考虑 meet in the middle，枚举除了点 $1$ 以外的前 $k/2-1$ 个点和后 $k/2-1$ 个点，进行搜索。最后再枚举中间三个点来合并。然后你发现会直接 TLE，如果像我一样实现常数巨大。

对两个部分分别优化：

- 对于搜索中的 TLE，发现很多边是不优的，所以选择前若干小出边 DFS，本人使用 $37$，只是因为它刚好通过了。
- 对于合并中的 TLE，发现端点处存储的答案太多了，所以对每个端点只保留前若干小方案，本人使用 $3$。

然后你发现 WA on test 129。打开发现它形如：

```plain
0 100 100 100 100...
100 0 100...
```

也就是说有很多同类点，导致前几小的策略容易被迷惑。

所以考虑删去同质点。对于一个点 $p$，如果存在另外至少 $2$ 个点 $q_1,q_2$，使得不考虑 $p,q$ 之间的连边，$p,q$ 向外的连边完全相同，那么把 $p$ 删去。（之所以要保留两个，是因为可以来回走，可能是优的。）

然后就通过了……\qiao。

可能是可以 hack 的，但是感觉 hack 也太累了吧。

代码实现上，感觉把这道题抬到了一个不属于它的高度。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MXN = 85;
const int LIM = 3;
const int CH = 37;
int N, K, val[MXN][MXN], ans(2e9);
bool disabled[MXN];
vector<pair<int, int>> choice1[MXN], choice2[MXN];
vector<pair<int, vector<int>>> mp1[MXN], mp2[MXN];

void dfs1(int p, vector<int>& path, int len) {
  if (path.size() == K / 2 - 1) {
    mp1[p].push_back(make_pair(len, path));
    if (mp1[p].size() > LIM) mp1[p].erase(max_element(mp1[p].begin(), mp1[p].end()));
    return;
  }
  for (int i(0); i != min(static_cast<int>(choice1[p].size()), CH); ++i) {
    int q(choice1[p][i].second);
    if (path.size() >= 3 && q == path[path.size() - 3]) continue;
    path.push_back(q);
    dfs1(q, path, len + val[p][q]);
    path.pop_back();
  }
}

void dfs2(int p, vector<int>& path, int len) {
  if (path.size() == K / 2 - 1) {
    mp2[p].push_back(make_pair(len, path));
    if (mp2[p].size() > LIM) mp2[p].erase(max_element(mp2[p].begin(), mp2[p].end()));
    return;
  }
  for (int i(0); i != min(static_cast<int>(choice2[p].size()), CH); ++i) {
    int q(choice2[p][i].second);
    if (path.size() >= 3 && q == path[path.size() - 3]) continue;
    path.push_back(q);
    dfs2(q, path, len + val[q][p]);
    path.pop_back();
  }
}

bool illegal(const vector<int>& path) {
  for (int i(1); i < path.size(); i += 2) {
    for (int j(0); j != path.size(); ++j) {
      if (path[(j + i) % path.size()] == path[j]) return true;
    }
  }
  return false;
}

int main() {
  cin >> N >> K;
  for (int i(0); i != N; ++i)
    for (int j(0); j != N; ++j) cin >> val[i][j];
  for (int i(1); i != N; ++i) {
    int cnt(0);
    for (int j(1); j != i; ++j) {
      if (disabled[j]) continue;
      bool same(true);
      for (int k(0); k != N; ++k)
        if (k != i && k != j && (val[k][i] != val[k][j] || val[i][k] != val[j][k]))
          same = false;
      cnt += same;
    }
    if (cnt >= 2) disabled[i] = true;
  }
  for (int i(0); i != N; ++i) {
    if (disabled[i]) continue;
    for (int j(0); j != N; ++j)
      if (j != i && !disabled[j])
        choice1[i].push_back(make_pair(val[i][j], j)),
        choice2[i].push_back(make_pair(val[j][i], j));
    sort(choice1[i].begin(), choice1[i].end());
    sort(choice2[i].begin(), choice2[i].end());
  }
  vector<int> tmp;
  dfs1(0, tmp, 0);
  dfs2(0, tmp, 0);
  for (int i(0); i != N; ++i) {
    for (int j(0); j != N; ++j) {
      for (int a(0); a != mp1[i].size(); ++a) {
        for (int b(0); b != mp2[j].size(); ++b) {
          for (int k(0); k != N; ++k) {
            vector<int> path(mp1[i][a].second);
            path.push_back(k);
            for (int d(K / 2 - 2); ~d; --d) path.push_back(mp2[j][b].second[d]);
            path.push_back(0);
            if (!illegal(path)) {
              ans = min(ans, mp1[i][a].first + val[i][k] + val[k][j] + mp2[j][b].first);
            }
          }
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
```

---

## 作者：1saunoya (赞：2)

### **吐槽:** 
为什么这场CF…不寻常，1D不应该是2F么…[悲]

### **题意:**
给定一个完全图，路径带权且 $dis_{i,j}$ 不一定等于 $dis_{j,i}$，边数为$k$不存在奇环且起点和终点都是$1$的最小路径。

由于要满足不存在奇环，需要将这个图黑白染色，然后每次都经过黑白边，这样就不会有奇环。但是枚举这个点是黑还是白色…复杂度就可以到 $2^n * kn^2$，显然不可以，然后会发现实际上你最多 $k$ 个点需要染色正确，因为你的边不会超过 $k$，所以理论上$2^{k}$次随机就够用了。

### **code:**

```cpp
#include <bits/stdc++.h>
int read() {
	int x = 0 ;
	char c = getchar() ;
	while(c < 48) c = getchar() ;
	while(c > 47) x = x * 10 + (c - 48) , c = getchar() ;
	return x ;
}

int n, k;
const int maxn = 88 ;
int dis[maxn][maxn] ;
int dp[11][maxn] ;
int main() {
	n = read() , k = read() ;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++)
			dis[i][j] = read() ;
	int seed = 0 ;
	for(char c : "sooketxdy")
		seed = seed * 233 + c ;
	srand(seed) ;
	int times = 5000 ;
	std :: vector < int > col(n + 1 , 0);
	int ans = 1e9 ;
	while(times --) {
		for(int i = 1 ; i <= n ; i ++)
			col[i] = rand() & 1 ;
		memset(dp , 0x3f , sizeof(dp)) ;
		dp[0][1] = 0;
		for(int kk = 0 ; kk < k ; kk ++)
			for(int i = 1 ; i <= n ; i ++)
				for(int j = 1 ; j <= n ; j ++)
					if(col[i] ^ col[j]) dp[kk + 1][j] = std :: min(dp[kk + 1][j] , dp[kk][i] + dis[i][j]) ;
		ans = std :: min(ans , dp[k][1]) ;
	}
	printf("%d" , ans) ;
	return 0 ;
}
```

---

## 作者：liujiaxi123456 (赞：1)

### 思路：

首先想的是正向一条边一条的转移，但是这样后效性没法记录。

又去想 DP 一个点经过一个偶环后的答案，但仍然没有办法记录后效性来拼接。

只能考虑分析性质，抽象模型：

- 首先，由于是完全图，所以我们相当于可以**忽略图的结构**，直接找出一个序列，并求这个序列的答案。

- 而不能有奇环的条件，相当于奇数位和偶数不能有相同的元素。

于是大致思路很容易就能想到：

- 先暴力搜索奇数位（因为首尾必为 1，所以这样枚举的次数要少一点）。

- 然后去 DP 剩余偶数位填什么：

  - 显然只与两边的奇数位有关，于是预处理任意两点之间填什么最优。
 
  - 但最优未必合法，于是进行排序，从小到大挨个试即可。
 
最后复杂度为：

- 预处理：$O(n^3) $。

- 搜索 + DP：$O(n^{\frac k2-1}(\frac k2)^2) $。

### Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;

const int Maxn = 85, INF = INT_MAX/2-5;

namespace Josh_zmf {
	
	int N, K, dis[Maxn][Maxn], chose[Maxn], bj[Maxn]; ll ans = INF; 
	vector <pair<int, int> > mn[Maxn][Maxn];

	inline void solve(int i) {
		if(i == K/2+1) {
			ll res = 0;
			// printf("solve:: \n");
			// printf("chose:: ");
			// for(int i=1; i<=K/2+1; i++)	printf("%d, ", chose[i]);
			// puts("");
			for(int i=2; i<=K/2+1; i++) {
				bool flag = 0;
				for(auto [val, x]: mn[chose[i-1]][chose[i]]) {
					if(bj[x])	continue;
					// printf("x:%d, val:%d\n", x, val);
					res += val, flag = 1; break;
				}
				if(!flag)	return ;
			}
			// printf("res:%lld, ans:%lld\n", res, ans);
			// puts("____________________");
			return ans = min(ans, res), void();
		}
		for(int u=1; u<=N; u++) {
			chose[i] = u, bj[u]++, solve(i+1), bj[u]--;
		}
	}

	inline int main() {
		cin>> N>> K;
		for(int i=1; i<=N; i++) {
			for(int j=1; j<=N; j++) {
				cin>> dis[i][j];
			}
			dis[i][i] = INF;
		}
		for(int u=1; u<=N; u++) {
			for(int v=1; v<=N; v++) {
				for(int x=1; x<=N; x++) {
					mn[u][v].push_back({dis[u][x]+dis[x][v], x});
				}
				sort(mn[u][v].begin(), mn[u][v].end());
			}
		}
		chose[1] = chose[K/2+1] = 1, solve(2);
		cout<< ans<< '\n';
		return 0;
	}

}

signed main() {
	Josh_zmf::main();
	return 0;
}
```

---

## 作者：chlchl (赞：1)

人类智慧。

## Solution 1
注意力惊人，发现 $k\le 10$。也就是说加上起、终点最多经过 $10$ 个点，并且第 $1$ 个和最后一个都是 $1$。

考虑枚举第 $2,4,6,8$ 个点经过了什么，这里枚举是 $O(n^4)$ 的。那么对于剩下的点 $x$，设其前后经过的点为 $u,v$，那么要找一个在 $2,4,6,8$ 个点都没有到过的 $x$，使得 $u\rightarrow x\rightarrow v$ 的花费最小。

时间复杂度 $O(n^5)$，无法通过。

显然可以利用与 [这题](https://www.luogu.com.cn/problem/P8817) 相同的 trick，显然只需要枚举与 $u$ 最近的 $5$ 个点，最优答案一定被包含在内。

时间复杂度降为 $O(n^4)$，带一个 $5$ 的常数，可以通过。

## Solution 2
人类智慧说的肯定不是 Sol 1 的解法，因为它太平凡了。

注意力十分惊人，不能有奇环，即走过的路线是二分图。

考虑将图上所有点**随机**黑白染色，每次只能往颜色不同的地方走。然后我们显然可以通过 DP 找到这个情况下的最短路线。

具体地，$f_{i,j}$ 表示走了 $i$ 条边后现在在 $j$ 点的最优答案。转移时枚举上一步所在的点，取最小值即可，这个是极其简单的，时间复杂度 $O(n^2k)$。

但是在一次随机染色中，答案并不一定会出现，有可能答案中经过的相邻两个点被染成同色。此时我们只要随机**足够多次**就好了。

更详细地，答案里经过的每个点都被染对色的概率仅为 $\dfrac{1}{2^9}$（每个点随机选择黑或白，但是要求一定要黑白交错），错误概率为 $\dfrac{2^9-1}{2^9}$。

设随机 $T$ 次，那么出错概率是 $\bigg(\dfrac{2^9-1}{2^9}\bigg)^T$。

当 $T=3000$ 时，出错概率为 $0.2\%$。~~我不会告诉你我跑 $T=3042$ 的时候 ``WA on #47``~~。

当 $T=4000$ 时，出错概率是 $0.04\%$，比较稳。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 80 + 5;
int n, k, col[N];
ll ans = 1e18, v[N][N], f[N][N];

int rnd(int l, int r){
	return 1ll * rand() * RAND_MAX % (r - l + 1) + l;
}

void solve(){
	memset(f, 0x3f, sizeof(f));
	f[0][1] = 0;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=n;j++){
			for(int l=1;l<=n;l++)
				if(col[l] ^ col[j])
					f[i][j] = min(f[i][j], f[i - 1][l] + v[l][j]);
		}
	}
	ans = min(ans, f[k][1]);
}

int main(){
	srand(time(0));
	scanf("%d%d", &n, &k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld", &v[i][j]);
	for(int T=1;T<=4244;T++){
		col[1] = 1;//0 白 1 黑 
		for(int i=2;i<=n;i++)
			col[i] = rnd(0, 1);
		solve();
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：RockyYue (赞：1)

### 题意

给你一个 $n$ 个点图和一个正整数 $k$，边有边权，求从点 $1$ 经过恰好 $k$ 条边回到点 $1$ 且这条路径上没有奇环的最小距离。

其中 $n\le 80,2\le k\le 10$。

### 解法

> Trick: 当题目中出现一些限制比较弱的条件，不方便判断时，可以通过随机染色的方法创造更强的条件解决，这里染色的原理是创造一些必定在限制内的方案。不要担心随机染色概率小，只要次数足够多可以逼近正解。

> Tip: 不要一看到一个值数据范围很小就想状压，也要往染色方面考虑。

没有奇环可以联想到二分图，即走过的路径是一个二分图。这个条件限制过弱，不易处理。而二分图恰好可以染色，于是对每个点随机染成黑或白，尝试寻找原图的一些二分图子图，具体方案是每次只走两端点颜色不同的边，如果正确答案对应的路径刚好在当前方案中被染为黑白交替，就相当于去除了奇环的条件。

在去除奇环条件的基础上考虑 DP，设 $f_{u,i}$ 表示点 $1$ 走到点 $u$ 一共 $k$ 步，且只走合法边时的最短路，第一层循环枚举步数，后面枚举一条合法边，通过这条边转移，这样一次随机化的复杂度就是 $O(kn^2)$。

接下来分析正确概率，假设只有一条最优路径（最劣情况），那么这条路径被黑白交替染色的概率为 $\frac{1}{2^{k-1}}$，这个概率最小为 $\frac{1}{512}$，那么我们使执行次数 $T$ 足够大，总正确率 $1-(1-\frac{1}{512})^T$ 便会足够大。

---

## 作者：Kexi_ (赞：0)

绷不住了，随机 1145 次的时候挂了一发。

## Solution

首先澄清一下题意，是给你路径长度，让你走一圈走回来，路径长度和最小且不含奇环。重点，两地之间距离可能不相等，这点在代码有体现。

来讲一下这个随机的算法吧。首先题面有关奇环，想到二分图染色。

可以看到这个数据范围非常的小，k 更是只有一位数左右，于是我们可以考虑随机化。

随机给所有节点染色，然后强制走黑白交替的节点。这样就可以保证我们走的一定是一个不含奇环的二分图，这保证了咱们所有随机情况的**正确性**。

然后考虑**最优性**。因为我们最终只会走 k 条边，而 k 不大于 10 ，所以每次随机染色最多只有 $\frac{511}{512}$ 的概率染错。在我们多次随机后，这个概率将降的很低。

所以，我们总会有一次随机到那个最优的方案。而这个最优方案就可以通过 $\min$ 函数筛出来，就得到了答案！我们在实现时暴力转移即可。

大体思路讲解就这些，具体有一些细节上的问题看代码。


```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
#define N 82
#define K 12
#define ri register int
using namespace std;
int ans,n,k,c[N],dp[N][K],edge[N][N];
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	srand(time(NULL));
	cin>>n>>k;
	for(ri i(1);i<=n;i++)
	{
		for(ri j(1);j<=n;j++)
		{
			cin>>edge[i][j];
		}
	}
	
	int T=5114.5; ans=inf;
	while(T--)
	{
		memset(dp,inf,sizeof(dp)); dp[1][0]=0;
    //dp[n][k]代表走了k条路径到点n的最短距离和
		for(ri i(1);i<=n;i++)
		{
			c[i]=rand()&1;
		}
		
		for(ri i(1);i<=k;i++)
		{
			for(ri j(1);j<=n;j++)
			{
				for(ri l(1);l<=n;l++)
				{
					if(c[j]!=c[l])
					{
						dp[j][i]=min(dp[j][i],dp[l][i-1]+edge[l][j]);// 这个位置要注意，edge[j][l]!=edge[l][j]，要动脑想一下怎么写
					}
				}
			}
		}
		ans=min(ans,dp[1][k]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

神秘的。直接做看上去十分困难，但是考虑到图中不能走出奇环，利用“二分图不存在奇环”这个性质，给图中每一个点随机赋值为 $0/1$，然后建图要求两个点权值不同才连边。此时不需要考虑奇环限制，暴力跑 dp 即可。因为一次算法正确率极低，而又不可能枚举所有的权值情况，因此考虑随机若干组数据（略大于 $30000$ 组），就可以通过了。具体可以稍微卡一下时。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200100;
using ull = unsigned long long;
int n, k, a[2010][2010], f[2010][2010], col[N];
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> a[i][j];
    int res = 1e18;
    srand(time(0));
    while (1. * clock() / CLOCKS_PER_SEC < 2.95) {
        for (int i = 1; i <= n; ++i) col[i] = rand() & 1;
        for (int i = 0; i <= k; ++i)
            for (int j = 1; j <= n; ++j) f[i][j] = 1e18;
        f[0][1] = 0;
        for (int i = 0; i < k; ++i)
            for (int j = 1; j <= n; ++j)
                for (int p = 1; p <= n; ++p)
                    if (j != p && col[j] != col[p])
                        f[i + 1][p] = min(f[i + 1][p], f[i][j] + a[j][p]);
        res = min(res, f[k][1]);
    }
    cout << res << '\n';
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## solution

伟大之神 xcc_szy 一眼秒了这个题并传授给我了一点方法。

首先看到奇环，想到二分图，我们很自然的想到去给图黑白然后，然后如果存在一条黑白交替的路径那么这条路径必然是没有奇环的。

但是现在问题是，这个图可能不是二分图，咋办？

我们想一个事情，普通图的性质其实比二分图强得多，也就是说如果存在一种染色方式的最段路在二分图上可以，那么在普通图中这条最短路就可能不可以了，绝对不存在啥普通图的最短路要比二分图短啥的。

此时 xcc_szy 告诉我们可以随机化在这张图上黑白染色，每次跑答案用 DP 跑，每次都有错误概率 $\frac{511}{512}$，因为我可以多次染色，只需要有一次对的即可，那么我大概随机 $10000$ 多次，错误概率就是 $(\frac{511}{512})^{10000}$ 大概就是 $0.000000003$ 左右的概率，然后就足够通过了。

哦 DP 状态就是 $f_{i, j}$ 表示到了 $i$ 用了 $j$ 步的最短路的值，一条边能够转移当且今当两端点颜色不同，每次对答案取最小值。

## code

code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;
mt19937 rnd ( time ( 0 ) );

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 85;

int n, k, ans = 8e18;
int dis[N][N], a[N], f[N][N];

void Solve () {
  cin >> n >> k;
  for ( int i = 1; i <= n; i ++ ) {
    for ( int j = 1; j <= n; j ++ ) {
      cin >> dis[i][j];
    }
  }
  for ( int t = 1; t <= 11000; t ++ ) {
    for ( int i = 1; i <= n; i ++ ) {
      a[i] = rnd () % 2;
    }
    memset ( f, 0x3f, sizeof ( f ) );
    f[1][0] = 0;
    for ( int i = 0; i < k; i ++ ) {
      for ( int x = 1; x <= n; x ++ ) {
        for ( int v = 1; v <= n; v ++ ) {
          if ( x != v && a[x] != a[v] ) {
            f[v][i + 1] = min ( f[v][i + 1], f[x][i] + dis[x][v] );
          }
        }
      }
    }
    ans = min ( ans, f[1][k] );
  }
  cout << ans;
}

signed main () {
#ifdef judge
	freopen ( "Code.in", "r", stdin );
	freopen ( "Code.out", "w", stdout );
	freopen ( "Code.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

没有奇环，等价于可以给经过的点集 $S$ 中每个点上色，使得路径上相邻两点之间不同色。

可是我又不知道路径经过的点集是啥。

但是注意到由于是一个大小为 $K$ 的回路，所以 $|S| \leq 10$，那么我对整张图随机染色，是正确答案的染色方案的概率就是 $2^{-10}$，那么我们期望跑 $3 \times 2^{10}$ 次就可以跑出正确答案，每次设计状态 $dp_{u,i}$ 表示走完第 $i$ 条边到点 $u$ 的最短路，把每次跑出来的结果取 $\min$ 即可。

时间复杂度 $O(n^2 \times k \times 2^k)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int warma = 3000;
const int maxn = 84;
const int maxk = 14;
int col[maxn];
int w[maxn][maxn];
int dp[maxn][maxk];
int n,k;
int ans=1e18;
mt19937 rd(time(0));
void solve(){
    for(int i=1;i<=n;i++) col[i]=rd()%2;
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxk;j++) dp[i][j]=1e18;
    dp[1][0]=0;
    for(int s=1;s<=k;s++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i!=j&&col[i]!=col[j]) dp[i][s]=min(dp[i][s],dp[j][s-1]+w[j][i]); 
            }
        }
    }
    ans=min(ans,dp[1][k]);
}
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) cin>>w[i][j];
    for(int i=1;i<=warma;i++) solve();
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：木棉絮123 (赞：0)

## 题意简述

$n$ 个点的图，给你图的邻接矩阵，求从点 $1$ 出发经过 $k$ 条边回到点 $1$，且路径上没有奇环的最短距离。

$2 \le n \le 80, 2\le k \le 10$

## 题目分析

### SOL1

模拟赛时半个小时切了，看到没有奇环，马上就想到了[二分图](https://oi.wiki/graph/bi-graph/)的性质：二分图不存在长度为奇数的环。

考虑构造二分图，枚举每个点左右属性是 $2^{n}$ 的数量级的。然后有一个很 Tricky 的做法，直接随机黑白染色后跑分层图取最优解。

因为最长的序列有 $9$ 个点（除去首尾），显然枚举一次出现正确答案的概率是 $\Large\frac{1}{2^9}$ 的，枚举 $x$ 次出现正确答案的概率为 $\large (1-\frac{1}{2^9})^x$。跑个 $4096$ 次即可通过。复杂度是 $O(Tn^2k)$ 的，$T$ 为枚举次数。

[提交记录](https://codeforces.com/contest/1310/submission/278704501)。

### SOL2

赛后去 CF 上看了一下，发现居然有确定性算法，于是学了一下。

记路径走过的点的序列为 $n_1,n_2 \dots n_{k+1}$，其中首尾两个点为 $1$。考虑无奇环这个性质，发现可以转化为上述序列中**奇数位**中的数字与**偶数位**不重复。$k$ 很小，考虑先搜索奇数位上的数字，再考虑在偶数位上填尽可能大的数。

发现这样子会 T 飞掉，考虑优化。不难发现对于 $(n_{x-1},n_x,n_{x+1})$，如果前后两个数确定了，可以提前枚举中间这个点。注意不能重复的条件，要记录前六优的点，这样搜索时候确定偶数位就可以做到 $O(1)$ 了。

综上我们先 $O(n^3)$ 的枚举去预处理奇数点对的前 $6$ 优偶数点，然后再 $O(n^{\frac{k}{2}-1})$ 的搜索即可。算法是确定性的，~~赢麻了~~。

~~没写~~

## 一些延伸

注意到这个题目的两种做法十分类似[P8817 [CSP-S 2022] 假期计划](https://www.luogu.com.cn/problem/P8817)。~~为什么呢~~。

温馨提示：省略号应使用 $\dots, \cdots, \ldots$（`$\dots, \cdots, \ldots$`）。~~我以前一直用的……（`shift + 6`）。~~

---

## 作者：Hoks (赞：0)

## 前言
随机化，真就不会一点，看到小数据全想状压去了。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
发现棘手的就是不能存在奇环。

考虑一种一定能把奇环搞掉的方案。

不难想到二分图，其判定中就包含了**图中所有回路的长度均为偶数**。

如果有了一张二分图，我们直接枚举两端点和目前走过几条边跑个暴力 $O(n^2k)$ 的 dp 即可。

接着考虑来构造二分图。

因为构造二分图的方法是黑白染色，所以我们把所有可能的黑白染色的情况都试一遍，显然是能得出答案的。

这样的复杂度为 $O(2^nn^2k)$，不能接受。

观察到题目中的 $k$ 很小，而路径上经过的不同的点数不会超过 $k$。

多随机几次就能过了。

考虑下为什么概率很大。

假设答案是一条长度为 $x$ 的回路，那么其中只有 $x-1$ 个点。

我们能得到这个正确答案当且仅当随机到了这 $x-1$ 个点黑白相间的情况。

概率为 $\frac{1}{2^{x-2}}$。

其中 $x$ 卡满为 $10$，所以一次随机随机到的概率最小即为 $\frac{1}{256}$。

随机 $3000$ 次的话概率即为 $(\frac{255}{256})^{3000}\approx0.0000795509492572$，就这样我还挂了一发也是真牛。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=85,V=15,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,k,T=3000,ans=INF,a[N],d[N][N],f[V][N];mt19937 rnd(time(NULL));
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int u(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) u=(u<<1)+(u<<3)+(fc^48),fc=getchar();
        return u*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int u)
    {
        if(u<0) put('-'),u=-u;
        if(u>9) print(u/10);
        put(u%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
signed main()
{
    n=read(),k=read();for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) d[i][j]=read();
    while(T--)
    {
        for(int i=1;i<=n;i++) a[i]=rnd()&1;memset(f,0x3f,sizeof f);f[0][1]=0;
        for(int i=0;i<k;i++)
            for(int j=1;j<=n;j++)
                for(int u=1;u<=n;u++)
                    if(a[j]!=a[u]) f[i+1][u]=min(f[i+1][u],f[i][j]+d[j][u]);
        ans=min(ans,f[k][1]);
    }print(ans);
    genshin:;flush();return 0;
}
```

---

## 作者：_dijkstra_ (赞：0)

一道有趣的题目。

## 思路

众所周知，二分图、染色法没有矛盾，图中没有奇环，三者**是等价的**。

所以我们可以尝试把奇环的条件转化为**二分图**。

但是没有任何有关黑白点的问题，而且这个图也显然和二分图没有关系。这怎么办呢？

没有条件，我们可以自己创造！

**考虑随机化**。随便乱给每个点一个 $a_i \in \{0, 1\}$ 的权值。

按照二分图的定义，每条边应该只练两个集合内的点。所以只能连 $a_u \ne a_v$ 的边（$u \to v$）。

然后随便 DP 即可。设 $dp_{u, i}$ 表示当前是 $u$ 号点，走了 $i$ 步，最短距离。那么很容易转移：

$$dp_{v, i} = \min\limits_{a_u \ne a_v} dp_{u, i - 1} + e_{u, v}$$

初始化 $\infty$，$dp_{1, 0} = 0$。答案即为 $dp_{1, k}$。

---

此时你试一下样例，有时候过有时候不过。这很正常，因为是随机化。

所以多来几遍就行。你可以有两种选择，都是很保险的做法：

第一个方法，设置一个定值 $T$。跑 $T$ 次这个程序即可。但是这个 $T$ 需要足够大。

```cpp
int T = 1000;
while (T--) ans = min(ans, solve());
```
第二个方法，这题时间是 $3$ 秒。我们快超时了再输出答案，非常稳定！

```cpp
srand(time(NULL));
double st = clock();
while ((clock() - st) / CLOCKS_PER_SEC <= 2.8) ans = min(ans, solve());
```

然后这题就做完了。所以这真暴力。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
using namespace std;
const int N = 105, K = 15;
int n, k;
int e[N][N], a[K], dp[N][K];
int solve()
{
	for (int i = 1; i <= n; i++) a[i] = (rand() & 1); //随机
	memset(dp, 0x3f, sizeof dp), dp[1][0] = 0;
	for (int i = 1; i <= k; i++) //直接跑 DP
		for (int u = 1; u <= n; u++)
			for (int v = 1; v <= n; v++)
				if (a[u] != a[v])
					dp[v][i] = min(dp[v][i], dp[u][i - 1] + e[u][v]);
	return dp[1][k];	
}
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &e[i][j]);
	srand(time(NULL));
	double st = clock(); int ans = 2147483647;
	while ((clock() - st) / CLOCKS_PER_SEC <= 2.8) ans = min(ans, solve()); //也可以采用第一种方法
	cout << ans;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：ny_jerry2 (赞：0)

随机化是个好东西。

看到没有奇环，可以想到二分图。  
想到二分图，就可以想到染色法。

因此，$u \to v$ 当且仅当两个点颜色不同。  
但题目中一点关于颜色的信息都没有，怎么办？  

还有**随机化**！

随机给每一个点分配颜色即可。  
然后就是 dp：
$$
dp_{i,st}=\min_{col_i \ne col_j} {dp_{j,st-1} + dist_{i,j}}
$$

其中，$dp_{i,st}$ 为走了 $st$ 步后到了 $i$ 的最大距离，$col_i$ 表示颜色，$dist_{i,j}$ 表示距离。

初始化：$dp_{1,0}=0$。  
答案：$dp_{1,k}$。

当然随机化一次很可能出错，所以要多来几次。自测 $3000$ 次没有问题（当然也说不准）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int N=85;
int a[N][N],f[N][N]; 
int d[N];
int main(){
	srand(time(NULL));
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
		}
	}
	int T=3000;
	int ans=2e9;
	while(T--){
		for(int i=1;i<=n;i++){
			d[i]=rand()%2;
		}
		memset(f,0x3f,sizeof f);
		f[1][0]=0;
		for(int k=1;k<=m;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					if(d[i]!=d[j]){
						f[i][k]=min(f[i][k],f[j][k-1]+a[i][j]);
					}
				}
			}
		}
		ans=min(ans,f[1][m]);
	}
	cout<<ans;
}
```

---

