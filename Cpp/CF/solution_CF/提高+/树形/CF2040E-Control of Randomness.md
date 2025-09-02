# Control of Randomness

## 题目描述

给定一棵树，树上有 $ n $ 个顶点。

我们在某个顶点 $ v \ne 1 $ 放置一个机器人，最初拥有 $ p $ 枚硬币。以下是机器人的移动规则：

- 当 $ i $ 为奇数时，机器人会向顶点 $ 1 $ 的方向移动到相邻的节点。
- 当 $ i $ 为偶数时，如果你愿意支付一枚硬币并且还有剩余的硬币，则机器人会向顶点 $ 1 $ 的方向移动到相邻的节点；否则，机器人将随机选择一个相邻的节点移动。

当机器人到达顶点 $ 1 $ 时，过程终止。记 $ f(v, p) $ 为通过最佳策略使用硬币时，使得上述过程的期望步数最小值。

你的任务是解决 $ q $ 个查询。每个查询包含一对 $(v_i, p_i)$，你需要计算 $ f(v_i, p_i) $ 模 $ 998\,244\,353 $ 的值。

具体来说，令 $ M = 998\,244\,353 $。结果可以表示为一个不可约分数 $ \frac{p}{q} $，其中 $ p $ 和 $ q $ 是整数且 $ q \not\equiv 0 \pmod{M} $。你需要输出 $ p \cdot q^{-1} \bmod M $。换句话说，输出满足 $ 0 \le x < M $ 且 $ x \cdot q \equiv p \pmod{M} $ 的整数 $ x $。

## 说明/提示

在第一个测试用例中，树的结构如下：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040E/6e37a094615504d3867ace023f49408cee6e1144.png)

第一个查询中，期望值为 $ 1 $，因为机器人从顶点 $ 2 $ 出发，一步就到达了顶点 $ 1 $，过程结束。

第二个查询中的期望步数计算如下（$ x $ 为步数）：

- $ P(x < 2) = 0 $，因为距离顶点 $ 1 $ 是 $ 2 $，机器人无法在更少的步数内到达。
- $ P(x = 2) = \frac{1}{3} $，因为只有一种步骤序列使 $ x = 2 $。即 $ 3 \rightarrow_{1} 2 \rightarrow_{0.33} 1 $，概率为 $ 1 \cdot \frac{1}{3} $。
- $ P(x \bmod 2 = 1) = 0 $，因为机器人只能通过偶数步数到达顶点 $ 1 $。
- $ P(x = 4) = \frac{2}{9} $：可能路径为 $ 3 \rightarrow_{1} 2 \rightarrow_{0.67} [3, 4] \rightarrow_{1} 2 \rightarrow_{0.33} 1 $。
- $ P(x = 6) = \frac{4}{27} $：可能路径为 $ 3 \rightarrow_{1} 2 \rightarrow_{0.67} [3, 4] \rightarrow_{1} 2 \rightarrow_{0.67} [3, 4] \rightarrow_{1} 2 \rightarrow_{0.33} 1 $。
- 一般情况下，$ P(x = i \cdot 2) = \frac{2^{i - 1}}{3^i} $。

因此，$ f(v, p) = \sum_{i=1}^{\infty}{i \cdot 2 \cdot \frac{2^{i - 1}}{3^i}} = 6 $。

第二个测试用例中，树的结构如下：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2040E/817926230fce12f251ecac195b4fa36da450f14f.png)


 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
