# Tree-Tac-Toe

## 题目描述

给出一棵 $N$ 个点的树，初始时某些节点是白色，其他节点没有颜色。

有两个人在树上博弈。每一回合，一方可以将一个没有颜色的点染成白色，然后另一方可以将一个没有颜色的点染成黑色。白色方为先手，黑色方为后手。

如果在某次染色后树上存在三个点 $ABC$ 满足有边 $(A,B)(B,C)$、$ABC$ 都有颜色且颜色相同，则该颜色对应的人获胜。

假设两人绝顶聪明，问最后结果如何。

## 样例 #1

### 输入

```
2
4
1 2
1 3
1 4
NNNW
5
1 2
2 3
3 4
4 5
NNNNN
```

### 输出

```
White
Draw
```

# 题解

## 作者：John_Smith (赞：11)

这题在 CF rating 是 3100+，听了讲评之后感觉醍醐灌顶。

如果您不看题解就 AC，那您是真的强。

首先，我们发现，黑不可能赢。

接下来，考虑一种简单的情况：没有任何点初始时有颜色。

情况 1：树中有一个点 $A$ 的度大于等于 $4$。

我们假设它连着 $B,C,D,E$ 等点。那么，白方下 $A$，不妨令黑下在 $B$，白下 $C$,此时白有两个未被阻挡且连起来的点，白胜。

剩下的情况中，每一个点的度都小于等于 $3$。

情况2：树中有一个点度为 $3$ ，且从这个点伸出至少两个长度至少为 $2$ 的链。

![](https://cdn.luogu.com.cn/upload/image_hosting/4rtj5lvx.png)

白下 $2$，不妨另黑下 $3$，则白下 $4$，此时白有两个未被阻挡且连起来的点，白胜。

剩下的情况中，每一个点最多伸出一条长度大于等于 $2$ 的链，并且容易发现，此时至多有 $3$ 个度为 $3$ 的点。否则，可以放入情况 2 中。

此时任选其中的两个点做讨论。此时，它们会出现图示的 $\text{H}$ 形结构。

一、两条竖杆中间夹着偶数个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/ujqipy0w.png)

白下 $4$，黑只能下 $2$；白下 $5$，黑下 $7$，平。

二、两条竖杆之间夹着奇数个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/peq98zlr.png)

白下 $4$，不妨另黑下 $2$；白下 $7$，不管黑堵住哪一边，白都能走另外一边连成 $3$ 个子。


我们转化为一般的情况。假设中间被夹着的点是 $1$ 至 $n$。白最优解就是下 $1$ 和 $n$，那么黑就会堵住另外两边的点（$1$ 前面的，$n$ 后面的）；然后白就会隔一个位置下一个子，然后黑为了防止白连成三个子，就会下在白中间的空位。就这样一直往中间下，如果最后白最中间的两个子有一个空位，则白胜（因为此时会留下两个空，无论黑占掉哪一个，白都可以下；另一个空而胜利）。

容易发现，上面这段等价于：$n$ 为奇数则白胜，否则平。

剩下的情况就是一条链了。这是黑和白会一直纠缠，最终平。上面就是所有情况。

如果最开始有白色的点呢？我们使用化归的思想，把左侧的 $A$ 转化为右侧的 $A'$：

