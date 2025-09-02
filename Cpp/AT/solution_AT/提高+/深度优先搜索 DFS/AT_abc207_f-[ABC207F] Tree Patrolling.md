# [ABC207F] Tree Patrolling

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc207/tasks/abc207_f

$ N $ 頂点の木があり、各頂点には $ 1 $ から $ N $ までの番号が振られています。また、$ i $ 本目の辺は頂点 $ u_i $ と頂点 $ v_i $ を双方向に結んでいます。

この木の持ち主であるあなたは、いくつかの頂点 ($ 0 $ 個でもよい) を選んで高橋くんを配置し、木の警備をさせることにしました。頂点 $ x $ に配置された高橋くんは、$ x $ と直接辺で結ばれた頂点、及び $ x $ 自身を警備します。

高橋くんを配置する頂点の選び方は $ 2^N $ 通りありますが、そのうち $ 1 $ 人以上の高橋くんに警備された頂点の個数がちょうど $ K $ 個となるような選び方はいくつありますか？

$ K=0,1,\ldots,N $ について答えを求め、$ (10^9+7) $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2000 $
- $ 1\ \leq\ u_i\ \lt\ v_i\ \leq\ N $
- 与えられるグラフは木
- 入力は全て整数

### Sample Explanation 1

高橋くんを配置する頂点の選び方は、以下の $ 8 $ 通りです。 - どの頂点にも高橋くんを配置しない。いずれの頂点も高橋くんに警備されていない状態となる。 - 頂点 $ 1 $ に高橋くんを配置する。全ての頂点が高橋くんに警備された状態となる。 - 頂点 $ 2 $ に高橋くんを配置する。頂点 $ 1 $, $ 2 $ の $ 2 $ つが高橋くんに警備された状態となる。 - 頂点 $ 3 $ に高橋くんを配置する。頂点 $ 1 $, $ 3 $ の $ 2 $ つが高橋くんに警備された状態となる。 - 頂点 $ 1 $ と頂点 $ 2 $ に高橋くんを配置する。全ての頂点が高橋くんに警備された状態となる。 - 頂点 $ 1 $ と頂点 $ 3 $ に高橋くんを配置する。全ての頂点が高橋くんに警備された状態となる。 - 頂点 $ 2 $ と頂点 $ 3 $ に高橋くんを配置する。全ての頂点が高橋くんに警備された状態となる。 - 全ての頂点に高橋くんを配置する。全ての頂点が高橋くんに警備された状態となる。

## 样例 #1

### 输入

```
3
1 3
1 2```

### 输出

```
1
0
2
5```

## 样例 #2

### 输入

```
5
1 3
4 5
1 5
2 3```

### 输出

```
1
0
2
5
7
17```

## 样例 #3

### 输入

```
10
6 10
1 8
2 7
5 6
3 8
3 4
7 10
4 9
2 8```

### 输出

```
1
0
3
8
15
32
68
110
196
266
325```

# 题解

## 作者：rui_er (赞：13)

挺简单的树上背包，就是有点难写。

设 ${dp}_{u,i,x,y}$ 表示仅考虑 $u$ 的子树内，有 $i$ 个节点被控制，$x$ 为节点 $u$ 是否有警卫，$y$ 为节点 $u$ 是否被控制。（其实所有 $x=1,y=0$ 的状态都没用，但我懒得管了。）

每个点 $u$ 的初始值为 ${dp}_{u,0,0,0}={dp}_{u,1,1,1}=1$，其他为 $0$。因为初始时这个点的背包大小为 $1$（只有自己），分别对应没有警卫和有警卫。

设 $v$ 为 $u$ 的儿子，考虑合并 $v$ 的背包到 $u$ 上。设 $u,v$ 的背包大小分别为 $p,q$。下面设 $i\in[0,p],j\in[0,q]$，考虑三种状态分别如何转移：

（一）状态 $x=0,y=0$。

此时 $v$ 上一定没有警卫，不然就会覆盖到 $u$，因此：

$$
{dp}_{u,i+j,0,0}\stackrel{+}{\gets}{dp}_{u,i,0,0}\times({dp}_{v,j,0,0}+{dp}_{v,j,0,1})
$$

（二）状态 $x=0,y=1$。

有两种情况：第一种是此前 $u$ 尚未被控制，直到 $v$ 有警卫后 $u$ 才被控制；第二种是此前 $u$ 已经被控制。因此：

