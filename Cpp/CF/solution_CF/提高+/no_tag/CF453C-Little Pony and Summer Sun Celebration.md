# Little Pony and Summer Sun Celebration

## 题目描述

Twilight Sparkle learnt that the evil Nightmare Moon would return during the upcoming Summer Sun Celebration after one thousand years of imprisonment on the moon. She tried to warn her mentor Princess Celestia, but the princess ignored her and sent her to Ponyville to check on the preparations for the celebration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF453C/076e2d37b9cb7b6614410629f2bfd3bd32464a7e.png)Twilight Sparkle wanted to track the path of Nightmare Moon. Unfortunately, she didn't know the exact path. What she knew is the parity of the number of times that each place Nightmare Moon visited. Can you help Twilight Sparkle to restore any path that is consistent with this information?

Ponyville can be represented as an undirected graph (vertices are places, edges are roads between places) without self-loops and multi-edges. The path can start and end at any place (also it can be empty). Each place can be visited multiple times. The path must not visit more than $ 4n $ places.

## 样例 #1

### 输入

```
3 2
1 2
2 3
1 1 1
```

### 输出

```
3
1 2 3
```

## 样例 #2

### 输入

```
5 7
1 2
1 3
1 4
1 5
3 4
3 5
4 5
0 1 0 1 0
```

### 输出

```
10
2 1 3 4 5 4 5 4 3 1 ```

## 样例 #3

### 输入

```
2 0
0 0
```

### 输出

```
0
```

# 题解

## 作者：泠小毒 (赞：11)

# Little Pony and Summer Sun Celebration
给一个无向图，n个点m条边，给定一个01序列，如果a[i]=1，要求走到这个点奇数次，否则，要求走到这个点偶数次，请你任选起点，输出满足要求的经过点的序列和序列长度，序列长度不能超过4n
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190510/)
## 解法
首先判断无解，如果图不连通，且两个块中都有要求走过奇数次的点，就无解

如果图连通，一定有解，下面给出过程

我们可以将a序列作为初始状态，每经过一次i号点，相当于a[i]^=1，目标是使a序列全部变成0

可以从一个a[root]=1的点开始走，每个点只走一次，走的路径就是一棵树，叶子节点只经过一次，其它节点经过两次

对于一个点，在回溯时，如果a[i]还是1，就要进行震荡操作，震荡操作是指对于点i回溯到fa[i]时，从fa[i]走到i再走回fa[i]的过程，经过这一操作，效果是a[i]^=1,a[fa[i]]^=1

对于回溯到root时，如果root需要震荡怎么办呢，我们可以不回溯到root，这样就相当于a[root]^=1

有人可能会问，这一定不超过4n吗？一定的

对于每一个点只走一次的情况，算上回溯的，一个点最多进队2次

