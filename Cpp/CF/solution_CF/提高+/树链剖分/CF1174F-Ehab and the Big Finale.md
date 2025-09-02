# Ehab and the Big Finale

## 题目描述

这是一个交互题。

给定一棵包含 $n$ 个节点的树，以节点 $1$ 作为根节点。树是一种无环连通图。

我们选择了一个隐藏节点 $x$。为了找到这个节点，你可以进行两种类型的询问：

- d $u$（$1 \le u \le n$）。我们会回答节点 $u$ 与 $x$ 之间的距离。两个节点之间的距离是它们之间最短路径上的边数。
- s $u$（$1 \le u \le n$）。我们会回答从 $u$ 到 $x$ 的路径上的第二个节点。但是，这里有一个限制。如果 $u$ 不是 $x$ 的祖先，你会收到“Wrong answer”判定！

如果节点 $a$ 是节点 $b$ 的祖先，意味着 $a \ne b$ 且从节点 $1$ 到节点 $b$ 的最短路径经过节点 $a$。注意，在本题中，一个节点不是自己的祖先。

你能否在不超过 $36$ 次询问内找到 $x$？隐藏节点在每个测试中是预先固定的，并且与你的询问无关。

## 说明/提示

在第一个样例中，隐藏节点是节点 $5$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1174F/2fc09cdc0e97e7f39493296632ab302b06fdb975.png)

我们首先询问节点 $2$ 与 $x$ 之间的距离。答案是 $3$，所以 $x$ 可能是节点 $4$ 或 $5$。然后我们询问从节点 $3$ 到 $x$ 的路径上的第二个节点。注意这里节点 $3$ 是节点 $5$ 的祖先。我们收到节点 $5$ 作为答案。最后，我们报告隐藏节点是节点 $5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 2
1 3
3 4
3 5
3
5```

### 输出

```
d 2
s 3
! 5```

# 题解

## 作者：JWRuixi (赞：6)

CF 原始难度 $2400$，~~这真的值得黑吗~~。

- 题意

给定一颗以 $1$ 号节点为根的 $n$ 个节点的树，有一个隐藏节点 $x$，你可以和交互机进行如下操作。

1. d $ u $，交互机返回 $u$ 和 $x$ 的距离。
2. s $ u $，交互机返回 $u$ 到 $x$ 的路径上的第二个数，要求 $u$ 是 $x$ 的祖先。

你需要在 $36$ 步以内求出 $x$，答案输出格式 ```! x```。

- 分析

看到这个 $36$，就应该激动起来。这道题的范围是 $n \le 200000$，而 $\log 200000$ 差不多就是 $18$，就是说你学要在 $\log n$ 的时间内求出答案，于是想到树剖。

如果我们每次询问和 $x$ 深度相同的重儿子和 $x$ 之间的距离，那么我们可以确定两者的 LCA，此时我们在询问 LCA 到 $x$ 路径上的第二个数字，我们就可以将问题进一步转移到询问结果为根的子树上，让后就递归了！

- code

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + c - '0';
			c = getchar();
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using namespace q_wr;

const int maxn = 2e5 + 500;

struct edge {
	int v, nxt;
} e[maxn << 1];

int n, head[maxn], tot, rev[maxn], sz[maxn], dep[maxn], maxd[maxn], depx, son[maxn];

void add (int u, int v) {
	e[++tot] = {v, head[u]};
	head[u] = tot;
}

void dfs (int u, int fa) {
	dep[u] = dep[fa] + 1, sz[u] = 1, maxd[u] = dep[u];
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (v == fa) continue;
		dfs(v, u);
		sz[u] += sz[v];
		maxd[u] = max(maxd[u], maxd[v]);
		if (sz[v] > sz[son[u]] && maxd[v] >= depx) son[u] = v;
	}
}

int main () {
	n = read();
	for (int i = 1; i < n; i++) {
		int u = read(), v = read();
		add(u, v);
		add(v, u);
	}
	printf("d 1\n");
	fflush(stdout);
	depx = read() + 1;
	dfs(1, 0);
	int u = 1;
	while (true) {
		if (dep[u] == depx) {
			printf("d %d\n", u);
			fflush(stdout);
			int d = read();
			if (!d) {
				printf("! %d", u);
				fflush(stdout);
				return 0;
			}
			u = rev[dep[u] - d / 2];
			printf("s %d\n", u);
			fflush(stdout);
			u = read();
			if (dep[u] == depx) {
				printf("! %d", u);
				fflush(stdout);
				return 0;
			}
		}
		rev[dep[u]] = u;
		u = son[u];
	}
}
```

