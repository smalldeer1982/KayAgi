# Tree Destruction

## 题目描述

给定一棵有 $n$ 个顶点的树。你可以一次选择两个顶点 $a$ 和 $b$，然后删除从 $a$ 到 $b$ 路径上的所有顶点，包括顶点本身。如果选择 $a=b$，则只会移除一个顶点。


你的任务是找到从树中移除路径后可以形成的连接组件的最大数量。


树是一个没有环的连通图。


连通组件是一组顶点的集合，其中任何顶点都有一条沿边缘的路径到达集合中的任何其他顶点（不可能到达不属于该集合的顶点）。

## 样例 #1

### 输入

```
6
2
1 2
5
1 2
2 3
3 4
3 5
4
1 2
2 3
3 4
5
2 1
3 1
4 1
5 4
6
2 1
3 1
4 1
5 3
6 3
6
2 1
3 2
4 2
5 3
6 4```

### 输出

```
1
3
2
3
4
3```

# 题解

## 作者：Tomwsc (赞：2)

# CF2050G Tree Destruction 题解

## 题意

给定一棵树，可以删除一次任意两点之间的一条路径，问删除路径后剩下的连通块的数量最大为多少。

## 思路

很明显的树形 dp。

设 $dp_{u,0}$ 表示以 $u$ 号节点为根，路径不包含该节点的连通块的最大数量。

设 $dp_{u,1}$ 表示以 $u$ 号节点为根，并且 $u$ 为路径的一端点的连通块的最大数量。

设 $dp_{u,2}$ 表示以 $u$ 号节点为根，并且 $u$ 为路径中一点的连通块的最大数量。

下面开始推方程：

对于 $dp_{u.0}$：

考虑若删掉的路径不包含儿子节点，则儿子节点必然和父亲节点在一个连通块中；若路径包含儿子节点，则父亲节点必然属于一个新的连通块。
  
  所以得到：$dp_{u.0}=\max(dp_{v,0},dp_{v,1}+1,dp_{v,2}+1)$。

对于 $dp_{u,1}$：

因为父亲节点处于路径的一端点，所以儿子节点必然处于路径中。设 $u$ 有 $child$ 个子节点，则这一条路径将整棵子树分成了 $child-1$ 个连通块。

所以得到：$dp_{u,1}=\max(dp_{v,1}+child-1)$。

对于 $dp_{u,2}$：

因为父亲节点处于路径中，所以必有两个儿子节点也处在路径中。因为新加了一个子节点进入路径，所以连通块数量要减一。于是只需要找到最大的一个处于路径中的子节点和原本的 $dp_{u,1}$ 再减一即可。

所以得到：$dp_{u,2}=\max(dp_{u,1}+dp_{v,1}-1)$。

注意，在求 $dp_{u,2}$ 时需要用到 $dp_{u,1}$，为了避免经过 $u$ 的两个子节点为同一个，所以要先求 $dp_{u,2}$ 再求 $dp_{u,1}$。

## 代码

比较简单：
```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (1ll << 62)
using namespace std;
const int MAXN = 2e5 + 10;
int t;
int n;
vector<int>G[MAXN];
int dp[MAXN][3];

inline int max(int a , int b) {
	return a > b ? a : b;
}
 
void dfs(int u , int fa) {
	dp[u][0] = 0;
	int child = 0;
	for(auto v : G[u])
		if(v != fa)
			child ++;
	dp[u][1] = dp[u][2] = child;
	for(auto v : G[u]) {
		if(v == fa)
			continue;
		dfs(v , u);
		dp[u][0] = max(dp[u][0] , dp[v][0]);
		dp[u][0] = max(dp[u][0] , max(dp[v][1] , dp[v][2]) + 1);
		dp[u][2] = max(dp[u][2] , dp[u][1] + dp[v][1] - 1);
		dp[u][1] = max(dp[u][1] , dp[v][1] + child - 1);
	}
	return;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t --) {
		cin >> n;
		for(register int i = 1;i <= n;i ++)
			G[i].clear();
		for(register int i = 1;i < n;i ++) {
			int u , v;
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		if(n == 2) {
			cout << 1 << '\n';
			continue;
		}
		dfs(1 , 0);
		cout << max(dp[1][2] , max(dp[1][0] , dp[1][1])) << '\n';
	}
	return 0;
}
```

---

## 作者：Determination_Y (赞：2)

[Cnblogs](https://www.cnblogs.com/Sundar-2022/p/18591492)

### 【题意简述】

你有一棵树，你可以从里面删除一条链上的节点，问剩下的点的联通块数量最大是多少。

### 【思路】

一眼树形 dp，默认根为 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/0760rffn.png)

我们以这棵树的 $1$ 节点作为示例。

设 $dp_{i,0}$ 表示 $i$ 节点的子树中选一条链，$i$ 不在链上的最大联通块数。