4 4
1 2
2 3
2 4
2 0
3 0
4 0
3 1
12 10
1 2
2 3
2 4
1 5
5 6
6 7
6 8
6 9
8 10
10 11
10 12
6 0
9 0
10 0
11 0
3 1
7 1
10 1
12 1
12 2
11 12```

### 输出

```
1
6
6
2
4
9
8
15
2
3
6
9
5
5```

# 题解

## 作者：Register_flicker (赞：6)

### 题目描述

给定一棵 $n$ 个节点的树，在 $v$ 号节点有一个人，他有 $p$ 个硬币。考虑以下过程，在第 $i$ 步：

* 如果 $i$ 为奇数，向他所在节点的父亲节点走一步。
* 如果 $i$ 为偶数，他有以下选择：
  * 支付一个硬币，向他所在节点的父亲节点走一步。
  * 不支付硬币，向随机相邻节点走一步。

$q$ 次询问，每次询问给定 $v,p$ ，求最优情况下走到 $1$ 节点的步数期望值。

### 解题思路

考虑把每 $2$ 步看成一组。

每组中的第一步一定会向父亲节点走，第二步可能会向父亲节点走也可能向儿子节点走。

注意到每组操作结束后他要么走到他的父亲节点的父亲节点，要么走到他的兄弟节点或他自己。

设当前节点的父亲节点的度数为 $d$ ，则经过一组操作后走到父亲节点的父亲节点的概率为 $\frac{1}{d} $ 。因为兄弟节点的父亲节点和自己的父亲节点是同一个节点，所以走到父亲节点的父亲节点的概率相等，可以推出不使用硬币时走到父亲节点的父亲节点的期望步数为 $2d$ 。

当使用硬币时，这组的第二步一定会向父亲节点走，所以走到父亲节点的父亲节点的步数为 $2$ 。

我们把每一组操作不使用硬币走到父亲节点的父亲节点的期望步数值存到一个 `vector` 里，然后把前 $p$ 大值变成 $2$ ，最后求和即为部分答案。

现在还有一个没处理的情况就是，当他走到一个节点，那个节点的父亲为 $1$ 号节点时，把答案加一即可。

复杂度 $O\left (  nq\log_{}{n} \right ) $ ，能过，不过完全可以优化。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
long long t,n,q,u,v,x,p,fa[2222],ans;
vector<long long>b[2222],ve;
void dfs(long long x,long long syg)
{
	fa[x]=syg;
	for(long long i=0;i<b[x].size();i++)
	{
		long long y=b[x][i];
		if(y==syg)
		{
			continue;
		}
		dfs(y,x);
	}
}
void dfs2(long long x)
{
	if(x==1)
	{
		return;
	}
	if(fa[x]==1)
	{
		ans++;//将答案加一
		return;
	}
	ve.push_back(b[fa[x]].size());
	dfs2(fa[fa[x]]);
}
int main()
{
	cin>>t;
	for(long long qwer=1;qwer<=t;qwer++)
	{
		cin>>n>>q;
		for(long long i=1;i<=n;i++)
		{
			b[i].clear();
			fa[i]=0;
		}
		for(long long i=1;i<n;i++)
		{
			cin>>u>>v;
			b[u].push_back(v);
			b[v].push_back(u);
		}
		dfs(1,0);//求每个节点的父亲节点
		for(long long i=1;i<=q;i++)
		{
			cin>>x>>p;
			ve.clear();
			ans=0;
			dfs2(x);
			if(ve.size()>0)
			{
				sort(ve.begin(),ve.end());
			}
			for(long long j=ve.size()-1;j>=0;j--)
			{
				if(p>0)
				{
					ans+=2;
					p--;
				}
				else
				{
					ans+=ve[j]*2;
				}
			}
			cout<<ans<<endl;
		}
	}
}
```

---

## 作者：Iniaugoty (赞：5)

### [CF2040E Control of Randomness](/problem/CF2040E)

额额，几乎一眼题卡了 1h 没调过，改个 while 条件就过了，好，很好，非常好。

先不考虑使用硬币。

设 $dp _ {u, i}$ 表示当前在 $u$ 结点，下一步操作的编号 $\bmod 2$ 为 $i$，到达 $1$ 的期望步数。

首先显然 $dp _ {1, 0} = dp _ {1, 1} = 0$。

然后显然 $dp _ {u, 1} = dp _ {fa _ u, 0} + 1$。

