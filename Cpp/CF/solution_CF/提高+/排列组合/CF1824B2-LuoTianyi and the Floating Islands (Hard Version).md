# LuoTianyi and the Floating Islands (Hard Version)

## 题目描述

这是该问题的困难版本。唯一的区别在于本版本中 $k \le n$。只有当你同时解决了该问题的两个版本时，才能进行 hack。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/12896184a3f823fcd8518f46dc5b68823c932f0f.png) Chtholly 和浮空岛。LuoTianyi 现在生活在一个有 $n$ 个浮空岛的世界里。这些浮空岛通过 $n-1$ 条无向空中航线连接，任意两个岛屿都可以通过这些航线互相到达。也就是说，这 $n$ 个浮空岛构成了一棵树。

有一天，LuoTianyi 想去见她的朋友们：Chtholly、Nephren、William，等等。她一共想见 $k$ 个人。她不知道他们的具体位置，但她知道他们分别在 $k$ 个不同的岛屿上。她定义一个岛屿是“好”的，当且仅当从该岛屿到这 $k$ 个有人岛屿的距离之和，在所有 $n$ 个岛屿中最小。

现在，LuoTianyi 想知道，如果这 $k$ 个人随机分布在 $n$ 个岛屿中的 $k$ 个不同岛屿上，那么期望有多少个“好”岛屿？你只需要告诉她这个期望值对 $10^9+7$ 取模的结果。

$^\dagger$ 两个岛屿之间的距离是指从一个岛屿到另一个岛屿所需经过的最少航线数。

## 说明/提示

在第一个样例中，航线构成如下的树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/f98245759af7851bb13c350e387c9b296063f10a.png)

如果这两个人分别在岛屿 $1$ 和 $2$ 上，则岛屿 $1$ 和 $2$ 都是“好”岛屿。

从岛屿 $1$ 或 $2$ 到所有人的距离之和是 $1+0=1$，这是最小值。而从岛屿 $3$ 到所有人的距离之和是 $2+1=3$，大于 $1$。

类似地，当两个人在岛屿 $1$ 和 $3$ 时，岛屿 $1,2,3$ 都是“好”岛屿。

当两个人在岛屿 $1$ 和 $4$ 时，岛屿 $1,2,3,4$ 都是“好”岛屿。

当两个人在岛屿 $2$ 和 $3$ 时，岛屿 $2$ 和 $3$ 是“好”岛屿。

当两个人在岛屿 $2$ 和 $4$ 时，岛屿 $2,3,4$ 是“好”岛屿。

当两个人在岛屿 $3$ 和 $4$ 时，岛屿 $3$ 和 $4$ 是“好”岛屿。

所以“好”岛屿数量的期望为 $\frac{16}{6}$，对 $10^9+7$ 取模后等于 $666666674$。

在第二个样例中，航线构成如下的树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1824B2/2f411e079090512cd14c27f9186226921a07c282.png)

