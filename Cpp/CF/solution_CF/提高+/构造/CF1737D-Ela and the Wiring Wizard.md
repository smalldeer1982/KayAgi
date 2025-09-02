# Ela and the Wiring Wizard

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737D/29746d080ff15dbf0ef0ecbc5ee000e146ff3f39.png)Ela needs to send a large package from machine $ 1 $ to machine $ n $ through a network of machines. Currently, with the network condition, she complains that the network is too slow and the package can't arrive in time. Luckily, a Wiring Wizard offered her a helping hand.

The network can be represented as an undirected connected graph with $ n $ nodes, each node representing a machine. $ m $ wires are used to connect them. Wire $ i $ is used to connect machines $ u_i $ and $ v_i $ , and has a weight $ w_i $ . The aforementioned large package, if going through wire $ i $ , will move from machine $ u_i $ to machine $ v_i $ (or vice versa) in exactly $ w_i $ microseconds. The Wiring Wizard can use his spell an arbitrary number of times. For each spell, he will choose the wire of index $ i $ , connecting machine $ u_i $ and $ v_i $ , and rewire it following these steps:

- Choose one machine that is connected by this wire. Without loss of generality, let's choose $ v_i $ .
- Choose a machine that is currently connecting to $ v_i $ (including $ u_i $ ), call it $ t_i $ . Disconnect the wire indexed $ i $ from $ v_i $ , then using it to connect $ u_i $ and $ t_i $ .

The rewiring of wire $ i $ will takes $ w_i $ microseconds, and the weight of the wire will not change after this operation. After a rewiring, a machine might have some wire connect it with itself. Also, the Wiring Wizard has warned Ela that rewiring might cause temporary disconnections between some machines, but Ela just ignores it anyway. Her mission is to send the large package from machine $ 1 $ to machine $ n $ as fast as possible. Note that the Wizard can use his spell on a wire zero, one, or many times. To make sure the network works seamlessly while transferring the large package, once the package starts transferring from machine $ 1 $ , the Wiring Wizard cannot use his spell to move wires around anymore.

Ela wonders, with the help of the Wiring Wizard, what is the least amount of time needed to transfer the large package from machine $ 1 $ to $ n $ .

## 说明/提示

Here is the graph in the first test case in the sample input:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737D/540d89f9584c578ad4d93a9554e38b995fff3695.png)Ela can ask the Wiring Wizard to use his spell on wire with the index of $ 7 $ , which is connecting machines $ 2 $ and $ 3 $ . Then, since the machine $ 8 $ is connected to machine $ 3 $ , the Wiring Wizard can disconnect wire $ 7 $ from machine $ 3 $ and connect it to machine $ 8 $ in $ 3 $ microseconds (weight of wire $ 3 $ ).

After that, the package can be sent from machine $ 1 $ to machine $ 8 $ in $ 6 $ microseconds. Therefore, the answer is $ 3 + 6 = 9 $ microseconds.

Here is the graph in the third test case in the sample input:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737D/47c58fe9b12d8c5ff0f0d959069226d0ab2ba121.png)

## 样例 #1

### 输入

```
3
8 9
1 2 3
6 4 5
3 5 6
6 1 3
7 4 4
3 8 4
2 3 3
7 8 5
4 5 2
4 5
1 2 1
2 4 1
3 4 1
3 1 1
1 3 2
8 8
4 6 92
7 1 65
6 5 43
6 7 96
4 3 74
4 8 54
7 4 99
2 5 22```

### 输出

```
9
2
154```

# 题解

## 作者：joke3579 (赞：11)

可以发现最优决策肯定是把一条边 $(u_i,v_i,w_i)$ 一直挪到成为 $(1,n)$，证明考虑反证法。这样的代价是 $w_i\times ([\text{挪动次数}] + 1)$ 的。
因此我们可以枚举边来更新答案。  
问题转化成：给定一条边，求挪动次数最小值。

首先我们可以发现，挪动次数与边权无关，因此我们可以首先将原图上的边权置为 $1$，得到一张新图。  
随后我们可以发现，一个端点 $u$ 移动到 $v$ 的最小移动次数是 $u,v$ 在新图上的最短路长度。因此首先在新图上跑一遍 floyed 算法得到两点间最短路 $dis(u,v)$。

然后分情况讨论 $(u,v)$ 边的挪动次数：
1. 两点分别走到 $1,n$ 两点。  
	例：$dis(u,1) + dis(v,n)$
    
2. 枚举中转点 $j$。其中一个点走到 $j$ 点，随后让另一个点一步挪动到 $j$ 点，再分别走到 $1,n$ 两点。这里的中转点可以是 $1/n$ 。   
	例：$dis(u,j) + 1 + dis(j,1) + dis(j,n)$

