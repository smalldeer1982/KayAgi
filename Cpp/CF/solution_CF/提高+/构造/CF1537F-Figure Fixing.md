# Figure Fixing

## 题目描述

You have a connected undirected graph made of $ n $ nodes and $ m $ edges. The $ i $ -th node has a value $ v_i $ and a target value $ t_i $ .

In an operation, you can choose an edge $ (i, j) $ and add $ k $ to both $ v_i $ and $ v_j $ , where $ k $ can be any integer. In particular, $ k $ can be negative.

Your task to determine if it is possible that by doing some finite number of operations (possibly zero), you can achieve for every node $ i $ , $ v_i = t_i $ .

## 说明/提示

Here is a visualization of the first test case (the orange values denote the initial values and the blue ones the desired values):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1537F/1a3ad14db7374ce21cd4060fc1b1fbe532afbff1.png)One possible order of operations to obtain the desired values for each node is the following:

- Operation $ 1 $ : Add $ 2 $ to nodes $ 2 $ and $ 3 $ .
- Operation $ 2 $ : Add $ -2 $ to nodes $ 1 $ and $ 4 $ .
- Operation $ 3 $ : Add $ 6 $ to nodes $ 3 $ and $ 4 $ .

Now we can see that in total we added $ -2 $ to node $ 1 $ , $ 2 $ to node $ 2 $ , $ 8 $ to node $ 3 $ and $ 4 $ to node $ 4 $ which brings each node exactly to it's desired value.

For the graph from the second test case it's impossible to get the target values.

## 样例 #1

### 输入

```
2
4 4
5 1 2 -3
3 3 10 1
1 2
1 4
3 2
3 4
4 4
5 8 6 6
-3 1 15 4
1 2
1 4
3 2
3 4```

### 输出

```
YES
NO```

# 题解

## 作者：OrangeEye (赞：14)

我的思路：并查集。

首先，把每个节点复制一遍，每次加边（设端点为 $a$和 $b$）就把 $a$与 $b$的副本所在集合合并（ $b$与 $a$同理）。这样，每次在一条边上操作，改变的节点一定在不同集合内（原因自行画图，在相同集合内则不改变总数）。又因为题目保证是连通图，所以集合个数一定不超过2个。每次操作在两集合内同时改变同样大小的数（如果在同一集合内则对总数无影响），只用查询两集合内所有编号 $1-n$的点所需改变的权值之和是否相等即可。

本题还需加两个特判（特判很重要！坑了我很久）：

- 点权值总和为奇数时肯定不行。（原因过于明显）
- 所有点在同一集合内时一定可以。（同一集合内无论怎样操作都可以）

AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,d[400009],F[400009],sz[400009];
long long find(long long x){
	if(F[x]==x)return x;
	x=F[x]=find(F[x]);
	return F[x];
}
void uni(long long a,long long b){
	a=find(a);b=find(b);
	if(a==b)return ;
	if(sz[a]>sz[b])swap(a,b);
	F[a]=b;
	sz[b]+=sz[a];
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(long long i=1;i<=2*n;i++){F[i]=i;sz[i]=1;}
		for(long long i=1;i<=n;i++)cin>>d[i];
		for(long long i=1;i<=n;i++){long long b;cin>>b;d[i]-=b;}
		long long f=0;for(int i=1;i<=n;i++)f+=d[i];
		while(m--){
			long long a,b;cin>>a>>b;
			uni(b,a+n);
			uni(a,b+n);
		}
		if(f%2){
			cout<<"NO\n";
			continue;
		}
		if(sz[find(1)]==2*n){
			cout<<"YES\n";
			continue;
		}
		long long k=0;
		for(long long i=1;i<=n;i++)if(find(1)==find(i))k+=d[i];
		else k-=d[i];
		cout<<(k?"NO":"YES")<<endl;
	}
	return 0;
}
```

如有漏洞，敬请指出。

---

## 作者：CDFLS_mao_zx (赞：8)

## CF1537F

### 废话：

很有意思的一道题，但我考场上爬了，没做。

### 题意：

给定一张无向连通图，点数 $n$ ，边数 $m$ ，每一个点 $i$ 有两个点权，当前权 $v_i$ 和目标权 $t_i$ ，每次操作可以选定一条边，让这条边的两个端点权值都加上 $k$ ，$k$ 是一个整数且没有任何限制，问是否存在一种操作方案让每个点的点权都变成目标权。

### 思路：

我们先把一些显然不行的情况判掉：$(\sum v_i -\sum t_i) $ % $2 = 1$  不行，因为每次操作对总权值的改变是偶数。 

**整数加减类构造问题，考虑每一个单元可以进行的操作**。注意到如果图是一颗树，那么就可以直接像拓扑排序一样从叶子向上搞。最后的答案一定是确定的，考虑有环的情况。

我们先把所有的权值移动到一个环上，也就是说，因为图联通，像弄树一样，先找一个环，然后随便选这个环上的一个点，然后弄一颗 $\text{MST}$ ，以这个点为根，权值的改变全部弄到这个点上。 

很显然，如果有奇环，那么这张图一定是可以搞定的，因为我们可以对一个点进行加 $2$ 的操作，具体方式如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/4h5yrpri.png)

只有红色箭头标注的点权值加了  $2$ ，其它的点权值没动。

所以如果有奇环，直接 $\text{YES}$ 走人，考虑无奇环的情况，也就是图是二分图的情况。

发现无论怎么操作，二分图两边的**权值的还需要的改变量**的差都是不动的，所以判断一下两边权值该变量的差($\sum v_i -\sum t_i$)是否一样就可以了。

如果改变量相同，那么一定存在一种方式可以构造出解。~~原因就不解释了，这个感性理解不难，但讲清楚还是有点难度的。~~

### 参考代码：

```cpp
#include<bits/stdc++.h>
#define y1 y3647
#define earse erase
#define INF 1000000000
#define LL long long
using namespace std;
inline void read(int &x)
{
	x=0;int f=1;
	char ch=getchar();
	while(ch!=45&&(ch>'9'||ch<'0'))ch=getchar();
	if(ch==45){f=-1,ch=getchar();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
const int N=2e5+10;
int i,j,k,n,s,t,m,flag;
int col[N],v[N],w[N];
vector<int> a[N];
void dfs(int u)
{
	for(int v:a[u])
	{
		if(col[v]!=-1)
		{
			if(col[v]==col[u])
			flag=0;
			continue;
		}
		col[v]=col[u]^1;
		dfs(v);
	}
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//freopen(".ans","w",sdtout);
	read(t);
	while(t--)
	{
		LL sum=0,sum2=0;
		flag=1;
		read(n),read(m);
		for(i=1;i<=n;i++)
		read(v[i]),sum+=v[i],col[i]=-1;
		for(i=1;i<=n;i++)
		read(w[i]),sum-=w[i],a[i].clear();
		for(i=1;i<=m;i++)
		{
			int x,y;
			read(x),read(y);
			a[x].push_back(y);
			a[y].push_back(x);
		}
		col[1]=0;
		dfs(1);
		for(i=1;i<=n;i++)
		{
			if(col[i])
			sum2+=w[i]-v[i];
			else
			sum2+=v[i]-w[i];
		}
		if(sum%2||(flag==1&&sum2))
		printf("NO\n");
		else
		printf("YES\n");
	}
	return 0;
}


```



---

## 作者：Mr_Gengar (赞：4)

### Problem

你有一张 $n$ 点 $m$ 边的无向连通图，第 $i$ 个点上有点权 $v_i$ 和目标值 $t_i$。

在一次操作中，你可以选择一条边 $(i,j)$，并同时给 $v_i$ 和 $v_j$ 增加一个任意整数值，可以为负。

你需要判断，这张图是否可以在有限步操作中，使得每个节点满足 $v_i = t_i$。

### Solution

约定 $c_i = v_i - t_i$，称一个图是合法的当且仅当能通过有限次操作使改图内所有点的 $c_i = 0$。

对于偶环，我们可以对环进行一个黑白染色，然后显然每条边都连接了不同颜色的点，因为操作为同增同减，所以只要两种颜色点的 $c_i$ 之和相等就能说明该环是合法的。

有同学 ~~（阮巨）~~ 就要问了，你这样只能证明和不相等一定不行，但是和相等也不一定可以啊？

没关系，我们不妨使用反证法。如果在最后存在点的 $c_i$ 不为零，那么可以假设为下图这样的状况，此时显然能再次通过操作使图变为合法的。

![](https://cdn.luogu.com.cn/upload/image_hosting/nk6efbql.png)

注意到这样的证明方法可以推广至所有二分图，所以接下来先考虑奇环。

对于奇环，我们先进行感性理解，因为每次操作无法改变环上 $\Sigma c_i$ 的奇偶性，所以说环上的 $\Sigma c_i$ 必须是偶数。

有同学 ~~（还是阮巨）~~ 又要问了，你这样只能证明 $\Sigma c_i$ 是奇数一定不行，但是 $\Sigma c_i$ 是偶数也不一定可以啊？

没关系，我们注意到奇环上两点之间的路径必定有一条长度是奇数，我们便可以通过如下图所示的方法来调节 $c_i$ 使环合法。

![](https://cdn.luogu.com.cn/upload/image_hosting/1k51ti6f.png)

讨论完以上两种基础情况，接下来我们就可以考虑一些复杂的情况了。

![](https://cdn.luogu.com.cn/upload/image_hosting/4fxav74h.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/9n6sjp4o.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/0wzkywc5.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/6qcqukme.png)

我们先对第一种情况进行考虑。

#### 1. 两个偶环共点

![](https://cdn.luogu.com.cn/upload/image_hosting/reni19z0.png)

如上图，显然该图是二分图，前面已讨论过。

#### 2. 偶环与奇环共点

![](https://cdn.luogu.com.cn/upload/image_hosting/4fxav74h.png)

如上图，~~这种我不会，所以请教了一下机房巨佬，~~ 所以我们对该图上的任意两个点分下列几种情况讨论：

- 均在偶环上

![](https://cdn.luogu.com.cn/upload/image_hosting/or37tj51.png)

此时两点间一定存在一条长度为奇数的路径，之前已处理过。

- 均在奇环上

此时与只有一个奇环的情况相同。

- 一个在偶环上一个在奇环上

![](https://cdn.luogu.com.cn/upload/image_hosting/mgzp5yc5.png)

此时两点间一定存在一条长度为奇数的路径，之前已处理过。

综上，与只有一个奇环并无明显区别。

#### 3. 两个奇环共点

![](https://cdn.luogu.com.cn/upload/image_hosting/tvivm5vi.png)

~~机房大佬让我学以致用，~~ 根据上一种情况的经验，我们做同样的分类讨论。

+ 在同一个奇环上

与单个奇环相同。略。

+ 在不同奇环上

![](https://cdn.luogu.com.cn/upload/image_hosting/tmm9c22i.png)

根据我的一些感性理解，此时两点间一定存在一条长度为奇数的路径，所以不用我多说了吧。

综上，此种情况与只有一个奇环也没有明显区别。

在继续讨论的过程中，我们发现第二、三种情况基本上就是在复读之前的证明过程，因为篇幅原因此处省略，~~读者自证不难。~~

所以只剩下第四种情况需要讨论，不难发现这种情况本质上就是树上套环。

- 树上套偶环

为二分图。证明略。

+ 树上套奇环

此时可以通过操作将 $c_i$ 集中到奇环上，接下来又回到了基础状况。

综合上面这么这么这么多情况 ~~（好恶心啊）~~，我们得出一个 ~~一点也不~~ 惊人的结论：如果图中含有奇环，那么就按奇环的状况考虑，否则图为二分图，也已讨论过。

所以做法就很明晰了，直接对图进行黑白染色判断是否有奇环，根据基础情况得出答案即可。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int kMaxN = 2e5 + 1;

int t, n, m, u, v, x, rzx;
LL sum, c[kMaxN], col[kMaxN], s[2];
vector<int> g[kMaxN];

void dfs(int u, int f) {
  if (~col[u]) {
    rzx |= (col[u] != f);
    return;
  }
  col[u] = f, s[f] += c[u];
  for (int v : g[u]) {
    dfs(v, f ^ 1);
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t; t--) {
    cin >> n >> m;
    rzx = 0, sum = 0, s[0] = s[1] = 0, fill(col + 1, col + n + 1, -1);
    for (int i = 1; i <= n; i++) {
      cin >> c[i];
      g[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      cin >> x;
      c[i] -= x, sum += c[i];
    }
    for (int i = 1; i <= m; i++) {
      cin >> u >> v;
      g[u].push_back(v), g[v].push_back(u);
    }
    dfs(1, 0);
    cout << (rzx ? (sum % 2 == 0 ? "Yes" : "No") : (s[0] == s[1] ? "Yes" : "No")) << "\n";
  }
  return 0;
}
```

---

## 作者：伊地知虹夏 (赞：3)

首先题目只跟 $d_i := t_i - v_i$ 有关，只保留 $d_i$ 即可。

---

case0：$\sum{d_i}$ 为奇数

由于每次操作都是增减 $2$，那么 $\sum d_i$ 若为奇数则一定无解。

---

case1：图为二分图

由于操作为同增同减，左部点权和肯定等于右部点权和，否则无法使所有 $d_i \to 0$，构造的话考虑对于点 $x$ 选择一个邻接点 $y$ 将 $d_x \to 0, d_y \to d_y - d_x$ 然后递归考虑即可。

---

case2：图中有奇环

我们可以通过类似 case1 的构造将所有点权集中到某个奇环上，这样我们只需考虑孤立奇环带点权的问题了。

而我们可以通过构造 $1$ 使得某个点点权单独增减 $2$ ，我们将每个点点权通过构造 $1$ 变成 $1$ 后通过构造 $2$ 将每个有权点排列在一起，然后一对一对 $-1$ 即可，由于点权和为偶数， 一定能删完所有点。

![](https://cdn.luogu.com.cn/upload/image_hosting/jait01z9.png)

---

我们把 case0,1,2 综合起来，就得到了这题解法，判二分图可以用染色法或种类并查集，时间复杂度 $\mathcal{O}(n + m)$，[记录](https://codeforces.com/problemset/submission/1537/266201539)。

---

## 作者：nao_nao (赞：3)

思考后可以发现，如果在两点之间有一条长度为奇数的路径，可以让这两点同时加上某个数。如果两个点之间有一条长度为偶数的路径，可以让这两点同时加减某个数，换言之：和不变。

首先处理一下每个点需要加上多少可以到达目标，作为点权。我们的目的就是把点权全都清零。

自然的联想到二分图，若给出的图是二分图，可以发现两边点权和的差值是无法改变的。所以若差值不为 0 ，我们无论如何都是没办法让它全清零的。否则的话必然有方法让两边全都清零。

如果不是二分图呢？发现对于整张图所有点的权值和，我们通过同时让两个点权加或减的方式无法改变权值和的奇偶性。所以如果权值和为奇数，那么无解。

```cpp
int n,m,col[N],V[N],T[N],vis[N],flag = 1;
int head[N],go[N],nxt[N],cnt;
void add(int u,int v)
{
	go[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}
void dfs(int u)
{
	for(int e = head[u];e;e = nxt[e]) {
		int v = go[e];
		if(!col[v]) {col[v] = -col[u];dfs(v);}
		else {
			if(col[v] == col[u]) {flag = 0;return ;}
		}
		if(!flag) return  ;
	}
}

void solve()
{
	n = read(),m = read();flag = 1;cnt = 0;
	for(int i = 1;i <= n;i ++) V[i] = read(),col[i] = 0,head[i] = 0;
	for(int i = 1;i <= n;i ++) T[i] = read();
	for(int i = 1;i <= m;i ++) {
		int u = read(),v = read();
		add(u,v);add(v,u);
	}
	col[1] = 1;dfs(1);
	int sum1 = 0,sum2 = 0,sum = 0;
	if(!flag) {
		for(int i = 1;i <= n;i ++) sum += T[i]-V[i];
		if(sum&1) {puts("NO");}
		else puts("YES");
	} else {
		for(int i = 1;i <= n;i ++) {
			if(col[i] > 0) sum1 += T[i]-V[i];
			else sum2 += T[i]-V[i];
		}
		if(sum1 - sum2 == 0) puts("YES");
		else puts("NO");
	}
	return ;
}
```

---

## 作者：xujunlang2011 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1537F)

## 思路

首先可以把 $\sum\limits_{i=1}^nv_i$ 与 $\sum\limits_{i=1}^nt_i$ 奇偶性不同的情况判掉，因为每次操作都会给两个数加上同一个值，所以每次会给 $\sum\limits_{i=1}^nv_i$ 加上一个偶数，奇偶性不变。

然后开始分类讨论。

$\bullet$ 有奇环

对于一个奇基环，我们可以进行以下两种操作：

1.你可以选择相邻的两个点同时加同一个值。（这不就题面吗……）

2.将一个点加（或减）二，如图。（不改变奇偶性）

![](https://cdn.luogu.com.cn/upload/image_hosting/m0jit35g.png)

所以对于一个有奇环的图，我们可以把所有多余的 $v_i$ 都传到奇环上的一个点上，然后再通过加（或减）二将多余的 $v_i$ 抵消。

由于 $\sum\limits_{i=1}^nv_i$ 与 $\sum\limits_{i=1}^nt_i$ 奇偶性不同的情况已经被判掉了，所以遇到有奇环的图直接无脑 `YES`。

$\bullet$ 没有奇环

很显然这是个二分图。

每次操作时我们发现左右两边会同时加上同一个值。

所以只要左边的 $\sum\limits v_i-\sum\limits t_i$ 等于右边的 $\sum\limits v_i-\sum\limits t_i$ 就行了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
long long T, n, m, s[N], t[N], x, y, cnt, hc[N], l, r, f[N];
bool F;
struct node
{
	long long u, v, h;
}a[N * 2];
void add(long long x, long long y)
{
	a[++cnt].u = x;
	a[cnt].v = y;
	a[cnt].h = hc[x];
	hc[x] = cnt;
}
void dfs(long long k, long long num)
{
	f[k] = num + 1;
	x += s[k];
	y += t[k];
	if (num == 0)
	{
		l += s[k];
		r += t[k];
	}
	else
	{
		l += t[k];
		r += s[k];
	}
	for (int i = hc[k];i;i = a[i].h)
	{
		if (!f[a[i].v])
		{
			dfs(a[i].v, num ^ 1);
		}
		else
		{
			if (f[k] == f[a[i].v])
			{
				F = 1;
			}
		}
	}
}
int main()
{
	cin >> T;
	for (int ti = 1;ti <= T;ti++)
	{
		cin >> n >> m;
		for (int i = 1;i <= n;i++)
		{
			cin >> s[i];
		}
		for (int i = 1;i <= n;i++)
		{
			cin >> t[i];
		}
		for (int i = 1;i <= m;i++)
		{
			cin >> x >> y;
			add(x, y);
			add(y, x);
		}
		x = y = 0;
		dfs(1, 0);
		// v之和模二 等于 t之和模二 且 (有奇环 或 二分图左边之和 等于 二分图右边之和) 
  		if ((x % 2 + 2) % 2 == (y % 2 + 2) % 2 && (F || l == r))
		{
			cout << "YES\n";
		}
		else
		{
			cout << "NO\n";
		}
		cnt = l = r = F = 0;
		for (int i = 1;i <= n;i++)
		{
			hc[i] = f[i] = 0;
		}
	}
	return 0;
}
```

## 警示后人

$\sum\limits v_i$ 与 $\sum\limits t_i$ 有可能是负数，取模时注意。

多测清空！！！

---

## 作者：taojinchen (赞：2)

# 思路
设点 $i$ 的 $f_i \gets v_i - t_i$。

第一步简化。将所有 $v_i$ 变成对应的 $t_i$，等价于将所有 $f_i$ 变成 $0$。

第二步找规律。我们发现将点 $i$ 的 $f_i$ 直接加到另外一个和自己距离为偶数的点 $j$ 上， 使得 $f_j \gets f_j + f_i$ 且 $f_i \gets 0$ 和原图是等价的。

第三步找特例。对于一个二分图而言，可以将点分为两个集合，其中的每一个集合的总值都可以扔在该集合的一个点中。为有两个集合，所以有两个点。如果这两个点的值相等，则可以消掉；否则不行。

第四步借助生成树思考。现在有一颗生成树，上面有一堆返祖边。如果返祖边连接的两个点的层数的奇偶性不同，则仍然二分图，当然树本身就是一个二分图。如果返祖边连接的两个点的层数的奇偶性相同，则会产生一个奇环，所有的点就可以放在一个点上，可以证明：当 $\sum f$ 是偶数时，就可以拆成两个相同的数，然后消掉；否则不能消掉。

第五步实现。我们发现找奇环其实可以不用生成树，直接二分图染色就可以实现，生成树只是我们思考时借助的工具。
# 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll kM = 2e5 + 5;
ll q, n, m, i, j, v[kM], f[kM], c[kM], t, ans;
ll ed[kM], ne[kM << 1], to[kM << 1], cnt;
void add(ll u, ll v){//链式前向星
  ne[++cnt] = ed[u], ed[u] = cnt, to[cnt] = v;
  return;
}
void dfs(ll rt){//二分图染色
  ll i; 
  for(i = ed[rt]; i; i = ne[i]){
    if(c[to[i]]){
      if(c[to[i]] == c[rt]){
        t = 1;
        break;
      }
    }
    else{
      c[to[i]] = c[rt] ^ 1;
      dfs(to[i]);
    }
    if(t) break;
  }
  return;
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> q;
  while(q--){
    cin >> n >> m;
    t = ans = 0, cnt = 1;// 初始值
    for(i = 1; i <= n; i++){
      cin >> v[i];
      c[i] = ed[i] = 0;// 初始值
    }
    for(i = 1; i <= n; i++){
      cin >> f[i];
      f[i] = v[i] - f[i];
    }
    for(i = 1; i <= m; i++){
      ll u, v;
      cin >> u >> v;
      add(u, v), add(v, u);
    }
    c[1] = 2;// 初始值
    dfs(1);// 二分图染色
    if(t){
      for(i = 1; i <= n; i++){
        ans += f[i];
      }// 一定不要用 ans & 1 ，因为负数是用补码存储的
      if(ans % 2) cout << "NO\n";//求奇偶性
      else cout << "YES\n";
    }
    else {
      cnt = 0;
      for(i = 1; i <= n; i++){
        if(c[i] == 2) ans += f[i];
        else cnt += f[i];
      }
      if(ans != cnt) cout << "NO\n";
      else cout << "YES\n";
    }
  }
  return 0;
}
```

---

## 作者：BLuemoon_ (赞：2)

[link](https://www.luogu.com.cn/problem/CF1537F)

## 题意

一个无向**连通**图，每个点有初始点权 $v_i$ 和目标值 $t_i$。

你可以执行任意次操作，每次操作你可以选择一条边，并同时给 $v_i$ 和 $v_j$ 同时增加 $p$，$p$ 为任意**整数**。

**多组数据**。对于每一组数据，询问是否可以在有限步操作中，使得每个节点的点权等于目标值，即 $\forall i \in [1, n],v_i=t_i$，其中 $n$ 为点的数量。

## 思路

$v_i=t_i$ 可以变形为 $v_i-t_i=0$，所以只需要存储初始点权和目标值的差即可，令其为 $s_i$。

因为题目要求同增同减，所以无论操作怎样，$\sum s_i$ 的奇偶性不变，又因为最后满足条件时 $\sum s_i=0$，所以只要初始的 $\sum s_i$ 是奇数，答案一定是 `NO`。

接下来进行分类讨论。

- 给定图不是二分图

则图中一定存在奇环，奇环上的每个点下都挂了一棵树。

显然可以通过有限次操作使一棵树上只有根节点的 $s_i \ne 0$。如下图（同种颜色为一次操作）。

![](https://cdn.luogu.com.cn/upload/image_hosting/grx95eqo.png)

这样，我们就得到了一个 $\sum s_i$ 为偶数的奇环。然后我们可以让整个奇环中只有一个点 $s_i \ne 0$。如下图（同种颜色为一次操作）。

![](https://cdn.luogu.com.cn/upload/image_hosting/b4v95kbe.png)

最后剩下的 $s_i$ 一定可以表示为 $(\sum_{i \in V_1} s_i) - (\sum_{i \in V_2} s_i)$ 的形式，其中$V_1 \cup V_2$ 为奇环的点集。

令 $p_1=\sum_{i \in V_1} s_i,p_2=\sum_{i \in V_2} s_i$。易知 $p_1+p_2$ 为偶数。所以 $p_1$ 与 $p_2$ 奇偶性相同，即 $p_1-p_2$ 为偶数。

然后我们容易在一个奇环中将唯一一个不为 $0$ 且是偶数的数变成 $0$。如下图（同种颜色为一次操作）。

![](https://cdn.luogu.com.cn/upload/image_hosting/m98r2og6.png)

这样就可以把整个奇环变成 $0$ 了。

综上，当给定图不是二分图时，答案一定为 `YES`。

- 给定图是二分图

那么每次操作改变的两个点一定是左部和右部各有一个。

令 $t_1, t_2$ 分别为左部点的 $\sum s_i$ 和右部点的 $\sum s_i$。

因为每次操作不改变两点之间的差，所以操作也不改变 $t_1-t_2$ 的差。

用染色法求出 $t_1,t_2$，如果 $t_1=t_2$，答案为 `YES`，反之为 `NO`。

## 算法过程

先特判 $\sum s_i$ 的奇偶性。

再染色判断是否为二分图，如果是则顺便记录 $t_1,t_2$。

如果是二分图，则判断 $t_1$ 与 $t_2$ 是否相同。

否则直接输出 `YES`。

时间复杂度为染色的 $O(n+m)$。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int kMaxN = 2e5 + 5;

int T, n, m, v[kMaxN], t[kMaxN], s[kMaxN], c[kMaxN];
LL cnt, t1, t2;
bool B = 1;
vector<int> g[kMaxN];

void DFS(int u, int clr) {
  for (int v : g[u]) {
    if (c[v] == 0) {
      c[v] = clr, DFS(v, 3 - clr);
    } else {
      if (c[v] != clr) {
        B = 0;
        return;
      }
    }
    if (B == 0) {
      return;
    }
  }
}

int main() {
  for (cin >> T; T; T--, B = 1, cnt = t1 = t2 = 0, fill(c, c + n + 2, 0)) {
    for (int i = 1; i <= n; i++) {
      g[i].clear();
    }
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      cin >> v[i];
    }
    for (int i = 1; i <= n; i++) {
      cin >> t[i], s[i] = v[i] - t[i], cnt += s[i];
    }
    for (int i = 1, u, v; i <= m; i++) {
      cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
    }
    if (cnt & 1) {
      cout << "NO\n";
      continue;
    }
    DFS(1, 1);
    if (B == 0) {
      cout << "YES\n";
      continue;
    }
    for (int i = 1; i <= n; i++) {
      (c[i] == 1 ? t1 : t2) += s[i];
    }
    cout << (t1 == t2 ? "YES" : "NO") << '\n';
  }
  return 0;
}
```

## 提醒

[$t_1,t_2$ 记得开 `LL`](https://www.luogu.com.cn/record/162510787)

---

## 作者：DaiRuiChen007 (赞：1)

# CF1537F 题解



## 思路分析

提供一种从代数角度的理解：

显然我们可以把原问题转化成下面的形式：

> 对于每条边 $i$，指定一个整数权值 $w_i$，使得对于每个节点 $u$，所有与 $u$ 相邻的边的权值和为 $t_i-v_i$。

此时假如我们把每个 $w_i$ 看成未知数，我们能够得到 $n$ 个 $m$ 元一次方程，而我们只需要判断这个方程组有没有一组整数解即可。

先判定原方程是否有解，那么我们考虑一组系数 $\{x_1,x_2,\cdots,x_n\}$ 使得节点 $i$ 对应的方程 $\times x_i$ 后全部相加使得 $w_1\sim w_m$ 的系数全部为 $0$，此时我们判断 $\sum_{i=1}^n x_i\times(t_i-v_i)$ 是否为 $0$ 即可得知该方程有没有解。

由于每个 $w_i$ 只在其两个端点 $u,v$ 处出现，因此如果想让 $w_i$ 最终系数为 $0$，那么一定有 $x_u+x_v=0$，因此任意相邻的两个节点符号相反，绝对值相同，显然只有这个图能被黑白染色时，即该图是二分图时有解。

对整个图进行黑白染色，黑点系数为 $1$，白点系数为 $-1$ 即可判定是否有一组合法的 $\{x_i\}$，然后我们用这组 $\{x_i\}$ 去检查 $\sum_{i=1}^n x_i\times(t_i-v_i)$ 是否为 $0$ 即可判定方程有没有解。

接下来考虑判定原方程是否有一组整数解，同样考虑一组系数 $\{x_i\}$ 使得最终 $w_1\sim w_n$ 都是某个 $k$ 的倍数，而此时我们继续判断 $\sum_{i=1}^n x_i\times(t_i-v_i)$ 是 $k$ 的倍数即可，同样，此时对于任意一条边 $(u,v)$ 都有 $x_u+x_v\equiv 0\pmod k$ 假设指定了某个点的系数为 $x\bmod k$，那么每个点的系数就依次为 $x\bmod k,(k-x)\bmod k$，为了保证判定有效，我们需要保证 $\gcd(x,k)=1$，否则对于 $x,k$ 同时约去其 $\gcd$ 依然不会改变判定结果。

但这样的判定只能在二分图上进行，且判定结果与上面的判定是等价的。

对于非二分图，我们只能考虑 $x\equiv k-x\pmod k$ 的情况，即 $k=2,x=1$，此时我们能对于非二分图也进行这样的判断，我们构造 $\{x_i\}=\{1,1,1,\cdots,1\}$，判断所有式子的和是否为 $2$ 的倍数即可。

因此总结一下：

- 对于二分图，判断其左部点的 $t_i-v_i$ 的和与右部点 $t_i-v_i$ 的和是否相等。
- 对于非二分图，判断其所有点的 $t_i-v_i$ 的和是否为偶数。

对整张图进行黑白染色并分类按照判定条件判断即可。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1;
vector <int> G[MAXN];
bool vis[MAXN],col[MAXN],ok=true;
int v[MAXN],t[MAXN];
inline void dfs(int p,bool c) {
	if(vis[p]) {
		if(c!=col[p]) ok=false;
		return ;
	}
	col[p]=c,vis[p]=true;
	for(int v:G[p]) dfs(v,c^1);
}
inline void solve() {
	int n,m,cnt=0;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i) G[i].clear(),vis[i]=false;
	for(int i=1;i<=n;++i) scanf("%lld",&v[i]);
	for(int i=1;i<=n;++i) scanf("%lld",&t[i]);
	for(int i=1;i<=m;++i) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	ok=true,dfs(1,0);
	if(!ok) {
		for(int i=1;i<=n;++i) cnt+=t[i]-v[i];
		puts(cnt%2==0?"YES":"NO");
		return ;
	}
	for(int i=1;i<=n;++i) cnt+=(col[i])?(t[i]-v[i]):(v[i]-t[i]);
	puts(cnt==0?"YES":"NO");
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：KaisuoShutong (赞：1)

突然有了一些新感悟，所以凑了篇题解。

首先 $\sum s$ 和 $\sum t$ 的奇偶性不同显然不行。

然后我们考虑图的奇偶性，那是什么呢？二分图。

如果图不是二分图，那么说明存在奇环。奇环就意味着我可以对环上某点做任意增减。加之图为连通，所以一定有解。

如果图不连通：考虑构造一颗 dfs 树。这样从叶子开始依次操作，就可以把问题合法性的判断转移到根上来。也就是说让除了根以外的所有点的 $s=t$，最后判断根可不可以。

如此推下来，判断方法就是看黑白染色后黑白点分别的 $\sum t-\sum s$ 相不相等了。构造方法同上理。

点个赞吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
const int maxn = 2e5+10;
vector<int>g[maxn];int c[maxn],n,m,v[maxn],t[maxn];
void add(int x,int y) {g[y].push_back(x),g[x].push_back(y);}
char dfs(int x) {
	for(auto y:g[x]) if(!c[y]&&(c[y]=3-c[x],!dfs(y))) return 0;
	else if(c[y]==c[x]) return 0;
	return 1;
}
signed main() {
	int csa=read();
	while(csa--) {
		n=read(),m=read();ll al=0;
		for(int i=1;i<=n;i++) v[i]=read(),g[i].clear(),c[i]=0;
		for(int i=1;i<=n;i++) t[i]=read(),al+=t[i]-v[i];
		for(int i=1;i<=m;i++) add(read(),read());
		c[1]=1;if(al&1) {cout<<"NO\n";continue;}
		if(!dfs(1)) cout<<"YES\n";
		else {
			ll t1=0,t2=0;
			for(int i=1;i<=n;i++) if(c[i]==1) t1+=t[i]-v[i];else t2+=t[i]-v[i];
			if(t1==t2) cout<<"YES\n";
			else cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：peterwuyihong (赞：0)

果然还是缺少人类智慧啊

题意：你有一张 $n$ 点 $m$ 边的无向连通图，第 $i$ 个点上有点权 $v_i$ 和目标值 $t_i$。

在一次操作中，你可以选择一条边 $(i,j)$，并同时给 $v_i$ 和 $v_j$ 增加一个任意整数值，可以为负。

你需要判断，这张图是否可以在有限步操作中，使得每个节点满足 $v_i = t_i$。

首先先奇偶判断一下，然后接下来判断图的性质。

先考虑特殊图，树，你就对层数的奇偶分类，那么你每次可以让奇层和偶层总和同时改变相同的值，那么如果奇层或偶层的点权和和目标值和之差不一样，那就 G 了，否则就可以。

然后类似的，二分图也像树一样判断即可。

然后对于非二分图，就存在一个奇环，这个时候奇环上任意两点都能经过构造同时增加 $1$，先把不是这个奇环上的点给操作了达到目标值，然后再转到这个奇环上即可。

```cpp
vector<int>color(vector<vector<int> >g){
  int n=g.size();
  vector<int>ans(n,-1);
  bool gg=0;
  function<void(int,int)>dfs=[&](int x,int c){
    if(gg)return;
    if(~ans[x]){
      if(ans[x]!=c)gg=1;
      return;
    }
    ans[x]=c;
    for(int y:g[x])dfs(y,c^1);
  };
  rep(i,0,n-1)if(ans[i]==-1)dfs(i,0);
  if(gg)return{};
  return ans;
}
using i64 = long long;
void solve(){
  int n,m;
  cin>>n>>m;
  vector<int>s(n),t(n);
  vector<vector<int> >g(n);
  for(int&i:s)cin>>i;
  for(int&i:t)cin>>i;
  i64 ss=accumulate(all(s),0ll);
  i64 st=accumulate(all(t),0ll);
  while(m--){
    int x,y;
    cin>>x>>y;x--,y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  if((ss^st)&1)return cout<<"NO"<<endl,void();
  auto G=color(g);
  if(G.size()==0)return cout<<"YES"<<endl,void();
  vector<i64>C(2);
  rep(i,0,n-1)C[G[i]]+=s[i]-t[i];
  if(C[0]!=C[1])cout<<"NO"<<endl;
  else cout<<"YES"<<endl;
}
```
我草，array 不默认清零的啊，我再也不用 array 了。

---

