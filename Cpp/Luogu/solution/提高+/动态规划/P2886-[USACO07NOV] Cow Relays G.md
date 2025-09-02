# [USACO07NOV] Cow Relays G

## 题目描述

给定一张 $T$ 条边的无向连通图，求从 $S$ 到 $E$ 经过 $N$ 条边的最短路长度。

## 说明/提示

对于所有的数据，保证 $1\le N\le 10^6$，$2\le T\le 100$。

所有的边保证 $1\le u,v\le 1000$，$1\le w\le 1000$。

## 样例 #1

### 输入

```
2 6 6 4
11 4 6
4 4 8
8 4 9
6 6 8
2 6 9
3 8 9```

### 输出

```
10```

# 题解

## 作者：guodong (赞：74)

# 浅谈矩阵加速优化动态规划
~~本文只适用于OI学习~~
## 矩阵乘法

给定两个矩阵

$A=\begin{bmatrix}1 &2 &3  \\ 4& 0&1\end{bmatrix}$

$B=\begin{bmatrix}1 &2 \\ 2 &0 \\ 3 &1\end{bmatrix}$

那么,$A \times B=C$

$C=\begin{bmatrix}1\times1+2\times2+3\times3 & 1\times 2 +2\times0+3\times1 \\ 4\times1+0\times 2 + 1\times3 & 4\times2+0\times 0 +1\times 1\end{bmatrix}$
 
用数学公式表述那就是：
$C_{ij}=\sum_{k=1}^{n}A[i][k]*B[k][j]$

一般来说，$A$的行数$B$的列数，$B$的行数也等于$A$的列数，当两个不满足上述条件的矩阵相乘时，我们可以通过**补零**的方式使他们满足。
> 由于矩阵乘法满足分配率，结合律（**但是不满足交换律！**）,所以我们可以通过**矩阵快速幂**的方法来加速

$tips:$矩阵加速利用的是矩阵乘法满足结合律

---
## Floyd
$Floyd$是一种最短路算法，适用于点数较少的图

$Floyd$的本质是**动态规划**,它的状态定义以及转移：
> 设$f[i][j]$为$i$到$j$的最短距离

> $f[i][j]=min(f[i][j],f[i][k]+f[k][j])$

代码实现：
```cpp
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
``` 
我们魔改一下：
```cpp
	int C[N][N];
	memset(C,127,sizeof C); // inf
	for(int k=1;k<=n;j++)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				C[i][j]=min(C[i][j],A[i][k]+A[k][j]);
	}
	memcpy(A,C,sizeof C);	
```
$Q$:这两种写法等价吗？

$A$:当然不是，floyd是动态规划```f[i][k]+f[k][j]```是已知的最优状态的转移，但是第二种却是两个初始矩阵简单的相乘。

$tips:$这里的矩阵乘法由原来的$C[i][j]=A[i][k]+B[k][i]$,变成了$C[i][j]=\color{red} {min(C[i][j],A[i][k]+A[k][j])}$
之所以可以加$\color{red} min$，是因为$min$也满足结合律:$min(min(a,b),c)=min(a,b,c)=min(a,min(b,c))$


