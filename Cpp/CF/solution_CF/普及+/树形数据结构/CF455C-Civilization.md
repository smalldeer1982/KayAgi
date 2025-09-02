# Civilization

## 题目描述

给出一个由 $n$ 个点，$m$ 条边组成的森林，有 $q$ 组询问

1. 给出点 $x$，输出点 $x$所在的树的直径  
2. 给出点 $x,y$，（如果 $x,y$ 在同一棵树中则忽略此操作）选择任意两点 $u,v$，使得 $u$ 跟 $x$ 在同一棵树中且 $v$ 跟 $y$ 在同一棵树中。将 $u,v$ 之间连一条边，使得连边后的到的新树的直径最小

## 说明/提示

$1 \le m < n \le 3\cdot 10^5$  
$1 \le q \le 3 \cdot 10^5$  
感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
6 0 6
2 1 2
2 3 4
2 5 6
2 3 2
2 5 3
1 1
```

### 输出

```
4
```

# 题解

## 作者：Priori_Incantatem (赞：8)

**Update 2020.08.25**：修改了一些错别字与不通顺的地方

### 题目大意

给出一个 $n$ 个点，$m$ 条边组成的森林，有 $q$ 组询问：  

1. 给出点 $x$，求点 $x$ 所在的树的直径  
2. 给出点 $x,y$，要求将 $x,y$ 所在的树之间连一条边并构成一棵新的树，满足这个新的树的直径最小

### 解题思路

首先，我们用树形DP（或bfs）求出每棵树的直径，并用并查集维护连通情况  
维护 $c$ 数组：对于每棵树的根节点 $x$，$c[x]=$ 该树的直径长度

接下来，对于每个询问 $2$（如果给出的两点在同一棵树内则忽略），利用并查集找出两棵树的根节点 $x,y$，并用并查集合并两棵树；合并后的树的直径则为 $max\{ \lceil\frac{c[x]}{2}\rceil  + \lceil\frac{c[y]}{2}\rceil +1,c[x],c[y] \}$，这里讲一下原因

要想直径最短，我们选择加边的点一定要在直径上，因为其他的点走到直径还要一段距离，从而增长了路径

那么直径就被选择的点分成了两段。因为我们要最小化较长的那一段，所以要让选择的点尽量靠近直径的中点。最后的答案就是 直径长度的一半向上取整

**注意**：后边的 $c[x],c[y]$ 一定要加上，不然只有三十分（像我一样QwQ）  
因为在合并后的树里，原来两棵树的直径还是存在的，所以新的树的直径至少是 $max(c[x],c[y])$

比如说下图：

![image.png](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pLmxvbGkubmV0LzIwMjAvMDEvMjcvWmROVGdpdjdrcmhDc21jLnBuZw?x-oss-process=image/format,png)


$c[x]=4,c[y]=0$  
那么，按 $\lceil\frac{c[x]}{2}\rceil  + \lceil\frac{c[y]}{2}\rceil +1$ 算出的直径应该是 $3$。  
而正确的直径该是 $4$，所以一定要考虑 $c[x],c[y]$

最后，对于每个询问 $1$，输出该树根节点对应的 $c$ 数组值就可以了

**AC代码**

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int Maxn=300000+10,inf=0x3f3f3f3f;
int d[Maxn],g[Maxn];
int f[Maxn],c[Maxn]; // 这里的c数组的含义不是跟上面对应的
bool vis[Maxn];
vector <int> e[Maxn];
int n,m,q,len;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int find(int x)
{
	if(f[x]==x)return x;
	return f[x]=find(f[x]);
}
void dfs(int x,int fa) // 树形DP求树的直径
{
	int m1=-1,m2=-1;
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if(y==fa)continue;
		dfs(y,x);
		int tmp=d[y]+1;
		d[x]=max(d[x],tmp);
		if(tmp>m1)m2=m1,m1=tmp;
		else if(tmp>m2)m2=tmp;
	}
	g[x]=max(max(0,m1+m2),max(m1,m2));
	len=max(len,g[x]);
}
void calc(int x) // 寻找树的直径
{
	len=0;
	dfs(x,0);
	c[x]=len;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),m=read(),q=read();
	
	for(int i=1;i<=n;++i)
	f[i]=i;
	
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		f[find(x)]=find(y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	
	for(int i=1;i<=n;++i)
	{
		if(f[i]!=i || vis[i])continue;
		calc(i);
		vis[i]=1;
	}
	
	while(q--)
	{
		int opt=read(),x=read();
		if(opt==1)
		{
			printf("%d\n",c[find(x)]);
			continue;
		}
		int y=read();
		x=find(x),y=find(y);
		if(x==y)continue;
		int tmp=((c[x]+1)>>1)+((c[y]+1)>>1)+1; //一个巧妙的向上取整的方法
		
		tmp=max(tmp,max(c[x],c[y]));
		
		f[find(x)]=find(y);
		c[find(x)]=tmp;
	}
	
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：4)

## 题意分析
首先给你一个由 $n$ 个点、$m$ 个边组成的森林，询问 $q$ 次，有两种操作，$1$ 操作是输出 $x$ 所在树的直径，$2$ 操作是连接给出的 $x$ 和 $y$。
## 大体思路
因为我们要找的是 $x$ 所在树的直径，所以最好是定义一个并查集 $fa$ 来存这个点的祖先，然后用两次 DFS 这种方便的方式来查每棵树的直径。

接下来就是重点了。
### 操作
操作 $1$ 的话直接输出就好了，操作 $2$ 的话要先判断在不在同一个树中，如果在就没必要连了，直径不会变，连的话我们需要用一个重要的性质：设直径为 $d$，在树上找到一点，要求其他点到这个点的距离最大值最小，其最大值 $=\lceil d\div2\rceil$。
```cpp
void hb(int x,int y){
	int maxxx=max(wei[x],wei[y]);
	fa[x]=y;//x是y的子树或者是y是x的子树都无所谓，统一好父节点就行 
	wei[y]=max(maxxx,(wei[x]+1)/2+(wei[y]+1)/2+1);//性质：在树上找到一点，其他点到这个点的距离最大值最小，最大值=直径/2+直径%2，这里要优化常数，否则会TLE
} 
```
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[300005];
vector<int> s[300005];
int maxb=1,maxx=0;//最远的节点和最大的直径 
int wei[300005];
int find(int x){
	if(fa[x]==x){
		return x;
	}
	else{
		fa[x]=find(fa[x]);
		return fa[x];
	}
}//并查集合并父节点的板子
void dfs(int x,int sum,int fa){
	if(sum>maxx){
		maxx=sum;
		maxb=x;
	}//比最大值大就更新 
	for(auto v:s[x]){
		if(v==fa){
			continue ;
		}//他和他父亲也连接，所以除了他父亲全都遍历一遍 
		dfs(v,sum+1,x);
	}
}
void hb(int x,int y){
	int maxxx=max(wei[x],wei[y]);
	fa[x]=y;//x是y的子树或者是y是x的子树都无所谓，统一好父节点就行 
	wei[y]=max(maxxx,(wei[x]+1)/2+(wei[y]+1)/2+1);//性质：在树上找到一点，其他点到这个点的距离最大值最小，最大值=直径/2+直径%2，这里要优化常数，否则会TLE
} 
int main(){
	int n,m,q;
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}//初始化自己的父节点是自己 
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		s[x].push_back(y);
		s[y].push_back(x);//连边 
		fa[find(x)]=find(y);//把这两个点合并，统一父节点 
	}
	for(int i=1;i<=n;i++){//遍历森林中每一棵树的根节点 
		if(fa[i]==i){
			maxb=i; 
			maxx=0;
			dfs(i,0,0);
			maxx=0;
			dfs(maxb,0,0);
			wei[i]=maxx;				
		}//两次dfs找树的直径 
	}
	for(int i=1;i<=q;i++){
		int t;
		scanf("%d",&t);
		if(t==1){
			int x;
			scanf("%d",&x);
			int xfa=find(x);
			cout<<wei[xfa]<<'\n';//如果是查询直接输出 
		}
		if(t==2){
			int x,y;
			scanf("%d%d",&x,&y);
			int xf=find(x),yf=find(y);
			if(xf!=yf){//如果是连新边，先判断在不在同一个树中（用查询祖先是不是一个点的方式），如果在就没必要连了，直径不会变 
				hb(xf,yf);//合并两棵树 
			}
		}
	}
	return 0;
}
```

---

## 作者：wxzzzz (赞：2)

### 思路

前置：[树的直径](https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=1&tn=baidu&wd=%E6%A0%91%E7%9A%84%E7%9B%B4%E5%BE%84&fenlei=256&rsv_pq=0x9cad29a800001d8d&rsv_t=e5a1KHbMcFQHP7tJTsH7IIJgIw2yySf%2FkYmjZ5zJE6cQEvgeECrJDwU%2BGb78&rqlang=en&rsv_dl=tb&rsv_enter=1&rsv_sug3=13&rsv_sug1=13&rsv_sug7=100&rsv_sug2=0&rsv_btype=i&inputT=2430&rsv_sug4=2430)、[并查集](https://www.cnblogs.com/wangxuzhou-blog/p/advanced-data-structure.html#并查集)

先考虑操作 $2$，怎样连能使新的直径最小。

随便画一张图，答案可以为 $(3,7)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/gd03xyw5.png)

