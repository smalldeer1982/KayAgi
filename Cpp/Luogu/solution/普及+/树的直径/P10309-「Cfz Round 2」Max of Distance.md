# 「Cfz Round 2」Max of Distance

## 题目描述

给定一棵包含 $n$ 个结点的树 $G$ 和一个整数 $E$。

你需要构造树 $G$ 中每条边的整数边权 $w_i$，满足：

- $1 \le w_i \le 10^9$；
- 均匀随机选择一个结点 $u$，$\max\limits_{v=1}^n\operatorname{dis}(u,v)$ 的期望对 $998244353$ 取模的值等于 $E$；

或报告无解。

其中，$\operatorname{dis}(u,v)$ 表示结点 $u,v$ 之间简单路径上的边权和。

如果你不知道如何计算期望对 $998244353$ 取模的结果，请移步 [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)。

## 说明/提示

#### 「样例解释 #1」

所有 $\operatorname{dis}$ 的值如下表，其中标红的是行首结点的 $\operatorname{dis}$ 的最大值。

|$\operatorname{dis}$|$1$|$2$|$3$|
|:-:|:-:|:-:|:-:|
|$1$|$0$|$1$|$\color{red}3$|
|$2$|$1$|$0$|$\color{red}2$|
|$3$|$\color{red}3$|$2$|$0$|

可以验证，$E=\dfrac{3+2+3}{3}=\dfrac{8}{3}\equiv 665496238\pmod {998244353} $。

#### 「数据范围」

对于所有数据，$2\le n\le 10^5$，$1 \le u_i,v_i \le n$，$0\le E < 998244353$，保证输入数据形成一棵树。

**只有你通过本题的所有测试点，你才能获得本题的分数。**

## 样例 #1

### 输入

```
3
1 2
2 3
665496238```

### 输出

```
1
2```

# 题解

## 作者：hzlqwq (赞：12)

是很有趣的构造题！膜拜出题人！在这里给出一种不太一样，但是比较好想的做法。

首先，我们先不管 $E$ 的限制，假设所有的边权都为 $1$，试着求出这个期望：

由于我们知道**到树上一点最远的点，一定是直径的一个端点**，我们就可以先找出一条直径，然后从直径的两个端点开始分别 dfs 一遍，求出每个点的 $\max\limits_{v=1}^n \mathbb{dis}(u,v)$，从而算出此时的期望。

如果我们给每条边赋上不同的边权，那么直径可能会变化，我们原本求出的这个期望就没有用了。但是，如果**所有边的边权都相同的话，我们原本求出的直径，和现在的直径就是相同的**！而且，假设所有边的边权都为 $x$，所有边权都为 $1$ 的期望为 $y$，那么现在的期望就是 $xy$！因为原本的期望其实就是现在的**边数期望**，乘上边权就是答案的期望了。

那么当 $y\ne 0$ 时，只要令所有边的边权都为 $\frac{E}{y}$，就可以符合条件了。但是若 $y=0$，怎么办呢？

其实问题也不大。首先可以发现此时树不会是一条链（当 $1\leq n\leq 10^5$ 时，没有任何一种长度的链，可以使得期望为 $0$）；也就是说，至少有三个叶子节点；也就是说，**一定存在不是直径端点的叶子节点**；

那么我们只要把与那个叶子节点相连的边的边权改成 $\bmod$ 即可，这样取模后就为 $0$，这个点的 $\max\limits_{v=1}^n \mathbb{dis}(u,v)$ 就会 $-1$，期望就不会是 $0$ 了，就可以按原本的方法做了。

总时间复杂度 $O(n)$，如果没有特判的话还是非常短的。

```cpp
int n, E, u[N], v[N], p1, p2, dis[N], res[N], sum;
vector<int> e[N];

void dfs(int u, int fa)
{
    for (auto j : e[u])
        if (j ^ fa)
            dis[j] = dis[u] + 1, dfs(j, u);
}

int qpow(int x, int k)
{
    int res = 1;
    while (k)
    {
        if (k & 1)
            res = 1ll * res * x % mod;
        x = 1ll * x * x % mod, k >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for (int i = 1; i < n; i++)
        cin >> u[i] >> v[i], e[u[i]].push_back(v[i]), e[v[i]].push_back(u[i]);
    cin >> E;
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        if (dis[i] > dis[p1])
            p1 = i;
    dis[p1] = 0, dfs(p1, 0);
    for (int i = 1; i <= n; i++)
    {
        res[i] = max(res[i], dis[i]);
        if (dis[i] > dis[p2])
            p2 = i;
    }
    dis[p2] = 0, dfs(p2, 0);
    for (int i = 1; i <= n; i++)
        res[i] = max(res[i], dis[i]), sum = (sum + res[i]) % mod;
    if (!sum)
    {
        int tag;
        for (int i = 1; i < n; i++)
            if (e[u[i]].size() == 1 && u[i] != p1 && u[i] != p2)
            {
                tag = i;
                break;
            }
            else if (e[v[i]].size() == 1 && v[i] != p1 && v[i] != p2)
            {
                tag = i;
                break;
            }
        E = 1ll * n * E % mod * qpow(mod - 1, mod - 2) % mod;
        if (!E)
            E = mod;
        for (int i = 1; i < n; i++)
            if (i != tag)
                cout << E << "\n";
            else
                cout << mod << "\n";
        return 0;
    }
    E = 1ll * n * E % mod * qpow(sum, mod - 2) % mod;
    if (!E)
        E = mod;
    for (int i = 1; i < n; i++)
        cout << E << "\n";
    return 0;
}
```

---

## 作者：rui_er (赞：7)

本题解是 Max of Distance 的官方题解。

本题是一道十分自由的构造题，解法可能有很多，本题解中将介绍笔者已知的最简单的一种，也是命题时笔者给出的命题人解法。

