# 【模板】ST 表 && RMQ 问题

## 题目背景

这是一道 ST 表经典题——静态区间最大值

**请注意最大数据时限只有 0.8s，数据强度不低，请务必保证你的每次查询复杂度为 $O(1)$。若使用更高时间复杂度算法不保证能通过。**

如果您认为您的代码时间复杂度正确但是 TLE，可以尝试使用快速读入：

```cpp
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
```

函数返回值为读入的第一个整数。

**快速读入作用仅为加快读入，并非强制使用。**

## 题目描述

给定一个长度为 $N$ 的数列，和 $ M $ 次询问，求出每一次询问的区间内数字的最大值。


## 说明/提示

对于 $30\%$ 的数据，满足 $1\le N,M\le 10$。

对于 $70\%$ 的数据，满足 $1\le N,M\le {10}^5$。

对于 $100\%$ 的数据，满足 $1\le N\le {10}^5$，$1\le M\le 2\times{10}^6$，$a_i\in[0,{10}^9]$，$1\le l_i\le r_i\le N$。

## 样例 #1

### 输入

```
8 8
9 3 1 7 5 6 0 8
1 6
1 5
2 7
2 6
1 8
4 8
3 7
1 8```

### 输出

```
9
9
7
7
9
8
7
9```

# 题解

## 作者：天泽龟 (赞：787)

### 翻了很多题解没找到一篇详细图解，于是就有了这篇。
$ST$表还是很需要一篇带图解的题解吧，
定义啥的其他题解都有，就不赘述了，我们直接结合图例来理解代码。

- ## 预处理阶段。

1. 首先你应该知道的是，ST表是利用倍增思想来缩短时间的。而倍增就体现在他数组的定义中：对于$f[i][j]$，指的是在序列的第i项，**向后$2^j$个元素所包含序列间的最大值**。

对于$i=1$，我们可以画出这么一个图，其下标即为$j$：
![](https://cdn.luogu.com.cn/upload/image_hosting/digxpwj5.png)

那么对于当前$i$转移其实很明显了，我们可以直接考虑将两个小区间的答案合并，即为这个大区间的值；如图中$f[1][2]$即可由$max(f[1][1],f[3][1])$转移来。

$$f[i][j]=max(f[i][j-1],f[i+2^{j-1}][j-1])$$

**其中$2^{j-1}$也可写为$(1<<(j-1))$**，这里位运算会更方便也会更快。

这个式子告诉我们，ST表类似于区间DP，是由两个小区间合并上来的。**所以应该先枚举区间长度l（这里即为$j$），再枚举$i$.**

2. 然后一个问题应运而生了：我们这个转移方程有没有**边界**呢？

不妨来看一下$i=6$的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/75ybmzf5.png)

可以看出在$i=6$时，$j=3$的范围是$[6,13(6+2^3)]$，已经超出了我们数据的范畴。所以当$j=3$时，$i$只能取到$[1,5(12-2^3+1)]$

**由上例再根据转移方程，不难看出当$j$确定时，i的范围受限在$[1,n-2^j+1]$。**


那么又根据$i=1$的情况，可知$j$应满足:
 
 $2^j\leq n \Leftrightarrow  j\leq lg[n] $，其中$lg[n]$表示n关于底数2的对数向下取整，可以递推求得。

最终附上预处理代码：
```cpp
	scanf("%d%d",&n,&m); lg[1]=0;
	for (int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
    //求lg[i]函数。
	for (int i=1;i<=n;i++) scanf("%d",&f[i][0]);
	for (int j=1;j<=lg[n];j++)
	for (int i=1;i<=n-(1<<j)+1;i++){ //注意两个边界
		f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	}	

```

时间复杂度为$O(N·logN)$

---

- ## 求最值阶段。

我们现在来求红色标记区间$[L,R]$的最值。如果要最大化利用ST表，仍应该考虑类似处理ST表的方法，**将该区间分成 两个ST表可直接维护的小区间，然后二者求最值即可。**

- 那对于起始点，我们找一段**ST表在该区间内可覆盖的，最大的子区间**，由数学语言可描述为：

$(L+2^k-1<=R) \Leftrightarrow (k<=lg[R-L+1])$ 那我们直接取等,令$j=k$即可~

于是对于起始点点在ST表里的取值即为：$f[L][k]$


- 对于终止点，我们**反向**找一个与起始点要求相同的子区间，由于对称性，此时k仍为起始点求得的$k=lg[R-L+1]$

但是我们应该如何确定该子区间的起点呢？由于子区间长度为$2^k$，设起点在$D$处，则满足：

$(D+2^k-1=R) \Leftrightarrow (D=R-2^k+1)$ 

于是对于终止点在ST表里的取值即为：$f[D][k]$，可证明这样一定可以覆盖整个区间。

### 综上，对于区间$[L,R]$求其最值，不难发现答案即为：
$$\max(f[L][k],f[R-(1<<k)+1][k])$$

接下来是一个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/7u35alot.png)

对于蓝色区间，我们先找到$k=lg[8-2+1]=lg[7]=2$，则两个子区间即为：$[2,5],[5,8]$，对应了$f[2][2],f[5][2]$，两个取最值即可。

附上求值部分代码：
```cpp
	for (int i=1;i<=m;i++)
	{
		cin>>x>>y; int l=lg[y-x+1];
		cout<<max(f[x][l],f[y-(1<<l)+1][l])<<endl;
	}
```

- ## 后记

虽说是详细图解，但好像更偏向于一些简单的数学证明。。

ST表对于RMQ问题还是有很大的使用空间，希望各位能好好掌握。

最后附上我丑陋的代码：
```cpp
#include <iostream>
using  namespace std;

int n,m,x,y,a[100010],lg[100010],f[100010][20];

int main()
{
	cin>>n>>m; lg[1]=0;
	for (int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for (int i=1;i<=n;i++) cin>>f[i][0];
	for (int j=1;j<=lg[n];j++)
	for (int i=1;i<=n-(1<<j)+1;i++){
		f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	}
	
	
	for (int i=1;i<=m;i++)
	{
		cin>>x>>y; int l=lg[y-x+1];
		cout<<max(f[x][l],f[y-(1<<l)+1][l])<<endl;
	}
}
```


---

## 作者：qwaszx (赞：76)

$magic!$ $O(n)$在线$RMQ$

前置知识:笛卡尔树

以下标作为节点建立的二叉搜索树，同时权值满足堆的性质.这题取max就是大根堆.

对就是一个$Treap$

对一个序列建立笛卡尔树

使用单调栈维护最右边一条链上的点，容易知道这条链是从上到下递减的，每次在最右边加入一个元素$w[i]$，如果它比栈顶大就弹栈，这样就可以找到它应该插入的位置.记录最后一次弹栈的元素$last$，令栈顶的右儿子是$w[i]$,$w[i]$的左儿子是$last$即可.容易知道是$O(n)$的.

建树代码
```cpp
void build_tree()
{
	int top=1;stack[1]=1;//为了方便，单调栈只记录下标
	for(int i=2;i<=n;i++)
	{
		int lst=0;
		while(top&&w[i]>w[stack[top]])lst=stack[top--];//弹栈
		fa[lst]=i;if(top)fa[i]=stack[top];
		stack[++top]=i;
	}
	for(int i=1;i<=n;i++)if(fa[i])ade(fa[i],i);else S=i;
    //S是根
}
```

容易知道一段区间$[l,r]$的$max$即笛卡尔树上$l$和$r$的$LCA$

然后如果你去翻了翻顶上$kcz\ rank1$的代码，你发现他做到这里就结束了，底下是一个暴力查询.

我们知道这样建出来的树是不平衡的，所以只需要构造一个单调递减的数列，然后每次都查单点就可以卡到$O(n^2)$，但是数据随机...随机...

不管了还是回到解题上来.

这题没强制在线所以可以$Tarjan$求$LCA$，$O(n+m)$.

强制在线?

考虑怎么在$O(n+m)$的时间内在线求一个$LCA$

转成$RMQ$去做~~(所以绕了一大圈又转回来了)~~，考虑树的欧拉序遍历.

欧拉序就是第一次遍历的时候记录一下$dfs$序，每次访问完一个儿子之后再记录一个$dfs$序.

下面是一张~~灵魂~~图示

