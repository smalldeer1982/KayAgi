# VOCV - Con-Junctions

## 题目描述

给一个 $n$ 个节点和 $n - 1$ 条边的树，现在要在一些节点放置灯最终点亮所有的边。

当一个节点上放置了一盏灯时，所有与它相连的边都会被点亮，且每一条边只需一个端点被点亮即认为被点亮。

试求最少的放灯数量和当放灯数量最少时的方案数。请将方案数结果模 $10007$ 输出。

数据范围：$n \le 100010$。

## 样例 #1

### 输入

```
2
4
1 2
2 3
3 4
3
1 2
1 3```

### 输出

```
2 3
1 1```

# 题解

## 作者：___new2zy___ (赞：6)

## 题解 SP666 【VOCV - Con-Junctions】

题目传送门:

https://www.luogu.org/problemnew/show/SP666

先吐槽一句：这题空间好大啊，貌似有点过~~（逃~~

===============================================

本题翻译请见讨论区(也是本人~~厚颜无耻~~发的)  (快逃

大概题意理解地差不多了，我们就来讲一下这题

首先看第一问，“求出最少放灯数量”

很简单，一看就是**树形DP**

我们设状态f[x][0]和f[x][1]表示对于以x为根的子树，x节点没放（或放了）灯之后使得这颗子树的边满足全被点亮所放置的最少灯数

如果我们设1为整棵树的根节点

那么，最终**第一问答案ans1=min(f[1][0],f[1][1])**

那么显然f有如下的两个**状态转移方程**:

	（以下y均表示y是x的子节点）
	
    1.f[x][0]=∑ f[y][1]
    
    2.f[x][1]=∑ min(f[y][0],f[y][1])

对于第一个转移方程，很好理解，因为x点不放置，要使得儿子与自己之间的边被覆盖，那么只能在儿子节点放置灯使得边被覆盖

那么对于第二个转移方程，我们也能很好的理解。对于x点，如果放置了灯，那么对于它的儿子y，放不放都可以（因为它们之间的边一定会被点亮），我们只需要累计满足y节点的最少数目就行了，即∑ min(f[y][0],f[y][1])

现在仔细回想一下，发现第一问类似这两题:

luogu p1352   [没有上司的舞会](https://www.luogu.org/problemnew/show/P1352)

luogu p2016   [战略游戏](https://www.luogu.org/problemnew/show/P2016)

二者都是**树形DP**，通过枚举以每个节点为根的子树是否放置来进行状态转移

那么其实本题第一问和战略游戏最像，推荐大家先去做掉这题

那么，第一问解决了，我们如何解决第二问

我们知道，对于第一问的转移方程是很好想出来的，但是对于方案数这种东西...emmmm..发现不太好做

有的同学可能想到了**dfs**~~（爆搜）~~理论上是可以过掉本题的~~（毕竟数据较水）~~，本人虽然没有亲测，但是想到如果数据大一些就可能会挂掉，还是放弃了这种思路

那么，我们不妨换一种思考方式

可以想到，对于**一个DP状态，它是由自己的儿子转移过来的**，那么我们自然可以想到**在进行状态转移的时候进行方案数的转移**

我们可以再新开一个二维数组num[maxn][2]，对于num[x][0]和num[x][1]分别表示在进行状态转移时，到达状态f[x][0]和状态f[x][1]时的方案数

那么经过分析num有如下的状态转移方程:

	（以下y表示是x的儿子）
	(1).num[x][0]=∏ num[y][1] 
    
    (2).
    ①当f[y][0]<f[y][1]时,num[x][1]=∏ num[y][0]
    ②当f[y][0]>f[y][1]时,num[x][1]=∏ num[y][1]
    ③当f[y][0]=f[y][1]时,num[x][1]=∏ (num[y][0]+num[y][1])
        
对于上面的状态转移方程，其实也很好理解

主要是**注意方案数要乘起来（乘法原理）**

(1)中的方程，和上面的f中的1.一致

(2)中的方程，如果要理解的话，可以这样：

我们对于第二个f的状态转移方程，它是由最小的儿子状态转移过来的，那么方案数也一定是这样转移的。那么当儿子两种状态的f值相等时，他们的方案数都是可以转移的，那么**他们的方案就要累加起来乘上（加法原理）**

那么到了这里，貌似这题也不难了呢，放代码吧

对了，还有，记得方案数**取模**，mod=10007

本人写的不是太好，望提出修改意见（逃

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
const int mod=10007;
inline int read()
{
    int p=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
    return f*p;}
const int maxn=100103;
struct Edge
{
    int from,to;
}p[maxn<<1];
int n,cnt,head[maxn<<1];
int f[maxn][2];
//f[i][0]和f[i][1]分别表示在第i个点是否放灯最后覆盖子树所用的最少灯数 
//num[i][0]和num[i][1]表示在第i个点做决策时的方案数 
ll num[maxn][2],ans;
inline void add_edge(int x,int y)//加边 
{
    cnt++;
    p[cnt].from=head[x];
    head[x]=cnt;
    p[cnt].to=y;
}
inline void TreeDP(int x,int fa)//树形DP 
{
    f[x][0]=0,f[x][1]=1;//最少放灯数初值
    num[x][0]=num[x][1]=1;//方案数初值
    for(int i=head[x];i;i=p[i].from)
        {
            int y=p[i].to;
            if(y==fa)continue;
            TreeDP(y,x);
            f[x][0]+=f[y][1];//这个点不放,只能由儿子放置转移过来 
            num[x][0]=num[x][0]*num[y][1]%mod;//转移方案 
            
            f[x][1]+=min(f[y][0],f[y][1]);//这个点放了,儿子放不放均可,取最小 
            if(f[y][1]<f[y][0])
                num[x][1]=num[x][1]*num[y][1]%mod;
            else if(f[y][1]>f[y][0])
                    num[x][1]=num[x][1]*num[y][0]%mod;
            else num[x][1]=num[x][1]*(num[y][1]+num[y][0])%mod;
            //转移方案 
        }
}
inline void Clean()
{
    memset(head,0,sizeof(head));
    cnt=ans=0;
}
int main()
{
    int T=read();
    while(T--)
        {
            n=read();
            for(int i=1;i<n;i++)
                {
                    int x=read(),y=read();
                    add_edge(x,y);
                    add_edge(y,x);
                }
            TreeDP(1,0);
            if(f[1][0]<f[1][1])ans=num[1][0];
            else if(f[1][0]>f[1][1])ans=num[1][1];
            else ans=(num[1][1]+num[1][0])%mod;
            //统计答案 
            printf("%d %lld\n",min(f[1][0],f[1][1]),ans);
            Clean();//清空 
        }
    return 0;
}

```

对于树形DP，希望同学们做一下这几题，当然上面那两只也算

luogu p1122  [最大子树和](https://www.luogu.org/problemnew/show/P1122)

luogu p1270  ["访问"美术馆](https://www.luogu.org/problemnew/show/P1270)

luogu p1273  [有线电视网](https://www.luogu.org/problemnew/show/P1273)

luogu p2015  [二叉苹果树](https://www.luogu.org/problemnew/show/P2015)

luogu p2014  [选课](https://www.luogu.org/problemnew/show/P2014)

luogu p3177  [树上染色](https://www.luogu.org/problemnew/show/P3177)

luogu p3360  [偷天换日](https://www.luogu.org/problemnew/show/P3360)

这些题目有些**树形DP**，同时包含**树上背包**，请注意

好啦，没了，感谢阅读

最后推广一下自己的blog:

https://www.luogu.org/blog/new2zy/

拜拜~~~ >=<


---

## 作者：_空白_ (赞：3)

注：本篇题解偏蒟蒻向，较为详细，dalao 轻喷。


[题目传送门](https://www.luogu.com.cn/problem/SP666)


## 题意简述：
给出一颗节点数为 $n$ 的树，从中选取最少个数的节点，使得树的每条边至少有一个端点被选取，求最少的节点数量和此时的情况数量（有点像 [P2016](https://www.luogu.com.cn/problem/P2016)）。


## 大致思路：
使用 vector 存边，用 DFS 遍历整棵树并在遍历时求出最少选取个数和情况数。


## 实现方法：



### 预处理：
清空 $dp$ 数组，清空所有 vector。


```cpp
for(int i=1;i<=n;i++)
	son[i].clear();
memset(dp,0,800080);
```


### 存边：
输入时用 vector 存边（避免由于占用空间过大造成的 CE $/$ MLE），存入时既存入 $a$ 至 $b$，又存 $b$ 至 $a$（在 DFS 时记录父节点即可防止重复遍历）。

```cpp
for(int i=1;i<=n-1;i++)
{
	int a,b;
	cin>>a>>b;
	son[a].push_back(b);
	son[b].push_back(a);
}
```

### DP过程：

$dp_{now,0/1}$ 表示以 $now$ 为根的字树，在该点不取 $/$ 取时最少要取多少个点才满足要求。

$num_{now,0/1}$ 表示以 $now$ 为根在个数为 $dp_{now,0/1}$ 时不取 $/$ 取时情况的个数。

由于本题中每个节点作为根都一样，在 DFS 时从 1 号节点开始即可。

#### 转移方程：

- $dp_{now,0}=dp_{son_{now,i},1}+dp_{now,0}$

  （如果当前节点没有被选择，就必须选择所有子节点）

- $dp_{now,1}=\min(dp_{son_{now,i},1},dp_{son_{now,i},0})+dp_{now,1}$

  （如果当前节点被选择了，子节点选不选就都可以了，所以选一个儿子被选和没被选中用点数较小的一个）

- $num_{now,0}=num_{son_{now,i},1}\times num_{now,0}$

  (不选该结点的情况数要乘选这个儿子时的情况数）

- 当 $dp_{now,0}<dp_{now,1}$ 时：

  $num_{now,1}=num_{son_{now,i},0}\times num_{now,1}$

- 当 $dp_{now,0}>dp_{now,1}$ 时：

  $num_{now,1}=num_{son_{now,i},1}\times num_{now,1}$

- 当 $dp_{now,0}=dp_{now,1}$ 时：

  $num_{now,1}=(num_{son_{now,i},0}+num_{son_{now,i},1})\times num_{now,1}$
  
  （选该节点的情况数要乘这个儿子选 $/$ 不选时的情况数）

其中，$now$ 为当前节点，$son_{now,i}$ 表示当前节点的第 $i$ 个儿子。

在遍历时依次遍历 **除父节点外的** 所有儿子。

```cpp
void dfs(int now,int fa)
{
	dp[now][1]=1;
	int siz=son[now].size();
	num[now][1]=1,num[now][0]=1;
	for(int i=0;i<=siz-1;i++)
	{
		if(son[now][i]==fa||son[now][i]==0)
			continue;
		dfs(son[now][i],now);
		int mi=min(dp[son[now][i]][0],dp[son[now][i]][1]);
		int zy=0;
		if(mi==dp[son[now][i]][0])
			zy+=num[son[now][i]][0];
		if(mi==dp[son[now][i]][1])
			zy+=num[son[now][i]][1];
		num[now][1]*=zy;
		dp[now][1]+=mi;
		num[now][0]*=num[son[now][i]][1];
		num[now][0]%=MOD;
		num[now][1]%=MOD;
		dp[now][0]+=dp[son[now][i]][1];
	}
	return;
}
```

注意在计算 $num$ 时要取模以及 $dp_{now,1}$ 的初始值是 1（因为其本身也使用了一个节点）。

### 输出：

最终最少的节点数为 $\min(dp_{1,0},dp_{1,1})$。

情况数即为对应的 $num$，但要注意在 $dp_{1,0}$ 与 $dp_{1,1}$ 相同时要输出两种情况对应的 $num$ 之和。

## 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD=1e4+7;
int t,n;
vector<int>son[100010];
int dp[100010][2];
int num[100010][2];
int nu;
int ans;
void dfs(int now,int fa)
{
	dp[now][1]=1;
	int siz=son[now].size();//提前算好大小，不要在循环里计算。
	num[now][1]=1,num[now][0]=1;
	for(int i=0;i<=siz-1;i++)
	{
		if(son[now][i]==fa||son[now][i]==0)//判断是否为它的父节点。
			continue;
		dfs(son[now][i],now);
		int mi=min(dp[son[now][i]][0],dp[son[now][i]][1]);
		int zy=0;
		if(mi==dp[son[now][i]][0])
			zy+=num[son[now][i]][0];
		if(mi==dp[son[now][i]][1])
			zy+=num[son[now][i]][1];
		num[now][1]*=zy;
		dp[now][1]+=mi;
		num[now][0]*=num[son[now][i]][1];
		num[now][0]%=MOD;//取模
		num[now][1]%=MOD;
		dp[now][0]+=dp[son[now][i]][1];
	}
	return;
}
int main()
{
	cin>>t;
	for(int c=1;c<=t;c++)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			son[i].clear();//clear()只能清空一个vector，所以要用循环来清空所有vector。
		memset(dp,0,800080);//800080就是dp数组的大小
		for(int i=1;i<=n-1;i++)
		{
			int a,b;
			cin>>a>>b;
			son[a].push_back(b);//存入vector
			son[b].push_back(a);
		}
		dfs(1,0);
		nu=0;
		ans=min(dp[1][0],dp[1][1]);//看看根节点取更好还是不取要更好
		if(ans==dp[1][0])
			nu+=num[1][0];//+=是为了保证在dp[1][0]=dp[1][1]时能把所有情况加上
		if(ans==dp[1][1])
			nu+=num[1][1];
		cout<<ans<<" "<<nu%MOD<<endl;
	}
	return 0;
   	//蒟蒻的第一篇题解，求管理员大大通过
}
```

---

## 作者：7KByte (赞：1)

$\texttt{SP666}$ 到此一游。。。

第一问：树上最小点覆盖

第二问：树上最小点覆盖计数

第一问可以一遍动态规划解决，第二问可以在动态规划的决策树上二次$\texttt{DP}$解决。

如果具体一点的话，$f[u][0/1]$表示以$u$为根的子树中，$u$是否选的最少点数，$g[u][0/1]$表示方案数。

$f[u][0]=\sum\limits_{u\to v} f[v][1]$，$f[u][1]=1+\sum\limits_{u\to v}\max\{f[v][0],f[v][1]\}$。

$g[u][0]=\prod\limits_{u\to v} f[v][1]$，$g[u][1]=\prod\limits_{u\to v}g[v][0]/g[v][1]/g[v][0]+g[v][1]\ \ (f[v][0]\ \ </>/=\ \ f[v][1])$。

时间复杂度$\rm {O(TN)}$

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
using namespace std;
int n,f[N][2],g[N][2],h[N],tot;
struct edge{
	int to,nxt;
}e[N<<1];
void add(int x,int y){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;
}
void dfs(int x,int fa){
	f[x][0]=0;f[x][1]=g[x][1]=g[x][0]=1;
	for(int i=h[x];i;i=e[i].nxt)if(e[i].to!=fa){
		dfs(e[i].to,x);
		f[x][0]+=f[e[i].to][1];g[x][0]*=g[e[i].to][1];
		f[x][1]+=min(f[e[i].to][0],f[e[i].to][1]);
		if(f[e[i].to][0]<f[e[i].to][1])g[x][1]*=g[e[i].to][0];
		else if(f[e[i].to][1]==f[e[i].to][0])g[x][1]*=(g[e[i].to][0]+g[e[i].to][1]);
		else g[x][1]*=g[e[i].to][1];
		g[x][0]%=10007;g[x][1]%=10007;
	}
}
void solve(){
	memset(h,0,sizeof(h));tot=0;
	scanf("%d",&n);
	rep(i,1,n-1){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);
	if(f[1][0]<f[1][1])printf("%d %d\n",f[1][0],g[1][0]);
	else if(f[1][0]==f[1][1])printf("%d %d\n",f[1][0],(g[1][0]+g[1][1])%10007);
	else printf("%d %d\n",f[1][1],g[1][1]);
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：_czy (赞：0)

## 分析

一眼**树形DP**。

不过，它既要求最小灯数，又要求方案数，略有些繁琐。

令 $f_{i,0/1}$ 表示以 $i$ 为根的子树当 $i$ 不取或取的最少灯数。

再令 $s_{i,0/1}$ 表示以 $i$ 为根的子树当 $i$ 不取或取的在最少灯数时的方案数。

显然有：
$$f_{x,0}=\sum_{x\to y}f_{y,1}$$
$$f_{x,1}=\sum_{x\to y}\min(f_{y,0},f_{y,1})$$
根据[乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447)，我们可以相似的求出方案数：
$$s_{x,0}=\prod_{x\to y}s_{y,1}$$
- 当 $f_{y,0}<f_{y,1}$ 时：
$$s_{x,1}=\prod_{x\to y}s_{y,0}$$
- 当 $f_{y,0}>f_{y,1}$ 时：
$$s_{x,1}=\prod_{x\to y}s_{y,1}$$
- 当 $f_{y,0}=f_{y,1}$ 时：
$$s_{x,1}=\prod_{x\to y}s_{y,0}+s_{y,1}$$
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100012
#define P 10007
int t,n,f[N][2],s[N][2],h[N],x,y,ans,sum;
struct edge{
	int to,nxt;
}e[N*2];
void dfs(int x,int fa){
	f[x][0]=0,f[x][1]=s[x][0]=s[x][1]=1;
	for(int i=h[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa)continue;
		dfs(y,x);
		f[x][0]+=f[y][1],(s[x][0]*=s[y][1])%=P;
		f[x][1]+=min(f[y][0],f[y][1]);
		if(f[y][0]<f[y][1])(s[x][1]*=s[y][0])%=P;
		else if(f[y][0]>f[y][1])(s[x][1]*=s[y][1])%=P;
		else (s[x][1]*=s[y][0]+s[y][1])%=P;
	}
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)f[i][0]=h[i]=0;
		for(int i=1;i<n;i++){
			scanf("%d%d",&x,&y);
			int j=i*2-1;
			e[j]={y,h[x]},h[x]=j++;
			e[j]={x,h[y]},h[y]=j;
		}
		dfs(1,0);
		if(f[1][0]<f[1][1])ans=f[1][0],sum=s[1][0];
		else if(f[1][0]>f[1][1])ans=f[1][1],sum=s[1][1];
		else ans=f[1][0],sum=s[1][0]+s[1][1];
		printf("%d %d\n",ans,sum%P);
	}
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

这棵树是无根的，我们钦定它的根为 $1$。

接下来对于这个节点，我们不考虑它连接它爹的那条边，那条边它的爹来管。也就是这个节点只需要管好它到它的儿子们之间的若干条边。

设这个节点为 $x$，那么对于 $x$ 的某个儿子 $y$：

+ 如果 $x$ 没有点亮，$x\to y$ 这条边必须点亮啊，所以 $y$ 必须被点亮。
+ 如果 $x$ 已经点亮了，$y$ 怎么样都无所谓了啊，因为 $x\to y$ 被爹 $x$ 管住了。

显然的，从下往上转移这个的话，是没有后效性的，直接莽树形 dp。

即设 $f(x,p)$ 表示以 $x$ 为根的子树全部，其中 $x$ 是否点亮的最小花费。$p=0$ 表示不点，$p=1$ 表示点亮。

按照以下方程从下往上转移（$y$ 为 $x$ 的儿子）：

+ $f(x,0)=\sum f(y,1)$；
+ $f(x,1)=\sum \min(f(y,0),f(y,1))$。

然后你会发现有第二问，第二问也是很经典的题。

类似地，设 $g(x,p)$ 表示方案数。

根据乘法原理，$g(x,0)=\prod g(x,1)$。

$g(x,1)$ 由 $f(y,0)$ 和 $f(y,1)$ 中较小者对应的 $g(x,p)$ 转移而来。注意到 $f(y,0)=f(y,1)$ 时，加法原理，对这个节点的方案是 $(g(y,0)+g(y,1))$ 种。

具体一点的，看代码前的注释。

```cpp
/*
f[x][1/0] 表示以 x 为根，x 有/没 点过。
+ f[x][0]=sum {f[son][1]}
+ f[x][1]=sum min(f[son][1],f[son][0])
g[x][1/0] 表示方案数

则 g[x][0]=Pi {f[son][1]}
g[x][1]=Pi
{
	if f[son][1]==f[son][0]
		g[son][1]*g[son][0]
	else
		if(f[son][1]<f[son][0])
			g[son][1]
		else
			g[son][0]
}*/
#include <bits/stdc++.h>
#define rep(i,l,r) for(i=l;i<=r;++i)
using namespace std;
const int N=100015,p=10007;
int f[N][2],g[N][2];
vector<int> e[N];
int t,n,i,x,y,ans;
inline void dp(int id,int fa)
{
	f[id][0]=0;f[id][1]=1;
	g[id][0]=g[id][1]=1;
	if(e[id].empty())return ;
	for(auto nxt : e[id])
	{
		if(nxt==fa)continue;
		dp(nxt,id);
		f[id][0]+=f[nxt][1];
		f[id][1]+=min(f[nxt][0],f[nxt][1]);
		(g[id][0]*=g[nxt][1])%=p;
		if(f[nxt][0]<f[nxt][1])
			(g[id][1]*=g[nxt][0])%=p;
		else if(f[nxt][0]>f[nxt][1])
			(g[id][1]*=g[nxt][1])%=p;
		else
			(g[id][1]*=(g[nxt][1]+g[nxt][0])%p)%=p;
	}
	cout<<id<<' '<<f[id][0]<<' '<<f[id][1]<<' '<<g[id][0]<<' '<<g[id][1]<<endl;;
	return ;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		rep(i,1,n)e[i].clear();
		rep(i,2,n)
		{
			cin>>x>>y;
			e[x].emplace_back(y);
			e[y].emplace_back(x);
		}
		dp(1,0);
		if(f[1][0]<f[1][1])
			ans=g[1][0];
		else if(f[1][0]>f[1][1])
			ans=g[1][1];
		else ans=g[1][1]+g[1][0];
		cout<<min(f[1][0],f[1][1])<<' '<<ans%p<<endl;
	}
	return 0;
}
```

---