还有显然 $dp _ {u, 0} = \frac {dp _ {fa _ u, 1} + \sum _ {v \in son(u)} dp _ {v, 1}} {deg _ u} + 1$。

这个式子里面同时有孩子和父亲很难看。

将 $dp _ {v, 1} = dp _ {u, 0} + 1$ 带进去得到 $dp _ {u, 0} = \frac {dp _ {fa _ u, 1} + \sum _ {v \in son(u)} dp _ {u, 0} + 1} {deg _ u} + 1$。

整理得到 $dp _ {u, 0} = dp _ {fa _ u, 1} + 2 deg _ u - 1$。

非常优美！

注意到上面这些转移，很多值是无用的，最后只关注 $dp _ {u, 1}$，所以带入一些东西，就直接得到了，$dp _ {u, 1} = dp _ {fa _ {fa _ u}, 1} + 2 deg _ {fa _ u}$。

又是非常优美！

于是这个所谓 $dp _ {u, 1}$，只是在 $u$ 到 $1$ 的链上，隔一个结点求 $deg$ 之和。

使用硬币的话，$dp _ {u, 0} = dp _ {fa _ u, 1} + 1$，于是又有 $dp _ {u, 1} = dp _ {fa _ {fa _ u}, 1} + 2$。

所以注意到，在一个结点处使用硬币，只是把 $deg$ 的贡献改成 $1$。

于是只需要贪心地把最大的 $p$ 个 $deg$ 改掉即可。

[直接做](https://codeforces.com/contest/2040/submission/295643736)时间复杂度 $O(nq)$。

但是这个做法非常的有前途啊！可以用 DS 随便优化到 $O(q \log n)$，~~而且感觉 corner 还更少~~。

出题人应该把 $n$ 和 $q$ 加强到 $2 \times 10 ^ 5$，难度起码升个 100 吧，而且这样一些随便 DP 就不好做了。

---

## 作者：lfxxx (赞：4)

不妨 $dp_{i,j,0/1}$ 表示处于点 $i$ 还剩 $j$ 个硬币，下一步是奇数步还是偶数步，抵达 $1$ 的期望最小值。

显然有 $dp_{i,j,0} = dp_{fa_i,j,1}+1$。

考虑对于 $dp_{i,j,1}$ 而言，假若不花费硬币，你是一个不断走下去又不断走回来的过程，具体而言每次有 $\frac{d-1}{d}$ 的概率走下去又走回来，这个过程会花费 $2$ 步，而有 $\frac{1}{d}$ 的概率走上去，也就是 $dp_{i,j,1} = \min(dp_{fa_i,j-1,0}+1,dp_{fa_i,j,0} + (\sum_{i=0}^{\infty} 2 \times i \times (\frac{d-1}{d})^i) \times \frac{1}{d} + 1)$。

等差数列求等比数列，处理方法是先乘上公比做差后得到一个等比数列再乘上公比做差，具体式子这里略去，结果是 $dp_{i,j,1} = \min(dp_{fa_i,j-1,0}+1,dp_{fa_i,j,0} + (d-1) \times 2 + 1)$，于是 $O(n^2)$ 预处理 $O(1)$ 回答即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = 2e3+114;
int dp[maxn][maxn][2];
vector<int> E[maxn];
int fa[maxn];
int n,q;
int dfn[maxn],dfncnt;
void dfs(int u){
    dfn[++dfncnt]=u;
    for(int v:E[u]){
        if(v!=fa[u]){
            fa[v]=u;
            dfs(v);
        }
    }
}
void work(){
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1);
    for(int i=0;i<=n;i++){
        dp[1][i][0]=dp[1][i][1]=0;
        for(int j=2;j<=n;j++){
            int u=dfn[j];
            if(i>=1) dp[u][i][1]=min(dp[fa[u]][i-1][0]+1,dp[fa[u]][i][0]+(int)(1ll*(E[u].size()-1)*2+1));
            else dp[u][i][1]=dp[fa[u]][i][0]+1ll*(E[u].size()-1)*2+1;
            dp[u][i][0]=dp[fa[u]][i][1]+1;
        }
    }
    while(q--){
        int x,y;
        cin>>x>>y;
        cout<<dp[x][y][0]%mod<<'\n';
    }
    for(int i=1;i<=n;i++){
        fa[i]=0;
        E[i].clear();
    }
    dfncnt=0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}

