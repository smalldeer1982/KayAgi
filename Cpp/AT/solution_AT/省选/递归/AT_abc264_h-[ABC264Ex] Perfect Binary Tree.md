# [ABC264Ex] Perfect Binary Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc264/tasks/abc264_h

頂点に $ 1,2,\dots,N $ の番号が付いた、 $ N $ 頂点の根付き木があります。  
 根は頂点 $ 1 $ であり、頂点 $ i\ \ge\ 2 $ について、その親は $ P_i(\ <\ i) $ です。  
 整数 $ k=1,2,\dots,N $ に対し次の問題を解いてください。

番号が $ 1 $ 以上 $ k $ 以下の頂点を、頂点 $ 1 $ を含むようにいくつか選ぶ方法は $ 2^{k-1} $ 通りあります。  
 そのうち、選ばれた頂点集合から誘導される部分グラフの形状が頂点 $ 1 $ を根とする (頂点数がある正整数 $ d $ を用いて $ 2^d-1 $ と表せるような) 完全二分木になるような頂点の選び方はいくつですか?  
 答えは非常に大きくなる場合があるので、$ 998244353 $ で割った余りを求めてください。

 誘導される部分グラフとは?

あるグラフ $ G $ から、一部の頂点を選んだ集合を $ S $ とします。この頂点集合 $ S $ から誘導される部分グラフ $ H $ は以下のように構成されます。

- $ H $ の頂点集合は $ S $ と一致させます。
- その後、 $ H $ に以下のように辺を追加します。
- $ i,j\ \in\ S,\ i\ を満たす全ての頂点対\ (i,j) $ について、 $ G $ 中に $ i,j $ を結ぶ辺が存在すれば、 $ H $ にも $ i,j $ を結ぶ辺を追加する。
 

完全二分木とは? 完全二分木とは、以下の全ての条件を満たす根付き木です。 - 葉以外の全ての頂点が、ちょうど $ 2 $ つの子を持つ。
- 全ての葉が根から等距離にある。
 
 ただし、頂点が $ 1 $ つで辺が $ 0 $ 本のグラフも完全二分木であるものとします。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ 1\ \le\ P_i\ <\ i $

### Sample Explanation 1

\- $ k\ \ge\ 1 $ であるとき $ \{1\} $ - $ k\ \ge\ 3 $ であるとき $ \{1,2,3\} $ - $ k\ \ge\ 5 $ であるとき $ \{1,2,5\},\{1,3,5\} $ - $ k\ \ge\ 8 $ であるとき $ \{1,2,4,5,6,7,8\} $ - $ k\ \ge\ 9 $ であるとき $ \{1,2,4,5,6,7,9\},\{1,2,4,5,6,8,9\} $ - $ k\ =\ 10 $ であるとき $ \{1,2,10\},\{1,3,10\},\{1,5,10\} $ が数えるべき頂点の選び方となります。

### Sample Explanation 2

$ N=1 $ である場合、入力の $ 2 $ 行目は空行です。

## 样例 #1

### 输入

```
10
1 1 2 1 2 5 5 5 1```

### 输出

```
1
1
2
2
4
4
4
5
7
10```

## 样例 #2

### 输入

```
1```

### 输出

```
1```

## 样例 #3

### 输入

```
10
1 2 3 4 5 6 7 8 9```

### 输出

```
1
1
1
1
1
1
1
1
1
1```

## 样例 #4

### 输入

```
13
1 1 1 2 2 2 3 3 3 4 4 4```

### 输出

```
1
1
2
4
4
4
4
4
7
13
13
19
31```

# 题解

## 作者：EnofTaiPeople (赞：6)

题意简述：对于一棵树动态加点，求当前以 $1$ 为根的满二叉树个数，对 $998244353$ 取模。

---
发现这是一个十分模板的树形 dp，与动态 dp 相类似，但更简单。

发现一棵满二叉树的高度最多为 $\log_2n$，于是只需要考虑高度少于 $\log_2n$ 的节点即可。

设 $dp_{x,dep,1}$ 表示以 $x$ 为根，最深节点到 $1$ 距离为 $dep$ 的满二叉树个数，同时为了方便转移，设 $dp_{x,dep,0}$ 表示 $x$ 只有一个儿子，而那个儿子是满二叉树的方案数。

转移时：

$dp_{x,dep,1}=dp_{x,dep,1}+dp_{x,dep,0}\times dp_{y,dep,1}$；

$dp_{x,dep,0}=dp_{x,dep,0}+dp_{y,dep,1}$。

