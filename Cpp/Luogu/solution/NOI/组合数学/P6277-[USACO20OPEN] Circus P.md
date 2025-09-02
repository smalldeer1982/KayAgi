# [USACO20OPEN] Circus P

## 题目描述

Farmer John 马戏团中的 $N$ 头奶牛正在为即将到来的演出做准备。演出全部在一棵节点编号为 $1\ldots N$ 的树上举行。演出的“初始状态”被定义为一个整数 $K$（$1\leq K\leq N$）使得奶牛 $1\ldots K$ 分布在树上的节点上，并且没有任何两头牛位于相同的节点。

在一场演出中，奶牛们可以“移动”任意次数。在一次“移动”中，一头奶牛可以从自己当前所处的节点移动到一个未被占据的相邻节点。如果一个状态可以通过一系列移动到达另一个状态，我们就称这两个初始状态是等价的。

对于每一个 $1\leq K\leq N$，你需要帮助奶牛确定有多少类等价的初始状态。即选出最多的起始状态数目，使得它们两两不等价。由于数字可能很大，所以只需输出答案 $\bmod \ 10^9+7$ 的结果。




## 说明/提示

#### 样例 $1$ 解释：
对于 $K=1$ 和 $K=2$，任何两个状态都可以互相到达。

然后考虑 $K=3$，令 $c_i$ 表示奶牛 $i$ 的位置，则状态 $(c_1,c_2,c_3)=(1,2,3)$ 等价于状态 $(1,2,5)$ 和 $(1,3,2)$，但不等价于状态 $(2,1,3)$。

-----

对于 $100\%$ 的数据，保证 $1 \le N \le 10^5$。

共 $20$ 个测试点，其中 $1\sim 2$ 为样例，其余性质如下：

对于测试点 $3 \sim 4$，满足 $N \leq 8$。  
对于测试点 $5 \sim 7$，满足 $N \leq 16$。  
对于测试点 $8 \sim 10$，满足 $N \leq 100$，且这个树为“星形”，最多有一个度数大于 $2$ 的节点。  
对于测试点 $11 \sim 15$，满足 $N \leq 100$。  
对于测试点 $16 \sim 20$，无特殊限制。

------

出题人：Dhruv Rohatgi

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
3 5```

### 输出

```
1
1
3
24
120```

## 样例 #2

### 输入

```
8
1 3
2 3
3 4
4 5
5 6
6 7
6 8```

### 输出

```
1
1
1
6
30
180
5040
40320```

# 题解

## 作者：xtx1092515503 (赞：26)

（本题解部分借鉴于[这里](https://blog.csdn.net/qq_39972971/article/details/105344133)，但是自己加入了部分感性的理解）

神题。

考虑我们现在树上有$k$头牛。它们无论散布在树的什么地方，我们**总可以移动某些牛，使得这$k$头牛位于树上的$1\dots k$号点**。这是非常显然的。


------------

我们考虑一下，假设位置$(x,y)$上的牛是可以在**不改动其它位置上的牛**的前提下完成**交换**的，我们把它称作“**交换关系**”（注意这一名词是针对**位置**的，不针对位置上到底是哪头牛）。则如果位置$(x,y)$与位置$(y,z)$都具有“交换关系”，那么，位置$(x,z)$也将具有交换关系，因为我们可以先交换位置$(x,y)$，再交换$(y,z)$，再交换$(x,y)$达到交换。换句话说，“交换关系”这种性质，具有**可传递性**。

则我们如果把“交换关系”看作边的话，它们将会构成许多**团（完全图）**。设这些团的大小为$s_i$，则有$k$头牛时的答案即为$\dfrac{k!}{\sum s_i!}$。


------------


现在我们考虑一下，什么情况下两个位置$(x,y)$会具有“交换关系”。

我们不妨想一想，假如你正常地想调换两个位置，你会怎么做？

我们画出图来：

![](https://cdn.luogu.com.cn/upload/image_hosting/ef0kqtfd.png)

假设我们要交换位置$3$和$5$的牛，应该怎么办？

先把一头牛移到$1$等待，然后再移动另一头牛。

这启发我们在移动牛时需要**在分叉的路径上等待**。

也就是说，在一条直线上的牛是不可能交换的。只有有“分叉”的地方才能完成交换。

------------


什么样的地方不存在“分叉”呢？

对，一条路径。

我们定义一条“**链**”为一条路径，使得路径两端的点的度数都不等于$2$，而链上其它点的度数都等于$2$。

典型的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/zzj9igcd.png)

$(3-4-5-6)$是一条链，链的两端是子树$3$与子树$6$。（实际上，如$(2-11-12)$，$(7-9)$都是链）。

我们来看一下更抽象的草图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ptqy8iam.png)

我们设左边子树有$\color{green}{A}$个点，右边子树有$\color{orange}{B}$个点，链上有$\color{red}{C}$个点（注意链两段的点既属于链，又属于子树）。

则如果$\color{red}k<(A-1)+(B-1)$的话，左右子树的点就可以任意交换。

我们感性理解一下：

首先，将所有$k$个点全都移到$A$子树或$B$子树中。则此时链上没有任何点（包括链两段），并且两颗子树中**至少有一个空隙**。

则这一个空隙，就可以成为我们之前提到的“**等待**”处，进行交换。

而只要能完成一次“交换”，则所有位置都可以交换。

（感性理解一下吧……严谨的证明我自己都看不懂……）

因为$(A-1)+(B-1)=N-C$，因此只要$k<N-C$，两边子树就是可交换的。


------------

我们考虑删去所有满足上述要求的链上的边。如果从大到小地枚举$k$的话，则删边就会变成加边，就可以使用并查集维护联通块。

考虑对于一坨联通块，有多少个外部节点可以通到它。设$(a_i,b_i)$为一条链，使得链的一端在块内，一端在块外。再设$B_i$为该链通到的另一端的子树大小。

则能通到该联通块的节点数量为

$$k-\sum\limits_{(a_i,b_i)}(k-B_i-1)$$

（感性理解：外层用$k$减去的那一大坨，是通不到的点的数量；而内层用$k$减去的，则是对于当前链$(a_i,b_i)$来说，能通到联通块内的数量。很明显这样做可能会重复计算，但估计容斥容斥就出来了？）

------------

我们对于每个联通块，维护它内部的边数量$ins$与它周围被切断的边数$out$。

则按照实际意义化简，我们得到了

$$k-(n-ins-1)+(n-k-1)out$$

理解：

$(n-ins-1)$是外部的点数量（注意$ins$是边数）。我们一开始假设这所有外部的点全部通不到）

$out$是被切断的边数，就是上述的$(a_i,b_i)$的数量。乘上$(n-k-1)$是子树中原本的$k$个点数量，再加上需要空出来的那个“等待区”的大小。这是$(n-ins-1)$中多减去的那些点。

再套上我们一开始得出的那个公式$\dfrac{k!}{\sum s_i!}$，则我们得出的那个$k-(n-ins-1)+(n-k-1)out$的式子就是分母中的$s_i$。通过预处理阶乘和阶乘的逆元，我们可以直接应用公式。


------------


最后是统计答案。直接枚举每个联通块即可，不必担心复杂度，因为所有时刻的联通块数量是$O(n)$的（联通块数量与 $\sum\text{链长}$ 是同级别的）。

复杂度分析：瓶颈在于添加上符合要求的链时，为了方便在$k$递减时直接处理要排序。如果用桶排，复杂度就是$O(n)$的。这里为了图方便，使用的是$O(n\log n)$的常规排序。然后是并查集，复杂度是$n\alpha(n)$的。这里为了方便，没有按秩合并，因此仍然是$O(n\log n)$的。另一个瓶颈就是维护仍然存在的联通块标号，只能采取平衡树等在$O(n\log n)$内通过。但是我不小心敲的是```vector```，理论复杂度是$O(n^2)$的，会被菊花图卡掉，但是没有被卡，大家敲的时候用普通```set```即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int ksm(int x,int y){
	int z=1;
	for(;y;x=1ll*x*x%mod,y>>=1)if(y&1)z=1ll*z*x%mod;
	return z;
}
int n,fac[100100],inv[100100],res[100100];
vector<int>g[100100],key;
struct dsu{
	int fa,ins,out;
}a[100100];
void init(){
	for(int i=1;i<=n;i++)if(g[i].size()!=2)a[i].fa=i,a[i].out=g[i].size(),key.push_back(i);
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[n]=ksm(fac[n],mod-2);
	for(int i=n-1;i>=0;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int find(int x){
	return a[x].fa==x?x:a[x].fa=find(a[x].fa);
}
void merge(int x,int y,int z){
	x=find(x),y=find(y);
	if(x==y)return;
	key.erase(lower_bound(key.begin(),key.end(),y));
	a[x].ins+=a[y].ins+z-1,a[x].out+=a[y].out-2,a[y].fa=x;
}
struct path{
	int x,y,z;
	path(int u,int v,int w){x=u,y=v,z=w;}
	friend bool operator <(const path &x,const path &y){
		return x.z<y.z;
	}
};
vector<path>paths;
void getpath(int x,int fa,int len,int from){
	if(g[x].size()!=2){
		if(from)paths.push_back(path(from,x,len));
		len=1,from=x;
	}
	for(auto y:g[x])if(y!=fa)getpath(y,x,len+1,from);
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),g[x].push_back(y),g[y].push_back(x);
	init();
	getpath(key.front(),0,0,0);
	sort(paths.begin(),paths.end());
	for(int i=n-1,j=0;i;i--){
		while(j<paths.size()&&i<n-paths[j].z)merge(paths[j].x,paths[j].y,paths[j].z),j++;
		res[i]=fac[i];
		for(auto x:key)res[i]=1ll*res[i]*inv[i-(n-a[x].ins-1)+a[x].out*(n-i-1)]%mod;
	}
	res[n]=fac[n];
	for(int i=1;i<=n;i++)printf("%d\n",res[i]);
	return 0;
}
```


