# Christmas Game

## 题目描述

Alice and Bob are going to celebrate Christmas by playing a game with a tree of presents. The tree has $ n $ nodes (numbered $ 1 $ to $ n $ , with some node $ r $ as its root). There are $ a_i $ presents are hanging from the $ i $ -th node.

Before beginning the game, a special integer $ k $ is chosen. The game proceeds as follows:

- Alice begins the game, with moves alternating each turn;
- in any move, the current player may choose some node (for example, $ i $ ) which has depth at least $ k $ . Then, the player picks some positive number of presents hanging from that node, let's call it $ m $ $ (1 \le m \le a_i) $ ;
- the player then places these $ m $ presents on the $ k $ -th ancestor (let's call it $ j $ ) of the $ i $ -th node (the $ k $ -th ancestor of vertex $ i $ is a vertex $ j $ such that $ i $ is a descendant of $ j $ , and the difference between the depth of $ j $ and the depth of $ i $ is exactly $ k $ ). Now, the number of presents of the $ i $ -th node $ (a_i) $ is decreased by $ m $ , and, correspondingly, $ a_j $ is increased by $ m $ ;
- Alice and Bob both play optimally. The player unable to make a move loses the game.

For each possible root of the tree, find who among Alice or Bob wins the game.

Note: The depth of a node $ i $ in a tree with root $ r $ is defined as the number of edges on the simple path from node $ r $ to node $ i $ . The depth of root $ r $ itself is zero.

## 说明/提示

Let us calculate the answer for sample input with root node as 1 and as 2.

Root node 1

Alice always wins in this case. One possible gameplay between Alice and Bob is:

- Alice moves one present from node 4 to node 3.
- Bob moves four presents from node 5 to node 2.
- Alice moves four presents from node 2 to node 1.
- Bob moves three presents from node 2 to node 1.
- Alice moves three presents from node 3 to node 1.
- Bob moves three presents from node 4 to node 3.
- Alice moves three presents from node 3 to node 1.

Bob is now unable to make a move and hence loses.

Root node 2

Bob always wins in this case. One such gameplay is:

- Alice moves four presents from node 4 to node 3.
- Bob moves four presents from node 5 to node 2.
- Alice moves six presents from node 3 to node 1.
- Bob moves six presents from node 1 to node 2.

Alice is now unable to make a move and hence loses.

## 样例 #1

### 输入

```
5 1
1 2
1 3
5 2
4 3
0 3 2 4 4```

### 输出

```
1 0 0 1 1```

# 题解

## 作者：bellmanford (赞：7)

显然的树上阶梯博弈。

首先，对于 $de_u \mod k=i$ 的节点可以分在一个游戏中，总的 $SG$ 值就是这 $k$ 个游戏的 $SG$ 值的异或和。

对于每个游戏，可以发现需要移动偶数次才会结束的点是毫无用处的，因为一旦移动到奇数位，对手可以再次移动到偶数位，将移动到偶数看做删除，就变为了奇数位上的 $Nim$ 游戏了，那么 $SG$ 就应该是奇数位上的 $a_i$ 的异或和。

设 $dp_{u,i,j}$ 为以 $u$ 为根， $de_v\mod k =i$ 且, $\left\lfloor\frac{de_v}{k}\right\rfloor \mod 2 =j$ 的 $a_v$ 的异或和 ，然后换根 dp 即可，复杂度 $\mathcal{O(nk)}$ 。

考场上的丑陋代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
const int M=1e5+5;
 
int max(int x,int y){ return x>y?x:y; }
int min(int x,int y){ return x<y?x:y; }
 
int n,K,a[M];
int read(){
	int x=0,y=1;char ch=getchar();
	while(ch<'0'||ch>'9') y=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*y;
}
 
int tot=0,first[M];
struct Edge{ int nxt,to; }e[M<<1];
void add(int x,int y){
	e[++tot]=(Edge){first[x],y},first[x]=tot;
	e[++tot]=(Edge){first[y],x},first[y]=tot;
}
 
int dp[M][25][2];
void dfs(int u,int fa){
	dp[u][0][0]=a[u];
	for(int i=first[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa) continue ;
		dfs(v,u);
		for(int j=0;j<K;j++){
			for(int k=0;k<2;k++){
				int nj=j,nk=k;
				nj++;
				if(nj>=K) nj-=K,nk^=1;
				dp[u][nj][nk]^=dp[v][j][k];
			}
		}
	}
}
int tmp[25][2];
void dfs2(int u,int fa){
	if(u!=1){
		for(int j=0;j<K;j++) for(int k=0;k<2;k++) tmp[j][k]=dp[fa][j][k];
		for(int j=0;j<K;j++){
			for(int k=0;k<2;k++){
				int nj=j,nk=k;
				nj++;
				if(nj>=K) nj-=K,nk^=1;
				tmp[nj][nk]^=dp[u][j][k];
			}
		}
		for(int j=0;j<K;j++){
			for(int k=0;k<2;k++){
				int nj=j,nk=k;
				nj++;
				if(nj>=K) nj-=K,nk^=1;
				dp[u][nj][nk]^=tmp[j][k];
			}
		}
	}
	for(int i=first[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa) continue ;
		dfs2(v,u);
	}
}
 
void solve(){
	n=read(),K=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add(x,y);
	}
	for(int i=1;i<=n;i++) a[i]=read();
	dfs(1,0),dfs2(1,0);
	for(int i=1;i<=n;i++){
		int Ans=0;
		for(int j=0;j<K;j++) Ans^=dp[i][j][1];
		if(Ans==0) printf("0 ");
		else printf("1 ");
	}
	printf("\n");
}
 
