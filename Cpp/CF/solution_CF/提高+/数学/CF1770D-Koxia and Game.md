# Koxia and Game

## 题目描述

Koxia and Mahiru are playing a game with three arrays $ a $ , $ b $ , and $ c $ of length $ n $ . Each element of $ a $ , $ b $ and $ c $ is an integer between $ 1 $ and $ n $ inclusive.

The game consists of $ n $ rounds. In the $ i $ -th round, they perform the following moves:

- Let $ S $ be the multiset $ \{a_i, b_i, c_i\} $ .
- Koxia removes one element from the multiset $ S $ by her choice.
- Mahiru chooses one integer from the two remaining in the multiset $ S $ .

Let $ d_i $ be the integer Mahiru chose in the $ i $ -th round. If $ d $ is a permutation $ ^\dagger $ , Koxia wins. Otherwise, Mahiru wins.

Currently, only the arrays $ a $ and $ b $ have been chosen. As an avid supporter of Koxia, you want to choose an array $ c $ such that Koxia will win. Count the number of such $ c $ , modulo $ 998\,244\,353 $ .

Note that Koxia and Mahiru both play optimally.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, there are $ 6 $ possible arrays $ c $ that make Koxia win — $ [1, 2, 3] $ , $ [1, 3, 2] $ , $ [2, 2, 3] $ , $ [2, 3, 2] $ , $ [3, 2, 3] $ , $ [3, 3, 2] $ .

In the second test case, it can be proved that no array $ c $ makes Koxia win.

## 样例 #1

### 输入

```
2
3
1 2 2
1 3 3
5
3 3 1 3 4
4 5 2 5 5```

### 输出

```
6
0```

# 题解

## 作者：elbissoPtImaerD (赞：7)

