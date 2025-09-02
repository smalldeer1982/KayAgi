# [AGC025D] Choosing Points

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc025/tasks/agc025_d

高橋君は平面上の点集合について研究しています。 高橋君にとって、座標平面上の点の集合 $ S $ が *いい集合* であるとは、$ S $ が以下の条件をともに満たすことを指します。

- $ S $ に属するどの $ 2 $ 点間の距離も $ \sqrt{D_1} $ でない。
- $ S $ に属するどの $ 2 $ 点間の距離も $ \sqrt{D_2} $ でない。

ただし、$ D_1,D_2 $ は高橋君の定めた正整数の定数です。

ここで、$ X $ を座標平面上の格子点 $ (i,j) $ であって $ 0\ ≦\ i,j\ <\ 2N $ を満たす点 $ (i,j) $ 全体からなる集合としましょう。 研究者の高橋君は、$ D_1,D_2 $ をどのように選んでも、$ X $ からうまく $ N^2 $ 個の点を選ぶことで、それらがいい集合をなすことを示しました。 しかし、実際にどのように選べばいい集合になるかは分かっていません。 そこで、高橋君の代わりに、$ X $ のサイズ $ N^2 $ の部分集合であって、いい集合となるものを見つけてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 300 $
- $ 1\ ≦\ D_1\ ≦\ 2×10^5 $
- $ 1\ ≦\ D_2\ ≦\ 2×10^5 $
- 入力される値は全て整数である

### Sample Explanation 1

この場合 $ 2 $ 点間の距離としてありうる値は $ 2 $ と $ 2\sqrt{2} $ のみであるから、確かに条件を満たします。

## 样例 #1

### 输入

```
2 1 2```

### 输出

```
0 0
0 2
2 0
2 2```

## 样例 #2

### 输入

```
3 1 5```

### 输出

```
0 0
0 2
0 4
1 1
1 3
1 5
2 0
2 2
2 4```

# 题解

## 作者：关怀他人 (赞：12)

#### Solution
首先只考虑一个$D$的情况，我们将所有距离为$\sqrt D$的点连边，得到的一定是一张二分图。证明：设$D=4^k\cdot p(p \bmod 4 \neq 0)$，那么所有距离为$D$的点对都可以写成$(2^k\cdot a,2^k \cdot b)$的形式，其中满足$a^2+b^2=p$。于是可以只考虑$\bmod 2^k$的等价类。
1. $p\bmod 4 \equiv 3$，此时不存在合法点对。
2. $p\bmod 4 \equiv 1$，此时$a$和$b$一奇一偶，按$a+b$的奇偶性黑白染色即可。
3. $p\bmod 4 \equiv 2$，此时$a$和$b$都为奇数，按$a$的奇偶性黑白染色即可。

由于一定能黑白染色，所以就证明了得到的图一定是二分图。

那么问题变为有两张$(2n)^2$个点的二分图，要求取出一个大小为$n^2$的点集，使得这个点集在两张图上均为独立集。给两张图分别二染色后，共有四种颜色，考虑给每个格子赋上两个二分图中的各一种颜色，共有$4$中不同的颜色组合，根据鸽巢原理，一定能找到一种颜色组合满足这样的格子至少有$n^2$个。

时间复杂度$\mathcal O(n^2)$
#### Code
```cpp
int n,D1,D2;
int col[3][MAXN][MAXN],cnt[2][2];

void Solve(int d,int id){
    int k = 0;
    while(d % 4 == 0) d /= 4, k += 1;
    if(d % 4 == 3) return;
    k = 1 << k;
    if(d % 4 == 1){
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++)
                col[id][i][j] = ((i - 1) / k + (j - 1) / k) & 1;
        }
    }else{
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++)
                col[id][i][j] = ((i - 1) / k) & 1;
        }
    }
}

int main(){
    scanf("%d%d%d",&n,&D1,&D2);
    n <<= 1;
    Solve(D1,1);
    Solve(D2,2);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++)
            cnt[col[1][i][j]][col[2][i][j]] += 1;
    } 
    int x,y;
    for(int i = 0;i < 2;i++){
        for(int j = 0;j < 2;j++){
            if(cnt[i][j] >= n * n / 4)
                x = i, y = j;
        }
    }
    int tot = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(col[1][i][j] == x && col[2][i][j] == y){
                printf("%d %d\n",i - 1,j - 1);
                tot += 1;
                if(tot >= n * n / 4) return 0;
            }
        }
    }
    return 0;
}
```

