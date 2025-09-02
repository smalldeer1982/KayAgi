# スプリンクラー (Sprinkler)

## 题目描述

IOI 农场由 $N$ 块土地组成。土地间有 $N-1$ 条双向道路相连，编号从 $1$ 到 $N-1$ ，第 $i$ 条道路连接土地 $A_i$  和 $B_i$ ，任意两块土地间都可以通过道路互达。农场的每块土地上都有一个洒水器，使用洒水器可以向附近的土地洒水。

JOI 谷是一种脆弱的植物，若它的高度大于等于 $L$ ，JOI 谷顶部长为 $L$ 的部分会立刻断裂并掉落。JOI 君会收获掉落的部分。

初始时，JOI 君在土地 $j$ 上种了一株高度为 $H_j$ 的 JOI 谷，之后的 $Q$ 天，JOI 君都会照料这些 JOI 谷，在第 $k$ 天，JOI 君会做如下两个操作之一：

- 操作 $1$：使用土地 $X_k$ 上的洒水器，向与土地 $X_k$ 距离不超过 $D_k$ 的土地上浇水，使这些土地上的 JOI 谷高度乘以 $W_k$。对高度为 h 的 JOI 谷洒水，它的高度会变为 $hW_k \bmod L$。

- 操作 $2$：测量土地 $X_k$ 上 JOI 谷的高度。

土地 $x$ 和土地 $y$ 间距离的定义为：从土地 $x$ 前往土地 $y$ 经过道路数的最小值。

## 说明/提示

对于所有数据，满足：

- $2\leq N\leq 200000$
- $2\leq L\leq 10^9$
- $1\leq A_i\lt B_i\leq N (i\in[1,N-1])$
- 任意土地之间都可以通过若干条道路到达
- $0\leq H_j\lt L (1\leq j\leq N)$
- $1\leq Q\leq 400000$
- $T_k$ 均为 $1$ 或 $2$
- 对于满足 $T_k=1 (k\in[1, Q])$ 的 $k$ ，保证 $1\leq X_k\leq N, 0\leq D_k\leq 40, 0\leq W_k\lt L$
- 对于满足 $T_k=2 (k\in[1, Q])$ 的 $k$ ，保证 $1\leq X_k\leq N$

详细子任务附加限制及分值如下表所示：

| 子任务编号 |                  附加限制                  | 分值 |
| :--------: | :----------------------------------------: | :--: |
|     1      |               $N,Q\le 1000$                | $3$  |
|     2      | 对于满足 $T_k=1$ 的 $k$ ，保证 $D_k\leq 1$ | $9$  |
|     3      | 对于满足 $T_k=1$ 的 $k$ ，保证 $D_k\leq 2$ | $29$ |
|     4      |   对于满足 $T_k=1$ 的 $k$ ，保证 $W_k=0$   | $12$ |
|     5      |   对于满足 $T_k=1$ 的 $k$ ，保证 $W_k=2$   | $30$ |
|     6      |                 无附加限制                 | $17$ |

# 题解

## 作者：P7GAB (赞：3)

### 题意

给定一棵 $n$ 个点的树，要求支持两种操作。

- `1 x d w`，使所有和点 $x$ 之间距离 $\le d$ 的点乘以 $w$ 并模一个给定的数 $L$。

- `2 x`，查询点 $x$ 的值。

### 分析

本题的代码量其实不大，就我而言，难度主要在能想到如何利用 $d\le40$ 这个条件上。

这是一棵无根树，维护的信息比较杂，没有什么数据结构能比较好的去解决这个问题，所以理应放弃那些对数据结构奇奇怪怪的想法。

虽说如此，在同机房大佬的指点下，我们有了一个分块加猫树的做法（正确性未知,应该是对的）。但在代码突破 3KB 大关而且感觉才写了不到一半的情况下果断弃疗（有能写出来的私信我一下）。

正如前面所说，$d\le40$ 实在太小了，小到都可以上暴力了。

很显然，如果直接修改每个节点，那 $n\le 2\times10^5$ 会直接教你做人。但如果我们只管父亲，至多也就 $40$ 次。

如果涉及到了儿子，就自己给自己打个标记，然后到了儿子的时候，直接只管 $40$ 个父亲有没有标记就好了。

但直接这样做是不行的,时间复杂度有 $O(nd^2)$ 之高，妥妥超时，所以我们需要优化。

有没有可能把 $\le d$ 的点都只标记一次呢？苦思冥想了许久之后，有了如下做法。