而每一个点最多只会对其父节点震荡一次，多进队2个点，将这个2的贡献都算在子节点上，可以发现一个节点产生4的贡献，而且一定有节点不到4，比如root，它一定不会震荡
## ac代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int to,next;}e[200010];
int n,m,x,y,ans,cnt,s,a[400010],head[100010];
bool vis[100010],c[100010];
void add(){e[++cnt]={y,head[x]},head[x]=cnt,e[++cnt]={x,head[y]},head[y]=cnt;}
void dfs(int u,int fa)
{
	vis[u]=1,a[++ans]=u,c[u]^=1;
	for(int i=head[u];i;i=e[i].next)
		if(!vis[e[i].to])
			dfs(e[i].to,u),a[++ans]=u,c[u]^=1;
	if(c[u]){a[++ans]=fa,c[fa]^=1,a[++ans]=u,c[u]^=1;}
}
int main()
{
	scanf("%d%d",&n,&m);
	while(m--)scanf("%d%d",&x,&y),add();
	for(int i=1;i<=n;i++){cin >> c[i];if(c[i])s=i;}
	if(s){dfs(s,-1);for(int i=1;i<=n;i++)if(!vis[i]&&c[i]){puts("-1");return 0;}}
	if(ans>1&&a[ans-1]==-1)ans-=3;
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++)printf("%d ",a[i]);
    return 0;
}
```

---

## 作者：lucky叶 (赞：4)

一道有意思的树形 $dp$。

## 问题

+ 给定一个 $n$ 个点，$m$ 条边的无向图和一个 $01$ 序列，若 $a[i] = 1$，则需遍历这个节点奇数次，否则需要遍历此节点偶数次（可以不遍历），求一个可行的方案，要求此方案的长度不超过 $4n$。

## solution

首先我们观察本题的规律，不难发现：

+ 当本图未联通时，任意两个连通块中有需要走奇数遍的点时一定无解（应该不需要解释吧）。
+ 因为一个节点可能有多个儿子，所以当我们未对当前节点的其他儿子进行判断前，一个可行的策略一定可以是：先处理当前节点的其中一个儿子节点，再从这个儿子节点（儿子节点的子树已经处理完了）回溯到当前节点，接着再由当前节点来处理它的其他儿子并回溯到它的父亲节点（以此递归处理问题）。
+ 我们顺着这个思路往下走，将一个需要走奇数次的节点作为根节点，递归处理它的子树，不难发现当我们处理完一个节点的子树，将要回溯到这个节点的父节点时，若这个节点还需要再遍历一遍，我们可以和此节点的父亲节点进行循环（由此节点跳到它的父节点，再由它的父节点跳到它，再由此节点进行回溯，即可更新此节点）。那么根节点如何处理呢？我们进行画图分析：
  ![无标题.png](https://i.loli.net/2021/11/17/PSAbMTjc53Z8amL.png)

+ 此时可以看到 $3$ 号节点需要回溯了，但根节点不需要被再次遍历，不然根节点会回溯到我们传的 $-1$ 号虚根节点上，对此，我们只需要进行特判，如果 $-1$ 号虚根节点入队了，队列数 $-3$（最后 $3$ 个数应该为 $root$，$-1$，$root$），即停止从 $3$ 号节点回溯到根节点，在根节点的前一个节点停止回溯，这样就保证了正确性。

我们再来分析此代码的效率，不难发现每一个叶子节点的最坏入队次数为 $2$ 次，使其父节点多进队 $2$ 次，即一个点最多对答案贡献 $4$ 次，但一定有如同 $root$ 一样的节点，它一定不会和自己的儿子节点循环，所以答案一定严格小于 $4n$。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 1e5 + 5, M = N << 1;
int idx;
int e[M], h[N], ne[M];
void add(int x, int y)
{
	idx ++;
	e[idx] = y, ne[idx] = h[x], h[x] = idx;
}
int a[N], root;
bool vis[N];
int st[N << 2], cnt;
void dfs(int x, int father)
{
	vis[x] = 1;
	st[++ cnt] = x;
	a[x] ^= 1;
	for(int i = h[x]; ~i;i = ne[i])
	{
		int j = e[i];
		if(vis[j]) continue;
		dfs(j, x);
		st[++ cnt] = x, a[x] ^= 1;
	}
	if(a[x]) st[++ cnt] = father, st[++ cnt] = x, a[x] ^= 1, a[father] ^= 1;//和父节点循环 
}
int n, m;
int main()
{
	memset(h, -1, sizeof(h));
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= m;i ++)
	{
		int o, u;
		scanf("%d%d", &o, &u);
		add(o, u);
		add(u, o);
	}
	for(int i = 1;i <= n;i ++)
		scanf("%d", &a[i]), root = (a[i] == 1 ? i : root);
	if(!root)//不用遍历就不遍历 
	{
		puts("0");
		return 0;
	}
	dfs(root, -1);
	for(int i = 1;i <= n;i ++)
	{
		if(a[i] == 1)
		{
			puts("-1");
			return 0;
		}
	}
	if(cnt > 1 && st[cnt - 1] == -1) cnt -= 3;//特判 
	printf("%d\n", cnt);
	for(int i = 1;i <= cnt;i ++)
		printf("%d ", st[i]);
    return 0;
}
```