![](https://cdn.luogu.com.cn/upload/image_hosting/hlhp77ab.png)

其中，右侧所有点未染色，且 $B,C,D$ 是新添加的。

思考一下意义：如果 $A'$ 此时被白下，黑为了不负必定下 $D$，此时 $C,B$ 就被浪费掉了（如果在这里黑子想连成三个，由于白先下，那么黑也比白慢，必须与白牵制），相当于让白多下了。

没了。注意每次清零的时候别用 ```memset```，直接循环赋 $0$，否则 T 飞第二个点。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define read() Read<int>()
#define write Write<int>
#define writesp Writesp<int>
#define writeln Writeln<int>
template<typename T>
inline T Read()
{
	bool f=0;T x=0;char ch;
	do{ch=getchar();f|=(ch=='-');}while(!isdigit(ch));
	do{x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}while(isdigit(ch));
	return f?-x:x;
}
template<typename T>
inline void Write(T x)
{
	if(x<0){putchar('-');write(-x);return;}
	if(x>9)write(x/10);
	putchar(x%10+48);
}
template<typename T> inline void Writeln(T x){Write(x);puts("");}
template<typename T> inline void Writesp(T x){Write(x);putchar(' ');}
const int maxn=2e6+5;
int nxt[maxn<<1|1],to[maxn<<1|1],head[maxn],tot=0;
int n;
void addedge(int u,int v)
{
	nxt[++tot]=head[u];
	head[u]=tot;
	to[tot]=v;
}
int deg[maxn];
bool judge1()//判断是否有度>=4的点 
{
	rep(i,1,n)if(deg[i]>3)return 1;
	return 0;
}
//接下来的情况中，所有点的度都<=3 
bool judge2()//判断是否有挂着两条长度>=2的链的点 
{
	rep(u,1,n)
	{
		int count=0;
		if(deg[u]!=3)continue;
		for(register int i=head[u];i;i=nxt[i])
		{
			int v=to[i];
			if(deg[v]>1)++count;
		}
		if(count>1)return 1;
	}
	return 0;
}
int dis[maxn];
void dfs(int u,int fa)
{
	dis[u]=dis[fa]+1;
	for(register int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(fa==v)continue;
		dfs(v,u);
	}
}
//接下来，每一个点只有可能挂着一条长链，剩下的地方都只连接着一个点
bool judge3()//判断“H”形情况
{
	int a=0,b=0,c=0;
	rep(i,1,n)
	{
		if(deg[i]>=3)
		{
			if(a&&b){c=i;break;}
			if(a){b=i;}
			else a=i;
		}
	}
	if(!b&&!c)return 0;
	memset(dis,0,sizeof dis);dfs(a,0);
	int len=dis[b];
	if(len&1)return 1;
	if(!c)return 0;
	len=dis[c];
	if(len&1)return 1;
	memset(dis,0,sizeof dis);dfs(b,0);
	len=dis[c];
	if(len&1)return 1;
	return 0;
} 
int main(){
	int t=read();
	while(t--)
	{
		n=read();
		rep(i,1,n-1)
		{
			int u=read(),v=read();
			addedge(u,v);
			addedge(v,u);
			++deg[u];++deg[v];
		}
		int cur=n;
		rep(i,1,n){
			char ch;cin>>ch;
			if(ch=='W')
			{
				cur+=3;
				addedge(i,cur-2);addedge(cur-2,i);
				addedge(cur-1,cur-2);addedge(cur-2,cur-1);
				addedge(cur,cur-2);addedge(cur-2,cur);
				deg[i]++;deg[cur-2]=3;
				deg[cur-1]=deg[cur]=1;
			}//拆点 
		}
		n=cur;
		if(judge1()){puts("White");}
		else if(judge2()){puts("White");}
		else if(judge3()){puts("White");}
		else puts("Draw");
		rep(i,1,n)deg[i]=head[i]=0;
		tot=0;
	}
	return 0;
} 
```

---

## 作者：Ink_Render (赞：5)

戳[这里](https://www.luogu.com.cn/blog/zym20070228/ti-xie-cf1110gtree-tac-toe-post#)食用更佳。

【题目大意】

在一棵原有一些白点和未染色的点的树上进行轮流染色游戏，白色先染，率先将三个相邻节点染色的一方胜，求获胜的一方。

这道题第一眼看上去应该就是博弈论，但是题目中的游戏明显是不公平的，所以不便于求解，所以我们先来考虑原树上没有白色点的情况。

考虑对于一个全为空节点的图（树），有哪些可能的局面是先手必胜的。

1. 

很明显，如果一个节点连上了至少 4 个点（即度大于 4 ），那么先手下在这个节点上，无论后手怎么下先手都必胜。

2. 

如果图中的点的度数都小于等于 2 ，则此图为一条链，必然为平局。

3. 

接下来我们只要关注度为 3 的点。如果我们下在一个度为 3 的点，对手会堵住一边，此时我们如果要和当前这个点连上，还有两个点可以下，即

![](https://cdn.luogu.com.cn/upload/image_hosting/9meey16u.png?x-oss-process=image/resize,m_lfit,h_270,w_345)

这样原图就变成了一个有一个白点的链，且此时白点先手。为了让先手必胜，这个链的长度至少为 4 ，即至少有一个子节点还接着一个节点，即度数至少为 2 。不过这还没完，由于你的对手足够聪明，他会断掉你最长的一个链，也就是说，他所断掉的节点度数也至少为 2 。

这一段对应着先手必胜的一个局面：对于一个度数为 3 的点，至少有两个子节点度数大于 2 。

4.

但如果每个度数为 3 的点都不满足上面的情况呢？我们来考虑最后的情况。关于两个度数为 3 的点之间的关系。假设两个度数为 3 的点长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/xrismtlt.png?x-oss-process=image/resize,m_lfit,h_270,w_325)

我们从左边下起，目标是尽可能的对右边造成贡献。在此前提下，我们的第一步下在 4 （不在 1 ，因为对手会堵在 4 ，这样没有对后面的贡献），对手必须堵在 1 ，我们跳过一个点，下在离 4 距离为 2 的 位置，对手会堵在 4 的右边，以此类推，最后我们要么会下到 8 ，要么下到 4 。具体为：当中间（指 1 到 5 中间）距离为偶数时，最后会下到 8 ，为奇数则到 5 。最后一步下到 8 时，对手会堵在 8 之前的点，我们就可以下在 5 ，此时先手必胜。若在 5 则平局。

这是先手必胜的另一个局面：存在两个度数为 3 的点，满足他们之间的路径长为偶数。

但如果度数为 3 的点很多，那复杂度岂不爆炸？不用担心，我们考虑：如果度数为 3 的点大于等于 3 个，由于原图是一棵树，则一定有一个点在另外两个点的路径上，假设这三个距离为 $l_1,l_2,l_3$ ，则 $l_1+l_2=l_3$ ，用奇偶性判断，这三个数中至少有一个偶数。故当度数为 3 的点的个数大于 2 时，先手必胜。

综上所述，先手必胜的局面有 3 个：

- 一个节点度大于 4 。

- 一个度数为 3 的点，至少有两个子节点度数大于 2 。

- 存在两个度数为 3 的点，满足他们之间的路径长为偶数。（包括度数为 3 的点的个数大于 2 ）

那么，我们还要想想，存不存在后手必胜的情况。答案是否定的。如果满足以上情况，先手就已经必胜了；如果不满足，那也不可能再出现以上情况了，所以后手不可能必胜。也就是说，除了先手必胜的情况，剩下的都为平局。

说完上面，我们回到此题。

对于这个有特殊限制的图，我们要想办法把他转变为我们刚刚讲的一般形式。如果一个点初始即为白色，我们可把它看做是原来空的一个点，白色先手下在了这个点，而黑色下在了原图之外的点，也就是我们从这个点引出一个点，把黑色下在引出的点上。

不过小黑（\doge）他很聪明，你需要给他一个理由让他下在这个点上。所以，我们需要设计一种情况，如果黑色不下在这白色就必胜，比如：

![](https://cdn.luogu.com.cn/upload/image_hosting/4ewydpdq.png?x-oss-process=image/resize,m_lfit,h_230,w_325)

其中 4 是原图中的点。这种情况下，黑色必须下在 1 上，也就满足了我们的目标。

那么我们的问题解决就完成了。最后有两个注意点：

1. 由于一个点会被拆成四个点，所以最多有 $4 \times N$ 个点，注意空间。

2. 多组数据注意清空，但是不要用 memset ！！因为 $\sum n=\operatorname{max} n$ ，所以用 memset 会浪费很多时间，然后你会在第二个点 TLE ，请用循环清空。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int t,n,tot;
int head[N],du[N],nxt[N<<1],to[N<<1];
char s[N];
void add(int u,int v)
{
	nxt[++tot]=head[u];
	head[u]=tot;
	to[tot]=v;
	du[u]++;
}
void ins(int u,int v) {add(u,v);add(v,u);}
void make_son(int x)//加建节点
{
	du[n+1]=du[n+2]=du[n+3]=head[n+1]=head[n+2]=head[n+3]=0;
	ins(n+1,x);ins(n+1,n+2);ins(n+1,n+3);
	n+=3;
}
bool dfs(int u,int fa,int len)// dfs 从一个度数为 3 的点找另一个度数为 3 的点
{
	if(du[u]==3 && len!=0 && !(len%2)) return true;
	for(int i=head[u];i;i=nxt[i])
	{
		if(to[i]==fa) continue;
		if(dfs(to[i],u,len+1)) return true;
	}
	return false;
}
bool calc()
{
	for(int i=1;i<=n;i++)
		if(du[i]>=4) return true;// 1
	int now,sum=0,p;// sum 记录度数大于等于 3 的节点数， now 记录当前节点的子节点中度数大于等于 2 的节点数
	for(int i=1;i<=n;i++)
	{
		now=0;
		if(du[i]<3) continue;
		sum++,p=i;
		for(int j=head[i];j;j=nxt[j])
			if(du[to[j]]>=2) now++;
		if(now>=2) return true;// 2
	}
	if(sum>=3) return true;// 3
	if(sum==2) return dfs(p,0,0);
	return false;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		tot=1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			head[i]=0,du[i]=0;
		int x,y;
		for(int i=1;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			ins(x,y);
		}
		scanf("%s",s+1);
		int nn=n;
		for(int i=1;i<=nn;i++)
			if(s[i]=='W') make_son(i);
		if(calc()) puts("White");
		else puts("Draw");
	}
	return 0;
}
```

---

## 作者：Itst (赞：4)

[传送门](http://codeforces.com/contest/1110/problem/G)

UPD：之前可能对白色变无色的过程讲的不是很清楚，已经补充

如果有任何问题可以去我的[Blog](https://www.cnblogs.com/Itst/p/10356243.html)问，在Luogu博客下回复可能无法及时看到

---

显然在双方绝顶聪明的情况下，黑色不可能赢

首先考虑树上一个白色的点都没有的情况：

1、如果树上有一个点的度数$\geq 4$，白色必赢，只需要第一次将这一个点染成白色，接着随便染它的两个邻居就可以达成目标

2、如果树上有一个点的度数$=3$，且它所连的$3$个点之间至少有$2$个点不是叶子节点，白色必赢，只需要第一次染这一个点，第二次染它的一个非叶子邻居，第三次就一定至少存在一个未被染色的点与这两个相邻。

那么剩下的情况，树的形态只会是下图中的三种

![](https://img2018.cnblogs.com/blog/1504072/201902/1504072-20190208152603205-904098959.png)

但是还没完~~（我以为到这里就完了结果WA2被Tutorial点名）~~

**最重要的3、如果树的形态是上面的图中最下面的那一种，而且总点数为奇数，那么白色必赢**

图长下面这样，中间的……省略的是一条链，编号从左往右递增。

![](https://img2018.cnblogs.com/blog/1504072/201902/1504072-20190208153044567-1850717860.png)

白色最开始染$2$号点，黑色如果染$3$号点白色直接染$1$号点，所以黑色必须染$1$号点。此时白色染$4$号点，黑色又只能染$3$号点……如是白色染到$2N$号点，黑色染$2N-1$号点之后，白色染$2N+1$号点，那么最右边就会有两个未被染的点，白色就赢了

其余的情况显然都是Draw的

然后考虑已经被染成白色的点的影响，~~最开始天真的我想直接各种特判过掉，结果WA14不晓得怎么回事~~

我们已经考虑了树上没有被染成白色的点的所有情况，那么能否将一个已经被染成白色的点等价为若干未被染成白色的点？实际上是可以的

假设下图中$1$号点在原树上是一个白色点，那就在保留它原来的邻居的基础上给它额外连上$3$个点，连成下面的$ABCD$结构

![](https://img2018.cnblogs.com/blog/1504072/201902/1504072-20190208154044755-1585040542.png)

原图$1$号点对应新图的$A$号点，原图上$1$号点跟哪些点连了边，新图上$A$号点也和它们连边，然后在下面挂上$BCD$三个点

对于执白色的人来说，如果TA在某一回合涂白了$A$号点，这个时候如果执黑色者不涂黑$B$号点，那么执白色者将会在下一回合涂白$B$号点，对于$CD$两个点，白色就一定可以涂白其中一个，白色就赢了

所以执黑色者只能涂黑$B$号点。而这个时候$BCD$三个点对于胜负已经没有影响了，可以直接砍掉这三个点，就相当于白色直接涂白了$A$号点，也就是涂白了原图的$1$号点，然后又来到白色的回合。

```
#include<bits/stdc++.h>
//This code is written by Itst
using namespace std;

inline int read(){
    int a = 0;
    char c = getchar();
    bool f = 0;
    while(!isdigit(c)){
	    if(c == '-')
			f = 1;
        c = getchar();
    }
    while(isdigit(c)){
		a = (a << 3) + (a << 1) + (c ^ '0');
		c = getchar();
	}
	return f ? -a : a;
}

const int MAXN = 1e6 + 9;
struct Edge{
	int end , upEd;
}Ed[MAXN << 1];
int head[MAXN] , in[MAXN] , N , cntEd , cnt;
char s[MAXN];

inline void addEd(int a , int b){
	Ed[++cntEd].end = b;
	Ed[cntEd].upEd = head[a];
	head[a] = cntEd;
	++in[a];
}

int main(){
	for(int T = read() ; T ; --T){
		N = read();
		cntEd = 0;
		memset(head , 0 , sizeof(int) * (N + 1));
		memset(in , 0 , sizeof(int) * (N + 1));
		for(int i = 1 ; i < N ; ++i){
			int a = read() , b = read();
			addEd(a , b);
			addEd(b , a);
		}
		scanf("%s" , s + 1);
		if(N < 3){
		    puts("Draw");
		    continue;
		}
		if(N == 3){
		    int cnt = 0;
		    for(int i = 1 ; i <= N ; ++i)
		        cnt += s[i] == 'W';
		    puts(cnt >= 2 ? "White" : "Draw");
		    continue;
		}
		bool ifans = 0;
		int cnt1 = 0;
		for(int i = 1 ; i <= N ; ++i)
		    if(s[i] == 'W'){
		        addEd(i , ++N);
		        head[N] = 0;
		        addEd(N , i);
		        in[N] = 3;
		    }
		for(int i = 1 ; !ifans && i <= N ; ++i)
			if(in[i] > 3)
				ifans = 1;
			else
				if(in[i] == 3){
					int cnt = 0; 
					for(int j = head[i] ; j ; j = Ed[j].upEd)
						cnt += in[Ed[j].end] >= 2;
					ifans = cnt >= 2;
					++cnt1;
			}
		if(cnt1 == 2 && (N & 1))
		    ifans = 1;
		puts(ifans ? "White" : "Draw");
	}
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：2)

## 题意
给一个 $n$ 个点的树，一开始树上的点染了一些颜色，有 `N`，`W` 两种情况，`N` 代表未被染色，`W` 代表被染了白色。

$Alice$ 和 $Bob$ 轮流操作：

+ $Alice$ 先选一个点染成白色；

+ $Bob$ 再选一个点染成黑色；

依次循环。

若树上出现一个三点链为白色，则 $Alice$ 获胜，输出 `White`, 停止游戏；

若树上出现一个三点链为黑色，则 $Bob$ 获胜，输出 `Black`，停止游戏；

若所有点都染完色并且没人获胜，则输出 `Draw`。

## 分析

初始白色点先不考虑，先考虑无白色点的情况：
1. 存在度数为 $4$ 的点时先手必胜

2. 如果所有的点度数都在 $2$ 以内就必定平局

3. 如果下在度数为 $3$ 的点上，则对手一定会堵住一边，还有两个位置可以下。此时就变成了一条有一个白点的链（黑点挡住的忽略不计）。此时如果白方胜，则链长度至少为 $4$，相当于有一个子节点度数至少为 $2$，并且对方所断掉的顶点度数也至少为 $2$。所以一个度数为 $3$ 的结点和两个度数为 $2$ 的子节点先手必胜。

4. 考虑多个度数为3节点之间的关系，模拟一下不难发现两个度数为3并且距离为偶数的节点必胜。而当出现多个度数为3的节点时，先手直接必胜的。

这时候再考虑有白色点的情况。

尝试把每一个染成白色的点拆成多个点，转化为上面的情况。如果一个点初始即为白色，可以把它看做是原来空的一个点，白色下在了这个点，而黑色下在了原图之外的点。也就是我们从这个点拆出一个点，把黑色下在拆出的点上。而因为白棋先手，所以相当于在没有额外点的情况下多下了一颗白棋。而这个构造，是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/20uctx0w.png)

于是就做完了。

## 代码

```cpp
/*
先考虑无白色点的情况
发现存在度数为4的点时先手必胜
如果所有的点度数都在2以内就必定平局
而如果下在度数为3的点上，则对手一定会堵住一边，还有两个位置可以下。
此时就变成了一条有一个白点的链（黑点挡住的忽略不计）。此时如果白方胜，则链长度至少为4，
相当于有一个子节点度数至少为2，并且对方所断掉的顶点度数也至少为2
所以一个度数为3的结点和两个度数为2的子节点先手必胜
最后就考虑多个度数为3节点之间的关系，模拟一下不难发现两个度数为3并且距离为偶数的节点也是必胜的。
而当出现多个度数为3的节点时，先手也是必胜的。
尝试把每一个染成白色的点拆成多个点，转化为上面的情况。
如果一个点初始即为白色，可以把它看做是原来空的一个点，白色下在了这个点，
而黑色下在了原图之外的点。也就是我们从这个点拆出一个点，把黑色下在拆出的点上。
所以我们需要设计一种情况使黑色必定下在这个点上，如代码所示。
于是就做完了。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define lld long long
const int N = 2000010;
struct edge {
	int to, nxt;
} es[N << 1];
int head[N], ecnt;
int deg[N];
inline void addedge(int u, int v) {
	es[++ ecnt] = (edge){v, head[u]};
	head[u] = ecnt;
	++ deg[u];
}
inline void addedge2(int u, int v) {
	addedge(u, v);
	addedge(v, u);
}
int T, n;
char str[N];
inline void white(int u) {
	deg[n + 1] = deg[n + 2] = deg[n + 3] = 0;
	head[n + 1] = head[n + 2] = head[n + 3] = 0;
	addedge2(n + 1, u);
	addedge2(n + 2, n + 1);
	addedge2(n + 3, n + 1);
	n += 3;
}
inline bool dfs(int u, int fa, int len) {
	if (deg[u] == 3 && len && !(len % 2)) return 1;
	for (int e = head[u], v; v = es[e].to, e; e = es[e].nxt)
		if (v != fa && dfs(v, u, len + 1)) return 1;
	return 0;
}
inline bool calc() {
	for (int i = 1; i <= n; ++ i)
		if (deg[i] >= 4) return 1;
	int sum2, sum = 0, p;
	for (int i = 1; i <= n; ++ i) {
		sum2 = 0;
		if (deg[i] <= 2) continue;
		++ sum, p = i;
		for (int e = head[i], v; v = es[e].to, e; e = es[e].nxt)
			if (deg[v] >= 2) ++ sum2;
		if (sum2 >= 2) return 1;
	}
	if (sum >= 3) return 1;
	if (sum == 2) return dfs(p, 0, 0);
	return 0;
}
int main() {
	scanf("%d", &T);
	for (; T --; ) {
		scanf("%d", &n);
		ecnt = 1;
		for (int i = 1; i <= n; ++ i)
			head[i] = deg[i] = 0;
		for (int u, v, i = 1; i < n; ++ i) {
			scanf("%d%d", &u, &v);
			addedge2(u, v);
		}
		scanf("%s", str + 1);
		int m = n;
		for (int i = 1; i <= m; ++ i)
			if (str[i] == 'W') white(i);
		if (calc()) puts("White");
		else puts("Draw");	
	}
}
```

---

## 作者：lndjy (赞：1)

模拟赛考场差点切掉，输麻了/ll

首先，黑是不可能赢的，考虑如果存在一种黑能赢的策略，白只需要先走它即可。

另外数据较小的时候分类讨论比较麻烦，所以我们可以在 $n\le 5$ 时爆搜，来减少讨论。

以下均基于 $n>5$。

然后你发现，白是很容易赢的，先考虑没有白点的情况：

1.如果有度数大于 3 的点，白只需要先占上它就可以赢。

2.如果有度数等于 3 且能延申出来两条长度大于 1 的链，占住它也可以赢。

这两种情况可以简单手玩一下。

这样来看，剩下情况就几乎是链，最多两边伸出来两个叉。

3.考虑有白点的情况，如果有 1 个白点不在边上，只需要占住旁边的就可以赢了。

4.考虑有两个白点在边上，如果距离是奇数，也可以赢。考虑极端情况一条链，不断构造"白空白"，最后和另一边的白接上即可。

5.如果大于两个白点，一定存在距离为奇数的两个点，一定赢。证明考虑在两个白点组成的链上接一段，分链种和链边接上，可以发现这个结论。

然后你发现，排除上面几种情况，剩下的树只有两种：一种是一条链，两边各分叉，一种是分一个叉，且不管哪种白点度数一定为 1。

考虑有白点的情况：

6.如果有白点且度数 3 的点距离白点是奇数，那么先手也可以赢。证明还是不断构造"白空白"，最后是"空白白空"的情况。

考虑没有白点的情况，如果只有一个叉必然无解，两个叉手玩可以发现 $n=7$ 有解，只需要占中间的点，于是可以利用构造“白空白”的思想，得到：

7.如果有两个度数为 3 的点，且 $n$ 是奇数，一定赢。

依次判断完这些，剩下的就是平局了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
char readchar()
{
	char ch=getchar();
	while(!isalpha(ch)) ch=getchar();
	return ch;
}
const int N=5e5+5;
struct edge
{
	int to,nxt;
}e[N*2];
int head[N],d[N],cnt,n;
void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
	d[v]++;
}
int a[N];
int DIS;
void dfs(int now,int fa,int dep,int to)
{
	if(now==to) DIS=dep;
	else
	{
		for(int i=head[now];i;i=e[i].nxt)
		if(e[i].to!=fa)
		dfs(e[i].to,now,dep+1,to);
	}
}
int dfs2(int now,int fa)
{
	for(int i=head[now];i;i=e[i].nxt)
	if(e[i].to!=fa) return 1;
	return 0;
}
bool FLAG;
void dfs3(int now,int fa,int dep)
{
	if(dep%2==1&&d[now]==3) FLAG=1;
	for(int i=head[now];i;i=e[i].nxt)
	if(e[i].to!=fa)
	dfs3(e[i].to,now,dep+1);
}
int E[10][10];
bool check(int x)
{
	for(int i=1;i<=n;i++)
	if(a[i]==x)
	for(int j=1;j<=n;j++)
	if(a[j]==x&&E[i][j])
	for(int k=1;k<=n;k++)
	if(a[k]==x&&E[j][k]&&k!=i)
	return 1;
	return 0;
}
bool check1();
bool check0()//1 bai ying
{
	if(check(1)) return 1;
	if(check(-1)) return 0;
	bool flg=0;
	for(int i=1;i<=n;i++)
	if(a[i]==0)
	{
		flg=1;
		a[i]=1;
		if(!check1())
		{
			a[i]=0;
			return 1;
		}
		a[i]=0;
	}
	if(flg==0)
	return check(1);
	return 0;
}
bool check1()//1 hei ying
{
	if(check(1)) return 0;
	if(check(-1)) return 1;
	bool flg=0;
	for(int i=1;i<=n;i++)
	if(a[i]==0)
	{
		flg=1;
		a[i]=-1;
		if(!check0())
		{
			a[i]=0;
			return 1;
		}
		a[i]=0;
	}
	if(flg==0)
	return !check(1);
	return 0;
}
void bf()
{
	if(check0()) cout<<"White\n";
	else cout<<"Draw\n";
}
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int T=read();
	while(T--)
	{
		n=read();
		if(n<=5)
		{
			for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			E[i][j]=0;
		}
		for(int i=1;i<=n;i++)
		d[i]=head[i]=0;
		cnt=0;
		for(int i=1;i<n;i++)
		{
			int x=read(),y=read();
			add(x,y);
			add(y,x);
			if(n<=5)
			E[x][y]=E[y][x]=1;
		}
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			char op=readchar();
			if(op=='N') a[i]=0;
			else a[i]=1,sum++;
		}
		if(n<=5)
		{
			bf();
			continue;
		}
		if(sum>=3)
		{
			cout<<"White\n";
			continue;
		}
		if(sum==2)
		{
			int id0=0,id1=0;
			for(int i=1;i<=n;i++)
			if(a[i]==1)
			{
				if(id0==0) id0=i;
				else id1=i;
			}
			dfs(id0,0,0,id1);
			if(DIS==1||DIS%2==0)
			{
				cout<<"White\n";
				continue;
			}
		}
		if(sum)
		{
			bool flg=0;
			for(int i=1;i<=n;i++)
			if(a[i]==1&&d[i]>1) flg=1;
			if(flg)
			{
				cout<<"White\n";
				continue;
			}
		}
		int flg=0;
		for(int i=1;i<=n;i++)
		if(d[i]>=4) flg=1;
		if(flg)
		{
			cout<<"White\n";
			continue;
		}
		int fuk=0;
		for(int i=1;i<=n;i++)
		if(d[i]==3)
		{
			flg=0;
			for(int j=head[i];j;j=e[j].nxt)
			flg+=dfs2(e[j].to,i);
			if(flg>=2)
			fuk=1;
		}
		if(fuk)
		{
			cout<<"White\n";
			continue;
		}
		if(sum)
		{
			FLAG=0;
			for(int i=1;i<=n;i++)
			if(a[i]==1)
			dfs3(i,0,0);
			if(FLAG)
			{
				cout<<"White\n";
				continue;
			}
		}
		if(n%2==1)
		{
			int d3=0;
			for(int i=1;i<=n;i++)
			if(d[i]==3) d3++;
			if(d3==2)
			{
				cout<<"White\n";
				continue;
			}
		}
		cout<<"Draw\n";
	}
 	return 0;
}
/*

*/

```


---

## 作者：xh39 (赞：1)

这题做了我两年半才做出来...细节是真的多......

注:此题黑白的先后顺序好像不符合常理。所以将此题黑白交换,即黑先。

定义:**度**表示一个结点与几个结点相连。

胜利条件0:遇到下图的情况,则必胜。(```@```表示棋子。```?```表示空)
```
@-@-?
  |
  ?
```
胜利条件1:如下图,**出现了度>=4的结点。**
```
  5
  |
2-1-3
  |
  4
```
黑第一步走1结点。那么剩下4个节点只要占满2个就可以胜利。最后一个下的一定是黑棋,此时黑胜。

胜利条件2:**出现了度>=3的结点。且至少有2个枝条大小至少为2。**
```
6-2-1-3-5
    |
    4
```
黑走1。若白走2或4或6,黑走3。白走3或5,黑走2。然后就构成了胜利情况0。黑胜。

注:以下情况无法连3子。为方便称作 T形。
```
2
|
1-4-5-6-7-8-9-...-
|
3
```
因为黑走1,则白走4.黑无法胜利。



首先看一个情况。度为3的结点。
```
1
|
2-4
|
3
```
如果黑下4,那么白必须走1,2,3中的任意一子。显然下2是最优情况。所以这种情况可转换为在4下一子。然后把1,2,3删掉。

胜利条件3:链
```
@-2-3-4-5-6-@
```
如果黑走3,则白必须走2。黑走5。则白必须走4。此刻黑走6,胜。观察规律。黑每次走的棋都是跳着来的。所以如果两个棋子的距离为偶,则黑必胜,否则和棋。

胜利条件4:**出现了两个度为3的点。且距离为偶。** 称作H形。
```
1                 12
|                 |
2-4-5-6-7-8-9-10-11
|                 |
3                 13
```
此时可转换为4,10有一黑子。

胜利条件5:**初始局面的黑子出现在度>=2的点上且n>=4。**
```
2-@-3-4      2-@-3
               |
               4
 (情况0)     (情况1)
```
黑此时走3。则转换成了开头讲的胜利情况0。

胜利情况6:**初始局面出现了至少3颗棋子。**
```
@
|              
1-4-5-6-7-8-...-@    @-2-3-4-5-6-@         @-2-3-@-5-6-@
|                          |
@                          @
(情况0)                  (情况1)                (情况2)     
```
对于链,一定中间会有一颗棋子,就是胜利条件5。对于T形,要么出现在中间满足胜利条件5,要么出现在3个叶节点上,此时如情况0,直接下在1就赢了。对于情况1,就直接是胜利条件2。

为方便,遇到T形就转换成一颗棋子。然后就判断胜利条件3,5,6。代码略。

---

## 作者：Coffins (赞：0)

感觉这个 *3100 好像有点水。

首先我们发现黑不可能赢，假设黑有必胜策略的话，由于白先手，白只需要先走这里即可。

于是只需要判断白是否存在必胜策略。

经过初步观察，我们可以知道，若存在一个度数大于 4 的点，那么白必胜。

原因显然，只需要走这个点即可。

于是我们只需要对所有点度数都小于 3 的图判断即可。

考虑一个三度点 $X$，与之相连的三个点中任意两个点度数大于 2，白色就又是必胜的。

原因同上，第一步走 $X$ 即可。

到这里，其实剩余图的约束条件已经非常严格了。事实上，这个图最多有两个三度点，且三度点连接的三个点中必然有两者度数为 1。

首先两者度数为 1 的原因显然，这个在上一步就直接筛出来了，由此我们画个图就可以知道，三度点若数量大于 2 的话图就原地爆炸螺旋升天了。~~其实是我一时间想不到太好的证明~~

接下来就针对三度点个数分类讨论了。
### 0 个三度点
此时图就是一条链，此时如果没有原始白点的话黑存在必定平局的策略：
能放白色上方就放，否则放下方，如果都不能放，随便乱放。

如果原始白点在 2 度点上且 $n\gt 3$（重要的特判），那么白色有必胜策略：放在此 2 度点的相邻 2 度点即可。

否则如果只有 1 个一度点有原始白点，发现和没有白点一样，黑用相同策略即可。

最后剩下 2 个一度点都有原始白点的情况，那么如果 $n$ 为奇数，可以通过隔一个一放的方式胜利，否则黑点随便挡挡就平了。
### 1 个三度点

这个时候图的形态是一个三度点上挂了两个一度点以及一条链。

首先判掉 $n=4$，因为不便讨论。

然后我们设那条链的另一端点为 $X$。

如果有 $X$ 以外的点是原始白点，那么在其相邻处度数大于 1 的点放即可必胜。

否则若 $X$ 不是原始白点，黑点也是随便挡挡就平了；

若 $X$ 是原始白点，参考 0 个三度点的情况，若 $n$ 为偶数，那么 $X$ 开始隔一个一放就是必胜的，否则的话黑点还是轻松拿捏~~拿下平局~~。
### 2 个三度点

可能是最简单的情况。

图的形态就是两个三度点中间挂一条链。

如果有原始白点那么就是必胜的，在其旁边随便放个点就行。

否则我们还是考虑从某个三度点旁边开始隔一个一放，那么 $n$ 为奇数的时候必胜，偶数时无必胜策略。

然后就讨论完所有情况了。

文中有很多地方不严谨，为感性理解，由于作者没水平导致写不出来证明，望见谅。

理解的时候最好多画几个图。

最后贴个 Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,dg[N];char s[N];
vector<int> vc[N];
int calc()
{
    if(n<=2)return 0;
    if(n==3)
    {
        int ct=0;
        for(int i=1;i<=n;i++)
        ct+=(s[i]=='W');
        if(ct>=2)return 1;
        else return 0;
    }int ct=0;
    for(int i=1;i<=n;i++)
    if(dg[i]>=4)return 1;
    for(int i=1;i<=n;i++)
    {
        if(dg[i]^3)continue;
        int a=vc[i][0],b=vc[i][1],c=vc[i][2];
        int ck=(dg[a]>1)+(dg[b]>1)+(dg[c]>1);
        if(ck>=2)return 1;
    }
    for(int i=1;i<=n;i++)
    ct+=(dg[i]==3);
    if(ct==2)
    {
        for(int i=1;i<=n;i++)
        if(s[i]=='W')return 1;
        return n&1;
    }
    if(ct==1)
    {
        if(n==4)
        {
            int x=0,cnt=0;
            for(int i=1;i<=n;i++)
            if(dg[i]==3)x=i;
            else cnt+=s[i]=='W';
            if(s[x]=='W')return 1;
            return cnt>0;
        }int x=0;
        for(int i=1;i<=n;i++)
        {
            if(dg[i]^1)continue;
            if(dg[vc[i][0]]^3)
            {x=i;break;}
        }
        for(int i=1;i<=n;i++)
        if((i^x)&&s[i]=='W')
        return 1;
        if(s[x]=='N')return 0;
        else return !(n&1);
    }
    if(ct==0)
    {
        bool fl=n&1;
        for(int i=1;i<=n;i++)
        {
            if(dg[i]==1)
            fl&=(s[i]=='W');
            else if(s[i]=='W')
            return 1;
        }return fl;
    }
}
const string str[2]={"Draw\n","White\n"};
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)dg[i]=0;
    for(int i=1;i<=n;i++)vc[i].clear();
    for(int i=2;i<=n;i++)
    {
        int x,y;cin>>x>>y;
        dg[x]++,dg[y]++;
        vc[x].push_back(y);
        vc[y].push_back(x);
    }cin>>s+1;
    cout<<str[calc()];
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;cin>>t;while(t--)solve();return 0;
}

```

---

## 作者：Genius_Star (赞：0)

### 题意：

给定一棵 $n$ 个节点的树，有些点初始为白色，其他点没有颜色。

`A` 和 `B` 在树上进行博弈，`A` 可以将一个没有颜色的点染为白色，`B` 可以将一个没有颜色的点染为黑色。

若在某次染色后存在三个点 $(a,b,c)$ 满足存在边 $(a,b),(b,c)$ 且 $a,b,c$ 三点同色，则操作者获胜。

问最优策略下，是 `A`必胜还是 `B` 必胜或者平局。

### 思路：

首先可以明确一点：`B` 是不可能赢的。

考虑反证，若 `B` 存在一种策略使得自己必胜：

- 则因为 `A` 先走，故 `A` 可以按照这种策略走，就会使得 `A` 必胜，与假设矛盾。

那么 `A` 天时地利人和，肯定不是公平博弈游戏，考虑分类讨论。

先忽略有白点的情况。

----

**情况 $1$：所有的点度数都 $\le 2$**

即树构成了一个链的形式，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/gun27kpy.png)

那么无论 `A` 初始将哪个点染色，`B` 都可以染相邻的位置将其堵住。

故这种情况为**平局**。

**情况 $2$：存在一个点的度数 $\ge 4$**

故有一个点存在至少 $4$ 个儿子，如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/ohjhk5in.png)

若 `A` 一开始先将 $1$ 染色，`B` 最多堵住 $1$ 的两个儿子，则剩下没被染色的儿子数量是肯定大于等于 $2$ 的。

故 `A` 在 `B` 堵节点的时候染其它的儿子节点就是必胜的。

这种情况是**先手必胜**。

**情况 $3$：仅存在一个点的度数为 $3$，且至少有两个儿子的度数 $= 2$**

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/26697dwq.png)

若 `A` 先将 $1$ 号点染色，`B` 会优先将 $2$ 或 $4$ 堵住，然后 `A` 会染 $2$ 和 $4$ 中没有被堵住的点。

那么因为这个点有一个儿子没被堵且 `A` 还有一个儿子没有被堵，故 `B` 无论堵哪个 `A` 都可以染另一个点。

故这种情况**先手必胜**。

**情况 $4$：仅存在两个三度点**

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3ink6orj.png)

其中 $n$ 表示两个三度点之间点的个数。

我们需要找到一种策略使得 `A` 染了当前这个点之后不得不去堵旁边一个点。

容易发现，若 `A` 初始染 $1$，则 `B` 必须去堵 $A$。

然后 `A` 又染 $3$，因为 $1,3$ 已经同色，则 `B` 必须去堵 $2$，以此类推。

若可以使得 `A` 最后一步下到点 $n$，`B` 必须堵住 $n-1$，然后 `A` 染 $A'$ 就必胜了。

则若 $n$ 为奇数时**先手必胜**（即两点间边数为偶数时），否则**平局**。

**情况 $5$：存在大于两个三度点**

我们也可以按照情况 $4$ 暴力枚举两个点检验，但是当三度点特别多时是不优的。

注意到，在一棵树内，因为一个点最多只有两儿子，故必有一个三度点 $B$ 在另外两个三度点 $A,C$ 的路径之间，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/r58piamr.png)

分情况讨论：

- 若 $dis(A,C)$ 为偶数，则 `A` 必胜。

- 否则肯定有 $dis(A,C),dis(B,C)$ 之一为偶数，则 `A` 也必胜。

故当存在多个三度点时也是**先手必胜**。

**情况 $6$：其余情况**

皆为**平局**。

----

现在我们再来考虑有白点的情况。

考虑将一个白点拆点，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/08bmknfy.png)