显然，把两棵树直径上中间的点连起来是最优的。

所以，答案与树的形态无关，仅与树的直径有关。

而且，合并后新的直径只与要合并的两棵树的直径长度有关。

记 $d_i$ 表示以 $i$ 为根的树的直径，要合并根节点分别为 $x,y$ 的两棵树，则新树的最小直径为：

$$\max(\lceil\dfrac{d_x}{2}\rceil  + \lceil\dfrac{d_y}{2}\rceil +1,d_x,d_y)$$

所以，在所有合并操作前先求出每棵树的直径，然后递推即可。

合并后，要更新每个节点的根节点，这个过程可以用并查集维护。

最后还要注意，如果两个点在同一棵树内，就无需操作。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, q, idx, pos, maxn, f[800005], d[800005], v[800005], h[800005], ne[800005];
inline void add(int a, int b) {
    v[++idx] = b, ne[idx] = h[a], h[a] = idx;
}
inline int up(int x) {
    return ceil(x / 2.0);
}
inline int find(int x) {
    if (x == f[x])
        return x;

    return f[x] = find(f[x]);
}
inline void dfs(int x, int F, int dis) {
    for (int i = h[x]; ~i; i = ne[i]) {
        int y = v[i];

        if (y == F)
            continue;

        if (maxn < dis + 1)
            maxn = dis + 1, pos = y;

        dfs(y, x, dis + 1);
    }
} //求在这棵树上离 x 最远的一个节点
inline void get(int x) {
    maxn = 0, pos = x;
    dfs(x, 0, 0), dfs(pos, 0, 0);
    d[x] = maxn;
} //两遍搜索求树的直径
int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= n; i++)
        f[i] = i;

    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y), add(y, x);
        f[find(x)] = find(y);
    }

    for (int i = 1; i <= n; i++)
        if (f[i] == i)
            get(i);

    while (q--) {
        int op, x;
        scanf("%d%d", &op, &x);
        x = find(x);

        if (op == 1) {
            printf("%d\n", d[x]);
        } else {
            int y;
            scanf("%d", &y);
            y = find(y);

            if (x == y)
                continue;

            f[x] = y, d[y] = max(up(d[x]) + up(d[y]) + 1, max(d[x], d[y]));
        }
    }

    return 0;
}
```

---

## 作者：Rainy_chen (赞：2)

### 题目翻译
原翻译有毒  
给你有$n$个点的森林，然后你需要支持两种操作：
- 询问某个点所在的树的直径
- 合并两棵树，同时使合并后的树的直径最小

### 题解
感觉有思维含量，但是不至于到紫题qwq

考虑到我们只关心每个点所在的树的信息，我们可以使用并查集去解决这个问题。

我们对并查集的每一棵树维护这棵树对应到原图后的直径，假设为$ans_i$，同时并查集的两个操作分别为`findfa(i),merge(u,v)`。

对于初始的森林，我们可以通过常规的两遍dfs或者树形dp求出每一棵树的直径，同时将所有在同一棵树中的节点`merge`起来，用之前求的直径去更新这棵树中某个节点的`ans[findfa(i)]`。

操作1直接输出`ans[findfa(i)]`即可。  

难点是操作2，我们需要合并两棵树并且保证合并后的直径最小。

我们不妨设这两棵树分别为$u,v$。

之后我们认为$rt_u,rt_v$为这两棵树的根，并且在之后的合并中要将$rt_u,rt_v$相连。  
容易发现$rt_u,rt_v$均为其所在树的某条直径的最中间的点。 我们考虑证明。

将$u,v$合并后的树的直径要么是在$u,v$两棵树中单独产生，要么通过新连的边产生。由于$u,v$直径已经是一个定值，我们只需要最小化后者。

我们发现实际上这个新连出来的边形成的可能作为直径的路径的长度就是$dep_u+dep_v-1$，也就是说从$u,v$中分别挑一条从根开始的最长的路径，其中$dep_u$表示$u$这棵树的深度，只有一个节点的树的深度被定义为1。

最小化$dep_u+dep_v-1$只需要使$dep_u,dep_v$最小即可。  

考虑到树中最长路径就是直径，所以只需要使直径折半即可，也就是令$rt_u$为直径的中点。此时$dep_u=\left\lfloor\frac{ans_u+1}2\right\rfloor+1$。

此时是否可能在$u$中存在一条从根开始的不在直径上的路径要长于折半后的直径？

不可能，我们假设存在这样一条路径，那么用这条路径代替原直径折半后较小的那一条路径一定会使找出的直径变长，而求出的直径一定已经是树中的最长路径而不可能更长，也就证明这样的路径不存在。

于是我们知道$u,v$合并后的树$x$的ans应该有
$$ ans[x] = \max(\left\lfloor\frac{ ans[u]+1}2\right\rfloor+\left\lfloor\frac{ans[v]+1}2\right\rfloor+1,ans[u],ans[v]) $$

复杂度**大概**在$\rm O((q+n)logn)$或者$\rm O((q+n)\alpha(n))$左右，这里取决于并查集的复杂度。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef int int_t;
const int_t maxn = 300100;

int_t read(){
    int_t x = 0,w = 1;char ch = 0;
    while(!isdigit(ch)) { ch = getchar(); if(ch == '-') w = -1;}
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x * w;
}

vector<int_t> G[maxn];

int_t vis[maxn];
int_t fa[maxn],ans[maxn];

int_t findfa(int_t rt){return rt == fa[rt] ? rt : fa[rt] = findfa(fa[rt]);}
void merge(int_t a,int_t b){if(findfa(a) != findfa(b)) fa[fa[a]] = fa[b];}

int_t tmp = 0,tmp2 = 0;//tmp记录每次dfs时的最远距离 tmp2记录最远距离是哪个点

void dfs(int_t rt,int_t col,int_t res){
    if(vis[rt] == col) return;
    if(res > tmp) tmp = res,tmp2 = rt;
    vis[rt] = col;
    for(int_t to : G[rt]) merge(rt,to),dfs(to,col,res+1);    
}

int main(){
    int_t n = read(),m = read(),q = read();
    for(int_t i=1;i<=n;i++) fa[i] = i;
    while(m--){
        int_t u = read(),v = read();
        G[u].push_back(v); G[v].push_back(u);
    }
    for(int_t i=1;i<=n;i++) if(!vis[i]) {
        tmp = 0,tmp2 = i;
        dfs(i,i,0);
        tmp = 0;
        dfs(tmp2,tmp2,0);
        ans[findfa(i)] = tmp;
    }
    while(q--){
        int_t opt = read();
        if(opt == 1) printf("%d\n",ans[findfa(read())]);
        else{
            int_t u = read(), v = read();
            u = findfa(u),v = findfa(v);
            if(u == v) continue;
            fa[u] = v;
            ans[v] = max(max(ans[v],ans[u]),(ans[u] + 1) / 2 + (ans[v] + 1) / 2 + 1);
        }
    }
}
```	

---

## 作者：noall (赞：2)

好题啊……

又是一道让人头秃的好题啊……

真是愉悦……

居然卡memset……

看完记得点赞啊！

#### 思路

~~My vegetable has exploded……~~咳咳……看题