---

## 作者：wzkdh (赞：3)

对于这道题，我们可以把图当作树来看，因为这道题只要求点的遍历次数，至于怎么遍历的并不要求，所以当作树和当作图来看没有区别了。

首先我们考虑一下无解的情况：如果所有节点不是连通的并且两边都有要求走奇数次的节点，那么我们无论从哪边遍历另一边的奇数节点都不会被满足，即无解。

如果只有一个连通区域存在要求奇数的节点，那么它一定有解。我们dfs遍历它之后回溯，如果回溯到一个节点要求经过奇数次，那么我们可以先返回他的父节点，然后在重新回到它，这样它就满足遍历奇数次了。

我们按照这个规则回溯到根节点，这时除了根节点之外的所有节点一定都是满足的，如果根节点是也满足要求了，我们直接输出就好了，如果不满足，我们只需要在最后一次回溯的时候不回溯，就可以只减少遍历根节点一次，具体操作就是将答案长度减少1即可。

至于题目中说的答案最长为节点数的4倍，这是一定满足的，因为每个节点最多就会有一次不满足要求返回父节点在回来的操作，所以它对于答案的最大贡献就是2，所以答案长度最多就是2n。

具体细节请见代码：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,ans[100010<<2],tot,lin[100010],root,w[100010],vis[100010];
struct edge{
	int to,nxt;
}a[100010];
void add(int x,int y)
{
	a[tot].to=y;
	a[tot].nxt=lin[x];
	lin[x]=tot++;
}
void dfs(int x,int fa)
{
	w[x]^=1;
	ans[++tot]=x;
	vis[x]=1;
	for(int i=lin[x];i!=-1;i=a[i].nxt)
	{
		if(!vis[a[i].to])
		{
			dfs(a[i].to,x);
			w[x]^=1;
			ans[++tot]=x;
		}
	}
	if(fa!=-1&&w[x])//因为是用树的方式处理的图，实际是有环的，要防止死循环
	{
		ans[++tot]=fa;
		w[fa]^=1;
		ans[++tot]=x;
		w[x]^=1;
	}
}
int main()
{
	memset(lin,-1,sizeof(lin));
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	tot=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&w[i]);
		if(w[i])
			root=i;
	}
	if(root)//如果没有奇数节点，则不用进行修改
	{
		dfs(1,-1);
		for(int i=1;i<=n;i++)
		{
			if(w[i]&&!vis[i])
			{
				printf("-1");
				return 0;
			}
		}
	}
	if(w[root])
		tot--;//如果根节点不满足，直接减去最后一次操作即可
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)
	{
		printf("%d ",ans[i]);
	}
	return 0;
}

---

## 作者：SmallTownKid (赞：2)

其实这题有点像树形dp，但还是搜索。

很好看出，题目要求我们把这个 $01$ 序列通过异或全变成 $0$ 。

直接构造不好做，考虑先生成一棵树，然后不断维护这棵树，使得满足题意。

生成一棵树之后再回溯，这样每个点都被经过了 $2$ 次，从深度最大的点往上回溯的时候判断这个点是否满足要求的奇偶性，如果不满足，就让他走向父节点再走回来，这样当前这个点的奇偶性就满足了要求，父节点满不满足不知道，但是一定可以通过这种操作一直回溯到根节点，并保证除根节点以外其他点的正确性，只需要判断根节点是否合法就可以了。如果回溯到根节点会使根节点不满足要求的奇偶性，那就最后一步不回溯到根节点（在代码体现中直接把指针减一了）。

最后答案一定是小于等于 $4n$ 的，因为整个搜索+回溯为 $2n$ ，假设每个点都需要一次调整的操作，也最多是 $2n$ 。