其中 $1$ 是原先的白点，$2,3,4$ 是新加的点，且都全都未被染色。

注意到，如果 `A` 想要将 $1$ 染色，那么 `B` 为了不输，肯定会将 $2$ 堵住，那么此时 $3,4$ 就对 `A` 没有贡献了，且又到了 `A` 的回合；就等价于初始这里就又一个白点。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const ll N=3*(5e5+10);
mt19937 R(time(0));
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
inline char get(){
	char c;
	while(1){
		c=getchar();
		if(c=='N'||c=='W')
		  break;
	}
	return c;
}
ll T,n,sum,cnt,x,y,ans;
ll u[N],v[N],d[N],f[N],fa[N];
char a[N];
vector<ll> E[N];
void add(ll u,ll v){
	E[u].push_back(v);
	E[v].push_back(u);
	d[u]++,d[v]++;
}
void dfs(ll u,ll f){
	for(auto v:E[u]){
		if(v==f)
		  continue;
		fa[v]=u;
		dfs(v,u); 
	}
}
void solve(){
	sum=x=y=0;
	n=cnt=read();
	for(int i=1;i<n;i++){
		u[i]=read();
		v[i]=read();
	}
	for(int i=1;i<=n;i++){
		a[i]=get();
		if(a[i]=='W')
		  sum++;
	}
	cnt+=sum*3ll;
	for(int i=1;i<=cnt;i++){
		E[i].clear();
		d[i]=f[i]=fa[i]=0;
	}
	cnt=n;
	for(int i=1;i<n;i++)
	  add(u[i],v[i]);
	for(int i=1;i<=n;i++){
		if(a[i]=='W'){
			ll x,y,z;
			x=++cnt;
			y=++cnt;
			z=++cnt;
			add(i,x);
			add(x,y);
			add(x,z);
		}
	}
	n=cnt;
	for(int i=1;i<=n;i++){
		if(d[i]>3){
			puts("White");
			return ;
		}
	}
	for(int u=1;u<=n;u++){
		if(d[u]==3){
			sum=0;
			for(auto v:E[u])
			  if(d[v]>1)
			    sum++;
			if(sum>=2){
				puts("White");
				return ;
			}
		}
	}
	sum=0;
	for(int i=1;i<=n;i++){
	    if(d[i]==3){
	    	sum++;
	    	if(x)
	    	  y=i;
	    	else
	    	  x=i;
		}
	}
	if(sum<2){
		puts("Draw");
		return ;
	}
	if(sum>2){
		puts("White");
		return ;		
	}
	ans=0;
	dfs(1,1);
	f[x]=1;
	while(fa[x]){
		f[fa[x]]=f[x]+1;
		x=fa[x];
	}
	while(y){
//		cerr<<y<<'\n';
		if(f[y]){
			ans+=f[y]-1;
			break;
		}
		ans++;
		y=fa[y];
	}
	if(ans&1ll)
	  puts("Draw");
	else
	  puts("White");
}
int main(){
	T=read();
	while(T--)
	  solve();
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：0)