![](https://cdn.luogu.com.cn/upload/pic/52055.png)

它的欧拉序是$1\ 2\ 4\ 2\ 5\ 2\ 1\ 3\ 1$

长度是多少呢?我们知道除了整棵树都要遍历一遍之外，每个点都有它的儿子个数$son[i]$遍重复

所以$len=n+\sum son[i]=2n-1$

记点$i$的深度是$dep[i]$，在欧拉序中第一次出现的位置是$first[i]$；欧拉序的第$i$个位置所对应的点是$point[i]$.

我们发现一个性质就是两个点$l,r$的$lca$是$min\{dep[point[i]]|first[l]\leq i\leq first[r]\}$所对应的点，也就是两点欧拉序之间深度最低的那个点.这个性质非常容易证明，因为两个点欧拉序第一次出现的位置之间不会有比$lca$深度更小的点且$lca$一定会出现.(其实不是第一次也一样233)

于是我们把$lca$转化成了$rmq$.

如果只是算$rmq$没什么用，但是我们注意到这个rmq有一个非常好的性质，即相邻两个元素之间的差只会是$1$或$-1$

这意味着什么呢?如果我们把长为$n$的序列分块，块的大小是$b$的话，只有$min(2^b,n)$个本质不同的块，因为差分之后每个元素只有两种取值(第一个元素取哪个都行).

为了$O(1)$查询区间的$rmq$，我们需要预处理块和块之间的$rmq$和每个块内的$rmq$.使用$ST$表来处理块间$rmq$，复杂度$O(\frac{n}{b}\log\frac{n}{b})=O(\frac{n}{b}\log n)$；预处理$2^b$种本质不同的情况，复杂度$O(min(2^b,n)b\log b)$.需要在两者中间取一个平衡.令$b=\left\lfloor\frac{\log n}{2}\right\rfloor$，那么前一个式子化成$O(n)$，后一个式子化成$O(\sqrt{n}\ b\log b)$因为$b=O(\log n)$渐进小于任何多项式函数，所以后面这个东西是小于$O(n)$的，从而整体复杂度$O(n)$.

可以预测到代码复杂度极高，所以没什么用.不过空间同样是$O(n)$的，也比$ST$表更加优越~~就是常数不知大到哪里去~~

其实也没有多长，就$130$行，和一个较复杂线段树差不多.压一压行更短.

代码丑的一匹qwq

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int inf=1e9;
int n,m,w[2000000],lg2[1500000];
int pos[1500000],lst[1500000],dep[1500000],id,mm,S,ch[1500000][2],stack[1500000];
struct LIM_RMQ
{
	int w[1500000],bl[1500000],blo,L[150000],R[150000],pos[10000],val[150000],minn[150000],minpos[150000],t[1000],n_st;
	struct ST_node{int f,id;bool operator <(const ST_node &tmp)const{return f<tmp.f;}};
	struct STable
	{
		ST_node a[4][12];//n=1e6的话logn/2只有9...所以放心开
		void make(int w[],int n)
		{
			for(int i=1;i<=n;i++)a[0][i]=(ST_node){w[i],i};
			for(int i=1;(1<<i)<=n;i++)//st表，不过要同时处理出最小值所在的位置
				for(int j=1;j+(1<<i)-1<=n;j++)
					a[i][j]=min(a[i-1][j],a[i-1][j+(1<<(i-1))]);
		}
		ST_node query(int l,int r)
		{
			int len=lg2[r-l+1];
			return min(a[len][l],a[len][r-(1<<len)+1]);
		}
	}st[10000];//这里只有sqrt(n)个，也不用开这么大
	struct STable_block
	{
		ST_node a[20][150000];//这个占空间最大了吧...不过也只是O(n)的
		void make(int w[],int n)
		{
			for(int i=1;i<=n;i++)a[0][i]=(ST_node){w[i],i};
			for(int i=1;(1<<i)<=n;i++)
				for(int j=1;j+(1<<i)-1<=n;j++)
					a[i][j]=min(a[i-1][j],a[i-1][j+(1<<(i-1))]);
		}
		ST_node query(int l,int r)
		{
			int len=lg2[r-l+1];//细节，math库的log2函数不能看做O(1)的，要提前处理
			return min(a[len][l],a[len][r-(1<<len)+1]);
		}
	}st_block;
	void make(int a[],int n)
	{
		for(int i=1;i<=n;i++)w[i]=a[i];
		lg2[1]=0;for(int i=2;i<=n;i++)lg2[i]=lg2[i>>1]+1;//处理log2
		blo=max(lg2[n]>>1,1);//分块
		for(int i=1;i<=n;i++)bl[i]=(i-1)/blo+1;
		for(int i=1;i<=bl[n];i++)L[i]=(i-1)*blo+1,R[i]=min(i*blo,n),minn[i]=inf;
		w[0]=w[1]-1;
		for(int i=1;i<=bl[n];i++)
		{
			int tmp=0,nn=0;
			for(int j=L[i];j<=R[i];j++)
			{
				t[++nn]=w[j],tmp=tmp<<1|(w[j]-w[j-1]==1?1:0);
				if(w[j]<minn[i])minn[i]=w[j],minpos[i]=j;
                //可以用一个状压来表示本质
			}
			if(!pos[tmp])st[pos[tmp]=++n_st].make(t,nn);
			val[i]=pos[tmp];//记下每个块属于哪一个本质
		}
		st_block.make(minn,bl[n]);//块间rmq
	}
	ST_node query_block(int id,int l,int r){ST_node t=st[val[id]].query(l-L[id]+1,r-L[id]+1);return (ST_node){t.f,t.id+L[id]-1};}
    //实际位置=块左端点+块内查询位置-1，如果你把块内查询从0开始写就可以省略-1
	int query(int l,int r)
	{
		int bll=bl[l],blr=bl[r];
		if(bll==blr)return query_block(bll,l,r).id;//一个块
		int ml=query_block(bll,l,R[bll]).id,mr=query_block(blr,L[blr],r).id,mm;
		if(w[ml]<w[mr])mm=ml;else mm=mr;//两端零散块
		if(bll+1<=blr-1)//整块
		{
			int mmid=minpos[st_block.query(bll+1,blr-1).id];
			if(w[mmid]<w[mm])mm=mmid;
		}
		return mm;
	}
}a;
void dfs(int u,int depth)
{
	lst[u]=++id,pos[id]=u;dep[id]=depth;//处理欧拉序列
	for(int i=0;i<=1;i++)
		if(ch[u][i])
		{
			dfs(ch[u][i],depth+1);
			pos[++id]=u,dep[id]=depth;
		}
}
int getin()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x;
}
int wt[30];
void putout(int x)
{
	if(!x){putchar('0');return;}
	int l=0;
	while(x)wt[++l]=x%10,x/=10;
	while(l)putchar(wt[l--]+48);
	puts("");
}
void build_tree()//笛卡尔树
{
	int top=1;stack[1]=S=1;//开始根为1
	for(int i=2;i<=n;i++)
	{
		int lst=0;
		while(top&&w[i]>w[stack[top]])lst=stack[top--];
		if(lst)ch[i][0]=lst;
		if(top)ch[stack[top]][1]=i;else S=i;
		stack[++top]=i;
	}
	dfs(S,1);
}
int main()
{
	n=getin(),m=getin();
	for(int i=1;i<=n;i++)w[i]=getin();
	build_tree();
	a.make(dep,id);
	for(int i=1;i<=m;i++)
	{
		int l=lst[getin()],r=lst[getin()];
		if(l>r)swap(l,r);//可能第一次出现的位置是反过来的
		putout(w[pos[a.query(l,r)]]);
	}
} 
```
其实也没那么长，因为有两个ST表是重复的可以复制粘贴.主要的代码长度就在分块和ST表上.

最多用来写写LCA吧233 纯lca只有100行，比树剖长不了多少

---

## 作者：FZzzz (赞：42)

众所周知，~~无良~~ cz 今天加强了 st 表板题的数据，卡掉了线段树，树状数组等查询带 log 的数据结构。

但是 st 表的板题显然是不能用 st 表做的呀！所以我们需要另一个查询是线性的数据结构。

这里，我们使用**猫树**。

猫树是一种支持 $O(n\log n)+O(1)+O(n\log n)$ 查询区间半群信息的数据结构，OI 界首先见于 immortalCO（猫老师）的博客，故名猫树。

首先声明这只是为了写题解而写的一个教程，并不是专门的学习笔记，所以有些地方可能讲得并不够详细。如果真的要学习猫树，建议去[洛谷日报](https://www.luogu.com.cn/blog/yestoday/mao-shu)或者猫老师的[原始博客](http://immortalco.blog.uoj.ac/blog/2102)。

这东西的思想大概是这样的：建一个类似于线段树一样的东西，然后在每个节点维护中点左边的所有点到中点的答案以及中点到中点右边所有点的答案。查询的时候找到某一个节点使得左右端点都在这个区间中并且位于中点两侧，然后合并答案。

如果直接从上往下去找的话复杂度带一个 log，我们考虑优化掉这个 log。

其实我们可以发现这个区间就是左右端点所对应节点的 lca，怎么去求一下 lca 就行了。

但是有更简单的做法。我们把数组的长度补到二的幂（在后面加零），我们发现两个节点的 lca 就是他们二进制表示的 lcp。

然后如果两个数异或之后，你会发现它们的 lcp 的部分都变成零了，也就是最高位往后挪了 lcp 这么多。

这样我们预处理一下所有数的最高位就行了。

实现上，我们可以把每一层的所有节点的信息存在一个数组里，然后只需要知道 lca 的深度即可。

另外每个数组开几倍要好好注意一下，我 RE 了一面才过……

下面是我自己觉得比较好看的实现：
```cpp
#include<algorithm>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=1e5+5;
int n,m,a[maxn*2];
int f[maxn*2][25],pos[maxn*2];
void build(int o,int l,int r,int d){
	if(l==r){
		pos[r]=o;
		return;
	}
	int mid=l+(r-l)/2;
	build(o*2,l,mid,d+1);
	build(o*2+1,mid+1,r,d+1);
	f[mid][d]=a[mid];
	for(int i=mid-1;i>=l;i--)
		f[i][d]=max(f[i+1][d],a[i]);
	f[mid+1][d]=a[mid+1];
	for(int i=mid+2;i<=r;i++)
		f[i][d]=max(f[i-1][d],a[i]);
}
int lg[maxn*4];
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    m=readint();
    for(int i=1;i<=n;i++) a[i]=readint();
    int len=1;
    while(len<n) len*=2;
    build(1,1,len,1);
    lg[0]=lg[1]=0;
    for(int i=2;i<=len*2;i++) lg[i]=lg[i/2]+1;
    while(m--){
    	int l,r;
    	l=readint();
    	r=readint();
    	if(l==r){
    	    printf("%d\n",a[r]);
    	    continue;
    	}
    	int k=lg[pos[r]]-lg[pos[l]^pos[r]];
    	printf("%d\n",max(f[l][k],f[r][k]));
	}
    return 0;
}
```
据说猫树的本质是把分治的过程离线下来。（所以其实可以直接离线询问然后分治可以做到线性空间）

另外还有一种科技是利用分块思想，每层分根号个块，可以做到 $O(n\log\log n)+O(1)+O(n\log\log n)$，这种科技叫做 sqrt tree，跟猫树有类似之处，我有时间再补吧。

lxl 还给过我一种科技，但是……截图我弄丢了（捂脸）。大概就是也是按照类似 sqrt tree 的方法分块，然后每层块长记得是 $\log$，$\log^{*}$，$\log^{**}$ 这样子（似乎？），分 $\alpha(n)$ 层，就可以做到 $O(n\alpha(n))+O(1)+O(n\alpha(n))$ 这样子，是很厉害的科技了。

总之……就这样吧，我们就用猫树水掉了 st 表的模板题（大雾）。

---

## 作者：critnos (赞：28)

本文主要参考 https://zhuanlan.zhihu.com/p/79423299

大家都会分块 ST 表吧？

就是把序列分块，每块长度 $\log n$，对每块的最大值建 ST 表，维护每块的前缀后缀 $\max$。每次询问的散块可以前后缀 $\max$，整块可以 ST 表。

但是这样有一个问题，就是当 $l,r$ 落在同一块的时候没有维护。

事实上最广为人知的算法 $\pm1$ RMQ 为了解决这个问题，通过建立笛卡尔树转化为 lca 问题，然后通过欧拉序求 lca 方法转化为相邻两项相差为 $\pm1$ 的特殊 RMQ。

upd：

感谢上面知乎文章作者 hqztrue 回复，搬运 TA 的一句话（对 $\pm1$ RMQ 的解释）：

>称±1RMQ的两个块本质不同，如果它们相邻作差后形成的±1数列不同(也就是说可以整体平移一个数，e.g. [1,2,3]和[4,5,6]本质相同，因为相邻作差后的数列为[1,1])。本质相同的两个块对于任意询问的答案所在位置都是相同的。

然后块长为 $\frac {\log n} 2$，则共有 $2^{\frac {\log n} 2}=\sqrt n$ 个本质不同的块，对这些块的每个子段处理，总复杂度 $\sqrt n\log ^2 n$。再把序列中的每一块映射到对应的本质不同的块上。

但是目测这样常数很大（块长过小导致 ST 表过大，cache miss 严重）。

我们先来回忆一下单调栈（单调递减）的性质：

下标单调递增，下标对应的元素单调递减（废话）

还容易得到，设单调栈（对于整个序列的单调栈）内元素为 $p_1\dots p_{size}$，序列为 $a$，序列长度为 $n$，则 $a_{p_1}$ 为 $[1,n]$ 的最大值，$a_{p_2}$ 为 $[p_1+1,n]$ 的最大值……对于 $p_i(1<i\le size)$，$a_{p_i}$ 为 $[p_{i-1}+1,n]$ 的最大值。

比如下面的表，显示出了 $[1\dots n]$ 时刻的单调栈。

```
a:1 3 5 2 4
1:1
2:2
3:3
4:3 4
5:3 5
```
现在问题来了，如何用上面的单调栈求出 $[2,4]$ 的最大值？

我们找到第 $4$ 时刻的单调栈，第一个 $\ge 2$ 的数 $p_i=3$，$a_{p_i}=5$ 即为答案。

一般的，对于区间 $[l,r]$，我们找到 $r$ 时刻的单调栈中第一个 $\ge l$ 的 $p_i$，$a_{p_i}$ 即为答案。

因为这个数一定在 $[l,r]$ 范围内，且它表示 $[p_{i-1}+1,r]$ 的最大值。因为 $p_i$ 是第一个 $\ge l$ 的数，所以 $p_{i-1}<l$，$p_{i-1}+1\le l$，即 $[p_{i-1}+1,r]$ 包含了 $[l,r]$，故而算法正确。

我们在块内使用这个算法即可。

第一个问题：无法存下所有的单调栈，否则会退化为 $\log^2 n$ 的。

我们采取**状态压缩**的 trick。一般认为（word-RAM model）计算机字长 $w\ge \log n$，int 的位数与 $w$ 相同，所以可以把下标在 $\log n$ 规模的单调栈压缩在一个 int 内。换句话说，int 的上界 $\ge n$。

第二个问题：状态压缩后，如何求第一个 $\ge l$ 的数？

我们使用 `l+__builtin_ctz(st[r]>>l)`。

解释一下，`__builtin_ctz(x)` 表示求 $x$ 的二进制表示从末尾开始 $0$ 的个数，`st` 表示状态压缩的单调栈数组。`st[r]>>l` 将 $[0\dots l-1]$ 的二进制位去除，只保留 $[l\dots r]$ 的二进制位。设要求出来的数为 $v$，则末尾应当有 $v-l$ 个 $0$，加上 $l$ 后正确的求出了 $v$。

[代码实现](https://www.luogu.com.cn/paste/xynn9r9k)

以上。

---

## 作者：JS_TZ_ZHR (赞：28)

要讲的内容：笛卡尔树，树的欧拉序，ST 表，分块 RMQ，$\pm1$RMQ。

## 笛卡尔树

笛卡尔树是二叉树的一种，每个节点有两个关键字，分别满足堆和二叉搜索树的性质。一个序列上的笛卡尔树的两个关键字就是值和下标（其实可以用 Treap 来理解），如下（堆是小根堆）：

![](https://oi-wiki.org/ds/images/cartesian-tree1.png)

图片引用自 OI-wiki。

通过笛卡尔树的定义，我们可以得到一个建树方式，对于 $[l,r]$  的笛卡尔树，先找到最值的位置 $p$，$p$ 即为这棵树的根。在将 $[l,p-1]$ 的笛卡尔树作为左子树，$[p+1,r]$ 的笛卡尔树作为右子树。这个建树方式表明一个节点的左/右子树的下标只能在这个节点的下标的左 / 右。

笛卡尔树有一个美妙的性质，就是对于两个下标为 $l$ 和 $r$ 的节点，$[l,r]$ 的最值就是 $l$ 和 $r$ 在笛卡尔树上的最近公共祖先的值。

我们来试着证明这个性质（下面 $l$ 节点指的是下标为 $l$ 的节点）。

定理 $1$:$[l,r]$ 的最值就是 $l$ 和 $r$ 在笛卡尔树上的最近公共祖先的值。

证：若 $l$ 节点和 $r$ 节点都在他们 LCA 的左 / 右子树，那么这与LCA的定义矛盾。显然，$l$ 节点和 $r$ 节点的 LCA 是其子树中的最值并且涵盖了 $[l,r]$ 这个区间，于是这个性质就得证了。这在 RMQ 转 LCA 问题时有很大的用处。

关于笛卡尔树的构建，可以参考 [P5854](https://www.luogu.com.cn/problem/P5854)，具体就是维护右链，对于新插入的值，找到右链上第值一个小于它的节点，变成它的右儿子，它原来的右儿子变为它的左儿子。没有这个节点，直接变为根，原来的树变成它的左子树。

核心代码：

```cpp
for(int i=1;i<=n;i++){
		k=top;
		while(k>0&&a[s[k]]>a[i])k--;
		if(k)rs[s[k]]=i;
		if(k<top)ls[i]=s[k+1];
		s[++k]=i;
		top=k;
	}
