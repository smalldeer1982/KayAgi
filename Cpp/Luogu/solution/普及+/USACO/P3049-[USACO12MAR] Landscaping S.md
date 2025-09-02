# [USACO12MAR] Landscaping S

## 题目背景

*本题与 [2016 年公开赛白金组同名题目](/problem/P2748) 在题意上一致，唯一的差别是数据范围。*

## 题目描述

Farmer John 打算修建一座花园，他需要移动不少泥土。

花园由 $N$ 个花坛组成（$1 \leq N \leq 100$），其中花坛 $i$ 包含 $A_i$ 单位的泥土。FJ 希望花坛 $i$ 包含 $B_i$ 单位的泥土，保证 $0 \leq A_i,B_i \leq 10$。

为了达到这个目标，他可以做这几件事情：

- 购买一单位的泥土，放在指定的花坛中，费用为 $X$。
- 从任意一个花坛中移走一单位泥土，费用为 $Y$。
- 从花坛 $i$ 运送一单位泥土到花坛 $j$，费用为 $Z|i-j|$。

请你帮 FJ 计算移动泥土的最小开销。

## 说明/提示

按下面的方案，最小花费为 $210$，可以证明不存在开销更小的方案。

- 移除 $4$ 号花坛的一单位泥土，花费 $200$。
- 将 $4$ 号花坛的三单位泥土移到 $1$ 号花坛，花费 $3 \times 3=9$。
- 将 $3$ 号花坛的一单位泥土移到 $2$ 号花坛，花费 $1 \times 1=1$。

## 样例 #1

### 输入

```
4 100 200 1 
1 4 
2 3 
3 2 
4 0 
```

### 输出

```
210 
```

# 题解

## 作者：Erutsiom (赞：22)

网校的讲法+蒟蒻本兔自己的理解qwq

入门dp第三天看到这个题非常懵x

今天终于看懂了激动得来发篇题解！！！

把输入的初始数组和目标数组转化成如下格式：

a 2 3 4 5

a'1 1 2 2 2 3 3 3 3 4 4 4 4 4

b 3 1 5 2

b'1 1 1 2 3 3 3 3 3 4 4

这样思路就很清晰的，想必大家都能明白（~~除了我~~


------------


```cpp
#include<bits/stdc++.h>//3049
using namespace std;
int n,x,y,z,a[1010],b[1010],f[1010][1010],p,q;
int minx(int a,int b,int c)
{
	if(a<=b &&a<=c)return a;
	if(b<=a &&b<=c)return b;
	if(c<=a &&c<=b)return c;
}

int main()
{
	int la=1,lb=1;
	cin>>n>>x>>y>>z;
	for(int i=1;i<=n;i++){
	cin>>p>>q;
	for(int j=1;j<=p;j++)a[la++]=i;
	for(int k=1;k<=q;k++)b[lb++]=i;
	}
	f[0][0]=0;
	//极限情况作为边界 
	for(int i=1;i<=la;i++)f[i][0]=i*y;//目标为空数组 
	for(int i=1;i<=lb;i++)f[0][i]=i*x;//原数组为空 
	
	for(int i=1;i<=la;i++){
	  for(int j=1;j<=lb;j++){
	  	f[i][j]=minx(f[i-1][j]+y,f[i][j-1]+x,f[i-1][j-1]+z*abs(a[i]-b[j]));
	  }
	  }
	cout<<f[la][lb]<<endl;
	return 0;
}






```

---

## 作者：daniEl_lElE (赞：15)

这题难度根本没有蓝题这么难，恶意评分QwQ！

只是思路难想。

首先，这题可能有贪心思想。可本蒟蒻想不出来QwQ！

俗话说，贪心不行就DP，DP不行就暴力。~~貌似不是俗话，而是本蒟蒻编的一句口诀。~~

那么，这题DP有几种思路。

# $1.DP_{i}$思路

具体指$DP_{i}$为修改到第i盆花所需要的费用。

但明显，我们可以从后方转移泥土，所以一维DP不可以QwQ。

# $2.DP_{i,j}$思路

## 状态设计

首先，我们假设$a$数组是$1，4，2，7$，我们可以将它改成$a'$数组：

$1，2，2，2，2，3，3，4，4，4，4，4，4，4$

相当于一种奇葩的离散化。

$b$数组也同样。

$DP_{i,j}$指由前$a'_{i}$变道前$b'_{j}$需要多少费用。

## 状态转移

先设定边界条件：$DP_{0,j}=j * X;DP_{1,0}=i * Y$。