先分析博弈性质：首先由于获胜条件是对等的，而且初态不会使后手占优，所以后手必不胜，先手必不败。故只需判断平局。

先不考虑有初始颜色，分析先手必胜的必要条件（进一步地，考虑充要条件）。

手玩数据发觉若一个点度数太大那么先手将此点染白即可。具体地，若存在度数超过 $3$ 的节点，则先手必胜，若不存在度数超过 $2$ 的节点（即一条链）则必和。

考虑一颗最大度数为 $3$ 的树。不妨取出其一个度数为 $3$ 的点。

先手定会将其染白尝试获胜，分析可得若其的邻点存在两个度数非 $1$ 的点则先手必胜。

那么度数为 $3$ 的点个数断然不超过 $2$。（画图易证）

个数为 $1$ 是平凡的，为 $2$ 则考虑连接两点的链的长度，易知答案仅和其奇偶性相关。

综上，我们解决了没有初始颜色的问题。

再考虑若初始时有一点为白点（记为 $u$），考虑改变树的局部形态使得初始颜色给先手的优势转化为先手决策上的优势。具体地，考虑建立虚点 $v_1,v_2,v_3$ 连边 $(u,v_1),(v_1,v_2),(v_1,v_3)$。对于这个局部型，若先手将 $u$ 染白，则后手必须将 $v_1$ 染白，故先手做此操作没有代价，且先手染 $v_1,v_2,v_3$ 任何一个都不会优于染 $u$，所以这步转化对答案无影响。由于转化后是没有初始颜色的一棵树，所以这道题就做完了。
# 
探其渊薮，我们先无视初始颜色，用分类讨论图的形态处理了一个图上博弈问题，然后将原问题化归为一个弱化限制的问题。最后一步化归着实巧妙。
# 
[$\color{green}{\checkmark}$](https://codeforces.com/contest/1110/submission/259441708)

---

## 作者：chlchl (赞：0)

所以 CF 的黑和紫是看心情评的是吗。。。。

## Solution
稍加推敲可以发现，黑根本不可能胜利，他只能阻碍白获胜，因此只有白胜和平局两种。

而显然平局的情况比白胜要多得多，所以我们讨论白胜。

先讨论不染色怎么做，原因就是~~校内模拟赛有 40 分部分分~~就算有染色，我们应该也可以通过一些类似 DP 和拆点转化等方法，将其变为无色。

显然若一个点的度 $\ge 4$，一定白胜，选那个点，剩下四个儿子至少能够选两个。

度为 $3$ 行不行啊？稍加思考，好像可以。如下图，若度为 $3$ 的节点有两个儿子度 $\ge 2$，则必定白胜，操作方式仍然如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/tifopj04.png?x-oss-process=image/resize,m_lfit,h_400,w_500)

