# [AGC059C] Guessing Permutation for as Long as Possible

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc059/tasks/agc059_c

先生が $ (1,2,\cdots,N) $ の順列 $ P=(P_1,P_2,\ldots,P_N) $ を隠し持っています。 これから、あなたはこの順列を特定します。

そのために、あなたは整数のペアの列 $ (A_1,B_1),(A_2,B_2),\ldots,(A_{N(N-1)/2},B_{N(N-1)/2}) $ を用意しました。これは、$ (a,b) $ ($ 1\ \le\ a\ <\ b\ \le\ N $) という形のすべてのペアを並べ替えたものです。 今から、あなたはこれらのペアを先頭から検査します。ペア $ (A_i,\ B_i) $ に対しては、$ P_{A_i}\ <\ P_{B_i} $ であるかを尋ね、先生が答えを教えます。 ただし、この質問への答えがそれ以前の答えから特定できる場合は、この質問を省略します。

このアルゴリズムで $ \frac{N(N-1)}{2} $ 個の質問がすべてされるような順列 $ P $ の個数を $ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \leq\ 400 $
- $ 1\ \le\ A_i\ <\ B_i\ \le\ N $
- $ (A_i,B_i)\ \neq\ (A_j,B_j) $ ($ i\ \neq\ j $)
- 入力中のすべての値は整数である。
 
### Sample Explanation 1

明らかに、どの順列 $ P $ に対しても、質問を一つする必要があります。

### Sample Explanation 2

例として、$ P=(2,3,1,4) $ を考えます。 この場合、二問目までで $ P_1\ <\ P_2 $ と $ P_1\ >\ P_3 $ を知って $ P_2\ >\ P_3 $ と特定できるため、三問目を省略します。 従って、$ P=(2,3,1,4) $ は数えません。

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
4
1 2
1 3
2 3
2 4
3 4
1 4```

### 输出

```
4```

## 样例 #3

### 输入

```
5
1 2
2 3
3 4
4 5
1 5
1 3
2 4
3 5
1 4
2 5```

### 输出

```
0```

# 题解

## 作者：lzqy_ (赞：6)

这题只要想到拿 $3$ 个数出来手玩就好做了。

考虑有三个下标 $a,b,c$ 满足数对 $(a,c)$ 最后出现，那么 $P_b$ 的值就不能位于 $P_a,P_c$ 之间（否则通过 $(a,b),(b,c)$ 可以推出 $P_a,P_c$ 的大小关系）。归纳一下可以发现，这是排列合法的**充要条件**。

维护的话就很简单了。对于数对 $(A,B)\,(A<B)$，我们称 $P_A<P_B$ 为白色数对，$P_A<P_B$ 为黑色数对，那么 $P_a,P_b,P_c$ 的关系就可以拿种类并查集或者2-SAT维护了。

然后发现，由于边数是 $\frac{n(n-1)}{2}$ 且每组询问都是有效的，所以能唯一确定一组排列。也就是说，每一种数对的染色方案都唯一对应了一个排列。因此最终的答案就是 $2^k$，$k$ 是独立的数对集合数（即强连通分量的个数）。
 
时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=410;
const int maxN=160010;
const int mod=1e9+7;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x; 
}
int col[maxn][maxn];
int ti[maxn][maxn];
int f[maxN<<1],n,m;
int Find(int x){return f[x]==x?x:f[x]=Find(f[x]);}
bool remerge(int x,int y){
//	printf("%d,%d\n",x,y);
//	printf("%d,%d\n",Find(x+m),Find(y+m));
	if(Find(x)==Find(y)) return 0;
	if(Find(x+m)==Find(y+m)) return 0;
	f[Find(x)]=Find(y+m),f[Find(y)]=Find(x+m);
	return 1;
}
bool merge(int x,int y){
	if(Find(x)==Find(y+m)) return 0;
	if(Find(y)==Find(x+m)) return 0;
	f[Find(x)]=Find(y),f[Find(x+m)]=Find(y+m);
	return 1;
}
int main(){
	int x,y;
	n=read(),m=n*(n-1)/2;
	for(int i=1;i<=m;i++){
		x=read(),y=read();
		ti[x][y]=ti[y][x]=i;
	}
	for(int i=1;i<=m;i++) f[i]=i,f[i+m]=i+m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=i+1;k<=n;k++)
				if(i!=j&&j!=k){
					int t1=ti[i][j],t2=ti[i][k],t3=ti[j][k];
					if(t2>max(t1,t3))
						if(!(((i<j)^(j<k))?merge(t1,t3):remerge(t1,t3)))
							return printf("0\n"),0;	
				}
	for(int i=1;i<=m;i++)
		if(Find(i)==Find(i+m))
			return printf("0\n"),0;
	int ans=1,cn=0;
//	for(int i=1;i<=m+m;i++)
//		printf("%d ",Find(i));
//	printf("\n");	
	for(int i=1;i<=m+m;i++)
		if(Find(i)==i) cn++;
//	while(1);
//	printf("%d\n",cn);
	for(int i=1;i<=cn/2;i++) ans=ans*2%mod;
	printf("%d\n",ans);
	return 0;
}  	 		
```