```
#include<bits/stdc++.h>
using namespace std;
int n,m,idx,cnt,st;
int opt[1000010],head[1000010],vis[1000010],ans[1000010];
struct node{
	int nxt,to;
}edge[10000010];
void add(int u,int v)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	head[u]=idx;
}
void dfs(int x,int fath)
{
	opt[x]^=1;
	vis[x]=1;//防止死循环并且在后面判断是否联通 
	ans[++cnt]=x;//答案数组 
	for(int i=head[x];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(!vis[v])
		{
			dfs(v,x);
			opt[x]^=1;
			ans[++cnt]=x;
		}
	}
	if(fath!=0&&opt[x])//不是根节点，dfs完一遍之后不满足奇偶性 
	{
		ans[++cnt]=fath;
		ans[++cnt]=x;
		opt[fath]^=1;
		opt[x]^=1;
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&opt[i]);
		if(opt[i])//找一个奇数点作为根节点 
		st=i;
	}
	if(st)
	{
		dfs(st,0);//随便dfs生成一棵树 
		for(int i=1;i<=n;i++)
		{
			if(!vis[i]&&opt[i])//如果整个图不连通并且其中有要求经过奇数次的点 
			{
				printf("-1");
				return 0;
			}
		}
	}
	if(opt[st])//特判根节点 
	cnt--;
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
	{
		printf("%d ",ans[i]);
	}
	return 0;
}
```



---

## 作者：傅天宇 (赞：2)

[在此观看效果更佳~](https://www.cnblogs.com/F-T-Y/p/13404143.html)

## CF453C Little Pony and Summer Sun Celebration

洛谷链接：https://www.luogu.com.cn/problem/CF453C

CF链接：https://codeforces.com/problemset/problem/453/C

### 前言：
~~小马特辑！i了i了~~

### 题意：
给出一张 $N$ 个点 $M$ 条边的无向图，有些点要求经过奇数次，有些点要求经过偶数次。要求寻找一条满足要求的路径，且该路径长度不超过点数的四倍。
$0\leq N,M\leq100000$

### 题解：
求出图的任意生成树，任意定根，搜索。很明显，如果这样的话，叶子必定只访问一次，非叶子结点必定只访问两次。
如果非叶子节点要求访问奇数次，就会有问题，这时只要让它的父亲多遍历这个点一次即可。
如果这个点是树根，只要对一个奇数点回溯即可。

### Code：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*f;
}
inline void write(int x)
{
    if(x<0) putchar('-'),write(-x);
    else
    {
        if(x>9)write(x/10);
        putchar('0'+x%10);
    }
}
inline void writeputs(int x)
{
    write(x);
    putchar('\n');
}
inline void writeputchar(int x)
{
    write(x);
    putchar(' ');
}
int n,m,tot,fir[100005],root,ans[400005],ANS;bool a[100005],vis[100005];
struct edge
{
    int nxt,to;
}e[200005];
inline void add(int u,int v)
{
    e[++tot]={fir[u],v};
    fir[u]=tot;
}
void dfs(int u,int dad)
{
    vis[u]=1,a[u]^=1,ans[++ANS]=u;
    for(int i=fir[u];i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(!vis[v]) dfs(v,u),ans[++ANS]=u,a[u]^=1;
    }
    if(a[u]) ans[++ANS]=dad,a[dad]^=1,ans[++ANS]=u,a[u]^=1;
}
int main()
{
    n=read(),m=read();
    FOR(i,1,m)
    {
        int u,v;
        u=read();
        v=read();
        add(u,v);
        add(v,u);
    } 
    FOR(i,1,n)
    {
        a[i]=read();
        if(a[i]&&!root)root=i;
    }
    if(root!=0)
    {
        dfs(root,-1);
        FOR(i,1,n)
            if(!vis[i]&&a[i])
            {
                write(-1);
                return 0;
            }
    }
    if(ANS>1&&ans[ANS-1]==-1) ANS-=3;
    writeputs(ANS);
    FOR(i,1,ANS) writeputchar(ans[i]);
    return 0;
}
```

---

## 作者：离散小波变换° (赞：1)

## 题解

题面上可能有点小问题。「一个节点没有被访问过」被算作「一个节点被访问偶数次」，为此 WA 了一发……

注意到我们需要构造出来的答案的长度只需要不超过 $4n$，因此无解条件应该是简单的，而剩余有解情况都可以通过比较简单的方法进行构造。

题目所给的是 $n$ 个点 $m$ 条边的无向图。按照上述思路，如果这个无向图有解，那么它的极大生成树森林应该也有解。这样就把问题简化了。

考虑一个平凡的树上 dfs 过程：从 $u$ 出发，遍历它的每个子树，再回溯。这个过程会遍历每条边恰好两次，产生的节点编号序列长度不超过 $2n$。当我们从子树 $v$ 回溯上来时，如果 $v$ 总访问次数的奇偶性与要求不一致，那总是容易构造 $u\to v\to u$ 的路径来使得奇偶性一致。它会在根节点出现特例，因为根节点没有父亲。但是注意到最后生成的序列最后一个元素一定是根节点，所以如果它的访问次数不符合要求，把序列最后一个元素去除就行。每一条边的遍历次数不超过 $4$ 次，产生的节点编号序列长度不超过 $4n$，符合题设。

如果一棵生成树里存在节点需要被遍历奇数次，那么它所在的生成树一定要被遍历。如果有多棵生成树一定要遍历，因为它们在不同的连通块内，所以肯定无解。这也就是上文所述「应该是简单的」无解条件。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
const int MAXN = 1e5 + 3;
int n, m, C[MAXN], D[MAXN]; bool F[MAXN];
vector <int> V[MAXN], A;
void dfs(int u, int g){
    F[u] = true;
    for(auto &v : V[u]) if(!F[v]){
        A.push_back(v), ++ D[v];
        dfs(v, g);
        A.push_back(u), ++ D[u];
        if(C[v] != D[v] % 2)
            A.push_back(v), ++ D[v],
            A.push_back(u), ++ D[u];
    }
}
int main(){
    n = qread(), m = qread();
    up(1, m, i){
        int u = qread(), v = qread();
        V[u].push_back(v);
        V[v].push_back(u);
    }
    up(1, n, i) C[i] = qread();
    up(1, n, i) if(C[i]){
            A.push_back(i), ++ D[i], dfs(i, i);
        if(C[i] != D[i] % 2) A.pop_back(), -- D[i];
        break;
    }
    up(1, n, i) if(C[i] != D[i] % 2) puts("-1"), exit(0);
    printf("%d\n", A.size());
    for(auto &x : A) printf("%d ", x);
    return 0;
}
```

