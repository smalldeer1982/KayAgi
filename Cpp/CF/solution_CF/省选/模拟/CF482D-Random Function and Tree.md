# Random Function and Tree

## 题目描述

You have a rooted tree consisting of $ n $ vertices. Let's number them with integers from $ 1 $ to $ n $ inclusive. The root of the tree is the vertex $ 1 $ . For each $ i>1 $ direct parent of the vertex $ i $ is $ p_{i} $ . We say that vertex $ i $ is child for its direct parent $ p_{i} $ .

You have initially painted all the vertices with red color. You like to repaint some vertices of the tree. To perform painting you use the function paint that you call with the root of the tree as an argument. Here is the pseudocode of this function:

```
count = 0 // global integer variable 

rnd() { // this function is used in paint code
    return 0 or 1 equiprobably
}

paint(s) {
    if (count is even) then paint s with white color
    else paint s with black color

    count = count + 1
    
    if rnd() = 1 then children = [array of vertex s children in ascending order of their numbers]
    else children = [array of vertex s children in descending order of their numbers]

    for child in children { // iterating over children array
        if rnd() = 1 then paint(child) // calling paint recursively
    }
}
```

As a result of this function, some vertices may change their colors to white or black and some of them may remain red.

Your task is to determine the number of distinct possible colorings of the vertices of the tree. We will assume that the coloring is possible if there is a nonzero probability to get this coloring with a single call of $ paint(1) $ . We assume that the colorings are different if there is a pair of vertices that are painted with different colors in these colorings. Since the required number may be very large, find its remainder of division by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

All possible coloring patterns of the first sample are given below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482D/19d967abe6f79007d166ea0e6fd74474e906140d.png)

## 样例 #1

### 输入

```
4
1 2 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3
1 1
```

### 输出

```
5
```

# 题解

## 作者：gyh20 (赞：9)

很明显是一个树形 DP，且一个点的贡献只和选出来的数的个数的奇偶性有关，我们可以设一个 $f_{x,0/1}$ 表示奇/偶。

接下来讨论转移：

假如说只有上升一种排法，那么直接转移即可：

$f_{x,0}=f_{x,1}\times f_{y,1}+f_{x,0}\times{(f_{y,0}+1)}$ （$+1$ 表示什么都不选的方案）

$f_{x,1}$ 转移类似。

但现在还有下降排法，考虑容斥，求出上升排法后 $\times 2$ 减去只能算一次的排法。

令选出的儿子非零子树大小为 $a_i$。

则一个状态不能算两次当且仅当不存在一个 $i$ 使得 $i$ 的前缀和与后缀和在模 $2$ 意义下不等。

进行一些分析：

若存在 $i,a_i\bmod 2\neq a_{i+1}\bmod 2$，那么 $i$ 或 $i+1$ 一定满足前缀和与后缀和在模 $2$ 意义下不等。

所以说不能重复计算的状态的奇偶性相同。

若全为偶数，只能算一次。

若全为奇数，若个数为奇数则只能算一次，否则倒过来也是对的，再来一个 DP 转移一下即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=1e9+7;
int n,f[100002][2],m,t,g[100002][4];
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x,re int y){return (x+=y)>=M?x-=M:x;}
vector<int>v[100002];
inline void dfs(re int x){
	sort(v[x].begin(),v[x].end());
	f[x][1]=1,f[x][0]=0;
	for(re int i=0,z;i<(int)v[x].size();++i){
		dfs(z=v[x][i]);
		re int tmp0=f[x][0],tmp1=f[x][1];
		add(f[x][0],1ll*tmp0*f[z][0]%M);
		add(f[x][0],1ll*tmp1*f[z][1]%M);
		add(f[x][1],1ll*tmp0*f[z][1]%M);
		add(f[x][1],1ll*tmp1*f[z][0]%M);
	}
	re int aaa=1;
	reverse(v[x].begin(),v[x].end());
	add(f[x][0],f[x][0]),add(f[x][1],f[x][1]);
	g[x][0]=1,g[x][1]=0;
	for(re int i=0,z;i<(int)v[x].size();++i){
		z=v[x][i];
		re int tmp=g[x][1];
		add(g[x][1],1ll*g[x][0]*f[z][1]%M);
		add(g[x][0],1ll*tmp*f[z][1]%M);
		aaa=1ll*aaa*(f[z][0]+1)%M;
	}
	add(f[x][0],M-g[x][1]);
	add(f[x][1],M-aaa);
}
int main(){
//	freopen("randomdfs.in","r",stdin);
//	freopen("randomdfs.out","w",stdout);
	t=1;
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)v[i].clear();
		for(re int i=2;i<=n;++i)v[read()].push_back(i);
		dfs(1);
		printf("%d\n",(f[1][0]+f[1][1])%M);
	}
}