那么它代表的意义又是什么呢？
先放出[例题](https://www.luogu.org/problem/P2886)

让我们做下列这个实验：
实验代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int A[1001][1001];
int C[1001][1001];
signed main()
{
	freopen("data.in","r",stdin);
	int n,m;
	scanf("%d %d",&n,&m);
	memset(A,50,sizeof A);
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d %d %d", &a,&b,&c);
		A[a][b]=A[b][a]=c;
		A[i][i]=0;
	}
	int tmp=1;// 看这里！！！！！！！！
	while(tmp--)
	{
		memset(C,127 , sizeof C);

		for(int k=1;k<=n;k++)
		{
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					C[i][j]=min(C[i][j],A[i][k]+A[k][j]);
		}
		memcpy(A,C,sizeof C);	
	}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				if(A[i][j]<100)
					printf("%d ",A[i][j]);
				else
				{
					printf("X ");
				}
			printf("\n");
		}
}
```
给出一条链：

$1-2-3->4-5\dots-10$

输入的邻接矩阵$A$，可以理解成**经过一条边的最短路**，我们记做$A^{1}$.

$C=A\times A, C= A^{2}$，然后把$A$赋值成为$C$，也就是$A^{2}$

容易发现，当$tmp=x$时，$C$为$A^{2^{x}}$

> 下面是我记录的实验数据:

| tmp | 邻接矩阵第一行（也就是点1到各个点距离）$X$为不连通|
|---  | -------------------------------------------|
| 1   | 0 1 2 X X X X X X X |
| 2   | 0 1 2 3 4 X X X X X |
| 3	  | 0 1 2 3 4 5 6 7 8 X |
-----

容易发现，${A^{x}}$是表示$A$经过了$x$条边的最短路。

于是上边的例题就能通过矩阵快速幂轻松解决！



---

## 作者：player (赞：55)

### 一道倍增floyd的题。

首先，我们有两个矩阵，如果其中一个矩阵代表恰好经过x条边的最短路，另外一个矩阵代表恰好经过y条边的最短路。那么将这两个矩阵合并就代表恰好经过x+y条边的最短路。怎么合并呢？结合下面这个式子理解一下：
###  c[i][j]=min(c[i][j],a[i][k]+b[k][j]);
其中i,j,k就是floyd三层循环里的i,j,k ;而a矩阵是经过x条边的最短路，b矩阵是经过y条边的最短路，那么c矩阵就是我们得到的经过x+y条边的最短路了。

那么我们依据初始输入的数组（也就是只经一条边两个点的距离）,这样转移n-1次，就可以得出我们想要的答案了；
### 然而
这样显然会炸啊！那怎么办呢？我们可以借助类似快速幂的操作去实现。

另外我们还可以将编号离散化

具体看代码吧

```
#include <bits/stdc++.h>
using namespace std;
int num[1000005];
int n,s,t,e,tol;
struct map
{
    int a[500][500];
    map operator * (const map &x) const //重载运算符，一会儿要用
    {
        map c;
        memset(c.a,0x3f3f3f3f,sizeof(c.a));//取min，显然置大数
        for(int k=1;k<=tol;k++)
            for(int i=1;i<=tol;i++)
                for(int j=1;j<=tol;j++)
                    c.a[i][j]=min(c.a[i][j],a[i][k]+x.a[k][j]);
        return c;		
    }
}dis,ans;
void init()
{
    memset(dis.a,0x3f3f3f3f,sizeof(dis.a));
    int x,y,z;
    cin>>n>>t>>s>>e;
    for(int i=1;i<=t;i++)
    {
        scanf("%d %d %d",&x,&y,&z);
        if(!num[y])  //这里做一个离散化
            num[y]=++tol;
        if(!num[z])
            num[z]=++tol;
        dis.a[num[y]][num[z]]=dis.a[num[z]][num[y]]=x;
    }
}
void doit() //快速幂
{
    n--;
    ans=dis;
    while(n)
    {
        if(n&1)
            ans=ans*dis;
        dis=dis*dis;
        n>>=1;
    }
}
int main()
{
    init();
    doit();
    cout<<ans.a[num[s]][num[e]];
}
```

---

## 作者：Alan_Zhao (赞：43)

[获得更好的阅读体验](https://www.cnblogs.com/alan-zhao-2007/p/p2886-sol.html)。

本文参考高逸涵的《部分贪心思想在信息学竞赛中的应用》。

## 一种 $\mathcal{O}(T^2)$ 的做法

首先感性理解一下：当 $N$ 很大的时候，最优策略一定是在某个边权很小的边上绕圈。

---

**性质 1**：只有可能在路径上一条最短的边上连续走多次。

**证明**：假如在其他边上连续走了多次，那我们可以将路径上来回走的一对边 $(u\to v,v\to u)$ 删去，换成在最短的边上来回走，这样一定不劣。

---

**性质 2**：只有路径上的一条最短边可能被在同一方向经过三次及以上，这里“经过”不要求连续。

**证明**：假如另外一条边被在同一方向经过三次及以上，那么路径上一定有包含这条边的两个环。若这两个环中有至少一个长度为偶数，那么可以删去这个环并在最短边上来回走；否则，两个环的长度都是奇数，把两个环都删去，换成在最短边上来回走即可。

---

**结论**：最优方案下，只会有至多一条边被经过 $>2$ 次。

设 $f_{u,d}$ 表示从 $S$ 到 $u$，经过的边数为 $d$ 的最短路。由于每条边都被经过 $\le 2$ 次，只需算出 $d\le 2T$ 的 $f$ 即可。于是可以 $\mathcal{O}(T^2)$ 预处理。同理，预处理 $g_{u,d}$ 表示从 $E$ 的。

枚举每条边作为那条被多次经过的边，并 $\mathcal{O}(T)$ 算出最小值即可。具体计算方式可见代码中的 `Calc` 函数。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
typedef long long ll;
const int N=1005,M=105,Inf=0x3f3f3f3f;
int n;
int Get(int u){
	static int num[N]{};
	if(!num[u]) return num[u]=++n;
	return num[u];
}
int t,m,S,T,f[M][M<<1],g[M][M<<1];
struct Edge{int u,v,w;}edge[M];
int Calc(int u,int len){
	int res=Inf;
	For(c,0,1){
		int mn=Inf,k=(t+c)%2-2;
		for(int j=m*2+c;j>=0;j-=2){
			while(k<m*2&&t-j-k>1){
				k+=2,mn+=2*len;
				mn=min(mn,g[u][k]);
			}
			if(mn>=Inf||f[u][j]>=Inf) continue;
			res=min(res,mn+f[u][j]+(t-j-k)*len);
		}
	}
	return res;
}
int main(){
	cin>>t>>m>>S>>T;
	S=Get(S),T=Get(T);
	For(i,1,m){
		cin>>edge[i].w>>edge[i].u>>edge[i].v;
		edge[i].u=Get(edge[i].u),edge[i].v=Get(edge[i].v);
	}
	memset(f,0x3f,sizeof f),memset(g,0x3f,sizeof g);
	f[S][0]=0,g[T][0]=0;
	For(i,1,m*2){
		For(j,1,m){
			f[edge[j].u][i]=min(f[edge[j].u][i],f[edge[j].v][i-1]+edge[j].w);
			f[edge[j].v][i]=min(f[edge[j].v][i],f[edge[j].u][i-1]+edge[j].w);
			g[edge[j].u][i]=min(g[edge[j].u][i],g[edge[j].v][i-1]+edge[j].w);
			g[edge[j].v][i]=min(g[edge[j].v][i],g[edge[j].u][i-1]+edge[j].w);
		}
	}
	int ans=Inf;
	For(i,1,m){
		ans=min({ans,Calc(edge[i].u,edge[i].w),Calc(edge[i].v,edge[i].w)});
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：啊嘞嘞嘞嘞 (赞：18)

先吐槽一下题目的翻译，标题估计是机翻，题干内容过于简洁，不过无所谓了。

大佬们都说得差不多了，这里我想补充一些。

读完题后，看到数据规模点数n<=101（最多100条边的连通图），又是最短路，应该能感觉这是用Floyd

但是！你跟我说要经过k条边(k<=1e6) (╯‵□′)╯︵┻━┻   这就不是普通的最短路了

没学过数学中 图的矩阵表示 可能会想到暴力spfa+dp，不过只能过一半点

### 题外话
图的邻接矩阵本质是矩阵（看名字就知道了，没学过矩阵的左转选修4-2）

它有一种最基本的表示内容：两点之间经过k条边的路径数。原始矩阵就是两点间经过1条边的路径数。

设矩阵$A$表示经过$k1$条边的路径数，$B$表示经过$k2$条边的路径数，则$A*B$表示经过$(k1+k2)$条边的路径数。

直接根据定义 $C_{ij}=\sum_{k=1}^n (A_{ik}*B_{kj})$  

这个应该很好理解，用的就是乘法原理和加法原理。这个运算本身就是标标准准的矩乘，k很大的时候用快速幂即可。

### 回到本题
如果有上述知识储备，应该比较容易想到这题能和矩乘挂钩。

题目求的不是路径数，而是路径长度，那就直接转化呗，把求和改成求最值
$$C_{ij}=\min_{k=1}^n (A_{ik}+B_{kj})$$

如果能理解上面那个公式，应该能觉得这个有道理，也是枚举出了所有中转点。依旧是矩乘，不过乘的运算有所改变。

因为在求C的过程中，C的每项仅作为左值，所以不用担心会得到一个很混乱的矩阵

这个公式和Floyd很像，但不同，Floyd要求k循环必须在最外层，且始终只用一个数组。再说Floyd是个dp，不关心路是怎么走的。所以其实跟Floyd关系并不大，不是说你想到Floyd就能随随便便得出这个公式。

```cpp
//和通常使用的字母统一，这里的变量名不同于题目中的
#include <cstdio>
#include <cstring>
#define MAXN 110
using namespace std;
int n,m,k;
struct matrix {
	int dat[MAXN][MAXN];
	matrix() {
		memset(dat,0x3f,sizeof(dat));
	}
	inline int* operator [](const int i) { //暴力重载运算符
		return dat[i];
	}
} g;
inline int min(int a,int b) {
	return a<b ? a : b;
}
matrix operator *(matrix &a,matrix &b) { //修改的矩乘
	matrix c;
	for (register int i=1;i<=n;i++) {
		for (register int j=1;j<=n;j++) {
			for (register int k=1;k<=n;k++) {
				c[i][j]=min(c[i][j],a[i][k]+b[k][j]);
			}
		}
	}
	return c;
}
matrix mpow(matrix a,int n) { //这应该算压行不错的快速幂了
	matrix ans=a;
	for (n--;n;a=a*a,n>>=1) {
		if (n&1) ans=ans*a;
	}
	return ans;
}
int main() {
	int s,t;
	scanf("%d%d%d%d",&k,&m,&s,&t);
	int id[1010]={}; //离散
	for (int i=0;i<m;i++) {
		int u,v,w;
		scanf("%d%d%d",&w,&u,&v);
		u=id[u] ? id[u] : id[u]=++n;
		v=id[v] ? id[v] : id[v]=++n;
		g[u][v]=g[v][u]=min(g[u][v],w);
	}
	s=id[s];
	t=id[t];
	matrix ans=mpow(g,k);
	printf("%d\n",ans[s][t]);
	return 0;
}
```

---

## 作者：三酒酒酒 (赞：15)

## 胡扯

可能大佬们都会这题，但是如果有大佬不知道（tan90°）这种很有趣又感觉很实用的知识点的话说不定能帮点忙。

## 理解

\* 看到这个边的数量，一下子→Floyd。

\* 那么对于Floyd，每次加入一个点扩展是不是就多了一条边呢？所以会想到扩展k次点来得到最短路。但是k很大，那么考虑一下，**对于一个图的邻接矩阵G而言(初始连通1，不连通0)一开始的读入后得到的G就是表示两点是否直接可达。**

\* 每一次选择中间扩展点k的时候，[i,k]+[k,j]是不是很眼熟？floyed的过程实际上是类似于**矩阵乘法**的,只不过要求松弛而已。使用矩乘，就可以模拟扩展点的时候计算此时经过了n条边的最短路径长度。

\* 一次floyed后所求的矩阵就是在i,j中插入一个点的k。那么不断插入，就能一直推下去推到经过k条边的最短路。要注意**每次都使用新的数组，用以前的数组进行更新**，才能保证，每次只用到了一个点来更新。

\* 然后加上离散化！加上快速幂！快乐AC（其实咸鱼想了半天才想明白

> 对于这题思想拓展推荐大家可以去看一下国家队论文《矩阵乘法在信息学中的应用》，十分实用。   
对于矩阵和递推的关系可以去看一些相关博客

对于**基本**的矩乘操作推荐博客http://blog.csdn.net/wust\_zzwh/article/details/52058209，更深层次的就搜一搜自己get吧\_(:з」∠)\_

   
下面代码，没啥好注释的，拼音取名解决一切疑问（。）

```cpp
#include <cstdio>
#include <cstring>
#define re register int
#define fp(i,a,b) for(re i=a,I=b;i<=I;++i)
#define min(a,b) a<b?a:b
typedef struct juzhen
{
    long long v[210][210];
}M;
M Gra,ans;
int K,T,S,E;
long long n;
long long p[2010];
M floyd(M a,M b)
{
    M c;
    memset(c.v,0x3f,sizeof(c.v));
    int i,j,k;
    fp(k,1,n)fp(i,1,n)fp(j,1,n) c.v[i][j]=min(c.v[i][j],a.v[i][k]+b.v[k][j]);
    return c;
}
void chen(int x)
{
    while(x)
    {
        if(x&1) ans=floyd(ans,Gra);
        Gra=floyd(Gra,Gra);
        x>>=1;
    }
}
int main()
{
    scanf("%d%d%d%d",&K,&T,&S,&E);
    memset(Gra.v,0x3f,sizeof(Gra.v));
    memset(ans.v,0x3f,sizeof(ans.v));
    fp(i,1,T){
        re x,y,z;
        scanf("%d%d%d",&z,&x,&y);
        if(!p[x]) p[x]=++n;if(!p[y]) p[y]=++n;
        Gra.v[p[x]][p[y]]=Gra.v[p[y]][p[x]]=min(z,Gra.v[p[y]][p[x]]);
    }
    for(int i=1;i<=n;i++) ans.v[i][i]=0;
    chen(K);
    printf("%lld",ans.v[p[S]][p[E]]);
    return 0;
}

