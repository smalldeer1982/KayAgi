# Two Step Sort

## 题目描述

有 $N$ 个盒子和 $N$ 个球，编号为 1 到 $N$。最初，第 $i$ 个盒子里装着编号为 $P_i$ 的球。每个盒子只能装一个球，开始时所有盒子都是关闭的，可以打开盒子。

接下来将进行两次球的移动操作，每次操作遵循以下步骤：

1. 选择若干盒子打开，每个盒子都有固定的打开成本。
2. 在打开的盒子之间随意移动球，操作完成时，每个盒子必须有一个球。
3. 将所有打开的盒子再次关闭。

第一次操作时，打开第 $i$ 个盒子的成本为 $A_i$；第二次操作时，打开第 $i$ 个盒子的成本为 $B_i$。经过两次操作后，要求第 $i$ 个盒子里装有第 $i$ 个球。请计算达到目标的最低总成本。

## 说明/提示

- $1 \leq N \leq 10^5$
- $1 \leq P_i \leq N$
- 当 $i \neq j$ 时，$P_i \neq P_j$
- $1 \leq A_i \leq 10^9$
- $1 \leq B_i \leq 10^9$
- 所有输入均为整数

### 示例解释

在第一个移动事件中，打开盒子 2 和 4，把球 1 放入盒子 2，把球 4 放入盒子 4，这样的操作成本是 8。在第二次移动事件中，打开盒子 1、2、3 和 5，把球 1、2、3 和 5 放入相应的盒子中，操作成本为 20。整个过程的总成本为 28，这是满足条件的最小成本。