---

## 作者：SDNetFriend (赞：4)

## AT3967 [AGC025D] Choosing Points 题解

### 整体情况

借鉴了现有题解奇偶点的讨论方式，并在处理 $4\mid d$ 的情况时运用了类似递归的证明思路。如果有错误希望您能指出。

### 题意这里不再赘述

[AT3967 [AGC025D] Choosing Points](https://www.luogu.com.cn/problem/AT3967)

### 朴素分析

原题中相距为 $\sqrt d$ 的点对实际上即两个点 $(x_1,y_1),(x_2,y_2)$ 满足 $(x_1-x_2)^2+(y_1-y_2)^2=d$。

### 分析性质

我们可以发现我们是无法找到不同的三个整点使其两两连线构成等边三角形的。不只是等边三角形，还有正五、七、九……边形都无法构成。这给我们了启示，即如果给距离相同的整点连边不会出现奇环，这个性质和二分图很类似，那我们尝试证明：距离相同的点两两连边会构成二分图。

那我们假设这个距离是 $d$，分析下上文的式子，我们发现 $x_1-x_2$ 的奇偶性和 $(x_1-x_2)^2$ 的奇偶性是一致的，也就是说式子左边的奇偶性等同于 $x_1+y_1-(x_2+y_2)$。

那么接着分析，对于 $d$ 为奇数则 $x_1+y_1$ 和 $x_2+y_2$ 的奇偶性不同，否则就相同。那我们把横纵坐标为奇数、偶数的点分别称为奇点和偶点，那么当 $d$ 为奇数时，二分图两个集合是奇点和偶点；如果是偶数，那么就是奇点和奇点，偶点和偶点之间连边，需要进一步讨论。

#### 对于 $d$ 为偶数的情况

这种情况下奇点图和偶点图是对称的，那么我们只考虑偶点图的情况。

我们可以发现，如果 $d\equiv 2\mod 4$，那这每对点的情况就会是 $($奇$,$奇$)$和$($偶$,$偶$)$，这样也可以将它们划分进两个集合里面，同样是二分图，不必过多讨论。

对于 $4\mid d$ 的情况，也就是每对点的情况是$($偶$,$偶$)$和$($偶$,$偶$)$或者$($奇$,$奇$)$和$($奇$,$奇$)$，这也是两种完全对称的情况，故这里只考虑横纵坐标均是偶数的情况。

对于最初始的式子，我们转化为 $4(x_1-x_2)^2+4(y_1-y_2)^2=d$,然后
两边约掉 $4$，我们会发现除了 $4\mid d$ 以外的所有情况我们都证明了是二分图，那这样我们可以反复进行约 $4$ 的操作，每次把 $4\mid d$ 且存在合法点对横纵坐标均是偶数的情况递归讨论，直到不存在这种情况，于是得证。

### 实现思路

我们对两个 $d$ 分别处理，这样每个点在两张图里面都在某个集合中，那这种在集合中的存在状态只有四种，因为二分图同一个集合中是不会连边的，所以一定可以找到一个点数大于等于 $\frac{2n\times 2n}{4}$ 的集合作为答案。

这样只需建图后 DFS 染色即可。

### 贴代码

```cpp
#include <bits/stdc++.h>
#define lint long long
#define rint register int
using namespace std;
inline lint read(){
	char c;lint f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const int N=310,P=N*N*4;
int hed[P],ver[P<<5],nxt[P<<5],ne=1;
inline void ae(int u,int v){
	if(!u||!v)return;
	ver[++ne]=v;
	nxt[ne]=hed[u];
	hed[u]=ne;
}
int co[P][2];
void DFS(int u,int c,int t){//染色 
	co[u][t]=c;
	for(rint e=hed[u];e;e=nxt[e]){
		int v=ver[e];
		if(co[v][t]==-1)DFS(v,c^1,t);		
	}
}
int n,d[2];
inline int id(int x,int y){
	if(x<1||x>2*n||y<1||y>2*n)return 0;
	else return (x-1)*2*n+y;
}
inline void build(int t){//建图 
	memset(hed,0,sizeof hed);
	//i仅是x之差 
	for(rint i=0;i*i<=d[t];++i){
		int j=(int)sqrt(d[t]-i*i);
		if(j*j+i*i!=d[t])continue;
		for(rint x=1;x<=2*n;++x)
			for(rint y=1;y<=2*n;++y){
				ae(id(x,y),id(x-i,y-j));
				if(j)ae(id(x,y),id(x-i,y+j));
				if(i)ae(id(x,y),id(x+i,y-j));
				if(i&&j)ae(id(x,y),id(x+i,y+j));
			}
	}
}
int sx[P][4],sy[P][4],tp[4];
int main(){
	n=read();
	d[0]=read();d[1]=read();
	memset(co,-1,sizeof co);
	for(rint t=0;t<2;++t){
		build(t);
		for(rint i=1;i<=n*n<<2;++i)
			if(co[i][t]==-1)DFS(i,0,t);
	}
	for(rint x=1;x<=2*n;++x)
		for(rint y=1;y<=2*n;++y){
			int i=id(x,y);
			int p=co[i][1]<<1|co[i][0];
			++tp[p];
			sx[tp[p]][p]=x;sy[tp[p]][p]=y;
			if(tp[p]==n*n)goto ep;
		}
	ep:for(rint i=0;i<4;++i){
		if(tp[i]<n*n)continue;
		while(tp[i]){
			printf("%d %d\n",sx[tp[i]][i]-1,sy[tp[i]][i]-1);
			--tp[i];
		}
		break;
	}
	return 0;
}


```




---

## 作者：樱雪喵 (赞：2)

Tags: 构造，二分图

考虑只有一个 $D$ 的限制的情况怎么做。将图上所有距离恰为 $\sqrt{D}$ 的整点之间连边，会得到一张二分图。

接下来证明这个结论。这里我们钦定边的其中一个起点是 $(0,0)$，其余连边都可以平移得到。

将 $D$ 表示为 $4^p\times q\ (q\bmod 4\neq 0)$ 的形式，那么边的另一端 $(x,y)$ 可以表示为 $(2^p\times a,2^p\times b)$。根据 $q\bmod 4$ 的值分类讨论：

- $q\bmod 4=1$，则 $a$ 和 $b$ 奇偶性不同。这说明 $x,y$ 奇偶性相同的点只会向奇偶性不同的点连边，这两个集合独立。
- $q\bmod 4=2$，则 $a\bmod 2=1$ 且 $b\bmod 2=1$。这时 $x,y$ 奇偶性相同的点只会向奇偶性相同的点连边。
- $q\bmod 4=3$，但 $a,b\bmod 2\in [0,1]$。因此这种情况不存在。

对两个 $D$ 分别建立二分图并染色，根据两个图上的颜色一共可以把点分为四类。那么 $4n^2$ 个点中至少有一类不少于 $n^2$ 个，找到这一类并输出即可。

```cpp
const int N=605;
int n,D1,D2,col[N][N],cnt[N],vis[N][N];
typedef pair<int,int> pir;
vector<pir> v;
int dx[4]={1,-1,1,-1};
int dy[4]={-1,1,1,-1};
void dfs(int x,int y,int tp)
{
	if(tp==2) cnt[col[x][y]]++;
	for(int w=0;w<4;w++)
		for(auto &[Dx,Dy]:v)
		{
			int nx=x+Dx*dx[w],ny=y+Dy*dy[w];
			if(nx<0||ny<0||nx>=(n<<1)||ny>=(n<<1)||vis[nx][ny]) continue;
			int ncol=(col[x][y]&tp)^tp;
			col[nx][ny]^=ncol,vis[nx][ny]=1,dfs(nx,ny,tp);
		}
}
void get(int D,int tp)
{
	v.clear();
	for(int i=0;i<(n<<1);i++)
		for(int j=0;j<(n<<1);j++)
		{
			vis[i][j]=0;
			if(i*i+j*j==D) v.push_back(pir(i,j));
		}
	for(int i=0;i<(n<<1);i++)
		for(int j=0;j<(n<<1);j++)
			if(!vis[i][j]) dfs(i,j,tp);
}
int main()
{
	n=read(),D1=read(),D2=read();
	get(D1,1);get(D2,2);
	for(int i=0;i<4;i++) if(cnt[i]>=n*n)
	{
		int tot=0;
		for(int x=0;x<(n<<1);x++)
			for(int y=0;y<(n<<1);y++)
			{
				if(tot==n*n) break;
				if(col[x][y]==i) tot++,printf("%d %d\n",x,y);
			}
		break;
	}
	return 0;
}
```

---

## 作者：MortisM (赞：2)

[AGC025D Choosing Points](https://atcoder.jp/contests/agc025/tasks/agc025_d)

**Hint：二分图。**

这道题最难的地方是观察出来二分图的性质。

通过直觉可以发现不会存在等边三角形，即不会存在 **三个格点之间的距离都是 $d$**，也就是所有距离为 $d$ 的格点间连边会构成一张二分图。下面来证明这件事。

先将距离为 $d$ 的式子列出来：$(x_1-x_2)^2+(y_1-y_2)^2=d$。对 $d$ 的奇偶性分开讨论。若 $d$ 为奇数，则 $(x_1-x_2)^2$ 和 $(y_1-y_2)^2$ 必然一奇一偶。又因为一个数的平方与该数奇偶性相同，所以 $x_1-x_2$ 和 $y_1-y_2$ 一奇一偶，则 $x_1-y_1$ 和 $x_2-y_2$ 一奇一偶。至此，把 $x-y$ 为奇数的选成一个集合，$x-y$ 为偶数的选成一个集合就可以了。

若 $d$ 为偶数，则分两种情况：$d\equiv 2\pmod 4$ 和 $d\equiv 0\pmod 4$。先考虑前者，容易发现 $x_1-x_2$ 和 $y_1-y_2$ 必须同为奇数，即 $x_1,x_2$ 和 $y_1,y_2$ 奇偶性都不同，所以在 $x,y$ 奇偶性相同与否的两个独立图中都是二分图，合起来也是。

下面剩下 $4|d$ 的情况。由于 $4|d$，所以可以将等式两边都除以 $4$，即：
$$
(\frac{x_1-x_2}{2})^2+(\frac{y_1-y_2}{2})^2=\frac{d}{4}
$$

还可以继续往下除，直到 $\frac{d}{4^p}$ 不为 $4$ 的倍数为止，而其他情况我们都证明了二分图，所以 $d\equiv 0\pmod 4$ 的情况也证明完毕。

有了这个结论以后，可以对 $D_1$ 和 $D_2$ 都分别拉一张二分图出来，每个点在两张图中都有染色，共四种情况：$(0,0),(0,1),(1,0),(1,1)$（$(x,y)$ 表示在第一张图中颜色为 $x$，第二张图中颜色为 $y$）。根据鸽笼原理，一共 $(2n)^2=4n^2$ 个点，这四种的点必然有一种是 $\geq n^2$ 的。

实现就不多讲了，我用的最暴力的 $\mathcal{O}(n^3)$ 也可以通过。[代码](https://atcoder.jp/contests/agc025/submissions/36811267)。

---

## 作者：syzf2222 (赞：2)

单考虑一个限制条件 $d$，将距离为 $\sqrt d$ 的点连边，下面证明这是二分图。

对于两个点 $(x_1,y_1),(x_2,y_2)$，它们有边则 $(x_1-x_2)^2+(y_1-y_2)^2=d$

定义 $x+y$ 为奇数的点为奇点，反之为偶点。

若 $d$ 为奇数，则 $x+y$ 的奇偶性不同，奇点与偶点连边。

若 $d$ 为偶数，则奇点与奇点连边，偶点与偶点连边，此时奇偶相互独立且等价。

若 $ d \equiv 2\pmod 4$，则 $x_1,x_2$ 和 $y_1,y_2$ 的奇偶性都不同，在奇点图和偶点图中都是二分图。

若 $4|d$，找到最大的 $p\in N^+$ 使 $2^{2p}|d$ ，容易证明$2^p|x_1-x_2,y_1-y_2$ 。

则$x_1,x_2$ 和 $y_1,y_2$ 分别在相同的模 $2^p$ 同余类里，同余类相互独立。

此时令 $c=\frac{d}{2^{2p}},x'=[\frac{x}{2^p}],y'=[\frac{y}{2^p}]$

$c\equiv 1,2\pmod 4$ 时与上面类似，而 $c$不可能模 $4$ 余 $0,3$ 。

故此图一定为二分图。

对$d_1,d_2$分别对原图连边、染色，把每个点分进四个集合，分别为$\{\text{黑,黑}\},\{\text{黑,白}\},\{\text{白,黑}\},\{\text{白,白}\}$  。由平均值原理，必有一个集合大于等于 $N^2$ 。

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=8e5+10;
const int mod=1e9+7;
int n,d1,d2;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int beg[maxn],nex[maxn*10],to[maxn*10],e;
inline void add(int x,int y){
	e++;nex[e]=beg[x];
	beg[x]=e;to[e]=y;
}
int dx[4]={1,-1,1,-1};
int dy[4]={1,-1,-1,1};
inline int id(int x,int y){return x*2*n+y;}
int col1[maxn],col2[maxn];
inline void dfs1(int x,int w){
	col1[x]=w;
	for(int i=beg[x];i;i=nex[i]){
		int t=to[i];
		if(col1[t]!=-1)continue;
		dfs1(t,w^1);
	}
}
vector<int>g[4];
inline void dfs2(int x,int w){
	col2[x]=w;
	for(int i=beg[x];i;i=nex[i]){
		int t=to[i];
		if(col2[t]!=-1)continue;
		dfs2(t,w^1);
	}
}
int main(){
	n=read(),d1=read(),d2=read();
	memset(col1,-1,sizeof(col1));
	memset(col2,-1,sizeof(col2));
	for(int i=0;i*i<=d1;i++){
		int j=sqrt(d1-i*i);
		if(i*i+j*j!=d1)continue;
		for(int a=0;a<2*n;a++)
			for(int b=0;b<2*n;b++)
				for(int k=0;k<=3;k++){
					int aa=a+dx[k]*i;
					int bb=b+dy[k]*j;
					if(aa>=0&&aa<2*n&&bb>=0&&bb<2*n)
						add(id(a,b),id(aa,bb));
				}
	}
	for(int i=0;i<4*n*n;i++)
		if(col1[i]==-1)dfs1(i,0);
	memset(beg,0,sizeof(beg));e=0;
	for(int i=0;i*i<=d2;i++){
		int j=sqrt(d2-i*i);
		if(i*i+j*j!=d2)continue;
		for(int a=0;a<2*n;a++)
			for(int b=0;b<2*n;b++)
				for(int k=0;k<=3;k++){
					int aa=a+dx[k]*i;
					int bb=b+dy[k]*j;
					if(aa>=0&&aa<2*n&&bb>=0&&bb<2*n)
						add(id(a,b),id(aa,bb));
				}
	}
	for(int i=0;i<4*n*n;i++)
		if(col2[i]==-1)dfs2(i,0);
	for(int i=0;i<4*n*n;i++)
		g[(col1[i]<<1)|col2[i]].push_back(i);
	for(int i=0;i<4;i++)
		if(g[i].size()>=n*n){
			for(int j=0;j<n*n;j++)
				printf("%d %d\n",g[i][j]/(2*n),g[i][j]%(2*n));
			break;
		}
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：Needna (赞：1)

题目解释：要从一个矩阵中找出至少n个点使得任意两点之间距离不为 $\sqrt{D_1} $ 或 $\sqrt{D_2} $。

思路：我们先假设只有 $\sqrt{D_1} $ 一个限制。那么我们就可以把矩阵中的点分组且组中的点互不违反规则，然后随便选一组即可。思考每一组的性质，这里有一个结论就是一个人矩阵只有两组，也就是矩阵可以构成二分图。

原理：因为假如一个正多边形有奇数条边，那么这个正多边形的每个角的 $\tan \alpha $ 都为无理数，可以感性理解一下。

我们回到题目，有两组限制，那么我们就每一个限制都分成 $2$ 组，那么对于每个点就会有 $4$ 种情况，每一种情况中的点就是符合题目要求的，因为有  $2n\times2n\div4=n 
^{2}$ 直接输出最大的一组即可。

考虑如何处理分组，可以用dfs，也可以用余数分类讨论,也是本题解的做法。简单来说就是构造 $x^{2} +y^{2}=D$（注意此时 $D$ 是缩放过的，$x$ 和 $y$ 同理）然后分析 $x$ 和 $y$ 的偶性。

1. 当 $D\equiv 1 \pmod{4}$ 时 $x+y$ 奇偶性相同的点对在一组。
   
2. 当 $D\equiv 3 \pmod{4}$ 时 $x$ 奇偶性相同的点对在一组。

ac code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=6e2+10;
int n,d1,d2,t1,t2,f[N][N][2],t[5],cnt; 
int main(){
    cin>>n>>d1>>d2;
    while(!(d1%4)) d1/=4,t1++;while(!(d2%4)) d2/=4,t2++;
    for(int i=1;i<=n*2;i++)
    	for(int j=1;j<=n*2;j++){
        	if(d1%4==1) f[i][j][0]=((i>>t1)+(j>>t1))&1;
        	else f[i][j][0]=(i>>t1)&1;
        	if(d2%4==1) f[i][j][1]=((i>>t2)+(j>>t2))&1;
        	else f[i][j][1]=(i>>t2)&1;
        	t[((f[i][j][0])<<1)+(f[i][j][1])]++;}
    for(int i=0;i<=3;i++){if(t[i]>=n*n) t1=(i>>1),t2=i%2;}   
    for(int i=1;i<=n*2;i++)
    	for(int j=1;j<=n*2;j++)
    		if(f[i][j][0]==t1&&f[i][j][1]==t2&&cnt<n*n)
    			cnt++,cout<<i-1<<" "<<j-1<<'\n';
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc025_d)

**题目大意**

> 给定 $n,x,y$，在 $2n\times 2n$ 的网格中选 $n^2$ 个点使得任意两个点之间的距离不为 $\sqrt x$ 或 $\sqrt y$。
>
> 数据范围：$n\le 300$。

**思路分析**

设 $x=dx^2+dy^2$，分讨 $x\bmod 4$ 的奇偶性：

- $x\bmod 4=2$：说明 $dx,dy$ 为奇数，因此距离为 $\sqrt x$ 的点横坐标奇偶性不同。
- $x\bmod 4=2$：说明 $dx,dy$ 恰有一个奇数，因此距离为 $\sqrt x$ 的点黑白间隔染色后颜色不同。
- $x\bmod 4=0$：说明 $dx,dy$ 均为偶数，将整个网格按横纵坐标 $\bmod 2$ 分成四个完全相等的部分。

因此我们发现距离为 $\sqrt x$ 的点对一定可以被黑白染色，即形成的图是二分图。

那么距离为 $\sqrt x$ 或 $\sqrt y$ 的点是两张二分图，我们要在其中找到一个大小 $\ge \dfrac 14|V|$ 的独立集。

这是简单的，在两张二分图上黑白染色，如果两个点在两张二分图上颜色都相同就划入同一个等价类，可以把 $V$ 恰分成 $4$ 个等价类，根据抽屉原理，直接取最大的一个即可。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=605;
int n,k1,k2;
void col(auto a,int k) {
	int x=0;
	while(k%4==0) k>>=2,++x;
	if(k%4==1) {
		for(int i=0;i<n;++i) for(int j=0;j<n;++j) a[i][j]=((i>>x)+(j>>x))&1;
	} else if(k%4==2) {
		for(int i=0;i<n;++i) for(int j=0;j<n;++j) a[i][j]=i>>x&1;
	}
}
bool f[MAXN][MAXN],g[MAXN][MAXN];
signed main() {
	scanf("%d%d%d",&n,&k1,&k2),n*=2;
	col(f,k1),col(g,k2);
	for(int p:{0,1}) for(int q:{0,1}) {
		vector <array<int,2>> wys;
		for(int i=0;i<n;++i) for(int j=0;j<n;++j) {
			if(f[i][j]==p&&g[i][j]==q) wys.push_back({i,j});
		}
		if(wys.size()>=n*n/4) {
			wys.resize(n*n/4);
			for(auto z:wys) printf("%d %d\n",z[0],z[1]);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：St_john (赞：1)

# [[AGC025D] Choosing Points](https://www.luogu.com.cn/problem/AT_agc025_d)



------------


* 结论：将所有距离为 $\sqrt{D}$ 的点染色，最终是个二分图。

证明：  

设距离为 $\sqrt{D}$ 的两个点为 $A(x_A,y_A),B(x_B,y_B)$ 。  
（$D \equiv 3 \pmod 4$ 时是不存在距离为 $\sqrt{D}$ 的点的 ，因为 $x^2 \equiv 0,1 \pmod 4$）

1. $D$ 为奇数。$(x_A-x_B)^2$ 和 $(y_A-y_B)^2$ 的奇偶性是不同的， $(x_A-x_B)$  和 $(y_A-y_B)$ 的奇偶性也是不同的，进而可得 $(x_A+y_A)-(x_B+y_B)$ 恒为奇数，所以这时按 $x+y$ 的奇偶性染色，可以得到二分图。    
1. $D$ 为偶数。 将 $D$ 除 $2$ ，坐标除 $\sqrt{2}$，转化为子问题。  

最后可证，这一定是个二分图。  




------------

分别对 $D_1$ 和 $D_2$ 构造出二分图，并染色。  
最后将 $4n^2$ 个点分到颜色的 $4$ 种集合中，必有一种集合的元素数目 $\geqslant n^2$ 。  

构造即可。  

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#define _for(i,a,b) for(register int i=(a);i<=(b);++i)
#define __for(i,a,b) for(register int i=(a);i>=(b);--i)
#define Re register int
#define il inline
#define pc putchar
using namespace std;
typedef long long ll;
const int N=600+10,M=531441+10,inf=2147483647;
il int re(){
	int x=0;
	bool f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
void pr(int x){
	if(x<0) x=-x,pc('-');
	if(x>9) pr(x/10);
	pc(x%10|48);
}

int n,nn,d[2];
int col[2][N][N];
vector<pair<int,int> > v[2];
int dx[5]={0,1,1,-1,-1},dy[5]={0,-1,1,-1,1};

void dfs(bool type,int x,int y,bool c){
	if(x<1||y<1||x>nn||y>nn||~col[type][x][y])
		return ;
	col[type][x][y]=c;
	for(auto i:v[type])
		_for(j,1,4)
			dfs(type,x+dx[j]*i.first,y+dy[j]*i.second,!c);
}
int num[4];

signed main(){
	n=re(),d[0]=re(),d[1]=re();
	nn=n*2;
	_for(k,0,2)
		_for(i,0,nn)
			_for(j,0,nn)
				if(i*i+j*j==d[k])
					v[k].push_back({i,j});
	memset(col,-1,sizeof(col));
	_for(i,1,nn)
		_for(j,1,nn)
			dfs(0,i,j,0),dfs(1,i,j,0);
	_for(i,1,nn)
		_for(j,1,nn)
			++num[col[0][i][j]<<1|col[1][i][j]];

	int need=0;
	_for(i,0,3)
		if(num[i]>=n*n){
			need=i;
			break;
		}
	int num=0;
	_for(i,1,nn)
		_for(j,1,nn)
			if((col[0][i][j]<<1|col[1][i][j])==need){
				pr(i-1),pc(' '),pr(j-1),pc('\n');
				if(++num==n*n) return 0;
			}
	return 0;
}
```

---

## 作者：GIFBMP (赞：1)

考虑只有一个限制怎么做，我们对于原图中的两点，若距离为 $\sqrt{d}$ 就连一条边。我们可以证明，这幅图是一张二分图。证明如下：

设 $d=4^p\times q\ (q\not\equiv 0\pmod 4)$，则距离为 $\sqrt{d}$ 的点对的 $x,y$ 坐标之差分别可以表示成 $2^p\times a$，$2^p\times b$ 的形式，其中 $a^2+b^2=q$。

按 $q\bmod 4$ 的余数分类讨论：

1. 若 $q\equiv 1\pmod 4$，则 $a,b$ 奇偶性必定不同，那么原图坐标转化之后的 $a,b$ 奇偶性相同的点对必然距离不为 $\sqrt{d}$，两两之间不连边，此时这幅图是二分图。

2. 若 $q\equiv 2\pmod 4$，则 $a,b$ 一定都是奇数，那么原图中转化后 $a$ 奇偶性相同的点必然两两不连边，此时这幅图是二分图。

3. 若 $q\equiv 3\pmod 4$，因为 $a^2\bmod 4\in\{0,1\}$，$b^2\bmod 4\in\{0,1\}$，因此 $a^2+b^2\bmod 4\in\{0,1,2\}$，这种情况不可能发生。

对于 $d1,d2$ 都建出图之后统计每个点在两个图中的颜色，根据颜色的不同可以将点分为四个集合。根据抽屉原理，必有一个集合的元素个数 $\ge n^2$，这题就做完了。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
int n , d1 , d2 , c1[610][610] , c2[610][610] , t1 , t2 , t[2][2] , cnt ;
int main () {
	scanf ("%d%d%d" , &n , &d1 , &d2) ;
	for (; d1 % 4 == 0 ; d1 /= 4 , t1++) ;
	for (; d2 % 4 == 0 ; d2 /= 4 , t2++) ;
	for (int i = 1 ; i <= 2 * n ; i++)
		for (int j = 1 ; j <= 2 * n ; j++) {
			if (d1 % 4 == 1) c1[i][j] = ((i >> t1) + (j >> t1)) & 1 ;
			if (d1 % 4 == 2) c1[i][j] = (i >> t1) & 1 ;
			if (d2 % 4 == 1) c2[i][j] = ((i >> t2) + (j >> t2)) & 1 ;
			if (d2 % 4 == 2) c2[i][j] = (i >> t2) & 1 ;
		}
	for (int i = 1 ; i <= 2 * n ; i++)
		for (int j = 1 ; j <= 2 * n ; j++)
			t[c1[i][j]][c2[i][j]]++ ;
	for (int i = 0 ; i < 2 ; i++)
		for (int j = 0 ; j < 2 ; j++)
			if (t[i][j] >= n * n) t1 = i , t2 = j ;
	for (int i = 1 ; i <= 2 * n ; i++)
		for (int j = 1 ; j <= 2 * n ; j++)
			if (c1[i][j] == t1 && c2[i][j] == t2 && cnt < n * n)
				cnt++ , printf ("%d %d\n" , i - 1 , j - 1) ;
	return 0 ;
}
```

---

## 作者：xht (赞：0)

## [Choosing Points](https://atcoder.jp/contests/agc025/tasks/agc025_d)

### 题意

- 构造 $n^2$ 个点，满足每个点的坐标都是 $[0,2n)$ 中的整数，且任一对点的距离都既不是 $\sqrt {d_1}$ 也不是 $\sqrt {d_2}$。
- $n \le 300$，$d_1,d_2 \le 2 \times 10^5$。

### 题解

考虑将距离为 $\sqrt d$ 的点连边，可以证明得到的是一个二分图。

> 设 $d = 4^kp$，其中 $p \bmod 4 \ne 0$。
>
> 若存在 $x^2+y^2 = d$，则 $(x,y)$ 一定可以写成 $(2^ku, 2^kv)$ 的形式，其中 $u^2+v^2=p$，反证很容易证明。
>
> 只考虑 $\bmod\ 2^k$ 的等价类。若 $p \bmod 4 = 1$，则 $u,v$ 奇偶性不同，按 $u+v$ 的奇偶性染色即可；若 $p \bmod 4 = 2$，则 $u,v$ 均为奇数，按 $u$ 的奇偶性染色即可；若 $p \bmod 4 = 3$，则不存在合法点。

于是问题变成我们得到了两张二分图，要求取出一个包含 $\frac 14$ 的点集，考虑被两张二分图分成的四类中包含点数最多的一类即可。

时间复杂度 $\mathcal O(n^2)$。

### 代码

```cpp
const int N = 607;
int n;
struct G {
	int d, c[N][N];
	vector<pi> p;
	inline bool pd(int x, int y) {
		return x >= 0 && x < n * 2 && y >= 0 && y < n * 2 && !~c[x][y];
	}
	void dfs(int x, int y, int z) {
		c[x][y] = z;
		for (pi o : p) {
			int X = x + o.fi, Y = y + o.se;
			if (pd(X, Y)) dfs(X, Y, z ^ 1);
		}
	}
	inline void main() {
		rd(d);
		for (int i = 0; i < n * 2; i++)
			for (int j = 0; j < n * 2; j++)
				c[i][j] = -1;
		for (int i = 1 - n * 2; i < n * 2; i++)
			for (int j = 1 - n * 2; j < n * 2; j++)
				if (i * i + j * j == d) p.pb(mp(i, j));
		for (int i = 0; i < n * 2; i++)
			for (int j = 0; j < n * 2; j++)
				if (pd(i, j)) dfs(i, j, 0);
	}
} g[2];
vector<pi> p[4];

int main() {
	rd(n), g[0].main(), g[1].main();
	for (int i = 0; i < n * 2; i++)
		for (int j = 0; j < n * 2; j++)
			p[g[1].c[i][j]*2+g[0].c[i][j]].pb(mp(i, j));
	int o = 0;
	for (int i = 1; i < 4; i++)
		if (p[i].size() > p[o].size()) o = i;
	while ((int)p[o].size() > n * n) p[o].pop_back();
	for (pi x : p[o]) print(x.fi, x.se);
	return 0;
}
```

---