```

---

## 作者：chenhanzheapple (赞：6)

# [传送门](https://www.luogu.com.cn/problem/P2886)

## 基本思路

暴力 BFS。

具体见代码（本题解侧重于证明）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,s,e;
int dis[105],dis2[105],b[1005],dot[205];
bool vis[105];
struct node{
    int x,w;
};
struct edge{
    int x,y,w;
}a[105];
vector<node> v[105];
void bfs(){
    queue<int> que,que2;
    memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;
    que.push(s);
    for(int i=1;i<=m;i++){//搜索m轮
        memset(dis2,0x3f,sizeof(dis));
        memset(vis,0,sizeof(vis));
        while(!que.empty()){//把点从队列里取出来
            int t = que.front();
            que.pop();
            for(auto x:v[t]){//找这个点的邻居
                dis2[x.x] = min(dis2[x.x],dis[t]+x.w);//更新距离
                if(!vis[x.x]){
                    vis[x.x] = 1;
                    que2.push(x.x);
                }
            }
        }
        for(int i=1;i<=n;i++){
            dis[i] = dis2[i];
        }
        while(!que2.empty()){
            que.push(que2.front());
            que2.pop();
        }
    }
    cout << dis[e];
}
int main(){
    cin >> m >> t >> s >> e;
    for(int i=1;i<=t;i++){
        cin >> a[i].w >> a[i].x >> a[i].y;
        dot[i] = a[i].x;
        dot[i+t] = a[i].y;
    }
    sort(dot+1,dot+t*2+1);//离散化
    n = unique(dot+1,dot+t*2+1)-dot-1;
    for(int i=1;i<=n;i++){
        b[dot[i]] = i;
    }
    s = b[s];
    e = b[e];
    for(int i=1;i<=t;i++){
        a[i].x = b[a[i].x];
        a[i].y = b[a[i].y];
        v[a[i].x].push_back((node){a[i].y,a[i].w});
        v[a[i].y].push_back((node){a[i].x,a[i].w});
    }
    //bfs
    bfs();
    return 0;
}
```
时间复杂度 $O(N \times T)$。

## 证明

我们要进行 $N$ 轮搜索（在我的代码里是 $m$）。对于第 $i$ 轮搜索找到的点是所有从出发点走 $i$ 条边能到达的点。图中最多有 $T+1$ 个点（大抵是显然的吧）。

每轮搜索我们需要把点从队列中取出来并遍历与这个点相连的所有边，而每条边连接着两个点，所以**每条边只能被左右两个点所遍历到**，因此每轮搜索至多要遍历 $T \times 2$ 次。我们会进行 $N$ 轮搜索，因此最坏时间复杂度（实际上达不到）是 $O(N \times T \times 2)$，即 $O(N \times T)$。

## 参考资料

[FS_NEO大佬的帖子](https://www.luogu.com.cn/discuss/962083)

---

## 作者：ycyaw (赞：6)

首先发现是一张连通图，而且只有$100$条边，那么点也很少

编号是乱的，先进行一波离散化，上$map$即可(~~STL大法好~~)

离散化后，转化成邻接矩阵，这个矩阵实际上表示的是$i$到$j$只经过$1$条边的最短路矩阵。这时发现，我们要求的答案是一个$st$到$ed$且只经过$n$条边的最短路矩阵。

考虑如何从小矩阵推向大矩阵：设矩阵$A$是一个任意两点经过$x$条边的最短路矩阵，设矩阵$B$是一个任意两点经过$y$条边的最短路矩阵

$A$ $\times$ $B$得到矩阵$C$，那么矩阵$C$是一个经过$(x+y)$条边的矩阵

重载乘法，因为矩阵转移时的实质为$Floyd$松弛：$C$($i,j$) $=$ $min$ ($A$($i,k$) $+$ $B$($k,j$) ) ($1$ $<=$ $k$ $<=$ $n$)

答案就是初始矩阵的$k$次方，矩阵快速幂加速即可 
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define oo (1e18)
#define int long long
#define LL unsigned long long
#define hh puts("")
using namespace std;
int k,m,st,ed,cnt=0;
map<int,int> mp;
struct matrix{
	int ma[105][105];
	void init(){memset(ma,0x3f,sizeof(ma));}
}f,ans;
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-1;ch=getchar();}
    while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+(ch^48);ch=getchar();}
    return ret*ff;
}
matrix mul(matrix a,matrix b){
	matrix res;
	res.init();
	for(int kk=1;kk<=cnt;kk++)
		for(int i=1;i<=cnt;i++)
			for(int j=1;j<=cnt;j++)
				res.ma[i][j]=min(res.ma[i][j],a.ma[i][kk]+b.ma[kk][j]);
	return res;
}
void ksm(int p){
	while(p){
		if(p&1) ans=mul(ans,f);
		p>>=1;
		f=mul(f,f);
	}
}
signed main(){
	k=read(),m=read(),st=read(),ed=read();
	f.init(),ans.init();
	for(int i=1;i<=m;i++){
		int v=read();
		int x=read(),y=read();
		if(!mp[x]) mp[x]=++cnt;
		if(!mp[y]) mp[y]=++cnt;
		f.ma[mp[x]][mp[y]]=f.ma[mp[y]][mp[x]]=min(f.ma[mp[x]][mp[y]],v);
	}
	for(int i=1;i<=cnt;i++) ans.ma[i][i]=0;
	ksm(k);
	printf("%lld",ans.ma[mp[st]][mp[ed]]);
    return 0;
}
```


---

## 作者：fanfansann (赞：5)

首先由于只有100条边也就是只用到了200个点，而一共有1000个点，所以我们要先离散化一下， 用map离散化到200个点。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200717161630878.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_16,color_FFFFFF,t_70)

上图中的第一行是经典的Floyd算法的思想。

下面一行是本题的变形思想。
其中 $d[a,i,k]$ 中的 $k$ 不是什么第 $k$ 条边，而是表示从 $i$ 走了 $a$ 条边（就是相当于走了$a$步）以后到达的结点 $k$ ，因此这个 $k$ 是在 $1$ ~ $N$ 之间的一个点。

这个转移方程表示从 $i$ 到 $j$ 走 $a+b$ （$x$）条边，等于在所有从 $i$ 走 $a$ 条边到 $k$ ，再从 $k$ 走 $b$ （$x-a$） 条边到 $j$ 中取最小值。

这样我们要求的是经过 $N$ 条边的最短路，最开始输入的每一个都是1条边（经过一条边的两个点的距离），那么我们要得到经过N条边就可以按照上述的方程，加 $N-1$ 次 $（d[2,i,j] = d[1,i,k] + d[1,k,j]）$

由于**每一部分之间没有任何关联，** 所以整个答案的求解可以看成是加法运算，满足**结合律**。因此可以用快速幂来处理。(快速幂就是利用倍增的思想，乘 $log_k$ 次得到了$x^k$，这里要加 $N$ 次，但是 $N$ 比较大，我们用模拟快速幂来进行优化，并用加法代替乘法，这样只需要 $log_N$ 次就可以得到加 $N$ 次的经过 $N$ 条边的最短路)

最终的时间复杂度为$O(T^3log_N)$
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<map>

#define x first
#define y second
using namespace std;
typedef pair<int,int> PII;

const int N =  507;

int k,n,m,S,E;
int g[N][N];
int d[N][N];

void mul(int c[][N],int a[][N],int b[][N]){
    static int temp[N][N];
    memset(temp,0x3f,sizeof temp);
    for(int k = 1;k <= n;++k)
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                temp[i][j] = min(temp[i][j],a[i][k] + b[k][j]);
    memcpy(c,temp,sizeof temp);
}

void qpow(){
    memset(d,0x3f,sizeof d);
    for(int i = 1;i <= n;++i)
        d[i][i] = 0;
    while(k){
        if(k & 1)mul(d, d, g);//d = d * g;
        mul(g, g, g);//g = g * g;
        k >>= 1;
    }
}

int main(){
    cin>>k>>m>>S>>E;
    memset(g,0x3f,sizeof g);
    //这里g[i][i]不能置为0，因为这里g[i][j]表示的是从i走1条边到达j,i不能经过1条边到i,因此应该也是INF
    map<int,int>ids;
    while(m--){
        int a,b,c;
        scanf("%d%d%d",&c,&a,&b);
        if(!ids.count(a))ids[a] = ++n;
        if(!ids.count(b))ids[b] = ++n;
        a = ids[a],b = ids[b];

        g[a][b] = g[b][a] = min(g[a][b],c);
    }
    if(!ids[S])ids[S] = ++n;
    if(!ids[E])ids[E] = ++n;
    S = ids[S],E = ids[E];

    qpow();

    cout<<d[S][E]<<endl;
    return 0;

}

```


