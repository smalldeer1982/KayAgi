# [AGC018D] Tree and Hamilton Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc018/tasks/agc018_d

$ N $ 頂点の木があり、頂点には $ 1 $ から $ N $ の番号がついています。 この木の $ i $ 番目の辺は頂点 $ A_i $ と $ B_i $ を結んでいて、その長さは $ C_i $ です。

joisinoお姉ちゃんは、$ N $ 頂点の完全グラフを作りました。 なお、この完全グラフの頂点 $ u $ と $ v $ を結ぶ辺の長さは、木での頂点 $ u $ と $ v $ の最短距離になっています。

joisinoお姉ちゃんは、この完全グラフのハミルトンパス(※)のうち、最も長いものの長さを知りたくなりました。 joisinoお姉ちゃんの作った完全グラフのハミルトンパスのうち、最も長いものの長さを求めてください。

## 说明/提示

### 注釈

あるグラフのハミルトンパスとは、そのグラフのパスであって、すべての頂点をちょうど一度だけ通るようなものを指します。

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- 入力で与えられるグラフは木である。
- $ 1\ \leq\ C_i\ \leq\ 10^8 $
- 入力はすべて整数である。

### Sample Explanation 1

$ 5 $ → $ 3 $ → $ 1 $ → $ 4 $ → $ 2 $ というハミルトンパスを考えると、その長さは、 $ 5+8+15+10=38 $ となります。長さ $ 39 $ 以上のハミルトンパスは作れないので、この例の答えは $ 38 $ になります。

## 样例 #1

### 输入

```
5
1 2 5
3 4 7
2 3 3
2 5 2```

### 输出

```
38```

## 样例 #2

### 输入

```
8
2 8 8
1 5 1
4 8 2
2 5 4
3 8 6
6 8 9
2 7 12```

### 输出

```
132```

# 题解

## 作者：installb (赞：20)

这题还是挺有意思的。

题目要求的是哈密顿路径，这个有点不好处理，我们先转化成求哈密顿回路后减去一条路径。  

## 1.求回路

这就是个套路题了，我们不考虑每条路径，而考虑每一个边最多被包含在几条路径内。  
对于每一个边，如果把它断开后把树分成了两个大小分别为 $x$ 和 $y$ 的连通块，则有 $\min(x,y)$ 条路径通过它，也就是说从小连通块中的点出发的路径都会经过这条边一次。  
放张图：  

