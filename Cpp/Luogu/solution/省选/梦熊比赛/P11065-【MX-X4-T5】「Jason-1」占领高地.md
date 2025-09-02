# 【MX-X4-T5】「Jason-1」占领高地

## 题目背景

原题链接：<https://oier.team/problems/X4F>。

## 题目描述

有一张 $n$ 行 $m$ 列的地图，其第 $i$ 行 $j$ 列的位置的**高度**为 $h_{i,j}$ 且**军事化程度**为 $p_{i,j}$，且满足**任意两个四连通相邻的位置高度差的绝对值不超过 $\bm 1$**。  
（两个位置 $(a, b)$、$(c, d)$ 四连通相邻，当且仅当 $\lvert a - c\rvert + \lvert b - d\rvert = 1$。）

你可以选择若干个位置建立补给站。若在位置 $(i,j)$ 建立了补给站，定义其**运输范围**为所有满足 $h_{i,j} - h_{x,y} + p_{i,j} \geq \lvert i - x\rvert + \lvert j - y\rvert$ 的位置 $(x, y)$。每个补给站都可以在其运输范围中任意移动物资的位置。

定义若干个补给站 $(x, y)$ 的安全程度为其中 $h_{x,y}$ 的最小值。

有 $q$ 次询问，每次给出四个整数 $a, b, c, d$，询问：若要建立若干个补给站，以将物资从位置 $(a, b)$ 运输至位置 $(c, d)$，则建立补给站的安全程度最大值是多少？或报告不可能完成运输任务。

**注意：物资可以通过多个补给站间接运输。不一定必须在 $(a, b)$ 和 $(c, d)$ 两点建立补给站。**

**本题数据保证 $\bm{p_{i, j} \le 9}$。**

## 说明/提示

**【样例解释 #1】**

第一个询问可以在 $(1,3)$ 建立补给站，安全程度为 $3$。

第二个询问可以在 $(4,1)$ 建立补给站，安全程度为 $4$。

第三个询问可以在 $(3,2)$ 建立补给站，安全程度为 $3$。

第四个询问可以在 $(3,2)$ 建立补给站，安全程度为 $3$。

第五个询问可以在 $(4,1)$ 建立补给站，安全程度为 $4$。

第六个询问可以在 $(4,1),(1,3)$ 建立补给站，安全程度为 $3$。

**【样例解释 #2】**

仅有在 $(1,1)$ 建立的补给站可以将物资在 $(1,1)$、$(1,2)$ 间任意移动，在其它位置建立的补给站都将无法移动任何物资。

故仅有询问 $1$ 可以达成目标，只需在 $(1,1)$ 建立补给站，安全程度为 $1$。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务 | $q \le$ | $n,m \le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $20$ | $10$ | A | $23$ |
| 2 | $10^5$ | $300$ | B | $19$ |
| 3 | $10^5$ | $100$ | 无 | $27$ |
| 4 | $2 \times 10^5$ | $300$ | 无 | $31$ |

- 特殊性质 A：$p_{i, j} \le 4$。
- 特殊性质 B：$p_{i, j} = 0$。

对于 $100 \%$ 的数据，$1 \le n,m \le 300$，$0 \le h_{i,j} \le 10^9$，$\bm{0 \le p_{i,j} \le 9}$，$1 \le q \le 2 \times 10^5$，$1 \le a,c \le n$，$1 \le b,d \le m$，$(a,b) \neq (c,d)$，**保证任意两个四连通相邻的位置高度差的绝对值不超过 $\bm 1$**。

## 样例 #1

### 输入

```
4 4 6
1 2 3 2
2 3 2 3
3 3 2 2
4 3 2 1
2 1 1 1
0 1 1 0
1 1 0 1
0 0 1 2
1 1 1 2
1 1 2 1
2 2 4 4
2 3 3 1
4 4 2 1
1 4 4 1
```

### 输出

```
3
4
3
3
4
3
```

## 样例 #2

### 输入

```
1 3 3
1 1 1
1 0 0
1 1 1 2
1 1 1 3
1 2 1 3
```

### 输出

```
1
-1
-1
```

## 样例 #3

### 输入