---

## 作者：Azuree (赞：5)

[查看原题请戳这里](https://www.luogu.org/problem/P2886)

首先，我们要明确这里的最短路是在经过n条路径的前提下的最短路，因为这是无向图，所以一定有解。

我们先来看朴素的Floyd的代码：

```cpp
for(int k = 1; k <= n; k++)
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			f[i][j] = min(f[i][j],f[i][k] + f[k][j]);
```

其中，我们每次都是枚举k并用ta去当中转点去更新每一个i->j的最短路。

那么，当k等于n/2时这段代码完成了什么呢？

那就是我们尝试了用[1,n/2]的点去更新最短路，我们可以发现，这样得到的最短路最多包含k+1条路径。

为什么是最多k+1条呢？

因为我们每次用k去尝试更新i->j的最短路是不一定成功（即f[i][j]<=f[i][k]+f[k][j]）

~~所以我们可以用Floyd+dp+倍增去切掉这道题~~

我们再来看一下矩阵乘法的代码：

```cpp
for(int k = 1; k <= n; k++)
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			c[i][j] = c[i][j] + a[i][k] * b[k][j];
```

是不是和Floyd的代码有点相似？

因为我们要求的是最短路，所以我们要对这个矩阵乘法魔改一下：

```cpp
memset(c,0x7f,sizeof(c));
for(int k = 1; k <= n; k++)
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			c[i][j] = min(c[i][j],a[i][k] + a[k][j]);
```

是不是和Floyd越来越相似了……

但是在这里，c[i][j]的初值为INF，所以我们每次枚举k都会选择一条边去更新最短路，所以如果我们用邻接矩阵map（不是STL的那个map）去存边，那么map的n次方存的就是经过n条边的最短路。

code:

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
#define INF 0x7fffffff
#define re register
#define rep(i,a,b) for(int i = (a); i <= (b); i++)
#define qwq printf("qwq\n");

using namespace std;

long long read()
{
	register long long x = 0,f = 1;register char ch;
	ch = getchar();
	while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
	while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}


long long n,m,t,sta,End,cnt,siz,u,d[100005];

struct edge{
	int fro,to,l;
}e[100005];

struct juzhen{
	long long a[105][105];
	juzhen operator * (const juzhen &x) const
    {
        juzhen c;
        memset(c.a,0x7f,sizeof(c.a));
        for(int k = 1; k <= siz; k++)
            for(int i = 1; i <= siz; i++)
                for(int j = 1; j <= siz; j++)
                    c.a[i][j] = min(c.a[i][j],a[i][k]+x.a[k][j]);
        return c;       
    }
}ans,map; 

void ksm(int b)
{
	while(b > 0)
	{
		if(b & 1) ans = ans * map;
		map = map * map;
		b >>= 1;
	}
}

bool cmp(int a,int b){return a < b;}

int main()
{
	n = read(); m = read(); sta = read(); End = read();
    for(int i = 1; i <= m; i++)
    {
    	e[i].l = read(); e[i].fro = read(); e[i].to = read();
    	d[++cnt] = e[i].fro; d[++cnt] = e[i].to;
	}
	sort(d + 1, d + cnt + 1, cmp);
	siz = unique(d + 1, d + cnt + 1) - d - 1;
	for(int i = 1; i <= siz; i++)
		for(int j = 1; j <= siz; j++)
			map.a[i][j] = INF;
  	for(int i = 1; i <= m; i++)
	{
		e[i].fro = lower_bound(d + 1, d + siz + 1, e[i].fro) - d;
		e[i].to = lower_bound(d + 1, d + siz + 1, e[i].to) - d;
		map.a[e[i].fro][e[i].to] = e[i].l;
		map.a[e[i].to][e[i].fro] = e[i].l;
	}
	sta = lower_bound(d + 1, d + siz + 1, sta) - d;
	End = lower_bound(d + 1, d + siz + 1, End) - d;// li san hua 
	for(int i = 1; i <= siz; i++)
		for(int j = 1; j <= siz; j++)
			ans.a[i][j] = map.a[i][j];
	ksm(n - 1);
	printf("%d\n",ans.a[sta][End]);
    return 0;
}

```

---

## 作者：lijinrui (赞：4)

# 方法1
用 $n$ 个矩阵来表示，第 $k$ 个矩阵的第 $i$ 行第 $j$ 列表示从节点 $i$ 到节点 $j$，恰好经过 $k$ 条边的最短路。第 $k$ 个矩阵与第 $p$ 个矩阵的“积”，就是第 $k+p$ 个矩阵。

类似于矩阵乘法，但**两个数之积的和**应变为**两个数的和的最小值**这里既可以重载运算符，也可以写一个单独的函数。  
这样，就可以用矩阵快速幂来实现了。

当然，由于边数很少，但点编号较大，可以离散化一下。于是就完美的 AC 了。
## Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define INF 0x3f3f3f3f
struct node
{
    int sq[105][105];
};
int n,t,s,e;//给定一张 T 条边的无向连通图，求从 S 到 E 经过 N 条边的最短路长度。
int map[105][105];
bool app[1001];
int as[1001];
int cnt=0;
int l[101],u[101],v[101];
node mult(node a,node b)
{
    node ret;
    memset(ret.sq,0x3f,sizeof(ret.sq));
    for(int i=1;i<=cnt;i++)
    for(int j=1;j<=cnt;j++)
    for(int x=1;x<=cnt;x++)
    {
        ret.sq[i][j]=min(ret.sq[i][j],a.sq[i][x]+b.sq[x][j]);
    }
    return ret;
}//"矩阵乘法"
node quick(node x,int y)
{
    if(y==1)return x;
    node ret;
    memset(ret.sq,0,sizeof(ret.sq));
    if(y==0)
    {
        return ret;
    }
    ret=quick(x,y>>1);
    return y%2==1?mult(x,mult(ret,ret)):mult(ret,ret);
}//矩阵快速幂
int main()
{
    cin>>n>>t>>s>>e;
    memset(map,0x3f,sizeof(map));
    for(int i=1;i<=t;i++)
    {
        cin>>l[i]>>u[i]>>v[i];
        app[u[i]]=1;
        app[v[i]]=1;
    }
    for(int i=1;i<=1001;i++)
    {
        if(app[i])as[i]=++cnt;
    }
    for(int i=1;i<=t;i++)
    {
        map[as[u[i]]][as[v[i]]]=l[i];
        map[as[v[i]]][as[u[i]]]=l[i];
    }
    node x;
    for(int i=1;i<=cnt;i++)
    {
        for(int j=1;j<=cnt;j++)
        {
            x.sq[i][j]=map[i][j];
        }
    }
    x=quick(x,n);
    cout<<x.sq[as[s]][as[e]]<<endl;
    return 0;
}
```
# 方法2
倍增+Floyd.不多说，上代码（~~其实是懒~~）

(~~仔细想想~~会发现，两种方法其实并没有本质区别)
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define INF 0x3f3f3f3f
using namespace std;
int n,t,s,e;//给定一张 T 条边的无向连通图，求从 S 到 E 经过 N 条边的最短路长度。
int map[105][105];
bool app[1001];
int as[1001];
int cnt=0;
int l[101],u[101],v[101];
int f[20][101][101],g[101][101],ans[101],nean[101];
int main()
{
    cin>>n>>t>>s>>e;
    memset(map,0x3f,sizeof(map));
    for(int i=1;i<=t;i++)
    {
        cin>>l[i]>>u[i]>>v[i];
        app[u[i]]=1;
        app[v[i]]=1;
    }
    for(int i=1;i<=1001;i++)
    {
        if(app[i])as[i]=++cnt;
    }
    for(int i=1;i<=t;i++)
    {
        map[as[u[i]]][as[v[i]]]=l[i];
        map[as[v[i]]][as[u[i]]]=l[i];
    }
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=cnt;i++)
        for(int j=1;j<=cnt;j++)
            f[0][i][j]=map[i][j];
    for(int _=1;1<<_<=n;_++)
        for(int i=1;i<=cnt;i++)
            for(int j=1;j<=cnt;j++)
                for(int k=1;k<=cnt;k++)
                    f[_][i][j]=min(f[_][i][j],f[_-1][i][k]+f[_-1][k][j]);
    memset(ans,0x3f,sizeof(ans));
    ans[as[s]]=0;
    for(int i=0;n;i++,n>>=1)
    {
        if(!(n&1))continue;
        for(int j=1;j<=cnt;j++)
        {
            nean[j]=INF;
            for(int k=1;k<=cnt;k++)
            {
                nean[j]=min(ans[k]+f[i][j][k],nean[j]);
            }
        }
        for(int j=1;j<=cnt;j++)
        {
            ans[j]=nean[j];
        }
    }
    cout<<ans[as[e]]<<endl;
    return 0;
}
```

---

## 作者：天羽 (赞：4)

貌似我用了個不太正確的方法來過這題？

我第一眼看到的其實不是倍增 floyd (因為我對矩陣還不太熟悉)，而是一種類似 dijk 的做法。

#### 題目分析

我們設 $f_{i,j}$ 為長度為 $i$ 且終點為 $j$ 的最路路徑。

那麽容易得出 $f_{i,v} = min (f_{i-1,u} + map_{u,v})$。

答案自然就是$f_{n,E}$。

當然空間一定會爆所以我們要用滾動數組。而時間複雜度方面，因為只有當兩個點有直接路徑時才會對 $dp$ 數組進行更新，路徑一共有 $t$ 條，一共要走 $n$ 段，所以時間複雜度是 $O(nt)$ ，大約會是 $10^8$ (剛剛好不爆)。

其實我也懷疑這個做法會不會有一些我沒想到的地方會導致WA， 因為我一開題解全部都是矩陣搭配floyd，但幸好還是過了OuO。可能會有一些數據會卡掉我的代碼，歡迎提出。

代碼:
```cpp
#include <iostream>
using namespace std;
long long int cnt,st,en,n,t,map[10005][3],dp[100005][2],tag[1005],num[10005];
int main()
{
	cin>>n>>t>>st>>en;
	for(int i=1;i<=t;i++)
	{
		cin>>map[i][0]>>map[i][1]>>map[i][2];
		if(tag[map[i][1]]==0)
		{
			tag[map[i][1]]=1;
			cnt++;
			num[cnt]=map[i][1];
		}
		if(tag[map[i][2]]==0)
		{
			tag[map[i][2]]=1;
			cnt++;
			num[cnt]=map[i][2];
		}
	}
	for(int i=1;i<=1000;i++)
	{
		dp[i][1]=9999999999999999;
	}
	dp[st][1]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=cnt;j++)
		{
			dp[num[j]][0]=dp[num[j]][1];
			dp[num[j]][1]=9999999999999999;
		}
		for(int j=1;j<=t;j++)
		{	
			dp[map[j][2]][1]=min(dp[map[j][2]][1],dp[map[j][1]][0]+map[j][0]);
			dp[map[j][1]][1]=min(dp[map[j][1]][1],dp[map[j][2]][0]+map[j][0]);
		}
	}
	cout<<dp[en][1];
}
```


---

## 作者：eternal (赞：3)

floyd可以用矩阵快速幂优化，因为满足结合率，然后就可以瞎搞了

/\*
ID:Agreement

LANG:C++

\*/
```cpp
// Invincible
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cstdlib> 
#define rep( i , l , r ) for( int i = (l) ; i <= (r) ; ++i )
#define per( i , r , l ) for( int i = (r) ; i >= (l) ; --i )
#define erep( i , u ) for( int i = head[(u)] ; ~i ; i = e[i].nxt )
using namespace std;
const int maxn = 1000 + 5 , INF = 0x3f3f3f3f;
int K , M , S , T;
int ans[maxn][maxn] , mp[maxn][maxn] , tmp[maxn][maxn] , dis[maxn][maxn];
int vis[maxn] , v[maxn] , num;
void floyd( int c[][maxn] , int a[][maxn] , int b[][maxn] ){
    rep( k , 0 , num - 1 ) rep( i , 0 , num - 1 ) rep( j , 0 , num - 1 )
        if( c[v[i]][v[j]] > a[v[i]][v[k]] + b[v[k]][v[j]] )
            c[v[i]][v[j]] = a[v[i]][v[k]] + b[v[k]][v[j]];
}
void copy( int a[][maxn] , int b[][maxn] ){
    rep( i , 0 , num - 1 )
        rep( j , 0 , num - 1 )
         a[v[i]][v[j]] = b[v[i]][v[j]] , b[v[i]][v[j]] = INF;
}
void solve( int k ){
    for( ; k ; k >>= 1 ){
        if( k & 1 ){
            floyd( dis , ans , mp );
            copy( ans , dis );
        }
        floyd( tmp , mp , mp );
        copy( mp , tmp );
    }
}
int main(){
    int x , y , w;
    scanf("%d %d %d %d" , &K , &M , &S , &T);
    memset( mp , 0x3f , sizeof mp );
    memset( tmp , 0x3f , sizeof tmp );
    memset( dis , 0x3f , sizeof dis );
    memset( ans , 0x3f , sizeof ans );
    rep( i , 0 , maxn - 5 ) ans[i][i] = 0;
    num = 0;
    rep( i , 0 , M - 1 ){
        scanf("%d %d %d" , &w , &x , &y );
        if( !vis[x] ) vis[x] = 1 , v[num++] = x;
        if( !vis[y] ) vis[y] = 1 , v[num++] = y;
        if( mp[x][y] > w ) mp[x][y] = mp[y][x] = w;
    }
    solve( K );
    printf("%d\n" , ans[S][T]);
    return 0;
}
```

---

## 作者：_sry (赞：2)


我们可以很容易推导$dp$方程,$dp(k,i,j)$表示经过$k$条边从$i$到$j$的最小花费。则，$dp(k,i,j)=min(dp(k-1,i,p)+dp(1,p,j))$。

而$(i,p),(p,j),(i,j)$发现了什么，这不是矩阵吗，$dp(1,i,j)$为初始矩阵($1$次幂),$dp(2,i,j)$为$2$次幂，$dp(3,i,j)$为$3$次幂，所以只需要矩阵快速幂一下即可。
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
inline int read(){
    int f=1,ans=0;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
    return f*ans;
}
const int MAXN=101;
struct matrix{
    int st[MAXN][MAXN];
}a,F,ans;
struct node{
    int u,v,w;
}x[MAXN];
int Map[1000001],n,k,m,S,T,cnt;
matrix mul(matrix s1,matrix s2){
    matrix s3;
    memset(s3.st,127/3,sizeof(s3.st));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int p=1;p<=n;p++){
                s3.st[i][p]=min(s3.st[i][p],s1.st[i][j]+s2.st[j][p]);
            }
    return s3;
}
matrix qpow(int b){
    if(b==0) return a;
    ans=a;
    while(b){
        if(b&1) ans=mul(ans,a);
        a=mul(a,a);b>>=1;
    }return ans;
}
signed main(){
    k=read(),m=read(),S=read(),T=read();
    memset(a.st,127/3,sizeof(a.st));
    for(int i=1;i<=m;i++){
        int w=read(),u=read(),v=read();
        if(Map[u]==0) Map[u]=++cnt;
        if(Map[v]==0) Map[v]=++cnt;
        u=Map[u],v=Map[v];
        x[i].w=w,x[i].u=u,x[i].v=v;
        a.st[u][v]=a.st[v][u]=min(a.st[u][v],w);
    }
    n=cnt;
    F=qpow(k-1);
    printf("%lld",F.st[Map[S]][Map[T]]);
}
/*
3 1 3
1 2
2 3
1 3
*/
```