在确定每条边的边权之前，统计每条边对 $E$ 的贡献是十分困难的，因为我们无从得知每条边被有效经过了多少次。因此，我们想到让绝大多数边对 $E$ 没有贡献。

先随便找到一个叶子结点 $p$，设与 $p$ 直接相连的点为 $q$。将所有 $n-2$ 条不与 $p$ 直接相连的边赋权值 $998244353$，之后只需要考虑 $p,q$ 之间的那条边的权值对 $E$ 的贡献。显然，这条边的权值在 $[1,998244353]$ 之间取就足够了。

设去掉点 $p$ 之后得到的 $n-1$ 点的树的直径两端为 $s,t$，则由直径的性质可知，对于每个不是 $p$ 的结点 $u$，使得 $\operatorname{dis}(u,v)$ 取到最大值的结点 $v$ 只可能是 $s,t,p$ 三者之一，且是 $p$ 的充要条件是 $\operatorname{dis}(u,q)=\max\{\operatorname{dis}(u,s),\operatorname{dis}(u,t)\}$。显然，从 $p$ 出发到使得 $\operatorname{dis}(p,v)$ 取到最大值的结点 $v$ 结束的路径一定经过了 $(p,q)$ 这条边。设根据上述性质统计出的边 $(p,q)$ 的经过次数为 $cnt$，则有 $\frac{cnt}{n}w(p,q)=E$，即 $w(p,q)=\frac{n}{cnt}E$。显然，$cnt\in[1,n]$，因此 ${cnt}^{-1}$ 必定存在且唯一。

时间复杂度 $O(n\log n)$。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(int x = (y); x <= (z); ++x)
#define per(x, y, z) for(int x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

template<int mod>
inline unsigned int down(unsigned int x) {
	return x >= mod ? x - mod : x;
}

template<int mod>
struct Modint {
	unsigned int x;
	Modint() = default;
	Modint(unsigned int x) : x(x) {}
	friend istream& operator>>(istream& in, Modint& a) {return in >> a.x;}
	friend ostream& operator<<(ostream& out, Modint a) {return out << a.x;}
	friend Modint operator+(Modint a, Modint b) {return down<mod>(a.x + b.x);}
	friend Modint operator-(Modint a, Modint b) {return down<mod>(a.x - b.x + mod);}
	friend Modint operator*(Modint a, Modint b) {return 1ULL * a.x * b.x % mod;}
	friend Modint operator/(Modint a, Modint b) {return a * ~b;}
	friend Modint operator^(Modint a, int b) {Modint ans = 1; for(; b; b >>= 1, a *= a) if(b & 1) ans *= a; return ans;}
	friend Modint operator~(Modint a) {return a ^ (mod - 2);}
	friend Modint operator-(Modint a) {return down<mod>(mod - a.x);}
	friend Modint& operator+=(Modint& a, Modint b) {return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b) {return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b) {return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b) {return a = a / b;}
	friend Modint& operator^=(Modint& a, int b) {return a = a ^ b;}
	friend Modint& operator++(Modint& a) {return a += 1;}
	friend Modint operator++(Modint& a, int) {Modint x = a; a += 1; return x;}
	friend Modint& operator--(Modint& a) {return a -= 1;}
	friend Modint operator--(Modint& a, int) {Modint x = a; a -= 1; return x;}
	friend bool operator==(Modint a, Modint b) {return a.x == b.x;}
	friend bool operator!=(Modint a, Modint b) {return !(a == b);}
};

typedef Modint<998244353> mint;

const int N = 1e5 + 5;

int n, deg[N], leaf, dis[N], fa[N], sz[N], son[N], top[N], d[N];
mint E;
vector<int> e[N];
vector<tuple<int, int>> G;