有时候，初始状态已经满足要求，意味着不需要进行任何移动。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2 4 5 1 3
11 5 3 3 8
4 6 7 9 3```

### 输出

```
28```

## 样例 #2

### 输入

```
1
1
1000000000
1000000000```

### 输出

```
0```

# 题解

## 作者：ran_qwq (赞：5)

首先如果建 $i$ 连向 $p_i$ 的图，会形成若干个环。我们的目标是把所有环变成自环。

随便手玩一下会发现，如果你第一步同时选了 $i$ 和 $p_i$，第二步就不用选 $p_i$，否则就要选 $p_i$。这是因为交换了 $(i,p_i)$，就会变成 $p_i\rightarrow p_i,i\rightarrow p_{p_i}$，$p_i$ 成自环。如果是第一步取连续多个同理。

每个环是独立的，看成序列直接 dp。$dp_{i,0/1,0/1}$ 表示前 $i$ 个数，当前不选/选，上一个不选/选的最小代价。转移显然。

但这是环不是序列，可以直接枚举第一个和最后一个选不选，硬拆成序列。

注意初始化不能用 memset，以及特判一下环长为 $1$ 的情况。

```cpp
int n,p[N],q[N],a[N],b[N];
namespace sol2 {
	int m,vs[N],ps[N]; ll as,mn,f[N][2][2];
	void sol(int x,int y) {
		for(int i=1;i<=m;i++) mst(f[i],0x3f);
		f[1][x][y]=(ll)(x?a[ps[1]]:0)+(y?a[ps[m]]:0)+(!x||!y?b[ps[m]]:0);
		for(int i=2;i<m;i++) for(int p=0;p<2;p++) for(int q=0;q<2;q++) for(int r=0;r<2;r++)
			cminll(f[i][p][q],f[i-1][q][r]+(p?a[ps[i]]:0)+(!p||!q?b[ps[i-1]]:0));
		for(int p=0;p<2;p++) for(int q=0;q<2;q++) cminll(mn,f[m-1][p][q]+(!p||!y?b[ps[m-1]]:0));
	}
	void sol() {
		for(int i=1;i<=n;i++) if(!vs[i]) {
			ps[m=1]=i,vs[i]=1,mn=INFll; for(int u=q[i];u!=i;u=q[u]) ps[++m]=u,vs[u]=1;
			if(m==1) continue; for(int x=0;x<2;x++) for(int y=0;y<2;y++) sol(x,y); as+=mn;
		}
		wrll(as,"\n");
	}
}
void QwQ() {
	n=rd();
	for(int i=1;i<=n;i++) q[p[i]=rd()]=i;
	for(int i=1;i<=n;i++) a[i]=rd();
	for(int i=1;i<=n;i++) b[i]=rd();
	return sol2::sol();
}
```

---

## 作者：HYXLE (赞：2)

## [AT_kupc2021_ Two Step Sort](https://www.luogu.com.cn/problem/AT_kupc2021_g)

首先不难想到将 $i$ 和 $p_i$ 连边，这样就形成了几个环，又不难发现不同环之间的数是不会在第一次操作中交换的，因为一定不优。

所以说每一个环的答案是独立的，不妨对每一个环进行 dp 。

考虑挖掘一些性质。

记 $pre_i$ 表示点 $i$ 在环上的前一个点的编号，$aft_i$ 表示点 $i$ 在环上的后一个点的编号。

不难发现若第一次要对点 $i$ 进行操作，则一定不会将其与除了 $pre_i$ 与 $aft_i$ 的点进行交换，易证这是不优的。

所以可以发现每种一操作的集合在环上操作的都是一段连续的点，所以不难写出一个 dp：设 $f_{i,0/1}$
表示当前是第 $i$ 个点，其选或不选为第一次操作的集合。

转移是简单的，但是要注意：这是在环上的 dp，所以考虑断环为链，暴力枚举链上的第一个点和最后一个点选不选，然后强行转为链上的 dp 即可。

复杂度是 $O(n)$ 的。

## code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register
using namespace std;
const int N=1e5+5;const ll inf=1e18;
ll n,a[N],b[N],fa[N],to[N];ll f[N][2],sum[N],res;
bool vis[N];
vector<int> v;
inline ll calc2(int l,int r){return sum[r]-sum[l-1];}
inline void solve(int u){
	v.clear();
	while(!vis[u]){v.emplace_back(u);vis[u]=1;u=fa[u];}
	int len=v.size();
	if(len==1)return;
	ll nw=inf;
	for(R int i=0;i<len;++i){
		sum[i+1]=sum[i]+a[to[v[i]]];
	}
	for(R int i=1;i<=len;++i)f[i][0]=f[i][1]=inf;
	f[1][0]=b[to[v[0]]];f[1][1]=inf;
	for(R int i=1;i<len;++i){
		f[i+1][0]=min(f[i][0],f[i][1])+b[to[v[i]]];
		f[i+1][1]=calc2(1,i+1)+b[to[v[0]]];
		f[i+1][1]=min({f[i+1][1],f[i][0]+b[to[v[i]]]+a[to[v[i]]],f[i][1]+a[to[v[i]]]});
	}
	nw=min(f[len][1],f[len][0]);
	for(R int i=1;i<=len;++i)f[i][0]=f[i][1]=inf;
	f[1][0]=inf;f[1][1]=a[to[v[0]]];
	for(R int i=1;i<len;++i){
		f[i+1][0]=min(f[i][0],f[i][1])+b[to[v[i]]];
		f[i+1][1]=calc2(1,i+1)+b[to[v[0]]];
		f[i+1][1]=min({f[i+1][1],f[i][0]+b[to[v[i]]]+a[to[v[i]]],f[i][1]+a[to[v[i]]]});
	}
	nw=min({nw,f[len][1],f[len][0]+b[to[v[0]]]});
	res+=nw;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n;
	for(R int i=1;i<=n;++i)cin>>fa[i],to[fa[i]]=i;
	for(R int i=1;i<=n;++i)cin>>a[i];
	for(R int i=1;i<=n;++i)cin>>b[i];
	for(R int i=1;i<=n;++i)if(!vis[i])solve(i);
	cout<<res<<'\n';
	return 0;
}
```

---

## 作者：VitrelosTia (赞：1)

联测放的题，被典中典 trick 干爆。

毫无头绪的交换问题，让人想到 dp，但是这么多环你怎么转移？直接把环给搞出来，按顺序变成序列就可以进行 dp 了！设 $f_{i,0/1}$ 表示考虑完前 $i$ 个，第 $i$ 个是否选择在第一次放到位置上。枚举第一个要不要第一次放，进行转移：