当一个节点深度过大，超过 $\log_2n$ 时，就可以直接跳过。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5,M=998244353;
using ll=long long;
int qp(int a,int x=M-2){
    int res=1;for(;x;x>>=1,a=ll(a)*a%M)
        if(x&1)res=ll(res)*a%M;return res;
}
void add(int &x,int y){
    if((x+=y)>=M)x-=M;
}
int f[N],n,d[N],dp[N][22][2],ans;
int main(){
    ios::sync_with_stdio(false);
    cin>>n;int x,y,_d,nw,p,pr,dat;
    for(x=1;x<=n;++x){
        if(x>1)cin>>f[x];
        d[x]=d[f[x]]+1,_d=d[x];
        if(_d<=20){
            dp[x][_d][1]=nw=1,pr=0;
            for(y=f[x];y;y=f[y]){
                dat=nw;
                nw=(ll(dp[y][_d][0]+M-pr)*nw)%M;
                add(dp[y][_d][0],dat);
                pr=dp[y][_d][1],add(dp[y][_d][1],nw);
            }
        }
        for(p=1,ans=0;p<=20;++p)
            add(ans,dp[1][p][1]);
        printf("%d\n",ans);
    }return 0;
}
```

---

## 作者：Coffee_zzz (赞：2)

先考虑不动态加点的情况。

定义 $f_{r,i}$ 表示在以 $r$ 为根的子树内选择出一棵以 $r$ 为根的深度为 $i$ 的满二叉树的方案数。

容易得到转移方程：

$$
f_{r,i}=\sum_{u \in son_r}\sum_{v \in son_r} [u<v] \times f_{u,i-1} \times f_{v,i-1}
$$

化简可得：

$$
f_{r,i}=\dfrac 1 2\left(\left(\sum_{u \in son_r} f_{u,i-1}\right)^2-\sum_{u \in son_r} {f_{u,i-1}}^2\right)
$$

由于深度为 $i$ 的满二叉树共有 $2^i-1$ 个结点，所以只需求出满足 $i\le\lceil \log n\rceil$ 的 $f_{u,i}$ 即可。

接下来考虑怎么处理动态加点。

注意到，每次新增一个叶子结点后，只会影响其 $k$ 级祖先 $u$ 所对应的 $f_{u,k+1}$ 的值。只有 $\mathcal O(\log n)$ 个值需要修改，所以我们暴力更新这些值即可。

答案即为：

$$
\sum_{i=1}^{\lceil\log n\rceil} f_{1,i}
$$

时间复杂度 $\mathcal O(n\log n)$。

```c++
#include <bits/stdc++.h>
#define int long long
#define ll long long
#define i128 __int128
#define endl '\n'
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define vei vector<int>
#define pq priority_queue
#define yes puts("yes")
#define no puts("no")
#define Yes puts("Yes")
#define No puts("No")
#define YES puts("YES")
#define NO puts("NO")
#define In(x) freopen(x".in","r",stdin)
#define Out(x) freopen(x".out","w",stdout)
#define File(x) (In(x),Out(x))
using namespace std;
const int N=3e5+5,L=20,mod=998244353;
int n,p[N],f[N][L],a[N][L],b[N][L];
void add(int &a,int b){
	a=a+b;
	if(a>=mod) a-=mod;
}
void modify(int u,int i){
	if(u==0||i>=L) return;
	if(i<L-1) add(a[p[u]][i+1],mod-f[u][i]),add(b[p[u]][i+1],mod-f[u][i]*f[u][i]%mod);
	f[u][i]=(mod+1)/2*((a[u][i]*a[u][i]-b[u][i]+mod)%mod)%mod;
	if(i<L-1) add(a[p[u]][i+1],f[u][i]),add(b[p[u]][i+1],f[u][i]*f[u][i]%mod);
	modify(p[u],i+1);
}
void solve(){
	cin>>n;
	for(int i=2;i<=n;i++) cin>>p[i];
	f[1][1]=1;
	cout<<1<<endl;
	for(int i=2;i<=n;i++){
		f[i][1]=1;
		add(a[p[i]][2],1);
		add(b[p[i]][2],1);
		modify(p[i],2);
		int ans=0;
		for(int i=1;i<L;i++) add(ans,f[1][i]);
		cout<<ans<<endl;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	signed T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：happybob (赞：0)

题意：

给定一棵 $n$ 个点的有根树，根为 $1$，保证对于任意 $2 \leq i \leq n$，$i$ 的父亲节点编号小于 $i$。你需要对于每个 $1 \leq k \leq n$，求有多少 $S \subseteq \{1,2,\cdots,k\} \neq \varnothing$ 使得 $S$ 在树上的导出子图连通且是以 $1$ 为根的一棵满二叉树。答案对 $998244353$ 取模。

$1 \leq n \leq 3 \times 10^5$。

解法：

当 $k$ 固定时，考虑 DP，记 $f_{i,j}$ 表示以 $i$ 为根的子树选点，构成一棵以 $i$ 为根的高度为 $j$ 的满二叉树的方案数。转移显然，复杂度 $O(n \log n)$。

对于每个 $k$ 计算一次，总复杂度 $O(n^2 \log n)$。

进一步，发现 $k$ 变成 $k+1$ 时，本质上是新增了一个叶子，从而只对 $O(\log n)$ 个其祖先的 DP 值产生贡献。但是对于祖先计算时仍然枚举每个儿子是不行的，容易被菊花卡成错误复杂度。但是只需要对于每个点记录儿子 DP 值的和就可以直接计算新的 DP 值。复杂度 $O(n \log n)$。

[Submission Link.](https://atcoder.jp/contests/abc264/submissions/60491653)

---

## 作者：forest114514 (赞：0)

### [ABC264Ex] Perfect Binary Tree

~~Ex 题什么时候这么好想了？~~

首先满二叉树不会超过 $\left\lfloor\log N\right\rfloor+1$  层，先 dfs 一遍，所有深度 $>\left\lfloor\log N\right\rfloor+1$ 层的都不管。

我们记 $f_{i,k}$ 为以子树 $i$ 拼成层数为 $k$ 的满二叉树的方案数，状态显然是 $N\log N$ 级别的。

先考虑怎么转移再考虑动态加点的问题。

转移方程：
$$
f_{u,k}=\sum\limits_{i,j\in son_u\land i\ne j} f_{i,k-1}\times f_{j,k-1}
$$
稍微整理一下，即：
$$
f_{u,k}=\frac{1}{2}\times\left[(\sum\limits_{v\in subtree_u}f_{v,k-1})^2-\sum\limits_{v\in subtree_u}f_{v,k-1}^2\right]
$$
每次加点直接上传修改一条链就行了，因为合法的点深度一定 $\ge\left\lfloor\log N\right\rfloor+1$ 的点，所以单次修改的复杂度是 $O(\log N)$，每次查询 $\sum\limits_{i=1}^{\left\lfloor\log N\right\rfloor+1}f_{1,i}$ 的值，也是 $O(\log N)$ 的。

所以本题时空复杂度均为 $O(N\log N)$。 

```cpp
//蒟蒻一枚 rp++
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
#define re register
#define il inline
#define gc() getchar()
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define repp(i,a,b) for(re int i=a;i<b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define tep(i,x) for(re int i=head[x];~i;i=ne[i])
#define ls(x) x<<1
#define rs(x) x<<1|1
#define eps (1e-9)
#define inf 0x3f3f3f3f
#define INF 1e18+100
#define pii pair<int,int>
#define mp(i,j) make_pair(i,j)
#define pb push_back
#define fi first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
template<typename T> inline void read(T &x){
	bool f=1;x=0;char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	x=f?x:-x;
}
template<typename T> inline void write(T x){
	if(x<0) putchar('-'),x=-x;
   	if(x>9) write(x/10);
   	putchar(('0'+x%10));
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
template<typename T> inline void write(T x,char c){write(x),putchar(c);}
//bool _ST;
const int N=3e5+100;
#define int LL 
const int mod=998244353;
int inv=499122177;
int n,f[N][25],g[N][25],g2[N][25],lim,fa[N],dep[N];
void update(int x,int d,int now,int las){
	int last=f[x][d];
	(g[x][d]+=now-las+mod)%=mod;
	(g2[x][d]+=now*now%mod-las*las%mod+mod)%=mod;
	f[x][d]=(g[x][d]*g[x][d]%mod-g2[x][d]+mod)%mod*inv%mod;
	if(x!=1) update(fa[x],d+1,f[x][d],last);
}
//bool _ED;
signed main(){
	//fprintf(stderr,"%.20lf MB\n",(&_ED-&_ST)/1048576.0);
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n);
	lim=21;
	dep[1]=1;f[1][1]=1;//g[1][1]=g2[1][1]=1;
	rep(i,2,n){
		read(fa[i]);
		dep[i]=dep[fa[i]]+1;
	}
	write(1,'\n');
	rep(i,2,n){
		f[i][1]=g[i][1]=g2[i][1]=1;
		if(dep[i]<=lim) 
		update(fa[i],2,1,0);
		LL ans=0;
		rep(i,1,lim) ans=(ans+f[1][i])%mod;
		write(ans,'\n'); 
	}
	//fprintf(stderr,"%.4lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
//谨记:
//十年OI一场空，不开longlong见祖宗
//数据千万条，清空第一条。数据不清空，爆零两行泪。清空不规范，TLE总相伴。
//快读要加类型名

```





---

## 作者：Tsawke (赞：0)

# [[ABC264Ex] Perfect Binary Tree](https://www.luogu.com.cn/problem/AT_abc264_h) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC264Ex)

## 题面

存在一棵以 $ 1 $ 为根节点的 $ n $ 个节点的树，给定序列 $ P_{n - 1} $ 表示 $ [2, n] $ 节点的父亲。给定 $ k $，你需要从 $ [1, k] $ 中选择一些点，对于每一个 $ k $ 一次询问，求有多少种选法使得选出的点为一棵以 $ 1 $ 为根节点的满二叉树。输出 $ k \in [1, n] $ 的答案，答案对 $ 998244353 $ 取模。

## Solution

首先一个比较重要的性质就是 $ n $ 个节点的满二叉树层高为 $ \log_2^n $，所以在原树里层高超过 $ \log_2^n $ 的节点就可以直接忽略了。

不难想到 DP，令 $ dp(p, i) $ 表示以 $ p $ 为根节点层高为 $ i $ 的满二叉树方案数。

朴素的转移十分显然，即在其儿子里找到两个层高为 $ i - 1 $ 的满二叉树拼起来即可，即转移为：
$$
dp(p, i) = \sum_{u \lt v, u, v \in son_p} dp(u, i - 1) \times dp(v, i - 1)
$$
考虑到我们每次询问都是增加一个节点，如此的转移方式复杂度显然是不正确的，考虑优化。不难想到这个式子可以转化为从和平方里去除平方和，即：
$$
dp(p, i) = \dfrac{1}{2}((\sum_{u \in son_p}dp(u, i - 1))^2 - \sum_{u \in son_p}dp(u, i - 1)^2)
$$
于是这个东西就可以支持 $ O(1) $ 修改了，维护一下和以及平方和即可。注意需要记录上一次的值和新的值，减去旧的加上新的。同时考虑发现每次增加一个点，将会改变该点到 $ 1 $ 节点的整条链，并且只会改变这些点，同时若变化的节点超过 $ \log_2^n $ 层了那么可以直接忽略。

最终的答案即为 $ \sum_{i = 1}^{\lfloor \log_2^n \rfloor}dp(1, i) $。

所以每次修改都是 $ O(\log n) $ 的，最终答案的查询也是 $ O(\log n) $ 的，最终复杂度 $ O(n \log n) $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (998244353ll)

template < typename T = int >
inline T read(void);

struct Edge{
    Edge* nxt;
    int to;
    OPNEW;
}ed[610000];
ROPNEW(ed);
Edge* head[310000];

ll qpow(ll a, ll b){
    ll ret(1), mul(a);
    while(b){
        if(b & 1)ret = ret * mul % MOD;
        b >>= 1;
        mul = mul * mul % MOD;
    }return ret;
}

int N;
int mxdep;
int inv2;
int dep[310000];
int fa[310000];
ll ans(0);
ll sum[310000][21], sum2[310000][21];

ll DP(int p, int i){
    if(i == 1)return 1;
    return ((sum[p][i] * sum[p][i] % MOD - sum2[p][i]) % MOD + MOD) % MOD * inv2 % MOD;
}
void dfs(int p = 1, int fa = 0){
    dep[p] = dep[fa] + 1;
    for(auto i = head[p]; i; i = i->nxt)
        if(SON != fa)dfs(SON, p);
}

int main(){
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    inv2 = qpow(2, MOD - 2);
    N = read();
    if(N == 1)printf("1\n"), exit(0);
    mxdep = (int)log2(N);
    for(int i = 2; i <= N; ++i){
        fa[i] = read();
        head[i] = new Edge{head[i], fa[i]};
        head[fa[i]] = new Edge{head[fa[i]], i};
    }dfs();
    for(int cp = 1; cp <= N; ++cp){
        if(dep[cp] <= mxdep){
            sum[cp][1] = sum2[cp][1] = 1;
            ll cnt(1), cur(cp), lst(-1), lstDP(0);
            while(cur != 1){
                lst = cur;
                cur = fa[cur], ++cnt;
                ll tmp = DP(cur, cnt);
                (((sum[cur][cnt] -= lstDP) %= MOD) += MOD) %= MOD;
                (((sum2[cur][cnt] -= lstDP * lstDP % MOD) %= MOD) += MOD) %= MOD;
                lstDP = tmp;
                (sum[cur][cnt] += DP(lst, cnt - 1)) %= MOD;
                (sum2[cur][cnt] += DP(lst, cnt - 1) * DP(lst, cnt - 1) % MOD) %= MOD;
            }
        }ans = 0;
        for(int i = 1; i <= mxdep; ++i)(ans += DP(1, i)) %= MOD;
        printf("%lld\n", ans);
    }
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_03 初稿

---