---

## 作者：echo6342 (赞：2)

这并不是对劲的题解…胡扯一句，不知道有没有人喜欢玩找不同

题意就是给一张无向有边权的图、起点、终点，求起点到终点经过n条边的最短路。n<=10^6，点的编号<=10^3，边数<=10^2。


这个边数让人不由自主地想到了floyd，然后发现floyd每次相当于加入了一个点（注意，这里的“一次”也是O(点数^3)的，但是在这一次floyd的过程中不会更新结果。）也就是说，第一次floyd求出来了两点之间只走一条边的最短路，第二次求出来了两点之间只走两条边的最短路……，第n次求出来了只走n条边的最短路。这时候就会发现，n遍不在过程中更新答案的floyd后，答案就出来了。


好不容易推到了这一步，发现了n<=10^6的数据范围，想必心中是有些崩溃的。但是邻接矩阵是什么？是矩阵！这样就可以思考用矩阵快速幂的方法。发现floyd的转移时c[i][j] = min { dis[i][k] + dis[k][j] | i,k,j为图中点的编号}，和矩阵快速幂的转移有点像，而且转移时也是上一步求出的答案对于最初的邻接矩阵作运算。这时就可以考虑用一些不对劲的方法改造矩阵乘法。


将矩阵快速幂中的乘法改成上面那样的转移方法，就会发现只要求出邻接矩阵^n就好了。


