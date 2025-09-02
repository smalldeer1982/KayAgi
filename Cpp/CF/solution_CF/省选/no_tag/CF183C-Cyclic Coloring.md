# Cyclic Coloring

## 题目描述

You are given a directed graph $ G $ with $ n $ vertices and $ m $ arcs (multiple arcs and self-loops are allowed). You have to paint each vertex of the graph into one of the $ k $ $ (k<=n) $ colors in such way that for all arcs of the graph leading from a vertex $ u $ to vertex $ v $ , vertex $ v $ is painted with the next color of the color used to paint vertex $ u $ .

The colors are numbered cyclically $ 1 $ through $ k $ . This means that for each color $ i $ $ (i&lt;k) $ its next color is color $ i+1 $ . In addition, the next color of color $ k $ is color $ 1 $ . Note, that if $ k=1 $ , then the next color for color $ 1 $ is again color $ 1 $ .

Your task is to find and print the largest possible value of $ k $ $ (k<=n) $ such that it's possible to color $ G $ as described above with $ k $ colors. Note that you don't necessarily use all the $ k $ colors (that is, for each color $ i $ there does not necessarily exist a vertex that is colored with color $ i $ ).

## 说明/提示

For the first example, with $ k=2 $ , this picture depicts the two colors (arrows denote the next color of that color).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/5fc25b3e1baecb0cc286fd1a3b08fbd0e1f5c4eb.png)With $ k=2 $ a possible way to paint the graph is as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/8c36834819409d82c5c1224a04a2fcf860f0bd11.png)It can be proven that no larger value for $ k $ exists for this test case.

For the second example, here's the picture of the $ k=5 $ colors.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/6fb597ece64567e61db8b5ed6d1b98f36788eb3f.png)A possible coloring of the graph is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/ddb3d14ab97f674110eb33ef458d1f97e9ea4ac4.png)For the third example, here's the picture of the $ k=3 $ colors.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/a77c6758c9d6428611a620004da04ba72186df31.png)A possible coloring of the graph is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF183C/5dc5850b22b6955a11cc6496cce3c42d93bc37c7.png)

## 样例 #1

### 输入

```
4 4
1 2
2 1
3 4
4 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 2
1 4
2 5
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4 5
1 2
2 3
3 1
2 4
4 1
```

### 输出

```
3
```

## 样例 #4

### 输入

```
4 4
1 1
1 2
2 1
1 2
```

### 输出

```
1
```

# 题解

## 作者：姬小路秋子 (赞：6)

题意：给一张有向图顶点染色，让你求一个最大的 $k$ 使得对于图中每条有向边 $u,v$ 使得$v$的颜色为$u$的颜色+1（比如颜色为1的+1为2，而颜色为k的+1为1，也就是个循环）。根据定义就可以知道k为1满足所有条件$==$

题解：不难发现k整除图中任意环的长度（应该说是点数），经过观察~~看题解~~又可以发现对于图中任意两条起点终点相同的链，设长度分别为$cnt1,cnt2,k|(cnt1-cnt2)$

然后我们就可以dfs解决这个问题辣！

但问题是对于图中每个联通块具体从那个点开始不好办，所以就有一个很神奇的操作：
对于每条边（边权为1），在建一条反向边（边权为-1）。

具体看代码$==$

```c
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,ans,tot,d[200001],e[200001],nt[200001],hd[200001],val[200001];
void build(int x,int y,int z){
	tot++;
	e[tot]=y;val[tot]=z;
	nt[tot]=hd[x];hd[x]=tot;
}
int gcd(int x,int y){
	if(!y)return x;
	return gcd(y,x%y);
}
void dfs(int x,int now){
	int i;
	if(d[x]){
		ans=gcd(ans,now-d[x]);
		return;
	}
	d[x]=now;
	for(i=hd[x];i;i=nt[i])dfs(e[i],now+val[i]);
}
int main(){
	int i,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		build(x,y,1);build(y,x,-1);
	}
	for(i=1;i<=n;i++)if(!d[i])dfs(i,n+n);
	printf("%d",ans?abs(ans):n);
}
```