```

---

## 作者：bsdsdb (赞：2)

题意：一个人拿着 $p(p\le 2000)$ 块钱在一棵树 $(n\le 2000)$ 的节点 $v$ 上走，规则如下：

- 如果这是第奇数步，向根走一步；
- 否则：
  - 付一块钱，向根走一步；
  - 或者，不付钱，向随机邻点走一步。

对 $q$ 对 $(v,p)$ 回答最优选择下，走到根的步数的最小期望值。

考虑 dp，设 $\mathrm{dp}_{i,j,0/1}$ 表示目前走到节点 $i$，有 $j$ 块钱，将要走第偶数 / 奇数步的答案。为了方便表述，定义 $\mathrm{sc}_i:=\text{number of sons of }i,p_i:=\text{parent of }i$. 初始情况显然是 $\mathrm{dp}_{1,j,0/1}=1$，奇数步也很好递推：$\mathrm{dp}_{i,j,1}=\mathrm{dp}_{p_i,j,0}+1$。对于偶数步，根据题目可得：

$$
\mathrm{dp}_{i,j,0}=1+\begin{aligned}\begin{cases}
\mathrm{dp}_{p_i,j-1,1},\qquad&\text{to pay}\\
\dfrac{\mathrm{dp}_{p_i,j,1}+\sum_{u\text{ is a son of }i}\mathrm{dp}_{u,j,1}}{\mathrm{sc_i}+1},\qquad&\text{not to pay}
\end{cases}\end{aligned}
$$

不付钱的情况与父亲和儿子都有关，比较难搞。但是不难注意到：$\forall u\text{ is a son of }i:\mathrm{dp}_{u,j,1}=\mathrm{dp}_{p_u,j,0}+1=\mathrm{dp}_{i,j,0}+1$，也就是说，对于不付钱的情况：

$$
\begin{aligned}
\mathrm{dp}_{i,j,0}&=1+\dfrac{\mathrm{dp}_{p_i,j,1}+\sum(\mathrm{dp}_{i,j,0}+1)}{\mathrm{sc}_i+1}\\
&=\dfrac{\mathrm{dp}_{p_i,j,1}+\mathrm{sc}_i\mathrm{dp}_{i,j,0}+2\mathrm{sc}_i+1}{\mathrm{sc}_i+1}\\
(\mathrm{sc}_i+1)\mathrm{dp}_{i,j,0}&=\mathrm{dp}_{p_i,j,1}+\mathrm{sc}_i\mathrm{dp}_{i,j,0}+2\mathrm{sc}_i+1\\
\mathrm{dp}_{i,j,0}&=\mathrm{dp}_{p_i,j,1}+2\mathrm{sc}_i+1
\end{aligned}
$$

所以，$\mathrm{dp}_{i,j,0}=\min\{\mathrm{dp}_{p_i,j-1,1},\mathrm{dp}_{p_i,j,1}+2\mathrm{sc}_i\}+1$。

更进一步的逻辑细节请参考 [this](https://codeforces.com/blog/entry/137182?#comment-1227247).

第一次见这种消掉 dp 的后效性用的是推式子而不是改状态的题。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const ldb eps = 1e-8;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 2e3 + 5;

ll n, q, coin, dp[MAXN][MAXN][2];
vector<ll> e[MAXN];

void srh(ll x, ll pr) {
	ll sc = e[x].size() - bool(pr);
	if (x == 1) {
		dp[x][coin][0] = dp[x][coin][1] = 0;
	} else {
		dp[x][coin][1] = dp[pr][coin][0] + 1;
		if (coin > 0) {
			dp[x][coin][0] = min(dp[pr][coin - 1][1], dp[pr][coin][1] + (sc << 1)) + 1;
		} else {
			dp[x][coin][0] = dp[pr][coin][1] + (sc << 1) + 1;
		}
	}
	for (ll i : e[x]) {
		if (i == pr) {
			continue;
		}
		srh(i, x);
	}
}

void init() {
	for (ll i = 1; i <= n; ++i) {
		e[i].clear();
		for (ll j = 0; j <= n; ++j) {
			dp[i][j][0] = dp[i][j][1] = 0;
		}
	}
	coin = 0;
}
int mian() {
	read(n), read(q);
	for (ll i = 1; i < n; ++i) {
		ll u, v;
		read(u), read(v);
		e[u].empb(v), e[v].empb(u);
	}
	for (coin = 0; coin <= n; ++coin) {
		srh(1, 0);
	}
	while (q--) {
		ll x, p;
		read(x), read(p);
		write(dp[x][p][1]), enter();
	}
	return 0;
}

int main() {
	ll T;
	read(T);
	while (T--) {
		init();
		mian();
	}
	return 0;
}

;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：wfc284 (赞：0)

本人没有那么出色的观察力。  

将奇偶两个操作合为一组。先不考虑用硬币。  
对于当前在 $u$ 点进行的【一组】操作，首先会 $100\%$ 地走向 $fa_u$，再随机蹦跳。设 $fa_u$ 的度数为 $d$。在 $fa_u$ 处，有 $\frac{1}{d}$ 的概率蹦向 $fa_{fa_u}$，有 $\frac{d-1}{d}$ 的概率蹦回 $u$ 的兄弟（或 $u$）。我们想，$u$ 的兄弟们的期望**一定都是相同的**，都是 $E(fa_u)+1$（要在奇数次操作花一步向父亲跳）。故：
$$E(fa_u)=\frac{1}{d} \cdot 1 + \frac{d-1}{d}[E(fa_u)+2] $$
$+2$ 的原因是往下往上浪费了两步。
解得 $E(fa_u)=2d-1$。  
于是 $E(u)=E(fa_u)+1=2d$。  
算贡献，就可以理解为一蹦两步地统计。可处理出 $u \to fa_{fa_u} \to fa_{fa_{fa_{fa_u}}} \to ... \to 1$ 每步贡献，存进一个 `vector` 里。

那再考虑硬币，**相当于把父节点的度数改为 $1$**。我们可以贪心地选出最大的 $p$ 个度数，改成 $1$。

统计答案，累加即可。当然，如果某【一组】操作在奇数操作就跳到了 $1$ 号，期望加一后退出就行。  

~代码抄第一篇题解就行~

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define int long long
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 2e3+2, mod = 998244353;
	
	int n, q;
	vector<int> g[N];
	
	int fa[N];
	void DFS1(int u, int f) {
		fa[u] = f;
		for(auto v : g[u]) {
			if(v == f) continue;
			DFS1(v, u);
		}
	}
	
	int ans;
	vector<int> ve;
	void DFS2(int u) {
		if(u == 1) return;
		if(fa[u] == 1) {
			++ans;
			return;
		}
		ve.push_back(g[fa[u]].size());
		DFS2(fa[fa[u]]);
	}
	
	void main() {
		cin >> n >> q;
		for(int i = 1; i <= n; ++i) g[i].clear();
		for(int i = 1, u, v; i < n; ++i) {
			scanf("%lld%lld", &u, &v);
			g[u].push_back(v), g[v].push_back(u);
		}
		DFS1(1, 0);
		
		for(int Case = 1, v, p; Case <= q; ++Case) {
			scanf("%lld%lld", &v, &p);
			ans = 0, ve.clear();
			DFS2(v);
			sort(all(ve), greater<int>());
			for(int i = 0; i < (int)ve.size(); ++i)
				if(i < p) ans += 2;
				else ans += ve[i] * 2;
			printf("%lld\n", ans % mod);
		}
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}
```

---