这样就完了？当然不是。


题目中，点的编号<=10^3，直接floyd肯定会时间超限。注意到边数<=10^2，而每条边顶多连两个与之前不同的点，那么出现的不同的点顶多有200个。将点进行离散化就解决了。


还有一些细节，编的时候都能想得到，在这就不多说了。


```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<cstdlib>
using namespace std;
typedef struct node
{
    int mat[210][210];
}Matrix;
Matrix rd,dis;
int n,t,s,e,siz,mc[1010];
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(isdigit(ch)==0 && ch!='-')ch=getchar();
    if(ch=='-')f=-1;
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}
Matrix mul(Matrix a,Matrix b)
{
    Matrix c;memset(c.mat,0x3f,sizeof(c.mat));
    for(int k=1;k<=siz;k++)
    {
        for(int i=1;i<=siz;i++)
        {
            for(int j=1;j<=siz;j++)
            {
                c.mat[i][j]=min(c.mat[i][j],a.mat[i][k]+b.mat[k][j]);
            }
        }
    }
    return c;
}
void pow(int tim)
{
    while(tim)
    {
        if(tim&1)
            rd=mul(rd,dis);
        dis=mul(dis,dis);
        tim>>1;
    }
}
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read(),t=read(),s=read(),e=read();
    memset(rd.mat,0x3f,sizeof(rd.mat));
    memset(dis.mat,0x3f,sizeof(dis.mat));
    memset(mc,-1,sizeof(mc));
    for(int i=1;i<=t;i++)
    {
        int w=read(),u=read(),v=read();
        if(mc[u]==-1)mc[u]=++siz;
        if(mc[v]==-1)mc[v]=++siz;
        u=mc[u],v=mc[v];
        dis.mat[v][u]=min(dis.mat[u][v],w);
        dis.mat[u][v]=min(dis.mat[u][v],w);
    }
    for(int i=1;i<=siz;i++)
    {
        rd.mat[i][i]=0;
    }
    pow(n);
    cout<<rd.mat[mc[s]][mc[e]];
    return 0;
}

```

---

## 作者：star_eternal (赞：2)

# 这$TM$是$floyd$ ！！！
误人子弟。
这是新的矩阵乘法运算而已。
我们来对比一下。
## $$f[i][j] = min(f[i][j],f[i][k] + f[k][j])$$
$This\ Floyd$

# $but$

这道题的情况是。

假设$A_{(n * n)},B_{(n * n)},C_{(n * n)}$s是三个矩阵

定义新运算。 $A*B$ 为

# $$C[i,j] = \min_{k = 1}^{b}{A[i,k] + B[k,j]}$$

然后矩阵快速幂。