后推方程：$DP_{i,j}=min(DP_{i,j-1}+X,DP_{i-1,j}+Y,DP_{i-1,j-1}+Z * abs(a_{i}-b_{j})$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[1005],b[1005],an,bn;
int c[1005][1005],X,Y,Z;
signed main(){
	int n;
	cin>>n>>X>>Y>>Z;
	for(int i=1;i<=n;i++){
		int j;
		cin>>j;
		while(j>0){
			a[++an]=i;
			j--;
		}
		cin>>j;
		while(j>0){
			b[++bn]=i;
			j--;
		}
	}
	for(int j=0;j<=bn;j++){
		c[0][j]=j*X;
	}
	for(int i=0;i<=an;i++){
		c[i][0]=i*Y;
	}
	for(int i=1;i<=an;i++){
		for(int j=1;j<=bn;j++){
			c[i][j]=i*Y+j*X;
			c[i][j]=min(c[i][j],c[i][j-1]+X);
			c[i][j]=min(c[i][j],c[i-1][j]+Y);
			c[i][j]=min(c[i][j],c[i-1][j-1]+Z*llabs(a[i]-b[j]));
		}
	}
	cout<<c[an][bn];
	return 0;
}
```

---

## 作者：EDqwq (赞：6)

### 前言：

这道题的dp做法，分明是很妙，很有趣的，但是遗憾的是题解区并没有一篇讲清楚这个做法的题解，所以我就补上这么一篇题解吧。

***

乍一看题目，我们可能会想到一种状态：设 $dp_i$ 为 $a$ 数组中前 $i$ 个数变成了$b$ 数组中的前 $i$ 个数需要的最小花费。

显然，这种一个一个操作的状态是不可行的，到了一个位置之后，不一定不使用前面操作完成的数，或者说是后面的数可能达不到最小花费。

观察数据范围： $a_i,b_i \leq 10$ 可以想到一种很舒适的处理方法：把每一个数拆分。

我们按照顺序把每一个 $a_i$ 拆成 $a_i$ 个 $i$ ，$b_i$ 同理，这样我们就把这个问题转化为了：

现在有两个数组，你要通过三种操作把第一个数组变成第二个。

1. 增加任意一个数，花费 $x$ 。

1. 删除任意一个数，花费 $y$ 。

1. 把一个数 $a_i$ 变成 $a_j$ ，花费 $z \times abs(a_i - a_j)$ 。

可以设计出一个状态： $dp_{i,j}$ 表示把 $a$ 数组的前 $i$ 项变得和 $b$ 数组的前 $j$ 项完全一样的最小花费。

有状态转移方程：

$dp_{ij} = \min(dp_{i,j},dp_{i,j - 1} + x,dp_{i - 1,j} + y,dp_{i - 1,j - 1} + abs(a_i - b_j) \times z)$

这里就来到了一个比较难想的地方：我们的第三个操作是把一个数变成另一个数，那为什么这不会影响到后面算到那个数的时候的结果呢？

因为我们这个数组处理后是从小到大，这个 $b_j$ 一定在后面，我们算到后面的时候，已经包括了这里，也就是换过来的这里，我们不在乎顺序，所以答案根本不影响。相当于现在我们用这些钱，暂时满足我们 $dp_{i,j}$ 的要求。

到此，这道题的dp做法就讲清楚了，时间复杂度和空间复杂度皆为 $O(n^2)$ ，虽然无法通过强化版，但是这个做法却值得一学。

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int N;
int n,m,x,y,z;
int aa[1000010];
int bb[1000010];
int a[1000010];
int b[1000010];
int dp[1010][1010];

signed main(){
	mem(dp,0x3f);
	dp[0][0] = 0;
	cin>>N>>x>>y>>z;
	for(int i = 1;i <= N;i ++)aa[i] = read(),bb[i] = read();
	for(int i = 1;i <= N;i ++){
		for(int j = 1;j <= aa[i];j ++)a[++ n] = i;
		for(int j = 1;j <= bb[i];j ++)b[++ m] = i;
	}
	for(int i = 1;i <= n;i ++)dp[i][0] = y * i;
	for(int i = 1;i <= m;i ++)dp[0][i] = x * i;
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			dp[i][j] = min(dp[i][j],min(dp[i][j - 1] + x,min(dp[i - 1][j] + y,dp[i - 1][j - 1] + abs(a[i] - b[j]) * z)));
		}
	}
	cout<<dp[n][m];
	return 0;
}
```

---

## 作者：Usada_Pekora (赞：4)

题意：给出数组 $a$，每次可以花费 $x$ 让一个数减去 $1$ ，花费 $y$ 让一个数加上 $1$，或者花费 $ z\left|i-j\right| $ 让 $a_i$ 减去 $1$ ，$a_j$ 加上 $1$ 。求让 $u$ 变成 $v$ 的最小花费。

如果我们扫到一个 $i$ ，且前面没有其他数可以操作，那就只能给它加上/减去了。如果后面遇到一个 $j$ ，且加减是和 $i$ 相反的，那就有了多种选择了: 继续给 $j$ 补上，花费 $x$ 或 $y$  ;  把前面的某一个 $i$ 给换过来（只换多余的部分），花费 $ z \left| i-j \right| - cost_i$ ，$cost_i$ 是 $i$ 已经的多余部分花费过的价值， 注意， 以上的操作建立在 $\left| u - v\right| = 1$ 的前提上， 也就是值的相差只有一的情况，那么运用时直接调用 $\left|u - v \right| $ 次就好了 。

$ z\left | i - j \right| - cost_i = zj - zi - v = zj - (zi + cost_i)$  把 $zj+cost_i$ 扔进大根堆， 每次减去最大。就可以确保这一步加上去的最小了。


```cpp
#include <iostream>
#include <queue>
#include <cmath>
#define int long long
using namespace std;
priority_queue<int> q[2];
int c[2], n, z, ans;
signed main() {
	ios::sync_with_stdio(false);
	cin >> n >> c[1] >> c[0] >> z;
	for (int i = 1, a, b, f; i <= n; i++) {
		cin >> a >> b;
		if (a == b) continue;
		f = a > b; //加上或减去
		for (int j = 1; j <= abs(a - b); j++) 
        if (q[f ^ 1].empty() || i * z - q[f ^ 1].top() > c[f ^ 1]) ans += c[f ^ 1], q[f].push(i * z + c[f ^ 1]);
            else ans += i * z - q[f ^ 1].top(), q[f].push(i * z + i * z - q[f ^ 1].top()), q[f ^ 1].pop();
    }
    cout << ans;
    return 0;
}
```


---

## 作者：pldzy (赞：4)

~~又是一道考试题~~

 _对一排泥土进行三种操作，使其变为目标状态，求最小花费代价。_ 
 
 ~~请原谅我接下来奇怪的量词......~~

## 思路

 1. 大致方法： 

	很明显，求代价，就是用 dp 。但是，你会发现直接去推动态转移方程是很难的，所以，**我们选择把泥土“量化”**。
    
 2. “量化泥土”：

	我们把泥土按量进行排列，例如：
    
    原数组是：1 2 3 4 ；
    
    转移后是：1 2 2 3 3 3 4 4 4 4 。
    
    这样一来， 我们就可以去处理 dp 数组 $f$ 了。
    
 3. 初始化 dp 数组：

	我们定义 $f[i][j]$ 表示用 $i$ 个泥土构造 $j$ 个泥土。
    
    那么就需要初始化 $f[0][j]$ 以及 $f[i][0]$ 两者。~~（这里并不难所以我就不多强调了）~~
    
4. 动态转移方程

	最后，我们不难得出动态转移方程 ~~（如果已经想出来的大佬就可以不用看了）~~，具体推导过程如下：
    
   要得到 $f[i][j]$ ,我们有三种方式推得: $f[i-1][j] , f[i][j-1] , f[i-1][j-1]$ 。
   
   1. 从 $f[i-1][j]$ 推得：只需要在已满足的该状态下花费 $y$ 费用多移过来一份泥土即可。
   
   2. 从 $f[i][j-1]$ 推得：在已满足状态下花费 $x$ 费用多移走一份泥土即可。
   
   3. 从 $f[i-1][j-1]$ 推得：在已满足状态下花费 $z*(a[i]-b[i])$ 费用把一份泥土转移即可。
   
   综上！！！我们终于推出完整的动态转移方程为 ~~（我终于敲完了）~~：
   
   $f[i][j] = \min (f[i - 1][j] + y, f[i][j - 1] + x, f[i - 1][j - 1] + z * abs (a[i] - b[j]))$ 。
   
   

------------
差不多就是这些啦，更多细节请见代码。

$Code$
```cpp
#include<bits/stdc++.h> 
using namespace std;

int n, x, y, z;
const int maxn = 1005;
int a[maxn], b[maxn];
int f[maxn][maxn];
int numa, numb;//cal nums of a and b

inline int minn (int a, int b, int c)
{
	return min (a, min (b, c));
}

int main()
{
	scanf ("%d %d %d %d", &n, &x, &y, &z);
	numa = 1;
	numb = 1;
	for (int i = 1; i <= n; i++)
	{
		int aa, bb;
		scanf ("%d %d", &aa, &bb);
		for (int j = 1; j <= aa; j++) a[numa++] = i;
		for (int l = 1; l <= bb; l++) b[numb++] = i;
	}
	for (int i = 1; i <= numa; i++) f[i][0] = i * y;
	for (int i = 1; i <= numb; i++) f[0][i] = i * x;
	for (int i = 1; i <= numa; i++)
	{
		for (int j = 1; j <= numb; j++)
		{
			f[i][j] = minn (f[i - 1][j] + y, f[i][j - 1] + x, f[i - 1][j - 1] + z * abs (a[i] - b[j]));
		}
	}
	printf ("%d\n", f[numa][numb]);
	return 0;
}
```
若有排版，写法错误，麻烦管理员指出斧正，感激不尽！

若文章中有问题，请大佬们指出，谢谢！


---

## 作者：离散小波变换° (赞：4)

## 题目大意

有$n$个花坛，编号为$1,2\dots n$。现在第$i$个花坛有$A_i$单位土壤，需要通过以下操作将它变成$B_i$单位的土壤。

- 按照单价$X$元购买土壤。

- 花费每单位$Y$元移走土壤。

- 向$j$花坛运送土壤，每单位$Z\times|i-j|$元。

求最小的总花费。

## 题解

$\qquad$上面既然给出了贪心和$dp$的解法，这里就给一个非常容易理解的网络流费用流方法吧。

$\qquad$为了控制第$i$个花坛拥有$B_i$单位土壤，我们可以将它向汇点$T$连一条边，容量为$B_i$，费用为$0$，这样满流之后就能保证每个花坛恰好有$B_i$单位土壤。节点之间传递土壤非常简单：对于点$i$，向$i-1,i+1$分别连接容量为$+\infty$，费用为$Z$的边。如何购买土壤？我们只需要从源点向每个花坛连出容量为$+\infty$，费用为$X$的边。也就是说，如果某个花坛想要多获得一份土地，他就需要多花费$X$元。

$\qquad$同时我们要从源点$S$向每个点连接一条边来处理初始情况（即每个花坛里有$A_i$的土壤）。但是要注意的是，由于我们初始时**必须**给每个点$A_i$的土壤，因此$S$向每个点连的边边权应该是$-Y$，同时我们要给结果加上$A_i\times Y$。如何理解？我们可以认为如果点$i$想要退回$1$单位的土壤，他就必须花费$Y$元；此时我们已经给他们垫付了$A_i\times Y$，因此结果需要加上$A_i\times Y$。

## 参考代码

```
#include<bits/stdc++.h>
#define pLi pair<LL,int>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
const int MAXN =1e5+3,MAXM=3e5+3;
class graph{
	public:
	LL n,m,s,t,ans; bool vis[MAXN],inq[MAXN];
	LL head[MAXN],nxt[MAXM*2],ver[MAXM*2],val[MAXM*2];
	LL tot,flw[MAXM*2],deg[MAXN],ufw[MAXN];
	graph():s(1),n(0),tot(1){
		memset(dep ,0,sizeof(dep ));
		memset(vis ,9,sizeof(vis ));
		memset(head,0,sizeof(head));
		memset(nxt ,0,sizeof(nxt ));
		memset(ver ,0,sizeof(ver ));
		memset(flw ,0,sizeof(flw ));
		memset(h   ,0,sizeof(h   ));
		memset(id  ,0,sizeof(id  ));
	}
	void _add(int u,int v,LL f,LL w){
		ver[++tot]=v,flw[tot]=f,val[tot]=w,
		nxt[tot]=head[u],head[u]=tot;
	}
	void add(int u,int v,LL f,LL w){
		deg[u]++,_add(u,v,f,w),_add(v,u,0,-w);
	}
	LL dep[MAXN],h[MAXN],id[MAXN];
};
bool dijstra(graph &g){
	priority_queue<pLi,vector<pLi >,greater<pLi > > pq;
	while(!pq.empty()) pq.pop(); int flg=INF;
	up(1,g.n,i) g.dep[i]=g.ufw[i]=INF,g.vis[i]=false;
	pq.push(make_pair(0ll,g.s)); while(!pq.empty()){
		pLi x=pq.top(); pq.pop();
		LL u=x.second,w=x.first,hu=g.h[u];
		if(g.vis[u]||w>flg) continue; g.vis[u]=true,g.dep[u]=w;
        if(u==g.t) flg=w;
		for(int i=g.head[u];i;i=g.nxt[i]){
			LL v=g.ver[i],hv=g.h[v],lmt=min(g.ufw[u],g.flw[i]);
			if(!g.vis[v]&&lmt&&g.dep[v]>g.dep[u]+g.val[i]+hu-hv){
				g.dep[v]=g.dep[u]+g.val[i]+hu-hv; 
				g.ufw[v]=lmt,g.id[v]=i;
				pq.push(make_pair(g.dep[v],v));
			}
		}
	}
	return g.dep[g.t]!=INF;
}
void SPFA(graph &g){
	up(1,g.n,i) g.inq[i]=false,g.dep[i]=INF;
	queue <int> q; q.push(g.s),g.inq[g.s]=true,g.dep[g.s]=0;
	while(!q.empty()){
		int u=q.front(); q.pop(),g.inq[u]=false; 
		for(int i=g.head[u];i;i=g.nxt[i]){
			int v=g.ver[i]; if(g.flw[i]&&g.dep[v]>g.dep[u]+g.val[i]){
				g.dep[v]=g.dep[u]+g.val[i];
				if(!g.inq[v]) q.push(v),g.inq[v]=true;
			}
		}
	}
	memcpy(g.h,g.dep,sizeof(g.h));
}
LL ans=0,cst=0;
void MCMA(graph &g){
	SPFA(g);
	while(dijstra(g)){
		LL mxflw=g.ufw[g.t],mncst=mxflw*(g.dep[g.t]-g.h[g.s]+g.h[g.t]);
		ans+=mxflw,cst+=mncst; for(int i=g.t;i!=g.s;i=g.ver[g.id[i]^1])
		g.flw[g.id[i]]-=mxflw,g.flw[g.id[i]^1]+=mxflw;
		up(1,g.n,i) g.h[i]+=g.dep[i];
	}
}
struct graph G;
int tp,x,y,z,a,b,num,ID[MAXN],sum;
int main(){
    num=qread(),x=qread(),y=qread(),z=qread();
    int s=++tp,t=++tp; up(1,num,i) ID[i]=++tp;
    up(1,num,i) {
        a=qread(),b=qread(),sum+=a*y;
        G.add(s,ID[i],a,-y),G.add(ID[i],t,b,0);
        G.add(s,ID[i],INF,x);
    }
    G.n=tp; G.s=s,G.t=t;
    up(1,num-1,i) G.add(ID[i],ID[i+1],INF,z),G.add(ID[i+1],ID[i],INF,z);
    MCMA(G);
    printf("%d\n",cst+sum);
    return 0;
}
```

**注**：因为是网络流费用流算法，所以过不掉加强版数据……

---

## 作者：lytqwq (赞：3)


因为$A_i,B_i$很小，我们把每单位泥土分开看。

对于**每单位**泥土在第$i$个位置上，设处理该**单位**泥土花费$Vi$费用：


$V_i:$

1. 如果是少了泥土，可以花费$X$费用来解决，所以$V_i=X$，还可以向前面要泥土，要泥土一定向之前多泥土的地方要，要花费$Z|i-j|$费用，但之前的泥土我们已经考虑了它的贡献了，所以之前的泥土的贡献就要再减去（即之前的那个泥土多了，但是不需要处理了，后面少了的那个泥土直接要过来了），总的费用为$Z|i-j|-V_j$，所以$V_i=\min(X,Z|i-j|-V_j)$

1. 如果是多了泥土，可以花费$Y$费用来解决，所以$V_i=Y$。还可以往前面送泥土，送泥土一点向之前少泥土的地方送。同理，总的费用为$Z|i-j|-V_j$，所以$V_i=\min(Y,Z|i-j|-V_j)$

拆开$V_i$的计算：

$V_i=\min(X,Z|i-j|-V_j)\space(i>j)$

$=\min(X,iZ-jZ-V_j)\space(i>j)$

$=\min(X,iZ+(-jZ-V_j))\space(i>j)$

所以，$V_i$的计算和前面的$j$有关的只有$(-jZ-V_j)$，要让当前的$V_i$最小，我们需要让$(-jZ-V_j)$最小。

为什么我们需要让$V_i$最小呢？为什么不把这个$j$留给后面的$V$呢？
 
前面的$(-jZ-V_j)$肯定是向后找最近的最好啊，越往后拖，$i$越大，$V_i$就有可能被$X$决定，还有可能出现距离更近的来更新。
 


开两个小根堆，一个存本来少了泥土的单位泥土的$(-jZ-V_j)$，可以用来更新现在多了泥土的地方。

另一个存本来多了泥土的单位泥土的$(-jZ-V_j)$，可以用来更新现在少了泥土的地方。

得到处理当前泥土的费用后把$(-iZ-V_i)$存进堆里，供后面的答案更新。



可以理解为后悔的贪心，把前面的费用给减去。
 
时间复杂度：$O(10nlog(10n))$

~~（然后你就可以水掉双倍经验P2748了）~~

 
代码如下：
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
const long long int N=100001;
long long int n,a[N],b[N],x,y,z;
long long int V[N];
long long int ans;
priority_queue<long long int,vector<long long int>,greater<long long int> > ovo,ovo2;
int main(){
	scanf("%lld%lld%lld%lld",&n,&x,&y,&z);
	for(long long int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i],&b[i]);
		for(long long int o=1;o<=a[i]-b[i];o++){
			V[i]=y;
			if(!ovo.empty()){
				V[i]=min(V[i],i*z+ovo.top());
				ovo.pop();
			}
			ovo2.push(-V[i]-i*z);
			ans+=V[i];
		}
		for(long long int o=1;o<=b[i]-a[i];o++){
			V[i]=x;
			if(!ovo2.empty()){
				V[i]=min(V[i],i*z+ovo2.top());
				ovo2.pop();
			}
			ovo.push(-V[i]-i*z);
			ans+=V[i];
		}
	}
	printf("%lld\n",ans);
}