---

## 作者：ღꦿ࿐ (赞：3)

Orz 蜜蜂！蜜蜂的智慧是不可估量的！

把偏序关系看作有向图上的边可以得到图 $G$。

一个条件 $(x,y)$ 是没用的当且仅当 $G$ 中已经有 $x\to y$ 或 $y \to x$ 的链了。

直接判断两个点之间没有长度较大的链的方案数并且还要加入边，是不太现实的，思考了一会感觉不行，于是考虑约化出较强的条件：

因为最终给出的是一个全序集，而不是问“在某个条件处不合法”的排列，所以若某个条件 $x \to y$ 有着一条很长的链，那么在之后连接这条链上的两个节点一定也不合法。

$\text{assertion}:$  $(x,y)$ 不存在长度为 $2$ 的链是排列**全局**合法的充分必要条件。

如果假设 $x\to y$ 存在链 $L$ 且长度大于 $2$，若 $L$ 上存在两个距离为 $2$ 的点之间还没有出现有向边，则后来出现的这条有向边不合法

试图构造出一条长度大于 $2$ 的 链，且其中距离为 $2$ 的点两两有有向边发现长度为 $3$ 的链无法构造出：长度假设已经有了长度为 $2$ 的链（图中的 $1\to2\to3$），现在加入点 $4$ 。

此时 $1\to 4,2\to 4,3\to4$ 产生了石头剪刀布的环形限制关系。