```
8 8 10
5 6 6 5 6 7 8 9
5 6 6 5 6 6 7 8
4 5 5 4 5 5 6 7
3 4 5 4 5 6 6 7
4 5 5 5 5 6 7 6
5 4 5 5 4 5 6 7
4 3 4 5 4 5 6 6
5 4 4 4 3 4 5 5
0 0 0 0 1 0 2 0
0 0 0 0 0 0 0 0
0 1 0 2 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0
6 3 7 7
1 5 2 2
7 7 6 7
4 3 7 7
7 6 8 2
3 2 8 7
1 6 8 6
1 6 7 4
4 5 4 4
5 4 1 1
```

### 输出

```
5
5
6
5
5
5
6
5
8
-1
```

# 题解

## 作者：是青白呀 (赞：5)

一个暴力的想法是对于每一个补给站 $(i,j)$，将其运输范围内的点用边权为 $h_{i,j}$ 的边连通起来。此时需要最大化路径上的最小权值，套路化地跑最大生成树，然后建立 Kruskal 重构树，对每次询问求解 LCA 即可。

考虑去除不优的边，减少边的数量。首先不难观察到一个结论：若点 $(x,y)$ 能被补给站 $(i,j)$ 覆盖，则 $(x,j)$ 和 $(i,y)$ 一定都能被补给站 $(i,j)$ 覆盖到。其原因是任意两个四连通相邻的位置高度差的绝对值不超过 $1$，因此 $h$ 的减少量一定不大于曼哈顿距离的减少量。也因此，任意补给站的覆盖范围都是一个连通块，且均可以通过先向左右方向走、再向上下方向走的方式抵达每一个覆盖位置。

于是不难想到将该图简化为相邻方格内连边，需要对于每一个相邻的方格，求得覆盖他们两个的补给站的 $h$ 最大值。

观察满足被补给站 $(i,j)$ 覆盖的式子：$h_{i,j}−h_{x,y}+p_{i,j}-|i−x|-|j−y|\geq 0$。你发现从 $(x,y)$ 走到距离 $(i,j)$ 更远的格子时，左式的新值与 $(i,j)$ 的具体位置无关，仅与 $(x,y)$ 处左式的原值有关。而根据 $h$ 的变化量不大于曼哈顿距离的变化量，合法时左式仅有 $[0,p_{i,j}]$ 几种取值，在题目 $p$ 的限制下只能为 $[0,9]$。于是不妨维护 $f_{i,j,k}$ 表示覆盖 $(i,j)$、且左式值为 $k$ 的所有补给站中 $h$ 的最大值。根据上文得到的结论，按照任意顺序在四个方向上分别将所有点进行一次转移，即可得到正确的取值。

对于相邻两个格子 $(i,j)$ 和 $(x,y)$，同时覆盖这两个格子意味着一定存在某个格子在另一个格子的远端。因此我们枚举 $k$，分别判断 $f_{i,j,k}$ 能否转移到 $f_{x,y,k}$ 以及 $f_{x,y,k}$ 能否转移到 $f_{i,j,k}$ 即可。则两点间的边权为所有可行转移的最大 $h$。

对建出来的新图跑最大生成树，然后建立 Kruskal 重构树即可。复杂度 $O(nm(p+\log nm)+q\log nm)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
const int N=305,M=2e5+5,S=(1<<15)+5,inf=(ll)1e18+7,mo=998244353;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,m,q;
int h[N][N],p[N][N],f[N][N][10];
int maxh[N][N],maxl[N][N];
int fa[N*N*2][20],dep[N*N*2];
struct edge{
    int x,y,val;
    friend bool operator<(edge x,edge y){
        return x.val>y.val;
    }
}e[N*N*2];
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1},cnte;
void update(int x,int y,int op){
    int lx=x+dx[op],ly=y+dy[op];
    repp(k,9,0){
        int nwk=k+h[lx][ly]-h[x][y]-1;
        if(nwk<0)break;
        f[x][y][nwk]=max(f[x][y][nwk],f[lx][ly][k]);
    }
}
void getedge(int k){
    rep(i,1,n-1){
        rep(j,1,m){
            if(k+h[i][j]-h[i+1][j]-1>=0)maxl[i][j]=max(maxl[i][j],f[i][j][k]);
            if(k+h[i+1][j]-h[i][j]-1>=0)maxl[i][j]=max(maxl[i][j],f[i+1][j][k]);
        }
    }
    rep(i,1,n){
        rep(j,1,m-1){
            if(k+h[i][j]-h[i][j+1]-1>=0)maxh[i][j]=max(maxh[i][j],f[i][j][k]);
            if(k+h[i][j+1]-h[i][j]-1>=0)maxh[i][j]=max(maxh[i][j],f[i][j+1][k]);
        }
    }
}
int getid(int x,int y){
    return (x-1)*m+y;
}
struct bcj{
    int fa[N*N*2];
    void init(){
        rep(i,1,n*m*2)
            fa[i]=i;
    }
    int find(int x){
        if(x==fa[x])return x;
        return fa[x]=find(fa[x]);
    }
    bool merge(int x,int y){
        x=find(x),y=find(y);
        if(x==y)return 0;
        fa[x]=y;
        return 1;
    }
}B;
int val[N*N*2],cntn;
vector<int>et[N*N*2];
void dfs(int x,int f){
    dep[x]=dep[f]+1,fa[x][0]=f;
    rep(i,1,18)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for(auto j:et[x])
        dfs(j,x);
}
int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    repp(i,18,0)
        if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
    if(x==y)return x;
    repp(i,18,0)
        if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int nrt[N*N*2];
