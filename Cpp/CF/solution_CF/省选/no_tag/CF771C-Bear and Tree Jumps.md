# Bear and Tree Jumps

## 题目描述

A tree is an undirected connected graph without cycles. The distance between two vertices is the number of edges in a simple path between them.

Limak is a little polar bear. He lives in a tree that consists of $ n $ vertices, numbered $ 1 $ through $ n $ .

Limak recently learned how to jump. He can jump from a vertex to any vertex within distance at most $ k $ .

For a pair of vertices $ (s,t) $ we define $ f(s,t) $ as the minimum number of jumps Limak needs to get from $ s $ to $ t $ . Your task is to find the sum of $ f(s,t) $ over all pairs of vertices $ (s,t) $ such that $ s&lt;t $ .

## 说明/提示

In the first sample, the given tree has $ 6 $ vertices and it's displayed on the drawing below. Limak can jump to any vertex within distance at most $ 2 $ . For example, from the vertex $ 5 $ he can jump to any of vertices: $ 1 $ , $ 2 $ and $ 4 $ (well, he can also jump to the vertex $ 5 $ itself).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF771C/8994ac77b38d70eaef5cd0952cd4c3fda510d514.png)There are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF771C/cde4e5f0e6e4654d394ac6cfffb62423a3518573.png) pairs of vertices $ (s,t) $ such that $ s&lt;t $ . For $ 5 $ of those pairs Limak would need two jumps: $ (1,6),(3,4),(3,5),(3,6),(5,6) $ . For other $ 10 $ pairs one jump is enough. So, the answer is $ 5·2+10·1=20 $ .

In the third sample, Limak can jump between every two vertices directly. There are $ 3 $ pairs of vertices $ (s&lt;t) $ , so the answer is $ 3·1=3 $ .

## 样例 #1

### 输入

```
6 2
1 2
1 3
2 4
2 5
4 6
```

### 输出

```
20
```

## 样例 #2

### 输入

```
13 3
1 2
3 2
4 2
5 2
3 6
10 6
6 7
6 13
5 8
5 9
9 11
11 12
```

### 输出

```
114
```

## 样例 #3

### 输入

```
3 5
2 1
3 1
```

### 输出

```
3
```

# 题解

## 作者：灵梦 (赞：14)