$$
{dp}_{u,i+j,0,1}\stackrel{+}{\gets}{dp}_{u,i-1,0,0}\times{dp}_{v,j,1,1}+{dp}_{u,i,0,1}\times({dp}_{v,j,0,0}+{dp}_{v,j,0,1}+{dp}_{v,j,1,1})
$$

注意第一种情况 $i$ 处要减一，因为 $u$ 点的贡献需要被算进来。

（三）状态 $x=1,y=1$。

这种情况对 $v$ 没有限制，因此：

$$
{dp}_{u,i+j,1,1}\stackrel{+}{\gets}{dp}_{u,i,1,1}\times({dp}_{v,j-1,0,0}+{dp}_{v,j,0,1}+{dp}_{v,j,1,1})
$$

注意这里 $j$ 处又有一个减一，跟上面同理，$v$ 点的贡献需要被算进来。

在完成 $v$ 的背包向 $u$ 的合并后，我们将 $p\stackrel{+}{\gets}q$ 即可继续合并下一棵子树。

上面减一处均有数组越界的风险，这里认为所有不合法（负数下标）的状态的值均为 $0$。

正确实现的树上背包的复杂度为 $\mathcal O(n^2)$，原因是两个点只在 LCA 处被合并一次。正确实现树上背包的方法是精细枚举背包大小，也就是上文对 $p,q$ 的处理。这一点在代码中是通过 $sz$ 数组实现的。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(ll x=(y);x<=(z);x++)
#define per(x,y,z) for(ll x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
    uniform_int_distribution<ll> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const ll N = 2e3+5, mod = 1e9+7;

ll n, dp[N][N][2][2], tmp[N][2][2], sz[N];
vector<ll> e[N];

void dfs(ll u, ll f) {
    dp[u][0][0][0] = dp[u][1][1][1] = 1;
    sz[u] = 1;
    for(ll v : e[u]) {
        if(v != f) {
            dfs(v, u);
            // debug("%lld -> %lld\n", u, v);
            rep(i, 0, sz[u]+sz[v]) {
                tmp[i][0][0] = 0;
                tmp[i][0][1] = 0;
                tmp[i][1][1] = 0;
            }
            per(i, sz[u], 0) {
                per(j, sz[v], 0) {
                    tmp[i+j][0][0] += dp[u][i][0][0] * (dp[v][j][0][0] + dp[v][j][0][1]);
                    tmp[i+j][0][0] %= mod;
                    if(i >= 1) {
                        tmp[i+j][0][1] += dp[u][i-1][0][0] * dp[v][j][1][1] + dp[u][i][0][1] * (dp[v][j][0][0] + dp[v][j][0][1] + dp[v][j][1][1]);
                        tmp[i+j][0][1] %= mod;
                        tmp[i+j][1][1] += dp[u][i][1][1] * ((j >= 1 ? dp[v][j-1][0][0] : 0) + dp[v][j][0][1] + dp[v][j][1][1]);
                        tmp[i+j][1][1] %= mod;
                    }
                }
            }
            rep(i, 0, sz[u]+sz[v]) {
                dp[u][i][0][0] = tmp[i][0][0];
                dp[u][i][0][1] = tmp[i][0][1];
                dp[u][i][1][1] = tmp[i][1][1];
            }
            sz[u] += sz[v];
            // rep(i, 0, sz[u]) debug("DP[%lld][%lld] = {%lld, %lld, %lld}\n", u, i, dp[u][i][0][0], dp[u][i][0][1], dp[u][i][1][1]);
        }
    }
    // debug("@ %lld\n", u);
    // rep(i, 0, sz[u]) debug("DP[%lld][%lld] = {%lld, %lld, %lld}\n", u, i, dp[u][i][0][0], dp[u][i][0][1], dp[u][i][1][1]);
}