可以看到每个岛屿上各有一个人，只有岛屿 $3$ 是“好”岛屿。所以期望数量为 $1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
1 2
2 3
3 4```

### 输出

```
666666674```

## 样例 #2

### 输入

```
5 5
1 2
2 3
3 4
3 5```

### 输出

```
1```

# 题解

## 作者：Reunite (赞：11)

## 一
---
   首先由 easy 版的启示，考虑 $k$ 为奇数的情况。
   
   - 当 $k=1$ 时，显然答案为 $1$。
   - 当 $k=3$ 时，经过讨论可知，好点一定在某一对点的 $lca$ 上，且是唯一的，答案仍为 $1$。
   - 当 $k$ 为其他奇数时，由~~数学归纳法~~（初中绝对值知识）可猜测，答案仍未 $1$。
   
   所以以下我们只需考虑 $k$ 为偶数的平凡情况。
   
## 二
---
       
   经过画图手玩可以发现，若 $k$ 个点已经确定是，好点一定是连续分布的。
    
   给出简单的说明：若不连续，考虑一个 $x\rightarrow y\rightarrow z$ 的连续三个点，则存在 $x$ 是好点，$z$ 是好点，$y$ 不是好点。设 $x,y,z$ 的块内分别有 $X,Y,Z$ 个点，最小距离和为 $d$。距离和与移动所有点到一点的路径长度和是等价的，假设所有点已经移到了 $x,y,z$ 三个点，容易知道这个值是定值，记此时的距离和为 $dd$，则根据好点定义：
   
        
$\begin{cases}Y+2Z=d-dd \\Y+2X=d-dd\\ X+Z>d-dd\end{cases}$
   
   显然这是矛盾的。即证。
   
   注意到在上述推导中，有 $X=Z$ 这一等式，容易证明对于每一条连接两好点的边，两边都分布了同样多的点。
   
   这也是本题的关键所在。
   
   还有一点要注意的是，直接计算对好点的贡献较烦，所以考虑计算边的贡献（也对应了上面“两边分布了同样多的点”）。因为一棵树的连通子图还是一棵树，因此好点的期望数就是“好边”期望数 $+1$。
   
   我们先一遍 DFS 求出子树节点数等信息，枚举每一条边，利用组合数，算出这条边的贡献，最后总答案加一即可。注意最后要除以总方案数。
   
$\large ans=\sum_{v=1}^{n}(\frac{C_{sz[v]}^{\frac{k}{2}}\cdot C_{n-sz[v]}^{\frac{k}{2}}}{C_{n}^{k}})+1$

----
[code](https://codeforces.com/contest/1824/submission/205240163)

---

## 作者：Register_int (赞：10)

对于 $k$ 为奇数的情况，首先好点必定存在，每次从好点移动一格，都会至少让路径长度增加 $\left\lfloor\dfrac k2\right\rfloor+1-\left\lfloor\dfrac k2\right\rfloor=1$，因此好点只有一个。直接输出 $1$。
以下设有人的点为“黑点”。

考虑在树上选出 $k$ 个点后，由于每次将好点向外移动时，一侧子树内的黑点数单调不增，因此距离总和单调不降。所以，好点在树上形成了一个连通块。为方便起见，我们可以该求一条边是否为好边。由于树的联通子图仍然是树，因此满足好点树比好边数多 $1$，求出边的期望即可。

对于一条好边 $(u,v)$，他的左右两端必定各有 $k/2$ 个黑点，否则点数较少一端不可能为好点，不满足好边的定义。那么放置黑点方案数为 $\dbinom{\text{size}_v}{k/2}\dbinom{n-\text{size}_v}{k/2}$，直接计算后除以总方案数，时间复杂度为 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;
const int mod = 1e9 + 7;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	for (; p; b = b * b % mod, p >>= 1) if (p & 1) res = res * b % mod;
	return res;
}

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll c(int n, int m) {
	if (n < 0 || m < 0 || n < m) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

struct node {
	int v, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

inline 
void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot;
}

int n, k, s[MAXN]; ll ans;

void dfs(int u, int f) {
	s[u] = 1;
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v;
		if (v == f) continue; dfs(v, u), s[u] += s[v];
		ans = (ans + c(s[v], k >> 1) * c(n - s[v], k >> 1) % mod) % mod;
	}
}

int main() {
	scanf("%d%d", &n, &k);
	if (k & 1) return puts("1"), 0;
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	init(n), dfs(1, 0);
	printf("%lld", (ans * ifac[n] % mod * fac[k] % mod * fac[n - k] % mod + 1) % mod);
}
```

---

## 作者：Un1quAIoid (赞：6)

这是 CF1824B 枚举点计算贡献的 $O(n)$ 做法。

--------------

**step1**

称有人的结点为**关键点**。

实际上 $\min_u \sum_{i} dis(u,i)$ 的性质就是**重心**，即点 $u$ 是好的当且仅当以 $u$ 做为根时，每个子树中关键点的数量均 $\le \lfloor \dfrac{k}{2} \rfloor$，因为从这样的点向任意方向移动都只会使距离和不减。

**step2**

接下来的思路非常直接：枚举每个点 $u$，然后计算有多少关键点的分布方式使得 $u$ 满足 step1 中提到的性质。

直接算不太行，但是注意到关键点数 $> \lfloor \dfrac{k}{2} \rfloor$ 的子树至多有一个，所以可以考虑容斥，于是点 $u$ 的贡献有式子：

$$
\sum_{(u,v) \in E} \sum_{i = \lfloor \frac{k}{2} \rfloor + 1}^{k} \binom{siz_v}{i} \binom{n-siz_v}{k-i}
$$

直接抄式子，能得到一个 $O(n^2)$ 做法。

**step3**

注意到 $\sum_{i = \lfloor \frac{k}{2} \rfloor + 1}^{k} \binom{siz_v}{i} \binom{n-siz_v}{k-i}$ 这整个式子只跟 $siz_v$ 有关系所欲我们不妨设：

$$
f_x = \sum_{i = \lfloor \frac{k}{2} \rfloor + 1}^{k} \binom{x}{i} \binom{n-x}{k-i}
$$

可以考虑 $O(n)$ 递推出来 $f_{1 \dots n}$。具体来说，我们有：

