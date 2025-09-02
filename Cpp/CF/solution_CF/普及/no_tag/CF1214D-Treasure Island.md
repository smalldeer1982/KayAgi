# Treasure Island

## 题目描述

我们都喜爱宝藏，对吧？这就是为何年轻的 Vasya 正在向一个宝藏岛进发。

宝藏岛可以看做一个$n \times m$的矩阵，行从上到下标号为$1..n$，列从左到右标号为$1..m$。Vasya 现在在第$1$行，第$1$列，而宝藏位于第$n$行，第$m$列。

宝藏岛上有些位置是可以通过的空地，而其他位置是不可经过的丛林。

现在 Vasya 正急着寻找宝藏。他可以从第$i$行，第$j$列走到第$i+1$行，第$j$列或第$i$行，第$j+1$列，即，可以向下或向右走。当然他不能通过丛林区域。

邪恶的女巫不想让 Vasya 得到宝藏。她可以用魔法使得一块空地变成丛林。当然，她不能对第$1$行，第$1$列或第$n$行，第$m$列施法。

请计算女巫至少需要将几块丛林变成空地，才能完全阻止 Vasya 获得宝藏。

## 说明/提示

$3 \leq n \times m \leq 10^6$

## 样例 #1

### 输入

```
2 2
..
..
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 4
....
#.#.
....
.#..
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 4
....
.##.
....
```

### 输出

```
2
```

# 题解

## 作者：lenlen (赞：11)

### $Problem$

题意简述：给你一个地图，其中有一些点不能走，问你最少要堵上几个点才能使点 $(1,1)$ 无法走到 $(n,m)$，只能向右或向下行走。

数据范围： $3$ $\leq$ $n×m$ $\leq$ $1 \times 10^6$。

### $Solution$

~~其实这个题作为蓝题挺水的。~~

首先可以考虑到，答案的值为 $0$ 或 $1$ 或 $2$。

证明：

- 因为最劣的情况就是将 $(1,2)$ 和 $(2,1)$ 堵住，价值也就是 $2$。

- 最优的情况就是根本不用你来堵住点，本身 $(1,1)$ 和 $(n,m)$ 就不联通。

那么我们就考虑什么时候会分别取到这三个值就好了。

$0$ 是最容易判的，直接从 $(1,1)$ 开始搜就行了，看能不能搜到 $(n,m)$，如果不能就输出 $0$。

如果搜得到 $(n,m)$，就说明至少要堵住 $1$ 个点了，然后在第一遍搜索的前提下，将第一遍走过的路径上的点变成障碍，在从 $(1,1)$ 出发，再搜一遍，如果还能搜到 $(n,m)$ 那么答案就为 $2$，否则为 $1$。

保证正确性的方法 ~~（虽然好像去掉了也能过）~~ ：第一遍搜索的时候优先往下搜，第二遍搜索优先往右搜，这样的话如果能搜到，因为我们的两条路径一条是优先向右走，一条是优先向下走，若这样都有交点，证明了所有路径必然相交。

### $Code$
~~丑陋的~~ 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;   
const int N=1e6+7232;
int n,m,ans;
string s[N];
int dx[2]={0,1};
int dy[2]={1,0};
void dfs(int x,int y)
{
    if(ans) return ;
    if(x==n&&y==m)
    {
        ans=1;
        return ;
    }
    for(int i=0;i<2;i++)
    {
        int xx=x+dx[i],yy=y+dy[i];
        if(xx<1||yy<1||xx>n||yy>m) continue;
        if(s[xx][yy]=='#') continue;
        s[xx][yy]='#';//将路径上的点设为障碍
        dfs(xx,yy);
        if(ans) return ;//搜到了一条路径，就不能标记其他点了，只标记一条路径上的点
    }
}
int main()  
{   
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) 
    {
        cin>>s[i];
        s[i]='?'+s[i];
    }
    s[1][1]='#';
    dfs(1,1);
    if(!ans) printf("0\n");//如果搜不到终点
    else 
    {
        ans=0;
        s[n][m]='.';//终点是可以经过多次的
        swap(dx[1],dx[0]);swap(dx[0],dx[1]);//保证了第一遍和第二遍搜索的优先方向不同
        dfs(1,1);//再重新搜一遍
        ans++;
        printf("%d\n",ans);
    }
}
```


---

## 作者：Koakuma (赞：10)

## $\text{Solution}$

简单的一道题, 想进去就很好做了 .

很显然, 答案最多是 $2$ , 也就是把起点或者终点直接给堵死 .

所以我们只需要去求 $0$ , $1$ , $2$ 三种中存在的最小值即可 .

考虑从起点 $(1,1)$ $dfs$ 一遍, 若无法到达 $(n,m)$ , 则输出 $0$ .

若可以到达 , 则看看还有没有其他的路可以到达终点 , 注意, 这里存在其他的路的前提是 : 在原先已得出的路径上任意设置障碍都不会受到影响 .

这里有个很巧妙的做法 , 我们在第一遍 $dfs$ 的时候每走到一个可行的位置 , 就将该位置变成障碍 , 然后接着寻找是否存在第二条路径的时候, 我们再 $dfs$ 一次, 如果仍然可以到达终点 , 则说明是存在第二条路的 , 这时候我们输出 $2$ .

其余输出 $1$ 即可 .

## $\text{Code}$

真正代码也就十几行而已 .


```cpp
#include <bits/stdc++.h>
#define reg register

using namespace std;

typedef long long LL;

template < typename _T >
inline void Read(_T &Ass) {
  Ass = 0; _T neg = 1; char c = getchar();
  while (c < '0' || c > '9') { if (c == '-') neg = -1; c = getchar(); }
  while (c >= '0' && c <= '9') Ass = (Ass << 3) + (Ass << 1) + (c & 15), c = getchar();
  Ass *= neg;
}

template < typename T_ >
inline void print(T_ x) {
  if (x < 0) putchar('-'), x = -x;
  if (x < 10) putchar(x + 48);
  else print(x / 10), putchar(x % 10 + 48);
}

template < typename T_ >
inline void print(T_ a, char b) {
  print(a); putchar(b);
}

const int kN = 1e6 + 10;

string s[kN];
int N, M;

int dfs(int x, int y) {
  if (x == N - 1 && y == M - 1) return 1;
  if (x >= N || y >= M) return 0;
  if (s[x][y] == '#') return 0;
  if (x || y) s[x][y] = '#';
  return dfs(x + 1, y) || dfs(x, y + 1);
}

int main() {
  Read(N), Read(M);
  for (reg int i = 0; i < N; ++i) cin >> s[i];
  int rva = dfs(0, 0);
  if (!rva) return puts("0"), 0;
  rva = dfs(0, 0);
  print(rva ? 2 : 1, '\n');
  return 0;
}