```







---

## 作者：Starrydream (赞：2)

## 题解

这是一道好神的贪心啊。（dp好像也能做），D1T2难度偏上，有概率D1T3。

看到那个10其实应该想到拆成一件一件的，然而还是没有想到。

之后的堆贪心倒不是非常的难，只不过想出前缀和的形式压进堆然后取出来和当前元素做差还是有些难度。

我们来分析一波。

假设当前是土少了，要加上或从别的地方运。

从别的地方运上一份土，我们应该运一份最优的（显然由于运输费用给定都相同，且前后路长差与代价线性）。

假设没有，我们只能买一份。

这就是这道题的大致思路。它为什么正确呢？

~~考虑到当前我们没有选择最优的决策，后面选择的决策并不会因此更优，没了，不会严格证明~~

~~显然的无后效性和最优子结构~~

由于每份土地不能重复用（当然你可以动态调整不断地运，注意费用即可），因此用堆维护。

用堆维护什么值呢？
$$
dis * z + x
$$
为什么是这个奇奇怪怪的东西呢？主要是考虑一种标准，使得取出的元素能快速和当前元素合并价值。

显然从前面取土是
$$
(dis_x - dis_{now}) * z - x
$$
这样上面维护的那个元素形式就不是很难理解了吧（虽然有点难想？）

Code:

```c++
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <queue>
#define maxn 100005
int n , x , y , z , ans;
std::priority_queue<int> q1 , q2;
int main()
{
	scanf("%d%d%d%d",&n,&x,&y,&z);
	int fr , to;
	for(int k = 1 ; k <= n ; ++k){
		scanf("%d%d",&fr,&to);
		if(fr < to){
			for(int i = 1 ; i <= to - fr ; ++i){
				if(q1.empty() || k * z - q1.top() > x){
					ans += x;
					q2.push(k * z + x);
				}
				else{
					int g = q1.top();
					ans += k * z - g;
					q1.pop();
					q2.push(k * z + k * z - g);
				}
			}
		}
		else {
			for(int i = 1 ; i <= fr - to ; ++i){
				if(q2.empty() || k * z - q2.top() > y){
					ans += y;
					q1.push(k * z + y);
				}
				else {
					int g = q2.top();
					ans += k * z - g;
					q2.pop();
					q1.push(k * z + k * z - g);
				}
			}
		}
	}
	printf("%d",ans);
}
```

---

## 作者：巨型方块 (赞：2)

这道题的思路啦，其实还好啦；

但是自己想的时候跟傻逼一样；

还好又fop\_zz给我讲了半天；

做这道题目啦，先去做一下洛谷的一题“种树”

这道题目啦

最本质的思路，就是先计算当前最优答案，加入总答案，然后在之后的计算里，来更新之前所谓的“最优答案”

比如我们现在在i缺一

那我们花费x的钱补一

之后我们在j多一颗土

那么我们假如这个土移到i

那当前的答案是不是(j-i)\*z-x

当然我们也可以直接运走费用y

那额当前最优解就是min(（j-i）\*z-x,y)

之后我们枚举到k又缺了土

假如从j移动到k

那么答案是不是(k-j)\*z-min(（j-i）\*z-x,y)

当然这个还要和x取一个min


那我们来观察从i移到j的转移

(j-i)\*z-x

=jz-iz-x

=jz-(iz+x)

这里的iz其实和j是没有什么关系的

这里的x就是在i的时候的最优解

那么我们是不是在j的时候对之前所有缺土的点取一个max(iz+x)就是当前最优解了

这个是不是一个堆就可以完成了？

所以我们维护2个堆，一个是多余，一个数不足

那么我们算出当前的最优解的时候，把答案放到另一个堆里面，假如现在的最优解并不是最终答案，那么就可以通过这个堆体现出来，并且在后面的“当前最优解”里面减去这个错误的最优解，最终保持当前的正确答案



```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const Ll N=1e5+5;
Ll n,x,y,ans,m1,m2,z;
priority_queue<Ll>Q1;
priority_queue<Ll>Q2;
int main()
{
    scanf("%lld%lld%lld%lld",&n,&x,&y,&z);
    for(Ll j=1;j<=n;j++){
        scanf("%lld%lld",&m1,&m2);
        if(m1<m2)
            for(Ll i=1;i<=m2-m1;i++)
                if(Q1.empty()||j*z-Q1.top()>=x){
                    ans+=x;Q2.push(x+j*z);
                }else{
                    Ll v=Q1.top();Q1.pop();
                    ans+=j*z-v;Q2.push(j*z*2-v);
                }
        else
            for(Ll i=1;i<=m1-m2;i++)
                if(Q2.empty()||j*z-Q2.top()>=y){
                    ans+=y;Q1.push(y+j*z);
                }else{
                    Ll v=Q2.top();Q2.pop();
                    ans+=j*z-v;Q1.push(j*z*2-v);
                }
    }
    printf("%lld",ans);
}
```

---

## 作者：pldzy (赞：0)

### 题目概述

给出一数组的初始状态及目标状态，有三种改变的方式，求最小代价。


------------


### 算法思路

1. 首先，看到题目要求的最小代价（~~还有数据范围~~）就可以推出要用 $dp$ 。

1. 但很显然，状态很难定义，**因为使某一堆符合条件可能会导致其他堆的初始状态改变**，所以我们尝试用二维 $dp$ 。


------------


### 推导状态转移方程

- 我们~~很容易~~能想到，用 $f[i][j]$ 表示用原先的前 $i$ 堆使前 $j$ 堆满足最后的要求，不过这很麻烦，所以，我们有了另一种定义。

- 我们可以把初始状态和目标状态进行特殊的离散化。例子如下。

	假定初始状态为：$1$ $2$ $3$ $4$，

	我们用数组 $a$ 存下它：$1$ $2$ $2$ $3$ $3$ $3$ $4$ $4$ $4$ $4$ 。

- 很明显，这样方便了许多。我们直接把泥土拆分成一个一个的，这样， $f[i][j]$ 就变成了用原先的前 $i$ 个单位泥土使最后的前 $j$ 个单位的泥土符合条件。

	（说人话： $f[i][j]$ 表示用 $i$ 个泥土去构造出 $j$ 个泥土。）

- 最后，我们不难得出状态转移方程 $f[i][j] = min(f[i-1][j]+y,f[i][j-1]+x,f[i-1][j-1]+z*abs(a[i]-b[j]))$


------------


### $Code$
```cpp
#include<bits/stdc++.h> 
using namespace std;

