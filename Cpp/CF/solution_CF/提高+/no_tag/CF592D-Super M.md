# Super M

## 题目描述

Ari the monster is not an ordinary monster. She is the hidden identity of Super M, the Byteforces’ superhero. Byteforces is a country that consists of $ n $ cities, connected by $ n-1 $ bidirectional roads. Every road connects exactly two distinct cities, and the whole road system is designed in a way that one is able to go from any city to any other city using only the given roads. There are $ m $ cities being attacked by humans. So Ari... we meant Super M have to immediately go to each of the cities being attacked to scare those bad humans. Super M can pass from one city to another only using the given roads. Moreover, passing through one road takes her exactly one kron - the time unit used in Byteforces.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592D/56ad621cd6030e31dd330e89c0a8c84a229488d5.png)However, Super M is not on Byteforces now - she is attending a training camp located in a nearby country Codeforces. Fortunately, there is a special device in Codeforces that allows her to instantly teleport from Codeforces to any city of Byteforces. The way back is too long, so for the purpose of this problem teleportation is used exactly once.

You are to help Super M, by calculating the city in which she should teleport at the beginning in order to end her job in the minimum time (measured in krons). Also, provide her with this time so she can plan her way back to Codeforces.

## 说明/提示

In the first sample, there are two possibilities to finish the Super M's job in $ 3 $ krons. They are:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592D/1e0931f0ee430eed74c20346afbbffa12e1171b1.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592D/3d215bf3b44e51bded5f8987ac4bd264a82b6423.png).

However, you should choose the first one as it starts in the city with the lower number.

## 样例 #1

### 输入

```
7 2
1 2
1 3
1 4
3 5
3 6
3 7
2 7
```

### 输出

```
2
3
```

## 样例 #2

### 输入

```
6 4
1 2
2 3
2 4
4 5
4 6
2 4 5 6
```

### 输出

```
2
4
```

# 题解

## 作者：A524 (赞：8)

小萌新人生的第一篇题解！
### 题目大意：有一个有 $n$ 个节点的树，其中有 $m$ 个点被标记。现在从任意点开始，去遍历这 $m$ 个点，问你遍历这 $m$ 个点的最少路程（边的权值为1）。
首先，题目中的任意点肯定是被标记的点（为了求最少路程）。然后我们先假设一种特殊的情况：所有的点都被标记，则，如下图：（我画的巨丑...）。
假设有这么一颗树，并且它的所有点都被标记。

