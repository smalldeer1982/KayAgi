# [USACO20DEC] Stuck in a Rut S

## 题目描述

Farmer John 最近扩大了他的农场，从奶牛们的角度看来这个农场相当于是无限大了！奶牛们将农场上放牧的区域想作是一个由正方形方格组成的无限大二维方阵，每个方格中均有美味的草（将每个方格看作是棋盘上的一个方格）。Farmer John 的 $N$ 头奶牛（$1≤N≤1000$）初始时位于不同的方格中，一部分朝向北面，一部分朝向东面。

每一小时，每头奶牛会执行以下二者之一：

 - 如果她当前所在的方格里的草已经被其他奶牛吃掉了，则她会停下（并从这个时刻开始一直保持停止）。
 - 吃完她当前所在的方格中的所有草，并向她朝向的方向移动一个方格。

经过一段时间，每头奶牛的身后会留下一条被啃秃了的轨迹。

如果两头奶牛在一次移动中移动到了同一个有草的方格，她们会分享这个方格中的草，并在下一个小时继续沿她们朝向的方向移动。

当 Farmer John 看到停止吃草的奶牛时会不高兴，他想要知道谁该为他停止吃草的奶牛受到责备。如果奶牛 $b$
停在了之前奶牛 $a$ 吃过草的一个方格，我们就称奶牛 $a$ 阻碍了奶牛 $b$。进一步地，如果奶牛 $a$ 阻碍了奶牛 $b$ 且奶牛 $b$ 阻碍了奶牛 $c$，我们认为奶牛 $a$ 也阻碍了奶牛 $c$（也就是说，「阻碍」关系具有传递性）。每头奶牛受到责备的程度与这头奶牛阻碍的奶牛数量一致。请计算每头奶牛受到责备的数量——也就是说，每头奶牛阻碍的奶牛数量。 

## 说明/提示

在这个样例中，奶牛 3 阻碍了奶牛 2，奶牛 4 阻碍了奶牛 5，奶牛 5 阻碍了奶牛 6。根据传递性，奶牛 4 也阻碍了奶牛 6。 

 - 测试点 2-5 中，所有坐标不超过 $2000$。
 - 测试点 6-10 没有额外限制。

供题：Brian Dean 

## 样例 #1

### 输入

```
6
E 3 5
N 5 3
E 4 6
E 10 4
N 11 1
E 9 2```

### 输出

```
0
0
1
2
1
0
```

# 题解

## 作者：feicheng (赞：37)

# P7150 题解


### 思路
 _经过一段时间，每头奶牛的身后会留下一条被啃秃了的轨迹。_ 
 
 这一句给了我们很关键的提示：**奶牛的轨迹是一条线**

所以可以将奶牛根据行进方向的不同分成两类

因为所有的奶牛的x，y坐标都不相同。

**意味着向北走的奶牛只会被向东走的奶牛阻挡，向东走的奶牛只会被向北走的奶牛阻挡。**

那么如何判断每头奶牛阻挡的个数呢？

观察数据范围发现：只可能从奶牛的行进方向入手（因为x,y的取值过大）。
所以我们可以将每一头奶牛的路径“画出来”。但是这样还是不能避免涉及过多坐标的问题。所以还需要精简。

考虑奶牛什么时候会停下：当且仅当方向不同且已行进路程的两头奶牛**相遇**时，才会有一头奶牛停下。所以我们可以


------------


### 维护交点

是的，只需要维护每头牛走过的线的交点即可。所以现在重点就是如何记录交点以及交点需要存储哪些信息。

首先我们要考虑哪些奶牛可以产生交点。

产生交点的条件：

1. 两头奶牛的方向不同
1. 假设向东走的奶牛为$c_e$,向北走的奶牛为$c_n$，则奶牛要相遇的条件为

$ c_e.x < c_n.x$
且
$c_e.y > c_n.y$

这个结论很好推，因为对于$c_n$，它的$x$坐标是不变的，所以如果一开始$c_e$的$x$坐标就比$c_n$大，那么很显然不能交上，$y$坐标同理

现在我们已经有了一张偌大的图，图上有若干个交点，那么我们应该维护哪些信息呢？

假设现在有一个交点$P$,由两头牛$N,E$相交得到，那么我们现在要判断哪一头牛会被挡住，**只需判断两头牛起始点距交点的距离即可**（很显然距离大的会被挡住）。

所以交点维护的信息已经一目了然：

交点坐标，由哪两条线相交而来（存储线的编号）。

但现在又有一个问题了：有的牛会被挡住，它实际上只走了一个线段，但是我们存储的仍然是一条射线。

这个问题其实很好解决，我们可以设置一个删除数组，维护每一头牛有没有被挡住，那么在交点判断时，如果有牛被挡住了，很显然这个交点是不存在的。
那么对于没有被挡住的牛，他挡住的牛的个数应该是

**他本身挡住的牛的个数 + 他挡住的另一头牛挡住的牛的个数 + 1（另一头牛本身）** 


------------


### 最后一个问题：**判断交点顺序**

相交距离越小的点越先被判断。那么哪些点的距离比较小呢？

很显然是左下角的点（因为牛是往右或者上走的）。

所以我们要对交点进行排序，以$x$坐标和$y$坐标的任意一个作为第一关键字排序,另一个作为第二关键字排序（从小到大），然后判断交点即可。


------------


接下来上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
struct cows{
	int x,y,num;
}c[1100],nth[1100],est[1100];//结构体维护奶牛的信息
//x，y为坐标，num为输入的编号（因为之后要把奶牛存到两个数组里去）
//nth数组是向北走的奶牛的集合，est是向东的 
struct point{
	int x,y;
	int numx,numy;
	bool operator < (const point others) const
	{
		if(this->x  == others.x){
			return this->y < others.y;
		}
		return this->x < others.x;
	}//重载运算符，当然写比较函数也可 
}p[1100 * 1100 /4];//交点维护坐标和相交奶牛的编号 
int n,cntn,cnte,cntp,ans[1100];
bool del[1100];//删除数组 
int main(void)
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i = 1;i <= n;i++){
		char x;
		cows tmp;
		cin>>x>>tmp.x>>tmp.y;
		tmp.num = i;
		if(x == 'N'){
			c[i] = tmp;
			nth[++cntn] = tmp;
		}
		else{
			c[i] = tmp;
			est[++cnte] = tmp;
		}
	}//输入不解释 
	for(int i = 1;i <= cntn;i++){
		for(int j = 1;j <= cnte;j++){
			if(nth[i].x > est[j].x && nth[i].y < est[j].y){
				p[++cntp].x = nth[i].x;
				p[cntp].y = est[j].y;
				p[cntp].numx = est[j].num;
				p[cntp].numy = nth[i].num;
			}//建立交点 
		}
	}
	sort(p + 1,p + 1 + cntp);
	for(int i = 1;i <= cntp;i++){
		if(del[p[i].numx] || del[p[i].numy]){
			continue;//如果有一头牛被挡住，说明交点不存在了 
		}
		int dx = p[i].x - c[p[i].numx].x;
		int dy = p[i].y - c[p[i].numy].y;//计算距离 
		if(dx < dy){
			del[p[i].numy] = 1;
			ans[p[i].numx] = ans[p[i].numx] + ans[p[i].numy] + 1;
		}
		if(dx > dy){
			del[p[i].numx] = 1;
			ans[p[i].numy] = ans[p[i].numy] + ans[p[i].numx] + 1;
		}
	}
	for(int i = 1;i <= n;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}