```
$ps: $ 修改了原先题解的小错误，不好意思，管理辛苦了

---

## 作者：cccgift (赞：4)

## 这题真的坑……

就这样，我看着机房里的其他同学一个一个在最后几分钟绝杀这道题，然后再看着他们一个一个FST……

首先，我们可以发现，答案肯定不会超过$2$。因为如果我们把$(1,2),(2,1)$这两个点堵上，或者把$(n-1,m),(n,m-1)$赌上，都可以保证走不到终点。

所以，我们可以分类讨论三种答案：

1、$0$

只要刚开始就走不到终点，答案就是$0$，记录一个$f$数组，表示每个点是否能走到，那么$f[i][j]=f[i-1][j]|f[i][j-1]$。

2、$1$

如何判断只堵一个点就能使$Vasya$走不到终点呢？

我们把整个矩阵想象成一个图，$(i,j)$向$(i,j+1),(i+1,j)$连边，就可以构成一个$DAG$。如果这是无向图，那么我们要找的点就是割点。

对于有向图呢？有向图必经点！

然而这是一个$DAG$，我们直接可以用$hash$+路径条数去求必经点。

然而，本题恶意卡$hash$，我们机房里几个写$hash$的同学全部$FST$了……

还有种解决方法是支配树，不过那个没多少人会……而且非常麻烦……

我们得充分挖掘本题的性质，发现有一个这样的性质：

```cpp
..#.
.#..
#...
....
```

如果有一条这样的对角线上的每一个点都是'#'，就无法到达终点。

于是，如果有一条对角线上只有一个'.'，那么这个点就是必经点……吗？

我考场上就这么打了，就这么$WA$了。

考虑如下情况：

```cpp
.#..
#...
..#.
.#..
```

那么$(2,4)$就不是必经边了，因为从起点出发根本到不了……

那么再用$f$数组判断一下能否到达这个点就好了……吗？

我也这么打了，也$WA$了……

再考虑一个情况：

```cpp
..#
.#.
.#.
```

那么$(3,1)$也不是必经点了，因为从它根本到不了终点……

于是，我们再开一个数组$g$，表示每个点出发是否能到达终点。

结论：如果存在一条对角线上只有一个'.'，且这个点能从起点到达它再到达终点，那么它就是必经点。

3、$2$

排除了其它情况，答案就是$2$了。

注意事项：本题的范围是$3≤n*m≤1000000$，我们不能开二维数组，我开了一个一维数组，事实上$vector$也可以。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define ll long long
//#define cccgift
//#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
namespace wode{
    template<typename T>
    inline void read(T &x)
    {
        static char ch;bool f=1;
        for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=0;
        for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());x=f?x:-x;
    }
    template<typename T>
    void print(T x)
    {
        if (x<0) putchar('-'),x=-x;
        if (x>=10) print(x/10);
        putchar(x%10+'0');
    }
    template<typename T>
    inline void print(T x,char ap) {print(x);if (ap) putchar(ap);}
    template<typename T>
    inline T max(T x,T y) {return x<y?y:x;}
    template<typename T>
    inline T min(T x,T y) {return x<y?x:y;}
    template<typename T>
    inline void chkmax(T &x,T y) {x=x<y?y:x;}
    template<typename T>
    inline void chkmin(T &x,T y) {x=x<y?x:y;}
}
using wode::read;using wode::chkmin;using wode::chkmax;using wode::print;
int n,m,d[2000001];
bool f[1000001],g[1000001];
char s[1000001];
inline int getid(int x,int y) {
	if(x<1||y<1||x>n||y>m) return 0;
	return (x-1)*m+y;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(res i=1;i<=n;++i)
	  for(res j=1;j<=m;++j) cin>>s[getid(i,j)];
	f[1]=true;
	for(res i=1;i<=n;++i)
	  for(res j=1;j<=m;++j) if(s[getid(i,j)]=='.'&&(i>1||j>1)) f[getid(i,j)]|=f[getid(i-1,j)]|f[getid(i,j-1)];
	if(!f[n*m]) return cout<<0<<endl,0;
	g[n*m]=true;
	for(res i=n;i;--i)
	  for(res j=m;j;--j) if(s[getid(i,j)]=='.'&&(i<n||j<m)) g[getid(i,j)]|=g[getid(i+1,j)]|g[getid(i,j+1)];
	for(res i=1;i<=n;++i)
	  for(res j=1;j<=m;++j) if(f[getid(i,j)]&&g[getid(i,j)]) ++d[i+j]; //判断对角线
	for(res i=3;i<n+m;++i) if(d[i]==1) return cout<<1<<endl,0; //注意起点和终点的那条对角线不能算！
	cout<<2<<'\n';
	cout<<flush;
	return 0;
}
```

---

## 作者：ChthollyTree (赞：3)

来一个网络流做法

这题应该是一个很基础的模型

就是求割点，对于每个点拆成入点和出点，然后出点和入点连一条权值为$1$的边($(1,1)$和$(n,m)$连一条权值$inf$的边)

然后求最小割即可

因为答案最大是$2$,所以最多增广$2$次，因此复杂度就是$O(n*m)$的，不过常数有点大

```
    #include<bits/stdc++.h>
    using namespace std;
     
    #define MAXN 3000005 
    #define INF 0x3f3f3f3f 
    int st = 1;
    int n,m;
    string s[MAXN]; 
     
    int qsz(int i,int j) {
    	return 2*((i-1)*m+j+1);
    }
     
    void rd()
    {
    	cin >> n >> m; 
    	for(int i = 1; i <= n; i ++)
    		cin >> s[i];
    } 
     
    namespace mp
    {
    	int n,m;
    	struct bian {
    		int x,y,l,ls;
    	}b[MAXN*6];
    	int t[MAXN],cnt = 1;
    	int p[MAXN];
    	queue<int>q;
    	int ss,tt;
    	
    	void wt()
    	{
    		for(int i = 1; i <= cnt; i ++)
    		if(b[i].l != 0)
    		{
    			cout<<b[i].x<<" "<<b[i].y<<" "<<b[i].l<<"\n";
    		}
    		cout<<"------\n";
    	}
    	
    	void qk() {
    		memset(t,0,sizeof(t));
    		cnt = 1;
    	}
    	
    	void jb(int x,int y,int l) {
    		cnt ++;
    		b[cnt].x = x;
    		b[cnt].y = y;
    		b[cnt].l = l;
    		b[cnt].ls = t[x];
    		t[x] = cnt;
    	}
    	
    	void jn(int x,int y,int l) {
    		jb(x,y,l);
    		jb(y,x,0); 
    	} 
    	
    	void huanyuan()
    	{
    		for(int i = 2; i <= m; i ++) {
    			if((i&1) == 0) {
    				b[i].l += b[i^1].l;
    				b[i^1].l = 0;
    			}
    		}
    	}
    	
    	int bfs()
    	{
    		memset(p,0,sizeof(p));
    		q.push(ss);
    		while(!q.empty())
    		{
    			int x = q.front();
    			q.pop();
    			for(int i = t[x]; i != 0; i = b[i].ls) 
    			if(b[i].l > 0){
    				int y = b[i].y;
    				if(!p[y]) {
    					p[y] = i^1;
    					q.push(y);
    				}
    			}
    		}
    		int x = tt,fl = INF;
    		if(p[tt] == 0) return 0;
    		while(x != ss) {
    			fl = min(fl,b[p[x]^1].l);
    			x = b[p[x]].y;
    		}
    		x = tt;
    		while(x != ss) {
    			b[p[x]^1].l -= fl;
    			b[p[x]].l += fl;
    			x = b[p[x]].y;
    		}
    		return fl;
    	} 
    	
    	int EK(int sb,int tb)
    	{
    		ss = sb;
    		tt = tb;
    		m = cnt;
    		int ans = 0;
    		while(1) {
    			int x = bfs();
    			if(x == 0) break;
    			ans += x;
    			
    		} 
    		huanyuan();
    		return ans;
    	}
    	
    }
     
    int an = 0;
     
    int main()
    {
    	rd();
    	for(int i = 1; i <= n; i ++)
    		for(int j = 0; j <= m-1; j++)
    		{
    			int t = qsz(i,j);
    			int td = qsz(i+1,j),tr = qsz(i,j+1);
    			if(s[i][j] != '#') {
    				int ty = 1;
    				if(i == 1 && j == 0) ty = 19260817;
    				if(i == n && j == m-1) ty = 19260817;
    				mp::jn(t,t+1,ty);
    				
    				mp::jn(t+1,td,19260817);
    				mp::jn(t+1,tr,19260817);
    			} 
    		}
    	cout<<mp::EK(qsz(1,0),qsz(n,m-1)+1);
    	return 0;
    }
```

吐槽：

这场pretest真水。