![](https://cdn.luogu.com.cn/upload/image_hosting/jnzuluri.png)

假设从 $2$ 出发，我们应当这样遍历： $2$ -> $1$ -> $5$ -> $1$ -> $3$ -> $1$ -> $6$ -> $1$ -> $4$ 。通过图我们可以发现，除了 $2$ -> $1$ 和 $1$ -> $4$ 遍历了 $1$ 次，别的边都遍历了 $2$ 次。那我们肯定是让遍历 $1$ 次的越多，因为这样才能让答案更小。

![](https://cdn.luogu.com.cn/upload/image_hosting/x22ac4r8.png)

那这遍历 $1$ 次的边是什么呢？再看下一张图片：（绿色为遍历 $1$	遍的边，红色为遍历 $2$ 遍的边）

![](https://cdn.luogu.com.cn/upload/image_hosting/ksm9iytk.png)

由此我们可以发现，遍历 $1$	遍的边为最长时，便是一颗树的直径！所以，（总点数 - $1$ ） X $2$ - 树的直径=答案。但是！这是所有的点都被标记的情况，那如果有些点没有标记这么办？比如：（红色点为标记点，绿色点为不需要处理的点）

![](https://cdn.luogu.com.cn/upload/image_hosting/xy4qz8az.png)

观察一下，那些绿色点（不需要处理的点）的特征就是它的**子树没有红色点**（标记点）!注意：为了使根要保留，所以**根必定为红色**！

所以，只要先把绿色点（不需要处理的点）删除。再算出（总点数 - $1$ ）* $2$ - 树的直径，就是答案。
最后再放出我~~丑陋~~的代码。
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define maxm 300300
using namespace std;
vector<int> a[maxm];
struct node{int N,P;}e[maxm],maxn;
int XY[maxm],f[maxm],O,i,n,m,x,y,S;
bool check(node A,node B){return (A.P>B.P)||(A.P==B.P&&A.N<B.N);}
int df(int t,int w){
	int i;
	for (i=0;i<a[t].size();i++)
		if (a[t][i]!=w)
			XY[t]|=df(a[t][i],t);
	if (f[t]) XY[t]=1;		
	S+=XY[t];
	return XY[t];
}
void dfs(int t,int w){
	int i;node X;
	node maxn1,maxn2;	
	maxn1.P=maxn2.P=0;
	maxn1.N=maxn2.N=t;
	for (i=0;i<a[t].size();i++)
		if (a[t][i]!=w&&XY[a[t][i]]){
			dfs(a[t][i],t);
			X.P=e[a[t][i]].P+1;X.N=e[a[t][i]].N;
			if (check(X,maxn1)) 
				maxn2=maxn1,maxn1=X;
			else if (check(X,maxn2)) 
				maxn2=X;
		}
	X.P=maxn1.P+maxn2.P;X.N=min(maxn1.N,maxn2.N);
	if (check(X,maxn)) maxn=X;
	e[t].P=maxn1.P;e[t].N=maxn1.N;
} 
int main(){
	scanf("%d %d",&n,&m);
	for (i=1;i<n;i++){
		scanf("%d %d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for (i=1;i<=m;i++) 
		scanf("%d",&x),f[x]=1;
	for (i=1;i<=n;i++)
		if (f[i]) break;
	maxn.N=i;	df(i,0);	dfs(i,0);
	printf("%d\n%d\n",maxn.N,(S-1)*2-maxn.P);
	return 0;
} 
```

---

## 作者：mrclr (赞：8)

首先这题虽然不是很难，但是黄题是不是有点过分了……好歹算个蓝题啊。

手玩样例得知，这哥们儿瞬移到的城市$A$一定是这些被攻击的城市构成的树的一个叶子，然后他经过的最后一个城市$B$和$A$构成的链一定是这棵新构成的树的直径（突然想到虚树）。

别激动，这题根本不用虚树。

我们只用求一遍树的直径就行了，只不过这个直径的端点必须满足都是被攻击的城市，则第一问就是端点中的较小值。

考虑第二问。
直径上的城市只会走一遍，而直径外的城市必须走过去再回来。所以我们从直径一段开始遍历整个直径，每经过一个点，就dfs这个点直径之外的子树，并统计子树内走到被攻击的城市的距离和。那么答案就是这些距离+加树的直径长度。

距离和的求法用树形dp就行。我们考虑每一条边的贡献。如果一个点的的儿子的子树内有被攻击的城市，则这条边一定会被走过，答案加2即可。

然后记得特判被攻击的城市只有一个的情况（被hack了……）。
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define In inline
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 2e5 + 5;
inline ll read()
{
  ll ans = 0;
  char ch = getchar(), last = ' ';
  while(!isdigit(ch)) last = ch, ch = getchar();
  while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
  if(last == '-') ans = -ans;
  return ans;
}
inline void write(ll x)
{
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write(x / 10);
  putchar(x % 10 + '0');
}

int n, m;
bool vis[maxn];
struct Edge
{
  int nxt, to;
}e[maxn << 1];
int head[maxn], ecnt = -1;
In void addEdge(int x, int y)
{
  e[++ecnt] = (Edge){head[x], y};
  head[x] = ecnt;
}

int dep[maxn], fa[maxn], Max = 0, A, B;
In void dfs1(int now, int _f, int dis, int& id)
{
  if(vis[now] && (dis > Max || (dis == Max && now < id))) Max = dis, id = now;
  dep[now] = dep[_f] + 1; fa[now] = _f;
  for(int i = head[now], v; ~i; i = e[i].nxt)
    if((v = e[i].to) ^ _f) dfs1(v, now, dis + 1, id);
}

bool dia[maxn];
int a[maxn], b[maxn], acnt = 0, bcnt = 0;
In void solve(int x, int y)
{
  a[++acnt] = x; b[++bcnt] = y;
  dia[x] = dia[y] = 1;
  while(x ^ y)
    {
      if(dep[x] > dep[y]) a[++acnt] = x = fa[x], dia[x] = 1;
      else b[++bcnt] = y = fa[y], dia[y] = 1;
      
    }
  --acnt;
}

int ans = 0;
In bool dfs2(int now, int _f, int dis)
{
  int flg = 0;
  for(int i = head[now], v; ~i; i = e[i].nxt)
    {
      if(dia[v = e[i].to] || v == _f) continue;
      int tp = dfs2(v, now, dis + 1);
      if(tp) ans += 2;
      flg |= tp;
    }
  return flg || vis[now];
}

int main()
{
  Mem(head, -1);
  n = read(), m = read();
  for(int i = 1; i < n; ++i)
    {
      int x = read(), y = read();
      addEdge(x, y), addEdge(y, x);
    }
  for(int i = 1; i <= m; ++i) A = read(), vis[A] = 1;
  dfs1(A, 0, 0, A), Max = 0, dfs1(A, 0, 0, B);
  if(!A || !B) {printf("%d\n0\n", A | B); return 0;}
  solve(A, B);
  for(int i = 1; i <= acnt; ++i) dfs2(a[i], 0, 0);  //这两行是遍历直径
  for(int i = 1; i <= bcnt; ++i) dfs2(b[i], 0, 0);
  write(min(A, B)), enter, write(ans + Max), enter;
  return 0;
}
```

---

## 作者：XL4453 (赞：5)

### $\text{Difficulty : 2200}$
---
### 解题思路：

为了方便描述问题，先任意选定一个被攻击的节点作为根节点。容易发现，在这样的描述下，根节点一定会被走到。

然后具体考虑哪一些节点需要被走到，根据题意，被攻击的节点一定要走。而对于未被攻击的节点，只要子树中有被攻击节点就一定要走。

后者的证明思路大致如下：假设在一个未被选中的节点的子树中有一个需要被经过的点，如果一开始的转送点在这个子树外就一定需要走到这个子树中，反之如果传送点在子树内部就至少需要走到根节点，同样需要经过这个未被选中的点。

于是就可以把子树中没有被攻击的点的未被攻击的点删掉了。

---

接着问题就转化为了从任意一个点开始遍历整棵树，不要求回到这个点。

逆向考虑这个问题，令这个人从某一个节点出发到达所有节点并最终回到这个节点，容易发现，形成这样一个回路之后任一点都可以作为这个起始点。然后考虑这个不要求回到原点的条件，实际上也就是从某一个点到另一个点之间的一条链只需要被走一次。

所以最终的答案就是删去一些点之后的边的个数的两倍减去树的直径长。

注意特判只有一个城市被攻击的情况。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=300000;
int n,m,head[MAXN],nxt[MAXN],num[MAXN],f[MAXN],v[MAXN],x,y,tot,maxi,maxi_2,cnt;
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
bool dfs(int now,int fa,int dis){
	f[now]=dis;
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]==fa)continue;
		v[now]|=dfs(num[i],now,dis+1);
	}
	return v[now];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	for(int i=1;i<=m;i++)
	scanf("%d",&x),v[x]=1;
	if(m==1){
		printf("%d\n0\n",x);
		return 0;
	}
	dfs(x,0,0);
	for(int i=1;i<=n;i++){
		if(v[i]==0)continue;
		if(f[i]>f[maxi])maxi=i;
	}
	dfs(maxi,0,0);
	for(int i=1;i<=n;i++){
		if(v[i]==0)continue;
		cnt++;
		if(f[i]>f[maxi_2])maxi_2=i;
	}
	printf("%d\n",min(maxi_2,maxi));
	printf("%d\n",(cnt-1)*2-f[maxi_2]);
	return 0;
}
```


---

## 作者：wuheshidaozod (赞：5)

设 $dp[u][0/1]$ 表示以 $u$ 为节点的子树，回到 / 不回到 $u$ 节点的最短用时，那么以每个节点为根进行 dp，取最小值就是答案。转移方程式：
$$
dp[u][0]=\sum (dp[v][0]+2)
$$
$$
dp[u][1]=\sum_{v\neq son_u} (dp[v][0]+2)+dp[son_u][1]+1
$$
其中 $son_u$ 表示 $dp[v][0]-dp[v][1]$ 最大的那个子节点，从 $u$ 节点出发走遍除 $son_u$ 以外的儿子再返回 $u$，最后走到 $son_u$ 一去不复返即可。

然而这样做会 T，所以考虑换根 DP，先跑出以 1 为根的答案，再跑一次 DFS 每次换根转移即可，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define grap(u) for(int aqa=e.head[u];aqa;aqa=e.nex[aqa])
#define to e.des[aqa]
#define val(u) (dp[u][0]-dp[u][1])
template <typename T>
inline void read(T &x)
{
    x=0;int f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    x*=f;
}
template<typename T, typename... Args> inline void read(T &first, Args& ... args)
{
    read(first);
    read(args...);
}
int flag[124515];
int dp[124515][2],son[124515],n,m,nexson[124515],ans1,ans2;
struct mp{
	int des[124515*2],nex[124515*2],head[124515];
	int ct=0;
	void add(int u,int v){
		des[++ct]=v;nex[ct]=head[u];head[u]=ct;
	}
}e;
void dfs1(int u=1,int fa=0){
	grap(u){
		if(to==fa)continue;
		dfs1(to,u);
		if(flag[to])flag[u]+=flag[to];
		else continue;
		dp[u][0]+=dp[to][0]+2;
		if(val(to)>=val(son[u]))nexson[u]=son[u],son[u]=to;
		else if(val(to)>=val(nexson[u]))nexson[u]=to;
	}
	if(son[u])dp[u][1]=dp[u][0]-val(son[u])-1;
}
void dfs2(int u=1,int fa=0){
	grap(u){
		if(to==fa)continue;
		if(!flag[to])continue;
		int dpu0=dp[u][0],dpu1=dp[u][1],flagu=flag[u];
		int dpto0=dp[to][0],dpto1=dp[to][1];
		flag[u]-=flag[to];
		dp[u][0]-=dp[to][0]+2;
		if(son[u]==to){
			if(nexson[u])dp[u][1]=dp[u][0]-dp[nexson[u]][0]+dp[nexson[u]][1]-1;
			else dp[u][1]=0;
		}
		else{
			dp[u][1]-=dp[to][0]+2;
		}
		if(flag[u]){
			
			if(dp[to][0]+dp[u][1]+1<=dp[to][1]+dp[u][0]+2){
				dp[to][1]=dp[to][0]+dp[u][1]+1;
				nexson[to]=son[to];
				son[to]=u;
			}
			else {
				dp[to][1]=dp[to][1]+dp[u][0]+2;
				if(val(u)>=val(nexson[to]))nexson[to]=u;
			}
			dp[to][0]+=dp[u][0]+2;
		}
		flag[to]+=flag[u];
		if(ans1>dp[to][1]){
			ans1=dp[to][1];
			ans2=to;
		}
		else if(ans1==dp[to][1]){
			ans2=min(ans2,to);
		}
		dfs2(to,u);
		dp[u][0]=dpu0;dp[to][0]=dpto0;
		dp[u][1]=dpu1;dp[to][1]=dpto1;
		flag[u]=flagu;
	}
}
int main(){
	read(n,m);
	for(int i=1,u,v;i<n;++i){
		read(u,v);
		e.add(u,v);
		e.add(v,u);
	}
	for(int i=1,x;i<=m;++i){
		read(x);
		flag[x]=1;
	}
	dfs1();
	ans1=min(dp[1][0],dp[1][1]);
	ans2=1;
	dfs2();	
	printf("%d\n%d",ans2,ans1);
   return 0;
}
```


---

## 作者：Marser (赞：4)

### 题意
给定一棵 $n$ 个点的树，其中有 $m$ 个两两不同的关键点，求从任意一个关键点出发，遍历所有关键点的最短路径。  
$m \le n \le 123456$ 。
### 题解
容易发现这是个虚树问题，但是直接上虚树太麻了，我们可以考虑一些优美的做法。  
首先要了解一个结论：  
> 遍历树上的一个点集，并返回起点，形成一个回路，最佳方案是按照 dfs 序从小到大依次遍历每个点。

但是，这样搞出来的是一条回路，显然不优。我们考虑魔改一下，去掉虚树上的一条链，让它成为一个合法的方案。为保证字典序最小，我们让去掉的这条链中编号较小的一个端点为起点，另一个为终点，就是一个合法方案了。同时，为了最小化答案，我们应该去掉虚树上最长的一条链。

还有一个问题，第一步中，我们按照 dfs 序大小遍历每个关键点。但是第二步中，我们并没有按这样去掉多余的链。这样为什么是对的呢？  
首先，如果所选的两个端点之间没有其他关键点，显然可以通过调整 dfs 子树的顺序使得它们的 dfs 序相邻。  
然后，我们考虑两点间有关键点的情况，这些关键点一定是至少一个端点的祖先。因为终点不需要折返，我们同样不需要两次经过这些点到端点的路径。  
因此，直接找到两端点均为关键点的树上最长链，编号较小的那个端点就是起点。

### 代码
```cpp
#include<bits/stdc++.h>
#define reg register
typedef long long ll;
using namespace std;
const int MN=3e5+5;
const int mod=998244353;
int to[MN<<1],nxt[MN<<1],h[MN],cnt;
inline void ins(int s,int t){
	to[++cnt]=t;nxt[cnt]=h[s];h[s]=cnt;
	to[++cnt]=s;nxt[cnt]=h[t];h[t]=cnt;
}
int n,m,node[MN],f[MN][19],dep[MN],dfn[MN],idx;
bool tag[MN];
void dfs1(int st){
	dfn[st]=++idx;dep[st]=dep[f[st][0]]+1;
	for(reg int i=1;i<19;i++)
		f[st][i]=f[f[st][i-1]][i-1];
	for(reg int i=h[st];i;i=nxt[i])
		if(to[i]!=f[st][0])
			f[to[i]][0]=st,dfs1(to[i]);
}
inline int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(reg int i=18;~i;i--)
		if(dep[f[x][i]]>=dep[y])x=f[x][i];
	if(x==y)return x;
	for(reg int i=18;~i;i--)
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
inline int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[LCA(x,y)];
}
int dp[MN],Res,Pos,Ans;
void dfs2(int st){
	if(tag[st])dp[st]=st;
	for(reg int i=h[st],res;i;i=nxt[i])
		if(to[i]!=f[st][0]){
			dfs2(to[i]);if(!dp[to[i]])continue;
			if(dp[st]){
				res=dep[dp[to[i]]]+dep[dp[st]]-2*dep[st];
				if(res>Res||(res==Res&&min(dp[st],dp[to[i]])<Pos))
					Pos=min(dp[st],dp[to[i]]),Res=res;
			}
			if(dep[dp[to[i]]]>dep[dp[st]]||
			  (dep[dp[to[i]]]==dep[dp[st]]&&dp[to[i]]<dp[st]))
			  	dp[st]=dp[to[i]];
		}
}
int main(){
	scanf("%d%d",&n,&m);
	for(reg int i=1,s,t;i<n;i++)
		scanf("%d%d",&s,&t),ins(s,t);
	for(reg int i=1;i<=m;i++)
		scanf("%d",node+i),tag[node[i]]=true;
	if(m==1)return 0*printf("%d\n0",node[1]);
	dfs1(1);
	sort(node+1,node+1+m,[](int a,int b){
		return dfn[a]<dfn[b];
	});
	for(reg int i=1;i<=m;i++)
		Ans+=dis(node[i],node[i%m+1]);
	Pos=n+1;dfs2(1);Ans-=Res;
	printf("%d\n%d\n",Pos,Ans);	
	return 0;
}
```

---

## 作者：zhujiajun2013 (赞：3)

### 前置知识：树的直径。
翻了半天只有一篇**树的直径**，就打算来发一篇。
### 思路点拨：
先标记所有关键点，把所有**含有关键点**的子树的根节点都置为关键点，最后求树的直径即可。

### AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,head[200005],cnt,dis[200005],ans,a[200005],f[200005];
struct node{
	int to,nxt;
}e[400005];
void add(int u,int v){
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt++;
}
void init(){
	memset(head,-1,sizeof head);
}
void dfs(int u,int fa,int w){//树的直径
	dis[u]=w;
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].to;
		if(f[v]==0)continue;
		if(v==fa)continue;
		dfs(v,u,w+1);
	}
}
int flag(int u,int fa){//标记
	f[u]=a[u];
	for(int i=head[u];~i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa)continue;
		f[u]|=flag(v,u);
    }
    return f[u];
}
int main(){
	cin>>n>>m;
	init();
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	int x;cin>>x;a[x]=1;
	if(m==1){cout<<x<<endl<<0<<endl;return 0;}
	for(int i=1;i<m;i++){
		int y;
		cin>>y;
		a[y]=1;
    }
	flag(x,0);
	dfs(x,0,0);
	int p1=0;
	for(int i=1;i<=n;i++)if(f[i]&&(dis[i]>dis[p1]||p1==0))p1=i;
	memset(dis,0,sizeof dis);
	dfs(p1,0,0);
	int cnt=0,p2=0;
	for(int i=1;i<=n;i++){
		cnt+=f[i];
		if(f[i]&&(dis[i]>dis[p2]||p2==0))p2=i;
	}
	cout<<min(p1,p2)<<endl<<2*(cnt-1)-dis[p2];//min(p1,p2) 必须得加，我一开始 WA 第六个点
	return 0;
}
```
最后一句 $2\times (cnt-1)-dis_{p2}$ 我再解释一下：

对于**这些标记点**都需要走**两遍**，然而有一些可以只走一遍的也就是这条**树的直径**。

---

## 作者：ln001 (赞：3)

## 题意
给定一个树，有若干标记点，请求一个起点，使得从该点开始，沿树边遍历每一个标记点的总用时最小，输出起点和总用时，边权均相同。
## 做法
首先将树上无用的点删去，称点 $x$ 是无用的，当且仅当删去该点后所有的标记点仍在同一个连通块内。

对于剩下的这一颗树，有任意一条边至多经过两次，且仅有**从倒数第二个经过的标记点到最后一个经过的标记点的路径**上的边经过一次。

要使这种路径最长，直接求直径，可以证明，在剩下的这棵树中，直径的两个端点均为标记点。

第二问即为剩下的树的边的个数的两倍与直径长度的差。

第一问可以转化为，在树上，找到**编号最小**的满足其是**一条直径的端点**的点 $x$。该条件的等价条件为距 $x$ 距离最远的点与 $x$ 的距离为直径长度。

又有性质“距离任意点最远的点一定是直径的一个端点”所以预处理以 $1$ 为根的深度和 $lca$ 即可。

第一步的删点直接以**任意标记点为根**，求每个子树内标记点的个数，若值为 $0$ 则删去**该子树的根**。

[Code](https://vjudge.net/solution/55514896/BlRkYy6f8tK0NgB4Ez4s)

---

## 作者：boluo2014 (赞：1)

这道题还是很有趣的。
### 修改
Upd at 2025/2/12：修改了部分表达的不准确、格式的错误。

Upd at 2025/2/14：修改了格式的问题
### 题意

给定一棵树，以及红点，求经过每个红点所需的最短距离。
### 前置知识

如果你没有学过树的直径的话，那你可以去学习一下。我这里就说做法，不做证明了。

#### 树的直径
##### 定义
树上一个点到另一个点的路径的最大值。
##### 做法
首先，这里的边权都是 $1$。

第一步：从任意节点出发，用 dfs 找到一个距离它最远的点 A。

第二步：再从 A 开始 dfs，找到距离 A 最远的点 B。

第三步：A 到 B 的长度就一定是树的直径。（可能有多种）

题目链接：[树的直径](https://www.luogu.com.cn/problem/B4016)

代码：
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
vector<int>g[maxn];
int mx=0,en,mx1=0;
void dfs(int x,int fx,int r){
	int i;
	if(r>mx){
		en=x;
		mx=r;
	}
	for(i=0;i<g[x].size();i++){
		if(g[x][i]==fx)continue;//记得判断爸爸生了你，你又生了你爸爸
		dfs(g[x][i],x,r+1);
	}
}
void dfs1(int x,int fx,int r){
	int i;
	if(r>mx1){
		mx1=r;
	}
	for(i=0;i<g[x].size();i++){
		if(g[x][i]==fx)continue;
		dfs1(g[x][i],x,r+1);
	}
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n,u,v,i;
	cin>>n;
	for(i=1;i<=n-1;i++){
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,1,0);//不一定是1
	dfs1(en,en,0);//再dfs
	cout<<mx1<<endl;
	return 0;
}
```

