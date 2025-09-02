# [USACO20DEC] Cowntagion S

## 题目描述

Farmer John 和他的农民团队为了控制牛传染病 COWVID-19 在他们农场间的传播而夜以继日地工作。

他们共同监控着 $N$ 个农场（$1≤N≤10^5$），编号为 $1…N$。农场间由 $N−1$ 条道路连接，使得每个农场都可以从农场 $1$ 出发经过一些道路到达。

很不幸，农场 $1$ 中的一头奶牛的 COWVID-19 检测呈阳性。暂时这个农场的其他奶牛以及其他农场的所有奶牛都还没有染上疾病。然而，根据这个疾病通过接触传播的特性，Farmer John 推测每一天都会有以下不利的事件之一发生：

(1) 在一个农场内，「超级传播者」导致该农场感染 COWVID-19 的奶牛数量翻倍；或者

(2) 一头感染 COWVID-19 的奶牛从一个农场沿道路去往了一个相邻的农场。

Farmer John 担心疫情会很快爆发。请帮助 Farmer John 求出每个农场内均有至少一头奶牛感染疾病所需经过的最小天数。 

## 说明/提示

该样例对应的一个可能的事件序列如下：农场 $1$ 内染病的奶牛数量翻倍再翻倍，使得两天后农场 $1$ 内有 $4$ 头染病的奶牛。在此后 $3$ 天，分别有一头染病的奶牛从农场 $1$ 去往农场 $2$、$3$ 和 $4$。$5$ 天过后每个农场均有至少 $1$ 头染病的奶牛。


 - 测试点 1-4 中，每个农场均直接与农场 $1$ 相连（除农场 $1$ 外）。
 - 测试点 5-7 中，农场 $2…N$ 均至多与两条道路相连。
 - 测试点 8-15 没有额外限制。

供题：Dhruv Rohatgi 

## 样例 #1

### 输入

```
4
1 2
1 3
1 4```

### 输出

```
5```

# 题解

## 作者：Unordered_OIer (赞：21)

# P7148 题解
## 题意
给定一棵树，每次可以进行两个操作：
1. 选择一个节点，该节点的值翻倍。

2. 选择一个节点，使其均匀地将其值分给其所有的儿子。

问最少经过多少次操作可以将所有节点的值都 $\geq 1$。
## 题解
首先，对于每一个节点，如果它的感染者数目已经超过了儿子数，则进行的一定是儿子个数次 (2) 操作。

反之，如果在还没有足够的感染者个数的情况下就开始分，显然是不优的。

所以对于每一个节点都进行贪心：
- 如果还不够分，就执行若干次 (1) 操作，直到够分了为止。

- 如果已经够分了，就花若干天，每天执行一次 (2) 操作直到所有儿子都有感染者为止。

很容易证明这是最优的。

于是我们记录每一个节点的儿子个数，记为 $cson[u]$，每次 $dfs$ 到一个点，我们就先计算 $(\log cson[u])+1$，表示自增至足够感染者的天数（注意不是 $\text{ceil}$ ），然后进行分发，即花 $cson[u]$ 天给所有儿子都发一个感染者，最后注意根节点本身就有一只感染者，处理一下即可。

复杂度 $\mathcal O(n)$，期望得分 $100$ 分。

其实甚至可以不用 $dfs$，从 $1$ 枚举到 $n$ 然后对于每一个节点都单一决策也行。

#### UPDATE 2020/12/27 : 修改了一处笔误，求管理大大重新审核一下 qwq

---

## 作者：Kalium (赞：9)

# 题解 P7148 【[USACO20DEC] Cowntagion S】

本人没打 $usaco$ （whk问题）

场外选手口胡

## 题意：

有 $n$ 个点，$n - 1$ 条边的一张图，在 $1$ 号农场有 $1$ 奶牛感染病毒，每天这头奶牛要么繁殖一个新的病毒奶牛，要么就是有一个病毒奶牛去了别的农场，现在求至少几天每个农场都有一头有病毒的奶牛

## 思路：

~~为什么走了就不能繁殖~~

回到正题

可以很容易得到，只要这个点 $u$ 农场的病毒奶牛的个数能够大于 $u$ 所能到达的所有农场的个数，那么我们就可以出发了

