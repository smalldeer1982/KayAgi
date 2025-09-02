# [USACO19OPEN] Fence Planning S

## 题目描述

Farmer John 的 $ N $ 头奶牛，编号为 $ 1 \ldots N $ （ $ 2 \leq N \leq 10^5 $ ），拥有一种围绕“哞网”，一些仅在组内互相交流却不与其他组进行交流的奶牛小组，组成的复杂的社交网络。

每头奶牛位于农场的二维地图上的不同位置 $ (x,y) $ ，并且我们知道有 $ M $ 对奶牛( $ 1 \leq M<10^5 $ )会相互哞叫。两头相互哞叫的奶牛属于同一哞网。

为了升级他的农场，Farmer John 想要建造一个四边与 $ x $ 轴和 $ y $ 轴平行的长方形围栏。Farmer John 想要使得至少一个哞网完全被围栏所包围（在长方形边界上的奶牛计为被包围的）。请帮助 Farmer John 求出满足他的要求的围栏的最小可能周长。有可能出现这一围栏宽为 $0$ 或高为 $0$ 的情况。

## 样例 #1

### 输入

```
7 5
0 5
10 5
5 0
5 10
6 7
8 6
8 4
1 2
2 3
3 4
5 6
7 6```

### 输出

```
10```

# 题解

## 作者：Mkarry (赞：15)

# 麻烦管理员好好看看我的题解，我的解法哪里重复了？？？

看到前面的大佬都用的是**并查集**，我就发一篇

## **DFS**的题解吧

基本的思路已经很清楚，基础的图论题目，先用链接表建图，然后对着图进行遍历。至于如何遍历，这道题需要找到每一个联通快，所以可以开一个$vis$数组标记一下这个点有没有遍历过，然后从一号节点开始，只要发现这个节点没有被标记过，就拿这个点开始把整个联通快都遍历，然后不断修正这个矩形的上方下方、左边右边。这个可以通过$DFS/BFS$来实现。这里放的是$DFS$方法。

这里就不详细说了，代码里都有注释。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5,maxe=maxn<<1;
int U,D,L,R,ans=2147483647,n,m,son[maxe],nxt[maxe],lik[maxn],tot; bool vis[maxn];
inline int read(){	//快读 
	int ret=0,f=1; char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') f=-f;
	for(;ch>='0'&&ch<='9';ch=getchar()) ret=ret*10+ch-'0';
	return ret*f;
}
void add_e(int x,int y){son[++tot]=y,nxt[tot]=lik[x],lik[x]=tot;}
	/*这里是用链接表建边，不再多说*/
struct cow{int x,y;}a[maxn];
void DFS(int step){
	vis[step]=1;	//标记遍历过了 
	U=max(U,a[step].y),D=min(D,a[step].y);
	R=max(R,a[step].x),L=min(L,a[step].x);
		//这里的U,D,L,R分别指up,down,left,right,这里就是碰到一个节点就修正矩形 
	for(int j=lik[step];j;j=nxt[j]) if(!vis[son[j]]) DFS(son[j]);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=(cow){read(),read()};
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		add_e(x,y),add_e(y,x);
	}
	for(int i=1;i<=n;i++) if(!vis[i]){	//找到没有遍历到的了 
		U=D=a[i].y,L=R=a[i].x; //给矩形赋最初的值 
		DFS(i);
		ans=min(ans,((U-D)+(R-L))<<1);		//修正答案， ((U-D)+(R-L))<<1就是周长 
	}
	printf("%d\n",ans);
	return 0;
}

```

然而，你们会有疑惑这个代码的**时间复杂度**吗？看了我的代码，看到了一个$for$循环里面还有一个$DFS$，你们会不会认为这是$n^2$的？哈哈，其实不是的。因为当你发现一个节点并遍历了以后，与它相关的节点就都不会再次遍历到了，所以时间复杂度其实是$O(n)$级别的。

## 完结撒花~

---

## 作者：Zed_ (赞：10)

### 题意：

给出一张无向图和点的坐标，每一个连通块都恰好被一个矩形围起来，求其中最小矩形的周长。

### 思路：

矩形周长取决于该连通块中“最靠外”的点，所以在求连通块的过程中，分别维护同一连通块中横纵坐标的最大值和最小值，然后更新答案，即可解决本题。

### Code:

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int E = 200000 + 10;
const int MAX_N = 200000;
const int INF = 0x3f3f3f3f;

int n, m;
struct Cow {
	int x, y;
} c[E];
struct Node {
	int from, to, next;
} edge[E << 1];
int head[E];
int co[E], size[E];
vector<int> vec[E];
bool vis[E];
int cnt = 1, tot = 0;
int ans = INF;

void add_edge(int u, int v) {
	cnt++;
	edge[cnt].from = u;
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
}

void dfs(int u, int col) {
	co[u] = col;
	size[col]++;
	vec[col].push_back(u);
	vis[u] = true;
	for (int i = head[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (vis[v]) continue;
		dfs(v, col);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d", &c[i].x, &c[i].y);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	
	for (int i = 1; i <= n; i++) if (!co[i]) dfs(i, ++tot);
	
	for (int i = 1; i <= tot; i++) {
		int max_x = -INF, max_y = -INF, min_x = INF, min_y = INF;
		for (int j = 0; j < vec[i].size(); j++) {
			if (c[vec[i][j]].x > max_x) max_x = c[vec[i][j]].x;
			if (c[vec[i][j]].y > max_y) max_y = c[vec[i][j]].y;
			if (c[vec[i][j]].x < min_x) min_x = c[vec[i][j]].x;
			if (c[vec[i][j]].y < min_y) min_y = c[vec[i][j]].y;
		}
		int temp = 2 * (max_x - min_x + max_y - min_y);
		if (temp < ans) ans = temp;
	}
	
	printf("%d\n", ans);
	
	return 0;
}
```