```


---

## 作者：feecle6418 (赞：7)

什么时候倒序访问儿子和正序访问儿子没有区别？当且仅当 $\forall y\in son_x$，$pre_{y}+1\equiv suf_{y}+1\pmod 2$（$pre_y$ 为 $y$ 之前访问的儿子 size 总和，$suf_y$ 为 $y$ 之后访问的儿子 size 总和）。该式仅在 $\forall$ 选择的 $y$，都有 $size_y$ 为 [偶数]/[奇数且选出的 $y$ 总个数为奇数] 时，才会成立。

设 $f_{x,0/1}$ 为 $x$ 的子树内选出奇数/偶数个节点，col 数组方案数，$g_{x,0/1,x/0}$ 为 $x$ 的子树内选出奇数/偶数个节点，每个子树内访问的节点数（即 size）全部是奇数/偶数，的 col 数组方案数。转移显然。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
vector<int> gr[100005];
int f[100005][2],g[100005][2][2],n;
//g[i][0/1][0/1]: i的子树（暂不考虑i），和为偶/奇，全是偶/全是奇
void dfs(int x){
	for(int y:gr[x])dfs(y);
	g[x][0][0]=g[x][0][1]=f[x][1]=1;
	for(int y:gr[x]){
		int t1=(1ll*f[x][0]*f[y][1]+1ll*f[y][0]*f[x][1])%mod;
		int t0=(1ll*f[x][0]*f[y][0]+1ll*f[y][1]*f[x][1])%mod;
		f[x][0]=(f[x][0]+t0)%mod,f[x][1]=(f[x][1]+t1)%mod;
		int t00=1ll*g[x][0][0]*f[y][0]%mod;
		int t01=1ll*g[x][1][1]*f[y][1]%mod;
		int t11=1ll*g[x][0][1]*f[y][1]%mod;
		g[x][0][0]=(g[x][0][0]+t00)%mod;
		g[x][0][1]=(g[x][0][1]+t01)%mod;
		g[x][1][1]=(g[x][1][1]+t11)%mod;
	}
	f[x][0]=(2ll*f[x][0]-g[x][1][1]+mod)%mod;
	f[x][1]=(2ll*f[x][1]-g[x][0][0]+mod)%mod;
}
int main(){
	scanf("%d",&n);
	for(int i=2,x;i<=n;i++)scanf("%d",&x),gr[x].push_back(i);
	dfs(1),printf("%d\n",(f[1][0]+f[1][1])%mod);
    return 0;
}
```

---

## 作者：Acee (赞：3)

发唐了。

这不是直接做吗，为什么发唐了。

你发现一个点的颜色只于之前染了几个点有关，更好的，是只与奇偶性有关系，就可以大力设 $f_{u,0/1}$ 了。

考虑转移，唯一需要细想的就是升序与降序重复的时候。

则一个状态不能算两次当且仅当不存在一个 $v$ 使得 $v$ 的前缀和与后缀和在模 2 意义下不等。

所以，若全为偶数，只能算一次。若全为奇数，若个数为奇数则只能算一次，否则倒过来也是对的，再来一个 DP 转移一下即可。

代码太好写了，就不放了。

---

## 作者：_l_l_ (赞：2)

## 题目简述

有一棵有根树，根为 $1$，每个节点有点权，初始全为 $-1$，有以下伪代码：

```cpp
cur = 0
col[] = {-1, -1, ...}

rand():
	随机返回 0 或 1

paint(当前节点 u):
	col[u] = cur
	当 cur == 1 时: cur = 0
	否则: cur = 1
	当 rand() == 1 时: 将 u 的所有儿子按照节点编号升序排序
	否则: 将 u 的所有儿子按照节点编号降序排序
	遍历每一个 u 的儿子 v:
		当 rand() == 1 时: paint(v)
	无返回
```

求运行一遍 `paint(1)` 后节点点权的方案数 mod $10^9+7$。

## 题解

假如去掉 `paint` 开头的随机排序这个问题该怎么做？