我有个同学写了边的最小割，结果过了pretest



---

## 作者：skydogli (赞：3)

考虑一种新手都打得出的方法:bfs。

首先从终点反向bfs,搜出所有能到达终点的点。然后我们从起点开始bfs，把那些能到终点的没访问过的点入队，找到终点直接结束，而答案就是任意时刻队列里点的数量的最小值。

~~既然它没有fst，那么应该就是对的。~~

我们可以这样理解：答案只有0,1,2两种可能，那么我们分情况考虑：

- 当答案为0时，我们肯定搜不到终点，那么队列就会自然出队直到队列中没有点，那么统计的答案自然为0。

- 当答案为1时，肯定有至少一个时刻队列中只有一个点，如果队列中一直有至少2个点能到终点，那么明显不能只堵一个。

- 其它情况，肯定是有很多种方式能到终点，但是我们最多只需要堵住起点右边和下面的2个点，答案就是2。

对于n,m数据范围不确定的情况，我们可以用一个函数把二维转为一维。

考场代码，不太美观，但是比较好打。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MN 1000015
int n,m,ch[MN],vis[MN],ok[MN];
inline int id(int x,int y){
	return (x-1)*m+y;
}
struct P{
	int x,y;
	P(int X=0,int Y=0){x=X;y=Y;}
};
queue<P>Q;
void bfs(){
	Q.push(P(n,m));
	ok[id(n,m)]=1;
	while(!Q.empty()){
		P w=Q.front();
		Q.pop();
		int x=w.x,y=w.y;
		//		cout<<"OK "<<x<<" "<<y<<endl;
		if(x>1&&!ok[id(x-1,y)]&&ch[id(x-1,y)]!='#'){
			Q.push(P(x-1,y));//注意是反向，所以方向也是反的，下同
			ok[id(x-1,y)]=1;
		}
		if(y>1&&!ok[id(x,y-1)]&&ch[id(x,y-1)]!='#'){
			Q.push(P(x,y-1));
			ok[id(x,y-1)]=1;//预处理出能到达终点的点
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			int now=id(i,j);
			ch[now]=getchar();
			while(ch[now]!='.'&&ch[now]!='#')ch[now]=getchar();
		}
	bfs();
	while(!Q.empty())Q.pop();
	Q.push(P(1,1));
	int ans=3;
	while(!Q.empty()){
		P w=Q.front();
		Q.pop();
		int x=w.x,y=w.y;
		//		cout<<"OK "<<x<<" "<<y<<endl;
		if(x<n&&!vis[id(x+1,y)]&&ok[id(x+1,y)]&&ch[id(x+1,y)]!='#'){
			Q.push(P(x+1,y));
			vis[id(x+1,y)]=1;//不重复入队
		}
		if(y<m&&!vis[id(x,y+1)]&&ok[id(x,y+1)]&&ch[id(x,y+1)]!='#'){
			Q.push(P(x,y+1));
			vis[id(x,y+1)]=1;
		}
		if(vis[id(n,m)]) {break;}//找到终点，直接结束
		ans=min(ans,(int)Q.size());
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Gu_Pigeon (赞：2)

# $ \Huge\texttt 奆 $坑题一道

在赛场上想到第一种办法结果被卡了……QAQ

显而易见的，答案只有$0,1,2$三种可能（真不行就直接堵`(1,2)`与`(2,1)`），如果一开始就不可能从左上角到右下角，则返回0。

处理答案为`1`或者`2`的情况？可以想到，如果有一个格子是所有可行道路的**必经之点**，则把这个格子堵住就OK了，否则输出2。

那么问题就是，如何求这个**必经之点**呢?

八仙过海，各显神通：

## 1.DP

通过递推得到每一个点到达`(1,1)`以及`(n,m)`的方案数，分别为`f[i][j]`与`g[i][j]`，则`f[i][j]*g[i][j]=经过此点的从左上到右下的路径数`，如果该值等于总路数(`g[1][1]`或者`f[n][m]`)，则这个点就是**必经之点**。

### BUT!

这种方法会导致其dp值很大（可以达到$\text C_{n+m}^{n}$左右），所以需要取模等hash方法，而这种方法会有一定概率被卡掉，所以不建议使用这种办法（据编者所知，1e9+7，1e9+9，998244353都被卡了~~某八位质数竟没有被卡~~）

所以还有什么办法呢？

## 2.对角线？

试试[这个题解](https://www.luogu.org/blog/chenyewei1234/cf1214d-treasure-island)？

一种玄学方法（反正我这种蒟蒻是想不出来~~我眼泪在肚子里打转~~），大概是一种**可靠**的正解。

## 3.支配树！

考完后听同机房奆佬说可以用支配树解决，然后就上网搜了一下，发现

$\Huge\texttt{米青女少口啊}$

支配树可以得到一幅图上从某个点到其他点的**必经之点**。

所以这，，不就裸题了吗？？？

那么支配树满足以下性质：

1. 根节点是我们选定的起点s。
2. 对于每个点i，它到根的链上的点集就是对于它的必经点集{xi}。
3. 对于每个点i，它是它的支配树上的子树内的点的必经点。

（↑网上找来的）

而这题又是一个DAG（有向无环图），又有一些蜜汁优越性，在支配树中插入一个新的节点$X_i$，只需要：

1. 求出所有连向该点的节点在树上的lca（最近公共祖先）
2. 将第一步求出的节点作为新节点的父亲
3. 更新插入节点的fa值

好了…

尤其是每一个节点顶多只有两个点连向它，~~所以求lca就珂以直接CXK+C&&CXK+V辣！~~

那么基本上就可以求出`(1,1)`到`(n,m)`的必经之点了，如果`(n,m)`节点在树上的父亲：

1. 是`(1,1)`：两点之间无**必经之点**，输出2
2. 是其他节点：该点到根节点`(1,1)`之间有别的必经之点，输出1
3. 不在树上：无法到达，输出0

$\Large\textit Code\ below$

```cpp
#include<algorithm>
#include<cstdio>
using namespace std;

char s[1 << 20];
int f[1 << 20], g[1 << 20], fa[1 << 20][20], d[1 << 20];
int n, m;

inline int pos(int x, int y)//将二维位置转为一维上的数组位置
{
    return x > 0 && y > 0 ? (x - 1) * m + y : 0;
}

inline int lca(int x, int y)//倍增求LCA
{
    bool bx = x <= 0 || !fa[x][0], by = y <= 0 || !fa[y][0];
    if (bx && by) return 0;
    if (bx && !by) return y;
    if (!bx && by) return x;//几个特判（x,y是否在树上）
    if (d[x] < d[y]) swap(x, y);
    for (int i = 19; i >= 0; i--) if (d[fa[x][i]] >= d[y]) x = fa[x][i];
    if(x == y) return x;
    for (int i = 19; i >= 0; i--) if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

signed main()
{
    // freopen("1.txt", "r", stdin);
    // freopen("2.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", &s[pos(i, 1)]);
   fa[pos(1, 1)][0] = -1;
	for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            int p = pos(i, j);
            if ((i != 1 || j != 1) && s[p] != '#')
            {
                fa[p][0] = lca(pos(i - 1, j), pos(i, j - 1)), d[p] = d[fa[p][0]] + 1;//上面提到的支配树操作
                for (int i = 1; i < 20 && fa[p][i - 1]; i++) fa[p][i] = fa[fa[p][i - 1]][i - 1];//更新fa数组
            }
        }
    switch (fa[pos(n, m)][0])
    {
        case 0: puts("0"); break;
        case 1: puts("2"); break;
        default: puts("1");
    }//情况判断
	return 0;
}

```

（这好像还是伪的支配树，不过能过这一题，在普通图的上支配树还是自行百度吧，窝也不会QAQ…）


---

## 作者：准点的星辰 (赞：2)

### CF1214D 【Treasure Island 】 题解

首先，这道题目我们发现答案只有$0$，$1$，$2$三种情况，因为最坏的情况你只需要在$(n,m-1)$，$(n-1,m)$两个地方放置障碍就可以了。

答案是$0$很好判断，只需要直接$bfs$判断是否可以到达终点就可以了。

答案是$1$的判断仔细想一下，**其实就是让你找是否存在一个点满足所有到终点的路径都经过这个点**。这个点肯定在任意一条路径上，所以我们可以枚举放置选中的到终点的路径上的每个点，然后判断是否可行。时间复杂度$(n+m)*n*m$，然后就炸了。

其实这是一个网格图的经典问题，这里有一个小技巧，就是维护两条路径，一个能往右就往右，另一个能往下就往下，如果这两个路径有交点，就相当于所有的路径都要经过这个点。而我的做法是只维护能向右就向右的，然后把这条路径堵上，如果没有其他的可行路径就说明有我们要找的点，其实实质是一样的。

```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>
#define ll long long
using namespace std;
const int N=1e6+100;
char a[N];
ll s[N],st[N];
bool mark[N];
int n,m,la;
inline void dfs(int x)
{
	if (x!=1&&x!=la)
	mark[x]=1;
	if (x==1) return ;
	if (x%m!=1&&st[x-1]==st[x]-1)
	{
		dfs(x-1);
		return ;
	}
	if (x-m>=1&&st[x-m]==st[x]-1)
	{
		dfs(x-m);
		return ;
	}
	return ;
}
inline void bfs()
{
	memset(st,0,sizeof(st));
	queue<int>q;
	q.push(1);
	st[1]=1;
	while (!q.empty())
	{
		int k=q.front();
		q.pop();
		if ((k+1)%m!=1&&a[k+1]!='#'&&!st[k+1]&&!mark[k+1])
		{
			q.push(k+1);
			st[k+1]=st[k]+1;
		}
		if (k+m<=la&&a[k+m]!='#'&&!st[k+m]&&!mark[k+m])
		{
			q.push(k+m);
			st[k+m]=st[k]+1;
		}
	}
	return ;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	scanf("%s",a+(i-1)*m+1);
	la=strlen(a+1);
	bfs();
	if (st[la]==0)
	{
		printf("0\n");
		return 0;
	}
	dfs(la);
	bfs();
	if (st[la]==0)
	{
		printf("1\n");
		return 0;
	}
	else
	{
		printf("2\n");
		return 0;
	}
	return 0;
}
```

---

## 作者：tujize (赞：1)

一看到这道题能提交题解，顿时精神抖擞

---

~~我就不多说废话了，因为废话说多了还是废话，所以我不说废话了。~~

首先，这道题目我们发现答案只有 0，1，2 三种情况，因为最坏的情况你只需要在
$
(
n,
m-1
)
$
，
$
(
n−1,
m
)
$
两个地方放置障碍就可以了。

答案是 0 很好判断，只需要直接 bfs 判断是否可以到达终点就可以了。

答案是 1 的判断仔细想一下，**其实就是让你找是否存在一个点满足所有到终点的路径都经过这个点**，这个点肯定在任意一条路径上，所以我们可以枚举放置选中的到终点的路径上的每个点，然后判断是否可行。时间复杂度
$
(
n
+
m
)
\times
n
\times
m
$
，然后就炸了。

其实这是一个网格图的经典问题，这里有一个小技巧，就是维护两条路径，一个能往右就往右，另一个能往下就往下，如果这两个路径有交点，就相当于所有的路径都要经过这个点。而我的做法是只维护能向右就向右的，然后把这条路径堵上，如果没有其他的可行路径就说明有我们要找的点，其实实质是一样的。

---

你们最想要的 **CODE** 来了：

```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>
#define ll long long
using namespace std;
const int N=1e6+100;
char a[N];
ll s[N],st[N];
bool mark[N];
int n,m,la;
inline void dfs(int x)
{
	if (x!=1&&x!=la)
	mark[x]=1;
	if (x==1) return ;
	if (x%m!=1&&st[x-1]==st[x]-1)
	{
		dfs(x-1);
		return ;
	}
	if (x-m>=1&&st[x-m]==st[x]-1)
	{
		dfs(x-m);
		return ;
	}
	return ;
}
inline void bfs()
{
	memset(st,0,sizeof(st));
	queue<int>q;
	q.push(1);
	st[1]=1;
	while (!q.empty())
	{
		int k=q.front();
		q.pop();
		if ((k+1)%m!=1&&a[k+1]!='#'&&!st[k+1]&&!mark[k+1])
		{
			q.push(k+1);
			st[k+1]=st[k]+1;
		}
		if (k+m<=la&&a[k+m]!='#'&&!st[k+m]&&!mark[k+m])
		{
			q.push(k+m);
			st[k+m]=st[k]+1;
		}
	}
	return ;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	scanf("%s",a+(i-1)*m+1);
	la=strlen(a+1);
	bfs();
	if (st[la]==0)
	{
		printf("0\n");
		return 0;
	}
	dfs(la);
	bfs();
	if (st[la]==0)
	{
		printf("1\n");
		return 0;
	}
	else
	{
		printf("2\n");
		return 0;
	}
	return 0;
}
```
这是本蒟蒻第一次发题解，点个赞吧！

---

## 作者：yinqf (赞：1)

### Part1 题目大意

给你一个地图，其中有一些点不能走，问你最少要堵上几个点才能使点 $(1,1)$ 无法走到 $(n,m)$，只能向右或向下行走。

$3 \leq n \times m \le 1 \times 10^6$。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1214D/ffd236a717daa534e0ea6864b71f5c242e37614d.png)

如图需要堵住两个位置。

### Part2 做法介绍

答案不超过 $2$（最次堵住出来的两个点），这就很好做，分讨一下即可。

如果本来就搜不到 $(n,m)$，明显是 $0$。

如果搜得到 $(n,m)$，就说明至少要堵住 $1$ 个点了，进行第一遍搜索，将第一遍走过的路径上的点变成障碍，再从 $(1,1)$ 出发，再搜一遍，如果还能搜到 $(n,m)$ 那么答案就为 $2$，否则为 $1$。

搜索时为了方便处理，将第一遍走过的路径上的点都变成了障碍。实际上可以只堵住一个点，就是这条路径上的最关键的点，也能达到全变成障碍的效果，所以这样做是对的。

### Part3 完整代码

```cpp
#include<bits/stdc++.h>
#define LL long long
#define faster ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
const int N=1e6+5;
struct node
{
	int x,y;
};
int n,m;
char t,bf;
vector <char> mp[N];
vector <bool> vis[N];
queue <node> q;
bool check(int x,int y)
{
	if(x>=1&&x<=n&&y>=1&&y<=m&&mp[x][y]=='.'&&vis[x][y]==0)return 1;
	else return 0;
}
bool dfs(int x,int y)
{
    if(x==n&&m==y)
    {
        mp[x][y]='#';
        return 1;
    }
    if(check(x+1,y))
    {
        if(dfs(x+1,y))
        {
            mp[x][y]='#';
            return 1;
        }
    }
    if(check(x,y+1))
    {
        if(dfs(x,y+1))
        {
            mp[x][y]='#';
            return 1;
        }
    }
    return 0;
}
int main()
{
	faster;
	cin >> n >> m;
	for(int i=1;i<=n;i++)
	{
		mp[i].push_back(0);
		vis[i].push_back(0);
		for(int j=1;j<=m;j++)
		{
			cin >> t;
			mp[i].push_back(t);
			vis[i].push_back(0);
		}
	}
	if(dfs(1,1))
	{
		cout << 0;
		return 0;
	}
	else
	{
		if(dfs(1,1))
		{
			cout << 2;	
			return 0;
		}
        else
        {
            cout << 1;	
            return 0;
        }
	}
	return 0;
}
```

---

## 作者：AFOier (赞：1)

可以说是很水的一道D题了……

题意：给定一个矩阵，你只能向下或向右走。有些格子不能通行，求至少放置多少个障碍使得不能从左上角走到右下角。

显然答案最多为2，只需堵住起点或终点连接的格子即可。

要使答案为0，只有一种情况，左上角无法到达右下角，dfs判定即可

要使答案为1，即堵住了某一个点之后左上角就无法到达右下角，则堵住的点必定是从步数为（左上角到当前点的步数）的唯一点。

但是有可能有其他步数相同但是无法到达右下角的点，我们可以在dfs判定左上角与上下角是否连通的时候预处理出能到达右下角的点

由于步数唯一，只需在矩阵中跑bfs遍历可以到达右下角的点，找到前后的步数都与当前点不同的点。若该点存在，则答案为1，否则为2

至于存储方式，因为nm<=1e6，所以可以用vector存，也可以转为一维数组。我用的是后者。

时间复杂度$O(n)$

$Code:$
```
#include <cstdio>
#include <iostream>
using namespace std;
int n,m,ans;
char a[1000011];//输入的矩阵
bool vis[1000011];//dfs判重
int dl[1000011][2];//bfs队列
int bs[1000011];//bfs中存储当前点到左上角点的步数
int used[1000011];//bfs判重
bool success;//是否是所有从左上角到右下角的路径的必经点
int head,tail;
int cal(int xx,int yy){
    return (xx-1)*m+yy;
}//二维数组下标转一维
void dfs(int x,int y){
    vis[cal(x,y)]=1;
    if(!vis[cal(x-1,y)]&&x-1>=1&&a[cal(x-1,y)]=='.')dfs(x-1,y);
    if(!vis[cal(x,y-1)]&&y-1>=1&&a[cal(x,y-1)]=='.')dfs(x,y-1);
}
void bfs(){
	dl[1][0]=1;dl[1][1]=1;bs[1]=0;tail=1;
	while(head<tail){
		int nwx=dl[++head][0],nwy=dl[head][1];
		used[cal(nwx,nwy)]=1;
		if(bs[head]!=bs[head-1]&&bs[head]!=bs[head+1]&&(bs[head]!=0)&&(!(nwx==n&&nwy==m))){
			success=true;
			return ;
		}//若当前点不为左上角和右下角且上一个节点步数和下一个节点步数都不等于当前节点步数，则当前点为所有从左上角到右下角的路径的必经点
		if(vis[cal(nwx+1,nwy)]&&nwx+1<=n&&(!used[cal(nwx+1,nwy)])){
			dl[++tail][0]=nwx+1;
			dl[tail][1]=nwy;
			bs[tail]=bs[head]+1;
			used[cal(nwx+1,nwy)]=1;
		}
		if(vis[cal(nwx,nwy+1)]&&nwy+1<=m&&(!used[cal(nwx,nwy+1)])){
			dl[++tail][0]=nwx;
			dl[tail][1]=nwy+1;
			bs[tail]=bs[head]+1;
			used[cal(nwx,nwy+1)]=1;
		}
	}
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
        cin>>a[cal(i,j)];
    }
    dfs(n,m);//从右下角开始跑dfs预处理出所有可以到达右下角的点
    if(!vis[cal(1,1)]){
        cout<<0<<endl;
    }//如果左上角不能到达右下角，输出0
    else{
    	success=false;
    	bfs();
        if(success)cout<<1<<endl;//若有所有从左上角到右下角的路径的必经点，输出1
        else cout<<2<<endl;//否则输出2
    }
    return 0;
}
```

---

## 作者：Llf0703 (赞：1)

[更好的阅读体验](https://llf0703.com/p/cf-1214.html)

## 题意

从 $(1,1)\rightarrow (n,m)$ ，只能向上向右走，图中的障碍物不能通过。问至少要再放置几个障碍物，使得无法到 $(n,m)$ 。

$n\times m\le 10^6$ 。

## 题解

可以发现答案最多为 $2$ ，即在 $(1,2)$ 和 $(2,1)$ 放上障碍物。所以只需要考虑答案为 $1,0$ 的情况。

如果答案为 $0$ ，说明本来就无法到 $(n,m)$ ，用 $\text{bfs}$ 搜索一遍即可判断。

如果答案为 $1$ ，就说明有一个格子是类似割点一样的状态。用 $gs[i][j]$ 表示从 $(1,1)\rightarrow (i,j)$ 的路径方案数，$gt[i][j]$ 表示从 $(n,m)\rightarrow (i,j)$ 的方案数，方程式为：

$$\begin{cases} gs[i][j]=gs[i-1][j]+gs[i][j-1]  \\ gt[i][j]=gt[i+1][j]+gt[i][j+1] \end{cases}$$

如果存在一个点 $(i,j)$ ，使得 $gs[i][j]\times gt[i][j]=gs[n][m]$ ，就说明所有路径都会经过这个点，那么就可以放障碍物在这个点，答案为 $1$ 。

不过 $gs,gt$ 可能会很大，所以需要膜一个大质数。我当时想过多膜几个，但仔细想来就算要叉我构造数据也很麻烦，就没写。

其它情况答案就是 $2$ 。

```cpp
#include<bits/stdc++.h>
#define ha 19260817
#define pii pair<int,int>
#define mp make_pair

using namespace std;

inline int read()
{
    char ch=getchar(); int f=1,x=0;
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return f*x;
}

char ch[1000005];
bool s[1000005],vis[1000005];
int n,m,gs[1000005],gt[1000005];
const int fx[2]={1,0},fy[2]={0,1};

inline int f(int x,int y) //将二维坐标转为一维
{
    if (x<1 || x>n || y<1 || y>m) return 0;
    return (x-1)*m+y;
}

inline void bfs()
{
    vis[f(1,1)]=1;
    queue <pii> q;
    q.emplace(mp(1,1));
    while (!q.empty())
    {
        int x=q.front().first,y=q.front().second; q.pop();
        for (int i=0;i<2;i++)
        {
            int tx=x+fx[i],ty=y+fy[i];
            if (tx<1 || tx>n || ty<1 || ty>m || s[f(tx,ty)] || vis[f(tx,ty)]) continue;
            vis[f(tx,ty)]=1;
            q.emplace(mp(tx,ty));
        }
    }
}

signed main()
{
    n=read(); m=read();
    for (int i=1;i<=n;i++)
    {
        scanf("%s",ch+1);
        for (int j=1;j<=m;j++) s[f(i,j)]=ch[j]=='#';
    }
    bfs();
    if (!vis[f(n,m)]) return 0&puts("0"); //如果无法到达说明答案是0
    gs[f(1,1)]=1;
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) 
        if ((i!=1 || j!=1) && !s[f(i,j)]) gs[f(i,j)]=(gs[f(i-1,j)]+gs[f(i,j-1)])%ha;
    gt[f(n,m)]=1;
    for (int i=n;i;i--) for (int j=m;j;j--)
        if ((i!=n || j!=m) && !s[f(i,j)]) gt[f(i,j)]=(gt[f(i+1,j)]+gt[f(i,j+1)])%ha;
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++)
    {
        if ((i==1 && j==1) || (i==n && j==m)) continue;
        if (1ll*gs[f(i,j)]*gt[f(i,j)]%ha==gs[f(n,m)]%ha) return 0&puts("1"); //(i,j)是割点，答案为1
    }
    return 0&puts("2");
}
```

---

## 作者：ZLCT (赞：0)

# CF1214D Treasure Island
## 题目翻译
给定一个 $n\times m$ 的矩形，有若干障碍点不能走，现在要从 $(1,1)$ 走到 $(n,m)$（只往下或右走），求最少把多少点改成障碍才能使无法从 $(1,1)$ 走到 $(n,m)$。
## 这题好像哪里见过
在见到这个题的第一眼我就想到 [ARC074F] Lotus Leaves，唯一的区别就是那个题起点终点不固定。\
那个题就是个最小割模板，将每个点拆成入点和出点，不连通就对应着被割开，将入点出点之间的流量设为 $1$，其余设为 $+\infty$，那么求最小割即可。\
正当我开始写时，观察到数据范围 $10^6$，理论上网络流是跑不过的，于是我们可以加一些小优化。\
观察到只要我们把 $(1,2),(2,1)$ 两点断开就一定满足条件，所以流量最大我们可以设为 $2$，这样跑得能快一些。\
但是比较悲催的是我只会 Dinic，所以最终遗憾 TLE on #16（有人用 EK 过了）。
### TLE code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+666;
int cur[N<<1],dep[N<<1];
int n,m,S,T;
string s;
struct edge{
    int to,w,flow,fxid;
};
vector<edge>G[N<<1];
void add(int u,int v,int w){
    G[u].push_back((edge){v,w,0,(int)G[v].size()});
    G[v].push_back((edge){v,0,0,(int)G[u].size()-1});
}
bool bfs(){
    queue<int>q;
    memset(dep,0,sizeof(dep));
    dep[S]=1;
    q.push(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(edge v:G[u]){
            if(v.flow>=v.w)continue;
            if(dep[v.to])continue;
            dep[v.to]=dep[u]+1;
            q.push(v.to);
        }
    }
    if(dep[T])return 1;
    return 0;
}
int dfs(int u,int maxflow){
    if(u==T)return maxflow;
    int flowww=maxflow;
    for(int i=cur[u];i<G[u].size();i=cur[u]+1){
        edge v=G[u][i];
        cur[u]=i;
        if(v.flow>=v.w)continue;
        if(dep[v.to]!=dep[u]+1)continue;
        int nowflow=dfs(v.to,min(maxflow,v.w-v.flow));
        G[u][i].flow+=nowflow;
        G[v.to][v.fxid].flow-=nowflow;
        maxflow-=nowflow;
        if(!maxflow)break;
    }
    if(flowww-maxflow>=2){
        cout<<2<<'\n';
        exit(0);
    }
    return flowww-maxflow;
}
void Dinic(){
    int res=0;
    while(bfs()){
        memset(cur,0,sizeof(cur));
        res+=dfs(S,2);
        if(res>=2){
            cout<<2<<'\n';
            return;
        }
    }
    cout<<res<<'\n';
    return;
}
signed main(){
    cin>>n>>m;
    S=1+n*m;T=n*m;
    for(int i=0;i<n;++i){
        cin>>s;
        for(int j=0;j<m;++j){
            if(s[j]=='#')continue;
            add(i*m+j+1,i*m+j+1+n*m,1);
            if(i!=n-1)add(i*m+j+1+n*m,i*m+m+j+1,2);
            if(j!=m-1)add(i*m+j+1+n*m,i*m+j+2,2);
        }
    }
    Dinic();
    return 0;
}
```
## 如梦初醒
TLE 完我才发现既然一共最大值就是 $2$，何不之间暴力跑 Dinic 里的 dfs？具体来说就是暴力 dfs 找从 $(1,1)$ 到 $(n,m)$ 的路径，假设找到了两条路径则直接输出即可（因为最大答案就是 $2$），否则找到几条不相交的路径答案就是几。\
如何处理不相交？\
这点好办，只要当次已经找到了一条 $(n,m)$ 的路径就不要再继续找了，而在这条路径上的点标记一下下次不要找了就好了。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+666;
string s[N];
int n,m,d[N],now;
void dfs(int x,int y){
    if(s[x][y]=='#')return;
    d[x*m+y+1]++;
    int nx=x+1,ny=y;
    if(nx==n-1&&ny==m-1)d[n*m]++;
    if(nx<n&&!d[nx*m+ny+1])dfs(nx,ny);
    if(d[n*m]>now)return;
    nx=x;ny=y+1;
    if(nx==n-1&&ny==m-1)d[n*m]++;
    if(ny<m&&!d[nx*m+ny+1])dfs(nx,ny);
    if(d[n*m]>now)return;
    d[x*m+y+1]--;
}
signed main(){
    cin>>n>>m;
    for(int i=0;i<n;++i){
        cin>>s[i];
    }
    dfs(0,0);
    now=1;
    dfs(0,0);
    cout<<d[n*m]<<'\n';
    return 0;
}
```
## 大彻大悟
但是你以为这就能过吗？那是不可能的。\
这么写和 Dinic 压根没有区别啊，所以还是会 TLE on #16。\
这题妙就妙在答案最大为 $2$，我们路径既然不能相交，那么尽量使这两条路径离得越远越好，所以我们可以规定第一条路尽可能先向下走，第二条路径尽可能先向右走（反之亦可）。\
这样第一次不在路径上的点也不需要回溯了，复杂度就变成 $O(n)$ 了。\
但是但是～\
这样需要写两个 dfs，实际上思考一下会发现其实不需要再写了，因为我们 dfs 只会一直找没有标记的点，所以第二次即便我们不换路径更新方向，它也只能走我们第一遍走的路径上面的路径。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+666;
string s[N];
int n,m,d[N],now;
void dfs(int x,int y){
    if(s[x][y]=='#')return;
    d[x*m+y+1]++;
    int nx=x+1,ny=y;
    if(nx==n-1&&ny==m-1)d[n*m]++;
    if(nx<n&&!d[nx*m+ny+1])dfs(nx,ny);
    if(d[n*m]>now)return;
    nx=x;ny=y+1;
    if(nx==n-1&&ny==m-1)d[n*m]++;
    if(ny<m&&!d[nx*m+ny+1])dfs(nx,ny);
}
signed main(){
    cin>>n>>m;
    for(int i=0;i<n;++i){
        cin>>s[i];
    }
    dfs(0,0);
    now=1;
    dfs(0,0);
    cout<<d[n*m]<<'\n';
    return 0;
}
```

---

## 作者：雄鹰展翅 (赞：0)

考虑一种极端情况：直接把起点处或终点处周围的格子堵死，此时答案为2，故答案最多为2。

用$a[i][j]$表示从起点出发能否到达点$(i,j)$,$b[i][j]$表示从终点出发能否到达点$(i,j)$：

 - 若从起点出发无法到达点$(n,m)$，则输出0；
 - 若一个点为**割点**时，输出1，此时这个点**在路径上**，并且过这个点的一三象限对角线上**只有这一个**在路径上的点；
 - 否则输出2。
 
 代码：
 
```cpp
#include<iostream
#include<string.h>
#define N 1000005
using namespace std;

int n,m;
int cnt[2*N];
string s[N];

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>s[i];
		for(int j=m+1;j>=1;--j) s[i][j]=s[i][j-1];//下标从1开始
	}
	bool a[n+10][m+10],b[n+10][m+10];//没错，这能过
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	
	a[1][0]=1;//边界小技巧
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(s[i][j]=='.') a[i][j]=a[i][j-1]||a[i-1][j];
	if(a[n][m]==0) {cout<<0<<endl;return 0;}
	b[n][m+1]=1;
	for(int i=n;i>=1;--i)
		for(int j=m;j>=1;--j)
			if(s[i][j]=='.') b[i][j]=b[i][j+1]||b[i+1][j];
	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) 
			if(a[i][j]&&b[i][j]&&s[i][j]=='.') cnt[i+j]++;
	for(int i=3;i<=n+m-1;++i) 
		if(cnt[i]==1) {cout<<1<<endl;return 0;}
	
	cout<<2<<endl;
	return 0;
}
```

---

## 作者：lenaalyth (赞：0)

蒟蒻趁人少过来发一下题解，题意为放最少的点使得无法走到=最小割，考虑网络流求解，如果两条边能有相同点的话在那个点放一个格子就可以了，所以每个格子只走一次就可以了，而题意可知最多最多需要放两个格子，于是控制一下dinic里面bfs的次数小于一定数量，防止超时（可能会？不确定）。。然后就是套网络流模板了，每个点和他右边的点下面的点连单向边，因为每个点只能走一次所以拆点处理一下即可。
代码如下：
```cpp
// luogu-judger-enable-o2
#include<cstdio>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cstring>
#include <string>
using namespace std;
int flow[8100000],to[8100000],next1[8100000],deep[8100000],head[4800000],cw[8100000],zw[8100000],qw[8100000],t,m,N,M,S,T,s1,e1,q1;
long long ans;
int l=0;
void add(int s,int e,int q) {
	if(head[s]==-1) {
		flow[m]=q;
		head[s]=m;
		to[m]=e;
	} else {
		next1[m]=head[s];
		head[s]=m;
		to[m]=e;
		flow[m]=q;
	}
	//printf("%d %d %d %d\n",flow[m],head[s],to[m],next[m]);
	m++;
}
bool bfs(int s,int e) {
	memset(deep,0,(N+3)<<2);
	deep[s]=1;
	queue<int> dl;
	dl.push(s);
	while(!dl.empty()) {
		int l=dl.front();
		//cout<<dl.size()<<endl;
		dl.pop();//cout<<dl.size()<<endl;
		for(int x=head[l]; x>=0; x=next1[x]) {
			//printf("%d %d %d %d %d\n",deep[to[x]],next[x],x,l,deep[l]);
			if(flow[x]&&deep[to[x]]==0) {
				//cout<<endl;
				deep[to[x]]=deep[l]+1;
				dl.push(to[x]);
			}
			//	printf("%d %d %d %d %d\n",deep[to[x]],next[x],x,l,deep[l]);
		}
	}
	return deep[e];
}
int aim;
int dfs(int now,int fl) {
	int f=0;
	if(now==aim) return fl;
	for(int x=head[now]; x>=0&&fl; x=next1[x]) {
		//head[now]=x;
		if(flow[x]&&deep[to[x]]==deep[now]+1) {
			int zhi=dfs(to[x],min(fl,flow[x]));
			flow[x]-=zhi;
			flow[x^1]+=zhi;
			f+=zhi;
			fl-=zhi;
		}
	}
	if(!f)
		deep[now]=-2;
	return f;
}
void adds(int ss,int ee,int qq) {
	add(ss,ee,qq);
	add(ee,ss,0);
}
long long int maxflow(int s,int e) {
	long long int ret=0;
	aim=T;
	int q=5;
	while(bfs(s,e)&&q<11) {
		q++;//cout<<1;
		ret+=dfs(s,1<<30);
	}
	return ret;
}
string s11[1110000];
int main() {
	cin>>N>>M;
	S=0;
	memset(head,-1,sizeof(head));
	memset(next1,-1,sizeof(next1));
    adds(0,1,100);//初始点肯定是可以无数次的啊
	for(int x=0; x<N; x++) {
		cin>>s11[x];
		for(int y=0; y<s11[x].size(); y++) {
                adds(2*l,2*l+1,1);
			if(y!=s11[x].size()) {
                    if(s11[x][y+1]=='.'&&s11[x][y]=='.')
                        {
                            adds(2*l+1,2*(l+1),1);
                        }
			}
			if(x!=0)
			{
			    if(s11[x][y]=='.'&&s11[x-1][y]=='.')
				{
				    adds(2*(l-s11[x].size())+1,2*l,1);
				}
			}
			l++;
		}
	}
	T=2*(l-1);
	ans=maxflow(S,T);
	printf("%lld\n",ans);
}
```



---

## 作者：miaokehao (赞：0)

**显然答案最多只有2，所以答案只可能是0，1，2**  
**0是不联通，一次dfs就可以判断**  
**1是说明在建图之后$(1,1)$到$($n$,$m$)$的路径上有必经点，于是有向图必经点就让我们联想到了支配树，于是就过了**
```
#include<bits/stdc++.h>
#define res register int
#define N 2000010
#define M 4000010
using namespace std;
bool vis[N], ifok[N];
int n, m, a[N];
inline int read(){
	res w=0,X=0;register char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){X=(X<<1)+(X<<3)+(ch^48);ch=getchar();}
	return w?-X:X;
}
struct papa{
	papa():to(0), next(0){};
	int to, next;
};
struct Graph {
	int d[N], tot;
	papa e[M];
	Graph(){
		memset(d, 0, sizeof(d));
		tot = 0;
	}
	inline void add(res x, res y) {
		e[++tot].to = y;
		e[tot].next = d[x];
		d[x] = tot;
	}	
}G, R, S, T;
int g[N], sdom[N], idom[N], dfn[N], mn[N], id[N], fa[N], size[N], tim;
inline int find(res x) {
	if(g[x] == x) return x;
	int f = g[x]; 
	g[x] = find(g[x]);
	if(dfn[sdom[mn[f]]] < dfn[sdom[mn[x]]])
		mn[x] = mn[f];
	return g[x];
}
inline void Dfs(res now) {
	dfn[now] = ++tim; id[tim] = now;
	for(res i = G.d[now]; i; i = G.e[i].next){
		res x = G.e[i].to;
		if(dfn[x]) continue;
		fa[x] = now;
		Dfs(x);
    }
}
inline void tarjan() {
	for(res i = 1;i <= n * m; ++i)
		sdom[i] = mn[i] = g[i] = i;
	for(res k = tim; k; --k) {
		res now = id[k];
		for(res i = S.d[now]; i; i = S.e[i].next){
			res x = S.e[i].to;
			find(x);
			if(sdom[mn[x]] == now) idom[x] = now;
			else idom[x] = mn[x];
		}
		for(res i = R.d[now]; i; i = R.e[i].next){
			res x = R.e[i].to;
			if(dfn[x]) {
				find(x);
				if(dfn[sdom[mn[x]]] < dfn[sdom[now]])
					sdom[now] = sdom[mn[x]];
			}
		}
		S.add(sdom[now], now); g[now] = fa[now];
	}
	for(res i = 2; i <= tim; ++i) {
		res now = id[i];
		if(idom[now] != sdom[now])
			idom[now] = idom[idom[now]];
//		T.add(idom[now], now);
	}
}
inline int ID(res x, res y){
	return (x - 1) * m + y;
}
inline void work(res now) {
	size[now] = 1;
	for(res i = T.d[now]; i; i = T.e[i].next){
		res x = T.e[i].to;
		work(x);
		size[now] += size[x];
    }
}
inline bool dfs(res now, res fa){
	if(now == n * m) return 1;
	if(vis[now]) return ifok[now];
	vis[now] = 1;
	for(res i = G.d[now]; i; i = G.e[i].next){
		res x = G.e[i].to;
		if(dfs(x, now)) return ifok[now] = 1;
	}
	return ifok[now] = 0;
}
int main() {
	n = read(), m = read();
	for(res i = 1; i <= n; i++)
	  for(res j = 1; j <= m; j++){
	  	register char ch = getchar();
	  	while(ch != '.' && ch != '#') ch = getchar();
	  	if(ch == '.') a[ID(i, j)] = 0;
	  	else a[ID(i, j)] = 1;
	  }
	for(res i = 1; i <= n; i++)
	  for(res j = 1; j <= m; j++){
	  	if(a[ID(i, j)] == 1) continue;
	  	if(j < m && a[ID(i, j + 1)] != 1) G.add(ID(i, j), ID(i, j + 1)), R.add(ID(i, j + 1), ID(i, j));
	  	if(i < n && a[ID(i + 1, j)] != 1) G.add(ID(i, j), ID(i + 1, j)), R.add(ID(i + 1, j), ID(i, j));
	  }
	if(!dfs(1, 0)){
		puts("0");
		return 0;
	}
	Dfs(1); 
	tarjan(); 
	work(1);
	if(idom[ID(n, m)] == 1)
		puts("2");
	else
	    puts("1");
	return 0;
}
```


---

## 作者：CYJian (赞：0)

在机房打CF的时候:

"Jerry你D被叉了"

"怎么可能啊, 我双哈希都能被叉?"

10min后...

"Jerry你的D怎么又被叉了?"

"我改了模数了啊...算了改个三模数我就不信这回还被叉"

最后, 这位同学趁着比赛最后一分钟交了...最后还是A了...

甚至有一个rand双模数的fst了...

---

**然而, 这里有一个完全不用担心被叉模数的做法:**

朋友, 你听说过狼抓兔子么?

---

我们利用一下[狼抓兔子](https://www.luogu.org/problem/P4001)的想法.

这道题里头相当于是要你搞出一条分裂 $(1, 1)$ 和 $(n, m)$ 的路径, 这条路径上全是 '#'. 这时候你找的路径在这个网格图中是八连通的了.

连边的时候将起点 $S$ 连接 $x = n$ 和 $y = m$ 的所有点, $x = 1$ 和 $y = m$ 的所有点连接 $T$. 这里 $(1, 1)$ 和 $(n, m)$ 需要从图中删去, 因为这两个点没法被覆盖上森林.

然后考虑边权的问题. 如果走到的下一个点是空地就连一条边权为 $1$ 的边, 如果走到的是森林就连一条边权为 $0$ 的边. 

然后直接跑最短路就是答案了.

是不是觉得很有道理?

然后你就会:

![](https://cdn.luogu.com.cn/upload/image_hosting/3tldjq3e.png)

为啥呢...

这里给一个数据哈:

```plain
8 8
..#.....
..#.....
..#.....
..#.....
.....#..
.....#..
.....#..
.....#..
```

显然, 答案是$0$...

但是按照刚才的算法, 跑出来的结果是$2$...

为啥呢?

我们考虑这样一个问题: 如果某时刻一个人在 $(x, y)$ 上, 那么他能到达的点为 $(x + 1, y)$ 和 $(x, y + 1)$

也就是说, 如果你跑最短路有一条路径走到了 $(x', y')$, 那么不管 $(x', y' - 1)$ 是不是森林, 它都等效于有一个森林在那里: 因为如果你在$(x', y' - 1)$的话, 那么你肯定无法穿过 $(x', y')$, 而且 $(x', y')$ 连通了一个到底边的森林的路径, 所以你就没法穿过这个森林的路径了..

就比如你在上面给的数据的$(5,5)$的时候, 你就没法穿过下面的那一条'#'的路径.

所以就很明了了: 每一个点往左/下/左下方的路径的权值一定为0.

然后这样你就可以过$pretest$了..

---

然后当我再看$System\ Test$的时候:

![](https://cdn.luogu.com.cn/upload/image_hosting/bnpq6h5l.png)

然后好像我的边建了$10^7$, 跑的Dijsktra还带个log, 然后我们机房还有一个TLE的fst, 而且还不带log的时候...

我慌得一批...

结果...

![](https://cdn.luogu.com.cn/upload/image_hosting/txoy9j3a.png)

~~慌nm啊稳得一匹...~~

其实也挺好写的...(请无视上面一大坨比赛用模板...)

```cpp
#include <bits/stdc++.h>
	