signed main(){
	solve();
}
```

---

## 作者：睿智的憨憨 (赞：3)

## 解法分析

看完题就想到了 Nim 取石子。当深度小于 $k$ 时完全动不了，当深度在 $[k,2k)$ 时相当于 Nim 取一堆石子，$SG(i)=a_i$。而深度在 $[2k,3k)$ 时先手挪一次，后手就再挪一次使其作废，因此先手必败，$SG(i)=0$。

所以我们发现了只有在深度模 $2k$ 的余数为 $[k,2k)$ 时才有 $SG(i)=a_i$，否则 $SG(i)=0$。问题转化为求以每个点为根时深度模 $2k$ 的余数为 $[k,2k)$ 的点的点权异或和。换根 dp 即可。

## 参考代码

```
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pushf push_front
#define pushb push_back
#define popf pop_front
#define popb pop_back
#define lowbit(x) (x-(x&(x-1)))
using namespace std;
const int N = 100010;

int n, K, f[N][45], g[N][45];
vector<int> e[N];
bool ans[N];

void dfs(int u, int pr){
	for (int v : e[u])
		if (v != pr){
			dfs(v, u);
			for (int i = 0; i < 2 * K; i++)
				f[u][i] ^= f[v][(i - 1 + 2 * K) % (2 * K)];
		}
}
void dps(int u, int pr){
	for (int i = 0; i < 2 * K; i++)
		g[u][i] = f[u][i];
	if (pr)
		for (int i = 0; i < 2 * K; i++)
			g[u][i] ^= g[pr][(i - 1 + 2 * K) % (2 * K)] ^ f[u][(i - 2 + 2 * K) % (2 * K)];
	int SG = 0;
	for (int i = K; i < 2 * K; i++)
		SG ^= g[u][i];
	if (SG)
		ans[u] = true;
	for (int v : e[u])
		if (v != pr)
			dps(v, u);
}

