# [ARC108F] Paint Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc108/tasks/arc108_f

$ 1 $ から $ N $ の番号がついた $ N $ 個の頂点と、$ 1 $ から $ N-1 $ の番号がついた $ N-1 $ 本の辺からなる木が与えられます。 辺 $ i $ は頂点 $ a_i $ と頂点 $ b_i $ を双方向につなぐ長さ $ 1 $ の辺です。

すぬけ君はそれぞれの頂点を白か黒のどちらかで塗ります。 塗り方の *良さ* は、白色の頂点同士の距離の最大値を $ X $、黒色の頂点同士の距離の最大値を $ Y $ として $ \max(X,Y) $ です。 ここで、その色の頂点が存在しない場合の距離の最大値は $ 0 $ とすることにします。

頂点への色の塗り方は $ 2^N $ 通りあります。それぞれの塗り方について良さを計算し、その総和を $ 10^{9}+7 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ N $
- 与えられるグラフは木

### Sample Explanation 1

\- 頂点 $ 1,2 $ の両方を同じ色で塗ったときの良さは $ 1 $ で、異なる色で塗ったときの良さは $ 0 $ です。 - 塗り方の良さの総和は $ 2 $ となります。

### Sample Explanation 3

\- $ 10^{9}+7 $ で割ったあまりを求めるのを忘れずに。

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
6
1 2
2 3
3 4
4 5
3 6```

### 输出

```
224```

## 样例 #3

### 输入

```
35
25 4
33 7
11 26
32 4
12 7
31 27
19 6
10 22
17 12
28 24
28 1
24 15
30 24
24 11
23 18
14 15
4 29
33 24
15 34
11 3
4 35
5 34
34 2
16 19
7 18
19 31
22 8
13 26
20 6
20 9
4 33
4 8
29 19
15 21```

### 输出

```
298219707```

# 题解

## 作者：Zelotz (赞：12)

本题有两种思路。

首先，对于普通的树，到一个点最远的点一定是直径的端点之一。记 $S$ 表示直径长度。

### 做法 $1$

先求出一条直径，若直径的两个端点颜色相同，则最长距离一定为直径。否则，令两个端点分别为 $x,y$，并钦定 $x,y$ 不同色。枚举答案 $d$，所有到 $x$ 距离 $>d$ 的点颜色必须与 $y$ 一样，所有到 $y$ 距离 $>d$ 的点颜色必须和 $x$ 一样。由于 $x, y$ 是直径的两个端点，可以发现，若一个点 $z$ 到 $x, y$ 的距离都不超过 $d$，则其到任何一个点的距离不超过 $d$，所以 $z$ 的颜色并不会对答案产生影响。

所以，定义 $cnt_i$ 表示到直径两端的距离不超过 $i$ 的点数。定义 $f_d$ 表示答案不超过 $d$ 的树的形态数，$g_d$ 表示答案为 $d$ 的树的形态数，$dis_{1/2}$ 表示从直径的两端点出发到其他点的距离。定义 $L=\max (\min(dis1_i,dis2_i))$。此处 $L$ 的意义为，在所有形态的树中，最小的答案（同色点对最大距离）。对于每个点取到直径两端点近的那个颜色即可。

最终的总权值为 $\sum\limits_{i=L}^S g_i\times i$。

容易得到 $f_d=2^{cnt_d}$。但是我们想要答案等于 $d$ 的树的形态数 $g_i$。很明显，只需要容斥减去 $f_{d-1}$ 即可，也就是 $g_d=f_d-f_{d-1}$。

注意 $x,y$ 共有 $2$ 种颜色分配方案。

### 做法 $2$

同样，先把答案化为 $\sum\limits d\times g_d$ 的形式，定义同上。

对于一个 $x$，我们记 $w(x)=\sum [d>x] f_d$。也就是答案大于 $x$ 的树的形态数。

则答案为 $\sum\limits_{i=0}^{S-1} w(i)$。此时，问题变为求 $w$。

定义 $L$，意义同上。

- 当 $i < L$ 时，$w(i)=2^n$。因为无论树长什么样子，答案都大于 $i$。
- 当 $i\ge L$ 时，进行容斥，$w(i)={2^n}$ 减去 $\sum [i\le x] g_i$，也就是减去最远点对 $\le x$ 的树的形态数，根据做法 $1$ 的推导，$\sum [i\le x]g_i=f_x=2^{cnt_{i}}$。

最后直径端点有两种分配方案。

两种方法殊途同归，实现上略有不同。代码中的 `solve1,solve2` 分别表示了两种方式的实现。

```
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define R(i, l, r) for (int i = (l); i <= (r); ++i)
#define int ll
const int N = 2e5 + 5, P = 1e9 + 7;
int n, dis1[N], dis2[N], pw[N] = {1}, cnt[N], ans;
vector <int> E[N];
void dfs(int x, int *dis, int fa)
{
    for (auto v : E[x])
    {
        if (v == fa) continue;
        dis[v] = dis[x] + 1;
        dfs(v, dis, x);
    }
}
int rt1 = -1, rt2 = -1;
void solve1()
{
    int t = 0;
    R(i, 1, n)
    {
        if (i == rt1 || i == rt2) continue;
        t = max(t, min(dis1[i], dis2[i]));
        cnt[max(dis1[i], dis2[i])]++;
    }
    R(i, 1, n) cnt[i] += cnt[i - 1];
    R(i, t, dis2[rt2])
    {
        ans += i * (pw[cnt[i]] - (i == t ? 0 : pw[cnt[i - 1]]) + P) % P;
        ans %= P;
    }
    (ans *= 2) %= P;
    (ans += dis2[rt2] * pw[n - 1] % P) %= P;
}
void solve2()
{
    int t = 0;
    R(i, 1, n)
    {
        t = max(t, min(dis1[i], dis2[i]));
        cnt[max(dis1[i], dis2[i])]++;
    }
    R(i, 1, n) cnt[i] += cnt[i - 1];
    R(i, 0, t - 1) (ans += pw[n]) %= P;
    R(i, t, dis2[rt2] - 1)
    {
        ans += (pw[n] - pw[cnt[i] + 1] + P) % P; // cnt[i]+1等于提前乘了最后的2
        ans %= P;
    }
}
signed main()
{
    cin >> n;
    R(i, 1, n) pw[i] = pw[i - 1] * 2 % P;
    R(i, 1, n - 1) 
    {
        int u, v; cin >> u >> v;
        E[u].push_back(v), E[v].push_back(u);
    }
    dfs(1, dis1, 0);
    R(i, 1, n) if (rt1 == -1 || dis1[i] > dis1[rt1]) rt1 = i;
    dfs(rt1, dis2, 0);
    R(i, 1, n) if (rt2 == -1 || dis2[i] > dis2[rt2]) rt2 = i;
    dis1[rt2] = 0;
    dfs(rt2, dis1, 0);
    // solve1,2 分别表示两种方式
    solve1(); 
    // solve2();
    cout << ans << endl;
    return 0;
}
```

---

## 作者：肖翔 (赞：6)

再来对 @Ishy 的题解进行一下诠释，说一说他跳了的转换，建议一起食用。

记每种方案的权值为 $val_{st}$，则答案即为所有 $val$ 之和。

直接不好做，考虑做一下变换。

我们枚举一个变量 $i \in [0,\infty] $，每当有一个 $val_{st} > i $，我们就令 $ans$ 自增。

显然，每个 $val_{st} $ 会使得 $ans$ 自增 $val_{st} $ 次，故这样操作完的 $ans $ 即为答案。

于是乎，我们弄清楚了他题解中的 $i$ 是什么。

我们所求即为$\sum_{i=0}^{\infty} [val_{st} \ge i \ ] $（方括号是艾弗森括号，表达式为真的时候值为 $1$，否则为 $0$）

------------
按照他的题解的方式定义 $d=\max(\min(dt_{u},ds_{u}))$。

我们发现上面的式子在 $i < d$ 时是非常好做的，就是 $2^n$（$val_{st}$ 一定大于 $i$）。


然而 $i \ge d$ 时并不好做，我们考虑单步容斥，用 $2^n$ 减去 $\sum [val_{st} \le i \ ] $ 

于是只需要解决一个问题，即 $\sum [val_{st} \le i \ ] $



------------
然后是他容斥时的分讨：

1. $dt_{u} >i $ 且 $ ds_{u}>i $，那么染色方案数为 $0$（一定不合法）

2. $dt_{u} \le i $ 且 $ ds_{u} \le i $，那么染色方案数为 $2$（一定合法）

3. 其余情况，一定是一大一小，只能选小的那个，方案数为 $1$

然而我们枚举时保证了 $i \ge d$，是不会出现情况一的，所以方案数不是 $1$ 就是 $2$。

发现满足条件 $2$，等价于满足 $\max(dt_{u},ds_{u}) \le i$。

记这个数量为 $cnt$，则剩下的都是 $1$，总的方案数即为 $2^{cnt}$。

但是我们有黑白两种颜色来对树的直径的端点进行分配，所以最后还要乘上 $2$。

统计 $cnt$ 可以用一个桶再前缀和。

于是就做完了。

贴一下我的代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int M=4e5+10;
struct edge{
	int v,nxt;
}e[M];
int h[N],Cnt;
inline void add(int x,int y){
	e[Cnt].v=y;
	e[Cnt].nxt=h[x];
	h[x]=Cnt++;
	return;
}
int n;
int dis1[N],dis2[N];
inline void dfs(int x,int fa,int *dis){
	for(int i=h[x];~i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa)continue;
		dis[v]=dis[x]+1;
		dfs(v,x,dis);
	}
	return;
}
int Get(int x,int *dis){
	dfs(x,0,dis);int adr=1;
	for(int i=1;i<=n;i++)if(dis[i]>dis[adr])adr=i;
	return adr;
}
const int mod=1e9+7;
int cnt[N],po[N];
signed main(){
	int x,y;memset(h,-1,sizeof(h));
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++)cin>>x>>y,add(x,y),add(y,x);
	int l=Get(1,dis2);int r=Get(l,dis1);
	//Ö±¾¶µÄÁ½¸ö¶Ëµã 
	memset(dis2,0,sizeof(dis2));
	dfs(r,0,dis2);
	int d=0,ans=0;
	po[0]=1;
	for(int i=1;i<=n;i++)po[i]=po[i-1]*2%mod;
	for(int i=1;i<=n;i++){
		d=max(d,min(dis1[i],dis2[i]));
		cnt[max(dis1[i],dis2[i])]++;
	}
	for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
	for(int i=0;i<d;i++)ans+=po[n]%mod;
	for(int i=d;i<dis1[r];i++){
		int tmp=(po[n]-po[cnt[i]+1])%mod;
		ans=(ans+tmp)%mod;
	}
	cout<<(ans+mod)%mod;
}
```


