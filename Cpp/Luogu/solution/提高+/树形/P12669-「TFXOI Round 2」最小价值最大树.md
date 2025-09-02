# 「TFXOI Round 2」最小价值最大树

## 题目背景

公元前 278 年的今天，伟大的诗人屈原投汨罗江自尽，距今已有 2303 年。  

有一颗江边的树想要纪念他，所以请你来对这棵树做一些装饰。  



## 题目描述

有一个 $n$ 个点的树，点的编号从 $1$ 到 $n$。  

第 $i$ 个点的点权是 $a_i$。   

定义 $f(x,y) = x \land (x \oplus y)$。  

定义 $all(i)$ 为点 $i$ 的所有能通过一条边到达的点的集合。  

定义如下操作：    
> 先选定一个点 $i$，以及一个其直接连接的点集 $s \subseteq all(i)$。    
然后，收益加上 $\sum\limits_{v\in s}f(a_i,a_v) - \sum\limits_{v\in all(i)}(a_v\land a_i)$。  
然后，$a_i \leftarrow 0 $。   

定义树的价值为对其执行任意次以上操作能获得的最大收益（假设一开始收益为 $0$，上述操作仅用于定义树的价值，不会真的执行）。  

定义森林的价值为其中所有树的价值的总和**减去**附加代价，森林中的两个点属于同一棵树，当且仅当两个点之间存在一条路径连接。  

一开始，附加代价等于 $0$。  

你可以执行以下两种操作，其中第一种操作次数没有限制，第二种操作最多执行 $k$ 次：  
1. 选定两个点 $u,v$，使得 $u,v$ 之间有直接连边，令 $x=a_u,y=a_v$，附加代价减去 $x+y$，然后将 $u,v$ 之间的边断开。  
2. 选定一个点 $u$，将 $u$ 点删除，并断开 $u$ 连接的所有边。  

答案为经过上述操作之后，题目给定的树形成的森林的最小价值。  

你需要对于 $k \in [0,lim]$ 都计算出这个答案。     

**注释一：$a \land b$ 的意思是 $a$ 和 $b$ 的按位与值**。

**注释二：$a \oplus b$ 的意思是 $a$ 和 $b$ 的按位异或值**。  

**注释三：$a \leftarrow 0$ 的意思是将 $a$ 赋值为 $0$**。

## 说明/提示

本题样例水的有点过分，故在赛后提供数据生成器，可在附件下载，运行前需要先将 std.cpp 编译为名为 std 的可执行文件，以及使用 python 包管理器安装 cyaron 库。   

**对于 C++ 语言，答案可能会超过 long long 范围，请使用 128 位整型，或者其他高精度**。   

对于全部的数据：$0 \le lim \le n \le 2000$，$\forall i \in [1,n],0 \le a_i \le 2^{63}-1$，详细数据范围见下表。  
| Subtask 编号 |     特殊限制     | 分值 |
| :----------: | :--------------: | :----:|
| #1        | $lim=0,n\le 10$  | $10$   |
| #2        | $lim=0,n \le 20$ | $15$   |
| #3        |  $lim=0$      | $20$   |
| #4        |    $n\le 6$   | $15$   |
| #5        |   $n \le 100$  | $30$   |
| #6        |      无     | $10$   | 

## 样例 #1

### 输入

```
5 3
1 4 5 1 4
1 2
2 3
3 4
4 5```

### 输出

```
15 6 0 0 
```

# 题解

## 作者：__vector__ (赞：5)

出题人题解。  

|特殊限制|做法或需要注意到的结论|
|:-:|:-:|
|$lim=0,n\le 10$|价值定义部分的操作不会在一个点重复执行。|
|$lim=0,n \le 20$|状压 DP 实现上面的结论。|
|$lim=0$|价值是所有边两端的数的异或和的总和。|
|$n\le 6$|断边操作不会执行。|
|$n \le 100$|价值是所有边两端数异或和的总和，断边操作不会执行。|
|无|同上面做法，上面那个是给树形 DP 写假了的。|   
|$n \le 5 \times 10^4$ | DP 是凸的，闵科夫斯基和。由于难度为黑，管理不建议放进比赛。 |

  
### 出题人做法
假设 $b(x,i)$ 表示非负整数 $x$ 的二进制表示中，从 $0$ 位算起，从低到高的第 $i$ 位的值。  