---

## 作者：wucstdio (赞：6)

先晒一下我的VP提交界面：

![](https://cdn.luogu.com.cn/upload/pic/60614.png)

题意：给你一棵树，让你在$36$次询问之内找到隐藏节点$x$。

首先我们考虑，$36$这个数字$\approx2\log n$，也就是说我们需要在$O(\log n)$次询问之内得到答案。

一说$\log$，肯定会想到二分。接下来我们考虑，如何才能在$2$次操作之内将候选节点个数减少一半。

首先当然要询问$d$ $1$，得到目标点的深度。

考虑树链剖分。一个点到$1$的路径上经过的轻边数量是$O(\log n)$级别的，能否利用一下这个性质呢？（假设目标节点是$12$号点）

![](https://cdn.luogu.com.cn/upload/pic/60616.png)

首先我们沿着以$1$号点为链头的重链一直走，直到到达链的底端：

![](https://cdn.luogu.com.cn/upload/pic/60617.png)

然后询问$14$号点到12号点的距离，得到的答案是$7$。

此时，由于我们知道了目标节点的深度，所以就能直接算出来它们的LCA是$1$。

接下来询问LCA上哪棵子树走可以走到目标节点，得到的答案是$2$。然后再沿着$2$号节点的重链一直往下走，到达链底：

![](https://cdn.luogu.com.cn/upload/pic/60619.png)

然后重复上述操作，得到它们的LCA是$6$，询问$s$ $6$就可以得到答案。

注意到，每进行一次操作，相当于沿着轻边向下走了一步，因此复杂度是对的。

在具体实现上，发现可以每次不是走到链底，而是走到和目标点深度相同的点。这样代码可以少很多细节，计算LCA也更好计算。

然后就TLE on test 66了……

最后一个坑：重链的深度可以很浅，所以沿着重链走不一定能走到深度和$x$相同的点。需要在处理重儿子的时候特判。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct Edge
{
	int to;
	int nxt;
}e[400005];
int n,m,edgenum,head[200005],dep[200005],pa[200005],size[200005],depx,x[200005],son[200005],maxd[200005];
void add(int u,int v)
{
	e[++edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs_pre(int node)
{
	dep[node]=dep[pa[node]]+1;
	size[node]=1;
	maxd[node]=dep[node];
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node])continue;
		pa[to]=node;
		dfs_pre(to);
		maxd[node]=max(maxd[node],maxd[to]);
		size[node]+=size[to];
		if(size[to]>size[son[node]]&&maxd[to]>=depx)son[node]=to;
	}
}
void solve()
{
	int node=1;
	while(1)
	{
		if(dep[node]==depx)
		{
			printf("d %d\n",node);
			fflush(stdout);
			int d;
			scanf("%d",&d);
			if(d==0)
			{
				printf("! %d\n",node);
				fflush(stdout);
				exit(0);
			}
			node=x[dep[node]-d/2];
			printf("s %d\n",node);
			fflush(stdout);
			scanf("%d",&node);
			if(dep[node]==depx)
			{
				printf("! %d\n",node);
				fflush(stdout);
				return;
			}
		}
		x[dep[node]]=node;
		node=son[node];
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	printf("d 1\n");
	fflush(stdout);
	scanf("%d",&depx);
	depx++;
	dfs_pre(1);
	solve();
	return 0;
}
```

---

## 作者：wurzang (赞：6)

询问次数为 2log 级别，考虑点分治。

如果点不是 $x$ 的祖先，那么往点的祖先所在的子树分治，否则询问 $s$，往询问结果所在的子树分治。

次数是 $2\log n+1$ 左右，稍微剪枝就可以过了。

[代码见这](https://codeforces.com/contest/1174/submission/119574088)

---

## 作者：蒟蒻君HJT (赞：5)

#### difficulty - 2400

#### [problem link](https://www.luogu.com.cn/problem/CF1174F)

#### [code](https://codeforces.com/contest/1174/submission/191801746)

写这篇题解的原因是目前题解区有的题解需要特判，比较烦，所以这里给出一种最简单的，没有任何细节的做法。

先轻重链剖分，并询问 $x$ 的深度 $d_x$。

实时维护结点 $x$ 存在的子树 $u$。初始 $u=1$。

每次迭代过程中，先从 $u$ 开始一直走重儿子走到底为止，最终达到 $v$。

询问 $v$ 与 $x$ 间距离 $t$。此时可能有两种情况：

- $x$ 为 $v$ 祖先，则必然满足 $d_v-d_x=t$。可直接返回 $v$ 的 $t$ 级祖先，迭代结束。

- $x$ 与 $v$ 没有祖先后代关系。则可以通过 $d_x,d_v,t$ 求出 $d_{\text{lca}(x,v)}$，进而得出 $\text{lca}(x,v)$。此时我们询问 $\text{s}(\text{lca}(x,v))$，得到 $u'$ 为新一轮迭代的 $u$。

- 注意不可能存在 $v$ 为 $x$ 祖先的情况，因为已经走到底了。

由于每次出现第二种情况时，从 $\text{lca}(x,v)$ 往 $\text{s}(\text{lca}(x,v))$ 走时一定是沿着轻边走，所以子树大小从 $u$ 变为 $u'$ 至少缩小一半，迭代次数至多为 $\log n$ 次，每次迭代最多询问两次，故询问次数足够，可以通过。

具体实现时只需求出每个结点的深度 $d_x$ ，重儿子 $hson_x$ 和父节点 $fa_x$，求 $k$ 级祖先时暴力跳 $fa_x$ 即可，由于每条重链至多只会在一次迭代中出现，因此总的时间复杂度为 $\mathcal{O}(n)$。

核心代码：

$\text{dx}$ 表示目标点 $x$ 的深度，$\text{Fa}(a,b)$ 函数返回 $a$ 的 $b$ 级祖先。
 
```cpp
int dx = ask_d(1) + 1, u = 1;
while(true){
 int v = u;
 while(hson[v]) v = hson[v];
 int t = ask_d(v);
 if(dep[v] - dx == t) return ans(Fa(v, t)),(void)0;
 u = Fa(v, (dep[v] - dx + t) / 2);
 u = ask_s(u);
}
```


---

## 作者：Refined_heart (赞：5)

[CF1174F Ehab and the Big Finale](https://www.luogu.com.cn/problem/solution/CF1174F)

~~来一发乱搞做法）~~

首先我们可以考虑询问出目标点的深度。然后考虑如何在 $O(\log n)$ 次询问中解决问题。

容易想到**点分治**。

这样每次会找到重心，然后利用第一个操作来判断询问的重心是不是目标点的祖先。

但是我发现这样会被菊花卡掉，而 $2$ 操作可以很好地解决这件事情。

所以我们大力猜菊花的 deg 是多少，在 deg 大的时候采用 $2$ 操作来越过这个限制，调整一下参数就可以过掉了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef double db;
#define int long long
#define fi first
#define se second
#define mk make_pair
#define pb emplace_back
#define poly vector<int>
#define Bt(a) bitset<a>
#define bc __builtin_popcount
#define pc putchar
#define ci const int&
const int mod = 1e9 + 7;
const db eps = 1e-10;
const int inf = (1 << 30);
inline int Max(ci x, ci y) {return x > y ? x : y;}
inline int Min(ci x, ci y) {return x < y ? x : y;}
inline db Max(db x, db y) {return x - y > eps ? x : y;}
inline db Min(db x, db y) {return x - y < eps ? x : y;}
inline int Add(ci x, ci y, ci M = mod) {return (x + y) % M;}
inline int Mul(ci x, ci y, ci M = mod) {return 1ll * x * y % M;}
inline int Dec(ci x, ci y, ci M = mod) {return (x - y + M) % M;}
typedef pair<int, int> pii;
inline int Abs(int x) {return x < 0 ? -x : x;}
//char buf[1<<21],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char Obuf[105000],*O=Obuf;//Siz shoule be the size of Out File
int pst[30],ptop;
inline void Fprint(){fwrite(Obuf,1,O-Obuf,stdout);}
inline void Fwrite(int x){
  if(x==0){*O++='0';return;}
  if(x<0)*O++='-',x=-x;ptop=0;
  while(x)pst[++ptop]=x%10,x/=10;
  while(ptop)*O++=pst[ptop--]+'0';
  if(O-Obuf>100000)Fprint(),O=Obuf;
}
inline int read() {
    int s = 0, w = 1;
    char ch = getchar();
    while (!isdigit(ch)) {if (ch == '-') w = -1;ch = getchar();}
    while (isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
    return s * w;
}
inline void write(int x) {
    if (x < 0)putchar('-'), x = -x;
    if (x > 9)write(x / 10);
	pc(x % 10 + '0');
}
inline int qpow(int x, int y) {
    int res = 1;
    while (y) {if (y & 1)res = Mul(res, x);x = Mul(x, x);y >>= 1;}
    return res;
}
inline void cadd(int &x, int y) {x += y;}
inline void cmul(int &x, int y) {x *= y;}
inline void cmax(int &x, int y) {x = Max(x, y);}
inline void cmin(int &x, int y) {x = Min(x, y);}
const int N = 4e5 + 10;
namespace Refined_heart{
	#define ff fflush(stdout)
	int head[N],tot,n,m;
	int dep[N],pa[N];
	struct E{int nxt,to;}e[N];
	inline void link(int x,int y){
		e[++tot]=(E){head[x],y};
		head[x]=tot;
	}
	void dfs(int x,int fa){
		pa[x]=fa;
		dep[x]=dep[fa]+1;
		for(int i=head[x];i;i=e[i].nxt){
			int j=e[i].to;
			if(j==fa)continue;
			dfs(j,x);
		}
	}
	inline int op(int opt,int u){
		if(opt==1){cout<<"d "<<u<<'\n';ff;}
		else if(opt==2){cout<<"s "<<u<<'\n';ff;}
		else {cout<<"! "<<u<<'\n';ff;return 0;}
		int as=read();
		return as;
	}
	int siz[N],root,ms,mson[N],vis[N],All,deg[N];
	inline bool ck(int x,int fa){return !(x==fa||vis[x]);}
	void DFS(int x,int fa){
		siz[x]=1;++All;
		for(int i=head[x];i;i=e[i].nxt){
			int j=e[i].to;
			if(j==fa)continue;
			if(vis[j])continue;
			DFS(j,x);siz[x]+=siz[j];
		}
	}
	
	void FINDROOT(int x,int fa){
		mson[x]=Max(siz[x],All-siz[x]);
		if(ms>mson[x]){
			ms=mson[x];
			root=x;
		}
		for(int i=head[x];i;i=e[i].nxt){
			int j=e[i].to;
			if(j==fa||vis[j])continue;
			FINDROOT(j,x);
		}
	}
	int nowroot=1;
	int goaldep;
//	int son[N];
	void work(){
		goaldep=op(1,1)+1;
		if(goaldep==1){
			op(3,1);
			return;
		}
		while(1){
			int val=inf;
			All=0;ms=inf;
			DFS(nowroot,0);
			FINDROOT(nowroot,0);
			if(deg[nowroot]>20000){
				val=op(2,nowroot);
				nowroot=val;
				vis[pa[nowroot]]=1;
				if(dep[val]==goaldep){
					op(3,val);
					return;
				}
				continue;
			}
			val=op(1,root);
			if(!val){
				op(3,root);
				return;
			}
			int cordis=goaldep-dep[root];
			if(cordis!=val)vis[root]=1;
			else {
				nowroot=root;
				vis[pa[root]]=1;
			}
		}
		return;
	}
	void solve(){
		n=read();
		for(int i=1;i<n;++i){
			int u=read(),v=read();
			link(u,v);link(v,u);
			deg[u]++;deg[v]++;
		}
		dfs(1,0);
		work();
	}
}
signed main(){
//	freopen("checker.out","r",stdin);
//	freopen("getin.in","w",stdout);
	Refined_heart::solve();
	return 0;
}


```


---

## 作者：tommymio (赞：3)

看到不超过 $36$ 次询问显然可以想到是 $\log $ 时间复杂度。

暴力的做法自然是 $u$ 从 $1$ 开始，每次询问 $u\to x$ 路径上的第 $2$ 个节点，暴力跳并继续询问，期望询问次数为 $\log n$，但链的询问次数为 $O(n)$。这和树剖很像，都是在链时存在 $\text{worst case}$ ，在期望情况下为 $\log n$。于是我们可以考虑树剖优化。

可以先使用一次 $\text{d 1}$ 的询问，得到 $x$ 的深度。然后从点 $1$ 开始向下跳重链，跳到重链尾再询问 $\text{d u}$，根据回答的值，我们可以算出此时的 $\text{lca}(u,x)$。然后再询问 $\text{s }lca(u,x)$ 得到 $x$ 所在的子树位于 $\text{lca}(u,x)$ 的位置，然后继续跳。

但是这样会 $\text{TLE}$，由于每次跳到重链尾都没有保存任何信息，仅凭深度，我们很难得到 $\text{lca}(u,x)$ 的值。所以我们不真正的一次跳到重链尾，而是每次直接跳一步，要么跳到重链尾，要么跳到和 $x$ 点深度相同的位置，此时深度小于 $u$ 的所有重链上的点信息都已被保存，所以我们很容易得到 $\text{lca}(u,x)$ 的值。

时间复杂度为 $O(n)$，能在 $\log n$ 个询问内得到答案。

**Show the Code**
```cpp
#include<cstdio>
#include<cstdlib>
int depx,res,cnt=0;
int h[200005],to[400005],ver[400005];
int mp[200005],size[200005],son[200005],dep[200005],maxDep[200005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void query(int op,int x) {
	if(op==1) {printf("d %d\n",x);fflush(stdout);scanf("%d",&res);}
	else if(op==2) {printf("s %d\n",x);fflush(stdout);scanf("%d",&res);}
	else {printf("! %d\n",x);exit(0);}
}
inline void dfs(int x,int fa) {
	size[x]=1; maxDep[x]=dep[x];
	for(register int i=h[x];i;i=ver[i]) {
		int y=to[i];
		if(y==fa) continue;
		dep[y]=dep[x]+1; dfs(y,x); size[x]+=size[y]; maxDep[x]=max(maxDep[x],maxDep[y]);
		if(size[son[x]]<size[y]&&maxDep[y]>=depx) son[x]=y;
	}
}
inline void solve() {
	int cur=1;
	while(1) {
//		printf("%d\n",cur);
		if(dep[cur]==depx) {
			query(1,cur);
			if(res==0) {query(3,cur);}
			cur=mp[depx-res/2];
			query(2,cur);
			if(dep[res]==depx) {query(3,res);}
			cur=res;
		}
		mp[dep[cur]]=cur;
		cur=son[cur];
	}
}
int main() {
	int n=read();
	for(register int i=1;i<n;++i) {int x=read(),y=read();add(x,y);add(y,x);}
	query(1,1); depx=res+1; 
	dep[1]=1; dfs(1,-1);
	solve();
	return 0;
}
```



---

## 作者：activeO (赞：1)

## 题目大意

就是给你一颗树，让你在 $ 36 $ 步之内找到隐藏点（并非真隐藏，只是你要找出系统想的树中的点）。两个操作：

- 给交互机一个点，返回他和隐藏点的距离。
- 给交互机一个点，返回这个点到隐藏点路径上的第二个点。

## 思路

怎么都是点分治？来个树剖的！

首先观察 $ 36 $ 这个特殊数，发现 $ 36 \approx 2 \times \log n $。

所以可以想到利用重链的性质：一个点到根节点的路径上经过的轻边数量是 $ \log n $ 的。

首先二分，可以进行 $ d \space 1 $，得到目标点的深度，然后沿着根节点的重链走到底端 $ u $。

然后可以询问 $ u $ 到目标点的距离，根据我们第一步算到的目标点的深度，我们可以判断 $ u $ 和目标点的 lca 就为根节点 $ 1 $。但是这个时候目标节点是不一定在这条重链上的（可以根据求得的深度判断），所以我们就用 $ 2 $ 询问，问从 $ 1 $ 到目标点的路径上的第二个点，然后接着以第二个点为根重复上述的步骤。

然后可以发现如果这样一直跑下去，总会跑到和目标节点同一条重链，这时候想上文一样求得 lca，再进行询问 $ 2 $ 就可以找到目标节点，所以正确性显然。
然后因为树剖的性质，一定能保证询问个数在 $ 36 $ 次以内（每次操作 $ 2 $ 遍询问，所以是 $ 2 \times \log n $）。

然后如果完全照上面打会 TLE，实则在操作中重用沿重链到和目标节点相同深度即可，然后如果如此做就要判断这条重链末端深度够不够目标节点的深度，这里特判一下就行了。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=2e5+10;
int head[maxn],len,n,disx;
int fa[maxn],son[maxn],sz[maxn];
int dep[maxn],maxx[maxn],tmp[maxn];
struct edge{
	int to,nxt;
}e[maxn<<1];

inline void init(){
	memset(head,-1,sizeof(head));
	len=0;
}
void add(int u,int v){
	e[++len].to=v;
	e[len].nxt=head[u];
	head[u]=len;
}

void dfs(int u,int f){
	maxx[u]=dep[u]=dep[f]+1;
	fa[u]=f;
	sz[u]=1;
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		dfs(v,u);
		sz[u]+=sz[v];
		maxx[u]=max(maxx[u],maxx[v]);
		if(sz[son[u]]<sz[v]&&maxx[v]>=disx) son[u]=v;
	}
}

int askd(int x){
	printf("d %d\n",x);
	fflush(stdout);
	scanf("%d",&x);
	return x;
}
int asks(int x){
	printf("s %d\n",x);
	fflush(stdout);
	scanf("%d",&x);
	return x;
}

int main(){
	
	init();
	
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		add(u,v);
		add(v,u);
	}
	
	disx=askd(1)+1;
	
	dfs(1,0);
	
	int u=1;
	
	while(1){
		while(dep[u]<disx){
			tmp[dep[u]]=u;
			u=son[u];
		}
		int d=askd(u);
		if(!d){
			printf("! %d\n",u);
			fflush(stdout);
			return 0;
		}
		int lca=tmp[disx-d/2];
		if(dep[lca]+1==disx){
			printf("! %d\n",asks(lca));
			fflush(stdout);
			return 0;
		}
		u=asks(lca);
	}
	
	return 0;
}

```


---

## 作者：xfrvq (赞：0)

[$\tt Link$](/problem/CF1174F)。

$36=2\left\lceil\log{2\times10^5}\right\rceil$。

我们考虑树链剖分，然后用这样的一个递归函数求解答案：

+ 首先通过 $\texttt{d }1$ 求出 $x$ 的深度 $d$。
+ $\texttt{solve(}u\texttt{)}$：答案 $x$ 在 $u$ 的子树里。
+ 从 $u$ 跳重链跳到与 $x$ 深度相同的一个点 $p$。
+ 询问 $\texttt{d }p$，这时可以知道 $\texttt{lca(}p,x\texttt{)}$，设其为 $q$。
+ 询问 $\texttt{s }q$，设答案为 $r$，这时转移到了 $\texttt{solve(}r\texttt{)}$。

每一次操作都走了一次轻边，因此子树大小至少减半。而一开始的子树大小是 $n$，所以 $\tt solve$ 只会迭代 $\log n$ 次，每次迭代产生两次询问，可过。

关于 $\texttt{lca(p,x)}$ 怎么求：维护 $1,\cdots,u$ 的链，然后根据深度进行计算即可。

```cpp
#import<iostream>
#import<vector>

using namespace std;

const int N = 2e5 + 5;

int n,dx,dep[N],siz[N],son[N],mxd[N],tmp[N];
vector<int> G[N];

void dfs(int u = 1,int fa = 0){
	mxd[u] = dep[u] = dep[fa] + 1;
	siz[u] = 1;
	for(int v : G[u]) if(v != fa){
		dfs(v,u);
		siz[u] += siz[v];
		mxd[u] = max(mxd[u],mxd[v]);
		if(siz[v] > siz[son[u]] && mxd[v] >= dx) son[u] = v;
	}
}

int main(){
	cin >> n;
	for(int i = 1;i < n;++i){
		int u,v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	cout << "d " << 1 << endl; cin >> dx; ++dx; dfs();
	for(int u = 1,t;;){
		if(dep[u] == dx){
			cout << "d " << u << endl; cin >> t;
			if(!t) return cout << "! " << u << endl,0;
			u = tmp[dep[u] - t / 2];
			cout << "s " << u << endl; cin >> u;
			if(dep[u] == dx) return cout << "! " << u << endl,0;
		}
		tmp[dep[u]] = u,u = son[u];
	}
	return 0;
}
```

---

## 作者：Endt (赞：0)

# Ehab and the Big Finale-题解

### 题意

这是一道交互题。

给定一棵 $n$ 个节点的树，根节点为 $1$，你需要找到节点 $x$。

你可以进行如下两种询问：

- 某节点到 $x$ 的距离。

- $x$ 的某祖先节点包含 $x$ 的那棵子树。

最多询问 $36$ 次。

### 暴力

从根节点开始，不断地进行询问二，总能找到 $x$。

询问次数为 $x$ 的深度，最坏为 $n$。

### 优化

$36$ 约是 $\log n$ 级别的树，我们需要在很少的询问次数内尽量向 $x$ 跳更多。在一条链上，每个点到 $x$ 的距离肯定是单谷的而这个谷就是 $x$ 的祖先（于是我最开始写了三分但询问次数的常数太大了），而且相邻两点到 $x$ 的距离只差 $1$。此时，我们分别询问链头和链尾与 $x$ 的距离，就可以推出 $x$ 祖先在这条链上的位置。

现在我们成功用 $2$ 次询问一代替了若干次询问二，但依然能被卡成 $n$ 级别的询问次数，为了让这个“若干”更大，我们进行重链剖分，根据重链剖分的性质，我们只会在 $\log n$ 条链上操作。

噫！好！我们过了！

### 代码

```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Pub  public

using std::min;using std::max;

int n;
class Node{
Pub:std::vector<int> s;int fa=0;
    int size=0;
    int dfn=0,id=0;
}p[200005];
int a[200005];
class Chain{
Pub:int l=0,r=0;
}c[200005];

void dfs(int x){
    p[x].size=1;
    for(int i:p[x].s){
        if(i==p[x].fa)continue;
        else p[i].fa=x;
        dfs(i);
        p[x].size+=p[i].size;
    }
}
int dfn,cntc;
void getchain(int x){
    if(x==0)return;
    ++dfn;
    p[x].dfn=dfn;a[dfn]=x;
    if(p[x].id==0){
        ++cntc;
        p[x].id=cntc;
        c[p[x].id].l=p[x].dfn;
    }
    int heavyson=0;
    for(int i:p[x].s)
        if(i!=p[x].fa&&p[i].size>p[heavyson].size)
            heavyson=i;
    if(heavyson==0)c[p[x].id].r=dfn;
    else{
        p[heavyson].id=p[x].id;
        getchain(heavyson);
        for(int i:p[x].s)
            if(i!=p[x].fa&&i!=heavyson)
                getchain(i);
    }
}

int DDD[200005];
int D(int x){
    if(DDD[x]!=-1)return DDD[x];
    int ans;
    printf("d %d\n",x);
    fflush(stdout);
    scanf("%d",&ans);
    if(ans==-1)exit(0);
    DDD[x]=ans;
    return ans;
}
int S(int x){
    int ans;
    printf("s %d\n",x);
    fflush(stdout);
    scanf("%d",&ans);
    if(ans==-1)exit(0);
    return ans;
}
int main(){
    scanf("%d",&n);
    std::fill(DDD+1,DDD+1+n,-1);
    for(int i=1;i<n;++i){
        int x,y;scanf("%d%d",&x,&y);
        p[x].s.push_back(y),p[y].s.push_back(x);
    }
    dfs(1);
    getchain(1);

    int x=1;
    while(1){
        int L=c[p[x].id].l,R=c[p[x].id].r,ans;
        int B1=D(a[L]),B2=D(a[R]),A=(B1+B2-R+L)/2;
        ans=a[L+B1-A];

        if(A==0){
            printf("! %d\n",ans);
            fflush(stdout);
            return 0;
        }else{
            x=S(ans);
            DDD[x]=A-1;
        }
    }

    return 0;
}
```

---

## 作者：gyyyyx (赞：0)

## 思路

一看到是交互题，立刻想到看给定的询问次数。

不少于 $36$ 次？这么少？肯定带 $\log$。

然后看题面和树有关，马上想到[树链刨分](https://www.luogu.com.cn/blog/s19418/shu-lian-pao-fen)。

树剖有一个重要的性质：两点的路径中轻（重）链的个数是 $O(\log_2{n})$ 级别的。

能否利用这个性质？

下面假设知道目标节点的深度（其实一开始询问 ```d 1``` 就可以知道）。

每次都沿着重链走到与目标节点深度相同的节点 $x$。

如果这个节点是目标节点（即：询问 ```d x``` 返回 $0$）那么就是 $x$（真废话）。

否则就找到它们的 $lca$ 然后询问 ```s lca``` ，就是问那棵子树可以到达目标节点。

这里可以做一个特判，如果该节点的深度和目标节点的深度一样，就直接输出该节点（不知道没写这个会不会挂掉，没试过）。

然后我们就从 $lca$ 开始重复次步骤，知道知道目标节点为止。

因为每进行一次操作相当于沿着轻边向下走了一步，因此复杂度没有问题。

但是，如何求 $lca$ 呢？

因为求 $lca$ 最快也要 $O(\log_2n)$ 的时间，但加上套跳链的复杂度，那就要带个平方了呀。

当然，作为一道可以写的题，还是有办法的。

假设有一个与目标节点深度同为 $d$ 的节点 $x$，距离为 $s$，我们将每次经历过的节点记录下为一个数组 $a$，$a_i$ 表示经历到深度为 $i$ 的节点，那 $lca$ 就等于 $a_{d-\frac{s}{2}}$。

这样就可以 $O(1)$ 求 $lca$ 了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int n;
vector <int> t[N];
int dep[N],siz[N],son[N],fa[N],maxd[N];
int depx,path[N],d,ans(1);
inline void dfs(int u,int f){
    fa[u]=f;dep[u]=dep[f]+1;siz[u]=1;maxd[u]=dep[u];
    for(int i(0);i<t[u].size();++i){
        int v(t[u][i]);
        if(v==f) continue;
        dfs(v,u);
        maxd[u]=max(maxd[u],maxd[v]);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]&&maxd[v]>=depx) son[u]=v;
    }
}
inline void solve(){
    while(1){
        if(dep[ans]==depx){
            printf("d %d\n",ans);fflush(stdout);
            scanf("%d",&d);
            if(!d){
                printf("! %d\n",ans);fflush(stdout);
                return;
            }
            ans=path[dep[ans]-d/2];
            printf("s %d\n",ans);fflush(stdout);
            scanf("%d",&ans);
            if(dep[ans]==depx){
                printf("! %d\n",ans);fflush(stdout);
                return;
            }
        }
        path[dep[ans]]=ans;
        ans=son[ans];
    }
}

int main(){
    scanf("%d",&n);
    for(int i(1);i<n;++i){
        int u,v;scanf("%d%d",&u,&v);
        t[u].push_back(v);
        t[v].push_back(u);
    }
    printf("d 1\n");fflush(stdout);
    scanf("%d",&depx);++depx;
    dfs(1,1);
    solve();
    return 0;
}
```

---