```
蒟蒻第一次写题解，希望能过

---

## 作者：Diaоsi (赞：11)

## 思路：

观察到坐标的数据范围很大，但数量却很少，考虑离散化。

由于每个牛子只能向东或向北走，所以阻碍关系不会构成环，会构成一个森林。

考虑模拟行走的过程。

将离散化后的坐标存进一个二维数组里，在二维数组里模拟向东或向北走，由于离散化的原因，此时走一格所花费的时间并不确定，可以使用一个堆来维护前进到下一个方格的时间+当前时间最小的牛子。

每次取出堆顶将堆顶的牛子朝它的方向前进一格，并判断前进后的牛子是否被阻碍，若当前的牛子被阻碍，记录下这头牛子是被谁阻碍的。

计算牛子前进的**下一格**的坐标，若超出地图范围则不把这个牛子放回堆里（即永远不会被阻碍）。

否则，计算前进到下一格所需要的时间，加上当前时间后塞回堆里。

这样就能正确地模拟行走的过程。

接下来将每个牛子与直接阻碍这个牛子的牛子建一条边，若这个牛子不被阻碍，那他**一定是森林中某棵树的根节点**。

建图后，对每个根节点跑一边深搜并记录以每个牛子为根的子树的大小。

答案就是以**每个牛子为根的子树的大小 $-1$**

总时间复杂度: $\mathcal{O(n^2 \log n)}$ 

既然你能找到这题，我相信你能瞬间做出来的。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=100010,M=1000010,INF=0x3f3f3f3f;
const long long dx[]={1,0};//E N
const long long dy[]={0,1};
struct node{
	char c;
	long long x,y,ti,id;
	bool operator <(const node &a)const{
		return ti>a.ti;
	}
}a[2010],e[2010],g[2010][2010];
long long head[N],ver[M],Next[M],tot;
long long T,n,m,cnt,num,size[2010],fa[2010],b[M],st[M];
priority_queue<node> q;
inline long long Max(long long x,long long y){return x>y?x:y;}
inline long long Min(long long x,long long y){return x<y?x:y;}
inline void Swap(long long &x,long long &y){x^=y^=x^=y;}
void add(long long x,long long y){
	ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
}
long long query(long long x){
	return lower_bound(b+1,b+cnt+1,x)-b;
}
void dfs(long long x,long long ffa){
	size[x]=1;
	for(long long i=head[x];i;i=Next[i]){
		long long y=ver[i];
		if(y==ffa)continue;
		dfs(y,x);
		size[x]+=size[y];
	}
}
int main(){
	scanf("%lld",&T);
	for(long long i=1;i<=T;i++){
		cin>>a[i].c;
		scanf("%lld%lld",&a[i].x,&a[i].y);
		b[++num]=a[i].x;
		b[++num]=a[i].y;
	}
	sort(b+1,b+num+1);
	cnt=unique(b+1,b+num+1)-b-1;
	for(long long i=1;i<=T;i++){
		long long x=query(a[i].x);
		long long y=query(a[i].y);
		g[x][y]=e[i]=(node){a[i].c,x,y,0,i};
		st[x]=a[i].x;st[y]=a[i].y;
		n=Max(n,x),m=Max(m,y);
	}
	for(long long i=1;i<=T;i++){
		fa[i]=i;
		long long mt;
		long long x=e[i].x;
		long long y=e[i].y;
		long long dir=(e[i].c=='E')?0:1;
		long long tx=x+dx[dir];
		long long ty=y+dy[dir];
		if(tx<1||tx>n||ty<1||ty>m)continue;
		if(dir&1)mt=st[ty]-st[y];
		else mt=st[tx]-st[x];
		q.push((node){e[i].c,x,y,mt,i});
	}
	while(q.size()){
		char c=q.top().c;
		node t=q.top();q.pop();
		long long dir=(c=='E')?0:1,mt;
		t.x+=dx[dir];
		t.y+=dy[dir];
		if(g[t.x][t.y].id&&g[t.x][t.y].ti<t.ti){
			fa[t.id]=g[t.x][t.y].id;
			continue;
		}
		g[t.x][t.y]=t;
		long long tx=t.x+dx[dir];
		long long ty=t.y+dy[dir];
		if(tx<1||tx>n||ty<1||ty>m)continue;
		if(dir&1)mt=st[ty]-st[t.y];
		else mt=st[tx]-st[t.x];
		q.push((node){t.c,t.x,t.y,t.ti+mt,t.id});
	}	
	for(long long i=1;i<=T;i++)
		if(fa[i]!=i)add(i,fa[i]),add(fa[i],i);
	for(long long i=1;i<=T;i++)
		if(fa[i]==i)dfs(i,0);
	for(long long i=1;i<=T;i++)
		printf("%lld\n",size[i]-1);
	return 0;
}
```


---

## 作者：_zy_ (赞：9)

## [题目传送门](https://www.luogu.com.cn/problem/P7150)

#### 题目大意：

有两类牛：一种向North走，一种向East走，当一条牛走到另一条牛走过的地方时，会被阻止，求每只牛阻挡了多少条牛（阻挡具有传递性）。


$Subtask1-5$ $:$

直接一步一步的走，记录i时间下$map[i][j]$已经被谁走过，当有牛再走时，就被阻挡.

$e[now].ans+=e[ map[i][j] ].ans+1;$


注意走到$2000$的时候直接跳出。

代码不予展示（~~我是不会告诉你我暴力一开始没有过$qwq$~~）

$Subtask1-10:$

只需要考虑每只牛的相对位置即可。

找到每个节点（不考虑被阻隔），然后再确定每个相交的顺序，将被阻隔的牛标记。

- 关于交点

我们需要维护出交点的坐标，以及由哪两个节点相交而来。

为了方便处理谁被拦截，我们定义$id_1$为$E$牛,$id_2$为$N$牛。

**注意考虑射线而非直线，如果在一条射线端点的另一侧，即使方向不同也没有交点。**
```cpp
for(int i=1;i<=n;i++)
for(int j=i+1;j<=n;j++)
{
	if(e[i].op==e[j].op)	continue;
	if(e[i].op&&!e[j].op&&e[i].x<e[j].x&&e[i].y>e[j].y) {
		w[++cnt].x=e[j].x;
		w[cnt].y=e[i].y;
		w[cnt].id_1=i;
		w[cnt].id_2=j;
	}
	if(!e[i].op&&e[j].op&&e[j].x<e[i].x&&e[j].y>e[i].y) {
		w[++cnt].x=e[i].x;
		w[cnt].y=e[j].y;
		w[cnt].id_1=j;
		w[cnt].id_2=i;
	}
}
```
- 关于相交的顺序