using namespace std;
	
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	inline void pc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template <class I>
	inline void gi (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	template <class I>
	inline void print (I x) {
		if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) pc (qu[qr --]);
	}
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: gi;
using io :: print;
using io :: pc;
	
#define Space pc(' ')
#define Enter pc('\n')
	
typedef long long ll;
typedef double db;
typedef unsigned int uit;
	
template<typename T> inline void chkmax(T&a, T b) { a = a > b ? a : b; }
template<typename T> inline void chkmin(T&a, T b) { a = a < b ? a : b; }
template<typename T> inline int gcd(T&a, T b) { return !b ? a : gcd(a, b); }
	
const db pi = acos(-1);
const int mod = 19260817;
const int Mod1 = 19491001;
const int Mod2 = 998244353;
const int Mod3 = 1000000007;
const int Mod4 = 1004535809;
const int Mod5 = 104857601;
// 看题目模数, 记得改啊!!!!!!
const int MAXN = 1000000;
	
inline int Mod(int x) { return x >= mod ? x - mod : x; }
inline void Add(int&x, int y) { x = Mod(x + y); }
inline int Mul(int x, int y) { return 1LL * x * y % mod; }
	
int n, m;
	
char s[MAXN + 1];
int v[MAXN + 1];
	
int tot;
int to[MAXN * 10];
int ne[MAXN * 10];
int fi[MAXN + 1];
int vl[MAXN * 10];
	
