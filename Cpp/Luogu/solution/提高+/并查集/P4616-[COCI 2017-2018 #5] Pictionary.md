# [COCI 2017/2018 #5] Pictionary

## 题目描述

在宇宙一个不为人知的地方，有一个星球，上面有一个国家，只有数学家居住。
在这个国家有$n$个数学家，有趣的是，每个数学家都住在自己的城市，且城市间无道路相连，因为他们可以在线交流。当然，城市有从$1$到$n$的编号。

一位数学家决定用手机发论文，而手机将“不言而喻”自动更正成了“猜谜游戏”。
不久之后，这个国家就发现了猜谜游戏。他们想要见面一起玩，于是这个国家就开始了修路工程。
道路修建会持续$m$天。对于第$i$天，若$\gcd(a,b)=m-i+1$，则$a$和$b$城市间会修一条路。

由于数学家们忙于建筑工作，请你来确定一对数学家最早什么时候能凑到一起玩。

## 说明/提示

对于$40\%$的数据：
$n≤4000,q≤10^5$  
对于全部数据：  
$1≤n,q≤10^5$  
$1≤m≤n$

样例1解释：
在第一天，$(3,6)$之间修了一条路，因此第二次询问输出`1`  
在第二天，$(2,4),(2,6),(2,8),(4,6),(6,8)$之间都修了一条路，此时$4$和$8$号城市连通，第三次询问输出`2`  
在第三天，所有编号互质的城市之间都修了路，$2$和$5$号城市在此时连通，第一次询问输出`1`

样例2解释：
在第二天，$(20,15)$之间修了一条路  
第四天，$(15,9)$之间修了一条路  
所以$20$和$9$号城市在第四天连通，输出`4`

## 样例 #1

### 输入

```
8 3 3
2 5
3 6
4 8```

### 输出

```
3
1
2```

## 样例 #2

### 输入

```
25 6 1
20 9```

### 输出

```
4```

## 样例 #3

### 输入

```
9999 2222 2
1025 2405
3154 8949```

### 输出

```
1980
2160```

# 题解

## 作者：Leap_Frog (赞：13)

### PS.
看了一下题解区，发现大多数题解都用树剖做的，但是我感觉根本不用树剖啊。。。用LCA就够了。  
此题其实没有紫色的qwq，个人感觉蓝~绿差不多了。

### Problem.
有$n$座城市。  
有$m$个时刻，在第$i$个时刻，所有$m-i+1$的倍数之间连边。  
有$q$个询问，询问第$x_i$座城市和$y_i$座城市什么时候联通。  

### Solution.
感觉这题根本不用树剖，而且一般dfs也就能搞定了。  
但是看题解区，基本上全都用树剖的。  
所以贡献一发LCA的题解。  

首先我们可以考虑如何把这棵树建出来。  
每一个时刻，**显然**可以直接考虑第$m-i+1$座城市和所有$m-i+1$的倍数连边。  
这两张图是等价的。（在只需要判断联通性的情况下  
那么就可以直接这样暴力枚举，然后用一个并查集记录两个点是否在同一个集合里。  
暴力枚举的复杂度是$\frac{N}{1}+\frac{N}{2}+...+\frac{N}{N}$的，所以复杂度是$O(N\times log_N)$的

这棵树建出来了，我们可以给这棵树附上权值。  
每条边的边权就是当前的时刻，从小到大加边。  
然后直接查两个点之间的路径上的瓶颈就好了。  
这个贪心**显然**是对的，笔者不证。  

然后，这棵树**显然**是一棵无根数。  
那么如何转化成一个有根数呢？  
方法很简单，直接钦定1为根就好了。  

然后这棵树建出来之后，接下来也没有修改操作。  
我就很想不通为什么楼上楼下都要用树剖做。  
这不是很**显然**一个lca的问题吗，真是令人谔谔。  
我相信，想来做这题的应该都会ST表求LCA了吧。  
笔者在这里也就不赘述方法了，如果不懂可以看代码注释。  

笔者不才，倍增用的st表，压行在这一行代码中也没有很体现。  
完结撒花，无耻求赞。  

### Coding.
```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{int to,wei,nxt;}e[200005];//边的结构体
int n,m,q,tot,head[100005],fa[100005],dep[100005],f[100005][35],dis[100005][35];
inline int getf(int x) {return fa[x]==x?x:fa[x]=getf(fa[x]);}//并查集找父亲
inline void adde(int x,int y,int w) {e[++tot]=(edge){y,w,head[x]},head[x]=tot;}//加边
inline void ready() {for(int i=m;i>=1;i--) for(int j=i+i,u=getf(i),v=getf(j);j<=n;j+=i,u=getf(i),v=getf(j)) if(u!=v) fa[u]=v,adde(i,j,m-i+1),adde(j,i,m-i+1);}//建树，直接暴力枚举
inline void dfs(int x,int fa=0,int val=0)
{//求出倍增数组，由于这题是边权，所以还需要一个val表示之前的边。
	f[x][0]=fa,dis[x][0]=val,dep[x]=dep[fa]+1;//f是father，dis是向上跳的最小值，dep是深度
	for(int i=1;(1<<i)<=dep[x];i++) f[x][i]=f[f[x][i-1]][i-1],dis[x][i]=max(dis[x][i-1],dis[f[x][i-1]][i-1]);//倍增处理
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) dfs(e[i].to,x,e[i].wei);//继续dfs
}
inline int lca(int x,int y)
{//求x到y的距离，lca模板
	int ans=0;if(dep[x]<dep[y]) swap(x,y);
	for(int i=25;i>=0;i--) if(dep[x]-(1<<i)>=dep[y]) ans=max(ans,dis[x][i]),x=f[x][i];
	if(x==y) return ans;
	for(int i=25;i>=0;i--) if(f[x][i]!=f[y][i]) ans=max(ans,max(dis[x][i],dis[y][i])),x=f[x][i],y=f[y][i];
	return max(ans,max(dis[x][0],dis[y][0]));
}
int main()
{
	for(int i=1;i<=100000;i++) fa[i]=i;//并查集初始化
	scanf("%d%d%d",&n,&m,&q),dep[0]=0,memset(dis,0x3f,sizeof(dis)),ready(),dfs(1);//一大堆初始化
	for(int x,y;q--;) scanf("%d%d",&x,&y),printf("%d\n",lca(x,y));//处理询问
	return 0;//完结撒花
}
```

---

## 作者：Captain_Paul (赞：8)

题意：$n$个点，一开始没有边，第$i$天在$gcd(a,b)=m-i+1$的两点之间连边，共$m$天。多组询问$x,y$最早在第几天连通



------------

发现第$i$天只需从$m-i+1$向它的倍数连边

这样两个以$m-i+1$为$gcd$的点也会相连

用并查集维护，再建立重构树，每次询问找到重构树上的瓶颈即可

~~比较裸的题但为什么就是想不出来！！！~~

如果你在$2018.11.10$之前看到了这篇题解

祝$NOIP2018$　$rp++$

```
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#define reg register
using namespace std;
const int N=2e5+5;
struct node
{
	int to,nxt;
}edge[N*20];
int n,m,num,head[N],cnt,f[N],tot[N],dep[N];
int tim,idx[N],top[N],fa[N],son[N],w[N];
inline int read()
{
	int x=0,w=1;
	char c=getchar();
	while (!isdigit(c)&&c!='-') c=getchar();
	if (c=='-') c=getchar(),w=-1;
	while (isdigit(c))
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*w;
}
inline void add_edge(int from,int to)
{
	edge[++num]=(node){to,head[from]}; head[from]=num;
	edge[++num]=(node){from,head[to]}; head[to]=num;
}
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void dfs(int k,int father,int deep)
{
	int bigson=0;
	fa[k]=father; dep[k]=deep; tot[k]=1;
	for (reg int i=head[k];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if (v==father) continue;
		dfs(v,k,deep+1); tot[k]+=tot[v];
		if (bigson<tot[v]) bigson=tot[v],son[k]=v;
	}
}
void dfs(int k,int tp)
{
	idx[k]=++tim; top[k]=tp;
	if (!son[k]) return; dfs(son[k],tp);
	for (reg int i=head[k];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if (!idx[v]) dfs(v,v);
	}
}
inline int getlca(int x,int y)
{
	while (top[x]!=top[y])
	{
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
int main()
{
	n=cnt=read(),m=read();
	for (reg int i=1;i<=(n<<1);i++) f[i]=i;
	for (reg int i=m;i;i--)
	{
		for (reg int j=(i<<1);j<=n;j+=i)
		{
			int u=find(i),v=find(j);
			if (u==v) continue;
			w[f[u]=f[v]=++cnt]=m-i+1;
			add_edge(u,cnt); add_edge(v,cnt);
		}
	}
	dfs(cnt,0,1); dfs(cnt,cnt);
	for (reg int T=read();T;T--) printf("%d\n",w[getlca(read(),read())]);
	return 0;
}
```

---

## 作者：decoqwq (赞：4)

题目需要一种支持合并一些点集的数据结构，显然是并查集，我们考虑对每个时间都合并一次点集，显然复杂度为$O(nlogn)$

然后每个点记录的是他和他父亲合并时的时间戳，那么显然，在查询两个点$(x,y)$的联通时间时，就是$x$到$lca(x,y)$的最大值加上$lca(x,y)$到$y$的最大值，注意不能包含$lca(x,y)$，因为这个点存储的时间是和另外一个点集的合并时间

然后往上跳就行，因为不能路径压缩，我们采用启发式合并
```cpp
/*deco loves Chino*/
#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n,m,q;
int f[100010],siz[100010],t[100010],app[100010],dep[100010],maxn[100010]; 
vector<int> vc[100010];
int find(int x)
{
	if(x==f[x])
	{
		return x;
	}
	return find(f[x]);
}
void dfs(int u)
{
	for(int i=0;i<vc[u].size();i++)
	{
		int v=vc[u][i];
		dep[v]=dep[u]+1;
		dfs(v);
	}
}
int main()
{
	//freopen("pictionary.in","r",stdin);
	//freopen("pictionary.out","w",stdout);
	cin>>n>>m>>q;
	int rt;
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		siz[i]=0;
	}
	for(int i=m;i>=1;i--)
	{
		for(int j=(i<<1);j<=n;j+=i)
		{
			int nt=(m-i+1);
			int dx=find(i),dy=find(j);
			if(dx==dy)
			{
				continue;
			}
			if(siz[dx]<siz[dy])
			{
				swap(dx,dy);
			}
			f[dy]=dx;
			vc[dx].push_back(dy);
			rt=dx;
			if(siz[dx]==siz[dy])
			{
				++siz[dx];
			}
			t[dy]=nt;
		}
	}
	dfs(rt);
	for(int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int ans=0;
		if(dep[x]<dep[y])
		{
			swap(x,y);
		}
		while(dep[x]>dep[y])
		{
			ans=max(ans,t[x]);
			x=f[x];
		}
		while(x!=y)
		{
			ans=max(max(t[x],t[y]),ans);
			x=f[x],y=f[y];
		}
		cout<<ans<<"\n";
	}
}
```

---

## 作者：Little09 (赞：3)

每一个时刻，题目要求我们把 $\gcd(a,b)=m-i+1$ 的 $a$ 与 $b$ 之间连边，我们可以想到把 $m-i+1$ 与它的倍数连边。不难发现，在只考虑连通性的情况下两张图等价。

给第 $i$ 天连的边赋权值 $i$，题目转换成查询两点 $x,y$，找到图上一条两点之间的路径使得路径上的最大值最小。

稍微一想，这不就是 [P1967 [NOIP2013 提高组] 货车运输](https://www.luogu.com.cn/problem/P1967) 吗？（很好奇为什么题解里没有人提出这一点）一个小区别就是这两个题目一个是最大值最小，一个是最小值最大。

原题做法是用 kruskal 先求出最大（这题里是最小）生成树，然后再树上倍增类似 LCA 地维护最值。在本题中同样适用也可以通过。注意到本题连边的过程已经排好序，所以省去了 kruskal 的排序过程。

与 [P1967 [NOIP2013 提高组] 货车运输](https://www.luogu.com.cn/problem/P1967) 长得几乎一样的代码，仅供参考：


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,p;
const int N=200005;
int fax[N];

struct edge
{
	int x,y,z;
}e[N*52];
int find(int x)
{
	if (fax[x]==x) return x;
	return fax[x]=find(fax[x]);
}
int h[N],nxt[N],v[N],t[N],cnt;
int fa[N][22],w[N][22],deth[N],used[N];
void add(int x,int y,int z)
{
	t[++cnt]=y;
	v[cnt]=z;
	nxt[cnt]=h[x];
	h[x]=cnt;
}
void dfs(int x,int f)
{
	fa[x][0]=f,used[x]=1;
	for (int i=1;i<=20;i++)
	{
		fa[x][i]=fa[fa[x][i-1]][i-1];
		w[x][i]=max(w[x][i-1],w[fa[x][i-1]][i-1]);
	}
	for (int i=h[x];i;i=nxt[i])
	{
		if (t[i]!=f) 
		{
			w[t[i]][0]=v[i];
			deth[t[i]]=deth[x]+1;
			dfs(t[i],x);
		}
	}
}
int LCA(int x,int y)
{
	if (find(x)!=find(y)) return -1;
	if (deth[x]<deth[y]) swap(x,y);
	int res=0;
	for (int i=20;i>=0;i--) 
	{
		if (deth[fa[x][i]]>=deth[y]) 
		{
			res=max(res,w[x][i]);
			x=fa[x][i];

		}
	}
    if (x==y) return res;
    for (int i=20;i>=0;i--)
    {
    	if (fa[x][i]!=fa[y][i]) 
    	{
    		res=max(res,w[x][i]);
    		res=max(res,w[y][i]);
    		x=fa[x][i],y=fa[y][i];
    	}
    }
    res=max(res,max(w[x][0],w[y][0]));
    return res;
}

inline int read()
{
    int F=1,ANS=0;
	char C=getchar();
    while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
    while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
    return F*ANS;
}
int main()
{
	n=read(),p=read();
	for (int i=1;i<=n;i++) fax[i]=i;
	for (int i=p;i>=1;i--)
	{
		for (int j=2;i*j<=n;j++)
		{
			++m;
			e[m].x=i,e[m].y=i*j,e[m].z=p-i+1;
			int x1=find(e[m].x),y1=find(e[m].y);
			if (x1==y1) continue;
			fax[x1]=y1;
			add(e[m].x,e[m].y,e[m].z),add(e[m].y,e[m].x,e[m].z);
		}
	}
	for (int i=1;i<=n;i++)
	{
		if (used[i]==0) 
		{
			fa[i][0]=i;
			w[i][0]=0;
			dfs(i,i);
		}
	}
	int q=read();
	while (q--)
	{
		int x=read(),y=read();
		cout << LCA(x,y) << endl;
	}
	return 0;
}
```


---

## 作者：木木！ (赞：3)

没想出来用边权表示天数做到 $\Theta((n+q)\log n)$，提供一个 $\Theta(n\log^2 n\times \alpha(n)+q\log n\times\alpha(n))$ 的离线做法。

首先维护连通性可以想到并查集。对于某个天数 $i$，连边 $\gcd(a,b)=m-i+1$ 的点，容易发现只需要连 $k(m-i+1)\leftrightarrow (k-1)(m-i+1)$ 即可保证连通性。

那么，对于第 $i$ 天，连的总边数即为 $O(\frac n{m-i+1})$。对于某一段天数 $[1,k]$ 来说，连的总边数为：

$$
\sum_{i=k}^m \frac{n}{i}\leq\sum_{i=1}^n=\Theta(n\log n)
$$

利用并查集，一趟连续天数的联通性维护可以保证在 $\Theta(n\log n\times \alpha(n))$ 的时间复杂度内，其中 $\alpha(n)$ 为反阿克曼函数。

由此可以想到一个整体二分的做法，先将询问离线下来然后每一趟查询每个询问的连通性。每一趟时间复杂度为 $\Theta(n\log n\times \alpha(n)+q\times \alpha(n))$，总共需要做 $\Theta(\log n)$ 趟，最终时间复杂度即为 $\Theta(n\log^2 n\times \alpha(n)+q\log n\times \alpha(n))$。

最终最大的点约 300ms。

附 AC 代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int getint()
{
	char ch;
	while((ch=getchar()) < '!') ;
	int x = ch^'0';
	while((ch=getchar()) > '!') x = (x*10)+(ch^'0');
	return x;
}

void putint(int x)
{
	if(x/10) putint(x/10);
	putchar((x%10)^'0');
}

int st[100005];
int rnk[100005];

void init(int n)
{
	for(int i=1; i<=n; ++i)
	{
		st[i] = i;
		rnk[i] = 0;
	}
}

int getfa(int x) { return x==st[x] ? x : st[x]=getfa(st[x]); }

void unio(int fa,int fb)
{
	if(rnk[fa] == rnk[fb])
	{
		st[fb] = fa;
		++rnk[fa];
	}
	else if(rnk[fa] > rnk[fb])
	{
		st[fb] = fa;
	}
	else
	{
		st[fa] = fb;
	}
}

struct query
{
	int a,b;
	int ansi;
	int qury;
	int id;
};

query qi[100005];

bool pmc(query a,query b) { return a.id < b.id; }

int main()
{
	int n = getint();
	int m = getint();
	int q = getint();
	for(int i=1; i<=q; ++i)
	{
		qi[i].a = getint();
		qi[i].b = getint();
	}
	
	int logn = 31-__builtin_clz(n);
	for(int i=1; i<=q; ++i)
	{
		qi[i].qury = 1<<logn;
		qi[i].id = i;
	}
	for(int i=logn-1; i>=-1; --i)
	{
		init(n);
		int tim = 1;
		for(int j=1; j<=q; ++j)
		{
			int r = j;
			while(qi[r+1].qury==qi[j].qury || (qi[j].qury>=m&&qi[r+1].qury>=m)) ++r;
			while(tim<=qi[j].qury && tim<=m)
			{
				int gcd = m-tim+1;
				for(int d=gcd; d<=n-gcd; d+=gcd)
				{
					int fa = getfa(d);
					int fb = getfa(d+gcd);
					if(fa != fb) unio(fa,fb);
				}
				++tim;
			}
			int cr = r;
			for(int c=j; c<=cr; ++c)
			{
				if(getfa(qi[c].a) == getfa(qi[c].b))
				{
					qi[c].ansi = tim-1;
					qi[c].qury -= 1<<i;
				}
				else
				{
					qi[c].qury += 1<<i;
					swap(qi[c],qi[cr]);
					--c; --cr;
				}
			}
			j = r;
		}
	}
	
	sort(qi+1,qi+1+q,pmc);
	
	for(int i=1; i<=q; ++i)
	{
		putint(qi[i].ansi);
		putchar('\n');
	}
}
```

---

## 作者：Suzt_ilymtics (赞：2)

## 写在前面

首先祝大家CSP rp++！

这道题本来是想练习树剖来，结果发现用LCA做更简单，于是又能~~水紫题了~~

## 正文

### 简述题意：

输入三个整数n, m, q, 分别表示城市数量，修路持续天数，询问数量

对于第i天，若gcd(a,b) = m - i +１，则a 和b 城市间会修一条路

q个询问，每次问a，b两个城市最早联通的时间


------------
### Solution

题目中说gcd(a,b) = m - i +１的意思是第i天时，编号为m-i+1的倍数的城市之间会修一条路（a，b肯定都有m-i+1作为因子）

所以我们以这条信息为依据来建树，把时间设做边权

直接暴力枚举所有符合条件的边，复杂度在Peal_Frog的上题解有证明

用并查集来避免出现环的情况

然后就是倍增求LCA的板子了

虽然这是棵无根树，但令1为根就可以处理

预处理出两个点的最近公共祖先，以及路径上的时间最大值（因为只有最晚被修的那条路被修了，两个城市才算被联通）

具体解释在代码中

### AC code


```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN = 1e5+5; 
struct edge{
	int to, nxt, w;
}e[MAXN << 1];
int head[MAXN], num_edge;
int n, m, q; 
int fa[MAXN], f[MAXN][20], fm[MAXN][20], dep[MAXN];
int read(){
	int w = 1, s = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-') w = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') s = (s << 1) + (s << 3) + ch - '0', ch = getchar();
	return w * s;
}
//链式前向星存边 
void add(int from, int to, int w){
	e[++num_edge].nxt = head[from];
	e[num_edge].to = to;
	e[num_edge].w = w;
	head[from] = num_edge;
}
//并查集避免出现环 
int find(int x){return fa[x] == x ? x : fa[x] = find(fa[x]);}
//建树 
void init(){
	for(int i = m; i >= 1; --i){//注意这里是从大到小，大家可以把题意的那个式子化简处理 
		for(int j = i + i; j <= n; j += i){//枚举每个编号为i的倍数的点 
			int fj = find(j), fi = find(i);
			if(fj != fi)
				fa[fj] = fi, add(i, j, m - i + 1), add(j, i, m - i + 1);
		}
	}
}
//lca预处理 
void dfs(int x, int fath){
	f[x][0] = fath; dep[x] = dep[fath] + 1; 
	for(int i = head[x]; i; i = e[i].nxt){
		int v = e[i].to;
		if(v == fath) continue;
		fm[v][0] = e[i].w;
		dfs(v, x);
	}
}
//lca预处理出最大值来 
void init_lca(){
	for(int i = 1; i <= 18; ++i){
		for(int j = 1; j <= n; ++j){
			f[j][i] = f[f[j][i - 1]][i - 1];
			fm[j][i] = max(fm[j][i-1], fm[f[j][i-1]][i-1]);
		}
	}
}
//取出x和y的最近公共祖先 
int get_lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	for(int i = 18; i >= 0; --i){
		if(dep[x] <= dep[f[y][i]])
			y = f[y][i];
	}
	if(x == y) return x;
	for(int i = 18; i >= 0; --i){
		if(f[x][i] == f[y][i]) continue;
		else{
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];
}
//求从x到lca的最大值 
int get_max(int x, int y){
	int ans = -19000;//因为两个点都是往它们的lca上跳，所以只需要前面那一块 
	for(int i = 18; i >= 0; --i){
		if(dep[f[x][i]] < dep[y]) continue;
		else{
			ans = max(ans, fm[x][i]);
			x = f[x][i];
		}
	}
	return ans;
}

int main()
{
	n = read(), m = read(), q = read();
	for(int i = 1; i <= n; ++i) fa[i] = i;
	init(); 
	dfs(1, 1);
	init_lca();
	for(int i = 1, u, v; i <= q; ++i){
		u = read(), v = read();
		int lca = get_lca(u, v);
		int maxu = get_max(u, lca);
		int maxv = get_max(v, lca);
		printf("%d\n", max(maxu, maxv));//愉快的输出答案 
	}
	return 0;//完美结束 
}

```



---

## 作者：Adove (赞：1)

~~我们教练上午考这题给扔到T1，花了一个半小时才A~~

首先这题题面可以这样描述

n个点，任意两点间连边的权值为$(a,b)$，（若$(a,b)>m$则无边相连），求$a$到$b$的一条路径，使得经过边权的最小值最大

那么我们只需要保留两点间联通时最大的必要的那些边

我们可以贪心地从大到小加边，从一个点向ta的倍数尝试连边，若不连通则连一条权值为该点编号的边

连通性可以用并查集维护

这样我们就得到了一棵树，两点间简单路径权值的最小值即为所求

加边的复杂度是$\Theta(n \log n)$级的，具体证明可以用放缩的方式来证

然后在树上跑倍增或树链剖分就行

问题：树链剖分如何做到$\Theta(q \log n)$？

我们可以预处理某点到链顶的最小边权

最后跳链到同一条时再用线段树

答案即为$m-ans+1$

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
#include"bitset"
using namespace std;

const int MAXN=1<<17;

int n,m,t,np;
int h[MAXN],f[MAXN],fa[MAXN],sn[MAXN],siz[MAXN],nwn[MAXN];
int id[MAXN],num[MAXN],ren[MAXN],dep[MAXN],top[MAXN];
int tree[MAXN<<1];
struct rpg{
	int li,nx,ln;
}a[MAXN<<1];

int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void un(int a,int b){int fa=find(a),fb=find(b);if(fa!=fb) f[fa]=fb;}
void add(int ls,int nx,int ln)
{
	a[++np]=(rpg){h[ls],nx,ln};h[ls]=np;
	a[++np]=(rpg){h[nx],ls,ln};h[nx]=np;
}

void dfs1(int x,int f,int tp,int ln)
{
	dep[x]=tp;
	fa[x]=f;
	siz[x]=1;
	num[x]=ln;
	for(int i=h[x];i;i=a[i].li){
		if(a[i].nx==f) continue;
		dfs1(a[i].nx,x,tp+1,a[i].ln);
		siz[x]+=siz[a[i].nx];
		if(siz[a[i].nx]>siz[sn[x]]) sn[x]=a[i].nx;
	}return;
}

void dfs2(int x,int tpx,int mx)
{
	id[x]=++id[0];
	ren[id[x]]=num[x];
	nwn[x]=mx;
	top[x]=tpx;
	if(!sn[x]) return;
	dfs2(sn[x],tpx,min(mx,num[sn[x]]));
	for(int i=h[x];i;i=a[i].li){
		if(a[i].nx==fa[x]||a[i].nx==sn[x]) continue;
		dfs2(a[i].nx,a[i].nx,num[a[i].nx]);
	}return;
}

void build(int k,int l,int r)
{
	if(l==r){
		tree[k]=ren[l];
		return;
	}int i=k<<1,mid=l+r>>1;
	build(i,l,mid);build(i|1,mid+1,r);
	tree[k]=min(tree[i],tree[i|1]);
	return;
}

int cask(int k,int l,int r,int le,int ri)
{
	if(le<=l&&r<=ri) return tree[k];
	int i=k<<1,mid=l+r>>1,ans=m+1;
	if(le<=mid) ans=min(ans,cask(i,l,mid,le,ri));
	if(mid<ri) ans=min(ans,cask(i|1,mid+1,r,le,ri));
	return ans;
}

int casks(int x,int y)
{
	int ans=m+1;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans=min(ans,nwn[x]);
		x=fa[top[x]];
	}if(dep[x]>dep[y]) swap(x,y);
	if(id[y]-id[x]>=1) ans=min(ans,cask(1,1,n,id[x]+1,id[y]));
	return ans;
}

int main()
{
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;++i) f[i]=i;
	for(int i=m;i;--i){
		for(int j=i<<1;j<=n;j+=i){
			if(find(i)!=find(j)){
				add(i,j,i);
				un(i,j);
			}
		}
	}dfs1(1,1,1,0);dfs2(1,1,m+1);
	build(1,1,n);
	while(t--){
		int x,y;scanf("%d%d",&x,&y);
		printf("%d\n",m-casks(x,y)+1);
	}return 0;
}
```

---

## 作者：rainygame (赞：0)

注意到可以从早到晚枚举 $k=m-i+1$，然后对于 $ak$ 和 $(a-1)k$ 之间连一条边，复杂度是调和级数。那么就相当于一个有 $O(n\ln n)$ 条边的图，每次询问两点之间路径的最大边权最小值。

看到这个可能可以考虑 Kruskal 重构树，但是不用这样做。将询问分别离线到 $a,b$ 上，每次合并两个连通块时枚举其中一个连通块的“待处理询问”，然后查询另一个连通块是否有这个询问，如果有，由于这是第一次将两个点连接（从早到晚枚举边），所以这个询问的答案即为当前的天数。对于没有的询问，放到合并后连通块的“待处理询问”集合即可。

时间复杂度 $O(n\log^2 n)$，代码很好写就不放了。

---

## 作者：OIerAlbedo (赞：0)



## $ \texttt{Introduction} $

原题+思维

## $ \texttt{Solution} $ 

本题题意可以简化为 $ i $ 和 $ j $ 之间连一条 $ m-\gcd(i,j)+1 $ 的边，然后问你从 $ a $ 走到 $ b $ 的道路中的最大值的最小值是多少。

简化之后的问题，难度就在于建边了，首先肯定不能建出一张单纯的图，我们发现答案要尽量的小，所以我们按价值从小到大加边，如果两个点已经相连，那么便不用再连，最后我们会得出一棵树。

但大体的思路怎么具体实现呢?

首先有一个很 $ naive $ 的想法，我们从大到小枚举最大公约数，然后找到最大公约数为这个数的两个点，按照上述的方法连边，但是这样时间复杂度会爆炸，亲测只有 $ 32pts $,那怎么办呢？

我们可以发现，选取的两个数一定都是最大公约数的倍数，那么我们直接将最大公约数和他的倍数连边，这样就把最大公约数是这个数的情况的边都连好了，也许你要问那如果会连多余的边呢，其实不会因为我们是要判断过得，如果最大公约数比这个数要大，那么前面一定已经连过边，就不会再连了。

建好这棵树之后就是经典操作了，我们要找两点之间的边的最大值，可以用倍增实现，具体可以参考[[NOIP2013 提高组] 货车运输](https://www.luogu.com.cn/problem/P1967)，然后这道题就做好了。

```c++
int find(int x)
{
	if (ff[x]==x) return ff[x];
	ff[x]=find(ff[x]);return ff[x];
}
void add(int x,int y,int z)
{
	cnt++;a[cnt]=y;b[cnt]=d[x];c[cnt]=z;d[x]=cnt;
}
void sc(int x,int y) //找两点之间最大边
{
    int t,i;
    if (e[x]>e[y]){
        t=x;x=y;y=t;
    }
for (i=lg[n];i>=0;i--)
     if (e[f[y][i]]>=e[x])
          {
              ans=max(ans,u[y][i]);
              y=f[y][i];
          }
    if (x==y) return ;
    for (i=lg[n];i>=0;i--)
         if (f[x][i]!=f[y][i])
              {
                  ans=max(ans,max(u[x][i],u[y][i]));
                  x=f[x][i];y=f[y][i];
              }
    ans=max(ans,max(u[x][0],u[y][0]));
}
int main()
{
	//ios::sync_with_stdio(0);cin.tie();cout.tie();
	n=read();m=read();T=read();
	for (i=1;i<=n;i++) ff[i]=i;
	for (i=m;i>=1;i--)
	     {
	     	for (j=2;j<=n/i;j++)
	     	              {
	     	              	x=i;y=i*j;
	     	              	r1=find(x);r2=find(y);
	     	              	if (r1!=r2)
	     	              	    {
	     	              	    	add(x,y,m-i+1);add(y,x,m-i+1);
	     	              	    	tot++;
								   }
							ff[r1]=r2;
							if (tot==n-1) break;
						   }
			if (tot==n-1) break;
	}//建图
	for (i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    t=1;w=1;f2[1]=1;e[1]=1;
    while (t<=w)
        {
            for (i=d[f2[t]];i;i=b[i])
                 {
                     if (e[a[i]]==0)
                          {
                              e[a[i]]=e[f2[t]]+1;
                              f[a[i]][0]=f2[t];u[a[i]][0]=c[i];
                              for (j=1;j<=lg[n];j++)
                                  {
                                  f[a[i]][j]=f[f[a[i]][j-1]][j-1];
                                  u[a[i]][j]=max(u[a[i]][j-1],u[f[a[i]][j-1]][j-1]);
                                  }
                            w++;f2[w]=a[i];
                            
                          }
                 }
            t++;
        }//倍增的预处理
    for (;T;T--)
          {
          	x=read();y=read();ans=0;
          	sc(x,y);
          	printf("%d\n",ans);
		  }
    return 0;
}

```



---

## 作者：ZCETHAN (赞：0)

[传送门](https://www.luogu.com.cn/problem/P4616)
## 题目大意
给定 $n$ 个点，第 $i$ 次会把所有编号满足 $\gcd(a,b)=m-i+1$ 的点对连边，对于每个询问 $a,b$，求点 $a$ 和点 $b$ 什么时候联通。

## Solution
脑洞不够，套路不够。其实想通了还是蛮简单的。

首先我们考虑把连边转化一下。如果 $\gcd(a,b)=k$，那么显然 $a$ 和 $b$ 都是 $k$ 的倍数。而每一次把 $\gcd(a,b)=k$ 的所有点连边，最后的连通性与把所有的 $k$ 的倍数是一样一样的。因此我们可以说，第 $i$ 次把所有编号为 $m-i+1$ 的倍数的点之间连边。

然后我们可以发现，如果我们把每次加的边编号的话，那么两个点之间最早的联通时间是路径上的最大值。因此就转化为求两点间所有路径上的最大值最小是多少。

于是自然联想到 [货车运输](https://www.luogu.com.cn/problem/P1967) 这题。考虑每次按序加边，同时维护是一颗树。当然可以选择克鲁斯卡尔重构树，或者直接最小生成树都是可以的，我代码中给出克鲁斯卡尔重构树的写法。

还有一个就是路径最值，可以倍增维护，当然也可以用树剖（不写挂的话），我代码中给出的是倍增。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf (1<<30)
#define INF (1ll<<60)
using namespace std;
const int MAXN=2e5+10;
int f[MAXN],val[MAXN];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
vector<int> e[MAXN];
int fa[MAXN][20],dp[MAXN][20],dep[MAXN];
void dfs(int x,int fat){
	fa[x][0]=fat;dp[x][0]=val[fat];
	for(int i=1;i<20;i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=1;i<20;i++)
		dp[x][i]=max(dp[x][i-1],dp[fa[x][i-1]][i-1]);//表示从 x 开始向上 2^i 格内的最大值
	for(int i=0;i<e[x].size();i++){
		int s=e[x][i];if(s==fat) continue;
		dep[s]=dep[x]+1;dfs(s,x);
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	int dlt=dep[x]-dep[y];
	for(int i=0;i<20;i++)
		if(dlt&(1<<i))
			x=fa[x][i];
	if(x==y) return x;
	for(int i=19;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}//倍增求 LCA
int main()
{
	int n,m,Q;
	scanf("%d%d%d",&n,&m,&Q);
	int cnt=n;
	for(int i=1;i<=n*2;i++)
		f[i]=i;
	for(int i=1;i<=m;i++){
		int dis=m-i+1;
		for(int j=dis;j+dis<=n;j+=dis){
			int u=find(j),v=find(j+dis);
			if(u==v) continue;
			val[++cnt]=i;
			f[u]=f[v]=cnt;
			e[cnt].push_back(u);
			e[cnt].push_back(v);
		}
	}
   //其实好像是不用克鲁斯卡尔重构树更加简洁……
   //不过也好顺便复习一下科技.jpg
	dfs(cnt,0);
	int x,y;
	while(Q--){
		scanf("%d%d",&x,&y);
		int lca=LCA(x,y);
		int dlt=dep[x]-dep[lca];
		int ans=0;
		for(int i=0;i<19;i++)
			if(dlt&(1<<i))
				ans=max(ans,dp[x][i]),
				x=fa[x][i];
		dlt=dep[y]-dep[lca];
		for(int i=0;i<19;i++)
			if(dlt&(1<<i))
				ans=max(ans,dp[y][i]),
				y=fa[y][i];
                //倍增找出最大值
		printf("%d\n",ans);
	}
}
```
## End

---

## 作者：FjswYuzu (赞：0)

发现现在做的题别人都做过，笑死。

注意到有许多条边，但是问题是判最少的天数联通。如果将一条边边权设为其修建的日子，那么问题询问的就是 $u$ 到 $v$ 的所有路径上，经过的最大边权最小的值。

注意到要答案越小越好，不难想到先建更小的边更好。那么，第 $i$ 天连了这么多条边，令 $x=m-i+1$，本质上我们只是将 $x,2x,\cdots ,\lfloor \frac{n}{x} \rfloor x$ 连接起来了。我们可以证明这些点之间可以只经过边权为 $x$ 的边。（因为 $\gcd(kx,(k-1)x) = x$）

关于暴力建边的时间复杂度，有一个经典结论是 $\sum_{i=1}^n \frac{n}{i} = \ln n$，所以时间复杂度是 $O(n \ln n)$。

考虑到我们之前的模型转换，对于一个一般的图这个问题是不好做的。如果放在一些有特殊性质的图上，或许可以简单解决。比如树。

注意到我们直接建边会出现环，我们用并查集避免这种事情发生即可。

于是建出一棵树，询问的就是两点间的最大边权。这个问题可以直接用倍增解决。每次询问两点间 LCA，倍增处理 $x$ 到 $x$ 的 $2^k$ 级祖先间的最大边权即可。

总时间复杂度是 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<18,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}
void write(int x)
{
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
struct unionFindSet{
	int fa[100005];
	void makeSet(int up){for(int i=0;i<=up;++i)	fa[i]=i;}
	int findSet(int x)
	{
		if(x==fa[x])	return x;
		return fa[x]=findSet(fa[x]);
	}
	bool unionSet(int x,int y)
	{
		int xx=findSet(x),yy=findSet(y);
		if(xx==yy)	return false;
		return fa[yy]=xx,true;
	}
}ufs;
struct Edge{
	int t,v;
	Edge(){}
	Edge(int T,int V){t=T,v=V;}
};
vector<Edge> G[100005];
int n,m,q,dep[100005],fa[18][100005],st[18][100005],lgs[100005];
void dfs(int now,int pre)
{
	dep[now]=dep[pre]+1;
	fa[0][now]=pre;
	for(int i=1;i<=17;++i)	fa[i][now]=fa[i-1][fa[i-1][now]],st[i][now]=max(st[i-1][now],st[i-1][fa[i-1][now]]);
	for(auto to:G[now])
	{
		int t=to.t,val=to.v;
		if(t==pre)	continue;
		st[0][t]=val;
		dfs(t ,now);
	}
}
int LCA(int u,int v)
{
	if(dep[u]>dep[v])	u^=v^=u^=v;
	while(dep[u]<dep[v])	v=fa[lgs[dep[v]-dep[u]]][v];
	if(u==v)	return u;
	for(int i=17;~i;--i)	if(fa[i][u]!=fa[i][v])	u=fa[i][u],v=fa[i][v];
	return fa[0][u];
}
int jump(int s,int t)
{
	int ret=0;
	while(dep[s]>dep[t])
	{
		ret=max(ret,st[lgs[dep[s]-dep[t]]][s]);
		s=fa[lgs[dep[s]-dep[t]]][s];
	}
	return ret;
}
int main(){
	n=read(),m=read(),q=read();
	ufs.makeSet(n);
	for(int i=1;i<=m;++i)
	{
		int tek=m-i+1;
		for(int j=2;j*tek<=n;++j)
		{
			if(ufs.unionSet((j-1)*tek,j*tek))
			{
				G[(j-1)*tek].push_back(Edge(j*tek,i));
				G[j*tek].push_back(Edge((j-1)*tek,i));
//				printf("%d %d %d\n",(j-1)*tek,j*tek,i);
			}
		}
	}
	dfs(1,0);
	for(int i=2;i<=n;++i)	lgs[i]=lgs[i>>1]+1;
	while(q-->0)
	{
		int u=read(),v=read(),lca=LCA(u,v);
		write(max(jump(u,lca),jump(v,lca))),puts("");
	}
	return 0;
}
```

---

## 作者：tommymio (赞：0)

结论题。

证明一下，对于 $\forall i$ ，在第 $i$ 天，只需将 $m-i+1$ 与它的倍数连边所得生成树 $T$ 的连通性与 $\forall i$，在第 $i$ 天，当 $\gcd(a,b)=m-i+1$，则将 $a,b$ 连边，所得图 $G$ 的连通性相同。对于两个点 $a,b$，在第 $i$ 天才能够 **直接到达（即在原图 $G$ 上有边 $(a,b)$）** ，一定满足 $\gcd(a,b)=m-i+1$，也就是说 $(m-i+1)|a,(m-i+1)|b$，按照我们对于生成树 $T$ 的定义，在生成树 $T$ 上这两点是连通的，在原图上也是连通的，证毕。

那么在第 $i$ 天，我们将 $m-i+1$ 与它的倍数连边。需要维护一组边集判断连边后是否存在环，这个可以使用并查集。还需要维护 $a,b$ 最早在哪天加入哪条边之后可以相互到达，使用按秩合并 $/$ 启发式合并保持并查集的结构，在 $a,b$ 已经连通时，查询路径 $a\to b$ 上最晚加入的边的天数。我们将第 $i$ 天加入的边的边权设做 $i$，那么就是查询 $a\to b$ 上边权最大的值。

按秩合并有着非常好的性质：所得生成树高不会超过 $\log n$，所以如果使用按秩合并，我们可以暴力查询这个值。 

---

