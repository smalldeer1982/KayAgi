# Mr. Kitayuta's Colorful Graph

## 题目描述

给出一个 $n$ 个点，$m$ 条边的无向图，每条边上是有颜色的。有 $q$ 组询问

对于第 $i$ 组询问，给出点对 $u_i,v_i$。求有多少种颜色 $c$ 满足：有至少一条 $u_i$ 到 $v_i$ 路径，满足该路径上的所有边的颜色都为 $c$

## 说明/提示

$2 \le n \le 100$  
$1 \le m,q \le 100$  
$1\le x_i,y_i,u_i,v_i \le n$  
$1 \le c_i \le m$  
感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
4 5
1 2 1
1 2 2
2 3 1
2 3 3
2 4 3
3
1 2
3 4
1 4
```

### 输出

```
2
1
0
```

## 样例 #2

### 输入

```
5 7
1 5 1
2 5 1
3 5 1
4 5 1
1 2 2
2 3 2
3 4 2
5
1 5
5 1
2 5
1 5
1 4
```

### 输出

```
1
1
1
1
2
```

# 题解

## 作者：封禁用户 (赞：3)

感觉最多黄，几乎是并查集模板题。

题目只要求我们维护两点之间的连通性，其次 $n,q \le 100$，所以并查集即可。

并查集的复杂度 $O(n)$，枚举每种颜色 $O(m)$，复杂度为 $O(qm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, q;
int fa[105][105];
void init() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			fa[i][j] = i;
		}
	}
}
int fnd(int u, int color) {
	if (fa[u][color] == u) {
		return u;
	}
	return fa[u][color] = fnd(fa[u][color], color);
}

void add(int u,int v,int c) {
	fa[fnd(u, c)][c] = fnd(v, c);
}

void solve() {
	cin >> n >> m;
	init();
	for (int i = 1; i <= m; i++) {
		int x, y, c;
		cin >> x >> y >> c;
		add(x,y,c);
	}
	cin >> q;
	while (q--) {
		int u, v;
		cin >> u >> v;
		int res = 0;
		for (int i = 1; i <= m; i++) {
			if (fnd(u, i) == fnd(v, i)) {
				res++;
			}
		}
		cout << res << endl;
	}
}

signed main() {
	solve();
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：3)

刚开始想了一个很暴力的 dfs 做法，不知道行不行，看到标签之后才开始往并查集的方向想

若 有至少一条 $u$ 到 $v$ 的路径，使得路径上所有的边颜色都是 $c$，我们则称这个颜色 $c$ 为 $u,v$ 的**连通色**

我们开一个二维并查集，$f[i][j]$ 表示点 $i$ 所在的连通色为 $j$ 的集合中的祖先节点

上面可能有点抽象，下面来个举个栗子  
对于两个点 $u,v$ 和颜色 $i$，如果 $f[u][i]=f[v][i]$，说明 $u,v$ 在同一个连通色为 $i$ 的集合中，那么 颜色 $i$ 一定是 $u,v$ 的连通色。

理解了并查集的意义，剩下的就很简单了  

对于一条连接点 $u,v$，颜色为 $c$ 的边，我们将点 $u,v$ 在以颜色为连通色的并查集中合并。因为这条边保证了 $c$ 是点 $u,v$ 的连通色

最后，对于询问 $u,v$ 的连通色个数，我们就枚举连通色 $i$，看看是否 $f[u][i]=f[v][i]$ 并统计答案就可以了

时间复杂度 $O(n^2)$

```cpp
#include<cstdio> 
#include<iostream>
using namespace std;
const int Maxn=110,inf=0x3f3f3f3f;
int f[Maxn][Maxn];
int n,m,q;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int find(int x,int i) //二维并查集
{
	if(f[x][i]==x)return x;
	return f[x][i]=find(f[x][i],i);
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),m=read();
	
	for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
	f[i][j]=i; // 并查集初始化
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read(),c=read();
		f[find(x,c)][c]=find(y,c); // 维护并查集
	}
	q=read();
	
	while(q--)
	{
		int x=read(),y=read(),tot=0;
		for(int i=1;i<=m;++i)
		if(find(x,i)==find(y,i))++tot;
		printf("%d\n",tot);
	}
	
	return 0;
}
```

---

## 作者：Graph_Theory (赞：1)

## CF505B Mr. Kitayuta's Colorful Graph 题解
### 题意：
在 $u$ 到 $v$ 之间有多少种走法使边权相同。
### 思路：
考虑到 $n,m<100$ 且需要查询任意两点是否存在边权相同的路，所以使用弗洛伊德求解。
### 设计状态
弗洛伊德的普通状态加上颜色的选择 $c$ ，其中 $dis_{u,v,c}$ 表示 $u\longrightarrow v$ 边且边权为 $c$ 的这一条边存在。

计算时，如果$ dis_{u,k,c} $ 和 $dis_{k,v,c}$ 都存在，说明 $u\longrightarrow v$ 有边权相同的走法。

### 代码 $O(n^4)$
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
#define MAXN 150
bool dis[MAXN][MAXN][MAXN];

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v,c;
		cin>>u>>v>>c;
		dis[u][v][c]=1;
		dis[v][u][c]=1;//无向图
	}
	for(int k=1;k<=n;k++)//弗洛伊德
		for(int u=1;u<=n;u++)
			for(int v=1;v<=n;v++)
				for(int c=1;c<=m;c++)//处理颜色的选择
					if(dis[u][k][c]&&dis[k][v][c])
						dis[u][v][c]=1;//判断是否有边权相同的走法
	int q;cin>>q;//q次询问
	while(q--)
	{
		int u,v,ans=0;
		cin>>u>>v;
		for(int i=0;i<=m;i++)
			if(dis[u][v][i]) ans++;//如果存在
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：ahawzlc (赞：0)

思路：并查集，对颜色边数采用分块思想， map 统计答案。

----

首先存下所有边，按照颜色排序，这样可以把同种颜色的边放到一起。同时离线询问。

接下来，我们每次选择一种颜色的边，统计这种颜色边的数量 `tot`，进行分类讨论。

1. $tot \ge \sqrt{n}$
2. $tot < \sqrt{n}$

对于第一种情况，出现这种情况的颜色数量不会超过 $\sqrt{n}$ 个。此时我们可以对于颜色边直接做并查集。然后扫一遍询问，如果询问的两个点在同一连通块，那么就会对答案产生 1 的贡献。

对于第二种情况，显然连通块内的点数不会超过 $n\sqrt{n}$ 个，那么我们在做完并查集之后，枚举该种颜色边所连接的点，如果这两个点在同一连通块，那么这对点会对答案产生贡献。

这里就出现了一个问题，点对上的答案怎么对询问的答案产生贡献？

可以考虑用 `map` 存储，建立一个 `pair<int,int>` 对 `int` 的映射，这样可以直接记录点对的贡献，最后在输出答案的时候加进去就可以了。

注意：
1. 因为 `pair` 是有序的，所以在存储时可以将点对 $(x,y)$ 处理成 $x<y$ 。
2. 在第二种情况里，颜色边所连接的点可能有重复，需要去重。

并查集使用路径压缩和按秩合并优化，复杂度 $O(\alpha(n))$ ， `map` 复杂度 $O(\log n)$ ， 分块复杂度 $O(n\sqrt n)$ ，由于并查集复杂度几乎可以不计，所以总复杂度约为 $O(n\sqrt n \log n)$ 。

Code:

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
#define mp make_pair
#define pi pair<int,int>
using namespace std;
const int N=100005;
inline int read() {
	int sum=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		sum=(sum<<3)+(sum<<1)+ch-'0';
		ch=getchar();
	}
	return sum*w;
}
int n,m,q,qx[N],qy[N],f[N],d[N],ans[N],tmp[N],siz;
struct node {
	int x,y,z;
	bool operator < (const node &a) const {
		return z<a.z;
	}
} e[N];
map<pi,int> p;
int find(int x) {//并查集
	return f[x]==x?x:f[x]=find(f[x]);
}
void merge(int x,int y) {
	x=find(x),y=find(y);
	if(x!=y) {
		if(d[x]<d[y]) swap(x,y);
		f[y]=x;
		if(d[x]==d[y]) d[x]++;
	}
}
int main() {
	n=read(),m=read();
	for(int i=1; i<=n; i++) f[i]=i;
	for(int i=1; i<=m; i++) {
		e[i].x=read(),e[i].y=read(),e[i].z=read();
		if(e[i].x>e[i].y) swap(e[i].x,e[i].y);//确保x<y 
	}
	sort(e+1,e+m+1);//按颜色排序 
	q=read();
	for(int i=1; i<=q; i++) {
		qx[i]=read(),qy[i]=read();
		if(qx[i]>qy[i]) swap(qx[i],qy[i]);//离线询问 
	}
	for(int i=1,j=1; i<=m; i=++j) {
		while(e[j].z==e[j+1].z) j++;//j的位置是最后一条该颜色的边 
		for(int k=i; k<=j; k++) merge(e[k].x,e[k].y);//做并查集 
		int tot=j-i+1; 
		if(tot<sqrt(m)) {//分块 
			siz=0;
			for(int k=i; k<=j; k++) tmp[++siz]=e[k].x,tmp[++siz]=e[k].y;//记录该颜色边所连接的点 
			sort(tmp+1,tmp+siz+1);
			siz=unique(tmp+1,tmp+siz+1)-tmp-1;//去重 
			for(int x=1; x<siz; x++)
				for(int y=x+1; y<=siz; y++)
					if(find(tmp[x])==find(tmp[y])) p[mp(tmp[x],tmp[y])]++;//在同一连通块，往点对上添加答案 
		} else for(int k=1; k<=q; k++) ans[k]+=(find(qx[k])==find(qy[k]));//直接扫询问统计答案 
		for(int k=i; k<=j; k++) f[e[k].x]=e[k].x,f[e[k].y]=e[k].y,d[e[k].x]=d[e[k].y]=0;//清空 
	}
	for(int i=1; i<=q; i++) {
		if(p.find(mp(qx[i],qy[i]))!=p.end()) ans[i]+=p[mp(qx[i],qy[i])];//统计点对对答案的贡献 
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

[强化版](https://www.luogu.com.cn/problem/CF506D)

---

## 作者：灵光一闪 (赞：0)

# 思路：把所有序号的都建一个图，再跑DFS：

```cpp
//代码
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>
#include<vector>
using namespace std;
int vis[123][123];
vector<int> al[123][123];//建图的数组
void dfs(int v,int c)
{
    if(vis[v][c])
        return;
    vis[v][c]=1;
    for(int i=0;i<al[c][v].size();i++)
    {
        int u=al[c][v][i];
        dfs(u,c);
    }
    return;
}
int main()
{
    int ans;
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int u,v,c;
        cin>>u>>v>>c;
        al[--c][--v].push_back(--u);//因为我们是从0开始的，所以要减1
        al[c][u].push_back(v);//坑点，这里不能减两个，否则将会如果u,v,c是一的话会成负数。
    }
    int q;
    cin>>q;
    for(int i=0;i<q;i++)
    {
        int u,v;
        cin>>u>>v;
        --u;
        for(int j=0;j<m;j++)
            dfs(u,j);
        int ans=0;
        --v;
        for(int j=0;j<m;j++)
            ans+=vis[v][j];
        for(int j=0;j<n;j++)
            for(int k=0;k<m;k++)
                vis[j][k]=0;
        cout<<ans<<endl;
    }
    return 0;
}
```


---