signed main(){
    read(n),read(m),read(q);
    rep(i,1,n){
        rep(j,1,m)
            read(h[i][j]);
    }
    rep(i,1,n){
        rep(j,1,m)
            read(p[i][j]);
    }
    rep(i,1,n){
        rep(j,1,m){
            rep(k,0,9)
                f[i][j][k]=-inf;
            maxh[i][j]=maxl[i][j]=-inf;
        }
    }
    rep(i,1,n){
        rep(j,1,m)
            f[i][j][p[i][j]]=h[i][j];
    }
    rep(i,2,n){
        rep(j,1,m)
            update(i,j,0);
    }
    repp(i,n-1,1){
        rep(j,1,m)
            update(i,j,1);
    }
    rep(i,1,n){
        rep(j,2,m)
            update(i,j,2);
    }
    rep(i,1,n){
        repp(j,m-1,1)
            update(i,j,3);
    }
    rep(k,0,9)
        getedge(k);
    rep(i,1,n){
        rep(j,1,m){
            if(j!=m)e[++cnte]=(edge){getid(i,j),getid(i,j+1),maxh[i][j]};
            if(i!=n)e[++cnte]=(edge){getid(i,j),getid(i+1,j),maxl[i][j]};
        }
    }
    sort(e+1,e+cnte+1);
    B.init();
    cntn=n*m;
    rep(i,1,cnte){
        int x=e[i].x,y=e[i].y;
        x=B.find(x),y=B.find(y);
        if(x==y)continue;
        val[++cntn]=e[i].val;
        B.merge(x,cntn);
        B.merge(y,cntn);
        et[cntn].push_back(x),et[cntn].push_back(y);
    }
    dfs(cntn,0);
    while(q--){
        int a,b,x,y;
        read(a),read(b),read(x),read(y);
        y=getid(x,y),x=getid(a,b);
        printf("%lld\n",max(-1ll,val[lca(x,y)]));
    }
    return 0;
}