假设 $lim=0$，即不存在对树的修改操作，也不存在附加代价的情况下，树的价值是多少。  

显然，$s$ 必然等于 $all(i)$。  

那么，先不考虑后面减去的那一项，答案会是什么样子。  

此时，每操作一个节点 $u$，就相当于加上 

$$
\sum\limits_{0 \le i \le 63} \sum\limits_{v \in all(i) }[b(u,i) \gt b(v,i)]2^i  
$$     

另外，每个节点最多被操作 $1$ 次，因为第二次操作不可能有贡献。  

令 $dis(u,v)$ 表示 $u$ 点到 $v$ 点所需要经过的最少边数。  

那么，所有的节点操作的贡献总和，似乎很像某个值？  

一个我认为最容易想到的猜想： $\sum\limits_{dis(u,v)=1}(a_u \oplus a_v)$  

然后，实际上上述操作（假设仍然忽略掉减少项）的总贡献并不是这个值。  

原因是，一个数 $u$ 清零之后，原本如果一个位，使 $u$ 和它相邻的节点 $v$ 这一位都是 $1$，那么这一位原本不应该在任何时候产生贡献。  

但是，操作了 $u$ 之后再操作 $v$，就导致这些位的贡献被错误地计算，因为 $u$ 的这一位的值被作为 $0$ 参与计算了。  

这时候，再考虑题目式子中减去的那个值，发现刚好将这一项贡献减掉了。  

所以猜想成立。  

那么现在，如何考虑那两种对于树本身的修改呢？  

对于第一种操作，考虑两个相邻点 $u,v$ ，如果不断开边，那么 $u,v$ 之间的贡献就是 $a_u \oplus a_v$，而断开边，需要多出 $a_u + a_v$ 的贡献，$a_u + a_v \ge a_u \oplus a_v$，这显然是不优的。  

所以，第一种操作永远不会被执行。  

对于第二种操作，考虑 dp。  

树形 dp，令 $f_{u,i,0/1}$ 表示 $u$ 为根的子树执行了 $i$ 次删除操作，$u$ 自己被删或没被删，此时的最小总价值是多少。  

### 审核管理做法  
不观察到异或性质也可以通过本题，方法是设置边权，但是这种方法相对复杂。  
### 加强版做法  
我也不会，一个 7 级钩出题人显然是不会做黑题的。  
但是既然做法存在，我就设置了 5 元的最优解奖金来征求 std。  