那么剩下度为 $3$ 但是不满足上述情况的呢？

稍加思考，貌似只剩下这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/4f1am3rq.png?x-oss-process=image/resize,m_lfit,h_400,w_550)

两边是链，中间是一条链相连的“H”型，其实本质上是两个度为 $3$ 的点相连的情况（那两个转折点）。

定义两点间距离为两点间的节点个数（包含这两个节点）。

那么如果度为 $3$ 的两个点，距离为奇数，那么按上图的走法，白总能获胜（如果黑第四步下 $5$ 的位置，白直接走 $4$ 连上就赢了）。

否则若距离为偶数，那就平局。

但是这种东西不好判，我们需要找到一个能快速解决这玩意的工具。

容易发现，树上任意三点一定在同一条**链**上，假设顺序为 $a\rightarrow b\rightarrow c$。

如果 $a\rightarrow b$ 或 $b\rightarrow c$ 为奇数，那么白一定就赢了。

否则它俩都是偶数，这时 $a\rightarrow c$ 的距离就是两个偶数加起来再 $-1$（$b$ 被算了两次）！

它仍然是个奇数！！！！！

也就是说，如果度为 $3$ 的点出现了 $\geq 3$ 个，必然有解。否则我们最多只用跑一次 dfs 找两点距离，时间复杂度是 $O(n)$ 的。