我们已经有了每个交点的横坐标和纵坐标，每只牛都是向右上走的，所以很显然每只牛是从左下角开始的相交。

**于是按照$x,y$的从小到大顺序排序即可。**

于是只需要$for$枚举每一个交点。

$e[u].ans+=e[v].ans+1;$

如果怕出错可以加$abs$

#### 代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
#include<queue>
#define N 100010
using namespace std;
int re() {
	int p=0; char i=getchar();
	while(i<'0'||i>'9')	i=getchar();
	while(i>='0'&&i<='9')	p=p*10+i-'0',i=getchar();
	return p;
}
int n;
bool used[N];
struct zy {
	int op;
	int x,y;
	int ans;
}e[N];
struct Point {
	int id_1,id_2;
	int x,y;
}w[N];
bool cmp(Point x,Point y) {
	if(x.x==y.x)
		return x.y<y.y;
	return x.x<y.x;
}
int main()
{
	n=re();
	for(int i=1;i<=n;i++) {
		char s; cin>>s;
		if(s=='E')	e[i].op=1;
		else e[i].op=0;
		e[i].x=re(); e[i].y=re();
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	{
		if(e[i].op==e[j].op)	continue;
		if(e[i].op&&!e[j].op&&e[i].x<e[j].x&&e[i].y>e[j].y)	{
			w[++cnt].x=e[j].x;
			w[cnt].y=e[i].y;
			w[cnt].id_1=i;
			w[cnt].id_2=j;
		}
		if(!e[i].op&&e[j].op&&e[j].x<e[i].x&&e[j].y>e[i].y) {
			w[++cnt].x=e[i].x;
			w[cnt].y=e[j].y;
			w[cnt].id_1=j;
			w[cnt].id_2=i;
		}	
	}
	sort(w+1,w+cnt+1,cmp);
	for(int i=1;i<=cnt;i++)
	{
		int est=w[i].id_1;
		int nor=w[i].id_2;
		if(used[est]||used[nor])	continue;
		if(abs(w[i].x-e[est].x)>abs(w[i].y-e[nor].y)) {
			used[est]=1;
			e[nor].ans+=e[est].ans+1;
		}
		if(abs(w[i].x-e[est].x)<abs(w[i].y-e[nor].y)) {
			used[nor]=1;
			e[est].ans+=e[nor].ans+1;
		}
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",e[i].ans);
	return 0;
}
```
如果不妥，请不要吝啬您的建议！



---

## 作者：wsyhb (赞：7)

## 题意简述

无限大的网格图上有 $N$ 头奶牛，第 $i$ 头奶牛的坐标为 $(x_i,y_i)$，一些奶牛朝向北面，一些奶牛朝向东面。

每一小时，若奶牛遇到了一个没有被吃过草的格子，她会吃掉当前这一格的全部草，并向前走一步；否则它会在这一格停住，不再往前走。特别地，若两头奶牛同时到达某一格子，它们会分享这个格子的草，并继续向前走。

我们称奶牛 $a$ 阻碍了奶牛 $b$ 当且仅当 $b$ 到达了一个 $a$ 已经吃过草的格子而停下，而「阻碍」关系具有传递性，即若 $a$ 阻碍了 $b$，且 $b$ 阻碍了 $c$，那么我们认为 $a$ 也阻碍了 $c$。

现在要求求出每头奶牛阻碍的奶牛数量。

**数据范围与约定**：$N \le 1000$，$0 \le x_i,y_i \le 10^9$ 且**保证 $x_i$ 和 $y_i$ 分别互不相同**。

## 分析 + 题解

PS：如果你参加了这次 USACO 的 Bronze 组，你会发现这道 Silver 的 T3 和它的 T3 背景是一模一样的，只是所求东西的不同。~~我猜大家都不会像我一样菜到去参加 Bronze 组。~~

------------

首先，考虑可能的**直接阻碍关系**。枚举第 $i$ 头牛和第 $j$ 头牛，这两头牛的路径上有交，当且仅当 $i$ 朝向东面，$j$ 朝向北面且 $x_i \le x_j$，$y_i \ge y_j$。（易知奶牛的路径是一条向上或向右的直线）

将奶牛到达交点的时间记下来，易知分别为 $x_j-x_i+1$ 和 $y_i-y_j+1$。（注意是网格图）并按其中较晚的时间为关键字进行排序，依次讨论每个阻碍关系是否真实存在。（可能会出现有奶牛在之前已经停下的情况）

具体来说，设当前先到的奶牛为 $a$，到达时间为 $t_1$，后到的奶牛为 $b$，到达时间为 $t_2$。我们按 $t_2$ 排序后，**给已停止的奶牛打上标记并记录其停止的时间**，分别记为 `mark` 和 `over_time`，然后判断 $t_1=t_2$，`mark[a]&&over_time[a]<t1` 和 `mark[b]` 三个条件是否存在某个成立，若存在，则不会出现该阻碍关系，否则 $a$ 阻碍了 $b$。

有关上述条件的说明：分别对应 $a$ 和 $b$ 同时到达而分享草，$a$ 在到达此处以前被阻碍，$b$ 在到达此处以前被阻碍。**之所以 $a$ 需要判到达时间，而 $b$ 不需要，是因为我们已按 $t_2$ 排序，但之前的 $t_1$ 可能比之后的 $t_2$ 大。**

将 $a$ 阻碍 $b$ 的关系看成一条有向边 $(a,b)$，那么这些关系会转化为若干棵树，即森林。**建反图并拓扑排序**即可。

有关森林的说明：由于一头奶牛至多会被阻碍一次，且阻碍奶牛存在先后关系，不可能出现 $a_1$ 阻碍 $a_2$，$a_2$ 阻碍 $a_3$，$\cdots$，且 $a_k$ 阻碍 $a_1$ 的情况。

------------

PS：赛时我~~脑子出了问题~~没有想到这些关系是一个森林，所以直接上了“**缩点+拓扑排序+bitset**” ，比较暴力，后文代码亦会给出。

## 代码

1. （赛时代码）缩点 + 拓扑排序 + bitset

时间复杂度：$O(\frac{n^3}{32})$

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_N=1e3+5;
int x[max_N],y[max_N];
char op[max_N][5];
const int max_cnt=1e6+5;
struct node
{
	int a,b,t1,t2;
}p[max_cnt];
bool cmp(node x,node y)
{
	return x.t2<y.t2;
}
bool mark[max_N];
int over_time[max_N];
const int max_M=1e6+5;
int End[max_M],Last[max_N],Next[max_M],e;
inline void add_edge(int x,int y)
{
	End[++e]=y;
	Next[e]=Last[x];
	Last[x]=e;
}
int dfn[max_N],low[max_N],Time;
int st[max_N],_top;
bool mark_st[max_N];
int belong[max_N],sz[max_N],scc;
void tarjan(int x)
{
	dfn[x]=low[x]=++Time;
	st[++_top]=x;
	mark_st[x]=true;
	for(int i=Last[x];i;i=Next[i])
	{
		int y=End[i];
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(mark_st[y])
			low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x])
	{
		++scc;
		do
		{
			belong[st[_top]]=scc;
			++sz[scc];
			mark_st[st[_top--]]=false;
		}while(st[_top+1]!=x);
	}
}
vector<int> edge[max_N];
bitset<max_N> flag[max_N];//bitset 大法好 
int d[max_N];
int q[max_N],_head,_tail;
int main()
{
	int N;
	scanf("%d",&N);
	for(int i=1;i<=N;++i)
		scanf("%s%d%d",op[i],x+i,y+i);
	int cnt=0;
	for(int i=1;i<=N;++i)
		for(int j=1;j<=N;++j)
		{
			if(i!=j&&op[i][0]=='E'&&op[j][0]=='N'&&x[i]<=x[j]&&y[i]>=y[j])
			{
				p[++cnt].a=i,p[cnt].b=j;
				p[cnt].t1=x[j]-x[i]+1,p[cnt].t2=y[i]-y[j]+1;
				if(p[cnt].t1>p[cnt].t2)
				{
					swap(p[cnt].a,p[cnt].b);
					swap(p[cnt].t1,p[cnt].t2);
				}
			}
		}
	sort(p+1,p+cnt+1,cmp);
	for(int i=1;i<=cnt;++i)
	{
		if((mark[p[i].a]&&over_time[p[i].a]<p[i].t1)||mark[p[i].b]||p[i].t1==p[i].t2)
			continue;
		mark[p[i].b]=true;
		over_time[p[i].b]=p[i].t2;
		add_edge(p[i].a,p[i].b);//建边 
	}
	for(int i=1;i<=N;++i)
	{
		if(!dfn[i])
			tarjan(i);//缩点 
	}
	for(int x=1;x<=N;++x)
		for(int i=Last[x];i;i=Next[i])
		{
			int y=End[i];
			if(belong[x]!=belong[y])
			{
				edge[belong[x]].push_back(belong[y]);//建新边 
				++d[belong[y]];
			}
		}
	for(int i=1;i<=scc;++i)
		flag[i][i]=true;
	_head=1,_tail=0;
	for(int i=1;i<=scc;++i)
	{
		if(!d[i])
			q[++_tail]=i;
	}
	while(_head<=_tail)//拓扑排序 
	{
		int x=q[_head++];
		for(int i=0;i<int(edge[x].size());++i)
		{
			int y=edge[x][i];
			flag[y]|=flag[x];
			--d[y];
			if(!d[y])
				q[++_tail]=y;
		}
	}
	for(int i=1;i<=N;++i)//统计答案 
	{
		int ans=0;
		int now=belong[i];
		for(int j=1;j<=scc;++j)
		{
			if(flag[j][now])
				ans+=sz[j];
		}
		printf("%d\n",ans-1); 
	}
	return 0;
}
```

2. （赛后代码）建反图拓扑排序

时间复杂度：$O(n^2)$

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_N=1e3+5;
int x[max_N],y[max_N];
char op[max_N][5];
const int max_cnt=1e6+5;
struct node
{
	int a,b,t1,t2;
}p[max_cnt];
bool cmp(node x,node y)//按较晚时间排序 
{
	return x.t2<y.t2;
}
bool mark[max_N];
int over_time[max_N];//记录奶牛被阻碍的信息 
const int max_M=1e6+5;
int End[max_M],Last[max_N],Next[max_M],e;
int d[max_N];
inline void add_edge(int x,int y)//链式前向星建边 
{
	End[++e]=y;
	Next[e]=Last[x];
	Last[x]=e;
	++d[y];
}
int q[max_N],_head,_tail;//手工队列 
int ans[max_N];//记录答案 
int main()
{
	int N;
	scanf("%d",&N);
	for(int i=1;i<=N;++i)
		scanf("%s%d%d",op[i],x+i,y+i);
	int cnt=0;
	for(int i=1;i<=N;++i)
		for(int j=1;j<=N;++j)
		{
			if(i!=j&&op[i][0]=='E'&&op[j][0]=='N'&&x[i]<=x[j]&&y[i]>=y[j])//上文中提到的条件 
			{
				p[++cnt].a=i,p[cnt].b=j;
				p[cnt].t1=x[j]-x[i]+1,p[cnt].t2=y[i]-y[j]+1;
				if(p[cnt].t1>p[cnt].t2)//要求 t1<t2，交换 
				{
					swap(p[cnt].a,p[cnt].b);
					swap(p[cnt].t1,p[cnt].t2);
				}
			}
		}
	sort(p+1,p+cnt+1,cmp);
	for(int i=1;i<=cnt;++i)
	{
		if((mark[p[i].a]&&over_time[p[i].a]<p[i].t1)||mark[p[i].b]||p[i].t1==p[i].t2)//上文中提到的条件 
			continue;
		mark[p[i].b]=true;
		over_time[p[i].b]=p[i].t2;//别忘了记录 
		add_edge(p[i].b,p[i].a);//建反边 
	}
	_head=1,_tail=0;
	for(int i=1;i<=N;++i)
	{
		if(!d[i])
			q[++_tail]=i;
	}
	while(_head<=_tail)//拓扑排序 
	{
		int x=q[_head++];
		++ans[x];
		for(int i=Last[x];i;i=Next[i])
		{
			int y=End[i];
			ans[y]+=ans[x];
			--d[y];
			if(!d[y])
				q[++_tail]=y;
		}
	}
	for(int i=1;i<=N;++i)
		printf("%d\n",ans[i]-1);//注意被阻碍的奶牛不包括自己，所以应减去 1 
	return 0;
}
```

---

## 作者：tuxuanming2024 (赞：6)

# 贪心+并查集

思路：

把所有奶牛按方向分类，分别装在两个结构体里，然后给他们排序，朝南的按 $ y $ 坐标排序，朝北的按 $ x $ 排序。因为只有方向不同的奶牛才可能相撞，于是我们可以两重循环枚举，判断他们会不会相撞，如果相撞，就用并查集合并。

如何判断他们是否会相撞？

假设设一个朝北的奶牛为 $ a $ ， 朝南的奶牛为 $ b $ ， 那么他们相撞肯定是有如下的条件：

$$ a.x \leq b.x $$
$$ a.y \geq b.y $$
$$ a.x+a.y \neq b.x+b.y $$

然后分别判断是哪个奶牛撞上哪个，依次合并即可。

code:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct point {int x,y,num;}a[1005],b[1005];
int n,cnt,cnt1,cnt2,s[1005],ans[1005],prt[1005];
bool flag[1005],bj[1005];
int getfather(int x) {return prt[x]==x?x:prt[x]=getfather(prt[x]);}
void Union(int x,int y)
{
	int f1=getfather(x),f2=getfather(y);
	if(f1!=f2)
	{
		prt[f1]=f2;
		ans[f2]+=ans[f1]+1;
	}
}
bool cmp1(point x,point y)
{
	if(x.y==y.y) return x.x<y.x;
	return x.y<y.y;
}
bool cmp2(point x,point y)
{
	if(x.x==y.x) return x.y<y.y;
	return x.x<y.x;
}
int main()
{
	scanf("%d",&n);
	char ch;
	int x,y;
	for(int i=1;i<=n;i++)
	{
		cin>>ch;
		scanf("%d %d",&x,&y);
		if(ch=='E') a[++cnt1].x=x,a[cnt1].y=y,a[cnt1].num=i;
		else b[++cnt2].x=x,b[cnt2].y=y,b[cnt2].num=i;
		prt[i]=i;
	}
	sort(a+1,a+1+cnt1,cmp1);
	sort(b+1,b+1+cnt2,cmp2);
	for(int i=1;i<=cnt1;i++)
		for(int j=1;j<=cnt2;j++)
		{
			if(flag[j]||a[i].x>b[j].x||a[i].y<b[j].y||a[i].x+a[i].y==b[j].x+b[j].y) continue;
			if(b[j].x-a[i].x>a[i].y-b[j].y)
			{
				bj[a[i].num]=1;
				Union(a[i].num,b[j].num);
				break;
			}
			else
			{
				bj[b[j].num]=1;
				Union(b[j].num,a[i].num);
				flag[j]=1;
			}
		}
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：Skies (赞：3)

~~本题解比较良心~~


### 这道题中因为牛都处于不同的x轴和y轴，牛只会因方向不同的牛停下。

所以让我们分别存储横纵方向的牛，让我们更方便查找交点。

让我们先看一下不同方向的牛可能出现的情况：

#### 1.竖着走的牛在横着起始点的左侧则必定不相交

![](https://cdn.luogu.com.cn/upload/image_hosting/nzwg9oz9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

#### 2.横着走的牛在竖着起始点的下方则必定不相交

![](https://cdn.luogu.com.cn/upload/image_hosting/fdx21lv0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

#### 3.两只牛离交点位置相同无需处理

![](https://cdn.luogu.com.cn/upload/image_hosting/3pkgbs35.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

此外，我们需要明晰

#### 右边的牛可能会被左边的一系列阻拦而影响，而左下角的交点一定是不会被影响的。所以我们找交点时需要排序从左下到右上（既可以以左为第一关键词，亦可以以下为第一关键词）。

然而，我们可以发现如果直接对于整个交点进行排序，复杂度会达到

$$ O(n²logn²) $$


所以我们可以运用一些方法避免这个更大的复杂度，先排序横着的线于竖着的线，从而使得枚举所有交点时所有点已经自动排好序了。

## 排序核心代码:
```cpp
bool cmp(heng p, heng q){	//横着的以y从下至上排序 
	if(p.y < q.y)	return 1;
	if(p.y > q.y)	return 0;
	return p.x < q.x;
}

bool cmq(zong p, zong q){	//竖着的以x从左至右排序 
	if(p.x < q.x)	return 1;
	if(p.x > q.x)	return 0;
	return p.y < q.y;
}

sort(a+1, a+numh+1, cmp);	//排序横着的牛 
sort(b+1, b+numz+1, cmq);	//排序纵着的牛 
```


另外，对于枚举交点确定谁影响谁时，我们定下一个标记表示他有没有被阻拦，若被阻拦则可跳过枚举。

```cpp
for(int i = 1; i <= num; i++){			//枚举所有交点 
	int p = w[i].num1, q = w[i].num2;	//p,q代表横纵牛编号 
	if(a[p].useful == 1 || b[q].useful == 1)	continue;	//若交点不可能则跳过 
	//内容//
}
```
### 代码里也有注释，辅助观看。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, x, y, numh, numz, num;//x, y方便输入,numh表示延坐标x轴走的牛，numz表示延坐标y轴走的牛 
int ans[1005], fa[1005];//ans[i]表示挡i这头牛路的牛,fa为该牛总共挡了多少头牛 
char c;

inline int read(){	// *************************************************读快写 
	int X = 0, w = 0;
	char ch = 0;
	while(!isdigit(ch)){
		w |= ch =='-', ch = getchar();
	}
	while(isdigit(ch))
		X = (X<<3) + (X<<1)+(ch^48), ch = getchar();
	return w?-X:X;
}

inline void write(int x){
	if(x < 0)	putchar('-'), x = -x;
	if(x > 9)	write(x/10);
	putchar(x % 10+'0');
}

struct heng{	//保存所有横着的牛的信息 
	int x, y;	//x为横坐标,y为纵坐标 
	bool useful;//记录有没有可能影响他牛     
	int ans;	//记录最终答案  
	int num;
}a[1005];                        

struct zong{	//保存所有竖着的牛的信息 
	int x, y;
	bool useful;
	int ans;
	int num;
}b[1005];    

struct node{	//保存可能出现的交点的信息 
	int x, y;	//交点 
	int num1, num2;	//表示哪两只牛交于此点，num1为横着的，num2为竖着的 
}w[250005];

bool cmp(heng p, heng q){	//横着的以y从下至上排序 
	if(p.y < q.y)	return 1;
	if(p.y > q.y)	return 0;
	return p.x < q.x;
}

bool cmq(zong p, zong q){	//竖着的以x从左至右排序 
	if(p.x < q.x)	return 1;
	if(p.x > q.x)	return 0;
	return p.y < q.y;
}

int main(){
	n = read();
	for(int i = 1; i <= n; i++){
		cin >> c;
		x = read(), y = read();
		if(c == 'E'){			//若为横着走的，保存至横着的结构体 
			numh++;
			a[numh].x = x;
			a[numh].y = y;
			a[numh].num = i;
		}
		if(c == 'N'){			//如上 
			numz++;
			b[numz].x = x;
			b[numz].y = y;
			b[numz].num = i;
		}
	}
	sort(a+1, a+numh+1, cmp);	//排序横着的牛 
	sort(b+1, b+numz+1, cmq);	//排序纵着的牛 
	//这两个sort可保证交点一定是从左下到右上的,使无需排序交点(复杂度O(n*n*logn*n)),而复杂度改为O(n*n) 
	for(int i = 1; i <= numh; i++){
		for(int j = 1; j <= numz; j++){		//枚举横纵的牛，找到每一个交点 
			if(a[i].useful == 1 || b[j].useful == 1)	continue;	//若不可能相遇跳过 
			if(a[i].y < b[j].y)	continue;		//若横着走的牛在竖着走的牛的下方，则一定不相遇跳过 
			if(a[i].x > b[j].x)	continue;		//同理，若竖着走的牛在横着走的牛的左侧则一定不相遇跳过 
			if(a[i].y - b[j].y == b[j].x - a[i].x)	continue;	//若到相遇点距离相等则不影响跳过 
			num++;		//可能储存交点 
			w[num].y = a[i].y;
			w[num].x = b[j].x;
			w[num].num1 = i;
			w[num].num2 = j;
		}
	}
	for(int i = 1; i <= num; i++){			//枚举所有交点 
		int p = w[i].num1, q = w[i].num2;	//p,q代表横纵牛编号 
		if(a[p].useful == 1 || b[q].useful == 1)	continue;	//若交点不可能则跳过 
		if(w[i].y - b[q].y > w[i].x - a[p].x){	//若横着的会使竖着的停下 
			b[q].useful = 1;					//竖着的无法影响他人 
			fa[b[q].num] = a[p].num;			//a[p].num是b[q].num停下的因素		
		}
		if(w[i].y - b[q].y < w[i].x - a[p].x){	//若竖着的会使横着的停下 
			a[p].useful = 1;
			fa[a[p].num] = b[q].num;
		}
	}
	for(int i = 1; i <= n; i++){				//找能影响他停下的牛 
		int k = i;
		while(fa[k] != 0){
			ans[fa[k]]++;
			k = fa[k];
		}
	}
	for(int i = 1; i <= n; i++)					//输出 
		cout << ans[i] << endl;
	return 0;
}
```
~~管理员小哥哥求过审！~~

---

## 作者：C1R1A1E1F1 (赞：2)

~~这题能和铜组第三题类似也是醉了~~

### PART1：分析题意

首先我们很容易发现一个事：奶牛们走过的轨迹必然是一条与 $x$ 轴或 $y$ 轴平行的直线，具体哪个取决于方向。

那么我们就可以把朝向北方的牛和朝向东方的牛分开讨论，如果这头牛朝向北方，就把它放到朝东方的牛中枚举，看看它会被哪头牛阻拦，反之同理。

### PART2：具体思路

那么我们现在就可以考虑如下两个问题：

1. 在什么情况下牛A与牛B会相遇（设牛A朝向东，牛B朝向北）？
2. 如果它们相遇，它们会在什么地方相遇？

这里我们会发现因为奶牛的路径只是两条平行于坐标轴的射线 $x=A_x$ 和 $y=B_y$ 所以说这两条路径的交点必然为 $(A_x,B_y)$ 这个点，所以说我们必须要满足$A_x \leq B_x$ 且 $B_y \leq A_y$ 这就是我们判定两点是否相交的判别式。

### PART3：维护方法

这题很明显是让我们计算那头牛被哪头牛阻拦，从而我们可以对朝北的牛进行枚举，并利用朝东的牛进行更新。

具体想法如下：

对于向东的被枚举的牛A和向北的被研究的牛B，有3种可能：

1. 如果两牛不满足上述判别式，跳过牛A。
1. 如果两牛满足上述判别式，且有牛A到达点的时间 $t_A < t_B$ ，则用牛A阻拦牛B。
1. 如果两牛满足上述判别式，且有牛A到达点的时间 $t_A > t_B$ ，则用牛B阻拦牛A。

很明显，这里面 $t_A=B_x-A_x,t_B=A_y-B_y$ 。

### PART4：具体细节

首先我们可以很容易的发现假如说有 $k$ 头向东的牛可以阻拦向北的牛A，那么这 $k$ 头牛中 $y$ 坐标最小的就是答案。（对向东的牛同理）

于是我们可以对向北的牛按 $x$ 坐标排序，对向东的牛按 $y$ 坐标排序，从而满足收个枚举到的值就是答案。

同时因为阻拦具有传递性，所以我们可以用类似于树的形式存储，再统计子树大小即可。

**时间复杂度 $O(n^2)$**

### PART5：代码

```
#include <bits/stdc++.h>
using namespace std;
int n,cnt[1005],s1,s2,vit[1005],used[1005];
struct it
{
	int x,y,id;
	char c;
}cow[1005],nc[1005],ec[1005];
vector<int>mp[1005];//存树图
bool cmy(it a,it b)//对向东牛的排序
{
	return a.y<b.y;
}
bool cmx(it a,it b)//对向北牛的排序
{
	return a.x<b.x;
}
void add(int x)//深搜统计子树
{
	vit[x]=1;
	for(int i=0;i<mp[x].size();i++)
	{
		add(mp[x][i]);
		cnt[x]+=cnt[mp[x][i]]+1;
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>cow[i].c>>cow[i].x>>cow[i].y,cow[i].id=i;
	for(int i=1;i<=n;i++)
		if(cow[i].c=='N')//分开处理向北牛和向东牛
			s1++,nc[s1]=cow[i];
		else
			s2++,ec[s2]=cow[i];
	sort(nc+1,nc+1+s1,cmx);
	sort(ec+1,ec+1+s2,cmy);//排序
	for(int i=1;i<=s1;i++)
		for(int j=1;j<=s2;j++)
			if(used[ec[j].id]==0&&ec[j].x<=nc[i].x&&ec[j].y>=nc[i].y)//情况1
				if(abs(nc[i].y-ec[j].y)<abs(nc[i].x-ec[j].x))//情况3
					mp[nc[i].id].push_back(ec[j].id),used[ec[j].id]=1;
				else
					if(abs(nc[i].y-ec[j].y)>abs(nc[i].x-ec[j].x))//情况2
					{
						mp[ec[j].id].push_back(nc[i].id);
						used[nc[i].id]=1;
						break;//很明显在它被阻拦后就不能再阻拦其它牛了
					}
	for(int i=1;i<=n;i++)
		if(used[i]==0)//最终统计
			add(i);
	for(int i=1;i<=n;i++)
		cout<<cnt[i]<<endl;
}
```


---

## 作者：Paris_Bentley (赞：1)

这个是USACO 2020 - 2021 赛季银组别的第三题，题目是铜组别最后一题的进阶，所以我是在之前的代码上进行修改了的。

每头牛有 N 和 E 两个方向，我们可以先用数学方法，把每一头面向 N 和面向 E 的牛记录未来会和哪头牛相遇，（把所有和 i 号牛相遇的牛都放入 vec[i] ）

再依次按照相遇的时间点遍历所有的相遇，相遇后，就保存 zb 。还有很多细节比如 1 号牛和 4 号牛已经相遇停下了。但是我发现之后的 3 号牛也因为 1 号牛停下了，这样就跳过 3 ，在比较下一个vec中的元素，如果有元素，就责备它，没有元素就跳过。


重点来了，这个题目要求是，比如 3 因为 4 停下，而 4 因为 5 停下，那么 5 又要被责备， 这里就可以用 dfs 递归下去，一直到某头牛责备自己为止。

详细的大家可以看代码，有标注哦。
```
#include <bits/stdc++.h>
using namespace std;
int n,a[1005],b[1005],ans[1005],zb[1005],bzb[1005];
char c[1005];
bool used[1005];
struct node
{
	int n,m,p;//阻挡的牛编号n，n号牛阻挡我的时间m，n号牛在p时刻阻挡我（判断能不能活到m） 
};
vector<node> vec[1005];
bool cmp(node x,node y)
{
	return x.m<y.m;
}
bool check()
{
	bool res=false;
	for (register int i=1;i<=n;i++)
	{
		if (used[i])
			continue;
		while(vec[i].size()&&(used[vec[i].front().n]==true&&vec[i].front().p>ans[vec[i].front().n]))
			vec[i].erase(vec[i].begin());
		if (vec[i].size())
			res=true;
	}
	return res;
}
void dfs(int x)//递归找到最后的牛。 
{
	if (x==zb[x])
		return;
	else
	{
		bzb[zb[x]]++;
		dfs(zb[x]);
	}
}
int main()
{
	scanf("%d",&n);
	for (register int i=1;i<=n;i++) 
	{
		cin>>c[i];//读入牛的方向 
		zb[i]=i;//初始每头牛都责备自己 
		scanf("%d%d",&a[i],&b[i]);//坐标点 
	}
	for (register int i=1;i<=n;i++)
	{
		if (c[i]=='N') 	continue;//对E方向的牛找 
		for (int j=1;j<=n;j++)
		{
			if(c[j]=='E')	continue;
			if (a[j]-a[i]>=0&&b[i]-b[j]>=0&&a[j]-a[i]>b[i]-b[j])  //前两个条件判断未来会相遇，后一个条件判断先到相遇点 
				vec[i].push_back({j,a[j]-a[i],b[i]-b[j]}); 
		}
		sort(vec[i].begin(),vec[i].end(),cmp);//按照相遇的先后顺序排 
	}
	for (register int i=1;i<=n;i++)
	{
		if (c[i]=='E') 	continue;
		for (int j=1;j<=n;j++)
		{
			if(c[j]=='N')	continue;
			if (b[j]-b[i]>=0&&a[i]-a[j]>=0&&b[j]-b[i]>a[i]-a[j])
				vec[i].push_back({j,b[j]-b[i],a[i]-a[j]}); 
		}
		sort(vec[i].begin(),vec[i].end(),cmp);
	}
	int minn=0x7fffffff,pos=0,stop=0;
	while(check())
	{
		for (int i=1;i<=n;i++)
		{
			if(used[i]) continue;
			if (vec[i].size()&&minn>vec[i].front().m)
			{
				pos=i;//下一个停下的是pos
				stop=vec[i].front().n;//因为谁停下; 
				minn=vec[i].front().m;
			}
		}
		ans[pos]=minn;
		zb[pos]=stop;
		used[pos]=true;
		minn=0x7fffffff;
	}
	
	for (int i=1;i<=n;i++)
	{
//		cout<<zb[i]<<endl;
		dfs(i);
	}
	for (int i=1;i<=n;i++)
		cout<<bzb[i]<<endl;
	return 0;
} 
```


---

## 作者：羚羊WANG (赞：1)

[题目传输门](https://www.luogu.com.cn/problem/P7150)

首先，不知道大家有没有看懂题目。但是，我相信，如果你看到这里，那你一定看懂了题目。

显然，题目就是一群奶牛正在进行~~运动~~，然后有些奶牛会被其它奶牛阻挡，阻挡存在传递性，最后问每头奶牛阻挡了多少头奶牛。、

每头奶牛只会被一头奶牛阻拦，所以，我们可以在最开始的时候判断出可能相交的奶牛，然后把他们按照时间排序。

当有奶牛被其它奶牛提前阻拦的时候，我们就可以打上标记，并传递答案，最后，再按照$n$行输出即可

代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
struct cow{
	int x,y;
	int num;
}c[1100],N[1100],E[1100];
struct node{
	int x,y;
	int numx,numy;
	bool operator < (const node h) const{
		if(this->x == h.x)
			return this->y<h.y;
		return this->x<h.x;
	}
}p[1100*1100];
int n;
int cntn;
int cnte;
int cntp;
int ans[1100];
int vis[1100];
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		{
			char x;
			cow tmp;
			cin>>x;
			tmp.x=read();
			tmp.y=read();
			tmp.num=i;
			if(x=='N')
				{
					c[i]=tmp;
					cntn++;
					N[cntn]=tmp;
				}
			else
				{
					c[i]=tmp;
					cnte++;
					E[cnte]=tmp;
				}
		}
	for(register int i=1;i<=cntn;++i)
		for(register int j=1;j<=cnte;++j)
			{
				if(N[i].x>E[j].x && N[i].y<E[j].y)
					{
						cntp++;
						p[cntp].x=N[i].x;
						p[cntp].y=E[j].y;
						p[cntp].numx=E[j].num;
						p[cntp].numy=N[i].num;
					}
			}
	sort(p+1,p+cntp+1);
	for(register int i=1;i<=cntp;++i)
		{
			if(vis[p[i].numx] || vis[p[i].numy])
				continue;
			int nx,ny;
			nx=p[i].x-c[p[i].numx].x;
			ny=p[i].y-c[p[i].numy].y;
			if(nx<ny)
				{
					vis[p[i].numy]=1;
					ans[p[i].numx]=ans[p[i].numx]+ans[p[i].numy]+1;
				}
			if(nx>ny)
				{
					vis[p[i].numx]=1;
					ans[p[i].numy]=ans[p[i].numx]+ans[p[i].numy]+1;
				}
		}
	for(register int i=1;i<=n;++i)
		{
			write(ans[i]);
			puts("");
		}
	return 0;
}
```


---

## 作者：xiaojuruo (赞：0)

## 思路
题目中指出 $ x \leq 10^9 $ 和 $ y \leq 10^9 $ ， 所以，我们是不能用一个二维数组来存储他们的位置的，当我们不妨用结构体来记录他们的坐标和编号。然后定义两结构体数组，分别记录两个方向，最后在一一比较，判断是否冲突即可。
## 实现 
我们实现这个方法有两个难点，一个是我们怎么判断是否冲突，另一个就是我们怎么判断谁先到达，让对方责备的。我们先来解决第一个问题，我们怎么判断冲突。
![](https://cdn.luogu.com.cn/upload/image_hosting/24xf9j5v.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图，这样的情况是不会碰撞的。发现了吗,如果向上的 $ x $ 坐标小于向右的 $ x $ 坐标，或者向上的 $ y $ 大于向右的 $ y $ 坐标，那么他们就不会冲突。所以，我们只需要判断一下他们坐标即可。接着，我们再来解决第二个问题，他们谁先冲突，其实很简单，他们如果冲突，那么他们必交与一点，所以只需要比较他们谁离这个点更近即可，比较他们的 $ x,y $ 即可。
## Code
```cpp
 #include<bits/stdc++.h>
using namespace std;
struct node{ 
	int x,y,id;
}n[10001],e[10001];
char c;
int n_i,e_i,stop[10001],sit[10001],num,answer[10001],a_1,b_1;
bool cmp(node a,node b){
	return a.y<b.y;
}
bool cmb(node a,node b){
	return a.x<b.x;
}
char c_1;
int main(){
	scanf("%d",&num);
	for(int i=1;i<=num;i++){
		cin>>c_1>>a_1>>b_1;
		if(c_1=='E') {
			e_i++;
			e[e_i].x=a_1,e[e_i].y=b_1,e[e_i].id=i;
		}
		else {
			n_i++;
			n[n_i].x=a_1,n[n_i].y=b_1,n[n_i].id=i;
		}
	}
	sort(n+1,n+n_i+1,cmb);//坐标轴越小的越可能碰撞，所以我们进行一个排序。 
	sort(e+1,e+e_i+1,cmp);
	for(int i=1;i<=e_i;i++)
		for(int j=1;j<=n_i;j++){
			if(!stop[n[j].id]&&!stop[e[i].id]&&n[j].y<e[i].y&&n[j].x>e[i].x){
				if(n[j].x-e[i].x>e[i].y-n[j].y){ //向上的让向右的辱骂 
					stop[e[i].id]=1;
					answer[n[j].id]+=1+answer[e[i].id];
				}
				else if(n[j].x-e[i].x<e[i].y-n[j].y){//向右的让向上的辱骂 
					stop[n[j].id]=1;
					answer[e[i].id]+=1+answer[n[j].id];
				}
			}
		}
		for(int i=1;i<=num;i++){
			cout<<answer[i]<<endl;
		}
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15730287.html)

良心模拟题！！！

# 题目大意

无限大的网格图上有 $N$ 头奶牛，第 $i$ 头奶牛的坐标为 $(x_i,y_i)$，一些奶牛朝向北面，一些奶牛朝向东面。

每一小时，若奶牛遇到了一个没有被吃过草的格子，她会吃掉当前这一格的全部草，并向前走一步；否则它会在这一格停住，不再往前走。特别地，若两头奶牛同时到达某一格子，它们会分享这个格子的草，并继续向前走。

我们称奶牛 $a$ 阻碍了奶牛 $b$ 当且仅当 $b$ 到达了一个 $a$ 已经吃过草的格子而停下，而「阻碍」关系具有传递性，即若 $a$ 阻碍了 $b$，且 $b$ 阻碍了 $c$，那么我们认为 $a$ 也阻碍了 $c$。

现在要求求出每头奶牛阻碍的奶牛数量。

# 题目分析

牛 $a$ 会遇到牛 $b$ 走过的方格，有两种情况：

+ $way[a]=N,way[b]=E,x[a]>x[b],y[a]<y[b]$。

+ $way[a]=E,way[b]=N,x[a]<x[b],y[a]>y[b]$。

于是我们将所有满足条件的 $a,b$ 放到结构体 $tmp$ 中。

在 $tmp$ 中，我们存储了所有奶牛的交点：

$id1,id2$ 分别存满足条件的 $\verb!East!$ 奶牛和 $\verb!North!$ 奶牛的下标；

$x,y$ 则表示交点坐标。

随后将这些交点从左往右排序。

最后，再遍历依次数组得到答案。

具体地：

（下面记向东方走的奶牛为东方奶牛，向北方走的奶牛为北方奶牛）

若 $|tmp[i].x-x[east]|>|tmp[i].y-y[north]|$，代表交点距离北方奶牛的距离更近一些，于是将 $ans[north]$ 加上 $ans[east]+1$。

另一种离东方奶牛的距离更近的情况同理。

----
时间复杂度 $\mathcal{O}(n^2)$。

# 代码

```cpp
const int ma=1005;

struct Node
{
	char opt;
	
	int x,y;
	
	int ans;
};

Node node[ma];

struct Answer
{
	int id1,id2;//id1 存 East,id2 存 North 
	
	int x,y;
};

Answer tmp[ma*ma];

bool vis[ma];

int n;

int idx;

inline bool cmp(Answer x,Answer y)
{
	if(x.x!=y.x)
	{
		return x.x<y.x;
	}
	
	return x.y<y.y;
}

inline int Abs(int x)
{
	return x>0?x:-x;
}

int main(void)
{
	speed_up();
	
	n=read();
	
	for(register int i=1;i<=n;i++)
	{
		cin>>node[i].opt;
		
		node[i].x=read(),node[i].y=read();
	}
	
	for(register int i=1;i<=n;i++)
	{
		for(register int j=i+1;j<=n;j++)
		{
			if(node[i].opt=='E' && node[j].opt=='N' && node[i].x<node[j].x && node[i].y>node[j].y)
			{
				tmp[++idx].x=node[j].x,tmp[idx].y=node[i].y;
				
				tmp[idx].id1=i,tmp[idx].id2=j;
			}
			
			else if(node[i].opt=='N' && node[j].opt=='E' && node[i].x>node[j].x && node[i].y<node[j].y)
			{
				tmp[++idx].x=node[i].x,tmp[idx].y=node[j].y;
				
				tmp[idx].id1=j,tmp[idx].id2=i;
			}
		}
	}
	
	sort(tmp+1,tmp+idx+1,cmp);
	
//	for(register int i=1;i<=idx;i++)
//	{
//		printf("%d %d %d %d\n",tmp[i].id1,tmp[i].id2,tmp[i].x,tmp[i].y);
//	}
	
	for(register int i=1;i<=idx;i++)
	{
		int east=tmp[i].id1,north=tmp[i].id2;
		
		if(vis[east]==false && vis[north]==false)
		{
			if(Abs(tmp[i].x-node[east].x)>Abs(tmp[i].y-node[north].y))
			{
				vis[east]=true;
				
				node[north].ans+=node[east].ans+1;	
			}
			
			else if(Abs(tmp[i].x-node[east].x)<Abs(tmp[i].y-node[north].y))
			{
				vis[north]=true;
				
				node[east].ans+=node[north].ans+1;
			}
		}
	}
	
	for(register int i=1;i<=n;i++)
	{
		printf("%d\n",node[i].ans);
	}
	
	return 0;
}
```

---

## 作者：45dino (赞：0)

一个比较显然的题目

先将```N```和```E```分类，预处理停止时的情况，可以用数组记录每一头牛应该责备那一头牛，注意，如果一头牛被挡住了，就不能继续下去。

显然，枚举时要有顺序，在这里，我将向东走的牛以y为关键字递增排序，将向北走的牛以x为关键字递增排序（想一想，为什么）
```cpp
struct node{
	int x,y;
} cw[1001];
int n,stck[1001],res[1001],rudu[1001];
vector<int> A,B;
queue<int> q;
bool cmp1(int x,int y)
{
	return cw[x].x<cw[y].x;
}
bool cmp2(int x,int y)
{
	return cw[x].y<cw[y].y;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		char ch=getchar();
		cw[i].x=read();
		cw[i].y=read();
		if(ch=='E')
			A.push_back(i);
		else
			B.push_back(i); 
	}
	sort(B.begin(),B.end(),cmp1);
	sort(A.begin(),A.end(),cmp2);
	for(int i=0;i<A.size();i++)
	{
		for(int l=0;l<B.size();l++)
			if(!stck[B[l]])
				if(cw[B[l]].y<cw[A[i]].y&&cw[B[l]].x>cw[A[i]].x)
				{
					if(cw[A[i]].y-cw[B[l]].y>cw[B[l]].x-cw[A[i]].x)
					{
						stck[B[l]]=A[i];
						res[A[i]]++;
						rudu[A[i]]++;
					}
					if(cw[A[i]].y-cw[B[l]].y<cw[B[l]].x-cw[A[i]].x)
					{
						stck[A[i]]=B[l];
						res[B[l]]++;
						rudu[B[l]]++;
						break;
					}
				}
	}
}
```

然后再拓扑排序即可，就不写了（

---