[在博客中查看效果更佳 ^_^](https://www.luogu.com.cn/blog/Hakurei-Reimu/solution-cf771c)

这里是一个 $O(nk)$ 的做法。

先考虑点 $u$ 到它的子树中节点的答案。这可以树形 DP 求出。记 $f_{u,i}$ 表示与 $u$ 子树中与它距离为 $i$ 的节点的答案和。转移时，对于 $i\neq 0$ 可以直接对儿子的答案求和；而 $i=0$ 时，分两部分计算：

- 与 $u$ 距离小于 $k$ 的节点，它们可以从 $u$ 一步跳到，每个节点的贡献为 $1$；
- 与 $u$ 距离不小于 $k$ 的节点，可以从 $u$ 往下先跳 $k$ 的距离，再由子树中的 DP 值转移。具体地，可以从 $u$ 的儿子中 $i=k-1$ 的状态转移，此外，每个节点的贡献还需要加上刚开始跳的一下。

然后发现 $u$ 子树中除了 $u$ 自己以外每个节点都有至少 $1$ 的贡献，把它单独拿出来就是 $size_u-1$；剩下的可以每个儿子 $O(k)$ 求和转移。方程大概是：

$$f_{u,0}=\sum_{v\in son_u}f_{v,k-1}+size_v$$

$$f_{u,i}=\sum_{v\in son_u}f_{v,i-1}$$

然后就比较套路了，从上到下再次 DFS 一遍，计算父亲方向的连通分量对 $u$ 的贡献。转移也是同理的，就不再写了。这样就可以得到每个节点到所有其他点的答案了。

最后题目要求所有无序对的答案，加起来以后除个 $2$ 就可以了。

```cpp
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN=220000;
int n, k, sz[MAXN];
vector<int> g[MAXN];
ll f[MAXN][5];
void dfs1(int u, int p)
{
	sz[u]=1;
	for (int v:g[u])
		if (v!=p)
		{
			dfs1(v, u);
			sz[u]+=sz[v], f[u][0]+=f[v][k-1]+sz[v];
			for (int i=1; i<k; i++) f[u][i]+=f[v][i-1];
		}
}
void dfs2(int u, int p)
{
	ll t[5]={0};
	if (p)
	{
		t[0]=f[p][0]-f[u][k-1]-sz[u];
		for (int i=1; i<k; i++) t[i]=f[p][i]-f[u][i-1];
	}
	f[u][0]+=t[k-1]+n-sz[u];
	for (int i=1; i<k; i++) f[u][i]+=t[i-1];
	for (int v:g[u])
		if (v!=p) dfs2(v, u);
}
int main()
{
//	freopen("B.in", "r", stdin);
//	freopen("B.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for (int i=1; i<n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(1, 0), dfs2(1, 0);
	ll ans=0;
	for (int i=1; i<=n; i++) ans+=f[i][0];
	printf("%lld\n", ans/2);
	return 0;
}
```





---

## 作者：RainFestival (赞：14)

设 $f_{x,i}=$ 在 $x$ 子树内到 $x$ 的距离为 $p\times k+i,p\in \mathbb{Z}$ 的点跳到 $x$ 所花费的步数和。

设 $g_{x,i}=$ 在 $x$ 子树内到 $x$ 的距离为 $p\times k+i,p\in \mathbb{Z}$ 的点的数量。

答案为 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{k} f_{i,j}$。

直接求是 $O(n^2)$ 的，但是$k\le 5$ ,很小，所以我们可以有许多性质。

考虑换根dp

我们在第一遍 dfs 时求出以 $1$ 为根时每个点的 $f,g$

第二遍对于每一个点求出以这个点为根的每个点的 $f,g$

代码：

```cpp
#include<cstdio>
#include<vector>
std::vector<int> a[200005];
int n,k;
long long f[200005][10],g[200005][10],ans;
void add(int x,int y){a[x].push_back(y),a[y].push_back(x);}
void dfs(int v,int fa)
{
	f[v][k]=0;g[v][k]=1;
	for (int i=0;i<a[v].size();i++)
	{
		int u=a[v][i];
		if (u==fa) continue;
		dfs(u,v);
		for (int j=1;j<=k;j++)
			if (j==1) f[v][j]=f[v][j]+f[u][k]+g[u][k],g[v][j]=g[v][j]+g[u][k];
			else f[v][j]=f[v][j]+f[u][j-1],g[v][j]=g[v][j]+g[u][j-1];
	}
}
void solve(int v,int fa)
{
	for (int i=1;i<=k;i++) ans=ans+1ll*f[v][i];
	for (int i=0;i<a[v].size();i++)
	{
		int u=a[v][i];
		if (u==fa) continue;
		long long tfv[10],tfu[10],tgv[10],tgu[10];
		for (int j=1;j<=k;j++) tfv[j]=f[v][j];
		for (int j=1;j<=k;j++) tfu[j]=f[u][j];
		for (int j=1;j<=k;j++) tgv[j]=g[v][j];
		for (int j=1;j<=k;j++) tgu[j]=g[u][j];
		for (int j=1;j<=k;j++)
			if (j==1) f[v][j]=f[v][j]-f[u][k]-g[u][k],g[v][j]=g[v][j]-g[u][k];
			else f[v][j]=f[v][j]-f[u][j-1],g[v][j]=g[v][j]-g[u][j-1];
		for (int j=1;j<=k;j++)
			if (j==1) f[u][j]=f[u][j]+f[v][k]+g[v][k],g[u][j]=g[u][j]+g[v][k];
			else f[u][j]=f[u][j]+f[v][j-1],g[u][j]=g[u][j]+g[v][j-1];
		solve(u,v);
        for (int j=1;j<=k;j++) f[v][j]=tfv[j];
		for (int j=1;j<=k;j++) f[u][j]=tfu[j];
		for (int j=1;j<=k;j++) g[v][j]=tgv[j];
		for (int j=1;j<=k;j++) g[u][j]=tgu[j];
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	dfs(1,-1);
	solve(1,-1);
	printf("%lld\n",ans/2);
	return 0;
}
```

然后我们就通过了一道题目

---

## 作者：liuyifan (赞：7)

## 树形DP

(以下分析内容转自[CNBLOGS](https://www.cnblogs.com/AOQNRMGYXLMV/p/6579771.html))
![](https://s2.ax1x.com/2019/03/15/AVGDUA.png)
本蒟蒻code:

```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register//register
#define ll long long
#define inf 0x3f3f3f3f
#define lowbit(x) x&(-x)//树状数组模板
using namespace std;
vector<ll>g[1000005];
ll n,k,size[1000005][5],d[1000005][5],ans,x,y;
inline void dfs(reg ll x,reg ll fa)//树上
{
    reg ll tsize[5]={0},td[5]={0};//DFS中的临时变量(注意一定不要定义为全局,用NOIP2017普及T3的惨痛经历告诉你们(当时我还是蒟蒻中的蒟蒻)
    for(auto y:g[x])
	if(y!=fa)
	{
		memset(tsize,0,sizeof tsize);
		memset(td,0,sizeof td);//数组清零
		dfs(y,x);
        for(reg ll i=0;i<k;i++)tsize[(i+1)%k]+=size[y][i];
        for(reg ll i=1;i<k;i++)td[(i+1)%k]+=d[y][i];
        td[1%k]+=d[y][0]+size[y][0];//树形DP的状态转移
        for(reg ll i=0;i<k;i++)
		{
            for(reg ll j=0;j<k;j++)
			{
                reg ll tmp=(i+j+k-1)/k-(i>0)-(j>0);
                ans+=d[x][i]*tsize[j]+td[j]*size[x][i];
                if(tmp)ans+=(ll)tmp*size[x][i]*tsize[j];//第二类答案,处理方式如图所示
            }
        }
        for(reg ll i=0;i<k;i++)
		{
			d[x][i]+=td[i];
			size[x][i]+=tsize[i];//第一类答案,直接求和处理
		}
    }
	for(reg ll i=0;i<k;i++)ans+=d[x][i];//第一类答案
    size[x][0]++;//DFS完成后做标记
}
int main()
{
    scanf("%lld%lld",&n,&k);
    for(reg ll i=1;i<=n-1;i++)
	{
		scanf("%lld%lld",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);//交叉存边,树形DP中的一种常用思路
    }
    dfs(1,0);
    printf("%lld",ans);//输出最终答案ans
    return 0;
}
```


---

## 作者：Overstars (赞：7)

## [CF771C Bear and Tree Jumps](https://codeforces.com/contest/771/problem/C)

受邀写题解，讲的墨迹点……

### 思路

换根$dp$，尝试两次转移来求解答案——对于树上的所有点对$(u,v)$，$f(u,v)$的总和。

#### 第一次转移

尝试得到以$x$为根时，节点$x$到$x$子树上所有点的步数和。在草纸上画一画就可以发现如果我们得到节点$v$所在子树的信息，在向其父节点$x$传递贡献时，$v$子树上距离$v$为$k$的倍数的点的贡献会整体$+1$（也就是有多少个点到$v$的距离模$k=0$，贡献就新增多少），所以肯定还要把距离和$k$的关系的点的数目记录下来。

我们可以发现$k\le 5$，那么设$dp[x]$表示$x$子树上所有点到$x$的贡献（一维就可以，$dp$不必记录关于$k$的信息）。

设$sum[x][y]$表示在$x$子树上到点$x$的距离**模$k$后**为$y$的点的数量，用来辅助转移。

```cpp
void dfs(int x,int fa)
{
	sum[x][0]=1;//注意这里,自己到自己距离为0
	for(int &v:G[x])
	{
		if(v==fa)
			continue;
		dfs(v,x);
		dp[x]+=dp[v];//回溯将v的贡献传递给其父亲
		for(int i=0;i<k;i++)//点的距离全部变为(i+1)%k
			sum[x][i]+=sum[v][(i-1+k)%k];
		dp[x]+=sum[v][0];//0距离再增加会多走一步,贡献全部+1
	}
}
```

#### 第二次转移

换根$dp$第二部尝试换根，设$dp2[x]$表示以$x$为根节点时，整棵树上所有点到达$x$所需步数和。

当我们尝试将根节点**从$x$转移到$v$时**，贡献$dp2[v]$相对于$dp2[x]$会发生什么变化？会发现$v$子树上所有到$v$的距离模$k$为$0$的点的贡献相对于$dp2[x]$会整体减$1$（这部分点经过$v$到$x$要多走一步，现在可以不走了）；而在整棵树关于$v$子树的补树上（原来的树去掉$v$子树），所有到$x$的距离模$k=0$的点贡献会整体加$1$。

那么此时我们需要寻找方案来方便地求解补树，因为之前我们得到了$sum$数组，所以我们只要得到某个点作为根节点的信息，即可通过减去子树$sum$信息来方便地得到补树上特定距离模数的点的数量。

设$ret[x][y]$表示以$x$为根时树上到点$x$的距离模$k$后等于$y$的点的数量，用来辅助第二次转移。对于原来的根（默认为$1$），$ret[1]$与$sum[1]$的信息含义是一样的。

那么如何通过父节点$x$的$ret$信息来推导出子节点$v$的$ret$呢？使用类似容斥的方法，先假设树上所有点到$v$的距离相对于原来到$x$的距离全部增加$1$，我们发现$v$的子树上的距离会被错误地增加了，$v$子树上到$v$的距离相对于到$x$点不应增加反而**应该减少**，那么我们删掉这一部分的数量并且使用$sum$里的信息来修正。

```cpp
ret[v][i]=ret[x][(i-1+k)%k];//距离全部+1,子树是错误的,下面两行修正
ret[v][i]-=sum[v][(i-2+k)%k];//虚假的子树
ret[v][i]+=sum[v][i];//真正的子树
```

我们得到了$ret$数组，接下来是换根转移过程，和上面类似，跳回到该部分第二段。

观察根节点转移到相邻节点时答案**贡献的变化**，以新的节点$x$为根的子树上距离模$k=0$的点贡献会整体减$1$，而补树上到$fa$距离模$k=0$的点贡献会整体加$1$，如下。

```cpp
dp2[x]=dp2[fa];
dp2[x]+=ret[fa][0]-sum[x][(k-1+k)%k];//x补树上到fa距离为0的点贡献+1
dp2[x]-=sum[x][0];//x子树上所有到x为0的点贡献-1
```

那么这题我们就做出来了，完结撒花ヾ(≧▽≦*)o。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define debug(x) std:: cerr << #x << " = " << x << std::endl;
const int maxn=2e5+10,inf=0x3f3f3f3f,mod=1000000007;
void read(){}
template<typename T,typename... T2>inline void read(T &x,T2 &... oth) {
	x=0; int ch=getchar(),f=0;
	while(ch<'0'||ch>'9'){if (ch=='-') f=1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	if(f)x=-x;
	read(oth...);
}
int sum[maxn][6],dp[maxn],dp2[maxn],k,ans=0;
vector<int>G[maxn];
void dfs(int x,int fa)
{
	sum[x][0]=1;
	for(int &v:G[x])
	{
		if(v==fa)
			continue;
		dfs(v,x);
		dp[x]+=dp[v];
		for(int i=0;i<k;i++)//0再向上会突破一级
			sum[x][i]+=sum[v][(i-1+k)%k];
		dp[x]+=sum[v][0];//步数全部+1
	}
}
int ret[maxn][6];//表示到x点模数为y的点的个数
void dfs2(int x,int fa)
{//转移下来时,x补树上距离为0的点贡献+1
	if(x!=1)
	{
		dp2[x]=dp2[fa];
		dp2[x]+=ret[fa][0]-sum[x][(k-1+k)%k];//x补树上到fa距离为0的点贡献+1
		dp2[x]-=sum[x][0];//x子树上所有到x为0的点贡献-1
	}
	ans+=dp2[x];
	for(int &v:G[x])
	{
		if(v==fa)
			continue;
		for(int i=0;i<k;i++)
		{//先假设上一层所有点距离增大,0->1
			ret[v][i]=ret[x][(i-1+k)%k];//子树是错误的,下面两行修正
			ret[v][i]-=sum[v][(i-2+k)%k];//虚假的子树,
			ret[v][i]+=sum[v][i];//真正的子树
		}
		dfs2(v,x);
	}
}
signed main(signed argc, char const *argv[])
{
	int n,u,v;
	cin>>n>>k;
	for(int i=1;i<n;i++)
	{
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	for(int i=0;i<k;i++)
		ret[1][i]=sum[1][i];
	dp2[1]=dp[1];
	dfs2(1,1);
	cout<<ans/2<<endl;
	return 0;
}
/*
 *可以从u点一次跳到任何与当前节点不超过k的节点
 *f(u,v)为u->v最少次数,求对所有点对的f总和
 *换根dp,以根节点深度为0dfs
 *k很小的时候才容易转移,记录对k取模后的余数
 *dp[x][k]表示在以x为根的子树上距离为k的节点的步数和
*/
```



---

## 作者：happy_zero (赞：5)

一个不用换根的简单写法。

先将答案展开：

$$\begin{aligned}\sum_{1\le s<t\le n}\lceil \frac{f(s,t)}{k}\rceil & = \sum_{1\le s<t\le n}\frac{f(s,t)+[k\nmid f(s,t)]\times(k-f(s,t)\bmod k)}{k}\\&=\frac{\sum_{1\le s<t\le n}f(s,t)+\sum_{1\le s<t\le n}[k\nmid f(s,t)]\times(k-f(s,t)\bmod k)}{k}\end{aligned}$$

显然可以先求分母再除以 $k$。钦定 $1$ 为根（任一点都可以），而 $\sum f(s,t)$ 这个又显然为 $\sum siz_i\times(n-siz_i)$，于是问题就变为了如何求后面那些东西。

记 $s_{u,i,j}$ 表示以 $u$ 为根的子树遍历到第 $i$ 个儿子中到 $u$ 距离模 $k$ 余 $j$ 的点的个数，那么有两种情况：一种是两个子树中的点“拼起来”，一种是任意一点到 $u$。

第一种情况就是拿 $s_{u,i-1}$ 与 $s_{v}(v\in son_u)$ 更新答案（枚举最终余数 $t(t\ne0)$，然后再枚举 $s_{u,i-1}$ 余数，计算出 $s_v$ 对应的余数后乘上 $k-t$）。和同普通树形 dp 一样，第一维 $i$ 可以省略。而第二种情况只需要一开始把 $s_{u,0}$ 设为 $1$ 之后也会被考虑进去。

上面说的可能有些不清楚，具体见代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
const int M = 10;
vector <int> p[N];
int n, k, s[N][M], d[N], f[N], siz[N], ans;
void dfs(int kk, int fa) {
	d[kk] = d[fa] + 1, s[kk][0] = siz[kk] = 1;
	for (auto i : p[kk]) {
		if (i == fa) continue;
		dfs(i, kk);
        for (int t = 1; t < k; t++)
		    for (int j = 0; j < k; j++)
			    ans += s[kk][j] * s[i][(-j + k + t - 1) % k] * (k - t);
            //需要减 1 是因为还要扣掉 i,kk 之间的距离
		for (int j = 0; j < k; j++)
			s[kk][j] += s[i][(j - 1 + k) % k];
		ans += siz[i] * (n - siz[i]); siz[kk] += siz[i];
	}
}
signed main() {
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int x, y; cin >> x >> y;
		p[x].push_back(y);
		p[y].push_back(x);
	}
	dfs(1, 0);
	cout << ans / k  << '\n';
	return 0;
}
```

---

## 作者：云浅知处 (赞：4)

> 给定一棵 $n$ 个节点的树与正整数 $k$，求
> $$
> \sum_{i=1}^n\sum_{j=1}^n\left\lceil\dfrac{\text{dist}(i,j)}{k}\right\rceil
> $$
> 的值。$1\le n\le 2\times 10^5,1\le k\le 5$。

尽管这题可以有 $O(nk^2)$ 的 dp 做法，但是仅限于边权为 $1$ 的情况。

而点分治可以处理边权任意的情形！考虑当前根为 $\text{rt}$ 的时候怎么算。

对每个 $u$ 处理出来 $\text{rt}\to u$ 路径上的边权和，记作 $d_u$，那么要求的就是：
$$
\sum_{b_u\neq b_v}\left\lceil\dfrac{d_u+d_v}{k}\right\rceil
$$
其中 $b_u$ 表示 $u$ 是从哪个子树过来的。我们要能快速算出这个东西就行了。

注意到 $k$ 很小，考虑将 $d_u$ 按照 $\bmod k$ 的余数分类。

由于 $d_u+d_v=k\lfloor d_u/k\rfloor+(d_u\bmod k)+k\lfloor d_v/k\rfloor +(d_v\bmod k)$，故
$$
\left\lceil\dfrac{d_u+d_v}{k}\right\rceil=\lfloor d_u/k\rfloor+\lfloor d_v/k\rfloor+\left\lceil\dfrac{(d_u\bmod k) +(d_v\bmod k)}{k}\right\rceil
$$
前一项可以直接算，考虑后一项怎么算。

设 $f_i$ 为当前子树内满足 $d_u\bmod k=i$ 的 $u$ 的个数，$g_i$ 为前面子树内 $\bmod k=i$ 的个数，那么后一项的和就是
$$
\sum_{i=0}^{k-1}\sum_{j=0}^{k-1}g_if_j\left\lceil\dfrac{i+j}{k}\right\rceil=\sum_{i=0}^{k-1}g_i\left(\sum_{j=1-i}^{k-i}f_j+2\sum_{j=k-i+1}^{k-1}f_j\right)
$$
维护 $f,g$ 以及 $f$ 的前缀和即可。$O(nk\log n)$。

感觉好像可以做到 $O((n+k)\log n)$ 之类的？

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int MN=2e5+5;
const int MK=10;

int f[MK],g[MK],fs[MK],n,k;
vector<int>G[MN];
int sz[MN],rt,all,mx[MN],ans=0;
bool vis[MN];

void calcsiz(int u,int fa){
	mx[u]=0,sz[u]=1;
	for(int v:G[u]){
		if(vis[v]||v==fa)continue;
		calcsiz(v,u),sz[u]+=sz[v],mx[u]=max(mx[u],sz[v]);
	}
	mx[u]=max(mx[u],all-sz[u]);
	if(mx[u]<mx[rt]||rt==0)rt=u;
}

int now=0;

void calcdis(int u,int fa,int de){
	f[de%k]++,now+=(int)(de/k);
	for(int v:G[u]){
		if(v==fa||vis[v])continue;
		calcdis(v,u,de+1);
	}
}

void work(int u){
	memset(g,0,sizeof(g)),memset(f,0,sizeof(f)),memset(fs,0,sizeof(fs));
	vis[u]=1,g[0]=1;int cnt=1,sum=0;
	for(int v:G[u]){
		if(vis[v])continue;
		memset(f,0,sizeof(f)),now=0,calcdis(v,u,1);
		ans+=(now*cnt+sum*sz[v]),sum+=now,cnt+=sz[v];
		fs[0]=f[0];for(int i=1;i<k;i++)fs[i]=fs[i-1]+f[i];
		for(int i=0;i<k;i++){
			if(i==0)ans+=g[i]*(fs[k-1]-fs[0]);
			else ans+=g[i]*(fs[k-i]+2*(fs[k-1]-fs[k-i]));
		}
		for(int i=0;i<k;i++)g[i]+=f[i];
	}
}

void dfz(int u){
	work(u);
	for(int v:G[u]){
		if(vis[v])continue;
		rt=0,all=sz[v],calcsiz(v,u),calcsiz(rt,u),dfz(rt);
	}
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif

	n=read(),k=read();
	for(int i=1;i<=n-1;i++){
		int u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	all=n,calcsiz(1,0),calcsiz(rt,0),dfz(rt);
	cout<<ans<<endl;

	return 0;
}
```

---

## 作者：_Cheems (赞：2)

一个稍有不同的解法？
### 题意
给出一棵有 $n$ 个点的树，定义 $dis(i,j)$ 为树上两点距离，求 $\sum\limits_{1\le i < j \le n} \lceil \frac {dis(i,j)}{k} \rceil$。

$n\le200000,1\le k\le5$
### 思路
容易想到换根 $\rm dp$ 求出每个点到其它点的距离之和 $S_i$，然后除以 $k$，但是由于有向上取整所以不好处理。

如何解决呢？发现不好对每个点单独讨论，也就是说最终式子最好含有 $S_i$ 项。

我们知道 $\lceil \frac ak \rceil = \frac {a+k-a \bmod k}{k}$，只要把 $a$ 除不尽的部分补上即可（当然前提是 $k\nmid a$ ）。

根据上式，有：$\sum \lceil \frac {a_i}{k} \rceil = \sum \frac {a_i+k-a_i \bmod k}{k}=\frac {\sum a_i + \sum (k-a_i\bmod k)} {k}$。

诶，这样就出现 $S_i$ 项了啊。把刚刚推出的式子带到这题里，节点 $i$ 对答案的贡献就是：$\frac {S_i+\sum k-dis(i,j) \bmod k}k$ 。

考虑怎么求 $\sum k-dis(i,j) \bmod k$ 这一项即可。注意到 $k$ 很小，容易想到枚举余数 $c$，统计 $dep(i,j) \bmod k = c$ 的数量即可。

具体的，记 $g_{i,c}/f_{i,c}$ 为子树内/子树外有多少个点 $j$ 满足 $dep(i,j)\bmod k=c$，直接维护即可。

复杂度 $O(nk)$，可以通过。最后注意：上述过程统计的是有序数对，转成无序数对要除以 $2$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5, K = 5;
int n, k, g[N], f[N], son[N], u, v;
int G[N][K], F[N][K], Gs[N][K], ans;
vector<int> to[N];

inline void dfs1(int u, int fa){
	son[u] = 1;
	for(auto v : to[u])
		if(v ^ fa){
			dfs1(v, u);
			son[u] += son[v];
			g[u] += g[v] + son[v];
			
			for(int c = 0; c < k; ++c)
				G[u][(c + 1) % k] += G[v][c], Gs[u][c] += G[v][c];
			++G[u][1 % k], ++Gs[u][0];
		}
}
inline void dfs2(int u, int fa){
	if(fa){
		f[u] = f[fa] + n - son[fa] + 1;
		f[u] += g[fa] - g[u] - son[u] + son[fa] - son[u] - 1;
		
		for(int c = 0; c < k; ++c){
			F[u][(c + 1) % k] += F[fa][c];
			F[u][(c + 2) % k] += Gs[fa][c] - G[u][c] - (c == 0);
		}
		++F[u][1 % k];
	}
	for(auto v : to[u])
		if(v ^ fa) dfs2(v, u);
}
signed main(){
	cin >> n >> k;
	for(int i = 1; i < n; ++i)
		scanf("%lld%lld", &u, &v), to[u].push_back(v), to[v].push_back(u);
	dfs1(1, 0), dfs2(1, 0);
	for(int i = 1; i <= n; ++i){
		int res = g[i] + f[i];
		for(int c = 1; c < k; ++c)
			res += (k - c) * (G[i][c] + F[i][c]);
		ans += res / k;
	}
	cout << ans / 2;
	return 0;
}
```


---

## 作者：Semorius (赞：2)

提供一个不需要换根的树形 $\text{dp}$ 做法。

假如只有一次询问，那么答案为树上两点间距离除以 $k$ 向上取整，那么很自然地想到能否直接求树上所有路径长度和，然后除以 $k$ 向上取整？显然是不行的，因为每条路径长除以 $k$ 的余数合并后可能错误地减少贡献。于是我们考虑将路径长除以 $k$ 的整数部分和余数部分分开计算。

观察数据范围，发现 $1\le k \le 5$，可以将路径长按除以 $k$ 的余数分为 $5$ 类。设 $dp_x$ 表示以 $x$ 为根的子树的答案。设 $f_x$ 表示以 $x$ 为根的子树中以 $x$ 为其中一端点的所有链长除以 $k$ 向下取整的和。设 $g_{x,i}$ 表示以 $x$ 为根的子树中以 $x$ 为其中一端点且长度模 $k$ 余 $i$ 的链的数量。

考虑如何转移：设当前节点为 $x$，它其中一个子节点为 $y$。

首先考虑如何转移 $f_x$ 与 $g_{x,i}$。当从 $y$ 点走到 $x$ 点时，所有以 $y$ 为较浅端点往下的链长度会增加 $1$。于是可以得到如下转移：
$$
\begin{aligned}
&f_x=\sum(f_y+g_{y,k-1})\\
&g_{x,i}=\sum g_{y,j},\ \ \ \ \text{$i \equiv j+1 \pmod {k}$}\\
\end{aligned}
$$

然后考虑如何转移得到 $dp_x$，分为这样几部分：每个子树内部的答案 $dp_y$，两个子树间余数部分的合并，每一个子树的 $f_y$ 产生的贡献和。第二者通过 $g_{y,i}$ 得到，具体实现可以记录一个所有 $y$ 左兄弟的 $g$ 数组的前缀和，可做到不重不漏。而最后一部分可以考虑以 $y$ 为根的子树中的链与所有子树外的点一一匹配，产生的贡献为 $f_y \times (s_x-s_y)$，其中 $s_x$ 为以 $x$ 为根的子树大小。

时间复杂度 $O(nk^2)$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll SIZE = 200005;
const ll mod = 998244353;
ll n, K;
ll head[SIZE], ver[SIZE*2], nxt[SIZE*2], tot;
ll dp[SIZE], f[SIZE], g[SIZE][5], siz[SIZE];

inline ll rd(){
	ll f = 1, x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f*x;
}

void add(ll x, ll y){
	ver[++tot] = y, nxt[tot] = head[x];
	head[x] = tot;	
}

void dfs(ll x, ll fa){
	ll jl[5]; memset(jl, 0, sizeof(jl));
	g[x][0] = 1; siz[x] = 1;
	for(int i = head[x]; i; i = nxt[i]){
		ll y = ver[i];
		if(y == fa) continue;
		dfs(y, x);
		dp[x] += dp[y]; siz[x] += siz[y];
		for(int j = 0; j < K; j++){
			dp[x] += ceil((double)(j+1) / (double)K) * g[y][j];
		}
		for(int j = 0; j < K; j++){
			for(ll k = 0; k < K; k++){
				dp[x] += ceil((double)(j+k+2) / (double)K) * jl[j] * g[y][k];
			}
		}
		for(int j = 0; j < K; j++) jl[j] += g[y][j];
	}
	for(int i = head[x]; i; i = nxt[i]){
		ll y = ver[i];
		if(y == fa) continue;
		for(int j = 0; j < K; j++) g[x][(j+1)%K] += g[y][j];
		dp[x] += (siz[x] - siz[y]) * f[y];
		f[x] += f[y] + g[y][K-1];
	}
}

int main(){
	n = rd(), K = rd();
	for(int i = 1; i < n; i++){
		ll x = rd(), y = rd();
		add(x, y); add(y, x);
	}
	dfs(1, 0);
	printf("%lld", dp[1]);
	return 0;
}
```


---

## 作者：2018ljw (赞：2)

提供一种 $O(n\log ^2n)$、复杂度与 $k$ 无关的做法。但因为 NTT 巨额常数或 FFT 精度误差在 CF 评测时可能 TLE or WA。

显然的是，对于一条长为 $d$ 的路径，它对答案的贡献应为 $\lceil\frac dk\rceil$。显然路径长度 $\le n$，那么我们考虑求出每种长度的路径各有多少。

直接套点分治。假设我们已经得到从分治重心出发，长为 $0,1\dots,t$ 的路径分别有 $a_{0\dots t}$ 条，考虑如何统计贡献。

点分治问题去重同子树贡献的方式一般有两种：从整体里先扣掉该子树，然后计算贡献；或者算出整体贡献，然后分别减去每个子树的贡献。我们采用第二种方法。那么就只需要考虑整体贡献如何计算即可。

假设我们有长为 $x$ 的路径 $a_x$ 条，长为 $y$ 的路径 $a_y$ 条。那么能拼出长为 $x+y$ 的路径多少条呢？根据乘法原理，显然是 $a_xa_y$ 条。

相同的，我们会发现，能拼出长为 $d$ 的路径条数为（这里先不考虑有序点对的问题） $f(d)=\sum\limits_{i=1}^da_ia_{d-i}$。

发现这是一个卷积的形式！我们让 $a$ 数组自己卷自己，再分别减去每个子树的 $a$ 数组自己卷自己，就可以得到每种长度的路径各有多少条。

最终统计答案时，每种长度每条路径会正反各被算一遍，所以直接除以 $2$ 即可。

由于路径可能个数在 $n^2$ 级别（菊花图），所以需要双模 NTT。复杂度点分治+双模数 NTT或 FFT，$O(n\log^2n)$。但 NTT 常数巨大还要做两次。每个子树也要各做一次，所以总复杂度阶级正确，但常数超出天际。

最终代码（双模 NTT 版本）
```cpp
#include<cstdio>
#include<algorithm>
#define swap(x,y) (x^=y^=x^=y)
const int mod[2]={998244353,167772161},g=3;
long long wn[4][1048576];
long long ksm(long long x,int y,int mod){
	long long res=1;
	while(y){
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int r[1048576];
long long a[600001];
void ntt(int lim,int tp){
	int i,j,k,md=mod[tp>>1],xs=tp?g:(md+1)/g;
	for(i=0;i<lim;i++)r[i]=(r[i>>1]>>1)|((i&1)*(lim>>1));
	for(i=0;i<lim;i++)if(i<r[i])swap(a[i],a[r[i]]);
	for(i=1;i<lim;i*=2){
		for(j=0;j<lim;j+=i*2){
			long long w=1;
			for(k=0;k<i;k++){
				long long x=a[j+k],y=a[i+j+k]*w%md;
				a[j+k]=(x+y)%md;
				a[i+j+k]=(x-y+md)%md;
				w=w*wn[tp][i]%md;
			}
		}
	}
	if(!(tp&1))return;
	long long inv=ksm(lim,md-2,md);
	for(i=0;i<lim;i++)a[i]=a[i]*inv%md;
}
long long res[2][400001];
struct edge{
	int col,dis;
}ge[200001];
bool operator<(edge a,edge b){
	return a.col<b.col;
}
int hed[200001],net[400001],ver[400001],tot,cnt;
void add(int x,int y){
	ver[++tot]=y;
	net[tot]=hed[x];
	hed[x]=tot;
}
int sz[200001],son[200001];
bool cut[200001];
void dfs0(int x,int fa){
	int i;
	sz[x]=1;son[x]=0;
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		if(y==fa||cut[y])continue;
		dfs0(y,x);
		sz[x]+=sz[y];
		if(sz[son[x]]<sz[y])son[x]=y;
	}
}
void dfs1(int x,int fa,int dis,int rt){
	ge[++cnt].dis=dis;ge[cnt].col=rt;
	int i;
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		if(y==fa||cut[y])continue;
		dfs1(y,x,dis+1,rt);
	}
}
int findh(int x,int se){
	while(sz[son[x]]>se/2)x=son[x];
	return x;
}
void dfz(int x){
	cut[x]=1;
	cnt=0;
	dfs0(x,x);
	int i,j;
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		if(cut[y])continue;
		dfs1(y,x,1,y);
	}
	std::sort(ge+1,ge+cnt+1);
	int dst=0;
	for(i=1;i<=cnt;i++){
		if(ge[i].dis>dst)dst=ge[i].dis;
		a[ge[i].dis]++;
	}
	a[0]=1;
	int lim=1;
	while(lim<=dst*2)lim<<=1;
	ntt(lim,0);for(i=0;i<lim;i++)a[i]=a[i]*a[i]%mod[0];
	ntt(lim,1);for(i=0;i<=dst*2;i++)res[0][i]+=a[i],a[i]=0;
	for(i=0;i<lim;i++)a[i]=0;for(i=1;i<=cnt;i++)a[ge[i].dis]++;a[0]=1;
	ntt(lim,2);for(i=0;i<lim;i++)a[i]=a[i]*a[i]%mod[1];
	ntt(lim,3);for(i=0;i<=dst*2;i++)res[1][i]+=a[i];
	for(i=0;i<lim;i++)a[i]=0;
	int lp=0;
	for(i=1;i<=cnt;i++){
		if(i!=cnt&&ge[i].col==ge[i+1].col)continue;
		lim=1,dst=0;
		for(j=lp+1;j<=i;j++){
			if(ge[j].dis>dst)dst=ge[j].dis;
			a[ge[j].dis]++;
		}
		while(lim<=dst*2)lim<<=1;
		ntt(lim,0);for(j=0;j<lim;j++)a[j]=a[j]*a[j]%mod[0];
		ntt(lim,1);for(j=0;j<=dst*2;j++)res[0][j]-=a[j],a[j]=0;
		for(j=0;j<lim;j++)a[j]=0;
		for(j=lp+1;j<=i;j++)a[ge[j].dis]++;
		ntt(lim,2);for(j=0;j<lim;j++)a[j]=a[j]*a[j]%mod[1];
		ntt(lim,3);for(j=0;j<=dst*2;j++)res[1][j]-=a[j],a[j]=0;
		lp=i;
		for(j=0;j<lim;j++)a[j]=0;
	}
	for(i=hed[x];i;i=net[i]){
		int y=ver[i];
		if(cut[y])continue;
		dfz(findh(y,sz[y]));
	}
}
long long ans[200001];
int main(){
    int n,k,i;
    scanf("%d%d",&n,&k);
    for(i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    for(i=1;i<=n*2;i++){
        wn[0][i]=ksm(g,(mod[0]-1)/(i*2),mod[0]);
        wn[1][i]=ksm((mod[0]+1)/g,(mod[0]-1)/(i*2),mod[0]);
        wn[2][i]=ksm(g,(mod[1]-1)/(i*2),mod[1]);
        wn[3][i]=ksm((mod[1]+1)/g,(mod[1]-1)/(i*2),mod[1]);
    }
    dfs0(1,1);dfz(findh(1,n));
    res[0][0]=res[1][0]=0;
    for(i=1;i<=n;i++){
        while(res[0][i]%mod[1]!=res[1][i])res[0][i]+=mod[0];
        ans[i]=res[0][i]/2;
    }
    long long rs=0;
    for(i=1;i<=n;i++)rs+=(i+k-1)/k*ans[i];
    printf("%lld",rs);
}
```

---

## 作者：qiyue7 (赞：2)

仍然给出点分的做法，点分做法复杂度O(knlogn),在k较大时相对O(nk^2)的树形dp才有优势。

这题我们可以看出题目中所求的值即为树上所有路径权值和的加强版，那么我们只需要考虑过重心的路径两端mod k后对答案所产生的贡献+原所有路径/k后所得的值即为原答案。具体细节看calc2函数，getdeep负责预处理，del则负责删除当前子树影响。（~~点分真的就是大型分类讨论啊~~）


核心分类讨论代码（ans为答案）：
```cpp
    long long ans;
    int deep[2 * N];
    int sum[6];
    long long sum_0,sz;
    void getdeep(int r, int fa) //当前轮处理数据
    {
        if (r != root)
        {
            sum_0 += deep[r] / k;
            sum[deep[r] % k]++;
            sz++;
        }
        for (int i = p.Begin[r]; i != -1; i = p.Next[i])
        {
            if (p.to[i] != fa && vis[p.to[i]] == false)
            {
                deep[p.to[i]] = deep[r] + p.weight[i];
                getdeep(p.to[i], r);
            }
        }
    }

    void calc2(int a, int fa)//计算当前子树
    {
        ans += (deep[a] / k)*(sz+1);
        int kkk = deep[a] % k;
        if (kkk != 0)
            ans++;
        ans += sum_0;
        for (int i = 0; i < 5; ++i)
            if (kkk + i > 0 && kkk + i <= k)
                ans += sum[i];
            else if (kkk + i > k)
                ans += sum[i] * 2;
        for (int i = p.Begin[a]; i != -1; i = p.Next[i])
        {
            if (p.to[i] != fa && vis[p.to[i]] == false)
                calc2(p.to[i], a);
        }
    }
    int sumnode;
    void del_(int a, int fa, int now)
    {
        sumnode++;
        sum_0 -= deep[a] / k;
        sum[deep[a] % k]--;
        sz--;
        for (int i = p.Begin[a]; i != -1; i = p.Next[i])
        {
            if (p.to[i] != fa && vis[p.to[i]] == false)
                del_(p.to[i], a, now);
        }
    }
    int all_[N * 2];
    void calc(int r)
    {
        getroot(r, r);
        vis[root] = true;
        deep[root] = 0;
        sum_0 = 0;
        sz = 0;
        memset(sum, 0, sizeof(sum));
        getdeep(root, root);
        for (int i = p.Begin[root]; i != -1; i = p.Next[i])
        {
            int L = p.to[i];
            if (vis[L] == false)
            {
                del_(L, root, L);
                calc2(L, root);
                all_[L] = size1[L];
            }
        }
        for (int i = p.Begin[root]; i != -1; i = p.Next[i])
            if (vis[p.to[i]] == false)
            {
                root = 0;
                allnode = all_[p.to[i]];
                calc(p.to[i]);
            }
    }
```


---

## 作者：george0929 (赞：1)

写篇题解纪念一下本蒟蒻为数不多能独立做出的紫题。

提供一种与众不同的 $O(nk\log n)$ 的做法。

### part 1：整理式子并得出暴力做法

我们发现 $\sum\limits_{1\le s<t\le n} f(s,t)$ 中的 $s<t$ 不好处理，所以把式子变成 $\frac{\sum\limits_{1\le s,t\le n} f(s,t)}{2}$，然后再考虑如何计算。

我们枚举其中的 $s$，令 $s$ 作为根，令 $dist(i,j)$ 表示 $i$ 到 $j$ 的树上路径边数。则对于一个 $t$，$f(s,t)=\lfloor\frac{dist(s,t)+k-1}{k}\rfloor$。然后你得到了一个 $O(n^2)$ 的做法。

### part 2：换根

考虑换根，整理一下换根要求的东西：

对于每个根，记 $deep_i$ 表示节点 $i$ 到根的距离，求出 $\sum\limits_{i=1}^{n} \lfloor\frac{deep_i+k-1}{k}\rfloor$。

为了方便计算，我们令 $dep_i\leftarrow deep_i+k-1$，即对于每个根求 $\sum\limits_{i=1}^{n} \lfloor\frac{dep_i}{k}\rfloor$。

考虑换根时每个点 $dep$ 的变化，假设根从 $u$ 换到了 $v$，则子树 $v$ 内的 $dep$ 减少 $1$，子树 $v$ 外的 $dep$ 增加 $1$。

### part 3：数据结构辅助换根

把树上节点拍到 DFS 序上，每次修改的节点是一个区间。

然后问题变成了维护一个数据结构，支持区间加减和整体查询每个数除以 $k$ 的整数部分的和。

考虑线段树，给每个节点额外维护一个 $cnt$ 数组，$cnt_i$ 表示这个区间内除以 $k$ 的余数为 $i$ 的个数，以便区间加时处理边界。具体看代码。

线段树区间加代码：

```cpp
void f(int p,int v){
	t[p].tg+=v;//懒标记
	int rdc=v/k;//大于 k 的部分直接转为区间加
	v%=k;
	if(v<0) rdc--,v+=k;//令 v>0 便于处理
	t[p].sum=t[p].sum+1ll*rdc*(t[p].r-t[p].l+1);
	int tcnt[5]={};
	for(int i=0;i<k;i++){
		tcnt[(i+v)%k]+=t[p].cnt[i];
		if(i+v>=k) t[p].sum+=t[p].cnt[i];//这些数除以 k 的整数部分会增加 1。
	}
	for(int i=0;i<k;i++){//更新 cnt 数组。
		t[p].cnt[i]=tcnt[i];
	}
}
```

### part 4：代码

到这里题目就做完了，可能需要卡常数，具体见代码注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int dep[200005];
long long ans;
vector<int> V[200005];
struct node{
	int l,r,cnt[5];
	long long sum,tg;
}t[800005];
void pushup(int p){
	t[p].sum=t[p*2].sum+t[p*2+1].sum;
	for(int i=0;i<k;i++){
		t[p].cnt[i]=t[p*2].cnt[i]+t[p*2+1].cnt[i];
	}
}
void f(int p,int v){
	t[p].tg+=v;
	int rdc=v/k;
	v%=k;
	if(v<0) rdc--,v+=k;
	t[p].sum=t[p].sum+1ll*rdc*(t[p].r-t[p].l+1);
	int tcnt[5]={};
	for(int i=0;i<k;i++){
		tcnt[(i+v)%k]+=t[p].cnt[i];
		if(i+v>=k) t[p].sum+=t[p].cnt[i];
	}
	for(int i=0;i<k;i++){
		t[p].cnt[i]=tcnt[i];
	}
}
void pushdown(int p){
	int tmp=t[p].tg;
	t[p].tg=0;
	f(p*2,tmp);
	f(p*2+1,tmp);
}
void build(int p,int l,int r){
	t[p].l=l,t[p].r=r;
	if(l==r){
		t[p].cnt[dep[l]%k]=1;
		t[p].sum=dep[l]/k;
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	pushup(p);
}
void modify(int p,int l,int r,int v){
	if(l>r) return;
	if(l<=t[p].l&&t[p].r<=r){
		f(p,v);
		return;
	}
	pushdown(p);
	int mid=(t[p].l+t[p].r)/2;
	if(mid>=l) modify(p*2,l,r,v);
	if(mid<r) modify(p*2+1,l,r,v);
	pushup(p);
}
int dfn[200005],out[200005],tot;
void dfs1(int u,int fa){
	dfn[u]=++tot;
	dep[tot]=dep[dfn[fa]]+1;
	for(int v:V[u]){
		if(v==fa) continue;
		dfs1(v,u);
	}
	out[u]=tot;
}
void dfs2(int u,int fa){
	ans=ans+t[1].sum;
	for(int v:V[u]){
		if(v==fa) continue;
		modify(1,1,n,1);
		modify(1,dfn[v],out[v],-2);
		/*
		优化常数，本来应该这么写：
		modify(1,1,dfn[v]-1,1);
		modify(1,out[v]+1,n,1);
		modify(1,dfn[v],out[v],-1);
		*/
		dfs2(v,u);
		modify(1,1,n,-1);
		modify(1,dfn[v],out[v],2);//同上。
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		V[u].push_back(v);
		V[v].push_back(u);
	}
	dep[0]=k-2;//这样 dep[1] 就会等于 k-1，符合我们的定义。
	dfs1(1,0);
	build(1,1,n);
	dfs2(1,0);
	cout<<ans/2<<endl;
}
```

---

## 作者：WZKQWQ (赞：1)

首先要求的柿子化简一下就是：$\sum_{1\le s < t\le n}\lceil\frac{d_{s,t}}{k}\rceil$，再化一下就是 $\sum_{1\le s < t\le n}\frac{d_{s,t}+(d_{s,t} +k-1) \bmod k + 1}{k}$，两部分分开就是 $\frac{\sum_{1\le s < t\le n}d_{s,t}}{k} + \frac{\sum_{1\le s < t\le n}(d_{s,t} +k-1) \bmod k + 1}{k}$。

先求第一部分：设 $dp_x$ 是一端为点 $x$，一端在以 $x$ 为根的子树内的链的总长度，设 $siz_x$ 为以 $x$ 为根的子树大小，$dp_x=\sum_{y\in son_x}dp_y + siz_y$，然后考虑跨过点 $x$ 的链的贡献是 $\sum_{y\in son_x}(dp_y + siz_y) \times(siz_x - siz_y)$。

再求第二部分，考虑 $k$ 很小所以对每个余数单独做，设 $f_{x,p}$ 是一端为点 $x$，一端在以 $x$ 为根的子树内且长度模 $k$ 余 $p$ 的链的条数。转移就是 $dp_{x,p} = \sum_{y\in son_x}dp_{y,p + k - 1 \bmod k}$，贡献考虑跨过点 $x$ 也不难写出。

复杂度 $O(nk^2)$，代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200005;
typedef long long ll;
ll f[N][5],ans[5],sum,d[N];
int n,k,siz[N];
vector<int>e[N];
void dfs(int x,int fa){
	vector<ll>o[5];
	ll tmp[5];
	for(int i = 0;i < k;++i) tmp[i] = 0;
	o[0].push_back(1);
	for(int i = 1;i < k;++i) o[i].push_back(0);
	siz[x] = 1;
	for(int to:e[x]){
		if(to == fa) continue;
		dfs(to,x);
		siz[x] += siz[to];
		d[x] += d[to] + siz[to];
		for(int i = 0;i < k;++i) o[(i + 1) % k].push_back(f[to][i]);
	}
	for(int to:e[x]){
		if(to == fa) continue;
		sum += (d[to] + siz[to]) * (siz[x] - siz[to]);
	}
	int len = o[0].size();
	for(int i = 0;i < len;++i)
		for(int j = 0;j < k;++j) f[x][j] += o[j][i];
	for(int i = 0;i < len;++i){
		for(int j = 0;j < k;++j)
			for(int _j = 0;_j < k;++_j) tmp[(j + _j) % k] += o[j][i] * (f[x][_j] - o[_j][i]);
	}	
	for(int i = 0;i < k;++i) ans[i] += tmp[i] / 2;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1,x,y;i < n;++i){
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1,0);
	//printf("%lld\n",sum);
	for(int i = 1;i < k;++i){
		sum += (k - i) * ans[i];
		//printf("%d %lld\n",i,ans[i]);
	} 
	printf("%lld\n",sum / k);
	return 0;
}
```


---

## 作者：Yansuan_HCl (赞：1)

即求
$$\sum_u \sum_v \lceil \frac{d(u,v)}{k} \rceil$$

上取整不好处理，于是转化成下取整：

$$\sum_u \sum_v \lfloor \frac{d(u,v)+k-1}{k} \rfloor$$

不妨设 $f_u(v)=d(u,v)+k-1$，原柿即：

$$\sum_u \sum_v \frac{f_u(v)-f_u(v) \bmod k}{k}$$

此时可以对于每个 $u$ 进行 dp, 记录 $f_u$ 的和，以及 $f_u \bmod k$ 为 $0, 1, \ldots,k-1$ 的个数。复杂度为 $O(n^2k)$。

采用换根 dp, 可以把复杂度降至 $O(nk)$。

```cpp
const int N = 200005;
int n, k;
BS<int> tr[N];

ll f[N], g[N], siz[N];
ll mF[N][5], mG[N][5];
void dfs(int u, int fa) {
	++mF[u][k - 1];
	f[u] = k - 1;
	siz[u] = 1;
	for (int v : tr[u]) if (v != fa) {
		dfs(v, u);
		siz[u] += siz[v];
		f[u] += f[v] + siz[v];
		U (i, 0, k - 1)
			mF[u][i] += mF[v][(i - 1 + k) % k];
	}
}

void dp(int u, int fa) {
	for (int v : tr[u]) if (v != fa) {
		ll t[5], tf = g[u] - f[v] - siz[v];
		U (i, 0, k - 1) t[i] = mG[u][i] - mF[v][(i - 1 + k) % k]; // 断链

		g[v] = f[v] + tf + n - siz[v];
		U (i, 0, k - 1)
			mG[v][i] = mF[v][i % k] + t[(i - 1 + k) % k];
		
		dp(v, u);
	}
}

int main() {
	rd(n, k);
	U (i, 2, n) {
		int u, v; rd(u, v);
		tr[u] += v; tr[v] += u;
	}
	dfs(1, 0);
	
	g[1] = f[1];
	U (i, 0, k - 1) mG[1][i] = mF[1][i];
	dp(1, 0);

	ll ans = 0;
	U (i, 1, n) {
		ans += g[i];
		U (j, 0, k - 1) {
			ans -= mG[i][j] * j;
		}
	}
	printf("%lld", ans / k / 2);
	return 0;
}
```

---

## 作者：RayAstRa_ (赞：0)

## Description

给一棵树，求 $\large \sum\limits_{1\leq s<t\leq n} \lceil\frac{dis(s,t)}{k}\rceil$。

## Solution

考虑换根 dp，对于每个点 $x$，维护 $f_{i,a}$ 为 $i$ 子树内 $dep_x \equiv a \pmod k$ 的 $x$ 数量和 $g_{i,a}$ 为 $dis(x,i) \equiv a \pmod k$ 的 $x$ 数量。首先预处理出 $f$ 数组。

考虑从点 $x$ 向点 $to$ 转移，对于 $to$ 子树里的所有点，$dis(x,i)=dis(to,i)+1$，反之则为 $-1$，借助这个性质可以用 $f_{to}$ 和 $g_x$ 转移得出 $g_{to}$。同时以 $to$ 为根得到的答案会在 $x$ 的答案为基础上变化，每个不在 $to$ 子树内且 $dis(x,i)\equiv 0\pmod k$ 的点会使答案 $+1$，每个在 $to$ 子树内且 $dis(x,i)\equiv 1\pmod k$ 的点会使答案 $-1$。答案的变化可以借助 $f,g$ 计算，dfs 时维护即可。

时间复杂度 $O(nk)$。

## Code


```cpp
const int N=200005;
int n,k,u,v,dep[N],f[N][6],g[N][6];
ll sum,ans;
vec eg[N];
void dfs1(int x,int fa,int d){
    sum+=(d+k-1)/k;
    dep[x]=d;f[x][d%k]=1;
    for(auto to:eg[x]){
        if(to==fa)continue;
        dfs1(to,x,d+1);
        For(i,0,k-1)
            f[x][i]+=f[to][i];
    }
}
void dfs2(int x,int fa,ll sum){
    ans+=sum;
    for(auto to:eg[x]){
        if(to==fa)continue;
        For(i,0,k-1){
            g[x][i]-=f[to][(i+dep[x])%k];
        }
        For(i,0,k-1)
            g[to][i]=g[x][(i-1+k)%k]+f[to][(i+dep[x]+1)%k];
        dfs2(to,x,sum+g[x][0]-f[to][(dep[x]+1)%k]);
        For(i,0,k-1)
            g[x][i]+=f[to][(i+dep[x])%k];
    }
}
void solve(){
    read(n);read(k);
    For(i,1,n-1){
        read(u);read(v);
        eg[u].pb(v);eg[v].pb(u);
    }
    dfs1(1,0,0);
    For(i,0,k-1)
        g[1][i]=f[1][i];
    dfs2(1,0,sum);
    print(ans/2);
}
```

---

## 作者：Kelvin2009 (赞：0)

这道树形动态规划比较常规，适合回忆巩固换根动态规划。

首先注意到：$k$ 的数量级较小，这使得记录与枚举对 $k$ 的余数具有可行性。已知，若两点之间的距离为 $step$，必定会选择跳 $\lceil\frac{step}{k}\rceil$ 步。由于记录的是任意两点之间步数的总和，直接记录总距离无法得到正确答案。

根据向上取整的性质，补全被除数的余数不影响先除再向上取整的结果。即若 $k \mid(c+step)$ 且 $0\leqslant c\leqslant k-1$，则$\lceil\frac{step}{k}\rceil$ 与 $\lceil\frac{step+c}{k}\rceil$ 的值相同。因此记录 $dp_{u,i}$ 表示与 $u$ 的距离对 $k$ 的余数为 $i$ 的点的个数。

用换根的常规方法求每个点到其它所有点的距离总和，同时维护 $dp_{u,i}$。最后对每个点到其它所有点的距离之和求和，同时补上所有的余数，除 $k$ 后即为答案。

**有几点需要注意：**

1. 记录答案要开 $\texttt{long long}$！

1. 由于靠节点维护路径的信息，两个端点重复计算，最终答案只取一半。

1. 虽然补全余数时不需要对整除补余，但仍要记录。因为其对父子节点间信息的转移维护产生贡献。

1. 分开记录该点子树上各点距离的取余情况与非子树上各点距离的取余情况。先维护子树上各点距离的取余情况，以供非子树上的情况需要。

1. 减后取余多加几个 $k$，$k$ 最小可为 $1$。

------------
代码：

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
const int tem_ran=10;
const int range=4e5+5;
int n,k,u,v;
int cnt=1,to[range],nxt[range],head[range];
long long ans,num[range],sum[range],asum[range],rec[range][tem_ran],dp[range][tem_ran];
inline void add(int u,int v)
{
	cnt++;
	nxt[cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
}
void sub(int u,int fa)
{
	num[u]=1ll;
	rec[u][0]++;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==fa) continue;
		sub(v,u);
		sum[u]+=(sum[v]+num[v]);num[u]+=num[v];
		for(int j=0;j<k;j++) rec[u][j]+=rec[v][(j-1+3*k)%k];
	}
	return ;
}
void bro(int u,int fa)
{
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==fa) continue;
		asum[v]=asum[u]+(n-2*num[v]);
		for(int j=0;j<=k;j++) dp[v][j]+=(rec[v][j]+dp[u][(j-1+3*k)%k]-rec[v][(j-2+3*k)%k]);
		bro(v,u);
	}
	return ;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	sub(1,0);
	asum[1]=sum[1];
	for(int j=0;j<k;j++) dp[1][j]=rec[1][j];
	bro(1,0);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<k;j++) asum[i]+=(k-j)*dp[i][j];
		ans+=(asum[i]/k);
	}
	printf("%lld",ans/2);
	return 0;
}
```

---

## 作者：hzx360 (赞：0)

转换题意，求：

$$\sum\limits_{1\le s<t\le n}\left \lceil \frac{d(s,t)}{k}  \right \rceil $$

其中 $d(s,t)$ 表示 $s$ 到 $t$ 的距离。

那问题是怎么向上取整并求和，你肯定不能先把和求出来再除以个 $k$ 吧？

可以这样想，若 $d(s,t) \bmod k = c$，那么:
$$\left \lceil \frac{d(s,t)}{k}  \right \rceil = \frac{d(s,t)+k-c}{k}$$

其中 $d(s,t)+k-c$ 是可以整除 $k$ 的。

我们可以设法吧每个 $d(s,t)$ 除以 $k$ 的余数求出来，用换根 $dp$ 求出 $\sum d(s,t)$ 后再一起加上这些 $k-c$ 去补足，最后除以个 $k$ 就行了。于是这样就可以保证最后答案是可以整除的了。

令 $dp_{i,j}$ 表示有多少个点到 $i$ 的距离除以 $k$ 后余数为 $j$（包括 $i$ 自己），求法与正常换根 $dp$ 类似，具体见代码。

当然最后答案别忘记除以二。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+100;
int n,k,sum[N],bb[N],dp1[N][7],dp2[N][7],si[N];
//dp1[u][oi]: 对于u而言有多少其子树内的点(包括u)满足：d(u,v)%k==oi
//dp2[u][oi]: 对于u而言有多少点(包括u)满足：d(u,v)%k==oi
int head[N],to[N],ne[N],tot;
void add(int x,int y){
	ne[++tot]=head[x];
	to[tot]=y;
	head[x]=tot;
}
void dfs1(int u,int fa){
	si[u]=1,dp1[u][0]=1;
	for(int i=head[u];i;i=ne[i]){
		int v=to[i];
		if(v==fa) continue;
		dfs1(v,u);
		sum[u]+=sum[v]+si[v],si[u]+=si[v];
		dp1[u][0]+=dp1[v][k-1];
		for(int o=1;o<k;o++) dp1[u][o]+=dp1[v][o-1];
	}
	return;
}
void dfs2(int u,int fa){
	for(int i=head[u];i;i=ne[i]){
		int v=to[i];
		if(v==fa) continue;
		bb[v]=bb[u]-si[v]+n-si[v];
		for(int o=0;o<k;o++){
			dp2[v][o]=dp1[v][o]+dp2[u][(o-1+k)%k]-dp1[v][((o-1+k)%k-1+k)%k];
		}
		dfs2(v,u);
	}
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y),add(y,x);
	}
	dfs1(1,0);
	bb[1]=sum[1];
	for(int o=0;o<k;o++) dp2[1][o]=dp1[1][o];
	dfs2(1,0);
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int o=1;o<k;o++) bb[i]+=(k-o)*dp2[i][o];
		ans+=bb[i]/k;
	}
	cout<<ans/2;
	return 0;
}

---

## 作者：Alex_Eon (赞：0)

## 广告

### [$\color{blueviolet}\text{CF 杂题集（点我）}$](https://www.cnblogs.com/Eon-Sky/p/17763683.html)
### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Ksy/solution-cf771c)

## 主体思路：点分治

## 复杂度：$O(n k^2 \log n)$

## 完整思路

提供一种复杂度稍劣一点的做法，可拓展性较强，当边权不为 $1$ 时也可做。

如果并不了解点分治，可以阅读我的[这篇文章](https://www.cnblogs.com/Eon-Sky/p/17537331.html)进行学习。

首先考虑题目让你求的到底是个什么东西，不难看出 $f(u, v) = \left\lceil\frac{dis(u, v)}{k}\right\rceil = \frac{dis(u, v) + (k - dis(u, v) \mod k)}{k}$，然后这个东西求和可以直接求分子的和然后最后除以 $k$。

分子一共有两部分，第一部分是所有路径的长度和，可以用点分治直接求，但第二部分貌似看起来有点困难。考虑到 $k$ 比较小，所以可以尝试按余数分类，设 $ans_i$ 为 $dis(u, v) \equiv i \pmod{k}$，的路径条数，那么第二部分即 $\sum \limits_{0 \le i < k} ans_i(k - i)$，也就是说第二部分只需要求出路径长度模 $k$ 为各个余数的路径数量即可，这个东西也可以用点分治维护，每次更新记一个桶，然后用乘法原理计数即可。

代码写得比较丑，谨慎阅读。特别地，代码中的 $m$ 即题目中的 $k$。

## 代码实现需要注意的地方：

- 需要开 **long long**，注意很多桶都需要开，在这里挂了好久。

## 参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int UIT;
typedef double DB;
typedef pair<int, int> PII;

#define fi first
#define se second
//--------------------//
const int N = 2e5 + 5, M = 4e5 + 5, K = 5 + 5;

int n, m;
LL ans[K];

struct Edge {
    int to, nex;
} edge[M];
int tot, head[N];

void add(int from, int to) {
    edge[++tot] = {to, head[from]};
    head[from] = tot;
}

LL sum;

int rt, rsiz;
int stot, mxsiz[N], siz[N];
bool vis[N];

void calc_g(int now, int fa) { // 点分治中的处理重心
    siz[now] = mxsiz[now] = 1;
    for (int to, i = head[now]; i; i = edge[i].nex) {
        to = edge[i].to;
        if (vis[to] || to == fa)
            continue;
        calc_g(to, now);
        siz[now] += siz[to], mxsiz[now] = max(mxsiz[now], siz[to]);
    }
    mxsiz[now] = max(mxsiz[now], stot - siz[now]);  
    if (!rt || rsiz > mxsiz[now])
        rt = now, rsiz = mxsiz[now];
    else if (rsiz == mxsiz[now])
        rt = min(rt, now);
}

LL distot, cbuc[K];
int dep[N];

void calc(int now, int fa) { // 计算一个子树的贡献
    cbuc[dep[now] % m]++; // 记录各种半径的数量
    distot += dep[now]; // 半径长度总和
    for (int to, i = head[now]; i; i = edge[i].nex) {
        to = edge[i].to;
        if (vis[to] || to == fa)
            continue;
        dep[to] = dep[now] + 1; // 记得更新深度
        calc(to, now);
    }
}

LL buc[K], tsum;

void divide(int now) {
    memset(buc, 0, sizeof(buc));
    buc[0] = 1; // 初始时已经有一个长度为 0 的路径，因为要计算以当前根节点为一端的贡献
    tsum = 0, vis[now] = true;
    for (int to, tcnt, cnt, i = head[now]; i; i = edge[i].nex) {
        to = edge[i].to;
        if (vis[to])
            continue;
        memset(cbuc, 0, sizeof(cbuc));
        distot = 0, dep[to] = 1;
        calc(to, now);
        for (int j = 0; j < m; j++)
            for (int k = 0; k < m; k++)
                ans[(j + k) % m] += 1LL * buc[j] * cbuc[k]; // 乘法原理计数
        cnt = tcnt = 0;
        for (int j = 0; j < m; j++)
            tcnt += buc[j], buc[j] += cbuc[j], cnt += cbuc[j]; // 将新处理的子树合并到当前子树中
        sum += 1LL * tsum * cnt + 1LL * distot * tcnt; // 更新路径总长度
        tsum += distot; // 合并子树路径总长
    }
    for (int to, i = head[now]; i; i = edge[i].nex) {
        to = edge[i].to;
        if (vis[to])
            continue;
        stot = siz[to], rt = rsiz = 0;
        calc_g(to, 0);
        calc_g(rt, 0);
        divide(rt);
    }
}
//--------------------//
int main() {
    scanf("%d%d", &n, &m);
    for (int u, v, i = 1; i < n; i++)
        scanf("%d%d", &u, &v), add(u, v), add(v, u);
    stot = n;
    calc_g(1, 0);
    calc_g(rt, 0);
    divide(rt);
    for (int i = 1; i < m; i++)
        sum += 1LL * ans[i] * (m - i); // 按照余数统计答案
    printf("%lld", sum / m); // 最后需要除以 m（题目中的 k）
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

upd：对不起，我又一次手残了，有一个地方写错了。

## 思路

看完题面，直觉就是树形 dp。

然后我想了想，如果这道题暴力去做是 $O(n^2)$ 的，我们于是就可以考虑用换根 dp，将复杂度降至 $O(n)$。

首先，按照套路我们先考虑 $u$ 子树内的答案，再进行换根。接下来想一想转移需要哪些东西。我们令 $f_{u,i}$ 表示和 $u$ 之间的距离模 $k$ 为 $i$ 的答案之和。

显然的，$\forall i ∈ [1,k-1], f_{u,i} = \sum f_{v,i-1}$。

但是 $f_{u,0}$ 需要特殊考虑，因为它不能直接从 $u$ 转移得到。我们可以先从 $u$ 向下走到它的儿子 $v$，这样答案就变成了 $\sum f_{v,k-1} + s_u -1$。其中 $s_u$ 表示 $u$ 子树的大小。减 1 是因为 $u$ 没有贡献。

所以我们得到第一个 dfs 的转移方程：

$$f_{u,0} = \sum f_{v,k-1} + s_u - 1$$

$$f_{u,i}(i > 0) = \sum f_{v,i-1}$$

接下来就是换根了。每次换根我们依然从上向下 dfs 一遍，就用 $fa$ 的值更新 $u$，相当于 $u$ 先向上走一步然后计算一下其他的答案，更新完 $u$ 之后，向下不断 dfs 即可。

可以用一个 trick，就是利用 $dp_{u,0}$ 的特殊性（已经对 $s_u - 1$ 求和了），可以加上 $n - s_u$ 并且把答案集中在 $dp_{u,0}$。最后的答案就是 $\sum\limits_{i=1}^{n} dp_{i,0}$。但是由于题目要求 $s < t$，所以我们的做法会有一半的重复，最后除以 2 即可。

时间复杂度 $O(nk)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=200005;
ll dp[MAXN][6],sze[MAXN];
int n,k;
vector<int> E[MAXN];

void dfs1(int u,int fa)
{
	sze[u]=1;
	for(int i=0;i<E[u].size();i++)
	{
		int v=E[u][i]; 
		if(v==fa) continue;
		dfs1(v,u);
		sze[u]+=sze[v];
		dp[u][0]+=dp[v][k-1];
		for(int j=1;j<k;j++) dp[u][j]+=dp[v][j-1];
	}
	dp[u][0]+=sze[u]-1; 
}
ll tmp[10];
void dfs2(int u,int fa)
{
	if(u!=1)
	{
		tmp[0]=dp[fa][0]-dp[u][k-1]-sze[u];
		for(int i=1;i<k;i++) tmp[i]=dp[fa][i]-dp[u][i-1];
		dp[u][0]+=tmp[k-1]+(n-sze[u]);
		for(int i=1;i<k;i++) dp[u][i]+=tmp[i-1];
	}
	for(int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if(v==fa) continue;
		dfs2(v,u);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<n;i++)
	{
		int x,y; cin>>x>>y;
		E[x].push_back(y);
		E[y].push_back(x);
	}
	dfs1(1,0); dfs2(1,0);
	ll ans=0;
	for(int i=1;i<=n;i++) ans+=dp[i][0];
	cout<<(ans>>1);
	return 0;
}
```

---