int sta[MAXN + 1];
	
inline void Link(int u, int v, int X = 1) {
	tot++;
	vl[tot] = sta[v] * X;
	to[tot] = v;
	ne[tot] = fi[u];
	fi[u] = tot;
}
	
inline int id(int x, int y) { return (x - 1) * m + y; }
	
struct Node {
	int x, d;
	
	Node(int x = 0, int d = 0):x(x), d(d) {}
	
	friend bool operator < (Node a, Node b) { return a.d < b.d; }
	friend bool operator > (Node a, Node b) { return a.d > b.d; }
};
	
priority_queue<Node, vector<Node>, greater<Node> >q;
	
int dis[MAXN + 1];
	
inline int Dijsktra(int S, int T) {
	memset(dis, 63, sizeof(dis));
	dis[S] = 0; q.push(Node(S, 0));
	while(!q.empty()) {
		Node f = q.top(); q.pop();
		if(f.d != dis[f.x]) continue;
		for(int i = fi[f.x]; i; i = ne[i]) {
			int u = to[i];
			if(dis[u] > dis[f.x] + vl[i]) {
				dis[u] = dis[f.x] + vl[i];
				q.push(Node(u, dis[u]));
			}
		}
	} return dis[T];
}
	
int main() {
	scanf("%d%d", &n, &m);
	int S = 1, T = n * m, ct = 2;
	for(int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for(int j = 1; j <= m; j++)
			sta[id(i, j)] = s[j] == '.' ? 1 : 0;
	} sta[S] = sta[T] = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(i == 1 && j == 1) continue;
			if(i == n && j == m) continue;
			if(i == 1 || j == m) Link(id(i, j), T);
			if(i == n || j == 1) Link(S, id(i, j));
			int to = id(i - 1, j);
			if(i > 1 && to != S && to != T) Link(id(i, j), to);
			to = id(i + 1, j);
			if(i < n && to != S && to != T) Link(id(i, j), to, 0);
			to = id(i, j - 1);
			if(j > 1 && to != S && to != T) Link(id(i, j), to, 0);
			to = id(i, j + 1);
			if(j < m && to != S && to != T) Link(id(i, j), to);
			to = id(i + 1, j + 1);
			if(i < n && j < m && to != S && to != T) Link(id(i, j), to);
			to = id(i - 1, j + 1);
			if(i > 1 && j < m && to != S && to != T) Link(id(i, j), to);
			to = id(i + 1, j - 1);
			if(i < n && j > 1 && to != S && to != T) Link(id(i, j), to, 0);
			to = id(i - 1, j - 1);
			if(i > 1 && j > 1 && to != S && to != T) Link(id(i, j), to);
		}
	}
	printf("%d\n", Dijsktra(S, T));
	return 0;
}
```

---