```

笛卡尔树其实可以从根暴力往下跳直到找到在 $[l,r]$ 之间的节点。这样做是 $O(nm)$ 的，但随机数据下比较快。如 [P3793](https://www.luogu.com.cn/problem/P3793)。

代码：

```cpp
#include<bits/stdc++.h>
#define N 20000005
using namespace std;
int n,a[N],s[N],top,ls[N],rs[N],k,x,root,m,_s,l,r;
long long ans;
int query(int rt,int l,int r) {
	while(rt<l||rt>r) {
		if(rt<l)rt=rs[rt];
		else rt=ls[rt];
	}
	return rt;
}
namespace GenHelper {
	unsigned z1,z2,z3,z4,b;
	unsigned rand_() {
		b=((z1<<6)^z1)>>13;
		z1=((z1&4294967294U)<<18)^b;
		b=((z2<<2)^z2)>>27;
		z2=((z2&4294967288U)<<2)^b;
		b=((z3<<13)^z3)>>21;
		z3=((z3&4294967280U)<<7)^b;
		b=((z4<<3)^z4)>>12;
		z4=((z4&4294967168U)<<13)^b;
		return (z1^z2^z3^z4);
	}
}
void srand(unsigned x) {
	using namespace GenHelper;
	z1=x;
	z2=(~x)^0x233333333U;
	z3=x^0x1234598766U;
	z4=(~x)+51;
}
int read() {
	using namespace GenHelper;
	int a=rand_()&32767;
	int b=rand_()&32767;
	return a*32768+b;
}
int main() {
	scanf("%d%d%d",&n,&m,&_s);
	srand(_s);
	for(int i=1; i<=n; i++)a[i]=-read();
	for(int i=1; i<=n; i++) {
		k=top;
		while(k>0&&a[s[k]]>a[i])k--;
		if(k)rs[s[k]]=i;
		if(k<top)ls[i]=s[k+1];
		s[++k]=i;
		top=k;
	}
	root=s[1];
	while(m--) {
		l=read()%n+1,r=read()%n+1;
		if(l>r)swap(l,r);
		ans-=a[query(root,l,r)];
	}
	cout<<ans<<endl;
}
```

## 树的欧拉序

树的欧拉序就是在 DFS 时，无论是访问到还是回溯时，都记录一遍点。这么说可能不理解，放代码更直观一点。

```cpp
void dfs(int now,int fa) {
	e[++cnt]=now;//e[i]表示欧拉序里第i个节点是什么
	fi[now]=cnt;//fi[now]表示now节点第一次出现的位置
	for(int i=ve[now].size()-1; i>=0; i--) {
		int y=ve[now][i];
		if(y==fa)continue;
		dep[y]=dep[now]+1;
		dfs(y,now);
		e[++cnt]=now;//回溯时记录
	}
}
```

从这里可以看出，树的欧拉序长点数加边数 $=2n-1$。

理解了树的欧拉序之后，我们来看它有什么性质可以利用。

定理 $2$：$i$ 和 $j$ 两个节点的 LCA 就是 $i$ 第一次出现的位置和 $j$ 第一次出现的位置之间深度最小的那个点。

证：当 $i=j$ 时显然。

若 $i$ 和 $j$ 中有一个是它们的 LCA ，那么在进入不是 LCA 的那个节点时到第一次进入 LCA，只会遍历到 LCA 子树中的节点里。所以深度最小的点就是 LCA。

如果 $i$ 和 $j$ 中没有一个是它们的 LCA，那么它们肯定在 LCA的不同儿子的子树内。遍历完一个会回溯到 LCA，并且因为下面还有节点要遍历，不会回到祖先。于是定理得证。

这样，LCA 和 RMQ 这两个问题就变得等价了。

欧拉序还有一个性质，就是序列中相邻节点的深度差为 $\pm1$，这个很显然，会在以后讲到。

## ST 表

ST表的核心思想是对于每个位置 $p$，预处理 $[p,p+2^0-1]$，$[p,p+2^1-1]$，$[p,p+2^2-1]$，$[p,p+2^3-1]$... 的最值。然后对于每个 $[l,r]$ 的询问，输出 $\max/\min(ST[l][k],ST[r-2^k+1][k])$ （$ST[p][k]$ 表示 $\max\limits_{l \le i \le p+2^k-1}/\min \limits_{l \le i \le p+2^k-1} a_i$ ）。这里  $k=\log_2 (r-l+1)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b;
int Max[100005][21];
inline int query(int l,int r) {
	register int k=log2(r-l+1);
	return max(Max[l][k],Max[r-(1<<k)+1][k]);
}
inline int read() {
	register int x=0;
	register char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')
		x=(x<<3)+(x<<1)+(ch-'0'),ch=getchar();
	return x;
}
int main() {
	scanf("%d%d",&n,&m);
	for(register int i=1; i<=n; i++)Max[i][0]=read();
	for(register int j=1; j<=21; j++)
		for(register int i=1; i+(1<<j)-1<=n; i++)
			Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);
	for(register int i=1; i<=m; i++) {
		a=read(),b=read();
		printf("%d\n",query(a,b));
	}	
}
```

## 分块 RMQ

分块 RMQ 是计算 RMQ 的一种思想，其一般与 ST 表等数据结构配合使用。这里先讲 $\log_2n$ 和 $\sqrt{n}$ 两种块长。最后的 +1-1RMQ 用的则是 $\frac{\log_2n}{2}$ 的块长。

先看 $\log_2n$（ Four Russian 算法，有人叫它四毛子）。我们对于整块，预处理整块的最值。再直接用 ST 表。时间复杂度 $O(\frac{n}{\log n} \log(\frac{n}{\log n}))=O(n)$。对于块内，也用 ST 表预处理,时间复杂度 $O(\frac{n}{\log n} \log \log n)=O(n \log \log n)$，查询时对整块和零散快分别 $O(1)$ 查询。

