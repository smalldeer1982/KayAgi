# Roads in the Kingdom

## 题目描述

王国有 $n$ 座城市与 $n$ 条有长度的街道，保证所有城市直接或间接联通，我们定义王国的直径为所有点对最短距离中的最大值，现因财政危机需拆除一条道路并同时要求所有城市仍然联通，求所有拆除方案中王国直径的最小值。

## 说明/提示

数据范围：$3 \le n \le 2 \times 10^5$，$1 \le u,v \le n$，$1 \le w \le 10^9$。

## 样例 #1

### 输入

```
3
1 2 4
2 3 5
1 3 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
2 3 7
3 1 9
4 1 8
3 5 4
4 5 5
```

### 输出

```
18
```

# 题解

## 作者：Leap_Frog (赞：23)

来贡献一发题解。  
### Problem.
给一个王国的地图，是n条边n个点的。  
求拆了一条边后的王国地图最大直径。  
当然，拆了一条边之后要保证地图联通。  

### Solution.
首先，我们发现，这个王国地图是n条边n个点的。  
那么这个王国呈一个环套树。  

我们可以把这个环套树想象成一个森林，然后根节点被连成了一个环。  
然后因为拆完之后形成的是一棵树，那么我们必须在环上拆边。  

首先，我们发现那个森林的每棵树的形状对答案是没有影响的。  
那么我们可以考虑对森林中的每棵树分别先算出答案，得到了每棵树的直径。  
那么每个树可以被缩成一个点，点权是这一棵子树的直径。  

于是现在题目可以被化简为，给定一个既有点权（$w_i$），又有边权（$dis_{i,j}$）的一个环。  
在这个环上拆了一条边，求$\max\{w_i+w_j+dis_{i,j}\}$这个东西的最小值。  

首先我们考虑分类讨论。  
假设我们现在**钦定**一个1号节点表示环的开始。  
然后我们现在断掉$\texttt{i}\Leftrightarrow\texttt{i+1}$这条边，那么我们可以分类讨论：

- Case 1 : 最长的两个点都在$[1,i]$上。
- Case 2 : 最长的两个点都在$[i,n]$上。
- Case 3 : 最长的两个点一个在$[1,i]$上，另一个在$[i,n]$上。

对于Case 1和Case 2，它只是一个序列上问题。  
不会用到环的性质。  
而且Case 1和Case 2很类似，所以笔者在这里不赘述。  
我们首先先考虑上面那个柿子。$\max\{w_i+w_j+dis_{j,i}\}$。  
然后我们考虑对$i$位置快速计算最大的$j$。  
首先，$w_i$对答案无影响，然后$dis_{j,i}=dis_{j,i-1}+wei_{i-1,i}$  
而$wei_{i-1,i}$对每个不同的$j$是没有影响的。  
那么可以考虑维护$w_j+dis_{j,?}$的最大值，递推可做。  
这个东西在下面代码中是`res`。  

对于Case 3，这个有点复杂。  
我们要求$i$到$j$的距离，要先从$j$到$1$，再从$1$到$i$。  
其实也和上面的Case 1,2差不多，只是那个$dis_{i,j}$维护起来有点复杂。  
需要两个维护的答案之和。  

### Coding.
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200005,INF=1e18+5;
struct edge{int to,wei,nxt;}e[N<<1];//笔者就是菜，边数组又忘记开两倍了
int n,tot=0,cnt=0,ans1=0,ans2=INF,res,head[N],cir[N],vis[N],f[N],we[N],l[N],l0[N],r[N],r0[N];
inline void adde(int x,int y,int w) {e[++tot]=(edge){y,w,head[x]},head[x]=tot;}//加边
inline int fnd(int x,int fa=-1)//这个是暴力dfs找环
{
	if(vis[x]) return x;else vis[x]=-1;//vis为-1表示不在环里，vis为0表示未访问过，vis为1表示在环里
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) {res=fnd(e[i].to,x);if(res) return cir[++cnt]=x,we[cnt]=e[i].wei,vis[x]=1,res==x?0:res;}
	return 0;
}
inline void dfs(int x,int fa=-1)//dfs，求一棵树的直径
{
	for(int i=head[x];i;i=e[i].nxt)
		if(vis[e[i].to]!=1&&e[i].to!=fa)
			dfs(e[i].to,x),ans1=max(ans1,f[x]+f[e[i].to]+e[i].wei),f[x]=max(f[x],f[e[i].to]+e[i].wei);
}
signed main()
{
//l和r之和就是Case 3的答案，l0是Case 1的答案，r0是Case 2的答案。
	scanf("%lld",&n),memset(vis,0,sizeof(vis)),memset(f,0,sizeof(f));
	for(int i=1,x,y,w;i<=n;i++) scanf("%lld%lld%lld",&x,&y,&w),adde(x,y,w),adde(y,x,w);
	fnd(1),we[0]=0;for(int i=1;i<=cnt;i++) dfs(cir[i]),we[i]+=we[i-1];//这里其实可以考虑用前缀和，处理起来更加方便一点。
	res=l[0]=l0[0]=-INF;//初始值赋极小值，res就是之前说的那个递推的东西
	for(int i=1;i<=cnt;i++) l0[i]=max(l0[i-1],f[cir[i]]+we[i]+res),l[i]=max(l[i-1],f[cir[i]]+we[i]),res=max(res,f[cir[i]]-we[i]);
	res=r[cnt+1]=r0[cnt+1]=-INF;//反着递推
	for(int i=cnt;i>=1;i--) r0[i]=max(r0[i+1],f[cir[i]]-we[i]+res),r[i]=max(r[i+1],f[cir[i]]+we[cnt]-we[i]),res=max(res,f[cir[i]]+we[i]);
	for(int i=1;i<=cnt;i++) ans2=min(ans2,max(l[i-1]+r[i],max(l0[i-1],r0[i])));//最后统计链上答案
	return printf("%lld\n",max(ans1,ans2)),0;//这里千万要注意，如果不和ans2取max就会WA
}
```

---

## 作者：Ofnoname (赞：23)

n点n边，则此题为基环树也， 去一边犹联通之，则则此条边即环上之边。

此求基环树径之题， 宜先学树之直径而为之
![](https://cdn.luogu.com.cn/upload/image_hosting/1cic8fm0.png)
我们都知道基环树的直径有两种情况。如果直径在子树内(红色)，那么无论怎么去掉环上的边，都是改变不了这个直径的，我们把所有这样的直径记为ans1.

第二种就是从环上选取两个点x,y（绿色），他们能往下走的最大值(记为f)，那么`f[x]+f[y]+dis[x,y]`就是直径的答案之一，但是由于本题会断掉一条边，计算会稍微麻烦些，我们把这里计算的断每一条边的最小答案记为ans2,那么`max(ans1,ans2)`就是答案。

设想找到了环，长度为M，记录为c，而环上所有边的前缀和记为v。

如果`c[i-1]`到`c[i]`的边断了，这时候的过环直径有三种情况：

1. 左右端点l,r都在`[1, i-1]`内，此时`L=(f[R]+v[R])+(f[L]-v[L])`（如果你求v的写法跟我不同，也有可能是`-v[L-1]`）。我们从左向右维护一个L0记录`f[i]-v[i]`最大即可解决。

2. 左右端点l,r都在`[i, M]`内，此时`L=(f[L]-v[L])+(f[R]+v[R])`。我们从右向左维护一个R0记录`f[i]+v[i]`最大即可解决。

3. 左端点在`[i, M]`内，右端点在`[1,i-1]`内，此时`L=(f[L]+v[L])+(f[R]+(v[M]-v[L]))`，从左向右，从右向左分别维护L,R记录他们的最大值即可解决。

当预处理完4个数组，断裂`i-1`到`i`的边时，答案就是：`max（L0[i-1],R0[i],L[i-1]+R[i]）`。

```cpp
#include <bits/stdc++.h> 
#define MAX (200000 + 7)
#define long long long
using namespace std;

int N,M,c[MAX],use[MAX],head[MAX];
long ans1,ans2,FA,v[MAX],f[MAX],L[MAX],L0[MAX],R[MAX],R0[MAX];

struct edge{int y,z,nxt;} E[MAX<<1];
void add(int x, int y, int z, int i)
{
	E[i] = edge{y, z, head[x]};
	head[x] = i;
}

#define y E[p].y
#define z E[p].z
int DFS(int x, int fa)
{
	if (use[x]) return x;
	
	use[x] = 1;
	for (int p = head[x]; p; p=E[p].nxt)
		if (y != fa)
		{
			FA = DFS(y, x);
			if (FA)
			{
				c[++M] = x; v[M] = z; use[x] = 2;
				return FA==x ? 0 : FA;
			}
		}
	return 0;
}

void DFS2(int x, int fa)
{
	for (int p = head[x]; p; p=E[p].nxt)
		if (use[y]!=2 && y!=fa)
		{
			DFS2(y, x);
			ans1 = max(ans1, f[x] + f[y] + z);
			f[x] = max(f[x], f[y] + z);
		}
}
#undef y
#undef z