std  

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(auto i=(a);i<=(b);i++)
#define REP(i,a,b) for(auto i=(a);i>=(b);i--)
#define FORK(i,a,b,k) for(auto i=(a);i<=(b);i+=(k))
#define REPK(i,a,b,k) for(auto i=(a);i>=(b);i-=(k))
#define pb push_back
#define mkpr make_pair
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
template<class T>
void ckmx(T& a,T b){
    a=max(a,b);
}
template<class T>
void ckmn(T& a,T b){
    a=min(a,b);
}
template<class T>
T gcd(T a,T b){
    return !b?a:gcd(b,a%b);
}
template<class T>
T lcm(T a,T b){
    return a/gcd(a,b)*b;
}
#define gc getchar()
#define eb emplace_back
#define pc putchar
#define ep empty()
#define fi first
#define se second
#define pln pc('\n');
#define islower(ch) (ch>='a'&&ch<='z')
#define isupper(ch) (ch>='A'&&ch<='Z')
#define isalpha(ch) (islower(ch)||isupper(ch))
template<class T>
void wrint(T x){
    if(x<0){
        x=-x;
        pc('-');
    }
    if(x>=10){
        wrint(x/10);
    }
    pc(x%10^48);
}
template<class T>
void wrintln(T x){
    wrint(x);
    pln
}
template<class T>
void read(T& x){
    x=0;
    int f=1;
    char ch=gc;
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=gc;
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=gc;
    }
    x*=f;
}
typedef __int128 sll;
const int maxn=2005;
int n,lim;
sll a[maxn];
vi gp[maxn];
sll f[maxn][maxn][2];
// u/u exist/u.optimes : minimul xor sum
int siz[maxn];
void dfs(int u,int _fa){
    siz[u]=1;
    for(int& v:gp[u]){
        if(v==_fa)continue;
        dfs(v,u);
        siz[u]+=siz[v];
    }
    sll g[2][maxn];
    {
        FOR(b,0,1){
            FOR(i,0,n)g[b][i]=1e30;
        }
        // u 存在
        g[0][0]=0;
        bool cur=0;
        int sz=0;
        for(int& v:gp[u]){
            if(v==_fa)continue;
            FOR(i,0,sz){
                FOR(j,0,siz[v]){
                    // v 存在
                    ckmn(g[cur^1][i+j],g[cur][i]+f[v][j][1]+(a[u]^a[v]));
                    // v 不存在
                    ckmn(g[cur^1][i+j],g[cur][i]+f[v][j][0]);
                }
            }
            FOR(i,0,sz)g[cur][i]=1e30;
            sz+=siz[v];
            cur^=1;
        }
        FOR(i,0,siz[u]){
            f[u][i][1]=g[cur][i];
        }
    }
    {
        FOR(b,0,1){
            FOR(i,0,n)g[b][i]=1e30;
        }
        // u 不存在
        g[0][1]=0;
        bool cur=0;
        int sz=1;
        for(int& v:gp[u]){
            if(v==_fa)continue;
            FOR(i,0,sz){
                FOR(j,0,siz[v]){
                    // v 存在
                    ckmn(g[cur^1][i+j],g[cur][i]+f[v][j][1]);
                    // v 不存在
                    ckmn(g[cur^1][i+j],g[cur][i]+f[v][j][0]);
                }
            }
            FOR(i,0,sz)g[cur][i]=1e30;
            sz+=siz[v];
            cur^=1;
        }
        FOR(i,1,siz[u]){
            f[u][i][0]=g[cur][i];
        }
    }
}
void solve(int id_of_test){
	read(n);
    read(lim);
    FOR(i,1,n){
        read(a[i]);
    }
    FOR(i,1,n-1){
        int u,v;
        read(u);
        read(v);
        gp[u].eb(v);
        gp[v].eb(u);
    }
    FOR(i,0,n){
        FOR(j,0,n){
            f[i][j][0]=f[i][j][1]=1e30;
        }
    }
    dfs(1,0);
    FOR(k,0,lim){
        sll ans=min(f[1][k][0],f[1][k][1]);
        wrint(ans);
        pc(' ');
    }
    pln
}
int main()
{
	int T;
	T=1;
	FOR(_,1,T){
		solve(_);
	}
	return 0;
}
```
验题人 @LastKismet 的代码：  

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __int128 i128;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<int,ll> pil;
typedef pair<ll,int> pli;
template<typename T> using vec=vector<T>;
template<typename T> using grheap=priority_queue<T>;
template<typename T> using lrheap=priority_queue<T,vector<T>,greater<T>>;
#define fir first
#define sec second
#define pub push_back
#define pob pop_back
#define puf push_front
#define pof pop_front
#define chmax(a,b) a=max(a,b)
#define chmin(a,b) a=min(a,b)
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
#define per(i,x,y) for(int i=(x);i>=(y);i--)
#define repl(i,x,y) for(int i=(x);i<(y);i++)
#define file(f) freopen(#f".in","r",stdin);freopen(#f".out","w",stdout);

struct mint {
	int x,mod;
	inline mint(int o=0,int p=998244353) {x=o;mod=p;}
	inline mint & operator=(ll o){return x=o%mod,(x+=mod)>=mod&&(x-=mod),*this;}
	inline mint & operator+=(mint o){return (x+=o.x)>=mod&&(x-=mod),*this;}
	inline mint & operator-=(mint o){return (x-=o.x)<0&&(x+=mod),*this;}
	inline mint & operator*=(mint o){return x=(ll)x*o.x%mod,*this;}
	inline mint & operator^=(ll b){mint res(1);for(;b;b>>=1,*this*=*this)if(b&1)res*=*this;return x=res.x,*this;}
	inline mint & operator^=(mint o){return *this^=o.x;}
	inline mint & operator/=(mint o){return *this*=(o^=(mod-2));}
	inline mint & operator++(){return *this+=1;}
	inline mint & operator--(){return *this-=1;}
	inline mint operator++(int o){mint res=*this;return *this+=1,res;}
	inline mint operator--(int o){mint res=*this;return *this-=1,res;}
	friend inline mint operator+(mint a,mint b){return a+=b;}
	friend inline mint operator-(mint a,mint b){return a-=b;}
	friend inline mint operator*(mint a,mint b){return a*=b;}
	friend inline mint operator/(mint a,mint b){return a/=b;}
	friend inline mint operator^(mint a,ll b){return a^=b;}
	friend inline mint operator^(mint a,mint b){return a^=b;}
	friend inline bool operator<(mint a,mint b){return a.x<b.x;}
	friend inline bool operator>(mint a,mint b){return a.x>b.x;}
	friend inline bool operator<=(mint a,mint b){return a.x<=b.x;}
	friend inline bool operator>=(mint a,mint b){return a.x>=b.x;}
	friend inline bool operator==(mint a,mint b){return a.x==b.x;}
	friend inline istream & operator>>(istream &in,mint &o){ll x;return in>>x,o=x,in;}
	friend inline ostream & operator<<(ostream &ot,mint o){return ot<<o.x,ot;}
};

const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;

const int N=2005;

int n,lim;
i128 a[N];
vec<int> g[N];

int siz[N];
i128 f[N][N][2];

void dfs(int now,int fid){
	siz[now]=1;
	f[now][0][0]=f[now][1][1]=0;
	for(auto nxt:g[now]){
		if(nxt==fid)continue;
		dfs(nxt,now);
		per(i,siz[now],0)per(j,siz[nxt],0){
			if(j)chmin(f[now][i+j][0],f[now][i][0]+min(f[nxt][j][1],f[nxt][j][0]+(a[now]^a[nxt])));
else f[now][i+j][0]=f[now][i][0]+min(f[nxt][j][1],f[nxt][j][0]+(a[now]^a[nxt]));
			if(i)if(j)chmin(f[now][i+j][1],f[now][i][1]+min(f[nxt][j][0],f[nxt][j][1]));
            else f[now][i+j][1]=f[now][i][1]+min(f[nxt][j][0],f[nxt][j][1]);
		}
		siz[now]+=siz[nxt];
	}
}

void print(i128 x){
	if(x/10)print(x/10);
	cout<<char(x%10+'0');
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>lim;
	memset(f,0x3f,sizeof(f));
	rep(i,1,n){
		ll x;cin>>x;
		a[i]=x;
	}
	repl(i,1,n){
		int u,v;cin>>u>>v;
		g[u].pub(v);g[v].pub(u);
	}
	dfs(1,0);
	rep(i,0,lim)print(min(f[1][i][0],f[1][i][1])),cout<<' ';
	return 0;
}
```