树的直径大家都知道吧……不知道的可以看[这篇博客](https://big-news.github.io/2019/04/11/%E6%A0%91%E7%9A%84%E7%9B%B4%E5%BE%84/)。

这里，我用的是跑两遍大法师（$dfs$）求直径。

树的合并，那么，很明显，我们要用并查集来解决问题。

我们可以先根据已知的边，来将已知的所有树（**注意集合的合并**）都建好。然后对于这每个树，都单独跑两遍大法师，求出这棵树（**这个集合**）所拥有的直径（也就是第一问）。

哦对，顺便说一下，在跑这几遍大法师的时候，不要用$memset$初始化$vis$数组，直接在大法师$return$前$vis[x]=false$即可，否则会T得很惨。

然后，进行操作。

当$opt=1$时，直接输出x所在的树（集合）所拥有的直径（$dis[find(x)]$）即可。

当$opt=2$时，将x和y所在的集合合并($merge(x,y)$)，更新合并后的树（集合）所拥有的直径即可。

怎么更新呢？这就是这个题的难点所在了吧……~~也许~~

首先，我们可以很容易证明，一个点越靠近一个链（直径）的中点，这个点所能达到两端的最长距离最短。

来个图bb一下：

![graph.png](https://img.langlangago.xyz/2019/06/25/5d11ce16eb380.png)

我们可以看到，在该链中，两端为$0$和$4$。

我们假如取$0$这个点，那么$0$到两端的最长距离为$0$到$4$的距离，为$4$.

我们假如取最靠近该链的中点的$2$（也就是中点），那么$2$到两端的最长距离为$2$到$4$的距离，为$2$。也就是这个点所能达到两端的最长距离最短。

那么，我们连接这两棵树中的直径上最靠近中点的两个点，就可以满足“最长路径的长度最小”。

也就是$dis[yy]=max(max((dis[xx]+1)/2+(dis[yy]+1)/2+1,dis[xx]),dis[yy]);$

$xx$为$find(x)$,$yy$为$find(y)$

#### code

```c++
#include<cstdio>
#include<cstring>

#define in inline
#define re register
#define mian int main()

const int maxn=3e6+10;

struct edge{
	int to,next;
}map[maxn];

int n,m,q,fa[maxn],maxx,dis[maxn],st;
int cnt,head[maxn];
bool vis[maxn],vis2[maxn];

in int read(){
    char ch=getchar();int x=0,f=1;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

in void add(int x,int y){
	map[++cnt].to=y;
	map[cnt].next=head[x];
	head[x]=cnt;
}

in int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
in void merge(int x,int y){
	int xx=find(x),yy=find(y);
	fa[xx]=yy;
}

in void dfs(int x,int val){
	if(maxx<val) maxx=val,st=x;
	for(int i=head[x];i;i=map[i].next){
		int y=map[i].to;
		if(!vis[y]){
			vis[y]=true;
			dfs(y,val+1);
		}
	}
	vis[x]=false;//TLE的惨痛教训
}

in void dfs2(int x,int val){
	if(maxx<val) maxx=val;
	for(int i=head[x];i;i=map[i].next){
		int y=map[i].to;
		if(!vis[y]){
			vis[y]=true;
			dfs2(y,val+1);
		}
	}
	vis[x]=false;//TLE的惨痛教训
}

in int max(int a,int b){return a>b?a:b;}

mian{
	n=read(),m=read(),q=read();
	for(re int i=1;i<=n;i++) fa[i]=i;//初始化 
	for(re int i=1;i<=m;i++){
		int x=read(),y=read();
		add(x,y),add(y,x);
		merge(x,y);
	}
	for(re int i=1;i<=n;i++){
		int x=find(i);
		if(vis2[x]) continue;
		maxx=-1;
		//memset(vis,false,sizeof(vis));->TLE的罪魁祸首
		vis[x]=true;
		dfs(x,0);//大法师1
		maxx=-1;
		//memset(vis,false,sizeof(vis));->TLE的罪魁祸首
		vis[st]=true;
		dfs2(st,0);//大法师2
		vis2[x]=true;
		dis[x]=maxx;//将这棵树（这个集合）所拥有的直径记录下来
	}
	for(re int i=1;i<=q;i++){
		int opt=read(),x=read(),y;
		if(opt==1) printf("%d\n",dis[find(x)]);
		else{
			y=read();int xx=find(x),yy=find(y);
			if(xx==yy) continue;
			dis[yy]=max(max((dis[xx]+1)/2+(dis[yy]+1)/2+1,dis[xx]),dis[yy]);
			merge(x,y);
		}
	}
	return 0;
}
```

更好的体验：https://www.langlangago.xyz/index.php/archives/76/


---

## 作者：yty2010 (赞：1)

### 并查集模板题

#### 所用知识：[并查集](https://baike.baidu.com/item/%E5%B9%B6%E6%9F%A5%E9%9B%86/9388442?fr=ge_ala) [树的直径](https://blog.csdn.net/qq_42757965/article/details/82015905)

题目简述：在一棵有 $n$ 个节点 $m$ 条边的一棵或多棵树上进行两次操作：输出 $x$ 所在的树的直径:合并 $x,y$ 所在的树，使新树的直径最短。

### 第一部分:构建并查集和树

创建两个数组，$fa[i]$ 表示 $i$ 节点的父亲节点，vector 类型数组 $vec[i]$ 表示 $i$ 节点可以到达的节点。当 $y$ 节点与 $x$ 节点相连时，令 $y$ 的祖宗节点（最大的父亲节点）成为 $x$ 的祖宗节点的父亲。并且两点连边，即压入 vector 数组。

并查集解释：打个比方，每个帮派都有一个老大，老大即为父节点，并且最高级别的老大是整个帮派的标志人物，即祖父节点。

部分代码：
```
//定义
int fa[300005];
vector<int>vec[300005];
int find(int x)            //找祖宗
{
	if(fa[x]==x)                   
		return x;
	return fa[x]=find(fa[x]);//向上找，并把路上经过的节点都把fa[i]指向祖宗节点（路径压缩）
}
//main函数内
for(int i=1;i<=n;i++)
	fa[i]=i;        //一开始自己就是祖宗
for(int i=1;i<=m;i++)
{
	int x,y;
	cin>>x>>y;
	fa[find(x)]=find(y); //两个祖宗认亲
	vec[x].push_back(y); //连接路径
	vec[y].push_back(x);
}
```
### 第二部分：树的直径
最方便的首选 DFS，时间复杂度 $O(n)$，对于每一棵树，搜索两次：第一次从这棵树的任意一点出发（我选择从最大的祖宗节点出发）找到最远的那个节点，再由这个节点找它的最远点，即树的直径。（原理可以上网找，这里不做解释）

部分代码：
```
//定义
int maxn,maxs;  //maxn记录当前最大直径，maxs记录最远节点
int siz[300005];
//dfs
void dfs(int k,int sum,int pre)
{
	if(sum>maxn)  //更新最大直径
	{
		maxn=sum;
		maxs=k;
	}
	for(int i=0;i<vec[k].size();i++) //决定下一步
	{
		int v=vec[k][i];
		if(v==pre)
			continue;
		dfs(v,sum+1,k);
	}
}
//main
for(int i=1;i<=n;i++)
	{
		if(i==find(i))   //如果自己就是祖宗
		{
			maxs=i;
			maxn=0;
			dfs(i,0,0);   //找最远节点
			maxn=0;
			dfs(maxs,0,0); //从最远节点出发找它的最远节点
			siz[i]=maxn;  //记录直径
		}
	}
```
### 第三部分：处理操作
设每次操作输入的表示操作类型的数为 $t$。

当 $t=2$ 时，对两棵树进行合并
![](https://cdn.luogu.com.cn/upload/image_hosting/6w0794vs.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

一般情况下，分别取两棵树的中心位置进行连接（左图），红线为连接方案，很明显，连接后新的直径在两棵树上的长度分别都是 $\left\lceil \frac{siz[x]}2\right\rceil$，$x$ 表示每棵树的祖宗节点。

第二种情况（右图），连接后看似直径为5，实际上仍为左树的直径6，因此进行特判。

对了，由于题目不对合并后树的形状有要求，因此只需求出新直径并用并查集合并树就好了。

当 $t=1$ 时，输出 $size[x]$（$x$ 为输入的数字）就好了。

部分代码：
```
//合并
void merge(int x,int y)
{
	int lx=siz[x];
	int ly=siz[y];
	fa[x]=y;  //合并
	siz[y]=max(max(lx,ly),(lx+1)/2+(ly+1)/2+1); //max左侧为特判，右侧求新的直径
}
//main
while(q--)
	{
		int t;
		cin>>t;
		if(t==1)
		{
			int x;
			cin>>x;
			cout<<siz[find(x)]<<endl; //输出
		}
		else
		{
			int x,y;
			cin>>x>>y;
			int fx=find(x),fy=find(y); //找祖宗操作
			if(fx!=fy)
				merge(fx,fy);
		}
	}
```
最后上完整代码，总时间 $O(n)$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;

int maxn,maxs;
int siz[300005];
int fa[300005];
vector<int>vec[300005];
int find(int x)
{
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}
bool b[300005];

void dfs(int k,int sum,int pre)
{
	if(sum>maxn)
	{
		maxn=sum;
		maxs=k;
	}
	for(int i=0;i<vec[k].size();i++)
	{
		int v=vec[k][i];
		if(v==pre)
			continue;
		dfs(v,sum+1,k);
	}
}
void merge(int x,int y)
{
	int lx=siz[x];
	int ly=siz[y];
	fa[x]=y;
	siz[y]=max(max(lx,ly),(lx+1)/2+(ly+1)/2+1);
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		fa[find(x)]=find(y);
		vec[x].push_back(y);
		vec[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
	{
		if(i==find(i))
		{
			maxs=i;
			maxn=0;
			dfs(i,0,0);
			maxn=0;
			dfs(maxs,0,0);
			siz[i]=maxn;
		}
	}
	while(q--)
	{
		int t;
		cin>>t;
		if(t==1)
		{
			int x;
			cin>>x;
			cout<<siz[find(x)]<<endl;
		}
		else
		{
			int x,y;
			cin>>x>>y;
			int fx=find(x),fy=find(y);
			if(fx!=fy)
				merge(fx,fy);
		}
	}
	return 0;
}
```


---

## 作者：快斗游鹿 (赞：1)

## 思路

先考虑操作 $2$ 怎么解决。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/v0sdtrco.png)

标红的是两棵树原本的直径，蓝色的边是我们应当连的边。可以发现，若原来两棵树直径长度分别为 $w_x,w_y$，则合并后直径长度为 $\max(w_x,w_y,\left\lceil\dfrac{w_x}{2}\right\rceil+\left\lceil\dfrac{w_y}{2}\right\rceil+1)$。

得到这个结论后，整题的思路就很清晰了。首先先对每棵树处理出它的直径，然后合并两棵树可以使用并查集维护，操作 $1$ 直接查，操作 $2$ 用上述结论处理即可。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
struct edge{
	int to,nxt;
}e[N<<1];
int n,m,q,fa[N],cnt,head[N],w[N],dis[N],c;
bool flag[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int u,int f){//cout<<u<<endl;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)continue;
		w[v]=w[u]+1;
		if(w[v]>w[c])c=v;
		dfs(v,u);
	}
}
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void merge(int u,int v){
	fa[find(u)]=find(v);
} 
int main(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int u,v;u=read();v=read();//int w;w=read();
		add(u,v);add(v,u);
		merge(u,v);
	}//cout<<1;
	//for(int i=1;i<=n;i++)cout<<fa[i]<<endl;
	for(int i=1;i<=n;i++){
		if(i==fa[i]){//cout<<i<<endl;
			c=0;//cout<<i<<endl;
			w[1]=0;
			dfs(i,0);int t=c;
			//cout<<i<<endl;
			w[t]=0;c=0;
			dfs(t,0);
			dis[i]=w[c];
			//cout<<w[c]<<endl;
		}
	}//cout<<1;
	while(q--){
		int op;op=read();
		if(op==1){
			int x;x=read();
			printf("%d\n",dis[find(x)]);
		}
		else{
			int u,v;u=read();v=read();
			if(find(u)!=find(v)){
				int X=find(u),Y=find(v);
				dis[Y]=max((dis[X]+1)/2+(dis[Y]+1)/2+1,max(dis[X],dis[Y]));
				fa[X]=Y;
			}
		}
	}
	return 0;
}

```


---

## 作者：jun头吉吉 (赞：1)

[更神奇的阅读体验](https://chen-jia-liang.gitee.io/blog/2020/06/27/%E9%A2%98%E8%A7%A3-CF455C-%E3%80%90Civilization%E3%80%91/)
## 题意
给出一片森林，有以下两种操作：
1. 查询某棵树的直径
1. 把两颗数合并并使直径最小




## 题解
首先，对于两棵树，其直径分别是$\ ans_a\ \text{与}\ ans_b\ $，那么生成的数的直径最小为
$$\max(ans_a,ans_b)$$
简单来说，其直径不肯能越合并越小

在两棵树上分别选两点，那么此时数的直径还有可能变为 以$a$为根的树的深度以$b$为根的树的深度+1，就像下图一样
![一张奇奇怪怪的图片](https://cdn.luogu.com.cn/upload/image_hosting/d9l60429.png)

所以此时，我们希望$a,b$两点能够使树的深度最小

因此，我们让$a,b$都为直径的中点(如果取不到就取旁边两个),此时两边的深度都为$\lceil\frac {ans} 2\rceil$，最终合并时
$$ans'=\max\{ans_a,ans_b,\lceil\frac {ans_a} 2\rceil+\lceil\frac {ans_b} 2\rceil+1\}$$

至于合并的维护就很简单了，[并查集](https://www.luogu.com.cn/problem/P3367)，合并一下就ok了
## 代码
```cpp
 #pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[15];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
const int maxn=3e5+100;
int fa[maxn];
int getfa(int x){
	if(x==fa[x])return x;
	return fa[x]=getfa(fa[x]);
}
struct node{int v,nxt;}e[maxn<<1];
int tot=0,head[maxn];
inline void add(int u,int v){e[++tot]=(node){v,head[u]};head[u]=tot;}
int maxp,dis[maxn];
#define v e[i].v
void dfs(int u,int fa){
	//寻找最远的点
	if(dis[u]>dis[maxp])maxp=u;
	for(int i=head[u];i;i=e[i].nxt){
		if(v==fa)continue;
		dis[v]=dis[u]+1,dfs(v,u);
	} 
}
int n,m,q,x,y;
bool vis[maxn];
int c[maxn];
signed main(){
	in::read(n,m,q);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
		in::read(x,y),fa[getfa(x)]=getfa(y),add(x,y),add(y,x);
	for(int i=1;i<=n;i++)
		if(!vis[getfa(i)]){
			dis[maxp=0]=-1;dfs(i,0);
			int st=maxp;dis[maxp=0]=-1;dfs(st,0);
			c[getfa(i)]=dis[maxp]-dis[st],vis[getfa(i)]=true;
		}
	for(int i=1;i<=q;i++){
		int opt;in::read(opt);
		if(opt==1){
			in::read(x);
			out::write(c[getfa(x)]);out::putc('\n');
		}
		else{
			in::read(x,y);
			if(getfa(x)==getfa(y))continue;
			c[getfa(y)]=max((c[getfa(x)]+1)/2+(c[getfa(y)]+1)/2+1,max(c[getfa(x)],c[getfa(y)]));
			fa[getfa(x)]=getfa(y);
		}
	}
	out::flush();
	return 0;
}
```

---

## 作者：pipiispig (赞：1)

##
神奇的树的直径+并查集方法，不得不说CF的题真的很考察思维；

树的直径有2种求法，一种是2次bfs||dfs，第二种是树形DP,2种方法各有优缺点，第一种可以记录路径,也就是直径上有哪几个点，缺点是没法处理带有负边权的问题；而第二种方法的优缺点和第一种刚好相反，而有的毒瘤题刚好两种方法都要会所以尽量都掌握一下吧，我这个题的方法是树形DP（当然不是因为好写QwQ）;

这个是树形DP的一个模板
```
void tree_dp(int x)
{
	vis[x]=1;
	for(int i=head[x];i;i=nexts[i])
	{
		int v=ver[i];
		if(vis[v])continue;
		tree_dp(v);
		ans=max(ans,dp[x]+dp[v]+edge[i]);
		dp[x]=max(dp[x],dp[v]+edge[i]);
	}
}
```
这个是BFS的模板
```
void do_bfs(int x)
{
    memset(vis,0,sizeof(vis));
    queue<int>q;
    memset(d,0,sizeof(d));
    q.push(x);
    vis[x]=1;
    while(!q.empty())
    {
        w=q.front();q.pop();
        for(int i=head[w];i;i=nexts[i])
        {
            int y=ver[i];
            if(vis[y])continue;
            dis[y]=w;
            d[y]=d[w]+edge[i];
            q.push(y);
            vis[y]=1;
        }
    }
}
//分行(下面应该在主函数里头）
 maxx=0;
    do_bfs(1);
    for(int i=1;i<=n;i++)
    {	
        if(d[i]>maxx)
        {
            maxx=d[i];
            w=i;
        }
    }
    memset(dis,0,sizeof(dis));
    do_bfs(w);
    maxx=0;
    for(int i=1;i<=n;i++)
    {
        if(d[i]>maxx)
        {
            maxx=d[i];
            w=i;
        }
}
//2次bfs,第一次求出从任意节点可以到达的最远距离的点是哪一个，第二次从所求的最远距离的点再跑一次bfs,所能到达的最远距离的点的路径就是树的直径了;正确性很显然，可以自己画个图试试；
```
这个题的代码，其实只要会了树的直径和并查集，自己写并不难；
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int N=6*100000+5;

int n,m,p;

int head[N],ver[N],nexts[N],cnt=0,dis[N],dp[N],vis[N];

void add(int x,int y)
{
	ver[++cnt]=y,nexts[cnt]=head[x],head[x]=cnt;
}
int fa[N];
int vix[N];
int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}//简单的并查集;
int ans=0;
void tree_dp(int x)
{
	vis[x]=1;
	for(int i=head[x];i;i=nexts[i])
	{
		int y=ver[i];
		if(vis[y])continue;
		tree_dp(y);
		ans=max(ans,dp[x]+dp[y]+1);
		dp[x]=max(dp[x],dp[y]+1);
	}
}//树形DP求树的直径；
int main()
{
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=n;i++)fa[i]=i;//初始千万不能忘了；
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
		int xx=find(x),yy=find(y);
		if(xx!=yy)fa[xx]=yy;
	}
	for(int i=1;i<=n;i++)
	{
		int x=find(i);
		if(vix[x])continue;
		vix[x]=1;
		ans=0;
		tree_dp(x);
		dis[x]=ans;
	}
	for(int i=1;i<=p;i++)
	{
		int p;
		scanf("%d",&p);
		if(p==2)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			int xx=find(x),yy=find(y);
			if(xx!=yy)
			{
				fa[xx]=yy;
				dis[yy]=max(max(dis[xx],dis[yy]),(dis[xx]+1)/2+(dis[yy]+1)/2+1);//这个地方可以自己画画图，就可以得到了，转移方程就是这个喽；
			}
		}
		else
		{
			int z;
			scanf("%d",&z);
			int zz=find(z);
			cout<<dis[zz]<<endl;
		}
	}
}
```

---

## 作者：liu_yi (赞：1)

## 题目大意
给定一个由 $n$ 个点，$m$ 条边组成的森林，共有 $q$ 组询问。

1. 给定点 $x$，要求求出点 $x$ 所在树的直径。
2. 给定两点 $x$，$y$，要求在 $x$，$y$ 所在的树之间连一条边构成一颗新的树，并使得新树的直径最小。

## 解题思路
考虑预处理出每棵树的直径，联通性使用并查集判断，可是合并两棵树的时间复杂度是 $\Theta(n)$，会超时，需要优化。

我们思考一下，要想直径最小，肯定这条边得连接原来两颗树的直径，不然直径只会更大，所以两个直径都被分成了两段，要想最终直径最短，就得平均一下，让两段差值最小，所以选择直径的中点即可，最后的直径为 $\max(\lceil \frac{diameter_x}{2} \rceil+\lceil \frac{diameter_y}{2} \rceil+1,diameter_x,diameter_y)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,q,x,y,opt,fa[300010],head[300010],cnt,dp[300010][2],sum,tmp,diameter[300010];
bool vis[300010];
struct edge{
	int next,to;
}e[600010];
inline void add(register int u,register int v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
inline int find(register int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
inline void dfs(register int cur,register int fa){
	vis[cur]=1;
	for(int i=head[cur];i;i=e[i].next){
		register int y=e[i].to;
		if(y==fa)continue;
		dfs(y,cur);
		if(dp[y][0]+1>dp[cur][0]){
			dp[cur][1]=dp[cur][0];
			dp[cur][0]=dp[y][0]+1;
		}else if(dp[y][0]+1>dp[cur][1])dp[cur][1]=dp[y][0]+1;
	}
	if(dp[cur][1]+dp[cur][0]>diameter[find(cur)])diameter[find(cur)]=dp[cur][1]+dp[cur][0];
}
inline int read(){
	int step=1,s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
	    if(ch=='-')step=-1;
	    ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
	    s=(s<<1)+(s<<3)+ch-'0';
	    ch=getchar();
	}
	return step*s;
}
inline void print(register int x){
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
int main(){
	n=read(),m=read(),q=read();
	for(register int i=1;i<=n;i++)fa[i]=i;
	for(register int i=1;i<=m;i++){
		x=read(),y=read();
		add(x,y),add(y,x);
		x=find(x),y=find(y);
		if(x!=y)fa[y]=x;
	}
	for(register int i=1;i<=n;i++)if(!vis[i]&&fa[i]==i)dfs(i,0);
	while(q--){
		opt=read();
		if(opt==1)x=read(),print(diameter[find(x)]),puts("");
		else{
			x=read(),y=read();
			if(find(x)==find(y))continue;
			else{
				tmp=max({diameter[find(x)],diameter[find(y)],(diameter[find(x)]+1>>1)+(diameter[find(y)]+1>>1)+1});
				fa[find(x)]=find(y);
				diameter[find(x)]=tmp;
			}
		}
	}
	return 0;
}
```

---

## 作者：Wei_Han (赞：0)

考虑当不存在二操作时，一操作就是普通的求直径，用贪心或者 DP 都可以求。显然，在同一棵树中，直径长度是唯一的，那么我们可以用并查集维护是否在同一棵树，对于每一棵树求一遍中心即可，时间复杂度不会超过 $O(n)$。

再考虑添加了二操作后怎么做，首先，连接后的树的直径要么是原来两棵树直径的最大值，或者连接后出现的新直径，其次，一个比较明显的结论，如果是连边的情况，连的两个点一定分别在两棵树的直径上。那么现在问题就可以看做选两点连接两条链，使得其中的最长路径最短。在一条链上选点之后，可以看做将原链分为两部分，而做合并时，就是将两条链分别的更长部分相连。由于本题没有边权，那么每条边都是等价的，假设两棵树的直径大小分别为 $x$，$y$，那么连接后的最短直径就是 $\left \lceil \frac{x}{2} \right \rceil + \left \lceil \frac{y}{2} \right \rceil+1$ 也就是两条直径分别取一半，再加上连接的这条边，连接边时还是可以用并查集维护，就能保证复杂度了，对于操作后的直径，就是 $\max(x,y,\left \lceil \frac{x}{2} \right \rceil + \left \lceil \frac{y}{2} \right \rceil+1)$。

时间复杂度基本为 $O(n)$。
### Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ;-- i  )
#define min(a,b) (a>b?b:a)
#define bug(x,y) (x<1||y<1||x>15||y>15)
using namespace std;
typedef int ll;
typedef double db;
const int N=3e5+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll head[N],tot,n,rt,dist[N],xx,fa[N],m,q,d[N];
struct Graph{ll ver,nxt;}g[N<<1];
inline void add(ll x,ll y){g[++tot].ver=y,g[tot].nxt=head[x],head[x]=tot;}
inline void dfs(ll x,ll fa){
	for(ll i=head[x];i;i=g[i].nxt){
		ll y=g[i].ver;
		if(y==fa) continue;
		dist[y]=dist[x]+1;
		if(dist[y]>dist[rt]) rt=y;
		dfs(y,x);
	}
}
inline ll Find(ll x){return (x==fa[x]?x:fa[x]=Find(fa[x]));}
inline void Link(ll x,ll y){ll xx=Find(x),yy=Find(y);fa[xx]=(fa[xx]==yy?fa[xx]:yy);}
map<ll,ll> mp;
signed main(){
	read(n);read(m),read(q);
	fo(1,i,n) fa[i]=i;
	fo(1,i,m){ll u,v,w;read(u),read(v);add(u,v),add(v,u);Link(u,v);}
	fo(1,i,n){
		if(i==fa[i]){
			if(mp[Find(i)]>0) d[i]=mp[Find(i)];
			else{
				rt=0;dist[i]=0;
				dfs(i,0);dist[rt]=0;
				dfs(rt,0);
				mp[i]=dist[rt];
				d[i]=mp[i];
			}
		}
	}
	fo(1,i,q){
		ll op,x,y;
		read(op);read(x);
		if(op==1) wr(d[Find(x)]),pr;
		else{
			read(y);
			ll fax=Find(x),fay=Find(y);
			if(fax==fay) continue;
			Link(fax,fay);
			d[Find(fax)]=max(max(d[fax],d[fay]),((d[fax]+1)>>1)+((d[fay]+1)>>1)+1);
			
		}
	}
	return 0;
}
``````

---

## 作者：Bpds1110 (赞：0)

我们先考虑求给出的每一棵树的直径，可以用树形 DP 求解。$d_i$ 表示以 $i$ 为根节点的树的直径。

我们用并查集维护一棵树的根节点。对于每次合并两棵树，要求新的直径最小，最优情况是连接两棵树**最长直径的中点**，因为这样就避免了一条直径选中过长部分的情况。还有一种特殊情况，就是原本两棵树的直径的最大值大于新的最大值，从而继续成为新直径。接着合并两棵树即可。

还要注意，求一棵树直径的一半时向上取整。可自行画图证明。

```cpp
#include <bits/stdc++.h>
typedef long long ll;

ll max(ll x, ll y) { return x > y ? x : y; }

namespace FastIO {
	ll read() {
		ll res = 0; bool flag1 = 0, flag2 = 0; char ch = getchar();
		for (; ! isdigit(ch); ch = getchar()) flag1 |= (ch == '-');
		for (; isdigit(ch); ch = getchar())
			res = (res << 1) + (res << 3) + (ch ^ 48);
		return (flag1 ? -res : res);
	}
	void write(ll tmp) {
		std::vector <int> vec;
		if (tmp == 0) return putchar('0'), void();
		if (tmp < 0) putchar('-'), tmp = abs(tmp);
		for (; tmp; tmp /= 10) vec.push_back(tmp % 10 + '0');
		for (int i = vec.size() - 1; i >= 0; -- i) putchar(vec[i]);
		return void();
	}
	void IOS() {
		std::ios::sync_with_stdio(false);
		return void();
	}
	void FastCin() {
		std::cin.tie(nullptr);
		std::cout.tie(nullptr);
		return void();
	}

}
//using namespace FastIO;

const int N = 3e5 + 100;
ll anc[N], dp1[N], dp2[N], d[N], len, n;
std::vector <ll> G[N];

ll find(ll tmp) {
	if (anc[tmp] == tmp) return tmp;
	else return anc[tmp] = find(anc[tmp]);
}

// dp1[i] 记录 i 的最长的儿子，dp2[i] 记录 i 的第二长的儿子。每次求出最大直径。

void dfs(ll u, ll fl) {
	for (ll i = 0; i < G[u].size(); ++ i) {
		ll v = G[u][i];
		if (v == fl) continue ;
		dfs(v, u);
		int t = dp1[v] + 1;
		if (t > dp1[u]) dp2[u] = dp1[u], dp1[u] = t;
		else if (t > dp2[u]) dp2[u] = t;
	}
	len = max(len, dp1[u] + dp2[u]);
	return void();
}

int main() {

//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);

	FastIO::FastCin; FastIO::IOS();

	int m = 0, q = 0; std::cin >> n >> m >> q;
	for (int i = 1; i <= n; ++ i) anc[i] = i;
	while (m --> 0) {
		ll x = 0, y = 0;
		std::cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
		int u = find(x), v = find(y);
		anc[u] = v;
	}
	for (ll i = 1; i <= n; ++ i) {
		if (anc[i] != i) continue ;
		len = 0;
		dfs(i, 0);
		d[i] = len;
	}
	while (q --> 0) {
		ll op = 0, x, y;
		std::cin >> op >> x;
		ll u = find(x);
		if (op == 1) {
			std::cout << d[u] << "\n";
			continue ;
		}
		std::cin >> y;
		ll v = find(y);
		if (u == v) continue ;
		int nowd = max(d[u], d[v]);
		nowd = max(nowd, (d[u] + 1) / 2 + (d[v] + 1) / 2 + 1);
		anc[u] = v; d[v] = nowd; d[u] = 0;
	}
	

	return 0;
}

```


---

## 作者：modfisher (赞：0)

# 思路
本文中所涉及到的路径长度（除了最后的答案）都是指路径上点的数量。~~问就是一开始看错题了。~~

先考虑一下操作 2，将哪两个节点相连，才会使直径最小呢？

容易想到，若将 $u$、$v$ 相连，要使直径最小，应满足：以 $u$ 为根时，其叶节点的深度中的最大值最小，$v$ 同理。

取哪个点最优呢？显然是取直径的中点最优。设直径的中点为 $m$，直径为 $d$，则以 $m$ 为根时叶节点的深度最大为 $\frac{d}{2}+1$。因为若是存在另一个叶节点的深度大于 $\frac{d}{2}+1$，则树中必定存在一条更长的简单路径，与我们的假设矛盾。接着，对于除 $m$ 外其他任意节点 $n$，以其为根时，必定存在一条从根到叶子的路径为 $n\to m\to$ 直径的某一端，它的长度必定长于路径 $m\to$ 直径的某一端，至此，我们证明了连接时应取直径中点相连。

那么问题就简单了，我们甚至用不上一棵真实的树，先预处理出森林中的每一棵树的直径，计算以直径中点为根时其最大叶节点深度（就是 $\frac{d}{2}+1$），在连接时，采用并查集来记录某一个节点属于哪一棵树。接下来分情况讨论：

设输入为 $x$、$y$，某棵树的最大深度为 $mxd[i]$，则：

当 $mxd[find(y)]<mxd[find(x)]$ 时，树的直径可能会被更新，所以尝试将 $mxd[find(x)]+mxd[find(y)]$ 与 $x$ 所在树的直径进行比较，如果大于，则更新 $x$ 所在树的直径，并将 $x$、$y$ 所在的树相连。

当 $mxd[find(y)]=mxd[find(x)]$ 时，仍然尝试更新树的直径，并将 $mxd[find(x)]$ 加上一。原因可以请读者们画画图，尝试连接一下，自然就知道了。

当 $mxd[find(y)]>mxd[find(x)]$ 时，直接交换 $x$、$y$，就转换成了第一种情况。

输出时，直接输出直径。~~然后我因为看错题了所以要减一~~。总时间复杂度 $O((n+q)\alpha(n))$。
# 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 5;

struct node{
	int x, l;
};
int head[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
int fa[maxn], vis[maxn], d[maxn], mxd[maxn];
queue<node> q;
vector<int> vv[maxn];

void add(int u, int v){
	nxt[++ cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt;
}
int find(int x){
	if(x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void join(int x, int y){
	if(find(x) != find(y)) fa[find(y)] = find(x);
}
void bfs(int x){
	q.push((node){x, 1});
	vis[x] = 1;
	int maxi = 0, max1 = 0;
	while(!q.empty()){
		int x = q.front().x, l = q.front().l;
		if(l > max1){
			max1 = l;
			maxi = x;
		}
		q.pop();
		for(int i = head[x]; i; i = nxt[i]){
			int j = to[i];
			if(vis[j]) continue;
			q.push((node){j, l + 1});
			vis[j] = 1;
		}
	}
	q.push((node){maxi, 1});
	max1 = 0;
	for(int i = 0; i < vv[find(x)].size(); i ++){
		vis[vv[find(x)][i]] = 0;
	}
	vis[maxi] = 1;
	while(!q.empty()){
		int x = q.front().x, l = q.front().l;
		max1 = max(max1, l);
		q.pop();
		for(int i = head[x]; i; i = nxt[i]){
			int j = to[i];
			if(vis[j]) continue;
			q.push((node){j, l + 1});
			vis[j] = 1;
		}
	}
	d[find(x)] = max1;
}

int main(){
	int n, m, q;
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= n; i ++) fa[i] = i;
	for(int i = 1; i <= m; i ++){
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v);
		add(v, u);
		join(u, v);
	}
	for(int i = 1; i <= n; i ++){
		vv[find(i)].push_back(i);
	}
	for(int i = 1; i <= n; i ++){
		if(!vis[i]){
			bfs(i);
			mxd[find(i)] = d[find(i)] / 2 + 1;
		}
	}
	while(q --){
		int op, x, y;
		scanf("%d %d", &op, &x);
		if(op == 1){
			printf("%d\n", d[find(x)] - 1);
		}else{
			scanf("%d", &y);
			if(find(x) == find(y)) continue;
			if(mxd[find(x)] < mxd[find(y)]) swap(x, y);
			if(mxd[find(y)] < mxd[find(x)]){
				d[find(x)] = max(d[find(x)], mxd[find(x)] + mxd[find(y)]);
				join(x, y);
			}else{
				d[find(x)] = max(d[find(x)], mxd[find(x)] + mxd[find(y)]);
				mxd[find(x)] ++;
				join(x, y);
			}
		}
	}
	return 0;
} 
```


---

## 作者：Rushroom (赞：0)

[题目传送门](https://codeforces.com/contest/455/problem/C)


> 给出一个有 $n$ 个点，$m$ 条边的森林，有 $q$ 次操作。操作有两种：
>
> 1. 查询点 $x$ 所在树的直径
> 2. 要求添加一条边，合并点 $x$ 和 $y$ 所在的两棵树，使合并后树的直径最小。（如果 $x$ 和 $y$ 在同一棵树中则不用操作）
>
> $n,m,q \le 3\cdot 10^5$

设添加的边的两个端点为 $u,v$，两棵树直径分别为 $d_1,d_2$。

使合并后树的直径最小，也就是使经过 $u,v$ 的最长路径最短，这条路径的长度为 $dis(u,u')+dis(v,v')+1$，其中 $u',v'$ 分别是合并前两棵树中的点。

考虑最小化 $dis(u,u')$，那么就是要在找到一个 $u$，使得它到树中其他点距离的最大值最小。

这里有一个经典结论，从一个点到树中其他的最长路径，另一端点一定是这棵树直径的一个端点。所以我们选的 $u$ 一定是直径的中点（若直径为奇数则中间两个点任取一个）。因此 $\max(dis(u,u'))=\left\lceil\dfrac{d_1}{2}\right\rceil$。

所以，合并后树的最小直径就是 $\max\left(d1,d2,\left\lceil\dfrac{d_1}{2}\right\rceil+\left\lceil\dfrac{d_2}{2}\right\rceil\right)$。

用并查集合并即可。

## Code

```cpp
int n, m, q, op, u, v;
vector<int> g[N];
int fa[N];
int Find(int i) {
	if(fa[i] == i) return i;
	else return fa[i] = Find(fa[i]);
}
int mx, id;
int d[N];
void dfs(int x, int f, int cnt) {
	if(cnt > mx) mx = cnt, id = x;
	for(int y: g[x]) {
		if(y == f) continue;
		dfs(y, x, cnt + 1);
	}
}
int div2(int x) {
	if(!x) return 0;
	else return (x - 1) / 2 + 1;
}
void solve() {
	cin >> n >> m >> q;
	rep(i, n) fa[i] = i;
	rep(i, m) {
		cin >> u >> v;
		u--, v--;
		g[u].pb(v), g[v].pb(u);
		fa[Find(u)] = Find(v);
	}
	memset(d, -1, sizeof(d));
	rep(i, n) if(d[Find(i)] == -1) {
		mx = -1;
		dfs(i, -1, 0);
		mx = -1;
		dfs(id, -1, 0);
		d[Find(i)] = mx;
	}
	while(q--) {
		cin >> op;
		if(op == 1) {
			cin >> u;
			u--;
			cout << d[Find(u)] << '\n';
		}
		else {
			cin >> u >> v;
			u--, v--;
			if(Find(u) == Find(v)) continue;
			else {
				d[Find(v)] = max(max(d[Find(u)], d[Find(v)]), div2(d[Find(u)]) + div2(d[Find(v)]) + 1);
				fa[Find(u)] = Find(v);
			}
		}
	}
}
```


---

## 作者：Yansuan_HCl (赞：0)

查询一个点的直径不难，我们考虑怎样合并两棵树使得新树的直径最小。

记两棵树分别为 $i, j$，直径为 $d_i, d_j$。因为原来两颗树存在，所以直径至少是 $\max{\{d_i, d_j\}}$（0）。

假设连接点对 $(u, v)$，那么根据直径的性质（一个点能到达最远的点是直径的一个端点），通过这条边的最大路径即为 **$u$ 到树 $i$ 直径两端点距离的较大值（1）** + **$v$ 到树 $j$ 直径两端点距离的较大值（2）** + 1。

因此我们可以分别最小化（1）（2）的值。

假如 $u$ 不在直径上，那 $u$ 到直径两端点的路径一定是经过一些边到达直径的链上再走到直径，一定不优。因此 $u$ 要在直径上。显然，当 $u$ 是直径的中点的时候（1）式最小。$v$ 同理。

当 $d_i$ 为奇数时很好处理，偶数时（1）式则会是 $\lceil d_i / 2 \rceil$ (需要取较长一端）。$v$ 同理。

最终答案就是 $\lceil d_i / 2 \rceil + \lceil d_j / 2 \rceil + 1$。
当 $d_i = d_j$ 且是奇数时，有更优的连法（一条上取整，一条下取整，再 +1），然而长度也等于 $d_i$。

最终取个 max 即可。

[丑陋的代码](https://www.luogu.com.cn/paste/mn4y2uzs)

---

## 作者：BrotherCall (赞：0)

以下的 “ 树 $x$ ”均代指 $x$ 节点所在的树。

### 题意：

$n$ 个点 $m$ 条边的一个森林，共 $q$ 次询问，做以下两种操作：

1.输出 树 $x$ 的直径。

2.将 树 $x$ 和 树 $y$ 的某两个点之间连边形成新树，要求这个新树的直径最小（若两者本来就在同一棵树中则忽略此操作）。

$1 \leqslant m < n \leqslant 3 \cdot 10^5$

$1 \leqslant q \leqslant 3 \cdot 10^5$

### 解法：

#### 暴力解法：

首先我们考虑暴力做法：

关于判断两个点是否在一棵树中，很明显用并查集维护。

预处理：每棵树用两次 dfs 求树的直径，时间复杂度为 $O(n)$ 。

对于操作一：可以用两次 dfs 求树的直径 ，单次复杂度为 $O(n)$ ，执行 $q$ 次复杂度为 $O(nq)$ 。

对于操作二：枚举两棵树中的每一个节点，连边之后求树的直径，找到最小直径的连边方式。单次复杂度为 $O(n^3)$ ， 执行 $q$ 次复杂度为 $O(n^3q)$ 。

总复杂度为 $O(n^3q)$ 。

#### 优化算法：

观察数据范围不难发现这题需要在 $O(n)$ 或 $O(n\log n)$ 的复杂度内完成，$O(n\sqrt{n})$ 就基本卡不过了。

所以我们需要找到暴力算法的瓶颈：

预处理是 $O(n)$ 的，复杂度很优秀，所以瓶颈处于两种操作。

目标很明确了：如何快速算出一棵树的直径，并找到两棵树合并后直径最小的连接方式。

我们不妨把两棵树的直径抽离出来分析，观察下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/aowbesq7.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这是一棵直径为 3 与一棵直径为 2 的两棵巨树。

手玩这个小样例，不难发现当树的直径为 $siz$ 时，第 $i$ 个点可以把一棵树的直径划分为 $i - 1$ 和 $siz - i + 1$ 两部分。

所以树直径的公式就为 $\max(siz_1 , siz_2 , \min(\max(i - 1 , siz_1 - i + 1) + \max(j - 1 , siz_2 - j + 1) + 1))$ 。

对这个式子进行分析，发现当 $i , j$ 都取直径中点的时候新树直径最小，此时新树的直径的公式为 $\max(siz_1 , siz_2 , \lceil \frac{siz_1}{2} \rceil +\lceil \frac{siz_2}{2} \rceil + 1)$ 。

到此为止，我们就找到了操作 1 和 2 的 $O(1)$ 处理方式了：用 $str[i]$ 表示 树 $i$ 的直径大小，然后动态使用公式维护新树的直径即可。

[Code](https://www.luogu.com.cn/paste/wa4y4sxd)

#### 时间复杂度：

并查集带 $\log n$ 的复杂度，其他的单次操作复杂度 $O(1)$ ，操作次数为 $q$ 次。

总复杂度为 $O(q \log n)$ 。

#### 总结：

这道题是很常规的森林中两棵树的合并问题，关键在于发掘合并的性质。

虽然是蓝题但是算比较简单的那一类，完全可以放在提高组第一题。这题应该是和廊桥分配难度差不多。

还有种树的合并方式叫启发式合并，也很有意思，这里只是提一下不多做赘述。

---

## 作者：FutaRimeWoawaSete (赞：0)

我们首先考虑如何做操作 2 。                  

我们考虑一下我们可以怎么转移我们的直径，假如得到两个子树的直径及直径端点信息以及得到两个连接点的话，我们就可以把子树直径端点分别到这两个点的距离拿出来交叉相加，然后再和原来两个子树的直径比较就可以转移了。               

令第一个子树 $A$ 的直径端点为 $a , b$ , 另一个子树 $B$ 直径端点为 $c , d$ ，连接的点是 $u , v$ ，写成形象点的数学式子就是：          

- $dist_{now} = max(max(dist_{a,u} , dist_{b ,u}) + max(dist_{c , v} + dist_{d , v}) , len_A,len_B)$ 


然后我们考虑一下怎么可以连直径最小的情况，其实就是在各自直径上找一个点 $k$ 使得 $max(dist_{a , k} , dist_{b , k})$ 的值最小然后连接。                

这里可以反证，如果不这么选择的话那么必然连出一条比这么选择连出来不更短的一条直径。        

并且我们知道，得到的新树的 $k$ 点必然也是这两个点的其中一个，毕竟如果选择其它点的话都会使得新树 $max(dist_{a , k} , dist_{b , k})$ 的值必定比选这两个点更好情况下那个点的值更劣，所以分类讨论一下即可在 $O(1)$ 时间复杂度转移。                         

接着初始化时直接跑树的直径就好了，稍微有点难写所以注重一下细节。      
```cpp
/*
考虑维护一棵树的以及点min{max(dis(u , a)) + dis(u , b)}
我们合并完后直接看两个点哪个点更近就好了  
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 3e5 + 5;
int n,m,fa[Len],q;
struct node
{
	int u,v,pos,disu,disv,len;
	node(){u = v = pos = disu = disv = len = 0;}
	node(int U,int V,int POS,int DISU,int DISV,int LEN){u = U , v = V , pos = POS , disu = DISU , disv = DISV , len = LEN;}
}tree[Len];
void makeSet(int x){for(int i = 1 ; i <= x ; i ++) fa[i] = i;}
int findSet(int x){return fa[x] == x ? fa[x] : fa[x] = findSet(fa[x]);}
void unionSet(int x,int y)
{
	int u = findSet(x) , v = findSet(y);
	if(u == v) return;
	fa[v] = u;	
	//printf("###%d %d %d %d %d %d\n",tree[u].u,tree[u].v,tree[u].pos,tree[u].disu,tree[u].disv,tree[u].len);
	//printf("###%d %d %d %d %d %d\n",tree[v].u,tree[v].v,tree[v].pos,tree[v].disu,tree[v].disv,tree[v].len);
	if(tree[u].disu < tree[u].disv) swap(tree[u].disu , tree[u].disv) , swap(tree[u].u , tree[u].v);
	if(tree[v].disu < tree[v].disv) swap(tree[v].disu , tree[v].disv) , swap(tree[v].u , tree[v].v);
	if(tree[u].disu + tree[v].disu + 1 < tree[u].len || tree[u].disu + tree[v].disu + 1 < tree[v].len)
	{
		if(tree[u].len < tree[v].len) tree[u] = tree[v];
	}
	else
	{
		if(max(tree[v].disu + 1 , tree[u].disu) < max(tree[u].disu + 1 , tree[v].disu)) tree[u] = node(tree[u].u , tree[v].u , tree[u].pos , tree[u].disu , tree[v].disu + 1 , tree[u].disu + tree[v].disu + 1);
		else tree[u] = node(tree[u].u , tree[v].u , tree[v].pos , tree[u].disu + 1 , tree[v].disu , tree[u].disu + tree[v].disu + 1);
	}
	//printf("%d %d %d %d %d %d\n",tree[u].u,tree[u].v,tree[u].pos,tree[u].disu,tree[u].disv,tree[u].len);
	tree[v] = node(0 , 0 , 0 , 0 , 0 , 0);
} 
int head[Len],cnt,Fa[Len],dis[Len];
struct Node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
int maxu,maxdis;
bool flag[Len];
void dfs(int x,int f,int Val,int root,bool ort)
{
	flag[x] = ort;
	fa[x] = root;
	Fa[x] = f;
	if(Val > maxdis)
	{
		maxu = x;
		maxdis = Val;
	}
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs(to , x , Val + 1 , root , ort);
	}
}
int main()
{
	scanf("%d %d %d",&n,&m,&q);
	for(int i = 1 ; i <= n ; i ++) tree[i] = node(i , i , i , 0 , 0 , 0);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);	
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		if(!flag[i])
		{
			maxu = i , maxdis = 0;
			dfs(i , 0 , 0 , i , 0);
			tree[i].u = maxu;
			dfs(maxu , 0 , 0 , i , 1);
			tree[i].v = maxu;
			tree[i].len = maxdis;
			int Up = tree[i].len >> 1;
			while(Up) maxu = Fa[maxu] , Up --;
			tree[i].pos = maxu;
			tree[i].disv = (tree[i].len >> 1) , tree[i].disu = tree[i].len - (tree[i].len >> 1);
		}
	}
	//for(int i = 1 ; i <= n ; i ++) printf("%d %d %d %d %d %d\n",tree[i].u,tree[i].v,tree[i].pos,tree[i].disu,tree[i].disv,tree[i].len);
	for(int i = 1 ; i <= q ; i ++) 
	{
		int op,x,y;scanf("%d",&op);
		if(op == 1) 
		{
			scanf("%d",&x);
			int Fat = findSet(x);
			printf("%d\n",tree[Fat].len);
		}
		else
		{
			scanf("%d %d",&x,&y);
			unionSet(x , y);
		}
	}
	return 0;
}
```

---

## 作者：ModestCoder_ (赞：0)

对于两个连通块连起来，肯定是在两个直径中点之间连一条边使得新的直径最短

并查集维护连通性，同时记录连通块的直径大小

令两个连通块的直径分别为$len_{s1}>len_{s2}$

则新的直径是$max(len_{s1},\frac{len_{s1}+1}{2}+\frac{len_{s2}+1}{2}+1)$

除法是上取整的意思

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 300010
using namespace std;
struct Edge{
	int to, next;
}edge[maxn << 1];
int num, head[maxn], rt, Max;
int n, m, q, f[maxn], len[maxn];

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

void addedge(int x, int y){ edge[++num] = (Edge){y, head[x]}, head[x] = num; }
int getfa(int k){ return f[k] == k ? k : f[k] = getfa(f[k]); }

void dfs(int u, int pre, int s){
	if (s > Max) Max = s, rt = u;
	for (int i = head[u]; i; i = edge[i].next){
		int v = edge[i].to;
		if (v != pre) dfs(v, u, s + 1);
	}
}

void merge(int x, int y){
	int s1 = getfa(x), s2 = getfa(y);
	if (len[s1] < len[s2]) swap(s1, s2);
	f[s2] = s1, len[s1] = max(len[s1], (len[s1] + 1) / 2 + (len[s2] + 1) / 2 + 1);
}

int main(){
//	freopen("1.txt", "r", stdin);
//	freopen("21.out", "w", stdout);
	n = read(), m = read(), q = read();
	for (int i = 1; i <= n; ++i) f[i] = i;
	while (m--){
		int x = read(), y = read(), s1 = getfa(x), s2 = getfa(y);
		addedge(x, y), addedge(y, x);
		f[s1] = s2;
	}
	for (int i = 1; i <= n; ++i){
		int x = getfa(i);
		if (!len[x]){
			rt = 0, Max = 0;
			dfs(i, 0, 0);
			Max = 0;
			dfs(rt, 0, 0);
			len[x] = Max;
		}
	}
	while (q--){
		int opt = read();
		if (opt == 1) printf("%d\n", len[getfa(read())]); else{
			int x = read(), y = read();
			if (getfa(x) != getfa(y)) merge(x, y);
		}
	}
	return 0;
}
```


---

## 作者：Rusalka (赞：0)

~~又水了一道紫题~~

双倍经验：[P2195 HXY造公园](https://www.luogu.com.cn/problem/P2195)
~~连样例都一样~~

### 一. 题意

原题连接：[CF455C Civilization](https://www.luogu.com.cn/problem/CF455C)

- 给定 $n$ 个点 $m$ 条边的森林，一共 $q$ 次操作，每次操作包括以下两种：  

1. `1 x` ：输出点 $x$ 所在的树的直径。  

2. `2 x y` ：用一条边连接点 $x$ 和 $y$ 所在的树，并使新树的直径最小。若点 $x$，$y$ 已连通则忽视该操作。

- $1 \le m \lt n \le 3 \times10^{5} , 1 \le q \le 3\times10^{5}$

### 二. 分析与解答

首先显然需要预处理初始时森林中每棵树的直径。  
  
这个可以用树形dp $O(n)$ 解决。

具体就是记录每个结点子树中到该结点的最大长度和次大长度（不能在同一棵子树中），然后用最大长度和次大长度的和更新当前直径。

如果上面的没看懂可以看代码。

在这里，可以使用并查集维护树的连通，并且用并查集的根存储这棵树的直径长度。至于为什么，等您看完后面就知道啦。

---

然后考虑如何处理两个操作。  
  
首先观察操作 2，要求维护集合的连通性，那么很容易想到并查集。

那么不妨用并查集的根来代表这棵树。

记 $val$ 表示连通块中的直径长度。

在合并两棵树 $x$，$y$ 时，这里不妨直接设 $x$、$y$ 都为树根。由于要求新的直径最小，所以容易想到取两棵树的直径的中点连边。这样新树直径的长度就为：
$$ max(val_x,val_y,\lceil\dfrac{val_x}{2}\rceil + \lceil\dfrac{val_y}{2}\rceil+1) $$

也就是在原来 $x$ 的直径和 $y$ 的直径以及新产生的跨越两棵树的最长路径中取最大值。

在最后一个式子中，上取整表示取较长的一段，因为要算上新连上的边所以要 +1 。

---

接下来再看操作 1，就会发现只需要输出处理好的 $x$ 所在的连通块直径即可。

就做完了。

### Code

```cpp
#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

const int MAXN = 300010;

int n, m, q;

struct edge{
	int ne, to;
	edge(int N=0,int T=0):ne(N),to(T){}
}e[MAXN<<1];
int fir[MAXN], num = 0;
inline void join(int a, int b)
{
	e[++num] = edge(fir[a], b);
	fir[a] = num;
}

int f[MAXN], val[MAXN];
int find(int x)
{
	return f[x] == x ? x : f[x] = find(f[x]);
}
inline void merge(int x, int y) // 合并两棵树 
{
	int fx = find(x), fy = find(y);
	if(fx == fy) return ;
	val[fx] =  max((val[fx]+1)/2+(val[fy]+1)/2+1, max(val[fx], val[fy]));
	// 更新新的直径 
	f[fy] = fx;
}

int maxx[MAXN][2];
void dfs(int u, int fa, int rt) // 处理直径 
{
	maxx[u][0] = maxx[u][1] = 0;
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		if(v == fa) continue;
		dfs(v, u, rt);
		int now = maxx[v][0] + 1;
		if(now > maxx[u][1])
		{
			if(now > maxx[u][0])
			{
				maxx[u][1] = maxx[u][0];
				maxx[u][0] = now;
			}
			else maxx[u][1] = now;
		}
	}
	val[rt] = max(val[rt], maxx[u][0] + maxx[u][1]);
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
		f[i] = i;
	for(int i=1;i<=m;i++)
	{
		int a, b;
		scanf("%d%d",&a,&b);
		join(a, b);
		join(b, a);
		int fx = find(a), fy = find(b);
		if(fx != fy) f[fx] = fy;
	}
	for(int i=1;i<=n;i++)
		if(f[i] == i)
			dfs(i, 0, i);
	while(q--)
	{
		int opt, x, y;
		scanf("%d",&opt);
		if(opt == 1) 
		{
			scanf("%d",&x);
			printf("%d\n",val[find(x)]);
		}
		else 
		{
			scanf("%d%d",&x,&y);
			merge(x, y);
		}
	}
	return 0;
}
```


---

## 作者：览遍千秋 (赞：0)

## 问题描述

[LG-CF455C](https://www.luogu.org/problem/CF455C)

---

## 题解

首先，题目给出了 $m$ 条边，对这 $n$ 个点， $m$ 条边组成的森林，跑出每棵树的直径，同时使用并查集维护树的连通性。

考虑合并两棵树的情况：设这两棵树的代表元为 $u,v$ ，这棵树的直径有三种来源：

- $u$ 这棵树的直径

- $v$ 这棵树的直径

- 穿过 $u,v$ 合并边的一条路径

$u,v$ 两棵树的直径是已知的，所以我们只需要考虑最小化第三种情况。

设树 $u,v$ 合并时的点为 $rt_u,rt_v$ ，此时第三种情况的值为 $\frac{maxdis_{rt_u}}{2}+\frac{maxdis_{rt_v}}{2}+1$

显然，为了最小化两个 $maxdis$ ，这两个点选取的一定是原来两棵树直径的中点。

---

## $\mathrm{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch>'9'||ch<'0')) ch=getchar();
	if(ch=='-') ch=getchar(),fh=-1;
	else fh=1;
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	x*=fh;
}

const int maxn=300007;
const int maxm=600007;

int n,m,T;
vector<int> G[maxn];
int fa[maxn];

int bel[maxn],cnt;

void add(int x,int y){
	G[x].push_back(y);
}

int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

int dep[maxn],ans[maxn];

int pos,lst;

void merge(int x,int y){
	if(find(x)!=find(y)) fa[fa[x]]=fa[y];
}

void dfs(int x,int col,int dis){
	if(bel[x]==col) return;
	if(dis>=lst) lst=dis,pos=x;
	bel[x]=col;
	for(int i=0;i<G[x].size();i++){
		int y=G[x][i];
		merge(x,y);
		dfs(y,col,dis+1);
	}
}

void Getmax(){
	int mx=-1;
	for(int i=1;i<=n;i++){
		if(dep[i]>mx) mx=dep[i],pos=i;
	}
}

void cz1(){
	int x;read(x);
	printf("%d\n",ans[find(x)]);
}

void cz2(){
	int x,y;read(x);read(y);
	int xx=find(x),yy=find(y);
	if(xx==yy) return;
	fa[xx]=yy;
	ans[yy]=max(ans[xx],max(ans[yy],(ans[xx]+1)/2+(ans[yy]+1)/2+1));
}

void preprocess(){
	for(int i=1;i<=n;i++) fa[i]=i;
}

int main(){
	read(n);read(m);read(T);
	
	preprocess();
	
	for(int i=1,x,y;i<=m;i++){
		read(x);read(y);
		add(x,y);add(y,x);
	}
	
	for(int i=1;i<=n;i++){
		if(bel[i]) continue;
		lst=0,pos=i;
		dfs(i,i,0);
		lst=0;
		dfs(pos,pos,0);
		ans[find(i)]=lst;
	}
	
	int op;
	while(T--){
		read(op);
		if(op==1) cz1();
		else cz2();
	}
	
	return 0;
}
```

---