# 我真的是佛了

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int Maxn = 100 + 10;
int L , m , S , T , mp[Maxn * 10] , n;
void id(int x){ if(!mp[x]) mp[x] = ++n;}
struct Matrix{
	int mat[Maxn][Maxn];
	Matrix(){memset(mat,0x3f,sizeof(mat));}
	inline Matrix operator *(const Matrix & a)const{
		Matrix b;
		for(int k = 1;k <= n;k++)
			for(int i = 1;i <= n;i++)
				for(int j = 1;j <= n;j++){
				b.mat[i][j] = min(b.mat[i][j] ,mat[i][k] + a.mat[k][j]);
			}
		return b;
	}

};
Matrix st;
Matrix q_pow(Matrix a , int p){
	if(p == 1)return a;
	Matrix t = a;p--;
	while(p){
		if(p & 1)t = t * a;
		a = a * a;
		p >>= 1;
	}
	return t;
}
int main()
{ 
	scanf("%d%d%d%d",&L,&m,&S,&T);
	for(int i = 1;i <= m;i++){
		int w  ,u , v;
		scanf("%d%d%d",&w,&u,&v);
		id(u)  , id(v);
		st.mat[mp[u]][mp[v]] = w;
		st.mat[mp[v]][mp[u]] = w;
	}
	st = q_pow(st,L);
	printf("%d\n",st.mat[mp[S]][mp[T]]);
	return 0;
}
```

---

## 作者：YuanZihan1225 (赞：1)

## 题意分析：
- 题目翻译已经很清楚了，（还没看的走这里 -> [P2886](https://www.luogu.com.cn/problem/P2886))。这是一道矩阵最短路的模板题（不会矩阵乘法的来这里 -> [传送门](https://www.yiibai.com/cplusplus/matrix-multiplication-in-cpp.html#:~:text=C%2B%2B%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95.%20%E6%88%91%E4%BB%AC%E5%8F%AF%E4%BB%A5%E5%9C%A8%202%20%E4%B8%AA%E7%9F%A9%E9%98%B5%E4%B8%8A%E6%89%A7%E8%A1%8C%E5%8A%A0%EF%BC%8C%E5%87%8F%EF%BC%8C%E4%B9%98%E5%92%8C%E9%99%A4%E8%BF%90%E7%AE%97%E3%80%82.%20%E4%BB%8E%E7%94%A8%E6%88%B7%E8%BE%93%E5%85%A5%E4%B8%80%E8%A1%8C%E6%95%B0%E5%AD%97%E5%92%8C%E5%88%97%E5%8F%B7%EF%BC%8C%E7%BB%84%E6%88%90%E7%AC%AC%E4%B8%80%E4%B8%AA%E7%9F%A9%E9%98%B5%E5%85%83%E7%B4%A0%E5%92%8C%E7%AC%AC%E4%BA%8C%E4%B8%AA%E7%9F%A9%E9%98%B5%E5%85%83%E7%B4%A0%E3%80%82.%20%E7%84%B6%E5%90%8E%EF%BC%8C%E5%AF%B9%E7%94%A8%E6%88%B7%E8%BE%93%E5%85%A5%E7%9A%84%E7%9F%A9%E9%98%B5%E6%89%A7%E8%A1%8C%E4%B9%98%E6%B3%95%E3%80%82.%20%E5%9C%A8%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95%E7%AC%AC%E4%B8%80%E7%9F%A9%E9%98%B5%E4%B8%AD%EF%BC%8C%E4%B8%80%E4%B8%AA%E8%A1%8C%E5%85%83%E7%B4%A0%E4%B9%98%E4%BB%A5%E7%AC%AC%E4%BA%8C%E7%9F%A9%E9%98%B5%E6%89%80%E6%9C%89%E5%88%97%E5%85%83%E7%B4%A0%E3%80%82.%20%E8%AE%A9%E6%88%91%E4%BB%AC%E9%80%9A%E8%BF%87%E4%B8%8B%E9%9D%A2%E7%9A%84%E5%9B%BE%E6%9D%A5%E7%90%86%E8%A7%A3,%2A%203%20%E5%92%8C%203%20%2A%203%20%E7%9F%A9%E9%98%B5%E7%9A%84%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95%EF%BC%9A.%20%E4%B8%8B%E9%9D%A2%E6%9D%A5%E7%9C%8B%E7%9C%8B%E7%9C%8BC%2B%2B%E4%B8%AD%E7%9A%84%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95%E7%A8%8B%E5%BA%8F%E3%80%82.)）。

### 让我们分析一下：
- 我们都知道，在矩阵乘法中$C_{ij}=\sum_{k=1}^nA_{ik} \times A_{kj}$  表示从 $i$ 到 $j$ 经过 $2$ 条边的路径数，这个是根据乘法原理得到，现在题目要求最短路，那么我们可以把原来的矩阵乘法改动一下，变成：  $C_{ij}=\min_{k=1}^n(A_{ik}+A_{kj})$ ，这里矩阵里的 $A_{ij}$ 表示的不再是路径数，而是最短路，假设 $A_{ik}$ 表示 $i$ 到 $k$ 经过 $x$ 条边的最短路， $A_{kj}$ 表示 $k$ 到 $j$ 经过 $y$ 条边的最短路，那么 $C_{ij}$ 就表示 $i$ 到 $j$ 经过 $x+y$ 条边的最短路。
```cpp
matrix operator *(matrix &a, atrix &b) {
	matrix c;
	for (register int i = 1; i <= cnt; i++)
		for (register int j = 1; j <= cnt; j++)
			for (register int k = 1; k <= cnt; k++)
				c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
	return c;
}
```
   - 但如果你再认真看看题，你会发现：明显会炸啊!于是我们要优化，把数据离散化。
```cpp
memset(mat.a, 0x3f3f3f3f, sizeof(co.a));
cin >> n >> t >> s >> e;
for(int i = 1; i <= t; i++)
{
		scanf("%d%d%d",&x,&y,&z);
		if(!num[y]) num[y] = ++cnt;//cnt是编号，用于标记离散化中数据的编号
		if(!num[z]) num[z] = ++cnt;//cnt一定要先加，不然会wa一个点
		mat.a[num[y]][num[z]] = mat.a[num[z]][num[y]] = x;//对矩阵的预先处理
}
```
完整无注释健康食用版代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int num[1000005], n, s, t, e, cnt;
struct matrix
{
		int a[500][500];
		matrix operator * (const matrix &x) const
		{
			matrix c;
			memset(c.a, 0x3f3f3f3f, sizeof(c.a));
			for(int k = 1; k <= cnt; k++)
 				for(int i = 1; i <= cnt; i++)
					for(int j = 1; j <= cnt; j++)
						c.a[i][j] = min(c.a[i][j], a[i][k] + x.a[k][j]);
			return c;		
		}
}mat, ans;
void power()
{
		n--, ans = mat;
		while(n)
		{
			if(n & 1) ans = ans * mat;
			mat = mat * mat, n >>= 1;
		}
}
int main()
{
		memset(mat.a, 0x3f3f3f3f, sizeof(mat.a));
		int x, y, z;
		cin >> n >> t >> s >> e;
		for(int i = 1; i <= t; i++)
		{
			scanf("%d %d %d",&x,&y,&z);
			if(!num[y]) num[y] = ++cnt;
			if(!num[z]) num[z] = ++cnt;
			mat.a[num[y]][num[z]] = mat.a[num[z]][num[y]] = x;
		}
		power();
		cout << ans.a[num[s]][num[e]];
		return 0;
}
```

---

## 作者：Gloaming (赞：1)

## 题目大意

给你一张无向联通图，求出从 $S$ 到 $E$ 经过**恰好** $N$ 条边的最短路。

## 分析

我们可以注意到一个特殊的限制：对于每一条边 $u,v\leq 1000$。这么小的范围，我们可以用邻接矩阵来储存，而又发现 $n$ 的范围在 $1e6$，不难想到 $n\log n$ 级别的算法。

然后我们在细细分析：floyd 算法实质上是一个 dp 转移方程为 $dis_{i,j,x+y}=\min\{dis_{i,j,x+y},dis_{i,k,x}+dis_{j,k,y}\}$ ，这和矩阵乘法的转移很像，能不能用矩阵来加速呢？

那怎么处理**恰好** $N$ 条边这一个条件呢？注意到我在转移方程的时候额外加了一个维度 ${i,j,x}$ 这个意思是**刚好**走了 $x$ 步之后的最短路，这样就可以解决这个问题了。

现在我们就可以将距离矩阵进行我们修改后的快速幂，这样就可以快速求得答案了。

时间复杂度 $O(n^3\log N)$，$n$ 是节点数，$N$ 是步骤数。

