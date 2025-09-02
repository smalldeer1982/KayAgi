# 「MCOI-01」Village 村庄

## 题目背景

今天，珂爱善良的0x3喵酱骑着一匹小马来到了一个村庄。

“诶，这个村庄的布局 ……”   
“好像之前我玩 Ciste 的地方啊 qwq”

0x3喵酱有一个地图，地图有着这个村庄的信息。

然后0x3喵酱要通过这张地图来判断 Ciste 有解无解啦 ~

注：Ciste 是《请问您今天要来点兔子吗》中的一种藏宝图游戏

## 题目描述

村庄被简化为一个 $n$ 个节点（编号为 $1$ 到 $n$）和 $n-1$ 条边构成的无向连通图。

0x3喵酱认为这个无向图里的信息跟满足以下条件的新图有关：

- 新图的点集与原图相同
- 在新图中 $u,v$ 之间有无向边 是 在原图中 $dis(u,v) \ge k$ 的**充分必要条件** （$k$ 为给定常量，$dis(u,v)$ 表示编号为 $u$ 的点到编号为 $v$ 的点最短路的长度）

0x3喵酱还认为这个"新图"如果为二分图，则 Ciste "有解"，如果"新图"不是二分图这个 Ciste "无解"。（如果您不知道二分图请翻到提示）

那么0x3喵酱想请您判断一下这个 Ciste 是否"有解"。

## 说明/提示

#### 样例解析

对于样例中的 **第一组** 数据：

原图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9f9zh4b2.png)
新图：

![](https://cdn.luogu.com.cn/upload/image_hosting/dg4es91e.png)

新图不为二分图，故输出 `Baka Chino`。

对于 **第三组** 数据：

原图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mku4v6uo.png)

新图：