int main(){
	scanf("%d %d", &n, &K);
	for (int i = 1, u, v; i < n; i++){
		scanf("%d %d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &f[i][0]);
	dfs(1, 0);
	dps(1, 0);
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：云浅知处 (赞：3)

注意不到，当以某个点为根时，$\text{dep}_x\bmod k$ 不同的点相互独立。

接下来，只需要解决这样的问题：

> 有 $m$ 堆石子，分别有 $x_1,x_2,\cdots ,x_m$ 个，每次你可以选一个 $i$（$1<i\le m$），并从第 $i$ 堆中移动 $k$（$1\le k\le x_i$）枚石子到第 $i-1$ 堆中，或从第一堆中选若干石子扔掉。
>
> 无法行动的人输，问先后手谁赢谁输。

还是注意不到，偶数位置的石子等价于没有。这是因为，如果先手在某个偶数位置进行了一次操作，那么后手可以直接把它再移回偶数位置，这样奇数位置的形态不变，先后手不变。进而可以推出，偶数位置等价于根。

那么在奇数位上进行一次操作，就等价于直接移动到根，发现转化为 $\text{nim}$ 游戏。

考虑设 $f(u,j,0/1)$ 表示只考虑 $u$ 的子树，$\text{dep}\bmod k=j$，且 $\lfloor\text{dep}/k\rfloor\bmod 2=0/1$ 的所有点的 $\text{xor}$ 和。

如何转移？考虑某个 $d=qk+r$，只有 $r=k-1$ 则 $q$ 的奇偶性会发生改变。因此有
$$
f(u,j,c)\leftarrow f(v,j-1,c),j\neq 0\\
f(u,0,c)\leftarrow f(v,k-1,1-c)
$$
显然具有可减性，换根是容易的。总的复杂度为 $O(nk)$。

<https://codeforces.com/contest/1498/submission/188981083>

---

## 作者：daniEl_lElE (赞：1)

考虑阶梯博弈，$\text{SG}$ 函数值为奇数距离的异或值。

考虑换根 dp，$dp_{i,j}$ 表示 $i$ 位置，距离 $\bmod\ 2k$ 为 $j$ 的所有点的异或和。移一位转移即可。

总复杂度为 $O(nk)$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int n,k;
vector<int> vc[1000005];
int a[1000005];
int dp[1000005][41],ans[1000005];
void dfs1(int now,int fa){
	dp[now][0]^=a[now];
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs1(v,now);
		for(int i=0;i<2*k;i++) dp[now][(i+1)%(2*k)]^=dp[v][i];
	} 
}
void dfs2(int now,int fa){
	for(int i=k;i<2*k;i++) ans[now]^=dp[now][i];
	for(auto v:vc[now]){
		if(v==fa) continue;
		for(int i=0;i<2*k;i++) dp[now][(i+1)%(2*k)]^=dp[v][i];
		for(int i=0;i<2*k;i++) dp[v][(i+1)%(2*k)]^=dp[now][i];
		dfs2(v,now);
		for(int i=0;i<2*k;i++) dp[v][(i+1)%(2*k)]^=dp[now][i];
		for(int i=0;i<2*k;i++) dp[now][(i+1)%(2*k)]^=dp[v][i];
	}
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	for(int i=1;i<=n;i++) cin>>a[i];
	dfs1(1,0),dfs2(1,0);
	for(int i=1;i<=n;i++) cout<<(ans[i]>=1)<<" ";
	return 0;
}

```

---

## 作者：7KByte (赞：1)

先考虑$k=1$的菊花图。

不难发现除了重心，其他节点都需要移到重心且直接移到重心，这就是$\rm Nim$游戏，直接对所有节点取$\rm xor$即可判断胜负。

考虑$k=1$的一般情况。对于深度为偶数的节点，移动到根必定经过偶数次。那么对于深度为偶数上的节点，一个人移动一次到奇数节点上，另一个人立即再移动一次到偶数节点上，而根节点深度为 $0$ ，所以偶数节点上的权值等价于根节点上的权值，可以不用考虑。

而深度为奇数的节点移动一次到偶数节点，这等价于移动一次到根。所以这仍然是$\rm Nim$游戏，我们将深度为奇数的节点权值异或起来即可。

对于$k\neq 1$，我们将原来的深度$\rm dep$等价于$\rm \left\lfloor\dfrac{dep}{k}\right\rfloor$。

求出每个节点为根的情况？换根即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
using namespace std;
int h[N],tot,n,k,a[N],ans[N];
struct edge{
	int to,nxt;
}e[N<<1];
void add(int x,int y){e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;}
int f[N][40];
void dfs(int x,int y){
	f[x][0]^=a[x];
	for(int i=h[x];i;i=e[i].nxt)if(e[i].to!=y){
		dfs(e[i].to,x);
		rep(j,0,2*k-1)f[x][(j+1)%(2*k)]^=f[e[i].to][j];
	}
}
void calc(int x,int fa){
	rep(i,k,2*k-1)ans[x]^=f[x][i];
	int g[40];
	for(int i=h[x];i;i=e[i].nxt)if(e[i].to!=fa){
		rep(j,0,2*k-1)g[(j+1)%(2*k)]=f[x][(j+1)%(2*k)]^f[e[i].to][j];
		rep(j,0,2*k-1)f[e[i].to][(j+1)%(2*k)]^=g[j];
		calc(e[i].to,x);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	rep(i,1,n-1){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	rep(i,1,n)scanf("%d",&a[i]);dfs(1,0);
	calc(1,0);rep(i,1,n)printf("%d ",ans[i]?1:0);
	return 0;
}
```

---