$$
\begin{aligned}
L &= \lfloor \frac{k}{2} \rfloor + 1\\
f_{x+1} - f_{x} &= \sum_{i = L}^k \binom{x+1}{i}\binom{n-x-1}{k-i}-\binom{x}{i}\binom{n-x}{k-i}\\
&= \sum_{i=L}^k \binom{x}{i-1}\binom{n-x-1}{k-i} + \binom{x}{i}\binom{n-x-1}{k-i} - \binom{x}{i}\binom{n-x}{k-i}\\
&= \sum_{i=L-1}^{k-1} \binom{x}{i}\binom{n-x-1}{k-i-1}-\sum_{i=L}^{k-1} \binom{x}{i}\binom{n-x-1}{k-i-1}\\
&= \binom{x}{\lfloor \frac{k}{2} \rfloor} \binom{n-x-1}{k - \lfloor \frac{k}{2} \rfloor - 1}
\end{aligned}
$$

于是我们就能 $O(n)$ 递推出 $f_{1 \dots n}$ 了，当然这个差分也可以考虑组合意义而不是暴力推：考虑 $f_{x+1}$ 比 $f_x$ 多的部分实际上就是前 $x+1$ 个点中恰好有 $\lfloor \frac{k}{2} \rfloor + 1$ 个关键点且第 $x+1$ 个点必为关键点的情况。

总复杂度 $O(n)$，所以这题实际上可以加强到带点权 $n \le 1 \times 10^7$。

代码：
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define eb emplace_back
#define pb push_back
#define mp make_pair
using namespace std;

typedef long long ll;
const int N = 2e5+5;
const int Mod = 1e9+7;

int n, k, siz[N];
int ans;
int f[N];

ll fac[N], ifac[N];

vector<int> T[N];

void dfs(int x, int fa) {
    siz[x] = 1;
    for (int son : T[x]) {
        if (son == fa) continue;
        dfs(son, x);
        siz[x] += siz[son];
    }
}

inline int qpow(int a, int b) {
    ll base = a, ans = 1;
    while (b) {
        if (b & 1) ans = ans * base % Mod;
        base = base * base % Mod;
        b >>= 1;
    }
    return ans;
}

inline void Add(int &a, int b) { a += b; if (a >= Mod) a -= Mod; }
inline ll C(int n, int m) { return n >= m ? fac[n] * ifac[m] % Mod * ifac[n - m] % Mod : 0; }

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        T[u].pb(v);
        T[v].pb(u);
    }

    dfs(1, 0);

    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % Mod;
    ifac[n] = qpow(fac[n], Mod - 2);
    for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % Mod;

    for (int i = 1; i <= n; i++) {
        f[i] = (f[i - 1] + C(n - i, k - k / 2 - 1) * C(i - 1, k / 2)) % Mod;
    }

    for (int i = 1; i <= n; i++) {
        Add(ans, C(n, k));
        for (int son : T[i]) {
            int s = siz[son] < siz[i] ? siz[son] : n - siz[i];
            Add(ans, Mod - f[s]);
        }
    }

    printf("%lld", (ll) ans * qpow(C(n, k), Mod - 2) % Mod);
    return 0;
}
```

---

## 作者：王熙文 (赞：3)

发现和我自己出的一道题 idea 有点相似，也许都是经典的套路吧。

## 思路

首先考虑如何判定一个节点是否是好的。考虑从根开始 dfs，同时计算当前节点与 $k$ 个节点的距离之和。考虑 $fa$ 走到 $u$ 的答案变化。考虑用每一条边的贡献计算距离之和，可以发现 $fa$ 到 $u$ 的这条边的贡献加上了 $k-2\cdot cnt_u$（$cnt$ 表示子树内选的节点个数），其它边的贡献没变。可以发现贡献的变化一定是从小到大的，且如果想保持贡献非正每次最多走向一个儿子，因此一种方案的好的节点个数为贡献为 $0$ 的边组成的链的节点个数。因为子树中选的节点个数为 $\dfrac{k}{2}$ 的节点是这条链除了链顶的节点，所以答案为子树选的节点为 $\dfrac{k}{2}$ 的节点个数$\text{}+1$。

因此当 $k$ 为奇数的时候答案一定为 $1$，可以先特判掉。

考虑统计所有树的好的节点个数之和。对每个点计算贡献，它的子树内选的节点个数需要为 $\dfrac{k}{2}$，所以一个点 $u$ 的贡献为 $C_{siz_u}^{\frac{k}{2}} \cdot C_{n-siz_u}^{\frac{k}{2}}$。加起来并除以 $C_{n,k}$ 再加 $1$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 1000000007
int qpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int jc[200010],invjc[200010];
int C(int n,int m) { return n<m?0:jc[n]*invjc[n-m]%mod*invjc[m]%mod; }
int n,k; vector<int> e[200010];
int siz[200010];
void dfs(int u,int fa)
{
	siz[u]=1;
	for(int v:e[u])
	{
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
signed main()
{
	jc[0]=1; for(int i=1; i<=2e5+5; ++i) jc[i]=jc[i-1]*i%mod;
	invjc[(int)2e5+5]=qpow(jc[(int)2e5+5],mod-2);
	for(int i=2e5+4; i>=0; --i) invjc[i]=invjc[i+1]*(i+1)%mod;
	cin>>n>>k;
	for(int i=1; i<=n-1; ++i)
	{
		int u,v; cin>>u>>v;
		e[u].push_back(v),e[v].push_back(u);
	}
	dfs(1,0);
	int cnt=C(n,k),ans=cnt;
	if(k%2==0) for(int i=1; i<=n; ++i) ans=(ans+C(siz[i],k/2)*C(n-siz[i],k/2))%mod;
	cout<<ans*qpow(cnt,mod-2)%mod;
	return 0;
}
```