---

## 作者：微芒晨曦 (赞：3)

### 建号以来的第一篇题解，如有讲不清楚的细节请多指教

~~第一眼看到这题就觉得挺水的，这还能是个绿？！~~

### 正题

首先，大家应该都能想到要查找连通块在X轴方向上的长度与在Y轴方向上的长度的和的最小值的两倍。
似乎语言并不能很清晰地表达清楚。

化成式子就是ans=2*min(ans，maxx-minx+maxy-miny)
注意，这里的minx maxx miny maxy表达的是单个连通块的边缘

这里我用的是两遍并查集，第一遍标记连通关系，第二遍是将同一连通块中所有点的fa都标记在同一个点上，方便更新连通块的边缘坐标，然后查找每个连通块的边缘坐标，最后更新ans就可以了。

code

```
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,ans=0x3f3f3f3f;
int fa[100001];
int x[100001],y[100001];
int maxx[100001],minx[100001],miny[100001],maxy[100001];
//x y两数组记录的是点的坐标，minx miny maxx maxy则记录连通块的边缘坐标 
int find(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void check(int p)
{
	int A=fa[p];//A这个点就是代表该连通块的根节点 
	maxx[A]=max(x[p],maxx[A]);
	minx[A]=min(x[p],minx[A]);
	miny[A]=min(y[p],miny[A]);
	maxy[A]=max(y[p],maxy[A]);
}
int main()
{
	memset(minx,0x3f3f3f3f,sizeof(minx));
	memset(miny,0x3f3f3f3f,sizeof(miny));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		int x=find(a);//第一遍并查集，标记连通块 
		int y=find(b);
		fa[x]=y;
	}
	for(int i=1;i<=n;i++)//第二遍并查集，将一个连通块缩为一个点，后面我用fa[i]==i这个特殊点代表其所在的连通块 
		find(i);
	for(int i=1;i<=n;i++)//挨个点查询，看这个点的坐标是否为该连通块的边缘坐标 
		check(i);
	for(int i=1;i<=n;i++)
		if(fa[i]==i)//如果fa[i]==i，那么i可以表示该连通块，进行ans的更改 
			ans=min(ans,maxx[i]-minx[i]+maxy[i]-miny[i]);
	printf("%d",ans*2);//不要忘记求的是周长，ans要乘2的 
	return 0;
}

```


---

## 作者：purinliang (赞：3)

两头相互哞叫的奶牛属于同一哞网，要维护的是一整个哞网的性质。

想一想不是就是问一个连通块的上下界和左右界分别在哪里吗？

那就把每头牛视作二维平面上的一个点，初始化其上下界和左右界为起始坐标。

然后并查集合并的时候就可以顺便把上下界和左右界拓展到相应的位置。

```cpp
u[fx]=max(u[fx],u[fy]);
d[fx]=min(d[fx],d[fy]);
l[fx]=min(l[fx],l[fy]);
r[fx]=max(r[fx],r[fy]);
```

时间复杂度几乎是 $O(n)$ ，因为其实并查集有一个很小的增长很慢的系数。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=100000;

int par[MAXN+5];
int u[MAXN+5],d[MAXN+5],l[MAXN+5],r[MAXN+5];

void init(int n) {
    for(int i=1; i<=n; i++) {
        par[i]=i;
    }
}

int find_par(int x) {
    int k,pk,r;
    r=x;
    while(r!=par[r])
        r=par[r];       //x查到根，保存为r
    k=x;
    while(k!=r) {       //循环处理x的祖先直到根
        pk=par[k];      //保存k的父亲后把k接入r
        par[k]=r;
        k=pk;           //处理k的父亲
    }
    return r;
}