预处理复杂度 $O(n^3)$，枚举边并判断复杂度 $O(nm)$。

$\text{code : }$

```cpp
int T, n, m, t1, t2;
ll ans;
struct {int u, v, w;} e[N];
int g[501][502];

int main() {
	get(T);
	while (T--) {
		get(n, m); rep(i,1,n) rep(j,1,n) if (i != j) g[i][j] = inf; ans = infll;
		rep(i,1,m) get(e[i].u, e[i].v, e[i].w), g[e[i].u][e[i].v] = g[e[i].v][e[i].u] = 1;
		rep(k,1,n) rep(i,1,n) rep(j,1,n) g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		rep(i,1,m) {
			int now = min( {g[1][e[i].u] + g[e[i].v][n], g[1][e[i].v] + g[e[i].u][n]} );
			rep(j,1,n) now = min( {now, g[e[i].u][j] + 1 + g[1][j] + g[j][n], g[e[i].v][j] + 1 + g[1][j] + g[j][n]} );
			ans = min(ans, 1ll * e[i].w * (now + 1));
		} cout << ans << '\n';
	}
}
```

---

## 作者：LinkZelda (赞：6)

一道很妙的题。

我们考虑肯定存在一种最优的走法是让某一条边变成连接 $1$ 和 $n$ 然后走这条边。因为如果这不是最优的，那么这条路径上必然存在另一条更短的边，那我们换成用这条更短的边走就行（用这条短边肯定好过用原来那条长边）。

于是问题就变成让一条边两个端点在图上走，可以走自己，（分别到达 $1$ 和 $n$ 的步数 $+1$）乘以边权的最小值。

设两点 $u,v$ 最短路为 $dis_{u,v}$，这里的图是原图把所有边权改成 $1$ 后得到的图。然后分类讨论一下每条边 $(x,y)$：

- 两个端点分别直接走到 $1$ 和 $n$，即 $\min(dis_{x,1}+dis_{y,n},dis_{x,n}+dis_{y,1})$。

- 枚举中间点 $k$，一个端点走到某个中间点 $k$，然后另一个端点走自己这条边使得两个点都在 $k$ 上然后分别走到 $1$ 和 $n$，即 $\min(dis_{x,k}+1+dis_{k,1}+dis_{k,n},dis_{y,k}+1+dis_{k,1}+dis_{k,n})$

我们跑一下 floyd，然后枚举每条边求一下答案即可。$O(n^3+nm)$。