---

## 作者：shinkuu (赞：2)

**结论：当 $k$ 为奇数时，答案永远为 $1$。**

证明：假设现在有一个点 $x$ 距离其他点距离之和最小，若我们沿 $x$ 的任意一条出边动一步到 $y$，则 $dist(x,i)=dist(y,i)-1$ 的数量一定不等于 $dist(x,i)=dist(y,i)+1$ 的数量，因为他们的奇偶性一定不同。故得证。

再考虑 $k$ 为偶数的情况：这时候就可以在我们[上一题的做法](https://www.luogu.com.cn/blog/Kato-Megumi/cf1824b1-post)上改进了：仍然是对每一条边算贡献，但是这次每一侧可能不止选 $1$ 个点，而是选 $\dfrac{k}{2}$ 个。所以这条边的贡献就为 $C_{siz_v}^{\frac{k}{2}}\times C_{n-siz_v}^{\frac{k}{2}}$。dfs 一遍求出总和 $s$，再和 B1 同理，最后期望即为 $\dfrac{s+C_n^k}{C_n^k}$。

code：

```cpp
int n,m,f[N];
int sum=0;
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
inline void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
inline int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
inline int Cnm(int x,int y){
	if(x<0||y<0||x<y)
		return 0;
	return 1ll*f[x]*qpow(1ll*f[y]*f[x-y]%mod,mod-2)%mod;
}
int siz[N];
void dfs(int u,int f){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)
			continue;
		dfs(v,u);
		siz[u]+=siz[v];
		sum=(sum+1ll*Cnm(siz[v],m/2)*Cnm(n-siz[v],m/2)%mod)%mod;
	}
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	f[0]=1;
	for(int i=1;i<=n;i++)
		f[i]=1ll*f[i-1]*i%mod;
	if(m&1){
		puts("1");
		return;
	}
	dfs(1,0);
	int k=Cnm(n,m);
	printf("%lld\n",1ll*(sum+k)%mod*qpow(k,mod-2)%mod);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：nalemy (赞：2)

根据 D1 中 $k\le3$ 时的结论，我们合理猜测 $k$ 为奇数时答案为 $1$。

**证明**：首先存在至少一个 good nodes，设其一为 $t$。我们设定 $t$ 为这棵树的根，令 $s_i$ 为当前有根树中，节点 $i$ 的子树中关键点的个数。定义 $\Delta f_i=f_i-f_{\operatorname{fa}_i}=+(k-s_i)-s_i=k-2s_i$。

然后我们考察 $t$ 的儿子中 $s$ 最大的点 $m$，因为 $t$ 为 good node，所以 $f_m\ge f_i$，即 $\Delta f_m=k-2s_m\ge0$，又因为 $k$ 为奇数，有 $k-2s_m>0$。

因为 $m$ 是 $t$ 的儿子中 $s$ 最大的点，不难发现 $(\forall i\neq t)s_i\le s_m$。于是 $k-2s_m>0\Longrightarrow(\forall i\neq t)\Delta f_i=k-2s_i>0$。

于是 $(\forall i\neq t)f_i>f_t$。即 good node 唯一。

---

下面考虑 $k$ 为偶数。类似于上面的证明，我们可以发现 $i$ 为 good node 当且仅当 $s_i=\dfrac{k}2$ 或 $i=t$。

然后我们考虑将枚举关键点集合 $S$ 并计算 $s_i=\dfrac{k}2$ 个数，转化为枚举 $i$ 并计算相应的 $S$ 个数，即

$$\binom{s_i}{\frac{k}2}\binom{k-s_i}{\frac{k}2}$$

注意还有 $i=t$ 的特殊情况，对于每个 $S$ 恰有 $1$ 个合法 good node，贡献总计 $\binom{n}{k}$。

最后求期望，答案为以上两种情况方案数除以关键点集合 $S$ 的个数，即 $\binom{n}{k}$。

---

```C++
#include<iostream>
#include<vector>

const int N = 2e5, P = 1e9 + 7;
std::vector<int>g[N];
int n, k, ans, sz[N];
long long fc[N+1], ifc[N+1];
long long C(int n, int m) {
	if (m < 0 || n < m) return 0;
	return fc[n]*ifc[m]%P*ifc[n-m]%P;
}
long long fp(long long a, int b=P-2) {
	long long r = 1;
	for (; b; a=a*a%P, b>>=1)
		if (b & 1) r = r * a % P;
	return r;
}
void dfs(int u, int fa) {
	sz[u] = 1;
	for (int v : g[u]) if (v != fa)
		dfs(v, u), sz[u] += sz[v];
	(ans += C(sz[u], k)*C(n-sz[u], k)%P) %= P;
}
int main() {
	std::cin >> n >> k, *fc = 1;
	if (k & 1) return puts("1"), 0;
	for (int i=1; i<=n; i++) fc[i] = fc[i-1] * i % P;
	ifc[n] = fp(fc[n]);
	for (int i=n; i; i--) ifc[i-1] = ifc[i] * i % P;
	for (int i=1, u, v; i<n; i++)
		std::cin >> u >> v, g[--u].push_back(--v), g[v].push_back(u);
	k >>= 1, dfs(0, 0), printf("%lld", (ans*fp(C(n, k*2))+1)%P);
}
```

---

## 作者：MatrixGroup (赞：2)

我们令 $p_i$ 为 $i$ 是坏的结点的概率，则答案为

$$n-\sum_{i=1}^n p_i$$

考虑计算 $p_i$。

$\textbf{Lemma }$ 一个点 $i$ 是坏的结点，当且仅当存在 $(i,j)\in E$，使得当 $i$ 为根时，以 $j$ 为根的子树中选定点的个数 $s$ 使得 $2s>k$。

$\textbf{Proof}$

$\Leftarrow$。显然，$j$ 比 $i$ 多了 $s$ 个贡献，少了 $k-s$ 个贡献，所以更优。$\square$

$\Rightarrow$。如果一个 $\forall j,2s\le k$，但是 $j$ 是坏结点，考虑找到一个好结点 $u$，则根据上面有 $u$ 符合 $2s\le k$。我们定义一条边的方向是从优的点向不优的点。（如果同样则无向）在 $j$ 到 $u$ 的路径上，显然会有形如 $ f \leftarrow a_1 - a_2 - a_3 - \cdots - a_n \rightarrow g$ 的一段点，但是显然不可能以 $a_1$ 为根 $f$ 的子树 $2s>k$（即更优） 的同时 $(i=a_n,j=g)$ 也符合条件。矛盾。$\square$

我们考虑 $(i,j)$ 这一对的概率。我们令以 $i$ 为根时以 $j$ 为根的子树中有 $s_0$ 个可能是选定点的点，则贡献为

$$
f(s_0)=\dfrac{1}{\binom{n}{k}}\sum_{2s>k}\dbinom{s_0}{s}\dbinom{n-s_0}{k-s}
$$

注意到

$$\dfrac{1}{\binom{n}{k}}\dbinom{s_0}{s}\dbinom{n-s_0}{k-s}=\dfrac{k!(n-k)!s_0!(n-s_0)!}{n!s!(k-s)!(s_0-s)!(n+s-s_0-k)!}=\dfrac{1}{\binom{n}{s_0}}\dbinom{k}{s}\dbinom{n-k}{s_0-s}$$

因此 $f(s_0)$ 即为

$$
\dfrac{1}{\binom{n}{s_0}}\sum_{s=0}^k[2s>k]\dbinom{k}{s}\dbinom{n-k}{s_0-s}
$$

其中 $\dbinom{u}{v}$ 如果 $v<0$ 或 $v>u$ 则为 $0$。

这后式是卷积形式，因此我们可以预处理 $f(s_0)$，时间复杂度 $O(n\log n)$。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0,_##i##__end=(n);i<_##i##__end;++i)
#define per(i,n) for(int i=(n)-1;i>=0;--i)
#define rep1(i,n) for(int i=1,_##i##__end=(n);i<=_##i##__end;++i)
#define per1(i,n) for(int i=(n);i>=1;--i)
#define pb push_back
typedef long long ll;
using namespace std;

// 代码模板

const ll mod[3]={998244353,1004535809,167772161};
const __int128 mod1=__int128(mod[0])*mod[1]*mod[2];
const ll g[3]={3,3,3};
const __int128 mod_inv[3]={541135637,819070325,107800441};
const __int128 ans_mul[3]={mod_inv[0]*mod[1]*mod[2],mod_inv[1]*mod[2]*mod[0],mod_inv[2]*mod[0]*mod[1]};
const ll mod2=1000000007;
const int N=1048576;

// 一些常数，特别是为 CRT（三模 NTT）

int rev[N];
void init_rev()
{
	rev[0]=0;
	for(int i=1;i<N;++i)
	{
		rev[i]=rev[i>>1]>>1;
		if(i&1) rev[i]|=N>>1;
	}
}

// 预处理 位逆序反转

ll qkpw(ll a,ll b,ll p)
{
	ll r=1;while(b)
	{
		if(b&1)r=r*a%p;a=a*a%p;b>>=1; 
	}
	return r;
}

// 快速幂

template<int id>
void dft(ll a[N])
{
	ll mod0=mod[id],g0=g[id];
	rep(i,N) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int l=2;l<=N;l<<=1)
	{
		ll omega=qkpw(g0,(mod0-1)/l,mod0);
		for(int i=0;i<N;i+=l)
		{
			int f=i+l;
			ll w=1;
			for(int j=i,k=i+l/2;k<f;++j,++k)
			{
				ll v=a[k]*w%mod0;
				a[k]=(a[j]-v+mod0)%mod0;
				a[j]+=v;if(a[j]>=mod0)a[j]-=mod0;
				w=w*omega%mod0;
			}
		}
	}
}
template<int id>
void idft(ll a[N])
{
	dft<id>(a);
	ll f=qkpw(N,mod[id]-2,mod[id]);
	rep(i,N) a[i]=a[i]*f%mod[id];
	reverse(a+1,a+N);
}

// mod (mod[id]) 意义下的 DFT 和 IDFT

ll t1[N],t2[N];
template<int id>
void convolve(ll f[N],ll g[N],ll h[N])
{
	rep(i,N) t1[i]=f[i]%mod[id];rep(i,N)t2[i]=g[i]%mod[id];
	dft<id>(t1);dft<id>(t2);rep(i,N)h[i]=t1[i]*t2[i]%mod[id];idft<id>(h);
}

// mod (mod[id]) 意义下的卷积

int n,k,u,v;
vector<int> con[N];//领接表
int siz[N],dep[N];//子树大小和深度
ll F[N],G[N],h[3][N],ans[N];// F,G 为多项式 h[id] 为 mod (mod[id]) 结果 answer 为 mod mod2 结果
ll fac[N],ivf[N];// 预处理阶乘和逆元
void dfs(int ver,int par)//预处理
{
	siz[ver]=1;
	rep(i,con[ver].size())
	{
		int nei=con[ver][i];
		if(nei!=par)
		{
			dep[nei]=dep[ver]+1;
			dfs(nei,ver);
			siz[ver]+=siz[nei];
		}
	}
}
ll C(ll x,ll y)//组合数
{
	if(y<0||y>x) return 0;
	return fac[x]*ivf[y]%mod2*ivf[x-y]%mod2;
}
void init()//求出 f(s0)
{
	fac[0]=1;rep1(i,N-1) fac[i]=fac[i-1]*i%mod2;
	ivf[N-1]=qkpw(fac[N-1],mod2-2,mod2);per(i,N-1) ivf[i]=ivf[i+1]*(i+1)%mod2;
	rep(i,N) if(i*2>k) F[i]=C(k,i); rep(i,N) G[i]=C(n-k,i);
	convolve<0>(F,G,h[0]);convolve<1>(F,G,h[1]);convolve<2>(F,G,h[2]);
	rep(i,N)
	{
		ans[i]=(ans_mul[0]*h[0][i]+ans_mul[1]*h[1][i]+ans_mul[2]*h[2][i])%mod1%mod2;// CRT
		ans[i]=ans[i]*qkpw(C(n,i),mod2-2,mod2)%mod2;
	}
}
ll total; 
int main()
{
	init_rev();
	ios_base::sync_with_stdio(false);
	cin>>n>>k;
	rep(i,n-1)
	{
		cin>>u>>v;con[u].pb(v);con[v].pb(u);
	}
	init();dfs(1,0);
	rep1(i,n) rep(j,con[i].size())
	{
		int k=con[i][j],sub_siz=0;
		if(dep[k]<dep[i])// 分类讨论 求 siz
		{
			sub_siz=siz[i];
		}
		else
		{
			sub_siz=n-siz[k];
		}
		total+=ans[sub_siz];
	}
	total%=mod2;
	total=n-total;if(total<0)total+=mod2;
	cout<<total<<endl;
	return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

按照 $k$ 的奇偶分开考虑。

$k$ 为奇数。一个好的节点有且仅有一个在任意两个有人的节点 $i,j$ 的路径的交点上的最优位置。若该交点偏移 $1$ 步，则必然会使路径长度和 $+1$。故期望为 $1$。

$k$ 为偶数。任意一个好的节点仍然在任意两个有人的节点 $i,j$ 的交点上。但若对于某个好点的偏移，在偏移后距离增加与减少的距离均为 $\frac{k}{2}$ 时，这个点也是好的。考虑枚举边，若一条边的两边有人的点的数量均为 $\frac{k}{2}$，则这条边有贡献 $1$。即每条边的贡献之和为 $\sum\limits_{u=1}^{n-1} \binom{siz_u}{\frac{k}{2}}\times \binom{n-siz_u}{\frac{k}{2}}$。其中 $siz_u$ 为边 $u$ 左端的节点数量。但是，对于某一条有好点的路径 $x$，其中的边的数量总会比点的数量少一，所以贡献之和还需要加上 $\binom{n}{k}$。所以对于 $k$ 为偶数时，期望为 $\frac{\sum\limits_{u=1}^{n-1} \binom{siz_u}{\frac{k}{2}}\times \binom{n-siz_u}{\frac{k}{2}}+\binom{n}{k}}{\binom{n}{k}}$。

注：求组合数可以先预处理 $1 \le i \le n$ 的阶乘，在用逆元乘。在 $siz_u+1 \le \frac{k}{2}$ 的时候，这条边是没有贡献的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=1e6+10,p=1e9+7;
int n,k;
int ne[N],e[N],h[N],idx;
int sum,siz[N],__[N];

il int qmi(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=ans*a%p;
		a=a*a%p,b>>=1;
	}
	return ans;
}
il int C(int n,int m){
	if(n<m) return 0;
	return __[n]%p*qmi(__[m],p-2)%p*qmi(__[n-m],p-2)%p;
}

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il void dfs(int now,int fa){
	siz[now]=1;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dfs(j,now),siz[now]+=siz[j];
	}
	return ;
}
il void dfs2(int now,int fa){
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		sum=(sum+C(siz[j],k/2)*C(n-siz[j],k/2))%p;
		dfs2(j,now);
	}
	return ;
}

il void solve(){
	cin>>n>>k;
	for(re int i=1,u,v;i<n;++i)
		cin>>u>>v,
		add(u,v),add(v,u);
	if(k&1){cout<<"1\n";return;}
	__[0]=1;for(re int i=1;i<=n+5;++i) __[i]=__[i-1]*i%p;
	sum=C(n,k);
	dfs(1,0),dfs2(1,0);
	cout<<(sum%p*qmi(C(n,k),p-2)%p)%p<<"\n";
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：Feyn (赞：1)

[My Blog](https://www.cnblogs.com/Feyn/p/16977678.html)

首先把求好的点的期望个数转化成每个点成为好点的概率。思考一个点什么时候不是好点，会发现一个点不好当且仅当它向某条边的另一侧移动之后到所有给定点的距离之和变少了。假设断掉这条边之后这个点所在的连通块有 $x$ 个给定点，另一个连通块里有 $k-x$ 个，那么这条边的移动使得 $x$ 个点的距离加一，剩下的减一。于是容易发现结论，这样的移动更优当且仅当 $x$ 小于 $k$ 的一半。所以对于每个点而言可以考虑枚举出边，并计算边对面的给定点比这边的多的概率就可以了。容易发现这样是正确的。

但是这样化出来是个不优雅的柿子，看起来并不是很有优化空间的样子。然后我们发现一个事实，是说对于一条连接 $u,v$ 的边而言，答案会减去 $u$ 连通块比 $v$ 多的情况，也会减去 $v$ 比 $u$ 多的情况，这两种情况之和其实就是 $1$ 减去两边点数相同的概率。有了这个就很简单了，可以做到线性。

当时由于有点急所以代码写得比较丑，见谅。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int N=200010;
const int mod=1e9+7;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}

int m,n;
struct edge{
	int t,nxt;
}e[N<<1];
int head[N],esum;
inline void add(int fr,int to){
	e[++esum]=(edge){to,head[fr]};head[fr]=esum;
}

inline int qp(int s1,int s2){
	if(s2==0)return 1;int an=qp(s1,s2>>1);
	if(s2&1)return an*an%mod*s1%mod;
	else return an*an%mod;
}

int p[N],q[N],inv[N],all=1;
void init(){
	p[0]=q[0]=inv[0]=1;
	p[1]=q[1]=inv[1]=1;
	for(int i=2;i<N;i++){
		inv[i]=qp(i,mod-2);
		p[i]=p[i-1]*i%mod;
		q[i]=q[i-1]*inv[i]%mod;
	}
}
inline int ask(int s1,int s2){
	if(s1<0||s2<0||s1>N||s2>N||s2>s1)return 0;
	return p[s1]*q[s2]%mod*q[s1-s2]%mod;
}

int siz[N],ans;
void solve(int wh,int fa){
	siz[wh]=1;
	for(int i=head[wh],th;i;i=e[i].nxt){
		if((th=e[i].t)==fa)continue;
		solve(th,wh);siz[wh]+=siz[th];
	}
	if(fa==0)return;
	int now=ask(siz[wh],n/2)*ask(m-siz[wh],n/2)%mod*all%mod;
	if(n&1)now=0;
	ans-=1-now;
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);init();
	for(int i=1;i<m;i++){
		int s1,s2;read(s1);read(s2);
		add(s1,s2);add(s2,s1);
	}
	for(int i=1;i<=n;i++)all=all*(m-i+1)%mod;
	for(int i=1;i<=n;i++)all=all*qp(i,mod-2)%mod;
	all=qp(all,mod-2);
	solve(1,0);ans+=m;
	printf("%lld\n",(ans%mod+mod)%mod);
	
	return 0;
}
```

---

## 作者：SkyRainWind (赞：0)

[更好的阅读体验](https://www.cnblogs.com/SkyRainWind/p/17385633.html)

题解：
考虑一棵 $n$ 个点的树，假如已经选定了 $k$ 个特殊点，如何判断某一个点是否为好点？

显然将这个点提到根没有影响，那么好点的充要条件是对于所有子树的 $S_u$ 值都 $\leq k/2$，这里 $S$ 代表 $u$ 子树中的特殊点的个数。

证明完全可以考虑重心，只不过这里根可能不是特殊点（如果是特殊点的话，直接把所有非特殊点删去，和重心完全一样），可以发现不影响证明（可以将这个非特殊点合并到相邻的特殊点上，然后删去非特殊点）
这样，我们就找到了一个点是好点的条件。现在考虑对于任意的 $k$ 个点。

考虑指定某一点为根，这里有一个很妙的操作：指定根之后就可以将点的贡献拆到这个点与父亲的边上了。考虑一个边是否为“好边”，显然判断方法就看这条边左边的树的 $S$ 值是否和右边的 $S$ 一样，都是 $k/2$（由于 $\leq k/2$，且只有两个部分，那么肯定都得相等），也就是说这个边是好边的概率是：

$$p_{u,v}=\frac{C_{S_u}^{k/2}\times C_{n-S_v}^{k/2}}{C_n^k}$$

注意好边的定义是两边的点都是好点，因此期望点的个数期望好边的个数 $+1$，也就是 $1+\sum p$。

代码：
```cpp
// by SkyRainWind
#include <bits/stdc++.h>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define pii pair<int,int>
#define pb push_back

using namespace std;

typedef long long ll;
typedef long long LL;

const int inf = 1e9, INF = 0x3f3f3f3f, mod = 1e9+7, maxn = 2e5+5;

int fac[maxn], inv[maxn],inv2;
vector<int>g[maxn];

int pw(int x,int y){
	if(!y)return 1;
	if(y == 1)return x;
	int mid=pw(x,y>>1);
	if(y&1)return 1ll*mid*mid%mod*x%mod;
	return 1ll*mid*mid%mod;
}

int C(int x,int y){
	if(x < y)return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}

int sz[maxn];

int ans = 0, iv; 
void dfs(int x,int fat=0){
	sz[x] = 1;
	for(int u : g[x])if(u != fat){
		dfs(u, x);
		sz[x] += sz[u];
	}
}

signed main(){
	inv2=pw(2,mod-2);
	fac[0] = inv[0] = 1;
	for(int i=1;i<=maxn-5;i++)fac[i] = 1ll*fac[i-1]*i%mod;
	inv[maxn-5] = pw(fac[maxn-5], mod-2);
	for(int i=maxn-6;i>=1;i--)inv[i] = 1ll*inv[i+1]*(i+1)%mod;
	
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		g[x].pb(y), g[y].pb(x);
	}
	
	if(k %2 == 1){
		puts("1");
		return 0;
	}
	
	dfs(1);
	iv = pw(C(n,k), mod-2);
	for(int i=1;i<=n;i++)
		(ans += 1ll * C(sz[i], k/2) * C(n-sz[i], k/2)%mod) %= mod;
	printf("%d\n",(1ll * ans * iv + 1) % mod);
	
	return 0;
}
```

---