我们可以设 $dp_u$ 为运行一遍 `paint(u)` 后 $u$ 的子树的点权方案数，则由于一儿子的点权取决于自己是否需要 `paint` 以及前面的儿子，而每一个儿子处受后效性影响的只有 `cur` 值，因此可以直接通过乘法原理计算：

$$
dp_u\gets\prod_{v\in u\text{' son}} (1+dp_v)
$$

但是加上了随机排序，我们不能只将贡献乘以 $2$，因为有些方案它是“对称的”，即无论将儿子升序还是降序排序，最终染色方案始终不变的，因此我们考虑将这些情况去掉。

进一步，我们发现情况出现当且仅当 升序时任意儿子前需要改点权的节点个数 与 升序时任意儿子后需要改点权的节点个数 关于 $2$ 同余。

通过枚举，只有以下情况符合要求：

- 所有的需要染色的子树都是偶数节点需要染色。
- 所有的需要染色的子树都是奇数节点需要染色，且需要染色的子树有奇数个。

我们就可以基于这个进行 dp 了。

定义 $dp_{u,0/1}$ 为 $u$ 号节点子树总染色节点为偶 / 奇数个的方案数。

定义 $f_{u,0/1}$ 为 $u$ 号节点的儿子节点有偶 / 奇数个要染奇数节点的方案数。

这两个 dp 状态是动态更新的。

转移如下：

1. 计算总贡献：
   
   $$
   \begin{aligned}
   dp_{u,0}&\gets dp'_{u,0}\times(1+dp_{v,0})+dp'_{u,1}\times dp_{v,1}\\
   dp_{u,1}&\gets dp'_{u,0}\times dp_{v,1}+dp'_{u,0}\times(1+dp_{v,0})
   \end{aligned}
   $$
   
   最后将 $dp_{u,0}$ 和 $dp_{u,1}$ 各自乘以 $2$。
   
2. 任意偶数子树：
   
   $$
   \text{cost}_u\gets\prod_{v}dp_{v,1}
   $$
   
   最后 $dp_{u,1}$ 减去 $\text{cost}_u$。
   
3. 奇数个奇数子树：
   
   $$
   \begin{aligned}
   f_{u,0}&\gets f'_{u,0}+f'_{u,1}\times dp_{v,1}\\
   f_{u,1}&\gets f'_{u,1}+f'_{u,0}\times dp_{v,1}
   \end{aligned}
   $$
   
   最后将 $dp_{u,0}$ 减去 $f_{u,1}$。
   
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
const int mod = 1000000007;
struct edge {
	int to, nxt;
} edges[MAXN]; int head[MAXN], tot;
void add(int u, int v) {
	edges[++tot].to = v; edges[tot].nxt = head[u]; head[u] = tot;
}
int dp[MAXN][2], f[MAXN][2];
// dp[u][0/1]: u 节点，总染色个数为偶 / 寄数个的方案数
// f[u][0/1]: u 节点，儿子节点有偶 / 寄数个染了寄数个节点的方案数 
// 两者皆动态更新 
void dfs(int u) {
	for (int i = head[u]; i; i = edges[i].nxt) dfs(edges[i].to);
	// 计算正反贡献 
	dp[u][0] = 0; dp[u][1] = 1;
	for (int i = head[u]; i; i = edges[i].nxt) {
		int dpu0 = dp[u][0], dpu1 = dp[u][1];
		dp[u][0] = (dpu0 * (1ll + dp[edges[i].to][0]) + 1ll * dpu1 * dp[edges[i].to][1]) % mod;
		dp[u][1] = (1ll * dpu0 * dp[edges[i].to][1] + dpu1 * (1ll + dp[edges[i].to][0])) % mod;
	}
	dp[u][0] = dp[u][0] * 2 % mod; dp[u][1] = dp[u][1] * 2 % mod;
	// 移除多余贡献
	// 1. 任意个 偶树
	int cst = 1;
	for (int i = head[u]; i; i = edges[i].nxt) {
		cst = cst * (1ll + dp[edges[i].to][0]) % mod;
	}
	dp[u][1] = (dp[u][1] + mod - cst) % mod;
	// 2. 寄数个 寄树
	f[u][0] = 1; f[u][1] = 0;
	for (int i = head[u]; i; i = edges[i].nxt) {
		int tmp = f[u][0];
		f[u][0] = (f[u][0] + 1ll * f[u][1] * dp[edges[i].to][1]) % mod;
		f[u][1] = (f[u][1] + 1ll * tmp * dp[edges[i].to][1]) % mod;
	}
	dp[u][0] = (dp[u][0] + mod - f[u][1]) % mod;
}
int main() {
	int n; scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		int fa; scanf("%d", &fa); add(fa, i);
	}
	dfs(1);
	printf("%d", (dp[1][0] + dp[1][1]) % mod);
	return 0;
}
```

---

## 作者：chroneZ (赞：0)

对于点 $u$，考虑钦定 $u$ 子树内被染色的点集（显然是一个含根的连通块），如果钦定子结点子树中的染色顺序，考虑什么情况下正序和逆序执行操作会得到相同的结果。容易发现，这等价于满足以下两个条件之一：（只考虑被染色结点）

- 所有子树大小均为偶数。
- 所有子树大小均为奇数，且子树数量为奇数。

记 $f_{u, 0/1}$ 表示 $u$ 子树的颜色序列方案数，其中被染色点集大小模 $2$ 余 $0/1$，点集非空。

初始令 $f_{u, 1} \gets 1$，每次 $f_{u, i} (f_{v, j} + [j = 0]) \to f_{u, i \oplus j}$ 即可，最后令 $f_{u, i} \gets 2f_{u, i}$，即正反操作会得到不同结果。

然后考虑减去会产生重复的部分：

- 所有染色子树大小均为偶数。这对应 $f_{u, 1} \gets f_{u, 1} - \prod (1 + f_{v, 0})$。
- 所有染色子树大小均为奇数，且染色子树数量为奇数。你可以选择 DP，但是更牛的做法是考虑多项式 $F = \prod (1 + f_{v, 1} x)$，其所有奇数次项的系数之和即为答案，而这等价于 $\frac{F(1) - F(-1)}{2}$。所以令 $f_{u, 0} \gets f_{u, 0} - \frac{\prod (1 + f_{v, 1}) - \prod (1 - f_{v, 1})}{2}$ 即可。

最终答案是 $f_{1, 0} + f_{1, 1}$，时间复杂度 $\Theta(n)$。

```cpp
// Such a destiny was not desired.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int mod = 1e9 + 7, N = 1e5 + 5;
namespace basic {
  inline int add(int x, int y) {return (x + y >= mod ? x + y - mod : x + y);}
  inline int dec(int x, int y) {return (x - y < 0 ? x - y + mod : x - y);}
  inline void ad(int &x, int y) {x = add(x, y);}
  inline void de(int &x, int y) {x = dec(x, y);}

  inline int qpow(int a, int b) {
    int r = 1;
    while(b) {
      if(b & 1) r = 1ll * r * a % mod;
      a = 1ll * a * a % mod; b >>= 1;
    }
    return r;
  }
  inline int inv(int x) {return qpow(x, mod - 2);}

  int fac[N], ifac[N];
  inline void fac_init(int n = N - 1) {
    fac[0] = 1;
    for(int i = 1; i <= n; i++)
      fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[n] = inv(fac[n]);
    for(int i = n - 1; i >= 0; i--)
      ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
  }
  int invx[N];
  inline void inv_init(int n = N - 1) {
    invx[1] = 1;
    for(int i = 2; i <= n; i++)
      invx[i] = 1ll * (mod - mod / i) * invx[mod % i] % mod;
  }
  inline int binom(int n, int m) {
    if(n < m || m < 0) return 0;
    return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
  }
}
using namespace basic;
constexpr int inv2 = (mod + 1) / 2;

int n; vector<int> G[N];
int f[N][2];

void dfs(int u) {
  f[u][1] = 1;
  for(auto v : G[u]) {
    dfs(v);
    int x = f[u][0], y = f[u][1];
    f[u][0] = add(1ll * x * (1 + f[v][0]) % mod, 1ll * y * f[v][1] % mod);
    f[u][1] = add(1ll * x * f[v][1] % mod, 1ll * y * (1 + f[v][0]) % mod);
  }
  f[u][0] = 2ll * f[u][0] % mod;
  f[u][1] = 2ll * f[u][1] % mod;

  int P = 1;
  for(auto v : G[u]) {
    P = 1ll * P * (1 + f[v][0]) % mod;
  }
  de(f[u][1], P);

  int F0 = 1, F1 = 1;
  for(auto v : G[u]) {
    F0 = 1ll * F0 * (1 + f[v][1]) % mod;
    F1 = 1ll * F1 * dec(1, f[v][1]) % mod;
  }
  de(f[u][0], 1ll * dec(F0, F1) * inv2 % mod);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  
  cin >> n;
  for(int i = 2; i <= n; i++) {
    int fa; cin >> fa;
    G[fa].push_back(i);
  }
  dfs(1);
  cout << add(f[1][0], f[1][1]) << "\n";
}
```

---

## 作者：Benzenesir (赞：0)

> 有一棵有根树，根为 1，每个节点有点权，初始全为 −1，有以下伪代码：
```cur = 0
col[] = {-1, -1, ...}
rand():
	随机返回 0 或 1
paint(当前节点 u):
	col[u] = cur
	当 cur == 1 时: cur = 0
	否则: cur = 1
	当 rand() == 1 时: 将 u 的所有儿子按照节点编号升序排序
	否则: 将 u 的所有儿子按照节点编号降序排序
	遍历每一个 u 的儿子 v:
		当 rand() == 1 时: paint(v)
	返回
```
>求运行一遍 paint(1) 后节点点权的方案数 mod 1e9+7。
> $n \leq 1e5$

抽象，太抽象了。

直觉能够告诉我们一个 DP，设 $f_{now,0/1,0/1}$ 为以以什么颜色进入 $now$，以什么颜色出来的方案数，不难看出，这个颜色的差是与染色的点的奇偶性有关的，改进一下状态 $f_{now,0/1}$ 为选了奇/偶数个点的方案数。

考虑转移，对于当前节点，既然已经来到了这个节点，自然已经选了一个点，$f_{now,1}=1，f_{now,0}=0$，

设 $x$ 为 $now$ 的一个儿子，等式右边的状态是之前的，奇数转移如下：

$f_{now,1}=f_{now,0} \times f_{x,1}+f_{now,1}\times (f_{x,0}+1)$

*这里的加一是可以空选*

偶数转移类似。

倒序乘个二就可以。

但是这样是会记重的，考虑什么样的选法会被计算两次。

![](https://cdn.luogu.com.cn/upload/image_hosting/q4p2wwon.png)

考虑这样的选择方案，如果对于每一个黄色的节点，在其之前选择的点的数量的奇偶性与其之后选择的点的数量的奇偶性都相同，则其反过来也是一样的。

观察可得，只有两种可能
1. 所有的子树内选的都是偶数个。
2. 所有的子树内选的都是奇数个，且选的子树个数为奇数。

对于第一种，直接连乘起来就可以了，第二种则需要一个 DP，状态和转移显然，就不再写了。

```c++
struct modint {
	ll x;
	modint() : x(0) {}
	modint(ll x) : x(x) {}
	bool operator==(modint y) { return x == y.x; }
	void operator=(int y) {y %= mod;this->x = (y % mod);}
	modint operator+(modint y) {modint z(x + y.x);if (z.x >= mod)z.x -= mod;return z;}
	modint operator-(modint y) {modint z(x - y.x);if (z.x < 0)z.x += mod;return z;}
};
modint operator*(modint x, ll y) {modint z(x.x * y);z.x %= mod;return z;}
modint operator*(ll y, modint x) {modint z(x.x * y);z.x %= mod;return z;}
modint operator*(modint x, modint y) {modint z(x.x * y.x);z.x %= mod;return z;}
ostream &operator<<(ostream &out, modint x) {out << x.x;return out;}
const int N=1e5+10;
int n;
modint f[N][2];
vector<int> g[N];
void dfs(int now){
	sort(g[now].begin(),g[now].end());
	for(int x:g[now]) dfs(x);
	modint d1=1,d2=0;
	f[now][1]=1,f[now][0]=0;
	for(int x:g[now]){
		modint nd1=d2*f[x][1]+d1*f[x][0],
			nd2=d2*f[x][0]+d1*f[x][1];
		d1=d1+nd1,d2=d2+nd2;	
	}
	reverse(g[now].begin(),g[now].end());
	modint p1=0,p2=1,mul=1;
	for(int x:g[now]){
		modint np1=p2*f[x][1],np2=p1*f[x][1];
		p2=p2+np2,p1=p1+np1;
		mul=mul*(f[x][0]+1);
	}
	f[now][1]=d1*2,f[now][0]=d2*2;
	f[now][1]=f[now][1]-mul;
	f[now][0]=f[now][0]-p1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	n=rd();
	fp(i,2,n) g[rd()].emplace_back(i);
	dfs(1);
	cout << f[1][0]+f[1][1] << endl;	
	return 0;
}
```

---