![](https://cdn.luogu.com.cn/upload/image_hosting/ogyymx6d.png)

更长的满足条件的链也无法构造出，因为长度为 $3$ 的链是它的一个子集。

所以条件就被强化为了只用考虑 $x\to p \to y$ ， 也就是说 $x \to y$ 限制了 $(x,p),(p,y)$ 不能同时存在。

直接处理出条件之间的相互限制关系，使用带权并查集或是直接 dfs 一遍即可判断可行性，由于每个联通块决定第一个条件的真假后就可以决定剩下条件的真假了，所以答案就是 $2^k$ ， $k$ 为联通块个数，时间复杂度 $O(n^3)$ 或 $O(n^3 \alpha(n^2))$。

你可能会担心这样会不会答案的有向图连出环产生不合法的情况 ，仔细思考可以发现，限制边的方式决定了图上的“环”一定会被至少一条反向边“打断”，否则一定不合法。

[code](https://atcoder.jp/contests/agc059/submissions/37099999)

让人恶心的是，atc 对 $998244353$ 取模不是已成习俗了吗，咋搞 $10^9 + 7$ 了？ 蜜蜂是不是 cf 混久了。






---

## 作者：FutaRimeWoawaSete (赞：2)

**AGC059C sol**

其实并不是很困难。

刚开始我想的时候以为是判长链，要容斥系数根本不可做。

后来瞄了一眼才发现我是纯 nt。具体来说我们只用判长度 $\geq 3$ 的同向边链就行了，即过程中形成的 DAG 图里没有长度 $= 3$ 且首尾未被连接的同向边链，若存在这条链在后续插入端点边时一定会导致无用信息。

枚举端点 $(a,c)$，找到其插入位置。在枚举一个端点 $b$，满足 $b$ 不被 $(a,b),(b,c)$ 边构成一条同向边组成的链。

考虑 $n$ 很小，将所有边都设成 $0,1$ 标记信息后的节点，那么上述的条件就可以做 2-SAT！！！！

再模拟一下，发现 2-SAT 中建的边是对称的，即在最后缩点后的图里任意一个弱连通块会和另一个弱连通块的节点集合基于 $0,1$ 对称。

那么两个弱连通块上的节点形成基于 $0,1$ 的对称关系，你可以看成是一个映射。

也就是说确定了其中一个弱连通块某个度数为 $0$ 的节点（选择还是不选择），另一个弱连通块中对应的度数为 $0$ 的节点选择还是不选择也会被确定！！！

确定了所有度数为 $0$ 的节点后底下的度数不为 $0$ 的节点的选择也会被确定。

由于 $\frac{n(n-1)}{2}$ 次加边有效，那么可唯一确定一个排列，即排列数对应我们在 DAG 上的选择情况。统计所有弱连通块度数为 $0$ 的节点的数量设为 $N$，答案显然就是 $2 ^ {\frac{N}{2}}$。

特判是否有 2-SAT 不合法的过程，时间复杂度 $O(n ^ 3)$，空间复杂度 $O(n ^ 2)$。

```cpp
/*
考虑在线建图，当前连接之前的所有路径不存在全部大于/小于的关系
感觉这个 ds 化，咕着。
先考虑把限制全部拿出来然后容斥，但是这个数量级爆炸啊！
那我们考虑它所连的边，只能这么算了
令 dp_{i,j,0/1} 表示 i 到 j 存在的两种情况的总方案数这个不好容啊！
倒着做，没前途。
发现我做复杂了。 
题解给了个提示：(a,b,c) 即可确定了。因为若是一条大于 3 的链，那么在之前就应该寄了。 
*/
#include "bits/stdc++.h"
using namespace std;
const int N = 5e2 + 5 , Len = 4 * N * N + 5 , mod = 1e9 + 7;
int n,m,head[Len],cnt,mp[N][N][2],ct;
int fa[Len],siz[Len];
inline void makeSet(int x){for(int i = 1 ; i <= x ; i ++) fa[i] = i , siz[i] = 1;}
int findSet(int x){return fa[x] == x ? fa[x] : fa[x] = findSet(fa[x]);}
void unionSet(int x,int y)
{
	int u = findSet(x) , v = findSet(y);
	if(u == v) return;
	fa[v] = u , siz[u] += siz[v];
}
int vis[N][N];
int col[Len];
int main()
{
	scanf("%d",&n);for(int i = 1 ; i <= n ; i ++) for(int j = i + 1 ; j <= n ; j ++) mp[i][j][0] = ++ ct , mp[i][j][1] = ++ ct;
	makeSet(ct);
	for(int i = 1 ; i <= n * (n - 1) / 2 ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		if(x > y) swap(x , y);
		for(int j = 1 ; j <= n ; j ++)
		{
			if(j == x || j == y) continue;
			int l1 = min(j , x) , r1 = max(j , x) , l2 = min(j , y) , r2 = max(j , y);
			if(vis[l1][r1] && vis[l2][r2]) 
			{
				//假设 l1 = j , r1 = x 
				unionSet(mp[l1][r1][1 ^ (l1 != j)] , mp[l2][r2][1 ^ (l2 != j)]);
				unionSet(mp[l2][r2][0 ^ (l2 != j)] , mp[l1][r1][0 ^ (l1 != j)]);
			}
		}
		vis[x][y] = 1;
	}
	for(int i = 1 ; i <= n ; i ++) for(int j = i + 1 ; j <= n ; j ++) if(findSet(mp[i][j][0]) == findSet(mp[i][j][1])) return puts("0") & 0;
	int rk = 0;
	for(int i = 1 ; i <= ct ; i ++) if(findSet(i) == i) rk ++;
	int ret = 1;
	for(int i = 1 ; i <= (rk >> 1) ; i ++) ret = 1ll * ret * 2 % mod;
	printf("%d\n",ret);
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：2)

题目转化：

给定一个 $n$ 阶完全图，边权构成了 $1\sim \binom{n}{2}$ 的排列。

问这个图有多少 DAG 定向，使得**每一条** $x\to y$ 边权为 $z$ 的**边**，不存在 $x\to y$ 边权**均小于** $z$ 的**路径**。

* * *

这个限制等价于所有三个点的诱导子图（设 $x\to y,y\to z,x\to z$）有 $x\to y$ 和 $y\to z$ 边权较大值大于 $x\to z$ 的边权。

为啥等价呢？可以用最小矛盾子图 $>3$ 推出矛盾来反证。

所以我们枚举有序点三元组 $(x,y,z)$，若 $(x,y)$ 和 $(x,z)$ 边权均小于 $(y,z)$，则 $(x,y)$ 和 $(x,z)$ 两条边定向时有且仅有一条是指向 $x$ 的。

发现这样的条件顺便满足了 DAG 这个限制，证明可以考虑若有环则最小环长度 $=3$。

所以我们存在多个形如「两条边方向必须相同 / 不同」的条件，就是 2sat 问题了。

这里只要考虑解的个数，所以用带权并查集即可。

---

## 作者：hhhqx (赞：1)

# [AGC059C] Guessing Permutation for as Long as Possible 题解

## 前言

题目传送门：[AGC059C Guessing Permutation for as Long as Possible](https://atcoder.jp/contests/agc059/tasks/agc059_c)。

题面：问又多少种 $1$ 到 $n$ 的排列 $P$，使得 $\frac{n(n-1)}{2}$ 个不同询问 $(i,j)$，你说出 $p_i$ 和 $p_j$ 那个大。不能让询问者在不提问的情况下就依据前面的回答，得到谁更大。

$2 \le n \le 400$。

这篇题解题只需要使用[【模板】并查集](https://www.luogu.com.cn/problem/P3367)。
## 思路

分析性质，如果 $(a,b)$ 能直接得答案，设 $p_a < p_b$，那么在此之前必然形成了一条链 $p_a < p_{c_1} < p_{c_2} < p_{c_3} < \cdots < p_b$。可如果 $p_a < p_{c_1} < p_{c_2}$ 那么在 $(a,c_2)$ 这里就可以得到答案了，轮不到讨论 $(a,b)$，于是我们只用讨论 $(a,c_2)$。

$a,c_1,c_2$ 太麻烦，于是改为 $i,k,j$。

如果 $p_i<p_k$，那么就只能 $p_k>p_j$。如果 $p_i>p_k$，那么就只能 $p_k<p_j$。

这不正是并查集的合并操作吗？设 $(d,e)$ 为一个节点代表 $p_d<p_e$，上面的讨论就是 $(i,k)$ 和 $(j,k)$ 合并，且 $(k,i)$ 和 $(k,j)$ 合并。这样一来，我们的并查集中的一个集合就表示这些条件都必须同时满足或不满足。

思路都到这里了，接下来统计方案数。如何判断答案为 $0$？只用看 $(i,j)$ 和 $(j,i)$ 是否在同一集合，因为它们两个不可以同时成立或同时不成立。如何求答案？设有 $k$ 个集合，呢么就有 $\frac{k}{2}$ 个集合**对应**另外 $\frac{k}{2}$ 个，因为 $(i,j)$ 和 $(j,i)$ 不在同一个集合，于是答案为 $2^{\frac{k}{2}}$。

最后时间复杂度 $O(n^3 \log n)$，复杂度卡在了合并这里，但是合并也是有条件的，不会跑满。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int MAXN = 400 + 3;
const LL mod = 1e9 + 7;

int n, vis[MAXN][MAXN];
int fa[MAXN * MAXN];

int Ri(int i, int j){ // (P_i < P_j) 这一节点的编号
  return (i - 1) * n + j;
}
int Getf(int x){ return fa[x] == x ? x : fa[x] = Getf(fa[x]); }
void Merge(int x, int y){ x = Getf(x), y = Getf(y), fa[x] = y; }

int main(){
  cin >> n;
  for(int i = 1, a, b; i <= n * (n - 1) / 2; i++){
    cin >> a >> b, vis[a][b] = vis[b][a] = i;
  }
  for(int i = 1; i <= n * n; i++) fa[i] = i;
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      for(int k = 1; k <= n; k++){
        if(vis[i][j] > vis[i][k] && vis[i][j] > vis[j][k]){
          Merge(Ri(i,k), Ri(j,k)); // Pi < Pk  <=>  Pj < Pk
          Merge(Ri(k,i), Ri(k,j)); // Pi > Pk  <=>  Pj > Pk
        }
      }
    }
  }
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      if(i != j && Getf(Ri(i,j)) == Getf(Ri(j,i))){
        cout << 0; // 矛盾
        return 0;
      }
    }
  }
  set<int> st;
  LL ans = 1;
  for(int i = 1; i <= n; i++){
    for(int j = 1; j <= n; j++){
      if(i == j) continue;
      int f = Getf(Ri(i,j)), _f = Getf(Ri(j,i));
      if(st.find(f) == st.end()){ // set 去重
        st.insert(f), st.insert(_f), ans = ans * 2ll % mod;
      }
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：Nuisdete (赞：1)

题意可以理解为按顺序给一个完全图的每条边定向，使得任何时候都不能出现一条长度为 $2$ 的有向链且链的两个端点没有边，求方案数。

每条边只有两个方向，因此按上面的题意模拟一下 `2-SAT` 就行了，两个方向规定为编号小的到大的和大的到小的。

不合法方案数就是 $0$，否则方案数就是 $2$ 的强连通分量个数次幂，因为每个强连通分量的方向是独立的。

限制是相互的，可以用并查集维护。

```cpp
# include <cstdio>
# include <algorithm>

constexpr int MAXN = 400 + 5;

int n;

int f[MAXN << 1][MAXN << 1];

int fa[MAXN * MAXN << 1];

int find(int x) { return fa[x] == x ? fa[x] : fa[x] = find(fa[x]); }

void unite(int x, int y) { fa[find(x)] = find(y); }

int main() {

  scanf("%d", &n); int m = n * (n - 1) >> 1;
  for (int i = 1; i <= 2 * m; ++i) fa[i] = i;
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    if (x > y) std::swap(x, y);
    f[x][y] = f[y][x] = i;
    for (int z = 1; z <= n; ++z) {
      if (f[x][z] && !f[y][z]) {
        if (z < x) 
          unite(f[x][z], f[x][y] + m), unite(f[x][z] + m, f[x][y]);
        else unite(f[x][z], f[x][y]), unite(f[x][z] + m, f[x][y] + m);
      }
      if (f[y][z] && !f[x][z]) {
        if (z > y)
          unite(f[y][z], f[x][y] + m), unite(f[y][z] + m, f[x][y]);
        else unite(f[y][z], f[x][y]), unite(f[y][z] + m, f[x][y] + m);
      }
    }
  }
  for (int i = 1; i <= m; ++i) 
    if (find(i) == find(i + m)) return puts("0"), 0;

  int ans = 1;
  for (int i = 1; i <= m; ++i) 
    ans <<= (fa[i] == i), ans %= 1000000007;

  printf("%d\n", ans);

  return 0;
}
```

---

## 作者：enucai (赞：1)

## C - Guessing Permutation for as Long as Possible

首先转化题意，我们把给出的序列看成一个无向图，边有边权，即为询问这一对点的时间戳。

原问题等价于问你有多少种给无向图定向的方案数，使得没有一条有向边 $(u,v,w)$，存在一条 $u$ 到 $v$ 或 $v$ 到 $u$ 的路径，路径上的边权最大值小于 $w$（若有，那么就能在这一次询问前的值 $u$ 和 $v$ 的大小关系，不用进行这次询问）。

考虑若有一个 $(u,v,w)$ 不合法，必定存在一个点 $p$，使得路径上只经过 $u,v,p$。

证明：若经过超过 $3$ 个点，找到最前面的三个点 $x,y,z$，考虑这两个点之间的边权，若 $>\max(v_{x,y},v_{y,z})$，那么直接选 $x,y,z$ 就不合法，否则可以直接删去 $y$ 点。

于是枚举每个三元组，然后会产生一些约束条件，原问题类似于一个 2-SAT 的计数问题，直接带权并查集即可，令 $k$ 表示最后并查集连通块个数，答案为 $2^k$。

提交记录：[link](https://atcoder.jp/contests/agc059/submissions/37028961)。

---

## 作者：Acoipp (赞：0)

## 分析

首先对于一个询问 $a,b$，得到结果让小的数往大的数连边，如果在连边之前 $a,b$ 就可以从一个到达另外一个了那这个排列就是不合法的。

更进一步，发现我们只要对任意三个数限制就行了，如果在问 $b,c$ 的关系之前有 $b<a,a<c$ 或者 $b>a,a>c$ 就不行，一定得是 $a>b,a>c$ 或者 $a<b,a<c$ 才可以。

于是我们可以得到关于边的一些限制，这些限制形如 $a=0$ 则 $b=1$，这个可以用扩展域并查集判断是否有解并且得到方案数，就是 $2^{\frac {cnt} 2}$，$cnt$ 为扩展域并查集连通块个数。

这样做来对于每一种满足条件的图我们都能唯一构造出一个序列，因为构造出来的图一定没有环，并且每条边的方向都是确定的，所以这道题正确性没问题。

时间复杂度就是 $O(n^3)$，可能需要带一个并查集的常数。

## 代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define mod 1000000007
#define N 500005
#define M 505
using namespace std;
vector<int> op[M];
struct node{int x,y;}p[N];
int n,m,i,j,k,dp[M][M],ans,id[M][M],fath[N],vis[N],tot,t1,t2,t3;
inline int gf(int x){return x==fath[x]?x:fath[x]=gf(fath[x]);}
inline int qmi(int a,int b,int p){
	int res = 1%p,t = a;
	while(b){
		if(b&1) res=1ll*res*t%p;
		t=1ll*t*t%p;
		b>>=1;
	}
	return res;
}
inline char nc(){
	static char buf[1000000],*p=buf,*q=buf;
	return p==q&&(q=(p=buf)+fread(buf,1,1000000,stdin),p==q)?EOF:*p++;
}
inline int read(){
	int res = 0;
	char c = nc();
	while(c<'0'||c>'9')c=nc();
	while(c<='9'&&c>='0')res=res*10+c-'0',c=nc();
	return res;
}
int main(){
	n=read(),m=n*(n-1)/2;
	for(i=1;i<=m;i++){
		p[i].x=read(),p[i].y=read();
		if(p[i].x>p[i].y) swap(p[i].x,p[i].y);
		dp[p[i].x][p[i].y]=i;
	}
	for(i=1;i<=n;i++) for(j=i+1;j<=n;j++) id[i][j]=++tot,fath[tot]=tot;
	for(i=1;i<=n;i++) for(j=1;j<i;j++) id[i][j]=id[j][i]+tot,fath[id[j][i]+tot]=id[j][i]+tot;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			for(k=i+1;k<=n;k++){
				if(i==j||j==k) continue;
				if(i<j) t1=dp[i][j];
				else t1=dp[j][i];
				if(j<k) t2=dp[j][k];
				else t2=dp[k][j];
				if(i<k) t3=dp[i][k];
				else t3=dp[k][i];
				if(t1<t3&&t2<t3){
					if(gf(id[i][j])==gf(id[j][k])||gf(id[j][i])==gf(id[k][j])){
						cout<<0<<endl;
						return 0;
					}
					fath[gf(id[i][j])]=gf(id[k][j]);
					fath[gf(id[j][i])]=gf(id[j][k]);
				}
			}
		}
	}
	for(i=1;i<=tot*2;i++) if(!vis[gf(i)]) ans++,vis[gf(i)]=1;
	cout<<qmi(2,ans/2,mod)<<endl;
	return 0;
} 
```

---

## 作者：Phartial (赞：0)

如果一个排列 $P$ 不合法，说明我们在某次询问 $(A_k,B_k)$ 时已经知道了 $P_{A_k},P_{B_k}$ 的大小关系，而这相当于我们在之前的询问中得到了一条推理链，形如 $P_{A_k}<P_{e_1}<P_{e_2}<\cdots<P_{e_m}<P_{B_k}$ 或 $P_{A_k}>P_{e_1}>P_{e_2}>\cdots>P_{e_m}>P_{B_k}$，且询问 $(A_k,e_1),(e_1,e_2),\cdots,(e_m,B_k)$ 都在 $(A_k,B_k)$ 之前。

然后是一步较为 tricky 的处理：考察这条推理链的前三项（$A_k,e_1,e_2$），如果询问 $(A_k,e_2)$ 在 $(A_k,e_1),(e_1,e_2)$ 之后，那么我们在询问 $(A_k,e_2)$ 时必然已经知道 $P_{A_k},P_{e_2}$ 的大小关系，从而得到另一条说明 $P$ 不合法的长为 $3$ 的推理链（$A_k,e_1,e_2$）。否则，我们可以使用 $A_k,e_2$ 代替推理链中的 $A_k,e_1,e_2$，从而使推理链长度减一。

归纳可得一个排列 $P$ 不合法当且仅当存在长度为 $3$ 的推理链，不妨设其为 $a,b,c$，则需要有 $(a,b),(b,c)$ 在 $(a,c)$ 之前。为使此推理链不成立，需要有 $P_a<P_b\iff P_c<P_b$ 且 $P_b<P_a\iff P_b<P_c$。

使用并查集不难维护出这些约束的等价类，对于两个约束 $P_i<P_j$ 和 $P_j<P_i$，若它们处于同一个等价类，则无解；否则我们可以任意选择这两个等价类中的一个，答案为 $2^{\text{等价类个数}/2}$。

```cpp
#include <iostream>
#include <atcoder/all>

using namespace std;

const int kN = 401;

int n, p[kN][kN]; 

int I(int i, int j) { return (i - 1) * n + j - 1; }

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1, x, y; i <= n * (n - 1) / 2; ++i) {
    cin >> x >> y;
    p[x][y] = p[y][x] = i;
  }
  atcoder::dsu d(n * n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      for (int k = 1; k <= n; ++k) {
        if (p[i][j] < p[i][k] && p[j][k] < p[i][k]) {
          d.merge(I(i, j), I(k, j));
          d.merge(I(j, i), I(j, k));
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i != j && d.leader(I(i, j)) == d.leader(I(j, i))) {
        cout << 0;
        return 0;
      }
    }
  }
  cout << atcoder::pow_mod(2, (d.groups().size() - n) / 2, 1e9 + 7);
  return 0;
}
```

---