int n, x, y, z;
const int maxn = 1005;
int a[maxn], b[maxn];
int f[maxn][maxn];
int t1, t2;
int la, lb;

int main()
{
	cin >> n >> x >> y >> z;
	la = lb = 1;
	for (int i = 1; i <= n; i++)
	{
		cin >> t1 >> t2;
		for (int j = 1; j <= t1; j++) a[la++] = i;
		for (int l = 1; l <= t2; l++) b[lb++] = i;
	}
	f[0][0] = 0;
	for (int i = 1; i <= la; i++) f[i][0] = i * y;
	for (int i = 1; i <= lb; i++) f[0][i] = i * x;
	for (int i = 1; i <= la; i++)
	{
		for (int j = 1; j <= lb; j++)
		{
			f[i][j] = min (f[i - 1][j] + y, min (f[i][j - 1] + x, f[i - 1][j - 1] + z * abs (a[i] - b[j])));
		}
	}
	cout << f[la][lb] << endl;
	return 0;
}
```

若本题解有错误，麻烦您给本蒟蒻指出，谢谢。

---

## 作者：mango09 (赞：0)

[Link](https://www.luogu.com.cn/problem/P3049)

考试的 B 题。

不难想到 DP。（然鹅我没想到 qwq）

我们先将数组进行一个神奇的处理，以样例为例：

$a={1,2,3,4}\to a'={1,2,2,3,3,3,4,4,4,4}$

$b={4,3,2,0}\to b'={1,1,1,1,2,2,2,3,3}$

这时就变成了我们熟悉的“编辑字符距离”的问题。[P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)

状态转移方程：

```dp[i][j] = min(min(dp[i][j - 1] + x, dp[i - 1][j] + y), dp[i - 1][j - 1] + z * abs(a[i] - b[j]))```

记得设边界条件。

$\text{Code}$

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 1e3 + 5;

int n, x, y, z, lena, lenb;
int a[MAXN], b[MAXN], dp[MAXN][MAXN];

int main()
{
	scanf("%d%d%d%d", &n, &x, &y, &z);
	for (int i = 1; i <= n; i++)
	{
		int c, d;
		scanf("%d%d", &c, &d);
		for (int j = 1; j <= c; j++) //预处理
		{
			a[++lena] = i;
		}
		for (int j = 1; j <= d; j++)
		{
			b[++lenb] = i;
		}
	}
	for (int i = 1; i <= lena; i++) //边界条件
	{
		dp[i][0] = y * i;
	}
	for (int i = 1; i <= lenb; i++)
	{
		dp[0][i] = x * i;
	}
	for (int i = 1; i <= lena; i++)
	{
		for (int j = 1; j <= lenb; j++)
		{
			dp[i][j] = min(min(dp[i][j - 1] + x, dp[i - 1][j] + y), dp[i - 1][j - 1] + z * abs(a[i] - b[j]));
		}
	}
	printf("%d", dp[lena][lenb]);
	return 0;
}
```