好了，无色的解决了，现在想想白点怎么办？

若一个点初始是白点，等价于让白多走了一步。~~但是这样就很不公平~~，黑根本就没走过！

所以考虑在白点周围加点，让黑一定要走那个加上的点，这样对实际操作并无影响。

如何让黑必须走那个点？简单，构造一个情况，如果黑不走那里白就赢了，不就行了吗？

不过还需要考虑一点，你加的点，黑走完之后，其它点不能让白走，因为实际上是没有这些点的，白不能走。

经过一番讨论，我们找到了最开始度为 $3$ 的那种情况，并且构造出了如下的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ffinvsor.png?x-oss-process=image/resize,m_lfit,h_500,w_550)

这个图就很好解释为什么不能构造右边的那个图了。

然后就没了，代码也不难写。~~感觉这题还没某些丧心病狂的紫数据结构难。~~

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
const int M = N << 2;
int T, n, tot, d[M], dis[M];
vector<int> g[M];
char col[N];

void dfs(int u, int fa){
	for(int v: g[u]){
		if(v == fa)
			continue;
		dis[v] = dis[u] + 1;
		dfs(v, u);
	}
}

bool check(){
	int d3 = 0, u[2] = {0, 0};
	for(int i=1;i<=tot;i++){
		if(d[i] >= 4)//度为 4 啥都不用玩，直接在儿子上瞎染
			return 1;
		else if(d[i] == 3){
			if(d3 <= 1)
				u[d3] = i;
			++d3;//首先判一下数量 
			int d2 = 0;
			for(int v: g[i])
				d2 += (d[v] >= 2);
			if(d2 >= 2)
				return 1;//至少有两个儿子向外面延伸了 
		}
	}
	if(d3 >= 3)
		return 1;//树上三点必然有两点距离为奇 
	else if(d3 == 2){
		for(int i=1;i<=tot;i++)
			dis[i] = 0;
		dis[u[0]] = 1;//距离定义为经过的节点数 
		dfs(u[0], u[0]);
//		printf("Now %d is the root! The distance of each vertice is: \n", u[0]);
//		for(int i=1;i<=tot;i++)
//			printf("%d ", dis[i]);
//		cout << endl;
		if(dis[u[1]] & 1)
			return 1;
	}
	return 0;
}

void solve(){
	for(int i=1;i<=tot;i++)
		g[i].clear(), d[i] = dis[i] = 0;
	scanf("%d", &n);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
		++d[u], ++d[v];
	}
	tot = n;
	scanf("%s", col + 1);
	for(int i=1;i<=n;i++){
		if(col[i] == 'W'){
			g[i].push_back(tot + 1), g[tot + 1].push_back(i);
			++d[i], ++d[tot + 1];
			g[tot + 1].push_back(tot + 2), g[tot + 2].push_back(tot + 1);
			++d[tot + 2], ++d[tot + 1];
			g[tot + 1].push_back(tot + 3), g[tot + 3].push_back(tot + 1);
			++d[tot + 3], ++d[tot + 1];
			tot += 3;//将白点拆成“令白多走一步并且黑一定牵制住白”的情况 
		}
	}
	if(check())
		printf("White\n");
	else
		printf("Draw\n");
}

int main(){
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
```


---