void dfs1(int u) {
    dis[u] = dis[fa[u]] + 1;
    sz[u] = 1;
    for(int v : e[u]) {
        if(v != fa[u]) {
            fa[v] = u;
            dfs1(v);
            sz[u] += sz[v];
            if(sz[v] > sz[son[u]]) son[u] = v;
        }
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    if(!son[u]) return;
    dfs2(son[u], tp);
    for(int v : e[u]) {
        if(v != fa[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}

inline int LCA(int u, int v) {
    while(top[u] != top[v]) {
        if(dis[top[u]] < dis[top[v]]) v = fa[top[v]];
        else u = fa[top[u]];
    }
    return dis[u] < dis[v] ? u : v;
}

inline int distance(int u, int v) {
    int p = LCA(u, v);
    return dis[u] + dis[v] - 2 * dis[p];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n - 1) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
        G.emplace_back(u, v);
        ++deg[u]; ++deg[v];
    }
    cin >> E;
    if(E == 0) {
        rep(i, 1, n - 1) cout << 998244353 << endl;
        return 0;
    }
    per(i, n, 1) {
        if(deg[i] == 1) {
            leaf = i;
            break;
        }
    }
    dfs1(1);
    dfs2(1, 1);
    int diam1 = 1, diam2 = 1;
    rep(i, 1, n) {
        if(i != leaf && dis[i] > dis[diam1]) {
            diam1 = i;
        }
    }
    rep(i, 1, n) {
        if(i != leaf && distance(diam1, i) > distance(diam1, diam2)) {
            diam2 = i;
        }
    }
    int cnt = 0;
    rep(i, 1, n) {
        if(i == leaf) ++cnt;
        else {
            int d1 = distance(i, diam1), d2 = distance(i, diam2);
            int d0 = distance(i, fa[leaf]);
            if(max(d1, d2) == d0) ++cnt;
        }
    }
    for(auto [u, v] : G) {
        if(u == leaf || v == leaf) cout << (E * n / cnt) << endl;
        else cout << 998244353 << endl;
    }
    return 0;
}
```

---

## 作者：FFTotoro (赞：6)

数据人 & 验题人题解。~~说句闲话：当时搞这个题的时候我还把出题人 std 叉了，还好只是一个细节。~~

前置知识：树的直径的性质，期望的定义。

令 $P=998244353$，定义 $M(x)=\begin{cases}P&x\equiv0\pmod P\\x\bmod P&x\not\equiv 0\pmod P\end{cases}$，因为要满足边权为**正整数**。

首先把“期望” $E=\dfrac{\sum\limits_{i=1}^n\max\limits_{j=1}^n\mathrm{dis}(i,j)}{n}$ 变为 $En=\sum\limits_{i=1}^n\max\limits_{j=1}^n\mathrm{dis}(i,j)$。

考虑对于一个结点，距离它最远的结点应该是什么。根据树的直径的性质，距离其最远的结点必为树直径的一个端点（不管有没有边权）。

当给定的树是一条链时，我们把所有贡献挂在一条边上：比较简单的方法是令 $u$ 为链的一个端点，把贡献挂在 $u$ 连出去的唯一一条边 $e$ 上，也就是说其他的所有边的边权都设为 $P$。考虑此时 $e$ 的边权应该设为多少（为方便我们使这个边权 $\le P$），即考虑有多少个结点满足离它最远的结点是 $e$：通过对 $n$ 的奇偶分类讨论，一共有 $m=\left\lfloor\dfrac{n}{2}\right\rfloor$ 个结点满足条件；所以将 $e$ 的边权设为 $M\left(\dfrac{En}{m+1}\right)$（$+1$ 是因为 $u$ 也能产生贡献）即可。

当给定的树不是一条链时，有一个比较显然的想法：先假设所有边都没有边权（即将全部边权视为 $1$），这次把所有的贡献都挂在一个不在直径上的叶子结点 $u$ 上（因为不是链所以一定有这样的结点），其他结点贡献全部为 $0$。如何做到这一点？将 $u$ 的唯一出边的边权设为 $M(En)$，其他边的边权设为 $P$。因为 $M(En)\le P$，所以不考虑边权的直径与这么构造后的直径是一样的；这样只有 $u$ 的贡献为 $M(En)$，其他结点的贡献都为 $0$（因为距离其他结点最远的点一定不是 $u$ 而是直径的一个端点）。

参考代码（C++17）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
const int p=998244353;
int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)(r*=a)%=p;
    (a*=a)%=p,b>>=1;
  }
  return r;
} // 快速幂，用于求逆元
main(){
  ios::sync_with_stdio(false);
  int n; cin>>n;
  vector<pii> t(n-1);
  vector<vector<int> > g(n);
  vector<int> d(n);
  for(auto &[u,v]:t){
    cin>>u>>v,d[--u]++,d[--v]++;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  int e; cin>>e;
  if(*max_element(d.begin(),d.end())<=2){
    int x=e*n%p*qpow((n>>1)+1,p-2)%p; // 特殊边的边权
    bool w=false;
    if(!x)x=p; // 注意特判 x 为 0 的情况
    for(auto [u,v]:t){
      if(min(d[u],d[v])==1&&!w)w=true,cout<<x<<'\n'; // 一个端点
      else cout<<p<<'\n';
    }
  } // 链的情况
  else{
    vector<int> s(n),f(n);
    function<void(int,int)> dfs=[&](int u,int r){
      s[u]=s[f[u]=r]+1;
      for(int i:g[u])
        if(i!=r)dfs(i,u);
    }; // 使用贪心找直径
    dfs(0,0);
    int p1=max_element(s.begin(),s.end())-s.begin();
    fill(s.begin(),s.end(),0),dfs(p1,p1);
    int p2=max_element(s.begin(),s.end())-s.begin();
    vector<bool> b(n); b[p1]=true;
    while(f[p2]!=p1)b[p2]=true,p2=f[p2]; // 标记直径上的点
    bool w=false;
    if((e*=n)%=p;!e)e=p; // 特殊的边的边权
    for(auto &[u,v]:t){
      if(d[u]>d[v])swap(u,v);
      if(d[u]==1&&!b[u]&&!w)w=true,cout<<e<<'\n'; // 找到目标结点
      else cout<<p<<'\n';
    }
  } // 非链的情况
  return 0;
}
```

---

## 作者：wsinb (赞：6)

[题面](https://www.luogu.com.cn/problem/T407490?contestId=162523)

前言：

做法与官方做法不同。

赛时题解，打月赛打到一半破防了。出题人是会造数据的。

注意这题边权不能为 $0$。所以一开始想到的【仅有一条边边权为正】的思路假了。

（update：看到官方题解之后才猛然意识到可以把 $0$ 替换为 $998244353$！我是小丑。）

然后思考怎么人类智慧。以下策略我也不知道当时怎么想到的。

---

如果不考虑 $E$ 的限制，将一开始每条边边权都设置为 $1$，显然题目中描述的 $v$ 一定为原树直径两端点之一。找到这两个端点（设它们分别为 $p,q$），再记录一个变量 $sum$，其定义为：

$$sum=\bigg(\sum_{i=1}^n \max\{dis(i,p),dis(i,q)\}\bigg) \bmod 998244353$$

默认大家都会实现 $dis$。

现在，如果把边权从 $1$ 改为 $k$，使得新的树符合 $E$ 的限制，那么有：

$$k\times \frac{sum}{n} \equiv E \pmod {998244353}$$

即：

$$k\equiv E \times \frac{n}{sum} \pmod {998244353}$$


当时我想，只要求出 $k$ 的值就做完了。

然后痛失 $5\%$ 的分数。因为这样做会有一些细节问题：

> 如果 $E=0$，那么求出来的 $k$ 就都是 $0$ 了。

这个好办，特判 $E=0$ 的情况，这个时候令 $k=998244353$ 就好了。（为什么我这个时候想到了把 $0$ 替换为 $998244353$ 啊啊啊）

> 如果 $sum=0$，那么除以 $sum$ 的时候就相当于除以 $0$ 了。

此时每条边边权仍相等的做法就行不通了（因为无论怎么改 $k$ 都无法改变 $sum$）。于是改进原做法。

还记得之前所定义的直径两端点 $p,q$ 么？既然 $p,q$ 的度数均为 $1$，我们把直接与 $p$、$q$ 相连的两条边的边权增加一个值 $h$。$h$ 的大小暂时未知。

想想这样做之后新的 $sum$ 会变成什么。对于 $p,q$ 两点，$\max dis(p,v)$ 和 $\max dis(q,v)$ 会增加 $2h$；对于剩下的点 $x$，$\max dis(x,v)$ 会增加 $h$。所以 $sum$ 会增加 $(n+2)h$。

因为 $k$ 怎么变，$sum $ 的值都不会再变了。所以我们索性将 $k$ 设置为 $1$。

所以现在的 $h$ 满足：

$$h\equiv E \times \frac{n}{n+2} \pmod {998244353}$$

求出 $h$ 之后，最后的效果就是：除了直径最末端两条边边权为 $h+1$，其它边边权均为 $1$。

代码太丑，就不贴了。

满分 $1500$，喜提 $842$。

---

## 作者：diqiuyi (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P10309)。

神秘构造。

首先把期望距离乘 $n$，这样就把问题转化为了距离总和。

我们考虑钦定一个点，使得从其他所有点出发的最长路径都以它为中点。为了方便，我们取一个度数为 $1$ 的点。这样只需要把和它相连的边权赋为 $10^9$，其他边权都赋为 $1$ 就可以了。不妨记这个点为 $R$。

但这样无法保证答案为 $E$。所以我们不妨找到在现有的树上离 $R$ 最远的一个点 $U$。那么我们只要调整 $U$ 和其父亲的连边的边权即可。但是注意调整边权对答案的变化量是个偶数，所以无法改变答案的奇偶。

不过我们发现边权 $w$ 的最大值大于 $998244353$，而 $998244353$ 是个奇数，所以如果需要调整的量是个奇数，那把它加上 $998244353$ 就行了。

考虑正确性。由于 $10^9-998244353$ 远大于 $n$，所以除了 $R$ 以外的点的最远距离是不会出错的。而由于 $U$ 在和父亲距离为 $1$ 时已经是离 $R$ 最远的点了，所以调整后它依然是离 $R$ 最远的点。

时间复杂度为 $O(n)$。

**CODE**
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define uint unsigned int
#define pii pair<int,int>
using namespace std;
inline int read(){
	int x=0;bool f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f?x:-x;
}
const int mod=998244353;
int n,u,v,root,leaf,deg[100005],w[100005],fid[100005],dis[100005];
ll e,sumr;
vector<pair<int,int> > g[100005];
void dfs(int x,int fa){
	if(dis[x]>dis[leaf]) leaf=x;
	for(int i=0;i<g[x].size();i++)
		if(g[x][i].first^fa){
			fid[g[x][i].first]=g[x][i].second;
			if(!w[g[x][i].second]) w[g[x][i].second]=1;
			dis[g[x][i].first]=dis[x]+w[g[x][i].second];
			dfs(g[x][i].first,x);
		}
}
int main(){
	n=read();
	for(int i=1;i<n;i++)
		u=read(),v=read(),g[u].push_back(make_pair(v,i)),g[v].push_back(make_pair(u,i));
	e=read();
	e=e*n;
	if(n==2){
		if(!e) e+=mod*2;
		printf("%lld\n",e>>1);
		return 0;
	}//注意特别考虑 n=2 的情况，因为我们是把边权当作 1 来调整的
	for(int i=1;i<=n;i++)
		if(g[i].size()==1)
			root=i;
	w[g[root][0].second]=1000000000;
	dfs(root,0);
	for(int i=1;i<=n;i++) sumr+=dis[i];
	sumr+=dis[leaf];
	int ad=((e-sumr)%mod+mod)%mod;
	if(ad&1) w[fid[leaf]]+=(ad+mod)/2;
	else w[fid[leaf]]+=ad/2;
	for(int i=1;i<n;i++)
		printf("%d\n",w[i]);
//	cout<<(496488710ll*2+1000000000ll*3)%mod<<' '<<e%mod<<endl;
    return 0;
}
```

---

## 作者：tobie (赞：2)

首先我们发现期望可以转化为对于每个 $u$ 的最远点距离求和。这个东西不好做，考虑简化条件。

你看这个 $n\le 10^9$，而 $10^9>998244353$，所以我们可以找到一个出度为 $1$ 的点 $u$ 作为根节点，将它连出去的边权设为 $x$，其他边设为 $998244353$，那么距离和可以表示为 $kx$ 的形式，我们现在只要求出有多少个点能到达的最远点为 $u$ 即可。

我们令 $u$ 唯一的出边连向了 $v$，**接下来我们暂时忽略**点 $u$，考虑求出每个点最远能走出多少条边。

套路地考虑 dp。令 $f_x$ 表示 $x$ 往子树内走的最远距离，$g_x$ 表示往 $x$ 子树外走的最远距离，那么有：

$$f_u=1+\max f_v$$
$$g_v=\max(g_u+1,\max_{x\in son_u\wedge x\ne v}(f_x)+2)$$

可以使用换根 dp 解决。计算 $g$ 时可以使用前后缀优化做到线性。

那么如果说 $\max(f_i,g_i)=\operatorname{dis}(v,i)$，那么 $i$ 出发的最长路径就一定会经过边 $(u,v)$，需要统计到 $k$ 中。

最后只需要计算 $kx=nE$，算个逆元就可以了。

总时间复杂度为 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<vector> 
using namespace std;
const int N=100009,mod=998244353;
#define int long long
int n,ru[N],u[N],v[N],E;
vector<int> to[N];
int f[N],g[N],dep[N];
int rt;
void dfs1(int now,int fa)
{
	f[now]=0;dep[now]=dep[fa]+1;
	for(int v:to[now])
	{
		if(v==fa||v==rt) continue;
		dfs1(v,now);
		f[now]=max(f[now],f[v]+1);
	}
}
int qz[N],hz[N];
int getnum(int x,int fa_){return x==fa_||x==rt?-2:f[x];}
void dfs2(int now,int fa)
{
	if(to[now].size()==1) return;
	qz[0]=getnum(to[now][0],fa);
	for(int i=1;i<to[now].size();i++) qz[i]=max(qz[i-1],getnum(to[now][i],fa));
	hz[to[now].size()-1]=getnum(to[now][to[now].size()-1],fa);
	for(int i=to[now].size()-2;i>=0;i--) hz[i]=max(hz[i+1],getnum(to[now][i],fa));
	for(int i=0;i<to[now].size();i++)
	{
		int v=to[now][i];
		if(v==fa||v==rt) continue;
		g[v]=max(g[now]+1,max(i==0?-2:qz[i-1],i==to[now].size()-1?-2:hz[i+1])+2);
	}
	for(int i=0;i<to[now].size();i++)
	{
		int v=to[now][i];
		if(v==fa||v==rt) continue;
		dfs2(v,now);
	}
}
int ksm(int x,int y){int res=1;for(;y;x=x*x%mod,y>>=1) if(y&1) res=res*x%mod;return res;}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<n;i++) scanf("%lld%lld",&u[i],&v[i]),ru[u[i]]++,ru[v[i]]++;
	for(int i=1;i<n;i++) to[u[i]].push_back(v[i]),to[v[i]].push_back(u[i]);
	scanf("%lld",&E);
	E=E*n%mod;
	for(int i=1;i<=n;i++)
	if(ru[i]==1)
	{
		rt=i;
		dfs1(to[i][0],0);
		dfs2(to[i][0],0);
		break;
	}
	int cnt=1;
	for(int i=1;i<=n;i++)
	if(i!=rt&&max(g[i],f[i])==dep[i]-1) cnt++;
	E=E*ksm(cnt,mod-2)%mod;
	if(E==0) E=mod;
	for(int i=1;i<n;i++)
	if(u[i]==rt||v[i]==rt) printf("%lld\n",E);
	else printf("%lld\n",mod);
}
```

---

## 作者：dspt (赞：1)

赛时这题写了好久啊，一直被最后两个点卡了，导致分数和 rank 极低。

&nbsp;

## 显然做法

显然我们可以钦定每条边权值相同，设为 $w$。先令边权均为 1，做换根 DP 易得距离每个点的 maxdis，设将 $n$ 的点的 maxdis 求和的结果为 $x$。那么 $wx=kn\bmod p$。

边界情况：若 $k=0$，则 $w=p$。否则答案就是 $w=\frac{kn}x\bmod p$。

于是很容易写了一发，最后两个点没过。

&nbsp;

## 边界修正

好好好，聪明的出题人直接卡了这种做法。为什么会被卡？因为出题人构造出了一棵树使 $x=p$，这样分式就被卡了。

容易发现我们一开始不必钦定边权为 1，如果我们钦定的边权在 1 / 2 之间等概率选择，这样可以让 $x$ 是随机的，基本不会被卡。求出对应的 $w$ 之后，如果初始边权为 1，则真实边权为 $w$；否则边权为 $2w$。正确性显然，但是我们需要保证 $2w\leqslant 10^9$，容易发现 $0\leqslant w<p$，随机常数次就可以得到一个可行的答案。

&nbsp;

时间复杂度 $O(n)$，好像爆标了，代码太丑了就不放了。

---

## 作者：SunsetGlow95 (赞：1)

# 题解 - P10309 「Cfz Round 2」Max of Distance

## 简述题意

给定一棵包含 $n$ 个结点的树和一个整数 $E$。构造树中每条边的整数边权 $w_i(1\le w_i\le 10^9)$，满足均匀随机选择一个结点 $u$，$\max\limits_{v=1}^n\operatorname{dis}(u,v)$ 的期望对 $998244353$ 取模的值等于 $E$；或报告无解。$2\le n\le 10^5$，$1 \le u_i,v_i \le n$，$0\le E < 998244353$。

## 分析

我们发现题目中的关键点既有 $\max$，又有期望，还有取模。就可以猜这个 $\max$ 是这其中关键要着手的。

一般地，树上的 $\max\limits_{v=1}^n\operatorname{dis}(u,v)$ 取到的 $v$ 是一个直径的端点，是一个叶子；那么，我们就直接钦定一个 $v$，让其他点都是到 $v$ 最远，而 $v$ 走直径就可以了。

具体的办法就是，随便选一个叶子 $v$，把与 $v$ 相连的唯一一条边设定一个 $\ge n$ 的权值，而其他的边权都设为 $1$。接下来只需要求出这个权值 $w$。

由题意，我们有 $w+\frac{1}{n}(\max_{u\neq v} d_u + \sum_{u\neq v} d_u)\equiv E\pmod {998244353}$，其中 $d_u$ 表示以 $v$ 为根，$u$ 点的深度 $-1$。

$d$ 可以直接通过 dfs 求出来，那么 $w$ 也就容易得到了。

最后为了确认满足这条边必走，如果 $w<n$，就让 $w$ 加上 $998244353$，这样也不会超出 $10^9$。

由以上的构造，可以发现恒有解。

时间复杂度 $O(n+\log V)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MXN = 100005;
const int DVS = 998244353;
int N, deg[MXN], eid[MXN], E, spid, mxd, diff;
vector<int> to[MXN];

void dfs(int p, int f, int d) {
  mxd = max(mxd, d);
  if (f != -1) diff = (diff + d - 1) % DVS;
  for (int q : to[p]) {
    if (q == f) continue;
    dfs(q, p, d + 1);
  }
}
int inv(int x) {
  int p(DVS - 2), a(1);
  while (p) {
    if (p & 1) a = a * 1LL * x % DVS;
    x = x * 1LL * x % DVS;
    p >>= 1;
  }
  return a;
}

int main() {
  cin >> N;
  for (int i(1), x(0), y(0); i != N; ++i) {
    cin >> x >> y;
    --x, --y;
    ++deg[x], ++deg[y];
    eid[x] = eid[y] = i;
    to[x].push_back(y);
    to[y].push_back(x);
  }
  cin >> E;
  for (int i(0); i != N; ++i) {
    if (deg[i] != 1) continue;
    spid = eid[i];
    dfs(i, -1, 0);
    diff = (diff + mxd - 1) % DVS;
    break;
  }
  diff = diff * 1LL * inv(N) % DVS;
  E = (E - diff + DVS) % DVS;
  if (E < N) E += DVS;
  for (int i(1); i != N; ++i) {
    if (i == spid) cout << E << endl;
    else cout << '1' << endl;
  }
  return 0;
}
```

---

## 作者：operator_ (赞：1)

# P10309 「Cfz Round 2」Max of Distance

[题目传送门](https://www.luogu.com.cn/problem/solution/P10309)

## 题解

随便钦定一个叶子 $u$ 当根，把除了这个叶子的对应边以外的边权全部赋 $1$，这条边赋 $w$。显然可以调整 $w$ 使 $w>n$，所以先随便钦定一个 $w$，此时所有点的答案都经过 $u$，其答案 $E'$ 直接 dfs 即可容易统计。然后由于所有点都有 $w$ 的贡献，所以 $\Delta w$ 是直接贡献在期望里的，我们令 $\Delta w=E-E'$ 即可。最后不要忘记调整一下最终的 $w'$ 使其满足限制。

这种做法的核心是 $998244353+n<10^9$。

为方便，代码钦定最初的 $w$ 也为 $1$。

```cpp
/*
 * @Author: operator_ 
 * @Date: 2024-04-05 16:33:39 
 * @Last Modified by: operator_
 * @Last Modified time: 2024-04-05 17:22:33
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
const int M=998244353;
#define FORGRAPH for(int i=h[u],v;v=e[i].v;i=e[i].nxt)
int n,E,E2,w,x,Mx,deg[100005],u[100005],v[100005],h[100005],cnt,d[100005];
struct QWQ{int v,nxt;} e[100005*2];
void add(int u,int v) {e[++cnt]={v,h[u]},h[u]=cnt;}
int qpow(int x) {int s=1;for(int y=M-2;y;y>>=1,x=x*x%M)if(y&1) s=s*x%M;return s;}
void dfs(int u,int p) {d[u]=d[p]+1;FORGRAPH if(v!=p) dfs(v,u);}
signed main(){
    cin>>n;d[0]=-1;
    for(int i=1;i<n;i++) deg[u[i]=rd()]++,deg[v[i]=rd()]++,add(u[i],v[i]),add(v[i],u[i]);
    cin>>E;
    for(int i=1;i<=n;i++) if(deg[i]==1) x=i;
    dfs(x,0);for(int i=1;i<=n;i++) E2=(E2+d[i])%M,Mx=max(Mx,d[i]);
    E2=(E2+Mx)*qpow(n)%M;w=(E-E2+M)%M+1;if(w<=n) w+=M;
    for(int i=1;i<n;i++) printf("%lld\n",(u[i]==x||v[i]==x)?w:1ll);
    return 0;
}
```

---

## 作者：aulive (赞：1)

## 题目分析
首先，题目给定了期望值，那么我们可以直接求出 $\max\limits_{v=1}^n\operatorname{dis}(u,v)$ 的总和

确定期望值 $E$ 是困难的，但是如果我们可以钦定一条连接叶子结点的边 $S$，使得其他点选取离自己最远的点时必然经过 $S$，这样问题将会简单很多。

接着考虑如何让边 $S$ 会被强制经过，那么我们就会有一个很显然的想法：\
将其他 $n-2$ 条边都置为 $1$，这样只要让 $S$ 的边权大于 $n$ 就可以保证边 $S$ 会被强制经过。

令边 $S$ 的值为 $val$，点 $i$ 到该叶子节点的距离为 $\operatorname{dept}_i$

那么若 $u$ 不为叶子节点，$\max\limits_{v=1}^n\operatorname{dis}(u,v)$ 为
 $\operatorname{dept}_i-1+val$。\
若 $u$ 为叶子节点，$\max\limits_{v=1}^n\operatorname{dis}(u,v)$ 为$\operatorname{dept}_i-1+val$的最大值。

这样我们就可以求出 $val$ 值，再特判一下 $val\le n$的情况就可以了。
## code
构造思路讲完了，剩下的就看代码了。\
时间复杂度 $O(n)$。
```cpp
/*
        ____  
   .-'&     '-.
  /            \
 :    ⊙   ⊙    ;
(       (_       )
 :              ;
  \     __     /
   `-.______.-'
     / `"""`\
    /     ,  \
   /|/\/\/\  _\ 
  (_|/\/\/\\ __)
    |_______|
   __)_ |_ (__
  (_____|_____)
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=1e5;
const ll inf=1e9;
const ll mod=998244353;
ll a[maxn+5];
ll n;
struct Edge{
	ll u,v;
}edge[maxn+5];
ll sum;
ll du[maxn+5];
ll ksm(ll x,ll y){
	if(!y)return 1;
	ll fw=ksm(x,y>>1);
	if(y&1)return fw*fw%mod*x%mod;
	return fw*fw%mod;
}
ll inv(ll x){
	return ksm(x,mod-2);
}
ll dept[maxn+5];
vector <ll> rood[maxn+5];
void dfs(ll now,ll fa){
	dept[now]=dept[fa]+1;
	for(ll to:rood[now]){
		if(to==fa)continue;
		dfs(to,now);
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(ll i=1;i<n;i++){
		cin>>edge[i].u>>edge[i].v;
		rood[edge[i].u].push_back(edge[i].v);
		rood[edge[i].v].push_back(edge[i].u);
		du[edge[i].u]++;
		du[edge[i].v]++;
	}
	cin>>sum;
	sum=sum*n%mod;
	ll root=0;
	for(ll i=1;i<=n;i++){
		if(du[i]==1){
			root=i;
			break;
		}
	}
	dfs(root,0);
	ll maxx=0;
	ll dept_sum=0;
	for(ll i=1;i<=n;i++){
		if(i==root)continue;
		dept_sum+=dept[i]-2;
		maxx=max(maxx,dept[i]-2);
	}
	sum-=dept_sum+maxx;
	sum=(sum%mod+mod)%mod;
	ll ans=sum*inv(n)%mod;
	if(ans<=n)ans+=mod;
	for(ll i=1;i<n;i++){
		if(edge[i].u==root||edge[i].v==root){
			cout<<ans<<"\n";
		}else{
			cout<<1<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：是青白呀 (赞：0)

首先把期望除掉的那个 $n$ 乘到对面去，也即 $\sum_u \max_v dis(u,v)=n\times E$。由于最后的答案均需要模 $998244353$，我们考虑将其中 $n-2$ 条边的边权都设成 $998244353$，这样大部分边无论被几个点的最长路径经过，都不影响答案。我们只需调整最后那条边的边权使得其满足答案要求即可。

为了方便调整，我们希望最后那条边被最少的最长路径经过。下面分两类情况讨论：

1. 当存在一个点 $x$ 的度数不小于 $3$ 时，我们以 $x$ 为根遍历这棵树，找到深度最小的叶子节点 $y$，则 $y$ 一定不在直径上（可以走到 $x$ 处，选择叶子结点更深的子树往下走，得到的链会更长）。于是，$y$ 的父亲边只会在 $\max_v dis(y,v)$ 处被计入答案 $1$ 次。我们直接把 $y$ 父亲边的边权设为 $n\times E\bmod 998244353$ 即可。

2. 当所有点的度数均小于 $3$ 时，给出的是一条链。我们选择任意一个端点 $x$，修改与 $x$ 相连的那条边的边权。由于我们会把边权改得比 $998244353$ 小，所以不难发现覆盖了与 $x$ 相连的那条边的最长路径数为 $\lfloor\frac n2\rfloor+1$。假设边权为 $y$，则有 $(\lfloor\frac n2\rfloor+1)y \equiv n\times E \pmod{998244353}$。用 exgcd 求解这个同余方程即可。

### Code
```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define lowbit(x) x&(-x)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second 
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=1e5+5,M=(1<<20)+2,mo=998244353,inf=1e9+7,bs=19491001;
const double eps=1e-8;
inline void read(int &p){
	int x=0,w=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n;
struct edge{
	int to,nxt;
}e[2*N];
int fir[N],np;
struct lk{
	int x,y;
}ed[N];
void add(int x,int y){
	e[++np]=(edge){y,fir[x]};
	fir[x]=np;
}
int deg[N],dep[N],rt,m,ans[N];
void exgcd(int &x,int &y,int a,int b){
	if(!b){
		x=1,y=0;
		return;
	}
	int x2=0,y2=0;
	exgcd(x2,y2,b,a%b);
	x=y2,y=x2-a/b*y2;
}
int minn=inf,minid;
void dfs(int x,int f){
	bool lv=1;
	dep[x]=dep[f]+1;
	for(int i=fir[x];i;i=e[i].nxt){
		int j=e[i].to;
		if(j==f)continue;
		lv=0,dfs(j,x);
	}
	if(lv&&dep[x]<minn)minn=dep[x],minid=x;
}
signed main(){
	read(n);
	rep(i,1,n-1){
		int x,y;
		read(x),read(y);
		add(x,y),add(y,x),deg[x]++,deg[y]++;
		ed[i].x=x,ed[i].y=y;
	}
	rep(i,1,n)
	    if(deg[i]>deg[rt])rt=i;
	read(m),m=m*n%mo;
	if(deg[rt]<3){
		rep(i,1,n-1){
			int x=ed[i].x,y=ed[i].y;
			if(deg[x]==2&&deg[y]==2)continue;
			int num=n/2+1;
			int x1=0,y1=0;
			exgcd(x1,y1,mo,num);
			y1=(y1*m%mo+mo)%mo;
			ans[i]=y1;
			break;
		}
		rep(i,1,n-1){
			if(!ans[i])printf("%lld\n",mo);
			else printf("%lld\n",ans[i]);
		}
		return 0;
	}
	
	dfs(rt,0);
	rep(i,1,n-1)
	    if(ed[i].x==minid||ed[i].y==minid)ans[i]=m;
	rep(i,1,n-1){
		if(!ans[i])printf("%lld\n",mo);
		else printf("%lld\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

这道题是简单的，个人认为可以评黄。

看到题可以先考虑完成题目要完成的问题：随机选一个点求这个点到其它点最长路径的期望，我们做的时候显然是所有点最长路径的和除以 $n$，因此我们可以先将 $E$ 乘 $n$。

此时，我们发现答案是难以维护的，因为我们无法琢磨每个点的最长路径所最终到达的点，不过能确定的是，**这个节点一定是叶子**。

因此我们要固定节点。

显然，如果要固定一个节点，我们可以让能且只能（不考虑这个点到其他点经过这条边）到达这个点的唯一边变得变得极大。

为了让别的边的和无法跟这个边比，可以到设为 $1$，然后由于所有节点的最长路径都要经过这条边，因此可以简单的求出这条边对 $998244353$ 取模后的值。

当然，有时这个值可能很小，这是我们可以让这个值加上 $998244353$，这样就大了，假设这个值加上 $998244353$ 会超过 $10^9$，此时这个值大于 $10^6$，大于其它边的值，因此可行。

那么代码就出炉啦！

时间复杂度 $\Theta(n)$，~~爆标~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int ans;
struct st{
	int v,ne,tt;
}sd[200009];
int h[100009];
int inn;
int ds[100009];
void add(int u,int v){
	sd[++inn].v=v;
	sd[inn].ne=h[u];
	sd[inn].tt=(inn+1)/2;
	h[u]=inn;
}
int dfs(int t,int fa,int le){//用 le 计算到达选定节点经过的边权为 1 的边的数量，即和选定叶子节点相连的节点的距离，ans 求和。
	ans+=le;
	int zz;
	zz=le;
	for(int i=h[t];i;i=sd[i].ne){
		if(sd[i].v!=fa){
			zz=max(zz,dfs(sd[i].v,t,le+1));
		}
	}
	return zz;//我们要计算选定节点到其他节点的最长距离所经过的边权为 1 的边的数量，设这个节点为根，还是与这个节点相连的节点到其他非选定节点的最长距离，返回值便是以当前节点为根的最长距离
}
int ny(int a){//计算 a 的逆元
	int b;
	b=mod-2;
	int ans;
	ans=1;
	while(b){
		if(b&1){
			ans*=a;
			ans%=mod;
		}
		a*=a;
		a%=mod;
		b>>=1;
	}
	return ans;
}
void _main(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
		ds[u]++;//方便求叶子，计算度数
		ds[v]++;
	}
	int e;
	cin>>e;
	e*=n;
	e%=mod;
	for(int i=1;i<=n;i++){
		if(ds[i]==1){
			int ss;
			ss=dfs(sd[h[i]].v,i,0);
			ans+=ss;
			ans%=mod;
			e-=ans;
			e+=mod;
			e%=mod;//nx=e
			e*=ny(n);
			e%=mod;
			if(e+mod<=1e9){//扩大
				e+=mod;
			}
			int xx;
			xx=sd[h[i]].tt;//记录边的编号
			for(int i=1;i<n;i++){
				if(i!=xx){
					cout<<1<<endl;
				}else{
					cout<<e<<endl;
				}
			}
			break;
		}
	}
}
signed main(){
	int t;
	//cin>>t;
	t=1;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：WaTleZero_pt (赞：0)

本体构造的方法很多，这里介绍我比赛时用的思路。

### 思路分析

首先选取任意一条连接叶子结点的边 $(u,v)$ （$u$ 为叶子节点），稍后我们会将其赋上一个非常大的权值。接下来我们将其他的边权值全部赋值为 $1$。显然除了 $u$ 以外，其他节点的最长路径一定是通往 $u$ 的。而 $u$ 的最长路径即与 $u$ 间隔的节点数最多的路径。

如果我们临时令 $(u,v)$ 的权值也为 $1$，我们就可以将所有路径的和 $s$ 求出。接下来求出距离目标 $E$ 还差多少，运用逆元即可求出 $(u,v)$ 的权值还需要加多少，即可得出 $dis(u,v) \equiv \frac{En-s}{n}+1 \ (\operatorname{mod} 998244353)$。

如果加完后发现 $(u,v)$ 的值不足 $10^5$，再加上一个 $998244353$ 即可（一定不会超过 $10^9$ 对吧）。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll Mod=998244353;
ll ksm(ll x,ll y){
	ll ans=1;
	while(y){
		if(y&1) ans=ans*x%Mod;
		x=x*x%Mod; y>>=1; 
	}
	return ans;
}
ll ny(ll x){return ksm(x,Mod-2);}
int head[100010];
struct Node{
	int v,nxt;
}edge[200010];
int cntE=0;
void addedge(int u,int v){
	edge[++cntE].v=v;
	edge[cntE].nxt=head[u];
	head[u]=cntE;
}
bool isleaf[100010];
void dfs(int u,int fa){
	bool visited=0;
	for(int i=head[u];i;i=edge[i].nxt)
		if(fa!=edge[i].v) visited=1,dfs(edge[i].v,u);
	if(!visited) isleaf[u]=1;
}
int len[100010];
void dfs2(int u,int fa){
	for(int i=head[u];i;i=edge[i].nxt)
		if(fa!=edge[i].v){
			len[edge[i].v]=len[u]+1;
			dfs2(edge[i].v,u);
		}
}
int n,u[100010],v[100010];
ll e;
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u[i],&v[i]);
		addedge(u[i],v[i]);
		addedge(v[i],u[i]);
	}
	dfs(1,0);
	int root=0;
	for(int i=1;i<=n;i++) if(isleaf[i]){root=i;break;}
	dfs2(root,0);
	ll sumlen=0,mx=0;
	for(int i=1;i<=n;i++)
		if(i!=root) sumlen+=len[i],mx=max(mx,(ll)len[i]);
	sumlen+=mx; sumlen%=Mod;
	scanf("%lld",&e);
	e=e*n%Mod;
	e=(e-sumlen+Mod)%Mod;
	e=e*ny(n)%Mod;
	if(e<=100000) e+=Mod;
	for(int i=1;i<n;i++){
		if((u[i]==root&&v[i]==edge[head[root]].v)||(v[i]==root&&u[i]==edge[head[root]].v))
			printf("%lld\n",e+1);
		else printf("1\n");
	}
}
```

---