---

## 作者：luckydrawbox (赞：1)

## 题意

>给一个无向图，$n$ 个点 $m$ 条边，给定一个 $01$ 序列 $a_1…a_n$，如果 $a_i=1$，要求走到这个点奇数次，否则，要求走到这个点偶数次，请你任选起点，输出满足要求的序列长度和经过点的序列，序列长度不能超过 $4\times n$，若无解则输出 $-1$。

## 分析

- 如果我们走过一个要走**奇数次**的点，那么它还要被走**偶数次**。

- 如果我们走过一个要走**偶数次**的点，那么它还要被走**奇数次**。

换句话说：

- $1\implies0$

- $0\implies1$

这不就是**逻辑非**运算吗！

于是问题就变成了：

>给一个无向图，$n$ 个点 $m$ 条边，给定一个 $01$ 序列 $a_1…a_n$，每次经过第 $i$ 个点时 $a_i\Rightarrow\ !a_i$，要求把所有的 $a_i$ 变成 $0$。请你任选起点，输出满足要求的序列长度和经过点的序列，序列长度不能超过 $4\times n$，若无解则输出 $-1$。

接下来我们任选一个点作为起点 $root$，且满足 $a_{root}=1$，从 $root$ 出发进行深搜，对于每个走到的点 $x$，并执行 $a_x\Rightarrow\ !a_x$,表示走到一次，接下来走 $x$ 的未被访问的儿子 $son_{x,i}$，并回溯 $a_x\Rightarrow\ !a_x$，如果访问完后 $a_x$ 还是 $1$，就走回他的父节点 $fa$ 再走回来，就可以保证 $a_x=0$。每次走记得记录路径。