[P3793](https://www.luogu.com.cn/problem/P3793) 代码（被卡了，只能过 $n=1.5*10^7$）：

```cpp
#include<bits/stdc++.h>
#define N 20001005
using namespace std;
int n,m,s,a[1000005],l,r,B,ST1[900000][26],ST2[900000][26][5],cnt;
long long ans;
namespace GenHelper {
	unsigned z1,z2,z3,z4,b;
	unsigned rand_() {
		b=((z1<<6)^z1)>>13;
		z1=((z1&4294967294U)<<18)^b;
		b=((z2<<2)^z2)>>27;
		z2=((z2&4294967288U)<<2)^b;
		b=((z3<<13)^z3)>>21;
		z3=((z3&4294967280U)<<7)^b;
		b=((z4<<3)^z4)>>12;
		z4=((z4&4294967168U)<<13)^b;
		return (z1^z2^z3^z4);
	}
}
void srand(unsigned x) {
	using namespace GenHelper;
	z1=x;
	z2=(~x)^0x233333333U;
	z3=x^0x1234598766U;
	z4=(~x)+51;
}
int read() {
	using namespace GenHelper;
	int a=rand_()&32767;
	int b=rand_()&32767;
	return a*32768+b;
}
int query1(int l,int r) {
	if(l>r)return 0;
	int k=a[r-l+1];
	return max(ST1[l][k],ST1[r-(1<<k)+1][k]);
}
int query2(int p,int l,int r) {
	int k=a[r-l+1];
	return max(ST2[p][l][k],ST2[p][r-(1<<k)+1][k]);
}
int query(int l,int r) {
	int L=(l-1)/B+1,R=(r-1)/B+1,res=0;
	if(L==R)return query2(L,((l-1)%B)+1,((r-1)%B)+1);
	res=query1(L+1,R-1);
	res=max(res,query2(L,((l-1)%B)+1,B));
	res=max(res,query2(R,1,((r-1)%B)+1));
	return res;
}
int main() {
	cin>>n>>m>>s;
	B=log2(n);
	cnt=(n-1)/B+1;
	srand(s);
	for(int i=1; i<=n; i++) {
		a[0]=read();
		int now=(i-1)/B+1;
		if(a[0]>ST1[now][0])ST1[now][0]=a[0];
		ST2[now][i-now*B+B][0]=a[0];
	}
	for(int j=1; (1<<j)<=cnt; j++)
		for(int i=1; i<=cnt; i++)
			ST1[i][j]=max(ST1[i][j-1],ST1[i+(1<<(j-1))][j-1]);
	for(int i=1; i<=cnt; i++)
		for(int j=1; (1<<j)<=B; j++)
			for(int k=1; k<=B; k++)
				ST2[i][k][j]=max(ST2[i][k][j-1],ST2[i][k+(1<<(j-1))][j-1]);
	a[0]=a[1]=0;
	for(int i=2; i<=1000000; i++)a[i]=a[i>>1]+1;
	while(m--) {
		l=read()%n+1,r=read()%n+1;
		if(l>r)swap(l,r);
		ans+=query(l,r);
	}
	cout<<ans<<endl;
}
```


其实这种做法可以反复分块，但这样没有什么用，常数还大。

$\sqrt{n}$ 块长的就比较玄学了，对于整块，直接暴力  $O(\sqrt{n}^2)$ 预处理，块内只预处理前后缀最值，这样，$l$  和 $r$ 不在同一块的情形就在 $O(1)$ 的时间解决了。容易发现，$l$ 和 $r$ 在同一块的概率大概是 $\frac{1}{\sqrt{n}}$ 的，$m$ 次询问这种情况运行 $O(\frac{m}{\sqrt{n}}\sqrt{n})=O(m)$，于是这种做法在随机数据下就是线性的，但上界其实是 $O(m \sqrt{n})$ 的。这样也可以通过 [P3793](https://www.luogu.com.cn/problem/P3793)。

代码：

```cpp
#include<bits/stdc++.h>
#define max Max
using namespace std;
int n,m,s,a[20000005],max1[2][5005][5005],max2[5005][5005];
int block,begin[1000005],end[1000005],l,r,num;
long long ans;
namespace GenHelper {
	unsigned z1,z2,z3,z4,b;
	unsigned rand_() {
		b=((z1<<6)^z1)>>13;
		z1=((z1&4294967294U)<<18)^b;
		b=((z2<<2)^z2)>>27;
		z2=((z2&4294967288U)<<2)^b;
		b=((z3<<13)^z3)>>21;
		z3=((z3&4294967280U)<<7)^b;
		b=((z4<<3)^z4)>>12;
		z4=((z4&4294967168U)<<13)^b;
		return (z1^z2^z3^z4);
	}
}
inline void srand(unsigned x) {
	using namespace GenHelper;
	z1=x;
	z2=(~x)^0x233333333U;
	z3=x^0x1234598766U;
	z4=(~x)+51;
}
inline int read() {
	using namespace GenHelper;
	int a=rand_()&32767;
	int b=rand_()&32767;
	return a*32768+b;
}
inline int max(int a,int b) {
	return a>b?a:b;
}
void build() {
	block=sqrt(n);
	for(int i=1; i<=n; i+=block) {
		begin[++num]=i,end[num]=min(n,i+block-1);
		for(int j=i; j<=end[num]; j++)
			max1[0][num][j-i+1]=max(max1[0][num][j-i],a[j]);
		for(int j=end[num]; j>=i; j--)
			max1[1][num][end[num]-j+1]=max(max1[1][num][end[num]-j],a[j]);
	}
	for(int i=1; i<=num; i++) {
		for(int j=i; j<=num; j++) {
			max2[i][j]=max2[i][j-1];
			max2[i][j]=max(max2[i][j],max1[0][j][end[j]-begin[j]+1]);
		}
	}
}
int query(int l,int r){
	int numl=(l/block)+(l%block!=0);
	int numr=(r/block)+(r%block!=0);
	int res=0;
	if(numl==numr){
		for(int i=l;i<=r;i++)res=max(res,a[i]);
		return res;
	}
	res=max(max1[1][numl][end[numl]-l+1],max1[0][numr][r-begin[numr]+1]);
	return max(max2[numl+1][numr-1],res);
}
int main() {
	scanf("%d%d%d",&n,&m,&s);
	srand(s);
	for(int i=1; i<=n; i++)a[i]=read();
	build();
	while(m--){
		l=read()%n+1,r=read()%n+1;
		if(l>r)swap(l,r);
		ans+=(unsigned long long)query(l,r);
	}
	cout<<ans;
}
```
## $\pm1$RMQ

重点来了。

上文提到，欧拉序中相邻的两个节点的深度值差为 $\pm1$。考虑利用这个性质。这种情况下可以使用分块 RMQ ，对于一个块，只有 $2^{B-1}$ 种本质不同的可能（ $B$ 是块长，有$B-1$个相邻的数对，且有$\pm1$两种可能）。于是块内可以在 $O(2^{B-1}B^2)$ 处理每种块的所有区间的最值的位置。容易发现，$B$ 取 $\frac{\log_2n}{2}$ 时可以在线性时间内解决。块内是 $O(\sqrt{n} \log^2n)$ 的复杂度。而整块，直接用 Four Russian 算法，还是线性的，于是这个问题就解决了。

最终代码：

RMQ：

```cpp
#include<bits/stdc++.h>
#define N 2000005
using namespace std;
int n,m,a[N],root,s[N],top,e[N],cnt,fi[N],sum[N],dep[N],B=8;
int M[2000][12][12],pre[2000][12],suf[2000][12],Min[50005],ST[50005][25];
int typ[N],Sum[N],lg[N];
struct T {
	int val,l,r;
} t[N];
vector<int>ve[N];
void build1() {
	for(int i=1; i<=n; i++) {
		t[i].val=a[i],s[top+1]=0;
		while(top&&t[s[top]].val<a[i])top--;
		t[i].l=s[top+1];
		if(top)t[s[top]].r=i;
		s[++top]=i;
	}
	root=s[1];
}
void build2() {
	int num[1005];
	while(cnt&7)cnt++;
	for(int i=0; i<(1<<(B-1)); i++) {
		num[1]=0;
		for(int j=0; j<B-1; j++) {
			if(i&(1<<j))num[j+2]=num[j+1]+1;
			else num[j+2]=num[j+1]-1;
		}
		for(int j=1; j<=B; j++) {
			M[i][j][j]=j;
			for(int k=j+1; k<=B; k++)	M[i][j][k]=num[k]<num[M[i][j][k-1]]?k:M[i][j][k-1];
		}
		for(int j=1; j<=B; j++)pre[i][j]=M[i][1][j],suf[i][j]=M[i][j][B];
		Min[i]=M[i][1][B];
	}
	for(int i=1; i<=(cnt>>3); i++) {
		typ[i]=0;
		for(int j=(i<<3)-B+2,t=0; j<=(i<<3); j++,t++)
			if(sum[j]-sum[j-1]>=0)typ[i]|=(1<<t);
		Sum[i]=sum[Min[typ[i]]+((i-1)<<3)];
	}
	for(int i=1; i<=(cnt>>3); i++)ST[i][0]=i;
	int len=lg[cnt]-2;
	for(int j=1; j<=len; j++) {
		for(int i=1; i<=(cnt>>3)-(1<<j)+1; i++) {
			int k=i+(1<<(j-1));
			ST[i][j]=Sum[ST[k][j-1]]<Sum[ST[i][j-1]]?ST[k][j-1]:ST[i][j-1];
		}
	}
}
int Brmq(int l,int r) {
	int k=lg[r-l+1];
	r-=(1<<k)-1;
	return Sum[ST[l][k]]<Sum[ST[r][k]]?ST[l][k]:ST[r][k];
}
void dfs(int now) {
	e[++cnt]=now;
	fi[now]=cnt;
	for(int i=ve[now].size()-1; i>=0; i--) {
		int y=ve[now][i];
		dep[y]=dep[now]+1;
		dfs(y);
		e[++cnt]=now;
	}
}
int query(int l,int r) {
	if(l>r)swap(l,r);
	int L=(l-1)/B+1,R=(r-1)/B+1;
	if(L==R) {
		int pos=(L-1)<<3;
		return pos+M[typ[L]][l-pos][r-pos];
	} else if(L+1==R) {
		int pl=(L-1)<<3,pr=(R-1)<<3;
		return sum[suf[typ[L]][l-pl]+pl]<sum[pre[typ[R]][r-pr]+pr]?suf[typ[L]][l-pl]+pl:pre[typ[R]][r-pr]+pr;
	} else {
		int pl=(L-1)<<3,pr=(R-1)<<3;
		int t1=Brmq(L+1,R-1),t2=sum[suf[typ[L]][l-pl]+pl]<sum[pre[typ[R]][r-pr]+pr]?suf[typ[L]][l-pl]+pl:pre[typ[R]][r-pr]+pr;
		t1=((t1-1)<<3)+Min[typ[t1]];
		return sum[t1]<sum[t2]?t1:t2;
	}
}
int LCA(int x,int y) {
	return e[query(fi[x],fi[y])];
}
namespace IO {
	const int MAXSIZE = 1 << 20;
	char buf[MAXSIZE], *p1, *p2;
#define gc()                                                               \
	(p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
	 ? EOF                                                               \
	 : *p1++)
	inline int read() {
		int x = 0, f = 1;
		char c = gc();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = gc();
		}
		while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
		return x * f;
	}
	char pbuf[1 << 20], *pp = pbuf;
	inline void push(const char &c) {
		if (pp - pbuf == 1 << 20) fwrite(pbuf, 1, pp - pbuf, stdout), pp = pbuf;
		*pp++ = c;
	}
	inline void write(int x) {
		static int sta[35];
		int top=0;
		do {
			sta[++top] = x % 10, x /= 10;
		} while (x);
		while (top) push(sta[top--]+'0');
		push('\n');
	}
}
using namespace IO;
int main() {
	n=read(),m=read();
	for(int i=2; i<=n*2+1; i++)lg[i]=lg[i>>1]+1;
	for(int i=1; i<=n; i++)a[i]=read();
	build1();
	for(int i=1; i<=n; i++) {
		if(t[i].l)ve[i].push_back(t[i].l);
		if(t[i].r)ve[i].push_back(t[i].r);
	}
	dfs(root);
	for(int i=1; i<=cnt; i++)sum[i]=dep[e[i]];
	build2();
	int l,r;
	while(m--) {
		l=read(),r=read();
		write(a[LCA(l,r)]);
	}
	fwrite(pbuf, 1, pp - pbuf, stdout);
}
```

LCA:

```cpp
#include<bits/stdc++.h>
#define N 2000005
using namespace std;
int n,m,root,s[N],top,e[N],cnt,fi[N],sum[N],dep[N],B;
int M[10005][12][12],pre[10005][12],suf[10005][12],Min[10005],ST[200005][25];
int typ[N],Sum[N],lg[N];
vector<int>ve[N];
void build() {
	int num[2005];
	while(cnt%B)cnt++;
	for(int i=0; i<(1<<(B-1)); i++) {
		num[1]=0;
		for(int j=0; j<B-1; j++) {
			if(i&(1<<j))num[j+2]=num[j+1]+1;
			else num[j+2]=num[j+1]-1;
		}
		for(int j=1; j<=B; j++) {
			M[i][j][j]=j;
			for(int k=j+1; k<=B; k++)	M[i][j][k]=num[k]<num[M[i][j][k-1]]?k:M[i][j][k-1];
		}
		for(int j=1; j<=B; j++)pre[i][j]=M[i][1][j],suf[i][j]=M[i][j][B];
		Min[i]=M[i][1][B];
	}
	for(int i=1; i<=cnt/B; i++) {
		typ[i]=0;
		for(int j=(i*B)-B+2,t=0; j<=(i*B); j++,t++)
			if(sum[j]-sum[j-1]>=0)typ[i]|=(1<<t);
		Sum[i]=sum[Min[typ[i]]+((i-1)*B)];
	}
	for(int i=1; i<=(cnt/B); i++)ST[i][0]=i;
	int len=lg[cnt]-2;
	for(int j=1; j<=len; j++) {
		for(int i=1; i<=(cnt/B)-(1<<j)+1; i++) {
			int k=i+(1<<(j-1));
			ST[i][j]=Sum[ST[k][j-1]]<Sum[ST[i][j-1]]?ST[k][j-1]:ST[i][j-1];
		}
	}
}
int Brmq(int l,int r) {
	int k=lg[r-l+1];
	r-=(1<<k)-1;
	return Sum[ST[l][k]]<Sum[ST[r][k]]?ST[l][k]:ST[r][k];
}
void dfs(int now,int fa) {
	e[++cnt]=now;
	fi[now]=cnt;
	for(int i=ve[now].size()-1; i>=0; i--) {
		int y=ve[now][i];
		if(y==fa)continue;
		dep[y]=dep[now]+1;
		dfs(y,now);
		e[++cnt]=now;
	}
}
int query(int l,int r) {
	if(l>r)swap(l,r);
	int L=(l-1)/B+1,R=(r-1)/B+1;
	if(L==R) {
		int pos=(L-1)*B;
		return pos+M[typ[L]][l-pos][r-pos];
	} else if(L+1==R) {
		int pl=(L-1)*B,pr=(R-1)*B;
		return sum[suf[typ[L]][l-pl]+pl]<sum[pre[typ[R]][r-pr]+pr]?suf[typ[L]][l-pl]+pl:pre[typ[R]][r-pr]+pr;
	} else {
		int pl=(L-1)*B,pr=(R-1)*B;
		int t1=Brmq(L+1,R-1),t2=sum[suf[typ[L]][l-pl]+pl]<sum[pre[typ[R]][r-pr]+pr]?suf[typ[L]][l-pl]+pl:pre[typ[R]][r-pr]+pr;
		t1=((t1-1)*B)+Min[typ[t1]];
		return sum[t1]<sum[t2]?t1:t2;
	}
}
int LCA(int x,int y) {
	return e[query(fi[x],fi[y])];
}
namespace IO {
	const int MAXSIZE = 1 << 20;
	char buf[MAXSIZE], *p1, *p2;
#define gc()                                                               \
	(p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
	 ? EOF                                                               \
	 : *p1++)
	inline int read() {
		int x = 0, f = 1;
		char c = gc();
		while (!isdigit(c)) {
			if (c == '-') f = -1;
			c = gc();
		}
		while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
		return x * f;
	}
	char pbuf[1 << 20], *pp = pbuf;
	inline void push(const char &c) {
		if (pp - pbuf == 1 << 20) fwrite(pbuf, 1, pp - pbuf, stdout), pp = pbuf;
		*pp++ = c;
	}
	inline void write(int x) {
		static int sta[35];
		int top=0;
		do {
			sta[++top] = x % 10, x /= 10;
		} while (x);
		while (top) push(sta[top--]+'0');
		push('\n');
	}
}
using namespace IO;
int main() {
	n=read(),m=read(),root=read();
	B=log2(2.0*n)/2.0;
	for(int i=2; i<=n*2+1; i++)lg[i]=lg[i>>1]+1;
	for(int i=1; i<n; i++) {
		int u,v;
		u=read(),v=read();
		ve[u].push_back(v);
		ve[v].push_back(u);
	}
	dfs(root,0);
	for(int i=1; i<=cnt; i++)sum[i]=dep[e[i]];
	build();
	int l,r;
	while(m--) {
		l=read(),r=read();
		write(LCA(l,r));
	}
	fwrite(pbuf, 1, pp - pbuf, stdout);
}
```

### UPD:改正了一个代码错误。

---

## 作者：PPL_ (赞：7)

# 前言

~~众所周知，模板题不用模板做法才是好做法。~~

本文与其它题解做法不同，使用了 $O(n\sqrt{n})$ 预处理，$O(1)$ 查询的分块做法。

# 题目

[洛谷](https://www.luogu.com.cn/problem/P3865)

# 讲解

首先我们直接按 $\sqrt{n}$ 的大小分块，然后考虑如何预处理才能实现 $O(1)$ 查询。

为方便描述，我将一个完整的块称为**整块**，将不完整的块称为**散块**。

我们通过询问来看看我们需要处理哪些东西：

## part1 询问跨块

![](https://cdn.luogu.com.cn/upload/image_hosting/xojjupvt.png)

如图，红色部分为询问区间，黑色部分为我们分的块。

显然我们需要预处理整块与整块之间的最大值。

而对于两边的散块，我们可以预处理每个整块的前缀和后缀最大值，从而得到两边散块的最大值。

预处理时间都是 $O(n)$ 的。

## part2 询问不跨块

![](https://cdn.luogu.com.cn/upload/image_hosting/j0ids7ob.png)

看似很困难，其实我们只需将每个**整块内的区间**的最大值预处理一下就好了。

时间是 $O(n\sqrt{n})$ 的。

搞定了吗？并没有。

我们算一算空间：$\sqrt{100000}\approx320,\dfrac{4\times 320^3}{1024^2}\approx 125\tt MB$。

本题空间限制：$125\tt MB$。

但事实上我们可以将无用空间省下来，比如区间 $[r,l],(r>l)$ 的空间完全就是浪费，所以我们扔掉这些空间之后，就可以让空间减半，此时可以通过。

当然也可以通过调整块的大小来实现时间换空间。

总时间复杂度为 $O(n\sqrt{n}+q)$。

# 代码

```cpp
//12252024832524
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define TT template<typename T>
using namespace std; 

typedef long long LL;
const int MAXN = 100005;
const int MAXB = 318;
int n,Q,B;

LL Read()
{
	LL x = 0,f = 1;char c = getchar();
	while(c > '9' || c < '0'){if(c == '-')f = -1;c = getchar();}
	while(c >= '0' && c <= '9'){x = (x*10) + (c^48);c = getchar();}
	return x * f;
}
TT void Put1(T x)
{
	if(x > 9) Put1(x/10);
	putchar(x%10^48);
}
TT void Put(T x,char c = -1)
{
	if(x < 0) putchar('-'),x = -x;
	Put1(x); if(c >= 0) putchar(c);
}
TT T Max(T x,T y){return x > y ? x : y;}
TT T Min(T x,T y){return x < y ? x : y;}
TT T Abs(T x){return x < 0 ? -x : x;}

int pre[MAXB][MAXB],suf[MAXB][MAXB],MAX[MAXB][MAXB],in[MAXB][MAXB*MAXB/2];
//分别为每个块的前缀最大值，后缀最大值，整块之间的最大值，整块内部的最大值
int ID[MAXN],BID[MAXN],ka[MAXB][MAXB];

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n = Read(); Q = Read();
	B = ceil(sqrt(n));
	for(int i = 0;i < n;++ i) ID[i] = i % B,BID[i] = i / B;
	int tot = 0;
	for(int i = 0;i < B;++ i)//ka=卡，因为这道题卡空间= =
		for(int j = i;j < B;++ j)
			ka[i][j] = tot++; 
	for(int i = 0;i < n;++ i) in[BID[i]][ka[ID[i]][ID[i]]] = Read();
	for(int i = 0;i*B < n;++ i) 
	{
		pre[i][0] = in[i][ka[0][0]];
		suf[i][B-1] = in[i][ka[B-1][B-1]];
		for(int j = 1;j < B;++ j) pre[i][j] = Max(pre[i][j-1],in[i][ka[j][j]]);
		for(int j = B-2;j >= 0;-- j) suf[i][j] = Max(suf[i][j+1],in[i][ka[j][j]]);
		MAX[i][i] = pre[i][B-1];
	}
	for(int i = 0;i*B < n;++ i)
	{
		for(int j = i+1;j*B < n;++ j)
			MAX[i][j] = Max(MAX[i][j-1],MAX[j][j]);
		for(int j = 0;j < B;++ j)
			for(int k = j+1;k < B;++ k)
				in[i][ka[j][k]] = Max(in[i][ka[j][k-1]],in[i][ka[k][k]]);
	}
	while(Q --> 0)
	{
		int l = Read()-1,r = Read()-1;
		int L = BID[l],R = BID[r];
		if(L == R) Put(in[L][ka[ID[l]][ID[r]]],'\n');
		else if(L+1 == R) Put(Max(suf[L][ID[l]],pre[R][ID[r]]),'\n');
		else Put(Max(MAX[L+1][R-1],Max(suf[L][ID[l]],pre[R][ID[r]])),'\n');
	}
	return 0;
}
```

---

## 作者：superLouis (赞：5)

## 题解：P3865 【模板】ST 表 && RMQ 问题

个人认为这是最详细的一篇题解了。

----------
### 1. 算法介绍
所谓的 RMQ 问题，其实就是 Range Minimum / Maximum Query，也就是“区间最大 / 最小值查询”这类问题。而 ST 表就是 Sparse Table，也称稀疏表，是用于解决可重复贡献问题的数据结构。这种算法也是一种离线算法，我们在这里讲述查找最大值。

稀疏表的思想就是把所有区间长度为二的幂次的最值存入一个表中，就可以在恒定的时间回答任何查找范围。

||$2^0$|$2^1$|$2^2$|$2^3$|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$[1,1]$|$[1,2]$|$[1,4]$|$[1,8]$|
|$2$|$[2,2]$|$[2,3]$|$[2,5]$|$[2,9]$|
|$3$|$[3,3]$|$[3,4]$|$[3,6]$|$[3,10]$|
|$4$|$[4,4]$|$[4,5]$|$[4,7]$|$[4,11]$|
|$5$|$[5,5]$|$[5,6]$|$[5,8]$|$[5,12]$|
|$6$|$[6,6]$|$[6,7]$|$[6,9]$|$\varnothing$|
|$7$|$[7,7]$|$[7,8]$|$[7,10]$|$\varnothing$|
|$8$|$[8,8]$|$[8,9]$|$[8,11]$|$\varnothing$|
|$9$|$[9,9]$|$[9,10]$|$[9,12]$|$\varnothing$|
|$10$|$[10,10]$|$[10,11]$|$\varnothing$|$\varnothing$|
|$11$|$[11,11]$|$[11,12]$|$\varnothing$|$\varnothing$|
|$12$|$[12,12]$|$\varnothing$|$\varnothing$|$\varnothing$|

#### （1）稀疏表的合并操作（建立）
在稀疏表内，记 `st[i][j]` 为以第 $i$ 个元素为开头长度为 $2^j$ 的区间最值。初始的时候，所有的 $st_{i,0}$ 都等于 $a_i$。

对于每个 $j>0$ 的 $st_{i,j}$，$st_{i,j} = \max(st_{i,j-1}, st_{i+2^{j-1},j-1})$。其实没你看着那么复杂，就是把长度为 $2^j$ 区间分成两个长度为 $2^{j-1}$ 的区间，两个小区间的起始坐标是 $i$ 和 $i + 2^{j-1}$。下面给一张图，更加直观：

![](https://cdn.luogu.com.cn/upload/image_hosting/a8dqsa13.png?x-oss-process=image/resize,m_lfit,h_400,w_800)

在这里，我们给出稀疏表的合并（建立）操作的代码：
```cpp
void st_build() {
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    int t = log2(n); // 这里 t 是枚举时长度的上限
    for (int j = 1; j <= t; j++)
        for (int i = 1; i <= n - (1 << j) + 1; i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
```
时间复杂度 $\Theta(n \log n)$

#### （2）稀疏表查询操作
说实话，最开始我想到的查询操作是 $\Theta(\log n)$ 时间复杂度的。大概是这样：把要查询的区间进行二进制拆分，然后拆成最多 $\log n$ 个互不重叠的区间，并将这些区间的最大值取 $\max$。实际上这样是大炮打蚊子——小题大做了。

$\max$ 的特性是什么？就是可以有任意的重叠部分啊！我们根本不用二进制拆分那么麻烦去分成一堆互不重叠的区间，因为在查询操作的时候就是可以有重叠。换句话说，令 $l < i < j < r$ 并且记 $f_{p,q}$ 为区间 $[p,q]$ 的区间最大值，那么 $f_{l,r} = \max(f_{l,j},f_{j+1,r}) = \max(f_{l,i}, f_{i+1,r}) = \max(f_{l,j}, f_{i,r})$，即使中间重叠了 $[i,j]$ 这段区间也没有问题，重复算对 $\max$ 没有影响。

所以，查询操作最简单的方式就是：

1. 当询问任意区间 $[l,r]$ 的最大值时，我们先计算出一个 $k$，满足：$2^k \le r–l+1 <2^{k+1}$。也就是在小于等于区间长度的前提下，找到最大的 $2$ 的 $k$ 次幂。
2. 此时，从“$l$ 开始的 $2^k$ 个数”，和“以 $r$ 结尾的 $2^k$ 个数”这两段一定覆盖 $[l,r]$（一般会有重合部分，但不影响答案）。
3. 这两段的最大值分别是 $st_{l,k}$ 和 $st_{r-2^k+1,k}$，两者的中的较大值就是整个区间 $[l,r]$ 中的最大值。

在这里，我们给出稀疏表查询操作的代码：
```cpp
int st_query(int l, int r) {
	int k = log2(r - l + 1); // std::log2 的性能非常高，时间复杂度非常接近 Θ(1)
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}
```

这样下来，时间复杂度 $\Theta (1)$，完美！

----------
### 2. 正确性证明
先对合并（建立）操作进行正确性证明。对于每一个 $st_{i,j} (j > 0)$，都能毫不重合并且不遗漏任何地从 $st_{i,j-1}$ 和 $st_{i+2^{j-1},j-1}$ 推得。设 $i=a, i+2^j=b, i+2^j-1=c$ 并且记区间 $[p,q]$ 的最大值是 $f_{p,q}$，则 $f_{a,b} = \max(f_{a,c}, f_{c+1,b}) = \max(st_{i,j-1}, st_{i+2^{j-1}，j-1})$。

查询操作的正确性前面证明过，这里再写一遍。令 $l < i < j < r$ 并且记 $f_{p,q}$ 为区间 $[p,q]$ 的区间最大值，那么 $f_{l,r} = \max(f_{l,j},f_{j+1,r}) = \max(f_{l,i}, f_{i+1,r}) = \max(f_{l,j}, f_{i,r})$，即使中间重叠了 $[i,j]$ 这段区间也没有问题，重复算对 $\max$ 没有影响。

此外，我说一下复杂度问题：

- 时间复杂度：合并（建立）为 $\Theta(n \log  n)$，查询为 $\Theta(1)$。
- 空间复杂度：$\Theta(n \log n)$，开销基本在 `st[][]` 数组上。 

----------
### 3. 代码实现

我觉得上面解析的很明白了，代码注释就不加了。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int maxm = log2(maxn) + 10;
int n, q, a[maxn], st[maxn][maxm];
namespace quick {
	inline int read() {
		int x = 0, f = 1; char ch = getchar();
		while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
		while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
		return x * f;
	}
}
void st_build() {
	for (int i = 1; i <= n; i++) st[i][0] = a[i];
	int t = log2(n);
	for (int j = 1; j <= t; j++) 
		for (int i = 1; i <= n - (1 << j) + 1; i++) 
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]); 
}
int st_query(int l, int r) {
	int k = log2(r - l + 1);
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	n = quick::read();
	q = quick::read();
	for (int i = 1; i <= n; i++) a[i] = quick::read();
	st_build();
	while (q--) {
		int l = quick::read(), r = quick::read(); 
		cout << st_query(l, r) << "\n";
	}
	return 0;
}
```
这里为了以防万一，还是按照题目的建议加了快读。

----------
### 4. 其他方法
对付 RMQ 问题，其实还有一种复杂的方法，就是普通线段树。更多请见 [这里](https://www.luogu.com.cn/problem/P3372) 哦，但线段树去解决 RMQ 问题其实小题大做了。值得说的是，线段树的查询操作是 $\Theta(\log n)$ 的，而不是 $\Theta(1)$ 的。代码贴在这里（根本不用 lazytag 的）：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#define lson (p << 1)
#define rson (p << 1 | 1)
constexpr int maxn = 1e5 + 10;
int n, q, a[maxn];
struct node { int l, r, ans; } t[maxn << 2];
namespace quick {
	inline int read() {
		int x = 0, f = 1; char ch = getchar();
		while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
		while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
		return x * f;
	}
    inline void w(int x) {
        if (x < 0) { x = ~(x - 1); putchar('-'); }
        if (x > 9) w(x / 10); putchar(x % 10 + '0');
    }
}
inline void build(int p, int l, int r) {
    t[p].l = l; t[p].r = r;
    if (l == r) {
        t[p].ans = a[l];
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    t[p].ans = max(t[lson].ans, t[rson].ans);
}
inline int query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].ans;
    int mid = (t[p].l + t[p].r) >> 1, ans = 0;
    if (l <= mid) ans = max(query(lson, l, r), ans);
    if (r >= mid + 1) ans = max(query(rson, l, r), ans);
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    n = quick::read(), q = quick::read();
    for (int i = 1; i <= n; i++) a[i] = quick::read();
    build(1, 1, n);
    while (q--) {
        int l = quick::read(), r = quick::read();
        quick::w(query(1, l, r)); putchar('\n');
    }
    return 0;
}
```

我在文章中讲解我一开始以为稀疏表查询时按二进制拆成若干个小区间的做法，其实在求区间加和、乘积等不能进行重叠计算的操作中可以使用。发展成这样的稀疏表已经很接近普通线段树了。

----------
谢谢大家的阅读！

---

## 作者：2014吕泽龙 (赞：4)

楼上楼下的st表写的好溜啊。。。

还混进了什么回滚莫队，分块，线段树等等神仙做法。

这里提供一种线性的做法-笛卡尔树

笛卡尔树是一颗二叉搜索堆。
因为它同时具有二叉搜索树和堆的性质。

具体地，其中序遍历是原序列，同时满足当前节点是子树最值。

构造的方法是用单调栈维护最右链，插入之后其余节点换到左子树。

性质是两点的Lca就是区间最值。

所以可以用Tarjan加并查集搞。

复杂度$O(n+m)$

被rmq吊打。

```cpp
#include<bits/stdc++.h>
int ri() {
    char c = getchar(); int x = 0, f = 1; for(;c < '0' || c > '9'; c = getchar()) if(c == '-') f = -1;
    for(;c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) - '0' + c; return x * f;
}
const int N = 1e5 + 10, M = 2e6 + 10;
int n, m, tp, rt, st[N], ls[N], rs[N], a[N], pr[N], g[N], A[M], to[M], nx[M], id[M]; bool vis[N];
int F(int x) {return !g[x] ? x : g[x] = F(g[x]);}
void adds(int u, int v, int i) {to[++tp] = v; nx[tp] = pr[u]; pr[u] = tp; id[tp] = i;}
void Tarjan(int u) {
    vis[u] = true;
    if(ls[u]) Tarjan(ls[u]), g[F(ls[u])] = u;
    if(rs[u]) Tarjan(rs[u]), g[F(rs[u])] = u;
    for(int i = pr[u]; i; i = nx[i]) 
        if(vis[to[i]] && !A[id[i]]) 
            A[id[i]] = F(to[i]);
}
int main() {
    n = ri(); m = ri();
    for(int i = 1;i <= n; ++i) {
        a[i] = ri();
        for(;tp && a[i] > a[st[tp]];) ls[i] = st[tp--];
        tp ? rs[st[tp]] = i : rt = i;
        st[++tp] = i;
    }
    for(int i = 1;i <= m; ++i) adds(ri(), ri(), i);
    Tarjan(rt);
    for(int i = 1;i <= m; ++i) printf("%d\n", a[A[i]]);
    return 0;
}
```

---

## 作者：hhy0911 (赞：1)

# 题意简介

给出一个数组，每次询问 $l$ 到 $r$ 之间的最大值。

# 介绍数据结构 ST 表

题目都写着 ST 表肯定要用它啦。

ST 表是一个好用的数据结构，可以在 $O(1)$ 的时间内计算一个数组的区间最小（大）值，需要预处理，预处理时间复杂度 $O(n \log n)$。

ST 表的思想是倍增。通过拼接两个长为 $2$ 的倍数的最大值得到最大值。下面我来介绍一下 ST 表怎么用。

## 一、预处理

从前面的讲解可知，ST 表需要拼接两个长为 $2$ 的倍数的区间最大值从而的到最大值，所以预处理需要处理出以每个节点为起点的区间的最大值。直接设以 $i$ 为起点，长为 $2^j$ 的区间最大值为 $st_{j, i}$，可得

$$
st_{j,i}=\max(st_{j-1,i},st_{j-1,i+2^{j-1}})
$$

即把两个长为 $2^{j-1}$ 的区间拼起来求最大值。为什么呢？简单想想就知道了，因为 $2^{j-1}+2^{j-1} = 2^j$，那么两个长为 $2^{j-1}$ 的区间拼起来长就是 $2^j$ 了。上图片：

![](https://cdn.luogu.com.cn/upload/image_hosting/qr1wu4wx.png)

我们还要处理一个 $log2$ 数组，用来储存每个数以 $2$ 为底的对数，向下取整（有什么用后面会说）。可以用简单递推解决，公式为 $log2_i = log2_{\left \lfloor \frac{i}{2}  \right \rfloor} + 1$。

代码如下：


```cpp
void init(){
	for(int i = 2;i <= n;i++)log2[i] = log2[i >> 1] + 1;
	for(int j = 1;j <= log2[n];j++){
		for(int i = 1;i <= n - (1 << j) + 1;i++){
			st[j][i] = max(st[j-1][i], st[j-1][i + (1 << (j - 1))]);
		}
	}
}
```

## 二、查询

在上文也提到，ST 表通过拼区间来求最值。那么通过上面的铺垫，也可以轻松想到，拼两个大小为 $2$ 的倍数中最大且小于 $r-l+1$ 的区间最值得到。重复部分不影响求最大值。因此怎么求最值的方法就很明显了。

先求一个 $lg=\log{r-l+1}$，再拼两个大小为 $2^{lg}$ 的区间。返回 $\max(st_{lg,l},st_{lg,r-2^{lg}+1})$，即两个区间的最值。公式有点晦涩，上个图片加深理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/697binoc.png)

代码：


```cpp
inline ll ask(ll l, ll r){
	ll lg = log2[r - l + 1];
	return max(st[lg][l], st[lg][r - (1 << lg) + 1]);
}
```

## 三、时间复杂度

因为 ST 表预处理出区间最值外层需要循环 $\log n$ 次，内层每一个点都要计算，所以 ST 表预处理的复杂度是 $O(n \log n)$。

而查询的时间复杂度就很显然了，没有循环，只要计算两个区间最大值，所以时间复杂度是 $O(1)$。

# AC代码


```cpp
#include<iostream>
using namespace std;
typedef long long ll;
const ll N = 1e5 + 7;
//快读 
inline ll read(){
	ll ans = 0;
	char c;
	while(1){
		c = getchar();
		if(isdigit(c))break;
	}
	while(1){
		ans *= 10;
		ans += c - '0';
		c = getchar();
		if(!isdigit(c))break;
	}
	return ans;
}
ll log2[N], st[30][N];
ll a[N];
ll n, m;
//预处理 
void init(){
	for(int i = 2;i <= n;i++)log2[i] = log2[i >> 1] + 1;
	for(int j = 1;j <= log2[n];j++){
		for(int i = 1;i <= n - (1 << j) + 1;i++){
			st[j][i] = max(st[j-1][i], st[j-1][i + (1 << (j - 1))]);
		}
	}
}
//求最值 
inline ll ask(ll l, ll r){
	ll lg = log2[r - l + 1];
	return max(st[lg][l], st[lg][r - (1 << lg) + 1]);
}
int main(){
	n = read();
	m = read();
	for(int i = 1;i <= n;i++){
		a[i] = read();
		st[0][i] = a[i];
	}
	//预处理 
	init();
	//求最值 
	for(int i = 1, l, r;i <= m;i++){
		l = read();
		r = read();
		cout << ask(l, r) << '\n';
	}
	return 0;
}

```

代码其实挺简短的，只是 $2$ 的幂运算有点绕。

---

## 作者：zsq9 (赞：1)

[AC 记录](https://www.luogu.com.cn/record/217204286)

## 前言

建议先学会[倍增](https://oi-wiki.org/basic/binary-lifting/)。

## 算法介绍

ST 表适用于 **可重复贡献问题**，比如这个 RMQ 问题，RMQ 问题就是区间最大 / 区间最小值。具体 ST 表实现如下，
首先我们要预处理一下，我们把一个 $[i,i+2^{s}-1]$ 区间分为，$[i,i+ 2^{s-1} -1]$ 和 $[i+ 2^{s-1},i+ 2^{s} -1]$ 我们算这两个区间的最大值就可以算出 $[i,j]$ 的最大值，这里 $s=\left\lfloor\log _{2}len\right\rfloor$。同样每个询问，我们把 $[l,r]$ 区间分为 $[l,l+ 2^s -1]$ 和 $[r-2^{s}+1,r]$，两部分的结果的最大值就是回答，这里 $s=\left\lfloor\log _{2}(r-l+1)\right\rfloor$。

## 正确性证明

由于这个问题是可重复贡献问题，所以重叠并不会对区间最大值产生影响，并且 $[l,l+ 2^s -1]$ 和 $[r-2^{s}+1,r]$ 一定覆盖了 $[l,r]$，所以不会对答案有影响。
因为我们倍增每次跳 $2^{s}$ 幂次所以，$s$ 为 $\left\lfloor\log _{2}len\right\rfloor$ 是可以的。我们 $s=\left\lfloor\log _{2}(r-l+1)\right\rfloor$ 就可以保证一定覆盖了 $[l,r]$ 并且对答案不会有影响。
求 $\log _{2}x$ 题解很多大佬都说过了，就是求二进制下的最高位，每次右移一位，右移的次数就是这个 $x$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
ll stmax[100005][20],n,q;
ll maxx(ll a,ll b){
	if(a>b)return a;
	else return b;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for (int i = 1; i <= n; i++)cin>>stmax[i][0];
	for (int j = 1; (1 << j) <= n; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			stmax[i][j] = maxx(stmax[i][j - 1], stmax[i + (1 << j - 1)][j - 1]);
	while (q--){
		ll l,r;
		cin>>l>>r;
		ll k = log2(r - l + 1);
		cout<<maxx(stmax[l][k], stmax[r - (1 << k) + 1][k])<<"\n";
	}
	return 0;
}
```

---

## 作者：zhou2414 (赞：1)

UPD：更正时间复杂度。

UPD：修改了对于预处理中公式的证明。

UPD：更换了~~更美观~~的图片。
# 前置知识
- 倍增。
### RMQ 问题
在一个数列中，回答若干询问，返回指定区间内的最小值或最大值。
# st 表简介
以下以求最大值为例。
## 作用
st 表是一种能以 $O(n\log n)$ 复杂度预处理，$O(1)$ 查询的数据结构。一般**不支持**修改操作。通常用于解决 RMQ 问题。
## 原理
st 算法通过预处理以点 $i$ 为左边界，区间长为 $2^k$ 的区间内的最大值，记为 $st_{i,k}$ ，然后在查询时快速得出结果。

如下图所示为左边界为 $1$ 的情况：

![美观的 st 表](https://cdn.luogu.com.cn/upload/image_hosting/tss1drl4.png)

而假设我们当前要求区间 $[a,b]$ 的最大值，那么就可以求出一个 $k$，使得 $2^k\leq b-a+1$ 且 $2^{k+1}\geq b-a+1$ 。然后返回 $\max(st_{a,k},st_{b-2^k+1,k})$ 即可。

如下图为查询区间 $[2,7]$ 的最大值的情况：

![美观的 st 表查询](https://cdn.luogu.com.cn/upload/image_hosting/lmxapt9n.png)
## 正确性证明
首先证明 $k$ 一定存在且唯一。设区间长度为 $len$，那么存在 $2^p=len$，令 $k=\lfloor p \rfloor$，显然此时 $2^k\leq len$ 且 $2^{k+1}\geq len$。由此也可以得出计算 $k$ 的方式，即 $k=\lfloor\log_2 len\rfloor$。

然后显然这样算一定会覆盖区间 $[a,b]$ 中的所有元素，且重叠部分不影响答案。
## 实现
### 预处理
可以从后往前，用类似 dp 的方式预处理。转移方程显然为：
$$
st_{i,j}=\max(st_{i,j-1},st_{i+2^{j-1},j-1})
$$
两重循环即可。

同时由于 c++ 中 ``log2(x)`` 函数的复杂度为 $O(\log x)$（一说接近 $O(1)$），要想实现真正的 $O(1)$ 查询，还要预处理出 $1$ 到 $n$ 的对数整数值，记为 $lg_i$。该值可以由下面这个公式估算：
$$
lg_i=lg_{\lfloor\frac i 2\rfloor}+1
$$
特别地，$lg_0=-1$，这是为了方便递推，实际查询时不会用到它。
#### 证明
~~不会证明被审核员打回并嘲讽了~~。所以来简单证明一下。

求 $\lfloor\log_2 x\rfloor$ 就相当于求其二进制最高位是第几位。那么显然不断右移直到仅剩一位，右移的次数即为答案。每次除以 $2$ 并向下取整，就相当于右移一位。由于前面一定已经求出过此时的结果，直接调用并加 $1$ 即可。
#### 代码

```cpp
void init() {
	lg[0] = -1;
	for (int i = 1; i < N; i++)
		lg[i] = lg[i / 2] + 1;
	for (int i = n; i >= 1; i--) {
		for (int j = 0; i + (1 << j) -1 <= n; j++) {
			if (j == 0)
				st[i][j] = a[i];
			else
				st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
}
```
### 查询
首先计算得出 $k$，然后返回 $\max(st_{a,k},st_{b-2^k+1,k})$ 即可。
#### 代码

```cpp
int query(int a, int b) {
	int len = (b - a + 1);
	int k = lg[len];
	return max(st[a][k], st[b - (1ll << k) +1][k]);
}
```
## 复杂度分析
预处理时间复杂度 $O(n\log n)$，查询复杂度 $O(1)$。总复杂度 $O(n\log n)$。

空间复杂度显然 $O(n\log n)$。
# 完整代码
本题时限较紧，需要用快读卡常。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define dd double
inline ll read() {
	ll x = 0, f = 1;
	char ch;
	while (((ch = getchar()) < 48 || ch > 57) && ch != EOF)if (ch == '-')f = -1;
	if (ch == EOF)x = EOF;
	while (ch >= 48 && ch <= 57)x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
const ll N = 1e5+9, logN = 30;
ll st[N][logN];
ll n, m;
ll lg[N];
ll a[N];
void init() {
	lg[0] = -1;
	for (int i = 1; i < N; i++)
		lg[i] = lg[i / 2] + 1;
	for (int i = n; i >= 1; i--) {
		for (int j = 0; i + (1 << j) -1 <= n; j++) {
			if (j == 0)
				st[i][j] = a[i];
			else
				st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
}
int query(int a, int b) {
	int len = (b - a + 1);
	int k = lg[len];
	return max(st[a][k], st[b - (1ll << k) +1][k]);
}
int main() {
	n = read();
	m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	init();
	for (int i = 1; i <= m; i++) {
		ll l = read(), r = read();
		cout << query(l, r);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：rainygame (赞：1)

半夜想到一种神奇的做法，可以将空间复杂度压到 $O(n+m)$，还很好写。

先将询问按 $\lfloor\log_2 (r-l+1)\rfloor$ 分成组，对于在同一个组内的询问，它们只需要第二维相同的倍增表。

然后直接在预处理 ST 表时回复询问就可以了。可以用滚动数组优化。

但是发现滚动数组不优美，观察 ST 表的转移方程：

$$
f_{i,j} = \max\{f_{i,j-1}, f_{i+2^{j-1},j-1}\}
$$

发现转移只需要使用**没有被更新**的元素，所以像背包一样，直接把第二维压掉即可。

这样所用的空间大概是 $n+4m$ 的样子，妈妈再也不用担心我被卡空间了。（貌似倍增有时候确实会被卡空间）

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 100001
#define MAXM 2000001
#define qry(l, r) max(f[l], f[(r)-(1<<nw)+1])

int n, m, nw;
int f[MAXN], ans[MAXM];
struct Que{int l, r, id;}; vector<Que> que[17];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> m; for (int i(1); i<=n; ++i) cin >> f[i];
    for (int i(1), l, r; i<=m; ++i) cin >> l >> r, que[__lg(r-l+1)].push_back({l, r, i});
    for (auto i: que[0]) ans[i.id] = qry(i.l, i.r);
    for (nw=1; nw<=16; ++nw){
    	for (int i(1); i+(1<<nw)-1<=n; ++i) f[i] = max(f[i], f[i+(1<<(nw-1))]);
    	for (auto i: que[nw]) ans[i.id] = qry(i.l, i.r);
	}
	for (int i(1); i<=m; ++i) cout << ans[i] << '\n';

    return 0;
}

```

---

## 作者：Little_Deer_Peach (赞：0)

题意已经简洁了不再赘述。

由于是 ST 表模板题，所以要介绍什么是 ST 表，以及如何实现。ST 表在本题中是求一个静态区间内的最大值。

首先我们先了解 ST 表的实现，它是由倍增的思想实现的。在查询前，先建出 ST 表。按照题目描述，定义 $st_{i,j}$ 为序列中第 $i$ 个数后连续 $2^j$ 个数中最大的值。

那么就可以按照 $j$ 从小到大推，把 ST 表建出来。因为一个长度为 $2^{len}$ 的大区间由可以两个长度为 $2^{len-1}$ 的小区间合并得到，所以我们从小区间开始合并到大区间。初始化就是 $st_{i,0}=a_i$，因为第 $i$ 个数后 $2^0$ 就是它自己一个数。

建表代码：
```cpp
for(int len=1;len<=lg[n];len++){//lg[i]=log2(i)，2^len为区间长度
    for(int i=1;i+(1<<len)-1<=n;i++){//i+(1<<len-1)是区间最后一个数，用来判断是否越界
		st[i][len]=max(st[i][len-1],st[i+(1<<(len-1))][len-1]);//长度为2^len的区间由两个长度为2^(len-1)的小区间合并得
	}
}
```
时间复杂度 $\mathcal O(n \log n)$。

由于上方代码出现了 $lg$ 数组，在这里解释它的作用。$lg_i$ 其实就是求 $\lfloor \operatorname{log_2}(i) \rfloor$，只不过是提前预处理出来优化掉一些常数。

如何预处理呢？我们知道一个数 $x$ 乘以 $2$，那么它 $\operatorname{log_2}(x \times 2)$ 的值就等于 $\operatorname{log_2}(x)+1$。因为 $2^x \times 2= 2 ^ {x+1}$。那么反过来可得 $lg_i=lg_{\frac{i}{2}}+1$。

所以我们可以这样预处理：
```cpp
for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
```
因为 $2^0=1$，所以从 $2$ 开始处理。时间复杂度 $\mathcal O(n)$。

那么如何查询呢？由于求一个区间的最大值是满足结合律的，也就是可以按不同顺序求，所以区间重复不影响结果。由此也可以得知，ST 表适用于求满足结合律的运算，如最大值，最小值，最大公约数等。前面我们预处理出 $lg$ 数组，而且一个大区间可以由两个小区间合并得到。那我们就可以把所求区间拆分成两个小区间来求答案。那么怎么拆？$lg$ 数组就派出用场了，因为 $lg_i = \lfloor \operatorname{log_2}(i) \rfloor$，所以设 $x = lg_i$，那么 $2^x \le i$，所以将长度为 $i$ 的区间分成两个长度为 $2^x$ 的区间即可，只不过首项尾项位置需要计算。给出一个示例：
```cpp
求一个长度为5的区间：
lg[5]=log2(5)=2  (向下取整运算)
小区间长度=2^2=4 (^ 在这里指乘方运算)
1 2 3 4 5 
1 2 3 4
  2 3 4 5
```
由此我们可以推出，查询一个区间 $[l,r]$，可以分成 $[l,l+2^{lg_{r-l+1}}]$ 和 $[r-2^{lg_{r-l+1}}+1,r]$，这样两个长度为 $2^{lg_{r-l+1}}$ 的区间就可以覆盖区间 $[l,r]$ 了。

代码：
```cpp
for(int i=1;i<=m;i++){
	int l,r;
	l=read();
	r=read();
	int x=lg[r-l+1];
	printf("%lld\n",max(st[l][x],st[r-(1<<x)+1][x]));
}
```
时间复杂度 $\mathcal O(1)$。

完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0) 
const int N=1e5+5;
int n,m;
int a[N];
int lg[N],st[N][30];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
signed main(){
	n=read();
	m=read();
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++){
		st[i][0]=read();
	}
	for(int len=1;len<=lg[n];len++){
		for(int i=1;i+(1<<len)-1<=n;i++){
			st[i][len]=max(st[i][len-1],st[i+(1<<(len-1))][len-1]);
		}
	}
	for(int i=1;i<=m;i++){
		int l,r;
		l=read();
		r=read();
		int x=lg[r-l+1];
		printf("%lld\n",max(st[l][x],st[r-(1<<x)+1][x]));
	}
	return 0;
}
```
[记录](https://www.luogu.com.cn/record/217169268)。

---

## 作者：LionBlaze (赞：0)

# 前置知识

如何快速求出 $\lfloor\log_2x\rfloor$？

这里有几种方法。

- $\mathcal O(n)$ 打表，在 ST 表的应用中只需要打数字数量级别的表就行。
- 使用不可移植的 GCC 内部函数。
- 标准做法是使用 C++20 的 `bit_width` 函数再 $-1$，注意目前 NOI 系列比赛不能用。
- $\mathcal O(\log \log n)$ 的倍增做法。

四种方法的代码见下。

```cpp
enum class qwq123_mode
{
	GetTable,
	GCCInnerFunc,
	BitWidth,
	Binary,
	Default = Binary // 此处 Binary 可以换成上面的任意一个值
};
constexpr int value_range = 100005; // 值域（用于打表）
unsigned qwq123(unsigned x)
{
	switch(qwq123_mode::Default)
	{
	case qwq123_mode::GetTable:
		// 定义表类型，原因见下
		class TableType
		{
			int* table;
		public:
			TableType()
			{
				table = new int[value_range + 1];
				table[1] = 0;
				for (int i = 2; i <= value_range; i++)
				{
					table[i] = table[i >> 1] + 1;
				}
			}
			int get(int x) { return table[x]; }
		};
		// 使用语法糖实现自动打表
		// 利用 static 变量第一次声明自动初始化
		static TableType tt;
		return tt.get(x);
	case qwq123_mode::GCCInnerFunc: return 31 - __builtin_clz(x);
	case qwq123_mode::BitWidth: return bit_width(x) - 1;
	case qwq123_mode::Binary: 
		// 通常来讲，unsigned 比 int 快
		// 前提是不开编译器优化。聪明一点的编译器
		// 都会把可以用 unsigned 的 int
		// 替换成 unsigned。
		unsigned res = 0;
		// 事实上，应该是 res += 16
		// 但是其实两者等价。不开编译器优化时
		// |= 明显更快。
		if (x >> 16) { res |= 16; x >>= 16; }
		if (x >> 8) { res |= 8; x >>= 8; }
		if (x >> 4) { res |= 4; x >>= 4; }
		if (x >> 2) { res |= 2; x >>= 2; }
		// 最后不需要调整 x 了。
		if (x >> 1) { res |= 1; }
		return res;
	}
}
```

下面是测速结果。

- 打表做法：[总用时 $2.10\mathrm{s}$，最快点 $4\mathrm{ms}$，最慢点 $467\mathrm{ms}$](https://www.luogu.com.cn/record/205109982)。
- 内部函数：[总用时 $2.05\mathrm{s}$，最快点 $3\mathrm{ms}$，最慢点 $448\mathrm{ms}$](https://www.luogu.com.cn/record/205110025)。
- 标准做法：[总用时 $2.06\mathrm{s}$，最快点 $3\mathrm{ms}$，最慢点 $456\mathrm{ms}$](https://www.luogu.com.cn/record/205110104)。
- 倍增算法：[总用时 $2.10\mathrm{s}$，最快点 $3\mathrm{ms}$，最慢点 $488\mathrm{ms}$](https://www.luogu.com.cn/record/205110153)。

意料之中地，GCC 内部函数做法最快，标准做法其次。

# 算法介绍

ST 表（又名稀疏表，Sparse Table），是一种支持静态 RMQ 问题的数据结构。

> 什么是 RMQ 问题？是 Range Maximum/Minimum Query 的缩写，表示区间最值。其实，ST 表不仅可以处理 RMQ 问题，还可以处理所有满足可重复贡献且满足结合律的问题（没错，这一段就是从 [OI-wiki](https://oi-wiki.org/ds/sparse-table/) 上抄的）。设操作为 $f(x,y)$，可重复贡献是指 $f(x,x)=x$，而满足结合律是指 $f(x,f(y,z))=f(f(x,y),z)$。**下面我们都假设操作为 $\bm{\max}$ 操作。**

它其实是一个二维数组。通常情况下，我们使用 $f_{i,j}$ 表示 $\displaystyle\max_{k=i}^{i+2^j-1}a_k$，但是事实证明这种表示方法并不是很好。

> 为什么？第一个原因是因为 cache 不友好，为啥不友好详见后面的预处理部分。第二个原因是因为作者常写的边度边预处理在这种表示法下不好写也不好看，作者习惯的是 $\displaystyle f_{j,i}=\max_{k=i-2^j+1}^{i}a_k$。**以下都用这种表示方法。**
>
> 测速结果（均使用 GCC 内置函数算 $\log$）：
>
> - cache 不友好：[$2.05 \mathrm{s}$](https://www.luogu.com.cn/record/205110025)。
> - cache 友好：[$1.87 \mathrm{s}$](https://www.luogu.com.cn/record/205111445)。

## 预处理

显然是递推。

我们注意到区间 $[x, x+2^j)$ 可以分为两部分，$[x,x+2^{j-1})$ 和 $[x+2^{j-1},x+2^j)$（看过我的线段树文章的估计对这个东西比较熟悉）。递推即可。递推式为 $f_{i,j}=\max(f_{i-1,j},f_{i-1,j-2^{i-1}})$，时间复杂度显然是 $\mathcal O(n \log n)$，显然这个递推式是时间复杂度上最优的。

我们发现一件事情：转移顺序？

显然第一维从 $i$ 还是 $j$ 开始转移都没毛病。然而，显然先枚举 $j$ 的做法难以处理“在 ST 表之后添加数字”，而先枚举 $i$ 可以，所以通常情况下我们先枚举 $j$。

## 查询

现在可重复贡献的优势就来了。

若 $x,y$ 是两个集合，则显然 $\displaystyle\max\left(\max_{i \in x} i,\max_{i\in y}i\right)=\max_{i \in x \cup y}i$。

那么如果 $x \cup y = [a,b]$，那么取 $k=2^{\log(b-a+1)}$，构造 $x=[a,a+2^k-1]$ 与 $y=[b-2^k+1,b]$，容易发现满足条件，且都可以使用 ST 表中的元素表示。时间复杂度取决于 $k$ 的计算复杂度，通常视为 $\Theta(1)$。

# 正确性证明

好好看文章。

已经在上面详细解释了。

# 代码实现

```cpp
#include <bit>
#include <cstdio>
#include <algorithm>

using namespace std;

int a[100005], st[25][100005];
enum class qwq123_mode
{
	GetTable,
	GCCInnerFunc,
	BitWidth,
	Binary,
	Default = GCCInnerFunc
};
constexpr int value_range = 100005; // 值域
unsigned qwq123(unsigned x)
{
	switch(qwq123_mode::Default)
	{
	case qwq123_mode::GetTable:
		// 定义表类型，原因见下
		class TableType
		{
			int* table;
		public:
			TableType()
			{
				table = new int[value_range + 1];
				table[1] = 0;
				for (int i = 2; i <= value_range; i++)
				{
					table[i] = table[i >> 1] + 1;
				}
			}
			int get(int x) { return table[x]; }
		};
		// 使用语法糖实现自动打表
		// 利用 static 变量第一次声明自动初始化
		static TableType tt;
		return tt.get(x);
	case qwq123_mode::GCCInnerFunc: return 31 - __builtin_clz(x);
	case qwq123_mode::BitWidth: return bit_width(x) - 1;
	case qwq123_mode::Binary: 
		// 通常来讲，unsigned 比 int 快
		// 前提是不开编译器优化。聪明一点的编译器
		// 都会把可以用 unsigned 的 int
		// 替换成 unsigned。
		unsigned res = 0;
		// 事实上，应该是 res += 16
		// 但是其实两者等价。不开编译器优化时
		// |= 明显更快。
		if (x >> 16) { res |= 16; x >>= 16; }
		if (x >> 8) { res |= 8; x >>= 8; }
		if (x >> 4) { res |= 4; x >>= 4; }
		if (x >> 2) { res |= 2; x >>= 2; }
		// 最后不需要调整 x 了。
		if (x >> 1) { res |= 1; }
		return res;
	}
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", st[0] + i);
		for (int j = 1; (i - (1 << j)) >= 0; j++)
		{
			st[j][i] = max(st[j - 1][i], st[j - 1][i - (1 << (j - 1))]);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		unsigned x, y;
		scanf("%u%u", &x, &y);
		unsigned len = y - x + 1, llen = qwq123(len), lllen = 1 << llen;
		printf("%d\n", max(st[llen][x + lllen - 1], st[llen][y]));
	}
	return 0;
}
```

[record](https://www.luogu.com.cn/record/205111445)。

---

## 作者：xuhoayang (赞：0)

## 题目介绍

要求一段区间 $l$ 至 $r$ 的最大值，$n\le10^5$ 且 $m\le2\times10^6$，数据偏大，如果使用暴力搜索肯定会超时，这时，就应用一个较为便捷的算法。

## 定义：倍增思想

简而言之，求从某一点向后跳 $2^j$ 这个区间内的某一信息，如区间和，区间最大值等，可以较为快速地求得答案。

## 利用倍增思想构造 ST 表

|  1  |  2  |  3  |  3  |  4  |  5  |  6  |  7  |  2  |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |

如图，下面一行表示下标，上面一行表示对应的值，当你要求 $l=3,r=7$ 时对应的最大值时，可以预先处理好其中前半部分及后半部分最大值并求最大，作为该区间最大值，这时定义一个 $f_{i,j}$ 表示下标为 $i$ 的点向后跳 $2^j$ 这部分区间的最大值，$j$ 会不断变大，这就是倍增，比如，$f_{3,2}$ 就表示例子的答案 $6$，等价于 $\max(f_{3,1},f_{5,1})$，抽象成代码如下。

```cpp
f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
```

这是数组的预处理，但对于向后跳 $2^j$ 中 $j$ 的取值，需要提前存从 $1$ 跳到某一节点需要的 $j$，方便表示区间，如下。

```cpp
for(int i=2; i<=n; i++) {
		lg[i]=lg[i/2]+1;
	}
```

## 代码实现

注意，最后求某一区间的最大值时还需要对半再求一次，AC 代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int f[N][22],lg[N],n,m;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main() {
	n=read(),m=read();
	for(int i=1; i<=n; i++) {
		f[i][0]=read();//快读
	}
	for(int i=2; i<=n; i++) {
		lg[i]=lg[i/2]+1;//提前处理lg
	}
		for(int j=1;j<=21;j++){
			for(int i=1;i<=n-(1<<j)+1;i++){//注意范围
				f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);//预处理最大值
			}
		}
		while(m--){
			int l=read(),r=read();
			int cha=lg[r-l+1];//记录跳上去的j
			printf("%d\n",max(f[l][cha],f[r-(1<<cha)+1][cha]));//求最大值
		}
	return 0;
}
```

---

## 作者：Xiaonao_Dali (赞：0)

#### 算法说明
这是一个非常经典的 ST 表问题。我们可以看到限制时间可知，这个模版题对我们的查询复杂度需要控制在 $O(1)$，所以我们可以分如下几步。ST 表一般分为建表和查询两步。
#### 第一步-建表
第一步，建表，写 ST 表首先是要建表，根据题可知，他要求我们求的是区间最大值，那么我们需要建的是最大值的 ST 表。具体实现代码如下，时间复杂度是 $O(N \cdot \log N)$，其实在这里有一点倍增法的思路在内了。
#### 第一步正确性说明
而在这里，需要一点点的正确性的证明：如果该区间长度为 $len$，那么也存在 $2^p=len$，那么有 $k=\lfloor p \rfloor$，而此时显而易见 $2^k \le len$，那么 $2^{k+1} \ge len$。因此可以得出 $k= \lfloor \log_2 len \rfloor$。\
那这很显然会有一定区间重合，但这并不影响答案。
#### 建表步骤代码实现
```cpp
void jb(){
	for(int i=1;i<=n;i++) F[i][0]=a[i];
	int k=log2(n);
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n-(1<<j)+1;i++){
			F[i][j]=max(F[i][j-1],F[i+(1<<(j-1))][j-1]);
		}
	}
} 
```
#### 第二步-查询
第二步，查询，我们可以通过一个公式去得出他的结果。我们可以知道他可以在 $O(1)$ 的复杂度的查询时间，且我们可以通过 `max(F[l][k],F[r-(1<<k)+1][k]);` 进行一次求值。那么我们就需要考虑 $k$ 的取值了。由于实在区间内所以必有左区间与右区间，假设左区间位置为 $l$，右区间为 $r$，则我们可以得出区间内个数有 $r-l+1$，那么我们可以立即得出代码。
#### 证明
这里稍微证明了一下，我们在不断右移时知道仅剩下一位，那么右移次数即为答案，每次除以 $2$ 后进行向下取整，相当于右移一位，那么由于前面在建表，也就是预处理，就已经求出来了，所以直接进行调用再加 $1$ 即可。
#### 查询步骤代码实现
```cpp
int cx(int l,int r){
	int k=log2(r-l+1);
	return max(F[l][k],F[r-(1<<k)+1][k]);
}
```
#### 整合代码
根据上述两步，那么我们可以得出下列代码，注意建表是需要把所有待处理的数输入好以后在进行建表。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int F[100005][25];
int a[100005];
int x,y;
void jb(){
	for(int i=1;i<=n;i++) F[i][0]=a[i];
	int k=log2(n);
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n-(1<<j)+1;i++){
			F[i][j]=max(F[i][j-1],F[i+(1<<(j-1))][j-1]);
		}
	}
} 
int cx(int l,int r){
	int k=log2(r-l+1);
	return max(F[l][k],F[r-(1<<k)+1][k]);
}
int main() {
	cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    jb();
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        cout<<cx(x,y)<<endl;
    }
     return 0;
}
```
#### 快读
但可以那份发现超时了，具体请见[链接](https://www.luogu.com.cn/record/215145637)，那么我们可以发现，我们没法在该算法上的时间复杂度进行优化，只能在输入输出进行优化，由于题目所给的函数不会用，所以我将使用如下 $3$ 行代码进行优化输入输出。
```cpp
   ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
```
所以将这三行贴入那份代码,我们可以就可以通过本题了。务必要注意的是，需要在主函数的前三行去贴，才能保证每次输入均能被优化。这三行加入后，即可得到完美的[正解](https://www.luogu.com.cn/record/216673935)。提示的已经很明显了。那么就可以得出如下代码。
#### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int F[100005][25];
int a[100005];
int x,y;
void jb(){
	for(int i=1;i<=n;i++) F[i][0]=a[i];
	int k=log2(n);
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n-(1<<j)+1;i++){
			F[i][j]=max(F[i][j-1],F[i+(1<<(j-1))][j-1]);
		}
	}
} 
int cx(int l,int r){
	int k=log2(r-l+1);
	return max(F[l][k],F[r-(1<<k)+1][k]);
}
int main() {
 ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    jb();
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        cout<<cx(x,y)<<endl;
    }
     return 0;
}
```
#### ST 表补充说明
但是做 ST 表时，需要注意，就需要静态区间的，如果有变动，就非常占时间，因为动态可能导致数会发生变化，从而导致 ST 表需要重新建表，但因为题目说是静态区间的，所以可以使用 ST 表完成本题。

---