---

## 作者：YFF1 (赞：1)

## 题意：
给一张有向图染色，使得一条边的入点颜色加一等于出点颜色。
求满足条件染色方案里所用颜色数量最大是几？
## 思路：
注意到影响所用颜色数由两个因素决定：

第一，环。因为环要求头和尾都是同一种颜色，因此在环内必然会形成循环。因此，环的长度必定会被颜色数量整除。当有多个环时，取这几个环的长度的最大公因数，以此满足整除的条件。

第二，起点和终点相同的链。因为两链的起点是同一种颜色，终点也是，所以在每一条链内也会形成循环，此时，颜色数取两链长度之差的最大公因数。再综合环的限制，颜色数量应该是各条链长度之差和各个环长度的最大公因数。

特别地，当没有形成诸如环之类的，颜色数等于节点数。

另外，在加入边权时，为每一条边设置另一条边权为负一的边，这样不仅可以快速获取环的长度和链长度之差，不用进行分类讨论，还可以避免因为搜索开始时的选点不当导致的错误，增加容错率。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int>pii;
int n,m,x,y,ans=0,cnt[200005],vis[200005];
vector<pii>g[200005];
void dfs(int x,int n){
	vis[x]=1;
	cnt[x]=n;//记录当前的颜色值 
	for(pii i:g[x]){
		if(!vis[i.first])dfs(i.first,n+i.second);//如果没有出现环 
		else ans=__gcd(ans,abs(n+i.second-cnt[i.first]));//取最大公因数，记得加绝对值 
	}//n+i.second是在求当前点的颜色值,abs(n+i.second-cnt[i.first])是在求当前链的长度之差或环的长度 
}
signed main () {
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&x,&y);
		g[x].push_back({y,1});
		g[y].push_back({x,-1});//反边权值设为-1 ，与题目给出的边权值相反 ，区分开来 
	}
	for(int i=1;i<=n;i++){
		if(!vis[i])dfs(i,0);//可能有多个连通块 
	}
	if(ans)printf("%lld",ans);
	else printf("%lld",n);//要是没有环，就可以用n种 
	return 0;
}
```

---

## 作者：EastPorridge (赞：1)

### 题目概述：

给有向图染色，存在边 $u \rightarrow v$，使得 $col_v = col_u + 1$，若存在 $k$ 种颜色，则下一个颜色为 $1,k \le n$，求最大的 $k$。

### 题目分析：

[[NOI2008] 假面舞会](https://www.luogu.com.cn/problem/P1477) 跟这道题思路相近。

将有向图拆为两种情况：当存在一个长度为 $len$ 的环时，满足 $k \mid len$；当存在两条起点终点相同的链时，满足 $k \mid (len1-len2)$。

进一步的，我们发现环的情况好处理，下一个问题就是如何穷举所有起点终点相同的链。建反边解决，将正边权值设为 $1$，反边权值设为 $-1$，这样操作在走反边时就会消除当前步的影响，就可以将环和链合并为一种情况，每次遍历到新点时打戳记录，类似记忆化搜索。

需要注意的是，当有向图为一条链时，$k$ 并不会被 dfs 更新，我们特判这种情况就可以了。

### Code.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int h[N],ne[N<<1],e[N<<1],w[N<<1],idx,k,n,m,f[N],st[N];
void add(int u,int v,int c) {ne[++idx]=h[u],e[idx]=v,w[idx]=c,h[u]=idx;}
void dfs(int u,int cnt)
{
	if(st[u]) return k=__gcd(k,cnt-f[u]),void(); st[u]=1; f[u]=cnt;
	for(int i=h[u];~i;i=ne[i]) {int j=e[i]; dfs(j,cnt+w[i]);}
}
int main()
{
	memset(h,-1,sizeof h); scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++) {scanf("%d%d",&u,&v); add(u,v,1); add(v,u,-1);}
	for(int i=1;i<=n;i++) if(! st[i]) dfs(i,0);
	printf("%d",k == 0 ? n : abs(k)); 
	return 0;
}
```

---