搜索结束后，判断是否有 $a_i$ 为 $1$ 而未被访问过的点，若有，则表明该图不连通且两边都有需要走奇数次的点，显然无解，输出 $1$。

最后判断一下 $a_{root}$ 是否为 $1$，若是，取消最后一次返回父节点的操作，即序列长度减去 $1$，就可以输出答案了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,a[N],ans[4*N],s,root,v[N];
vector<int>e[N];
void dfs(int x,int fa)
{
	a[x]=!a[x];
	ans[++s]=x;
	v[x]=1;
	for(int i=0;i<e[x].size();i++)
		if(!v[e[x][i]])
		{
			dfs(e[x][i],x);
			a[x]=!a[x];
			ans[++s]=x;
		}
	if(fa>0&&a[x])
	{
		ans[++s]=fa,ans[++s]=x;
		a[fa]=!a[fa],a[x]=!a[x];
	}
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
    	int u,v;
    	cin>>u>>v;
    	e[u].push_back(v);
    	e[v].push_back(u);
	}
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
    	if(a[i])
    		root=i;
	}
	if(root)
	{
		dfs(root,0);
		for(int i=1;i<=n;i++)
			if(a[i]&&!v[i])
			{
				cout<<-1;
				return 0;
			}
	}
	if(a[root])
		s--;
	cout<<s<<endl;
	for(int i=1;i<=s;i++)
		cout<<ans[i]<<" ";
	return 0;
}
```


---

## 作者：LlLlCc (赞：1)

翻译中有一点没提到，题目中可能有无解的情况，记得要输出$-1$。当出现两个不相连的联通块都有奇数的情况，那么就一定是无解的

下面我们考虑如何求出可行解

因为只要输出长度不超过$4n$的可行解就行，所以这给我们提供了很大的操作（~~乱搞~~）空间

我们可以随便挑一个节点当根，然后从图中挖出来一棵树，这样每个叶子节点被走了$1$次，非叶子节点被走了他的子节点数$+1$次。因为每个节点只会使自己和父节点被多走了一次，所以序列长度不超过$2n$，合法

但这样并不能保证每个点满足奇偶性，所以我们要再加上一个操作

每次遍历完子节点，就判断子节点是否满足奇偶性，如果不满足，那么就再走一次子节点，然后再上来，这样序列长度就$+2$。因为每个点最多也就这样被处理一次，一次贡献长度是$2$，所以最多为$2n$，加上第一步操作也就是说序列长度最长为$4n$，合法

还有个细节，因为根节点一定是序列的最后一个元素，所以如果根节点不满足奇偶性，那就直接把序列长度$-1$就行

## code
```
#include<bits/stdc++.h>
#define maxn 4000005
using namespace std;
int m,n,Tt,son[maxn],d[maxn],x,y,Ans[maxn],lnk[maxn],nxt[maxn],tot,Q[100],Cnt,root;
bool vis[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-f;ch=getchar();}
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline void dfs(int x){
	vis[x]=1;Tt+=d[x];
	for (int i=lnk[x];i;i=nxt[i]) if (!vis[son[i]]) dfs(son[i]);
}
inline void Dfs(int x){
	Ans[++Cnt]=x;d[x]^=1;vis[x]=1;
	for (int i=lnk[x];i;i=nxt[i])
	  if (!vis[son[i]]){
	  	Dfs(son[i]);
	  	d[x]^=1,Ans[++Cnt]=x;
	  	if (d[son[i]]&1) d[x]^=1,d[son[i]]^=1,Ans[++Cnt]=son[i],Ans[++Cnt]=x;
	  }
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=m;i++) x=read(),y=read(),add(x,y),add(y,x);
	for (int i=1;i<=n;i++) d[i]=read();
	for (int i=1,Tot=0;i<=n;i++,Tt=0)
	  if (!vis[i]){
	     dfs(i);
	     if (Tt) root=i,Tot++;
	     if (Tot>1){printf("-1");return 0;}
      }
    memset(vis,0,sizeof vis);
    Dfs(root);
    if (d[root]&1) Cnt--;
    printf("%d\n",Cnt);
    for (int i=1;i<=Cnt;i++) printf("%d ",Ans[i]);
    return 0;
}
```


---

## 作者：Mihari (赞：1)

# 题目

[传送门](http://codeforces.com/problemset/problem/453/C)

# 题解

首先判断无解的情况：有两个及两个以上的连通块中存在需要走奇数次的点。

这个判断可以在输入的时候做。

然后考虑怎么解决这个问题？

对于最优的情况，我们不经过偶数点，只经过奇数点，走一条单链

但是这只是我们的梦想，这种数据只存在于样例...

但是我们不能放弃我们的梦想，考虑多走一些其他的点，将这些奇数点串起来，这样，在我们走的这条路径上，奇数点有些走了奇数次，有些走了偶数次（因为可能有回溯），偶数点同理，再反观我们走出的路径，实际上可以说成是一颗 $dfs$ 树，我们在这颗树上对于一些走了奇数次的偶数点进行修改，亦可以完成这个任务，但是由于我们的 $dfs$ 树十分不可控，许多信息诸如树根、结构都不清楚，那么，我们考虑随意生成一颗树来代替这个 $dfs$ 树，这也是可行的

那么，随意弄一颗生成树，在这个生成树上首先 $dfs$ 一遍，在某个点所有儿子都访问完之后，如果这个点的走到步数与要求不符，那么我们就再走到父节点，再走到它，这会造成什么？父节点多走一步，它变成目标状态，**相当于将它的错误转移到父节点上**，一直这样转移，直到根节点，对于根节点的最后一个节点，如果回溯到根节点，会造成根节点错误，那么我们就不回溯，保证根节点正确。

不难看出，这道题除了之前所说的特判情况，是一定有解的

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13388006.html
```