int main()
{
	scanf("%d", &N);
	for (int i = 1 ,x, y, z; i <= N; i++)
	{
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z, i*2); add(y, x, z, i*2-1);
	}
	DFS(1, -1);//找环，求解c，v数组。 
	for (int i = 1; i <= M; i++)
		DFS2(c[i], 0), v[i] += v[i-1];//求解ans1，f数组并计算v的前缀和 
	//以上为树的直径知识 
		
	FA = L[0] = L0[0] = -1e18;
	for (int i = 1; i <= M; i++)
	{//从左向右更新L和L0 
		L0[i] = max(L0[i-1], f[c[i]] + v[i] + FA);
		L[i] = max(L[i-1], f[c[i]] + v[i]);
		FA = max(FA, f[c[i]] - v[i]);//更新当前f[i]-c[i]最大值 
	}
	FA = R[M+1] = R0[M+1] = -1e18;
	for (int i = M; i >= 1; i--)
	{//同上 
		R0[i] = max(R0[i+1], f[c[i]] - v[i] + FA);
		R[i] = max(R[i+1], f[c[i]] + v[M]- v[i]);
		FA = max(FA, f[c[i]] + v[i]);
	}
	
	ans2 = 1e18;
	for (int i = 1; i <= M; i++)//统计答案 
		ans2 = min(ans2, max(L[i-1]+R[i], max(L0[i-1], R0[i])));
	printf("%lld\n", max(ans1, ans2));
}
```
其他基环树好题：

[P1399 [NOI2013]快餐店](https://www.luogu.org/problem/P1399)

[P4381 [IOI2008]Island](https://www.luogu.org/problem/P4381)

---

## 作者：Mirach (赞：10)

Problem
------

[CodeForces-835F](codeforces.com/problemset/problem/835/F)

题意：求基环树删去环上任意一边后直径最小值，直径定义为所有点对最近距离的最大值

Solution
------

首先明确删去环上一点是不会影响树内直径的，所以应当先把所有树的直径求出来，这是树形Dp可以解决的，同时建议使用树形Dp，可以一次性求出接下来要用到的数据

这是直径在树上的情况，接下来考虑直径从树开始，中途经过环，最后回到树的情况

我们先把每个点向树里头能走的最远距离（也就是带权深度）$f[x]$求出来，同时把环排成一行，放到栈里头$st[1]$~$st[top]$，同时把这个环边权的前缀和求出来，放到数组$pre$里面

考虑删去边$(st[d],st[d+1])$

则最远点对$(x,y)$有这两种情况：

* $case~1~(1\leq x\leq y\leq d~or~d+1\leq x\leq y\leq n): ans=f[x]-pre[x]+f[y]+pre[y]$
* $case~2~(1\leq x\leq d,d+1\leq y\leq n): ans=f[x]+pre[x]+f[y]-pre[y]+pre[n]$

由于我们需要快速求出删去每一条边的最远点对，所以可以考虑维护前缀后缀最大值：

$gl_x=\max\{f_i-pre_i\big|i\in[1,x]\}$

$gr_x=\max\{f_i-pre_i\big|i\in[x,n]\}$

$hl_x=\max\{f_i+pre_i\big|i\in[1,x]\}$

$hr_x=\max\{f_i+pre_i\big|i\in[x,n]\}$

这样的话，最远距离$ans$可以转化为$ans=\max(fl_d+hl_d,fr_{d+1}+hr_{d+1},pre_n-hl_d+gr_{d+1})$

由于这是个环，记得特殊考虑删去边$(top,1)$

还有一点需要注意，就是加起来的两个值不能在同一个地方取到，比如说$fl_2=f_1-pre_1,hl_2=f_1+pre_1$，则$fl_2$和$hl_2$加起来是没有意义的，需要舍去，所以我们对于每个数组还需要维护一个次大值

嗯，你没看错，就是八个数组( • ̀ω ⁃᷄)✧

Code
------
如果需要解释的话，$get\_cir$是找环的，$dfs$是处理树的情况的，$work$是处理环的

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=201000;const ll inf=0x3f3f3f3f3f3f3f3f;
struct Edge{int v,nxt,w;}a[N<<1];
int head[N],is[N],st[N],vis[N];
ll f[N],pre[N];
int gl[N],gr[N],hl[N],hr[N],hhl[N],hhr[N],ggl[N],ggr[N];
int n,m,_,top;ll Ans;

void get_cir(int x,int las){
	if(vis[x]){
		int p=top;
		while(st[p]^x)--p;
		for(rg int i=p;i<=top;++i)
			is[st[i-p+1]=st[i]]=1;
		st[0]=-1;top-=p-1;
		return ;
	}vis[st[++top]=x]=1;
	for(int i=head[x];i&&~st[0];i=a[i].nxt)
		if(a[i].v^las)get_cir(a[i].v,x);
	if(~st[0])vis[st[top--]]=0;
}

void dfs(int x,int las){
	ll sec=0ll;
	for(int i=head[x];i;i=a[i].nxt)
		if(!is[a[i].v]&&a[i].v^las){
			dfs(a[i].v,x);f[a[i].v]+=a[i].w;
			if(f[a[i].v]>=f[x])sec=f[x],f[x]=f[a[i].v];
			else if(f[a[i].v]>sec)sec=f[a[i].v];
		}
	Ans=max(Ans,f[x]+sec);
}

inline ll G(int x){return x?f[st[x]]-pre[x]:-inf;}
inline ll H(int x){return x?f[st[x]]+pre[x]:-inf;}

void work(){
	st[0]=st[top];
	for(rg int x=1;x<=top;++x){
		for(rg int i=head[st[x-1]];i;i=a[i].nxt)
			if(a[i].v==st[x]){
				pre[x]=pre[x-1]+a[i].w;
				break;
			}
		dfs(st[x],0);
	}
	for(rg int i=1;i<=top;++i){
		gl[i]=gl[i-1],ggl[i]=ggl[i-1];
		hl[i]=hl[i-1],hhl[i]=hhl[i-1];
		if(G(i)>G(gl[i]))ggl[i]=gl[i],gl[i]=i;
		else if(G(i)>G(ggl[i]))ggl[i]=i;
		if(H(i)>H(hl[i]))hhl[i]=hl[i],hl[i]=i;
		else if(H(i)>H(hhl[i]))hhl[i]=i;
	}
	for(rg int i=top;i;--i){
		gr[i]=gr[i+1],ggr[i]=ggr[i+1];
		hr[i]=hr[i+1],hhr[i]=hhr[i+1];
		if(G(i)>G(gr[i]))ggr[i]=gr[i],gr[i]=i;
		else if(G(i)>G(ggr[i]))ggr[i]=i;
		if(H(i)>H(hr[i]))hhr[i]=hr[i],hr[i]=i;
		else if(H(i)>H(hhr[i]))hhr[i]=i;
	}
	ll ans;
	if(hl[top]!=gl[top])ans=G(gl[top])+H(hl[top]);
	else ans=max(G(ggl[top])+H(hl[top]),G(gl[top])+H(hhl[top]));
	for(rg int i=1;i<top;++i){
		ll val=pre[top]+H(hl[i])+G(gr[i+1]);
		ll tmp;
		if(gl[i]^hl[i])tmp=G(gl[i])+H(hl[i]);
		else tmp=max(G(ggl[i])+H(hl[i]),G(gl[i])+H(hhl[i]));
		val=max(val,tmp);++i;
		if(gr[i]^hr[i])tmp=G(gr[i])+H(hr[i]);
		else tmp=max(G(ggr[i])+H(hr[i]),G(gr[i])+H(hhr[i]));
		val=max(val,tmp);--i;
		ans=min(ans,val);
	}cout<<max(ans,Ans)<<endl;
}

void init();void work();
int main(){init();work();return 0;}

void init(){
	read(n);int u,v,w;
	for(rg int i=1;i<=n;++i){
		read(u),read(v),read(w);
		a[++_].v=v,a[_].w=w,a[_].nxt=head[u],head[u]=_;
		a[++_].v=u,a[_].w=w,a[_].nxt=head[v],head[v]=_;
	}get_cir(1,1);
}
```

---

## 作者：zac2010 (赞：4)

### 前言