![](https://cdn.luogu.com.cn/upload/image_hosting/z6nujmip.png)

其它被覆盖的路径**完全没有变化**，而被圈出的路径被经过次数增加了，我们完全可以随便构造一个方案然后不停像图中这么做。

这样是答案的理论上界，而我们的方案也达到了这个理论上界。

放道类似的[题](https://www.luogu.com.cn/problem/CF1280C)。  

然后把每条边的贡献加起来就好了。

## 2.减去一条路径

**下面才是重点了**  

接下来在于要去掉哪条路径。  

如果你觉得随便去哪一条都行，就去最小的那条吧，那么连样例都过不去。  

因为可能这条路径**不包含在任意一个最优解中**。  

事实上，**不经过重心的路径都不包含在任一最优解中**。  
因为对于树的重心，把它作根，它不存在 $siz> \frac{n}{2}$ 的子树。可以想象如果存在 $siz> \frac{n}{2}$ 的子树，那么必定有至少一条路径是在这棵子树内部的，因为其它的子树合起来都不够和这棵子树配对出来那么多经过这个节点的路径。  

每一个子树都 $siz\leq \frac{n}{2}$ 的子树是一定可以做到的。这很显然了，不浪费时间证明这个了。

**树的重心符合这个性质，也只有树的重心符合这个性质。**

这就意味着如果我们可以做到每一条路径，都是在重心的两个不同子树中各取一点相连。

就像最开始出示的那张图一样，我们要是让两条在同一个子树内的路径交叉而经过重心，则一定更优。

![](https://cdn.luogu.com.cn/upload/image_hosting/dvfbruqa.png)

既然所有经过重心的路径都可行，那就删去最短的一条，也就是以中心为一端的边中最短的边。

如果树有两个重心，那么减去两重心之间的边。把边等效为上文的重心。

可以贴代码了  
```cpp
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL ec = 0,hed[200005] = {0},to[400005],w[400005],nxt[400005];
void add_edge(LL f,LL t,LL cst){
	++ ec; to[ec] = t; nxt[ec] = hed[f]; w[ec] = cst; hed[f] = ec;
}

LL siz[200005],mx[200005];
LL ans = 0,n;

void dfs(LL u,LL f){
	siz[u] = 1;
	for(LL i = hed[u];i;i = nxt[i]){
		LL v = to[i];
		if(v == f) continue;
		dfs(v,u);
		siz[u] += siz[v]; mx[u] = max(mx[u],siz[v]);
		ans += 2 * min(siz[v],n - siz[v]) * w[i];
	}
	mx[u] = max(mx[u],n - siz[u]);
}

int main(){
	ios::sync_with_stdio(false);
	LL u,v,ww,g = INF,sub = INF,p1 = 0,p2 = 0;
	cin >> n;
	for(LL i = 1;i < n;i ++){
		cin >> u >>	v >> ww;
		add_edge(u,v,ww);
		add_edge(v,u,ww);
	}
	dfs(1,0);
	for(LL i = 1;i <= n;i ++) g = min(g,mx[i]);
	for(LL i = 1;i <= n;i ++){
		if(mx[i] != g) continue;
		if(!p1) p1 = i;
		else p2 = i;
	}
	for(LL i = hed[p1];i;i = nxt[i]){
		LL v = to[i];
		if(p2 && v != p2) continue;
		sub = min(sub,w[i]);
	}
	cout << ans - sub << endl;
	return 0;
}
```
$\sf{difficulty:\color{red}2813}$  
要求运用重心的性质以及用到一个常用的 trick，思维难度还是挺大的（想不到是重心），代码实现难度还是一如既往的小。

---

## 作者：syzf2222 (赞：6)

前言：

我：原来哈密尔顿路径是一条链

juju：这真是我听到的最废话的废话

做法：

考虑一个经典的构造，我们假设要求的是哈密尔顿回路。

那么显然对于每一条边，都可以经过两倍两边的最小值次，显然存在这样的构造方案。

那么我们现在要删一条边，考虑怎样这种构造就不合法了。

显然如果删掉了两点，切他们的 $lca$ 的子树大小不超过 $n$ 除 $2$，就是不合法的。

换句话说，两点路径不经过重心就是不合法的。

反向思考，这也意味着只要每一条路径都经过重心，那方案就是合法的。所以只要删去过重心的最小的边即可。

注意一个细节，当有两个重心时删去重心之间的边。

```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
const int maxn=2e5+10;
int beg[maxn],nex[maxn],to[maxn],w[maxn],e;
inline void add(int x,int y,int z){
	e++;nex[e]=beg[x];beg[x]=e;to[e]=y;w[e]=z;
	e++;nex[e]=beg[y];beg[y]=e;to[e]=x;w[e]=z;
}
#define ll long long
int n,siz[maxn],mx[maxn];ll ans;
inline void dfs(int x,int fa){
	siz[x]=1;
	for(int i=beg[x];i;i=nex[i]){
		int t=to[i];
		if(t==fa)continue;
		dfs(t,x);siz[x]+=siz[t];
		ans+=2ll*min(siz[t],n-siz[t])*w[i];
		mx[x]=max(mx[x],siz[t]);
	}mx[x]=max(mx[x],n-siz[x]);
}
int main(){
	n=read();
	for(int i=1,x,y,z;i<n;i++)
		x=read(),y=read(),z=read(),add(x,y,z);
	dfs(1,0);int p1=0,p2=0;mx[0]=n+1;
	for(int i=1;i<=n;i++)
		if(mx[i]<mx[p1])p2=p1,p1=i;
		else if(mx[i]<mx[p2])p2=i;
	int tmp=1000000000;
	for(int i=beg[p1];i;i=nex[i]){
		int t=to[i];
		if(t==p2&&mx[p1]==mx[p2]){tmp=w[i];break;}
		tmp=min(tmp,w[i]);
	}printf("%lld\n",ans-tmp);
	return 0;
}
```

后记：

xzy：这不是大经典题，你怎么这都不会？

我：……

深深地感到自己的弱小

---

## 作者：Caiest_Oier (赞：5)

# [AT_agc018_d](https://www.luogu.com.cn/problem/AT_agc018_d)   

做这题的时候被 Eray 和 black_trees 吊打了，完全不会。    

首先考虑构造哈密顿回路。这个算是比较典了，哈密顿回路上界是 $\sum_{i\in E}v_i\times 2\times\min(sz_{ed_i},n-sz_{ed_i})$，具体构造可以将树以重心为根（双重心将边视作根），随便找一个叶子，跨过重心连向另外的叶子，同时删掉当前叶子，从连向的点再次出发，最后所有点都被删除，再连回起点。这是达到了答案的上界的。   

题目要求哈密顿路径，就相当于给哈密顿回路断一条边。如果是双重心，则构造方案只能在两个子树中来回连，所以最优的一定是断两个重心的连边。否则我们找一个离重心最近的点（相邻），在方案（这里的方案需要对于每个相邻的点都保留到最后，因为是重心所以可以做到）中把它延到最后连，答案就减掉这条边。   

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k1,k2,k3,k4,k5,k6,k7,k8,k9;
struct Edge{
	int st;
	int ed;
	int nxt;
	int val;
}E[500003];
int totE,head[500003];
void addEdge(int st,int ed,int val){
	E[++totE].st=st;
	E[totE].ed=ed;
	E[totE].nxt=head[st];
	head[st]=totE;
	E[totE].val=val;
}
int sz[500003],mx[500003],rt1,rt2,ans;
void dfs(int now,int p){
	sz[now]=1;
	for(int i=head[now];i;i=E[i].nxt){
		if(E[i].ed==p)continue;
		dfs(E[i].ed,now);
		sz[now]+=sz[E[i].ed];
		mx[now]=max(mx[now],sz[E[i].ed]);
		ans+=2ll*min(sz[E[i].ed],n-sz[E[i].ed])*E[i].val;
	}
	mx[now]=max(mx[now],n-sz[now]);
	if(rt1==0||mx[now]<mx[rt1])rt1=now,rt2=0;
	else if(mx[now]==mx[rt1])rt2=now;
	return;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		scanf("%lld%lld%lld",&k1,&k2,&k3);
		addEdge(k1,k2,k3);
		addEdge(k2,k1,k3);
	}
	dfs(1,0);
	if(rt2!=0){
		for(int i=1;i<=totE;i++){
			if(E[i].st==rt2&&E[i].ed==rt1){
				ans-=E[i].val;
				printf("%lld",ans);
				return 0;
			}
		}
	}
	k9=-1;
	for(int i=head[rt1];i;i=E[i].nxt){
		if(k9==-1)k9=E[i].val;
		else k9=min(k9,E[i].val);
	}
	ans-=k9;
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：myee (赞：5)

### 思路

考虑反向统计贡献。

一个显然的上界：每个边最多会被计算 $2\min\{siz_1,siz_2\}-[siz_1=siz_2]$ 次（假设其两边点数分别为 $siz_1,siz_2$）；具体就是左右节点之间横跳的贡献，容易发现这是一个比较紧的上界。

我们尝试构造方案尽可能取到这个上界。

我们先考虑双重心的情况，容易发现从一侧重心开始，在左右子树任意交替选择，最后到达另一侧重心，即可取满。

再考虑单重心的情况，那么任一子树大小均 $<n/2$。

使用经典结论（[「ZJOI2018」历史](https://loj.ac/p/2434)，或者 [「POI2015」LOG](https://www.luogu.com.cn/problem/P3586)），我们可以证明，任取重心外一点做起点，以重心做终点，存在遍历整个图的方案使得**步步跨过重心**。

这样唯一会被**算不满的贡献**就是起点和重心之间的边，直接统计这样的边中最小值，从答案中减去即可。

至于单重心时这个算法的最优性，我们考虑只用证明，**无论如何取，至少会有一条和重心相连的边不被取满**。

容易发现，假设起点在重心为根的树上的某个子树内，那么其到根的路径上的边，**总不可能取满贡献。**

因此减去权值最小的和重心相连的边的贡献即可。

总复杂度 $O(n)$。

### Code

核心代码很短。

```cpp
uint n;ullt ans;
std::vector<uint>P;
std::vector<std::pair<uint,uint> >Way[100005];
uint dfs(uint p,uint f){
    uint siz=1,t=0,user;
    for(auto s:Way[p])if(s.first!=f)
        siz+=user=dfs(s.first,p),_max(t,user);
    if(n-siz<=n/2&&t<=n/2)
        P.push_back(p);
    for(auto s:Way[p])if(s.first==f)
        ans+=2llu*std::min(siz,n-siz)*s.second;
    return siz;
}
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    // freopen("QAQ.out","w",stdout);
#endif
    scanf("%u",&n);
    for(uint i=1,u,v,w;i<n;i++)
        scanf("%u%u%u",&u,&v,&w),
        Way[--u].push_back({--v,w}),Way[v].push_back({u,w});
    dfs(0,-1);
    if(P.size()==2){
        for(auto s:Way[P[0]])if(s.first==P[1])ans-=s.second;
    }else{
        uint v=-1;
        for(auto s:Way[P[0]])_min(v,s.second);
        ans-=v;
    }
    printf("%llu\n",ans);
    return 0;
}
```


---

## 作者：Wolfycz (赞：3)

这道题直接计算不好算，我们考虑每条边的贡献，基于一种贪心的思想，我们发现只要围着树的重心跑，就可以使每条边得到充分利用

考虑边i的贡献，我们假定边i割掉后分成两个大小为x，y的联通块，那么贡献则为$2*v[i]*min(x,y)$

因为我们走的不是回路，因此有一条边不会被算两次。如果树的重心只有一个，那么必然减去与重心相连的边权最小的边；如果树的重心有两个，减去两重心相连的边即可

``` cpp
/*program from Wolfycz*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x7f7f7f7f
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
inline char gc(){
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int frd(){
	int x=0,f=1;char ch=gc();
	for (;ch<'0'||ch>'9';ch=gc())	if (ch=='-')    f=-1;
	for (;ch>='0'&&ch<='9';ch=gc())	x=(x<<1)+(x<<3)+ch-'0';
	return x*f;
}
inline int read(){
	int x=0,f=1;char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar())	if (ch=='-')	f=-1;
	for (;ch>='0'&&ch<='9';ch=getchar())	x=(x<<1)+(x<<3)+ch-'0';
	return x*f;
}
inline void print(int x){
	if (x<0)    putchar('-'),x=-x;
	if (x>9)	print(x/10);
	putchar(x%10+'0');
}
const int N=2e5;
int pre[(N<<1)+10],now[N+10],child[(N<<1)+10],val[(N<<1)+10];
int size[N+10],Msize[N+10];
int n,tot,rize,root;
ll Ans;
void join(int x,int y,int z){pre[++tot]=now[x],now[x]=tot,child[tot]=y,val[tot]=z;}
void insert(int x,int y,int z){join(x,y,z),join(y,x,z);}
void dfs(int x,int fa,int v){
	int Max=0; size[x]=1;
	for (int p=now[x],son=child[p];p;p=pre[p],son=child[p]){
		if (son==fa)	continue;
		dfs(son,x,val[p]),size[x]+=size[son];
		Max=max(Max,size[son]);
	}
	Ans+=1ll*min(size[x],n-size[x])*v*2;
	Max=max(Max,n-size[x]);
	Msize[x]=Max;
	if (Max<rize){
		rize=Max;
		root=x;
	}
}
int main(){
	n=read(),rize=inf;
	for (int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		insert(x,y,z);
	}
	dfs(1,0,0);
	int tmp=inf;
	for (int p=now[root],son=child[p];p;p=pre[p],son=child[p]){
		tmp=min(tmp,val[p]);
		if (Msize[root]==Msize[son]){
			Ans-=val[p];
			printf("%lld\n",Ans);
			return 0;
		}
	}
	printf("%lld\n",Ans-tmp);
	return 0;
}
```

---

## 作者：I_LOVE_MATH (赞：2)

[更好的阅读体验](https://www.cnblogs.com/lintianchen/p/18679648)

### 题目大意

给出一棵有 $N$ 个点有边权的无根树，现有一个有 $N$ 个点的完全图，两点间边权即为他们在树上的简单路径长度，求这个图最长的哈密顿路径的长度。

### 解题思路

先考虑最长哈密顿回路长度。

要使其最长，就需要尽可能多地经过每一条边，考虑树上一条边能做出的最大贡献。

设这条边为 $(u,fa)$，由于是哈密顿回路，有出有进且不能重复访问点，可以得到访问次数上界为 $2\min(size_u,n-size_u)$。

考虑能否让每条边取到这个上界，假设子树的点数小于子树外点数，可以发现取到上界时**不能有路径在子树内部**，因为子树点数本来就少，又被自己匹配掉一些，就会使经过这条边的最大次数减少，如果大于同理，也不能有路径完全在子树外。

为了方便讨论，我们不妨**钦定重心为树根**（如果重心有两个就可以缩点成一个），根据重心的性质，不会有子树点数大于子树外点数的情况，就避免了考虑另一种情况。

于是可以得到：**不能有路径在一个子树内部，即每条路径都要经过重心，就可以取到最值**（补充：一个重心可以就只在达重心上，两个重心必须经过连接两个重心的边），我们只需将答案加上最值即可。

现在我们考虑哈密顿路径，就是在回路的基础上减去一条最短的路径。

- 一个重心：此时最小值一定是在终点在重心上，那么就可以钦定连接重心的最小边为最后一条边，删去它损失必定最小。
- 两个重心：由于两个重心必须经过连接两个重心的边，那么最短的路径即恰好为连接两个重心的边。

时间复杂度：$O(n)$。

关于讨论区问题的补充：

证明最大哈密顿回路去掉最小边一定是最大哈密顿路径。

如果它不是最大哈密顿回路，即存在在同一棵子树的路径，由于一条路径会匹配掉两个点，那么就会使得经过的连接重心的边的访问次数减 $2$。

如图，中间的边少访问了两次：（非原创，侵删）

![](https://cdn.luogu.com.cn/upload/image_hosting/dvfbruqa.png)

因为少了两次，而我们的哈密顿路径选取了最小的边，只少一次，因此它的哈密顿回路已经小于最大的哈密顿路径，所有哈密顿路径更小于最大的哈密顿路径。

### 代码
```cpp
#include<bits/stdc++.h>
#define endl "\n"
#define ll long long
using namespace std;

const int N = 1e5 + 10;

struct edge
{
	int to, w, next;
} e[N << 1];

ll n, tot, ans, p1, p2;
ll h[N], sz[N], mx[N];

void add(int u, int v, int w)
{
	tot++;
	e[tot].to = v;
	e[tot].w = w;
	e[tot].next = h[u];
	h[u] = tot;
}

void dfs(int u, int fa)
{
	sz[u] = 1;
	for (int i = h[u]; i; i = e[i].next)
	{
		int v = e[i].to;
		if (v == fa)
		{
			continue;
		}
		dfs(v, u);
		sz[u] += sz[v];
		mx[u] = max(mx[u], sz[v]);
		ans += 2 * min(sz[v], n - sz[v]) * e[i].w;
	}
	mx[u] = max(mx[u], n - sz[u]);
}

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w), add(v, u, w);
	}
	dfs(1, 0);
	ll mn = LONG_LONG_MAX;
	for (int i = 1; i <= n; i++)
	{
		mn = min(mn, mx[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		if (mx[i] == mn)
		{
			if (!p1)
			{
				p1 = i;
			}
			else
			{
				p2 = i;
			}
		}
	}
	mn = LONG_LONG_MAX;
	for (int i = h[p1]; i; i = e[i].next)
	{
		int v = e[i].to;
		if (p2 && v != p2)
		{
			continue;
		}
		mn = min(mn, (ll)e[i].w);
	}
	cout << ans - mn << endl;
	return 0;
}
```

---

## 作者：GIFBMP (赞：1)

直接做不太好做，考虑先构造哈密顿回路，再删掉一条边得到答案。

考虑如何构造哈密顿回路。对于树上的一条边，如果它两边的连通块大小分别为 $x$，$y$，那么这条边最多会被贡献 $2\times\min(x,y)$ 次，这也就是哈密顿回路长度的上界。证明可以自行画图感性理解。

接着我们考虑删掉一条树上的路径。但是有的路径在最长哈密顿回路中不一定会出现，我们考虑什么样的路径是一定会出现的。我们拿出树的重心当作根，此时为了让从它连出的几条边贡献都达到上界，哈密顿回路中的每一条路径都会横跨重心的两个子树，因此经过重心的路径一定会出现。

同时我们假设存在一条在最优解中的路径，使得它不经过重心，假设它在重心的子树 $x$ 中。根据重心的性质，$sz_x\le \lfloor\dfrac{n}{2}\rfloor$，因此 $\min(sz_x,n-sz_x)=sz_x$，因为这条路径在子树内部，使得根连到 $x$ 的边最多只能被贡献 $2\times sz_x-1$ 次，与前面的推导不符。至此，我们证明了：**一条路径在最优解中出现，当且仅当它经过重心。**

所以我们只要删掉经过重心的最短路径即可。换句话说，对于一个重心的情况，只要删掉重心连出的最短边，对于两个重心的情况，删掉它们中间的点即可。

时间复杂度 $\Theta(n)$。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
const int MAXN = 1e5 + 10 , INF = 0x3f3f3f3f ;
typedef long long ll ;
ll ans ;
int n , fir[MAXN] , tot , sz[MAXN] , mx[MAXN] , mn = INF , rt[5] , cnt ;
struct edge {int to , nxt , w ;} e[MAXN << 1] ;
void add (int u , int v , int w) {e[++tot].to = v ; e[tot].nxt = fir[u] ; fir[u] = tot ; e[tot].w = w ;} 
void dfs (int x , int fa) {
	sz[x] = 1 ;
	for (int i = fir[x] ; i ; i = e[i].nxt) {
		int v = e[i].to , w = e[i].w ;
		if (v == fa) continue ;
		dfs (v , x) , sz[x] += sz[v] , mx[x] = max (mx[x] , sz[v]) ;
		ans += (ll)w * 2LL * min (sz[v] , n - sz[v]) ;
	}
	mx[x] = max (mx[x] , n - sz[x]) ; mn = min (mn , mx[x]) ;
} 
int main () {
	scanf ("%d" , &n) ;
	for (int i = 1 , u , v , w ; i < n ; i++)
		scanf ("%d%d%d" , &u , &v , &w) , add (u , v , w) , add (v , u , w) ;
	dfs (1 , 0) ;
	for (int i = 1 ; i <= n ; i++)
		if (mx[i] == mn) rt[++cnt] = i ;
	int ret = INF ;
	for (int i = fir[rt[1]] ; i ; i = e[i].nxt) {
		int v = e[i].to , w = e[i].w ;
		if (cnt == 2 && v != rt[2]) continue ;
		ret = min (ret , w) ;
	}
	printf ("%lld\n" , ans - ret) ;
	return 0 ;
}
```

---

## 作者：_Cheems (赞：0)

等价于找一个排列 $p$，求最小权值 $\sum\limits_{i<n} dist(p_i,p_{i+1})$。

乍一看难以下手，任意定一个根，转化为 $\sum\limits_{i<n} dep_{p_i}+dep_{p_{i+1}}-2dep_{lca(p_i,p_{i+1})}$。

前两项只和起点终点有关，即为 $2\sum dep_i-dep_{p_1}-dep_{p_n}$。

对于 $lca$ 项，一个简单的想法是尽量取到根。于是很容易想到定重心为根。同时选取两个最小的 $dep$ 分别做起点终点，这是上界。

显然起点为重心，终点为它的一个儿子。我们发现，当只有一个重心时，确实可以构造达到上界。具体来说，将每个儿子子树染色，删去终点，将它们排个序，然后经典地让 $i$ 和 $i+\frac n2$ 配对，得到若干异色配对（可能剩下一个电灯泡），因为不存在绝对众数所以可行。然后拼起来即可。

对于有两个重心的情况，不妨在两个重心之间建立虚点，然后同上。结论就是删去重心之间的边。

$O(n)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pir pair<int, int>
const int N = 1e5 + 5;
int n, u, v, w, siz[N], d[N], ans;
vector<pir> to[N];
vector<int> zx;

inline void add(int u, int v, int w) {to[u].push_back({v, w}), to[v].push_back({u, w});} 
inline void dfs(int u, int from){
	siz[u] = 1; 
	int mx = 0;
	for(auto _ : to[u]){
		int v = _.first, w = _.second;
		if(v ^ from) dfs(v, u), siz[u] += siz[v], mx = max(mx, siz[v]);
	}
	mx = max(mx, n - siz[u]);
	if(mx <= n / 2) zx.push_back(u);
}
inline void dfs2(int u, int from){
	for(auto _ : to[u]){
		int v = _.first, w = _.second;
		if(v ^ from) d[v] = d[u] + w, dfs2(v, u);
	}
	ans += d[u] * 2;
}
signed main(){
	cin >> n;
	for(int i = 1; i < n; ++i) scanf("%lld%lld%lld", &u, &v, &w), add(u, v, w);
	dfs(1, 0);
	if(zx.size() == 1){
		int rot = zx[0], mi = 1145141919;
		dfs2(rot, 0);
		for(auto _ : to[rot]) mi = min(mi, _.second);
		cout << ans - mi;
	}
	else{
		int x = zx[0], y = zx[1], xzy;
		for(auto _ : to[x]) if(_.first == y) xzy = _.second;
		dfs2(x, 0);
		cout << ans - xzy;
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

首先考虑最长哈密顿回路。

对于每一条边，我们发现经过他的次数至多是 $2\min(cnt_1,cnt_2)$，其中 $cnt_1,cnt_2$ 为这条边两边的点数。

下面证明可以取到这个上界。

对于有一个重心的情况，考虑其每个儿子的子树中的点分别是 $V_1,V_2,\dots,V_k$，按顺序合并得到 $V'$，取 $V'_1,V'_{\frac n2+1},V'_2,V'_{\frac n2+2},\dots,V'_{\frac n2},V'_n$ 即可取到上界。（将重心扔到任意一个 $V_i$ 中即可）

对于有两个重心的情况，在两边交替取即可取到上界。

考虑哈密顿路径，依然是分类讨论。

对于一个重心的情况，我们可以调整出 $c,i$ 路径，其中 $c$ 为重心，$i$ 为任意点。下面证明删除 $c,i$ 中边权和最小的路径是对的。反证，假设删除 $j,k$ 这一条路径，如果经过 $c$ 那么显然不如 $c,j$，如果不经过 $c$ 那么 $j,k$ 必然在同一个子树里，不妨设子树根为 $rt$，我们发现答案至少变小 $2\operatorname{dist}(rt,c)$，不如删除 $c,rt$。

对于两个重心的情况，可以类似证明删除这两个重心之间的边最优。

总复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
vector<pair<int,int>> vc[1000005];
int minv,rt[1000005],top;
int siz[1000005],n;
void dfs(int now,int fa){
	siz[now]=1;
	int maxv=0;
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		dfs(v.first,now);
		maxv=max(maxv,siz[v.first]); siz[now]+=siz[v.first];
	}
	maxv=max(maxv,n-siz[now]);
	if(maxv<minv){
		minv=maxv;
		top=1; rt[top]=now;
	}
	else if(maxv==minv){
		rt[++top]=now;
	}
}
int ans=0;
void dfs2(int now,int fa,int len){
	siz[now]=1;
	for(auto v:vc[now]){
		if(v.first==fa) continue;
		dfs2(v.first,now,v.second);
		siz[now]+=siz[v.first];
	}
	ans+=siz[now]*len;
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w; cin>>u>>v>>w;
		vc[u].push_back(make_pair(v,w));
		vc[v].push_back(make_pair(u,w));
	}
	minv=1e9;
	dfs(1,0);
	if(top==1){
		dfs2(rt[1],0,0);
		minv=1e9;
		for(auto v:vc[rt[1]]) minv=min(minv,v.second);
		ans*=2;
		ans-=minv;
	}
	else{
		dfs2(rt[1],rt[2],0);
		dfs2(rt[2],rt[1],0);
		ans*=2;
		for(auto v:vc[rt[1]]){
			if(v.first==rt[2]){
				ans+=v.second*(n-1);
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

**[D - Tree and Hamilton Path](https://atcoder.jp/contests/agc018/tasks/agc018_d)（6）**

首先考虑哈密顿回路的情况。一条边的最多的贡献是 $2\times[连接两端点数的较小值]$。现在考虑哈密顿路径。

首先“两边点数最小值”容易让我们想到重心，那么把重心作为根就是后面那坨就可以变成子树大小。那么哈密顿回路的构造是简单的，只要从根 $rt$ 开始，每次往返不同的 $rt$ 儿子的子树就可以得到最优值。

现在会少掉一条路径，我们大胆猜测这是一条边。观察样例 2 发现如果有两个重心那么删掉的必然是连接两个重心的边。手膜一下发现如果只有一个重心那么删掉的就是连接重心的边当中权值最小者。

[submission](https://atcoder.jp/contests/agc018/submissions/45300117) 

---