---

## 作者：wyl_AC (赞：1)

## 转化问题

看题面很难想到是搜索，但就是搜索。

很轻松（jsnb）能看出走一次i点是把**a[i]^1**：

那么问题便是将整个序列异或至全为0

## 解决问题

首先想到如果有**多个**联通块，而因为题目中只有**一个**起点，如果超过一个联通块有要求经过奇数次的点，那么显然**无解**。

其次可以想到要先走完整个图再调整，因为如果没走完那我怎么救没走的点。而走完后前面如果被踩歪了，就得**回溯**去救，中间仍然会出现被又踩歪的点，这个时候就得用最小的代价去调整

然后如果要调整的话，可以用一个与其相连的点来处理，过去再回来，就多走了一遍。

但防止需要多次回溯，就选择**父亲节点**。

注意了，回溯至**根节点**仍然需要调整的时候，就别回溯了。但是前面为什么不停呢，因为他们不仅有父亲而且上面可能还有节点需要调整。

## 代码
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
using namespace std;
#define M 100005
#define LL long long
#define pai pair<LL,LL>
void read(LL &x) {
    x = 0;
    LL f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            f = -f;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar();
    }
    x *= f;
    return;
}
LL fs(LL x){
	return x<0?-x:x;
}
void print(LL x){
	if(x<10){
		putchar(x+'0');
		return ;
	}
	print(x/10);
	putchar(x%10+'0');
	return ;
}
void write(LL x){
	if(x<0){
		putchar('-');
		x=fs(x);
	}
	print(x);
	return ;
}
LL mint(LL x,LL y){
	return x<y?x:y;
}
LL maxt(LL x,LL y){
	return x>y?x:y;
}
vector<LL>G[M];
LL n,m,st,a[M<<2],ans;
bool vis[M],c[M];
void dfs(LL u,LL fa){
	c[u]^=1;vis[u]=1;a[++ans]=u;
	for(int i=0;i<G[u].size();i++)
	{
		LL v=G[u][i];
		if(!vis[v])
			dfs(v,u),a[++ans]=u,c[u]^=1; 
	}
	if(c[u])
		if(!fa)//既然我不需要被调整，那你回来干嘛 
			ans--;
		else
			c[fa]^=1,c[u]^=1,a[++ans]=fa,a[++ans]=u;
}
int main(){
	read(n),read(m);
	for(int i=1;i<=m;i++){
		LL u,v;
		read(u),read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		LL tmp;
		read(tmp);
		c[i]=tmp;
		if(c[i])
			st=i;//选一个需要踩的点，否则会没有父亲处理他 
	}
	if(st){
		dfs(st,0);
		for(int i=1;i<=n;i++)
			if(!vis[i]&&c[i]){//更多的联通块 
				puts("-1"); 
				return 0;
			}
	}
	printf("%lld\n",ans);
	for(int i=1;i<=ans;i++)
		printf("%lld ",a[i]);
}
```


---

## 作者：qfy123 (赞：0)

# CF453C
[传送门](https://www.luogu.com.cn/problem/CF453C)
## 题意
给定一张 $n$ 个点 $m$ 条边无向图和 $n$ 个限制 $x_1,x_2,...,x_n$，满足 $x_i \in \{0,1\}$，其中 $1$ 表示经过对应点奇数次，$0$ 代表经过对应点偶数次。现在请你任选起点，输出满足所有限制的经过点的序列和序列长度，且序列长度不超过 $4n$。若有多个答案，输出任意一个；若没有满足要求的序列，输出 $-1$。

- $2 \le n \le 10^5$；
- $0 \le m \le 10^5$。
## 思路
显然，因为 $x_i=1$ 的点至少要经过一次，所以要将任一 $x_i=1$ 的点作为起点。然后对其进行深搜，模拟实现过程即可。可以发现，对一个点进行深搜，dfs 序就是一棵树。每经过一个点一次，剩余次数会由奇变偶，或由偶变奇，让点权异或 $1$ 即可。

其次，对于一个点，如果回溯后点权仍旧为 $1$，则只要与父亲节点来回一次就能把他的权值变为 $0$。

接着我们来考虑无解的情况。显然，当一遍深搜过后，仍有点权为 $1$ 的点，则一定无解。

还要注意一点：当回溯到 dfs 序的根节点，其权值变为 $1$ 时，程序会在根节点与虚拟根节点之间来回走一次，但这样显然有问题，因为原图中没有虚拟根节点的存在。其实，遇到这种情况直接停留在根节点的子结点上就可以了。因此，我们要进行特判，当遇到上述情况时，直接将步数减三再输出即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct E{
	int to,nxt;
}e[N<<1];
int head[N<<1],tot,n,m,ans[N<<2],cnt,val[N],rt=1;
bool vis[N];
void add(int x,int y){
	e[++tot].to = y;
	e[tot].nxt = head[x];
	head[x] = tot;
}
void dfs(int u,int fa){
	vis[u]=1;val[u]^=1;ans[++cnt]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v = e[i].to;
		if(vis[v]) continue;
		dfs(v,u);
		val[u]^=1,ans[++cnt]=u;
	}
	if(val[u]) val[fa]^=1,ans[++cnt]=fa,val[u]^=1,ans[++cnt]=u;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	for(int i=1;i<=n;i++) scanf("%d",val+i);
	for(int i=1;i<=n;i++){
		if(val[i]){
			rt = i;
			break;
		}
	}
	dfs(rt,0);
	for(int i=1;i<=n;i++){
		if(!vis[i]&&val[i]){
			printf("-1\n");
			return 0;
		}
	}
	if(!ans[cnt-1] && cnt>1) cnt-=3;
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%d ",ans[i]);
	return 0;
}

```

---