代码实现
```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int SIZE = 1000 + 10, MOD = 19260817;
struct Matrix {
	int val[SIZE][SIZE];
	void BuildEpsilon(int n) {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                val[i][j]=INT_MAX;;
	}
}g;
Matrix Mul(Matrix x, Matrix y, int n) { //修改后的矩阵乘法
	Matrix result;result.BuildEpsilon(n);
	for(int k = 1; k <= n; k ++) {
		for(int i = 1; i <= n; i ++) {
			for(int j = 1; j <= n; j ++) {
				result.val[i][j] = min(result.val[i][j], x.val[i][k] + y.val[k][j]);
			}
		}
	}
	return result;
}
Matrix Qpow(Matrix base, int top, int n) {//快速幂
	Matrix result=base;top--;
	while(top) {
		if(top & 1) result = Mul(result, base, n);
		base = Mul(base, base, n);
		top >>= 1;
	}
	return result;
}
signed main() {//注意节点要离散化
	int k,e,s,t;cin>>k>>t>>s>>e;
	int lisan[1010]={},nodetot=0;
	g.BuildEpsilon(1000);
	for(int i=1,u,v,w;i<=t;i++){
		cin>>w>>u>>v;
        if(u==v)continue;
		if(lisan[u]==0) lisan[u]=++nodetot;
		if(lisan[v]==0) lisan[v]=++nodetot;
		g.val[lisan[u]][lisan[v]]=g.val[lisan[v]][lisan[u]]=w;
	}
	Matrix res=Qpow(g,k,nodetot);
	cout<<res.val[lisan[s]][lisan[e]]<<endl;
	return 0;
}
```

---

## 作者：horz (赞：1)

### 题意
给出一张无向连通图，求$s$到$t$经过$n$条边的最短路。

### 分析

首先根据输入，我们可以得到一个链接矩阵，假设是$A$，我们可以重新定义矩阵的乘法

```c++
mat mul(mat A,mat B)
{   
    mat res;
    for(int k = 1; k <= cnt; k++) 
    {
        for(int j = 1; j <= cnt; j++) 
        {
            for(int i = 1; i <= cnt; i++) 
            {
                res.a[i][j] = min(res.a[i][j],A.a[i][k]+B.a[k][j]);
            }
        }
    }
    return res;
}
```
那么$A^k \times A$等价于走了k条边之后，再走一条边，所以我们只需要求出$A^n$次方来就可以得到$s$到$t$经过$n$条边的最短路。

---

## 作者：Object_ (赞：1)

**易错点：**

* 由于是广义矩阵乘法，mul(Mat a,Mat b)方法中的局部变量ans不能使用memcpy直接复制矩阵a或b的数据.

------------

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
using namespace std;
const int MAXN=2e2;
struct Mat{
	int a[MAXN][MAXN];
	void pre(){
		memset(a,0x3f,sizeof(a));
	}
};
int nodeCnt=0;
Mat mul(Mat a,Mat b){
	Mat ans;
	ans.pre();
	for(int i=1;i<=nodeCnt;i++){
		for(int j=1;j<=nodeCnt;j++){
			for(int k=1;k<=nodeCnt;k++){
				ans.a[i][j]=min(ans.a[i][j],a.a[i][k]+b.a[k][j]);
			}
		}
	}
	return ans;
}
Mat poww(Mat a,int x){
	Mat ans;
	memcpy(ans.a,a.a,sizeof(ans.a));
	x--;
	while(x){
		if(x&1)ans=mul(ans,a);
		a=mul(a,a);
		x>>=1;
	}
	return ans;
}
map<int,int> m;
int main(){
	int n,t,s,e;
	scanf("%d%d%d%d",&n,&t,&s,&e);
	Mat a;//defult graph
	a.pre();
	for(int i=1;i<=t;i++){
		int u,v,w;
		scanf("%d%d%d",&w,&u,&v);
		u=m[u]?m[u]:(m[u]=++nodeCnt);
		v=m[v]?m[v]:(m[v]=++nodeCnt);
		a.a[u][v]=a.a[v][u]=min(a.a[u][v],w);
	}
	Mat ans=poww(a,n);
	printf("%d\n",ans.a[m[s]][m[e]]);
	return 0;
}
```


---

## 作者：zhenglier (赞：1)

[更好的观看体验](https://www.cnblogs.com/zhenglier/p/11155878.html)

## 矩阵乘法（快速幂）

为说明方便，这里让$k$为点数，$n$为路径长度。

先将点都离散化，这样最后的点只有$2k$个。

先考虑一种暴力，每次用$O(k^3)$的复杂度来暴力更新，设当前长度$l$点的两两最短路矩阵为$S$，现在要转移到$l+1$时的最短路矩阵$T$。我们考虑用每条边更新，对于某条从$x$连向$y$的长度为$z$的边，对于任一点$i$,有：

$$T[i][y]=min(T[i][y],T[i][x]+z)$$

另外，每次更新时，$T$矩阵的初始值为无限大。

然后我们就可以用$O(nk^3)$的复杂度去做这道题了。但这明显不行。

我们设没有直接连通的两个点距离为无限大，构建出邻接矩阵$D$,就可以魔改一下上面的式子，改成：

$$T[i][j]=min(T[i][x]+D[x][j])$$

其中$x$为自己枚举的中间节点，然后就出现的如下的代码：

```cpp
for(int i=0;i<k;++i){
    for(int j=0;j<k;++j){
        for(int l=0;l<k;++l){
            ret.a[i][j]=min(ret.a[i][j],a.a[i][l]+b.a[l][j]);
		}
	}
}
```
发现，这不是就是矩阵乘法吗？

因为取最小值满足可加性，所以使用矩阵快速幂是可行的。这样，我们就能把复杂度优化为$O(lognk^3)$

然后，我就不开O2过不了了。

我们发现从源点能到达的点数最多只有$k+1$（因为即使走过每条边都发现一个新节点，也只能发现这么多点。）所以我们可以只用源点能到的点进行离散化，可以将点数从$2k$到$k$，从而在矩阵乘法时省掉**8倍**常数，然后就可以不开O2AC了。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1000010,M=200;
int n,k,s,t;
struct data{
    ll a[M][M];
    data(){memset(a,0,sizeof a);}
}a;
data operator*(const data&a,const data&b){
    data ret;
    memset(ret.a,0x3f,sizeof ret.a);
    for(int i=0;i<k;++i){
        for(int j=0;j<k;++j){
            for(int l=0;l<k;++l){
                ret.a[i][j]=min(ret.a[i][j],a.a[i][l]+b.a[l][j]);
			}
		}
	}
	return ret;
}
data mpow(data a,int n){
    data ret=a;
    n--;
    while(n){
         if(n&1)ret=ret*a;
         n/=2;
         a=a*a;
	}
	return ret;
}
int tot,bian[N],nxt[N],head[N];
void add(int x,int y){
    tot++,bian[tot]=y,nxt[tot]=head[x],head[x]=tot;
}
struct edge{
    int x,y;
    ll z;
}e[M];
int vis[N];
vector<int>v;
void dfs(int x){
    if(vis[x])return;
    v.push_back(x);
    vis[x]=1;
	for(int i=head[x];i;i=nxt[i]){
	    int y=bian[i];
	    dfs(y);
	}
}
int main(){
    cin>>n>>k>>s>>t;
    memset(a.a,0x3f,sizeof a.a);
    for(int i=1;i<=k;++i){
        scanf("%lld%d%d",&e[i].z,&e[i].x,&e[i].y);
        add(e[i].x,e[i].y);
        add(e[i].y,e[i].x);
	}
	dfs(s);
	sort(v.begin(),v.end());
	for(int i=1;i<=k;++i){
		if(!vis[e[i].x])continue;
		int x=lower_bound(v.begin(),v.end(),e[i].x)-v.begin(),
		    y=lower_bound(v.begin(),v.end(),e[i].y)-v.begin();
	    a.a[y][x]=a.a[x][y]=min(a.a[x][y],e[i].z);
	    
	}
    data ret=mpow(a,n);
    s=lower_bound(v.begin(),v.end(),s)-v.begin();
    t=lower_bound(v.begin(),v.end(),t)-v.begin();
    cout<<ret.a[s][t]<<endl;
}
```

---