![](https://cdn.luogu.com.cn/upload/image_hosting/15o3x3zz.png)

新图为二分图，故输出 `Yes`。

#### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 1（16 pts）$\ $ ：$n \le 10$。
- Subtask 2（24 pts）$\ $ ：$n \le 100$。
- Subtask 3（8 pts）$\ $ ：$n \le 1000$。
- Subtask 4（28 pts）：图退化成一条链。
- Subtask 5（24 pts）：无特殊限制。

对于 $100\%$ 的数据，$n \le 10^5$，$T \le 10$，$v \le 1000$，$k \le 1000000$。

本题数据使用 [CYaRon](https://www.luogu.org/discuss/show?postid=11410) 生成。

#### 提示


**二分图** 又称作二部图，是图论中的一种特殊模型。设 $G=(V,E)$ 是一个无向图，如果顶点 $V$ 可分割为两个互不相交的子集 $(A,B)$，并且图中的每条边 $(i,j)$ 所关联的两个顶点 $i$ 和 $j$ 分别属于这两个不同的顶点集 $(i \in A,j \in B)$，则称图 $G$ 为一个二分图。（摘自[百度百科](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E5%9B%BE/9089095?fr=aladdin)）

#### 说明

Minecraft OI Round 1 A

- Idea：0x3喵酱
- Solution/Std：0x3喵酱
- Data：0x3喵酱
- Tester：tarjin

## 样例 #1

### 输入

```
5
5 2
1 2 1
2 3 1
3 4 1
4 5 1
5 3
1 2 1
2 3 1
3 4 1
4 5 1
5 8
1 3 3
1 2 1
2 4 6
2 5 2
5 2
1 3 3
1 2 1
2 4 6
2 5 2
7 4
1 2 3
1 3 3
2 5 3
2 6 3
3 7 3
2 4 2```

### 输出

```
Baka Chino
Yes
Yes
Baka Chino
Baka Chino```

# 题解

## 作者：Zenith_Yeh (赞：29)

看到大家方法都不同。

此处献上换根dp


记一下每个点子树离他最远的三个点的距离 记一下每个点父亲最远距离 然后判断一下>=k就行

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int maxn=200010;
struct edge{
	int next,to,w;
}a[maxn*2];
int head[maxn],len;
void add(int x,int y,int z){
	a[++len]={head[x],y,z};
	head[x]=len;
}
int i,j,k,n,m,dp[maxn][4];//dp[][0]=每个点父亲最远距离，dp[][1]/[2]/[3]=每个点子树离他最远的三个点的距离。
void dfs(int now,int fa){
	for(int i=head[now];i;i=a[i].next){
		int u=a[i].to;
		if(u==fa)continue;
		dfs(u,now);
		if(dp[u][0]+a[i].w>dp[now][0]){//记录一下
			dp[now][3]=dp[now][2];
			dp[now][2]=dp[now][0];
			dp[now][0]=dp[u][0]+a[i].w;
			dp[now][1]=u;
		}else
		if(dp[u][0]+a[i].w>dp[now][2]){
			dp[now][3]=dp[now][2];
			dp[now][2]=dp[u][0]+a[i].w;
		}else
		if(dp[u][0]+a[i].w>dp[now][3])
			dp[now][3]=dp[u][0]+a[i].w;
	}
}
bool B=true;
void dfs2(int now,int fa,int len){
	for(int i=head[now];i;i=a[i].next){
		int u=a[i].to;
		if(u==fa)continue;
		if(u==dp[now][1])dfs2(u,now,max(len,dp[now][2])+a[i].w);
		else dfs2(u,now,max(len,max(len,dp[now][0])+a[i].w));
	}
	if((len>=k) + (dp[now][0]>=k) + (dp[now][2]>=k)>=2)B=false;//判断
	if(len+dp[now][2]>=k && dp[now][0]+dp[now][2]>=k)B=false;
	if(dp[now][2]+dp[now][3]>=k)B=false;
}
int main(){
	int T;cin>>T;
	while(T--){
		B=true;
		n=read();k=read();
		for(i=1;i<n;i++){
			int x=read(),y=read(),z=read();
			add(x,y,z);add(y,x,z);//加边
		}
		dfs(1,0);dfs2(1,0,0);
		if(B)puts("Yes");
		else puts("Baka Chino");
		for(i=1;i<=n;i++)dp[i][0]=dp[i][1]=dp[i][2]=dp[i][3]=head[i]=0;len=0;//赋初始值
	}
	return 0;
}
```


---

## 作者：一只书虫仔 (赞：24)

原文作者：莉墨lymoe

原题作者：莉墨 lymoe

他让我转过来的 qwq

---

**题目灵感**

当初其实是想考察一下“树上全源最短路”和“二分图染色”，想了很久也没想出怎么出。

最后就把这两个算法合到一块，就出现了这个题。

原本这个题难度并不高（刚开始数据 $ n $ 最大为 $1000$ （其实数据加强后，难度也不高QAQ）），后来WAAutoMaton发现了一个 $ O(n) $ 的算法，于是这个题就稍微难了一点。

**Part 0-题目分析**

分析题目可以发现，我们可以建立一个新图，新图中的点和原图中的点一一对应。如果 $ dis(u,v)\ge k $ 则在新图中把 $ u,v $ 相连。

那么新图中的任意一个“环”都对应一个满足题目条件的序列 $a_1 ,a_2,a_3,...,a_m$ 。

而如果新图中存在奇环，则为“无解”。

**part 1-测试点1~10 40分**

先用弗洛伊德算法求出全源最短路，建立新图。

我们知道不存在奇环的图为二分图。所以对新图进行二分图染色（或者用并查集判断二分图），若该图是二分图，则“有解”，若该图不是二分图，则“无解”。

**part 2-测试点15~20 64分（40+24）**

把弗洛伊德算法改用dfs求树上全源最短路即可。如果你嫌码量太小，使用tarjan、树剖、倍增等求lca的方法求最短路也可。

**part 3-测试点11~14 16分**

对于这一部分和下一部分的分数，已经不需要建立新图了，但是为了方便证明，我们还会说到这个新图。

我们来考虑一下这个**退化成链**的部分。

通过在纸上手造几个数据，我们可以发现新图的一个性质：若新图上存在奇数环，则一定存在三元环。

那么怎么证明呢？

由于链上的环跟链上的点编号无关，不妨设这个链上的点从左往右编号依次为 $ 1,2,3,...,n $ 。（ $1,2$之间连边，$2,3$ 之间连边...以此类推）

设这个链**对应的新图**存在奇环 $ a_1,a_2,...,a_m $ ，且 $ m\not= 3 $ 。

不妨设 $ a_1 $ 为奇环中编号最小的点，$ a_x $ 为奇环中编号最大的点。

那么显而易见 $ dis(a_1,a_x)\ge k $ 。（因为如果奇环中距离最远的两个点距离都小于 $ k $ 的话，则新图上一定不存在这个奇环）

假设奇环上**不存在**一点 $ a_q $ 满足 $ dis(a_1,a_q) \ge k \text{ and } dis(a_1,a_x)\ge k$ ，则

$ \because dis(a_1,a_2)\ge k $ 

$ \therefore dis(a_2,a_x) < k $

$ \because dis(a_2,a_3) \ge k ,dis(a_2,a_x)<k$ 

$ dis(a_3,a_x)\ge k,dis(a_1,a_3)<k $

...

以此类推，可以用数学归纳法证明（这里就省略数学归纳的过程），$dis(a_{2p},a_x)<k $ ，$ dis(a_{2p+1},a_1)<k $ ，其中 $ p\in N^* $ 。那么可以发现，因为 $dis(a_{2p},a_x)<k $ ，所以无法构成包含 $ a_x $ 的奇环。

故产生矛盾，则奇环上存在一点满足 $ dis(a_1,a_q) \ge k \text{ and } dis(a_1,a_x)\ge k$ 。

则证明了存在奇数环就一定存在三元环。

那么接下来，我们可以猜测：若存在三元环，则存在包括 $ 1 $ 号点和 $ n $ 号点的三元环。

证明：

我们设三元环为 $ (a_1,a_2,a_3) $ 且 $ a_1<a_2<a_3 $ 。

$ \because dis(a_1,a_2)\ge k,a_1\ge1 $

$ \therefore dis(1,a_2)\ge k $ 

$ \because dis(a_2,a_3)\ge k,a_3\le n $

$ \therefore dis(a_2,n) \ge k $ 

所以存在三元环 $ (1,a_2,n) $ 满足条件 。

那么对于链的解法就显而易见了。我们只需要求一下前缀和，然后看看链上是否存在一点能与首尾构成三元环。

**part 4-测试点21~25 100分**

对于这部分分，我们可以采用类比法（类比part 3）。

同理我们先来证明，若存在奇数环，则存在三元环。

首先我们找到奇环里距离最远的两个点 $ a_1,a_x $ 。

假设奇环上**不存在**一点 $ a_q $ 满足 $ dis(a_1,a_q) \ge k \text{ and } dis(a_1,a_x)\ge k$ ，则

$ \because dis(a_1,a_2)\ge k $ 

$ \therefore dis(a_2,a_x) < k $

$ \because dis(a_2,a_3) \ge k ,dis(a_2,a_x)<k$ 

$ \therefore dis(a_3,a_x)\ge k,dis(a_1,a_3)<k $

...（若比较难理解可以自行画图）

所以与 part 3 相同，因为 $dis(a_{2p},a_x)<k $ ，所以无法构成包含 $ a_x $ 的奇环。

那么接下来，我们可以猜测：若存在三元环，则存在包括直径两个端点的三元环。

证明：

首先我们将树简化：


![](https://cdn.luogu.com.cn/upload/image_hosting/adhd46a6.png)

大写字母表示点，小写字母表示边，该简化图中边长可以为 $ 0 $ 。

$ AB $ 为树的直径， $ (D,F,G) $ 为直径外一三元环。

我们可以假设三元环上任意一点都**不满足**“到 $ A $ 的距离不小于 $ k $ 且到 $ B $ 的距离不小于 $ k $ ” 。

不妨设 $ (f+d)+l+b< k $ ，则

$  (f+d)+c \ge k$

$ \therefore b+l<c $

$ \therefore a+l+c>a+l+b+l\ge a+b $

则 $ dis(A,D)> dis(A,B) $ ，则 $ (A,B) $ 不为直径，产生矛盾。

所以三元环上存在一点满足“到 $ A $ 的距离不小于 $ k $ 且到 $ B $ 的距离不小于 $ k $ ”。

那么正解的算法也就显而易见了，只需要先求树的直径，再看看是否存在一点到直径两端距离不小于 $ k $ 。

最后贴出std：

```cpp
#include<stdio.h>
#include<string.h>
#define MAXN 1000005
struct node
{
	int eh;
}V[MAXN];
struct edge
{
	int v;
	int to;
	int next;
}E[MAXN*2];
int tot;
int dis1[MAXN],dis2[MAXN];
void add_edge(int from,int to,int v)
{
	E[++tot]=(edge){v,to,V[from].eh};
	V[from].eh=tot;
}
void dfs(int i,int fa,int* dis)
{
	int p;
	for(p=V[i].eh;p;p=E[p].next)
	{
		if(E[p].to==fa) continue;
		dis[E[p].to]=dis[i]+E[p].v;
		dfs(E[p].to,i,dis);
	}
}
int main()
{
	int n,i,T,x,y,v,k,flag;
	scanf("%d",&T);
	while(T--)
	{
		memset(V,0,sizeof(V));
		memset(E,0,sizeof(E));
		tot=0;flag=1;
		scanf("%d%d",&n,&k);
		for(i=0;i<n-1;i++)
		{
			scanf("%d%d%d",&x,&y,&v);
			add_edge(x,y,v);
			add_edge(y,x,v);
		}
		dis1[1]=0;
		dfs(1,0,dis1);x=1;
		for(i=2;i<=n;i++)
		{
			if(dis1[i]>dis1[x]) x=i;
		}
		dis1[x]=0;
		dfs(x,0,dis1);y=x;
		for(i=1;i<=n;i++)
		{
			if(dis1[i]>dis1[y]) y=i;
		}
		dis2[y]=0;
		dfs(y,0,dis2);
		for(i=1;i<=n;i++)
		{
			if(dis1[i]>=k&&dis2[i]>=k) flag=0;
		}
		if(flag) printf("Yes\n");
		else printf("Baka Chino\n");
	}
	return 0;
} 
```

---

## 作者：JK_LOVER (赞：6)

## 题意
给你一棵树，如果在树上的距离大于或等于一个值，那么在原图上就会有一条边。判断原图是否为二分图。[QWQ](https://www.luogu.com.cn/blog/xzc/solution-p6722)
## 分析
一个图不是二分图的充要条件是原图没有奇环。我们尝试把这个把这棵树分成两部分。

- 代表元的选取

树上最长的路径是直径，那么直径的两个端点一定是在两个不同集合中的。

- 元素的扩展

我们只需要 $O(n)$ 从一个端点遍历整个树就可以标记哪些点和它是一个集合的，另一个端点也这样遍历。那么当有一个元素同时处于这两个集合中，那么说明出现了奇环。总的时间复杂度为  $O(n)$ 。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x = 0,f = 0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 1e6;
vector<int> G[N],W[N];
int dp[N],dis[N],Dis[N],col[N],n,rt,Rt,tot[N],k,pd = 0;
void dfs(int x,int fa){
//	cout<<dp[rt]<<" "<<dp[x]<<endl;
	if(dp[rt] < dp[x]) rt = x;
	for(int i = 0;i < G[x].size();i++)
	{
		int w = W[x][i],y = G[x][i];
		if(y == fa) continue;
		dp[y] = dp[x] + w;
		dfs(y,x);
		
	}
}
void dfs1(int x,int fa)
{
	if(dis[Rt] < dis[x]) Rt = x;
	if(dis[x] >= k) col[x] = 1;
	for(int i = 0;i < G[x].size();i++)
	{
		int w = W[x][i],y = G[x][i];
		if(y == fa) continue;
		dis[y] = dis[x] + w;
		dfs1(y,x);
	}
	
}
void dfs2(int x,int fa)
{
	if(Dis[x] >= k && col[x]) pd = 1;
	for(int i = 0;i < G[x].size();i++)
	{
		int w = W[x][i],y = G[x][i];
		if(y == fa) continue;
		Dis[y] = Dis[x] + w;
		dfs2(y,x);
	}
//	cout<<"x "<<x<<" col[x] "<<col[x]<<endl;
	
}
signed main()
{
	int T = read();
	while(T--){
		n = read();k = read();
		rt = Rt = pd = 0;
		memset(dis,0,sizeof(dis));
		memset(Dis,0,sizeof(Dis));
		memset(dp,0,sizeof(dp));
		memset(col,0,sizeof(col));
		for(int i = 1;i <= n;i++) G[i].clear(),W[i].clear();
		for(int i = 1;i < n;i++){
			int a = read(),b = read(),w = read();
			G[a].push_back(b);G[b].push_back(a);
			W[a].push_back(w);W[b].push_back(w);
		} 
		dfs(1,0);
		dfs1(rt,0);
		dfs2(Rt,0);
//		cout<<rt<<" "<<Rt<<" "<<endl;
		if(pd) cout<<"Baka Chino"<<endl;
		else cout<<"Yes"<<endl;
	}
}
```


---

## 作者：青鸟_Blue_Bird (赞：3)

蒟蒻来 ~~水一发题解，顺便~~ 理清一下官方题解的各种数学证明 ~~以及修复那崩坏的LATEX~~吧！

## 题意矫正

个人认为题目的描述有些“不好”。

如果是“新图中存在边$(u, v)$, 则原图中必须满足.....”
那么，原图上的距离即为新图建边的前提条件。

注意，仅仅是“前提条件”。

那么，如此理解，如果我的新图中没有边，全是点呢？ 那么不就永远成立了吗？

所以，个人认为题目应该描述为“如果原图中满足....., 那么新图中存在边$(u,v)$”。

(~~如果说错了望各位大佬斧正。~~)

## Step1 前置芝士：

如何证明一个图是二分图，又如何证明一个图不是二分图？

从定义入手： 二分图是一种不含有奇数条边环的图。

所以，对于此题，如果我们能确定新图中是否含有基环，我们就相应的可以确定这个数据合不合法。

## Step2 从暴力开始

考虑如何暴力建新图？

如果$dis_{u, v} \ge k$，那么在新图中就可以有连边呗。

所以，求出全源最短路，然后暴力建新图，最后判断是否为二分图就是我们的暴力做法了。
（~~感觉这个暴力也很麻烦的亚子，还不如继续推写正解(滑稽~~）

## Step 3 考虑基环的性质

在一个基环上，我们考虑每个点的编号为$a_1, a_2, a_3$ ~ $a_m$。
其中$a_m$为编号最大的一个基环上的点, 令 $m > 3$。

假设基环上不存在一个点$a_p$, 满足$dis(a_1, a_p) \ge k$ ^ $dis(a_p, a_m) \ge k$，即不满足存在三元环的条件


不妨利用数学归纳法：
设一点$a_x$存在于基环上。

当 $x = 1$时，显然有 $dis(a_1, a_m) \ge k$ ^ $dis(a_1, a_2) \ge k$

当$x = 2$时，显然有 $dis(a_2, a_3) \ge k$ ^ $dis(a_2, a_m) < k$

当$x = 2y(y ≠0)$时，有 $dis(a_{2y}, a_{2y+1}) \ge k$ ^ $dis(a_{2y},a_1) < k$ ^ $dis(a_{2y}, a_m) < k$  $\Rightarrow$ 可知，此时的$a_m$不能存在于基环中，显然不对。

（这里还要结合原图来看啊，建议大家结合样例来手摸。）


![hhh](https://s1.ax1x.com/2020/08/01/aGCdaR.png)

（基环）


那么，证明了图中存在三元环之后，~~我们来看看官方题解~~，看看三元环跟树的直径的关系。

![zzz](https://s1.ax1x.com/2020/08/01/aGni3d.png)

假设图中1,2,3号点构成三元环。
那么，有$d + e \ge k$, $d + f \ge k$, $e + f \ge k$.

令图中$a + b$为极大值，则 $4,5,6$为树的直径。

假设不存在一点到直径两端点可以构成三元环。

那么，令1号点等效于1,2,3号点。

为满足条件，我们有：

$d + c + a < k$, 配合前面的柿子：
 $d + e \ge k$
 
 不等式基本原则，$a + c < e$
 
 所以 $b + c + e > b + c + a + c > a + b$，此时$(2,6)$成为直径，不符合原图。
 
 所以，三元环上一定有一点到直径的两端距离均大于$k$。于是，我们只要找出树的直径，然后判断是否有点到其两端的距离均$\ge k$即可。如果存在，则原图存在基环，不成立。
 
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100010

template <class T>
inline void read(T& a){
	T x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){
		if(c == '-') s = -1;
		c = getchar();
	}
	while(isdigit(c)){
		x = x * 10 + (c ^ '0');
		c = getchar();
	}
	a = x * s;
	return ;
}

struct node{      
	public:
		int v, w, next;
	
	public:
		node(int v = 0, int w = 0, int next = 0){
			this -> v = v;
			this -> w = w;
			this -> next = next;
			return ;
		}// 为什么存个边要写得这么毒瘤？  因为方便赋予初值啊 
		
	public: 
		inline void clean(){
			this -> v = 0;
			this -> next = 0;
			this -> w = 0;
			return ;
		}
	
} t[N << 1];
int f[N];

int bian = 0;
inline void add(int u, int v, int w){
	t[++bian] = node(v, w, f[u]), f[u] = bian;
	t[++bian] = node(u, w, f[v]), f[v] = bian;
	return ;
}

int dis[N], dis1[N], dis2[N];
int s1, s2;
int maxn = -666;
int cur = 0;

#define v t[i].v
void dfs(int now, int father, int* dis){  // 用指针方便传入dis数组 
	if(dis[now] > maxn){
		maxn = dis[now];
		cur = now;
	}	
	for(int i = f[now]; i; i = t[i].next){
		if(v != father){
			dis[v] = dis[now] + t[i].w;
			dfs(v, now, dis);
		}
	}
	return ;
}
#undef v

inline void search(int x, int& y, int* dis){   // 找端点等各种操作 
	maxn = -666;
	cur = 0;
	dis[x] = 0;
	dfs(x, 0, dis);
	y = cur;
	return ;
}

inline void clean(){   // 不要忘记清空 
	for(int i = 1;i <= bian; i++)
		t[i].clean();
	memset(f, 0, sizeof(f));
	bian = 0;
	return ;
}

int main(){
	int T;
	read(T);
	while(T--){
		clean();
		int n, k;
		read(n), read(k);
		s1 = 0, s2 = 0;
		for(int i = 1; i < n; i++){
			int x, y, w;
			read(x), read(y), read(w); 
			add(x, y, w);
		}
		search(1, s1, dis);
		search(s1, s2, dis1);  // 找端点,顺便记录dis1 
		int temp = 0;
		search(s2, temp, dis2);  // 多搜一次，找dis2 
		bool flag = 0;
		for(int i = 1;i <= n; i++)
			if(dis1[i] >= k && dis2[i] >= k) {
				flag = 1;
				break;
			}
		if(flag)puts("Baka Chino");
		else puts("Yes");
	}
	return 0;
}
```



写了这么多，~~怎么感觉我像是在复述官方题解似的~~。

结尾强调一遍，本题难点，数学归纳法那里一定要画图，结合原图手摸啊！！








---

## 作者：HPXXZYY (赞：1)

$\color{blue}{\texttt{[Analysis]}}$

$\texttt{Subtask } 1,2,3$

我们可以直接指定 $1$ 为无根树的根，求出每个点之间的距离，暴力建图，然后判断是否是二分图即可。

如果想优化这个算法，那么我们可以用并查集来维护新图。即对于每个节点 $u$，开一个新点 $f(u)$，如果新图中加入一条新边 $(u,v)$，则在并查集中把 $(u,f(v))$ 和 $(v,f(u))$ 连接。如果发现 $u$ 和 $f(u)$ 在同一个集合中，则不是二分图。

$\texttt{subtask all}$

继续优化上面的算法。

记以点 $u$ 为根的子树为 $S_{u}$（谁是整棵树根节点不是很重要，你就认为 $1$ 是根节点吧）。

因为边权非负，所以如果点 $x$ 和点 $u$ 的距离不小于 $k$，那么对于 $\forall v \in S_{u}$，$x$ 和 $v$ 间的距离都不小于 $k$。

即：如果新图中有边 $(x,u)$，则对于 $\forall v \in S_{u}$，新图中有边 $(x,v)$。

那么，在新图中点 $u$ 和点 $v$ 就一定不能有边相连，即 $u$ 和 $v$ 间的距离就一定不能大于等于 $k$。

显然，我们不需要考虑原图的每一条边，我们考虑最难满足限制的那条边就可以了（它都符合条件，其它一定符合）。

于是我们想到树的直径。判断是否存在这样的一个节点，它到直径两端的点的距离是否都大于等于 $k$。如果有，则无解；没有，则有解。

> 注意，不能只判断直径上的点是否满足限制。
> 
> 如下图
> 
> ![在这里插入图片描述](https://img-blog.csdnimg.cn/bbfa010f9b1a45b8b7b6b70d1d108b0f.png)
> 
> 很显然，这棵树的直径应该是 $3 \to 1 \to 2 \to 4$，假设 $k=5$，我们发现对于直径上任何一点，它到直径两端（即点 $3$ 和点 $6$）的距离不都大于等于 $5$。
> 
> 但是我们观察点 $2$，它到 $6$ 的距离为 $8$，到 $3$ 的距离为 $6$，所以它是不符合限制的。
> 
> 因此，我们不能只判断直径上的点是否符合条件。

（这篇题解的说法可能不太严谨，但做法是对的，严谨的证明请大家看看其它题解）


$\color{blue}{\texttt{[Solution]}}$

1. 求出树的直径
2. 判断是否存在这样的点，使得它到直径两端的距离都大于等于 $k$.
3. 如果有，则输出无解信息 `Baka Chin`；否则，输出有解信息 `Yes`。

注意多组数据，要清空。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=1e5+100;

struct edge{
	int next,to,val;
}e[N<<1];int h[N],te;
inline void add(int u,int v,int w){
	e[++te]=(edge){h[u],v,w};h[u]=te;
}

bool vis[N];
int dist[N],dis[N];
inline void bfs(int be){
	queue<int> q;q.push(be);
	
	memset(dist,128,sizeof(dist));
	memset(vis,true,sizeof(vis));
	
	dist[be]=0;vis[be]=false;
	while (!q.empty()){
		int u=q.front();q.pop();
		for(int i=h[u];i;i=e[i].next){
			register int v=e[i].to;
			if (!vis[v]) continue;
			dist[v]=dist[u]+e[i].val;
			q.push(v);vis[v]=false;
		}
	}
}

int n,k;

inline int Farthest(int u){
	bfs(u);
	
	int ans=u;
	for(int i=1;i<=n;i++)
		if (dist[i]>dist[ans]) ans=i;
	
	return ans;
}

int main(){
	for(int T=1,Q=read();T<=Q;T++){
		te=0;//clear the graph
		memset(h,0,sizeof(h));
		
		n=read();k=read();
		for(int i=1,u,v,w;i<n;i++){
			u=read();v=read();w=read();
			add(u,v,w);add(v,u,w);//undirected
		}
		
		int rt=Farthest(1);
		int tmp=Farthest(rt);
		
		memcpy(dis,dist,sizeof(dis));
		
		bfs(tmp);
		
		bool flag=true;
		
		for(int i=1;i<=n;i++)
			if (dist[i]>=k&&dis[i]>=k){
				flag=false;break;
			}
		
		printf("%s\n",(flag?"Yes":"Baka Chino"));
	}
	
	return 0;
}
```

---

## 作者：Z_X_D_ (赞：0)

## 题意
~~[如下](https://www.luogu.com.cn/problem/P6722)~~。

给定一个树，建一个新图使得：

1. 点集与原图相同；

1. 在原图上距离大于 $k$ 的两点之间有一条边。

若这个新图是[二分图](https://oi.wiki/graph/bi-graph/)就输出 $\texttt{Yes}$，否则输出 $\texttt{Baka Chino}$。
## 分析
根据二分图的性质，二分图不存在奇环（即奇数条边组成的环）。那么假如这个新图存在奇环，它就一定不是二分图，反之，就一定是二分图。

因此，我们只要找原图中相距最远的两个结点（即[树的直径](https://oi.wiki/graph/tree-diameter/)的两端点），并在这条最长链上找到一个分叉满足：分叉深度+分叉点与两端点的距离分别大于等于 $k$，即可说明新图不为二分图。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct E
{
	int t,w;
};
vector<E>e[100010];
int le[100010],so[100010],lh,k,rt;
void dfs(int x,int fa)
{
	for(auto i:e[x])
	{
		if(i.t==fa)continue;
		dfs(i.t,x);
		if(lh<le[x]+le[i.t]+i.w)
			rt=x,lh=le[x]+le[i.t]+i.w;
		if(le[i.t]+i.w>le[x])
			so[x]=i.t,le[x]=le[i.t]+i.w;
	}
	return;
}
bool ddfs(int x,int fa,int de)
{
	if(de>=k&&le[x]>=k)
		return true;
	for(auto i:e[x])
	{
		if(i.t==fa||i.t==so[x])continue;
		if(le[i.t]+i.w+de>=k&&le[i.t]+i.w+le[x]>=k)
			return true;
	}
	if(so[x])
		return ddfs(so[x],x,de+le[x]-le[so[x]]);
	return false;
}
int main()
{
	int t,n,i,x,y,z;
	scanf("%d",&t); 
	while(t--)
	{
		scanf("%d%d",&n,&k);
		memset(so,0,sizeof so);
		memset(le,0,sizeof le);
		lh=0;
		for(i=1;i<=n;i++)e[i].clear();
		for(i=1;i<n;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			e[x].push_back({y,z});
			e[y].push_back({x,z}); 
		}
		dfs(1,0);
		while(so[rt])rt=so[rt];
		memset(so,0,sizeof so);
		memset(le,0,sizeof le);
		dfs(rt,0);
		if(ddfs(rt,0,0))printf("Baka Chino\n");
		else printf("Yes\n");
	}
	return 0;
}
```

---