------------

代码：



---

## 作者：syzf2222 (赞：9)

不妨假设这些点正好在 $1\sim k$ 上，若 $x,y$ 能够在不影响其他点位的情况下交换，则 $x,y$ 之间连边，不难发现有传递性，则会连成若干个团，则答案为 $\dfrac{k!}{\prod [\text{团大小}]!}$。

考虑点 $x,y$ 何时能够互通，它必然需要一个地方腾挪。而一个二度点显然是不能腾挪的。

考虑一条路径，两端不为二度点，中间全为二度点。设其左端点的子树大小为 $A$ 右边为 $B$ 链上有 $C$ 个点，显然有 $A-1+B-1+C=n$。

当 $k>A-1+B-1$ 时，恒有 $k-(A-1)-(B-1)$ 个点在链上，则左边 $A-1$ 个点和中间 $k-(A-1)-(B-1)$ 和右边 $B-1$ 个点互不相通。$k=A-1+B-1$ 时亦然，只是中间不存在点而已。否则我们一定可以交换链两端的点。

若 $x\to y$ 路径上所有的链都满足 $k<A-1+B-1$ 则可以互通。

我们把树上的路径缩起来形成一棵新树，把所有 $k\geqslant A-1+B-1=n-C$ 的边断掉，则剩下的每个连通块就代表一个团。我们计算这个团的大小。

这个团的大小是由与其相连的断边刻画的，每条断边会规定一些一定不能与其交换，即

$
k-\sum (k-(B-1))=k-\sum (k-n+(A-1)+C)$

$=k-(k+1-n)[\text{断边个数}]+n-[\text{连通块大小}]
$

于是从大到小枚举 $k$，然后每次加路径维护每个连通块的大小和断边个数即可。

注意到每个时刻连通块个数为断边个数加一，长为 $l$ 的断边恰好断 $l$ 个 $k$，于是任意时刻连通块个数的和是 $\mathcal O(n)$，于是整体时间复杂度就是 $\mathcal O(n\log n)$ 的。

---

## 作者：cff_0102 (赞：7)

当 $k$ 固定时，无论怎么样，所有初始状态都一定可以通过操作把所有奶牛堆到同样的一些点上（例如 $1\sim k$ 号点）。

这样，如果 $i$ 和 $j$ 号奶牛能在不改变其它奶牛位置的情况下交换位置（后面称为“成功交换”），那么对应的两种情况就是等价的。

不难发现这种关系具有传递性，即如果 $i$ 能和 $j$ 成功交换，$j$ 和 $k$ 能成功交换，那么 $i$ 和 $k$ 就能成功交换：先交换 $i$ 和 $j$，再交换已经到原来 $j$ 位置上的 $i$ 和 $k$，接着再交换在原来 $i$ 位置上的 $j$ 和在原来 $j$ 位置上的 $k$。

若两个奶牛 $i,j$ 可以成功交换，我们就在一个图上给 $i,j$ 连边，那么最后的图一定由若干个团 $cl_1,cl_2,\dots$ 组成。

如果我们知道这个图上每个团的大小 $sz_{cl_i}$，那么这个 $k$ 对应的答案就应该是 $\dfrac{k!}{\prod\limits_{i}sz_{cl_i}!}$。其中阶乘和阶乘逆元可以预处理。

---

考虑怎么样交换中间没有被其它奶牛挡住的两头奶牛的位置：

![](https://cdn.luogu.com.cn/upload/image_hosting/w5xt1vsw.png)

首先，两头奶牛之间的路径上所有点的度数一定大于等于 $2$。要在两头奶牛的路径中间找到一个度数大于 $2$ 的点，先把一头奶牛移到那里的分叉，接着把另一头奶牛移到第一头奶牛原本的位置，再把第一头奶牛移到第二头奶牛原本的位置即可。这样的两个**点**（指固定不动的位置，而不是奶牛）称为可交换点。如果两个点之间的路径没有度数大于 $2$ 的点，则这两个点是不可交换点。在两个不可交换点上的奶牛，除非其中一个可以退到一个连接的不被其它奶牛挡住的点（后面称这些点为“自由点”）的数量 $>2$ 的点，否则它们不可能可以交换。

定义树上的一条“链”为两端度数不等于 $2$，中间所有点度数都为 $2$ 的一条路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/ump55u7o.png)

考虑树上的一条链（如上图），它可以把树分成三个部分：

1. 链上左侧的点左边的子树，设其中的点数为 $A$；
2. 链上右侧的点右边的子树，设其中的点数为 $B$；
3. 这条链，设其中的点数为 $C$。

- 由于奶牛的位置可以改变，所以 $A,B,C$ 指的是点数而不是奶牛数。

如果 $A-1+B-1=k$（注：不是下图），不难发现被分到这两个子树的奶牛是不能互相交换的：如果链上有一个点，则要交换的话肯定要把链上的奶牛先移到子树中，而此时任何奶牛都无法进一步后退到一个连接的“自由点”的数量 $>2$ 的点后面。