---

## 作者：Sliarae (赞：3)

首先，我认为这是一道好题；其次，我认为它更应该出现在愚人节比赛。

考虑树的价值如何计算。要最大化收益，而 $f(x, y)$ 为正，所以应选择 $s = all(i)$。这样选择一个点 $i$ 后，获得的收益就是 $\sum\limits_{v \in all(i)} \big[ f(a_i, a_v) - (a_i \ \text{and} \ a_v) \big]$。

如果一条边 $(u, v)$ 满足 $u, v$ 两个点都被我们操作过。假设 $u$ 先被操作，$v$ 后被操作，那么与这条边有关的收益是 $\big[ f(a_u, a_v) - (a_u \ \text{and} \ a_v) \big] + \big[ f(a_v, 0) - (a_v \ \text{and} \ 0) \big] = \big[ f(a_u, a_v) - (a_u \ \text{and} \ a_v) \big] + a_v$，讨论 $a_u/a_v = 0/1$ 易得这个收益就是 $a_u \oplus a_v$。

用这个结论反过来考虑，如果最终存在点 $i$ 使得 $a_i \neq 0$，不如额外对所有点操作一遍，这样每条边获得的收益 $a_u \oplus a_v$ 都是非负的。所以结束时一定有 $\forall i, a_i = 0$。