bool union_set(int x,int y) {
    int fx=find_par(x);
    int fy=find_par(y);
    if(fx==fy) {
        return false;
    } else {
        par[fy]=fx;
        u[fx]=max(u[fx],u[fy]);
        d[fx]=min(d[fx],d[fy]);
        l[fx]=min(l[fx],l[fy]);
        r[fx]=max(r[fx],r[fy]);
        return true;
    }
}

ll calc(int fi){
    ll dy=u[fi]-d[fi];
    ll dx=r[fi]-l[fi];
    return 2ll*(dy+dx);
}

int main() {
#ifdef Yinku
    freopen("Yinku.in","r",stdin);
#endif // Yinku
    int n,m;
    scanf("%d%d",&n,&m);
    init(n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&l[i],&d[i]);
        r[i]=l[i],u[i]=d[i];
    }
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        union_set(x,y);
    }

    ll ans=1e18;
    for(int i=1;i<=n;i++){
        int fi=find_par(i);
        ans=min(ans,calc(fi));
    }
    printf("%lld\n",ans);

    return 0;
}
```

---

## 作者：Qquun (赞：1)

## 1.题目大意：
给定N个点的二维坐标，和M对关系，计算完每对关系后可以构成若干个联通块，求包围某个联通块所用的最小矩形周长。


## 2.解题思路：
并查集维护联通块，并维护每个联通块最大最小的x,y值，最后计算求每个联通块中的最小周长即可。




### ps:代码用了STL中的map和pair。




## Code:
```c
#include<bits/stdc++.h>
using namespace std;
int f[200005];
map<int,pair<int,int> >mp;
map<pair<int,int>,int>q;
int find(int x){//并查集
	if(f[x]!=x){
		f[x]=find(f[x]);
	}
	return f[x];
}
int ansx1[200005],ansy1[200005],ansx2[200005],ansy2[200005];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		int l,r;
		cin>>l>>r;
		q[{l,r}]=i;//映射对
		mp[i]={l,r};
	}
	for(int i=1;i<=n;++i)f[i]=i;
	for(int i=1;i<=m;++i){
		int l,r;
		cin>>l>>r;
		if(find(l)!=find(r)){
			f[find(r)]=find(l);//合并操作
		}
	}
	for(int i=1;i<=n;++i){
		ansx1[i]=ansy1[i]=-0x3f3f3f3f;//x1 y1维护联通块最大x,y
		ansx2[i]=ansy2[i]=0x3f3f3f3f;//x2 y2维护联通块最小x,y
	}
	for(int i=1;i<=n;++i){
		int fa=find(i);
		ansx1[fa]=max(ansx1[fa],mp[i].first);
		ansx2[fa]=min(ansx2[fa],mp[i].first);
		ansy1[fa]=max(ansy1[fa],mp[i].second);	
		ansy2[fa]=min(ansy2[fa],mp[i].second);		
	}
	long long minn=1000000000000000;
	for(int i=1;i<=n;++i){
		if(ansx1[i]!=-0x3f3f3f3f&&ansy1[i]!=-0x3f3f3f3f&&ansx2[i]!=0x3f3f3f3f&&ansy2[i]!=0x3f3f3f3f)
        	minn=min(1LL*2*(ansx1[i]-ansx2[i]+ansy1[i]-ansy2[i]),minn);
	}
	cout<<minn<<"\n";
	return 0;
}


```
**最后贡献一组卡了我的数据(tcl）：**

```cpp
2 1
100000000 100000000
0 0
1 2
```


---

## 作者：localhost (赞：1)

直接用并茶几来搞

然后每次操作把两个集合的矩形合并

上代码

```cpp
#include<bits/stdc++.h>
#define Fur(i,x,y) for(int i=x;i<=y;++i)
#define inf 0x3f3f3f3f
#define N 200011
using namespace std;
int MIN(int x,int y){return x<y?x:y;}
int MAX(int x,int y){return x>y?x:y;}
int n,m,f[N],X[N],Y[N],XX[N],YY[N];
struct node{
    int x,y;
}a[N];
int gf(int x){
    return (f[x]==x)?x:(f[x])=gf(f[x]);
}
int main(){
	 ios::sync_with_stdio(false);
    cin>>n>>m;
    Fur(i,1,n)cin>>a[i].x>>a[i].y,f[i]=i,X[i]=inf,Y[i]=inf;
    int x,y;
    Fur(i,1,m){
        cin>>x>>y;
        if(gf(x)!=gf(y))f[f[x]]=f[y];
    }
    Fur(i,1,n){
        int t=gf(i);
        X[t]=MIN(X[t],a[i].x);
        XX[t]=MAX(XX[t],a[i].x);
        Y[t]=MIN(Y[t],a[i].y);
        YY[t]=MAX(YY[t],a[i].y);
    }
    int ans=inf;
    Fur(i,1,n)if(i==gf(i))
        ans=MIN(ans,XX[i]-X[i]+YY[i]-Y[i]);

    cout<<(ans<<1)<<endl;
}

```

---