至此，思路已经有了

1.将 $1$ 号点入队并标记

2.取出队头，然后遍历出边，将其出边入队并标记

3.不断将 $1$ 号牧场的奶牛数量扩大并 $ans ++$，直至大于出度数量是终止

4.将 $ans$ 加上其出度

重复 $2$，$3$，$4$ 步，直至队列为空

## 代码：

# CODE

```cpp
#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 1e5 + 7;

int n;

struct Edge {
	int to, next;
} edge[N << 1];

int head[N], cnt;

bool use[N];

inline int read() {
	int n = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -f;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		n = (n << 3) + (n << 1) + (c ^ '0');
		c = getchar();
	}
	return n * f;
}

inline void ins(int u, int v) {
	edge[++ cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
}

inline void bfs() {
	queue <int> q;
	int out = 0, ans = 0, sum = 1;
	use[1] = 1;
	q.push(1);
	while (! q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; ~i; i = edge[i].next) {
			int v = edge[i].to;
			if (! use[v]) {
				out ++;
				use[v] = 1;
				q.push(v);
			}
		}
		while (sum <= out) {
			ans ++, sum <<= 1;
		}
		ans += out; 
		sum = 1, out = 0;
	}
	cout << ans << endl;
	return ;
} 

int main() {
	n = read();
	memset(head, -1, sizeof(head));
	for (int i = 1, u, v; i < n; i ++) {
		u = read(), v = read();
		ins(u, v);
		ins(v, u); 
	}
	bfs();
	return 0;
}
```


---

## 作者：wsyhb (赞：8)

## 题意简述

PS：为方便描述，下文将每个农场中染上疾病的奶牛的数量视为对应节点的点权，记为 $v$，$v$ 并未在原题中出现。

给定一棵 $N$ 个节点的树，第 $i$ 个节点权值为 $v_i$，初始时 $1$ 号节点权值为 $1$，其余点权值均为 $0$，接下来每一天都会发生下列两种事件中的一种：

1. 对于某个节点 $i$，$v_i$ 变为原来的两倍；

2. 对于某条边 $(a,b)$，$v_a$ 将大小为 $1$ 的权值向 $v_b$ 转移，即 $v_a$ 减去 $1$，$v_b$ 加上 $1$。

问最少多少天可以使得所有节点权值均大于 $0$，即对于任意 $1 \le i \le n$，满足 $v_i>0$。

**数据范围**：$N \le 10^5$

## 分析 + 题解

每一天有两种事件可以选择，如何选取才最优呢？

或许你会使用如下策略：

先花费若干天将 $v_1$ 翻倍，使得 $v_1 \ge N$，然后以 $1$ 为根向下转移权值。$ans=\lceil log_{2}N\rceil + \sum_{i=2}^N dis_i$，其中 $dis_i$ 表示 $i$ 到根节点 $1$ 的距离。

**通过举例可以发现，当这是一张以 $1$ 为中心的菊花图时，上述策略是最优的，反之则不一定。**

举例：