int main() {
    // freopen("debug.log", "w", stderr);
    scanf("%lld", &n);
    rep(i, 1, n-1) {
        ll u, v;
        scanf("%lld%lld", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0);
    rep(i, 0, n) printf("%lld\n", (dp[1][i][0][0]+dp[1][i][0][1]+dp[1][i][1][1])%mod);
    return 0;
}
```

---

## 作者：IGA_Indigo (赞：6)

## 题意分析
有一棵树，树上有 $n$ 个节点，树上有若干个个警卫，这些警卫可以控制自己在的节点和相邻的节点，问被控制的节点数 $k=0,1,2,...,n$ 分别有多少种被控制的方案数（ 注意要模 $10^9+7$）。
## 大体思路
这道题是明显的树上背包题，但是实际操作起来十分复杂，因为 $f$ 数组是累加起来的，所以我们还要定义一个 $gg$ 数组来记录 $f$ 数组当前的值。
```cpp
for(long long j=cc[dq];j>=0;j--){
	gg[j][0][0]=f[dq][j][0][0];
	gg[j][1][0]=f[dq][j][1][0];
	gg[j][1][1]=f[dq][j][1][1];
	f[dq][j][0][0]=0;
	f[dq][j][1][0]=0;
	f[dq][j][1][1]=0;
}
```
### 状态设置
$f[i][j][0/1][0/1]$ 以 $i$ 为根的子树，控制 $j$ 个节点，$i$ 没有/有被控制，$i$ 没有/有放警卫。
### 状态转移
这里的转移有九种不同的情况，分别是：

（$dq$ 是当前遍历到的点，$j$ 是背包第一层的变量，$k$ 是背包第二层的变量，$ez$ 是当前节点第 $i$ 个儿子，详细见代码）
1. 当前点和他的儿子都没被控制，状态转移后不会加被控制的点，不加点。
```cpp
f[dq][j+k][0][0]=(f[dq][j+k][0][0]+(gg[j][0][0]*f[ez][k][0][0]));
```
2. 当前点没被控制，但他的儿子有警卫，转移后自己会被控制，加点。
```cpp
f[dq][j+k+1][1][0]=(f[dq][j+k+1][1][0]+(gg[j][0][0]*f[ez][k][1][1]));
```
3. 当前点没被控制，但他的儿子被控制，状态转移后不会加被控制的点，不加点。
```cpp
f[dq][j+k][0][0]=(f[dq][j+k][0][0]+(gg[j][0][0]*f[ez][k][1][0]));
```
4. 前点有警卫，但他的儿子没被控制，转移后儿子会被控制，加点。
```cpp
f[dq][j+k+1][1][1]=(f[dq][j+k+1][1][1]+(gg[j][1][1]*f[ez][k][0][0]));
```
5. 当前点有警卫，他的儿子也有警卫，状态转移后不会加被控制的点，不加点。
```cpp
f[dq][j+k][1][1]=(f[dq][j+k][1][1]+(gg[j][1][1]*f[ez][k][1][1]));
```
6. 当前点有警卫，他的儿子被控制，状态转移后不会加被控制的点，不加点。
```cpp
f[dq][j+k][1][1]=(f[dq][j+k][1][1]+(gg[j][1][1]*f[ez][k][1][0]));
```
7. 当前点被控制，他的儿子有警卫，状态转移后不会加被控制的点，不加点。
```cpp
f[dq][j+k][1][0]=(f[dq][j+k][1][0]+(gg[j][1][0]*f[ez][k][1][1]))%;
```
8. 当前点被控制，他的儿子没被控制，状态转移后不会加被控制的点，不加点。
```cpp
f[dq][j+k][1][0]=(f[dq][j+k][1][0]+(gg[j][1][0]*f[ez][k][0][0]));
```
9. 当前点被控制，他的儿子也被控制，状态转移后不会加被控制的点，不加点。
```cpp
f[dq][j+k][1][0]=(f[dq][j+k][1][0]+(gg[j][1][0]*f[ez][k][1][0]));
```
虽然看上去复杂了点，实际上是很有规律的。最后提醒大家，别忘了模 $10^9+7$。
## 输出答案
这样的话答案就转变成了 $f[1][i][0][0]+f[1][i][1][0]+f[1][i][1][1]$ （以一为根），**别忘了模** $10^9+7$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long tu[2005][2005];
long long b[2005];
long long f[2005][2005][2][2];
long long gg[2005][2][2];
long long cc[2005];//要处理的数量 
void dp(long long dq,long long bb){
	f[dq][0][0][0]=1;
	f[dq][1][1][1]=1;//初始化当前的情况，以免以后一直输出0 
	cc[dq]=1;
	for(long long i=1;i<=b[dq];i++){
		long long ez=tu[dq][i];
		if(ez==bb){
			continue ;
		}
		dp(ez,dq);
		for(long long j=cc[dq];j>=0;j--){
			gg[j][0][0]=f[dq][j][0][0];
			gg[j][1][0]=f[dq][j][1][0];
			gg[j][1][1]=f[dq][j][1][1];
			f[dq][j][0][0]=0;
			f[dq][j][1][0]=0;
			f[dq][j][1][1]=0;
		}//f数组的当前状态清零，记录在gg数组里
		for(long long j=cc[dq];j>=0;j--){
			for(long long k=cc[ez];k>=0;k--){
				f[dq][j+k][0][0]=(f[dq][j+k][0][0]+(gg[j][0][0]*f[ez][k][0][0])%1000000007)%1000000007;
				//当前点和他的儿子都没被控制，状态转移后不会加被控制的点,不加点 
				f[dq][j+k+1][1][0]=(f[dq][j+k+1][1][0]+(gg[j][0][0]*f[ez][k][1][1])%1000000007)%1000000007;
				//当前点没被控制,但他的儿子有警卫，转移后自己会被控制，加点
				f[dq][j+k][0][0]=(f[dq][j+k][0][0]+(gg[j][0][0]*f[ez][k][1][0])%1000000007)%1000000007;
				//当前点没被控制,但他的儿子被控制，状态转移后不会加被控制的点，不加点 
				f[dq][j+k+1][1][1]=(f[dq][j+k+1][1][1]+(gg[j][1][1]*f[ez][k][0][0])%1000000007)%1000000007;
				//当前点有警卫,但他的儿子没被控制，转移后儿子会被控制，加点
				f[dq][j+k][1][1]=(f[dq][j+k][1][1]+(gg[j][1][1]*f[ez][k][1][1])%1000000007)%1000000007;
				//当前点有警卫,他的儿子也有警卫，状态转移后不会加被控制的点，不加点 
				f[dq][j+k][1][1]=(f[dq][j+k][1][1]+(gg[j][1][1]*f[ez][k][1][0])%1000000007)%1000000007;
				//当前点有警卫,他的儿子被控制，状态转移后不会加被控制的点，不加点
				f[dq][j+k][1][0]=(f[dq][j+k][1][0]+(gg[j][1][0]*f[ez][k][0][0])%1000000007)%1000000007;
				//当前点被控制,他的儿子没被控制，状态转移后不会加被控制的点，不加点	
				f[dq][j+k][1][0]=(f[dq][j+k][1][0]+(gg[j][1][0]*f[ez][k][1][1])%1000000007)%1000000007;
				//当前点被控制,他的儿子有警卫，状态转移后不会加被控制的点，不加点		
				f[dq][j+k][1][0]=(f[dq][j+k][1][0]+(gg[j][1][0]*f[ez][k][1][0])%1000000007)%1000000007;
				//当前点被控制,他的儿子也被控制，状态转移后不会加被控制的点，不加点		
			}
		}
		cc[dq]+=cc[ez];
	}
}
int main(){
	long long n;
	cin>>n;
	for(long long i=1;i<n;i++){
		long long l,r;
		cin>>l>>r;
		b[l]++;
		b[r]++;//b[r]数组存的是现在tu[r][]存到哪了，也就是第二维的尾巴，队尾 
		tu[l][b[l]]=r;
		tu[r][b[r]]=l;//tu数组是表示谁和谁连接，因为是无向图，所以两边都得连 
	}
	dp(1,0);
	for(long long i=0;i<=n;i++){
		cout<<(f[1][i][0][0]+f[1][i][1][0]+f[1][i][1][1])%1000000007<<'\n';
	}
	return 0;
} 
```

---

## 作者：Hacker_Cracker (赞：3)

## [ABC207F] Tree Patrolling
### Solution
树上背包。

定义状态：设 $dp_{i,j,k}$ 为以 $i$ 为根节点的子树，有 $j$ 个节点被守卫。第三维中，若 $k=0$ 表示根节点 $i$ 没有放置守卫且未被守卫；若 $k=1$ 表示 $i$ 节点已放置守卫，已被守卫；若 $k=2$ 表示 $i$ 未放置守卫，但已被守卫。令 $siz_i$ 为以 $i$ 为根节点的子树大小（含根）。

过程：通过 dfs 遍历树进行动态规划，将根节点 $u$ 与 $v$ 所代表的子树的状态合并。之后更新 $siz_u$ 的值。

初始化：令 $dp_{u,0,0}=dp_{u,1,1}=1,siz_u=1$。

状态转移：我们需要开一个 $f_{i,0/1/2}$ 数组来记录 $dp_{u,i,0/1/2}$ 的情况。因为后者的值可能随着合并发生改变，但是转移中所用到的 $dp$ 值不应变化。之后为了避免重复计算，我们要把 $dp_{u,i,0/1/2}$ 的值赋为 $0$。

分成九种情况讨论：

- 根节点和字节点都没有放置守卫，没有被守卫。合并后不会产生新的被守卫的节点，转移后根节点依然是 $k=0$ 的情况。转移公式为 $dp_{u,i+j,0} \gets dp_{u,i+j,0}+f_{i,0}\times dp_{v,j,0}$。

- 根节点和子节点均未放置守卫，但是子节点被守卫。合并后不会产生新的被守卫的节点，转移后根节点依然是 $k=0$ 的情况。转移公式为 $dp_{u,i+j,0}\gets f_{i,0}\times dp_{v,j,2}$。
- 根节点和字节点都放置了守卫，都被守卫。合并后不会产生新的被守卫的节点，转移后根节点依然是 $k=1$ 的情况。转移公式为 $dp_{u,i+j,1} \gets dp_{u,i+j,1}+f_{i,1}\times dp_{v,j,1}$。
- 根节点和字节点都被守卫，但子节点没有放置守卫。合并后不会产生新的被守卫的节点，转移后根节点依然是 $k=1$ 的情况。转移公式为 $dp_{u,i+j,1} \gets dp_{u,i+j,1}+f_{i,1}\times dp_{v,j,2}$。
- 根节点和字节点都没有放置守卫，但子节点没有被守卫。合并后不会产生新的被守卫的节点，转移后根节点依然是 $k=2$ 的情况。转移公式为 $dp_{u,i+j,2} \gets dp_{u,i+j,2}+f_{i,2}\times dp_{v,j,0}$。
- 根节点和字节点都被守卫，但根节点没有放置守卫。合并后不会产生新的被守卫的节点，转移后根节点依然是 $k=2$ 的情况。转移公式为 $dp_{u,i+j,2} \gets dp_{u,i+j,2}+f_{i,2}\times dp_{v,j,1}$。
- 根节点和字节点都被守卫，都没有放置守卫。合并后不会产生新的被守卫的节点，转移后根节点依然是 $k=2$ 的情况。转移公式为 $dp_{u,i+j,2} \gets dp_{u,i+j,2}+f_{i,2}\times dp_{v,j,2}$。
- 根节点放置了守卫且被守卫，但子节点没有放置守卫或被守卫。合并后**会**产生新的被守卫的节点，转移后根节点是 $k=1$ 的情况。转移公式为 $dp_{u,i+j+1,1} \gets dp_{u,i+j+1,1}+f_{i,1}\times dp_{v,j,0}$。
- 根节点和字节点都被守卫，但根节点没有放置守卫。合并后**会**产生新的被守卫的节点，转移后根节点是 $k=2$ 的情况。转移公式为 $dp_{u,i+j+1,2} \gets dp_{u,i+j+1,2}+f_{i,0}\times dp_{v,j,1}$。

对于 $K=0,1,\dots,N$ 的答案即为 $dp_{1,K,0}+dp_{1,K,1}+dp_{1,K,2}$。

**注意取模。**

时间和空间复杂度均为 $O(N^2)$。

### [AC Code](https://www.luogu.com.cn/record/202468873)
```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
const int N=2e3+10;
const int MOD=1e9+7;
vector<int>G[N];
int siz[N],n,u,v;
ll dp[N][N][3],dp_new[N][3];
//dp[i][j][0/1/2]:以i为根节点的子树，守卫了j个节点，根节点的守卫情况为：未被守卫、未放守卫/已被守卫、已放守卫/已被守卫、未放守卫 
void dfs(int u,int fa){
	dp[u][0][0]=dp[u][1][1]=1;//初始化 
	siz[u]=1; 
	for(auto v:G[u]){
		if(v==fa) continue;
		dfs(v,u);
		for(int i=siz[u];i>=0;i--){//因为dp[u][i][0/1/2]转移过程中可能会发生变化，但参与转移的量应保持不变，所以开dp_new[i][0/1/2]记录下来，同时清空以防止发生重复计算 
			dp_new[i][0]=dp[u][i][0];
			dp_new[i][1]=dp[u][i][1];
			dp_new[i][2]=dp[u][i][2];
			dp[u][i][0]=dp[u][i][1]=dp[u][i][2]=0;
		}
		for(int i=siz[u];i>=0;i--){
			for(int j=siz[v];j>=0;j--){
				dp[u][i+j][0]=(dp[u][i+j][0]+(dp_new[i][0]*dp[v][j][0])%MOD)%MOD;
				
				dp[u][i+j][0]=(dp[u][i+j][0]+(dp_new[i][0]*dp[v][j][2])%MOD)%MOD;
				
				dp[u][i+j][1]=(dp[u][i+j][1]+(dp_new[i][1]*dp[v][j][1])%MOD)%MOD;
				
				dp[u][i+j][1]=(dp[u][i+j][1]+(dp_new[i][1]*dp[v][j][2])%MOD)%MOD;
				
				dp[u][i+j][2]=(dp[u][i+j][2]+(dp_new[i][2]*dp[v][j][0])%MOD)%MOD;
				
				dp[u][i+j][2]=(dp[u][i+j][2]+(dp_new[i][2]*dp[v][j][1])%MOD)%MOD;
				
				dp[u][i+j][2]=(dp[u][i+j][2]+(dp_new[i][2]*dp[v][j][2])%MOD)%MOD;
				
				dp[u][i+j+1][1]=(dp[u][i+j+1][1]+(dp_new[i][1]*dp[v][j][0])%MOD)%MOD;
				
				dp[u][i+j+1][2]=(dp[u][i+j+1][2]+(dp_new[i][0]*dp[v][j][1])%MOD)%MOD;
			}
		}
		siz[u]+=siz[v];
	}
	return;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	} 
	dfs(1,0);
	for(int i=0;i<=n;i++){
		ll ans=0;
		for(int k=0;k<=2;k++) ans=(ans+dp[1][i][k])%MOD;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：__yun__ (赞：3)

简单的树上背包。

$f_{i,j,s}$ 表示编号为 $i$ 的节点的子树中，有 $j$ 个节点被控制，$s$ 为 $0$ 表示当前节点没有警卫且没有被控制，$s$ 为 $1$ 表示当前节点有警卫，$s$ 为 $2$ 表示当前节点没有警卫但已被控制。

初始值 $f_{i,0,0}=f_{i,1,1}=1$。

转移要分类讨论，详见代码。

### $Code$：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=5010;
const int mod=1e9+7;
int n,sz[M],ans[M],cnt;
int f[M][M][3],g[M][3];
vector<int> eg[M];
void dfs(int u,int fa){
	f[u][0][0]=f[u][1][1]=1;
	sz[u]=1; 
	for(auto v:eg[u]){
		if(v==fa) continue;
		dfs(v,u);
		for(int i=0;i<=sz[u];i++){
			g[i][0]=f[u][i][0];
			g[i][1]=f[u][i][1];
			g[i][2]=f[u][i][2];
			f[u][i][0]=f[u][i][1]=f[u][i][2]=0;
			//同步转移
		}
		for(int i=sz[u];i>=0;i--){
			for(int j=sz[v];j>=0;j--){
				f[u][i+j][0]=(f[u][i+j][0]+(g[i][0]*f[v][j][0])%mod)%mod;
				//当前点没被控制，儿子没被控制 ，转移后一定没被控制，被控制节点数不变 
				f[u][i+j+1][2]=(f[u][i+j+1][2]+(g[i][0]*f[v][j][1])%mod)%mod;
				//当前点没被控制，儿子有警卫 ，转移后一定被控制，被控制节点数加1 （自己被控制了）
				f[u][i+j][0]=(f[u][i+j][0]+(g[i][0]*f[v][j][2])%mod)%mod;
				//当前点没被控制，儿子被控制 ，转移后一定没被控制，被控制节点数不变（孙子有警卫对自己没有影响）
				f[u][i+j+1][1]=(f[u][i+j+1][1]+(g[i][1]*f[v][j][0])%mod)%mod;
				//当前点有警卫，儿子没被控制 ，转移后一定有警卫，被控制节点数加1 （儿子被控制了）
				f[u][i+j][1]=(f[u][i+j][1]+(g[i][1]*f[v][j][1])%mod)%mod;
				//当前点有警卫，儿子有警卫 ，转移后一定有警卫，被控制节点数不变 
				f[u][i+j][1]=(f[u][i+j][1]+(g[i][1]*f[v][j][2])%mod)%mod;
				//当前点有警卫，儿子有警卫 ，转移后一定有警卫，被控制节点数不变 
				f[u][i+j][2]=(f[u][i+j][2]+(g[i][2]*f[v][j][0])%mod)%mod;
				//当前点被控制，儿子没被控制 ，转移后一定被控制，被控制节点数不变 
				f[u][i+j][2]=(f[u][i+j][2]+(g[i][2]*f[v][j][1])%mod)%mod;
				//当前点被控制，儿子有警卫 ，转移后一定被控制，被控制节点数不变 
				f[u][i+j][2]=(f[u][i+j][2]+(g[i][2]*f[v][j][2])%mod)%mod;
				//当前点被控制，儿子被控制，转移后一定被控制，被控制节点数不变 
			}
		}
		sz[u]+=sz[v];
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	int u,v;
	for(int i=1;i<n;i++){
		cin>>u>>v;
		eg[u].push_back(v);
		eg[v].push_back(u);
	}
	dfs(1,0);
	for(int i=0;i<=n;i++){
		cout<<(f[1][i][0]+f[1][i][1]+f[1][i][2])%mod<<endl;
	}
	return 0;
}
```

---

## 作者：xuantianhao (赞：2)

# [[ABC207F] Tree Patrolling](https://www.luogu.com.cn/problem/AT_abc207_f)

弱智 DP 题，设 $f(i,j,0/1/2)$ 表示在点 $i$，子树中有 $j$ 个点被覆盖，且 $i$ 点自身状态是未被覆盖/被自身覆盖/被某个儿子覆盖，然后树上背包更新就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=2e3+100;
int n,x,y;
int f[N][N][3],g[N][3],sz[N];
vector<int> v[N];
void dfs(int x,int fa){
    f[x][0][0]=1;
    f[x][1][1]=1;
    sz[x]=1;
    for(auto y:v[x])if(y!=fa){
        dfs(y,x);
        for(int i=0;i<=sz[x];i++){
			for(int j=0;j<=sz[y];j++){
			    (g[i+j][0]+=f[x][i][0]*f[y][j][0]%mod)%=mod;
			    (g[i+j+1][2]+=f[x][i][0]*f[y][j][1]%mod)%=mod;
			    (g[i+j][0]+=f[x][i][0]*f[y][j][2]%mod)%=mod;
			    (g[i+j+1][1]+=f[x][i][1]*f[y][j][0]%mod)%=mod;
			    (g[i+j][1]+=f[x][i][1]*f[y][j][1]%mod)%=mod;
			    (g[i+j][1]+=f[x][i][1]*f[y][j][2]%mod)%=mod;
			    (g[i+j][2]+=f[x][i][2]*f[y][j][0]%mod)%=mod;
			    (g[i+j][2]+=f[x][i][2]*f[y][j][1]%mod)%=mod;
			    (g[i+j][2]+=f[x][i][2]*f[y][j][2]%mod)%=mod;
			}
		}
        sz[x]+=sz[y];
        for(int i=0;i<=sz[x];i++){
			for(int j=0;j<3;j++){
				f[x][i][j]=g[i][j];
				g[i][j]=0;
			}
		}
    }
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
    dfs(1,0);
    for(int i=0;i<=n;i++){
        int res=0;
        for(int j=0;j<3;j++) (res+=f[1][i][j])%=mod;
        cout<<res<<'\n';
    }
    return 0;
}
```


---

## 作者：EuphoricStar (赞：0)

简单树形 dp。

设 $f_{u,i,p=0/1,q=0/1}$ 为 $u$ 的子树中被覆盖点数为 $i$，$u$ 有没有被覆盖，$u$ 有没有被选。

转移树形背包合并即可，需要分类讨论。要注意如果 $u$ 没被覆盖，$v$ 选了，或者 $u$ 选了，$v$ 没被覆盖，被覆盖点数要 $+1$。

式子较复杂，具体见代码。

[code](https://atcoder.jp/contests/abc207/submissions/41310206)

---

