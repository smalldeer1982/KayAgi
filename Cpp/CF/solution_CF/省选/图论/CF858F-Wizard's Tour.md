# Wizard's Tour

## 题目描述

All Berland residents are waiting for an unprecedented tour of wizard in his Blue Helicopter over the cities of Berland!

It is well-known that there are $ n $ cities in Berland, some pairs of which are connected by bidirectional roads. Each pair of cities is connected by no more than one road. It is not guaranteed that the road network is connected, i.e. it is possible that you can't reach some city from some other.

The tour will contain several episodes. In each of the episodes:

- the wizard will disembark at some city $ x $ from the Helicopter;
- he will give a performance and show a movie for free at the city $ x $ ;
- he will drive to some neighboring city $ y $ using a road;
- he will give a performance and show a movie for free at the city $ y $ ;
- he will drive to some neighboring to $ y $ city $ z $ ;
- he will give a performance and show a movie for free at the city $ z $ ;
- he will embark the Helicopter and fly away from the city $ z $ .

It is known that the wizard doesn't like to use roads, so he agrees to use each road at most once (regardless of direction). In other words, for road between $ a $ and $ b $ he only can drive once from $ a $ to $ b $ , or drive once from $ b $ to $ a $ , or do not use this road at all.

The wizards wants to plan as many episodes as possible without violation the above rules. Help the wizard!

Please note that the wizard can visit the same city multiple times, the restriction is on roads only.

## 样例 #1

### 输入

```
4 5
1 2
3 2
2 4
3 4
4 1
```

### 输出

```
2
1 4 2
4 3 2
```

## 样例 #2

### 输入

```
5 8
5 3
1 2
4 5
5 1
2 5
4 3
1 4
3 2
```

### 输出

```
4
1 4 5
2 3 4
1 5 3
5 2 1
```

# 题解

## 作者：Morning_Glory (赞：6)