---

## 作者：Ishy (赞：4)

# ARC108F Paint Tree（2646）

[洛谷：ARC108F Paint Tree](https://www.luogu.com.cn/problem/AT_arc108_f) 

[Atcoder：ARC108F Paint Tree](https://atcoder.jp/contests/arc108/tasks/arc108_f) 

[ARC108F Paint Tree - cnblogs](https://www.cnblogs.com/Schucking-Sattin/p/17106851.html)

## Problem

给定一棵 $n$ 个节点的树。你需要对每个节点黑白染色。

设 $x$ 表示白色点之间的最大距离，$y$ 表示黑色点之间的最大距离，那么定义一种染色的权值为 $\max(x,y)$。如果某种颜色没有出现那么对应的 $x/y$ 就是 $0$。

求所有 $2^n$ 种染色方式的权值和。对 $10^9+7$ 取模。

## Solution

首先考虑最特殊的情况：树的直径链上两端点节点颜色相同。此时单个染色的贡献即为树的直径 $D$。

记树的直径链两端点分别为 $S$ 和 $T$。

由于染色数要乘上贡献的权值，因此，不妨在枚举、统计时，计算 $\max(x, y) > i$​ 的染色数，我们发现这样会更方便数数。于是我们只用枚举 $i < D$，因此接下来的分析均以 $S$ 与 $T$ 异色。

记 $ds_u$ 为 $u$ 到 $S$ 的距离，$dt_u$ 为 $u$ 到 $T$ 的距离。

 记 $d = \max(\min(ds_u, dt_u))$，对于所有 $< d$ 的 $i$，由于不存在 $\max(x, y) < d$ 的染色方案，因此这些 $i$ 的贡献即为 $2^n$。

当 $d \le i < D$ 时：考虑容斥，用总染色数 $2^n$ 减去 $\max(x, y) \le i$ 的染色数。

考虑每一个点对答案可能的贡献，可能的最大贡献即为 $\max(ds_u, dt_u)$。如果存在一个点使得 $\max(ds_u, dt_u) > i$，那么这种染色就应该被计入当前枚举的 $i$ 对应的染色数中；然而我们现在要找的是不合法的染色方案，用总方案去减掉这部分的数量。

发现当 $\max(ds_u, dt_u) \le i$ 时，点 $u$ 的染色一定不会 **决定** 产生 $> i$ 的贡献。

记这种点的数量为 $cnt_i$，则不合法的染色数为 $2^{cnt_i + 1}$。对于 $\max(ds_u, dt_u) \le i$ 的点，任意染色；否则，只能根据两端点的染色情况尽可能让 $u$ 靠近同色的一端，即令其贡献为 $\min(ds_u, dt_u)$。由于 $i \ge d = \max(\min(ds_u, dt_u))$，因此取 $\min(ds_u, dt_u)$，一定 $\le i$，保证了总有一种且仅有一种对这部分点的染色方案使总染色方案不合法。至于 $2^{cnt_i + 1}$ 中的 $+1$，是对两端点的颜色进行分配。

于是这题就分析完了。

[code ARC108F](https://atcoder.jp/contests/arc108/submissions/38725889) 

---

## 作者：IGpig (赞：2)

# arc108f

## Problem

[problem](https://atcoder.jp/contests/arc108/tasks/arc108_f)

## Solution

看到两点的最长距离，很容易想到树的直径，这里先处理出起点，终点，以及到每个点的距离：$st,ed,dst[v],ded[v]$。\
现在很容易发现如果 $st,ed$ 是同一个颜色的时候答案就是直径。

现在考虑 $st$ 为黑，$ed$ 为白的情况，我们从最大值开始枚举答案 $mx$，如果 $\max(dst[v],ded[v])\le mx$，则 $v$ 的颜色不影响答案，否则与远的那个端点。\
很明显如果有一个点 $\min(dst[v],ded[v])>mx$，那么就不合法，所以在枚举的时候可以从这个从直径长度到最大的 $\min(dst[v],ded[v])$。

接下来看怎么计算不合法的答案。\
首先用一个 $f_i$ 数组记录一下按照 $dis[i]$ 从大到小的长度。然后在枚举答案时维护一个 $j$ 表示最小的一个大于答案的位置。所以有 $2^{n-j+2}$ 的答案不合法。

那么为什么是 $2^{n-j+2}$ 的答案不合法，因为有 $n-j+1$ 个点是 $\min(dst[v],ded[v])>mx$ 的，也就是不合法的，然后因为端点的颜色可以交换，$st$ 为白，$ed$ 为黑，所以再加一，最后就是 $n-j+2$ 个点的染色方案。 

## Code

~~~cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
const LL N=1e6+5,mod=1e9+7;
namespace tree{
    vector<LL> g[N];
    LL st,ed,dst[N],ded[N];
    void get_st(LL x,LL fa){
        for(auto i : g[x]){
            if(i==fa) continue;
            dst[i]=dst[x]+1;
            if(dst[i]>dst[st]) st=i;
            get_st(i,x);
        }
    }
    void get_ed(LL x,LL fa){
        for(auto i : g[x]){
            if(i==fa) continue;
            ded[i]=ded[x]+1;
            if(ded[i]>ded[ed]) ed=i;
            get_ed(i,x);
        }
    }
}
using namespace tree;
LL n,dis[N],pw[N]={1},f[N],s,ans,mn=0;
bool cmp(LL p,LL q){
    return dis[p]>dis[q];
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    get_st(1,0);
    dst[st]=0;
    get_st(st,0);
    ed=st;
    get_ed(ed,0);
    s=ded[ed];
    //cout<<st<<' '<<ed<<endl;
    for(int i=1;i<=n;i++){
        f[i]=i,dis[i]=max(dst[i],ded[i]),mn=max(mn,min(dst[i],ded[i]));
    }
    sort(f+1,f+n+1,cmp);
    ans=s*pw[n]%mod,s--;
    //cout<<mn;
    LL j=1;
    while((s--)>=mn){
        while(j<=n&&s<dis[f[j]]) j++;
		ans=(ans-pw[n-j+2])%mod;
    }
    cout<<(ans+mod)%mod;
    return 0;
}
~~~

---

## 作者：_Kamisato_Ayaka_ (赞：2)

[[ARC108F] Paint Tree](https://www.luogu.com.cn/problem/AT_arc108_f)

## Solution

以下记 $dis(x,y)$ 表示 $x,y$ 两点在树上的距离。

对于同一颜色的两点，固然的，当它们都为树直径的端点时，答案一定最大，但是这题并不保证端点同色，我们就可以考虑去枚举最终答案，即我们去枚举两点之间的距离。

记两点为 $x,y$，为使答案最优，我们保证所有到 $x$ 距离大于枚举的 $dist$ 的点颜色都和 $y$ 一样，所有到 $y$ 距离大于枚举的 $dist$ 的点颜色都和 $x$ 一样，这样取得 $dis(x,y)$ 定为最优解。

考虑如何维护，相当于我们将题目转化为维护一条直径，然后对于每个点记录其到直径的距离。

先考虑直径上的点，记为 $w$，显然的，$dis(w,x) \leq dist$ 且 $dis(w,y) \leq dist$，固然的 $w$ 到其余所有点的距离 $dis(w,i) \leq dist$，所以直径上的点并不会对答案产生影响。

具体的，对于钦定的两端点 $x,y$，我们判断其是否合法，即当它们到直径的最小距离大于所枚举的距离，定不合法，否则对于除去 $x,y$ 的点可黑可白即可统计答案。

记 $cnt_B$ 为除直径点的个数，$cnt_A$ 为剩余点的总个数，$maxd$ 为最大距离，$dist$ 倒序枚举保证最优：

$$
Ans = \sum\limits_{dist}{2^{(cnt_A - cnt_B)} \times i}
$$

$cnt_B$ 初始为 $0$，$2$ 的幂次方预处理可以得到 $O(n)$ 的优秀复杂度。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace FASTIO {
    inline int read() {
        int res = 0, f = 1;
        char ch = getchar();
        while (!isdigit (ch)) f = ch == '-' ? -1 : 1, ch = getchar();
        while (isdigit (ch)) res = (res << 1) + (res << 3) + (ch ^ 48), ch = getchar();
        return res * f;
    }
    inline void write (int x) {
        int st[33], top = 0;
        if (x < 0) x = -x, putchar ('-');
        do { st[top ++] = x % 10, x /= 10; } while (x);
        while (top) putchar (st[-- top] + '0');
    }
} using namespace FASTIO;
const int MOD = 1e9 + 7, MAXN = 1e6 + 10;
int n, head[MAXN], idx, disA[MAXN], disB[MAXN], CntA[MAXN], CntB[MAXN], posD, pos, Cnt, Answer, pw2[MAXN];
bool fl[MAXN];
struct Ayaka { int v, nxt; } edge[MAXN << 1];
inline void Addedge (int u, int v) { edge[++ idx].v = v, edge[idx].nxt = head[u], head[u] = idx; }

void Dfs (int u, int fa, int st) {
    disA[u] = st;
    if (disA[u] > disA[posD]) posD = u;
    for (int i = head[u]; ~i; i = edge[i].nxt) {
        int v = edge[i].v;
        if (v == fa) continue;
        Dfs (v, u, st + 1);
    }
}

signed main() {
    n = read();
    pw2[0] = 1;
    for (int i = 1; i <= n; i ++)
        pw2[i] = (pw2[i - 1] << 1) % MOD;
    memset (head, -1, sizeof head);
    for (int i = 1; i < n; i ++) {
        int u = read(), v = read();
        Addedge (u, v), Addedge (v, u);
    }
    Dfs (1, 1, 0);
    pos = posD, posD = 0;
    Dfs (pos, pos, 0);
    for (int i = 1; i <= n; i ++) CntA[disA[i]] ++;
    memcpy (disB, disA, sizeof disA);
    memcpy (CntB, CntA, sizeof CntA);
    memset (CntA, 0, sizeof CntA);
    pos = posD;
    Dfs (pos, pos, 0);
    /* 两次 dfs 寻找直径后寻找另一端点 */
    for (int i = 1; i <= n; i ++) CntA[disA[i]] ++; /* 统计点数 */
    for (int i = 1; i <= n; i ++)
        fl[min (disA[i], disB[i])] = 1;
    int mxVal = disA[posD], mxCnt = pw2[n], m = n + 1; /* 总共 2^n 种情况 */
    for (int i = mxVal; ~i; i --) {
        if (fl[i]) {
            Answer = (Answer + i * mxCnt % MOD) % MOD; 
            write (Answer), putchar ('\n');
            return 0;
        }
        m -= CntA[i], m -= CntB[i];
        int tmpCnt = pw2[m];
        Answer = (Answer + i * (mxCnt - tmpCnt + MOD) % MOD) % MOD;
        mxCnt = tmpCnt;
    }
    return 0;
}
```

---

## 作者：ty_mxzhn (赞：2)

# T4

困难题。考察了选手对于树论和组合技巧的综合运用。

## 部分分

$O(n^2)$ 留给一些不会维护的正解，其他的留给？？？

## 正解

**性质：对于一颗树，到一个点最远的点一定是直径端点之一。**

先找出直径的两条端点先。若端点颜色相同则最长距离为直径。下面讨论端点不同情况。

设端点中黑色的点是 $x$，另一个是 $y$。枚举答案为 $d$。

则所有到 $x$ 距离 $>d$ 的点颜色是白色，到 $y$ 距离 $>d$ 的点颜色是黑色。

若一个点 $z$ 到 $x,y$ 距离都 $\le d$，则这个点可以乱选。

预处理出 $\max(\mathrm{dis}_{i,x},\mathrm{dis}_{i,y})$。按照这一关键字从大到小排序后依次加入。

若有 $\min(\mathrm{dis}_{i,x},\mathrm{dis}_{i,y})> d$ 则这个 $d$ 不合法。预处理 $2$ 的幂可以在 $O(n)$ 的时间复杂度内解决这个问题。

std 也很短：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1e6+10,mod=1e9+7;
int n,pw[N],u,v,ans,d1[N],d2[N],d[N],a,b,res,p[N];
vector<int> e[N];
void dfs(int u,int fa,int *d){
	d[u]=d[fa]+1;
	if(d[u]>d[res])res=u;
	for(int v:e[u])if(v!=fa)dfs(v,u,d);
}
bool cmp(int x,int y){return d[x]>d[y];}
signed main(){
	freopen("rndcolor.in" ,"r",stdin);
	freopen("rndcolor.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;pw[0]=1,d1[0]=-1,d2[0]=-1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<n;i++)cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
	dfs(1,0,d2);a=res;
	dfs(a,0,d1);b=res;
	dfs(b,0,d2);res=0;
	for(int i=1;i<=n;i++)p[i]=i,d[i]=max(d1[i],d2[i]),res=max(res,min(d1[i],d2[i]));sort(p+1,p+n+1,cmp);
	int m=d1[b];
	ans=m*pw[n]%mod;
	for(int i=m-1,j=1;i>=res;i--){
		while(j<=n&&d[p[j]]>i)j++;
		ans=(ans-pw[n-j+2])%mod;
//		cout<<"##"<<i<<" "<<n-j+2<<endl;
	}
	cout<<(ans+mod)%mod;
}
```

---

## 作者：hbhz_zcy (赞：2)

对另一篇题解进行更加通俗的解释。  
题意很简洁：给一棵 $N$ 个节点的树，对每个节点黑白染色，求所有方案的 $\max\limits_{u,v \in V}[color_u=color_v]dis(i,j)$ 和。  
考虑钦定一条直径（想到直径很关键），端点为 $S,T$。  
钦定 $S$ 染为黑色。  
如果两个端点颜色相同，则答案为直径长度，其它点随便选。  
否则，一个点对 $S$ 和 $T$ 中二选一进行贡献，可以将任意一个点 $u$ **只考虑** $dis(S,u),dis(T,u)$ 中二选一作为贡献。  
证明：  
直径的性质。假设还有一个点 $v\sim u$，则 $dis(u,v) \le \max(dis(S,u),dis(T,u))$，否则 $v$ 会取代 $S$ 或 $T$ 作为直径。  
但是考虑可能存在 $dis(u,v) \gt \min(dis(S,u),dis(T,u))$，钦定是到 $S$ 比较小，则从 $u$ 到 $v$ 必然是向 $T$ 方向走一段（否则向 $S$ 或其它无关点方向会导致 $dis(T,u)+dis(u,v)$能构成直径），故 $dis(S,v)=dis(S,u)+dis(u,v)$，又知道 $S,u,v$ 同色，所以这种情况下，维持所有的点都向端点贡献，会导致贡献与 $dis(S,v)$ 取最大值，依然是不劣的。  
所以贡献 $dis(u,v)$ 一定不比贡献到端点优。  

现在，问题转化为有 $N$ 张卡片，每张正面是 $dis(S,u)$，反面是 $dis(T,u)$。问所有的翻转情况下最大值的和。  
发现原问题可能存在多个直径不好处理，但是按照实际意义可以把除了 $S$ 的所有点都放进来，直接求转化后的问题，最后结果乘二即可。  
新的问题比较好做。首先钦定都选较小的数，然后翻动，从小到大枚举最大值 $t$ 计算贡献。  
设卡片上的数为 $l,r(l \le r)$，则卡片可以分为 $3$ 类，$r \lt t,r = t,r \gt t$。第一类随便翻，第二类至少翻一个，第三类不能翻。因此对答案贡献是 $2^{cnt1}(2^{cnt2}-1)t$。特别的，初始的时候（$t=\max l_i$）第二类可以一个也没有，贡献 $2^{cnt1+cnt2}t$。  

```cpp
const int maxn=2e5+10,mod=1e9+7;
int N,head[maxn],nume=0,S,T,vis[maxn],a[maxn][2],tn[2][maxn];LL mi[maxn],ans=0;
struct node{int to,nxt;}e[maxn<<1];
void edgen(int from,int to){e[++nume]={to,head[from]},head[from]=nume;}
struct nodep{int t,v;};bool operator<(const nodep &x,const nodep &y){return x.v<y.v;}
nodep dfs(int u,int d,int t){
	vis[u]=1;nodep rt={u,d};a[u][t]=d;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])  continue;
		rt=max(rt,dfs(v,d+1,t));
	}
	vis[u]=0;return rt;
}
int main(){
	freopen("in.txt","r",stdin);
	N=qd();for(int i=1;i<N;i++){int x=qd(),y=qd();edgen(x,y),edgen(y,x);}
	mi[0]=1;for(int i=1;i<=N;i++)  mi[i]=mi[i-1]*2%mod;
	S=dfs(N,0,0).t,T=dfs(S,0,0).t;dfs(T,0,1);
	for(int i=1;i<=N;i++){
		if(a[i][0]>a[i][1])  swap(a[i][0],a[i][1]);
		tn[0][a[i][0]]++,tn[1][a[i][1]]++;
	}
	tn[1][a[S][1]]--;
	for(int i=1;i<=N;i++){
		tn[0][i]+=tn[0][i-1];
		if(tn[0][i]>=N){
			if(tn[0][i-1]<N)  (ans+=mi[tn[1][i-1]+tn[1][i]]*i)%=mod;
			else (ans+=mi[tn[1][i-1]]*(mi[tn[1][i]]-1)%mod*i)%=mod;
		}
		tn[1][i]+=tn[1][i-1];
	}
	printf("%lld\n",ans*2%mod);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

考虑求出某一个直径的两个端点 $u$ 和 $v$，距离为 $d$。

如果 $u$ 和 $v$ 颜色相同，答案显然就是 $d$，下面考虑 $u$ 和 $v$ 颜色不同的情况。

如果存在 $w \neq u$ 且 $w \neq v$，使得 $\text{dis}(u,w) = \text{dis}(v,w)=d$，则答案也为 $d$。

考虑剩下的情况，我们可以把点分为三种点集：$A$，$B$ 和 $C$。

$A$ 表示，所有到 $v$ 距离为 $d$ 的点，如 $u \in A$；$B$ 表示，所有到 $u$ 距离为 $d$ 的点，如 $v \in B$；
$C$ 表示，所有不在 $A$ 且不在 $B$ 中的点。

$A$ 中的点必须和 $u$ 同色，$B$ 中的点必须和 $v$ 同色。使用树形 DP 求出，每个点距离 $A$ 中的点距离的最大值，以及到 $B$，记为 $f_u$ 和 $g_u$。

考虑计算有多少种方案，使得答案 $\le t$，这样差分一下就行了。当 $t=d$ 的时候，显然是 $2^n$。如果 $\exists u \in C$ 使得 $\min\{f_u,g_u\} > t$，或者存在两个 $A$ 中或 $B$ 中的点的距离 $>t$，答案是 $0$。否则，答案是：

$$
2^{1 + \sum_{u \in C}[\max\{f_u,g_u\} \le t]}
$$

做一个差分即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MOD=1e9+7;
int n,flg[MAXN],pw[MAXN],ot,cnt[MAXN],din[MAXN][3],dout[MAXN][3],lst,fas[MAXN];
vector<int> G[MAXN];
void dfs(int u,int f,vector<int>& dis) {
	if(f) dis[u]=dis[f]+1;
	for(auto v:G[u]) if(v!=f) dfs(v,u,dis);
	return ;	
}
vector<int> gdis(int u) {
	vector<int> ans;
	ans.resize(n+1),dfs(u,0,ans);	
	return ans;
}
void dfs1(int u,int f) {
	if(flg[u]==1) din[u][1]=dout[u][1]=0;
	if(flg[u]==2) din[u][2]=dout[u][2]=0;
	for(auto v:G[u]) if(v!=f) dfs1(v,u),din[u][1]=max(din[u][1],din[v][1]+1),din[u][2]=max(din[u][2],din[v][2]+1);	
	return ;
}
void dfs2(int u,int f) {
	int mx1=dout[u][1],mx2=dout[u][2];
	for(auto v:G[u]) if(v!=f) {
		dout[v][1]=max(dout[v][1],mx1+1),dout[v][2]=max(dout[v][2],mx2+1);
		mx1=max(mx1,din[v][1]+1),mx2=max(mx2,din[v][2]+1);
	}
	mx1=dout[u][1],mx2=dout[u][2],reverse(G[u].begin(),G[u].end());
	for(auto v:G[u]) if(v!=f) {
		dout[v][1]=max(dout[v][1],mx1+1),dout[v][2]=max(dout[v][2],mx2+1);
		mx1=max(mx1,din[v][1]+1),mx2=max(mx2,din[v][2]+1);
	}
	for(auto v:G[u]) if(v!=f) dfs2(v,u);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n,pw[0]=1;
	ffor(i,1,n) pw[i]=pw[i-1]*2%MOD;
	ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	auto tmp1=gdis(1);
	int mx=*max_element(tmp1.begin(),tmp1.end()),u=-1,v=-1;
	ffor(i,1,n) if(tmp1[i]==mx) u=i;
	auto dis1=gdis(u);
	mx=*max_element(dis1.begin(),dis1.end());
	ffor(i,1,n) if(dis1[i]==mx) v=i;
	auto dis2=gdis(v);
	ffor(i,1,n) if(dis1[i]==mx&&dis2[i]==mx) return cout<<mx*pw[n]%MOD,0;
	ffor(i,1,n) if(dis2[i]==mx) flg[i]=1; else if(dis1[i]==mx) flg[i]=2; else ot++;
	memset(din,-0x3f,sizeof(din));
	memset(dout,-0x3f,sizeof(dout));
	dfs1(1,0),dfs2(1,0);
	ffor(i,1,n) if(!flg[i]) lst=max(lst,min(max(din[i][1],dout[i][1]),max(din[i][2],dout[i][2])));
	ffor(i,1,n) if(!flg[i]) cnt[max(max(din[i][1],dout[i][1]),max(din[i][2],dout[i][2]))]++;
	ffor(i,1,n) if(flg[i]==1) lst=max(lst,max(din[i][1],dout[i][1]));
	ffor(i,1,n) if(flg[i]==2) lst=max(lst,max(din[i][2],dout[i][2]));
	int mul=2,ans=0;
	ffor(i,1,lst-1) mul=mul*pw[cnt[i]]%MOD;
	ffor(i,lst,mx-1) mul=mul*pw[cnt[i]]%MOD,fas[i]=mul;
	fas[mx]=pw[n];
	roff(i,mx,lst) fas[i]=(fas[i]-fas[i-1])%MOD;
	ffor(i,lst,mx) ans=(ans+i*fas[i])%MOD;
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：DerrickLo (赞：1)

看到两个点之间的最大距离，不难想到直径。

我们先找到一条直径，假设直径的两个端点是 $a$ 和 $b$，那么如果这两点同色那么 $\max(x,y)$ 必然是直径长度，所以我们假设这两点异色，再钦定 $a$ 是黑，$b$ 是白，最后将答案乘 $2$ 即可。

那么我们考虑求出对于每个 $i$，$\max(x,y)\le i$ 的个数，将其差分一下即可得到 $\max(x,y)=i$ 的个数， $\max(x,y)\le i$ 当且仅当 $x\le i$ 且 $y\le i$。我们要求的也就是满足这个条件的个数。

我们发现对于黑色点集中的任意两个点的距离的最大值必然是某个点到 $a$ 的距离，因为如果有一条路径 $u\rightarrow v$ 比任意一个点到 $a$ 的距离都要大，那么 $u\rightarrow b$ 和 $v\rightarrow b$ 这两条路径必然有一条比 $a\rightarrow b$ 长，与 $a$ 是直径端点矛盾。白色点集中也是同理。

那么要满足 $x\le i$ 且 $y\le i$ 就需要满足以下两个条件：

- 所有黑色点到 $a$ 的距离 $\le i$，也就是所有到 $a$ 的距离 $>i$ 的点都是白点。

- 所有白色点到 $b$ 的距离 $\le i$，也就是所有到 $b$ 的距离 $>i$ 的点都是黑点。

那么我们考虑倒序枚举 $i$，现在确定了若干个点的颜色，而其他点是可以随便填的，设有 $x$ 个点可以填，那么方案数就是 $2^x$。注意此时如果有一个点既需要填黑也需要填白那么方案数就是 $0$。

时间复杂度 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
using namespace std;
int n,u,v,maxx,x,dep1[200005],dep2[200005],y,dis[200005],anss,pre,sum,vis[200005],flag=1,now,ans[2000005];
vector<int>ve[200005],ve2[200005],ve3[200005];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1; 
	}
	return res;
}
void dfs(int u,int fa,int d,int&pos){
	if(d>maxx)pos=u,maxx=d;
	for(int v:ve[u]){
		if(v==fa)continue;
		dfs(v,u,d+1,pos);
	}
}
void dfs2(int u,int fa,int *dep){
	dep[u]=dep[fa]+1,maxx=max(maxx,dep[u]);
	for(int v:ve[u]){
		if(v==fa)continue;
		dfs2(v,u,dep);
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n,now=n-2;
	for(int i=1;i<n;i++)cin>>u>>v,ve[u].emplace_back(v),ve[v].emplace_back(u);
	dfs(1,0,0,x),maxx=0,dfs2(x,0,dep1);
	for(int i=n;i;i--)if(dep1[i]==maxx)y=i;
	dfs2(y,0,dep2);
	for(int i=1;i<=n;i++)if(i!=x&&i!=y)ve2[dep1[i]].emplace_back(i);
	for(int i=1;i<=n;i++)if(i!=x&&i!=y)ve3[dep2[i]].emplace_back(i);
	for(int i=maxx;i;i--){
		for(int v:ve2[i+1]){
			if(vis[v])flag=0;
			vis[v]=1,now--;
		}
		for(int v:ve3[i+1]){
			if(vis[v])flag=0;
			vis[v]=1,now--;
		}
		if(!flag)break;
		ans[i-1]=ksm(2,now);
	}
	for(int i=maxx-1;i;i--)ans[i]-=ans[i-1],ans[i]+=mod,ans[i]%=mod;
	for(int i=0;i<maxx;i++)anss+=ans[i]*i%mod,anss%=mod;
	anss*=2,anss%=mod;
	cout<<(anss+ksm(2,n-1)*(maxx-1)%mod)%mod;
	return 0;
}
```

---

## 作者：_RainCappuccino_ (赞：1)

> $\mathtt{TAGS}$ ：组合数学，树上计数

> 模拟赛切了，特来写发题解。

首先，根据直径的性质：任意一个点能到达的最远端点一定为直径的某一端点。所以无论最远白点对还是最远黑点对一定包含直径端点。不妨从直径开始考虑。

下文设 $t1, t2$ 为直径的两个端点。

$dis_1$ 为 $t1$ 到其他节点的距离，$dis_2$ 为 $t2$ 到其他节点的距离。

## Case. 1 直径同色

显然 $\max(x, y)$ 的值为直径的长度。

此时其他节点可以随意染色，有 $2 ^ {n - 2}$ 种染色方案。

## Case. 2 直径不同色

1. $\max(x, y)$ 端点为 $t1$
	
	枚举 $\max (x, y)$ 的长度 $k$，统计该长度的情况下，哪些节点可以随意染色，哪些节点无法染色，那些节点只能和 $t1$ 或 $t2$ 同色。
    
 	如果 $dis_{1, i} = k$ 这些点中某一节点必须与 $t_1$ 同色，所以当这些点中全满足 $dis_{1, i} = k, dis_{2, i} \le k$ 时，这些点的染色方案为 $2^{cnt} - 1$。如果只有部分点满足该条件，那么一定有点保证只能与 $t1$ 同色，所以这部分点可以任意染色，方案有 $2 ^ {cnt}$ 种。
    
   显然对 $\max(x, y)$ 长度无影响的节点可以随意染色，满足 $dis_{1, i} < k, dis_{2, i} \le k$。
   
   而如果有对 $\max(x, y)$ 一定有影响的节点，那么该长度 $k$ 不存在一种染色可以满足。这种节点满足 $dis_{1, i} > k, dis_{2, i} > k$。
   
   其余点要么满足 $dis_{1, i} > k, dis_{2, i} \le k$，要么满足 $dis_{1, i} < k, dis_{2, i}$ 此时它们的颜色要么与 $t1$ 同色，要么与 $t2$ 同色，对方案数的贡献为 $1$。
   
2.  $\max(x, y)$ 端点为 $t_2$

    同上，但是对于 $dis_1$ 不能等于 $k$，因为上一种情况考虑了 $x = y$ 的状态，此时就不能再次计算了。
    
所以答案即为这两种情况之和。

## Code 

挑战全谷裸代码长度最长解。

实现很复杂，用到了类似双指针加树状数组统计可以改变的点的数量。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
typedef long long ll;
#define endl '\n'
int n;
vector<int> g[N];
// x, y 中必定包含直径的两个端点 
int dis[N], dis2[N];
pair<int, int> d[N];
int t1, t2; // 直径的两个端点 
void find (int u, int fa) {
	if(!fa) dis[u] = 0;
	for (int v : g[u]) if(v != fa) dis[v] = dis[u] + 1, find(v, u);
}
void getdis (int u, int fa) {
	if(!fa) dis2[u] = 0;
	for (int v : g[u]) if(v != fa) dis2[v] = dis2[u] + 1, getdis(v, u);
}
namespace tr {
	int c[N], len;
	void add (int x) {
		for (int i = x; i <= len; i += i & -i) c[i] ++;
	} 
	int sum (int x) {
		int res = 0;
		for (int i = x; i; i -= i & -i) res += c[i];
		return res; 
	}
	void clean() {
		for (int i = 0; i <= len; i ++) c[i] = 0;
	}
};
// 可随便染色： dis[i] < nowdis && dis2[i] <= nowdis
// 无法染色： dis[i] > nowdis && dis2[i] > nowdis
// 固定颜色： dis[i] > nowdis && dis2[i] <= nowdis || dis[i] < nowdis && dis2[i] > nowdis 
int maxn[N];
int qmi (int x, int k) {
	int res = 1;
	while(k) {
		if(k & 1) res = res * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return res;
}
int work () {
	int tot = 0;
	for (int i = 1; i <= n; i ++) if(i != t1 && i != t2) d[++ tot] = {dis[i], dis2[i]};
	sort(d + 1, d + 1 + tot);
	int ans = 0, j = 1;
	for (int i = tot; i >= 1; i --) maxn[i] = max(maxn[i + 1], d[i].second);
	for (int i = 1; i <= n; i ++) {
		int res = 0, cnt = 0, sum = 0;
		while(d[j].first < i && j <= tot) tr::add(d[j].second), j ++;
		res = qmi(2, tr::sum(i));
		while(d[j].first <= i && j <= tot) tr::add(d[j].second), sum ++, cnt += (d[j].second <= i), j ++;
		if(maxn[j] > i) continue;
		if(sum == 0) continue;
		if(cnt == sum) {
			res *= (qmi(2, cnt) - 1 + mod) % mod, res %= mod;
		} else {
			res *= qmi(2, cnt), res %= mod;
		}
		ans += res * i % mod, ans %= mod;
	}
	tr::clean();
	return ans;
}
int work2 () {
	int tot = 0;
	for (int i = 1; i <= n; i ++) if(i != t1 && i != t2) d[++ tot] = {dis[i], dis2[i]};
	sort(d + 1, d + 1 + tot);
	int ans = 0, j = 1;
	for (int i = tot; i >= 1; i --) maxn[i] = max(maxn[i + 1], d[i].second);
	for (int i = 1; i <= n; i ++) {
		int res = 0, cnt = 0, sum = 0;
		while(d[j].first < i && j <= tot) tr::add(d[j].second), j ++;
		res = qmi(2, tr::sum(i - 1));
		while(d[j].first <= i && j <= tot) tr::add(d[j].second), sum ++, cnt += (d[j].second < i), j ++;
		if(maxn[j] >= i) continue;
		if(sum == 0) continue;
		if(cnt == sum) {
			res *= (qmi(2, cnt) - 1 + mod) % mod, res %= mod;
		} else {
			res *= qmi(2, cnt), res %= mod;
		}
		ans += res * i % mod, ans %= mod;
	}
	tr::clean();
	return ans;	
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	tr::len = n;
	for (int i = 1; i < n; i ++) {
		int u, v;
		cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
	}
	find(1, 0);
	for (int i = 1; i <= n; i ++) if(dis[i] > dis[t1]) t1 = i;
	find(t1, 0);
	for (int i = 1; i <= n; i ++) if(dis[i] > dis[t2]) t2 = i;
	int r = dis[t2];
	getdis(t2, 0);
	int ans = 0;
	ans += work(), ans %= mod;
	for (int i = 1; i <= n; i ++) swap(dis[i], dis2[i]);
	ans += work2(), ans %= mod;
	ans += r * qmi(2, n - 2) % mod, ans %= mod;
	ans *= 2, ans %= mod;
	cout << ans; 
	return 0;
}
```

---

## 作者：orz_z (赞：1)


发现同颜色最远点对一定有一点在直径 $S$ 上。

这下找到直径，算每个点到直径的两种距离。

然后枚举最远点对长度 $d$，根据两种距离跟 $d$ 的大小关系，我们可以知道一个点选的方案数。

然后我们考虑容斥。

记答案为 $\sum w_if_i$ 的形式，表示最远点对为 $w_i$ 的方案数为 $f_i$。

对于一个 $x$，我们计算 $g(x)=\sum [w_i> x]f_i$，则答案为 $\sum\limits_{x=0}^{S-1} g(x)$。

我们钦定直径的颜色不同。

记 $mn=\max(\min(d1_i,d2_i))$，即最远点对的最小值。

对于 $x\in [0,mn)$，$g(x)=2^n$。

对于 $x\in[mn, S)$，$g(x)=2^n -\sum [w_i\le x]f_i$，减去的就是最远点对 $\le x$ 的方案数。

对于点 $i$，如果它满足 $\max(d1_i,d2_i)\le x$，则它两种颜色都可以染；否则它只能染一种。记满足前者条件的点有 $cnt$ 个，则 $\sum[w_i\le x]f_i=2^{cnt + 1}$，还有对直径颜色的分配。

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

出在模拟赛里，切了。

很容易想到树上两同色点间的最大距离一定在树的直径上，考虑拎出一条直径，在直径上进行讨论，分两种情况：

- 直径两端点的颜色相同，此时这条直径一定是树上两点间距离最大的，其他点随机颜色都行，直接计数即可。

- 直径两端点的颜色不同，设此时两同色点间最大距离为 $s$，处理出树上所有点到直径端点 $x$ 和 $y$ 的距离，则可以知道所有与 $x$ 距离大于 $s$ 的点颜色一定与 $y$ 相同，所有与 $y$ 距离大于 $s$ 的点颜色一定与 $x$ 相同。中间的距离小于 $s$ 的点显然不会影响答案，计数即可。

具体实现上，先找出直径，再预处理出所有点到端点的距离 $dis_{x,u}$ 和 $dis_{y,u}$ 枚举距离 $s$ 计算没有被第二种情况限制的点，计数即可。预处理 $2^k$ 可以做到 $O(n)$，当然不预处理也能过。

---

## 作者：shinkuu (赞：0)

讲的题，~~但是没听而且感觉挺有意思而且见过类似的，于是~~自己做出来了。

首先有关键性质：若最大距离的同色点对为 $u,v$，树上的任意一条直径 $(s,t)$ 满足 $s=u,s=v,t=u,t=v$ 其中至少一个成立。

证明：反证。若有一条直径两端点为 $s,t$ 且 $u,v$ 不是任何的一个 $s$ 或 $t$，$s,t,u,v$ 互不相同，钦定 $dis(s,u)<dis(t,u)$，则 $col_u\not=col_t$。同时，因为 $(s,t)$ 为直径，$dis(u,t)<dis(s,t)$，$dis(u,v)<dis(s,v)$，于是 $col_s\not=col_v$，又 $col_u=col_v$，则 $col_s=col_t$，此时显然 $s,t$ 同色且距离更远，不成立。

所以先找出任意一条直径 $(s,t)$，有 $2^{n-1}$ 种情况同色，答案为 $dis(s,t)$。否则，钦定 $col_s=0$，对于每个点 $u$ 考虑钦定 $col_u=0/1$ 的时，有多少种情况使得 $u$ 与一个直径端点的距离是最终答案。

预处理出 $\max(dis(u,s),dis(u,t))$ 然后排序后，处理出此时选这个点做答案的其中一个端点是否可行（$\max(dis(u,s),dis(u,t))\ge\max_{v\not=u}\min(dis(v,s),dis(v,t))$）有多少点 $v$ 是 $col_v$ 为 $0/1$ 都行（即为排序后排名 $-1$），然后计算即可。最后将这部分贡献 $\times 2$，因为加上 $col_s=1$ 的情况。

code：

```cpp
int n,m,dis[N],g[N],h[N],pw[N],pos;
int tot,head[N];
struct node{
	int to,nxt;
}e[N<<1];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
void dfs(int u,int f){
	if((dis[u]=dis[f]+1)>dis[pos]){
		pos=u;
	}
	go(i,u){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		dfs(v,u);
	}
}
void getDis(int u,int f,int *d){
	go(i,u){
		int v=e[i].to;
		if(v==f){
			continue;
		}
		d[v]=d[u]+1,getDis(v,u,d);
	}
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n-1){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	int u,v;
	dfs(1,0),u=pos,pos=0;
	dfs(u,0),v=pos;
	getDis(u,0,g),getDis(v,0,h);
	pw[0]=1;
	rep(i,1,n){
		pw[i]=2*pw[i-1]%mod;
	}
	int ans=1ll*pw[n-1]*g[v]%mod;
	rep(i,1,n){
		if(g[i]>h[i]){
			swap(g[i],h[i]);
		}
	}
	sort(g+1,g+n+1),sort(h+1,h+n+1);
	rep(i,1,n-2){
		if(g[n]>h[i]){
			continue;
		}
		ans=Mod(ans,2ll*h[i]*pw[i-1]%mod);
	}
	int p=lower_bound(h+1,h+n-1,g[n])-h-1;
	ans=Mod(ans,2ll*g[n]*pw[p]%mod);
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：smallpeter (赞：0)

# Solution

考虑把一条直径找出来，两端顶点分别为 $u,v$，直径长度为 $len$ 。现在可以考虑对 $u,v$ 的颜色分类考虑。

## $u,v$ 同色

若这两个点染了同样的颜色，则最大点对距离为 $len$，对答案贡献为 $2^{n-1}\times len$（$u$ 和 $v$ 颜色要相同，$2$ 种；其他点随便选，$2^{n-2}$ 种）。

## $u,v$ 不同色

现在考虑枚举最大点对距离，记作 $s$，有结论：只要每个点到 $u,v$ 中颜色相同的距离不大于 $s$ 即为满足条件的合法方案。证明也不难:若存在某点 $x$ 与 $y$ 同色,观察下图（不妨设 $u$ 与 $x$ 同色 ），若 $s_1>s>s_2+s_3$，则 $s_1+s_2+s_4>s_3+s_4$，与 $u,v$ 为直径矛盾。
![](https://cdn.luogu.com.cn/upload/image_hosting/vqflsjil.png)

但是因为要控制最大距离恰好为 $s$，比较不好计算。我们考虑将要求的东西变成最大距离小于等于 $s$ 的方案数，计算出这个后我们可以利用差分还原出恰好的方案数。

剩下的 $n-2$ 个非直径点只有 $3$ 种状态，与 $u,v$ 距离都不大于 $s$，与 $u,v$ 中的一个距离不大于 $s$ 而另一个大于，与 $u,v$ 的距离都大于 $s$。第一种情况会对答案造成 $\times 2$ 的贡献，第二种情况对答案无影响，第三种情况直接无解。

我们考虑以从大到小的顺序考虑 $s$，这样我们就可以均摊 $O(1)$ 的维护每个点对答案的影响。代码如下。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define fi first
#define se second
#define pb push_back
#define pii pair<LL,LL>
#define mem(a,x) memset((a),(x),sizeof(a))

//#define long long int
#define LLL __int128

template<typename type>
inline void read(type &x)
{
	x=0;bool flag(0);char ch=getchar();
	while(!isdigit(ch)) flag=ch=='-',ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	flag?x=-x:0;
}

template<typename type>
inline void write(type x,bool mode=1)//0为空格，1为换行
{
	x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
	do Stack[++top]=x%10,x/=10; while(x);
	while(top) putchar(Stack[top--]|48);
	mode?putchar('\n'):putchar(' ');
}

LL qsm(LL a,LL b,LL mod){
	LL ans=1,sum=a;
	while(b){
		if(b&1) ans=ans*sum%mod;
		sum=sum*sum%mod;
		b>>=1;
	}
	return ans;
}

const LL N=1e6+10,mod=1e9+7;

LL n;

vector<LL> g[N];

LL dep[N];

vector<LL> ru[N],rv[N];

void dfs(LL u,LL fa,LL &s,LL op){
	if(fa==-1) dep[u]=0;
	else dep[u]=dep[fa]+1;
	if(dep[u]>dep[s]) s=u;
	if(op){
		ru[dep[u]].push_back(u);
	}
	for(LL v:g[u]){
		if(v==fa) continue;
		dfs(v,u,s,op);
	}
}

void dfs(LL u,LL fa){
	if(fa==-1) dep[u]=0;
	else dep[u]=dep[fa]+1;
	rv[dep[u]].push_back(u);
	for(LL v:g[u]){
		if(v==fa) continue;
		dfs(v,u);
	}
}

LL s[N];

LL use[N];

void solve(){
	read(n);
	for(LL i=1;i<n;i++){
		LL u,v;
		read(u),read(v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	if(n==2){
		write(2);
		return ;
	}
	LL U=0,V=0;
	dfs(1,-1,U,0);
	dfs(U,-1,V,1);
	dfs(V,-1);
	LL len=dep[U];
	LL ans=2*len%mod*qsm(2,n-2,mod)%mod;
	LL cnt=n-2;
	for(LL i=len;i>=1;i--){
		for(LL v:ru[i+1]){
			if(v==V||v==U) continue;
			use[v]++;
			if(use[v]==2){
				cnt=-1;
				break;
			}
			cnt--;
		}
		if(cnt<0) break;
		for(LL v:rv[i+1]){
			if(v==V||v==U) continue;
			use[v]++;
			if(use[v]==2){
				cnt=-1;
				break;
			}
			cnt--;
		}
		if(cnt<0) break;
		s[i]=qsm(2,cnt,mod);
	}
	for(LL i=1;i<=len;i++) ans=(ans+2*i%mod*(((s[i]-s[i-1])%mod+mod)%mod)%mod)%mod;
	write(ans);
}

int main(){
	LL T=1;
//	read(T);
	while(T--){
		solve();
	}
}
```

记得要特判 $n=2$，因为这种情况下除掉直径端点不存在点会导致答案计算出错。

---