---

## 作者：__233 (赞：0)

# [更好的阅读体验](https://blog.csdn.net/Zbr162/article/details/93410608)

<font size="6"> [$$园林绿化$$](https://www.luogu.org/problemnew/show/P3049) </font>
___
<font size="6" color=blue> $\mathcal{Description}$ </font>
有n块土地，每块有A[i]泥土，现把其改造成B[i]泥土，有3种操作：
(1)花费X向任意土地增加1泥土；
(2)花费Y向任意土地减少1泥土；
(3)花费Z*|i-j|把土地i的1泥土运到土地j。问最小花费是多少。

$A[i],B[i]<=100,\\n<=100,\\X,Y,Z<=1000$
___

<font size="6" color=o123vverwatc> $\mathcal{Solution_1}$ </font><br/>

<font color=blue size="5"> $最初想法$ </font>
思考发现, 最开始土地分为两种类型 : **要求降低**, **要求升高**.
在两个不同类型的土地 $i,j$ 之间, 若 $X+Y>Z*|i-j|$ 时, 则将泥土从 $i$ 搬往 $j$ 一定优于 直接升高降低.
于是按照此方法 **贪心**, 得到 $50pts$.
___
<font color=red size="5"> $正解部分$ </font>
大概思想如上, 是因为我维护方法不对才拿了 $50pts$, 重点看实现部分.
___
<font color=red size="5"> $实现部分$ </font>
对两种类型的土地分别建立两个 **大根堆** $Q_1,\ Q_2$, 内部元素是 **单位泥土**, 
(可以理解为 $Q_1$ 是囤积的泥土, 可以堆到其他土地上; $Q_2$ 是筐, 可以将其他土地上的泥土倒到对应土地上),

**从左往右边扫**, 设当前位置为 $i$, 土地类型为 **要求下降**, 即可以将当前泥土堆到其他土地上.
将该地泥土分为 $A[i]$ 个单位泥土, 对每个单位泥土 **单独处理**,

对当前 **要升高** 的单位泥土, 有两种选择: 
1. 直接扔泥土, $cost=X$, 此时需要 $Q_1.push(i*Z + X)$ 
2. 从前方不同类型的土地 **搬泥土**, $cost_2 = i*Z-Q_2.top.first$,
3. 从后方不同类型的土地 **搬泥土**,此时需要$\ Q_2.push(i*Z+cost_2)$

注意以上都需执行 $Ans += min(cost,cost_2)$., (弹出操作已省略).

时间复杂度 $O(N*10*log(N*10))$
<font size="6" color=o123vverwatc> $\mathcal{Solution_2}$ </font><br/>

可以使用 $Dp$,
设 $F[i, j]$ 表示 处理了 $i$ 个第一类型的**单位泥土**, $j$ 个第二类型的**单位泥土** 所花费的最小价值,

$F[i, j]=
min\begin{cases}
F[i-1, j] + X\\
F[i, j-1] + Y\\
F[i-1,j-1]+Z*∣pos_i-pos_j∣
\end{cases}$

时间复杂度  $O((N*10)^2)$
___

<font size="6" color=Black> $\mathcal{Code}$ </font>
贪心代码.

```cpp
#include<bits/stdc++.h>
#define reg register

const int maxn = 105;
const int inf = 0x7f7f7f7f;

int N;
int X;
int Y;
int Z;
int Ans;
int A[maxn];
int B[maxn];

std::priority_queue <int> Q1;
std::priority_queue <int> Q2;

void Work_1(int i){  // In, Up
        int cost = inf;
        if(!Q1.empty()){
                int t = Q1.top();
                int tmp = i*Z - t;
                if(tmp < X) Q1.pop(), cost = tmp, Q2.push(i*Z+tmp);
        }
        if(cost == inf) cost = X, Q2.push(i*Z+X);
        Ans += cost;
}

void Work_2(int i){ // Out, Down
        int cost = inf;
        if(!Q2.empty()){
                int t = Q2.top();
                int tmp = i*Z - t;
                if(tmp < Y) Q2.pop(), cost = tmp, Q1.push(i*Z+tmp);
        }
        if(cost == inf) cost = Y, Q1.push(i*Z+Y);
        Ans += cost;
}

int main(){
        scanf("%d%d%d%d", &N, &X, &Y, &Z);
        for(reg int i = 1; i <= N; i ++) scanf("%d%d", &A[i], &B[i]);
        for(reg int i = 1; i <= N; i ++)
                for(reg int j = 1; j <= abs(B[i]-A[i]); j ++)
                        if(A[i] < B[i]) Work_1(i); 
                        else Work_2(i);
        printf("%d\n", Ans);
        return 0;
}

```


---