![](https://cdn.luogu.com.cn/upload/image_hosting/x4bqjeru.png)

可以发现，对于这棵树的一种最优策略是：依次讨论 $i=1,2,3,4$，将 $v_i$ 翻倍（由 $1$ 变成 $2$），然后下传 $1$ 至儿子节点 $i+1$，$ans=8$。

由此我们可以发现如下的**最优策略**：

**前序遍历整棵树，设当前讨论节点为 $i$ 号点，设其儿子个数为 $son_i$，经过若干次翻倍后使得 $v_i \ge son_i+1$，然后逐个下传给各个儿子。**

------------

简单**证明**一下：

首先，最优策略一定不会走回头路——满足 $i$ 号点必先满足 $i$ 的所有祖先。

其次，$i$ 号点最初的值必定从 $i$ 的祖先转移而来，而与其从 $i$ 的父亲以外的节点转移而来，不如直接利用 $i$ 的父亲翻倍获得。（因为这样的天数为 $2$，而从其余某个节点 $x$ 转移而来需要花费至少 $dis_{i,x} \ge 2$ 天）

再者，这样还可以使 $i$ 的儿子个数的增加合在一起，减少翻倍次数。

------------

故最终答案为：

$$ans= (N-1) + \sum_{i=1}^N \lceil log_{2}(son_i+1)\rceil $$

其中 $N-1$ 表示总共需要转移 $N-1$ 条边。

## 代码实现

`dfs` 遍历树，统计儿子个数，并预处理 `Log` 表即可。

时间复杂度：$O(N)$

贴一下代码：

``` cpp
#include<bits/stdc++.h>
using namespace std;
int N;
const int max_N=1e5+5;
int End[max_N<<1],Last[max_N],Next[max_N<<1],e;
inline void add_edge(int x,int y)
{
	End[++e]=y;
	Next[e]=Last[x];
	Last[x]=e;
	End[++e]=x;
	Next[e]=Last[y];
	Last[y]=e;
}
int son[max_N];
void dfs(int x,int fa)
{
	for(int i=Last[x];i;i=Next[i])
	{
		int y=End[i];
		if(y!=fa)
		{
			dfs(y,x);
			++son[x];
		}
	}
}
int Log[max_N];
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N-1;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y);
	}
	dfs(1,0);//遍历树 
	Log[0]=-1;
	for(int i=1;i<=N;++i)
		Log[i]=Log[i>>1]+1;//预处理 Log 表 
	int ans=N-1;
	for(int i=1;i<=N;++i)
	{
		ans+=Log[son[i]+1];
		if(Log[son[i]+1]==Log[son[i]])
			++ans;//因为是上取整，所以判断一下 son[i]+1 是否为 2 的次幂 
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：零殇 (赞：6)

$n$个结点和$n-1$条边，形成一棵树。

对于每个节点，最优策略就是不断增加奶牛的感染数，当达到足以分配给所有子树的个数时，就分配下去。然后对每个子树进行同样的操作，直到叶子节点位置。

关于这道题的具体实现，我和楼上大佬们有一点点不同。对于两个相连的结点$x$与$y$，可以把两个的边个数分别加$1$，最后除了根节点$1$之外，所有节点的子树个数就都是边的个数$-1$（其中$1$代表父亲结点）。这样我们就可以省去建图的麻烦。

### 注意点

分配时不仅要分给子树，自己也要留一个

上代码：
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int sum[100001],ans;
long long tot;
int main()
{
	int n,x,y;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		sum[x]++;//记录边的个数 
		sum[y]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(i!=1)//排除根节点 
			sum[i]--;//子树个数为边个数减1 
		x=1;
		while(x<=sum[i])//没达到所需个数 
		{
			tot++; 
			x*=2;//翻倍增长 
		}
		tot+=sum[i];//分配 
	}
	printf("%lld",tot);
	return 0;
}
```
完结撒花~

---

## 作者：Skies (赞：6)

这道题是贪心和树的遍历的结合

~~首先建图大家都会吧~~
```cpp
struct node{
	int to,nex;
}ed[2*N];
int head[N],idx;
void add(int x,int y)
{
	ed[++idx].to=y;
	ed[idx].nex=head[x];
	head[x]=idx;
}
```
链式前向星

然后想想贪心的思路

这是一棵树

![](https://cdn.luogu.com.cn/upload/image_hosting/mpxjrwpf.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

1号点有一头牛

节点的牛的来源只能来自于父亲节点

### 现在如果要给2号牛，1号节点给一只牛就是最优选择

为什么呢？

因为翻倍和给一头牛代价一样，所以给2头牛和给1头牛再翻倍是一样的

### 以此类推，多头牛时，翻倍是更优的一种选择,并且只需给每个子节点1头牛

下一步思考

如何给子节点牛?

当前节点有1头牛

假如有k个子节点

那么需要
$$log_2(k+1)$$
次翻倍操作


所以每次只要统计有多少个子儿子，逐步累加即可
# code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
const int N=1e5+10;
struct node{
	int to,nex;
}ed[2*N];
int head[N],idx;
void add(int x,int y)
{
	ed[++idx].to=y;
	ed[idx].nex=head[x];
	head[x]=idx;
}//链式前向星
long long p; 
int si[N];//存子节点个数
void dfs(int x,int fa)
{
	int lo=-1;
	if(x==1)lo++;
	
	lo+=si[x];
	p+=lo;
	int u=0;
	while(1)//计算log
	{
		if((1<<u)>lo)break;
		u++;
	}
	p+=u;
	for(int i=head[x];i;i=ed[i].nex)
	{
		int y=ed[i].to;
		if(y!=fa)dfs(y,x);
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
		si[x]++;si[y]++;//子儿子个数
	}
	dfs(1,0); 
	cout<<p;
	return 0;
}
```
~~管理员大大求过~~





---

## 作者：Alarm5854 (赞：4)

题意简述：有一棵树，这棵树上除了 $1$ 号节点的权值为 $1$ 以外，其他节点权值都为 $0$。现在对于第 $u$ 个节点有如下两个操作（设第 $i$ 个点权值为 $a_i$）：

- 将 $a_u$ 乘以 $2$
- 将 $a_u$ 减一，将 $a_v$ 加一（$v$ 是 $u$ 的儿子）

求每个节点的权值都不为 $0$ 的最少操作次数。

显然，有一种贪心的思路就是先将 $a_u$ 不停地乘以 $2$，直到 $a_u>s_u$（$s_u$ 为 $u$ 的儿子个数），然后，将 $a_u$ 减去 $s_u$，将 $u$ 的每一个儿子 $v$ 的 $a_v$ 都变为 $1$。

这样的操作次数是最少的，因为乘 $2$ 的效率比加 $1$ 的效率高，持续乘 $2$ 的效率比边减边乘 $2$ 的效率高，所以这样的操作次数是最少的。

```cpp
#include<queue>
#include<cctype>
#include<cstdio>
using namespace std;
const int N = 1e5 + 10;
int read() {
	int x = 0, f = 1; char c;
	while (!isdigit(c = getchar())) f -= (c == '-') * 2;
	while (isdigit(c)) x = x * 10 + f * (c - 48), c = getchar();
	return x;
}
struct Edge {
	int to, nxt; Edge(int to = 0, int nxt = 0): to(to), nxt(nxt){}
} e[N * 2];
int n, tot, ans, lg[N], fa[N], cnt[N], head[N];
void add(int u, int v) {
	e[++tot] = Edge(v, head[u]);
	head[u] = tot;
}
void dfs(int x) {
	cnt[x] = 1;
	for (int i = head[x]; i; i = e[i].nxt) {
		int y = e[i].to; if (y == fa[x]) continue;
		fa[y] = x, dfs(y), ++cnt[x];
	}
}
void bfs() {
	queue<int> q; q.push(1);
	while (!q.empty()) {
		int x = q.front(); q.pop(); ans += lg[cnt[x]];//乘2的操作次数为lg[cnt[x]]次，lg数组代表log2向上取整
		for (int i = head[x]; i; i = e[i].nxt) {
			int y = e[i].to; if (y == fa[x]) continue;
			q.push(y);
		}
	}
}
int main() {
	n = read(), ans = n - 1;//转移需要n-1次
	for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
	for (int i = 2; i <= n; ++i) if (i & (i - 1)) ++lg[i];
	for (int i = 1; i < n; ++i) {
		int u = read(), v = read();
		add(u, v), add(v, u);
	}
	dfs(1);
	bfs();
	printf("%d", ans);
	return 0;
}
```

---

## 作者：ETHANK (赞：2)

## 题意
一棵树的根节点有一头牛，每次可以进行两种操作：

### 1.令一个节点上的牛数量翻倍

### 2.移动节点上的一头牛到它的任一相邻节点

问使每个节点都有牛的最少操作数。

## 思路
设$son[u]$为$u$节点的儿子个数。如果根节点只需要把它里面的牛移动给他的儿子，显然，我们只用$\left \lceil \log_2 son[rt]\right \rceil $次操作$1$把根节点的一头牛翻倍，再用$son[rt]$次操作$2$完成下放。

注意到对于任意$u$的儿子$v$，如果$u$向$v$下放的牛数量$k>1$，这种做法一定不是最优的。因为下放$k$头牛的总操作次数为$k$；而下放一头牛后用操作$2$达到数量为$k$头，总操作次数为：
$$1+\left \lceil \log_2 k\right \rceil\le k$$

以上述策略贪心，我们对于每个节点$u$，只需要做$\left \lceil \log_2 son[rt]\right \rceil +son[u]$次操作，那么总操作次数为：
$$\sum_{u=1}^n \left \lceil \log_2 son[rt]\right \rceil +son[u]=\boxed{n-1+\sum_{u=1}^n \left \lceil \log_2 son[rt]\right \rceil}$$

这样就愉快的通过了本题！
![image.png](https://i.loli.net/2020/12/31/F2PtXEQrmMDeh7b.png)

## 代码
只需预处理$Log(i)$以及记录每个点的度即可。

### 时间复杂度：$O(n)$
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){//快读
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int n,ans,deg[100005],Log[100005];
int main(){
    n=read();
    //预处理Log
    for(int i=1;i<=n;i++)Log[i]=Log[i>>1]+1;
    for(int i=1,u,v;i<n;i++){
        u=read(),v=read();
        deg[u]++,deg[v]++;
    }
    //节点1的度数就是儿子数
    ans=Log[deg[1]];
    for(int i=2;i<=n;i++){//有父亲的节点
        ans+=Log[deg[i]-1];//son[i]=deg[i]-1
    }
    printf("%d\n",ans+n-1);//加上总下放次数
    return 0;
}
```


---

## 作者：Zenith_Yeh (赞：2)

不难发现：
1. 一个点直接向另一个点传 $4$ 头奶牛，共 $4$ 步。
2. 一个点先传 $1$ 头奶牛再进行两次翻倍操作，共 $3$ 步。

发现达到的效果一样，但第二种方式要少一步。

所以可以得到一个最优策略。

就是当一个点有奶牛被感染时就先不断进行翻倍的操作，直到比与它连边的农场数要多时，就进行移动的操作即可。

**上菜：**
```
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{//优美的快读
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
        #define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
int head[100005],n,cnt,gs[100005],bs;
bool bj[100005];
vector<int> rz[100005];
queue<int> q;
inline int ksm(int x,int y)
{	int res=1;
	while(y)
	{	if(y&1)res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
int main()
{   n=read();
    for(register int i=1;i<n;++i)
    {	int x=read(),y=read();
    	rz[x].push_back(y);
    	rz[y].push_back(x);
	}
	gs[1]=1;
	q.push(1);
	while(!q.empty())
	{	int x=q.front();
		q.pop();
		if(bj[x])continue;
		bj[x]=1;
		for(register int i=0;i<rz[x].size();++i)if(!gs[rz[x][i]])gs[x]++;
		int now=0;
		while(ksm(2,now)<gs[x])now++;//不断翻倍，直到可以
		bs+=now;
		for(register int i=0;i<rz[x].size();++i)
			if(!gs[rz[x][i]])//分给别的农场
			{	gs[rz[x][i]]++;
				bs++;
				q.push(rz[x][i]);
			}
	}
	printf("%d",bs);
    return 0;
}
```


---

## 作者：MolotovM (赞：2)

# 树形DP＋记忆化搜索
考虑每次倍增一个农场病牛是指数级别，每个农场有意义的倍增次数不超过$log_2(n)$，所以可以在每个点枚举倍增次数

设f[i]为在ｉ号节点有一头病牛，感染ｉ的子树的最小时间花费

对于每个子节点考虑以下的决策：

- 1.放一头牛过去，感染整个子树
- 2.给子节点的子树的每个节点放一头牛

如果1更优则选择1决策，否则将当前节点所有2决策更优的节点存入优先队列，贪心决策

可以记录每个点的f值，时间复杂度$O(nlogn)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int Read(){
  	int s = 0 , w = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		s = (s << 1) + (s << 3) + ch - '0';
		ch = getchar();
	}
	return s * w;
}
const int INF = 0x3f3f3f3f3f3f3f;
const int MAXN = 1e5 + 50;
int n;
int head[MAXN],to[MAXN << 1],nxt[MAXN << 1],tot;
void add(int x,int y){
	to[++tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
}
int dep[MAXN],sz[MAXN],lg[MAXN],sum[MAXN];
int f[MAXN];
int DF(int u,int fa){
	if(f[u]) return f[u];
	int deg = 0 , ret = INF;
	dep[u] = dep[fa] + 1;
	sz[u] = sum[u] = 1;
 	for(int i = head[u] ; i ; i = nxt[i]){
		int v = to[i];
		if(v == fa) continue;
		deg ++;
	}
	if(deg == 0) return (f[u] = 0);
	for(int t = ceil(log2(deg + 1)) ; t <= ceil(log2(n)) ; t ++){
		int ctb = 0 , res = (1 << t);
		priority_queue<pair<int,int> >Q;
		for(int i = head[u] ; i ; i = nxt[i]){
			int v = to[i];
			if(v == fa) continue;
			int tmp = 1 + DF(v,u);
			if(tmp <= sum[v]) ctb += tmp;
			else Q.push(make_pair(- (tmp - sum[v]),tmp));
		}
		while(!Q.empty()){
			int x = Q.top().first , y = Q.top().second;
			Q.pop();
			if(res >= y - x){
				res -= y - x;
			}
			else ctb += y;
		}
		ret = min(ret,ctb + t);
	}
	for(int i = head[u] ; i ; i = nxt[i]){
		int v = to[i];
		if(v == fa) continue;
		sum[u] += sz[v] + sum[v];
		sz[u] += sz[v];
	}
	return (f[u] = ret);
}
#undef int 
int main(){
	#define int long long
	n = Read();
	for(int i = 1 ; i < n ; i ++){
		int x = Read() , y = Read();
		add(x,y);
		add(y,x);
	}
	cout << DF(1,0) << endl;
	return 0;
}
```


---

## 作者：Paris_Bentley (赞：1)

 USACO ， 2020 年 12 月银组第一题题解。

好久不打USACO这种线上比赛了，近年来越来越膨胀了，银组第一题竟然就直接来了个树也还比较意外。

说一下思路吧，我们简单的模拟。如果有这样的数据

5个节点4条路分别是： 
1 - 2, 2 - 3, 2 - 4, 2 - 5

如果我们选择在a感染后再一头一头牛运到后面很显然是浪费了很多时间。所以需要做的是每次从线上走的牛只要一头，然后每次在节点感染的牛数量刚好是儿子的数量。

核心过程如下：

1. 先用 vec 保存每个节点和其他那些位置相连，（因为题目中没有说 a 和 b 谁距离1更近）

2. 我这里是用了一下 bfs 求每个节点在树的第几层。并且标记每个节点的孩子数量。

3. 之后再来模拟每个节点需要多少天感染奶牛。

4. 千万别忘了每条路也需要时间，最后n+1.

```
#include<bits/stdc++.h>
using namespace std;
bool vis[100005];
int n,res,son[100005],x,y;
vector<int> vec[100005];
queue <int> q;
int main()
{
	scanf("%d",&n);
	for (register int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		vec[x].push_back(y);
		vec[y].push_back(x);
	}
	q.push(1);
	vis[1]=true;
	while (q.size())//BFS
	{
		int now=q.front();
		q.pop();
		for (register int i=0;i<vec[now].size();i++)//find sons
		{
			if (vis[vec[now][i]])
				continue;
			son[now]++; 
			q.push(vec[now][i]);
			vis[vec[now][i]]=true;
		}
	}
	int maxx=0;
	for (register int i=1;i<=n;i++)//how many cows do we need at the point
	{
		int cow=1;
		while(cow<son[i]+1)
		{
			res++;
			cow=cow*2;
		}
	}
	cout<<res+(n-1)<<endl;
	return 0;
}
```


---

## 作者：study_nerd (赞：1)

这一道题主要是分析每一个节点被传染的过程。

首先肯定是一个有病毒的节点不断扩倍，直到达到一定数量为止

这个数量是多少呢？可以发现，对于每个节点，只有和它相邻的点接受它的“感染者”才最优，如果把患者送到更远的点就要多花一天甚至更多，还不如送到离它最近的点后再扩倍再送，并且每次只送一个，送两个也要多花一天，也不如先送再扩倍。

不过如果一个节点如果已经向四周送过患者了，它就不会再用到了，也不用再送患者，因为这个节点至少有一个了。

总结一下，每次到了一个新的节点就不断扩倍，直到总数达到
  未被感染节点数+1（自己要留一个）  就不断向周围送人，不断这么做，直到所有点都被感染。

代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
const int N=1e5+5;
ll n,day=0,lg[20];
queue<ll>q[N];
bool vis[N];
void dfs(int x)
{
	vis[x]=1;
	ll num=1;
	if(!q[x].empty())
	{
		if(!vis[q[x].front()])
		{	
			num++;
		}
		ll sum=q[x].front();
		q[x].pop();
		q[x].push(sum);
		while(sum!=q[x].front())
		{
			ll y=q[x].front();
			q[x].pop();
			if(!vis[y])num++;
			q[x].push(y);
		}
	}
	if(num==1)return;
	else
	{
		for(int i=1;i<=19;++i)
		{
			if(lg[i]>=num)
			{
				day+=i;
				break;
			}
		}
		while(!q[x].empty())
		{
			ll y=q[x].front();
			q[x].pop();
			if(vis[y])continue;
			day++;
			dfs(y);
		}
	}
	return;
}
int main(){
	scanf("%lld",&n);
	lg[0]=1;
	for(ri i=1;i<=19;++i)lg[i]=lg[i-1]<<1;
	for(ri i=1;i<n;++i)
	{
		ll u,v;
		scanf("%lld%lld",&u,&v);
		q[u].push(v);
		q[v].push(u);
	}
	dfs(1);
	printf("%lld",day);
	return 0;
}
/*
9
1 2
1 3
1 4
4 5
4 6
5 7
5 8
5 9
*/
```


---

## 作者：Skyjoy (赞：1)

简单题，考场上脑筋不动想得太多竟然没写出来

题意的话大概就是有一棵树，根上有一只病牛，每一天可以选择将一个节点上的病牛复制或者让一头病牛转移，求使所有节点都有病牛的最小天数

这题想要直接从最开始入手是比较难的，但是我们可以从树的最底下入手，我们可以发现我们的最优策略应该就是自己一次性传染够再一个个发到下一层（也就是自己的所有儿子），这样是最好的，因为如果先转移再让下面的复制会浪费时间。所以答案就应该是 $(\sum_{i=1}^{n}\lceil logson_i\rceil)+n-1$ ，建图遍历即可，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,x,y,head[N],cnt,son[N],ans;
struct edge{
	int to,nxt;
}e[N<<1];
void add(int u,int v){
	e[++cnt].to=v,e[cnt].nxt=head[u],head[u]=cnt;
}
void dfs(int u,int f){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)continue;
		dfs(v,u);
		son[u]++;
	}
	int base=1;
	while(base<=son[u])base<<=1,ans++;
	ans+=son[u];
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs(1,0);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：jingkongwanglimiaoa (赞：1)

## 题目性质分析
- $n$ 个 点，由 $n$ $-$ $1$ 条边代表这是一个无向无环图

**得到结论1，对于每个牧场，有且只有一个牧场给它输送奶牛**

证明：若有两个牧场能给当前牧场输送奶牛，则这两个牧场一定有不经过当前牧场的路径与一号牧场相连，同时这两个牧场又都与当前牧场相连，则有环：一号牧场 $-$ 两个牧场 $-$ 当前牧场，不符合无向无环图的性质

- 每天只能有**一头**奶牛去**一个**牧场

**得到结论2，只要不断翻倍，一旦足够输送（即与它相连且还没有奶牛的牧场的数量），就可以开始输送，不用再翻倍了**

证明：很多人会想到一个问题：我给下一个牧场多送几头奶牛过去，翻倍的时候基数不就会更大了吗$——$然而一天只能送一头，你觉得是花一天送一头划算呢，还是花一天翻个倍划算呢？

针对这个翻倍的问题，有的人可能会想到，假如当前牧场已有16条牛，而它要输送17条牛，那可不可以不翻倍，让其他牧场来送呢

这时我们一直没用到的结论1排上用场了，如果这个牧场不送，那么它就会被它唯一的输送方咕咕咕掉，所以不能不送

## 具体实现
- 注意要开 vis 数组表示当前有没有牛，开双向边

- 然后跟据结论2模拟实现，存图我用的邻接链表

- 详情看代码与其注释

```cpp
# include <cstdio>
# include <queue>
using namespace std;
int lk[100010],vis[100010],hp = 0,n,u,v,ans = 0;
// n,u,v 为输入，ans 存答案最少天数，vis数组用来判断该牧场有没有牛
//lk数组、hp、以及下面的结构体，用来存图与遍历
struct sth{int pow,wei;}a[200010];
queue <int> q;
void add(int xx,int yy)//存图函数
{
	a[++hp] = {yy,lk[xx]};
	lk[xx] = hp;
}
void bfs()//遍历图
{
	while (!q.empty())
	{
		int user = q.front(),in = 0;
		q.pop();
		for (int i = lk[user];i;i = a[i].wei) if (!vis[a[i].pow]) in++;//存储它要输送的牧场的数量
		int sum = 1;
		while (sum <= in) sum *= 2,ans++;//翻一倍用一天，翻够了就退出
		ans += in;//每输送一头就要一天
		for (int i = lk[user];i;i = a[i].wei)//遍历图
		{
			if (!vis[a[i].pow]) q.push(a[i].pow);
			vis[a[i].pow] = 1;
		}
	}
}
int main()
{
	scanf("%d",&n);
	for (int i = 1;i < n;i++)
	{
		scanf("%d %d",&u,&v);
		add(u,v);
		add(v,u);
	}
	vis[1] = 1;//注意这里，1号牧场初始有牛要处理
	q.push(1); //初始入队
	bfs();
	printf("%d",ans);
}
```


---

## 作者：45dino (赞：1)

可以看出，对于一个点 $i$ ，若开始有一头牛，则要进行如下两步骤
- 进行传染
- 将奶牛输送到儿子节点上

由于最终的目标是所有点都有一头感染的牛，所以对于点 $i$，要保证其向所有子节点“输送”至少一头牛，可以证明，“输送”一头牛是最优的。

所以，每一个节点需要至少先达到子节点数+1头奶牛再进行输送。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=0;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
    return (flag?x:~(x-1));
}
struct node{
	int to,nxt;
} edge[199999];
int n,cnt,ans,head[100001],son[100001]; 
void add(int x,int y)
{
	edge[++cnt].to=y;
	edge[cnt].nxt=head[x];
	head[x]=cnt;
}
void dfs(int x,int fa)
{
	son[x]=1;
	for(int i=head[x];i;i=edge[i].nxt)
		if(edge[i].to!=fa)
		{
			dfs(edge[i].to,x);
			son[x]++;
		}
	int s=1;
	while(s<son[x])
	{
		ans++;
		s*=2;
	}
}
signed main()
{
	n=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	cout<<ans+n-1;
	return 0;
}