[Link](https://codeforces.com/contest/1770/problem/D)
# 简述题意
给定 $n$ 和序列 $a_n,b_n$，还有一个序列 $c_n$

有两个人：小 K 和 小 M。

对于每个 $i\in[1,n]$，小 K 先从可重集 $\{a_i,b_i,c_i\}$ 中删去一个数，然后小 M 再从中选取一个数 $d_i$。

小 K 需要让 $d_n$ 是一个排列，小 M 则反之。

求能使 $d_n$ 是一个排列的序列 $c_n$ 个数。

$n \le 10^5$，答案对 $998244353$ 取模。

# 解题报告
首先小 M 不能有选择，即小 M 面临的两个数必须相同，不然小 M 会捣蛋，就做不到排列。  

那么 $\forall a_i\neq b_i, c_i \in \{a_i,b_i\}$，否则 $c_i\in[1,n]$。

但是这不完全能取到。  
考虑：最后是取出一个排列。

$a_i\neq b_i$ 时 $c_i$ 是一个或的限制。  
尝试连出无向边 $(a_i,b_i)$。  
发现序列 $a,b$，可以有 $c$ 当且仅当对于每个连通分量有 $|V|=|E|$，即点数等于边数。

首先由于每个空有且仅有一个选择，一个空也有且仅有一条边，所以充分性显然。

考虑必要性：当 $|V|=|E|$ 时，这个图要么是一颗基环树，要么是一颗树加一条自环。  
存在一种方案等价于每一条边都有且仅有一个顶点被选中。

先考虑自环，此时以自环的点为根，对于每个非自环的边取它深度更深的那个端点，对于自环取根，这样是合法的。  
再考虑基环树。环是显然的，环外的树可以仿照树 + 自环的构造。这样也是存在合法构造的。

综上，命题得证。

实现的话把图建出来，先判掉无解，然后考虑每个连通分量，如果有自环那么贡献是 $n$，否则是基环树那贡献是 $2$（环有两种取法）。乘起来即可。

复杂度 $\mathcal{O(\sum n)}$。

[$\color{green}{\checkmark}$](https://codeforces.com/contest/1770/submission/187510700)

---

## 作者：xiaruize (赞：4)

考虑在什么情况下Koxia可以必胜，发现以下几条特征：

- 对于每一次操作，Mahiru都有且只有一个数字可选，即Mahiru选什么完全确定
- 得出这样的结论
  - $a_i=b_i$ 时 , $c_i$ 为任意数都满足条件 , 此时最终选择结果一定为 $a_i$
  - $a_i\neq b_i$ 时， $c_i=a_i$ 或者 $c_i=b_i$ , 此时最终选择结果一定为 $c_i$

得出以上结论后，考虑将原来的数组转化为图，具体操作为在 $a_i$ 与 $b_i$ 之间建边

此时, 这个图不一定联通，考虑对于一个联通块，有如下这些结论:

- 当且仅当联通块是一个基环树(包括自环)时，这个联通块才能转化为可行的 $c_i$ 
- 如果任意联通块不是基环树，则答案为0 
- 按照环分两类: 自环/环
  - 对于自环，答案 $\times n$
  - 对于环, 答案 $\times 2$

具体可以使用并查集维护三个量：点数，边数，是否是自环，统计答案

 数据举例

```
3
1 2 2
1 3 3
```

对于样例一，建图如下

![](https://i.imgtg.com/2022/12/31/ESwIG.png)

显然, 点1是自环 2-3形成环

所以答案为 $3 \times 2 =6$


```cpp
/*
    Name:
    Author: xiaruize
    Date:
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define ALL(a) (a).begin(), (a).end()
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define pis pair<int, string>
#define sec second
#define fir first
#define sz(a) int((a).size())
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define repp(i, x, y) for (int i = x; i >= y; i--)
#define Yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define No cout << "No" << endl
#define NO cout << "NO" << endl
#define debug(x) cerr << #x << ": " << x << endl
#define double long double
const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
const int N = 2e5 + 10;

// bool st;
int t;
int n;
int a[N];
int b[N];
int fa[N];
int sz[N];//点数
int num[N];//边数
bool s[N];//是否自环
// bool en;

//并查集
int get(int x)
{
    if (x == fa[x])
        return x;
    return fa[x] = get(fa[x]);
}

void uni(int x, int y)
{
    int fx = get(x), fy = get(y);
    num[fx]++;
    if (x == y)
        s[fx] = true;
    if (fx == fy)
        return;
    sz[fx] += sz[fy];
    fa[fy] = fx;
    s[fx] |= s[fy];
    num[fx] += num[fy];
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        sz[i] = 1;
        num[i] = 0;
        s[i] = false;
    }
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
    {
        uni(a[i], b[i]);
    }
    int res = 1;
    for (int i = 1; i <= n; i++)
    {
        if (fa[i] != i)
            continue;
        if (sz[i] != num[i])//是否是基环树
        {
            cout << '0' << endl;
            return;
        }
        if (s[i])
            res = res * n % MOD;//自环
        else
            res = res * 2 % MOD;//非自环
    }
    cout << res << endl;
}

signed main()
{
    cin >> t;
    while (t--)
        solve();
    return 0;
}

```


---

## 作者：robinyqc (赞：3)

**结论**：$a_i, b_i, c_i$ 中至少有两个相等是 Koxia 必胜的必要条件。

**证明**：

1. 考虑游戏进行到完 $n - 1$ 局，此时 Koxia 不败，则 Mahiru 选择了一个 $1\sim n$ 的排列去掉一个数 $x$。第 $n$ 局时，若三个数都不相同，不管删掉哪个数，剩下两个中必有一个数 $\neq x$。因此，第 $n$ 局时，至少有两个数相等。
2. 对于前 $n - 1$ 局，可以看做构成一个 $1\sim n - 1$ 的排列，可以应用上一步的分析。归纳得证。

回到本题，就是若 $a_i = b_i$ 那么 $c_i$ 随便填，否则 $c_i\in \{a_i, b_i\}$。

每次可以选择两个中的一个的计数问题可以建图：对于每个 $i$，将点 $a_i$ 和点 $b_i$ 之间连一条边，得到一个基环树森林。每个点仅属于一条边，相当于给边定向，让每个点入度为 $1$。

对于非环边，它的指向唯一：朝向叶子。对于环边，若它的环是一个点的自环（$a_i = b_i$）那么有 $n$ 种填法；否则，有两种填法：顺时针填环和逆时针填环。

无解的情况是有重边。

用并查集或者直接遍历做一下就好了。

---

## 作者：Inui_Sana (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1770D)

## 解题思路：topo

首先，我们可以想想对方怎么让我们必败。因为最后要组成排列，所以对方可以一直让我们取不到一个数。

所以，我们需要每一个数都在某一个位置上“一定取得到”，即对于每一个 $x$，都存在一个 $i$，使 $a_i,b_i,c_i$ 中，至少有两个为 $x$。

那么要如何计算方案数呢？我们会发现，如果 $a_i\ne b_i$，那么对于这个 $i$，能“一定取得到”的只能是这两个数中的一个。于是我们可以建出一张图，对于每个 $i$，在 $a_i$ 和 $b_i$ 之间连一条边。每次确定一个 $c_i$ 就相当于是删掉点 $c_i$ 以及它的一条边。答案就是删的方案数。（无序）

怎样计算方案数呢？我们会发现，如果有解，建出的图一定是类似一个内向基环树森林。对于那些不在环上的点，可以用拓扑排序一个一个一个删掉，它们删的方式都是惟一的。至于在环上的点，如果是自环，结合原本的题意可知，这一位上放 $1$ 至 $n$ 的任意数都行，否则，一个环上的每一个点都和它“左边或右边”的边一起删掉，每个环都会使方案数 $\times 2$。

形式化地说，设有 $x$ 个自环，$y$ 个非自环的环，答案即为 $n^x\times 2^y$。

code：

```cpp
int n,m,cnt,d[N],in[N];
int l,r,q[N];
int tot,head[N];struct node{int to,nxt;}e[N<<1];
inline void add(int u,int v){e[++tot]={v,head[u]},head[u]=tot;}
void dfs(int u){
	in[u]=-1,cnt++;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(~in[v])dfs(v);
	}
}
void solve(){
	scanf("%d",&n);
	ll ans=1;mems(in,0),mems(head,0),tot=0,l=1,r=0;
	for(int i=1;i<=n;i++)scanf("%d",&d[i]);
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		if(d[i]==x)ans=ans*n%mod;
		add(x,d[i]),add(d[i],x);
		in[x]++,in[d[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(in[i]==1)q[++r]=i;
		if(!in[i]){puts("0");return;}
	}
	while(l<=r){
		int u=q[l++];in[u]=-1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(in[v]==-1)continue;
			in[v]--;
			if(!in[v]){puts("0");return;}
			if(in[v]==1)q[++r]=v;
		}
	}
	for(int i=1;i<=n;i++){
		if(~in[i]){
			cnt=0,dfs(i);
			if(cnt>1)ans=ans*2%mod;
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：rui_er (赞：3)

观察：对于每个 $x$，至少存在一个 $i$，使得 $a_i,b_i,c_i$ 中至少两个等于 $x$。

证明：假设 $x_0$ 不符合条件。Koxia 只需要删除所有等于 $x_0$ 的 $a_i,b_i,c_i$，便可以使得 Mahiru 无法取到 $x_0$，从而无法构成排列。$\square$

我们建无向图 $G=(V,E)$，其中 $V=\{i\mid 1\le i\le n\}$，$E=\{(a_i,b_i)\mid 1\le i\le n\}$。问题等价于给每条边定向，使得每个点入度均为 $1$。

易证，要有解，则 $G$ 的每个连通块必须是一棵基环树。其中，含自环的连通块对答案的贡献是 $n$ 倍（因为 $c_i$ 可以任意取），不含自环的连通块对答案的贡献是 $2$ 倍（环的方向）。

赛时代码可能略微写麻烦了，但是还是比较清晰的，放在这里供参考。

```cpp
// Problem: D. Koxia and Game
// Contest: Codeforces - Good Bye 2022: 2023 is NEAR
// URL: https://codeforces.com/contest/1770/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const ll N = 1e5+5, mod = 998244353;

ll T, n, a[N], b[N], buc[N], vis[N], cnt[N], sz[N];
vector<ll> e[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
bool dfs1(ll u, ll f) {
	for(ll v : e[u]) {
		if(v == f) continue;
		if(vis[v]) return 0;
		vis[v] = 1;
		if(!dfs1(v, u)) return 0;
	}
	return 1;
}
void dfs2(ll u, ll rt) {
	vis[u] = 1;
	++sz[rt];
	for(ll v : e[u]) {
		++cnt[rt];
		if(!vis[v]) dfs2(v, rt);
	}
}

int main() {
	for(scanf("%lld", &T); T; T--) {
		scanf("%lld", &n);
		rep(i, 1, n) scanf("%lld", &a[i]);
		rep(i, 1, n) scanf("%lld", &b[i]);
		ll ans = 1;
		rep(i, 1, n) {
			if(a[i] == b[i]) {
				++buc[a[i]];
				vis[a[i]] = 1;
			}
		}
		rep(i, 1, n) {
			if(buc[i] > 1) ans = 0;
			else if(buc[i] == 1) ans = ans * n % mod;
		}
		rep(i, 1, n) {
			if(a[i] != b[i]) {
				if(buc[a[i]] && buc[b[i]]) ans = 0;
				else {
					e[a[i]].push_back(b[i]);
					e[b[i]].push_back(a[i]);
				}
			}
		}
		rep(i, 1, n) if(buc[i]) if(!dfs1(i, 0)) ans = 0;
		rep(i, 1, n) {
			if(!vis[i]) {
				dfs2(i, i);
				// printf("%lld : %lld %lld\n", i, cnt[i], sz[i]);
				if(cnt[i] != sz[i] * 2) ans = 0;
				else ans = ans * 2 % mod;
			}
		}
		printf("%lld\n", ans);
		rep(i, 1, n) {
			a[i] = b[i] = buc[i] = vis[i] = cnt[i] = sz[i] = 0;
			e[i].clear();
		}
	}
	return 0;
}
```

---

## 作者：Missa (赞：2)

47min 时过 C 降智 50min 做不出 D。果然晚上容易降智。

题意不想复述，好长。

[link to CF](https://codeforces.com/problemset/problem/1770/D) | [link to Luogu](https://www.luogu.com.cn/problem/CF1770D)

合理猜测留给后手的两个数字必须相等。证明为若不相等，则后手可以把最终的数列换掉一个数字，一定能打破排列的性质。

因此若 $a_i=b_i$，则 $c_i$ 可以随便取；否则 $c_i=a_i$ 或 $c_i=b_i$。则方案数等于在只看 $a_i \neq b_i$ 的选择中取出一个排列（预先取出 $a_i=b_i$ 的数字）的方案数，再乘上 $n^{\text{自由元的个数}}$。

注意到这个规则挺弱，可以交换任意两条的顺序，也可以交换 $a_i$ 和 $b_i$，可以建个无向图来显示这个性质。

然后赛场降智开始写大分讨。调不出来，存在解判不存在。

考虑观察图的性质，这是带自环基环树森林。单拎一个基环树出来看看，则需要把每条边（除自环）定向让每个点入度恰为 $1$。

对于非环上的边，定向方向是唯一的，即远离环的方向；而环上的边有两种定向方法，除非是自环。

至此，逐一看每个连通块，若非基环树则无解；否则，判断是否有自环，无自环则对答案贡献 $2$，否则贡献 $n$。

```cpp
#include <cstdio>
#include <vector>
using namespace std;
const int M = 1e5 + 5, mod = 998244353;
int fa[M], n, sm[M], ans, siz[M], ec[M];
void init(int n) {
    for(int i = 1; i <= n; i++)
        fa[i] = i, sm[i] = 0, siz[i] = 1, ec[i] = 0;
}
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
void merge(int u, int v) {
    u = find(u); v = find(v);
    if(u != v) fa[u] = v, sm[v] += sm[u], siz[v] += siz[u];
}
int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<int> a(n), b(n);
        init(n);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        for(int i = 0; i < n; i++) scanf("%d", &b[i]);
        int cnt = 0, cnt2 = 0; 
        for(int i = 0; i < n; i++) {
            if(a[i] == b[i]) ++cnt, sm[a[i]] = 1;
        }
        for(int i = 0; i < n; i++) merge(a[i], b[i]);
        for(int i = 0; i < n; i++) {
            ++ec[find(a[i])];
        } 
        int ans = 1;
        for(int i = 1; i <= n; i++) {
            if(fa[i] != i) continue;
            if(ec[i] != siz[i]) ans = 0;
            else if(sm[i] > 0) ans = 1ll * ans * n % mod;
            else ans = 1ll * ans * 2 % mod;
        }
        printf("%d\n", ans);
    }
}
```

---

## 作者：Ryder00 (赞：1)

题意清晰，不再阐述。

### 思路
分析 $a$ 与 $b$ 数组，得到下列两种情况：
- $a_i=b_i$，则第 $i$ 位上的数必须与 $a_i$ 相等。

证明：假设除了第 $i$ 位以外其他位都已经选择好，若此时选择的数不与 $a_i$ 相等，则Mahiru一定会选择一个与其余某一位矛盾的数。

- $a_i \ne b_i$，则 $c_i$ 必须与两者其中之一相等。

证明同理。

这种二选一问题我们容易想到连边。将下标 $i$ 与 $n+a_i$ 和 $n+b_i$ 分别连一条无向边，建出类似圆方树的图。称小于等于 $n$ 的点为“圆”点，其余为“方”点。可以判断无解情况为：存在某一连通块上的“圆”点和“方”点数量不相等。

证明：当两者不相等时，无论如何都无法完成下标与值的一一配对，总会有一个值未被选择或一个位置无法选择值。

对于情况 $1$，易得 $c_i$ 的取值有 $n$ 种。考虑如何解决情况 $2$。

由上面无解情况的推导，我们能证得：一个连通块内最多有一个环。

证明：对于一个已经有环的圆方点数量平衡图，若在任意一个点上再拓展出一个环，增加的异类点数一定会比同类点数多 $1$。故当环数大于 $1$ 时，会变为无解。

易得环上点的取值方案为 $2$ 种。最后把所有的取值方案乘起来即可。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define _ 0
const int N=2e5+10,mod=998244353,MOD=1e9+123,inf=1e18;
int T=1,n,a[N],b[N],val[N],vis[N],cnt1,cnt2,pd;
vector<int> e[N];
void dfs(int x,int lst){
    vis[x]=1;
    if(x<=n) cnt1++;
    else cnt2++;
    for(int y:e[x]){
        if(y==lst) continue;
        if(vis[y]){
            pd=1;
            continue;
        }
        dfs(y,x);
    }
}
void mem(){
    for(int i=1;i<=2*n;i++){
        vis[i]=val[i]=0;
        e[i].clear();
    }
    cnt1=cnt2=pd=0;
}
void solve(){
    cin>>n;
    mem();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    int res=1;
    for(int i=1;i<=n;i++){
        if(a[i]==b[i]) {
            res=(res*n)%mod;
            e[i].pb(n+a[i]),e[n+a[i]].pb(i);
            continue;
        }
        e[i].pb(n+a[i]),e[i].pb(n+b[i]);
        e[n+a[i]].pb(i),e[n+b[i]].pb(i);
    }
    for(int i=1;i<=n;i++){
        cnt1=cnt2=pd=0;
        if(!vis[i]) dfs(i,0);
        if(cnt1!=cnt2){
            cout<<0<<endl;
            return ;
        }
        if(pd) res=(res*2)%mod;
    }
    cout<<res<<endl;
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        solve();
    }
    // cerr<<endl<<"Time: "<<1.0*clock()/CLOCKS_PER_SEC<<" s";
    return ~~(0^_^0);
}
```

---

## 作者：LittleChara (赞：0)

注意到 $a_i=b_i$ 时 $c_i$ 无论取什么数都可以使后手必须取 $a_i$，而 $a_i\ne b_i$ 时 $c_i\in \{a_i,b_i\}$。因为只有这样才能限制后手只能取 $a_i$ 或 $b_i$。

考虑建图，连接 $(a_i,b_i)$。

如果图中有树或者孤立点的话答案是 0，证明：

> 我们连边表示该边映射的 $c_i$ 可以选择左右两个端点的其中之一，若图中有树相当于当前极大联通子图中映射的 $k$ 个数 会被 $k-1$ 个 $c_i$ 所选，即有一个数字不会被选择。孤立点情况即为树的特殊情况。

因为边数只有 $n$ 条，所以图中只允许有自环或基环树。

自环的贡献是 $n$ 的，很显然。

基环树的贡献是 $2$，因为一个点数大于 $1$ 的环中的每一条边可以有两种选择，而一个选择会影响环上的所有点，所以贡献是 $2$。

据此计算即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long
#define db double
#define ld long double

#define M 100005
#define N 2005
#define mod 998244353
#define base 13331
#define inf 1e9
#define dinf 1e15
#define linf 1e18+7
#define eps 1e-15
#define delta 0.997

int T;
int n;
int a[M],b[M];
bool d[M];

vector<int> g[M];
#define add(u,v) g[u].push_back(v)

int sum,cnt;
bool sp;
bool vis[M];

void dfs(int u){
	vis[u]=1;
	sum+=(int)g[u].size();
	++cnt;
	sp|=d[u];
	for(auto v:g[u]){
		if(vis[v]) continue;
		dfs(v);
	}
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		ll ans=1; bool ok=1;
		for(int i=1;i<=n;++i) g[i].clear(),vis[i]=d[i]=0;
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		for(int i=1;i<=n;++i) scanf("%d",&b[i]),d[a[i]]|=(a[i]==b[i]);
		for(int i=1;i<=n;++i) add(a[i],b[i]),add(b[i],a[i]);
		for(int i=1;i<=n;++i){
			sum=cnt=sp=0;
			if(!vis[i]){
				dfs(i);
				if(sum==(cnt<<1)){
					if(sp) ans=ans*n%mod;
					else ans=ans*2%mod;
				}
				else ok=0;
			}
		}
		if(!ok) printf("0\n");
		else printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：EBeason (赞：0)

# 思路
首先先推一些性质。  
如果 `a[i]==b[i]` 那么 `c[i]` 可以随意取。  
如果 `a[i]!=b[i]` 那么 `c[i]` 只能二选一。  
由于我们要组成一个排列，那么所有数都必须要出现，我们可以把这个题转换成一个图论题，把 `(a[i],b[i])` 当成一条边处理 。
这个图可以分成几个联通块，每个联通块都必须点数等于边数，换句话就是说要有一个环。 
自环对答案贡献是N，其他环对答案贡献是 $2$ 。  
这个联通块处理可以用并查集来处理。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
const int MaxN=1e6+100;
const int INF=1e9;
int T,N,M,a[MaxN],b[MaxN],P=998244353,fa[MaxN],vis[MaxN];
int sum1[MaxN],sum2[MaxN],pd[MaxN];
template<class T>
inline void qread(T &sum)
{
	sum=0;int boo=1;
	char x=getchar();
	while(x<'0'||x>'9'){if(x=='-')boo=-1;x=getchar();}
	while(x>='0'&&x<='9'){sum=(sum<<1)+(sum<<3)+x-'0';x=getchar();}
	sum*=boo;
}
template<class T>
void qput(T x)
{
	if(x<0) {x=-x;putchar('-');}
	if(x>9) qput(x/10);
	putchar(x%10+48);
}
int find1(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find1(fa[x]);
}
inline void hebin(int x,int y)
{
	int fx=find1(x),fy=find1(y);
	sum1[fx]+=sum1[fy];
	sum2[fx]+=sum2[fy];
	pd[fx]|=pd[fy];
	fa[fy]=fx;
}
inline void Solve()
{
	qread(N);
	for(int i=1;i<=N;i++) qread(a[i]);
	for(int i=1;i<=N;i++) qread(b[i]);
	int ans=1;
	for(int i=1;i<=N;i++)
	{
		fa[i]=i;
		vis[i]=0;
		sum1[i]=1;
		sum2[i]=0;
		pd[i]=0;
	}
	for(int i=1;i<=N;i++)
	{
		int fx=find1(a[i]),fy=find1(b[i]);
		if(fx!=fy) hebin(fx,fy);
		sum2[find1(fx)]++;
		if(a[i]==b[i]) pd[find1(fx)]=1;
	}
	for(int i=1;i<=N;i++)
	{
		if(vis[find1(i)]) continue;
		if(sum1[find1(i)]!=sum2[find1(i)]) ans=0;
		else
		{
			if(pd[find1(i)])
			{
				ans*=N;
			}
			else
			ans*=2;
			ans%=P;
		}
		vis[find1(i)]=1;
	}
	qput(ans);putchar('\n');
}
signed main()
{
	qread(T);
	while(T--) Solve();
}
```


---

## 作者：luogubot (赞：0)

假设有值域为 $[1,n]$ 的三个序列 $a_{1\cdots n},b_{1\cdots n},c_{1\cdots n}$，两人博弈，在第 $1\leq i\leq n$ 轮中，先手从可重集 $\{a_i,b_i,c_i\}$ 中任意移除一个元素，后手在剩余两个元素中任取一个，记为 $d_i$。最终如果 $d$ 是一个排列，则后手胜。给出 $a,b$，求有多少个 $c$ 可以让后手必胜。

$n\leq 10^5$。

刚开始转化歪了，从先手移除之后的可重集怎样合法入手，发现先手移除后若剩下 $X_i,Y_i$，则连边形成的图要是基环森林后手才能赢。但是对于连通性是几乎无法刻画的，于是重新开始思考，如果给出 $a,b,c$，先手的最优策略是什么？因为“$d$ 是排列”这个限制比较紧，所以它的反面“存在一个元素不出现在 $d$ 中”是很松的，这导出了先手的一个策略：选定一个元素 $x$，在包含 $x$ 的集合中一定删除 $x$，以求最终其不出现在 $d$ 中。那么，如果对于这个 $x$，它在某个集合中出现了两次，那是无法阻止它进入 $d$ 的。

至此得到一个性质：若每个 $x$ 都在某一个集合中出现了至少两次，那么后手必胜；否则如果存在某个 $x$ 在每个集合中都只出现至多一次，则先手可以让 $x$ 不在 $d$ 中。也就是得到了后手必胜的充要条件：每个 $x$ 都在某一个集合中出现了至少两次。由于每个集合的大小是 3，$x$ 和集合的个数均为 $n$ 个，于是每个集合如果初始是 $\{x,y\}$（$x\neq y$），则可以选择添加一个 $x$ 或添加一个 $y$，即连边 $(x,y)$，要求其是基环森林才能合法，且环上有两种走法，于是对答案的贡献是 $\times 2$；特殊地，如果出现了自环，则对应集合任意添加都是可以的，对答案的贡献是 $\times n$，于是只需要并查集维护基环森林结构。$O(n\log n)$。

---