![](https://cdn.luogu.com.cn/upload/image_hosting/sgm9yhxx.png)

而如果 $k<A-1+B-1$ 呢？那么此时就出现了一个连接的“自由点”的数量 $>2$ 的点，通过这个点，两个子树的**所有能到达链上的奶牛**都可以互相交换。

![](https://cdn.luogu.com.cn/upload/image_hosting/lsgu8lf7.png)

我们把中间那条符合 $k<A-1+B-1$ 的链称为“合法链”，表示这个链两端的点一定可以成功交换。反之，则称为“非法链”。如果我们知道一条链的长度为 $C$，那么可以把 $A-1+B-1$ 改写成 $n-C$，更方便计算。

在另一个图中，把所有合法链两端相连，非法链两端不相连，则会形成一个个连通块。对于这些 $k\ge n-C$ 的非法链，存在一些牛把两端的牛的集合分开，这些牛之间就不能交换，在本文开头所说的那个由团组成的图上则会表现为这两个集合中的牛不在一个团里面。而对于合法链，其两端的牛都可以交换，那么其左右两端的牛的集合就在一个团里面。再看上文所说的合法链连接起来的一个个连通块，则不难发现每一个连通块都对应着一个团。

那么只需要求出每个连通块对应的团的大小就可以了。

正如前文所说，对于一条非法链，存在一些牛把两端的牛的集合分开，使得这些牛之间不能交换。那么怎么知道两端的牛的集合的分界具体是怎么样的呢？因为两端的牛的集合要满足内部可交换，而这条非法链使得 $k\ge n-C$，即要么两端的子树一定填满了，要么链上一定有一头牛。对于后者的情况，如果不满足前者，可以直接通过操作把它变成前者的情况；对于前者的情况，那么可以发现这些牛的集合的分界已经自然形成了：

![](https://cdn.luogu.com.cn/upload/image_hosting/rayxtbz8.png)

只要 $k\le n-2$，左右两侧子树前端的几个点就一定可以在内部互相交换，而中间的牛不可能参与进来。而 $k>n-2$ 的时候所有链都是非法链，左右两侧的牛的集合都不可能大于 $1$，其内部必然“可以互相交换”。

因此，一条非法链所划分的集合边界，就在两边子树都被填满时，链的两端的位置（反正参考上图）。

一条非法边可以确定牛的集合的一部分边界，再根据其它非法边确定这些集合的其它边界，最后就能求出所有牛的集合（即那个图中的团）的大小了。

不过直接划分边界的方法还是太抽象了，具体实现比较困难，有没有简单的实现方法？有的兄弟，有的。考虑换一个求解连通块对应的团的大小的思路，即用牛的总数，减去对于每条非法链，被划到集合外的牛的个数。这样就好算很多了。

假设我们直接枚举每条非法链，且对于每条链已经知道两端的 $A$ 和 $B$（注意这里仍然指的是点数）的值，其中 $B$ 为应该划分到这个连通块外的那一边。$A$ 这一端最多只能堆 $A-1$ 个奶牛，所以另一边划分出去的部分剩下 $k-(A-1)=k-(n-(B+C-1))=k-n+B+C-1$ 个奶牛。对于这个连通块，它的团的大小就是：

$$\begin{aligned}&k-(\sum\limits_{i} k-n+B_i+C_i-1)\\=&k-(\sum\limits_{i} k-n+1+(B_i+C_i-2))\\=&k-(\sum\limits_{i} k-n+1+\sum\limits_{i}(B_i+C_i-2))\\=&k-((k-n+1)\times cnt+(n-siz))\\=&k-(k-n+1)\times cnt-n+siz\\=&k-n+1-(k-n+1)\times cnt+siz-1\\=&(1-cnt)(k-n+1)+siz-1\\=&(cnt-1)(n-k-1)+siz-1\end{aligned}$$

其中 $cnt$ 是这个连通块所连接的非法边的数量，$siz$ 是这个连通块的大小。注意：连通块的大小指的是点的数量，而要计算的团的大小指的是奶牛的数量。

因此只要知道每个连通块的 $cnt$ 和 $siz$ 就可以了。

因为题目要求出所有 $k$ 的答案，因此需要动态维护所有连通块的 $cnt$ 和 $siz$。$k$ 从小到大，非法边会越变越多，则连通块的数量也会越变越多，不容易维护。但是不一定要让 $k$ 从小到大枚举，可以从大到小枚举，最后再把答案倒序输出。这样就可以用并查集维护了。

---

这样，就能知道开头提到的每个团的大小 $sz_{cl_i}$ 了。不过还有个问题，就是它的复杂度是多少？对于每个 $k$，都枚举一次所有连通块（因为 $k$ 在变化导致其它没有参与合并的连通块对应的团的大小也会变化，需要重新计算），复杂度不会炸吗？

考虑一条长度为 $C$ 的非法链，当 $k$ 从 $n$ 开始枚举时，它作为非法链只能持续 $C+1$ 个回合。每条链都只能存活链长 $+1$ 个回合，而每一回合连通块的个数是非法链个数 $+1$，因此 $n$ 回合下来总共的连通块个数其实是 $O(\sum\limits_{每一回合}\text{非法链个数})=O(\sum\limits_{每一条链}\text{链的长度})=O(n)$ 的，不用担心。

可以使用 `set` 维护所有连通块。最终时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5,mod=1e9+7;
int n;
// 维护连通块
int fa[N],siz[N],cnt[N];
set<int>st;
int find(int x){
	if(x==fa[x])return fa[x];
	return fa[x]=find(fa[x]);
}
void merge(int x,int y,int c){// c is the length of the link
	x=find(x),y=find(y);
	fa[x]=y;
	siz[y]+=siz[x]+c-2;
	cnt[y]+=cnt[x]-2;
	st.erase(x);
}
// links
struct links{
	int u,v,c;
}l[N];
vector<int>g[N];
// setup
int ksm(int a,int b){
	int s=1;
	while(b){
		if(b&1)(s*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return s;
}
int fac[N],ifac[N],d[N];
void setup(){
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=(fac[i-1]*i)%mod;
	ifac[N-1]=ksm(fac[N-1],mod-2);
	for(int i=N-2;i>=0;i--)ifac[i]=(ifac[i+1]*(i+1))%mod;
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
		d[u]++;d[v]++;
	}
	for(int i=1;i<=n;i++){
		if(d[i]!=2){// 刚开始所有边都是非法边，所以 cnt 必为 d[i]，siz 必为 1
			fa[i]=i;
			siz[i]=1;
			cnt[i]=d[i];
			st.insert(i);
		}
	}
}
int id;
void dfs(int x,int f,int hd,int c){
	// hd：当前这个链的另一端 c：当前这个链的长度
	if(d[x]!=2){// 这个点的度不是 2，则是一个链的端点 
		if(hd)l[++id]={hd,x,c};
		c=1;
		hd=x;
	}
	for(int y:g[x])if(y!=f){
		dfs(y,x,hd,c+1);
	}
}
int ans[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	setup();
	// 搞链
	dfs(*st.begin(),0,0,0);// 从 *st.begin() 开始可以保证扫的根是链的端点
	sort(l+1,l+1+id,[](links x,links y){
		return x.c<y.c;
	});
	ans[n]=fac[n];
	int x=1;
	for(int k=n-1;k>=1;k--){
		while(x<=id&&k<n-l[x].c){
			merge(l[x].u,l[x].v,l[x].c);
			x++;
		}
		ans[k]=fac[k];
		for(int i:st){
			(ans[k]*=ifac[(cnt[i]-1)*(n-k-1)+siz[i]-1])%=mod;
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：ZnPdCo (赞：4)

发现交换操作有可传递性：如果 $(x,y)$ 两个**位置**（注意我们这里是位置而不是指牛）可以互相交换，$(y,z)$ 两个位置也可以互相交换，那么 $(x,z)$ 两个位置必定是可以互相交换的。因为可以先交换 $(x,y)$，再交换 $(y,z)$，最后再次交换 $(x,y)$。

---

我们发现如果当前如果有 $k$ 头牛，无论它们在哪些位置，我们总是可以移动它们到树上的 $1\cdots k$ 号位置。也就是说，如果**忽略标号**的话，任意两个状态都是直达的。

所以我们固定这 $k$ 头牛在 $1\cdots k$ 号位置，计算有多少种有标号的排列状态。

假如 $(x,y)$ 两头**牛**能够在不影响其它牛的情况下交换，我们就给它们连一条边，发现最后面会形成很多个团（完全图）。根据交换操作的可传递性，那么每一个团的情况肯定是可以互相到达的。

我们设这些团大小为 $s_i$，那么答案就是 $\frac{k!}{\prod (s_i!)}$。

---

考虑怎样的情况下两头牛是可以交换的：

首先，我们可以把牛从位置 $1\cdots k$ 移出来到任意位置。

然后在不影响其它牛的情况下交换两头牛。

最后，按照相反的顺序移动回位置 $1\cdots k$。

此时，两头牛就是可交换的，连一条边。

---

考虑怎样在不影响其它牛的情况下交换两头牛：

发现当在一条**没有牛的链**且**出现一个分支**时，两头牛可以交换：

![](https://cdn.luogu.com.cn/upload/image_hosting/znhwvyl3.png)

如上，位置 $1$ 上的牛和位置 $6$ 上的牛交换时，可以在这个**没有牛**且**有一个分支** $4$ 的链 $2\to5$ 上进行交换。先把 $1$ 上的牛移动到 $4$ 上，再把 $6$ 上的牛移动到 $1$ 上，最后把移动到 $4$ 上的牛移动到 $6$ 上。

总结可以交换的规律：

1. 没有牛的链；
2. 有一个分支（有一个位置度数大于二）。

---

我们将其拓展一下：

在一个**中间都是二度点，两端都是非二度点的链**上，设两端不包括链的树的大小分别为 $a$、$b$，链的长度为 $c$（它们都包括两端的点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/1wmy2gx6.png)

如上，$1\to8$ 就是合法的**中间都是二度点，两端都是非二度点的链**。其中 $a=5$（位置 $1$，$2$，$3$，$4$，$5$ 都是左端的树），$b=5$（位置 $8$，$9$，$10$，$11$，$12$ 都是右端的树），$c=4$（位置 $1$，$6$，$7$，$8$ 都是中间的链）。

我们发现，当 $k\le(a-1)+(b-1)-1$ 时，两端的树上的每一个位置都可以互相交换，**也就是能到达左端的牛和能到达右端的牛一定可以交换**，我们对这两头牛连边。

原理：将 $k$ 头牛任意的移动到两颗树上，留下一个空位置作为**交换的分支**，然后树上的任意两头牛都可以通过这个**分支**和**没有牛的链**进行交换。

总结可以交换的规律：$k<(a-1)+(b-1)$，也就是 $k<n-c$。

---

发现，若 $(x,y)$ 是满足这个条件的一条链，也就是能到达 $x$ 的牛能和能到达 $y$ 的牛交换。以及若 $(y,z)$ 也是满足这个条件的一条链，那么能到达 $x$ 的牛能肯定也能和能到达 $z$ 的牛交换。

也就是说，我们链的两端可以互相连接形成很多个连通块。

我们可以把每个满足交换条件，也就是 $k<n-c$ 的链的两端连接起来，因为可以到达这两个位置中的一个的牛就可以和能到达另一个位置的牛交换，所以说，我们计算能到达这些点的牛的个数，即可得到 $s_i$，也就是团的大小。

因为当 $k$ 从小到大枚举时，$k<n-c$ 也就是 $c<n-k$ 的边是越来越少的，不好维护。考虑时光倒流，将 $k$ 从大到小枚举时，$c<n-k$ 的边将会越来越多，用并查集即可维护。

---

回到刚刚那个问题，怎么计算能到达这些点的牛的个数？

正難则反，我们可以计算出无法到达这个连通块的牛的个数，再用牛的总数 $k$ 减去即可。

如果 $a_i\to b_i$ 不是一条满足上面交换条件的链，设连通块外的树的大小为 $a_i$，连通块内树的大小为 $b_i$，链的长度为 $c_i$。

那么我们能够进入到这个联通块的最多只有 $b_i-1$ 头牛，也就是把连通块内树全部填满，那么还有 $k-(b_i-1)$ 的牛无法与之交换。

那么总共的可到达的节点数量为：

$$
\begin{aligned}
k-\sum_{a_i\to b_i}(k-(b_i-1)) &= k-\sum_{a_i\to b_i}(k-(n-a_i-(c_i-1))) \\
&= k-\sum_{a_i\to b_i}(k-n+a_i+c_i-1) \\
\end{aligned}
$$

发现 $a_i+c_i-1$ 为“联通块内子树” 外的点减一（$c_i$ 有一端在连通块内），所以设 $p_i$ 为链方向连通块外的点的个数，有：

$$
\begin{aligned}
k-\sum_{a_i\to b_i}(k-(b_i-1)) &= k-\sum_{a_i\to b_i}(k-n+p_i+1) \\
&= k-(\sum_{a_i\to b_i}(k-n+1)+\sum_{a_i\to b_i}p_i)
\end{aligned}
$$

设连通块大小为 $\text{siz}$，不合法的 $a_i\to b_i$ 个数为 $\text{out}$。我们发现子树外的点数和 $\sum_{a_i\to b_i}p_i=n-\text{siz}$。有：

$$
\begin{aligned}
k-\sum_{a_i\to b_i}(k-(b_i-1)) &= k-([\text{out}](k-n+1)+n-[\text{siz}]) \\
&= k-[\text{out}](k-n+1)-n+[\text{siz}] \\
&= ([\text{out}]-1)(n-k-1)+[\text{siz}]-1
\end{aligned}
$$

我们维护一下连通块的 $\text{out}$ 和 $\text{siz}$ 即可。注意在合并的时候，双方的 $\text{out}$ 和 $\text{siz}$ 都会减小！

---

因为每一次连通块个数等于不合法链的数量加上一，而不合法链只能存活链长的时间，所以均摊之后是 $O(n)$ 的。连通块使用 `set` 维护。所以时间复杂度为 $O(n\log n)$。精细实现能够做到更优。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100010
#define P 1000000007
ll n;
ll deg[N];
ll head[N], nxt[2 * N], to[2 * N], cnt;
ll fa[N], out[N], siz[N];
ll ans[N], fac[N], ifac[N];
set<ll> s;
struct node {
	ll a, b, c;
	node(ll a = 0, ll b = 0, ll c = 0):a(a), b(b), c(c) {}
} edge[N];
ll tot;
void addEdge(ll u, ll v) {
	cnt ++;
	to[cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}
ll find(ll x) {
	if(fa[x] == x) {
		return x;
	}
	return fa[x] = find(fa[x]);
}
void merge(ll a, ll b, ll c) {
	a = find(a), b = find(b);
	fa[a] = b;
	siz[b] += siz[a] + c - 2;
	out[b] += out[a] - 2;
	s.erase(a);
}
void dfs(ll u, ll fa, ll rt, ll c) {
	if(deg[u] != 2) {
		if(rt) {
			edge[++ tot] = node(u, rt, c);
		}
		c = 1;
		rt = u;
	}
	for(ll i = head[u]; i; i = nxt[i]) {
		ll v = to[i];
		if(v == fa) continue;
		dfs(v, u, rt, c + 1);
	}
}
ll qpow(ll x, ll y) {
	if(y == 0) return 1;
	if(y % 2 == 1) return x * qpow(x, y - 1) % P;
	ll tmp = qpow(x, y / 2);
	return tmp * tmp % P;
}
int main() {
	scanf("%lld", &n);
	for(ll k = 1; k < n; k ++) {
		ll u, v;
		scanf("%lld %lld", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
		deg[u] ++;
		deg[v] ++;
	}
	for(ll i = 1; i <= n; i ++) {
		if(deg[i] != 2) {
			fa[i] = i;
			siz[i] = 1;
			out[i] = deg[i];
			s.insert(i);
		}
	}
	dfs(*s.begin(), 0, 0, 0);
	sort(edge + 1, edge + 1 + tot, [&](const auto &x, const auto &y) {
		if(x.c == y.c) {
			if(x.a == y.a) return x.b < y.b;
			else return x.a < y.a;
		}
		return x.c < y.c;
	});
	fac[0] = 1;
	for(ll i = 1; i <= n; i ++) {
		fac[i] = fac[i - 1] * i % P;
	}
	ifac[n] = qpow(fac[n], P - 2);
	for(ll i = n; i >= 1; i --) {
		ifac[i - 1] = ifac[i] * i % P;
	}
	ans[n] = fac[n];
	ll pos = 1;
	for(ll k = n - 1; k >= 1; k --) {
		while(pos <= tot && k < n - edge[pos].c) {
			merge(edge[pos].a, edge[pos].b, edge[pos].c);
			pos ++;
		}
		ans[k] = fac[k];
		for(ll i : s) {
			(ans[k] *= ifac[(out[i] - 1) * (n - k - 1) + siz[i] - 1]) %= P;
		}
	}
	for(ll i = 1; i <= n; i ++) {
		printf("%lld\n", ans[i]);
	}
}
```

---

## 作者：APJifengc (赞：4)

首先容易发现每种等价类的大小一定是相等的，那么最后答案就一定是 $\frac{k!}{size}$，$size$ 表示等价类的大小。

我们考虑两头牛之间能不能交换，发现这种关系是具有传递性的，那么交换的关系图一定会形成若干个团，一个团之间是可以任意交换的。那么最后答案就是 $\frac{k!}{\prod s_i!}$，其中 $s_i$ 表示每个团的大小。

我们考虑什么时候能交换，容易想到一种简单的交换就是在一个度数为三的点上去换。这是一个最基本的交换，只要在任意一个度数大于等于 $3$ 且存在至少两个空位的情况下就可以在这里进行交换。

而整棵树由若干关键点划分成了若干条链，我们考虑一条由两个关键点连起来的一条链上能否进行交换。我们设两端两个关键点的子树大小分别为 $a, b$，中间的链长为 $c$，其中两个端点同时包含在链与子树内，显然有 $(a - 1) + (b - 1) + c = n$。

首先考虑到我们的问题是能够使得两头牛交换且不改变其它牛的位置，但是不改变其它牛的位置这个限制实际上是没有意义的，因为如果某一刻能够使得两头牛交换位置，那么我们再按照一模一样的移动倒着就能把其它所有牛全部还原回去，所以我们实际上只用考虑某一刻能否将考虑的两头牛交换即可。

那么我们考虑链上两头相邻的牛能否交换。直观的想法肯定是让这两个点左边的牛全部往左边的子树里填，右边的牛全部往右边的子树里填，这样这两头牛可以去任意一个关键点的地方去调换位置。而子树内可以包含的牛是有限的，注意到如果左右两棵子树全都填满了，那么此时这两头牛就不能交换了，这时一定有 $k \ge (a - 1) + (b - 1)$，而由此我们又可以推出，存在恰好 $k - (a - 1) - (b - 1)$ 头牛之间是不能交换位置的，而这会导致此时左边的任何点都无法与右边的任何点进行交。

如果 $k < (a - 1) + (b - 1)$，那么说明将所有的牛全部填入子树后，一定存在一棵子树里至少有一个空。考虑链上相邻的两头牛，如果将这两头牛的左边所有牛全部填入左子树，右边所有牛全部填入右子树，那么可以发现存在一个子树至少有两个空，而通过这两个空我们就可以完成这两个点的交换了，也就是说，当 $k < (a - 1) + (b - 1)$ 时，我们可以交换链上任意两头牛的位置。

总结一下，对于一条链，如果 $k \ge (a - 1) + (b - 1)$，那么存在一些牛不能互相交换，同时这些牛将左右两个集合分开，使得左右两个集合之间也不能交换。**这在交换的关系图上意味着，左右两个集合不可能在同一个团内**。而 $k < (a - 1) + (b - 1)$ 时，链上的任意两个点之间都是可以交换的，这说明只要能移动到这条链上的点都是可互相交换的，**这在交换的关系图上意味着，左右两个集合是在同一个团内的**。

这时候问题就清晰了许多了。我们称满足 $k < (a - 1) + (b - 1)$ 的链为合法链，那么整个交换关系图，是由若干条不合法链划分成的若干个团，而合法链将关键点连成了若干个连通块，每个连通块对应着一个团。那么，我们就只需要求出每个团的大小，就能计算出答案了。

首先链合法的条件可以改写成 $k < n - c$，即 $n - k > c$，那么发现如果我们将 $k$ 从大往小枚举，则会依次加入每一条合法链，然后使用并查集即可维护关键点形成的连通块。那么现在问题在于，如何计算出每个连通块对应的团的大小。

团的大小并不好计算，但是我们是容易计算团外面的点数的，于是简单容斥一步就可以了。对于团外面的点数，我们考虑连通块往外连的每一条不合法链，设连通块外的子树为 $a$，连通块内的子树为 $b$，那么我们让所有的牛全部填满子树 $b$，则多出来的点就是这条不合法链方向的不在连通块内的点，这些点的数量等于 $k - (b - 1) = k - (n - c - (a - 1)) = k - n + c + a - 1 = k - n + 1 + p$，其中 $p$ 为不合法链方向的关键点子树大小。将所有的出边求和，容易发现，$\sum p = n - x$，其中 $x$ 为关键点连成的连通块点数，于是总和就是 $n - x + y(k - n + 1)$，拿 $k$ 减去它就是团的点数，即 $(y - 1)(n - k - 1) + x - 1$。但是这个式子里面跟 $k$ 有关系，也就是每个连通块的权值一直在变，这导致我们并不能 $O(1)$ 维护出所有连通块的权值乘积了。但是实际上我们可以直接枚举每一个连通块进行计算答案，因为连通块数量等于不合法链的数量加一，而不合法链存在的时间等于链长，链长总和是 $O(n)$ 的，所以每一时刻下连通块数量的总和也是 $O(n)$ 的。于是我们可以拿链表或者 `set` 维护所有的连通块，每次遍历所有连通块计算答案即可。时间复杂度 $O(n \log n)$ 或 $O(n \alpha(n))$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005, P = 1000000007;
int n;
vector<int> e[MAXN];
set<int> s;
int fa[MAXN], out[MAXN], siz[MAXN];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int u, int v, int w) {
    u = find(u), v = find(v);
    fa[u] = v, siz[v] += siz[u] + w - 2, out[v] += out[u] - 2;
    s.erase(u);
}
vector<tuple<int, int, int>> ed;
void dfs(int u, int pre, int rt, int dep) {
    if (e[u].size() != 2) {
        if (rt) ed.push_back({ dep, rt, u });
        rt = u, dep = 1;
    }
    for (int v : e[u]) if (v != pre) dfs(v, u, rt, dep + 1);
}
int qpow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % P;
        a = 1ll * a * a % P;
        b >>= 1;
    }
    return ans;
}
int fac[MAXN], inv[MAXN];
int ans[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        e[u].push_back(v), e[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) if (e[i].size() != 2) s.insert(i), fa[i] = i, out[i] = e[i].size(), siz[i] = 1;
    dfs(*s.begin(), 0, 0, 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = 1ll * i * fac[i - 1] % P;
    inv[n] = qpow(fac[n], P - 2);
    for (int i = n; i >= 1; i--) inv[i - 1] = 1ll * inv[i] * i % P;
    ans[n] = fac[n];
    sort(ed.begin(), ed.end());
    auto it = ed.begin();
    for (int k = n - 1; k >= 1; k--) {
        while (it != ed.end() && k < n - get<0>(*it)) merge(get<1>(*it), get<2>(*it), get<0>(*it)), it++;
        ans[k] = fac[k];
        for (int i : s) ans[k] = 1ll * ans[k] * inv[(n - 1 - k) * (out[i] - 1) + siz[i] - 1] % P;
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：david0911 (赞：1)

显然不论这些牛的初始位置在哪里，我们都可以将它们移动到某特定的 $k$个位置上，然后计数分配标号的方案数。不妨认为将这些牛移动到编号为 $1,2,\cdots,k$ 的点上。

牛在树上的移动会受到其他牛的限制，有时会被堵死，有时可以互换位置。所以我们只关心某两个位置上的两头牛是否能交换位置。

如果位置 $(x,y)$ 上的牛可以交换位置且不改变其它牛的位置或者可以将其它牛恢复到原位，则称这两个位置有**交换关系**。显然这种关系具有传递性。

我们将这种关系视作一张图上连接 $(x,y)$ 的一条边，那么由于传递性，最终会形成若干个**团**。不妨对将牛排列在 $1,2,\cdots,k$ 位置的标号排列计数。设第 $i$ 个团的大小为 $s_i$，那么答案就是 $\dfrac{k!}{\prod\limits_i (s_i!)}$。这些 $s_i$ 都是在 $k$ 头牛限制下得到的，可以说明 $i\le k$。

现在来刻画这种交换关系在树上表现出的形态。感性上，两个位置想要交换，必然需要一个空位置，来让其中一头牛在上面等待另一头牛移动。

这告诉我们，一条不分叉的路径上，两个位置不能交换。以下定义**链**为两端的点度数不为 $2$，中间的每个点度数都为 $2$ 的一条路径。

不妨将一条链拎起来，称左端点及其下方部分为左子树，设其大小为 $A$，右端点同理，设其大小为 $B$，设链长（含两个端点的点数）为 $C$。显然有等式 $(A-1)+(B-1)+C=n$。

考虑在 $k$ 的限制下，何时可以交换左右子树中的一个点。

可以断言：当且仅当 $k<(A-1)+(B-1)=n-C$ 时，左右子树中的点可以任意交换。

必要性是显然的，若 $k>n-C$，那么链上至少会有 $k-n+C$ 头牛无法交换位置，故左右子树中的点无法交换。若 $k=n-C$，容易验证与前一种情况类似。

充分性可以构造得证。感性理解就是 $k<n-C$ 时，将 $k$ 头牛扔进左右子树后仍有空位，可以利用这些空位完成交换。

以下称一条链是非法的，如果 $C\ge n-k$。

考虑对于固定的 $k$ 算一次答案。我们将 $C\ge n-k$ 的非法链从原图中删去，那么剩下的若干个连通块一一对应着若干个团。

此处应注意区分：**连通块的大小**指树上的点的数量，而**团的大小**指奶牛的数量。

考虑计算一个连通块对应的团的大小。直接算是不好算的，这个团是由与这个连通块相连的非法链刻画的，每条非法链会从这个团中扣掉一部分。不妨用牛的总数 $k$ 减去每条非法链从这个团中划分出去的数量。设一条非法链已知其 $A,B,C$，那么它可以从这个团中划分出 $k-(A-1)=k-(n-(B-1)-C)$ 个点。

那么对于一个连通块，枚举其每一条非法链出边，计算其团的大小。设连通块大小为 $siz$，非法链出边数量为 $cnt$。

$$
\begin{aligned}
k-\sum(k-(n-(B-1)-C))&=k-k\cdot cnt+n\cdot cnt+cnt-(\sum B-1+C-1)-2\cdot cnt\\
&=k-(k-n+1)\cdot cnt-(n-siz)\\
&=(n-k-1)\cdot (cnt-1)+siz-1
\end{aligned}
$$

对每个连通块维护 $cnt$ 和 $siz$，就可以算出对应的团的大小。

从大到小枚举 $k$，就可以改删边为加边，使用并查集维护。上述过程在 $k=n$ 时会越界，要特殊处理 $k=n$ 时的答案，显然这是 $n!$。

注意到这里枚举的复杂度是 $O(\sum\limits_k \text{连通块个数})=O(\sum\limits_k\text{非法链个数})$。考虑每条非法链的贡献，可以得到 $O(\sum\limits_k\text{非法链个数})=O(\sum\limits_k\text{链长})=O(n)$。过程中如果用 `set` 维护，时间复杂度 $O(n\log n)$。

---

## 作者：Felix72 (赞：0)

吐槽：有些题解打着“感性理解”的幌子给出容易引发歧义的描述，甚至还出现了错误的结论和复杂度错误的代码，素质不高。

可以看出答案仅仅和奶牛之间的相对位置相关。对于两头奶牛 $(i, j)$，他们可能可以通过一系列操作交换位置，这时他们的相对位置就无关紧要；也有可能他们一定不能交换位置，此时他们就是独立的。定义图 $G = \{(x, y) | x, y \  \text{can be swapped}\}$，则 $G$ 由若干连通块组成，我们关心的就是每个连通块的大小。

**（注意，整篇题解中我们都不关心哪头奶牛在哪个位置。这是因为仅仅知道所有连通块的大小就可以计算出答案。）**

尝试思考 $(x, y)$ 有边的条件，即 $x, y$ 为什么能被交换。我们刚学编程时就知道交换的道理是这样的：$t \larr x, x \larr y, y \larr t$。相似的，我们尝试在图上找到合适的 $t$ 节点，使得 $x, y$ 可以使用 $t$ 作为中转。

一个明确的事实是链上不存在合适的 $t$。比如你不可能交换下图的两头奶牛。（我们用加粗节点表示这上面有奶牛）

![](https://cdn.luogu.com.cn/upload/image_hosting/hb8j5yfu.png)

当存在度数 $\neq 2$ 的节点时，才存在交换的**可能**。比如下面这两张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/d6u8jbik.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/o3gmy69v.png)

$1 - 2 - 3$ 为一条链，两边看作子树。我们发现第一张图的左右两边存在可以交换的节点，但是第二张图不存在。究其原因，是奶牛太多了，填满了左右两棵子树，使得我们找不到合适的 $t$ 节点了。

于是我们声称：令一条极长链（除了端点外节点度数均是 $2$）左右两棵子树的大小分别为 $A, B$，则当 $k < (A - 1) + (B - 1)$ 时，一定存在**某一对** $(x, y)$，使得 $x$ 在左子树，$y$ 在右子树，且 $(x, y) \in G$，此时称这条链为 $1$ 类链；当 $k \geq (A - 1) + (B - 1)$ 时，必然不存在这样的 $(x, y)$，此时称这条链为 $2$ 类链。

注意这个加粗的“某一对”。这表示并不是所有节点都能任意交换的，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/xbrg21d5.png)

这张图中 $11$ 号节点的奶牛不可能能和 $7$ 或 $6$ 的奶牛换位。

（有题解在这里给出的错误结论是“左右子树的节点可以任意换位”，还说要感性认识这一点，严谨证明看不懂之类的话。他当然看不懂，因为严谨证明是不存在的）

现在我们可以感受到，一条 $1$ 类链只说明了“链的两个端点的奶牛处于同一个连通块中”，若要分析两棵子树内部奶牛能否交换，还得递归分析这个子树的结构；而一条 $2$ 类链直接否定了链两端任何节点相互连通的可能性，干脆利落。

这引导我们从 $2$ 类链入手分析：是否可以对于某一个点和一个固定的 $k$，先假设这个点所在连通块大小就是 $k$，然后再减去与这个点所在连通块相连接的 $2$ 类链造成的一定不能在连通块中的节点呢？答案是肯定的。

这是因为对于任意一种初始的奶牛状态和一条两边子树大小为 $A, B$ 的 $2$ 类链，我们一定能准确地指出，有 $k - (A - 1)$ 头奶牛必定不在左端点所在的连通块，且有 $k - (B - 1)$ 头奶牛必定不在右端点所在的连通块。由于 $2$ 类链 $k \geq (A - 1) + (B - 1)$ 的特性，你会发现这 $k - (A/B - 1)$ 头奶牛的编号是**固定的**，这就保证了不重不漏。

考虑到一条链一条链的加比较麻烦，我们倒过来一条链一条链地删，这可以用并查集维护。总复杂度为 $O(n \log n)$，优化后可以做到 $O(n \alpha(n))$。

```cpp
/* K_crane x N_Cat */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 100010, mod = 1e9 + 7;
typedef pair < int, int > PAIR;
long long fac[N], inv[N];
inline long long qpow(long long a, long long b)
{
	long long res = 1;
	while(b)
	{
		if(b & 1) res = res * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return res;
}
inline long long C(int n, int m) {return fac[n] * inv[m] % mod * inv[n - m] % mod;}
inline void init_math()
{
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= 100000; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[100000] = qpow(fac[100000], mod - 2);
	for(int i = 99999; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}

int T = 1, n, deg[N], fa[N][22], siz[N], dep[N]; vector < int > tr[N];
long long res[N];

int seq[N * 2][22], sn, lft[N];
inline int LCA(int x, int y)
{
	if(lft[x] > lft[y]) swap(x, y);
	int k = __lg(lft[y] - lft[x] + 1);
	if(dep[seq[lft[x]][k]] <= dep[seq[lft[y] - (1 << k) + 1][k]])
		return seq[lft[x]][k];
	else return seq[lft[y] - (1 << k) + 1][k];
}
inline int get_dist(int x, int y) {return dep[x] + dep[y] - 2 * dep[LCA(x, y)];}
inline void init_LCA()
{
	for(int i = 1; (1 << i) <= sn; ++i)
	{
		for(int j = 1; j + (1 << i) - 1 <= sn; ++j)
		{
			if(dep[seq[j][i - 1]] <= dep[seq[j + (1 << (i - 1))][i - 1]])
				seq[j][i] = seq[j][i - 1];
			else seq[j][i] = seq[j + (1 << (i - 1))][i - 1];
		}
	}
	for(int i = sn; i >= 1; --i) lft[seq[i][0]] = i;
}
inline int jump(int x, int dist)
{
	while(dist) x = fa[x][__lg(lowbit(dist))], dist -= lowbit(dist);
	return x;
}
inline PAIR get(int x, int y)
{
	if(LCA(x, y) == x) return {n - siz[jump(y, dep[y] - dep[x] - 1)], siz[y]};
	else if(LCA(x, y) == y) return {siz[x], n - siz[jump(x, dep[x] - dep[y] - 1)]};
	else return {siz[x], siz[y]};
}

struct Path
{
	int x, y;
	inline int dist() {return get_dist(x, y);}
} path[N]; int pn;
inline bool cmp(Path u, Path v) {return u.dist() < v.dist();}

int tag[N];
struct DSU
{
	int prt[N], siz[N]; long long w[N], num[N];
	inline void init(int n) {for(int i = 1; i <= n; ++i) prt[i] = i, siz[i] = 1;}
	inline int find(int x) {return ((prt[x] == x) ? x : (prt[x] = find(prt[x])));}
	inline void merge(int x, int y)
	{
		x = find(x), y = find(y);
		if(x != y)
		{
			if(siz[x] > siz[y]) swap(x, y);
			prt[x] = y, siz[y] += siz[x], w[y] += w[x], num[y] += num[x];
			w[x] = num[x] = 0;
		}
	}
}; DSU dsu;
inline long long calc(int k, int id)
{
	if(tag[id] == k) return 1;
	tag[id] = k;
	return inv[k - (k * dsu.num[id] - dsu.w[id])];
}

inline void init(int pos, int prt)
{
	fa[pos][0] = prt, siz[pos] = 1;
	for(int i = 1; ; ++i)
	{
		if(fa[fa[pos][i - 1]][i - 1]) fa[pos][i] = fa[fa[pos][i - 1]][i - 1];
		else break;
	}
	seq[++sn][0] = pos, dep[pos] = dep[prt] + 1;
	for(int to : tr[pos])
	{
		if(to == prt) continue;
		init(to, pos), siz[pos] += siz[to];
		seq[++sn][0] = pos;
	}
}
inline void search(int pos, int prt, int st)
{
	if(deg[pos] != 2)
	{
		if(st < pos) path[++pn] = {st, pos};
		return ;
	}
	for(int to : tr[pos])
	{
		if(to == prt) continue;
		search(to, pos, st);
	}
}

inline void sol()
{
	cin >> n;
	for(int i = 1, x, y; i < n; ++i)
	{
		cin >> x >> y;
		++deg[x], ++deg[y];
		tr[x].push_back(y);
		tr[y].push_back(x);
	}
	init(1, 0); init_LCA(); dsu.init(n);
	for(int i = 1; i <= n; ++i)
		if(deg[i] != 2)
			for(int j : tr[i])
				search(j, i, i);
	sort(path + 1, path + pn + 1, cmp);
	for(int i = 1; i <= pn; ++i)
	{
		PAIR cur = get(path[i].x, path[i].y);
		dsu.w[dsu.find(path[i].x)] += (cur.first - 1);
		dsu.w[dsu.find(path[i].y)] += (cur.second - 1);
		++dsu.num[dsu.find(path[i].x)];
		++dsu.num[dsu.find(path[i].y)];
	}
	res[n] = fac[n], res[n - 1] = fac[n - 1];
	for(int k = n - 2, pt = 1; k >= 1; --k)
	{
		res[k] = fac[k];
		if(pt == pn + 1) res[k] = 1;
		for(int i = pt; i <= pn; ++i)
		{
			res[k] = res[k] * calc(k, dsu.find(path[i].x)) % mod;
			res[k] = res[k] * calc(k, dsu.find(path[i].y)) % mod;
		}
		while(pt <= pn && path[pt].dist() + 1 == n - k)
		{
			PAIR cur = get(path[pt].x, path[pt].y);
			dsu.w[dsu.find(path[pt].x)] -= (cur.first - 1);
			dsu.w[dsu.find(path[pt].y)] -= (cur.second - 1);
			--dsu.num[dsu.find(path[pt].x)];
			--dsu.num[dsu.find(path[pt].y)];
			dsu.merge(path[pt].x, path[pt].y);
			++pt;
		}
	}
	for(int i = 1; i <= n; ++i) cout << res[i] << '\n';
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	init_math();
	while(T--) sol();
	return 0;
}
/*

*/
```

---

## 作者：_Cheems (赞：0)

题意：$n$ 个点的树，有 $k$ 头不同的牛分布在不同的点上，可以操作一头牛向相邻点移动，要求不能有牛在相同节点。状态 $A$ 若可以经过若干次操作到达状态 $B$ 则它们在同一等价类，对每个 $k\in[1,n]$ 求有多少种不同等价类。$n\le 10^5$。

感性理解万岁！其实是太菜了 qwq。

首先有如下想法：

1. 忽略标号，则所有状态互相可达。很显然。所以不妨让牛移动到 $1\dots k$ 上。
2. 对于两个位置 $x,y$，若可以在不影响其他牛的情况下交换上面的牛，就连边 $x,y$。那么存在传递性，因为可以依次 $(x,y),(y,z),(x,y)$ 以做到 $(x,z)$。于是关系图是若干团，答案即为 $\frac {k!}{\prod s_i!}$，$s_i$ 为团大小。
3. “不影响其他牛”其实毫无意义，因为只需交换后倒置整个过程，即可消除影响。

现在考察两头牛 $a,b$ 可以交换的条件，发现形如将 $a$ 移到空位 $c$、将 $b$ 移到 $a$ 原位、将 $a$ 移到 $b$ 原位。

拓展一下，对于一条链 $s\to t$，令其满足 $s,t$ 是非 $2$ 度点，链上其它点均是二度点。很自然地先将牛分别移动到 $s,t$ 子树，那么假如此时 $s,t$ 子树均填满了的话（此处子树不包括 $s,t$），两边子树的牛不可能交换成功。否则存在一个空隙，能凭借它交换两端可以到达链上的点。未填满的条件即为 $k<n-len$，$len$ 是链长。

考察链在树上形态：在树上划出这些链，它们首尾相接，并且每条边恰被覆盖一次。

考察链在关系图上形态：称不满足条件的链为非法链，反之为合法链，合法链构成若干连通块，则每个连通块都在同一个团，又因为非法链的存在所以不同连通块在不同的团。

可能有一些团大小为 $1$ 没被考虑到，但是问题不大，因为不影响答案。只考虑 $\ge 2$ 的团，它们一定是存在交换关系的，也就是对应着连通块。

唯一的问题是怎么求出连通块对应的团的大小，直接统计貌似很困难。正难则反，转而用相接的非法链去刻画这个团，对于一条相接的非法链 $a_i\to b_i$，令 $a_i$ 在连通块内而 $b_i$ 在连通块外。那么向 $a_i$ 子树填牛，至多填 $A_i-1$ 个，也就是说 $k-(A_i-1)$ 头牛必然在团外。注意并非 $a_i$，因为恰在 $a_i$ 上的这头牛显然也是无法参与团内交换的。

这样算不重不漏，因为每一次相当于排除 $b_i$ 方向的一些团，每次排除的团的不会重复，且总和恰好是其它团。

于是团大小即为：

$$k-\sum k-(A_i-1)=k-\sum k-(n-B_i-len_i+1)=k-((k-n+1)cnt+\sum B_i+len_i-2)$$

其中 $cnt$ 是相邻非法链数量，注意到 $\sum B_i+len_i-2$ 即为连通块外点数即 $n-siz$，所以只需维护一下 $cnt,siz$ 即可。

时光倒流 $k$ 使得删边变加边，所以 $cnt,siz$ 是容易用并查集维护的。同时，连通块个数是非法链条数加一，一条非法链存活时间为其长度，所以所有时刻连通块总数是非法链长度级别的，也就是 $O(n)$，直接拿个 `set` 维护即可。复杂度 $O(n\log n)$。

当然可以精细实现 $O(n)$，在连通块合并时直接维护答案应该就行了？
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5 + 5, mod = 1e9 + 7;
int n, u, v, du[N], rot, m, ans[N], jc[N], jcinv[N];
int fa[N], siz[N], cnt[N]; 
vector<int> to[N];
set<int> s;
struct dist{int x, y, w;};
vector<dist> jjdw[N];

inline int qstp(int a, int k) {int res = 1; for(; k; a = a * a % mod, k >>= 1) if(k & 1) res = res * a % mod; return res;}
inline void dfs(int u, int from, int lst, int len){
	if(du[u] == 2){
		for(auto v : to[u]) if(v ^ from) dfs(v, u, lst, len + 1); 
	}
	else{
		fa[u] = u, siz[u] = 1, s.insert(u);
		if(lst) jjdw[len].push_back({u, lst, len}), ++cnt[u], ++cnt[lst];
		for(auto v : to[u]) if(v ^ from) dfs(v, u, u, 2);
	}
}
inline int find(int u) {return fa[u] == u ? u : fa[u] = find(fa[u]);}
inline void mer(int x, int y, int w){
	int fx = find(x), fy = find(y);
	fa[fx] = fy;
	siz[fy] += siz[fx] + w - 2;
	cnt[fy] += cnt[fx] - 2;
	s.erase(fx);
}
signed main(){
	jc[0] = jcinv[0] = 1;
	for(int i = 1; i < N; ++i) jcinv[i] = qstp(jc[i] = jc[i - 1] * i % mod, mod - 2);
	
	cin >> n;
	for(int i = 1; i < n; ++i){
		scanf("%lld%lld", &u, &v);
		to[u].push_back(v), to[v].push_back(u);
		++du[u], ++du[v];
	}
	for(int i = 1; i <= n; ++i) if(du[i] == 1) rot = i;
	dfs(rot, 0, 0, 0);
	ans[n] = jc[n];
	for(int k = n - 1; k; --k){
		for(auto _ : jjdw[n - k - 1]) mer(_.x, _.y, _.w);
		ans[k] = jc[k];
		for(auto i : s){
			int mb = k - ((k - n + 1) * cnt[i] + n - siz[i]);
			ans[k] = ans[k] * jcinv[mb] % mod;
		}
	}
	for(int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
	return 0;
}
```

---