```

---

## 作者：min_inf (赞：4)

感觉这个 D 真的比 BC 简单啊，好像大家都有点做烦了。

首先能发现询问的是网格图上的瓶颈路，边权是两个点被同一个点覆盖到的最大 $h$。

把式子写成 $h_{i,j}-h_{x,y}+p_{i,j}-\operatorname{dis}((i,j),(x,y))\ge 0$，这玩意显然是 $\le p_{i,j}$ 的。直接设 $f_{i,j,k}$ 为到达 $(i,j)$ 这个点当前值为 $k$ 的最大 $h$，上下左右各 DP 一遍，边权就是所有转移上的 $\max f$。

剩下就是 Kruskal 重构树板子，时间复杂度 $O(nm\max p+nm\log nm+q)$。代码太丑就不放了。

---

## 作者：一只绝帆 (赞：2)

感觉是妙妙题，可能还是见的太少了。

耐心读完题，询问相当于问两个点什么时候联通，所以我们离线，按照 $h$ 从大到小激活一个点，每激活一个点都把它和它能支配的点的连通性合并，使用启发式合并即可维护。

现在的唯一问题是怎么找到“它能支配的点”，并且不会 TLE。

首先题目保证了相邻位置高度差不超过 $1$，这保证了一个点的支配区域真的是联通的，考虑 $\rm bfs$。

不妨把题目给的支配式子变形，记 $\max_{(u,v)\text{ is enable}}h_{u,v}+p_{u,v}-h_{x,y}-|u-x|-|v-y|$ 为 $(x,y)$ 这个点的有利值，由于题目保证了 $p_{u,v}\le 9$，所以每个点的有利值 $\le 9$。

你发现一个点有继续 $\rm bfs$ 下去的必要，当且仅当它的有利值被更新得更大，这意味着通过它搜继续下去有可能扩展更多的点。

所以只需要在有利值被更新的时候继续 $\rm bfs$ 即可，复杂度相当于 $\max p$ 次遍历全图。

复杂度 $\mathcal O(nm\max p+(nm+q)\log^2(nm))$。

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i=a,i##E=b;i<=i##E;i++)
#define UF(i,a,b) for(int i=a,i##E=b;i>=i##E;i--)
#define sz(x) int(x.size())
using namespace std;typedef long long ll;
#define vec vector
template<typename T>
void operator+=(vec<T> &a,const T&b) {a.push_back(b);}
#define gc() getchar()
//#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char *p1,*p2,buf[1<<21];
int read() {
	int s=0,w=0;char ch=gc();
	while(ch<'0'||ch>'9') w|=(ch=='-'),ch=gc();
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=gc();
	return w?-s:s;
} const int N=305,Q=2e5+5,M=N*N+N;
int n,m,q,h[N][N],p[N][N],r[N][N],ans[Q],f[M];
set<pair<int,int>> s[M];
vec<tuple<int,int,int>> que[N][N];
vec<pair<int,int>> nei(int x,int y) {
	using P=pair<int,int>;
	vec<pair<int,int>> ans;
	for(auto[dx,dy]:{P{0,1},P{0,-1},P{1,0},P{-1,0}}) {
		if(x+dx>=1&&x+dx<=n&&y+dy>=1&&y+dy<=m) {
			ans+=make_pair(x+dx,y+dy);
		}
	} return ans;
}
int id(int x,int y) {
	return (x-1)*m+y;
}
int find(int x) {return f[x]^x?f[x]=find(f[x]):x;}
void init(int x,int y) {
	f[id(x,y)]=id(x,y);
	s[id(x,y)].insert({x,y});
} 
void mer(int x,int y,int H) {
	x=find(x);y=find(y);
	if(x==y) return;
	if(sz(s[x])>sz(s[y])) swap(x,y);
	f[x]=y;
	for(auto[i,j]:s[x]) {
		for(auto[u,v,id]:que[i][j]) {
			if(s[y].count({u,v})) {
				ans[id]=H;
			}
		}
	}
	for(auto a:s[x]) {
		s[y].insert(a);
	} s[x]={};
}
void bfs(int x,int y,int H) {//cerr<<"BFS::"<<x<<' '<<y<<' '<<H<<endl;
	queue<pair<int,int>> q;
	if(p[x][y]>r[x][y]) r[x][y]=p[x][y],q.push({x,y});
	while(!q.empty()) {
		auto[i,j]=q.front();q.pop();//cerr<<"new::"<<i<<' '<<j<<endl;
		for(auto[u,v]:nei(i,j)) {
			if(h[x][y]-h[u][v]+p[x][y]-abs(x-u)-abs(y-v)>r[u][v]) {
				r[u][v]=h[x][y]-h[u][v]+p[x][y]-abs(x-u)-abs(y-v);
				q.push({u,v});
			}
			if(h[x][y]-h[u][v]+p[x][y]-abs(x-u)-abs(y-v)>=0) /*cerr<<"BING:"<<x<<' '<<y<<' '<<u<<' '<<v<<' '<<H<<endl,*/mer(id(x,y),id(u,v),H);
		}
	}
}
int main() {
	n=read();m=read();q=read();
	int mi=1e9;
	memset(r,-1,sizeof r);
	F(i,1,n) F(j,1,m) h[i][j]=read(),mi=min(mi,h[i][j]),init(i,j);
	vec<vec<pair<int,int>>> V(n+m+2);
	F(i,1,n) F(j,1,m) p[i][j]=read();
	F(i,1,n) F(j,1,m) h[i][j]-=mi,V[h[i][j]]+=make_pair(i,j);
	F(i,1,q) {
		int a=read(),b=read(),c=read(),d=read();
		que[a][b]+=make_tuple(c,d,i);
		que[c][d]+=make_tuple(a,b,i);
		ans[i]=-1;
	}
	UF(H,n+m,0) for(auto[i,j]:V[H]) bfs(i,j,H+mi);
	F(i,1,q) printf("%d\n",ans[i]);
	return 0;
}
```

---