所以一棵树 $T$ 的价值就是 $\sum\limits_{(u, v) \in T} (a_u \oplus a_v)$。

现在考虑如何计算答案，操作 $1$ 会花 $a_u + a_v$ 的代价，让树的价值减少 $a_u \oplus a_v$，因为 $a_u + a_v \ge a_u \oplus a_v$，它肯定不优，我们不会使用。

而操作 $2$ 相当于在树上直接割掉一个点，且限制了只能割不超过 $k = 0 \sim lim$ 次。

于是开始 dp，设 $f_{i, j, 0/1}$ 表示 $i$ 子树内割了 $j$ 个点，其中 $i$ 割了/未割的最小价值。用树形背包模型可以分析出时间复杂度为 $O(n^2)$。

```cpp
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;
using i128 = __int128;

const int kN = 2e3 + 5;
const i128 Inf = i128(1) << 100;

int n, lim;
LL a[kN];
vector<int> e[kN];
i128 f[kN][kN][2];
int siz[kN];

void Print (i128 x) {
  if (!x) return cout << 0, void();
  vector<int> v;
  while (x) {
    v.push_back(int(x % 10));
    x /= 10;
  }
  while (!v.empty()) {
    cout << v.back();
    v.pop_back();
  }
}

void Dfs (int u, int r) {
  siz[u] = 1;
  f[u][0][1] = 0, f[u][0][0] = Inf;
  f[u][1][0] = 0, f[u][1][1] = Inf;
  for (auto v : e[u]) {
    if (v == r) continue;
    Dfs(v, u);
    static i128 g[kN][2];
    for (int i = 0; i <= siz[u]; ++i) {
      for (int p = 0; p < 2; ++p) {
        g[i][p] = f[u][i][p];
      }
    }
    for (int i = 0; i <= siz[u] + siz[v]; ++i) {
      for (int p = 0; p < 2; ++p) {
        f[u][i][p] = Inf;
      }
    } 
    for (int i = 0; i <= siz[u]; ++i) {
      for (int j = 0; j <= siz[v]; ++j) {
        for (int p = 0; p < 2; ++p) {
          for (int q = 0; q < 2; ++q) {
            i128 &ret = f[u][i + j][p];
            ret = min(ret, g[i][p] + f[v][j][q] + (p && q ? a[u] ^ a[v] : 0));
          }
        }
      }
    }
    siz[u] += siz[v];
  }
}

int main () {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> lim;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  Dfs(1, 0);
  static i128 ans[kN];
  for (int i = 0; i <= n; ++i) ans[i] = min(f[1][i][0], f[1][i][1]);
  for (int i = 1; i <= n; ++i) ans[i] = min(ans[i], ans[i - 1]);
  for (int i = 0; i <= lim; ++i) {
    Print(ans[i]);
    cout << ' ';
  }
  cout << '\n';
  return 0; 
}
```

---

## 作者：modfish_ (赞：0)