[双倍经验题](https://www.luogu.com.cn/problem/P1399)。按我的做法本题答案除以 $2$ 就能通过那道题。

这是一题基环树入门题，很套路。就是把基环树转到序列上乱搞一通就过了。

### 思路

基环树转到序列上过于套路，没啥可讲的，就讲一下序列上则怎么处理吧。

我们假设现在已经转到了序列上（不用把序列复制一遍，而是直接处理），我们枚举断边，那么可以观察到现在被分为了两边——当前断边断开的左边和右边，我们可以预处理出 $mx1$ 表示当前以及当前左边的所有节点子树，这些节点中的最远距离，即维护前缀最远距离。$mx2$ 乃反之，亦然，为后缀最远距离。

我们发现可能会存在最远点对中一个在左边，一个在右边，那么我们就维护一个 $mxq$ 表示当前的前缀距离（当前点到序列最前面点的距离）加上当前子树内的最大深度节点，$mxh$ 与其堆成，表示当前的后缀距离（当前点到序列最后面点的距离）加上当前子树内的最大深度节点。

可以借助下图进行理解：![](https://cdn.luogu.com.cn/upload/image_hosting/te7knvow.png)

所以每次取 $mx1_i$、$mx2_{i+1}$ 与 $mxq_i+mxh_{i+1}+\text{连接序列首尾两点的那条边}$ 的最大值作为断当前边的直径，那么拿所有断边的直径取最小值就是答案。

坑点提醒：
* 直径可能存在于单个环上节点的子树内。
* 只能删环上的边，因为删完要保持连通。

[代码](http://codeforces.com/contest/835/submission/200838347)。

---

## 作者：Piwry (赞：4)

来个不太一样的做法（感谢[讨论区](https://www.luogu.com.cn/discuss/show/255658)的 @C3H5ClO qwq）

## 解析

前面其它题解提到的部分就直接给定义了

### 转化问题

首先我们断环为链，并把得到的链序列复制一遍，这样在这个复制后序列上滑动一个宽度为 $k$ 的窗口，其中 $k$ 为环上结点个数，就可以得到所有的断环情况

具体来讲，我们随便设环上一个结点为起点，并从它开始按规定方向不重复遍历环上结点，就得到了一个序列 $\{u_0, \cdots, u_{k-1}\}$，设序列从 $0$ 开始，其中 $k$ 为环上结点个数。接着将该序列复制一遍，得到序列 $\{u_0, \cdots, u_{k-1}, u_0, \cdots, u_{k-1}\}$，重标号为 $\{u_0, \cdots, u_{k-1}, u_k, \cdots, u_{2k-1}\}$，若有一个宽为 $k$ 窗口在序列中滑动，并规定窗口中第一个元素和最后一个元素间的边是断边，该窗口的所有可能状态就对应着所有可能的断边状态

同时在做树 dp 时，我们应该已经对环上每一个点处理出了它只向子树走的最长路径，记为 $f(u)$

再来考虑一段路径的贡献，其显然为 $f(u)+f(v)+dist(u, v)$，其中 $u$ 是环上起点，$v$ 是环上终点，$dist(u, v)$ 指从 $u$ 到 $v$ 在环上按规定方向遍历的路径长

而 $dist(u, v)$ 其实可以用前缀和维护。具体来说，给 $u_0$ 赋权值 $0$，对于其余的 $u_i$ 赋权值 $w(u_{i\mod k}, u_{(i-1)\mod k})$，其中 $w(u, v)$ 指图中对应边的权值；我们给这个值做一个前缀和，记为 $s(u)$，上面的贡献式子就可以写为 $f(u)-s(u)+f(v)+s(v)$，我们要令它最大

### 滑动窗口维护次大值

由于式子里有两个元素，一个是 “加” 一个是 “减”，所以我们要维护两种值的最大值。但注意到当 $f(u)$ 足够大时，两种值的最大值都会取同一个结点，这显然是不合法的，因此我们还需维护次大值。滑动窗口次大值单调队列是不可做的（如果有什么方法请告诉我qaq），这里给出一个其它思路的线性做法

设区间从 $0$ 开始标号，窗口大小为 $m$

设 $f(x, 0/1)$ 表示右端点为 $x$，左端点为最大的 $y$ 满足 $y< x$ 且 $(m-1)|y$，区间 $(y, x]$ 的最大值（`0`）、次大值（`1`）

设 $g(x, 0/1)$ 表示左端点为 $x$，右端点为最小的 $y$ 满足 $y\geq x$ 且 $(m-1)|y$，区间 $[x, y]$ 的最大值（`0`）、次大值（`1`）

对于任意窗口，设其左端点为 $l$，其范围就为 $[l, l+m-1]$。**它一定包含一个下标能被 $(m-1)$ 整除的元素**；设该元素下标为 $z$，还一定满足 $[l, z], (z, l+m-1]$ 均非空。

设 $f'(x)=\max(f(x, 0), f(x, 1))$， $g'(x)$ 也同。于是该窗口的最大值就为 $\max(g'(l), f'(l+m-1))$，次大值也可用类似的方法计算出

另外如果区间有次大值，则应满足 $m\geq 2$，所以整除 $(m-1)$ 没有大碍

（其实改成 $m$ 也可以，用类似的方式定义就行了，两个区间不满足均非空但没有大碍。只是我敲代码时还没发现这点，为了方便代码理解题解里就讲成 $m-1$ 了）

同时这个方法也可维护滑动窗口的其它可逆/不可逆区间信息（不过必须得可合并）

## CODE

预处理上述两个数组只需顺着逆着遍历一遍序列，每隔 $(m-1)$ 就清空一次最大/次大值即可

但注意更新值、记录值（预处理数组）、清空值的顺序，根据上面定义的开/闭区间等会有一些变化（话说这里的顺序我是直接手模出来的X）

另外由于还需记录值对应的结点编号，因此代码会有一些壮观...不过只要思路看懂了自己应该也能敲出来X（最后我实际打出来也没调多久）

```cpp
#include <cstdio>
#include <iostream>
#define ll long long
using std::max;
using std::min;

const int MAXN =2e5+50;

/*------------------------------Map------------------------------*/

int n, m;
int first[MAXN], tote;
struct edge{
	int net, to, w;
}e[MAXN<<1];

inline void addedge(int u, int v, int w){
	++tote;
	e[tote].to =v, e[tote].w =w, e[tote].net =first[u];
	first[u] =tote;
	++tote;
	e[tote].to =u, e[tote].w =w, e[tote].net =first[v];
	first[v] =tote;
}

/*------------------------------Circle------------------------------*/

int circle/*环上一点，相当于 index*/, lenc/*环长度*/;
int pre[MAXN], net[MAXN], evalpre[MAXN], evalnet[MAXN];
bool vis[MAXN], color[MAXN];
int stk[MAXN], top;

int predfs(int u, int eid/*处理重边环*/){
	if((eid&1) == 0)
		--eid;
	else
		++eid;
	vis[u] =1;
	stk[top++] =u;
	for(int l =first[u]; l; l =e[l].net)
		if(l != eid){
			net[u] =e[l].to;
			evalnet[u] =e[l].w;
			if(vis[e[l].to])
				return e[l].to;
			else{
				int ret =predfs(e[l].to, l);
				if(ret != 0)
					return ret;
			}
		}
	--top;
	return 0;
}

void getCircle(){
	int cir =predfs(1, 0);
	circle =cir;
	lenc =1;
	/*接环并给环染色*/
	pre[cir] =stk[top-1];
	evalpre[cir] =evalnet[stk[top-1]];
	color[cir] =1;
	while(stk[top-1] != cir){
		++lenc;
		pre[stk[top-1]] =stk[top-2];
		evalpre[stk[top-1]] =evalnet[stk[top-2]];
		color[stk[top-1]] =1;
		--top;
	}
}

/*------------------------------Dfs------------------------------*/

ll dp1[MAXN], dp2[MAXN];/*从 u 向子树走最大、次大的链*/
ll Anst;

void dfs1(int u, int fa){
	for(int l =first[u]; l; l =e[l].net)
		if(e[l].to != fa && !color[e[l].to]/*避免走环*/){
			dfs1(e[l].to, u);
			if(e[l].w+dp1[e[l].to] > dp1[u]){
				dp2[u] =dp1[u];
				dp1[u] =e[l].w+dp1[e[l].to];
			}
			else if(e[l].w+dp1[e[l].to] > dp2[u])
				dp2[u] =e[l].w+dp1[e[l].to];
		}
	Anst =max(Anst, dp1[u]+dp2[u]);
}

/*------------------------------滑动窗口------------------------------*/

/*其中 z 代表 x 左且 z<x / 右且 z>=x，最近的下标被 m-1 整除的点，其中 m 为窗口大小*/
/*前两个是 dp+sum，后两个是 dp-sum，第二维代表最大/次大值*/
ll l1[MAXN<<1][2]/*(z, x]*/, r1[MAXN<<1][2]/*[x, z]*/, l2[MAXN<<1][2], r2[MAXN<<1][2];
int idl1[MAXN<<1][2], idr1[MAXN<<1][2], idl2[MAXN<<1][2], idr2[MAXN<<1][2];

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

inline void modify(ll &mx, ll & mxs, int &idmx, int &idmxs, const ll &val, const int &idval){
	if(val > mx)
		mxs =mx, idmxs =idmx, mx =val, idmx =idval;
	else if(val > mxs)
		mxs =val, idmxs =idval;
}

int main(){
	n =read();
	for(int i =0; i < n; ++i){
		int u =read(), v =read(), w =read();
		addedge(u, v ,w);
	}
	getCircle();
	for(int u =circle, flg =0; u != circle || flg == 0; u =net[u]){
		if(u == circle)
			flg =1;
		dfs1(u, 0);
	}
	ll sum =-evalpre[circle];
	/*走两圈，序列大致为：s, ..., t, s, ..., t*/
	ll mx1 =0, mx1s =0, mx2 =-0x3f3f3f3f3f3f3f3f, mx2s =-0x3f3f3f3f3f3f3f3f;/*mx 最大，mxs 次大，注意 mx2 可能取负数*/
	int idmx1 =-1, idmx1s =-1, idmx2 =-1, idmx2s =-1;
	for(int u =circle, flg =0, i =0; u != circle || flg < 2; u =net[u], ++i){
		if(u == circle)
			++flg;
		sum +=evalpre[u];
		modify(mx1, mx1s, idmx1, idmx1s, dp1[u]+sum, i);
		modify(mx2, mx2s, idmx2, idmx2s, dp1[u]-sum, i);
		l1[i][0] =mx1, idl1[i][0] =idmx1, l1[i][1] =mx1s, idl1[i][1] =idmx1s;
		l2[i][0] =mx2, idl2[i][0] =idmx2, l2[i][1] =mx2s, idl2[i][1] =idmx2s;
		if(i%(lenc-1) == 0)/*开区间，且注意顺序 ( 这里顺序我是靠手模解决的 X )*/
			mx1 =mx1s =0, mx2 =mx2s =-0x3f3f3f3f3f3f3f3f,
			idmx1 =-1, idmx1s =-1, idmx2 =-1, idmx2s =-1;
	}
	/*注意 sum 不要清空，以及注意接下来对 sum 的处理*/
	mx1 =0, mx1s =0, mx2 =-0x3f3f3f3f3f3f3f3f, mx2s =-0x3f3f3f3f3f3f3f3f;
	idmx1 =-1, idmx1s =-1, idmx2 =-1, idmx2s =-1;
	for(int u =pre[circle], flg =0, i =2*lenc-1/*注意下标*/; u != pre[circle] || flg < 2; u =pre[u], --i){
		if(u == pre[circle])
			++flg;
		if(i%(lenc-1) == 0)/*闭区间，且注意顺序*/
			mx1 =mx1s =0, mx2 =mx2s =-0x3f3f3f3f3f3f3f3f,
			idmx1 =-1, idmx1s =-1, idmx2 =-1, idmx2s =-1;
		modify(mx1, mx1s, idmx1, idmx1s, dp1[u]+sum, i);
		modify(mx2, mx2s, idmx2, idmx2s, dp1[u]-sum, i);
		r1[i][0] =mx1, idr1[i][0] =idmx1, r1[i][1] =mx1s, idr1[i][1] =idmx1s;
		r2[i][0] =mx2, idr2[i][0] =idmx2, r2[i][1] =mx2s, idr2[i][1] =idmx2s;
		sum -=evalpre[u];
	}
	/*走一圈统计答案, 初始窗口大概是这样的：[s, ..., t], s, ..., t*/
	ll Ansc =0x3f3f3f3f3f3f3f3f;
	for(int u =circle, flg =0, i =0; u != circle || flg < 1; u =net[u], ++i){
		if(u == circle)
			++flg;
		ll Mx1 =0, Mx1s =0, Mx2 =-0x3f3f3f3f3f3f3f3f, Mx2s =-0x3f3f3f3f3f3f3f3f;
		int idMx1 =-1, idMx1s =-1, idMx2 =-1, idMx2s =-1;
		modify(Mx1, Mx1s, idMx1, idMx1s, r1[i][0], idr1[i][0]), modify(Mx1, Mx1s, idMx1, idMx1s, r1[i][1], idr1[i][1]);
		modify(Mx1, Mx1s, idMx1, idMx1s, l1[i+lenc-1][0], idl1[i+lenc-1][0]), modify(Mx1, Mx1s, idMx1, idMx1s, l1[i+lenc-1][1], idl1[i+lenc-1][1]);
		modify(Mx2, Mx2s, idMx2, idMx2s, r2[i][0], idr2[i][0]), modify(Mx2, Mx2s, idMx2, idMx2s, r2[i][1], idr2[i][1]);
		modify(Mx2, Mx2s, idMx2, idMx2s, l2[i+lenc-1][0], idl2[i+lenc-1][0]), modify(Mx2, Mx2s, idMx2, idMx2s, l2[i+lenc-1][1], idl2[i+lenc-1][1]);
		ll Mx;
		if(idMx1 != idMx2)/*如果两种最大值的 id 不同*/
			Mx =Mx1+Mx2;
		else
			Mx =max(Mx1+Mx2s, Mx1s+Mx2);
		Ansc =min(Ansc, Mx);
	}
	printf("%lld", max(Anst, Ansc));
}
```

---

## 作者：glorious_dream (赞：3)

### 算法分析：

首先这是一道基环树的题。给定 $n$ 个点和 $n$ 条边，而且保证联通，那么就存在一个环。

那么考虑如何求直径。有两种情况。

$1$.直径不经过基环。

$2$.直径经过基环。

在求直径之前，我们需要将哪些点在环上记录下来。我们从 $1$ 号点开始深搜找环。具体看代码注释。

```cpp
inline bool find(int u){
	vis[u] = 1; //这个点记录为走过 
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(v == fa[u]) continue; //走到了父亲不行 
		fa[v] = u;
		w[v] = e[i].w; //将这条边的边权转化为儿子的点权，和树剖的转化类似 
		if(!vis[v]) { if(find(v)) return 1; } //如果这个点没有走过而且后面能找到环，就一直往回return 
		else{ //找到了环 
			int p = u; //枚举环上的点 
			while(1){
				inc[p] = 1; //inc[p]=1表示p在环上 
				cv[++tot] = p; //环上的点的编号，由于后面操作，我们需要重新编号 
				cw[tot] = w[p]; //环上这个编号点的点权 
				p = fa[p]; //由于记录了fa[p]是p的父亲，所以可以往回找 
				if(p == u) break; //环遍历完了 
			}
			return 1; //记录已经找到环 
		}
	}
	return 0; //没找到就继续往下找 
}
```


一个一个考虑，先看直径不经过基环，这个比较好求。此基环树的直径为环上挂着的点的每一棵子树的最大直径，记为 $res1$，枚举环上的每一个点，深搜计算子树的直径 $res1 = max(d[u]+d[v]+w(u,v))$。顺道求出以 $u$ 为根的子树的最大深度 $d[u]$。

```cpp
inline void dfs(int u,int fa){
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to,w = e[i].w;
		if(inc[v] || v==fa) continue; //如果这个点在环上，或者搜到了父亲就不继续 
		dfs(v,u); //往下搜 
		res1 = max(res1,d[u]+d[v]+w); //求最大的直径 
		d[u] = max(d[u],d[v]+w); //顺道记录下来以u为根的最大深度 
	}
}

rep(i,1,tot) dfs(cv[i],0);
```

然后来看直径经过环。一个最简单的想法就是，暴力枚举删哪一条边， $res[i] = max ($两个子树的深度 $+$ 它们在环上的距离 $)$。则经过环的直径 $res2 = min(res[i])$。

但这样做复杂度是 $n^2$ 的，过不去本题。考虑如何进行优化。

$1$.把边 $(1,tot)$ 断开，$tot$ 为环上有 $tot$ 个点，预处理前缀长度。

$A[i] = max($ 前缀中链的长度 $+$ 节点树的深度 $)$。

$B[i] = max($ 前缀中两棵树的深度 $+$ 这两个节点之间的距离 $)$。

$2$.把边 $(1,tot)$ 断开，预处理后缀长度。

$C[i] = max($ 后缀中链的长度 $+$ 节点树的深度 $)$。

$D[i] = max($ 后缀中两棵树的深度 $+$ 这两个节点之间的距离 $)$。

3.枚举断开环上的边 $(i,i+1)$，拼凑答案。

$res[i] = max(B[i],D[i+1],A[i]+C[i+1]+w(1,tot))$

则经过环的直径 $res2 = min(res[i])$。

注意，最后需要有个特判，断开 $(1,tot)$ 这条边，需要加上一句话 $res2 = min(res2,B[tot])$。

那么基环树的直径就是 $max(res1,res2)$，这道题的答案就是 $max(res1,res2)$。

```cpp
double sum=0,mx=0;
	rep(i,1,tot){ //预处理前缀 
		sum += cw[i-1]; //sum就是链长的加和 
		A[i] = max(A[i-1],sum+d[cv[i]]); //根据A数组的定义来推 
		B[i] = max(B[i-1],mx+d[cv[i]]+sum); //这里很巧妙
											//我们的mx记录的是i这个点之前的某一个点k的深度-k之前的链长 
											//也就是说，我们要求B数组，可以用一个抵消的思想
											//sum记录的是链长的加和，再加上mx，也就把k前面的链长消掉了
											//最后剩的就是k的深度+k到i的链长+i的深度，与B数组定义相同 
		mx = max(mx,d[cv[i]]-sum); //注意要更新mx 
	}
	sum = mx = 0;
	double cn_1 = cw[tot]; //这里也很巧妙，把tot这个点的点权记录下来，也就是相当于把1和tot这条边断开 
	cw[tot] = 0; //要把tot这个点点权清零 
	drep(i,tot,1){ //预处理后缀，和前缀类似 
		sum += cw[i];
		C[i] = max(C[i+1],sum+d[cv[i]]);
		D[i] = max(D[i+1],mx+d[cv[i]]+sum);
		mx = max(mx,d[cv[i]]-sum);
	}
	double res;
	rep(i,1,tot){
		res = max(max(B[i],D[i+1]),A[i]+C[i+1]+cn_1); //上述所说的三段 
		res2 = min(res2,res); //使res2最小化 
	}
	res2 = min(res2,B[tot]); //别忘了加上特判 
	printf("%.1lf\n",max(res1,res2)/2);
```

### 总代码：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define re register
#define int long long
#define double long long
#define drep(a,b,c) for(re int a(b) ; a>=(c) ; --a)
#define rep(a,b,c) 	for(re int a(b) ; a<=(c) ; ++a)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int M = 2e6+10;
int n;
int head[M],vis[M],fa[M];
int inc[M],cv[M],cw[M],w[M];
double d[M],A[M],B[M],C[M],D[M];
int cnt,tot,ans;
double res1,res2=1e18;
struct edge{
	int to,nxt,w;
}e[M];
inline void add(int u,int v,int w){
	e[++cnt].to = v;
	e[cnt].w = w;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}
inline bool find(int u){
	vis[u] = 1; //这个点记录为走过 
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to;
		if(v == fa[u]) continue; //走到了父亲不行 
		fa[v] = u;
		w[v] = e[i].w; //将这条边的边权转化为儿子的点权，和树剖的转化类似 
		if(!vis[v]) { if(find(v)) return 1; } //如果这个点没有走过而且后面能找到环，就一直往回return 
		else{ //找到了环 
			int p = u; //枚举环上的点 
			while(1){
				inc[p] = 1; //inc[p]=1表示p在环上 
				cv[++tot] = p; //环上的点的编号，由于后面操作，我们需要重新编号 
				cw[tot] = w[p]; //环上这个编号点的点权 
				p = fa[p]; //由于记录了fa[p]是p的父亲，所以可以往回找 
				if(p == u) break; //环遍历完了 
			}
			return 1; //记录已经找到环 
		}
	}
	return 0; //没找到就继续往下找 
}
inline void dfs(int u,int fa){
	for(re int i(head[u]) ; i ; i=e[i].nxt){
		int v = e[i].to,w = e[i].w;
		if(inc[v] || v==fa) continue; //如果这个点在环上，或者搜到了父亲就不继续 
		dfs(v,u); //往下搜 
		res1 = max(res1,d[u]+d[v]+w); //求最大的直径 
		d[u] = max(d[u],d[v]+w); //顺道记录下来以u为根的最大深度 
	}
}
signed main(){
	n=read();
	rep(i,1,n){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	find(1);
	rep(i,1,tot) dfs(cv[i],0);
	double sum=0,mx=0;
	rep(i,1,tot){ //预处理前缀 
		sum += cw[i-1]; //sum就是链长的加和 
		A[i] = max(A[i-1],sum+d[cv[i]]); //根据A数组的定义来推 
		B[i] = max(B[i-1],mx+d[cv[i]]+sum); //这里很巧妙
											//我们的mx记录的是i这个点之前的某一个点k的深度-k之前的链长 
											//也就是说，我们要求B数组，可以用一个抵消的思想
											//sum记录的是链长的加和，再加上mx，也就把k前面的链长消掉了
											//最后剩的就是k的深度+k到i的链长+i的深度，与B数组定义相同 
		mx = max(mx,d[cv[i]]-sum); //注意要更新mx 
	}
	sum = mx = 0;
	double cn_1 = cw[tot]; //这里也很巧妙，把tot这个点的点权记录下来，也就是相当于把1和tot这条边断开 
	cw[tot] = 0; //要把tot这个点点权清零 
	drep(i,tot,1){ //预处理后缀，和前缀类似 
		sum += cw[i];
		C[i] = max(C[i+1],sum+d[cv[i]]);
		D[i] = max(D[i+1],mx+d[cv[i]]+sum);
		mx = max(mx,d[cv[i]]-sum);
	}
	double res;
	rep(i,1,tot){
		res = max(max(B[i],D[i+1]),A[i]+C[i+1]+cn_1); //上述所说的三段 
		res2 = min(res2,res); //使res2最小化 
	}
	res2 = min(res2,B[tot]); //别忘了加上特判 
	printf("%.1lf\n",max(res1,res2));
	return 0;
}
```


---

## 作者：________a____ (赞：3)

## 题目大意

求基环树的直径。

## 解析

一颗基环树的直径有两种情况：

1. 直径为环上某一点子树的直径。
2. 直径为环上某一点子节点经过环到达另一点子节点。

对于情况 $1$，显然断环上哪条边对子树直径不会有影响，可以直接处理出来。

对于情况 $2$，可以求断掉环上任意一边的直径的最大值(也就相当于钦定一条边不属于直径，求出所以可能的直径情况)：

 ![](https://cdn.luogu.com.cn/upload/image_hosting/qt6z5cqn.png)

将环上任意一边断开拆环为链，并复制一遍接在末尾：

![](https://cdn.luogu.com.cn/upload/image_hosting/h4gxe78j.png)

用一个长度为环的点数的窗口从左向右扫过去，每次更新答案，就可以包含所以断边的情况。

如图，若先断开 $1,3$ 之间的边。

令 $dep_i$ 为 $i$ 点子节点的最大深度，$sum_i$ 为 $i$ 距 $1$ 号节点的距离。

令 $a_i=dep_i-sum_i,b_i=dep_i+sum_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/g14ukm6w.png)

如图，红色段为 $a$，蓝色段为 $b$，紫色段为合并后的直径。

直径长度为 $\max\{dep_i+dep_j+sum_j-sum_i\}$ $(sum_i<sum_j)$。

也就是直径为 $\max\{a_i+b_j\}$。

所以可以取 $\max\{a_i\}+\max\{b_j\}$ 为直径。

但可能会出现 $i=j$ 的情况。

所以要维护 $a_i$ 和 $b_i$ 的最大值和次大值。

最后将情况 $1$ 与情况 $2$ 取最大值。

## 实现

建立一个可以支持单点修改并查询最值的数据结构(如线段树)。

断开环上任意一边并将链复制一遍接在末尾。

若环长为$k$。

依次扫描每个点，每次更新 $a_i,b_i$ ,前 $(k-1)$ 个点不更新 $ans$(还没形成一颗完整的树),之后每次查询 $a_i$ 和 $b_i$ 的最大值和次大值更新 $ans$。

每次更新的信息的有效期为 $k$ 次移动窗口。

而 $k$ 次移动窗口是一个循环，又回到了同一点，直接更新 $a$ 和 $b$ ，替代过期信息即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 200010
#define ls p<<1
#define rs p<<1|1
int n;
vector<int> ver[MAXN],e[MAXN];
inline int read(){
    int a=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') {
        a=(a<<1)+(a<<3)+(ch^48);
        ch=getchar();
    }
    return a;
}
inline void add(int u,int v,int w){
    ver[u].push_back(v);
    e[u].push_back(w);
}
int pre[MAXN];
int w[MAXN];
char mark[MAXN];
int dep[MAXN];
int _ans=0;
void dfs_(int u){ //标记环上的点
    if(mark[u]) return ;
    mark[u]=1;
    dfs_(pre[u]);
}
bool dfs(int u,int fa){ //找环
    for(int v,i=0;i<ver[u].size();i++){
        if((v=ver[u][i])==fa) continue;
        if(pre[v]){
            pre[v]=u;
            w[v]=e[u][i];
            dfs_(u);
            return 1;
        }
        pre[v]=u;
        w[v]=e[u][i];
        if(dfs(v,u)) return 1;
    }
    return 0;
}
void dfs_dep(int u,int fa){ //处理子树直径和dep[u]
    for(int i=0,v;i<ver[u].size();i++){
        if((v=ver[u][i])==fa) continue;
        if(mark[v]) continue;
        dfs_dep(v,u);
        _ans=max(_ans,dep[u]+dep[v]+e[u][i]);
        dep[u]=max(dep[u],dep[v]+e[u][i]);
    }
}
int a[MAXN],b[MAXN];
inline bool cmp1(int _a,int _b){ //因为是记录的点的编号,所以按数组对应元素排序
    return a[_a]<a[_b];
}
inline bool cmp2(int _a,int _b){
    return b[_a]<b[_b];
}
struct node {
    int a,aa,b,bb;
    node operator + (node _b){
        node res; //奇丑无比的区间最大值次大值维护
        vector<int> rec;
        rec.push_back(a);
        rec.push_back(aa);
        rec.push_back(_b.a);
        rec.push_back(_b.aa);
        sort(rec.begin(),rec.end(),cmp1);
        res.a=rec[3],res.aa=rec[2];
        rec.clear();
        rec.push_back(b);
        rec.push_back(bb);
        rec.push_back(_b.b);
        rec.push_back(_b.bb);
        sort(rec.begin(),rec.end(),cmp2);
        res.b=rec[3],res.bb=rec[2];

        return res;
    }
}data[MAXN<<2];
inline void push_up(int p){
    data[p]=data[ls]+data[rs];
}
inline void build(int l,int r,int p){
    if(l==r){
        data[p].a=data[p].b=l;
        //记录对应节点编号
        return ;
    }
    int mid=l+r>>1;
    build(l,mid,ls);
    build(mid+1,r,rs);
    push_up(p);
}
void upd(int l,int r,int x,int p){
    if(l==r){
        // 确实什么都没有
        return ;
    }
    int mid=l+r>>1;
    if(mid>=x) upd(l,mid,x,ls);
    else upd(mid+1,r,x,rs);
    push_up(p);
}
inline int qu(){
    if(data[1].a==data[1].b) //如果是同一点，分类讨论更新
        return max(a[data[1].a]+b[data[1].bb],a[data[1].aa]+b[data[1].b]);
    return a[data[1].a]+b[data[1].b]; //不是同一点，直接更新
}
signed main(){
    scanf("%lld",&n);
    for(int i=1,u,v,w;i<=n;i++){
        u=read();
        v=read();
        w=read();
        add(u,v,w);
        add(v,u,w);
    }
    dfs(1,0);
    int __s=-1,sum=0,ans=LONG_LONG_MAX;
    for(int i=1;i<=n;i++)
        if(mark[i]) {
            __s=i;//随便选一个开始点
            dfs_dep(i,0);
        }
    memset(a,0xcf,sizeof a); //初始-inf
    memset(b,0xcf,sizeof b);
    for(int i=__s;mark[i]<=2;i=pre[i]){ //如果第3次扫到一个节点代表已经处理完了
        mark[i]++;
        if(mark[pre[i]]<2){
            a[i]=dep[i]-sum;
            b[i]=dep[i]+sum;
            //upd(1,n,i,1);
            sum+=w[i];
            if(mark[pre[pre[i]]]==2) //因为没有查询，最后建树时一次性push_up会更快
                build(1,n,1);
            continue;
        }
        a[i]=dep[i]-sum;
        b[i]=dep[i]+sum;
        sum+=w[i];
        upd(1,n,i,1);//单点修改
        ans=min(ans,qu());
    }
    if(ans<_ans) ans=_ans; //如果子树直径更长久选子树直径
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：pzc2004 (赞：2)

# Solution
这是一个线段树做法。优点是简单粗暴分类讨论小，但是码量较大，~~请谨慎食用~~。  
$n$ 个点 $n$ 条边，必然是一颗基环树，又因为断边后依然要联通，因此断掉的边必定是基环上的边。  
首先我们找出基环树的环，则最后树的直径只可能有两种情况：要么在基环上的一颗子树内部，要么是基环上的两棵子树内的最长链再加上环上的一段距离。  
![两种情况](https://cdn.luogu.com.cn/upload/image_hosting/0yaqpjvz.png)  
左为情况一，右为情况二。  
第一种情况跟我们断哪条边无关，因此可以直接树形 DP 求出。  
对于第二种情况，我们可以先求出基环上每个子树内的最长链。对于基环上的节点 $i$，记其子树内最长链为 $len_i$。现在我们开始断边，如图所示.![](https://cdn.luogu.com.cn/upload/image_hosting/yjn9u9ff.png)  
我们记断掉的边的一个端点为 $x$，断边后基环上点 $i$ 到 $x$ 的距离为 $dis_i$，则此时过基环的最长链可以表示为 $\max(len_i+dis_i+len_j-dis_j)(i\ne j)$，我们可以分别求出 $len_i+dis_i$ 和 $len_i-dis_i$ 的最大值、次大值来维护（因为两个最大值的来源不能相同，因此还要求出次大值）。注意到当我们换成断掉 $x$ 和下一个节点的边时，除去 $x$ 所有点的 $dis$ 都要减去这条边的边权（现在的 $dis$ 是到 $x$ 的下一个点的距离），而 $x$ 的 $dis$ 要改成基环的总长减去边权。这相当于要进行区间加和单点修改，维护全局最大值，因此我们可以用线段树来动态维护。  
求出两种情况的结果后，我们只需取一个最大值即可得出答案。
# Code
我的线段树维护了最大值、次大值、最大值的来源，因此码量~~可能~~会比较大。
``` cpp
#include <bits/stdc++.h>
using namespace std;
template <class T> inline void read(T &x) {
	x= 0;
	char c= getchar();
	while(!isdigit(c)) c= getchar();
	while(isdigit(c)) x= x * 10 + (c & 15), c= getchar();
}
#define N 100001
int n, head[N], cnt, stk[N], top, a[N], nxt[N], cnt2, id[N];
long long len[N], l, ans= 9223372036854775807, tot, dis[N];
struct Tree {
	long long s1, s2, s3, s4, la;  //s1:len+dis s2:len-dis
	int s5, s6;
} s[N << 2];
bool vis[N];
vector<int> c;
struct Edge {
	int a, b, c;
} e[N << 1];
inline void add(int a, int b, int c) { e[++cnt].a= head[a], e[cnt].b= b, e[cnt].c= c, head[a]= cnt; }
inline void dfs1(int x, int y) {
	if(vis[x]) {
		if(c.empty()) {
			int no= top;
			while(stk[no] != x) c.push_back(stk[no--]);
			c.push_back(x);
		}
		return;
	}
	stk[++top]= x, vis[x]= 1;
	for(int i= head[x]; i; i= e[i].a) {
		if(e[i].b == y) continue;
		dfs1(e[i].b, x);
	}
	--top;
}
inline void dfs2(int x, int y) {
	for(int i= head[x]; i; i= e[i].a) {
		if(e[i].b == y || vis[e[i].b]) continue;
		dfs2(e[i].b, x), l= max(l, len[e[i].b] + e[i].c + len[x]), len[x]= max(len[x], len[e[i].b] + e[i].c);
	}
}
inline void pushUp(int p) {
	if(s[p << 1].s1 > s[p << 1 | 1].s1)
		s[p].s1= s[p << 1].s1, s[p].s5= s[p << 1].s5, s[p].s3= max(s[p << 1].s3, s[p << 1 | 1].s1);
	else
		s[p].s1= s[p << 1 | 1].s1, s[p].s5= s[p << 1 | 1].s5, s[p].s3= max(s[p << 1 | 1].s3, s[p << 1].s1);
	if(s[p << 1].s2 > s[p << 1 | 1].s2)
		s[p].s2= s[p << 1].s2, s[p].s6= s[p << 1].s6, s[p].s4= max(s[p << 1].s4, s[p << 1 | 1].s2);
	else
		s[p].s2= s[p << 1 | 1].s2, s[p].s6= s[p << 1 | 1].s6, s[p].s4= max(s[p << 1 | 1].s4, s[p << 1].s2);
}
inline void pushDown(int p, int l, int r) {
	if(s[p].la) {
		s[p << 1].s1+= s[p].la, s[p << 1 | 1].s1+= s[p].la;
		s[p << 1].s2-= s[p].la, s[p << 1 | 1].s2-= s[p].la;
		int mid= (l + r) >> 1;
		if(mid != l) s[p << 1].s3+= s[p].la, s[p << 1].s4-= s[p].la;
		if(mid + 1 != r) s[p << 1 | 1].s3+= s[p].la, s[p << 1 | 1].s4-= s[p].la;
		s[p << 1].la+= s[p].la, s[p << 1 | 1].la+= s[p].la;
		s[p].la= 0;
	}
}
inline void build(int p, int l, int r) {
	if(l == r) return s[p].s1= len[c[l]] + dis[c[l]], s[p].s2= len[c[l]] - dis[c[l]], s[p].s3= s[p].s4= -9223372036854775807, s[p].s5= s[p].s6= l, void();
	int mid= (l + r) >> 1;
	build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
	pushUp(p);
}
inline void add(int p, int l, int r, int x, long long y) {
	if(l == r) return s[p].s1= len[c[x]] + y, s[p].s2= len[c[x]] - y, void();
	pushDown(p, l, r);
	int mid= (l + r) >> 1;
	if(mid >= x)
		add(p << 1, l, mid, x, y);
	else
		add(p << 1 | 1, mid + 1, r, x, y);
	pushUp(p);
}
signed main() {
	read(n);
	for(int i= 1, x, y, z; i <= n; i++) read(x), read(y), read(z), add(x, y, z), add(y, x, z);
	dfs1(1, 0);
	cnt2= c.size() - 1;
	memset(vis, 0, sizeof(vis));
	for(auto &i : c) vis[i]= 1;
	for(auto &i : c) dfs2(i, 0);
	for(int i= 0; i < (int)c.size(); i++) nxt[c[i]]= c[(i + 1) % c.size()], id[c[i]]= i;
	for(auto &i : c) {
		for(int j= head[i]; j; j= e[j].a)
			if(e[j].b == nxt[i]) {
				a[i]= e[j].c, tot+= a[i];
				break;
			}
		if(nxt[i] != c[0]) dis[nxt[i]]= dis[i] + a[i];
	}
	build(1, 0, cnt2);
	for(auto &i : c) {
		ans= min(ans, (s[1].s5 != s[1].s6) ? s[1].s1 + s[1].s2 : max(s[1].s1 + s[1].s4, s[1].s3 + s[1].s2));
		s[1].s1-= a[i], s[1].s2+= a[i], s[1].s3-= a[i], s[1].s4+= a[i], s[1].la-= a[i];
		add(1, 0, cnt2, id[i], tot - a[i]);
	}
	printf("%0.1lf", max(ans, l) * 0.5);
	return 0;
}
```

---

## 作者：旋转卡壳 (赞：2)

**题目大意：**
给出一颗基环树 希望删掉环上一边后剩下的树的的直径最小 求出这个直径

一道简单的题目 就是有点复杂

我是不会的 很大程度借鉴了 **Mirach** dalao的题解QAQ

首先我们很自然地可以得出一个超快的算法

1、找环

2、预处理环上各点的 **子树直径和与环相连的最长路径的长度**

2、**枚举删掉环上任意一边 求此时经过环的最大路径长度**

3、与原来各子树内部直径比较得出当前直径

4、更新答案

一眼看来 问题就在于删掉一条边后我们如何快速地求出过环的最大路径长度

找环的时候 我们顺便把环上个点压入栈内

则有S[1]/S[2]/……/S[top] (S[1]和S[top]之间也连着边)

那么我们枚举断边i->i+1 (1->top的到时候直接预处理就完事了) 同时用pre[i]数组记录环上的距离前缀和 f[i]为环上的i点到子树的最长距离

这时候就会有三种路径 我们举个例子说明一下(pre[1]为边(6->1)的长度 pre[2]为边(6->1)和(1->2)的和)

1	2	3	4	5	6

我们断掉了3->4

那么会有三种情况

一： 1子树-1-2-2子树 全在左边

ans=f[1]-pre[1]+pre[2]+f[2]

二： 1子树-1-6-5-5子树 一左一右

ans=f[1]+pre[1]+pre[6]-pre[5]+f[5]

三： 4子树-4-5-5子树 全在右边

ans=f[4]-pre[4]+pre[5]+f[5]

所以经过观察会有：

**删掉边(i,i+1)**

**① 1<=x<y<=i或者i+1<=x<y<=top**

**ans=f[x]-pre[x]+f[y]+pre[y]**

**② 1<=x<=i并且i+1<=y<=top**

**ans=f[x]+pre[x]+pre[top]+f[y]-pre[y]**


又因为ans要取最大值 所以

我们可以预处理一些前缀后最最大次大数组(次大是为了防止x==y)

**gl[i] 为当x属于[1,i]时 最大的f[x]-pre[x] (Gl次大)**

**gr[i] 为当x属于[i,top]时 最大的f[x]-pre[x] (Gr次大)**

**hl[i] 为当x属于[1,i]时 最大的f[x]+pre[x] (Hl次大)**

**hr[i] 为当x属于[i,top]时 最大的f[x]+pre[x] (Hr次大)**

那么删掉边(i,i+1)的答案就变成了

**ans=max(gl[i]+hl[i],gr[i+1]+hr[i+1],pre[top]-hl[i]+gr[i+1])**

那差不多就是这样了 但是实现的细节还是有很多的 看代码注释吧= =

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
const int N=2e5+50; const int M=4e5+50;
const ll inf=0x3f3f3f3f3f3f3f3f;
//inf一定要设置大一点 第二次我就因为设为2147483647而WA了 

int n;

inline int read(int x=0,char c=getchar()) {
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}

int edge,head[N],Next[M],to[M],w[M]; //c++11 不能用next 第一次我就CE了 

inline void add_edge(int c,int u,int v) {
	Next[++edge]=head[u];to[head[u]=edge]=v;w[edge]=c;
	Next[++edge]=head[v];to[head[v]=edge]=u;w[edge]=c;
}

int top,S[N],inS[N],loop[N]; //loop[u] u是不是环上的点 

void get_cir(int u,int fa) {
	if(S[0]==-1) return ; //已经找到环了 
	if(inS[u]) { //找环并把环压如栈中 
		int bot=top; while(S[bot]!=u) --bot;
		for(register int i=bot;i<=top;++i) loop[S[i-bot+1]=S[i]]=1;
		top-=(bot-1); S[0]=-1; //此时S[1]到S[top]中就是环上的所有点了 
	} else {
		inS[S[++top]=u]=1;
		for(int i=head[u];i;i=Next[i])
			if(to[i]!=fa) get_cir(to[i],u);
		if(S[0]!=-1) inS[S[top--]]=0; //不要破坏找到环后的S结构 
	}
}

ll ans,Ans,pre[N],f[N],gl[N],gr[N],hl[N],hr[N],Gl[N],Gr[N],Hl[N],Hr[N];
//f[u] 从u点出发的最长的链 

void dfs(int u,int fa,ll sec=0) {
	for(int i=head[u];i;i=Next[i]) if(to[i]!=fa&&!loop[to[i]]) {
		dfs(to[i],u); f[to[i]]+=w[i]; //此时f违反其定义 只是走个过场 
		if(f[to[i]]>=f[u]) sec=f[u],f[u]=f[to[i]]; //维护最大次大值 
		else if(f[to[i]]>sec) sec=f[to[i]];
	} ans=max(ans,f[u]+sec); //树内直径 
}

inline ll G(int x) {return x?f[S[x]]-pre[x]:-inf;} //记得给个大负数 
inline ll H(int x) {return x?f[S[x]]+pre[x]:-inf;}

inline void init() { //预处理pre数组/f数组/子树直径/4个前缀后缀最大次大值 
	S[0]=S[top]; for(register int i=1;i<=top;++i) {
		for(int j=head[S[i-1]];j;j=Next[j]) if(to[j]==S[i])
			{pre[i]=pre[i-1]+w[j]; break;} //环上前缀和 
		dfs(S[i],0);
	} for(register int i=1;i<=top;++i) { //从左到右维护l 
		gl[i]=gl[i-1]; Gl[i]=Gl[i-1]; hl[i]=hl[i-1]; Hl[i]=Hl[i-1];
		//继承上一个的最大值 
		if(G(i)>G(gl[i])) Gl[i]=gl[i],gl[i]=i; //维护g的最大最小值 
		else if(G(i)>G(Gl[i])) Gl[i]=i;
		if(H(i)>H(hl[i])) Hl[i]=hl[i],hl[i]=i;
		else if(H(i)>H(Hl[i])) Hl[i]=i;
	} for(register int i=top;i;--i) {
		gr[i]=gr[i+1]; Gr[i]=Gr[i+1]; hr[i]=hr[i+1]; Hr[i]=Hr[i+1];
		if(G(i)>G(gr[i])) Gr[i]=gr[i],gr[i]=i;
		else if(G(i)>G(Gr[i])) Gr[i]=i;
		if(H(i)>H(hr[i])) Hr[i]=hr[i],hr[i]=i;
		else if(H(i)>H(Hr[i])) Hr[i]=i;
	}
}

inline void work() {
	if(gl[top]!=hl[top]) Ans=G(gl[top])+H(hl[top]); //预处理断边1->top
	else Ans=max(G(Gl[top])+H(hl[top]),G(gl[top])+H(Hl[top])); //最大与次大 
	for(register int i=1;i<top;++i) {
		ll opr1=pre[top]+H(hl[i])+G(gr[i+1]),opr2,opr3; //1在两边 2在左边 
		if(gl[i]!=hl[i]) opr2=G(gl[i])+H(hl[i]);
		else opr2=max(G(Gl[i])+H(hl[i]),G(gl[i])+H(Hl[i]));
		if(gr[i+1]!=hr[i+1]) opr3=G(gr[i+1])+H(hr[i+1]);
		else opr3=max(G(Gr[i+1])+H(hr[i+1]),G(gr[i+1])+H(Hr[i+1]));
		Ans=min(Ans,max(opr1,max(opr2,opr3)));
	}
}

int main() {
	for(register int i=n=read();i;--i) add_edge(read(),read(),read());
	get_cir(1,0); init(); work(); printf("%lld\n",max(Ans,ans));
	return 0;
}
```



---

## 作者：Gmt丶FFF (赞：1)

讲一个比较暴力的方法

题意：求减去基环树的环上一条边的直径最小值。

首先我们可以找出基环树上的每一个点，对于其子树求一遍直径，可以知道这些直径肯定不会发生改变，所以可以统计这些直径的最大值。

而对于环上的边，我们枚举删除的边，对于剩下的树求直径。

如果直接枚举复杂度为 $O(n^2)$，肯定无法承受。

我们可以对于环上的每一个点 $x$，可以记录 $f_x$ 为以 $x$ 开始对于其子树的最长链，我们再钦定一个环上的点 $y$ 为起点，然后记 $dis_x$ 为 $x$ 到 $y$ 的路径长度，由于要记顺时针逆时针两边的距离，所以我们可以复制一倍点来处理环的问题。

那么如果我们要求有环上的边的直径时，答案即为 $\max(f_x+f_y+\left| dis_x-dis_y\right|)(x\ne y)$。

那么我们就可以用 st 表维护区间 $f_x+dis_x$ 和 $f_x-dis_x$ 的最大值，然后对于枚举删除的那条边，利用石子合并的思想，设基环树上的点为 $num$，那么枚举区间 $\left[l,l+num\right]$，这样这个区间内的 $dis$ 只会由 $num-1$ 条边的权值转移过来，就会帮助我们删除一条边。

注意要处理两个最大值对应的点都是一样的情况，具体实现就是先找一个最大值，然后在其左边区间或右边区间找到另一个最大值。

由于用 st 表空间开销比较大，所以不能 dll。

时间复杂度： $O(n\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define ll long long
using namespace std;
const int N=4e5+5; 
int n,id[N],head,lg[N],cnt,num1[N][21],num2[N][21];
ll dis[N],st1[N][21],st2[N][21],f[N][2];
bool vis[N],huan[N];
struct node
{
	int to,data;
};
vector<node>a[N];
int dfs(int x,int fa)
{
	vis[x]=1;
	int len=a[x].size(),num=0;
	for(int i=0;i<len;i++)
	{
		if(a[x][i].to==fa)continue;
		if(vis[a[x][i].to])
		{
			if(!huan[a[x][i].to])huan[x]=1,num=a[x][i].to;	
			continue;
		}
		int lim=dfs(a[x][i].to,x);
		if(lim)num=lim;
	}
	if(num)huan[x]=1;
	if(num==x)return 0;
	return num;
}
inline void getnum(int x,ll y)
{
	f[x][1]=max(y,f[x][1]);
	if(f[x][1]>f[x][0])swap(f[x][1],f[x][0]);
}
void dfs2(int x,int fa)
{
	f[x][0]=f[x][1]=0;
	int len=a[x].size();
	for(int i=0;i<len;i++)
	{
		if(a[x][i].to==fa||huan[a[x][i].to])continue;
		dfs2(a[x][i].to,x);
		getnum(x,f[a[x][i].to][0]+a[x][i].data);
	}
}
void dfs3(int x,int fa,int num,ll sum)
{
	id[++cnt]=x;
	dis[cnt]=sum;
	int len=a[x].size();
	for(int i=0;i<len;i++)
	{
		if(a[x][i].to==fa||!huan[a[x][i].to])continue;
		if(a[x][i].to==num)
		{
			for(int j=cnt+1;j<=2*cnt;j++)id[j]=id[j-cnt],dis[j]=dis[cnt]+a[x][i].data+dis[j-cnt];
			return;
		}
		dfs3(a[x][i].to,x,num,sum+a[x][i].data);
		return;
	}
}
inline ll getans1(int l,int r)
{
	if(l>r)return 0;
	int num=lg[r-l+1];
	return max(st1[l][num],st1[r-(1<<num)+1][num]);
}
inline ll getans2(int l,int r)
{
	if(l>r)return 0;
	int num=lg[r-l+1];
	return max(st2[l][num],st2[r-(1<<num)+1][num]);
}
inline ll getans(int l,int r)
{
	int num=lg[r-l+1];
	ll ans=0;
	if(st1[l][num]>st1[r-(1<<num)+1][num])ans=getans1(l,r)+getans2(num1[l][num]+1,r);
	else ans=getans1(l,r)+getans2(num1[r-(1<<num)+1][num]+1,r);
	if(st2[l][num]>st2[r-(1<<num)+1][num])ans=max(ans,getans2(l,r)+getans1(l,num2[l][num]-1));
	else ans=max(ans,getans2(l,r)+getans1(l,num2[r-(1<<num)+1][num]-1));
	return ans;
}
int main()
{
//	freopen("data.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a[x].push_back({y,z});
		a[y].push_back({x,z}); 
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)if(huan[i])dfs2(i,0);
	for(int i=1;i<=n;i++)if(huan[i]){dfs3(i,0,i,0);break;}
	cnt*=2;
	for(int i=1;i<=cnt;i++)st1[i][0]=f[id[i]][0]-dis[i],st2[i][0]=f[id[i]][0]+dis[i],num1[i][0]=num2[i][0]=i;
	for(int i=1;i<=20;i++)
	{
		for(int j=1;j+(1<<i)-1<=cnt;j++)
		{
			if(st1[j][i-1]>st1[j+(1<<(i-1))][i-1])st1[j][i]=st1[j][i-1],num1[j][i]=num1[j][i-1];
			else st1[j][i]=st1[j+(1<<(i-1))][i-1],num1[j][i]=num1[j+(1<<(i-1))][i-1];
			if(st2[j][i-1]>st2[j+(1<<(i-1))][i-1])st2[j][i]=st2[j][i-1],num2[j][i]=num2[j][i-1];
			else st2[j][i]=st2[j+(1<<(i-1))][i-1],num2[j][i]=num2[j+(1<<(i-1))][i-1];
		}
	}
	ll ans=0,res=1e18;
	for(int i=1;i<=n;i++)ans=max(ans,f[i][0]+f[i][1]);
	for(int i=2;i<=cnt;i++)lg[i]=lg[i>>1]+1;
	for(int i=cnt/2;i<=cnt;i++)res=min(res,getans(i-cnt/2+1,i));
	printf("%lld",max(ans,res));
	return 0;
}
```


---

## 作者：Mirasycle (赞：0)

$n$ 个点 $n$ 条边所以是基环树，最重要的就是找到环对环进行处理。

找环可以用拓扑排序，最终度数为二的都是在环上的点。

分析题意可以发现，由于删掉一条边之后要保持联通，所以我们只能在环上去除一条边，最小化剩下的那颗树的直径即可。

首先以环上各点为根统计其子树内的直径还有最长链长。直接拿子树直径更新答案，并且用子树最长链长和其他子树拼凑出最大值即为直径。

这样就可以转化成环上问题了，也就是环上每一个点都有一个权值，环上两点之间的权值定义为距离 $+$ 两点权值。要求断开一条边，以最小化环上两点距离最大值。

考虑枚举断点，记录一下前/后缀最小值，和跨过 $1,n$ 位置可以拼接的最大最小值，即可对于每个断点 $O(1)$ 统计。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=2e5+10;
struct edge{
	int to,Next,w;
}edges[maxn<<1];
queue<int> q;
int head[maxn],deg[maxn],vis[maxn],n,tot=0;
long long l[maxn<<1],r[maxn<<1],l1[maxn<<1],r1[maxn<<1];
long long  f[maxn],a[maxn<<1],b[maxn<<1],ans=0,len=1e18;
void add(int u,int v,int w){
	edges[++tot]=(edge){v,head[u],w};
	head[u]=tot; ++deg[u];
}
void toposort(){
	for(int i=1;i<=n;i++)
		if(deg[i]==1) q.push(i);//叶子节点入队
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=head[u];i;i=edges[i].Next){
			int v=edges[i].to;
			if(deg[v]>1){
				ans=max(ans,f[u]+f[v]+edges[i].w);
				f[v]=max(f[v],f[u]+edges[i].w);
				if(--deg[v]==1) q.push(v);
			}
		}
	}
}
void Dp(int s){
	int m=0,y=s,k,z=0;
	do{
		a[++m]=f[y]; deg[y]=1;
		for(k=head[y];k;k=edges[k].Next){
			if(deg[edges[k].to]>1){
				b[m+1]=b[m]+edges[k].w;//前缀和 
				y=edges[k].to;
				break;
			}
		}
	}while(k);
	if(m==2){
		for(int i=head[y];i;i=edges[i].Next)
			if(edges[i].to=s) z=min(z,edges[i].w);
		len=max(len,f[s]+f[y]+z);
		return ;
	}
	for(int i=head[y];i;i=edges[i].Next)
		if(edges[i].to==s){
			b[m+1]=b[m]+edges[i].w;
			break;
		}
	long long pre; pre=l[0]=l1[0]=-1e18;
	for(int i=1;i<=m;i++){
		l1[i]=max(l1[i-1],a[i]+b[i]+pre);
		l[i]=max(l[i-1],a[i]+b[i]);
		pre=max(pre,a[i]-b[i]);
	}
	long long suf; suf=r[m+1]=r1[m+1]=-1e18;
	for(int i=m;i>=1;i--){
		r1[i]=max(r1[i+1],a[i]-b[i]+suf);
		r[i]=max(r[i+1],a[i]+b[m+1]-b[i]);
		suf=max(suf,a[i]+b[i]);
	}
	for(int i=1;i<=m;i++)
		len=min(len,max(l[i-1]+r[i],max(l1[i-1],r1[i])));
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w); add(v,u,w);
	}
	toposort();
	for(int i=1;i<=n;i++)
		if(deg[i]>1){ Dp(i); break; }
	cout<<max(ans,len);
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

基环树入门题。

考虑求出所有树边中的直径。他们是不能改变的。

然后考虑所有经过环上的直径。我们求出环上每个点引发的所有树边中最长链的长度，记做 $len_i$。

然后断环为链。考虑这时候环上两个点之间的距离是确定的。而环上两点间的点对只有三种情况：全部在删掉的这条边左边，全部在删掉的这条边右边，分别在两侧。

使用前缀和优化即可。

复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,vis[MAXN],fa[MAXN],in[MAXN],dep[MAXN],faw[MAXN]; 
vector<pair<int,pair<int,int>>> G[MAXN];
vector<pair<int,int>> cir;
int flg[MAXN],mxlen[MAXN],mxans[MAXN];
int tot,len[MAXN],id[MAXN],pre1[MAXN],pre2[MAXN],suf1[MAXN],suf2[MAXN],ans,res;
void dfs(int u,int f) {
	vis[u]=1,fa[u]=f,dep[u]=dep[f]+1;
	for(auto pr:G[u]) {
		int v=pr.first,w=pr.second.first,id=pr.second.second;
		if(id==in[u]) continue ;
		if(vis[v]) {
			if(dep[v]<dep[u]) {
				int pos=u;
				while(pos!=v) cir.push_back({pos,faw[pos]}),pos=fa[pos];
				cir.push_back({v,w});
			}
		}
		else faw[v]=w,in[v]=id,dfs(v,u);
	}
	return ;
}
void Dfs(int u,int f) {
	for(auto pr:G[u]) {
		int v=pr.first,w=pr.second.first,id=pr.second.second;
		if(v==f||flg[v]) continue;
		Dfs(v,u);
		mxans[u]=max({mxans[u],mxans[v],mxlen[u]+mxlen[v]+w});
		mxlen[u]=max(mxlen[u],mxlen[v]+w);	
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) {
		int u,v,w;
		cin>>u>>v>>w;	
		G[u].push_back({v,{w,i}}),G[v].push_back({u,{w,i}}); 
	}
	dfs(1,0);
	for(auto pr:cir) flg[pr.first]=1;
	for(auto pr:cir) Dfs(pr.first,0),ans=max(ans,mxans[pr.first]);
	int sum=0; res=LONG_LONG_MAX;
	for(auto pr:cir) id[++tot]=pr.first,len[tot+1]=len[tot]+pr.second,sum+=pr.second;
	int mx=-0x3f3f3f3f3f3f3f3f;
	pre1[0]=pre2[0]=suf1[tot+1]=suf2[tot+1]=mx;
	ffor(i,1,tot) pre1[i]=max(pre1[i-1],mx+len[i]+mxlen[id[i]]),mx=max(mx,mxlen[id[i]]-len[i]);
	ffor(i,1,tot) pre2[i]=max(pre2[i-1],mxlen[id[i]]+len[i]);
	mx=-0x3f3f3f3f3f3f3f3f;
	roff(i,tot,1) suf1[i]=max(suf1[i+1],mx-len[i]+mxlen[id[i]]),mx=max(mx,mxlen[id[i]]+len[i]);
	roff(i,tot,1) suf2[i]=max(suf2[i+1],mxlen[id[i]]+sum-len[i]);
	ffor(i,1,tot) res=min(res,max({ans,pre1[i],suf1[i+1],pre2[i]+suf2[i+1]}));
	cout<<res;
	return 0;
}
```

Bonus：[这一题](https://www.luogu.com.cn/problem/P1399) 只需要在这道题的基础上加一个除以 $2$ 即可。

---

## 作者：FLY_lai (赞：0)

此题解纪念我这一题一遍过。

[传送门](https://www.luogu.com.cn/problem/CF835F)

题意：给定基环树（带边权），问删掉一条边之后，直径最短是多少。

显然为了保证连通，我们只能删环上的边。

我们需要找出这个环：

```
struct Edge {
	int to;
	ll val;
	Edge(int t = 0, ll v = 0) {
		to = t;
		val = v;
	}
};
vector<Edge> e[N];

// 环上的一个点st，环上一共cnt个点，i号点在环上的上一个点为pre[i]，下一个nxt[i]，i->nxt[i]的边权是wei[i] 
int st, cnt = 0, pre[N], nxt[N], wei[N];

bool inCir[N] = {}; // inCir[i] = true表示i在环上

bool vis[N] = {}, flag = false; // vis[i]表示i访问过，flag表示找到了环
void srh(int x, int pr) {
	vis[x] = true;
	for (int i = 0; i < e[x].size() && !flag; i++)
		if (e[x][i].to != pr) {
			int v = e[x][i].to, tw = e[x][i].val;
			if (!vis[v])
				nxt[x] = v, wei[x] = tw, srh(v, x);
			else { // 若访问过，则说明找到了环
				nxt[x] = v, wei[x] = tw, pre[v] = x, st = v;
				flag = true;
				for (int i = st; true; i = nxt[i]) {
					cnt++, inCir[i] = true;
					if (nxt[i] == st)
						break;
				}
			}
		}
}
```

因为基环树可以看作是森林的根结点相连，我们可以把基环树的直径分成两种情况分别求：

1. 是某一棵树内部的直径；

2. 是两棵树组合得到的直径。

上面两种情况分别求出来，然后两种情况取 $\max$ 即可。

## 【某一棵树内部的直径】

既然已经找出了环，我们只需要遍历环上每一个点，求出对应的树里面的直径即可。

我用的是 DP 求。

```
ll dth[N] = {}, mxd[N] = {}, smxd[N] = {}; //深度，最长链，次长链 
ll dp_tree[N] = {}; //dp_tree[u]表示u的子树内的直径 
void dfs_tree(int x, int pr) {
//	cout << x << ' ' << pr << endl;
	for (auto i: e[x])
		if (i.to != pr && !inCir[i.to]) {
			dth[i.to] = dth[x] + i.val;
			dfs_tree(i.to, x);
			if (i.val + mxd[i.to] > mxd[x]) {
				smxd[x] = mxd[x];
				mxd[x] = i.val + mxd[i.to];
			}
			else if (i.val + mxd[i.to] > smxd[x])
				smxd[x] = i.val + mxd[i.to];
		}
	for (auto v: e[x]) {
		if (v.to != pr && !inCir[v.to])
			dp_tree[x] = max(dp_tree[x], dp_tree[v.to]);
	}
	dp_tree[x] = max(dp_tree[x], mxd[x] + smxd[x]);
}
```

这里不仅求了树内部的直径，同时还记录的最长链 $mxd$。这个最长链就是第二种情况要用到的。

## 【两棵树组合的直径】

如果枚举环上的点对，至少是 $O(n^2)$ 的，而且还要考虑删的边，无法接受。

我们转而考虑删了环上的哪条边，然后对所有删边的情况取 $\min$ 就是删边的最佳方案。（注意这里是 $\min$）

我们记整个环是 $c_1c_2\dots c_k$，环的边是 $c_ic_{i+1}(i<k)$ 和 $c_kc_1$。

1. 如果删的是 $c_ic_{i+1}(i<k)$。

	这种情况下的直径，能分成三种可能：
    
    1. 两棵树都属于 $c_1\sim c_i$ 中。
    
    	
    	我们考虑预处理出一个 $L[i]$：表示 $c_1\sim c_i$ 中任取两棵树，得到的路径最长是多少；$R[i]$ 类似表示 $c_i\sim c_k$ 中的答案。
    
        这里我们只考虑 $L[i]$ 怎么计算，这也是一个 DP。

        如果第 $i$ 棵树不选，$L[i]=L[i-1]$；

        如果第 $i$ 棵树选了，$L[i]=\displaystyle\max_{j=1}^{i-1}(mxd[i]+mxd[j]+dis(j,i))$。

        前一种情况简单，关注第二种。首先 $dis(j,i)$ 可以通过记录环上的边的前缀和 $s$，变成 $s[i-1]-s[j-1]$（这里 $-1$ 是因为我写的是 $s[i]$ 表示从 $1$ 走到 $i+1$）。

        这样式子就变成 $L[i]=\displaystyle\max_{j=1}^{i-1}(mxd[i]+mxd[j]+s[i-1]-s[j-1])=mxd[i]+s[i-1]+\displaystyle\max_{j=1}^{i-1}(mxd[j]-s[j-1]).$

        于是我们再预处理一个 $mxl[i]=\displaystyle\max_{j=1}^i(mxd[j]-s[j-1])$，可以简单递推得到。

        则 $L[i]=\max(L[i-1],mxd[i]+s[i-1]+mxl[i-1])$。
    
    2. 两棵树都属于 $c_{i+1}\sim c_k$ 中。
    
    	这种情况和上面类似。也预处理一个 $R[i],mxr[i]$。
    
    3. 一颗在 $c_1\sim c_i$，另一颗在 $c_{i+1}\sim c_k$。
        
    	对于这种情况，假设我们 $c_1\sim c_i$ 选了 $c_p$，则 $c_p$ 对直径的贡献是 $mxd[p]+s[p-1]$；同理 $c_{i+1}\sim c_k$ 中选了 $c_q$ 的贡献是 $mxd[q]+s[k-1]-s[q-1]$。
        
        $ans=\max(mxd[p]+s[p-1]+mxd[q]+s[k-1]-s[q-1]+w)$，其中 $w$ 是 $c_k\rightarrow c_1$ 的权值。
        
        于是 $ans=\max(mxd[p]+s[p-1]+mxd[q]-s[q-1])+s[k]$，我们再次预处理 $mxl2[i]=\max(mxd[i]+s[i-1]),mxr2[i]=\max(mxd[i]-s[i-1])$ 即可。
        
2. 删的是 $c_kc_1$，刚好可以用上面预处理的 $L[k]$ 直接得到。
        
这道题还是相当考验码力的，但是模块分得清楚也不是特别难写。（就是模块也太多了）

## 【Code】

```
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;

int n;
struct Edge {
	int to;
	ll val;
	Edge(int t = 0, ll v = 0) {
		to = t;
		val = v;
	}
};
vector<Edge> e[N];

// 环上的一个点st，环上一共cnt个点，i号点在环上的上一个点为pre[i]，下一个nxt[i]，i->nxt[i]的边权是wei[i] 
int st, cnt = 0, pre[N], nxt[N], wei[N];

bool inCir[N] = {}; // inCir[i] = true表示i在环上

bool vis[N] = {}, flag = false; // vis[i]表示i访问过，flag表示找到了环
void srh(int x, int pr) {
	vis[x] = true;
	for (int i = 0; i < e[x].size() && !flag; i++)
		if (e[x][i].to != pr) {
			int v = e[x][i].to, tw = e[x][i].val;
			if (!vis[v])
				nxt[x] = v, wei[x] = tw, srh(v, x);
			else { // 若访问过，则说明找到了环
				nxt[x] = v, wei[x] = tw, pre[v] = x, st = v;
				flag = true;
				for (int i = st; true; i = nxt[i]) {
					cnt++, inCir[i] = true;
					if (nxt[i] == st)
						break;
				}
			}
		}
}

ll dth[N] = {}, mxd[N] = {}, smxd[N] = {}; //深度，最长链，次长链 
ll dp_tree[N] = {}; //dp_tree[u]表示u的子树内的直径 
void dfs_tree(int x, int pr) {
//	cout << x << ' ' << pr << endl;
	for (auto i: e[x])
		if (i.to != pr && !inCir[i.to]) {
			dth[i.to] = dth[x] + i.val;
			dfs_tree(i.to, x);
			if (i.val + mxd[i.to] > mxd[x]) {
				smxd[x] = mxd[x];
				mxd[x] = i.val + mxd[i.to];
			}
			else if (i.val + mxd[i.to] > smxd[x])
				smxd[x] = i.val + mxd[i.to];
		}
	for (auto v: e[x]) {
		if (v.to != pr && !inCir[v.to])
			dp_tree[x] = max(dp_tree[x], dp_tree[v.to]);
	}
	dp_tree[x] = max(dp_tree[x], mxd[x] + smxd[x]);
}

ll ans, ans2; 

ll a[N], w[N];
ll s[N];
//s[i]=w[1]+...+w[i]


ll L[N], R[N], mxl[N], mxr[N];
ll mxl2[N], mxr2[N];

int main() {
	cin >> n;
	for (int i = 1, u, v, tw; i <= n; i++) {
		cin >> u >> v >> tw;
		e[u].push_back(Edge(v, tw));
		e[v].push_back(Edge(u, tw));
	}
	srh(1, 0);
	for (int i = st; ; i = nxt[i]) {
		dth[i] = mxd[i] = 0;
		dfs_tree(i, 0);
		ans = max(ans, dp_tree[i]);
		if (nxt[i] == st)
			break;
	}
	//此时，令a[i]=mxd[i]，要做环形 DP了
	for (int cc = 1, i = st; ; i = nxt[i], cc++) {
		a[cc] = mxd[i];
		w[cc] = wei[i]; //w[i]是从i->i+1 
		if (nxt[i] == st)
			break;
	}
	s[0] = 0;
	for (int i = 1; i <= cnt; i++)
		s[i] = s[i - 1] + w[i]; 
	//删除某条边，同时最小化 max(a[x]+a[y]+dist(x,y))
	/*
	1. 1~i = L[i] = max(L[i-1], j~i) = max(L[i-1], s[i-1]-s[j-1]+a[i]+a[j]) = max(L[i-1], max{a[j]-s[j-1]} + a[i]+s[i-1])
		令mxl[i] = max{a[i]-s[i-1]}，则 L[i]=max(L[i-1], mxl[i-1] + a[i] + s[i-1]) 
	
	2. i~n = R[i] = max(R[i+1], i~j) = max(R[i+1], a[i]+a[j]+s[j-1]-s[i-1]) = max(R[i+1], a[i]-s[i-1] + max{a[j]+s[j-1]})
		令mxr[i] = max{a[j]+s[j-1]}，则 R[i]=max(R[i+1], a[i] - s[i-1] + mxr[i+1]) 
	3. i~i+1 = max{a[i]+s[i-1] + a[j]-s[j-1]} + s[n]
		令 mxl2[i] = max{a[i]+s[i-1]}, mxr2[i]=max{a[j]-s[j-1]}
		则 i~i+1 = max{mxl2[i] + mxr2[i+1]} + s[cnt]
	*/
	
	L[0] = mxl[0] = mxl2[0] = ~0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= cnt; i++) {
		L[i] = max(L[i - 1], mxl[i - 1] + a[i] + s[i - 1]);
		mxl[i] = max(mxl[i - 1], a[i] - s[i - 1]);
	}
	
	R[cnt + 1] = mxr[cnt + 1] = mxr2[cnt + 1] = ~0x3f3f3f3f3f3f3f3f;
	for (int i = cnt; i >= 1; i--) {
		R[i] = max(R[i + 1], a[i] - s[i - 1] + mxr[i + 1]);
		mxr[i] = max(mxr[i + 1], a[i] + s[i - 1]);
	}
	
	for (int i = 1; i <= cnt; i++)
		mxl2[i] = max(mxl2[i - 1], a[i] + s[i - 1]);
	for (int i = cnt; i >= 1; i--)
		mxr2[i] = max(mxr2[i + 1], a[i] - s[i - 1]);
	
	ans2 = 0x3f3f3f3f3f3f3f3f;
	
//	for (int i = st; ; i = nxt[i]) {
//		cout << wei[i] << ' ';
//		if (nxt[i] == st)
//			break;
//	}
//	puts("");
//	for (int i = 1; i <= cnt; i++)
//		cout << mxl2[i] << ' ';
//	puts("");
//	for (int i = 1; i <= cnt; i++)
//		cout << mxr2[i] << ' ';
//	puts("");
	ans2 = min(ans2, L[cnt]);
	for (int i = 1; i < cnt; i++) { //枚举删的是 i-i+1
		ans2 = min(ans2, max(max(L[i], R[i + 1]), mxl2[i] + mxr2[i + 1] + s[cnt]));
	}
//	puts("");
	cout << max(ans, ans2) << endl;
	return 0;
}
```
    
    
    
    
    .
    
    

---

## 作者：_Vix_ (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF835F)

## 分析

求基环树断掉环上一条边之后的最小直径。

根据经典套路，分类讨论不经过环的直径和经过环的直径。

对于不经过经过环的直径，则是环上一点的子树的直径，因为即使删掉一条边也对子树内没有影响。

对于经过环的直径，那么答案的构成应该是环上两点间的最短距离加上两点的最长链。这里运用环上问题的经典 trick：破环成链。然后记录以下信息：$f_u$ 表示点 $u$ 的最长链，$s_u$ 表示到 $u$ 的前缀距离和。两点 $u$，$v$ 的答案就是：$f_u + f_v + s_u - s_v$，分别维护 $f_u+s_u$ 和 $f_u-s_u$ 的最大值就好了。

注意到有可能最大值会有 $u=v$ 的情况，将其中一个改为次大值就好了，代码里是使用堆维护的。

## 注意
破环成链数组一定要开两倍

## Code
```cpp
#include <bits/stdc++.h>
#define gc getchar
#define ll long long
#define il inline
using namespace std;

inline int read() {
	int x = 0; bool flag = 0; char ch = gc();
	for (;!isdigit(ch); ch = gc()) flag |= ch == '-';
	for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return flag ? ~(x - 1) : x;
}

const int N = 4e5 + 10;
int h[N], e[N], ne[N], w[N], idx;
int fa[N], dfn[N], tsp;
int tmp[N], cnt, val[N];
ll d[N], len, sum[N], dp[N];
int n;
bool inc[N];

struct cmp1 {
	int operator() (int x, int y) {
		return dp[x] - sum[x] < dp[y] - sum[y];
	}
};
struct cmp2 {
	int operator() (int x, int y) {
		return dp[x] + sum[x] < dp[y] + sum[y];
	}
};
priority_queue<int, vector<int>, cmp1> q1;
priority_queue<int, vector<int>, cmp2> q2;

il void add(int u, int v, int c) {
	e[idx] = v, w[idx] = c, ne[idx] = h[u], h[u] = idx++;
}

void find_cir(int u) {
	dfn[u] = ++tsp;
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (v == fa[u]) continue;
		if (dfn[v]) {
			if (dfn[v] < dfn[u]) continue;
			for (int x = v; x != fa[u]; x = fa[x]) {
				cnt++, tmp[cnt] = x, sum[cnt + 1] = sum[cnt] + val[x];
				inc[x] = true;
			}
			sum[cnt + 1] = sum[cnt] + w[i];
		} else fa[v] = u, val[v] = w[i], find_cir(v);
	}
}

void dfs(int u, int fa) {
	for (int i = h[u]; ~i; i = ne[i]) {
		int v = e[i];
		if (inc[v] || v == fa) continue;
		dfs(v, u);
		len = max(len, d[u] + d[v] + w[i]);
		d[u] = max(d[u], d[v] + w[i]);
	}
}

il ll solve() {
	ll ans_tre = 0, ans_cir = 2e18;
	for (int i = 1; i <= cnt; i++) {
		len = 0;
		dfs(tmp[i], 0);
		ans_tre = max(ans_tre, len);
		dp[i] = dp[i + cnt] = d[tmp[i]];
		sum[i + cnt + 1] = sum[i + cnt] + sum[i + 1] - sum[i];
	}
	for (int i = 1; i <= cnt; i++) q1.push(i), q2.push(i);
	for (int i = 1; i <= cnt; i++) {
		while (q1.top() < i && q1.size() > 1) q1.pop();
		while (q2.top() < i && q2.size() > 1) q2.pop();
		int x = q1.top(), y = q2.top();
		if (x == y) {
			q1.pop(); q2.pop();
			while (q1.top() < i && q1.size() > 1) q1.pop();
			while (q2.top() < i && q2.size() > 1) q2.pop();
			int tx = q1.top(), ty = q2.top();
			ans_cir = min(ans_cir, max(dp[x] - sum[x] + dp[ty] + sum[ty], dp[tx] - sum[tx] + dp[y] + sum[y]));
			q1.push(x); q2.push(y);
		} else ans_cir = min(ans_cir, dp[x] - sum[x] + dp[y] + sum[y]);
		q1.push(i + cnt); q2.push(i + cnt);
	}
	return max(ans_tre, ans_cir);
}

int main() {
	memset(h, -1, sizeof h);
	n = read();
	for (int i = 1, u, v, c; i <= n; i++) {
		u = read(), v = read(), c = read();
		add(u, v, c); add(v, u, c);
	}
	find_cir(1);
	cout << solve();
	return 0;
}
```


---

## 作者：xfrvq (赞：0)

从基环树上断一条边且保持联通，只能断环上的边。

直径的情况讨论为 `不经过环` 和 `经过环` 两种。前者对每个子树跑一边树形 $\tt dp$ 求求。

对于后者，考虑记下基环树的所有点 $p_1,\cdots,p_k$，**每个点的子树内的最大深度 $w_i$**，答案就是

$$\max\{w_{p_i}+w_{p_j}+\mathtt{dis(p_i,p_j)}\}$$

断环为二倍长度的链，$\tt dis$ 有：

$$\mathtt{dis}(p_i,p_j)=\mathtt{dis}(p_i,p_{i+1})+\cdots\mathtt{dis}(p_{j-1},p_j)$$

于是我们不妨记 $s_i=\mathtt{dis}(p_1,p_2)+\cdots+\mathtt{dis}(p_{i-1},p_i)$，$\mathtt{dis}(p_i,p_j)=s_j-s_i$。

于是我们将原式拆成 $w_{p_i}+w_{p_j}+s_j-s_i$，答案是 $[1,k],[2,k+1],\cdots,[k+1,2k]$ 等滑动窗口里上述式子的最小值。

滑动窗口直接扫，过程中两个 `set`，里面装 $\{w_{p_i}+s_i\}$ 以及 $\{w_{p_i}-s_i\}$，单次直径询问就会是两个 `set` 最大值之和。

本来需要特殊判断提出的两个位置是否满足一个大小关系。但是你仔细想想会发现如果答案是 $(i,j)$，取 $w_{p_i}+s_i+w_{p_j}-s_j$ 会更小。

但是这里还没有判 $i=j$ 的情况。这个需要在 `set` 每个节点多维护一个 `id`，如果两个最大值 `id` 相等考虑使用次大值。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 4e5 + 5;

int n,p[N * 2],cnt;
vector<pair<int,int>> G[N];
multiset<pair<ll,int>> s1,s2;
bool vis[N],cir[N],flg;
int stk[N],wei[N],tp;
ll f[N],s[N];
ll res = 9e18,ans = 0;

void dfs0(int u,int ft,ll w){
	if(flg) return; 
	if(vis[u]){
		flg = 1,cnt = 1,p[cnt] = u,s[cnt] = w,cir[u] = true;
		do{
			++cnt,p[cnt] = stk[tp],s[cnt] = wei[tp];
			cir[stk[tp]] = true; --tp;
		} while(stk[tp] != u);
	}
	if(flg) return; 
	vis[u] = true;
	++tp,stk[tp] = u,wei[tp] = w;
	for(auto[v,w] : G[u]) if(v != ft) dfs0(v,u,w);
	--tp;
}

void dfs1(int u,int ft){
	for(auto[v,w] : G[u]) if(!cir[v] && v != ft){
		dfs1(v,u);
		ans = max(ans,f[u] + f[v] + w);
		f[u] = max(f[u],f[v] + w);
	}
}

int main(){
	scanf("%d",&n);
	for(int i = 1,u,v,w;i <= n;++i){
		scanf("%d%d%d",&u,&v,&w);
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
	}
	dfs0(1,0,0);
	for(int i = 1;i <= cnt;++i) dfs1(p[i],0),p[i + cnt] = p[i],s[i + cnt] = s[i];
	for(int i = 1;i <= 2 * cnt + 1;++i) s[i] += s[i - 1];
	for(int i = 2 * cnt + 1;i >= 1;--i) s[i] = s[i - 1];
	for(int i = 1;i < cnt;++i)
		s1.insert({f[p[i]] + s[i],i}),
		s2.insert({f[p[i]] - s[i],i});
	for(int i = 1,j = cnt;i <= cnt + 1;++i,++j){
		s1.insert({f[p[j]] + s[j],j}),
		s2.insert({f[p[j]] - s[j],j});
		auto[u1,i1] = *rbegin(s1); auto[u2,i2] = *++rbegin(s1);
		auto[v1,j1] = *rbegin(s2); auto[v2,j2] = *++rbegin(s2);
		if(i1 != j1) res = min(res,u1 + v1);
		else res = min(res,max(u1 + v2,u2 + v1));
		s1.erase({f[p[i]] + s[i],i});
		s2.erase({f[p[i]] - s[i],i});
	}
	printf("%lld\n",max(res,ans));
	return 0;
}
```

---