- $f_{i,0}=\min(f_{i-1,0}, f_{i-1,1}+a_i)+b_i$

含义是如果上一个要来，那你这次也要选，不然从别的地方再来肯定亏，花费 $a_i$。因为你第一次没放到位置上，所以就不得不在第二次放回去，花费 $b_i$。
  
- $f_{i,1}=\min(f_{i-1,0}, f_{i-1,1})+a_i$

含义是上一个不管怎么样都可以放过来，直接加上花费 $a_i$ 即可。

细节是如果第一个第一次不选，最后一个第一次选，要加上 $a_1$。然后你会发现如果你按照直观的想法连 $i \to p_i$ 的边就寄了，因为你这样在交换 $i-1$ 和 $i$ 的时候会把 $i$ 归位，所以你要连 $p_i \to i$ 才能满足你 dp 的意图，当然你倒着 dp 也行。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define test cerr << "test\n"
#define print(x) cout << #x << " = " << x << endl
#define file(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

const int N = 1e5 + 5, inf = 1e18;
int n, p[N], a[N], b[N];
vector <int> g[N];

bool vis[N]; int c[N], tot;
void dfs(int u) { c[++tot] = u; vis[u] = true; for (int v : g[u]) if (!vis[v]) dfs(v); }
int f[N][2], ans;
void dp() {
    for (int i = 2; i <= tot; i++) {
        f[i][0] = min(f[i - 1][0], f[i - 1][1] + a[c[i]]) + b[c[i]];
        f[i][1] = min(f[i - 1][0], f[i - 1][1]) + a[c[i]];
    }
}
int solve() {
    if (tot == 1) return 0; int now = inf;
    f[1][0] = inf; f[1][1] = a[c[1]]; dp();
    now = min({now, f[tot][0], f[tot][1]});
    f[1][0] = b[c[1]]; f[1][1] = inf; dp();
    now = min({now, f[tot][0], f[tot][1] + a[c[1]]});
    return now;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i], g[p[i]].push_back(i);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) if (!vis[i])
        tot = 0, dfs(i), ans += solve();
    cout << ans;
    return 0;
}

```

---

## 作者：mskqwq (赞：0)

先把所有 $p_i=i$ 的位置去掉，设第一次操作的位置集合为 $S$，$P_S=\{p_x\vert x\in S\}$，那么 $S$ 的答案为 $\sum_{x \in S} A_x+B_x[x \notin P_S] + \sum_{x \notin S} B_x$。

接着对着这个式子优化，显然可以把每个置换环分开考虑。考虑环上连续一段的在 $S$ 中的点 $a_1 ,a_2 \dots a_k$，其中 $a_i$ 向 $a_{i+1}$ 连边。那么这一段的贡献为 $\sum_{i=1}^k A_{a_i} + B_{a_1}$，因为没有连向 $a_1$ 且在 $S$ 中的点，所以要加上 $B_{a_1}$。然后在环上 dp，设 $f_{i,0/1}$ 表示考虑了前 $i$ 个点，第 $i$ 个点是否在 $S$ 中的最小代价，分别钦定第一个点在不在 $S$ 中然后跑两遍就行。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define pc(x) __builtin_popcount(x)
#define mems(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char c=getchar();int f=1,x=0;
    for(;c<48||c>57;c=getchar())if(c=='-') f=-1;
    for(;47<c&&c<58;c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x*f;
}
const int N=1e5+10,mod=998244353;
int n,a[N],b[N],p[N],vis[N];ll ans,f[N][2];
void misaka(){
    n=read();
    rep(i,1,n) p[i]=read();
    rep(i,1,n) a[i]=read();
    rep(i,1,n) b[i]=read();
    rep(i,1,n)if(!vis[i]&&p[i]!=i){
        vector<int> v{0,i};
        for(int x=p[i];x^i;x=p[x]) v.eb(x);
        int k=v.size()-1;ll sum=0;
        rep(j,1,k) sum+=a[v[j]],vis[v[j]]=1;
        f[1][0]=1e18,f[1][1]=b[v[1]];
        rep(i,2,k){
            f[i][0]=min(f[i-1][0]+a[v[i]],f[i-1][1]+a[v[i]]+b[v[i]]);
            f[i][1]=min(f[i-1][0],f[i-1][1])+b[v[i]];
        }
        sum=min(sum,min(f[k][0],f[k][1]));
        f[1][0]=a[v[1]],f[1][1]=1e18;
        rep(i,2,k){
            f[i][0]=min(f[i-1][0]+a[v[i]],f[i-1][1]+a[v[i]]+b[v[i]]);
            f[i][1]=min(f[i-1][0],f[i-1][1])+b[v[i]];
        }
        sum=min(sum,min(f[k][0],f[k][1]+b[v[1]]));
        ans+=sum;
    }
    printf("%lld",ans);
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    // FIO("A");
    int T=1;
    while(T--) misaka();
    return 0;
}

```