## 思路
首先注意到一件事情：

$$f(x,y)=x\land(x\oplus y)=x-(x\land y)$$

可以验证这是对的。只要把 $x,y$ 各取 $0,1$ 的四种情况讨论一下即可。

那么，题干中一次操作的收益即为：

$$\lvert s\rvert a_i-\sum_{v\in s}(a_v\land a_i)-\sum_{v\in all(i)}(a_v\land a_i)$$

所以，将 $s$ 增加一个数，会得到 $a_i$ 的收益，并失去 $a_v\land a_i$ 的收益。显而易见地，$a_i\ge (a_v\land a_i)$，所以 $s$ 取为 $all(i)$ 必定是最优的。那么单次最大收益即为：

$$\text{deg}_ia_i-2\sum_{v\in all(i)}(a_v\land a_i)$$

每次做完操作后 $a_i$ 就变成 $0$。这其实是表示 $a_i$ 只参与 $1$ 次上述的统计，也就是说第二项中的 $a_v\land a_i$，每一个 $i$ 只被相邻的 $v$ 统计一次。

我们可以把点权转化为边权，具体地，对于一条边 $(u,v)$，令其权值为 $a_u+a_v-2(a_u\land a_v)$。可以发现，一棵树的所有边权和即为这棵树的价值。

接下来我们来观察题目所给的两种操作。

操作 $1$ 是断掉一条边 $(u,v)$，但是需要花 $a_u+a_v$ 的代价。原本有这条边时，它的贡献是 $a_u+a_v-2(a_u\land a_v)$，必定不大于 $a_u+a_v$，所以断边必定使答案变劣，不必考虑。

操作 $2$ 是删掉一个点，并把它周围的边删除。不过只能做 $k$ 次。换个角度考虑：我们需要选出 $k$ 个点，最大化与其相邻的边的权值和。

显然可以做一个树上背包。令 $dp_{x,i,0/1}$ 表示在 $x$ 的子树内选择了 $i$ 个点，且 $x$ 自己不被选/被选。转移直接枚举每一个儿子进行转移就行。