[代码](https://www.luogu.com.cn/paste/m11ef56k)。

---

## 作者：TernaryTree (赞：5)

有趣题。

首先注意到，一次操作某种意义上相当于，将两条相邻的边中较大的边权改为较小的边权。而显然不能简单地将全图边权直接像这样改为最小的那个，因为我们不一定要走完全图，我们只需要走一条路径。

考虑这样一条路径上的边权最小的边。我们可以将其不断地操作，类似一个一个点地吃掉，使得最后这条边吃到能直接连接 $1\to n$。形式化地，假设路径为 $1 \to p_1\to p_2\to p_3\to\dots\to p_k\to n$，要扩展的边为 $p_x\to p_{x+1}$，则可以通过操作 $(p_{x-1},p_{x},p_{x+1})$ 得到与原边相同边权的 $p_{x-1}\to p_{x+1}$，或者通过操作 $(p_{x},p_{x+1},p_{x+2})$ 得到 $p_{x}\to p_{x+2}$，这时路径上就可以去掉一个点，反复操作使得原路径变为 $1\to n$。这里我们发现答案是 $\min w_i\times(dis_{1,u_i}+dis_{v_i,n}+1)$，其中 $dis$ 表示两点不考虑边权的最短路，即最少边数，floyd 跑一遍就能算。上面那个式子，$u_i,v_i$ 还要反过来计算一次。

写出来上面那个式子，你会愉快地发现你样例都过不去。考虑这样一个东西：

```
1
6 5
2 3 1
3 4 114514
4 5 114514
5 6 114514
1 5 114514
```

显然这个时候边权为 $114514$ 的边都无法构成最优解，关键放在我们的边权为 $1$ 的点上。仔细观察题目，可以发现 $u,t$ 可以相同，这意味着我们可以“牵一发而动全身”，找一个中转点，将一个端点先挪过去，然后再走自己这条边把 $v$ 也挪过去。只需要挪一个点再加上 $1$，总代价大概少了一半！这时你还有这条边吗？如有！反正自环也是边，继续操作也行。于是我们枚举一个中转点，然后两个端点再从这个中转点分家分别去 $1,n$。这里操作的次数是 $\min_{k=1}^n \min(dis_{u,k},dis_{v,k})+1+dis_{1,k}+dis_{k,n}$，计算答案同理，加一再乘上边权。

然后这题就做完啦。时间复杂度 $\Theta(n^3+nm)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 5e2 + 10;
const int inf = 1e15;

struct edge { int u, v, w; };
int T, n, m;
int dis[maxn][maxn];
edge e[maxn * maxn];

signed main() {
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) dis[i][j] = inf * (i != j);
		for (int i = 1, u, v, w; i <= m; i++) cin >> u >> v >> w, e[i] = {u, v, w}, dis[u][v] = dis[v][u] = 1;
		for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
		int ans = inf;
		for (int i = 1; i <= m; i++) {
			int u = e[i].u, v = e[i].v, cur = min(dis[u][1] + dis[v][n], dis[v][1] + dis[u][n]);
			for (int k = 1; k <= n; k++) cur = min(cur, min(dis[u][k], dis[v][k]) + 1 + dis[k][1] + dis[k][n]);
			ans = min(ans, (cur + 1) * e[i].w);
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：jamesharden666 (赞：1)

考场上想到了答案一定是由一条边扩展出来的，但是没打出来，遂挂。

我们将原图上的边权全部设为 $1$，然后跑一遍 Floyd，得出两点之间的最短距离 $a_{u,v}$。

对于每一条边（ $w_{i,j}$ 为这条边的边权），有两种方式给答案做贡献。

第一种：

两个端点直接扩展到 $1,n$。

对应的方程式：$ans=\min(ans,w_{i,j} \times (a_{i,1}+a_{j,n}+1)) $。

第二种：

当 $1,n$ 在两个端点的同侧时，我们就需要枚举一个中转点，先将一端扩展到中转点，在用一次操作形成自环后即可同上操作了。

对应的方程式：$ans=\min(ans,w_{i,j}\times (a_{i,k}+a_{k,1}+a_{k,n}+2)) $ 。

总时间复杂度为 $\mathcal O(n^3)$。

代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500+10;
int t,n,m;
long long a[N][N],w[N][N];
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
        s=s*10+(ch-'0'),ch=getchar();
    return s*w;
}
int main()
{
    t=read();
    while(t--)
    {
        n=read(),m=read();
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                a[i][j]=w[i][j]=1e12;
        for(int i=1;i<=m;++i)
        {
            int u=read(),v=read(),val=read();
            a[u][v]=a[v][u]=1;
            w[u][v]=min(w[u][v],1ll*val);
            w[v][u]=min(w[v][u],1ll*val); 
        }
        for(int i=1;i<=n;++i)
            a[i][i]=w[i][i]=0;
        for(int k=1;k<=n;++k)
            for(int i=1;i<=n;++i)
                for(int j=1;j<=n;++j)
                    a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
        long long ans=LONG_LONG_MAX;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                if(w[i][j]!=1e12&&i!=j)
                {
                    ans=min(ans,w[i][j]*(a[i][1]+a[j][n]+1));
                    for(int k=1;k<=n;++k)
                        ans=min(ans,w[i][j]*(a[i][k]+a[k][1]+a[k][n]+2));
                }
        printf("%lld\n",ans);
    }
    return 0;
}  
```

---

## 作者：_iridescent (赞：0)

### 思路
首先可以发现，对于这道题我们最优的策略就是选择某一条的边，令其逐渐扩展到最后的连接 $1$ 和 $n$。

由于本题点的数量较小（$n \le 500$），可以先不考虑边权跑一遍 floyd，算出两两点之间的距离 $d_{i,j}$。接下来再枚举以点 $i$ 和 $j$ 的连边为初始边时所需的时间：

若 $1$ 和 $n$ 恰好分别在边 $d_{i,j}$ 的两侧，此时只需要向 $1$ 的方向操作 $d_{i,1}$ 次，向 $n$ 的方向操作 $d_{j,n}$ 次，就能得到我们期望的边，此时需花费的代价（注意还有操作完传送那一次的花费）是 $val_{i,j} \times (d_{i,1}+d_{j,n}+1)$。

若 $1$ 和 $n$ 在边 $d_{i,j}$ 的同侧，此时需要枚举一个中转点 $k$，先操作 $d_{i,k}$ 次把当前边“移”到中转点 $k$，再将其向两边拓展到点 $1$ 和 $n$。此时需要花费的代价是 $val_{i,j} \times (d_{i,k}+d_{k,1}+d_{k,n}+2)$。

最后记录下最小的代价 $ans$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=505,inf=1e11;
int T,n,m,ans=inf;
int val[N][N],d[N][N];
signed main(){
//	freopen("CF1737D.in","r",stdin);
//	freopen("mamba.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;ans=1e18;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)val[i][j]=d[i][j]=(i==j?0:inf);
		}
		for(int i=1;i<=m;i++){
			int u,v,w;
			cin>>u>>v>>w;
			val[u][v]=val[v][u]=min(val[u][v],w);
			d[u][v]=d[v][u]=1;
		}
		for(int k=1;k<=n;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i!=j&&val[i][j]!=inf){
					if(val[i][j]*(d[i][1]+d[j][n]+1)<0)continue;
					ans=min(ans,val[i][j]*(d[i][1]+d[j][n]+1));
					for(int k=1;k<=n;k++){
						if(d[i][k]==inf||d[k][1]==inf||d[k][n]==inf)continue;
						ans=min(ans,val[i][j]*(d[i][k]+d[k][1]+d[k][n]+2));						
					}
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

不知道哪个唐氏在模拟赛这个题挂了。

显然注意不到题解里的所有性质，从头开始。

手摸样例可以发现，一条路径的权值是路径中边长的最小值乘路径长度。

但是这样子是过不了样例的，观察第二组样例，发现是把一个原来不在路径上的边弄到路径上点的自环上，然后再放到路径中对答案产生贡献。

观察一下可以发现，步数最多是 $\mathcal{O}(n)$ 的，把边移到自环上 $n$ 步；最后走 $n$ 步，所以上界是 $2n+eps$ 步。

$f_{stp,i}$ 表示走了 $stp$ 步，走到 $i$ 这个点 $1\to i$ 的路径上最短的边的长度。$h_{stp,i}$ 表示走了 $stp$ 步，需要把一个自环移到 $i$ 上需要多少步。

如果 $i,j$ 有边 $mp_{i,j}$，则 $f_{stp,j}\leftarrow \min(f_{stp-1,i},mp_{i,j}),h_{1,j}\leftarrow mp_{i,j}$，其中 $\leftarrow $ 表示取 $\min$。

对于 $i$ 更新 $i$，需要初始化 $f,h$，以及用 $h$ 更新 $f$。在此不再赘述，方程可以看代码。

特别地，$f_{*,1}$ 有点特殊，需要额外初始化一下。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 505, inf = 0x3f3f3f3f;
int T, n, m, mp[N][N], x, y, z, f[N << 1][N];
int h[N << 1][N];
ll ans;
bool flg;
inline void chkmin(int &x, int y){
	if(x > y) x = y;
}
inline void chkmin(ll &x, ll y){
	if(x > y) x = y;
}
signed main(){
//	freopen("data.in", "r", stdin);
//	freopen("travel.out", "w", stdout);
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		ans = 0x3f3f3f3f3f3f3f3f;
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n * 2 + 2; j++){
				h[j][i] = inf;
				f[j][i] = inf;
			}
			for(int j = 1; j <= n; j++){
				mp[i][j] = inf;
			}
		}
		for(int i = 1; i <= m; i++){
			scanf("%d%d%d", &x, &y, &z);
			chkmin(mp[x][y], z);
			chkmin(mp[y][x], z);
		}
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				chkmin(h[1][i], mp[i][j]);
			}
		}
//		for(int j = 1; j <= n; j++){
//			printf("h[%d][%d] = %d\n", 1, j, h[1][j]);
//		}
		for(int s = 2; s <= 2 * n + 2; s++){
			for(int i = 1; i <= n; i++){
				for(int j = 1; j <= n; j++){
					if(mp[i][j] ^ inf) chkmin(h[s][j], h[s - 1][i]);
				}
			}
//			for(int j = 1; j <= n; j++){
//				printf("h[%d][%d] = %d\n", s, j, h[s][j]);
//			}
		}
		for(int i = 1; i <= n; i++){
			f[1][i] = mp[1][i];
		}
		if(f[1][n] ^ inf) chkmin(ans, 1ll * f[1][n]);
//		for(int i = 1; i <= n; i++){
//			printf("f[%lld][%lld] = %lld\n", 1, i, f[i]);
//		}
		for(int s = 2; s <= 2 * n + 2; s++){
			f[s][1] = h[s - 1][1];
		}
		for(int s = 2; s <= 2 * n + 2; s++){
			for(int i = 1; i <= n; i++){
				for(int j = 1; j < s - 1; j++){
					if(f[s - j - 1][i] == inf) continue ;
					chkmin(f[s][i], h[j][i]);
				}
				if(f[s - 1][i] == inf) continue ;
				for(int j = 1; j <= n; j++){
					if(mp[i][j] == inf) continue ;
					chkmin(f[s][j], min(f[s - 1][i], mp[i][j]));
				}
			}
			if(f[s][n] ^ inf) chkmin(ans, 1ll * f[s][n] * s);
//			for(int i = 1; i <= n; i++){
//				printf("f[%lld][%lld] = %lld\n", s, i, f[s][i]);
//			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