---

## 作者：zdd6310 (赞：0)

# Two Step Sort

模拟赛 T1。

---

对于每一次操作，如果能让 $p_i=i$ 的话，肯定会这样操作。

定义排列 $V$，$V_{p_i}=i$。

连有向边 $(i,V_i)$，形成若干个环。

一次操作，在环上选取若干个段，每一个段除了最后一个位置，其他位置都归位了。

剩下没有选上的位置和段的最后一个位置，只能用第二次操作消除了。

对于 $i$：

- 如果第一次在段中，贡献 $a_i$。
- 如果第一次在段尾，贡献 $a_i+b_i$。
- 如果第一次不选，贡献 $b_i$。

然后可以 `dp` 了。定义 $dp_{i,j}$ 表示考虑第 $i$ 个位置，最后一个位置状态为 $j$ 的最小代价。

$j\in\{1,2,3\}$，分别表示段中，段尾，不选。

然后枚举段首的状态，分别 dp 就可以了。复杂度 $O(n)$。

---

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
const int inf=1e18;
int n,p[MAXN],a[MAXN],b[MAXN],V[MAXN],vis[MAXN];
int dp[MAXN][3];
signed main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i],V[p[i]]=i;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	int ans=0;
	for(int i=1;i<=n;i++)if(V[i]!=i&&!vis[i]){
		vector<int>vec;vec.push_back(i);
		int now=V[i];while(now!=i)vec.push_back(now),now=V[now];
		int all=0;
		for(int j:vec){
			all+=a[j];vis[j]=1;
		}
		int res=all;
		dp[0][0]=a[vec[0]],dp[0][1]=inf,dp[0][2]=inf;
		for(int i=1;i<vec.size();i++){
			dp[i][0]=min(dp[i-1][0],dp[i-1][2])+a[vec[i]];
			dp[i][1]=dp[i-1][0]+a[vec[i]]+b[vec[i]];
			dp[i][2]=min(dp[i-1][1],dp[i-1][2])+b[vec[i]];
		}
		int lst=vec.size()-1;
		res=min(res,min(dp[lst][0],dp[lst][2]));

		dp[0][0]=inf,dp[0][1]=a[vec[0]]+b[vec[0]],dp[0][2]=inf;
		for(int i=1;i<vec.size();i++){
			dp[i][0]=min(dp[i-1][0],dp[i-1][2])+a[vec[i]];
			dp[i][1]=dp[i-1][0]+a[vec[i]]+b[vec[i]];
			dp[i][2]=min(dp[i-1][1],dp[i-1][2])+b[vec[i]];
		}
		res=min(res,dp[lst][0]);


		dp[0][0]=inf,dp[0][1]=inf,dp[0][2]=b[vec[0]];
		for(int i=1;i<vec.size();i++){
			dp[i][0]=min(dp[i-1][0],dp[i-1][2])+a[vec[i]];
			dp[i][1]=dp[i-1][0]+a[vec[i]]+b[vec[i]];
			dp[i][2]=min(dp[i-1][1],dp[i-1][2])+b[vec[i]];
		}
		res=min(res,min(dp[lst][1],dp[lst][2]));

		ans+=res;
	}
	cout<<ans<<"\n";
}
```

---