根据树形背包经典结论，只要保证每次枚举的 $i$ 大小不超过 $x$ 的已经扫描的子树大小，最终复杂度为 $O(n^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define i128 __int128

using namespace std;

const int maxn = 2005;
const i128 INF = (__int128)(1ll << 62) * 20000;

ll a[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], siz[maxn], cnt = 0;
i128 ww[maxn << 1], dp[maxn][maxn][2], sum[maxn];

int n, k;
void match(int u, int v, i128 w){
    nxt[++ cnt] = head[u], to[cnt] = v, ww[cnt] = w, head[u] = cnt;
}
void write(i128 x){
    if(x >= 10) write(x / 10);
    putchar(x % 10 + 48);
}
void dfs(int x, int f){
    for(int e = 0; e <= k; e ++) dp[x][e][0] = dp[x][e][1] = 0;
    siz[x] = 1;
    for(int i = head[x]; i; i = nxt[i]){
        int j = to[i];
        if(j == f) continue;
        dfs(j, x);
        for(int e = siz[x]; e >= 0; e --){
            for(int g = siz[j]; g >= 0; g --){
                dp[x][e + g][0] = max(dp[x][e + g][0], dp[x][e][0] + max(dp[j][g][0], dp[j][g][1] + ww[i]));
                dp[x][e + g][1] = max(dp[x][e + g][1], dp[x][e][1] + max(dp[j][g][0], dp[j][g][1]) + ww[i]);
            }
        }
        siz[x] += siz[j];
    }
    for(int e = k; e >= 1; e --) dp[x][e][1] = dp[x][e - 1][1];
    dp[x][0][1] = -INF;
}

int main(){
    scanf("%d %d", &n, &k);
    for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
    i128 tot = 0;
    for(int i = 1; i < n; i ++){
        int u, v;
        scanf("%d %d", &u, &v);
        i128 w = (i128)a[u] + a[v] - (i128)(a[u] & a[v]) * 2;
        match(u, v, w), match(v, u, w);
        tot += w;
    }
    dfs(1, 0);
    for(int i = 0; i <= k; i ++) write(tot - max(dp[1][i][0], dp[1][i][1])), putchar(' ');
    printf("\n");
    return 0;
}
```

---

## 作者：sbno333 (赞：0)

诈骗题。

先观察 $f(x,y)$ 是个什么鬼。

考虑拆位考虑，略一枚举可得当 $0\le x,y\le1$ 时，$f(x,y)$ 表示是否同时满足 $x=1$ 而且 $y=0$。

为了最大化收益。

我们的 $s$ 显然要取全集。

计算 $f(a_i,a_v)-(a_i\land a_v)$。

略一枚举。

当 $a_i=1,a_v=0$ 时，返回 $1$。

当都是 $1$ 时，返回 $-1$。

其余返回 $0$。

当然，返回 $-1$ 并不一定差，因为操作后 $a_i$ 变成了 $0$，此时操作 $v$ 就返回了 $1$，抵消了。

于是我们都要操作。

由于再次操作一定返回 $0$，所以只操作一次即可。

发现二个点此时都操作，那么返回 $1$ 当且仅当二者恰好有一个 $1$，与异或吻合。

于是树的权值为所有边两端阶段权值的异或和的和。

现在考虑操作。

发现第一种操作删去了一个 $x\oplus y$，增加了 $x+y$。

答案肯定增加了，不优。

于是我们只进行第二种操作。

即选定树上一些点，一条边贡献当且仅当两个端点都没被选择。

树上背包合并即可。

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
int MA;
struct st{
	int v,ne;
}sd[1000009];
int inn;
int h[1000009];
void add(int u,int v){
	sd[++inn].v=v;
	sd[inn].ne=h[u];
	h[u]=inn;
}
int dp[2009][2009][2];
int sz[2009];
int a[1000009];
void dfs(int t,int fa){
	sz[t]=1;
	dp[t][0][1]=dp[t][1][0]=-MA;
	dp[t][0][0]=dp[t][1][1]=0;
	for(int i=2;i<=2000;i++){
		dp[t][i][0]=dp[t][i][1]=-MA;
	}
	for(int i=h[t];i;i=sd[i].ne){
		if(sd[i].v!=fa){
			dfs(sd[i].v,t),sz[t]+=sz[sd[i].v];
			for(int j=sz[t];j>=0;j--){
				for(int k=0;k<=min(sz[sd[i].v],j);k++){
					dp[t][j][0]=max(dp[t][j][0],dp[t][j-k][0]+max(dp[sd[i].v][k][0],dp[sd[i].v][k][1]+(a[sd[i].v]^a[t])));
					dp[t][j][1]=max(dp[t][j][1],dp[t][j-k][1]+max(dp[sd[i].v][k][0],dp[sd[i].v][k][1])+(a[sd[i].v]^a[t]));
				}
				
			}
		}	
	}
}
void prk(int x){
	if(x==0){
		cout<<0<<" ";
		return;
	}
	string s;
	s="";
	while(x){
		s=char(x%10+'0')+s;
		x/=10;
	}
	cout<<s<<" ";
}
signed main(){
	MA=1;
	for(int i=1;i<=120;i++){
		MA*=2;
	}
	long long n,lim;
	cin>>n>>lim;
	for(int i=1;i<=n;i++){
		long long gg;
		cin>>gg;
		a[i]=gg;
	}
	int ans;
	ans=0;
	for(int i=1;i<n;i++){
		long long u,v;
		cin>>u>>v;
		ans+=(a[u]^a[v]);
		add(u,v),add(v,u);
	}
	dfs(1,0);
	for(int i=0;i<=lim;i++){
		prk(ans-max(dp[1][i][0],dp[1][i][1]));
	}
	return 0;
}
```

---