[也许更好的阅读体验cnblog](https://www.cnblogs.com/Morning-Glory/p/11437909.html)	

[也许更好的阅读体验csdn](https://blog.csdn.net/Morning_Glory_JR/article/details/100168725)
	
# $\mathcal{Description}$	
	
给定一张 $n$ 个点 $m$ 条边的无向图，每条边连接两个顶点，保证无重边自环，不保证连通。	
	
你想在这张图上进行若干次旅游，每次旅游可以任选一个点 $x$ 作为起点，再走到一个与 $x$ 直接有边相连的点 $y$，再走到一个与 $y$ 直接有边相连的点 $z$ 并结束本次旅游。	
	
作为一个旅游爱好者，你不希望经过任意一条边超过一次，注意一条边不能即正向走一次又反向走一次，注意点可以经过多次，在满足此条件下，你希望进行尽可能多次的旅游，请计算出最多能进行的旅游次数并输出任意一种方案。	
	
# $\mathcal{Solution}$	
	
## **20**分思路	
	
先提供一个比较傻且只能得20分的思路		
就是我们把每条边看做是一个点，距离为一的点之间连一条边	
于是问题就变成了求最大匹配了	
不过这样会把边的条数大大增大.....	
妥妥的TLE	
	
## **100**分思路	
	
若仅是一棵树，那此题的做法还是很显然的	
要保证边用的最多，按照树的深度从小到大考虑，即按照拓扑序将能匹配的匹配就是正确的	
	
若不仅是一棵树，我们随便按照一种方式把它的生成树建出来	
这样就有非树边和树边，对于每个点，我们先将其与父亲的边不考虑	
设其周围有$n$条边	
若$n$为偶数，就可以把它们两两搭配，有$\frac{n}{2}$种方法	
若$n$为奇数，就拿一条边与其与父亲的边搭配，剩下的两两搭配	
显然，这样做除了在根节点剩下一条边，其他的边都会被用到	
	
# $\mathcal{Code}$	
	
实现部分说一下吧	
我觉得我打得比其它人的简洁一些吧	
大部分人用了一个$vector$去记录哪些边	
实际上，我们可以直接把这些边匹配	
用$f[x]$表示是否有一条与$x$相连且还没有匹配的边	
每次拿到新边看看有没有为匹配的边，有的话它们就匹配	
注意一条边只需考虑一次	
```cpp	
/*******************************	
Author:Morning_Glory	
LANG:C++	
Created Time:2019年08月30日 星期五 09时08分56秒	
*******************************/	
#include <cstdio>	
#include <fstream>	
#include <cstring>	
using namespace std;	
const int maxn = 1000006;	
//{{{cin	
struct IO{	
	template<typename T>	
	IO & operator>>(T&res){	
		res=0;	
		bool flag=false;	
		char ch;	
		while((ch=getchar())>'9'||ch<'0')	 flag|=ch=='-';	
		while(ch>='0'&&ch<='9') res=(res<<1)+(res<<3)+(ch^'0'),ch=getchar();	
		if (flag)	 res=~res+1;	
		return *this;	
	}	
}cin;	
//}}}	
int n,m,u,v,cnt,ans;	
int head[maxn],nxt[maxn],to[maxn];//edge	
int a[maxn],b[maxn],c[maxn],f[maxn];//ans	
bool vis[maxn];	
//{{{add	
void add (int u,int v)	
{	
	nxt[cnt]=head[u],head[u]=cnt,to[cnt++]=v;	
}	
//}}}	
//{{{dfs	
void dfs (int x)	
{	
	vis[x]=true;	
	for (int e=head[x];~e;e=nxt[e]){	
		int te=to[e];	
		to[e]=to[e^1]=0;	
		if (te){	
			if (!vis[te])	dfs(te);	
			if (f[te])	a[++ans]=x,b[ans]=te,c[ans]=f[te],f[te]=0;	
			else if (f[x])	a[++ans]=f[x],b[ans]=x,c[ans]=te,f[x]=0;	
			else	f[x]=te;	
		}	
	}	
}	
//}}}	
int main()	
{	
	memset(head,-1,sizeof(head));	
	cin>>n>>m;	
	for (int i=1;i<=m;++i)	cin>>u>>v,add(u,v),add(v,u);	
	vis[0]=true;	
	for (int i=1;i<=n;++i)	
		if (!vis[i])	dfs(i);	
	printf("%d\n",ans);	
	for (int i=1;i<=ans;++i)	printf("%d %d %d\n",a[i],b[i],c[i]);	
	return 0;	
}	
```	


---

## 作者：Hoks (赞：3)

## 前言
比较有意思的题，鸽了好几天。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
题意即为能把一张图最多分成多少份连续的两条边。

题目中的图不一定连通，但其实不连通也就是很多张连通图的答案加起来而已，所以这里我们只考虑图连通的情况。

对于图连通的情况，我们考虑再把它变得特殊一点，要是直接是一颗树呢？

对于 $n$ 个点的一颗树，显然我们可以匹配上 $\lfloor\frac{n-1}{2}\rfloor$。

方法即为对于一个点优先拿他儿子的边匹配，匹配完了还剩下一个奇数的就把走向父亲的边拿上。

注意到我们这个过程中为什么这样选肯定可以满足。

因为我们不断把深度低的多余的 $1$ 条边不断的往上丢，尝试在深度更低的位置处理他。

那么对于这个题同理。

我们现在已经找出了一颗生成树，接着对于每个点，先尝试用非走向父亲的边两两匹配。

若还剩下 $1$ 条边，就选上走向父亲的边，也就相当于把多余边扔上去了。

这个过程中多余的边的深度在不断减少，除了初始那一层，其他层都不可能有多余边，所以最多浪费一条。

因为图不连通，所以遍历下都跑一遍即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,V=1e5,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int n,m,tot,res,mp[N],f[N];vector<int>e[N];vector<pair<pair<int,int>,int>>ans;map<pair<int,int>,bool>vis;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int u(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) u=(u<<1)+(u<<3)+(fc^48),fc=getchar();
        return u*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int u)
    {
        if(u<0) put('-'),u=-u;
        if(u>9) print(u/10);
        put(u%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void dfs(int u)
{
    mp[u]=1;
    for(auto v:e[u])
    {
        if(vis.count({u,v})||vis.count({v,u})) continue;vis[{u,v}]=1;vis[{v,u}]=1;tot++;
        if(!mp[v]) dfs(v);
        if(f[v]) ans.push_back({{u,v},f[v]}),f[v]=0;
        else if(f[u]) ans.push_back({{f[u],u},v}),f[u]=0;
        else f[u]=v;
    }
}
signed main()
{
    n=read(),m=read();for(int i=1,u,v;i<=m;i++) u=read(),v=read(),e[u].emplace_back(v),e[v].emplace_back(u);
    for(int i=1;i<=n;i++) if(!mp[i]) tot=0,dfs(i),res+=tot/2;print(res);put('\n');
    for(auto i:ans) print(i.first.first),put(' '),print(i.first.second),put(' '),print(i.second),put('\n');
    genshin:;flush();return 0;
}
```

---

## 作者：ln001 (赞：2)

## 题意
给你一个不一定联通的无向[简单](https://oi-wiki.org/graph/concept/#%E7%AE%80%E5%8D%95%E5%9B%BE:~:text=%E8%8B%A5%E4%B8%80%E4%B8%AA%E5%9B%BE%E4%B8%AD%E6%B2%A1%E6%9C%89%E8%87%AA%E7%8E%AF%E5%92%8C%E9%87%8D%E8%BE%B9%EF%BC%8C%E5%AE%83%E8%A2%AB%E7%A7%B0%E4%B8%BA%E7%AE%80%E5%8D%95%E5%9B%BE%E3%80%82)图，每次操作可以删除两条共点的边，求最大的操作次数，输出操作过程。

## 做法

较为暴力的做法为把原图中的边化为新图上的点，在**在原图中共点的边**对应的两个新点中连边，然后跑二分图匹配。不过复杂度假了，且对正解没什么启发性。

---

由于不同的连通块之间贡献独立，不妨假设图是联通的。

先思考图是一棵树的情况下的答案，一种可行的策略如下：

>将树按照点的深度分层，自深向浅**逐层**遍历，假设当前扫到点 $x$，且 $x$ 目前有偶数个连向儿子的边，则将其逐个配对。若 $x$ 有奇数个儿子，则一条边与边 $x \leftrightarrow fa_x$ 匹配，并删去点 $x$，然后跑偶数个儿子的做法。

在这种策略下，显然能保证对任意边 $x \leftrightarrow fa_x \ (fa_x \neq \text{root})$ 均被配对。更进一步的，至多会有一条边未被匹配，即答案为 $\lfloor \frac{n - 1}{2} \rfloor$，记录操作过程也是容易的。

若图不是一棵树，则先跑出一颗生成树，然后将非树边 $x \leftrightarrow y \  (dep_x < dep_y)$ 改为 $x \leftrightarrow \text{a new unique node}$。这时图变成了树，只需要照着上述树的方式跑一遍。

---

## 作者：qfpjm (赞：1)

# 一些变量/表述方式

- $u-v$ 表示连接 $u,v$ 的边。

- $f_i$，则 $i-f_i$ 是一条没被使用过的边。

# 题解

1. 递归到每一个节点 $u$，判断 $u-v_i$ 是否被使用过。

2. 如果没有，那么在判断 $v_i$ 是否被访问过，如果没有，就递归这个节点。

3. 然后判断 $v_i$ 有没有没使用过的边。如果有 $u-v_i-f_{v_i}$ 就构成了一组符合题目要求的路线。如果没有，那没判断 $u$ 有没有没被使用过的边，如果有，那么 $f_{u}-u-v_i$ 就构成了一组符合题目要求的路线。如果还没有，那么 $u,v_i$ 就无法找到一个可以与之构成题目要求路线的点，只能记录下 $u,v_i$ 之间这一条没有被使用过的边，然后等待下一个机会。

- 由于图不一定连通，所以要逐个从没访问过的节点开始递归。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

struct node
{
	int x, y, z;
}ans[200005];

int n, m, cnt, f[200005];
bool vis[200005];
int tot, head[200005], to[400005], nxt[400005];

void add(int x, int y)
{
	nxt[tot] = head[x];
	head[x] = tot;
	to[tot ++] = y;
}

void dfs(int u)
{
	vis[u] = 1;
	for (int i = head[u] ; ~i ; i = nxt[i])
	{
		int v = to[i];
		to[i] = to[i ^ 1] = 0;
		if (v)
		{
			if (!vis[v])
			{
				dfs(v);
			}
			if (f[v])
			{
				ans[++ cnt] = (node){u, v, f[v]};
				f[v] = 0;
			}
			else if (f[u])
			{
				ans[++ cnt] = (node){f[u], u, v};
				f[u] = 0;
			}
			else
			{
				f[u] = v;
			}
		}
	}
}

int main()
{
	memset(head, -1, sizeof(head));
	cin >> n >> m;
	for (int i = 1 ; i <= m ; i ++)
	{
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	vis[0] = true;
	for (int i = 1 ; i <= n ; i ++)
	{
		if (!vis[i])
		{
			dfs(i);
		}
	}
	cout << cnt << endl;
	for (int i = 1 ; i <= cnt ; i ++)
	{
		cout << ans[i].x << " " << ans[i].y << " " << ans[i].z << endl;
	}
}
```


---