为了说明步骤 1 中“任选一点”的操作，我还写了一个随机数来找第一个点，[结果](https://www.luogu.com.cn/record/201924198)还真的通过了！虽然树的直径简单，但是它有很多延伸，就如这题。
### 思考过程

我们发现，这道题目有一些关键信息：

一，有的节点必须经过。

二，要求不是最长，而是最短。

所以，我们想一下：如果所有的点都被标记必须走过，那岂不是很简单了？所以，我们就要想办法让要走过的点都变成必须走过的点，不走过的在遍历的过程中直接不管他了。

然后你一定就纳闷了？这是最小路径，和最大直径又什么关系？想到这里，我给大家画了一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/e4tqwe4c.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在这张图上，我们设必须走过的点为红色，不一定走过的点设为蓝色。然后我们可以开始观察了：

#### 有什么性质

我们可以先来看看最短的路径，我依旧画了一张图片：

![](https://cdn.luogu.com.cn/upload/image_hosting/w3gqk69e.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

黄色第箭头代表所走的路径。从 2 到 1，到 3，到 7 到3，到 5，到 8。然而，你会惊喜地发现：有两个点是毫无作用的，那就是 4 和 6。毫无作用的原因是它们根本就不是红色，而且子树中也没有红色节点。

这个就是第一个性质，子树及自身中没有红色节点的毫无作用。既然这样，我们可以在主要程序开始之前，就预处理一下整一棵树，可以直接用 dfs 标记好新的节点颜色。

可是，现在仍然没有对“最短路径”的搜索方法。也许是因为这样的最短路径难以观察，我再画一个相对好观察到的：
![](https://cdn.luogu.com.cn/upload/image_hosting/cs94sq94.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

~~这张图颜色绚丽~~

在图中，黄色、绿色的路径是另一种经过所有红点的路径，但不是最短路径。而绿色的路径，也就是走了两遍的路径。我们就要观察绿色和黄色。

首先，不一定所有的路径都是绿色的。那不是绿色的就是只走了一遍的。你可以理解黄色路径为“主要路径”（长度为 $x$），理解绿色路径为“分支路径”。而假设**全部都不走回头路**的总路径长度为 $y$。（这里不要理解错了，这副图中总路径长度也就是新的红点数 $-1$）

那么，都走回头路就是 $2y$。但它并非真正长度，还得减去 $x$，因为它直走一遍。便是 $(2y-x)$。

我们可以对比一下两张不一样的路径：
![](https://cdn.luogu.com.cn/upload/image_hosting/w3gqk69e.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$x=4,y=5,2y-x=6$（主要路径长度为 $4$，全部不走两次长度为 $5$，最终长度为 $6$）

![](https://cdn.luogu.com.cn/upload/image_hosting/cs94sq94.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$x=3,y=5,2y-x=7$（主要路径长度为 $3$，全部不走两次长度为 $5$，最终长度为 $7$）。

如果真的想让路径长度变短，真的需要让 $x$ 变大。

不断地变大。现在你可以回忆一下前面讲的“自己和子树都不是红色的节点不管，自己和子树有红色的节点都标记为红色”，那就可以开始遍历。还是画图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jiqyqkde.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

注意：**遍历时不再考虑蓝点**。

那么，总共有 $6$ 个红点，$5$ 条边。橙色路径就是**树的直径**！长度为 $4$。$5 \times 2 -4=6$，就是答案！ 

但是，你一看样例输出，还有一个数，那就是初始的点。那也没有关系，很方便，我们直接输出树的直径中第一遍 dfs 搜索到的最远的地方即可，不管是头是尾，因为路径是对称的。

### 总结、写代码

总结了刚才所有思考结果：

一，定义
```
bool tmp[maxn],col[maxn];//原来、新的颜色
int n,m;
vector<int>G[maxn];
int mx,en,mx1,en2;//后 dfs 用
```
二，如果子树或自身含有红色节点，自身标记为红色。
```
void updcol(int x,int fx){
    col[x]=tmp[x];
    int i;
    for(i=0;i<G[x].size();i++){
        int y=G[x][i];
        if(y==fx){continue;}//爸爸生了你，你又生了你爸爸
        updcol(y,x);
        col[x]|=col[y];//有红色就是红色
    }
}
```
三，两遍 dfs 跑出树的直径

注意：要取编号最小的值。所以长度相等的时候需要看编号！（这里已经给过代码了，就不给了）

四，计算出答案，答案是 红点数减 $1$ 的差乘 $2$ 减去树的直径长度。

你理解了吗？这是一道蓝题，好歹有点难度的。

---

## 作者：include13_fAKe (赞：0)

怎么有人这题调了 $2$ 个下午（星期一下午和星期五下午）才调出来这种水题呢？（实际上写了两个假做法）

还原做题时的思路。

---

考虑建出包含关键点的虚树（关键点到 LCA 的所有点都保留在虚树上），然后计算虚树上从所有点出发能走到的最长简单路径的的长度，可以用换根 dp 实现。

具体来说，把以 $u$ 节点为开头的路径分为两类：在 $u$ 子树内的、从 $u$ 子树往外走的。第一类情况是简单的。重点讨论第二种情况：

- 在 $fa_u$ 子树内且不经过 $u$ 的路径。可以通过记录一个点的子树的最大深度和次大深度实现 $O(n)$ 转移（因为虚树最多可能有 $n$ 个点）。
- 从 $fa_{fa_u}$ 转移而来。在第一种转移的基础上增加 $dp_v=\max(dp_v,dp_u+1)$。（代码使用变量 $\texttt {dp2}$ 实现）

最后考虑答案，显然是两种 dp 方案得到的最大值。

注意 $m=1$ 的情况。时间复杂度 $O(n+m\log n)$。

---

其实在第一次写完上面的做法之后（当时写了接近两百行的 4.76KB 错了彻底破防了）又想了一种歪门邪道的求树的直径的方法：求所有点到（无根树定义下的）任意一个叶子的最短路，但这是错误的，反例如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5h4p829q.png)

此时节点 $3$ 的搜索值为 $1$，节点 $4$ 的搜索值为 $2$，但它们是直径 $1-2-3-4-5-6$ 的两个中心。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=2e5+15; 
int n,m;
int a[N];
vector<int> g[N],h[N];	//原树和虚树  
int fa[N][22];	//层次父亲 用于找 LCA 
int dep[N];
void dfs(int u){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(fa[u][0]==v)	continue;
		fa[v][0]=u,dep[v]=dep[u]+1;
		for(int j=1;j<=20;j++){
			fa[v][j]=fa[fa[v][j-1]][j-1];
		}
		dfs(v);
	}
} 
int LCA(int u,int v){
	if(dep[u]<dep[v])	swap(u,v);
	for(int i=20;i>=0;i--){
		if(dep[fa[u][i]]>=dep[v])	u=fa[u][i];
	}
	if(u==v)	return u;
	for(int i=20;i>=0;i--){
		if(fa[u][i]!=fa[v][i])	u=fa[u][i],v=fa[v][i];
	}
	return fa[u][0];
}
int atree[N];	//接下来是对 h 树的处理方案  
int ans=0;
int maxson[N][3];	//最大深度的儿子 
int deph[N];	//h 树上的儿子  
int dp[N];	//最终答案 换根求出答案  
int dp2[N];	//dp 不需要换根 真正需要换根的是 dp2  
void dfs2(int u){
	deph[u]=1;
	for(int i=0;i<h[u].size();i++){
		int v=h[u][i];
		if(fa[u][0]==v)	continue;
		dfs2(v);
		deph[u]=max(deph[u],deph[v]+1);
		if(maxson[u][1]<deph[v]){
			maxson[u][2]=maxson[u][1];
			maxson[u][1]=deph[v];
		}
		else if(maxson[u][2]<deph[v]){
			maxson[u][2]=deph[v];
		}
	}
	dp[u]=maxson[u][1]+1;
//	cout<<'#'<<u<<' '<<deph[u]<<' '<<maxson[u][1]<<' '<<maxson[u][2]<<endl; 
}
void dfs3(int u){
//	cout<<'#'<<u<<' '<<dp[u]<<' '<<dp2[u]<<endl;
	for(int i=0;i<h[u].size();i++){
		int v=h[u][i];
		if(fa[u][0]==v)	continue;
		if(deph[v]<maxson[u][1]){
			dp2[v]=maxson[u][1]+2;
		}
		else{
			dp2[v]=maxson[u][2]+2;
		}
		dp2[v]=max(dp2[v],dp2[u]+1);
		dfs3(v);
	}
//	cout<<'#'<<u<<' '<<dp[u]<<' '<<dp2[u]<<endl;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		g[u].push_back(v),g[v].push_back(u);
	}
	dep[1]=1;
	dfs(1);
	int LCA_=0; 
	for(int i=1;i<=m;i++){
		cin>>a[i];
		if(LCA_==0)	LCA_=a[i];
		else LCA_=LCA(LCA_,a[i]);
	}
	if(m==1){
		cout<<a[1]<<endl<<0<<endl;
		return 0;
	}
//	cout<<LCA_<<endl;
	for(int i=1;i<=m;i++){
		int now=a[i];
		while(now!=LCA_&&atree[now]==0){
			atree[now]=1;
//			cout<<now<<endl;
			now=fa[now][0];
		}
	}
	for(int i=1;i<=n;i++){
		if(atree[i]){
			h[i].push_back(fa[i][0]),h[fa[i][0]].push_back(i);
			ans++;
		}
	}
	dfs2(LCA_);
//	cout<<endl;
	dfs3(LCA_);
//	cout<<endl;
//	cout<<deph[1]<<endl;
	for(int i=1;i<=n;i++){
//		cout<<'#'<<i<<' '<<dp[i]<<' '<<dp2[i]<<endl;
	}
	int ans1,ans2=0;
	for(int i=1;i<=n;i++){
		int now=max(dp[i]-1,dp2[i]-1);
		if(now>ans2){
			ans1=i,ans2=now;
		}
	}
	cout<<ans1<<endl<<ans*2-ans2<<endl;
	return 0;
} //CF592D
```

代码和机房同学相比还是太长了，2.55KB 的正解代码不值得你拥有。会不会是他们有更简单的做法啊？

---

## 作者：EllinY (赞：0)

图画得很丑，致歉。由于 Remote Judge 宕机了，提供 [Codeforces 提交记录（Accepted）](https://codeforces.com/problemset/submission/592/278873572)。
# 题意
在一棵树上，有一些关键点，你需要选择一个起点，使走遍所有关键点所需的路程最短，当路程长度相等的时候，选择编号最小的起点。
# 思路
如果要从一个点出发，遍历整棵树并回到起点，那么树上的每条边都会经过两次（走到儿子节点后，必须走回父亲节点才能去别的儿子节点）。$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/6yq7qrtu.png)$\\$ 但是这里不需要回到起点，也就是说，如果从根出发，那么有一条从根节点走向某个叶子节点的路是不需要走第二遍的。$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/zlwwdsm8.png)$\\$ 由于树上的边数是确定的，要使最后走的路程最短，就要使不走的这条路径最长，将边数乘 $2$ 减去这条路径长度之后就是遍历整棵树的最短路径。我们要找的就是整棵树的直径，并把直径的一端作为起点（想象它是根节点），就可以找到最短的路。$\\$ 调整一下刚才那棵树，使起点和终点都是一条直径的两端，得到最短路径 $2\times(9-1)-5=11$。$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/fbuf3jae.png)$\\$ 在这道题里面不是所有点都要经过，所以我们得先把树里不用经过的点删掉。把关键点中的一个点作为树的根，确保根一定会保留，通过 dfs 判断是否保留一个点。如果一个节点的某个儿子节点必须保留，那么它也要保留（即每个关键点通往根的路径要保留）。下图中的点，红色为关键点，灰色为被删除的点：$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/d7ywp5sj.png)$\\$ 重新建图。由于在路径长度相同的情况下要找到两头编号的最小值更小的直径，所以记录每个点的 $m1_i,m2_i$ 表示往它的子树走能得到的最大长度和次大长度，当然，这两条路径不能相交（除了在节点 $i$ 相交）。记录 $m1p_i,m2p_i$ 表示最长路径和次长路径分别走到了哪个点，在路径长相等的情况下 $m1p$ 和 $m2p$ 尽量小。比如说上图中 $2$ 号节点，$m1_2=3,m2_2=2,m1p_2=7,m2p_2=13$。$\\$ 最后的答案就是找到一个点 $i$，使 $m1_i+m2_i$ 最大，在和相等的情况下，使 $\min(m1p_i,m2p_i)$ 最小。
# 代码
主要是树形 dp 的转移要写对，这里提供一组测试路径长度相等的情况下程序的结果是否正确的样例。
``` cpp
/*
input:
13 5
1 5
12 6
3 5
4 3
1 7
7 11
2 6
5 6
10 7
8 9
5 13
5 8
4 7 2 8 5
output:
2
10
*/
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,m1[123460],m2[123460];
int m1p[123460],m2p[123460],cnt;
bool flag[123460],stay[123460];//是否为关键节点；是否保留
vector<int> go[123460],e[123460];//原图；新图
void dfs(int ps,int fa){
	if(flag[ps]) stay[ps]=1;
	for(auto g:go[ps]){
		if(g==fa) continue;
		dfs(g,ps);
		stay[ps]|=stay[g];
	}
}
void dist(int ps,int fa){
	cnt++;
	m1p[ps]=m2p[ps]=0x3f3f3f3f;
	if(e[ps].size()<=1) m1p[ps]=ps;
	//注意：如果只有一个点，那么没有边，size=0
	for(auto g:e[ps]){
		if(g==fa) continue;
		dist(g,ps);
		//儿子节点只能更新 m1,m2 的其中一个，用 else if
		if(m1[g]+1>m1[ps]){
			m2[ps]=m1[ps],m2p[ps]=m1p[ps];
			m1[ps]=m1[g]+1;
			m1p[ps]=m1p[g];
		}
		else if(m1[g]+1==m1[ps]&&m1p[g]<m1p[ps]){
			m2[ps]=m1[ps],m2p[ps]=m1p[ps];
			m1p[ps]=m1p[g];
		}
		else if(m1[g]+1>m2[ps]){
			m2[ps]=m1[g]+1;
			m2p[ps]=m1p[g];
		}
		else if(m1[g]+1==m2[ps]&&m1p[g]<m2p[ps]) m2p[ps]=m1p[g];
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		go[u].push_back(v),go[v].push_back(u);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&u);
		flag[u]=1;
	}
	dfs(u,0);
	for(int i=1;i<=n;i++)
		if(stay[i]) for(auto j:go[i])
			if(stay[j]) e[i].push_back(j);
	dist(u,0);int ans=0,minp=0x3f3f3f3f;
	for(int i=1;i<=n;i++){
		if(!stay[i]) continue;
		if(m1[i]+m2[i]>ans){
			minp=min(m1p[i],m2p[i]);
			ans=m1[i]+m2[i];
		}
		else if(m1[i]+m2[i]==ans) minp=min(minp,min(m1p[i],m2p[i]));
	}
	printf("%d\n%d\n",minp,2*(cnt-1)-ans);
	return 0;
} 
```
感谢阅读 Thanks♪(･ω･)ﾉ。

---

## 作者：cike_bilibili (赞：0)

根据 [P3320](https://www.luogu.com.cn/problem/P3320) 的启发，我们可以将问题转化为从一个关键点遍历所有关键点但不用回到原点的最短距离，直接将关键点按 dfs 序排序后算相邻两个点的距离之和，包括首尾两点。再减去最远的两个点的距离即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n,m;
struct edge{
	int to;
	int next;
}ed[300005];
int tot;
int h[200005];
void add(int x,int y){
	ed[++tot]={y,h[x]};
	h[x]=tot;
}
int pts[200005];
int f[200005][25];
int dfn[200005],dep[200005];
int tim;
bool cmp(int a,int b){
	return dfn[a]<dfn[b];
}
void dfs(int x,int fa){
	f[x][0]=fa;
	dfn[x]=++tim;
	dep[x]=dep[fa]+1;
	for(int i=h[x];i;i=ed[i].next){
		int v=ed[i].to;
		if(v==fa)continue;
		dfs(v,x);
	}
}
void init(){
	for(int j=1;j<=20;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--){
		if(dep[f[x][i]]>=dep[y])x=f[x][i]; 
	}
	if(x==y)return x;
	for(int i=20;i>=0;i--){
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}
bool is[200005];
int ans;
int g[200005],id[200005],cnt,st;
void dp(int x,int fa){
	if(is[x])g[x]=0;
	int maxx=0,remaxx=0,bj=is[x];
	for(int i=h[x];i;i=ed[i].next){
		int v=ed[i].to;
		if(v==fa)continue;
		dp(v,x);
		if(g[v]+1>=maxx)remaxx=maxx,maxx=g[v]+1,bj=1;
		else if(g[v]+1>remaxx)remaxx=g[v]+1;
	}
//	cout<<x<<" "<<bj<<' '<<maxx<<" "<<remaxx<<" "<<"\n"; 
	if(!bj)return;
	if(!(!remaxx&&!is[x])&&maxx+remaxx>cnt){
		cnt=maxx+remaxx,st=1e9;
		for(int i=h[x];i;i=ed[i].next){
			int v=ed[i].to;
			if(v==fa)continue;
			if(g[v]+1==maxx||g[v]+1==remaxx)st=min(id[v],st);
		}
		if(g[x]==maxx||g[x]==remaxx)st=min(x,st);
	}else if(!(!remaxx&&!is[x])&&maxx+remaxx==cnt){
		for(int i=h[x];i;i=ed[i].next){
			int v=ed[i].to;
			if(v==fa)continue;
			if(g[v]+1==maxx||g[v]+1==remaxx)st=min(id[v],st);
		}
		if(g[x]==maxx||g[x]==remaxx)st=min(x,st);
	}
	
	if(is[x]&&!maxx)id[x]=x;
	else id[x]=1e9;
	g[x]=maxx;
	for(int i=h[x];i;i=ed[i].next){
		int v=ed[i].to;
		if(v==fa)continue;
		if(g[v]+1==maxx)id[x]=min(id[x],id[v]);
	}
	
}
int main(){
	for(int i=1;i<=200000;i++)g[i]=-1e9;
	n=read(),m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		add(x,y),add(y,x);
	}	
	dfs(1,0);
	init();
	for(int i=1;i<=m;i++)pts[i]=read(),is[pts[i]]=1;
	sort(pts+1,pts+1+m,cmp);
	for(int i=2;i<=m;i++){
		ans+=dep[pts[i-1]]+dep[pts[i]]-2*dep[lca(pts[i-1],pts[i])];
	}
	ans+=dep[pts[1]]+dep[pts[m]]-2*dep[lca(pts[1],pts[m])];
	dp(1,0);
//	for(int i=1;i<=n;i++)cout<<g[i]<<' ';
//	cout<<'\n';
	if(m==1){
		cout<<pts[1]<<'\n'<<0<<'\n';
		return 0;
	}
	cout<<st<<"\n"<<ans-cnt<<"\n";
} 
/*
2 1
2 1
1
*/
```

---