设 $s_{x,d}$ 表示点 $x$ 的子树中距离点 $x$ 为 $d$ 的点的标记。我们只需要对 $x$ 的 $g$ 级祖先在 $s_{x,d-g}$ 和 $s_{x,d-g-1}$ 处打标记，这样每个点就刚刚好只标记一次了。

这样时间复杂度就被优化成了 $O(nd)$ 的，完美通过。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+223;
#define int long long
int n,q,L;
struct node {
	int to,nxt;
} edge[maxn<<1];
int head[maxn],cnt=0;
int h[maxn],fa[maxn],s[maxn][41];
void add(int u,int v) {
	cnt++;
	edge[cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int u,int fath) {
	fa[u]=fath;
	for(int i=head[u]; i; i=edge[i].nxt) {
		int v=edge[i].to;
		if(v!=fath)
			dfs(v,u);
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>L;
	for(int i=1; i<n; i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}

	for(int i=1; i<=n; i++)
		cin>>h[i];
	for(int i=1; i<=40; i++) {
		int u=n,v=++n;
		add(u,v);
		add(v,u);
	}
	for(int i=1; i<=n; i++)
		for(int j=0; j<=40; j++)
			s[i][j]=1;
	dfs(n,0);
	cin>>q;
	while(q--) {
		int op,x,d,w;
		cin>>op;
		if(op==1) {
			cin>>x>>d>>w;
			while(d>=0) {
				s[x][d]=(s[x][d]*w)%L;
				if(d>0)
					s[x][d-1]=(s[x][d-1]*w)%L;
				x=fa[x];
				d--;
			}
		} else {
			cin>>x;
			int ans=h[x];
			int d=0;
			while(d<=40) {
				ans=(ans*s[x][d])%L;
				x=fa[x];
				d++;
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
```


---

## 作者：18d47y (赞：1)

# Solution

$d \leq 40$ 提供了一个很关键的信息，使其可以暴力标记当前 $x$ 的 $40$ 个父亲。

打 $tag$ 时对于 $x$ 的 $d$ 级祖先打上 $d$ 和 $d - 1$ 两个标记，查询时直接乘上 $tag$ 即可。

### **code**

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, m, P, a[200001], pa[200001], tg[200001][41];
vector<int > g[200001];

void dfs(int u, int fa) {
	pa[u] = fa; 
	for (int v : g[u])
		if (v != fa)
			dfs(v, u);
}

signed main() {
	cin.tie(0)->sync_with_stdio(false);
	cin >> n >> P;
	for (int i = 1, u, v; i < n; i++)
		cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		for (int j = 0; j <= 40; j++) tg[i][j] = 1;
	} dfs(1, 0); cin >> m;
	while (m--) {
		int op, x, d, w; cin >> op;
		if (op == 1) {
			cin >> x >> d >> w;
			while (d >= 0) {
				tg[x][d] = tg[x][d] * w % P;
				if (d >= 1)
					tg[x][d - 1] = tg[x][d - 1] * w % P;
				if (x == 1) {
					for (int i = 0; i <= d - 2; i++)
						tg[x][i] = tg[x][i] * w % P; break;
				} x = pa[x]; d--;
			}
		} else {
			cin >> x; int ans = a[x];
			for (d = 0; x && d <= 40; d++) 
				ans = ans * tg[x][d] % P, x = pa[x];
			cout << ans << '\n';
		}
	} return 0;
}
```

---

## 作者：kkxacj (赞：0)

#### 思路

乍一看很不可做，然后发现 $d \le 40$，考虑从此入手。

首先对于操作 $1$，考虑向上跳 $d$ 次，记 $sum_{i,j}$ 表示第 $i$ 个数对下面 $j$ 层可以乘上多少贡献，初值全为 $1$，每次向上跳，将 $d-1$，然后 $sum_{i,d-1} \times w$，若无法往上跳就结束。

但上面这个有个问题，就是我查询时如果直接暴力算贡献，就会算重。

分别看一下对于其中一个操作 $2$ 和其中一个操作 $1$ 的关系，如图:

![](https://cdn.luogu.com.cn/upload/image_hosting/5onzesex.png)

这里黄色是操作 $2$，红色时是操作 $1$，如果每次算贡献我都乘上 $sum_{i,j},sum_{i,j+1}$，那么刚好能乘上操作 $2$ 的贡献，因为这样一定会相交，且只会相交一次，当然这是有前提的，就是能够向上跳足够的次数。

如果不够怎么办？我们默认 $1$ 为根，直接计算 $sum_{1,j}$ 到 $sum_{1,40}$ 就行了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
const int N = 2e5+10;
int n,l,op,x,y,d,q,a[N],head[N],cnt,fa[N],sum[N][50],ans,r; 
struct w
{
	int to,nxt;
}b[N<<1];
inline void add(int x,int y)
{
	b[++cnt].nxt = head[x];
	b[cnt].to = y;
	head[x] = cnt;
}
void dfs(int x,int y)
{
	fa[x] = y;
	for(int i = head[x];i;i = b[i].nxt)
		if(fa[x] != b[i].to) dfs(b[i].to,x);
}
signed main()
{
	read(n),read(l);
	for(int i = 1;i < n;i++) read(x),read(y),add(x,y),add(y,x);
	for(int i = 1;i <= n;i++) read(a[i]);
	for(int i = 1;i <= n;i++)
		for(int j = 0;j <= 40;j++) 
			sum[i][j] = 1;
	read(q);
	dfs(1,0);
	while(q--)
	{
		read(op),read(x);
		if(op == 1) 
		{
			read(d),read(y);
			for(int i = d,j = x;i >= 0 && j;i--,j = fa[j])
				sum[j][i] = sum[j][i]*y%l;
		}
		else 
		{
			ans = a[x];
			for(int i = 0;i <= 40;i++) 
			{
				if(!fa[x]) r = 40;
				else r = min(40ll,i+1);
				for(int j = i;j <= r;j++) ans = ans*sum[x][j]%l;
				x = fa[x];
				if(!x) break;
			} 
			print(ans),pc('\n');
		}
	}
	flush();
	return 0; 
}
```

---

## 作者：__Louis__ (赞：0)

## P9527  AT_joisc2022_h スプリンクラー (Sprinkler)题解

#### 题目描述 

给定一颗树，有两种操作。

- ``` 1 x d w ``` 表示给距离 ```x``` 小于等于 ```d``` 的节点乘上 ```w``` 。

- ```2 x``` 表示查询节点 ```x``` 模 ```L``` 的值。

#### 分析

对于一个节点，如果 $d=1$，那么我们可以通过如下方法优化。

我们把权值节点设置为 $0,1$ 两个不同的数组，$0$ 表示这个数本身的标记，而 $1$ 表示这个节点的儿子有多少标记。

很明显，能通过找到自己和父亲的值来很快计算出答案，也能利用这个来很快标记。类推一下，就可以得出算法。

简单来说，如果一个地方标记为距离为 $d$，则标记其 $d$ 的儿子和其 $d-1$ 的儿子，然后标记父亲 $d-1$，$d-2$ 的孩子，以此类推。

#### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;

int w[maxn][42];
vector<int> v[maxn];
int fa[maxn],arr[maxn];
int vis[maxn];
int n,m,mod;
void dfs(int x,int f){
	vis[x]=true;
	for(int i=0;i<=40;i++){
		w[x][i]=1;
	}
	fa[x]=f;
	for(int k:v[x]){
		if(!vis[k]) dfs(k,x);
	}
}
void insert(int x,int da,int dep){
	if(dep==0){
		w[x][dep]=w[x][dep]*da%mod;
		return;
	}else if(x==1){
		for(int i=0;i<=dep;i++){
			w[x][i]=w[x][i]*da%mod;
		}
	}else{
		w[x][dep]=w[x][dep]*da%mod;
		w[x][dep-1]=w[x][dep-1]*da%mod;
		insert(fa[x],da,dep-1);
	}
}
int find(int x,int dep){
	if(dep>40) return 1;
	else if(x==0) return 1;
	else return find(fa[x],dep+1)%mod*w[x][dep]%mod;
}
signed main(){
	freopen("trees.in","r",stdin);
	freopen("trees.out","w",stdout);
	scanf("%lld%lld",&n,&mod);
	int a,b;
	for(int i=1;i<n;i++){
		scanf("%lld%lld",&a,&b);
		v[a].push_back(b);
		v[b].push_back(a);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&arr[i]);
	}
	
	dfs(1,0);
	scanf("%lld",&m);
	int c,d;
	int cnt=0;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&a,&b);
		if(a==1){
			scanf("%lld%lld",&c,&d);
			c=c%mod;
			insert(b,d,c);
		}else{
			printf("%lld\n",find(b,0)*arr[b]%mod);
		}
	}
}







```

---