```


---

## 作者：andyc_03 (赞：1)

题目要求每个农场内均有至少一头奶牛感染疾病所需经过的最小天数。

#### 那么可以贪心的考虑每头个农场需要翻倍来满足其子节点的农场都有一个即可

这个的正确很容易想到 如果一个牛走两步，不如在翻倍再走一步，所以说，我们dfs走一遍即可

至于每个农场翻倍时，剩下的感染的牛不做处理即可，若要通过它们去感染新的农场，那么至少要走两步（此时子节点已经有一个），与翻倍子节点再走的操作数一样

代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+5;
int n,head[maxn],cnt;
struct edge
{
	int to,nxt;
}e[maxn<<1];
void add(int x,int y)
{
	e[++cnt].nxt=head[x];
	e[cnt].to=y;
	head[x]=cnt;
}
long long ans;
void dfs(int x,int fa)
{
	int son=0;
	for(int i=head[x];i;i=e[i].nxt)
	{
		int to=e[i].to;
		if(to==fa) continue;
		son++;
		dfs(to,x);
	}
	ans+=son;
	int tmp=1;
	while(tmp<=son)
	{
		ans++;
		tmp*=2;
	}
}
int main()
{
	scanf("%d",&n);
	int x,y;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
} 

```

~~代码略丑~~

---