设 $dp_{i,1}$ 表示 $i$ 节点的子树中选一条链，$i$ 在链端点的最大联通块数。

设 $dp_{i,2}$ 表示 $i$ 节点的子树中选一条链，$i$ 在链中间的最大联通块数。

* $dp_{i,0}$：$i$ 不在链上，意味着一定是 $i$ 的某一个子节点的子树内有一条链。

  * $dp_{son,0}$：当前儿子也不在链上，如图所示：

    ![](https://cdn.luogu.com.cn/upload/image_hosting/vm0m1f59.png)

    $2$ 节点不在红色链上，当前 $2$ 子树中有一个绿色联通块，发现带上 $1$ 号点之后联通块扩大，但是个数不变。

  * $dp_{son,1},dp_{son,2}$：当前儿子在链上，如图所示：

    ![](https://cdn.luogu.com.cn/upload/image_hosting/vqq2ugp4.png)

    $2$ 节点在红色链上，当前 $2$ 子树中有一个绿色联通块，发现带上 $1$ 号点之后联通块个数 +1。

* $dp_{i,1}$：$i$ 在链的端点，意味着

  * 这个子树内只有这一个点在链上，答案即为子树个数。

  * $i$ 的子节点有一个处于其子树中链的端点上，如图所示：

    ![](https://cdn.luogu.com.cn/upload/image_hosting/7vf1zv9j.png)

    $2$ 节点在红色链上，当前 $2$ 子树中有两个绿色联通块，连接 $1$ 号点之后联通块个数 +(子节点个数-1)。

* $dp_{i,2}$：$i$ 在链的中间，意味着

  * 有两个子节点处于其子树中链的端点上，如图所示：

    ![](https://cdn.luogu.com.cn/upload/image_hosting/hf2b8ocp.png)

    $2,3$ 节点在红色链上，当前 $2$ 子树中有两个绿色联通块，$3$ 子树中没用联通块，连接 $1$ 号点之后联通块个数 +(子节点个数-2)。

    选择联通块个数最大的两个子树连起来就好。

然后就很好写了。

### 【Code】

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int>Edge[200005];
int n,u,v,dp[200005][3];

void DFS(int u,int fa){
	int soncnt=0,max0=0,max1=0,sec1=0,max2=0;
	for(auto v:Edge[u]){
		if(v!=fa){
			DFS(v,u),soncnt++;
			max0=max(max0,dp[v][0]);
			max2=max(max2,dp[v][2]);
			if(dp[v][1]>max1){
				sec1=max1;
				max1=dp[v][1];
			}else if(dp[v][1]>sec1){
				sec1=dp[v][1];
			}
		}
	}
	dp[u][0]=max(max0,max(max1,max2)+1);
	dp[u][1]=max(soncnt,max1+(soncnt-1));
	dp[u][2]=max1+sec1+(soncnt-2);
} 

void Main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) dp[i][0]=dp[i][1]=dp[i][2]=0,Edge[i].clear();
	for(int i=1;i<=n-1;i++){
		scanf("%d%d",&u,&v);
		Edge[u].push_back(v);
		Edge[v].push_back(u);
	}
	DFS(1,0);
	printf("%d\n",max({dp[1][0],dp[1][1],dp[1][2]})); 
} 

int T;
int main()
{
	scanf("%d",&T);
	while(T--) Main();
	return 0;
}
```

### 【后记】

祝贺我自己，在上蓝前的最后一场 Div.3 AK。

两发罚时全是数组开小，乐。

以后就打不了了。

---

## 作者：AK_400 (赞：1)

考虑删掉一个点会发生什么：以它为根时它的所有子树独立为一个连通块。

删一条链时，端点的贡献少一个，其余点的贡献少两个（被删了且与其相邻），注意到端点的数量是固定为 $2$ 的，所以我们可以将端点的贡献减一，最后加回来。

现在题目转化为每个点的点权为其度数减二，求点权和最大是多少。

树形 dp 即可


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
vector<int>e[200005];
int mx[200005],mx2[200005],ans;
void dfs(int p,int f){
    int d=e[p].size()-2;
    mx[p]=mx2[p]=d;
    for(int x:e[p]){
        if(x==f)continue;
        dfs(x,p);
        if(mx[x]+d>=mx[p])mx2[p]=mx[p],mx[p]=mx[x]+d;
        else if(mx[x]+d>mx2[p])mx2[p]=mx[x]+d;
    }
    ans=max(ans,mx[p]+mx2[p]-d+2);
}
void slv(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)e[i].clear(),mx[i]=mx2[i]=0;
    ans=0;
    return;
}   
signed main(){
    int t;cin>>t;while(t--)
    slv();
    return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

# 思路
删掉一条路径有两种情况，一种是从一个点删到它的某个祖先，另一种情况是两个点一起删到它们的最近公共祖先。

考虑 DP，用 $f_i$ 表示以 $i$ 为根的子树中删掉一个点到 $i$ 的路径后连通块数的最大值。递推可以视作一个儿子为根删了之后再删当前结点，$s_i$ 表示 $i$ 的儿子集合，有递推
$$
f_i=\max_{j\in s_i}f_j+\text{card}(s_i)-1
$$
再考虑第二种情况，以 $g_i$ 表示 $g$ 为一条路径的顶点时删去这条路径后的最大连通块数，这种情况相当于从两个儿子的后代删到这两个儿子，再把这个结点删去，所以有
$$
g_i=\max_{j\in s_i}\max_{k\in s_i \wedge j\ne k} \text{card}(s_i)-2+f_j+f_k
$$
就是选定两个儿子子树进行第一种操作，其余儿子子树自成一个连通块。$\max(\max f,\max g$) 即为答案。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,q,u,v,f[200001],g[200001],ans,mx[200001][2];
vector<int>e[200001];
void sch(int u,int fa){
	f[u] = e[u].size() - bool(fa);//度数不等于儿子数，要考虑父亲结点
	for(auto v : e[u]){
		if(v == fa) continue;
		sch(v,u);
		f[u] = max(f[u],f[v] + int(e[u].size()) - 1 - bool(fa));//最大值更新
		if(f[v] > mx[u][0]) mx[u][1] = mx[u][0],mx[u][0] = f[v];//次大值更新
		else if(f[v] > mx[u][1]) mx[u][1] = f[v];
	} 
	g[u] = mx[u][0] + mx[u][1] + int(e[u].size()) - 2 - bool(fa);//取两个儿子的最大的 f
	ans = max(ans,max(f[u],g[u]) + bool(fa));
	return;
}
int main(){
	scanf("%d",&T);
	while(T --){
		ans = 1;
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++) e[i].clear(),mx[i][0] = mx[i][1] = 0;
		for(int i = 1;i < n;i ++){
			scanf("%d%d",&u,&v);
			e[u].push_back(v),e[v].push_back(u); 
		}
		sch(1,0);
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：Drifty (赞：1)

### Preface

好简单的 Div.3。好简单的 G。

### Solution

首先你会发现，由于这是一颗树，因此当你去掉 $a,b$ 之间的路径之后，所有与这个路径相连的所有的边对应的子树都会变成一个独立的连通块。那么问题就变成了求一个最大的链，这里链的权值定义为与这个链相连边的条数。

那么我们可以考虑用近似求直径的方法解决，具体地，记 $f_{u,0}$ 为以 $u$ 结束的最大链的权值，$f_{u,1}$ 为两个端点在 $u$ 的两个子树中最大链的权值，然后取个 $\max$ 就可以了。实现的时候会发现 $f_{u,1}$ 可以直接用最大值和次大值算，就不用了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int N = 2e5 + 7;
vector <int> e[N];
int n, T, f[N], g[N], ans;
void dfs(int u, int fa) {
    f[u] = (int)e[u].size();
    int ret = -1;
    for (auto v : e[u]) {
        if (v == fa) continue;
        dfs(v, u);
        int temp = f[v] + (int)e[u].size() - 2;
        if (temp > f[u]) ret = f[u], f[u] = temp;
        else if (temp > ret) ret = temp;
    }
    ans = max({ret + f[u] - (int)e[u].size(), f[u], ans});
}
void solve() {
    cin >> n; ans = -1;
    auto Add = [&](int u, int v) {e[u].push_back(v);};
    for (int i = 1; i <= n; i ++) e[i].clear();
    fill (f + 1, f + n + 1, 0);
    fill (g + 1, g + n + 1, 0);
    for (int i = 1, u, v; i < n; i ++)
        cin >> u >> v, Add(u, v), Add(v, u);
    dfs(1, 0);
    cout << ans << '\n';
}
int main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    cin >> T;
    while (T --) solve();
    return 0;
}

```

---

## 作者：OIer_Hhy (赞：0)

令某个子树个数 $\ge 2$ 的节点作为根 $root$。

令 $e_i$ 表示 $i$ 的子树数量，$f_i$ 表示删去 $i$ 到 $root$ 的路径后联通分量个数，$g_i$ 表示根为 $i$ 的子树中最大的 $f_i$。

状态转移：

$$f_{root}=e_{root}$$

$$f_{u}=f_{fa}+e_u-1$$

$$g_{u}=f_{u}$$

$$g_{fa}=\max(g_{fa},g_{u})$$

枚举每个 $i$ 作为子树的节点，选出子树中 $g$ 最大的 $j$ 和 $k$，$g_j+g_k-f_i$ 即为所求 $res_i$。

答案即为 $\max\{res_1,res_2,\cdots,res_n\}$。

[my code](https://codeforces.com/contest/2050/submission/298962300)

---

